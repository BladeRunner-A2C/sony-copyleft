/** @file EcUpdateStateMachine.c

  Provides EC FW Update State Machine services.

  Copyright (c) 2022-2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                            EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when           who         what, where, why
  --------       ---         --------------------------------------------------
  2023/04/28     ananns      Update the state to UPDATE_FAIL when attempt count
                             reaches to EC_FW_UPDATE_ATTEMPT_COUNT_MAX
  2023/04/10     ananns      Changes to print the Flash update end time
  2023/03/13     bkulkarn    Migrate FmpDevicePkg to latest EDK2 version that is
                             getting integrated by UEFI team
  2023/02/23     bkulkarn    Changes to fix reset hook support
  2023/02/04     sumesahu    FR79849: Support for Prepare/Flash/Post/Rollback FMP StateMachine
                             and code refactoring
  2022/12/01     bkulkarn    Reset hook support for EC device firmware update
  2022/11/22     sumesahu    Changes to support A/B partition update
  2022/09/22     bkulkarn    Support for recovery protocol & common state handlers
  2022/07/29     bkulkarn    Initial version
=============================================================================*/

#include <Uefi.h>
#include <Uefi/UefiBaseType.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BootConfig.h>
#include <Library/QcomLib.h>
#include <Library/QcomBaseLib.h>
#include <Library/SecBootSigLib.h>
#include <Protocol/FirmwareManagement.h>
#include <Protocol/GraphicsOutput.h>
#include <Library/ECFwUpdateLib.h>
#include <Library/FwCommonLib/FwUtil_Common.h>

extern EC_DEVICE_CONTEXT *deviceContext;

UINT8 ResetPhaseData[EC_FW_TESTHOOK_MAX] = {0};

// Order of string in below should match with entries of EC_FW_TEST_HOOK_PHASE enum.
const CHAR16 *EcFwUpdatePhaseNames[EC_FW_TESTHOOK_MAX] =
{
  L"PrepareUpdate Phase",
  L"FlashUpdate Phase",
  L"UpdateSuccess Phase",
  L"UpdateFail Phase",
  L"RollbackDone Phase",
  L"RollbackFail Phase"
};

// EC Firmware Progress Update
EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS    mProgressFuncEcDeviceFmp = NULL;

EFI_STATUS
EFIAPI
EcFwUpdateProgress (
  IN  UINTN     Completion
  )
{
  EFI_STATUS Status = EFI_UNSUPPORTED;

  if (NULL == mProgressFuncEcDeviceFmp)
  {
    goto Exit;
  }

  EC_I("- Rendering Progress: %d\n", Completion);
  Status = mProgressFuncEcDeviceFmp(Completion);
  if (EFI_UNSUPPORTED == Status)
  {
    mProgressFuncEcDeviceFmp = NULL;
  }

Exit:
  return Status;
}

