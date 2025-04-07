/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 6/9/21    zxue     fix parasoft issue
 26/8/21   zxue     refine the code
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QDF_STDIO_H
#define __QDF_STDIO_H

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <qdf/base_type.h>
#include <qdf/errno.h>

/* memory operations */
#define memcmp(a, b, size) (int)CompareMem(a, b, size)
#define memcpy CopyMem
#define memmove(dest,source,count) CopyMem(dest,source,(UINTN)(count))
void *memset(void *s, int ch, size_t n);

 /* string operations */
#define strcmp(_str1, _str2) AsciiStrCmp((CONST CHAR8 *)(_str1), (CONST CHAR8 *)(_str2))
#define strlen(_str) AsciiStrLen((CONST CHAR8 *)(_str))

size_t strlcpy(char *dst, const char *src, size_t size);

#define scnprintf (u32)AsciiSPrint
#define snprintf  (u32)AsciiSPrint 
#define _snwprintf UnicodeSPrint

#define strhextou64(_str) AsciiStrHexToUint64((CONST CHAR8 *)(_str))

static inline int strncpy_s_c(char *dst, size_t num, const u16 *src)
{
    RETURN_STATUS Status = UnicodeStrToAsciiStrS(src, dst, num);
    if (Status != RETURN_SUCCESS) {
        return -EINVAL;
    }
    return 0;
}

/* stdlibc implementation */
static inline int isspace(int c)
{
    return c == ' ' || (unsigned)c - '\t' < 5;
}

/* arithmetic */
static inline u32 abs(s32 arg)
{
    if (arg >= 0)
        return (u32)(arg);
    else
        return (u32)(-arg);
}

static inline u32 prandom_u32(void)   // :TODO::
{
    static u32 rand = 9;

    rand += 7;
    return rand;
}

#endif // !__QDF_STDIO_H

