/*=============================================================================
 
  File: Dp_host.c
 
  DP Host layer
  
 
 Copyright (c) 2016-2023 Qualcomm Technologies, Inc.
 All Rights Reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.
 =============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif


/*---------------------------------------------------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------------------------------------------------*/
#include "dp_i.h"
#include "hal_dp_phy.h"
#include "dp_dsc.h"
#include "dp_audio.h"
#include "dp_sim.h"
#include "dp_redirector.h"
#include "dp_mst.h"

/*---------------------------------------------------------------------------------------------------------------------
 * Defines
 *-------------------------------------------------------------------------------------------------------------------*/

#define DPHOST_GET_SHARED_CTX()                     (&gDpSharedData)                     // Get global context for DP Host
#define DPHOST_GET_HOST_LOCK()                      (DPHOST_GET_SHARED_CTX()->hHostLock) // Get global lock for DP Host
#define DPHOST_GET_CONTROLLER_INFO(_id_)            (((_id_) < DP_MAX_CONTROLLER_NUM) ? (&sDPControllerPool[(_id_)]) : (&sDPControllerPool[0]))
#define DPHOST_GET_LIST_SIZE(_list_)                (sizeof(_list_)/sizeof(_list_[0]))

/* Defines for DP PHY CTS settings */
#define DP_IDLE_PATTERN_REP_NUM                         0
#define DP_SAFE_TO_EXIT_LEVEL                           2
#define DP_HBR2_ERM_PATTERN                             0x00010000        // Sending HBR2 compliance EYE pattern
#define DP_HBR2_COMPLIANCE_SCRAMBLER_RESET              0xFC              // Count of number of scrambled 0 symbols to be output for every enhanced framing scrambler reset sequence (SR BF BF SR). Count includes the reset sequence.
#define DP_CUSTOM_PATTERN_R0                            0x3E0F83E0        // Custom pattern R0 required by PHY CTS
#define DP_CUSTOM_PATTERN_R1                            0x0F83E0F8        // Custom pattern R1 required by PHY CTS
#define DP_CUSTOM_PATTERN_R2                            0x0000F83E        // Custom pattern R2 required by PHY CTS
#define DP_MAX_CONTROLLER_NUM                           3                 // Maximum number of controllers

/* Defines for restoring default values of PHY CTS setting registers */
#define DEFAULT_DP_IDLE_PATTERN_REP_NUM                 0xA
#define DEFAULT_DP_SAFE_TO_EXIT_LEVEL                   0x14
#define DEFAULT_DP_HBR2_ERM_PATTERN                     0
#define DEFAULT_DP_HBR2_COMPLIANCE_SCRAMBLER_RESET      0x2000
#define DEFAULT_DP_CUSTOM_PATTERN_R0                    0
#define DEFAULT_DP_CUSTOM_PATTERN_R1                    0
#define DEFAULT_DP_CUSTOM_PATTERN_R2                    0

/* Maximum wait time for controller link state changes in microseconds.  Based on 24hz refresh */
#define DP_MAX_LINK_STATE_CHANGE_WAIT_US                ((1000*1000)/24)   

/* Interval time for checking mainlink ready status */
#define DP_STATE_CHANGE_POLL_TIME_US                    100

/* AUX timeout limits to be set in hardware */
#define DP_AUX_CLKS_FOR_ONE_MSEC                        0x4B00             // 19.2Mhz clock assumed

/* Maximum allowed attempts to configure DP link settings*/
#define DP_LINK_CONFIG_MAX_RETRIES                      24

/*---------------------------------------------------------------------------------------------------------------------
 * Global Data Definitions
 *-------------------------------------------------------------------------------------------------------------------*/
DP_DeviceDataType  gDpSharedData;

/* A mapping to give display ID from the combination of device ID and stream ID. */
const MDP_Display_IDType sMSTDisplayMap[DP_DEVICE_MAX][DP_MST_STREAM_ID_MAX] =
{
  // Default to external non-external DP devices
  {MDP_DISPLAY_EXTERNAL,  MDP_DISPLAY_EXTERNAL }, // DP_DEVICE_ID_NONE
  {MDP_DISPLAY_EXTERNAL,  MDP_DISPLAY_EXTERNAL2}, // DP_DEVICE_ID_ALT_MODE_0
  {MDP_DISPLAY_EXTERNAL3, MDP_DISPLAY_EXTERNAL4}, // DP_DEVICE_ID_ALT_MODE_1
  {MDP_DISPLAY_EXTERNAL5, MDP_DISPLAY_EXTERNAL6}, // DP_DEVICE_ID_ALT_MODE_2
  {MDP_DISPLAY_PRIMARY,   MDP_DISPLAY_PRIMARY  }, // DP_DEVICE_ID_EDP  
};

/* Mapping table from USB pin assignment to number of lanes */
uint32 sPinAssignmentToLaneNumMapping[DP_CONNECTION_PINASSIGNMENT_MAX] =
{
  0, // DP_CONNECTION_PINASSIGNMENT_INVALID  = 0x00,    /* No DP cable is connected                     */
  0, // DP_CONNECTION_PINASSIGNMENT_DFPD_A   = 0x01,    /* DFP_D(Downstream Facing Port DP) Pin A       */
  0, // DP_CONNECTION_PINASSIGNMENT_DFPD_B   = 0x02,    /* DFP_D(Downstream Facing Port DP) Pin B       */
  4, // DP_CONNECTION_PINASSIGNMENT_DFPD_C   = 0x03,    /* DFP_D(Downstream Facing Port DP) Pin C       */
  2, // DP_CONNECTION_PINASSIGNMENT_DFPD_D   = 0x04,    /* DFP_D(Downstream Facing Port DP) Pin D       */
  4, // DP_CONNECTION_PINASSIGNMENT_DFPD_E   = 0x05,    /* DFP_D(Downstream Facing Port DP) Pin E       */
  2, // DP_CONNECTION_PINASSIGNMENT_DFPD_F   = 0x06,    /* DFP_D(Downstream Facing Port DP) Pin F       */
  0, // DP_CONNECTION_PINASSIGNMENT_UFPD_A   = 0x07,    /* UFP_D(Upstream Facing Port DP)   Pin A       */
  0, // DP_CONNECTION_PINASSIGNMENT_UFPD_B   = 0x08,    /* UFP_D(Upstream Facing Port DP)   Pin B       */
  4, // DP_CONNECTION_PINASSIGNMENT_UFPD_C   = 0x09,    /* UFP_D(Upstream Facing Port DP)   Pin C       */
  2, // DP_CONNECTION_PINASSIGNMENT_UFPD_D   = 0x0A,    /* UFP_D(Upstream Facing Port DP)   Pin D       */
  4, // DP_CONNECTION_PINASSIGNMENT_UFPD_E   = 0x0B,    /* UFP_D(Upstream Facing Port DP)   Pin E       */
};

/* Controller pool table for dynamic controller allocation. */
DP_ControllerInfoType sDPControllerPool[DP_MAX_CONTROLLER_NUM] =
{
  // eControllerId,       bInUse
  {DP_CONTROLLER_ID_DP_0, FALSE}, // DP_CONTROLLER_ID_DP_0
  {DP_CONTROLLER_ID_DP_1, FALSE}, // DP_CONTROLLER_ID_DP_1
  {DP_CONTROLLER_ID_DP_2, FALSE}, // DP_CONTROLLER_ID_DP_2
};


/* Friendly DP device names */
const char *sDPDeviceName[DP_DEVICE_MAX] =
{
  "Invalid",      // DP_DEVICE_ID_NONE
  "DP AltMode#0", // DP_DEVICE_ID_ALT_MODE_0
  "DP AltMode#1", // DP_DEVICE_ID_ALT_MODE_1
  "DP AltMode#2", // DP_DEVICE_ID_ALT_MODE_2
  "eDP",          // DP_DEVICE_ID_EDP
};


/* -----------------------------------------------------------------------
** Local Prototypes
** ----------------------------------------------------------------------- */
static DP_ControllerIDType AllocateDPController(DP_DeviceIDType   eDeviceID,
                                                DP_DeviceCtxType *pDeviceCtx);

static void FreeDPController(DP_DeviceCtxType *pDeviceCtx);

void CloseDeviceContext(DP_DeviceCtxType  *pDeviceCtx);

static DP_Status ReadModeInfoFromSink(DP_DisplayCtxType *pDisplayCtx);

static DP_Status LinkRateReduce(DP_DisplayCtxType    *pDisplayCtx);

static DP_Status LaneCountReduce(DP_DisplayCtxType* pDisplayCtx);

static DP_Status VerifyLinkBandwidth(DP_DisplayCtxType* pDisplayCtx);

static DP_Status SetPHYTestPattern(MDP_Display_IDType    eDisplayID, 
                                   DP_ControllerIDType   eControllerID,
                                   DP_PHYTestPatternType ePhyTestPattern);

static uint32 MapDPInterruptsToHAL(DP_DisplayCtxType *pDisplayCtx,
                                   uint32             uDPInterrupts);

static uint32 MapHALInterruptsToDP(DP_DisplayCtxType *pDisplayCtx,
                                   uint32             uHALInterrupts);

static DP_Status HandleReplugHPD(DP_DisplayCtxType  *pDisplayCtx);

static DP_Status HandleIrqHPD(DP_DisplayCtxType  *pDisplayCtx);

static void IRQHPDWorkThread(void *pDeviceObject, 
                             void *pContext);

static uint32 FilterLanesByPinAssignment(DP_DeviceIDType            eDeviceID,
                                         DP_ConnectionPinAssignment ePinAssignment,
                                         uint32                     uNumberofLanes);

static DP_Status ConfigureMainLink(DP_DisplayCtxType *pDisplayCtx, 
                                   DP_LinkCommandType eCommandType);

static uint32 GetNumStreamsInUse(DP_DeviceCtxType *pDeviceCtx);

static bool32 GetConcurrencyMode(DP_DeviceCtxType *pDeviceCtx);

static DP_Status ConfigureExternalSourceClock(DP_DeviceCtxType     *pDeviceCtx,
                                              HAL_DP_PllConfigType *pPhyConfig,
                                              bool32                bEnable);

static int32 UpdateSourceClockRefCount(DP_DeviceCtxType *pDeviceCtx,
                                       int32             iValue);

static bool32 IsAltModeDPDevice(DP_DeviceIDType eDeviceID);

static DP_Status QueryBrightnessCaps(DP_DisplayCtxType *pDisplayCtx);

static DP_Status SetupBondedConfig(DP_DeviceCtxType         *pDeviceCtx, 
                                   DP_StreamCtxType         *pStreamCtx,
                                   DP_Config_BondedModeType *pBondedModeCfg);

static DP_Status SetModeDSCConfig(DP_DisplayCtxType *pDisplayCtx, bool32 bTraining);

static DP_DeviceModeType GetDPDeviceMode(MDP_Display_IDType eDisplayID,
                                         DP_DeviceIDType    eDeviceID,
                                         bool32             bTunnelingmode);

static DP_Status SetVSCSDP(DP_DeviceCtxType *pDeviceCtx,
                           DP_StreamCtxType *pStreamCtx);

static bool32 ValidLinkRate(DP_DeviceCtxType *pDeviceCtx, uint32 uLinkRate);

static float Ceilf(float x);

static DP_Status DP_LinkLaneReduction(DP_DisplayCtxType *pDisplayCtx);

/*------------------------------------------------------------------------------------------
 * Public Functions
 *------------------------------------------------------------------------------------------*/

