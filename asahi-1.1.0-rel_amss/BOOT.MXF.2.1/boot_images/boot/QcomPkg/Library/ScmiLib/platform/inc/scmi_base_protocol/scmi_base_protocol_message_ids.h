/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#pragma once

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
