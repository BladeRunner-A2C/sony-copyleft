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

#include <Uefi.h>

#include <Protocol/Smbios.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PrintLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIChipInfo.h>
#include "SmbiosCfgInfo.h"
#include <Library/QcomLib.h>
#include <Library/UefiCfgLib.h>
#include "SmbiosLibTarget.h"
#include "ProcessorInfo.h"

#define MAX_SPEED_TEMPLATE " @ x.xx GHz"

UINTN  ProcessorInfoSocketInfoStringNum = 1;
CHAR8* ProcessorInfoSocketInfoString = (CHAR8*)PcdGetPtr(PcdProcessorInfoSockInfoStr);

UINTN  ProcessorManufacturerStringNum = 2;
CHAR8* ProcessorManufacturerString = "Qualcomm Technologies Inc";

UINTN  ProcessorVersionStringNum = 3;
CHAR8* ProcessorVersionString = (CHAR8*)PcdGetPtr(PcdProcessorInfoVersionStr);

UINTN  ProcessorInfoPartNumberStringNum = 4;
CHAR8  ProcessorInfoPartNumberString[EFICHIPINFO_MAX_ID_LENGTH];

UINTN  PartSerialNumberStringNum = 5;
CHAR8  PartSerialNumberString[EFICHIPINFO_MAX_ID_LENGTH];

extern EFI_SMBIOS_HANDLE       L1InstCacheHandle;
extern EFI_SMBIOS_HANDLE       L1DataCacheHandle;
extern EFI_SMBIOS_HANDLE       L2CacheHandle;
extern EFI_SMBIOS_HANDLE       L3CacheHandle;
extern UINT32                  NumOfFunctionalCores;

/**
  Add Processor Info /Type 4 table to Smbios table List

  @param  SmbiosTableNode   Pointer to the Smbios Table list
                            node

  @retval EFI_SUCCESS    Initialization success


**/
EFI_STATUS ProcessorInfoTableInit( SMBIOS_TABLE_NODE     *SmbiosTableNode)
{
  EFI_STATUS       Status = EFI_INVALID_PARAMETER ;

  if( SmbiosTableNode == NULL)
    return Status;
  
  // Init functional cluster and Cores
  InitFunctionalClusterCores();

  // Add type 4 /Processor info table.
  SmbiosTableNode->TablePtr= (VOID *) pSMBIOS_PROCESSOR_INFO;
  SmbiosTableNode->TableType = EFI_SMBIOS_TYPE_PROCESSOR_INFORMATION;
  Status = EFI_SUCCESS;

  return Status;
}

