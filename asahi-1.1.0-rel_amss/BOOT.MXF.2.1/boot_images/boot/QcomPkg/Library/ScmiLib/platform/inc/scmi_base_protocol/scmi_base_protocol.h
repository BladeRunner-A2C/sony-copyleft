/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#pragma once

#include "scmi_packet.h"

#define SCMI_BASE_PROTOCOL_VERSION (0x20000)

int handle_scmi_base_protocol_msg(scmi_packet_t *packet);
