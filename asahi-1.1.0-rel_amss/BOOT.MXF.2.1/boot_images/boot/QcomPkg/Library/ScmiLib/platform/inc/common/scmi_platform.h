/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#pragma once

#include <stdint.h>
// SCMI packet member offsets
#define SCMI_PACKET_CHANNEL_STATUS_OFFSET (0x4)
#define SCMI_PACKET_MAILBOX_FLAGS_OFFSET (0x10)
#define SCMI_PACKET_PAYLOAD_SIZE_OFFSET (0x14)
#define SCMI_PACKET_HEADER_OFFSET (0x18)
#define SCMI_PACKET_PAYLOAD_STATUS_OFFSET (0x1C)

// List of SCMI message-types
#define SCMI_MSG_TYPE_CMD (0x0)
#define SCMI_MSG_TYPE_DEL_RSP (0x2)
#define SCMI_MSG_TYPE_NOTIF (0x3)

// Mailbox flags field definitions
#define SCMI_MBOX_FLAG_INT_CMD_ENAB_SHFT (0)
#define SCMI_MBOX_FLAG_INT_CMD_ENAB_MASK (0x1)
#define SCMI_MBOX_FLAG_INT_CMD_COMP_VIA_INT (1)
#define SCMI_MBOX_FLAG_INT_CMD_COMP_VIA_POLL (0)

// Channel status
#define CHAN_STAT_CHAN_FREE (1 << 0)
#define CHAN_STAT_CHAN_BUSY (0 << 0)
#define CHAN_STAT_CHAN_ERR (1 << 1)

/*
 * SCMI message header structure
 *
 * This structure represents a single SCMI
 * message header. It contains the following
 * members:
 * @msg_id: Unique 8-bit message identifier
 * @prot_id: Unique 8-bit protocol identifier
 * @msg_type: Type of message (See SCMI specification)
 * @token: Token usage varies with message type. See
 *         SCMI specification for more details.
 *
 */
typedef struct msg_hdr {
	uint32_t msg_id : 8;
	uint32_t msg_type : 2;
	uint32_t prot_id : 8;
	uint32_t token : 10;
	uint32_t res_sbz : 4; // reserved - should be zero
} __attribute__((packed)) msg_hdr_t;

/*
 * SCMI packet structure
 *
 * This structure describes the layout of the shared
 * memory region which is shared between the agent
 * and platform for SCMI based communication. An SCMI
 * packet would conform to the same layout.
 *
 * See the 'Transports' section of the SCMI specification
 * for more details.
 *
 */
typedef struct scmi_packet {
	uint32_t res0;
	uint32_t chan_sts;
	uint64_t res1;
	uint32_t chan_flags;
	uint32_t len;
	msg_hdr_t msg_hdr;
	char payload[];
} scmi_packet_t;

/**
 * scmi_process_packet - Process SCMI pkt
 *
 * This function is used to process the pkt to get
 * the protocol ids and message ids and call the
 * handler functions accordingly.
 */
int scmi_process_packet(scmi_packet_t *packet);

/**
 * scmi_mark_channel_free - Mark the channel status as free
 *
 * This function is to mark the channel status as free
 *
 */
void scmi_mark_channel_free(scmi_packet_t *packet);

/**
 * scmi_send_response_irq - Send the irq to agent
 *
 * This function is used to send the response irq to agent
 *
 */
void scmi_send_response_irq(scmi_packet_t *packet);

/**
 * plat_scmi_send_response_irq - platform specific send irq implementation
 *
 * This function is used to implement platform specific api to send the 
 * response irq 
 *
 */
void plat_scmi_send_response_irq(scmi_packet_t *packet);

