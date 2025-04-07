/*=====================================================================================================================
 
  File: dp_dpcd.c
 
  Source file for DP EDID read and parse related functionality 
   
  Copyright (c) 2016-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=======================================================================================================================*/


/*---------------------------------------------------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------------------------------------------------*/
#include "dp_i.h"


#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------------------------------------------------
 * Defines
 *-------------------------------------------------------------------------------------------------------------------*/
#define DPCD_EDP_CONFIGURATION_CAP_LEN                1
#define DPCD_EDP_CONFIGURATION_CAP                    0x0D

#define DPCD_CAP_LEN                                  16
#define DPCD_CAP_START_ADDRESS                        0

#define DPCD_PSR_CAP_LEN                              2
#define DPCD_PSR_CAP_START_ADDRESS                    0x70

#define DPCD_PSR_ENABLE_CONFIG_LEN                    1
#define DPCD_PSR_ENABLE_CONFIG_ADDRESS                0x170

#define DPCD_ALPM_ENABLE_LEN                          1
#define DPCD_ALPM_ENABLE_START_ADDRESS                0x116

#define DPCD_ALPM_CAP_START_ADDRESS                   0x2E
#define DPCD_ALPM_CAP_MASK                            0x1
#define DPCD_ALPM_STANDBY_CAP_MASK                    0x2

#define DPCD_DSC_CAP_LEN                              16
#define DPCD_DSC_CAP_START_ADDRESS                    0x60

#define DPCD_DSC_ENABLE_LEN                           1
#define DPCD_DSC_ENABLE_START_ADDRESS                 0x160

#define DPCD_DSC_STATUS_LEN                           1
#define DPCD_DSC_STATUS_START_ADDRESS                 0x20f

#define DPCD_FEC_CAP_LEN                              1
#define DPCD_FEC_CAP_START_ADDRESS                    0x90

#define DPCD_FEC_CONFIG_LEN                           1
#define DPCD_FEC_CONFIG_START_ADDRESS                 0x120

#define DPCD_FEC_STATUS_LEN                           3
#define DPCD_FEC_STATUS_START_ADDRESS                 0x280

#define DPCD_LINK_STATUS_LEN                          6
#define DPCD_LINK_STATUS_START_ADDRESS                0x202
#define DPCD_LINK_STATUS_LANE23_START_ADDRESS         0x203
#define DPCD_LINK_STATUS_LANEALIGN_START_ADDRESS      0x204

#define DPCD_LINKCONFIG_LEN                           2
#define DPCD_LINKCONFIG_START_ADDRESS                 0x100

#define DPCD_TRAINING_PATTERN_SET_LEN                 1
#define DPCD_TRAINING_PATTERN_SET_START_ADDRESS       0x102

#define DPCD_TRAINING_LANE_SET_LEN                    4
#define DPCD_TRAINING_LANE_SET_START_ADDRESS          0x103  
#define DPCD_TRAINING_LANE1_SET_START_ADDRESS         0x104
#define DPCD_TRAINING_LANE2_SET_START_ADDRESS         0x105
#define DPCD_TRAINING_LANE3_SET_START_ADDRESS         0x106

#define DPCD_LINK_DOWNSPREAD_CTRL_LEN                 1
#define DPCD_LINK_DOWNSPREAD_CTRL_ADDRESS             0x107

#define DPCD_EDP_CONFIGURATION_SET_LEN                1
#define DPCD_EDP_CONFIGURATION_SET                    0x10A

#define DPCD_SET_POWER_STATE_LEN                      1
#define DPCD_SET_POWER_STATE_START_ADDRESS            0x600

#define DPCD_DEVICE_SERVICE_IRQ_VECTOR_LEN            1
#define DPCD_DEVICE_SERVICE_IRQ_VECTOR_ADDRESS        0x201

#define DPCD_AUTOMATED_TEST_REQUEST                   0x2

#define DPCD_TEST_REQUEST_LEN                         1
#define DPCD_TEST_REQUEST_ADDRESS                     0x218

#define DPCD_TEST_RESPONSE_LEN                        1
#define DPCD_TEST_RESPONSE_ADDRESS                    0x260
#define DPCD_TEST_RESPONSE_ACK                        0x01
#define DPCD_TEST_RESPONSE_NAK                        0x02
#define DPCD_TEST_RESPONSE_EDID_CHECKSUM_WRITE        0x04

#define DPCD_TEST_EDID_CHECKSUM_LEN                   1
#define DPCD_TEST_EDID_CHECKSUM_ADDRESS               0x261

#define DPCD_SINK_STATUS_LEN                          8
#define DPCD_SINK_STATUS_ADDRESS                      0x200
#define DPCD_SINK_STATUS_CP_READY_MASK                0x40

#define DPCD_SINK_SYMBOL_STATUS_ADDRESS               0x210
#define DPCD_SINK_SYMBOL_STATUS2_ADDRESS              0x211

#define DPCD_LANE_STATUS_DS_PORT_STATUS_MASK          0x40
#define DPCD_TEST_LINK_RATE_LEN                       1
#define DPCD_TEST_LINK_RATE_ADDRESS                   0x219

#define DPCD_TEST_LANE_COUNT_LEN                      1
#define DPCD_TEST_LANE_COUNT_ADDRESS                  0x220

#define DPCD_TEST_BIT_DEPTH_LEN                       1
#define DPCD_TEST_BIT_DEPTH_ADDRESS                   0x232

#define DPCD_TEST_LINK_SWING_LEN                      1
#define DPCD_TEST_LINK_SWING_ADDRESS                  0x206
#define DPCD_TEST_LINK_LANE23_SWING_ADDRESS           0x207

#define DPCD_TEST_MISC_BIT_DEPTH_BMSK                 0xE0
#define DPCD_TEST_MISC_BIT_DEPTH_SHFT                 5

#define DPCD_TEST_MISC_BIT_DEPTH_6BPP                 0x0
#define DPCD_TEST_MISC_BIT_DEPTH_8BPP                 0x1
#define DPCD_TEST_MISC_BIT_DEPTH_10BPP                0x2
#define DPCD_TEST_MISC_BIT_DEPTH_12BPP                0x3
#define DPCD_TEST_MISC_BIT_DEPTH_16BPP                0x4

#define DPCD_TEST_PHY_TEST_PATTERN_LEN                1
#define DPCD_TEST_PHY_TEST_PATTERN_ADDRESS            0x248

#define DPCD_PSR_ERROR_LEN                            5
#define DPCD_PSR_ERROR_START_ADDRESS                  0x2006

#define DPCD_PSR_CRC_LEN                              6
#define DPCD_PSR_CRC_START_ADDRESS                    0x240

#define DPCD_EXTENDED_CAP_START_ADDRESS               0x2200

#define DPCD_MST_CAP_START_ADDRESS                    0x21

#define DPCD_GUID_LEN                                 16    /* 16 byte GUID */
#define DPCD_GUID_START_ADDRESS                       0x30

#define DPCD_DEVICE_SPECIFIC_LEN                      12    /* including IEEE_OUI code, Device Identification String, and HW/FW reversion */
#define DPCD_SOURCE_IEEE_OUI_START_ADDRESS            0x300
#define DPCD_SINK_IEEE_OUI_START_ADDRESS              0x400                 
#define DPCD_BRANCH_IEEE_OUI_START_ADDRESS            0x500                    

/* Max loop count to poll if sink link status is stable*/
#define DPCD_LINK_STATUS_CHECK_UPDATE_LOOP            100

#define DPCD_LINK_RATE_TABLE_LENGTH                   8     /* Size of rate table for eDP */

#define DSC_MAJOR_VERSION_SUPPORT_MIN                 1
#define DSC_MAJOR_VERSION_SUPPORT_MAX                 1
#define DSC_MINOR_VERSION_SUPPORT_MIN                 1
#define DSC_MINOR_VERSION_SUPPORT_MAX                 2

/* EDP Brightness caps */
#define DPCD_BRIGHTNESS_CAP_LEN                       2
#define DPCD_BRIGHTNESS_CAP_START_ADDRESS             0x701

#define DPCD_DISPLAY_CONTROL_LEN                      1
#define DPCD_DISPLAY_CONTROL_START_ADDRESS            0x720
#define DPCD_BACKLIGHT_ENABLE_MASK                    0x1

#define DPCD_BACKLIGHT_MODE_LEN                       1
#define DPCD_BACKLIGHT_MODE_START_ADDRESS             0x721
#define DPCD_BACKLIGHT_BRIGHTNESS_CTRL_MODE_MASK      0x3
#define DPCD_BACKLIGHT_BRIGHTNESS_CTRL_BY_REG         0x2

#define DPCD_BACKLIGHT_BRIGHTNESS_MSB_ADDRESS         0x722
#define DPCD_BACKLIGHT_BRIGHTNESS_LSB_ADDRESS         0x723

#define DPCD_BACKLIGHT_BRIGHTNESS_CUSTOM1_ADDRESS     0x320
#define DPCD_BACKLIGHT_BRIGHTNESS_CUSTOM2_ADDRESS     0x354

#define DPCD_BACKLIGHT_BRIGHTNESS_CUSTOM1_SIZE        4
#define DPCD_BACKLIGHT_BRIGHTNESS_CUSTOM2_SIZE        4

#define DPCD_BACKLIGHT_BRIGHTNESS_8BIT_MAX            0xFF
#define DPCD_BACKLIGHT_BRIGHTNESS_16BIT_MAX           0x7FF

/* DP Standard Link Rate in kHz per lane */
#define DPCD_RBR_LINK_RATE                            162000
#define DPCD_HBR_LINK_RATE                            270000
#define DPCD_HBR2_LINK_RATE                           540000
#define DPCD_HBR3_LINK_RATE                           810000

/* Mask to check if EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT (bit 7) in TRAINING_AUX_RD_INTERVAL register(DPCD 000Eh) is set */
#define DPCD_EXTENDED_CAP_AVAILABLE_BMSK              0x80  

#define DPCD_EXCLUSIVE_EXT_CAP_START_ADDRESS          0x2210
#define DPCD_EXCLUSIVE_EXT_CAP_LEN                    5

/* Mask to check if ADAPTIVE_SYNC_SDP_SUPPORTED (bit 0) in ADAPTIVE_SYNC_CAPABILITY register (DPCD 2214h) is set*/
#define DPCD_ADAPTIVE_SYNC_SDP_BMSK                   0x1

/* LTTPR (LT Tunable Phy Repeaters) */
#define DPCD_LTTPR_CAPS_LEN                           6
#define DPCD_LTTPR_CAPS_START_ADDRESS                 0xF0000

#define DPCD_LTTPR_MAJOR_VERSION_SUPPORT_MIN          1
#define DPCD_LTTPR_MINOR_VERSION_SUPPORT_MIN          4

#define DPCD_LTTPR_REPEATER1_DEVICE_ID_LEN            9
#define DPCD_LTTPR_REPEATER1_DEVICE_ID_START_ADDRESS  0xF003D

#define DPCD_LTTPR_REPEATER1_CONFIG_ADDRESS           0xF0010
#define DPCD_LTTPR_REPEATER2_CONFIG_ADDRESS           0xF0060
#define DPCD_LTTPR_REPEATER3_CONFIG_ADDRESS           0xF00B0
#define DPCD_LTTPR_REPEATER4_CONFIG_ADDRESS           0xF0100
#define DPCD_LTTPR_REPEATER5_CONFIG_ADDRESS           0xF0150
#define DPCD_LTTPR_REPEATER6_CONFIG_ADDRESS           0xF01A0
#define DPCD_LTTPR_REPEATER7_CONFIG_ADDRESS           0xF01F0
#define DPCD_LTTPR_REPEATER8_CONFIG_ADDRESS           0xF0240

#define DPCD_LTTPR_REPEATER_CONFIG_OFFSET             0x50

#define DPCD_LTTPR_REPEATER_STATUS_OFFSET             0x20  // 20h from the REPEATER config addresses
#define DPCD_LTTPR_REPEATER_SYMBOL_ERRROR_OFFSET      0x25  // 25h from the REPEATER config addresses

#define DPCD_LTTPR_PHY_REPEATER_MODE_ADDRESS          0xF0003
#define DPCD_LTTPR_PHY_REPEATER_MODE_LEN              1

#define DPCD_LTTPR_TRAINING_INTERVAL_OFFSET           0x10
#define DPCD_LTTPR_TRAINING_INTERVAL_LEN              1

#define DPCD_LTTPR_CE_TRAINING_INERVAL_MIN            400
#define DPCD_LTTPR_CE_TRAINING_INERVAL_OFFSET         4000

/* MSTM_CTRL offset and masks */
#define DP_MSTM_CTRL_ADDR                             0x111      // Register to enable MST on RX 
#define DP_MSTM_CTRL_UP_REQ_EN_MASK                   0x00000002 // Enable up request packets
#define DP_MSTM_CTRL_UPSTREAM_SRC_MASK                0x00000004 // Indicate that up stream device is source

/*---------------------------------------------------------------------------------------------------------------------
 * Function pre-declarations
 *-------------------------------------------------------------------------------------------------------------------*/
static DP_Status  DP_ParseSinkDPCDCap(
  MDP_Display_IDType              eDisplayID,
  DP_DPCDSinkCapRawDataType       *psDPCDCapRawData,
  DP_DPCDSinkCapType              *psDPCDSinkCap);

static DP_Status  DP_ParseSinkDPCDStatus(
  uint8                           *psDPCDSinkStatusRawData,
  DP_DPCDSinkStatusType           *psDPCDSinkStatus,
  bool32                           bRepeater);

static DP_Status  DP_ReadSinkPSRCap(
  DP_DisplayCtxType  *pDisplayCtx);

static DP_Status DP_ReadSinkDPCDCapRaw(
  DP_DisplayCtxType           *pDisplayCtx,
  DP_ReadPacketType           *pReadPacket,
  DP_DPCDSinkCapRawDataType   *pDPCDCapRawData,
  uint32                       uStartAddress);

static DP_Status  DP_ModifySinkDPCDReg(
  DP_DisplayCtxType *pDisplayCtx,
  uint32             uRegAddress,
  uint8              uBitMask,
  uint8              uNewValue);

static void  DP_ParseSinkBrightnessCap(
  MDP_Display_IDType        eDisplayId,
  uint8                    *pRawData,
  DP_SinkBrightnessCapType *pSinkBrightnessCap);

static DP_Status WriteSinkDPCDPower(
  DP_DisplayCtxType      *pDisplayCtx,
  DP_DPCDPowerStateType   ePowerState);


