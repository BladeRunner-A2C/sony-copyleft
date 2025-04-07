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
	return EFI_UNSUPPORTED;
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
  return NULL;
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
	return EFI_UNSUPPORTED;
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
	return EFI_UNSUPPORTED;
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
	return EFI_UNSUPPORTED;
}
