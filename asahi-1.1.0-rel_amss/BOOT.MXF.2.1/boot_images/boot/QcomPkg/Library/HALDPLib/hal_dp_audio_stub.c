/*=============================================================================

File: hal_dp_audio_stub.c

Source file for DP audio controller stubs

Copyright (c) 2023 Qualcomm Technologies, Inc.
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

/*------------------------------------------------------------------------------
* Private Functions
*----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
* Public Functions
*----------------------------------------------------------------------------*/

/****************************************************************************
*
** FUNCTION: HAL_DP_ConfigAudioTiming()
*/
/*!
* \brief
*     Configure the AUDIO_TIMING (Maud and Naud) Registers
*
* \param [in] eControllerId         - DP core ID
* \param [in] bSSCMode              - Status of SSC mode
*
****************************************************************************/
void HAL_DP_ConfigAudioTiming(DP_ControllerIDType eControllerId, bool32 bSSCMode)
{
}

/****************************************************************************
*
** FUNCTION: HAL_DP_Audio_Enable()
*/
/*!
* \brief
*     Enable/Disable audio engine
*
* \param [in] eControllerId         - DP core ID
* \param [in] bEnable               - Enable/disable audio engine
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_Audio_Enable(DP_ControllerIDType eControllerId,
                                       bool32              bEnable)
{
  return HAL_MDSS_STATUS_SUCCESS;
}

/****************************************************************************
*
** FUNCTION: HAL_DP_AudioSetup()
*/
/*!
* \brief
*     Configure DP audio engine
*
* \param [in] eControllerId         - DP core ID
* \param [in] psAudioConfig         - Audio engine configure info
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_AudioSetup(DP_ControllerIDType     eControllerId,
                                     HAL_DP_AudioConfigType *psAudioConfig)
{
  return HAL_MDSS_STATUS_SUCCESS;
}


#ifdef __cplusplus
}
#endif