/*********************************************************************************************
*
** FUNCTION: DP_Host_SetMode()
*/
/*!
* \DESCRIPTION
*     Set selected display mode
*
* \param [in]   pDisplayCtx        - Pointer to context
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_Host_SetMode(DP_DisplayCtxType    *pDisplayCtx)
{
  DP_Status               eStatus      = DP_STATUS_SUCCESS; 
  DP_DeviceCtxType       *pDeviceCtx   = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType       *pStreamCtx   = DPHOST_GET_STREAM_CTX(pDisplayCtx);

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx))
  {
    DP_LOG_MESSAGE_ERROR("DP_Host_SetMode: unexpected null handle ");
    eStatus = DP_STATUS_FAILED_DRIVER_NOT_INITIALIZED;
  }
  else
  {
    if (DP_HOST_MODE_INVALID == pStreamCtx->uModeIndex)
    {
      TraceInfo(QdiTraceDP, "DP%d: DP_Host_SetMode, invalid mode set.", pStreamCtx->eDisplayID);
      eStatus = DP_STATUS_FAILED_DRIVER_NOT_INITIALIZED;
    }
    else
    {
      DP_PanelInfoType          *psPanelInfo              = &(pStreamCtx->sPanelInfo[pStreamCtx->uModeIndex]);
      bool32                     bASSR                    = FALSE;
      bool32                     bLinkTrainingRequired    = FALSE;
      DP_TUSizeCalcParamType     sTUSizeParam;
      DP_RGCalcParamType         sRGCalcParam;
      HAL_DP_TUConfigType        sHALTuConfig;
      HAL_DP_RGConfigType        sHALRgConfig;
      HAL_DP_StreamAttribType    sStreamAttrib;
      HAL_DP_MSAPacketType       sHALMSAPacket;
      DP_PixelClk_Info           sPixClkInfo;
      HAL_DP_SinkAttribType      sSinkAttrib;
      DPMST_VCAllocConfigType    sVCInfo;
      uint32                     uAudioStreamIndex;
      uint32                     uRetries;

      /* If the link is not configured or we are in SST mode, then link training is required */
      if ((FALSE == pDeviceCtx->bMSTEnabled) ||
          (FALSE == pDeviceCtx->bLinkConfigured))
      {
        bLinkTrainingRequired = TRUE;
      }
 
      for (uRetries = 0; uRetries < DP_LINK_CONFIG_MAX_RETRIES; uRetries++)
      {
        DP_OSAL_MemSet((void *)&sTUSizeParam,  0, sizeof(DP_TUSizeCalcParamType));
        DP_OSAL_MemSet((void *)&sRGCalcParam,  0, sizeof(DP_RGCalcParamType));
        DP_OSAL_MemSet((void *)&sHALTuConfig,  0, sizeof(HAL_DP_TUConfigType));  
        DP_OSAL_MemSet((void *)&sHALRgConfig,  0, sizeof(HAL_DP_RGConfigType));  
        DP_OSAL_MemSet((void *)&sStreamAttrib, 0, sizeof(HAL_DP_StreamAttribType));
        DP_OSAL_MemSet((void *)&sHALMSAPacket, 0, sizeof(HAL_DP_MSAPacketType));
        DP_OSAL_MemSet((void *)&sPixClkInfo,   0, sizeof(DP_PixelClk_Info)); 
        DP_OSAL_MemSet((void *)&sSinkAttrib,   0, sizeof(HAL_DP_SinkAttribType));
        DP_OSAL_MemSet((void *)&sVCInfo,       0, sizeof(DPMST_VCAllocConfigType));

        /* Default to max supported lane link rate and lane number from DPCD if they are not set by DP_Host_SetProperty for mode changing. 
           The values could have been changed by previous SetMode when link training failure and reduce link rate */
        if (0 == (pStreamCtx->uDirtyBits & DP_DIRTYFIELD_LINK_RATE))
        {
          pDeviceCtx->uLinkRateInKhz = pDeviceCtx->sSinkDPCDCap.uMaxLinkRateInKhz;
        }

        if (0 == (pStreamCtx->uDirtyBits & DP_DIRTYFIELD_LANE_NUMBER))
        {
          pDeviceCtx->uNumLanes = pDeviceCtx->sSinkDPCDCap.uMaxLaneCount;
        }

        // Pin assignment info from USB indicates a lane number, this lane number may not match with DPCP reported lane number
        pDeviceCtx->uNumLanes = FilterLanesByPinAssignment(pDeviceCtx->eDeviceID, pDeviceCtx->ePinAssignment, pDeviceCtx->uNumLanes);
        
        if ((uRetries > 0) &&
            (TRUE == bLinkTrainingRequired))
        {
          TraceInfo(QdiTraceDP, "DP%d: Retrying Link Training, %dKhz with %d lanes",
                                 pStreamCtx->eDisplayID,
                                 pDeviceCtx->uLinkRateInKhz,
                                 pDeviceCtx->uNumLanes);
        }
                    
        // Special handling for Compliance test cases
        if (pStreamCtx->uDirtyBits & DP_DIRTYFIELD_BPC)
        {
          psPanelInfo->eColorFormat = (pStreamCtx->uBitDepth == DP_BITDEPTH_6BPC) ? DP_PIXEL_FORMAT_RGB_666_18BPP : DP_PIXEL_FORMAT_RGB_888_24BPP;
          pStreamCtx->uDirtyBits   &= ~DP_DIRTYFIELD_BPC;
        }
        else
        {
          pStreamCtx->uBitDepth = DPHOST_GETPIXELFMT(psPanelInfo->eColorFormat).uBitsPerComponent;
        }

        // Recalculate FEC/DSC parameters on a mode set, as the previous parameters assumed best link rate
        if (DP_STATUS_SUCCESS != DP_FEC_CalculateParameters(pDisplayCtx))
        {
          DP_LOG_MESSAGE_ERROR("DP_Host_SetMode: Failed to calculate FEC parameters for display %d", pStreamCtx->eDisplayID);
        }
        else if ((TRUE               == bLinkTrainingRequired) && 
                 ((DP_STATUS_SUCCESS != DP_FEC_ConfigureSink(pDisplayCtx, FALSE)) ||
                  (DP_STATUS_SUCCESS != DP_DSC_ConfigureSink(pDisplayCtx, FALSE))))
        {
          DP_LOG_MESSAGE_ERROR("DP_Host_SetMode: Failed to configure FEC or DSC on sink for display %d", pStreamCtx->eDisplayID);
        } 
        else if (DP_STATUS_SUCCESS != DP_DSC_CalculateParameters(pDisplayCtx, pStreamCtx->uModeIndex))
        {
          DP_LOG_MESSAGE_ERROR("DP_Host_SetMode: Failed to calculate DSC parameters for display %d", pStreamCtx->eDisplayID);
        }

        /* Select frequency table based on pixel clock frequency, which needs to be called prior to DP_CalculateLink() */
        if (pDeviceCtx->bDualPixelMode)
        {
          HAL_DP_PHY_SelectPClockFrequencyTable(pDeviceCtx->eDeviceID, pDeviceCtx->uLinkRateInKhz, psPanelInfo->uPclkFreq / 2);
        }
        else
        {
          HAL_DP_PHY_SelectPClockFrequencyTable(pDeviceCtx->eDeviceID, pDeviceCtx->uLinkRateInKhz, psPanelInfo->uPclkFreq);
        }

        /* Calculate all the link settings */
        eStatus = DP_CalculateLink(pDisplayCtx, &pDeviceCtx->sSinkDPCDCap, psPanelInfo, &sPixClkInfo);

        if(DP_STATUS_SUCCESS != eStatus)
        {
          DP_LOG_MESSAGE_ERROR("DP_Host_SetMode: Failed to calculate link settings for display %d", pStreamCtx->eDisplayID);
          eStatus = DP_STATUS_FAIL;
          goto exit;
        }

        /* Calculate TU size and related settings */
        if (FALSE == pDeviceCtx->bMSTEnabled)
        {
          sTUSizeParam.eDisplayId       = pStreamCtx->eDisplayID;
          sTUSizeParam.uBPP             = pStreamCtx->uBitDepth * DP_NUM_COLOR_COMPONENTS;
          sTUSizeParam.uNumberOfLanes   = pDeviceCtx->uNumLanes;
          sTUSizeParam.uWidth           = psPanelInfo->uVisibleWidthInPixels;
          sTUSizeParam.uOriginalWidth   = psPanelInfo->uVisibleWidthInPixels;
          sTUSizeParam.dHBlankPeriod    = (double)psPanelInfo->uHsyncFrontPorchInPixels +
                                          (double)psPanelInfo->uHsyncBackPorchInPixels +
                                          psPanelInfo->uHsyncPulseInPixels;
          sTUSizeParam.uOriginalhbp     = psPanelInfo->uHsyncFrontPorchInPixels +
                                          psPanelInfo->uHsyncBackPorchInPixels +
                                          psPanelInfo->uHsyncPulseInPixels;
          sTUSizeParam.dLinkClockInMhz  = sPixClkInfo.dActualLinkClkMHz;
          sTUSizeParam.dPixelClockInMhz = (double)pStreamCtx->uPixelClkInKhz / 1000;
          sTUSizeParam.dActualLinkClk   = sPixClkInfo.dActualLinkClkMHz;
          sTUSizeParam.dActualPixelClk  = (double)sPixClkInfo.dActualPixelClkMHz;
          sTUSizeParam.bSynchronousClk  = pDeviceCtx->bSynchronousClk;

          // All the modes with horizontal blanking period less than 160 pixels are 
          // to be considered as RB2 for TU Calculation
          if (sTUSizeParam.uOriginalhbp < 160)
          {
            sTUSizeParam.bRB2Timing = TRUE;
          }
          else
          {
            sTUSizeParam.bRB2Timing = FALSE;
          }


          //adjust parameters for DSC and FEC for SST case
          if (TRUE == pStreamCtx->sDSCInfo.bDSCEnabled)
          {
            sTUSizeParam.bDSCEnabled      = TRUE;
            sTUSizeParam.dPixelClockInMhz = (double)pStreamCtx->sDSCInfo.uDSCPixelClkInKhz/1000;
            sTUSizeParam.uWidth           = pStreamCtx->sDSCInfo.uDSCWidth;
            sTUSizeParam.dHBlankPeriod    = pStreamCtx->sDSCInfo.dDSCHBlankPeriod;
            sTUSizeParam.uBPP             = 24;
          }

          if (TRUE == pDeviceCtx->bFECEnabled)
          {
            sTUSizeParam.bFECEnabled      = TRUE;
            sTUSizeParam.dLinkClockInMhz  = DP_LINKRATE_FEC_OVERHEAD_RATIO * sPixClkInfo.dActualLinkClkMHz;
          }

          // For SST calculate TU
          eStatus = DP_CalculateTU(&sTUSizeParam, &sHALTuConfig);

          if (DP_STATUS_SUCCESS != eStatus)
          {
            // DP_CalculateTU should not fail for valid link/pclk rates
            // In case it does, just log error and continue
            DP_LOG_MESSAGE_ERROR("DP_Host_SetMode: Calculate TU failed, status=%d", eStatus);  
          }
        }
        else
        {
          sRGCalcParam.eDisplayId       = pStreamCtx->eDisplayID;
          sRGCalcParam.uBPP             = pStreamCtx->uBitDepth * DP_NUM_COLOR_COMPONENTS;
          sRGCalcParam.uNumberOfLanes   = pDeviceCtx->uNumLanes;
          sRGCalcParam.uVisWidth        = psPanelInfo->uVisibleWidthInPixels;
          sRGCalcParam.dLinkClockInMhz  = sPixClkInfo.dActualLinkClkMHz;
          sRGCalcParam.uPixelClockInKhz = pStreamCtx->uPixelClkInKhz;
          sRGCalcParam.bSynchronousClk  = pDeviceCtx->bSynchronousClk;

          // Adjust parameters for DSC and FEC for  MST case
          if (TRUE == pStreamCtx->sDSCInfo.bDSCEnabled)
          {
            sRGCalcParam.bDSCEnabled  = TRUE;
            sRGCalcParam.uBPP         = (uint32)Ceilf(sRGCalcParam.uBPP / pStreamCtx->sDSCInfo.uCompressionRatio);
            sRGCalcParam.fDSCOverHead = pStreamCtx->sDSCInfo.fDSCOverheadRatio;
          }

          if (TRUE == pDeviceCtx->bFECEnabled)
          {
            sRGCalcParam.bFECEnabled = TRUE;
          }

          // Calculate RG for MST
          if (DP_STATUS_SUCCESS == (eStatus = DP_CalculateRG(&sRGCalcParam, &sHALRgConfig)))
          {
            sVCInfo.bAllocate          = TRUE;
            sVCInfo.uRequiredPBN       = sHALRgConfig.uPBN;
            sVCInfo.uRequiredTimeSlots = sHALRgConfig.uSlotCount;
          }
          else
          {
            // DP_CalculateRG should not fail for valid link/pclk rates
            // In case it does, just log error and continue
            DP_LOG_MESSAGE_ERROR("DP_Host_SetMode: Calculat RG failed, status=%d", eStatus);  
          }
        }

        /* Filter out audio modes that don't fit within the bandwidth available for the current link configuration */
        if (DP_STATUS_SUCCESS != DP_Audio_FilterModes(pDisplayCtx, psPanelInfo, &sHALRgConfig))
        {
          TraceInfo(QdiTraceDP, "DP%d: Audio mode filtering failed, discarding all audio modes", pStreamCtx->eDisplayID);

          // Audio mode filtering failed; discard all audio modes 
          for (uAudioStreamIndex = 0; uAudioStreamIndex < pStreamCtx->uNumberOfAudioModes; uAudioStreamIndex++)
          {
            pStreamCtx->sAudioModeInfo[uAudioStreamIndex].uSupportedAudioSampleRateMask = 0;
            pStreamCtx->sAudioModeInfo[uAudioStreamIndex].uSupportedAudioChannelMask    = 0;
          }
        }

        // PHY needs to be initialized only once for MST stream
        // TODO: whenever the link need to be reconfigured, this need to be FALSE again.
        if (FALSE == pDeviceCtx->bLinkConfigured)
        {
          HAL_DP_PllConfigType   sPhyConfig;
          bool32                 bPHYConfigResult;

          DP_OSAL_MemSet((void *)&sPhyConfig, 0, sizeof(HAL_DP_PllConfigType));

          /* Set up PHY PLL */
          sPhyConfig.uNumLanes                 = pDeviceCtx->uNumLanes;      
          sPhyConfig.uLinkRateMbps             = (pDeviceCtx->uLinkRateInKhz / 1000) * DP_LINK_SYMBOL_SIZE;   // symbol size = 10 bits
          sPhyConfig.uPixelClkMNDInputMhz      = sPixClkInfo.uPixelClkMNDInputMhz;
          sPhyConfig.uPreemphasisLevel         = pDeviceCtx->uPreEmphasisLevel;
          sPhyConfig.uVoltSwingLevel           = pDeviceCtx->uVoltageSwingLevel;
          sPhyConfig.bInvertedPlug             = pDeviceCtx->bInvertedPlug;
          sPhyConfig.bReversePhyDataPath       = DP_PhyDataPathIsReverse(pDisplayCtx);
        
          if ((MDP_DP_SSC_ENABLED_DOWNSPREAD == pDeviceCtx->eSSCMode) &&
              (DP_DPCD_CAP_MAX_DOWNSPREAD_0_5 & pDeviceCtx->sSinkDPCDCap.eDPCDCap))
          {
            sPhyConfig.uFlags              |= HAL_DP_PLLCONFIG_FLAG_SSC;
          }
  
          if (GetConcurrencyMode(pDeviceCtx))
          {
            sPhyConfig.uFlags              |= HAL_DP_PLLCONFIG_FLAG_DPUSB_CONCURRENCY;
          }
          
          // Log start of PHY and PLL enable
          DISP_OSAL_EVENTLOG3(DISP_OSAL_EVENT_PLLPROGRAMMING_START, pDeviceCtx->eDeviceID, 0, (DP_PHY_POWER_PHY | DP_PHY_POWER_PLL));

          if (FALSE == (bPHYConfigResult = HAL_DP_PHY_Config(pDeviceCtx->eDeviceID, &sPhyConfig, pDeviceCtx->eDeviceDPMode)))
          {
            DP_LOG_MESSAGE_ERROR("DP%d: DP_Host_SetMode: Setup of PHY PLL failed\n", pStreamCtx->eDisplayID);      
            eStatus = DP_STATUS_FAIL;
            goto exit;
          }

          // Log end of PHY and PLL enable
          DISP_OSAL_EVENTLOG3(DISP_OSAL_EVENT_PLLPROGRAMMING_END, pDeviceCtx->eDeviceID, bPHYConfigResult, (DP_PHY_POWER_PHY | DP_PHY_POWER_PLL));

          // Setup required for external PLL in bonded mode, if the clock has not been configured yet
          if (0 == UpdateSourceClockRefCount(pDeviceCtx, 0))
          {
            // Disable SSC on externally sourced pixel clock
            sPhyConfig.uFlags &= ~HAL_DP_PLLCONFIG_FLAG_SSC;

            sPhyConfig.uFlags |= HAL_DP_PLLCONFIG_FLAG_PLL;

            if (DP_STATUS_SUCCESS != (eStatus = ConfigureExternalSourceClock(pDeviceCtx, &sPhyConfig, TRUE)))
            {
              DP_LOG_MESSAGE_ERROR("DP%d: DP_Host_SetMode: Setup of external PLL failed\n", pStreamCtx->eDisplayID);
              goto exit;
            }
          }
          
          // Set up external clock source and dividers for all the main link clocks
          if(DP_STATUS_SUCCESS != (eStatus = DP_LinkClockEnable(pDisplayCtx, TRUE)))
          {
            DP_LOG_MESSAGE_ERROR("DP_Host_SetMode: Failed to configure main link clocks ");
            goto exit;
          }

          // Set the DPTX link interface in native DP mode
          HAL_DP_ConfigureLinkInterfaceMode(pDeviceCtx->eControllerID, FALSE);
          
        }

        if ((TRUE == bLinkTrainingRequired) && 
            (FALSE == DPHOST_CHECK_DP_TUNNELING_MODE(pDeviceCtx)))
        {
          HAL_MDSS_ErrorType ePHYPowerResult;

          /* Reset Phy re-timing buffer */
          if (HAL_MDSS_STATUS_SUCCESS != (ePHYPowerResult = HAL_DP_PHY_Power(pDeviceCtx->eDeviceID, FALSE, DP_PHY_POWER_PHY_TIMING_FIFO)))
          {
            DP_LOG_MESSAGE_ERROR("DP%d: Failed to disable re-timing buffer with error=%d in DP_Host_SetMode.\n",
                                 pStreamCtx->eDisplayID,
                                 ePHYPowerResult);
          }

          if (HAL_MDSS_STATUS_SUCCESS != (ePHYPowerResult = HAL_DP_PHY_Power(pDeviceCtx->eDeviceID, TRUE, DP_PHY_POWER_PHY_TIMING_FIFO)))
          {
            DP_LOG_MESSAGE_ERROR("DP%d: Failed to enable re-timing buffer with error=%d in DP_Host_SetMode.\n",
                                 pStreamCtx->eDisplayID,
                                 ePHYPowerResult);
          }
        }

        /* Set DSC configuration in default state */
        if (DP_STATUS_SUCCESS != (eStatus = DP_DSC_ConfigureSource(pDisplayCtx, FALSE)))
        {
          DP_LOG_MESSAGE_ERROR("DP_Host_SetMode: DP_DSC_ConfigureSource failed.");
          goto exit;
        }

        /* If the link is not configured or we are in SST mode then do link training, write link configuration to the sink DPCD.
           Skip writing link settings, if panel is not detected.
         */
        if (TRUE == bLinkTrainingRequired)
        {
          /* Disable FEC; not disabling FEC results in link training failing. */
          HAL_DP_SetFECConfig(pDeviceCtx->eControllerID, FALSE, DPHOST_CHECK_DP_TUNNELING_MODE(pDeviceCtx));

          /* Check whether valid LTTPR present */
          if (DP_IsValidLTTPR(pDisplayCtx))
          {
            // Limit the link rate and number of lanes by the repeater cap
            pDeviceCtx->sSinkDPCDCap.uMaxLaneCount     = DP_MIN(pDeviceCtx->sSinkDPCDCap.uMaxLaneCount , pDeviceCtx->sLTTPRCaps.uMaxLaneCount);
            pDeviceCtx->uNumLanes                      = DP_MIN(pDeviceCtx->uNumLanes, pDeviceCtx->sSinkDPCDCap.uMaxLaneCount);
            pDeviceCtx->sSinkDPCDCap.uMaxLinkRateInKhz = DP_MIN(pDeviceCtx->sSinkDPCDCap.uMaxLinkRateInKhz , pDeviceCtx->sLTTPRCaps.uMaxLinkRate);
            pDeviceCtx->uLinkRateInKhz                 = DP_MIN(pDeviceCtx->uLinkRateInKhz, pDeviceCtx->sSinkDPCDCap.uMaxLinkRateInKhz);

            // Check whether LTTPR custom sink
            pDeviceCtx->eCustomSinkType = DP_IdentifyCustomSink(pDisplayCtx,
                                                                DP_SINKCLASS_REPEATER,
                                                                DP_DEVICE_IDENTIFIER_STRING_LEN);

            if ((DP_CUSTOM_SINKID_NONE != pDeviceCtx->eCustomSinkType) &&
                (DP_STATUS_SUCCESS != DP_WriteCustomLTTPRInitSequence(pDisplayCtx, pDeviceCtx->eCustomSinkType)))
            {
              DP_LOG_MESSAGE_ERROR("DP%d: Failed to configure custom LTTPR init sequence", pDeviceCtx->eControllerID);
            }
          }
          
          /* Write to link/lane count setting DPCD registers; internal registers in tunneling mode */
          if (DP_STATUS_SUCCESS != DP_WriteSinkDPCDLink(pDisplayCtx))
          {
            DP_LOG_MESSAGE_ERROR("DP_Host_SetMode: Failed to write link settings to panel DPCD ");       
            eStatus = DP_STATUS_FAIL;
            goto exit;
          }
          else if ((MDP_DP_SSC_ENABLED_DOWNSPREAD == pDeviceCtx->eSSCMode) &&
                   (DP_DPCD_CAP_MAX_DOWNSPREAD_0_5 & pDeviceCtx->sSinkDPCDCap.eDPCDCap) &&
                   (DP_STATUS_SUCCESS != DP_WriteSinkDPCDDownSpreadEnabled(pDisplayCtx)))
          {
            DP_LOG_MESSAGE_ERROR("DP_Host_SetMode: Failed to write SSC settings to panel DPCD ");
            eStatus = DP_STATUS_FAIL;
            goto exit;
          }
        }

        /* Enable ASSR mode in sink device if supported */
        if ((DP_DEVICE_MODETYPE_EDP == pDeviceCtx->eDeviceDPMode) &&
            (0 != (pDeviceCtx->sSinkDPCDCap.eDPCDCap & DP_DPCD_CAP_SUPPORT_ASSR)))
        {
          if (DP_STATUS_SUCCESS == DP_WriteSinkASSREnable(pDisplayCtx, TRUE))
          {
            bASSR = TRUE;    // set flag to indicate that ASSR needs to be enabled on source as well
          }    
        }

        /* Configure link configuration on host side */   
    
        /* Set Lane mapping based on USB Type-C plug polarity */
        sSinkAttrib.eLaneMapping     = pDeviceCtx->uLaneMapping;
        sSinkAttrib.ePixelFormat     = HAL_DP_PIXELFORMAT_TYPE_RGB;
        sSinkAttrib.eRGBMapping      = HAL_DP_RGBMAP_TYPE_RGB;
        sSinkAttrib.uBitPerComponent = DPHOST_GETPIXELFMT(psPanelInfo->eColorFormat).uBitsPerComponent;
        sSinkAttrib.uLaneNumber      = pDeviceCtx->uNumLanes;
        sSinkAttrib.uStreamId        = pStreamCtx->eMSTStreamId;
        HAL_DP_SetSinkAttrib(pDeviceCtx->eControllerID, &sSinkAttrib);

        if (FALSE == pDeviceCtx->bMSTEnabled)
        {
          // COnfigure TU for SST
          HAL_DP_SetTUConfig(pDeviceCtx->eControllerID, &sHALTuConfig); 
        }
        else
        {
          // Configure RG for MST
          HAL_DP_SetRGConfig(pDeviceCtx->eControllerID, pStreamCtx->eMSTStreamId, &sHALRgConfig);
        }

        sStreamAttrib.bSynchronousClk  = pDeviceCtx->bSynchronousClk;
        sStreamAttrib.bEnhancedFraming = pDeviceCtx->sSinkDPCDCap.eDPCDCap & DP_DPCD_CAP_SUPPORT_ENHANCED_FRAME;
        sStreamAttrib.bASSR            = bASSR;
        sStreamAttrib.bInterlaced      = psPanelInfo->bInterlaced;
        HAL_DP_SetStreamAttrib(pDeviceCtx->eControllerID, &sStreamAttrib);

        /* Set Main stream attributes on host side */
        sHALMSAPacket.uSWMVid                  = sPixClkInfo.uSWMvid;
        sHALMSAPacket.uSWNVid                  = sPixClkInfo.uSWNvid;  
        sHALMSAPacket.uVisibleWidthInPixels    = psPanelInfo->uVisibleWidthInPixels; 
        sHALMSAPacket.uVisibleHeightInPixels   = psPanelInfo->uVisibleHeightInPixels; 
        sHALMSAPacket.uHsyncBackPorchInPixels  = psPanelInfo->uHsyncBackPorchInPixels; 
        sHALMSAPacket.uHsyncFrontPorchInPixels = psPanelInfo->uHsyncFrontPorchInPixels; 
        sHALMSAPacket.uHsyncPulseInPixels      = psPanelInfo->uHsyncPulseInPixels;
        sHALMSAPacket.uHsyncSkewInPixels       = psPanelInfo->uHsyncSkewInPixels;
        sHALMSAPacket.uVsyncBackPorchInLines   = psPanelInfo->uVsyncBackPorchInLines; 
        sHALMSAPacket.uVsyncFrontPorchInLines  = psPanelInfo->uVsyncFrontPorchInLines; 
        sHALMSAPacket.uVsyncPulseInLines       = psPanelInfo->uVsyncPulseInLines;
        sHALMSAPacket.uHLeftBorderInPixels     = psPanelInfo->uHLeftBorderInPixels; 
        sHALMSAPacket.uHRightBorderInPixels    = psPanelInfo->uHRightBorderInPixels;
        sHALMSAPacket.uVTopBorderInLines       = psPanelInfo->uVTopBorderInLines; 
        sHALMSAPacket.uVBottomBorderInLines    = psPanelInfo->uVBottomBorderInLines;
        sHALMSAPacket.bHSyncActiveLow          = psPanelInfo->bHSyncActiveLow;
        sHALMSAPacket.bVSyncActiveLow          = psPanelInfo->bVSyncActiveLow;
        sHALMSAPacket.uMisc0                   = DP_CalculateMisc0(psPanelInfo->eColorFormat);
        sHALMSAPacket.uMisc1                   = 0;
        sHALMSAPacket.uStreamId                = pStreamCtx->eMSTStreamId;

        if (TRUE == pDeviceCtx->bSynchronousClk)
        {
          sHALMSAPacket.uMisc0                |= DP_SPEC_MSA_MISCO_SYNC_CLK_BMSK;
        }
        
        if (DP_RX_FEATURE_VSC_SDP_COLORIMETRY & pDeviceCtx->sSinkDPCDCap.eRxFeatureEnumList)
        {
          // Set bit 6 to make sink listen for VSC packet when VSC SDP is supported by the sink
          sHALMSAPacket.uMisc1 = 0x1 << 6;
        }

        HAL_DP_SetMSA(pDeviceCtx->eControllerID, &sHALMSAPacket);

        // Enable MST on controller side
        HAL_DP_MST_Enable(pDeviceCtx->eControllerID, pDeviceCtx->bMSTEnabled);

        // Perform stream specific MST enable
        HAL_DP_MST_Stream_Enable(pDeviceCtx->eControllerID, (DP_StreamIDType)pStreamCtx->eMSTStreamId, pDeviceCtx->bMSTEnabled); 
        
        /* Enable Main link */ 
        HAL_DP_Mainlink_Enable(pDeviceCtx->eControllerID, TRUE); 

        /* Clear mainlink state before a SW reset */
        HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_NONE);

        /* SW Reset DP mainlik HW */
        HAL_DP_Reset(pDeviceCtx->eControllerID, HAL_DP_MODULE_TYPE_MAINLINK, 0);

        /* If the link is not configured or we are in SST mode then do link training. */
        if (TRUE == bLinkTrainingRequired)
        {
          DP_LinkTrainingType eLinkTraining                 = DP_LINK_TRAINING_TYPE_NO_TRAINING;
          uint32              uHBR2ComplianceScramblerReset = 0;
          uint32              uIdlePatternRepNum            = DEFAULT_DP_IDLE_PATTERN_REP_NUM;
          uint32              uSafeToExitLevel              = DEFAULT_DP_SAFE_TO_EXIT_LEVEL;
          bool32              bBypassLaneSkew               = FALSE;
          bool32              bBypassScrambler              = FALSE;
          bool32              bBypass8B10B                  = FALSE;
          bool32              bBypassFECRS                  = FALSE;

          HAL_DP_OptionalType sDPOptionCfg;
          
          /* Clear HBR2 ERM configuration back to default */
          DP_OSAL_MemSet(&sDPOptionCfg, 0, sizeof(HAL_DP_OptionalType));
          sDPOptionCfg.puHBR2ComplianceScramblerReset = &uHBR2ComplianceScramblerReset;
          sDPOptionCfg.puIdlePatternRepNum            = &uIdlePatternRepNum;
          sDPOptionCfg.puSafeToExitLevel              = &uSafeToExitLevel;
          sDPOptionCfg.pbBypassLaneSkew               = &bBypassLaneSkew;
          sDPOptionCfg.pbBypassScrambler              = &bBypassScrambler;
          sDPOptionCfg.pbBypass8B10B                  = &bBypass8B10B;
          sDPOptionCfg.pbBypassFECRS                  = &bBypassFECRS;

          HAL_DP_SetOptionalConfig(pDeviceCtx->eControllerID, &sDPOptionCfg);

          // For normal video mode, use the link training specified in the device context
          if (pDeviceCtx->ePhyTestPattern == DP_PHY_TEST_PATTERN_NONE)
          {
            eLinkTraining = pDeviceCtx->eLinkTrainingType;
          }

          // If valid repeater is detected in non-transparent mode, we need to perform manual training across all repeaters
          if ((DP_IsValidLTTPR(pDisplayCtx)) &&
                (DPCD_SPEC_LTTPR_NON_TRANSPARENT_MODE == pDeviceCtx->sLTTPRCaps.uRepeaterMode))
          {
            uint32 uCount;
                          
            // DP Link Training in LTTPR mode, train from repeater closes to DPTX down to DPRX
            for (uCount=pDeviceCtx->sLTTPRCaps.uRepeaterCount; uCount > 0; uCount--)
            {
              // Cast directly to the repeater ID
              pDeviceCtx->eLTTPRRepeaterID = (DP_LTTPR_RepeaterIDType)uCount;

              if (DP_STATUS_SUCCESS != DP_ReadLTTPRCETrainingInterval(pDisplayCtx))
              {
                TraceInfo(QdiTraceDP,"DP%d: Failed to read LTTPR CE training interval on repeater #%d. Set to default CE interval",
                                     pStreamCtx->eDisplayID,
                                     uCount);
              }

              if (DP_STATUS_SUCCESS != (eStatus = DP_LinkTraining(pDisplayCtx, eLinkTraining, 0)))
              {
                DP_LOG_MESSAGE_ERROR("DP%d: DP_Host_SetMode: Failed LTTPR training on repeater #%d",
                                      pStreamCtx->eDisplayID,
                                      uCount);
                break;
              }
            }
          }
          
          // DP Link Training with Rx
          if (DP_STATUS_SUCCESS == eStatus)
          {
            // Clear Repeater ID
            pDeviceCtx->eLTTPRRepeaterID = DP_LTTPR_NO_REPEATER;

            eStatus = DP_LinkTraining(pDisplayCtx, eLinkTraining, 0);
          }

          if (DP_STATUS_SUCCESS == eStatus)
          { 
            if (DP_STATUS_SUCCESS != (eStatus = VerifyLinkBandwidth(pDisplayCtx)))
            {
              // Indicate that EDID needs to be reparsed
              pStreamCtx->bEDIDObtained = FALSE;
              goto exit;
            }

            pDeviceCtx->bLinkConfigured = TRUE;

            TraceInfo(QdiTraceDP, "DP%d: Link Training Done, %dMbps with %d lanes",
                                   pStreamCtx->eDisplayID,
                                   (pDeviceCtx->uLinkRateInKhz / 1000) * 10,
                                   pDeviceCtx->uNumLanes);

            break;
          }
          else
          {
            if (DP_STATUS_SUCCESS != (eStatus = DP_LinkLaneReduction(pDisplayCtx)))
            {
              TraceInfo(QdiTraceDP, "DP%d: Exhausted all lane and rate combinations, unable to find a suitable link configuration",
                                     pStreamCtx->eDisplayID);
              goto exit;
            }
          }
        }
        else
        {
          // Link was already trained.
          break;
        }
      }
	  
      // Push Idle Patterns, to avoid any underflow condition.
      ConfigureMainLink(pDisplayCtx, DP_LINKCOMMAND_TYPE_PUSH_IDLE);
      
      // Start Video
      ConfigureMainLink(pDisplayCtx, DP_LINKCOMMAND_TYPE_SEND_VIDEO);

      /* Set up external clock source and dividers for the pixel clock */
      if (DP_STATUS_SUCCESS != (eStatus = DP_PixelClockEnable(pDisplayCtx, &sPixClkInfo, TRUE)))
      {
        DP_LOG_MESSAGE_ERROR("DP_Host_SetMode: Failed to configure pixel clock.");
        goto exit;
      }

      /* Setup MDP Backpressure to enable data flow */
      HAL_DP_SetBackPressure(pDeviceCtx->eControllerID, (DP_StreamIDType)pStreamCtx->eMSTStreamId, TRUE);

      if (DP_STATUS_SUCCESS != DP_WaitForLinkStatus(pDisplayCtx, HAL_DP_LINKSTATUS_TYPE_READY_FOR_VIDEO))
      {
        // If this video send command fails, we may get corrupted or no content at all
        TraceInfo(QdiTraceDP, "DP%d: Failed to start video", pStreamCtx->eDisplayID);
        eStatus = DP_STATUS_FAIL;
        goto exit;
      }

      // Enable test patterns after link is up and stable (ready for video state)
      if (DP_TEST_PHY_PATTERN == pDeviceCtx->ePendingTestRequest)
      {
        SetPHYTestPattern(pStreamCtx->eDisplayID, pDeviceCtx->eControllerID, pDeviceCtx->ePhyTestPattern);
      }
      else if (DP_TEST_EDID_READ == pDeviceCtx->ePendingTestRequest)
      {
        if (DP_STATUS_SUCCESS != (eStatus = DP_WriteTestResponse(pDisplayCtx)))
        {
          DP_LOG_MESSAGE_WARN("DP_HPDHandleThread: DP_WriteTestResponse Failed, eStatus = %d.", eStatus);
        }
      }

      // Configure FEC, and DSC after ReadyForVideo is set
      if (DP_STATUS_SUCCESS != (eStatus = SetModeDSCConfig(pDisplayCtx, bLinkTrainingRequired)))
      {
        TraceInfo(QdiTraceDP, "DP%d: Failed to configure DSC", pStreamCtx->eDisplayID);
        goto exit;
      }

      // Increment pixel clock source ref count, for shared resource bookkeeping in bonded mode. 
      UpdateSourceClockRefCount(pDeviceCtx, 1);

      TraceInfo(QdiTraceDP, "DP%d: Main link setup [link_rate: %d Mbps, lanes: %d, mode: %dx%d @ %dHz]",
                             pStreamCtx->eDisplayID,
                             (pDeviceCtx->uLinkRateInKhz / 1000) * 10, 
                             pDeviceCtx->uNumLanes,
                             psPanelInfo->uVisibleWidthInPixels, 
                             psPanelInfo->uVisibleHeightInPixels,
                             psPanelInfo->uPclkFreq); 
    } 
  } 
  
exit:
  return eStatus;  
}

/*********************************************************************************************
*
** FUNCTION: DP_Host_Set_RefreshRate()
*/
/*!
* \DESCRIPTION
*     Set selected display mode
*
* \param [in]   pDeviceCtx        - Pointer to device context
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_Host_Set_RefreshRate(DP_DisplayCtxType    *pDisplayCtx,
                                   uint32                uModeIndex)
{
  DP_DeviceCtxType       *pDeviceCtx   = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType       *pStreamCtx   = DPHOST_GET_STREAM_CTX(pDisplayCtx);
  DP_Status               eStatus      = DP_STATUS_SUCCESS;

  if ((NULL == pStreamCtx) ||
      (NULL == pDeviceCtx))
  {
    DP_LOG_MESSAGE_ERROR("DP_Host_Set_RefreshRate: unexpected null handle ");
    eStatus = DP_STATUS_FAILED_DRIVER_NOT_INITIALIZED;
  }
  else if (DP_HOST_MODE_INVALID == uModeIndex)
  {
    TraceInfo(QdiTraceDP, "DP%d: DP_Host_Set_RefreshRate, invalid mode set", pStreamCtx->eDisplayID);
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else 
  {
    DP_PanelInfoType          *psPanelInfo  = &(pStreamCtx->sPanelInfo[uModeIndex]);
    HAL_DP_MSAPacketType       sHALMSAPacket;
    DP_PixelClk_Info           sPixClkInfo;

    DP_OSAL_MemSet((void *)&sHALMSAPacket, 0, sizeof(HAL_DP_MSAPacketType));
    DP_OSAL_MemSet((void *)&sPixClkInfo, 0, sizeof(DP_PixelClk_Info));

    /* Default to max supported lane link rate and lane number from DPCD if they are not set by DP_Host_SetProperty for mode changing. 
       The values could have been changed by previous SetMode when link training failure and reduce link rate */

    /* This is needed explicitly for bootup-case as SetMode is not called for regular bootup */
    if (0 == (pStreamCtx->uDirtyBits & DP_DIRTYFIELD_LINK_RATE))
    {
      pDeviceCtx->uLinkRateInKhz = pDeviceCtx->sSinkDPCDCap.uMaxLinkRateInKhz;
    }

    if (0 == (pStreamCtx->uDirtyBits & DP_DIRTYFIELD_LANE_NUMBER))
    {
      pDeviceCtx->uNumLanes = pDeviceCtx->sSinkDPCDCap.uMaxLaneCount;
    }

    /* Calculate all the link settings */
    if (DP_STATUS_SUCCESS != DP_CalculateLink(pDisplayCtx, &pDeviceCtx->sSinkDPCDCap, psPanelInfo, &sPixClkInfo))
    {
      DP_LOG_MESSAGE_ERROR("DP_Host_Set_RefreshRate: Failed to calculate link settings ");    
      eStatus = DP_STATUS_FAIL;
    }
    else 
    {
      /* Set Main stream attributes on host side */
      sHALMSAPacket.uSWMVid                  = sPixClkInfo.uSWMvid;
      sHALMSAPacket.uSWNVid                  = sPixClkInfo.uSWNvid;  
      sHALMSAPacket.uVisibleWidthInPixels    = psPanelInfo->uVisibleWidthInPixels; 
      sHALMSAPacket.uVisibleHeightInPixels   = psPanelInfo->uVisibleHeightInPixels; 
      sHALMSAPacket.uHsyncBackPorchInPixels  = psPanelInfo->uHsyncBackPorchInPixels; 
      sHALMSAPacket.uHsyncFrontPorchInPixels = psPanelInfo->uHsyncFrontPorchInPixels; 
      sHALMSAPacket.uHsyncPulseInPixels      = psPanelInfo->uHsyncPulseInPixels;
      sHALMSAPacket.uHsyncSkewInPixels       = psPanelInfo->uHsyncSkewInPixels;
      sHALMSAPacket.uVsyncBackPorchInLines   = psPanelInfo->uVsyncBackPorchInLines; 
      sHALMSAPacket.uVsyncFrontPorchInLines  = psPanelInfo->uVsyncFrontPorchInLines; 
      sHALMSAPacket.uVsyncPulseInLines       = psPanelInfo->uVsyncPulseInLines;
      sHALMSAPacket.uHLeftBorderInPixels     = psPanelInfo->uHLeftBorderInPixels; 
      sHALMSAPacket.uHRightBorderInPixels    = psPanelInfo->uHRightBorderInPixels;
      sHALMSAPacket.uVTopBorderInLines       = psPanelInfo->uVTopBorderInLines; 
      sHALMSAPacket.uVBottomBorderInLines    = psPanelInfo->uVBottomBorderInLines;
      sHALMSAPacket.bHSyncActiveLow          = psPanelInfo->bHSyncActiveLow;
      sHALMSAPacket.bVSyncActiveLow          = psPanelInfo->bVSyncActiveLow;
      sHALMSAPacket.uMisc0                   = DP_CalculateMisc0(psPanelInfo->eColorFormat);

      if (TRUE == pDeviceCtx->bSynchronousClk)
      {
        sHALMSAPacket.uMisc0                |= DP_SPEC_MSA_MISCO_SYNC_CLK_BMSK;
      }
      sHALMSAPacket.uMisc1                   = 0;
      sHALMSAPacket.uStreamId                = pStreamCtx->eMSTStreamId;

      HAL_DP_SetMSA(pDeviceCtx->eControllerID, &sHALMSAPacket);
    }
  }
  
  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_Host_QueryPanelInfo()