/**********************************************************************************************************************

FUNCTION: DP_ParseSinkDPCDCap()
   
   This function will parse the DPCD Capability from the Raw Data. 

Parameters:
   eDisplayID        -[in]  Display id
   psDPCDCapRawData  -[out] Raw data buffer containing DPCD data.
   psDPCDSinkCap     -[out] Pointer to DPCD Sink Capability.

Return: 
   DP_Status 

**********************************************************************************************************************/
static DP_Status  DP_ParseSinkDPCDCap(MDP_Display_IDType         eDisplayID,
                                      DP_DPCDSinkCapRawDataType *psDPCDCapRawData,
                                      DP_DPCDSinkCapType        *psDPCDSinkCap)
{
  DP_Status    eStatus                 = DP_STATUS_SUCCESS;
  uint32       uMaxLinkRateSupported   = 0;

  DP_OSAL_MemSet((char*)psDPCDSinkCap, 0, sizeof(DP_DPCDSinkCapType));

  /* Byte 0: DPCD_REV */
  switch (psDPCDCapRawData->uDPCDRevision)
  {
    case  DPCD_SPEC_REV_MAJOR_1_0:
    {
      psDPCDSinkCap->eDPCDMajorRev = DP_DPCD_MAJORREV_1_0;
      uMaxLinkRateSupported        = DPCD_HBR_LINK_RATE;
      break;
    }
    case  DPCD_SPEC_REV_MAJOR_1_1:
    {
      psDPCDSinkCap->eDPCDMajorRev = DP_DPCD_MAJORREV_1_1;
      uMaxLinkRateSupported        = DPCD_HBR_LINK_RATE;
      break;
    }
    case  DPCD_SPEC_REV_MAJOR_1_2:
    {
      psDPCDSinkCap->eDPCDMajorRev = DP_DPCD_MAJORREV_1_2;
      uMaxLinkRateSupported        = DPCD_HBR2_LINK_RATE;
      break;
    }
    case  DPCD_SPEC_REV_MAJOR_1_3:
    {
      psDPCDSinkCap->eDPCDMajorRev = DP_DPCD_MAJORREV_1_3;
      uMaxLinkRateSupported        = DPCD_HBR3_LINK_RATE;
      break;
    }
    case  DPCD_SPEC_REV_MAJOR_1_4:
    {
      psDPCDSinkCap->eDPCDMajorRev = DP_DPCD_MAJORREV_1_4;
      uMaxLinkRateSupported        = DPCD_HBR3_LINK_RATE;
      break;
    }
    default:
    {
      // Snap to the closest spec in the event that we detect a sink that we don't recognize.
      if (psDPCDCapRawData->uDPCDRevision < DPCD_SPEC_REV_MAJOR_1_0)
      {
        psDPCDSinkCap->eDPCDMajorRev = DP_DPCD_MAJORREV_1_0;
        uMaxLinkRateSupported        = DPCD_HBR_LINK_RATE;
      }
      else if (psDPCDCapRawData->uDPCDRevision > DPCD_SPEC_REV_MAJOR_1_4)
      {
        psDPCDSinkCap->eDPCDMajorRev = DP_DPCD_MAJORREV_1_4;
        uMaxLinkRateSupported        = DPCD_HBR3_LINK_RATE;

      }

      TraceInfo(QdiTraceDP, "DP%d: DPCD_REV 0x%x unsupported, snapping to the closest version.", 
        eDisplayID, psDPCDCapRawData->uDPCDRevision);

      break;
    }
  }
      
  /* Byte 1: MAX_LINK_RATE */
  if (0 == psDPCDCapRawData->uMaxLinkRate)
  {
    uint32 uIndex = 0;
    /* 
     * Special case for eDP
     * The supported link rates are in Bytes 0x10-0x1f
     * The rates are in multiples of 200Khz
     */
    for (uIndex = 0; uIndex < DPCD_LINK_RATE_TABLE_LENGTH; uIndex ++)
    {
      psDPCDSinkCap->uSupportedLinkRatesInKhz[uIndex] = psDPCDCapRawData->uSupportedRates[uIndex] * 20;

      /* If the next entry is zero, then this is the maximum supported link rate and rest of the entries are invalid*/
      if ((uIndex < (DPCD_LINK_RATE_TABLE_LENGTH - 1)) &&
          (0      == psDPCDCapRawData->uSupportedRates[uIndex + 1]))
      {
        psDPCDSinkCap->uMaxLinkRateInKhz = DPHOST_MIN(psDPCDSinkCap->uSupportedLinkRatesInKhz[uIndex], uMaxLinkRateSupported);
		break;
      }
    }
  }
  else
  {
    /*
     * DP Link rate in Khz
     *
     * |------------------|---------------|-------------------|
     * |                  | uMaxLinkRate  | uMaxLinkRateInKhz |
     * |                  |  (From Sink)  |    x27000         |
     * |------------------|---------------|-------------------|
     * | 1.62 Mbps (RBR)  |     6         |    162000         |
     * | 2.7  Mbps (HBR)  |    10         |    270000         |
     * | 5.4  Mbps (HBR2) |    20         |    540000         |
     * | 8.1  Mbps (HBR3) |    30         |    810000         |
     * |------------------|---------------|-------------------|
     */
    psDPCDSinkCap->uMaxLinkRateInKhz = DPHOST_MIN((uint32)(psDPCDCapRawData->uMaxLinkRate) * 27000, uMaxLinkRateSupported);
  }

  /* Byte 2: MAX_LANE_COUNT */
  psDPCDSinkCap->uMaxLaneCount = psDPCDCapRawData->uMaxLaneCount & DPCD_SPEC_MAX_LANE_COUNT_MAX_LANE_COUNT_BMSK;
  
  if (psDPCDCapRawData->uMaxLaneCount & 0x80)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_SUPPORT_ENHANCED_FRAME;
  }
  if (psDPCDCapRawData->uMaxLaneCount & 0x40)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_SUPPORT_TRAININGPATTERN3;
  }
  if (psDPCDCapRawData->uMaxLaneCount & 0x20)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_SUPPORT_POST_LT_ADJ_REQ;
  }

  /*Byte 3: MAX_DOWNSPREAD */
  if (psDPCDCapRawData->uMaxDownSpread & 0x01)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_MAX_DOWNSPREAD_0_5;
  }
  if (psDPCDCapRawData->uMaxDownSpread & 0x40)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_NO_AUX_HANDSHAKE;
  }
  if (psDPCDCapRawData->uMaxDownSpread & 0x80)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_SUPPORT_TRAININGPATTERN4;
  }

  /* Byte 4: NORP */
  psDPCDSinkCap->uNumofRXPorts  = (psDPCDCapRawData->uNumofReceiverPorts & 0x1) + 1;

  if (psDPCDCapRawData->uNumofReceiverPorts & 0x20)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_5V_DP_PWR;
  }

  if (psDPCDCapRawData->uNumofReceiverPorts & 0x40)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_12V_DP_PWR;
  }

  if (psDPCDCapRawData->uNumofReceiverPorts & 0x80)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_18V_DP_PWR;
  } 

  /* Byte 5: DOWNSTREAMPORT_PRESENT */
  if (psDPCDCapRawData->uDownStreamPortPresent & 0x01)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_DWN_STRM_PORT_PRESENT;
  }
  
  switch((psDPCDCapRawData->uDownStreamPortPresent >> 1) & 0x03)
  {
    case  DPCD_SPEC_DWN_STRM_PORT_TYPE_DISPLAYPORT:
    {
      psDPCDSinkCap->eDwnStreamPortType = DP_DPCD_DOWNSTREAMPORTTYPE_DISPLAYPORT;
      break;
    }
    case  DPCD_SPEC_DWN_STRM_PORT_TYPE_VGA_DVI_I:
    {
      psDPCDSinkCap->eDwnStreamPortType = DP_DPCD_DOWNSTREAMPORTTYPE_VGA_DVI_I;
      break;
    }
    case  DPCD_SPEC_DWN_STRM_PORT_TYPE_DVI_HDMI:
    {
      psDPCDSinkCap->eDwnStreamPortType = DP_DPCD_DOWNSTREAMPORTTYPE_DVI_HDMI;
      break;
    }
    case  DPCD_SPEC_DWN_STRM_PORT_TYPE_OTHERS:
    {
      psDPCDSinkCap->eDwnStreamPortType = DP_DPCD_DOWNSTREAMPORTTYPE_OTHER;
      break;
    }
    default:
    {
      psDPCDSinkCap->eDwnStreamPortType = DP_DPCD_DOWNSTREAMPORTTYPE_NONE;
      break;
    }
  }
  if (psDPCDCapRawData->uDownStreamPortPresent & 0x08)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_SUPPORT_FOMRAT_CONVERSION;
  }
  if (psDPCDCapRawData->uDownStreamPortPresent & 0x10)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_DETAILED_CAP_INFO_AVAILABLE;
  }

  /* Byte 6: MAIN_LINK_CHANNEL_CODING */  

  /* Byte 7: DOWN_STREAM_PORT_COUNT */
  psDPCDSinkCap->uNumOfDownStreamPorts = psDPCDCapRawData->uDownStreamPortCount & 0x0F;
  if (psDPCDCapRawData->uDownStreamPortCount & 0x40)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_MSA_TIMING_PAR_IGNORED;
  }
  if (psDPCDCapRawData->uDownStreamPortCount&0x80)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_SUPPORT_OUI;
  }

  /* Byte 8: RECEIVE_PORT0_CAP_0 */
  if (psDPCDCapRawData->uReceivePort0Cap0 & 0x02)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_PORT0_EDID_PRESENTED;
  }
  if (psDPCDCapRawData->uReceivePort0Cap0 & 0x04)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_PORT0_USED_FOR_2ND_STREAM;
  }

  /* Byte 9: RECEIVE_PORT0_CAP_1 */
  psDPCDSinkCap->uRXPort0BufferSize  = (psDPCDCapRawData->uReceivePort0Cap1 + 1) * 32;

  /* Byte 10: RECEIVE_PORT1_CAP_0 */
  if (psDPCDCapRawData->uReceivePort1Cap0 & 0x02)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_PORT1_EDID_PRESENTED;
  }
  if (psDPCDCapRawData->uReceivePort1Cap0 & 0x04)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_PORT1_USED_FOR_2ND_STREAM;
  }

  /*Byte 11: RECEIVE_PORT1_CAP_1 */
  psDPCDSinkCap->uRXPort1BufferSize            = (psDPCDCapRawData->uReceivePort1Cap1 + 1) * 32;

  /*Byte 12: I2C speed control */
  switch(psDPCDCapRawData->uI2CSpeedControlCap)
  {
    case  DPCD_SPEC_I2C_SPEED_CTRL_1KBPS:
    {
      psDPCDSinkCap->eI2CSpeedCtrl = DP_DPCD_I2CSPEEDCTRL_1KBPS;
      break;
    }
    case  DPCD_SPEC_I2C_SPEED_CTRL_5KBPS:
    {
      psDPCDSinkCap->eI2CSpeedCtrl = DP_DPCD_I2CSPEEDCTRL_5KBPS;
      break;
    }
    case  DPCD_SPEC_I2C_SPEED_CTRL_10KBPS:
    {
      psDPCDSinkCap->eI2CSpeedCtrl = DP_DPCD_I2CSPEEDCTRL_10KBPS;
      break;
    }
    case  DPCD_SPEC_I2C_SPEED_CTRL_100KBPS:
    {
      psDPCDSinkCap->eI2CSpeedCtrl = DP_DPCD_I2CSPEEDCTRL_100KBPS;
      break;
    }
    case  DPCD_SPEC_I2C_SPEED_CTRL_400KBPS:
    {
      psDPCDSinkCap->eI2CSpeedCtrl = DP_DPCD_I2CSPEEDCTRL_400KBPS;
      break;
    }
    case  DPCD_SPEC_I2C_SPEED_CTRL_1MBPS:
    {
      psDPCDSinkCap->eI2CSpeedCtrl = DP_DPCD_I2CSPEEDCTRL_1MBPS;
      break;
    }
    default:
    {
      psDPCDSinkCap->eI2CSpeedCtrl = DP_DPCD_I2CSPEEDCTRL_NONE;
      break;
    }
  }

  /* Byte 13: eDP_CONFIGURATION_CAP is eDP specific */  
  if (psDPCDCapRawData->uEDPConfigurationCap & 0x01)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_SUPPORT_ASSR;
  }
  if (psDPCDCapRawData->uEDPConfigurationCap & 0x02)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_FORCE_ENHANCED_FRAME;
  }

  /* Byte 14: TRAINING_AUX_RD_INTERVAL */
  switch (psDPCDSinkCap->eDPCDMajorRev)
  {  
  case DP_DPCD_MAJORREV_1_4:
      // Clock recovery interval is 100us
      psDPCDSinkCap->uCRTrainingIntervalInUs = 100; 
      // Channel equalization interval is 400us, 4ms, 8ms, 12ms, 16ms        
      psDPCDSinkCap->uCETrainingIntervalInUs = DPHOST_MAX(400, (psDPCDCapRawData->uTrainingAUXRdInterval & 0x7F) * 4000);
      break;
  case DP_DPCD_MAJORREV_1_3:
  case DP_DPCD_MAJORREV_1_2:   
      // Clock recovery interval is 100us, 4ms, 8ms, 12ms, 16ms
      psDPCDSinkCap->uCRTrainingIntervalInUs = DPHOST_MAX(100, (psDPCDCapRawData->uTrainingAUXRdInterval & 0x7F) * 4000); 
      // Channel equalization interval is 400us, 4ms, 8ms, 12ms, 16ms        
      psDPCDSinkCap->uCETrainingIntervalInUs = DPHOST_MAX(400, (psDPCDCapRawData->uTrainingAUXRdInterval & 0x7F) * 4000);
      break;
  case DP_DPCD_MAJORREV_1_0: 
  case DP_DPCD_MAJORREV_1_1:     
  default:
      // Clock recovery interval is 100us, DPCD register TRAINING_AUX_RD_INTERVAL is not supported.
      psDPCDSinkCap->uCRTrainingIntervalInUs = 100; 
      // Channel equalization interval is 400us, DPCD register TRAINING_AUX_RD_INTERVAL is not supported.
      // However some sinks take longer so we default to 4ms (level 1 from DP1.2) 
      psDPCDSinkCap->uCETrainingIntervalInUs = 4000;
      break;      
  }
  
  if (psDPCDCapRawData->uTrainingAUXRdInterval & 0x80)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_EXTENDED_RECEIVER_FIELD;
  }

  /* Byte 15: ADAPTER_CAP */
  if (psDPCDCapRawData->uAdapterCap & 0x01)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_SUPPORT_VGA_FORCE_LOAD_SENSE;
  }
  if (psDPCDCapRawData->uAdapterCap & 0x02)
  {
    psDPCDSinkCap->eDPCDCap    |= DP_DPCD_CAP_SUPPORT_ALTERNATE_I2C_PATTERN;
  }

  return eStatus;
}


/**********************************************************************************************************************

FUNCTION: DP_ParseSinkDPCDStatus()
   
   This function will parse the DPCD Status from the Raw Data. 

Parameters:
   psDPCDSinkStatusRawData          -[in ] Raw data buffer containing DPCD Status data.
   psDPCDSinkStatus                 -[out] Pointer to DPCD sink Status.
   bool32                           -[in]  True: LTTPR repeater. False: DP Rx sink

Return: 
   DP_Status 

**********************************************************************************************************************/
static DP_Status  DP_ParseSinkDPCDStatus(uint8                              *psDPCDSinkStatusRawData,
                                         DP_DPCDSinkStatusType              *psDPCDSinkStatus,
                                         bool32                              bRepeater)
{
  DP_Status                       eStatus        = DP_STATUS_SUCCESS;

  DP_OSAL_MemSet((char*)psDPCDSinkStatus, 0, sizeof(DP_DPCDSinkStatusType));

  /* DPRx Byte 0x202, LTTPR1 Byte 0xF0030: LANE0_1_STATUS */
  if (psDPCDSinkStatusRawData[0]  & 0x01)
  {
    psDPCDSinkStatus->eLaneStatus[0] |= DP_DPCD_LANE_STATUS_CR_DONE;
  }
  if (psDPCDSinkStatusRawData[0]  & 0x02)
  {
    psDPCDSinkStatus->eLaneStatus[0] |= DP_DPCD_LANE_STATUS_CHANNEL_EQ_DONE;
  }
  if (psDPCDSinkStatusRawData[0]  & 0x04)
  {
    psDPCDSinkStatus->eLaneStatus[0] |= DP_DPCD_LANE_STATUS_SYMBOL_LOCKED;
  }
  if (psDPCDSinkStatusRawData[0]  & 0x10)
  {
    psDPCDSinkStatus->eLaneStatus[1] |= DP_DPCD_LANE_STATUS_CR_DONE;
  }
  if (psDPCDSinkStatusRawData[0]  & 0x20)
  {
    psDPCDSinkStatus->eLaneStatus[1] |= DP_DPCD_LANE_STATUS_CHANNEL_EQ_DONE;
  }
  if (psDPCDSinkStatusRawData[0]  & 0x40)
  {
    psDPCDSinkStatus->eLaneStatus[1] |= DP_DPCD_LANE_STATUS_SYMBOL_LOCKED;
  }

  /* DPRx Byte 0x203, LTTPR1 Byte 0xF0031: LANE2_3_STATUS */
  if (psDPCDSinkStatusRawData[1]  & 0x01)
  {
    psDPCDSinkStatus->eLaneStatus[2] |= DP_DPCD_LANE_STATUS_CR_DONE;
  }
  if (psDPCDSinkStatusRawData[1] & 0x02)
  {
    psDPCDSinkStatus->eLaneStatus[2] |= DP_DPCD_LANE_STATUS_CHANNEL_EQ_DONE;
  }
  if (psDPCDSinkStatusRawData[1] & 0x04)
  {
    psDPCDSinkStatus->eLaneStatus[2] |= DP_DPCD_LANE_STATUS_SYMBOL_LOCKED;
  }
  if (psDPCDSinkStatusRawData[1] & 0x10)
  {
    psDPCDSinkStatus->eLaneStatus[3] |= DP_DPCD_LANE_STATUS_CR_DONE;
  }
  if (psDPCDSinkStatusRawData[1] & 0x20)
  {
    psDPCDSinkStatus->eLaneStatus[3] |= DP_DPCD_LANE_STATUS_CHANNEL_EQ_DONE;
  }
  if (psDPCDSinkStatusRawData[1] & 0x40)
  {
    psDPCDSinkStatus->eLaneStatus[3] |= DP_DPCD_LANE_STATUS_SYMBOL_LOCKED;
  }

  /* DPRx Byte 0x204, LTTPR1 Byte 0xF0032: LANE_ALIGN_STATUS_UPDATED */
  if (psDPCDSinkStatusRawData[2] & 0x01)
  {
    psDPCDSinkStatus->eLinkStatusBitArray |= DP_DPCD_BIT_STATUS_INTERLANE_ALIGN_DONE;
  }
  if (psDPCDSinkStatusRawData[2] & 0x40)
  {
    psDPCDSinkStatus->eLinkStatusBitArray |= DP_DPCD_BIT_STATUS_PORT_STATUS_CHANGED;
  }
  if (psDPCDSinkStatusRawData[2] & 0x80)
  {
    psDPCDSinkStatus->eLinkStatusBitArray |= DP_DPCD_BIT_STATUS_LINK_STATUS_UPDATED;
  }

  /* LTTPR repeater DPCD field does not has SINK_STATUS field */
  if (!bRepeater)
  {
    /* DPRx Byte 0x205: SINK_STATUS */
    if (psDPCDSinkStatusRawData[3] & 0x01)
    {
      psDPCDSinkStatus->eLinkStatusBitArray |= DP_DPCD_BIT_STATUS_PORT_0_IN_SYNC;
    }
    if (psDPCDSinkStatusRawData[3] & 0x02)
    {
      psDPCDSinkStatus->eLinkStatusBitArray |= DP_DPCD_BIT_STATUS_PORT_1_IN_SYNC;
    }
	
    /* DPRx Byte 0x206: ADJUST_REQUEST_LANE0_1 */
    psDPCDSinkStatus->uVoltageSwingLevel[0]   = (psDPCDSinkStatusRawData[4])      & 0x3;
    psDPCDSinkStatus->uPreEmphasisLevel[0]    = (psDPCDSinkStatusRawData[4] >> 2) & 0x3;
    psDPCDSinkStatus->uVoltageSwingLevel[1]   = (psDPCDSinkStatusRawData[4] >> 4) & 0x3;
    psDPCDSinkStatus->uPreEmphasisLevel[1]    = (psDPCDSinkStatusRawData[4] >> 6) & 0x3;

    /* DPRx Byte 0x207: ADJUST_REQUEST_LANE2_3 */
    psDPCDSinkStatus->uVoltageSwingLevel[2]   = (psDPCDSinkStatusRawData[5])      & 0x3;
    psDPCDSinkStatus->uPreEmphasisLevel[2]    = (psDPCDSinkStatusRawData[5] >> 2) & 0x3;
    psDPCDSinkStatus->uVoltageSwingLevel[3]   = (psDPCDSinkStatusRawData[5] >> 4) & 0x3;
    psDPCDSinkStatus->uPreEmphasisLevel[3]    = (psDPCDSinkStatusRawData[5] >> 6) & 0x3;
  }
  else
  {
    /* LTTPR1 Byte 0xF0033: ADJUST_REQUEST_LANE0_1 */
    psDPCDSinkStatus->uVoltageSwingLevel[0]   = (psDPCDSinkStatusRawData[3])      & 0x3;
    psDPCDSinkStatus->uPreEmphasisLevel[0]    = (psDPCDSinkStatusRawData[3] >> 2) & 0x3;
    psDPCDSinkStatus->uVoltageSwingLevel[1]   = (psDPCDSinkStatusRawData[3] >> 4) & 0x3;
    psDPCDSinkStatus->uPreEmphasisLevel[1]    = (psDPCDSinkStatusRawData[3] >> 6) & 0x3;

    /* LTTPR1 Byte 0xF0034: ADJUST_REQUEST_LANE2_3 */
    psDPCDSinkStatus->uVoltageSwingLevel[2]   = (psDPCDSinkStatusRawData[4])      & 0x3;
    psDPCDSinkStatus->uPreEmphasisLevel[2]    = (psDPCDSinkStatusRawData[4] >> 2) & 0x3;
    psDPCDSinkStatus->uVoltageSwingLevel[3]   = (psDPCDSinkStatusRawData[4] >> 4) & 0x3;
    psDPCDSinkStatus->uPreEmphasisLevel[3]    = (psDPCDSinkStatusRawData[4] >> 6) & 0x3;
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ReadSinkExclusiveExtendedCaps()

This function will read extended capabilities of the sink from DPCD address 2210h to 2214h
These registers are exclusive to extended cap register set and not present in DPCD base registers set

Parameters:
   pDisplayCtx                       - [in ] Pointer to display context

Return:
DP_Status

**********************************************************************************************************************/
static DP_Status  DP_ReadSinkExclusiveExtendedCaps(DP_DisplayCtxType* pDisplayCtx)
{
  DP_Status          eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType  *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkExclusiveExtendedCaps: Unexpected null context.");
  }
  else
  {
    uint8             uData[DPCD_EXCLUSIVE_EXT_CAP_LEN]; // 5 bytes
    DP_ReadPacketType sReadPacket;

    /*Read DPCD Data*/
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    DP_OSAL_MemSet(&uData, 0, sizeof(uData));
    sReadPacket.eTransactionType = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer = uData;
    sReadPacket.uAddress         = DPCD_EXCLUSIVE_EXT_CAP_START_ADDRESS;
    sReadPacket.uReadSize        = sizeof(uData);
    sReadPacket.uBytesRead       = 0;
    sReadPacket.bQueueOnly       = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP_ReadSinkExclusiveExtendedCaps: Registers read failed, eStatus=0x%x.", eStatus);
    }
    else
    {
      /* Extended Cap Byte 0: DPRX_FEATURE_ENUMERATION_LIST */
      pDeviceCtx->sSinkDPCDCap.eRxFeatureEnumList      = (DP_ExtDPCDRxFeatureType)uData[0];

      /* Extended Cap Byte 4: ADAPTIVE_SYNC_CAPABILITY */
      pDeviceCtx->sSinkDPCDCap.bAdaptiveSyncSDPSupport = (DPCD_ADAPTIVE_SYNC_SDP_BMSK & uData[4]) ? TRUE : FALSE;

      TraceInfo(QdiTraceDP, "DP%i: DPCD Exclusive Extended Caps (5 bytes from 2210h to 2214h): {0x%x, 0x%x, 0x%x, 0x%x, 0x%x}",
                             pDeviceCtx->eDisplayID, uData[0], uData[1], uData[2], uData[3], uData[4]);
    }
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ReadSinkPSRCap()

This function will check sink PSR support and capabilities

Parameters:
   pDeviceCtx                       -[in ] Pointer to device context

Return:
DP_Status

**********************************************************************************************************************/
static DP_Status  DP_ReadSinkPSRCap(DP_DisplayCtxType  *pDisplayCtx)
{
  DP_Status          eStatus = DP_STATUS_SUCCESS;  
  DP_DeviceCtxType  *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkPSRCap: Unexpected null context.");
  }
  else
  {
    uint8              uPSRBuf[DPCD_PSR_CAP_LEN];
    DP_ReadPacketType  sReadPacket;
    
    /*Read DPCD Data*/  
    DP_OSAL_MemSet(&uPSRBuf,     0, DPCD_PSR_CAP_LEN);
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    sReadPacket.eTransactionType     = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer     = (uint8*)&uPSRBuf;
    sReadPacket.uAddress             = DPCD_PSR_CAP_START_ADDRESS;
    sReadPacket.uReadSize            = DPCD_PSR_CAP_LEN;
    sReadPacket.uBytesRead           = 0;
    sReadPacket.bQueueOnly           = FALSE;
    
    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP_ReadSinkPSRCap: Read Failed, eStatus=0x%x.", eStatus);
    }
    else
    {
      uint8  uPSRVersion = uPSRBuf[0];
      uint8  uPSRCaps    = uPSRBuf[1];
      uint8  uData       = 0;
     
#ifndef PSR2_SUPPORTED
      if (DPCD_SPEC_PSR_VERSION_UNSUPPORTED != uPSRVersion)
      {
        // This is to only support PSR v1 for now
        pDeviceCtx->sSinkDPCDCap.sPSRCap.uVersion = DPCD_SPEC_PSR_VERSION_1;
      }
#endif      

      // Bit 0 indicates link training requirements for PSR1 - it is a 'don't care' for PSR2
      if ((DPCD_SPEC_PSR_VERSION_1 == uPSRVersion) &&
          (1                       == (uPSRCaps & 0x1)))
      {
        // Fast wake is required for PSR1
        pDeviceCtx->sSinkDPCDCap.sPSRCap.eLinkTrainingonExit = DP_LINK_TRAINING_TYPE_NO_TRAINING;
      }
      else
      {
        // Default to fast training
        pDeviceCtx->sSinkDPCDCap.sPSRCap.eLinkTrainingonExit = DP_LINK_TRAINING_TYPE_FAST_TRAINING;
      }
    
      // Bits 1:3 indicate setup time
      uData = (uPSRCaps >> 1) & 0x7;
      if (uData > 6)
      {
        uData = 6;     
      }    
      /*
       * PSR Setup Time have 0 ~ 6 levels,
       * 330 us for level 0 which is default.
       * after that, each level has 55 us decreased
       */
      pDeviceCtx->sSinkDPCDCap.sPSRCap.uSetupTimeUs = 330 - (55 * uData);
    
      TraceInfo(QdiTraceDP, "DP%d: DPCD PSR caps: ver %d, link_training_on_exit: %d, setup_time: %d Us",
                pDeviceCtx->eDisplayID,
                uPSRVersion,
                pDeviceCtx->sSinkDPCDCap.sPSRCap.eLinkTrainingonExit,
                pDeviceCtx->sSinkDPCDCap.sPSRCap.uSetupTimeUs);
    }
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ReadSinkALPMCap()

This function will check ALPM capabilities of the sink
Advanced Link Power Management(ALPM) is a receiver side(DPRX) power saving feature

Parameters:
   pDisplayCtx                       - [in ] Pointer to display context

Return:
DP_Status

**********************************************************************************************************************/
static DP_Status  DP_ReadSinkALPMCap(DP_DisplayCtxType* pDisplayCtx)
{
  DP_Status          eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType*  pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkALPMCap: Unexpected null context.");
  }
  else
  {
    uint8              uData = 0;
    DP_ReadPacketType  sReadPacket;

    /*Read DPCD Data*/
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    sReadPacket.eTransactionType = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer = &uData;
    sReadPacket.uAddress         = DPCD_ALPM_CAP_START_ADDRESS;
    sReadPacket.uReadSize        = sizeof(uData);
    sReadPacket.uBytesRead       = 0;
    sReadPacket.bQueueOnly       = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP_ReadSinkALPMCap: Read Failed, eStatus=0x%x.", eStatus);
    }
    else
    {
      pDeviceCtx->sSinkDPCDCap.sALPMCap.bALPMCapable    = (uData & DPCD_ALPM_CAP_MASK) ? TRUE : FALSE;
      pDeviceCtx->sSinkDPCDCap.sALPMCap.bStandBySupport = (uData & DPCD_ALPM_STANDBY_CAP_MASK) ? TRUE : FALSE;
    }
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ReadMSTCap()

This function will check MST capabilities of the sink

Parameters:
    pDisplayCtx  - [in ] Pointer to display context

Return:
    DP_Status

**********************************************************************************************************************/
static DP_Status  DP_ReadSinkMSTCap(DP_DisplayCtxType  *pDisplayCtx)
{
  DP_Status         eStatus = DP_STATUS_SUCCESS;  
  DP_DeviceCtxType *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkMSTCap: Unexpected null context.");
  }
  else
  {
    uint8              uData = 0;
    DP_ReadPacketType  sReadPacket;

    /*Read DPCD Data*/
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    sReadPacket.eTransactionType = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer = &uData;
    sReadPacket.uAddress         = DPCD_MST_CAP_START_ADDRESS;
    sReadPacket.uReadSize        = sizeof(uData);
    sReadPacket.uBytesRead       = 0;
    sReadPacket.bQueueOnly       = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
       DP_LOG_MESSAGE_ERROR("DP_ReadSinkMSTCap: Read Failed, eStatus=0x%x.", eStatus);
    }
    else
    {
      pDeviceCtx->sSinkDPCDCap.bMSTCapable = (uData & DPCD_SPEC_MSTM_CAP_MST_CAP_BMSK) ? TRUE : FALSE;
    }
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ReadSinkDPCDCapRaw()

   This function will read the raw Sink Capability Data from DPCD over AUX Channel

Parameters:
   pDisplayCtx                      -[in ] Pointer to context
   pReadPacket                      -[in ] Pointer to the read packet
   pDPCDCapRawData                  -[out] Pointer to the raw data buffer to store DPCD sink capability data
   uStartAddress                    -[in ] Start address of the DPCD sink capability data

Return:
   DP_Status

**********************************************************************************************************************/
static DP_Status DP_ReadSinkDPCDCapRaw(DP_DisplayCtxType            *pDisplayCtx,
                                       DP_ReadPacketType            *pReadPacket,
                                       DP_DPCDSinkCapRawDataType    *pDPCDCapRawData,
                                       uint32                        uStartAddress)
{

  DP_Status          eStatus = DP_STATUS_SUCCESS;  
  DP_DeviceCtxType  *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkDPCDCapRaw: Unexpected null context.");
  }
  else
  {
    uint32     uReadSize   = sizeof(DP_DPCDSinkCapRawDataType);
  
    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxRead(pDisplayCtx,
                                                        (uint8*)pDPCDCapRawData,
                                                        &uReadSize,
                                                        uStartAddress,
                                                        DP_TRANSACTION_MODE_AUX)))
    {
      /* Attempt reading one byte at a time as some dongles can only return DPCD byte by byte */
      uint32 uReadIdx;
      
      DP_OSAL_MemSet(pReadPacket, 0, sizeof(DP_ReadPacketType));
      pReadPacket->eTransactionType     = DP_TRANSACTION_MODE_AUX;
      pReadPacket->puReadDataBuffer     = (uint8*)pDPCDCapRawData;
      pReadPacket->uAddress             = uStartAddress;
      pReadPacket->uReadSize            = 1;
      pReadPacket->uBytesRead           = 0;
      pReadPacket->bQueueOnly           = FALSE;
  
      for (uReadIdx = 0; uReadIdx < sizeof(DP_DPCDSinkCapRawDataType); uReadIdx++)
      {
        if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, pReadPacket)))
        {
          break;
        }
        pReadPacket->puReadDataBuffer++;
        pReadPacket->uAddress++;
      }
  
      if (DP_STATUS_SUCCESS != eStatus)
      {
        DP_LOG_MESSAGE_ERROR("DP_ReadDPCDSinkCap: Read Failed, eStatus=0x%x.", eStatus);
      }
      else if (pReadPacket->uBytesRead != pReadPacket->uReadSize)
      {
        eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
        DP_LOG_MESSAGE_ERROR("DP_ReadDPCDSinkCap: Bytes Read(%d) is not expected when reading byte-by-byte.", pReadPacket->uBytesRead);
      }
    }
    else if (uReadSize != sizeof(DP_DPCDSinkCapRawDataType))
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DP_LOG_MESSAGE_ERROR("DP_ReadDPCDSinkCap: Bytes Read(%d) is not expected.", pReadPacket->uBytesRead);
    }
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: WriteSinkDPCDPower()
   
   Helper function to set the sink power state via corresponding DPCD write.

