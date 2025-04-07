/*
 * Copyright (c) 2020-2021, 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include <Library/UefiLib.h>
#include <Library/DevicePathLib.h>
#include <Library/UefiApplicationEntryPoint.h>

#include <Protocol/DriverSupportedEfiVersion.h>
#include <Protocol/DriverBinding.h>
#include <Protocol/ResetNotification.h>

#include "Dev.h"
#include "QcaWlan.h"
#include "Debug.h"

GLOBAL_REMOVE_IF_UNREFERENCED
EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL gWlanUefiSupportedVersion = {
    sizeof(EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL),
    0x0002001E
};

EFI_QCWLAN_DEVICE_CONTEXT gWlanDriverContext = { 0 };

extern EFI_COMPONENT_NAME2_PROTOCOL gQcWlanUefiComponentName2;
extern EFI_COMPONENT_NAME_PROTOCOL gQcWlanUefiComponentName;
extern EFI_DRIVER_BINDING_PROTOCOL gQcWlanDrvBinding;
extern EFI_DRIVER_DIAGNOSTICS2_PROTOCOL gWlanUefiDiagnostics2;

VOID
QcWlanResetSystem(
	IN EFI_RESET_TYPE  ResetType,
    IN EFI_STATUS      ResetStatus,
    IN UINTN           DataSize,
    IN VOID            *ResetData)
{
    DbgPrint("Reset System");
    QcWlanUninitializeNic(&gWlanDriverContext);
}

VOID
QcWlanRegisterResetNotification(
    VOID)
{
	EFI_STATUS                       Status;
	EFI_RESET_NOTIFICATION_PROTOCOL  *ResetNotify;

	Status = gBS->LocateProtocol(&gEfiResetNotificationProtocolGuid, NULL, (VOID **)&ResetNotify);
	if (!EFI_ERROR(Status)) {
		Status = ResetNotify->RegisterResetNotify(ResetNotify, QcWlanResetSystem);
		if (EFI_ERROR(Status)) {
			DbgPrint("RegisterResetNotify Status = %r", Status);
		}
	} else {
		DbgPrint("ResetNotification absent!!!");
	}
}

VOID
QcWlanUnregisterResetNotification(
    VOID)
{
	EFI_STATUS                       Status;
	EFI_RESET_NOTIFICATION_PROTOCOL  *ResetNotify;

	Status = gBS->LocateProtocol(&gEfiResetNotificationProtocolGuid, NULL, (VOID **)&ResetNotify);
	if(!EFI_ERROR (Status)) {
		Status = ResetNotify->UnregisterResetNotify(ResetNotify, QcWlanResetSystem);
		if(EFI_ERROR (Status)) {
			DbgPrint("UnregisterResetNotify Status = %r", Status);
		}
	}
}

STATIC
EFI_STATUS
QcWlanInstallBinding(
    IN  EFI_HANDLE ImageHandle,
    IN  EFI_SYSTEM_TABLE *SystemTable,
    OUT EFI_DRIVER_BINDING_PROTOCOL **BindingProtocol)
{
    EFI_STATUS Status;
    *BindingProtocol = NULL;

    Status = EfiLibInstallDriverBindingComponentName2(
        ImageHandle,
        SystemTable,
        &gQcWlanDrvBinding,
        ImageHandle,
        &gQcWlanUefiComponentName,
        &gQcWlanUefiComponentName2);
    if (EFI_ERROR(Status)) {
        goto cleanup;
    }

    *BindingProtocol = &gQcWlanDrvBinding;
cleanup:
    return Status;
}

STATIC
VOID
QcWlanUninstallBinding(
    IN  EFI_HANDLE ImageHandle)
{
    EFI_STATUS Status;

    Status = gBS->UninstallMultipleProtocolInterfaces(
        ImageHandle,
        &gEfiDriverBindingProtocolGuid, &gQcWlanDrvBinding,
        NULL);
    if (EFI_ERROR(Status)) {
        DbgError("ERROR %r\n", Status);
    }

#if SUPPORT_RESET_NOTIFICATION
	QcWlanUnregisterResetNotification();
#endif
	
    DbgPrint("Exit");
}

EFI_STATUS
EFIAPI
WlanDriverInstallProtocols(
    IN EFI_HANDLE			ImageHandle,
    IN EFI_SYSTEM_TABLE		*SystemTable)
{
    EFI_STATUS Status;
    EFI_LOADED_IMAGE_PROTOCOL *Image;

    WallTimerAttach();

    Status = gBS->HandleProtocol(
        ImageHandle,
        &gEfiLoadedImageProtocolGuid,
        (VOID**)&Image);
    if (EFI_ERROR(Status)) {
        goto exit;
    }
    gWlanDriverContext.Image = Image;

    GlobalLoggingContextInitialize(Image);

    Status = gBS->InstallMultipleProtocolInterfaces(
        &ImageHandle,
        &gEfiDriverSupportedEfiVersionProtocolGuid, &gWlanUefiSupportedVersion,
        &gEfiDriverDiagnostics2ProtocolGuid,&gWlanUefiDiagnostics2,
        NULL);
    if (EFI_ERROR(Status)) {
		DbgError("Failed to install protocols: %r\n", Status);
        goto exit;
    }

    Status = QcWlanInstallBinding(
        ImageHandle,
        SystemTable,
        &gWlanDriverContext.BindingProtocol
    );
    if (EFI_ERROR(Status)) {
        DbgError("Failed to install binding protocol: %r\n", Status);
        goto exit;
    }

#if SUPPORT_RESET_NOTIFICATION
	QcWlanRegisterResetNotification();
#endif

exit:
    return Status;
}

#if SUPPORT_LOAD_BY_EVT
extern EFI_GUID gEfiEventWifiReadyToEnableGuid;

STATIC 
VOID
WlanDriverEnableCallback(
    IN EFI_EVENT    Event,
    IN VOID         *Context
)
{
    EFI_STATUS Status;

    Status = WlanDriverInstallProtocols(gImageHandle, gST);
    if (EFI_ERROR(Status)) {
        DbgError("Failed to install protocols: %r\n", Status);
        return;
    }

    // Install protocols successfully
    if (gWlanDriverContext.ReadyToEnable != NULL) {
        gBS->CloseEvent(gWlanDriverContext.ReadyToEnable);
        gWlanDriverContext.ReadyToEnable = NULL;
  	}
}

EFI_STATUS
EFIAPI
WlanDriverCreateEnableEvent (
	IN EFI_HANDLE			ImageHandle,
	IN EFI_SYSTEM_TABLE		*SystemTable)
{
    EFI_STATUS Status;
    
    Status = gBS->CreateEventEx(
        EVT_NOTIFY_SIGNAL,
        TPL_CALLBACK,
        WlanDriverEnableCallback,
        NULL,
        &gEfiEventWifiReadyToEnableGuid,
        &gWlanDriverContext.ReadyToEnable);

    if (EFI_ERROR(Status)) {
        DEBUG((EFI_D_ERROR, "Wlan Driver enable event creation failed!!"));
    }
    
    return Status;
}

EFI_STATUS
EFIAPI
WlanDriverCloseEnableEvent (
	IN EFI_HANDLE			ImageHandle)
{
    EFI_STATUS Status = EFI_SUCCESS;

	// Driver is ready to enable but not enable yet
    if (gWlanDriverContext.ReadyToEnable != NULL) {
        gBS->CloseEvent(gWlanDriverContext.ReadyToEnable);
        gWlanDriverContext.ReadyToEnable = NULL;
        return EFI_SUCCESS;
    }
    
    return Status;
}
#endif

EFI_STATUS
EFIAPI
WlanDriverEntryPoint (
	IN EFI_HANDLE			ImageHandle,
	IN EFI_SYSTEM_TABLE		*SystemTable)
{
    EFI_STATUS Status;

#if SUPPORT_LOAD_BY_EVT
	Status = WlanDriverCreateEnableEvent(ImageHandle, SystemTable);
	if (EFI_ERROR(Status)) {
        DbgError("Failed to create event: %r\n", Status);
	}
#else
	Status = WlanDriverInstallProtocols(ImageHandle, SystemTable);
	if (EFI_ERROR(Status)) {
        DbgError("Failed to install protocols: %r\n", Status);
	}
#endif
    return Status;
}

EFI_STATUS
EFIAPI
WlanDriverUnload(IN EFI_HANDLE ImageHandle)
{
    EFI_STATUS Status;

#if SUPPORT_LOAD_BY_EVT
	WlanDriverCloseEnableEvent(ImageHandle);
#endif
	
    if (gWlanDriverContext.Started == DEV_START_SUCC) {
        DbgFlush();
        return EFI_NOT_READY;
    }

    QcWlanUninstallBinding(ImageHandle);

    Status = gBS->UninstallMultipleProtocolInterfaces(
        ImageHandle,
        &gEfiDriverSupportedEfiVersionProtocolGuid, &gWlanUefiSupportedVersion,
        &gEfiDriverDiagnostics2ProtocolGuid,&gWlanUefiDiagnostics2,
        NULL
    );

    DbgPrint("Status: %r", Status);

    GlobalLoggingContextUninitialize();

    WallTimerDetach();
    return Status;
}

