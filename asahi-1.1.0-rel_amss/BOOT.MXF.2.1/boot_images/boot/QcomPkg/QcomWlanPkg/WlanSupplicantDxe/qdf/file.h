/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
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
    IN UINTN *BufferSize);

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

#endif //!__QDF_FILE_H