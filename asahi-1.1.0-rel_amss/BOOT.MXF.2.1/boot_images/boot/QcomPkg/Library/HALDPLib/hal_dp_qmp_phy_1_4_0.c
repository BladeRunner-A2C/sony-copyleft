/*===========================================================================
  
  This file contains the programming for the DP QMP Phy/PLL (v1.4.0 5nm).

  Copyright (c) 2020 Qualcomm Technologies, Inc.
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
#include "hal_dp_phy_1_4_0_hwio.h"

/* -----------------------------------------------------------------------
** Macros
** ----------------------------------------------------------------------- */

#define DP_PREEMPHASIS_LEVEL_NUM                   4          /* Num of pre-emph levels               */
#define DP_VOLTAGESWING_LEVEL_NUM                  4          /* Num of swing levels                  */
#define DP_PREEMPH_VOLSWING_VALUE_LIST_4LVLS       16         /* Num of value pairs of PE & Sw        */ 
#define DP_PREEMPH_VOLSWING_MULTIPLIER_LIST_NUM    2          /* Num of multiplier values for PE & Sw */


#define HAL_DP_PLL_POLL_MAX_TRIES                  100        /*  100 iterations */
#define HAL_DP_PLL_POLL_INTERVAL                   500        /*  500 Us */


#define DP_PHY_REGREAD(_a_)                        in_dword((_a_))
#define DP_PHY_REGWRITE(_a_, _d_)                  out_dword((_a_), (_d_))

/* -----------------------------------------------------------------------
** Structure definitions
** ----------------------------------------------------------------------- */

/* 
 * DP QMP PHY rate dependent settings struct
 */
typedef struct {
  uint8 uHsclkSel;
  uint8 uLockCmpEn;
  uint8 uDecStart;
  uint8 uDivFracStart1;
  uint8 uDivFracStart2;
  uint8 uDivFracStart3;
  uint8 uCmnConfig;
  uint8 uLockCmp1;
  uint8 uLockCmp2;
  uint8 uPhyVcoDiv;
  uint8 uTunneledVCOTuneMap;
} DP_QmpPhy_RateParams;


/* 
 * DP QMP PHY SSC settings struct
 */
typedef struct {
  uint8 uAdjPer1;
  uint8 uSSCPer1;
  uint8 uSSCPer2;
  uint8 uStepSize1;
  uint8 uStepSize2;
} DP_QmpPhy_SSCParams;


/* 
 * DP QMP PHY HW settings structure
 */
typedef struct
{
  uint32                 uLinkRatePerLaneMbps;     // Desired link rate
  uint32                 uVcoDividedClkMhz;        // vco_divided_clk
  DP_QmpPhy_RateParams   sRateParams;              // Recommended settings
} DP_QmpPhy_HwSettingsType;


/* -----------------------------------------------------------------------
** Static Variables
** ----------------------------------------------------------------------- */


/* DP QMP PHY rate dependent PHY/PLL settings  */
DP_QmpPhy_HwSettingsType gPhySettings[] = {
  {1620,  810, {0x05, 0x04, 0x69, 0x00, 0x80, 0x07, 0x02, 0x6F, 0x08, 0x01, 0x02}},  // RBR at SVSL1
  {2700,  675, {0x03, 0x08, 0x69, 0x00, 0x80, 0x07, 0x02, 0x0F, 0x0E, 0x02, 0x02}},  // HBR at SVSL1
  {5400,  900, {0x01, 0x08, 0x8C, 0x00, 0x00, 0x0A, 0x02, 0x1F, 0x1C, 0x00, 0x06}},  // HBR2 at SVSL1
  {8100, 1350, {0x00, 0x08, 0x69, 0x00, 0x80, 0x07, 0x02, 0x2F, 0x2A, 0x00, 0x02}},  // HBR3 at Nominal
};

#define NUMBER_OF_DP_LINK_RATES_SUPPORTED    HAL_SIZEOF(gPhySettings)/(HAL_SIZEOF(DP_QmpPhy_HwSettingsType))


/* DP QMP PHY SSC settings */
DP_QmpPhy_SSCParams gSSCParams[] = {
  {0x00, 0x36, 0x01, 0x45, 0x06},     // RBR
  {0x00, 0x36, 0x01, 0x45, 0x06},     // HBR
  {0x00, 0x36, 0x01, 0x5C, 0x08},     // HBR2
  {0x00, 0x36, 0x01, 0x45, 0x06},     // HBR3
};


/* Pre-emphasis and Voltage swing combinations supported by hardware for HBR & RBR */
static HAL_DP_PeSwPairType aPeSwPair[DP_VOLTAGESWING_LEVEL_NUM][DP_PREEMPHASIS_LEVEL_NUM] =
{
  {{0x20, 0x28 }, {0x2E, 0x2F}, {0x35, 0x36}, {0x3B, 0x3F}}, /* SW0_PE0, SW0_PE1, SW0_PE2, SW0_PE3 */
  {{0x20, 0x31 }, {0x2E, 0x3E}, {0x35, 0x3F}, {0x00, 0x00}}, /* SW1_PE0, SW1_PE1, SW1_PE2  */
  {{0x20, 0x36 }, {0x2E, 0x3F}, {0x00, 0x00}, {0x00, 0x00}}, /* SW2_PE0, SW2_PE1  */  
  {{0x24, 0x3F }, {0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}}, /* SW3_PE0          */
};

