/*=============================================================================
 
  File: hal_edp_psr.c
 
  Source file for eDP PSR hardware functionality 
   
  Copyright (c) 2018-2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/


/*------------------------------------------------------------------------------
 * Include Files
 *----------------------------------------------------------------------------*/
#include "hal_dp_i.h"

#ifdef __cplusplus
extern "C" {
#endif


/*---------------------------------------------------------------------------------------------------------------------
 * Private defines 
 *---------------------------------------------------------------------------------------------------------------------*/

// Fast train time in aux clock cycles. Default: 2.5 ms (19200 cycles_per_ms * 2.5 ms = 48000 cycles)
#define HAL_EDP_DEFAULT_FAST_TRAIN_CYCLES                          48000    

/*---------------------------------------------------------------------------------------------------------------------
 * Public functions 
 *---------------------------------------------------------------------------------------------------------------------*/


//-------------------------------------------------------------------------------------------------
//  HAL_eDP_PSR_VSC_Setup
//
//  @brief
//      Function configure VSC SDP settings for PSR on the eDP controller
//      It is the callers responsibility to set appropriate Interface Flush flags so that these settings are applied
//
//  @params
//      [IN] eControllerId
//          Controller ID.
//
//  @return
//      None 
//-------------------------------------------------------------------------------------------------
//
void HAL_eDP_PSR_VSC_Setup(DP_ControllerIDType eControllerId)
{
  uintPtr uOffset  = 0;
  uint32  uRegVal  = 0;

  uRegVal = in_dword(uOffset + HWIO_DPTX_2_MAINLINK_LEVELS_2_ADDR);
  uRegVal |= HWIO_DPTX_2_MAINLINK_LEVELS_2_MSA_TO_VSC_DELAY_MODE_BMSK;
  out_dword(uOffset + HWIO_DPTX_2_MAINLINK_LEVELS_2_ADDR, uRegVal);

  uRegVal = in_dword(uOffset + HWIO_DPTX_2_SDP_CFG2_ADDR);
  uRegVal &= ~HWIO_DPTX_2_SDP_CFG2_VSC_SDPFSM_SRC_BMSK;
  uRegVal |= HWIO_DPTX_2_SDP_CFG2_PSR_VSC_SDPSIZE_BMSK;              // 32 bytes
  out_dword(uOffset + HWIO_DPTX_2_SDP_CFG2_ADDR, uRegVal);

  /* Enable VSC SDP */
  uRegVal = in_dword(uOffset + HWIO_DPTX_2_CONFIGURATION_CTRL_ADDR );
  uRegVal = HWIO_OUT_FLD( uRegVal, DPTX_2_CONFIGURATION_CTRL, SEND_VSC, 1);
  out_dword(uOffset + HWIO_DPTX_2_CONFIGURATION_CTRL_ADDR, uRegVal );
}

//-------------------------------------------------------------------------------------------------
//  HAL_eDP_PSR_Config
//
//  @brief
//      Function configures PSR on the controller side
//
//  @params
//      [IN] eControllerId
//          Controller ID.
//      [IN] pConfig
//          config to be applied
//
//  @return
//      None 
//-------------------------------------------------------------------------------------------------
//
void HAL_eDP_PSR_Config(DP_ControllerIDType  eControllerId, HAL_DP_PSRConfigType *pConfig)
{
  uint32   uRegValue = 0;
  uintPtr  uOffset   = 0;

  // Clear any stale command before init
  out_dword(uOffset + HWIO_DPTX_2_PSR_CMD_ADDR, 0);

  uRegValue = in_dword(uOffset + HWIO_DPTX_2_PSR_CONFIG_ADDR);  
  uRegValue = HWIO_OUT_FLD(uRegValue, DPTX_2_PSR_CONFIG, PSR_MODE,    pConfig->ePSRMode);
  uRegValue = HWIO_OUT_FLD(uRegValue, DPTX_2_PSR_CONFIG, POWER_STATE, (pConfig->bMainLinkActive) ? 1 : 0);
  uRegValue = HWIO_OUT_FLD(uRegValue, DPTX_2_PSR_CONFIG, SEND_CRC,    (pConfig->bVerifyCRC) ? 1 : 0);
  uRegValue = HWIO_OUT_FLD(uRegValue, DPTX_2_PSR_CONFIG, FRAME_CAPTURE_INDICATION, (pConfig->bCaptureSecondFrame) ? 1 : 0);
  out_dword(uOffset + HWIO_DPTX_2_PSR_CONFIG_ADDR, uRegValue);

  // Setup Fast Link training on PSR Exit
  // FAST_TRAIN_PATTERNS is set to 1 to enable TPS1 patterns
  uRegValue = in_dword(uOffset + HWIO_DPTX_2_EXIT_CONFIG_ADDR);
  uRegValue = HWIO_OUT_FLD(uRegValue, DPTX_2_EXIT_CONFIG, FAST_TRAIN_PATTERNS, (pConfig->bTrainingOnExit) ? 1 : 0);
  uRegValue = HWIO_OUT_FLD(uRegValue, DPTX_2_EXIT_CONFIG, FAST_TRAIN_CYCLES, HAL_EDP_DEFAULT_FAST_TRAIN_CYCLES);

  out_dword(uOffset + HWIO_DPTX_2_EXIT_CONFIG_ADDR, uRegValue);
}

//-------------------------------------------------------------------------------------------------
//  HAL_eDP_PSR_Command
//
//  @brief
//      Function to execute PSR commands (enter, exit, etc.)
//
//  @params
//      [IN] eControllerId
//          DP controller ID.
//      [IN] eCommand
//          PSR command.
//
//  @return
//      None 
//-------------------------------------------------------------------------------------------------
//
void HAL_eDP_PSR_Command(DP_ControllerIDType  eControllerId, HAL_DP_PSR_CmdType eCommand)
{
  uintPtr uOffset  = 0;
  
  out_dword(uOffset + HWIO_DPTX_2_PSR_CMD_ADDR, eCommand);
}

//-------------------------------------------------------------------------------------------------
//  HAL_eDP_PSR_Interrupt_Status
//
//  @brief
//      Function to get PSR interrupt status
//
//  @params
//      [IN] eControllerId
//          DP controller ID.
//
//  @return
//      Bit-field of interrupts that fired 
//-------------------------------------------------------------------------------------------------
//
uint32 HAL_eDP_PSR_Interrupt_Status(DP_ControllerIDType  eControllerId)
{
  uintPtr uOffset        = 0;
  uint32  uHalInterrupt  = 0;  
  uint32  uRegValue      = in_dword(uOffset + HWIO_DPTX_2_INTERRUPT_STATUS_4_ADDR);

  if (uRegValue & HWIO_DPTX_2_INTERRUPT_STATUS_4_PSR_UPDATE_INT_BMSK )
  {
    uHalInterrupt |= HAL_DP_INTR_TYPE_PSR_UPDATE;
  }

  if (uRegValue & HWIO_DPTX_2_INTERRUPT_STATUS_4_PSR_CAPTURE_INT_BMSK )
  {
    uHalInterrupt |= HAL_DP_INTR_TYPE_PSR_CAPTURE;
  }

  if (uRegValue & HWIO_DPTX_2_INTERRUPT_STATUS_4_PSR_EXIT_INT_BMSK )
  {
    uHalInterrupt |= HAL_DP_INTR_TYPE_PSR_EXIT;
  }

  if (uRegValue & HWIO_DPTX_2_INTERRUPT_STATUS_4_PSR_UPDATE_ERROR_INT_BMSK )
  {
    uHalInterrupt |= HAL_DP_INTR_TYPE_PSR_UPDATE_ERR;
  }    

  if (uRegValue & HWIO_DPTX_2_INTERRUPT_STATUS_4_PSR_WAKE_ERROR_INT_BMSK )
  {
    uHalInterrupt |= HAL_DP_INTR_TYPE_PSR_WAKE_ERR;
  }    

  return uHalInterrupt;
}

//-------------------------------------------------------------------------------------------------
//  HAL_eDP_PSR_Interrupt_Clear
//
//  @brief
//      Function to clear PSR interrupts
//
//  @params
//      [IN] eControllerId
//          DP controller ID
//      [IN] uInterrupts
//          Bit-field of interrupts to be cleared
//
//
//  @return
//      None
//-------------------------------------------------------------------------------------------------
//
void HAL_eDP_PSR_Interrupt_Clear(DP_ControllerIDType  eControllerId, uint32 uInterrupts)
{
  uint32 uRegValue  = in_dword(HWIO_DPTX_2_INTERRUPT_STATUS_4_ADDR);
  
  if (uInterrupts & HAL_DP_INTR_TYPE_PSR_UPDATE)
  {
    uRegValue = HWIO_OUT_FLD(uRegValue, DPTX_2_INTERRUPT_STATUS_4, PSR_UPDATE_ACK, 1);
  }

  if (uInterrupts & HAL_DP_INTR_TYPE_PSR_CAPTURE)
  {
    uRegValue = HWIO_OUT_FLD(uRegValue, DPTX_2_INTERRUPT_STATUS_4, PSR_CAPTURE_ACK, 1);
  }

  if (uInterrupts & HAL_DP_INTR_TYPE_PSR_EXIT)
  {
    uRegValue = HWIO_OUT_FLD(uRegValue, DPTX_2_INTERRUPT_STATUS_4, PSR_EXIT_ACK, 1);
  }

  if (uInterrupts & HAL_DP_INTR_TYPE_PSR_UPDATE_ERR)
  {
    uRegValue = HWIO_OUT_FLD(uRegValue, DPTX_2_INTERRUPT_STATUS_4, PSR_UPDATE_ERROR_ACK, 1);
  }

  if (uInterrupts & HAL_DP_INTR_TYPE_PSR_WAKE_ERR)
  {
    uRegValue = HWIO_OUT_FLD(uRegValue, DPTX_2_INTERRUPT_STATUS_4, PSR_WAKE_ERROR_ACK, 1);
  }

  out_dword(HWIO_DPTX_2_INTERRUPT_STATUS_4_ADDR, uRegValue);
}

#ifdef __cplusplus
}
#endif
