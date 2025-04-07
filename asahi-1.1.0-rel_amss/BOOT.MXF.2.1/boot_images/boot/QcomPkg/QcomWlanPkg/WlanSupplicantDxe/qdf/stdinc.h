/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
Portions:
 Copyright (c) 2010 - 2019, Intel Corporation. All rights reserved.<BR>
 SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#ifndef __QDF_STDINC_H
#define __QDF_STDINC_H

#ifdef CONFIG_NO_STDLIB_SUPPORT

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <qdf/base_type.h>
#include <qdf/limits.h>

/* memory operations */
#define memcmp(a, b, size) (int)CompareMem(a, b, size)
#define memmove(dest,source,count) CopyMem(dest,source,(UINTN)(count))
void *memcpy(void *d, const void *s, size_t n);
void *memset(void *s, int ch, size_t n);


/* errno */
#define	EINVAL		22

#define va_start VA_START
#define va_arg   VA_ARG
#define va_end   VA_END
#define va_list  VA_LIST

typedef VOID *FILE;

/*
 * Structures Definitions
 */
struct timeval {
    long tv_sec;      /* time value, in seconds */
    long tv_usec;     /* time value, in microseconds */
};

struct tm {
    int   tm_sec;     /* seconds after the minute [0-60] */
    int   tm_min;     /* minutes after the hour [0-59] */
    int   tm_hour;    /* hours since midnight [0-23] */
    int   tm_mday;    /* day of the month [1-31] */
    int   tm_mon;     /* months since January [0-11] */
    int   tm_year;    /* years since 1900 */
    int   tm_wday;    /* days since Sunday [0-6] */
    int   tm_yday;    /* days since January 1 [0-365] */
    int   tm_isdst;   /* Daylight Savings Time flag */
    long  tm_gmtoff;  /* offset from CUT in seconds */
    char  *tm_zone;   /* timezone abbreviation */
};

#else /* !CONFIG_NO_STDLIB_SUPPORT */

#include <Uefi.h>
#include <stdlib.h>

typedef UINT8 u8;
typedef UINT16 u16;
typedef UINT32 u32;
typedef UINT64 u64;

typedef BOOLEAN bool;
typedef UINTN size_t;

#define false FALSE
#define true  TRUE

#ifndef SIZE_MAX
#define SIZE_MAX         0xffffffffffffffffu
#endif

#define ARRAY_LENGTH(_Array) (sizeof(_Array) / sizeof((_Array)[0]))

#endif /* CONFIG_NO_STDLIB_SUPPORT */


/* missing errno */
#define	ENOENT		2

/* uefi stdlibc implementation */
int __isspace(int c);
int __sscanf(const char *str, const char *format, ...);
int __atoi(const char *str);

#undef isspace
#define isspace(_c) __isspace(_c)
#undef atoi
#define atoi(_str)  __atoi(_str)

/* Add a implementation for sscanf as it is null implmentation in UEFI */
#define sscanf(_str, _fmt, ...) __sscanf(_str, _fmt, ##__VA_ARGS__)


#endif // !__QDF_STDINC_H