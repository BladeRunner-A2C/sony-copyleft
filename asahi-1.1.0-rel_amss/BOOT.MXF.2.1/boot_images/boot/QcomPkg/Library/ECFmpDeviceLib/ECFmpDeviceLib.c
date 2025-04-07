/** @file
  Provides firmware device specific services to support updates of a Embedded Controller(EC) device.

  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc. All rights reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  Portions:
  Copyright (c) 2016, Microsoft Corporation. All rights reserved.<BR>
  Copyright (c) 2018 - 2019, Intel Corporation. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/
/*=============================================================================
when           who              what, where, why
--------       ---              ------------------------------------------
2023/04/28     ananns           Update the state to UPDATE_FAIL when attempt count 
                                reaches to EC_FW_UPDATE_ATTEMPT_COUNT_MAX
2023/03/29     sumesahu         Add support for Power-off EC during off mode charging &
                                enable check for power level.
2023/03/13     bkulkarn         Migrate FmpDevicePkg to latest EDK2 version that
                                is getting integrated by UEFI team
2023/03/06     sumesahu         Reorder the sequence in Fmpdeviceinit for overcoming the Initialization Failure.
2023/02/23     bkulkarn         Support to query & update EC device status in NV and code refactoring
2023/02/28     sumesahu         Fix for Boot KPI during empty EC FW
2023/02/04     sumesahu         FR79849: Support for Prepare/Flash/Post/Rollback FMP StateMachine, code refactoring
2023/01/17     ananns           Cleaning up reference to global device context structure
2022/12/08     bkulkarn         Update Hamoa EC FW partition size/I2C core instance, code refactoring
2022/12/06     sumesahu         Remove Ec Power On, as it is controlled from PMIC.
2022/12/01     bkulkarn         Reset hook support for EC device firmware update.
2022/09/22     bkulkarn         Support for recovery protocol
2022/07/29     sumesahu         Initial version
=============================================================================*/

#include <stdbool.h>
#include <PiDxe.h>
#include <Uefi.h>
#include <Library/FmpDeviceLib.h>
#include <Protocol/LoadedImage.h>
#include <Library/UefiLib.h>
#include <Library/QcomLib.h>
#include <Library/QcomUtilsLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/SimpleFileSystem.h>
#include <Guid/FileInfo.h>
#include <LastAttemptStatus.h>

/* EC Specific Headers */
#include <Library/ECFwUpdateLib.h>
#include <Library/ECFwUpdateLib/EcPowerAndResources.h>
#include <Library/ECFwUpdateLib/EcRecovery.h>

extern EC_DEVICE_CONTEXT *deviceContext;
static EFI_GUID gEcDeviceFwResourceGuid;
extern EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS    mProgressFuncEcDeviceFmp;
extern CORRUPTION_INFO corruptionLookUpTable[];

#define LAST_ATTEMPT_STATUS_ECFMPDEVICELIB_ERROR_CODE(ecfwupdateresult) \
  (LAST_ATTEMPT_STATUS_DEVICE_LIBRARY_MIN_ERROR_CODE_VALUE + ecfwupdateresult)
  
