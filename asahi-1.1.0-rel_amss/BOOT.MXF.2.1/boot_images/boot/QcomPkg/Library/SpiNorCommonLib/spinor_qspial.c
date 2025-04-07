/**********************************************************************
 * spionor_qspial.c
 *
 * This file implements function to interface spinor driver with qspi buses driver
 *
 * Copyright (c) 2017-2020, 2022, 2023 Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 **********************************************************************/
/*=======================================================================
                        Edit History


when        who  what, where, why
----------  ---  ---------------------------------------------------
2023-03-31  sc   Remove redundant fields in the config_data.
2022-11-14  sc   Set chip_select according to slot_no
2020-07-23  wek  Use the same error codes on all SPI-NOR dirver files.
2020-04-08  wek  Add SFDP support.
2019-03-12  wek  Expose the SPI power state to upper layers.
2018-03-21  wek  Update cache management logic.
2017-05-25  md   Initial Release based on SPI-NOR driver from Quartz.


======================================================================*/
#include "spinor_utils.h"
#include "spinor_init_config.h"
#include "spinor_osal.h"
#include <api/systemdrivers/busywait.h>
#include "quadspi.h"
#include "spinor_core.h"
#include "spinor_spial.h"


static SPINOR_STATUS config_cmd_spi(spinor_handle_t handle, QSPI_CMD *qspi_config_cmd, SPI_COMMAND_TYPE cmd_mode, uint8_t opcode);

SPINOR_STATUS spial_init(spinor_handle_t handle, bool init_status, uint32 chip_select)
{
  SPINOR_STATUS status = SPINOR_DEVICE_DONE;
  QSPI_MASTER_CONFIG qspi_cfg;
  spinor_drv_info *spinor_dev = (spinor_drv_info*)handle;

  /* Zero inialize memory. */
  memset(&qspi_cfg, 0, sizeof(qspi_cfg));

  qspi_cfg.chip_select  = (uint8_t)chip_select;
  /* This setting is for SPI mode */
  qspi_cfg.clk_polarity = FALSE;
  qspi_cfg.clk_phase    = FALSE;

  /* The QSPI frequency is controlled by the spinor driver via clock APIs */
  /* This clk_freq field is not used by the QSPI buses driver */
  if (init_status == FALSE)
  {
    qspi_cfg.clk_freq = 8000000;
  }
  else
  {
    qspi_cfg.clk_freq = spinor_dev->config_data->freq_khz * 1000;
  }
  (void) quadspi_init(&qspi_cfg);

  return status;
}


SPINOR_STATUS spial_deinit(spinor_handle_t handle)
{
  SPINOR_STATUS status = SPINOR_DEVICE_DONE;
  quadspi_deinit();
  return status;
}

SPINOR_STATUS spial_enter_working_state(void)
{
  /* We don't do power management yet at this stage of boot. */
  return SPINOR_DEVICE_DONE;
}

SPINOR_STATUS spial_enter_low_power_state(void)
{
  /* We don't do power management yet at this stage of boot. */
  return SPINOR_DEVICE_DONE;
}

SPINOR_STATUS spial_transfer(spinor_handle_t handle, SPI_COMMAND_TYPE cmd_mode, uint32_t addr, uint8 *reg_value, uint32 len,uint8_t opcode )
{
  SPINOR_STATUS status = SPINOR_DEVICE_DONE;
  boolean transfer_mode = FALSE;
  uint8 *temp_buffer;
  uint32 transfer_size = 0;
  QSPI_CMD qspi_cmd;
  spinor_drv_info *spinor_dev = (spinor_drv_info*)handle;

  temp_buffer = reg_value;
  transfer_size = len;
  uint32 address= addr;

  if (cmd_mode == qspi_read_mode || cmd_mode == qspi_write_mode ||cmd_mode == qspi_erase_mode || cmd_mode == qspi_erase_bulk_mode ||cmd_mode == qspi_write_enable_mode)
  {
    transfer_mode = spinor_dev->config_data->dma_enable; //QSPI_DMA_INT_MODE : QSPI_DMA_POLL_MODE;
  }

  memset (&qspi_cmd, 0, sizeof(QSPI_CMD));

  if (status != config_cmd_spi(handle, &qspi_cmd, cmd_mode, opcode))
  {
    status = SPINOR_DEVICE_FAIL;
    spinor_log (&spinor_dev->debug_log, 0x500);
    goto done;
  }

  if (spinor_dev->config_data->dma_enable == TRUE)
  {
    spinor_cache_op(temp_buffer, transfer_size, FLUSH);
  }

  if (!quadspi_cmd(&qspi_cmd, address, temp_buffer, transfer_size, transfer_mode))
  {
    status = SPINOR_DEVICE_FAIL;
    spinor_log (&spinor_dev->debug_log, 0x501);
  }

  if (spinor_dev->config_data->dma_enable == TRUE)
  {
    spinor_cache_op(temp_buffer, transfer_size, INVAL);
  }

done:

  return status;
}


