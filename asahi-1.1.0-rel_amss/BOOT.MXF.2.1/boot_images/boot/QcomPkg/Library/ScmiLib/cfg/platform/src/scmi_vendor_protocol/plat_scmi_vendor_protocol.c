/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include <stdint.h>
#include <stddef.h>
#include "scmi_packet.h"
#include "scmi_err.h"
#include "platform_hal.h"
#include "scmi_vendor_protocol.h"

int __attribute__((weak)) plat_scmi_vendor_protocol_version(scmi_packet_t *pkt)
{
	plat_write_output_payload_word(pkt, SCMI_SUCCESS);
	plat_write_output_payload_word(pkt, SCMI_VENDOR_PROTOCOL_VERSION);
	return 0;
}

int __attribute__((weak))
plat_scmi_vendor_protocol_attributes(scmi_packet_t *pkt)
{
	plat_write_output_payload_word(pkt, SCMI_DENIED);
	return 0;
}

int __attribute__((weak))
plat_scmi_vendor_protocol_msg_attributes(scmi_packet_t *pkt)
{
	plat_write_output_payload_word(pkt, SCMI_DENIED);
	return 0;
}
