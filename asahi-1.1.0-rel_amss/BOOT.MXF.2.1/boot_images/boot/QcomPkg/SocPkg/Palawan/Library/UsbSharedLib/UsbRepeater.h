/** @file UsbRepeater.h

  The public header file for UsbRepeater.c

**/
//============================================================================
/**
  Copyright (c) 2021-2023 Qualcomm Technologies, Inc. All rights reserved.
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

/*=============================================================================
                              EDIT HISTORY

 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 09/09/21   srmi     Initial Check-in
=============================================================================*/

#ifndef _USB_REPEATER_H_
#define _USB_REPEATER_H_

#include "UsbSharedLib.h"

#define PMIC_EUSB_RPTR0_INDEX                       (7)   // PMIC_H, Kohala PM8550B
#define PMIC_EUSB_RPTR_SPMI_BUSID                   (0)

#define EUSB2_BASE                                  (0x0000fd00)
#define PMIC_EUSB2_TUNE_USB2_CROSSOVER_OFFS         (0x00000050)
#define PMIC_EUSB2_TUNE_IUSB2_OFFS                  (0x00000051)
#define PMIC_EUSB2_TUNE_RES_FSDIF_OFFS              (0x00000052) 
#define PMIC_EUSB2_TUNE_HSDISC_OFFS                 (0x00000053) 
#define PMIC_EUSB2_TUNE_SQUELCH_U_OFFS              (0x00000054) 
#define PMIC_EUSB2_TUNE_USB2_SLEW_OFFS              (0x00000055) 
#define PMIC_EUSB2_TUNE_USB2_EQU_OFFS               (0x00000056) 
#define PMIC_EUSB2_TUNE_USB2_PREEM_OFFS             (0x00000057) 
#define PMIC_EUSB2_TUNE_USB2_HS_COMP_CURRENT_OFFS   (0x00000058) 
#define PMIC_EUSB2_TUNE_EUSB_SLEW_OFFS              (0x00000059) 
#define PMIC_EUSB2_TUNE_EUSB_EQU_OFFS               (0x0000005a) 
#define PMIC_EUSB2_TUNE_EUSB_HS_COMP_CURRENT_OFFS   (0x0000005b) 


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
UINT32 usb_repeater_get_index_for_core(uint32 core_num);

// ===========================================================================
/**
 * @function    usb_repeater_init
 * 
 * @brief   This function start repeater driver
 * 
 * @param   core_num   -  which core repeater locate
 * 
 * @return  boolean - TRUE successs, FALSE error
 * 
 */
// ===========================================================================
boolean usb_repeater_init(uint32 core_num);



// ===========================================================================
/**
 * @function    usb_repeater_reset
 * 
 * @brief   This function reset repeater driver
 * 
 * @param   core_num   -  which core repeater locate
 * 
 * @return  boolean - TRUE successs, FALSE error
 * 
 */
// ===========================================================================
boolean usb_repeater_reset(uint32 core_num);

#endif /* _USB_REPEATER_H_ */