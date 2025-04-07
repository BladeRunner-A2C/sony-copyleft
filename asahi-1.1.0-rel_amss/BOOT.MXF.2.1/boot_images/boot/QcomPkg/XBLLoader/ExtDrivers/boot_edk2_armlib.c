/*===========================================================================

GENERAL DESCRIPTION
  This module contains the arm if.

 Copyright 2020, 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.

 ==============================================================================*/
 /*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
02/15/23   ck      Renamed to boot_arm_if
05/21/20   rama    Initial revision
=============================================================================*/

#include <Library/ArmLib.h>
#include <boot_arm_if.h>


boot_arm_if_type arm_if = {
  ArmDataSynchronizationBarrier,
  ArmDataMemoryBarrier,
  //ArmReadCpacr,
  ArmWriteCpacr,
  ArmInstructionSynchronizationBarrier,
  ArmInvalidateDataCache,
  ArmInvalidateInstructionCache,
  //ArmEnableCachesAndMmu,
  ArmDisableCachesAndMmu
};