/** @file EnvDxe.h

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
 05/22/2022  vvishu  Initial revision
=============================================================================*/
#ifndef __ENVDXE_H__
#define __ENVDXE_H__

#include <Protocol/EFIQcomEnv.h>

EFI_STATUS
EFI_SetDdrThroughputLow (
   IN EFI_QCOMENV_PROTOCOL *This
   );

UINTN
EFI_GetTimerCountus(
   IN EFI_QCOMENV_PROTOCOL *This
   );


UINTN
EFI_GetTimerCountms(
   IN EFI_QCOMENV_PROTOCOL *This
   );
/**
  Extract the Command line arguments from the Image handle, process them and return
  in Argc, Argv format.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image to extract Cmd line
  @param[in] ArgcPtr        Pointer to Argc count variable.
  @param[in] ArgvArrayPtr   Pointer to Argv variable. If Argc>0 then Argv need to be freed using
                             FreePool call

  @retval EFI_UNSUPPORTED
**/
EFI_STATUS
EFI_GetCmdLineArgs (
    IN EFI_QCOMENV_PROTOCOL *This,
    IN  EFI_HANDLE          ImageHandle,
    OUT UINTN               *ArgcPtr,
    OUT CHAR8               ***ArgvArrayPtr
  );


/**
  Loads a  file from a partition specified by Root Device type GUID
  Partition Type GUID and Block IO attributes

  @param  Path            Path to Smbios file
  @param  RootDeviceType  Root Device Type GUID
  @param  Partition Type  GUID eg: gEfiPartTypeSystemPartGuid
  @param  PartitionLabel  eg: L"logfs"
  @param  BlkIOAttrib     Attributes to be used for fetching Block IO handle
  @param  ReadFileSize    Ptr that can hold read file size

  @retval EFI_UNSUPPORTED
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
   );


/**
  Returns a list of BlkIo handles based on required criteria
  SelectionAttrib : Bitmask representing the conditions that need
                    to be met for the handles returned. Based on the
                    selections filter members should have valid values.
  FilterData      : Instance of Partition Select Filter structure that
                    needs extended data for certain type flags. For example
                    Partition type and/or Volume name can be specified.
  MaxBlkIopCnt    : On input, max number of handle structures the buffer can hold,
  @retval EFI_UNSUPPORTED
 */
EFI_STATUS
EFI_GetBlkIOHandles (
   IN EFI_QCOMENV_PROTOCOL   *This,
   IN  UINT32                SelectionAttrib,
   IN  PartiSelectFilter     *FilterData,
   OUT HandleInfo            *HandleInfoPtr,
   IN OUT  UINT32*           MaxBlkIopCnt
   );

EFI_STATUS
EFI_GetUUID (
   IN EFI_QCOMENV_PROTOCOL *This,
   OUT VOID                *Buffer,
   IN UINT32               BufferSize);



/**
 * Get processor name string
 *
 * @param  ProcNameStr   Pointer to buffer where result can be expected
 * @param  StrSize       Size of the buffer
 *
  @retval EFI_UNSUPPORTED

 * **/
EFI_STATUS
EFI_GetProcessorName (
    IN EFI_QCOMENV_PROTOCOL *This,
    IN OUT  CHAR8*          ProcNameStr,
    IN      UINTN           StrSize
        );

/**
  Delete a  file from specified partition
  @param  Path            Path to Smbios file
  @param  RootDeviceType  Root Device Type GUID
  @param  Partition Type  GUID eg: gEfiPartTypeSystemPartGuid
  @param  PartitionLabel      eg: L"logfs"
  @param  SelectNonRemovable  TRUE for Non-removable / FALSE for Removable
  @param  Volumename          VolumeName to match
  @retval EFI_UNSUPPORTED
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
    );


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
  @retval EFI_UNSUPPORTED

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
  );


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
  @retval EFI_UNSUPPORTED

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
  );

/**
  Get Memory Region information structure created by parsing the
  platform config file

  @param  RegionName             Pointer to ASCII region name in configuration file
  @param  MemRegionInfo          Pointer to MemRegionInfo, allocated by caller,
                                 returns copy in same struct, cannot be NULL

  @retval EFI_UNSUPPORTED
**/
EFI_STATUS
EFI_GetSimpleMemRegionInfoByName (
  IN EFI_QCOMENV_PROTOCOL*      This,
  IN     CHAR8                  *RegionName,
  OUT    SimpleMemRegionInfo    *SimpleMemoryRegion
  );

#endif  /* __ENVDXE_H__ */

