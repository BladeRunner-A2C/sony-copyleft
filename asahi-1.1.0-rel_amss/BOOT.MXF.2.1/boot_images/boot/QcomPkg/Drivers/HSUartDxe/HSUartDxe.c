/** @file HSUartDxe.c
   
  HS-UART UEFI Driver code

  Copyright (c) 2023 Qualcomm Technologies, Inc. All rights reserved.
   
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/05/23   RK      Initial revision for UEFI HS-UART Driver

=============================================================================*/

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>

/**
  HS-UART PROTOCOL interfaces
 */
#include <Protocol/EFIHSUart.h>
#include "HSUart.h"
#include "DALSys.h"

/**
  HS-UART UEFI Protocol implementation
 */
EFI_QCOM_HSUART_PROTOCOL HSUartProtocolImplementation = 
{
  HSUART_DXE_REVISION,
  hsuart_initialize,
  hsuart_read,
  hsuart_write,
  hsuart_poll,
  hsuart_deinitialize,
  hsuart_set_baudrate,
  hsuart_initialize_ex,
  hsuart_read_ex,
  hsuart_write_ex,
  hsuart_poll_ex,
  hsuart_deinitialize_ex,
  hsuart_set_baudrate_ex,
};

/**
  HS-UART DXE Driver Entry Point
 */
EFI_STATUS
HSUartProtocolInit (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable)
{
  EFI_STATUS Status;

  DALSYS_InitMod(NULL);

  Status = gBS->InstallMultipleProtocolInterfaces(
	  &ImageHandle,
	  &gQcomHSUartProtocolGuid,
	  &HSUartProtocolImplementation,
	  NULL);

  return Status;
}

