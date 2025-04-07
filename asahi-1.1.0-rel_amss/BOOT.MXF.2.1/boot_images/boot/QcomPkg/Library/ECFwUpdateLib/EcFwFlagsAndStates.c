/** @file EcFwFlagsAndStates.c

  Provides functions to read/write EC FW update flags and states to NV storage.

  Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

**/
/*=============================================================================
                            EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  when           who         what, where, why
  --------       ---         ----------------------------------------
  2023/02/23     bkulkarn    Support to query & update EC device status in NV and code refactoring
  2023/02/04     sumesahu    FR79849: Support for Prepare/Flash/Post/Rollback FMP StateMachine, code refactoring
  2022/11/22     sumesahu    Changes to update write protection status in NV
  2022/07/29     bkulkarn    Initial version
=============================================================================*/

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BootConfig.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/QcomLib.h>
#include <Guid/GlobalVariable.h>
#include <Library/ECFwUpdateLib.h>
#include "EcFwFlagsAndStates.h"

static const EC_FW_UPDATE_NV_IDENTIFIER EcNVConfigData[EC_FW_UPDATE_NV_MAX] =
{
  {EC_FW_UPDATE_NV_EC_FW_VERSION,         EC_FW_UPDATE_NV_EC_FW_VERSION_NAME,         EC_FW_UPDATE_NV_EC_FW_VERSION_NAME_SIZE,    (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS)},
  {EC_FW_UPDATE_NV_EC_LS_FW_VERSION,      EC_FW_UPDATE_NV_EC_LS_FW_VERSION_NAME,      EC_FW_UPDATE_NV_EC_LS_FW_VERSION_NAME_SIZE, (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS)},
  {EC_FW_UPDATE_NV_UPDATE_STATE,          EC_FW_UPDATE_NV_UPDATE_STATE_NAME,          EC_FW_UPDATE_NV_UPDATE_STATE_SIZE,          (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS)},
  {EC_FW_UPDATE_NV_ATTEMPT_COUNT,         EC_FW_UPDATE_NV_ATTEMPT_COUNT_NAME,         EC_FW_UPDATE_NV_ATTEMPT_COUNT_SIZE,         (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS)},
  {EC_FW_UPDATE_NV_WP_EN_STATUS,          EC_FW_UPDATE_NV_WP_EN_STATUS_NAME,          EC_FW_UPDATE_NV_WP_EN_STATUS_SIZE,          (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS)},
  {EC_FW_UPDATE_NV_ACTV_PROTOCOL_STATUS,  EC_FW_UPDATE_NV_ACTV_PROTOCOL_STATUS_NAME,  EC_FW_UPDATE_NV_ACTV_PROTOCOL_STATUS_SIZE,  (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS)},
  {EC_FW_UPDATE_NV_FLASH_TYPE_STATUS,     EC_FW_UPDATE_NV_FLASH_TYPE_STATUS_NAME,     EC_FW_UPDATE_NV_FLASH_TYPE_STATUS_SIZE,     (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS)},
  {EC_FW_UPDATE_NV_DEVICE_STATUS,         EC_FW_UPDATE_NV_DEVICE_STATUS_NAME,         EC_FW_UPDATE_NV_DEVICE_STATUS_SIZE,         (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS)},
};

extern EFI_GUID gQcomTokenSpaceGuid;

/**
 * @brief Gets or Sets EC related NV data of given type
 *
 * @param NVType - NV to Read/Modify
 * @param Value - Value to set/Value Returned from read.
 * @param ValueSize - Size of the Value to set/Size of the Value Returned from read.
 * @param Operation - Get, Set with flush or Set with no flush NV Data
 *
 * @retval EFI_SUCCESS            On successful operation
 * @retval EFI_BUFFER_TOO_SMALL   Requested NV type holds larger data than expected.
 */
EFI_STATUS
GetOrSetEcNVData(
  IN     EC_FW_UPDATE_NV_TYPE       NVType,
  IN OUT VOID                       **Value,
  IN OUT UINTN                      *ValueSize,
  IN     EC_FW_UPDATE_GET_SET       Operation
  )