/* Pre-emphasis and Voltage swing combinations supported by hardware for HBR2 & HBR3 */
static HAL_DP_PeSwPairType aPeSwPair_HBR2[DP_VOLTAGESWING_LEVEL_NUM][DP_PREEMPHASIS_LEVEL_NUM] =
{
  {{0x20, 0x22 }, {0x2C, 0x32}, {0x35, 0x36}, {0x3A, 0x3A}}, /* SW0_PE0, SW0_PE1, SW0_PE2, SW0_PE3 */
  {{0x22, 0x29 }, {0x2E, 0x39}, {0x36, 0x3F}, {0x00, 0x00}}, /* SW1_PE0, SW1_PE1, SW1_PE2  */
  {{0x22, 0x30 }, {0x31, 0x3F}, {0x00, 0x00}, {0x00, 0x00}}, /* SW2_PE0, SW2_PE1  */  
  {{0x24, 0x3F }, {0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}}, /* SW3_PE0          */
};


/* -----------------------------------------------------------------------
** Private Functions
** ----------------------------------------------------------------------- */

//-------------------------------------------------------------------------------------------------
//  HAL_DP_Qmp_GetRegBaseOffset
//
//  @brief
//      Helper function to get the register base offset for the phy
//
//  @params
//   [IN] eDeviceId
//       PHY device Id
//
//  @return
//      Offset
//-------------------------------------------------------------------------------------------------
static uintPtr HAL_DP_Qmp_GetRegBaseOffset(DP_DeviceIDType  eDeviceId)
{
  uintPtr uOffset = 0;

  switch (eDeviceId)
  {
    case DP_DEVICE_ID_ALT_MODE_0:
    {
      uOffset = 0;
      break;
    }
  
    case DP_DEVICE_ID_ALT_MODE_1:
    {
      uOffset = (AHB2PHY_2QUSB4PHY_USB43DP_COM_USB43DP_COM_USB4_USB3_DP_COM_REG_BASE - 
                 AHB2PHY_0QUSB4PHY_USB43DP_COM_USB43DP_COM_USB4_USB3_DP_COM_REG_BASE);
      break;
    }
  
    default:
    {
      uOffset        = 0;
      break;
    }
  }

  return uOffset;
}

//-------------------------------------------------------------------------------------------------
//  HAL_DP_Qmp_Phy_Poll_PhyReady
//
//  @brief
//      Check if PHY is ready
//
//  @params
//   [IN] eDeviceId
//       Device ID
//   [IN/OUT] uReadyMask
//           ready mask to check for
//
//  @return
//      HAL_MDSS_STATUS_SUCCESS if mask is set
//-------------------------------------------------------------------------------------------------
static HAL_MDSS_ErrorType HAL_DP_Qmp_Phy_Poll_PhyReady(DP_DeviceIDType eDeviceId,
                                                       uint32          uReadyMask)
{
  HAL_MDSS_ErrorType eStatus   = HAL_MDSS_MDP_STATUS_FAILED;
  uintPtr            uOffset   = HAL_DP_Qmp_GetRegBaseOffset(eDeviceId);
  uint32             uNumPolls = 0;
  uint32             uReg      = 0;

  for (uNumPolls = 0; uNumPolls < HAL_DP_PLL_POLL_MAX_TRIES; ++uNumPolls)
  {  
    uReg = DP_PHY_REGREAD(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_STATUS_ADDR);
    if ((uReadyMask & uReg) != 0)
    {
      eStatus = HAL_MDSS_STATUS_SUCCESS;
      break;
    }
    HAL_DP_SLEEP_US(HAL_DP_PLL_POLL_INTERVAL);
  }

  return eStatus;
}


//-------------------------------------------------------------------------------------------------
//  HAL_DP_PHY_Qmp_Pll_Poll_Cready
//
//  @brief
//      Check if PLL is ready
//
//  @params
//   [IN] eDeviceId
//       Device ID
//
//  @return
//      HAL_MDSS_STATUS_SUCCESS if mask is set
//-------------------------------------------------------------------------------------------------
static HAL_MDSS_ErrorType HAL_DP_PHY_Qmp_Pll_Poll_Cready(DP_DeviceIDType eDeviceId)
{
  HAL_MDSS_ErrorType eStatus   = HAL_MDSS_MDP_STATUS_FAILED;
  uintPtr            uOffset   = HAL_DP_Qmp_GetRegBaseOffset(eDeviceId);
  uint32             uNumPolls = 0;
  uint32             uReg      = 0;

  for (uNumPolls = 0; uNumPolls < HAL_DP_PLL_POLL_MAX_TRIES; ++uNumPolls)
  {  
    uReg = DP_PHY_REGREAD(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_C_READY_STATUS_ADDR);
    if ((HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_C_READY_STATUS_C_READY_BMSK & uReg) != 0)
    {
      eStatus = HAL_MDSS_STATUS_SUCCESS;
      break;
    }
    HAL_DP_SLEEP_US(HAL_DP_PLL_POLL_INTERVAL);
  }

  return eStatus;
}


