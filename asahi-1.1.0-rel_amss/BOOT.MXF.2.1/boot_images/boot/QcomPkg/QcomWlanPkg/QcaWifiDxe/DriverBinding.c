/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
  Copyright (C) 2013, Red Hat, Inc.
  Copyright (c) 2006 - 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials are licensed and made available
  under the terms and conditions of the BSD License which accompanies this
  distribution. The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN ""AS IS"" BASIS, WITHOUT
  WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED
**/

/** @file
  Provides interface to advanced shell functionality for parsing both handle and protocol database.

  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>
  (C) Copyright 2013-2015 Hewlett-Packard Development Company, L.P.<BR>
  (C) Copyright 2015-2016 Hewlett Packard Enterprise Development LP<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 18/11/21  zxue     refine code
 23/7/21   zxue     add missing copyright
 14/7/21   zxue     branch for core boot

=============================================================================*/
#include <Library/UefiLib.h>
#include <Pi/PiFirmwareVolume.h>
#include <Pi/PiFirmwareFile.h>
#include <Protocol/FirmwareVolume2.h>

#include <net/ether.h>
#include <net/net80211.h>
#include <qdf/pci.h>
#include "Version.h"
#include "Debug.h"
#include "Dev.h"
#include "QcaWlan.h"
#include "Aip.h"
#include "Snp.h"

extern EFI_QCWLAN_DEVICE_CONTEXT gWlanDriverContext;

struct net80211_notifier gNet80211UefiNotifier = { 0 };

VOID QcWlanOnNet80211DeviceAdded(struct net80211_pdev *pdev, void *ctx);
VOID QcWlanOnNet80211DeviceRemoved(struct net80211_pdev *pdev, void *ctx);
VOID QcWlanOnNet80211DeviceNotification(struct net80211_pdev *pdev,
    struct net80211_dev_event *devt, void *ctx);

STATIC
VOID
QcWlanStopDevice(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
)
{
    DbgPrint("Stop the device");

    pci_remove(&Dev->PciDev);

    net80211_deinit(&gNet80211UefiNotifier);
}

VOID
EFIAPI
QcWlanSnpExitBoot(
    IN  EFI_EVENT Event,
    IN  VOID      *Context
)
{
    QcWlanUninitializeNic((EFI_QCWLAN_DEVICE_CONTEXT *)Context);
}

