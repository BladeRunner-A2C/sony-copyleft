/*==============================================================================

FILE:      ChipInfoCore.c

DESCRIPTION:
  This file implements the parts of the ChipInfo driver specific to XBL Core

PUBLIC CLASSES:
  ChipInfo_Init

================================================================================
        Copyright (c) 2016-2017, 2019, 2022, 2023 Qualcomm Technologies, Inc.All rights reserved.

================================================================================

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/ChipInfoLib/ChipInfoCore.c#1 $
  $DateTime: 2024/04/02 23:00:31 $
  $Author: cirrusp4svc $
==============================================================================*/

/*==============================================================================
      Include Files
==============================================================================*/
#include "ChipInfo.h"
#include "ChipInfoLocal.h"
#include "DALStdErr.h"
#include "DALStdDef.h"
#include "ChipInfoImage.h"
#include "PlatformInfoDefs.h"

/*=========================================================================
      Data Definitions
==========================================================================*/

/*
 * Internal structure to hold chip info.
 *
 * During XBL Core, ChipInfoDxe init pulls data from the SMEM region
 * and stores it in here.
 *
 * The query APIs read data from this structure.
 */
ChipInfoCtxtType ChipInfoCtxt;

/*==============================================================================
      Functions
==============================================================================*/

/*=============================================================================

  FUNCTION      ChipInfo_Init

  DESCRIPTION   Initialize the XBL Core chip info driver  by reading the
                SMEM buffer populated by PlatformInfo during XBL Loader phase

==============================================================================*/
DALResult ChipInfo_Init
(
  void
)
{
  //uint32 nSize = 0;
  uint32 *aCPUClusters, *aDisabledFeaturesArray;
  uint32 nClusterArraySize;
  DalPlatformInfoSMemType *pSMem;

  if (ChipInfoCtxt.bInitComplete)
  {
    return DAL_SUCCESS;
  }

  // Get the address of the SoCInfo structure using the
  // image-specific API
  pSMem = ChipInfo_GetSocInfo();

  if (pSMem == NULL)
  {
    // This will only happen in pre-sil on a standalone build.
    // Return SUCCESS using the UNKNOWN values for each field,
    // and let the information be set manually. However, mark the driver as
    // initialized, to record that this has happened.
    ChipInfo_strcpy(ChipInfoCtxt.szChipIdString, "UNKNOWN", CHIPINFO_MAX_ID_LENGTH);
    ChipInfoCtxt.bInitComplete = TRUE;
    return DAL_SUCCESS;
  }

  // Read the chip information from SMem
  ChipInfoCtxt.nRawPartNum = pSMem->nRawChipId;
  ChipInfoCtxt.eChipInfoId = (ChipInfoIdType)pSMem->eChipId;
  ChipInfoCtxt.nRevNumber = pSMem->nRawChipVersion;
  ChipInfoCtxt.nVersion = pSMem->nChipVersion;
  ChipInfoCtxt.eFamilyId = (ChipInfoFamilyType)pSMem->nChipFamily;
  ChipInfoCtxt.nFamilyDeviceId = pSMem->nRawDeviceNumber;
  ChipInfoCtxt.nRawFamilyId = pSMem->nRawDeviceFamily;
  ChipInfoCtxt.eFoundryId = (ChipInfoFoundryIdType)pSMem->nFoundryId;
  ChipInfoCtxt.nSerialNum = pSMem->nChipSerial;
  ChipInfoCtxt.nQFPROMChipId = pSMem->nQFPROMChipId;
  ChipInfoCtxt.nModemSupported = pSMem->nModemSupported;
  ChipInfo_strcpy(ChipInfoCtxt.szChipIdString, pSMem->szChipIdStr, CHIPINFO_MAX_ID_LENGTH);

  if (pSMem->nFormat >= DALPLATFORMINFO_VERSION(0, 14))
  {
    ChipInfoCtxt.nNumClusters = pSMem->nNumClusters;

    // Avoid crashes from DALSYS_Malloc on some images if size == 0
    if (ChipInfoCtxt.nNumClusters > 0)
    {
      aCPUClusters = (uint32 *)((uintnt)pSMem + pSMem->nClusterArrayOffset);
      nClusterArraySize = ChipInfoCtxt.nNumClusters * sizeof(uint32);

      ChipInfoCtxt.aCPUClusters = ChipInfo_malloc(nClusterArraySize);
      if (ChipInfoCtxt.aCPUClusters != NULL)
      {
        ChipInfo_memcpy(ChipInfoCtxt.aCPUClusters, nClusterArraySize, aCPUClusters, nClusterArraySize);
      }
    }

    aDisabledFeaturesArray = (uint32 *)((uintnt)pSMem + pSMem->nDisabledFeaturesArrayOffset);
    ChipInfo_memcpy(ChipInfoCtxt.aDisabledFeatures, CHIPINFO_NUM_PARTS * sizeof(uint32),
        aDisabledFeaturesArray, pSMem->nNumParts * sizeof(uint32));
  }

  if (pSMem->nFormat >= DALPLATFORMINFO_VERSION(0, 16))
  {
    ChipInfoCtxt.eFeatureCode = pSMem->eFeatureCode;
    ChipInfoCtxt.ePCode = pSMem->ePCode;
  }

  if (pSMem->nFormat >= DALPLATFORMINFO_VERSION(0, 19))
  {
    ChipInfoCtxt.nNumFunctionalClusters = pSMem->nNumFunctionalClusters;
    ChipInfoCtxt.nBootCluster = pSMem->nBootCluster;
    ChipInfoCtxt.nBootCore = pSMem->nBootCore;
  }

  ChipInfo_UnmapSMem();
  ChipInfoCtxt.bInitComplete = TRUE;
  return DAL_SUCCESS;

} /* END ChipInfo_DriverInit */


