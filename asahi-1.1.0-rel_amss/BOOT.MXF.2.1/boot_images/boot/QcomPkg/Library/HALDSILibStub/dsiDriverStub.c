/*=============================================================================
 
  File: dsipanel.c
 
  Source file for HAL DSI Panel configuration
  
     Copyright (c) 2011-2021 Qualcomm Technologies, Inc.
     All Rights Reserved.
     Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

/* -----------------------------------------------------------------------
** Includes
** ----------------------------------------------------------------------- */
#include "dsiHostShared.h"

/* -----------------------------------------------------------------------
** Defines
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Global variables
** ----------------------------------------------------------------------- */

/*------------------------------------------------------------------------
Custom DSI commands types
-------------------------------------------------------------------------- */

/*------------------------------------------------------------------------
Local Prototypes
-------------------------------------------------------------------------- */


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_Read()
** 
** DESCRIPTION:
**   This allows to send the dsi read commands to the panel. 
** 
**
** -------------------------------------------------------------------- */
MDP_Status DSIDriver_Read(MDP_Display_IDType eDisplayId, uint8 uCmdType, void *pPayload, uint32 uPayloadSize, void *pReadData, uint32 *pReadSize, DSIDisplay_CmdFlags eFlags)
{
  MDP_Status          eStatus       = MDP_STATUS_OK;

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_Write()
** 
** DESCRIPTION:
**   This allows to send the dsi write commands to the panel. 
** 
**
** -------------------------------------------------------------------- */
MDP_Status DSIDriver_Write(MDP_Display_IDType eDisplayId, uint8 uCmdType, void *pPayload, uint32 uPayloadSize, DSIDisplay_CmdFlags eFlags)
{
  MDP_Status           eMDPStatus   = MDP_STATUS_OK;

  return eMDPStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_Init()
** 
** DESCRIPTION:
**   Initialize the DSI Core
**
*//* -------------------------------------------------------------------- */
MDP_Status DSIDriver_Init(MDP_Panel_AttrType *pPanelConfig)
{
  MDP_Status            eStatus       = MDP_STATUS_OK;

  return eStatus;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_Close()
** 
** DESCRIPTION:
**   Deinitialize the DSI Core
**
*//* -------------------------------------------------------------------- */
void DSIDriver_Close(MDP_Display_IDType eDisplayId)
{

}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: ConvertPanelColorToDSIColorFormat()
**
** DESCRIPTION:
**   Convert Panel CorlorFormat to DSI ColorFormat
**
*//* -------------------------------------------------------------------- */

DSI_ColorFormatType ConvertPanelColorToDSIColorFormat(MDP_ColorFormat_Type eColorFormat)
{
  DSI_ColorFormatType eDsiColorFormat = DSI_COLOR_RGB_888_24BPP;
  
  return eDsiColorFormat;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_SetMode()
** 
** DESCRIPTION:
**   Initialize the DSI Core
**
*//* -------------------------------------------------------------------- */
MDP_Status DSIDriver_SetMode(MDP_Panel_AttrType *pPanelConfig)
{
  MDP_Status            eStatus                =  MDP_STATUS_OK;
  
  return eStatus;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_RemapLane()
** 
** DESCRIPTION:
**   Remap DSI lane order
**
** ---------------------------------------------------------------------- */

MDP_Status DSIDriver_RemapLane(MDP_Display_IDType eDisplayId, uint32 uLaneRemapOrder)
{
  MDP_Status       eStatus        =  MDP_STATUS_OK;

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_ConfigClockLane()
** 
** DESCRIPTION:
**   Config the clock lane to HS or LP(default)
**
** ---------------------------------------------------------------------- */

MDP_Status DSIDriver_ConfigClockLane(MDP_Display_IDType eDisplayId, uint32 uClkConfig)
{
  MDP_Status               eStatus        =  MDP_STATUS_OK;
   
  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_MinimalInit()
** 
** DESCRIPTION:
**   Minimal initialization needed to do DSI read commands
**
** ---------------------------------------------------------------------- */
MDP_Status DSIDriver_MinimalInit(MDP_Display_IDType eDisplayId, bool32 bCPhyMode)
{
  MDP_Status             eStatus              = MDP_STATUS_OK;

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_GetCalibrationCodes()
** 
** DESCRIPTION:
**   Get dynamic refresh calibration codes
**
** ---------------------------------------------------------------------- */
MDP_Status DSIDriver_GetCalibrationCodes(uint32 uDSIIndex, MDP_PLLCodesInfo *psPllCodesInfo)
{
  MDP_Status             eStatus              = MDP_STATUS_OK;

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_SetDynamicRefreshFreqs()
** 
** DESCRIPTION:
**   Set dynamic refresh frequencies
**
** ---------------------------------------------------------------------- */
MDP_Status DSIDriver_SetDynamicRefreshFreqs(uint32 *puFreqList, uint32 uFreqNum)
{
  MDP_Status                eStatus              = MDP_STATUS_OK;

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_CalibratePLL()
** 
** DESCRIPTION:
**   Calibration and get PLL codes, should call DSIDriver_SetDynamicRefreshFreqs
**   before calling this function
**
** ---------------------------------------------------------------------- */
MDP_Status DSIDriver_CalibratePLL(uint32 *puPllCodes, uint32 *puPllCodesSize)
{
  MDP_Status                eStatus              = MDP_STATUS_OK;

  return eStatus;
}

/*------------------------------------------------------------------------
Panel Driver Helper Functions
-------------------------------------------------------------------------- */



/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DsiPanelInit()
** 
** DESCRIPTION:
**   DSI Clocks and timing initialization
**
** ---------------------------------------------------------------------- */
MDP_Status DsiPanelInit(MDP_Panel_AttrType    *pPanelInfo)
{
  MDP_Status        eStatus         = MDP_STATUS_OK;

  return eStatus;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DsiPanelShutdown()
** 
** DESCRIPTION:
**   Gracefully shutdown the controller and panel
**
*//* -------------------------------------------------------------------- */
MDP_Status DsiPanelShutdown(MDP_Panel_AttrType *pPanelConfig)
{
  MDP_Status  eStatus =  MDP_STATUS_OK;

  return eStatus;
}




/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DsiPanelSendCommandSequence()
** 
** DESCRIPTION:
**   Send DSI command sequence
**
** ---------------------------------------------------------------------- */
MDP_Status DsiPanelSendCommandSequence(MDP_Panel_AttrType *pPanelInfo, MdpPanelCommandType eCommand, void *pCustomCommand, uint32 uFlags)
{
  MDP_Status            eStatus     =  MDP_STATUS_OK;

  return eStatus;
}




/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DsiPanelDumpRegisters()
** 
** DESCRIPTION: Helper function to dump panel registers
** 
**
*//* -------------------------------------------------------------------- */
MDP_Status DsiPanelDumpRegisters(void)
{

  return MDP_STATUS_OK;
}


/*------------------------------------------------------------------------
Local Functions
-------------------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