//-------------------------------------------------------------------------------------------------
//  HAL_DP_Qmp_Phy_Pll_Config
//
//  @brief
//      Apply PLL settings based on link rate etc.
//
//  @params
//   [IN] uOffset
//      Register base offset
//   [IN] pDPPllConfigInfo
//      PLL Configuration
//
//  @return
//      HAL_MDSS_STATUS_SUCCESS if successful
//-------------------------------------------------------------------------------------------------
static HAL_MDSS_ErrorType HAL_DP_Qmp_Phy_Pll_Config(uintPtr                uOffset, 
                                                    HAL_DP_PllConfigType  *pDPPllConfigInfo)
{
  uint32                    uFreqIndex = 0;
  DP_QmpPhy_HwSettingsType *pSettings  = NULL;
  HAL_MDSS_ErrorType        eStatus    = HAL_MDSS_STATUS_FAILED_NOT_SUPPORTED;

  for (uFreqIndex = 0; uFreqIndex < NUMBER_OF_DP_LINK_RATES_SUPPORTED; ++uFreqIndex)
  {
    if ((gPhySettings[uFreqIndex].uLinkRatePerLaneMbps == pDPPllConfigInfo->uLinkRateMbps) &&
        (gPhySettings[uFreqIndex].uVcoDividedClkMhz    == pDPPllConfigInfo->uPixelClkMNDInputMhz))
    {
      pSettings = &gPhySettings[uFreqIndex];
      eStatus   = HAL_MDSS_STATUS_SUCCESS;
      break;
    }
  }

  if (pSettings != NULL)
  {
    DP_QmpPhy_RateParams *pRateParams = &pSettings->sRateParams;
    DP_QmpPhy_SSCParams  *pSSCParams  = &gSSCParams[uFreqIndex];
  
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_ADDR,          0x05);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SYSCLK_EN_SEL_ADDR,             0x3b);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SYS_CLK_CTRL_ADDR,              0x02);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_CLK_ENABLE1_ADDR,               0x0c);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_ADDR,         0x06);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_CLK_SELECT_ADDR,                0x30);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_HSCLK_SEL_ADDR,                 pRateParams->uHsclkSel);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_PLL_IVCO_ADDR,                  0x0f);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_LOCK_CMP_EN_ADDR,               pRateParams->uLockCmpEn);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_PLL_CCTRL_MODE0_ADDR,           0x36);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_PLL_RCTRL_MODE0_ADDR,           0x16);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_CP_CTRL_MODE0_ADDR,             0x06);

    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_DEC_START_MODE0_ADDR,           pRateParams->uDecStart);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_DIV_FRAC_START1_MODE0_ADDR,     pRateParams->uDivFracStart1);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_DIV_FRAC_START2_MODE0_ADDR,     pRateParams->uDivFracStart2);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_DIV_FRAC_START3_MODE0_ADDR,     pRateParams->uDivFracStart3);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_CMN_CONFIG_ADDR,                pRateParams->uCmnConfig);

    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE0_ADDR,     0x3f);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE0_ADDR,     0x00);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_VCO_TUNE_MAP_ADDR,              0x00);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_LOCK_CMP1_MODE0_ADDR,           pRateParams->uLockCmp1);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_LOCK_CMP2_MODE0_ADDR,           pRateParams->uLockCmp2);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_BG_TIMER_ADDR,                  0x0a);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_CORECLK_DIV_MODE0_ADDR,         0x0a);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_VCO_TUNE_CTRL_ADDR,             0x00);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_ADDR,       0x15);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_CORE_CLK_EN_ADDR,               0x1f);

    // SSC config
    if (HAL_DP_PLLCONFIG_FLAG_SSC & pDPPllConfigInfo->uFlags)
    {
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_EN_CENTER_ADDR,           0x01);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_ADJ_PER1_ADDR,            pSSCParams->uAdjPer1);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_ADJ_PER2_ADDR,            0x00);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_PER1_ADDR,                pSSCParams->uSSCPer1);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_PER2_ADDR,                pSSCParams->uSSCPer2);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0_ADDR,    pSSCParams->uStepSize1);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0_ADDR,    pSSCParams->uStepSize2);        
    }
    else
    {
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_EN_CENTER_ADDR,           0x00);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_ADJ_PER1_ADDR,            0x00);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_ADJ_PER2_ADDR,            0x00);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_PER1_ADDR,                0x00);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_PER2_ADDR,                0x00);      
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0_ADDR,    0x00);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0_ADDR,    0x00);        
    }

    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_VCO_DIV_ADDR,                        pRateParams->uPhyVcoDiv);
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  HAL_DP_Tunneled_Qmp_Phy_Pll_Config
//
//  @brief
//      Apply DP Tunneling PLL settings based on link rate etc.
//
//  @params
//   [IN] uOffset
//      Register base offset
//   [IN] pDPPllConfigInfo
//      PLL Configuration
//
//  @return
//      HAL_MDSS_STATUS_SUCCESS if successful
//-------------------------------------------------------------------------------------------------
static HAL_MDSS_ErrorType HAL_DP_Tunneled_Qmp_Phy_Pll_Config(uintPtr                uOffset, 
                                                             HAL_DP_PllConfigType  *pDPPllConfigInfo)
{
  uint32                    uFreqIndex = 0;
  DP_QmpPhy_HwSettingsType *pSettings  = NULL;
  HAL_MDSS_ErrorType        eStatus    = HAL_MDSS_STATUS_FAILED_NOT_SUPPORTED;
  
  for (uFreqIndex = 0; uFreqIndex < NUMBER_OF_DP_LINK_RATES_SUPPORTED; ++uFreqIndex)
  {
    if ((gPhySettings[uFreqIndex].uLinkRatePerLaneMbps == pDPPllConfigInfo->uLinkRateMbps) &&
        (gPhySettings[uFreqIndex].uVcoDividedClkMhz    == pDPPllConfigInfo->uPixelClkMNDInputMhz))
    {
      pSettings = &gPhySettings[uFreqIndex];
      eStatus   = HAL_MDSS_STATUS_SUCCESS;
      break;
    }
  }

  if (pSettings != NULL)
  {
    DP_QmpPhy_RateParams *pRateParams = &pSettings->sRateParams;
    DP_QmpPhy_SSCParams  *pSSCParams  = &gSSCParams[uFreqIndex];

    if (HAL_DP_PLLCONFIG_FLAG_SSC & pDPPllConfigInfo->uFlags)
    {
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_EN_CENTER_ADDR, 0x01);
    }
    else
    {
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_EN_CENTER_ADDR, 0x00);
    }

    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_PER1_ADDR,              0x36);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_PER2_ADDR,              0x01);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_CP_CTRL_MODE0_ADDR,         0x06);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_CP_CTRL_MODE1_ADDR,         0x06);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_PLL_RCTRL_MODE0_ADDR,       0x16);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_PLL_RCTRL_MODE1_ADDR,       0x16);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_PLL_CCTRL_MODE0_ADDR,       0x36);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_PLL_CCTRL_MODE1_ADDR,       0x36);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SYSCLK_EN_SEL_ADDR,         0x3b);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_LOCK_CMP_EN_ADDR,           pRateParams->uLockCmpEn);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_DEC_START_MODE0_ADDR,       0x69);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_DEC_START_MODE1_ADDR,       0x8c);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_DIV_FRAC_START1_MODE0_ADDR, 0x00);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_DIV_FRAC_START2_MODE0_ADDR, 0x80);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_DIV_FRAC_START3_MODE0_ADDR, 0x07);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_DIV_FRAC_START1_MODE1_ADDR, 0x00);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_DIV_FRAC_START2_MODE1_ADDR, 0x00);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_DIV_FRAC_START3_MODE1_ADDR, 0x0a);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_CORECLK_DIV_MODE0_ADDR,     0x0a);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_CORECLK_DIV_MODE1_ADDR,     0x0a);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_CMN_CONFIG_ADDR,            0x02);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_CORE_CLK_EN_ADDR,           0x30);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_CLK_ENABLE1_ADDR,           0x0c);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_BG_TIMER_ADDR,              0x0a);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE0_ADDR, 0x3f);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE0_ADDR, 0x00);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE1_ADDR, 0x3f);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE1_ADDR, 0x00);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_CLK_SELECT_ADDR,            0x30);

    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0_ADDR,  pSSCParams->uStepSize1);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0_ADDR,  pSSCParams->uStepSize2);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_LOCK_CMP1_MODE0_ADDR,       pRateParams->uLockCmp1);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_LOCK_CMP2_MODE0_ADDR,       pRateParams->uLockCmp2);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_VCO_TUNE_MAP_ADDR,          pRateParams->uTunneledVCOTuneMap);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_VCO_DIV_ADDR,                    pRateParams->uPhyVcoDiv);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_HSCLK_SEL_ADDR,             pRateParams->uHsclkSel);
  }

  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  HAL_DP_Qmp_Phy_PllOnlyConfig
