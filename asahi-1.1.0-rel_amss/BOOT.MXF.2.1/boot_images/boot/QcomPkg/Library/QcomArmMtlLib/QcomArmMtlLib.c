/** @file

  Copyright (c) 2017-2021, Arm Limited. All rights reserved.
  Copyright (c) 2023, Qualcomm Technologies, Inc. All Rights Reserved.

  SPDX-License-Identifier: BSD-2-Clause-Patent

  System Control and Management Interface V1.0
    http://infocenter.arm.com/help/topic/com.arm.doc.den0056a/
    DEN0056A_System_Control_and_Management_Interface.pdf
**/

#include <string.h>
#include <Library/QcomArmMtlLib.h>
#include <Library/DebugLib.h>
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>

extern EFI_GUID gEfiMBoxIPCProtocolGuid;

#define CHANNEL_NAME "scmi" 

/** Wait until channel is free till timeout.

  @param[in] Channel                Pointer to a channel.
  @param[in] TimeOutInMicroSeconds  Timeout in micro seconds.

  @retval EFI_SUCCESS               Channel is free.
  @retval EFI_TIMEOUT               Time out error.
  @retval EFI_UNSUPPORTED           Interface not implemented.
**/
EFI_STATUS
MtlWaitUntilChannelFree (
  IN MTL_CHANNEL  *Channel,
  IN UINTN        TimeOutInMicroSeconds
  )
{
	MTL_MAILBOX*	Mb;
	UINT32 Timeout=0;
	if (!Channel||Channel->MailBox==NULL)
		return EFI_UNSUPPORTED;

	Mb = Channel->MailBox;

	do {
		if (CHANNEL_IS_FREE(Mb->ChannelStatus))
			break;

		gBS->Stall(50);
		Timeout += 50;
	} while (Timeout<=TimeOutInMicroSeconds);

	if (Timeout>TimeOutInMicroSeconds)
		DEBUG((EFI_D_ERROR, "Got timeout when waiting for channel free.\n"));

	return (Timeout>TimeOutInMicroSeconds)?EFI_TIMEOUT:EFI_SUCCESS;
}

/** Returns the address of the message payload.

  @param[in] Channel   Pointer to a channel.

  @retval UINT32*      Pointer to the payload.
**/
UINT32*
MtlGetChannelPayload (
  IN  MTL_CHANNEL  *Channel
  )
{
  MTL_MAILBOX* Mb;

  if (!Channel||Channel->MailBox==NULL)
	return NULL;

  Mb = Channel->MailBox;

  return &Mb->Payload[0];
}

/** Returns pointer to a MTL channel & pointer to Mbox handle for the requested channel
  type.

  @param[in] ChannelType        ChannelType, Low or High priority channel.
                                MTL_CHANNEL_TYPE_LOW or
                                MTL_CHANNEL_TYPE_HIGH

  @param[in] DestPlatform       Enum for SCMI destination.

  @param[out] Channel           Holds pointer to the channel.

  @param[out] MBoxHandle        Holds pointer to Mbox handle.

  @retval EFI_SUCCESS           Channel acquisition is successful.
  @retval EFI_UNSUPPORTED       Requested channel type not supported or
                                interface not implemented.								
  @retval EFI_INVALID_PARAMETER Requested destination is invalid.
**/
EFI_STATUS
MtlGetChannel (
  IN  MTL_CHANNEL_TYPE     ChannelType,
  IN  SCMI_PLATFORM_TYPE   DestPlatform,
  OUT MTL_CHANNEL          **Channel,
  OUT mbox_ipc_handle_type *MBoxHandle
  )
{
	EFI_STATUS Status;

	if (ChannelType != MTL_CHANNEL_TYPE_LOW)
	{
		*Channel = NULL;
		return EFI_UNSUPPORTED;
	}

	Status = GetMTLChannel(DestPlatform, Channel);
	if (EFI_ERROR (Status))
	{
		DEBUG ((EFI_D_ERROR, "Error getting shared memory channel\n"));
		return Status;
	}

	/* Clear channel error if pending */
	if (IS_CHANNEL_ERROR((*Channel)->MailBox->ChannelStatus))
	{
		CLEAR_CHANNEL_ERROR((*Channel)->MailBox->ChannelStatus);
		DEBUG ((EFI_D_ERROR, "Earlier tx msg failed\r\n"));
	}

	if (uefiMboxHandle[DestPlatform] == NULL)
	{
		mbox_ipc_err_type ret;
		mbox_ipc_open_config_type open_cfg;
		MBOX_IPC_OPEN_CONFIG_INIT(open_cfg);

		open_cfg.remote_ss = RemotePlatform[DestPlatform];
		open_cfg.name = CHANNEL_NAME;
		open_cfg.options = 0;
		open_cfg.notify_rx = mbox_scmi_rx_notification_cb[DestPlatform];
		open_cfg.send_timeout = 0;
		open_cfg.priv = NULL;

		EFI_MBOX_IPC_PROTOCOL *MBoxIPCProtocol;

		Status = gBS->LocateProtocol (
				&gEfiMBoxIPCProtocolGuid,
				NULL,
				(VOID**)&MBoxIPCProtocol
		);
		if (EFI_ERROR (Status)) {
			//ASSERT (FALSE);
			DEBUG ((EFI_D_ERROR, "SCMI error: Unable to locate Mbox Protocol\n"));
			return Status;
		}

		Status = MBoxIPCProtocol->MailBoxIPCOpen(&open_cfg, MBoxHandle, &ret);
		if (EFI_ERROR (Status))
		{
			DEBUG ((EFI_D_ERROR, "mbox_ipc_open failed err = (0x%x)\r\n", ret));
			return Status;
		}
		else
		{
			uefiMboxHandle[DestPlatform] = *MBoxHandle;
		}
	}
	else
	{
		*MBoxHandle = uefiMboxHandle[DestPlatform];
	}

	return EFI_SUCCESS;
}

