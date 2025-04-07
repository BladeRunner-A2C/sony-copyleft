#ifndef _DP_SPEC_H_
#define _DP_SPEC_H_
/*! \file */
/*=====================================================================================================
 
  File: dp_spec.h
 
  Header file for DP Spec definitions. Present version used is v1.4  
   
  Copyright (c) 2016-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
====================================================================================================*/

#include "dp_types.h"

/* --------------------------------------------------------------------------------------------------------------------
Enumerated types
---------------------------------------------------------------------------------------------------------------------*/
/* DPCD Version                                                                                                      */
typedef enum
{
  DP_DPCD_MAJORREV_NONE                           = 0,
  DP_DPCD_MAJORREV_1_0,                                                /* DPCD Major Version 1.0                    */
  DP_DPCD_MAJORREV_1_1,                                                /* DPCD Major Version 1.1                    */
  DP_DPCD_MAJORREV_1_2,                                                /* DPCD Major Version 1.2                    */  
  DP_DPCD_MAJORREV_1_3,                                                /* DPCD Major Version 1.3                    */
  DP_DPCD_MAJORREV_1_4,                                                /* DPCD Major Version 1.4                    */
  DP_DPCD_MAJORREV_MAX,
  DP_DPCD_MAJORREV_FORCE_32BIT                    = 0x7FFFFFFF
} DP_DPCDMajorRevType;

/* DPCD Downstream Port, such DP, VGA, DVI, HDMI                                                                     */
typedef enum
{
   DP_DPCD_DOWNSTREAMPORTTYPE_NONE                = 0,
   DP_DPCD_DOWNSTREAMPORTTYPE_DISPLAYPORT,                             /* Downstream port is DisplayPort            */
   DP_DPCD_DOWNSTREAMPORTTYPE_VGA_DVI_I,                               /* Downstream port is VGA/DVI-I              */
   DP_DPCD_DOWNSTREAMPORTTYPE_DVI_HDMI,                                /* Downstream port is DVI/HDMI               */
   DP_DPCD_DOWNSTREAMPORTTYPE_OTHER,                                   /* Downstream port is other type             */
   DP_DPCD_DOWNSTREAMPORTTYPE_MAX,
   DP_DPCD_DOWNSTREAMPORTTYPE_FORCE_32BIT         = 0x7FFFFFFF
} DP_DPCDDownstreamPortTypeType;

/* DPCD capability bits array type                                                                                   */
typedef enum
{
   DP_DPCD_CAP_NONE                               = 0,
   DP_DPCD_CAP_SUPPORT_ENHANCED_FRAME             = DP_BIT(0),        /* The sink supports Enhanced Frame          */
   DP_DPCD_CAP_SUPPORT_TRAININGPATTERN3           = DP_BIT(1),        /* The sink supports Training Pattern 3      */
   DP_DPCD_CAP_MAX_DOWNSPREAD_0_5                 = DP_BIT(2),        /* The sink supports max 0.5 down spread     */
   DP_DPCD_CAP_NO_AUX_HANDSHAKE                   = DP_BIT(3),        /* The sink supports No AUX handshake        */
   DP_DPCD_CAP_DWN_STRM_PORT_PRESENT              = DP_BIT(4),        /* The sink has the down stream port         */
   DP_DPCD_CAP_SUPPORT_FOMRAT_CONVERSION          = DP_BIT(5),        /* The sink can convert the format           */
   DP_DPCD_CAP_DETAILED_CAP_INFO_AVAILABLE        = DP_BIT(6),        /* The sink has detailed CAP info from 0x80  */
   DP_DPCD_CAP_MSA_TIMING_PAR_IGNORED             = DP_BIT(7),        /* The sink don't need MSA to render image   */
   DP_DPCD_CAP_SUPPORT_OUI                        = DP_BIT(8),        /* The sink supports OUI                     */
   DP_DPCD_CAP_PORT0_EDID_PRESENTED               = DP_BIT(9),        /* The sink has EDID in Receiver Port 0      */
   DP_DPCD_CAP_PORT0_USED_FOR_2ND_STREAM          = DP_BIT(10),       /* Receiver Port0 is used for 2nd stream     */
   DP_DPCD_CAP_PORT1_EDID_PRESENTED               = DP_BIT(11),       /* The sink has EDID in Receiver Port 1      */
   DP_DPCD_CAP_PORT1_USED_FOR_2ND_STREAM          = DP_BIT(12),       /* Receiver Port1 is used for 2nd stream     */
   DP_DPCD_CAP_SUPPORT_ASSR                       = DP_BIT(13),       /* The sink supports ASSR                    */
   DP_DPCD_CAP_FORCE_ENHANCED_FRAME               = DP_BIT(14),       /* Will force to use Enhanced Framing,       */
   DP_DPCD_CAP_SUPPORT_VGA_FORCE_LOAD_SENSE       = DP_BIT(15),       /* VGA force load adapter sense mechanism    */
   DP_DPCD_CAP_SUPPORT_ALTERNATE_I2C_PATTERN      = DP_BIT(16),       /* supports alternate I2C patterns           */
   DP_DPCD_CAP_SUPPORT_POST_LT_ADJ_REQ            = DP_BIT(17),       /* supports Post-Link Training Adjust Request*/   
   DP_DPCD_CAP_SUPPORT_TRAININGPATTERN4           = DP_BIT(18),       /* The sink supports Training Pattern 4      */
   DP_DPCD_CAP_5V_DP_PWR                          = DP_BIT(19),       /* Sink capable of producing +4.9 to +5.5V   */
   DP_DPCD_CAP_12V_DP_PWR                         = DP_BIT(20),       /* Sink capable of producing +12V            */
   DP_DPCD_CAP_18V_DP_PWR                         = DP_BIT(21),       /* Sink capable of producing +18V            */
   DP_DPCD_CAP_EXTENDED_RECEIVER_FIELD            = DP_BIT(22),       /* Extended Receive Capability field present */
   DP_DPCD_CAP_SUPPORT_GTC                        = DP_BIT(23),       /* The sink supports GTC feature             */
   DP_DPCD_CAP_SUPPORT_AV_SYNC                    = DP_BIT(24),       /* The sink supports AV sync feature         */
   DP_DPCD_CAP_SUPPORT_VSC_SDP                    = DP_BIT(25),       /* The sink supports VSC SDP extension       */
   DP_DPCD_CAP_SUPPORT_MAX,
   DP_DPCD_CAP_SUPPORT_FORCE_32BIT                = 0x7FFFFFFF
} DP_DPCDCapType;

