/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)limits.h	8.3 (Berkeley) 1/4/94
 * $FreeBSD$
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QDF_LIMITS_H
#define __QDF_LIMITS_H

#include <qdf/base_type.h>

#define USHRT_MAX	0xffff              /* max value for an unsigned short */
#define SHRT_MAX	0x7fff              /* max value for a short */
#define SHRT_MIN	(-0x7fff - 1)	    /* min value for a short */
#define	UINT_MAX	0xffffffff	        /* max value for an unsigned int */
#define INT_MAX		0x7fffffff	        /* max value for an int */
#define INT_MIN		(-0x7fffffff - 1)	/* min value for an int */
#define LONG_MAX	0x7fffffffL         /* max for a long */
#define LONG_MIN	(-0x7fffffffL - 1)  /* min for a long */
#define ULONG_MAX	0xffffffffUL        /* max for an unsigned long */
#define LLONG_MAX	0x7fffffffffffffffLL /* max value for a long long */
#define LLONG_MIN	(-0x7fffffffffffffffLL - 1)  /* min for a long long */
#define ULLONG_MAX	0xffffffffffffffffULL /* max value for an unsigned long long */
#define SIZE_MAX	(~(size_t)0)

#define U8_MAX		((u8)~0U)              /* max value for an unsigned 8 bits integer */
#define U16_MAX		((u16)~0U)             /* max value for an unsigned 16 bits integer */
#define U32_MAX		((u32)~0U)             /* max value for an unsigned 32 bits integer */
#define U64_MAX		((u64)~0ULL)           /* max value for an unsigned 64 bits integer */
#define S8_MAX		((s8)(U8_MAX >> 1))    /* max value for a signed 8 bits integer */
#define S8_MIN		((s8)(-S8_MAX - 1))    /* min value for a signed 8 bits integer */
#define S16_MAX		((s16)(U16_MAX >> 1))  /* max value for a signed 16 bits integer */
#define S16_MIN		((s16)(-S16_MAX - 1))  /* min value for a signed 16 bits integer */
#define S32_MAX		((s32)(U32_MAX >> 1))  /* max value for a signed 32 bits integer */
#define S32_MIN		((s32)(-S32_MAX - 1))  /* min value for a signed 32 bits integer */
#define S64_MAX		((s64)(U64_MAX >> 1))  /* max value for a signed 64 bits integer */
#define S64_MIN		((s64)(-S64_MAX - 1))  /* min value for a signed 64 bits integer */

#endif // !__QDF_LIMITS_H

