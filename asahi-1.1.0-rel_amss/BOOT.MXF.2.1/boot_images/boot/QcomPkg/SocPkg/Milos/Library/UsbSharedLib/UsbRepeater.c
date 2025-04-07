/*=======================================================================*//**
 * @file        UsbRepeater.c
 * @author:     pohanw
 * @date        09-Sep-2021
 *
 * @brief       USB common & shared USB core implementation for repeater Library.
 *
 * @details     This file contains sequence to enable repeater.
 *
 * @note        
 *
 * 
*//*========================================================================*/
//============================================================================
/**
  Copyright (c) 2021-2023 Qualcomm Technologies, Inc. All rights reserved.
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
// 09/09/21      srmi    Initial revision
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------

#include "UsbSharedLib.h"
#include "UsbRepeater.h"
#include "UsbSharedLibTargetConfig.h"


const usb_booster_cfg_type*  g_repeater_tuning_cfg_handle;
uint32 g_repeater_tuning_size;

static const usb_booster_cfg_type PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_MTP [] = 
{ 
  {PMIC_EUSB2_TUNE_IUSB2_OFFS, 0x08},
  {PMIC_EUSB2_TUNE_SQUELCH_U_OFFS, 0x03},
  {PMIC_EUSB2_TUNE_USB2_PREEM_OFFS, 0x05},
};
static const usb_booster_cfg_type PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_ATP [] = 
{ 
  {PMIC_EUSB2_TUNE_IUSB2_OFFS, 0x00},
  {PMIC_EUSB2_TUNE_SQUELCH_U_OFFS, 0x04},
  {PMIC_EUSB2_TUNE_USB2_PREEM_OFFS, 0x00},
};
static const usb_booster_cfg_type PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_QRD [] = 
{ 
  {PMIC_EUSB2_TUNE_IUSB2_OFFS, 0x0D},
  {PMIC_EUSB2_TUNE_HSDISC_OFFS, 0x06},
  {PMIC_EUSB2_TUNE_SQUELCH_U_OFFS, 0x03},
  {PMIC_EUSB2_TUNE_USB2_PREEM_OFFS, 0x07},
};


// ===========================================================================
/**
 * @function    usb_repeater_get_index_for_core
 * 
 * @brief   This function returns  pmic eusb repeater index depening upon core
 * 
 * @param   core_num  -  core number to which repeater is connected
 * 
 * @return  uint32  
 * 
 */
// ===========================================================================
UINT32 usb_repeater_get_index_for_core(uint32 core_num)
{
  UINT32        pmic_eusb_rptr_index = 0x0;
  switch (core_num)
  {
    case 0: pmic_eusb_rptr_index = PMIC_EUSB_RPTR0_INDEX; break;
#if USB_SEC_FLAG
    case 1: pmic_eusb_rptr_index = PMIC_EUSB_RPTR1_INDEX; break;
#endif
#if USB_TER_FLAG
    case 2: pmic_eusb_rptr_index = PMIC_EUSB_RPTR2_INDEX; break;
#endif
    default:
  {
     usb_shared_uart_log_error("invalid core", core_num);
  }
    break;
  }
  return pmic_eusb_rptr_index; 
}


boolean usb_repeater_spmi_tune(uint32 core_num)
{
  //usb_shared_spmi_process_cfg_reg_array(core_num, g_repeater_tuning_cfg_handle, 0 , g_repeater_tuning_size, FALSE);
  if (TRUE == usb_shared_spmi_process_cfg_reg_array(core_num, g_repeater_tuning_cfg_handle, 0 , g_repeater_tuning_size, TRUE))
  {
    return usb_shared_spmi_process_cfg_reg_array(core_num, g_repeater_tuning_cfg_handle, 0 , g_repeater_tuning_size, FALSE);
  }
  return FALSE;
}

boolean usb_repeater_is_tuning_allowed (usb_platform_ctx plat_type, uint32 core_num)
{
  boolean repeater_tune_allow = FALSE;
  // usb_shared_uart_log_error("Platform :", plat_type.platform); 
  switch (plat_type.platform)
  {
    case DALPLATFORMINFO_TYPE_QRD:
      repeater_tune_allow = TRUE;
      g_repeater_tuning_cfg_handle = PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_QRD;
      g_repeater_tuning_size = (sizeof(PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_QRD) / sizeof(usb_booster_cfg_type));
	  break;
    case DALPLATFORMINFO_TYPE_MTP:
    case DALPLATFORMINFO_TYPE_CDP:
    case DALPLATFORMINFO_TYPE_CRD: // windows specific
      /* fall through */
    case DALPLATFORMINFO_TYPE_IDP:
      repeater_tune_allow = TRUE;
      g_repeater_tuning_cfg_handle = PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_MTP;
      g_repeater_tuning_size = (sizeof(PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_MTP) / sizeof(usb_booster_cfg_type));	  
      break;
    case DALPLATFORMINFO_TYPE_ATP:
      repeater_tune_allow = TRUE;
      g_repeater_tuning_cfg_handle = PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_ATP;
      g_repeater_tuning_size = (sizeof(PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_ATP) / sizeof(usb_booster_cfg_type));
      break;
    default:
      repeater_tune_allow = FALSE;
  }
  return repeater_tune_allow;
}

boolean usb_repeater_init(uint32 core_num)
{
  usb_platform_ctx plat_type = usb_shared_get_platform();
  boolean is_usb_repeater_tuning_allow = usb_repeater_is_tuning_allowed(plat_type, core_num);
  
  if (is_usb_repeater_tuning_allow)
  {
    // usb_shared_uart_log_error("usb_repeater_init", plat_type.platform);
    //usb_shared_error_log(REPEATER_INIT_LOG, 0, plat_type.platform);

    if (FALSE == usb_shared_spmi_init(core_num))
    {
      usb_shared_uart_log_error("spmi_init_failed", core_num);
      //usb_shared_error_log(REPEATER_INIT_FAIL__SPMI_INIT_LOG, 0, core_num);
      return FALSE;
    }

    if (FALSE == usb_repeater_spmi_tune(core_num))
    {
      usb_shared_uart_log_error("spmi_tune_failed", core_num);
      //usb_shared_error_log(REPEATER_INIT_FAIL__SPMI_TUNE_LOG, 0, core_num);
      return FALSE;
    }
  }
  return TRUE;
}


boolean usb_repeater_reset(uint32 core_num)
{
  if (FALSE == usb_shared_pmic_gpio_enable(USB_REPEATER_RESET_GPIO_IDX, FALSE))
  {
    return FALSE;
  }
  usb_shared_delay_us(20);  
  if (FALSE == usb_shared_pmic_gpio_enable(USB_REPEATER_RESET_GPIO_IDX, TRUE))
  {
    return FALSE;
  }
  return TRUE;
}