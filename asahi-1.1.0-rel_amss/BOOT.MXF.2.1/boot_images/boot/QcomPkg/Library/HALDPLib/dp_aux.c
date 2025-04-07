/*=====================================================================================================================

  File: dp_aux.c

  DESCRIPTION: Implementation of DP AUX/I2C transaction logic.

  Copyright (c) 2016-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  =====================================================================================================================*/

/*---------------------------------------------------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------------------------------------------------*/
#include "dp_i.h"
#include "hal_dp_phy.h"
#include "dp_sim.h"
#include "dp_redirector.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------------------------------------------------
 * Macros
 *-------------------------------------------------------------------------------------------------------------------*/

/* Macro for logging aux transaction statistics: 
     aux level - bits 31:24
     retries   - bits 7:0
*/     
#define DP_AUX_LEVEL_RETRY(_level_, _retry_)      ((((_level_) & 0xFF)<<24) |  \
                                                  ((_retry_) & 0xFF))

/* Macro for logging aux transaction type and address: 
     type (i2c/aux) - bits 31:24
     address        - bits 23:0
*/     
#define DP_AUX_TYPE_ADDRESS(_type_, _address_)    ((((_type_) & 0xFF)<<24) |  \
                                                  ((_address_) & 0xFFFFFF))


/*---------------------------------------------------------------------------------------------------------------------
 * Defines
 *-------------------------------------------------------------------------------------------------------------------*/

#define DP_AUX_CMD_HEADER_SIZE_IN_BYTE            4                             /* AUX packet header size in byte            */

#define DP_AUX_MAX_I2C_RETRY                      7                             /* Number of retry attempts if AUX/I2C I/O defers (DP spec recommends 7)  */

#define DP_AUX_TRANS_TIMEOUT_MS                   (DP_AUX_HW_TIMEOUT_MS + 2)    /* SW timeout should be higher than HW timeout - add 2 ms buffer */
#define DP_AUX_DONE_POLL_STALL_INTERVAL_US        50                            /* 50 Us: stall interval between successive polls for AUX DONE of a transaction */   
#define DP_AUX_DONE_POLL_SLEEP_INTERVAL_MS        20                            /* 20 ms: value is chosen as sleep for smaller values is not very accurate */   

#define DP_I2C_TRANS_TIMEOUT_MS                   200                           /* in ms: how long to poll for I2C AUX Transaction Done before timing out */
#define DP_AUX_MAX_BUFFER_SIZE                    1024                          /* Artificial maximum aux buffer size limit used to prevent staying in AUX functions for too long */
#define DP_AUX_MAX_SEGMENT_SIZE                   16                            /* Every Aux transaction should no more than 16 bytes */
#define DP_AUX_NACK_DEFER_DELAY_MS                50                            /* Delay after a I2C consecutive Defer response, experimentally covers all of the possible sink delays */

/* Define the AUX/I2C packet struct to be send to DP controller H/W                                                 */
typedef struct  
{
  bool32                           bWriteCmd;                          /* 1: this is a write command, otherwise read*/
  uint32                           uCmdAddress;                        /* The read/write address for this command   */
  uint8                           *puCmdData;                          /* Command data pointer                      */
  uint32                           uLength;                            /* Length of command                         */
} DP_PackCmdType;

/*Define the LUT to convert DP_TransactionModeType to HAL_DP_AuxTransactionModeType */
HAL_DP_AuxTransactionModeType geHostTransTypeToHALTransType[HAL_DP_AUX_TRANSACTION_MODE_MAX]= 
{
  HAL_DP_AUX_TRANSACTION_MODE_NONE,    //DP_TRANSACTION_MODE_NONE
  HAL_DP_AUX_TRANSACTION_MODE_NATIVE,  //DP_TRANSACTION_MODE_AUX
  HAL_DP_AUX_TRANSACTION_MODE_I2C,     //DP_TRANSACTION_MODE_I2C
};


/* Define for all AUX transaction status */
#define HAL_DP_AUX_TRANSACTION_STATUS_ALL   (HAL_DP_AUXSTATUS_TYPE_AUX_I2C_DONE              |\
                                             HAL_DP_AUXSTATUS_TYPE_WRONG_ADDRESS             |\
                                             HAL_DP_AUXSTATUS_TYPE_CONSECUTIVE_TIMEOUT       |\
                                             HAL_DP_AUXSTATUS_TYPE_CONSECUTIVE_NACK_DEFER    |\
                                             HAL_DP_AUXSTATUS_TYPE_WRONG_READDATA_COUNT      |\
                                             HAL_DP_AUXSTATUS_TYPE_AUX_NACK_DURING_I2C       |\
                                             HAL_DP_AUXSTATUS_TYPE_AUX_DEFER_DURING_I2C)

/* Define for all AUX transaction failure status */
#define HAL_DP_AUX_TRANSACTION_FAIL         (HAL_DP_AUXSTATUS_TYPE_WRONG_ADDRESS             |\
                                             HAL_DP_AUXSTATUS_TYPE_CONSECUTIVE_TIMEOUT       |\
                                             HAL_DP_AUXSTATUS_TYPE_WRONG_READDATA_COUNT      |\
                                             HAL_DP_AUXSTATUS_TYPE_CONSECUTIVE_NACK_DEFER    |\
                                             HAL_DP_AUXSTATUS_TYPE_AUX_NACK_DURING_I2C       |\
                                             HAL_DP_AUXSTATUS_TYPE_AUX_DEFER_DURING_I2C)

