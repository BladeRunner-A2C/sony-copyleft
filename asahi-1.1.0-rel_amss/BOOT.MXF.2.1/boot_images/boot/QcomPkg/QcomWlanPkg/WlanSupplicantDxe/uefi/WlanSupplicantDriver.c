/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include <Protocol/EapConfiguration.h>
#include <Protocol/LoadedImage.h>
#include <Library/DevicePathLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include "WlanSupplicant.h"
#include "Utils.h"
#include "Debug.h"

SUPPLICANT_SERVICE gSupplicantService = { 0 };

STATIC
EFI_STATUS
EFIAPI
SupplicantServiceBindingCreateChild(
    IN EFI_SERVICE_BINDING_PROTOCOL  *This,
    IN EFI_HANDLE                    *ChildHandle
)
{
    EFI_STATUS Status;
    SUPPLICANT_SERVICE *SupplicantService;
    SUPPLICANT_INSTANCE *Instance;
    EFI_TPL OldTpl;

    if ((This == NULL) || (ChildHandle == NULL)) {
        return EFI_INVALID_PARAMETER;
    }

    SupplicantService = SUPPLICANT_SERVICE_FROM_THIS(This);

    Instance = AllocateZeroPool(sizeof(SUPPLICANT_INSTANCE));
    if (Instance == NULL)
        return EFI_OUT_OF_RESOURCES;

    Status = SupplicantServiceInitInstance(SupplicantService, Instance);
    if (Status != EFI_SUCCESS) {
        FreePool(Instance);
        return Status;
    }

    Status = gBS->InstallMultipleProtocolInterfaces(
        ChildHandle,
        &gEfiSupplicantProtocolGuid, (VOID *)&Instance->SupplicantProtocol,
        &gEfiEapConfigurationProtocolGuid, (VOID *)&Instance->EapCfgProtocol,
        NULL
    );
    if (EFI_ERROR(Status)) {
        FreePool(Instance);
        return Status;
    }

    Instance->Handle = *ChildHandle;

    OldTpl = gBS->RaiseTPL(TPL_CALLBACK);
    InsertTailList(&SupplicantService->ChildrenList, &Instance->Node);
    SupplicantService->ChildrenNumber++;
    gBS->RestoreTPL(OldTpl);

    return Status;
}

STATIC
EFI_STATUS
EFIAPI
SupplicantServiceBindingDestroyChild(
    IN EFI_SERVICE_BINDING_PROTOCOL  *This,
    IN EFI_HANDLE                    ChildHandle
)
{
    EFI_STATUS Status;
    SUPPLICANT_SERVICE *SupplicantService;
    SUPPLICANT_INSTANCE *Instance;
    EFI_SUPPLICANT_PROTOCOL *SupplicantProtocol;
    EFI_TPL OldTpl;

    if ((This == NULL) || (ChildHandle == NULL)) {
        return EFI_INVALID_PARAMETER;
    }

    SupplicantService = SUPPLICANT_SERVICE_FROM_THIS(This);

    Status = gBS->OpenProtocol(
        ChildHandle,
        &gEfiSupplicantProtocolGuid,
        (VOID **)&SupplicantProtocol,
        SupplicantService->ImageHandle,
        ChildHandle,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR(Status)) {
        return EFI_UNSUPPORTED;
    }

    Instance = SUPPLICANT_INSTANCE_FROM_SUPP_PROTO(SupplicantProtocol);
    gBS->CloseProtocol(ChildHandle,
        &gEfiSupplicantProtocolGuid,
        SupplicantService->ImageHandle,
        ChildHandle);

    Status = gBS->UninstallMultipleProtocolInterfaces(
        ChildHandle,
        &gEfiSupplicantProtocolGuid, &Instance->SupplicantProtocol,
        &gEfiEapConfigurationProtocolGuid, &Instance->EapCfgProtocol,
        NULL
    );
    if (EFI_ERROR(Status)) {
        return Status;
    }

    OldTpl = gBS->RaiseTPL(TPL_CALLBACK);

    RemoveEntryList(&Instance->Node);
    SupplicantService->ChildrenNumber--;

    gBS->RestoreTPL(OldTpl);

    SupplicantServiceDeinitInstance(SupplicantService, Instance);

    FreePool(Instance);

    return Status;
}

EFI_STATUS
EFIAPI
SupplicantDriverEntryPoint(
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
)
{
    EFI_STATUS Status;
    EFI_HANDLE SupplicantSvcBindingHandle = NULL;
    UINTN HandleArraySize = sizeof(SupplicantSvcBindingHandle);
    EFI_LOADED_IMAGE_PROTOCOL *Image;

    WallTimerAttach();

    Status = gBS->HandleProtocol(
        ImageHandle,
        &gEfiLoadedImageProtocolGuid,
        (VOID**)&Image
    );
    if (EFI_ERROR(Status))
        goto Exit;

    gSupplicantService.Image = Image;

    GlobalLoggingContextInitialize(Image);

    Status = gBS->LocateHandle(ByProtocol,
        &gEfiSupplicantServiceBindingProtocolGuid,
        NULL,
        &HandleArraySize,
        &SupplicantSvcBindingHandle);
    if (!EFI_ERROR(Status)) {
        goto Exit;
    }

    if (wpas_register()) {
        Status = EFI_DEVICE_ERROR;
        goto Exit;
    }

    InitializeListHead(&gSupplicantService.ChildrenList);
    gSupplicantService.Signature = SUPPLICANT_SERVICE_SIGNATURE;
    gSupplicantService.ServiceBinding.CreateChild = SupplicantServiceBindingCreateChild;
    gSupplicantService.ServiceBinding.DestroyChild = SupplicantServiceBindingDestroyChild;
    gSupplicantService.ImageHandle = ImageHandle;

    Status = gBS->InstallMultipleProtocolInterfaces(
        &ImageHandle,
        &gEfiSupplicantServiceBindingProtocolGuid, &gSupplicantService.ServiceBinding,
        NULL);

Exit:
    if (EFI_ERROR(Status)) {
        GlobalLoggingContextUninitialize();
        WallTimerDetach();
    }

    return Status;
}

EFI_STATUS
EFIAPI
SupplicantDriverUnload(
    IN EFI_HANDLE  ImageHandle
)
{
    EFI_STATUS Status;

    Status = gBS->UninstallMultipleProtocolInterfaces(
        ImageHandle,
        &gEfiSupplicantServiceBindingProtocolGuid, &gSupplicantService.ServiceBinding,
        NULL
    );
    if (EFI_ERROR(Status))
        return Status;

    GlobalLoggingContextUninitialize();
    WallTimerDetach();

    return EFI_SUCCESS;
}