//------------------------------SCMI PROTOCOL IDs-----------------------------//
//
// Source:
//   ARM System Control and Management Interface
//   Platform Design Document
//   Section 4.1.2: Message format
//   Table 2: Protocol identifiers
//
//----------------------------------------------------------------------------//
#define SCMI_BASE_PROTOCOL (0x10)
#define SCMI_POWER_DOMAIN_MANAGEMENT_PROTOCOL (0x11)
#define SCMI_SYSTEM_POWER_MANAGEMENT_PROTOCOL (0x12)
#define SCMI_PERFORMANCE_DOMAIN_MANAGEMENT_PROTOCOL (0x13)
#define SCMI_CLOCK_MANAGEMENT_PROTOCOL (0x14)
#define SCMI_SENSOR_MANAGEMENT_PROTOCOL (0x15)
#define SCMI_RESET_DOMAIN_MGMT_PROTOCOL (0x16)
#define SCMI_VOLTAGE_DOMAIN_MGMT_PROTOCOL (0x17)
//----------------------------------------------------------------------------//
//---------------------------SCMI COMMON MESSAGE IDs--------------------------//
//
// Source:
//   ARM System Control and Management Interface
//   Platform Design Document
//   Section 4.1.3: Protocol discovery
//   Table 4: Required messages
//
//----------------------------------------------------------------------------//
#define PROTOCOL_VERSION (0x0)
#define PROTOCOL_ATTRIBUTES (0x1)
#define PROTOCOL_MESSAGE_ATTRIBUTES (0x2)
//----------------------------------------------------------------------------//

//----------------------------SCMI BASE PROTOCOL -----------------------------//
//-----------------------SCMI BASE PROTOCOL MESSAGE IDs-----------------------//
//
// Source:
//   ARM System Control and Management Interface
//   Platform Design Document
//   Section 4.2.1: Base protocol Commands
//
//----------------------------------------------------------------------------//
#define BASE_DISCOVER_VENDOR (0x3)
#define BASE_DISCOVER_SUB_VENDOR (0x4)
#define BASE_DISCOVER_IMPLEMENTATION_VERSION (0x5)
#define BASE_DISCOVER_LIST_PROTOCOLS (0x6)
#define BASE_DISCOVER_AGENT (0x7)
#define BASE_NOTIFY_ERRORS (0x8)
#define BASE_SET_DEVICE_PERMISSIONS (0x9)
#define BASE_SET_PROTOCOL_PERMISSIONS (0xA)
#define BASE_RESET_AGENT_CONFIGURATION (0xB)
//----------------------------------------------------------------------------//
//------------------------SCMI BASE PROTOCOL APIS-----------------------------//

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

//------------------------------------------------------------------------------//
//-------------------SCMI INPUT STRUCTS FOR BASE PROTOCOL MESSAGES--------------//

// BASE_DISCOVER_VENDOR
typedef struct {
	uint32_t skip;
} scmi_base_discover_list_protocols_agent_t;

//----------------------------------------------------------------------------//
//-------------------SCMI RETURN STRUCTS FOR BASE PROTOCOL MESSAGES-----------//
// PROTOCOL_VERSION
typedef struct {
	int32_t status;
	uint32_t version;
} scmi_base_protocol_version_t;

// PROTOCOL_ATTRIBUTES
typedef struct {
	int32_t status;
	uint32_t attributes;
} scmi_base_protocol_attributes_t;

// PROTOCOL_MESSAGE_ATTRIBUTES
typedef struct {
	int32_t status;
	uint32_t attributes;
} scmi_base_protocol_message_attributes_t;

// BASE_DISCOVER_VENDOR
typedef struct {
	int32_t status;
	uint8_t vendor_identifier[16];
} scmi_base_discover_vendor_t;

// BASE_DISCOVER_SUB_VENDOR
typedef struct {
	int32_t status;
	uint8_t vendor_identifier[16];
} scmi_base_discover_sub_vendor_t;

// BASE_DISCOVER_IMPLEMENTATION_VERSION
typedef struct {
	int32_t status;
	uint32_t implementation_version;
} scmi_base_discover_implementation_version_t;

// BASE_DISCOVER_LIST_PROTOCOLS
typedef struct {
	int32_t status;
	uint32_t num_protocols;
	uint32_t protocols;
} scmi_base_discover_list_protocols_t;

// BASE_DISCOVER_AGENT
typedef struct {
	int32_t status;
	uint32_t agent_id;
	uint8_t name[16];
} scmi_base_discover_agent_t;

