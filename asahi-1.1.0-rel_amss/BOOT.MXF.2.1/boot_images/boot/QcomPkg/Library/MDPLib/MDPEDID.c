/*=============================================================================

  File: MDPEDID.c

  Source file for MDP panel detection and configuration


  Copyright (c) 2011-2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/
/*=========================================================================
      Include Files
==========================================================================*/

#include <Library/PcdLib.h>
#include <Library/QcomTargetLib.h>
#include <Library/BaseLib.h>
#include "MDPTypes.h"
#include "MDPLib_i.h"
#include "MDPPlatformLib.h"
#include "MDPSystem.h"
#include "xmlparser.h"
#include "xmltags.h"
#include "string.h"
#include "MDPLib.h"
#include "MDPEDID.h"
/*=========================================================================
      Local Defines
==========================================================================*/
// DP Override buffer sizes in bytes without padding
#define OEM_PANEL_DP_EDID_SIZE                                    (0x80 * 4) /* 4 blocks */
#define OEM_PANEL_DP_DPCD_CAPS_SIZE                               (0x100)    /* DPCD registers 0x00 - 0xff */
#define OEM_PANEL_DP_DPCD_STATUS_SIZE                             (0x100)    /* DPCD registers 0x200 - 0x2ff */

// Padded override buffer sizes to store length information from XML parser
#define OEM_PANEL_DP_EDID_SIZE_PAD                                (OEM_PANEL_DP_EDID_SIZE + OEM_PANEL_BIN_BUF_PAD)
#define OEM_PANEL_DP_DPCD_CAPS_SIZE_PAD                           (OEM_PANEL_DP_DPCD_CAPS_SIZE + OEM_PANEL_BIN_BUF_PAD)
#define OEM_PANEL_DP_DPCD_STATUS_SIZE_PAD                         (OEM_PANEL_DP_DPCD_STATUS_SIZE + OEM_PANEL_BIN_BUF_PAD)

// size of 2 ints for XML parser binary fields with a single packet (packet length + length of 0 termination)
#define OEM_PANEL_BIN_BUF_PAD                                     (2*sizeof(uint32))

/*=========================================================================
      Local Functions
==========================================================================*/
static MDP_Status MDPGetSprConfigInfo(MDP_Display_IDType eDisplayId, MDPPlatformParams *pPlatformParams);

/*=========================================================================
      Local Tables
==========================================================================*/

/* Panel configuration for each interface on the platform
 */
static MDP_Panel_AttrType gPanelConfig;
static uint8       gDSIContorllerMapping[16];
static uint32      gDemuraPanelID32[2];
static uint8       gDPDeviceIDMapping[16];
uint8              sDPEDIDBuffer[OEM_PANEL_DP_EDID_SIZE_PAD];                 /**< DP EDID override buffer */
uint8              sDPDPCDCapsBuffer[OEM_PANEL_DP_DPCD_CAPS_SIZE_PAD];        /**< DP DPCD caps override buffer */
uint8              sDPDPCDStatusBuffer[OEM_PANEL_DP_DPCD_STATUS_SIZE_PAD];    /**< DP DPCD status override buffer */
uint8              gDSIDemuraPanelIDReadCMD[MDP_DEMURA_PANEL_ID_READ_CMD_MAX_LENGTH];


/* XML Tag parser
 */
