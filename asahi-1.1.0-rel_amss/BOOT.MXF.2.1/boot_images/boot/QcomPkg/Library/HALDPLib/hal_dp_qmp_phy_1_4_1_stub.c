/*===========================================================================
  
  This file contains the stub programming for the DP QMP Phy/PLL (v1.4.1 5nm).

  Copyright (c) 2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* -----------------------------------------------------------------------
** Includes
** ----------------------------------------------------------------------- */
#include "hal_dp_i.h"
#include "hal_dp_phy.h"

//-------------------------------------------------------------------------------------------------
//  HAL_DP_Qmp_1_4_1_PhyFxnsInit
//
//  @brief
//      Initialize function vector table for DP QMP PHY
//
//  @params
//   [IN/OUT] pFxnTable
//           Pointer to DP PHY function vector table
//
//  @return
//      None
//-------------------------------------------------------------------------------------------------
void HAL_DP_Qmp_1_4_1_PhyFxnsInit(HAL_DP_PhyPllFunctionTable *pFxnTable)
{
  pFxnTable->HAL_DP_PHY_AUX_Init            = NULL;  
  pFxnTable->HAL_DP_PHY_SetPHYMode          = NULL;
  pFxnTable->HAL_DP_PHY_Config              = NULL;
  pFxnTable->HAL_DP_PHY_SetupPeSw           = NULL;
  pFxnTable->HAL_DP_PHY_GetMaxPeSwLevel     = NULL;
  pFxnTable->HAL_DP_PHY_Power               = NULL;
  pFxnTable->HAL_DP_PHY_GetPLLStatus        = NULL;
  pFxnTable->HAL_DP_PHY_GetCalcPhyClksFreq  = NULL;
}