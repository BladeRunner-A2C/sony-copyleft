/*=============================================================================

  File: Dp_DriverStub.c

  DP stubs for the case where DP is not supported by platform


 Copyright (c) 2016-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
 Qualcomm Technologies Proprietary and Confidential.
 =============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif


/*=========================================================================
      Include Files
==========================================================================*/

#include "MDPLib_i.h"
#include "dp_i.h"

/*=========================================================================
      Public Functions
==========================================================================*/


/****************************************************************************
*
** FUNCTION: DPDriver_Open()
*/
/*!
* \brief
*   Initialize DP driver (host and panel)
*
* \param [in]   eDisplayId           - DP id
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status DPDriver_Open(MDP_Display_IDType eDisplayId)
{
  return MDP_STATUS_FAILED;
}

/****************************************************************************
*
** FUNCTION: DPDriver_IsDisplayPlugged()
*/
/*!
* \brief
*   Check if a panel is plugged into the DP interface
i*
* \param [in]   eDisplayId           - DP id
*
* \retval bool32
*
****************************************************************************/
bool32 DPDriver_IsDisplayPlugged(MDP_Display_IDType eDisplayId)
{
  return FALSE;
}

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
MDP_Status DPDriver_GetModeInfo(MDP_Panel_AttrType *pPanelInfo)
{
  return MDP_STATUS_FAILED;
}

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
MDP_Status DPDriver_SetMode(MDP_Panel_AttrType *pPanelInfo, uint32 uFlags)
{
  return MDP_STATUS_FAILED;
}

/************************************************************************************************************
*
** FUNCTION: DPDriver_Close()
*/
/*!
* \brief
*   Deinitialize DP driver (and power down components)
*
* \param [in]   eDisplayId           - DP id
*
* \retval MDP_Status
*
**************************************************************************************************************/
MDP_Status DPDriver_Term(MDP_Display_IDType eDisplayId)
{
  return MDP_STATUS_FAILED;
}

/* ----------------------------------------------------------------------
** FUNCTION: DPDriver_SendComamndSequence()
**    
** DESCRIPTION: 
**    DP Driver sends meta data to client (panel)
**    
-------------------------------------------------------------------- */
MDP_Status DPDriver_SendCommandSequence(MDP_Panel_AttrType *pPanelInfo, MdpPanelCommandType eCommand, void *pPayload, uint32 uFlags)
{   
  return MDP_STATUS_FAILED;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DPDriver_UpdateBondedModeTimings()
**
** DESCRIPTION:
**   Scale the panel attribute timings to represent the display with all 
**   bonded devices combined.
**
*//* -------------------------------------------------------------------- */
void DPDriver_UpdateBondedModeTimings(MDP_Panel_AttrType *pPanelAttr)
{
  return;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DPDriver_SetConnectionStatus()
**
** DESCRIPTION:
**   Set DP connection status in driver context.
**
*//* -------------------------------------------------------------------- */
MDP_Status DPDriver_SetConnectionStatus(MDP_Display_IDType eDisplayId, bool32 bConnected, MDP_HotPlugEventDataType *pHotPlugData)
{
  return MDP_STATUS_FAILED;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DPDriver_TunneledOpen()
**
** DESCRIPTION:
**   Perform DP Tunneled mode open.
**
*//* -------------------------------------------------------------------- */
MDP_Status DPDriver_TunneledOpen(MDP_Display_IDType eDisplayId, uint32 uFlags)
{
  return MDP_STATUS_FAILED;
}

/* ----------------------------------------------------------------------
** FUNCTION: DPDriver_BrightnessEnable()
**
** DESCRIPTION:
**    Enable panel brightness through AUX
**
-------------------------------------------------------------------- */
MDP_Status DPDriver_BrightnessEnable(MDP_Display_IDType eDisplayId, bool32 bEnable)
{
  return MDP_STATUS_FAILED;
}

/* ----------------------------------------------------------------------
** FUNCTION: DPDriver_BrightnessLevel()
**
** DESCRIPTION:
**    Set panel brightness to requested level
**
-------------------------------------------------------------------- */
MDP_Status DPDriver_BrightnessLevel(MDP_Display_IDType eDisplayId, float fNewLevel, uint32 uMillinits)
{
  return MDP_STATUS_FAILED;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DPDriver_GetEDID()
**
** DESCRIPTION:
**   Retrieve panel EDID.
**
*//* -------------------------------------------------------------------- */
MDP_Status DPDriver_GetEDID(MDP_Display_IDType eDisplayId, void* pEDIDInfo, uint32* pEDIDSize)
{
  return MDP_STATUS_FAILED;
}

#ifdef __cplusplus
}
#endif

