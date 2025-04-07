/*============================================================================
  @file AcpiPlatfromChipInfo.h

AcpiPlatfrom Callback functions for chipinfo 
               Copyright (c) 2014-2015, 2020-2021,2022,2023 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Qualcomm Technologies Confidential and Proprietary.
               
               
============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/16/23   vb      Added AmlUpdateDpbm for populating Defective Parts Bit Mask value in ACPI
 12/21/22   vbu     Added AmlUpdateFPID for populating Product Index value in ACPI
 09/16/2022	skanni	Added missing EFIAPI for AML variables
 06/01/21   rc      Adding support for SIDT & SJTG variables
 11/20/20   vb      Port changes for support for PLST variable
 07/09/15   wayne   Added for Chip Serial number callback
 10/17/14   wayne   Created for chipinfo acpi callback 
=============================================================================*/


#ifndef ACPIPLATFORM_CHIPINFO_H
#define ACPIPLATFORM_CHIPINFO_H

extern EFI_STATUS EFIAPI AmlUpdateChipId (
  IN OUT VOID         **AmlVariableBuffer,
  IN OUT UINTN          AmlVariableBufferSize
);

extern EFI_STATUS EFIAPI AmlUpdateChipChipIdString (
  IN OUT VOID         **AmlVariableBuffer,
  IN OUT UINTN          AmlVariableBufferSize
);

extern EFI_STATUS EFIAPI AmlUpdateChipVersion (
  IN OUT VOID         **AmlVariableBuffer,
  IN OUT UINTN          AmlVariableBufferSize
);

extern EFI_STATUS EFIAPI AmlUpdateMajorChipVersion (
  IN OUT VOID         **AmlVariableBuffer,
  IN OUT UINTN          AmlVariableBufferSize
);

extern EFI_STATUS EFIAPI AmlUpdateMinorChipVersion (
  IN OUT VOID         **AmlVariableBuffer,
  IN OUT UINTN          AmlVariableBufferSize
);

extern EFI_STATUS EFIAPI AmlUpdateChipFamily(
  IN OUT VOID         **AmlVariableBuffer,
  IN OUT UINTN          AmlVariableBufferSize
);

extern EFI_STATUS EFIAPI AmlUpdateModemInfo(
  IN OUT VOID         **AmlVariableBuffer,
  IN OUT UINTN          AmlVariableBufferSize
);

extern EFI_STATUS EFIAPI AmlUpdateChipSerialNum(
  IN OUT VOID         **AmlVariableBuffer,
  IN OUT UINTN          AmlVariableBufferSize
);

extern EFI_STATUS EFIAPI AmlUpdateSocInfoAddr(
  IN OUT VOID         **AmlVariableBuffer,
  IN OUT UINTN          AmlVariableBufferSize
);

extern EFI_STATUS EFIAPI AmlGetBootOption(
  IN OUT VOID         **AmlVariableBuffer,
  IN OUT UINTN          AmlVariableBufferSize
);

extern EFI_STATUS EFIAPI AmlUpdateEmulationInfo(
  IN OUT VOID         **AmlVariableBuffer,
  IN OUT UINTN          AmlVariableBufferSize
);

extern EFI_STATUS EFIAPI AmlUpdatePlst(
  IN OUT VOID         **AmlVariableBuffer,
  IN OUT UINTN          AmlVariableBufferSize
);

extern EFI_STATUS EFIAPI AmlUpdateSidt(
  IN OUT VOID         **AmlVariableBuffer,
  IN OUT UINTN          AmlVariableBufferSize
);

extern EFI_STATUS EFIAPI AmlUpdateSjtg(
  IN OUT VOID         **AmlVariableBuffer,
  IN OUT UINTN          AmlVariableBufferSize
);

extern EFI_STATUS EFIAPI AmlUpdateFPID(
  IN OUT VOID         **AmlVariableBuffer,
  IN OUT UINTN          AmlVariableBufferSize
);

extern EFI_STATUS EFIAPI AmlUpdateDpbm(
  IN OUT VOID         **AmlVariableBuffer,
  IN OUT UINTN          AmlVariableBufferSize
);
#endif
