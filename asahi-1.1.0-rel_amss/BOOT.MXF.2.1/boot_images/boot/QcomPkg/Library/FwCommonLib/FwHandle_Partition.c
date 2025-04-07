/** @file PartitionHandles.c
   
  Handles core partition functions for FwCommonLib. 
   
  Maintains a registry of the partitions needed for FwUpdate 
    and provides lookup functions for these partitions and
    their appropriate read/write functions.

  Copyright (c) 2011-2012,2016-2019,2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when           who         what, where, why
 --------       ---         --------------------------------------------------
 2023/01/19     dmohan      Changes to support Dual SPINOR
 2019/03/28     vkasilya    Added BLK_IO_SEL_STRING_CASE_INSENSITIVE to avoid No handles found failure
 2018/05/31     prema       Change to support capsule update for SPINOR-NVME devices
 2018/05/21     gparam      Changes to move all file based state-machine data to NV +
                            Cleanup of unused functions after the file to NV migration
 2017/04/18     gparam      Removed unused/redundant definitions/parameters
 2017/02/13     gpavithr    Removed the log message which prints ACTIVE LUN in GetBootLUN
 2016/12/07     ssumit      Replaced #define GUIDs with extern variables
 2016/06/27     edg         Modified FwUpdateGetEmmcPartitionTypeGuid function to be generic for UFS support
 2012/11/15     mic         Added FwUpdateGetEmmcPartitionTypeGuid function
 2012/10/17     rs          Changes in FwUpdateGetPartitionHandle to check for
                            Partition Name
 2012/07/10     rs          Changes in FindinFV to check all FWFile Enums
 2011/10/12     jthompso    Initial version

=============================================================================*/

#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/FwCommonLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/BootConfig.h>
#include <Library/DevicePathLib.h>
#include <Pi/PiDxeCis.h>
#include <Protocol/SimpleFileSystem.h>
#include <Protocol/BlockIo.h>
#include <Protocol/FirmwareVolume2.h>
#include <Include/Library/QcomLib.h>
#include <Include/api/storage/ufs_api.h>
#include <Include/Protocol/EFICardInfo.h>
#include "FwHandle_Partition.h"
#include <Library/MemoryAllocationLib.h>

#define     MAX_DISKS                   5

/* UFS Device Path */
typedef struct {
   VENDOR_DEVICE_PATH  Ufs;
   EFI_DEVICE_PATH     End;
} QCUFS_DEVICE_PATH;

extern GUID gEfiPartitionTypeGuid;
extern EFI_GUID gQcomTokenSpaceGuid;
extern EFI_GUID gEfiPartitionRecordGuid;
extern EFI_GUID gEfiMemCardInfoProtocolGuid;
extern EFI_GUID gEfiEmmcUserPartitionGuid;
extern EFI_GUID gEfiEmmcBootPartition1Guid;
extern EFI_GUID gEfiEmmcBootPartition2Guid;
extern EFI_GUID gEfiEmmcRpmbPartitionGuid;
extern EFI_GUID gEfiEmmcGppPartition1Guid;
extern EFI_GUID gEfiEmmcGppPartition2Guid;
extern EFI_GUID gEfiEmmcGppPartition3Guid;
extern EFI_GUID gEfiEmmcGppPartition4Guid;
extern EFI_GUID gEfiUfsLU0Guid;
extern EFI_GUID gEfiUfsLU1Guid;
extern EFI_GUID gEfiUfsLU2Guid;
extern EFI_GUID gEfiUfsLU3Guid;
extern EFI_GUID gEfiUfsLU4Guid;
extern EFI_GUID gEfiUfsLU5Guid;
extern EFI_GUID gEfiUfsLU6Guid;
extern EFI_GUID gEfiUfsLU7Guid;
extern EFI_GUID gEfiSpiNor0Guid;
extern EFI_GUID gEfiSpiNor1Guid;
extern EFI_GUID gEfiNvme0Guid;

