/*
==============================================================================

FILE:         ClockTargetBSP.c

DESCRIPTION:
  This file contains the Target Specific functionality (and all misc api's).
  
==============================================================================

$Header: //components/dev/core.boot/6.1/arajashe.core.boot.6.1.milosuefi/QcomPkg/SocPkg/Kailua/Library/ClockLib/ClockTarget.c#1 $

==============================================================================
            Copyright (c) 2021, 2022, 2023 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================

*/


/*=========================================================================
      Include Files
==========================================================================*/
#include "ClockApps.h"
#include "Library/ClockCoreLib/inc/ClockDriverImage.h"
#include "HALhwio.h"
#include "HALclkHWIO.h"
#include "Library/HALclkGeneric.h"
#include "busywait.h"

/*=========================================================================
      Macros
==========================================================================*/



/*=========================================================================
      Externals
==========================================================================*/
extern ClockAppsBSPType ClockAppsBSP;
extern ClockAppsCtxtType ClockAppsCtxt;

/*=========================================================================
      Prototypes
==========================================================================*/


/*=========================================================================
      Type Definitions
==========================================================================*/



/*=========================================================================
      Data Declarations
==========================================================================*/

/* =========================================================================
**  Function : Clock_InitTarget
** =========================================================================*/
/*
  See ClockApps.h
*/
ClockResult Clock_InitTarget
(
  void
)
{
  ClockResult eResult = CLOCK_SUCCESS;

  ULogFront_RealTimeInit (&(ClockAppsCtxt.hClockAppsULog),
                          "Clock_Apps_Log", ClockAppsCtxt.nLogSize,
                          ULOG_MEMORY_LOCAL, ULOG_LOCK_OS);
  ULogCore_HeaderSet (ClockAppsCtxt.hClockAppsULog,
                      "Content-Type: text/tagged-log-1.0;");

  eResult = Clock_InitImage();
  if (eResult != CLOCK_SUCCESS)
  {
    return CLOCK_ERROR;
  }

  return CLOCK_SUCCESS;

} /* END Clock_InitTarget */


/* =========================================================================
**  Function : Clock_DeInitTarget
** =========================================================================*/
/*
  See ClockApps.h
*/
/**
  De-Initialization and cleanup of the target specific portion of the clock driver.
  It is specific to the image and chipset we are running on.

  @return
  CLOCK_SUCCESS - Sucessfully Initialize the target specific portion of the clock driver.

  @dependencies
  None.
*/

ClockResult Clock_DeInitTarget
(
  void
)
{
  /*-----------------------------------------------------------------------*/
  /* Clear out driver context data.                                        */
  /*-----------------------------------------------------------------------*/
  memset(&ClockAppsBSP,  0x0, sizeof(ClockAppsBSPType));
  memset(&ClockAppsCtxt, 0x0, sizeof(ClockAppsCtxtType));

  return CLOCK_SUCCESS;

} /* END Clock_DeInitTarget */


/* =========================================================================
**  Function : Clock_GetBootCorner
** =========================================================================*/
/**
  Returns the configured boot voltage corner for the given rail stored in a
  BSP data structure.

  @param szRailName  [in] -- Name of the rail.
  @param eBootCorner [out] -- The configured boot corner to return.

  @return
  CLOCK_SUCCESS if the value was found and retrieved, CLOCK_ERROR otherwise.

  @dependencies
  None.
*/

ClockResult Clock_GetBootCorner
(
  const char         *szRailName,
  rail_voltage_level *eBootCorner
)
{
  ClockResult              eResult;
  ClockRailConfigType     *ClockRailConfig;
  uint32_t                 nIndex;

  if (!szRailName || !eBootCorner)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Get the boot voltage corner table.                                    */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_GetPropertyHandle("ClockRailConfig", (void**)(&ClockRailConfig));

  if (eResult == CLOCK_SUCCESS)
  {
    for (nIndex = 0; ClockRailConfig[nIndex].sName != NULL; nIndex++)
    {
      if (strcmp(ClockRailConfig[nIndex].sName, szRailName) == 0)
      {
        *eBootCorner = ClockRailConfig[nIndex].eBootCorner;
        return CLOCK_SUCCESS;
      }
    }
    *eBootCorner = RAIL_VOLTAGE_LEVEL_OFF;
    return CLOCK_ERROR_NOT_FOUND;
  }

  return eResult;

} /* END Clock_GetBootCorner */


