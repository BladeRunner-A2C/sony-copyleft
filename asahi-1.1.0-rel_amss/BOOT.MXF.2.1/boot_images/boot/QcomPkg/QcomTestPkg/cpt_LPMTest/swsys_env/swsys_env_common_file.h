/*
===========================================================================
*/
/**
  @file swsys_env_common_file.h

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

#ifndef SWSYS_ENV_COMMON_FILE_H
#define SWSYS_ENV_COMMON_FILE_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "swsys_env.h"

void swsys_env_init_common_file();

FILE*    swsys_fopen_common  (const char* filename, const char* mode);
int64_t  swsys_fclose_common (FILE* f);
uint64_t swsys_fread_common  (void* buf, uint64_t size, uint64_t count, FILE* f);
uint64_t swsys_fwrite_common (const void* buf, uint64_t size, uint64_t count, FILE* f);
int32_t  swsys_fflush_common (FILE* stream);
FILE*    swsys_stdout_common ();

#endif // SWSYS_ENV_COMMON_FILE_H
