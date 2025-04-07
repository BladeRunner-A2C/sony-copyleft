/** @file
  Provides platform policy services used during a capsule update.
  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc.  All Rights
  Reserved. Qualcomm Technologies Proprietary and Confidential.
  Portions:
  Copyright (c) 2016, Microsoft Corporation. All rights reserved.<BR>
  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/
/*=============================================================================
                            EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when           who         what, where, why
  --------       ---         --------------------------------------------------------
  2023/02/04     sumesahu    FR79849: Support for Prepare/Flash/Post/Rollback FMP StateMachine
                             and code refactoring
  2022/09/22     bkulkarn    Support for CheckSystemPower
  2022/07/29     sumesahu    Initial version
=====================================================================================*/

#include <PiDxe.h>
#include <Uefi.h>
#include <Library/CapsuleUpdatePolicyLib.h>
#include <Library/ECFwUpdateLib.h>
#include <Library/ECFwUpdateLib/EcPowerAndResources.h>

/**
  Determine if the system power state supports a capsule update.

  @param[out] Good  Returns TRUE if system power state supports a capsule
                    update.  Returns FALSE if system power state does not
                    support a capsule update.  Return value is only valid if
                    return status is EFI_SUCCESS.

  @retval EFI_SUCCESS            Good parameter has been updated with result.
  @retval EFI_INVALID_PARAMETER  Good is NULL.
  @retval EFI_DEVICE_ERROR       System power state can not be determined.

**/
EFI_STATUS
EFIAPI
CheckSystemPower (
  OUT BOOLEAN  *Good
  )
{
  EFI_STATUS                    status = EFI_SUCCESS;
  BOOLEAN                       bPowerGood = FALSE;
  EC_FW_UPDATE_STATE_VARIABLE   updateState  = EC_FW_STATE_NOT_IN_PROGRESS;
  EC_TRACE();

  if (NULL == Good)
  {
    EC_E("CheckSystemPower received invalid parameter!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  *Good = FALSE;

  status = GetNvEcFwUpdateState(&updateState);
  if (EFI_ERROR(status)) 
  {
    EC_E("GetNvEcFwupdateState() failed with %r\n", status);
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (EC_FW_STATE_NOT_IN_PROGRESS == updateState)
  {
    status = EcCheckPowerLevel(&bPowerGood);
    if (EFI_ERROR(status))
    {
      EC_E("EcCheckPowerLevel() failed with %r\n", status);
      goto Exit;
    }
    else if (bPowerGood == FALSE)
    { 
      EC_E("Aborting update due to insufficient battery!\n");
      *Good = FALSE;
      goto Exit;
    }
    else
    {
      *Good = TRUE;
    }
  }
  else 
  {
    // Allowing as this should be the situation where an update was
    // attempted when the battery value was in the border value of
    // the threshold and a reboot/reset would have happened between
    // update. So we need to allow the device to complete update
    // to prevent it from having partially updated contents and still
    // have an older FW version.
    *Good = TRUE;
  }

Exit:
  return status;
}

/**
  Determines if the system thermal state supports a capsule update.

  @param[out] Good  Returns TRUE if system thermal state supports a capsule
                    update.  Returns FALSE if system thermal state does not
                    support a capsule update.  Return value is only valid if
                    return status is EFI_SUCCESS.

  @retval EFI_SUCCESS            Good parameter has been updated with result.
  @retval EFI_INVALID_PARAMETER  Good is NULL.
  @retval EFI_DEVICE_ERROR       System thermal state can not be determined.

**/
EFI_STATUS
EFIAPI
CheckSystemThermal (
  OUT BOOLEAN   *Good
  )
{
  *Good = TRUE;
  return EFI_SUCCESS;
}

/**
  Determines if the system environment state supports a capsule update.

  @param[out] Good  Returns TRUE if system environment state supports a capsule
                    update.  Returns FALSE if system environment state does not
                    support a capsule update.  Return value is only valid if
                    return status is EFI_SUCCESS.

  @retval EFI_SUCCESS            Good parameter has been updated with result.
  @retval EFI_INVALID_PARAMETER  Good is NULL.
  @retval EFI_DEVICE_ERROR       System environment state can not be determined.

**/
EFI_STATUS
EFIAPI
CheckSystemEnvironment (
  OUT BOOLEAN   *Good
  )
{
  *Good = TRUE;
  EC_I(" CheckSystemEnvironment\n");
  return EFI_SUCCESS;
}

/**
  Determines if the Lowest Supported Version checks should be performed.  The
  expected result from this function is TRUE.  A platform can choose to return
  FALSE (e.g. during manufacturing or servicing) to allow a capsule update to a
  version below the current Lowest Supported Version.

  @retval TRUE   The lowest supported version check is required.
  @retval FALSE  Do not perform lowest support version check.

**/
BOOLEAN
EFIAPI
IsLowestSupportedVersionCheckRequired (
  VOID
  )
{
  EC_I(" IsLowestSupportedVersionCheckRequired\n");
  return TRUE;
}

/**
  Determines if the FMP device should be locked when the event specified by
  PcdFmpDeviceLockEventGuid is signaled. The expected result from this function
  is TRUE so the FMP device is always locked.  A platform can choose to return
  FALSE (e.g. during manufacturing) to allow FMP devices to remain unlocked.

  @retval TRUE   The FMP device lock action is required at lock event guid.
  @retval FALSE  Do not perform FMP device lock at lock event guid.

**/
BOOLEAN
EFIAPI
IsLockFmpDeviceAtLockEventGuidRequired (
  VOID
  )
{
  EC_I(" IsLockFmpDeviceAtLockEventGuidRequired\n");
  return TRUE;
}
