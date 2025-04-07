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
02/15/23   ck      Renamed to boot_cache_if
05/21/20   rama    Initial revision
=============================================================================*/

#include <Library/CacheMaintenanceLib.h>
#include <boot_cache_if.h>


boot_cache_if_type cache_if = {
  InvalidateInstructionCache,
  InvalidateInstructionCacheRange,
  WriteBackInvalidateDataCache,
  WriteBackInvalidateDataCacheRange,
  WriteBackDataCache,
  WriteBackDataCacheRange,
  InvalidateDataCache,
  InvalidateDataCacheRange
};