//-------------------------------------------------------------------------------------------------
//  DP_PackCmd
//
//  @brief
//      This API will pack the AUX/I2C read/write packet into the format 
//      required by DP controller H/W.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN] psPackCmd
//          The packet to be packed.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
static DP_Status DP_PackCmd(DP_DisplayCtxType    *pDisplayCtx,
                            DP_PackCmdType       *psPackCmd)
{
  DP_Status          eStatus     = DP_STATUS_SUCCESS; 
  DP_DeviceCtxType  *pDeviceCtx  = DPHOST_GET_DEVICE_CTX(pDisplayCtx);

  if (NULL == pDeviceCtx)
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    uint32             uLen        = 0;  
    uint32             i           = 0;
    uint8             *pData       = NULL;
    

    if (TRUE == psPackCmd->bWriteCmd)
    {
      uLen = DP_AUX_CMD_HEADER_SIZE_IN_BYTE + psPackCmd->uLength;
    }
    else
    {
      uLen = DP_AUX_CMD_HEADER_SIZE_IN_BYTE;
    }

    if (pDeviceCtx->uAUXCmdBufferCurrentSize + uLen < pDeviceCtx->uMaxAUXCmdFifoLen)
    {
      pData = &(pDeviceCtx->uAUXCmdBuffer[pDeviceCtx->uAUXCmdBufferCurrentSize]); 

      /*   COMM[3:1]   COMM[0]     ADDR[19:16]
       *  --------------------------------------
       * | Reserved  |  Read   | Address[19:16] |
       *  --------------------------------------    */  
      *pData = (psPackCmd->uCmdAddress>>16) & 0xF;      
      if (FALSE == psPackCmd->bWriteCmd)
      {
        *pData |= 0x10;
      }
      
      /* ADDR[15:8] */
      *(++pData) = (psPackCmd->uCmdAddress>>8) & 0xFF;

      /* ADDR[7:0] */
      *(++pData) =  psPackCmd->uCmdAddress & 0xFF;

      /* LEN [7:0] */
      *(++pData) = (psPackCmd->uLength-1) & 0x0ff;

      /* Data bytes in case of write */
      if (TRUE == psPackCmd->bWriteCmd ) 
      {
        for (i = 0; i < psPackCmd->uLength; i++)
        {
          *(++pData) = psPackCmd->puCmdData[i];
        }
      }
      
      pDeviceCtx->uAUXCmdBufferCurrentSize += uLen;
      pDeviceCtx->uAUXNumOfTransaction++;
    }
    else
    {
      eStatus  = DP_STATUS_FAILED_PKT_LENGTH_EXCEED;
      DP_LOG_MESSAGE_ERROR("DP_PackCmd() : Transaction size is too large for the CMD FIFO");
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_Host_AuxInstall
//
//  @brief
//      Install AUX function table. AUX functions may need initialization before use.
//
//  @params
//      [IN] pDeviceCtx
//          Device context.
//      [IN] pStreamCtx
//          Stream context.
//      [IN] eFunctionType
//          Type of AUX function (physical, simulated, section redirector)
//
//  @return
//      void
//-------------------------------------------------------------------------------------------------
void DP_Host_AuxInstall(DP_DeviceCtxType  *pDeviceCtx,
                        DP_StreamCtxType  *pStreamCtx,
                        DP_AUXFunctionType eFunctionType)
{
  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx) ||
      (eFunctionType >= DP_AUX_FUNCTION_TYPE_MAX))
  {
    DP_LOG_MESSAGE_ERROR("DP: DP_Host_AuxInstall failed: Invalid parameter.");
  }
  else
  {
    uint32 uStreamID;

    for (uStreamID = 0; uStreamID < DP_MST_STREAM_ID_MAX; uStreamID++)
    {
      switch(eFunctionType)
      {
        case DP_AUX_FUNCTION_TYPE_REDIRECTOR:
        {
          pDeviceCtx->aStreamCtx[uStreamID].sAuxFunctions.DP_AUX_Read  = DP_Host_Redirector_ClientRead;
          pDeviceCtx->aStreamCtx[uStreamID].sAuxFunctions.DP_AUX_Write = DP_Host_Redirector_ClientWrite;
          TraceInfo(QdiTraceDP, "DP%d: Using AUX redirector for eDeviceId: %d, uStreamId: %d",
                    pStreamCtx->eDisplayID,
                    pDeviceCtx->eDeviceID,
                    uStreamID);
          break;
        }
        case DP_AUX_FUNCTION_TYPE_SIM:
        {
          pDeviceCtx->aStreamCtx[uStreamID].sAuxFunctions.DP_AUX_Read  = DP_Host_Simulation_ClientRead;
          pDeviceCtx->aStreamCtx[uStreamID].sAuxFunctions.DP_AUX_Write = DP_Host_Simulation_ClientWrite;
          TraceInfo(QdiTraceDP, "DP%d: Using AUX simulator for eDeviceId: %d, uStreamId: %d",
                    pStreamCtx->eDisplayID,
                    pDeviceCtx->eDeviceID,
                    uStreamID);
          break;
        }
        case DP_AUX_FUNCTION_TYPE_PHYSICAL:
        {
          pDeviceCtx->aStreamCtx[uStreamID].sAuxFunctions.DP_AUX_Read  = DP_Host_AUX_ClientRead;
          pDeviceCtx->aStreamCtx[uStreamID].sAuxFunctions.DP_AUX_Write = DP_Host_AUX_ClientWrite;
          TraceInfo(QdiTraceDP, "DP%d: Using physical AUX for eDeviceId: %d, uStreamId: %d",
                    pStreamCtx->eDisplayID,
                    pDeviceCtx->eDeviceID,
                    uStreamID);
          break;
        }
        default:
        {
          // DP_Host_Client{Read/Write} will use DP_Host_AUX_Client{Read,Write} if these are NULL.
          pDeviceCtx->aStreamCtx[uStreamID].sAuxFunctions.DP_AUX_Read  = NULL;
          pDeviceCtx->aStreamCtx[uStreamID].sAuxFunctions.DP_AUX_Write = NULL;
          TraceInfo(QdiTraceDP, "DP%d: Invalid AUX function type, using default for eDeviceId: %d, uStreamId: %d",
                    pStreamCtx->eDisplayID,
                    pDeviceCtx->eDeviceID,
                    uStreamID);
          break;
        }
      }
    }
  }
}

