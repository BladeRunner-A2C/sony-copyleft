/*==============================================================================
  @file ChipInfoBSP.c

  ChipInfo BSP data.

================================================================================

  Copyright (c) 2016-2023, 2024 Qualcomm Technologies, Inc. All rights reserved. 
  Confidential and Proprietary - Qualcomm Technologies, Inc

================================================================================*/

/*==============================================================================
      Include Files
==============================================================================*/
#include "comdef.h"
#include "ChipInfoLocal.h"
#include "ChipInfoLoader.h"

/*==============================================================================
      Data Definitons
==============================================================================*/
//#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

/*==============================================================================
      Data Definitons
==============================================================================*/

/*
 * ChipInfoDataLUT
 *
 * Array of chip id strings, chip IDs, part numbers, and modem support.
 *
 * This table only needs to contain mappings for targets supported out of this warehouse.
 */
static const ChipInfoDataLUTType ChipInfoDataLUT[] =
{
  { "UNKNOWN",            CHIPINFO_ID_UNKNOWN,              CHIPINFO_PARTNUM_UNKNOWN,           CHIPINFO_MODEM_UNKNOWN    },

  { "QRU_LASSEN",         CHIPINFO_ID_QRU_LASSEN,           CHIPINFO_PARTNUM_QRU_LASSEN,        CHIPINFO_MODEM_SUPPORTED  },
  { "QDU_LASSEN",         CHIPINFO_ID_QDU_LASSEN,           CHIPINFO_PARTNUM_QDU_LASSEN,        CHIPINFO_MODEM_SUPPORTED  },
  { "QDU1010_LASSEN",     CHIPINFO_ID_QDU1010_LASSEN,       CHIPINFO_PARTNUM_QDU1010_LASSEN,    CHIPINFO_MODEM_SUPPORTED  },
  { "QRU1032_LASSEN",     CHIPINFO_ID_QRU1032_LASSEN,       CHIPINFO_PARTNUM_QRU1032_LASSEN,    CHIPINFO_MODEM_SUPPORTED  },
  { "QRU1052_LASSEN",     CHIPINFO_ID_QRU1052_LASSEN,       CHIPINFO_PARTNUM_QRU1052_LASSEN,    CHIPINFO_MODEM_SUPPORTED  },
  { "QRU1062_LASSEN",     CHIPINFO_ID_QRU1062_LASSEN,       CHIPINFO_PARTNUM_QRU1062_LASSEN,    CHIPINFO_MODEM_SUPPORTED  },
  { "SM_LANAI",           CHIPINFO_ID_SM_LANAI,             CHIPINFO_PARTNUM_SM_LANAI,          CHIPINFO_MODEM_SUPPORTED  },
  { "SMP_LANAI",          CHIPINFO_ID_SMP_LANAI,            CHIPINFO_PARTNUM_SMP_LANAI,         CHIPINFO_MODEM_UNKNOWN    },
  { "SCP_HAMOA",          CHIPINFO_ID_SCP_HAMOA,            CHIPINFO_PARTNUM_SCP_HAMOA,         CHIPINFO_MODEM_UNKNOWN    },
  { "SDX_PINNACLES",      CHIPINFO_ID_SDX_PINNACLES,        CHIPINFO_PARTNUM_SDX_PINNACLES,     CHIPINFO_MODEM_SUPPORTED  },
  { "SDX_PINNACLES_M",    CHIPINFO_ID_SDX_PINNACLES_M,      CHIPINFO_PARTNUM_SDX_PINNACLES_M,   CHIPINFO_MODEM_SUPPORTED  },
  { "SA_PINNACLES",       CHIPINFO_ID_SA_PINNACLES,         CHIPINFO_PARTNUM_SA_PINNACLES,      CHIPINFO_MODEM_SUPPORTED  },
  { "SA_PINNACLES_L",     CHIPINFO_ID_SA_PINNACLES_L,       CHIPINFO_PARTNUM_SA_PINNACLES_L,    CHIPINFO_MODEM_SUPPORTED  },
  { "SDX_KUNO_SINGLEDIE", CHIPINFO_ID_SDX_KUNO_SINGLEDIE,   CHIPINFO_PARTNUM_SDX_KUNO_SINGLEDIE, CHIPINFO_MODEM_SUPPORTED },
  { "SDX_KUNO_HYBRID",    CHIPINFO_ID_SDX_KUNO_HYBRID,      CHIPINFO_PARTNUM_SDX_KUNO_HYBRID,   CHIPINFO_MODEM_SUPPORTED  },
  { "SDX_PINNACLES_L",    CHIPINFO_ID_SDX_PINNACLES_L,      CHIPINFO_PARTNUM_SDX_PINNACLES_L,   CHIPINFO_MODEM_SUPPORTED  },
  { "SDX_PINNACLES_UL",   CHIPINFO_ID_SDX_PINNACLES_UL,     CHIPINFO_PARTNUM_SDX_PINNACLES_UL,  CHIPINFO_MODEM_SUPPORTED  },
  { "SCP_HAMOA_10CORE",   CHIPINFO_ID_SCP_HAMOA_10CORE,     CHIPINFO_PARTNUM_SCP_HAMOA_10CORE,  CHIPINFO_MODEM_UNKNOWN    },
  { "SCP_HAMOA_8CORE",    CHIPINFO_ID_SCP_HAMOA_8CORE,      CHIPINFO_PARTNUM_SCP_HAMOA_8CORE,   CHIPINFO_MODEM_UNKNOWN    },
  { "SM_PAKALA",          CHIPINFO_ID_SM_PAKALA,            CHIPINFO_PARTNUM_SM_PAKALA,         CHIPINFO_MODEM_SUPPORTED  },
  { "SM_PALAWAN",         CHIPINFO_ID_SM_PALAWAN,           CHIPINFO_PARTNUM_SM_PALAWAN,        CHIPINFO_MODEM_SUPPORTED  },
  { "SM_LAMMA",           CHIPINFO_ID_SM_LAMMA,             CHIPINFO_PARTNUM_SM_LAMMA,          CHIPINFO_MODEM_SUPPORTED  },
  { "SM_KIMILOS",         CHIPINFO_ID_SM_KIMOLOS,           CHIPINFO_PARTNUM_SM_KIMILOS,        CHIPINFO_MODEM_SUPPORTED  },
  { "SM_MILOS",           CHIPINFO_ID_SM_MILOS,             CHIPINFO_PARTNUM_SM_MILOS,          CHIPINFO_MODEM_SUPPORTED  },
  { "SMP_MILOS",          CHIPINFO_ID_SMP_MILOS,            CHIPINFO_PARTNUM_SMP_MILOS,         CHIPINFO_MODEM_UNKNOWN    },
  { "SMP_PALAWAN",        CHIPINFO_ID_SMP_PALAWAN,          CHIPINFO_PARTNUM_SMP_PALAWAN,       CHIPINFO_MODEM_UNKNOWN    },
  { "SMP_LAMMA",          CHIPINFO_ID_SMP_LAMMA,            CHIPINFO_PARTNUM_SMP_LAMMA,         CHIPINFO_MODEM_UNKNOWN    },
  { "QCM_LANAI",       	  CHIPINFO_ID_QCM_LANAI,            CHIPINFO_PARTNUM_QCM_LANAI,         CHIPINFO_MODEM_SUPPORTED  },
  { "QCS_LANAI",       	  CHIPINFO_ID_QCS_LANAI,            CHIPINFO_PARTNUM_QCS_LANAI,         CHIPINFO_MODEM_UNKNOWN    },
  { "QCM_MILOS",       	  CHIPINFO_ID_QCM_MILOS,            CHIPINFO_PARTNUM_QCM_MILOS,         CHIPINFO_MODEM_SUPPORTED  },
  { "QCS_MILOS",       	  CHIPINFO_ID_QCS_MILOS,            CHIPINFO_PARTNUM_QCS_MILOS,         CHIPINFO_MODEM_UNKNOWN    },
};