*/
/*!
* \DESCRIPTION
*     Query EDID/DPCD info from panel
*
* \param [in]   hHandle           - Handle to DP device
* \param [in]   puNumStreams      - Number of MST streams supported for this device
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status DP_Host_QueryPanelInfo(DP_HandleType  hHandle, 
                                 uint32        *puNumStreams)
{
  DP_Status                  eStatus        = DP_STATUS_SUCCESS; 
  DP_DisplayCtxType         *pDisplayCtx    = DPHOST_GETCTX_FROM_HANDLE(hHandle); 
  DP_DeviceCtxType          *pDeviceCtx     = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType          *pStreamCtx     = DPHOST_GET_STREAM_CTX(pDisplayCtx); 

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx))
  {
    DP_LOG_MESSAGE_ERROR("DP_Host_QueryPanelInfo: Unexpected null handle ");
    eStatus = DP_STATUS_FAILED_DRIVER_NOT_INITIALIZED;
  }
  else
  { 
    if ((0 != DPHOST_GETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_ALT_MODE_FIXED_LANE_CONFIGURATION)) &&
        (TRUE == IsAltModeDPDevice(pDeviceCtx->eDeviceID)))
    {
      /* Set GPIO for AUX polarity if it is DP over USB TypeC */
      DP_ConfigureGPIOState(pDisplayCtx, DP_GPIO_RESOURCE_AUX_POLARITY_SEL, 0);
      
      /* Set GPIO for AUX switch select if it is DP over USB TypeC */
      DP_ConfigureGPIOState(pDisplayCtx, DP_GPIO_RESOURCE_AUX_SWITCH_SEL, 0);
    }

    if (0 == pDeviceCtx->uNumActiveStreams)
    {
      if (DP_STATUS_SUCCESS != (eStatus = DP_WriteSinkDPCDPower(pDisplayCtx, DP_DPCD_POWERSTATE_D0)))
      {
        TraceInfo(QdiTraceDP, "DP%d: Failed to Set Sink Device to D0 state", pStreamCtx->eDisplayID);
        eStatus = DP_STATUS_FAIL;
      }
      else if (DP_STATUS_SUCCESS != (eStatus = DP_ReadSinkDPCDCap(pDisplayCtx)))
      {
        TraceInfo(QdiTraceDP, "DP%d: Failed to Read DPCD info from Sink Device", pStreamCtx->eDisplayID);
      } 
      else if (DP_STATUS_SUCCESS != (eStatus = DP_ReadSinkStatus(pDisplayCtx)))
      {
        TraceInfo(QdiTraceDP, "DP%d: Failed to Read Sink status", pStreamCtx->eDisplayID);
      }
      else if ((pDeviceCtx->sSinkDPCDCap.eDPCDCap & DP_DPCD_CAP_DWN_STRM_PORT_PRESENT) && 
               (0 == pDeviceCtx->uSinkCount))
      {
        TraceInfo(QdiTraceDP, "DP%d: Sink removed while querying DPCD", pStreamCtx->eDisplayID);
        eStatus = DP_STATUS_FAIL;
      }
      else
      {
        // Pin assignment info from USB indicates a lane number, this lane number may not match with DPCP reported lane number
        pDeviceCtx->sSinkDPCDCap.uMaxLaneCount = FilterLanesByPinAssignment(pDeviceCtx->eDeviceID, pDeviceCtx->ePinAssignment, pDeviceCtx->sSinkDPCDCap.uMaxLaneCount);

        if (pDeviceCtx->sSourceOverrideCaps.uMaxLinkRateInKHz)
        {
          if (pDeviceCtx->sSourceOverrideCaps.uMaxLinkRateInKHz < pDeviceCtx->sSinkDPCDCap.uMaxLinkRateInKhz)
          {
            TraceInfo(QdiTraceDP, "DP%i: Link rate capped to %d", pStreamCtx->eDisplayID, pDeviceCtx->sSourceOverrideCaps.uMaxLinkRateInKHz);
          }

          pDeviceCtx->sSinkDPCDCap.uMaxLinkRateInKhz = DPHOST_MIN(pDeviceCtx->sSinkDPCDCap.uMaxLinkRateInKhz, pDeviceCtx->sSourceOverrideCaps.uMaxLinkRateInKHz);          
        }
      }
    }

    if (DP_STATUS_SUCCESS == eStatus)
    {
      if ((0 == (DP_CAPS_MST & pDeviceCtx->eCapabilityMask)) ||
          (DP_HOST_FLAG_DISABLE_MST & pDeviceCtx->uFlags) ||
          (FALSE == pDeviceCtx->sSinkDPCDCap.bMSTCapable))
      {
        /* SST case: Stream 0 is connected if we received valid results from DPCD. Stream 1 is disabled. */
        pStreamCtx->bSinkConnected = (DP_MST_STREAM_ID_0 == pStreamCtx->eMSTStreamId) ? TRUE : FALSE;

        if (TRUE == pDeviceCtx->sSinkDPCDCap.bMSTCapable)
        {
          /* Reset the mode back to SST on initialization. */
          if ( DP_STATUS_SUCCESS == DP_WriteSinkMSTEnable(pDisplayCtx, FALSE))
          {
            TraceInfo(QdiTraceDP, "DP%d: Cleared MST mode control to 0",pDeviceCtx->eDisplayID);
          }
        }
      }

      /* Only proceed to read stream related information if it is connected */
      if (TRUE == pStreamCtx->bSinkConnected)
      { 
        /* Read DSC capabilities  
         * Commenting out to avoid AUX failures on HA during bringup
         * Will re-enable after debug.
         *
        if (DP_STATUS_SUCCESS != (eStatus = DP_DSC_QueryInfo(pDisplayCtx)))
        {
          TraceInfo(QdiTraceDP, "DP%d: Failed to Read DSC info", pStreamCtx->eDisplayID);
        }

        * Read FEC capabilities 
        if (DP_STATUS_SUCCESS != (eStatus = DP_FEC_QueryInfo(pDisplayCtx)))
        {
          TraceInfo(QdiTraceDP, "DP%d: Failed to Read FEC info", pStreamCtx->eDisplayID);
        }
        */

        /* Read EDID */
        if ((DP_STATUS_SUCCESS != (eStatus = ReadModeInfoFromSink(pDisplayCtx))))
        {
          TraceInfo(QdiTraceDP, "DP%d: Failed to get any display modes from EDID of Sink Device", pStreamCtx->eDisplayID);
        }

        /* Read Brightness Caps */
        if ((DP_STATUS_SUCCESS != QueryBrightnessCaps(pDisplayCtx)))
        {
          /* Do not return failure if the query brightness caps fails, sink may not support brightness capability */
          TraceInfo(QdiTraceDP, "DP%d: Sink Device brightness capability not supported", pStreamCtx->eDisplayID);
        }
      }
    }
  }

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_Host_Init()
*/
/*!
* \DESCRIPTION
*        This init function must be called before any host layer functions. 
*        Called from DPDriver_DrvInstall
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_Host_Init(void)
{
  DP_Status             eStatus        = DP_STATUS_SUCCESS;
  DP_DeviceDataType    *pSharedData    = DPHOST_GET_SHARED_CTX(); 

  if (NULL == pSharedData)
  {
    DP_LOG_MESSAGE_ERROR("DP_Host_Init: Failed to get DP Host shared data.");
    eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
  }
  else
  {
    /* Caution! bInitialized is not protected from multi-threaded access */
    /* Initialize the SharedData on the first Init call */

    if (FALSE == pSharedData->bInitialized)
    {
      DISP_OSAL_MemZero(pSharedData, sizeof(DP_DeviceDataType));

      /* Initialize PHY function vector table */
      HAL_DP_PhyFxnsInit();

      /* Initialize USB4 host router and QMPPhy base address */
      eStatus = DP_SetHostRouterBaseAddress();

      pSharedData->bInitialized = TRUE;
    }
    
    if (NULL == pSharedData->hHostLock)
    {
      if (MDP_STATUS_OK != DISP_OSAL_CreateLockEvent(&(pSharedData->hHostLock), (OSCharType*)L"HOSTLOCK"))
      { 
        DP_LOG_MESSAGE_ERROR("DP_Host_Init: Failed to create the global lock for DP Host.");
        eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      }
    }
  } 

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_Host_Deinit()
*/
/*!
* \DESCRIPTION
*        This deinit function must be called to fully terminate DP host.
*        Called from DPDriver_Uninstall
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_Host_Deinit()
{
  DP_Status             eStatus        = DP_STATUS_SUCCESS; 
  DP_DeviceDataType    *pSharedData    = DPHOST_GET_SHARED_CTX(); 
  
  if (NULL == pSharedData)
  {
    DP_LOG_MESSAGE_ERROR("DP_Host_Deinit: Failed to get DP Host shared data."); 
  }
  else
  {
    // Destroy the lock on first deinit call
    if (NULL != pSharedData->hHostLock)
    {
      if (MDP_STATUS_OK !=  DISP_OSAL_DestroyLockEvent(&(pSharedData->hHostLock)))
      { 
        DP_LOG_MESSAGE_ERROR("DP_Host_Deinit: Failed to destroy the global lock for DP Host."); 
        eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      } 
    }
  } 
 
  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_Host_Open()
*/
/*!
* \DESCRIPTION
*        This open function must be called before any other DP function is called
*
* \param [out]  phHandle        - Pointer to handle of DP Device
* \param [in]   psOpenConfig    - Pointer to host open configuration
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_Host_Open(DP_HandleType               *phHandle,
                        DP_HostOpenConfigType       *psOpenConfig)
{ 
  DP_Status eStatus = DP_STATUS_SUCCESS; 
  
  if ((NULL == phHandle) ||
      (NULL == psOpenConfig))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_Host_Open: Got Null Pointer ");
  }
  else if (DP_MST_STREAM_ID_MAX <= psOpenConfig->eStreamId)
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_Host_Open: psOpenConfig->eStreamId is out of range");
  }
  else
  { 
    DP_DeviceDataType          *pSharedData     = DPHOST_GET_SHARED_CTX();
    DP_DisplayCtxType          *pDisplayCtx     = DPHOST_GETCTX_FROM_HANDLE(*phHandle);
    DP_DeviceCtxType           *pDeviceCtx      = DPHOST_GET_DEVICE_CTX_FROM_ID(psOpenConfig->eDeviceID);
    DP_StreamCtxType           *pStreamCtx      = &(pDeviceCtx->aStreamCtx[psOpenConfig->eStreamId]);
    DP_HostRouterDeviceCtxType *pHostRouterCtx  = (DP_HostRouterDeviceCtxType*)psOpenConfig->hHostRouterHandle;
    MDP_Status                  eLocalStatus    = MDP_STATUS_OK;
    OSEventType                 hHostLock       = DPHOST_GET_HOST_LOCK();
    DP_Status                   eDPLocalStatus  = DP_STATUS_SUCCESS;

    /* Caution! bInitialized is not protected from multi-threaded access */
    if (FALSE == pSharedData->bInitialized)
    {
      /* One time initialization */
      DP_Host_Init();
    }
    if ((NULL == pDeviceCtx) || 
        (NULL == pStreamCtx))
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FATAL_ERROR;
      DP_LOG_MESSAGE_ERROR("DP_Host_Open: Failed to acquire the device context and the stream context from shared data.");
    }
    else if ((TRUE == psOpenConfig->bTunnelingMode) &&
             ((NULL == pHostRouterCtx)              ||  
              (FALSE == pHostRouterCtx->bInitialized)))
    {
      eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
      DP_LOG_MESSAGE_ERROR("DP_Host_Open: Invalid Host Router handle provided");
    }
    else
    {
      if (MDP_STATUS_OK != DISP_OSAL_AcquireLockEvent(hHostLock,0))
      { 
        DP_LOG_MESSAGE_ERROR("DP_Host_Open: Failed to acquire the global lock for DP Host.");
        eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      }
      else
      {
        if (NULL == pDisplayCtx)
        {
          // Allocate DP display context only if it has not been previously allocated
          pDisplayCtx = DISP_OSAL_Malloc(sizeof(DP_DisplayCtxType), QDI_OSAL_COMP_HDMI); 
          
          if (NULL == pDisplayCtx)
          {
            eStatus = DP_STATUS_FAILED_RESOURCE_FATAL_ERROR;
            DP_LOG_MESSAGE_ERROR("DP_Host_Open: Failed to allocate resource for DP handle");
          }
          else
          {
            DISP_OSAL_MemZero(pDisplayCtx, sizeof(DP_DisplayCtxType));
            pDisplayCtx->pDeviceCtx         = pDeviceCtx;
            pDisplayCtx->pStreamCtx         = pStreamCtx; 
            pDisplayCtx->pHostRouterCtx     = pHostRouterCtx;
            pDeviceCtx->eDeviceID           = psOpenConfig->eDeviceID;
            pDeviceCtx->eDeviceDPMode       = GetDPDeviceMode(psOpenConfig->eDisplayID,
                                                              psOpenConfig->eDeviceID,
                                                              psOpenConfig->bTunnelingMode);
            if (DP_MST_STREAM_ID_0 == psOpenConfig->eStreamId)
            {
              // Physical device is associated with stream 0.
              pDeviceCtx->eDisplayID          = psOpenConfig->eDisplayID; 
            }
            pStreamCtx->eMSTStreamId        = psOpenConfig->eStreamId;
            pStreamCtx->eDisplayID          = psOpenConfig->eDisplayID;
            pStreamCtx->bInUse              = TRUE;
          }
        }

        if (NULL != pDisplayCtx)
        {
          *(phHandle) = (void *)pDisplayCtx; // The display context has been allocated, need to be passed out and freed in host_close

          /* If the driver open call for stream 1 comes before stream 0, ignore it, as a subsequent
             driver open call for stream 1 will be invoked; driver open call for stream 0 will generate
             a soft HPD IN for slave displays. This is required to ensure the priority for stream
             bandwidth allocation remains consistent regardless of the sequence of the driver open calls.
          */
          if ((0 == pDeviceCtx->uNumActiveStreams) &&
              (DP_MST_STREAM_ID_1 == psOpenConfig->eStreamId))
          {
            // Do nothing
            TraceInfo(QdiTraceDP,"DP%d: Open, Deferring Stream 1 until Stream 0 is opened, StreamID=%d",
                                  pStreamCtx->eDisplayID,
                                  pStreamCtx->eMSTStreamId);
          }
          /* ACPI HPD event can be triggered not just by HPD but also certain sideband messages. 
            Which calls OpenPanelDriver. We have to ensure that if stream is already initialized
            not do execute dp_host_open actions again
          */
          else if ((NULL == pDisplayCtx->pStreamCtx)                                         ||
                   (FALSE == pDisplayCtx->pStreamCtx->bInitialized)                          ||
                   (0 != DPHOST_GETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_UNPLUG_HPD_DETECTED)))
          {
            if (DP_CONTROLLER_ID_NONE == (pDeviceCtx->eControllerID = AllocateDPController(psOpenConfig->eDeviceID, pDeviceCtx)))
            {
              // Dynamically allocate controller, return error when no controllers are available
              eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
              TraceInfo(QdiTraceDP,"DP%d: Open failed, no controllers, Deviceid = %d, StreamID = %d",
                                    pStreamCtx->eDisplayID,
                                    pDeviceCtx->eDeviceID, 
                                    pStreamCtx->eMSTStreamId); 
            }
            else if (DP_STATUS_SUCCESS != (eStatus = DP_ConfigureAllClocks(pDisplayCtx, TRUE))) /* Enable clocks prior to any controller/phy programming */
            {
              DP_LOG_MESSAGE_ERROR("DP_Host_Open: DP_ConfigureAllClocks Failed, eStatus = %d", eStatus);
              eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
            }
            else
            {
              /* Scenario where HPD-IN, HPD-OUT, HPD-IN are happening in quick succession
                 Power off after HPD Out didn't happened and HPD-In comes again, and so in order to successfully 
                 open the context, link configuration, stream init state and active stream count needs to be reset
              */
              if (0 != DPHOST_GETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_UNPLUG_HPD_DETECTED))
              {
                pDeviceCtx->bLinkConfigured   = FALSE;
                pDeviceCtx->uNumActiveStreams = 0;
                pStreamCtx->bInitialized      = FALSE;
                pDeviceCtx->uFlags            = DPHOST_CLEARFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_UNPLUG_HPD_DETECTED);
                pDeviceCtx->uFlags            = DPHOST_SETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_TOPOLOGY_UPDATED);      // force reparse
              
                TraceInfo(QdiTraceDP, "DP%d: Open, StreamID = %d is coming from HPD-In, HPD-Out, HPD-In scenario, where HPD-Out is happening while HPD-In is progress",
                                      pStreamCtx->eDisplayID, 
                                      pStreamCtx->eMSTStreamId); 
              }
              
              if (0 == pDeviceCtx->uNumActiveStreams)
              {
                HAL_DP_HPDConfigType  sHPDConfig;

                pDeviceCtx->uFlags              = DPHOST_MAPSETFLAG(psOpenConfig->eConfigFlags, pDeviceCtx->uFlags, DP_CONFIG_FLAG_HPD_FAILSAFE, DP_HOST_FLAG_HPD_FAILSAFE);
                pDeviceCtx->eConnectionPolarity = psOpenConfig->eConnectionPolarity;
                pDeviceCtx->ePinAssignment      = psOpenConfig->ePinAssignment; 
                pDeviceCtx->eDiagLevel          = psOpenConfig->eDiagLevel;

                if ((0 != psOpenConfig->sSourceOverrideCaps.uMaxLinkRateInKHz) &&
                      (!ValidLinkRate(pDeviceCtx, psOpenConfig->sSourceOverrideCaps.uMaxLinkRateInKHz)))
                {
                  pDeviceCtx->sSourceOverrideCaps.uMaxLinkRateInKHz = 0;

                  DISP_OSAL_LOG_WARNX("DP%i: Open, Invalid max source link rate (%d) override cap provided, cap will not take effect",
                                      pStreamCtx->eDisplayID,
                                      psOpenConfig->sSourceOverrideCaps.uMaxLinkRateInKHz);
                }
                else
                {
                  pDeviceCtx->sSourceOverrideCaps.uMaxLinkRateInKHz = psOpenConfig->sSourceOverrideCaps.uMaxLinkRateInKHz;
                }

                /* Set DP Tunneling mode enable */
                pDeviceCtx->sTunnelingModeConfig.bTunnelingMode = psOpenConfig->bTunnelingMode; 

                /* Set bonded mode configuration (must happen before redirector for bonded setup) */
                SetupBondedConfig(pDeviceCtx, pStreamCtx, &psOpenConfig->sBondedModeConfig);           

                /* Install and setup AUX functions */
                if ((TRUE == pDeviceCtx->sBondedModeConfig.bEnabled) &&
                    (pDeviceCtx->sBondedModeConfig.eMasterAUXDeviceID != pDeviceCtx->eDeviceID))
                {
                  // Slaves redirect EDID (to force same timing) and DPCD reads (on failure) to master AUX
                  // DPCD writes are redirected to a simulated success to avoid writing to an inexistent link.
                  DP_Redirector_ConfigureSlave(pDeviceCtx->eDeviceID,
                                               pDeviceCtx->sBondedModeConfig.eMasterAUXDeviceID,
                                               &psOpenConfig->sOverrideConfig);
                  DP_Host_AuxInstall(pDeviceCtx, pStreamCtx, DP_AUX_FUNCTION_TYPE_REDIRECTOR);
                }
                else if (MDP_DP_OVERRIDE_MODE_OFF != psOpenConfig->sOverrideConfig.eMode)
                {
                  // Internal displays will have specified sections (EDID, DPCD Caps, DPCD Status, DPCD reads/writes)
                  // redirected, if mode is REPLACE, provided buffers from sOverrideConfig are always redirected to,
                  // and if mode is FALLBACK, the buffers will be redirected if AUX fails.
                  DP_Redirector_ConfigureOverrides(pDeviceCtx->eDeviceID, &psOpenConfig->sOverrideConfig);
                  DP_Host_AuxInstall(pDeviceCtx, pStreamCtx, DP_AUX_FUNCTION_TYPE_REDIRECTOR);
                }
                else if (DPHOST_GETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_SIMULATION_MODE))
                {
                  DP_Host_AuxInstall(pDeviceCtx, pStreamCtx, DP_AUX_FUNCTION_TYPE_SIM);
                }
                else
                {
                  DP_Host_AuxInstall(pDeviceCtx, pStreamCtx, DP_AUX_FUNCTION_TYPE_PHYSICAL);
                }

                if (0 != (psOpenConfig->eConfigFlags & DP_CONFIG_FLAG_ALT_MODE_FIXED_LANE_CONFIGURATION))
                {
                  if (TRUE == IsAltModeDPDevice(pDeviceCtx->eDeviceID))
                  {
                    pDeviceCtx->uFlags = DPHOST_SETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_ALT_MODE_FIXED_LANE_CONFIGURATION);
                  }
                  else
                  {
                    DISP_OSAL_LOG_WARNX("DP_Host_Open: Lane mapping only supported on Type-C ports, eDeviceID = %d", pDeviceCtx->eDeviceID);
                  }
                }

                /* Initialize and reset HW */
                if (FALSE == psOpenConfig->bInitContextOnly)
                {
                  /* 
                   * If display is already active(continuous splash), then only the sw context is initialized 
                   * and hw should not be touched. So skip the hw reset.
                   */
                  HAL_DP_Reset(pDeviceCtx->eControllerID, HAL_DP_MODULE_TYPE_CONTROLLER, 0);
                }  
              
                HAL_DP_Init( pDeviceCtx->eControllerID);
             
                /* Enable double-buffering */
                HAL_DP_Enable_DoubleBuffer(pDeviceCtx->eControllerID, TRUE);
              
                /* Enable AUX block for HPD block */
                HAL_DP_AUXChannel_Enable(pDeviceCtx->eControllerID, TRUE);
              
                /* HPD block init */
                DP_OSAL_MemSet(&sHPDConfig, 0, sizeof(HAL_DP_HPDConfigType));
                sHPDConfig.eDeviceID     = pDeviceCtx->eDeviceID;
                sHPDConfig.eDeviceDPMode = pDeviceCtx->eDeviceDPMode;
                sHPDConfig.bEnable       = TRUE;
                sHPDConfig.bActiveLow    = FALSE;
                HAL_DP_HPD_Engine_Enable(pDeviceCtx->eControllerID, &sHPDConfig);
                
                /* Check device plug-in status*/
                if (DP_STATUS_SUCCESS != (eStatus = DP_CheckConnectionStatus((DP_HandleType)pDisplayCtx)))
                {
                  DP_LOG_MESSAGE_ERROR("DP_Host_Open: DP_CheckConnectionStatus Failed, eStatus = %d", eStatus);
                }
                else if ((DP_CONNECTION_STATUS_DISCONNECTED   == pDeviceCtx->eConnectionPolarity)    ||
                         (pDeviceCtx->eConnectionPolarity     >= DP_CONNECTION_STATUS_MAX)           ||
                         (DP_CONNECTION_PINASSIGNMENT_INVALID == pDeviceCtx->ePinAssignment)         ||
                         (pDeviceCtx->ePinAssignment          >= DP_CONNECTION_PINASSIGNMENT_MAX))
                {
                  /* Gfx queries connection status using bPluggedin status, since a valid connection is
                    not detected, so forcing the status to false */
                  pDeviceCtx->bPluggedIn = FALSE;
                  TraceInfo(QdiTraceDP, "DP%d: Host_Open did not detect Type-C connection (Polarity:%d, PinAssignment:%d)",
                                         pStreamCtx->eDisplayID,
                                         pDeviceCtx->eConnectionPolarity, 
                                         pDeviceCtx->ePinAssignment);
                }
                /* Create an event to synchronize DPCP read/write access */
                else if ((NULL         == pDeviceCtx->hAuxAccessLock) && 
                        (MDP_STATUS_OK != (eLocalStatus = DISP_OSAL_CreateLockEvent(&pDeviceCtx->hAuxAccessLock, (OSCharType*)L"AUXSYNCLOCK"))))
                {
                  pDeviceCtx->bPluggedIn = FALSE;
                  eStatus                = DP_STATUS_FAILED_RESOURCE_FAILED;
                  DISP_OSAL_LOG1("DP_Host_Open() failed to initialize hAuxAccessLock qdiStatus=%d", eLocalStatus);
                }
                else
                {
                  /* Create an Event for DP AUX transaction waiting status */
                  if ((TRUE          != psOpenConfig->bAuxUsePolling)       &&
                      (NULL          == pDeviceCtx->hAuxReadyEvent)         &&
                      (MDP_STATUS_OK != (eLocalStatus = DISP_OSAL_CreateEvent(&pDeviceCtx->hAuxReadyEvent, (OSCharType*)L"AUXEVENT"))))
                  {
                    DISP_OSAL_LOG_WARN1("DP_Host_Open() failed to initialize hAuxEvent qdiStatus=%d continue with Polling", eLocalStatus);
                  }
              
                  HAL_DP_AuxHwCapsType            sHALHwCap;
              
                  // TODO: this is alway false 
                  if (FALSE == GetConcurrencyMode(pDeviceCtx))
                  {
                    if (0 != (psOpenConfig->eConfigFlags & DP_CONFIG_FLAG_ALT_MODE_COMMON_RESET))
                    {
                      /* Reset DP & USB combo PHY */
                      HAL_DP_PHY_Reset(pDeviceCtx->eDeviceID, DP_PHY_RESET_ALT_MODE_COMMON_RESET);
                    }

                    HAL_DP_PHY_SetPHYMode(pDeviceCtx->eDeviceID, DP_PHY_MODE_DP);
                  }
              
                  /* Indicate a valid Connection status */
                  pDeviceCtx->bPluggedIn              = TRUE;
                  pDeviceCtx->bInvertedPlug           = DP_CONNECTION_POLARITY_POLARITY_DEFAULT == pDeviceCtx->eConnectionPolarity ? TRUE : FALSE;
              
                  /* Set Default values */
                  pDeviceCtx->eLinkTrainingType       = DP_LINK_TRAINING_TYPE_FULL_TRAINING;
                  pDeviceCtx->bSynchronousClk         = TRUE;   // Pixel clock and Main-Link Symbol clock are synchronous with each other 
                  pDeviceCtx->hIRQPollingThread       = NULL;
                  pDeviceCtx->uIRQPollingIntervalInMs = 1000;
                  pDeviceCtx->bDualPixelMode          = DP_DualPixelModeSupported(pDisplayCtx);
              
                  /* Update Open Parameters */
                  pDeviceCtx->eSSCMode                = psOpenConfig->eSSCMode;
                  pDeviceCtx->uLaneMapping            = ((HAL_DP_LANEMAP_TYPE_NONE == psOpenConfig->uLaneMapping) ||
                                                        (HAL_DP_LANEMAP_TYPE_MAX  <= psOpenConfig->uLaneMapping)) ? HAL_DP_LANEMAP_TYPE_0123 : psOpenConfig->uLaneMapping;
                  pDeviceCtx->uFlags                  = DPHOST_MAPSETFLAG(psOpenConfig->eConfigFlags, pDeviceCtx->uFlags, DP_CONFIG_FLAG_AUX_PIN_SWITCH_INVERTED, DP_HOST_FLAG_AUX_PN_SWITCH_INVERTED);
                  pDeviceCtx->uFlags                  = DPHOST_SETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_DISABLE_DSC);
                  pDeviceCtx->uFlags                  = DPHOST_SETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_DISABLE_MST);
                  pDeviceCtx->uFlags                  = DPHOST_MAPSETFLAG(psOpenConfig->eConfigFlags, pDeviceCtx->uFlags, DP_CONFIG_FLAG_STRICT_EDID_CHECK, DP_HOST_FLAG_STRICT_EDID_CHECK);
                  pDeviceCtx->uFlags                  = DPHOST_SETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_DISABLE_PSR);
                  pDeviceCtx->uTotalPixelRate         = DP_GetMaxPixelRate();
                  
                  DISP_OSAL_MemCpyEx(&pDeviceCtx->sPreEmphSwingConfigType, sizeof(DP_Config_PreEmphSwingType), &psOpenConfig->sPreEmphSwingConfigType, sizeof(DP_Config_PreEmphSwingType));
                  
                  if (DPCD_SPEC_MAX_VOLTAGE_SWING_LEVEL >= psOpenConfig->uLaneSwingLevel)
                  {
                    pDeviceCtx->uVoltageSwingLevel = psOpenConfig->uLaneSwingLevel;
                  }
                  else
                  {
                    pDeviceCtx->uVoltageSwingLevel = DPCD_SPEC_MIN_VOLTAGE_SWING_LEVEL;
                    DP_LOG_MESSAGE_WARN("DP_Host_Open: Invalid voltage swing level, set to MIN_VOLTAGE_SWING_LEVEL");
                  }
              
                  if (DPCD_SPEC_MAX_PRE_EMPHASIS_LEVEL >= psOpenConfig->uPreemphasisLevel)
                  {
                    pDeviceCtx->uPreEmphasisLevel = psOpenConfig->uPreemphasisLevel;
                  }
                  else
                  {
                    pDeviceCtx->uPreEmphasisLevel = DPCD_SPEC_MIN_PRE_EMPHASIS_LEVEL;
                    DP_LOG_MESSAGE_WARN("DP_Host_Open: Invalid pre-emphasis level, set to MIN_PRE_EMPHASIS_LEVEL");
                  }
              
                  /* Get the max supported voltage swing & pre-emphasis levels in hardware */
                  if (HAL_MDSS_STATUS_SUCCESS != HAL_DP_PHY_GetMaxPeSwLevel(pDeviceCtx->eDeviceID,
                                                                          &pDeviceCtx->uMaxPreemphLvl,
                                                                          &pDeviceCtx->uMaxVoltSwingLvl))
                  {
                    pDeviceCtx->uMaxPreemphLvl   = DPCD_SPEC_MAX_PRE_EMPHASIS_LEVEL;
                    pDeviceCtx->uMaxVoltSwingLvl = DPCD_SPEC_MAX_VOLTAGE_SWING_LEVEL;
                  }
              
                  /* Get the Max CMD FIFO length from HAL */
                  HAL_DP_AUX_GetHwCaps(pDeviceCtx->eControllerID, &sHALHwCap);
                  pDeviceCtx->uMaxAUXCmdFifoLen       = sHALHwCap.uAUXCmdFifoLen;
                  pDeviceCtx->bInitialized            = TRUE;
              
                  if (FALSE == psOpenConfig->bInitContextOnly)
                  {
                    /* Enable clocks prior to any controller/phy programming */
                    if (HAL_MDSS_STATUS_SUCCESS != HAL_DP_CrossbarConfig(pDeviceCtx->eControllerID, pDeviceCtx->eDeviceID))
                    {
                      DP_LOG_MESSAGE_ERROR("DP: Failed to configure DP PHY crossbar for DP controller %d", pDeviceCtx->eControllerID);
                      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
                    }
                    else
                    {
                      HAL_DP_AUXConfigType     sAUXCtrlConfig;
                      HAL_DP_AUXAttribType     sAUXAttrib;
                      uint32                   uAuxTimeoutCount = DP_AUX_CLKS_FOR_ONE_MSEC;    // corresponds to 1 ms                 
                      uint32                   uAuxTimeout      = DP_AUX_HW_TIMEOUT_MS;
              
                      /* Set the DP clocks source to CXO */
                      DP_ParkLinkAndPixelClockSources(pDisplayCtx);
              
                      /* SW Reset DP HW */
                      HAL_DP_Reset(pDeviceCtx->eControllerID, (HAL_DP_MODULE_TYPE_AUX | HAL_DP_MODULE_TYPE_PHY), 0);
              
                      /* Set max AUX timeout config */
                      DP_OSAL_MemSet(&sAUXCtrlConfig, 0, sizeof(HAL_DP_AUXConfigType));
                      DP_OSAL_MemSet(&sAUXAttrib,     0, sizeof(HAL_DP_AUXAttribType));
                      sAUXAttrib.puTimeoutLimit   = &uAuxTimeout;
                      sAUXAttrib.puReadZeroLimit  = &uAuxTimeout;
                      sAUXAttrib.puNackDeferLimit = &uAuxTimeout;
                      sAUXAttrib.puI2CDeferLimit  = &uAuxTimeout;
                      sAUXAttrib.puTimeoutCount   = &uAuxTimeoutCount;
                      sAUXCtrlConfig.psAUXAttrib  = &sAUXAttrib;
                      HAL_DP_AUXConfig(pDeviceCtx->eControllerID, &sAUXCtrlConfig, 0);
              
                      /* Initialize Auxiliary  */
                      HAL_DP_PHY_AUX_Init(pDeviceCtx->eDeviceID, pDeviceCtx->eDeviceDPMode);
                    }
                  } 
                
                  if (DP_STATUS_SUCCESS == eStatus)
                  {
                      /* Clear any stale interrupts */
                    HAL_DP_Interrupt_Clear(pDeviceCtx->eControllerID, HAL_DP_AUX_INTR_ALL, 0);
                        
                    pDeviceCtx->bAuxReady = TRUE;
                    
                    /* Pass on capability mask */
                    pDeviceCtx->eCapabilityMask = psOpenConfig->eCapabilityMask;
                  } 
                }
              } 
              
              TraceInfo(QdiTraceDP,"DP%d: Open - deviceID:%d, streamID:%d, numStreams:%d, plugStatus:%d, plugPolarity:%d", 
                        pStreamCtx->eDisplayID, 
                        pDeviceCtx->eDeviceID, 
                        pStreamCtx->eMSTStreamId,
                        pDeviceCtx->uNumActiveStreams,
                        pDeviceCtx->bPluggedIn,
                        pDeviceCtx->bInvertedPlug);
              
              if (FALSE == pDeviceCtx->bPluggedIn)
              {
                pStreamCtx->bSinkConnected = FALSE;
              }
              else 
              {
                uint32 uNumStreams = 0;
                
                pStreamCtx->uModeIndex              = DP_HOST_MODE_INVALID;
                pStreamCtx->uNumModes               = 0;
                pStreamCtx->eBrightnessType         = psOpenConfig->eBrightnessType;

                if ((DP_STATUS_SUCCESS != (eStatus = DP_Host_QueryPanelInfo(pDisplayCtx, &uNumStreams))))
                {
                  DP_LOG_MESSAGE_ERROR("DP_Host_Open: DP_Host_QueryPanelInfo failed, eStatus = %d ", eStatus);
              
                  pDeviceCtx->bPluggedIn     = (pDeviceCtx->uSinkCount) ? TRUE : FALSE;
                  pStreamCtx->bSinkConnected = FALSE; 
                }
                else
                {
                  /* Disable SSC mode if the sink reports it does not support it */
                  if (!(DP_DPCD_CAP_MAX_DOWNSPREAD_0_5 & pDeviceCtx->sSinkDPCDCap.eDPCDCap))
                  {
                    pDeviceCtx->eSSCMode = MDP_DP_SSC_DISABLED;
                  }
                  
                  uint32 uLinkRate    = DP_ReadLinkRateOverride(pDisplayCtx);
                  
                  if (0 != uLinkRate)
                  {
                    DP_SetPropertyParamsType  sPropertyData;
              
                    DP_OSAL_MemSet(&sPropertyData, 0, sizeof(DP_SetPropertyParamsType));
                    sPropertyData.uLinkRate = uLinkRate;
              
                    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_SetProperty(pDisplayCtx, DP_SETPROPERTY_LINK_RATE, &sPropertyData)))
                    {
                      DP_LOG_MESSAGE_ERROR("DP_Host_Open: DP_Host_SetProperty failed to set link rate, eStatus = %d", eStatus);
                    }
                    TraceInfo(QdiTraceDP, "DP%d: Link Rate is override to %dMhz, eStatus = %d", pStreamCtx->eDisplayID, uLinkRate, eStatus);
                  } 
              
                  // Send Soft HPD interrupt 
                  // Soft HPD for additional sinks need to be requested only once,
                  // When uNumActiveStreams is non-zero soft HPD has already been issued
                  if (0 == pDeviceCtx->uNumActiveStreams)
                  {
                    uint32 uStreamIdx   = DP_MST_STREAM_ID_1;
                    uint32 uHPDCount    = 0;                                       // Number of MST streams not including stream0
                    uint32 uHPDTotal    = uNumStreams > 1 ? (uNumStreams - 1) : 0; // SST or MST 1 stream does not need extra HPDs to be sent
              
                    // Soft HPD needs to be issued only for stream1 onwards
                    // For Stream0, HPD is reported though ACPI or USB events
                    while ((uStreamIdx < DP_MST_STREAM_ID_MAX) && 
                           (uHPDCount  < uHPDTotal))
                    { 
                      // Indicate which displays require soft HPD 
                      pDeviceCtx->sMSTSinkHPDList[uHPDCount].eDisplayID = DP_GetDisplayMap(pDeviceCtx->eDeviceID, uStreamIdx);
                      pDeviceCtx->sMSTSinkHPDList[uHPDCount].bHPDIn     = TRUE;
                      uHPDCount++;
                      uStreamIdx++;
                    }
              
                    pDeviceCtx->uMSTSinkHPDCount = uHPDCount;
                  }
                }
              }
              
              // Only increment the stream count if the display is connected and the stream is setup properly.
              if ((DP_STATUS_SUCCESS == eStatus)             && 
                  (TRUE  == pStreamCtx->bSinkConnected)      &&
                  (FALSE == pStreamCtx->bInitialized))
              {
                pDeviceCtx->uNumActiveStreams++;
                pStreamCtx->bInitialized = TRUE;
              
                /* Create WorkItem for HPD worker thread if needed */
                if (DP_STATUS_SUCCESS != (eDPLocalStatus = DP_CreateWorkItem(&pStreamCtx->hHPDWorkItem)))
                {
                  DP_LOG_MESSAGE_WARN("DP_Host_Open: DP_CreateWorkItem failed, eDPLocalStatus = %d ", eDPLocalStatus);
                }
                
                // Enable only the resources for the controller allocated to this stream.  
                DP_SetControllerResources(pDeviceCtx->eControllerID, 
                                          DP_GetDisplayMap(pDeviceCtx->eDeviceID, pStreamCtx->eMSTStreamId)); 
              
                TraceInfo(QdiTraceDP,"DP%d: Open Done - streamId:%d, streamCount:%d", 
                   pStreamCtx->eDisplayID,
                   pStreamCtx->eMSTStreamId,
                   pDeviceCtx->uNumActiveStreams);
              }
            }
            
            if (0 == pDeviceCtx->uNumActiveStreams)
            {
              // Free controller back to the pool when no external display is connected 
              FreeDPController(pDeviceCtx);
            }
          }
        }

        DISP_OSAL_ReleaseLockEvent(hHostLock);
      } 
    }
  }

  return eStatus;
} 


