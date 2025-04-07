/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 11/8/21   zxue     add support to read file from specific path
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <Protocol/ServiceBinding.h>
#include <Protocol/WiFi2.h>
#include <Protocol/Supplicant.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Protocol/Shell.h>
#include <Protocol/ShellParameters.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/EapConfiguration.h>
#include <Protocol/SimpleFileSystem.h>
#include <Protocol/LoadedImage.h>

#define DbgConsolePrint(fmt, ...) Print(fmt L"\n", ## __VA_ARGS__)
#define DbgError(fmt, ...) Print(L"{\"error\": \"" fmt L"\"}\n", ## __VA_ARGS__)

#define WIFI_RSN_CIPHER_SUITE_CCMP 0x000fac04
#define WIFI_RSN_CIPHER_SUITE_TKIP 0x000fac02
#define WIFI_CIPHER_SUITE_TYPE_CCMP   4
#define WIFI_CIPHER_SUITE_TYPE_TKIP   2

#define WIFI_RSN_AKM_SELECTOR_PSK   0x000fac02
#define WIFI_RSN_AKM_SELECTOR_8021X 0x000fac01

#define WIFI_AKM_SUITE_TYPE_8021X 1
#define WIFI_AKM_SUITE_TYPE_PSK   2
#define WIFI_AKM_SUITE_TYPE_SAE   8

#ifndef ETH_ALEN
#define ETH_ALEN 6
#endif

typedef enum _QCA_WIFI_MGR_ACTION_ID {
    ACTION_LINK_STATE,
	ACTION_LINK_ADDRESS,
    ACTION_SCAN,
    ACTION_CONNECT,
    ACTION_CONNECT_ONEX,
    ACTION_DISCONNECT,
    ACTION_RSSI,
    ACTION_LOG_LEVEL,
    ACTION_INVALID,
} QCA_WIFI_MGR_ACTION_ID;


typedef struct _QCA_WIFI_MGR_ACTION
{
    UINT8   ActionId;
    CHAR16* ActionStr;

}QCA_WIFI_MGR_ACTION;

typedef struct _WIFI_MGR_SCAN_DATA {
    EFI_80211_GET_NETWORKS_TOKEN  Token;
    EFI_80211_GET_NETWORKS_DATA   Data;
    // extra EFI_80211_SSID structs, as dictated by Data.NumOfSSID
} WIFI_MGR_SCAN_DATA;

typedef struct _WIFI_MGR_CONNECT_DATA {
    EFI_80211_CONNECT_NETWORK_TOKEN Token;
    EFI_80211_CONNECT_NETWORK_DATA Data;
    EFI_80211_NETWORK Network;

    // only support a single AKM suite - SHA1
    EFI_80211_AKM_SUITE_SELECTOR AKMSuite;

    // only support a single cipher suite for now - CCMP, pairwise and group
    EFI_80211_CIPHER_SUITE_SELECTOR CipherSuite;
} WIFI_MGR_CONNECT_DATA;