XML_TagDefType sXmlTagsList[] = {

    // Display Panel interface configuration
    XML_CREATE_TAG_ENTRY("InterfaceType", XML_TAG_DATATYPE_INTEGER, gPanelConfig.ePhysConnect),
    XML_CREATE_TAG_ENTRY("PanelOrientation", XML_TAG_DATATYPE_INTEGER, gPanelConfig.ePhysPanelOrientation),

    XML_CREATE_TAG_ENTRY("InterfaceColorFormat", XML_TAG_DATATYPE_INTEGER, gPanelConfig.eColorFormat),

    XML_CREATE_TAG_ENTRY("HorizontalFrontPorch", XML_TAG_DATATYPE_INTEGER, gPanelConfig.sActiveTiming.uHsyncFrontPorchDclk),
    XML_CREATE_TAG_ENTRY("HorizontalBackPorch", XML_TAG_DATATYPE_INTEGER, gPanelConfig.sActiveTiming.uHsyncBackPorchDclk),
    XML_CREATE_TAG_ENTRY("HorizontalSyncPulse", XML_TAG_DATATYPE_INTEGER, gPanelConfig.sActiveTiming.uHsyncPulseWidthDclk),
    XML_CREATE_TAG_ENTRY("HorizontalSyncSkew", XML_TAG_DATATYPE_INTEGER, gPanelConfig.sActiveTiming.uHsyncSkewDclk),


    XML_CREATE_TAG_ENTRY("HorizontalActive", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uDisplayWidth),
    XML_CREATE_TAG_ENTRY("VerticalActive", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uDisplayHeight),

    XML_CREATE_TAG_ENTRY("VerticalFrontPorch", XML_TAG_DATATYPE_INTEGER, gPanelConfig.sActiveTiming.uVsyncFrontPorchLines),
    XML_CREATE_TAG_ENTRY("VerticalBackPorch", XML_TAG_DATATYPE_INTEGER, gPanelConfig.sActiveTiming.uVsyncBackPorchLines),
    XML_CREATE_TAG_ENTRY("VerticalSyncPulse", XML_TAG_DATATYPE_INTEGER, gPanelConfig.sActiveTiming.uVsyncPulseWidthLines),

    XML_CREATE_TAG_ENTRY("HorizontalLeftBorder",  XML_TAG_DATATYPE_INTEGER, gPanelConfig.sActiveTiming.uHLeftBorderDClk),
    XML_CREATE_TAG_ENTRY("HorizontalRightBorder", XML_TAG_DATATYPE_INTEGER, gPanelConfig.sActiveTiming.uHRightBorderDClk),
    XML_CREATE_TAG_ENTRY("VerticalTopBorder",     XML_TAG_DATATYPE_INTEGER, gPanelConfig.sActiveTiming.uVTopBorderLines),
    XML_CREATE_TAG_ENTRY("VerticalBottomBorder",  XML_TAG_DATATYPE_INTEGER, gPanelConfig.sActiveTiming.uVBottomBorderLines),
    XML_CREATE_TAG_ENTRY("BorderColor",           XML_TAG_DATATYPE_INTEGER, gPanelConfig.sActiveTiming.uBorderColorRgb888),
    XML_CREATE_TAG_ENTRY("UnderflowColor",         XML_TAG_DATATYPE_INTEGER, gPanelConfig.uUnderflowColor),

    XML_CREATE_TAG_ENTRY("InvertDataPolarity",  XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.sActiveTiming.uDataEnInvertSignal),
    XML_CREATE_TAG_ENTRY("InvertVsyncPolarity", XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.sActiveTiming.uVsyncInvertSignal),  
    XML_CREATE_TAG_ENTRY("InvertVsyncPolairty", XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.sActiveTiming.uVsyncInvertSignal),
    XML_CREATE_TAG_ENTRY("InvertHsyncPolarity", XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.sActiveTiming.uHsyncInvertSignal),
    XML_CREATE_TAG_ENTRY("PanelId",             XML_TAG_DATATYPE_INTEGER, gPanelConfig.uPanelId),
    XML_CREATE_TAG_ENTRY("TextScaleFactor",     XML_TAG_DATATYPE_INTEGER, gPanelConfig.uTextScaleFactor),
    
    // DSI Common Parameters
    XML_CREATE_TAG_ENTRY("DSIRefreshRate", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uRefreshRate),
    XML_CREATE_TAG_ENTRY("DSIDynamicRefreshRates", XML_TAG_DATATYPE_HEX_LIST , gPanelConfig.uAttrs.sDsi.uDynamicRefreshRates),
    XML_CREATE_TAG_ENTRY("DSIBitClockFrequency", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uBitClockFrequency),
    XML_CREATE_TAG_ENTRY("DSILanes", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uDataLaneNum),
    XML_CREATE_TAG_ENTRY("DSICPhyMode", XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bCPhyMode),
    XML_CREATE_TAG_ENTRY("DSIChannelId", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.eChannelId),
    XML_CREATE_TAG_ENTRY("DSIVirtualId", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.eDisplayVC),
    XML_CREATE_TAG_ENTRY("DSIColorFormat", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.eColorFormat),
    XML_CREATE_TAG_ENTRY("DSIPacketTransferHS", XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bPacketTransferHS),
    XML_CREATE_TAG_ENTRY("DSIClockHSForceRequest", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uClockHSForceRequest),
    XML_CREATE_TAG_ENTRY("DSIHostLaneMapping", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uLaneRemap),
    XML_CREATE_TAG_ENTRY("DSILP11AtInit", XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bLP11AtInit),
    XML_CREATE_TAG_ENTRY("DSIPhyDCDCMode",        XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bPhyDCDCMode),
    XML_CREATE_TAG_ENTRY("DSIDisableEoTAfterHSXfer", XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bDisableEotpAfterHSXfer),
    XML_CREATE_TAG_ENTRY("DSIControllerMapping", XML_TAG_DATATYPE_BINARY, gDSIContorllerMapping),
    XML_CREATE_TAG_ENTRY("DSINullpacketInsertionBytes", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uNullPacketInsertionLength),
    XML_CREATE_TAG_ENTRY("DSIInterfaceMaster", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uDsiInterfaceMaster),
    XML_CREATE_TAG_ENTRY("DSIFlags", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uFlags),
    XML_CREATE_TAG_ENTRY("DSISSCConfig", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.eSSCConfig),
    XML_CREATE_TAG_ENTRY("DSIDMAScheduleLine", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uDmaScheduleLine),

    //DSC compression
    XML_CREATE_TAG_ENTRY("DSIDSCEnable",        XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.sDSCConfig.bDSCEnable),
    XML_CREATE_TAG_ENTRY("DSIDSCMajor",         XML_TAG_DATATYPE_INTEGER, gPanelConfig.sDSCConfig.uDSCMajor),
    XML_CREATE_TAG_ENTRY("DSIDSCMinor",         XML_TAG_DATATYPE_INTEGER, gPanelConfig.sDSCConfig.uDSCMinor),
    XML_CREATE_TAG_ENTRY("DSIDSCScr",           XML_TAG_DATATYPE_INTEGER, gPanelConfig.sDSCConfig.uDSCScr),
    XML_CREATE_TAG_ENTRY("DSIDSCProfileID",     XML_TAG_DATATYPE_INTEGER, gPanelConfig.sDSCConfig.uDSCProfileID),
    XML_CREATE_TAG_ENTRY("DSIDSCSliceHeight",   XML_TAG_DATATYPE_INTEGER, gPanelConfig.sDSCConfig.uDSCSliceHeight),
    XML_CREATE_TAG_ENTRY("DSIDSCSliceWidth",    XML_TAG_DATATYPE_INTEGER, gPanelConfig.sDSCConfig.uDSCSliceWidth),
    XML_CREATE_TAG_ENTRY("DSIDSCSlicePerPacket",XML_TAG_DATATYPE_INTEGER, gPanelConfig.sDSCConfig.uDSCSlicePerPacket),
    XML_CREATE_TAG_ENTRY("DSIDSCChromaFormat",  XML_TAG_DATATYPE_INTEGER, gPanelConfig.sDSCConfig.eDSCChromaFormat ),

    // DSI Timing parameters
    XML_CREATE_TAG_ENTRY("DSIAutoRefreshFrameNumDiv", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uAutoRefreshFrameNumDiv),
    XML_CREATE_TAG_ENTRY("DSIEnableAutoRefresh", XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bEnableAutoRefresh),
    XML_CREATE_TAG_ENTRY("DSIInitMasterTime", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uInitMasterTime),
    XML_CREATE_TAG_ENTRY("DisplayResetGpio", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uResetGpio),
    XML_CREATE_TAG_ENTRY("DisplayResetInfo", XML_TAG_DATATYPE_HEX_LIST, gPanelConfig.uAttrs.sDsi.aResetInfo),
    XML_CREATE_TAG_ENTRY("DSIEscapeClockDivisor", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uEscapeClockDivisor),
    XML_CREATE_TAG_ENTRY("DSIEscapeClockFrequency", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uEscapeClockFreq),

   // DSI PHY Timing parameters
    XML_CREATE_TAG_ENTRY("DSITimingHSZeroOverride",     XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bTimingHSZeroOverride),
    XML_CREATE_TAG_ENTRY("DSITimingHSZeroValue",        XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uTimingHSZeroValue),
    XML_CREATE_TAG_ENTRY("DSITimingHSExitOverride",     XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bTimingHSExitOverride),
    XML_CREATE_TAG_ENTRY("DSITimingHSExitValue",        XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uTimingHSExitValue),
    XML_CREATE_TAG_ENTRY("DSITimingHSPrepareOverride",  XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bTimingHSPrepareOverride),
    XML_CREATE_TAG_ENTRY("DSITimingHSPrepareValue",     XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uTimingHSPrepareValue),
    XML_CREATE_TAG_ENTRY("DSITimingHSTrailOverride",    XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bTimingHSTrailOverride),
    XML_CREATE_TAG_ENTRY("DSITimingHSTrailValue",       XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uTimingHSTrailValue),
    XML_CREATE_TAG_ENTRY("DSITimingHSRequestOverride",  XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bTimingHSRequestOverride),
    XML_CREATE_TAG_ENTRY("DSITimingHSRequestValue",     XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uTimingHSRequestValue),
    XML_CREATE_TAG_ENTRY("DSITimingCLKZeroOverride",    XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bTimingCLKZeroOverride),
    XML_CREATE_TAG_ENTRY("DSITimingCLKZeroValue",       XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uTimingCLKZeroValue),
    XML_CREATE_TAG_ENTRY("DSITimingCLKTrailOverride",   XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bTimingCLKTrailOverride),
    XML_CREATE_TAG_ENTRY("DSITimingCLKTrailValue",      XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uTimingCLKTrailValue),
    XML_CREATE_TAG_ENTRY("DSITimingCLKPrepareOverride", XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bTimingCLKPrepareOverride),
    XML_CREATE_TAG_ENTRY("DSITimingCLKPrepareValue",    XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uTimingCLKPrepareValue),
    XML_CREATE_TAG_ENTRY("DSITimingCLKPreOverride",     XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bTimingCLKPreOverride),
    XML_CREATE_TAG_ENTRY("DSITimingCLKPreValue",        XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uTimingCLKPreValue),
    XML_CREATE_TAG_ENTRY("DSITimingCLKPostOverride",    XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bTimingCLKPostOverride),
    XML_CREATE_TAG_ENTRY("DSITimingCLKPostValue",       XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uTimingCLKPostValue),
    XML_CREATE_TAG_ENTRY("DSITimingTASureOverride",     XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bTimingTASureOverride),
    XML_CREATE_TAG_ENTRY("DSITimingTASureValue",        XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uTimingTASureValue),
    XML_CREATE_TAG_ENTRY("DSITimingTAGoOverride",       XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bTimingTAGoOverride),
    XML_CREATE_TAG_ENTRY("DSITimingTAGoValue",          XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uTimingTAGoValue),
    XML_CREATE_TAG_ENTRY("DSITimingTAGetOverride",      XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bTimingTAGetOverride),
    XML_CREATE_TAG_ENTRY("DSITimingTAGetValue",         XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uTimingTAGetValue),
    XML_CREATE_TAG_ENTRY("DSITimingMargin",             XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uPHYTimingMargin),

    // DSI Video Mode Configuration
    XML_CREATE_TAG_ENTRY("DSITrafficMode",          XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.eTrafficMode),
    XML_CREATE_TAG_ENTRY("DSIHsaHseAfterVsVe",      XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bSendHsaHseAfterVsVe),
    XML_CREATE_TAG_ENTRY("DSILowPowerModeInHFP",    XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bLowPowerModeInHFP),
    XML_CREATE_TAG_ENTRY("DSILowPowerModeInHBP",    XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bLowPowerModeInHBP),
    XML_CREATE_TAG_ENTRY("DSILowPowerModeInHSA",    XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bLowPowerModeInHSA),
    XML_CREATE_TAG_ENTRY("DSILowPowerModeInBLLPEOF",XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bLowPowerModeInBLLPEOF),
    XML_CREATE_TAG_ENTRY("DSILowPowerModeInBLLP",   XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bLowPowerModeInBLLP),
    XML_CREATE_TAG_ENTRY("DSIForceCmdInVideoHS",    XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bForceCmdInVideoHS),

    // DSI Command Mode Configurations
    XML_CREATE_TAG_ENTRY("DSICmdModeIdleTime",          XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uCommandModeIdleTime),
    XML_CREATE_TAG_ENTRY("DSICMDSwapInterface",         XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bSwapInterface),
    XML_CREATE_TAG_ENTRY("DSICMDUsingTrigger",          XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.bUsingTrigger),
    XML_CREATE_TAG_ENTRY("DSISlaveControllerSkewLines", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.iSlaveControllerSkewLines),
    XML_CREATE_TAG_ENTRY("DSICmdModePixelAlignment",    XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uCmdModePixelAlignment),

    // DSI TE Configuration (Command mode only)
    XML_CREATE_TAG_ENTRY("DSITECheckEnable",           XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.sTE.bTECheckEnable),
    XML_CREATE_TAG_ENTRY("DSITECheckSetDisable",       XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.sTE.bTECheckSetDisable),
    XML_CREATE_TAG_ENTRY("DSITEUsingDedicatedTEPin",   XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.uAttrs.sDsi.sTE.bDedicatedTEPin),
    XML_CREATE_TAG_ENTRY("DSITEvSyncStartPos",         XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.sTE.vSyncStartPos),
    XML_CREATE_TAG_ENTRY("DSITEvSyncContinueLines",    XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.sTE.vSyncContinueLines),
    XML_CREATE_TAG_ENTRY("DSITEvSyncStartLineDivisor", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.sTE.vSyncStartLineDivisor),
    XML_CREATE_TAG_ENTRY("DSITEvSyncPosSafetyMargin",  XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.sTE.vSyncPosSafetyMargin),
    XML_CREATE_TAG_ENTRY("DSITEvSyncBelowSafetyMargin",XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.sTE.vSyncBelowSafetyMargin),
    XML_CREATE_TAG_ENTRY("DSITEPercentVariance",       XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.sTE.vSyncPercentVariance),
    XML_CREATE_TAG_ENTRY("DSITEvSyncRdPtrIrqLine",     XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.sTE.vSyncRdPtrIrqLine),
    XML_CREATE_TAG_ENTRY("DSITEvSyncSelect",           XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.sTE.vSyncSelect),
    XML_CREATE_TAG_ENTRY("DSITEvSyncInitVal",          XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.sTE.uVsyncInitValue),

    // DSI Strength configuration
    XML_CREATE_TAG_ENTRY("DSIDataStrengthLP", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uDataStrengthLP),
    XML_CREATE_TAG_ENTRY("DSIDataStrengthHS", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uDataStrengthHS),
    XML_CREATE_TAG_ENTRY("DSIClockStrengthHS", XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.uClockStrengthHS),

    // SPR panel configuration
    XML_CREATE_TAG_ENTRY("DSISprPackType",  XML_TAG_DATATYPE_INTEGER, gPanelConfig.uAttrs.sDsi.sDemuraConfig.eSprPackType),

    // DSI Panel init sequence
    XML_CREATE_TAG_ENTRY("DSIInitSequence", XML_TAG_DATATYPE_BINARY, gPanelConfig.uAttrs.sDsi.sInitBuffer.pBuffer),
    XML_CREATE_TAG_ENTRY("DSITermSequence", XML_TAG_DATATYPE_BINARY, gPanelConfig.uAttrs.sDsi.sTermBuffer.pBuffer),

    // Demura Panel ID read command
    XML_CREATE_TAG_ENTRY("DSIDemuraPanelIDReadCMD",   XML_TAG_DATATYPE_BINARY,   gDSIDemuraPanelIDReadCMD),
    XML_CREATE_TAG_ENTRY("DSIDemuraPanelID",          XML_TAG_DATATYPE_HEX_LIST, gDemuraPanelID32),
    
    // DSI split link configuration 
    XML_CREATE_TAG_ENTRY("DSISplitLinkConfig",        XML_TAG_DATATYPE_INTEGER,  gPanelConfig.uAttrs.sDsi.eSplitLinkConfig),

    // I2C configuration  
    XML_CREATE_TAG_ENTRY("DSII2CSlaveAddressList", XML_TAG_DATATYPE_INTEGER_LIST, gPanelConfig.uAttrs.sDsi.sI2CConfig.aI2CSlaveAddressList),
    XML_CREATE_TAG_ENTRY("DSII2CI2CNumOfSlaves",   XML_TAG_DATATYPE_INTEGER,      gPanelConfig.uAttrs.sDsi.sI2CConfig.uI2CNumOfSlaves),
    XML_CREATE_TAG_ENTRY("DSII2CFrequency",        XML_TAG_DATATYPE_INTEGER,      gPanelConfig.uAttrs.sDsi.sI2CConfig.uI2CBusFrequency),
    XML_CREATE_TAG_ENTRY("DSII2CGSBIPort",         XML_TAG_DATATYPE_INTEGER,      gPanelConfig.uAttrs.sDsi.sI2CConfig.uI2CGSBICore),
    XML_CREATE_TAG_ENTRY("DSII2COffsetLength",     XML_TAG_DATATYPE_INTEGER,      gPanelConfig.uAttrs.sDsi.sI2CConfig.uI2COffsetLengthInByte),

    // I2C init/term sequence
    XML_CREATE_TAG_ENTRY("I2CInitSequence", XML_TAG_DATATYPE_BINARY, gPanelConfig.uAttrs.sDsi.sI2CConfig.sI2CInitSequence.pBuffer),
    XML_CREATE_TAG_ENTRY("I2CTermSequence", XML_TAG_DATATYPE_BINARY, gPanelConfig.uAttrs.sDsi.sI2CConfig.sI2CTermSequence.pBuffer),

    // I2C and EDID configuration
    XML_CREATE_TAG_ENTRY("DynamicEDIDEnabled",         XML_TAG_DATATYPE_BOOLEAN, gPanelConfig.sDynamicEDIDConfig.bDynamicEDIDEnabled),
    XML_CREATE_TAG_ENTRY("DynamicEDIDI2CSlaveAddress", XML_TAG_DATATYPE_INTEGER, gPanelConfig.sDynamicEDIDConfig.uI2CAddress),
    XML_CREATE_TAG_ENTRY("DynamicEDIDI2CFrequency",    XML_TAG_DATATYPE_INTEGER, gPanelConfig.sDynamicEDIDConfig.uI2CFrequency),
    XML_CREATE_TAG_ENTRY("DynamicEDIDI2CGSBIPort",     XML_TAG_DATATYPE_INTEGER, gPanelConfig.sDynamicEDIDConfig.uI2CGSBIPort),
    XML_CREATE_TAG_ENTRY("DynamicEDIDPTM",             XML_TAG_DATATYPE_INTEGER, gPanelConfig.sDynamicEDIDConfig.uPreferredTimingMode),
    XML_CREATE_TAG_ENTRY("DynamicEDIDStartAddress",    XML_TAG_DATATYPE_INTEGER, gPanelConfig.sDynamicEDIDConfig.uStartAddress),

    // Backlight configuration
    XML_CREATE_TAG_ENTRY("BacklightType",              XML_TAG_DATATYPE_INTEGER, gPanelConfig.sBacklightConfig.eBacklightType),
    XML_CREATE_TAG_ENTRY("BacklightPmicControlType",   XML_TAG_DATATYPE_INTEGER, gPanelConfig.sBacklightConfig.uBacklightCntrl.eBacklightCtrl),
    XML_CREATE_TAG_ENTRY("BacklightPmicPWMFrequency",  XML_TAG_DATATYPE_INTEGER, gPanelConfig.sBacklightConfig.uPwmDesiredFreqHz),
    XML_CREATE_TAG_ENTRY("BacklightPmicId",            XML_TAG_DATATYPE_INTEGER, gPanelConfig.sBacklightConfig.uPMICId),
    XML_CREATE_TAG_ENTRY("BacklightDefault",           XML_TAG_DATATYPE_INTEGER, gPanelConfig.sBacklightConfig.uLevel),
    XML_CREATE_TAG_ENTRY("BacklightBitWidth",          XML_TAG_DATATYPE_INTEGER, gPanelConfig.sBacklightConfig.uNumBits),
    XML_CREATE_TAG_ENTRY("BrightnessMax",              XML_TAG_DATATYPE_INTEGER, gPanelConfig.sBacklightConfig.uBrightnessMax),
    XML_CREATE_TAG_ENTRY("BrightnessMin",              XML_TAG_DATATYPE_INTEGER, gPanelConfig.sBacklightConfig.uBrightnessMin),

    // MDP_DISPLAY_PRIMARY configuration flags
    XML_CREATE_TAG_ENTRY("DisplayPrimaryFlags",        XML_TAG_DATATYPE_INTEGER, gPanelConfig.eDisplayFlags),

    // Default GPIO state
    XML_CREATE_TAG_ENTRY_EX("TLMMGPIODefaultLow",      XML_TAG_DATATYPE_HEX_LIST, gPanelConfig.uDefaultGPIOState[0], 0xFF),
    XML_CREATE_TAG_ENTRY_EX("TLMMGPIODefaultHigh",     XML_TAG_DATATYPE_HEX_LIST, gPanelConfig.uDefaultGPIOState[1], 0xFF),

    // EDP Parameters
    XML_CREATE_TAG_ENTRY   ("EDPRefreshRate",          XML_TAG_DATATYPE_INTEGER,  gPanelConfig.uAttrs.sDp.uRefreshRate),
    XML_CREATE_TAG_ENTRY   ("EDPVoltageSwingLevel",    XML_TAG_DATATYPE_INTEGER,  gPanelConfig.uAttrs.sDp.uLaneSwingLevel),
    XML_CREATE_TAG_ENTRY   ("EDPPreemphasisLevel",     XML_TAG_DATATYPE_INTEGER,  gPanelConfig.uAttrs.sDp.uPreemphasisLevel),
    XML_CREATE_TAG_ENTRY   ("EDPNumberOfLanes",        XML_TAG_DATATYPE_INTEGER,  gPanelConfig.uAttrs.sDp.uNumberOfLanes),
    XML_CREATE_TAG_ENTRY   ("EDPLinkRate",             XML_TAG_DATATYPE_INTEGER,  gPanelConfig.uAttrs.sDp.uLinkRateInKhz),
    XML_CREATE_TAG_ENTRY   ("EDPMaxLinkRate",          XML_TAG_DATATYPE_INTEGER,  gPanelConfig.uAttrs.sDp.uMaxLinkRate),

    XML_CREATE_TAG_ENTRY   ("EDPTraining",             XML_TAG_DATATYPE_INTEGER,  gPanelConfig.uAttrs.sDp.eLinkTraining),
    XML_CREATE_TAG_ENTRY   ("EDPDPCDRead",             XML_TAG_DATATYPE_BOOLEAN,  gPanelConfig.uAttrs.sDp.bReadDPCD),
    XML_CREATE_TAG_ENTRY   ("EDPEDIDRead",             XML_TAG_DATATYPE_BOOLEAN,  gPanelConfig.uAttrs.sDp.bReadEDID),
    XML_CREATE_TAG_ENTRY   ("EDPHPDActiveLow",         XML_TAG_DATATYPE_BOOLEAN,  gPanelConfig.uAttrs.sDp.bHPDActiveLow),
    XML_CREATE_TAG_ENTRY   ("EDPPowerUpWaitInMs",      XML_TAG_DATATYPE_INTEGER,  gPanelConfig.uAttrs.sDp.uPowerupWaitinMs),
    XML_CREATE_TAG_ENTRY   ("EDPMaxAuxRetry ",         XML_TAG_DATATYPE_INTEGER,  gPanelConfig.uAttrs.sDp.uMaxAuxRetry),
    XML_CREATE_TAG_ENTRY   ("EDPDeviceIDMapping",      XML_TAG_DATATYPE_BINARY,   gDPDeviceIDMapping),

    // eDP EDID and DPCD overrides / fallbacks
    XML_CREATE_TAG_ENTRY   ("EDPOverrideEDID",         XML_TAG_DATATYPE_BINARY,   sDPEDIDBuffer),
    XML_CREATE_TAG_ENTRY   ("EDPOverrideDPCDCaps",     XML_TAG_DATATYPE_BINARY,   sDPDPCDCapsBuffer),
    XML_CREATE_TAG_ENTRY   ("EDPOverrideDPCDStatus",   XML_TAG_DATATYPE_BINARY,   sDPDPCDStatusBuffer),
    XML_CREATE_TAG_ENTRY   ("EDPOverrideMode",         XML_TAG_DATATYPE_INTEGER,  gPanelConfig.uAttrs.sDp.eOverrideMode)
};

