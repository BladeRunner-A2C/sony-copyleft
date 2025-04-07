/*=======================================================================*//**
 * @file        UsbRetimer.c
 * @author:     pohanw
 * @date        09-Sep-2021
 *
 * @brief       USB common & shared USB core implementation for retimer Library.
 *
 * @details     This file contains sequence to enable retimer.
 *
 * @note        
 *
 * 
*//*========================================================================*/
//============================================================================
/**
  Copyright (c) 2021-2022 Qualcomm Technologies, Inc. All rights reserved.
  Portions Copyright (c) 2007 - 2013 Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php
  
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 */
//============================================================================

// ===========================================================================
// 
//                            EDIT HISTORY FOR FILE
//   This section contains comments describing changes made to the module.
//   Notice that changes are listed in reverse chronological order.
// 
// 
// when          who     what, where, why
// ----------   -----    ----------------------------------------------------------
// 12/20/22     pohanw   update ps8830 retimer sequence
// 05/28/21     jaychoi  Update retimer sequence
// 04/30/21     jaychoi  Added support for B1 retimer
// 12/10/20     pohanw   Initial revision
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "HalusbHWIO.h"
#include "DDITlmm.h"
#include "DALSys.h"   // Required for DALSYS_InitMod for TLMM
#include "UsbSharedLib.h"

#include <Uefi.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include "DDIPlatformInfo.h"
#include "UsbRetimer.h"
#include "UsbSharedLibTargetConfig.h"

usb_retimer_ctx_type usb_retimer_ctx[USB_MAX_NUM_CORE];

#if USB_KB8001_RETIMER_FLAG

#define USB_I2C_KB8001_FREQUENCY_KHZ                    (400)
#define USB_I2C_KB8001_MAX_CLOCK_STRETCH_US             (500)

// SMB1355 mounted on I2C instance 021, but since SBL sequence start from 1, 
// so here it is 022 instead 021
#define USB_I2C_KB8001_PRI_INSTANCE             (I2C_INSTANCE_004)
#define USB_I2C_KB8001_PRI_SLAVE_ADDRESS        (0x08)
#define USB_I2C_KB8001_SEC_INSTANCE             (I2C_INSTANCE_008)
#define USB_I2C_KB8001_SEC_SLAVE_ADDRESS        (0x08)
#define USB_I2C_KB8001_TRI_INSTANCE             (I2C_INSTANCE_002)
#define USB_I2C_KB8001_TRI_SLAVE_ADDRESS        (0x08)

// Delay must be greater than or equal to 100us between PWR ON, RESET, and first i2c write
#define USB_KB8001_RETIMER_DELAY_US__USB1_PWR_TO_RESET  (200)

// USB1_PWR_3P3_EN
// HWIO_TLMM_GPIO_CFG27_OUT(0x201);
// HWIO_TLMM_GPIO_IN_OUT27_OUT(0x2);
#define USB_KB8001_RETIMER_GPIO__USB1_PWR_3P3_EN        (27)

// USB1_RESET_N
// HWIO_TLMM_GPIO_CFG26_OUT(0x201);
// HWIO_TLMM_GPIO_IN_OUT26_OUT(0x2);
#define USB_KB8001_RETIMER_GPIO__USB1_RESET_N           (26)

// Delay must be greater than or equal to 100us between PWR ON, RESET, and first i2c write
#define USB_SHARED_RETIMER_DELAY_US__USB1_PWR_TO_RESET  (200)


static const usb_booster_cfg_type KB8001_RESET_CFG[] = 
{
  //in V1 the reset value change to 0x0, but to keep compa with V0 chip, write 0xD within 100 ms of releasing RESETN 
  { 0x0006,  (0x0F) }, // Mcx_reset 
  { 0x0006,  (0x0D) }, // Enable TWI
  
  { 0x5058, 0x12 },
  { 0x5059, 0x12 },
  { 0xFF63, 0x3C },
  { 0xF021, 0x02 },
  { 0xF022, 0x02 },
  { 0xF057, 0x02 },
  { 0xF058, 0x02 },
  { 0x8194, 0x37 },
  { 0xF0C9, 0x0C },
  { 0xF0CA, 0x0B },
  { 0xF0CB, 0x0A },
  { 0xF0CC, 0x09 },
  { 0xF0CD, 0x08 },
  { 0xF0CE, 0x07 },
  { 0xF0DF, 0x57 },
  { 0xF0E0, 0x66 },
  { 0xF0E1, 0x66 },
  { 0x8198, 0x33 },
  { 0x8191, 0x00 },
};

//KB8001 must be programmed to operate in USB3 mode at this time. Register settings for
//USB-C normal and flipped orientation are shown below:
static const usb_booster_cfg_type KB8001_USB3_LANEA_CFG[] = 
{
  { 0xF020, 0x2f },
  { 0xF056, 0x2f },
  //Normal orientation
  { 0x0006,  (0x00) }, // mcx_reset 
};

static const usb_booster_cfg_type KB8001_USB3_LANEB_CFG[] = 
{
  { 0xF020, 0x2f },
  { 0xF056, 0x2f },

  { 0x0002,  (0x01) }, // mcx_orientation
  { 0x0006,  (0x00) }, // mcx_reset 
};


