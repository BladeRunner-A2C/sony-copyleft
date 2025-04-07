/** @file FwGptHelpers.h
   
  Header for FwGptHelpers.h

  Copyright (c) 2011-2016, 2018, 2021-2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when           who         what, where, why
 --------       ---         --------------------------------------------------
 2023/01/19     dmohan      Changes to support Dual SPINOR
 2022/12/26     dmohan      Added changes needed for 8380
 2021/06/30     dmohan      Changes to support A/B Recovery feature
 2018/07/11     prema       Changes to move GPT backup from file to NV
 2018/07/11     rajb        Added support to store active GPT data
 2018/05/21     gparam      Removed unused definitions
 2016/08/16     ltg         Replace "Emmc" with "DiskType"
 2015/04/15     mic         Added 64bit firmware update support
 2012/10/10     jd          Handle GPT switch based on firmware entry list  
 2012/10/08     mic         renamed gpt functions
 2011/10/12     hozefak     Initial version

=============================================================================*/

#ifndef __QCOM_FW_GPT_HELPERS_H__
#define __QCOM_FW_GPT_HELPERS_H__

#include "FwLinkedList.h"
#include <Library/FwUpdateLib/FwPayloadEntry.h>

#define ANYSIZE_ARRAY 1

//Maximum entries allowed for different storage types based on 
//partition.xml file contents.
#define UFS_BOOT_MAX_ENTRIES    0   // 0 LUN1, LUN2 uses ping pong
#define UFS_GPP_MAX_ENTRIES     98  // 88(UFS_LUN4) + 10 reserved for OEM expansion
#define SPINOR_BOOT_MAX_ENTRIES 102 // Few more entries added then actual partition number for OEM expansion
#define NVME_GPP_MAX_ENTRIES    25  // Few more entries added then actual partition number for OEM expansion
#define EMMC_BOOT_MAX_ENTRIES   10  // 2 (XBL. XBL_CONFIG) + 8 reserved for OEM expansion
#define EMMC_GPP_MAX_ENTRIES    40  // 32(GPP) + 8 reserved for OEM expansion

typedef enum{
    ORIGINAL_TABLE,
    SWITCHED_TABLE
}GPT_TABLE_STATE;

typedef enum{
    BACKUP_GPT_TABLE,
    PRIMARY_GPT_TABLE
}GPT_TABLE_TYPE;

// Struct to store active GPT data
typedef struct _ACTIVE_GPT_ENTRY_SUB_DATA {
    EFI_GUID  PartitionTypeGUID;
    CHAR16    PartitionName[PARTITION_NAME_MAX_CHAR16_SIZE];
    UINT32    TableIndex;
} ACTIVE_GPT_ENTRY_SUB_DATA;

typedef struct _ACTIVE_GPT_SUB_DATA {
    UINT32                      Size;
    UINT32                      MaxEntries;
    UINT32                      UsedEntries;
    ACTIVE_GPT_ENTRY_SUB_DATA   ActiveGPTEntrySubData[ANYSIZE_ARRAY];
} ACTIVE_GPT_SUB_DATA;

typedef struct _COMPRESSED_DATA {
    UINT32                      Size;
    UINT32                      UncompressedSize;
    UINT8                       Data[ANYSIZE_ARRAY];
} COMPRESSED_DATA;

/**
 * Invalidates GPT Tables across all storage disks based on table type and 
 * determing if FMP payload include partition updates to a disk.
 *
 * @param tableType   :  Primary or backup GPT table
 *
 * @return EFI_STATUS
 *
 */
EFI_STATUS InvalidateAllGPT(
    IN GPT_TABLE_TYPE  tableType
);

/**
 * Copy Partition Tables (LUN4/SPINOR/NVME/EMMC) to FAT16.bin in files BPx.TBL GPP.TBL
 *
 * @param None
 *
 * @return EFI _STATUS
 *
 */
EFI_STATUS BackupAllGPTTable(VOID);

/**
 * Modifies Boot Partition and GPP partition tables to point to the backup tables 
 * Also modifies and fills in the right CRC 
 * 
 * @param tableType   :  Primary or backup GPT table
 * 
 * @return EFI_STATUS 
 */
EFI_STATUS RestoreAllGPTTablesFromNV(
    IN GPT_TABLE_TYPE  tableType
);

/**
 * Modifies all gpt partition tables (BOOT partition and GPP)
 *
 * @param None
 *
 * @return EFI_STATUS
 *
 */
EFI_STATUS ModifyAllBackupGptTablesForFailSafeUpdate(VOID);

/**
 * Compare GPT with the table in FAT partition and check if it the swapped table 
 * or it is the primary original table 
 *
 * @param tableType       :   Type of GPT Table
 * @param diskTypeGuid    :   Vendor GUID whose GPT has to be 
 *                            compared
 * @param gptNvType       :   Type of NV Data
 * @param pGptTableState  :   returns if GPT table is in the
 *                            original or switched state
 *
 * @return EFI_STATUS
 *
 */
EFI_STATUS CmpGPTTable(
    IN  GPT_TABLE_TYPE          tableType,
    IN  EFI_GUID                diskTypeGuid,
    IN  QCOM_FW_UPDATE_NV_TYPE  gptNvType,
    OUT GPT_TABLE_STATE        *pGptTableState
);


/**
 * Reads the partition table and returns Filesize and FileBuffer
 * with data from the GPT tables. In case FileBuffer is NULL
 * will return only the FileSize by reading the GPT header
 *
 * @param Memory_GUID     : Vendor GUID for which GPT tables
 *                          have to be read
 * @param FileBuffer      : Pointer to buffer where GPT should
 *                          be read. Iif NULL, Function will
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
EFI_STATUS ReadGPTTable(
    IN  EFI_GUID         Memory_GUID,
    OUT OPTIONAL VOID  **FileBuffer,
    OUT UINTN           *FileSize,
    OUT OPTIONAL UINT32 *SizeOfPartitionEntry,
    IN  GPT_TABLE_TYPE   TableType
);

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
);

/**
 *  Function to allocate and init memory for all GPT backup table entries
 *
 * @return EFI_STATUS
 */
EFI_STATUS AllocateAndInitGPTBackupData(
    ACTIVE_GPT_SUB_DATA **BootGPTSubData,
    ACTIVE_GPT_SUB_DATA **GppGPTSubData
);

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
EFI_STATUS AllocateAndInitGPTSubData(
    IN UINT32                  MaxEntries,
    OUT ACTIVE_GPT_SUB_DATA  **GPTSubData
);

/**
 * This function will retrive active GPT data from GPT table
 * 
 * @param memoryGUID           :  Vendor GUID whose GPT has to be changed
 * @param pGptNvTypePtr        :  GPTNvType name
 * @param pDiskPartTypePtr     :  Type of disk partition to be filled
 * @param pMaxEntriesPtr       :  Max. partition entries supported
 *                                for a storage disk
.*
 * @return EFI_STATUS 
 */
EFI_STATUS GetGptDataForDisk(
    IN EFI_GUID                                   memoryGUID,
    OUT OPTIONAL QCOM_FW_UPDATE_NV_TYPE          *pGptNvTypePtr,
    OUT OPTIONAL FWENTRY_DISK_PARTITION_TYPE     *pDiskPartTypePtr,
    OUT OPTIONAL UINT32                          *pMaxEntriesPtr
);

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
EFI_STATUS AllocateAndInitCompressedData(
    IN UINT32                  UncompressedSize,
    IN OPTIONAL VOID          *InputData,
    IN UINT32                  InputDataSize,
    OUT COMPRESSED_DATA      **CompressedData
);

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
  );

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
  );

#endif
