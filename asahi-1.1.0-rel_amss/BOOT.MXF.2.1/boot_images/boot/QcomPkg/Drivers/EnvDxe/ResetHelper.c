/** @file
    ResetHelper.c

  Copyright (c) 2023 Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 02/16/23   cm      initial version
=============================================================================*/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>

#include <Protocol/EFIResetReason.h>
#include <Protocol/EFIHWIO.h>
#include <Protocol/ResetNotification.h>

#include <Library/EfiResetSystemLib.h>

#define ROUND_TO_PAGE(x) (x & 0xfffff000)

EFI_EVENT ResetArchProtocolInstalledEvent = NULL;
EFI_EVENT ResetNotificationProtocolInstalledEvent = NULL;
EFI_EVENT VirtualAddressChangeEvt = NULL;
VOID *ResetArchProtocolRegistration = NULL;
VOID *ResetNotificationProtocolRegistration = NULL;

UINTN    PSHoldAddress = 0;

STATIC
EFI_STATUS
EFIAPI
EFI_Get_Reset_Reason(
   IN EFI_RESETREASON_PROTOCOL *This,
   IN OUT UINT32               *ResetReason,
   IN OUT CHAR16               *ResetReasonString,
   IN OUT UINT32               *ResetReasonStrLen
   )
{
  EFI_STATUS Status;
  Status = LibGetResetReason (ResetReason, ResetReasonString, ResetReasonStrLen);
  return Status;
}

STATIC
EFI_STATUS
EFIAPI
EFI_Clear_Reset_Reason(
   IN EFI_RESETREASON_PROTOCOL *This
   )
{
  EFI_STATUS Status;
  Status = LibClearResetReason ();
  return Status;
}


STATIC
EFI_RESETREASON_PROTOCOL ResetReasonProtocol =
{
  EFI_RESETREASON_PROTOCOL_REVISION,
  EFI_Get_Reset_Reason,
  EFI_Clear_Reset_Reason
};

/**
  This function will install the ResetReason protocol

  @param  None

  @retval EFI_SUCCESS           Call is successfull.

**/
EFI_STATUS
InstallResetReasonProtocol (
  VOID
  )
{
  EFI_STATUS Status;
  EFI_HANDLE  Handle = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (
               &Handle,
               &gEfiResetReasonProtocolGuid, (VOID**) &ResetReasonProtocol,
               NULL,
               NULL
               );
  ASSERT_EFI_ERROR (Status);
  return Status;
}

/**
  Virtual address change notification call back. It converts global pointer
  to virtual address.

  @param  Event         Event whose notification function is being invoked.
  @param  Context       Pointer to the notification function's context, which is
                        always zero in current implementation.

**/
VOID
EFIAPI
VirtualAddressChngCB (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  gRT->ConvertPointer(0, (VOID**)&PSHoldAddress);
  gRT->ConvertPointer(0, (VOID**)&gRT);
}



EFI_STATUS
EFIAPI
SetPSHoldAddressRangeAsRuntimeMemory ()
{
  EFI_STATUS Status = EFI_SUCCESS;
  EFI_GCD_MEMORY_SPACE_DESCRIPTOR  PSHoldMemoryDescriptor;
  EFI_HWIO_PROTOCOL *HWIOProtocol = NULL;
  UINTN    PSHoldAddress = 0;
  
  /* Setup PSHold */
  Status = gBS->LocateProtocol(&gEfiHwioProtocolGuid, NULL,
    (void**)&HWIOProtocol);
  if ((EFI_SUCCESS != Status) || (HWIOProtocol == NULL))
  {
    DEBUG ((EFI_D_ERROR, "ERROR: Failed to locate HWIO Protocol: 0x%08x\n", Status));
    return EFI_DEVICE_ERROR;
  }
  Status = HWIOProtocol->MapRegion(HWIOProtocol, "+MPM_POWER_STATE_HOLD", (UINT8**) &PSHoldAddress);
  if (EFI_SUCCESS != Status)
  {
    DEBUG ((EFI_D_ERROR, "ERROR: Failed to map PSHOLD register address: 0x%08x\n", Status));
    return EFI_DEVICE_ERROR;
  }
  if (PSHoldAddress == 0)
  {
    DEBUG ((EFI_D_ERROR, "ERROR: PSHOLD register address invalid!"));
    return EFI_DEVICE_ERROR;
  }


  /******** Setup HWIO access for runtime ********/
  /*
   * Get the GCD Memory Descriptor specified by PSHoldAddress page boundary
   */
  Status = gDS->GetMemorySpaceDescriptor (ROUND_TO_PAGE(PSHoldAddress), 
                                          &PSHoldMemoryDescriptor);
  ASSERT_EFI_ERROR (Status);

  /*
   * Mark the 4KB region as EFI_RUNTIME_MEMORY so the OS
   * will allocate a virtual address range.
   */
  Status = gDS->SetMemorySpaceAttributes (
                  ROUND_TO_PAGE(PSHoldAddress), 
                  EFI_PAGE_SIZE, 
                  PSHoldMemoryDescriptor.Attributes | EFI_MEMORY_RUNTIME);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

VOID
EFIAPI
ResetArchProtocolEnabledCb (
  IN EFI_EVENT Event,
  IN VOID *Context
)
{
  
  EFI_STATUS Status;
  Status = InstallResetReasonProtocol();
  if(EFI_ERROR(Status)) {
    DEBUG((EFI_D_WARN, "Reset Reason Protocol: Not installed!\n"));
  }
  
  Status = SetPSHoldAddressRangeAsRuntimeMemory();
  if(EFI_ERROR(Status)) {
    DEBUG((EFI_D_WARN, "PSHOLD Address not set as Runtime memory, Status: %s\n", Status));
    return;
  }
  
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  VirtualAddressChngCB,
                  NULL,
                  &gEfiEventVirtualAddressChangeGuid,
                  &VirtualAddressChangeEvt
                  );
  if(EFI_ERROR(Status)) {
    DEBUG((EFI_D_WARN, "VirtualAddressChngCB CreateEventex returned: %s!\n", Status));
  }
}


