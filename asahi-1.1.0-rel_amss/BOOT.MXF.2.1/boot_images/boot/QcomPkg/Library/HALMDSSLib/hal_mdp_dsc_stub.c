/*! \file */

/*
===========================================================================

FILE:         hal_mdp_dsc_stub.c

DESCRIPTION:  This file contains Display Stream Compression (DSC) stubs

===========================================================================
===========================================================================
Copyright (c) 2023 Qualcomm Technologies, Inc.
All Rights Reserved.
Qualcomm Technologies Proprietary and Confidential.
===========================================================================
*/

/*------------------------------------------------------------------------------
 * Include Files
 *----------------------------------------------------------------------------*/
#include "hal_mdp_i.h"
#include "hal_mdp_dsc.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_Setup()
*/
/*!
* \brief
*     Configures the control/data flow for the DSC encoder modules and also
*     configured the encoder configuration parameters to compress the pixel data
*
* \param [in] eDSCId    - none, 0, 1, 2 etc.
* \param [in] pDSCConfig         - Basic configuration parameters for DSC encoder
* \param [in] uFlags             - Reserved
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_MDP_DSC_Setup(HAL_MDP_DSCId          eDSCId,
                                     HAL_MDP_DSCInfoType   *pDSCInfo,
                                     uint32                 uFlags)
{
   HAL_MDSS_ErrorType   eStatus        = HAL_MDSS_STATUS_SUCCESS;

   return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSC_GetPropery()
*/
/*!
* \brief
*     Used to extract the various types of information from DSC encoder module
*
* \param [in]     eDSCId             - none, 0, 1, 2 etc.
* \param [in/out] pDSCInfo           - Input information to extract the required data and
*                                      Output information prepared by HAL driver as response to 
*                                      the requested information.
* \param [in]     uFlags             - Reserved
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_MDP_DSC_GetPropery(HAL_MDP_DSCId          eDSCId,
                                          HAL_MDP_DSCInfoType   *pDSCInfo,
                                          uint32                 uFlags)
{
   HAL_MDSS_ErrorType             eStatus       = HAL_MDSS_STATUS_SUCCESS;

   return eStatus;
}



#ifdef __cplusplus
}
#endif
