/** @file
  Copyright (c) 2023, Qualcomm Technologies, Inc. All Rights Reserved.
**/

#ifndef QCOM_ARM_SCMI_VENDOR_PROTOCOL_H_
#define QCOM_ARM_SCMI_VENDOR_PROTOCOL_H_

#include <Protocol/QcomArmScmi.h>
#include <Library/QcomArmMtlLib.h>

#define ARM_SCMI_QCOM_VENDOR_PROTOCOL_GUID { \
  0xd1dca45c, 0xf10b, 0x4802, {0xb5, 0x1, 0x53, 0x34, 0x60, 0x16, 0x7b, 0x20} \
  }

typedef enum {
  MsgIdSetParam = 0x10,
  MsgIdGetParam = 0x11,
  MsgIdStartActivity = 0x12,
  MsgIdStopActivity = 0x13,
} QCOM_SCMI_MSG_ID_TYPE;

typedef
INT32
(*QCOM_VENDOR_CALLBACK_TYPE) (
  UINT8 MsgId,
  UINT8 ParamId,
  CHAR8 *Payload,
  UINT32 PayloadLen,
  CHAR8 *OutPayload
);

extern EFI_GUID gArmScmiQcomVendorProtocolGuid;

typedef struct _SCMI_QCOM_VENDOR_PROTOCOL SCMI_QCOM_VENDOR_PROTOCOL;

/** Return version of the Qcom Vendor protocol supported by SCP firmware.

  @param[in]  This          A Pointer to SCMI_QCOM_VENDOR_PROTOCOL Instance.
  
  @param[in]  DestPlatform  Enum for SCMI destination.

  @param[out] Version       Version of the supported SCMI Qcom Vendor protocol.

  @retval EFI_SUCCESS       The version is returned.
  @retval EFI_DEVICE_ERROR  SCP returns an SCMI error.
  @retval !(EFI_SUCCESS)    Other errors.
**/
typedef
EFI_STATUS
(EFIAPI *SCMI_QCOM_VENDOR_GET_VERSION) (
  IN  SCMI_QCOM_VENDOR_PROTOCOL  *This,
  IN  SCMI_PLATFORM_TYPE         DestPlatform,
  OUT UINT32                     *Version
  );

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
typedef
EFI_STATUS
(EFIAPI *SCMI_QCOM_VENDOR_SEND) (
  IN  SCMI_QCOM_VENDOR_PROTOCOL *This,
  IN  SCMI_PLATFORM_TYPE        DestPlatform,
  IN  QCOM_SCMI_MSG_ID_TYPE     MessageId,
  IN  CHAR8                     *AlgoStr,
  IN  UINT32                    ParamId,
  IN  UINT32                    *MessageParams,
  IN  UINT32                    MessageParamCount,
  OUT UINT32                    **ReturnValues
);

/** Register a vendor protocol handler.

  @param[in]  AlgoStr      Pointer to requested Algorithm string.
  
  @param[in]  Callback     Function pointer to be registered for the callback.
  
  @param[in]  ChannelBase  Shared memory address to be used for communication.

  @retval EFI_SUCCESS      The callback is registered successfully.
  @retval !(EFI_SUCCESS)   Other errors.
**/
typedef
EFI_STATUS
(EFIAPI *SCMI_QCOM_VENDOR_REGISTER_CALLBACK) (
  IN CHAR8                      *AlgoStr,
  IN QCOM_VENDOR_CALLBACK_TYPE  Callback,
  IN UINT32                     ChannelBase
);

typedef struct _SCMI_QCOM_VENDOR_PROTOCOL {
  SCMI_QCOM_VENDOR_GET_VERSION GetVersion;
  SCMI_QCOM_VENDOR_SEND VendorSend;
  SCMI_QCOM_VENDOR_REGISTER_CALLBACK VendorRegisterCallback;
} SCMI_QCOM_VENDOR_PROTOCOL;

#endif /* QCOM_ARM_SCMI_VENDOR_PROTOCOL_H_ */