{
  EFI_STATUS        status = EFI_SUCCESS;
  static BOOLEAN    skipVariableFlush = FALSE;

  // Check the expected file size
  if ((NVType >= EC_FW_UPDATE_NV_MAX) ||
      (NULL == Value) ||
      (NULL == ValueSize))
  {
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  if (EC_FW_UPDATE_GET_NV_DATA == Operation)
  {
    status = GetVariable2(
      EcNVConfigData[NVType].Name,
      &gQcomTokenSpaceGuid,
      Value,
      ValueSize
      );
    EC_ERROR_HANDLER(status,GetVariable2,Exit);

    if (NULL == *Value)
    {
      status = EFI_LOAD_ERROR;
      EC_E("Error: GetVariable2 returned invalid buffer\n");
      goto Exit;
    }

    if (*ValueSize > EcNVConfigData[NVType].Size)
    {
      status = EFI_BUFFER_TOO_SMALL;
      EC_E("Error: NV size larger than expected value. Expected: %d. Actual Size: %d.\n",
        EcNVConfigData[NVType].Size, *ValueSize);

      if (*Value != NULL)
      {
          FreePool (*Value);
          *Value = NULL;
      }
      goto Exit;
    }
  }
  else
  {
    if (NULL == *Value)
    {
      status = EFI_INVALID_PARAMETER;
      goto Exit;
    }

    status = gRT->SetVariable(
      EcNVConfigData[NVType].Name,
      &gQcomTokenSpaceGuid,
      EcNVConfigData[NVType].Attributes,
      *ValueSize,
      *Value
      );
    EC_ERROR_HANDLER(status, SetVariable, Exit);

    if (EC_FW_UPDATE_SET_NV_DATA_FLUSH == Operation)
    {
       if (FALSE == skipVariableFlush)
       {
         /* On successful write to variable services, trigger a flush
          to ensure it is written to disk without requring a reset. */
         status = FlushVariableServices();
         if (EFI_NOT_FOUND == status)
         {
           /* Skip further attempts to flush assuming that flush
              operation is either not supported or not ready during
              early stage of development */
           skipVariableFlush = TRUE;
           EC_E("FlushVariableServices returned %r. Will skip future calls to FlushVariableServices\n", status);
         }
       }
     }
  }
Exit:
  return status;
}

/**
 * @brief Read the current EC FW update state from non-volatile memory
 *
 * @param  State       -  Pointer to variable to hold the EC FW update state
 *
 * @return EFI_STATUS  - Status value indicating result of the operation.
 */
EFI_STATUS
GetNvEcFwUpdateState(
  OUT EC_FW_UPDATE_STATE_VARIABLE *State
  )
{
  EFI_STATUS status = EFI_SUCCESS;
  UINTN NVSize = 0;
  VOID *NVData = NULL;
  EC_TRACE();

  if (!State)
  {
    EC_E("Invalid State input parameter!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  status = GetOrSetEcNVData(
    EC_FW_UPDATE_NV_UPDATE_STATE,
    &NVData,
    &NVSize,
    EC_FW_UPDATE_GET_NV_DATA
    );
  EC_ERROR_HANDLER(status, GetOrSetEcNVData, Exit);

  if (NVSize > sizeof (*State))
  {
    EC_E("Current Size=%d : Max Expected Size=%d",
      NVSize,
      EcNVConfigData[EC_FW_UPDATE_NV_UPDATE_STATE].Size
      );
    status = EFI_BUFFER_TOO_SMALL;
    goto Exit;
  }

  ZeroMem(State, sizeof(*State));
  CopyMem(State, NVData, NVSize);

Exit:
  if (NULL != NVData)
  {
    FreePool (NVData);
    NVData = NULL;
  }
  return status;
}

/**
 * @brief Read the attempt count from the file in non-volatile memory
 *
 * @param  cnt         -  Pointer to variable to hold the attempt count
 *
 * @return EFI_STATUS  - Status value indicating result of the operation.
 *
 */
EFI_STATUS
GetNvEcFwAttemptCount(
  OUT UINT8 *cnt
  )
{
  EFI_STATUS status = EFI_SUCCESS;
  UINTN NVSize = 0;
  VOID *NVData = NULL;
  EC_TRACE();

  if (!cnt)
  {
    EC_E("Invalid cnt input parameter!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  status = GetOrSetEcNVData(
    EC_FW_UPDATE_NV_ATTEMPT_COUNT,
    &NVData,
    &NVSize,
    EC_FW_UPDATE_GET_NV_DATA
    );
  EC_ERROR_HANDLER(status, GetOrSetEcNVData, Exit);

  if (NVSize > sizeof (*cnt))
  {
    EC_E("Current Size=%d : Max Expected Size=%d",
      NVSize,
      EcNVConfigData[EC_FW_UPDATE_NV_ATTEMPT_COUNT].Size
      );
    status = EFI_BUFFER_TOO_SMALL;
    goto Exit;
  }

  ZeroMem(cnt, sizeof(*cnt));
  CopyMem(cnt, NVData, NVSize);

Exit:
  if (NULL != NVData)
  {
    FreePool (NVData);
    NVData = NULL;
  }
  return status;
}

/**
 * @brief This function updates state in non-volatile memory.
 *
 * @param State         - State of the EC FW update that needs to be
 *                        updated
 * @return EFI_STATUS  - Status value indicating result of the operation.
 */
EFI_STATUS
SetNvEcFwUpdateState(
  IN EC_FW_UPDATE_STATE_VARIABLE State
  )
{
  EFI_STATUS status = EFI_SUCCESS;
  UINTN NVSize = EcNVConfigData[EC_FW_UPDATE_NV_UPDATE_STATE].Size;
  VOID *NVValue = &State;

  EC_TRACE();

  status = GetOrSetEcNVData(
    EC_FW_UPDATE_NV_UPDATE_STATE,
    &NVValue,
    &NVSize,
    EC_FW_UPDATE_SET_NV_DATA_FLUSH
    );
  EC_ERROR_HANDLER(status, GetOrSetEcNVData, Exit);

Exit:
  return status;
}

/**
 * *********This function should be called during boot time only**************
 * ******************for boot time optimization*******************************
 * This function updates the state flag in non-volatile memory for future retrieval
 * without flushing.
 *
 * @param State       - State of the system that needs to be
 *                      updated
 *
 * @return EFI_STATUS
 */
EFI_STATUS
SetNvEcFwUpdateStateDonotFlush(
  IN EC_FW_UPDATE_STATE_VARIABLE State
  )
{
  EFI_STATUS status = EFI_SUCCESS;
  UINTN NVSize = EcNVConfigData[EC_FW_UPDATE_NV_UPDATE_STATE].Size;
  VOID *NVValue = &State;

  EC_TRACE();

  status = GetOrSetEcNVData(
    EC_FW_UPDATE_NV_UPDATE_STATE,
    &NVValue,
    &NVSize,
    EC_FW_UPDATE_SET_NV_DATA_NO_FLUSH
    );
  EC_ERROR_HANDLER(status, GetOrSetEcNVData, Exit);

Exit:
  return status;
}

/**
 * This function updates the attempt count in non-volatile memory.
 *
 * @param AttemptCnt       - attempt count to update in the non-volatile memory
 *
 * @return EFI_STATUS
 */
EFI_STATUS
SetNvEcFwAttemptCount(
  IN UINT8 AttemptCnt
  )
{
  UINTN NVSize = EcNVConfigData[EC_FW_UPDATE_NV_ATTEMPT_COUNT].Size;
  VOID *NVValue = &AttemptCnt;

  EC_TRACE();

  return GetOrSetEcNVData(
    EC_FW_UPDATE_NV_ATTEMPT_COUNT,
    &NVValue,
    &NVSize,
    EC_FW_UPDATE_SET_NV_DATA_FLUSH
    );
}

/**
 * *********This function should be called during boot time only**************
 * ******************for boot time optimization*******************************
 * This function updates the attempt count in non-volatile memory
 * without flushing.
 *
 * @param AttemptCnt       - attempt count to update in the non-volatile memory
 *
 * @return EFI_STATUS
 */

EFI_STATUS
SetNvEcFwAttemptCountDonotFlush(
  IN UINT8 AttemptCnt
  )
{
  UINTN NVSize = EcNVConfigData[EC_FW_UPDATE_NV_ATTEMPT_COUNT].Size;
  VOID *NVValue = &AttemptCnt;

  EC_TRACE();

  return GetOrSetEcNVData(
    EC_FW_UPDATE_NV_ATTEMPT_COUNT,
    &NVValue,
    &NVSize,
    EC_FW_UPDATE_SET_NV_DATA_NO_FLUSH
    );
}

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
  UINT32 FwVersion
  )
{
  UINTN NVSize = EcNVConfigData[EC_FW_UPDATE_NV_EC_FW_VERSION].Size;
  VOID  *NVValue = &FwVersion;

  EC_TRACE();

  return GetOrSetEcNVData(
    EC_FW_UPDATE_NV_EC_FW_VERSION,
    &NVValue,
    &NVSize,
    EC_FW_UPDATE_SET_NV_DATA_FLUSH
    );
}

/**
 * This function gets the EC FW version from non-volatile memory.
 * Make sure after the write a flush command is issued to clear
 * the FS cache
 *
 * @param Version       - FW version to be updated in the FS
 *
 * @return EFI_STATUS
 */
EFI_STATUS
GetNvEcFwVersion(
  OUT UINT32 *FwVersion
  )
{
  EFI_STATUS status = EFI_SUCCESS;
  UINTN NVSize = 0;
  VOID *NVData = NULL;

  EC_TRACE();

  if (!FwVersion)
  {
    EC_E("Invalid FwVersion input parameter!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  status = GetOrSetEcNVData(
    EC_FW_UPDATE_NV_EC_FW_VERSION,
    &NVData,
    &NVSize,
    EC_FW_UPDATE_GET_NV_DATA
  );
  EC_ERROR_HANDLER(status, GetOrSetEcNVData, Exit);

  if (NVSize > sizeof (*FwVersion))
  {
    EC_E("Current Size=%d : Max Expected Size=%d",
      NVSize,
      EcNVConfigData[EC_FW_UPDATE_NV_EC_FW_VERSION].Size
      );
    status = EFI_BUFFER_TOO_SMALL;
    goto Exit;
  }

  ZeroMem(FwVersion, sizeof(*FwVersion));
  CopyMem(FwVersion, NVData, NVSize);

Exit:
  if (NULL != NVData)
  {
    FreePool (NVData);
    NVData = NULL;
  }
  return status;
}

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
  UINT32 LsFwVersion
  )
{
  UINTN NVSize = EcNVConfigData[EC_FW_UPDATE_NV_EC_LS_FW_VERSION].Size;
  VOID  *NVValue = &LsFwVersion;

  EC_TRACE();

  return GetOrSetEcNVData(
    EC_FW_UPDATE_NV_EC_LS_FW_VERSION,
    &NVValue,
    &NVSize,
    EC_FW_UPDATE_SET_NV_DATA_FLUSH
    );
}

/**
 * This function gets the EC Lowest Supported (LS) FW version from non-volatile memory.
 * Make sure after the write a flush command is issued to clear
 * the FS cache
 *
 * @param Version       - FW version to be updated in the FS
 *
 * @return EFI_STATUS
 */
EFI_STATUS
GetNvEcLsFwVersion(
  OUT UINT32 *LsFwVersion
  )
{
  EFI_STATUS status = EFI_SUCCESS;
  UINTN NVSize = 0;
  VOID *NVData = NULL;

  EC_TRACE();

  if (!LsFwVersion)
  {
    EC_E("Invalid LsFwVersion input parameter!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  status = GetOrSetEcNVData(
    EC_FW_UPDATE_NV_EC_LS_FW_VERSION,
    &NVData,
    &NVSize,
    EC_FW_UPDATE_GET_NV_DATA
  );
  EC_ERROR_HANDLER(status, GetOrSetEcNVData, Exit);

  if (NVSize > sizeof (*LsFwVersion))
  {
    EC_E("Current Size=%d : Max Expected Size=%d",
      NVSize,
      EcNVConfigData[EC_FW_UPDATE_NV_EC_LS_FW_VERSION].Size
      );
    status = EFI_BUFFER_TOO_SMALL;
    goto Exit;
  }

  ZeroMem(LsFwVersion, sizeof(*LsFwVersion));
  CopyMem(LsFwVersion, NVData, NVSize);

Exit:
  if (NULL != NVData)
  {
    FreePool (NVData);
    NVData = NULL;
  }
  return status;
}

/**
 * This function updates the EC Write-Protection Sttaus in to the non-volatile memory.
 * Make sure after the write a flush command is issued to clear
 * the FS cache
 *
 * @param Version       - FW version to be updated in the FS
 *
 * @return EFI_STATUS
 */
EFI_STATUS
SetNvEcWriteProtectStatus(
  UINT32 WriteProtectStatus
  )
{
  UINTN NVSize = EcNVConfigData[EC_FW_UPDATE_NV_WP_EN_STATUS].Size;
  VOID  *NVValue = &WriteProtectStatus;

  EC_TRACE();

  return GetOrSetEcNVData(
    EC_FW_UPDATE_NV_WP_EN_STATUS,
    &NVValue,
    &NVSize,
    EC_FW_UPDATE_SET_NV_DATA_FLUSH
    );
}

/**
 * This function gets the EC Write-Protection Sttaus from non-volatile memory.
 * Make sure after the write a flush command is issued to clear
 * the FS cache
 *
 * @param Version       - FW version to be updated in the FS
 *
 * @return EFI_STATUS
 */
EFI_STATUS
GetNvEcWriteProtectStatus(
  OUT UINT32 *IsWriteProtectEnabled
  )
{
  EFI_STATUS status = EFI_SUCCESS;
  UINTN NVSize = 0;
  VOID *NVData = NULL;

  EC_TRACE();

  if (!IsWriteProtectEnabled)
  {
    EC_E("Invalid IsWriteProtectEnabled input parameter!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  status = GetOrSetEcNVData(
    EC_FW_UPDATE_NV_WP_EN_STATUS,
    &NVData,
    &NVSize,
    EC_FW_UPDATE_GET_NV_DATA
  );
  EC_ERROR_HANDLER(status, GetOrSetEcNVData, Exit);

  if (NVSize > sizeof (*IsWriteProtectEnabled))
  {
    EC_E("Current Size=%d : Max Expected Size=%d",
      NVSize,
      EcNVConfigData[EC_FW_UPDATE_NV_WP_EN_STATUS].Size
      );
    status = EFI_BUFFER_TOO_SMALL;
    goto Exit;
  }

  ZeroMem(IsWriteProtectEnabled, sizeof(*IsWriteProtectEnabled));
  CopyMem(IsWriteProtectEnabled, NVData, NVSize);

Exit:
  if (NULL != NVData)
  {
    FreePool (NVData);
    NVData = NULL;
  }
  return status;
}

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
  )
{
  UINTN NVSize = EcNVConfigData[EC_FW_UPDATE_NV_ACTV_PROTOCOL_STATUS].Size;
  VOID *NVValue = &ActiveProtocolStatus;
  EC_TRACE();

  return GetOrSetEcNVData(
    EC_FW_UPDATE_NV_ACTV_PROTOCOL_STATUS,
    &NVValue,
    &NVSize,
    EC_FW_UPDATE_SET_NV_DATA_NO_FLUSH
    );
}

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
  )
{
  UINTN NVSize = EcNVConfigData[EC_FW_UPDATE_NV_ACTV_PROTOCOL_STATUS].Size;
  VOID *NVValue = &ActiveProtocolStatus;
  EC_TRACE();

  return GetOrSetEcNVData(
    EC_FW_UPDATE_NV_ACTV_PROTOCOL_STATUS,
    &NVValue,
    &NVSize,
    EC_FW_UPDATE_SET_NV_DATA_FLUSH
    );
}

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
  )
{
  EFI_STATUS status = EFI_SUCCESS;
  UINTN NVSize = 0;
  VOID *NVData = NULL;
  EC_TRACE();

  if (!ActiveProtocolStatus)
  {
    EC_E("Invalid input parameter!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  status = GetOrSetEcNVData(
    EC_FW_UPDATE_NV_ACTV_PROTOCOL_STATUS,
    &NVData,
    &NVSize,
    EC_FW_UPDATE_GET_NV_DATA
    );
  EC_ERROR_HANDLER(status, GetOrSetEcNVData, Exit);

  if (NVSize > sizeof (*ActiveProtocolStatus))
  {
    EC_E("Current Size=%d : Max Expected Size=%d",
      NVSize,
      EcNVConfigData[EC_FW_UPDATE_NV_ACTV_PROTOCOL_STATUS].Size
      );
    status = EFI_BUFFER_TOO_SMALL;
    goto Exit;
  }

  ZeroMem(ActiveProtocolStatus, sizeof(*ActiveProtocolStatus));
  CopyMem(ActiveProtocolStatus, NVData, NVSize);

Exit:
  if (NULL != NVData)
  {
    FreePool (NVData);
    NVData = NULL;
  }
  return status;
}

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
  )
{
  UINTN NVSize = EcNVConfigData[EC_FW_UPDATE_NV_FLASH_TYPE_STATUS].Size;
  VOID *NVValue = &FlashTypeStatus;
  EC_TRACE();

  return GetOrSetEcNVData(
    EC_FW_UPDATE_NV_FLASH_TYPE_STATUS,
    &NVValue,
    &NVSize,
    EC_FW_UPDATE_SET_NV_DATA_NO_FLUSH
    );
}

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
  )
{
  UINTN NVSize = EcNVConfigData[EC_FW_UPDATE_NV_FLASH_TYPE_STATUS].Size;
  VOID *NVValue = &FlashTypeStatus;
  EC_TRACE();

  return GetOrSetEcNVData(
    EC_FW_UPDATE_NV_FLASH_TYPE_STATUS,
    &NVValue,
    &NVSize,
    EC_FW_UPDATE_SET_NV_DATA_FLUSH
    );
}

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
  )
{
  EFI_STATUS status = EFI_SUCCESS;
  UINTN NVSize = 0;
  VOID *NVData = NULL;
  EC_TRACE();

  if (!FlashTypeStatus)
  {
    EC_E("Invalid input parameter!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  status = GetOrSetEcNVData(
    EC_FW_UPDATE_NV_FLASH_TYPE_STATUS,
    &NVData,
    &NVSize,
    EC_FW_UPDATE_GET_NV_DATA
    );
  EC_ERROR_HANDLER(status, GetOrSetEcNVData, Exit);

  if (NVSize > sizeof (*FlashTypeStatus))
  {
    EC_E("Current Size=%d : Max Expected Size=%d",
      NVSize,
      EcNVConfigData[EC_FW_UPDATE_NV_FLASH_TYPE_STATUS].Size
      );
    status = EFI_BUFFER_TOO_SMALL;
    goto Exit;
  }

  ZeroMem(FlashTypeStatus, sizeof(*FlashTypeStatus));
  CopyMem(FlashTypeStatus, NVData, NVSize);

Exit:
  if (NULL != NVData)
  {
    FreePool (NVData);
    NVData = NULL;
  }
  return status;
}


/**
 * Check if the NV variables related to EC firmware update
 * is present. Else create those with default values
 *
 * @return EFI_STATUS
 */
EFI_STATUS
CheckAndCreateEcNVData()
{
  EFI_STATUS                    status = EFI_SUCCESS;
  UINT8                         AttemptCount = 0;
  UINT8                         FlashType    = 0;
  UINT8                         ActvProtocol = 0;
  UINT8                         DeviceStatus = 0;
  EC_FW_UPDATE_STATE_VARIABLE   UpdateState  = EC_FW_STATE_NOT_IN_PROGRESS;
  EC_TRACE();

  status = GetNvEcFwUpdateState(&UpdateState);
  if ((EFI_NOT_FOUND == status) ||
     (EFI_BUFFER_TOO_SMALL == status))
  {
    UpdateState = EC_FW_STATE_NOT_IN_PROGRESS;
    status = SetNvEcFwUpdateStateDonotFlush(EC_FW_STATE_NOT_IN_PROGRESS);
    EC_ERROR_HANDLER(status, SetNvEcFwUpdateStateDonotFlush, Exit);
  }

  EC_I("UpdateState: %d\n", UpdateState);

  status = GetNvEcFwAttemptCount(&AttemptCount);
  if ((EFI_NOT_FOUND == status) ||
     (EFI_BUFFER_TOO_SMALL == status))
  {
    status = SetNvEcFwAttemptCountDonotFlush(0);
    EC_ERROR_HANDLER(status, SetNvEcFwAttemptCountDonotFlush, Exit);
  }

  status = GetNvEcFwFlashTypeStatus(&FlashType);
  if ((EFI_NOT_FOUND == status) ||
     (EFI_BUFFER_TOO_SMALL == status))
  {
    status = SetNvEcFwFlashTypeStatusDonotFlush(0);
    EC_ERROR_HANDLER(status, SetNvEcFwFlashTypeStatusDonotFlush, Exit);
  }

  status = GetNvEcFwActiveProtocolStatus(&ActvProtocol);
  if ((EFI_NOT_FOUND == status) ||
     (EFI_BUFFER_TOO_SMALL == status))
  {
    status = SetNvEcFwActiveProtocolStatusDonotFlush(0);
    EC_ERROR_HANDLER(status, SetNvEcFwActiveProtocolStatusDonotFlush, Exit);
  }

  status = GetNvEcDeviceStatus(&DeviceStatus);
  if ((EFI_NOT_FOUND == status) ||
     (EFI_BUFFER_TOO_SMALL == status))
  {
    status = SetNvEcDeviceStatusDonotFlush(0);
    if (EFI_ERROR(status))
    {
      EC_E("SetNvEcDeviceStatusDonotFlush() failed with %r\n", status);
      goto Exit;
    }
  }
Exit:
  return status;
}

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
  )
{
  UINTN NVSize = EcNVConfigData[EC_FW_UPDATE_NV_DEVICE_STATUS].Size;
  VOID *NVValue = &DeviceStatus;

  return GetOrSetEcNVData(
    EC_FW_UPDATE_NV_DEVICE_STATUS,
    &NVValue,
    &NVSize,
    EC_FW_UPDATE_SET_NV_DATA_FLUSH
    );
}

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
  )
{
  EFI_STATUS status = EFI_SUCCESS;
  UINTN NVSize = 0;
  VOID *NVData = NULL;

  if (!DeviceStatus)
  {
    EC_E("Invalid input parameter!\n");
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  status = GetOrSetEcNVData(
    EC_FW_UPDATE_NV_DEVICE_STATUS,
    &NVData,
    &NVSize,
    EC_FW_UPDATE_GET_NV_DATA
    );
  if (EFI_ERROR(status))
  {
    EC_E("GetOrSetEcNVData(EC_FW_UPDATE_NV_DEVICE_STATUS) failed with %r\n");
    goto Exit;
  }

  if (NVSize > sizeof (*DeviceStatus))
  {
    EC_E("Current Size=%d : Max Expected Size=%d",
      NVSize,
      EcNVConfigData[EC_FW_UPDATE_NV_DEVICE_STATUS].Size
      );
    FreePool (NVData);
    NVData = NULL;

    status = EFI_BUFFER_TOO_SMALL;
    goto Exit;
  }

  ZeroMem(DeviceStatus, sizeof(*DeviceStatus));
  CopyMem(DeviceStatus, NVData, NVSize);

Exit:
  if (NULL != NVData)
  {
    FreePool (NVData);
    NVData = NULL;
  }
  return status;
}

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
  )
{
  UINTN NVSize = EcNVConfigData[EC_FW_UPDATE_NV_DEVICE_STATUS].Size;
  VOID *NVValue = &DeviceStatus;

  return GetOrSetEcNVData(
    EC_FW_UPDATE_NV_DEVICE_STATUS,
    &NVValue,
    &NVSize,
    EC_FW_UPDATE_SET_NV_DATA_NO_FLUSH
    );
}