/* Display SPR XML Tag Parser
 */
XML_TagDefType sSprXmlTagsList[] = {
    XML_CREATE_TAG_ENTRY("AdaptiveMode",               XML_TAG_DATATYPE_STRING,   gPanelConfig.uAttrs.sDsi.sDemuraConfig.sDisplaySprDataConfig.aAdaptiveMode),
    XML_CREATE_TAG_ENTRY("FilterType",                 XML_TAG_DATATYPE_STRING,   gPanelConfig.uAttrs.sDsi.sDemuraConfig.sDisplaySprDataConfig.aFilterType),
    XML_CREATE_TAG_ENTRY("AdaptiveFilterCoeffs",       XML_TAG_DATATYPE_HEX_LIST, gPanelConfig.uAttrs.sDsi.sDemuraConfig.sDisplaySprDataConfig.aAdaptiveStrengths),
    XML_CREATE_TAG_ENTRY("FilterCoeffs",               XML_TAG_DATATYPE_HEX_LIST, gPanelConfig.uAttrs.sDsi.sDemuraConfig.sDisplaySprDataConfig.aFilterCoeffs),
    XML_CREATE_TAG_ENTRY("PhaseInc",                   XML_TAG_DATATYPE_INTEGER,  gPanelConfig.uAttrs.sDsi.sDemuraConfig.sDisplaySprDataConfig.uPhaseInc),
    XML_CREATE_TAG_ENTRY("PhaseRepeat",                XML_TAG_DATATYPE_INTEGER,  gPanelConfig.uAttrs.sDsi.sDemuraConfig.sDisplaySprDataConfig.uPhaseRepeat),
    XML_CREATE_TAG_ENTRY("ColorPhaseOffsetsRed",       XML_TAG_DATATYPE_HEX_LIST, gPanelConfig.uAttrs.sDsi.sDemuraConfig.sDisplaySprDataConfig.aColorPhaseOffsetsRed),
    XML_CREATE_TAG_ENTRY("ColorPhaseOffsetsGreen",     XML_TAG_DATATYPE_HEX_LIST, gPanelConfig.uAttrs.sDsi.sDemuraConfig.sDisplaySprDataConfig.aColorPhaseOffsetsGreen),
    XML_CREATE_TAG_ENTRY("ColorPhaseOffsetsBlue",      XML_TAG_DATATYPE_HEX_LIST, gPanelConfig.uAttrs.sDsi.sDemuraConfig.sDisplaySprDataConfig.aColorPhaseOffsetsBlue),
    XML_CREATE_TAG_ENTRY("ColorPhaseOffsetsWhite",     XML_TAG_DATATYPE_HEX_LIST, gPanelConfig.uAttrs.sDsi.sDemuraConfig.sDisplaySprDataConfig.aColorPhaseOffsetsWhite),
};

