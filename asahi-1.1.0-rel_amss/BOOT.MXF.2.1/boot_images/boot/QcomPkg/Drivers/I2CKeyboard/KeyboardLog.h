/** @file
  Keyboard Logger is used for different level of logging.

Copyright (c) 2022 Qualcomm Technologies Inc. All rights reserved.
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 10/17/22   ananns      Added code documentation and function descriptions
 10/17/22   sumesahu    Initial revision
=============================================================================*/

#ifndef _KB_LOG_H
#define _KB_LOG_H

#include <Library/DebugLib.h>

#define KB_I(fmt, args...)                                \
  DebugPrint(EFI_D_INFO, "[KB] [%a] "fmt, __func__, ##args)

#define KB_W(fmt, args...)                                \
    DebugPrint(EFI_D_WARN, " "fmt, ##args)

#define KB_E(fmt, args...)                                \
  DebugPrint(EFI_D_ERROR, "[KB] [%a %d] "fmt, __func__, __LINE__, ##args)

#define KB_D(fmt, args...)                                \
  DebugPrint(EFI_D_VERBOSE, "[KB] [%a %d] "fmt, __func__, __LINE__, ##args)

#define KB_TRACE() KB_I( "\n")

/* Log for Dumping the packet info */
#define KB_P(fmt, args...)              \
  DebugPrint(EFI_D_ERROR, " " fmt, ##args)

#define KB_ERROR_HANDLER(Status, Function, Label) \
  do {  \
    if(EFI_ERROR(Status))   \
    {   \
      DebugPrint(EFI_D_ERROR, "[KB] %a failed with %r\n", #Function, Status);\
      goto Label; \
    }   \
  }while (0)

#endif