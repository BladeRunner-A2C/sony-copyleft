/** @file MfgModeMgmtDxe.c

Implementation for Qualcomm Manufacturing Mode protocol

Copyright (c) 2023 Qualcomm Technologies, Inc.
All rights reserved.
Qualcomm Technologies, Confidential and Proprietary.

**/

/*=============================================================================
EDIT HISTORY


when           who         what, where, why
--------       ---         --------------------------------------------------
2023/03/16     gpavithr    Initial revision
=============================================================================*/

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/QcomLib.h>
#include <Library/DebugLib.h>
#include <Library/QcomTargetLib.h>
#include <Library/UefiLib.h>
#include <Library/MfgModeMgmtApp.h>
#include <Protocol/EFIScm.h>
#include <scm_sip_interface.h>
#include <MfgModeMgmtDxe.h>
#include <Protocol/EFIMfgModeMgmt.h>
#include <Uefi.h>

#define QCOM_NV_VAR_MFG_MODE  L"QCOM_NV_VAR_MFG_MODE"
#define TZ_RETURN_SUCCESS      1

QCOM_SCM_PROTOCOL    *pQcomScmProtocol = NULL;  // SCM Protocol
uint32                gAppId = 0;

/**
  Callback function for Ready to Boot Event.
  
  @param[in]  event     Event whose notification function is being invoked
  @param[in]  context   Pointer to the notification function's context
**/
STATIC
VOID
EFIAPI
MfgModeMgmtReadyToBootCallback (
  IN EFI_EVENT event,
  IN VOID *pContext
  )
{
  UINT64        parameters[SCM_MAX_NUM_PARAMETERS] = {0};
  UINT64        results[SCM_MAX_NUM_RESULTS]       = {0};
  EFI_STATUS    status                             = EFI_SUCCESS;
  MFG_SVC_REQ_T req                                = {0};
  MFG_SVC_RSP_T rsp                                = {0};

  parameters[0] = TZ_UEFI_READY_TO_BOOT_FUSE;
  //Invoke READY_TO_BOOT MILESTONE CALL
  status = pQcomScmProtocol->ScmSipSysCall(
    pQcomScmProtocol,
    TZ_BLOW_SW_FUSE_ID,
    TZ_BLOW_SW_FUSE_ID_PARAM_ID,
    parameters,
    results
    );
  //On Success results[0] is set to TZ_RETURN_SUCCESS(1)
  if (EFI_ERROR (status) || TZ_RETURN_SUCCESS != results[0])
  {
    DEBUG ((
      EFI_D_ERROR,
      "MfgModeMgmtReadyToBootCallback: failed to set TZ_UEFI_READY_TO_BOOT_FUSE, status: %r, results[0]: %d\n",
      status,
      results[0]
      ));
    goto Exit;
  }

  //Signal to apply write-protection to MfgModeMgmtTA
  req.commandId = CMD_STORAGE_WRITE_PROTECT;
  status = pQcomScmProtocol->ScmSendCommand(
    pQcomScmProtocol,
    APP_SEND_DATA_CMD,
    &gAppId,
    &req,
    sizeof(MFG_SVC_REQ_T),
    &rsp,
    sizeof (MFG_SVC_RSP_T)
    );
  if (EFI_ERROR (status))
  {
    DEBUG ((
      EFI_D_ERROR,
      "MfgModeMgmtReadyToBootCallback: CMD_STORAGE_WRITE_PROTECT failed, SMC status: %r, rsp.status: %d\n",
      status,
      rsp.status
      ));
    //initiate a device Crash , as it is not safe to boot device on write-protection failure
    ASSERT(FALSE);
  }

  // On Status: Success check for the values in Rsp.status
  if (MFG_DEVICE_IN_MFG_MODE == rsp.status)
  {
    DEBUG ((
      EFI_D_WARN,
      "MfgModeMgmtReadyToBootCallback: Write-Protection is skipped as device is in mfgmode, SMC status: %r, rsp.status: %d\n",
      status,
      rsp.status
      ));
    goto Exit;
  }
  else if (MFG_MODE_EOF_NOT_BLOWN == rsp.status)
  {
    DEBUG ((
      EFI_D_WARN,
      "MfgModeMgmtReadyToBootCallback: Write-Protection is skipped as EOF fuse is not blown, SMC Status: %r, rsp.status: %d\n",
      status,
      rsp.status
      ));
    goto Exit;
  }
  else if (MFG_SUCCESS == rsp.status)
  {
    DEBUG ((
      EFI_D_WARN,
      "MfgModeMgmtReadyToBootCallback: Write-Protection is applied, SMC Status: %r, rsp.status: %d\n",
      status,
      rsp.status
      ));
    goto Exit;
  }
  else
  {
    //any other value in Rsp.status other than the above is considered as failure
    DEBUG ((
      EFI_D_ERROR,
      "MfgModeMgmtReadyToBootCallback: CMD_STORAGE_WRITE_PROTECT failed, SMC Status: %r, rsp.status: %d\n",
      status,
      rsp.status
      ));
    //initiate a device Crash , as it is not safe to boot device on write-protection failure
    ASSERT(FALSE);
  }

Exit:
    gBS->CloseEvent(event);
    return;
}