/**********************************************************************************************************************

FUNCTION: DP_Host_Power()
   
   This API is called to de-initialize the corresponding resources that is initialized when DP_Open() is called.
   It will return an error if the device handle is invalid. All resources will be de-initialized . User should ensure 
   that no other DP function will be called before another DP_Open() were called. otherwise corresponding error will 
   be returned to the user. Upon an invalid device handle, this call will also return an error.

Parameters:
    hHandle              - [in] handle to DP device 
    bPowerEnable         - [in] Power on/off

Return: 
   DP_Status 

**********************************************************************************************************************/
DP_Status  DP_Host_Power(DP_HandleType hHandle, bool32 bPowerEnable)
{
  DP_Status                 eStatus       = DP_STATUS_SUCCESS; 
  DP_DisplayCtxType        *pDisplayCtx   = DPHOST_GETCTX_FROM_HANDLE(hHandle); 
  DP_DeviceCtxType         *pDeviceCtx    = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType         *pStreamCtx    = DPHOST_GET_STREAM_CTX(pDisplayCtx); 

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_Host_Power: Null pointer handle passed in");
  }
  else
  { 
    OSEventType           hHostLock   = DPHOST_GET_HOST_LOCK();
    
    if (MDP_STATUS_OK != DISP_OSAL_AcquireLockEvent(hHostLock,0))
    { 
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DP_LOG_MESSAGE_ERROR("DP_Host_Power: Failed to acquire the global lock for DP Host.");
    } 
    else
    {
      if (TRUE == bPowerEnable)
      {
        DP_LOG_MESSAGE_ERROR("DP_Host_Power: Power on path has not been defined.");
      }
      else
      {
        if (FALSE == pDeviceCtx->bInitialized)
        {
          TraceInfo(QdiTraceDP,"DP%d: Host Power(off), device has not been initialized yet",
                                pStreamCtx->eDisplayID);
        }
        else if (FALSE == pStreamCtx->bInitialized)
        {
          /* Stream has not been Initialized yet */
        }
        else
        {
          DP_ClockStatusType    uClockStatus;
          bool32                bPLLLocked = FALSE;

          /* Disable pixel clock for current MST stream */
          DP_PixelClockEnable(pDisplayCtx, NULL, FALSE);

          if (pDeviceCtx->uNumActiveStreams > 0)
          {
            pDeviceCtx->uNumActiveStreams--;
          } 

          /* Close actions needed for each stream. */
          pStreamCtx->bInitialized = FALSE;

          /* If DP is plugged out, then clear the edid status flag */
          if (FALSE == pDeviceCtx->bPluggedIn)
          {
            pStreamCtx->bEDIDObtained = FALSE;
          }     

          TraceInfo(QdiTraceDP,"DP%d: Host Power(off), stream count = %d", pStreamCtx->eDisplayID,
                                                                           pDeviceCtx->uNumActiveStreams); 
          
          // Close actions need only if there is zero active stream.
          if (0 == pDeviceCtx->uNumActiveStreams)
          { 
            HAL_DP_HPDConfigType  sHPDConfig;
            HAL_MDSS_ErrorType    ePHYPowerResult;

            /* HPD block disable */
            DP_OSAL_MemSet(&sHPDConfig, 0, sizeof(HAL_DP_HPDConfigType));

            sHPDConfig.eDeviceID     = pDeviceCtx->eDeviceID;
            sHPDConfig.eDeviceDPMode = pDeviceCtx->eDeviceDPMode;
            sHPDConfig.bEnable       = FALSE;
            sHPDConfig.bActiveLow    = FALSE;
            HAL_DP_HPD_Engine_Enable(pDeviceCtx->eControllerID, &sHPDConfig);

            if (TRUE == pDeviceCtx->bMSTEnabled)
            {
              // Disable MST on controller side
              pDeviceCtx->uTotalPixelRate     = 0;
              pDeviceCtx->bMSTEnabled         = FALSE;
            }

            /* if DP is still plugged in, send power state command to sink
               If panel is not connected or aux lock is already cleared, skip aux write
             */
            if ((TRUE == pDeviceCtx->bPluggedIn)  &&
                (NULL != pDeviceCtx->hAuxAccessLock))
            {
              DP_WriteSinkDPCDPower(pDisplayCtx, DP_DPCD_POWERSTATE_D3);
            }

            /* Disable all interrupts - AUX and HPD */
            HAL_DP_Interrupt_Disable(pDeviceCtx->eControllerID, HAL_DP_INTR_ALL, 0x0);
            HAL_DP_Interrupt_Clear(pDeviceCtx->eControllerID, HAL_DP_INTR_ALL, 0x0);

            /* Disable AUX */
            HAL_DP_AUXChannel_Enable(pDeviceCtx->eControllerID, FALSE);

            /* Set the DP clocks source to CXO before turning them off*/
            DP_LinkClockEnable(pDisplayCtx, FALSE);

            /* Query DP clock status */
            HAL_DP_GetClockStatus(pDeviceCtx->eControllerID,   &uClockStatus);
            HAL_DP_PHY_GetPLLStatus(pDeviceCtx->eDeviceID, &bPLLLocked);

            if ((0 == (uClockStatus & DP_CLOCKSTATUS_MAIN_LINK_CLK_ACTIVE)) ||
                (FALSE == bPLLLocked))
            {
              TraceInfo(QdiTraceDP, "DP%d: Skipping Link clock related operation, since mode is not set and DP PLL is unlocked", pStreamCtx->eDisplayID);
            }
            else
            {
              /* Push idle pattern */
              HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_PUSH_IDLE);

              /* Turn off MDP Backpressure */
              HAL_DP_SetBackPressure(pDeviceCtx->eControllerID, (DP_StreamIDType)pStreamCtx->eMSTStreamId, FALSE);

              /* Disable links */
              HAL_DP_Mainlink_Enable(pDeviceCtx->eControllerID, FALSE);
            }

            if (!GetConcurrencyMode(pDeviceCtx))
            {
              HAL_DP_PHY_SetPHYMode(pDeviceCtx->eDeviceID, DP_PHY_MODE_USB_DATA);
            }

            /* Log start of PHY and PLL disable */
            DISP_OSAL_EVENTLOG3(DISP_OSAL_EVENT_PLLPROGRAMMING_START, pDeviceCtx->eDeviceID, 0, (DP_PHY_POWER_PHY | DP_PHY_POWER_PLL));

            /* Power down DP PHY/PLL */
            if (HAL_MDSS_STATUS_SUCCESS != (ePHYPowerResult = HAL_DP_PHY_Power(pDeviceCtx->eDeviceID,
                                                                               FALSE,
                                                                               (DP_PHY_POWER_PHY | DP_PHY_POWER_PLL))))
            {
              DP_LOG_MESSAGE_ERROR("DP%d: HAL_DP_PHY_Power failed with error=%d in DP_Host_Power.\n",
                                   pStreamCtx->eDisplayID,
                                   ePHYPowerResult);
            }

            /* Log end of PHY and PLL disable */
            DISP_OSAL_EVENTLOG3(DISP_OSAL_EVENT_PLLPROGRAMMING_END, pDeviceCtx->eDeviceID, ePHYPowerResult, (DP_PHY_POWER_PHY | DP_PHY_POWER_PLL));

            /* Decrement pixel clock source ref count, for shared resource bookkeeping in bonded mode. */
            if (0 == UpdateSourceClockRefCount(pDeviceCtx, -1))
            {
              /* Tear down required for external PLL in bonded mode */
              if (DP_STATUS_SUCCESS != (eStatus = ConfigureExternalSourceClock(pDeviceCtx, NULL, FALSE)))
              {
                DP_LOG_MESSAGE_ERROR("DP%d: ConfigureExternalSourceClock failed with error=%d in DP_Host_Power.\n", pDeviceCtx->eDeviceID, eStatus);
              }
            }

            /* Reinitialize and reset HW */
            HAL_DP_Init(pDeviceCtx->eControllerID);

            /* Disable all DP clocks */
            DP_ConfigureAllClocks(pDisplayCtx, FALSE);

            /* Clean up device context */
            CloseDeviceContext(pDeviceCtx);
          }
        }
      } 
      DISP_OSAL_ReleaseLockEvent(hHostLock); 
    }
  }

  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_Host_Close()
   
   This API is called to free the dynamically allocated DP host layer handle, which needs to be kept even after 
   DPDriver_Power Down path.

Parameters:
    hHandle              - [in] handle to DP device 

Return: 
   DP_Status 

**********************************************************************************************************************/
DP_Status  DP_Host_Close(DP_HandleType    hHandle)
{ 
  DP_DisplayCtxType     *pDisplayCtx    = DPHOST_GETCTX_FROM_HANDLE(hHandle); 
  DP_DeviceCtxType      *pDeviceCtx     = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType      *pStreamCtx     = DPHOST_GET_STREAM_CTX(pDisplayCtx);
  OSEventType            hHostLock      = DPHOST_GET_HOST_LOCK();

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx))
  {
    DP_LOG_MESSAGE_ERROR("DP_Host_Close: invalid DP host handle.");
  } 
  else if (MDP_STATUS_OK != DISP_OSAL_AcquireLockEvent(hHostLock,0))
  { 
    DP_LOG_MESSAGE_ERROR("DP_Host_Close: Failed to acquire the global lock for DP Host.");
  }
  else
  {
    if (TRUE == pStreamCtx->bInitialized)
    {
      DP_LOG_MESSAGE_WARN("DP_Host_Close: Close without powering down.");

      /*
       * Stream refcount is handled inside power off. Since power off wasn't called in this
       * scenario, make sure the refcount is updated so device context gets closed properly.
       */
      if (pDeviceCtx->uNumActiveStreams > 0)
      {
        pDeviceCtx->uNumActiveStreams--;
      }
    }

    /* Release resource for HPD worker thread */
    if (DP_STATUS_SUCCESS != DP_DestroyWorkItem(&pStreamCtx->hHPDWorkItem))
    {
      DP_LOG_MESSAGE_WARN("DP_Host_Close: Failed to destory workitem.");
    }

    /* Clear Stream Context */
    DISP_OSAL_MemZero(pStreamCtx, sizeof(DP_StreamCtxType));

    if (0 == GetNumStreamsInUse(pDeviceCtx))
    {
      /* Free controllers when all streams are closed */
      FreeDPController(pDeviceCtx);

      /* Clean up device context */
      CloseDeviceContext(pDeviceCtx);

      /* Clear Device Context */
      DISP_OSAL_MemZero(pDeviceCtx, sizeof(DP_DeviceCtxType));
    } 

    DISP_OSAL_Free(hHandle); 
    DISP_OSAL_ReleaseLockEvent(hHostLock);
  } 

  return DP_STATUS_SUCCESS;
}

/**********************************************************************************************************************

FUNCTION:  DP_Host_Commit

  This API allows users to commit all the settings and apply to H/W. 

Parameters:
  hHandle                           -[in] Logic handle of DP Device.

Return: 
  DP_Status 

**********************************************************************************************************************/
DP_Status  DP_Host_Commit(DP_HandleType    hHandle)
{
  DP_Status              eStatus        = DP_STATUS_SUCCESS; 
  OSEventType            hHostLock      = DPHOST_GET_HOST_LOCK(); 
  DP_DisplayCtxType     *pDisplayCtx    = DPHOST_GETCTX_FROM_HANDLE(hHandle); 
  DP_DeviceCtxType      *pDeviceCtx     = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType      *pStreamCtx     = DPHOST_GET_STREAM_CTX(pDisplayCtx);

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_Host_Commit: Null pointer handle passed in");
  }
  else if (MDP_STATUS_SUCCESS != DISP_OSAL_AcquireLockEvent(hHostLock, 0))
  {
    DP_LOG_MESSAGE_ERROR("DP_Host_Commit: Failed to acquire host layer global lock. Controller=%d", pDeviceCtx->eControllerID);
    eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
  }
  /* The settings are usually applied on a SetMode */
  else
  { 
    if (pStreamCtx->uDirtyBits & DP_DIRTYFIELD_SETMODE)
    {
      if (DP_STATUS_SUCCESS != (eStatus = DP_Host_SetMode(pDisplayCtx)))
      {
        DP_LOG_MESSAGE_ERROR("DP_Host_Commit: DP_Host_SetMode failed, eStatus = %d", eStatus);
      }

      pStreamCtx->uDirtyBits &= ~DP_DIRTYFIELD_SETMODE;
    }

    DISP_OSAL_ReleaseLockEvent(hHostLock);
  }

  return eStatus;
}