Parameters:
   pDisplayCtx                      -[in ] Pointer to context
   ePowerState                      -[in ] Sink power state to be set

Return: 
   DP_Status 

**********************************************************************************************************************/
static DP_Status WriteSinkDPCDPower(DP_DisplayCtxType      *pDisplayCtx,
                                    DP_DPCDPowerStateType   ePowerState)
{
  DP_Status          eStatus = DP_STATUS_SUCCESS;  
  uint8              uWriteBuffer;

  switch (ePowerState)
  {
    case DP_DPCD_POWERSTATE_D0:
    {
      uWriteBuffer = DPCD_SPEC_POWER_STATE_D0;
      break;
    }
    case DP_DPCD_POWERSTATE_D3:
    {
      uWriteBuffer = DPCD_SPEC_POWER_STATE_D3;
      break;
    }
    case DP_DPCD_POWERSTATE_LINK_D3_AUX_D0:
    {
      uWriteBuffer = DPCD_SPEC_POWER_STATE_LINK_D3_AUX_D0;
      break;
    }
    default:
    {
      eStatus      = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
      DP_LOG_MESSAGE_ERROR("WriteSinkDPCDPower: Invalid input parameter ");
      break;
    }
  }
  
  if (DP_STATUS_SUCCESS == eStatus)
  {
    DP_WritePacketType       sWritePacket;

    /*Write DPCD Data*/
    DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
    sWritePacket.eTransactionType    = DP_TRANSACTION_MODE_AUX;
    sWritePacket.puWriteData         = &uWriteBuffer;
    sWritePacket.uAddress            = DPCD_SET_POWER_STATE_START_ADDRESS;
    sWritePacket.uWriteDataSize      = DPCD_SET_POWER_STATE_LEN;
    sWritePacket.uBytesWritten       = 0;
    sWritePacket.bQueueOnly          = FALSE;
    
    eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket);
  }
  
  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ReadSinkDPCDCap()
   
   This function will read and parse the Sink Capability Data from DPCD over AUX Channel

Parameters:
   pDisplayCtx                      -[in ] Pointer to context

Return: 
   DP_Status 

**********************************************************************************************************************/
DP_Status  DP_ReadSinkDPCDCap(DP_DisplayCtxType    *pDisplayCtx)
{
  DP_Status                       eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType               *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkDPCDCap: Unexpected null context.");
  }
  else
  {
    DP_DPCDSinkCapRawDataType       sDPCDCapRawData;
    DP_ReadPacketType               sReadPacket;
    DP_DPCDSinkCapType             *psDPCDSinkCap = &pDeviceCtx->sSinkDPCDCap;
    DP_DPCDSinkCapType              sExtendedDPCDSinkCap;

    /*Read DPCD Data*/
    if (DP_STATUS_SUCCESS != (eStatus = DP_ReadSinkDPCDCapRaw(pDisplayCtx, &sReadPacket, &sDPCDCapRawData, DPCD_CAP_START_ADDRESS)))
    {
      DP_LOG_MESSAGE_ERROR("DP_ReadSinkDPCDCapRaw failed, eStatus=0x%x.", eStatus);
    }
    else if (DP_STATUS_SUCCESS != (eStatus = DP_ParseSinkDPCDCap(pDeviceCtx->eDisplayID, &sDPCDCapRawData, psDPCDSinkCap)))
    {
      DP_LOG_MESSAGE_ERROR("DP_ParseSinkDPCDCap failed, eStatus=0x%x.", eStatus);
    }
    else if (0 != (psDPCDSinkCap->eDPCDCap & DP_DPCD_CAP_EXTENDED_RECEIVER_FIELD))
    {
      /* If the receiver reports it has extended capabilities, parse the extended capabilities section also */
      if (DP_STATUS_SUCCESS != DP_ReadSinkDPCDCapRaw(pDisplayCtx, &sReadPacket, &sDPCDCapRawData, DPCD_EXTENDED_CAP_START_ADDRESS))
      {
        DP_LOG_MESSAGE_ERROR("DP_ReadSinkDPCDCapRaw (Extended) failed");
      }
      else if (DP_STATUS_SUCCESS != DP_ParseSinkDPCDCap(pDeviceCtx->eDisplayID, &sDPCDCapRawData, &sExtendedDPCDSinkCap))
      {
        DP_LOG_MESSAGE_ERROR("DP_ParseSinkDPCDCap (Extended) failed");
      }
      else
      {
        DISP_OSAL_MemCpyEx(psDPCDSinkCap, sizeof(DP_DPCDSinkCapType), &sExtendedDPCDSinkCap, sizeof(DP_DPCDSinkCapType));
      }
    }

    if (DP_STATUS_SUCCESS == eStatus)
    {
      if (DP_DPCD_CAP_EXTENDED_RECEIVER_FIELD & psDPCDSinkCap->eDPCDCap)
      {
        /* Read DPCD registers exclusive to extended capabilities register set */
        DP_ReadSinkExclusiveExtendedCaps(pDisplayCtx);
      }

      if (DP_DEVICE_MODETYPE_EDP  == pDeviceCtx->eDeviceDPMode)
      {
        /* Read PSR and ALPM power saving capabilities of sink */
        DP_ReadSinkPSRCap(pDisplayCtx);
        DP_ReadSinkALPMCap(pDisplayCtx);
      }
      else // Standard caps for DP
      {
        /* LTTPR only supported for DP interfaces */
        DP_ReadSinkLTTPRCap(pDisplayCtx);

        /* Read closest to Tx repeater OUI device info */
        DP_ReadSinkLTTPRRepeaterOUI(pDisplayCtx,
                                   (DP_LTTPR_RepeaterIDType)(pDeviceCtx->sLTTPRCaps.uRepeaterCount));
        
        /* Read MST caps */
        DP_ReadSinkMSTCap(pDisplayCtx);
      }

      /* Cache the DPCD caps */
      DISP_OSAL_MemCpyEx(&pDeviceCtx->sDPCDCapRawData, sizeof(pDeviceCtx->sDPCDCapRawData), &sDPCDCapRawData, sizeof(sDPCDCapRawData));
    }

    TraceInfo(QdiTraceDP, "DP%d: DPCD Caps - ver 1.%d, max lanes: %d, max rate: %dMhz, ClkRecovery interval: %dus, ChanEq interval: %dus, MST capable: %d", 
              pDeviceCtx->eDisplayID, 
              psDPCDSinkCap->eDPCDMajorRev-1, 
              psDPCDSinkCap->uMaxLaneCount, 
              psDPCDSinkCap->uMaxLinkRateInKhz/1000, 
              psDPCDSinkCap->uCRTrainingIntervalInUs,
              psDPCDSinkCap->uCETrainingIntervalInUs,
              psDPCDSinkCap->bMSTCapable);
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ReadSinkDPCDStatus()
   
   This function will read Sink Status Raw Data from DPCD over AUX Channel

Parameters:
   pDisplayCtx                      -[in ] Pointer to context
   psDPCDSinkStatus                 -[out] Pointer to DPCD Sink Status Data struct.
   uReadFlags                       -[in]  Flags to be used for DP AUX read

Return: 
   DP_Status 

**********************************************************************************************************************/
DP_Status  DP_ReadSinkDPCDStatus(DP_DisplayCtxType     *pDisplayCtx,
                                 DP_DPCDSinkStatusType *psDPCDSinkStatus,
                                 uint32                 uReadFlags)
{
  DP_Status                 eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType         *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkDPCDStatus: Unexpected null context.");
  }
  else if (FALSE == DPHOST_CHECK_IS_LTTPR_REPEATER(pDeviceCtx))
  {
    DP_DPCDSinkStatusRawDataType    sDPCDSinkStatusRawData;
    DP_ReadPacketType               sReadPacket;
    
    /* Read DPCD Data */
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    sReadPacket.eTransactionType     = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer     = (uint8*)&sDPCDSinkStatusRawData;
    sReadPacket.uAddress             = DPCD_LINK_STATUS_START_ADDRESS;
    sReadPacket.uReadSize            = sizeof(DP_DPCDSinkStatusRawDataType);
    sReadPacket.uBytesRead           = 0;
    sReadPacket.bQueueOnly           = FALSE;
    sReadPacket.eFlags               = uReadFlags;
    
    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      TraceInfo(QdiTraceDiag, "DP%i: Read address:0x%x failed, eStatus=0x%x.", 
        pDeviceCtx->eDisplayID, 
        DPCD_LINK_STATUS_START_ADDRESS, 
        eStatus);
    }
    else if (sReadPacket.uBytesRead != sReadPacket.uReadSize)
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      TraceInfo(QdiTraceDiag, "DP%i: Read address:0x%x failed: Bytes Read(0x%x) is not expected.", 
         pDeviceCtx->eDisplayID, 
         DPCD_LINK_STATUS_START_ADDRESS, 
         sReadPacket.uBytesRead);
    }
    else
    {
      eStatus = DP_ParseSinkDPCDStatus((uint8 *)&sDPCDSinkStatusRawData, psDPCDSinkStatus, FALSE);
    }
    
    if (DP_STATUS_SUCCESS == eStatus)
    {
      // Cache the raw sink status information, 6 registers from 202h
      DP_OSAL_MemCpyEx(&pDeviceCtx->aSinkStatus, sizeof(pDeviceCtx->aSinkStatus), &sDPCDSinkStatusRawData, sizeof(DP_DPCDSinkStatusRawDataType));
    
      // Log the sink status to WPP
      TraceInfo(QdiTraceDiag, "DP%i: Sink lane status (202h-207h):0x%x,0x%x,0x%x,0x%x,0x%x,0x%x", 
          pDeviceCtx->eDisplayID,
          sDPCDSinkStatusRawData.uLaneStatus0_1,
          sDPCDSinkStatusRawData.uLaneStatus2_3,
          sDPCDSinkStatusRawData.uLaneAlignStatusUpdated,
          sDPCDSinkStatusRawData.uSinkStatus,
          sDPCDSinkStatusRawData.uAdjustRequestLane0_1,
          sDPCDSinkStatusRawData.uAdjustRequestLane2_3);  
    }
  }
  else
  {
   /* LTTPR case */
    DP_DPCDLTTPRStatusRawDataType sDPCDLTTPRStatusRawData;
    DP_ReadPacketType             sReadPacket;
  
    /* Read DPCD LTTPR Data */
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    sReadPacket.eTransactionType   = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer   = (uint8*)&sDPCDLTTPRStatusRawData;
    sReadPacket.uAddress           = DP_GetRepeaterDPCDOffset(pDeviceCtx->eLTTPRRepeaterID, DPCD_LINK_STATUS_START_ADDRESS);
    sReadPacket.uReadSize          = sizeof(DP_DPCDLTTPRStatusRawDataType);
    sReadPacket.uBytesRead         = 0;
    sReadPacket.bQueueOnly         = FALSE;
    sReadPacket.eFlags             = uReadFlags;
  
    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      TraceInfo(QdiTraceDiag, "DP%i: Read address:0x%x failed, eStatus=0x%x.", 
          pDeviceCtx->eDisplayID, 
          sReadPacket.uAddress, 
          eStatus);
    }
    else if (sReadPacket.uBytesRead != sReadPacket.uReadSize)
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      TraceInfo(QdiTraceDiag, "DP%i: Read address:0x%x failed: Bytes Read(0x%x) is not expected.", 
          pDeviceCtx->eDisplayID, 
          sReadPacket.uAddress , 
          sReadPacket.uBytesRead);
    }
    else
    {
      eStatus = DP_ParseSinkDPCDStatus((uint8 *)&sDPCDLTTPRStatusRawData, psDPCDSinkStatus, TRUE);
    }

    if (DP_STATUS_SUCCESS == eStatus)
    {
      // Log the LTTPR status to WPP
      TraceInfo(QdiTraceDiag, "DP%i: LTTPR%i: lane status (ex:F0030h-F0034h):0x%x,0x%x,0x%x,0x%x,0x%x", 
          pDeviceCtx->eDisplayID,
          pDeviceCtx->eLTTPRRepeaterID,
          sDPCDLTTPRStatusRawData.uLaneStatus0_1,
          sDPCDLTTPRStatusRawData.uLaneStatus2_3,
          sDPCDLTTPRStatusRawData.uLaneAlignStatusUpdated,
          sDPCDLTTPRStatusRawData.uAdjustRequestLane0_1,
          sDPCDLTTPRStatusRawData.uAdjustRequestLane2_3);  
    }
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_WriteSinkDPCDLink()
   
   This function will Write the link setting to panel DPCD 

Parameters:
   pDisplayCtx  -[in]    : DP Display Context

Return: 
   DP_Status 

**********************************************************************************************************************/
DP_Status  DP_WriteSinkDPCDLink(DP_DisplayCtxType    *pDisplayCtx)
{
  DP_Status                 eStatus = DP_STATUS_SUCCESS; 
  DP_DeviceCtxType         *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_WriteSinkDPCDLink: Unexpected null context.");
  }
  else
  {
    DP_WritePacketType        sWritePacket;
    uint8                     uWriteBuffer[2];
    uint32                    i;

    /*
     * For eDP 1.4+, the panel will report supported bit rates as a Table as opposed to just the max bit rate
     * on previous spec revisions. In this case, we set the selected link rate on DPCD register 0x115. For all 
     * other cases, the link rate is set on DPCD register 0x100.
     */

    /* LINK_BW_SET */
    if (DP_DEVICE_MODETYPE_EDP == pDeviceCtx->eDeviceDPMode)
    {
      sWritePacket.eTransactionType    = DP_TRANSACTION_MODE_AUX;
      sWritePacket.puWriteData         = uWriteBuffer;
      sWritePacket.uAddress            = 0x115;
      sWritePacket.uWriteDataSize      = 1;
      sWritePacket.uBytesWritten       = 0;
      sWritePacket.bQueueOnly          = FALSE;

      /* Find the index in the list of supported rates */
      for (i = 0; i < 8; i++)
      {
        if (pDeviceCtx->sSinkDPCDCap.uSupportedLinkRatesInKhz[i] == pDeviceCtx->uLinkRateInKhz)
        {
          uWriteBuffer[0] = (uint8) i;
          eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket);

          if (DP_STATUS_SUCCESS != eStatus)
          {
            DP_LOG_MESSAGE_ERROR( "DP_WriteSinkDPCDLink: Write Failed, eStatus=0x%x.",eStatus);
          }
        }
      }

      /* LINK_RATE_SET */
      // Reset byte zero in the buffer for the next command
      uWriteBuffer[0] = 0;
    }

    switch(pDeviceCtx->uLinkRateInKhz)
    {
      case 162000:
      {
        uWriteBuffer[0] = DPCD_SPEC_MAX_LINK_RATE_1_62GBPS;
        break;
      }
      case 270000:
      {
        uWriteBuffer[0] = DPCD_SPEC_MAX_LINK_RATE_2_7GBPS;
        break;
      }
      case 540000:
      {
        uWriteBuffer[0] = DPCD_SPEC_MAX_LINK_RATE_5_4GBPS;
        break;
      }
      case 810000:
      {
        uWriteBuffer[0] = DPCD_SPEC_MAX_LINK_RATE_8_1GBPS;
        break;
      }
      default:
      {
        eStatus         = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
        DP_LOG_MESSAGE_ERROR("DP_WriteSinkDPCDLink: Invalid input parameter.");
        break;
      }
    }

    if (DP_STATUS_SUCCESS == eStatus )
    {
      /* LANE_COUNT_SET */
      
      uWriteBuffer[1] = (uint8) pDeviceCtx->uNumLanes;
      
      if (pDeviceCtx->sSinkDPCDCap.eDPCDCap & DP_DPCD_CAP_SUPPORT_ENHANCED_FRAME)
      {
        uWriteBuffer[1] |= DPCD_SPEC_EN_ENHANCED_FRAME_BMSK ;
      }

      /*Write DPCD Data*/
      DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
      sWritePacket.eTransactionType    = DP_TRANSACTION_MODE_AUX;
      sWritePacket.puWriteData         = uWriteBuffer;
      sWritePacket.uAddress            = DPCD_LINKCONFIG_START_ADDRESS;
      sWritePacket.uWriteDataSize      = DPCD_LINKCONFIG_LEN;
      sWritePacket.uBytesWritten       = 0;
      sWritePacket.bQueueOnly          = FALSE;
      
      eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket);

      if (DP_STATUS_SUCCESS != eStatus)
      {
        DP_LOG_MESSAGE_ERROR( "DP_WriteSinkDPCDLink: Write Failed, eStatus=0x%x.",eStatus);
      }
    }
    TraceInfo(QdiTraceDP, "DP%d: DP_WriteSinkDPCDLink Setting Link Rate=%d, Lane Number=%d", 
              pDeviceCtx->eDisplayID, 
              pDeviceCtx->uLinkRateInKhz, 
              pDeviceCtx->uNumLanes);
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_WriteSinkDPCDTrainingPattern()
   
   This function will select the training pattern for link training to panel DPCD 