//
//  @brief
//      Helper function to configure only the PLL (No lane config)
//
//  @params
//   [IN] eDeviceId
//       Device Id
//   [IN] pDPPllConfigInfo
//       Config info
//   [IN] eDeviceDPMode
//       DP Device Mode
//
//  @return
//       HAL_MDSS_STATUS_SUCCESS if successful
//-------------------------------------------------------------------------------------------------
static HAL_MDSS_ErrorType HAL_DP_Qmp_Phy_PllOnlyConfig(DP_DeviceIDType       eDeviceId,
                                                       HAL_DP_PllConfigType *pDPPllConfigInfo,
                                                       DP_DeviceModeType     eDeviceDPMode)
{
  HAL_MDSS_ErrorType    eStatus     = HAL_MDSS_STATUS_SUCCESS;
  uintPtr               uOffset     = HAL_DP_Qmp_GetRegBaseOffset(eDeviceId);

  // USB4 DP Tunneling case
  if (DP_DEVICE_MODETYPE_TUNNELING == eDeviceDPMode)
  {
    // Release pwrdn for DP analog in tunneling mode
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL_ADDR,               0x79);

    /* Configure QMP PLL for DP Tunneling case */
    eStatus = HAL_DP_Tunneled_Qmp_Phy_Pll_Config(uOffset, pDPPllConfigInfo);
    
    if (HAL_MDSS_STATUS_SUCCESS == eStatus)
    {
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_TX2_TX3_LANE_CTL_ADDR,   0x01);

      /* PLL reset sequence */
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR,                0x04);
      HAL_DP_SLEEP_MS(1);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR,                0x00);
      HAL_DP_SLEEP_MS(1);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR,                0x08);
      HAL_DP_SLEEP_MS(1);

      // Check if power up is done
      eStatus = HAL_DP_PHY_Qmp_Pll_Poll_Cready(eDeviceId);
    }
  }
  else
  {
    // Power up PLL, L0/1/2/3 off, AUX off, ungated all clocks, power up all analog blocks
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL_ADDR,               0x61); 
  
    /* Configure QMP PLL */
    eStatus = HAL_DP_Qmp_Phy_Pll_Config(uOffset, pDPPllConfigInfo);
  
    if (HAL_MDSS_STATUS_SUCCESS == eStatus)
    {
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_TX0_TX1_LANE_CTL_ADDR,     0x01);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_TX2_TX3_LANE_CTL_ADDR,     0x01);
  
      /* PLL reset sequence */
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR,                  0x01);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR,                  0x05);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR,                  0x01);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR,                  0x09);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_RESETSM_CNTRL_ADDR,   0x20);
    
      // Check if power up is done
      eStatus = HAL_DP_PHY_Qmp_Pll_Poll_Cready(eDeviceId);
    }
  }

  return eStatus;
}


/* -----------------------------------------------------------------------
** Public Functions
** ----------------------------------------------------------------------- */


//-------------------------------------------------------------------------------------------------
//  HAL_DP_Qmp_1_4_0_PHY_GetPLLStatus
//
//  @brief
//      Get PLL lock status
//
//  @params
//   [IN] eDeviceId
//       Device Id
//   [OUT] pbPLLLocked
//       TRUE : PLL locked, FALSE: PLL not locked
//
//  @return
//       None
//-------------------------------------------------------------------------------------------------
void HAL_DP_Qmp_1_4_0_PHY_GetPLLStatus(DP_DeviceIDType eDeviceId, bool32 *pbPLLLocked)
{
  if (NULL != pbPLLLocked)
  {
    uintPtr  uOffset = HAL_DP_Qmp_GetRegBaseOffset(eDeviceId);
    uint32   uStatus = DP_PHY_REGREAD(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_STATUS_ADDR) & 
                                      HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_STATUS_TSYNC_DONE_BMSK;

    *pbPLLLocked = (0 == uStatus) ? FALSE : TRUE;
  }
}


