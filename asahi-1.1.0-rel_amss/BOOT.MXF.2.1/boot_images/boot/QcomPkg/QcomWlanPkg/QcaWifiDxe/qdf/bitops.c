/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
/*-
 * Copyright (c) 2010 Isilon Systems, Inc.
 * Copyright (c) 2010 iX Systems, Inc.
 * Copyright (c) 2010 Panasas, Inc.
 * Copyright (c) 2013-2017 Mellanox Technologies, Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD$
 */
 
/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include "bitops.h"

#define	BITMAP_LAST_WORD_MASK(n)	(~0UL >> (BITS_PER_LONG - (n)))

unsigned long find_last_bit(const unsigned long *addr, unsigned long size)
{
    long mask;
    int offs;
    int bit;
    int pos;

    pos = size / BITS_PER_LONG;
    offs = size % BITS_PER_LONG;
    bit = BITS_PER_LONG * pos;
    addr += pos;
    if (offs) {
        mask = (*addr) & BITMAP_LAST_WORD_MASK(offs);
        if (mask)
            return (bit + __flsl(mask));
    }
    while (pos--) {
        addr--;
        bit -= BITS_PER_LONG;
        if (*addr)
            return (bit + __flsl(*addr));
    }
    return (size);
}

unsigned long
find_first_bit(const unsigned long *addr, unsigned long size)
{
    long mask;
    int bit;

    for (bit = 0; size >= BITS_PER_LONG;
        size -= BITS_PER_LONG, bit += BITS_PER_LONG, addr++) {
        if (*addr == 0)
            continue;
        return (bit + __ffsl(*addr));
    }
    if (size) {
        mask = (*addr) & BITMAP_LAST_WORD_MASK(size);
        if (mask)
            bit += __ffsl(mask);
        else
            bit += size;
    }
    return (bit);
}