Parameters:
   pDisplayCtx                      -[in ] Pointer to context
   eTraingPattern                   -[in ] Link Training pattern 

Return: 
   DP_Status 

**********************************************************************************************************************/
DP_Status  DP_WriteSinkDPCDTrainingPattern(DP_DisplayCtxType             *pDisplayCtx,
                                           DP_DPCDTrainingPatternSetType  eTraingPattern)
{
  DP_Status                 eStatus       = DP_STATUS_SUCCESS; 
  DP_DeviceCtxType         *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_WriteSinkDPCDLink: Unexpected null context.");
  }
  else
  {
    uint8                     uWriteBuffer  = 0;
    DP_WritePacketType        sWritePacket;

    switch(eTraingPattern)
    {
      case DP_DPCD_TRAININGPATTERNSET_NONE:
      {
        uWriteBuffer = DPCD_SPEC_TRAINING_PATTERN_NONE;
        break;
      }
      case DP_DPCD_TRAININGPATTERNSET_PATTERN1:
      {
        uWriteBuffer = DPCD_SPEC_TRAINING_PATTERN_1;      
        /* Disable scrambling as this sequence is not scrambled */
        uWriteBuffer |= DPCD_SPEC_SCRAMBLING_DISABLE_BMSK;      
        break;
      }
      case DP_DPCD_TRAININGPATTERNSET_PATTERN2:
      {
        uWriteBuffer = DPCD_SPEC_TRAINING_PATTERN_2;      
        /* Disable scrambling as this sequence is not scrambled */
        uWriteBuffer |= DPCD_SPEC_SCRAMBLING_DISABLE_BMSK;
        break;
      }
      case DP_DPCD_TRAININGPATTERNSET_PATTERN3:
      {
        uWriteBuffer = DPCD_SPEC_TRAINING_PATTERN_3;      
        /* Disable scrambling as this sequence is not scrambled */
        uWriteBuffer |= DPCD_SPEC_SCRAMBLING_DISABLE_BMSK;
        break;
      }    
      case DP_DPCD_TRAININGPATTERNSET_PATTERN4:
      {
        /* TPS4 is scrambled. So don't disable Scrambling */
        uWriteBuffer = DPCD_SPEC_TRAINING_PATTERN_4;
        break;
      }    
      default:
      {
        eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
        DP_LOG_MESSAGE_ERROR("DP_WriteSinkDPCDTrainingPattern: Invalid input parameter");
        break;
      }
    }

    if (DP_STATUS_SUCCESS == eStatus)
    {
      /* Write DPCD Data */
      DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
      sWritePacket.eTransactionType    = DP_TRANSACTION_MODE_AUX;
      sWritePacket.puWriteData         = &uWriteBuffer;
      sWritePacket.uAddress            = DP_GetRepeaterDPCDOffset(pDeviceCtx->eLTTPRRepeaterID, DPCD_TRAINING_PATTERN_SET_START_ADDRESS);
      sWritePacket.uWriteDataSize      = DPCD_TRAINING_PATTERN_SET_LEN;
      sWritePacket.uBytesWritten       = 0;
      sWritePacket.bQueueOnly          = FALSE;
      sWritePacket.eFlags              = DP_AUX_TRANSACTION_AUX_WAIT_STALL_FLAG;        // Use stall as link training is timing sensitive
      
      eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket);

      if (DP_STATUS_SUCCESS != eStatus)
      {
        DP_LOG_MESSAGE_ERROR("DP_WriteSinkDPCDTrainingPattern: Write Failed, eStatus=0x%x.", eStatus);
      }
    }
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_WriteSinkDPCDLevels()
   
   This function will select the training Voltage Swing Level and Pre-emphasis Level.

Parameters:
   pDisplayCtx                      -[in ] Pointer to context
   uDesiredVoltageSwingLevel        -[in ] The desired Voltage Swing level for link training
   uDesiredPreEmphasisLevel         -[in ] The desired pre-emphasis level for link training

Return: 
   DP_Status 

**********************************************************************************************************************/
DP_Status  DP_WriteSinkDPCDLevels(DP_DisplayCtxType  *pDisplayCtx,
                                  uint32              uDesiredVoltageSwingLevel,
                                  uint32              uDesiredPreEmphasisLevel)
{
  DP_Status                eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType        *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_WriteSinkDPCDLevels: Unexpected null context.");
  }
  else
  {
    DP_WritePacketType       sWritePacket;
    uint8                    uWriteBuffer[4];       
    uint32                   uNumLanes;

    uNumLanes          = ((pDeviceCtx->uNumLanes > 4) || (pDeviceCtx->uNumLanes < 1)) ? 4 : pDeviceCtx->uNumLanes;
    uWriteBuffer[0]    = uDesiredVoltageSwingLevel & 0x3;
    uWriteBuffer[0]   |= (uDesiredPreEmphasisLevel << 3) & 0x18;
    
    if (pDeviceCtx->uMaxVoltSwingLvl == uDesiredVoltageSwingLevel)
    {
      uWriteBuffer[0] |= DPCD_SPEC_MAX_SWING_REACHED_BMSK;
    }
    if (pDeviceCtx->uMaxPreemphLvl == uDesiredPreEmphasisLevel)
    {
      uWriteBuffer[0] |= DPCD_SPEC_MAX_PRE_EMPHASIS_REACHED_BMSK;
    }
    
    /* Use same config for lanes 1-4 */
    uWriteBuffer[3] = uWriteBuffer[0];
    uWriteBuffer[2] = uWriteBuffer[0];
    uWriteBuffer[1] = uWriteBuffer[0];
    
    /* Write DPCD Data */
    DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
    sWritePacket.eTransactionType    = DP_TRANSACTION_MODE_AUX;
    sWritePacket.puWriteData         = uWriteBuffer;
    sWritePacket.uAddress            = DP_GetRepeaterDPCDOffset(pDeviceCtx->eLTTPRRepeaterID, DPCD_TRAINING_LANE_SET_START_ADDRESS);
    sWritePacket.uWriteDataSize      = uNumLanes;                     // apply settings only for the enabled lanes
    sWritePacket.uBytesWritten       = 0;
    sWritePacket.bQueueOnly          = FALSE;
    sWritePacket.eFlags              = DP_AUX_TRANSACTION_AUX_WAIT_STALL_FLAG; // Use stall as link training is timing sensitive
    
    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP_WriteSinkDPCDLevels: Write Failed, eStatus=0x%x.", eStatus);
    }
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_WriteSinkDPCDDownSpreadEnabled()
   
   This function will indicate that downspread has been enabled on host side.

Parameters:
   pDisplayCtx  -[in]    : DP Display Context

Return: 
   DP_Status 

**********************************************************************************************************************/
DP_Status DP_WriteSinkDPCDDownSpreadEnabled(DP_DisplayCtxType    *pDisplayCtx)
{
  DP_Status                eStatus         = DP_STATUS_SUCCESS;  
  DP_DeviceCtxType        *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_WriteSinkDPCDLevels: Unexpected null context.");
  }
  else
  {
    uint8 uDownspreadCtrl = 0x10; // Bit 4: SPREAD_AMP

    DP_WritePacketType sWritePacket;
    uint8              uWriteBuffer = uDownspreadCtrl;    

    DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
    sWritePacket.eTransactionType    = DP_TRANSACTION_MODE_AUX;
    sWritePacket.puWriteData         = &uWriteBuffer;
    sWritePacket.uAddress            = DPCD_LINK_DOWNSPREAD_CTRL_ADDRESS;
    sWritePacket.uWriteDataSize      = DPCD_LINK_DOWNSPREAD_CTRL_LEN;
    sWritePacket.uBytesWritten       = 0;
    sWritePacket.bQueueOnly          = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP_WriteSinkDPCDDownSpreadEnabled: Write Failed, eStatus=0x%x.", eStatus);
    }
		
    TraceInfo(QdiTraceDP, "DP%d: SSC Enabled, eStatus= 0x%x", 
	          pDisplayCtx->pDeviceCtx->eDisplayID, 
		      eStatus);
    
  }

  return eStatus;
}



/**********************************************************************************************************************

FUNCTION: DP_WriteSinkDPCDPower()
   
   This function will set the sink power state. i.e Power on/off for main link or AUX

Parameters:
   pDisplayCtx                      -[in ] Pointer to context
   ePowerState                      -[in ] Sink power state to be set

Return: 
   DP_Status 

**********************************************************************************************************************/
DP_Status DP_WriteSinkDPCDPower(DP_DisplayCtxType     *pDisplayCtx,
                                DP_DPCDPowerStateType  ePowerState)
{
  DP_Status                eStatus = DP_STATUS_SUCCESS;  
  DP_DeviceCtxType        *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_WriteSinkDPCDPower: Unexpected null context.");
  }
  else
  {
    if (DP_STATUS_SUCCESS != (eStatus = WriteSinkDPCDPower(pDisplayCtx, ePowerState)))
    {
      DP_LOG_MESSAGE_ERROR("DP_WriteSinkDPCDPower: Write Failed, eStatus=0x%x.", eStatus);
    }

    TraceInfo(QdiTraceDP, "DP%d: Set Sink Power - state:%d, status:0x%x",
              pDeviceCtx->eDisplayID, 
              ePowerState, 
              eStatus);
  }

  if (DP_STATUS_SUCCESS == eStatus)
  {
    // Allow a minimal delay to give sink the time to transition to the new power state
    DISP_OSAL_SleepMs(1);
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ReadTestLinkSetting()

  This function will read DPCD test request fields for link rate and lane numbers

Parameters:
  pDisplayCtx                      -[in ] Pointer to context

Return:
  DP_Status
**********************************************************************************************************************/
DP_Status DP_ReadTestLinkSetting(DP_DisplayCtxType      *pDisplayCtx)
{
  DP_Status               eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType       *pDeviceCtx;
  DP_StreamCtxType       *pStreamCtx;
  
  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadTestLinkSetting: Unexpected null context.");
  }
  else
  {
    uint32               uTestLinkRate = 0;
    uint32               uSwing        = 0;
    DP_ReadPacketType    sReadPacket;
    
    /*Read DPCD Data*/
    sReadPacket.eTransactionType  = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer  = (uint8*)&uTestLinkRate;
    sReadPacket.uAddress          = DPCD_TEST_LINK_RATE_ADDRESS;
    sReadPacket.uReadSize         = DPCD_TEST_LINK_RATE_LEN;
    sReadPacket.uBytesRead        = 0;
    sReadPacket.bQueueOnly        = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      TraceInfo(QdiTraceDP, "DP%d: DP_ReadTestRequest: Read address(0x%x) Failed. eStatus=0x%x",
        pDeviceCtx->eDisplayID, sReadPacket.uAddress, eStatus);
    }
    else
    {
      switch (uTestLinkRate)
      {
      case  DPCD_SPEC_MAX_LINK_RATE_1_62GBPS:
      {
        pDeviceCtx->uLinkRateInKhz = 162000;
        break;
      }
      case  DPCD_SPEC_MAX_LINK_RATE_2_7GBPS:
      {
        pDeviceCtx->uLinkRateInKhz = 270000;
        break;
      }
      case  DPCD_SPEC_MAX_LINK_RATE_5_4GBPS:
      {
        pDeviceCtx->uLinkRateInKhz = 540000;
        break;
      }
      case  DPCD_SPEC_MAX_LINK_RATE_8_1GBPS:
      {
        pDeviceCtx->uLinkRateInKhz = 810000;
        break;
      }
      default:
      {
        pDeviceCtx->uLinkRateInKhz = 0;
        break;
      }
      }
      pStreamCtx->uDirtyBits |= DP_DIRTYFIELD_LINK_RATE;
    }
    
    sReadPacket.puReadDataBuffer  = (uint8*)&(pDeviceCtx->uNumLanes);
    sReadPacket.uAddress          = DPCD_TEST_LANE_COUNT_ADDRESS;
    sReadPacket.uReadSize         = DPCD_TEST_LANE_COUNT_LEN;
    
    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      TraceInfo(QdiTraceDP, "DP%d: DP_ReadTestLinkSetting: Read address:0x%x Failed, eStatus=0x%x.",
                pDeviceCtx->eDisplayID,
                sReadPacket.uAddress,
                eStatus);
    }
    else
    {
      pStreamCtx->uDirtyBits |= DP_DIRTYFIELD_LANE_NUMBER;
    }
    
    /*Read DPCD Data*/
    sReadPacket.eTransactionType  = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer  = (uint8*)&uSwing;
    sReadPacket.uAddress          = DPCD_TEST_LINK_SWING_ADDRESS;
    sReadPacket.uReadSize         = DPCD_TEST_LINK_SWING_LEN;
    sReadPacket.uBytesRead        = 0;
    sReadPacket.bQueueOnly        = FALSE;
    
    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      TraceInfo(QdiTraceDP, "DP%d: DP_ReadTestRequest: Read address:0x%x Failed, eStatus=0x%x.",
                pDeviceCtx->eDisplayID,
                sReadPacket.uAddress,
                eStatus);
    }
    else
    {
      pDeviceCtx->uPreEmphasisLevel  = (uSwing >> 2) & 0x3;
      pDeviceCtx->uVoltageSwingLevel = (uSwing & 0x3); 
    }
    
    TraceInfo(QdiTraceDP, "DP%d: Test Link Settings Rate=%d Lane#=%d PreEmphasis=0x%x  Swing=0x%x",
              pStreamCtx->eDisplayID,
              pDeviceCtx->uLinkRateInKhz,
              pDeviceCtx->uNumLanes,
              pDeviceCtx->uPreEmphasisLevel,
              pDeviceCtx->uVoltageSwingLevel);
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ReadTestRequest()

  This function will read DPCD test request fields for compliance test.

Parameters:
   pDisplayCtx                      -[in ] Pointer to context

Return:
  DP_Status
