/*
===========================================================================

FILE:         hal_mdp_source.h

===========================================================================
  Copyright (c) 2010-2021 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
===========================================================================
*/

/* -----------------------------------------------------------------------
 * Includes
 * ----------------------------------------------------------------------- */

#include "hal_mdp_i.h"
#include "hal_mdp.h"


#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
*
** FUNCTION: HAL_MDP_SSPP_ScalerLUTConfig()
*/
/*!
* \brief
*     Configures the SSPP scaler LUT
*
* \param [in] eSourcePipe           - Source Pipe ID
* \param [in] psScalarConfig        - QSEED LUT configuration
*
* \retval NONE
*
****************************************************************************/
void HAL_MDP_SSPP_ScalerLUTConfig(HAL_MDP_SourcePipeId      eSourcePipe, 
                                  HAL_MDP_ScalarConfigType *psScalarConfig)
{
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_SSPP_ScalerDEConfig()
*/
/*!
* \brief
*     Program  scaler DE registers
*
* \param [in]   eSourcePipe             - Source pipe id
* \param [in]   eLayerType              - Layer Type, Only RGB, VG and DMA are supported
* \param [in]   psScalarConfig          - Scalar configuration
*
* \retval void
*
****************************************************************************/
void HAL_MDP_SSPP_ScalerDEConfig(HAL_MDP_SourcePipeId             eSourcePipe,
                                 HAL_MDP_LayerType                eLayerType,
                                 HAL_MDP_ScalarConfigType        *psScalarConfig)
{
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_SSPP_ScalerConfig()
*/
/*!
* \brief
*     Program  scaler registers
*
* \param [in]   eSourcePipe             - Source pipe id
* \param [in]   eLayerType              - Layer Type, Only RGB, VG and DMA are supported
* \param [in]   psScalarConfig          - Scalar configuration
*
* \retval void
*
****************************************************************************/
void HAL_MDP_SSPP_ScalerConfig(HAL_MDP_SourcePipeId             eSourcePipe,
                               HAL_MDP_LayerType                eLayerType,
                               HAL_MDP_ScalarConfigType        *psScalarConfig)
{
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_SSPP_ScalerLUTConfig()
*/
/*!
* \brief
*     Configures the DSPP scaler LUT
*
* \param [in] eDestPipe             - Destination Pipe ID
* \param [in] psScalarConfig        - QSEED LUT configuration
*
* \retval NONE
*
****************************************************************************/
void HAL_MDP_DSPP_ScalerLUTConfig(HAL_MDP_DestinationPipeId   eDestPipe, 
                                  HAL_MDP_ScalarConfigType   *psScalarConfig)
{
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSPP_ScalerDEConfig()
*/
/*!
* \brief
*     Program  destination scaler DE registers
*     populated from HAL_MDP_UTILITY_CalcDisplayConfig()
*
* \param [in]   eDestPipe               - Destination pipe id
* \param [in]   psScalarConfig          - Values populated from 
*                                         HAL_MDP_UTILITY_CalcDisplayConfig()
*
* \retval void
*
****************************************************************************/
void HAL_MDP_DSPP_ScalerDEConfig(HAL_MDP_DestinationPipeId        eDestPipe,
                                 HAL_MDP_ScalarConfigType        *psScalarConfig)
{
}

/****************************************************************************
*
** FUNCTION: HAL_MDP_DSPP_ScalerConfig()
*/
/*!
* \brief
*     Program  scaler registers
*
* \param [in]   eDestPipe               - Destination pipe id
* \param [in]   psScalarConfig          - Scalar configuration
*
* \retval void
*
****************************************************************************/
void HAL_MDP_DSPP_ScalerConfig(HAL_MDP_DestinationPipeId        eDestPipe,
                               HAL_MDP_ScalarConfigType        *psScalarConfig)
{
}


#ifdef __cplusplus
}
#endif