//KB8001 must be programmed to operate in DisplayPort mode after a DisplayPort Configure
//Acknowledge message is received by the host. Register settings for USB-C normal and
//flipped orientation are shown below:
static const usb_booster_cfg_type KB8001_USB3DP_LANEA_CFG[] = 
{
  { 0xF2CB, 0x30 },
  { 0x0011, 0x00 },

  { 0x0001,  (0x01) }, // mcx_protocol
  { 0xF020, 0x2f },
  { 0xF056, 0x2f },

  { 0x0002,  (0x06) }, // mcx_orientation
  { 0x0006,  (0x00) }, // mcx_reset 
};

static const usb_booster_cfg_type KB8001_USB3DP_LANEB_CFG[] = 
{
  { 0xF2CB, 0x30 },
  { 0x0011, 0x00 },

  { 0x0001,  (0x01) }, // mcx_protocol
  { 0xF020, 0x2f },
  { 0xF056, 0x2f },

  { 0x0002,  (0x07) }, // mcx_orientation
  { 0x0006,  (0x00) }, // mcx_reset 
};

//KB8001 must be programmed to operate in DisplayPort mode after a DisplayPort Configure
//Acknowledge message is received by the host. Register settings for USB-C normal and
//flipped orientation are shown below:
static const usb_booster_cfg_type KB8001_DP4LN_LANEB_CFG[] = 
{
  { 0xF2CB, 0x30 },
  { 0x0011, 0x00 },

  { 0x0001,  (0x02) }, // mcx_protocol
  { 0x0002,  (0x07) }, // mcx_orientation
  { 0x0006,  (0x00) }, // mcx_reset 
};

static const usb_booster_cfg_type KB8001_DP4LN_LANEA_CFG[] = 
{
  { 0xF2CB, 0x30 },
  { 0x0011, 0x00 },

  { 0x0001,  (0x02) }, // mcx_protocol
  { 0x0002,  (0x06) }, // mcx_orientation
  { 0x0006,  (0x00) }, // mcx_reset 
};


//KB8001 must be programmed to operate in Thunderbolt mode after the Thunderbolt Enter
//Mode Acknowledge message is received by the host. Register settings for USB-C normal and
//flipped orientation are shown below:
static const usb_booster_cfg_type KB8001_TBT3_LANEA_CFG[] = 
{
  { 0xF26B, 0x01 },
  { 0xF26E, 0x19 },

  { 0x0001,  (0x03) }, // mcx_protocol
  { 0x0006,  (0x00) }, // mcx_reset 
};

static const usb_booster_cfg_type KB8001_TBT3_LANEB_CFG[] = 
{
  { 0xF26B, 0x01 },
  { 0xF26E, 0x19 },

  { 0x0001,  (0x03) }, // mcx_protocol
  { 0x0002,  (0x01) }, // mcx_orientation
  { 0x0005,  (0x02) }, // mcx_map_ctl 
  { 0x0006,  (0x00) }, // mcx_reset 
};

//KB8001 must be programmed to operate in Thunderbolt mode after the Thunderbolt Enter
//Mode Acknowledge message is received by the host. Register settings for USB-C normal and
//flipped orientation are shown below:
static const usb_booster_cfg_type KB8001_USB4_LANEA_CFG[] = 
{
  { 0xF26B, 0x01 },
  { 0xF26E, 0x19 },
  { 0x0001, 0x03 },

  { 0x0006,  (0x00) }, // mcx_reset 
};

static const usb_booster_cfg_type KB8001_USB4_LANEB_CFG[] = 
{
  { 0xF26B, 0x01 },
  { 0xF26E, 0x19 },
  { 0x0001, 0x03 },

  { 0x0002,  (0x01) }, // mcx_orientation
  { 0x0005,  (0x02) }, // mcx_map_ctl 
  { 0x0006,  (0x00) }, // mcx_reset 
};


static const uint32 kb8001_reset_cfg_size   = (sizeof(KB8001_RESET_CFG)       /sizeof(usb_booster_cfg_type));
static const uint32 kb8001_usb3_cfg_size    = (sizeof(KB8001_USB3_LANEA_CFG)  /sizeof(usb_booster_cfg_type));
static const uint32 kb8001_usb3dp_cfg_size  = (sizeof(KB8001_USB3DP_LANEA_CFG)/sizeof(usb_booster_cfg_type));
static const uint32 kb8001_dp4lane_cfg_size = (sizeof(KB8001_DP4LN_LANEA_CFG) /sizeof(usb_booster_cfg_type));
static const uint32 kb8001_tbt3_cfg_size    = (sizeof(KB8001_TBT3_LANEA_CFG)  /sizeof(usb_booster_cfg_type));
static const uint32 kb8001_usb4_cfg_size    = (sizeof(KB8001_USB4_LANEA_CFG)  /sizeof(usb_booster_cfg_type));
#endif

#if USB_PS8330_RETIMER_FLAG

#define USB_I2C_PS8830_FREQUENCY_KHZ                    (100)
#define USB_I2C_PS8830_MAX_CLOCK_STRETCH_US             (500)