/*I2C speed control/status bit map.                                                                                */
typedef enum
{
   DP_DPCD_I2CSPEEDCTRL_NONE                      = 0,
   DP_DPCD_I2CSPEEDCTRL_1KBPS,                                         /* I2C at 1Kbps                              */
   DP_DPCD_I2CSPEEDCTRL_5KBPS,                                         /* I2C at 5Kbps                              */
   DP_DPCD_I2CSPEEDCTRL_10KBPS,                                        /* I2C at 10Kbps                             */
   DP_DPCD_I2CSPEEDCTRL_100KBPS,                                       /* I2C at 100Kbps                            */
   DP_DPCD_I2CSPEEDCTRL_400KBPS,                                       /* I2C at 400Kbps                            */
   DP_DPCD_I2CSPEEDCTRL_1MBPS,                                         /* I2C at 1Mbps                              */
   DP_DPCD_I2CSPEEDCTRL_MAX, 
   DP_DPCD_I2CSPEEDCTRL_FORCE_32BIT               = 0x7FFFFFFF
} DP_DPCDI2CSpeedCtrlType;

/* Link Training pattern .                                                                                           */
typedef enum
{
   DP_DPCD_TRAININGPATTERNSET_NONE                = 0,
   DP_DPCD_TRAININGPATTERNSET_PATTERN1,                                /* Link Training pattern 1                   */
   DP_DPCD_TRAININGPATTERNSET_PATTERN2,                                /* Link Training pattern 2                   */
   DP_DPCD_TRAININGPATTERNSET_PATTERN3,                                /* Link Training pattern 3                   */   
   DP_DPCD_TRAININGPATTERNSET_PATTERN4            = 0x7,               /* Link Training pattern 3                   */
   DP_DPCD_TRAININGPATTERNSET_MAX,
   DP_DPCD_TRAININGPATTERNSET_FORCE_32BIT         = 0x7FFFFFFF
} DP_DPCDTrainingPatternSetType;


/* Sink Power State.                                                                                                */
typedef enum
{
   DP_DPCD_POWERSTATE_NONE                        = 0,
   DP_DPCD_POWERSTATE_D0,                                              /* Sink in D0 (power up) state               */
   DP_DPCD_POWERSTATE_D3,                                              /* Sink in D3 (power down) state             */
   DP_DPCD_POWERSTATE_LINK_D3_AUX_D0,                                  /* Mainlink in D3 state, AUX in D0 state     */
   DP_DPCD_POWERSTATE_MAX,
   DP_DPCD_POWERSTATE_FORCE_32BIT                 = 0x7FFFFFFF
} DP_DPCDPowerStateType;

/* Lane state after Link training .                                                                                 */
typedef enum
{
   DP_DPCD_LANE_STATUS_NONE                       = 0,
   DP_DPCD_LANE_STATUS_CR_DONE                    = DP_BIT(0),         /* Clock recovery is done                    */
   DP_DPCD_LANE_STATUS_CHANNEL_EQ_DONE            = DP_BIT(1),         /* Channel Equalization is done              */
   DP_DPCD_LANE_STATUS_SYMBOL_LOCKED              = DP_BIT(2),         /* Symbol is Locked                          */
   DP_DPCD_LANE_STATUS_MAX,
   DP_DPCD_LANE_STATUS_FORCE_32BIT                = 0x7FFFFFFF
} DP_DPCDLaneStatusType;

/* DPCD Status bit array.                                                                                           */
typedef enum
{
   DP_DPCD_BIT_STATUS_NONE                        = 0,
   DP_DPCD_BIT_STATUS_INTERLANE_ALIGN_DONE        = DP_BIT(0),        /* Inter-lane align is done                  */
   DP_DPCD_BIT_STATUS_PORT_STATUS_CHANGED         = DP_BIT(1),        /* Port Status has changed                   */
   DP_DPCD_BIT_STATUS_LINK_STATUS_UPDATED         = DP_BIT(2),        /* Link status is updated                    */
   DP_DPCD_BIT_STATUS_PORT_0_IN_SYNC              = DP_BIT(3),        /* Port 0 is in sync                         */
   DP_DPCD_BIT_STATUS_PORT_1_IN_SYNC              = DP_BIT(4),        /* Port 1 is in sync                         */
   DP_DPCD_BIT_STATUS_SUPPORT_MAX,
   DP_DPCD_BIT_STATUS_SUPPORT_FORCE_32BIT         = 0x7FFFFFFF
} DP_DPCDBitStatusType;

