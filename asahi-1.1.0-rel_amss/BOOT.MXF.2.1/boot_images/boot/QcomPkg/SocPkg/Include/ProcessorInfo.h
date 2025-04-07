/** @file
  Updates the SMBios table with the processor info structure.

  Copyright (c) 2010-2013, 2018-2022 Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/15/22   dnkg    Fix Indentation Issues
 03/11/21   kbarad  Added QFPROMChipId in to table
 05/28/20   kbarad  Added SMBIOS_HANDLE_PI_RESERVED as default handle
 02/24/20   kbarad  Add 5th and 6th string support for SMBIOS_PROCESSOR_INFO table
 12/02/19   rc      Updated processor version string building
 04/10/19   vb      Add support for reading APQ feature_id fuse information
 01/20/19   vb      Add support for reading feature_id fuse information
 08/02/18   ltg     Add max speed to processor version string
 01/16/18   ltg     Port changes from 2.2 to comply with v3.0
 11/01/13   vk      Fix 64 bit compiler warnings
 04/10/13   niting  Updated NumCpus to read from cfg file
 01/30/13   vk      Fix warning
 04/13/12   jz      Fixed ProcessorInfoVersionString
 03/23/12   kpa     Add support for config file based smbios table init
 07/20/11   yg      Added dynamic Processor info
 06/22/11   cgross  Added MpPark support
 05/25/11   niting  Initial revision

=============================================================================*/

#ifndef __PROCERSSOR_INFO_H__
#define __PROCERSSOR_INFO_H__

#include <Uefi.h>
#include <Protocol/Smbios.h>

#pragma pack(1)

typedef struct _SMBIOS_PROCESSOR_INFO
{
  EFI_SMBIOS_TABLE_HEADER  Header;
  UINT8                    SocketDesignationStringNum;
  UINT8                    ProcessorType;
  UINT8                    ProcessorFamily;
  UINT8                    ProcessorManufacturerStringNum;
  UINT64                   ProcessorID;
  UINT8                    ProcessorVersionStringNum;
  UINT8                    Voltage;
  UINT16                   ExternalClock;
  UINT16                   MaxSpeed;
  UINT16                   CurrentSpeed;
  UINT8                    Status;
  UINT8                    ProcessorUpgrade;
  UINT16                   L1CacheHandle;
  UINT16                   L2CacheHandle;
  UINT16                   L3CacheHandle;
  UINT8                    SerialNumberStringNum;
  UINT8                    AssetTagStringNum;
  UINT8                    PartNumberStringNum;
  UINT8                    CoreCount;
  UINT8                    CoreEnabled;
  UINT8                    ThreadCount;
  UINT16                   ProcessorCharacteristics;
  UINT16                   ProcessorFamily2;
  UINT16                   CoreCount2;
  UINT16                   CoreEnabled2;
  UINT16                   ThreadCount2;

  UINT8                    String1[2];
  UINT8                    String2[2];
  UINT8                    String3[2];
  UINT8                    String4[2];
  UINT8                    String5[2];
  UINT8                    String6[2];
  UINT8                    EndNull;
} SMBIOS_PROCESSOR_INFO;

typedef struct _PROCESSOR_STRING_STRUCTURE{
  UINT8                    String1[2];
  UINT8                    String2[2];
  UINT8                    String3[2];
  UINT8                    String4[2];
  UINT8                    String5[2];
  UINT8                    String6[2];
  UINT8                    EndNull;
} PROCESSOR_STRING_STRUCTURE;

#pragma pack()

extern SMBIOS_PROCESSOR_INFO *const pSMBIOS_PROCESSOR_INFO;

#endif
