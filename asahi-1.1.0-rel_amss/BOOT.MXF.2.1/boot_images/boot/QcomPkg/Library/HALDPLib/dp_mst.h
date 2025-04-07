#ifndef _DP_MST_H_
#define _DP_MST_H_
/*! \file */

/*=============================================================================
 
  File: dp_mst.h
 
  DP MST header file
  
 
 Copyright (c) 2018-2020 Qualcomm Technologies, Inc.
 All Rights Reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.
 =============================================================================*/

#include "hal_dp.h"
#include "dp_types.h"


/* --------------------------------------------------------------------------------------------------------------------
** Macros and Struct
---------------------------------------------------------------------------------------------------------------------*/
#define DP_MST_MAX_SINKS 2


/* --------------------------------------------------------------------------------------------------------------------
Enumerated types
---------------------------------------------------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------------------------------------------------
 Structs
---------------------------------------------------------------------------------------------------------------------*/
//-------------------------------------------------------------------------------------------------
//  DPMST_VCAllocConfigType
//
//  @brief
//      MST Virtual channel configuration info
//
//-------------------------------------------------------------------------------------------------
//
typedef struct _DPMST_VCAllocConfigType
{
  bool32 bAllocate;            /**< TRUE: allocate slots. FALSE: clear slots.                       */
  bool32 bClearAll;            /**< To be used when bAllocate == FALSE
                                    TRUE: Clear payload/slot configuration for all active streams
                                    FALSE: Clear payload/slot configuration on per stream basis.    */
  bool32 bSlotCfgUpdated;      /**< TRUE: Update TX slot config and Trigger ACT. 
                                    FALSE: No change in slot configuration                          */
  uint32 uRequiredPBN;         /**< PBN required for current mode.                                  */
  uint32 uRequiredTimeSlots;   /**< Timeslots required for current mode.                            */
} DPMST_VCAllocConfigType;


/* --------------------------------------------------------------------------------------------------------------------
  Functions
---------------------------------------------------------------------------------------------------------------------*/
//-------------------------------------------------------------------------------------------------
//  DPMST_Open
//
//  @brief
//      API needs to be called before any other MST API for this context. 
//      Initializes MST context and returns number of sinks that can be supported for
//      this DP device.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [OUT] puNumSinks
//          Number of sinks that can be configured on this MST device.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DPMST_Open(DP_DisplayCtxType *pDisplayCtx, 
                     uint32            *puNumSinks);
 
//-------------------------------------------------------------------------------------------------
//  DPMST_CalculateMaxBandwidth
//
//  @brief
//      Calculate the bandwidth limit for the current stream based on:
//        1. Available remaining Slots
//        2. Available PBN queried from DPMST_REQ_ID_ENUM_PATH_RESOURCES 
//
//  @params
//      [IN] uLinkRateInKhz
//          The link rate in Khz obtained from DP context.
//      [IN] uNumLanes
//          The number of lanes obtained from DP context.
//      [IN] uRemainingSlots
//          The number of remaining VC slots obtained from DP context.
//      [IN] uAvailablePathPBN
//          The path PBN obtained from ENUM_PATH_RESOURCES
//
//  @return
//      uMaxBandwidth.
//-------------------------------------------------------------------------------------------------
//
uint64 DPMST_CalculateMaxBandwidth(uint32 uLinkRateInKhz,
                                   uint32 uNumLanes,
                                   uint32 uRemainingSlots, 
                                   uint32 uAvailablePathPBN);
 
//-------------------------------------------------------------------------------------------------
//  DPMST_ReserveVCSlots
//
//  @brief
//      API looks for the most bandwidth-intensive mode the stream owns and reserves slots for it.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context. 
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DPMST_ReserveVCSlots(DP_DisplayCtxType *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DPMST_SetMode
//
//  @brief
//      API sets mode (pStreamCtx->uModeIndex) MST device (pStreamCtx->eMSTStreamId) 
//
//  @params
//      [IN] pDisplayCtx
//          DP Device Context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DPMST_SetMode(DP_DisplayCtxType *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DPMST_ConfigureRxVCSlots
//
//  @brief
//      API configures VC payload allocation on Rx side, and returns the slot configuration
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN] pVCInfo
//          VC allocation info provided by caller.
//      [OUT] pVCAllocInfo
//          HAL slot configuration to be written on TX side.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DPMST_ConfigureRxVCSlots(DP_DisplayCtxType          *pDisplayCtx, 
                                   DPMST_VCAllocConfigType    *pVCInfo, 
                                   HAL_DP_MSTVCAllocationType *pVCAllocInfo);

