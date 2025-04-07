/*
===========================================================================
*/
/**
  @file swsys_env_common.h

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

#ifndef SWSYS_ENV_COMMON_H
#define SWSYS_ENV_COMMON_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "swsys_env.h"

void swsys_env_init_common();

void* swsys_malloc_common    (uint64_t size);
void  swsys_free_common      (void* buf);

int32_t swsys_vprintf_common   (const char* format, va_list arg);
int32_t swsys_vsnprintf_common (char* s, uint64_t n, const char* format, va_list arg);

int32_t  swsys_strtoi32_common (const char* str, char** endptr, int32_t base);
int64_t  swsys_strtoi64_common (const char* str, char** endptr, int32_t base);
uint32_t swsys_strtou32_common (const char* str, char** endptr, int32_t base);
uint64_t swsys_strtou64_common (const char* str, char** endptr, int32_t base);

int32_t  swsys_strncmp_common (const char* str1, const char* str2, uint64_t num);
int32_t  swsys_strcmp_common  (const char* str1, const char* str2);
char*    swsys_strstr_common  (const char* str1, const char* str2);
uint64_t swsys_strlen_common  (const char* str);

void swsys_memcpy_common (void* dest, const void* src, uint64_t len);
void swsys_memset_common (void* ptr, int32_t value, uint64_t num);

bool swsys_is_ap_core_common ();
uint32_t swsys_get_ap_core_num_common ();

#endif // SWSYS_ENV_COMMON_H
