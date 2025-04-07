/** @file

  Copyright (c) 2017-2021, Arm Limited. All rights reserved.
  Copyright (c) 2023, Qualcomm Technologies, Inc. All Rights Reserved.

  SPDX-License-Identifier: BSD-2-Clause-Patent

  System Control and Management Interface V1.0
    http://infocenter.arm.com/help/topic/com.arm.doc.den0056a/
    DEN0056A_System_Control_and_Management_Interface.pdf
**/

#include <Library/QcomArmMtlLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include "QcomScmiPrivate.h"

/** Return a pointer to the message payload.

  @param[in]  DestPlatform    Enum for SCMI destination.

  @param[out] Payload         Holds pointer to the message payload.

  @retval EFI_SUCCESS         Payload holds a valid message payload pointer.
  @retval EFI_TIMEOUT         Time out error if MTL channel is busy.
  @retval EFI_UNSUPPORTED     If MTL channel is unsupported.
**/
EFI_STATUS
ScmiCommandGetPayload (
  IN  SCMI_PLATFORM_TYPE  DestPlatform,
  OUT UINT32**            Payload
  )
{
  EFI_STATUS   Status;
  MTL_CHANNEL  *Channel;

  mbox_ipc_handle_type MBoxHandle;
  // Get handle to the Channel.
  Status = MtlGetChannel (MTL_CHANNEL_TYPE_LOW, DestPlatform, &Channel, &MBoxHandle);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  // Payload will not be populated until channel is free.
  Status = MtlWaitUntilChannelFree (Channel, RESPONSE_TIMEOUT);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  // Get the address of the payload.
  *Payload = MtlGetChannelPayload (Channel);

  return EFI_SUCCESS;
}

