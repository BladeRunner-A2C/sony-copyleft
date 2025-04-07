/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#pragma once

#include "scmi_packet.h"

int plat_scmi_vendor_protocol_version(scmi_packet_t *pkt);

int plat_scmi_vendor_protocol_attributes(scmi_packet_t *pkt);

int plat_scmi_vendor_protocol_msg_attributes(scmi_packet_t *pkt);
