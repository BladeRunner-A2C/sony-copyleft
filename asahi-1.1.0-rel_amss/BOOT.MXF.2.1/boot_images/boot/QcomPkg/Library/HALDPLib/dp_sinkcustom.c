/*=============================================================================
 
  File: dp_sinkcustom.c
 
  DP Custiom sink related functions.
  
  Copyright (c) 2022 Qualcomm Technologies, Inc.
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

/*---------------------------------------------------------------------------------------------------------------------
 * Defines
 *-------------------------------------------------------------------------------------------------------------------*/
#define DPCD_LTTPR_CUSTOM_SPECIFIC_ADDRESS           0xF004F
#define DPCD_LTTPR_CUSTOM_SPECIFIC_LEN               4
#define DPCD_LTTPR_CUSTOM_MAX_VSPE_LEVEL_NUM         3

#define DPCD_LINKCONFIG_START_ADDRESS                0x100

//-------------------------------------------------------------------------------------------------
//  DP_IdentifyCustomSink
//
//  @brief
//    Helper function to compare and identify the sink type
//
//  @params
//    [IN] pDisplayCtx
//      Pointer to display context
//    [IN] eSinkClass
//      DP Sink type
//    [IN] uSinkNameLength
//      Sink name length
//
//  @return
//    Particular custom sink type.
//-------------------------------------------------------------------------------------------------
DP_CustomSinkType DP_IdentifyCustomSink(DP_DisplayCtxType *pDisplayCtx,
                                        DP_SinkClassType   eSinkClass,
                                        uint32             uSinkNameLength)
{
  DP_CustomSinkType  eCustomSinkType = DP_CUSTOM_SINKID_NONE;
  DP_DeviceCtxType  *pDeviceCtx;
  DP_StreamCtxType  *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) ||
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    DP_LOG_MESSAGE_ERROR("DP_IdentifyCustomSink: Unexpected null context.");
  }
  else
  {
    switch (eSinkClass)
    {
      case DP_SINKCLASS_REPEATER:
      {
        // If vendor has specific requirement for the repeater, we can add it here
        if ((DP_IsValidLTTPR(pDisplayCtx))&&
            (0 == DP_Strncmp(pDeviceCtx->sLTTPRDeviceInfo.aDeviceString,
                                    (uint8*)DP_RETIMER_KB8001,
                                    uSinkNameLength)))
        {
          eCustomSinkType = DP_CUSTOM_SINKID_1;
        }
        break;
      }
      default:
      {
        eCustomSinkType = DP_CUSTOM_SINKID_NONE;
        break;
      }
    }
  }

  return eCustomSinkType;
}