/* PSR version values defined by eDPv1.4  */
typedef enum
{
  DPCD_SPEC_PSR_VERSION_UNSUPPORTED               = 0,
  DPCD_SPEC_PSR_VERSION_1                         = 1,
  DPCD_SPEC_PSR_VERSION_2                         = 2,  
  DPCD_SPEC_PSR_VERSION_FORCE_32BIT               = 0x7FFFFFFF
} DP_PSRVersionType;

/* EDP Brightness bit depth values  */
typedef enum
{
  DPCD_BRIGHTNESS_CONTROL_8BIT                    = 0,
  DPCD_BRIGHTNESS_CONTROL_16BIT,
  DPCD_BRIGHTNESS_CONTROL_MAX,
  DPCD_BRIGHTNESS_CONTROL_FORCE_32BIT             = 0x7FFFFFFF
} DP_BrightnessBitDepthType;

/* EDP General Capability bits array type (701h) */
typedef enum
{
   DP_GENERAL_CAP_NONE                            = 0,
   DP_GENERAL_CAP_TCON_BACKLIGHT_ADJUST           = DP_BIT(0),        /* TCON has brightness or PWM freq control    */
   DP_GENERAL_CAP_BACKLIGHT_PIN_ENABLE            = DP_BIT(1),        /* The sink supports BL enable through pin    */
   DP_GENERAL_CAP_BACKLIGHT_AUX_ENABLE            = DP_BIT(2),        /* The sink supports BL enable register       */
   DP_GENERAL_CAP_PANEL_SELF_TEST_PIN_ENABLE      = DP_BIT(3),        /* The sink supports LCD self test pin        */
   DP_GENERAL_CAP_PANEL_SELF_TEST_AUX_ENABLE      = DP_BIT(4),        /* The sink supports panel self test register */
   DP_GENERAL_CAP_FRC_ENABLE                      = DP_BIT(5),        /* The sink supports FRC enable bit           */
   DP_GENERAL_CAP_COLOR_ENGINE                    = DP_BIT(6),        /* The sink supports Color Engine enable bit  */
   DP_GENERAL_CAP_SET_POWER                       = DP_BIT(7),        /* Panel power can be controlled through reg  */
   DP_GENERAL_CAP_SUPPORT_MAX,
   DP_GENERAL_CAP_SUPPORT_FORCE_32BIT             = 0x7FFFFFFF
} DP_DPCDGeneralCapType;

/* EDP Brightness capability bits array type 701h */
typedef enum
{
   DP_BACKLIGHT_CAP_NONE                          = 0,
   DP_BACKLIGHT_CAP_BRIGHTNESS_PWM_PIN            = DP_BIT(0),        /* The sink supports BL adjust through pin    */
   DP_BACKLIGHT_CAP_BRIGHTNESS_AUX_SET            = DP_BIT(1),        /* The sink supports BL adjust through reg    */
   DP_BACKLIGHT_CAP_BRIGHTNESS_BYTE_COUNT         = DP_BIT(2),        /* The sink supports 16-bit brightness value  */
   DP_BACKLIGHT_CAP_AUX_PWM_PRODUCT               = DP_BIT(3),        /* The sink combines BL from pin and reg      */
   DP_BACKLIGHT_CAP_FREQ_PWM_PIN_PASS_THRU        = DP_BIT(4),        /* The sink directly passes PWM freq from pin */
   DP_BACKLIGHT_CAP_FREQ_AUX_SET                  = DP_BIT(5),        /* The sink supports PWM freq through reg     */
   DP_BACKLIGHT_CAP_DYNAMIC_BACKLIGHT             = DP_BIT(6),        /* The sink supports dynamic BL control       */
   DP_BACKLIGHT_CAP_VBLANK_BACKLIGHT_UPDATE       = DP_BIT(7),        /* The sink supports BL update at vblank      */
   DP_BACKLIGHT_CAP_SUPPORT_MAX,
   DP_BACKLIGHT_CAP_SUPPORT_FORCE_32BIT           = 0x7FFFFFFF
} DP_DPCDBacklightAdjustCapType;

/* DP Receiver Feature Enumeration list from DPCD Extended Cap register at 2210h*/
typedef enum
{
   DP_RX_FEATURE_NONE                             = 0,
   DP_RX_FEATURE_GTC                              = DP_BIT(0),        /* Sink supports Global Time Code                    */
   DP_RX_FEATURE_SST_SDP_SPLIT                    = DP_BIT(1),        /* Sink supports SDP splitting in SST                */
   DP_RX_FEATURE_AV_SYNC                          = DP_BIT(2),        /* Sink supports Audio-to-Video sync                 */
   DP_RX_FEATURE_VSC_SDP_COLORIMETRY              = DP_BIT(3),        /* Sink supports VCS SDP Colorimetry                 */
   DP_RX_FEATURE_VSC_EXT_VESA_SDP                 = DP_BIT(4),        /* Sink supports VSC Extension VESA SDP              */
   DP_RX_FEATURE_VSC_EXT_VESA_SDP_CHAINING        = DP_BIT(5),        /* Sink supports VSC Extension VESA SDP chaining >64 */
   DP_RX_FEATURE_VSC_EXT_CTA_SDP                  = DP_BIT(6),        /* Sink supports VSC Extension CTA SDP               */
   DP_RX_FEATURE_VSC_EXT_CTA_SDP_CHAINING         = DP_BIT(7),        /* Sink supports VSC Extension CTA SDP chaining >64  */
   DP_RX_FEATURE_MAX,                             
   DP_RX_FEATURE_FORCE_32BIT                      = 0x7FFFFFFF
} DP_ExtDPCDRxFeatureType;

