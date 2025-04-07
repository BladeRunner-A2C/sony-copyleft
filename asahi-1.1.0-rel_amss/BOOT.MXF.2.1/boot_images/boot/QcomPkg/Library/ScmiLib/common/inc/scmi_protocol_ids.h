/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#pragma once
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