// BASE_NOTIFY_ERRORS
typedef struct {
	int32_t status;
} scmi_base_notify_errors_t;

// BASE_SET_DEVICE_PERMISSIONS
typedef struct {
	int32_t status;
} scmi_base_set_device_permissions_t;

// BASE_SET_PROTOCOL_PERMISSIONS
typedef struct {
	int32_t status;
} scmi_base_set_protocol_permissions_t;

// BASE_RESET_AGENT_CONFIGURATION
typedef struct {
	int32_t status;
} scmi_base_reset_agent_configutation_t;

//------------------------------------------------------------------------------//

//-------------------SCMI POWER DOMAIN MANAGEMENT PROTOCOL ---------------------//
//-----------SCMI POWER DOMAIN MANAGEMENT PROTOCOL MESSAGE IDs------------------//
//
// Source:
//   ARM System Control and Management Interface
//   Platform Design Document
//   Section 4.3.2: Power Domain Management protocol Commands
//
//----------------------------------------------------------------------------//
#define POWER_DOMAIN_ATTRIBUTES (0x3)
#define POWER_STATE_SET (0x4)
#define POWER_STATE_GET (0x5)
#define POWER_STATE_NOTIFY (0x6)
#define POWER_STATE_CHANGE_REQUESTED_NOTIFY (0x7)

//------------------------- POWER STATE PARAMETER LAYOUT----------- ----------//
#define POWER_STATE_ON 1
#define POWER_STATE_OFF 0
//----------------------------------------------------------------------------//
//-------------------SCMI INPUT STRUCTS FOR POWER DOMAIN PROTOCOL MESSAGES----//

// POWER_DOMAIN_ATTRIBUTES
typedef struct {
	uint32_t domain_id;
} scmi_power_domain_attributes_agent_t;

//POWER_STATE_SET
typedef struct {
	uint32_t flags;
	uint32_t domain_id;
	uint32_t power_state;
} scmi_power_state_set_agent_t;

//POWER_STATE_GET
typedef struct {
	uint32_t domain_id;
} scmi_power_state_get_agent_t;

//POWER_STATE_NOTIFY
typedef struct {
	uint32_t domain_id;
	uint32_t notify_enable;
} scmi_power_state_notify_agent_t;

//POWER_STATE_CHANGE_REQUESTED_NOTIFY
typedef struct {
	uint32_t domain_id;
	uint32_t notify_enable;
} scmi_power_state_request_notify_agent_t;

//POWER_DOMAIN_NAME_GET
typedef struct {
	uint32_t domain_id;
} scmi_power_domain_name_get_agent_t;

//----------------------------------------------------------------------------//
//-------SCMI RETURN STRUCTS FOR POWER DOMAIN MANAGEMENT PROTOCOL MESSAGES ---//

// PROTOCOL_VERSION
typedef struct {
	int32_t status;
	uint32_t version;
} scmi_power_domain_protocol_version_t;

// PROTOCOL_ATTRIBUTES
typedef struct {
	int32_t status;
	uint32_t attributes;
	uint32_t statistics_address_low;
	uint32_t statistics_address_high;
	uint32_t statistics_len;
} scmi_power_domain_protocol_attributes_t;

// PROTOCOL_MESSAGE_ATTRIBUTES
typedef struct {
	int32_t status;
	uint32_t attributes;
} scmi_power_protocol_message_attributes_t;

// POWER_DOMAIN_ATTRIBUTES
typedef struct {
	int32_t status;
	uint32_t attributes;
	uint8_t name[16];
} scmi_power_domain_attributes_t;

// POWER_STATE_SET
typedef struct {
	int32_t status;
} scmi_power_state_set_t;

//POWER_STATE_GET
typedef struct {
	int32_t status;
	uint32_t power_state;
} scmi_power_state_get_t;

// POWER_STATE_NOTIFY
typedef struct {
	int32_t status;
} scmi_power_state_notify_t;

//POWER_STATE_CHANGE_REQUESTED_NOTIFY
typedef struct {
	int32_t status;
} scmi_power_state_request_notify_t;

