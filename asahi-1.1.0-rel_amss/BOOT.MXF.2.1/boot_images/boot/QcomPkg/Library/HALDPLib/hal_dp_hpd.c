/*=============================================================================
 
  File: hal_dp_hpd.c
 
  Source file for DP HPD hardware functionality 
   
  Copyright (c) 2016-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* -----------------------------------------------------------------------
** Includes
** ----------------------------------------------------------------------- */
#include "hal_dp_i.h"


/* -----------------------------------------------------------------------
** Local Types
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Static Variable
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Private Functions
** ----------------------------------------------------------------------- */


/****************************************************************************
*
** FUNCTION: HAL_DP_HPD_Engine_Init()
*/
/*!
* \brief
*   The \b Initialize counters for HPD  
*
* \param [in]   eControllerId   - DP core ID
*
* \retval void
*
****************************************************************************/
static void HAL_DP_HPD_Engine_Init(DP_ControllerIDType eControllerId)
{
  /* Setup reference timer to generate 1 strobe per Us (from 19.2 MHz source) */
  uint32 uRefTime = (HWIO_DPTX_0_DP_HPD_REFTIMER_REFTIMER_ENABLE_BMSK | 0x13);
  uintPtr uOffset = HAL_DP_GetRegBaseOffset(eControllerId);

  /* Setup the reference timer */
  out_dword(uOffset + HWIO_DPTX_0_DP_HPD_REFTIMER_ADDR, uRefTime);

  /*
   * For detection thresholds, we rely on the following Hardware reset values :
   *     HPD_CONNECT_TIME = 100 ms,  HPD_GLITCH_TIME = 0.25ms
   *     IRQ_HPD_MAX_TIME = 2 ms,    HPD_DISCONNECT_TIME = 100ms
   */

  /* Clear any stale interrupt bits */
  out_dword(uOffset + HWIO_DPTX_0_DP_HPD_INT_ACK_ADDR, 0xF);
}



/* -----------------------------------------------------------------------
** Public Functions
** ----------------------------------------------------------------------- */


/****************************************************************************
*
** FUNCTION: HAL_DP_HPD_Engine_Enable()
*/
/*!
* \brief
*   The \b Enable Hot Plug Detect functionality 
*
* \param [in] eControllerId   - DP core ID
* \param [in] psConfig        - HPD configuration
*
* \retval void
*
****************************************************************************/
void HAL_DP_HPD_Engine_Enable(DP_ControllerIDType   eControllerId,
                              HAL_DP_HPDConfigType *psConfig)
{
  uint32             uValue       = 0;
  uintPtr            uOffset      = HAL_DP_GetRegBaseOffset(eControllerId);
  uint32             uRegVal;
  HAL_HW_VersionType sDPHwVersion = { 0 };

  if (TRUE == psConfig->bEnable)
  {
    /* Setup HPD timer and detection thresholds */
    HAL_DP_HPD_Engine_Init(eControllerId);

    uValue |= HWIO_DPTX_0_DP_HPD_CTRL_DP_HPD_EN_BMSK;
  }

  if (TRUE == psConfig->bActiveLow)
  {
    uValue |= HWIO_DPTX_0_DP_HPD_CTRL_HPD_PIN_POLARITY_BMSK;
  }

  /* Enable/Disable HPD hardware */
  out_dword(uOffset + HWIO_DPTX_0_DP_HPD_CTRL_ADDR, uValue);

  uRegVal = in_dword(HWIO_MDP_DP_HPD_SELECT_ADDR);

  HAL_DP_ReadVersionInfo(eControllerId, &sDPHwVersion);

  if (DP_DEVICE_MODETYPE_EDP != psConfig->eDeviceDPMode)
  {
	  /* Route the HPD line based on DP device and controller */
    switch (eControllerId)
    {
    case DP_CONTROLLER_ID_DP_0:
      uRegVal = HWIO_OUT_FLD(uRegVal, MDP_DP_HPD_SELECT, DP0_SEL, 0);
      break;
    case DP_CONTROLLER_ID_DP_1:
      uRegVal = HWIO_OUT_FLD(uRegVal, MDP_DP_HPD_SELECT, DP1_SEL, 1);
      break;
    case DP_CONTROLLER_ID_DP_2:
      uRegVal = HWIO_OUT_FLD(uRegVal, MDP_DP_HPD_SELECT, DP2_SEL, 2);
      break;
    case DP_CONTROLLER_ID_DP_3:
      uRegVal = HWIO_OUT_FLD(uRegVal, MDP_DP_HPD_SELECT, DP3_SEL, 3);
      break;
    default:
      break;
    }
  }

  out_dword(HWIO_MDP_DP_HPD_SELECT_ADDR, uRegVal);
}

/****************************************************************************
*
** FUNCTION: HAL_DP_HPD_PanelPlugged()
*/
/*!
* \brief
*   The \b Checks whether panel is plugged in
*
* \param [in]   eControllerId   - DP core ID
*
* \retval DP_HPD_StatusType for connection
*
****************************************************************************/
DP_HPD_StatusType HAL_DP_HPD_PanelPlugged(DP_ControllerIDType eControllerId)
{
  DP_HPD_StatusType eConnected  = DP_HPD_STATUS_DISCONNECTED;
  uintPtr           uOffset     = HAL_DP_GetRegBaseOffset(eControllerId);
  uint32            uIntStatus  = in_dword(uOffset + HWIO_DPTX_0_DP_HPD_INT_STATUS_ADDR);
  uint32            uHPDState   = HWIO_GETVAL(DPTX_0_DP_HPD_INT_STATUS, uIntStatus, DP_HPD_STATE_STATUS);

  static const DP_HPD_StatusType ConnectionMapping[HWIO_DP_HPD_STATE_STATUS_MAX] =
  {
    DP_HPD_STATUS_DISCONNECTED,
    DP_HPD_STATUS_CONNECT_PENDING,
    DP_HPD_STATUS_CONNECTED,
    DP_HPD_STATUS_HPD_IO_GLITH_COUNT,
    DP_HPD_STATUS_IRQ_HPD_PULSE_COUNT,
    DP_HPD_STATUS_HPD_REPLUG_COUNT,
  };

  if (uHPDState < DP_HPD_STATUS_MAX)
  {
    eConnected = ConnectionMapping[uHPDState];
  }

  return eConnected;
}

#ifdef __cplusplus
}
#endif