/** Mark the channel busy and send the message using Mbox.

  @param[in] Channel            Pointer to a channel.
  @param[in] MBoxHandle         Pointer to Mbox handle.
  @param[in] MessageHeader      Message header.

  @param[out] PayloadLength     Message length.

  @retval EFI_SUCCESS           Message sending is successful.
  @retval EFI_UNSUPPORTED       Requested channel type not supported or
                                interface not implemented.								
  @retval EFI_NOT_READY         Requested channel is busy.
**/
EFI_STATUS
MtlSendMessage (
  IN  MTL_CHANNEL          *Channel,
  IN  mbox_ipc_handle_type MBoxHandle,
  IN  UINT32               MessageHeader,
  OUT UINT32               PayloadLength
  )
{
	MTL_MAILBOX*  Mb;

	if ((Channel == NULL) || (Channel->MailBox == NULL) || (MBoxHandle == NULL))
		return EFI_UNSUPPORTED;

	Mb = Channel->MailBox;

	/* make sure channel is free */
	if (CHANNEL_IS_BUSY(Mb->ChannelStatus))
	{
		DEBUG((EFI_D_ERROR, "channel is not free\n"));
		return EFI_NOT_READY;
	}

	/* populate shared mem */
	Mb->Flags = USE_COMPLETION_POLLING;
	Mb->MessageHeader = MessageHeader;
	Mb->Length = sizeof(Mb->MessageHeader) + PayloadLength;

	/* mark channel as busy */
	MARK_CHANNEL_BUSY(Mb->ChannelStatus);

	/* Mbox Transport layer */

	mbox_ipc_err_type ret;

	uint32_t interrupt = 0x494D4353; // IMCS -> 0x494D4353

	EFI_MBOX_IPC_PROTOCOL *MBoxIPCProtocol;
	EFI_STATUS             Status;
	Status = gBS->LocateProtocol (
			&gEfiMBoxIPCProtocolGuid,
			NULL,
			(VOID**)&MBoxIPCProtocol
	);
	if (EFI_ERROR (Status)) {
		//ASSERT (FALSE);
		DEBUG ((EFI_D_ERROR, "SCMI error: Unable to locate Mbox Protocol\n"));
		return Status;
	}

	Status = MBoxIPCProtocol->MailBoxIPCSend(MBoxHandle, NULL, interrupt, sizeof(interrupt), 0, &ret);
	if (EFI_ERROR (Status))
	{
		DEBUG ((EFI_D_ERROR, "mbox_ipc_send failed err = (0x%x)\r\n", ret));
		return Status;
	}

	return EFI_SUCCESS;
}

/** Wait for a response on a channel.

  If channel is free after sending message, it implies SCP responded
  with a response on the channel.

  @param[in] Channel               Pointer to a channel.

  @param[out] MessageHeader        Message header.

  @param[out] PayloadLength        Message length.

  @retval EFI_SUCCESS              Message received successfully.
  @retval EFI_UNSUPPORTED          Interface not implemented.
  @retval EFI_TIMEOUT              Time out error.
**/
EFI_STATUS
MtlReceiveMessage (
  IN  MTL_CHANNEL  *Channel,
  OUT UINT32       *MessageHeader,
  OUT UINT32       *PayloadLength
  )
{
	MTL_MAILBOX* 	Mb;
	EFI_STATUS	Status;

	if (!Channel||Channel->MailBox==NULL)
		return EFI_UNSUPPORTED;

	Mb = Channel->MailBox;

	/* make sure channel free */
	Status = MtlWaitUntilChannelFree(Channel, RESPONSE_TIMEOUT);
	if (EFI_ERROR(Status))
		return Status;

	*MessageHeader = Mb->MessageHeader;
	*PayloadLength = Mb->Length - 4;
	return EFI_SUCCESS;
}
