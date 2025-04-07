/** @file FwGptHelpers.c
   
  GUID Partition Table (GPT) functions for FwCommonLib.

  Copyright (c) 2011-2016, 2018, 2020-2021, 2023 Qualcomm Technologies, Inc . All rights reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/

/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


 when           who         what, where, why
 --------       ---         --------------------------------------------------
 2023/01/19     dmohan      Changes to support Dual SPINOR
 2021/06/30     dmohan      Changes to support A/B Recovery feature
 2020/02/24     kbarad      Modified BackupGPTTable() to more generic to only taking backup of GPT
 2018/07/20     gparam      KW Fixes
 2018/07/11     prema       Changes to move GPT backup from file to NV
 2018/07/11     rajb        Added support to get active GPT data from main GPT & vice
                            versa. Implemented compression & decompression support 
                            for GPT data to store to NV
 2018/05/31     prema       Change to support capsule update for SPINOR-NVME devices
 2018/05/21     gparam      Changes to move all file based state-machine data to NV +
                            Cleanup of unused functions after the file to NV migration
 2016/12/07     ssumit      Replaced #define GUIDs with extern variables
 2016/08/29     ltg         Added UFS support
 2015/04/15     mic         Added 64bit firmware update support
 2014/17/10     tj          KW Fixes
 2014/04/21     mic         Fixed KW warnings
 2012/12/11     mic         Fixed KW warnings
 2012/11/14     mic         Added robustness for GPT copy and restore functions
 2012/11/12     rs          Swap ParitionName also when switching GPT
 2012/10/10     jd          Handle GPT switch based on firmware entry list   
 2012/10/08     mic         renamed gpt functions
 2011/10/12     hozefak     Initial version

=============================================================================*/

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/FwCommonLib.h>
#include <Library/DebugLib.h>
#include <Library/QcomLib.h>
#include <Library/zlib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/BlockIo.h>
#include <Protocol/DiskIo.h>
#include <Protocol/DevicePath.h>
#include <Protocol/SimpleFileSystem.h>
#include <Uefi/UefiGpt.h>
#include "FwGpt_Helpers.h"
#include "FwHandle_Partition.h"

#define TYPE_END_DEVICE_PATH       0x7F
#define PRIMARY_HEADER_LBA         0x1

/**
 * This function will write the Buffer into the specified GPT
 * Table. It will also calculate the CRC's and cache the 
 * updated header and table type in pDiskInfo structure. This function should 
 * be followed by call to WriteAllGPTTableCRCs() to rewrite the CRC 
 * across all disks with modified GPT.
 * 
 * @param pFileBuffer  :  Pointer to Buffer which needs to be
 *                        written to the GPT Tables 
 * @param fileSize     :  Pointer to the Size of the buffer
 * @param memoryGuid   :  Vendor GUID whose GPT has to be changed
 * @param tableType    :  Primary or backup GPT table
 * 
 * @return EFI_STATUS 
 */

EFI_STATUS 
WriteGPTTableEntries(
    IN VOID                     *pFileBuffer,
    IN UINTN                     fileSize,
    IN EFI_GUID                  memoryGuid,
    IN GPT_TABLE_TYPE            tableType
)
{
    EFI_STATUS                  status                   = EFI_SUCCESS;
    UINT32                      currentLBA               = 0;
    EFI_PARTITION_ENTRY        *pPartitionEntry          = NULL;
    EFI_PARTITION_TABLE_HEADER *pPartHdr                 = NULL;
    EFI_PARTITION_TABLE_HEADER *pBackupPartHdr           = NULL;
    EFI_PARTITION_TABLE_HEADER *pOutPartitionHeader      = NULL;
    UINT32                      partitionArrayCRC32      = 0;
    UINT32                      crcForHeader             = 0;
    UINT32                      blocksToWrite            = 0;
    UINT32                      blocksToWriteRemainder   = 0;
    UINT8                      *pBlocksToWriteBuffer     = NULL;
    UINT8                      *pBlocksToWriteTempBuffer = NULL;
    EFI_BLOCK_IO_PROTOCOL      *hBlockIoHandleHardDrive  = NULL;
    UINT32                      outStartLBA              = 0;
    UINT32                      partitionEntryArraySize  = 0;
    PSTORAGE_DISK_INFO          pDiskInfo                = NULL;


    status = GetStorageDiskInfoFromDiskGuid(memoryGuid, &pDiskInfo);
    HANDLE_ERROR_LABEL(status, GetStorageDiskInfoFromDiskGuid, Exit);

    /* Get the BlockIO handle for the given Disk type*/
    status = GetDiskTypeHandle(pDiskInfo->guid, &hBlockIoHandleHardDrive);
    HANDLE_ERROR_LABEL(status,GetDiskTypeHandle,Exit);

    if (hBlockIoHandleHardDrive != NULL)
    {
        /* Allocate and zero out buffer for primary GPT */
        status = gBS->AllocatePool(
            EfiBootServicesData,
            hBlockIoHandleHardDrive->Media->BlockSize,
            (VOID*)&pPartHdr);
        HANDLE_ERROR_LABEL(status,gBS->AllocatePool,Exit);
        gBS->SetMem(pPartHdr, hBlockIoHandleHardDrive->Media->BlockSize, 0); 

        /* Read current primary GPT to get the GPT info */
        status =  hBlockIoHandleHardDrive->ReadBlocks(
            hBlockIoHandleHardDrive,
            hBlockIoHandleHardDrive->Media->MediaId,
            PRIMARY_HEADER_LBA,
            hBlockIoHandleHardDrive->Media->BlockSize,
            pPartHdr);
        HANDLE_ERROR_LABEL(status,hBlockIoHandleHardDrive->ReadBlocks,Exit);

        partitionEntryArraySize = (pPartHdr->NumberOfPartitionEntries * pPartHdr->SizeOfPartitionEntry);

        /* Assign the correct writing buffer and start LBA*/
        if(tableType == BACKUP_GPT_TABLE )
        {
            /* Allocate and zero out buffer for Backup GPT */
            status = gBS->AllocatePool(
                EfiBootServicesData,
                hBlockIoHandleHardDrive->Media->BlockSize,
                (VOID*)&pBackupPartHdr);
            HANDLE_ERROR_LABEL(status,gBS->AllocatePool,Exit);
            gBS->SetMem(pBackupPartHdr, hBlockIoHandleHardDrive->Media->BlockSize, 0 );

            /* Read current backup GPT by given PartHdr->AlternateLBA*/
            status =  hBlockIoHandleHardDrive->ReadBlocks(
                hBlockIoHandleHardDrive,
                hBlockIoHandleHardDrive->Media->MediaId,
                pPartHdr->AlternateLBA,
                hBlockIoHandleHardDrive->Media->BlockSize,
                pBackupPartHdr);
            HANDLE_ERROR_LABEL(status,hBlockIoHandleHardDrive->ReadBlocks,Exit);

            pOutPartitionHeader = pBackupPartHdr;
            outStartLBA = pPartHdr->LastUsableLBA + 1;

            gBS->FreePool(pPartHdr);
            pPartHdr = NULL;
        }
        else
        {
            pOutPartitionHeader = pPartHdr;
            outStartLBA = pPartHdr->MyLBA + 1;
        }

        pPartitionEntry = (EFI_PARTITION_ENTRY*)pFileBuffer;

        /*Calculate the PartitionEntryArrayCRC32 of the input GPT buffer*/
        status = gBS->CalculateCrc32 (
            pFileBuffer, 
            (pOutPartitionHeader->NumberOfPartitionEntries * pOutPartitionHeader->SizeOfPartitionEntry),
            &partitionArrayCRC32);
        HANDLE_ERROR_LABEL(status, gBS->CalculateCrc32, Exit);

        pOutPartitionHeader->PartitionEntryArrayCRC32 = partitionArrayCRC32;

        //Clear out the CRC to calculate the new header CRC
        pOutPartitionHeader->Header.CRC32 = 0;
        status = gBS->CalculateCrc32 (
            pOutPartitionHeader,
            pOutPartitionHeader->Header.HeaderSize,
            &crcForHeader);
        HANDLE_ERROR_LABEL(status, gBS->CalculateCrc32, Exit);

        pOutPartitionHeader->Header.CRC32 = crcForHeader;

        blocksToWrite = (partitionEntryArraySize / hBlockIoHandleHardDrive->Media->BlockSize);
        blocksToWriteRemainder = (partitionEntryArraySize % hBlockIoHandleHardDrive->Media->BlockSize);
        blocksToWrite += (blocksToWriteRemainder == 0) ? 0 : 1;

        // Allocate and zero out buffer for blocks to be written 
        status = gBS->AllocatePool(
            EfiBootServicesData,
            (blocksToWrite * hBlockIoHandleHardDrive->Media->BlockSize),
            (VOID*)&pBlocksToWriteBuffer);
        HANDLE_ERROR_LABEL(status, gBS->AllocatePool, Exit);
        gBS->SetMem(pBlocksToWriteBuffer, blocksToWrite * hBlockIoHandleHardDrive->Media->BlockSize, 0);
        if (fileSize <= (blocksToWrite * hBlockIoHandleHardDrive->Media->BlockSize))
        {
            gBS->CopyMem(pBlocksToWriteBuffer, pPartitionEntry, fileSize);
        }
        else
        {
            status = EFI_BAD_BUFFER_SIZE;
            HANDLE_ERROR_LABEL(status, gBS->CopyMem, Exit);
        }
        pBlocksToWriteTempBuffer = pBlocksToWriteBuffer;

        //Start to write all the partition entries
        for(currentLBA = outStartLBA; currentLBA < (outStartLBA + blocksToWrite); currentLBA++) 
        {
            status = hBlockIoHandleHardDrive->WriteBlocks (
                hBlockIoHandleHardDrive,
                hBlockIoHandleHardDrive->Media->MediaId,
                currentLBA,
                hBlockIoHandleHardDrive->Media->BlockSize,
                pBlocksToWriteTempBuffer
                );
            HANDLE_ERROR_LABEL(status, hBlockIoHandleHardDrive->WriteBlocks, Exit);

           pBlocksToWriteTempBuffer += hBlockIoHandleHardDrive->Media->BlockSize;
        }

        /* Flush the BlockIOHandle */
        status = hBlockIoHandleHardDrive->FlushBlocks (hBlockIoHandleHardDrive);
        HANDLE_ERROR_LABEL(status, hBlockIoHandleHardDrive->FlushBlocks, Exit);

        // At this point, all previous calls would have succeeded 
        // So, updating pDiskInfo structure with updated header and tabletype.
        pDiskInfo->pOutPartitionHeader = pOutPartitionHeader;
        pDiskInfo->partHdrTableType = tableType;
    }
    else
    {
        status = EFI_NOT_FOUND;
        HANDLE_ERROR_LABEL(status,GetDiskTypeHandle,Exit);
    }

Exit:

    if (EFI_ERROR(status))
    {
        if (pPartHdr != NULL)
        {
            gBS->FreePool(pPartHdr);
            pPartHdr = NULL;
        }

        if (pBackupPartHdr != NULL)
        {
            gBS->FreePool(pBackupPartHdr);
            pBackupPartHdr = NULL;
        }
    }

    if (pBlocksToWriteBuffer != NULL)
    {
        gBS->FreePool(pBlocksToWriteBuffer);
        pBlocksToWriteBuffer = NULL;
    }

    return  status;
}

