/*=============================================================================
  Copyright (c) 2021-2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* -----------------------------------------------------------------------
** Includes
** ----------------------------------------------------------------------- */
#include "displayid.h"
#include "edid.h"


#define DP_LOG_MESSAGE_ERROR(fmt, ...)     MDP_Log_Message(MDP_LOGLEVEL_ERROR, fmt, ##__VA_ARGS__)
/* -----------------------------------------------------------------------
** Enums
** ----------------------------------------------------------------------- */

//-------------------------------------------------------------------------------------------------
//  DisplayId_Video_AspectRatio
//
//  @brief
//      Defines the aspect ratio of the input video format 
//-------------------------------------------------------------------------------------------------
//
typedef enum
{
  //DISPLAYID_VIDEO_ASPECT_RATIO_NONE,
  DISPLAYID_VIDEO_ASPECT_RATIO_1_1,
  DISPLAYID_VIDEO_ASPECT_RATIO_5_4,
  DISPLAYID_VIDEO_ASPECT_RATIO_4_3,
  DISPLAYID_VIDEO_ASPECT_RATIO_15_9,
  DISPLAYID_VIDEO_ASPECT_RATIO_16_9,
  DISPLAYID_VIDEO_ASPECT_RATIO_16_10,
  DISPLAYID_VIDEO_ASPECT_RATIO_64_27,
  DISPLAYID_VIDEO_ASPECT_RATIO_256_135,
  DISPLAYID_VIDEO_ASPECT_RATIO_NOT_DEFINED,
  DISPLAYID_VIDEO_ASPECT_RATIO_RESERVED,
  DISPLAYID_VIDEO_ASPECT_RATIO_MAX,
  DISPLAYID_VIDEO_ASPECT_RATIO_FORCE_32BIT,
} DisplayId_Video_AspectRatio;

/* -----------------------------------------------------------------------
** Structures
** ----------------------------------------------------------------------- */

//-------------------------------------------------------------------------------------------------
//  EDID_DispModeTimingType
//
//  @brief
//      Structure holds info specific to video format such as timing, mode capabilities
//
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
  uint32                      uActiveH;             /**< Horizontal active pixels */
  uint32                      uFrontPorchH;         /**< Horizontal front porch pixels */
  uint32                      uPulseWidthH;         /**< Horizontal sync pulse width pixels */
  uint32                      uBackPorchH;          /**< Horizontal back porch pixels */
  uint32                      uTotalBlankH;         /**< Horizontal blanking pixels */
  bool32                      bActiveLowH;          /**< Horizontal sync polarity */
  uint32                      uActiveV;             /**< Vertical active pixels */
  uint32                      uFrontPorchV;         /**< Vertical front porch pixels */
  uint32                      uPulseWidthV;         /**< Vertical sync pulse width pixels */
  uint32                      uBackPorchV;          /**< Vertical back porch pixels */
  uint32                      uTotalBlankV;         /**< Vertical blanking pixels */
  bool32                      bActiveLowV;          /**< Vertical sync polarity */
  uint32                      uPixelFreq;           /**< Must divide by 1000 to get the actual frequency in MHZ */
  uint32                      uRefreshRate;         /**< Must divide by 1000 to get the actual frequency in HZ */
  bool32                      bInterlaced;          /**< Indicates format is interlaced or not */
  EDID_SpecificationType      eEDIDSpecType;        /**< HDMI/DP specification type */
  uint32                      uPixelRepeatFactor;   /**< Pixel repetition factor denoted as 2^n where is n is the repetition factor */
  DisplayId_Video_AspectRatio eAspectRatio;         /**< Aspect ratio of the format */
  DisplayId_Video_3DStereo    e3DStereoSupport;     /**< 3D Stereo support */
  EDID_Standard_Type          eStandard;            /**< Indicates the EDID standard */
} DisplayId_DispModeTimingType;

/* -----------------------------------------------------------------------
** Functions
** ----------------------------------------------------------------------- */

/* DisplayId_DataBlockOffsetSetup
 */
static MDP_Status DisplayId_DataBlockOffsetSetup(EDID_ParserContextType* pEdidSharedData, uint8* pDataBuf, uint32 uNumOfCEABlocks, DisplayId_ParserInfoType* pDisplayIdInfo);

/* DisplayId_Parser_Detail_Desc
 */