/*********************************************************************************************
*
** FUNCTION: DP_Host_SetProperty()
*/
/*!
* \DESCRIPTION
*      Allows the user to set the attributes and properties of the DP device
*
* \param [in]   hHandle        - Handle to DP device
* \param [in]   ePropertyType  - Property ID that requires update
* \param [in]   pPropertyData  - parameters of the property to be applied
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_Host_SetProperty(DP_HandleType                   hHandle,
                               DP_SetPropertyType              ePropertyType,
                               DP_SetPropertyParamsType       *pPropertyData)
{
  DP_Status                       eStatus        = DP_STATUS_SUCCESS; 
  DP_DisplayCtxType              *pDisplayCtx    = DPHOST_GETCTX_FROM_HANDLE(hHandle);
  DP_DeviceCtxType               *pDeviceCtx     = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType               *pStreamCtx     = DPHOST_GET_STREAM_CTX(pDisplayCtx); 

  if (((NULL == pDeviceCtx)  ||
       (NULL == pStreamCtx)) &&
       (DP_SETPROPERTY_SIMULATION_MODE != ePropertyType))
  {
    DP_LOG_MESSAGE_ERROR("DP_Host_SetProperty: Null handle");
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  { 
    switch (ePropertyType)
    {
      case DP_SETPROPERTY_LINK_RATE:
      {
        uint32  uIndex;
        uint32 *puSupportedLinkRateInKHz;
        uint32  uSupportedLinkRateCount;
        uint32  uRequestedLinkRate  = 0; 
        bool32  bFound              = FALSE;
        
        
        /* Supported eDP link rate setting */
        uint32 uEDPSupportedLinkRateInKHz[9] =
        {
          162000, // Reduced Bit Rate[RBR]
          216000,
          243000,
          270000, // High Bit Rate [HBR]
          324000,
          432000,
          540000, // High Bit Rate 2 [HBR2]
          594000,
          810000, // High Bit Rate 3 [HBR3]
        };

        /* Supported DP link rate setting */
        uint32 uDPSupportedLinkRateInKHz[4]=
        {
          162000, // Reduced Bit Rate[RBR]
          270000, // High Bit Rate [HBR]
          540000, // High Bit Rate 2 [HBR2]
          810000, // High Bit Rate 3 [HBR3]
        };

        // Handle request to default back to DPCD caps
        if (0 == pPropertyData->uLinkRate)
        {
          uRequestedLinkRate = pDeviceCtx->sSinkDPCDCap.uMaxLinkRateInKhz; 
          bFound             = TRUE;
        }
        else
        {
          // Select the link rate table based on the controller
          if (DP_CONTROLLER_ID_DP_3 == pDeviceCtx->eControllerID)
          {
            uSupportedLinkRateCount   = DPHOST_GET_LIST_SIZE(uEDPSupportedLinkRateInKHz);
            puSupportedLinkRateInKHz  = &uEDPSupportedLinkRateInKHz[0];
          }
          else
          {
            uSupportedLinkRateCount   = DPHOST_GET_LIST_SIZE(uDPSupportedLinkRateInKHz);
            puSupportedLinkRateInKHz  = &uDPSupportedLinkRateInKHz[0];
          }
  
          for (uIndex = 0; uIndex < uSupportedLinkRateCount; uIndex++)
          {
            if (puSupportedLinkRateInKHz[uIndex] == pPropertyData->uLinkRate)
            {
              uRequestedLinkRate = pPropertyData->uLinkRate;
              bFound             = TRUE;
              break;
            }
          }
        }

        if (TRUE == bFound)
        {
          pDeviceCtx->uLinkRateInKhz                = uRequestedLinkRate;
          pStreamCtx->uDirtyBits                   |= DP_DIRTYFIELD_SINK_ATTRIB  |
                                                      DP_DIRTYFIELD_LINK_RATE    |
                                                      DP_DIRTYFIELD_TU_PARAMETERS;
          TraceInfo(QdiTraceDP, "DP%d: DP_Host_SetProperty() setting link rate(Khz) %d", pStreamCtx->eDisplayID, pPropertyData->uLinkRate);
        }
        else
        {
          eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
          TraceInfo(QdiTraceDP, "DP%d: DP_Host_SetProperty() invalid link rate(Khz) %d request", pStreamCtx->eDisplayID, pPropertyData->uLinkRate);
        }
        break;
      }
      case DP_SETPROPERTY_LANE_NUMBER:
      {
        uint32 uIndex;
        uint32 uRequestedLanes = 0;
        bool32 bFound          = FALSE;
        

        /* Supported lane count setting */
        const uint32 uSupportLaneCount[] =
        {
          1,
          2,
          4,
        };

        // Handle request to default back to DPCD caps
        if (0 == pPropertyData->uLaneNumber)
        {
          uRequestedLanes = pDeviceCtx->sSinkDPCDCap.uMaxLaneCount;
          bFound          = TRUE;
        }
        else
        {
          for (uIndex = 0; uIndex < DPHOST_GET_LIST_SIZE(uSupportLaneCount); uIndex++)
          {
            if (uSupportLaneCount[uIndex] == pPropertyData->uLaneNumber)
            {
              uRequestedLanes = pPropertyData->uLaneNumber;
              bFound          = TRUE;
              break;
            }
          }
        }

        if (TRUE == bFound)
        {
          pDeviceCtx->uNumLanes                     = uRequestedLanes;
          pStreamCtx->uDirtyBits                   |= DP_DIRTYFIELD_SINK_ATTRIB |
                                                      DP_DIRTYFIELD_LANE_NUMBER |
                                                      DP_DIRTYFIELD_TU_PARAMETERS;
          TraceInfo(QdiTraceDP, "DP%d: DP_Host_SetProperty() setting lane count %d", pStreamCtx->eDisplayID, pPropertyData->uLaneNumber);
        }
        else
        {
          eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
          TraceInfo(QdiTraceDP, "DP%d: DP_Host_SetProperty() invalid lane count %d request", pStreamCtx->eDisplayID, pPropertyData->uLaneNumber);
        }

        break;
      }
      case DP_SETPROPERTY_PANEL_INFO:
      {
        /* Override existing modes with mode provided */
        pStreamCtx->uModeIndex = 0;
        pStreamCtx->uNumModes  = 1;

        DP_OSAL_MemCpy((void*)&pStreamCtx->sPanelInfo[pStreamCtx->uModeIndex], 
                       (void*)&(pPropertyData->sPanelInfo), 
                       sizeof(DP_PanelInfoType));
        
        pStreamCtx->uDirtyBits |= DP_DIRTYFIELD_SINK_ATTRIB    |
                                  DP_DIRTYFIELD_TU_PARAMETERS  |
                                  DP_DIRTYFIELD_MAINLINK_PACKET;
        break;
      }
      case DP_SETPROPERTY_PANEL_MODE_INDEX:
      {
        if (DP_MODESET_FLAG_UPDATEONLY & pPropertyData->sModeInfo.uFlags)
        {
          /* After bootup if mode index is invalid force it 0 as Post mode set operation*/
          if (DP_HOST_MODE_INVALID == pStreamCtx->uModeIndex)
          {
            DP_PanelInfoType   *psPanelInfo  = &(pStreamCtx->sPanelInfo[pPropertyData->sModeInfo.uModeIndex]);
            DP_PixelClk_Info    sPixClkInfo;

            DP_OSAL_MemSet((void *)&sPixClkInfo, 0, sizeof(DP_PixelClk_Info)); 

            // Set Mode index
            pStreamCtx->uModeIndex = pPropertyData->sModeInfo.uModeIndex;

            // Set default link params from DPCD
            pDeviceCtx->uLinkRateInKhz = pDeviceCtx->sSinkDPCDCap.uMaxLinkRateInKhz;
            pDeviceCtx->uNumLanes      = pDeviceCtx->sSinkDPCDCap.uMaxLaneCount;

            /* This path is only hit on bootup for eDP after UEFI has already configured the clocks
             * We still need to send main link clock frequency to clock driver so it can set the right voltages
             */
            if (DP_STATUS_SUCCESS == DP_CalculateLink(pDisplayCtx, &pDeviceCtx->sSinkDPCDCap, psPanelInfo, &sPixClkInfo))
            {   
              /* Configure the link clock */
              if (DP_STATUS_SUCCESS == DP_LinkClockEnable(pDisplayCtx, TRUE))
              {
                /* Set bLinkConfigured to TRUE as link won't be configured on bootup via DP_Host_SetMode for eDP */
                pDeviceCtx->bLinkConfigured = TRUE;
              }
              
              /* Configure the pixel clock */
              DP_PixelClockEnable(pDisplayCtx, &sPixClkInfo, TRUE);
            }
          }
        }
        else if (pPropertyData->sModeInfo.uModeIndex < pStreamCtx->uNumModes)
        {
          /* Updates the mode index as part of regular mode set operation */
          pStreamCtx->uModeIndex                     = pPropertyData->sModeInfo.uModeIndex;
          pStreamCtx->uDirtyBits                    |= DP_DIRTYFIELD_SINK_ATTRIB    |
                                                       DP_DIRTYFIELD_TU_PARAMETERS  |
                                                       DP_DIRTYFIELD_MAINLINK_PACKET|
                                                       DP_DIRTYFIELD_SETMODE;
        }
        else 
        {
          eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
        }
        break;
      }
      case DP_SETPROPERTY_LINK_TRAINING_TYPE:
      {
        pDeviceCtx->eLinkTrainingType             = pPropertyData->eLinkTrainingType;
        break;
      }
      case DP_SETPROPERTY_CONNECTION_STATUS:
      {
        // TODO: update stream context as well
        pDeviceCtx->bPluggedIn = pPropertyData->bConnected;

        // If cable is plugged out clear the edid flag
        if (FALSE == pDeviceCtx->bPluggedIn)
        {
          uint32 uStreamIndex;
          uint32 uMSTDisconnectedSinks = 0;

          // Mark the sink as not ready
          pStreamCtx->bEDIDObtained  = FALSE;
          pStreamCtx->bSinkConnected = FALSE;
          pDeviceCtx->bAuxReady      = FALSE;

          // Clear the cached link rate and lane counts
          pDeviceCtx->uLinkRateInKhz = 0;
          pDeviceCtx->uNumLanes      = 0;
          pStreamCtx->uDirtyBits    &= ~(DP_DIRTYFIELD_LINK_RATE | DP_DIRTYFIELD_LANE_NUMBER);

          // Set a hint for the next Open that unplug happened
          pDeviceCtx->uFlags         = DPHOST_SETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_UNPLUG_HPD_DETECTED);

          // Send Soft HPD interrupt from 2nd stream onwards
          // HPD for first stream comes as ACPI, USB events, or HPD interrupt
          for (uStreamIndex = 1; uStreamIndex < DP_MST_STREAM_ID_MAX; uStreamIndex++)
          {
            if (TRUE == pDeviceCtx->aStreamCtx[uStreamIndex].bInitialized)
            {
              if (DP_DEVICE_MODETYPE_DP == pDeviceCtx->eDeviceDPMode)
              {
                // Send HPD out for stream1 only for DP controller
                // HPD out for Alt-mode is issued from USB event
                DP_SoftHPDInterrupt(DP_GetDisplayMap(pDeviceCtx->eDeviceID, uStreamIndex), FALSE);
              }

              // Indicate which display has been disconnected
              pDeviceCtx->sMSTSinkHPDList[uMSTDisconnectedSinks].eDisplayID = DP_GetDisplayMap(pDeviceCtx->eDeviceID, uStreamIndex);
              pDeviceCtx->sMSTSinkHPDList[uMSTDisconnectedSinks].bHPDIn     = FALSE;
              uMSTDisconnectedSinks++;
            }
          }

          pDeviceCtx->uMSTSinkHPDCount = uMSTDisconnectedSinks;
        }
        break;
      }
      case DP_SETPROPERTY_INTERRUPT_ENABLE:
      {
        if (DP_CONTROLLER_ID_NONE != pDeviceCtx->eControllerID)
        {
          uint32 uHalInterruptList;

          /* Signals that can enable interrupt now during booting */
          if (pPropertyData->uInterruptList & DP_INTR_TYPE_HPD_UNPLUG_INT)
          {
            /* Setting flag to switch to interrupt driven mechanism for DP AUX wait */
            pDeviceCtx->uFlags |= DP_HOST_FLAG_AUX_INTERRUPT_DRIVEN;
          }

          // HPD for ALT Mode is not handled by controller. So mask them out.
          if ((TRUE == IsAltModeDPDevice(pDeviceCtx->eDeviceID)) &&
              (0 == DPHOST_GETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_ALT_MODE_FIXED_LANE_CONFIGURATION)))
          {
            pPropertyData->uInterruptList = DPHOST_CLEARFLAG(pPropertyData->uInterruptList, DP_INTR_TYPE_HPD_ALL);
          }

          // SST mode requires MISR to be enabled for FRAME_END interrupt
          if ((pPropertyData->uInterruptList & DP_INTR_TYPE_FRAME_END)  &&
              (FALSE == pDeviceCtx->bMSTEnabled))
          {
            HAL_DP_Enable_MISR(pDeviceCtx->eControllerID, TRUE);
          }

          uHalInterruptList = MapDPInterruptsToHAL(pDisplayCtx, pPropertyData->uInterruptList);
          HAL_DP_Interrupt_Enable(pDeviceCtx->eControllerID, uHalInterruptList, 0);
        }
        break;
      }
      case DP_SETPROPERTY_INTERRUPT_DISABLE:
      {
        // HW access should be done only we have a valid controller
        if(DP_CONTROLLER_ID_NONE != pDeviceCtx->eControllerID)
        {
          // Disable interrupts that are not sharing between streams within one controller.
          if (DP_STREAM_INTERRUPT_ALL & pPropertyData->uInterruptList)
          {
            uint32 uHalInterruptList = MapDPInterruptsToHAL(pDisplayCtx, pPropertyData->uInterruptList & DP_STREAM_INTERRUPT_ALL);

            HAL_DP_Interrupt_Disable(pDeviceCtx->eControllerID, uHalInterruptList, 0);
            
            pPropertyData->uInterruptList = DPHOST_CLEARFLAG(pPropertyData->uInterruptList, DP_STREAM_INTERRUPT_ALL);
          }

          // SST mode requires MISR to be enabled for FRAME_END interrupt
          if (pPropertyData->uInterruptList & DP_INTR_TYPE_FRAME_END)
          {
            // TODO: Dependency if MISR is being used for CRC or other scenarios
            HAL_DP_Enable_MISR(pDeviceCtx->eControllerID, FALSE);
          }

          // Disable interrupt only if just 1 stream connected to the controller.
          // If there are 2 active streams, we will keep the interrupt enabled, since it is used by other stream.
          // If there is 1 active stream, but stream is not connected, we should not disable interrupt, since it is used by other stream.
          if ((pDeviceCtx->uNumActiveStreams <= 1) &&
              (TRUE == pStreamCtx->bSinkConnected))
          {
            uint32 uHalInterruptList = MapDPInterruptsToHAL(pDisplayCtx, pPropertyData->uInterruptList);

            HAL_DP_Interrupt_Disable(pDeviceCtx->eControllerID, uHalInterruptList, 0);

            /* Disable the Aux Interrupt mechanism based on HPD unplug interrupt disable setting */
            if (pPropertyData->uInterruptList & DP_INTR_TYPE_HPD_UNPLUG_INT)
            {
              /* Setting flag to switch to interrupt driven mechanism for DP AUX wait */
              pDeviceCtx->uFlags &= ~DP_HOST_FLAG_AUX_INTERRUPT_DRIVEN;
            }
          }  
        }
        break;
      }
      case DP_SETPROPERTY_INTERRUPT_CLEAR:
      {
        uint32 uHalInterruptList = MapDPInterruptsToHAL(pDisplayCtx, pPropertyData->uInterruptList);

        HAL_DP_Interrupt_Clear(pDeviceCtx->eControllerID, uHalInterruptList, 0);
        
        break;
      }
      case DP_SETPROPERTY_AUDIO_CONFIG:
      {
        HAL_DP_AudioConfigType sAudioConfig;
        
        /* Configure DP audio engine */
        DP_OSAL_MemSet(&sAudioConfig, 0, sizeof(HAL_DP_AudioConfigType));
        sAudioConfig.bSSCMode             = ((pDeviceCtx->eSSCMode == MDP_DP_SSC_DISABLED) ? FALSE : TRUE);
        sAudioConfig.uLinkRateInKhz       = pDeviceCtx->uLinkRateInKhz;
        sAudioConfig.eMSTStreamID         = pStreamCtx->eMSTStreamId;
        sAudioConfig.eAudioFormat         = pPropertyData->sAudioParams.eAudioFormat;
        sAudioConfig.eAudioNumOfChannel   = pPropertyData->sAudioParams.eAudioNumOfChannel;
        sAudioConfig.eAudioSampleRate     = pPropertyData->sAudioParams.eAudioSampleRate;
        sAudioConfig.eAudioSampleBitDepth = pPropertyData->sAudioParams.eAudioSampleBitDepth;

        HAL_DP_AudioSetup(pDeviceCtx->eControllerID, &sAudioConfig);

        TraceInfo(QdiTraceDP, "DP%d: Audio config - format:%d, channels:%d, sample_rate:%d, bit_depth:%d",
             pStreamCtx->eDisplayID, 
             sAudioConfig.eAudioFormat,
             sAudioConfig.eAudioNumOfChannel,
             sAudioConfig.eAudioSampleRate,
             sAudioConfig.eAudioSampleBitDepth);

        break;
      }
      case DP_SETPROPERTY_AUDIO_ENABLE:
      {         
        HAL_DP_Audio_Enable(pDeviceCtx->eControllerID, pPropertyData->bEnabled);

        TraceInfo(QdiTraceDP, "DP%d: Audio config - streamEnabled: %d", pStreamCtx->eDisplayID, pPropertyData->bEnabled);

        break;
      }
      case DP_SETPROPERTY_LINK_CLOCK:
      {
        if (FALSE == pPropertyData->bEnabled)
        {
          /* Set the DP clocks source to CXO */
          DP_ParkLinkAndPixelClockSources(pDisplayCtx);
        }
        break;
      }
      case DP_SETPROPERTY_SIGNAL_EVENT:
      {
        DP_Status eDPLocalStatus = DP_STATUS_SUCCESS;

        if ((DP_EVENT_AUX_WAIT & pPropertyData->uInterruptList) && 
            (NULL != pDeviceCtx->hAuxReadyEvent))
        {
          if (MDP_STATUS_SUCCESS != DISP_OSAL_SetEvent(pDeviceCtx->hAuxReadyEvent))
          {
            /* Failed to signal the AUX event that interrupt has been fired */
            DP_LOG_MESSAGE_WARN("DP AUX EVENT set failed");
          }
        }

        if (TRUE == pDeviceCtx->bInitialized)
        {
          if (DP_EVENT_IRQ_HPD & pPropertyData->uInterruptList)
          {
            if (DP_STATUS_SUCCESS != (eDPLocalStatus = DP_LaunchWorkItem(pStreamCtx->hHPDWorkItem, IRQHPDWorkThread, pDisplayCtx)))
            {
              TraceInfo(QdiTraceDP, "DP%d: DP_LaunchWorkItem failed, eDPLocalStatus = %d", pStreamCtx->eDisplayID, eDPLocalStatus);
            }
          }

          if (DP_EVENT_REPLUG_HPD & pPropertyData->uInterruptList)
          {
            if (DP_STATUS_SUCCESS != (eDPLocalStatus = HandleReplugHPD(pDisplayCtx)))
            {
              TraceInfo(QdiTraceDP, "DP%d: HandleReplugHPD failed, eDPLocalStatus = %d", pStreamCtx->eDisplayID, eDPLocalStatus);
            }
          }
        }
        break;
      }
      case DP_SETPROPERTY_UPDATE_SINK_STATUS:
      {
        if (FALSE == pDeviceCtx->bInitialized)
        {
          TraceInfo(QdiTraceDP, "DP%d: skip sink status update since DP is not initialized", pStreamCtx->eDisplayID);
        }
       
        else 
        {
          if (TRUE == IsAltModeDPDevice(pDeviceCtx->eDeviceID))
          {

            // DP-TypeC (AltMode) IRQ_HPD is handled by generating a software interrupt.
            // Skip this path for the MiniDP IRQ_HPD as that is handed by the controller via an interrupt/DPC
            if (DP_STATUS_SUCCESS != (eStatus = HandleIrqHPD(pDisplayCtx)))
            {
              TraceInfo(QdiTraceDP, "DP%d: HandleIrqHPD failed, eStatus = %d", pStreamCtx->eDisplayID, eStatus);
            }
          }
        }
        break;
      }
      case DP_SETPROPERTY_PHY_POWER:
      {       
        HAL_MDSS_ErrorType ePHYPowerResult;
        
        // Log start of PHY and PLL enable/disable
        DISP_OSAL_EVENTLOG3(DISP_OSAL_EVENT_PLLPROGRAMMING_START, pDeviceCtx->eDeviceID, 0, (uint32)pPropertyData->sPHYPowerInfo.uModules);

        /* Power down DP PHY/PLL */
        if (HAL_MDSS_STATUS_SUCCESS != (ePHYPowerResult = HAL_DP_PHY_Power(pDeviceCtx->eDeviceID,
                                                                           pPropertyData->sPHYPowerInfo.bEnabled,
                                                                           pPropertyData->sPHYPowerInfo.uModules)))
        {
          DP_LOG_MESSAGE_ERROR("DP%d: HAL_DP_PHY_Power failed with error=%d DP_Host_SetProperty.\n", pStreamCtx->eDisplayID, ePHYPowerResult);
        }

        // Log end of PHY and PLL enable/disable
        DISP_OSAL_EVENTLOG3(DISP_OSAL_EVENT_PLLPROGRAMMING_END, pDeviceCtx->eDeviceID, ePHYPowerResult, (uint32)pPropertyData->sPHYPowerInfo.uModules);
        break;
      }
      case DP_SETPROPERTY_PSR_CONFIG:
      {
        if ((0 == DPHOST_GETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_DISABLE_PSR)) && 
            (DP_DEVICE_MODETYPE_EDP == pDeviceCtx->eDeviceDPMode))
        {
          eStatus = eDP_PSR_Request(pDisplayCtx, pPropertyData->ePSRRequest);
        }
        else
        {          
          DP_LOG_MESSAGE_ERROR("DP_Host_SetProperty: PSR not supported for DP%d", pDeviceCtx->eControllerID);
          eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
        }        
        break;
      }
      case DP_SETPROPERTY_GENERIC_SDP_CONFIG:
      {
        if ((pPropertyData->sGenericSDPCfg.uPayloadBytes > DP_GENERIC_SDP_PAYLOAD_BYTES_MAX) ||
            (NULL == pPropertyData->sGenericSDPCfg.pPayloadBuffer))
        {
          eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
        }
        else
        {
          HAL_DP_GenericSDPConfigType sGenericSDPCfg;

          DISP_OSAL_MemZero(&sGenericSDPCfg, sizeof(HAL_DP_GenericSDPConfigType));
          sGenericSDPCfg.uHB0          = pPropertyData->sGenericSDPCfg.uHB0;
          sGenericSDPCfg.uHB1          = pPropertyData->sGenericSDPCfg.uHB1;
          sGenericSDPCfg.uHB2          = pPropertyData->sGenericSDPCfg.uHB2;
          sGenericSDPCfg.uHB3          = pPropertyData->sGenericSDPCfg.uHB3;
          sGenericSDPCfg.uPayloadBytes = pPropertyData->sGenericSDPCfg.uPayloadBytes;
          sGenericSDPCfg.pSDPPayload   = pPropertyData->sGenericSDPCfg.pPayloadBuffer;

          HAL_DP_GenericSDP_Config(pDeviceCtx->eControllerID,
                                   pStreamCtx->eMSTStreamId,
                                   pPropertyData->sGenericSDPCfg.uSDPIndex,
                                   &sGenericSDPCfg);
        }
        break;
      }
      case DP_SETPROPERTY_GENERIC_SDP_ENABLE:
      {
        HAL_DP_GenericSDP_Enable(pDeviceCtx->eControllerID,
                                 pStreamCtx->eMSTStreamId,
                                 pPropertyData->sGenericSDPEnable.uSDPIndex,
                                 pPropertyData->sGenericSDPEnable.bEnabled);
        break;
      }
      case DP_SETPROPERTY_UPDATE_PPS:
      {
        if (pPropertyData->sDSCPPSParams.uSize < DP_PPS_BUFFER_SIZE)
        {
          DP_LOG_MESSAGE_ERROR("DP_Host_SetProperty: Insufficient PPS data (%d vs %d) on  DP%d", 
                               pPropertyData->sDSCPPSParams.uSize,
                               DP_PPS_BUFFER_SIZE,
                               pDeviceCtx->eControllerID);
          eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
        }
        else
        {
          HAL_DP_PPSConfigType sPPSConfig;

          // Send PPS
          DP_OSAL_MemSet(&sPPSConfig, 0, sizeof(HAL_DP_PPSConfigType));
          sPPSConfig.uStreamId    = pStreamCtx->eMSTStreamId;
          sPPSConfig.puPPSBuffer  = pPropertyData->sDSCPPSParams.pPPSBuffer;
          sPPSConfig.uBufferSize  = DP_PPS_BUFFER_SIZE;
       
          HAL_DP_DSC_SendPPS(pDeviceCtx->eControllerID, &sPPSConfig);
        }

        break;
      }
      case DP_SETPROPERTY_REFRESHRATE:
      {
        /* Update Refresh rate using Blanking Adjustment */

        uint32 uModeIndex           = pStreamCtx->uModeIndex;
        uint32 uOriginalRefreshRate = pStreamCtx->sPanelInfo[uModeIndex].uRefreshRate;
		
		// Variable only used for logging which may be disabled 
		UNREFERENCED_PARAMETER(uOriginalRefreshRate);
		
        if (pStreamCtx->uNumModes <= uModeIndex)
        {
          DP_LOG_MESSAGE_ERROR("DP_Host_SetProperty: DP_SETPROPERTY_REFRESHRATE failed, ModeIndex is invalid");
          eStatus = DP_STATUS_FAIL;
        }
        else 
        {
          pStreamCtx->sPanelInfo[uModeIndex].uVsyncBackPorchInLines     = pPropertyData->sPanelInfo.uVsyncBackPorchInLines;
          pStreamCtx->sPanelInfo[uModeIndex].uVsyncFrontPorchInLines    = pPropertyData->sPanelInfo.uVsyncFrontPorchInLines;
          pStreamCtx->sPanelInfo[uModeIndex].uVsyncPulseInLines         = pPropertyData->sPanelInfo.uVsyncPulseInLines;
          pStreamCtx->sPanelInfo[uModeIndex].uHsyncBackPorchInPixels    = pPropertyData->sPanelInfo.uHsyncBackPorchInPixels;
          pStreamCtx->sPanelInfo[uModeIndex].uHsyncPulseInPixels        = pPropertyData->sPanelInfo.uHsyncPulseInPixels;
          pStreamCtx->sPanelInfo[uModeIndex].uHsyncFrontPorchInPixels   = pPropertyData->sPanelInfo.uHsyncFrontPorchInPixels;
          pStreamCtx->sPanelInfo[uModeIndex].uRefreshRate               = pPropertyData->sPanelInfo.uRefreshRate;

          if (DP_STATUS_SUCCESS != (eStatus = DP_Host_Set_RefreshRate(pDisplayCtx, uModeIndex)))
          {
            DP_LOG_MESSAGE_ERROR("DP%d: DP_Host_SetProperty(REFRESH RATE) failed, status = %d\n", pStreamCtx->eDisplayID, eStatus);
          }
          else 
          {
            TraceInfo(QdiTraceDP, "DP%d: DP_Host_SetProperty(REFRESH RATE) Successful, Refresh rate changed from %dHz to %dHz ", 
            pStreamCtx->eDisplayID, ((uint32)(uOriginalRefreshRate >> 16)), ((uint32)(pPropertyData->sPanelInfo.uRefreshRate>> 16)));
          }
        }
        break;
      }
      case DP_SETPROPERTY_PRE_EMPHASIS_LEVEL:
      {
        
        if (pPropertyData->uPreEmphasisLevel <= pDeviceCtx->uMaxPreemphLvl)
        {
          pDeviceCtx->uPreEmphasisLevel             = pPropertyData->uPreEmphasisLevel;
          pStreamCtx->uDirtyBits                   |= DP_DIRTYFIELD_SINK_ATTRIB;
          TraceInfo(QdiTraceDP, "DP%d: DP_Host_SetProperty() setting pre emphasis level %d", pStreamCtx->eDisplayID, pPropertyData->uPreEmphasisLevel);
        }
        else
        {
          eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
          TraceInfo(QdiTraceDP, "DP%d: DP_Host_SetProperty() invalid pre emphasis level %d request", pStreamCtx->eDisplayID, pPropertyData->uPreEmphasisLevel);
        }
        break;
      }
      case DP_SETPROPERTY_VOLTAGE_SWING_LEVEL:
      {
        if (pPropertyData->uVoltageSwingLevel <= pDeviceCtx->uMaxVoltSwingLvl)
        {
          pDeviceCtx->uVoltageSwingLevel            = pPropertyData->uVoltageSwingLevel;
          pStreamCtx->uDirtyBits                   |= DP_DIRTYFIELD_SINK_ATTRIB;
          TraceInfo(QdiTraceDP, "DP%d: DP_Host_SetProperty() setting voltage swing level %d", pStreamCtx->eDisplayID, pPropertyData->uVoltageSwingLevel);
        }
        else
        {
          eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
          TraceInfo(QdiTraceDP, "DP%d: DP_Host_SetProperty() invalid voltage swing level %d request", pStreamCtx->eDisplayID, pPropertyData->uVoltageSwingLevel);
        }
        break;
      }
      case DP_SETPROPERTY_TEST_PATTERN:
      {
        if (pPropertyData->uTestPatternType < DP_PHY_TEST_PATTERN_MAX)
        {
          pDeviceCtx->ePhyTestPattern               = (DP_PHYTestPatternType)pPropertyData->uTestPatternType;
          // CTS tests require a reconfiguration of link & link training
          pDeviceCtx->bLinkConfigured               = FALSE;

          if (DP_PHY_TEST_PATTERN_NONE == pDeviceCtx->ePhyTestPattern)
          {
            pDeviceCtx->ePendingTestRequest          &= ~DP_TEST_PHY_PATTERN;
          }
          else
          {
            pDeviceCtx->ePendingTestRequest          |= DP_TEST_PHY_PATTERN;
          }

          TraceInfo(QdiTraceDP, "DP%d: DP_Host_SetProperty() setting test pattern %d", pStreamCtx->eDisplayID, pPropertyData->uTestPatternType);
        }
        else
        {
          eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
          TraceInfo(QdiTraceDP, "DP%d: DP_Host_SetProperty() invalid test pattern %d request", pStreamCtx->eDisplayID, pPropertyData->uTestPatternType);
        }
        break;
      }
      case DP_SETPROPERTY_WRITE:
      {
        WriteInfoType      *pWriteInfo  = &pPropertyData->sWriteInfo;
        DP_WritePacketType  sWritePacket;

        DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
        sWritePacket.eTransactionType  = pWriteInfo->eMode;
        sWritePacket.puWriteData       = pWriteInfo->pDataBuf;
        sWritePacket.uAddress          = pWriteInfo->uAddress;
        sWritePacket.uWriteDataSize    = *(pWriteInfo->pNumBytes);
        sWritePacket.uBytesWritten     = 0;
        sWritePacket.bQueueOnly        = FALSE;

        eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket);

        // Set the bytes written
        if (DP_STATUS_SUCCESS == eStatus)
        {
          *(pWriteInfo->pNumBytes) = sWritePacket.uBytesWritten;
        }
        break;
      }
      case DP_SETPROPERTY_MAIN_LINK_STATE:
      {
        // Updates the main link state to requested state.
        ConfigureMainLink(pDisplayCtx, pPropertyData->eLinkCommandtype);
        break;
      }
      case DP_SETPROPERTY_SIMULATION_MODE:
      {
        DP_DeviceCtxType *pSimDeviceCtx = DPHOST_GET_DEVICE_CTX_FROM_ID(pPropertyData->sSimulationInfo.eDeviceId);
        
        if (NULL != pSimDeviceCtx)
        {
          if (TRUE == pPropertyData->sSimulationInfo.bEnabled)
          {
            if (TRUE == SIM_LoadConfigFile((SIM_DeviceIDType)pPropertyData->sSimulationInfo.eDeviceId))
            {
              pSimDeviceCtx->uFlags = DPHOST_SETFLAG(pSimDeviceCtx->uFlags, DP_HOST_FLAG_SIMULATION_MODE);
            }
            else
            {
              eStatus = DP_STATUS_FAIL;
            }
          }
          else
          {
            pSimDeviceCtx->uFlags = DPHOST_CLEARFLAG(pSimDeviceCtx->uFlags, DP_HOST_FLAG_SIMULATION_MODE);
          }
        }
        else
        {
          eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
        }
        break;
      }
      case DP_SETPROPERTY_BRIGHTNESS_CONTROL:
      {
        switch(pPropertyData->sBrightnessInfo.eBrightnessRequest)
        {
          case DP_BRIGHTNESS_REQUEST_OFF:
          {
            eStatus = DP_WriteSinkBrightnessEnable(pDisplayCtx, FALSE);
            break;
          }
          case DP_BRIGHTNESS_REQUEST_ON:
          {
            eStatus = DP_WriteSinkBrightnessEnable(pDisplayCtx, TRUE);
            break;
          }
          case DP_BRIGHTNESS_REQUEST_LEVEL:
          {
            eStatus = DP_WriteSinkBrightnessLevel(pDisplayCtx, pPropertyData->sBrightnessInfo.fLevel, pPropertyData->sBrightnessInfo.uMillinits);
            break;
          }
          default:
          {
            eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
            DP_LOG_MESSAGE_ERROR("DP_SETPROPERTY_BRIGHTNESS_CONTROL - unknown request type %d for disp %d",
                                  pPropertyData->sBrightnessInfo.eBrightnessRequest, pStreamCtx->eDisplayID);
            break;
          }
        }
        break;
      }
      case DP_SETPROPERTY_RESET_PHY:
      {
        if ((pPropertyData->sPHYResetInfo.eDeviceID > DP_DEVICE_ID_NONE) &&
            (pPropertyData->sPHYResetInfo.eDeviceID < DP_DEVICE_MAX))
        {
          HAL_DP_PHY_Reset(pPropertyData->sPHYResetInfo.eDeviceID,
                           pPropertyData->sPHYResetInfo.ePHYResetFlag);
        }
        else
        {
          eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
        }     
        break;
      }
      case DP_SETPROPERTY_COLOR_SPACE:
      {
        // Set up the VSC SDP pakcet
        if (DP_RX_FEATURE_VSC_SDP_COLORIMETRY & pDeviceCtx->sSinkDPCDCap.eRxFeatureEnumList)
        {
          // Configure VSC SDP packet
          if (DP_STATUS_SUCCESS != (eStatus = SetVSCSDP(pDeviceCtx, pStreamCtx)))
          {
            DP_LOG_MESSAGE_WARN("DP_Host_SetProperty: Failed to set VSC SDP for colorimetry");
          }
        }
        break;
      }
      default:
      {
        eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
        DP_LOG_MESSAGE_ERROR("DP_Host_SetProperty: Invalid property");
        break;
      }
    }
  } 

  return eStatus;
}