/* External dispaly XML Tag parser
 */
XML_TagDefType sExtDPXmlTagsList[] = {
    // DP EDID and DPCD overrides / fallbacks
    XML_CREATE_TAG_ENTRY("DPOverrideEDID",             XML_TAG_DATATYPE_BINARY,   sDPEDIDBuffer),
    XML_CREATE_TAG_ENTRY("DPOverrideDPCDCaps",         XML_TAG_DATATYPE_BINARY,   sDPDPCDCapsBuffer),
    XML_CREATE_TAG_ENTRY("DPOverrideDPCDStatus",       XML_TAG_DATATYPE_BINARY,   sDPDPCDStatusBuffer),
    XML_CREATE_TAG_ENTRY("DPOverrideMode",             XML_TAG_DATATYPE_INTEGER,  gPanelConfig.uAttrs.sDp.eOverrideMode)
};

#define XML_EXTDPTAGSLIST_LENGTH  (sizeof(sExtDPXmlTagsList)/sizeof(XML_TagDefType))
/*=========================================================================
      Public Functions
==========================================================================*/

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: AllocateDynamicBuffer()
**
** DESCRIPTION:
**   Dynamic Allocate Buffer And Update XML Tags.
**
** --------------------------------------------------------------------- */
MDP_Status AllocateDynamicBuffer(uint8 *pTagName, uint32 uTagLength, MDP_BufferType *pBuffer, uint16 uBufferSize)
{
  MDP_Status eStatus             = MDP_STATUS_OK;

  if (NULL == pBuffer)
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "AllocateDynamicBuffer: Invalid parameter\n");
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else if (NULL != pBuffer->pBuffer)
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "AllocateDynamicBuffer: Already allocated\n");
  }
  else if (NULL == (pBuffer->pBuffer = (uint8 *)MDP_OSAL_CALLOC(uBufferSize)))
  {
    XML_UpdateTag(sXmlTagsList, MDP_ARRAY_LENGTH(sXmlTagsList), (uint8 *)pTagName, uTagLength, NULL, 0);
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else if (NULL == pTagName)
  {
    //Some buffer do not have TagName, such as DSC PPS.
  }
  else if (XML_PARSER_STATUS_BADPARAM == XML_UpdateTag(sXmlTagsList, MDP_ARRAY_LENGTH(sXmlTagsList), (uint8 *)pTagName, uTagLength, pBuffer->pBuffer, uBufferSize))
  {
    MDP_OSAL_FREE(pBuffer->pBuffer);
    pBuffer->pBuffer = NULL;
    eStatus = MDP_STATUS_BAD_PARAM;
  }

  return eStatus;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: EDIDInitialize()
**
** DESCRIPTION:
**   Initialize EDID structure with default values.
**
** --------------------------------------------------------------------- */
void EDIDInitialize(MDP_Panel_EDID_Config *pEDID)
{
  if (NULL == pEDID)
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: Input parameter is NULL\n");
  }
  else
  {
    // Populate header (bytes 2-7)
    MDP_OSAL_MEMSET(&pEDID->Header[1],0xFF, 6);
    // Standard Timings (fill with 01)
    MDP_OSAL_MEMSET(&pEDID->StandardTiming, 0x1, sizeof(pEDID->StandardTiming));
    // Indicate the 3 detailed descriptors are dummy fields (0x10-dummy descriptor)
    pEDID->EDID_DetailedInfo.DisplayDescriptors[0].TagId = EDID_DISPLAY_DESC_DUMMY_TAG;
    pEDID->EDID_DetailedInfo.DisplayDescriptors[1].TagId = EDID_DISPLAY_DESC_DUMMY_TAG;
    pEDID->EDID_DetailedInfo.DisplayDescriptors[2].TagId = EDID_DISPLAY_DESC_DUMMY_TAG;
  }
}