/**
 * @brief Function to update progress string of the EC Firmware.
 *
 * @retval EFI_SUCCESS       The update progress is displayed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EFIAPI
EcFwUpdateProgressTextDisplay ()
{
  EFI_STATUS                           status           = EFI_SUCCESS;
  EFI_GRAPHICS_OUTPUT_PROTOCOL        *pGop             = NULL;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL_UNION  foregroundcolour = {0};
  UINT32                               offsetX          = 0;
  UINT32                               offsetY          = 0;
  UINT32                               startX           = 0;
  UINT32                               startY           = 0;
  UINTN                                numOfChars       = 0;
  CHAR16*                              progressString   = 0;

  status = gBS->LocateProtocol (
    &gEfiGraphicsOutputProtocolGuid,
    NULL,
    (VOID **)&pGop
    );
  if (EFI_ERROR (status))
  {
    EC_E("Could not locate GOP, status = %r\n", status);
    status = EFI_NOT_READY;
    goto Cleanup;
  }

  foregroundcolour.Raw = PcdGet32(PcdFmpDeviceForeGroundTextColor);
  progressString = (CHAR16*)PcdGetPtr(PcdFmpDeviceProgressString);

  offsetX = pGop->Mode->Info->HorizontalResolution;
  offsetY = pGop->Mode->Info->VerticalResolution;
  EC_I("offsetX: %d\n", offsetX);
  EC_I("offsetY: %d\n", offsetY);

  startX = ((offsetX - StrLen(progressString) * EFI_GLYPH_WIDTH) / 2);
  EC_I("startX: %d\n", startX);

  startY = ((offsetY * 80) / 100);
  EC_I("startY: %d\n");

  numOfChars = PrintXY(
    startX,
    startY,
    &foregroundcolour.Pixel,
    NULL,
    progressString
    );
  EC_I("numOfChars: %d\n", numOfChars);

Cleanup:
  return status;
}

/**
 * @brief The Entry function for EC Firmware Prepare Update state.
 *
 * @param None
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EcFwStatePrepareUpdateHandler()
{
  EFI_STATUS                    status    = EFI_SUCCESS;
  UINT8                         cycle_ms  = 50;
  UINT8                         max_retry = 5;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  status = EcFwUpdateProgressTextDisplay();
  EC_WARN_HANDLER(status, EcFwUpdateProgressTextDisplay);

  //[TODO]: Disable WP_EN GPIO here to unlock the EC flash access from MSM */

  status = EcFwCheckP1BBKCorruption();
  if (EFI_ERROR(status))
  {
    EC_W("Use predefine to update...\n");
    deviceContext->is_fw_corrupted = 1;
  }
  else
  {
    EC_W("P1BBK is intact\n");
    deviceContext->is_fw_corrupted = 0;
  }

  if (deviceContext->is_fw_corrupted)
  {
    EC_W("Fw is corrupted, switch to recovery protocol\n");
    /* Update internal state variable to use RECOVERY I2C protocol */
    deviceContext->active_protocol  = RECOVERY_I2C_PROTOCOL;
    status = SetNvEcFwActiveProtocolStatus(deviceContext->active_protocol);
    EC_WARN_HANDLER(status, SetNvEcFwActiveProtocolStatus);
    STATE_UPDATE(FLASH_UPDATE, Exit);
  }
  else
  {
    EC_W("Switch to ACPI I2C protocol\n");
    deviceContext->active_protocol = ACPI_I2C_PROTOCOL;
    status = SetNvEcFwActiveProtocolStatus(deviceContext->active_protocol);
    EC_WARN_HANDLER(status, SetNvEcFwActiveProtocolStatus);
  }

  /* Check Fw flash status */
  status = EcCheckFwStatus();
  if (EFI_ERROR(status))
  {
    EC_E("EcCheckFwStatus() failed with %r\n", status);
    STATE_UPDATE(UPDATE_FAIL, Exit);
    goto Exit;
  }

  if (BOOT_BLK != deviceContext->fw_status)
  {
    EC_W("Not in BBK, attempting to enter into BBK\n");

    /*
     * Not treated as error, as we need to check again in the next step,
     * If the FW is really in BBK/MBK and then take the neccessary action.
     */
    status = EcEnterBBK();
    EC_WARN_HANDLER(status, EcEnterBBK);

    status = WaitForEnterIntoBootBlock(cycle_ms, max_retry);
    if (EFI_ERROR(status))
    {
      EC_W("WaitForEnterIntoBootBlock() failed with %r\n", status);
      deviceContext->active_protocol = RECOVERY_I2C_PROTOCOL;
      status = SetNvEcFwActiveProtocolStatus(deviceContext->active_protocol);
      EC_WARN_HANDLER(status, SetNvEcFwActiveProtocolStatus);
      STATE_UPDATE(FLASH_UPDATE, Exit);
    }
    deviceContext->fw_status = BOOT_BLK;
  }

  if (ACPI_I2C_PROTOCOL == deviceContext->active_protocol)
  {
    deviceContext->partition_to_update = INTERNAL_FLASH_P1;
  }

  deviceContext->flash_type = deviceContext->partition_to_update;
  status = SetNvEcFwFlashTypeStatus(deviceContext->flash_type);
  EC_WARN_HANDLER(status, SetNvEcFwFlashTypeStatus);
  STATE_UPDATE(FLASH_UPDATE, Exit);

