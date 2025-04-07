/*===============================================================================
  Copyright (c) 2020-2023 Qualcomm Technologies, Inc.  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc

  FILE: 		SSRDxe.c
  DESCRIPTION:

  REVISION HISTORY
  when       who     	what, where, why
  --------   ---     	--------------------------------------------------------
  09/15/23   kk       add new APIs to support ssr bringup and shutdown
  12/29/22   kanandac Locate SSRGuid Protocol before init
  09/10/20	 yanw  	  initial version

================================================================================*/
#include <Protocol/EFISSR.h>
#include <Library/QcomTargetLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include "SSRCore.h"
#include "SSRNotifier.h"
#include "SSRSmp2p.h"

extern SSR_SUBSYS_CTX_TYPE**	SSRSubsysCtx;

STATIC EFI_STATUS EFI_SSR_RegisterSubsys(
    IN UINT32 SubsysId
    )
{    // todo add lock
    return RegisterSubsys(SubsysId);
}

STATIC EFI_STATUS EFI_SSR_RegisterCbForSubsys(
	IN CHAR8*							DrvName,
	IN UINT32							SubsysId,
	IN SSR_DRIVER_CB_TYPE*              Cb,
	IN UINT32							Prio
	)
{
	// todo add lock
	return RegisterCbForSubsys(DrvName,	SubsysId, Cb, Prio);

}

STATIC EFI_STATUS EFI_SSR_UnRegisterCbForSubsys(
	IN	CHAR8* DrvName,
	IN	UINT32 SubsysId
	)
{

	return UnRegisterCbForSubsys(DrvName, SubsysId);

}

STATIC EFI_STATUS EFI_SSR_ModifyRestartLvl(
	IN UINT32  SubsysId,
	IN RESTART_LEVEL Lvl
	)
{
	// todo add lock
	return ModifyRestartLvl(SubsysId, Lvl);
}

STATIC EFI_STATUS EFI_SSR_CheckIfSubsysUp(
	IN UINT32  SubsysId,
	IN OUT BOOLEAN* SubsysUp
)
{	
	EFI_STATUS Status;
	SSR_SUBSYS_STATUS St = SSR_SUBSYS_STATUS_UNKOWN;
	
	Status = CheckSubsysStatus(SubsysId, &St);
	if (Status == EFI_SUCCESS) *SubsysUp = (St==SSR_SUBSYS_STATUS_UP);
	return Status;
}

STATIC EFI_STATUS EFI_SSR_ShutdownSubsys(IN UINT32 SubsysId)
{
	return ShutdownSubsys(SubsysId, FALSE);
}

STATIC EFI_STATUS EFI_SSR_BringupSubsys(IN CHAR8* SubsysName)
{
	return BringupSubsys(SubsysName, NULL);
}

STATIC EFI_SSR_PROTOCOL SSRProtocol =
{
   EFI_SSR_PROTOCOL_VERSION_V3,
   EFI_SSR_RegisterSubsys,
   EFI_SSR_RegisterCbForSubsys,
   EFI_SSR_ModifyRestartLvl,
   EFI_SSR_UnRegisterCbForSubsys,
   EFI_SSR_ShutdownSubsys,
   EFI_SSR_BringupSubsys,
   EFI_SSR_CheckIfSubsysUp
};

EFI_STATUS SSRDxeEntry
(
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
)
{
  EFI_HANDLE Handle = NULL;
  EFI_STATUS         Status   = EFI_LOAD_ERROR;
  EFI_SSR_PROTOCOL* SSRInterface;

  Status = gBS->LocateProtocol (&gEfiSSRProtocolGuid,
                                NULL,
                                (VOID**)&SSRInterface);

  if(Status != EFI_NOT_FOUND){
    DEBUG ((EFI_D_ERROR,"SSRdxe is already initialized..\n"));
    return Status;
  }

  Status = LoadSSRSubsystemConfigFromDT();
  if (EFI_ERROR(Status))
	return Status;

  SSRSubsysCtx = AllocateZeroPool(sizeof(SSR_SUBSYS_CTX_TYPE *) * MaxSubsysConfigured);
  if (SSRSubsysCtx==NULL)
	  return EFI_OUT_OF_RESOURCES;

  SSRNotifInit();

  Status = gBS->InstallMultipleProtocolInterfaces(
						&Handle,
						&gEfiSSRProtocolGuid,
						(VOID **)&SSRProtocol,
						NULL );

  return Status;
}