/** Execute a SCMI command and receive a response.

  This function uses a MTL channel to store SCMI message and uses Mailbox to
  transfer message to SCP and waits for a response.

  @param[in]     Command        Pointer to the SCMI command (Protocol ID
                                and Message ID).

  @param[in]     DestPlatform   Enum for SCMI destination.

  @param[in,out] PayloadLength  SCMI command message length.

  @param[out] OPTIONAL  ReturnValues   Pointer to SCMI response.

  @retval OUT EFI_SUCCESS       Command sent and message received successfully.
  @retval OUT EFI_UNSUPPORTED   Channel not supported.
  @retval OUT EFI_TIMEOUT       Timeout on the channel.
  @retval OUT EFI_DEVICE_ERROR  Channel not ready.
  @retval OUT EFI_DEVICE_ERROR  Message Header corrupted.
  @retval OUT EFI_DEVICE_ERROR  SCMI error.
**/
EFI_STATUS
ScmiCommandExecute (
  IN     SCMI_COMMAND       *Command,
  IN     SCMI_PLATFORM_TYPE DestPlatform,
  IN OUT UINT32             *PayloadLength,
  OUT    UINT32             **ReturnValues OPTIONAL
  )
{
  EFI_STATUS             Status;
  SCMI_MESSAGE_RESPONSE  *Response;
  UINT32                 MessageHeader;
  UINT32                 ResponseHeader;
  MTL_CHANNEL            *Channel;

  //ASSERT (PayloadLength != NULL);
  if (PayloadLength == NULL)
  {
	DEBUG ((EFI_D_ERROR, "SCMI error: Payload Length is Null\n"));
	return EFI_INVALID_PARAMETER;
  }

  mbox_ipc_handle_type MBoxHandle;

  Status = MtlGetChannel (MTL_CHANNEL_TYPE_LOW, DestPlatform, &Channel, &MBoxHandle);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  // Fill in message header.
  MessageHeader = SCMI_MESSAGE_HEADER (
                    Command->MessageId,
                    ScmiMessageTypeCommand,
                    Command->ProtocolId
                    );

  // Send payload using MTL channel.
  Status = MtlSendMessage (
             Channel,
			 MBoxHandle,
             MessageHeader,
             *PayloadLength
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  // Wait for the response on the channel.
  Status = MtlReceiveMessage (Channel, &ResponseHeader, PayloadLength);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  // SCMI must return MessageHeader unmodified.
  if (MessageHeader != ResponseHeader) {
    //ASSERT (FALSE);
    DEBUG ((EFI_D_ERROR, "SCMI error: Header mismatch\n"));
    return EFI_DEVICE_ERROR;
  }

  Response = (SCMI_MESSAGE_RESPONSE*)MtlGetChannelPayload (Channel);

  if (Response != NULL)
  {
	// Check if response status is success
	if (Response->Status != ScmiSuccess) {
	  DEBUG ((EFI_D_ERROR, "SCMI error: ProtocolId = 0x%x, MessageId = 0x%x, error = %d\n",
			Command->ProtocolId,
			Command->MessageId,
			Response->Status
		    ));

	  //ASSERT (FALSE);
	  return EFI_DEVICE_ERROR;
	}
  }
  else
  {
	DEBUG ((EFI_D_ERROR, "SCMI error: Response is Null\n"));
	return EFI_INVALID_PARAMETER;
  }

  if (ReturnValues != NULL) {
    *ReturnValues = Response->ReturnValues;
  }

  return EFI_SUCCESS;
}

/** Internal common function useful for common protocol discovery messages.

  @param[in] ProtocolId    Protocol Id of the the protocol.
  @param[in] MesaageId     Message Id of the message.
  @param[in] DestPlatform  Enum for SCMI destination.

  @param[out] ReturnValues SCMI response return values.

  @retval EFI_SUCCESS      Success with valid return values.
  @retval EFI_DEVICE_ERROR SCMI error.
  @retval !(EFI_SUCCESS)   Other errors.
**/
STATIC
EFI_STATUS
ScmiProtocolDiscoveryCommon (
  IN  SCMI_PROTOCOL_ID   ProtocolId,
  IN  SCMI_MESSAGE_ID    MessageId,
  IN  SCMI_PLATFORM_TYPE DestPlatform,
  OUT UINT32             **ReturnValues
  )
{
  SCMI_COMMAND  Command;
  UINT32        PayloadLength = 0;

  Command.ProtocolId = ProtocolId;
  Command.MessageId  = MessageId;

  return ScmiCommandExecute (
           &Command,
		   DestPlatform,
           &PayloadLength,
           ReturnValues
           );
}

/** Return protocol version from SCP for a given protocol ID.

  @param[in]  Protocol ID    Protocol ID.
  @param[in]  DestPlatform   Enum for SCMI destination.
  @param[out] Version        Pointer to version of the protocol.

  @retval EFI_SUCCESS        Version holds a valid version received
                             from the SCP.
  @retval EFI_DEVICE_ERROR   SCMI error.
  @retval !(EFI_SUCCESS)     Other errors.
**/
EFI_STATUS
ScmiGetProtocolVersion (
  IN  SCMI_PROTOCOL_ID   ProtocolId,
  IN  SCMI_PLATFORM_TYPE DestPlatform,
  OUT UINT32             *Version
  )
{
  EFI_STATUS             Status;
  UINT32                 *ProtocolVersion;

  Status = ScmiProtocolDiscoveryCommon (
             ProtocolId,
             ScmiMessageIdProtocolVersion,
			 DestPlatform,
             (UINT32**)&ProtocolVersion
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  *Version = *ProtocolVersion;

  return EFI_SUCCESS;
}

/** Return protocol attributes from SCP for a given protocol ID.

  @param[in]  Protocol ID   Protocol ID.
  @param[in]  DestPlatform  Enum for SCMI destination.
  @param[out] ReturnValues  Pointer to attributes of the protocol.

  @retval EFI_SUCCESS       ReturnValues points to protocol attributes.
  @retval EFI_DEVICE_ERROR  SCMI error.
  @retval !(EFI_SUCCESS)    Other errors.
**/
EFI_STATUS
ScmiGetProtocolAttributes (
  IN  SCMI_PROTOCOL_ID   ProtocolId,
  IN  SCMI_PLATFORM_TYPE DestPlatform,
  OUT UINT32             **ReturnValues
  )
{
  return ScmiProtocolDiscoveryCommon (
           ProtocolId,
           ScmiMessageIdProtocolAttributes,
		   DestPlatform,
           ReturnValues
           );
}

/** Return protocol message attributes from SCP for a given protocol ID.

  @param[in]  Protocol ID    Protocol ID.
  @param[in]  DestPlatform   Enum for SCMI destination.
  @param[out] ReturnValues   Pointer to message attributes of the protocol.

  @retval EFI_SUCCESS       ReturnValues points to protocol message attributes.
  @retval EFI_DEVICE_ERROR  SCMI error.
  @retval !(EFI_SUCCESS)    Other errors.
**/
EFI_STATUS
ScmiGetProtocolMessageAttributes (
  IN  SCMI_PROTOCOL_ID   ProtocolId,
  IN  SCMI_PLATFORM_TYPE DestPlatform,
  OUT UINT32             **ReturnValues
  )
{
  return ScmiProtocolDiscoveryCommon (
           ProtocolId,
           ScmiMessageIdProtocolMessageAttributes,
		   DestPlatform,
           ReturnValues
           );
}
