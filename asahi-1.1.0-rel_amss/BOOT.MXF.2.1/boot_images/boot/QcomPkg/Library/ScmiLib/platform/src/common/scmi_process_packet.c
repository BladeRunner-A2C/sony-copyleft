/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include "scmi_protocol_ids.h"
#include "scmi_base_protocol.h"
#include "scmi_unknown_protocol.h"
#include "scmi_vendor_protocol.h"
#include "scmi_vendor_protocol_message_ids.h"

/**
 * scmi_process_packet - Process incoming SCMI packet
 * @pkt: Pointer to SCMI packet instance
 *
 * This function is called from process_secure_channels or
 * process_nonsecure_channels.
 *
 * The function parses out the protocol ID from the packet
 * header and invokes the protocol specific APIs in order to
 * handle the SCMI packet (Ex: handle_scmi_base_protocol_msg
 * is called for handling a base protocol packet).
 *
 * Once the packet has been processed, the channel status is
 * marked as free.
 *
 * This function returns 0, indicating success.
 *
 */
int scmi_process_packet(scmi_packet_t *pkt)
{
	int retVal;

	// call the appropriate scmi protocol handler
	switch (pkt->msg_hdr.prot_id) {
	case SCMI_BASE_PROTOCOL:
		retVal = handle_scmi_base_protocol_msg(pkt);
		break;

	case QCOM_SCMI_VENDOR_PROTOCOL:
		retVal = handle_scmi_vendor_protocol_msg(pkt);
		break;

	default:
		retVal = handle_scmi_unknown_protocol(pkt);
		break;
	}

	return retVal;
}

void __attribute__((weak)) plat_scmi_send_response_irq(scmi_packet_t *packet)
{
}

/**
 * scmi_send_response_irq - Send IPC interrupt to agent
 * @packet: Pointer to SCMI packet instance
 *
 * This function is a weak implementation
 *
 */
void scmi_send_response_irq(scmi_packet_t *packet)
{
	if (SCMI_MBOX_FLAG_INT_CMD_COMP_VIA_INT ==
	    (((scmi_packet_t *)packet)->chan_flags &
	     SCMI_MBOX_FLAG_INT_CMD_ENAB_MASK)) {
		plat_scmi_send_response_irq(packet);
	}
}

/**
 * scmi_mark_channel_free - Mark secure SCMI channel as free.
 * @packet: Pointer to SCMI packet instance
 *
 * This function is called from process_nonsecure_channels.
 * This marks secure channel as free. If Scheduler is used then
 * it created a High priority task and pushed to Queue.
 *
 */
void __attribute__((weak)) scmi_mark_channel_free(scmi_packet_t *packet)
{
	packet->chan_sts = CHAN_STAT_CHAN_FREE;
}