/* DP LTTPR Repeater ID */
typedef enum
{
   DP_LTTPR_NO_REPEATER     = 0x0,
   DP_LTTPR_REPEATER1_ID    = 0x1,
   DP_LTTPR_REPEATER2_ID    = 0x2,
   DP_LTTPR_REPEATER3_ID    = 0x3,
   DP_LTTPR_REPEATER4_ID    = 0x4,
   DP_LTTPR_REPEATER5_ID    = 0x5,
   DP_LTTPR_REPEATER6_ID    = 0x6,
   DP_LTTPR_REPEATER7_ID    = 0x7,
   DP_LTTPR_REPEATER8_ID    = 0x8,
   DP_LTTPR_REPEATER_MAX  
} DP_LTTPR_RepeaterIDType;

/* --------------------------------------------------------------------------------------------------------------------
** Macros and Struct
---------------------------------------------------------------------------------------------------------------------*/
/* DPCD version value defined by DPv1.4                                                                              */
#define DPCD_SPEC_REV_MAJOR_1_0                                                   0x10
#define DPCD_SPEC_REV_MAJOR_1_1                                                   0x11
#define DPCD_SPEC_REV_MAJOR_1_2                                                   0x12
#define DPCD_SPEC_REV_MAJOR_1_3                                                   0x13
#define DPCD_SPEC_REV_MAJOR_1_4                                                   0x14

/* Max link rate value defined by DPv1.4                                                                             */
#define DPCD_SPEC_MAX_LINK_RATE_1_62GBPS                                          0x06
#define DPCD_SPEC_MAX_LINK_RATE_2_7GBPS                                           0x0A
#define DPCD_SPEC_MAX_LINK_RATE_5_4GBPS                                           0x14
#define DPCD_SPEC_MAX_LINK_RATE_8_1GBPS                                           0x1E

/* Max lane count value defined by DPv1.4                                                                            */
#define DPCD_SPEC_MAX_LANE_COUNT_MAX_LANE_COUNT_1                                 0x01
#define DPCD_SPEC_MAX_LANE_COUNT_MAX_LANE_COUNT_2                                 0x02
#define DPCD_SPEC_MAX_LANE_COUNT_MAX_LANE_COUNT_4                                 0x04
#define DPCD_SPEC_MAX_LANE_COUNT_MAX_LANE_COUNT_SHFT                              0
#define DPCD_SPEC_MAX_LANE_COUNT_MAX_LANE_COUNT_BMSK                              0x1F
#define DPCD_SPEC_MAX_LANE_COUNT_POST_LT_ADJ_REQ_SUPPORTED_NOT_SUPPORTED          0x00
#define DPCD_SPEC_MAX_LANE_COUNT_POST_LT_ADJ_REQ_SUPPORTED_SUPPORTED              0x01
#define DPCD_SPEC_MAX_LANE_COUNT_POST_LT_ADJ_REQ_SUPPORTED_SHFT                   5
#define DPCD_SPEC_MAX_LANE_COUNT_POST_LT_ADJ_REQ_SUPPORTED_BMSK                   0x01
#define DPCD_SPEC_MAX_LANE_COUNT_TPS3_SUPPORTED_NOT_SUPPORTED                     0x00
#define DPCD_SPEC_MAX_LANE_COUNT_TPS3_SUPPORTED_SUPPORTED                         0x01
#define DPCD_SPEC_MAX_LANE_COUNT_TPS3_SUPPORTED_SHFT                              6
#define DPCD_SPEC_MAX_LANE_COUNT_TPS3_SUPPORTED_BMSK                              0x40

/* Max downspread value defined by DPv1.4                                                                            */
#define DPCD_SPEC_MAX_DOWNSPREAD_TPS4_SUPPORTED_NOT_SUPPORTED                     0x00
#define DPCD_SPEC_MAX_DOWNSPREAD_TPS4_SUPPORTED_SUPPORTED                         0x01
#define DPCD_SPEC_MAX_DOWNSPREAD_TPS4_SUPPORTED_SHFT                              7
#define DPCD_SPEC_MAX_DOWNSPREAD_TPS4_SUPPORTED_BMSK                              0x80
#define DPCD_SPEC_MAX_DOWNSPREAD_NO_AUX_TRANSACTION_LINK_TRAINING_AUX             0x00
#define DPCD_SPEC_MAX_DOWNSPREAD_NO_AUX_TRANSACTION_LINK_TRAINING_NO_AUX          0x01
#define DPCD_SPEC_MAX_DOWNSPREAD_NO_AUX_TRANSACTION_LINK_TRAINING_SHFT            6
#define DPCD_SPEC_MAX_DOWNSPREAD_NO_AUX_TRANSACTION_LINK_TRAINING_BMSK            0x01

/* Down steam port type value defined by DPv1.4                                                                      */
#define DPCD_SPEC_DWN_STRM_PORT_TYPE_DISPLAYPORT                                  0x00
#define DPCD_SPEC_DWN_STRM_PORT_TYPE_VGA_DVI_I                                    0x01
#define DPCD_SPEC_DWN_STRM_PORT_TYPE_DVI_HDMI                                     0x02
#define DPCD_SPEC_DWN_STRM_PORT_TYPE_OTHERS                                       0x03

