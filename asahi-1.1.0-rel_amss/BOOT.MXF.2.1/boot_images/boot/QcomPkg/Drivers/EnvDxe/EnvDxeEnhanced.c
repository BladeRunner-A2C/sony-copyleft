/** @file EnvDxeEnhanced.c

  UEFI Environment Dxe code for registering FBPT event handlers
  For all Qualcomm specific initializations

  Copyright (c) 2022 Qualcomm Technologies, Inc.
  All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 27/05/2022  vvishu  Initial revision
=============================================================================*/
#include <Protocol/EFIQcomEnv.h>
#include <Protocol/EFIDDRGetConfig.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/QcomLib.h>
#include <Library/RamPartitionTableLib.h>
#include <Library/KernelLib.h>
#include <Library/UefiCfgLib.h>
#include <Library/EnvDxe.h>

LockHandle* UefiCfgLockPtr;

EFI_STATUS
EFI_SetDdrThroughputLow (
   IN EFI_QCOMENV_PROTOCOL *This
   )
{
  EFI_STATUS               Status;
  UINT32                   DdrMinimumFreq       = 200000;
  EFI_DDRGETINFO_PROTOCOL  *pDDRGetInfoProtocol = NULL;

  Status = gBS->LocateProtocol (&gEfiDDRGetInfoProtocolGuid, NULL, (VOID **)&pDDRGetInfoProtocol);
  if (EFI_ERROR (Status) || (pDDRGetInfoProtocol == NULL)) {
    DEBUG ((EFI_D_ERROR, "Locate EFI_DDRGETINFO_PROTOCOL failed, Status =  (0x%x)\r\n", Status));
    return Status;
  }

  Status = pDDRGetInfoProtocol->SetDDRFreq (pDDRGetInfoProtocol, DdrMinimumFreq);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_WARN, "Failed to set DDR Freq"));
  }

  return Status;
}
UINTN
EFI_GetTimerCountus(
   IN EFI_QCOMENV_PROTOCOL *This
   )
{
  return GetTimerCountus();
}


UINTN
EFI_GetTimerCountms(
   IN EFI_QCOMENV_PROTOCOL *This
   )
{
  return GetTimerCountms();
}
/**
  Extract the Command line arguments from the Image handle, process them and return
  in Argc, Argv format.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image to extract Cmd line
  @param[in] ArgcPtr        Pointer to Argc count variable.
  @param[in] ArgvArrayPtr   Pointer to Argv variable. If Argc>0 then Argv need to be freed using
                             FreePool call
  
  @retval EFI_SUCCESS           Successfully processed
  @retval EFI_OUT_OF_RESOURCES  Failed to allocate memory for the buffers
**/
EFI_STATUS
EFI_GetCmdLineArgs (
    IN EFI_QCOMENV_PROTOCOL *This,
  IN  EFI_HANDLE          ImageHandle,
    OUT UINTN               *ArgcPtr,
    OUT CHAR8               ***ArgvArrayPtr
  )
{
  return GetCmdLineArgs ( ImageHandle,
                          ArgcPtr,
                          ArgvArrayPtr
                        );
}


/**
  Loads a  file from a partition specified by Root Device type GUID
  Partition Type GUID and Block IO attributes

  @param  Path            Path to Smbios file
  @param  RootDeviceType  Root Device Type GUID
  @param  Partition Type  GUID eg: gEfiPartTypeSystemPartGuid
  @param  PartitionLabel  eg: L"logfs"
  @param  BlkIOAttrib     Attributes to be used for fetching Block IO handle
  @param  ReadFileSize    Ptr that can hold read file size

  @return EFI_SUCCESS if successful
**/
EFI_STATUS
EFI_LoadFileFromPartition (
   IN EFI_QCOMENV_PROTOCOL *This,
   UINT32                  BlkIOAttrib,
   CHAR16                  *Path,
   EFI_GUID                *RootDeviceType,
   EFI_GUID                *PartitionType,
   CHAR16                  *PartitionLabel,
   UINT8                   **CfgBuffPtr,
   UINTN                   *ReadFileSize
   )
{
  return LoadFileFromPartition (  BlkIOAttrib,
								  Path,
								  RootDeviceType,
								  PartitionType,
								  PartitionLabel,
								  CfgBuffPtr,
								  ReadFileSize
								);
}


