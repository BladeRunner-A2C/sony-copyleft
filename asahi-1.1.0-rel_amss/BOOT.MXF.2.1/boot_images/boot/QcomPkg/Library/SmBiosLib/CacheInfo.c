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

#include <Uefi.h>

#include <Protocol/Smbios.h>

#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <SmbiosCfgInfo.h>
#include <Protocol/EFIChipInfo.h>
#include "SmbiosLibTarget.h"
#include "CacheInfo.h"

UINTN  CacheInfoL1InstStringNum = 1;
CHAR8*  CacheInfoL1InstString = "L1 Instruction Cache";

UINTN  CacheInfoL1DataStringNum = 1;
CHAR8*  CacheInfoL1DataString = "L1 Data Cache";

UINTN  CacheInfoL2StringNum = 1;
CHAR8*  CacheInfoL2String = "L2 Cache";

UINTN  CacheInfoL3StringNum = 1;
CHAR8*  CacheInfoL3String = "L3 Cache";

EFI_SMBIOS_HANDLE       L1InstCacheHandle = SMBIOS_HANDLE_PI_RESERVED;
EFI_SMBIOS_HANDLE       L1DataCacheHandle = SMBIOS_HANDLE_PI_RESERVED;
EFI_SMBIOS_HANDLE       L2CacheHandle = SMBIOS_HANDLE_PI_RESERVED;
EFI_SMBIOS_HANDLE       L3CacheHandle = SMBIOS_HANDLE_PI_RESERVED;


/**
  Add L1 Instruction cache Info /Type 7 table to Smbios table List

  @param  SmbiosTableNode   Pointer to the Smbios Table list
                            node

  @retval EFI_SUCCESS    Initialization success

**/
EFI_STATUS L1InstCacheInfoTableInit( SMBIOS_TABLE_NODE     *SmbiosTableNode)
{
  EFI_STATUS       Status = EFI_INVALID_PARAMETER ;

  if( SmbiosTableNode == NULL)
    return Status;

  // Add type 0 /Bios info table.
  SmbiosTableNode->TablePtr= (VOID *) pSmbios_L1InstructionCacheInfo ;
  SmbiosTableNode->TableType = SMBIOS_L1_INSTN_CACHE_TABLE;
  Status = EFI_SUCCESS;

  return Status;
}

/**
  Add L1 Data cache Info /Type 7 table to Smbios table List

  @param  SmbiosTableNode   Pointer to the Smbios Table list
                            node

  @retval EFI_SUCCESS    Initialization success

**/
EFI_STATUS L1DataCacheInfoTableInit( SMBIOS_TABLE_NODE     *SmbiosTableNode)
{
  EFI_STATUS       Status = EFI_INVALID_PARAMETER ;
  
  if( SmbiosTableNode == NULL)
    return Status;

  // Add type 0 /Bios info table.
  SmbiosTableNode->TablePtr= (VOID *) pSmbios_L1DataCacheInfo ;
  SmbiosTableNode->TableType = SMBIOS_L1_DATA_CACHE_TABLE;
  Status = EFI_SUCCESS;

  return Status;
}

/**
  Add L2 cache Info /Type 7 table to Smbios table List

  @param  SmbiosTableNode   Pointer to the Smbios Table list
                            node

  @retval EFI_SUCCESS    Initialization success

**/
EFI_STATUS L2CacheInfoTableInit( SMBIOS_TABLE_NODE     *SmbiosTableNode)
{
  EFI_STATUS       Status = EFI_INVALID_PARAMETER ;

  if( SmbiosTableNode == NULL)
    return Status;

  // Add type 0 /Bios info table.
  SmbiosTableNode->TablePtr= (VOID *) pSmbios_L2CacheInfo;
  SmbiosTableNode->TableType = SMBIOS_L2_CACHE_TABLE;
  Status = EFI_SUCCESS;

  return Status;
}

/**
  Add L3 cache Info /Type 7 table to Smbios table List

  @param  SmbiosTableNode   Pointer to the Smbios Table list
                            node

  @retval EFI_SUCCESS    Initialization success

**/
EFI_STATUS L3CacheInfoTableInit( SMBIOS_TABLE_NODE     *SmbiosTableNode)
{
  EFI_STATUS       Status = EFI_INVALID_PARAMETER ;

  if( SmbiosTableNode == NULL)
    return Status;

  // Add type 7 /Bios info table.
  SmbiosTableNode->TablePtr= (VOID *) pSmbios_L3CacheInfo;
  SmbiosTableNode->TableType = SMBIOS_L3_CACHE_TABLE;
  Status = EFI_SUCCESS;

  return Status;
}

