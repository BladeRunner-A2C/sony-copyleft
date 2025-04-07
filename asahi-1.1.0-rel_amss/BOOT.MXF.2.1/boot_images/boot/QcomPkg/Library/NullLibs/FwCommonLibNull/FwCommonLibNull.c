/** @file FwCommonLibNull.c

  Stub functions for FwCommonLib, FwProvisionLib, and FwUpdateLib
  
  Copyright (c) 2013, 2017, 2022 Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who         what, where, why
 --------   ---         -----------------------------------------------------------
 03/13/19   vkasilya    Passing the progress fun ptr as a parameter to RunFwUpdateMain
 
 04/18/17   gparam      Updated the API to match the parameter list of the
                        implementation in non-NULL library
 03/09/13   vk          Initial revision

=============================================================================*/

#include <Uefi.h>


#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/FwCommonLib.h>
#include <Protocol/FirmwareManagement.h>

EFI_STATUS
RunFwProvisionMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  return EFI_UNSUPPORTED;
}

/**
 * The user Entry Point for FirmwareUpdate.
 *
 * @param Image              -Image to update
 * @param Image              -Size of the image to update
 * @param MsftAttemptStatus  -Microsoft last attempt status 
 * @param QcResultFlag       -QCFirmwareUpdate result flag
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EFIAPI
RunFwUpdateMain (
  IN CONST VOID                                    *Image,
  IN UINTN                                          ImageSize,
  OUT UINT32                                       *MsftAttemptStatus,
  OUT QCFW_UPDATE_FLAG_VALUE                       *QcResultFlag,
  IN  EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS Progress            OPTIONAL
  )
{
  return EFI_UNSUPPORTED;
}