Exit:
  return status;
}

/**
 * @brief The Entry function for EC Firmware Flash Update state.
 *
 * @param None
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EcFwStateFlashUpdateHandler()
{
  EFI_STATUS    status = EFI_SUCCESS;
  EC_TRACE();

  status = EcReflashFirmware();
  if (EFI_ERROR(status))
  {
    EC_E("EcReflashFirmware() failed with %r\n", status);
    STATE_UPDATE(UPDATE_FAIL, Exit);
    goto Exit;
  }

  STATE_UPDATE(UPDATE_SUCCESS, Exit);

Exit:
  return status;
}

/**
 * @brief The Entry function for handling post EC Firmware update state.
 *
 * @param MsftAttemptStatus  Microsoft last attempt status
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EcFwStatePostUpdateHandler(
  OUT UINT32    *MsftAttemptStatus
  )
{
  EFI_STATUS    status = EFI_SUCCESS;

  EC_TRACE();

  if (NULL == MsftAttemptStatus)
  {
    EC_E("Invalid MsftAttemptStatus input parameter!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  status = EcPostFwUpdate();
  if (EFI_ERROR(status))
  {
    EC_E("EcPostFwUpdate() failed with %r\n", status);
    STATE_UPDATE(UPDATE_FAIL, Exit);
    goto Exit;
  }

  *MsftAttemptStatus = LAST_ATTEMPT_STATUS_SUCCESS;

Exit:
  return status;
}

/**
 * @brief The Entry function for handling EC Firmware update rollback state.
 *
 * @param None
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EcFwStateRollbackHandler()
{
  EFI_STATUS                status = EFI_SUCCESS;
  UINT8                     rollback_cmd = 0;
  EC_FLASH_PARTITION_INFO   flashType    = 0;

  EC_TRACE();

  if (!deviceContext)
  {
    EC_E("EC device is not initialized!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  if (!deviceContext->flash_type)
  {
    status = GetNvEcFwFlashTypeStatus((UINT8 *)&flashType);
    EC_ERROR_HANDLER(status, GetNvEcFwFlashTypeStatus, Exit);
    deviceContext->flash_type = flashType;
    deviceContext->partition_to_update = deviceContext->flash_type;
  }
  
  if (!deviceContext->corruption_status)
  {
    status = GetEcFwCorruptionStatus(
      &deviceContext->corruption_status);
    EC_ERROR_HANDLER(status, GetEcFwCorruptionStatus, Exit);
  }

  if (deviceContext->corruption_status == 0)
  {
    EC_E("Either older FW or P1, P2 Partition may be corrupted!!\n");
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  /**
   * 1. Trigger recovery(copy) from back-up partition to active.
   * 2. Calculate the checksum of active partition.
   */
  EC_W("Partition to Update: %d\n", deviceContext->partition_to_update);
  if ((INTERNAL_FLASH_P1 == deviceContext->partition_to_update) &&
    IS_PARTITION_VALID(deviceContext->corruption_status, P2_MBK))
  {
    rollback_cmd  = COPY_INT_P2MBK_TO_P1;
    flashType = INTERNAL_FLASH_P2;
    EC_E("Rollback will start from P2 to P1\n");
  }
  else if (INTERNAL_FLASH_P2 == deviceContext->partition_to_update &&
    IS_PARTITION_VALID(deviceContext->corruption_status, P1_MBK))
  {
    rollback_cmd  = COPY_INT_P1MBK_TO_P2;
    flashType = INTERNAL_FLASH_P1;
    EC_E("Rollback will start from P1 to P2\n");
  }
  else
  {
    EC_E("Unknown Partition to update (%d)\n",
      deviceContext->partition_to_update);
    status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  status = EcFirmwareSync(rollback_cmd, flashType);
  if (EFI_ERROR(status))
  {
    EC_E("EcFirmwareRollback() failed with %r \n", status);
    goto Exit;
  }

  STATE_UPDATE(ROLLBACK_DONE, Exit);

Exit:
  if (EFI_ERROR(status))
  {
    STATE_UPDATE(ROLLBACK_FAIL, Exit);
  }

  return status;
}