// SMB1355 mounted on I2C instance 021, but since SBL sequence start from 1, 
// so here it is 022 instead 021
#define USB_I2C_PS8830_PRI_INSTANCE                     (I2C_INSTANCE_004)
#define USB_I2C_PS8830_PRI_SLAVE_ADDRESS        (0x08)
#define USB_I2C_PS8830_SEC_INSTANCE                     (I2C_INSTANCE_008)
#define USB_I2C_PS8830_SEC_SLAVE_ADDRESS        (0x08)
#define USB_I2C_PS8830_TER_INSTANCE                     (I2C_INSTANCE_002)
#define USB_I2C_PS8830_TER_SLAVE_ADDRESS        (0x08)

// USB1_PWR_3P3_EN
// HWIO_TLMM_GPIO_CFG34_OUT(0x201);
// HWIO_TLMM_GPIO_IN_OUT34_OUT(0x2);
#define USB_PS8830_RETIMER_GPIO__USB1_PWR_3P3_EN        (186)

// USB1_PWR_1P1_EN
// HWIO_TLMM_GPIO_CFG111_OUT(0x201);
// HWIO_TLMM_GPIO_IN_OUT111_OUT(0x2);
#define USB_PS8830_RETIMER_GPIO__USB1_PWR_1P1_EN        (188)

// USB1_PWR_1P8_EN
// HWIO_TLMM_GPIO_CFG175_OUT(0x201);
// HWIO_TLMM_GPIO_IN_OUT175_OUT(0x2);
#define USB_PS8830_RETIMER_GPIO__USB1_PWR_1P8_EN        (175)

// USB1_RESET_N
// HWIO_TLMM_GPIO_CFG26_OUT(0x201);
// HWIO_TLMM_GPIO_IN_OUT26_OUT(0x2);
#define USB_PS8830_RETIMER_GPIO__USB1_RESET_N           (176)

// USB1_PWR_3P3_EN
// HWIO_TLMM_GPIO_CFG34_OUT(0x201);
// HWIO_TLMM_GPIO_IN_OUT34_OUT(0x2);
#define USB_PS8830_RETIMER_GPIO__USB2_PWR_3P3_EN        (187)

// USB1_PWR_1P1_EN
// HWIO_TLMM_GPIO_CFG111_OUT(0x201);
// HWIO_TLMM_GPIO_IN_OUT111_OUT(0x2);
#define USB_PS8830_RETIMER_GPIO__USB2_PWR_1P1_EN        (126)

// USB1_PWR_1P8_EN
// HWIO_TLMM_GPIO_CFG175_OUT(0x201);
// HWIO_TLMM_GPIO_IN_OUT175_OUT(0x2);
#define USB_PS8830_RETIMER_GPIO__USB2_PWR_1P8_EN        (189)

// USB1_RESET_N
// HWIO_TLMM_GPIO_CFG26_OUT(0x201);
// HWIO_TLMM_GPIO_IN_OUT26_OUT(0x2);
#define USB_PS8830_RETIMER_GPIO__USB2_RESET_N           (185)



// Delay must be greater than or equal to 100us between PWR ON, RESET, and first i2c write
#define USB_PS8830_RETIMER_DELAY_US  (20000)

/* Safe Mode */
static const usb_booster_cfg_type PS8830_RESET_CFG[] =
{
  { 0x00, 0x01 },
  { 0x01, 0x00 },
  { 0x02, 0x00 },
};

static const usb_booster_cfg_type PS8830_USB3_LANEA_CFG[] =
{
  { 0x00, 0x21 },
  { 0x01, 0x00 },
  { 0x02, 0x00 },
};

static const usb_booster_cfg_type PS8830_USB3_LANEB_CFG[] =
{
  { 0x00, 0x23 },
  { 0x01, 0x00 },
  { 0x02, 0x00 },
};


static const usb_booster_cfg_type PS8830_USB3DP_LANEA_CFG[] =
{
  { 0x00, 0x21 },
  { 0x01, 0x85 },
  { 0x02, 0x00 },
};

static const usb_booster_cfg_type PS8830_USB3DP_LANEB_CFG[] =
{
  { 0x00, 0x23 },
  { 0x01, 0x85 },
  { 0x02, 0x00 },
};

static const usb_booster_cfg_type PS8830_DP4LN_LANEA_CFG[] =
{
  { 0x00, 0x01 },
  { 0x01, 0x85 },
  { 0x02, 0x00 },
};

static const usb_booster_cfg_type PS8830_DP4LN_LANEB_CFG[] =
{
  { 0x00, 0x03 },
  { 0x01, 0x85 },
  { 0x02, 0x00 },
};


static const usb_booster_cfg_type PS8830_TBT3_LANEA_CFG[] =
{
  { 0x00, 0x01 },
  { 0x01, 0x00 },
  { 0x02, 0x01 },
};

static const usb_booster_cfg_type PS8830_TBT3_LANEB_CFG[] =
{
  { 0x00, 0x03 },
  { 0x01, 0x00 },
  { 0x02, 0x01 },
};

static const usb_booster_cfg_type PS8830_USB4_LANEA_CFG[] =
{
  { 0x00, 0x01 },
  { 0x01, 0x00 },
  { 0x02, 0x80 },
};

static const usb_booster_cfg_type PS8830_USB4_LANEB_CFG[] =
{
  { 0x00, 0x03 },
  { 0x01, 0x00 },
  { 0x02, 0x80 },
};
// ----- PS8830

#define QUSB_I2C_CFG_ENTRY_CNT(cfg) (sizeof(cfg)/sizeof(usb_booster_cfg_type))