/**
  Provide a function to install the Firmware Management Protocol instance onto a
  device handle when the device is managed by a driver that follows the UEFI
  Driver Model.  If the device is not managed by a driver that follows the UEFI
  Driver Model, then EFI_UNSUPPORTED is returned.

  @param[in] FmpInstaller  Function that installs the Firmware Management
                           Protocol.

  @retval EFI_SUCCESS      The device is managed by a driver that follows the
                           UEFI Driver Model.  FmpInstaller must be called on
                           each Driver Binding Start().
  @retval EFI_UNSUPPORTED  The device is not managed by a driver that follows
                           the UEFI Driver Model.
  @retval other            The Firmware Management Protocol for this firmware
                           device is not installed.  The firmware device is
                           still locked using FmpDeviceLock().

**/
EFI_STATUS
EFIAPI
RegisterFmpInstaller (
  IN FMP_DEVICE_LIB_REGISTER_FMP_INSTALLER  Function
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Provide a function to uninstall the Firmware Management Protocol instance from a
  device handle when the device is managed by a driver that follows the UEFI
  Driver Model.  If the device is not managed by a driver that follows the UEFI
  Driver Model, then EFI_UNSUPPORTED is returned.

  @param[in] FmpUninstaller  Function that installs the Firmware Management
                             Protocol.

  @retval EFI_SUCCESS      The device is managed by a driver that follows the
                           UEFI Driver Model.  FmpUninstaller must be called on
                           each Driver Binding Stop().
  @retval EFI_UNSUPPORTED  The device is not managed by a driver that follows
                           the UEFI Driver Model.
  @retval other            The Firmware Management Protocol for this firmware
                           device is not installed.  The firmware device is
                           still locked using FmpDeviceLock().

**/
EFI_STATUS
EFIAPI
RegisterFmpUninstaller (
  IN FMP_DEVICE_LIB_REGISTER_FMP_UNINSTALLER  Function
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Set the device context for the FmpDeviceLib services when the device is
  managed by a driver that follows the UEFI Driver Model.  If the device is not
  managed by a driver that follows the UEFI Driver Model, then EFI_UNSUPPORTED
  is returned.  Once a device context is set, the FmpDeviceLib services
  operate on the currently set device context.

  @param[in]      Handle   Device handle for the FmpDeviceLib services.
                           If Handle is NULL, then Context is freed.
  @param[in, out] Context  Device context for the FmpDeviceLib services.
                           If Context is NULL, then a new context is allocated
                           for Handle and the current device context is set and
                           returned in Context.  If Context is not NULL, then
                           the current device context is set.

  @retval EFI_SUCCESS      The device is managed by a driver that follows the
                           UEFI Driver Model.
  @retval EFI_UNSUPPORTED  The device is not managed by a driver that follows
                           the UEFI Driver Model.
  @retval other            The Firmware Management Protocol for this firmware
                           device is not installed.  The firmware device is
                           still locked using FmpDeviceLock().

**/
EFI_STATUS
EFIAPI
FmpDeviceSetContext (
  IN EFI_HANDLE  Handle,
  IN OUT VOID    **Context
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Returns the size, in bytes, of the firmware image currently stored in the
  firmware device.  This function is used to by the GetImage() and
  GetImageInfo() services of the Firmware Management Protocol.  If the image
  size can not be determined from the firmware device, then 0 must be returned.

  @param[out] Size  Pointer to the size, in bytes, of the firmware image
                    currently stored in the firmware device.

  @retval EFI_SUCCESS            The size of the firmware image currently
                                 stored in the firmware device was returned.
  @retval EFI_INVALID_PARAMETER  Size is NULL.
  @retval EFI_UNSUPPORTED        The firmware device does not support reporting
                                 the size of the currently stored firmware image.
  @retval EFI_DEVICE_ERROR       An error occurred attempting to determine the
                                 size of the firmware image currently stored in
                                 in the firmware device.

**/
EFI_STATUS
EFIAPI
FmpDeviceGetSize (
  OUT UINTN  *Size
  )
{
  EFI_STATUS status = EFI_SUCCESS;

  if (Size == NULL)
  {
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }
  *Size = 0;

Exit:
  return status;
}

/**
  Returns the GUID value used to fill in the ImageTypeId field of the
  EFI_FIRMWARE_IMAGE_DESCRIPTOR structure that is returned by the GetImageInfo()
  service of the Firmware Management Protocol.  If EFI_UNSUPPORTED is returned,
  then the ImageTypeId field is set to gEfiCallerIdGuid.  If EFI_SUCCESS is
  returned, then ImageTypeId is set to the Guid returned from this function.

  @param[out] Guid  Double pointer to a GUID value that is updated to point to
                    to a GUID value.  The GUID value is not allocated and must
                    not be modified or freed by the caller.

  @retval EFI_SUCCESS      EFI_FIRMWARE_IMAGE_DESCRIPTOR ImageTypeId GUID is set
                           to the returned Guid value.
  @retval EFI_UNSUPPORTED  EFI_FIRMWARE_IMAGE_DESCRIPTOR ImageTypeId GUID is set
                           to gEfiCallerIdGuid.

**/
EFI_STATUS
EFIAPI
FmpDeviceGetImageTypeIdGuidPtr (
  OUT EFI_GUID  **Guid
  )
{
  EFI_STATUS status = EFI_SUCCESS;

  EC_TRACE();

  if (NULL == Guid)
  {
    EC_E("Invalid Guid parameter!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  /* Get the EC Device Firmware Resource GUID for the curent platform. */
  status = GetEcFwResourceGuid(&gEcDeviceFwResourceGuid);
  if (EFI_ERROR (status))
  {
    EC_E("GetEcFwResourceGuid failed with error: %r. Using default GUID.\n", status);
    goto Exit;
  }

  *Guid = &gEcDeviceFwResourceGuid;
Exit:
  return status;
}

/**
  Returns values used to fill in the AttributesSupported and AttributesSettings
  fields of the EFI_FIRMWARE_IMAGE_DESCRIPTOR structure that is returned by the
  GetImageInfo() service of the Firmware Management Protocol.  The following
  bit values from the Firmware Management Protocol may be combined:
    IMAGE_ATTRIBUTE_IMAGE_UPDATABLE
    IMAGE_ATTRIBUTE_RESET_REQUIRED
    IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED
    IMAGE_ATTRIBUTE_IN_USE
    IMAGE_ATTRIBUTE_UEFI_IMAGE

  @param[out] Supported  Attributes supported by this firmware device.
  @param[out] Setting    Attributes settings for this firmware device.

  @retval EFI_SUCCESS            The attributes supported by the firmware
                                 device were returned.
  @retval EFI_INVALID_PARAMETER  Supported is NULL.
  @retval EFI_INVALID_PARAMETER  Setting is NULL.

**/
EFI_STATUS
EFIAPI
FmpDeviceGetAttributes (
  OUT UINT64    *Supported,
  OUT UINT64    *Setting
  )
{
  EFI_STATUS status = EFI_SUCCESS;

  EC_TRACE();

  if (Supported == NULL || Setting == NULL) {
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  *Supported = IMAGE_ATTRIBUTE_IMAGE_UPDATABLE |
               IMAGE_ATTRIBUTE_RESET_REQUIRED |
               IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED |
               IMAGE_ATTRIBUTE_IN_USE |
               IMAGE_ATTRIBUTE_UEFI_IMAGE;

  *Setting = IMAGE_ATTRIBUTE_IMAGE_UPDATABLE |
             IMAGE_ATTRIBUTE_RESET_REQUIRED |
             IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED |
             IMAGE_ATTRIBUTE_IN_USE |
             IMAGE_ATTRIBUTE_UEFI_IMAGE;

Exit:
  return status;
}

/**
  Returns the value used to fill in the LowestSupportedVersion field of the
  EFI_FIRMWARE_IMAGE_DESCRIPTOR structure that is returned by the GetImageInfo()
  service of the Firmware Management Protocol.  If EFI_SUCCESS is returned, then
  the firmware device supports a method to report the LowestSupportedVersion
  value from the currently stored firmware image.  If the value can not be
  reported for the firmware image currently stored in the firmware device, then
  EFI_UNSUPPORTED must be returned.  EFI_DEVICE_ERROR is returned if an error
  occurs attempting to retrieve the LowestSupportedVersion value for the
  currently stored firmware image.

  @note It is recommended that all firmware devices support a method to report
        the LowestSupportedVersion value from the currently stored firmware
        image.

  @param[out] LowestSupportedVersion  LowestSupportedVersion value retrieved
                                      from the currently stored firmware image.

  @retval EFI_SUCCESS       The lowest supported version of currently stored
                            firmware image was returned in LowestSupportedVersion.
  @retval EFI_UNSUPPORTED   The firmware device does not support a method to
                            report the lowest supported version of the currently
                            stored firmware image.
  @retval EFI_DEVICE_ERROR  An error occurred attempting to retrieve the lowest
                            supported version of the currently stored firmware
                            image.

**/
EFI_STATUS
EFIAPI
FmpDeviceGetLowestSupportedVersion (
  OUT UINT32  *LowestSupportedVersion
  )
{
  EFI_STATUS    status = EFI_SUCCESS;
  UINT32        LsFwVersion = DEFAULT_EC_FW_LOWEST_SUPPORTED_VERSION;
  boolean       IsLsFwVersionSame = FALSE;
  boolean       IsDeviceUp = FALSE;

  EC_TRACE();

  if (!LowestSupportedVersion)
  {
    EC_E("Invalid LowestSupportedVersion parameter!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  status = GetDeviceStatus(&IsDeviceUp);
  EC_ERROR_HANDLER(status, GetDeviceStatus, Exit);

  if (!IsDeviceUp)
  {
    EC_E("Device is not Initialised/Active with %r\n", status);
    status = EFI_UNSUPPORTED;
    goto Exit;
  }

  status = GetOnNvEcLsFwVersion(&LsFwVersion);
  if (EFI_ERROR(status))
  {
    EC_W("GetOnNvEcLsFwVersion() failed with %r, returning default value\n", status);
    *LowestSupportedVersion = DEFAULT_EC_FW_LOWEST_SUPPORTED_VERSION;
    status = EFI_SUCCESS;
    goto Exit;
  }

  status = CreateAndGetOnIcLsFwVersion(&LsFwVersion);
  EC_ERROR_HANDLER(status, CreateAndGetOnIcLsFwVersion, Exit);

  status = CompareOnIcLsFwVersions(&IsLsFwVersionSame);
  EC_ERROR_HANDLER(status, CompareOnIcLsFwVersions, Exit);

  if (!IsLsFwVersionSame)
  {
    *LowestSupportedVersion = LsFwVersion;

    status = SetNvEcLsFwVersion(LsFwVersion);
    EC_ERROR_HANDLER(status, SetNvEcLsFwVersion, Exit);
  }
  else
  {
    *LowestSupportedVersion = LsFwVersion;
  }

Exit:
  return status;
}

/**
 This routine get the current firmware version and convert it in to represenatable string format by masking version value.
  @retval CHAR16 *  returns the firmware version in string format
  @retval NULL      firmware version not found so return NULL
**/
CHAR16 *FmpDeviceCreateEcVersionNameString()
{
  UINT32        Major =0;
  UINT32        Minor =0;
  UINT32        Version = 0;
  CHAR16        *VersionStr= NULL;
  boolean       IsDeviceUp = FALSE;
  EFI_STATUS    status = EFI_SUCCESS;

  status = GetDeviceStatus(&IsDeviceUp);
  EC_WARN_HANDLER(status, GetDeviceStatus);
  if (!IsDeviceUp)
  {
    EC_E("Device is not Initialised/Active with %r\n", status);
    goto Exit;
  }

  status = FmpDeviceGetVersion(&Version);
  if (EFI_SUCCESS == status)
  {
    Minor = Version & 0xffff;
    Major = (Version >> 16) & 0xffff;

    VersionStr = CatSPrint(VersionStr,L":  %d.%d",Major,Minor);
    EC_I("[FmpDeviceCreateEcVersionNameString]: VersionStr=%s\n", VersionStr);
  }

Exit:
  return VersionStr;
}

/**
  Returns the Null-terminated Unicode string that is used to fill in the
  VersionName field of the EFI_FIRMWARE_IMAGE_DESCRIPTOR structure that is
  returned by the GetImageInfo() service of the Firmware Management Protocol.
  The returned string must be allocated using EFI_BOOT_SERVICES.AllocatePool().

  @note It is recommended that all firmware devices support a method to report
        the VersionName string from the currently stored firmware image.

  @param[out] VersionString  The version string retrieved from the currently
                             stored firmware image.

  @retval EFI_SUCCESS            The version string of currently stored
                                 firmware image was returned in Version.
  @retval EFI_INVALID_PARAMETER  VersionString is NULL.
  @retval EFI_UNSUPPORTED        The firmware device does not support a method
                                 to report the version string of the currently
                                 stored firmware image.
  @retval EFI_DEVICE_ERROR       An error occurred attempting to retrieve the
                                 version string of the currently stored
                                 firmware image.
  @retval EFI_OUT_OF_RESOURCES   There are not enough resources to allocate the
                                 buffer for the version string of the currently
                                 stored firmware image.

**/
EFI_STATUS
EFIAPI
FmpDeviceGetVersionString (
  OUT CHAR16  **VersionString
  )
{
  EFI_STATUS status = EFI_SUCCESS;
  boolean   IsFwUpdateDone = FALSE;

  if ((NULL == VersionString) ||
    (NULL == *VersionString))
  {
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  *VersionString = FmpDeviceCreateEcVersionNameString();
  if ((CHAR16*)NULL != *VersionString)
  {
    status = EFI_SUCCESS;
    goto Exit;
  }

  status = GetFwUpdateStatus(&IsFwUpdateDone);
  EC_ERROR_HANDLER(status, GetFwUpdateStatus, Exit);

  if (IsFwUpdateDone)
  {
    status = EcDeInitializeDevice();
  }

Exit:
  return status;
}


/**
  Returns the value used to fill in the Version field of the
  EFI_FIRMWARE_IMAGE_DESCRIPTOR structure that is returned by the GetImageInfo()
  service of the Firmware Management Protocol.  If EFI_SUCCESS is returned, then
  the firmware device supports a method to report the Version value from the
  currently stored firmware image.  If the value can not be reported for the
  firmware image currently stored in the firmware device, then EFI_UNSUPPORTED
  must be returned.  EFI_DEVICE_ERROR is returned if an error occurs attempting
  to retrieve the LowestSupportedVersion value for the currently stored firmware
  image.

  @note It is recommended that all firmware devices support a method to report
        the Version value from the currently stored firmware image.

  @param[out] Version  The version value retrieved from the currently stored
                       firmware image.

  @retval EFI_SUCCESS       The version of currently stored firmware image was
                            returned in Version.
  @retval EFI_UNSUPPORTED   The firmware device does not support a method to
                            report the version of the currently stored firmware
                            image.
  @retval EFI_DEVICE_ERROR  An error occurred attempting to retrieve the version
                            of the currently stored firmware image.
**/
EFI_STATUS
EFIAPI
FmpDeviceGetVersion (
  OUT UINT32  *Version
  )
{
  EFI_STATUS    status              = EFI_SUCCESS;
  UINT32        FwVersion           = DEFAULT_EC_FW_VERSION;
  UINT32        LsFwVersion         = DEFAULT_EC_FW_LOWEST_SUPPORTED_VERSION;
  boolean       IsOnIcFwVersionSame = FALSE;
  UINT8         CodeMirrorTag       = 0;
  boolean       IsDeviceUp          = FALSE;

  EC_TRACE();

  if (!Version)
  {
    status = EFI_DEVICE_ERROR;
    EC_E("Invalid input parameter received in FmpDeviceGetVersion. Returning %r\n",
      status);
    goto Exit;
  }

  status = GetDeviceStatus(&IsDeviceUp);
  EC_WARN_HANDLER(status, GetDeviceStatus);
  if (!IsDeviceUp)
  {
    EC_E("Device is not Initialised/Active with %r\n", status);
    status = EFI_UNSUPPORTED;
    goto Exit;
  }

  status = GetOnNvEcFwVersion(&FwVersion);
  EC_I("GetOnNvEcFwVersion() returned %r\n", status);

  // Query the EC FW version from device
  status = GetOnDeviceFullEcFwVersion();
  if (EFI_ERROR(status))
  {
    EC_E("GetOnDeviceFullEcFwVersion failed with %r!\n", status);
    deviceContext->is_fw_corrupted = 1;
    goto Exit;
  }

  status = CreateAndGetOnIcFwVersion(&FwVersion);
  EC_ERROR_HANDLER(status, CreateAndGetOnIcFwVersion, Exit);

  status = CreateAndGetOnIcLsFwVersion(&LsFwVersion);
  EC_ERROR_HANDLER(status, CreateAndGetOnIcLsFwVersion, Exit);

  /* Do comparison and flush the latest Fv and LsFv to NV storage */
  status = CompareOnIcFwVersion(&IsOnIcFwVersionSame);
  EC_ERROR_HANDLER(status, CompareOnIcFwVersion, Exit);

  if (!IsOnIcFwVersionSame)
  {
    *Version = FwVersion;

    status = SetNvEcFwVersion(FwVersion);
    EC_WARN_HANDLER(status, SetNvEcFwVersion);
  }

  /*
   * If code-mirror tag corresponds to "R" (ASCII: 0x52)
   * reset the EC related NV items as this indicates FW is recovered from Recovery partition.
   */
  status = GetCodeMirrorTag(&CodeMirrorTag);
  EC_ERROR_HANDLER(status, GetCodeMirrorTag, Exit);

  if (CodeMirrorTag == 0x52)
  {
    status = SetNvEcFwAttemptCount(0);
    EC_WARN_HANDLER(status, SetNvEcFwAttemptCount);

    status = SetNvEcFwVersion(DEFAULT_EC_FW_VERSION);
    EC_WARN_HANDLER(status, SetNvEcFwVersion);

    status = SetNvEcLsFwVersion(DEFAULT_EC_FW_LOWEST_SUPPORTED_VERSION);
    EC_WARN_HANDLER(status, SetNvEcLsFwVersion);

    status = SetNvEcFwUpdateState(
      EC_FW_STATE_NOT_IN_PROGRESS
      );
    EC_WARN_HANDLER(status, SetNvEcFwUpdateState);
  }

  *Version = FwVersion;

  status = DisplayEcFwVersionDetails();
  if (EFI_ERROR(status))
  {
    EC_E("DisplayVersionDetails failed with %r\n",status);
    goto Exit;
  }

Exit:
    return status;
}

/**
  Returns the value used to fill in the HardwareInstance field of the
  EFI_FIRMWARE_IMAGE_DESCRIPTOR structure that is returned by the GetImageInfo()
  service of the Firmware Management Protocol.  If EFI_SUCCESS is returned, then
  the firmware device supports a method to report the HardwareInstance value.
  If the value can not be reported for the firmware device, then EFI_UNSUPPORTED
  must be returned.  EFI_DEVICE_ERROR is returned if an error occurs attempting
  to retrieve the HardwareInstance value for the firmware device.

  @param[out] HardwareInstance  The hardware instance value for the firmware
                                device.

  @retval EFI_SUCCESS       The hardware instance for the current firmware
                            device is returned in HardwareInstance.
  @retval EFI_UNSUPPORTED   The firmware device does not support a method to
                            report the hardware instance value.
  @retval EFI_DEVICE_ERROR  An error occurred attempting to retrieve the hardware
                            instance value.

**/
EFI_STATUS
EFIAPI
FmpDeviceGetHardwareInstance (
  OUT UINT64  *HardwareInstance
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Returns a copy of the firmware image currently stored in the firmware device.

  @note It is recommended that all firmware devices support a method to retrieve
        a copy currently stored firmware image.  This can be used to support
        features such as recovery and rollback.

  @param[out]     Image     Pointer to a caller allocated buffer where the
                            currently stored firmware image is copied to.
  @param[in, out] ImageSize Pointer the size, in bytes, of the Image buffer.
                            On return, points to the size, in bytes, of firmware
                            image currently stored in the firmware device.

  @retval EFI_SUCCESS            Image contains a copy of the firmware image
                                 currently stored in the firmware device, and
                                 ImageSize contains the size, in bytes, of the
                                 firmware image currently stored in the
                                 firmware device.
  @retval EFI_BUFFER_TOO_SMALL   The buffer specified by ImageSize is too small
                                 to hold the firmware image currently stored in
                                 the firmware device. The buffer size required
                                 is returned in ImageSize.
  @retval EFI_INVALID_PARAMETER  The Image is NULL.
  @retval EFI_INVALID_PARAMETER  The ImageSize is NULL.
  @retval EFI_UNSUPPORTED        The operation is not supported.
  @retval EFI_DEVICE_ERROR       An error occurred attempting to retrieve the
                                 firmware image currently stored in the firmware
                                 device.

**/
EFI_STATUS
EFIAPI
FmpDeviceGetImage (
  OUT    VOID   *Image,
  IN OUT UINTN  *ImageSize
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Checks if a new firmware image is valid for the firmware device.  This
  function allows firmware update operation to validate the firmware image
  before FmpDeviceSetImage() is called.

  @param[in]  Image           Points to a new firmware image.
  @param[in]  ImageSize       Size, in bytes, of a new firmware image.
  @param[out] ImageUpdatable  Indicates if a new firmware image is valid for
                              a firmware update to the firmware device.  The
                              following values from the Firmware Management
                              Protocol are supported:
                                IMAGE_UPDATABLE_VALID
                                IMAGE_UPDATABLE_INVALID
                                IMAGE_UPDATABLE_INVALID_TYPE
                                IMAGE_UPDATABLE_INVALID_OLD
                                IMAGE_UPDATABLE_VALID_WITH_VENDOR_CODE

  @retval EFI_SUCCESS            The image was successfully checked.  Additional
                                 status information is returned in
                                 ImageUpdatable.
  @retval EFI_INVALID_PARAMETER  Image is NULL.
  @retval EFI_INVALID_PARAMETER  ImageUpdatable is NULL.

**/
EFI_STATUS
EFIAPI
FmpDeviceCheckImage (
  IN  CONST VOID  *Image,
  IN  UINTN       ImageSize,
  OUT UINT32      *ImageUpdatable
  )
{
  UINT32  LastAttemptStatus = LAST_ATTEMPT_STATUS_SUCCESS;

  EC_TRACE();

  return FmpDeviceCheckImageWithStatus(
    Image,
    ImageSize,
    ImageUpdatable,
    &LastAttemptStatus
    );
}

/**
  Updates a firmware device with a new firmware image.  This function returns
  EFI_UNSUPPORTED if the firmware image is not updatable.  If the firmware image
  is updatable, the function should perform the following minimal validations
  before proceeding to do the firmware image update.
    - Validate that the image is a supported image for this firmware device.
      Return EFI_ABORTED if the image is not supported.  Additional details
      on why the image is not a supported image may be returned in AbortReason.
    - Validate the data from VendorCode if is not NULL.  Firmware image
      validation must be performed before VendorCode data validation.
      VendorCode data is ignored or considered invalid if image validation
      fails.  Return EFI_ABORTED if the VendorCode data is invalid.

  VendorCode enables vendor to implement vendor-specific firmware image update
  policy.  Null if the caller did not specify the policy or use the default
  policy.  As an example, vendor can implement a policy to allow an option to
  force a firmware image update when the abort reason is due to the new firmware
  image version is older than the current firmware image version or bad image
  checksum.  Sensitive operations such as those wiping the entire firmware image
  and render the device to be non-functional should be encoded in the image
  itself rather than passed with the VendorCode.  AbortReason enables vendor to
  have the option to provide a more detailed description of the abort reason to
  the caller.

  @param[in]  Image             Points to the new firmware image.
  @param[in]  ImageSize         Size, in bytes, of the new firmware image.
  @param[in]  VendorCode        This enables vendor to implement vendor-specific
                                firmware image update policy.  NULL indicates
                                the caller did not specify the policy or use the
                                default policy.
  @param[in]  Progress          A function used to report the progress of
                                updating the firmware device with the new
                                firmware image.
  @param[in]  CapsuleFwVersion  The version of the new firmware image from the
                                update capsule that provided the new firmware
                                image.
  @param[out] AbortReason       A pointer to a pointer to a Null-terminated
                                Unicode string providing more details on an
                                aborted operation. The buffer is allocated by
                                this function with
                                EFI_BOOT_SERVICES.AllocatePool().  It is the
                                caller's responsibility to free this buffer with
                                EFI_BOOT_SERVICES.FreePool().

  @retval EFI_SUCCESS            The firmware device was successfully updated
                                 with the new firmware image.
  @retval EFI_ABORTED            The operation is aborted.  Additional details
                                 are provided in AbortReason.
  @retval EFI_INVALID_PARAMETER  The Image was NULL.
  @retval EFI_UNSUPPORTED        The operation is not supported.

**/
EFI_STATUS
EFIAPI
FmpDeviceSetImage (
  IN  CONST VOID                                     *Image,
  IN  UINTN                                          ImageSize,
  IN  CONST VOID                                     *VendorCode,       OPTIONAL
  IN  EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress,          OPTIONAL
  IN  UINT32                                         CapsuleFwVersion,
  OUT CHAR16                                         **AbortReason
  )
{
  UINT32  LastAttemptStatus = LAST_ATTEMPT_STATUS_SUCCESS;

  EC_TRACE();

  return FmpDeviceSetImageWithStatus(
    Image,
    ImageSize,
    VendorCode,
    Progress,
    CapsuleFwVersion,
    AbortReason,
    &LastAttemptStatus
    );
}

/**
  Lock the firmware device that contains a firmware image.  Once a firmware
  device is locked, any attempts to modify the firmware image contents in the
  firmware device must fail.

  @note It is recommended that all firmware devices support a lock method to
        prevent modifications to a stored firmware image.

  @note A firmware device lock mechanism is typically only cleared by a full
        system reset (not just sleep state/low power mode).

  @retval  EFI_SUCCESS      The firmware device was locked.
  @retval  EFI_UNSUPPORTED  The firmware device does not support locking

**/
EFI_STATUS
EFIAPI
FmpDeviceLock (
  VOID
  )
{
  EFI_STATUS    status = EFI_UNSUPPORTED;

  // [TODO]: Enable once EC firmware supports write-protection feature.
#if EC_WRITE_PROT_EN
  UINT32 IsWriteProtectEnabled = FALSE;

  status = EcUpdateTLMMGpio(
    GPIO_FOR_EC_WRITE_PROT_EN,
    DAL_GPIO_HIGH_VALUE);
  EC_ERROR_HANDLER(status, EcUpdateTLMMGpio, Exit);

  IsWriteProtectEnabled = TRUE;
  status = SetNvEcWriteProtectStatus(IsWriteProtectEnabled);
  EC_ERROR_HANDLER(status, SetNvEcWriteProtectStatus, Exit);
Exit:
#endif
  return status;
}

/**
  Prepare for the subsequent calls from FmpDxe by keeping the necessary contents
  initialized

  @retval  EFI_SUCCESS      The firmware device was successfully initialized.

**/
EFI_STATUS
EFIAPI
FmpDeviceInit (
  VOID
  )
{
  EFI_STATUS  status = EFI_SUCCESS;
  EC_TRACE();

 /*
  * QCOM_EDK2 Patch expects this function to return EFI_SUCCESS.
  * Upon returning failure, an ASSERT() is raised in the EDK2's FmpDxe code.
  * To avoid blocking of device boot-up, this function always returns EFI_SUCCESS.
  */

  status = EcInitializeDevice();
  if (EFI_ERROR(status))
  {
    EC_E("EcInitializeDevice() failed with %r\n", status);
    status = EFI_SUCCESS;
    goto Exit;
  }

  status = EcPowerInit();
  if (EFI_ERROR(status))
  {
    EC_E("EcPowerInit() failed with %r\n", status);
    status = EFI_SUCCESS;
    goto Exit;
  }

  status = EcOffModeChargingHandler();
  if (EFI_ERROR(status))
  {
    EC_E("EcOffModeChargingHandler() failed with %r\n", status);
    status = EFI_SUCCESS;
    goto Exit;
  }

  status = EcRecoveryGetChipID();
  if (EFI_ERROR(status))
  {
    EC_E("EcRecoveryGetChipID() failed with %r\n", status);
    status = EFI_SUCCESS;
    goto Exit;
  }

  status = CheckAndCreateEcNVData();
  if (EFI_ERROR(status))
  {
    EC_E("CheckAndCreateEcNVData() failed with %r\n", status);
    status = EFI_SUCCESS;
    goto Exit;
  }

  status = QueryAndUpdateDeviceStatus();
  if (EFI_ERROR(status))
  {
    EC_E("QueryAndUpdateDeviceStatus() failed with %r\n", status);
    status = EFI_SUCCESS;
    goto Exit;
  }

  status = WaitForEcFwToStable();
  if (EFI_ERROR(status))
  {
    EC_E("WaitForEcFwToStable() failed with %r\n",status);
    status = EFI_SUCCESS;
    goto Exit;
  }

  status = GetEcDeviceId();
  if (EFI_ERROR(status))
  {
    EC_E("GetEcDeviceId() failed with %r\n",status);
    status = EFI_SUCCESS;
    goto Exit;
  }

  status = DisplayEcFwPartitionDetails();
  if (EFI_ERROR(status))
  {
    EC_E("DisplayVersionDetails failed with %r\n",status);
    status = EFI_SUCCESS;
    goto Exit;
  }

Exit:
  return status;
}

EFI_STATUS FmpDeviceVarLockOnEvent(
  EFI_GUID *LockGuid,
  const CHAR16  **FmpVariableList,
  UINT32 VariableListSize
  )
{

  EFI_STATUS status = EFI_SUCCESS;
  return status;
}

/**
  Updates a firmware device with a new firmware image.  This function returns
  EFI_UNSUPPORTED if the firmware image is not updatable.  If the firmware image
  is updatable, the function should perform the following minimal validations
  before proceeding to do the firmware image update.
    - Validate that the image is a supported image for this firmware device.
      Return EFI_ABORTED if the image is not supported.  Additional details
      on why the image is not a supported image may be returned in AbortReason.
    - Validate the data from VendorCode if is not NULL.  Firmware image
      validation must be performed before VendorCode data validation.
      VendorCode data is ignored or considered invalid if image validation
      fails.  Return EFI_ABORTED if the VendorCode data is invalid.

  VendorCode enables vendor to implement vendor-specific firmware image update
  policy.  Null if the caller did not specify the policy or use the default
  policy.  As an example, vendor can implement a policy to allow an option to
  force a firmware image update when the abort reason is due to the new firmware
  image version is older than the current firmware image version or bad image
  checksum.  Sensitive operations such as those wiping the entire firmware image
  and render the device to be non-functional should be encoded in the image
  itself rather than passed with the VendorCode.  AbortReason enables vendor to
  have the option to provide a more detailed description of the abort reason to
  the caller.

  @param[in]  Image             Points to the new firmware image.
  @param[in]  ImageSize         Size, in bytes, of the new firmware image.
  @param[in]  VendorCode        This enables vendor to implement vendor-specific
                                firmware image update policy.  NULL indicates
                                the caller did not specify the policy or use the
                                default policy.
  @param[in]  Progress          A function used to report the progress of
                                updating the firmware device with the new
                                firmware image.
  @param[in]  CapsuleFwVersion  The version of the new firmware image from the
                                update capsule that provided the new firmware
                                image.
  @param[out] AbortReason       A pointer to a pointer to a Null-terminated
                                Unicode string providing more details on an
                                aborted operation. The buffer is allocated by
                                this function with
                                EFI_BOOT_SERVICES.AllocatePool().  It is the
                                caller's responsibility to free this buffer with
                                EFI_BOOT_SERVICES.FreePool().
  @param[out] LastAttemptStatus A pointer to a UINT32 that holds the last attempt
                                status to report back to the ESRT table in case
                                of error. This value will only be checked when this
                                function returns an error.

                                The return status code must fall in the range of
                                LAST_ATTEMPT_STATUS_DEVICE_LIBRARY_MIN_ERROR_CODE_VALUE to
                                LAST_ATTEMPT_STATUS_DEVICE_LIBRARY_MAX_ERROR_CODE_VALUE.

                                If the value falls outside this range, it will be converted
                                to LAST_ATTEMPT_STATUS_ERROR_UNSUCCESSFUL.

  @retval EFI_SUCCESS            The firmware device was successfully updated
                                 with the new firmware image.
  @retval EFI_ABORTED            The operation is aborted.  Additional details
                                 are provided in AbortReason.
  @retval EFI_INVALID_PARAMETER  The Image was NULL.
  @retval EFI_UNSUPPORTED        The operation is not supported.

**/
EFI_STATUS
EFIAPI
FmpDeviceSetImageWithStatus (
  IN  CONST VOID                                     *Image,
  IN  UINTN                                          ImageSize,
  IN  CONST VOID                                     *VendorCode        OPTIONAL,
  IN  EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS  Progress           OPTIONAL,
  IN  UINT32                                         CapsuleFwVersion,
  OUT CHAR16                                         **AbortReason,
  OUT UINT32                                         *LastAttemptStatus
  )
{
  EFI_STATUS            status = EFI_SUCCESS;
  EFI_STATUS            statusExitPath = EFI_SUCCESS;
  UINT32                FirmwareVersion = 0;
  UINT32                newFirmwareVersion = 0;
  UINT32                LowestSupportedFirmwareVersion = 0;
  UINT32                newLowestSupportedFirmwareVersion = 0;
  boolean               IsValidRawBuffExist = FALSE;
  EC_FW_UPDATE_RESULT   EcFwUpdateResult = EC_FW_UPDATE_SUCCESS;

  EC_TRACE();

  if (Progress != NULL)
  {
    mProgressFuncEcDeviceFmp = Progress;
  }

  if (!Image)
  {
    EC_E("Image parameter is NULL.\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!LastAttemptStatus)
  {
    EC_E("LastAttemptStatus parameter is NULL.\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  *LastAttemptStatus = LAST_ATTEMPT_STATUS_SUCCESS;

  status = GetRawBuffExistStatus(&IsValidRawBuffExist);
  EC_ERROR_HANDLER(status, GetRawBuffExistStatus, Exit);

  if (!IsValidRawBuffExist)
  {
    EC_E("Raw buffer is not valid!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  status = GetOnIcAndOnBinVersion(
    &FirmwareVersion,
    &LowestSupportedFirmwareVersion,
    &newFirmwareVersion,
    &newLowestSupportedFirmwareVersion
  );
  EC_ERROR_HANDLER(status, GetOnIcAndOnBinVersion, Exit);

  EC_I("Fv: 0x%X, lsFv: 0x%X, newfv: 0x%X, newlsFv: 0x%X\n",
    FirmwareVersion, LowestSupportedFirmwareVersion,
    newFirmwareVersion, newLowestSupportedFirmwareVersion);

  status = EcFwUpdateMain(
    Image,
    ImageSize,
    LastAttemptStatus,
    Progress
    );
  EC_ERROR_HANDLER(status, EcFwUpdateMain, Exit);

  EC_W("EC firmware updated successfully\n");

#if EC_WRITE_PROT_EN
  UINT32 IsWriteProtectEnabled = FALSE;

  // Enable the EC Write-protection to prevent access to the EC flash.
  status = EcUpdateTLMMGpio(
    GPIO_FOR_EC_WRITE_PROT_EN,
    DAL_GPIO_HIGH_VALUE);
  EC_ERROR_HANDLER(status, EcUpdateTLMMGpio, Exit);

  IsWriteProtectEnabled = TRUE;
  status = SetNvEcWriteProtectStatus(IsWriteProtectEnabled);
  EC_ERROR_HANDLER(status, SetNvEcWriteProtectStatus, Exit);
#endif

Exit:

  ResetEcFwHookEntryToDefault();

  if (EFI_ERROR(status))
  {
    EcFwUpdateResult = EC_FW_UPDATE_FAIL;

    if (LastAttemptStatus)
    {
      if (LAST_ATTEMPT_STATUS_SUCCESS == *LastAttemptStatus)
      {
        *LastAttemptStatus = LAST_ATTEMPT_STATUS_ECFMPDEVICELIB_ERROR_CODE(EcFwUpdateResult);
      }

      EC_W("Firmware update failed with %r. Last attempt status: 0x%x\n",
        status, *LastAttemptStatus);
    }
  }
  else
  {
    EC_I("Firmware update completed successfully\n");
  }

  if (LastAttemptStatus)
  {
    if (LAST_ATTEMPT_STATUS_SUCCESS == *LastAttemptStatus)
    {
      // Update the lowest supported version only if it's greater than current one.
      if (newLowestSupportedFirmwareVersion > LowestSupportedFirmwareVersion)
      {
        LowestSupportedFirmwareVersion = newLowestSupportedFirmwareVersion;
      }
      FirmwareVersion = newFirmwareVersion;

      statusExitPath = SetNvEcFwVersion(FirmwareVersion);
      EC_WARN_HANDLER(statusExitPath, SetNvEcWriteProtectStatus);

      statusExitPath = SetNvEcLsFwVersion(newLowestSupportedFirmwareVersion);
      EC_WARN_HANDLER(statusExitPath, SetNvEcLsFwVersion);
    }
  }

  if (Progress != NULL)
  {
    Progress(PROGRESS_EC_FW_CAPSULE_UPDATE_PROCESS_COMPLETE);
  }

  statusExitPath = SetNvEcFwAttemptCount(0);
  EC_WARN_HANDLER(statusExitPath, SetNvEcFwAttemptCount);

  statusExitPath = SetNvEcFwUpdateState(
    EC_FW_STATE_NOT_IN_PROGRESS);
  EC_WARN_HANDLER(statusExitPath, SetNvEcFwUpdateState);

  if (EFI_SUCCESS == status)
  {
    statusExitPath = SetFwUpdateStatus(1);
    EC_WARN_HANDLER(statusExitPath, SetFwUpdateStatus);
  }

  EC_I(" FmpDeviceSetImage Exit with status %r\n", status);
  return (EFI_ERROR (status) ? status : statusExitPath);
}

/**
  Checks if a new firmware image is valid for the firmware device.  This
  function allows firmware update operation to validate the firmware image
  before FmpDeviceSetImage() is called.

  @param[in]  Image               Points to a new firmware image.
  @param[in]  ImageSize           Size, in bytes, of a new firmware image.
  @param[out] ImageUpdatable      Indicates if a new firmware image is valid for
                                  a firmware update to the firmware device.  The
                                  following values from the Firmware Management
                                  Protocol are supported:
                                    IMAGE_UPDATABLE_VALID
                                    IMAGE_UPDATABLE_INVALID
                                    IMAGE_UPDATABLE_INVALID_TYPE
                                    IMAGE_UPDATABLE_INVALID_OLD
                                    IMAGE_UPDATABLE_VALID_WITH_VENDOR_CODE
  @param[out] LastAttemptStatus   A pointer to a UINT32 that holds the last attempt
                                  status to report back to the ESRT table in case
                                  of error.

                                  The return status code must fall in the range of
                                  LAST_ATTEMPT_STATUS_DEVICE_LIBRARY_MIN_ERROR_CODE_VALUE to
                                  LAST_ATTEMPT_STATUS_DEVICE_LIBRARY_MAX_ERROR_CODE_VALUE.

                                  If the value falls outside this range, it will be converted
                                  to LAST_ATTEMPT_STATUS_ERROR_UNSUCCESSFUL.

  @retval EFI_SUCCESS            The image was successfully checked.  Additional
                                 status information is returned in
                                 ImageUpdatable.
  @retval EFI_INVALID_PARAMETER  Image is NULL.
  @retval EFI_INVALID_PARAMETER  ImageUpdatable is NULL.

**/
EFI_STATUS
EFIAPI
FmpDeviceCheckImageWithStatus(
  IN  CONST VOID  *Image,
  IN  UINTN       ImageSize,
  OUT UINT32      *ImageUpdatable,
  OUT UINT32      *LastAttemptStatus
  )
{
  EFI_STATUS            status = EFI_SUCCESS;
  EFI_STATUS            statusOnDeInit = EFI_SUCCESS;
  VOID                  *EcFwBuffer = NULL;
  UINTN                 EcFwBufferSize = 0;
  UINT32                FwVersion = DEFAULT_EC_FW_VERSION;
  UINT32                LsFwVersion = DEFAULT_EC_FW_LOWEST_SUPPORTED_VERSION;
  UINT32                OnBinFwVersion = DEFAULT_EC_FW_VERSION;
  UINT32                OnBinLsFwVersion = DEFAULT_EC_FW_LOWEST_SUPPORTED_VERSION;
  byte                  EcVersionStartbyte = 0;
  boolean               IsFwVersionLesser = FALSE;
  UINT8                 RawBuffStatus = 0;
  char                  *ECVersionString[] = { "EC VER:", "LsFv:" };
  EC_FW_UPDATE_RESULT   EcFwUpdateResult = EC_FW_UPDATE_SUCCESS;

  EC_TRACE();

  if (!Image)
  {
    EC_E("Image Pointer Parameter is NULL.\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!ImageSize)
  {
    EC_E("ImageSize is invalid.\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (!ImageUpdatable)
  {
    EC_E("ImageUpdateable Pointer Parameter is NULL.\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  //Set to valid and then if any tests fail it will update this flag.
  *ImageUpdatable = IMAGE_UPDATABLE_VALID;

  if (!LastAttemptStatus)
  {
    EC_E("LastAttemptStatus is invalid!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  *LastAttemptStatus = LAST_ATTEMPT_STATUS_SUCCESS;

  status = ReadEcFwFromFV(
    (void *)Image,
    ImageSize,
    &EcFwBuffer,
    &EcFwBufferSize
    );
  EC_ERROR_HANDLER(status, ReadEcFwFromFV, Exit);

  if (!EcFwBufferSize)
  {
    EC_E("Invalid EcFwBufferSize!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  status = GetECVersionOffset(
    (byte *)EcFwBuffer,
    EcFwBufferSize,
    &EcVersionStartbyte
    );
  EC_ERROR_HANDLER(status, GetECVersionOffset, Exit);

  EC_I("Bin File Size: %d\n", EcFwBufferSize);
  EC_I("Size of FW file = %dKB\n", (EcFwBufferSize/1024));

  if ('E' == EcVersionStartbyte)
  {
    EC_I("Binary data successfully copied!\n");
    RawBuffStatus = 1;
  }
  else
  {
    EC_W("Binary data not copied properly!!\n");
    RawBuffStatus = 0;
  }

  status = SetRawBuffExistStatus(RawBuffStatus);
  EC_ERROR_HANDLER(status, SetRawBuffExistStatus, Exit);

  status = GetOnBinaryEcFwVersions(
    *(ECVersionString + 0)
    );
  EC_ERROR_HANDLER(status, GetOnBinaryEcFwVersions, Exit);

  status = CreateAndSetOnBinFwVersion(&OnBinFwVersion);
  EC_ERROR_HANDLER(status, CreateAndSetOnBinFwVersion, Exit);

  status = GetOnBinaryEcFwVersions(
    *(ECVersionString + 1)
    );
  EC_ERROR_HANDLER(status, GetOnBinaryEcFwVersions, Exit);

  status = CreateAndGetOnBinLsFwVersion(&OnBinLsFwVersion);
  EC_ERROR_HANDLER(status, CreateAndGetOnBinLsFwVersion, Exit);

  status = CompareFwVersion(&IsFwVersionLesser);
  EC_ERROR_HANDLER(status, CompareFwVersion, Exit);
  if (!IsFwVersionLesser)
  {
    status = DisplayVersionMismatchDetails();
    EC_WARN_HANDLER(status, DisplayVersionMismatchDetails);

    status = CreateAndGetOnIcFwVersion(&FwVersion);
    EC_ERROR_HANDLER(status, CreateAndGetOnIcFwVersion, Exit);

    status = CreateAndGetOnIcLsFwVersion(&LsFwVersion);
    EC_ERROR_HANDLER(status, CreateAndGetOnIcLsFwVersion, Exit);

    status = SetNvEcFwVersion(FwVersion);
    EC_ERROR_HANDLER(status, SetNvEcFwVersion, Exit);

    status = SetNvEcLsFwVersion(LsFwVersion);
    EC_ERROR_HANDLER(status, SetNvEcLsFwVersion, Exit);
  }

  // [TODO]: Enable once EC firmware supports write-protection feature.
#if EC_WRITE_PROT_EN
  UINT32 WriteProtectStatus = FALSE;

  status = EcUpdateTLMMGpio(
    GPIO_FOR_EC_WRITE_PROT_EN,
    DAL_GPIO_LOW_VALUE);
  EC_ERROR_HANDLER(status, EcUpdateTLMMGpio, Exit);

  WriteProtectStatus = FALSE;
  status = SetNvEcWriteProtectStatus(WriteProtectStatus);
  EC_ERROR_HANDLER(status, SetNvEcWriteProtectStatus, Exit);
#endif

Exit:
  if (EFI_ERROR(status))
  {
    EcFwUpdateResult = EC_FW_UPDATE_FAIL;

    if (LastAttemptStatus)
    {
      *LastAttemptStatus = LAST_ATTEMPT_STATUS_ECFMPDEVICELIB_ERROR_CODE(EcFwUpdateResult);
    }
    statusOnDeInit = EcDeInitializeDevice();
    EC_WARN_HANDLER(status, EcDeInitializeDevice);

    if (ImageUpdatable)
    {
      *ImageUpdatable = IMAGE_UPDATABLE_INVALID;
    }
  }

  EC_I(" FmpDeviceCheckImageWithStatus Exit with status %r\n", status);
  return status;
}