//-------------------------------------------------------------------------------------------------
//  HAL_DP_Qmp_1_4_0_PHY_Power
//
//  @brief
//      Power on/off DP PHY HW blocks
//
//  @params
//   [IN] eDeviceId
//       Device Id
//   [IN] bPower on
//       TRUE : power on, FALSE: power off
//   [IN] uModules
//       HW modules to power on/off
//
//  @return
//      HAL_MDSS_STATUS_SUCCESS if power up/down is done successfully
//-------------------------------------------------------------------------------------------------
HAL_MDSS_ErrorType HAL_DP_Qmp_1_4_0_PHY_Power(DP_DeviceIDType        eDeviceId,
                                              bool32                 bPowerOn,
                                              DP_PHYPowerModuleType  uModules)
{
  HAL_MDSS_ErrorType eStatus = HAL_MDSS_STATUS_SUCCESS;
  uintPtr  uOffset           = HAL_DP_Qmp_GetRegBaseOffset(eDeviceId);
  uint32   uRegVal           = 0;

  if (FALSE == bPowerOn)
  {
    if ((DP_PHY_POWER_PLL | DP_PHY_POWER_PHY) & uModules)
    {
      uRegVal = DP_PHY_REGREAD(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL_ADDR);

      if (uModules & DP_PHY_POWER_PHY)
      {
        /* Power down PHY */
        uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL, PWRDN_B, 0);
        uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL, PSR_PWRDN, 1);
        uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL, AUX_PWRDN_B, 0);
        uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL, LANE_0_1_PWRDN_B, 0);
        uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL, LANE_2_3_PWRDN_B, 0);
        uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL, DP_CLAMP_EN_B, 0);
        uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL, SPARE_PWRDN_B, 0);
      }

      if (uModules & DP_PHY_POWER_PLL)
      {
        /* Power down PLL */
        uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL, PLL_PWRDN_B, 0);
      }

      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL_ADDR, uRegVal);
    }

    if (uModules & DP_PHY_POWER_PHY_TIMING_FIFO)
    {
      /* Disable retimer */
      uRegVal = DP_PHY_REGREAD(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR);
      uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG, RETIMING_ENABLE, 0);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR, uRegVal);
    }
  }
  else
  {
    if ((DP_PHY_POWER_PLL | DP_PHY_POWER_PHY) & uModules)
    {
      uRegVal = DP_PHY_REGREAD(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL_ADDR);
          
      if (uModules & DP_PHY_POWER_PHY)
      {
        /* Power up PHY */
        uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL, PWRDN_B, 1);
        uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL, PSR_PWRDN, 0);
        uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL, AUX_PWRDN_B, 1);
        uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL, LANE_0_1_PWRDN_B, 1);
        uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL, LANE_2_3_PWRDN_B, 1);
        uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL, DP_CLAMP_EN_B, 1);
        uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL, SPARE_PWRDN_B, 0);
      }

      if (uModules & DP_PHY_POWER_PLL)
      {
        /* Power up PLL */
        uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL, PLL_PWRDN_B, 1);
      }

      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL_ADDR, uRegVal);

      if (uModules & DP_PHY_POWER_PLL)
      {
        /* PLL reset sequence */
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR,                0x01);
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR,                0x05);
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR,                0x01);
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR,                0x09);
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_RESETSM_CNTRL_ADDR, 0x20);
      
        /* Poll C_READY status */
        eStatus = HAL_DP_PHY_Qmp_Pll_Poll_Cready(eDeviceId);
        
        if (HAL_MDSS_STATUS_SUCCESS != eStatus)
        {
          DP_LOG_MESSAGE_WARN("HAL_DP_Qmp_1_4_0_PHY_Power: Polling C_READY failed for DP:%d\n", eDeviceId);
        }
      
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR, 0x19);
      }
      
      if (uModules & DP_PHY_POWER_PHY)
      {
        /* Poll for PHY ready */                  
        eStatus = HAL_DP_Qmp_Phy_Poll_PhyReady(eDeviceId, HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_STATUS_PHY_READY_BMSK);
        
        if (HAL_MDSS_STATUS_SUCCESS != eStatus)
        {
          DP_LOG_MESSAGE_WARN("HAL_DP_Qmp_1_4_0_PHY_Power: Polling PHY_READY failed for DP:%d\n", eDeviceId);
        }
      }
    }

    if (uModules & DP_PHY_POWER_PHY_TIMING_FIFO)
    {
      /* Enable retimer */
      uRegVal = DP_PHY_REGREAD(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR);
      uRegVal = HWIO_OUT_FLD(uRegVal, AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG, RETIMING_ENABLE, 1);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR, uRegVal);
    }
  }

  return eStatus;
}


//-------------------------------------------------------------------------------------------------
//  HAL_DP_Qmp_1_4_0_PHY_GetMaxPeSwLevel
//
//  @brief
//      Get the swing and Pre-emphasis level supported by hardware
//
//  @params
//   [IN] eDeviceId
//       PHY device Id
//   [OUT] uMaxPreemphLvl
//        Max pre-emphasis value supported
//   [OUT] uMaxVoltSwingLvl
//        Max swing value supported
//
//  @return
//      None
//-------------------------------------------------------------------------------------------------
void HAL_DP_Qmp_1_4_0_PHY_GetMaxPeSwLevel(DP_DeviceIDType  eDeviceId,
                                          uint32          *uMaxPreemphLvl,
                                          uint32          *uMaxVoltSwingLvl)
{
  *uMaxPreemphLvl   = DP_PREEMPHASIS_LEVEL_NUM - 1;
  *uMaxVoltSwingLvl = DP_VOLTAGESWING_LEVEL_NUM - 1;
}


