/**
    @file  i2c_iface.c
    @brief I2C driver implementation
 */
/*=============================================================================
            Copyright (c) 2017, 2021-2023 Qualcomm Technologies, Incorporated.
                              All rights reserved.
              Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
                              EDIT HISTORY
 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/15/23   vcs     returning proper error code in the i2c driver and handling the transfer request
 03/17/23   gkr     Added logic to initiate transfer only if IOS lines is high to avoid bad GENI state
 02/05/23   gkr     migration to new hwio format
 01/06/23   mp      Increased the poll time.
 10/11/22   SS      WA for Kuno reg read
 05/10/22   jc      Add Smbus Support
 03/25/22   bn      Added I2Chub support
 09/05/17   ska     Made changes to add cancel sequence for NACK (As per HPG)
 30/08/17   ska     Made changes to propogate proper error to client
 13/07/17   vg      Updated firmware API
 13/07/17   vg      Fixed KW issues
 31/05/17   vg      Copyright  updated 
=============================================================================*/

#include "i2c_drv.h"
#include <i2c_config.h>
#include "i2c_iface.h"
#include "i2c_plat.h"
#include "i2c_log.h"
#include "i2c_api.h"
#include "i2c_hal.h"
#include "i2c_fw_load.h"
#include "PlatformInfoDefs.h"

#define BUS_IFACE_TCE_STATUS_BIT_NACK       (1 << 10)
#define BUS_IFACE_TCE_STATUS_BIT_ARB_LOST   (1 << 12)
#define BUS_IFACE_TCE_STATUS_BIT_BUS_ERROR  (1 << 13)

#define TX_PACKING_CFG0_VAL 0x7F8FE
#define TX_PACKING_CFG1_VAL 0xFFEFE
#define RX_PACKING_CFG0_VAL 0x7F8FE
#define RX_PACKING_CFG1_VAL 0xFFEFE

#define POLL_TIME_DEFAULT_US    1000000
#define POLL_INTERVAL_US        5

static i2c_status i2c_handle_cancel_sequence(uint8 *se_base , i2c_status i_status);
extern DalPlatformInfoPlatformType ePlatformType;

typedef struct hsr_setting {
    uint32 index;
    uint32 value;
} hsr_setting;

/* Values from Image txt*/
#define GENI_FW_REVISION		0x333
#define GENI_S_FW_REVISION		0x0
#define GENI_INIT_CFG_REVESION	0x2


typedef enum cmd_opcode
{
    CMD_INVALID                 = 0,
    CMD_I2C_WRITE               = 1,
    CMD_I2C_READ                = 2,
    CMD_I2C_WRITE_THEN_READ     = 3,
    CMD_I2C_ADDRESS_ONLY        = 4,
    CMD_I2C_BUS_CLEAR           = 6,
    CMD_I2C_STOP_ON_BUS         = 7,
    CMD_I3C_PRIVATE_WRITE       = 9,
    CMD_I3C_PRIVATE_READ        = 10,
    CMD_I3C_HDR_DDR_WRITE       = 11,
    CMD_I3C_HDR_DDR_READ        = 12,
    CMD_I3C_READ_IBI            = 15,
    CMD_I3C_BROADCAST_CCC_WRITE = 16,
    CMD_I3C_DIRECT_CCC_WRITE    = 17,
    CMD_I3C_DIRECT_CCC_READ     = 18,

} cmd_opcode;


void bus_iface_process_ibi(client_ctxt *c_ctxt)
{
}

void bus_iface_write_to_fifo (uint8 *se_base, transfer_ctxt *t_ctxt)
{
    i2c_descriptor *dc = t_ctxt->desc + t_ctxt->transfer_count;
    uint32 transferred = t_ctxt->transferred;
    uint8 *buffer = dc->buffer + transferred;
    uint32 length = dc->length;
    uint32 word = 0, i = 0, j = 0;
    uint32 tx_watermark = HWIO_INXF(GENI_DATA_BASE(se_base), GENI_TX_WATERMARK_REG, TX_WATERMARK);
    uint32 tx_fifo_depth = HWIO_INXF(GENI_SE_DMA_BASE(se_base), SE_HW_PARAM_0, TX_FIFO_DEPTH);
    uint32 bytes_to_write = (tx_fifo_depth << 2) - (tx_watermark << 2);
    
    if(transferred == 0)
    {
        if(dc->flags & SMBUS_FLAG_CMD)
        {
            word = dc->cmd;
            i++;
            bytes_to_write--;
        }
        if(dc->flags & SMBUS_FLAG_LEN)
        {
            word = word | (length << 8);
            i++;
            bytes_to_write--;
        }
    }

    if ((length - transferred) < bytes_to_write)
    {
        bytes_to_write = length - transferred;
        // if all data will be written, then disable watermark
        HWIO_OUTX(GENI_DATA_BASE(se_base), GENI_TX_WATERMARK_REG,
            FLD_SET(GENI_TX_WATERMARK_REG, TX_WATERMARK, 0));
    }

    for (; j < bytes_to_write; i++,j++)
    {
        if (i && ((i & 0x3) == 0))
        {
            HWIO_OUTXI(GENI_DATA_BASE(se_base), GENI_TX_FIFOn, 0, word);
            word = 0;
        }
        word = word | (buffer[j] << ((i & 0x3) << 3));
    }
     HWIO_OUTXI(GENI_DATA_BASE(se_base), GENI_TX_FIFOn, 0, word);
    t_ctxt->transferred += bytes_to_write;
}

