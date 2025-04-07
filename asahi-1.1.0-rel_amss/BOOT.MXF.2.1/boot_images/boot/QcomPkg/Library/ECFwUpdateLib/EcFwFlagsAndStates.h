/** @file EcFwFlagsAndStates.h

  Header file for EcFwFlagsAndStates.c

  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                            EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when           who         what, where, why
  --------       ---         --------------------------------------------------
  2023/02/23     bkulkarn    Support to query & update EC device status in NV and code refactoring
  2023/02/04     sumesahu    FR79849: Support for Prepare/Flash/Post/Rollback FMP StateMachine
                             and code refactoring
  2022/12/01     bkulkarn    Reset hook support for EC device firmware update.
  2022/07/29     sumesahu    Initial version
=============================================================================*/

#ifndef __ECFWFLAGSANDSTATES_H__
#define __ECFWFLAGSANDSTATES_H__

#include "Uefi.h"

//-------------------EC FW update NV items section start ------------------
#define EC_FW_UPDATE_NV_EC_FW_VERSION_NAME                          L"EC_FW_VERSION"
#define EC_FW_UPDATE_NV_EC_FW_VERSION_NAME_SIZE                     (sizeof (UINT32))

#define EC_FW_UPDATE_NV_EC_LS_FW_VERSION_NAME                       L"EC_LS_FW_VERSION"
#define EC_FW_UPDATE_NV_EC_LS_FW_VERSION_NAME_SIZE                  (sizeof (UINT32))

#define EC_FW_UPDATE_NV_UPDATE_STATE_NAME                           L"EC_UPDATE_STATE"
#define EC_FW_UPDATE_NV_UPDATE_STATE_SIZE                           (sizeof (EC_FW_UPDATE_STATE_VARIABLE))

#define EC_FW_UPDATE_NV_ATTEMPT_COUNT_NAME                          L"EC_ATTEMPT_COUNT"
#define EC_FW_UPDATE_NV_ATTEMPT_COUNT_SIZE                          (sizeof (UINT8))

#define EC_FW_UPDATE_NV_WP_EN_STATUS_NAME                           L"EC_WP_EN_STATUS"
#define EC_FW_UPDATE_NV_WP_EN_STATUS_SIZE                           (128)

#define EC_FW_UPDATE_NV_ACTV_PROTOCOL_STATUS_NAME                   L"EC_ACTV_PROTOCOL_STATUS"
#define EC_FW_UPDATE_NV_ACTV_PROTOCOL_STATUS_SIZE                   (sizeof (UINT8))

#define EC_FW_UPDATE_NV_FLASH_TYPE_STATUS_NAME                      L"EC_FLASH_TYPE_STATUS"
#define EC_FW_UPDATE_NV_FLASH_TYPE_STATUS_SIZE                      (sizeof (UINT8))

#define EC_FW_UPDATE_NV_DEVICE_STATUS_NAME                          L"EC_DEVICE_STATUS"
#define EC_FW_UPDATE_NV_DEVICE_STATUS_SIZE                          (sizeof (UINT8))

#define NO_RESET_IN_CURRENT_EC_FW_UPDATE_PHASE                       (0xFF)
#define MAX_ALLOWED_EC_FW_ENTRIES                                    (1)
#define RESET_EC_FW_PHASE_DATA_NV                                    L"ResetEcFwPhaseDataNV"
//-------------------EC FW update NV items section end --------------------

typedef enum
{
  EC_FW_STATE_NOT_IN_PROGRESS,
  EC_FW_STATE_PREPARE_UPDATE,
  EC_FW_STATE_FLASH_UPDATE,
  EC_FW_STATE_UPDATE_SUCCESS,
  EC_FW_STATE_UPDATE_FAIL,
  EC_FW_STATE_ROLLBACK_DONE,
  EC_FW_STATE_ROLLBACK_FAIL,
} EC_FW_UPDATE_STATE_VARIABLE;

typedef enum
{
  EC_FW_UPDATE_NV_EC_FW_VERSION,
  EC_FW_UPDATE_NV_EC_LS_FW_VERSION,
  EC_FW_UPDATE_NV_UPDATE_STATE,
  EC_FW_UPDATE_NV_ATTEMPT_COUNT,
  EC_FW_UPDATE_NV_WP_EN_STATUS,
  EC_FW_UPDATE_NV_ACTV_PROTOCOL_STATUS,
  EC_FW_UPDATE_NV_FLASH_TYPE_STATUS,
  EC_FW_UPDATE_NV_DEVICE_STATUS,
  EC_FW_UPDATE_NV_MAX
}EC_FW_UPDATE_NV_TYPE;

typedef enum
{
  EC_FW_UPDATE_GET_NV_DATA,
  EC_FW_UPDATE_SET_NV_DATA_FLUSH,
  EC_FW_UPDATE_SET_NV_DATA_NO_FLUSH
}EC_FW_UPDATE_GET_SET;