VOID
EnvResetSystem   (IN EFI_RESET_TYPE  ResetType,
  IN EFI_STATUS      ResetStatus,
  IN UINTN           DataSize,
  IN VOID            *ResetData OPTIONAL
  )
{
  /*Anything specific for Envdxe to do on Reset can be added here */
}

VOID
EFIAPI
ResetNotificationProtocolCb (
  IN EFI_EVENT Event,
  IN VOID *Context
)
{
  
  EFI_STATUS Status;
  EFI_RESET_NOTIFICATION_PROTOCOL *ResetNotifyProtocol = NULL;
  
  Status = gBS->LocateProtocol(&gEfiResetNotificationProtocolGuid, NULL,
    (void**)&ResetNotifyProtocol);
  if(EFI_ERROR(Status)) {
    DEBUG ((EFI_D_WARN, "Reset notification not located, Status:%r\n", Status));
    return;
  }
  
  Status = ResetNotifyProtocol->RegisterResetNotify(ResetNotifyProtocol, EnvResetSystem);
  ASSERT_EFI_ERROR (Status);
  gBS->CloseEvent (Event); 
}


EFI_STATUS
RegisterForResetArchProtocol(
 VOID
)
{
  EFI_STATUS Status;
  
  Status = gBS->CreateEvent (EVT_NOTIFY_SIGNAL, TPL_CALLBACK, ResetArchProtocolEnabledCb, NULL, &ResetArchProtocolInstalledEvent);
  
  if(EFI_ERROR(Status)) {
    DEBUG((EFI_D_WARN, "Reset Arch Protocol: Failed to create event!\n"));
    return Status;
  }
  
  Status = gBS->RegisterProtocolNotify (&gEfiResetArchProtocolGuid, ResetArchProtocolInstalledEvent, &ResetArchProtocolRegistration);
  if(EFI_ERROR(Status)) {
    DEBUG((EFI_D_WARN, "Failed to Register for Reset Arch Protocol!\n"));
    return Status;
  }

  return Status;

}

EFI_STATUS
RegisterForResetNotificationProtocol(
 VOID
)
{
  EFI_STATUS Status;
  
  Status = gBS->CreateEvent (EVT_NOTIFY_SIGNAL, TPL_CALLBACK, ResetNotificationProtocolCb, NULL, &ResetNotificationProtocolInstalledEvent);
  if(EFI_ERROR(Status)) {
    DEBUG((EFI_D_WARN, "Reset Notification Protocol : Failed to create event!\n"));
    return Status;
  }
  Status = gBS->RegisterProtocolNotify (&gEfiResetNotificationProtocolGuid, ResetNotificationProtocolInstalledEvent, &ResetNotificationProtocolRegistration);
  if(EFI_ERROR(Status)) {
    DEBUG((EFI_D_WARN, "Failed to Register Protocol notification for ResetNotificationProtocol !\n"));
    return Status;
  }
  
  return Status;

}
    