void bus_iface_read_from_fifo (uint8 *se_base, transfer_ctxt *t_ctxt)
{
    uint32 rx_fifo_status = HWIO_INX(GENI_DATA_BASE(se_base), GENI_RX_FIFO_STATUS);
    uint8  bytes_in_last_word = 0;
    uint32 bytes_to_read = FLD_GET(rx_fifo_status, GENI_RX_FIFO_STATUS, RX_FIFO_WC) << 2;
    uint32 transferred = t_ctxt->transferred;
    i2c_descriptor *dc = t_ctxt->desc + t_ctxt->transfer_count;
    uint8 *buffer = dc->buffer + transferred;
    uint32 length = dc->length;
    uint32 word = 0, i = 0, j = 0;

    if (FLD_GET(rx_fifo_status, GENI_RX_FIFO_STATUS, RX_LAST))
    {
        bytes_in_last_word = FLD_GET(rx_fifo_status, GENI_RX_FIFO_STATUS, RX_LAST_BYTE_VALID);
        bytes_to_read = (bytes_to_read - 4) + bytes_in_last_word;
    }

    if(transferred == 0)
    {
        if(dc->flags & SMBUS_FLAG_LEN)
        {
            word = HWIO_INXI(GENI_DATA_BASE(se_base), GENI_RX_FIFOn, 0);
            t_ctxt->read_count_from_slave = word & 0xFF;
            i++;
            bytes_to_read--;
        }
    }

    if ((length - transferred) < bytes_to_read)
    {
        bytes_to_read = length - transferred;
    }


    for (; j < bytes_to_read; i++,j++)
    {
        if ((i & 0x3) == 0)
        {
            word = HWIO_INXI(GENI_DATA_BASE(se_base), GENI_RX_FIFOn, 0);
        }	
        buffer[j] = (word >> ((i & 0x3) << 3)) & 0xFF;
    }
    t_ctxt->transferred += bytes_to_read;	
}

uint32 bus_iface_get_bytes_transferred (transfer_ctxt *t_ctxt)
{
    uint32 i, transferred = 0;
    i2c_descriptor *dc = t_ctxt->desc;
    
    if(t_ctxt->transfer_count == 0)
    {
        return 0;
    }
    
    for (i = 0; i < (t_ctxt->transfer_count - 1); i++)
    {
        transferred += dc->length;
        dc++;
    }

    return (transferred + t_ctxt->transferred);
}

plat_clock_config *bus_iface_get_clock_config (plat_device_config *dcfg, uint32 bus_frequency_khz)
{
    uint8 i = 0;
    plat_clock_config *clk_cfg = dcfg->clock_config;

    while (clk_cfg[i].bus_speed_khz != 0)
    {
        if (clk_cfg[i].bus_speed_khz == bus_frequency_khz) { break; }
        i++;
    }

    if (clk_cfg[i].bus_speed_khz == bus_frequency_khz)
    {
        return (clk_cfg + i);
    }

    return NULL;
}

cmd_opcode bus_iface_get_opcode (uint32 t_flags, uint32 length, i2c_mode mode)
{
    switch (mode)
    {
        case SMBUS: 
        case I2C: 
            if (length == 0)
            {
                if ((t_flags & I2C_FLAG_START) == I2C_FLAG_START)
                {
                    return CMD_I2C_ADDRESS_ONLY;
                }
                else if ((t_flags & I2C_FLAG_STOP) == I2C_FLAG_STOP)
                {
                    return CMD_I2C_STOP_ON_BUS;
                }
                else if (t_flags == 0)
                {
                    return CMD_I2C_BUS_CLEAR;
                }
            }
            else
            {
                if (t_flags & I2C_FLAG_WRITE) { return CMD_I2C_WRITE; }
                if (t_flags & I2C_FLAG_READ ) { return CMD_I2C_READ; }
            }
            break;

        case I3C_SDR:
            if (t_flags & I2C_FLAG_WRITE) { return CMD_I3C_PRIVATE_WRITE; }
            if (t_flags & I2C_FLAG_READ ) { return CMD_I3C_PRIVATE_READ; }
            break;

        case I3C_HDR_DDR:
            if (t_flags & I2C_FLAG_WRITE) { return CMD_I3C_HDR_DDR_WRITE; }
            if (t_flags & I2C_FLAG_READ ) { return CMD_I3C_HDR_DDR_READ; }
            break;

        case I3C_BROADCAST_CCC:
            return CMD_I3C_BROADCAST_CCC_WRITE;
            break;

        case I3C_DIRECT_CCC:
            if (t_flags & I2C_FLAG_WRITE) { return CMD_I3C_DIRECT_CCC_WRITE; }
            if (t_flags & I2C_FLAG_READ ) { return CMD_I3C_DIRECT_CCC_READ; }
            break;

        case I3C_IBI_READ:
            return CMD_I3C_READ_IBI;
            break;

        default:
            return CMD_INVALID;
    }

    return 0;
}

