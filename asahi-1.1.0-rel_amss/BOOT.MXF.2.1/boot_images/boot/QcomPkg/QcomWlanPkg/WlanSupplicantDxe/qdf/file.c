/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "file.h"
#include "WlanSupplicant.h"
#include <Pi/PiFirmwareFile.h>
#include <Library/DxeServicesLib.h>
#include <Library/EfiFileLib.h>
#include <Debug.h>

#if SUPPORT_DEBUG_PRINT
#define SUPPORT_EFI_FILE_LIB  1
#endif

extern EFI_BOOT_SERVICES *gBS;

typedef EFI_STATUS(*EFI_QDF_FILE_READ_ALLOCATE_POOL)(VOID *Context, VOID **Buffer, OUT UINTN *Size);
typedef EFI_STATUS(*EFI_QDF_FILE_WRITE)(VOID *Context, VOID *Buffer, UINTN *BufferSize);
typedef EFI_STATUS(*EFI_QDF_FILE_FLUSH)(VOID *Context);
typedef EFI_STATUS(*EFI_QDF_FILE_CLOSE)(VOID *Context);
typedef EFI_STATUS(*EFI_QDF_FILE_DELETE)(VOID *Context);
typedef EFI_STATUS(*EFI_QDF_FILE_SETNAME)(VOID *Context, CONST CHAR16 *NewFileName);

typedef struct {
    UINT32 Header;
    VOID *Context;
    EFI_QDF_FILE_READ_ALLOCATE_POOL ReadAllocatePool;
    EFI_QDF_FILE_WRITE Write;
    EFI_QDF_FILE_FLUSH Flush;
    EFI_QDF_FILE_CLOSE Close;
    EFI_QDF_FILE_DELETE Delete;
    EFI_QDF_FILE_SETNAME SetName;
} EFI_QDF_FILE;

#define QDF_FILE_HEADER SIGNATURE_32('E', 'Q', 'D', 'F')

STATIC EFI_FILE_PROTOCOL *
SimpleOpenFile(
    IN CONST CHAR16 *FileName,
    IN CONST UINT64 OpenMode)
{
    EFI_STATUS                      Status;
    EFI_LOADED_IMAGE_PROTOCOL       *Image;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *Vol;
    EFI_FILE_PROTOCOL               *RootDir;
    EFI_FILE_PROTOCOL               *FileHandle = NULL;
    CHAR16                          LocalFileName[256] = { 0 };

    Image = GetDriverLoadedImage();

    Status = gBS->HandleProtocol(
        Image->DeviceHandle,
        &gEfiSimpleFileSystemProtocolGuid,
        (VOID **)&Vol
    );
    if (EFI_ERROR(Status)) {
        DbgWarn("Failed to get simple file system volume: %r\n", Status);
        return NULL;
    }

    Status = Vol->OpenVolume(Vol, &RootDir);
    if (EFI_ERROR(Status)) {
        DbgWarn("Failed to open volume: %r\n", Status);
        return NULL;
    }

    UnicodeSPrint(LocalFileName, sizeof(LocalFileName), L"%s", FileName);

    Status = RootDir->Open(RootDir, &FileHandle, LocalFileName, OpenMode, 0);
    if (EFI_ERROR(Status)) {
        DbgWarn("Failed to open file '%s': %r\n", LocalFileName, Status);
        goto CloseRootDir;
    }

CloseRootDir:
    RootDir->Close(RootDir);
    return FileHandle;
}

STATIC EFI_STATUS
SimpleFileWrite(
    IN EFI_FILE_PROTOCOL *FileHandle, 
    IN VOID *Buffer, 
    IN OUT UINTN *BufferSize)
{
    EFI_STATUS Status;
    Status = FileHandle->Write(FileHandle, BufferSize, Buffer);

    return Status;
}

