/*
 * Copyright (c) 2019-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#pragma once

#include <stdint.h>

// SCMI packet member offsets
#define SCMI_PACKET_CHANNEL_STATUS_OFFSET (0x4)
#define SCMI_PACKET_MAILBOX_FLAGS_OFFSET (0x10)
#define SCMI_PACKET_PAYLOAD_SIZE_OFFSET (0x14)
#define SCMI_PACKET_HEADER_OFFSET (0x18)
#define SCMI_PACKET_PAYLOAD_STATUS_OFFSET (0x1C)

// List of SCMI message-types
#define SCMI_MSG_TYPE_CMD (0x0)
#define SCMI_MSG_TYPE_DEL_RSP (0x2)
#define SCMI_MSG_TYPE_NOTIF (0x3)

// Mailbox flags field definitions
#define SCMI_MBOX_FLAG_INT_CMD_ENAB_SHFT (0)
#define SCMI_MBOX_FLAG_INT_CMD_ENAB_MASK (0x1)
#define SCMI_MBOX_FLAG_INT_CMD_COMP_VIA_INT (1)
#define SCMI_MBOX_FLAG_INT_CMD_COMP_VIA_POLL (0)

// Channel status
#define CHAN_STAT_CHAN_FREE (1 << 0)
#define CHAN_STAT_CHAN_BUSY (0 << 0)
#define CHAN_STAT_CHAN_ERR (1 << 1)

#define SCMI_MESSAGE_HEADER_LENGTH 0x04

/*
 * SCMI message header structure
 *
 * This structure represents a single SCMI
 * message header. It contains the following
 * members:
 * @msg_id: Unique 8-bit message identifier
 * @prot_id: Unique 8-bit protocol identifier
 * @msg_type: Type of message (See SCMI specification)
 * @token: Token usage varies with message type. See
 *         SCMI specification for more details.
 *
 */
typedef struct msg_hdr {
	uint32_t msg_id : 8;
	uint32_t msg_type : 2;
	uint32_t prot_id : 8;
	uint32_t token : 10;
	uint32_t res_sbz : 4; // reserved - should be zero
} __attribute__((packed)) msg_hdr_t;

/*
 * SCMI packet structure
 *
 * This structure describes the layout of the shared
 * memory region which is shared between the agent
 * and platform for SCMI based communication. An SCMI
 * packet would conform to the same layout.
 *
 * See the 'Transports' section of the SCMI specification
 * for more details.
 *
 */
typedef struct scmi_packet {
	uint32_t res0;
	uint32_t chan_sts;
	uint64_t res1;
	uint32_t chan_flags;
	uint32_t len;
	msg_hdr_t msg_hdr;
	char payload[];
} scmi_packet_t;
