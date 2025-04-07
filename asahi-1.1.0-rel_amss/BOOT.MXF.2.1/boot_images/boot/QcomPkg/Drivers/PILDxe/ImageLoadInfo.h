/*===============================================================================
  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE:         ImageLoadInfo.h
  DESCRIPTION:  Header file to store Image loaded informartion/table in Allocated memory
                This is different to what is being loaded in IMEM.  
  
  REVISION HISTORY
  when       who         what, where, why
  --------   ---         --------------------------------------------------------
  11/18/22   cm           initial version

================================================================================*/

#ifndef __IMG_LOADINFO_H__
#define __IMG_LOADINFO_H__

#define IMAGE_LOAD_INFO_SIGNATURE  ('L' | ('G' << 8) | ('M' << 16) | ('I' << 24))
#define MAX_IMAGE_NAME_LENGTH 32
#define MAX_IMAGE_ENTRY       10
#define MAX_NUM_SEGMENTS      64


typedef enum {
  load = 1,
} segment_type;

typedef struct {
  segment_type Type;
  UINTN BaseAddress;
  UINT32 Size;
} SEGMENT_INFO;

typedef struct {
  UINTN BaseAddress;
  UINT32 Size;
} ELF_INFO;


typedef struct {
  CHAR16       Name[MAX_IMAGE_NAME_LENGTH];
  UINTN        EntryPoint;
  UINT32       NumberOfSegments;
  UINT64       reserved0;
  UINT64       reserved1;
  ELF_INFO     *ElfInfo;
  SEGMENT_INFO *SegmentInfo;
} IMAGE_ENTRY;

typedef struct {
  UINT32      Signature;
  IMAGE_ENTRY Entry[MAX_IMAGE_ENTRY];
  UINT32      NumberOfEntries;
} IMAGE_TABLE_INFO;

EFI_STATUS InitializeImageLoadInfoTable();
EFI_STATUS GetImageLoadInfoTable(IN OUT IMAGE_TABLE_INFO *ImgInfoTable);
EFI_STATUS InitNewImageEntry(IN CHAR16 *Name);
EFI_STATUS ClearImageEntry();
EFI_STATUS UpdateImageEntryPoint(UINTN EntryPoint);
EFI_STATUS AddImageEntry();
EFI_STATUS InitSegments(UINT64 NumberOfSegments);
EFI_STATUS AddSegment(UINTN BaseAddress, UINT32 Size);
EFI_STATUS UpdateImageLoadInfoVar();
EFI_STATUS AddElfInfo(UINTN BaseAddress, UINT32 Size);
EFI_STATUS Clear_ImageLoadInfoTable();

#endif

