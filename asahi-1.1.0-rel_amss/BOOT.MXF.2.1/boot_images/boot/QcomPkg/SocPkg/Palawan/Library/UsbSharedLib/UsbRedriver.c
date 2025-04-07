/*=======================================================================*//**
 * @file        UsbRedriver.c
 * @author:     pohanw
 * @date        09-Sep-2021
 *
 * @brief       USB common & shared USB core implementation for redriver Library.
 *
 * @details     This file contains sequence to enable redriver.
 *
 * @note        
 *
 * 
*//*========================================================================*/
//============================================================================
/**
  Copyright (c) 2021,2023 Qualcomm Technologies, Inc. All rights reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
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
// 09/09/21     pohanw   Initial revision
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "HalusbHWIO.h"
#include "UsbSharedLib.h"
#include "UsbSharedLibTargetConfig.h"


#if USB_ONSEMI_REDRIVER_FLAG

#define USB_REDRIVER_I2C_INSTANCE_PRIMARY  (I2C_INSTANCE_001)
#define USB_REDRIVER_I2C_SLAVE_ADDRESS_PRIMARY (0x1C)

usb_redriver_ctx_type usb_redriver_ctx[USB_MAX_NUM_CORE];



#define ONSEMI_GENERAL_DEVICE_SETTING_REG 0x00
// 7   Channel D enable
// 6   Channel C Enable
// 5   Channel B Enable
// 4   Channel A Enable
// 3:1 operation modes:
//      101= Two ports of USB 3.2 Gen1/Gen2 (Default)
//           Channel A: USB 3.2 RX
//           Channel B: USB3.2 TX
//           Channel C: USB3.2 TX
//           Channel D: USB3.2 RX
// 0   Chip Enable Control
#define ONSEMI_OPERATION_USB_MODE 0xFB

// 3:1 operation modes:
//      010= Four lanes of DisplayPort
//        Channel A: DP Lane
//        Channel B: DP Lane
//        Channel C: DP Lane
//        Channel D: DP Lane
#define ONSEMI_OPERATION_DP_MODE 0xF5

// 3:1 operation modes:
//      000= Two lanes of DisplayPort + One port of USB 3.2 Gen1/Gen2
//        Channel A: USB 3.2 RX
//        Channel B: USB 3.2 TX
//        Channel C: DP Lane
//        Channel D: DP Lane
#define ONSEMI_OPERATION_USB_DP_MODE 0xF1

const usb_booster_cfg_type ONSEMI_REDRIVER_TUNING_CFG[] = 
{
  //in V1 the reset value change to 0x0, but to keep compa with V0 chip, write 0xD within 100 ms of releasing RESETN 
  {ONSEMI_GENERAL_DEVICE_SETTING_REG, 0x00},  // General Device Settings //Disable ALL
  {0x01, 0x08},  // Channel A Equalization Settings
  {0x18, 0x03},  // Channel A Flat Gain
  {0x02, 0x07},  // Channel A Output -1dB Compression & Polarity Settings
  {0x19, 0x01},  // Channel A Loss Profile Matching Control
  {0x03, 0x08},  // Channel B Equalization Settings
  {0x1a, 0x01},  // Channel B Flat Gain Settings
  {0x04, 0x07},  // Channel B Output -1dB Compression & Polarity Settings
  {0x1b, 0x03},  // Channel B Loss Profile Matching Control
  {0x05, 0x08},  // Channel C Equalization Settings
  {0x1c, 0x01},  // Channel C Flat Gain Settings
  {0x06, 0x07},  // Channel C Output -1dB Compression & Polarity Settings
  {0x1d, 0x03},  // Channel C Loss Profile Loss Matching Control
  {0x07, 0x08},  // Channel D Equalization Settings
  {0x1e, 0x03},  // Channel D Flat Gain Settings
  {0x08, 0x07},  // Channel D Output -1dB Compression & Polarity Settings
  {0x1f, 0x01},  // Channel D Loss Profile Matching Control, USB State Machine & DP Channel Direction
};

const uint32 onsemi_redriver_tuning_size   = (sizeof(ONSEMI_REDRIVER_TUNING_CFG)       /sizeof(usb_booster_cfg_type));

// ===========================================================================
/**
 * @function    usb_redriver_init
 * 
 * @brief   This function start redriver driver
 * 
 * @param   core_num   -  which core redriver locate
 * 
 * @return  boolean - TRUE successs, FALSE error
 * 
 */
