/*=====================================================================================================================
 
  File: dp_dsc.c
 
  Source file for DP DSC related functionality 
   
  Copyright (c) 2018 - 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=======================================================================================================================*/


/*---------------------------------------------------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------------------------------------------------*/

#include "dp_i.h"
#include "dp_dsc.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------------------------------------------------
 * Defines
 *-------------------------------------------------------------------------------------------------------------------*/

/* Pixel rate to Slices per line mapping information.                         */
typedef struct
{
  uint32 uPeakPixelRateMHz;    /* Pixel rate in megapixels/second             */
  uint32 uSlicePerLine;        /* Slices per line for 1 pixel per clock mode  */
} PeakPixelRateToSliceType;


/* DSO DTO parameters */
typedef struct
{
  uint32 uCompressionRatio;       // Compression Ratio
  uint32 uBitsPerPixel;           // Input bits per pixel
  uint32 uNumerator;              // DTO numerator
  uint32 uDenominator;            // DTO denominator
} DSCDTORatioType;

/* LUT to get DSC DTO numerator and denominator values */
DSCDTORatioType gDSCDTORatioLUT[] = 
{
  {2, 24, 1, 2},
  {3, 24, 1, 3},
  {2, 30, 5, 8},
  {3, 30, 5, 12},
};

/*--------------------------------------------------------------------------------------------
 * Local Prototypes
 *------------------------------------------------------------------------------------------*/
DP_Status CalculateSliceDimensions(DP_StreamCtxType *pStreamCtx, uint32 uModeIdx);

static void GetDTONumDem(uint32  uCompressionRatio,
                         uint32  uTargetBpp,
                         uint32 *pNumerator,
                         uint32 *pDenominator);

static uint32 CalculateBlankEndInLane(DP_StreamCtxType *pStreamCtx, bool32 bDSCEnable, bool32 bMSTEnable);

/*--------------------------------------------------------------------------------------------
 * Public Functions
 *------------------------------------------------------------------------------------------*/