// POWER STATE and CHANGE REQUEST NOTIFY RESPONSE
typedef struct {
	uint32_t agent_id;
	uint32_t domain_id;
	uint32_t power_state;
} scmi_power_state_notify_response_t;

//POWER_DOMAIN_NAME_GET
typedef struct {
	int32_t status;
	uint32_t flags;
	uint8_t ext_name[64];
} scmi_power_domain_name_get_t;
//----------------------------------------------------------------------------//

//-----------------SCMI POWER DOMAIN MANAGEMENT PROTOCOL APIS-----------------//

int plat_scmi_power_mgmt_protocol_version(scmi_packet_t *pkt);

int plat_scmi_power_mgmt_protocol_attributes(scmi_packet_t *pkt);

int plat_scmi_power_mgmt_protocol_msg_attributes(scmi_packet_t *pkt);

int plat_scmi_power_mgmt_power_dom_attributes(scmi_packet_t *pkt);

int plat_scmi_power_mgmt_describe_rates(scmi_packet_t *pkt);

int plat_scmi_power_mgmt_power_state_get(scmi_packet_t *pkt);

int plat_scmi_power_mgmt_power_state_set(scmi_packet_t *pkt);

int plat_scmi_power_mgmt_power_state_notify(scmi_packet_t *pkt);

int plat_scmi_power_mgmt_power_state_change_requested_notify(scmi_packet_t *pkt);

//----------------------------------------------------------------------------//

//--------------SCMI SYSTEM POWER DOMAIN MANAGEMENT PROTOCOL -----------------//
//-----------SCMI SYSTEM POWER DOMAIN MANAGEMENT PROTOCOL MESSAGE IDs---------//
//
// Source:
//   ARM System Control and Management Interface
//   Platform Design Document
//   Section 4.4.2: System Power management protocol Commands
//
//----------------------------------------------------------------------------//
#define SYSTEM_POWER_STATE_SET (0x3)
#define SYSTEM_POWER_STATE_GET (0x4)
#define SYSTEM_POWER_STATE_NOTIFY (0x5)
//----------------------------------------------------------------------------//
//-------------SCMI SYSTEM POWER DOMAIN MANAGEMENT PROTOCOL APIS--------------//

int plat_scmi_system_power_mgmt_protocol_version(scmi_packet_t *pkt);

int plat_scmi_system_power_mgmt_protocol_attributes(scmi_packet_t *pkt);

int plat_scmi_system_power_mgmt_protocol_msg_attributes(scmi_packet_t *pkt);

int plat_scmi_system_power_mgmt_system_power_state_set(scmi_packet_t *pkt);

int plat_scmi_system_power_mgmt_system_power_state_get(scmi_packet_t *pkt);

int plat_scmi_system_power_mgmt_system_power_state_notify(scmi_packet_t *pkt);

//----------------------------------------------------------------------------//

//-----------------SCMI PERFORMANCE DOMAIN MANAGEMENT PROTOCOL ---------------//
//-----------SCMI PERFORMANCE DOMAIN MANAGEMENT PROTOCOL MESSAGE IDs----------//
//
// Source:
//   ARM System Control and Management Interface
//   Platform Design Document
//   Section 4.5.2: Performance domain management protocol Commands
//
//----------------------------------------------------------------------------//
#define PERFORMANCE_DOMAIN_ATTRIBUTES (0x3)
#define PERFORMANCE_DESCRIBE_LEVELS (0x4)
#define PERFORMANCE_LIMITS_SET (0x5)
#define PERFORMANCE_LIMITS_GET (0x6)
#define PERFORMANCE_LEVEL_SET (0x7)
#define PERFORMANCE_LEVEL_GET (0x8)
#define PERFORMANCE_NOTIFY_LIMITS (0x9)
#define PERFORMANCE_NOTIFY_LEVEL (0xA)
#define PERFORMANCE_DESCRIBE_FASTCHANNEL (0xB)
#define PERFORMANCE_DOMAIN_NAME_GET (0xC)

//----------------------------------------------------------------------------//

//------------SCMI PERFORMANCE DOMAIN MANAGEMENT PROTOCOL Formats -------------//

