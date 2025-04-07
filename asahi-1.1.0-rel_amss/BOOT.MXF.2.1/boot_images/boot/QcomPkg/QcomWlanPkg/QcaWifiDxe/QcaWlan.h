/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 18/11/21  zxue     refine code
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QCA_WLAN_H__
#define __QCA_WLAN_H__

#include <Protocol/WiFi2.h>
#include <Protocol/DevicePath.h>
#include "Dev.h"

// Additional types

#define ETHER_ADDR_LEN 6

#define EFI_RECEIVE_FILTERS_NO_MCAST ((UINT32)(    \
            EFI_SIMPLE_NETWORK_RECEIVE_UNICAST |   \
            EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST | \
            EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS))

// User defined EFI_SUPPLICANT_DATA_TYPE to set MFP
#define EfiSupplicant80211UserMfp          (EfiSupplicantDataTypeMaximum + 1)
#define EfiSupplicant80211RsnxeCapability  (EfiSupplicantDataTypeMaximum + 2)

enum EfiSupplicantMfpOptions {
    EfiSupplicantMfpNone = 0,
    EfiSupplicantMfpOptional = 1,
    EfiSupplicantMfpRequired = 2,
};

/* Protocols API */
EFI_STATUS
QcWlanInstallConnectionProtocols(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
);

VOID
QcWlanUninstallConnectionProtocols(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
);

EFI_DEVICE_PATH_PROTOCOL *
QcWlanBuildDevicePath(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN EFI_HANDLE DeviceHandle,
    IN EFI_DRIVER_BINDING_PROTOCOL *BindingProtocol
);

/* WLAN */
EFI_STATUS
QcWlanInitializeNic(IN EFI_QCWLAN_DEVICE_CONTEXT *Dev);

EFI_STATUS
QcWlanUninitializeNic(IN EFI_QCWLAN_DEVICE_CONTEXT *Dev);

VOID
QcWlanApplyNicConfiguration(IN EFI_QCWLAN_DEVICE_CONTEXT *Dev);

EFI_STATUS
QcWlanSetCountryCode(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev, 
    IN CONST UINT8 *CCode
);

VOID
QcWlanGetMacAddress(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev, 
    OUT UINT8 *Address
);

EFI_STATUS
QcWlanConnect(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN EFI_80211_CONNECT_NETWORK_TOKEN *Token
);

EFI_STATUS
QcWlanDisconnect(
	IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
	IN EFI_80211_DISCONNECT_NETWORK_TOKEN *Token);

VOID
QcWlanCompleteConnection(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN EFI_STATUS Status
);

VOID
QcWlanSetSupplicantState(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN EFI_80211_LINK_STATE State
);

EFI_STATUS
QcWlanHandleSupplicantState(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
);

EFI_STATUS
QcWlanSetupEapolSm(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN UINT16 PendingEapolConnect
);

EFI_STATUS
QcWlanCleanupEapolSm(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
);

VOID
QcWlanSetEapolTimer(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
);

EFI_STATUS
QcWlanSetPtkKey(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
);

EFI_STATUS
QcWlanSetGtkKey(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
);

#endif // __QCA_WLAN_H__