STATIC
EFI_STATUS
EFIAPI
QcWlanSnpPopulate(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
)
{
    EFI_STATUS Status;
    UINT8 DevMacAddress[ETHER_ADDR_LEN] = { 0, };

    DbgPrint("Enter");

    //
    // We set up a function here that is asynchronously callable by an
    // external application to check if there are any packets available for
    // reception. The least urgent task priority level we can specify for such a
    // "software interrupt" is TPL_CALLBACK.
    //
    // TPL_CALLBACK is also the maximum TPL an SNP implementation is allowed to
    // run at (see 6.1 Event, Timer, and Task Priority Services in the UEFI
    // Specification 2.3.1+errC).
    //
    // Since we raise our TPL to TPL_CALLBACK in every single function that
    // accesses the device, and the external application also queues its interest
    // for received packets at the same TPL_CALLBACK, in effect the
    // QcWlanSnpIsPacketAvailable() function will never interrupt any
    // device-accessing driver function, it will be scheduled in isolation.
    //
    // TPL_CALLBACK (which basically this entire driver runs at) is allowed
    // for "[l]ong term operations (such as file system operations and disk
    // I/O)". Because none of our functions block, we'd satisfy an even stronger
    // requirement.
    //
    Status = gBS->CreateEvent(EVT_NOTIFY_WAIT, TPL_CALLBACK,
        &QcWlanSnpIsPacketAvailable, Dev, &Dev->Snp.WaitForPacket);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Dev->Snp.Revision = EFI_SIMPLE_NETWORK_PROTOCOL_REVISION;
    Dev->Snp.Start = &QcWlanSnpStart;
    Dev->Snp.Stop = &QcWlanSnpStop;
    Dev->Snp.Initialize = &QcWlanSnpInitialize;
    Dev->Snp.Reset = &QcWlanSnpReset;
    Dev->Snp.Shutdown = &QcWlanSnpShutdown;
    Dev->Snp.ReceiveFilters = &QcWlanSnpReceiveFilters;
    Dev->Snp.StationAddress = &QcWlanSnpStationAddress;
    Dev->Snp.Statistics = &QcWlanSnpStatistics;
    Dev->Snp.MCastIpToMac = &QcWlanSnpMcastIpToMac;
    Dev->Snp.NvData = &QcWlanSnpNvData;
    Dev->Snp.GetStatus = &QcWlanSnpGetStatus;
    Dev->Snp.Transmit = &QcWlanSnpTransmit;
    Dev->Snp.Receive = &QcWlanSnpReceive;
    Dev->Snp.Mode = &Dev->Snm;

    Dev->Snm.State = EfiSimpleNetworkStopped;
    Dev->Snm.HwAddressSize = ETH_ALEN;
    Dev->Snm.MediaHeaderSize = ETH_HLEN;
    Dev->Snm.MaxPacketSize = 1500;
    Dev->Snm.NvRamSize = 0;
    Dev->Snm.NvRamAccessSize = 0;
    Dev->Snm.ReceiveFilterMask = EFI_RECEIVE_FILTERS_NO_MCAST;
    Dev->Snm.ReceiveFilterSetting = EFI_RECEIVE_FILTERS_NO_MCAST;
    Dev->Snm.MaxMCastFilterCount = 0;
    Dev->Snm.MCastFilterCount = 0;
    Dev->Snm.IfType = NET_IFTYPE_ETHERNET;
    Dev->Snm.MacAddressChangeable = FALSE;
    Dev->Snm.MultipleTxSupported = TRUE;

    ASSERT(ETHER_ADDR_LEN <= sizeof(EFI_MAC_ADDRESS));

    QcWlanGetMacAddress(Dev, DevMacAddress);

    CopyMem(&Dev->Snm.CurrentAddress, DevMacAddress, ETHER_ADDR_LEN);
    CopyMem(&Dev->Snm.PermanentAddress, &Dev->Snm.CurrentAddress, ETHER_ADDR_LEN);
    SetMem(&Dev->Snm.BroadcastAddress, ETHER_ADDR_LEN, 0xFF);

    // media is set as present only when WiFi is connected
    Dev->Snm.MediaPresentSupported = TRUE;
    Dev->Snm.MediaPresent = FALSE;

    Status = gBS->CreateEvent(EVT_SIGNAL_EXIT_BOOT_SERVICES, TPL_CALLBACK,
        &QcWlanSnpExitBoot, Dev, &Dev->ExitBoot);
    if (EFI_ERROR(Status)) {
        goto CloseWaitForPacket;
    }

    return EFI_SUCCESS;

CloseWaitForPacket:
    gBS->CloseEvent(Dev->Snp.WaitForPacket);
    return Status;
}

STATIC
VOID
EFIAPI
QcWlanSnpEvacuate(
    IN OUT EFI_QCWLAN_DEVICE_CONTEXT *Dev
)
{
    //
    // This function runs either at TPL_CALLBACK already (from
    // QcWlanDrvBindingStop()), or it is part of a teardown following
    // a partial, failed construction in QcaDrvBindingStart(), when
    // WaitForPacket was never accessible to the world.
    //
    gBS->CloseEvent(Dev->ExitBoot);
    gBS->CloseEvent(Dev->Snp.WaitForPacket);
}

