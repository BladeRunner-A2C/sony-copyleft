/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
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

#ifndef __QCA_SCAN_H
#define __QCA_SCAN_H

#include <net/net80211.h>
#include <QcaWifi.h>
#include "Dev.h"
#include "QcaWlan.h"

typedef struct {
    LIST_ENTRY Node;
    EFI_80211_NETWORK_DESCRIPTION NetworkDesc;
} EFI_80211_NETWORK_ENTRY;

typedef struct {
    LIST_ENTRY NetworkList;
    UINT32 NetworkCount;
    UINT32 NetworkDescTotalSize;
} EFI_80211_NETWORK_LIST_INFO;

typedef struct {
    LIST_ENTRY Node;
    EFI_QCWLAN_RSSI_DESCRIPTION RssiDesc;
} EFI_80211_BSS_RSSI_ENTRY;

typedef struct {
    UINT64 Timestamp;
    EFI_80211_SSID SSId;
    LIST_ENTRY BssRssiList;
    UINT32 BssRssiCount;
} EFI_80211_BSS_RSSI_LIST_INFO;

#define SUITE_SIZE sizeof(EFI_80211_SUITE_SELECTOR)

/* Helpers */
EFI_STATUS Net80211ErrorToEfiStatus(INT32 Error);

BOOLEAN QcWlanIsSupportedCipherSuite(
    IN CONST EFI_80211_SUITE_SELECTOR *CipherSuite);

BOOLEAN QcWlanIsSupportedAkmSuite(
    IN CONST EFI_80211_SUITE_SELECTOR *AkmSuite);

/* Scan */
EFI_STATUS QcWlanScan(EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    EFI_80211_SSID *SSIdList, UINT32 NumOfSSId,
    UINT32 *FrequencyList, UINT32 NumOfFreqency);

VOID QcWlanProcessScanComplete(EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    struct net80211_vif *vif, struct net80211_scan_result *scan_result);

EFI_STATUS
QcWlanBuildGetRssiResult(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
	IN EFI_QCWLAN_GET_RSSI_TOKEN *Token
);

#endif
