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

#ifndef __MEMORY_ARRAY_INFO_H__
#define __MEMORY_ARRAY_INFO_H__

#include <Uefi.h>
#include <Protocol/Smbios.h>

#pragma pack(1)

typedef struct _SMBIOS_MEMORY_ARRAY_INFO
{
  EFI_SMBIOS_TABLE_HEADER  Header;

  UINT8                    Location;
  UINT8                    Use;
  UINT8                    MemoryErrorCondition;
  UINT32                   MaximumCapacity;
  UINT16                   MemErrorInfoHandle;
  UINT16                   NumMemoryDevices;
  //SMBIOS SPEC version 2.7+
  UINT64                   ExtendedMaxCapacity;
  UINT8                    EndNull1;
  UINT8                    EndNull2;
} SMBIOS_MEMORY_ARRAY_INFO;

typedef struct _MEMORY_ENDNULL_STRUCTURE{
  UINT8                    EndNull1;
  UINT8                    EndNull2;
} MEMORY_ENDNULL_STRUCTURE;

typedef struct _SMBIOS_MEMORY_DEVICE_INFO
{
  EFI_SMBIOS_TABLE_HEADER  Header;
  UINT16                   PhysMemArrayHandle;
  UINT16                   MemErrorHandle;
  UINT16                   TotalWidth;
  UINT16                   DataWidth;
  UINT16                   Size;
  UINT8                    FormFactor;
  UINT8                    DeviceSet;
  UINT8                    DeviceLocationStringNum;
  UINT8                    BankLocationStringNum;
  UINT8                    MemoryType;
  UINT16                   TypeDetail;
  UINT16                   Speed;
  UINT8                    ManufacturerStringNum;
  UINT8                    SerialNumberStringNum;
  UINT8                    AssetTagStringNum;
  UINT8                    PartNumberStringNum;
  UINT8                    Attributes;
  UINT32                   ExtendedSize;
  UINT16                   ConfiguredMemoryClockSpeed;
  UINT16                   MinimumVoltage;
  UINT16                   MaximumVoltage;
  UINT16                   ConfiguredVoltage;
  //SMBIOS SPEC version 3.2+
  UINT8                    MemoryTechnology;
  UINT16                   MemoryOperatingModeCapability;
  UINT8                    FirmwareVersion;
  UINT16                   ModuleManufacturerID;
  UINT16                   ModuleProductID;
  UINT16                   MemorySubsystemControllerManufacturerID;
  UINT16                   MemorySubsystemControllerProductID;
  UINT64                   NonVolatileSize;
  UINT64                   VolatileSize;
  UINT64                   CacheSize;
  UINT64                   LogicalSize;
  UINT8                    String1[2];
  UINT8                    String2[2];
  UINT8                    String3[2];
  UINT8                    String4[2];
  UINT8                    String5[2];
  UINT8                    String6[2];
  UINT8                    EndNull;
} SMBIOS_MEMORY_DEVICE_INFO;

typedef struct _MEMORY_DEVICE_INFO_STRING_STRUCTURE {
  UINT8                    String1[2];
  UINT8                    String2[2];
  UINT8                    String3[2];
  UINT8                    String4[2];
  UINT8                    String5[2];
  UINT8                    String6[2];
  UINT8                    EndNull;
} MEMORY_DEVICE_INFO_STRING_STRUCTURE;

typedef struct _SMBIOS_MEMORY_ARRAY_MAPPED_ADDRESS {
  EFI_SMBIOS_TABLE_HEADER  Header;
  UINT32                   StartingAddress;
  UINT32                   EndingAddress;
  UINT16                   MemoryArrayHandle;
  UINT8                    PartitionWidth;
  UINT64                   ExtendedStartingAddress;
  UINT64                   ExtendedEndingAddress;
  UINT8                    EndNull1;
  UINT8                    EndNull2;
} SMBIOS_MEMORY_ARRAY_MAPPED_ADDRESS;

#pragma pack()

extern SMBIOS_MEMORY_ARRAY_INFO *const pSMBIOS_MEMORY_ARRAY_INFO;
extern SMBIOS_MEMORY_DEVICE_INFO *const pSMBIOS_MEMORY_DEVICE_INFO;
extern SMBIOS_MEMORY_ARRAY_MAPPED_ADDRESS *const pSMBIOS_MEMORY_ARRAY_MAPPED_ADDRESS;

#endif