//----------------------------------------------------------------------------//
//-------------------SCMI INPUT STRUCTS PERF DOMAIN PROTOCOL MESSAGES---------//
//PROTOCOL_MESSAGE_ATTRIBUTES
typedef struct {
	uint32_t message_id;
} scmi_perf_message_attributes_agent_t;

//PERFORMANCE_DOMAIN_ATTRIBUTES
typedef struct {
	uint32_t domain_id;
} scmi_perf_domain_attributes_agent_t;

// PERFORMANCE_DESCRIBE_LEVELS
typedef struct {
	uint32_t domain_id;
	uint32_t level_idx;
} scmi_perf_describe_levels_agent_t;

// PERFORMANCE_LIMITS_SET
typedef struct {
	uint32_t domain_id;
	uint32_t range_max;
	uint32_t range_min;
} scmi_perf_limits_set_agent_t;

// PERFORMANCE_LEVEL_SET
typedef struct {
	uint32_t domain_id;
	uint32_t perf_level;
} scmi_perf_level_set_agent_t;

// PERFORMANCE_LEVEL_GET
typedef struct {
	uint32_t domain_id;
} scmi_perf_level_get_agent_t;

// PERFORMANCE_NOTIFY_{LIMITS/LEVEL}
typedef struct {
	uint32_t domain_id;
	uint32_t notify_enable;
} scmi_perf_notify_agent_t;

// PERFORMANCE_DESCRIBE_FASTCHANNEL
typedef struct {
	uint32_t domain_id;
	uint32_t message_id;
} scmi_perf_describe_fastchannel_agent_t;

// PERFORMANCE_DOMAIN_NAME_GET
typedef struct {
	uint32_t domain_id;
} scmi_perf_domain_name_get_agent_t;

//----------------------------------------------------------------------------//
//-------------------SCMI RETURN STRUCTS PERF DOMAIN PROTOCOL-----------------//
// PROTOCOL_VERSION
typedef struct {
	int32_t status;
	uint32_t version;
} scmi_perf_domain_protocol_version_t;

// PROTOCOL_ATTRIBUTES
typedef struct {
	int32_t status;
	uint32_t attributes;
	uint32_t statistics_address_low;
	uint32_t statistics_address_high;
	uint32_t statistics_len;
} scmi_perf_domain_protocol_attributes_t;

// PROTOCOL_MESSAGE_ATTRIBUTES
typedef struct {
	int32_t status;
	uint32_t attributes;
} scmi_perf_protocol_message_attributes_t;

// PERFORMANCE_DOMAIN_ATTRIBUTES
typedef struct {
	int32_t status;
	uint32_t attributes;
	uint32_t rate_limit;
	uint32_t sustained_freq;
	uint32_t sustained_perf_level;
	uint8_t name[16];
} scmi_perf_domain_attributes_t;

// PERFORMANCE_DESCRIBE_LEVELS
struct __attribute__((packed, aligned(4))) scmi_perf_level_data {
	uint32_t perf_value;
	uint32_t power;
	uint16_t transition_latency;
	uint16_t reserved;
};

typedef struct {
	int32_t status;
	uint32_t num_levels;
	struct scmi_perf_level_data perf_levels[];
} scmi_perf_describe_levels_t;

typedef struct {
	int32_t status;
} scmi_perf_limits_set_t;

//PERFORMANCE_LIMITS_GET
typedef struct {
	int32_t status;
	uint32_t range_max;
	uint32_t range_min;
} scmi_perf_limits_get_t;

// PERFORMANCE_LEVEL_SET
typedef struct {
	int32_t status;
} scmi_perf_level_set_t;

// PERFORMANCE_LEVEL_GET
typedef struct {
	int32_t status;
	uint32_t perf_level;
} scmi_perf_level_get_t;

// PERFORMANCE_NOTIFY_{LIMITS/LEVEL}
typedef struct {
	int32_t status;
} scmi_perf_notify_t;

