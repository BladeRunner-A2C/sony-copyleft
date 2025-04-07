/*=============================================================================================
  Copyright (c) 2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------------------------*/
#include "dp_i.h"
#include "dp_audio.h"

/*---------------------------------------------------------------------------------------------
 * Public Functions
 *-------------------------------------------------------------------------------------------*/

/**********************************************************************************************
*
** FUNCTION: DP_Audio_FilterModes()
*/
/*!
* \DESCRIPTION
*     Filter audio modes based on the current link configuration
*
* \param [in]   pDisplayCtx        - Pointer to display context
* \param [in]   psPanelInfo        - Pointer to panel parameters for current display mode
* \param [in]   pHALRgConfig       - Pointer to the current MST RG configuration
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_Audio_FilterModes(DP_DisplayCtxType    *pDisplayCtx,
                                DP_PanelInfoType     *psPanelInfo,
                                HAL_DP_RGConfigType  *pHALRgConfig)
{
    DP_Status            eStatus = DP_STATUS_SUCCESS;
    return eStatus;
}

#ifdef __cplusplus
}
#endif

