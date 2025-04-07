/** @file

  Copyright (c) 2017-2021, Arm Limited. All rights reserved.<BR>
  Copyright (c) 2023, Qualcomm Technologies, Inc. All Rights Reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

  @par Specification Reference:
  - Arm System Control and Management Interface - Platform Design Document
    (https://developer.arm.com/documentation/den0056/)
**/

#include <Base.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/QcomArmScmiBaseProtocol.h>
#include <Protocol/QcomArmScmiVendorProtocol.h>

#include "QcomArmScmiBaseProtocolPrivate.h"
#include "QcomArmScmiVendorProtocolPrivate.h"
#include "QcomScmiDxe.h"
#include "QcomScmiPrivate.h"

STATIC CONST SCMI_PROTOCOL_ENTRY Protocols[] = {
  { ScmiProtocolIdBase, ScmiBaseProtocolInit },
  { ScmiProtocolIdQcomVendor, ScmiQcomVendorProtocolInit }
};

/** ARM SCMI driver entry point function.

  This function installs the SCMI Base protocol and a list of other
  protocols is queried using the Base protocol. If protocol is supported,
  driver will call each protocol init function to install the protocol on
  the ImageHandle.

  @param[in] ImageHandle     Handle to this EFI Image which will be used to
                             install Base, Clock and Performance protocols.
  @param[in] SystemTable     A pointer to boot time system table.

  @retval EFI_SUCCESS       Driver initalized successfully.
  @retval EFI_UNSUPPORTED   If SCMI base protocol version is not supported.
  @retval !(EFI_SUCCESS)    Other errors.
**/
EFI_STATUS
EFIAPI
QcomScmiDxeEntryPoint (
  IN EFI_HANDLE             ImageHandle,
  IN EFI_SYSTEM_TABLE       *SystemTable
  )
{
  EFI_STATUS            Status;
  SCMI_BASE_PROTOCOL    *BaseProtocol;
  UINT32                Version;
  UINT32                Index;
  UINT32                NumProtocols;
  UINT32                ProtocolIndex;
  UINT8                 *SupportedList;
  UINT32                SupportedListSize;
  EFI_CHIPINFO_PROTOCOL *mChipInfoProtocol;
  UINT32                bootCluster;
  UINT32                bootCore;

  //DEBUG ((EFI_D_ERROR, "***** ScmiDxe entry *****\r\n"));
  // Every SCMI implementation must implement the base protocol.
  //ASSERT (Protocols[0].Id == ScmiProtocolIdBase);
  if (Protocols[0].Id != ScmiProtocolIdBase)
  {
	  return EFI_UNSUPPORTED;
  }

  Status = ScmiBaseProtocolInit (&ImageHandle);
  if (EFI_ERROR (Status)) {
    //ASSERT (FALSE);
	DEBUG ((EFI_D_ERROR, "SCMI error: Unable to initialize BaseProtocol\n"));
    return Status;
  }

  Status = gBS->LocateProtocol (
                  &gArmScmiBaseProtocolGuid,
                  NULL,
                  (VOID**)&BaseProtocol
                  );
  if (EFI_ERROR (Status)) {
    //ASSERT (FALSE);
    DEBUG ((EFI_D_ERROR, "SCMI error: Unable to locate BaseProtocol\n"));
    return Status;
  }

  // Get SCMI Base protocol version from boot cluster. 
  Status = gBS->LocateProtocol(
				&gEfiChipInfoProtocolGuid,
				NULL,
				(VOID**)&mChipInfoProtocol
				);
  
  if (EFI_ERROR (Status)) {
	//ASSERT (FALSE);
	DEBUG ((EFI_D_ERROR, "SCMI error: Unable to locate ChipInfoProtocol\n"));
    return Status;
  }
  
  Status = mChipInfoProtocol->GetBootClusterAndCore(mChipInfoProtocol, &bootCluster, &bootCore);
  
  if (EFI_ERROR (Status)) {
	//ASSERT (FALSE);
	DEBUG ((EFI_D_ERROR, "SCMI error: Unable to get boot cluster\n"));
    return Status;
  }

  //DEBUG((EFI_D_ERROR, "Boot Cluster:%d\n", bootCluster));
  //DEBUG((EFI_D_ERROR, "Boot Core:%d\n", bootCore));
	
  Status = BaseProtocol->GetVersion (BaseProtocol, bootCluster, &Version);
  if (EFI_ERROR (Status)) {
    //ASSERT (FALSE);
    DEBUG ((EFI_D_ERROR, "SCMI error: Unable to get version\n"));
    return Status;
  }

  //DEBUG ((EFI_D_ERROR, "BaseVersion:0x%x\r\n", Version));

  // Accept any version between SCMI v1.0 and SCMI v2.0
  if ((Version < BASE_PROTOCOL_VERSION_V1) ||
    (Version > BASE_PROTOCOL_VERSION_V2)) {
    //ASSERT (FALSE);
    DEBUG ((EFI_D_ERROR, "SCMI error: Version not acceptable\n"));
    return EFI_UNSUPPORTED;
  }

  // Apart from Base protocol, SCMI may implement various other protocols,
  // query total protocols implemented by the SCP firmware.
  NumProtocols = 0;
  Status = BaseProtocol->GetTotalProtocols (BaseProtocol, bootCluster, &NumProtocols);
  if (EFI_ERROR (Status)) {
    //ASSERT (FALSE);
	DEBUG ((EFI_D_ERROR, "SCMI error: Unable to get no. of protocols\n"));
    return Status;
  }

  //DEBUG ((EFI_D_ERROR, "NumProtocols:0x%x\r\n", NumProtocols));

  //ASSERT (NumProtocols != 0);
  if (NumProtocols == 0)
  {
	  DEBUG ((EFI_D_ERROR, "SCMI error: No protocols supported by platform\n"));
	  return EFI_UNSUPPORTED;
  }

  SupportedListSize = (NumProtocols * sizeof (*SupportedList));

  Status = gBS->AllocatePool (
                  EfiBootServicesData,
                  SupportedListSize,
                  (VOID**)&SupportedList
                  );
  if (EFI_ERROR (Status)) {
    //ASSERT (FALSE);
    DEBUG ((EFI_D_ERROR, "SCMI error: Unable to allocate pool\n"));
    return Status;
  }

  // Get the list of protocols supported by SCP firmware on the platform.
  Status = BaseProtocol->DiscoverListProtocols (
                           BaseProtocol,
						   bootCluster,
                           &SupportedListSize,
                           SupportedList
                           );
  if (EFI_ERROR (Status)) {
    gBS->FreePool (SupportedList);
    //ASSERT (FALSE);
    DEBUG ((EFI_D_ERROR, "SCMI error: Unable to get supported protocols\n"));
    return Status;
  }

  // Install supported protocol on ImageHandle.
  for (ProtocolIndex = 1; ProtocolIndex < ARRAY_SIZE (Protocols);
       ProtocolIndex++) {
    for (Index = 0; Index < NumProtocols; Index++) {
      if (Protocols[ProtocolIndex].Id == SupportedList[Index]) {
        Status = Protocols[ProtocolIndex].InitFn (&ImageHandle);
        //DEBUG ((EFI_D_ERROR, "ProtocolIndex Init:0x%x\r\n", ProtocolIndex));
        if (EFI_ERROR (Status)) {
          //ASSERT_EFI_ERROR (Status);
          DEBUG ((EFI_D_ERROR, "SCMI error: Protocol initialization failure\n"));
          return Status;
        }
        break;
      }
    }
  }

  gBS->FreePool (SupportedList);

  //DEBUG ((EFI_D_ERROR, "SCMI stack init end\r\n"));

  return EFI_SUCCESS;
}