//-------------------------------------------------------------------------------------------------
//  DPMST_ConfigureRxPayload
//
//  @brief
//      API allocates required PBN for a particular mode.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN] pVCInfo
//          VC (PBN) allocation info provided by caller.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DPMST_ConfigureRxPayload(DP_DisplayCtxType          *pDisplayCtx, 
                                   DPMST_VCAllocConfigType    *pVCInfo);

//-------------------------------------------------------------------------------------------------
//  DPMST_Close
//
//  @brief
//      API clears all topology information for this DP device.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DPMST_Close(DP_DisplayCtxType *pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DPMST_ProcessIrqHPD
//
//  @brief
//      API checks if topology change has happened and returns the number of old and new sinks.
//
//  @params
//      [IN] pDisplayCtx
//          DP display context.
//      [OUT] pOldSinkCount
//          Old sink count.
//      [OUT] pNewSinkCount
//          New sink count.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DPMST_ProcessIrqHPD(DP_DisplayCtxType *pDisplayCtx, 
                              uint32            *pOldSinkCount, 
                              uint32            *pNewSinkCount);

//-------------------------------------------------------------------------------------------------
//  DPMST_EDIDRead
//
//  @brief
//      1. Read 1 block of the EDID data
//      2. EDID is read through REMOTE_I2C_READ request
//
//  @params
//      [IN] pDisplayCtx
//          DP display context.
//      [IN] uStartAddress
//          Start address of EDID block 
//      [IN] uSegmentNum
//          Segment number of EDID block 
//      [OUT] puReadDataBuffer
//          The output data buffer, the size should be 128 bytes
//      [IN] uReadDataBufferSize
//          The size of the output buffer
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DPMST_EDIDRead(DP_DisplayCtxType *pDisplayCtx, uint8 uStartAddress, uint8 uSegmentNum, uint8 *puReadDataBuffer, uint32 uReadDataBufferSize);

//-------------------------------------------------------------------------------------------------
//  DPMST_UpdateTargetGUID
//
//  @brief
//      API to update non-zero GUID to target. If MST link address report non-zero GUID, we will use 
//      it, if link address did not report valid GUID, we will use display container GUID from miniport
//
//  @params
//      [IN] pDisplayCtx
//          DP display context.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DPMST_UpdateTargetGUID(DP_DisplayCtxType* pDisplayCtx);

//-------------------------------------------------------------------------------------------------
//  DPMST_RemoteDPCDRead
//
//  @brief
//      Read Remote DPCD registers
//
//  @params
//      [IN] pDisplayCtx
//           DP display context.
//      [IN] uLinkCountfromSink
//           Number of links between Branch device to read and the Sink
//      [IN] uAddress
//           Address of DPCD
//      [OUT] puReadDataBuffer
//          The output data buffer
//      [IN] uReadSize
//           Number of bytes to read
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DPMST_RemoteDPCDRead(DP_DisplayCtxType *pDisplayCtx,
                               uint8              uLinkCountfromSink,
                               uint32             uAddress,
                               uint8             *puReadDataBuffer,
                               uint32             uReadSize);

//-------------------------------------------------------------------------------------------------
//  DPMST_RemoteDPCDWrite
//
//  @brief
//       Write to DPCD registers of remote DP Device
//
//  @params
//      [IN] pDisplayCtx
//           DP display context.
//      [IN] uLinkCountfromSink
//           Number of links between Branch device to write and the Sink
//      [IN] uAddress
//           Address of DPCD
//      [OUT] puWriteDataBuffer
//          The Write data buffer
//      [IN] uWriteSize
//           Number of bytes to write
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DPMST_RemoteDPCDWrite(DP_DisplayCtxType *pDisplayCtx,
                                uint8              uLinkCountfromSink,
                                uint32             uAddress,
                                uint8             *puWriteDataBuffer,
                                uint32             uWriteSize);


#endif //_DP_MST_H_
