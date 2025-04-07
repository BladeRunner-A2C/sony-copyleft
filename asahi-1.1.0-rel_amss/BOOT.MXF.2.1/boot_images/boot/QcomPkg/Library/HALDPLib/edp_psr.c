
/*=====================================================================================================================
 
  File: edp_psr.c
 
  Source file for eDP PSR related functionality 
   
  Copyright (c) 2018-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=======================================================================================================================*/


/*---------------------------------------------------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------------------------------------------------*/
#include "dp_i.h"
#include "hal_dp_phy.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------------------------------------------------
 * Defines
 *-------------------------------------------------------------------------------------------------------------------*/


#define EDP_PSR_INTERRUPTS_ALL                   (HAL_DP_INTR_TYPE_PSR_UPDATE     |\
                                                  HAL_DP_INTR_TYPE_PSR_CAPTURE    |\
                                                  HAL_DP_INTR_TYPE_PSR_EXIT       |\
                                                  HAL_DP_INTR_TYPE_PSR_UPDATE_ERR |\
                                                  HAL_DP_INTR_TYPE_PSR_WAKE_ERR)


#define EDP_PSR_DONE_TIMEOUT_US                   100000        /* How long to wait for PSR entry/exit done            */ 
#define EDP_PSR_DONE_POLL_INTERVAL_US             5000          /* Poll interval while waiting for PSR entry/exit done */
#define EDP_PSR_TPS1_FLUSH_DELAY_US               100           /* Delay to fill PHY's symbol FIFO with TPS1           */


/*---------------------------------------------------------------------------------------------------------------------
 * Private functions 
 *---------------------------------------------------------------------------------------------------------------------*/

//-------------------------------------------------------------------------------------------------
//  eDP_PSR_WaitForInterrupt
//
//  @brief
//      Function blocking waits with timeout until the PSR interrupt passed is received. 
//
//  @params
//      [IN/OUT] pDisplayCtx
//          Pointer to context handle.
//      [IN] eInterrupt
//          Interrupt to wait for
//
//  @return
//      DP_Status 
//-------------------------------------------------------------------------------------------------
//
static DP_Status eDP_PSR_WaitForInterrupt(DP_DeviceCtxType          *pDeviceCtx,
                                          HAL_DP_PSRInterruptType    eInterrupt)
{
  DP_Status       eStatus      = DP_STATUS_FAILED_TIMEOUT;
  volatile uint32 uIntStatus   = HAL_eDP_PSR_Interrupt_Status(pDeviceCtx->eControllerID);
  uint32          uIntsToClear = 0;
  uint32          uPolls       = (EDP_PSR_DONE_TIMEOUT_US / EDP_PSR_DONE_POLL_INTERVAL_US);
  
  while ((0 == (uIntStatus & eInterrupt)) &&
         (uPolls-- > 0))
  {
    DP_OSAL_SleepUs(EDP_PSR_DONE_POLL_INTERVAL_US);
    uIntStatus = HAL_eDP_PSR_Interrupt_Status(pDeviceCtx->eControllerID);

    // Check for any errors
    if (0 != (uIntStatus & HAL_DP_INTR_TYPE_PSR_UPDATE_ERR))
    {
      DP_LOG_MESSAGE_ERROR("PSR Update command is not successfully executed");
      uIntsToClear |= HAL_DP_INTR_TYPE_PSR_UPDATE_ERR;
      break;
    }
    else if (0 != (uIntStatus & HAL_DP_INTR_TYPE_PSR_WAKE_ERR))
    {
      DP_LOG_MESSAGE_ERROR("PSR WAKE signal to the panel is not successfully acknowledged");     
      uIntsToClear |= HAL_DP_INTR_TYPE_PSR_WAKE_ERR;
      break;
    }
  }

  if (0 != (uIntStatus & eInterrupt))
  {  
    uIntsToClear |= (eInterrupt & uIntStatus);    
    eStatus = DP_STATUS_SUCCESS;    
  }
  else
  {
    DP_LOG_MESSAGE_ERROR("eDP_PSR_WaitForDone Timed out waiting for 0x%x done - 0x%x", eInterrupt, uIntStatus);
  }

  // Clear the interrupt
  if (uIntsToClear != 0)
  {
    HAL_eDP_PSR_Interrupt_Clear(pDeviceCtx->eControllerID, uIntsToClear);
  }

  return eStatus;
}



/*---------------------------------------------------------------------------------------------------------------------
 * Public functions 
 *---------------------------------------------------------------------------------------------------------------------*/