#endif  /* USB_PS8830_RETIMER_FLAG */

#if USB_KB8001_RETIMER_FLAG

//============================================================================

/**
* @function usb_shared_kb8001_ctx_init
*
* @brief  API used to initialize the KB8001 I2C Ctx
*
*/
//============================================================================
void usb_kb8001_ctx_init(uint8 core_num)
{
#if 0
  usb_retimer_ctx[core_num].i2c_ctx.handle = NULL;
  usb_retimer_ctx[core_num].i2c_ctx.instance = USB_I2C_KB8001_INSTANCE;

  usb_retimer_ctx[core_num].i2c_ctx.config.bus_frequency_khz = USB_I2C_KB8001_FREQUENCY_KHZ;
  usb_retimer_ctx[core_num].i2c_ctx.config.slave_max_clock_stretch_us = USB_I2C_KB8001_MAX_CLOCK_STRETCH_US;
  usb_retimer_ctx[core_num].i2c_ctx.config.mode = I2C;
  usb_retimer_ctx[core_num].i2c_ctx.config.core_configuration1 = 0;
  usb_retimer_ctx[core_num].i2c_ctx.config.core_configuration2 = 0;

  switch (core_num)
  {
    case USB_RETIMER_CORE_0:
      usb_retimer_ctx[core_num].i2c_ctx.config.slave_address = USB_I2C_KB8001_PRI_SLAVE_ADDRESS;  
      break;
    case USB_RETIMER_CORE_1:
      usb_retimer_ctx[core_num].i2c_ctx.config.slave_address = USB_I2C_KB8001_SEC_SLAVE_ADDRESS;  
      break;
    default:
      usb_retimer_ctx[core_num].i2c_ctx.config.slave_address = USB_I2C_KB8001_PRI_SLAVE_ADDRESS;  
  }
#endif
}

boolean usb_kb8001_reset(uint8 core_num)
{
  return usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, KB8001_RESET_CFG,0,kb8001_reset_cfg_size, TRUE);
}

boolean usb_shared_kb8001_deinit(uint8 core_num)
{
  if (core_num >= USB_MAX_NUM_CORE)
  {
    usb_shared_uart_log_error("usb_shared_kb8001_deinit, wrong input parameter:", core_num);
    return FALSE;
  }
  if (usb_retimer_ctx[core_num].i2c_ctx.handle != NULL)
  {
    if(usb_shared_i2c_close(&usb_retimer_ctx[core_num].i2c_ctx))
    {
      usb_retimer_ctx[core_num].i2c_ctx.handle = NULL;
    }
    else
    {
      usb_shared_uart_log_error("usb_shared_kb8001_deinit, failed close:", core_num);    
      return FALSE;
    }
  }
  return TRUE;
}