/**
  Function to retrieve the status of mfgmode on the device.
  
  @param[out]  pMfgModeStatus       EFI_QC_MFG_MODE_ENABLED/EFI_QC_MFG_MODE_DISABLED depending
                                    on whether mfgmode is enabled/disabled.
  
  @retval      EFI_SUCCESS          Mfgmode status is returned successfully.
  @retval      EFI_XXXXXX           Failure occured.
  
**/
EFI_STATUS
GetManufacturingMode(
   OUT EFI_QC_MFG_MODE_STATUS_TYPE *pMfgModeStatus
  )
{
  EFI_STATUS    status = EFI_SUCCESS;
  MFG_SVC_REQ_T req    = {0};
  MFG_SVC_RSP_T rsp    = {0};

  if (pMfgModeStatus == NULL)
  {
    DEBUG ((EFI_D_ERROR, "GetManufacturingMode: pmfgModeStatus is NULL\n"));
    status = EFI_INVALID_PARAMETER;
    goto Exit;
  }

  *pMfgModeStatus = EFI_QC_MFG_MODE_DISABLED; //default value

  req.commandId = CMD_GET_MFG_MODE;
  status = pQcomScmProtocol->ScmSendCommand(
    pQcomScmProtocol,
    APP_SEND_DATA_CMD,
    &gAppId,
    &req,
    sizeof(MFG_SVC_REQ_T),
    &rsp,
    sizeof(MFG_SVC_RSP_T)
    );
  if (status != EFI_SUCCESS)
  {
    DEBUG((
      EFI_D_ERROR,
      "GetManufacturingMode: CMD_GET_MFG_MODE failed, SMC status: %r, rsp.status: %d\n",
      status,
      rsp.status
      ));
    goto Exit;
  }

  DEBUG ((
    EFI_D_WARN,
    "GetManufacturingMode: CMD_GET_MFG_MODE passed, SMC status: %r, rsp.status: %d\n",
    status,
    rsp.status
    ));

  if (MFG_DEVICE_IN_MFG_MODE == rsp.status)
  {
    DEBUG ((EFI_D_WARN, "GetManufacturingMode: CMD_GET_MFG_MODE returned as device is in mfg mode\n"));
    *pMfgModeStatus = EFI_QC_MFG_MODE_ENABLED;
  }

  DEBUG ((EFI_D_WARN, "GetManufacturingMode: pMfgModeStatus = %d\n", *pMfgModeStatus));

Exit:
  return status;
}

