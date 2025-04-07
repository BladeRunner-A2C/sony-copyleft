/** @file
  Copyright (c) 2023, Qualcomm Technologies, Inc. All Rights Reserved.
**/

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/QcomArmScmiVendorProtocol.h>

#include "QcomScmiPrivate.h"
#include <scmi_platform.h>
#include "QcomArmScmiVendorProtocolPrivate.h"
#include "ScmiPlatformMemory.h"

/** Return version of the Qcom vendor protocol supported by SCP firmware.

  @param[in]  This          A Pointer to SCMI_QCOM_Vendor_PROTOCOL Instance.
  
  @param[in]  DestPlatform  Enum for SCMI destination.

  @param[out] Version       Version of the supported SCMI Qcom Vendor protocol.

  @retval EFI_SUCCESS       The version is returned.
  @retval EFI_DEVICE_ERROR  SCP returns an SCMI error.
  @retval !(EFI_SUCCESS)    Other errors.
**/
STATIC
EFI_STATUS
VendorGetVersion (
  IN  SCMI_QCOM_VENDOR_PROTOCOL *This,
  IN  SCMI_PLATFORM_TYPE        DestPlatform,
  OUT UINT32                    *Version
  )
{
  return ScmiGetProtocolVersion (ScmiProtocolIdQcomVendor, DestPlatform, Version);
}

