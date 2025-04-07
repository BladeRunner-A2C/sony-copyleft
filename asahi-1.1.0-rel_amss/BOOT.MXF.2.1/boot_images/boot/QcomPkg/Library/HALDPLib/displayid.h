#ifndef __DISPLAYID_H__
#define __DISPLAYID_H__
/*=============================================================================

  File: displayid.h

  DisplayId headers and utilitiy functions

  $Header: 

  Copyright (c) 2021 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

#include "MDPLib_i.h"
#include "dp_types.h"

/* -----------------------------------------------------------------------
**  Defines
** ----------------------------------------------------------------------- */
#define DISPLAYID_EDID_EXTENSION_TAG_CODE                                    (0x70)  // DisplayId edid extension block tag code
 
#define DISPLAYID_DATA_BLOCK_RELATIVE_OFFFSET                                0x05
#define DISPLAYID_DATA_BLOCK_HEADER_SIZE                                     0x03
#define DISPLAYID_MAX_ASPECT_RATIO                                           0x06    // Max aspect ratio 6:1
#define DISPLAYID_DISP_MODE_LIST_MAX_NUM                                     32      // Max number of modes
#define DISPLAYID_TIMING_BLOCK_SIZE                                          20

#define DISPLAYID_V1_3_PRODUCT_IDENTIFICATION_BLOCK_TAG_CODE                 0x00
#define DISPLAYID_V2_0_PRODUCT_IDENTIFICATION_BLOCK_TAG_CODE                 0x20
#define DISPLAYID_TYPEI_TIMING_BLOCK_TAG_CODE                                0x03
#define DISPLAYID_TYPEVII_TIMING_BLOCK_TAG_CODE                              0x22
#define DISPLAYID_V1_3_DISPLAY_PARAMETERS_DATA_BLOCK_TAG_CODE                0x01
#define DISPLAYID_V2_0_DISPLAY_PARAMETERS_DATA_BLOCK_TAG_CODE                0x21
#define DISPLAYID_COLOR_CHARACTERISTIC_DATA_BLOCK_TAG_CODE                   0x02
#define DISPLAYID_V1_3_DISPLAY_INTERFACE_DATA_BLOCK_TAG_CODE                 0x0F
#define DISPLAYID_V2_0_DISPLAY_INTERFACE_DATA_BLOCK_TAG_CODE                 0x26
#define DISPLAYID_TOPOLOGY_DATA_BLOCK_TAG_CODE                               0x12

#define DISPLAYID_DETAILED_TIMING_BLOCK_REVISION_OFFSET                      0x01
#define DISPLAYID_DETAILED_TIMING_BLOCK_REVISION_MASK                        0x07
#define DISPLAYID_DETAILED_TIMING_PAYLOAD_SIZE                               0x14

#define DISPLAYID_DETAILED_TIMING_PAYLOAD_SIZE_OFFSET                        0x02
#define DISPLAYID_MAX_DETAIL_TIMING_BLOCK                                    0x0C    // Max no of detailed timing block that can be supported, as DisplayId spec.