void bus_iface_config (uint8 *se_base, boolean in_i2c_mode, plat_clock_config *clk_cfg)
{
    // dfs index
    HWIO_OUTX(GENI_CFG_BASE(se_base), GENI_CLK_SEL,
            FLD_SET(GENI_CLK_SEL, CLK_SEL, 0));

    // packing
    HWIO_OUTX(GENI_IMAGE_REGS_BASE(se_base), GENI_TX_PACKING_CFG0, TX_PACKING_CFG0_VAL);
    HWIO_OUTX(GENI_IMAGE_REGS_BASE(se_base), GENI_TX_PACKING_CFG1, TX_PACKING_CFG1_VAL);
    HWIO_OUTX(GENI_IMAGE_REGS_BASE(se_base), GENI_RX_PACKING_CFG0, RX_PACKING_CFG0_VAL);
    HWIO_OUTX(GENI_IMAGE_REGS_BASE(se_base), GENI_RX_PACKING_CFG1, RX_PACKING_CFG1_VAL);

    // clk divider
    HWIO_OUTX(GENI_CFG_BASE(se_base), GENI_SER_M_CLK_CFG,
            FLD_SET(GENI_SER_M_CLK_CFG, CLK_DIV_VALUE,   clk_cfg->clk_div) |
            FLD_SET(GENI_SER_M_CLK_CFG, SER_CLK_EN,      1));

    // scl waveform conditioning
    if (in_i2c_mode)
    {
        HWIO_OUTX(GENI_IMAGE_REGS_BASE(se_base), I2C_SCL_COUNTERS,
                FLD_SET(I2C_SCL_COUNTERS, I2C_SCL_HIGH_COUNTER,  clk_cfg->t_high) |
                FLD_SET(I2C_SCL_COUNTERS, I2C_SCL_LOW_COUNTER,   clk_cfg->t_low)  |
                FLD_SET(I2C_SCL_COUNTERS, I2C_SCL_CYCLE_COUNTER, clk_cfg->t_cycle));
    }
    else
    {
        HWIO_OUTX(GENI_IMAGE_REGS_BASE(se_base), I3C_SCL_LOW,
                FLD_SET(I3C_SCL_LOW, I3C_SCL_LOW_COUNTER, clk_cfg->t_low));
    }
}

i2c_status bus_iface_transfer (client_ctxt *c_ctxt)
{
    hw_ctxt             *h_ctxt;
    //bus_iface_hw_ctxt   *g_ctxt;
    transfer_ctxt       *t_ctxt;
    plat_device_config  *dcfg;
    plat_clock_config   *clk_cfg;
    i2c_descriptor      *dc;
    uint8               *se_base;
    uint32              length_temp;
    uint32              params = 0;
    cmd_opcode          opcode = CMD_INVALID;
    boolean             in_i2c_mode = TRUE;

    if ((c_ctxt         == NULL) ||
        (c_ctxt->h_ctxt == NULL))
    {
        return I2C_ERROR_INVALID_PARAMETER;
    }

    h_ctxt = c_ctxt->h_ctxt;
    //g_ctxt = h_ctxt->core_iface;
    t_ctxt = &c_ctxt->t_ctxt;
    dcfg   = (plat_device_config *) h_ctxt->core_config;
    dc     = t_ctxt->desc + t_ctxt->transfer_count;

    if ((dcfg           == NULL) ||
        (t_ctxt         == NULL) ||
        (t_ctxt->config == NULL) ||
        (dc             == NULL))
    {
        return I2C_ERROR_INVALID_PARAMETER;
    }

    t_ctxt->transferred = 0;
    t_ctxt->read_count_from_slave = 0;
	
    clk_cfg = bus_iface_get_clock_config (dcfg, t_ctxt->config->bus_frequency_khz);
    if (clk_cfg == NULL)
    {
        return I2C_ERROR_PLATFORM_GET_CLOCK_CONFIG_FAIL;
    }

    se_base = dcfg->core_base_addr + dcfg->core_offset;
    in_i2c_mode = ((t_ctxt->config->mode == I2C) || (t_ctxt->config->mode == SMBUS));

    bus_iface_config (se_base, in_i2c_mode, clk_cfg);
    
    opcode = bus_iface_get_opcode (dc->flags, dc->length, t_ctxt->config->mode);
    if (opcode == CMD_INVALID)
    {
        return I2C_ERROR_INVALID_CMD_OPCODE;
    }

    if (dc->flags & I2C_FLAG_READ)
    {

        if (in_i2c_mode)
        {
            length_temp = dc->length;
            if(dc->flags & SMBUS_FLAG_LEN)
            {
                length_temp++;
            }
            HWIO_OUTX(GENI_IMAGE_REGS_BASE(se_base), I2C_RX_TRANS_LEN, length_temp);
        }
        else
        {
            HWIO_OUTX(GENI_IMAGE_REGS_BASE(se_base), I3C_RX_TRANS_LEN, dc->length);
        }

        if ((t_ctxt->transfer_count < (t_ctxt->num_descs - 1)) &&
            (!(dc->flags & I2C_FLAG_STOP)))
        {
            i2c_descriptor *dc_next = dc + 1;
            if ((dc_next->flags & I2C_FLAG_READ) &&
               !(dc_next->flags & I2C_FLAG_START))
            {
                params = params | M_CMD_FLAG_SET(READ_FINISH_WITH_ACK, 1);
            }
        }
    }
    else if (dc->flags & I2C_FLAG_WRITE)
    {
        if (in_i2c_mode)
        {
            length_temp = dc->length;
            if(dc->flags & SMBUS_FLAG_CMD)
            {
                length_temp++;
            }
            if(dc->flags & SMBUS_FLAG_LEN)
            {
                length_temp++;
            }
            HWIO_OUTX(GENI_IMAGE_REGS_BASE(se_base), I2C_TX_TRANS_LEN, length_temp);
        }
        else
        {
            HWIO_OUTX(GENI_IMAGE_REGS_BASE(se_base), I3C_TX_TRANS_LEN, dc->length);
        }
    }

    params = params | M_CMD_FLAG_SET(SLAVE_ADDRESS,t_ctxt->config->slave_address);

    if ((t_ctxt->delay) && (t_ctxt->transfer_count == 0))
    {
        uint32 delay = (t_ctxt->delay * clk_cfg->se_clock_frequency_khz) / 1000;
        if (in_i2c_mode)
        {
            HWIO_OUTX(GENI_IMAGE_REGS_BASE(se_base), I2C_DELAY_COUNTER, delay);
        }
        else
        {
            HWIO_OUTX(GENI_IMAGE_REGS_BASE(se_base), I3C_DELAY_COUNTER, delay);
        }
        params = params | M_CMD_FLAG_SET(PRE_CMD_DELAY, 1);
    }

    if (dc->flags & I2C_FLAG_TIMESTAMP)
    {
        if (dc->flags & I2C_FLAG_START)
        {
            params = params | M_CMD_FLAG_SET(TIMESTAMP_BEFORE, 1);
        }
        else if (dc->flags & I2C_FLAG_STOP)
        {
            params = params | M_CMD_FLAG_SET(TIMESTAMP_AFTER, 1);
        }
    }

    if (dc->length != 0)
    {
        if (!(dc->flags & I2C_FLAG_STOP))
        {
            params = params | M_CMD_FLAG_SET(STRETCH, 1);
        }

        if (!(dc->flags & I2C_FLAG_START))
        {
            params = params | M_CMD_FLAG_SET(BYPASS_ADDRESS_PHASE, 1);
        }
    }

    if (!in_i2c_mode)
    {
        HWIO_OUTX(GENI_IMAGE_REGS_BASE(se_base), I3C_TRANS_CFG,
            FLD_SET(I3C_TRANS_CFG, I3C_USE_7E,        1) |
            FLD_SET(I3C_TRANS_CFG, I3C_IBI_NACK_CTRL, 0));
    }

    HWIO_OUTX(GENI_DATA_BASE(se_base), GENI_M_CMD0,
            FLD_SET(GENI_M_CMD0, OPCODE, opcode) |
            FLD_SET(GENI_M_CMD0, PARAM,  params));

    t_ctxt->transfer_state = TRANSFER_IN_PROGRESS;

    if (opcode == CMD_I2C_WRITE)
    {
        HWIO_OUTX(GENI_DATA_BASE(se_base), GENI_TX_WATERMARK_REG,
            FLD_SET(GENI_TX_WATERMARK_REG, TX_WATERMARK, 1));
    }
    else if (opcode == CMD_I2C_READ)
    {
    /*    HWIO_OUTX(GENI_DATA_BASE(se_base), GENI_RX_WATERMARK_REG,
            FLD_SET(GENI_RX_WATERMARK_REG, RX_WATERMARK, g_ctxt->rx_fifo_depth - 2));  */
    }

    return I2C_SUCCESS;
}