// PERFORMANCE_DESCRIBE_FASTCHANNEL
typedef struct {
	int32_t status;
	uint32_t attributes;
	uint32_t rate_limit;
	uint32_t chan_addr_low;
	uint32_t chan_addr_high;
	uint32_t chan_size;
	uint32_t doorbell_addr_low;
	uint32_t doorbell_addr_high;
	uint32_t doorbell_set_mask_low;
	uint32_t doorbell_set_mask_high;
	uint32_t doorbell_preserve_mask_low;
	uint32_t doorbell_preserve_mask_high;
} scmi_perf_describe_fastchannel_t;

// PERFORMANCE_DOMAIN_NAME_GET
typedef struct {
	int32_t status;
	uint32_t flags;
	uint8_t name[64];
} scmi_perf_name_get_t;

// PERFORMANCE_LIMITS_CHANGED
typedef struct {
	uint32_t agent_id;
	uint32_t domain_id;
	uint32_t range_max;
	uint32_t range_min;
} scmi_perf_limits_notify_t;

typedef struct {
	uint32_t agent_id;
	uint32_t domain_id;
	uint32_t perf_level;
} scmi_perf_level_notify_t;
//----------------------------------------------------------------------------//

//-------------SCMI PERFORMANCE DOMAIN MANAGEMENT PROTOCOL APIS---------------//

int plat_scmi_perf_dom_mgmt_protocol_version(scmi_packet_t *pkt);

int plat_scmi_perf_dom_mgmt_protocol_attributes(scmi_packet_t *pkt);

int plat_scmi_perf_dom_mgmt_protocol_msg_attributes(scmi_packet_t *pkt);

int plat_scmi_perf_dom_mgmt_perf_dom_attributes(scmi_packet_t *pkt);

int plat_scmi_perf_dom_mgmt_describe_levels(scmi_packet_t *pkt);

int plat_scmi_perf_dom_mgmt_perf_limits_set(scmi_packet_t *pkt);

int plat_scmi_perf_dom_mgmt_perf_limits_get(scmi_packet_t *pkt);

int plat_scmi_perf_dom_mgmt_perf_level_set(scmi_packet_t *pkt);

int plat_scmi_perf_dom_mgmt_perf_level_get(scmi_packet_t *pkt);

int plat_scmi_perf_dom_mgmt_perf_describe_fastchannel(scmi_packet_t *pkt);

//----------------------------------------------------------------------------//

//----------------------------SCMI CLOCK MANAGEMENT PROTOCOL -----------------//
//------------------------SCMI CLOCK MANAGEMENT PROTOCOL MESSAGE IDs----------//
//
// Source:
//   ARM System Control and Management Interface
//   Platform Design Document
//   Section 4.6.2: Clock management protocol Commands
//
//----------------------------------------------------------------------------//
#define CLOCK_ATTRIBUTES (0x3)
#define CLOCK_DESCRIBE_RATES (0x4)
#define CLOCK_RATE_SET (0x5)
#define CLOCK_RATE_GET (0x6)
#define CLOCK_CONFIG_SET (0x7)
//----------------------------------------------------------------------------//
//------------------------SCMI CLOCK MANAGEMENT PROTOCOL APIS-----------------//

int plat_scmi_clk_mgmt_protocol_version(scmi_packet_t *pkt);

int plat_scmi_clk_mgmt_protocol_attributes(scmi_packet_t *pkt);

int plat_scmi_clk_mgmt_protocol_msg_attributes(scmi_packet_t *pkt);

int plat_scmi_clk_mgmt_clk_attributes(scmi_packet_t *pkt);

int plat_scmi_clk_mgmt_describe_rates(scmi_packet_t *pkt);

int plat_scmi_clk_mgmt_clock_rate_get(scmi_packet_t *pkt);

int plat_scmi_clk_mgmt_clock_rate_set(scmi_packet_t *pkt);

int plat_scmi_clk_mgmt_clock_config_set(scmi_packet_t *pkt);

//------------------------------------------------------------------------------//
//------------SCMI INPUT VALUES FOR CLOCK MANAGEMENT PROTOCOL------------------//

// CLOCK_CONFIG_SET
typedef struct {
	uint32_t clock_id;
	uint32_t attributes;
} scmi_clk_mgt_clock_config_set_agent_t;

