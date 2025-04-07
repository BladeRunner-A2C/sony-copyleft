/*
===========================================================================
*/
/**
  @file swsys_env_uefi_core_bsp.c

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

#include "swsys_env_uefi_core.h"
bool swsys_is_ap_core_uefi ()
{
  return false;
}

uint32_t swsys_get_ap_core_num_uefi ()
{
  return 0;
}
