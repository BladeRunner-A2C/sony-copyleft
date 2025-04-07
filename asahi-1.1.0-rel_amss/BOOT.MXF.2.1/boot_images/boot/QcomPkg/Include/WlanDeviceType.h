/** @file WlanDeviceType.h
  Copyright (c) 2023, Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential
**/

/*=============================================================================
                              EDIT HISTORY


when         who   what, where, why
----------   ---   --------------------------------------------------------------
2023-03-23   zxue  Initial version, add an API to get the chip type on Hamoa.

=============================================================================*/
#ifndef WLANDEVICETYPE_H
#define WLANDEVICETYPE_H

enum WLAN_DEVICE_TYPE{
	WLAN_DEVICE_TYPE_NONE = 0,
	WLAN_DEVICE_TYPE_HSP  = 1,
	WLAN_DEVICE_TYPE_HMT  = 2
};

/**
 * DeviceType:
 * ChipIdStr:   String representing the chip name.
 * ChipId:       Incremental, internal chip ID
 * VendorId:   String representing the chip name.
 * DeviceId:    Incremental, internal chip ID
 */
typedef struct
{
  CONST CHAR8          			*ChipIdStr;
  enum WLAN_DEVICE_TYPE     	ChipId;
  UINT16						VendorId;
  UINT16						DeviceId;
} WlanDeviceInfo;

typedef WlanDeviceInfo *WlanDeviceInfoHandle;

EFI_STATUS WlanGetDeviceType(enum WLAN_DEVICE_TYPE *Type);
EFI_STATUS WlanGetDeviceInfo(WlanDeviceInfoHandle *DeviceInfoHandle);

#endif