//------------------------------------------------------------------------------//
//------------SCMI RETURN VALUES FOR CLOCK MANAGEMENT PROTOCOL------------------//

// PROTOCOL_VERSION
typedef struct {
	int32_t status;
	uint32_t version;
} scmi_clk_mgt_protocol_version_t;

// PROTOCOL_ATTRIBUTES
typedef struct {
	int32_t status;
	uint32_t attributes;
} scmi_clk_mgt_protocol_attributes_t;

// PROTOCOL_MESSAGE_ATTRIBUTES
typedef struct {
	int32_t status;
	uint32_t attributes;
} scmi_clk_mgt_protocol_message_attributes_t;

// CLOCK _ATTRIBUTES
typedef struct {
	int32_t status;
	uint32_t attributes;
	uint8_t clock_name[16];
	uint32_t clock_enable_delay;
} scmi_clk_mgt_clock_attributes_t;

// CLOCK_CONFIG_SET
typedef struct {
	int32_t status;
} scmi_clk_mgt_clock_config_set_t;

//------------------------------------------------------------------------------//

//----------------------SCMI SENSOR MANAGEMENT PROTOCOL ------------------------//
//-----------------SCMI SENSOR MANAGEMENT PROTOCOL MESSAGE IDs------------------//
//
// Source:
//   ARM System Control and Management Interface
//   Platform Design Document
//   Section 4.7.2: Sensor management protocol Commands
//
//------------------------------------------------------------------------------//
#define SENSOR_DESCRIPTION_GET (0x3)
#define SENSOR_TRIP_POINT_NOTIFY (0x4)
#define SENSOR_TRIP_POINT_CONFIG (0x5)
#define SENSOR_READING_GET (0x6)
//-------------------------------------------------------------------------------//
//-----------------------SCMI SENSOR MANAGEMENT PROTOCOL APIS--------------------//

int plat_scmi_sensor_mgmt_protocol_version(scmi_packet_t *pkt);

int plat_scmi_sensor_mgmt_protocol_attributes(scmi_packet_t *pkt);

int plat_scmi_sensor_dom_mgmt_protocol_msg_attributes(scmi_packet_t *pkt);

int plat_scmi_sensor_mgmt_sensor_description_get(scmi_packet_t *pkt);

int plat_scmi_sensor_mgmt_sensor_trip_point_notify(scmi_packet_t *pkt);

int plat_scmi_sensor_mgmt_sensor_trip_point_config(scmi_packet_t *pkt);

int plat_scmi_sensor_mgmt_sensor_reading_get(scmi_packet_t *pkt);

//-------------------------------------------------------------------------------//

//---------------SCMI RESET DOMAIN MANAGEMENT PROTOCOL MESSAGE IDs---------------//
//---------------SCMI RESET DOMAIN MANAGEMENT PROTOCOL MESSAGE IDs---------------//
//
// Source:
//   ARM System Control and Management Interface
//   Platform Design Document
//   Section 4.8.2: Reset Domain management protocol Commands
//
//------------------------------------------------------------------------------//
#define RESET_DOMAIN_ATTRIBUTES (0x3)
#define RESET (0x4)
#define RESET_NOTIFY (0x5)
//------------------------------------------------------------------------------//
//---------------SCMI RESET DOMAIN MANAGEMENT PROTOCOL APIS---------------------//

int plat_scmi_reset_dom_mgmt_protocol_version(scmi_packet_t *pkt);

int plat_scmi_reset_dom_mgmt_protocol_attributes(scmi_packet_t *pkt);

int plat_scmi_reset_dom_mgmt_protocol_msg_attributes(scmi_packet_t *pkt);

int plat_scmi_reset_dom_mgmt_reset_dom_attributes(scmi_packet_t *pkt);

int plat_scmi_reset_dom_mgmt_reset(scmi_packet_t *pkt);

int plat_scmi_reset_dom_mgmt_reset_notify(scmi_packet_t *pkt);

//------------------------------------------------------------------------------//

