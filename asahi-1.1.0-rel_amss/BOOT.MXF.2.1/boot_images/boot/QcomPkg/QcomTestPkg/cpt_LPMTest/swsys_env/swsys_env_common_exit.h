/*
===========================================================================
*/
/**
  @file swsys_env_common_exit.h

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

#ifndef SWSYS_ENV_COMMON_EXIT_H
#define SWSYS_ENV_COMMON_EXIT_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "swsys_env.h"

void swsys_env_init_common_exit();

void swsys_exit_common (int32_t status);

#endif // SWSYS_ENV_COMMON_EXIT_H
