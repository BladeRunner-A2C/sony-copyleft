/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include <stdint.h>
#include "scmi_common_message_ids.h"
#include "scmi_err.h"
#include "scmi_base_protocol.h"
#include "scmi_base_protocol_message_ids.h"
#include "scmi_packet.h"
#include "platform_scmi_base_protocol.h"
#include "platform_hal.h"
#include "scmi_common_api.h"

/**
 * handle_scmi_base_protocol_msg - Process SCMI base protocol packet
 * @pkt: Pointer to SCMI packet instance
 *
 * This function handles an SCMI base protocol packet. It performs
 * the following operations:
 *
 * 1. Initialize output payload
 * 2. Retrieve the message ID from the packet header
 * 3. Retrieve information from the input payload (optional)
 * 4. Write the output payload with the error code
 * 5. Write the output payload with the requested data (if valid)
 *
 * Supported message IDs are defined in scmi_base_protocol_message_ids.h.
 *
 * The function returns 0, indicating success.
 *
 */
int handle_scmi_base_protocol_msg(scmi_packet_t *pkt)
{
	scmi_lib_init_payload(pkt);
	int ret = 0;
	switch (pkt->msg_hdr.msg_id) {
	case PROTOCOL_VERSION:
		ret = plat_scmi_base_protocol_version(pkt);
		break;
	case PROTOCOL_ATTRIBUTES:
		ret = plat_scmi_base_protocol_attributes(pkt);
		break;
	case PROTOCOL_MESSAGE_ATTRIBUTES:
		ret = plat_scmi_base_protocol_message_attributes(pkt);
		break;
	case BASE_DISCOVER_VENDOR:
		ret = plat_scmi_base_discover_vendor(pkt);
		break;
	case BASE_DISCOVER_SUB_VENDOR:
		ret = plat_scmi_base_discover_sub_vendor(pkt);
		break;
	case BASE_DISCOVER_IMPLEMENTATION_VERSION:
		ret = plat_scmi_base_discover_implementation_version(pkt);
		break;
	case BASE_DISCOVER_LIST_PROTOCOLS:
		ret = plat_scmi_base_discover_list_protocols(pkt);
		break;
	case BASE_DISCOVER_AGENT:
	    ret = plat_scmi_base_discover_agent(pkt);
	    break;
	case BASE_NOTIFY_ERRORS:
		ret = plat_scmi_base_notify_errors(pkt);
		break;
	case BASE_SET_DEVICE_PERMISSIONS:
		ret = plat_scmi_base_set_device_permissions(pkt);
		break;
	case BASE_SET_PROTOCOL_PERMISSIONS:
		ret = plat_scmi_base_set_protocol_permissions(pkt);
		break;
	case BASE_RESET_AGENT_CONFIGURATION:
		ret = plat_scmi_base_reset_agent_configuration(pkt);
		break;
	default:
		plat_write_output_payload_word_at_offset(
			pkt, SCMI_OPP_NOT_SUPPORTED, 0);
		break;
	}
	return ret;
}
