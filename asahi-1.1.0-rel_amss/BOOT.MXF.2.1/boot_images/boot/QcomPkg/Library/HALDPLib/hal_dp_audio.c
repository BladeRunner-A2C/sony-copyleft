/*=============================================================================

File: hal_dp_audio.c

Source file for DP audio controller hardware functionality

Copyright (c) 2018-2022 Qualcomm Technologies, Inc.
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
  uintPtr uOffset         = HAL_DP_GetRegBaseOffset(eControllerId);

  uint32 ssc_maud[]       = { 0x04000, 0x04000, 0x00700, 0x00700, 0x02000, 0x02000 };
  uint32 ssc_naud[]       = { 0x2773B, 0x41C0D, 0x03219, 0x0537F, 0x0D269, 0x15EAF };

  uint32 non_ssc_maud[]   = { 0x00400, 0x00400, 0x00310, 0x00310, 0x00200, 0x00200 };
  uint32 non_ssc_naud[]   = { 0x0278D, 0x041EB, 0x015F9, 0x0249F, 0x00D2F, 0x015F9 };

  uint32 *ptr_maud        = NULL;
  uint32 *ptr_naud        = NULL;

  uint32 uLength          = 0;

  if (bSSCMode != FALSE)
  {
    ptr_maud = ssc_maud;
    ptr_naud = ssc_naud;

    uLength  = sizeof(ssc_maud) / sizeof(ssc_maud[0]);
  }
  else
  {
    ptr_maud = non_ssc_maud;
    ptr_naud = non_ssc_naud;

    uLength  = sizeof(non_ssc_maud) / sizeof(non_ssc_maud[0]);
  }

  /* Program AUDIO_TIMING_MAUD_RBR/HBR_32/44/48 registers */
  for (uint32 uIndex = 0; uIndex < uLength; uIndex++)
  {
    out_dword((uOffset + HWIO_DPTX_0_AUDIO_TIMING_MAUD_RBR_32_ADDR) + (uIndex * sizeof(uint32)), ptr_maud[uIndex]);
  }

  /* Program AUDIO_TIMING_NAUD_RBR/HBR_32/44/48 registers */
  for (uint32 uIndex = 0; uIndex < uLength; uIndex++)
  {
    out_dword((uOffset + HWIO_DPTX_0_AUDIO_TIMING_NAUD_RBR_32_ADDR) + (uIndex * sizeof(uint32)), ptr_naud[uIndex]);
  }
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