EFI_STATUS 
ClearAllOutPartitionHeaders(VOID)
{
    EFI_STATUS                  status                 = EFI_SUCCESS;
    UINT8                       diskIdx                = 0;
    PSTORAGE_DISK_LIST          pDiskList              = NULL;
    PSTORAGE_DISK_INFO          pDiskInfo              = NULL;

    status = GetStorageDiskList(&pDiskList);
    HANDLE_ERROR_LABEL(status, GetStorageDiskList, Exit);

    for (diskIdx = 0; diskIdx < pDiskList->count; diskIdx++)
    {
        pDiskInfo = &pDiskList->storageInfo[diskIdx];
        if (NULL == pDiskInfo)
        {
            status = EFI_NOT_FOUND;
            DEBUG_ERR_LABEL (
                "ClearAllOutPartitionHeaders: pDiskInfo is NULL\n",
                Exit);
        }

        if (NULL != pDiskInfo->pOutPartitionHeader)
        {
            gBS->FreePool(pDiskInfo->pOutPartitionHeader);
            pDiskInfo->pOutPartitionHeader = NULL;
        }
    }

Exit:

    return status;
}

/**
 * This function will rewrite the partition header with updated CRC values
 * for the modified GPT table across all storage disks. We are doing this 
 * back to back for all disks to reduce the window in committing the
 * updates to the GPT Table when partitions are split across disks
 * i.e. primary partition in disk 1 and backup partition in disk 2.
 * This function should be preceded by call to WriteGPTTableEntries()
 * to compute the CRC across all disks with modified GPT.
 *
 * @param tableType   :  Primary or backup GPT table
 * 
 * @return EFI_STATUS 
 */

EFI_STATUS 
WriteAllGPTTableCRCs(
    IN GPT_TABLE_TYPE   tableType
)
{
    EFI_STATUS                  status                  = EFI_SUCCESS;
    EFI_BLOCK_IO_PROTOCOL      *hBlockIoHandleHardDrive = NULL;
    UINT8                       diskIdx                 = 0;
    PSTORAGE_DISK_LIST          pDiskList               = NULL;
    PSTORAGE_DISK_INFO          pDiskInfo               = NULL;

    status = GetStorageDiskList(&pDiskList);
    HANDLE_ERROR_LABEL(status, GetStorageDiskList, Exit);

    for (diskIdx = 0; diskIdx < pDiskList->count; diskIdx++)
    {
        pDiskInfo = &pDiskList->storageInfo[diskIdx];
        if (NULL == pDiskInfo)
        {
            status = EFI_NOT_FOUND;
            DEBUG_ERR_LABEL ("WriteAllGPTTableCRCs: pDiskInfo is NULL\n", Exit);
        }

        if (pDiskInfo->switchGPT)
        {
            if (NULL == pDiskInfo->pOutPartitionHeader)
            {
                status = EFI_DEVICE_ERROR;
                DEBUG_ERR_LABEL("GPT switched, but Partition header is empty\n",Exit);
            }

            if (tableType != pDiskInfo->partHdrTableType)
            {
                status = EFI_DEVICE_ERROR;
                DEBUG_ERR_LABEL("Mismatch between Cached GPT header type and input TableType\n",Exit);
            }

            /* Get the BlockIO handle for the given Disk type*/
            status = GetDiskTypeHandle(pDiskInfo->guid, &hBlockIoHandleHardDrive);
            HANDLE_ERROR_LABEL(status,GetDiskTypeHandle,Exit);

            if (hBlockIoHandleHardDrive != NULL)
            {
                // Write the Calculated CRC to the partition Header
                status = hBlockIoHandleHardDrive->WriteBlocks (
                    hBlockIoHandleHardDrive,
                    hBlockIoHandleHardDrive->Media->MediaId,
                    pDiskInfo->pOutPartitionHeader->MyLBA,
                    hBlockIoHandleHardDrive->Media->BlockSize,
                    pDiskInfo->pOutPartitionHeader
                    );
                HANDLE_ERROR_LABEL(status, hBlockIoHandleHardDrive->WriteBlocks, Exit);
                
                /* Flush the BlockIOHandle */
                status = hBlockIoHandleHardDrive->FlushBlocks (hBlockIoHandleHardDrive);
                HANDLE_ERROR_LABEL(status, hBlockIoHandleHardDrive->FlushBlocks, Exit);
            }
            else
            {
                status = EFI_NOT_FOUND;
                HANDLE_ERROR_LABEL(status,GetDiskTypeHandle,Exit);
            }
        }
    }

Exit:

    ClearAllOutPartitionHeaders();
    return  status;
}

/**
 * This function will retrive active GPT data from GPT table
 * 
 * @param memoryGuid            :  Vendor GUID whose GPT has to be changed
 * @param tableType             :  Primary or backup GPT table
 * @param pList                 :  Firmware entry list 
 * @param pGPTSubDataPtr        :  Pointer to hold active GPT data
 * 
 * @return EFI_STATUS 
 */

