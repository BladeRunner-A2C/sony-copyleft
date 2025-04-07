#ifndef _DP_TUNNELED_SPEC_H_
#define _DP_TUNNELED_SPEC_H_
/*! \file */
/*=====================================================================================================
 
  File: dp_tunneled_spec.h
 
  Header file for DP Tunneled Spec (USB4) definitions. Present version used is v1.0
   
  Copyright (c) 2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
====================================================================================================*/

#include "dp_types.h"

/* --------------------------------------------------------------------------------------------------------------------
** Enumerated types
---------------------------------------------------------------------------------------------------------------------*/
/* Protocol Adapter Version                                                                                          */
typedef enum
{
  DP_TUNNELED_PROTOCOL_ADAPTER_VERSION_TBT3                    = 0x03,
  DP_TUNNELED_PROTOCOL_ADAPTER_VERSION_1_0                     = 0x04,
  DP_TUNNELED_PROTOCOL_ADAPTER_VERSION_MAX
} DP_TunneledProtocolAdapterVersionType;

/* Maximal DPCD Rev                                                                                                  */
typedef enum
{
  DP_TUNNELED_MAXIMAL_DPCD_REV_1_1                             = 0x00,
  DP_TUNNELED_MAXIMAL_DPCD_REV_1_2                             = 0x01,
  DP_TUNNELED_MAXIMAL_DPCD_REV_1_3                             = 0x02,
  DP_TUNNELED_MAXIMAL_DPCD_REV_1_4a                            = 0x03,
  DP_TUNNELED_MAXIMAL_DPCD_REV_MAX
} DP_TunneledMaximalDPCDRevType;

/* Maximal Link Rate                                                                                                 */
typedef enum
{
  DP_TUNNELED_MAXIMAL_LINK_RATE_1_62                           = 0x00,
  DP_TUNNELED_MAXIMAL_LINK_RATE_2_7                            = 0x01,
  DP_TUNNELED_MAXIMAL_LINK_RATE_5_4                            = 0x02,
  DP_TUNNELED_MAXIMAL_LINK_RATE_8_1                            = 0x03,
  DP_TUNNELED_MAXIMAL_LINK_RATE_MAX
} DP_TunneledMaximalLinkRateType;

/* Maximal Lane Count                                                                                                */
typedef enum
{
  DP_TUNNELED_MAXIMAL_LANE_COUNT_1                             = 0x00,
  DP_TUNNELED_MAXIMAL_LANE_COUNT_2                             = 0x01,
  DP_TUNNELED_MAXIMAL_LANE_COUNT_4                             = 0x02,
  DP_TUNNELED_MAXIMAL_LANE_COUNT_MAX
} DP_TunneledMaximalLaneCountType;

/* MST Capability                                                                                                    */
typedef enum
{
  DP_TUNNELED_MST_CAPABILITY_NOT_SUPPORTED                     = 0x00,
  DP_TUNNELED_MST_CAPABILITY_SUPPORTED                         = 0x01,
  DP_TUNNELED_MST_CAPABILITY_MAX
} DP_TunneledMSTCapabilityType;

/* TPS3 Capability                                                                                                   */
typedef enum
{
  DP_TUNNELED_TPS3_CAPABILITY_NOT_SUPPORTED                    = 0x00,
  DP_TUNNELED_TPS3_CAPABILITY_SUPPORTED                        = 0x01,
  DP_TUNNELED_TPS3_CAPABILITY_MAX
} DP_TunneledTPS3CapabilityType;

/* TPS4 Capability                                                                                                   */
typedef enum
{
  DP_TUNNELED_TPS4_CAPABILITY_NOT_SUPPORTED                    = 0x00,
  DP_TUNNELED_TPS4_CAPABILITY_SUPPORTED                        = 0x01,
  DP_TUNNELED_TPS4_CAPABILITY_MAX
} DP_TunneledTPS4CapabilityType;

/* FEC Not Supported                                                                                                 */
typedef enum
{
  DP_TUNNELED_FEC_NOT_SUPPORTED_SUPPORTED                      = 0x00,
  DP_TUNNELED_FEC_NOT_SUPPORTED_NOT_SUPPORTED                  = 0x01,
  DP_TUNNELED_FEC_NOT_SUPPORTED_MAX
} DP_TunneledFECNotSupportedType;

/* Secondary Split Capability                                                                                        */
typedef enum
{
  DP_TUNNELED_SECONDARY_SPLIT_CAPABILITY_NOT_SUPPORTED         = 0x00,
  DP_TUNNELED_SECONDARY_SPLIT_CAPABILITY_SUPPORTED             = 0x01,
  DP_TUNNELED_SECONDARY_SPLIT_CAPABILITY_MAX
} DP_TunneledSecondarySplitCapabilityType;

/* LTTPR Not Supported                                                                                               */
typedef enum
{
  DP_TUNNELED_LTTPR_NOT_SUPPOTED_CAPABILITY_SUPPORTED          = 0x00,
  DP_TUNNELED_LTTPR_NOT_SUPPOTED_CAPABILITY_NOT_SUPPORTED      = 0x01,
  DP_TUNNELED_LTTPR_NOT_SUPPOTED_CAPABILITY_MAX
} DP_TunneledLTTPRNotSupportedType;

/* DSC Not Supported                                                                                                 */
typedef enum
{
  DP_TUNNELED_DSC_NOT_SUPPOTED_CAPABILITY_SUPPORTED            = 0x00,
  DP_TUNNELED_DSC_NOT_SUPPOTED_CAPABILITY_NOT_SUPPORTED        = 0x01,
  DP_TUNNELED_DSC_NOT_SUPPOTED_CAPABILITY_MAX
} DP_TunneledDSCNotSupportedType;

/* The DP_HostRouterControllerIDType lists all supported DP Tunneling Host Router Controllers                        */
typedef enum
{
  DP_HOSTROUTER_CONTROLLER_ID_NONE                         = 0x00000000,
  DP_HOSTROUTER_CONTROLLER_ID_0,                                               /**< DP Tunneling Host Router Controller 0 */
  DP_HOSTROUTER_CONTROLLER_ID_1,                                               /**< DP Tunneling Host Router Controller 1 */
  DP_HOSTROUTER_CONTROLLER_ID_MAX,
} DP_HostRouterControllerIDType;

/* --------------------------------------------------------------------------------------------------------------------
** Macros and Struct
---------------------------------------------------------------------------------------------------------------------*/
/* Fields of DP_LOCAL_CAP/DP_REMOTE_CAP/DP_COMMON_CAP register in the DP Adapter Configuration Capability section    */
 typedef struct 
{
  DP_TunneledProtocolAdapterVersionType   eProtocolAdapterVersion;
  DP_TunneledMaximalDPCDRevType           eMaximalDPCDRev;
  DP_TunneledMaximalLinkRateType          eMaximalLinkRate;
  DP_TunneledMaximalLaneCountType         eMaximalLaneCount;
  DP_TunneledMSTCapabilityType            eMSTCapability;
  DP_TunneledTPS3CapabilityType           eTPS3Capability;
  DP_TunneledTPS4CapabilityType           eTPS4Capability;
  DP_TunneledFECNotSupportedType          eFECNotSupported;
  DP_TunneledSecondarySplitCapabilityType eSecondarySplitCapability;
  DP_TunneledLTTPRNotSupportedType        eLTTPRNotSupported;
  DP_TunneledDSCNotSupportedType          eDSCNotSupported;
} DP_TunneledDPCapsFieldsType;

#endif //_DP_TUNNELED_SPEC_H_