/** --------------------------------------------------------------------- */
/**
** FUNCTION: EDIDGenerateDetailedTiming()
**
** DESCRIPTION:
**   Generate EDID Detailed Timings.
**
** @params
**   [OUT] pEDID
**      Edid config.
**   [IN] pPanelAttr
**      Panel attributes.
**  @return
**    void.
**
** --------------------------------------------------------------------- */
void EDIDGenerateDetailedTiming(MDP_Panel_EDID_Config *pEDID, MDP_Panel_AttrType *pPanelAttr)
{
  uint16 uBlanking                = 0;
  uint32 uPixelRate               = 0;
  uint32 uDstWidthActive          = 0;
  uint32 uDstHeightActive         = 0;
  uint32 uDstWidthTotal           = 0;
  uint32 uDstHeightTotal          = 0;
  uint32 uRefreshRate             = 0;

  if ((NULL == pEDID) ||
      (NULL == pPanelAttr))
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: Input parameter are NULL\n");
  }
  else
  {
    uDstWidthActive          = pPanelAttr->uDisplayWidth;
    uDstHeightActive         = pPanelAttr->uDisplayHeight;
    uDstWidthTotal           = uDstWidthActive +
                                    pPanelAttr->sActiveTiming.uHsyncFrontPorchDclk +
                                    pPanelAttr->sActiveTiming.uHsyncBackPorchDclk +
                                    pPanelAttr->sActiveTiming.uHsyncPulseWidthDclk;
    uDstHeightTotal          = uDstHeightActive +
                                    pPanelAttr->sActiveTiming.uVTopBorderLines +
                                    pPanelAttr->sActiveTiming.uVBottomBorderLines +
                                    pPanelAttr->sActiveTiming.uVsyncPulseWidthLines +
                                    pPanelAttr->sActiveTiming.uVsyncBackPorchLines +
                                    pPanelAttr->sActiveTiming.uVsyncFrontPorchLines;
    uRefreshRate             = pPanelAttr->uAttrs.sDsi.uRefreshRate;
    uPixelRate               = uDstWidthTotal * uDstHeightTotal * uRefreshRate;

    // Pixel clock (divided by 10000)
    pEDID->DetailedTiming.PixelClock = (uint16)(uPixelRate/10000);
    // Active Horiziontal (Split in to two fields)
    pEDID->DetailedTiming.HPixels = (pPanelAttr->uDisplayWidth & 0xFF);
    pEDID->DetailedTiming.HPixels_Blanking |= (pPanelAttr->uDisplayWidth & 0xF00)>>4;

    // Blanking (Split in to two fields), blanking is Front Porch + Sync Width + Back Porch
    uBlanking = (uint16)(pPanelAttr->sActiveTiming.uHsyncBackPorchDclk +
                pPanelAttr->sActiveTiming.uHsyncPulseWidthDclk +
                pPanelAttr->sActiveTiming.uHsyncFrontPorchDclk);
    pEDID->DetailedTiming.HBlanking = (uBlanking & 0xFF);
    pEDID->DetailedTiming.HPixels_Blanking |= (uBlanking & 0xF00)>>12;

    // Active Vertical (Split in to two fields)
    pEDID->DetailedTiming.VPixels = (pPanelAttr->uDisplayHeight & 0xFF);
    pEDID->DetailedTiming.VPixels_Blanking |= (pPanelAttr->uDisplayHeight & 0xF00)>>4;

    // Blanking (Split in to two fields), blanking is Front Porch + Sync Width + Back Porch
    uBlanking = (uint16)(pPanelAttr->sActiveTiming.uVsyncBackPorchLines +
                pPanelAttr->sActiveTiming.uVsyncPulseWidthLines +
                pPanelAttr->sActiveTiming.uVsyncFrontPorchLines);
    pEDID->DetailedTiming.VBlanking = (uBlanking & 0xFF);
    pEDID->DetailedTiming.VPixels_Blanking |= (uBlanking & 0xF00)>>12;

    // Horizontal Front Porch & Synch Width (Split between two fields)
    pEDID->DetailedTiming.HFrontPorch = (pPanelAttr->sActiveTiming.uHsyncFrontPorchDclk & 0xFF);
    pEDID->DetailedTiming.HVPorchSyncWidths |= (pPanelAttr->sActiveTiming.uHsyncFrontPorchDclk & 0x300) >> 2;
    pEDID->DetailedTiming.HSyncWidth = (pPanelAttr->sActiveTiming.uHsyncPulseWidthDclk & 0xFF);
    pEDID->DetailedTiming.HVPorchSyncWidths |= (pPanelAttr->sActiveTiming.uHsyncPulseWidthDclk & 0x300) >> 4;

    // Vertical Front Porch & Synch Width (Split betwen two fields)
    pEDID->DetailedTiming.VFrontPorch_SyncWidth |= (pPanelAttr->sActiveTiming.uVsyncFrontPorchLines & 0xF) << 4;
    pEDID->DetailedTiming.HVPorchSyncWidths |= (pPanelAttr->sActiveTiming.uVsyncFrontPorchLines & 0x30) >> 2;
    pEDID->DetailedTiming.VFrontPorch_SyncWidth |= (pPanelAttr->sActiveTiming.uVsyncPulseWidthLines & 0xF);
    pEDID->DetailedTiming.HVPorchSyncWidths |= (pPanelAttr->sActiveTiming.uVsyncPulseWidthLines & 0x30) >> 4;

    // Signal timing
    pEDID->DetailedTiming.SignalTimingInterface |= 0x10; // Digital timing
    if (pPanelAttr->sActiveTiming.uHsyncInvertSignal)
    {
      pEDID->DetailedTiming.SignalTimingInterface |= 0x8;
    }
    else
    {
      pEDID->DetailedTiming.SignalTimingInterface |= 0xC;
    }

    if (!pPanelAttr->sActiveTiming.uVsyncInvertSignal)
    {
      pEDID->DetailedTiming.SignalTimingInterface |= 0x2;
    }
 }
}

/**
**  FUNCTION: EDIDGenerateMonitorNameDescriptor()
**
**  @brief
**    Generate EDID Monitor Name Descriptor.
**
**  @params
**    [OUT] pDisplayDescriptor
**          Edid display descriptor.
**     [IN] pcName
**          Monitor name.
**
**  @return
**      VOID.
** ---------------------------------------------------------------------------------------------- */
void EDIDGenerateMonitorNameDescriptor(Panel_EDID_DisplayDescriptor *pDisplayDescriptor, char * pcName)
{
  if ((NULL == pDisplayDescriptor) ||
      (NULL == pcName))
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: Input parameter are NULL\n");
  }
  else
  {
    //Descriptor flag
    pDisplayDescriptor->DescriptorHeader = 0;
    // Set monitor name descriptor block's tag
    pDisplayDescriptor->TagId = 0xFC;
    //Monitor name decription
    MDP_OSAL_MEMCPY(pDisplayDescriptor->Descriptor,  pcName, sizeof(pDisplayDescriptor->Descriptor));
  }
}

/** ----------------------------------------------------------------------------------------------- */
/**
**  FUNCTION: EDIDGenerateChecksum()
**
**  @brief
**    Generate EDID checksum.
**
**  @params
**    [IN/OUT] pEDID
**        Edid config.
**
**  @return
**    VOID.
**
** ------------------------------------------------------------------------------------------------ */
void EDIDGenerateChecksum(MDP_Panel_EDID_Config *pEDID)
{
  uint32   count;
  uint8    totalsum   = 0;
  uint8    *pEDIDData = (uint8*)pEDID;

  for (count = 0; count < (sizeof(MDP_Panel_EDID_Config) - 1); count++)
  {
    totalsum += pEDIDData[count];
  }

  // Total sum, including checksum must equal zero.
  pEDID->Checksum = (uint8)(0x100 - totalsum);
}