typedef enum
{
  EC_FW_TESTHOOK_PREPARE_UPDATE_PHASE,
  EC_FW_TESTHOOK_FLASH_UPDATE_PHASE,
  EC_FW_TESTHOOK_UPDATE_SUCCESS_PHASE,
  EC_FW_TESTHOOK_UPDATE_FAIL_PHASE,
  EC_FW_TESTHOOK_ROLLBACK_DONE_PHASE,
  EC_FW_TESTHOOK_ROLLBACK_FAIL_PHASE,
  EC_FW_TESTHOOK_MAX
}EC_FW_TEST_HOOK_PHASE;

typedef struct
{
  EC_FW_UPDATE_NV_TYPE    Type;
  UINT16                  *Name;
  UINTN                   Size;
  UINT32                  Attributes;
}EC_FW_UPDATE_NV_IDENTIFIER;

/**
 * Read the current state from non-volatile memory
 *
 * @param  State      -  Output STATE_VARIABLE
 *
 * @return EFI_STATUS
 *
 */
EFI_STATUS
GetNvEcFwUpdateState(
  OUT EC_FW_UPDATE_STATE_VARIABLE *State
  );

/**
 * Read the update attempt count from non-volatile memory
 *
 * @param  cnt      -  Output attempt count
 *
 * @return EFI_STATUS
 *
 */
EFI_STATUS
GetNvEcFwAttemptCount(
  OUT UINT8 *cnt
  );

/**
 * This function updates the state flag in non-volatile memory for future retrieval.
 *
 * @param State         - State of the EC FW update that needs to be updated
 * @param UpdateReason  - Optional EC FW update reason that needs to be updated
 *
 * @return EFI_STATUS
 */
EFI_STATUS
SetNvEcFwUpdateState(
  IN EC_FW_UPDATE_STATE_VARIABLE State
  );


/**
 * *********This function should be called during boot time only**************
 * ******************for boot time optimization*******************************
 * This function updates state and/or update reason in non-volatile memory without flushing.
 *
 * @param State         - State of the EC FW update that needs to be updated
 * @param UpdateReason  - Optional EC FW update reason that needs to be updated
 *
 * @return EFI_STATUS
 */
EFI_STATUS
SetNvEcFwUpdateStateDonotFlush(
  IN EC_FW_UPDATE_STATE_VARIABLE State
  );

/**
 * This function updates the attempt count in non-volatile memory.
 * Make sure after the write a flush command is issued to clear
 * the FS cache
 *
 * @param AttemptCnt       - attempt count to update in the FS
 *
 * @return EFI_STATUS
 */
EFI_STATUS
SetNvEcFwAttemptCount(
  IN UINT8 AttemptCnt
  );

/**
 * *********This function should be called during boot time only**************
 * ******************for boot time optimization*******************************
 * This function updates the attempt count in non-volatile memory.
 * Make sure after the write a flush command is issued to clear
 * the FS cache without flushing
 *
 * @param AttemptCnt       - attempt count to update in the FS
 *
 * @return EFI_STATUS
 */

EFI_STATUS
SetNvEcFwAttemptCountDonotFlush(
  IN UINT8 AttemptCnt
  );

/**
 * This function updates the EC FW version in non-volatile memory.
 * Make sure after the write a flush command is issued to clear
 * the FS cache
 *
 * @param Version       - FW version to be updated in the FS
 *
 * @return EFI_STATUS
 */
EFI_STATUS
SetNvEcFwVersion(
  UINT32 Version
  );

/**
 * This function gets the EC FW version from non-volatile memory.
 *
 * @param Version       - FW version to be updated in the FS
 *
 * @return EFI_STATUS
 */
EFI_STATUS
GetNvEcFwVersion(
  OUT UINT32 *Version
  );

/**
 * This function updates the EC Lowest Supported (LS) FW version in non-volatile memory.
 * Make sure after the write a flush command is issued to clear
 * the FS cache
 *
 * @param Version       - FW version to be updated in the FS
 *
 * @return EFI_STATUS
 */
EFI_STATUS
SetNvEcLsFwVersion(
  UINT32 Version
  );

/**
 * This function gets the EC Lowest Supported (LS) FW version from non-volatile memory.
 *
 * @param Version       - FW version to be updated in the FS
 *
 * @return EFI_STATUS
 */
EFI_STATUS
GetNvEcLsFwVersion(
  OUT UINT32 *Version
  );

/**
 * Gets or Sets EC related NV data of given type
 *
 * @param NVType - NV to Read/Modify
 * @param Value - Value to set/Value Returned from read.
 * @param ValueSize - Size of the Value to set/Size of the Value Returned from read.
 * @param Operation - Get or Set with flush or Set with no flush NV Data
 *
 @retval EFI_SUCCESS            On successful operation
 @retval EFI_BUFFER_TOO_SMALL   Requested NV type holds larger data than expected.
 */
