/*=============================================================================
 
  File: hal_dp_phy.c
 
  Source file for DP PHY hardware functionality 
   
  Copyright (c) 2016-2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

#include "hal_dp_i.h"
#include "hal_dp_phy.h"


#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------------------------------------------------
  Macros
---------------------------------------------------------------------------------------------------------------------*/



/* -----------------------------------------------------------------------
** Types
** ----------------------------------------------------------------------- */






/* -----------------------------------------------------------------------
** Statics
** ----------------------------------------------------------------------- */

HAL_DP_PhyPllFunctionTable gDPPhyPllFxnTable[DP_DEVICE_MAX];

/*---------------------------------------------------------------------------------------------------------------------
  Public Functions
---------------------------------------------------------------------------------------------------------------------*/


/****************************************************************************
*
** FUNCTION: HAL_DP_PhyFxnsInit()
*/
/*!
* \DESCRIPTION
*   Initialize DP PHY/PLL function table
*
* \retval None
*
****************************************************************************/
void HAL_DP_PhyFxnsInit(void)
{
  uint32             uRegValue     = in_dword(HWIO_DPTX_0_HW_VERSION_ADDR);
  HAL_HW_VersionType sCoreVersion;

  sCoreVersion.uMajorVersion   = HWIO_GETVAL(DPTX_0_HW_VERSION, uRegValue, MAJOR);
  sCoreVersion.uMinorVersion   = HWIO_GETVAL(DPTX_0_HW_VERSION, uRegValue, MINOR);
  sCoreVersion.uReleaseVersion = HWIO_GETVAL(DPTX_0_HW_VERSION, uRegValue, STEP);

  //clear function table
  DP_OSAL_MemSet(&gDPPhyPllFxnTable, 0, HAL_SIZEOF(gDPPhyPllFxnTable));

  if ((1 == sCoreVersion.uMajorVersion) &&
      (4 == sCoreVersion.uMinorVersion) &&
      (1 == sCoreVersion.uReleaseVersion))
  {
    DP_DeviceIDType eDeviceId;

    for (eDeviceId = DP_DEVICE_ID_ALT_MODE_0; eDeviceId < DP_DEVICE_MAX; eDeviceId++)
    {
      switch (eDeviceId)
      {
      case DP_DEVICE_ID_ALT_MODE_0:
      case DP_DEVICE_ID_ALT_MODE_1:
      case DP_DEVICE_ID_ALT_MODE_2:
      {
        HAL_DP_Qmp_1_4_1_PhyFxnsInit(&gDPPhyPllFxnTable[eDeviceId]);
        break;
      }
      case DP_DEVICE_ID_EDP:
      {
        HAL_DP_1_4_1_PhyFxnsInit(&gDPPhyPllFxnTable[eDeviceId]);
        break;
      }
      default:
        break;
      }
    }
  }
  else
  {
    DP_LOG_MESSAGE_ERROR("HAL_DP_PhyFxnsInit: major=%d minor=%d is NOT supported\n", sCoreVersion.uMajorVersion, sCoreVersion.uMinorVersion);
  }
}

