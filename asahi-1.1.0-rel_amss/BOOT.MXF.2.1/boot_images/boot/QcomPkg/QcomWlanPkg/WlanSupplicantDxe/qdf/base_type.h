/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
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

#ifndef __QDF_BASE_TYPE_H
#define __QDF_BASE_TYPE_H

#include <Uefi.h>

/*************************************************************/
/* types */
#define WPA_TYPES_DEFINED
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

#define ARRAY_LENGTH(_Array) (sizeof(_Array) / sizeof((_Array)[0]))

#endif // !__QDF_BASE_TYPE_H