EFI_STATUS
GetOrSetEcNVData(
  IN     EC_FW_UPDATE_NV_TYPE       NVType,
  IN OUT VOID                       **Value,
  IN OUT UINTN                      *ValueSize,
  IN     EC_FW_UPDATE_GET_SET       Operation
  );

/**
 * Check if the NV variables related to firmware update
 * is present. Else create those with default values
 *
 * @return EFI_STATUS
 */
EFI_STATUS
CheckAndCreateEcNVData(
  VOID
  );

/**
 * This function updates the EC Write-Protection Sttaus in to the non-volatile memory.
 * Make sure after the write a flush command is issued to clear
 * the FS cache
 *
 * @param WriteProtectStatus       - Indicates the current write-protection status to be updated.
 *
 * @return EFI_STATUS
 */
EFI_STATUS
SetNvEcWriteProtectStatus(
  UINT32 WriteProtectStatus
  );

/**
 * This function gets the EC Write-Protection Sttaus from non-volatile memory.
 * Make sure after the write a flush command is issued to clear
 * the FS cache
 *
 * @param IsWriteProtectEnabled      - Output variable to store the current write-protection status
 *
 * @return EFI_STATUS
 */
EFI_STATUS
GetNvEcWriteProtectStatus(
  OUT UINT32 *IsWriteProtectEnabled
  );

/**
 * @brief This function updates the Active i2c Protocol in NV memory.
 *
 * @param ActiveProtocolStatus   - Active i2c Protocol to update in the NV memory
 *
 * @return EFI_STATUS  - Status value indicating result of the operation.
 */
EFI_STATUS
SetNvEcFwActiveProtocolStatus(
  IN UINT8 ActiveProtocolStatus
  );

/**
 * @brief This function reads the Active Protocol status in NV memory.
 *
 * @param ActiveProtocolStatus - Contains the Active Protocol device status to be updated in NV memory.
 *
 * @return EFI_STATUS  - Status value indicating result of the operation.
 */
EFI_STATUS
GetNvEcFwActiveProtocolStatus(
  OUT UINT8 *ActiveProtocolStatus
  );

/**
 * @brief This function updates the Active i2c Protocol in NV memory for future retrieval
 * without flushing.
 *
 * @param ActiveProtocolStatus   - Active i2c Protocol to update in the NV memory
 *
 * @return EFI_STATUS  - Status value indicating result of the operation.
 */
EFI_STATUS
SetNvEcFwActiveProtocolStatusDonotFlush(
  IN UINT8 ActiveProtocolStatus
  );

/**
 * @brief This function updates the EC Flash type in NV memory.
 *
 * @param FlashTypeStatus   - EC flash Type to update in the NV memory
 *
 * @return EFI_STATUS  - Status value indicating result of the operation.
 */
EFI_STATUS
SetNvEcFwFlashTypeStatus(
  IN UINT8 FlashTypeStatus
  );

/**
 * @brief This function reads the ec flash type device status in NV memory.
 *
 * @param FlashTypeStatus - Contains the EC Flash Type device status to be updated in NV memory.
 *
 * @return EFI_STATUS  - Status value indicating result of the operation.
 */
EFI_STATUS
GetNvEcFwFlashTypeStatus(
  OUT UINT8 *FlashTypeStatus
  );

/**
 * @brief This function updates the EC Flash type in NV memory for future retrieval
 * without flushing.
 *
 * @param FlashTypeStatus   - EC flash Type to update in the NV memory
 *
 * @return EFI_STATUS  - Status value indicating result of the operation.
 */
EFI_STATUS
SetNvEcFwFlashTypeStatusDonotFlush(
  IN UINT8 FlashTypeStatus
  );

/**
 * @brief This function updates the ec device status in non-volatile memory.
 *
 * @param DeviceStatus - Contains the EC device status to be updated in memory.
 *
 * @return EFI_STATUS  - Status value indicating result of the operation.
 */
EFI_STATUS
SetNvEcDeviceStatus(
  IN UINT8 DeviceStatus
  );

/**
 * @brief This function reads the ec device status in non-volatile memory.
 *
 * @param DeviceStatus - Contains the EC device status to be updated in memory.
 *
 * @return EFI_STATUS  - Status value indicating result of the operation.
 */
EFI_STATUS
GetNvEcDeviceStatus(
  OUT UINT8 *DeviceStatus
  );

/**
 * *********This function should be called during boot time only**************
 * ******************for boot time optimization*******************************
 * @brief This function updates the ec device status in non-volatile memory without flushing.
 *
 * @param DeviceStatus - Contains the EC device status to be updated in memory.
 *
 * @return EFI_STATUS  - Status value indicating result of the operation.
 */
EFI_STATUS
SetNvEcDeviceStatusDonotFlush(
  IN UINT8 DeviceStatus
  );
#endif