/*********************************************************************************************
*
** FUNCTION: DP_Host_GetProperty()
*/
/*!
* \DESCRIPTION
*      Allows the user to query the attributes and properties of the DP device
*
* \param [in]   hHandle        - Logical handle of DP Device
* \param [in]   ePropertyType  - Property ID query
* \param [in]   pPropertyData  - parameters of the property that will be returned
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status DP_Host_GetProperty(DP_HandleType                   hHandle,
                              DP_GetPropertyType              ePropertyType,
                              DP_GetPropertyParamsType       *pPropertyData)
{
  DP_Status                  eStatus        = DP_STATUS_SUCCESS;
  DP_DisplayCtxType         *pDisplayCtx    = DPHOST_GETCTX_FROM_HANDLE(hHandle);
  DP_DeviceCtxType          *pDeviceCtx     = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType          *pStreamCtx     = DPHOST_GET_STREAM_CTX(pDisplayCtx);  

  if ((NULL == pPropertyData)|| 
      (NULL == pDeviceCtx)   ||
      (NULL == pStreamCtx))
  {
    DP_LOG_MESSAGE_ERROR("DP_Host_GetProperty: Null input");
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  } 
  else
  { 
    switch (ePropertyType)
    {
      case DP_GETPROPERTY_GET_MODE_INFO:
      {        
        /* If EDID has been read from sink successfully */
        if ((TRUE == pStreamCtx->bEDIDObtained) &&
            (pPropertyData->sPanelInfo.uModeIndex < pStreamCtx->uNumModes))
        {
          /* Return selected mode info */
          DP_OSAL_MemCpy(&pPropertyData->sPanelInfo, 
                          &pStreamCtx->sPanelInfo[pPropertyData->sPanelInfo.uModeIndex], 
                          sizeof(DP_PanelInfoType));
          
          eStatus = DP_STATUS_SUCCESS;
        }
        else
        {
          eStatus = DP_STATUS_FAILED_RESOURCE_NOT_READY;
        }
        break;
      }
      case DP_GETPROPERTY_LANE_NUMBER:
      {        
        pPropertyData->uLaneNumber = pDeviceCtx->uNumLanes;
        break;
      }
      case DP_GETPROPERTY_LINK_RATE:
      {
        pPropertyData->uLinkRateInKhz = pDeviceCtx->uLinkRateInKhz;
        break;
      }      
      case DP_GETPROPERTY_CONNECTION_STATUS:
      {
        /* The connection status will be continuously polled by the OS during plug-in events */
        if ((TRUE == pDeviceCtx->bPluggedIn)     &&
            (TRUE == pStreamCtx->bSinkConnected) &&
            (TRUE == pStreamCtx->bEDIDObtained))
        {
          /* Report TRUE when a connection is made with at least one sink.
           * Ensure EDID has also been read to avoid reporting a missing or incomplete EDID during DP_GETPROPERTY_EDID_INFO */
          pPropertyData->bPluggedIn = TRUE;
        }
        else
        {
          pPropertyData->bPluggedIn = FALSE;
        }
        break;
      }
      case DP_GETPROPERTY_EDID_INFO:
      {
        if (pDeviceCtx->bPluggedIn && pStreamCtx->bSinkConnected)
        {
          uint32   uCopyLength = pStreamCtx->uEDIDDataLength;

          if (pPropertyData->sEdidInfo.uDataLength)
          {
            if (pPropertyData->sEdidInfo.uDataLength < uCopyLength)
            {
              uCopyLength = pPropertyData->sEdidInfo.uDataLength;
            }
          }

          if (pPropertyData->sEdidInfo.pDataBuf)
          {
            DISP_OSAL_MemCpyEx(pPropertyData->sEdidInfo.pDataBuf, uCopyLength, &(pStreamCtx->auEDIDCache), uCopyLength);
            eStatus = DP_STATUS_SUCCESS;
          }
          pPropertyData->sEdidInfo.uDataLength = uCopyLength;
        }
        else
        {
          eStatus = DP_STATUS_FAILED_RESOURCE_NOT_READY;
          DP_LOG_MESSAGE_WARN("DP_Host_GetProperty: Not supported");
        }
        break;
      }
      case DP_GETPROPERTY_INTERRUPT_STATUS:
      {
        HAL_DP_InterruptType eInterruptList = 0;

        HAL_DP_Interrupt_GetStatus(pDeviceCtx->eControllerID, &eInterruptList, 0);
        pPropertyData->uInterruptList = MapHALInterruptsToDP(pDisplayCtx, eInterruptList);

        break;
      }
      case DP_GETPROPERTY_AUDIO_MODE_INFO:
      {
        uint32 uModeIndex = pPropertyData->psAudioModeInfo->uAudioModeIndex;

        if (uModeIndex >= pStreamCtx->uNumberOfAudioModes)
        {
          eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
        }
        else
        {
          uint32 uCopyLen = sizeof(DP_AudioModeInfoPropType);

          DISP_OSAL_MemCpyEx(pPropertyData->psAudioModeInfo, uCopyLen, &(pStreamCtx->sAudioModeInfo[uModeIndex]), uCopyLen);
        }
        break;
      }
      case DP_GETPROPERTY_VENDOR_SPECIFIC_INFO:
      {
        DISP_OSAL_MemCpyEx(&(pPropertyData->sVendorInfo), sizeof(DP_VendorInfoType), &(pStreamCtx->sVendorInfo), sizeof(DP_VendorInfoType));
        break;
      }
      case DP_GETPROPERTY_ROUTING_INFO:
      {
        // Relation between 'uControllerId' and 'eControllerID' is uControllerId = eControllerID - 1. 
        // uControllerId 0 and 1 maps to DP0 and DP1 respectively.
        if (DP_CONTROLLER_ID_NONE != pDeviceCtx->eControllerID )
        {
          pPropertyData->sRoutingInfo.uControllerId  = pDeviceCtx->eControllerID - 1;
          
          if (TRUE == pDeviceCtx->bMSTEnabled)
          {
            pPropertyData->sRoutingInfo.uStreamId = pStreamCtx->eMSTStreamId;
          }
          else
          {
            // If it is not MST, default to stream ID 0
            pPropertyData->sRoutingInfo.uStreamId = 0;
          }
        }
        else
        {
          DP_LOG_MESSAGE_WARN("DP_Host_GetProperty: Controller not initialized for DP Device id - %d", pDeviceCtx->eDeviceID);
          eStatus = DP_STATUS_FAILED_DRIVER_NOT_INITIALIZED;
        }
        break;
      }
      case DP_GETPROPERTY_SINK_STATUS:
      {
        pPropertyData->sSinkStatus.bLinkLost  = pDeviceCtx->bLinkLost;
        pPropertyData->sSinkStatus.bPluggedIn = pDeviceCtx->bPluggedIn;

        if (pPropertyData->sSinkStatus.uFlags & PANELSINKSTATUS_SINK_COUNT_FLAG)
        {
          // Caller will issue an HPD IN on connected sinks
          uint32 uDisplayCount;

          for (uDisplayCount = 0; (uDisplayCount < DP_MAX_HPD_LIST_SIZE) && (uDisplayCount < pDeviceCtx->uMSTSinkHPDCount); uDisplayCount++)
          {
            pPropertyData->sSinkStatus.sSinkList[uDisplayCount].eDisplayId = pDeviceCtx->sMSTSinkHPDList[uDisplayCount].eDisplayID;
            pPropertyData->sSinkStatus.sSinkList[uDisplayCount].bHDPIn     = pDeviceCtx->sMSTSinkHPDList[uDisplayCount].bHPDIn;

            // Clear the cache once sink info has been reported
            pDeviceCtx->sMSTSinkHPDList[uDisplayCount].eDisplayID             = MDP_DISPLAY_MAX;
          }

          pPropertyData->sSinkStatus.uSinkCount = uDisplayCount;

          // Clear the cached sink count once sink added info has been reported
          pDeviceCtx->uMSTSinkHPDCount = 0;
        }
        break;
      }
      case DP_GETPROPERTY_DSC_INFO:
      {
        DP_OSAL_MemCpy(&pPropertyData->sDSCInfo, &pStreamCtx->sDSCInfo, sizeof(DP_DSCInfoType));
        break;
      }
      case DP_GETPROPERTY_STREAM_INFO:
      {
        // Relation between 'uControllerId' and 'eControllerID' is uControllerId = eControllerID - 1. 
        // uControllerId 0 and 1 maps to DP0 and DP1 respectively.
        if ((pDeviceCtx->eControllerID != DP_CONTROLLER_ID_NONE) &&
            (TRUE == pDeviceCtx->bMSTEnabled))
        {
          pPropertyData->sStreamInfo.uVirtualChannelId  = pStreamCtx->uVirtualChannelId;
        }
        else
        {
          DP_LOG_MESSAGE_WARN("DP_Host_GetProperty: Stream virtual id not initialized for DP Device id - %d", pDeviceCtx->eDeviceID);
          eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
        }
        break;
      }
      case DP_GETPROPERTY_REFRESHRATE:
      {
        uint32 uModeIndex = pStreamCtx->uModeIndex;

        if (MAX_DP_PANEL_MODE <= uModeIndex)
        {
          DP_LOG_MESSAGE_ERROR("DP_Host_GetProperty: DP_GETPROPERTY_REFRESHRATE failed, ModeIndex is invalid for DP Device id - %d", pDeviceCtx->eDeviceID);
          eStatus = DP_STATUS_FAIL;
        }
        else 
        {
          pPropertyData->sPanelInfo.uRefreshRate = pStreamCtx->sPanelInfo[uModeIndex].uRefreshRate;
        }
        break;
      }
      case DP_GETPROPERTY_DISPLAY_RANGE_INFO:
      {
        
        if ((0 == pDeviceCtx->uMaxRefreshRate) &&
            (0 == pDeviceCtx->uMinRefreshRate))
        {
          eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
        }
        else 
        {
          pPropertyData->sRefreshRateRangeInfo.uMaxRefreshRate = pDeviceCtx->uMaxRefreshRate;
          pPropertyData->sRefreshRateRangeInfo.uMinRefreshRate = pDeviceCtx->uMinRefreshRate;
        }
        break;
      }
      case DP_GETPROPERTY_READ:
      {
        ReadInfoType      *pReadInfo = &pPropertyData->sReadInfo;
        DP_ReadPacketType  sReadPacket;

        DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
        sReadPacket.eTransactionType  = pReadInfo->eMode;
        sReadPacket.puReadDataBuffer  = pReadInfo->pDataBuf;
        sReadPacket.uAddress          = pReadInfo->uAddress;
        sReadPacket.uReadSize         = *(pReadInfo->pNumBytes);
        sReadPacket.uBytesRead        = 0;
        sReadPacket.bQueueOnly        = FALSE;

        eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket);

        // Set the read byte size
        if (DP_STATUS_SUCCESS == eStatus)
        {
          *(pReadInfo->pNumBytes) = sReadPacket.uBytesRead;
        }
        break;
      }
      case DP_GETPROPERTY_TOPOPLOGY_CHANGED:
      {
        // Only report topology change on DFP_D(Downstream Facing PORT) of MST dongle when UFP_D(Upstream Facing Port) of MST dongle is still connected, 
        if (TRUE == pDeviceCtx->bPluggedIn)
        {
          pPropertyData->bTopologyChanged = (pDeviceCtx->uFlags & DP_HOST_FLAG_TOPOLOGY_UPDATED) ? TRUE : FALSE;
        }
        else
        {
          pPropertyData->bTopologyChanged = FALSE;
        }
        break;
      }
      case DP_GETPROPERTY_PSR_CONFIG:
      {
        if ((0 == DPHOST_GETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_DISABLE_PSR)) &&
            (DP_DEVICE_MODETYPE_EDP == pDeviceCtx->eDeviceDPMode))
        {
          pPropertyData->ePSRState = pDeviceCtx->ePSRState;
        }
        else
        {          
          pPropertyData->ePSRState = DP_PSR_REQUEST_NONE;
        }        
        break;      
      }
      case DP_GETPROPERTY_PRE_EMPHASIS_LEVEL:
      {
         pPropertyData->uPreEmphasisLevel[0] = pDeviceCtx->uPreEmphasisLevel;
         pPropertyData->uPreEmphasisLevel[1] = pDeviceCtx->uMaxPreemphLvl;      
         break;
      }
      case DP_GETPROPERTY_VOLTAGE_SWING_LEVEL:
      {
         pPropertyData->uVoltageSwingLevel[0] = pDeviceCtx->uVoltageSwingLevel;
         pPropertyData->uVoltageSwingLevel[1] = pDeviceCtx->uMaxVoltSwingLvl;
         break;
      }
      case DP_GETPROPERTY_DPCD_CAPS_INFO:
      {
          uint32   uCopyLength = sizeof(DP_DPCDSinkCapRawDataType);

          if (pPropertyData->sDPCDInfo.uDataLength)
          {
            if (pPropertyData->sDPCDInfo.uDataLength < uCopyLength)
            {
              uCopyLength = pPropertyData->sDPCDInfo.uDataLength;
            }
          }

          if (pPropertyData->sDPCDInfo.pDataBuf)
          {
            DISP_OSAL_MemCpyEx(pPropertyData->sDPCDInfo.pDataBuf, uCopyLength, &(pDeviceCtx->sDPCDCapRawData), uCopyLength);
            eStatus = DP_STATUS_SUCCESS;
          }
          pPropertyData->sDPCDInfo.uDataLength = uCopyLength;
         break;
      }
      case DP_GETPROPERTY_AUX_FAILSAFE_MODE:
      {
        pPropertyData->bEnabled = DPHOST_GETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_AUX_FAILSAFE) ? TRUE : FALSE;
        break;
      }
      case DP_GETPROPERTY_DEVICE_SPECIFIC_INFO:
      {
        uint32   uCopyLength = sizeof(DP_DeviceSpecificInfoType);

        DISP_OSAL_MemCpyEx(&pPropertyData->sDeviceSpecificInfo[DP_DEVICESPECIFIC_SINK],
                           uCopyLength,
                           &pStreamCtx->sDeviceSpecificInfo[DP_DEVICESPECIFIC_SINK], 
                           uCopyLength);
        DISP_OSAL_MemCpyEx(&pPropertyData->sDeviceSpecificInfo[DP_DEVICESPECIFIC_BRANCH],
                           uCopyLength,
                           &pStreamCtx->sDeviceSpecificInfo[DP_DEVICESPECIFIC_BRANCH],
                           uCopyLength);

        eStatus = DP_STATUS_SUCCESS;
        break;
      }
      case DP_GETPROPERTY_FRAME_CRC:
      {
         if (HAL_MDSS_STATUS_SUCCESS != HAL_DP_Get_Frame_CRC(pDeviceCtx->eControllerID, &pPropertyData->uCRC))
         {
            eStatus = DP_STATUS_FAILED_TIMEOUT;
         }
         break;
      }
      default:
      {
        DP_LOG_MESSAGE_ERROR("DP_Host_GetProperty: Not supported");
        eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
        break;
      }      
    }
  }
  
  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_GetDisplayMap()
*/
/*!
* \DESCRIPTION
*     Retrieve display ID using device and stream ID
*
* \param [in]   eDeviceID        - Device ID
* \param [in]   eStreamID        - Stream ID

*
* \retval QDI Display ID
*
**********************************************************************************************/
MDP_Display_IDType DP_GetDisplayMap(DP_DeviceIDType eDeviceID, DP_MSTStreamIDType eStreamID)
{
  MDP_Display_IDType eDisplayID = MDP_DISPLAY_EXTERNAL; // Default to EXTERNAL

  if ((eDeviceID < DP_DEVICE_MAX) && 
      (eStreamID < DP_MST_STREAM_ID_MAX))
  {
    eDisplayID = sMSTDisplayMap[eDeviceID][eStreamID];
  }

  return eDisplayID;
}


/*---------------------------------------------------------------------------------------------------------------------
 * Private Functions
 *---------------------------------------------------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------- 
*
** FUNCTION: AllocateDPController()
*/
/*!
* \DESCRIPTION
*     Map DP_DeviceIDType to DP_ControllerIDType. For external displays,
*     dynamically allocate controller. 
*
* \param [in]   eDeviceID         - Device ID
* \param [in]   pDeviceCtx        - Device context 
*
* \retval DP Controller ID
*
**********************************************************************************************/
static DP_ControllerIDType AllocateDPController(DP_DeviceIDType   eDeviceID,
                                                DP_DeviceCtxType *pDeviceCtx)
{
  DP_ControllerIDType      eControllerID   = DP_CONTROLLER_ID_NONE;

  if (NULL == pDeviceCtx)
  {
    DP_LOG_MESSAGE_ERROR("AllocateDPController: Unexpected null context.");
  }
  else if (DP_CONTROLLER_ID_NONE != pDeviceCtx->eControllerID)
  {
    // Controller already allocated, no need to re-allocate
    eControllerID = pDeviceCtx->eControllerID;
  }
  else
  {
    DP_ControllerIDType ControllerDeviceIdMap[DP_DEVICE_MAX] = 
    {
      DP_CONTROLLER_ID_NONE, // DP_DEVICE_ID_NONE
      DP_CONTROLLER_ID_DP_0, // DP_DEVICE_ID_ALT_MODE_0
      DP_CONTROLLER_ID_DP_1, // DP_DEVICE_ID_ALT_MODE_1
      DP_CONTROLLER_ID_DP_2, // DP_DEVICE_ID_ALT_MODE_2
      DP_CONTROLLER_ID_DP_3, // DP_DEVICE_ID_EDP
    };

    eControllerID  = (pDeviceCtx->eDeviceID < DP_DEVICE_MAX) ? ControllerDeviceIdMap[pDeviceCtx->eDeviceID] : DP_CONTROLLER_ID_NONE;
  }

  return eControllerID;
}

/* ---------------------------------------------------------------------- 
*
** FUNCTION: FreeDPController()
*/
/*!
* \DESCRIPTION
*     Release the controller back to controller pool. 
*
* \param [in]   pDeviceCtx        - Device context 
*
* \retval 
*
************************************************************************/
static void FreeDPController(DP_DeviceCtxType *pDeviceCtx)
{
  if (NULL == pDeviceCtx)
  {
    DP_LOG_MESSAGE_ERROR("FreeDPController: Unexpected null context.");
  }
  else
  {
    pDeviceCtx->eControllerID = DP_CONTROLLER_ID_NONE;
  }
}


/* ---------------------------------------------------------------------- 
*
** FUNCTION: CloseDeviceContext()
*/
/*!
* \DESCRIPTION
*     Clean up the device context.
*
* \param [in]   pDeviceCtx        - Device context 
*
* \retval None
*
************************************************************************/
void CloseDeviceContext(DP_DeviceCtxType  *pDeviceCtx)
{
  if (NULL != pDeviceCtx->hAuxAccessLock)
  {
    /* Destroy DPCD lock event */
    DISP_OSAL_DestroyLockEvent(&pDeviceCtx->hAuxAccessLock);
  }
  
  if (NULL != pDeviceCtx->hAuxReadyEvent)
  {
    /* Destroy AUX transaction wait event */
    DISP_OSAL_DestroyEvent(&pDeviceCtx->hAuxReadyEvent);
  }
  
  pDeviceCtx->bInitialized                  = FALSE;
  pDeviceCtx->bLinkConfigured               = FALSE;
  // Clear the port status, topology status and simulation flag.
  // If panel not detected earlier, that will give a chance to
  // discover the panel again on resume
  pDeviceCtx->uFlags                        = DPHOST_CLEARFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_DS_PORT_STATUS_CHANGED |
                                                                                   DP_HOST_FLAG_TOPOLOGY_UPDATED       |
                                                                                   DP_HOST_FLAG_AUX_FAILSAFE         |
                                                                                   DP_HOST_FLAG_UNPLUG_HPD_DETECTED);
  pDeviceCtx->uDeviceServiceIRQVector       = 0;
  pDeviceCtx->uSinkCount                    = 0;
  pDeviceCtx->bLinkLost                     = TRUE;
}

/*********************************************************************************************
*
** FUNCTION: ReadModeInfoFromSink()
*/
/*!
* \DESCRIPTION
*     Retrieve modes from EDID of DP sink
*
* \param [in]   pDisplayCtx        - Pointer to context
*
* \retval DP_Status
*
**********************************************************************************************/
static DP_Status ReadModeInfoFromSink(DP_DisplayCtxType    *pDisplayCtx)
{
  DP_Status                 eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType         *pDeviceCtx;
  DP_StreamCtxType         *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) ||
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("ReadModeInfoFromSink: Unexpected null context.");
  }
  else
  {
    // Set link rate & num of lanes to Use DPCD limits only if no overrides (from previous link training for instance) 
    // These values will be used to filter modes while parsing EDID
    
    if (0 == (pStreamCtx->uDirtyBits & DP_DIRTYFIELD_LINK_RATE))
    {      
      pDeviceCtx->uLinkRateInKhz = pDeviceCtx->sSinkDPCDCap.uMaxLinkRateInKhz;
    }
    
    if (0 == (pStreamCtx->uDirtyBits & DP_DIRTYFIELD_LANE_NUMBER))
    {
      pDeviceCtx->uNumLanes = pDeviceCtx->sSinkDPCDCap.uMaxLaneCount;
    }
    
    if (DP_STATUS_SUCCESS != (eStatus = DP_ReadSinkEDIDRaw(pDisplayCtx)))
    {
      DP_LOG_MESSAGE_ERROR("DP_ReadSinkEDIDRaw failed (eStatus = 0x%x): overriding with fail-safe", eStatus);
        
      eStatus = DP_SetFailSafeEDID(pDisplayCtx);
    }
    else if (DP_STATUS_SUCCESS != (eStatus = DP_ParseSinkEDID(pDisplayCtx)))
    {
      DP_LOG_MESSAGE_ERROR("ReadModeInfoFromSink: DP_ParseSinkEDID failed, eStatus = 0x%x", eStatus);
    }
    
    if (DP_STATUS_SUCCESS == eStatus)
    {
      pStreamCtx->bEDIDObtained  = TRUE;
      pStreamCtx->uDirtyBits    &= ~(DP_DIRTYFIELD_LINK_RATE | DP_DIRTYFIELD_LANE_NUMBER);
    }
  }

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: LinkRateReduce()
*/
/*!
* \DESCRIPTION
*     Reduce link rate if link training for higher link rate failed
*
* \param [in]   pDisplayCtx        - Pointer to context
*
* \retval DP_Status
*
**********************************************************************************************/
static DP_Status LinkRateReduce(DP_DisplayCtxType    *pDisplayCtx)
{
  DP_Status                 eStatus     = DP_STATUS_SUCCESS; 
  DP_DeviceCtxType         *pDeviceCtx  = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType         *pStreamCtx  = DPHOST_GET_STREAM_CTX(pDisplayCtx); 

  if ((NULL == pDeviceCtx) || 
      (NULL == pStreamCtx))
  {
    DP_LOG_MESSAGE_ERROR("LinkRateReduce: unexpected null handle ");
    eStatus = DP_STATUS_FAILED_DRIVER_NOT_INITIALIZED;
  }
  else
  { 
    uint32                    uLinkRateInKhz = 0;
    
    switch (pDeviceCtx->uLinkRateInKhz)
    {
      case DP_LINK_SYMBOL_RATE_KHZ_PER_LANE_810MBps:
      {
        uLinkRateInKhz = DP_LINK_SYMBOL_RATE_KHZ_PER_LANE_540MBps;
        break;
      }
      case DP_LINK_SYMBOL_RATE_KHZ_PER_LANE_540MBps:
      {
        uLinkRateInKhz = DP_LINK_SYMBOL_RATE_KHZ_PER_LANE_270MBps;
        break;
      }
      case DP_LINK_SYMBOL_RATE_KHZ_PER_LANE_270MBps:
      {
        uLinkRateInKhz = DP_LINK_SYMBOL_RATE_KHZ_PER_LANE_162MBps;
        break;
      }
      default:
      {
        eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
      }
    }

    if (DP_STATUS_SUCCESS == eStatus) 
    {
      // Set link-rate bit to prevent updating link rate elsewhere
      pDeviceCtx->uLinkRateInKhz  =  uLinkRateInKhz;
      pStreamCtx->uDirtyBits     |=  DP_DIRTYFIELD_LINK_RATE;
    }
    else
    {
      // Clear link-rate bit to indicate that it is modifiable (training failed at this linkrate)
      pStreamCtx->uDirtyBits     &= ~DP_DIRTYFIELD_LINK_RATE;
    }
  }

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: LaneCountReduce()
*/
/*!
* \DESCRIPTION
*     Reduce lane count to the number of lanes that were successfully trained (CR done)
*
* \param [in]   pDisplayCtx        - Pointer to context
*
* \retval DP_Status
*
**********************************************************************************************/
static DP_Status LaneCountReduce(DP_DisplayCtxType* pDisplayCtx)
{
  DP_Status                 eStatus         = DP_STATUS_FAILED_NOT_SUPPORTED;
  bool32                    bDone           = FALSE;
  DP_DeviceCtxType*         pDeviceCtx      = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType*         pStreamCtx      = DPHOST_GET_STREAM_CTX(pDisplayCtx);
  DP_DPCDSinkStatusType     sSinkDPCDStatus;

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx))
  {
    DP_LOG_MESSAGE_ERROR("LaneCountReduce: unexpected null handle ");
  }
  else if (DP_STATUS_SUCCESS == (eStatus = DP_ReadSinkDPCDStatus(pDisplayCtx, &sSinkDPCDStatus, DP_AUX_TRANSACTION_AUX_WAIT_STALL_FLAG)))
  {
    // Using DP_CheckTrainingResult() we check which lanes' CR bit is set
    if (4 == pDeviceCtx->uNumLanes)
    {
      pDeviceCtx->uNumLanes = 2;
      bDone = DP_CheckTrainingResult(pDisplayCtx, &sSinkDPCDStatus, DP_LINK_TRAINING_STATUS_CLK_RECOVERY_DONE);
    }
    if ((2     == pDeviceCtx->uNumLanes) &&
        (FALSE == bDone))
    {
      pDeviceCtx->uNumLanes = 1;
      bDone = DP_CheckTrainingResult(pDisplayCtx, &sSinkDPCDStatus, DP_LINK_TRAINING_STATUS_CLK_RECOVERY_DONE);
    }

    if (TRUE == bDone)
    {
      // Set lane-number bit to prevent updating number of lanes elsewhere
      pStreamCtx->uDirtyBits    |=  DP_DIRTYFIELD_LANE_NUMBER;
      eStatus                    =  DP_STATUS_SUCCESS; 
    }
    else
    {
      // Clear lane-number bit to indicate that it is modifiable (all lanes set, weren't trained)
      pStreamCtx->uDirtyBits    &= ~DP_DIRTYFIELD_LANE_NUMBER;
      eStatus                    = DP_STATUS_FAILED_LINK_TRAINING;
    }
  }

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: VerifyLinkBandwidth()
*/
/*!
* \DESCRIPTION
*     Verify if link rate can support the request mode by comparing the bit rates
*     Comparison of LinkBitRate and ModeBitRate is in bits per second
*
* \param [in]   pDisplayCtx        - Pointer to context
* \param [in]   uLinkRateInKhz     - Updated link rate to check the mode against
*
* \retval DP_Status
*
**********************************************************************************************/
static DP_Status VerifyLinkBandwidth(DP_DisplayCtxType* pDisplayCtx)
{
  DP_Status              eStatus    = DP_STATUS_SUCCESS;
  DP_DeviceCtxType*      pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType*      pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx);

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx))
  {
    DP_LOG_MESSAGE_ERROR("VerifyLinkBandwidth: unexpected null handle ");
    eStatus = DP_STATUS_FAILED_DRIVER_NOT_INITIALIZED;
  }
  else
  {
    DP_PanelInfoType* psPanelInfo    = &(pStreamCtx->sPanelInfo[pStreamCtx->uModeIndex]);

    // Check if the queried link rate can support the requested mode
    uint64 uModeBitRate = (uint64)psPanelInfo->uPclkFreq * pStreamCtx->uBitDepth * 3;      //  1 pix = 3 * bpc
    uint64 uLinkBitRate = DP_GetMaxAvailableBw(pDisplayCtx);

    // Adjust mode bit rate if DSC is enabled
    if (pStreamCtx->sDSCInfo.bDSCEnabled)
    {
      uModeBitRate /= pStreamCtx->sDSCInfo.uCompressionRatio;
    }

    if (uModeBitRate > uLinkBitRate)
    {
      TraceInfo(QdiTraceDP, "DP%d: Link bandwidth cannot support this mode (Pclk: %dHz, Link rate: %dKhz with %d lanes) ",
                             pDeviceCtx->eControllerID,
                             psPanelInfo->uPclkFreq,
                             pDeviceCtx->uLinkRateInKhz,
                             pDeviceCtx->uNumLanes);

      eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
    }
  }

  return eStatus;
}
/*********************************************************************************************
*
** FUNCTION: CheckPhyPatternStatus()
*/
/*!
* \DESCRIPTION
*     Function to confirm the mainlink is in the correct state for test patterns.
*
* \param [in]   eDisplayID         - Display Id
* \param [in]   eControllerID      - Controller Id
* \param [in]   eLinkStatus        - Link status to check
*
* \retval bool32 - TRUE if hardware is in the requested state.
*
**********************************************************************************************/
static bool32 CheckPhyPatternStatus(MDP_Display_IDType    eDisplayID,
                                    DP_ControllerIDType   eControllerID,
                                    HAL_DP_LinkStatusType eLinkStatus)
{
  bool32 bResult    = FALSE;
  uint32 uRetry;

  // Hardware can take up to one full frame to report the state change in the mainlink status
  for (uRetry = 0;uRetry < (DP_MAX_LINK_STATE_CHANGE_WAIT_US/DP_STATE_CHANGE_POLL_TIME_US);uRetry++)
  {
    uint32 uLinkStatus = HAL_DP_Mainlink_Status(eControllerID);

    if (eLinkStatus & uLinkStatus)
    {
      TraceInfo(QdiTraceDP, "DP%d: CheckPhyPatternStatus: Mainlink took %dms to transition to state 0x%x", eDisplayID, (uRetry*DP_STATE_CHANGE_POLL_TIME_US)/1000, eLinkStatus);
      bResult = TRUE;
      break;
    }
    else
    {
      DISP_OSAL_StallUs(DP_STATE_CHANGE_POLL_TIME_US);
    }
  }

  return bResult;
}
                                     
