/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#pragma once

int plat_scmi_base_protocol_version(scmi_packet_t *pkt);

int plat_scmi_base_protocol_attributes(scmi_packet_t *pkt);

int plat_scmi_base_protocol_message_attributes(scmi_packet_t *pkt);

int plat_scmi_base_discover_vendor(scmi_packet_t *pkt);

int plat_scmi_base_discover_sub_vendor(scmi_packet_t *pkt);

int plat_scmi_base_discover_implementation_version(scmi_packet_t *pkt);

int plat_scmi_base_discover_list_protocols(scmi_packet_t *pkt);

int plat_scmi_base_discover_agent(scmi_packet_t *pkt);

int plat_scmi_base_notify_errors(scmi_packet_t *pkt);

int plat_scmi_base_set_device_permissions(scmi_packet_t *pkt);

int plat_scmi_base_set_protocol_permissions(scmi_packet_t *pkt);

int plat_scmi_base_reset_agent_configuration(scmi_packet_t *pkt);