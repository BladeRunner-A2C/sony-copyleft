/*=====================================================================================================================
 
  File: dp_dsc_stub.c
 
  Stubbed source file for DP DSC functions 
   
  Copyright (c) 2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=======================================================================================================================*/


/*---------------------------------------------------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------------------------------------------------*/

#include "dp_i.h"
#include "dp_dsc.h"

#ifdef __cplusplus
extern "C" {
#endif

/*--------------------------------------------------------------------------------------------
 * Public Functions
 *------------------------------------------------------------------------------------------*/

/*********************************************************************************************
*
** FUNCTION: DP_DSC_ConfigureSink()
*/
/*!
* \DESCRIPTION
*      Configure DSC on sink
*
* \param [in]   pDisplayCtx        - Pointer to DP Context
* \param [in]   bEnable            - Flag used to determine if DSC needs to be enabled/disabled
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_DSC_ConfigureSink(DP_DisplayCtxType  *pDisplayCtx, bool32 bEnable)
{
  DP_Status               eStatus = DP_STATUS_SUCCESS;

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_FEC_ConfigureSink()
*/
/*!
* \DESCRIPTION
*      Configure FEC on sink
*
* \param [in]   pDisplayCtx        - Pointer to DP Context
* \param [in]   bEnable            - Flag used to determine if FEC needs to be enabled/disabled
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_FEC_ConfigureSink(DP_DisplayCtxType *pDisplayCtx, bool32 bEnable)
{
  DP_Status               eStatus = DP_STATUS_SUCCESS;

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_DSC_QueryInfo()
*/
/*!
* \DESCRIPTION
*      Query DSC information from the sink.
*
* \param [in]   pDisplayCtx        - Pointer to DP Context
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status DP_DSC_QueryInfo(DP_DisplayCtxType *pDisplayCtx)
{
  DP_Status               eStatus = DP_STATUS_SUCCESS;

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_FEC_QueryInfo()
*/
/*!
* \DESCRIPTION
*      Query FEC information from the sink.
*
* \param [in]   pDisplayCtx        - Pointer to DP Context
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status DP_FEC_QueryInfo(DP_DisplayCtxType *pDisplayCtx)
{
  DP_Status               eStatus = DP_STATUS_SUCCESS;

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_DSC_CalculateParameters()
*/
/*!
* \DESCRIPTION
*      Calculate DSC Slice info (height, width and slice per line).
*
* \param [in]   pDisplayCtx        - Pointer to DP Context
* \param [in]   uModeIdx           - Index of the mode to use for calculation
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status DP_DSC_CalculateParameters(DP_DisplayCtxType *pDisplayCtx, uint32 uModeIdx)
{
  DP_Status               eStatus = DP_STATUS_SUCCESS;

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_FEC_CalculateParameters()
*/
/*!
* \DESCRIPTION
*      Calculate FEC info (adjusted link rate).
*
* \param [in]   pDisplayCtx        - Pointer to DP Context
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status DP_FEC_CalculateParameters(DP_DisplayCtxType *pDisplayCtx)
{
  DP_Status               eStatus = DP_STATUS_SUCCESS;

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_DSC_ConfigureSource()
*/
/*!
* \DESCRIPTION
*      Configure DSC in DP controller
*
* \param [in]   pDisplayCtx      - Pointer to DP Context
* \param [in]   bEnable          - Flag used to determine if DSC needs to be enabled/disabled
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status DP_DSC_ConfigureSource(DP_DisplayCtxType  *pDisplayCtx, bool32 bEnable)
{
  DP_Status               eStatus = DP_STATUS_SUCCESS;

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: DP_FEC_Decode_Status()
*/
/*!
* \DESCRIPTION
*      Read FEC status to check if "Decode enable" is detected
*
* \param [in]   pDisplayCtx      - Pointer to DP Context
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status DP_FEC_Decode_Status (DP_DisplayCtxType  *pDisplayCtx)
{
  DP_Status               eStatus           = DP_STATUS_SUCCESS;

  return eStatus;
}


/*--------------------------------------------------------------------------------------------
 * Private Functions
 *------------------------------------------------------------------------------------------*/

/*********************************************************************************************
*
** FUNCTION: CalculateSliceDimensions
*/
/*!
* \DESCRIPTION
*      Get DSC Slice info (height, width and slice per line).
*
* \param [in]   pStreamCtx        - Pointer to stream context
* \param [in]   uModeIdx          - Index of the mode to use for calculation
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status CalculateSliceDimensions(DP_StreamCtxType *pStreamCtx, uint32 uModeIdx)
{
  DP_Status                  eStatus          = DP_STATUS_SUCCESS;

  return eStatus;
}

/*********************************************************************************************
*
** FUNCTION: CalculateBlankEndInLane
*/
/*!
* \DESCRIPTION
*      BE_IN_LANE is only used when MST Constant fill and DATABUS_WIDEN are ON.
*      BE_IN_LANE is always set to 10 by default except when DSC is enabled, then it follows  
*      one hot encoding scheme which shows the lane we should send the blank end (BE) packet on. 
*      If 3  >= h compressed total mod 12 > 0, blank end will be on lane 0 (0b0001)
*      If 6  >= h compressed total mod 12 > 3, blank end will be on lane 1 (0b0010)
*      If 9  >= h compressed total mod 12 > 6, blank end will be on lane 2 (0b0100)
*      If 11 >= h compressed total mod 12 > 9, blank end will be on lane 3 (0b1000)
*
* \param [in]   pStreamCtx       - Pointer to stream context
* \param [in]   bDSCEnable       - Flag used to determine if DSC is enabled/disabled
* \param [in]   bMSTEnable       - Flag used to determine if MST is enabled/disabled
*
* \retval BE_IN_LANE
*
**********************************************************************************************/
uint32 CalculateBlankEndInLane(DP_StreamCtxType *pStreamCtx, bool32 bDSCEnable, bool32 bMSTEnable)
{
  uint32 uBeInLane = 10;

  return uBeInLane;
}

#ifdef __cplusplus
}
#endif