/**
 * @brief The entry Point for EC FirmwareUpdate state machine.
 *
 * @param Image              Image to update
 * @param Image              Size of the image to update
 * @param MsftAttemptStatus  Microsoft last attempt status
 * @param Progress           cb function ptr to report the Progress of FW update.
 *
 * @retval EFI_SUCCESS       The entry point is executed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EFIAPI
EcFwUpdateMain (
  IN  CONST VOID                                   *Image,
  IN  UINTN                                         ImageSize,
  OUT UINT32                                       *MsftAttemptStatus,
  IN  EFI_FIRMWARE_MANAGEMENT_UPDATE_IMAGE_PROGRESS Progress    OPTIONAL
  )
{
  EFI_STATUS                    status       = EFI_SUCCESS;
  EFI_STATUS                    PhaseStatus  = EFI_SUCCESS;
  UINT8                         AttemptCnt   = 0;
  EC_FW_UPDATE_STATE_VARIABLE   UpdateState  = EC_FW_STATE_NOT_IN_PROGRESS;

  EC_TRACE();

  if ((NULL == Image) ||
      (NULL == MsftAttemptStatus ))
  {
    EC_E("One or more input parameters are NULL.\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  *MsftAttemptStatus = LAST_ATTEMPT_STATUS_ERROR_UNSUCCESSFUL;

  status = GetNvEcFwAttemptCount(&AttemptCnt);
  if (EFI_ERROR(status))
  {
    EC_E("Failed to get EC FW Update attempt count from NV\n");
    if (status == EFI_NOT_FOUND)
    {
      status = SetNvEcFwAttemptCount(0);
    }
    AttemptCnt = 0;
  }

  if (AttemptCnt <= EC_FW_UPDATE_ATTEMPT_COUNT_MAX)
  {
    AttemptCnt++;
  }
  EC_W("\n Current EC FW update attempt count is: %d\n", AttemptCnt);

  status = GetNvEcFwUpdateState(&UpdateState);
  if (UpdateState == EC_FW_STATE_NOT_IN_PROGRESS)
  {
    STATE_UPDATE(PREPARE_UPDATE, Exit);
  }

  status = SetNvEcFwAttemptCount(AttemptCnt);
  if (EFI_ERROR(status))
  {
    EC_E("SetNvEcFwAttemptCount() failed with %r\n", status);
    AttemptCnt = 0;
    goto Exit;
  }

  while (1)
  {
    status = GetNvEcFwUpdateState(&UpdateState) ;
    EC_ERROR_HANDLER(status, GetNvEcFwUpdateState, Exit);

    status = GetNvEcFwAttemptCount(&AttemptCnt);
    if (EFI_ERROR(status))
    {
      AttemptCnt = 0;
    }

    /*
     * If update is in progress and update attempt limit is reached, perform a rollback.
     */
    if ((AttemptCnt > EC_FW_UPDATE_ATTEMPT_COUNT_MAX) &&
      (EC_FW_STATE_ROLLBACK_FAIL != UpdateState) &&
      (EC_FW_STATE_ROLLBACK_DONE != UpdateState))
    {
      if (EC_FW_STATE_PREPARE_UPDATE == UpdateState)
      {
        status = EFI_DEVICE_ERROR;
        EC_E("Aborting update, as reached update attempt limit!\n");
        goto Exit;
      }
      else
      {
        STATE_UPDATE(UPDATE_FAIL, Exit);
        EC_E("AttemptCount exceeded!! Aborting Update & Initiating Rollback!!\n");
      }
    }

    status = GetEcFwTestHookData();
    if (EFI_ERROR(status))
    {
      /*
       * Fill with the default value so that no reset is
       * triggered when variable not found.
       */
      SetMem(
        &ResetPhaseData,
        sizeof(ResetPhaseData),
        NO_RESET_IN_CURRENT_EC_FW_UPDATE_PHASE);
      status = EFI_SUCCESS;
    }

    status = GetNvEcFwUpdateState(&UpdateState) ;
    EC_ERROR_HANDLER(status, GetNvEcFwUpdateState, Exit);

    switch (UpdateState)
    {
      case EC_FW_STATE_PREPARE_UPDATE:
        EC_W("\n EC FW Prepare Update Start. Time (ms): %lld\n",
          GetTimerCountms());
        EcFwUpdateProgress(PROGRESS_EC_FW_CAPSULE_PREPARE_START);

        ClearHookPhaseDataAndTriggerReset(
          EC_FW_TESTHOOK_PREPARE_UPDATE_PHASE,
          1,
          MAX_ALLOWED_EC_FW_ENTRIES);

        status = EcFwStatePrepareUpdateHandler();
        EC_ERROR_HANDLER(status, EcFwStatePrepareUpdateHandler, Exit);

        EcFwUpdateProgress(PROGRESS_EC_FW_CAPSULE_PREPARE_END);
        EC_W("\n EC FW Prepare Update End. Time (ms): %lld\n",
          GetTimerCountms());
        break;

      case EC_FW_STATE_FLASH_UPDATE:
        EC_W("\n EC FW Post Prepare Update Start. Time (ms): %lld\n\n",
          GetTimerCountms());
        EcFwUpdateProgress(PROGRESS_EC_FW_CAPSULE_FLASH_UPDATE_START);

        ClearHookPhaseDataAndTriggerReset(
          EC_FW_TESTHOOK_FLASH_UPDATE_PHASE,
          1,
          MAX_ALLOWED_EC_FW_ENTRIES);

        status = EcFwStateFlashUpdateHandler();
        EC_ERROR_HANDLER(status, EcFwStateFlashUpdateHandler, Exit);

        EcFwUpdateProgress(PROGRESS_EC_FW_CAPSULE_FLASH_UPDATE_END);
        EC_W("\n EC FW Update End. Time (ms): %lld\n\n",
          GetTimerCountms());
        break;

      case EC_FW_STATE_UPDATE_SUCCESS:
        EC_W("\n EC FW Post Update Success Start. Time (ms): %lld\n",
          GetTimerCountms());
        EcFwUpdateProgress(PROGRESS_EC_FW_CAPSULE_UPDATE_SUCCESS);

        ClearHookPhaseDataAndTriggerReset(
          EC_FW_TESTHOOK_UPDATE_SUCCESS_PHASE,
          1,
          MAX_ALLOWED_EC_FW_ENTRIES);

        status = EcFwStatePostUpdateHandler(MsftAttemptStatus);
        EC_ERROR_HANDLER(status, EcFwStatePostUpdateHandler, Exit);

        EcFwUpdateProgress(PROGRESS_EC_FW_CAPSULE_UPDATE_PROCESS_COMPLETE);
        EC_W("\n EC FW Post Update Success End. Time (ms): %lld\n",
          GetTimerCountms());

        // Exit the state-machine in case of successful firmware update .
        goto Exit;

      case EC_FW_STATE_UPDATE_FAIL:
        EC_W("\n EC FW Update Fail and Rollback Started. Time (ms): %lld\n",
          GetTimerCountms());

        ClearHookPhaseDataAndTriggerReset(
          EC_FW_TESTHOOK_UPDATE_FAIL_PHASE,
          1,
          MAX_ALLOWED_EC_FW_ENTRIES);

        status = EcFwStateRollbackHandler();
        PhaseStatus = EFI_DEVICE_ERROR;
        EC_W("\n EC FW Update Fail and Rollback End. Time (ms): %lld\n",
          GetTimerCountms());
        EC_ERROR_HANDLER(status, EcFwStateRollbackHandler, Exit);
        break;

      case EC_FW_STATE_ROLLBACK_DONE:
        EC_W("\n EC FW Rollback Done Start. Time (ms): %lld\n",
          GetTimerCountms());
        STATE_UPDATE(PREPARE_UPDATE, Exit);

        // Update the phase-status to error to indicate the update status is reported as failure.
        if (EFI_SUCCESS == PhaseStatus)
        {
          PhaseStatus = EFI_DEVICE_ERROR;
        }

        EC_W("\n EC FW Rollback Done End. Time (ms): %lld\n",
          GetTimerCountms());
        goto Exit;

      case EC_FW_STATE_ROLLBACK_FAIL:
        EC_W("\n EC FW Rollback Fail Start. Time (ms): %lld\n",
          GetTimerCountms());

        ClearHookPhaseDataAndTriggerReset(
          EC_FW_TESTHOOK_ROLLBACK_FAIL_PHASE,
          1,
          MAX_ALLOWED_EC_FW_ENTRIES);

        PhaseStatus = EFI_LOAD_ERROR;

        EC_W("\n EC FW Rollback Fail End. Time (ms): %lld\n",
          GetTimerCountms());
        goto Exit;

      default:
        EC_E("Invalid EC FW update state: %d!\n", UpdateState);
        status = EFI_LOAD_ERROR;
        goto Exit;
    }

    // Preserve the first error encountered
    PhaseStatus = EFI_ERROR(PhaseStatus) ? PhaseStatus : status;
  }