/**
  Returns a list of BlkIo handles based on required criteria
  SelectionAttrib : Bitmask representing the conditions that need
                    to be met for the handles returned. Based on the
                    selections filter members should have valid values.
  FilterData      : Instance of Partition Select Filter structure that
                    needs extended data for certain type flags. For example
                    Partition type and/or Volume name can be specified.
  HandleInfoPtr   : Pointer to array of HandleInfo structures in which the
                    output is returned.
  MaxBlkIopCnt    : On input, max number of handle structures the buffer can hold,
                    On output, the number of handle structures returned.
   @retval EFI_SUCCESS if the operation was successful
 */
EFI_STATUS
EFI_GetBlkIOHandles (
   IN EFI_QCOMENV_PROTOCOL   *This,
   IN  UINT32                SelectionAttrib,
   IN  PartiSelectFilter     *FilterData,
   OUT HandleInfo            *HandleInfoPtr,
   IN OUT  UINT32*           MaxBlkIopCnt
   )
{
  return GetBlkIOHandles(SelectionAttrib,
						 FilterData,
				   		 HandleInfoPtr,
						 MaxBlkIopCnt);
}

EFI_STATUS
EFI_GetUUID (
   IN EFI_QCOMENV_PROTOCOL *This,
   OUT VOID                *Buffer,
   IN UINT32               BufferSize)
{
  return GetUUID(Buffer, BufferSize);
}



/**
 * Get processor name string
 *
 * @param  ProcNameStr   Pointer to buffer where result can be expected
 * @param  StrSize       Size of the buffer
 *
 * @return EFI_SUCCESS if successful
 
 * **/
EFI_STATUS
EFI_GetProcessorName (
    IN EFI_QCOMENV_PROTOCOL *This,
    IN OUT  CHAR8*          ProcNameStr,
    IN      UINTN           StrSize
        )
{
  return GetProcessorName(ProcNameStr, StrSize);
}

/**
  Delete a  file from specified partition
  @param  Path            Path to Smbios file
  @param  RootDeviceType  Root Device Type GUID
  @param  Partition Type  GUID eg: gEfiPartTypeSystemPartGuid
  @param  PartitionLabel      eg: L"logfs"
  @param  SelectNonRemovable  TRUE for Non-removable / FALSE for Removable
  @param  Volumename          VolumeName to match
  @return EFI_SUCCESS if successful
**/

EFI_STATUS
EFI_DeleteFile (
  IN EFI_QCOMENV_PROTOCOL *This,
  IN  CHAR16              *Path,
  IN  EFI_GUID            *RootDeviceType,
  IN  EFI_GUID            *PartitionType,
  IN  CHAR16              *PartitionLabel,
  IN  BOOLEAN             SelectNonRemovable,
  IN  CHAR8               *VolumeName
    )
{
  return DeleteFile(Path,
					RootDeviceType,
					PartitionType,
					PartitionLabel,
					SelectNonRemovable,
					VolumeName
					);
}


/**
  Read a file to a buffer

  @param  Path                File path
  @param  RootDeviceTypeGuid  eg: gEfiEmmcGppPartition1Guid
  @param  PartitionType       eg: gEfiPlatPartitionTypeGuid
  @param  PartitionLabel      eg: L"logfs"
  @param  SelectNonRemovable  TRUE for Non-removable / FALSE for Removable
  @param  Volumename          VolumeName to match
  @param  BytesToRead         # of bytes to read from file
  @param  ReadOffset          Read-offset in file in bytes
  @param  FileBuffer          Data read from file is copied to FileBuffer
  @param  FileBufferSize      Size of the file
  @return EFI_SUCCESS         If file was read successfully

**/
EFI_STATUS
EFI_ReadFile(
  IN EFI_QCOMENV_PROTOCOL *This,
  IN     CHAR16           *Path,
  IN     EFI_GUID         *RootDeviceType,
  IN     EFI_GUID         *PartitionType,
  IN     CHAR16           *PartitionLabel,
  IN     BOOLEAN          SelectNonRemovable,
  IN     CHAR8            *VolumeName,
  IN OUT UINTN            *BytesToRead,
  IN     UINT64           ReadOffset,
  OUT    UINT8            *FileBuffer,
  IN     UINT32           FileBufferSize
  )
{
  return ReadFile( Path,
				 RootDeviceType,
				 PartitionType,
				 PartitionLabel,
				 SelectNonRemovable,   
				 VolumeName,
				 BytesToRead,
				 ReadOffset,
				 FileBuffer,
				 FileBufferSize
				);
}


