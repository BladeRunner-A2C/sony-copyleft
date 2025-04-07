
/*=====================================================================================================================
 
  File: edp_psr_stub.c
 
  Stubbed source file for eDP PSR related functionality 
   
  Copyright (c) 2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=======================================================================================================================*/


/*---------------------------------------------------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------------------------------------------------*/
#include "dp_i.h"
#include "hal_dp_phy.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------------------------------------------------
 * Defines
 *-------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 * Private functions 
 *---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 * Public functions 
 *---------------------------------------------------------------------------------------------------------------------*/

//-------------------------------------------------------------------------------------------------
//  eDP_PSR_Init
//
//  @brief
//      Function enables PSR/PSR2 function in the sink and configures the eDP controller. If the function 
//      returns success, it means that the sink & source are ready to process PSR enter/exit requests.
//      NOTE: PSR2 support is not exposed yet.
//
//  @params
//      [IN/OUT] pDisplayCtx
//          Pointer to context handle.
//
//  @return
//      DP_Status 
//-------------------------------------------------------------------------------------------------
//
DP_Status eDP_PSR_Init(DP_DisplayCtxType  *pDisplayCtx)
{
  DP_Status             eStatus = DP_STATUS_SUCCESS;

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  eDP_PSR_Request
//
//  @brief
//      Function to set PSR state of source and sink
//
//
//  @params
//      [IN/OUT] pDisplayCtx
//          Pointer to context handle.
//      [IN] ePSRRequest
//          Type of PSR Request
//
//  @return
//      DP_Status 
//-------------------------------------------------------------------------------------------------
//
DP_Status eDP_PSR_Request(DP_DisplayCtxType  *pDisplayCtx,  
                          DP_PSRRequestType   ePSRRequest)
{
  DP_Status          eStatus = DP_STATUS_SUCCESS;  

  return eStatus;
}

#ifdef __cplusplus
}
#endif
