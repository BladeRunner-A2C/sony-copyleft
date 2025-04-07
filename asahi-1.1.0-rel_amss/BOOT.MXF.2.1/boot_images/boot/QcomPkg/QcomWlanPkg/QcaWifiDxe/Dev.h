/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 8/3/22    zxue     fix the MISRA issue
 18/11/21  zxue     refine code
 26/8/21   zxue     support logfs
 16/8/21   zxue     create a new event and enable wifi at the event callback
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __DEV_H
#define __DEV_H

#include <Uefi.h>

//
// Libraries
//
#include <Library/MemoryAllocationLib.h>
#include <Library/DevicePathLib.h>
#include <Library/NetLib.h>

//
// UEFI Driver Model Protocols
//
#include <Protocol/DriverBinding.h>
#include <Protocol/ServiceBinding.h>
#include <Protocol/Supplicant.h>
#include <IndustryStandard/Pci.h>

//
// Consumed Protocols
//
#include <Protocol/PciIo.h>
#include <Protocol/SimpleNetwork.h>
#include <Protocol/AdapterInformation.h>
#include <Protocol/LoadedImage.h>

//
// Produced Protocols
//
#include <Protocol/WiFi2.h>
#include <QcaWifi.h>

// Additional structures
#include <qdf/sk_buff.h>

#define QCA_PCI_ANY_ID 0

typedef enum {
    QCA_DMA_BIDIRECTIONAL = 0,
    QCA_DMA_TO_DEVICE = 1,
    QCA_DMA_FROM_DEVICE = 2,
    QCA_DMP_NONE = 3
} QCA_DMA_DIRECTION;

typedef enum {
    QCA_FIRMWARE_SUPPORT_MHI_DIAG = 0x00000001,
    QCA_FIRMWARE_SUPPORT_WMI_DIAG = 0x00000002,
} QCA_FIRMWARE_ATTRIBUTES;

typedef struct {
    UINT16 VendorId;
    UINT16 DeviceId;
    UINT16 SubsystemVendorId;
    UINT16 SubsystemId;
    UINT32 FirmwareAttributes;
} QCA_HARDWARE_ID;

typedef struct {
    EFI_PCI_IO_PROTOCOL   *PciIo;
    UINT64                OriginalPciAttributes;
    UINT64                EnabledPciAttributes;
    UINT8                 BarIndex;
    QCA_HARDWARE_ID       HardwareId;
    VOID                  *DriverData;
} QCA_PCI_DEVICE;

typedef struct _Net80211Context {
    void *NetDev;
    void *NetIf;
} NET80211_CONTEXT;

typedef enum {
    DEV_START_INIT = 0,
    DEV_START_FW_FAIL = 1,
    DEV_START_SUCC = 2,
} QCA_DEV_START_STATUS;

typedef struct _EFI_QCWLAN_DEVICE_CONTEXT {
    UINTN                                   Signature;
    QCA_DEV_START_STATUS                    Started;
	EFI_EVENT 						        ReadyToEnable;
    QCA_PCI_DEVICE                          PciDev;

    EFI_DRIVER_BINDING_PROTOCOL             *BindingProtocol;

    /* WLAN protocols */
    EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL WirelessMacConnectionProtocol;
    EFI_QCWLAN_TEST_PROTOCOL                QcWlanTestProtocol;

    EFI_80211_DISCONNECT_NETWORK_TOKEN      *DisconnectNetworkToken;
    EFI_80211_CONNECT_NETWORK_TOKEN         *ConnectNetworkToken;
    EFI_80211_GET_NETWORKS_TOKEN            *GetNetworksToken;
    EFI_QCWLAN_GET_RSSI_TOKEN               *GetRssiToken;
    UINT64                                  ScanTimestamp;

    /* Supplicant State Machine */
	EFI_HANDLE                              SupplicantServiceBindingProtocolHandle;
	EFI_SERVICE_BINDING_PROTOCOL            *SupplicantBindingProtocol;
	EFI_SUPPLICANT_PROTOCOL                 *SupplicantProtocol;
    EFI_HANDLE                              MacHandle;

    UINT8                                   Bssid[6];
    BOOLEAN                                 WantEapol;
    UINT32                                  PendingEapolConnect;
	UINT8                                   EapolConnectRetries;
    EFI_EVENT                               EapolTimeout;
    UINT8                                   EapolTimeoutRetries;

    /* SNP and Device Path */
    EFI_DEVICE_PATH_PROTOCOL                *DevicePathProtocol;
    EFI_SIMPLE_NETWORK_PROTOCOL             Snp;
    EFI_SIMPLE_NETWORK_MODE                 Snm;
    EFI_ADAPTER_INFORMATION_PROTOCOL        Aip;

	EFI_LOADED_IMAGE_PROTOCOL               *Image;
    NET80211_CONTEXT                        WiFi;
    struct sk_buff_pool                     tx_skb_pool;

    EFI_EVENT                               ExitBoot;
} EFI_QCWLAN_DEVICE_CONTEXT;


#define QCWLAN_DRIVER_SIGNATURE SIGNATURE_32('w', 'l', 'a', 'n')

#define QCWLAN_DEV_FROM_WIFI2(This) CR(This, EFI_QCWLAN_DEVICE_CONTEXT, WirelessMacConnectionProtocol, QCWLAN_DRIVER_SIGNATURE)
#define QCWLAN_DEV_FROM_AIP(This)   CR(This, EFI_QCWLAN_DEVICE_CONTEXT, Aip, QCWLAN_DRIVER_SIGNATURE)
#define QCWLAN_DEV_FROM_SNP(This)   CR(This, EFI_QCWLAN_DEVICE_CONTEXT, Snp, QCWLAN_DRIVER_SIGNATURE)
#define QCWLAN_DEV_FROM_TEST(This)  CR(This, EFI_QCWLAN_DEVICE_CONTEXT, QcWlanTestProtocol, QCWLAN_DRIVER_SIGNATURE)

extern EFI_QCWLAN_DEVICE_CONTEXT gWlanDriverContext;

STATIC inline EFI_LOADED_IMAGE_PROTOCOL *GetDriverLoadedImage(void) {
    return gWlanDriverContext.Image;
}

#endif // __DEV_H