/**
  Write a buffer to a file

  @param  Path                File path
  @param  RootDeviceTypeGuid  eg: gEfiEmmcGppPartition1Guid
  @param  PartitionType       eg: gEfiPlatPartitionTypeGuid
  @param  PartitionLabel      eg: L"logfs"
  @param  SelectNonRemovable  TRUE for Non-removable / FALSE for Removable
  @param  Volumename          VolumeName to match
  @param  BytesToRead         # of bytes to write to file
  @param  WriteOffset         Write-offset in file in bytes
  @param  FileBuffer          Data written to a file is copied from FileBuffer
  @param  FileBufferSize      Size of the file
  @return EFI_SUCCESS         If file was written successfully

**/
EFI_STATUS
EFI_WriteFile(
  IN EFI_QCOMENV_PROTOCOL *This,
  IN     CHAR16           *Path,
  IN     EFI_GUID         *RootDeviceType,
  IN     EFI_GUID         *PartitionType,
  IN     CHAR16           *PartitionLabel,
  IN     BOOLEAN          SelectNonRemovable,
  IN     CHAR8            *VolumeName,
  IN     UINTN            *BytesToWrite,
  IN     UINT64           WriteOffset,
  IN     UINT8            *FileBuffer,
  IN     UINT32           FileBufferSize
  )
{
  return WriteFile( Path,
					RootDeviceType,
					PartitionType,
					PartitionLabel,
					SelectNonRemovable,
					VolumeName,
					BytesToWrite,
					WriteOffset,
					FileBuffer,
					FileBufferSize
				);
}

/**
  Get Memory Region information structure created by parsing the
  platform config file

  @param  RegionName             Pointer to ASCII region name in configuration file
  @param  MemRegionInfo          Pointer to MemRegionInfo, allocated by caller,
                                 returns copy in same struct, cannot be NULL

  @retval EFI_SUCCESS            Successfully retrieved the entry
  @retval EFI_NOT_FOUND          Unable to find specified entry in table
  @retval EFI_NOT_READY          Error: Config SharedLib is not initialized
  @retval EFI_INVALID_PARAMETER  RegionName or MemoryRegion is NULL
**/
EFI_STATUS
EFI_GetSimpleMemRegionInfoByName (
  IN EFI_QCOMENV_PROTOCOL*      This,
  IN     CHAR8                  *RegionName,
  OUT    SimpleMemRegionInfo    *SimpleMemoryRegion
  )
{
        EFI_STATUS Status;
        MemRegionInfo MemRegion;

        if (RegionName==NULL || SimpleMemoryRegion==NULL)
                return EFI_INVALID_PARAMETER;

        AcquireLock(UefiCfgLockPtr);
        Status = GetMemRegionInfoByName(RegionName, &MemRegion);
        ReleaseLock(UefiCfgLockPtr);

        if(Status == EFI_SUCCESS)
        {
                AsciiStrnCpyS(  SimpleMemoryRegion->Name,
                                                MAX_MEM_LABEL_NAME2,
                                                (CONST CHAR8*)&MemRegion.Name,
                                                MAX_MEM_LABEL_NAME);
                SimpleMemoryRegion->MemBase = MemRegion.MemBase;
                SimpleMemoryRegion->MemSize = MemRegion.MemSize;
        }
        return Status;
}