//-------------SCMI VOLTAGE DOMAIN MANAGEMENT PROTOCOL MESSAGE IDs--------------//
//-------------SCMI VOLTAGE DOMAIN MANAGEMENT PROTOCOL MESSAGE IDs--------------//
//
// Source:
//   ARM System Control and Management Interface
//   Platform Design Document
//   Section 4.9.2:  domain management protocol Commands
//
//------------------------------------------------------------------------------//
#define VOLTAGE_DOMAIN_ATTRIBUTES (0x3)
#define VOLTAGE_DESCRIBE_LEVELS (0x4)
#define VOLTAGE_CONFIG_SET (0x5)
#define VOLTAGE_CONFIG_GET (0x6)
#define VOLTAGE_LEVEL_SET (0x7)
#define VOLTAGE_LEVEL_GET (0x8)
//------------------------------------------------------------------------------//
//---------------SCMI VOLTAGE DOMAIN MANAGEMENT PROTOCOL APIS-------------------//

int plat_scmi_voltage_dom_mgmt_protocol_version(scmi_packet_t *pkt);

int plat_scmi_voltage_dom_mgmt_protocol_attributes(scmi_packet_t *pkt);

int plat_scmi_voltage_dom_mgmt_protocol_msg_attributes(scmi_packet_t *pkt);

int plat_scmi_voltage_dom_mgmt_voltage_dom_attributes(scmi_packet_t *pkt);

int plat_scmi_voltage_dom_mgmt_voltage_describe_levels(scmi_packet_t *pkt);

int plat_scmi_voltage_dom_mgmt_voltage_config_set(scmi_packet_t *pkt);

int plat_scmi_voltage_dom_mgmt_voltage_config_get(scmi_packet_t *pkt);

int plat_scmi_voltage_dom_mgmt_voltage_levels_set(scmi_packet_t *pkt);

int plat_scmi_voltage_dom_mgmt_voltage_levels_get(scmi_packet_t *pkt);

//------------------------------------------------------------------------------//

//----------------------SCMI VENDOR MANAGEMENT PROTOCOL ------------------------//
//----------------SCMI VENDOR MANAGEMENT PROTOCOL PROTOCOL IDs------------------//
//
//------------------------------------------------------------------------------//
#define QCOM_SCMI_VENDOR_PROTOCOL (0x80)

//------------------------------------------------------------------------------//

//--------------SCMI VENDOR MANAGEMENT PROTOCOL MESSAGE IDs---------------------//
//
//------------------------------------------------------------------------------//
#define SET_PARAM (0x10)
#define GET_PARAM (0x11)
#define START_ACTIVITY (0x12)
#define STOP_ACTIVITY (0x13)
//------------------------------------------------------------------------------//

//-------------------SCMI RETURN VALUES FOR VENDOR PROTOCOL---------------------//

// PROTOCOL_VERSION
typedef struct {
	int32_t status;
	uint32_t version;
} scmi_vendor_protocol_version_t;

// PROTOCOL_ATTRIBUTES
typedef struct {
	int32_t status;
	uint32_t attributes;
} scmi_vendor_protocol_attributes_t;

// PROTOCOL_MESSAGE_ATTRIBUTES
typedef struct {
	int32_t status;
	uint32_t attributes;
} scmi_vendor_protocol_message_attributes_t;

//------------------------------------------------------------------------------//

#define VENDOR_PAYLOAD_START_IDX 4

#define GET_SCMI_PAYLOAD_START_INDEX(x)                                        \
	((uint32_t *)x - VENDOR_PAYLOAD_START_IDX)

typedef struct __attribute__((packed, aligned(4))) vendor_protocol_payload {
	uint32_t extended_msg_id;
	uint64_t ascii_algo_id;
	uint32_t param_id;
	char payload[];
} vendor_protocol_payload_t;

typedef int (*scmi_vendor_callback)(uint8_t msg_id, uint8_t param_id,
		char *payload, uint32_t payload_len,
		char *out_payload);

int scmi_vendor_register_callback(uint8_t prot_id, uint64_t algo_str,
		scmi_vendor_callback cb,
		uintptr_t channel_base);
//---------------------------------------------------------------------------------//
