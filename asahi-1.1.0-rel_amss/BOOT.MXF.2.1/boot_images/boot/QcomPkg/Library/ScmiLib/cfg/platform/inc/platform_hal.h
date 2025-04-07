/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#pragma once

#include <stdint.h>
#include <scmi_packet.h>

void plat_write_output_payload_word_at_offset(scmi_packet_t *packet,
					      uint32_t data, int offset);
void plat_write_output_payload_word(scmi_packet_t *packet, uint32_t data);
uint32_t plat_get_input_payload_char_at_offset(scmi_packet_t *packet,
					       int offset);
uint32_t plat_get_input_payload_word_at_offset(scmi_packet_t *packet,
					       int offset);