EFI_STATUS
GetActiveGPTDataFromGPT (
    IN  EFI_GUID                      memoryGuid,
    IN  GPT_TABLE_TYPE                tableType,
    IN  FW_LINKED_LIST_TYPE          *pList,
    IN OUT ACTIVE_GPT_SUB_DATA       *pGptSubDataPtr
)
{
    EFI_STATUS                    status                 = EFI_SUCCESS;
    EFI_PARTITION_ENTRY          *pStartPartitionEntry   = NULL;
    EFI_PARTITION_ENTRY          *pPartitionEntry        = NULL;
    UINT32                        numberOfPartitions     = 0;
    UINT32                        sizeOfPartitionEntry   = 0;
    UINT32                        partitionIndex         = 0;
    UINTN                         fileSize               = 0;
    FW_LIST_NODE_TYPE            *pCurrentNode           = NULL;
    QPAYLOAD_FW_ENTRY            *pFwEntry               = NULL;
    FWENTRY_DISK_PARTITION_TYPE   diskPartType;
    UINTN                         i                      = 0;

    if((NULL == pList)||
       (NULL == pGptSubDataPtr))
    {
        return EFI_INVALID_PARAMETER;
    }

    status = GetGptDataForDisk(
        memoryGuid,
        NULL,
        &diskPartType,
        NULL
        );
    HANDLE_ERROR_LABEL(status,GetGptDataForDisk,GetActiveGPTDataFromGPTExit);
    

    status = ReadGPTTable(memoryGuid,
                          (VOID*)&pStartPartitionEntry, 
                          &fileSize, 
                          &sizeOfPartitionEntry,
                          tableType);
    HANDLE_ERROR_LABEL(status,ReadGPTTable,GetActiveGPTDataFromGPTExit);

    pPartitionEntry = pStartPartitionEntry;
    numberOfPartitions = fileSize / sizeOfPartitionEntry;

    /* Go through each partition entry
     for loop 1:
        go through each partition entry by jumping partition etnry size at a time
     for loop 2:
        go through the partition entry info in the List to see if any match.
    */
    for(partitionIndex = 0; partitionIndex < numberOfPartitions; partitionIndex++) 
    {
        pCurrentNode = pList->Head;
        for( i = 0; i < pList->Count; i++) 
        {
            pFwEntry = (QPAYLOAD_FW_ENTRY*)(pCurrentNode->Data);
            if(pFwEntry->Metadata.UpdateType == FWENTRY_UPDATE_TYPE_PARTITION &&
               pFwEntry->Metadata.BackupType == FWENTRY_UPDATE_TYPE_PARTITION &&
               pFwEntry->Metadata.UpdatePath.DiskPartitionType == diskPartType&&
               pFwEntry->Metadata.BackupPath.DiskPartitionType == diskPartType)
            {
                if(CompareGuid(&(pStartPartitionEntry->PartitionTypeGUID), &(pFwEntry->Metadata.UpdatePath.PartitionTypeGUID)) &&
                   CompareMem(pStartPartitionEntry->PartitionName, pFwEntry->Metadata.UpdatePath.PartitionName, StrSize(pStartPartitionEntry->PartitionName)) == 0)
                {
                    if(partitionIndex > pGptSubDataPtr->MaxEntries)
                    {
                        status = EFI_OUT_OF_RESOURCES;
                        DEBUG ((EFI_D_ERROR, "Error: exceededs the maximum allowed GPT entries which is : %x\n", pGptSubDataPtr->MaxEntries));
                        goto GetActiveGPTDataFromGPTExit;
                    }

                    CopyMem(&(pGptSubDataPtr->ActiveGPTEntrySubData[pGptSubDataPtr->UsedEntries].PartitionTypeGUID), &pFwEntry->Metadata.UpdatePath.PartitionTypeGUID, sizeof (EFI_GUID));
                    CopyMem(pGptSubDataPtr->ActiveGPTEntrySubData[pGptSubDataPtr->UsedEntries].PartitionName, pFwEntry->Metadata.UpdatePath.PartitionName, StrSize(pFwEntry->Metadata.UpdatePath.PartitionName));

                    pGptSubDataPtr->ActiveGPTEntrySubData[pGptSubDataPtr->UsedEntries].TableIndex = partitionIndex;
                    pGptSubDataPtr->UsedEntries++;

                    break;
                }
                else if(CompareGuid(&(pStartPartitionEntry->PartitionTypeGUID), &(pFwEntry->Metadata.BackupPath.PartitionTypeGUID)) &&
                        CompareMem(pStartPartitionEntry->PartitionName, pFwEntry->Metadata.BackupPath.PartitionName, StrSize(pStartPartitionEntry->PartitionName)) == 0)
                {
                    if(partitionIndex > pGptSubDataPtr->MaxEntries)
                    {
                        status = EFI_OUT_OF_RESOURCES;
                        DEBUG ((EFI_D_ERROR, "Error: PartitionIndex exceededs the maximum allowed GPT entries.\n"));
                        goto GetActiveGPTDataFromGPTExit;
                    }

                    CopyMem(&(pGptSubDataPtr->ActiveGPTEntrySubData[pGptSubDataPtr->UsedEntries].PartitionTypeGUID), &pFwEntry->Metadata.BackupPath.PartitionTypeGUID, sizeof (EFI_GUID));
                    CopyMem(pGptSubDataPtr->ActiveGPTEntrySubData[pGptSubDataPtr->UsedEntries].PartitionName, pFwEntry->Metadata.BackupPath.PartitionName, StrSize(pFwEntry->Metadata.BackupPath.PartitionName));

                    pGptSubDataPtr->ActiveGPTEntrySubData[pGptSubDataPtr->UsedEntries].TableIndex = partitionIndex;
                    pGptSubDataPtr->UsedEntries++;

                    break;
                }
            }
            pCurrentNode = pCurrentNode->Next;
        }
        pStartPartitionEntry = (EFI_PARTITION_ENTRY *)((UINT8 *) pStartPartitionEntry + sizeOfPartitionEntry);
    }

GetActiveGPTDataFromGPTExit:

    /* Free the buffer allocated in ReadGPTTable function*/
    if (pPartitionEntry != NULL)
    {
        gBS->FreePool(pPartitionEntry);
        pPartitionEntry = NULL;
    }

    return status;
}

/**
 * This function will retrive active GPT data from GPT table
 * 
 * @param EFI_GUID              :  Vendor GUID whose GPT has to be changed
 * @param GPT_TABLE_TYPE        :  Primary or backup GPT table
 * @param ACTIVE_GPT_SUB_DATA   :  Pointer to hold active GPT data
 * @param PartitionEntry        :  Partition table entry 
 * @param GPTFileSize    :  Size of PartitionEntry 
 * 
 * gBS->FreePool will be used to free OUT buffer
 * 
 * @return EFI_STATUS 
 */

EFI_STATUS
GetGPTFromActiveGPTData (
    IN  EFI_GUID                      Memory_GUID,
    IN  GPT_TABLE_TYPE                TableType,
    IN  ACTIVE_GPT_SUB_DATA          *GPTSubDataPtr,
    OUT VOID                        **PartitionEntry,
    OUT UINTN                        *GPTFileSize,
    OUT OPTIONAL UINT32              *PartitionSize
)
{
    EFI_STATUS                    Status                 = EFI_SUCCESS;
    EFI_PARTITION_ENTRY          *StartPartitionEntry    = NULL;
    UINT32                        SizeOfPartitionEntry   = 0;
    UINT32                        NumberOfPartitions     = 0;
    UINT32                        PartitionIndex         = 0;
    UINTN                         GPTSize                = 0;
    UINTN                         i                      = 0;

    if(NULL == GPTSubDataPtr)
    {
        return EFI_INVALID_PARAMETER;
    }

    Status = ReadGPTTable(Memory_GUID,
                          (VOID*)&StartPartitionEntry, 
                          &GPTSize, 
                          &SizeOfPartitionEntry,
                          TableType);
    HANDLE_ERROR_LABEL(Status,ReadGPTTable (Memory_GUID),GetGPTFromActiveGPTDataExit);

    NumberOfPartitions = GPTSize / SizeOfPartitionEntry;

    if(NULL != PartitionSize)
    {
        *PartitionSize = SizeOfPartitionEntry;
    }

    *PartitionEntry = StartPartitionEntry;
    *GPTFileSize = GPTSize;

    /* Go through each partition entry
     for loop 1:
        go through each partition entry by jumping partition etnry size at a time
     for loop 2:
        go through the GPT backup sub data to see if the table index match with current patition index.
    */
    for(PartitionIndex = 0; PartitionIndex < NumberOfPartitions; PartitionIndex++) 
    {
        for(i = 0; i < GPTSubDataPtr->UsedEntries ; i++) 
        {
            if(PartitionIndex == GPTSubDataPtr->ActiveGPTEntrySubData[i].TableIndex)
            {
                StartPartitionEntry->PartitionTypeGUID = GPTSubDataPtr->ActiveGPTEntrySubData[i].PartitionTypeGUID;
                CopyMem(
                    StartPartitionEntry->PartitionName,
                    GPTSubDataPtr->ActiveGPTEntrySubData[i].PartitionName,
                    sizeof(GPTSubDataPtr->ActiveGPTEntrySubData[i].PartitionName)
                    );
                break;
            }
        }
        StartPartitionEntry = (EFI_PARTITION_ENTRY *)((UINT8 *)StartPartitionEntry + SizeOfPartitionEntry);
    }

GetGPTFromActiveGPTDataExit:

    return Status;
}

/**
 * This function will retrive active GPT data from GPT table
 * 
 * @param memoryGUID           :  Vendor GUID whose GPT has to be changed
 * @param pGptNvTypePtr        :  GPTNvType name
 * @param pDiskPartTypePtr     :  Type of disk partition to be filled
 * @param pMaxEntriesPtr       :  Max. partition entries in a storage disk
 *                                that needs backup
 * 
 * @return EFI_STATUS 
 */