//-------------------------------------------------------------------------------------------------
//  HAL_DP_Qmp_1_4_0_PHY_SetupPeSw
//
//  @brief
//      Set the swing and Pre-emphasis level passed if valid
//
//  @params
//   [IN] eDeviceId
//       PHY device Id
//   [IN] eDeviceDPMode
//       DP Device Mode
//   [IN/OUT] pPeSwConfig
//          Pointer to Swing/Pre-emphasis configuration to be applied
//
//  @return
//      HAL_MDSS_STATUS_SUCCESS if value applied
//-------------------------------------------------------------------------------------------------
HAL_MDSS_ErrorType HAL_DP_Qmp_1_4_0_PHY_SetupPeSw(DP_DeviceIDType        eDeviceId,
                                                  DP_DeviceModeType      eDeviceDPMode,
                                                  HAL_DP_PeSwConfigType *pPeSwConfig)
{
  HAL_MDSS_ErrorType  eStatus  = HAL_MDSS_STATUS_FAILED_NOT_SUPPORTED;
  uintPtr             uOffset  = HAL_DP_Qmp_GetRegBaseOffset(eDeviceId);

  pPeSwConfig->bPreemphNotSupported = FALSE;
  pPeSwConfig->bSwingNotsupported   = FALSE;

  if (pPeSwConfig->uPreemphasisLevel >= DP_PREEMPHASIS_LEVEL_NUM)
  {
    pPeSwConfig->bPreemphNotSupported = TRUE;
  }
  else if (pPeSwConfig->uLaneSwingLevel >= DP_VOLTAGESWING_LEVEL_NUM)
  {
    pPeSwConfig->bSwingNotsupported   = TRUE;
  }
  else
  {
    uint32 uPreEmphasisReg  = 0;
    uint32 uVoltageSwingReg = 0;

    // uConfigDataLength if 16, indicates 16 override value pairs of Pe-Sw
    if (DP_PREEMPH_VOLSWING_VALUE_LIST_4LVLS == pPeSwConfig->uConfigDataLength)
    {
      uPreEmphasisReg  = pPeSwConfig->aOverrideValueLUT[pPeSwConfig->uPreemphasisLevel][pPeSwConfig->uLaneSwingLevel].uPreEmphasis;
      uVoltageSwingReg = pPeSwConfig->aOverrideValueLUT[pPeSwConfig->uPreemphasisLevel][pPeSwConfig->uLaneSwingLevel].uVoltageSwing;
    }
    else 
    {
      switch (pPeSwConfig->uLinkRateKhz)
      {
        case HAL_DP_LINK_RATE_KHZ_PER_LANE_810MBps:
        case HAL_DP_LINK_RATE_KHZ_PER_LANE_540MBps:
        {
          // HBR2 or HBR3
          uPreEmphasisReg  = aPeSwPair_HBR2[pPeSwConfig->uLaneSwingLevel][pPeSwConfig->uPreemphasisLevel].uPreEmphasis;
          uVoltageSwingReg = aPeSwPair_HBR2[pPeSwConfig->uLaneSwingLevel][pPeSwConfig->uPreemphasisLevel].uVoltageSwing;
          break;
        }
        case HAL_DP_LINK_RATE_KHZ_PER_LANE_270MBps:
        case HAL_DP_LINK_RATE_KHZ_PER_LANE_162MBps:
        default:
        {
          // HBR or RBR
          uPreEmphasisReg  = aPeSwPair[pPeSwConfig->uLaneSwingLevel][pPeSwConfig->uPreemphasisLevel].uPreEmphasis;
          uVoltageSwingReg = aPeSwPair[pPeSwConfig->uLaneSwingLevel][pPeSwConfig->uPreemphasisLevel].uVoltageSwing;
          break;
        }
      }
      
      // uConfigDataLength if 2, indicates 2 boost/reduce multiplier values for our default values' LUT only. 
      // Index 1 is the multiplier for Pre-Emphasis value and index 2 is the multiplier for Swing Voltage.
      if (DP_PREEMPH_VOLSWING_MULTIPLIER_LIST_NUM == pPeSwConfig->uConfigDataLength)
      {
        if (pPeSwConfig->aValueMultiplierList[0] != 0)
        {
          uPreEmphasisReg = HALDPPHY_CEIL((uPreEmphasisReg * pPeSwConfig->aValueMultiplierList[0]), 100);
        }
        if (pPeSwConfig->aValueMultiplierList[1] != 0)
        {
          uVoltageSwingReg = HALDPPHY_CEIL((uVoltageSwingReg * pPeSwConfig->aValueMultiplierList[1]), 100);
        }
      }
    }

    if (0 == uPreEmphasisReg)
    {
      pPeSwConfig->bSwingNotsupported   = TRUE;
    }
    else
    {
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_TX_DRV_LVL_ADDR,       uVoltageSwingReg);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_TX_EMP_POST1_LVL_ADDR, uPreEmphasisReg);

      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_TX_DRV_LVL_ADDR,       uVoltageSwingReg);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_TX_EMP_POST1_LVL_ADDR, uPreEmphasisReg);

      eStatus = HAL_MDSS_STATUS_SUCCESS;
    }
  }

  return eStatus;
}


