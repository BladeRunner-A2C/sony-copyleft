/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 26/8/21   zxue     support logfs
 14/7/21   zxue     branch for core boot

=============================================================================*/


#ifndef __QDF_FILE_H
#define __QDF_FILE_H

#include <Uefi.h>

typedef VOID *EFI_QDF_FILE_HANDLE;

EFI_STATUS
QdfOpenFile(
    IN CONST CHAR16 *DevicePath,
    IN CONST CHAR16 *FileName,
    IN CONST UINT64 OpenMode,
    OUT EFI_QDF_FILE_HANDLE *FileHandle);

EFI_STATUS
QdfFileWrite(
    IN EFI_QDF_FILE_HANDLE FileHandle,
    IN VOID *Buffer,
    IN OUT UINTN *BufferSize);

EFI_STATUS
QdfFileReadAllocatePool(
    IN EFI_QDF_FILE_HANDLE FileHandle,
    OUT VOID **Buffer,
    IN OUT UINTN *Size);

EFI_STATUS
QdfFileFlush(IN EFI_QDF_FILE_HANDLE FileHandle);

EFI_STATUS
QdfFileClose(IN EFI_QDF_FILE_HANDLE FileHandle);

EFI_STATUS
QdfReadFile(
    IN CONST CHAR16 *DevicePath,
    IN CONST CHAR16 *FileName,
    OUT VOID **Buffer,
    OUT UINTN *Size);

EFI_STATUS
QdfWriteFile(
    IN CONST CHAR16 *DevicePath,
    IN CONST CHAR16 *FileName,
    IN VOID *Buffer,
    IN OUT UINTN *BufferSize);

EFI_STATUS
QdfRenameFile(
    IN CONST CHAR16 *DevicePath,
    IN CONST CHAR16 *FileName,
    IN CONST CHAR16 *NewFileName);

struct Segment {
    UINT64 Size;
    VOID *Buffer;
};

EFI_STATUS
QdfWriteFileSegments(
    IN CONST CHAR16 *DevicePath,
    IN CONST CHAR16 *FileName,
    IN struct Segment *Segments
);

EFI_STATUS
QdfReadFirmwareVolumeSection(
    IN CONST EFI_GUID *NameGuid,
    OUT VOID **Buffer,
    OUT UINTN *Size);

EFI_STATUS 
QdfReadFromPartition (                          
    EFI_GUID         *PartitionGuid   OPTIONAL,                          
    CHAR16           *PartitionLabel  OPTIONAL,                          
    VOID             **ReadBuffer,                          
    UINTN            *ImageSize,                          
    UINT32           Attrib);


/* ----- */
#include <qdf/base_type.h>

struct segment {
    u64 size;
    void *buffer;
};

static inline int
fread(const u16 *filename, u8 **buffer, u64 *size) 
{
    EFI_STATUS Status = QdfReadFile(NULL, (CONST CHAR16 *)filename, 
        (VOID **)buffer, (UINTN *)size);
    return efi_status_to_errno(Status);
}

static inline int 
fvread_section(const GUID *name_guid, u8 **buffer, u64 *buffersize)
{
    EFI_STATUS Status = QdfReadFirmwareVolumeSection(
        name_guid, (VOID **)buffer, (UINTN *)buffersize);
    return efi_status_to_errno(Status);
}

static inline int
fv_read_from_partition(
    EFI_GUID *partition_guid, u16 *partition_Label, 
    u8 **buffer, u64 *image_size, u32 attrib)
{
    EFI_STATUS Status = QdfReadFromPartition(partition_guid, (CHAR16 *)partition_Label, (VOID **)buffer, (UINTN *)image_size, (UINT32)attrib);
	return efi_status_to_errno(Status);
}

#endif //!__QDF_FILE_H
