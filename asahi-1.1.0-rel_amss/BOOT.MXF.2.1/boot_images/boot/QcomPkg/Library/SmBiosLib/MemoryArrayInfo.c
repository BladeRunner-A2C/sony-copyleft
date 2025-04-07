/** @file
  Updates the SMBios table with the memory array info structure.

  Copyright (c) 2010-2013,2016-2022 Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/18/22   dnkg    Bug Fix for TypeDetail Field & added latest spec fields
 06/15/22   dnkg    Fix Indentation Issues
 05/10/22   vb      Update ConfiguredMemoryClockSpeed field with max DDR speed
 11/09/21   dnkg    Modified Size code and added ExtendedSize code
 05/28/20   kbarad  Added SMBIOS_HANDLE_PI_RESERVED as default handle
 05/06/20   vb      Port changes from boot 3.0.1 to avoid rounding memory to 64MB alignement
 09/26/19   rajb    Added GetInstalledSDRAMMemory to get full RAM size, which will
                    be used to update SMBIOS table and removed round off logic
 04/10/19   vb      Add support for reading APQ feature_id fuse information
 01/20/19   vb      Add support for reading feature_id fuse information
 01/16/18   ltg     Port changes from 2.2 to comply with v3.0
 01/02/17   ltg     Modify MemoryType in smbiosMemoryDeviceInfo
                    Add smbiosMemoryArrayMappedAddressInfo struct
 11/26/13   vk      GetDDRInfo returns UINTN
 07/09/13   vk      Update DDR2 to DDR3
 01/30/13   vk      Fix warning
 07/26/12   vishalo Enable Type 17 table, add latest spec fields
 07/20/12   vishalo Disable adding Type 17 table
 03/23/12   kpa     Add support for config file based smbios table init
 11/23/11   jz      Use library routine to get memory size
 07/20/11   yg      Converted to Lib
 05/25/11   niting  Initial revision

=============================================================================*/

#include <Uefi.h>
#include <Library/UefiLib.h>

#include <Protocol/Smbios.h>

#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/RamPartitionTableLib.h>
#include <Library/QcomBaseLib.h>
#include <SmbiosCfgInfo.h>
#include "SmbiosLibTarget.h"
#include "MemoryArrayInfo.h"

#define UPPER_32_BITS_MASK 0xFFFFFFFF00000000
#define DEVICE_LOCATOR_STRING1 "Top - on board"
#define DEVICE_LOCATOR_STRING2 "Bottom - on board"
#define BANK_LOCATION_STRING "Bank 0"


/**
  Add Memory Array Info /Type 16 table to Smbios table List

  @param  SmbiosTableNode   Pointer to the Smbios Table list
                            node

  @retval EFI_SUCCESS    Initialization success


**/
EFI_STATUS MemoryArrayTableInit( SMBIOS_TABLE_NODE     *SmbiosTableNode)
{
  EFI_STATUS       Status = EFI_INVALID_PARAMETER ;

  if( SmbiosTableNode == NULL)
    return Status;

  // Add type 16 /Memory Array info table.
  SmbiosTableNode->TablePtr= (VOID *) pSMBIOS_MEMORY_ARRAY_INFO ;
  SmbiosTableNode->TableType = EFI_SMBIOS_TYPE_PHYSICAL_MEMORY_ARRAY;
  Status = EFI_SUCCESS;

  return Status;
}

/**
  Add Memory Device Info /Type 17 table to Smbios table List

  @param  SmbiosTableNode   Pointer to the Smbios Table list
                            node

  @retval EFI_SUCCESS    Initialization success


**/
EFI_STATUS MemoryDeviceInfoInit( SMBIOS_TABLE_NODE     *SmbiosTableNode)
{
  EFI_STATUS       Status = EFI_INVALID_PARAMETER ;

  if( SmbiosTableNode == NULL)
    return Status;

  // Add type 17 /Memory Device info table.
  SmbiosTableNode->TablePtr= (VOID *) pSMBIOS_MEMORY_DEVICE_INFO;
  SmbiosTableNode->TableType = EFI_SMBIOS_TYPE_MEMORY_DEVICE;
  Status = EFI_SUCCESS;


  return Status;
}

/**
  Add Memory Array Mapped Address Info /Type 19 table to Smbios table List

  @param  SmbiosTableNode   Pointer to the Smbios Table list
                            node

  @retval EFI_SUCCESS    Initialization success


**/
EFI_STATUS MemoryArrayMappedAddressInfoInit( SMBIOS_TABLE_NODE     *SmbiosTableNode)
{
  EFI_STATUS       Status = EFI_INVALID_PARAMETER ;

  if( SmbiosTableNode == NULL)
    return Status;

  // Add type 19 /Memory Array Mapped Address info table.
  SmbiosTableNode->TablePtr= (VOID *) pSMBIOS_MEMORY_ARRAY_MAPPED_ADDRESS;
  SmbiosTableNode->TableType = EFI_SMBIOS_TYPE_MEMORY_ARRAY_MAPPED_ADDRESS;
  Status = EFI_SUCCESS;

  return Status;
}