EFI_STATUS UpdateProcessorInfoTable (EFI_SMBIOS_PROTOCOL *Smbios)
{
  EFI_STATUS                Status;
  EFI_SMBIOS_HANDLE         ProcessorHandle = SMBIOS_HANDLE_PI_RESERVED;
  EFI_CHIPINFO_PROTOCOL     *mChipInfoProtocol;
  EFIChipInfoSerialNumType  deviceSerialNumber = 0;
  UINT16                    maxSpeedGHZHigh = 0;
  UINT16                    maxSpeedGHZLow = 0;
  UINTN                     maxSpeedCharCount = 0;
  CHAR8                     maxSpeedString[AsciiStrSize(MAX_SPEED_TEMPLATE)];
  UINTN                     procVersionStringLen = 0;
  UINT16                    maxSpeedGHZLowRem = 0;
  EFIChipInfoQFPROMChipIdType chipIDinfo = 0;
  
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

  Status = gBS->LocateProtocol(
    &gEfiChipInfoProtocolGuid,
    NULL,
    (VOID **) &mChipInfoProtocol
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }

  if (NumOfFunctionalCores == 0)
  {
    DEBUG ((EFI_D_ERROR, "NumCpus not found\r\n"));
  }
  else
  {
    pSMBIOS_PROCESSOR_INFO->CoreCount = NumOfFunctionalCores;
    pSMBIOS_PROCESSOR_INFO->CoreEnabled = NumOfFunctionalCores;
    pSMBIOS_PROCESSOR_INFO->ThreadCount = NumOfFunctionalCores;
  }
  if(L1InstCacheHandle != SMBIOS_HANDLE_PI_RESERVED)
  {
    pSMBIOS_PROCESSOR_INFO->L1CacheHandle = L1InstCacheHandle;
  }
  if(L2CacheHandle != SMBIOS_HANDLE_PI_RESERVED)
  {
    pSMBIOS_PROCESSOR_INFO->L2CacheHandle = L2CacheHandle;
  }
  if(L3CacheHandle != SMBIOS_HANDLE_PI_RESERVED)
  {
    pSMBIOS_PROCESSOR_INFO->L3CacheHandle = L3CacheHandle;
  }
    
  Status = smbiosGetMaxSpeed(&(pSMBIOS_PROCESSOR_INFO->MaxSpeed));
  if (Status == EFI_SUCCESS)
  {
    maxSpeedGHZHigh = (pSMBIOS_PROCESSOR_INFO->MaxSpeed) / 1000;
    maxSpeedGHZLow = (pSMBIOS_PROCESSOR_INFO->MaxSpeed) % 1000;
    maxSpeedGHZLowRem = (pSMBIOS_PROCESSOR_INFO->MaxSpeed) % 10;

    if (maxSpeedGHZLowRem < 5)
    {
      maxSpeedGHZLow = maxSpeedGHZLow / 10;
    }
    else
    {
      maxSpeedGHZHigh = (pSMBIOS_PROCESSOR_INFO->MaxSpeed / 10) + 1;
      maxSpeedGHZLow = maxSpeedGHZHigh % 100;
      maxSpeedGHZHigh = maxSpeedGHZHigh / 100;
    }
    maxSpeedCharCount = AsciiSPrint(
      maxSpeedString,
      sizeof(maxSpeedString),
      " @ %d.%d GHz",
      maxSpeedGHZHigh,
      maxSpeedGHZLow
      );
    procVersionStringLen = AsciiStrSize((CHAR8*)PcdGetPtr(PcdProcessorInfoVersionStr));
    ProcessorVersionString = (CHAR8*)AllocatePool(procVersionStringLen + maxSpeedCharCount);
    if (ProcessorVersionString == NULL)
    {
      return EFI_OUT_OF_RESOURCES;
    }

    Status = smbiosGetProcVersionStr(ProcessorVersionString);
    if (Status != EFI_SUCCESS)
    {
      return Status;
    }

    Status = AsciiStrCatS(
      ProcessorVersionString,
      procVersionStringLen + maxSpeedCharCount,
      maxSpeedString
      );
    if (Status != EFI_SUCCESS)
    {
      return Status;
    }
  }
  else
  {
    Status = smbiosGetProcVersionStr(ProcessorVersionString);
    if (Status != EFI_SUCCESS)
    {
      return Status;
    }
  }
  //Add the processor Info
  Status = Smbios->Add(
    Smbios,
    NULL,
    &ProcessorHandle,
    (EFI_SMBIOS_TABLE_HEADER*)pSMBIOS_PROCESSOR_INFO
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }

  // Store table handle and Update strings if any.
  UpdateTableData(Smbios, ProcessorHandle, EFI_SMBIOS_TYPE_PROCESSOR_INFORMATION );

  Status = Smbios->UpdateString(
    Smbios,
    &ProcessorHandle,
    &ProcessorInfoSocketInfoStringNum,
    ProcessorInfoSocketInfoString
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }

  Status = Smbios->UpdateString(
    Smbios,
    &ProcessorHandle,
    &ProcessorManufacturerStringNum,
    ProcessorManufacturerString
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }

  Status = Smbios->UpdateString(
    Smbios,
    &ProcessorHandle,
    &ProcessorVersionStringNum,
    ProcessorVersionString
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }

  Status = mChipInfoProtocol->GetQFPROMChipId(mChipInfoProtocol,&chipIDinfo);
  DEBUG((EFI_D_INFO," chipIDinfo: %x\r\n", chipIDinfo ));
  if(Status != EFI_SUCCESS)
  {
    DEBUG((EFI_D_WARN," GetQFPROMChipId failed: %r\r\n", Status ));
    return Status;
  }
  AsciiSPrint(
    ProcessorInfoPartNumberString,
    sizeof(ProcessorInfoPartNumberString),
    "%X",
    chipIDinfo
    );

  Status = Smbios->UpdateString(
    Smbios,
    &ProcessorHandle,
    &ProcessorInfoPartNumberStringNum,
    ProcessorInfoPartNumberString
    );
  if (Status != EFI_SUCCESS)
  {
    return Status;
  }

  // Read serial number of the device
  Status = mChipInfoProtocol->GetSerialNumber(
    mChipInfoProtocol,
    &deviceSerialNumber
    );
  if (Status != EFI_SUCCESS)
  {
    return Status;
  }

  // Populate serial number string with the serial number of the device
  AsciiSPrint(
    PartSerialNumberString, 
    sizeof(PartSerialNumberString), 
    "%Lx", 
    deviceSerialNumber
    );

  // Update serial number string of type 4 record with the serial number string
  Status = Smbios->UpdateString(
    Smbios,
    &ProcessorHandle,
    &PartSerialNumberStringNum,
    PartSerialNumberString
    );
  if (Status != EFI_SUCCESS)
  {
    return Status;
  }
  return Status;
}
