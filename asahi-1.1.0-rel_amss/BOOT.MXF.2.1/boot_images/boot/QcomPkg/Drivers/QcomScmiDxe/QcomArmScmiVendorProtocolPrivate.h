/** @file
  Copyright (c) 2023, Qualcomm Technologies, Inc. All Rights Reserved.
**/

#ifndef QCOM_ARM_SCMI_VENDOR_PROTOCOL_PRIVATE_H_
#define QCOM_ARM_SCMI_VENDOR_PROTOCOL_PRIVATE_H_

/** Initialize Qcom Vendor protocol and install protocol on a given handle.

  @param[in] Handle              Handle to install Qcom Vendor protocol.

  @retval EFI_SUCCESS            Qcom Vendor protocol interface installed successfully.
**/
EFI_STATUS
ScmiQcomVendorProtocolInit (
  IN EFI_HANDLE *Handle
  );

#endif /* QCOM_ARM_SCMI_VENDOR_PROTOCOL_PRIVATE_H_ */