STATIC EFI_STATUS
SimpleFileReadAllocatePool(
    IN EFI_FILE_PROTOCOL *FileHandle,
    IN VOID **Buffer,
    IN OUT UINTN *Size)
{
    EFI_FILE_INFO                   *FileInfo;
    UINTN                           InfoSize = 0;
    EFI_STATUS Status;

    FileHandle->GetInfo(FileHandle, &gEfiFileInfoGuid, &InfoSize, NULL);
    FileInfo = AllocatePool(InfoSize);
    if (!FileInfo) {
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    Status = FileHandle->GetInfo(FileHandle, &gEfiFileInfoGuid, &InfoSize, FileInfo);
    if (EFI_ERROR(Status)) {
        DbgError("Failed to get file size: %r\n", Status);
        goto Exit;
    }

    *Size = FileInfo->FileSize;
    FreePool(FileInfo);
    *Buffer = (VOID *)AllocateZeroPool(*Size);
    if (!*Buffer) {
        DbgError("Failed to allocate buffer\n");
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    Status = FileHandle->Read(FileHandle, Size, *Buffer);
    if (EFI_ERROR(Status)) {
        DbgError("Read file error: %r\n", Status);
        goto FreeBuffer;
    }

    return Status;

FreeBuffer:
    FreePool(*Buffer);
Exit:
    return Status;
}

STATIC EFI_STATUS
SimpleFileFlush(
    IN EFI_FILE_PROTOCOL *FileHandle)
{
    return FileHandle->Flush(FileHandle);
}

STATIC EFI_STATUS
SimpleFileClose(
    IN EFI_FILE_PROTOCOL *FileHandle)
{
    return FileHandle->Close(FileHandle);
}

STATIC EFI_STATUS
SimpleFileDelete(
    IN EFI_FILE_PROTOCOL *FileHandle)
{
    return FileHandle->Delete(FileHandle);
}

STATIC
EFI_STATUS
SimpleFileSetName(
    IN EFI_FILE_PROTOCOL *FileHandle,
    IN CONST CHAR16 *NewFileName)
{
    EFI_STATUS Status;
    EFI_FILE_INFO *FileInfo = NULL;
    UINTN InfoSize = 0, BufferSize = 0;

    FileHandle->GetInfo(FileHandle, &gEfiFileInfoGuid, &InfoSize, NULL);
    if (!InfoSize) {
        DbgError("Failed to get file info size: %d\n", InfoSize);
        Status = EFI_NOT_FOUND;
        goto Out;
    }

    BufferSize = MAX(InfoSize, OFFSET_OF(EFI_FILE_INFO, FileName) + 256);
    FileInfo = AllocatePool(BufferSize);
    if (!FileInfo) {
        Status = EFI_OUT_OF_RESOURCES;
        goto FreeBuffer;
    }
    InfoSize = BufferSize;

    Status = FileHandle->GetInfo(FileHandle, &gEfiFileInfoGuid, &InfoSize, FileInfo);
    if (EFI_ERROR(Status)) {
        DbgError("Failed to get file info (size %d): %r\n", InfoSize, Status);
        goto FreeBuffer;
    }

    Status = StrCpyS(FileInfo->FileName,
        (BufferSize - OFFSET_OF(EFI_FILE_INFO, FileName)) / sizeof(CHAR16), NewFileName);
    if (EFI_ERROR(Status)) {
        DbgError("Failed to copy new file name (info size %d, dest size %d: %r\n",
            InfoSize, (InfoSize - OFFSET_OF(EFI_FILE_INFO, FileName)) / sizeof(CHAR16), Status);
        goto FreeBuffer;
    }

    Status = FileHandle->SetInfo(FileHandle, &gEfiFileInfoGuid, BufferSize, FileInfo);
    if (EFI_ERROR(Status)) {
        DbgError("Failed to set file info: %r\n", Status);
        goto FreeBuffer;
    }

FreeBuffer:
    FreePool(FileInfo);
Out:
    return Status;
}

STATIC EFI_STATUS
SimpleOpenQdfFile(
    IN CONST CHAR16 *FileName,
    IN CONST UINT64 OpenMode,
    OUT EFI_QDF_FILE **FileHandle)
{
    EFI_FILE_PROTOCOL *SimpleFileHandle;
    EFI_QDF_FILE *QdfFile;

    SimpleFileHandle = SimpleOpenFile(FileName, OpenMode);
    if (!SimpleFileHandle)
        return EFI_DEVICE_ERROR;

    QdfFile = (EFI_QDF_FILE *)AllocateZeroPool(sizeof(EFI_QDF_FILE));
    if (SimpleFileHandle == NULL) {
        SimpleFileClose(SimpleFileHandle);
        return EFI_OUT_OF_RESOURCES;
    }

    QdfFile->Header = QDF_FILE_HEADER;
    QdfFile->Context = SimpleFileHandle;
    QdfFile->ReadAllocatePool = (EFI_QDF_FILE_READ_ALLOCATE_POOL)SimpleFileReadAllocatePool;
    QdfFile->Write = (EFI_QDF_FILE_WRITE)SimpleFileWrite;
    QdfFile->Flush = (EFI_QDF_FILE_FLUSH)SimpleFileFlush;
    QdfFile->Close = (EFI_QDF_FILE_CLOSE)SimpleFileClose;
    QdfFile->Delete = (EFI_QDF_FILE_DELETE)SimpleFileDelete;
    QdfFile->SetName = (EFI_QDF_FILE_SETNAME)SimpleFileSetName;

    *FileHandle = QdfFile;
    return EFI_SUCCESS;
}

#if SUPPORT_EFI_FILE_LIB

STATIC EFI_STATUS
EfiFlush(IN EFI_OPEN_FILE *FileHandle)
{
    if (!FileHandle->FsFileHandle)
        return EFI_UNSUPPORTED;

    return FileHandle->FsFileHandle->Flush(FileHandle->FsFileHandle);
}

STATIC EFI_STATUS 
EfiDelete(IN EFI_OPEN_FILE *FileHandle)
{
    if (!FileHandle->FsFileHandle)
        return EFI_UNSUPPORTED;

    return FileHandle->FsFileHandle->Delete(FileHandle->FsFileHandle);
}

STATIC EFI_STATUS
EfiSetName(
    IN EFI_OPEN_FILE *FileHandle,
    IN CONST CHAR16 *NewFileName)
{
    if (!FileHandle->FsFileHandle)
        return EFI_UNSUPPORTED;

    return SimpleFileSetName(FileHandle->FsFileHandle, NewFileName);
}

STATIC EFI_STATUS
EfiOpenQdfFile(
    IN CONST CHAR16 *FileName,
    IN CONST UINT64 OpenMode,
    OUT EFI_QDF_FILE **FileHandle)
{
    CHAR8 AsciiFileName[256] = { 0 };
    EFI_OPEN_FILE *OpenFileHandle = NULL;
    EFI_QDF_FILE *QdfFile;
    EFI_STATUS Status;

    Status = UnicodeStrToAsciiStrS(FileName, AsciiFileName, ARRAY_SIZE(AsciiFileName));
    if (EFI_ERROR(Status)) {
        DbgError("Failed to get ascii file name: %r\n", Status);
        return Status;
    }

    OpenFileHandle = EfiOpen(AsciiFileName, OpenMode, 0);
    if (!OpenFileHandle)
        return EFI_DEVICE_ERROR;

    QdfFile = (EFI_QDF_FILE *)AllocateZeroPool(sizeof(EFI_QDF_FILE));
    if (QdfFile == NULL) {
        EfiClose(OpenFileHandle);
        return EFI_OUT_OF_RESOURCES;
    }

    QdfFile->Header = QDF_FILE_HEADER;
    QdfFile->Context = OpenFileHandle;
    QdfFile->ReadAllocatePool = (EFI_QDF_FILE_READ_ALLOCATE_POOL)EfiReadAllocatePool;
    QdfFile->Write = (EFI_QDF_FILE_WRITE)EfiWrite;
    QdfFile->Flush = (EFI_QDF_FILE_FLUSH)EfiFlush;
    QdfFile->Close = (EFI_QDF_FILE_CLOSE)EfiClose;
    QdfFile->Delete = (EFI_QDF_FILE_DELETE)EfiDelete;
    QdfFile->SetName = (EFI_QDF_FILE_SETNAME)EfiSetName;

    *FileHandle = QdfFile;

    return EFI_SUCCESS;
}

#endif // !SUPPORT_EFI_FILE_LIB

EFI_STATUS
QdfOpenFile(
    IN CONST CHAR16 *DevicePath,
    IN CONST CHAR16 *FileName,
    IN CONST UINT64 OpenMode,
    OUT EFI_QDF_FILE_HANDLE *FileHandle)
{
    if (!FileName)
        return EFI_INVALID_PARAMETER;

    if (DevicePath && DevicePath[0] != 0) {
#if SUPPORT_EFI_FILE_LIB
        CHAR16 FilePath[256] = { 0 };
        UnicodeSPrint(FilePath, ARRAY_SIZE(FilePath), L"%s%s", DevicePath, FileName);
        return EfiOpenQdfFile(FilePath, OpenMode, (EFI_QDF_FILE **)FileHandle);
#else
        return EFI_UNSUPPORTED;
#endif
    }
    else {
        return SimpleOpenQdfFile(FileName, OpenMode, (EFI_QDF_FILE **)FileHandle);
    }
}

EFI_STATUS
QdfFileWrite(
    IN EFI_QDF_FILE_HANDLE FileHandle, 
    IN VOID *Buffer, 
    IN OUT UINTN *BufferSize)
{
    EFI_QDF_FILE *QdfFile = FileHandle;

    if (!QdfFile || !QdfFile->Write)
        return EFI_UNSUPPORTED;

    return QdfFile->Write(QdfFile->Context, Buffer, BufferSize);
}

EFI_STATUS
QdfFileReadAllocatePool(
    IN EFI_QDF_FILE_HANDLE FileHandle, 
    OUT VOID **Buffer, 
    IN OUT UINTN *Size)
{
    EFI_QDF_FILE *QdfFile = FileHandle;

    if (!QdfFile || !QdfFile->ReadAllocatePool)
        return EFI_UNSUPPORTED;

    return QdfFile->ReadAllocatePool(QdfFile->Context, Buffer, Size);
}

EFI_STATUS
QdfFileFlush(IN EFI_QDF_FILE_HANDLE FileHandle)
{
    EFI_QDF_FILE *QdfFile = FileHandle;

    if (!QdfFile || !QdfFile->Flush)
        return EFI_UNSUPPORTED;

    return QdfFile->Flush(QdfFile->Context);
}

EFI_STATUS
QdfFileClose(IN EFI_QDF_FILE_HANDLE FileHandle)
{
    EFI_STATUS Status;
    EFI_QDF_FILE *QdfFile = FileHandle;
    
    if (!QdfFile || !QdfFile->Close)
        return EFI_UNSUPPORTED;

    Status = QdfFile->Close(QdfFile->Context);

    if (EFI_ERROR(Status))
        return Status;

    FreePool(QdfFile);
    return Status;
}

EFI_STATUS
QdfFileDelete(IN EFI_QDF_FILE_HANDLE FileHandle)
{
    EFI_STATUS Status;
    EFI_QDF_FILE *QdfFile = FileHandle;

    if (!QdfFile || !QdfFile->Delete)
        return EFI_UNSUPPORTED;

    Status = QdfFile->Delete(QdfFile->Context);
    if (!EFI_ERROR(Status))
        FreePool(QdfFile);

    return Status;
}

EFI_STATUS
QdfFileSetName(
    IN EFI_QDF_FILE_HANDLE FileHandle,
    IN CONST CHAR16 *NewFileName)
{
    EFI_QDF_FILE *QdfFile = FileHandle;

    if (!QdfFile->SetName)
        return EFI_UNSUPPORTED;

    return QdfFile->SetName(QdfFile->Context, NewFileName);
}

EFI_STATUS
QdfReadFile(
    IN CONST CHAR16 *DevicePath,
    IN CONST CHAR16 *FileName,
    OUT VOID **Buffer,
    OUT UINTN *Size)
{
    EFI_STATUS Status;
    EFI_QDF_FILE_HANDLE FileHandle = NULL;

    Status = QdfOpenFile(DevicePath, FileName, EFI_FILE_MODE_READ, &FileHandle);
    if (EFI_ERROR(Status) || !FileHandle) {
        DbgWarn("Failed to open file '%s%s': %r\n", 
            DevicePath ? DevicePath : L"", FileName, Status);
        goto Out;
    }

    Status = QdfFileReadAllocatePool(FileHandle, Buffer, Size);
    if (EFI_ERROR(Status)) {
        DbgWarn("Failed to read file '%s%s': %r\n", 
            DevicePath ? DevicePath : L"", FileName, Status);
        goto CloseFile;
    }

    DbgInfo("Read '%s%s' (%d bytes)\n", 
        DevicePath ? DevicePath : L"", FileName, *Size);
   
CloseFile:
    QdfFileClose(FileHandle);

Out:
    return Status;
}

EFI_STATUS
QdfWriteFile(
    IN CONST CHAR16 *DevicePath,
    IN CONST CHAR16 *FileName,
    IN VOID *Buffer,
    IN OUT UINTN *BufferSize
)
{
    EFI_STATUS Status;
    EFI_QDF_FILE_HANDLE FileHandle = NULL;

    Status = QdfOpenFile(DevicePath, FileName,
        EFI_FILE_MODE_CREATE | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_READ, 
        &FileHandle);
    if (EFI_ERROR(Status) || !FileHandle) {
        DbgError("Failed to open file '%s%s': %r\n", 
            DevicePath ? DevicePath : L"", FileName, Status);
        goto Out;
    }

    Status = QdfFileWrite(FileHandle, Buffer, BufferSize);
    if (EFI_ERROR(Status)) {
        DbgError("Failed to write file '%s%s': %r\n", 
            DevicePath ? DevicePath : L"", FileName, Status);
        goto CloseFile;
    }

    DbgInfo("Write '%s%s' (%d bytes)\n", 
        DevicePath ? DevicePath : L"", FileName, *BufferSize);

CloseFile:
    QdfFileClose(FileHandle);
Out:
    return Status;
}

EFI_STATUS
QdfWriteFileSegments(
    IN CONST CHAR16 *DevicePath,
    IN CONST CHAR16 *FileName,
    IN struct Segment *Segments
)
{
    EFI_STATUS Status;
    struct Segment *Segment = Segments;
    UINT64 TotalSize = 0;
    EFI_QDF_FILE_HANDLE FileHandle = NULL;

    Status = QdfOpenFile(DevicePath, FileName,
        EFI_FILE_MODE_CREATE | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_READ,
        &FileHandle);
    if (EFI_ERROR(Status) || !FileHandle) {
        DbgError("Failed to open file '%s%s': %r\n", DevicePath ? DevicePath : L"", FileName, Status);
        goto Out;
    }

    do {
        if ((Segment->Size == 0) || (Segment->Buffer == NULL))
            break;

        Status = QdfFileWrite(FileHandle, Segment->Buffer, &Segment->Size);
        if (EFI_ERROR(Status)) {
            DbgError("Write file error: %r\n", Status);
            break;
        }
        TotalSize += Segment->Size;
        Segment++;
    } while (1);

    DEBUG_PARAMETER(TotalSize);
    DbgInfo("Write '%s%s' (%d bytes)\n", 
        DevicePath ? DevicePath : L"", FileName, TotalSize);

    QdfFileClose(FileHandle);

Out:
    return Status;
}

EFI_STATUS
QdfRenameFile(
    IN CONST CHAR16 *DevicePath,
    IN CONST CHAR16 *FileName,
    IN CONST CHAR16 *NewFileName)
{
    EFI_STATUS Status;
    EFI_QDF_FILE_HANDLE FileHandle, ExistedFileHandle;

    Status = QdfOpenFile(DevicePath, FileName, 
        EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, &FileHandle);
    if (EFI_ERROR(Status)) {
        DbgError("Failed to open file '%s%s': %r\n", 
            DevicePath ? DevicePath : L"", FileName, Status);
        goto Out;
    }

    // Exists a file with NewFileName
    Status = QdfOpenFile(DevicePath, NewFileName, 
        EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, &ExistedFileHandle);
    if (!EFI_ERROR(Status)) {
        Status = QdfFileDelete(ExistedFileHandle);
        if (EFI_ERROR(Status)) {
            DbgError("Failed to delete file '%s%s': %r\n", 
                DevicePath ? DevicePath : L"", NewFileName, Status);
            goto CloseExistedFile;
        }
    }

    Status = QdfFileSetName(FileHandle, NewFileName);
    if (EFI_ERROR(Status)) {
        DbgError("Failed to set filename '%s': %r\n", NewFileName, Status);
        goto CloseFile;
    }

    DbgError("Rename '%s%s' to '%s%s'\n", 
        DevicePath ? DevicePath : L"", FileName, 
        DevicePath ? DevicePath : L"", NewFileName);
    goto CloseFile;

CloseExistedFile:
    QdfFileClose(ExistedFileHandle);

CloseFile:
    QdfFileClose(FileHandle);

Out:
    return Status;
}

