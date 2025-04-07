/** @file
  Updates the SMBios table with the cache info structure.

  Copyright (c) 2010-2013, 2018, 2020, 2022 Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/18/22   dnkg    SupportedSRAMType and CurrentSRAMType Bug Fix
 06/13/22   dnkg    Fix Indentation issues.
 05/28/20   kbarad  Added SMBIOS_HANDLE_PI_RESERVED as default handle
 01/16/18   ltg     Port fixes from 1.2.2 for cache sizes and other attributes
 01/30/13   vk      Fix warning
 03/23/12   kpa     Add support for config file based smbios table init
 07/20/11   yg      Converted to Lib
 05/25/11   niting  Initial revision

=============================================================================*/

#ifndef __CACHE_INFO_H__
#define __CACHE_INFO_H__

#include <Uefi.h>
#include <Protocol/Smbios.h>

#pragma pack(1)

typedef struct _SMBIOS_CACHE_INFO
{
  EFI_SMBIOS_TABLE_HEADER  Header;
  UINT8                    SocketDesignationStringNum;
  UINT16                   CacheConfiguration;
  UINT16                   MaxSize;
  UINT16                   InstalledSize;
  UINT16                   SupportedSRAMType;
  UINT16                   CurrentSRAMType;
  UINT8                    CacheSpeed;
  UINT8                    ErrorCorrectionType;
  UINT8                    SystemCacheType;
  UINT8                    Associativity;

  UINT8                    String1[2];
  UINT8                    EndNull;
} SMBIOS_CACHE_INFO;

typedef struct _CACHE_STRING_STRUCTURE{
  UINT8                    String1[2];
  UINT8                    EndNull;
} CACHE_STRING_STRUCTURE;

#pragma pack()

extern SMBIOS_CACHE_INFO *const pSmbios_L1InstructionCacheInfo;
extern SMBIOS_CACHE_INFO *const pSmbios_L1DataCacheInfo;
extern SMBIOS_CACHE_INFO *const pSmbios_L2CacheInfo;
extern SMBIOS_CACHE_INFO *const pSmbios_L3CacheInfo;

#endif