// ===========================================================================
boolean usb_redriver_init(uint32 core_num, uint32 usb_mode)
{

  boolean status = TRUE;
  usb_platform_ctx platform = usb_shared_get_platform();
  if (core_num >= USB_MAX_NUM_CORE)
  {
    //usb_shared_uart_log_error("usb_redriver, bad_para", __LINE__);
    usb_shared_error_log(REDRIVER_INIT_FAIL__BAD_PARAMETER_LOG, 0, core_num);
    return FALSE;
  }


  if (platform.platform== DALPLATFORMINFO_TYPE_QRD)
  {
    //usb_shared_i2c_bus_scan (USB_REDRIVER_I2C_INSTANCE_PRIMARY);

    //usb_shared_uart_log_info1("usb_redriver, core ", core_num);

    if (usb_redriver_ctx[core_num].i2c_ctx.handle != NULL)
    {
      //usb_shared_uart_log_error("usb_redriver_init, already open:", core_num);
      usb_shared_error_log(REDRIVER_INIT_FAIL__ALREADY_OPEN_LOG, 0, core_num);
      return TRUE;
    }

    status = usb_shared_i2c_open(&usb_redriver_ctx[core_num].i2c_ctx, USB_REDRIVER_I2C_INSTANCE_PRIMARY, USB_REDRIVER_I2C_SLAVE_ADDRESS_PRIMARY);
    if((FALSE == status) || (usb_redriver_ctx[core_num].i2c_ctx.handle == NULL))
    {
      usb_shared_uart_log_error("usb_redriver, Failed slave", USB_REDRIVER_I2C_SLAVE_ADDRESS_PRIMARY);  
      usb_shared_error_log(REDRIVER_INIT_FAIL__OPEN_LOG, 0, USB_REDRIVER_I2C_SLAVE_ADDRESS_PRIMARY);
      return FALSE;
    }
    usb_shared_uart_log_info1("usb_redriver, open inst|sla|core", usb_redriver_ctx[core_num].i2c_ctx.instance<<16|USB_REDRIVER_I2C_SLAVE_ADDRESS_PRIMARY<<8|core_num);  
    usb_shared_error_log(REDRIVER_INIT_LOG, 0, USB_REDRIVER_I2C_SLAVE_ADDRESS_PRIMARY);

  }  
  return TRUE;
}

// ===========================================================================
/**
 * @function    usb_redriver_set_usb_mode
 * 
 * @brief   This function set usb mode for redriver
 * 
 * @param   core_num   -  which core redriver locate
 * @param   usb_mode   -  which mode usb should set to.
 * 
 * @return  boolean - TRUE successs, FALSE error
 * 
 */
// ===========================================================================
boolean usb_redriver_set_usb_mode(uint32 core_num, uint32 usb_mode)
{
	boolean result = FALSE;
  //uint8 read_value =1;
  uint32 setting_value = ONSEMI_OPERATION_USB_MODE;
  
  usb_shared_uart_log_warn("usb_redriver, set_mode:", usb_mode);
  //usb_shared_error_log(REDRIVER_SET_MODE_LOG, 0, usb_mode);

  if ((core_num >= USB_MAX_NUM_CORE) || (usb_mode >=USB4_MODE_TYPE_MAX))
  {
    usb_shared_uart_log_error("usb_redriver, bad para", __LINE__);
    usb_shared_error_log(REDRIVER_INIT_FAIL__BAD_PARAMETER_LOG, 0, core_num);
    return FALSE;
  }

  if (NULL == usb_redriver_ctx[core_num].i2c_ctx.handle)
  {
    if (FALSE == usb_redriver_init(core_num, usb_mode))
    {
      return FALSE;
    }
  }

  //result = usb_shared_i2c_read(&usb_redriver_ctx[core_num].i2c_ctx, ONSEMI_GENERAL_DEVICE_SETTING_REG, &read_value, 1);    
  //result = usb_shared_i2c_read(&usb_redriver_ctx[core_num].i2c_ctx, 0x1, &read_value, 1);  
  //result = usb_shared_i2c_read(&usb_redriver_ctx[core_num].i2c_ctx, 0x9, &read_value, 1);  


  
  result = usb_shared_i2c_process_cfg_reg_array(&usb_redriver_ctx[core_num].i2c_ctx, ONSEMI_REDRIVER_TUNING_CFG,0,onsemi_redriver_tuning_size, TRUE);

    if (FALSE == result)
    {
      return FALSE;
    }
    switch (usb_mode)
    {
      case USB4_MODE_TYPE_USB3:
	  	  setting_value = ONSEMI_OPERATION_USB_MODE;
        result = usb_shared_i2c_write(&usb_redriver_ctx[core_num].i2c_ctx, ONSEMI_GENERAL_DEVICE_SETTING_REG, (uint8*)&setting_value, 1);
        break;
      case USB4_MODE_TYPE_USB3DP:
	  	  setting_value = ONSEMI_OPERATION_USB_DP_MODE;
        result = usb_shared_i2c_write(&usb_redriver_ctx[core_num].i2c_ctx, ONSEMI_GENERAL_DEVICE_SETTING_REG, (uint8*)&setting_value, 1);
        break;
      case USB4_MODE_TYPE_DP4LANE:
	  	  setting_value = ONSEMI_OPERATION_DP_MODE;
        result = usb_shared_i2c_write(&usb_redriver_ctx[core_num].i2c_ctx, ONSEMI_GENERAL_DEVICE_SETTING_REG, (uint8*)&setting_value, 1);      
        break;
      default:
        usb_shared_uart_log_error("usb_redriver, unsupported mode:", usb_mode); 
        usb_shared_error_log(REDRIVER_SET_MODE_FAIL__WRONG_MODE_LOG, 0, usb_mode);
        result = usb_shared_i2c_write(&usb_redriver_ctx[core_num].i2c_ctx, ONSEMI_GENERAL_DEVICE_SETTING_REG, (uint8*)&setting_value, 1);
    }
    return result;
}
#else
boolean usb_redriver_init(uint32 core_num, uint32 usb_mode)
{
  return FALSE;
}
boolean usb_redriver_set_usb_mode(uint32 core_num, uint32 usb_mode)
{
  return FALSE;
}

#endif