void process_transfer_completion (hw_ctxt *h_ctxt, i2c_status i_status)
{
    client_ctxt *temp;
    transfer_ctxt *t_ctxt;
    plat_device_config *dcfg = (plat_device_config *) h_ctxt->core_config;

    do
    {
        plat_mutex_instance_lock (h_ctxt->queue_lock);
        // remove the client from the queue
        temp = h_ctxt->client_ctxt_head;
        h_ctxt->client_ctxt_head = temp->next;
        temp->next = NULL;

        // get transfer context
        t_ctxt = &(temp->t_ctxt);

        // store next client ctxt in temp
        temp = h_ctxt->client_ctxt_head;
        plat_mutex_instance_unlock (h_ctxt->queue_lock);

        t_ctxt->transfer_status = i_status;
        t_ctxt->transferred = bus_iface_get_bytes_transferred (t_ctxt);

        if (t_ctxt->callback != NULL)
        {
          /*
            // should be implemented in a qdi abstraction
            i2c_notify_completion(t_ctxt->callback,
                                  t_ctxt->transfer_status,
                                  t_ctxt->transferred,
                                  t_ctxt->ctxt);*/
        }
        else if (dcfg->polled_mode == FALSE)
        {
            // for synchronous calls
            plat_signal_event(t_ctxt->signal);
        }

        // check if more clients are queued
        if (temp != NULL)
        {
            i_status = bus_iface_transfer (temp);
            if (I2C_SUCCESS(i_status))
            {
                t_ctxt = &(temp->t_ctxt);
                t_ctxt->transfer_state = TRANSFER_IN_PROGRESS;
                break;
            }
        }
    }
    while (temp != NULL);
}

