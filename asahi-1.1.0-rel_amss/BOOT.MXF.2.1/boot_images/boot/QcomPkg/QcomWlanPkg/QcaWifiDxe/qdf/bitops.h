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

#ifndef __QDF_BITOPS_H
#define __QDF_BITOPS_H

#include <qdf/base_type.h>
#include <qdf/stdio.h>
#include <qdf/pr_debug.h>

 /* BIT Defines */
#define BIT(nr)			((1UL) << (nr))

#define BITS_PER_BYTE          8
#define BITS_PER_LONG          32
#define BITS_PER_LONG_LONG     64

#define BITS_PER_TYPE(_type)	(sizeof(_type) * BITS_PER_BYTE)

#define BITS_TO_LONGS(n)	howmany((n), BITS_PER_LONG)

#define	GENMASK(h, l)       (((MAX_UINT32) >> (32 - (h) - 1)) & ((MAX_UINT32) << (l)))
#define	GENMASK_ULL(h, l)	(((MAX_UINT64) >> (64 - (h) - 1)) & ((MAX_UINT64) << (l)))

/* BITMAP */
#define DECLARE_BITMAP(_name, _bits) \
	unsigned long _name[BITS_TO_LONGS(_bits)]

static inline void bitmap_zero(unsigned long *dst, unsigned int nbits)
{
    unsigned int len = BITS_TO_LONGS(nbits) * sizeof(unsigned long);
    memset(dst, 0, len);
}

static inline void set_bit(u32 pos, void *data)
{
    ((u8*)data)[pos / 8] |= BIT(pos % 8);
}

static inline u8 test_bit(u32 pos, void *data)
{
    return !!(((u8*)data)[pos / 8] & BIT(pos % 8));
}

static inline void clear_bit(u32 pos, void *data)
{
    ((u8*)data)[pos / 8] &= ~BIT(pos % 8);
}

static inline u8 test_and_clear_bit(u32 pos, void *data)
{
    u8 old = test_bit(pos, data);
    clear_bit(pos, data);
    return old;
}

/* return bits 0-31 of a number */
#define lower_32_bits(n) ((u32)(n))

/* return bits 32-63 of a number */
#define upper_32_bits(n) ((u32)(((n) >> 16) >> 16))

/*********************************************/
/*
 * Population count algorithm using SWAR approach
 * - "SIMD Within A Register".
 */
static __inline u8
__bitcount8(u8 _x)
{
    _x = (_x & 0x55) + ((_x & 0xaa) >> 1);
    _x = (_x & 0x33) + ((_x & 0xcc) >> 2);
    _x = (_x + (_x >> 4)) & 0x0f;
    return (_x);
}

static __inline u16
__bitcount16(u16 _x)
{
    _x = (_x & 0x5555) + ((_x & 0xaaaa) >> 1);
    _x = (_x & 0x3333) + ((_x & 0xcccc) >> 2);
    _x = (_x + (_x >> 4)) & 0x0f0f;
    _x = (_x + (_x >> 8)) & 0x00ff;
    return (_x);
}

static __inline u32
__bitcount32(u32 _x)
{
    _x = (_x & 0x55555555) + ((_x & 0xaaaaaaaa) >> 1);
    _x = (_x & 0x33333333) + ((_x & 0xcccccccc) >> 2);
    _x = (_x + (_x >> 4)) & 0x0f0f0f0f;
    _x = (_x + (_x >> 8));
    _x = (_x + (_x >> 16)) & 0x000000ff;
    return (_x);
}

static __inline u64
__bitcount64(u64 _x)
{
    _x = (_x & 0x5555555555555555) + ((_x & 0xaaaaaaaaaaaaaaaa) >> 1);
    _x = (_x & 0x3333333333333333) + ((_x & 0xcccccccccccccccc) >> 2);
    _x = (_x + (_x >> 4)) & 0x0f0f0f0f0f0f0f0f;
    _x = (_x + (_x >> 8));
    _x = (_x + (_x >> 16));
    _x = (_x + (_x >> 32)) & 0x000000ff;
    return (_x);
}

#define	hweight8(x)     __bitcount8((u8)(x))
#define	hweight16(x)    __bitcount16(x)
#define	hweight32(x)    __bitcount32(x)
#define	hweight64(x)    __bitcount64(x)

/*********************************************/
/* find first set bit */
static inline int __ffsl(unsigned long x)
{
    int bit = 0;

#if BITS_PER_LONG == 64
    if ((x & 0xffffffff) == 0) {
        bit += 32;
        x >>= 32;
    }
#endif
    if ((x & 0xffff) == 0) {
        bit += 16;
        x >>= 16;
    }
    if ((x & 0xff) == 0) {
        bit += 8;
        x >>= 8;
    }
    if ((x & 0xf) == 0) {
        bit += 4;
        x >>= 4;
    }
    if ((x & 0x3) == 0) {
        bit += 2;
        x >>= 2;
    }
    if ((x & 0x1) == 0)
        bit += 1;
    return bit;
}

