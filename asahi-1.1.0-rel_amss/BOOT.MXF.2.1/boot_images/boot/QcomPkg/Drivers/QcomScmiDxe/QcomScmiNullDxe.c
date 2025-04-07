/** @file

  Copyright (c) 2017-2021, Arm Limited. All rights reserved.<BR>
  Copyright (c) 2023, Qualcomm Technologies, Inc. All Rights Reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

  @par Specification Reference:
  - Arm System Control and Management Interface - Platform Design Document
    (https://developer.arm.com/documentation/den0056/)
**/


/** ARM SCMI driver entry point function.

  Null API for QcomScmiNullDxe.

  @param[in] ImageHandle     Handle to this EFI Image which will be used to
                             install Base, Clock and Performance protocols.
  @param[in] SystemTable     A pointer to boot time system table.

  @retval EFI_UNSUPPORTED    This is Null Dxe.

**/
EFI_STATUS
EFIAPI
QcomScmiDxeEntryPoint (
  IN EFI_HANDLE             ImageHandle,
  IN EFI_SYSTEM_TABLE       *SystemTable
  )
{
  return EFI_UNSUPPORTED;
}