void bus_iface_isr (void *int_handle)
{
    hw_ctxt             *h_ctxt = (hw_ctxt *) int_handle;
    //bus_iface_hw_ctxt   *g_ctxt;
    client_ctxt         *c_ctxt = NULL;
    transfer_ctxt       *t_ctxt;
    i2c_status           i_status = I2C_SUCCESS;
    plat_device_config  *dcfg;
    i2c_descriptor      *dc;
    uint8               *se_base;
    uint32               irq_status = 0;
    uint32               gp_length = 0;

    if ((h_ctxt                     == NULL)    ||
        (h_ctxt->core_config        == NULL)    ||
        (h_ctxt->core_iface         == NULL))
    {
        return;
    }

    plat_mutex_instance_lock (h_ctxt->queue_lock);
    if (h_ctxt->client_ctxt_head != NULL)
    {
        c_ctxt = h_ctxt->client_ctxt_head;
    }
    plat_mutex_instance_unlock (h_ctxt->queue_lock);
    if (c_ctxt == NULL)
    {
        return;
    }

    //g_ctxt = h_ctxt->core_iface;
    t_ctxt = &c_ctxt->t_ctxt;
    dc = t_ctxt->desc + t_ctxt->transfer_count;
    dcfg = (plat_device_config *) h_ctxt->core_config;
    se_base = dcfg->core_base_addr + dcfg->core_offset;

    irq_status = HWIO_INX(GENI_DATA_BASE(se_base), GENI_M_IRQ_STATUS);
    gp_length  = HWIO_INX(GENI_DATA_BASE(se_base), GENI_M_GP_LENGTH); //No.of bytes that are transferred 
	
    if( ePlatformType == DALPLATFORMINFO_TYPE_RUMI )
    {
	  /* WA for wrong data getting read for first time on RUMI Platform */
      irq_status = HWIO_INX(GENI_DATA_BASE(se_base), GENI_M_IRQ_STATUS);
	}
	if ((FLD_GET(irq_status, GENI_M_IRQ_STATUS, M_GP_IRQ_1)) && (gp_length!= 0))
    {
        i_status = I2C_ERROR_DATA_NACK;
    }
    else if (FLD_GET(irq_status, GENI_M_IRQ_STATUS, M_GP_IRQ_1))
    {
        i_status = I2C_ERROR_ADDR_NACK;
    }
    else if (FLD_GET(irq_status, GENI_M_IRQ_STATUS, M_GP_IRQ_3))
    {
        i_status = I2C_ERROR_START_STOP_UNEXPECTED;
    }
    else if (FLD_GET(irq_status, GENI_M_IRQ_STATUS, M_GP_IRQ_4))
    {
        i_status = I2C_ERROR_ARBITRATION_LOST;
    }
    else if (FLD_GET(irq_status, GENI_M_IRQ_STATUS, RX_FIFO_RD_ERR))
    {
        i_status = I2C_ERROR_INPUT_FIFO_UNDER_RUN;
    }
    else if (FLD_GET(irq_status, GENI_M_IRQ_STATUS, RX_FIFO_WR_ERR))
    {
        i_status = I2C_ERROR_INPUT_FIFO_OVER_RUN;
    }
    else if (FLD_GET(irq_status, GENI_M_IRQ_STATUS, TX_FIFO_RD_ERR))
    {
        i_status = I2C_ERROR_OUTPUT_FIFO_UNDER_RUN;
    }
    else if (FLD_GET(irq_status, GENI_M_IRQ_STATUS, TX_FIFO_WR_ERR))
    {
        i_status = I2C_ERROR_OUTPUT_FIFO_OVER_RUN;
    }
    else if (FLD_GET(irq_status, GENI_M_IRQ_STATUS, M_CMD_OVERRUN))
    {
        i_status = I2C_ERROR_COMMAND_OVER_RUN;
    }
    else if ((FLD_GET(irq_status, GENI_M_IRQ_STATUS, M_CMD_CANCEL)) ||
             (FLD_GET(irq_status, GENI_M_IRQ_STATUS, M_CMD_ABORT)))
    {
        i_status = I2C_TRANSFER_FORCE_TERMINATED;
    }
    else if (FLD_GET(irq_status, GENI_M_IRQ_STATUS, M_ILLEGAL_CMD))
    {
        i_status = I2C_ERROR_COMMAND_ILLEGAL;
    }
    else if (FLD_GET(irq_status, GENI_M_IRQ_STATUS, M_GP_SYNC_IRQ_0))
    {
        bus_iface_process_ibi(c_ctxt);
    }

    if (i_status != I2C_SUCCESS)
    {
        HWIO_OUTX(GENI_DATA_BASE(se_base), GENI_TX_WATERMARK_REG,
            FLD_SET(GENI_TX_WATERMARK_REG, TX_WATERMARK, 0));
        t_ctxt->transfer_state = TRANSFER_CANCELED;
        t_ctxt->transfer_status = i_status;
        irq_status = HWIO_INX(GENI_DATA_BASE(se_base), GENI_M_IRQ_STATUS);
        goto exit;
    }

    if (FLD_GET(irq_status, GENI_M_IRQ_STATUS, M_TIMESTAMP))
    {
        t_ctxt->start_bit_timestamp = HWIO_INX(GENI_DATA_BASE(se_base), GENI_TIMESTAMP);
        t_ctxt->stop_bit_timestamp  = t_ctxt->start_bit_timestamp;
    }

    if (FLD_GET(irq_status, GENI_M_IRQ_STATUS, M_CMD_DONE))
    {
        t_ctxt->transfer_state = TRANSFER_DONE;
        if (dc->flags & I2C_FLAG_READ)
        {
            bus_iface_read_from_fifo (se_base, t_ctxt);
        }
        if(t_ctxt->read_count_from_slave)
        {
            if(t_ctxt->read_count_from_slave != t_ctxt->transferred)
            {
                i_status = I2C_ERROR_SMBUS_INCORRECT_LENGTH_READ;
            }
        }
    }
    else if (FLD_GET(irq_status, GENI_M_IRQ_STATUS, RX_FIFO_WATERMARK))
    {
        bus_iface_read_from_fifo (se_base, t_ctxt);
    }
    else if (FLD_GET(irq_status, GENI_M_IRQ_STATUS, TX_FIFO_WATERMARK))
    {
        bus_iface_write_to_fifo (se_base, t_ctxt);
    }

exit:
    HWIO_OUTX(GENI_DATA_BASE(se_base), GENI_M_IRQ_CLEAR, irq_status);

    if (t_ctxt->transfer_state == TRANSFER_DONE)
    {
        t_ctxt->transfer_count++;
        if (I2C_SUCCESS(i_status) &&
           (t_ctxt->transfer_count < t_ctxt->num_descs))
        {
            i_status = bus_iface_transfer (c_ctxt);
            // if this call returned an error, then the transfer_state is still
            // TRANSFER_DONE in which case the below condition will hit and the
            // process_transfer_completion will complete this transfer. do not
            // check the i_status here.
        }
    }

    //
    // DO NOT CLUB THIS WITH ABOVE CONDITION
    // bus_iface_transfer called above may change transfer_state
    // 
    if ((t_ctxt->transfer_state == TRANSFER_DONE) ||
        (t_ctxt->transfer_state == TRANSFER_TIMED_OUT))
    {
        process_transfer_completion (h_ctxt, i_status);
    }
}
static i2c_status i2c_handle_cancel_sequence(uint8 *se_base , i2c_status i_status)
{
	uint32 retry_count = 50;
    
	HWIO_OUTX(GENI_DATA_BASE(se_base), GENI_M_CMD_CTRL_REG, FLD_SET(GENI_M_CMD_CTRL_REG, M_GENI_CMD_CANCEL, 1));
	while((FLD_GET(HWIO_INX(GENI_DATA_BASE(se_base), GENI_M_IRQ_STATUS), GENI_M_IRQ_STATUS, M_CMD_CANCEL) != 1) && retry_count != 0)
	{
		plat_delay_us(100); //delay is in us
		retry_count--;
	}
	if(retry_count == 0)
	{
		//since cancel transfer timed out do abort as per HPG
		retry_count = 50;
		HWIO_OUTX(GENI_DATA_BASE(se_base), GENI_M_CMD_CTRL_REG, FLD_SET(GENI_M_CMD_CTRL_REG, M_GENI_CMD_ABORT, 1));
		while((FLD_GET(HWIO_INX(GENI_DATA_BASE(se_base), GENI_M_IRQ_STATUS), GENI_M_IRQ_STATUS, M_CMD_ABORT ) != 1) && retry_count != 0)
	    {
		   plat_delay_us(100); //delay is in us
		   retry_count--;
	    }
		if(retry_count == 0)
		{
			i_status = I2C_TRANSFER_FORCE_TERMINATED;
		}
		HWIO_OUTX(GENI_CFG_BASE(se_base), GENI_FORCE_DEFAULT_REG, FLD_SET(GENI_FORCE_DEFAULT_REG, FORCE_DEFAULT, 1));
	}
	return i_status;
}

