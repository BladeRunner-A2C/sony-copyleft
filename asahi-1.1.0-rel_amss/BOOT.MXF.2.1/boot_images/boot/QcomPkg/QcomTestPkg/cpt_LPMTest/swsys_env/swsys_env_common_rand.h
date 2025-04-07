/*
===========================================================================
*/
/**
  @file swsys_env_common_rand.h

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

#ifndef SWSYS_ENV_COMMON_RAND_H
#define SWSYS_ENV_COMMON_RAND_H

#include "swsys_env.h"

void    swsys_srand_common (uint32_t seed);
int32_t swsys_rand_common  ();

#endif // SWSYS_ENV_COMMON_RAND_H
