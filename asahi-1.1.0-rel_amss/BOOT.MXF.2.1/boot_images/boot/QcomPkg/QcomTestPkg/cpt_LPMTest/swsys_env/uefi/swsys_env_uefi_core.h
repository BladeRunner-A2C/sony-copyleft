/*
===========================================================================
*/
/**
  @file swsys_env_uefi_core.h

*/
/*
  ====================================================================

  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  06/14/17   jh      Initial revision.

  ====================================================================
*/

#ifndef SWSYS_ENV_UEFI_CORE_H
#define SWSYS_ENV_UEFI_CORE_H

#include "../swsys_env.h"
bool swsys_is_ap_core_uefi();
uint32_t swsys_get_ap_core_num();

#endif // SWSYS_ENV_UEFI_CORE_H