//-------------------------------------------------------------------------------------------------
//  AllocDPOverrideBuffers
//
//  @brief
//      Allocate and initialize DPCD and EDID fallback/override data from ACPI.
//
//  @params
//   [IN] eDisplayId
//       Display Id
//   [IN] pPhyDisplay
//       Physical display Info
//
//  @return
//      QDI_STATUS_SUCCESS if DP resource allocation and initialization completed successfully.
//-------------------------------------------------------------------------------------------------
//
static MDP_Status AllocDPOverrideBuffers(MDP_Display_IDType     eDisplayId,
                                         MDP_Panel_AttrType    *pDisplayInfo)
{
  MDP_Status eRetStatus = MDP_STATUS_OK;

  if((eDisplayId >= MDP_DISPLAY_MAX) ||
     (NULL == pDisplayInfo))
  {
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "Invalid display id: %d", eDisplayId);
    eRetStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    MDP_DP_OverrideBufsType *pOverrideBufs   = &pDisplayInfo->uAttrs.sDp.sOverrideBufs;
    XML_BinaryPacketType    *pXMLEDID        = (XML_BinaryPacketType*) sDPEDIDBuffer;
    XML_BinaryPacketType    *pXMLDPCDCaps    = (XML_BinaryPacketType*) sDPDPCDCapsBuffer;
    XML_BinaryPacketType    *pXMLDPCDStatus  = (XML_BinaryPacketType*) sDPDPCDStatusBuffer;

    // Truncate buffers to static limits (these lengths are used to allocate and copy)
    pOverrideBufs->sEDID.uSize       = MDP_MIN(pXMLEDID->uPacketLength, OEM_PANEL_DP_EDID_SIZE);
    pOverrideBufs->sDPCDCaps.uSize   = MDP_MIN(pXMLDPCDCaps->uPacketLength, OEM_PANEL_DP_DPCD_CAPS_SIZE);
    pOverrideBufs->sDPCDStatus.uSize = MDP_MIN(pXMLDPCDStatus->uPacketLength, OEM_PANEL_DP_DPCD_STATUS_SIZE);

    if (MDP_DP_OVERRIDE_MODE_OFF != gPanelConfig.uAttrs.sDp.eOverrideMode)
    {
      // All of the buffers are optional, unless used as a failsafe fallback, in which case a missing buffer could cause
      // the driver to not have valid data to read.
      if ((MDP_DP_OVERRIDE_MODE_FALLBACK == gPanelConfig.uAttrs.sDp.eOverrideMode) &&
          ((0 == pOverrideBufs->sEDID.uSize) ||
           (0 == pOverrideBufs->sDPCDCaps.uSize) ||
           (0 == pOverrideBufs->sDPCDStatus.uSize)))
      {
        MDP_Log_Message(MDP_LOGLEVEL_INFO, "[Display:%i] Invalid DP fallback mode set, not all buffers provided\n", eDisplayId);
      }

      // Allocate the EDID, DPCD caps and status buffers only if they exist, stop early if ran out of memory
      if ((pOverrideBufs->sEDID.uSize > 0) &&
          (NULL == (pOverrideBufs->sEDID.pBuffer = MDP_OSAL_CALLOC(pOverrideBufs->sEDID.uSize))))
      {
        MDP_Log_Message(MDP_LOGLEVEL_WARN, "AllocDPOverrideBuffers() Failed to allocate EDID buffer for display Id %i\n", eDisplayId);
        eRetStatus = MDP_STATUS_NO_RESOURCES;
      }
      else if ((pOverrideBufs->sDPCDCaps.uSize > 0) &&
               (NULL == (pOverrideBufs->sDPCDCaps.pBuffer = MDP_OSAL_CALLOC(pOverrideBufs->sDPCDCaps.uSize))))
      {
        MDP_Log_Message(MDP_LOGLEVEL_WARN, "AllocDPOverrideBuffers() Failed to allocate DPCD Caps buffer for display Id %i\n", eDisplayId);
        eRetStatus = MDP_STATUS_NO_RESOURCES;
      }
      else if ((pOverrideBufs->sDPCDStatus.uSize > 0) &&
               (NULL == (pOverrideBufs->sDPCDStatus.pBuffer = MDP_OSAL_CALLOC(pOverrideBufs->sDPCDStatus.uSize))))
      {
        MDP_Log_Message(MDP_LOGLEVEL_WARN, "AllocDPOverrideBuffers() Failed to allocate DPCD Status buffer for display Id %i\n", eDisplayId);
        eRetStatus = MDP_STATUS_NO_RESOURCES;
      }

      if (eRetStatus != MDP_STATUS_OK)
      {
        // Clear all buffers if any of the allocation failed
        pOverrideBufs->sEDID.uSize                       = 0;
        pOverrideBufs->sDPCDCaps.uSize                   = 0;
        pOverrideBufs->sDPCDStatus.uSize                 = 0;
        pDisplayInfo->uAttrs.sDp.eOverrideMode = MDP_DP_OVERRIDE_MODE_OFF;
      }
      else
      {
        // Copy the EDID, DPCD caps and status buffers from ACPI. Sizes are truncated and should be valid.
        if (NULL != pOverrideBufs->sEDID.pBuffer)
        {
          MDP_OSAL_MEMCPY(pOverrideBufs->sEDID.pBuffer,
                          &pXMLEDID->pData,
                          pOverrideBufs->sEDID.uSize);
        }

        if (NULL != pOverrideBufs->sDPCDCaps.pBuffer)
        {
          MDP_OSAL_MEMCPY(pOverrideBufs->sDPCDCaps.pBuffer,
                          &pXMLDPCDCaps->pData,
                          pOverrideBufs->sDPCDCaps.uSize);
        }

        if (NULL != pOverrideBufs->sDPCDStatus.pBuffer)
        {
          MDP_OSAL_MEMCPY(pOverrideBufs->sDPCDStatus.pBuffer,
                          &pXMLDPCDStatus->pData,
                          pOverrideBufs->sDPCDStatus.uSize);
        }
        pDisplayInfo->uAttrs.sDp.eOverrideMode = gPanelConfig.uAttrs.sDp.eOverrideMode;
      }
    }
  }

  return eRetStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPDetectPanel()