/** Send a Qcom SCMI vendor protocol message.

  @param[in]  This              A Pointer to SCMI_QCOM_VENDOR_PROTOCOL Instance.
  
  @param[in]  DestPlatform      Enum for SCMI destination.
  
  @param[in]  MessageId         Enum for Message ID type.
  
  @param[in]  AlgoStr           Pointer to requested Algorithm string.
  
  @param[in]  ParamId           Parameter ID.
  
  @param[in]  MessageParams     Message payload to be sent.
  
  @param[in]  MessageParamCount Message payload length.

  @param[out] ReturnValues      Response of the sent message.

  @retval EFI_SUCCESS       The send is successful.
  @retval EFI_DEVICE_ERROR  SCP returns an SCMI error.
  @retval !(EFI_SUCCESS)    Other errors.
**/
STATIC
EFI_STATUS
QcomVendorSend (
  IN  SCMI_QCOM_VENDOR_PROTOCOL *This,
  IN  SCMI_PLATFORM_TYPE        DestPlatform,
  IN  QCOM_SCMI_MSG_ID_TYPE     MessageId,
  IN  CHAR8                     *AlgoStr,
  IN  UINT32                    ParamId,
  IN  UINT32                    *MessageParams,
  IN  UINT32                    MessageParamCount,
  OUT UINT32                    **ReturnValues
  )
{
  EFI_STATUS    Status;
  INT32         Idx;
  UINT32        PayloadLength;
  SCMI_COMMAND  Cmd;
  UINT32        *TxPayload;

  Status = ScmiCommandGetPayload (DestPlatform, &TxPayload);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  TxPayload[1] = 0;
  TxPayload[2] = 0;
  CopyMem(&TxPayload[1], AlgoStr, AsciiStrLen(AlgoStr));

  TxPayload[3] = ParamId;

  for ( Idx = 0; Idx < MessageParamCount; Idx++) {
    TxPayload[Idx + 4] = MessageParams[Idx];
  }

  Cmd.ProtocolId = ScmiProtocolIdQcomVendor;
  Cmd.MessageId = MessageId;

  PayloadLength = sizeof(UINT32) * (4 + MessageParamCount);

  Status = ScmiCommandExecute (
             &Cmd,
             DestPlatform,
             &PayloadLength,
             ReturnValues
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}

/** Register a vendor protocol handler.

  @param[in]  AlgoStr      Pointer to requested Algorithm string.
  
  @param[in]  Callback     Function pointer to be registered for the callback.
  
  @param[in]  ChannelBase  Shared memory address to be used for communication.

  @retval EFI_SUCCESS      The callback is registered successfully.
  @retval !(EFI_SUCCESS)   Other errors.
**/
EFI_STATUS
QcomVendorRegisterCallback (
  IN CHAR8                      *AlgoStr,
  IN QCOM_VENDOR_CALLBACK_TYPE  Callback,
  IN UINT32                     ChannelBase
  )
{
  UINT32 ret;
  UINT64 AlgoId = 0;

  CopyMem(&AlgoId, AlgoStr, AsciiStrLen(AlgoStr));
  ret = scmi_vendor_register_callback(ScmiProtocolIdQcomVendor, AlgoId, Callback,
          ChannelBase);

  if (ret == 0)
    return EFI_SUCCESS;
  else
    return ret;
}

/** Initializes the Mailbox channel status as free.
**/
STATIC
EFI_STATUS ScmiPlatformInit(void)
{
	EFI_STATUS Status = EFI_UNSUPPORTED;
	EFI_CHIPINFO_PROTOCOL *mChipInfoProtocol;
	UINT32 noOfFunctionalClus = 0;
	UINT32 cluster_no = 0, CoreMaskDefective = 0;
	UINT32 CoresPerCluster = FixedPcdGet64(PcdCorePerCluster);
	
	Status	= gBS->LocateProtocol(
								&gEfiChipInfoProtocolGuid,
								NULL,
								(VOID**)&mChipInfoProtocol
								);

	if (EFI_ERROR (Status))
	{
		DEBUG((EFI_D_ERROR, "Failed to locate chipinfo protocol: %r\n", Status));
		return Status;
	}
	
	Status = mChipInfoProtocol->GetNumFunctionalClusters(mChipInfoProtocol, &noOfFunctionalClus);
	
	if (EFI_ERROR (Status))
	{
		DEBUG((EFI_D_ERROR, "Failed to read NumFunctionalClusters: %r\n", Status));
		return Status;
	}
	else
	{
		//DEBUG((EFI_D_ERROR, "Total Functional Clusters: %d\n", noOfFunctionalClus));
	}
	
    while (noOfFunctionalClus) 
    {
		Status = mChipInfoProtocol->GetDefectiveCPUs(mChipInfoProtocol, cluster_no, &CoreMaskDefective); /* Returns Mask setting defective CPU's to 1 */
		if (EFI_ERROR (Status))
		{
			DEBUG((EFI_D_ERROR, "Failed to read DefectiveCPUs: %r\n", Status));
			//ASSERT (FALSE);
			return Status;
		}
		else
		{
			//DEBUG((EFI_D_ERROR, "Defective mask: 0x%x cluster: %d\n", CoreMaskDefective, cluster_no));
			
			if ((CoreMaskDefective & ((1 << CoresPerCluster) - 1)) != ((1 << CoresPerCluster) - 1))
			{
				//DEBUG((EFI_D_ERROR, "Functional cluster: %d\n", cluster_no));
				
				// Mark channel as free initially
				MARK_CHANNEL_FREE(PDP2UEFI_SharedMemory[cluster_no]->ChannelStatus);
				
				noOfFunctionalClus--;
			}
			cluster_no++;
		}
    }

	return EFI_SUCCESS;
}

// Instance of the SCMI Qcom Vendor protocol.
STATIC CONST SCMI_QCOM_VENDOR_PROTOCOL ScmiQcomVendorProtocol = {
	VendorGetVersion,
	QcomVendorSend,
	QcomVendorRegisterCallback
};

/** Initialize Qcom Vendor protocol and install protocol on a given handle.

  @param[in] Handle              Handle to install Qcom Vendor protocol.

  @retval EFI_SUCCESS            Qcom Vendor protocol interface installed successfully.
**/
EFI_STATUS
ScmiQcomVendorProtocolInit (
  IN EFI_HANDLE* Handle
  )
{
	EFI_STATUS Status;

	Status = ScmiPlatformInit();
	if (EFI_ERROR (Status))
	{
		DEBUG((EFI_D_ERROR, "Failed to Initialize Scmi Platform Stack: %r\n", Status));
		//ASSERT (FALSE);
		return Status;
	}

	return gBS->InstallMultipleProtocolInterfaces (
			Handle,
			&gArmScmiQcomVendorProtocolGuid,
			&ScmiQcomVendorProtocol,
			NULL
	);
}