/* find last set bit */
static inline unsigned long __flsl(unsigned long x)
{
    int bit = BITS_PER_LONG - 1;

#if BITS_PER_LONG == 64
    if (!(x & (~0ul << 32))) {
        bit -= 32;
        x <<= 32;
    }
#endif
    if (!(x & (~0ul << (BITS_PER_LONG - 16)))) {
        bit -= 16;
        x <<= 16;
    }
    if (!(x & (~0ul << (BITS_PER_LONG - 8)))) {
        bit -= 8;
        x <<= 8;
    }
    if (!(x & (~0ul << (BITS_PER_LONG - 4)))) {
        bit -= 4;
        x <<= 4;
    }
    if (!(x & (~0ul << (BITS_PER_LONG - 2)))) {
        bit -= 2;
        x <<= 2;
    }
    if (!(x & (~0ul << (BITS_PER_LONG - 1))))
        bit -= 1;
    return bit;
}

/* Example:
 *   flsl(0) = 0,
 *   flsl(1) = 1
 *   flsl(0x80000000) = 32
 */
static inline int flsl(unsigned long x)
{
    int bit = 32;

    if (!x) {
        return 0;
    }

    if (!(x & 0xffff0000u)) {
        x <<= 16;
        bit -= 16;
    }
    if (!(x & 0xff000000u)) {
        x <<= 8;
        bit -= 8;
    }
    if (!(x & 0xf0000000u)) {
        x <<= 4;
        bit -= 4;
    }
    if (!(x & 0xc0000000u)) {
        x <<= 2;
        bit -= 2;
    }
    if (!(x & 0x80000000u)) {
        x <<= 1;
        bit -= 1;
    }
    return bit;
}

static inline int __ffs(unsigned long a)
{
    return __ffsl(a);
}

static inline int ffs(unsigned long a)
{
    if (a)
        return __ffsl(a) + 1;
    return 0;
}

/* Return first zero in "a": [0-31], 32 if all bits is 1 */
static inline int ffz(unsigned long a) {
    return __ffsl(~(a));
}

/* find last set bit */
static inline int __fls(unsigned long a)
{
    return __flsl(a);
}

static inline int fls(unsigned long a)
{
    return flsl(a);
}

static inline unsigned long __ffs64(u64 x)
{
#if BITS_PER_LONG == 32
    if (((u32)x) == 0UL)
        return __ffsl((u32)(x >> 32)) + 32;
#elif BITS_PER_LONG != 64
#error BITS_PER_LONG is not 32 or 64
#endif
    return __ffsl((unsigned long)x);
}

/* find bit from a memory region */
unsigned long find_last_bit(const unsigned long *addr, unsigned long size);

unsigned long find_first_bit(const unsigned long *addr, unsigned long size);

static inline unsigned long
roundup_pow_of_two(unsigned long x)
{
    return (1UL << flsl(x - 1));
}

/*********************************************/
/* bitfield.h operations TODOTODO: to remove */
#define FIELD_PREP(_mask, _val)						\
    ((_val) << (ffs(_mask) - 1)) & (_mask)
#define FIELD_GET(_mask, _reg)						\
	(((_reg) & (_mask)) >> (ffs(_mask) - 1))

static u64 __field_multiplier(u64 field)
{
    if ((field | (field - 1)) & ((field | (field - 1)) + 1))
        return 1;
    return field & -(s64)field;
}
static u64 __field_mask(u64 field)
{
    return field / __field_multiplier(field);
}

#define ____MAKE_OP(type,base,to,from)					           \
static __##type type##_encode_bits(base v, base field)	           \
{									                               \
	if ((v) && (v & ~__field_mask(field)))	                       \
		ASSERT(0);					                               \
	return to((v & (type)__field_mask(field)) * (type)__field_multiplier(field));  \
}									                               \
static base type##_get_bits(__##type v, base field)	               \
{								                                   \
	return (from(v) & (type)field)/(type)__field_multiplier(field);  \
}
#define __MAKE_OP(size)							                      \
	____MAKE_OP(le##size,u##size,__cpu_to_le##size,le##size##_to_cpu) \
	____MAKE_OP(be##size,u##size,__cpu_to_be##size,be##size##_to_cpu) \
	____MAKE_OP(u##size,u##size,,)

____MAKE_OP(u8, u8, , )
__MAKE_OP(16)
__MAKE_OP(32)
__MAKE_OP(64)
#undef __MAKE_OP
#undef ____MAKE_OP

#endif // !__QDF_BITOPS_H