/*********************************************************************************************
*
** FUNCTION: DP_DSC_ConfigureSink()
*/
/*!
* \DESCRIPTION
*      Configure DSC on sink
*
* \param [in]   pDisplayCtx        - Pointer to DP Context
* \param [in]   bEnable            - Flag used to determine if DSC needs to be enabled/disabled
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_DSC_ConfigureSink(DP_DisplayCtxType  *pDisplayCtx, bool32 bEnable)
{
  DP_Status               eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType       *pDeviceCtx;
  DP_StreamCtxType       *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_DSC_ConfigureSink: Unexpected null context.");
  }
  else if (TRUE == pStreamCtx->sDSCCaps.bSupported)
  {
    if (DP_STATUS_SUCCESS != (eStatus = DP_WriteSinkDSCConfig(pDisplayCtx, bEnable)))
    {
      // Unable to enable DSC on sink.
      pStreamCtx->sDSCInfo.bDSCEnabled = FALSE;
    }
  
    TraceInfo(QdiTraceDP, "DP%d: Config DSC on sink, bEnable: %d, status:0x%x", pStreamCtx->eDisplayID, bEnable, eStatus);
  }

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_FEC_ConfigureSink()
*/
/*!
* \DESCRIPTION
*      Configure FEC on sink
*
* \param [in]   pDisplayCtx        - Pointer to DP Context
* \param [in]   bEnable            - Flag used to determine if FEC needs to be enabled/disabled
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_FEC_ConfigureSink(DP_DisplayCtxType *pDisplayCtx, bool32 bEnable)
{
  DP_Status               eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType       *pDeviceCtx;
  DP_StreamCtxType       *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) ||
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_DSC_ConfigureSink: Unexpected null context.");
  }
  else if (pStreamCtx->sFECCaps.bCapable)
  {
    if (DP_STATUS_SUCCESS != (eStatus = DP_WriteSinkFECConfig(pDisplayCtx, bEnable)))
    {
      TraceInfo(QdiTraceDP, "DP%i: Failed to configure FEC on sink, disabling DSC and FEC", pStreamCtx->eDisplayID);

      // Unable to enable FEC - remove FEC overhead on link rate
      pStreamCtx->sDSCInfo.bFECEnabled      = FALSE;
      pStreamCtx->sDSCInfo.uFECLinkClkInKhz = pDeviceCtx->uLinkRateInKhz;

      // If FEC failed, then we cannot support DSC
      pStreamCtx->sDSCInfo.bDSCEnabled      = FALSE;
    }
    else
    {
      TraceInfo(QdiTraceDP, "DP%d: FEC enabled on sink, bEnable: %d, status:0x%x", pStreamCtx->eDisplayID, bEnable, eStatus);
    }
  }

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_DSC_QueryInfo()
*/
/*!
* \DESCRIPTION
*      Query DSC information from the sink.
*
* \param [in]   pDisplayCtx        - Pointer to DP Context
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status DP_DSC_QueryInfo(DP_DisplayCtxType *pDisplayCtx)
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
    if (pDeviceCtx->sSinkDPCDCap.eDPCDMajorRev >= DP_DPCD_MAJORREV_1_4)
    {
      /* Read DSC information */
      if (DP_STATUS_SUCCESS != (eStatus = DP_ReadSinkDSCCap(pDisplayCtx)))
      {
        TraceInfo(QdiTraceDP, "DP%i: Failed to Read Sink DSC capabilities", pStreamCtx->eDisplayID);
      }

      /* DSC is not disabled */
      if ((0           == (DP_HOST_FLAG_DISABLE_DSC & pDeviceCtx->uFlags)) &&
          (DP_CAPS_DSC == (DP_CAPS_DSC & pDeviceCtx->eCapabilityMask)))
      {
        pStreamCtx->sDSCInfo.bDSCEnabled        = pStreamCtx->sDSCCaps.bSupported;
        pStreamCtx->sDSCInfo.uMajorVersion      = pStreamCtx->sDSCCaps.uMajor;
        pStreamCtx->sDSCInfo.uMinorVersion      = pStreamCtx->sDSCCaps.uMinor;

        // TODO: Determine compression ratio from DPCD.
        // Initializing this here, earlier to DP_DSC_CalculateParameters since
        // this value is used in mode filtering to account for compression in BW
        pStreamCtx->sDSCInfo.uCompressionRatio  = DP_DSC_COMPRESSION_RATIO;
      }
    }
  }

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_FEC_QueryInfo()
*/
/*!
* \DESCRIPTION
*      Query FEC information from the sink.
*
* \param [in]   pDisplayCtx        - Pointer to DP Context
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status DP_FEC_QueryInfo(DP_DisplayCtxType *pDisplayCtx)
{
  DP_Status               eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType       *pDeviceCtx;
  DP_StreamCtxType       *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) ||
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_FEC_QueryInfo: Unexpected null context.");
  }
  else if (pDeviceCtx->sSinkDPCDCap.eDPCDMajorRev >= DP_DPCD_MAJORREV_1_4)
  {
    /* Read FEC information */
    if (DP_STATUS_SUCCESS != (eStatus = DP_ReadSinkFECCap(pDisplayCtx)))
    {
      TraceInfo(QdiTraceDP, "DP%i: Failed to Read Sink FEC capabilities", pStreamCtx->eDisplayID);
    }

    if ((0           == (DP_HOST_FLAG_DISABLE_DSC & pDeviceCtx->uFlags)) &&
        (DP_CAPS_DSC == (DP_CAPS_DSC & pDeviceCtx->eCapabilityMask)))
    {
      pStreamCtx->sDSCInfo.bFECEnabled = pStreamCtx->sFECCaps.bCapable;
    }
  }

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_DSC_CalculateParameters()
*/
/*!
* \DESCRIPTION
*      Calculate DSC Slice info (height, width and slice per line).
*
* \param [in]   pDisplayCtx        - Pointer to DP Context
* \param [in]   uModeIdx           - Index of the mode to use for calculation
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status DP_DSC_CalculateParameters(DP_DisplayCtxType *pDisplayCtx, uint32 uModeIdx)
{
  DP_Status               eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType       *pDeviceCtx;
  DP_StreamCtxType       *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_DSC_CalculateParameters: Unexpected null context.");
  }
  else
  {
    DP_DSCInfoType        *pDSCInfo          = &(pStreamCtx->sDSCInfo);
    
    if ((uModeIdx >= MAX_DP_PANEL_MODE) ||
        (0 == pStreamCtx->sPanelInfo[uModeIdx].uPclkFreq))
    {
      eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    }
    else if (TRUE == pDSCInfo->bDSCEnabled)
    {      
      if (DP_STATUS_SUCCESS != (eStatus = CalculateSliceDimensions(pStreamCtx, uModeIdx)))
      {
        TraceInfo(QdiTraceDP, "DP%i: Failed to calculate slice dimensions", pStreamCtx->eDisplayID);
      }
      else
      {
        DP_PanelInfoType  *psPanelInfo       = &(pStreamCtx->sPanelInfo[uModeIdx]);
        uint32             uBPP              = DPHOST_GETPIXELFMT(psPanelInfo->eColorFormat).uBitsPerPixel;
        uint32             uSliceWidth       = pStreamCtx->sDSCInfo.uSliceWidth;
        uint32             uSlicesPerLine    = pStreamCtx->sDSCInfo.uSlicesPerLine;
        uint32             uWidthBytesSlice;
        uint32             uEOCBytes;
        uint32             uTotalEOCNumber;
        uint32             uTotalHorizontalBytes;
        uint32             uTotalDummyBytes;
        uint32             uNumLanes;
        uint32             uDSCWidthBytes;
        uint32             uHBP;

        /* Always send total of 4 EOCs regardless of number of active lanes in case of MST */
        uNumLanes                      = (pDeviceCtx->bMSTEnabled) ? 4 : pDeviceCtx->uNumLanes;

        /* Width bytes per slice after compression */
        uWidthBytesSlice               = ((uSliceWidth * uBPP) / 8) / pDSCInfo->uCompressionRatio;
        uEOCBytes                      = uSliceWidth % uNumLanes;
        uTotalEOCNumber                = uNumLanes * uSlicesPerLine;
        uTotalHorizontalBytes          = uWidthBytesSlice * uSlicesPerLine;
        uTotalDummyBytes               = (uNumLanes - uEOCBytes) * uSlicesPerLine;
        uDSCWidthBytes                 = uTotalHorizontalBytes + uTotalEOCNumber + (uEOCBytes == 0 ? 0 : uTotalDummyBytes);
        pStreamCtx->sDSCInfo.uDSCWidth = (uDSCWidthBytes * 8) / uBPP;
        uHBP                           = psPanelInfo->uHsyncFrontPorchInPixels +
                                         psPanelInfo->uHsyncBackPorchInPixels +
                                         psPanelInfo->uHsyncPulseInPixels;
    
        /* pclk_dsc = original pclk * dsc width / old width */
        pStreamCtx->sDSCInfo.uDSCPixelClkInKhz        = (psPanelInfo->uPclkFreq  / 1000) * pStreamCtx->sDSCInfo.uDSCWidth / psPanelInfo->uVisibleWidthInPixels;
        /* DSC pixels per line = ceil(ceil(ceil(horizontal active / number of slices) * (uncompressed bpp / compression ratio)  * (1 / 8)) * number of slices * (1 / databus widen ? 6 : 3)) */
        pStreamCtx->sDSCInfo.uDSCPixelsPerLine        = DPHOST_CEIL(DPHOST_CEIL(DPHOST_CEIL(psPanelInfo->uVisibleWidthInPixels, uSlicesPerLine) * (uBPP/pDSCInfo->uCompressionRatio), 8) * uSlicesPerLine, 6); // "PCLK cycles required" equation from DP HPG adjusted for 2 ppc
        pStreamCtx->sDSCInfo.fDSCOverheadRatio        = ((float)uDSCWidthBytes)/uTotalHorizontalBytes;
        pStreamCtx->sDSCInfo.uInputBitsPerComponent   = uBPP / 3;
        pStreamCtx->sDSCInfo.uOutputBitsPerPixel      = uBPP / pDSCInfo->uCompressionRatio;
        pStreamCtx->sDSCInfo.dDSCHBlankPeriod = ((double)uHBP * pStreamCtx->sDSCInfo.uDSCPixelClkInKhz / psPanelInfo->uPclkFreq);

        GetDTONumDem(pDSCInfo->uCompressionRatio, uBPP, &pDSCInfo->uDSCDTONumerator, &pDSCInfo->uDSCDTODenominator);
      }
    }
    else
    {
      eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
    }
  }

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_FEC_CalculateParameters()
*/
/*!
* \DESCRIPTION
*      Calculate FEC info (adjusted link rate).
*
* \param [in]   pDisplayCtx        - Pointer to DP Context
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status DP_FEC_CalculateParameters(DP_DisplayCtxType *pDisplayCtx)
{
  DP_Status               eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType       *pDeviceCtx;
  DP_StreamCtxType       *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) ||
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_FEC_CalculateParameters: Unexpected null context.");
  }
  else if (TRUE == pStreamCtx->sDSCInfo.bFECEnabled)
  {
    /* Link rate adjusted for FEC overhead */
    pStreamCtx->sDSCInfo.uFECLinkClkInKhz = (uint32)((float)pDeviceCtx->uLinkRateInKhz * DP_LINKRATE_FEC_OVERHEAD_RATIO);
  }
  else
  {
    pStreamCtx->sDSCInfo.uFECLinkClkInKhz = pDeviceCtx->uLinkRateInKhz;
  }

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_DSC_ConfigureSource()
*/
/*!
* \DESCRIPTION
*      Configure DSC in DP controller
*
* \param [in]   pDisplayCtx      - Pointer to DP Context
* \param [in]   bEnable          - Flag used to determine if DSC needs to be enabled/disabled
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status DP_DSC_ConfigureSource(DP_DisplayCtxType  *pDisplayCtx, bool32 bEnable)
{
  DP_Status               eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType       *pDeviceCtx;
  DP_StreamCtxType       *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_DSC_ConfigureSource: Unexpected null context.");
  }
  else
  {
    HAL_DP_DSCConfigType    sHALDSCConfig;
    
    DP_OSAL_MemSet(&sHALDSCConfig, 0, sizeof(HAL_DP_DSCConfigType));
    
    /* DSC Configuration */
    sHALDSCConfig.bCompressed = bEnable;
    sHALDSCConfig.uStreamId   = pStreamCtx->eMSTStreamId;
    sHALDSCConfig.uBeInLane   = CalculateBlankEndInLane(pStreamCtx, bEnable, pDeviceCtx->bMSTEnabled);
    
    if (TRUE == bEnable)
    {
      DP_PanelInfoType *psPanelInfo = &(pStreamCtx->sPanelInfo[pStreamCtx->uModeIndex]);
      
      sHALDSCConfig.uSlicesPerLine             = pStreamCtx->sDSCInfo.uSlicesPerLine;
      sHALDSCConfig.uTargetBppUncompressed     = DPHOST_GETPIXELFMT(psPanelInfo->eColorFormat).uBitsPerPixel;
      sHALDSCConfig.uSliceWidth                = pStreamCtx->sDSCInfo.uSliceWidth;
      sHALDSCConfig.uCompressionRatio          = pStreamCtx->sDSCInfo.uCompressionRatio;
      sHALDSCConfig.uCompressedPixelsPerLine   = pStreamCtx->sDSCInfo.uDSCPixelsPerLine;
      sHALDSCConfig.uDTONumerator              = pStreamCtx->sDSCInfo.uDSCDTONumerator;
      sHALDSCConfig.uDTODenominator            = pStreamCtx->sDSCInfo.uDSCDTODenominator;
    }
    
    // Configure DSC on the controller
    HAL_DP_SetDSCConfig(pDeviceCtx->eControllerID, &sHALDSCConfig);
  }

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_FEC_Decode_Status()
*/
/*!
* \DESCRIPTION
*      Read FEC status to check if "Decode enable" is detected
*
* \param [in]   pDisplayCtx      - Pointer to DP Context
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status DP_FEC_Decode_Status (DP_DisplayCtxType  *pDisplayCtx)
{
  DP_Status               eStatus           = DP_STATUS_SUCCESS;
  DP_DeviceCtxType       *pDeviceCtx;
  DP_StreamCtxType       *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_DSC_CalculateParameters: Unexpected null context.");
  }
  else if (TRUE == pStreamCtx->sDSCInfo.bFECEnabled)
  {  
    if ((DP_STATUS_SUCCESS != DP_ReadSinkFECEnable(pDisplayCtx))  ||
        (DP_STATUS_SUCCESS != DP_ReadSinkFECStatus(pDisplayCtx)))
    {
      eStatus                           = DP_STATUS_FAILED_RESOURCE_NOT_READY;
      pStreamCtx->sDSCInfo.bDSCEnabled  = FALSE;
    }
  }

  return eStatus;
}


/*--------------------------------------------------------------------------------------------
 * Private Functions
 *------------------------------------------------------------------------------------------*/