Exit:
  EC_W("PhaseStatus: %r, status: %r\n",PhaseStatus, status);
  return (EFI_ERROR(PhaseStatus) ? PhaseStatus : status);
}

/**
 * @brief Function to read the NV test hook variable for EC firmware
 * and fill in the "ResetPhaseData" data structure.
 *
 * @param  none
 *
 * @retval status    A EFI_STATUS indicating result of the operation.
 */
EFI_STATUS
GetEcFwTestHookData(
  )
{
  EFI_STATUS    status = EFI_SUCCESS;
  UINTN         ResetPhaseDataSize = 0;

  ResetPhaseDataSize = sizeof(ResetPhaseData);

  status = gRT->GetVariable (
    RESET_EC_FW_PHASE_DATA_NV,
    &gQcomTokenSpaceGuid,
    NULL,
    &ResetPhaseDataSize,
    &ResetPhaseData
    );
  EC_ERROR_HANDLER(status, GetVariable, Exit);
  if (ResetPhaseDataSize != sizeof (ResetPhaseData))
  {
    EC_E("Failed to get ResetPhase test hook data. Size mismatch!!\n",
      status);
    goto Exit;
  }

Exit:
  return status;
}

/**
 *  @brief Function will reset the respective test hook variable and
 *  reset the device. Input of CurrentPhaseResetEntry value shall
 *  be with respective to CurrentPhase.
 *
 * @param CurrentPhase                      Used to differentiate the phase.
 * @param CurrentFwEntryCount               Current index value.
 * @param TotalFwEntries                    Max Fw Entry value in Capsule payload
 *
 * @return    None
 */