/* I2C speed value defined by DPv1.4                                                                                 */
#define DPCD_SPEC_I2C_SPEED_CTRL_1KBPS                                            0x01
#define DPCD_SPEC_I2C_SPEED_CTRL_5KBPS                                            0x02
#define DPCD_SPEC_I2C_SPEED_CTRL_10KBPS                                           0x04
#define DPCD_SPEC_I2C_SPEED_CTRL_100KBPS                                          0x08
#define DPCD_SPEC_I2C_SPEED_CTRL_400KBPS                                          0x10
#define DPCD_SPEC_I2C_SPEED_CTRL_1MBPS                                            0x20

/* Link training pattern value defined by DPv1.4                                                                     */
#define DPCD_SPEC_TRAINING_PATTERN_NONE                                           0x00
#define DPCD_SPEC_TRAINING_PATTERN_1                                              0x01
#define DPCD_SPEC_TRAINING_PATTERN_2                                              0x02
#define DPCD_SPEC_TRAINING_PATTERN_3                                              0x03
#define DPCD_SPEC_TRAINING_PATTERN_4                                              0x07

/* Min/Max of voltage swing/pre-emphasis value defined by DPv1.4                                                     */
#define DPCD_SPEC_MIN_VOLTAGE_SWING_LEVEL                                         0
#define DPCD_SPEC_MIN_PRE_EMPHASIS_LEVEL                                          0
#define DPCD_SPEC_MAX_VOLTAGE_SWING_LEVEL                                         3
#define DPCD_SPEC_MAX_PRE_EMPHASIS_LEVEL                                          3

/* Power state value defined by DPv1.4                                                                               */
#define DPCD_SPEC_POWER_STATE_D0                                                  0x1
#define DPCD_SPEC_POWER_STATE_D3                                                  0x2
#define DPCD_SPEC_POWER_STATE_LINK_D3_AUX_D0                                      0x5

/* Max Lane number defined by DPv1.4                                                                                 */
#define MAX_LANE_NUM                                                              4

/* Bit masks defined by DPv1.4                                                                                       */
#define DPCD_SPEC_EN_ENHANCED_FRAME_BMSK                                          0x80
#define DP_SPEC_MSA_MISCO_COLOR_8BPC_BMSK                                         0x20
#define DP_SPEC_MSA_MISCO_SYNC_CLK_BMSK                                           0x01
#define DPCD_SPEC_MAX_SWING_REACHED_BMSK                                          0x4
#define DPCD_SPEC_MAX_PRE_EMPHASIS_REACHED_BMSK                                   0x20
#define DPCD_SPEC_SCRAMBLING_DISABLE_BMSK                                         0x20

/* PSR config values defined by eDPv1.4b                                                                             */
#define DPCD_SPEC_PSR_ENABLE                                                      0x01
#define DPCD_SPEC_PSR_SRC_TX_ACTIVE                                               0x02
#define DPCD_SPEC_PSR_VERIFY_CRC                                                  0x04
#define DPCD_SPEC_I2C_PSR_FRAME_CAPTURE                                           0x08
#define DPCD_SPEC_PSR2_ENABLE                                                     0x40

/* MST mode cap defined by DPv1.4                                                                                    */
#define DPCD_SPEC_MSTM_CAP_MST_CAP_DISABLED                                       0x00
#define DPCD_SPEC_MSTM_CAP_MST_CAP_ENABLED                                        0x01
#define DPCD_SPEC_MSTM_CAP_MST_CAP_BMSK                                           0x01
#define DPCD_SPEC_MSTM_CAP_MST_CAP_SHFT                                           0

/* SST/MST mode control defined by DPv1.4                                                                            */
#define DPCD_SPEC_MSTM_CTRL_MST_EN_SST_MODE                                       0x00
#define DPCD_SPEC_MSTM_CTRL_MST_EN_MST_MODE                                       0x01
#define DPCD_SPEC_MSTM_CTRL_MST_EN_BMSK                                           0x01
#define DPCD_SPEC_MSTM_CTRL_MST_EN_SHFT                                           0

/* FEC configuration defined by DPv1.4                                                                               */
#define DPCD_SPEC_FEC_CONFIGURATION_FEC_READY_NOT_READY                           0x00
#define DPCD_SPEC_FEC_CONFIGURATION_FEC_READY_READY                               0x01
#define DPCD_SPEC_FEC_CONFIGURATION_FEC_READY_BMSK                                0x01
#define DPCD_SPEC_FEC_CONFIGURATION_FEC_READY_SHFT                                0

/* DSC configuration defined by DPv1.4                                                                               */
#define DPCD_SPEC_DSC_SUPPORT_DSC_SUPPORT_NOT_SUPPORTED                           0x00
#define DPCD_SPEC_DSC_SUPPORT_DSC_SUPPORT_SUPPORTED                               0x01
#define DPCD_SPEC_DSC_SUPPORT_DSC_SUPPORT_BMSK                                    0x01
#define DPCD_SPEC_DSC_SUPPORT_DSC_SUPPORT_SHFT                                    0

/* FEC capability defined by DPv1.4                                                                                  */
#define DPCD_SPEC_FEC_CAPABILITY_0_FEC_CAPABLE_NOT_CAPABLE                        0x00
#define DPCD_SPEC_FEC_CAPABILITY_0_FEC_CAPABLE_CAPABLE                            0x01
#define DPCD_SPEC_FEC_CAPABILITY_0_FEC_CAPABLE_BMSK                               0x01
#define DPCD_SPEC_FEC_CAPABILITY_0_FEC_CAPABLE_SHFT                               0

