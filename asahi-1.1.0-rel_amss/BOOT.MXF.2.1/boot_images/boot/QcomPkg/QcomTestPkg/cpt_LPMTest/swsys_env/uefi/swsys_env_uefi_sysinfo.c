/*
===========================================================================
*/
/**
  @file swsys_env_uefi_sysinfo.c

*/
/*
  ====================================================================

  Copyright (c) 2023 Qualcomm Technologies, Inc.  All Rights Reserved
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  when       who     what, where, why
  --------   ---     -------------------------------------------------
  10/24/17  IH      Initial revision.

  ====================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/QcomLib.h>
//#include "DALSys.h"
//#include "DALStdDef.h"
#include <Protocol/EFIChipInfo.h>
#include <Protocol/EFIPlatformInfo.h>
#include "../swsys_env/swsys_env.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/
/* PROTOCOL HANDLES */
EFI_CHIPINFO_PROTOCOL      *ChipInfoProtocol = NULL;
EFI_PLATFORMINFO_PROTOCOL  *PlatformInfoProtocol = NULL;

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/
bool swsys_init_sysinfo_uefi()
{
  /* Get Protocol handles */
  gBS->LocateProtocol (&gEfiChipInfoProtocolGuid, NULL, (VOID **) &ChipInfoProtocol);
  gBS->LocateProtocol ( &gEfiPlatformInfoProtocolGuid, NULL, (VOID **) &PlatformInfoProtocol);

  if(!ChipInfoProtocol || !PlatformInfoProtocol) {
    return false;
  }
  return true;
}

bool swsys_get_serial_number_uefi(uint64_t *serial_number)
{
    EFI_STATUS eResult = EFI_UNSUPPORTED;

    EFIChipInfoSerialNumType SerialNum;

    if(ChipInfoProtocol && serial_number) {
      eResult = ChipInfoProtocol->GetSerialNumber(ChipInfoProtocol, &SerialNum);
    }
    if (eResult == EFI_SUCCESS) {
      *serial_number = SerialNum;
      return true;
    }
    return false;
}


bool swsys_get_chip_id_uefi(char* chip_id, uint32_t size)
{
    EFI_STATUS eResult = EFI_UNSUPPORTED;

    if(ChipInfoProtocol && chip_id && size > 0) {
        eResult = ChipInfoProtocol->GetChipIdString(ChipInfoProtocol, chip_id, size);
    }
    if (eResult  == EFI_SUCCESS) {
      return true;
    }
    return false;
}

bool swsys_get_chip_version_uefi(uint32_t *chip_version)
{
    EFI_STATUS eResult = EFI_UNSUPPORTED;

    if(ChipInfoProtocol && chip_version) {
        eResult = ChipInfoProtocol->GetChipId(ChipInfoProtocol, (EFIChipInfoVersionType *)chip_version);
    }
    
    if (eResult  == EFI_SUCCESS) {
      return true;
    }
    return false;
}

bool swsys_get_processor_name_uefi(char *processor_name, uint32_t size)
{
  EFI_STATUS eResult = EFI_UNSUPPORTED;
  if(processor_name && size > 0) {
    eResult = GetProcessorName(processor_name, (UINTN)size);
  }
  if (eResult  == EFI_SUCCESS) {
      return true;
  }
  return false;
}

bool swsys_get_device_id_uefi(uint8_t *buf, uint32_t size)
{
  EFI_STATUS eResult = EFI_UNSUPPORTED;

  if ( buf && size > 0) {
    eResult = GetUUID((uint8_t*)&buf[0], size);
  }
  if (eResult  == EFI_SUCCESS) {
      return true;
  }
  return false;
}

