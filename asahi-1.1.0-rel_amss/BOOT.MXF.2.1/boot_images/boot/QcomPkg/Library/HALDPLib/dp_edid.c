/*=====================================================================================================================

File: dp_edid.c

Source file for DP EDID read and parse related functionality

Copyright (c) 2016-2022 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
=======================================================================================================================*/


/*---------------------------------------------------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------------------------------------------------*/
#include "dp_i.h"
#include "edid.h"
#include "dp_mst.h"

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------
 * Local Prototypes
 *----------------------------------------------------------------------------*/
static DP_Status DP_I2CWrite(DP_DisplayCtxType* pDisplayCtx, uint32 uAddress, uint8* pWriteData, uint32 uWriteDataSize, DP_AUX_TransactionFlags eFlags);

/*------------------------------------------------------------------------------
 * Public Functions
 *----------------------------------------------------------------------------*/

/**********************************************************************************************************************

FUNCTION: DP_EDIDReadBlock()
   
   This function will read 128 bytes EDID block

Parameters:
  pDisplayCtx  -[in]    : DP Display Context
  psReadPacket -[in/out]: Pointer to read packet

Return:
   DP_Status 

**********************************************************************************************************************/
static DP_Status DP_EDIDReadBlock(DP_DisplayCtxType *pDisplayCtx, 
                                  DP_ReadPacketType *psReadPacket)
{
  DP_Status              eStatus        = DP_STATUS_SUCCESS; 
  
  if ((NULL == pDisplayCtx) ||
      (NULL == psReadPacket))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    if (psReadPacket->bTunneledMode)
    {
      /* Read the EDID block 16 bytes at a time in tunneled case */
      eStatus = DP_Host_AuxRead(pDisplayCtx,
                                psReadPacket->puReadDataBuffer,
                                &(psReadPacket->uReadSize), 
                                psReadPacket->uAddress,
                                DP_TRANSACTION_MODE_I2C);

      /* Update the uBytesRead to handle the common error checking below */
      psReadPacket->uBytesRead = psReadPacket->uReadSize;
    }
    else 
    {
      /* Read as a single block in non-tunneled case to speed up performance 
         uBytesRead is already updated within the function                   */
      eStatus = DP_Host_AuxReadRaw(pDisplayCtx, psReadPacket);
    }
    
    if (DP_STATUS_SUCCESS != eStatus)
    {
      DP_LOG_MESSAGE_ERROR("DP_EDIDReadBlock() : DP Aux Read Failed, eStatus=%d\n", eStatus);
    }
    else if (DP_EDID_BLOCK_SIZE != psReadPacket->uBytesRead)
    {
      DP_LOG_MESSAGE_ERROR( "DP_EDIDReadBlock() : Read Failed. Bytes read %d (expected %d)\n", psReadPacket->uBytesRead, DP_EDID_BLOCK_SIZE);
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
    }
  }
  return eStatus;
}

/**********************************************************************************************************************

FUNCTION: DP_ParseSinkEDID()
   
   This function will parse the DPCD Capability from the Raw Data. 

Parameters:
  pDisplayCtx  -[in]    : DP Display Context

Return:
   DP_Status 

**********************************************************************************************************************/
DP_Status  DP_ParseSinkEDID(DP_DisplayCtxType    *pDisplayCtx)
{
  return DP_ParseEDID(pDisplayCtx);
}