//-------------------------------------------------------------------------------------------------
//  HAL_DP_Qmp_1_4_0_PHY_Config
//
//  @brief
//      Configure the QMP PHY
//
//  @params
//   [IN] eDeviceId
//       PHY device Id
//   [IN] pDPPllConfigInfo
//       Config info
//   [IN] eDeviceDPMode
//       DP Device Mode
//
//  @return
//      TRUE if configuration is successful and PHY is ready to transmit data
//-------------------------------------------------------------------------------------------------
bool32 HAL_DP_Qmp_1_4_0_PHY_Config(DP_DeviceIDType       eDeviceId,
                                   HAL_DP_PllConfigType *pDPPllConfigInfo,
                                   DP_DeviceModeType     eDeviceDPMode)
{
  bool32   bStatus  = TRUE;
  uintPtr  uOffset  = HAL_DP_Qmp_GetRegBaseOffset(eDeviceId);
  
  if (HAL_DP_PLLCONFIG_FLAG_PLL & pDPPllConfigInfo->uFlags)
  {
    // Configure PLL only
    if (HAL_MDSS_STATUS_SUCCESS != HAL_DP_Qmp_Phy_PllOnlyConfig(eDeviceId, pDPPllConfigInfo, eDeviceDPMode))
    {
      bStatus = FALSE;
    }
  }
  else
  {
    bool32                 bPortSelect = !pDPPllConfigInfo->bInvertedPlug;    
    HAL_DP_PeSwConfigType  sPeSwConfig;

    /*
     * PHY Reset and port select config (for DP mode) 
     * In DP-USB concurrency mode, below registers are configured by the USB Driver 
     */
    if (0 == (pDPPllConfigInfo->uFlags & HAL_DP_PLLCONFIG_FLAG_DPUSB_CONCURRENCY))
    {
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_COM_TYPEC_CTRL_ADDR, (bPortSelect ? 0x0B : 0x0A));
  
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_COM_SWI_CTRL_ADDR,         0x00);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_COM_SW_RESET_ADDR,         0x00);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_COM_POWER_DOWN_CTRL_ADDR,  0x01);
    }
    
    if (4 == pDPPllConfigInfo->uNumLanes)
    {
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL_ADDR, 0x7d);
    }
    else
    { 
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL_ADDR, (bPortSelect ? 0x6d : 0x75));
    }
        
    /* Configure QMP PLL */
    if (HAL_DP_Qmp_Phy_Pll_Config(uOffset, pDPPllConfigInfo) != HAL_MDSS_STATUS_SUCCESS)
    {
      bStatus = FALSE;
    }
        
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_MODE_ADDR, (bPortSelect ? 0x5c : 0x4c));

    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_TX0_TX1_LANE_CTL_ADDR, 0x05);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_TX2_TX3_LANE_CTL_ADDR, 0x05);
    
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_VMODE_CTRL1_ADDR,                0x40);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_ADDR,     0x00);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_INTERFACE_SELECT_ADDR,           0xFF);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_ADDR,              0x0F);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_RESET_TSYNC_EN_ADDR,             0x03);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_ADDR,           0x0F);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_ADDR, 0x00);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_TX_ADDR,    0x11);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_RX_ADDR,    0x11);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_TX_BAND_ADDR,                    0x01);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_LANE_MODE_3_ADDR,                0x51);
    
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_VMODE_CTRL1_ADDR,                0x40);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_ADDR,     0x00);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_INTERFACE_SELECT_ADDR,           0xFF);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_ADDR,              0x0F);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_RESET_TSYNC_EN_ADDR,             0x03);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_ADDR,           0x0F);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_ADDR, 0x00);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_TX_ADDR,    0x11);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_RX_ADDR,    0x11);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_TX_BAND_ADDR,                    0x01);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_LANE_MODE_3_ADDR,                0x51);
        
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR,                0x01);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR,                0x05);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR,                0x01);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR,                0x09);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_RESETSM_CNTRL_ADDR, 0x20);
    
    //Check if power up is done
    if (HAL_DP_PHY_Qmp_Pll_Poll_Cready(eDeviceId) != HAL_MDSS_STATUS_SUCCESS)
    {
      bStatus = FALSE;
    }   
        
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR, 0x19);      
  
    if (HAL_DP_Qmp_Phy_Poll_PhyReady(eDeviceId, HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_STATUS_TSYNC_DONE_BMSK) != HAL_MDSS_STATUS_SUCCESS)
    {
      bStatus = FALSE;
    }
        
    if (4 == pDPPllConfigInfo->uNumLanes)
    { 
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_ADDR,   0x3F);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_ADDR,         0x10);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_ADDR,   0x3F);
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_ADDR,         0x10);
    }
    else if (2 == pDPPllConfigInfo->uNumLanes)
    { 
      if (bPortSelect)
      {
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_ADDR, 0x3F);
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_ADDR,       0x10);
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_ADDR, 0x15);
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_ADDR,       0x10);
      }
      else
      {        
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_ADDR, 0x15);
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_ADDR,       0x10);
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_ADDR, 0x3F);
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_ADDR,       0x10);
      }     
    }
    else if (1 == pDPPllConfigInfo->uNumLanes)
    {
      if (bPortSelect)        
      {
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_ADDR, 0x3e);
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_ADDR,       0x13);
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_ADDR, 0x15);
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_ADDR,       0x10);
      }
      else
      {
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_ADDR, 0x15);
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_ADDR,       0x10);
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_ADDR, 0x3e);
        DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_ADDR,       0x13);
      }
    }
        
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXA_TX_POL_INV_ADDR,  0x0a);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_QSERDES_TXB_TX_POL_INV_ADDR,  0x0a);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR,                   0x18);
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_CFG_ADDR,                   0x19);

    if (HAL_DP_Qmp_Phy_Poll_PhyReady(eDeviceId, HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_STATUS_TSYNC_DONE_BMSK) != HAL_MDSS_STATUS_SUCCESS)
    {
      bStatus = FALSE;
    }       
  
    // Configure pre-emphasis & driver strength - these may be changed during link training  
    sPeSwConfig.uLaneSwingLevel   = pDPPllConfigInfo->uVoltSwingLevel;
    sPeSwConfig.uPreemphasisLevel = pDPPllConfigInfo->uPreemphasisLevel;
    HAL_DP_Qmp_1_4_0_PHY_SetupPeSw(eDeviceId, DP_DEVICE_MODETYPE_ALTMODE, &sPeSwConfig);
  }

  if (!bStatus)
  {
    /* Requested settings not supported or config failed : Power down */
    DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL_ADDR, 0x02);
  }

  return bStatus;
}