STATIC
EFI_STATUS
QcWlanCreateEmptyDevice(
	IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_QCWLAN_DEVICE_CONTEXT 	*Dev,
    IN EFI_HANDLE                	ControllerHandle
)
{
	EFI_STATUS Status;
	EFI_DEVICE_PATH_PROTOCOL *DevicePath = NULL;
    DbgPrint("Create a empty device");
	
    // Build device path
    DevicePath = QcWlanBuildDevicePath(Dev, ControllerHandle, This);
    if (DevicePath == NULL) {
        DbgError("Failed to create device path\n");
        Status = EFI_OUT_OF_RESOURCES;
        return Status;
    }

	Status = gBS->InstallMultipleProtocolInterfaces(&Dev->MacHandle,
        &gEfiDevicePathProtocolGuid, Dev->DevicePathProtocol,
        NULL);
    if (EFI_ERROR(Status)) {
        DbgError("Failed to install DevicePath protocols: %r\n", Status);
        return Status;
    }

	return EFI_SUCCESS;
}

CHAR16 *
EFIAPI
QcGetStringNameFromHandle (
  IN CONST EFI_HANDLE  TheHandle  
  )
{
  EFI_COMPONENT_NAME2_PROTOCOL  *CompNameStruct;
  EFI_STATUS                    Status;
  CHAR16                        *RetVal;
  CHAR8                         *BestLang = "en";

  Status = gBS->OpenProtocol (
                  TheHandle,
                  &gEfiComponentName2ProtocolGuid,
                  (VOID **)&CompNameStruct,
                  gImageHandle,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (!EFI_ERROR (Status)) {
    Status = CompNameStruct->GetDriverName (CompNameStruct, BestLang, &RetVal);
    if (!EFI_ERROR (Status)) {
      return (RetVal);
    }
  }

  Status = gBS->OpenProtocol (
                  TheHandle,
                  &gEfiComponentNameProtocolGuid,
                  (VOID **)&CompNameStruct,
                  gImageHandle,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (!EFI_ERROR (Status)) {
    Status = CompNameStruct->GetDriverName (CompNameStruct, BestLang, &RetVal);
    if (!EFI_ERROR (Status)) {
      return (RetVal);
    }
  }

  return (NULL);
}

CHAR16 *
QcGetImageNameFromHandle (
  IN CONST EFI_HANDLE Handle
  )
{
  EFI_STATUS                        Status;
  EFI_DRIVER_BINDING_PROTOCOL       *DriverBinding;
  EFI_LOADED_IMAGE_PROTOCOL         *LoadedImage;
  EFI_DEVICE_PATH_PROTOCOL          *DevPathNode;
  EFI_GUID                          *NameGuid;
  CHAR16                            *ImageName;
  UINTN                             BufferSize;
  UINT32                            AuthenticationStatus;
  EFI_FIRMWARE_VOLUME2_PROTOCOL     *Fv2;

  LoadedImage   = NULL;
  DriverBinding = NULL;
  ImageName     = NULL;

  Status = gBS->OpenProtocol (
                  Handle,
                  &gEfiDriverBindingProtocolGuid,
                  (VOID **) &DriverBinding,
                  NULL,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
      return NULL;
  }
  Status = gBS->OpenProtocol (
                  DriverBinding->ImageHandle,
                  &gEfiLoadedImageProtocolGuid,
                  (VOID**)&LoadedImage,
                  gImageHandle,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (!EFI_ERROR (Status)) {
    DevPathNode = LoadedImage->FilePath;
    if (DevPathNode == NULL) {
      return NULL;
    }
    while (!IsDevicePathEnd (DevPathNode)) {
      NameGuid = EfiGetNameGuidFromFwVolDevicePathNode ((MEDIA_FW_VOL_FILEPATH_DEVICE_PATH *)DevPathNode);
      if (NameGuid != NULL) {
        Status = gBS->HandleProtocol (
                        LoadedImage->DeviceHandle,
                        &gEfiFirmwareVolume2ProtocolGuid,
                        (VOID **)&Fv2
                        );
        if (!EFI_ERROR (Status)) {
          Status = Fv2->ReadSection (
                          Fv2,
                          NameGuid,
                          EFI_SECTION_USER_INTERFACE,
                          0,
                          (VOID **)&ImageName,
                          &BufferSize,
                          &AuthenticationStatus
                          );
          if (!EFI_ERROR (Status)) {
            break;
          }
          ImageName = NULL;
        }
      }
      //
      // Next device path node
      //
      DevPathNode = NextDevicePathNode (DevPathNode);
    }
    if (ImageName == NULL) {
      ImageName = ConvertDevicePathToText (LoadedImage->FilePath, TRUE, TRUE);
    }
  }
  return ImageName;
}

EFI_HANDLE*
EFIAPI
QcGetHandleListByProtocol (
  IN CONST EFI_GUID *ProtocolGuid OPTIONAL
  )
{
	EFI_HANDLE          *HandleList;
	UINTN               Size;
	EFI_STATUS          Status;

	Size = 0;
	HandleList = NULL;

	//
	// We cannot use LocateHandleBuffer since we need that NULL item on the ends of the list!
	//
	if (ProtocolGuid == NULL) {
		Status = gBS->LocateHandle(AllHandles, NULL, NULL, &Size, HandleList);
		if (Status == EFI_BUFFER_TOO_SMALL) {
			HandleList = AllocateZeroPool(Size + sizeof(EFI_HANDLE));
			if (HandleList == NULL) {
				return (NULL);
			}
			Status = gBS->LocateHandle(AllHandles, NULL, NULL, &Size, HandleList);
			HandleList[Size/sizeof(EFI_HANDLE)] = NULL;
		}
	} else {
		Status = gBS->LocateHandle(ByProtocol, (EFI_GUID*)ProtocolGuid, NULL, &Size, HandleList);
		if (Status == EFI_BUFFER_TOO_SMALL) {
			HandleList = AllocateZeroPool(Size + sizeof(EFI_HANDLE));
			if (HandleList == NULL) {
				return (NULL);
			}
			Status = gBS->LocateHandle(ByProtocol, (EFI_GUID*)ProtocolGuid, NULL, &Size, HandleList);
			HandleList[Size/sizeof(EFI_HANDLE)] = NULL;
		}
	}
	if (EFI_ERROR(Status)) {
		if (HandleList != NULL) {
			FreePool(HandleList);
		}
		return (NULL);
	}
	return (HandleList);
}

EFI_STATUS
QcWlanDrvCheckNetworkStack()
{
	EFI_HANDLE *HandleList = NULL;
	EFI_HANDLE *HandleWalker;
	CHAR16     *ImageName;
	CHAR16     *DriverName;
	
	HandleList = QcGetHandleListByProtocol(&gEfiDriverBindingProtocolGuid);
	for (HandleWalker = HandleList ; HandleWalker != NULL && *HandleWalker != NULL ; HandleWalker++){
		ImageName = QcGetImageNameFromHandle(*HandleWalker);
		if (ImageName != NULL && 
			(StrCmp(ImageName, L"MnpDxe") == 0 ||
			 StrCmp(ImageName, L"Ip4Dxe") == 0 ||
			 StrCmp(ImageName, L"Ip6Dxe") == 0 )) {
			DbgInfo("Find Netwkork Stack ImageName = %s\n", ImageName);
			return EFI_SUCCESS;
		}

		DriverName = QcGetStringNameFromHandle(*HandleWalker);
		if (DriverName != NULL && 
			(StrCmp(DriverName, L"MNP Network Service Driver") == 0 ||
			 StrCmp(DriverName, L"IP4 Network Service Driver") == 0 ||
			 StrCmp(DriverName, L"IP6 Network Service Driver") == 0 )) {
			DbgInfo("Find Netwkork Stack DriverName = %s\n", DriverName);
			return EFI_SUCCESS;
		}
	}

	return EFI_NOT_FOUND;
}

static
EFI_STATUS
EFIAPI
QcWlanDrvBindingSupported(
    IN EFI_DRIVER_BINDING_PROTOCOL            *This,
    IN EFI_HANDLE                             ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL               *RemainingDevicePath
)
{
    EFI_STATUS Status;
    QCA_HARDWARE_ID *DevHwId = &gWlanDriverContext.PciDev.HardwareId;
    EFI_PCI_IO_PROTOCOL *PciIo = NULL;
    PCI_TYPE00 Pci;
    const struct pci_device_id *device_id;

    (void)RemainingDevicePath;

    Status = gBS->OpenProtocol(ControllerHandle, &gEfiPciIoProtocolGuid,
        (VOID **)&PciIo, This->DriverBindingHandle,
        ControllerHandle,
        EFI_OPEN_PROTOCOL_BY_DRIVER);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint32,
        0, sizeof(Pci) / sizeof(UINT32),
        &Pci);
    if (EFI_ERROR(Status)) {
        DbgError("Failed to read PCI cfg info: %r\n", Status);
        goto cleanup;
    }

    Status = EFI_NOT_FOUND;

    device_id = pci_match(Pci.Hdr.VendorId, Pci.Hdr.DeviceId,
        Pci.Device.SubsystemVendorID, Pci.Device.SubsystemID);

    if (device_id) {

        BUILD_BUG_ON(sizeof(*DevHwId) != sizeof(*device_id));

        CopyMem(DevHwId, device_id, sizeof(*device_id));
        
        DbgPrint("Found supported WiFi device: VendorId: 0x%x, "
            "DeviceId: 0x%x, SubsystemVendorId: 0x%x, SubsystemId: 0x%x, "
            "FirmwareAttributes: 0x%x",
            DevHwId->VendorId, DevHwId->DeviceId,
            DevHwId->SubsystemVendorId, DevHwId->SubsystemId,
            DevHwId->FirmwareAttributes);

		Status = QcWlanDrvCheckNetworkStack();
    }

cleanup:
    gBS->CloseProtocol(ControllerHandle, &gEfiPciIoProtocolGuid,
        This->DriverBindingHandle, ControllerHandle);

    return Status;
}

static
EFI_STATUS
EFIAPI
QcWlanDrvBindingStart(
    IN EFI_DRIVER_BINDING_PROTOCOL* This,
    IN EFI_HANDLE                   ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath)
{
    EFI_STATUS Status;
    EFI_QCWLAN_DEVICE_CONTEXT *Dev = &gWlanDriverContext;
    EFI_PCI_IO_PROTOCOL *PciIo;

    EFI_DEVICE_PATH_PROTOCOL *DevicePath = NULL;
    EFI_HANDLE SnpHandle = NULL;
    VOID *Child = NULL;
    EFI_TPL OldTpl;
    int ret;

    OldTpl = gBS->RaiseTPL(TPL_CALLBACK);

    if (Dev->Started == DEV_START_SUCC) {
        DbgError("Already Started\n");
        Status = EFI_DEVICE_ERROR;
        goto RestoreTpl;
    }

    DbgPrint("Start");

    Dev->Signature = QCWLAN_DRIVER_SIGNATURE;

    Status = gBS->OpenProtocol(ControllerHandle,
        &gEfiPciIoProtocolGuid,
        (VOID**)&PciIo, This->DriverBindingHandle,
        ControllerHandle, EFI_OPEN_PROTOCOL_BY_DRIVER);
    if (EFI_ERROR(Status)) {
        DbgError("Failed to open PciIo protocol: %r\n", Status);
        goto RestoreTpl;
    }

    // Initialize PciDevice
    Dev->PciDev.PciIo = PciIo;
    Dev->PciDev.OriginalPciAttributes = 0;

    // Initialize the firmware trace
    GlobalLoggingFirmwareTraceInitialize();

    // Net80211 initialize
    gNet80211UefiNotifier.ctx = &Dev->WiFi;
    gNet80211UefiNotifier.dev_registered = QcWlanOnNet80211DeviceAdded;
    gNet80211UefiNotifier.dev_unregistered = QcWlanOnNet80211DeviceRemoved;
    gNet80211UefiNotifier.dev_notify = QcWlanOnNet80211DeviceNotification;
    ret = net80211_init(&gNet80211UefiNotifier);
    if (ret) {
        Status = EFI_DEVICE_ERROR;
        DbgError("Failed to initalize net80211: 0x%x\n", ret);
        goto ClosePciIo;
    }

    // Probe device
    ret = pci_probe(&Dev->PciDev);
    if (ret) {
        Status = EFI_DEVICE_ERROR;
        DbgError("Failed to probe device: 0x%x\n", ret);
        goto DeinitializeNet80211;
    }

    Status = QcWlanSnpPopulate(Dev);
    if (EFI_ERROR(Status)) {
        DbgError("Failed to populate SNP: %r\n", Status);
        goto RemoveDevice;
    }

    // Build device path
    DevicePath = QcWlanBuildDevicePath(Dev, ControllerHandle, This);
    if (DevicePath == NULL) {
        DbgError("Failed to create device path\n");
        Status = EFI_OUT_OF_RESOURCES;
        goto SnpEvacuate;
    }

    // Check if the driver is already loaded
    Dev->DevicePathProtocol = DevicePath;
    Status = gBS->LocateDevicePath(&gEfiSimpleNetworkProtocolGuid, &DevicePath,
        &SnpHandle);
    if (!EFI_ERROR(Status)) {
        DbgError("Already started - Found existing SNP handle on DevicePath\n");
        Status = EFI_ALREADY_STARTED;
        goto FreeDevicePath;
    }

    // Initialize AIP
    Dev->Aip.GetInformation = QcWlanAipGetInfo;
    Dev->Aip.GetSupportedTypes = QcWlanAipGetSupportedTypes;
    Dev->Aip.SetInformation = QcWlanAipSetInfo;

    Status = gBS->InstallMultipleProtocolInterfaces(&Dev->MacHandle,
        &gEfiSimpleNetworkProtocolGuid, &Dev->Snp,
        &gEfiAdapterInformationProtocolGuid, &Dev->Aip,
        &gEfiDevicePathProtocolGuid, Dev->DevicePathProtocol,
        NULL);
    if (EFI_ERROR(Status)) {
        DbgError("Failed to install SNP/DevicePath/AIP protocols: %r\n",
            Status);
        goto FreeDevicePath;
    }

    Status = gBS->OpenProtocol(ControllerHandle, &gEfiPciIoProtocolGuid,
        &Child, This->DriverBindingHandle,
        Dev->MacHandle, EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER);
    if (EFI_ERROR(Status)) {
        DbgError("Failed to open PciIo protocol by controller: %r\n", Status);
        goto UninstallMultiple;
    }

    Status = QcWlanInstallConnectionProtocols(Dev);
    if (EFI_ERROR(Status)) {
        DbgError("Failed to install WLAN connection protocols: %r\n", Status);
        goto CloseChildProtocol;
    }

    DbgPrint("Binding success\n");
    Dev->Started = DEV_START_SUCC;
    gBS->RestoreTPL(OldTpl);
    DbgFlush();
    return EFI_SUCCESS;

CloseChildProtocol:
    gBS->CloseProtocol(ControllerHandle, &gEfiPciIoProtocolGuid,
        This->DriverBindingHandle, Dev->MacHandle);

UninstallMultiple:
    gBS->UninstallMultipleProtocolInterfaces(Dev->MacHandle,
        &gEfiDevicePathProtocolGuid, Dev->DevicePathProtocol,
        &gEfiAdapterInformationProtocolGuid, &Dev->Aip,
        &gEfiSimpleNetworkProtocolGuid, &Dev->Snp,
        NULL);

FreeDevicePath:
    FreePool(Dev->DevicePathProtocol);

SnpEvacuate:
    QcWlanSnpEvacuate(Dev);

RemoveDevice:
    pci_remove(&Dev->PciDev);

DeinitializeNet80211:
    net80211_deinit(&gNet80211UefiNotifier);
	if (ret) {
		// If can not find matched fw from FV/Partition, mark as DEV_START_FW_FAIL
		if (ret == -ENOEXEC || ret == -EFTYPE || 
			ret == -EAUTH || ret == -EFAULT) {
			DbgError("Failed to find matched fw file: 0x%x\n", ret);
			Dev->Started = DEV_START_FW_FAIL;
		}
		
		QcWlanCreateEmptyDevice(This, Dev, ControllerHandle);
		gBS->RestoreTPL(OldTpl);
	    return EFI_SUCCESS;
	}

ClosePciIo:
    gBS->CloseProtocol(ControllerHandle, &gEfiPciIoProtocolGuid,
        This->DriverBindingHandle, ControllerHandle);

RestoreTpl:
    gBS->RestoreTPL(OldTpl);
    DbgError("Failed to start: %r\n", Status);
    return Status;
}

static
EFI_STATUS
EFIAPI
QcWlanDrvBindingStop(
    IN EFI_DRIVER_BINDING_PROTOCOL           *This,
    IN EFI_HANDLE                            ControllerHandle,
    IN UINTN                                 NumberOfChildren,
    IN EFI_HANDLE                            *ChildHandleBuffer
)
{
    EFI_QCWLAN_DEVICE_CONTEXT *Dev = &gWlanDriverContext;
    EFI_STATUS Status;

    DbgPrint("NumberOfChildren %d", NumberOfChildren);

    if (NumberOfChildren > 0) {
        EFI_SIMPLE_NETWORK_PROTOCOL *Snp;
        EFI_TPL                     OldTpl;

        ASSERT(NumberOfChildren == 1);

        Status = gBS->OpenProtocol(ChildHandleBuffer[0],
            &gEfiSimpleNetworkProtocolGuid, (VOID **)&Snp,
            This->DriverBindingHandle, ControllerHandle,
            EFI_OPEN_PROTOCOL_GET_PROTOCOL);
        if (EFI_ERROR(Status)) {
            DbgError("Failed to open simple network protocol: %r\n", Status);
        }

        Dev = QCWLAN_DEV_FROM_SNP(Snp);
        OldTpl = gBS->RaiseTPL(TPL_CALLBACK);

        WARN_ON(Dev->MacHandle != ChildHandleBuffer[0]);
        if (Dev->Snm.State != EfiSimpleNetworkStopped) {
            Status = EFI_DEVICE_ERROR;
            DbgError("Driver stop failed: %r\n", Status);
        }
        else {
            QcWlanUninstallConnectionProtocols(Dev);

            QcWlanStopDevice(Dev);

            GlobalLoggingFirmwareTraceUninitialize();

            Status = gBS->CloseProtocol(ControllerHandle, &gEfiPciIoProtocolGuid,
                This->DriverBindingHandle, Dev->MacHandle);
            if (EFI_ERROR(Status)) {
                DbgError("Failed to close pci io protocol: %r\n", Status);
            }

            Status = gBS->UninstallMultipleProtocolInterfaces(Dev->MacHandle,
                &gEfiDevicePathProtocolGuid, Dev->DevicePathProtocol,
                &gEfiAdapterInformationProtocolGuid, &Dev->Aip,
                &gEfiSimpleNetworkProtocolGuid, &Dev->Snp,
                NULL);
            if (EFI_ERROR(Status)) {
                DbgError("Failed to unstall simple network protocol: %r\n", Status);
            }

            FreePool(Dev->DevicePathProtocol);
            QcWlanSnpEvacuate(Dev);
        }

        gBS->RestoreTPL(OldTpl);
        Dev->Started = DEV_START_INIT;
        return Status;
    }

    Status = gBS->CloseProtocol(ControllerHandle, &gEfiPciIoProtocolGuid,
        This->DriverBindingHandle, ControllerHandle);

    DbgPrint("Driver stopped: %r", Status);
    return Status;
}

EFI_DRIVER_BINDING_PROTOCOL gQcWlanDrvBinding = {
    QcWlanDrvBindingSupported,
    QcWlanDrvBindingStart,
    QcWlanDrvBindingStop,
    WLAN_DRV_VERSION,
    NULL,
    NULL
};
