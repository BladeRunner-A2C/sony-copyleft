/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __DIAGNOSTICS_H
#define __DIAGNOSTICS_H

#include <Uefi.h>
#include <Protocol/DriverDiagnostics2.h>
#include <Protocol/PciIo.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiLib.h>

#include "Debug.h"

EFI_STATUS 
EFIAPI
QcWlanRunDiagnostics (
  IN  EFI_DRIVER_DIAGNOSTICS2_PROTOCOL  *This,
  IN  EFI_HANDLE                        ControllerHandle,
  IN  EFI_HANDLE                        ChildHandle,       OPTIONAL
  IN  EFI_DRIVER_DIAGNOSTIC_TYPE        DiagnosticType,
  IN  CHAR8                             *Language,
  OUT EFI_GUID                          **ErrorType,
  OUT UINTN                             *BufferSize,
  OUT CHAR16                            **Buffer
  );

#endif