boolean usb_shared_kb8001_init(uint8 core_num, USB4_MODE_TYPE usb_mode, uint32 cc_lane)
{
  boolean result = FALSE;
  uint32 slave_address = USB_I2C_KB8001_PRI_SLAVE_ADDRESS;
  uint32 i2c_instance  = USB_I2C_KB8001_PRI_INSTANCE;
  if ((core_num >= USB_MAX_NUM_CORE) || (usb_mode >=USB4_MODE_TYPE_MAX) || (cc_lane >= USB_TYPE_C_NO_LANE))
  {
    usb_shared_uart_log_error("usb_shared_kb8001_init, wrong input parameter:", usb_mode);
    return FALSE;
  }

  if (usb_retimer_ctx[core_num].i2c_ctx.handle != NULL)
  {
    usb_shared_uart_log_error("usb_shared_kb8001_init, already open:", core_num);  
  }

  if (cc_lane == 0)
  {
    usb_shared_uart_log_error("usb_shared_kb8001_init, LANE_A: core: ", core_num );
  }
  else
  {
    usb_shared_uart_log_error("usb_shared_kb8001_init, LANE_B: core: ", core_num );
  }
  
  if (core_num == 1)
  {
    usb_shared_uart_log_error("usb_shared_kb8001_init, enable GPIO core:", core_num);  
    slave_address = USB_I2C_KB8001_SEC_SLAVE_ADDRESS;
    i2c_instance  = USB_I2C_KB8001_SEC_INSTANCE;
    

    usb_shared_tlmm_gpio_high(USB_KB8001_RETIMER_GPIO__USB1_PWR_3P3_EN);

    usb_shared_delay_us(USB_KB8001_RETIMER_DELAY_US__USB1_PWR_TO_RESET);
    
    usb_shared_tlmm_gpio_high(USB_KB8001_RETIMER_GPIO__USB1_RESET_N);

    usb_shared_delay_us(USB_KB8001_RETIMER_DELAY_US__USB1_PWR_TO_RESET);

  }

  result = usb_shared_i2c_open(&usb_retimer_ctx[core_num].i2c_ctx, i2c_instance, slave_address);
  if((FALSE == result) || (usb_retimer_ctx[core_num].i2c_ctx.handle == NULL))
  {
    usb_shared_uart_log_error("usb_shared_kb8001_init, Failed open:", result);  
    return FALSE;
  }
  result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, KB8001_RESET_CFG,0,kb8001_reset_cfg_size,TRUE);
  usb_shared_uart_log_error("KB8001_RESET_CFG", result);
  if (FALSE == result)
  {
    return FALSE;
  }

  if (usb_shared_is_retimer_force_dp4lane_enabled())
  {
    usb_shared_uart_log_error("usb_shared_kb8001_init, force DP4LANE", cc_lane);  
    usb_mode = USB4_MODE_TYPE_DP4LANE;
  }

  if (cc_lane == USB_TYPE_C_LANE_B)
  {
    switch (usb_mode)
    {
      case USB4_MODE_TYPE_USB3:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, KB8001_USB3_LANEB_CFG,0,kb8001_usb3_cfg_size,TRUE);
        usb_shared_uart_log_error("KB8001_USB3_LANEB_CFG", result);
        break;
      case USB4_MODE_TYPE_USB3DP:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, KB8001_USB3DP_LANEB_CFG,0,kb8001_usb3dp_cfg_size,TRUE);
        usb_shared_uart_log_error("KB8001_USB3DP_LANEB_CFG", result);
        break;
      case USB4_MODE_TYPE_DP4LANE:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, KB8001_DP4LN_LANEB_CFG,0,kb8001_dp4lane_cfg_size,TRUE);
        usb_shared_uart_log_error("KB8001_DP4LN_LANEB_CFG", result);
        break;
      case USB4_MODE_TYPE_TBT3:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, KB8001_TBT3_LANEB_CFG,0,kb8001_tbt3_cfg_size,TRUE);
        usb_shared_uart_log_error("KB8001_TBT3_LANEB_CFG", result);
        break;
      case USB4_MODE_TYPE_USB4:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, KB8001_USB4_LANEB_CFG,0,kb8001_usb4_cfg_size,TRUE);
        usb_shared_uart_log_error("KB8001_USB4_LANEB_CFG", result);
        break;
      default:
        usb_shared_uart_log_error("usb_shared_kb8001_init, wrong usb_mode:", usb_mode);  
        result = FALSE;
    }
  }
  else
  {
    switch (usb_mode)
    {
      case USB4_MODE_TYPE_USB3:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, KB8001_USB3_LANEA_CFG,0,kb8001_usb3_cfg_size,TRUE);
        usb_shared_uart_log_error("KB8001_USB3_LANEA_CFG", result);
        break;
      case USB4_MODE_TYPE_USB3DP:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, KB8001_USB3DP_LANEA_CFG,0,kb8001_usb3dp_cfg_size,TRUE);
        usb_shared_uart_log_error("KB8001_USB3DP_LANEA_CFG", result);
        break;
      case USB4_MODE_TYPE_DP4LANE:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, KB8001_DP4LN_LANEA_CFG,0,kb8001_dp4lane_cfg_size,TRUE);
        usb_shared_uart_log_error("KB8001_DP4LN_LANEA_CFG", result);
        break;
      case USB4_MODE_TYPE_TBT3:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, KB8001_TBT3_LANEA_CFG,0,kb8001_tbt3_cfg_size,TRUE);
        usb_shared_uart_log_error("KB8001_TBT3_LANEA_CFG", result);
        break;
      case USB4_MODE_TYPE_USB4:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, KB8001_USB4_LANEA_CFG,0,kb8001_usb4_cfg_size,TRUE);
        usb_shared_uart_log_error("KB8001_USB4_LANEA_CFG", result);
        break;
      default:
        usb_shared_uart_log_error("usb_shared_kb8001_init, wrong usb_mode:", usb_mode);  
        result = FALSE;
    }
  }
  
  return result;
}

#endif /* USB_KB8001_RETIMER_FLAG */


#if USB_PS8330_RETIMER_FLAG
boolean usb_shared_PS8830_fw_dump (uint8 core_num)
{
  uint8 value;
  boolean result;
  uint8 base_slave_address =  usb_retimer_ctx[core_num].i2c_ctx.config.slave_address;
  usb_retimer_ctx[core_num].i2c_ctx.config.slave_address = base_slave_address +1;
  result = usb_shared_i2c_read(&usb_retimer_ctx[core_num].i2c_ctx, 0xFF, &value, 0x1);
  result = usb_shared_i2c_read(&usb_retimer_ctx[core_num].i2c_ctx, 0xFE, &value, 0x1);
  
  usb_retimer_ctx[core_num].i2c_ctx.config.slave_address = base_slave_address +9;

  result = usb_shared_i2c_read(&usb_retimer_ctx[core_num].i2c_ctx, 0x01, &value, 0x1);
  result = usb_shared_i2c_read(&usb_retimer_ctx[core_num].i2c_ctx, 0x02, &value, 0x1);
  result = usb_shared_i2c_read(&usb_retimer_ctx[core_num].i2c_ctx, 0x03, &value, 0x1);
  result = usb_shared_i2c_read(&usb_retimer_ctx[core_num].i2c_ctx, 0x04, &value, 0x1);

  usb_retimer_ctx[core_num].i2c_ctx.config.slave_address = base_slave_address;
  return result;

}


boolean usb_shared_PS8830_mode_dump(uint8 core_num)
{
  uint8 value;
  boolean result;

  result = usb_shared_i2c_read(&usb_retimer_ctx[core_num].i2c_ctx, 0x00, &value, 0x1);
  result = usb_shared_i2c_read(&usb_retimer_ctx[core_num].i2c_ctx, 0x01, &value, 0x1);
  result = usb_shared_i2c_read(&usb_retimer_ctx[core_num].i2c_ctx, 0x02, &value, 0x1);
  return result;
}


