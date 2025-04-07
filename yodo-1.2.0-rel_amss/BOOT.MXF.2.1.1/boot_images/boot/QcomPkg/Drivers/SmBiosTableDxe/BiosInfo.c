/** @file
  Implements the BIOS Info Table for SMBios.

  Copyright (c) 2010-2013, 2015, 2017, 2019-2020, 2022 Qualcomm Technologies Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/11/22   dnkg    Added correct values for BiosRomSize and ExtendedBiosRomSize
 06/15/22   dnkg    Fix Indentation issues
 05/28/20   kbarad  Added SMBIOS_HANDLE_PI_RESERVED as default handle
 05/06/20   vb      Port changes from boot 3.0.1 to fix KW error
 03/25/19   vb      Fix KW error
 05/05/17   ltg     Fix version update
 09/30/15   bh      Update firmware versioning
 01/15/15   bh      Change UINT32 to UINTN
 01/30/12   vk      Fixed KW warning
 07/23/12   jz      Fixed version display when build version number is supplied
 07/09/12   yg      Fixed warning
 04/10/12   jz      Fixed release date format and klockwork warnings
 03/23/12   kpa     Add support for config file based smbios table init
 01/27/12   yg      Added Another char for year in version
 12/20/11   niting  Added build version string to SmBios
 09/13/11   jz      Added support for gST->FirmwareRevision (UINT32)
 09/01/11   jz      Fixed the handling of date
 08/31/11   jz      Update version with date
 07/28/11   yg      Added null termination
 07/15/11   yg      Added date information
 05/25/11   niting  Initial revision

=============================================================================*/

#include <Uefi.h>

#include <Protocol/Smbios.h>

#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PcdLib.h>
#include <Library/BaseLib.h>
#include <Library/QcomLib.h>
#include <Library/HobLib.h>

#include "BuildVersion.h"
#include <SmbiosCfgInfo.h>

#define MAX_VERSION_STR_LENGTH 128

#define MAX_RELEASE_DATE_STR_LENGTH 11

#pragma pack(1)
typedef struct _SMBIOS_BIOS_INFO
{
  EFI_SMBIOS_TABLE_HEADER  Header;
  UINT8                    VendorStringNum;
  UINT8                    BiosStringNum;
  UINT16                   BiosAddress;
  UINT8                    BiosReleaseDateNum;
  UINT8                    BiosRomSize;
  UINT64                   BiosCharacteristics;
  UINT8                    BiosCharacteristicsExtension1;
  UINT8                    BiosCharacteristicsExtension2;
  UINT8                    SystemBiosMajorRevision;
  UINT8                    SystemBiosMinorRevision;
  UINT8                    EmbeddedControllerMajorRevision;
  UINT8                    EmbeddedControllerMinorRevision;
  // Smbios spec 3.1+
  UINT16                   ExtendedBiosRomSize;

  UINT8                    String1[2];
  UINT8                    String2[2];
  UINT8                    String3[2];
  UINT8                    EndNull;
}SMBIOS_BIOS_INFO;

typedef struct _BIOS_STRING_STRUCTURE{
  UINT8                    String1[2];
  UINT8                    String2[2];
  UINT8                    String3[2];
  UINT8                    EndNull;
}BIOS_STRING_STRUCTURE;


//Bios information
SMBIOS_BIOS_INFO SmBiosBootInfo =
{
  {
    EFI_SMBIOS_TYPE_BIOS_INFORMATION,
    sizeof(SMBIOS_BIOS_INFO) - sizeof(BIOS_STRING_STRUCTURE),
    0         //handle
  },
  1,          // VendorStringNum
  2,          // BiosStringNum
  0x00000,    // Bios Address Segment (doesn't apply to us)
  3,          // BiosReleaseDateNum
  0xFF,       // BiosRomSize (16MB) see ExtendedBiosRomSize for actual value
  0,          // BiosCharacteristics
  1,          // Extension1 - bit 0 - supports ACPI
  0x06,       // Extension2 - bit 3 UEFI, bit 2, this is valid
  0xFF,       // SystemBiosMajorRevision;
  0xFF,       // SystemBiosMinorRevision;
  0xFF,       // EmbeddedControllerMajorRevision;
  0xFF,       // EmbeddedControllerMinorRevision;
  //Smbios spec 3.1+
  0x0040,     //ExtendedBiosRomSize (64MB);

  "1",
  "2",
  "3",
  0
};


#pragma pack()