VOID
ClearHookPhaseDataAndTriggerReset (
  IN EC_FW_TEST_HOOK_PHASE     CurrentPhase,
  IN UINTN                     CurrentFwEntryCount,
  IN UINTN                     TotalFwEntries
  )
{
  EFI_STATUS    status = EFI_SUCCESS;
  BOOLEAN       IsResetRequired = FALSE;
  BOOLEAN       ResetCurrentPhaseInNV = FALSE;
  EC_TRACE();

  if (CurrentPhase >= EC_FW_TESTHOOK_MAX)
  {
    status = EFI_INVALID_PARAMETER;
    EC_E("Invalid CurrentPhase %d!\n", CurrentPhase);
    goto Exit;
  }

  if (NO_RESET_IN_CURRENT_EC_FW_UPDATE_PHASE == ResetPhaseData[CurrentPhase])
  {
    /*
     * Return as current phase is not configured to reset for any firmware entry count
     */
    EC_W("No reset phase data is configured!\n");
    goto Exit;
  }

  /*
   * Check if user have requested for a reset for a firmware
   * entry count that is larger than the maximum number of firmware
   * entries in the current payload. If yes, reset the setting and
   * skip the reset operation
   */
  if (TotalFwEntries < ResetPhaseData[CurrentPhase])
  {
    ResetCurrentPhaseInNV = TRUE;
    IsResetRequired = FALSE;

    EC_W("Reset skipped during %s, as the Fw entry count \
      %d configured for reset, exceeds \n",
      EcFwUpdatePhaseNames[CurrentPhase],
      ResetPhaseData[CurrentPhase]);
    EC_W("the maximum number of firmware enries in current payload %d \n",
      TotalFwEntries);
  }

  /*
   * Check if current firmware entry is the one recorded in
   * reset data. If yes, enable reset and enable clearing this
   * setting in NV
   */
  if (CurrentFwEntryCount == ResetPhaseData[CurrentPhase])
  {
    ResetCurrentPhaseInNV = TRUE;
    IsResetRequired = TRUE;
  }

  if (ResetCurrentPhaseInNV)
  {
    ResetPhaseData[CurrentPhase] = NO_RESET_IN_CURRENT_EC_FW_UPDATE_PHASE;
    status = gRT->SetVariable(
      RESET_EC_FW_PHASE_DATA_NV,
      &gQcomTokenSpaceGuid,
      EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
      sizeof(ResetPhaseData),
      &ResetPhaseData
      );
    EC_ERROR_HANDLER(status, SetVariable, Exit);

    FlushVariableServicesIfSupported();
  }

  if (IsResetRequired)
  {
    EC_W("\n Resetting the device during %s, \
      at start of firmware entry count '%d'\n",
      EcFwUpdatePhaseNames[CurrentPhase],
      CurrentFwEntryCount);

    for (UINTN Index = 5; Index > 0; Index--)
    {
      Print(L"Resetting system in %d seconds ...\n", Index);
      EC_W("Resetting system in %d seconds ...\n", Index);
      gBS->Stall(1000000);
    }

    gRT->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);

    CpuDeadLoop();
  }

Exit:
  EC_I("Status: %r\n", status);
  return;
}

/**
 * @brief Function will set the Reset test hook phase NV variable
 * @brief To NO_RESET_IN_CURRENT_EC_FW_UPDATE_PHASE.
 *
 * @param  None
 * @retval status    A EFI_STATUS indicating result of the operation.
 */
EFI_STATUS
ResetEcFwHookEntryToDefault()
{
  EFI_STATUS    status = EFI_SUCCESS;

  SetMem(
    &ResetPhaseData,
    sizeof(ResetPhaseData),
    NO_RESET_IN_CURRENT_EC_FW_UPDATE_PHASE);

  status = gRT->SetVariable (
    RESET_EC_FW_PHASE_DATA_NV,
    &gQcomTokenSpaceGuid,
    EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
    sizeof(ResetPhaseData),
    &ResetPhaseData);
  EC_WARN_HANDLER(status, SetVariable);

return status;
}