i2c_status bus_iface_init (hw_ctxt *h_ctxt)
{
    plat_device_config *dcfg = NULL;
    bus_iface_hw_ctxt *g_ctxt;
    uint8 *se_base;

	if ((h_ctxt == NULL) || (h_ctxt->core_config == NULL))
    {
        return I2C_ERROR_INVALID_PARAMETER;
    }

	dcfg = (plat_device_config *) h_ctxt->core_config;

    g_ctxt = (bus_iface_hw_ctxt *) plat_mem_alloc (dcfg->core_index,
                                                   sizeof(bus_iface_hw_ctxt),
                                                   CORE_IFACE_TYPE);
    if (g_ctxt == NULL)
    {
        return I2C_ERROR_INVALID_PARAMETER;
    }

    h_ctxt->core_iface = g_ctxt;


    se_base = dcfg->core_base_addr + dcfg->core_offset;

//    HWIO_OUTX(dcfg->common_base_addr, QUPV3_SE_AHB_M_CFG,
//    FLD_SET(QUPV3_SE_AHB_M_CFG, AHB_M_CLK_CGC_ON,       1));

	if(I2C_SUCCESS != i2c_fw_load(dcfg))
	{
      return I2C_ERROR_FW_LOAD_FALIURE;
	}
		  
    // diable for RUMI
    // HWIO_OUTX(GENI_CFG_BASE(se_base), GENI_DFS_IF_CFG,
    //         FLD_SET(GENI_DFS_IF_CFG, NUM_WAIT_STATES, 0) |
    //         FLD_SET(GENI_DFS_IF_CFG, DFS_IF_EN,       1));

 /*   HWIO_OUTX(dcfg->common_base_addr, QUPV3_SE_AHB_M_CFG,
            FLD_SET(QUPV3_SE_AHB_M_CFG, AHB_M_CLK_CGC_ON,       1));

    HWIO_OUTX(GENI_IMAGE_REGS_BASE(se_base), GENI_DMA_MODE_EN,
            FLD_SET(GENI_DMA_MODE_EN, GENI_DMA_MODE_EN, 0));

    HWIO_OUTX(GENI_SE_DMA_BASE(se_base), DMA_GENERAL_CFG,
            FLD_SET(DMA_GENERAL_CFG, AHB_SEC_SLV_CLK_CGC_ON, 1) |
            FLD_SET(DMA_GENERAL_CFG, DMA_AHB_SLV_CLK_CGC_ON, 1) |
            FLD_SET(DMA_GENERAL_CFG, DMA_TX_CLK_CGC_ON,      1) |
            FLD_SET(DMA_GENERAL_CFG, DMA_RX_CLK_CGC_ON,      1));

    HWIO_OUTX(GENI_CFG_BASE(se_base), GENI_CGC_CTRL,
            FLD_SET(GENI_CGC_CTRL, EXT_CLK_CGC_ON,           1) |
            FLD_SET(GENI_CGC_CTRL, RX_CLK_CGC_ON,            1) |
            FLD_SET(GENI_CGC_CTRL, TX_CLK_CGC_ON,            1) |
            FLD_SET(GENI_CGC_CTRL, SCLK_CGC_ON,              1) |
            FLD_SET(GENI_CGC_CTRL, DATA_AHB_CLK_CGC_ON,      1) |
            FLD_SET(GENI_CGC_CTRL, CFG_AHB_WR_CLK_CGC_ON,    1) |
            FLD_SET(GENI_CGC_CTRL, CFG_AHB_CLK_CGC_ON,       1));*/
    if(!dcfg->i2c_hub)
    {
        g_ctxt->tx_fifo_depth = HWIO_INXF(GENI_SE_DMA_BASE(se_base), SE_HW_PARAM_0, TX_FIFO_DEPTH);
        g_ctxt->rx_fifo_depth = HWIO_INXF(GENI_SE_DMA_BASE(se_base), SE_HW_PARAM_1, RX_FIFO_DEPTH);
    }
    else
    {
        g_ctxt->tx_fifo_depth = 16;
        g_ctxt->rx_fifo_depth = 16;
    }

    HWIO_OUTX(GENI_DATA_BASE(se_base), GENI_RX_RFR_WATERMARK_REG,
            FLD_SET(GENI_RX_RFR_WATERMARK_REG, RX_RFR_WATERMARK, (g_ctxt->rx_fifo_depth - 2)));
    HWIO_OUTX(GENI_DATA_BASE(se_base), GENI_RX_WATERMARK_REG,
            FLD_SET(GENI_RX_WATERMARK_REG, RX_WATERMARK, 
                   ((HWIO_INXF(GENI_DATA_BASE(se_base), GENI_RX_RFR_WATERMARK_REG, RX_RFR_WATERMARK)) - 1)));

  /*  HWIO_OUTX(GENI_CFG_BASE(se_base), GENI_FORCE_DEFAULT_REG,
            FLD_SET(GENI_FORCE_DEFAULT_REG, FORCE_DEFAULT, 1));

    HWIO_OUTX(GENI_CFG_BASE(se_base), GENI_OUTPUT_CTRL,
            FLD_SET(GENI_OUTPUT_CTRL, IO_OUTPUT_CTRL, 0x7f));

    HWIO_OUTX(GENI_IMAGE_REGS_BASE(se_base), GENI_DMA_MODE_EN,
            FLD_SET(GENI_DMA_MODE_EN, GENI_DMA_MODE_EN, 0)); */
    if(!dcfg->i2c_hub)
    {
        /* For FIFO Polled mode*/
        HWIO_OUTX(GENI_SE_DMA_BASE(se_base), SE_IRQ_EN,
                FLD_SET(SE_IRQ_EN, DMA_RX_IRQ_EN, 0) |
                FLD_SET(SE_IRQ_EN, DMA_TX_IRQ_EN, 0) |
                FLD_SET(SE_IRQ_EN, GENI_M_IRQ_EN, 0) |
                FLD_SET(SE_IRQ_EN, GENI_S_IRQ_EN, 0));

        HWIO_OUTX(GENI_SE_DMA_BASE(se_base), SE_GSI_EVENT_EN,
                FLD_SET(SE_GSI_EVENT_EN, DMA_RX_EVENT_EN, 0) |
                FLD_SET(SE_GSI_EVENT_EN, DMA_TX_EVENT_EN, 0) |
                FLD_SET(SE_GSI_EVENT_EN, GENI_M_EVENT_EN, 0) |
                FLD_SET(SE_GSI_EVENT_EN, GENI_S_EVENT_EN, 0));

    }
    
    if(!dcfg->polled_mode)
    {
        HWIO_OUTX(GENI_DATA_BASE(se_base), GENI_M_IRQ_ENABLE,
                FLD_SET(GENI_M_IRQ_ENABLE, M_CMD_OVERRUN_EN,     1) |
                FLD_SET(GENI_M_IRQ_ENABLE, M_ILLEGAL_CMD_EN,     1) |
                FLD_SET(GENI_M_IRQ_ENABLE, M_CMD_FAILURE_EN,     1) |
                FLD_SET(GENI_M_IRQ_ENABLE, M_CMD_CANCEL_EN,      1) |
                FLD_SET(GENI_M_IRQ_ENABLE, M_CMD_ABORT_EN,       1) |
                FLD_SET(GENI_M_IRQ_ENABLE, M_TIMESTAMP_EN,       1) |
                FLD_SET(GENI_M_IRQ_ENABLE, IO_DATA_ASSERT_EN,    1) |
                FLD_SET(GENI_M_IRQ_ENABLE, IO_DATA_DEASSERT_EN,  1) |
                FLD_SET(GENI_M_IRQ_ENABLE, RX_FIFO_RD_ERR_EN,    1) |
                FLD_SET(GENI_M_IRQ_ENABLE, RX_FIFO_WR_ERR_EN,    1) |
                FLD_SET(GENI_M_IRQ_ENABLE, TX_FIFO_RD_ERR_EN,    1) |
                FLD_SET(GENI_M_IRQ_ENABLE, TX_FIFO_WR_ERR_EN,    1));

        HWIO_OUTX(GENI_DATA_BASE(se_base), GENI_S_IRQ_ENABLE,
                FLD_SET(GENI_S_IRQ_ENABLE, S_CMD_OVERRUN_EN,     1) |
                FLD_SET(GENI_S_IRQ_ENABLE, S_ILLEGAL_CMD_EN,     1) |
                FLD_SET(GENI_S_IRQ_ENABLE, S_CMD_CANCEL_EN,      1) |
                FLD_SET(GENI_S_IRQ_ENABLE, S_CMD_ABORT_EN,       1) |
                FLD_SET(GENI_S_IRQ_ENABLE, S_GP_IRQ_0_EN,        1) |
                FLD_SET(GENI_S_IRQ_ENABLE, S_GP_IRQ_1_EN,        1) |
                FLD_SET(GENI_S_IRQ_ENABLE, S_GP_IRQ_2_EN,        1) |
                FLD_SET(GENI_S_IRQ_ENABLE, S_GP_IRQ_3_EN,        1) |
                FLD_SET(GENI_S_IRQ_ENABLE, RX_FIFO_WR_ERR_EN,    1) |
                FLD_SET(GENI_S_IRQ_ENABLE, RX_FIFO_RD_ERR_EN,    1));

        HWIO_OUTX(GENI_DATA_BASE(se_base), GENI_M_IRQ_ENABLE,
                HWIO_INX(GENI_DATA_BASE(se_base), GENI_M_IRQ_ENABLE)                |
                FLD_SET(GENI_M_IRQ_ENABLE, RX_FIFO_WATERMARK_EN, 1) |
                FLD_SET(GENI_M_IRQ_ENABLE, TX_FIFO_WATERMARK_EN, 1) |
                FLD_SET(GENI_M_IRQ_ENABLE, RX_FIFO_LAST_EN,      1) |
                FLD_SET(GENI_M_IRQ_ENABLE, M_CMD_DONE_EN,        1) |
                FLD_SET(GENI_M_IRQ_ENABLE, SEC_IRQ_EN,           1));

        HWIO_OUTX(GENI_DATA_BASE(se_base), GENI_S_IRQ_ENABLE,
                HWIO_INX(GENI_DATA_BASE(se_base), GENI_S_IRQ_ENABLE)                |
                FLD_SET(GENI_S_IRQ_ENABLE, S_CMD_DONE_EN, 1));
    }
    return I2C_SUCCESS;
}

