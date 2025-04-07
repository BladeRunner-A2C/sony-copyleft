/*
 * Copyright (c) 2020-2021, 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QCA_WIFI_H__
#define __QCA_WIFI_H__

#include <Uefi.h>

 // {9E4675D2-10CC-4DFB-91BF-2182F23AF3A9}
#define EFI_QCWLAN_TEST_PROTOCOL_GUID \
    { \
     0x9e4675d2, 0x10cc, 0x4dfb, { 0x91, 0xbf, 0x21, 0x82, 0xf2, 0x3a, 0xf3, 0xa9 } \
    }

typedef struct _EFI_QCWLAN_TEST_PROTOCOL EFI_QCWLAN_TEST_PROTOCOL;

#define EFI_MAX_SSID_LEN  32
#define EFI_MAX_BSSID_LEN 6
#define EFI_MAX_CHAIN     4

#ifndef SUPPORT_LOAD_BY_EVT
#define SUPPORT_LOAD_BY_EVT 0
#endif

#ifndef SUPPORT_GET_DEVICE_TYPE_BY_WLANLIB
#define SUPPORT_GET_DEVICE_TYPE_BY_WLANLIB 0
#endif

#ifndef SUPPORT_RESET_NOTIFICATION
#define SUPPORT_RESET_NOTIFICATION 0
#endif

/* Protocols API */

typedef struct {
    //
    // Length in bytes of the SSId. If zero, ignore SSId field.
    //
    UINT8                            SSIdLen;
    //
    // Specifies the service set identifier.
    //
    UINT8                            SSId[EFI_MAX_SSID_LEN];
} EFI_QCWLAN_SSID;

typedef struct {
    //
    // The SSID of target.
    //
    EFI_QCWLAN_SSID             SSId;
    //
    // The number of frequencies to scan. If zero, all the supported channels 
    // will be scanned.
    //
    UINT32                      NumOfFrequency;
    //
    // The frequency list to scan.
    //
    UINT32                      FrequencyList[0];
} EFI_QCWLAN_GET_RSSI_DATA;

typedef struct {
    // The BSSID of Access Point scanned.
    UINT8						Bssid[EFI_MAX_BSSID_LEN];
    // The SSID of the Access Point.
    EFI_QCWLAN_SSID             SSId;

    //
    // The combo RSSI (dbm) calculated from all chains.
    //
    INT8						ComboRssi;

    //
    // The number of chains.
    //
    UINT8                       NumOfChain;

    //
    // The RSSI (dbm) for different chains.
    //
    INT8						ChainRssi[EFI_MAX_CHAIN];
} EFI_QCWLAN_RSSI_DESCRIPTION;

typedef struct {
    //
    // The number of EFI_QCWLAN_RSSI_DESCRIPTION in RssiDesc. 
    // If zero, SSIDList should be ignored.
    //
    UINT32                       NumOfRssiDesc;
    //
    // The RssiDesc is a pointer to an array of EFI_QCWLAN_RSSI_DESCRIPTION instances.
    // The number of entries is specified by NumOfRssiDesc. 
    //
    EFI_QCWLAN_RSSI_DESCRIPTION  RssiDesc[0];
} EFI_QCWLAN_GET_RSSI_RESULT;

typedef struct {
    //
    // If the status code returned by GetRssi() is EFI_SUCCESS, then this
    // Event will be signaled after the Status field is updated. 
    // The type of Event must be EFI_NOTIFY_SIGNAL.
    //
    EFI_EVENT                        Event;

    //
    // The status code returned by GetRssi(). 
    //
    EFI_STATUS                       Status;

    //
    // Pointer to the input data of getting rssi.
    //
    EFI_QCWLAN_GET_RSSI_DATA         *Data;

    //
    // Indicates the rssi result. It is caller's responsibility to free this
    // buffer.
    //
    EFI_QCWLAN_GET_RSSI_RESULT       *Result;
} EFI_QCWLAN_GET_RSSI_TOKEN;


/**
  Request a RSSI of a specified network.

  @param[in]  This                Pointer to the EFI_QCWLAN_TEST_PROTOCOL
                                  instance.
  @param[in]  Token               Pointer to the token for getting RSSI.

  @retval EFI_SUCCESS             The operation started, and an event will
                                  eventually be raised for the caller.
  @retval EFI_INVALID_PARAMETER   One or more of the following conditions is
                                  TRUE:
                                  This is NULL.
                                  Token is NULL.
  @retval EFI_OUT_OF_RESOURCES    Required system resources could not be
                                  allocated.

**/
typedef EFI_STATUS
(EFIAPI *EFI_QCWLAN_GET_RSSI) (
    IN EFI_QCWLAN_TEST_PROTOCOL       *This,
    IN EFI_QCWLAN_GET_RSSI_TOKEN      *Token
    );

///
/// The EFI_QCWLAN_TEST_PROTOCOL provides interfaces for Qualcomm
/// WLAN driver. It is used by network applications (and drivers) to
/// get wireless information to test the device. 
///
struct _EFI_QCWLAN_TEST_PROTOCOL {
    EFI_QCWLAN_GET_RSSI GetRssi;
};

extern EFI_GUID gEfiQcWlanTestProtocolGuid;

#endif // __QCA_WIFI_H__