/*********************************************************************************************
*
** FUNCTION: SetPHYTestPattern()
*/
/*!
* \DESCRIPTION
*     Set up DP PHY test pattern for PHY CTS
*    
*     DPCD 248h PHY_TEST_PATTERN
*
*     0] 000b No pattern
*     1] 001b D10.2 without scrambling
*     2] 010b Symbol error measurement count
*     3] 011b PRBS7 
*     4] 100b 80bit custom pattern
*     5] 101b CP2520 Pattern1 (HBR2 Compliance EYE pattern)
*     6] 110b CP2520 Pattern2
*     7] 111b CP2520 Pattern3 (TPS4)
*
*   
* \param [in]   eDisplayID         - Display  Id
* \param [in]   eControllerID      - Controller Id
* \param [in]   ePhyTestPattern    - Test pattern
*
* \retval DP_Status
*
**********************************************************************************************/
static DP_Status SetPHYTestPattern(MDP_Display_IDType    eDisplayID,
                                   DP_ControllerIDType   eControllerID,
                                   DP_PHYTestPatternType ePhyTestPattern)
{
  DP_Status           eStatus            = DP_STATUS_SUCCESS; 
  uint32              uIdlePatternRepNum = DP_IDLE_PATTERN_REP_NUM;
  HAL_DP_OptionalType sDPOptionCfg;
     
  TraceInfo(QdiTraceDP, "DP%d: SetPHYTestPattern setting PHY Test Pattern 0x%x", eDisplayID, ePhyTestPattern);

  // Hardware must be in IDLE before it can enable patterns, ensure we are in the correct state.  IDLE_PATTERN2 indicates a SW requested idle pattern.
  if (FALSE == CheckPhyPatternStatus(eDisplayID, eControllerID, HAL_DP_LINKSTATUS_TYPE_SENDING_IDLE_PATTERN2))
  {
    uint32 uHBR2ComplianceScramblerReset = 0;
  
    // Reset scramber configuration HBR2 ERM            
    DP_OSAL_MemSet(&sDPOptionCfg, 0, sizeof(HAL_DP_OptionalType));
    sDPOptionCfg.puHBR2ComplianceScramblerReset = &uHBR2ComplianceScramblerReset;
    uHBR2ComplianceScramblerReset               = 0;
    HAL_DP_SetOptionalConfig(eControllerID, &sDPOptionCfg);
  
    // Reset default idle pattern time
    DP_OSAL_MemSet(&sDPOptionCfg, 0, sizeof(HAL_DP_OptionalType));
    sDPOptionCfg.puIdlePatternRepNum  = &uIdlePatternRepNum;
    HAL_DP_SetOptionalConfig(eControllerID, &sDPOptionCfg);  
  
    // Push the link state back to idle before any transition to from video and test patterns
    HAL_DP_SetLinkState(eControllerID, HAL_DP_LINKCOMMAND_TYPE_PUSH_IDLE);
  
    // Warn if we are not in the right state
    if (FALSE == CheckPhyPatternStatus(eDisplayID, eControllerID, HAL_DP_LINKSTATUS_TYPE_SENDING_IDLE_PATTERN2))
    {
      TraceInfo(QdiTraceDP, "DP%d: SetPHYTestPattern: Mainlink failed to transition to idle", eDisplayID);
    }
  }

  switch (ePhyTestPattern)
  {
    case DP_PHY_TEST_PATTERN_NONE:
    {
      // No action we've transitioned to idle already
      break;
    }
    case DP_PHY_TEST_PATTERN_D10_2_NO_SCRAMBLING:
    {
      HAL_DP_SetLinkState(eControllerID, HAL_DP_LINKCOMMAND_TYPE_SEND_PATTERN1);

      // Confirm controller is in the correct pattern
      if (FALSE == CheckPhyPatternStatus(eDisplayID, eControllerID, HAL_DP_LINKSTATUS_TYPE_SENDING_PATTERN1))
      {
        TraceInfo(QdiTraceDP, "DP%d: SetPHYTestPattern: Mainlink failed to transition to D10.2 pattern", eDisplayID);
      }      
      break;
    }
    case DP_PHY_TEST_PATTERN_SYMBOL_ERR_MEASUREMENT_CNT:
    {
      bool32              bBypassScrambler              = FALSE;
      uint32              uSafeToExitLevel              = DP_SAFE_TO_EXIT_LEVEL;
      uint32              uHBR2ComplianceScramblerReset = 0;

      DP_OSAL_MemSet(&sDPOptionCfg, 0, sizeof(HAL_DP_OptionalType));
      
      sDPOptionCfg.pbBypassScrambler = &bBypassScrambler;
      HAL_DP_SetOptionalConfig(eControllerID, &sDPOptionCfg);

      DP_OSAL_MemSet(&sDPOptionCfg, 0, sizeof(HAL_DP_OptionalType));
      sDPOptionCfg.puHBR2ComplianceScramblerReset = &uHBR2ComplianceScramblerReset;
      uHBR2ComplianceScramblerReset = 0;
      HAL_DP_SetOptionalConfig(eControllerID, &sDPOptionCfg);

      uHBR2ComplianceScramblerReset |= DP_HBR2_COMPLIANCE_SCRAMBLER_RESET;
      HAL_DP_SetOptionalConfig(eControllerID, &sDPOptionCfg);

      DP_OSAL_MemSet(&sDPOptionCfg, 0, sizeof(HAL_DP_OptionalType));
      sDPOptionCfg.puSafeToExitLevel    = &uSafeToExitLevel;
      sDPOptionCfg.puIdlePatternRepNum  = &uIdlePatternRepNum;
      HAL_DP_SetOptionalConfig(eControllerID, &sDPOptionCfg);

      HAL_DP_SetLinkState(eControllerID, HAL_DP_LINKCOMMAND_TYPE_SEND_SYMBOL_ERM);

      // Warn if we are not in the right state
      if (FALSE == CheckPhyPatternStatus(eDisplayID, eControllerID, HAL_DP_LINKSTATUS_TYPE_SENDING_SYMBOL_ERM))
      {
        TraceInfo(QdiTraceDP, "DP%d: SetPHYTestPattern: Mainlink failed to transition to symbol error measurement (ERM) pattern", eDisplayID);
      }          
      break;
    }
    case DP_PHY_TEST_PATTERN_PRBS7:
    {
      HAL_DP_SetLinkState(eControllerID, HAL_DP_LINKCOMMAND_TYPE_SEND_PRBS7);

      // Warn if we are not in the right state
      if (FALSE == CheckPhyPatternStatus(eDisplayID, eControllerID, HAL_DP_LINKSTATUS_TYPE_SENDING_PRBS7))
      {
        TraceInfo(QdiTraceDP, "DP%d: SetPHYTestPattern: Mainlink failed to transition to PRBS7 pattern", eDisplayID);      
      }         
      break;
    }
    case DP_PHY_TEST_PATTERN_80_BIT_CUSTOM_PATTERN:
    {
      HAL_DP_CustomPatternType  sCustomPattern;

      DP_OSAL_MemSet(&sDPOptionCfg,   0, sizeof(HAL_DP_OptionalType));
      DP_OSAL_MemSet(&sCustomPattern, 0, sizeof(HAL_DP_CustomPatternType));
      sDPOptionCfg.psCustomPattern     = &sCustomPattern;
      sCustomPattern.uCustomPattern_R0 = DP_CUSTOM_PATTERN_R0;
      sCustomPattern.uCustomPattern_R1 = DP_CUSTOM_PATTERN_R1;
      sCustomPattern.uCustomPattern_R2 = DP_CUSTOM_PATTERN_R2;
      HAL_DP_SetOptionalConfig(eControllerID, &sDPOptionCfg);

      HAL_DP_SetLinkState(eControllerID, HAL_DP_LINKCOMMAND_TYPE_SEND_CUSTOM_PATTERN);

      // Warn if we are not in the right state
      if (FALSE == CheckPhyPatternStatus(eDisplayID, eControllerID, HAL_DP_LINKSTATUS_TYPE_SENDING_CUSTOM_PATTERN))
      {
        TraceInfo(QdiTraceDP, "DP%d: SetPHYTestPattern: Mainlink failed to transition to 80bit custom pattern", eDisplayID);    
      }           
      break;
    }
    case DP_PHY_TEST_PATTERN_CP2520_PATTERN_1:
    {
      uint32              uSafeToExitLevel              = DP_SAFE_TO_EXIT_LEVEL;
      uint32              uHBR2ComplianceScramblerReset = 0;

      DP_OSAL_MemSet(&sDPOptionCfg, 0, sizeof(HAL_DP_OptionalType));
      sDPOptionCfg.puHBR2ComplianceScramblerReset = &uHBR2ComplianceScramblerReset;
      uHBR2ComplianceScramblerReset               = DP_HBR2_ERM_PATTERN;
      HAL_DP_SetOptionalConfig(eControllerID, &sDPOptionCfg);

      uHBR2ComplianceScramblerReset |= DP_HBR2_COMPLIANCE_SCRAMBLER_RESET;
      HAL_DP_SetOptionalConfig(eControllerID, &sDPOptionCfg);

      DP_OSAL_MemSet(&sDPOptionCfg, 0, sizeof(HAL_DP_OptionalType));
      sDPOptionCfg.puSafeToExitLevel    = &uSafeToExitLevel;
      sDPOptionCfg.puIdlePatternRepNum  = &uIdlePatternRepNum;
      HAL_DP_SetOptionalConfig(eControllerID, &sDPOptionCfg);

      HAL_DP_SetLinkState(eControllerID, HAL_DP_LINKCOMMAND_TYPE_SEND_SYMBOL_ERM);

      // Warn if we are not in the right state
      if (FALSE == CheckPhyPatternStatus(eDisplayID, eControllerID, (HAL_DP_LinkStatusType)HAL_DP_LINKCOMMAND_TYPE_SEND_SYMBOL_ERM))
      {
        TraceInfo(QdiTraceDP, "DP%d: SetPHYTestPattern: Mainlink failed to transition to CP2520 Pattern 1", eDisplayID); 
      }             
      break;
    }
    case DP_PHY_TEST_PATTERN_CP2520_PATTERN_2:  
    {
      TraceInfo(QdiTraceDP, "DP%d: SetPHYTestPattern: Mainlink failed to transition to CP2520 Pattern 2 (Not supported)", eDisplayID); 
      break;
    }    
    case DP_PHY_TEST_PATTERN_CP2520_PATTERN_3:
    {
      HAL_DP_SetLinkState(eControllerID, HAL_DP_LINKCOMMAND_TYPE_SEND_PATTERN4);

      // Warn if we are not in the right state
      if (FALSE == CheckPhyPatternStatus(eDisplayID, eControllerID, HAL_DP_LINKSTATUS_TYPE_SENDING_PATTERN4))
      {
        TraceInfo(QdiTraceDP, "DP%d: SetPHYTestPattern: Mainlink failed to transition to CP2520 Pattern 3 (TPS4)", eDisplayID); 
      }         

      break;
    }
    default:
    {
      TraceInfo(QdiTraceDP, "DP%d: SetPHYTestPattern: Phy pattern 0x%x is not supported", eDisplayID, ePhyTestPattern);
      break;
    }
  }

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: MapDPInterruptsToHAL()
*/
/*!
* \DESCRIPTION
*      Map DP generic interrupts to corresponding HAL interrupts
*
* \param [in] uDPInterrupts  - DP generic interrupts to be mapped to HAL.
*
* \retval uint32
*
**********************************************************************************************/
static uint32 MapDPInterruptsToHAL(DP_DisplayCtxType *pDisplayCtx,
                                   uint32             uDPInterrupts)
{
  uint32            uHALInterrupts = 0;
  DP_StreamCtxType *pStreamCtx     = DPHOST_GET_STREAM_CTX(pDisplayCtx);

  if (NULL == pStreamCtx)
  {
    DP_LOG_MESSAGE_ERROR("MapDPInterruptsToHAL: pStreamCtx is null.");
  }
  else
  {
    /* Mapping to DP_INTERRUPT_STATUS register */
    if (uDPInterrupts & DP_INTR_TYPE_AUX_I2C_DONE)
    {
      uHALInterrupts |= HAL_DP_INTR_TYPE_AUX_I2C_DONE;
    }

    if (uDPInterrupts & DP_INTR_TYPE_WRONG_ADDRESS)
    {
      uHALInterrupts |= HAL_DP_INTR_TYPE_WRONG_ADDRESS;
    }

    if (uDPInterrupts & DP_INTR_TYPE_CONSECUTIVE_TIMEOUT)
    {
      uHALInterrupts |= HAL_DP_INTR_TYPE_CONSECUTIVE_TIMEOUT;
    }

    if (uDPInterrupts & DP_INTR_TYPE_CONSECUTIVE_NACK_DEFER)
    {
      uHALInterrupts |= HAL_DP_INTR_TYPE_CONSECUTIVE_NACK_DEFER;
    }

    if (uDPInterrupts & DP_INTR_TYPE_WRONG_READDATA_COUNT)
    {
      uHALInterrupts |= HAL_DP_INTR_TYPE_WRONG_READDATA_COUNT;
    }

    if (uDPInterrupts & DP_INTR_TYPE_AUX_NACK_DURING_I2C)
    {
      uHALInterrupts |= HAL_DP_INTR_TYPE_AUX_NACK_DURING_I2C;
    }

    if (uDPInterrupts & DP_INTR_TYPE_AUX_DEFER_DURING_I2C)
    {
      uHALInterrupts |= HAL_DP_INTR_TYPE_AUX_DEFER_DURING_I2C;
    }

    if (uDPInterrupts & DP_INTR_TYPE_PLL_UNLOCK_DET)
    {
      uHALInterrupts |= HAL_DP_INTR_TYPE_PLL_UNLOCK_DET;
    }

    if (uDPInterrupts & DP_INTR_TYPE_DPPHY_AUX_ERROR)
    {
      uHALInterrupts |= HAL_DP_INTR_TYPE_DPPHY_AUX_ERROR;
    }

    /* Mapping to DP_INTERRUPT_STATUS_2 register */
    if (uDPInterrupts & DP_INTR_TYPE_ENCRYPTION_READY)
    {
      uHALInterrupts |= HAL_DP_INTR_TYPE_ENCRYPTION_READY;
    }

    if (uDPInterrupts & DP_INTR_TYPE_ENCRYPTION_NOT_READY)
    {
      uHALInterrupts |= HAL_DP_INTR_TYPE_ENCRYPTION_NOT_READY;
    }

    if (uDPInterrupts & DP_INTR_TYPE_AUTH_SUCCESS)
    {
      uHALInterrupts |= HAL_DP_INTR_TYPE_AUTH_SUCCESS;
    }

    if (uDPInterrupts & DP_INTR_TYPE_AUTH_FAIL)
    {
      uHALInterrupts |= HAL_DP_INTR_TYPE_AUTH_FAIL;
    }

    if (uDPInterrupts & DP_INTR_TYPE_HPD_PLUG_INT)
    {
      uHALInterrupts |= HAL_DP_INTR_TYPE_HPD_PLUG_INT;
    }

    if (uDPInterrupts & DP_INTR_TYPE_HPD_IRQ_INT)
    {
      uHALInterrupts |= HAL_DP_INTR_TYPE_HPD_IRQ_INT;
    }

    if (uDPInterrupts & DP_INTR_TYPE_HPD_REPLUG_INT)
    {
      uHALInterrupts |= HAL_DP_INTR_TYPE_HPD_REPLUG_INT;
    }

    if (uDPInterrupts & DP_INTR_TYPE_HPD_UNPLUG_INT)
    {
      uHALInterrupts |= HAL_DP_INTR_TYPE_HPD_UNPLUG_INT;
    }

    if (uDPInterrupts & DP_INTR_TYPE_FRAME_END)
    {
      if (DP_MST_STREAM_ID_1 == pStreamCtx->eMSTStreamId)
      {
        uHALInterrupts |= HAL_DP_INTR_TYPE_FRAME_END_STREAM1;
      }
      else
      {
        uHALInterrupts |= HAL_DP_INTR_TYPE_FRAME_END;
      }
    }
  }

  return uHALInterrupts;
}

/*********************************************************************************************
*
** FUNCTION: MapHALInterruptsToDP()
*/
/*!
* \DESCRIPTION
*      Map DP HAL interrupts to corresponding DP generic interrupts
*
* \param [in] uHALInterrupts  - DP HAL interrupts to be mapped.
*
* \retval uint32
*
**********************************************************************************************/
static uint32 MapHALInterruptsToDP(DP_DisplayCtxType *pDisplayCtx,
                                   uint32             uHALInterrupts)
{
  uint32            uDPInterrupts = 0;
  DP_StreamCtxType *pStreamCtx    = DPHOST_GET_STREAM_CTX(pDisplayCtx);

  if (NULL == pStreamCtx)
  {
    DP_LOG_MESSAGE_ERROR("MapHALInterruptsToDP: pStreamCtx is null.");
  }
  else
  {
    /* Reading AUX_INTERRUPT_STATUS register status */
    if (uHALInterrupts & HAL_DP_INTR_ALL)
    {
      if (uHALInterrupts & HAL_DP_INTR_TYPE_AUX_I2C_DONE)
      {
        uDPInterrupts |= DP_INTR_TYPE_AUX_I2C_DONE;
      }

      if (uHALInterrupts & HAL_DP_INTR_TYPE_WRONG_ADDRESS)
      {
        uDPInterrupts |= DP_INTR_TYPE_WRONG_ADDRESS;
      }

      if (uHALInterrupts & HAL_DP_INTR_TYPE_CONSECUTIVE_TIMEOUT)
      {
        uDPInterrupts |= DP_INTR_TYPE_CONSECUTIVE_TIMEOUT;
      }

      if (uHALInterrupts & HAL_DP_INTR_TYPE_CONSECUTIVE_NACK_DEFER)
      {
        uDPInterrupts |= DP_INTR_TYPE_CONSECUTIVE_NACK_DEFER;
      }

      if (uHALInterrupts &HAL_DP_INTR_TYPE_WRONG_READDATA_COUNT)
      {
        uDPInterrupts |= DP_INTR_TYPE_WRONG_READDATA_COUNT;
      }

      if (uHALInterrupts & HAL_DP_INTR_TYPE_AUX_NACK_DURING_I2C)
      {
        uDPInterrupts |= DP_INTR_TYPE_AUX_NACK_DURING_I2C;
      }

      if (uHALInterrupts & HAL_DP_INTR_TYPE_AUX_DEFER_DURING_I2C)
      {
        uDPInterrupts |= DP_INTR_TYPE_AUX_DEFER_DURING_I2C;
      }

      if (uHALInterrupts & HAL_DP_INTR_TYPE_PLL_UNLOCK_DET)
      {
        uDPInterrupts |= DP_INTR_TYPE_PLL_UNLOCK_DET;
      }

      if (uHALInterrupts & HAL_DP_INTR_TYPE_DPPHY_AUX_ERROR)
      {
        uDPInterrupts |= DP_INTR_TYPE_DPPHY_AUX_ERROR;
      }
    }

    /* Reading AUX_INTERRUPT_STATIUS_2 register status */
    if (uHALInterrupts & HAL_DP_INTR_TYPE_ENCRYPTION_READY)
    {
       uDPInterrupts |= DP_INTR_TYPE_ENCRYPTION_READY;
    }

    if (uHALInterrupts & HAL_DP_INTR_TYPE_ENCRYPTION_NOT_READY)
    {
       uDPInterrupts |= DP_INTR_TYPE_ENCRYPTION_NOT_READY;
    }

    if (uHALInterrupts & HAL_DP_INTR_TYPE_AUTH_SUCCESS)
    {
       uDPInterrupts |= DP_INTR_TYPE_AUTH_SUCCESS;
    }

    if (uHALInterrupts & HAL_DP_INTR_TYPE_AUTH_FAIL)
    {
      uDPInterrupts |= DP_INTR_TYPE_AUTH_FAIL;
    }

    if (uHALInterrupts & HAL_DP_INTR_TYPE_HPD)
    {
      uDPInterrupts |= DP_INTR_TYPE_HPD;
    }

    if (uHALInterrupts & HAL_DP_INTR_TYPE_HPD_PLUG_INT)
    {
      uDPInterrupts |= DP_INTR_TYPE_HPD_PLUG_INT;
    }

    if (uHALInterrupts & HAL_DP_INTR_TYPE_HPD_IRQ_INT)
    {
      uDPInterrupts |= DP_INTR_TYPE_HPD_IRQ_INT;
    }

    if (uHALInterrupts & HAL_DP_INTR_TYPE_HPD_REPLUG_INT)
    {
      uDPInterrupts |= DP_INTR_TYPE_HPD_REPLUG_INT;
    }

    if (uHALInterrupts & HAL_DP_INTR_TYPE_HPD_UNPLUG_INT)
    {
      uDPInterrupts |= DP_INTR_TYPE_HPD_UNPLUG_INT;
    }

    if ((uHALInterrupts & HAL_DP_INTR_TYPE_FRAME_END) &&
        (DP_MST_STREAM_ID_0 == pStreamCtx->eMSTStreamId))
    {
      uDPInterrupts |= DP_INTR_TYPE_FRAME_END;
    }

    if ((uHALInterrupts & HAL_DP_INTR_TYPE_FRAME_END_STREAM1) &&
        (DP_MST_STREAM_ID_1 == pStreamCtx->eMSTStreamId))
    {
      uDPInterrupts |= DP_INTR_TYPE_FRAME_END;
    }
  }

  return uDPInterrupts;
}

//-------------------------------------------------------------------------------------------------
//  HandleReplugHPD
//
//  @brief
//      Replug HPD will notify OS there is hot plug out
//
//  @params
//      pDisplayCtx         -[in ] Pointer to context
//
//  @return
//      void.
//-------------------------------------------------------------------------------------------------
static DP_Status HandleReplugHPD(DP_DisplayCtxType      *pDisplayCtx)
{
  DP_Status             eStatus     = DP_STATUS_SUCCESS;
  DP_DeviceCtxType     *pDeviceCtx;
  DP_StreamCtxType     *pStreamCtx;

  if (NULL == pDisplayCtx)
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) ||
           (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_DRIVER_NOT_INITIALIZED;
  }
  else
  {
    /* DP Over USBC does not have replug event */
    if (DP_DEVICE_MODETYPE_DP == pDeviceCtx->eDeviceDPMode)
    {
      MDP_Display_IDType        eDisplayId      = DP_GetDisplayMap(pDeviceCtx->eDeviceID, pStreamCtx->eMSTStreamId);
      DP_SetPropertyParamsType  sDPProp;

      TraceInfo(QdiTraceDP, "DP%d: HandleReplugHPD Notify Sink is plugged out",  eDisplayId);

      DISP_OSAL_MemZero(&sDPProp, sizeof(DP_SetPropertyParamsType));
      sDPProp.bConnected = FALSE;

      if (DP_STATUS_SUCCESS != (eStatus = DP_Host_SetProperty(pDisplayCtx, DP_SETPROPERTY_CONNECTION_STATUS, &sDPProp)))
      {
        DISP_OSAL_LOGX("HandleReplugHPD: DP_Host_SetProperty failed to set connection status, eRetStatus =%d", eStatus);
      }

      /* For replug case, HPD-Out happens while HPD-In is in progress, and before it calls the power off another HPD-In
         comes. Setting this un-plug HPD-Out flag will allow the re-enummeration of the display correctly, during
         the re-plug processing.
      */
      pDeviceCtx->uFlags = DPHOST_SETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_UNPLUG_HPD_DETECTED);

      DP_SoftHPDInterrupt(eDisplayId, FALSE);
    }
  }

  return eStatus;
}


//-------------------------------------------------------------------------------------------------
//  HandleIrqHPD
//
//  @brief
//      Process IRQ HPD
//
//  @params
//      pDisplayCtx         -[in ] Pointer to context
//
//  @return
//      void.
//-------------------------------------------------------------------------------------------------
static DP_Status HandleIrqHPD(DP_DisplayCtxType    *pDisplayCtx)
{
  DP_Status   eStatus = DP_STATUS_SUCCESS;

  if (NULL == pDisplayCtx)
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else 
  {
    OSEventType           hHostLock  = DPHOST_GET_HOST_LOCK();
    DP_DeviceCtxType     *pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
    DP_StreamCtxType     *pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx);

    if ((NULL == pDeviceCtx) ||
        (NULL == pStreamCtx))
    {
      eStatus = DP_STATUS_FAILED_DRIVER_NOT_INITIALIZED;
    }
    else if (MDP_STATUS_SUCCESS != DISP_OSAL_AcquireLockEvent(hHostLock, 0))
    {
      DP_LOG_MESSAGE_ERROR("HandleIrqHPD: Failed to acquire host layer global lock. Controller=%d", pDeviceCtx->eControllerID);
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
    }
    else 
    {
      if (TRUE == pDeviceCtx->bInitialized)
      {
        TraceInfo(QdiTraceDP, "DP%d: HandleIrqHPD, StreamID = %d, StreamCount = %d", pStreamCtx->eDisplayID, pStreamCtx->eMSTStreamId, pDeviceCtx->uNumActiveStreams);

        if (DP_STATUS_SUCCESS != (eStatus = DP_ReadTestRequest(pDisplayCtx)))
        {
          TraceInfo(QdiTraceDP, "DP%d: HandleIrqHPD: Failed to get test request, eStatus =%d.", pStreamCtx->eDisplayID, eStatus);
        }
        else if ((DP_TEST_NONE != pDeviceCtx->ePendingTestRequest) ||
                ((TRUE         == pDeviceCtx->bLinkLost) &&           /* If link has been previously configured, and sink reports link lost, link training is required */
                (TRUE         == pDeviceCtx->bLinkConfigured)))
        {
          bool32 bPreAck = FALSE;

          if ((DP_TEST_LINK_TRAINING == pDeviceCtx->ePendingTestRequest) ||
              (DP_TEST_EDID_READ     == pDeviceCtx->ePendingTestRequest))
          {
            /* If it is link training test, source has to ACK the request before link training */
            bPreAck = TRUE;
            if (DP_STATUS_SUCCESS != (eStatus = DP_WriteTestResponse(pDisplayCtx)))
            {
              TraceInfo(QdiTraceDP, "DP%d: IRQHPDWorkThread: DP_WriteTestResponse Failed, eStatus = %d.", pStreamCtx->eDisplayID, eStatus);
            }
          }

          // CTS tests require a reconfiguration of link & link training
          pDeviceCtx->bLinkConfigured = FALSE;
          pStreamCtx->uDirtyBits     |= DP_DIRTYFIELD_SETMODE;

          if (DP_STATUS_SUCCESS != (eStatus = DP_Host_SetMode(pDisplayCtx)))
          {
            TraceInfo(QdiTraceDP, "DP%d: IRQHPDWorkThread: DP_Host_SetMode failed, eStatus =%d.", pStreamCtx->eDisplayID, eStatus);
          }

          if (FALSE == bPreAck)
          {
            /* Send test response if it is requested */
            if (DP_STATUS_SUCCESS != (eStatus = DP_WriteTestResponse(pDisplayCtx)))
            {
              TraceInfo(QdiTraceDP, "DP%d: IRQHPDWorkThread: DP_WriteTestResponse Failed, eStatus = %d.", pStreamCtx->eDisplayID, eStatus);
            }
          }
        } 
      }
      
      DISP_OSAL_ReleaseLockEvent(hHostLock);
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  IRQHPDWorkThread
//
//  @brief
//      Work thread to handle IRQ HPD
//
//  @params
//      pDeviceObject  -[in]    : PDO handle
//      pContext       -[in]    : handle to DP display context
//
//  @return
//      void.
//-------------------------------------------------------------------------------------------------
static void IRQHPDWorkThread(void *pDeviceObject,
                             void *pContext)
{
  DP_Status eStatus = DP_STATUS_SUCCESS;

  UNREFERENCED_PARAMETER(pDeviceObject);

  if (NULL == pContext)
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    eStatus = HandleIrqHPD((DP_DisplayCtxType*)pContext);
  }

  if (DP_STATUS_SUCCESS != eStatus)
  {
    TraceInfo(QdiTraceDP, "DP: IRQHPDWorkThread failed, eStatus = %d", eStatus);
  }
}

//-------------------------------------------------------------------------------------------------
//  FilterLanesByPinAssignment
//
//  @brief
//      Filter the lane number that are taken by USB driver.
//
//  @params
//      eDeviceID         -[in ] DP device ID
//      ePinAssignment    -[in ] USB/DP pin assignment info
//      uNumberofLanes    -[in ] Current number of DP lanes.
//
//  @return
//      uint32 filtered number of DP lanes.
//-------------------------------------------------------------------------------------------------
static uint32 FilterLanesByPinAssignment(DP_DeviceIDType            eDeviceID,
                                         DP_ConnectionPinAssignment ePinAssignment,
                                         uint32                     uNumberofLanes)
{
  uint32 uFilteredNumberofLanes = uNumberofLanes;

  // Only USB alt-mode can share data lane with USB driver.
  if (TRUE == IsAltModeDPDevice(eDeviceID))
  {
    uFilteredNumberofLanes = DP_MIN(sPinAssignmentToLaneNumMapping[ePinAssignment], uNumberofLanes);
  }

  return uFilteredNumberofLanes;
}

//-------------------------------------------------------------------------------------------------
//  ConfigureMainLink
//
//  @brief
//      Configures the main link depending of the requested command type.
//
//  @params
//      pDeviceCtx         -[in ] Pointer to device context.
//      eCommandType       -[in ] DP link command type
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
static DP_Status ConfigureMainLink(DP_DisplayCtxType *pDisplayCtx, 
                                   DP_LinkCommandType eCommandType)
{
  DP_Status         eStatus    = DP_STATUS_SUCCESS;
  DP_DeviceCtxType *pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  
  if (NULL == pDeviceCtx)
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else 
  {
    switch(eCommandType)
    {
      case DP_LINKCOMMAND_TYPE_NONE:
      {
        // Clear mainlink state
        HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_NONE);
        break;
      }
      case DP_LINKCOMMAND_TYPE_ENABLE:
      {
        HAL_DP_Mainlink_Enable(pDeviceCtx->eControllerID, TRUE);    
        break;
      }
      case DP_LINKCOMMAND_TYPE_PUSH_IDLE:
      {
        // Check if the link is configured before pushing idle as requests to push idle can
        // occur during power on and change mode events before the mainlink is setup
        if (TRUE == pDeviceCtx->bLinkConfigured)
        {
          // Push Idle Patterns
          HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_PUSH_IDLE);
          
          if (DP_STATUS_SUCCESS != DP_WaitForLinkStatus(pDisplayCtx, HAL_DP_LINKSTATUS_TYPE_IDLE_PATTERNS_SENT))
          {
            eStatus = DP_STATUS_FAIL;
            DP_LOG_MESSAGE_WARN("DP_Host_Set_Property(): Failed to push Idle Pattern");
          }
        }
        break;
      }
      case DP_LINKCOMMAND_TYPE_SEND_VIDEO:
      {
        // Start Video
        // Note: Before waiting for link status, some more actions are needed for MST. (TX slots, send ACT) 
        HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_SEND_VIDEO);
        break;
      }
      case DP_LINKCOMMAND_TYPE_SEND_PATTERN1:
      {
        // Push Idle Patterns
        HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_SEND_PATTERN1);

        if (DP_STATUS_SUCCESS != DP_WaitForLinkStatus(pDisplayCtx, HAL_DP_LINKSTATUS_TYPE_SENDING_PATTERN1))
        {
          eStatus = DP_STATUS_FAIL;
          DP_LOG_MESSAGE_WARN("DP_Host_Set_Property(): Failed to send Pattern1");
        }
        break;
      }
      case DP_LINKCOMMAND_TYPE_SEND_PATTERN2:
      {
        // Push Idle Patterns
        HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_SEND_PATTERN2);

        if (DP_STATUS_SUCCESS != DP_WaitForLinkStatus(pDisplayCtx, HAL_DP_LINKSTATUS_TYPE_SENDING_PATTERN2))
        {
          eStatus = DP_STATUS_FAIL;
          DP_LOG_MESSAGE_WARN("DP_Host_Set_Property(): Failed to send Pattern2");
        }
        break;
      }
      case DP_LINKCOMMAND_TYPE_SEND_PATTERN3:
      {
        // Push Idle Patterns
        HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_SEND_PATTERN3);

        if (DP_STATUS_SUCCESS != DP_WaitForLinkStatus(pDisplayCtx, HAL_DP_LINKSTATUS_TYPE_SENDING_PATTERN3))
        {
          eStatus = DP_STATUS_FAIL;
          DP_LOG_MESSAGE_WARN("DP_Host_Set_Property(): Failed to send Pattern3");
        }
        break;
      }
      case DP_LINKCOMMAND_TYPE_DISABLE:
      {
        HAL_DP_Mainlink_Enable(pDeviceCtx->eControllerID, FALSE);    
        break;
      }
      default:
      {
        eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
        DP_LOG_MESSAGE_ERROR("DP_Host_SetProperty: Invalid main link state");
        break;
      }
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  GetNumStreamsInUse
//
//  @brief
//      Counts the number of streams are in use
//
//  @params
//      pDeviceCtx         -[in ] Pointer to device context.
//
//  @return
//      uint32.
//-------------------------------------------------------------------------------------------------
static uint32 GetNumStreamsInUse(DP_DeviceCtxType *pDeviceCtx)
{
  uint32             uNumStreams = 0;
  DP_MSTStreamIDType eStreamID;

  if (pDeviceCtx == NULL)
  {
    TraceInfo(QdiTraceDP, "DP: GetNumStreamsInUse failed: Null device context.");
  }
  else
  {
    for (eStreamID = DP_MST_STREAM_ID_0; eStreamID < DP_MST_STREAM_ID_MAX; eStreamID++)
    { 
      if (TRUE == pDeviceCtx->aStreamCtx[eStreamID].bInUse)
      {
        uNumStreams++;
      }
    }
  }
  
  return uNumStreams;
}