//-------------------------------------------------------------------------------------------------
//  HAL_DP_Qmp_1_4_0_PHY_AUX_Init
//
//  @brief
//      Initialize AUX settings
//
//  @params
//   [IN] eDeviceId
//       PHY device Id
//   [IN] eDeviceDPMode
//       DP Device Mode
//
//  @return
//      None
//-------------------------------------------------------------------------------------------------
void HAL_DP_Qmp_1_4_0_PHY_AUX_Init(DP_DeviceIDType eDeviceId, DP_DeviceModeType eDeviceDPMode)
{
  UNREFERENCED_PARAMETER(eDeviceDPMode);

  uintPtr               uOffset     = HAL_DP_Qmp_GetRegBaseOffset(eDeviceId);

  DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL_ADDR,   0x02);
  DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_PD_CTL_ADDR,   0x7D);

  DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_ADDR, 0x15);

  DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_AUX_CFG1_ADDR, 0x13);
  DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_AUX_CFG2_ADDR, 0x26);
  DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_AUX_CFG3_ADDR, 0x00);
  DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_AUX_CFG4_ADDR, 0x0A);
  DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_AUX_CFG5_ADDR, 0x26);
  DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_AUX_CFG6_ADDR, 0x0A);
  DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_AUX_CFG7_ADDR, 0x03);
  DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_AUX_CFG8_ADDR, 0xB7);
  DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_AUX_CFG9_ADDR, 0x03);

  // Disable interrupts
  DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_DP_DP_PHY_AUX_INTERRUPT_MASK_ADDR, 0x00);
}


//-------------------------------------------------------------------------------------------------
//  HAL_DP_Qmp_1_4_0_PhyFxnsInit
//
//  @brief
//      Set PHY mode (not applicable for USB4)
//
//  @params
//   [IN/OUT] ePHYMode
//           PHY mode to set
//
//  @return
//      None
//-------------------------------------------------------------------------------------------------
void HAL_DP_Qmp_1_4_0_PHY_SetPHYMode(DP_DeviceIDType  eDeviceId,
                                     DP_PHYModeType   ePHYMode)
{
  uintPtr uOffset = HAL_DP_Qmp_GetRegBaseOffset(eDeviceId);

  switch (ePHYMode)
  {
    case DP_PHY_MODE_USB_DATA:
    {
      // USB3 enabled, DP disabled
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_COM_PHY_MODE_CTRL_ADDR, 0x01);
      break;
    }

    case DP_PHY_MODE_DP:
    {
      // USB3 disabled, DP enabled
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_COM_PHY_MODE_CTRL_ADDR, 0x02);
      break;
    }

    case DP_PHY_MODE_CONCURRENCY:
    {
      // USB3 and DP enabled concurrently
      DP_PHY_REGWRITE(uOffset + HWIO_AHB2PHY_0QUSB4PHY_USB43DP_COM_PHY_MODE_CTRL_ADDR, 0x03);
      break;
    }

    default:
    {
      break;
    }
  }
}

/****************************************************************************
*
** FUNCTION: HAL_DP_Qmp_1_4_0_PHY_GetCalcPhyClksFreq()
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
HAL_MDSS_ErrorType  HAL_DP_Qmp_1_4_0_PHY_GetCalcPhyClksFreq(DP_DeviceIDType               eDeviceId,
                                                            HAL_DP_PhyClksFreqCalcParams *pPhyClksFreqCalcParams)
{
  HAL_MDSS_ErrorType        eStatus    = HAL_MDSS_STATUS_SUCCESS;
  DP_QmpPhy_HwSettingsType *pSettings  = NULL;
  uint32                    uFreqIndex;

  if (NULL == pPhyClksFreqCalcParams)
  {
    eStatus = HAL_MDSS_STATUS_FAILED_EXPECTED_NON_NULL_PTR;
  }
  else
  {
    for (uFreqIndex = 0; uFreqIndex < NUMBER_OF_DP_LINK_RATES_SUPPORTED; ++uFreqIndex)
    {
      if ((gPhySettings[uFreqIndex].uLinkRatePerLaneMbps == pPhyClksFreqCalcParams->uLinkRateMbps) &&
          (gPhySettings[uFreqIndex].uVcoDividedClkMhz    == pPhyClksFreqCalcParams->uVcoDivClkFreqMHz))
      {
        pSettings = &gPhySettings[uFreqIndex];
        break;
      }
    }

    if (NULL == pSettings)
    {
      eStatus = HAL_MDSS_STATUS_FAILED_NO_HW_SUPPORT;
    }
  }
  return eStatus;
}

//-------------------------------------------------------------------------------------------------
//  HAL_DP_Qmp_1_4_0_PhyFxnsInit
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
void HAL_DP_Qmp_1_4_0_PhyFxnsInit(HAL_DP_PhyPllFunctionTable *pFxnTable)
{
  pFxnTable->HAL_DP_PHY_AUX_Init        = HAL_DP_Qmp_1_4_0_PHY_AUX_Init;  
  pFxnTable->HAL_DP_PHY_SetPHYMode      = HAL_DP_Qmp_1_4_0_PHY_SetPHYMode;
  pFxnTable->HAL_DP_PHY_Config          = HAL_DP_Qmp_1_4_0_PHY_Config;
  pFxnTable->HAL_DP_PHY_SetupPeSw       = HAL_DP_Qmp_1_4_0_PHY_SetupPeSw;
  pFxnTable->HAL_DP_PHY_GetMaxPeSwLevel = HAL_DP_Qmp_1_4_0_PHY_GetMaxPeSwLevel;
  pFxnTable->HAL_DP_PHY_Power           = HAL_DP_Qmp_1_4_0_PHY_Power;
  pFxnTable->HAL_DP_PHY_GetPLLStatus    = HAL_DP_Qmp_1_4_0_PHY_GetPLLStatus;  
  pFxnTable->HAL_DP_PHY_GetCalcPhyClksFreq  = HAL_DP_Qmp_1_4_0_PHY_GetCalcPhyClksFreq;
}


#ifdef __cplusplus
}
#endif