// Offset to the Detailed Timing Descriptors
#define DISPLAYID_TIMING_PIXEL_CLOCK_LOWER_BYTE_OFFSET                       (0x00)  // Relative Offset to the DisplayId detailed timing descriptors - Pixel Clock lower byte
#define DISPLAYID_TIMING_PIXEL_CLOCK_MIDDLE_BYTE_OFFSET                      (0x01)  // Relative Offset to the DisplayId detailed timing descriptors - Pixel Clock middle byte
#define DISPLAYID_TIMING_PIXEL_CLOCK_UPPER_BYTE_OFFSET                       (0x02)  // Relative Offset to the DisplayId detailed timing descriptors - Pixel Clock upper byte
#define DISPLAYID_TIMING_OPTIONS                                             (0x03)  // Relative Offset to the DisplayId detailed timing descriptors - Timing Options
#define DISPLAYID_TIMING_ASPECT_RATIO_MASK                                   (0x0F)  // Lower 4 bit mask
#define DISPLAYID_TIMING_FRAME_SCAN                                          (0x10)  // Frame scaning mask
#define DISPLAYID_TIMING_STEREO_SUPPORT                                      (0x60)  // Stereo bit mask
#define DISPLAYID_TIMING_PREFERRED_DETAILED_TIMING                           (0x80)  // Preferred Detailed timing
#define DISPLAYID_TIMING_H_ACTIVE_LOWER                                      (0x04)  // Relative Offset to the DisplayId detailed timing descriptors - H active lower byte
#define DISPLAYID_TIMING_H_ACTIVE_UPPER                                      (0x05)  // Relative Offset to the DisplayId detailed timing descriptors - H active upper byte
#define DISPLAYID_TIMING_H_BLANK_LOWER                                       (0x06)  // Relative Offset to the DisplayId detailed timing descriptors - H blank lower byte
#define DISPLAYID_TIMING_H_BLANK_UPPER                                       (0x07)  // Relative Offset to the DisplayId detailed timing descriptors - H blank upper byte
#define DISPLAYID_TIMING_H_OFFSET_LOWER                                      (0x08)  // Relative Offset to the DisplayId detailed timing descriptors - H offset lower byte
#define DISPLAYID_TIMING_H_OFFSET_UPPER                                      (0x09)  // Relative Offset to the DisplayId detailed timing descriptors - H offset upper byte
#define DISPLAYID_TIMING_H_OFFFSET_UPPER_MASK                                (0x7F)  // Horizontal Offset Mask
#define DISPLAYID_TIMING_H_SYNC_POLARITY_MASK                                (0x80)  // Horizontal sync polarity mask
#define DISPLAYID_TIMING_H_WIDTH_LOWER                                       (0x0A)  // Relative Offset to the DisplayId detailed timing descriptors - H width lower byte
#define DISPLAYID_TIMING_H_WIDTH_UPPER                                       (0x0B)  // Relative Offset to the DisplayId detailed timing descriptors - H width upper byte
#define DISPLAYID_TIMING_V_ACTIVE_LOWER                                      (0x0C)  // Relative Offset to the DisplayId detailed timing descriptors - V active lower byte
#define DISPLAYID_TIMING_V_ACTIVE_UPPER                                      (0x0D)  // Relative Offset to the DisplayId detailed timing descriptors - V active upper byte
#define DISPLAYID_TIMING_V_BLANK_LOWER                                       (0x0E)  // Relative Offset to the DisplayId detailed timing descriptors - V blank lower byte
#define DISPLAYID_TIMING_V_BLANK_UPPER                                       (0x0F)  // Relative Offset to the DisplayId detailed timing descriptors - V blank upper byte
#define DISPLAYID_TIMING_V_OFFSET_LOWER                                      (0x10)  // Relative Offset to the DisplayId detailed timing descriptors - v offset lower byte
#define DISPLAYID_TIMING_V_OFFSET_UPPER                                      (0x11)  // Relative Offset to the DisplayId detailed timing descriptors - v offset upper byte
#define DISPLAYID_TIMING_V_OFFFSET_UPPER_MASK                                (0x7F)  // Vertical Offset Mask
#define DISPLAYID_TIMING_V_SYNC_POLARITY_MASK                                (0x80)  // Vertical sync polarity mask
#define DISPLAYID_TIMING_V_WIDTH_LOWER                                       (0x12)  // Relative Offset to the DisplayId detailed timing descriptors - v width lower byte
#define DISPLAYID_TIMING_V_WIDTH_UPPER                                       (0x13)  // Relative Offset to the DisplayId detailed timing descriptors - v width upper byte

 /* Macro to left shift 1 by _a_ bits/position */
#define DISPLAYID_BIT(_a_)                                                   (1 << (_a_))

/* -----------------------------------------------------------------------
**  Enums
** ----------------------------------------------------------------------- */

//-------------------------------------------------------------------------------------------------
//  DisplayId_Version
//
//  @brief
//      Defines the version of the displayid 
//-------------------------------------------------------------------------------------------------
//
typedef enum
{
  DISPLAYID_VERSION_INVALID = 0x0,
  DISPLAYID_VERSION_1_2     = 0x12,
  DISPLAYID_VERSION_1_3     = 0x13,
  DISPLAYID_VERSION_2_0     = 0x20,
  DISPLAYID_VERSION_RESERVED,
  DISPLAYID_VERSION_MAX,
  DISPLAYID_VERSION_FORCE_32BIT
} DisplayId_Version;

//-------------------------------------------------------------------------------------------------
//  DisplayId_Video_3DStereo
//
//  @brief
//      Defines the 3D Stereo support of the timing mode 
//-------------------------------------------------------------------------------------------------
//
typedef enum
{
  DISPLAYID_VIDEO_3D_SETEREO_MONO,
  DISPLAYID_VIDEO_3D_SETEREO_STEREO,
  DISPLAYID_VIDEO_3D_SETEREO_USER,
  DISPLAYID_VIDEO_3D_SETEREO_RESERVED,
  DISPLAYID_VIDEO_3D_SETEREO_MAX,
  DISPLAYID_VIDEO_3D_SETEREO_FORCE_32BIT,
} DisplayId_Video_3DStereo;

/* -----------------------------------------------------------------------
**  Structures
** ----------------------------------------------------------------------- */