/**********************************************************************************************************************

FUNCTION: DP_ReadSinkEDIDRaw()

  This function will read EDID Raw Data from Sink over I2c.

Parameters:
  pDisplayCtx  -[in]    : DP Display Context

Return:
  DP_Status

**********************************************************************************************************************/
DP_Status  DP_ReadSinkEDIDRaw(DP_DisplayCtxType    *pDisplayCtx)
{
  DP_Status               eStatus       = DP_STATUS_SUCCESS;
  DP_DeviceCtxType       *pDeviceCtx    = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType       *pStreamCtx    = DPHOST_GET_STREAM_CTX(pDisplayCtx);

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx))
  {
    DP_LOG_MESSAGE_ERROR("DP_ReadSinkEDIDRaw() : DP handle is NULL pointer\n");
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  { 
    uint8                  *puEDID         = pStreamCtx->auEDIDCache;
    uint32                  uEDIDReadRetry = DP_EDID_READ_RETRY_NUMBER;

    /* Set default return EDID length */
    pStreamCtx->uEDIDDataLength = 0;

    while (uEDIDReadRetry--)
    {
      if (DP_STATUS_SUCCESS != (eStatus = DP_EDIDRead(pDisplayCtx, 0, (uint8*)puEDID, DP_EDID_BLOCK_SIZE)))
      {      
        // Read the EDID Block 0 failed
        TraceInfo(QdiTraceDP, "DP%i: DP_ReadSinkEDIDRaw() : EDID Read Failed, eStatus = 0x%x", pDeviceCtx->eDisplayID, eStatus);
        continue;
      }
      else if ((FALSE == EDIDValidateEDIDHeader(puEDID, DP_EDID_MAX_NUM_OF_BLOCKS)) ||
               (FALSE == EDIDValidateCheckSum(puEDID)))
      {
        TraceInfo(QdiTraceDP, "DP%i: DP_ReadSinkEDIDRaw() : Read EDID Header or CheckSum is not valid or corrupted", pDeviceCtx->eDisplayID);
        
        if ((pDeviceCtx->ePendingTestRequest & DP_TEST_EDID_READ) ||
            (pDeviceCtx->uFlags              & DP_HOST_FLAG_STRICT_EDID_CHECK))
        {
          // DP link CTS in progress or strict EDID CRC check is enforced, directly fail to fail-safe mode
          eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
          break;
        }
      }
      else
      {
        // Good EDID, everything is OK.
        eStatus = DP_STATUS_SUCCESS;
        break;
      }

      if (0 == uEDIDReadRetry)
      {
        TraceInfo(QdiTraceDP, "DP%i: DP_ReadSinkEDIDRaw() : EDID corruption detected after %i retries, trying to parse corrupted EDID", pDeviceCtx->eDisplayID, DP_EDID_READ_RETRY_NUMBER);
      }
    }

    if (DP_STATUS_SUCCESS == eStatus)
    {
      uint8   uExtBlockNum = 0;

      /* Block 0 size*/
      pStreamCtx->uEDIDDataLength += DP_EDID_BLOCK_SIZE;
      
      /* Get Extension block number */
      uExtBlockNum = puEDID[DP_EDID_EXT_BLOCK_NUM_OFFSET];

      /* uExtBlockNum should be limited by buffer size*/
      if (uExtBlockNum > DP_EDID_MAX_NUM_OF_BLOCKS)
      {
        uExtBlockNum = DP_EDID_MAX_NUM_OF_BLOCKS;
      }
      
      if (uExtBlockNum >= 1)
      {
        for (uint8 uBlockIdx = 1; uBlockIdx <= uExtBlockNum; uBlockIdx++)
        {
          /* Read next EDID Data Block */
          if (DP_STATUS_SUCCESS != (eStatus = DP_EDIDRead(pDisplayCtx, uBlockIdx, (uint8*)& puEDID[uBlockIdx * DP_EDID_BLOCK_SIZE], DP_EDID_BLOCK_SIZE)))
          {
            TraceInfo(QdiTraceDP, "DP%i: DP_ReadSinkEDIDRaw() : EDID blockIdx = %d Read Failed, eStatus = 0x%x", pDeviceCtx->eDisplayID, uBlockIdx, eStatus);
          }
          else
          {
            pStreamCtx->uEDIDDataLength += DP_EDID_BLOCK_SIZE;

            /* Still have EDID blocks unread*/
            if ((pStreamCtx->uEDIDDataLength + DP_EDID_BLOCK_SIZE > DP_EDID_MAX_BUF_SIZE) &&
                (uBlockIdx <= uExtBlockNum))
            {
              DP_LOG_MESSAGE_WARN("DP_ReadSinkEDIDRaw() : EDID buffer too small, %d bytes unread\n", (uExtBlockNum - uBlockIdx) * DP_EDID_BLOCK_SIZE);
              break;
            }
          }
        }
      }
    }
  } 

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_EDIDRead
//
//  @brief
//      1. EDID read of 1 block, the block index needs to be specified.
//      2. The function is used for both SST and MST.
//      3. The size of the block is fixed at DP_EDID_BLOCK_SIZE.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN] uBlockIdx
//          Index of EDID block to be read.
//      [OUT] puReadDataBuffer
//          The output data buffer.
//      [IN] uReadDataBufferSize
//          The size of the output data buffer
//
//  @return
//      DP_Status 
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_EDIDRead(DP_DisplayCtxType *pDisplayCtx, uint8 uBlockIdx, uint8 *puReadDataBuffer, uint32 uReadDataBufferSize)
{
  DP_Status              eStatus        = DP_STATUS_SUCCESS; 
  DP_DeviceCtxType      *pDeviceCtx     = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  uint8                  uSegmentNum    = 0;
  uint8                  uStartAddress  = 0;

  if (NULL == pDeviceCtx)
  {
    DP_LOG_MESSAGE_ERROR("DP_EDIDRead() : DP handle is NULL pointer.");
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else if (uReadDataBufferSize < DP_EDID_BLOCK_SIZE)
  {
    DP_LOG_MESSAGE_ERROR("DP_EDIDRead() : Output buffer too small.");
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    uSegmentNum   = uBlockIdx >> 1;
    uStartAddress = (uBlockIdx % 2 == 0) ? 0 : DP_EDID_BLOCK_SIZE;

    if (FALSE == pDeviceCtx->bMSTEnabled)
    { 
      // E-DDC spec recommends setting segment number before the offset of the start address
      if (uSegmentNum)
      {
        if (DP_STATUS_SUCCESS != (eStatus = DP_I2CWrite(pDisplayCtx, DP_EDID_SEGMENT_ADDRESS, &uSegmentNum, 1, DP_AUX_TRANSACTION_I2C_SET_MOT_FLAG)))
        {
          DP_LOG_MESSAGE_ERROR("DP_EDIDRead() : Failed to update extension segment number, eStatus=%d\n", eStatus);
        }
      }
      if ((DP_STATUS_SUCCESS == eStatus) &&
          (DP_STATUS_SUCCESS != (eStatus = DP_I2CWrite(pDisplayCtx, DP_EDID_START_ADDRESS, &uStartAddress, 1, DP_AUX_TRANSACTION_I2C_SET_MOT_FLAG))))
      {
        DP_LOG_MESSAGE_ERROR("DP_EDIDRead() : Failed to write EDID block %d, eStatus=%d\n", uBlockIdx, eStatus);
      }

      if (DP_STATUS_SUCCESS == eStatus)
      {
        DP_ReadPacketType       sReadPacket;

        /* Read EDID Data Block 0*/
        DP_OSAL_MemSet(&sReadPacket, 0, sizeof(DP_ReadPacketType));
        sReadPacket.eTransactionType     = DP_TRANSACTION_MODE_I2C;
        sReadPacket.uAddress             = DP_EDID_START_ADDRESS;
        sReadPacket.uReadSize            = DP_EDID_BLOCK_SIZE;
        sReadPacket.bQueueOnly           = FALSE; 
        sReadPacket.puReadDataBuffer     = puReadDataBuffer;
        sReadPacket.bTunneledMode        = DPHOST_CHECK_DP_TUNNELING_MODE(pDeviceCtx);

        eStatus = DP_EDIDReadBlock(pDisplayCtx, &sReadPacket);
      }
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_I2CWrite
//
//  @brief
//      I2C write to initiate and configure EDID reads for SST. 
//
//  @params
//      [IN] pDisplayCtx
//          DP display context.
//      [IN] uAddress
//          THE I2C address to write to.
//      [IN] pWriteData
//          The data buffer for I2C write.
//      [IN] uWriteDataSize
//          The size of the data buffer.
//      [IN] uFlags
//          Write flags for stall/sleep, set MoT in I2C
//
//  @return
//      DP_Status 
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_I2CWrite(DP_DisplayCtxType *pDisplayCtx, uint32 uAddress, uint8 *pWriteData, uint32 uWriteDataSize, DP_AUX_TransactionFlags eFlags)
{
  DP_Status              eStatus      = DP_STATUS_SUCCESS; 
  DP_DeviceCtxType      *pDeviceCtx   = DPHOST_GET_DEVICE_CTX(pDisplayCtx);

  if (NULL == pDeviceCtx)
  {
    DP_LOG_MESSAGE_ERROR("DP_I2CWrite() : DP handle is NULL pointer");
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else if (FALSE == pDeviceCtx->bMSTEnabled)
  { 
    DP_WritePacketType      sWritePacket; 

    /* Write read request to EDID Data, Block 0 */
    DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
    sWritePacket.eTransactionType    = DP_TRANSACTION_MODE_I2C;
    sWritePacket.puWriteData         = pWriteData;
    sWritePacket.uAddress            = uAddress;
    sWritePacket.uWriteDataSize      = uWriteDataSize;
    sWritePacket.bQueueOnly          = FALSE;    
    sWritePacket.eFlags              = eFlags;

    if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket)))
    {
      DP_LOG_MESSAGE_ERROR("DP_I2CWrite() : DP_Host_AuxWriteRaw Failed, eStatus=%d\n", eStatus);
    } 
  }

  return eStatus;
}
 
#ifdef __cplusplus
}
#endif
