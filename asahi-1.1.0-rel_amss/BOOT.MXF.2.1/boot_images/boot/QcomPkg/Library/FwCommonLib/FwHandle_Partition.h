/** @file PartitionHandles.h
   
  Defines types for PartionHandles.c
  Copyright (c) 2011-2012,2016-2018,2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when           who         what, where, why
 --------       ---         --------------------------------------------------
 2023/01/19     dmohan      Changes to support Dual SPINOR
 2018/05/31     prema       Change to support capsule update for SPINOR-NVME devices
 2018/05/21     gparam      Changes to move all file based state-machine data to NV +
                            Cleanup of unused functions after the file to NV migration
 2017/04/18     gparam      Removed unused/redundant definitions/parameters
 2017/02/13     gpavithr    Adding list of LUN indexes in a UFS device
 2016/12/07     ssumit      Removed duplicate #define GUIDs
 2016/06/27     edg         Modified FwUpdateGetEmmcPartitionTypeGuid function to be generic for UFS support
 2012/11/15     mic         Added FwUpdateGetEmmcPartitionTypeGuid function
 2012/10/08     mic         Removed unused Guids and comments
 2012/08/08     mic         Added maximum update attempts support
 2012/08/08     rsb         Removed unused file enum types
 2012/07/10     rs          Changes in FindinFV to check all FWFile Enums
 2012/06/22     mic         Added support for OPM keys 
 2012/06/21     rs          Adding support for FPDT ACPI table
 2012/06/12     rs          Added support for BreakChangeNumber
 2011/10/12     jthompso    Initial version

=============================================================================*/
#ifndef __QCOM_FW_HANDLES_PARTITION_H__
#define __QCOM_FW_HANDLES_PARTITION_H__

#include <Library/FwCommonLib.h>
#include <Include/Protocol/EFICardInfo.h>
#include "FwCheck_FlagsStates.h"
#include "FwGpt_Helpers.h"
#include <Protocol/BlockIo.h>

#define UFS_LUN_0                  0x00
#define UFS_LUN_1                  0x01
#define UFS_LUN_2                  0x02
#define UFS_LUN_3                  0x03
#define UFS_LUN_4                  0x04
#define UFS_LUN_5                  0x05
#define UFS_LUN_6                  0x06
#define UFS_LUN_7                  0x07

#define TYPE_MEDIA_DEVICE_PATH      4

#define TYPE_END_DEVICE_PATH        0x7F

typedef struct _STORAGE_DISK_INFO
{
  EFI_GUID                      guid;     //spinor0/spinor1/nvme/LUN1/LUN2/LUN4/emmc
  BOOLEAN                       switchGPT;
  GPT_TABLE_STATE               gptState;
  QCOM_FW_UPDATE_NV_TYPE        nvType;
  UINT32                        nvDataMaxEntries;
  GPT_TABLE_TYPE                partHdrTableType;
  EFI_PARTITION_TABLE_HEADER   *pOutPartitionHeader;
} STORAGE_DISK_INFO, *PSTORAGE_DISK_INFO;

typedef struct _STORAGE_DISK_LIST
{
  UINT8                 count;                   // number of storage disks
  PSTORAGE_DISK_INFO    storageInfo;             // array of storage disk info 
} STORAGE_DISK_LIST, *PSTORAGE_DISK_LIST;


/**
 * Function to get a disk partition type guid by a given 
 * disk partition type enum 
 *  
 * @param DiskType      - Partition type enum
 * @Param DiskTypeGuid  - Disk type GUID
 *
 * @return : EFI_STATUS
 */
EFI_STATUS
FwUpdateGetDiskPartitionTypeGuid(
    IN  FWENTRY_DISK_PARTITION_TYPE  DiskType,
    OUT EFI_GUID                    *DiskTypeGuid
    );

/**
 * Function to get  partition handle
 * 
 * @param PartHandle    - partition handle
 * @param EmmcType      - Emmc partition type
 * @Param PartTypeGuid  - Partition type GUID
 * @Param PartitionName - Partition name
 * @Param GetFATHandle  - TRUE  - Filter from FAT partition handles
 *                        FALSE - Filter from BLOCKIO handles
 * @return : EFI_STATUS
 */
