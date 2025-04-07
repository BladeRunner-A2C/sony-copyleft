/*
==============================================================================

FILE:         ClockImage.c

DESCRIPTION:
  This file contains Image Specific Api's.

==============================================================================

$Header: //components/dev/core.boot/6.1/arajashe.core.boot.6.1.milosuefi/QcomPkg/SocPkg/Kailua/Library/ClockLib/ClockImage.c#1 $

==============================================================================
            Copyright (c) 2023 Qualcomm Technologies, Inc. All rights reserved.
            Confidential and Proprietary - Qualcomm Technologies, Inc.
==============================================================================

*/

/*=========================================================================
      Include Files
==========================================================================*/
#include "ClockApps.h"
#include "Library/ClockCoreLib/inc/ClockDriverImage.h"


/*=========================================================================
      Type Definitions
==========================================================================*/

/*=========================================================================
      Function Definitions
==========================================================================*/

ClockResult ClockApps_DetectCPUFrequency
(
  uint32_t    nClusterIndex,
  uint32_t   *pnFreqHz
);


ClockResult Clock_InitCPU
(
  void
);


void HAL_clk_InitMiscRegisters();
void HAL_clk_EnableDCDs();


/*=========================================================================
      Externs
==========================================================================*/
extern ClockAppsBSPType ClockAppsBSP;

/*=========================================================================
      Data
==========================================================================*/

/*
 * Clock Apps context.
 */
ClockAppsCtxtType ClockAppsCtxt = {
  .pBSP                = &ClockAppsBSP,
  .nLogSize            = 0x4000,
  .hClockAppsULog      = NULL,
  .bImageBISTEnabled   = FALSE,
};

/*=========================================================================
     Functions
==========================================================================*/

ClockResult Clock_ConfigureDCD 
(
  void
)
{
  ClockDrvCtxt             *pDrvCtxt = Clock_GetDrvCtxt();
  ClockIdType               nClockId=0;
  ClockNameListType        *pDCDDependencies= NULL;
  uint32_t                  i=0;
  ClockResult               eResult;

  /*-----------------------------------------------------------------------*/
  /* Enable Mutimedia DCD's.                                               */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_GetPropertyValue("ClockDCDEnableDependencies", (ClockPropertyValueType*)&pDCDDependencies);
  if (eResult != CLOCK_SUCCESS){
      return CLOCK_ERROR;
  }

  for (i = 0; pDCDDependencies[i].szName != NULL; i++){
    if ((Clock_GetClockId(pDrvCtxt->hClient, pDCDDependencies[i].szName, &nClockId) == CLOCK_SUCCESS) &&
        (Clock_EnableEx(pDrvCtxt->hClient, nClockId, 0) == CLOCK_SUCCESS))
    {
       //busywait(5);
    }
    else
    {
      ULOG_RT_PRINTF_1 (pDrvCtxt->hClockLog, "Failed to Enable DCD dependency clock %s", pDCDDependencies[i].szName);
      return CLOCK_ERROR;
    }
  }

  HAL_clk_EnableDCDs();


  eResult = Clock_GetPropertyValue("ClockDCDDisableDependencies", (ClockPropertyValueType*)&pDCDDependencies);
  if (eResult != CLOCK_SUCCESS){
      return CLOCK_ERROR;
  }

  for (i = 0; pDCDDependencies[i].szName != NULL; i++){
    if ((Clock_GetClockId(pDrvCtxt->hClient, pDCDDependencies[i].szName, &nClockId) == CLOCK_SUCCESS) &&
        (Clock_DisableEx(pDrvCtxt->hClient, nClockId, 0) == CLOCK_SUCCESS))
    {
      continue;
    }
    else
    {
      ULOG_RT_PRINTF_1 (pDrvCtxt->hClockLog, "Failed to Disable DCD dependency clock %s", pDCDDependencies[i].szName);
    }
  }
  return eResult;
}

/* =========================================================================
**  Function : Clock_InitImage
** =========================================================================*/

ClockResult Clock_InitImage
(
  void
)
{
  ClockDrvCtxt             *pDrvCtxt = Clock_GetDrvCtxt();
  ClockResult               eResult;
  ClockAppsClusterNodeType *pCluster = NULL;
  uint32_t                  nClusterOffset=0, nFreqHz=0;

  /*
   * Hookup references.
   */
  pDrvCtxt->pImageCtxt = &ClockAppsCtxt;

  /*
   * Intialize the CPU.
   */
  eResult = Clock_InitCPU();
  if (eResult != CLOCK_SUCCESS)
    DEBUG((EFI_D_WARN, "Clock_InitCPU failed.\n"));

  /*
   * Intialize QDSS.
   */
  eResult = Clock_InitQDSS();
  if (eResult != CLOCK_SUCCESS)
    DEBUG((EFI_D_WARN, "Clock_InitQDSS failed.\n"));

  /*-----------------------------------------------------------------------*/
  /* Detecting Current PerfLevel frequency.                                */
  /*-----------------------------------------------------------------------*/
  eResult = CLOCK_SUCCESS;
  for (nClusterOffset=0; nClusterOffset < ClockAppsBSP.nNumClusters; nClusterOffset++)
  {
    pCluster = &(ClockAppsBSP.aClusters[nClusterOffset]);
    eResult |= ClockApps_DetectCPUFrequency(nClusterOffset, &nFreqHz);
    DEBUG((EFI_D_WARN, ">>> %a Running at: %lu Hz.\n", pCluster->szName, nFreqHz));
  }
  if (eResult != CLOCK_SUCCESS)
    DEBUG((EFI_D_WARN, "ClockApps_DetectCPUFrequency failed.\n"));

  /*-----------------------------------------------------------------------*/
  /* Update miscellaneous registers.                                       */
  /*-----------------------------------------------------------------------*/
  HAL_clk_InitMiscRegisters();

  /* TODO: Enable DCD post BU*/
  if(ClockAppsBSP.bEnableDcds)
  {
    Clock_ConfigureDCD();
  }
  

  return CLOCK_SUCCESS;

} /* END Clock_InitImage */

