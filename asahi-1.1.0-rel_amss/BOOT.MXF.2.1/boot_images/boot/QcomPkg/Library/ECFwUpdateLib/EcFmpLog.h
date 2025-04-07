/** @file EC_FMP_Log.h

  Header for EC FMP related logging macros

  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc.  All Rights
  Reserved. Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                            EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when           who         what, where, why
  --------       ---         --------------------------------------------------
  2023/02/28     sumesahu    Fix for Boot KPI during empty EC FW
  2023/02/04     sumesahu    FR79849: Support for Prepare/Flash/Post/Rollback FMP StateMachine
                             and code refactoring
  2022/07/29     sumesahu    Initial version
=============================================================================*/

#ifndef _EC_FMP_LOG_H
#define _EC_FMP_LOG_H

#include <Library/DebugLib.h>

#define EC_I(fmt, args...)                                \
  DebugPrint(EFI_D_INFO, "[EC] [%a] "fmt, __func__, ##args)

#define EC_W(fmt, args...)                                \
    DebugPrint(EFI_D_WARN, " "fmt, ##args)

#define EC_E(fmt, args...)                                \
  DebugPrint(EFI_D_ERROR, "[EC] [%a %d] "fmt, __func__, __LINE__, ##args)

#define EC_D(fmt, args...)                                \
  DebugPrint(EFI_D_VERBOSE, "[EC] [%a %d] "fmt, __func__, __LINE__, ##args)

#define EC_TRACE() EC_D( "\n")

/* Log for Dumping the packet info */
#define EC_P(fmt, args...)              \
  DebugPrint(EFI_D_VERBOSE, " " fmt, ##args)

#define EC_ERROR_HANDLER(Status, Function, Label) \
  do {  \
    if (EFI_ERROR(Status))   \
    {   \
      DebugPrint(EFI_D_ERROR, "[EC] %a failed with %r Line: %d\n",\
      #Function, Status, __LINE__);\
      goto Label; \
    }   \
  }while (0)

#define EC_WARN_HANDLER(Status, Function) \
  do {  \
    if (EFI_ERROR(Status))   \
    {   \
      DebugPrint(EFI_D_WARN, "[EC] %a failed with %r\n", #Function, Status);\
      status = EFI_SUCCESS;\
    }   \
  }while (0)

#endif