static MDP_Status DisplayId_Parser_Detail_Desc(EDID_ParserContextType* pEdidSharedData, uint8* pDataBuf, DisplayId_Version eDisplayID_Version, uint32 uDataBlockSize);

/* DisplayId_Parser_Detail_Timing
 */
static MDP_Status DisplayId_Parser_Detail_Timing(EDID_ParserContextType* pEdidSharedData, uint8* pDataBuf, DisplayId_Version eDisplayID_Version, uint32 uTimingBlockIndex);

/* DisplayId_Parser_DID_2_0
 */
static MDP_Status DisplayId_Parser_DID_2_0(EDID_ParserContextType* pEdidSharedData, DisplayId_ParserInfoType* pDisplayIdInfo);

/* DisplayId_Parser_DID_1_3
 */
static MDP_Status DisplayId_Parser_DID_1_3(EDID_ParserContextType* pEdidSharedData, DisplayId_ParserInfoType* pDisplayIdInfo);

//-------------------------------------------------------------------------------------------------
//  DisplayId_DataBlockOffsetSetup
//
//  @brief
//      Initializes the various data block offsets of the DisplayId.
//
//  @params
//      [IN] pEdidSharedData
//          EDID parser context.
//      [IN] pDataBuf
//          Buffer that contains DisplayId data.
//      [IN] uNumOfCEABlocks
//          Number of CEA blocks in this EDID.
//      [OUT] pDisplayIdInfo
//          DisplayId Information
//
//  @return
//      eStatus.
//-------------------------------------------------------------------------------------------------
//
static MDP_Status DisplayId_DataBlockOffsetSetup(EDID_ParserContextType* pEdidSharedData, uint8* pDataBuf, uint32 uNumOfCEABlocks, DisplayId_ParserInfoType* pDisplayIdInfo)
{
  MDP_Status eStatus              = MDP_STATUS_SUCCESS;
  uint32     uWorkingOffset       = 0;
  uint32     uExBlockLastOffset   = 0;
  uint32     uStartingOffset      = 0;
  uint32     uDataBlockLastOffset = 0;
  uint32     uDataTagCode         = 0;
  uint32     uNumOfBytes          = 0;
  uint32     uI                   = 0;
  uint32     uNumOfBlocks         = (uNumOfCEABlocks > EDID_MAX_NUM_OF_CEA_EXTENSION_BLOCKS) ? EDID_MAX_NUM_OF_CEA_EXTENSION_BLOCKS : uNumOfCEABlocks;
 
  if(uNumOfBlocks == 0)
  {
    eStatus = MDP_STATUS_NO_RESOURCES;
    DISP_OSAL_LOG_INFO("DisplayId_DataBlockOffsetSetup: Extension Block is not present\n");
  }
  else
  {
    /* Initialize global variable for all the data block offsets to be 0 */
    DISP_OSAL_MemZero(&pEdidSharedData->sDisplayIdDataBlock, sizeof(DisplayId_DataBlockType));
  
    /* Check if 1st extension block is treated as EDID Block Map Extension*/
    if (EDID_EXTENSION_BLOCK_MAP_TAG_CODE == pDataBuf[EDID_BLOCK_SIZE] )
    {
      uStartingOffset += EDID_BLOCK_SIZE;

      if (uNumOfBlocks)
      {
        uNumOfBlocks -= 1;
      }
    }
  
    for (uI = 0; uI < uNumOfBlocks; uI++)
    {
      /* Beginning of each extension block */
      uStartingOffset   += EDID_BLOCK_SIZE;
      uExBlockLastOffset = uStartingOffset + EDID_BLOCK_SIZE;
      uWorkingOffset     = uStartingOffset;

      if (DISPLAYID_EDID_EXTENSION_TAG_CODE == pEdidSharedData->auEDIDCache[uWorkingOffset])
      {
        uWorkingOffset++;

        if (DISPLAYID_VERSION_1_2 == pEdidSharedData->auEDIDCache[uWorkingOffset])
        {
          pDisplayIdInfo->eDIDVersion = DISPLAYID_VERSION_1_2;
        }
        else if (DISPLAYID_VERSION_1_3 == pEdidSharedData->auEDIDCache[uWorkingOffset])
        {
          pDisplayIdInfo->eDIDVersion = DISPLAYID_VERSION_1_3;
        }
        else if (DISPLAYID_VERSION_2_0 >= pEdidSharedData->auEDIDCache[uWorkingOffset])
        {
          // DisplayId v2.0 and higher versions, all are treated as Version 2.0 only.
          pDisplayIdInfo->eDIDVersion = DISPLAYID_VERSION_2_0;
        }
        break;
      }
    }

    if ((MDP_STATUS_SUCCESS         != eStatus)      ||
        ((uI                        == uNumOfBlocks) &&
         (DISPLAYID_VERSION_INVALID == pDisplayIdInfo->eDIDVersion)))
    {
      eStatus = MDP_STATUS_INVALID_STATE;
      DISP_OSAL_LOGX("DisplayId_DataBlockOffsetSetup: failed, valid DisplayId version not found");
    }
    else
    {
      uWorkingOffset = uStartingOffset + DISPLAYID_DATA_BLOCK_RELATIVE_OFFFSET;

      do
      {
        uDataTagCode         = pDataBuf[uWorkingOffset];
        uNumOfBytes          = pDataBuf[uWorkingOffset + DISPLAYID_DETAILED_TIMING_PAYLOAD_SIZE_OFFSET];
        uDataBlockLastOffset = uWorkingOffset + uNumOfBytes + DISPLAYID_DATA_BLOCK_HEADER_SIZE;

        // Check if Data block fits within DisplayID (as EDID extension) block 
        if (uExBlockLastOffset  < uDataBlockLastOffset)
        {
          eStatus = MDP_STATUS_INVALID_STATE;
          DISP_OSAL_LOGX("DisplayId_DataBlockOffsetSetup: data block for TagCode = 0x%x, doesn't fit within DisplayID (as EDID extension) block", uDataTagCode);
          break;
        }

        switch (uDataTagCode)
        {
          case DISPLAYID_V1_3_PRODUCT_IDENTIFICATION_BLOCK_TAG_CODE:
          case DISPLAYID_V2_0_PRODUCT_IDENTIFICATION_BLOCK_TAG_CODE:
          {
            pEdidSharedData->sDisplayIdDataBlock.sProductIdentificationDesc.uProductIdentificationOffset           = uWorkingOffset;
            pEdidSharedData->sDisplayIdDataBlock.sProductIdentificationDesc.uDataBlockLength                       = uNumOfBytes;

            break;
          }
          case DISPLAYID_TYPEVII_TIMING_BLOCK_TAG_CODE:
          case DISPLAYID_TYPEI_TIMING_BLOCK_TAG_CODE:
          {
            uint32 uTimingBlockNum = pEdidSharedData->sDisplayIdDataBlock.sDetailTimingBlockDesc.uNumTimingBlocks;

            pEdidSharedData->sDisplayIdDataBlock.sDetailTimingBlockDesc.uDetailTimingIBlockOffset[uTimingBlockNum] = uWorkingOffset;
            pEdidSharedData->sDisplayIdDataBlock.sDetailTimingBlockDesc.uDataBlockLength[uTimingBlockNum]          = uNumOfBytes;
            pEdidSharedData->sDisplayIdDataBlock.sDetailTimingBlockDesc.uNumTimingBlocks++;

            break;
          }
          case DISPLAYID_V1_3_DISPLAY_PARAMETERS_DATA_BLOCK_TAG_CODE:
          case DISPLAYID_V2_0_DISPLAY_PARAMETERS_DATA_BLOCK_TAG_CODE:
          {
            pEdidSharedData->sDisplayIdDataBlock.sDisplayParametersDataBlock.uDisplayParametersDataBlockOffset     = uWorkingOffset;
            pEdidSharedData->sDisplayIdDataBlock.sDisplayParametersDataBlock.uDataBlockLength                      = uNumOfBytes;

            break;
          }
          case DISPLAYID_V1_3_DISPLAY_INTERFACE_DATA_BLOCK_TAG_CODE:
          case DISPLAYID_V2_0_DISPLAY_INTERFACE_DATA_BLOCK_TAG_CODE:
          {
            pEdidSharedData->sDisplayIdDataBlock.sDisplayInterfaceDataBlock.uDisplayInterfaceDataBlockOffset       = uWorkingOffset;
            pEdidSharedData->sDisplayIdDataBlock.sDisplayInterfaceDataBlock.uDataBlockLength                       = uNumOfBytes;

            break;
          }
          case DISPLAYID_TOPOLOGY_DATA_BLOCK_TAG_CODE:
          {
            pEdidSharedData->sDisplayIdDataBlock.sDisplayTopologyBlockDesc.uDisplayTopologyDataBlockOffset         = uWorkingOffset;
            pEdidSharedData->sDisplayIdDataBlock.sDisplayTopologyBlockDesc.uDataBlockLength                        = uNumOfBytes;

            break;
          }
          case DISPLAYID_COLOR_CHARACTERISTIC_DATA_BLOCK_TAG_CODE:
          {
            pEdidSharedData->sDisplayIdDataBlock.sDisplayColorCharacteristicBlock.uColorCharacteristicBlockOffset  = uWorkingOffset;
            pEdidSharedData->sDisplayIdDataBlock.sDisplayColorCharacteristicBlock.uDataBlockLength                 = uNumOfBytes;

            break;
          }
          default:
          {
            DISP_OSAL_LOGX("DisplayId_DataBlockOffsetSetup: uDataTagCode = 0x%x, not supported", uDataTagCode) ;

            break;
          }
        }
        // Update offset to point to next Data block.
        uWorkingOffset += uNumOfBytes + DISPLAYID_DATA_BLOCK_HEADER_SIZE;

      }while((uWorkingOffset < (uStartingOffset + EDID_BLOCK_SIZE)) &&
             ((uDataTagCode  != 0x0)                                && 
              (uNumOfBytes   != 0x0)));
    }
  }
  
  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DisplayId_Parser_Detail_Desc
//
//  @brief
//      Parses the DisplayId structure and find out all the video mode supported 
//      using detailed timing descriptors.
//
//  @params
//      [IN] pEdidSharedData
//          DisplayID parser context
//      [IN] pDataBuf
//          Buffer that contains Timing block data.
//      [IN] eDisplayID_Version
//          Indicates for which DIsplayId Version Detailed Timing to be parsed.
//      [IN] uDataBlockSize
//          Data block payload size.
//
//  @return
//      MDP_STATUS_SUCCESS if matching mode is found.
//-------------------------------------------------------------------------------------------------
//
static MDP_Status DisplayId_Parser_Detail_Desc(EDID_ParserContextType* pEdidSharedData, uint8* pDataBuf, DisplayId_Version eDisplayID_Version, uint32 uDataBlockSize)
{
  MDP_Status eStatus = MDP_STATUS_SUCCESS;

  if ((NULL                                   == pDataBuf)        ||
      (NULL                                   == pEdidSharedData) ||
      (DISPLAYID_DETAILED_TIMING_PAYLOAD_SIZE >  uDataBlockSize))
  {
    eStatus = MDP_STATUS_BAD_PARAM;
    DISP_OSAL_LOGX("DisplayId_Parser_Detail_Desc failed with status = 0x%x", eStatus);
  }
  else
  {
    EDID_DispModeListType   *pDispModeList = &pEdidSharedData->sDispModeList;
    bool32                   bMatchFound   = FALSE;
    EDID_DispModeTimingType  sModeInfo;
    uint32                   uDivisor;

    DISP_OSAL_MemZero((void*)&sModeInfo, sizeof(EDID_DispModeTimingType));

    // Parse Pixel frequency
    sModeInfo.uPixelFreq       = pDataBuf[DISPLAYID_TIMING_PIXEL_CLOCK_UPPER_BYTE_OFFSET];
    sModeInfo.uPixelFreq     <<= 8;
    sModeInfo.uPixelFreq      |= (uint32)pDataBuf[DISPLAYID_TIMING_PIXEL_CLOCK_MIDDLE_BYTE_OFFSET];
    sModeInfo.uPixelFreq     <<= 8;
    sModeInfo.uPixelFreq      |= (uint32)pDataBuf[DISPLAYID_TIMING_PIXEL_CLOCK_LOWER_BYTE_OFFSET];

    if ((DISPLAYID_VERSION_1_3 == eDisplayID_Version) ||
        (DISPLAYID_VERSION_1_2 == eDisplayID_Version))
    {
      // Must multiply by 10 to convert to KHZ for LUT search
      sModeInfo.uPixelFreq    *= 10;
    }

    // Aspect Ratio
    switch (pDataBuf[DISPLAYID_TIMING_OPTIONS] & DISPLAYID_TIMING_ASPECT_RATIO_MASK)
    {
      case 0x0:
      {
        sModeInfo.eAspectRatio = EDID_VIDEO_ASPECT_RATIO_1_1;
        break;
      }
      case 0x1:
      {
        sModeInfo.eAspectRatio = EDID_VIDEO_ASPECT_RATIO_5_4;
        break;
      }
      case 0x2:
      {
        sModeInfo.eAspectRatio = EDID_VIDEO_ASPECT_RATIO_4_3;
        break;
      }
      case 0x3:
      {
        sModeInfo.eAspectRatio = EDID_VIDEO_ASPECT_RATIO_15_9;
        break;
      }
      case 0x4:
      {
        sModeInfo.eAspectRatio = EDID_VIDEO_ASPECT_RATIO_16_9;
        break;
      }
      case 0x5:
      {
        sModeInfo.eAspectRatio = EDID_VIDEO_ASPECT_RATIO_16_10;
        break;
      }
      case 0x6:
      {
        sModeInfo.eAspectRatio = EDID_VIDEO_ASPECT_RATIO_64_27;
        break;
      }
      case 0x7:
      {
        sModeInfo.eAspectRatio = EDID_VIDEO_ASPECT_RATIO_256_135;
        break;
      }
      case 0x8:
      {
        // Aspect ratio shall be calculated by using the Horizontal Active Image Pixels
        // and Vertical Active Image Lines fields
        sModeInfo.eAspectRatio = EDID_VIDEO_ASPECT_RATIO_NONE;
        break;
      }
      default :
      {
        sModeInfo.eAspectRatio = EDID_VIDEO_ASPECT_RATIO_NONE;
        break; 
      }
    }

    // Stereo Support
    sModeInfo.e3DStereoSupport = pDataBuf[DISPLAYID_TIMING_OPTIONS] & DISPLAYID_TIMING_STEREO_SUPPORT;

    // Interlaced Frame Scanning
    sModeInfo.uModeFlags      |= (pDataBuf[DISPLAYID_TIMING_OPTIONS] & DISPLAYID_TIMING_FRAME_SCAN) ? MODE_FLAG_INTERLACED : 0 ;

    // Timing Option (Preferred mode flag)
    sModeInfo.uModeFlags      |= (pDataBuf[DISPLAYID_TIMING_OPTIONS] & DISPLAYID_TIMING_PREFERRED_DETAILED_TIMING) ? MODE_FLAG_PREFERRED_MODE : 0;

    // Horizontal Active Image Pixels
    sModeInfo.uActiveH         = (uint32)pDataBuf[DISPLAYID_TIMING_H_ACTIVE_UPPER];
    sModeInfo.uActiveH       <<= 8;
    sModeInfo.uActiveH        |= (uint32)pDataBuf[DISPLAYID_TIMING_H_ACTIVE_LOWER];
    sModeInfo.uActiveH++;

    // Horizontal Blank Pixels
    sModeInfo.uTotalBlankH     = (uint32)pDataBuf[DISPLAYID_TIMING_H_BLANK_UPPER];
    sModeInfo.uTotalBlankH   <<= 8;
    sModeInfo.uTotalBlankH    |= (uint32)pDataBuf[DISPLAYID_TIMING_H_BLANK_LOWER];
    sModeInfo.uTotalBlankH++;

    // Horizontal Offset
    sModeInfo.uFrontPorchH     = (uint32) (pDataBuf[DISPLAYID_TIMING_H_OFFSET_UPPER] & DISPLAYID_TIMING_H_OFFFSET_UPPER_MASK);
    sModeInfo.uFrontPorchH   <<= 8;
    sModeInfo.uFrontPorchH    |= (uint32)pDataBuf[DISPLAYID_TIMING_H_OFFSET_LOWER] ;
    sModeInfo.uFrontPorchH++;

    if ((uint32)pDataBuf[DISPLAYID_TIMING_H_OFFSET_UPPER] & DISPLAYID_TIMING_H_SYNC_POLARITY_MASK)
    {
      // Hsync positive polarity
    }
    else
    {
      // Hsync negative polarity
      sModeInfo.uModeFlags    |= MODE_FLAG_HSYNC_LOW;
    }

    // Horizontal Sync Width
    sModeInfo.uPulseWidthH     = (uint32)pDataBuf[DISPLAYID_TIMING_H_WIDTH_UPPER];
    sModeInfo.uPulseWidthH   <<= 8;
    sModeInfo.uPulseWidthH    |= (uint32)pDataBuf[DISPLAYID_TIMING_H_WIDTH_LOWER];
    sModeInfo.uPulseWidthH++;

    // Vertical Active Image Pixels
    sModeInfo.uActiveV         = (uint32)pDataBuf[DISPLAYID_TIMING_V_ACTIVE_UPPER];
    sModeInfo.uActiveV       <<= 8;
    sModeInfo.uActiveV        |= (uint32)pDataBuf[DISPLAYID_TIMING_V_ACTIVE_LOWER];
    sModeInfo.uActiveV++;

    // Vertical Blank Lines
    sModeInfo.uTotalBlankV     = (uint32)pDataBuf[DISPLAYID_TIMING_V_BLANK_UPPER];
    sModeInfo.uTotalBlankV   <<= 8;
    sModeInfo.uTotalBlankV    |= (uint32)pDataBuf[DISPLAYID_TIMING_V_BLANK_LOWER];
    sModeInfo.uTotalBlankV++;

    // Vertical Sync Offset
    sModeInfo.uFrontPorchV     = (uint32)(pDataBuf[DISPLAYID_TIMING_V_OFFSET_UPPER] & DISPLAYID_TIMING_V_OFFFSET_UPPER_MASK);
    sModeInfo.uFrontPorchV   <<= 8;
    sModeInfo.uFrontPorchV    |= (uint32)pDataBuf[DISPLAYID_TIMING_V_OFFSET_LOWER];
    sModeInfo.uFrontPorchV++;
 
    if ((uint32)pDataBuf[DISPLAYID_TIMING_V_OFFSET_UPPER] & DISPLAYID_TIMING_V_SYNC_POLARITY_MASK)
    {
      // Vsync positive polarity 
    }
    else
    {
      // Vsync negative polarity
      sModeInfo.uModeFlags    |= MODE_FLAG_VSYNC_LOW;
    }

    // Vertical Sync Width
    sModeInfo.uPulseWidthV     = (uint32)pDataBuf[DISPLAYID_TIMING_V_WIDTH_UPPER];
    sModeInfo.uPulseWidthV   <<= 8;
    sModeInfo.uPulseWidthV    |= (uint32)pDataBuf[DISPLAYID_TIMING_V_WIDTH_LOWER];
    sModeInfo.uPulseWidthV++;

    // Calculate the Refresh rate value
    uDivisor = (sModeInfo.uActiveH + sModeInfo.uTotalBlankH) * (sModeInfo.uActiveV + sModeInfo.uTotalBlankV);

    if (0 != uDivisor)
    {
      sModeInfo.uRefreshRate = (uint32)((float)(sModeInfo.uPixelFreq * 1000) / uDivisor * 1000);
    }
    else 
    {
      // Need to cross check to populate default value
      sModeInfo.uRefreshRate = (uint32)(60 * 1000);
    }

    sModeInfo.uBackPorchH      = (sModeInfo.uTotalBlankH < (sModeInfo.uPulseWidthH + sModeInfo.uFrontPorchH)) ? 0 : (sModeInfo.uTotalBlankH - sModeInfo.uPulseWidthH - sModeInfo.uFrontPorchH);
    sModeInfo.uBackPorchV      = (sModeInfo.uTotalBlankV < (sModeInfo.uPulseWidthV + sModeInfo.uFrontPorchV)) ? 0 : (sModeInfo.uTotalBlankV - sModeInfo.uPulseWidthV - sModeInfo.uFrontPorchV);
    sModeInfo.eEDIDSpecType    = EDID_SPEC_ALL;
    sModeInfo.eStandard        = EDID_Standard_VESA;

    // For embedded display add all timings as custom timing.
    if (FALSE == pEdidSharedData->bEmbeddedDisplay)
    {
      bMatchFound = EDID_CheckDuplicateVideoMode(&sModeInfo, pEdidSharedData, pDispModeList);
    }

    if (FALSE == bMatchFound)   // Custom timing
    {
      EDID_Parser_InsertDispFormat(pEdidSharedData, pDispModeList, &sModeInfo, EDID_VIDEO_YUV420_NOT_SUPPORTED);
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DisplayId_Parser_Detail_Timing
//
//  @brief
//      Parses the DisplayId structure and find out all the video mode supported 
//      using detailed timing descriptors.
//
//  @params
//      [IN] pEdidSharedData
//          DisplayID parser context
//      [IN] pDataBuf
//          Buffer that contains DisplayId data.
//      [IN] uTimingBlockIndex
//          Indicates which detail timing block need to parsed, as DisplayId can have multiple 
//          Detailed Timing blocks (Header + Payload).
//
//  @return
//      MDP_STATUS_SUCCESS if matching mode is found.
//-------------------------------------------------------------------------------------------------
//
static MDP_Status DisplayId_Parser_Detail_Timing(EDID_ParserContextType* pEdidSharedData, uint8* pDataBuf, DisplayId_Version eDisplayID_Version, uint32 uTimingBlockIndex)
{
  MDP_Status        eStatus               = MDP_STATUS_FAILED;
  uint32            uTimingBlockSize      = 0;
  uint32            uNumberOfTimingBlocks = 0;
  uint32            uWorkingOffset        = 0;

  if (pDataBuf)
  {
    if (pEdidSharedData->sDisplayIdDataBlock.sDetailTimingBlockDesc.uDetailTimingIBlockOffset[uTimingBlockIndex])
    {
      uWorkingOffset   = pEdidSharedData->sDisplayIdDataBlock.sDetailTimingBlockDesc.uDetailTimingIBlockOffset[uTimingBlockIndex];
      uTimingBlockSize = pEdidSharedData->sDisplayIdDataBlock.sDetailTimingBlockDesc.uDataBlockLength[uTimingBlockIndex];
    }

    uNumberOfTimingBlocks = uTimingBlockSize / DISPLAYID_TIMING_BLOCK_SIZE;
    uNumberOfTimingBlocks = (uNumberOfTimingBlocks > DISPLAYID_MAX_DETAIL_TIMING_BLOCK) ? DISPLAYID_MAX_DETAIL_TIMING_BLOCK : uNumberOfTimingBlocks;
    uWorkingOffset       += DISPLAYID_DATA_BLOCK_HEADER_SIZE;

    for (uint32 uIndex = 1; uIndex <= uNumberOfTimingBlocks; uIndex++)
    {
      uWorkingOffset += ((uIndex-1) * DISPLAYID_TIMING_BLOCK_SIZE);

      eStatus = DisplayId_Parser_Detail_Desc(pEdidSharedData, &pDataBuf[uWorkingOffset], eDisplayID_Version, uTimingBlockSize);
    }
  }
  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DisplayId_Parser_DID_2_0
//
//  @brief
//      Parses the DisplayId 2.0 block in EDID Extension block.
//
//  @params
//      [IN]  pEdidSharedData
//           EDID parser context
//      [IN]  pDataBuf
//      [OUT] pDisplayIdInfo
//           Buffer that contains DisplayId data.
//           DisplayId information.
//
//  @return
//      MDP_STATUS_SUCCESS if parsing is successful.
//-------------------------------------------------------------------------------------------------
//
static MDP_Status DisplayId_Parser_DID_2_0(EDID_ParserContextType* pEdidSharedData, DisplayId_ParserInfoType* pDisplayIdInfo)
{
  MDP_Status eStatus          = MDP_STATUS_SUCCESS;
  MDP_Status eLocalStatus     = MDP_STATUS_SUCCESS;
  uint8*     pDataBuf         = pEdidSharedData->auEDIDCache;
  uint32     uNumTimingBlocks = pEdidSharedData->sDisplayIdDataBlock.sDetailTimingBlockDesc.uNumTimingBlocks;

  if (0 < uNumTimingBlocks)
  {
    uint32 uBlockIndex = 0;

    while (uNumTimingBlocks > uBlockIndex)
    {
      if (0 != pEdidSharedData->sDisplayIdDataBlock.sDetailTimingBlockDesc.uDetailTimingIBlockOffset[uBlockIndex])
      {
        if (MDP_STATUS_SUCCESS != (eLocalStatus = DisplayId_Parser_Detail_Timing(pEdidSharedData, pDataBuf, pDisplayIdInfo->eDIDVersion, uBlockIndex)))
        {
          DISP_OSAL_LOGX("DisplayId_Parser_DID_2_0: DisplayId_Parser_Detail_Timing failed with status = 0x%x,", eLocalStatus);
        }
      }
      uBlockIndex++;
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DisplayId_Parser_DID_1_3
//
//  @brief
//      Parses the DisplayId 1.3 block in EDID Extension block.
//
//  @params
//      [IN]  pEdidSharedData
//           EDID parser context
//      [IN]  pDataBuf
//           Buffer that contains DisplayId data.
//      [OUT] pDisplayIdInfo
//           DisplayId information.
//
//  @return
//      MDP_STATUS_SUCCESS if parsing is successful.
//-------------------------------------------------------------------------------------------------
//
static MDP_Status DisplayId_Parser_DID_1_3(EDID_ParserContextType* pEdidSharedData, DisplayId_ParserInfoType* pDisplayIdInfo)
{
  MDP_Status eStatus          = MDP_STATUS_SUCCESS;
  MDP_Status eLocalStatus     = MDP_STATUS_SUCCESS;
  uint8*     pDataBuf         = pEdidSharedData->auEDIDCache;
  uint32     uNumTimingBlocks = pEdidSharedData->sDisplayIdDataBlock.sDetailTimingBlockDesc.uNumTimingBlocks;

  if (0 < uNumTimingBlocks)
  {
    uint32 uBlockIndex = 0;

    while (uNumTimingBlocks > uBlockIndex)
    {
      if (0 != pEdidSharedData->sDisplayIdDataBlock.sDetailTimingBlockDesc.uDetailTimingIBlockOffset[uBlockIndex])
      {
        if (MDP_STATUS_SUCCESS != (eLocalStatus = DisplayId_Parser_Detail_Timing(pEdidSharedData, pDataBuf, pDisplayIdInfo->eDIDVersion, uBlockIndex)))
        {
          DISP_OSAL_LOGX("DisplayId_Parser_DID_1_3: DisplayId_Parser_Detail_Timing failed with status = 0x%x,", eLocalStatus);
        }
      }
      uBlockIndex++;
    }
  }

  return eStatus;
}

// ------------------------------------------------------------------------------------------------ -
//  DisplayId_ParseDID
//
//  @brief
//      Parses the DisplayId structure present as part of EDID Extension.
//
//  @params
//      [IN] pDisplayIdInfo
//          Pointer to the display Id information.
//
//  @return
//      MDP_STATUS_SUCCESS if data is successfully extracted.
//-------------------------------------------------------------------------------------------------
//
MDP_Status DisplayId_ParseDID(DP_HandleType hHandle, DisplayId_ParserInfoType* pDisplayIdInfo)
{
  MDP_Status eStatus          = MDP_STATUS_SUCCESS;
  MDP_Status eLocalStatus     = MDP_STATUS_SUCCESS;
  uint32     uNumOfCEABlocks  = 0;

  if ((NULL == hHandle) ||
      (NULL == pDisplayIdInfo))
  {
    eStatus = MDP_STATUS_BAD_PARAM;
    DISP_OSAL_LOGX("DisplayId_ParseDID: failed with status = 0x%x", eStatus);
  }
  else
  {
    EDID_ParserContextType* pEdidSharedData = (EDID_ParserContextType*) hHandle;
    uNumOfCEABlocks                         = EDID_GetNumOfCEAExtBlocks(pEdidSharedData);

    DISP_OSAL_MemZero((void*)pDisplayIdInfo, sizeof(DisplayId_ParserInfoType));

    if (MDP_STATUS_SUCCESS != (eStatus = DisplayId_DataBlockOffsetSetup(pEdidSharedData, pEdidSharedData->auEDIDCache, uNumOfCEABlocks, pDisplayIdInfo)))
    {
      DISP_OSAL_LOG_INFO("DisplayId_ParseDID: DisplayId_DataBlockOffsetSetup failed with status = 0x%x \n", eStatus);
    }
    else
    {
      if ((DISPLAYID_VERSION_1_2 == pDisplayIdInfo->eDIDVersion)  ||
          (DISPLAYID_VERSION_1_3 == pDisplayIdInfo->eDIDVersion))
      {
        if (MDP_STATUS_SUCCESS != (eLocalStatus = DisplayId_Parser_DID_1_3(pEdidSharedData, pDisplayIdInfo)))
        {
          DISP_OSAL_LOGX("DisplayId_ParseDID: DisplayId_Parser_DID_1_3 failed with status = 0x%x ", eLocalStatus);
        }
      }
      else 
      {
        if (MDP_STATUS_SUCCESS != (eStatus = DisplayId_Parser_DID_2_0(pEdidSharedData, pDisplayIdInfo)))
        {
          DISP_OSAL_LOGX("DisplayId_ParseDID: DisplayId_Parser_DID_2_0 failed with status = 0x%x ", eLocalStatus);
        }
      }
    }
  }

  return eStatus; 
}

#ifdef __cplusplus
}
#endif
