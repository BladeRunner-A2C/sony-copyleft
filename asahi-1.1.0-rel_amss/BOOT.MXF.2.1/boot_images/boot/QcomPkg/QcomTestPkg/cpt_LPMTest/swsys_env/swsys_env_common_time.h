/*
===========================================================================
*/
/**
  @file swsys_env_common_time.h

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

#ifndef SWSYS_ENV_COMMON_TIME_H
#define SWSYS_ENV_COMMON_TIME_H

#include <stdint.h>

#include "swsys_env.h"

void swsys_env_init_common_time();

time_t swsys_time_common (time_t* t);
double swsys_difftime_common (time_t end, time_t beginning);

#endif // SWSYS_ENV_COMMON_TIME_H
