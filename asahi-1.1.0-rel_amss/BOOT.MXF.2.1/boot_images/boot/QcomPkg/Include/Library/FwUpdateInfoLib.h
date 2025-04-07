/** @file FwUpdateInfoLib.h
   
  Header for externally-available functions of the 
  FwUpdateInfoLib

  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when           who         what, where, why
 --------       ---         --------------------------------------------------
 2023/03/10     gpavithr    Initial version

=============================================================================*/
#ifndef _FW_UPDATEINFO_LIB_H_
#define _FW_UPDATEINFO_LIB_H_

#include <Uefi.h>

/**
  Function to check if there are any pending capsules.

  @retval  TRUE    Capsule pending.
  @retval  FALSE   No pending capsules.

**/
BOOLEAN
CheckIfCapsulePending (VOID);

#endif
