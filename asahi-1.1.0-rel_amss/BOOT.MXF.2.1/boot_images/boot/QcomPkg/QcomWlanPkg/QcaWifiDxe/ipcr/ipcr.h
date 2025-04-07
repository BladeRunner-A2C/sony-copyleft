/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
 
/* SPDX-License-Identifier: ISC */
/*
 * Copyright (c) 2021 The Linux Foundation. All rights reserved.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 19/10/21  zxue     new file to bypass the qrtr

=============================================================================*/

#ifndef __IPCR_H__
#define __IPCR_H__

#include <qdf/base_type.h>
#include <qdf/sk_buff.h>

#define IPCR_PORT_CTRL	0xfffffffeu
#define IPCR_PORT_DATA	16384
#define IPCR_PROC_LOCAL	1

#pragma pack(1)
struct ipcr_addr_v1
{
	u32 proc_id;
	u32 port_id;
};

struct ipcr_addr_v2
{
	u16 proc_id;
	u16 port_id;
};

struct ipcr_server {
	u32 service_id;
	u32 instance_id;
	struct ipcr_addr_v1 addr;
};

struct ipcr_client {
	struct ipcr_addr_v1 addr;
};

struct ipcr_ctrl_pkt {
	u32 cmd;

	union {
		struct ipcr_server server;
		struct ipcr_client client;
	}u;
} __packed;
#pragma pack()

enum ipcr_pkt_type {
	IPCR_CONTROL_INVALID = 0,
	IPCR_CONTROL_DATA = 1,
	IPCR_CONTROL_HELLO = 2,
	IPCR_CONTROL_BYE = 3,
	IPCR_CONTROL_NEW_SERVER	= 4,
	IPCR_CONTROL_DEL_SERVER	= 5,
	IPCR_CONTROL_DEL_CLIENT	= 6,
	IPCR_CONTROL_RESUME_TX	= 7,
	IPCR_CONTROL_EXIT = 8,
	IPCR_CONTROL_PING = 9,
	IPCR_CONTROL_NEW_LOOKUP	= 10,
	IPCR_CONTROL_DEL_LOOKUP	= 11,
};

struct ipcr_cb {
	u32 src_proc_id;
	u32 src_port_id;
	u32 dst_proc_id;
	u32 dst_port_id;

	u8 pkt_type;
	u8 ack_rx;
};

void qcom_mhi_interface_init(int (*fn)(struct sk_buff *, void *), void *data);
int qcom_mhi_ipcr_sendmsg(void *pkt, int len, u32 pkt_type, struct ipcr_addr_v1 *to, struct ipcr_addr_v1 *from);

#endif