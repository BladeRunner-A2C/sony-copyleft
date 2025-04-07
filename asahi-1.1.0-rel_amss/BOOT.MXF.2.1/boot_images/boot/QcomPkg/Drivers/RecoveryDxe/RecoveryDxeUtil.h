/** @file RecoveryDxeUtil.c
   
  Header for RecoveryDxeUtil.c

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

#ifndef _RECOVERYDXEUTIL_H_
#define _RECOVERYDXEUTIL_H_

/**
  Get number of entries in SMEM recovery list.

  @param[out]  pCount     Number of entries in SMEM recovery list

  @retval  EFI_SUCCESS    Read SMEM ID to fetch number of entries in recovery list.
  @retval  EFI_NOT_READY  SMEM ID not initialized.
  @retval  EFI_XXXX       Other errors.

**/
EFI_STATUS
GetSmemRecoveryItemCount (
  OUT UINT8                   *pCount
  );

/**
  Get Recovery partition info from SMEM and store it in RECOVERY_PRIVATE_DATA structure.

  @param[out]      pPartitionInfo         Pointer to recovery data entries.
  @param[in, out]  pPartitionInfoSize     On input, holds the size of PartitionInfo.
                                          If buffer is too small, returns the 
                                          size of PartitionInfo as output.

  @retval  EFI_SUCCESS             Successfully copied recovery partition info
                                   from SMEM to RECOVERY_PRIVATE_DATA structure.
  @retval  EFI_NOT_READY           SMEM ID not initialized.
  @retval  EFI_BUFFER_TOO_SMALL    Input buffer too small.
  @retval  EFI_XXXX                Other errors.

**/
EFI_STATUS
GetRecoveryPartitionInfoFromSmem (
  OUT void                   *pPartitionInfo,
  IN OUT UINTN               *pPartitionInfoSize
  );

/**
  Update "flags" field for corrupted partition in SMEM to reflect successful recovery.

  @param[in]  corruptedPartitionIndex     Index to the Corrupted partition in SMEM recovery
                                          partition info.

  @retval     EFI_SUCCESS                 Successfully updated the bit[2] of the "flags" to 1
                                          to indicate successful recovery
  @retval     EFI_NOT_READY               SMEM ID not initialized.
  @retval     EFI_XXXX                    Other errors.

**/
EFI_STATUS
SetSmemPartitionRecoveredFlag (
  IN UINT8 corruptedPartitionIndex
  );

/**
  Fetch "flags" field for corrupted partition in SMEM to detect if partition is already recovered.

  @param[in]  corruptedPartitionIndex     Index to the Corrupted partition in SMEM recovery
                                          partition info.
  @param[out] pFlags                      Returns the flags value of the Corrupted partition in
                                          SMEM recovery partition info.

  @retval     EFI_SUCCESS                 Successfully read the "flags" value of corrupted partition from SMEM 
                                          and copied its value to the output param pFlags.
                                          to indicate successful recovery
  @retval     EFI_NOT_READY               SMEM ID not initialized.
  @retval     EFI_XXXX                    Other errors.

**/
EFI_STATUS
GetSmemRecoveryPartitionInfoFlags(
  IN UINT8 corruptedPartitionIndex,
  OUT UINT32 *pFlags
  );

#endif // #ifndef _RECOVERYDXEUTIL_H_

