/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
/*-
 * Copyright (c) 2010 Isilon Systems, Inc.
 * Copyright (c) 2010 iX Systems, Inc.
 * Copyright (c) 2010 Panasas, Inc.
 * Copyright (c) 2013-2016 Mellanox Technologies, Ltd.
 * Copyright (c) 2014-2015 François Tigeot
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
 26/8/21   zxue     refine code
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QDF_BASE_TYPE_H
#define __QDF_BASE_TYPE_H

#include <Uefi.h>

/*************************************************************/
/* types */

typedef BOOLEAN bool;
typedef UINT8 __u8;
typedef UINT16 __u16;
typedef UINT32 __u32;
typedef UINT64 __u64;
typedef UINT8 u8;
typedef UINT16 u16;
typedef UINT32 u32;
typedef UINT64 u64;

typedef INT8 __s8;
typedef INT16 __s16;
typedef INT32 __s32;
typedef INT64 __s64;

typedef INT8 s8;
typedef INT16 s16;
typedef INT32 s32;
typedef INT64 s64;

typedef UINT16 __le16;
typedef UINT32 __le32;
typedef UINT64 __le64;

typedef UINT16 le16;
typedef UINT32 le32;
typedef UINT64 le64;

typedef UINT16 __be16;
typedef UINT32 __be32;
typedef UINT64 __be64;

typedef UINT16 be16;
typedef UINT32 be32;
typedef UINT64 be64;

typedef UINT8 uint8_t;
typedef UINT16 uint16_t;
typedef UINT32 uint32_t;
typedef UINT64 uint64_t;

typedef INT32 time_t;
typedef UINT64 size_t;
typedef INTN ssize_t;

#if defined(_WIN32)
/* WIN32 is an 32bit platform */
typedef unsigned int uintptr_t;
#elif defined(_WIN64)
typedef unsigned long int uintptr_t;
#elif defined(__aarch64__)
typedef unsigned long int uintptr_t;
#endif

#define false FALSE
#define true  TRUE

typedef UINT64 dma_addr_t;
typedef unsigned int gfp_t;

/* endian */

/* big endian is not supported */
#define CONFIG_CPU_BIG_ENDIAN 0

#define __cpu_to_le16(_v) ((__le16)(_v))
#define __cpu_to_le32(_v) ((__le32)(_v))
#define __cpu_to_le64(_v) ((__le64)(_v))


#define __le16_to_cpu(_v) (_v)
#define __le32_to_cpu(_v) (_v)
#define __le64_to_cpu(_v) (_v)

#define le16_to_cpu(_v) (_v)
#define le32_to_cpu(_v) (_v)
#define le64_to_cpu(_v) (_v)

#define cpu_to_le16(_v) ((__le16)(_v))
#define cpu_to_le32(_v) ((__le32)(_v))
#define cpu_to_le64(_v) ((__le64)(_v))

static inline u16 swab16(u16 val)
{
    return ((val & 0x00ffU) << 8 |
        (val & 0xff00U) >> 8);
}

static inline u32 swab32(u32 val)
{
    return ((val & 0x000000ffUL) << 24 |
        (val & 0x0000ff00UL) << 8 |
        (val & 0x00ff0000UL) >> 8 |
        (val & 0xff000000UL) >> 24);
}

static inline u64 swab64(u64 val)
{
	return  (u64)((val& (u64)0x00000000000000ffULL) << 56) |
		(u64)((val & (u64)0x000000000000ff00ULL) << 40) |
		(u64)((val & (u64)0x0000000000ff0000ULL) << 24) |
		(u64)((val & (u64)0x00000000ff000000ULL) <<  8) |
		(u64)((val & (u64)0x000000ff00000000ULL) >>  8) |
		(u64)((val & (u64)0x0000ff0000000000ULL) >> 24) |
		(u64)((val & (u64)0x00ff000000000000ULL) >> 40) |
		(u64)((val & (u64)0xff00000000000000ULL) >> 56);
}

#define __cpu_to_be64(_v) ((__be64)swab64((_v)))
#define __cpu_to_be32(_v) ((__be32)swab32((_v)))
#define __cpu_to_be16(_v) ((__be16)swab16((_v)))

#define __be64_to_cpu(_v) swab64((__u64)(__be64)(_v))
#define __be32_to_cpu(_v) swab32((__u32)(__be32)(_v))
#define __be16_to_cpu(_v) swab16((__u16)(__be16)(_v))

#define be16_to_cpu(_v) swab16((__u16)(__be16)(_v))
#define be32_to_cpu(_v) swab32((__u32)(__be32)(_v))
#define be64_to_cpu(_v) swab64((__u64)(__be64)(_v))


/*************************************************************/

#define	howmany(x, y)	(((x)+((y)-1))/(y))
#define	roundup(x, y)	((((x)+((y)-1))/(y))*(y))  /* to any y */
#define	roundup2(x, y)	(((x)+((y)-1))&(~((y)-1))) /* if y is powers of two */


/*************************************************************/
/* Alignment */

 /* Macros for Data Alignment : size */
#define	ALIGN(x, y)       roundup2((x), (y))
#define PTR_ALIGN(p, a)   ((u8 *)(ALIGN(((u64)p), (a))))
#define IS_ALIGNED(x, a)  (((x) & ((a) - 1)) == 0)

#define	DIV_ROUND_UP(x, n)	howmany(x, n)

/*************************************************************/
/* Comparison */
#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif
#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

#define min_t(_type, _x, _y) ((_type)(_x) < (_type)(_y) ? (_type)(_x) : (_type)(_y))
#define max_t(_type, _x, _y) ((_type)(_x) > (_type)(_y) ? (_type)(_x) : (_type)(_y))

#define offsetof(_type, _member) ((size_t) &((_type *)0)->_member)
#define container_of(_ptr, _type, _member) ((_type *)((u8*)(_ptr) - offsetof(_type, _member)))
#define struct_size(_ptr, _member, _num) \
	(sizeof(*(_ptr)) + sizeof(*(_ptr)->_member) * (_num))

#define	FIELD_SIZEOF(_t, _f)	((UINTN)sizeof(((_t *)0)->_f))

#define ARRAY_LENGTH(_Array) (sizeof(_Array) / sizeof((_Array)[0]))

/* base device */
struct device {
    u8 type;
};


/* helpers */
int efi_status_to_errno(EFI_STATUS Status);

#endif // !__QDF_BASE_TYPE_H