/**
  OEM specific uefi modules will have logic to detect if manufacturing mode
  needs to be enabled on the device. Either based on manufacturing policy
  enabled in a signed policy blob or some sort of TA based authorization.
  If mfgmode needs to be enabled on the device , OEM specific modules 
  in UEFI must use this api to enable mfgmode on the device.

  @param[in]  value               EFI_QC_MFG_MODE_ENABLED : Enable manufacturing mode.
  
  @retval  EFI_SUCCESS            MANUFACTURING_MODE is enabled successfully.
  @retval  EFI_UNSUPPORTED        Disabling mfgmode using value(EFI_QC_MFG_MODE_DISABLED)
                                  is not supported.
  @retval  EFI_XXXXXX             Failure occured.
  
**/
EFI_STATUS
SetManufacturingMode (
  IN EFI_QC_MFG_MODE_STATUS_TYPE value
  )
{
  EFI_STATUS    status = EFI_SUCCESS;
  MFG_SVC_REQ_T req    = {0};
  MFG_SVC_RSP_T rsp    = {0};

  DEBUG ((EFI_D_WARN, "SetManufacturingMode: value = %d\n", value));

  if (EFI_QC_MFG_MODE_ENABLED == value)
  {
    req.commandId = CMD_ENTER_MFG_MODE;
    status = pQcomScmProtocol->ScmSendCommand(
      pQcomScmProtocol,
      APP_SEND_DATA_CMD,
      &gAppId,
      &req,
      sizeof(MFG_SVC_REQ_T),
      &rsp,
      sizeof (MFG_SVC_RSP_T)
      );
    if (EFI_ERROR(status))
    {
      DEBUG ((
        EFI_D_ERROR,
        "SetManufacturingMode: CMD_ENTER_MFG_MODE failed, SMC status: %r, rsp.status: %d\n",
        status,
        rsp.status
        ));
      goto Exit;
    }

    if (MFG_MODE_EOF_NOT_BLOWN == rsp.status)
    {
      DEBUG ((
        EFI_D_WARN,
        "SetManufacturingMode: Device is in MfgMode as EOF fuse is not blown, SMC status: %r, rsp.status: %d\n",
        status,
        rsp.status
        ));
      goto Exit;
    }
    else if (MFG_DEVICE_IN_MFG_MODE == rsp.status)
    {
      DEBUG ((
        EFI_D_WARN,
        "SetManufacturingMode: MfgMode is already enabled on the device, SMC status: %r, rsp.status: %d\n",
        status,
        rsp.status
        ));
      goto Exit;
    }
    else if (MFG_SUCCESS == rsp.status)
    {
      DEBUG ((
        EFI_D_WARN,
        "SetManufacturingMode: MfgMode is enabled on the device, SMC Status: %r, rsp.status: %d\n",
        status,
        rsp.status
      ));
      goto Exit;
    }
    else
    {
      //any other value in Rsp.status other than the above is considered as failure
      DEBUG ((
        EFI_D_ERROR,
        "SetManufacturingMode: CMD_ENTER_MFG_MODE failed, SMC Status: %r, rsp.status: %d\n",
        status,
        rsp.status
        ));
    }
  }
  else
  {
    //Disable mfg_mode has to be initiated from HLOS as part of ExitMfgMode command from factorytools
    //which invokes create_hmac apis followed by disable mfgmode
    DEBUG ((EFI_D_ERROR, "SetManufacturingMode: Invalid argument to disable mfg_mode from UEFI\n"));
    status = EFI_UNSUPPORTED;
    goto Exit;
  }

Exit:
  return status;
}

/**
  Function to enable MfgMode from MfgModeToggleApp.
  
  @retval  EFI_SUCCESS    If QCOM_NV_VAR_MFG_MODE is set by MfgModeToggleApp then
                          MfgMode is enabled on the device.
                          Otherwise QCOM_NV_VAR_MFG_MODE is not set by MfgModeToggleApp.
  
  @retval  EFI_XXXXXX     Failure occured.
  
**/
EFI_STATUS
EnableMfgModeFromNV(
  VOID
  )
{
  EFI_STATUS status         = EFI_SUCCESS;
  UINT8      mfgModeValue   = 0;
  UINTN      varSize        = 0;

  varSize = sizeof(mfgModeValue);

  //Read the QCOM_NV_VAR_MFG_MODE NV variable
  status = gRT->GetVariable (
    QCOM_NV_VAR_MFG_MODE,
    &gQcomTokenSpaceGuid,
    NULL,
    &varSize,
    &mfgModeValue
    );
  if (EFI_ERROR (status))
  {
    DEBUG((
      EFI_D_ERROR,
      "EnableMfgModeFromNV: GetVariable(QCOM_NV_VAR_MFG_MODE) returned status: %r\n",
      status
      ));
    status = EFI_SUCCESS;
    goto Exit;
  }

  DEBUG ((EFI_D_WARN, "EnableMfgModeFromNV: mfgModeValue = %d\n", mfgModeValue));

  if (EFI_QC_MFG_MODE_ENABLED == mfgModeValue)
  {
    status = SetManufacturingMode(mfgModeValue);
    if (EFI_ERROR (status))
    {
      DEBUG((EFI_D_ERROR, "EnableMfgModeFromNV: SetManufacturingMode() failed with status: %r\n", status));
      goto Exit;
    }

    //Reset MfgMode NV variable, so that its value doesnot persist across reboots
    mfgModeValue = EFI_QC_MFG_MODE_DISABLED;

    status = gRT->SetVariable (
      QCOM_NV_VAR_MFG_MODE,
      &gQcomTokenSpaceGuid,
      (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS),
      0,
      &mfgModeValue
      );
    if (EFI_ERROR (status))
    {
      DEBUG((EFI_D_ERROR, "EnableMfgModeFromNV: Clearing the NV(QCOM_NV_VAR_MFG_MODE) failed with status: %r\n", status));
      goto Exit;
    }

    FlushVariableServices();
  }

Exit:
  return status;
}

