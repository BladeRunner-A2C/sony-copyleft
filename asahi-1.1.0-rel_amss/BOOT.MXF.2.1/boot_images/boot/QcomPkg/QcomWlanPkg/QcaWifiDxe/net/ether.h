/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
/*-
 * Copyright (c) 2015-2016 Mellanox Technologies, Ltd. All rights reserved.
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

#ifndef __NET_ETHER_H
#define __NET_ETHER_H

#include <qdf/qbase.h>


#define	ETHER_ADDR_LEN		6	/* length of an Ethernet address */
#define	ETHER_TYPE_LEN		2	/* length of the Ethernet type field */
#define	ETHER_HDR_LEN		(ETHER_ADDR_LEN*2+ETHER_TYPE_LEN)

/* FreeBSD LinuxKPI */
#define ETH_ALEN	ETHER_ADDR_LEN
#define ETH_HLEN	ETHER_HDR_LEN

#define ETH_P_AARP	0x80F3		/* Appletalk AARP		*/
#define ETH_P_IPX	0x8137		/* IPX over DIX			*/
 /*
 * Structure of an Ethernet header.
 */
#pragma pack(1)
struct ethhdr {
	unsigned char	h_dest[ETH_ALEN];	/* destination address */
	unsigned char	h_source[ETH_ALEN];	/* source address */
	__be16		    h_proto;		    /* type field */
} /* STRUCT_PACKED */;
#pragma pack()

static inline void
ether_addr_copy(u8 *dst, const u8 *src)
{
    memcpy(dst, src, ETHER_ADDR_LEN);
}

static inline bool
is_zero_ether_addr(const u8 *addr)
{
    return ((addr[0] + addr[1] + addr[2] + addr[3] + addr[4] + addr[5]) == 0x00);
}

static inline bool
is_multicast_ether_addr(const u8 *addr)
{
    return (0x01 & addr[0]);
}

static inline bool
is_broadcast_ether_addr(const u8 * addr)
{
    return ((addr[0] + addr[1] + addr[2] + addr[3] + addr[4] + addr[5]) == (6 * 0xff));
}

static inline bool is_unicast_ether_addr(const u8 *addr)
{
    return !(0x01 & addr[0]);
}

static inline bool
is_valid_ether_addr(const u8 *addr)
{
    return !is_multicast_ether_addr(addr) && !is_zero_ether_addr(addr);
}

static inline bool
ether_addr_equal(const u8 *pa, const u8 *pb)
{
    return (memcmp(pa, pb, ETHER_ADDR_LEN) == 0);
}

static inline void
eth_zero_addr(u8 *pa)
{
    memset(pa, 0, ETHER_ADDR_LEN);
}

#endif //!__NET_ETHER_H