SPINOR_STATUS config_cmd_spi(spinor_handle_t handle, QSPI_CMD *qspi_config_cmd, SPI_COMMAND_TYPE cmd_mode, uint8_t opcode)
{
  QSPI_CMD *qspi_cmd;
  qspi_cmd = qspi_config_cmd;
  SPINOR_STATUS status = SPINOR_DEVICE_DONE;
  spinor_drv_info *spinor_dev = (spinor_drv_info*)handle;

  if (cmd_mode == qspi_read_mode)
  {
    qspi_cmd->opcode       = spinor_dev->config_data->read_opcode;
    qspi_cmd->addr_bytes   = spinor_dev->config_data->addr_bytes;
    qspi_cmd->dummy_clocks = spinor_dev->config_data->read_wait_state;
    qspi_cmd->cmd_mode     = SDR_1BIT;
    qspi_cmd->addr_mode    = SDR_1BIT;
    qspi_cmd->data_mode    = SDR_1BIT;
    qspi_cmd->write        = false;

    switch (spinor_dev->config_data->read_mode)
    {
    case READ_SDR_1_1_1_MODE:
      break;                                   /* default settings */

    case READ_SDR_1_1_4_MODE:
      qspi_cmd->data_mode    = SDR_4BIT;
      break;

    case READ_SDR_1_4_4_MODE:
      qspi_cmd->addr_mode    = SDR_4BIT;
      qspi_cmd->data_mode    = SDR_4BIT;
      break;

    case READ_SDR_4_4_4_MODE:
      qspi_cmd->cmd_mode  = SDR_4BIT;
      qspi_cmd->addr_mode = SDR_4BIT;
      qspi_cmd->data_mode = SDR_4BIT;
      break;

    case READ_DDR_1_1_1_MODE:
    /* The mode isn't thoroughly tested. Reverting to READ_DDR_1_4_4_MODE */

    case READ_DDR_1_2_2_MODE:
    /* The mode isn't thoroughly tested. Reverting to READ_DDR_1_4_4_MODE */

    case READ_DDR_1_8_8_MODE:
    /* Octal SPI support isn't available. Reverting to READ_DDR_1_4_4_MODE */

    case READ_DDR_1_4_4_MODE:
      qspi_cmd->addr_mode    = DDR_4BIT;
      qspi_cmd->data_mode    = DDR_4BIT;
      qspi_cmd->opcode       = spinor_dev->config_data->read_opcode;
      qspi_cmd->dummy_clocks = spinor_dev->config_data->read_wait_state;
      break;

    default:
      status = SPINOR_DEVICE_FAIL;
      spinor_log (&spinor_dev->debug_log, 0x510);
      goto config_cmd_spi;
    }
  }
  else if (cmd_mode == qspi_write_mode)
  {
    qspi_cmd->opcode = spinor_dev->config_data->write_opcode;
    qspi_cmd->addr_bytes = spinor_dev->config_data->addr_bytes;
    qspi_cmd->dummy_clocks = 0;
    qspi_cmd->cmd_mode = SDR_1BIT;
    qspi_cmd->addr_mode = SDR_1BIT;
    qspi_cmd->data_mode = SDR_1BIT;
    qspi_cmd->write = true;

    switch (spinor_dev->config_data->write_mode)
    {
    case WRITE_SDR_1_1_1_MODE:
      break;								   /* default settings */

    case WRITE_SDR_1_1_4_MODE:
      qspi_cmd->data_mode = SDR_4BIT;
      break;

    case WRITE_SDR_1_1_8_MODE:
    /* Octal SPI support isn't available. Reverting to WRITE_SDR_1_4_4_MODE */    

    case WRITE_SDR_1_8_8_MODE:
    /* Octal SPI support isn't available. Reverting to WRITE_SDR_1_4_4_MODE */  
  
    case WRITE_SDR_1_4_4_MODE:
      qspi_cmd->addr_mode = SDR_4BIT;
      qspi_cmd->data_mode = SDR_4BIT;
      break;

    default:
      status = SPINOR_DEVICE_FAIL;
      spinor_log (&spinor_dev->debug_log, 0x511);
      goto config_cmd_spi;
    }
  }
  else if (cmd_mode == qspi_erase_mode)
  {
    qspi_cmd->opcode = spinor_dev->config_data->erase_4kb_opcode;
    qspi_cmd->addr_bytes = spinor_dev->config_data->addr_bytes;
    qspi_cmd->dummy_clocks = 0;
    qspi_cmd->cmd_mode = SDR_1BIT;
    qspi_cmd->addr_mode = SDR_1BIT;
    qspi_cmd->data_mode = SDR_1BIT;
    qspi_cmd->write = false;
  }
  else if (cmd_mode == qspi_erase_bulk_mode)
  {
    qspi_cmd->opcode = spinor_dev->config_data->bulk_erase_opcode;
    qspi_cmd->addr_bytes = spinor_dev->config_data->addr_bytes;
    qspi_cmd->dummy_clocks = 0;
    qspi_cmd->cmd_mode = SDR_1BIT;
    qspi_cmd->addr_mode = SDR_1BIT;
    qspi_cmd->data_mode = SDR_1BIT;
    qspi_cmd->write = false;
  }
  else if (cmd_mode == qspi_write_enable_mode)
  {
    /* WRITE_ENABLE_CMD 0x06*/
    qspi_cmd->opcode = WRITE_ENABLE_CMD;
    qspi_cmd->addr_bytes = 0;
    qspi_cmd->dummy_clocks = 0;
    qspi_cmd->cmd_mode = SDR_1BIT;
    qspi_cmd->addr_mode = SDR_1BIT;
    qspi_cmd->data_mode = SDR_1BIT;
    qspi_cmd->write = false;
  }
  else if (cmd_mode == qspi_register_write)
  {
    qspi_cmd->opcode = opcode;
    qspi_cmd->addr_bytes = 0;
    qspi_cmd->dummy_clocks = 0;
    qspi_cmd->cmd_mode = SDR_1BIT;
    qspi_cmd->addr_mode = SDR_1BIT;
    qspi_cmd->data_mode = SDR_1BIT;
    qspi_cmd->write = true;
  }
  else if (cmd_mode == qspi_register_read)
  {
    qspi_cmd->opcode = opcode;
    qspi_cmd->addr_bytes = 0;
    qspi_cmd->dummy_clocks = 0;
    qspi_cmd->cmd_mode = SDR_1BIT;
    qspi_cmd->addr_mode = SDR_1BIT;
    qspi_cmd->data_mode = SDR_1BIT;
    qspi_cmd->write = false;

  }
  else if (cmd_mode == qspi_read_sfdp_mode)
  {
    qspi_cmd->opcode = opcode;
    qspi_cmd->addr_bytes = 3;
    qspi_cmd->dummy_clocks = 8;
    qspi_cmd->cmd_mode = SDR_1BIT;
    qspi_cmd->addr_mode = SDR_1BIT;
    qspi_cmd->data_mode = SDR_1BIT;
    qspi_cmd->write = false;
  }

config_cmd_spi:
  return status;
}


