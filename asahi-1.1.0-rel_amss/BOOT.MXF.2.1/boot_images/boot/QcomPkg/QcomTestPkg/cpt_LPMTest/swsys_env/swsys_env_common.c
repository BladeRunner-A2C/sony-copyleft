/*
===========================================================================
*/
/**
  @file swsys_env_common.c

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

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <assert.h>

#include "swsys_env.h"
#include "swsys_env_common.h"

swsys_env swsys_env_i;

void swsys_env_init_common ()
{
  swsys_env_i.env       = SWSYS_ENV_NONE;
  swsys_env_i.env_str   = NULL;

  swsys_env_i.malloc    = swsys_malloc_common;
  swsys_env_i.malloc_uc = NULL;
  swsys_env_i.free      = swsys_free_common;

  swsys_env_i.vprintf    = swsys_vprintf_common;
  swsys_env_i.vsnprintf  = swsys_vsnprintf_common;

  swsys_env_i.strtoi32  = swsys_strtoi32_common;
  swsys_env_i.strtoi64  = swsys_strtoi64_common;
  swsys_env_i.strtou32  = swsys_strtou32_common;
  swsys_env_i.strtou64  = swsys_strtou64_common;

  swsys_env_i.strncmp   = swsys_strncmp_common;
  swsys_env_i.strcmp    = swsys_strcmp_common;
  swsys_env_i.strstr    = swsys_strstr_common;
  swsys_env_i.strlen    = swsys_strlen_common;

  swsys_env_i.memcpy = swsys_memcpy_common;
  swsys_env_i.memset = swsys_memset_common;
}

void* swsys_malloc_common (uint64_t size)
{
  return (void*) malloc(size);
}

void swsys_free_common (void* buf)
{
  free(buf);
}

int32_t swsys_vprintf_common (const char* format, va_list arg)
{
  return vprintf(format, arg);
}

int32_t swsys_vsnprintf_common (char* s, uint64_t n, const char* format, va_list arg)
{
  return vsnprintf(s, n, format, arg);
}

int32_t swsys_strtoi32_common (const char* str, char** endptr, int32_t base)
{
  return strtol(str, endptr, base);
}

int64_t swsys_strtoi64_common (const char* str, char** endptr, int32_t base)
{
  return strtoll(str, endptr, base);
}

uint32_t swsys_strtou32_common (const char* str, char** endptr, int32_t base)
{
  return strtoul(str, endptr, base);
}

uint64_t swsys_strtou64_common (const char* str, char** endptr, int32_t base)
{
  return strtoull(str, endptr, base);
}

int32_t swsys_strncmp_common (const char* str1, const char* str2, uint64_t num)
{
  return strncmp(str1, str2, num);
}

int32_t swsys_strcmp_common (const char* str1, const char* str2)
{
  return strcmp(str1, str2);
}

char* swsys_strstr_common (const char* str1, const char* str2)
{
  return strstr(str1, str2);
}

uint64_t swsys_strlen_common (const char* str)
{
  return strlen(str);
}

void swsys_memcpy_common (void* dest, const void* src, uint64_t len)
{
  memcpy(dest, src, len);
}

void swsys_memset_common (void* ptr, int32_t value, uint64_t num)
{
  memset(ptr, value, num);
}

bool swsys_is_ap_core_common ()
{
  return false;
}

uint32_t swsys_get_ap_core_num_common ()
{
  return 0;
}