**
** DESCRIPTION:
**   Panel detection code, via XML, I2C or EDID
**
** ---------------------------------------------------------------------- */
MDP_Status MDPDetectPanel(MDP_Display_IDType eDisplayId, MDP_Panel_AttrType *pDisplayInfo)
{
  MDP_Status           eStatus                  = MDP_STATUS_OK;

  MDP_LOG_FUNC_ENTRY("MDPDetectPanel", eDisplayId);

  MDPPlatformParams    sPlatformParams;

  MDP_OSAL_MEMZERO(&sPlatformParams,            sizeof(MDPPlatformParams));
  MDP_OSAL_MEMZERO(&gPanelConfig,               sizeof(MDP_Panel_AttrType));
  MDP_OSAL_MEMZERO(&gDSIContorllerMapping,      sizeof(gDSIContorllerMapping));
  MDP_OSAL_MEMZERO(&gDSIDemuraPanelIDReadCMD,   sizeof(gDSIDemuraPanelIDReadCMD));
  MDP_OSAL_MEMZERO(&gDPDeviceIDMapping,         sizeof(gDPDeviceIDMapping));

  //Update XML tag list for dynamic allocated pointer.
  if (MDP_STATUS_OK != AllocateDynamicBuffer((uint8 *)"DSIInitSequence", sizeof("DSIInitSequence"), &gPanelConfig.uAttrs.sDsi.sInitBuffer, MDP_DSI_COMMAND_BUFFER_SIZE))
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPDetectPanel: DSIInitSequence dynamic allocated failed\n");
  }

  if (MDP_STATUS_OK != AllocateDynamicBuffer((uint8 *)"DSITermSequence", sizeof("DSITermSequence"), &gPanelConfig.uAttrs.sDsi.sTermBuffer, MDP_DSI_COMMAND_BUFFER_SIZE))
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPDetectPanel: DSITermSequence dynamic allocated failed\n");
  }

  if (MDP_STATUS_OK != AllocateDynamicBuffer((uint8 *)"I2CInitSequence", sizeof("I2CInitSequence"), &gPanelConfig.uAttrs.sDsi.sI2CConfig.sI2CInitSequence, MDP_I2C_COMMAND_BUFFER_SIZE))
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPDetectPanel: I2CInitSequence dynamic allocated failed\n");
  }

  if (MDP_STATUS_OK != AllocateDynamicBuffer((uint8 *)"I2CTermSequence", sizeof("I2CTermSequence"), &gPanelConfig.uAttrs.sDsi.sI2CConfig.sI2CTermSequence, MDP_I2C_COMMAND_BUFFER_SIZE))
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPDetectPanel: I2CTermSequence dynamic allocated failed\n");
  }

  if (MDP_STATUS_OK != AllocateDynamicBuffer(NULL, 0, &gPanelConfig.uAttrs.sDsi.sDSCPpsBuffer, MDP_PANEL_DSC_PPS_TOTAL_PACKET_SIZE))
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPDetectPanel: DSCPpsBuffer dynamic allocated failed\n");
  }

  if (NULL == pDisplayInfo)
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else if ((eDisplayId == pDisplayInfo->eDisplayId) &&
           (TRUE       == pDisplayInfo->bDetected))
  {
    // Platform already detected just continue
    eStatus = MDP_STATUS_OK;
  }
  else if (MDP_STATUS_OK != (eStatus = MDPPlatformConfigure(eDisplayId, MDPPLATFORM_CONFIG_GETPANELCONFIG, &sPlatformParams)))
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPLib: MDPPlatformConfigure(MDPPLATFORM_CONFIG_GETPANELCONFIG) failed!\n");
  }
  else if ((NULL == sPlatformParams.sPlatformPanel.pPanelXMLConfig) &&
           (0 == sPlatformParams.sPlatformPanel.uConfigSize))
  {
    // Platform configuration is NULL or invalid
    eStatus = MDP_STATUS_BAD_PARAM;
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "MDPLib: Platform configuration does not exist!\n");
  }
  else if (XML_PARSER_STATUS_OK == XML_Parser(sPlatformParams.sPlatformPanel.pPanelXMLConfig, sPlatformParams.sPlatformPanel.uConfigSize, sXmlTagsList, MDP_ARRAY_LENGTH(sXmlTagsList)))
  {
    MDP_Panel_AttrType *pPanelInfo = &gPanelConfig;

    //Set panel name
    AsciiStrCpyS(pPanelInfo->szName, DISPLAY_PANEL_NAME_MAX_LEN, sPlatformParams.sPlatformPanel.szName);
    pPanelInfo->uNumInterfaces = MDP_INTERFACE_SINGLE;

    // Setup any display interface specific settings
    switch (pPanelInfo->ePhysConnect)
    {
      case MDP_DISPLAY_CONNECT_PRIMARY_DSI_VIDEO:
      case MDP_DISPLAY_CONNECT_PRIMARY_DSI_CMD:
      case MDP_DISPLAY_CONNECT_SECONDARY_DSI_VIDEO:
      case MDP_DISPLAY_CONNECT_SECONDARY_DSI_CMD:
      {
        XML_BinaryPacketType  sXMLBinaryData;
        uint8                *pSrc             = (uint8 *)gDSIContorllerMapping;
        uint8                *pDsiMapping      = NULL;

        pPanelInfo->sDSCConfig.pDSCPpsBuffer  = NULL;

        if (pPanelInfo->sDSCConfig.bDSCEnable)
        {
          pPanelInfo->sDSCConfig.pDSCPpsBuffer = (void*)gPanelConfig.uAttrs.sDsi.sDSCPpsBuffer.pBuffer;
        }

        if (pPanelInfo->uAttrs.sDsi.eSplitLinkConfig >= MDP_SPLIT_LINK_CONFIG_MAX)
        {
          MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPDetectPanel: Invalid Split Link configuration (%d), Split link disabled\n", pPanelInfo->uAttrs.sDsi.eSplitLinkConfig);
          pPanelInfo->uAttrs.sDsi.eSplitLinkConfig = MDP_SPLIT_LINK_CONFIG_DISABLED;
        }

        // Use Unaligned Memory read from DSI Command buffer (Required for THUMB2 mode)
        MDP_ReadUnaligned_U32(&sXMLBinaryData.uPacketLength, pSrc);
        sXMLBinaryData.pData = (uint8* )&(((XML_BinaryPacketType*)pSrc)->pData);
        pDsiMapping = (uint8*)sXMLBinaryData.pData;

        if (TRUE == pPanelInfo->sDSCConfig.bDSCEnable)
        {
          if ((1 < pPanelInfo->sDSCConfig.uDSCMajor) ||
              (2 < pPanelInfo->sDSCConfig.uDSCMinor))
          {
            /* Reset to default DSC major and minor version */
            MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPDetectPanel: DSC major:%d minor:%d invalid, using default\n", pPanelInfo->sDSCConfig.uDSCMajor, pPanelInfo->sDSCConfig.uDSCMinor);
            pPanelInfo->sDSCConfig.uDSCMajor = 1;
            pPanelInfo->sDSCConfig.uDSCMinor = 1;
            pPanelInfo->sDSCConfig.uDSCScr   = 0;
          }
        }

        pPanelInfo->uNumInterfaces = MDP_INTERFACE_SINGLE;

        if (0 == sXMLBinaryData.uPacketLength)
        {
          /* If Mapping is not defined, default to DSI controller 0*/
          pPanelInfo->uAttrs.sDsi.uControllerMapping[0]    = 0;
          pPanelInfo->uAttrs.sDsi.uControllerMappingMask   = 0x1;
          pPanelInfo->uAttrs.sDsi.uControllerSinglePrimary = DSI_0_SINGLE_PRIMARY;
        }
        else if (1 == sXMLBinaryData.uPacketLength)
        {
          pPanelInfo->uAttrs.sDsi.uControllerMapping[0]  = pDsiMapping[0];
          pPanelInfo->uAttrs.sDsi.uControllerMappingMask = 0x1;

          // Check is this is single DSI only with DSI1 controller as primary
          if (0x00 == pDsiMapping[0])
          {
            pPanelInfo->uAttrs.sDsi.uControllerSinglePrimary = DSI_0_SINGLE_PRIMARY;
          }
          else
          {
            pPanelInfo->uAttrs.sDsi.uControllerSinglePrimary = DSI_1_SINGLE_PRIMARY;
          }
        }
        else if( (0x00 == pDsiMapping[0]) &&
                 (0x01 == pDsiMapping[1]))
        {
          /* Enable Dual pipe if DSI panel is dual DSI panel */
          pPanelInfo->uAttrs.sDsi.uControllerMapping[0]   = pDsiMapping[0];
          pPanelInfo->uAttrs.sDsi.uControllerMapping[1]   = pDsiMapping[1];
          pPanelInfo->uAttrs.sDsi.uControllerMappingMask  = 0x3;
          pPanelInfo->uNumInterfaces                      = MDP_INTERFACE_DUAL;
        }
        else if ((0x01 == pDsiMapping[0]) &&
                 (0x00 == pDsiMapping[1]))
        {
          /* Enable Dual pipe if DSI panel is dual DSI panel */
          pPanelInfo->uAttrs.sDsi.uControllerMapping[0]  = pDsiMapping[0];
          pPanelInfo->uAttrs.sDsi.uControllerMapping[1]  = pDsiMapping[1];
          pPanelInfo->uAttrs.sDsi.uControllerMappingMask = 0x3;
          pPanelInfo->uNumInterfaces                     = MDP_INTERFACE_DUAL;
        }


        break;
      }
      case MDP_DISPLAY_CONNECT_EDP:
      {
        if (MDP_STATUS_OK != AllocDPOverrideBuffers(eDisplayId, pPanelInfo))
        {
          eStatus = MDP_STATUS_NO_RESOURCES;
          MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DPDriver allocate data failed for %d display id\n", eDisplayId);
        }
        MDPPanelGetEDID(pPanelInfo);
        break;
      }
      default:
        break;
    }


    MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxe: Resolution %dx%d (PhysConnect %d)\n", pPanelInfo->uDisplayWidth,
                                                                                          pPanelInfo->uDisplayHeight,
                                                                                          pPanelInfo->ePhysConnect);

    /*
     * Perform a quick sanity check
     * for eDP, if both width and height are 0, then panel timing is derived from edid
     * so no sanity check for eDP
     */
    if ((pPanelInfo->ePhysConnect !=  MDP_DISPLAY_CONNECT_EDP)  && 
        (pPanelInfo->ePhysConnect !=  MDP_DISPLAY_CONNECT_DP_2) && 
        (pPanelInfo->ePhysConnect !=  MDP_DISPLAY_CONNECT_DP)   && 
        (pPanelInfo->ePhysConnect !=  MDP_DISPLAY_CONNECT_DP_1) && 
        ((0 == pPanelInfo->uDisplayHeight) || (0 == pPanelInfo->uDisplayWidth)))
    {
      MDP_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxe: Invalid mode detected for panel id %i!\n", pDisplayInfo->eDisplayId);
      eStatus = MDP_STATUS_BAD_PARAM;
    }
    else
    {
      // Check panel orientation override
      MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));
      if (MDP_STATUS_OK == MDPPlatformConfigure(eDisplayId, MDPPLATFORM_CONFIG_GETPLATFORMINFO, &sPlatformParams))
      {
        if (sPlatformParams.sPlatformInfo.uPanelOrientationOverride != MDP_ROTATE_NONE)
        {
          gPanelConfig.ePhysPanelOrientation = sPlatformParams.sPlatformInfo.uPanelOrientationOverride;
        }
      }

      // Copy local to the caller's data structure
      MDP_OSAL_MEMCPY(pDisplayInfo, pPanelInfo, sizeof(MDP_Panel_AttrType));

      // Report display is detected & set the display id
      pDisplayInfo->eDisplayId = eDisplayId;
      pDisplayInfo->bDetected  = TRUE;

      // Check for sw rendering mode (used for invalid platforms)
      MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));
      if (MDP_STATUS_OK == MDPPlatformConfigure(eDisplayId, MDPPLATFORM_CONFIG_SW_RENDERER, &sPlatformParams))
      {
        pDisplayInfo->bSWRenderer = sPlatformParams.sPlatformInfo.bSWRender;
      }

      // Append PCB to primary flags to append any new flags
      pDisplayInfo->eDisplayFlags |= PcdGet32(PcdPrimaryFlags);
    }

    MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));

    // Get SPR configuration
    if (MDP_STATUS_OK == MDPGetSprConfigInfo(eDisplayId, &sPlatformParams))
    {
      pDisplayInfo->uAttrs.sDsi.sDemuraConfig.pSprXMLConfig = sPlatformParams.sSprXMLInfo.pSprXMLConfig;

      if ((gDemuraPanelID32[0]) ||
          (gDemuraPanelID32[1]))
      {
        // Demura panel ID override from panel xml
        pDisplayInfo->uAttrs.sDsi.sDemuraConfig.uDemuraPanelID = (((uint64)gDemuraPanelID32[1]) << 32) + gDemuraPanelID32[0];
      }
      else
      {
        // Read Demura panel ID from panel
        XML_BinaryPacketType  sXMLBinaryData;
        uint8                *pSrc = gDSIDemuraPanelIDReadCMD;

        // Use Unaligned Memory read from DSI Command buffer (Required for THUMB2 mode)
        MDP_ReadUnaligned_U32(&sXMLBinaryData.uPacketLength, pSrc);
        sXMLBinaryData.pData = (uint8*)&(((XML_BinaryPacketType*)pSrc)->pData);

        if ((0 != sXMLBinaryData.uPacketLength) &&
            (sXMLBinaryData.uPacketLength < sizeof(gDSIDemuraPanelIDReadCMD)) &&
            (0 != sXMLBinaryData.pData[0]))
        {
          MDPGetDemmuraPanelID(pDisplayInfo, sXMLBinaryData.pData, sXMLBinaryData.uPacketLength);
        }
      }
    }
  }
  else
  {
    // Parser failed
    MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: Invalid or missing XML configuration!\n");
    eStatus = MDP_STATUS_FAILED;
  }

  MDP_LOG_FUNC_EXIT("MDPDetectPanel", eDisplayId);

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: SPRTableValid()
*/
/*!
* \brief
*     Helper function to check if the SPR arrary is empty or not.
*
* \param [in] pArray       - Array point
* \param [in] uLength      - Array Length
*
* \retval bool32
*
****************************************************************************/
static bool32 SPRTableValid(void *pArray, uint32 uLength)
{
  uint32  uI     = 0;
  bool32  bValid = FALSE;
  uint32 *pList  = (uint32 *)pArray;

  if (NULL != pList)
  {
    for (uI=0; uI<uLength; uI++)
    {
      if (0 != *pList)
      {
        bValid = TRUE;
        break;
      }

      pList++;
    }
  }

  return bValid;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPGetSprConfigInfo()
**
** DESCRIPTION:
**   Get display SPR configuration info by reading / parsing the SPR xml.
**
** ---------------------------------------------------------------------- */
static MDP_Status MDPGetSprConfigInfo(MDP_Display_IDType eDisplayId, MDPPlatformParams *pPlatformParams)
{
  MDP_Status                  eStatus                                          = MDP_STATUS_OK;
  MDP_Panel_AttrType         *pDisplayInfo                                     = MDP_GET_DISPLAYINFO(eDisplayId);
  const MDPInterfaceCapsType *pMDPInterfaceCaps                                = MDPGetInterfaceCaps();
  const CHAR8                 szAdaptiveMode[HAL_MDP_SPR_ADAPTIVEMODE_MAX][20] = {"\0", "YYGM", "YYGW"};
  const CHAR8                 szFilterType[HAL_MDP_SPR_FILTER_MAX][20]         = {"\0", "PixelDrop", "Bilinear", "FourTap", "Adaptive", "2DAvg"};

  // Check the existence of SPR config file and get display SPR info
  if ((NULL == pPlatformParams) ||
      (NULL == pMDPInterfaceCaps))
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPGetSprConfigInfo: pPlatformParams or pMDPInterfaceCaps is NULL!\n");
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else if ((0                       == (MDP_INTERFACE_CAPS_SPR & pMDPInterfaceCaps->uInterfaceFeatureCaps)) ||
           (HAL_MDP_SPR_PACK_NONE   == pDisplayInfo->uAttrs.sDsi.sDemuraConfig.eSprPackType))
  {
    // SPR is not supported or not enabled in UEFI.
    eStatus = MDP_STATUS_NOT_SUPPORTED;
  }
  else
  {
    if ((MDP_STATUS_OK        == MDPPlatformConfigure(eDisplayId, MDPPLATFORM_CONFIG_GETSPRXMLINFO, pPlatformParams)) &&
        (XML_PARSER_STATUS_OK == XML_Parser(pPlatformParams->sSprXMLInfo.pSprXMLConfig, pPlatformParams->sSprXMLInfo.uSprConfigSize, sSprXmlTagsList, MDP_ARRAY_LENGTH(sSprXmlTagsList))))
    {
      HAL_MDP_SprDataConfigType  *psDisplaySprDataConfig = &pDisplayInfo->uAttrs.sDsi.sDemuraConfig.sDisplaySprDataConfig;
      uint32                      uI                     = 0;

      MDP_OSAL_MEMCPY(psDisplaySprDataConfig, &gPanelConfig.uAttrs.sDsi.sDemuraConfig.sDisplaySprDataConfig, sizeof(HAL_MDP_SprDataConfigType));

      for (uI=0; uI<HAL_MDP_SPR_ADAPTIVEMODE_MAX; uI++)
      {
        if (HAL_MDP_SPR_ADAPTIVEMODE_NONE == uI)
        {
          // Skip the string comparison for szAdaptiveMode[0].
          continue;
        }
        else if (0 == AsciiStrnCmp((CHAR8 *)psDisplaySprDataConfig->aAdaptiveMode, szAdaptiveMode[uI], AsciiStrLen(szAdaptiveMode[uI])))
        {
          psDisplaySprDataConfig->eAdaptiveMode = (HAL_MDP_SprAdaptiveMode_Type)uI;
          break;
        }
      }

      for (uI=0; uI<HAL_MDP_SPR_FILTER_MAX; uI++)
      {
        if (HAL_MDP_SPR_FILTER_NONE == uI)
        {
          // Skip the string comparison for szFilterType[0].
          continue;
        }
        else if (0 == AsciiStrnCmp((CHAR8 *)psDisplaySprDataConfig->aFilterType, szFilterType[uI], AsciiStrLen(szFilterType[uI])))
        {
          psDisplaySprDataConfig->eFilterType = (HAL_MDP_SprFilter_Type)uI;
          break;
        }
      }

      if (TRUE == SPRTableValid(&psDisplaySprDataConfig->aAdaptiveStrengths[0], MDP_ARRAY_LENGTH(psDisplaySprDataConfig->aAdaptiveStrengths)))
      {
        psDisplaySprDataConfig->bAdaptiveStrengthsOverride = TRUE;
      }

      if (TRUE == SPRTableValid(&psDisplaySprDataConfig->aFilterCoeffs[0], MDP_ARRAY_LENGTH(psDisplaySprDataConfig->aFilterCoeffs)))
      {
        psDisplaySprDataConfig->bFilterCoeffsOverride = TRUE;
      }

      if (TRUE == SPRTableValid(&psDisplaySprDataConfig->aColorPhaseOffsetsRed[0], MDP_ARRAY_LENGTH(psDisplaySprDataConfig->aColorPhaseOffsetsRed)))
      {
        psDisplaySprDataConfig->bColorPhaseOffsetsRedOverride = TRUE;
      }

      if (TRUE == SPRTableValid(&psDisplaySprDataConfig->aColorPhaseOffsetsGreen[0], MDP_ARRAY_LENGTH(psDisplaySprDataConfig->aColorPhaseOffsetsGreen)))
      {
        psDisplaySprDataConfig->bColorPhaseOffsetsGreenOverride = TRUE;
      }

      if (TRUE == SPRTableValid(&psDisplaySprDataConfig->aColorPhaseOffsetsBlue[0], MDP_ARRAY_LENGTH(psDisplaySprDataConfig->aColorPhaseOffsetsBlue)))
      {
        psDisplaySprDataConfig->bColorPhaseOffsetsBlueOverride = TRUE;
      }

      if (TRUE == SPRTableValid(&psDisplaySprDataConfig->aColorPhaseOffsetsWhite[0], MDP_ARRAY_LENGTH(psDisplaySprDataConfig->aColorPhaseOffsetsWhite)))
      {
        psDisplaySprDataConfig->bColorPhaseOffsetsWhiteOverride = TRUE;
      }
    }
  }

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: MDPDetectPanelExt()
**
** DESCRIPTION:
**   Get panel configuration info by reading / parsing the xml.
**
** ---------------------------------------------------------------------- */
MDP_Status MDPDetectPanelExt(MDP_Display_IDType eDisplayId, MDP_Panel_AttrType* pDisplayInfo)
{
  MDP_Status           eStatus = MDP_STATUS_OK;
  MDPPlatformParams    sPlatformParams;

  MDP_OSAL_MEMZERO(&sPlatformParams, sizeof(MDPPlatformParams));

  /* get the xml setting from the platform */
  if ((MDP_STATUS_OK != MDPPlatformConfigure(eDisplayId, MDPPLATFORM_CONFIG_GETPANELCONFIG, &sPlatformParams)) ||
      (NULL == sPlatformParams.sPlatformPanel.pPanelXMLConfig)                                                 ||
      (0 == sPlatformParams.sPlatformPanel.uConfigSize)                                                        ||
      (XML_PARSER_STATUS_OK != XML_Parser(sPlatformParams.sPlatformPanel.pPanelXMLConfig, sPlatformParams.sPlatformPanel.uConfigSize, sExtDPXmlTagsList, XML_EXTDPTAGSLIST_LENGTH)))
  {
    MDP_Log_Message(MDP_LOGLEVEL_WARN, "MDPGetExtDisplayPlatformInfo: Failed to get xml settings for external display :0x%x!\n", eDisplayId);
  }
  else
  {
    if ((MDP_DP_OVERRIDE_MODE_FALLBACK == gPanelConfig.uAttrs.sDp.eOverrideMode) &&
        (MDP_STATUS_OK != AllocDPOverrideBuffers(eDisplayId, pDisplayInfo)))
    {
      eStatus = MDP_STATUS_NO_RESOURCES;
      MDP_Log_Message(MDP_LOGLEVEL_ERROR, "DPDriver allocate data failed for %d display id\n", eDisplayId);
    }
  }

  return eStatus;
}