void HAL_clk_InitMiscRegisters()
{  
  /*
   * Empty
   */
}

void HAL_clk_EnableDCDs()
{
  HWIO_OUT(CAM_CC_CAMNOC_NRT_AXI_DIV_DCDR, 1);
  HWIO_OUT(VCODEC_VIDEO_CC_MVS0C_DIV_DCDR, 1);
} /* HAL_clk_EnableDCDs */

/* ===========================================================================
**  HAL_clk_GPUGxPowerDomainEnable
** ======================================================================== */
/*
 * GX_CLKCTL HPG, VDD GX power on sequence
 */
void HAL_clk_GPUGxPowerDomainEnable
(
  HAL_clk_PowerDomainDescType *pmPowerDomainDesc
)
{
  uintnt nAddr;
  uint32_t nVal, nMask;

  nAddr = pmPowerDomainDesc->VoterRegister.nAddr;
  if(nAddr)
  {
    nMask = pmPowerDomainDesc->VoterRegister.nMask;
  }
  else
  {
    nAddr = pmPowerDomainDesc->nGDSCRAddr;
    nMask = HAL_CLK_GDSCR_SW_COLLAPSE_FMSK;
  }

  /*
   * Sanity check
   */
  if (nAddr == 0)
  {
    return;
  }
 
  /* 
   * Setting up RCG   
   */
  HWIO_OUTF(GPUCC_GPU_CC_FF_CFG_RCGR, SRC_SEL, 5);
  HWIO_OUTF(GPUCC_GPU_CC_FF_CFG_RCGR, SRC_DIV, 5);
  HWIO_OUTF(GPUCC_GPU_CC_FF_CMD_RCGR, UPDATE, 1);

  HWIO_OUTF(GPUCC_GPU_CC_GX_AHB_FF_CBCR, CLK_ENABLE, 1);

  /* 
   *  Turn on GFX3D clock
   */
  HWIO_OUTF(GPU_GX_CLKCTL_GX_GFX3D_CBCR, CLK_ENABLE, 1);

  /* 
   *  Turn on GFX xo clocks
   */
  HWIO_OUTF(GPU_GX_CLKCTL_CLK_CTL_XO_CBCR, CLK_ENABLE, 1);

  
  
  nVal  = inpdw(nAddr);
  /*
   * Clear the SW PD collapse bit
   */
  nVal &= ~nMask;
  outpdw(nAddr, nVal);
   
  /*
   * Wait for PD ON
   */
  while (!(inpdw(pmPowerDomainDesc->nGDSCRAddr) & HAL_CLK_GDSCR_PWR_ON_FMSK));

} /* END HAL_clk_GPUGxPowerDomainEnable */

/* ===========================================================================
**  HAL_clk_GPUGxPowerDomainDisable
** ======================================================================== */

void HAL_clk_GPUGxPowerDomainDisable
(
  HAL_clk_PowerDomainDescType *pmPowerDomainDesc
)
{
  uintnt nAddr;
  uint32_t nVal, nMask;

  nAddr = pmPowerDomainDesc->VoterRegister.nAddr;
  if(nAddr)
  {
    nMask = pmPowerDomainDesc->VoterRegister.nMask;
  }
  else
  {
    nAddr = pmPowerDomainDesc->nGDSCRAddr;
    nMask = HAL_CLK_GDSCR_SW_COLLAPSE_FMSK;
  }

  /*
   * Sanity check
   */
  if (nAddr == 0)
  {
    return;
  }

  /*
   * Set the SW PD collapse bit
   */
  nVal  = inpdw(nAddr);
  nVal |= nMask;
  outpdw(nAddr, nVal);

  /*
   * Wait for PD OFF
   */
  while ((inpdw(pmPowerDomainDesc->nGDSCRAddr) & HAL_CLK_GDSCR_PWR_ON_FMSK));


} /* END HAL_clk_GPUGxPowerDomainDisable */

HAL_clk_PowerDomainControlType HAL_clk_GPUGxPowerDomainControl =
{
   .Enable     = HAL_clk_GPUGxPowerDomainEnable,
   .Disable    = HAL_clk_GPUGxPowerDomainDisable,
   .IsEnabled  = HAL_clk_GenericPowerDomainIsEnabled,
   .IsOn       = HAL_clk_GenericPowerDomainIsOn,
   .EnableHW   = HAL_clk_GenericPowerDomainEnableHW,
   .DisableHW  = HAL_clk_GenericPowerDomainDisableHW
};