UINTN  BiosInfoVendorNameStringNum = 1;
UINTN  BiosInfoVersionStringNum = 2;
UINTN  BiosInfoReleaseDateStringNum = 3;

CHAR8 *BuildVersionNum = UEFI_BUILD_VERSION;

extern EFI_GUID gQcomFwVersionStringGuid;
extern EFI_GUID gQcomRelDateStringGuid;

/**
  Add Bios Info /Type 0 table to Smbios table List

  @param  SmbiosTableNode   Pointer to the Smbios Table list
                            node

  @retval EFI_SUCCESS    Initialization success

**/
EFI_STATUS BiosInfoTableInit( SMBIOS_TABLE_NODE     *SmbiosTableNode)
{
  EFI_STATUS       Status = EFI_INVALID_PARAMETER ;

  if(SmbiosTableNode == NULL)
  {
    return Status;
  }

  // Add type 0 /Bios info table.
  SmbiosTableNode->TablePtr= (VOID *) &SmBiosBootInfo ;
  SmbiosTableNode->TableType = EFI_SMBIOS_TYPE_BIOS_INFORMATION;
  Status = EFI_SUCCESS;

  return Status;
}

EFI_STATUS UpdateBiosInfoTable( EFI_SMBIOS_PROTOCOL     *Smbios)
{
  EFI_STATUS              Status;
  EFI_SMBIOS_HANDLE       BiosHandle = SMBIOS_HANDLE_PI_RESERVED;
  EFI_HOB_GUID_TYPE       *GuidHob;
  CHAR8 AsciiString[MAX_VERSION_STR_LENGTH];
  UINTN i = 0;
  CHAR16 *UnicodeStringPCD = NULL;
  CHAR8 *RelDateString, *FwVerStr = NULL;  /* format: mm/dd/yyyy */
  UINTN Length = 0;

  Status = Smbios->Add(
    Smbios,
    NULL,
    &BiosHandle,
    (EFI_SMBIOS_TABLE_HEADER*)&SmBiosBootInfo
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }

  // Store table handle and Update strings if any.
  UpdateTableData(
    Smbios,
    BiosHandle,
    EFI_SMBIOS_TYPE_BIOS_INFORMATION
    );

  //convert vendor name to ASCII
  UnicodeStringPCD = FixedPcdGetPtr (PcdFirmwareVendor);

  if(UnicodeStringPCD != NULL)
  {
    Length = StrLen(UnicodeStringPCD);
    if((Length > 0) && (Length < MAX_VERSION_STR_LENGTH))
    {
      while((i <= Length) && (*UnicodeStringPCD != 0) && (i < (MAX_VERSION_STR_LENGTH - 1)))
      {
        AsciiString[i] = (CHAR8)*UnicodeStringPCD;
        UnicodeStringPCD++;
        i++;
      }
    }
  }
  AsciiString[i] = 0;

  Status = Smbios->UpdateString(
    Smbios,
    &BiosHandle,
    &BiosInfoVendorNameStringNum,
    AsciiString
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }

  //Get FW version string from HOB
  GuidHob = GetFirstGuidHob(&gQcomFwVersionStringGuid);
  if (GuidHob == NULL)
  {
    DEBUG((EFI_D_INFO, "FW version string HOB not found\n"));
    return EFI_NOT_FOUND;
  }

  FwVerStr = GET_GUID_HOB_DATA(GuidHob);
  if (FwVerStr == NULL)
  {
    DEBUG((EFI_D_INFO, "Release date string not found in HOB\n"));
    return EFI_NOT_FOUND;
  }

  Status = Smbios->UpdateString(
    Smbios,
    &BiosHandle,
    &BiosInfoVersionStringNum,
    FwVerStr
    );
  if(Status != EFI_SUCCESS)
  {
    return Status;
  }

  //Get release date string from HOB
  GuidHob = GetFirstGuidHob(&gQcomRelDateStringGuid);
  if (GuidHob == NULL)
  {
    DEBUG((EFI_D_INFO, "Release date string HOB not found\n"));
    return EFI_NOT_FOUND;
  }

  RelDateString = GET_GUID_HOB_DATA(GuidHob);
  if (RelDateString == NULL)
  {
    DEBUG((EFI_D_INFO, "Release date string not found in HOB\n"));
    return EFI_NOT_FOUND;
  }

  // Format of date string should be "mm/dd/yyyy"
  return Smbios->UpdateString(
    Smbios,
    &BiosHandle,
    &BiosInfoReleaseDateStringNum,
    RelDateString
    );
}
