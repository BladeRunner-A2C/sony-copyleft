/*
 * Copyright (c) 2022-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "scmi_common_message_ids.h"
#include "scmi_err.h"
#include "scmi_packet.h"
#include "platform_hal.h"
#include "scmi_common_api.h"
#include "scmi_vendor_protocol.h"
#include "scmi_vendor_protocol_message_ids.h"
#include "platform_scmi_vendor_protocol.h"

static scmi_vendor_prot_desc
	scmi_vendor_prot_list[PLAT_MAX_SCMI_VENDOR_PROTOCOLS];

/**
 * scmi_get_vendor_cb - Get SCMI vendor callback function
 * @prot_id: Protocol ID
 * @msg_id: Message ID
 * @algo_str: Algorithm string
 * 
 * This function checks the SCMI vendor callback list for
 * a callback mapped to @prot_id and @msg_id. If found, it returns a
 * pointer to the callback. If not, it returns NULL.
 *
 */
static scmi_vendor_callback
scmi_get_vendor_cb(uint8_t prot_id, uint64_t algo_str, uintptr_t channel_base)
{
	uint32_t i;
	scmi_vendor_prot_desc *prot = NULL;
	scmi_vendor_callback cb = (scmi_vendor_callback)0;

	for (i = 0; i < PLAT_MAX_SCMI_VENDOR_PROTOCOLS; i++) {
		prot = &scmi_vendor_prot_list[i];
		if ((prot_id == prot->prot_id) &&
		    (algo_str == prot->algo_str) &&
		    (channel_base == prot->channel_base)) {
			cb = prot->cb;
			break;
		}
	}

	return cb;
}

/**
 * scmi_vendor_register_callback - Register SCMI callback
 * @prot_id: Protocol ID
 * @msg_id: Message ID
 * @cb: Pointer to callback function
 *
 * This function is used to register @cb, a callback function
 * of type 'scmi_vendor_callback', with a protocol ID @prot_id and @msg_id.
 *
 */
int scmi_vendor_register_callback(uint8_t prot_id, uint64_t algo_str,
				  scmi_vendor_callback vendor_cb,
				  uintptr_t channel_base)
{
	uint32_t i;
	scmi_vendor_prot_desc *cb_entry;
	bool cb_list_entry = false;
	// ToDo: update the logic to return failure case
	for (i = 0; i < PLAT_MAX_SCMI_VENDOR_PROTOCOLS; i++) {
		cb_entry = &scmi_vendor_prot_list[i];
		if (!cb_entry->cb) {
			cb_entry->prot_id = prot_id;
			cb_entry->algo_str = algo_str;
			cb_entry->cb = vendor_cb;
			cb_entry->channel_base = channel_base;
			cb_list_entry = true;
			break;
		}
	}
	if (cb_list_entry)
		return 0;
	else
		return SCMI_OUT_OF_RANGE;
}

/**
 * handle_scmi_system_vendor_protocol_msg - Process SCMI system power mgmt. protocol packet
 * @pkt: Pointer to SCMI packet instance
 *
 * This function handles an SCMI vendor protocol packet. It performs
 * the following operations:
 *
 * 1. Initialize output payload
 * 2. Retrieve the message ID from the packet header
 * 3. Retrieve information from the input payload (optional)
 * 4. Write the output payload with the error code
 * 5. Write the output payload with the requested data (if valid)
 *
 * Supported message IDs are defined in scmi_vendor_protocol_message_ids.h.
 *
 * The function returns 0, indicating success.
 *
 */

int handle_scmi_vendor_protocol_msg(scmi_packet_t *pkt)
{
	uint32_t handled = 1;
	uint32_t algo_str_high, algo_str_low;
	uint64_t algo_str;
	uint8_t msg_id = pkt->msg_hdr.msg_id;
	uint8_t prot_id = pkt->msg_hdr.prot_id;
	uint32_t param_id = 0;
	uint32_t len = pkt->len;
	scmi_vendor_callback cb;

	scmi_lib_init_payload(pkt);

	int ret = 0, ret_cb;
	switch (msg_id) {
	case PROTOCOL_VERSION:
		ret = plat_scmi_vendor_protocol_version(pkt);
		break;
	case PROTOCOL_ATTRIBUTES:
		ret = plat_scmi_vendor_protocol_attributes(pkt);
		break;
	case PROTOCOL_MESSAGE_ATTRIBUTES:
		ret = plat_scmi_vendor_protocol_msg_attributes(pkt);
		break;
	default:
		algo_str_high = *((uint32_t *)pkt->payload + 2);
		algo_str_low = *((uint32_t *)pkt->payload + 1);
		algo_str = ((uint64_t)algo_str_high << 32 | algo_str_low);
		param_id = plat_get_input_payload_word_at_offset(pkt, 3);

		cb = scmi_get_vendor_cb(prot_id, algo_str, (uintptr_t)pkt);
		if (cb) {
			/* length = len_frm_pkt(len) - msg_hdr(0x04) - vend_proto_hdr(0x10) */
			ret_cb = cb(msg_id, param_id,
				    (char *)((uint32_t *)pkt->payload +
					     VENDOR_PAYLOAD_START_IDX),
				    (len - SCMI_MESSAGE_HEADER_LENGTH -
				     VENDOR_PROTOCOL_MESSAGE_HEADER_LENGTH),
				    (char *)((uint32_t *)pkt->payload));
			if (ret_cb < 0) {
				ret = ret_cb;
			} else {
				pkt->len += ret_cb;
			}
		} else {
			handled = 0;
		}
		if (!handled) {
			plat_write_output_payload_word_at_offset(
				pkt, SCMI_OPP_NOT_SUPPORTED, 0);
		}
	}
	return ret;
}
