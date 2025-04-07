/*
 * Copyright (c) 2022-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#pragma once

#include "scmi_packet.h"

#define SCMI_VENDOR_PROTOCOL_VERSION 0x10000
#define VENDOR_PAYLOAD_START_IDX 4
#define VENDOR_PROTOCOL_MESSAGE_HEADER_LENGTH 0x10

/* If not defined in compilation flag keep default to 16 */
#ifndef PLAT_MAX_SCMI_VENDOR_PROTOCOLS
#define PLAT_MAX_SCMI_VENDOR_PROTOCOLS 16
#endif

int handle_scmi_vendor_protocol_msg(scmi_packet_t *);

typedef struct __attribute__((packed, aligned(4))) vendor_protocol_payload {
	uint32_t extended_msg_id;
	uint64_t ascii_algo_id;
	uint32_t param_id;
	char payload[];
} vendor_protocol_payload_t;

typedef int(*scmi_vendor_callback)(uint8_t msg_id, uint8_t param_id,
					 char *payload, uint32_t payload_len, char* out_payload);

typedef struct __scmi_vendor_prot_desc {
	uint32_t prot_id;
	uint64_t algo_str;
	uintptr_t channel_base;
	scmi_vendor_callback cb;
} scmi_vendor_prot_desc;
