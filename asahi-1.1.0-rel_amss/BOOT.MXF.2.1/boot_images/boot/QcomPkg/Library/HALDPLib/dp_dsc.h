#ifndef _DP_DSC_H_
#define _DP_DSC_H_
/*! \file */
/*=====================================================================================================
 
  File: dp_dsc.h
 
  Header file for DP DSC
   
  Copyright (c) 2018-2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
====================================================================================================*/


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
DP_Status DP_DSC_QueryInfo(DP_DisplayCtxType *pDisplayCtx);
  
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
DP_Status DP_FEC_QueryInfo(DP_DisplayCtxType *pDisplayCtx);

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
DP_Status DP_DSC_CalculateParameters(DP_DisplayCtxType *pDisplayCtx, uint32 uModeIdx);

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
DP_Status DP_FEC_CalculateParameters(DP_DisplayCtxType *pDisplayCtx);

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
DP_Status DP_DSC_ConfigureSource(DP_DisplayCtxType  *pDisplayCtx,
                                 bool32              bEnable);

/*********************************************************************************************
*
** FUNCTION: DP_DSC_ConfigureSink()
*/
/*!
* \DESCRIPTION
*      Configure DSC on sink, if enabled
*
* \param [in]   pDisplayCtx        - Pointer to DP Context
* \param [in]   bEnable            - Flag used to determine if DSC needs to be enabled/disabled
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status DP_DSC_ConfigureSink(DP_DisplayCtxType  *pDisplayCtx, bool32 bEnable);

/*********************************************************************************************
*
** FUNCTION: DP_FEC_ConfigureSink()
*/
/*!
* \DESCRIPTION
*      Configure FEC on sink, if enabled
*
* \param [in]   pDisplayCtx        - Pointer to DP Context
* \param [in]   bEnable            - Flag used to determine if FEC needs to be enabled/disabled
*
* \retval DP_Status
*
**********************************************************************************************/
DP_Status  DP_FEC_ConfigureSink(DP_DisplayCtxType  *pDisplayCtx, bool32 bEnable);

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
DP_Status DP_FEC_Decode_Status (DP_DisplayCtxType  *pDisplayCtx);

#endif //_DP_DSC_H_