/*********************************************************************************************
*
** FUNCTION: CalculateSliceDimensions
*/
/*!
* \DESCRIPTION
*      Get DSC Slice info (height, width and slice per line).
*
* \param [in]   pStreamCtx        - Pointer to stream context
* \param [in]   uModeIdx          - Index of the mode to use for calculation
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status CalculateSliceDimensions(DP_StreamCtxType *pStreamCtx, uint32 uModeIdx)
{
  DP_Status                  eStatus          = DP_STATUS_SUCCESS;
  DP_PanelInfoType          *psPanelInfo      = &(pStreamCtx->sPanelInfo[uModeIdx]);
  uint32                     uPixelRate       = psPanelInfo->uPclkFreq;
  uint32                     uIndex           = 0;
  uint32                     uSlicesPerLine   = 0;
  PeakPixelRateToSliceType   sPPRSliceTable[] = {
                                                { 340,   1},
                                                { 680,   2},
                                                {1360,   4},
                                                {3200,   8},
                                                {4800,  12},
                                                {6400,  16},
                                                {8000,  20},
                                                {9600,  24},
                                                {   0,   0},
                                                };

  for (uIndex = 0; uIndex < sizeof(sPPRSliceTable) / sizeof(PeakPixelRateToSliceType); uIndex++)
  {
    if (uPixelRate <= (sPPRSliceTable[uIndex].uPeakPixelRateMHz * 1000000))
    {
      uSlicesPerLine = sPPRSliceTable[uIndex].uSlicePerLine;
      break;
    }
  }
  
  if (0 == uSlicesPerLine)
  {
    // Unable to find valid slices per line.
    eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
  }
  else
  {
    uint32            aSliceHeight[] = {40, 36, 32, 30, 25, 24, 20, 16, 15};
    uint32            uVisWidth      = psPanelInfo->uVisibleWidthInPixels;
    uint32            uVisHeight     = psPanelInfo->uVisibleHeightInPixels;
    uint32            uSliceWidth    = 0;
    uint32            uSliceHeight   = 0;

    uSliceWidth  = (uVisWidth / uSlicesPerLine);
    
    /* check slice width against max slice width */
    if (pStreamCtx->sDSCCaps.uMaxSliceWidth > 0)
    {
      while (uSliceWidth > pStreamCtx->sDSCCaps.uMaxSliceWidth)
      {
        // Reduce it by half till its less than max allowed
        uSliceWidth    >>= 1;
        uSlicesPerLine <<= 1;
      }
    }
    
    /* calculate slice height  */
    for (uIndex = 0; uIndex < sizeof(aSliceHeight) / sizeof(uint32); uIndex++)
    {
      if (0 == (uVisHeight % aSliceHeight[uIndex]))
      {
        uSliceHeight = aSliceHeight[uIndex];
        break;
      }
    }

    if (0 == uSliceHeight)
    {
      uSliceHeight = uVisHeight;
      DP_LOG_MESSAGE_WARN("DP_DSC_SliceHeight: Warning, No proper Slice Height Found for Picture Height=%d, default slice height is picture height.\n", uVisHeight);
    }

    pStreamCtx->sDSCInfo.uSliceHeight   = uSliceHeight;
    pStreamCtx->sDSCInfo.uSliceWidth    = uSliceWidth;
    pStreamCtx->sDSCInfo.uSlicesPerLine = uSlicesPerLine;
  }

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: GetDTONumDem()
*/
/*!
* \DESCRIPTION
*      Returns the DSC DTO numerator and denominator configuration for the corresponding
*      compression ratio and the uncompressed BPP.
*
* \param [in]    uCompressionRatio    - DSC compression ratio
* \param [in]    uTargetBpp           - Uncompressed bits per pixel.
* \param [out]   pNumerator           - Pointer to the write to the DSC DTO numerator
* \param [out]   pDenominator         - Pointer to the write to the DSC DTO denominator
*
* \retval None
*
**********************************************************************************************/
static void GetDTONumDem(uint32  uCompressionRatio,
                         uint32  uTargetBpp,
                         uint32 *pNumerator,
                         uint32 *pDenominator)
{
  uint32 uIndex         = 0;
  uint32 uLen           = sizeof(gDSCDTORatioLUT) / sizeof(gDSCDTORatioLUT[0]);
  uint32 uNumerator     = 1;
  uint32 uDenominator   = 1;

  for (uIndex = 0; uIndex < uLen; uIndex++)
  {
    if ((gDSCDTORatioLUT[uIndex].uCompressionRatio == uCompressionRatio) &&
        (gDSCDTORatioLUT[uIndex].uBitsPerPixel     == uTargetBpp))
    {
      uNumerator   = gDSCDTORatioLUT[uIndex].uNumerator;
      uDenominator = gDSCDTORatioLUT[uIndex].uDenominator;
    }
  }

  *pNumerator   = uNumerator;
  *pDenominator = uDenominator;
}

