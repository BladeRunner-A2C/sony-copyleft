/** @file Cache.c

  Copyright (c) 2010-2015, 2021-2023 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

  Portions Copyright (c) 2008 - 2009, Apple Inc. All rights reserved.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/10/23   rbv     Mapping DT,IMEM early on for early Initialization of Device tree
 09/12/22   kac     Mapped QUP region in EarlyCacheInit since base address for UART will be present
 11/12/20   cm      Add support for NoMap to skip mapping in MMU
 09/09/15   vk      Add MMU lib
 08/13/15   vk      Remove DBI header
 04/17/15   vk      Remove collapsing regions
 09/30/14   vk      Remove carveout and reinit cache
 08/01/14   nk      Increased Max Memory entry
 05/22/14   vk      Remove 2MB carveout
 05/19/14   vk      GetConfigValue64 support
 04/16/14   vk      Remove 1 MB alignment
 03/11/14   vk      Re-init cache with only AddPeripherals regions
 12/05/13   vk      Fix top of DDR value
 11/26/13   vk      Do not add hob for page table, memory allocation adds hob
 11/15/13   vk      Add return value for MMU configuration
 10/31/13   vk      Update for absolute address for top of memory
 10/10/13   vk      Update for absolute address in cfg
 10/09/13   niting  Added prodmode check for offline crash dump memory reservation
 06/11/13   niting  Get config item to reserve memory for crash dump
 05/17/13   vk      Initialize cache early
 03/03/13   yg      Increase Max Mem regions
 02/01/13   vk      Branch from 8974 for common Sec
=============================================================================*/

#include <ProcessorBind.h>
#include <PiPei.h>
#include <Library/ArmMmuLib.h>
#include <Library/PrePiLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiCfgLib.h>
#include <Library/QcomTargetLib.h>
#include <Library/RamPartitionTableLib.h>
#include "UefiPlatCfg.h"
#include <Library/CacheMaintenanceLib.h>
#define MAX_MEMORY_ENTRIES  (128)

EFI_STATUS
EFIAPI
InitCache (
  IN MemRegionInfo  *pMemRegions,
  IN UINTN          RegionsCnt
  )
{
  EFI_STATUS                           Status;
  STATIC ARM_MEMORY_REGION_DESCRIPTOR  MemoryTable[MAX_MEMORY_ENTRIES];
  ARM_MEMORY_REGION_ATTRIBUTES         CacheAttributes;
  VOID                                 *TranslationTableBase;
  UINTN                                TranslationTableSize;
  UINTN                                MemRgnCnt;
  UINTN                                MemoryTableIndex = 0;

  ZeroMem (MemoryTable, sizeof (MemoryTable));

  // Sanity check
  if ((RegionsCnt >= MAX_MEMORY_ENTRIES) || (pMemRegions == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if (FeaturePcdGet (PcdCacheEnable) == TRUE) {
    CacheAttributes = ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK;
  } else {
    CacheAttributes = ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED;
  }

  for (MemRgnCnt = 0; MemRgnCnt < RegionsCnt; MemRgnCnt++) {
    // Skip entries which explicitly ask to be added as HOB only
    // Also skip entries that are marked as NoMap so a hole is created.
    BUILD_HOB_OPTION_TYPE  HobValue = pMemRegions[MemRgnCnt].BuildHobOption;
    if ((HobValue == HobOnlyNoCacheSetting) || (HobValue == NoMap) || (HobValue == AddDynamicMem)) {
      continue;
    }

    // Fill the new entry
    MemoryTable[MemoryTableIndex].PhysicalBase = pMemRegions[MemRgnCnt].MemBase;
    MemoryTable[MemoryTableIndex].VirtualBase  = pMemRegions[MemRgnCnt].MemBase;
    MemoryTable[MemoryTableIndex].Length       = pMemRegions[MemRgnCnt].MemSize;

    if (pMemRegions[MemRgnCnt].CacheAttributes == ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK) {
      MemoryTable[MemoryTableIndex].Attributes = CacheAttributes;
    } else {
      MemoryTable[MemoryTableIndex].Attributes = pMemRegions[MemRgnCnt].CacheAttributes;
    }

    MemoryTableIndex++;

    if (MemoryTableIndex >= MAX_MEMORY_ENTRIES) {
      return EFI_INVALID_PARAMETER;
    }
  }

  // End of Table
  MemoryTable[MemoryTableIndex].PhysicalBase = 0;
  MemoryTable[MemoryTableIndex].VirtualBase  = 0;
  MemoryTable[MemoryTableIndex].Length       = 0;
  MemoryTable[MemoryTableIndex].Attributes   = (ARM_MEMORY_REGION_ATTRIBUTES)0;

  WriteBackInvalidateDataCacheRange((VOID *)FixedPcdGet64(PcdEmbeddedFdBaseAddress), FixedPcdGet64 (PcdUefiFdSize));
  WriteBackInvalidateDataCacheRange((VOID *)FixedPcdGet64(PcdBootDtBase), FixedPcdGet64 (PcdBootDtSize));
  
  Status = ArmConfigureMmu (MemoryTable, &TranslationTableBase, &TranslationTableSize);

  ASSERT (Status == EFI_SUCCESS);

  if (Status != EFI_SUCCESS) {
    return Status;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EarlyCacheInit (
  UINTN  MemBase,
  UINTN  MemSize
  )
{
  ARM_MEMORY_REGION_DESCRIPTOR  EarlyInitMemoryTable[5]   = { 0 };
  UINTN                         EarlyInitMemoryTableIndex = 0;


  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].PhysicalBase = FixedPcdGet64 (PcdQUPRegionBase);
  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].VirtualBase  = FixedPcdGet64 (PcdQUPRegionBase);
  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].Length       = FixedPcdGet64 (PcdQUPRegionSize);
  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].Attributes   = ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE;
  EarlyInitMemoryTableIndex++;

  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].PhysicalBase = FixedPcdGet64(PcdIMemCookiesBase);
  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].VirtualBase  = FixedPcdGet64(PcdIMemCookiesBase);
  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].Length       = FixedPcdGet64(PcdIMemCookiesSize);
  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].Attributes   = ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE;
  EarlyInitMemoryTableIndex++;

  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].PhysicalBase = FixedPcdGet64(PcdBootDtBase);
  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].VirtualBase  = FixedPcdGet64(PcdBootDtBase);
  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].Length       = FixedPcdGet64(PcdBootDtSize);
  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].Attributes   = ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK;
  EarlyInitMemoryTableIndex++;

  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].PhysicalBase = MemBase;
  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].VirtualBase  = MemBase;
  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].Length       = MemSize;
  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].Attributes   = ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK;
  EarlyInitMemoryTableIndex++;

  // End of Table
  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].PhysicalBase = 0;
  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].VirtualBase  = 0;
  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].Length       = 0;
  EarlyInitMemoryTable[EarlyInitMemoryTableIndex].Attributes   = (ARM_MEMORY_REGION_ATTRIBUTES)0;

  return ArmConfigureMmu (EarlyInitMemoryTable, NULL, NULL);
}