EFI_STATUS
FwUpdateGetPartitionHandle(
  IN OUT EFI_HANDLE                *PartHandle,
    IN FWENTRY_DISK_PARTITION_TYPE  DiskType,
    IN EFI_GUID                    *PartTypeGuid,
    IN CHAR16                      *PartitionName,
    IN BOOLEAN                      GetFATHandle
    );

/**
* Depending on the device flash type, EMMC or UFS or SPINOR-NVME, returns
* the GUID for the BOOT/LUN1/LUN2/SPINOR and GPP/LUN4/NVME partition
*
* @param BOOTGUID - GUID number for the BOOT/LUN1/LUN2/SPINOR partition.
* @param GPPGUID  - GUID number for the GPP/LUN4/NVME partition.
*
* @return EFI_STATUS
*/
EFI_STATUS GetPartitionGUIDs(
  OUT EFI_GUID  *BOOTGUID,
  OUT EFI_GUID  *GPPGUID
  );

/**
* It searches for the MemCardInfo handler using gEfiMemCardInfoProtocolGuid protocol
*
* @param MemCardInfo  - Handler obtained by gEfiMemCardInfoProtocolGuid protocol.
*
* @return EFI_STATUS
*/
EFI_STATUS
GetMemCardInfoHandle(
    OUT EFI_MEM_CARDINFO_PROTOCOL **MemCardInfo
   );
   
/**
* Identifies the boot LUN number in a UFS device
*
* @param LUN  - UFS LUN number.
*
* @return EFI_STATUS
*/
EFI_STATUS GetBootLUN(
  OUT UINT32  *LUN
  );

/**
 * Finds the blockIOHandle for the given Vendor GUID which is 
 * defined in MMCHS driver 
 * 
 * @param memoryGUID  - Vendor GUID to find the BlockIOHandle 
 * @param hBlockIO    - BlockIO handle
 * 
 * @return EFI_STATUS
 */

EFI_STATUS
GetDiskTypeHandle(
    IN  EFI_GUID                memoryGUID,
    OUT EFI_BLOCK_IO_PROTOCOL **hBlockIO
   );

/**
* Function to get StorageDiskList.
*
* @param pList - Storage disks supported by device flash type (UFS/SPINOR-NVME/EMMC)
*
* @return EFI_STATUS
*/
EFI_STATUS
GetStorageDiskList(
    OUT PSTORAGE_DISK_LIST    *pList
    );

/**
 * Function to get a StorageDiskInfo based on the partition handle.
 *  
 * @param partitionHandle - Handle to the partition
 * @Param pDiskInfo       - Pointer to Disk info structure
 *
 * @return : EFI_STATUS
 */
EFI_STATUS
GetStorageDiskInfoFromPartHandle(
    IN  EFI_HANDLE              partitionHandle,
    OUT PSTORAGE_DISK_INFO     *pDiskInfo
    );

/**
 * Function to get a StorageDiskInfo based on the disk guid.
 *  
 * @param memoryGUID     - Vendor GUID to find the BlockIOHandle 
 * @Param pDiskInfo      - Pointer to Disk info structure
 *
 * @return : EFI_STATUS
 */
EFI_STATUS
GetStorageDiskInfoFromDiskGuid(
    IN  EFI_GUID                memoryGUID,
    OUT PSTORAGE_DISK_INFO     *pDiskInfo
    );

/**
* Sets the flag in StorageDiskList structure if the storage disk has
* partitions marked for update and needs GPT switch. This flag is set to FALSE 
* for UFS boot LUNs as GPT switch is not allowed.
*
* @param partitionHandle - Handle to the partition..
*
* @return EFI_STATUS
*/
EFI_STATUS
SetStorageDiskNeedsSwitchGpt (
    IN EFI_HANDLE        partitionHandle
    );

#endif