//============================================================================

/**
* @function usb_shared_ps8830_ctx_init
*
* @brief  API used to initialize the PS8830 I2C Ctx
*
*/
//============================================================================
void usb_ps8830_ctx_init(uint8 core_num)
{
#if 0
  usb_retimer_ctx[core_num].i2c_ctx.handle = NULL;
  usb_retimer_ctx[core_num].i2c_ctx.instance = USB_I2C_PS8830_INSTANCE;

  usb_retimer_ctx[core_num].i2c_ctx.config.bus_frequency_khz = USB_I2C_PS8830_FREQUENCY_KHZ;
  usb_retimer_ctx[core_num].i2c_ctx.config.slave_max_clock_stretch_us = USB_I2C_PS8830_MAX_CLOCK_STRETCH_US;
  usb_retimer_ctx[core_num].i2c_ctx.config.mode = I2C;
  usb_retimer_ctx[core_num].i2c_ctx.config.core_configuration1 = 0;
  usb_retimer_ctx[core_num].i2c_ctx.config.core_configuration2 = 0;

  switch (core_num)
  {
    case USB_RETIMER_CORE_0:
      usb_retimer_ctx[core_num].i2c_ctx.config.slave_address = USB_I2C_PS8830_PRI_SLAVE_ADDRESS;  
      break;
    case USB_RETIMER_CORE_1:
      usb_retimer_ctx[core_num].i2c_ctx.config.slave_address = USB_I2C_PS8830_SEC_SLAVE_ADDRESS;  
      break;
    default:
      usb_retimer_ctx[core_num].i2c_ctx.config.slave_address = USB_I2C_PS8830_PRI_SLAVE_ADDRESS;  
  }
#endif  
}


boolean usb_ps8830_reset(uint8 core_num)
{
  return usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, PS8830_RESET_CFG,0,QUSB_I2C_CFG_ENTRY_CNT(PS8830_RESET_CFG),TRUE);
}

boolean usb_shared_ps8830_deinit(uint8 core_num)
{
  i2c_status i2c_sts = I2C_SUCCESS;
  if (core_num >= USB_MAX_NUM_CORE)
  {
    usb_shared_uart_log_error("usb_shared_ps8830_deinit, wrong input parameter:", core_num);
    return FALSE;
  }
  if (usb_retimer_ctx[core_num].i2c_ctx.handle != NULL)
  {
    i2c_sts = i2c_close(usb_retimer_ctx[core_num].i2c_ctx.handle);
    if(I2C_SUCCESS == i2c_sts)
    {
      usb_retimer_ctx[core_num].i2c_ctx.handle = NULL;
    }
    else
    {
      usb_shared_uart_log_error("usb_shared_ps8830_deinit, failed close:", core_num);    
      return FALSE;
    }
  }
  return TRUE;
}
boolean usb_shared_ps8830_reg_dump(uint8 core_num, i2c_instance i2c_instance_core, uint32 address)
{
    boolean result = FALSE;
    uint8 value = 0;
    result = usb_shared_i2c_open(&usb_retimer_ctx[core_num].i2c_ctx, i2c_instance_core, address);
    if(result==FALSE)
      return FALSE;
    for (uint32 i=0;i<256;i++)
    {
      result = usb_shared_i2c_read(&usb_retimer_ctx[core_num].i2c_ctx, i, &value, 0x1);
    }
    result = usb_shared_i2c_close(&usb_retimer_ctx[core_num].i2c_ctx);
    return result;
}

