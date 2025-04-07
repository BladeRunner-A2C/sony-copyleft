/*=============================================================================
 
  File: hal_dp_dsc_stub.c
 
  Source file for DP DSC HAL function stubs
   
  Copyright (c) 2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/


/*------------------------------------------------------------------------------
 * Include Files
 *----------------------------------------------------------------------------*/
#include "hal_dp_i.h"

#ifdef __cplusplus
extern "C" {
#endif

/* -----------------------------------------------------------------------
** Public Functions
** ----------------------------------------------------------------------- */

/**********************************************************************************************************************
FUNCTION: HAL_DP_DSC_SendPPS()
   
   This API sends the DSC PPS through SDP

Parameters: 
   eControllerId              -[in] DP core ID
   psPPSConfig                -[in] Pointer to PPS config structrure

Return:  
   None

**********************************************************************************************************************/
void  HAL_DP_DSC_SendPPS(DP_ControllerIDType   eControllerId,
                         HAL_DP_PPSConfigType *psPPSConfig)
{  
}

/**********************************************************************************************************************
FUNCTION: HAL_DP_SetDSCConfig()
   
   This API set the DSC configuration 

Parameters: 
   eControllerId              -[in] DP core ID
   psDSCConfig              -[in] Pointer to DSC configurations structure.

Return:  
   None

**********************************************************************************************************************/
void HAL_DP_SetDSCConfig(DP_ControllerIDType     eControllerId,
                         HAL_DP_DSCConfigType   *psDSCConfig)
{
}

/**********************************************************************************************************************
FUNCTION: HAL_DP_SetFECConfig()

   This API sets the FEC configuration

Parameters:
   eControllerId        -[in] DP core ID
   bEnable              -[in] Flag used to enable/disable FEC
   bTunneledMode        -[in] Boolean used to indicate if in DP tunneling mode

Return:
   None

**********************************************************************************************************************/
void HAL_DP_SetFECConfig(DP_ControllerIDType    eControllerId,
                         bool32                 bEnable,
                         bool32                 bTunneledMode)
{
}

#ifdef __cplusplus
}
#endif