//-------------------------------------------------------------------------------------------------
//  DisplayId_ProductIdentificationDesc
//
//  @brief
//      Contains Product identification data block offset and size.
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
  uint32 uProductIdentificationOffset;      /* Offset of Display parameters data block         */
  uint32 uDataBlockLength;                  /* Length of this data block                       */
} DisplayId_ProductIdentificationDesc;

//-------------------------------------------------------------------------------------------------
//  DisplayId_DisplayParametersDataBlock
//
//  @brief
//      Contains Display parameters data block offset and size.
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
  uint32 uDisplayParametersDataBlockOffset; /* Offset of Display parameters data block         */
  uint32 uDataBlockLength;                  /* Length of this data block                       */
} DisplayId_DisplayParametersDataBlock;

//-------------------------------------------------------------------------------------------------
//  DisplayId_ColorCharacteristicBlock
//
//  @brief
//    Contains color characteristic data block offset and size.
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
  uint32 uColorCharacteristicBlockOffset;   /* Offset of Color characteristic data block       */
  uint32 uDataBlockLength;                  /* Length of this data block                       */
} DisplayId_ColorCharacteristicBlock;

//-------------------------------------------------------------------------------------------------
//  DisplayId_DetailTimingBlockDesc
//
//  @brief
//    Contains Deatiled timing data block offset and size.
//
//    Represents DetailTimingTypeIBlockDesc for DisplayID 1.3
//    Represents DetailTimingTypeVIIBlockDesc for DisplayID 2.0
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
  uint32 uDetailTimingIBlockOffset[DISPLAYID_MAX_DETAIL_TIMING_BLOCK];
                                            /* Offset of detail timing data block              */
  uint32 uDataBlockLength[DISPLAYID_MAX_DETAIL_TIMING_BLOCK];
                                            /* Length of this data block                       */
  uint32 uNumTimingBlocks;                  /* Number of DetailTimingBlockTypeIDesc Data blocks 
                                               are there (Header + Payload)                    */
} DisplayId_DetailTimingBlockDesc;

//-------------------------------------------------------------------------------------------------
//  DisplayId_DisplayInterfaceDataBlock
//
//  @brief
//    Contains display interface data block offset and size.
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
  uint32 uDisplayInterfaceDataBlockOffset;  /* Offset of type I detail timing data block       */
  uint32 uDataBlockLength;                  /* Length of this data block                       */
} DisplayId_DisplayInterfaceDataBlock;

//-------------------------------------------------------------------------------------------------
//  DisplayId_TopologyDataBlock
//
//  @brief
//    Contains display topology data block offset and size.
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
  uint32 uDisplayTopologyDataBlockOffset;   /* Offset of Display Topology data block           */
  uint32 uDataBlockLength;                  /* Length of this data block                       */
} DisplayId_TopologyDataBlock;

//-------------------------------------------------------------------------------------------------
//  DisplayId_DataBlockType
//
//  @brief
//      Contains all the data block offsets from the DisplayId
//-------------------------------------------------------------------------------------------------
//
typedef struct
{
  DisplayId_ProductIdentificationDesc  sProductIdentificationDesc;
  DisplayId_DisplayParametersDataBlock sDisplayParametersDataBlock;
  DisplayId_ColorCharacteristicBlock   sDisplayColorCharacteristicBlock;
  DisplayId_DetailTimingBlockDesc      sDetailTimingBlockDesc;
  DisplayId_DisplayInterfaceDataBlock  sDisplayInterfaceDataBlock;
  DisplayId_TopologyDataBlock          sDisplayTopologyBlockDesc;
} DisplayId_DataBlockType;

//-------------------------------------------------------------------------------------------------
//  DisplayId_ParserInfoType
//
//  @brief
//      DisplayId parser Information. 
//
//------------------------------------------------------------------------------------------------
//
typedef struct
{
//  EDID_DispModeAttrType      sModeInfo;
  DisplayId_Version          eDIDVersion;
} DisplayId_ParserInfoType;

/* -----------------------------------------------------------------------
**  Functions
** ----------------------------------------------------------------------- */

// ------------------------------------------------------------------------------------------------ -
//  DisplayId_ParseDID
//
//  @brief
//      Parses the DisplayId structure present as part of EDID Extension.
//
//  @params
//      [IN] hHandle
//          Pointer to EDID parser context (EDID_ParserContextType), argument passed as void pointer.
//      [IN] pDisplayIdInfo
//          Pointer to the display Id information.
//
//  @return
//      QDI_STATUS_SUCCESS  data is successfully extracted.
//-------------------------------------------------------------------------------------------------
//
MDP_Status DisplayId_ParseDID(DP_HandleType hHandle, DisplayId_ParserInfoType* pDisplayIdInfo);

#endif // __DISPLAYID_H__