/* FEC capability defined by DPv1.4                                                                                  */
#define DPCD_SPEC_SINK_COUNT_SINK_COUNT_BMSK                                      0x3F
#define DPCD_SPEC_SINK_COUNT_SINK_COUNT_SHFT                                      0

/* LTTPR (LT Tunable Phy Repeater) defined by DP1.4                                                                  */
#define DPCD_SPEC_LTTPR_TRANSPARENT_MODE                                          0x55
#define DPCD_SPEC_LTTPR_NON_TRANSPARENT_MODE                                      0xAA

/* Sink's Advanced Link Power Management(ALPM) DPCD Capability struct, read from DPCD Address 0x2E  */
typedef struct
{
  bool32                          bALPMCapable;                         /* ALPM supported by sink                    */
  bool32                          bStandBySupport;                      /* PM_State 2a(Stand By state) Support      */
} DP_SinkALPMCapType;

/* Sink PSR DPCD Capability struct, read from DPCD Address 0x70-0x71  */
typedef struct
{
  uint32                           uVersion;                            /* PSR supported by sink                     */
  uint32                           uSetupTimeUs;                        /* PSR Setup time                            */
  DP_LinkTrainingType              eLinkTrainingonExit;                 /* Type of link training required on PSR exit*/
} DP_SinkPSRCapType;

/* Sink DPCD Capability struct, read from DPCD Address 0x0000~0x000F                                                 */
typedef struct
{                                                           
   DP_DPCDMajorRevType              eDPCDMajorRev;                      /* Sink DPCD version (Major part)            */
   uint32                           uMaxLinkRateInKhz;                  /* Max Link rate in Khz Sink supports        */
   uint32                           uMaxLaneCount;                      /* Max Lane Number Sink supports             */     
   DP_DPCDCapType                   eDPCDCap;                           /* DPCD Capability Bit array                 */
   uint32                           uNumofRXPorts;                      /* Number of Receiver Port                   */
   DP_DPCDDownstreamPortTypeType    eDwnStreamPortType;                 /* Down Stream Port type                     */
   uint32                           uNumOfDownStreamPorts;              /* Number of Down Stream Port                */
   uint32                           uRXPort0BufferSize;                 /* Receiver Port 0 buffer size               */
   uint32                           uRXPort1BufferSize;                 /* Receiver Port 1 buffer size               */
   DP_DPCDI2CSpeedCtrlType          eI2CSpeedCtrl;                      /* I2C Speed control                         */
   uint32                           uCRTrainingIntervalInUs;            /* Training status check interval for clock recovery       */
   uint32                           uCETrainingIntervalInUs;            /* Training status check interval for channel equalization */
   uint32                           uSleepWakeTimeoutInMs;              /* Min. supported timeout duration in ms     */
   uint32                           uSupportedLinkRatesInKhz[8];        /* List of supported link rates              */
   DP_SinkPSRCapType                sPSRCap;                            /* Panel self-refresh capabilities of sink   */
   bool32                           bMSTCapable;                        /* Multi-stream support                      */
   DP_SinkALPMCapType               sALPMCap;                           /* ALPM Capabilities of sink                 */
   DP_ExtDPCDRxFeatureType          eRxFeatureEnumList;                 /* Extended Cap: Receiver feature enum list  */
   bool32                           bAdaptiveSyncSDPSupport;            /* Extended Cap: Adaptive sync SDP support   */
} DP_DPCDSinkCapType;

/* Sink DPCD Capability Raw data, read from DPCD Address 0x0000~0x000F                                                 */
typedef struct
{                                                           
   uint8                            uDPCDRevision;                      /* Raw Data Byte 0                           */
   uint8                            uMaxLinkRate;                       /* Raw Data Byte 1                           */
   uint8                            uMaxLaneCount;                      /* Raw Data Byte 2                           */     
   uint8                            uMaxDownSpread;                     /* Raw Data Byte 3                           */
   uint8                            uNumofReceiverPorts;                /* Raw Data Byte 4                           */
   uint8                            uDownStreamPortPresent;             /* Raw Data Byte 5                           */
   uint8                            uMainlinkChannelCoding;             /* Raw Data Byte 6                           */
   uint8                            uDownStreamPortCount;               /* Raw Data Byte 7                           */
   uint8                            uReceivePort0Cap0;                  /* Raw Data Byte 8                           */
   uint8                            uReceivePort0Cap1;                  /* Raw Data Byte 9                           */
   uint8                            uReceivePort1Cap0;                  /* Raw Data Byte 10                          */
   uint8                            uReceivePort1Cap1;                  /* Raw Data Byte 11                          */
   uint8                            uI2CSpeedControlCap;                /* Raw Data Byte 12                          */
   uint8                            uEDPConfigurationCap;               /* Raw Data Byte 13                          */
   uint8                            uTrainingAUXRdInterval;             /* Raw Data Byte 14                          */
   uint8                            uAdapterCap;                        /* Raw Data Byte 15                          */
   uint16                           uSupportedRates[8];                 /* Raw Data byte 0x10 to 0x1f                */
} DP_DPCDSinkCapRawDataType;