//-------------------------------------------------------------------------------------------------
//  DP_WaitAUXDone
//
//  @brief
//      This function will wait for the aux transaction to finish.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN] uFlags
//          Flags for sleep vs stall.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
static DP_Status DP_WaitAUXDone(DP_DisplayCtxType *pDisplayCtx,
                                uint32             uFlags)
{
  DP_Status                       eStatus        = DP_STATUS_FAILED_TIMEOUT;
  DP_DeviceCtxType               *pDeviceCtx     = DPHOST_GET_DEVICE_CTX(pDisplayCtx); 

  if (NULL == pDeviceCtx)
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_WaitAUXDone: Reference to Display context is NULL");
  }
  else
  {
    uint32                          i              = 0;
    uint32                          uIntrStatus    = 0;
    uint32                          uPollCount     = 1;
    uint32                          uPollInterval  = 1;

    /* Setting timeout depending on it is I2C over AUX Transaction or native AUX Transaction */
    uint32  uTimeoutMs = (DP_TRANSACTION_MODE_I2C == pDeviceCtx->eAUXTransactionTypeInQueue) ? 
                                                      DP_I2C_TRANS_TIMEOUT_MS : DP_AUX_TRANS_TIMEOUT_MS;

    /* Checking pDeviceCtx->uFlags to ensure interrupts are enabled by OS, otherwise may fail at boot time */
    /* Checking pDeviceCtx->hAuxReadyEvent to ensure event has been create to avoid waiting on a NULL event */
    /* Thus only if both of these conditions are satisfied we can switch to Interrupt mechanism */

    if ((NULL != pDeviceCtx->hAuxReadyEvent) && 
        (DP_HOST_FLAG_AUX_INTERRUPT_DRIVEN & pDeviceCtx->uFlags))
    {

      HAL_DP_Interrupt_Clear(pDeviceCtx->eControllerID, (HAL_DP_InterruptType) DP_AUX_TRANSACTION_INTR_ALL, 0);
      HAL_DP_Interrupt_Enable(pDeviceCtx->eControllerID, (HAL_DP_InterruptType) DP_AUX_TRANSACTION_INTR_ALL, 0);

      if (MDP_STATUS_OK == DISP_OSAL_WaitEvent(pDeviceCtx->hAuxReadyEvent, uTimeoutMs))
      {
        uIntrStatus = HAL_DP_AUX_Status(pDeviceCtx->eControllerID);
        DISP_OSAL_ResetEvent(pDeviceCtx->hAuxReadyEvent);
      }
      else
      {
        DP_LOG_MESSAGE_WARN("DP_WaitAUXDone: DISP_OSAL_WaitEvent() timeout, waited for %d ms ",uTimeoutMs);
      }

      HAL_DP_Interrupt_Disable(pDeviceCtx->eControllerID, (HAL_DP_InterruptType) DP_AUX_TRANSACTION_INTR_ALL, 0);
    }
    else
    {
      if (uFlags & DP_AUX_TRANSACTION_AUX_WAIT_STALL_FLAG)
      {
        uPollCount    = ((uTimeoutMs * 1000) / DP_AUX_DONE_POLL_STALL_INTERVAL_US) + 1;    
        uPollInterval = DP_AUX_DONE_POLL_STALL_INTERVAL_US;
      }
      else
      {
        uPollCount    = (uTimeoutMs / DP_AUX_DONE_POLL_SLEEP_INTERVAL_MS) + 1;  
        uPollInterval = DP_MIN(uTimeoutMs, DP_AUX_DONE_POLL_SLEEP_INTERVAL_MS);
      }

      for (i = 0; i < uPollCount; ++i)
      {
        uIntrStatus = HAL_DP_AUX_Status(pDeviceCtx->eControllerID);
        
        if (uIntrStatus & HAL_DP_AUX_TRANSACTION_STATUS_ALL)
        {
          break;
        }
        
        /* Stall or Sleep depending on user request */
        if (uFlags & DP_AUX_TRANSACTION_AUX_WAIT_STALL_FLAG)
        {
          DP_OSAL_StallUs(uPollInterval);
        }
        else
        {
          DP_OSAL_SleepMs(uPollInterval);
        }
      }

      uIntrStatus = HAL_DP_AUX_Status(pDeviceCtx->eControllerID);
    }

    /* Clear transaction so that next transaction / retry can be done */
    HAL_DP_AUX_ClearTransaction(pDeviceCtx->eControllerID);

    if (uIntrStatus & HAL_DP_AUX_TRANSACTION_STATUS_ALL)
    {
      HAL_DP_Interrupt_Clear(pDeviceCtx->eControllerID, (HAL_DP_InterruptType)uIntrStatus, 0);

      if (HAL_DP_AUXSTATUS_TYPE_AUX_I2C_DONE & uIntrStatus)
      {
        eStatus = DP_STATUS_SUCCESS;
      }
      else
      {
        TraceInfo(QdiTraceDP, "DP%d: AUX transaction failed (0x%x)",
                  pDeviceCtx->eDisplayID,
                  uIntrStatus);

        if (HAL_DP_AUXSTATUS_TYPE_CONSECUTIVE_NACK_DEFER & uIntrStatus)
        {
          eStatus = DP_STATUS_FAILED_AUX_NACK_DEFER;
        }
        else if (HAL_DP_AUX_TRANSACTION_FAIL & uIntrStatus)
        {
          eStatus = DP_STATUS_FAILED_RESOURCE_FATAL_ERROR;
        }
        
        /* Make sure sink is still connected
         *
         * In scenarios where the sink is unplugged before DP setup is complete, since interrupts are not enabled yet,
         * the HPD out will not be received. This check is to detect such case and prevent further aux retry.
         *
         * For type-C the HPD out will be received from USB, so this internal checking is not needed.
         */
        if ((DP_DEVICE_MODETYPE_DP == pDeviceCtx->eDeviceDPMode) &&
            (DP_HPD_STATUS_DISCONNECTED == HAL_DP_HPD_PanelPlugged(pDeviceCtx->eControllerID)))
        {
          TraceInfo(QdiTraceDP, "DP%d: Sink disconnected. Updating AUX status.", pDeviceCtx->eDisplayID);
          pDeviceCtx->bAuxReady = FALSE;
        }
      }
    }
    else
    {  
      TraceInfo(QdiTraceDP, "DP%d: Software timeout waiting for AUX/I2C interrupt ", pDeviceCtx->eDisplayID);
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_Host_AuxReadRaw
//
//  @brief
//      This function will read from AUX/I2c channel.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN/OUT] psReadPacket
//          The read packet.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_AuxReadRaw(DP_DisplayCtxType *pDisplayCtx,
                             DP_ReadPacketType *psReadPacket)
{
  DP_Status           eStatus    = DP_STATUS_FAIL;
  DP_StreamCtxType   *pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx);
  
  if ((NULL != pDisplayCtx) &&
      (NULL != pStreamCtx) &&
      (NULL != pStreamCtx->sAuxFunctions.DP_AUX_Read))
  {
    eStatus = pStreamCtx->sAuxFunctions.DP_AUX_Read(pDisplayCtx, psReadPacket);
  }
  else
  {
    eStatus = DP_Host_AUX_ClientRead(pDisplayCtx, psReadPacket);
  }  
  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_Host_AUX_ClientRead
//
//  @brief
//      This function will read from AUX/I2c channel.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN/OUT] psReadPacket
//          The read packet.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_AUX_ClientRead(DP_DisplayCtxType    *pDisplayCtx,
                                 DP_ReadPacketType    *psReadPacket)
{
  DP_Status           eStatus          = DP_STATUS_SUCCESS; 
  DP_DeviceCtxType   *pDeviceCtx       = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType   *pStreamCtx       = DPHOST_GET_STREAM_CTX(pDisplayCtx);

  if ((NULL == pDeviceCtx) || 
      (NULL == pStreamCtx) ||
      (NULL == psReadPacket))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else if (FALSE == pDeviceCtx->bAuxReady)
  {
    /* Check for plug out before waiting for aux lock */
    eStatus = DP_STATUS_FAILED_RESOURCE_NOT_READY;
  }
  else
  {
    MDP_Status       eLocalStatus     = MDP_STATUS_OK; 

    // Log the start for profiling
    DISP_OSAL_EVENTLOG4(DISP_OSAL_EVENT_DISPLAY_READ_START, pDeviceCtx->eControllerID, 
                                                            pStreamCtx->eMSTStreamId, 
                                                            DP_AUX_TYPE_ADDRESS(psReadPacket->eTransactionType, psReadPacket->uAddress),
                                                            psReadPacket->uReadSize);     

    // Acquire lock to ensure that no two threads can read/write AUX at the same time
    if (MDP_STATUS_OK != (eLocalStatus = DISP_OSAL_AcquireLockEvent(pDeviceCtx->hAuxAccessLock, 0x00)))
    {
      // Fail if lock is not acquired
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DISP_OSAL_LOG_WARN1("DP_Host_AUX_ClientRead() DISP_OSAL_AcquireLockEvent() failed qdiStatus=%d", eLocalStatus);
    }
    else if ((pDeviceCtx->eAUXTransactionTypeInQueue != DP_TRANSACTION_MODE_NONE) &&
            (pDeviceCtx->eAUXTransactionTypeInQueue != psReadPacket->eTransactionType))
    {
      // Release the acquired lock
      DISP_OSAL_ReleaseLockEvent(pDeviceCtx->hAuxAccessLock);

      DP_LOG_MESSAGE_ERROR("DP_Host_AUX_ClientRead() : All transactions in the queued batch must be of same type");
      eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
    }
    else if (HAL_DP_AUX_TRANSACTION_MODE_MAX <= psReadPacket->eTransactionType)
    {
      // Release the acquired lock
      DISP_OSAL_ReleaseLockEvent(pDeviceCtx->hAuxAccessLock);

      DP_LOG_MESSAGE_ERROR("DP_Host_AUX_ClientRead() : psReadPacket->eTransactionType is out of range");
      eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    }
    else
    {
      uint32                       uRetryNum     = 0;
      uint32                       uAuxPhyCfgIdx = 0;
      DP_PackCmdType               sPackCmd;
      HAL_DP_WritePacketType       sHALWritePacket;
      HAL_DP_ReadPacketType        sHALReadPacket;

      sPackCmd.bWriteCmd    = FALSE;
      sPackCmd.uCmdAddress  = psReadPacket->uAddress;
      sPackCmd.puCmdData    = NULL;
      sPackCmd.uLength      = psReadPacket->uReadSize;

      /* Pack into software queue */
      eStatus = DP_PackCmd(pDisplayCtx, &sPackCmd);

      pDeviceCtx->eAUXTransactionTypeInQueue = psReadPacket->eTransactionType;
      psReadPacket->uBytesRead               = 0;

      if ((DP_STATUS_SUCCESS == eStatus) &&
          (FALSE             == psReadPacket->bQueueOnly))
      {
        HAL_DP_AuxPhyCfgType    sAuxPhyCfg;

        sAuxPhyCfg.pDPAuxPhyCfg1Index = &uAuxPhyCfgIdx;

        for (;;)
        {
          for (uRetryNum = 0; uRetryNum <= DP_AUX_MAX_I2C_RETRY; uRetryNum++)
          {
            if (FALSE == pDeviceCtx->bAuxReady)
            {
              TraceInfo(QdiTraceDP, "DP%d: Plug out during AUX read or AUX controller is not setup yet", pStreamCtx->eDisplayID);
              eStatus = DP_STATUS_FAILED_RESOURCE_NOT_READY;
              break;
            }
            
            sHALWritePacket.eTransactionType    = geHostTransTypeToHALTransType[psReadPacket->eTransactionType];
            sHALWritePacket.puWriteData         = pDeviceCtx->uAUXCmdBuffer;
            sHALWritePacket.uNumofTransactions  = pDeviceCtx->uAUXNumOfTransaction;
            sHALWritePacket.uWriteDataSize      = pDeviceCtx->uAUXCmdBufferCurrentSize;

            /* Send the command */
            HAL_DP_Write(pDeviceCtx->eControllerID, &sHALWritePacket, HAL_DP_AUXFLAGS_READ);

            eStatus = DP_WaitAUXDone(pDisplayCtx, psReadPacket->eFlags);

            if ((DP_STATUS_SUCCESS == eStatus) ||
                (FALSE == pDeviceCtx->bAuxReady))
            {
              break;
            }
            else if (DP_STATUS_FAILED_AUX_NACK_DEFER == eStatus)
            {
              DP_OSAL_SleepMs(DP_AUX_NACK_DEFER_DELAY_MS);
            }
          }

          if ((DP_STATUS_SUCCESS == eStatus) ||
              (FALSE == pDeviceCtx->bAuxReady))
          {
            break;
          }
          else
          {
            /* AUX Write failed, try next AUX PHY setting */
            uAuxPhyCfgIdx++;
            
            if (HAL_MDSS_STATUS_SUCCESS != HAL_DP_PHY_AUXConfig(pDeviceCtx->eDeviceID, &sAuxPhyCfg))
            {
              /* Tried all AUX PHY settings */
              break;
            }

            /* HW team recommended to add a sleep of 1ms after setting the new aux config */
            DP_OSAL_SleepMs(1);
          }
        }

        /* Reset AUX related context */
        pDeviceCtx->uAUXCmdBufferCurrentSize    = 0;
        pDeviceCtx->uAUXNumOfTransaction        = 0;
        pDeviceCtx->eAUXTransactionTypeInQueue  = DP_TRANSACTION_MODE_NONE;

        if (DP_STATUS_SUCCESS == eStatus)
        {
          /* Read the reply: data should be in the DATA FIFO now */
          sHALReadPacket.puReadDataBuffer = psReadPacket->puReadDataBuffer;
          sHALReadPacket.uReadSize        = psReadPacket->uReadSize;
          HAL_DP_Read(pDeviceCtx->eControllerID, &sHALReadPacket, 0);

          psReadPacket->uBytesRead = sHALReadPacket.uBytesRead;

        }
        else
        {
          TraceInfo(QdiTraceDP, "DP%d: AUX Read at addr 0x%x failed",
                    pStreamCtx->eDisplayID,
                    psReadPacket->uAddress);
        }
      }

      // Release the acquired lock
      DISP_OSAL_ReleaseLockEvent(pDeviceCtx->hAuxAccessLock);

      // Log the completion for profiling
      DISP_OSAL_EVENTLOG4(DISP_OSAL_EVENT_DISPLAY_READ_END, pDeviceCtx->eControllerID, 
                                                            pStreamCtx->eMSTStreamId, 
                                                            eStatus, 
                                                            DP_AUX_LEVEL_RETRY(uAuxPhyCfgIdx, uRetryNum));
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_Host_AuxWriteRaw
//
//  @brief
//      This API allows users to send the eDP command out to DP Panels.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN] pWritePacket
//          Command package to be sent out to DP panels.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_AuxWriteRaw(DP_DisplayCtxType  *pDisplayCtx,
                              DP_WritePacketType *psWritePacket)
{
  DP_Status           eStatus    = DP_STATUS_FAIL;
  DP_StreamCtxType   *pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx);

  if ((NULL != pDisplayCtx) &&
      (NULL != pStreamCtx) && 
      (NULL != pStreamCtx->sAuxFunctions.DP_AUX_Write))
  {
    eStatus = pStreamCtx->sAuxFunctions.DP_AUX_Write(pDisplayCtx, psWritePacket);
  }
  else
  {
    eStatus = DP_Host_AUX_ClientWrite(pDisplayCtx, psWritePacket);
  }
  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_Host_AUX_ClientWrite
//
//  @brief
//      This API allows users to send the eDP command out to DP Panels.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN] pWritePacket
//          Command package to be sent out to DP panels.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_AUX_ClientWrite(DP_DisplayCtxType   *pDisplayCtx,
                                  DP_WritePacketType  *psWritePacket)
{
  DP_Status           eStatus      = DP_STATUS_SUCCESS; 
  DP_DeviceCtxType   *pDeviceCtx   = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType   *pStreamCtx   = DPHOST_GET_STREAM_CTX(pDisplayCtx);

  if((NULL == pDeviceCtx) ||
     (NULL == pStreamCtx) ||
     (NULL == psWritePacket))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else if (FALSE == pDeviceCtx->bAuxReady)
  {
    /* Check for plug out before waiting for aux lock */
    eStatus = DP_STATUS_FAILED_RESOURCE_NOT_READY;
  }
  else
  {
    MDP_Status       eLocalStatus = MDP_STATUS_OK;

    // Log the start for profiling
    DISP_OSAL_EVENTLOG4(DISP_OSAL_EVENT_DISPLAY_WRITE_START, pDeviceCtx->eControllerID, 
                                                             pStreamCtx->eMSTStreamId, 
                                                             DP_AUX_TYPE_ADDRESS(psWritePacket->eTransactionType, psWritePacket->uAddress),
                                                             psWritePacket->uWriteDataSize);     

    // Acquire lock to ensure that no two threads can read/write AUX at the same time
    if (MDP_STATUS_OK != (eLocalStatus = DISP_OSAL_AcquireLockEvent(pDeviceCtx->hAuxAccessLock, 0x00)))
    {
      // Fail if lock is not acquired
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DISP_OSAL_LOG_WARN1("DP_Host_AUX_ClientWrite() DISP_OSAL_AcquireLockEvent() failed qdiStatus=%d", eLocalStatus);
    }
    else if ((pDeviceCtx->eAUXTransactionTypeInQueue != DP_TRANSACTION_MODE_NONE) &&
            (pDeviceCtx->eAUXTransactionTypeInQueue != psWritePacket->eTransactionType))
    {
      // Release the acquired lock
      DISP_OSAL_ReleaseLockEvent(pDeviceCtx->hAuxAccessLock);

      DP_LOG_MESSAGE_ERROR("DP_Host_AUX_ClientWrite() : All transactions in the queued batch must be of same type");
      eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
    }
    else if (HAL_DP_AUX_TRANSACTION_MODE_MAX <= psWritePacket->eTransactionType)
    {
      // Release the acquired lock
      DISP_OSAL_ReleaseLockEvent(pDeviceCtx->hAuxAccessLock);

      DP_LOG_MESSAGE_ERROR("DP_Host_AUX_ClientWrite() : psWritePacket->eTransactionType is out of range");
      eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    }
    else
    {
      uint32                       uRetryNum     = 0;
      uint32                       uAuxPhyCfgIdx = 0;      
      HAL_DP_WritePacketType       sHALWritePacket;
      DP_PackCmdType               sPackCmd;

      sPackCmd.bWriteCmd   = TRUE;
      sPackCmd.uCmdAddress = psWritePacket->uAddress;
      sPackCmd.puCmdData   = psWritePacket->puWriteData;
      sPackCmd.uLength     = psWritePacket->uWriteDataSize;

      eStatus = DP_PackCmd(pDisplayCtx, &sPackCmd);

      pDeviceCtx->eAUXTransactionTypeInQueue = psWritePacket->eTransactionType;

      psWritePacket->uBytesWritten = 0;

      DP_OSAL_MemSet(&sHALWritePacket, 0, sizeof(HAL_DP_WritePacketType));

      if ((DP_STATUS_SUCCESS == eStatus) &&
          (FALSE == psWritePacket->bQueueOnly))
      {
        HAL_DP_AuxPhyCfgType    sAuxPhyCfg;

        sAuxPhyCfg.pDPAuxPhyCfg1Index = &uAuxPhyCfgIdx;

        for (;;)
        {
          for (uRetryNum = 0; uRetryNum <= DP_AUX_MAX_I2C_RETRY; uRetryNum++)
          {
            if (FALSE == pDeviceCtx->bAuxReady)
            {
              TraceInfo(QdiTraceDP, "DP%d: Plug out during AUX write or AUX controller is not setup yet", pStreamCtx->eDisplayID);
              eStatus = DP_STATUS_FAILED_RESOURCE_NOT_READY;
              break;
            }
          
            sHALWritePacket.eTransactionType   = geHostTransTypeToHALTransType[psWritePacket->eTransactionType];
            sHALWritePacket.puWriteData        = pDeviceCtx->uAUXCmdBuffer;
            sHALWritePacket.uNumofTransactions = pDeviceCtx->uAUXNumOfTransaction;
            sHALWritePacket.uWriteDataSize     = pDeviceCtx->uAUXCmdBufferCurrentSize;

            /* Send the command */
            HAL_DP_Write(pDeviceCtx->eControllerID, &sHALWritePacket, 0);

            eStatus = DP_WaitAUXDone(pDisplayCtx, psWritePacket->eFlags);

            if (DP_STATUS_SUCCESS == eStatus)
            {
              psWritePacket->uBytesWritten = sHALWritePacket.uBytesWritten;
              break;
            }
            else if (FALSE == pDeviceCtx->bAuxReady)
            {
              break;
            }
            else if (DP_STATUS_FAILED_AUX_NACK_DEFER == eStatus)
            {
              DP_OSAL_SleepMs(DP_AUX_NACK_DEFER_DELAY_MS);
            }

          }

          if ((DP_STATUS_SUCCESS == eStatus) ||
              (FALSE             == pDeviceCtx->bAuxReady))
          {
            break;
          }
          else
          {
            /* AUX Write failed, try next AUX PHY setting */
            uAuxPhyCfgIdx++;
            if (HAL_MDSS_STATUS_SUCCESS != HAL_DP_PHY_AUXConfig(pDeviceCtx->eDeviceID, &sAuxPhyCfg))
            {
              /* Tried all AUX PHY settings */
              break;
            }

            /* HW team recommended to add a sleep of 1ms after setting the new aux config */
            DP_OSAL_SleepMs(1);
          }
        }
        
        /* Reset AUX related context */
        pDeviceCtx->uAUXCmdBufferCurrentSize    = 0;
        pDeviceCtx->uAUXNumOfTransaction        = 0;
        pDeviceCtx->eAUXTransactionTypeInQueue  = DP_TRANSACTION_MODE_NONE;

        if (DP_STATUS_SUCCESS != eStatus)      
        {
          TraceInfo(QdiTraceDP, "DP%d: AUX Write at addr 0x%x FAILED", pStreamCtx->eDisplayID, psWritePacket->uAddress);
        }
        else if (sHALWritePacket.uBytesWritten != sHALWritePacket.uWriteDataSize)
        {
          eStatus  = DP_STATUS_FAILED_RESOURCE_FAILED;
          TraceInfo(QdiTraceDP, "DP%d: AUX Write (addr: 0x%x) - bytes written (%d) is not expected (%d)",
                    pStreamCtx->eDisplayID, 
                    psWritePacket->uAddress,
                    sHALWritePacket.uBytesWritten,
                    sHALWritePacket.uWriteDataSize);
          DP_LOG_MESSAGE_ERROR("DP_Host_AUX_ClientWrite() : Bytes Written(0x%x) is not expected", sHALWritePacket.uBytesWritten);
        }
      }

      // Release the acquired lock
      DISP_OSAL_ReleaseLockEvent(pDeviceCtx->hAuxAccessLock);

      // Log the completion for profiling
      DISP_OSAL_EVENTLOG4(DISP_OSAL_EVENT_DISPLAY_WRITE_END, pDeviceCtx->eControllerID, 
                                                             pStreamCtx->eMSTStreamId, 
                                                             eStatus, 
                                                             DP_AUX_LEVEL_RETRY(uAuxPhyCfgIdx, uRetryNum));
    }
  } 

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_Host_AuxRead
//
//  @brief
//      API to read AUX data from DPCD offset, EDID and MST topology. It breaks each read into 16 bytes segments.
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [OUT] pMessage
//          Message that is read from sink which is allocated by caller.
//      [IN/OUT] pMessageSize
//          Message size. Size is updated if size is different from caller provided value.
//      [IN] uReadAddress
//          DPCD offset to read from.
//      [IN] eTranscationType
//          DP Transaction type native aux or I2C
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_AuxRead(DP_DisplayCtxType      *pDisplayCtx,
                          uint8                  *pMessage,
                          uint32                 *pMessageSize,
                          uint32                  uReadAddress,
                          DP_TransactionModeType  eTransactionType)
{
  DP_Status           eStatus     = DP_STATUS_SUCCESS;
 
  if ((NULL == pDisplayCtx)  ||
      (NULL == pMessage)     ||
      (NULL == pMessageSize) ||
      ((DP_TRANSACTION_MODE_I2C != eTransactionType) && 
       (DP_TRANSACTION_MODE_AUX != eTransactionType)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_Host_AuxRead() Invalid input");
  }
  else
  { 
    if ((0 == *pMessageSize) ||
        (*pMessageSize > DP_AUX_MAX_BUFFER_SIZE))
    {
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DP_LOG_MESSAGE_ERROR("DP_Host_AuxRead() Invalid message size=%d", *pMessageSize);
    }
    else
    {
      uint32            uSizeRead    = 0;             // Number of bytes read from FIFO
      DP_ReadPacketType sReadPacket;
      DP_DeviceCtxType *pDeviceCtx   = DPHOST_GET_DEVICE_CTX(pDisplayCtx);

      // Messages are read in 16 byte segments
      do 
      {          
        DP_OSAL_MemSet(&sReadPacket, 0x0 , sizeof(DP_ReadPacketType));

        sReadPacket.eTransactionType = eTransactionType;

        if (DP_TRANSACTION_MODE_AUX == eTransactionType)
        {
          sReadPacket.uAddress       = uReadAddress + uSizeRead;
        }
        else 
        {
          // In I2C case, we read the same address
          sReadPacket.uAddress       = uReadAddress;
          
          // For I2C read if this is not the last data block to be read, set MOT bit to maintain segment and offset
          if ((*pMessageSize - uSizeRead) > DP_AUX_MAX_SEGMENT_SIZE)
          {
            sReadPacket.eFlags       |= DP_AUX_TRANSACTION_I2C_SET_MOT_FLAG;
          }
        }

        sReadPacket.eFlags           |= DP_AUX_TRANSACTION_AUX_WAIT_STALL_FLAG; // Use stall for polling for better timer resolution

        if ((*pMessageSize - uSizeRead) < DP_AUX_MAX_SEGMENT_SIZE)
        {
          sReadPacket.uReadSize      = *pMessageSize - uSizeRead;
        }
        else 
        {
          sReadPacket.uReadSize      = DP_AUX_MAX_SEGMENT_SIZE;
        }
        
        sReadPacket.puReadDataBuffer = &pMessage[uSizeRead];
      
        eStatus = DP_Host_AuxReadRaw(pDisplayCtx, &sReadPacket);

        // Update number of bytes read 
        uSizeRead += sReadPacket.uReadSize;
      } while ((DP_STATUS_SUCCESS == eStatus) && 
              (uSizeRead < *pMessageSize));
        

      if (DP_STATUS_FAILED_RESOURCE_NOT_READY == eStatus)
      {
        // Sink was plugged out. Log it and return success
        TraceInfo(QdiTraceDP, "DP%d: Sink not connected. Skip AuxRead from addr:0x%04x", 
                  pDeviceCtx->eDisplayID, 
                  uReadAddress);
        eStatus = DP_STATUS_SUCCESS;
      }
      else if (DP_STATUS_SUCCESS != eStatus)
      {
        DP_LOG_MESSAGE_ERROR("DP_Host_AuxRead() failed with DPstatus = %d", eStatus);
      }
      else
      {
        *pMessageSize = uSizeRead;
      }

      /* Diag level 1 - MST Aux data */
      if (pDeviceCtx->eDiagLevel >= DP_DIAG_LEVEL_1)
      {
        uint32 uIndex       = 0;

        // Log Aux read data
        for (uIndex = 0; uIndex < uSizeRead; uIndex += 8)
        {
          TraceVerb(QdiTraceDP, "DP%d: AuxRead Addr:0x%04x Size:%2d Data[%02x]:[%02x %02x %02x %02x %02x %02x %02x %02x]", 
                    pDeviceCtx->eDisplayID, 
                    uReadAddress, uSizeRead, uIndex,
                    (uIndex < uSizeRead) ? pMessage[uIndex] : 0,
                    ((uIndex+1) < uSizeRead) ? pMessage[uIndex+1] : 0,
                    ((uIndex+2) < uSizeRead) ? pMessage[uIndex+2] : 0,
                    ((uIndex+3) < uSizeRead) ? pMessage[uIndex+3] : 0,
                    ((uIndex+4) < uSizeRead) ? pMessage[uIndex+4] : 0,
                    ((uIndex+5) < uSizeRead) ? pMessage[uIndex+5] : 0,
                    ((uIndex+6) < uSizeRead) ? pMessage[uIndex+6] : 0,
                    ((uIndex+7) < uSizeRead) ? pMessage[uIndex+7] : 0);
        }
      }
    }
  } 
  
  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_Host_AuxWrite
//
//  @brief
//      API to write data over AUX at specified DPCD and MST address. Data should be written in 
//      16 byte segments
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN] eMessageType
//          Message type to be written to sink.
//      [OUT] pMessage
//          Message that is written to sink.
//      [IN] uMessageSize
//          Message size.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_AuxWrite(DP_DisplayCtxType      *pDisplayCtx,
                           uint8                  *pMessage,
                           uint32                  uMessageSize, 
                           uint32                  uWriteAddress)
{
  DP_Status           eStatus     = DP_STATUS_SUCCESS; 

  if ((NULL == pDisplayCtx) ||
      (NULL == pMessage))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("DP_Host_AuxWrite() Invalid input");
  }
  else
  { 
    // Check if the message to be written is larger than expected size of message
    if ((0 == uMessageSize) || 
        (uMessageSize > DP_AUX_MAX_BUFFER_SIZE))
    {
      eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
      DP_LOG_MESSAGE_ERROR("DP_Host_AuxWrite() Invalid message size=%d", uMessageSize);
    }
    else
    {
      DP_WritePacketType sWritePacket;
      uint32             uSizeWrite    = 0;              // Number of bytes written
      DP_DeviceCtxType  *pDeviceCtx    = DPHOST_GET_DEVICE_CTX(pDisplayCtx);

      /* Diag level 1 - MST Aux data */
      if (pDeviceCtx->eDiagLevel >= DP_DIAG_LEVEL_1)
      {
        uint32             uIndex;

        // Log Aux write information
        for (uIndex = 0; uIndex < uMessageSize; uIndex += 8)
        {
          TraceVerb(QdiTraceDP, "DP%d: AuxWrite Addr:0x%04x Size:%2d Data[%02x]:[%02x %02x %02x %02x %02x %02x %02x %02x]", 
                    pDeviceCtx->eDisplayID,
                    uWriteAddress, uMessageSize, uIndex,
                    (uIndex < uMessageSize) ? pMessage[uIndex] : 0,
                    ((uIndex+1) < uMessageSize) ? pMessage[uIndex+1] : 0,
                    ((uIndex+2) < uMessageSize) ? pMessage[uIndex+2] : 0,
                    ((uIndex+3) < uMessageSize) ? pMessage[uIndex+3] : 0,
                    ((uIndex+4) < uMessageSize) ? pMessage[uIndex+4] : 0,
                    ((uIndex+5) < uMessageSize) ? pMessage[uIndex+5] : 0,
                    ((uIndex+6) < uMessageSize) ? pMessage[uIndex+6] : 0,
                    ((uIndex+7) < uMessageSize) ? pMessage[uIndex+7] : 0);
        }
      }

      do 
      {          
        DP_OSAL_MemSet(&sWritePacket, 0x0 , sizeof(DP_WritePacketType));

        sWritePacket.eTransactionType = DP_TRANSACTION_MODE_AUX;
        sWritePacket.uAddress         = uWriteAddress + uSizeWrite;
        sWritePacket.eFlags           = DP_AUX_TRANSACTION_AUX_WAIT_STALL_FLAG; // Use stall for polling for better timer resolution

        if ((uMessageSize - uSizeWrite) < DP_AUX_MAX_SEGMENT_SIZE)
        {
          sWritePacket.uWriteDataSize      = uMessageSize - uSizeWrite;
        }
        else 
        {
          sWritePacket.uWriteDataSize      = DP_AUX_MAX_SEGMENT_SIZE;
        }
        
        sWritePacket.puWriteData      = &pMessage[uSizeWrite]; 
      
        eStatus = DP_Host_AuxWriteRaw(pDisplayCtx, &sWritePacket);

        // Update number of bytes written 
        uSizeWrite += sWritePacket.uWriteDataSize;
      
      } while ((DP_STATUS_SUCCESS == eStatus) && 
              (uSizeWrite < uMessageSize));
      
      if (DP_STATUS_FAILED_RESOURCE_NOT_READY == eStatus)
      {
        // Sink was plugged out. Log it and return success
        TraceInfo(QdiTraceDP, "DP%d: Sink not connected. Skip AuxWrite to addr:0x%04x", 
                  pDeviceCtx->eDisplayID, 
                  uWriteAddress);
        eStatus = DP_STATUS_SUCCESS;
      }
      else if (DP_STATUS_SUCCESS != eStatus)
      {
        DP_LOG_MESSAGE_ERROR("DP_Host_AuxWrite() failed with DPstatus = %d", eStatus);
        TraceInfo(QdiTraceDP, "DP%d: AuxWrite failed [Addr:0x%x Size: %d bytes : Status: %d]",
                  pDeviceCtx->eDisplayID,
                  uWriteAddress, 
                  uMessageSize, 
                  eStatus);
      }
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  TriggerSoftHPDInterrupt
//
//  @brief
//      For standalone DP controller check the current connection status and 
//      generate a soft HPD out interrupt 
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//
//  @return
//      DP_STATUS_SUCCESS if DP is not connected and Soft HPD interrupt has been fired
//-------------------------------------------------------------------------------------------------
//
static DP_Status TriggerSoftHPDInterrupt(DP_DisplayCtxType *pDisplayCtx)
{
  DP_Status         eStatus    = DP_STATUS_SUCCESS;
  DP_DeviceCtxType *pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx);

  if (NULL == pDeviceCtx)
  {
    DISP_OSAL_LOGX("TriggerSoftHPDInterrupt: Unexpected null handle");
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else
  {
    /* For standalone DP controller the reset may cause loss of HPD Out event
      so checking the current connection status to generate a soft HPD out interrupt.
      For Type-C DP Plug-in/out notification will come from USB IOCTL, so this
      workaround is not needed.
    */
    if ((DP_DEVICE_MODETYPE_DP      == pDeviceCtx->eDeviceDPMode) &&
        (DP_HPD_STATUS_DISCONNECTED == HAL_DP_HPD_PanelPlugged(pDeviceCtx->eControllerID)))
    {
      DP_Status                eRetStatus      = DP_STATUS_SUCCESS;
      DP_SetPropertyParamsType sDPProp;
      
      DISP_OSAL_MemZero(&sDPProp, sizeof(DP_SetPropertyParamsType));
      sDPProp.bConnected = FALSE;

      if (DP_STATUS_SUCCESS != (eRetStatus = DP_Host_SetProperty(pDisplayCtx, DP_SETPROPERTY_CONNECTION_STATUS, &sDPProp)))
      {
        DISP_OSAL_LOGX("TriggerSoftHPDInterrupt: DP_Host_SetProperty failed to set connection status, eRetStatus =%d", eRetStatus);
      }
      DP_SoftHPDInterrupt(MDP_DISPLAY_EXTERNAL, FALSE);
    }
    else
    {
      eStatus = DP_STATUS_FAIL;
    }
  } 

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_Host_Simulation_ClientRead
//
//  @brief
//      This function will read from AUX/I2c channel from memory
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN/OUT] psReadPacket
//          The read packet.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status  DP_Host_Simulation_ClientRead(DP_DisplayCtxType *pDisplayCtx,
                                         DP_ReadPacketType *psReadPacket)
{
  DP_Status         eStatus    = DP_STATUS_SUCCESS;
  DP_DeviceCtxType *pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType *pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx);

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx) ||
      (NULL == psReadPacket))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else if (FALSE == pDeviceCtx->bAuxReady)
  {
    /* Check for plug out before waiting for aux lock */
    eStatus = DP_STATUS_FAILED_RESOURCE_NOT_READY;
  }
  else
  {
    MDP_Status       eLocalStatus = MDP_STATUS_OK;

    // Log the start for profiling
    DISP_OSAL_EVENTLOG4(DISP_OSAL_EVENT_DISPLAY_READ_START, pDeviceCtx->eControllerID,
                                                            pStreamCtx->eMSTStreamId,
                                                            DP_AUX_TYPE_ADDRESS(psReadPacket->eTransactionType, 
                                                            psReadPacket->uAddress),
                                                            psReadPacket->uReadSize);

    // Acquire lock to ensure that no two threads can read/write AUX at the same time
    if (MDP_STATUS_OK != (eLocalStatus = DISP_OSAL_AcquireLockEvent(pDeviceCtx->hAuxAccessLock, 0x00)))
    {
      // Fail if lock is not acquired
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DISP_OSAL_LOG_WARN1("DP_Host_Simulation_ClientRead() DISP_OSAL_AcquireLockEvent() failed qdiStatus=%d", eLocalStatus);
    }
    else if ((pDeviceCtx->eAUXTransactionTypeInQueue != DP_TRANSACTION_MODE_NONE) &&
            (pDeviceCtx->eAUXTransactionTypeInQueue != psReadPacket->eTransactionType))
    {
      // Release the acquired lock
      DISP_OSAL_ReleaseLockEvent(pDeviceCtx->hAuxAccessLock);
        
      DP_LOG_MESSAGE_ERROR("DP_Host_Simulation_ClientRead() : All transactions in the queued batch must be of same type");
      eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
    }
    else
    {
      psReadPacket->uBytesRead = DP_SimulationAuxRead((SIM_DeviceIDType)pDeviceCtx->eDeviceID,
                                                      psReadPacket->uAddress,
                                                      psReadPacket->uReadSize,
                                                      psReadPacket->puReadDataBuffer,
                                                      (eModeType)psReadPacket->eTransactionType);
      // Release the acquired lock
      DISP_OSAL_ReleaseLockEvent(pDeviceCtx->hAuxAccessLock);
     }
    
    // Log the completion for profiling
    DISP_OSAL_EVENTLOG3(DISP_OSAL_EVENT_DISPLAY_READ_END, pDeviceCtx->eControllerID,
        pStreamCtx->eMSTStreamId,
        eStatus);
  }
  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  DP_Host_Simulation_ClientWrite
//
//  @brief
//      This function will write to AUX/I2c channel from memory
//
//  @params
//      [IN] pDisplayCtx
//          DP Context.
//      [IN] pWritePacket
//          Command package to be sent out to DP panels.
//
//  @return
//      DP_STATUS_SUCCESS.
//-------------------------------------------------------------------------------------------------
//
DP_Status DP_Host_Simulation_ClientWrite(DP_DisplayCtxType  *pDisplayCtx,
                                         DP_WritePacketType *psWritePacket)
{
  DP_Status         eStatus    = DP_STATUS_SUCCESS;
  DP_DeviceCtxType *pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx);
  DP_StreamCtxType *pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx);

  if ((NULL == pDeviceCtx) ||
      (NULL == pStreamCtx) ||
      (NULL == psWritePacket))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
  }
  else if (FALSE == pDeviceCtx->bAuxReady)
  {
    /* Check for plug out before waiting for aux lock */
    eStatus = DP_STATUS_FAILED_RESOURCE_NOT_READY;
  }
  else
  {
    MDP_Status       eLocalStatus = MDP_STATUS_OK;

    // Log the start for profiling
    DISP_OSAL_EVENTLOG4(DISP_OSAL_EVENT_DISPLAY_WRITE_START, pDeviceCtx->eControllerID,
                                                             pStreamCtx->eMSTStreamId,
                                                             DP_AUX_TYPE_ADDRESS(psWritePacket->eTransactionType,
                                                             psWritePacket->uAddress),
                                                             psWritePacket->uWriteDataSize);

    // Acquire lock to ensure that no two threads can read/write AUX at the same time
    if (MDP_STATUS_OK != (eLocalStatus = DISP_OSAL_AcquireLockEvent(pDeviceCtx->hAuxAccessLock, 0x00)))
    {
      // Fail if lock is not acquired
      eStatus = DP_STATUS_FAILED_RESOURCE_FAILED;
      DISP_OSAL_LOG_WARN1("DP_Host_Simulation_ClientWrite() DISP_OSAL_AcquireLockEvent() failed qdiStatus=%d", eLocalStatus);
    }
    else if ((pDeviceCtx->eAUXTransactionTypeInQueue != DP_TRANSACTION_MODE_NONE) &&
             (pDeviceCtx->eAUXTransactionTypeInQueue != psWritePacket->eTransactionType))
    {
      // Release the acquired lock
      DISP_OSAL_ReleaseLockEvent(pDeviceCtx->hAuxAccessLock);

      DP_LOG_MESSAGE_ERROR("DP_Host_Simulation_ClientWrite() : All transactions in the queued batch must be of same type");
      eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
    }
    else
    {
      /* Send the command */
      psWritePacket->uBytesWritten = DP_SimulationAuxWrite((SIM_DeviceIDType)pDeviceCtx->eDeviceID,
                                                           psWritePacket->uAddress,
                                                           psWritePacket->uWriteDataSize,     
                                                           psWritePacket->puWriteData,
                                                           (eModeType)psWritePacket->eTransactionType);
           
      // Release the acquired lock
      DISP_OSAL_ReleaseLockEvent(pDeviceCtx->hAuxAccessLock);
    }

    // Log the completion for profiling
    DISP_OSAL_EVENTLOG3(DISP_OSAL_EVENT_DISPLAY_WRITE_END, pDeviceCtx->eControllerID,
        pStreamCtx->eMSTStreamId,
        eStatus);
  }
  return eStatus;
}


#ifdef __cplusplus
}
#endif

