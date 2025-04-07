/** @file
  Updates the SMBios table with the system info structure.

  Copyright (c) 2010-2013, 2016, 2020, 2022 Qualcomm Technologies Inc. All rights reserved.

**/
/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/13/22   dnkg    fix Indentation issues
 05/28/20   kbarad  Added SMBIOS_HANDLE_PI_RESERVED as default handle
 12/07/16   lg      Remove duplicated code and call GetUUID() in SystemInfoTableInit()
 09/13/16   jt      Change SdccCardInfo to MemCardInfo
 01/30/13   vk      Fix warning
 08/17/12   yg      Allow Cfg override UUID in SystemInfo
 06/06/12   yg      Cfg data overrides the code generated data for SystemInfo
 04/26/12   yg      Populate appropriate SMBios values
 03/23/12   kpa     Add support for config file based smbios table init
 07/20/11   yg      Added UUID based on eMMC info
 05/25/11   niting  Initial revision
=============================================================================*/
#ifndef __SYSTEM_INFO_H__
#define __SYSTEM_INFO_H__

#include <Uefi.h>
#include <Protocol/Smbios.h>

//------------------------------------------------------------------------------
// Data structure definitions (#data)
//------------------------------------------------------------------------------

#pragma pack(1)

typedef struct _SMBIOS_SYSTEM_INFO
{
  EFI_SMBIOS_TABLE_HEADER  Header;
  UINT8                    ManufacturerStringNum;
  UINT8                    ProductNameStringNum;
  UINT8                    VersionStringNum;
  UINT8                    SerialNumberStringNum;
  UINT8                    UUID[16];
  UINT8                    WakeUpType;
  UINT8                    SkuNumberStringNum;
  UINT8                    FamilyStringNum;
  UINT8                    String1[2];
  UINT8                    String2[2];
  UINT8                    String3[2];
  UINT8                    String4[2];
  UINT8                    String5[2];
  UINT8                    String6[2];
  UINT8                    EndNull;
} SMBIOS_SYSTEM_INFO;

typedef struct _SYSTEM_STRING_STRUCTURE{
  UINT8                    String1[2];
  UINT8                    String2[2];
  UINT8                    String3[2];
  UINT8                    String4[2];
  UINT8                    String5[2];
  UINT8                    String6[2];
  UINT8                    EndNull;
} SYSTEM_STRING_STRUCTURE;

#pragma pack()

extern SMBIOS_SYSTEM_INFO *const pSMBIOS_SYSTEM_INFO;

#endif