boolean usb_shared_ps8830_init(uint8 core_num, USB4_MODE_TYPE usb_mode, uint32 cc_lane)
{
  i2c_status i2c_sts = I2C_SUCCESS;
  i2c_instance i2c_instance_core = USB_I2C_PS8830_PRI_INSTANCE;
  uint32 i2c_slave_addr = USB_I2C_PS8830_PRI_SLAVE_ADDRESS;
  boolean result = FALSE;
  if ((core_num >= USB_MAX_NUM_CORE) || (usb_mode >=USB4_MODE_TYPE_MAX) || (cc_lane >= USB_TYPE_C_NO_LANE))
  {
    usb_shared_uart_log_error("usb_shared_ps8830_init, wrong input parameter:", usb_mode);
    return FALSE;
  }

  if (cc_lane == 0)
  {
    usb_shared_uart_log_error("usb_shared_ps8830_init, LANE_A: core: ", core_num );
  }
  else
  {
    usb_shared_uart_log_error("usb_shared_ps8830_init, LANE_B: core: ", core_num );
  }
  
  if (usb_retimer_ctx[core_num].i2c_ctx.handle != NULL)
   {
     usb_shared_uart_log_error("usb_shared_ps8830_init, already open:", core_num);  
   }
   else
   {

     #if USB_SEC_FLAG
     // Add logic to configure PMIC GPIO for core 0?
     if (core_num == 1)
     {
       i2c_instance_core = USB_I2C_PS8830_SEC_INSTANCE;
       i2c_slave_addr = USB_I2C_PS8830_SEC_SLAVE_ADDRESS;
            
       usb_shared_uart_log_error("usb_shared_ps8830_init, enable GPIO core:", core_num);  
     
       usb_shared_tlmm_gpio_high(USB_PS8830_RETIMER_GPIO__USB1_PWR_3P3_EN);
     
       usb_shared_delay_us(USB_PS8830_RETIMER_DELAY_US);
     
       usb_shared_tlmm_gpio_high(USB_PS8830_RETIMER_GPIO__USB1_PWR_1P1_EN);
     
       usb_shared_delay_us(USB_PS8830_RETIMER_DELAY_US);
       
       usb_shared_tlmm_gpio_high(USB_PS8830_RETIMER_GPIO__USB1_PWR_1P8_EN);
     
       usb_shared_delay_us(USB_PS8830_RETIMER_DELAY_US);
       
       usb_shared_tlmm_gpio_high(USB_PS8830_RETIMER_GPIO__USB1_RESET_N);
     
       usb_shared_delay_us(USB_PS8830_RETIMER_DELAY_US*6);        
     }
#endif
#if USB_TER_FLAG
     else if (core_num == 2)
     {
       i2c_instance_core = USB_I2C_PS8830_TER_INSTANCE;
       i2c_slave_addr = USB_I2C_PS8830_TER_SLAVE_ADDRESS;
         
       usb_shared_uart_log_error("usb_shared_ps8830_init, enable GPIO core:", core_num);  
     
       usb_shared_tlmm_gpio_high(USB_PS8830_RETIMER_GPIO__USB2_PWR_3P3_EN);
     
       usb_shared_delay_us(USB_PS8830_RETIMER_DELAY_US);
     
       usb_shared_tlmm_gpio_high(USB_PS8830_RETIMER_GPIO__USB2_PWR_1P1_EN);
     
       usb_shared_delay_us(USB_PS8830_RETIMER_DELAY_US);
       
       usb_shared_tlmm_gpio_high(USB_PS8830_RETIMER_GPIO__USB2_PWR_1P8_EN);
     
       usb_shared_delay_us(USB_PS8830_RETIMER_DELAY_US);
       
       usb_shared_tlmm_gpio_high(USB_PS8830_RETIMER_GPIO__USB2_RESET_N);
     
       usb_shared_delay_us(USB_PS8830_RETIMER_DELAY_US*6);        
         
     }
#endif

     
     result = usb_shared_i2c_open(&usb_retimer_ctx[core_num].i2c_ctx, i2c_instance_core, i2c_slave_addr);
     if((I2C_SUCCESS != i2c_sts) || (usb_retimer_ctx[core_num].i2c_ctx.handle == NULL))
     {
       usb_shared_uart_log_error("usb_shared_ps8830_init, Failed open:", i2c_sts);  
       return FALSE;
     }
   }


  result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, PS8830_RESET_CFG,0,QUSB_I2C_CFG_ENTRY_CNT(PS8830_RESET_CFG),TRUE);
  usb_shared_PS8830_fw_dump( core_num );
  usb_shared_PS8830_mode_dump( core_num );

  usb_shared_uart_log_error("PS8830_RESET_CFG", result);
  if (FALSE == result)
  {
    return FALSE;
  }

  if (usb_shared_is_retimer_force_dp4lane_enabled())
  {
    usb_shared_uart_log_error("usb_shared_ps8830_init, force DP4LANE", cc_lane);  
    usb_mode = USB4_MODE_TYPE_DP4LANE;
  }

  if (cc_lane == USB_TYPE_C_LANE_B)
  {
    switch (usb_mode)
    {
      case USB4_MODE_TYPE_USB3:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, PS8830_USB3_LANEB_CFG,0,QUSB_I2C_CFG_ENTRY_CNT(PS8830_USB3_LANEB_CFG),TRUE);
        usb_shared_uart_log_error("PS8830_USB3_LANEB_CFG", result);
        break;
      case USB4_MODE_TYPE_USB3DP:
        
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, PS8830_USB3DP_LANEB_CFG,0,QUSB_I2C_CFG_ENTRY_CNT(PS8830_USB3DP_LANEB_CFG),TRUE);
        usb_shared_uart_log_error("PS8830_USB3DP_LANEB_CFG", result);
        break;
      case USB4_MODE_TYPE_DP4LANE:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, PS8830_DP4LN_LANEB_CFG,0,QUSB_I2C_CFG_ENTRY_CNT(PS8830_DP4LN_LANEB_CFG),TRUE);
        usb_shared_uart_log_error("PS8830_DP4LN_LANEB_CFG", result);
        break;
      case USB4_MODE_TYPE_TBT3:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, PS8830_TBT3_LANEB_CFG,0,QUSB_I2C_CFG_ENTRY_CNT(PS8830_TBT3_LANEB_CFG),TRUE);
        usb_shared_uart_log_error("PS8830_TBT3_LANEB_CFG", result);
        break;
      case USB4_MODE_TYPE_USB4:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, PS8830_USB4_LANEB_CFG,0,QUSB_I2C_CFG_ENTRY_CNT(PS8830_USB4_LANEB_CFG),TRUE);
        usb_shared_uart_log_error("PS8830_USB4_LANEB_CFG", result);
        break;
      default:
        usb_shared_uart_log_error("usb_shared_ps8830_init, wrong usb_mode:", usb_mode);  
        result = FALSE;
    }
  }
  else
  {
    switch (usb_mode)
    {
      case USB4_MODE_TYPE_USB3:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, PS8830_USB3_LANEA_CFG,0,QUSB_I2C_CFG_ENTRY_CNT(PS8830_USB3_LANEA_CFG),TRUE);
        usb_shared_uart_log_error("PS8830_USB3_LANEA_CFG", result);
        break;
      case USB4_MODE_TYPE_USB3DP:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, PS8830_USB3DP_LANEA_CFG,0,QUSB_I2C_CFG_ENTRY_CNT(PS8830_USB3DP_LANEA_CFG),TRUE);
        usb_shared_uart_log_error("PS8830_USB3DP_LANEA_CFG", result);
        break;
      case USB4_MODE_TYPE_DP4LANE:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, PS8830_DP4LN_LANEA_CFG,0,QUSB_I2C_CFG_ENTRY_CNT(PS8830_DP4LN_LANEA_CFG),TRUE);
        usb_shared_uart_log_error("PS8830_DP4LN_LANEA_CFG", result);
        break;
      case USB4_MODE_TYPE_TBT3:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, PS8830_TBT3_LANEA_CFG,0,QUSB_I2C_CFG_ENTRY_CNT(PS8830_TBT3_LANEA_CFG),TRUE);
        usb_shared_uart_log_error("PS8830_TBT3_LANEA_CFG", result);
        break;
      case USB4_MODE_TYPE_USB4:
        result = usb_shared_i2c_process_cfg_reg_array(&usb_retimer_ctx[core_num].i2c_ctx, PS8830_USB4_LANEA_CFG,0,QUSB_I2C_CFG_ENTRY_CNT(PS8830_USB4_LANEA_CFG),TRUE);
        usb_shared_uart_log_error("PS8830_USB4_LANEA_CFG", result);
        break;
      default:
        usb_shared_uart_log_error("usb_shared_ps8830_init, wrong usb_mode:", usb_mode);  
        result = FALSE;
    }
  }
  usb_shared_PS8830_mode_dump( core_num );
  return result;
}