i2c_status bus_iface_de_init (hw_ctxt *h_ctxt)
{
    if (h_ctxt->core_iface != NULL)
    {
        plat_mem_free (h_ctxt->core_iface, sizeof(bus_iface_hw_ctxt), CORE_IFACE_TYPE);
    }

    return I2C_SUCCESS;
}

i2c_status bus_iface_queue_transfer (client_ctxt *c_ctxt)
{
    hw_ctxt             *h_ctxt  = c_ctxt->h_ctxt;
    transfer_ctxt       *t_ctxt  = &c_ctxt->t_ctxt;
    plat_device_config  *dcfg    = NULL;
    i2c_status          i_status = I2C_SUCCESS;
    uint8               *se_base = NULL;
    uint32              irq_status;

    if ((h_ctxt == NULL) || (t_ctxt->config == NULL))
    {
        return I2C_ERROR_INVALID_PARAMETER;
    }
    
    dcfg    = (plat_device_config *) h_ctxt->core_config;
    se_base = dcfg->core_base_addr + dcfg->core_offset;

    if(bus_is_geni_ios_proper(c_ctxt))
    {
        if(h_ctxt->pending_xfer)
        {
            h_ctxt->pending_xfer = FALSE;
            i_status = i2c_handle_cancel_sequence(se_base, i_status);
            irq_status = HWIO_INX(GENI_DATA_BASE(se_base), GENI_M_IRQ_STATUS);
            HWIO_OUTX(GENI_DATA_BASE(se_base), GENI_M_IRQ_CLEAR, irq_status);
        }

        i_status = bus_iface_transfer (c_ctxt);
    }
    else
    {
        i_status = I2C_TRANSFER_FORCE_TERMINATED;
        process_transfer_completion(h_ctxt, i_status);
        return i_status;
    }

    // polled mode logic
    if (I2C_SUCCESS(i_status) && dcfg->polled_mode)
    {
        uint32 timeout_us = POLL_TIME_DEFAULT_US;
        while ((t_ctxt->transfer_state != TRANSFER_DONE) && (timeout_us != 0))
        {
            bus_iface_isr (h_ctxt);
            if(t_ctxt->transfer_state == TRANSFER_CANCELED)
            {
                break;
            }
            plat_delay_us (POLL_INTERVAL_US);
            timeout_us -= POLL_INTERVAL_US;
        }

        if (((timeout_us == 0) && (t_ctxt->transfer_state != TRANSFER_DONE))||(t_ctxt->transfer_state == TRANSFER_CANCELED))
        {
            i_status = t_ctxt->transfer_status;

            if(!dcfg->i2c_hub || (dcfg->i2c_hub && (bus_is_geni_ios_proper(c_ctxt))))
            {
                i_status = i2c_handle_cancel_sequence(se_base, i_status);
                irq_status = HWIO_INX(GENI_DATA_BASE(se_base), GENI_M_IRQ_STATUS);
                HWIO_OUTX(GENI_DATA_BASE(se_base), GENI_M_IRQ_CLEAR, irq_status);
                t_ctxt->transfer_count++;
            }
            else if(dcfg->i2c_hub && !(bus_is_geni_ios_proper(c_ctxt)))
            {
                h_ctxt->pending_xfer = TRUE;
            }
            if(t_ctxt->transfer_state != TRANSFER_CANCELED) //no error is returned by GENI, transfer got stuck
            {
            t_ctxt->transfer_state = TRANSFER_TIMED_OUT;
                i_status = I2C_ERROR_TRANSFER_TIMEOUT;
            }
            process_transfer_completion (h_ctxt, i_status);
        }
        else
        {
            i_status = t_ctxt->transfer_status;
        }

    }

    return i_status;
}