/* Sink DPCD Link status struct, read from DPCD Address 0x0202~0x0207                                                */
typedef struct
{                                                           
   DP_DPCDLaneStatusType           eLaneStatus[MAX_LANE_NUM];          /* Link Training Status                      */
   DP_DPCDBitStatusType            eLinkStatusBitArray;                /* Other Link Status                         */
   uint32                          uVoltageSwingLevel[MAX_LANE_NUM];   /* requested Voltage Swing level for training*/
   uint32                          uPreEmphasisLevel[MAX_LANE_NUM];    /* requested pre-emphasis level for training */
} DP_DPCDSinkStatusType;


/* Sink DPCD Link status raw data, read from DPCD Address 0x0202~0x0207                                              */
typedef struct
{                                                           
   uint8                            uLaneStatus0_1;                     /* Raw Data Byte 0                           */
   uint8                            uLaneStatus2_3;                     /* Raw Data Byte 1                           */
   uint8                            uLaneAlignStatusUpdated;            /* Raw Data Byte 2                           */
   uint8                            uSinkStatus;                        /* Raw Data Byte 3                           */
   uint8                            uAdjustRequestLane0_1;              /* Raw Data Byte 4                           */
   uint8                            uAdjustRequestLane2_3;              /* Raw Data Byte 5                           */
} DP_DPCDSinkStatusRawDataType;

/* LTTPR DPCD Link status raw data. For repeater1 read from DPCD Address 0xF0030~0xF0034                                 */
typedef struct
{                                                           
   uint8                            uLaneStatus0_1;                     /* Raw Data Byte 0                           */
   uint8                            uLaneStatus2_3;                     /* Raw Data Byte 1                           */
   uint8                            uLaneAlignStatusUpdated;            /* Raw Data Byte 2                           */
   uint8                            uAdjustRequestLane0_1;              /* Raw Data Byte 3                           */
   uint8                            uAdjustRequestLane2_3;              /* Raw Data Byte 4                           */
} DP_DPCDLTTPRStatusRawDataType;

/* Sink DPCD Link symbol status raw data, read from DPCD Address 0x0210~0x0218                                       */
typedef struct
{                                                           
   uint16                           uErrorCountLane0;                   /* Raw Data Bytes 0 and 1                    */
   uint16                           uErrorCountLane1;                   /* Raw Data Bytes 2 and 3                    */
   uint16                           uErrorCountLane2;                   /* Raw Data Bytes 4 and 5                    */
   uint16                           uErrorCountLane3;                   /* Raw Data Bytes 6 and 7                    */
} DP_SinkSymbolStatusType;


/* Defines the EDID Established Timings.                                                                             */
typedef struct 
{
   uint8                            uTimingI;                           /* Established timings table I               */
   uint8                            uTimingII;                          /* Established timings table II              */
   uint8                            uManufacturesTiming;                /* Manufacturer's timings table              */
} DP_EDID_EstablishedTimings;


/* Defines the EDID Standard Timings.                                                                                */
typedef struct 
{
   uint8                            uHorizontalPixels;                  /* Horizontal pixel width                    */
   uint8                            uAspectRatio_Refresh;               /* Aspect ratio and field refresh rate       */
} DP_EDID_StandardTimings;


/* Defines the EDID Detailed Timings.                                                                                */
typedef struct 
{
   uint16                           uPixelClock;
   uint8                            uHPixels;                           /* Low 8 bits of H addressable video pixels  */
   uint8                            uHBlanking;                         /* Low 8 bits of H blanking pixels           */
   uint8                            uHPixels_Blanking;                  /* High 4 bits of H active and blanking      */
   uint8                            uVPixels;                           /* Low 8 bits of V addressable video pixels  */
   uint8                            uVBlanking;                         /* Low 8 bits of V blanking pixels           */
   uint8                            uVPixels_Blanking;                  /* High 4 bits of V active and blanking      */
   uint8                            uHFrontPorch;                       /* Low 8 bits of H front porch               */
   uint8                            uHSyncWidth;                        /* Low 8 bits of H synch width               */
   uint8                            uVFrontPorch_SyncWidth;             /* Low 4 bits of V front porch and sync width*/
   uint8                            uHVPorchSyncWidths;                 /* High 2 bits of V/H porch and sync widths  */
   uint8                            uHImageSize;                        /* Lower 8 bits of video image width         */
   uint8                            uVImageSize;                        /* Lower 8 bits of video image height        */
   uint8                            uHVImageSize;                       /* Upper 4 bits of video image width/height  */
   uint8                            uHBorder;                           /* Horizontal border size                    */
   uint8                            uVBorder;                           /* Vertical border size                      */
   uint8                            uSignalTimingInterface;             /* Detail timing signal information          */
} DP_EDID_DetailedTiming;

/* Defines the EDID Display Descriptor.                                                                              */
typedef struct {
   uint16                           uDescriptorHeader;                  /* 0x0 indicates this is a descriptor block  */
   uint8                            uReserved1;                         /* Reserved                                  */
   uint8                            uTagId;                             /* Indicates the tag for this descriptor     */
   uint8                            uReserved2;                         /* Reserved                                  */
   uint8                            uDescriptor[13];                    /* Descriptor string                         */
} DP_EDID_DisplayDescriptor;

