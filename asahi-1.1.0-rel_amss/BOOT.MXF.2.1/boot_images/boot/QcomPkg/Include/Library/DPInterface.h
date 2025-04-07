#ifndef DPINTERFACE_H
#define DPINTERFACE_H
/*=============================================================================
 
  File: DPInterface.h
 
  Header file for DP driver
  
 
  Copyright (c) 2018-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/

#include "MDPTypes.h"
#include "../MDPLib/MDPLib_i.h"

/* -----------------------------------------------------------------------
**    Defines
-------------------------------------------------------------------------- */

/* Flags for DP_Driver_Open function */
#define DPINTERFACE_PLUG_INVERTED         0x00000001      /* configure the thpe-c for an inverted polarity */

/* -----------------------------------------------------------------------
** Function Declarations
-------------------------------------------------------------------------- */


/****************************************************************************
*
** FUNCTION: DPDriver_Open()
*/
/*!
* \brief
*   Initialize DP driver (host and panel)
*
* \param [in]   eDisplayId           - display id
* \param [in]   Flags                - DP driver flags
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status DPDriver_Open(MDP_Display_IDType eDisplayId, uint32 Flags);

/****************************************************************************
*
** FUNCTION: DP_Driver_IsDisplayPlugged()
*/
/*!
* \brief
*   Check if a panel is plugged into the DP interface
*
* \param [in]   eDisplayId           - display id
*
* \retval bool32
*
****************************************************************************/
bool32 DPDriver_IsDisplayPlugged( MDP_Display_IDType eDisplayId);

/************************************************************************************************************
*
** FUNCTION: DP_Driver_GetModeInfo()
*/
/*!
* \brief
*   Retrieves the mode info of the display plugged into the DP interface
*
* \param [out]  pPanelInfo            - Pointer to mode info.
*
* \retval MDP_Status          MDP_STATUS_OK = mode supported, MDP_STATUS_NOT_SUPPORTED = mode not supported
*
**************************************************************************************************************/
MDP_Status DPDriver_GetModeInfo(MDP_Panel_AttrType *pPanelInfo);

/* ----------------------------------------------------------------------
** FUNCTION: DPDriver_BrightnessEnable()
**
** DESCRIPTION:
**    Enable panel brightness through AUX
**
-------------------------------------------------------------------- */
MDP_Status DPDriver_BrightnessEnable(MDP_Display_IDType eDisplayId, bool32 bEnable);

/* ----------------------------------------------------------------------
** FUNCTION: DPDriver_BrightnessLevel()
**
** DESCRIPTION:
**    Set panel brightness to requested level
**
-------------------------------------------------------------------- */
MDP_Status DPDriver_BrightnessLevel(MDP_Display_IDType eDisplayId, float fNewLevel, uint32 uMillinits);

/************************************************************************************************************
*
** FUNCTION: DP_Driver_SetMode()
*/
/*!
* \brief
*   Set a mode on the display plugged into the DP interface using either a mode index or panel info
*   Set pPanelInfo to NULL to set the mode index based on the EDID data
*
* \param [in]  pPanelInfo            - Pointer to mode info.
* \param [in]  uFlags                - Associated flags
*
* \retval MDP_Status          MDP_STATUS_OK = mode set successfully
*
**************************************************************************************************************/
MDP_Status DPDriver_SetMode(MDP_Panel_AttrType *pPanelInfo, uint32 uFlags);

/************************************************************************************************************
*
** FUNCTION: DP_Driver_Close()
*/
/*!
* \brief
*   Deinitialize DP driver (and power down components)
*
* \param [in]   eDisplayId           - display id
*
* \retval MDP_Status          
*
**************************************************************************************************************/
MDP_Status DPDriver_Term(MDP_Display_IDType eDisplayId);

/************************************************************************************************************
*
** FUNCTION: DPDriver_UpdateBondedModeTimings()
*/
/*!
* \brief
*    Scale the panel attribute timings to represent the display with all bonded devices combined.
*
* \param [in]      pPanelAttr       - Pointer to panel attributes
*
* \retval NONE
*
**************************************************************************************************************/
void DPDriver_UpdateBondedModeTimings(MDP_Panel_AttrType *pPanelAttr);

/************************************************************************************************************
*
** FUNCTION: DPDriver_SetConnectionStatus()
*/
/*!
* \brief
*    Update the panel connection status and other HPD data.
*
* \param [in]      eDisplayId       - Display Id
* \param [in]      bConnected       - TRUE = display plugged in, FALSE = display plugged out
* \param [in]      pHotPlugData     - Pointer to additional HPD data
*
* \retval MDP_Status
*
**************************************************************************************************************/
MDP_Status DPDriver_SetConnectionStatus(MDP_Display_IDType eDisplayId, bool32 bConnected, MDP_HotPlugEventDataType *pHotPlugData);

/************************************************************************************************************
*
** FUNCTION: DPDriver_GetEDID()
*/
/*!
* \brief
*    Fetches the panel EDID.
*
* \param [in]      eDisplayId       - Display Id
* \param [in]      pEDIDInfo        - Pointer to EDID array
* \param [in]      pEDIDSize        - Pointer to EDID size
*
* \retval MDP_Status
*
**************************************************************************************************************/
MDP_Status DPDriver_GetEDID(MDP_Display_IDType eDisplayId, void *pEDIDInfo, uint32 *pEDIDSize);


#endif  /* #define DPINTERFACE_H */
