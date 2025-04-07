/*
==============================================================================

FILE:         ClockTargetBSP.c

DESCRIPTION:
  This file contains the CPU Clock driver BSP data.
  
==============================================================================

$Header: //components/dev/core.boot/6.1/arajashe.core.boot.6.1.milosuefi/QcomPkg/SocPkg/Kailua/Library/ClockLib/ClockTargetBSP.c#1 $

==============================================================================
            Copyright (c) 2023 Qualcomm Technologies, Inc. All rights reserved.
            Confidential and Proprietary - Qualcomm Technologies, Inc.
==============================================================================

*/

/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockApps.h"
#include "Library/ClockCoreLib/inc/ClockBSP.h"
#include "HALclkHWIO.h"


/*=========================================================================
      Externs
==========================================================================*/


/*
 * CPU Cluster control structures.
 */

extern HAL_clk_ClusterControlType         HAL_clk_GenericEPSSControl;


/*=========================================================================
      Data Declarations
==========================================================================*/


/*=========================================================================
      Clusters
==========================================================================*/


ClockAppsClusterNodeType aClusters[] =
{
    {
        .szName               = "SILVER",
        .nCoreCount           = 4,
        .HALCluster           = 
        {
            .nAddr               = EPSSSLOW_CLKDOM1_CD1_REG_BASE_PHYS,
            .pmControl           = &HAL_clk_GenericEPSSControl,
        },
    },
    {
        .szName               = "GOLD",
        .nCoreCount           = 3,
        .HALCluster           = 
        {
            .nAddr               = EPSSSLOW_CLKDOM2_CD2_REG_BASE_PHYS,
            .pmControl           = &HAL_clk_GenericEPSSControl,
        },
    },
    {
        .szName               = "GOLD-PLUS",
        .nCoreCount           = 1,
        .HALCluster           = 
        {
            .nAddr               = EPSSSLOW_CLKDOM3_CD3_REG_BASE_PHYS,
            .pmControl           = &HAL_clk_GenericEPSSControl,
        },
    },
    {
        .szName               = "L3",
        .nCoreCount           = 1,            // TODO: figure out when is L3 CoreCount set to 0, one that is resolved remove all decltation of nCoreCount in Here.
        .HALCluster           = 
        {
            .nAddr               = EPSSSLOW_CLKDOM0_CD0_REG_BASE_PHYS,
            .pmControl           = &HAL_clk_GenericEPSSControl,
        },
    },
};

/*=========================================================================
      Main Image BSP
==========================================================================*/
ClockAppsBSPType ClockAppsBSP = 
{
    .aClusters     = aClusters,
    .nNumClusters  = SIZEOF_ARRAY(aClusters),
    .nFlags        = CLOCK_GLOBAL_FLAG_LOG_CLOCK_FREQ_CHANGE,
    .bEnableDcds   = FALSE,
};
