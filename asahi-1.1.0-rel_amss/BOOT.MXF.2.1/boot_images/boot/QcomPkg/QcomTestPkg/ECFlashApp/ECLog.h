/** @file
  EC_log is used to provide different level of logging for SERIAL/XBL/UEFI console

Copyright (c) 2021-2022 Qualcomm Technologies Inc. All rights reserved.
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

/*=============================================================================
                              EDIT HISTORY

 when       who                 what, where, why
 --------   ---                 ----------------------------------------------------------
 12/08/22   bkulkarn            Update Hamoa EC FW partition size/I2C core instance, code refactoring
 11/14/22   ananns              Added code documentation and function descriptions 
 10/17/21   sumesahu            Initial revision
=============================================================================*/

#ifndef _EC_LOG_H
#define _EC_LOG_H

#include <Library/DebugLib.h>
#include <Library/PrintLib.h>

/* For logging - Mutually exclusive Macros */
#define SERIAL_UART         1
#define UEFI_CONSOLE        0
#define XBL_CONSOLE         0

#define Tool_Version        "1.0"
#define Tool_Vendor         "Qualcomm"

enum EC_DEBUG
{
  DISABLE_LOGS=0,
  ENABLE_LOGS=1
};

/* Logging Prints Start */
#if SERIAL_UART

  #define EC_I(fmt, args...)                              \
    AsciiPrint("[ITE-EC I] [%a] "                       \
      fmt, __func__, ##args)
  
  #define EC_E(fmt, args...)                              \
    AsciiPrint("[ITE-EC E] [%a %d] "                    \
      fmt, __func__, __LINE__, ##args)
  
  #define EC_D(fmt, args...)                              \
    do {                                                \
      if (deviceContext->debug_mask & (ENABLE_LOGS))      \
          AsciiPrint("[ITE-EC D] [%a] "               \
         fmt, __func__, ##args);                     \
    } while (0)

  #define EC_TRACE()  EC_D( "\n")
  
  #define EC_P(fmt, args...)                              \
      AsciiPrint(fmt, ##args)

#elif UEFI_CONSOLE

  #define EC_I(fmt, args...)                              \
    Print(L"[ITE-EC] [%a]"                              \
      fmt, __func__, ##args)
  
  #define EC_E(fmt, args...)                              \
      Print(L"[ITE-EC E] [%a %d] "                        \
       fmt, __func__, __LINE__, ##args)
  
  #define EC_D(fmt, args...)                              \
    do {                                                \
      if (deviceContext->debug_mask & (ENABLE_LOGS))      \
          Print(L"[ITE-EC D] [%a] "                   \
          fmt, __func__, ##args);                     \
   } while (0)

  #define EC_TRACE()  EC_D( "\n")

  #define EC_P(fmt, args...)                              \
    Print((const CHAR16 *)fmt, ##args)

#elif XBL_CONSOLE

  #define EC_I(fmt, args...)                              \
     DebugPrint(EFI_D_INFO, "[ITE-EC] " fmt, ##args)

  #define EC_E(fmt, args...)                              \
    DebugPrint(EFI_D_ERROR, "[ITE-EC] " fmt, ##args)

  #define EC_D(fmt, args...)                              \
    do {                                                \
       if (deviceContext->debug_mask & (ENABLE_LOGS))      \
           DebugPrint(EFI_D_INFO, "[ITE-EC] " fmt, ##args);       \
    } while (0)

    #define EC_TRACE()

    #define EC_P(fmt, args...)                              \
      DebugPrint(EFI_D_ERROR, "[ITE-EC] " fmt, ##args)
#else
  #define EC_I(fmt, args...)
  #define EC_E(fmt, args...)
  #define EC_D(fmt, args...)
  #define EC_P(fmt, args...)

#endif
/* Logging Prints END */

#endif