**********************************************************************************************************************/
DP_Status DP_ReadTestRequest(DP_DisplayCtxType      *pDisplayCtx)
{
  DP_Status               eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType       *pDeviceCtx;
  DP_StreamCtxType       *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadTestRequest: Unexpected null context.");
  }
  else
  {
    uint32                  uDeviceServiceIRQVector = 0;
    DP_ReadPacketType       sReadPacket;

    if (DP_STATUS_SUCCESS != DP_ReadSinkStatus(pDisplayCtx))
    {
      TraceInfo(QdiTraceDP, "DP%d: DP_ReadTestRequest: DP_ReadSinkStatus failed", pStreamCtx->eDisplayID);
    }
    else if (0 == pDeviceCtx->uSinkCount)
    {
      TraceInfo(QdiTraceDP, "DP%d: Sink is plugged out", pStreamCtx->eDisplayID);
      pDeviceCtx->bPluggedIn = FALSE;
    }
    else
    {
      pDeviceCtx->bPluggedIn = TRUE;

      /*Read DPCD Data*/
      DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
      sReadPacket.eTransactionType = DP_TRANSACTION_MODE_AUX;
      sReadPacket.puReadDataBuffer = (uint8*)&uDeviceServiceIRQVector;
      sReadPacket.uAddress         = DPCD_DEVICE_SERVICE_IRQ_VECTOR_ADDRESS;
      sReadPacket.uReadSize        = DPCD_DEVICE_SERVICE_IRQ_VECTOR_LEN;
      sReadPacket.uBytesRead       = 0;
      sReadPacket.bQueueOnly       = FALSE;
    
      // Check for any test requests
      if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
      {
        TraceInfo(QdiTraceDP, "DP%d: DP_ReadTestRequest: Read address(0x%x) Failed, eStatus=0x%x.",
                  pStreamCtx->eDisplayID,
                  sReadPacket.uAddress,
                  eStatus);
      }
      else if (uDeviceServiceIRQVector & DPCD_AUTOMATED_TEST_REQUEST)
      {
        TraceInfo(QdiTraceDP, "DP%d: Test IRQ detected", pStreamCtx->eDisplayID);

        sReadPacket.uAddress          = DPCD_TEST_REQUEST_ADDRESS;
        sReadPacket.uReadSize         = DPCD_TEST_REQUEST_LEN;
        sReadPacket.puReadDataBuffer  = (uint8*)&pDeviceCtx->ePendingTestRequest;

        if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
        {
          TraceInfo(QdiTraceDP, "DP%d: DP_ReadTestRequest: Read address(0x%x) Failed, eStatus=0x%x.",
                    pStreamCtx->eDisplayID,
                    sReadPacket.uAddress,
                    eStatus);
        }
        else if (DP_TEST_NONE != pDeviceCtx->ePendingTestRequest)
        {
          TraceInfo(QdiTraceDP, "DP%d: Test Request = 0x%x",
                    pStreamCtx->eDisplayID,
                    pDeviceCtx->ePendingTestRequest);

          switch (pDeviceCtx->ePendingTestRequest)
          {
          case DP_TEST_LINK_TRAINING:
          {
            DP_ReadTestLinkSetting(pDisplayCtx);
            break;
          }
          case DP_TEST_EDID_READ:
          {
            break;
          }
          case DP_TEST_PATTERN:
          {
            /* These tests will be run manually using displayTool. However there are cases which require support for 18bpp while EDID indicates 24bpp
               We just handle that case here */
            uint8       uRegValue         = 0;
          
            sReadPacket.puReadDataBuffer  = &uRegValue;
            sReadPacket.uAddress          = DPCD_TEST_BIT_DEPTH_ADDRESS;
            sReadPacket.uReadSize         = DPCD_TEST_BIT_DEPTH_LEN;
          
            if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
            {
              TraceInfo(QdiTraceDP, "DP%d: DP_ReadTestRequest: Read address(0x%x) Failed, eStatus=0x%x.",
                        pStreamCtx->eDisplayID,
                        sReadPacket.uAddress,
                        eStatus);
            
              // No action to take for this test request
              pDeviceCtx->ePendingTestRequest = DP_TEST_NONE;
            }
            else
            {
              /* override device bit depth based on DPCD setting during CTS test. */
              uint32 uBitDepth;

              /* Parse DPCD bit depth */
              switch ((uRegValue & DPCD_TEST_MISC_BIT_DEPTH_BMSK) >> DPCD_TEST_MISC_BIT_DEPTH_SHFT)
              {
                case DPCD_TEST_MISC_BIT_DEPTH_6BPP:
                {
                  uBitDepth = DP_BITDEPTH_6BPC;
                  break;
                }
                case DPCD_TEST_MISC_BIT_DEPTH_8BPP:
                {
                  uBitDepth = DP_BITDEPTH_8BPC;
                  break;
                }
                default:
                {
                  TraceInfo(QdiTraceDP, "DP%d: DP_ReadTestRequest: Unsupported color bit depth, uRegValue =0x%x.",
                            pStreamCtx->eDisplayID,
                            (uRegValue & DPCD_TEST_MISC_BIT_DEPTH_BMSK) >> DPCD_TEST_MISC_BIT_DEPTH_SHFT);

                  uBitDepth = DP_BITDEPTH_NONE;
                  break;
                }
              }

              if (uBitDepth != pStreamCtx->uBitDepth)
              {
                pStreamCtx->uBitDepth   = uBitDepth;
                pStreamCtx->uDirtyBits |= DP_DIRTYFIELD_BPC;
              }
              else
              {
                /* No action to take as we are already set to the right BPC */
                pDeviceCtx->ePendingTestRequest = DP_TEST_NONE;
              }
            }
            break;
          }
          case DP_TEST_PHY_PATTERN:
          {
            sReadPacket.uAddress          = DPCD_TEST_PHY_TEST_PATTERN_ADDRESS;
            sReadPacket.uReadSize         = DPCD_TEST_PHY_TEST_PATTERN_LEN;
            sReadPacket.puReadDataBuffer  = (uint8*)&pDeviceCtx->ePhyTestPattern;

            if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
            {
              TraceInfo(QdiTraceDP, "DP%d: DP_ReadTestRequest: Read address(0x%x) Failed, eStatus=0x%x",
                        pStreamCtx->eDisplayID,
                        sReadPacket.uAddress,
                        eStatus);
            }
            else if (DP_STATUS_SUCCESS != (eStatus = DP_ReadTestLinkSetting(pDisplayCtx)))
            {
              TraceInfo(QdiTraceDP, "DP%d: DP_ReadTestRequest: DP_ReadTestLinkSetting Failed, eStatus=0x%x.",
                        pStreamCtx->eDisplayID,
                        eStatus);
            }
            else
            {
              TraceInfo(QdiTraceDP, "DP%d: Test Request (Phy Pattern) = 0x%x",
                        pStreamCtx->eDisplayID,
                        pDeviceCtx->ePhyTestPattern);
              pDeviceCtx->ePendingTestRequest = DP_TEST_PHY_PATTERN;
              pDeviceCtx->eLinkTrainingType   = DP_LINK_TRAINING_TYPE_NO_TRAINING;
            }
            break;
          }
          default:
            TraceInfo(QdiTraceDP, "DP%d: Test Request = 0x%x not handled",
                      pStreamCtx->eDisplayID,
                      pDeviceCtx->ePendingTestRequest);
            pDeviceCtx->ePendingTestRequest = DP_TEST_NONE;
            break;
          }
        }
      }
      else
      {
        pDeviceCtx->ePendingTestRequest = DP_TEST_NONE;
      }
    }
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_WriteTestResponse()

This function will write DPCD test response fields for compliance test.

Parameters:
   pDisplayCtx                      -[in ] Pointer to context

Return:
DP_Status

**********************************************************************************************************************/
DP_Status DP_WriteTestResponse(DP_DisplayCtxType      *pDisplayCtx)
{
  DP_Status                eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType        *pDeviceCtx;
  DP_StreamCtxType        *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_WriteTestResponse: Unexpected null context.");
  }
  else
  {
    DP_WritePacketType       sWritePacket;
    uint8                    uWriteBuffer;
    
    DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));

    /* Sink request EDED testing*/
    if (DP_TEST_EDID_READ == pDeviceCtx->ePendingTestRequest)
    {
      if (pStreamCtx->uEDIDDataLength)
      {
        /* Write checksum of last EDID block */
        DP_OSAL_MemSet(&sWritePacket, 0x0, sizeof(sWritePacket));
        uWriteBuffer                    = pStreamCtx->auEDIDCache[pStreamCtx->uEDIDDataLength - 1];
        sWritePacket.puWriteData        = &uWriteBuffer;
        sWritePacket.eTransactionType   = DP_TRANSACTION_MODE_AUX;
        sWritePacket.uAddress           = DPCD_TEST_EDID_CHECKSUM_ADDRESS;
        sWritePacket.uWriteDataSize     = DPCD_TEST_EDID_CHECKSUM_LEN;
        sWritePacket.uBytesWritten      = 0;
        sWritePacket.bQueueOnly         = FALSE;
        eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket);
    
        /*Notify sink that EDID checksum has been written to the TEST_EDID_CHECKSUM register.*/
        uWriteBuffer                     = DPCD_TEST_RESPONSE_EDID_CHECKSUM_WRITE;
        sWritePacket.uAddress            = DPCD_TEST_RESPONSE_ADDRESS;
        sWritePacket.uWriteDataSize      = DPCD_TEST_RESPONSE_LEN;
        sWritePacket.uBytesWritten       = 0;
        eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket);
      }
    }
    
    /* No Ack for video pattern tests as they are run manually */
    if ((DP_TEST_NONE    != pDeviceCtx->ePendingTestRequest) &&
        (DP_TEST_PATTERN != pDeviceCtx->ePendingTestRequest))
    {
      /* Positive acknowledgment of the TEST_REQ.  */
      DP_OSAL_MemSet(&sWritePacket, 0x0, sizeof(sWritePacket));    
      uWriteBuffer                     = DPCD_TEST_RESPONSE_ACK;
      sWritePacket.puWriteData         = &uWriteBuffer;
      sWritePacket.eTransactionType    = DP_TRANSACTION_MODE_AUX;
      sWritePacket.uAddress            = DPCD_TEST_RESPONSE_ADDRESS;
      sWritePacket.uWriteDataSize      = DPCD_TEST_RESPONSE_LEN;
      sWritePacket.uBytesWritten       = 0;
      sWritePacket.bQueueOnly          = FALSE;
      eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket);
    }
    
    if (DP_TEST_PHY_PATTERN == pDeviceCtx->ePendingTestRequest)
    {
      // Acknowledge the test request
      DP_OSAL_MemSet(&sWritePacket, 0x0, sizeof(sWritePacket));
      sWritePacket.puWriteData        = &uWriteBuffer;
      sWritePacket.eTransactionType   = DP_TRANSACTION_MODE_AUX;
      sWritePacket.uAddress           = DPCD_DEVICE_SERVICE_IRQ_VECTOR_ADDRESS;
      sWritePacket.uWriteDataSize     = DPCD_DEVICE_SERVICE_IRQ_VECTOR_LEN;
      sWritePacket.uBytesWritten      = 0;
      sWritePacket.bQueueOnly         = FALSE;
    
      if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket)))
      {
        TraceInfo(QdiTraceDP, "DP%d: DP_WriteTestResponse: DP_Host_AuxWriteRaw failed, eStatus=0x%x.",
                  pStreamCtx->eDisplayID,
                  eStatus);
      }
    }
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ReadSinkStatus()

This function will read sink status register for sink count and CP readiness. 

Parameters:
   pDisplayCtx                      -[in ] Pointer to context

Return:
DP_Status

**********************************************************************************************************************/
DP_Status  DP_ReadSinkStatus(DP_DisplayCtxType      *pDisplayCtx)
{
  DP_Status                       eStatus       = DP_STATUS_SUCCESS;  
  DP_DeviceCtxType               *pDeviceCtx    = DPHOST_GET_DEVICE_CTX(pDisplayCtx);

  if (NULL == pDeviceCtx)
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkStatus: Unexpected null context.");
  }
  else
  {
    uint8                           uSinkStatus[DPCD_SINK_STATUS_LEN];
    DP_ReadPacketType               sReadPacket;
    DP_DPCDSinkStatusType           sSinkDPCDStatus;

    /*Read DPCD Data*/
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    DP_OSAL_MemSet(&uSinkStatus,     0, sizeof(uSinkStatus));
    sReadPacket.eTransactionType     = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer     = (uint8*)&uSinkStatus;
    sReadPacket.uAddress             = DPCD_SINK_STATUS_ADDRESS;
    sReadPacket.uReadSize            = DPCD_SINK_STATUS_LEN;
    sReadPacket.uBytesRead           = 0;
    sReadPacket.bQueueOnly           = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      pDeviceCtx->bLinkLost = TRUE;
      TraceInfo(QdiTraceDP, "DP%d: DP_ReadSinkStatus: Read address(0x%x) Failed, eStatus=0x%x",
                pDeviceCtx->eDisplayID,
                sReadPacket.uAddress,
                eStatus);
    }
    else
    {
      bool32 bPortStatus  = (uSinkStatus[4] & DPCD_LANE_STATUS_DS_PORT_STATUS_MASK) ? TRUE : FALSE;
      uint32 uSinkCount   = (uint32)(uSinkStatus[0] & DPCD_SPEC_SINK_COUNT_SINK_COUNT_BMSK);

      if (FALSE == bPortStatus)
      {
        // In case bridge dongle does not update Downstream port status register.
        if (uSinkCount != pDeviceCtx->uSinkCount)
        {
          bPortStatus = TRUE;
        }
        else
        {
          bPortStatus = FALSE;
        }
      }

      pDeviceCtx->uFlags                        = bPortStatus? DPHOST_SETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_DS_PORT_STATUS_CHANGED): DPHOST_CLEARFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_DS_PORT_STATUS_CHANGED);
      pDeviceCtx->uSinkCount                    = uSinkCount;
      pDeviceCtx->bCPReady                      = (uSinkStatus[0] & DPCD_SINK_STATUS_CP_READY_MASK) ? TRUE : FALSE;
      pDeviceCtx->uDeviceServiceIRQVector       = uSinkStatus[1];

      // Check Link status only if it was already configured
      if (TRUE == pDeviceCtx->bLinkConfigured)
      {
        DP_OSAL_MemSet(&sSinkDPCDStatus, 0, sizeof(sSinkDPCDStatus));
        DP_ParseSinkDPCDStatus((uint8 *)&uSinkStatus[2], &sSinkDPCDStatus, FALSE);
        if ((TRUE == DP_CheckTrainingResult(pDisplayCtx, &sSinkDPCDStatus, DP_LINK_TRAINING_STATUS_CHANNEL_EQ_DONE))   &&
            (TRUE == DP_CheckTrainingResult(pDisplayCtx, &sSinkDPCDStatus, DP_LINK_TRAINING_STATUS_SYMBOL_LOCKED))     &&
            (TRUE == DP_CheckTrainingResult(pDisplayCtx, &sSinkDPCDStatus, DP_LINK_TRAINING_STATUS_CLK_RECOVERY_DONE)) &&
            (TRUE == DP_CheckTrainingResult(pDisplayCtx, &sSinkDPCDStatus, DP_LINK_TRAINING_STATUS_INTERLANE_ALIGN_DONE)))
        {
          pDeviceCtx->bLinkLost = FALSE;
        }
        else
        {
          pDeviceCtx->bLinkLost = TRUE;
        }
      }
      else
      {
        pDeviceCtx->bLinkLost = TRUE;
      }

      // Branch device has a upstream port connected to source(MSM), and downstream port(s) connected to sink(monitor)
      if (pDeviceCtx->sSinkDPCDCap.eDPCDCap & DP_DPCD_CAP_DWN_STRM_PORT_PRESENT)
      {
        // Downstream port connection status changed
        if (TRUE == DPHOST_GETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_DS_PORT_STATUS_CHANGED))
        {
          if (0 == pDeviceCtx->uSinkCount)
          {
            // IRQ HPD OUT, sink is removed from downstream port from branch device, 
            pDeviceCtx->uFlags = DPHOST_SETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_IRQ_HPD_OUT);
            TraceInfo(QdiTraceDP, "DP%d: Branch device HPD but no sink attached downstream", pDeviceCtx->eDisplayID);
          }
          else
          {
            //IRQ HPD IN, sink is plugged in to downstream port.
            pDeviceCtx->uFlags = DPHOST_CLEARFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_IRQ_HPD_OUT);
            TraceInfo(QdiTraceDP, "DP%d: IRQ HPD IN detected", pDeviceCtx->eDisplayID);
          }

          pDeviceCtx->uFlags = DPHOST_CLEARFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_REDUNDANT_IRQ_HPD);
        }
        else
        {
          if ((FALSE == pDeviceCtx->bLinkLost) &&
              (0     == pDeviceCtx->uDeviceServiceIRQVector))
          {
            // No changes in downstream port, no IRQ vector setting, and DP is up and running, sink is sending redundant IRQ HPD
            pDeviceCtx->uFlags = DPHOST_SETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_REDUNDANT_IRQ_HPD);
            TraceInfo(QdiTraceDP, "DP%d: No Downstream Port changed and link has been setup", pDeviceCtx->eDisplayID);
          }
          else
          {
            pDeviceCtx->uFlags = DPHOST_CLEARFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_REDUNDANT_IRQ_HPD);
          }
        }
      }
      else
      {
        // Direct connected sink should not request IRQ HPD OUT event
        pDeviceCtx->uFlags = DPHOST_CLEARFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_IRQ_HPD_OUT | DP_HOST_FLAG_REDUNDANT_IRQ_HPD);
      }

      TraceInfo(QdiTraceDP, "DP%d: Sink Status - branchDevice:%d, portType:%d, connectedSinks:%d, uFlags:0x%x, linkLost:%d, sinkIRQVector:0x%x",
                pDeviceCtx->eDisplayID,
                (pDeviceCtx->sSinkDPCDCap.eDPCDCap & DP_DPCD_CAP_DWN_STRM_PORT_PRESENT) ? 1 : 0,
                pDeviceCtx->sSinkDPCDCap.eDwnStreamPortType,
                pDeviceCtx->uSinkCount,
                pDeviceCtx->uFlags,
                pDeviceCtx->bLinkLost,
                pDeviceCtx->uDeviceServiceIRQVector);

    }
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ReadSinkSymbolStatus()

This function will read sink registers for symbol error counts. 

Parameters:
   pDisplayCtx                      -[in ] Pointer to context
   pDisplayCtx                      -[out] Pointer to fetch symbol errors (optional)

Return:
DP_Status

**********************************************************************************************************************/
DP_Status  DP_ReadSinkSymbolStatus(DP_DisplayCtxType       *pDisplayCtx,
                                   DP_SinkSymbolStatusType *pSymbolStatusRawData)
{
  DP_Status                 eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType         *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkSymbolStatus: Unexpected null context.");
  }
  else
  {
    DP_SinkSymbolStatusType  sSymbolStatusRead;
    DP_ReadPacketType        sReadPacket;

    //Read DPCD Data
    DP_OSAL_MemSet(&sReadPacket,       0, sizeof(DP_ReadPacketType));
    DP_OSAL_MemSet(&sSymbolStatusRead, 0, sizeof(DP_SinkSymbolStatusType));
    sReadPacket.eTransactionType          = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer          = (uint8*)&sSymbolStatusRead;
    sReadPacket.uAddress                  = DP_GetRepeaterDPCDOffset(pDeviceCtx->eLTTPRRepeaterID, DPCD_SINK_SYMBOL_STATUS_ADDRESS);
    sReadPacket.uReadSize                 = sizeof(DP_SinkSymbolStatusType);
    sReadPacket.uBytesRead                = 0;
    sReadPacket.bQueueOnly                = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      TraceInfo(QdiTraceDP, "DP%d: Reading sink symbol status at address(0x%x) Failed, eStatus=0x%x",
                pDeviceCtx->eDisplayID,
                sReadPacket.uAddress,
                eStatus);
    }
    else 
    {
      // Log the symbol error counts
      if (DPHOST_CHECK_IS_LTTPR_REPEATER(pDeviceCtx))
      {
        TraceVerb(QdiTraceDiag, 
                  "DP%i: LTTPR%i: lane symbol status (ex F0035h-F003Ch): Lane0:0x%x, Lane1:0x%x, Lane2:0x%x, Lane3:0x%x",
                   pDeviceCtx->eDisplayID,
                   pDeviceCtx->eLTTPRRepeaterID,
                   sSymbolStatusRead.uErrorCountLane0,
                   sSymbolStatusRead.uErrorCountLane1,
                   sSymbolStatusRead.uErrorCountLane2,
                   sSymbolStatusRead.uErrorCountLane3);
      }
      else
      {
        TraceVerb(QdiTraceDiag, 
                  "DP%i: Sink lane symbol status (210h-217h): Lane0:0x%x, Lane1:0x%x, Lane2:0x%x, Lane3:0x%x",
                  pDeviceCtx->eDisplayID,
                  sSymbolStatusRead.uErrorCountLane0,
                  sSymbolStatusRead.uErrorCountLane1,
                  sSymbolStatusRead.uErrorCountLane2,
                  sSymbolStatusRead.uErrorCountLane3);
      }
    
      if (NULL != pSymbolStatusRawData)
      {
        // Return the data read
        DISP_OSAL_MemCpyEx(pSymbolStatusRawData, sizeof(DP_SinkSymbolStatusType),
                           &sSymbolStatusRead, sizeof(DP_SinkSymbolStatusType));
      }
    }
  }

  return eStatus;
}
/**********************************************************************************************************************

FUNCTION: DP_WriteSinkPSRConfiguration()

This function will enable/disable PSR and set PSR config. 

Parameters:
   pDeviceCtx                       -[in ] Pointer to device context
   pPSRCfg                          -[in ] Pointer to PSR config

Return:
DP_Status

**********************************************************************************************************************/
DP_Status  DP_WriteSinkPSRConfiguration(DP_DisplayCtxType *pDisplayCtx, 
                                        DP_PSRCfgType     *pPSRCfg)
{
  DP_Status           eStatus       = DP_STATUS_SUCCESS;  
  uint8               uData         = 0;
  DP_WritePacketType  sWritePacket;
  
  if (DP_PSR_MODE_DISABLE != pPSRCfg->ePSRMode)
  {
    uData |= DPCD_SPEC_PSR_ENABLE;
  }
  if (pPSRCfg->bMainLinkActive)
  {
    uData |= DPCD_SPEC_PSR_SRC_TX_ACTIVE;
  }
  if (pPSRCfg->bVerifyCRC)
  {
    uData |= DPCD_SPEC_PSR_VERIFY_CRC;
  }
  if (pPSRCfg->bCaptureSecondFrame)
  {
    uData |= DPCD_SPEC_I2C_PSR_FRAME_CAPTURE;
  }
  if (DP_PSR_MODE_ENABLE_PSR2 == pPSRCfg->ePSRMode)
  {
    uData |= DPCD_SPEC_PSR2_ENABLE;
  }
  
  /* Write DPCD Data*/
  DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
  sWritePacket.eTransactionType    = DP_TRANSACTION_MODE_AUX;
  sWritePacket.puWriteData         = &uData;
  sWritePacket.uAddress            = DPCD_PSR_ENABLE_CONFIG_ADDRESS;
  sWritePacket.uWriteDataSize      = DPCD_PSR_ENABLE_CONFIG_LEN;
  sWritePacket.uBytesWritten       = 0;
  sWritePacket.bQueueOnly          = FALSE;
  
  eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket);
  if (DP_STATUS_SUCCESS != eStatus)
  {
    DP_LOG_MESSAGE_ERROR( "DP_WriteSinkPSRConfiguration: Write Failed, eStatus=0x%x.",eStatus);
  }
  
  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkALPMConfig
//
//  @brief
//      This function will toggle sink's ALPM feature
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] bEnable
//          TRUE:  Enable ALPM ; FALSE: Disable ALPM
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteSinkALPMConfig(DP_DisplayCtxType* pDisplayCtx, bool32 bEnable)
{
  DP_Status           eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType*   pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_WriteSinkALPMConfig: Unexpected null context.");
  }
  else
  {
    uint8               uData = 0;
    DP_WritePacketType  sWritePacket;

    uData = (bEnable) ? 0x01 : 0x00;

    /* Write DPCD Data*/
    DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
    sWritePacket.eTransactionType = DP_TRANSACTION_MODE_AUX;
    sWritePacket.puWriteData      = &uData;
    sWritePacket.uAddress         = DPCD_ALPM_ENABLE_START_ADDRESS;
    sWritePacket.uWriteDataSize   = DPCD_ALPM_ENABLE_LEN;
    sWritePacket.uBytesWritten    = 0;
    sWritePacket.bQueueOnly       = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP%d: DP_WriteSinkALPMConfig: Write Failed, eStatus=0x%x.", pDeviceCtx->eControllerID, eStatus);
    }
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ParseSinkDSCCap()

This function will parse sink DSC Capabilities data 

Parameters:
   pRawData                      -[in ] buffer contains sink PSR data
   pSinkDSCCap                   -[in ] pointer of DSC struct

Return:
DP_Status