#endif /* USB_PS8830_RETIMER_FLAG */

#if USB_KB8001_RETIMER_FLAG
boolean usb_retimer_support(uint32 core_num)
{
  usb_platform_ctx platform = usb_shared_get_platform();  
  
  //usb_shared_uart_log_error("retimerKB, platform", ((platform.platform << 0x100) | platform.subtype));
  if ( (platform.platform == DALPLATFORMINFO_TYPE_QRD) 
        && (platform.subtype  == USB_SHARED_PLATFORM_QRD_SUBTYPE__RETIMER) )
  {
    return TRUE;
  }
  return FALSE;
}

boolean usb_retimer_init(uint32 core_num, uint32 usb_mode, uint32* lane)
{
  boolean                           retimer_result   = TRUE;

  if ((core_num >= USB_MAX_NUM_CORE) || (usb_mode >=USB4_MODE_TYPE_MAX) || (lane >= USB_TYPE_C_NO_LANE))
  {
    usb_shared_uart_log_error("usb_retimer_init, wrong input parameter:", usb_mode);
    return FALSE;
  }
  if (usb_retimer_support(core_num))
  {
    retimer_result = usb_shared_kb8001_init(core_num, usb_mode, *lane);
    if (retimer_result == TRUE)
  {
      // if retimer program successful, overwrite CC_LANE to LaneA
      *lane = USB_TYPE_C_LANE_A;
    }
  }
  return retimer_result;
}
boolean usb_retimer_set_usb_mode(uint32 core_num, uint32 usb_mode, uint32* lane)
{
  return usb_retimer_init(core_num, usb_mode, lane);
}

#elif USB_PS8330_RETIMER_FLAG
boolean usb_retimer_support(uint32 core_num)
{
  usb_platform_ctx platform = usb_shared_get_platform();  
  
  // usb_shared_uart_log_error("retimerPS, platform", ((platform.platform * 10000) | platform.subtype));
  if (platform.platform == DALPLATFORMINFO_TYPE_CRD)
  {
    return TRUE;
  }
  return FALSE;
}

        
boolean usb_retimer_init(uint32 core_num, uint32 usb_mode, uint32* lane)
{
  boolean                           retimer_result   = TRUE;

  if ((core_num >= USB_MAX_NUM_CORE) || (usb_mode >=USB4_MODE_TYPE_MAX) || (*lane >= USB_TYPE_C_NO_LANE))
  {
    usb_shared_uart_log_error("usb_retimer_init, wrong input parameter:", usb_mode);
    return FALSE;
  }

  if (usb_retimer_support(core_num))
  {
    retimer_result = usb_shared_ps8830_init(core_num, usb_mode, *lane);
  }
  // this retimer does not require to over write the CC_LANE
  return retimer_result;
}
boolean usb_retimer_set_usb_mode(uint32 core_num, uint32 usb_mode, uint32* lane)
{
  return usb_retimer_init(core_num,usb_mode,lane);
}

#else
boolean usb_retimer_support(uint32 core_num)
{
  return TRUE;
}

boolean usb_retimer_init(uint32 core_num, uint32 usb_mode, uint32* lane)
{
  return TRUE;
}


boolean usb_retimer_set_usb_mode(uint32 core_num, uint32 usb_mode, uint32* lane)
{
  return TRUE;
}

#endif

