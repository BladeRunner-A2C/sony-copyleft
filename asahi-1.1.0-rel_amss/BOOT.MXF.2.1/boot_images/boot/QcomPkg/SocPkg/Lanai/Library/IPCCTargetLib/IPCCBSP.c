/*
================================================================================
*/
/**
  @file IPCCBSP.c

  BSP file for the IPCC driver.
*/
/*
  ==============================================================================

  Copyright (c) 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  ==============================================================================

  $Header: $
  $DateTime: $
  $Author: $

  ==============================================================================
*/

/*==============================================================================
  Includes
==============================================================================*/

#include "IPCC_Internal.h"


/*==============================================================================
  Macros
==============================================================================*/

#define NUM_PROTOCOLS          (IPCC_P_FENCE - IPCC_P_MPROC + 1)

#define NUM_CLIENTS_MPROC      16
#define NUM_CLIENTS_COMPUTEL0  11
#define NUM_CLIENTS_COMPUTEL1  11
#define NUM_CLIENTS_PERIPH     8
#define NUM_CLIENTS_FENCE      19


/*==============================================================================
  Data
==============================================================================*/

IPCCClientType IPCCClientMproc[NUM_CLIENTS_MPROC] =
{
  { .eClient = IPCC_C_AOP      },
  { .eClient = IPCC_C_APSS_S   },
  { .eClient = IPCC_C_MPSS     },
  { .eClient = IPCC_C_LPASS    },
  { .eClient = IPCC_C_SDC      },
  { .eClient = IPCC_C_NSP0     },
  { .eClient = IPCC_C_APSS_NS0 },
  { .eClient = IPCC_C_GPU      },
  { .eClient = IPCC_C_CAM      },
  { .eClient = IPCC_C_APSS_NS1 },
  { .eClient = IPCC_C_CVP      },
  { .eClient = IPCC_C_VPU      },
  { .eClient = IPCC_C_IPA      },
  { .eClient = IPCC_C_DBG      },
  { .eClient = IPCC_C_SPSS     },
  { .eClient = IPCC_C_TMESS    },
};

IPCCClientType IPCCClientComputeL0[NUM_CLIENTS_COMPUTEL0] =
{
  { .eClient = IPCC_C_MPSS     },
  { .eClient = IPCC_C_LPASS    },
  { .eClient = IPCC_C_NSP0     },
  { .eClient = IPCC_C_APSS_NS0 },
  { .eClient = IPCC_C_GPU      },
  { .eClient = IPCC_C_CAM      },
  { .eClient = IPCC_C_APSS_NS1 },
  { .eClient = IPCC_C_CVP      },
  { .eClient = IPCC_C_VPU      },
  { .eClient = IPCC_C_DPU0     },
  { .eClient = IPCC_C_DBG      },
};

IPCCClientType IPCCClientComputeL1[NUM_CLIENTS_COMPUTEL1] =
{
  { .eClient = IPCC_C_MPSS     },
  { .eClient = IPCC_C_LPASS    },
  { .eClient = IPCC_C_NSP0     },
  { .eClient = IPCC_C_APSS_NS0 },
  { .eClient = IPCC_C_GPU      },
  { .eClient = IPCC_C_CAM      },
  { .eClient = IPCC_C_APSS_NS1 },
  { .eClient = IPCC_C_CVP      },
  { .eClient = IPCC_C_VPU      },
  { .eClient = IPCC_C_DPU0     },
  { .eClient = IPCC_C_DBG      },
};

IPCCClientType IPCCClientPeriph[NUM_CLIENTS_PERIPH] =
{
  { .eClient = IPCC_C_MPSS     },
  { .eClient = IPCC_C_LPASS    },
  { .eClient = IPCC_C_NSP0     },
  { .eClient = IPCC_C_APSS_NS0 },
  { .eClient = IPCC_C_PCIE0    },
  { .eClient = IPCC_C_PCIE1    },
  { .eClient = IPCC_C_APSS_NS1 },
  { .eClient = IPCC_C_DBG      },
};

IPCCClientType IPCCClientFence[NUM_CLIENTS_FENCE] =
{
  { .eClient = IPCC_C_MPSS     },
  { .eClient = IPCC_C_LPASS    },
  { .eClient = IPCC_C_NSP0     },
  { .eClient = IPCC_C_APSS_NS0 },
  { .eClient = IPCC_C_GPU      },
  { .eClient = IPCC_C_CAM      },
  { .eClient = IPCC_C_APSS_NS1 },
  { .eClient = IPCC_C_CVP      },
  { .eClient = IPCC_C_VPU      },
  { .eClient = IPCC_C_DPU0     },
  { .eClient = IPCC_C_DBG      },
  { .eClient = IPCC_C_IFE0     },
  { .eClient = IPCC_C_IFE1     },
  { .eClient = IPCC_C_IFE2     },
  { .eClient = IPCC_C_IFE3     },
  { .eClient = IPCC_C_IFE4     },
  { .eClient = IPCC_C_IFE5     },
  { .eClient = IPCC_C_IFE6     },
  { .eClient = IPCC_C_IFE7     },
};

IPCCProtocolType IPCCProtocols[NUM_PROTOCOLS] =
{
  [IPCC_P_MPROC] =
  {
    .nProtocolId        = 0,
    .nNumSigs           = 8,
    .nNumClients        = NUM_CLIENTS_MPROC,
    .nInterrupt         = 261,
    .nPhysBaseAddress   = 0x00400000,
    .pClients           = &IPCCClientMproc[0],
  },

  [IPCC_P_COMPUTEL0] =
  {
    .nProtocolId        = 1,
    .nNumSigs           = 32,
    .nNumClients        = NUM_CLIENTS_COMPUTEL0,
    .nInterrupt         = 262,
    .nPhysBaseAddress   = 0x00400000,
    .pClients           = &IPCCClientComputeL0[0],
  },

  [IPCC_P_COMPUTEL1] =
  {
    .nProtocolId        = 2,
    .nNumSigs           = 32,
    .nNumClients        = NUM_CLIENTS_COMPUTEL1,
    .nInterrupt         = 263,
    .nPhysBaseAddress   = 0x00400000,
    .pClients           = &IPCCClientComputeL1[0],
  },

  [IPCC_P_PERIPH] =
  {
    .nProtocolId        = 3,
    .nNumSigs           = 32,
    .nNumClients        = NUM_CLIENTS_PERIPH,
    .nInterrupt         = 746,
    .nPhysBaseAddress   = 0x00400000,
    .pClients           = &IPCCClientPeriph[0],
  },

  [IPCC_P_FENCE] =
  {
    .nProtocolId        = 4,
    .nNumSigs           = 32,
    .nNumClients        = NUM_CLIENTS_FENCE,
    .nInterrupt         = 102,
    .nPhysBaseAddress   = 0x00400000,
    .pClients           = &IPCCClientFence[0],
  },
};

IPCCBSPDataType IPCCBSPData =
{
  .pProtocols    = &IPCCProtocols[0],
  .nNumProtocols = NUM_PROTOCOLS,
  .eClient       = IPCC_C_APSS_NS0,
};
