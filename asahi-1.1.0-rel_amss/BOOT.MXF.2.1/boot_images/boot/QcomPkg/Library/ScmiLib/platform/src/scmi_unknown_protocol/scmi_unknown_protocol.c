/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include <stdint.h>
#include "scmi_common_message_ids.h"
#include "scmi_err.h"
#include "scmi_packet.h"
#include "platform_hal.h"
#include "scmi_common_api.h"
#include "scmi_unknown_protocol.h"

/**
 * handle_scmi_unknown_protocol - Process unsupported protocol packet
 * @packet: Pointer to SCMI packet instance
 *
 * This function is called when the protocol ID (present in
 * the SCMI message header) does not match with any of the
 * supported SCMI protocol IDs.
 *
 * The function returns 0, indicating success.
 */
int handle_scmi_unknown_protocol(scmi_packet_t *pkt)
{
	scmi_lib_init_payload(pkt);
	int ret = 0;
	switch (pkt->msg_hdr.msg_id) {
	default:
		plat_write_output_payload_word(pkt, SCMI_OPP_NOT_SUPPORTED);
		break;
	}
	return ret;
}