/*********************************************************************************************
*
** FUNCTION: HAL_DP_SetupPHYPeSwLevel()
*/
/*!
* \brief
*        Set up DP Lane Pre Emphasis and voltage swing level
*
* \param [in]     eDeviceId      - DP Device ID
* \param [in]     eDeviceDPMode  - DP device mode
* \param [in/out] pPeSwConfig    - Pre-emphasis/Swing level settings.
*
* \retval  HAL_MDSS_ErrorType
*
**********************************************************************************************/
HAL_MDSS_ErrorType HAL_DP_SetupPHYPeSwLevel(DP_DeviceIDType        eDeviceId,
                                            DP_DeviceModeType      eDeviceDPMode,
                                            HAL_DP_PeSwConfigType *pPeSwConfig)
{
  HAL_MDSS_ErrorType          eStatus   = HAL_MDSS_STATUS_SUCCESS;
  HAL_DP_PhyPllFunctionTable *pFxnTable = &gDPPhyPllFxnTable[eDeviceId];

  if (NULL != pFxnTable->HAL_DP_PHY_SetupPeSw)
  {
    eStatus = pFxnTable->HAL_DP_PHY_SetupPeSw(eDeviceId, eDeviceDPMode, pPeSwConfig);
  }
  else
  {
    eStatus = HAL_MDSS_STATUS_FAILED_NOT_IMPLEMENTED;
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_DP_PHY_Config()
*/
/*!
* \DESCRIPTION
*           Configure DP PHY and PLL 
*
* \param [in]   eDeviceId             - DP Device ID
* \param [in]   HAL_DP_PllConfigType  - DP PHY PLL config info
* \param [in]   eDeviceDPMode         - DP Device mode
*
* \retval boolean  
*
****************************************************************************/
bool32 HAL_DP_PHY_Config(DP_DeviceIDType       eDeviceId,
                         HAL_DP_PllConfigType *pDPPllConfigInfo,
                         DP_DeviceModeType     eDeviceDPMode)
{
  bool32                      bStatus   = FALSE;
  HAL_DP_PhyPllFunctionTable *pFxnTable = &gDPPhyPllFxnTable[eDeviceId];

  if (NULL != pFxnTable->HAL_DP_PHY_Config)
  {
    bStatus = pFxnTable->HAL_DP_PHY_Config(eDeviceId, pDPPllConfigInfo, eDeviceDPMode);
  }

  return bStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_DP_PHY_Reset()
*/
/*!
* \DESCRIPTION
*           Reset DP PHY
*
* \param [in]     eDeviceId   - DP Device ID
*        [in]     eModules    - PHY module to reset
*
* \retval   
*
****************************************************************************/
void HAL_DP_PHY_Reset(DP_DeviceIDType      eDeviceId,
                      DP_PHYResetFlagType  eModules)
{
  HAL_DP_PhyPllFunctionTable *pFxnTable = &gDPPhyPllFxnTable[eDeviceId];

  if (NULL != pFxnTable->HAL_DP_PHY_Reset)
  {
    pFxnTable->HAL_DP_PHY_Reset(eDeviceId, eModules);
  }
}

/****************************************************************************
*
** FUNCTION: HAL_DP_PHY_AUX_Init()
*/
/*!
* \DESCRIPTION
*           Configure DP AUX PHY
*
* \param [in] eDeviceId      - DP Device ID
* \param [in] eDeviceDPMode  - DP device mode
*
* \retval   
*
****************************************************************************/
void HAL_DP_PHY_AUX_Init(DP_DeviceIDType eDeviceId, DP_DeviceModeType eDeviceDPMode)
{
  HAL_DP_PhyPllFunctionTable *pFxnTable = &gDPPhyPllFxnTable[eDeviceId];

  if (NULL != pFxnTable->HAL_DP_PHY_AUX_Init)
  {
    pFxnTable->HAL_DP_PHY_AUX_Init(eDeviceId, eDeviceDPMode);
  }
}

/*********************************************************************************************
*
** FUNCTION: HAL_DP_PHY_GetMaxPeSwLevel()
*/
/*!
* \brief
*        Get max supported DP Lane Pre Emphasis and voltage swing levels
*
* \param [in]    eDeviceId        - DP Device ID
* \param [out]   uMaxPreemphLvl   - max Pre-emphasis level supported.
* \param [out]   uMaxVoltSwingLvl - max voltage swing level supported.
*
* \retval  void
*
**********************************************************************************************/
HAL_MDSS_ErrorType HAL_DP_PHY_GetMaxPeSwLevel(DP_DeviceIDType  eDeviceId,
                                              uint32          *uMaxPreemphLvl,
                                              uint32          *uMaxVoltSwingLvl)
{
  HAL_MDSS_ErrorType          eStatus   = HAL_MDSS_STATUS_SUCCESS;
  HAL_DP_PhyPllFunctionTable *pFxnTable = &gDPPhyPllFxnTable[eDeviceId];

  if (NULL != pFxnTable->HAL_DP_PHY_GetMaxPeSwLevel)
  {
    pFxnTable->HAL_DP_PHY_GetMaxPeSwLevel(eDeviceId, uMaxPreemphLvl, uMaxVoltSwingLvl);
  }
  else
  {
    eStatus = HAL_MDSS_STATUS_FAILED_NOT_SUPPORTED;
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_DP_PHY_Power()
*/
/*!
* \DESCRIPTION
*           Power on/off DP PHY related HW blocks
*
* \param [in]     eDeviceId - DP Device ID
* \param [in]     bPowerOn  - TRUE: power on, FALSE: power off
* \param [in]     uModules  - HW module(s) to power on/off
*
* \retval   HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_PHY_Power(DP_DeviceIDType        eDeviceId,
                                    bool32                 bPowerOn,
                                    DP_PHYPowerModuleType  uModules)
{
  HAL_MDSS_ErrorType eStatus = HAL_MDSS_STATUS_SUCCESS;

  HAL_DP_PhyPllFunctionTable *pFxnTable = &gDPPhyPllFxnTable[eDeviceId];

  if (NULL != pFxnTable->HAL_DP_PHY_Power)
  {
    eStatus = pFxnTable->HAL_DP_PHY_Power(eDeviceId, bPowerOn, uModules);
  }
  else
  {
    eStatus = HAL_MDSS_STATUS_FAILED_NOT_SUPPORTED;
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_DP_PHY_AUXConfig()
*/
/*!
* \DESCRIPTION
*           Power on/off DP PHY
*
* \param [in]     eDeviceId  - DP Device ID
* \param [in]     pAuxPhyCfg - Aux configuration
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType HAL_DP_PHY_AUXConfig(DP_DeviceIDType       eDeviceId,
                                        HAL_DP_AuxPhyCfgType *pAuxPhyCfg)
{
  HAL_MDSS_ErrorType          eStatus   = HAL_MDSS_STATUS_SUCCESS;
  HAL_DP_PhyPllFunctionTable *pFxnTable = &gDPPhyPllFxnTable[eDeviceId];

  if (NULL != pFxnTable->HAL_DP_PHY_AUXConfig)
  {
    eStatus = pFxnTable->HAL_DP_PHY_AUXConfig(eDeviceId, pAuxPhyCfg);
  }
  else
  {
    eStatus = HAL_MDSS_STATUS_FAILED_NOT_SUPPORTED;
  }

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: HAL_DP_PHY_SetPHYMode()
*/
/*!
* \DESCRIPTION
*           Set the PHY Mode to DP or USB SS
*
* \param [in]     eDeviceId  - DP Device ID
* \param [in]     ePHYMode   - PHY mode
*
* \retval
*
****************************************************************************/
void HAL_DP_PHY_SetPHYMode(DP_DeviceIDType  eDeviceId,
                           DP_PHYModeType   ePHYMode)
{
  HAL_DP_PhyPllFunctionTable *pFxnTable = &gDPPhyPllFxnTable[eDeviceId];

  if (NULL != pFxnTable->HAL_DP_PHY_SetPHYMode)
  {
    pFxnTable->HAL_DP_PHY_SetPHYMode(eDeviceId, ePHYMode);
  }

}

/****************************************************************************
*
** FUNCTION: HAL_DP_PHY_GetPLLStatus()
*/
/*!
* \DESCRIPTION
*           Get DP PLL status
*
* \param [in]     eDeviceId   - DP Device ID
* \param [out]    pbPLLLocked - TRUE is DP PLL is locked, otherwise FALSE
*
* \retval void
*
****************************************************************************/
void HAL_DP_PHY_GetPLLStatus(DP_DeviceIDType      eDeviceId,
                             bool32              *pbPLLLocked)
{
  HAL_DP_PhyPllFunctionTable *pFxnTable = &gDPPhyPllFxnTable[eDeviceId];

  if (NULL != pFxnTable->HAL_DP_PHY_GetPLLStatus)
  {
    pFxnTable->HAL_DP_PHY_GetPLLStatus(eDeviceId, pbPLLLocked);
  }

}

/****************************************************************************
*
** FUNCTION: HAL_DP_PHY_GetCalcPhyClksFreq()
*/
/*!
* \DESCRIPTION
*           Get calcualted phy clock frequencies for given SSC, Link parameters
*
* \param [in]     eDeviceId              - DP Device ID
* \param [in]     pPhyClksFreqCalcParams - Parameters required for calcualting phy clk values
* \param [out]    pCalcPhyClksFreq       - calcuated values of phy clocks
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType  HAL_DP_PHY_GetCalcPhyClksFreq(DP_DeviceIDType               eDeviceId,
                                                  HAL_DP_PhyClksFreqCalcParams *pPhyClksFreqCalcParams)
{
  HAL_MDSS_ErrorType          eStatus   = HAL_MDSS_STATUS_FAILED_NOT_SUPPORTED;
  HAL_DP_PhyPllFunctionTable *pFxnTable = &gDPPhyPllFxnTable[eDeviceId];

  if (NULL != pFxnTable->HAL_DP_PHY_GetCalcPhyClksFreq)
  {
    eStatus = pFxnTable->HAL_DP_PHY_GetCalcPhyClksFreq(eDeviceId, pPhyClksFreqCalcParams);
  }
  
  return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_DP_CalculatePhyFreq()
*/
/*!
* \DESCRIPTION
*           calcualte phy clock frequencies for given SSC, phy parameters
*
* \param  [in]     pPhyRateParams           - Phy setting related to rate parameters
* \param  [in]     pPhySSCParams            - Phy SSC settings
* \param [out]     pCalcPhyClksFreq         - calcalted phy clk values
*
* \retval HAL_MDSS_ErrorType
*
****************************************************************************/
HAL_MDSS_ErrorType  HAL_DP_CalculatePhyFreq(HAL_DP_Phy_RateParams        *pPhyRateParams,
                                            HAL_DP_Phy_SSCParams         *pSSCParams,
                                            HAL_DP_PhyClksFreq           *pCalcPhyClksFreq)
{
  HAL_MDSS_ErrorType          eStatus = HAL_MDSS_STATUS_SUCCESS;

  if ((NULL == pCalcPhyClksFreq) ||
      (NULL == pPhyRateParams)   ||
      (NULL == pSSCParams))
  {
    eStatus = HAL_MDSS_STATUS_FAILED_EXPECTED_NON_NULL_PTR;
  }
  else
  {
    double               dClkDivTxFreq = 0;
    double               dVcoFreq      = 0;
    uint32               uVcoDivClk    = 0;
    double               dHSClkDivSel  = 0;
    uint32               uVcoMode      = 0;
    uint32               uPllDivDec    = 0;
    uint32               uPllDivFrac   = 0;
    uint32               uSpreadAmount = 0;
    uint8                HsclkregValue = 0;
    uint8                uVcoDivregVal = 0;
     
    if (pPhyRateParams->uTunneledVCOTuneMap & 0x04)
    {
      uVcoMode = 1;
    }

    /* Formula for calculating the Vco div clock and link clock
        VcoDivClkFreq = (ClkDivTxFreq / VcoClkDiv);
        LinkClkFreq   = (ClkDivTxFreq / 10);
        ClkDivTxFreq  = (VcoFreq / HsclkDivSel);
    */

    /* Calculate VCO frequency */
    uPllDivDec  = pPhyRateParams->uDecStart;
    uPllDivFrac = (((uint32)pPhyRateParams->uDivFracStart3) << 16) + 
                  (((uint32)pPhyRateParams->uDivFracStart2) << 8) + 
                  ((uint32)pPhyRateParams->uDivFracStart1);    
    dVcoFreq    = 38.4 * 4 * (uPllDivDec + (((double)uPllDivFrac)/(double)(1<<20)));

    if (0 != pSSCParams->uSSCEnable)
    {
      uint32               uSscStepSize  = 0;
      uint32               uSscAdjPer    = 0;

      /* Calculate SSC spread uing formula
        spread_amount = (uint32)(1000000.0 * (ssc_per + 1) * ssc_step_size /
                                ((ssc_adj_per + 1) * ((double)pll_div_dec * pow(2, 20) + pll_div_frac)));
      */

      uSscAdjPer    = (uint32)pSSCParams->uAdjPer1;
      uSscStepSize  = (((uint32)pSSCParams->uStepSize2) << 8) + (uint32)pSSCParams->uStepSize1;

      uSpreadAmount = (uint32)((1000000.0 * (uSscAdjPer + 1) * uSscStepSize) / 
                                ((uSscAdjPer + 1) + ((((double)uPllDivDec) * (1<<20)) + uPllDivFrac)));
    }

    dVcoFreq = dVcoFreq * (1 - (uSpreadAmount / 2000000.0));

    /* Calcualte HSClk Div Sel */
    HsclkregValue = (uVcoMode == 0) ? (pPhyRateParams->uHsclkSel & 0x0F) : ((pPhyRateParams->uHsclkSel & 0xF0) >> 4);
    
    switch (HsclkregValue)
    {
      case 13: dHSClkDivSel = 10;  break;
      case 12: dHSClkDivSel = 8;   break;
      case 11:                  
      case 15: dHSClkDivSel = 6;   break;
      case 5:  dHSClkDivSel = 5;   break;
      case 4:  dHSClkDivSel = 4;   break;
      case 3:                   
      case 7:                   
      case 10:                  
      case 14: dHSClkDivSel = 3;   break;
      case 1:                   
      case 9:  dHSClkDivSel = 2;   break;
      case 2:  
      case 6:  dHSClkDivSel = 1.5; break;
      case 0:
      case 8:
      default: dHSClkDivSel = 1;   break;
    }

    uVcoDivregVal = pPhyRateParams->uPhyVcoDiv & 0x03;

    switch (uVcoDivregVal)
    {
      case 3:  uVcoDivClk = 8; break;
      case 2:  uVcoDivClk = 4; break;
      case 1:  uVcoDivClk = 2; break;
      case 0:
      default: uVcoDivClk = 6; break;
    }

    dClkDivTxFreq = dVcoFreq / dHSClkDivSel;

    pCalcPhyClksFreq->dVcoDivClkFreqMhz = dClkDivTxFreq / uVcoDivClk;
    pCalcPhyClksFreq->dLinkClkFreqMHz   = dClkDivTxFreq / 10;
  }
  
  return eStatus;
}

/****************************************************************************
*
** FUNCTION: HAL_DP_PHY_SelectPClockFrequencyTable()
*/
/*!
* \DESCRIPTION
*           Select the frequency table based on uPclkFreq
*
* \param [in]     eDeviceId - DP Device ID
* \param [in]     uLinkRate - Link rate
* \param [in]     uPclkFreq - VCO clock frequency
*
* \retval None
*
****************************************************************************/
void HAL_DP_PHY_SelectPClockFrequencyTable(DP_DeviceIDType eDeviceId,
                                           uint32          uLinkRate, 
                                           uint32          uPclkFreq)
{
  HAL_DP_PhyPllFunctionTable *pFxnTable = &gDPPhyPllFxnTable[eDeviceId];

  if (NULL != pFxnTable->HAL_DP_PHY_SelectPClockFrequencyTable)
  {
    pFxnTable->HAL_DP_PHY_SelectPClockFrequencyTable(eDeviceId, uLinkRate, uPclkFreq);
  }
}

#ifdef __cplusplus
}
#endif