/*********************************************************************************************
*
** FUNCTION: CalculateBlankEndInLane
*/
/*!
* \DESCRIPTION
*      BE_IN_LANE is only used when MST Constant fill and DATABUS_WIDEN are ON.
*      BE_IN_LANE is always set to 10 by default except when DSC is enabled, then it follows  
*      one hot encoding scheme which shows the lane we should send the blank end (BE) packet on. 
*      If 3  >= h compressed total mod 12 > 0, blank end will be on lane 0 (0b0001)
*      If 6  >= h compressed total mod 12 > 3, blank end will be on lane 1 (0b0010)
*      If 9  >= h compressed total mod 12 > 6, blank end will be on lane 2 (0b0100)
*      If 11 >= h compressed total mod 12 > 9, blank end will be on lane 3 (0b1000)
*
* \param [in]   pStreamCtx       - Pointer to stream context
* \param [in]   bDSCEnable       - Flag used to determine if DSC is enabled/disabled
* \param [in]   bMSTEnable       - Flag used to determine if MST is enabled/disabled
*
* \retval BE_IN_LANE
*
**********************************************************************************************/
uint32 CalculateBlankEndInLane(DP_StreamCtxType *pStreamCtx, bool32 bDSCEnable, bool32 bMSTEnable)
{
  uint32 uBeInLane = 10;

  if ((NULL                 == pStreamCtx)             ||
      (DP_HOST_MODE_INVALID == pStreamCtx->uModeIndex) ||
      (MAX_DP_PANEL_MODE    <= pStreamCtx->uModeIndex))
  {
    DP_LOG_MESSAGE_ERROR("CalculateBlankEndInLane failed: Invalid parameter.");
  }
  // MST Constant Fill is always set to 1 if MST is enabled
  else if ((bDSCEnable) && 
           (bMSTEnable))
  {    
    DP_PanelInfoType *psPanelInfo = &(pStreamCtx->sPanelInfo[pStreamCtx->uModeIndex]);

    uint32 uHTotal            = 0;
    uint32 uCompressedHTotal  = 0;
    uint32 uModResult         = 0;

    uHTotal           = psPanelInfo->uVisibleWidthInPixels    + 
                        psPanelInfo->uHsyncFrontPorchInPixels + 
                        psPanelInfo->uHsyncBackPorchInPixels  + 
                        psPanelInfo->uHsyncPulseInPixels;
    uCompressedHTotal = (uint32)DPHOST_CEIL((uHTotal * pStreamCtx->uBitDepth * DP_NUM_COLOR_COMPONENTS), (8.0 * pStreamCtx->sDSCInfo.uCompressionRatio));

    // Determine which lane the BE will appear on by taking the modulus of H Total in compressed byte count by 12.
    uModResult        = uCompressedHTotal % 12;

    if (0 == uModResult)
    {
      uBeInLane = 8;
    }
    else if (3 >= uModResult)
    {
      uBeInLane = 1;
    }
    else if (6 >= uModResult)
    {
      uBeInLane = 2;
    }
    else if (9 >= uModResult)
    {
      uBeInLane = 4;
    }
    else if (11 >= uModResult)
    {
      uBeInLane = 8;
    }
  }
  return uBeInLane;
}

#ifdef __cplusplus
}
#endif