CONST EFI_GUID *FwEntryDiskPartitionGuids[FWENTRY_DISK_PARTITION_MAX] = {
    &gEfiEmmcUserPartitionGuid,
    &gEfiEmmcBootPartition1Guid,
    &gEfiEmmcBootPartition2Guid,
    &gEfiEmmcRpmbPartitionGuid,
    &gEfiEmmcGppPartition1Guid,
    &gEfiEmmcGppPartition2Guid,
    &gEfiEmmcGppPartition3Guid,
    &gEfiEmmcGppPartition4Guid,
    &gEfiUfsLU0Guid,
    &gEfiUfsLU1Guid,
    &gEfiUfsLU2Guid,
    &gEfiUfsLU3Guid,
    &gEfiUfsLU4Guid,
    &gEfiUfsLU5Guid,
    &gEfiUfsLU6Guid,
    &gEfiUfsLU7Guid,
    &gEfiSpiNor0Guid,
    &gEfiNvme0Guid
};

STORAGE_DISK_LIST       StorageDiskList = {0};

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
    )
{
    if ((DiskType >=  FWENTRY_DISK_PARTITION_MAX) ||
        (DiskTypeGuid == NULL))
    {
        return EFI_INVALID_PARAMETER;
    }

    CopyMem((VOID*)DiskTypeGuid, (VOID*)FwEntryDiskPartitionGuids[DiskType], sizeof(EFI_GUID));
    
    return EFI_SUCCESS;
  
}

/**
 * Function to get a matching partition handle
 * after comparing the Disk type, Partition Name and 
 * Partition type GUID
 *  
 * @param PartHandle    - partition handle
 * @param DiskType      - Disk partition type
 * @Param PartTypeGuid  - Partition type GUID
 * @Param PartitionName - Partition name
 * @Param GetFATHandle  - TRUE  - Filter from FAT partition handles
 *                        FALSE - Filter from BLOCKIO handles
 * @return : EFI_STATUS
 */
EFI_STATUS
FwUpdateGetPartitionHandle(
    IN OUT EFI_HANDLE              *PartHandle,
    IN FWENTRY_DISK_PARTITION_TYPE  DiskType,
    IN EFI_GUID                    *PartTypeGuid,
    IN CHAR16                      *PartitionName,
    IN BOOLEAN                      GetFATHandle
    )
{
  EFI_STATUS                        Status           = EFI_SUCCESS;
  UINT32                            MaxHandles       = 0;
  UINT32                            Attrib           = 0;
  HandleInfo                        HandleInfoList[2];
  PartiSelectFilter                 HandleFilter;

  MaxHandles = sizeof(HandleInfoList)/sizeof(*HandleInfoList);

  Attrib |= BLK_IO_SEL_PARTITIONED_GPT;
  Attrib |= BLK_IO_SEL_MATCH_PARTITION_TYPE_GUID;
  Attrib |= BLK_IO_SEL_MATCH_ROOT_DEVICE;
  Attrib |= BLK_IO_SEL_MATCH_PARTITION_LABEL;
  Attrib |= BLK_IO_SEL_STRING_CASE_INSENSITIVE;
  
  if (TRUE == GetFATHandle) {
    Attrib |= BLK_IO_SEL_SELECT_MOUNTED_FILESYSTEM;
  }


  HandleFilter.PartitionType   = PartTypeGuid;
  HandleFilter.RootDeviceType  = NULL;
  HandleFilter.VolumeName      = 0;
  HandleFilter.PartitionLabel  = PartitionName;

  // RootDeviceType need to be defined only for UFS boot LUNs as
  // partitions with same GUID will exist only in LUN1 and LUN2.
  if ((boot_from_ufs ()) && 
      ((DiskType == FWENTRY_UFS_LUN1) || (DiskType == FWENTRY_UFS_LUN2)))
  {
    Attrib |= BLK_IO_SEL_MATCH_ROOT_DEVICE;
    HandleFilter.RootDeviceType  = (EFI_GUID*)FwEntryDiskPartitionGuids[DiskType];
  }

  Status = GetBlkIOHandles(Attrib, &HandleFilter, HandleInfoList, &MaxHandles);

  if(EFI_SUCCESS == Status) {
    if(MaxHandles == 0) {
      Status = EFI_NOT_FOUND;
      DEBUG(( EFI_D_WARN, "No handles found for the given criteria.\n"));
      goto FwUpdateGetPartitionHandleExit;
    }
    if(MaxHandles != 1) {
      Status = EFI_UNSUPPORTED;
      DEBUG(( EFI_D_WARN, "GetBlkIOHandles returned more than one handles. Returning %r\n", Status));
      goto FwUpdateGetPartitionHandleExit;
    }
  }

  *PartHandle = HandleInfoList[0].Handle;

FwUpdateGetPartitionHandleExit:

  return Status;

}