/* Defines the EDID Display Raw data                                                                                 */
typedef struct
{
   uint8                            uHeader[8];                         /* Header (00 FF FF FF FF FF FF 00)          */
   uint16                           uManufacureName;                    /* ID Manufacturer Name                      */
   uint16                           uProductCode;                       /* ID Product Code                           */
   uint32                           uSerialNumber;                      /* 32-bit serial number                      */
   uint8                            uWeekOfManufacture;                 /* Week number                               */
   uint8                            uYearOfManufacture;                 /* Year                                      */
   uint8                            uEdidVersion;                       /* EDID Structure Version                    */
   uint8                            uEdidRevision;                      /* EDID Structure Revision                   */
   uint8                            uVideoInputDefinition;              /* Video Input Definition                    */
   uint8                            uMaxHorizontalImageSize;            /* Horizontal Screen size in cm              */
   uint8                            uMaxVerticalImageSize;              /* Vertical Screen size in cm                */
   uint8                            uDisplayTransferCharacteristic;     /* Display Transfer Characteristic (Gamma)   */
   uint8                            uFeatureSupport;                    /* Feature Support                           */
   uint8                            uRedGreenLowBits;                   /* Rx1 Rx0 Ry1 Ry0 Gx1 Gx0 Gy1Gy0            */
   uint8                            uBlueWhiteLowBits;                  /* Bx1 Bx0 By1 By0 Wx1 Wx0 Wy1 Wy0           */
   uint8                            uRedX;                              /* Red-x Bits 9 - 2                          */
   uint8                            uRedY;                              /* Red-y Bits 9 - 2                          */
   uint8                            uGreenX;                            /* Green-x Bits 9 - 2                        */
   uint8                            uGreenY;                            /* Green-y Bits 9 - 2                        */
   uint8                            uBlueX;                             /* Blue-x Bits 9 - 2                         */
   uint8                            uBlueY;                             /* Blue-y Bits 9 - 2                         */
   uint8                            uWhiteX;                            /* White-x Bits 9 - 2                        */
   uint8                            uWhiteY;                            /* White-x Bits 9 - 2                        */
   DP_EDID_EstablishedTimings       sEstablishedTimings;                /* Established Timings                       */
   DP_EDID_StandardTimings          sStandardTiming[8];                 /* Standard Timings                          */
   DP_EDID_DetailedTiming           sDetailedTiming;                    /* Detailed Timings                          */
   union 
   {
      DP_EDID_DetailedTiming        sDetailedTimings[3];                /* Detailed Timing 2/3/4                     */
      DP_EDID_DisplayDescriptor     sDisplayDescriptors[3];             /* or Display Descriptor                     */
   }EDID_DetailedInfo;
   uint8                            ExtensionFlag;                      /* Number of EDID extension blocks to follow */
   uint8                            Checksum;                           /* Checksum                                  */
} DP_EDIDDataType;


/* Sink DPCD DSC Capability struct, read from DPCD Address 0x0060~0x006F                                             */
typedef struct
{
   bool32                           bSupported;                          /* DSC supported                            */
   uint32                           uMajor;                              /* DSC Version Major                        */
   uint32                           uMinor;                              /* DSC Version Minor                        */
   uint32                           uRCBufferSize;                       /* DSC RC buffer size                       */
   uint32                           uSliceSupported;                     /* DSC Slice supported                      */
   uint32                           uLineBufBitDepth;                    /* DSC Buffer Bit Depth                     */
   bool32                           bBlockPrediction;                    /* DSC Block Prediction Support             */
   uint32                           uMaxBitsPerPixel;                    /* DSCBits per Pixel, u6.4 format           */
   uint32                           uColorFormatCap;                     /* DSC Color format supported               */
   uint32                           uColorDepthCap;                      /* DSC Color Depth supported                */
   uint32                           uPeakThroughputMode0;                /* DSC throughtput mode0, 4:4:4 and 4:2:2   */
   uint32                           uPeakThroughputMode1;                /* DSC throughtput mode1, 4:2:2 and 4:2:0   */
   uint32                           uMaxSliceWidth;                      /* DSC Max Slice Width                      */
   uint32                           uBitsPerPixelIncrement;              /* DSC Bits per Pixel Increment             */
} DP_SinkDSCCapType;

/* Sink DPCD FEC Capability struct, read from DPCD Address 0x009                                                     */
typedef struct
{
   bool32                           bCapable;                            /* FEC supported                            */
   bool32                           bUncorrectedBlockErrorCountCapable;  /* Uncorrected block error count capable    */
   bool32                           bCorrectedBlockErrorCountCapable;    /* Corrected block error count capable      */
   bool32                           bBitErrorCountCapable;               /* Bit error count capable                  */
} DP_SinkFECCapType;

/* Sink DPCD Brightness Capability struct, read from DPCD Address 0x0701~0x0702                                      */
typedef struct
{
   bool32                           bAuxControlCapable;                  /* Brightness can be controlled through AUX */
   DP_BrightnessBitDepthType        eLevelBitDepth;                      /* Only MSB (723h) or both MSB & LSB (722h) */
} DP_SinkBrightnessCapType;

/* Sink DPCD LTTPR Caps 0xF0000-0xF00005                                                                             */
typedef struct
{
   uint32                           uMajor;                              /* LTTPR Major Revision                     */
   uint32                           uMinor;                              /* LTTPR Minor Revision                     */
   uint32                           uMaxLinkRate;                        /* Max link rate of downstream repeaters    */
   uint32                           uRepeaterCount;                      /* Number of repeaters in the downstream    */
   uint32                           uRepeaterMode;                       /* Repeater mode (non/transparent mode)     */
   uint32                           uMaxLaneCount;                       /* Max number of lanes                      */
   uint32                           uExtendedWakeTimeoutRequest;         /* Time required in ms to exit power-savings*/
   uint32                           uExtendedWakeTimeoutGrant;           /* Extend timeout grant request             */
} DP_LTTPRCapType;

#endif //_DP_SPEC_H_