EFI_STATUS
GetGptDataForDisk(
    IN EFI_GUID                                   memoryGUID,
    OUT OPTIONAL QCOM_FW_UPDATE_NV_TYPE          *pGptNvTypePtr,
    OUT OPTIONAL FWENTRY_DISK_PARTITION_TYPE     *pDiskPartTypePtr,
    OUT OPTIONAL UINT32                          *pMaxEntriesPtr
    )
{
    EFI_STATUS                  status              = EFI_SUCCESS;
    EFI_GUID                    emmcBootGuid        = gEfiEmmcBootPartition1Guid;
    EFI_GUID                    emmcGppGuid         = gEfiEmmcGppPartition1Guid;
    EFI_GUID                    ufsBootLun1Guid     = gEfiUfsLU1Guid;
    EFI_GUID                    ufsBootLun2Guid     = gEfiUfsLU2Guid;
    EFI_GUID                    ufsBootLun4Guid     = gEfiUfsLU4Guid;
    EFI_GUID                    spinor0Guid         = gEfiSpiNor0Guid;
    EFI_GUID                    spinor1Guid         = gEfiSpiNor1Guid;
    EFI_GUID                    nvmeGuid            = gEfiNvme0Guid;
    QCOM_FW_UPDATE_NV_TYPE      gptNvType           = QCOM_FW_UPDATE_NV_MAX;
    FWENTRY_DISK_PARTITION_TYPE diskPartType        = FWENTRY_DISK_PARTITION_MAX;
    UINT32                      maxEntries          = 0;

    // Return error if both Optional parameters are missing
    if ((NULL == pDiskPartTypePtr) && 
        (NULL == pGptNvTypePtr) &&
        (NULL == pMaxEntriesPtr))
    {
        status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    if (CompareGuid(&memoryGUID, &emmcBootGuid))
    {
        diskPartType = FWENTRY_EMMC_PARTITION_BOOT1;
        gptNvType = QCOM_FW_UPDATE_NV_GPT1;
        maxEntries = EMMC_BOOT_MAX_ENTRIES;
    }
    else if (CompareGuid(&memoryGUID, &emmcGppGuid))
    {
        diskPartType = FWENTRY_EMMC_PARTITION_GPP1;
        gptNvType = QCOM_FW_UPDATE_NV_GPT2;
        maxEntries = EMMC_GPP_MAX_ENTRIES;
    }
    else if (CompareGuid(&memoryGUID, &ufsBootLun1Guid))
    {
        diskPartType = FWENTRY_UFS_LUN1;
        gptNvType = QCOM_FW_UPDATE_NV_GPT1;
        maxEntries = UFS_BOOT_MAX_ENTRIES;
    }
    else if (CompareGuid(&memoryGUID, &ufsBootLun2Guid))
    {
        diskPartType = FWENTRY_UFS_LUN2;
        gptNvType = QCOM_FW_UPDATE_NV_GPT1;
        maxEntries = UFS_BOOT_MAX_ENTRIES;
    }
    else if (CompareGuid(&memoryGUID, &ufsBootLun4Guid))
    {
        diskPartType = FWENTRY_UFS_LUN4;
        gptNvType = QCOM_FW_UPDATE_NV_GPT2;
        maxEntries = UFS_GPP_MAX_ENTRIES;
    }
    else if (CompareGuid(&memoryGUID, &spinor0Guid))
    {
        diskPartType = FWENTRY_SPINOR;
        gptNvType = QCOM_FW_UPDATE_NV_GPT1;
        maxEntries = SPINOR_BOOT_MAX_ENTRIES;
    }
    else if (CompareGuid(&memoryGUID, &nvmeGuid))
    {
        diskPartType = FWENTRY_NVME;
        gptNvType = QCOM_FW_UPDATE_NV_GPT2;
        maxEntries = NVME_GPP_MAX_ENTRIES;
    }
    else if (CompareGuid(&memoryGUID, &spinor1Guid))
    {
        diskPartType = FWENTRY_SPINOR;
        gptNvType = QCOM_FW_UPDATE_NV_GPT3;
        maxEntries = (SPINOR_BOOT_MAX_ENTRIES/2);
    }
    else
    {
        status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    if(NULL != pDiskPartTypePtr)
    {
        *pDiskPartTypePtr = diskPartType;
    }

    if(NULL != pGptNvTypePtr)
    {
        *pGptNvTypePtr = gptNvType;
    }

    if(NULL != pMaxEntriesPtr)
    {
        *pMaxEntriesPtr = maxEntries;
    }

Exit:

    return status;
}

/**
 * This function will switch GUID with backup and vice
 * versa as requested by parsing the input firmware entry list, 
 * and write the Buffer into the specified GPT Table.
 * 
 * @param memoryGuid   : Vendor GUID whose GPT has to be changed
 * @param pList        : Firmware entry list 
 * 
 * @return EFI_STATUS 
 */

EFI_STATUS 
SwitchBackupGptTableEntries(
    IN  EFI_GUID               memoryGuid,
    IN  FW_LINKED_LIST_TYPE   *pList
    )
{
    EFI_STATUS                    status                  = EFI_SUCCESS;
    EFI_PARTITION_ENTRY          *pStartPartitionEntry    = NULL;
    EFI_PARTITION_ENTRY          *pPartitionEntry         = NULL;
    UINT32                        numberOfPartitions      = 0;
    UINT32                        partitionIndex          = 0;
    UINT32                        sizeOfPartitionEntry    = 0;
    EFI_BLOCK_IO_PROTOCOL        *hBlockIoHandleHardDrive = NULL;
    UINTN                         fileSize                = 0;
    FW_LIST_NODE_TYPE            *pCurrentNode            = NULL;
    QPAYLOAD_FW_ENTRY            *pFwEntry                = NULL;
    FWENTRY_DISK_PARTITION_TYPE   diskPartType            = FWENTRY_DISK_PARTITION_MAX;
    UINTN                         i                       = 0;
    QCOM_FW_UPDATE_NV_TYPE        gptNvType               = QCOM_FW_UPDATE_NV_MAX;
    ACTIVE_GPT_SUB_DATA          *pGptSubDataPtr          = NULL;
    UINT32                        gptSubDataSize          = 0;
    COMPRESSED_DATA              *pCompressedDataPtr      = NULL;
    UINTN                         compressedDataSize      = 0;
    GPT_TABLE_TYPE                tableType               = BACKUP_GPT_TABLE;

    /* Check input parameters, 
       1. It supports Boot and GPP EMMC type and LUN1, LUN2 and LUN4 UFS type
       2. List shouldn't be NULL
       3. if List-> Count == 0, return SUCCESS
       4. List -> Head == NULL is not allowed
       5. when Memory Guid points to LUN1 or LUN2, return SUCCESS
     */

    /* Check 1 */
    status = GetGptDataForDisk(
        memoryGuid,
        &gptNvType,
        &diskPartType,
        NULL
        );
    HANDLE_ERROR_LABEL(status,GetGptDataForDisk,Exit);

    if ((diskPartType == FWENTRY_UFS_LUN1) ||
        (diskPartType == FWENTRY_UFS_LUN2))
    {
        //Check 5
        DEBUG((EFI_D_WARN,"\n    Skipping backup of GPT table for LUN1/LUN2\n"));
        goto Exit;
    }

    /* Check 2 */
    if (pList == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    /* Check 3 */
    if (pList->Count == 0)  
    {
        return EFI_SUCCESS;
    }

    /* Check 4 */
    if (pList->Head == NULL)
    {
        return EFI_INVALID_PARAMETER;
    }

    // Locate Disk type BlockIO handler
    status = GetDiskTypeHandle(memoryGuid, &hBlockIoHandleHardDrive);
    HANDLE_ERROR_LABEL(status,GetDiskTypeHandle,Exit);

    if ( hBlockIoHandleHardDrive != NULL)
    {
        // Read partition entries from backup
        status = GetGPTNvData(gptNvType, (VOID **)&pCompressedDataPtr, &compressedDataSize);
        HANDLE_ERROR_LABEL(status,GetGPTNvData,Exit);

        gptSubDataSize = pCompressedDataPtr->UncompressedSize;
        pGptSubDataPtr = AllocateZeroPool (gptSubDataSize);
        status = (NULL == pGptSubDataPtr) ? EFI_OUT_OF_RESOURCES : EFI_SUCCESS;
        HANDLE_ERROR_LABEL(status, AllocateZeroPool (pGptSubDataPtr), Exit);

        status = DecompressGPT(
            pCompressedDataPtr->Data,
            (pCompressedDataPtr->Size - OFFSET_OF(COMPRESSED_DATA, Data)),
            pGptSubDataPtr,
            &gptSubDataSize);
        HANDLE_ERROR_LABEL(status,DecompressGPT,Exit);

        // Derive the original GPT table using GPT sub data
        status = GetGPTFromActiveGPTData (
            memoryGuid,
            tableType,
            pGptSubDataPtr,
            (VOID*)&pPartitionEntry,
            &fileSize,
            &sizeOfPartitionEntry
            );
        HANDLE_ERROR_LABEL(status,GetGPTFromActiveGPTData,Exit);

        pStartPartitionEntry = pPartitionEntry;

        numberOfPartitions = fileSize / sizeOfPartitionEntry;

        /* Go through each partition entry
         for loop 1:
            go through each partition entry by jumping partition etnry size at a time
         for loop 2:
            go through the partition entry info in the List to see if any match.
        */
        for(partitionIndex = 0; partitionIndex < numberOfPartitions; partitionIndex++) 
        {
            pCurrentNode = pList->Head;
            for( i = 0; i < pList->Count; i++) 
            {
                pFwEntry = (QPAYLOAD_FW_ENTRY*)(pCurrentNode->Data);
                if(pFwEntry->Metadata.UpdateType == FWENTRY_UPDATE_TYPE_PARTITION &&
                   pFwEntry->Metadata.BackupType == FWENTRY_UPDATE_TYPE_PARTITION &&
                   pFwEntry->Metadata.UpdatePath.DiskPartitionType == diskPartType &&
                   pFwEntry->Metadata.BackupPath.DiskPartitionType == diskPartType)
                {
                    if(CompareGuid(&(pStartPartitionEntry->PartitionTypeGUID), &(pFwEntry->Metadata.UpdatePath.PartitionTypeGUID)) &&
                       CompareMem(pStartPartitionEntry->PartitionName, pFwEntry->Metadata.UpdatePath.PartitionName, StrSize(pStartPartitionEntry->PartitionName)) == 0)
                    {
                        pStartPartitionEntry->PartitionTypeGUID = pFwEntry->Metadata.BackupPath.PartitionTypeGUID;
                        CopyMem(pStartPartitionEntry->PartitionName, pFwEntry->Metadata.BackupPath.PartitionName, sizeof(pStartPartitionEntry->PartitionName));
                        break;
                    }
                    else if(CompareGuid(&(pStartPartitionEntry->PartitionTypeGUID), &(pFwEntry->Metadata.BackupPath.PartitionTypeGUID)) &&
                            CompareMem(pStartPartitionEntry->PartitionName, pFwEntry->Metadata.BackupPath.PartitionName, StrSize(pStartPartitionEntry->PartitionName)) == 0)
                    {
                        pStartPartitionEntry->PartitionTypeGUID = pFwEntry->Metadata.UpdatePath.PartitionTypeGUID;
                        CopyMem(pStartPartitionEntry->PartitionName, pFwEntry->Metadata.UpdatePath.PartitionName, sizeof(pStartPartitionEntry->PartitionName));
                        break;
                    }
                }
                pCurrentNode = pCurrentNode->Next;
            }

            pStartPartitionEntry = (EFI_PARTITION_ENTRY *)((UINT8 *) pStartPartitionEntry + sizeOfPartitionEntry);
        }

        status = WriteGPTTableEntries(
            (VOID *)pPartitionEntry,
            fileSize,
            memoryGuid,
            tableType);
        HANDLE_ERROR_LABEL(status, WriteGPTTableEntries,Exit);
    }
    else
    {
        status = EFI_NOT_FOUND;
        HANDLE_ERROR_LABEL(status,GetDiskTypeHandle,Exit);
    }

Exit:

    //Free all the Allocated Memory
    if(pPartitionEntry != NULL) 
    {
        gBS->FreePool(pPartitionEntry);
        pPartitionEntry = NULL;
    }

    if (NULL != pGptSubDataPtr)
    {
        FreePool (pGptSubDataPtr);
        pGptSubDataPtr = NULL;
    }

    if (NULL != pCompressedDataPtr)
    {
        FreePool (pCompressedDataPtr);
        pCompressedDataPtr = NULL;
    }

    return status;
}

/**
 * Restores Boot Partition and GPP partition tables from NV Data.
 * Also modifies and fills in the right CRC 
 * 
 * @param tableType        :  Primary or backup GPT table
 * 
 * @return EFI_STATUS 
 */

EFI_STATUS 
RestoreAllGPTTablesFromNV(
    IN GPT_TABLE_TYPE tableType
    )
{

    EFI_STATUS              status               = EFI_SUCCESS;
    UINTN                   gptFileSize          = 0;
    VOID                   *pPartitionEntry      = NULL;
    ACTIVE_GPT_SUB_DATA    *pgptSubDataPtr       = NULL;
    UINT32                  gptSubDataSize       = 0;
    COMPRESSED_DATA        *pCompressedDataPtr   = NULL;
    UINTN                   compressedDataSize   = 0;
    UINT8                   diskIdx              = 0;
    PSTORAGE_DISK_LIST      pDiskList            = NULL;
    PSTORAGE_DISK_INFO      pDiskInfo            = NULL;

    status = GetStorageDiskList(&pDiskList);
    HANDLE_ERROR_LABEL(status, GetStorageDiskList, Exit);

    for (diskIdx = 0; diskIdx < pDiskList->count; diskIdx++)
    {
        pDiskInfo = &pDiskList->storageInfo[diskIdx];
        if (NULL == pDiskInfo)
        {
            status = EFI_NOT_FOUND;
            DEBUG_ERR_LABEL (
                "RestoreAllGPTTablesFromNV: pDiskInfo is NULL\n",
                Exit);;
        }

        /* Check if it is required to restore GPT for a storage disk.
           On UFS, boot GPT need not be restored as LUN switching is done.
        */
        if (pDiskInfo->switchGPT)
        {
            DEBUG((EFI_D_INFO, "Restore GPT for Disk guid: %g.\n", &pDiskInfo->guid));

            status = GetGPTNvData(pDiskInfo->nvType, (VOID **)&pCompressedDataPtr, &compressedDataSize);
            HANDLE_ERROR_LABEL(status,GetGPTNvData,Exit);

            gptSubDataSize = pCompressedDataPtr->UncompressedSize;
            pgptSubDataPtr = AllocateZeroPool (gptSubDataSize);
            status = (NULL == pgptSubDataPtr) ? EFI_OUT_OF_RESOURCES : EFI_SUCCESS;
            HANDLE_ERROR_LABEL(status, AllocateZeroPool (pgptSubDataPtr),Exit);

            status = DecompressGPT(
                pCompressedDataPtr->Data,
                (pCompressedDataPtr->Size - OFFSET_OF(COMPRESSED_DATA, Data)),
                pgptSubDataPtr,
                &gptSubDataSize);
            HANDLE_ERROR_LABEL(status,DecompressGPT,Exit);

            // Derive the original GPT table using GPT sub data
            status = GetGPTFromActiveGPTData (
                pDiskInfo->guid,
                tableType,
                pgptSubDataPtr,
                &pPartitionEntry,
                &gptFileSize,
                NULL
                );
            HANDLE_ERROR_LABEL(status,GetGPTFromActiveGPTData,Exit);

            status = WriteGPTTableEntries(
                pPartitionEntry,
                gptFileSize,
                pDiskInfo->guid,
                tableType);
            HANDLE_ERROR_LABEL(status,WriteGPTTableEntries,Exit);

            FreePool (pCompressedDataPtr);
            pCompressedDataPtr = NULL;
        }
    }

    status = WriteAllGPTTableCRCs(tableType);
    HANDLE_ERROR_LABEL(status,WriteAllGPTTableCRCs,Exit);

Exit:

    if(pPartitionEntry != NULL)
    {
        gBS->FreePool(pPartitionEntry);
        pPartitionEntry = NULL;
    }

    if (pgptSubDataPtr != NULL)
    {
        FreePool(pgptSubDataPtr);
        pgptSubDataPtr = NULL;
    }

    if (NULL != pCompressedDataPtr)
    {
        FreePool (pCompressedDataPtr);
        pCompressedDataPtr = NULL;
    }

    return status;
}

/**
 * Modifies gpt partition tables (BOOT partition and GPP) based 
 * on firmware entries in payload. 
 *
 * @param None
 *
 * @return EFI_STATUS
 *
 */
EFI_STATUS 
ModifyAllBackupGptTablesForFailSafeUpdate(VOID)
{
    EFI_STATUS                    status                 = EFI_SUCCESS;
    UINT8                         diskIdx                = 0;
    PSTORAGE_DISK_LIST            pDiskList              = NULL;
    PSTORAGE_DISK_INFO            pDiskInfo              = NULL;
    FW_LINKED_LIST_TYPE          *pList                  = NULL;
    GPT_TABLE_TYPE                tableType              = BACKUP_GPT_TABLE;
    BOOLEAN                       isGptSwitchPending     = FALSE;

    status = FwGetFwEntryList(&pList);
    HANDLE_ERROR_LABEL(status, FwGetFwEntryList, Exit);

    status = GetStorageDiskList(&pDiskList);
    HANDLE_ERROR_LABEL(status, GetStorageDiskList, Exit);

    for (diskIdx = 0; diskIdx < pDiskList->count; diskIdx++)
    {
        pDiskInfo = &pDiskList->storageInfo[diskIdx];
        if (NULL == pDiskInfo)
        {
            status = EFI_NOT_FOUND;
            DEBUG_ERR_LABEL (
                "ModifyAllBackupGptTablesForFailSafeUpdate: pDiskInfo is NULL\n",
                Exit);;
        }

        if (pDiskInfo->switchGPT)
        {
            status = CmpGPTTable(
                tableType,
                pDiskInfo->guid,
                pDiskInfo->nvType,
                &pDiskInfo->gptState);
            HANDLE_ERROR_LABEL(status, CmpGPTTable, Exit);

            DEBUG((
                EFI_D_WARN, 
                "Diskguid: %g GptState: %d\n", 
                &pDiskInfo->guid, pDiskInfo->gptState));

            if (ORIGINAL_TABLE == pDiskInfo->gptState)
            {
                isGptSwitchPending = TRUE;

                // Switch backup GPT table entries for storage disks
                status = SwitchBackupGptTableEntries(pDiskInfo->guid, pList);
                HANDLE_ERROR_LABEL(status, SwitchBackupGptTableEntries, Exit);
            }
        }
    }

    // Adding this check to handle the case when GPT is already switched and
    // we re-entered this API call due to abnormal reset in the middle of update.
    if (isGptSwitchPending)
    {
        status = WriteAllGPTTableCRCs(tableType);
        HANDLE_ERROR_LABEL(status, WriteAllGPTTableCRCs, Exit);
    }

Exit:

    return status;
}

/**
 * Invalidates GPT Tables across all storage disks based on table type and 
 * determing if FMP payload include partition updates to a disk.
 *
 * @param tableType   :  Primary or backup GPT table
 *
 * @return EFI_STATUS
 *
 */
EFI_STATUS 
InvalidateAllGPT(
    IN GPT_TABLE_TYPE  tableType
)
{
    EFI_STATUS           status           = EFI_SUCCESS;
    UINT8                diskIdx          = 0;
    PSTORAGE_DISK_LIST   pDiskList        = NULL;
    PSTORAGE_DISK_INFO   pDiskInfo        = NULL;

    status = GetStorageDiskList(&pDiskList);
    HANDLE_ERROR_LABEL(status, GetStorageDiskList, Exit);

    for (diskIdx = 0; diskIdx < pDiskList->count; diskIdx++)
    {
        pDiskInfo = &pDiskList->storageInfo[diskIdx];
        if (NULL == pDiskInfo)
        {
            status = EFI_NOT_FOUND;
            DEBUG_ERR_LABEL("InvalidateAllGPT: pDiskInfo is NULL\n", Exit);
        }

        if (pDiskInfo->switchGPT)
        {
            status = InvalidateGPT(
                pDiskInfo->guid,
                tableType);
            HANDLE_ERROR_LABEL(status, InvalidateGPT, Exit);
        }
    }

    status = WriteAllGPTTableCRCs(tableType);
    HANDLE_ERROR_LABEL(status,WriteAllGPTTableCRCs,Exit);

Exit:

    return status;
}

/**
 * This function will invalidate the CRC for the given 
 * table type (Primary/Backup GPT) and cache the updated header and 
 * table type in pDiskInfo structure. This function should 
 * be followed by call to WriteAllGPTTableCRCs() to rewrite the CRC 
 * across all disks with modified GPT.
 *
 * @param memoryGuid         : Vendor GUID whose GPT has to be changed
 * @param tableType          : Primary or backup GPT table
 *
 * @return EFI_STATUS
 *
 */

EFI_STATUS 
InvalidateGPT(
    IN EFI_GUID        memoryGuid,
    IN GPT_TABLE_TYPE  tableType
    )
{
    EFI_STATUS                  status                 = EFI_SUCCESS;
    EFI_BLOCK_IO_PROTOCOL      *hBlockIoHandleHardDrive = NULL;
    EFI_PARTITION_TABLE_HEADER *pPartHdr                = NULL;
    EFI_PARTITION_TABLE_HEADER *pBackupPartHdr          = NULL;
    EFI_PARTITION_TABLE_HEADER *pOutPartitionHeader     = NULL;
    PSTORAGE_DISK_INFO          pDiskInfo              = NULL;

    status = GetStorageDiskInfoFromDiskGuid(memoryGuid, &pDiskInfo);
    HANDLE_ERROR_LABEL(status, GetStorageDiskInfoFromDiskGuid, Exit);

    status = GetDiskTypeHandle(memoryGuid,&hBlockIoHandleHardDrive);
    HANDLE_ERROR_LABEL(status,GetDiskTypeHandle,Exit);

    if (hBlockIoHandleHardDrive != NULL)
    {
        status = gBS->AllocatePool(
            EfiBootServicesData,
            hBlockIoHandleHardDrive->Media->BlockSize,
            (VOID*)&pPartHdr);
        HANDLE_ERROR_LABEL(status,gBS->AllocatePool,Exit);
        gBS->SetMem(pPartHdr, hBlockIoHandleHardDrive->Media->BlockSize, 0 );

        status =  hBlockIoHandleHardDrive->ReadBlocks(
            hBlockIoHandleHardDrive,
            hBlockIoHandleHardDrive->Media->MediaId,
            PRIMARY_HEADER_LBA,
            hBlockIoHandleHardDrive->Media->BlockSize,
            pPartHdr);
        HANDLE_ERROR_LABEL(status,hBlockIoHandleHardDrive->ReadBlocks,Exit);

        if(tableType == BACKUP_GPT_TABLE)
        {
            status = gBS->AllocatePool(
                EfiBootServicesData,
                hBlockIoHandleHardDrive->Media->BlockSize,
                (VOID*)&pBackupPartHdr);
            HANDLE_ERROR_LABEL(status,gBS->AllocatePool,Exit);
            gBS->SetMem(pBackupPartHdr, hBlockIoHandleHardDrive->Media->BlockSize, 0 );

            status =  hBlockIoHandleHardDrive->ReadBlocks(
                hBlockIoHandleHardDrive,
                hBlockIoHandleHardDrive->Media->MediaId,
                pPartHdr->AlternateLBA,
                hBlockIoHandleHardDrive->Media->BlockSize,
                pBackupPartHdr);
            HANDLE_ERROR_LABEL(status,hBlockIoHandleHardDrive->ReadBlocks,Exit);

             /* Invalidate the backup GPT by modify the CRC */
            pBackupPartHdr->Header.CRC32 = 0;
            pOutPartitionHeader = pBackupPartHdr;

            gBS->FreePool(pPartHdr);
            pPartHdr = NULL;
        }
        else
        {
            /* Invalidate the primary GPT by modify the CRC */
            pPartHdr->Header.CRC32 = 0;
            pOutPartitionHeader = pPartHdr;
        }

        // At this point, all previous calls would have succeeded 
        // So, updating pDiskInfo structure with updated header and tabletype.
        pDiskInfo->pOutPartitionHeader = pOutPartitionHeader;
        pDiskInfo->partHdrTableType = tableType;
    }
    else
    {
        status = EFI_NOT_FOUND;
        HANDLE_ERROR_LABEL(status,GetDiskTypeHandle,Exit);
    }

Exit:

    if(EFI_ERROR(status))
    {
        if (pPartHdr != NULL)
        {
           gBS->FreePool(pPartHdr);
           pPartHdr = NULL;
        }

        if (pBackupPartHdr != NULL)
        {
           gBS->FreePool(pBackupPartHdr);
           pBackupPartHdr = NULL;
        }
    }

    return status;
 }

/**
 * Reads the partition table and returns Filesize and FileBuffer
 * with data from the GPT tables. In case FileBuffer is NULL
 * will return only the FileSize by reading the GPT header
 *
 * @param Memory_GUID     : Vendor GUID for which GPT tables
 *                          have to be read
 * @param FileBuffer      : Pointer to buffer where GPT should
 *                          be read. If NULL, Function will
 *                          return only the FileSize
 * @param FileSize        : Size of the buffer to be read, i.e
 *                          size of the partition table
 * @param SizeOfPartitionEntry : Size of one partition entry in
 *                          the partition table
 * @param TableType
 * 
 *
 * @return EFI_STATUS
 *
 */

EFI_STATUS 
ReadGPTTable(
    IN  EFI_GUID         Memory_GUID,
    OUT OPTIONAL VOID  **FileBuffer,
    OUT UINTN           *FileSize,
    OUT OPTIONAL UINT32 *SizeOfPartitionEntry,
    IN  GPT_TABLE_TYPE   TableType
    )
{
    EFI_STATUS                  Status                 = EFI_SUCCESS;
    EFI_BLOCK_IO_PROTOCOL      *BlockIoHandleHardDrive = NULL;
    EFI_PARTITION_TABLE_HEADER *PartHdr                = NULL;
    EFI_PARTITION_ENTRY        *PartitionEntry         = NULL;
    UINT8                       *BlocksReadBuffer      = NULL;
    UINT8                       *BlocksReadBufferTemp  = NULL;
    UINT32                      BlocksToRead           = 0;
    UINT32                      BlocksToReadRemainder    = 0;
    UINT32                      i                      = 0;
    /*Logical Block Address */
    UINT32                      StartLBA               = 0;  

    /* NULL FileBuffer is allowed */
    if(FileSize == NULL) 
    {
        return EFI_INVALID_PARAMETER;
    }
    
    /* Initialize the out put buffer pointer and size */
    *FileSize = 0;

    /* Get the handle of given Disk type Memory GUID */
    Status = GetDiskTypeHandle(Memory_GUID , &BlockIoHandleHardDrive);
    HANDLE_ERROR_LABEL(Status,GetDiskTypeHandle,ReadGPTTableExit);

    if (BlockIoHandleHardDrive != NULL)
    {
        Status = gBS->AllocatePool(EfiBootServicesData , BlockIoHandleHardDrive->Media->BlockSize,(VOID*)&PartHdr );
        HANDLE_ERROR_LABEL(Status, gBS->AllocatePool, ReadGPTTableExit);
        gBS->SetMem(PartHdr, BlockIoHandleHardDrive->Media->BlockSize, 0 ); 
      
        /* Read the Disk partition Header */
        Status =  BlockIoHandleHardDrive->ReadBlocks ( BlockIoHandleHardDrive,
                                                       BlockIoHandleHardDrive->Media->MediaId,
                                                       PRIMARY_HEADER_LBA,
                                                       BlockIoHandleHardDrive->Media->BlockSize,
                                                       PartHdr
                                                       );    
        HANDLE_ERROR_LABEL(Status, BlockIoHandleHardDrive->ReadBlocks, ReadGPTTableExit);
      
        /* Get the Partition Table Size */
        *FileSize = (PartHdr->NumberOfPartitionEntries) * (PartHdr->SizeOfPartitionEntry);
      
        if (NULL != SizeOfPartitionEntry)
        {
            *SizeOfPartitionEntry = PartHdr->SizeOfPartitionEntry;
        }

        /* Return if FileSize is the only requestd data*/
        if (FileBuffer == NULL)
        {
            return EFI_SUCCESS;
        }
      
        /* Get the total number of blocks to be read */
        BlocksToRead = (PartHdr->NumberOfPartitionEntries * PartHdr->SizeOfPartitionEntry) / BlockIoHandleHardDrive->Media->BlockSize;
        BlocksToReadRemainder  = (PartHdr->NumberOfPartitionEntries * PartHdr->SizeOfPartitionEntry) % BlockIoHandleHardDrive->Media->BlockSize;
        BlocksToRead += (BlocksToReadRemainder == 0) ? 0 : 1;
      
        /* Allocate and zero out a buffer to store the blocks read from disk */
        Status = gBS->AllocatePool(EfiBootServicesData,
                                   BlocksToRead * BlockIoHandleHardDrive->Media->BlockSize,
                                   (VOID*)&BlocksReadBuffer);
        HANDLE_ERROR_LABEL(Status, gBS->AllocatePool, ReadGPTTableExit);
        gBS->SetMem(BlocksReadBuffer, BlocksToRead * BlockIoHandleHardDrive->Media->BlockSize, 0);
      
        /* Allocate and zero out a buffer to store the partition table */
        Status = gBS->AllocatePool(EfiBootServicesData, 
                                   (PartHdr->NumberOfPartitionEntries * PartHdr->SizeOfPartitionEntry),
                                   (VOID*)&PartitionEntry);
        HANDLE_ERROR_LABEL(Status, gBS->AllocatePool, ReadGPTTableExit);
        gBS->SetMem(PartitionEntry , (PartHdr->NumberOfPartitionEntries * PartHdr->SizeOfPartitionEntry), 0 );
      
        /* The output buffer points to the first partition entry */
        *FileBuffer = (VOID*)PartitionEntry;
      
        /* Depends on reading primary or back up GPT, Assign the correct startLBA 
           by given TableType 
        */
        if(TableType == PRIMARY_GPT_TABLE) 
        {
            StartLBA = PartHdr->MyLBA + 1;
        }
        else
        {
            StartLBA = PartHdr->LastUsableLBA + 1;
        }
      
        BlocksReadBufferTemp = BlocksReadBuffer;
      
        // Start reading all the partitions one block at a time
        for (i = StartLBA; i < (StartLBA + BlocksToRead); i++)
        {
            Status = BlockIoHandleHardDrive->ReadBlocks ( BlockIoHandleHardDrive,
                                                          BlockIoHandleHardDrive->Media->MediaId,
                                                          i,
                                                          BlockIoHandleHardDrive->Media->BlockSize,
                                                          BlocksReadBufferTemp);
            HANDLE_ERROR_LABEL(Status, BlockIoHandleHardDrive->ReadBlocks, ReadGPTTableExit);
      
            BlocksReadBufferTemp += BlockIoHandleHardDrive->Media->BlockSize;
        }
      
        gBS->CopyMem(PartitionEntry, BlocksReadBuffer, (PartHdr->NumberOfPartitionEntries) * (PartHdr->SizeOfPartitionEntry));

        if (BlocksReadBuffer != NULL)
        {
            gBS->FreePool(BlocksReadBuffer);
            BlocksReadBuffer = NULL;
        }
      
        gBS->FreePool(PartHdr);
        PartHdr = NULL;
      
        return EFI_SUCCESS;
    }
    else
    {
        Status = EFI_NOT_FOUND;
        HANDLE_ERROR_LABEL(Status,GetDiskTypeHandle,ReadGPTTableExit);
    }

ReadGPTTableExit:

    if (PartHdr != NULL)
    {
        gBS->FreePool(PartHdr);
        PartHdr = NULL;
    }
    if(FileBuffer != NULL)
    {
      if (*FileBuffer != NULL)
      {
          gBS->FreePool(*FileBuffer);
          *FileBuffer = NULL;
      }
    }
    if (BlocksReadBuffer != NULL)
    {
        gBS->FreePool(BlocksReadBuffer);
        BlocksReadBuffer = NULL;
    }
    return Status;
}

/**
 * Copy Partition Tables (LUN4/SPINOR/NVME/EMMC) to FAT16.bin in files BPx.TBL GPP.TBL
 *
 * @param None
 *
 * @return EFI _STATUS
 *
 */

EFI_STATUS 
BackupAllGPTTable(VOID)
{

    EFI_STATUS            status                = EFI_SUCCESS;
    FW_LINKED_LIST_TYPE  *pList                 = NULL;
    ACTIVE_GPT_SUB_DATA  *pGptSubData           = NULL;
    ACTIVE_GPT_SUB_DATA **pTempGptSubData       = NULL;
    VOID                 *pCompressedGptData    = NULL;
    UINT32                compressedGptDataSize = 0;
    COMPRESSED_DATA      *pCompressedData       = NULL;
    UINT8                 diskIdx               = 0;
    PSTORAGE_DISK_LIST    pDiskList             = NULL;
    PSTORAGE_DISK_INFO    pDiskInfo             = NULL;

    status = FwGetFwEntryList(&pList);
    HANDLE_ERROR_LABEL(status, FwGetFwEntryList, BackupGPTTableExit);

    status = GetStorageDiskList(&pDiskList);
    HANDLE_ERROR_LABEL(status, GetStorageDiskList, BackupGPTTableExit);

    for (diskIdx = 0; diskIdx < pDiskList->count; diskIdx++)
    {
        pDiskInfo = &pDiskList->storageInfo[diskIdx];
        if (NULL == pDiskInfo)
        {
            status = EFI_NOT_FOUND;
            DEBUG_ERR_LABEL (
                "BackupAllGPTTable: pDiskInfo is NULL\n",
                BackupGPTTableExit);;
        }

        /* Check if it is required to back up GPT of storage disks. 
           On UFS, boot partition backup is not needed.
        */
        if (pDiskInfo->switchGPT)
        {
            DEBUG((EFI_D_INFO, "Backup GPT for Disk guid: %g.\n", &pDiskInfo->guid));
            pTempGptSubData = &pGptSubData;

            status = AllocateAndInitGPTSubData(pDiskInfo->nvDataMaxEntries, pTempGptSubData);
            HANDLE_ERROR_LABEL(status, AllocateAndInitGPTBackupData, BackupGPTTableExit);

            if (NULL != pGptSubData)
            {
                status = GetActiveGPTDataFromGPT (
                    pDiskInfo->guid,
                    PRIMARY_GPT_TABLE,
                    pList,
                    pGptSubData);
                HANDLE_ERROR_LABEL(status, GetActiveGPTDataFromGPT (pDiskInfo->guid), BackupGPTTableExit);

                compressedGptDataSize = pGptSubData->Size;
                /* Giving double size to make sure we dont run short of memory.
                   For very small buffers that have really compact data, there
                   is a chance that compressed data is larger than the uncompressed
                   data. Such case should not fail compression */
                pCompressedGptData = AllocateZeroPool (compressedGptDataSize * 2); 

                status = CompressGPT(
                    pGptSubData,
                    pGptSubData->Size,
                    pCompressedGptData,
                    &compressedGptDataSize);
                HANDLE_ERROR_LABEL(status, CompressGPT, BackupGPTTableExit);

                status = AllocateAndInitCompressedData(
                    pGptSubData->Size,
                    pCompressedGptData,
                    compressedGptDataSize,
                    &pCompressedData);
                HANDLE_ERROR_LABEL(status, AllocateAndInitCompressedData(pDiskInfo->guid), BackupGPTTableExit);

                /* Safely backup GPT table to a NV variable */
                status = SetGPTNvData(pDiskInfo->nvType, pCompressedData, pCompressedData->Size);
                HANDLE_ERROR_LABEL(status, SetGPTNvData (pDiskInfo->nvType),BackupGPTTableExit);

                FreePool(pCompressedGptData);
                pCompressedGptData = NULL;

                FreePool(pGptSubData);
                pGptSubData = NULL;
            }
        }
   }

BackupGPTTableExit:

    if (NULL != pGptSubData)
    {
        FreePool(pGptSubData);
        pGptSubData = NULL;
    }

    if (NULL != pCompressedGptData)
    {
        FreePool(pCompressedGptData);
        pCompressedGptData = NULL;
    }

    return status;
}

/**
 * Compare GPT with the table in FAT partition and check if it the swapped table 
 * or it is the primary original table 
 *
 * @param tableType        :   Type of GPT Table
 * @param diskTypeGuid     :   Vendor GUID whose GPT has to be 
 *                             compared
 * @param gptNvType        :   Type of NV Data
 * @param pGptTableState   :   returns if GPT table is in the
 *                             original or switched state
 *
 * @return EFI_STATUS
 *
 */
EFI_STATUS 
CmpGPTTable(
    IN  GPT_TABLE_TYPE          tableType,
    IN  EFI_GUID                diskTypeGuid,
    IN  QCOM_FW_UPDATE_NV_TYPE  gptNvType,
    OUT GPT_TABLE_STATE        *pGptTableState
    )
{
    EFI_STATUS             status                 = EFI_SUCCESS;
    VOID                  *pGptFromNv             = NULL;
    VOID                  *pGptData               = NULL;
    UINTN                  gptFromNVSize          = 0;
    UINTN                  gptDataSize            = 0;
    EFI_PARTITION_ENTRY   *pPartitionEntryFromGpt = NULL;
    EFI_PARTITION_ENTRY   *pPartitionEntryFromFat = NULL;
    COMPRESSED_DATA       *pCompressedDataPtr     = NULL;
    UINTN                  compressedDataSize     = 0;
    UINT32                 gptSubDataSize         = 0;
    ACTIVE_GPT_SUB_DATA   *pGptSubDataPtr         = NULL;

    status = ReadGPTTable(diskTypeGuid, &pGptData, &gptDataSize, NULL, tableType);
    HANDLE_ERROR_LABEL(status,ReadGPTTable,CmpGPTTableExit);

    status = GetGPTNvData(gptNvType, (VOID **)&pCompressedDataPtr, &compressedDataSize);
    HANDLE_ERROR_LABEL(status,GetGPTNvData,CmpGPTTableExit);

    gptSubDataSize = pCompressedDataPtr->UncompressedSize;
    pGptSubDataPtr = AllocateZeroPool (gptSubDataSize);
    status = (NULL == pGptSubDataPtr) ? EFI_OUT_OF_RESOURCES : EFI_SUCCESS;
    HANDLE_ERROR_LABEL(status, AllocateZeroPool (pGptSubDataPtr),  CmpGPTTableExit);
    
    status = DecompressGPT(
        pCompressedDataPtr->Data,
        (pCompressedDataPtr->Size - OFFSET_OF(COMPRESSED_DATA, Data)),
        pGptSubDataPtr,
        &gptSubDataSize);
    HANDLE_ERROR_LABEL(status,DecompressGPT,CmpGPTTableExit);

    // Derive the original GPT table using GPT sub data
    status = GetGPTFromActiveGPTData (
        diskTypeGuid,
        tableType,
        pGptSubDataPtr,
        &pGptFromNv,
        &gptFromNVSize,
        NULL
        );
    HANDLE_ERROR_LABEL(status,GetGPTFromActiveGPTData,CmpGPTTableExit);

    pPartitionEntryFromGpt = (EFI_PARTITION_ENTRY *)pGptData;
    pPartitionEntryFromFat = (EFI_PARTITION_ENTRY *)pGptFromNv;

    if(CompareMem((VOID*)pPartitionEntryFromGpt, (VOID*)pPartitionEntryFromFat, gptDataSize) == 0)
    {
        *pGptTableState = ORIGINAL_TABLE;
    }
    else 
    {
        *pGptTableState = SWITCHED_TABLE;
    }
    status = EFI_SUCCESS;

CmpGPTTableExit:

    if(pGptData != NULL)
    {
        gBS->FreePool(pGptData);
        pGptData = NULL;
    }

    if(pGptFromNv != NULL)
    {
        gBS->FreePool(pGptFromNv);
        pGptFromNv = NULL;
    }

    if (NULL != pGptSubDataPtr)
    {
        FreePool (pGptSubDataPtr);
        pGptSubDataPtr = NULL;
    }

    if (NULL != pCompressedDataPtr)
    {
        FreePool (pCompressedDataPtr);
        pCompressedDataPtr = NULL;
    }

    return status;
}

/**
 * Function to allocate memory for GPT sub data with for the given length
 *
 * Use FreePool() to free the memory allocated by this function
 *
 * @param MaxEntries    :  Max entries allowed in the GPT array
 * @param GPTSubData    :  GPT sub data allocated and initialized
 *                         GPT needs to be switched
 * 
 * @return EFI_STATUS
 */
EFI_STATUS
AllocateAndInitGPTSubData(
    IN UINT32                  MaxEntries,
    OUT ACTIVE_GPT_SUB_DATA  **GPTSubData
)
{
  EFI_STATUS            Status = EFI_SUCCESS;
  UINT32                GPTSubDataSize = 0;

  if ((NULL == GPTSubData) ||
      (0 == MaxEntries))
  {
    return EFI_INVALID_PARAMETER;
  }

  GPTSubDataSize = 
      sizeof (ACTIVE_GPT_SUB_DATA) + 
      (sizeof (ACTIVE_GPT_ENTRY_SUB_DATA) * (MaxEntries - 1));
  
  *GPTSubData = AllocateZeroPool (GPTSubDataSize);
  
  Status = (NULL == *GPTSubData) ? EFI_OUT_OF_RESOURCES : EFI_SUCCESS;
  HANDLE_ERROR_LABEL(Status, AllocateZeroPool (GPTSubDataSize),  AllocateAndInitGPTSubDataExit);

  (*GPTSubData)->MaxEntries = MaxEntries;
  (*GPTSubData)->Size = GPTSubDataSize;

  return EFI_SUCCESS;

 AllocateAndInitGPTSubDataExit:

  if (*GPTSubData != NULL)
  {
    FreePool(*GPTSubData);
    *GPTSubData = NULL;
  }

  return Status;
}

/**
 * Function to allocate memory for GPT sub data with for the given length
 *
 * @param UncompressedSize:  Data size before compression happens
 * @param InputData       :  Optional parameter. If supplied, needs
 *                           to be copied to the COMPRESSED_DATA->Data
 * @param InputDataSize   :  Compressed data size
 * @param CompressedData  :  To hold compressed data
 * 
 * @return EFI_STATUS
 */
EFI_STATUS
AllocateAndInitCompressedData(
    IN UINT32                  UncompressedSize,
    IN OPTIONAL VOID          *InputData,
    IN UINT32                  InputDataSize,
    OUT COMPRESSED_DATA      **CompressedData
)
{
  EFI_STATUS            Status = EFI_SUCCESS;
  UINT32                CompressedDataSize = 0;

  if ((NULL == CompressedData) ||
      (0 == UncompressedSize))
  {
    return EFI_INVALID_PARAMETER;
  }

  CompressedDataSize = 
      OFFSET_OF(COMPRESSED_DATA, Data) +
      InputDataSize;

  *CompressedData = AllocateZeroPool (CompressedDataSize);
  
  Status = (NULL == *CompressedData) ? EFI_OUT_OF_RESOURCES : EFI_SUCCESS;
  HANDLE_ERROR_LABEL(Status, AllocateZeroPool (CompressedDataSize),  AllocateAndInitCompressedDataExit);

  (*CompressedData)->Size = CompressedDataSize;
  (*CompressedData)->UncompressedSize = UncompressedSize;

  if (NULL != InputData)
  {
    CopyMem(&(*CompressedData)->Data, InputData, InputDataSize);
  }

  return EFI_SUCCESS;

 AllocateAndInitCompressedDataExit:

  if (*CompressedData != NULL)
  {
    FreePool(*CompressedData);
    *CompressedData = NULL;
  }

  return Status;
}

void *myalloc(
    void *Opaque, 
    unsigned Items, 
    unsigned Size
)
{
    Opaque = Z_NULL;
    return AllocatePool (Items * Size);
}

void myfree(
    void *Opaque,
    void *Addr
)
{
    Opaque = Z_NULL;
    FreePool(Addr);
}

/**
 * This function compresses the SourceBuffer of SourceSize and the
 * output will be copied to DestinationBuffer, respective DestinationSize 
 * will be updated with compressed size.
 *  
 * @param SourceBuffer          Buffer to compress 
 * @param SourceSize     :      Size of source buffer
 * @param DestinationBuffer  :  Destination buffer to store compressed data
 * @param DestinationSize  :    Destination buffer size
 * 
 * @return EFI_STATUS 
 */

EFI_STATUS
CompressGPT (
  IN VOID       *SourceBuffer,
  IN UINT32      SourceSize,
  IN OUT VOID   *DestinationBuffer,
  IN OUT UINT32 *DestinationSize
  )
{
  z_stream  Stream;
  INT32     Ret;

  if (SourceBuffer == NULL || 
      !SourceSize ||
      DestinationBuffer == NULL ||
      DestinationSize == NULL)
  {
    return EFI_INVALID_PARAMETER;
  }

  Stream.zalloc = myalloc;
  Stream.zfree = myfree;
  Stream.opaque = Z_NULL;

  Stream.next_in  = SourceBuffer; 
  Stream.avail_in = SourceSize;
  
  Stream.next_out  = DestinationBuffer; 
  Stream.avail_out = *DestinationSize;

  Ret = deflateInit2(
    &Stream,
    Z_BEST_COMPRESSION,
    Z_DEFLATED,
    MAX_WBITS,
    MAX_MEM_LEVEL,
    Z_DEFAULT_STRATEGY
    );
  if (Ret != Z_OK)
  {
    DEBUG ((EFI_D_WARN, "deflateInit2 failed!. Ret - %d\n", Ret));
    return EFI_OUT_OF_RESOURCES;
  }

  Ret = deflate(
    &Stream, 
    Z_FINISH
    );
  if (Ret != Z_STREAM_END) {
      DEBUG ((EFI_D_WARN, "deflate failed!. Ret - %d\n", Ret));
      deflateEnd(&Stream);
      return  Ret == Z_OK ? EFI_BUFFER_TOO_SMALL : EFI_NOT_COMPRESSED;
  }

  *DestinationSize = Stream.total_out;

  (VOID) deflateEnd(&Stream);

#ifdef DEBUG
  DEBUG ((EFI_D_ERROR, "    GPT-Data Compression Statistics:: OriginalSize: %d, CompressedSize: %d\n\n", SourceSize, *DestinationSize));
#endif // #ifdef DEBUG

  return EFI_SUCCESS;
}

/**
 * This function decompresses the SourceBuffer of SourceSize and the
 * output will be copied to DestinationBuffer, respective DestinationSize 
 * will be updated with decompressed size.
 *  
 * @param SourceBuffer          Buffer to Decompress 
 * @param SourceSize     :      Size of source buffer
 * @param DestinationBuffer  :  Destination buffer to store decompressed data
 * @param DestinationSize  :    Destination buffer size
 * 
 * @return EFI_STATUS 
 */

EFI_STATUS
DecompressGPT (
  IN VOID       *SourceBuffer,
  IN UINT32      SourceSize,
  IN OUT VOID   *DestinationBuffer,
  IN OUT UINT32 *DestinationSize
  )
{
  z_stream  Stream;
  INT32     Ret;

  if (SourceBuffer == NULL || 
      !SourceSize ||
      DestinationBuffer == NULL ||
      !DestinationSize)
  {
    return EFI_INVALID_PARAMETER;
  }

  Stream.zalloc = myalloc;
  Stream.zfree = myfree;
  Stream.opaque = Z_NULL;

  Stream.next_in  = SourceBuffer; 
  Stream.avail_in = SourceSize;
  
  Stream.next_out  = DestinationBuffer; 
  Stream.avail_out = *DestinationSize;

  Ret = inflateInit2(
    &Stream,
    MAX_WBITS
    );
  if (Ret != Z_OK)
  {
    DEBUG ((EFI_D_WARN, "inflateInit2 failed!. Ret - %d\n", Ret));
    return EFI_OUT_OF_RESOURCES;
  }

  Ret = inflate(
    &Stream, 
    Z_FINISH
    );
  if (Ret != Z_STREAM_END) {
      DEBUG ((EFI_D_WARN, "inflate failed!. Ret - %d\n", Ret));
      inflateEnd(&Stream);
      if (Ret == Z_NEED_DICT || (Ret == Z_BUF_ERROR && Stream.avail_in == 0)) {
          return EFI_COMPROMISED_DATA;
      }
      return EFI_ABORTED;
  }

  *DestinationSize = Stream.total_out;

  (VOID) inflateEnd(&Stream);

  return EFI_SUCCESS;
}