/**
  Template for EFI_MFG_MODE_MGMT_PROTOCOL.
**/
static EFI_QC_MFG_MODE_MGMT_PROTOCOL mfgModeMgmtProtocol = {
  EFI_QC_MFG_MODE_MGMT_PROTOCOL_REVISION_1,
  SetManufacturingMode,
  GetManufacturingMode
};

/**
  Initializes EFI_MANUFACTURING_MODE protocol
  
  @param[in]  hImageHandle   Firmware allocated handle for the EFI image.
  @param[in]  pSystemTable   Pointer to the EFI System Table.
  
  @retval  EFI_SUCCESS    MANUFACTURING_MODE protocol initialized successfully.
  @retval  EFI_XXXXXX     Failure occured.
  
**/
EFI_STATUS
MfgModeMgmtDxeEntryPoint (
  IN EFI_HANDLE          hImageHandle,
  IN EFI_SYSTEM_TABLE    *pSystemTable
  )
{
  EFI_STATUS status           = EFI_SUCCESS;
  EFI_EVENT  readyToBootEvent = NULL;

  // Install MFG_MODE_MGMT Protocol
  status = gBS->InstallMultipleProtocolInterfaces (
    &hImageHandle,
    &gEfiQCMfgModeMgmtProtocolGuid,
    &mfgModeMgmtProtocol,
    NULL,
    NULL,
    NULL
    );
  if (EFI_ERROR (status))
  {
    DEBUG ((EFI_D_ERROR, "MfgModeMgmtDxeEntryPoint: Protocol install error, status: %r\n", status));
    goto Exit;
  }

  status = gBS->LocateProtocol (
    &gQcomScmProtocolGuid,
    NULL,
    (VOID **)&pQcomScmProtocol
    );
  if (EFI_ERROR (status))
  {
    DEBUG((EFI_D_ERROR, "MfgModeMgmtDxeEntryPoint: Locate SCM Protocol failed, status: %r\n", status));
    goto Exit;
  }

  //Query MfgModeMgmtTA APPID
  status = pQcomScmProtocol->ScmSendCommand(
    pQcomScmProtocol,
    APP_QUERY_APPID_CMD,
    &gAppId,
    MFGMODEMGMT_APP_NAME,
    sizeof(MFGMODEMGMT_APP_NAME),
    NULL,
    0
    );
  if (EFI_ERROR(status))
  {
    DEBUG ((EFI_D_ERROR, "MfgModeMgmtDxeEntryPoint: QueryAppId for mfgmodemgmt app failed, status: %r\n", status));
    gAppId = 0;
    goto Exit;
  }

  DEBUG ((EFI_D_WARN, "MfgModeMgmtDxeEntryPoint: QueryAppId for mfgmodemgmt app passed with AppId: %d\n", gAppId));

  /* Enable Mfgmode from MfgModeToggleApp, the app would set QCOM_NV_VAR_MFG_MODE
   * Read NV variable : QCOM_NV_VAR_MFG_MODE
   * If its set then call SetManufacturingMode()
   * reset NV variable
   * Restrict this code from getting executed on Retail device
   */
  if (!RETAIL)
  {
    DEBUG ((EFI_D_WARN, "MfgModeMgmtDxeEntryPoint: Not a RETAIL device can execute EnableMfgModeFromNV()\n"));
    status = EnableMfgModeFromNV();
    if (EFI_ERROR (status))
    {
      DEBUG(( EFI_D_ERROR, "MfgModeMgmtDxeEntryPoint: EnableMfgModeFromNV() failed, status: %r\n", status));
      goto Exit;
    }
  }

  status = EfiCreateEventReadyToBootEx (
    TPL_CALLBACK,
    MfgModeMgmtReadyToBootCallback,
    NULL,
    &readyToBootEvent
    );
  if (EFI_ERROR (status))
  {
    DEBUG ((EFI_D_ERROR, "MfgModeMgmtDxeEntryPoint: Register for ReadyToBoot Event failed, status: %r\n", status));
    goto Exit;
  }

  DEBUG ((EFI_D_WARN, "MfgModeMgmtDxeEntryPoint: Registered for ReadyToBoot Event Callback.\n"));

Exit:
  return status;
}
