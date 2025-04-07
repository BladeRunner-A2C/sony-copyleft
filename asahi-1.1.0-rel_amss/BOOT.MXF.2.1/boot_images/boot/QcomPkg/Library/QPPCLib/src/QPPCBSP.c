/*===========================================================================
FILE:         QPPCTargetBSP.c

DESCRIPTION:
  This file contains the QPPC driver BSP data.

==============================================================================

$Header: $

==============================================================================
            Copyright (c) 2022-23 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================

*/

/*=========================================================================
      Include Files
==========================================================================*/

#include "QPPC.h"


/*=========================================================================
      Externs
==========================================================================*/



/*=========================================================================
      Data Declarations
==========================================================================*/

#define PCCT_PHYSICAL_ADDRESS 0x81E00000
#define PCCT_BASE_SIZE 0x00200000

uintptr_t QPPC_nPCCTBaseAddr;

/*=========================================================================
            BASE ADDRESS
==========================================================================*/
static QPPCBaseType aPcctBase[] = 
{ PCCT_PHYSICAL_ADDRESS,        PCCT_BASE_SIZE,        &QPPC_nPCCTBaseAddr };

/*=========================================================================
      Clusters
==========================================================================*/
static QPPCCoreType aCores[] =
{
    {
        .szPdpName            = "pdp0",
        .szQppcName           = "qppc1"
    },
    {
        .szPdpName            = "pdp0",
        .szQppcName           = "qppc2",
        .nFlags               = QPPC_FLAG_CORE_ONDEMAND_INIT,
    },
    {
        .szPdpName            = "pdp0",
        .szQppcName           = "qppc3",
        .nFlags               = QPPC_FLAG_CORE_ONDEMAND_INIT,
    },
    {
        .szPdpName            = "pdp0",
        .szQppcName           = "qppc4",
        .nFlags               = QPPC_FLAG_CORE_ONDEMAND_INIT,
    },
    {
        .szPdpName            = "pdp1",
        .szQppcName           = "qppc1",
        .nFlags               = QPPC_FLAG_CORE_ONDEMAND_INIT,
    },
    {
        .szPdpName            = "pdp1",
        .szQppcName           = "qppc2",
        .nFlags               = QPPC_FLAG_CORE_ONDEMAND_INIT,
    },
    {
        .szPdpName            = "pdp1",
        .szQppcName           = "qppc3",
        .nFlags               = QPPC_FLAG_CORE_ONDEMAND_INIT,
    },
    {
        .szPdpName            = "pdp1",
        .szQppcName           = "qppc4",
        .nFlags               = QPPC_FLAG_CORE_ONDEMAND_INIT,
    },
    {
        .szPdpName            = "pdp2",
        .szQppcName           = "qppc1",
        .nFlags               = QPPC_FLAG_CORE_ONDEMAND_INIT,
    },
    {
        .szPdpName            = "pdp2",
        .szQppcName           = "qppc2",
        .nFlags               = QPPC_FLAG_CORE_ONDEMAND_INIT,
    },
    {
        .szPdpName            = "pdp2",
        .szQppcName           = "qppc3",
        .nFlags               = QPPC_FLAG_CORE_ONDEMAND_INIT,
    },
    {
        .szPdpName            = "pdp2",
        .szQppcName           = "qppc4",
        .nFlags               = QPPC_FLAG_CORE_ONDEMAND_INIT,
    },
};

/*=========================================================================
      Main Image BSP
==========================================================================*/
QPPCBSPType QppcBSP =
{
  .aPcctBase     = aPcctBase,
  .nBases        = SIZEOF_ARRAY(aPcctBase),
  .aCores        = aCores,
  .nNumCores     = SIZEOF_ARRAY(aCores),
  //.nFlags        = QPPC_FLAG_STUB_DRIVER,
};