/**
* Depending on the device flash type, EMMC or UFS or SPINOR-NVME, returns
* the GUID for the BOOT/LUN1/LUN2/SPINOR and GPP/LUN4/NVME partition
*
* @param BOOTGUID - GUID number for the BOOT/LUN1/LUN2/SPINOR partition.
* @param GPPGUID  - GUID number for the GPP/LUN4/NVME partition.
*
* @return EFI_STATUS
*/
EFI_STATUS
GetPartitionGUIDs(
   OUT EFI_GUID  *BOOTGUID,
   OUT EFI_GUID  *GPPGUID
   )
{
    EFI_STATUS   Status        = EFI_SUCCESS;
    UINT32       BootLunNumber = 0;
    UINT32       LunNumber1    = 1;
    UINT32       LunNumber2    = 2;
    EFI_GUID     LUN1GUID      = gEfiUfsLU1Guid;
    EFI_GUID     LUN2GUID      = gEfiUfsLU2Guid;
    EFI_GUID     LUN4GUID      = gEfiUfsLU4Guid;
    EFI_GUID     emmcBootGUID  = gEfiEmmcBootPartition1Guid;
    EFI_GUID     emmcGPPGUID   = gEfiEmmcGppPartition1Guid;
    EFI_GUID     SPINOR_GUID   = gEfiSpiNor0Guid;
    EFI_GUID     NVME_GUID     = gEfiNvme0Guid;

    if (BOOTGUID == NULL || GPPGUID == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    /* Getting BOOTGUID and GPPGUID depending on device's flash type: eMMC or UFS */
    /* UFS device requires extra check to determine bootable LUN: LUN1 or LUN2    */
    if (boot_from_ufs())
    {
        Status = GetBootLUN(&BootLunNumber);
        HANDLE_ERROR_LABEL(Status, GetBootLUN, GetPartitionGUIDsExit);

        if (BootLunNumber == LunNumber1)
        {
            CopyMem((VOID*)BOOTGUID, (VOID*)&LUN1GUID, sizeof (EFI_GUID));
            CopyMem((VOID*)GPPGUID,  (VOID*)&LUN4GUID, sizeof (EFI_GUID));
            Status = EFI_SUCCESS;
        }
        else if (BootLunNumber == LunNumber2)
        {
            CopyMem((VOID*)BOOTGUID, (VOID*)&LUN2GUID, sizeof (EFI_GUID));
            CopyMem((VOID*)GPPGUID,  (VOID*)&LUN4GUID, sizeof (EFI_GUID));
            Status = EFI_SUCCESS;
        }
        else
        {
            Status = EFI_NOT_FOUND;
            DEBUG_ERR_LABEL("Could not determine Boot LUN", GetPartitionGUIDsExit);
        }
    }
    else if (boot_from_emmc())
    {
        CopyMem((VOID*)BOOTGUID, (VOID*)&emmcBootGUID, sizeof (EFI_GUID));
        CopyMem((VOID*)GPPGUID,  (VOID*)&emmcGPPGUID, sizeof (EFI_GUID));
        Status = EFI_SUCCESS;
    }
    else if (boot_from_spi_nor())
    {
        CopyMem((VOID*)BOOTGUID, (VOID*)&SPINOR_GUID, sizeof (EFI_GUID));
        CopyMem((VOID*)GPPGUID,  (VOID*)&NVME_GUID, sizeof (EFI_GUID));
        Status = EFI_SUCCESS;
    }
    else
    {
        Status = EFI_INCOMPATIBLE_VERSION;
        DEBUG_ERR_LABEL("Could not determine Boot flash type", GetPartitionGUIDsExit);
    }

GetPartitionGUIDsExit:

    return Status;
}

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
   )
{
    EFI_STATUS            Status           = EFI_SUCCESS;
    UINTN                 NumHandles       = 0;
    EFI_HANDLE            *HandleBuffer    = NULL;
    UINTN                 HandleCounter;
    QCUFS_DEVICE_PATH     *DevicePath       = NULL;


    if (MemCardInfo == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    Status = gBS->LocateHandleBuffer(ByProtocol,
                                     &gEfiMemCardInfoProtocolGuid,
                                     NULL,
                                     &NumHandles,
                                     &HandleBuffer);
    ERR_HANDLE(Status);
    
    for(HandleCounter = 0; HandleCounter < NumHandles; HandleCounter++)
    {
        // Get MemCardInfo
        Status = gBS->HandleProtocol(HandleBuffer[HandleCounter],
                                     &gEfiMemCardInfoProtocolGuid,
                                    (VOID**)MemCardInfo);  

        if(EFI_ERROR(Status))
        {
           continue;
        }

        // Compare MemCardInfo to UFS LUN1
        DevicePath = (QCUFS_DEVICE_PATH *) DevicePathFromHandle(HandleBuffer[HandleCounter]);
        
        if(DevicePath == NULL)
        {
            continue;
        }

        if (CompareGuid(&DevicePath->Ufs.Guid, (FwEntryDiskPartitionGuids[FWENTRY_UFS_LUN1]))) 
        {
            Status = EFI_SUCCESS;
            goto GetMemCardInfoHandleExit;
        }
    }

    Status = EFI_NOT_FOUND;

GetMemCardInfoHandleExit:
    if(HandleBuffer != NULL)
    {
        gBS->FreePool(HandleBuffer);
        HandleBuffer = NULL;
    }

    return Status;
}

/**
* Identifies the boot LUN number in a UFS device
*
* @param LUN  - UFS LUN number.
*
* @return EFI_STATUS
*/
EFI_STATUS
GetBootLUN(
    OUT UINT32  *LUN
    )
{
    EFI_STATUS                Status           = EFI_SUCCESS;
    EFI_MEM_CARDINFO_PROTOCOL *MemCardInfo     = NULL;
    UINT32                    BootLUN          = 0;       

    if (LUN == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    Status = GetMemCardInfoHandle(&MemCardInfo);
    HANDLE_ERROR_LABEL(Status, GetMemCardInfoHandle, GetBootLUNExit);

    Status = MemCardInfo->GetBootLU(MemCardInfo, &BootLUN);
    HANDLE_ERROR_LABEL(Status, MemCardInfo->GetBootLU, GetBootLUNExit);

    *LUN = BootLUN;

GetBootLUNExit:

    return Status;

}

/**
 * Finds the blockIOHandle for the given Vendor GUID which is 
 * defined in MMCHS driver 
 * 
 * @param memoryGUID   - Vendor GUID to find the BlockIOHandle 
 * @param hBlockIO     - BlockIO handle
 *
 * @return EFI_STATUS
 */
EFI_STATUS
GetDiskTypeHandle(
    IN  EFI_GUID                memoryGUID,
    OUT EFI_BLOCK_IO_PROTOCOL **hBlockIO
   )
{
    EFI_STATUS          status        = EFI_SUCCESS;
    UINT32              attribs       = 0;
    PartiSelectFilter   handleFilter;
    // Use size as 2 to detect existance of more than one capsule partition while query
    HandleInfo          handleInfoList [10];
    UINT32              noHandles     = sizeof(handleInfoList) / sizeof(*handleInfoList);

    if (hBlockIO == NULL)
    {
        status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    /* Initialize output parameter*/
    *hBlockIO = NULL;

    attribs |= BLK_IO_SEL_MATCH_ROOT_DEVICE;
    attribs |= BLK_IO_SEL_SELECT_ROOT_DEVICE_ONLY;
  
    handleFilter.VolumeName = NULL;
    handleFilter.RootDeviceType = &memoryGUID;
    handleFilter.PartitionType = NULL;
    handleFilter.PartitionLabel = NULL;
    
    status = GetBlkIOHandles(attribs, &handleFilter, handleInfoList, &noHandles);
    
    if ((EFI_ERROR (status)) ||
        (0 == noHandles)) {
      DEBUG ((EFI_D_ERROR, "Failed to find handle for given root device type. Status: %r\n", status));
      status = (EFI_ERROR (status) ? status : EFI_NOT_FOUND);
      goto Exit;
    }

#if 0  // TODO: Prem: Handle as per response from UEFI team
    if (NoHandles != 1) {
      DEBUG ((EFI_D_ERROR, "Error: More than 1 handle found for the given root device type.\n"));
      Status = EFI_UNSUPPORTED;
      goto GetDiskTypeHandleExit;
    }
#endif // #if 0

    *hBlockIO = handleInfoList[0].BlkIo;

Exit:

    return status;
}

/**
* Depending on the device flash type (EMMC/UFS/SPINOR-NVME), returns
* the array of disk type (boot and gpp) GUIDs.
*
* @param pDiskCount      - Number of disk types.
* @param pDiskTypeGuids  - Array of disk type GUIDs.
*
* @return EFI_STATUS
*/
EFI_STATUS
GetDiskTypeGuids(
    OUT UINT8           *pDiskCount,
    OUT EFI_GUID        *pDiskTypeGuids
   )
{
    EFI_STATUS                   status        = EFI_SUCCESS;
    UINT32                       bootLunNumber = 0;
    UINT32                       lunNumber1    = 1;
    UINT32                       lunNumber2    = 2;
    EFI_GUID                     lun1Guid      = gEfiUfsLU1Guid;
    EFI_GUID                     lun2Guid      = gEfiUfsLU2Guid;
    EFI_GUID                     lun4Guid      = gEfiUfsLU4Guid;
    EFI_GUID                     emmcBootGuid  = gEfiEmmcBootPartition1Guid;
    EFI_GUID                     emmcGppGuid   = gEfiEmmcGppPartition1Guid;
    EFI_GUID                     spinor0Guid   = gEfiSpiNor0Guid;
    EFI_GUID                     spinor1Guid   = gEfiSpiNor1Guid;
    EFI_GUID                     nvmeGuid      = gEfiNvme0Guid;
    EFI_BLOCK_IO_PROTOCOL       *hBlkIoHandle  = NULL;

    if (pDiskCount == NULL || pDiskTypeGuids == NULL)
    {
        status= EFI_INVALID_PARAMETER;
        goto Exit;
    }

    // Getting disk type GUIDs depending on device's flash type.
    // UFS device requires extra check to determine bootable LUN: LUN1 or LUN2
    if (boot_from_ufs())
    {
        *pDiskCount = 2;
        status = GetBootLUN(&bootLunNumber);
        HANDLE_ERROR_LABEL(status, GetBootLUN, Exit);

        if (bootLunNumber == lunNumber1)
        {
            CopyMem((VOID*)&pDiskTypeGuids[0], (VOID*)&lun1Guid, sizeof (EFI_GUID));
            CopyMem((VOID*)&pDiskTypeGuids[1], (VOID*)&lun4Guid, sizeof (EFI_GUID));
        }
        else if (bootLunNumber == lunNumber2)
        {
            CopyMem((VOID*)&pDiskTypeGuids[0], (VOID*)&lun2Guid, sizeof (EFI_GUID));
            CopyMem((VOID*)&pDiskTypeGuids[1], (VOID*)&lun4Guid, sizeof (EFI_GUID));
        }
        else
        {
            status = EFI_NOT_FOUND;
            DEBUG_ERR_LABEL("Could not determine Boot LUN", Exit);
        }
    }
    else if (boot_from_emmc())
    {
        *pDiskCount = 2;
        CopyMem((VOID*)&pDiskTypeGuids[0], (VOID*)&emmcBootGuid, sizeof (EFI_GUID));
        CopyMem((VOID*)&pDiskTypeGuids[1], (VOID*)&emmcGppGuid, sizeof (EFI_GUID));
    }
    else if (boot_from_spi_nor())
    {
        *pDiskCount = 2;
        CopyMem((VOID*)&pDiskTypeGuids[0], (VOID*)&spinor0Guid, sizeof (EFI_GUID));
        CopyMem((VOID*)&pDiskTypeGuids[1], (VOID*)&nvmeGuid, sizeof (EFI_GUID));

        // Get the handle for SPINOR1 disk type
        status = GetDiskTypeHandle(spinor1Guid, &hBlkIoHandle);
        if (status == EFI_SUCCESS)
        {
            DEBUG((EFI_D_WARN, "GetDiskTypeGuids: Dual Spinor supported\n"));
            CopyMem((VOID*)&pDiskTypeGuids[2], (VOID*)&spinor1Guid, sizeof (EFI_GUID));
            (*pDiskCount)++;
        }
        else if (status == EFI_NOT_FOUND)
        {
            // BlkIO handle to SPINOR1 disk not found indicates it is a 
            // single SPINOR device.
            DEBUG((EFI_D_INFO, "GetDiskTypeGuids: Dual Spinor NOT supported\n"));
            status = EFI_SUCCESS;
        }
    }
    else
    {
        status = EFI_INCOMPATIBLE_VERSION;
        DEBUG_ERR_LABEL("Could not determine Boot flash type", Exit);
    }

Exit:
    return status;
}

/**
* Populates the storage disks(boot and gpp disks) supported based on the device 
* flash type (EMMC/UFS/SPINOR-NVME) to StorageDiskList.
*
* @param None
*
* @return EFI_STATUS
*/
EFI_STATUS
InitStorageDiskInfo (VOID)
{
    EFI_STATUS     status                      = EFI_SUCCESS;
    UINT8          diskCount                   = 0;
    UINT8          diskIdx                     = 0;
    EFI_GUID       diskGuidEntries[MAX_DISKS]  = {0};
    PSTORAGE_DISK_INFO    pStorageDiskInfo     = NULL;

    status = GetDiskTypeGuids(&diskCount, diskGuidEntries);
    HANDLE_ERROR_LABEL(status, GetDiskTypeGuids, Exit);

    StorageDiskList.count = diskCount;
    StorageDiskList.storageInfo = AllocateZeroPool(sizeof(STORAGE_DISK_INFO) * diskCount);
    if (NULL == StorageDiskList.storageInfo)
    {
        status = EFI_OUT_OF_RESOURCES;
        DEBUG_ERR_LABEL(
            "InitStorageDiskInfo: Memory allocation failed.\n",
             Exit
            );
    }

    for (diskIdx = 0; diskIdx < diskCount; diskIdx++)
    {
        pStorageDiskInfo = &StorageDiskList.storageInfo[diskIdx];

        CopyMem(&pStorageDiskInfo->guid, &diskGuidEntries[diskIdx], sizeof (EFI_GUID));
        DEBUG(( 
            EFI_D_INFO,
            "InitStorageDiskInfo: storageInfo[%d].guid: %g\n",
            diskIdx, &pStorageDiskInfo->guid)
            );

        status = GetGptDataForDisk(
                   pStorageDiskInfo->guid,
                   &pStorageDiskInfo->nvType,
                   NULL,
                   &pStorageDiskInfo->nvDataMaxEntries
                   );
        HANDLE_ERROR_LABEL(status, GetGptDataForDisk, Exit);
    }

Exit:
    if (EFI_ERROR(status))
    {
        if (NULL != StorageDiskList.storageInfo)
        {
          FreePool(StorageDiskList.storageInfo);
          StorageDiskList.storageInfo = NULL;
        }
    }

    return status;
}

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
    )
{
    EFI_STATUS      status = EFI_SUCCESS;

    if(pList == NULL)
    {
        status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    if((0 == StorageDiskList.count) || (NULL == StorageDiskList.storageInfo))
    {
        status = EFI_NOT_FOUND;
        goto Exit;
    }

    *pList = &StorageDiskList;

Exit:

    return status;
};

/**
 * Function to get a StorageDiskInfo based on the partition handle.
 *  
 * @param partitionHandle  - Handle to the partition
 * @Param pDiskInfo        - Pointer to Disk info structure
 *
 * @return : EFI_STATUS
 */
EFI_STATUS
GetStorageDiskInfoFromPartHandle(
    IN  EFI_HANDLE              partitionHandle,
    OUT PSTORAGE_DISK_INFO     *pDiskInfo
    )
{
    EFI_STATUS               status              = EFI_SUCCESS;
    UINT8                    diskIdx             = 0;
    PSTORAGE_DISK_INFO       pStorageDiskInfo    = NULL;
    PSTORAGE_DISK_LIST       pDiskList           = NULL;
    VENDOR_DEVICE_PATH      *pDevPathInst        = NULL;

    //Check input parameters
    if ((NULL == pDiskInfo) ||
        (NULL == partitionHandle))
    {
        status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    status = gBS->HandleProtocol (partitionHandle,
                                  &gEfiDevicePathProtocolGuid,
                                  (VOID **) &pDevPathInst);
    if (EFI_ERROR(status))
    {
        DEBUG_ERR_LABEL(
            "GetStorageDiskInfoFromPartHandle: HandleProtocol failed.\n",
             Exit);
    }

    DEBUG((
        EFI_D_INFO,
        "GetStorageDiskInfoFromPartHandle: DevPathInst->Guid: %g\n",
        &pDevPathInst->Guid));

    status = GetStorageDiskList(&pDiskList);
    HANDLE_ERROR_LABEL(status, GetStorageDiskList, Exit);

    for (diskIdx = 0; diskIdx < pDiskList->count; diskIdx++)
    {
        pStorageDiskInfo = &pDiskList->storageInfo[diskIdx];
        if (NULL == pStorageDiskInfo)
        {
            status = EFI_NOT_FOUND;
            DEBUG_ERR_LABEL (
                "GetStorageDiskInfoFromPartHandle: pDiskInfo is NULL\n",
                Exit);;
        }

        if (CompareGuid(&pStorageDiskInfo->guid, &pDevPathInst->Guid))
        {
            *pDiskInfo = pStorageDiskInfo;
            break;
        }
    }

    if (NULL == *pDiskInfo)
    {
        DEBUG((
            EFI_D_ERROR,
            "GetStorageDiskInfoFromPartHandle: Diskinfo not found for diskguid: %g\n",
            &pDevPathInst->Guid));
        status = EFI_NOT_FOUND;
        goto Exit;
    }

Exit:

    return status;
}

/**
 * Function to get a StorageDiskInfo based on the disk guid.
 *  
 * @param memoryGuid      - Vendor GUID to find the BlockIOHandle 
 * @Param pDiskInfo       - Pointer to Disk info structure
 *
 * @return : EFI_STATUS
 */
EFI_STATUS
GetStorageDiskInfoFromDiskGuid(
    IN  EFI_GUID                memoryGuid,
    OUT PSTORAGE_DISK_INFO     *pDiskInfo
    )
{
    EFI_STATUS               status               = EFI_SUCCESS;
    UINT8                    diskIdx              = 0;
    PSTORAGE_DISK_INFO       pStorageDiskInfo     = NULL;
    PSTORAGE_DISK_LIST       pDiskList            = NULL;

    //Check input parameters
    if (NULL == pDiskInfo)
    {
        status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    status = GetStorageDiskList(&pDiskList);
    HANDLE_ERROR_LABEL(status, GetStorageDiskList, Exit);

    for (diskIdx = 0; diskIdx < pDiskList->count; diskIdx++)
    {
        pStorageDiskInfo = &pDiskList->storageInfo[diskIdx];
        if (NULL == pStorageDiskInfo)
        {
            status = EFI_NOT_FOUND;
            DEBUG_ERR_LABEL (
                "GetStorageDiskInfoFromDiskGuid: pDiskInfo is NULL\n",
                Exit);;
        }

        if (CompareGuid(&pStorageDiskInfo->guid, &memoryGuid))
        {
            *pDiskInfo = pStorageDiskInfo;
            break;
        }
    }

    if (NULL == *pDiskInfo)
    {
        DEBUG((
            EFI_D_ERROR,
            "GetStorageDiskInfoFromDiskGuid: Diskinfo not found for diskguid: %g\n",
            &memoryGuid));
        status = EFI_NOT_FOUND;
        goto Exit;
    }

Exit:

    return status;
}

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
    )
{
    EFI_STATUS               status       = EFI_SUCCESS;
    VENDOR_DEVICE_PATH      *pDevPathInst  = NULL;
    UINT8                    diskIdx      = 0;
    PSTORAGE_DISK_INFO       pDiskInfo    = NULL;
    PSTORAGE_DISK_LIST       pDiskList    = NULL;

    status = gBS->HandleProtocol (partitionHandle,
                                  &gEfiDevicePathProtocolGuid,
                                  (VOID **) &pDevPathInst);
    if (EFI_ERROR(status))
    {
        DEBUG_ERR_LABEL(
            "SetStorageDiskNeedsSwitchGpt: HandleProtocol failed.\n",
             Exit
            );
    }
    DEBUG(( EFI_D_INFO, "SetStorageDiskNeedsSwitchGpt: RootDeviceTypeGuid: %g\n", &pDevPathInst->Guid));

    status = GetStorageDiskList(&pDiskList);
    HANDLE_ERROR_LABEL(status, GetStorageDiskList, Exit);

    for (diskIdx = 0; diskIdx < pDiskList->count; diskIdx++)
    {
        pDiskInfo = &pDiskList->storageInfo[diskIdx];
        if (NULL == pDiskInfo)
        {
            status = EFI_NOT_FOUND;
            DEBUG_ERR_LABEL (
                "SetStorageDiskNeedsSwitchGpt: pDiskInfo is NULL\n",
                Exit);;
        }

        if ((!pDiskInfo->switchGPT) &&
            (CompareGuid(&pDiskInfo->guid, &pDevPathInst->Guid)) &&
            (!CompareGuid(&pDiskInfo->guid, &gEfiUfsLU1Guid)) &&
            (!CompareGuid(&pDiskInfo->guid, &gEfiUfsLU2Guid)))
        {
            pDiskInfo->switchGPT = TRUE;
            DEBUG((EFI_D_INFO, "SetStorageDiskNeedsSwitchGpt: TRUE\n"));
        }
    }

Exit:
    return status;
}
