/**
 * @file:  SpmiTarget.c
 *
 * Copyright (c) 2013-2020, 2023 by Qualcomm Technologies Incorporated. All Rights Reserved.
 *
 * $DateTime: 2023/01/30 21:02:31 $
 * $Header: //components/dev/core.boot/6.1/syejare.core.boot.6.1.palawan_adding_3101/QcomPkg/Library/SPMILib/src/platform/target/lanai/SpmiTarget.c#1 $
 * $Change: 43194842 $
 * $Author: syejare $
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * * 06/24/19  Initial Version
 */
#include "SpmiHal.h"
#include "ChipInfo.h"
#include "SpmiTarget.h"



//******************************************************************************
// Macros / Definitions / Constants
//******************************************************************************

#define WDT_CFG_VAL  0x01
#define TLMM_PMIC_CLK_HDRV_PULL_CTL_ADDR   0x0F1B7000
#define TLMM_PMIC_DATA_HDRV_PULL_CTL_ADDR  0x0F1B8000

//******************************************************************************
// Implemented API Functions
//******************************************************************************

void SpmiTarget_PreInit(SpmiDevInfo *pDev)
{
  uint8 * base_addr = pDev->baseAddrs;
  
  SPMI_HWIO_OUT_MASK( HWIO_SPMI_CFG_REG_ADDR( base_addr, pDev->uDevIdx ), HWIO_SPMI_CFG_REG_SCLK_OE_EXTEND_BMSK, 1 << HWIO_SPMI_CFG_REG_SCLK_OE_EXTEND_SHFT);
  SPMI_HWIO_OUT_MASK( HWIO_SPMI_CFG_REG_ADDR( base_addr, pDev->uDevIdx ), HWIO_SPMI_CFG_REG_RPMH_CLK_REQ_EN_BMSK, 1 << HWIO_SPMI_CFG_REG_RPMH_CLK_REQ_EN_SHFT);
  
  //* Set TLMM HDRV PULL CTL for clock and data lines */
  //SPMI_HWIO_OUT(TLMM_PMIC_CLK_HDRV_PULL_CTL_ADDR, 0xF900);
  //SPMI_HWIO_OUT(TLMM_PMIC_DATA_HDRV_PULL_CTL_ADDR, 0x1F00);


  return;
}