//-------------------------------------------------------------------------------------------------
//  DP_WriteCustomLTTPRInitSequence
//
//  @brief
//    This function will run the LTTPR custom init sequence.
//
//  @params
//    [IN] pDisplayCtx
//      Pointer to context
//    [IN] eCustomSinkType
//      Custom sink type
//
//  @return
//    DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteCustomLTTPRInitSequence(DP_DisplayCtxType *pDisplayCtx,
                                           DP_CustomSinkType  eCustomSinkType)
{
  DP_Status         eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    switch (eCustomSinkType)
    {
      case DP_CUSTOM_SINKID_1:
      {
        DP_WritePacketType sWritePacket;
        uint8              uData[4] = {0x01, 0x50, 0x63, 0xFF};

        // Write F004F (4 bytes) 01 50 63 FF. Override VS, PE
        DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
        sWritePacket.eTransactionType = DP_TRANSACTION_MODE_AUX;
        sWritePacket.puWriteData      = (uint8*) &uData;
        sWritePacket.uAddress         = DPCD_LTTPR_CUSTOM_SPECIFIC_ADDRESS;
        sWritePacket.uWriteDataSize   = DPCD_LTTPR_CUSTOM_SPECIFIC_LEN;
        sWritePacket.uBytesWritten    = 0;
        sWritePacket.bQueueOnly       = FALSE;

        if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket)))
        {
          DP_LOG_MESSAGE_ERROR( "DP%d: DP_WriteCustomLTTPRInitSequence: Override VS, PE write Failed, eStatus=0x%x.", pDeviceCtx->eControllerID, eStatus);
        }

        if (DP_STATUS_SUCCESS == eStatus)
        {
          // Write F004F (4 bytes) 01 51 63 00. VS = 0 all lanes
          uData[1] = 0x51;
          uData[3] = 0x00;

          DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
          sWritePacket.eTransactionType = DP_TRANSACTION_MODE_AUX;
          sWritePacket.puWriteData      = (uint8*) &uData;
          sWritePacket.uAddress         = DPCD_LTTPR_CUSTOM_SPECIFIC_ADDRESS;
          sWritePacket.uWriteDataSize   = DPCD_LTTPR_CUSTOM_SPECIFIC_LEN;
          sWritePacket.uBytesWritten    = 0;
          sWritePacket.bQueueOnly       = FALSE;

          if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket)))
          {
            DP_LOG_MESSAGE_ERROR( "DP%d: DP_WriteCustomLTTPRInitSequence: VS = 0 all lanes write Failed, eStatus=0x%x.", pDeviceCtx->eControllerID, eStatus);
          }
        }

        if (DP_STATUS_SUCCESS == eStatus)
        {
          // Write F004F (4 bytes) 01 52 63 00. PE = 0 all lanes
          uData[1] = 0x52;

          DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
          sWritePacket.eTransactionType = DP_TRANSACTION_MODE_AUX;
          sWritePacket.puWriteData      = (uint8*) &uData;
          sWritePacket.uAddress         = DPCD_LTTPR_CUSTOM_SPECIFIC_ADDRESS;
          sWritePacket.uWriteDataSize   = DPCD_LTTPR_CUSTOM_SPECIFIC_LEN;
          sWritePacket.uBytesWritten    = 0;
          sWritePacket.bQueueOnly       = FALSE;

          if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket)))
          {
            DP_LOG_MESSAGE_ERROR( "DP%d: DP_WriteCustomLTTPRInitSequence: PE = 0 all lanes write Failed, eStatus=0x%x.", pDeviceCtx->eControllerID, eStatus);
          }
        }

        if (DP_STATUS_SUCCESS == eStatus)
        {
          // Enable incept until serdes is trained
          if (DP_STATUS_SUCCESS != (eStatus = DP_EnableCustomLTTPRIntercept(pDisplayCtx, TRUE, eCustomSinkType)))
          {
            DP_LOG_MESSAGE_ERROR("DP%d: DP_WriteCustomLTTPRInitSequence: Enable incept failed, eStatus=0x%x.", pDeviceCtx->eControllerID, eStatus);
          }
        }

        if (DP_STATUS_SUCCESS == eStatus)
        {
          // Write 00100 (1 byte) to default RBR.
          uint8 uWriteBuffer = 0x6;

          DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
          sWritePacket.eTransactionType = DP_TRANSACTION_MODE_AUX;
          sWritePacket.puWriteData      = (uint8*) &uWriteBuffer;
          sWritePacket.uAddress         = DPCD_LINKCONFIG_START_ADDRESS;
          sWritePacket.uWriteDataSize   = 1;
          sWritePacket.uBytesWritten    = 0;
          sWritePacket.bQueueOnly       = FALSE;
        
          if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket)))
          {
            DP_LOG_MESSAGE_ERROR( "DP%d: DP_WriteCustomLTTPRInitSequence: Force reset to FSM write Failed, eStatus=0x%x.", pDeviceCtx->eControllerID, eStatus);
          }
        }
        break;
      }
      default:
      {
        eStatus = DP_STATUS_SUCCESS;
        break;
      }
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_EnableCustomLTTPRIntercept
//
//  @brief
//    This function will enable the Custom LTTPR intercept.
//
//  @params
//    [IN] pDisplayCtx
//      Pointer to context
//    [IN] bEnable 
//      Flag to enable/disable intercept.
//    [IN] eCustomSinkType
//      Custom sink type
//
//  @return
//    DP_Status.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_EnableCustomLTTPRIntercept(DP_DisplayCtxType *pDisplayCtx,
                                         bool32             bEnable,
                                         DP_CustomSinkType  eCustomSinkType)
{
  DP_Status         eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    switch (eCustomSinkType)
    {
      case DP_CUSTOM_SINKID_1:
      {
        DP_WritePacketType  sWritePacket;
        uint8               uData[4];
        
        if (TRUE == bEnable)
        {
          // Write F004F (4 bytes) 01 55 63 00. Enable incept
          uData[0] = 0x01;
          uData[1] = 0x55;
          uData[2] = 0x63;
          uData[3] = 0x00;
        }
        else
        {
          // Write F004F (4 bytes) 01 55 63 68. Disable intercept
          uData[0] = 0x01;
          uData[1] = 0x55;
          uData[2] = 0x63;
          uData[3] = 0x68;
        }
        
        DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
        sWritePacket.eTransactionType    = DP_TRANSACTION_MODE_AUX;
        sWritePacket.puWriteData         = (uint8*) &uData;
        sWritePacket.uAddress            = DPCD_LTTPR_CUSTOM_SPECIFIC_ADDRESS;
        sWritePacket.uWriteDataSize      = DPCD_LTTPR_CUSTOM_SPECIFIC_LEN;
        sWritePacket.uBytesWritten       = 0;
        sWritePacket.bQueueOnly          = FALSE;
        
        if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket)))
        {
          DP_LOG_MESSAGE_ERROR( "DP%d: DP_EnableCustomLTTPRIntercept: intercept write Failed, bEnable=%d, eStatus=0x%x.",
                                pDeviceCtx->eControllerID, bEnable, eStatus);
        }
        break;
      }
      default:
      {
        eStatus = DP_STATUS_SUCCESS;
        break;
      }
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_WriteCustomLTTPRDPCDLevels()
//
//  @brief
//    This function will select the training Voltage Swing Level and Pre-emphasis Level for custom LTTPR retimer.
//
//  @params
//    [IN] pDisplayCtx
//      Pointer to context
//    [IN] uDesiredVoltageSwingLevel
//      The desired Voltage Swing level for link training
//    [IN] uDesiredPreEmphasisLevel
//      The desired pre-emphasis level for link training
//    [IN] eCustomSinkType
//      Custom sink type
//
//  @return: 
//   DP_Status
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_WriteCustomLTTPRDPCDLevels(DP_DisplayCtxType  *pDisplayCtx,
                                         uint32              uDesiredVoltageSwingLevel,
                                         uint32              uDesiredPreEmphasisLevel,
                                         DP_CustomSinkType   eCustomSinkType)
{
  DP_Status         eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType *pDeviceCtx;

  const uint8 aKandouVSPE[DPCD_LTTPR_CUSTOM_MAX_VSPE_LEVEL_NUM + 1] =
  {
    0x00,
    0x55,
    0xAA,
    0xFF,
  };

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_WriteCustomLTTPRDPCDLevels: Unexpected null context.");
  }
  else if ((DPCD_LTTPR_CUSTOM_MAX_VSPE_LEVEL_NUM < uDesiredVoltageSwingLevel) ||
           (DPCD_LTTPR_CUSTOM_MAX_VSPE_LEVEL_NUM < uDesiredPreEmphasisLevel))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_WriteCustomLTTPRDPCDLevels: Unexpected desired DPCD level.");
  }
  else
  {
    switch (eCustomSinkType)
    {
      case DP_CUSTOM_SINKID_1:
      {
        DP_WritePacketType sWritePacket;
        uint8              uWriteBuffer[4];
        
        uWriteBuffer[0] = 0x01;
        uWriteBuffer[1] = 0x51;
        uWriteBuffer[2] = 0x63;
        uWriteBuffer[3] = aKandouVSPE[uDesiredVoltageSwingLevel];
        
        /* Write F004F (4 bytes) 01 51 63 xx. xx values: VS=0: 00, VS=1: 55, VS=2: aa, VS=3: ff */
        DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
        sWritePacket.eTransactionType    = DP_TRANSACTION_MODE_AUX;
        sWritePacket.puWriteData         = (uint8*) &uWriteBuffer;
        sWritePacket.uAddress            = DPCD_LTTPR_CUSTOM_SPECIFIC_ADDRESS;
        sWritePacket.uWriteDataSize      = DPCD_LTTPR_CUSTOM_SPECIFIC_LEN;
        sWritePacket.uBytesWritten       = 0;
        sWritePacket.bQueueOnly          = FALSE;
        sWritePacket.eFlags              = DP_AUX_TRANSACTION_AUX_WAIT_STALL_FLAG;  // Use stall as link training is timing sensitive
        
        if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket)))
        {
          DP_LOG_MESSAGE_ERROR("DP_WriteCustomLTTPRDPCDLevels: Kandou VS Write Failed, eStatus=0x%x.", eStatus);
        }
        
        if (DP_STATUS_SUCCESS == eStatus)
        {
          uWriteBuffer[0] = 0x01;
          uWriteBuffer[1] = 0x52;
          uWriteBuffer[2] = 0x63;
          uWriteBuffer[3] = aKandouVSPE[uDesiredPreEmphasisLevel];
        
          /* Write F004F (4 bytes) 01 52 63 yy. yy values: PE=0: 00, PE=1: 55, PE=2: aa, PE=3: ff */
          DP_OSAL_MemSet(&sWritePacket, 0, sizeof(DP_WritePacketType));
          sWritePacket.eTransactionType    = DP_TRANSACTION_MODE_AUX;
          sWritePacket.puWriteData         = (uint8*) &uWriteBuffer;
          sWritePacket.uAddress            = DPCD_LTTPR_CUSTOM_SPECIFIC_ADDRESS;
          sWritePacket.uWriteDataSize      = DPCD_LTTPR_CUSTOM_SPECIFIC_LEN;
          sWritePacket.uBytesWritten       = 0;
          sWritePacket.bQueueOnly          = FALSE;
          sWritePacket.eFlags              = DP_AUX_TRANSACTION_AUX_WAIT_STALL_FLAG;  // Use stall as link training is timing sensitive
        
          if (DP_STATUS_SUCCESS != (eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket)))
          {
            DP_LOG_MESSAGE_ERROR("DP_WriteCustomLTTPRDPCDLevels: Kandou PE Write Failed, eStatus=0x%x.", eStatus);
          }
        }
        break;
      }
      default:
      {
        eStatus = DP_STATUS_SUCCESS;
        break;
      }
    }
  }

  return eStatus;
}


#ifdef __cplusplus
}
#endif

