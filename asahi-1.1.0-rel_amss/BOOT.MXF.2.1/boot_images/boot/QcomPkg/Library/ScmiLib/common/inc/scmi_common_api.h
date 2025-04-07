/*---------------------------------------------------------------------------
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *---------------------------------------------------------------------------*/
#pragma once
#include <scmi_err.h>
#include <scmi_packet.h>

/**
 * scmi_lib_construct_msg_hdr - Construct SCMI packet
 * @msg_id: Message ID
 * @msg_type: Message type (Command/Delayed Response/Notification)
 * @prot_id: Protocol ID
 * @token: Token Field
 *
 * This function constructs and returns an SCMI message header
 * (32-bit) using the @msg_id, @msg_type, @prot_id and @token arguments.
 *
 * Supported message types are defined in scmi_packet.h.
 *
 * Details about the SCMI message header fields can be found in the ARM
 * System Control and Management Interface specification.
 *
 */
static inline msg_hdr_t scmi_lib_construct_msg_hdr(uint32_t msg_id, uint32_t msg_type,
				     uint32_t prot_id, uint32_t token)

{
	msg_hdr_t hdr;
	hdr.msg_id = msg_id;
	hdr.msg_type = msg_type;
	hdr.prot_id = prot_id;
	hdr.token = token;
	hdr.res_sbz = 0;
	return hdr;
}
/**
 * scmi_lib_init_payload - Initialize SCMI payload
 * @packet: Pointer to scmi_packet_t instance
 *
 * This function initializes the SCMI payload before data
 * is written to it.
 *
 */
static inline void scmi_lib_init_payload(scmi_packet_t *packet_address)
{
	packet_address->len = 4;
}

/**
 * scmi_lib_payload_size_check - Check SCMI payload size
 * @payload_size: Size of the payload
 * @shared_mem_size: Size of the shared memory
 *
 * This function checks the payload size against the shared memory size
 *
 */
static inline int scmi_lib_payload_size_check(uint32_t payload_size,
				uint32_t shared_mem_size)
{
	if (payload_size >
	    (shared_mem_size - SCMI_PACKET_PAYLOAD_STATUS_OFFSET))
		return SCMI_SEND_ERR_TX_SIZE;
	return 0;
}
