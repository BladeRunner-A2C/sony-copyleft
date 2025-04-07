/** @file RecoveryDxeUtil.c
   
  Recovery SMEM utility functions.

  Copyright (c) 2021, 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when           who         what, where, why
 --------       ---         --------------------------------------------------
 2023/04/09     gpavithr    Added support for SetSmemPartitionRecoveredFlag()
 2021/03/16     dmohan      Initial version
=============================================================================*/

#include <Library/BaseMemoryLib.h>
#include "smem.h"
#include "boot_recovery_partition.h"
#include "RecoveryDxe.h"

EFI_STATUS
GetSmemRecoveryItemCount (
  OUT UINT8                    *pCount
  )
{
  EFI_STATUS                     status            = EFI_SUCCESS;
  smem_recovery_partitions_info *pSmemRecoveryInfo = NULL;
  UINT32                         bufSize           = 0;

  pSmemRecoveryInfo = (smem_recovery_partitions_info *)smem_get_addr(
    RECOVERY_PARTITION_SMEM_ID,
    &bufSize
    );
  if(pSmemRecoveryInfo == NULL)
  {
    DEBUG((EFI_D_ERROR, "SMEM Recovery buffer is NULL "));
    status = EFI_NOT_READY;
    goto GetSmemRecoveryItemCountExit;
  }

  *pCount = pSmemRecoveryInfo->num_of_entries;

GetSmemRecoveryItemCountExit:
  return status;
}

EFI_STATUS
GetRecoveryPartitionInfoFromSmem(
  OUT void                   *pPartitionInfo,
  IN OUT UINTN               *pPartitionInfoSize
  )
{
  EFI_STATUS                     status                = EFI_SUCCESS;
  smem_recovery_partitions_info *pSmemRecoveryInfo     = NULL;
  UINT32                         bufSize               = 0;
  UINT8                          idx                   = 0;
  UINTN                          sizeOfRecoveryEntries = 0;

  pSmemRecoveryInfo = (smem_recovery_partitions_info *)smem_get_addr(
    RECOVERY_PARTITION_SMEM_ID,
    &bufSize
    );
  if (pSmemRecoveryInfo == NULL)
  {
    DEBUG((EFI_D_ERROR, "SMEM Recovery buffer is NULL "));
    status = EFI_NOT_READY;
    goto GetRecoveryPartitionInfoFromSmemExit;
  }

  DEBUG((EFI_D_INFO, "magic_cookie: 0x%x  max_entries: %d version: %d num_of_entries: %d\n",
    pSmemRecoveryInfo->magic_cookie,
    pSmemRecoveryInfo->max_entries,
    pSmemRecoveryInfo->version,
    pSmemRecoveryInfo->num_of_entries
    ));

  sizeOfRecoveryEntries = (pSmemRecoveryInfo->num_of_entries * sizeof(RECOVERY_DATA_ENTRY));

  if (*pPartitionInfoSize < sizeOfRecoveryEntries)
  {
    status = EFI_BUFFER_TOO_SMALL;
    *pPartitionInfoSize = sizeOfRecoveryEntries;
    goto GetRecoveryPartitionInfoFromSmemExit;
  }

  PRECOVERY_DATA_ENTRY pRecoveryEntries = (PRECOVERY_DATA_ENTRY)pPartitionInfo;

  for (idx = 0; idx < pSmemRecoveryInfo->num_of_entries; idx++)
  {
    DEBUG((
      EFI_D_INFO, "corrupted_partition_id[%d]: %g  recovery_partition_id[%d]: %g\n",
      idx, &pSmemRecoveryInfo->partition_info[idx].corrupted_partition_id,
      idx, &pSmemRecoveryInfo->partition_info[idx].recovery_partition_id
      ));

    CopyMem(
      &pRecoveryEntries[idx].PrimaryGuid,
      &pSmemRecoveryInfo->partition_info[idx].corrupted_partition_id,
      sizeof(EFI_GUID)
      );

    CopyMem(
      &pRecoveryEntries[idx].SecondaryGuid,
      &pSmemRecoveryInfo->partition_info[idx].recovery_partition_id,
      sizeof(EFI_GUID)
      );

    DEBUG((
      EFI_D_INFO, "PrimaryGuid[%d]: %g  SecondaryGuid[%d]: %g\n",
      idx, &pRecoveryEntries[idx].PrimaryGuid,
      idx, &pRecoveryEntries[idx].SecondaryGuid
      ));
  }

GetRecoveryPartitionInfoFromSmemExit:
  return status;
}

EFI_STATUS
SetSmemPartitionRecoveredFlag(
  IN UINT8                   corruptedPartitionIndex
  )
{
  EFI_STATUS                     status                = EFI_SUCCESS;
  smem_recovery_partitions_info *pSmemRecoveryInfo     = NULL;
  UINT32                         bufSize               = 0;

  pSmemRecoveryInfo = (smem_recovery_partitions_info *)smem_get_addr(
    RECOVERY_PARTITION_SMEM_ID,
    &bufSize
    );
  if (pSmemRecoveryInfo == NULL)
  {
    DEBUG((EFI_D_ERROR, "SMEM Recovery buffer is NULL\n"));
    status = EFI_NOT_READY;
    goto Exit;
  }

  pSmemRecoveryInfo->partition_info[corruptedPartitionIndex].flags |= RECOVERED_FLAG;

  DEBUG((
    EFI_D_INFO,
    "corrupted_partition_id[%d]: %g  flags: [0x%x]\n",
    corruptedPartitionIndex,
    &pSmemRecoveryInfo->partition_info[corruptedPartitionIndex].corrupted_partition_id,
    pSmemRecoveryInfo->partition_info[corruptedPartitionIndex].flags
    ));

Exit:
  return status;
}

EFI_STATUS
GetSmemRecoveryPartitionInfoFlags(
  IN UINT8                  corruptedPartitionIndex,
  OUT UINT32                *pFlags
  )
{
  EFI_STATUS                     status                = EFI_SUCCESS;
  smem_recovery_partitions_info *pSmemRecoveryInfo     = NULL;
  UINT32                         bufSize               = 0;

  if(pFlags == NULL)
  {
    DEBUG((EFI_D_ERROR, "pFlags is NULL\n"));
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  pSmemRecoveryInfo = (smem_recovery_partitions_info *)smem_get_addr(
    RECOVERY_PARTITION_SMEM_ID,
    &bufSize
    );
  if (pSmemRecoveryInfo == NULL)
  {
    DEBUG((EFI_D_ERROR, "SMEM Recovery buffer is NULL\n"));
    status = EFI_NOT_READY;
    *pFlags = 0;
    goto Exit;
  }

  *pFlags = pSmemRecoveryInfo->partition_info[corruptedPartitionIndex].flags;

  DEBUG((
    EFI_D_INFO,
    "corrupted_partition_id[%d]: %g  flags: [0x%x]\n",
    corruptedPartitionIndex,
    &pSmemRecoveryInfo->partition_info[corruptedPartitionIndex].corrupted_partition_id,
    *pFlags
    ));

Exit:
  return status;
}