**********************************************************************************************************************/
static void  DP_ParseSinkDSCCap(uint8              *pRawData,
                                DP_SinkDSCCapType  *pSinkDSCCap)
{
  if (pRawData != NULL) 
  {
    /* dpcd 0x60 */
    pSinkDSCCap->bSupported = (pRawData[0] & 0x1);

    if (TRUE == pSinkDSCCap->bSupported)
    {
      /* dpcd 0x61 */
      pSinkDSCCap->uMajor = pRawData[1] & 0x0f;
      pSinkDSCCap->uMinor = (pRawData[1] >> 4);

      if (((pSinkDSCCap->uMajor < DSC_MAJOR_VERSION_SUPPORT_MIN) ||
           (pSinkDSCCap->uMajor > DSC_MAJOR_VERSION_SUPPORT_MAX))||
          ((pSinkDSCCap->uMinor < DSC_MINOR_VERSION_SUPPORT_MIN) ||
           (pSinkDSCCap->uMinor > DSC_MINOR_VERSION_SUPPORT_MAX)))
      {
        /* Check if reported DSC version is supported*/
        pSinkDSCCap->bSupported = FALSE;
      }
      else
      {
        /* dpcd 0x62 */
        switch (pRawData[2])
        {
        case 0:
          pSinkDSCCap->uRCBufferSize = 1024;   /* 1k */
          break;
        case 1:
          pSinkDSCCap->uRCBufferSize = 4096;   /* 4k */
          break;
        case 2:
          pSinkDSCCap->uRCBufferSize = 16384;  /* 16k */
          break;
        case 3:
          pSinkDSCCap->uRCBufferSize = 65536;  /* 64 */
          break;
        default:
          pSinkDSCCap->uRCBufferSize = 0;
          break;
        }

        /* dpcd 0x63 */
        pSinkDSCCap->uRCBufferSize *= (pRawData[3] + 1);

        /* dpcd 0x64 */
        pSinkDSCCap->uSliceSupported = pRawData[4];

        /* dpcd 0x6d */
        pSinkDSCCap->uSliceSupported |= (pRawData[13] << 8);

        /* dpcd 0x65 */
        if (8 == (pRawData[5] & 0xf))
        {
          pSinkDSCCap->uLineBufBitDepth = 8;
        }
        else
        {
          pSinkDSCCap->uLineBufBitDepth = pRawData[5] + 9;
        }

        /* dpcd 0x66 */
        if (pRawData[6] & 0x1)
        {
          pSinkDSCCap->bBlockPrediction = TRUE;
        }

        /* MaxBitsPerPixel is used at edp 1.4a or higher, U6.4 format */
        /* dpcd 0x67 */
        pSinkDSCCap->uMaxBitsPerPixel = pRawData[7];

        /* dpcd 0x68 */
        pSinkDSCCap->uMaxBitsPerPixel |= ((pRawData[8] & 0x3) << 8);

        /* dpcd 0x69 */
        pSinkDSCCap->uColorFormatCap = (pRawData[9] & 0x1f);

        /* dpcd 0x6a */
        pSinkDSCCap->uColorDepthCap = (pRawData[0xa] & 0xf);

        /* dpcd 0x6b */
        pSinkDSCCap->uPeakThroughputMode0 = (pRawData[0xb] & 0x0f);
        pSinkDSCCap->uPeakThroughputMode1 = (pRawData[0xb] >> 4);

        /* dpcd 0x6c */
        pSinkDSCCap->uMaxSliceWidth = pRawData[0xc] * 320;

        /* dpcd 0x6f */
        pSinkDSCCap->uBitsPerPixelIncrement = (pRawData[0xf] & 0x7);    /* 1/16, 1/8, 1/4, 1/2, 1/1 */
      }
    }
  }
}

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkDSCCap
//
//  @brief
//      This function will read Sink DSC Capability over AUX Channel
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadSinkDSCCap(DP_DisplayCtxType *pDisplayCtx)
{
  DP_Status                eStatus       = DP_STATUS_SUCCESS;  
  DP_DeviceCtxType        *pDeviceCtx;
  DP_StreamCtxType        *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkDSCCap: Unexpected null context.");  
  }
  else
  {
    uint8                           uRawData[DPCD_DSC_CAP_LEN];
    DP_ReadPacketType               sReadPacket;

    /* Read DPCD Data */
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    DP_OSAL_MemSet(&uRawData,    0, sizeof(uRawData));

    sReadPacket.eTransactionType     = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer     = (uint8*)&uRawData;
    sReadPacket.uAddress             = DPCD_DSC_CAP_START_ADDRESS;
    sReadPacket.uReadSize            = DPCD_DSC_CAP_LEN;
    sReadPacket.uBytesRead           = 0;
    sReadPacket.bQueueOnly           = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP_ReadSinkDSCCap: Read Failed, eStatus=0x%x.", eStatus);
    }
    else if (sReadPacket.uBytesRead != sReadPacket.uReadSize)
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DP_LOG_MESSAGE_ERROR("DP_ReadSinkDSCCap: Bytes Read(0x%x) is not expected.", sReadPacket.uBytesRead);
    }
    else
    {
      TraceInfo(QdiTraceDP, "DP%d: DSC caps raw data [0x%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x]",
                pStreamCtx->eDisplayID,
                uRawData[0],  uRawData[1],  uRawData[2],  uRawData[3],
                uRawData[4],  uRawData[5],  uRawData[6],  uRawData[7],
                uRawData[8],  uRawData[9],  uRawData[10], uRawData[11],
                uRawData[12], uRawData[13], uRawData[14], uRawData[15]);

      DP_ParseSinkDSCCap(uRawData, &pStreamCtx->sDSCCaps);

      TraceInfo(QdiTraceDP, "DP%d: DSC caps 1:  supported %d, version: %d.%d, blk_size: %d buf_depth: %d block_prediction: %d",
                pStreamCtx->eDisplayID,
                pStreamCtx->sDSCCaps.bSupported,
                pStreamCtx->sDSCCaps.uMajor,
                pStreamCtx->sDSCCaps.uMinor,
                pStreamCtx->sDSCCaps.uRCBufferSize,
                pStreamCtx->sDSCCaps.uLineBufBitDepth,
                pStreamCtx->sDSCCaps.bBlockPrediction);

      TraceInfo(QdiTraceDP, "DP%d: DSC caps 2: color_format %d, color_depth: %d, peak_throughput_0: %d, peak_throughput_1: %d",
                pStreamCtx->eDisplayID,
                pStreamCtx->sDSCCaps.uColorFormatCap,
                pStreamCtx->sDSCCaps.uColorDepthCap,
                pStreamCtx->sDSCCaps.uPeakThroughputMode0,
                pStreamCtx->sDSCCaps.uPeakThroughputMode1);

      TraceInfo(QdiTraceDP, "DP%d: DSC caps 3: silce_supported %d, max_slice_width: %d, max_bpp: %d bpp_increment: %d",
                pStreamCtx->eDisplayID,
                pStreamCtx->sDSCCaps.uSliceSupported,
                pStreamCtx->sDSCCaps.uMaxSliceWidth,
                pStreamCtx->sDSCCaps.uMaxBitsPerPixel,
                pStreamCtx->sDSCCaps.uBitsPerPixelIncrement);
    
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkDSCStatus
//
//  @brief
//      This function will read sink DSC Status
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadSinkDSCStatus(DP_DisplayCtxType *pDisplayCtx)
{
  DP_Status                       eStatus = DP_STATUS_SUCCESS;  
  DP_DeviceCtxType               *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkDSCStatus: Unexpected null context.");
  }
  else
  {
    uint8                           uRawData[DPCD_DSC_STATUS_LEN];
    DP_ReadPacketType               sReadPacket;
    
    /* Read DPCD Data */
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    sReadPacket.eTransactionType     = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer     = (uint8*)&uRawData;
    sReadPacket.uAddress             = DPCD_DSC_STATUS_START_ADDRESS;
    sReadPacket.uReadSize            = DPCD_DSC_STATUS_LEN;
    sReadPacket.uBytesRead           = 0;
    sReadPacket.bQueueOnly           = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadSinkDSCStatus: Read Failed, eStatus=0x%x.\n",
                           pDeviceCtx->eDisplayID,
                           eStatus);
    }
    else if (sReadPacket.uBytesRead != sReadPacket.uReadSize)
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadSinkDSCStatus: Bytes Read(0x%x) is not expected.\n",
                           pDeviceCtx->eDisplayID,
                           sReadPacket.uBytesRead);
    }
    else
    {
      TraceInfo(QdiTraceDP, "DP%d: DSC Sink status: underrun: %d, overflow: %d, chunk_length: %d",
                pDeviceCtx->eDisplayID, 
                (uRawData[0] & 0x1),
                ((uRawData[0] >> 1) & 0x1),
                ((uRawData[0] >> 2) & 0x1));
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkDSCConfig
//
//  @brief
//      This function will write sink DSC configuration.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] bEnable
//          Flag used to determine if DSC needs to be enabled/disabled
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteSinkDSCConfig(DP_DisplayCtxType *pDisplayCtx, bool32 bEnable)
{
  DP_Status           eStatus = DP_STATUS_SUCCESS;  
  DP_DeviceCtxType   *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_WriteSinkDSCConfig: Unexpected null context.");
  }
  else
  {
    uint8               uData = 0;
    DP_WritePacketType  sWritePacket;

    if (bEnable)
    {
      /* enabled */
      uData = 0x01;
    }
    else
    {
      /* disabled */
      uData = 0x00;
    }
    
    /* Write DPCD Data*/
    DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
    sWritePacket.eTransactionType    = DP_TRANSACTION_MODE_AUX;
    sWritePacket.puWriteData         = &uData;
    sWritePacket.uAddress            = DPCD_DSC_ENABLE_START_ADDRESS;
    sWritePacket.uWriteDataSize      = DPCD_DSC_ENABLE_LEN;
    sWritePacket.uBytesWritten       = 0;
    sWritePacket.bQueueOnly          = FALSE;

    eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket);
    if (DP_STATUS_SUCCESS != eStatus)
    {
      DP_LOG_MESSAGE_ERROR("DP%d: DP_WriteSinkDSCConfig: Write Failed, eStatus=0x%x.",
                            pDeviceCtx->eControllerID,
                            eStatus);
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkDSCEnable
//
//  @brief
//      This function will read DSC enable flag from sink
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadSinkDSCEnable(DP_DisplayCtxType *pDisplayCtx)

{
  DP_Status                       eStatus = DP_STATUS_SUCCESS;  
  DP_DeviceCtxType               *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkDSCEnable: Unexpected null context.");
  }
  else
  {
    uint8                           uRawData[DPCD_DSC_ENABLE_LEN];
    DP_ReadPacketType               sReadPacket;
    
    /* Read DPCD Data */
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    sReadPacket.eTransactionType     = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer     = (uint8*)&uRawData;
    sReadPacket.uAddress             = DPCD_DSC_ENABLE_START_ADDRESS;
    sReadPacket.uReadSize            = DPCD_DSC_ENABLE_LEN;
    sReadPacket.uBytesRead           = 0;
    sReadPacket.bQueueOnly           = FALSE;
    
    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadSinkDSCEnable: Read Failed, eStatus=0x%x.\n",
                           pDeviceCtx->eControllerID,
                           eStatus);
    }
    else if (sReadPacket.uBytesRead != sReadPacket.uReadSize)
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadSinkDSCEnable: Bytes Read(0x%x) is not expected.\n",
                           pDeviceCtx->eControllerID,
                           sReadPacket.uBytesRead);
    }
    else
    {
      TraceInfo(QdiTraceDP, "DP%d: DP_ReadSinkDSCEnable: DSC enabled: %x",
                pDeviceCtx->eDisplayID,
                uRawData[0]);
    }
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ParseSinkFECCap()

This function will parser sink FEC Capabilities register 

Parameters:
   pRawData                       -[in ] buffer contains sink PSR data
   pSinkDSCCap                    -[in ] pointer of DSC struct

Return:
DP_Status

**********************************************************************************************************************/
static void  DP_ParseSinkFECCap(uint8              *pRawData,
                                DP_SinkFECCapType  *pSinkFECCap)
{
  uint8  uData = 0;

  if (pRawData != NULL) 
  {
     uData = pRawData[0]; /* dpcd 0x90 */

     if (0x01 == (uData & 0x01))
     {
        pSinkFECCap->bCapable = TRUE;
     }
     if (0x02 == (uData & 0x02))
     {
        pSinkFECCap->bUncorrectedBlockErrorCountCapable = TRUE;
     }
     if (0x04 == (uData & 0x04))
     {
        pSinkFECCap->bCorrectedBlockErrorCountCapable = TRUE;
     }
     if (0x08 == (uData & 0x08))
     {
        pSinkFECCap->bBitErrorCountCapable = TRUE;
     }

  }

}

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkFECCap
//
//  @brief
//      This function will read Sink FEC Capability over AUX Channel
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadSinkFECCap(DP_DisplayCtxType *pDisplayCtx)

{
  DP_Status                       eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType               *pDeviceCtx;
  DP_StreamCtxType               *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) ||
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkFECCap: Unexpected null context.");
  }
  else
  {
    uint8                           uRawData[DPCD_FEC_CAP_LEN];
    DP_ReadPacketType               sReadPacket;
    
    /* Read DPCD Data */
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    sReadPacket.eTransactionType     = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer     = (uint8*)&uRawData;
    sReadPacket.uAddress             = DPCD_FEC_CAP_START_ADDRESS;
    sReadPacket.uReadSize            = DPCD_FEC_CAP_LEN;
    sReadPacket.uBytesRead           = 0;
    sReadPacket.bQueueOnly           = FALSE;
    
    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadSinkFECCap: Read Failed, eStatus=0x%x.",
                           pDeviceCtx->eControllerID,
                           eStatus);
    }
    else if (sReadPacket.uBytesRead != sReadPacket.uReadSize)
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadSinkFECCap: Bytes Read(0x%x) is not expected.",
                           pDeviceCtx->eControllerID,
                           sReadPacket.uBytesRead);
    }
    else
    {
      TraceInfo(QdiTraceDP, "DP%d: FEC caps raw_data [%x]",
                pStreamCtx->eDisplayID, uRawData[0]);
    
      DP_ParseSinkFECCap(uRawData, &pStreamCtx->sFECCaps);
    
      TraceInfo(QdiTraceDP, "DP%d: FEC caps: capable: %d, uncorrected: %d, corrected: %d, bit_error: %d",
                pStreamCtx->eDisplayID,
                pStreamCtx->sFECCaps.bCapable,
                pStreamCtx->sFECCaps.bUncorrectedBlockErrorCountCapable,
                pStreamCtx->sFECCaps.bCorrectedBlockErrorCountCapable,
                pStreamCtx->sFECCaps.bBitErrorCountCapable);
    
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkFECStatus
//
//  @brief
//      This function will read sink FEC Status
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadSinkFECStatus(DP_DisplayCtxType *pDisplayCtx)
{
  DP_Status                       eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType               *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkFECStatus: Unexpected null context.");
  }
  else
  {
    uint8                           uRawData[DPCD_FEC_STATUS_LEN];
    DP_ReadPacketType               sReadPacket;
    
    /* Read DPCD Data */
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    sReadPacket.eTransactionType     = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer     = (uint8*)&uRawData;
    sReadPacket.uAddress             = DPCD_FEC_STATUS_START_ADDRESS;
    sReadPacket.uReadSize            = DPCD_FEC_STATUS_LEN;
    sReadPacket.uBytesRead           = 0;
    sReadPacket.bQueueOnly           = FALSE;
    
    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadSinkFECStatus: Read Failed, eStatus=0x%x.\n",
                           pDeviceCtx->eControllerID,
                           eStatus);
    }
    else if (sReadPacket.uBytesRead != sReadPacket.uReadSize)
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DP_LOG_MESSAGE_ERROR("DP%d DP_ReadSinkFECStatus: Bytes Read(0x%x) is not expected.\n",
                           pDeviceCtx->eControllerID,
                           sReadPacket.uBytesRead);
    }
    else
    {
      uint32 uDecodeStatus = (uRawData[0] & 0x1);

      if (0 == uDecodeStatus)
      {
        eStatus = DP_STATUS_FAILED_RESOURCE_NOT_READY;
        
        DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadSinkFECStatus: Sink FEC decode is not enabled.\n",
                             pDeviceCtx->eDisplayID);
      }
      
      TraceInfo(QdiTraceDP, "DP%d: Sink FEC status: decode_enable=%d, decode_disable: %d error_valid: %d error_count: %d",
                pDeviceCtx->eDisplayID,
                (uRawData[0] & 0x1),
                ((uRawData[0] >> 1) & 0x1),
                ((uRawData[2] >> 7) & 0x1),
                (((uRawData[2] & 0x7F) << 8 ) | uRawData[1]));
                
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkFECConfig
//
//  @brief
//      This function will write FEC configuration to sink
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//      [IN] bEnable
//          Flag used to determine if FEC needs to be enabled/disabled
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteSinkFECConfig(DP_DisplayCtxType *pDisplayCtx, bool32 bEnable)
{
  DP_Status           eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType   *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_WriteSinkFECConfig: Unexpected null context.");
  }
  else
  {
    uint8               uData         = 0;
    DP_WritePacketType  sWritePacket;

    if (bEnable)
    {
      /* 
       * FEC ready
       * bit error count
       * link 0 for error
       */
      uData = 0x07;
    }
    else
    {
      /* FEC not ready/disabled */
      uData = 0x00;
    }
    
    /* Write DPCD Data*/
    DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
    sWritePacket.eTransactionType    = DP_TRANSACTION_MODE_AUX;
    sWritePacket.puWriteData         = &uData;
    sWritePacket.uAddress            = DPCD_FEC_CONFIG_START_ADDRESS;
    sWritePacket.uWriteDataSize      = DPCD_FEC_CONFIG_LEN;
    sWritePacket.uBytesWritten       = 0;
    sWritePacket.bQueueOnly          = FALSE;
    
    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP%d: DP_WriteSinkFECConfig: Write Failed, eStatus=0x%x.",
                           pDeviceCtx->eDisplayID,
                           eStatus);
    
      TraceInfo(QdiTraceDP, "DP%d: Failed to configure FEC on sink. Status: 0x%x",
                pDeviceCtx->eDisplayID,
                eStatus);
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkFECEnable
//
//  @brief
//      This function will read FEC enable flag from sink
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadSinkFECEnable(DP_DisplayCtxType *pDisplayCtx)
{
  DP_Status                       eStatus = DP_STATUS_SUCCESS;  
  DP_DeviceCtxType               *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkFECEnable: Unexpected null context.");
  }
  else
  {
    uint8                           uRawData[DPCD_FEC_CONFIG_LEN];
    DP_ReadPacketType               sReadPacket;
    
    /* Read DPCD Data */
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    sReadPacket.eTransactionType     = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer     = (uint8*)&uRawData;
    sReadPacket.uAddress             = DPCD_FEC_CONFIG_START_ADDRESS;
    sReadPacket.uReadSize            = DPCD_FEC_CONFIG_LEN;
    sReadPacket.uBytesRead           = 0;
    sReadPacket.bQueueOnly           = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadSinkFECEnable: Read Failed, eStatus=0x%x.\n",
                           pDeviceCtx->eDisplayID,
                           eStatus);
    }
    else if (sReadPacket.uBytesRead != sReadPacket.uReadSize)
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadSinkFECEnable: Bytes Read(0x%x) is not expected.\n",
                           pDeviceCtx->eDisplayID,
                           sReadPacket.uBytesRead);
    }
    else
    {
      uint32 uReadyStatus = (uRawData[0] & 0x1);

      if (0 == uReadyStatus)
      {
        eStatus = DP_STATUS_FAILED_RESOURCE_NOT_READY;
        
        DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadSinkFECEnable: Sink FEC is not in ready state.\n",
                             pDeviceCtx->eDisplayID);
      }
    
      TraceInfo(QdiTraceDP, "DP%d: Sink FEC ready status: ready=%d [Raw Data:0x%x]",
                pDeviceCtx->eDisplayID,
                uReadyStatus,
                uRawData[0]);
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkASSREnable
//
//  @brief
//      Function will enable/disable ASSR mode on the sink
//
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context handle.
//      [IN] bEnable
//          Enable/Disable ASSR
//
//  @return
//      DP_Status 
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteSinkASSREnable(DP_DisplayCtxType *pDisplayCtx, bool32 bEnable)
{
  DP_Status           eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType   *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_WriteSinkASSREnable: Unexpected null context.");
  }
  else
  {
    uint8               uData = bEnable ? 1 : 0;      /* bit 0: Alternate Scrambler Reset Enable */
    DP_WritePacketType  sWritePacket;
    
    /* write DPCD Data*/
    DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
    sWritePacket.eTransactionType    = DP_TRANSACTION_MODE_AUX;
    sWritePacket.puWriteData         = &uData;
    sWritePacket.uAddress            = DPCD_EDP_CONFIGURATION_SET;
    sWritePacket.uWriteDataSize      = DPCD_EDP_CONFIGURATION_SET_LEN;
    sWritePacket.uBytesWritten       = 0;
    sWritePacket.bQueueOnly          = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket)))
    {
      DP_LOG_MESSAGE_ERROR( "DP%d: DP_WriteSinkASSR: Write Failed, eStatus=0x%x.", pDeviceCtx->eControllerID, eStatus);
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkPSRStatus
//
//  @brief
//      Read PSR status from Sink
//
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context handle.
//
//  @return
//      DP_Status 
//-------------------------------------------------------------------------------------------------
DP_Status  DP_ReadSinkPSRStatus(DP_DisplayCtxType *pDisplayCtx)
{
  DP_Status                       eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType               *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkPSRStatus: Unexpected null context.");
  }
  else
  {
    uint8                           uRawData[DPCD_PSR_ERROR_LEN];
    DP_ReadPacketType               sReadPacket;
    
    /* Read DPCD Data */
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    sReadPacket.eTransactionType     = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer     = (uint8*) &uRawData;
    sReadPacket.uAddress             = DPCD_PSR_ERROR_START_ADDRESS;
    sReadPacket.uReadSize            = DPCD_PSR_ERROR_LEN;
    sReadPacket.uBytesRead           = 0;
    sReadPacket.bQueueOnly           = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      TraceInfo(QdiTraceDiag, "DP%d: Read @ 0x%x Failed, eStatus=0x%x.", 
                pDeviceCtx->eDisplayID, 
                DPCD_PSR_ERROR_START_ADDRESS, 
                eStatus);
    }
    else if (sReadPacket.uBytesRead != sReadPacket.uReadSize)
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      TraceInfo(QdiTraceDiag, "DP%d: Read @ 0x%x Failed: Bytes Read(0x%x) is not expected.", 
                pDeviceCtx->eDisplayID, 
                DPCD_PSR_ERROR_START_ADDRESS, 
                sReadPacket.uBytesRead);
    }
    else
    {
      TraceInfo(QdiTraceDiag, "DP%d: Sink PSR status (2006h-200Ah):0x%x,0x%x,0x%x,0x%x,0x%x",
                pDeviceCtx->eDisplayID, 
                uRawData[0], 
                uRawData[1], 
                uRawData[2], 
                uRawData[3], 
                uRawData[4]);
    }
  }
 
  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkCRC
//
//  @brief
//      Read CRC values from Sink
//
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context handle.
//
//  @return
//      DP_Status 
//-------------------------------------------------------------------------------------------------
DP_Status  DP_ReadSinkCRC(DP_DisplayCtxType *pDisplayCtx)
{
  DP_Status                       eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType               *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkCRC: Unexpected null context.");
  }
  else
  {
    uint8                           uRawData[DPCD_PSR_CRC_LEN];
    DP_ReadPacketType               sReadPacket;
    
    /* Read DPCD Data */
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    sReadPacket.eTransactionType     = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer     = (uint8*) &uRawData;
    sReadPacket.uAddress             = DPCD_PSR_CRC_START_ADDRESS;
    sReadPacket.uReadSize            = DPCD_PSR_CRC_LEN;
    sReadPacket.uBytesRead           = 0;
    sReadPacket.bQueueOnly           = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      TraceInfo(QdiTraceDiag, "DP%d: Read @ 0x%x Failed, eStatus=0x%x.", 
                pDeviceCtx->eDisplayID, 
                DPCD_PSR_CRC_START_ADDRESS, 
                eStatus);
    }
    else if (sReadPacket.uBytesRead != sReadPacket.uReadSize)
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      TraceInfo(QdiTraceDiag, "DP%d: Read @ 0x%x Failed: Bytes Read(0x%x) is not expected.", 
                pDeviceCtx->eDisplayID, 
                DPCD_PSR_CRC_START_ADDRESS, 
                sReadPacket.uBytesRead);
    }
    else
    {
      TraceInfo(QdiTraceDiag, "DP%d: Sink CRC status (240h-245h): 0x%x%x,0x%x%x,0x%x%x", 
                pDeviceCtx->eDisplayID, 
                uRawData[1], 
                uRawData[0], 
                uRawData[3], 
                uRawData[2], 
                uRawData[5], 
                uRawData[4]);
    }
  }

  return eStatus;
}
 
//-------------------------------------------------------------------------------------------------
//  DP_WriteGUID
//
//  @brief
//       Write to sink DPCD GUID.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context handle.
//      [IN] pGUID
//          GUID string to be written.
//      [IN] uGUIDSize
//          size of GUID string.
//
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_WriteGUID(DP_DisplayCtxType* pDisplayCtx, uint8* pGUID, uint32 uGUIDSize)
{
  DP_Status            eStatus    = DP_STATUS_SUCCESS;
  DP_DeviceCtxType    *pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  
  if ((NULL == pDeviceCtx) ||
      (NULL == pGUID)      ||
      (uGUIDSize != DPCD_GUID_LEN))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_WriteGUID: Invalid input parameters.");
  }
  else if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWrite(pDisplayCtx, pGUID, uGUIDSize, DPCD_GUID_START_ADDRESS)))
  {
    TraceInfo(QdiTraceDP, "DP%d: DP_WriteGUID() : DP_Host_AuxWrite Failed, eStatus=%d",
              pDeviceCtx->eDisplayID,
              eStatus);
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_ReadDeviceOUI
//
//  @brief
//       Read and log device-specific data of sink and branch which consists of 
//       IEEE Organizational Unique ID (OUI), Device Identification String, and HW/FW version
//
//  @params
//      [IN] pDisplayCtx
//          DP Context handle.
//
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_ReadDeviceOUI(DP_DisplayCtxType *pDisplayCtx)
{
  DP_Status          eStatus    = DP_STATUS_SUCCESS;
  DP_DeviceCtxType  *pDeviceCtx;
  DP_StreamCtxType  *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) ||
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadDeviceOUI: Unexpected null context.");
  }
  else
  {
    uint8  aDeviceSpecificData[DPCD_DEVICE_SPECIFIC_LEN];
    uint32 uDataSize                                          = sizeof(aDeviceSpecificData);
    uint32 uAddress[DP_DEVICESPECIFIC_MAX]                    = { DPCD_SINK_IEEE_OUI_START_ADDRESS, DPCD_BRANCH_IEEE_OUI_START_ADDRESS };
    uint32 i;

    DP_OSAL_MemSet(&aDeviceSpecificData, 0, uDataSize);

    for (i = DP_DEVICESPECIFIC_SINK; i < DP_DEVICESPECIFIC_MAX; i++)
    {
      if ((DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxRead(pDisplayCtx, 
                                                           aDeviceSpecificData, 
                                                           &uDataSize, 
                                                           uAddress[i],
                                                           DP_TRANSACTION_MODE_AUX))))
      {
        TraceInfo(QdiTraceDP, "DP%d: DP_ReadDeviceOUI() : DP_Host_AuxRead Failed, eStatus=%d",
                  pDeviceCtx->eDisplayID,
                  eStatus);
      }
      else
      {
        pStreamCtx->sDeviceSpecificInfo[i].uDataLength      = uDataSize;
        pStreamCtx->sDeviceSpecificInfo[i].aIEEEOUI[0]      = aDeviceSpecificData[0];
        pStreamCtx->sDeviceSpecificInfo[i].aIEEEOUI[1]      = aDeviceSpecificData[1];
        pStreamCtx->sDeviceSpecificInfo[i].aIEEEOUI[2]      = aDeviceSpecificData[2];
        pStreamCtx->sDeviceSpecificInfo[i].aDeviceString[0] = aDeviceSpecificData[3];
        pStreamCtx->sDeviceSpecificInfo[i].aDeviceString[1] = aDeviceSpecificData[4];
        pStreamCtx->sDeviceSpecificInfo[i].aDeviceString[2] = aDeviceSpecificData[5];
        pStreamCtx->sDeviceSpecificInfo[i].aDeviceString[3] = aDeviceSpecificData[6];
        pStreamCtx->sDeviceSpecificInfo[i].aDeviceString[4] = aDeviceSpecificData[7];
        pStreamCtx->sDeviceSpecificInfo[i].aDeviceString[5] = aDeviceSpecificData[8];
        pStreamCtx->sDeviceSpecificInfo[i].aDeviceString[6] = 0;
        pStreamCtx->sDeviceSpecificInfo[i].uHWRevision      = aDeviceSpecificData[9];
        pStreamCtx->sDeviceSpecificInfo[i].uFWMajorRevision = aDeviceSpecificData[10];
        pStreamCtx->sDeviceSpecificInfo[i].uFWMinorRevision = aDeviceSpecificData[11];
        pStreamCtx->sDeviceSpecificInfo[i].bIsLinkCTSDevice = 0;
      }
    }
  }
  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkBrightnessCap
//
//  @brief
//      This function will read Sink Brightness Capability over AUX Channel
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadSinkBrightnessCap(DP_DisplayCtxType *pDisplayCtx)
{
  DP_Status                eStatus       = DP_STATUS_SUCCESS;  
  DP_DeviceCtxType        *pDeviceCtx;
  DP_StreamCtxType        *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkDSCCap: Unexpected null context.");  
  }
  else
  {
    uint8                           uRawData[DPCD_BRIGHTNESS_CAP_LEN];
    DP_ReadPacketType               sReadPacket;

    /* Read DPCD Data */
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    DP_OSAL_MemSet(&uRawData,    0, sizeof(uRawData));

    sReadPacket.eTransactionType     = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer     = (uint8*)&uRawData;
    sReadPacket.uAddress             = DPCD_BRIGHTNESS_CAP_START_ADDRESS;
    sReadPacket.uReadSize            = DPCD_BRIGHTNESS_CAP_LEN;
    sReadPacket.uBytesRead           = 0;
    sReadPacket.bQueueOnly           = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP_ReadSinkBrightnessCap: Display %d - Read Failed, eStatus=0x%x.", 
                           pStreamCtx->eDisplayID, eStatus);
    }
    else if (sReadPacket.uBytesRead != sReadPacket.uReadSize)
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadSinkBrightnessCap: Display %d - Bytes Read(0x%x) is not as expected",
                           pStreamCtx->eDisplayID, sReadPacket.uBytesRead);
    }
    else
    {
      DP_ParseSinkBrightnessCap(pStreamCtx->eDisplayID, uRawData, &pStreamCtx->sBrightnessCaps);
    }
  }

  return eStatus;
}
  
//-------------------------------------------------------------------------------------------------
//  DP_ParseSinkBrightnessCap
//
//  @brief
//      This function will parse sink Brightness Capabilities data 
//
//  @params
//      [IN] eDisplayId
//          Display Id for logging purpose.
//      [IN] pRawData
//          Buffer containing sink Brightness cap data.
//      [IN] pSinkBrightnessCap
//          Pointer of Brightness cap struct
//
//  @return
//      None
//-------------------------------------------------------------------------------------------------
//
static void  DP_ParseSinkBrightnessCap(MDP_Display_IDType        eDisplayId,
                                       uint8                    *pRawData,
                                       DP_SinkBrightnessCapType *pSinkBrightnessCap)
{
  if (pRawData != NULL) 
  {
    TraceInfo(QdiTraceDP, "DP%d: 701h (EDP General Cap) - Raw: 0x%x, \
                           Brightness Adjust: 0x%x, Pin enable: 0x%x, Aux enable: 0x%x", 
                          eDisplayId, 
                          pRawData[0],
                          DPHOST_GETFLAG(pRawData[0], DP_GENERAL_CAP_TCON_BACKLIGHT_ADJUST), 
                          DPHOST_GETFLAG(pRawData[0], DP_GENERAL_CAP_BACKLIGHT_PIN_ENABLE), 
                          DPHOST_GETFLAG(pRawData[0], DP_GENERAL_CAP_BACKLIGHT_AUX_ENABLE));
    
    TraceInfo(QdiTraceDP, "DP%d: 702h (EDP Backlight Adjustment Cap) - Raw: 0x%x, \
                           Pin level set: 0x%x, Aux level set: 0x%x, Level bit depth: 0x%x", 
                          eDisplayId, 
                          pRawData[1],
                          DPHOST_GETFLAG(pRawData[1], DP_BACKLIGHT_CAP_BRIGHTNESS_PWM_PIN), 
                          DPHOST_GETFLAG(pRawData[1], DP_BACKLIGHT_CAP_BRIGHTNESS_AUX_SET), 
                          DPHOST_GETFLAG(pRawData[1], DP_BACKLIGHT_CAP_BRIGHTNESS_BYTE_COUNT));
    
    /* if sink supports brightness control save required caps */
    if (DPHOST_GETFLAG(pRawData[0], DP_GENERAL_CAP_TCON_BACKLIGHT_ADJUST))
    {
      /* set aux cap if both enable and level control are supported */
      pSinkBrightnessCap->bAuxControlCapable = (DPHOST_GETFLAG(pRawData[0], DP_GENERAL_CAP_BACKLIGHT_AUX_ENABLE)  &
                                                DPHOST_GETFLAG(pRawData[1], DP_BACKLIGHT_CAP_BRIGHTNESS_AUX_SET)) ?
                                               TRUE : FALSE;

      /* fetch the bit depth for brightness level */
      if (DPHOST_GETFLAG(pRawData[1], DP_BACKLIGHT_CAP_BRIGHTNESS_BYTE_COUNT))
      {
        pSinkBrightnessCap->eLevelBitDepth    = DPCD_BRIGHTNESS_CONTROL_16BIT;
      }
      else
      {
        pSinkBrightnessCap->eLevelBitDepth    = DPCD_BRIGHTNESS_CONTROL_8BIT;
      }
    }
  }
}

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkBrightnessEnable
//
//  @brief
//      Function to enable/disable brightness
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context
//      [IN] bEnable
//          TRUE to enable backlight
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteSinkBrightnessEnable(DP_DisplayCtxType *pDisplayCtx,
                                        bool32             bEnable)
{
  DP_Status                eStatus       = DP_STATUS_SUCCESS;  
  DP_DeviceCtxType        *pDeviceCtx;
  DP_StreamCtxType        *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_WriteSinkBacklightEnable: Unexpected null context.");  
  }
  else if ((0 == pStreamCtx->sBrightnessCaps.bAuxControlCapable) &&
           (MDP_PANEL_BACKLIGHTTYPE_AUX == pStreamCtx->eBrightnessType))
  {
    eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
    DP_LOG_MESSAGE_ERROR("DP_WriteSinkBrightnessEnable: Display %d - AUX control not suported!", pStreamCtx->eDisplayID);  
  }
  else
  {
    switch (pStreamCtx->eBrightnessType)
    {
        case MDP_PANEL_BACKLIGHTTYPE_AUX:
        {
          if (bEnable)
          {
              /* Set backlight mode first during enable */
              if (DP_STATUS_SUCCESS != DP_ModifySinkDPCDReg(pDisplayCtx,
                                                            DPCD_BACKLIGHT_MODE_START_ADDRESS,
                                                            DPCD_BACKLIGHT_BRIGHTNESS_CTRL_MODE_MASK,
                                                            DPCD_BACKLIGHT_BRIGHTNESS_CTRL_BY_REG))
              {
                  DP_LOG_MESSAGE_WARN("DP_WriteSinkBrightnessEnable: Display %d - Failed to set brightness mode!", pStreamCtx->eDisplayID);
              }
    
              /* Set duty cycle to 0 to prevent flash to random level when enabled */
              if (DP_STATUS_SUCCESS != DP_WriteSinkBrightnessLevel(pDisplayCtx, 0, 0))
              {
                  DP_LOG_MESSAGE_WARN("DP_WriteSinkBrightnessEnable: Display %d - Failed to clear brightness level!", pStreamCtx->eDisplayID);
              }
          }
    
          /* Set backlight state */
          if (DP_STATUS_SUCCESS != (eStatus = DP_ModifySinkDPCDReg(pDisplayCtx,
                                                                   DPCD_DISPLAY_CONTROL_START_ADDRESS,
                                                                   DPCD_BACKLIGHT_ENABLE_MASK,
                                                                   bEnable ? DPCD_BACKLIGHT_ENABLE_MASK : 0x0)))
          {
              DP_LOG_MESSAGE_ERROR("DP_WriteSinkBrightnessEnable: Display %d - Failed to enable brightness!", pStreamCtx->eDisplayID);
          }
        }
        break;
    
        case MDP_PANEL_BACKLIGHTTYPE_AUX_CUSTOM1:
        case MDP_PANEL_BACKLIGHTTYPE_AUX_CUSTOM2:
        {
          if (DP_STATUS_SUCCESS != DP_WriteSinkBrightnessLevel(pDisplayCtx, 0, 0))
          {
              DP_LOG_MESSAGE_WARN("DP_WriteSinkBrightnessEnable: Display %d - Failed to clear brightness level!", pStreamCtx->eDisplayID);
          }
        }
        break;
        
        default:
        {
            DP_LOG_MESSAGE_WARN("DP_WriteSinkBrightnessEnable: Display %d Aux Brightness Type %d Not Supported", pStreamCtx->eDisplayID, pStreamCtx->eBrightnessType);
            eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
        }
        break;
    }    

  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkBrightnessLevel
//
//  @brief
//      This function will write Sink Brightness level over AUX Channel
//      to only MSB (722h) or both MSB & LSB (722h&723h) based on caps
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context
//      [IN] fLevel
//          Backlight level to set in percentage
//      [IN] uMillinits
//          Backlight level to set in millinits 
// 
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteSinkBrightnessLevel(DP_DisplayCtxType *pDisplayCtx,
                                       float              fLevel,
                                       uint32             uMillinits)
{
  DP_Status                eStatus       = DP_STATUS_SUCCESS;  
  DP_DeviceCtxType        *pDeviceCtx;
  DP_StreamCtxType        *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_WriteSinkBrightnessLevel: Unexpected null context.");  
  }
  else if ((0 == pStreamCtx->sBrightnessCaps.bAuxControlCapable) &&
           (MDP_PANEL_BACKLIGHTTYPE_AUX == pStreamCtx->eBrightnessType))
  {
    eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
    DP_LOG_MESSAGE_ERROR("DP_WriteSinkBrightnessLevel: Display %d - AUX control is not suported!", pStreamCtx->eDisplayID); 
  }
  else
  {
    DP_WritePacketType    sWritePacket;
    uint8                 uData[4];
    uint32                uDataSize       = 0;
    uint32                uLevelConverted = 0;

    /* Write DPCD Data*/
    DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
    sWritePacket.eTransactionType   = DP_TRANSACTION_MODE_AUX;
    sWritePacket.uBytesWritten      = 0;
    sWritePacket.bQueueOnly         = FALSE;
    
    switch (pStreamCtx->eBrightnessType)
    {
        /* Default eDP Setting */
        case MDP_PANEL_BACKLIGHTTYPE_AUX:
        {
            if (DPCD_BRIGHTNESS_CONTROL_16BIT == pStreamCtx->sBrightnessCaps.eLevelBitDepth)
            {
                /* Sink is using both MSB (722h) and LSB (723h) */
                uDataSize       = 2;
                uLevelConverted = DPHOST_FLOAT_TO_INT(fLevel, DPCD_BACKLIGHT_BRIGHTNESS_16BIT_MAX);
                uData[1]        = (uint8)uLevelConverted;         // LSB
                uData[0]        = (uint8)(uLevelConverted >> 8);  // MSB
            }
            else if (DPCD_BRIGHTNESS_CONTROL_8BIT == pStreamCtx->sBrightnessCaps.eLevelBitDepth)
            {
                /* Sink is using only MSB (722h) */
                uDataSize       = 1;
                uLevelConverted = DPHOST_FLOAT_TO_INT(fLevel, DPCD_BACKLIGHT_BRIGHTNESS_8BIT_MAX);
                uData[0]        = (uint8)uLevelConverted;
            }
            else
            {
                DP_LOG_MESSAGE_WARN("DP_WriteSinkBrightnessLevel: Display %d Bit Depth %d Not Supported", pStreamCtx->eDisplayID, pStreamCtx->sBrightnessCaps.eLevelBitDepth);
                eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
            }

            sWritePacket.uAddress    = DPCD_BACKLIGHT_BRIGHTNESS_MSB_ADDRESS;
        }
        break;

        case MDP_PANEL_BACKLIGHTTYPE_AUX_CUSTOM1:
        {
            uData[0]         = (uint8)(uMillinits) & 0xFF;
            uData[1]         = (uint8)(uMillinits >> 8) & 0xFF;
            uData[2]         = (uint8)(uMillinits >> 16) & 0xFF;
            uData[3]         = 0;
            uDataSize        = DPCD_BACKLIGHT_BRIGHTNESS_CUSTOM1_SIZE;

            sWritePacket.uAddress = DPCD_BACKLIGHT_BRIGHTNESS_CUSTOM1_ADDRESS;
        }
        break;

        case MDP_PANEL_BACKLIGHTTYPE_AUX_CUSTOM2:
        {
            uLevelConverted = uMillinits / 1000;
            uData[0]        = (uint8)(uLevelConverted) & 0xFF;
            uData[1]        = (uint8)(uLevelConverted >> 8) & 0xFF;
            uData[2]        = 0;
            uData[3]        = 0;
            uDataSize       = DPCD_BACKLIGHT_BRIGHTNESS_CUSTOM2_SIZE;

            sWritePacket.uAddress = DPCD_BACKLIGHT_BRIGHTNESS_CUSTOM2_ADDRESS;
        }
        break;

        default:
        {
            DP_LOG_MESSAGE_WARN("DP_WriteSinkBrightnessLevel: Display %d Aux Brightness Type %d Not Supported", pStreamCtx->eDisplayID, pStreamCtx->eBrightnessType);
            eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
        }
        break;
    }

    sWritePacket.puWriteData    = uData;
    sWritePacket.uWriteDataSize = uDataSize;

    if (DP_STATUS_SUCCESS == eStatus)
    {
        if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket)))
        {
            DP_LOG_MESSAGE_ERROR("DP_WriteSinkBrightnessLevel: Display %d - Write Failed, eStatus=0x%x.",
                                  pStreamCtx->eDisplayID, eStatus);
        }
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_ModifySinkDPCDReg
//
//  @brief
//      Function to read and update selective bits within a register
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context
//      [IN] uRegAddress
//          Address of the DPCD register to modify
//      [IN] uBitMask
//          Mask for the specific bits in the register
//      [IN] uNewValue
//          Updated bit values in exact positions
//          Rest of the bits are DC (can be 0)
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
static DP_Status  DP_ModifySinkDPCDReg(DP_DisplayCtxType *pDisplayCtx,
                                       uint32             uRegAddress,
                                       uint8              uBitMask,
                                       uint8              uNewValue)
{
  DP_Status                eStatus       = DP_STATUS_SUCCESS;  
  DP_DeviceCtxType        *pDeviceCtx;
  DP_StreamCtxType        *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ModifySinkDPCDReg: Unexpected null context.");  
  }
  else
  {
    uint8                           uRawData;
    DP_ReadPacketType               sReadPacket;
    DP_WritePacketType              sWritePacket;

    /* Read DPCD Data */
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    DP_OSAL_MemSet(&uRawData,    0, sizeof(uRawData));

    sReadPacket.eTransactionType     = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer     = (uint8*)&uRawData;
    sReadPacket.uAddress             = uRegAddress;
    sReadPacket.uReadSize            = 1;
    sReadPacket.uBytesRead           = 0;
    sReadPacket.bQueueOnly           = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP_ModifySinkDPCDReg: Display %d - Read Failed at Address=0x%x, eStatus=0x%x.", 
                            pStreamCtx->eDisplayID,
                            uRegAddress,
                            eStatus);
    }
    else if (sReadPacket.uBytesRead != sReadPacket.uReadSize)
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DP_LOG_MESSAGE_ERROR("DP%d: DP_ModifySinkDPCDReg: Display %d - Bytes Read(0x%x) is not as expected(0x1)\n", 
                            pStreamCtx->eDisplayID,
                            pStreamCtx->eDisplayID,
                            sReadPacket.uBytesRead);
    }
    else
    {
      /* Get the current value */
      uint8 uCurrentValue = uRawData & uBitMask;
    
      /* Modify only the required bits */
      uint8 uNewData      = (uRawData & ~uBitMask) | uNewValue;

      /* Send new value only if it is different */
      if (uCurrentValue != uNewValue)
      {
        /* Write DPCD Data*/
        DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
        sWritePacket.eTransactionType    = DP_TRANSACTION_MODE_AUX;
        sWritePacket.puWriteData         = &uNewData;
        sWritePacket.uAddress            = uRegAddress;
        sWritePacket.uWriteDataSize      = 1;
        sWritePacket.uBytesWritten       = 0;
        sWritePacket.bQueueOnly          = FALSE;

        eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket);
        if (DP_STATUS_SUCCESS != eStatus)
        {
          DP_LOG_MESSAGE_ERROR("DP%d: DP_ModifySinkDPCDReg: Display %d - Write Failed at Address=0x%x, eStatus=0x%x.\n",
                               pStreamCtx->eDisplayID,
                               pStreamCtx->eDisplayID,
                               uRegAddress,
                               eStatus);
        }
      }
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_ParseSinkLTTPRCap
//
//  @brief
//      This function will parse the repater LTTPR caps if valid.
//
//  @params
//      [IN] pRawData
//          Pointer to raw DPCD data.
//      [IN] pLTTPRCap
//          Pointer to LTTPR caps.
//
//  @return
//      DP_Status
//-------------------------------------------------------------------------------------------------
//
static DP_Status  DP_ParseSinkLTTPRCap(uint8              *pRawData,
                                       DP_LTTPRCapType    *pLTTPRCap)
{
  DP_Status eStatus = DP_STATUS_SUCCESS;

  if (NULL == pRawData) 
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    pLTTPRCap->uMajor                      = (pRawData[0] >> 4) & 0xF;
    pLTTPRCap->uMinor                      = pRawData[0] & 0xF;

    if ((DPCD_LTTPR_MAJOR_VERSION_SUPPORT_MIN > pLTTPRCap->uMajor) ||
        (DPCD_LTTPR_MINOR_VERSION_SUPPORT_MIN > pLTTPRCap->uMinor))
    {
      eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    }
    else
    {
      pLTTPRCap->uMaxLinkRate                = (pRawData[1]) * (DPCD_HBR_LINK_RATE / 10); // Link rate in Khz
      pLTTPRCap->uRepeaterMode               = pRawData[3];
      pLTTPRCap->uMaxLaneCount               = pRawData[4];
      pLTTPRCap->uExtendedWakeTimeoutRequest = pRawData[5] & 0x7f;
      pLTTPRCap->uExtendedWakeTimeoutGrant   = (pRawData[5] >> 7) & 0x1;
      
      switch (pRawData[2])
      {
      case 0x80:
        pLTTPRCap->uRepeaterCount = 1;
        break;
      case 0x40:
        pLTTPRCap->uRepeaterCount = 2;
        break;
      case 0x20:
        pLTTPRCap->uRepeaterCount = 3;
        break;
      case 0x10:
        pLTTPRCap->uRepeaterCount = 4;
        break;
      case 0x08:
        pLTTPRCap->uRepeaterCount = 5;
        break;
      case 0x04:
        pLTTPRCap->uRepeaterCount = 6;
        break;
      case 0x02:
        pLTTPRCap->uRepeaterCount = 7;
        break;
      case 0x01:
        pLTTPRCap->uRepeaterCount = 8;
        break;
      default:
        pLTTPRCap->uRepeaterCount = 0;
        break;
      }
    }
  }

  return eStatus;
}


