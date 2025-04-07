/** @file EcUpdateStateMachine.h

  Header for EC FW Update State Machine services.

  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                            EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when           who         what, where, why
  --------       ---         --------------------------------------------------
  2023/04/28     ananns      Fixed the IS_PARTITION_VALID macro logic
  2023/02/04     sumesahu    FR79849: Support for Prepare/Flash/Post/Rollback FMP StateMachine
                             and code refactoring
  2022/12/01     bkulkarn    Reset hook support for EC device firmware update.
  2022/07/29     bkulkarn    Initial version
=============================================================================*/

#ifndef _ECUPDATESTATEMACHINE_H
#define _ECUPDATESTATEMACHINE_H

#include <Uefi.h>
#include <Protocol/FirmwareManagement.h>

/**
 * EC FW Capsule update progress values (in %),
 * start and end values edited here will reflect in the update progress bar.
 */
#define PROGRESS_EC_FW_CAPSULE_PREPARE_START                01
#define PROGRESS_EC_FW_CAPSULE_PREPARE_END                  10
#define PROGRESS_EC_FW_CAPSULE_FLASH_UPDATE_START           11
#define PROGRESS_EC_FW_CAPSULE_FLASH_UPDATE_END             18
#define PROGRESS_EC_FW_CAPSULE_UPDATE_SUCCESS               23
#define PROGRESS_EC_FW_CAPSULE_UPDATE_START                 25
#define PROGRESS_EC_FW_CAPSULE_ERASE_START                  30
#define PROGRESS_EC_FW_CAPSULE_ERASE_END                    45
#define PROGRESS_EC_FW_CAPSULE_UPDATE_END                   90
#define PROGRESS_EC_FW_CAPSULE_UPDATE_PROCESS_COMPLETE      100

#define STATE_UPDATE(FLAG, LABEL)                                                       \
  do {                                                                                  \
        EC_FW_UPDATE_STATE_VARIABLE TempUpdateState = EC_FW_STATE_##FLAG;               \
        status = SetNvEcFwUpdateState(TempUpdateState);                                 \
        if (EFI_ERROR(status))                                                          \
        {                                                                               \
          EC_E("SetNvEcFwUpdateState failed with %r\n", status);                        \
          goto LABEL;                                                                   \
        }                                                                               \
  } while (0)

#define IS_PARTITION_VALID(CORRUPTION_STATUS, PARTITION) \
  ((CORRUPTION_STATUS) & (PARTITION))
/**
 * The entry Point for EC FirmwareUpdate.
 *
 * @param Image              -Image to update
 * @param Image              -Size of the image to update
 * @param Progress           -cb function ptr to report the Progress of FW update.
 * @param MsftAttemptStatus  -Microsoft last attempt status
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
  );

/**
 * Callback funtion to report the process of the EC Firmware update.
 * Wrap the caller's version in this so that progress from the device lib is within the expected range.
 *
 * @param   Completion    A value between 1 and 100 indicating the current completion
 * progress of the firmware update. Completion progress is
 * reported as from 1 to 100 percent. A value of 0 is used by
 * the driver to indicate that progress reporting is not supported.
 *
 * @param  None
 * @retval EFI_SUCCESS       SetImage() continues to do the callback if supported.
 * @retval other             SetImage() discontinues the callback and completes
 * the update and returns.
**/
EFI_STATUS
EFIAPI
EcFwUpdateProgress (
  IN  UINTN Completion
  );

/**
 * Function to update progress string of the EC Firmware.
 *
 * @retval EFI_SUCCESS       The update progress is displayed successfully.
 * @retval other             Some error occurs when executing this entry point.
 *
 **/
EFI_STATUS
EFIAPI
EcFwUpdateProgressTextDisplay (
  );

/**
 *  Function will set the reset test hook phase NV variable
 *  to NO_RESET_IN_CURRENT_EC_FW_UPDATE_PHASE.
 *
 * @param  None
 *
 * @retval EFI_STATUS Indicating result of the operation.
 */
EFI_STATUS
ResetEcFwHookEntryToDefault(
  );

/**
 * Function to read the NV test hook variable for EC firmware
 * and fill in the "ResetPhaseData" data structure.
 *
 * @param  none
 *
 * @retval status    A EFI_STATUS indicating result of the operation.
 */
EFI_STATUS
GetEcFwTestHookData(
  );

/**
 *  Function will reset the respective test hook variable and
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
  );

/**
 * Function will set the Rest test hook phase NV variable to NO_RESET_IN_CURRENT_EC_FW_UPDATE_PHASE.
 *
 * @param  None
 * @retval status    A EFI_STATUS indicating result of the operation.
 */
EFI_STATUS
ResetEcFwHookEntryToDefault(
  );

#endif
