/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include <stdint.h>
#include <scmi_packet.h>
#include "platform_hal.h"

/**
 * plat_write_output_payload_word_at_offset - Write to SCMI payload with offset
 * @packet: Pointer to scmi_packet_t instance
 * @data: Data to be written (32-bits)
 * @offset: Offset within payload where @data needs to be written
 *
 * This function populates the SCMI response payload with @data,
 * at a word offset of @offset.
 *
 */
void __attribute__((weak))
plat_write_output_payload_word_at_offset(scmi_packet_t *packet, uint32_t data,
					 int offset)
{
	*((uint32_t *)(packet->payload) + offset) = data;
	packet->len += 4;
}

/**
 * plat_write_output_payload_word - Append SCMI payload with 32-bit data
 * @packet: Pointer to scmi_packet_t instance
 * @data: Data to be written (32-bits)
 *
 * This function appends the SCMI response payload with @data.
 *
 */
void __attribute__((weak))
plat_write_output_payload_word(scmi_packet_t *packet, uint32_t data)
{
	*((uint32_t *)(packet->payload) + ((packet->len - 4 + 3) / 4)) = data;
	packet->len += 4;
}

/**
 * plat_get_input_payload_char_at_offset - Get input payload data with
 *                                    byte offset
 * @packet: Pointer to scmi_packet_t instance
 * @offset: Byte offset
 *
 * This function returns 32-bit data that resides in the input
 * payload at a byte offset of @offset.
 *
 */
uint32_t __attribute__((weak))
plat_get_input_payload_char_at_offset(scmi_packet_t *packet, int offset)
{
	return *(uint32_t *)(packet->payload + offset);
}

/**
 * plat_get_input_payload_word_at_offset - Get input payload data with
 *                                    word offset
 * @packet: Pointer to scmi_packet_t instance
 * @offset: Word offset
 *
 * This function returns 32-bit data that resides in the input
 * payload at a word offset of @offset.
 *
 */
uint32_t __attribute__((weak))
plat_get_input_payload_word_at_offset(scmi_packet_t *packet, int offset)
{
	return *((uint32_t *)(packet->payload) + offset);
}
