/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <qdf/base_type.h>
#include "stdio.h"

void *memset(void *s, int ch, size_t n)
{
    return SetMem(s, n, (u8)ch);
}

size_t strlcpy(char *dst, const char *src, size_t size)
{
    size_t l = 0;
    for (; size > 1 && *src; size--) {
        *dst++ = *src++;
        l++;
    }
    if (size)
        *dst = '\0';
    return l + strlen(src);
}