boolean bus_iface_has_queueing(hw_ctxt *h_ctxt)
{
    return TRUE;

}

boolean bus_iface_has_interrupt_consumer(hw_ctxt *h_ctxt)
{
    return FALSE;
}

boolean bus_is_geni_ios_proper(client_ctxt *c_ctxt)
{
    hw_ctxt             *h_ctxt  = c_ctxt->h_ctxt;
    transfer_ctxt       *t_ctxt  = &c_ctxt->t_ctxt;
    plat_device_config  *dcfg    = NULL;
    volatile uint32     geni_ios = 0;
    uint8               *se_base = NULL;

    if ((h_ctxt == NULL) || (t_ctxt->config == NULL))
    {
        return I2C_ERROR_INVALID_PARAMETER;
    }
    dcfg    = (plat_device_config *) h_ctxt->core_config;

    se_base = dcfg->core_base_addr + dcfg->core_offset;

    geni_ios = HWIO_INX(GENI_DATA_BASE(se_base) , GENI_IOS);

    //check if GENI IOS lines are high
    if(FLD_GET(geni_ios, GENI_IOS, RX_DATA_IN) &&
       FLD_GET(geni_ios, GENI_IOS, IO2_DATA_IN))
    {
        return TRUE;
    }
    I2C_LOG(LEVEL_ERROR, "[I2C] IOS lines not high 0x%08x\n", geni_ios);
    return FALSE;
}