//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkLTTPRCap
//
//  @brief
//      This function will read the repater LTTPR caps if present.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadSinkLTTPRCap(DP_DisplayCtxType *pDisplayCtx)

{
  DP_Status                       eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType               *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkLTTPRCap: Unexpected null context.");
  }
  else
  {
    uint8                           uRawData[DPCD_LTTPR_CAPS_LEN];
    DP_ReadPacketType               sReadPacket;
    
    /* Read DPCD LTTPR Data */
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    sReadPacket.eTransactionType     = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer     = (uint8*)&uRawData;
    sReadPacket.uAddress             = DPCD_LTTPR_CAPS_START_ADDRESS;
    sReadPacket.uReadSize            = DPCD_LTTPR_CAPS_LEN;
    sReadPacket.uBytesRead           = 0;
    sReadPacket.bQueueOnly           = FALSE;
    
    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadSinkLTTPRCap: Read Failed, eStatus=0x%x.",
                           pDeviceCtx->eControllerID,
                           eStatus);
    }
    else if (sReadPacket.uBytesRead != sReadPacket.uReadSize)
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadSinkLTTPRCap: Bytes Read(0x%x) is not expected.",
                           pDeviceCtx->eControllerID,
                           sReadPacket.uBytesRead);
    }
    else
    {
      if (DP_STATUS_SUCCESS != DP_ParseSinkLTTPRCap(uRawData, &pDeviceCtx->sLTTPRCaps))
      {
        DP_LOG_MESSAGE_WARN("DP%d: DP_ReadSinkLTTPRCap: Invalid sink LTTPR caps.", pDeviceCtx->eControllerID);
      }
      else
      {
        TraceInfo(QdiTraceDP, "DP%i: LTTPR caps: version: %d.%d, count: %d, max rate: %d, max lanes: %d, repeater mdoe: 0x%x",
                  pDeviceCtx->eControllerID,
                  pDeviceCtx->sLTTPRCaps.uMajor,
                  pDeviceCtx->sLTTPRCaps.uMinor,                
                  pDeviceCtx->sLTTPRCaps.uRepeaterCount,
                  pDeviceCtx->sLTTPRCaps.uMaxLinkRate,
                  pDeviceCtx->sLTTPRCaps.uMaxLaneCount,
                  pDeviceCtx->sLTTPRCaps.uRepeaterMode);
      
      }
    }
  }
  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_ReadSinkLTTPRRepeaterOUI
//
//  @brief
//      Read and log LTTPR device-specific data of the repeater which consists of 
//      IEEE Organizational Unique ID (OUI) and Device Identification String
//
//
//  @params
//      [IN] pDisplayCtx
//          DP Context handle.
//      [IN] eRepeaterID
//          Index of the repeater
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_ReadSinkLTTPRRepeaterOUI(DP_DisplayCtxType       *pDisplayCtx,
                                      DP_LTTPR_RepeaterIDType  eRepeaterID)
{
  DP_Status                       eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType               *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkLTTPRRepeaterOUI: Unexpected null context.");
  }
  else if( (DP_LTTPR_REPEATER_MAX <= eRepeaterID) ||
           (DP_LTTPR_NO_REPEATER == eRepeaterID))
  {
    // Skip if repeater id is invalid
    eStatus = DP_STATUS_SUCCESS;
  }
  else
  {
    uint8                           uLTTPRDeviceData[DPCD_LTTPR_REPEATER1_DEVICE_ID_LEN];
    DP_ReadPacketType               sReadPacket;

    uint32                          uLTTPRDevieIDStartAddress = DPCD_LTTPR_REPEATER1_DEVICE_ID_START_ADDRESS +
                                                                (DPCD_LTTPR_REPEATER_CONFIG_OFFSET *
                                                                (eRepeaterID - DP_LTTPR_REPEATER1_ID));

    /* Read repeater device info */
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    sReadPacket.eTransactionType     = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer     = (uint8*)&uLTTPRDeviceData;
    sReadPacket.uAddress             = uLTTPRDevieIDStartAddress;
    sReadPacket.uReadSize            = DPCD_LTTPR_REPEATER1_DEVICE_ID_LEN;
    sReadPacket.uBytesRead           = 0;
    sReadPacket.bQueueOnly           = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadSinkLTTPRRepeaterOUI: Read Hardware Info Failed, eStatus=0x%x.",
                           pDeviceCtx->eControllerID,
                           eStatus);
    }
    else if (sReadPacket.uBytesRead != sReadPacket.uReadSize)
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadSinkLTTPRRepeaterOUI: Bytes Read(0x%x) is not expected.",
                           pDeviceCtx->eControllerID,
                           sReadPacket.uBytesRead);
    }
    else
    {
      pDeviceCtx->sLTTPRDeviceInfo.aIEEEOUI[0]      = uLTTPRDeviceData[0];
      pDeviceCtx->sLTTPRDeviceInfo.aIEEEOUI[1]      = uLTTPRDeviceData[1];
      pDeviceCtx->sLTTPRDeviceInfo.aIEEEOUI[2]      = uLTTPRDeviceData[2];
      pDeviceCtx->sLTTPRDeviceInfo.aDeviceString[0] = uLTTPRDeviceData[3];
      pDeviceCtx->sLTTPRDeviceInfo.aDeviceString[1] = uLTTPRDeviceData[4];
      pDeviceCtx->sLTTPRDeviceInfo.aDeviceString[2] = uLTTPRDeviceData[5];
      pDeviceCtx->sLTTPRDeviceInfo.aDeviceString[3] = uLTTPRDeviceData[6];
      pDeviceCtx->sLTTPRDeviceInfo.aDeviceString[4] = uLTTPRDeviceData[7];
      pDeviceCtx->sLTTPRDeviceInfo.aDeviceString[5] = uLTTPRDeviceData[8];
      pDeviceCtx->sLTTPRDeviceInfo.aDeviceString[6] = 0;

      TraceInfo(QdiTraceDP, "DP%d: LTTPR device identifier string: %s",
                             pDeviceCtx->eControllerID,
                             (char*)(pDeviceCtx->sLTTPRDeviceInfo.aDeviceString));
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_WriteSinkLTTPRRepeaterMode
//
//  @brief
//      This function will update the repater LTTPR mode if present.
//
//  @params
//      [IN] pDisplayCtx
//          Pointer to context
//      [IN] bTransparentMode
//          TRUE to enable transparent mode
//          FALSE to disable transparent mode
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteSinkLTTPRRepeaterMode(DP_DisplayCtxType *pDisplayCtx, bool32 bTransparentMode)

{
  DP_Status         eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    uint32              uData        = bTransparentMode ? DPCD_SPEC_LTTPR_TRANSPARENT_MODE : 
                                                          DPCD_SPEC_LTTPR_NON_TRANSPARENT_MODE;
    DP_WritePacketType  sWritePacket;
    
    /* write DPCD Data*/
    DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
    sWritePacket.eTransactionType    = DP_TRANSACTION_MODE_AUX;
    sWritePacket.puWriteData         = (uint8*) &uData;
    sWritePacket.uAddress            = DPCD_LTTPR_PHY_REPEATER_MODE_ADDRESS;
    sWritePacket.uWriteDataSize      = DPCD_LTTPR_PHY_REPEATER_MODE_LEN;
    sWritePacket.uBytesWritten       = 0;
    sWritePacket.bQueueOnly          = FALSE;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket)))
    {
      DP_LOG_MESSAGE_ERROR( "DP%d: DP_WriteSinkLTTPRRepeaterMode: Write Failed, eStatus=0x%x.", pDeviceCtx->eControllerID, eStatus);
    }

  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_ReadLTTPRCETrainingInterval
//
//  @brief
//      Read and log LTTPR device Chanel Equalization training interval data of the repeater
//
//  @params
//      [IN] pDisplayCtx
//          DP Context handle.
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_ReadLTTPRCETrainingInterval(DP_DisplayCtxType *pDisplayCtx)
{
  DP_Status             eStatus     = DP_STATUS_SUCCESS;
  DP_DeviceCtxType     *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_ReadLTTPRCETrainingInterval: Unexpected null context.");
  }
  else if (DPHOST_CHECK_IS_LTTPR_REPEATER(pDeviceCtx))
  {
    uint8              uRawData[DPCD_LTTPR_TRAINING_INTERVAL_LEN];
    DP_ReadPacketType  sReadPacket;
    uint32             uLTTPRCETrainingIntervalInUs  = DPCD_LTTPR_CE_TRAINING_INERVAL_MIN;

    uint32             uLTTPRTrainingIntervalAddress = DPCD_LTTPR_REPEATER1_CONFIG_ADDRESS +
                                                       DPCD_LTTPR_TRAINING_INTERVAL_OFFSET +
                                                       (DPCD_LTTPR_REPEATER_CONFIG_OFFSET *
                                                        (pDeviceCtx->eLTTPRRepeaterID - DP_LTTPR_REPEATER1_ID));
 
    /* Read repeater device info */
    DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
    sReadPacket.eTransactionType   = DP_TRANSACTION_MODE_AUX;
    sReadPacket.puReadDataBuffer   = (uint8*)&uRawData;
    sReadPacket.uAddress           = uLTTPRTrainingIntervalAddress;
    sReadPacket.uReadSize          = DPCD_LTTPR_TRAINING_INTERVAL_LEN;
    sReadPacket.uBytesRead         = 0;
    sReadPacket.bQueueOnly         = FALSE;
 
    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadLTTPRCETrainingInterval: Read Hardware Info Failed, eStatus=0x%x.",
                            pDeviceCtx->eControllerID,
                            eStatus);
    }
    else if (sReadPacket.uBytesRead != sReadPacket.uReadSize)
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DP_LOG_MESSAGE_ERROR("DP%d: DP_ReadLTTPRCETrainingInterval: Bytes Read(0x%x) is not expected.",
                            pDeviceCtx->eControllerID,
                            sReadPacket.uBytesRead);
    }
    else
    {
      uLTTPRCETrainingIntervalInUs = DPHOST_MAX(DPCD_LTTPR_CE_TRAINING_INERVAL_MIN, (uRawData[0] & 0x7F) * DPCD_LTTPR_CE_TRAINING_INERVAL_OFFSET);
    }

    pDeviceCtx->uLTTPRCETrainingIntervalInUs = uLTTPRCETrainingIntervalInUs;
  }
  else
  {
    pDeviceCtx->uLTTPRCETrainingIntervalInUs = DPCD_LTTPR_CE_TRAINING_INERVAL_MIN;
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_GetRepeaterDPCDOffset
//
//  @brief
//      This function will calculate the remapped DPCD address of the matching LTTPR repeater
//      DPCD address for a particular repeater ID.  Only addresses 102h - 106h are remapped DPCD registers.
//
//  @params
//      [IN] eRepeaterID
//          Repeater ID
//      [IN] uDPCDOffset
//          The base DPCD address to be written to
//
//  @return
//      The equivelent offset of the Phy repeater DPCD address for a particular repeater
//-------------------------------------------------------------------------------------------------
//
uint32  DP_GetRepeaterDPCDOffset(DP_LTTPR_RepeaterIDType eRepeaterID, uint32 uDPCDOffset)
{
    uint32 uRepeaterDPCDOffset = uDPCDOffset;
    
    const uint32 aRepeaterConfigDPCDOffset[DP_LTTPR_REPEATER_MAX] = 
    {
      0x00000,                              // DP_LTTPR_NO_REPEATER
      DPCD_LTTPR_REPEATER1_CONFIG_ADDRESS,  // DP_LTTPR_REPEATER1_ID
      DPCD_LTTPR_REPEATER2_CONFIG_ADDRESS,  // DP_LTTPR_REPEATER2_ID
      DPCD_LTTPR_REPEATER3_CONFIG_ADDRESS,  // DP_LTTPR_REPEATER3_ID
      DPCD_LTTPR_REPEATER4_CONFIG_ADDRESS,  // DP_LTTPR_REPEATER4_ID
      DPCD_LTTPR_REPEATER5_CONFIG_ADDRESS,  // DP_LTTPR_REPEATER5_ID
      DPCD_LTTPR_REPEATER6_CONFIG_ADDRESS,  // DP_LTTPR_REPEATER6_ID
      DPCD_LTTPR_REPEATER7_CONFIG_ADDRESS,  // DP_LTTPR_REPEATER7_ID
      DPCD_LTTPR_REPEATER8_CONFIG_ADDRESS,  // DP_LTTPR_REPEATER8_ID
    };

    if (DP_LTTPR_NO_REPEATER == eRepeaterID)
    {
      uRepeaterDPCDOffset = uDPCDOffset;
    }
    else if (DP_LTTPR_REPEATER_MAX > eRepeaterID)
    {
      uint32 uConfigOffset = aRepeaterConfigDPCDOffset[eRepeaterID];
      
      switch (uDPCDOffset)
      {
        case DPCD_TRAINING_PATTERN_SET_START_ADDRESS:  // 102h
        case DPCD_TRAINING_LANE_SET_START_ADDRESS:     // 103h
        case DPCD_TRAINING_LANE1_SET_START_ADDRESS:    // 104h
        case DPCD_TRAINING_LANE2_SET_START_ADDRESS:    // 105h 
        case DPCD_TRAINING_LANE3_SET_START_ADDRESS:    // 106h
        {
            // Calculate the corresponding repeater DPCD offset for matching config register
            uRepeaterDPCDOffset = uConfigOffset + (uDPCDOffset - DPCD_TRAINING_PATTERN_SET_START_ADDRESS);
        }
        break;
        case DPCD_LINK_STATUS_START_ADDRESS:           // 202h
        case DPCD_LINK_STATUS_LANE23_START_ADDRESS:    // 203h
        case DPCD_LINK_STATUS_LANEALIGN_START_ADDRESS: // 204h
        {
            // Calculate the corresponding repeater status offset for matching status register
            uRepeaterDPCDOffset = uConfigOffset + DPCD_LTTPR_REPEATER_STATUS_OFFSET + (uDPCDOffset - DPCD_LINK_STATUS_START_ADDRESS);
        }
        break;
        case DPCD_SINK_SYMBOL_STATUS_ADDRESS:          // 210h
        case DPCD_SINK_SYMBOL_STATUS2_ADDRESS:         // 211h
        {
            // Calculate the corresponding repeater DPCD offset for matching error count register
            uRepeaterDPCDOffset = uConfigOffset + DPCD_LTTPR_REPEATER_SYMBOL_ERRROR_OFFSET + (uDPCDOffset - DPCD_SINK_SYMBOL_STATUS_ADDRESS);
        }
        break;
        default:
        {
            DP_LOG_MESSAGE_ERROR("DP_LTTPR_RepeaterDPCDOffset: Invalid DPCD offset for repeaters.");
        }
        break;
      }
    }
    else
    {
      DP_LOG_MESSAGE_ERROR("DP_LTTPR_RepeaterDPCDOffset: Invalid Repeater ID.");
    }

    return uRepeaterDPCDOffset;
}

//-------------------------------------------------------------------------------------------------
// DP_WriteSinkMSTEnable
//
// @brief
//    Enable MST.
//
// @params
//    [IN] pDisplayCtx
//      DP Context handle.
//    [IN] bEnable
//      Enable/Disable MST.
//
// @return
//    DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_WriteSinkMSTEnable(DP_DisplayCtxType *pDisplayCtx, bool32 bEnable)
{
  DP_Status         eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_WriteSinkMSTEnable: Unexpected null context.");
  }
  else
  {
    uint8 uMSTModeCtrl = 0;

    if (TRUE == bEnable)
    {
      // Need to enable rp_req and upstream_src bits as well as per spec
      uMSTModeCtrl = DPCD_SPEC_MSTM_CTRL_MST_EN_BMSK|DP_MSTM_CTRL_UP_REQ_EN_MASK|
                     DP_MSTM_CTRL_UPSTREAM_SRC_MASK;
    }

    // Write MST control bits
    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWrite(pDisplayCtx, 
                                                         &uMSTModeCtrl, 
                                                         sizeof(uMSTModeCtrl), 
                                                         DP_MSTM_CTRL_ADDR)))
    {
      TraceInfo(QdiTraceDP, "DP%i: DP_WriteSinkMSTEnable() write failed for device=%d", pDeviceCtx->eDisplayID, pDeviceCtx->eDeviceID);
    }
  }

  return eStatus;
}

#ifdef __cplusplus
}
#endif

