/*
===========================================================================
*/
/**
  @file swsys_env_common_float.h

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

#ifndef SWSYS_ENV_COMMON_FLOAT_H
#define SWSYS_ENV_COMMON_FLOAT_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "swsys_env.h"

void swsys_env_init_common_float();

float    swsys_strtof_common   (const char* str, char** endptr);
double   swsys_strtod_common   (const char* str, char** endptr);

#endif // SWSYS_ENV_COMMON_FLOAT_H
