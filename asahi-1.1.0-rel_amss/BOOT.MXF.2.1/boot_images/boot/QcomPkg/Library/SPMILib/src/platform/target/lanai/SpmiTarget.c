/**
 * @file:  SpmiTarget.c
 *
 * Copyright (c) 2013 - 2024 Qualcomm Technologies, Inc.  All Rights Reserved. 
 *  Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 * $DateTime: 2024/04/02 23:00:31 $
 * $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/SPMILib/src/platform/target/lanai/SpmiTarget.c#1 $
 * $Change: 53083464 $
 * $Author: cirrusp4svc $
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
#define TLMM_PMIC_CLK_HDRV_PULL_CTL_ADDR   0x0F1D1000
#define TLMM_PMIC_DATA_HDRV_PULL_CTL_ADDR  0x0F1D2000
#define AOSS_TEST_BUS_CTRL_ADDR            0x0C260208

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

  SPMI_HWIO_OUT(AOSS_TEST_BUS_CTRL_ADDR, 0x40000000);

  return;
}

