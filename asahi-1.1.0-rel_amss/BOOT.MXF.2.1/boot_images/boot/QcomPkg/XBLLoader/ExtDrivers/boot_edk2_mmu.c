/*===========================================================================

GENERAL DESCRIPTION
  This module contains the initial memory map for SBL.

  Copyright 2020, 2023 by Qualcomm Technologies Incorporated.  All Rights Reserved.
==============================================================================*/
/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
02/15/23   ck      Renamed to boot_mmu_if
05/21/20   rama    Initial revision
=============================================================================*/

#include <Library/ArmMmuLib.h>
#include <ArmMmuLibEfiAttributesMap.h>
#include <boot_mmu_if.h>


boot_mmu_if_type mmu_if = {
  ArmConfigureMmu,
  ArmSetMemoryAttributes
};