/*
 * ChipInfoArchFamilyArray
 *
 * Array of default chip ID and family IDs to use if the JTAG ID is not recognized.
 * The product family can be identified using TCSR_SOC_HW_VERSION, which is defined
 * in RTL and is therefore always available. This is typically only needed when
 * parts haven't yet been fused (e.g. RUMI or early during silicon bring up).
 *
 * This array only needs to contain information for product families being supported
 * from this warehouse.
 */
static const ChipInfoArchFamilyDataType ChipInfoArchFamilyArray[] =
{
  { CHIPINFO_ARCH_FAMILY_UNKNOWN,      0,  CHIPINFO_FAMILY_UNKNOWN,     CHIPINFO_ID_UNKNOWN       },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,      7,  CHIPINFO_FAMILY_LASSEN,      CHIPINFO_ID_QRU_LASSEN    },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,      9,  CHIPINFO_FAMILY_HAMOA,       CHIPINFO_ID_SCP_HAMOA     },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,     11,  CHIPINFO_FAMILY_PINNACLES,   CHIPINFO_ID_SDX_PINNACLES },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,     12,  CHIPINFO_FAMILY_LANAI,       CHIPINFO_ID_SM_LANAI      },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,     14,  CHIPINFO_FAMILY_KUNO,        CHIPINFO_ID_SDX_KUNO_SINGLEDIE },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,     18,  CHIPINFO_FAMILY_PAKALA,      CHIPINFO_ID_SM_PAKALA     },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,     19,  CHIPINFO_FAMILY_PALAWAN,     CHIPINFO_ID_SM_PALAWAN    },
  { CHIPINFO_ARCH_FAMILY_WILDCAT,     24,  CHIPINFO_FAMILY_MILOS,       CHIPINFO_ID_SM_KIMOLOS    },
};


static ChipInfoBSPType ChipInfoBSP =
{
  .aLUT = ChipInfoDataLUT,
  .nNumLUTEntries = ARRAY_SIZE(ChipInfoDataLUT),
  .aArchFamilyData = ChipInfoArchFamilyArray,
  .nNumArchFamilyDataEntries = ARRAY_SIZE(ChipInfoArchFamilyArray),
};


/*==============================================================================
      Functions
==============================================================================*/

ChipInfoBSPType *ChipInfo_GetBSPData
(
  void
)
{
  return &ChipInfoBSP;
}