//-------------------------------------------------------------------------------------------------
//  DP_Host_SetAUXFailsafeMode
//
//  @brief
//      This function simulates the display AUX being plugged-in.
//
//  @params
//      [IN] pDeviceCtx
//          Handle to DP Device context.
//      [IN] pStreamCtx
//          Handle to DP Stream context.
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
DP_Status DP_Host_SetAUXFailsafeMode(DP_DeviceCtxType *pDeviceCtx,
                                     DP_StreamCtxType *pStreamCtx)
{
  DP_Status eStatus = DP_STATUS_SUCCESS;

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_SetPanelFailsafeMode: Unexpected null context.");
  }
  else
  {
    // Set the flag that indicate panel failed
    pDeviceCtx->uFlags = DPHOST_SETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_AUX_FAILSAFE);

    // Disable link training and simulate AUX connected
    pDeviceCtx->eLinkTrainingType = DP_LINK_TRAINING_TYPE_NO_TRAINING;
    pDeviceCtx->bAuxReady         = TRUE;

    TraceInfo(QdiTraceDP, "DP%d: eDeviceID: %d Transitioning to AUX fail-safe mode due to AUX failure",
              pStreamCtx->eDisplayID,
              pDeviceCtx->eDeviceID);
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  GetConcurrencyMode
//
//  @brief
//      This function will return true if the system should support DP/USB SS concurrency
//
//  @params
//      pDeviceCtx         -[in ] Pointer to device context.
//
//  @return
//      bool32.
//-------------------------------------------------------------------------------------------------
static bool32 GetConcurrencyMode(DP_DeviceCtxType *pDeviceCtx)
{
  bool32 bRetVal = TRUE;

  if (NULL == pDeviceCtx)
  {
    DP_LOG_MESSAGE_ERROR("GetConcurrencyMode: unexpected null pointer");
  }
  else if ((0 != DPHOST_GETFLAG(pDeviceCtx->uFlags, DP_HOST_FLAG_ALT_MODE_FIXED_LANE_CONFIGURATION)) ||
           (DP_HOST_FLAG_SIMULATION_MODE & pDeviceCtx->uFlags))
  {
    /* DP/USB concurrency not supported if Type-C/Alt-Mode DP device is using fixed lane configuration */
    /* Used in cases where DP driver has full control of PHY and HPD event handshaking with USB driver is not required */
    bRetVal = FALSE;
  }

  return bRetVal;
}

//-------------------------------------------------------------------------------------------------
//  ConfigureExternalSourceClock
//
//  @brief
//      Configures the DP PHY PLL of a separate DP device
//
//  @params
//      pDeviceCtx        -[in ] Pointer to device context.
//      pPhyConfig        -[in ] Pointer to DP PHY PLL config info.
//      bEnable           -[in ] Flag to enable/disable PLL.
//
//  @return
//      DP_Status.
//-------------------------------------------------------------------------------------------------
static DP_Status ConfigureExternalSourceClock(DP_DeviceCtxType     *pDeviceCtx,
                                              HAL_DP_PllConfigType *pPhyConfig,
                                              bool32                bEnable)
{
  DP_Status eStatus = DP_STATUS_SUCCESS;

  if (NULL == pDeviceCtx)
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("ConfigureExternalSourceClock: unexpected null pointer");
  }
  else if (DP_BONDED_MODE_SHARED_RESOURCE_EXTERNAL_PIXEL_CLOCK == pDeviceCtx->sBondedModeConfig.eSharedResourceConfig)
  {
    DP_DeviceIDType eDeviceID = pDeviceCtx->sBondedModeConfig.eSourceClockDeviceID;

    /* Log start of PLL enable/disable */
    DISP_OSAL_EVENTLOG3(DISP_OSAL_EVENT_PLLPROGRAMMING_START, eDeviceID, 0, (DP_PHY_POWER_PHY | DP_PHY_POWER_PLL));
    
    if (TRUE == bEnable)
    {
      HAL_DP_PHY_SetPHYMode(eDeviceID, DP_PHY_MODE_CONCURRENCY);
      
      /* Configure and enable DP PLL */
      if (FALSE == HAL_DP_PHY_Config(eDeviceID, pPhyConfig, pDeviceCtx->eDeviceDPMode))
      {
        DP_LOG_MESSAGE_ERROR("DP%d: HAL_DP_PHY_Config failed in ConfigureExternalSourceClock.\n", eDeviceID);   
        eStatus = DP_STATUS_FAIL;
      }
    }
    else
    {
      HAL_MDSS_ErrorType ePHYPowerResult;
	  
      /* Power down DP PLL */
      if (HAL_MDSS_STATUS_SUCCESS != (ePHYPowerResult = HAL_DP_PHY_Power(eDeviceID, FALSE, (DP_PHY_POWER_PHY | DP_PHY_POWER_PLL))))
      {
        DP_LOG_MESSAGE_ERROR("DP%d: HAL_DP_PHY_Power failed with error=%d in ConfigureExternalSourceClock.\n",
                             eDeviceID,
                             ePHYPowerResult);
      }
    }
    
    /* Log end of PLL enable/disable */
    DISP_OSAL_EVENTLOG3(DISP_OSAL_EVENT_PLLPROGRAMMING_END, eDeviceID, eStatus, (DP_PHY_POWER_PHY | DP_PHY_POWER_PLL));
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  UpdateSourceClockRefCount
//
//  @brief
//      Increments/decrements source clock ref count and returns the current value.
//
//  @params
//      pDeviceCtx        -[in ] Pointer to device context.
//      iValue            -[in ] Value used to increment/decrement source clock ref count.
//  @return
//      int32.
//-------------------------------------------------------------------------------------------------
static int32 UpdateSourceClockRefCount(DP_DeviceCtxType *pDeviceCtx,
                                       int32             iValue)
{
  int32 iRetVal = -1;

  if (NULL == pDeviceCtx)
  {
    DP_LOG_MESSAGE_ERROR("UpdateSourceClockRefCount: Unexpected null context.");
  }
  else if (TRUE == pDeviceCtx->sBondedModeConfig.bEnabled)
  {
    /* Increment/decrement ref count for PLL internal/external to DP device based on input value provided */
    DP_DeviceIDType  eDeviceID  = (DP_BONDED_MODE_SHARED_RESOURCE_EXTERNAL_PIXEL_CLOCK == pDeviceCtx->sBondedModeConfig.eSharedResourceConfig) ? 
                                  pDeviceCtx->sBondedModeConfig.eSourceClockDeviceID : pDeviceCtx->eDeviceID;

    if (eDeviceID < DP_DEVICE_MAX)
    {
      int32 *pRefCount = &gDpSharedData.uSourceClockRefCount[eDeviceID];

      (*pRefCount) += iValue;

      if (*pRefCount < 0)
      {
        *pRefCount = 0;
        DP_LOG_MESSAGE_WARN("UpdateSourceClockRefCount: Clock source ref count reached minimum count, eDeviceID = %d", eDeviceID);
      }
      else if (*pRefCount > DP_DEVICE_MAX)
      {
        *pRefCount = DP_DEVICE_MAX;
        DP_LOG_MESSAGE_WARN("UpdateSourceClockRefCount: Clock source ref count exceeded maximum count, eDeviceID = %d", eDeviceID);
      }

      iRetVal = *pRefCount;
    }
  }

  return iRetVal;
}

//-------------------------------------------------------------------------------------------------
//  IsAltModeDPDevice
//
//  @brief
//      Return TRUE if DP Device ID belongs to an Alt-mode DP Device.
//
//  @params
//      eDeviceID        -[in ] DP Device ID.
//  @return
//      bool32.
//-------------------------------------------------------------------------------------------------
static bool32 IsAltModeDPDevice(DP_DeviceIDType eDeviceID)
{
  bool32 bRetVal = FALSE;

  switch (eDeviceID)
  {
    case DP_DEVICE_ID_ALT_MODE_0:
    case DP_DEVICE_ID_ALT_MODE_1:
	  case DP_DEVICE_ID_ALT_MODE_2:
      bRetVal = TRUE;
      break;
    default:
      break;
  }

  return bRetVal;
}

//-------------------------------------------------------------------------------------------------
//  DP_QueryBrightnessCaps
//
//  @brief
//      Query Brightness capabilities of the sink
//
//  @params
//      pDisplayCtx         -[in ] Pointer to display context
//
//  @return
//      DP_Status
//-------------------------------------------------------------------------------------------------
static DP_Status QueryBrightnessCaps(DP_DisplayCtxType *pDisplayCtx)
{
  DP_Status               eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType       *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_DSC_QueryInfo: Unexpected null context.");
  }
  else
  {
  
    /* Read caps only if brightness for this panel is configured through DP AUX */
    if ((DP_CAPS_BRIGHTNESS & pDeviceCtx->eCapabilityMask)  &&
        (DP_STATUS_SUCCESS != (eStatus = DP_ReadSinkBrightnessCap(pDisplayCtx))))
    {
      TraceInfo(QdiTraceDP, "DP%d: Failed to Read Sink Brightness capabilities", pDeviceCtx->eDisplayID);
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  SetupBondedConfig
//
//  @brief
//      Set up bonded mode configuration.
//
//  @params
//      pDeviceCtx   -[IN] Pointer to device context
//      pStreamCtx   -[IN] Pointer to stream context
//      psOpenConfig -[IN] Pointer to open configuration
//
//  @return
//      DP_Status
//-------------------------------------------------------------------------------------------------
static DP_Status SetupBondedConfig(DP_DeviceCtxType         *pDeviceCtx,
                                   DP_StreamCtxType         *pStreamCtx,
                                   DP_Config_BondedModeType *pBondedModeCfg)
{
  DP_Status eStatus = DP_STATUS_SUCCESS;

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx) ||
      (NULL == pBondedModeCfg))
  {
    DP_LOG_MESSAGE_ERROR("SetupBondedConfig: Unexpected null context.");
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else if (TRUE == pBondedModeCfg->bEnabled)
  {
    // Check Device ID of device providing the source clock
    if ((pBondedModeCfg->eSourceClockDeviceID < DP_DEVICE_MAX) &&
        (pBondedModeCfg->eMasterAUXDeviceID < DP_DEVICE_MAX) &&
        (pBondedModeCfg->eSourceClockDeviceID != DP_DEVICE_ID_NONE) &&
        (pBondedModeCfg->eMasterAUXDeviceID != DP_DEVICE_ID_NONE))
    {
      if (pBondedModeCfg->eSourceClockDeviceID != pDeviceCtx->eDeviceID)
      {
        // If DP device pixel clock needs to be sourced from a separate DP device source clock
        pDeviceCtx->sBondedModeConfig.eSharedResourceConfig = DP_BONDED_MODE_SHARED_RESOURCE_EXTERNAL_PIXEL_CLOCK;
        pDeviceCtx->sBondedModeConfig.eSourceClockDeviceID  = pBondedModeCfg->eSourceClockDeviceID;

        // Sourcing an external pixel clock is asynchronous with respect to our link clock
        pDeviceCtx->bSynchronousClk = FALSE;
      }
      else
      {
        // If DP device pixel clock is sourced from its corresponding source clock
        pDeviceCtx->sBondedModeConfig.eSharedResourceConfig = DP_BONDED_MODE_SHARED_RESOURCE_NONE;
        pDeviceCtx->sBondedModeConfig.eSourceClockDeviceID  = pDeviceCtx->eDeviceID;

        // If bonded mode is enabled and our clock is the source for other PHYs, we cannot enable SSC on this PHY
        pDeviceCtx->eSSCMode = MDP_DP_SSC_DISABLED;
      }
      pDeviceCtx->sBondedModeConfig.eMasterAUXDeviceID = pBondedModeCfg->eMasterAUXDeviceID;
      pDeviceCtx->sBondedModeConfig.bEnabled           = TRUE;
      TraceInfo(QdiTraceDP,
                "DP%d: SetupBondedConfig() Bonded mode enabled on interface %d",
                pStreamCtx->eDisplayID,
                pDeviceCtx->eDeviceID);
    }
    else
    {
      // Invalid source clock Device ID
      pBondedModeCfg->bEnabled = FALSE;
      TraceInfo(QdiTraceDP,
                "DP%d: SetupBondedConfig() invalid Device ID in bonded mode configuration",
                pStreamCtx->eDisplayID);
      eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    }
  }
  else
  {
    pDeviceCtx->sBondedModeConfig.bEnabled = FALSE;
  }
  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  SetModeDSCConfig
//
//  @brief
//      Helper function to configure FEC/DSC during SetMode
//
//  @params
//      pDisplayCtx         -[in ] Pointer to display context
//      bLinkTraining       -[in ] TRUE if link training is done in the mode set
//
//  @return
//      DP_Status
//-------------------------------------------------------------------------------------------------
static DP_Status SetModeDSCConfig(DP_DisplayCtxType *pDisplayCtx, bool32 bLinkTraining)
{
  DP_Status               eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType       *pDeviceCtx;
  DP_StreamCtxType       *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) ||
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_DSC_QueryInfo: Unexpected null context.");
  }
  else
  {
    if (bLinkTraining)
    {    
      if (pStreamCtx->sDSCInfo.bFECEnabled)
      {
        // FEC is already enabled on sink side before link training
        // But it is disabled on source to prevent failures in training
        // Enabling it here after training is done and link is setup
        
        // Enable FEC on source
        HAL_DP_SetFECConfig(pDeviceCtx->eControllerID, TRUE, DPHOST_CHECK_DP_TUNNELING_MODE(pDeviceCtx));
      }

      if (pStreamCtx->sDSCInfo.bDSCEnabled)
      {
        // Read sink FEC status before configuring DSC on sink
        if (DP_STATUS_SUCCESS != (eStatus = DP_FEC_Decode_Status(pDisplayCtx)))
        {
          DP_LOG_MESSAGE_ERROR("SetModeDSCConfig: Sink did not detect FEC_DECODE_EN for display %d", 
                               pStreamCtx->eDisplayID);
        }
        else if (DP_STATUS_SUCCESS != (eStatus = DP_DSC_ConfigureSink(pDisplayCtx, TRUE)))
        {
          DP_LOG_MESSAGE_ERROR("SetModeDSCConfig: Failed to enable DSC on sink for display %d", 
                               pStreamCtx->eDisplayID);
        }
      }
    }
    
    // DSC is disabled by default on source during mode set
    // So need to program here if it should be enabled
    if ((TRUE               == pStreamCtx->sDSCInfo.bDSCEnabled) &&
        (DP_STATUS_SUCCESS  != (eStatus = DP_DSC_ConfigureSource(pDisplayCtx, TRUE))))
    {
      DP_LOG_MESSAGE_ERROR("SetModeDSCConfig: Failed to configure DSC on source for display %d", 
                           pStreamCtx->eDisplayID);
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  GetDPDeviceMode
//
//  @brief
//      Helper function to get the DP Device mode type
//
//  @params
//      eDisplayID              -[in ] MDP Display ID
//      eDeviceID               -[in ] DP Device ID 
//      bTunnelingmode          -[in ] boolean for indicating the DP tunnel mode 
//
//  @return
//      DP_DeviceModeType
//-------------------------------------------------------------------------------------------------
static DP_DeviceModeType GetDPDeviceMode(MDP_Display_IDType eDisplayID,
                                         DP_DeviceIDType    eDeviceID,
                                         bool32             bTunnelingmode)
{
  DP_DeviceModeType eDeviceDPMode = DP_DEVICE_MODETYPE_DP;

  switch (eDisplayID)
  {
  case MDP_DISPLAY_PRIMARY:
  case MDP_DISPLAY_SECONDARY:
  {
    if (DP_DEVICE_ID_EDP == eDeviceID)
    {
      eDeviceDPMode = DP_DEVICE_MODETYPE_EDP;
    }
    else
    {
      eDeviceDPMode = DP_DEVICE_MODETYPE_ALTMODE;
    }
  }
  break;
  case MDP_DISPLAY_EXTERNAL:
  case MDP_DISPLAY_EXTERNAL2:
  case MDP_DISPLAY_EXTERNAL3:
  case MDP_DISPLAY_EXTERNAL4:
  case MDP_DISPLAY_EXTERNAL5:
  case MDP_DISPLAY_EXTERNAL6:
  {
    if (TRUE == bTunnelingmode)
    {
      eDeviceDPMode = DP_DEVICE_MODETYPE_TUNNELING;
    }
    else
    {
      eDeviceDPMode = DP_DEVICE_MODETYPE_ALTMODE;
    }
  }
  break;
  default:
    eDeviceDPMode = DP_DEVICE_MODETYPE_DP;
    break;
  }

  return eDeviceDPMode;
}

//-------------------------------------------------------------------------------------------------
//  SetVSCSDP()
//
//  @brief
//      Helper function to send VSC SDP packet to convey colirimetry info
//
//  @params
//      pDeviceCtx -[in ] Pointer to dp device context
//
//  @return
//      DP_Status
//-------------------------------------------------------------------------------------------------
static DP_Status SetVSCSDP(DP_DeviceCtxType *pDeviceCtx,
                           DP_StreamCtxType *pStreamCtx)
{
  DP_Status               eRetStatus  = DP_STATUS_SUCCESS;
  DP_PanelInfoType       *psPanelInfo = &(pStreamCtx->sPanelInfo[pStreamCtx->uModeIndex]);
  HAL_DP_VSCSDPConfigType sVSCSDPCfg;
  uint8                   uDB[32];
  
  DISP_OSAL_MemZero(&sVSCSDPCfg, sizeof(HAL_DP_VSCSDPConfigType));
  DISP_OSAL_MemZero(&uDB, sizeof(uDB));

  // Data byte 16: Set bit 7-4 as RGB (=0) pixel encoding and bit 3-0 as as sRGB (=0) colorimetry format
  // Note: No HDR support in UEFI for now
  uDB[16] = (HAL_DP_PIXEL_ENCODING_RGB << 4) | HAL_DP_COLORIMETRY_FORMAT_SRGB;

  // Data byte 17 contains bit 7 as dynamic range, bit 6-3 resevered and bit 2-0 color bit depth
  // Selct VESA dynamic range (full range) for SDR (sRGB color space)
  uDB[17] = HAL_DP_DYNAMIC_RANGE_VESA << 7;

  switch(DPHOST_GETPIXELFMT(psPanelInfo->eColorFormat).uBitsPerComponent)
  {
    case DP_BITDEPTH_6BPC:
      uDB[17] |=  0;
      break;
    case DP_BITDEPTH_8BPC:
      uDB[17] |= 0x1;
      break;
    case DP_BITDEPTH_10BPC:
      uDB[17] |= 0x2;
      break;
    case DP_BITDEPTH_12BPC:
      uDB[17] |= 0x3;
      break;
    case DP_BITDEPTH_16BPC:
      uDB[17] |= 0x4;
      break;
    default:
      uDB[17] |= 0x2;
      break;
  }

  // Data byte 18 contains the content type
  uDB[18] = HAL_DP_CONTENT_GRAPHICS;

  // VSC secondary data packet id = 0
  sVSCSDPCfg.uHB0          = 0x00;
  // VSC SDP packet type
  sVSCSDPCfg.uHB1          = 0x07;
  // VSC SDP supporting 3D stereo, PSR2 and Pixel Encoding/colorimetry Format indication
  sVSCSDPCfg.uHB2          = 0x05;
  // VSC SDP supporting 3D stereo, PSR2 and Pixel Encoding/colorimetry Format indication
  sVSCSDPCfg.uHB3          = 0x13;

  sVSCSDPCfg.pSDPPayload   = &uDB[0];
  sVSCSDPCfg.uPayloadBytes = 32;

  // Configure VSC SDP.
  HAL_DP_VSCSDP_Config(pDeviceCtx->eControllerID, pStreamCtx->eMSTStreamId, &sVSCSDPCfg);

  // Enable VSC SDP.
  HAL_DP_VSCSDP_Enable(pDeviceCtx->eControllerID, pStreamCtx->eMSTStreamId, TRUE);

  return eRetStatus;
}

//-------------------------------------------------------------------------------------------------
//  ValidLinkRate
//
//  @brief
//      Checks if the provided link rate is valid.
//
//  @params
//      pDeviceCtx          -[in ] Pointer to dp device context
//      uLinkRate           -[in ] Link Rate to validate
//
//  @return
//      bool32
//-------------------------------------------------------------------------------------------------
static bool32 ValidLinkRate(DP_DeviceCtxType *pDeviceCtx, uint32 uLinkRate)
{
  bool32 bFound = FALSE;

  if ((NULL != pDeviceCtx) && 
      (0 != uLinkRate))
  {
    uint32  uIndex;
    uint32 *puSupportedLinkRateInKHz;
    uint32  uSupportedLinkRateCount;
  
    /* Supported eDP link rate setting */
    uint32 uEDPSupportedLinkRateInKHz[9] =
    {
      162000, // Reduced Bit Rate[RBR]
      216000,
      243000,
      270000, // High Bit Rate [HBR]
      324000,
      432000,
      540000, // High Bit Rate 2 [HBR2]
      594000,
      810000, // High Bit Rate 3 [HBR3]
    };
  
    /* Supported DP link rate setting */
    uint32 uDPSupportedLinkRateInKHz[4]=
    {
      162000, // Reduced Bit Rate[RBR]
      270000, // High Bit Rate [HBR]
      540000, // High Bit Rate 2 [HBR2]
      810000, // High Bit Rate 3 [HBR3]
    };
  
    // Select the link rate table based on the controller
    if (DP_DEVICE_MODETYPE_EDP == pDeviceCtx->eDeviceDPMode)
    {
      uSupportedLinkRateCount   = DPHOST_GET_LIST_SIZE(uEDPSupportedLinkRateInKHz);
      puSupportedLinkRateInKHz  = &uEDPSupportedLinkRateInKHz[0];
    }
    else
    {
      uSupportedLinkRateCount   = DPHOST_GET_LIST_SIZE(uDPSupportedLinkRateInKHz);
      puSupportedLinkRateInKHz  = &uDPSupportedLinkRateInKHz[0];
    }
    
    for (uIndex = 0; uIndex < uSupportedLinkRateCount; uIndex++)
    {
      if (puSupportedLinkRateInKHz[uIndex] == uLinkRate)
      {
        bFound = TRUE;
        break;
      }
    }
  }
  
  return bFound;
}

//-------------------------------------------------------------------------------------------------
//  Ceilf()
//
//  @brief
//      Helper function to similar to ceilf() in math library
//
//  @params
//      num - float number
//
//  @return
//      output float number
//-------------------------------------------------------------------------------------------------
static float Ceilf(float num)
{
  union 
  {
    float   f;
    uint32  i;
  } inputData = {num};
  
  int32 exp = (int32)(inputData.i >> 23 & 0xff) - 0x7f;
  uint32 mant;

  if (exp >= 23)
  {
    return num;
  }
  
  if (exp >= 0)
  {
    mant = 0x007fffff >> exp;
    if ((inputData.i & mant) == 0)
    {
      return num;
    }
        
    if (inputData.i >> 31 == 0)
    {
      inputData.i += mant;
    }
    inputData.i &= ~mant;
  }
  else
  {
    if (inputData.i >> 31)
    {
      inputData.f = -0.0;
    }
    else if (inputData.i << 1)
    {
      inputData.f = 1.0;
    }
  }
  return inputData.f;
}

//-------------------------------------------------------------------------------------------------
//  DP_LinkLaneReduction
//
//  @brief
//      Helper function to get the reduce link rate or lane count base on link training results
//
//  @params
//      pDisplayCtx          -[in ] Pointer to dp display context
//
//  @return
//      TRUE if downstream repeaters are in non-transparent mode
//-------------------------------------------------------------------------------------------------
static DP_Status DP_LinkLaneReduction(DP_DisplayCtxType *pDisplayCtx)
{
  DP_Status         eStatus    = DP_STATUS_FAILED_NOT_SUPPORTED;
  DP_DeviceCtxType *pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType *pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx);

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx))
  {
    DP_LOG_MESSAGE_ERROR("LaneCountReduce: unexpected null handle ");
  }
  else if (pDeviceCtx->uFlags & DP_HOST_FLAG_LINK_TRAINING_EQ_FALLBACK)
  {
    /* LANEx_CR_DONE over two or four lanes should fail if one (2-lane config) or two lanes (4-lane config)
    *  are available for DP Main-Link. However, itt is known that there are DPRX implementations that erroneously
    *  set the LANEx_CR_DONE bit(s) on all lanes during channel equalization. For EQ Fallback, reduction of lane count
    *  will be attempted first for such conditions and try to set up link again.
    */
    if (DP_STATUS_SUCCESS != (eStatus = LaneCountReduce(pDisplayCtx)))
    {
      // If LinkCountReduce fails, reduce the link rate and re-start clock recovery sequence 
      if (DP_STATUS_SUCCESS == (eStatus = LinkRateReduce(pDisplayCtx)))
      {
        // Reset back to max supported rate in sink's DPCP for next link training attempt
        pDeviceCtx->uLinkRateInKhz = pDeviceCtx->sSinkDPCDCap.uMaxLinkRateInKhz;
        pStreamCtx->uDirtyBits    |= DP_DIRTYFIELD_LINK_RATE;
      }
    }
  }
  else
  {
    if (DP_STATUS_SUCCESS != (eStatus = LinkRateReduce(pDisplayCtx)))
    {
      // If LinkRateReduce fails, reduce the no of lanes and re-start clock recovery sequence 
      if (DP_STATUS_SUCCESS == (eStatus = LaneCountReduce(pDisplayCtx)))
      {
        // Reset back to max supported rate in sink's DPCP for next link training attempt
        pDeviceCtx->uLinkRateInKhz = pDeviceCtx->sSinkDPCDCap.uMaxLinkRateInKhz;
        pStreamCtx->uDirtyBits    |= DP_DIRTYFIELD_LINK_RATE;
      }
    }
  }
  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_IsValidLTTPR
//
//  @brief
//      Determines if a repeater is present and valid.
//
//  @params
//      pDisplayCtx          -[in ] Pointer to dp display context
//
//  @return
//      TRUE if downstream repeaters are valid
//-------------------------------------------------------------------------------------------------
bool32  DP_IsValidLTTPR(DP_DisplayCtxType *pDisplayCtx)
{
  bool32            bValidLTTPR = FALSE;
  DP_DeviceCtxType *pDeviceCtx;

  if (NULL != (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    if ((pDeviceCtx->sLTTPRCaps.uMajor > 0)         &&
        (pDeviceCtx->sLTTPRCaps.uRepeaterCount > 0) &&
        (pDeviceCtx->sLTTPRCaps.uMaxLaneCount > 0)  &&
        (pDeviceCtx->sLTTPRCaps.uMaxLinkRate > 0))
    {
      // Valid repeater detected.
      bValidLTTPR = TRUE;
    }
  }

  return bValidLTTPR;
}

#ifdef __cplusplus
}
#endif