//-------------------------------------------------------------------------------------------------
//  eDP_PSR_Init
//
//  @brief
//      Function enables PSR/PSR2 function in the sink and configures the eDP controller. If the function 
//      returns success, it means that the sink & source are ready to process PSR enter/exit requests.
//      NOTE: PSR2 support is not exposed yet.
//
//  @params
//      [IN/OUT] pDisplayCtx
//          Pointer to context handle.
//
//  @return
//      DP_Status 
//-------------------------------------------------------------------------------------------------
//
DP_Status eDP_PSR_Init(DP_DisplayCtxType  *pDisplayCtx)
{
  DP_Status             eStatus = DP_STATUS_SUCCESS;
  DP_DeviceCtxType     *pDeviceCtx;
  DP_StreamCtxType     *pStreamCtx;

  if ((NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx))) || 
      (NULL == (pStreamCtx = DPHOST_GET_STREAM_CTX(pDisplayCtx))))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("eDP_PSR_Init: Unexpected null context.");
  }
  else
  {
    uint32                uModeIndex   = (pStreamCtx->uModeIndex >= MAX_DP_PANEL_MODE) ? 0 : pStreamCtx->uModeIndex;
    DP_PanelInfoType     *psPanelInfo  = &(pStreamCtx->sPanelInfo[uModeIndex]);
    uint32                uBlankLines  = (psPanelInfo->uVsyncBackPorchInLines  + 
                                         psPanelInfo->uVsyncFrontPorchInLines +  
                                         psPanelInfo->uVsyncPulseInLines - 1);
    uint32                uBlankTimeUs = 0;
    bool32                bPSR2        = (DPCD_SPEC_PSR_VERSION_2 == pDeviceCtx->sSinkDPCDCap.sPSRCap.uVersion) ? TRUE : FALSE;
    HAL_DP_PSRConfigType  sHalConfig;  
    DP_PSRCfgType         sConfig;
    
    if (DPCD_SPEC_PSR_VERSION_UNSUPPORTED == pDeviceCtx->sSinkDPCDCap.sPSRCap.uVersion)
    {
      eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;    
      DP_LOG_MESSAGE_WARN("Sink doesn't support PSR feature");
    }
    else
    {
      if ((0 != (uBlankLines + psPanelInfo->uVisibleHeightInPixels)) &&
          (0 != (psPanelInfo->uRefreshRate >> 16)))
      {
        // Refresh rate is in Hz (Q16.16 format) - so we multiply by 10^6 to get blanking time in Us
        uBlankTimeUs =  (uBlankLines * (1000000 / (psPanelInfo->uRefreshRate >> 16))) / (uBlankLines + psPanelInfo->uVisibleHeightInPixels);
      }
    
      /* Program the PSR configuration in the sink */
      
      DP_OSAL_MemSet(&sConfig, 0, sizeof(DP_PSRCfgType));
    
      // Mainlink can shut down for PSR/PSR2
      sConfig.bMainLinkActive      = FALSE;
      // CRC verification at sink only for PSR2
      sConfig.bVerifyCRC           = (bPSR2) ? TRUE : FALSE;
      // If PSR set up time is more than blanking time, then indicate that sink should capture the second frame
      sConfig.bCaptureSecondFrame  = (uBlankTimeUs < pDeviceCtx->sSinkDPCDCap.sPSRCap.uSetupTimeUs);
    
      eStatus = DP_WriteSinkPSRConfiguration(pDisplayCtx, &sConfig);
      if (DP_STATUS_SUCCESS != eStatus)
      {
        DP_LOG_MESSAGE_WARN("Failed to program sink device PSR configuration");
      }
      else
      {
        /* Program the PSR configuration in the source (eDP controller) */
      
        DP_OSAL_MemSet(&sHalConfig, 0, sizeof(HAL_DP_PSRConfigType));
        
        // PSR2 implementation is without AUX_FRAME_SYNC (OS doesnt support selective frame update)
        sHalConfig.ePSRMode            = (bPSR2) ? HAL_DP_PSR_MODE_ENABLE_PSR2 : HAL_DP_PSR_MODE_ENABLE_PSR;
        sHalConfig.bMainLinkActive     = sConfig.bMainLinkActive;
        sHalConfig.bVerifyCRC          = sConfig.bVerifyCRC;
        sHalConfig.bCaptureSecondFrame = sConfig.bCaptureSecondFrame;
        sHalConfig.bTrainingOnExit     = TRUE;

        if (DP_LINK_TRAINING_TYPE_NO_TRAINING == pDeviceCtx->sSinkDPCDCap.sPSRCap.eLinkTrainingonExit)
        {
          sHalConfig.bTrainingOnExit = FALSE;
        }
      
        HAL_eDP_PSR_Config(pDeviceCtx->eControllerID, &sHalConfig);
       
        HAL_eDP_PSR_VSC_Setup(pDeviceCtx->eControllerID);
    
        /* Enable PSR in sink */
        
        sConfig.ePSRMode = (bPSR2) ? DP_PSR_MODE_ENABLE_PSR2 : DP_PSR_MODE_ENABLE_PSR;

        eStatus = DP_WriteSinkPSRConfiguration(pDisplayCtx, &sConfig);

#ifdef PSR2_SUPPORTED
        if (TRUE == pDeviceCtx->sSinkDPCDCap.sALPMCap.bALPMCapable)
        {
          // Enable ALPM on sink
          DP_WriteSinkALPMConfig(pDisplayCtx, TRUE);
        }
#endif // PSR2_SUPPORTED        

        TraceInfo(QdiTraceDP, "DP%i: PSR enabled on source and sink, verify CRC: %i, second frame:%i, link training at exit: %i, status: 0x%x",
                  pStreamCtx->eDisplayID,
                  sHalConfig.bVerifyCRC,
                  sHalConfig.bCaptureSecondFrame,
                  sHalConfig.bTrainingOnExit,
                  eStatus);
      }
    }
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  eDP_PSR_Request
//
//  @brief
//      Function to set PSR state of source and sink
//
//
//  @params
//      [IN/OUT] pDisplayCtx
//          Pointer to context handle.
//      [IN] ePSRRequest
//          Type of PSR Request
//
//  @return
//      DP_Status 
//-------------------------------------------------------------------------------------------------
//
DP_Status eDP_PSR_Request(DP_DisplayCtxType  *pDisplayCtx,  
                          DP_PSRRequestType   ePSRRequest)
{
  DP_Status          eStatus = DP_STATUS_SUCCESS;  
  DP_DeviceCtxType  *pDeviceCtx;

  if (NULL == (pDeviceCtx = DPHOST_GET_DEVICE_CTX(pDisplayCtx)))
  {
    eStatus = DP_STATUS_FAILED_INVALID_INPUT_PARAMETER;
    DP_LOG_MESSAGE_ERROR("eDP_PSR_Request: Unexpected null context.");
  }
  else
  {
    // Cache the last requested state
    pDeviceCtx->ePSRState = ePSRRequest;

    switch (ePSRRequest)
    {
      case DP_PSR_REQUEST_ENABLE:
      {
        eStatus = eDP_PSR_Init(pDisplayCtx);      
        break;
      }  
    
      case DP_PSR_REQUEST_ENTER:
      {
        // Clear any stale interrupts and issue Enter command
        HAL_eDP_PSR_Interrupt_Clear(pDeviceCtx->eControllerID, EDP_PSR_INTERRUPTS_ALL);
        
        // Issue Enter Command
        HAL_eDP_PSR_Command(pDeviceCtx->eControllerID, HAL_DP_PSR_CMD_ENTER);
    
        break;
      }
      
      case DP_PSR_REQUEST_WAIT_FOR_ENTER_DONE:
      {
        // Wait for completion so that main link can be turned off  
        if (DP_STATUS_SUCCESS == (eStatus = eDP_PSR_WaitForInterrupt(pDeviceCtx, HAL_DP_INTR_TYPE_PSR_UPDATE)))
        {         
          /*
           * HW will automatically put the PHY into sleep mode on PSR entry
           * PLL power-down/suspend would be here if implemented in the future
           */     
        }
        else
        {        
          // Return failure - Upper layer will retry the PSR entry
          DP_LOG_MESSAGE_ERROR("Failed to enter PSR");
        }

        TraceVerb(QdiTraceDP, "DP%i: PSR enter (update done), status: 0x%x", 
                  pDeviceCtx->eDisplayID, eStatus);
  
        /* Diag level 1 - Source/Sink CRC  */
        if ((DP_DIAG_LEVEL_1         <= pDeviceCtx->eDiagLevel) &&
            (DPCD_SPEC_PSR_VERSION_1 == pDeviceCtx->sSinkDPCDCap.sPSRCap.uVersion))
        {
          uint16 uControllerCRC[3]; // CRC is split in R, G and B components
              
          // Read sink CRC
          DP_ReadSinkCRC(pDisplayCtx);

          // Read the source CRC 
          if (HAL_MDSS_STATUS_SUCCESS == HAL_DP_CRC_Capture(pDeviceCtx->eControllerID, &uControllerCRC[0], &uControllerCRC[1], &uControllerCRC[2]))
          {
            TraceInfo(QdiTraceDiag, "Diag (EDP%i): Source CRC status : 0x%x,0x%x,0x%x",
                                     pDeviceCtx->eControllerID, 
                                     uControllerCRC[0], 
                                     uControllerCRC[1], 
                                     uControllerCRC[2]);
          }
        }
        
        // Diag level 2 - Sink PSR Status 
        if ((DP_DIAG_LEVEL_2         <= pDeviceCtx->eDiagLevel) ||
           ((DP_DIAG_LEVEL_1         <= pDeviceCtx->eDiagLevel) && 
            (DPCD_SPEC_PSR_VERSION_2 == pDeviceCtx->sSinkDPCDCap.sPSRCap.uVersion)))
        {
          // Read and log PSR status to WPP
          DP_ReadSinkPSRStatus(pDisplayCtx);
        }

        break;
      }
      
      case DP_PSR_REQUEST_EXIT:
      {
        // Clear any stale interrupts
        HAL_eDP_PSR_Interrupt_Clear(pDeviceCtx->eControllerID, EDP_PSR_INTERRUPTS_ALL);
    
        // Setup TPS1 before disabling mainlink, so that at PSR exit TPS1 is sent out during aux wake.
        HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_SEND_PATTERN1);
        
        // Wait to allow TPS1 symbols to fill PHY's buffer.
        DP_OSAL_SleepUs(EDP_PSR_TPS1_FLUSH_DELAY_US);
        
        // Clear link state - Controller won't transition to READY_FOR_VIDEO unless link state is cleared.
        HAL_DP_SetLinkState(pDeviceCtx->eControllerID, HAL_DP_LINKCOMMAND_TYPE_NONE);

        // Issue Exit Command      
        HAL_eDP_PSR_Command(pDeviceCtx->eControllerID, HAL_DP_PSR_CMD_EXIT);

        /*
         * HW will automatically send AUX wake command & take the PHY out of sleep mode
         */
       
        break;
      }
    
      case DP_PSR_REQUEST_WAIT_FOR_EXIT_DONE:
      {
        eStatus = eDP_PSR_WaitForInterrupt(pDeviceCtx, HAL_DP_INTR_TYPE_PSR_EXIT);

        TraceVerb(QdiTraceDP, "DP%i: PSR exit (exit done), status: 0x%x", 
                  pDeviceCtx->eDisplayID, eStatus);        

        // Diag level 1 - Source/Sink CRC and Sink Link Status
        if (pDeviceCtx->eDiagLevel >= DP_DIAG_LEVEL_2)
        {
          DP_DPCDSinkStatusType sSinkDPCDStatus; 
        
          // Read sink lane status after PSR exit (Hardware initates training on PSR exit)
          DP_ReadSinkDPCDStatus(pDisplayCtx, &sSinkDPCDStatus, DP_AUX_TRANSACTION_AUX_WAIT_STALL_FLAG);

          // Read sink's PSR status 
          DP_ReadSinkPSRStatus(pDisplayCtx);
        }

        break;
      }
    
      case DP_PSR_REQUEST_SETUP_TX_FOR_VIDEO:
      {
        if (DP_STATUS_SUCCESS == eStatus)
        {
          if (DP_STATUS_SUCCESS != (eStatus =  DP_WaitForLinkStatus(pDisplayCtx, HAL_DP_LINKSTATUS_TYPE_READY_FOR_VIDEO)))
          {
            DP_LOG_MESSAGE_ERROR("PSR exit: Failed to start video");
          }
        }

        TraceVerb(QdiTraceDP, "DP%i: PSR exit (wait for video done), status: 0x%x", 
          pDeviceCtx->eDisplayID, eStatus);

        break;
      }

      default:
      {
        DP_LOG_MESSAGE_ERROR("eDP_PSR_SetState: Invalid request %d", ePSRRequest);
        eStatus = DP_STATUS_FAILED_NOT_SUPPORTED;
        break;
      }
    }
  }

  return eStatus;
}

#ifdef __cplusplus
}
#endif
