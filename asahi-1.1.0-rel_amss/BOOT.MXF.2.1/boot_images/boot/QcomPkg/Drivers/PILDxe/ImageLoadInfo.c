/*===============================================================================
  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE:         ImageLoadInfo.c
  DESCRIPTION:  A file that provied API's to store Image loaded informartion/table in Allocated memory
                This is different to what is being loaded in IMEM.
  
  REVISION HISTORY
  when       who         what, where, why
  --------   ---         --------------------------------------------------------
  11/18/22   ps         initial version
================================================================================*/

#include <ImageLoadInfo.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>

IMAGE_TABLE_INFO *Table = NULL;
IMAGE_ENTRY *ImgEntry = NULL;
SEGMENT_INFO *Info = NULL;

EFI_STATUS InitializeImageLoadInfoTable()
{
  Table = (IMAGE_TABLE_INFO*)AllocateZeroPool(sizeof(IMAGE_TABLE_INFO));
  if(Table == NULL)
    return EFI_OUT_OF_RESOURCES;
  Table->Signature = IMAGE_LOAD_INFO_SIGNATURE;
  Table->NumberOfEntries = 0;
  return EFI_SUCCESS;
}

EFI_STATUS InitNewImageEntry(IN CHAR16 *Name)
{
  if(Name == NULL)
    return EFI_INVALID_PARAMETER;
  
  if(Table == NULL)
    return EFI_NOT_READY;
  
  ImgEntry = (IMAGE_ENTRY*)AllocateZeroPool(sizeof(IMAGE_ENTRY));
  if(ImgEntry == NULL)
    return EFI_OUT_OF_RESOURCES;
  
  ImgEntry->NumberOfSegments = 0;
  ImgEntry->EntryPoint = 0x0;
  return StrCpyS(ImgEntry->Name, MAX_IMAGE_NAME_LENGTH, Name);
  
}

EFI_STATUS InitSegments(UINT64 NumberOfSegments)
{
  if(Table == NULL)
    return EFI_NOT_READY;
  
  Info = (SEGMENT_INFO*)AllocateZeroPool(NumberOfSegments * sizeof(SEGMENT_INFO));
  if(Info == NULL)
    return EFI_OUT_OF_RESOURCES;
  
  ImgEntry->SegmentInfo = Info;
  return EFI_SUCCESS;
}

EFI_STATUS ClearImageEntry()
{
  if(Table == NULL || ImgEntry == NULL )
    return EFI_NOT_READY;

  if(ImgEntry->SegmentInfo != NULL)
	FreePool(ImgEntry->SegmentInfo);

  if(ImgEntry->ElfInfo != NULL)
	  FreePool(ImgEntry->ElfInfo);
  
  FreePool(ImgEntry);
  return EFI_SUCCESS;
}

EFI_STATUS UpdateImageEntryPoint(UINTN EntryPoint)
{
  if(Table == NULL || ImgEntry == NULL )
    return EFI_NOT_READY;
  
  ImgEntry->EntryPoint = EntryPoint;
  return EFI_SUCCESS;
}


EFI_STATUS AddElfInfo(UINTN BaseAddress, UINT32 Size)
{
  if(Table == NULL)
    return EFI_NOT_READY;

  ELF_INFO *ElfInfo = (ELF_INFO*)AllocateZeroPool(sizeof(ELF_INFO));
  if(ElfInfo == NULL)
    return EFI_OUT_OF_RESOURCES;
  
  ElfInfo->BaseAddress = BaseAddress;
  ElfInfo->Size = Size;
  
  ImgEntry->ElfInfo = ElfInfo;
  return EFI_SUCCESS;
}


EFI_STATUS AddSegment(UINTN BaseAddress, UINT32 Size)
{
  if(Table == NULL)
    return EFI_NOT_READY;

  if(Info == NULL)
    return EFI_UNSUPPORTED;
  
  Info->Type = load; // as of now only supporting load segments
  Info->BaseAddress = BaseAddress;
  Info->Size = Size;
  Info++;
  ImgEntry->NumberOfSegments++;
  return EFI_SUCCESS;
  
}

EFI_STATUS AddImageEntry()
{
   if(Table == NULL)
    return EFI_NOT_READY;
  
   if(Table->NumberOfEntries > MAX_IMAGE_ENTRY)
    return EFI_OUT_OF_RESOURCES;
   
   if(ImgEntry == NULL)
     return EFI_UNSUPPORTED;
   
   //Table->Entry[Table->NumberOfEntries] = *ImgEntry;
   CopyMem(&Table->Entry[Table->NumberOfEntries], ImgEntry, sizeof(ImgEntry));
   Table->NumberOfEntries++;
   FreePool(ImgEntry);
   return EFI_SUCCESS;

}

EFI_STATUS GetImageLoadInfoTable(IN OUT IMAGE_TABLE_INFO *ImgInfoTable)
{
  if(Table == NULL)
    return EFI_NOT_READY;
  
  ImgInfoTable = Table;
  return EFI_SUCCESS;
}

EFI_STATUS Clear_ImageLoadInfoTable(){
	if(Table == NULL)
		return EFI_NOT_READY;
	
	for(int index =0; index<Table->NumberOfEntries ; index++){
		FreePool(Table->Entry[index].SegmentInfo);
		FreePool(Table->Entry[index].ElfInfo);
	}
	FreePool(Table);
	
	return EFI_SUCCESS;
}

EFI_STATUS UpdateImageLoadInfoVar()
{
  if(Table == NULL)
    return EFI_NOT_READY;
  EFI_STATUS Status;
  
  IMAGE_TABLE_INFO **ptr = &Table;
 
  
  UINTN      DataSize = 0;
  DataSize = sizeof(&Table);
  
  Status = gRT->SetVariable (L"ImageLoadInfoTableAddr",
                             &gQcomTokenSpaceGuid,
                             EFI_VARIABLE_BOOTSERVICE_ACCESS,
                             DataSize,
                             ptr);
                             
  return Status; 
}