EFI_STATUS UpdateMemoryArrayInfoTable (EFI_SMBIOS_PROTOCOL *Smbios)
{
  EFI_STATUS              Status;
  EFI_SMBIOS_HANDLE       MemoryArrayHandle = SMBIOS_HANDLE_PI_RESERVED;
  EFI_SMBIOS_HANDLE       MemoryDeviceHandle = SMBIOS_HANDLE_PI_RESERVED;
  EFI_SMBIOS_HANDLE       MemoryArrayMappedAddressHandle = SMBIOS_HANDLE_PI_RESERVED;

  UINTN                   MemoryCapacity;
  UINTN                   StartAddress;
  UINTN                   StringNum = 0;

  /* Get available memory from partition table */
  InitRamPartitionTableLib();
  Status = GetInstalledSDRAMMemory(&MemoryCapacity);
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }

  Status = GetLowestPhysicalStartAddress(&StartAddress);
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }

  pSMBIOS_MEMORY_ARRAY_INFO->MaximumCapacity = (UINT32) ((MemoryCapacity / (1024)));

  //Add the Memory Info
  Status = Smbios->Add(
    Smbios,
    NULL,
    &MemoryArrayHandle,
    (EFI_SMBIOS_TABLE_HEADER*) pSMBIOS_MEMORY_ARRAY_INFO
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }

  // Store table handle and Update strings if any.
  UpdateTableData(
    Smbios,
    MemoryArrayHandle,
    EFI_SMBIOS_TYPE_PHYSICAL_MEMORY_ARRAY
    );

  //Add the Memory Device
  pSMBIOS_MEMORY_DEVICE_INFO->PhysMemArrayHandle = MemoryArrayHandle;

  //If ( size of the memory device ) >= (32GB-1MB), populate Size field
  //with 0x7FFF and actual value in ExtendedSize.
  if((MemoryCapacity / 1024 / 1024) >= 0x7FFF )
  {
    pSMBIOS_MEMORY_DEVICE_INFO->Size = 0x7FFF;
    pSMBIOS_MEMORY_DEVICE_INFO->ExtendedSize = (UINT32)(MemoryCapacity / 1024 / 1024);
  }
  //Else populate the actual value in Size field
  else
  {
    pSMBIOS_MEMORY_DEVICE_INFO->Size = (UINT16)(MemoryCapacity / 1024 / 1024);
  }

  //Get DDR speed
  smbiosGetDDRSpeed(&(pSMBIOS_MEMORY_DEVICE_INFO->Speed));

  //Get max DDR speed
  smbiosGetDDRSpeed(&(pSMBIOS_MEMORY_DEVICE_INFO->ConfiguredMemoryClockSpeed));

  Status = Smbios->Add(
    Smbios,
    NULL,
    &MemoryDeviceHandle,
    (EFI_SMBIOS_TABLE_HEADER*)pSMBIOS_MEMORY_DEVICE_INFO
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }
  // Store table handle and Update strings if any.
  UpdateTableData(
    Smbios,
    MemoryDeviceHandle,
    EFI_SMBIOS_TYPE_MEMORY_DEVICE
    );

  StringNum = pSMBIOS_MEMORY_DEVICE_INFO->DeviceLocationStringNum;

  Status = Smbios->UpdateString(
    Smbios,
    &MemoryDeviceHandle,
    (UINTN *)&StringNum,
    (CHAR8 *)DEVICE_LOCATOR_STRING1
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }

  StringNum = pSMBIOS_MEMORY_DEVICE_INFO->BankLocationStringNum;

  Status = Smbios->UpdateString(
    Smbios,
    &MemoryDeviceHandle,
    (UINTN *)&StringNum,
    (CHAR8 *)BANK_LOCATION_STRING
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }

  //Add the Memory Array Mapped Address
  pSMBIOS_MEMORY_ARRAY_MAPPED_ADDRESS->MemoryArrayHandle = MemoryArrayHandle;

  // if the starting or ending addresses are greater than the max 32-bit value, populate the extended address fields
  // otherwise, populate the regular address fields
  if ( (((UINT64) StartAddress) & UPPER_32_BITS_MASK) || (((UINT64) (StartAddress + MemoryCapacity - 1)) & UPPER_32_BITS_MASK) ){
    pSMBIOS_MEMORY_ARRAY_MAPPED_ADDRESS->ExtendedStartingAddress = (UINT64) StartAddress;
    pSMBIOS_MEMORY_ARRAY_MAPPED_ADDRESS->ExtendedEndingAddress = (UINT64) (StartAddress + MemoryCapacity - 1);
  }
  else{
    pSMBIOS_MEMORY_ARRAY_MAPPED_ADDRESS->StartingAddress = (UINT32) StartAddress;
    pSMBIOS_MEMORY_ARRAY_MAPPED_ADDRESS->EndingAddress = (UINT32) (StartAddress + MemoryCapacity - 1);
  }

  Status = Smbios->Add(
    Smbios,
    NULL,
    &MemoryArrayMappedAddressHandle,
    (EFI_SMBIOS_TABLE_HEADER*) pSMBIOS_MEMORY_ARRAY_MAPPED_ADDRESS
    );
  if(Status == EFI_SUCCESS)
  {
    // Store table handle and Update strings if any.
    UpdateTableData(
      Smbios,
      MemoryArrayMappedAddressHandle,
      EFI_SMBIOS_TYPE_MEMORY_ARRAY_MAPPED_ADDRESS
      );
  }
  return Status;

}

