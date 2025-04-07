#ifndef _DP_AUDIO_H_
#define _DP_AUDIO_H_
/*! \file */
/*============================================================================================
  Copyright (c) 2019-2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================================*/

/*********************************************************************************************
*
** FUNCTION: DP_Audio_FilterModes()
*/
/*!
* \DESCRIPTION
*     Filter audio modes based on the current link configuration
*
* \param [in]   pDisplayCtx        - Pointer to display context
* \param [in]   psPanelInfo        - Pointer to panel parameters for the active display mode
* \param [in]   pHALRgConfig       - Pointer to the MST RG configuration
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_Audio_FilterModes(DP_DisplayCtxType    *pDisplayCtx,
                                DP_PanelInfoType     *psPanelInfo,
                                HAL_DP_RGConfigType  *pHALRgConfig);

#endif //_DP_AUDIO_H_
