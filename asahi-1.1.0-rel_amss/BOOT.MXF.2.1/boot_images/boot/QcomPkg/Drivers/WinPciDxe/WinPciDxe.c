/** @file

  Copyright (c) 2022, Qualcomm Technologies, Inc. All rights reserved.

  Wireless Connectivity power Driver 

**/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who         what, where, why
--------   ---         ----------------------------------------------------------
11/07/22   skanni    initial edit
==============================================================================*/

/*==============================================================================

                       INCLUDE FILES FOR THIS MODULE

==============================================================================*/

#include <Uefi.h>
#include <WinPciBsp.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>


/*==============================================================================

                         DEFINES FOR THIS MODULE

==============================================================================*/

/*==============================================================================

                     EXTERNAL DEFINES FOR THIS MODULE

==============================================================================*/


/*==============================================================================

                      PROTOTYPES USED IN THIS MODULE

==============================================================================*/


/*==============================================================================

                     GLOBAL VARIABLES FOR THIS MODULE

==============================================================================*/


/*==============================================================================

                             API IMPLEMENTATION

==============================================================================*/


EFI_STATUS
EFIAPI
WinPciEntryPoint (IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS Status = EFI_SUCCESS;

  Status = WinPciInit();
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "%a: Error powering up WinPci, Status=0x%x\r\n", __func__, Status));
  }
  else{
    DEBUG((EFI_D_INFO, "WinPciDxe Exit successful-------------------->\r\n"));
  }
  return Status;
}