EFI_STATUS UpdateCacheInfoTable (EFI_SMBIOS_PROTOCOL     *Smbios)
{
  EFI_STATUS              Status;
  
  EFI_CHIPINFO_PROTOCOL     *pEfiChipInfoProtocol = NULL;
  EFIChipInfoFamilyType      chipFamily = EFICHIPINFO_FAMILY_UNKNOWN;
   
  // locate chip info protocol
  Status = gBS->LocateProtocol(&gEfiChipInfoProtocolGuid,NULL, (VOID**) &pEfiChipInfoProtocol);
  if (EFI_ERROR(Status) || (pEfiChipInfoProtocol == NULL))
  {
      DEBUG((EFI_D_WARN,"gEfiChipInfoProtocolGuid protocol failed\r\n" ));
      return Status;
  }

  Status = pEfiChipInfoProtocol->GetChipFamily(pEfiChipInfoProtocol,&chipFamily);
  if((Status != EFI_SUCCESS) || (chipFamily == EFICHIPINFO_FAMILY_UNKNOWN))
  {
    DEBUG((EFI_D_WARN,"GetChipFamily failed\r\n" ));
    return Status;
  } 

  //Add the L1 Instruction Cache Info
  
  pSmbios_L1InstructionCacheInfo->MaxSize = NumOfFunctionalCores * L1InstructionCacheSize;
  pSmbios_L1InstructionCacheInfo->InstalledSize =  NumOfFunctionalCores * L1InstructionCacheSize;
  
  Status = Smbios->Add(
    Smbios,
    NULL,
    &L1InstCacheHandle,
    (EFI_SMBIOS_TABLE_HEADER*) pSmbios_L1InstructionCacheInfo
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }

  // Store table handle and Update strings if any.
  UpdateTableData(
    Smbios,
    L1InstCacheHandle,
    SMBIOS_L1_INSTN_CACHE_TABLE
    );

  Status = Smbios->UpdateString(
    Smbios,
    &L1InstCacheHandle,
    &CacheInfoL1InstStringNum,
    CacheInfoL1InstString
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }

  //Add the L1 Data Cache Info
  
  pSmbios_L1DataCacheInfo->MaxSize = NumOfFunctionalCores  * L1DataCacheSize;
  pSmbios_L1DataCacheInfo->InstalledSize =  NumOfFunctionalCores  * L1DataCacheSize;  
  Status = Smbios->Add(
    Smbios,
    NULL,
    &L1DataCacheHandle,
    (EFI_SMBIOS_TABLE_HEADER*) pSmbios_L1DataCacheInfo
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }

  // Store table handle and Update strings if any.
  UpdateTableData(
    Smbios,
    L1DataCacheHandle,
    SMBIOS_L1_DATA_CACHE_TABLE
    );

  Status = Smbios->UpdateString(
    Smbios,
    &L1DataCacheHandle,
    &CacheInfoL1DataStringNum,
    CacheInfoL1DataString
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }


  //Add the L2 Cache Info
 
  pSmbios_L2CacheInfo->MaxSize = SET_CACHE_SIZE_GRANULARITY + (NumOfFunctionalCluster  * L2CacheSize);
  pSmbios_L2CacheInfo->InstalledSize =  SET_CACHE_SIZE_GRANULARITY + (NumOfFunctionalCluster  * L2CacheSize); 
  
  Status = Smbios->Add(
    Smbios,
    NULL,
    &L2CacheHandle,
    (EFI_SMBIOS_TABLE_HEADER*) pSmbios_L2CacheInfo
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }

  // Store table handle and Update strings if any.
  UpdateTableData(
    Smbios,
    L2CacheHandle,
    SMBIOS_L2_CACHE_TABLE
    );

  Status =  Smbios->UpdateString(
    Smbios,
    &L2CacheHandle,
    &CacheInfoL2StringNum,
    CacheInfoL2String
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }
  
  if (chipFamily != EFICHIPINFO_FAMILY_HAMOA)
  {
    //Add the L3 Cache Info
    Status = Smbios->Add(
      Smbios,
      NULL,
      &L3CacheHandle,
      (EFI_SMBIOS_TABLE_HEADER*)pSmbios_L3CacheInfo
      );
    if(Status != EFI_SUCCESS)
    {
      return Status;
    }
    
    // Store table handle and Update strings if any.
    UpdateTableData(
      Smbios,
      L3CacheHandle,
      SMBIOS_L3_CACHE_TABLE
      );
    
    Status =  Smbios->UpdateString(
      Smbios,
      &L3CacheHandle,
      &CacheInfoL3StringNum,
      CacheInfoL3String
      );
  }

  return Status;
}


