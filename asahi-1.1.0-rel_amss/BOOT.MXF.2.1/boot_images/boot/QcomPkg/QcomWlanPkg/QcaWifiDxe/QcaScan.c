/*
 * Copyright (c) 2020-2021, 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */


/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 27/5/22   zxue     WAR for the WifiConnMgr for the assert issue
 18/11/21  zxue     refine code
 28/7/21   zxue     update the connection error code
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include "QcaScan.h"

// RSSI -> Network Quality Conversion
#define LOW_RSSI_THRESHOLD1       	-2
#define LOW_RSSI_THRESHOLD2        	7
#define HIGH_RSSI_THRESHOLD       	45
#define LOW_RSSI_LINK_QUALITY      	0
#define HIGH_RSSI_LINK_QUALITY   	100
#define LOW_RSSI_THRESHOLD_ADJUST   12
#define HIGH_RSSI_THRESHOLD_ADJUST  40
#define ATH_DEFAULT_NOISE_FLOOR     (-96)

// Helper functions
EFI_STATUS
Net80211ErrorToEfiStatus(INT32 Error)
{
    if (0 == Error)
        return EFI_SUCCESS;
    if (-EBUSY == Error)
        return EFI_NOT_READY;
    if (-EINVAL == Error)
        return EFI_INVALID_PARAMETER;
    if (-EALREADY == Error)
        return EFI_ALREADY_STARTED;
    if (-EINPROGRESS == Error)
        return EFI_NOT_READY;
    if (-ENOMEM == Error)
        return EFI_OUT_OF_RESOURCES;
    if (-ENOTSUPP == Error)
        return EFI_UNSUPPORTED;
	if (-ECONNABORTED == Error)
        return EFI_ABORTED;
	
    return EFI_DEVICE_ERROR;
}

STATIC inline UINT16
SizeofAkmSuiteSelector(IN UINT16 Count)
{
    return OFFSET_OF(EFI_80211_AKM_SUITE_SELECTOR, AKMSuiteList) +
        (sizeof(EFI_80211_SUITE_SELECTOR) * (MAX(1, Count)));
}

STATIC inline UINT16
SizeOfCipherSuiteSelector(IN UINT16 Count)
{
    return OFFSET_OF(EFI_80211_CIPHER_SUITE_SELECTOR, CipherSuiteList) +
        (sizeof(EFI_80211_SUITE_SELECTOR) * (MAX(1, Count)));
}

STATIC
CONST EFI_80211_SUITE_SELECTOR *
WpaGetStandardCipherSuite(
    IN CONST VOID *WpaCipherSuite,
    IN BOOLEAN IsGroup
)
{
    typedef struct {
        EFI_80211_SUITE_SELECTOR WpaCipherSuite;
        EFI_80211_SUITE_SELECTOR StandardCipherSuite;
    } EFI_80211_SUITE_SELECTOR_PAIR;

    STATIC CONST EFI_80211_SUITE_SELECTOR_PAIR CcmpCipherSuitePair = {
        .WpaCipherSuite = {.Oui = { 0x00, 0x50, 0xF2 },.SuiteType = 4 },
        .StandardCipherSuite = {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 4 },
    };

    STATIC CONST EFI_80211_SUITE_SELECTOR_PAIR TikpCipherSuitePair = {
        .WpaCipherSuite = {.Oui = { 0x00, 0x50, 0xF2 },.SuiteType = 2 },
        .StandardCipherSuite = {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 2 },
    };

    if (CompareMem(WpaCipherSuite, &CcmpCipherSuitePair.WpaCipherSuite, SUITE_SIZE) == 0)
        return &CcmpCipherSuitePair.StandardCipherSuite;

    if (IsGroup &&
        CompareMem(WpaCipherSuite, &TikpCipherSuitePair.WpaCipherSuite, SUITE_SIZE) == 0)
        return &TikpCipherSuitePair.StandardCipherSuite;

    return NULL;
}

STATIC
CONST EFI_80211_SUITE_SELECTOR *
WpaGetStandardAkmSuite(IN CONST VOID *WpaAkmSuite)
{
    STATIC CONST struct {
        EFI_80211_SUITE_SELECTOR WpaAkmSuite;
        EFI_80211_SUITE_SELECTOR StandardAkmSuite;
    } WpaStandardAkmSuiteMap[] = {
        {
            .WpaAkmSuite = {.Oui = { 0x00, 0x50, 0xF2 },.SuiteType = 1 },       // 8021X
            .StandardAkmSuite = {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 1 },
        },
        {
            .WpaAkmSuite = {.Oui = { 0x00, 0x50, 0xF2 },.SuiteType = 2 },       // PSK
            .StandardAkmSuite = {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 2 },
        },
    };

    UINT32 i;

    for (i = 0; i < ARRAY_SIZE(WpaStandardAkmSuiteMap); i++) {
        if (CompareMem(WpaAkmSuite, &WpaStandardAkmSuiteMap[i].WpaAkmSuite, SUITE_SIZE) == 0)
            return &WpaStandardAkmSuiteMap[i].StandardAkmSuite;
    }

    return NULL;
}

// Supported Chiper suites and akm suites
STATIC
BOOLEAN
IsSupportedCipherSuite(
    IN CONST VOID *CipherSuite,
    IN BOOLEAN IsGroup
)
{
    // Supported standard Cipher suites
    STATIC CONST EFI_80211_SUITE_SELECTOR SUPPORTED_CIPHER_SUITES[] = {
        {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 4 },   // CCMP
        {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 9 },   // GCMP256
        {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 10 },  // CCMP256
        {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 11 },  // BIP_GMAC_256
        {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 12 },  // BIP_GMAC_256
        {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 13 },  // BIP_CMAC_256
    };
    // Supported group cipher suite
    STATIC CONST EFI_80211_SUITE_SELECTOR SUPPORTED_GROUP_CIPHER_SUITES[] = {
        {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 2 },   // TKIP
    };

    UINT32 i;

    for (i = 0; i < ARRAY_SIZE(SUPPORTED_CIPHER_SUITES); i++) {
        if (CompareMem(CipherSuite, &SUPPORTED_CIPHER_SUITES[i], SUITE_SIZE) == 0)
            return TRUE;
    }

    if (IsGroup) {
        for (i = 0; i < ARRAY_SIZE(SUPPORTED_GROUP_CIPHER_SUITES); i++) {
            if (CompareMem(CipherSuite, &SUPPORTED_GROUP_CIPHER_SUITES[i], SUITE_SIZE) == 0)
                return TRUE;
        }
    }

    DbgInfo("Unsupported %a cipher suite: 0x%x\n", 
        IsGroup ? "group" : "pairwise", GetBe32(CipherSuite));

    return FALSE;
}

BOOLEAN
QcWlanIsSupportedCipherSuite(
    IN CONST EFI_80211_SUITE_SELECTOR *CipherSuite)
{
    return IsSupportedCipherSuite(CipherSuite, FALSE);
}

BOOLEAN
QcWlanIsSupportedAkmSuite(
    IN CONST EFI_80211_SUITE_SELECTOR *AkmSuite)
{
    // Supported akm suites
    STATIC CONST EFI_80211_SUITE_SELECTOR SUPPORTED_AKM_SUITES[] = {
        {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 1},    // 8021X
        {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 2 },   // PSK
        {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 5 },   // 8021X_SHA256
        {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 6 },   // PSK_SHA256
        {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 8 },   // SAE
        {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 11 },  // SUITE_B
        {.Oui = { 0x00, 0x0F, 0xAC },.SuiteType = 12 },  // SUITE_B_256
    };

    UINT32 i;

    for (i = 0; i < ARRAY_SIZE(SUPPORTED_AKM_SUITES); i++) {
        if (CompareMem(AkmSuite, &SUPPORTED_AKM_SUITES[i], SUITE_SIZE) == 0)
            return TRUE;
    }

    return FALSE;
}

STATIC
EFI_STATUS
Ieee80211ParseSsidIe(
    IN CONST UINT8 *SsidIe,
    OUT EFI_80211_SSID *Ssid)
{
    UINT8 Length = SsidIe[1];
    CONST UINT8 *Data = SsidIe + 2;
    UINT8 i;

    // Invalid SSID
    if (Length > EFI_MAX_SSID_LEN)
        return EFI_INVALID_PARAMETER;

    // Hidden SSID is not supported
    if (Length == 0)
        return EFI_UNSUPPORTED;

    Ssid->SSIdLen = Length;
    CopyMem(Ssid->SSId, Data, Length);

    // SSID with ALL NULL is not supported
    for (i = 0; i < Length; i++) {
        if (Data[i] != 0)
            return TRUE;
    }
    return EFI_UNSUPPORTED;
}

STATIC
EFI_STATUS 
Ieee80211ParseRsnIe(
    IN CONST UINT8 *Ie, 
    OUT UINT16 *CipherSuiteCount,
    OUT EFI_80211_SUITE_SELECTOR *CipherSuites,
    OUT UINT16 *AKMSuiteCount,
    OUT EFI_80211_SUITE_SELECTOR *AKMSuites)
{
    UINT16 Length;
    UINT16 i, Count;
    UINT16 Version;
    UINT16 SupportedCipherSuiteCount = 0;

    ASSERT(Ie != NULL);
    ASSERT(CipherSuiteCount != NULL);
    ASSERT(AKMSuiteCount != NULL);

    Length = Ie[1];
    if (Length < 2) {
        DbgInfo("RSN IE is too short, len %u\n", Length);
        return EFI_INVALID_PARAMETER;
    }
    Ie += 2;

    // Version
    Version = LE16(Ie);
    if (Version != 1) {
        DbgInfo("RSN bad version %u\n", Version);
        return EFI_INVALID_PARAMETER;
    }
    Ie += 2; Length -= 2;

    // Multicast/group cipher
    if (Length >= 4) {
        // make sure group cipher is supported
        if (!IsSupportedCipherSuite(Ie, TRUE)) {
            return EFI_UNSUPPORTED;
        }
        Ie += 4; Length -= 4;
    }
    else {
        return EFI_BAD_BUFFER_SIZE;
    }

    // Unicast ciphers
    if (Length >= 2) {
        Count = LE16(Ie);
        Ie += 2; Length -= 2;
        if (Length < Count * 4) {
            DbgInfo("RSN ucast cipher data too short; Length %u, Count %u\n",
                Length, Count);
            return EFI_INVALID_PARAMETER;
        }
        *CipherSuiteCount = Count;
        for (i = 0; i < Count; i++) {
            if (IsSupportedCipherSuite(Ie, FALSE))
                SupportedCipherSuiteCount++;
            if (CipherSuites)
                CopyMem(&CipherSuites[i], Ie, 4);
            Ie += 4, Length -= 4;
        }

        if (SupportedCipherSuiteCount == 0) {
            DbgInfo("Supported RSN ucast cipher set empty\n");
            return EFI_UNSUPPORTED;
        }
    }
    else {
        return EFI_BAD_BUFFER_SIZE;
    }

    // Key management algorithms
    if (Length >= 2) {
        Count = LE16(Ie);
        Ie += 2; Length -= 2;
        if (Length < Count * 4) {
            DbgInfo("RSN key mgmt alg data too short; Length %u, Count %u\n",
                Length, Count);
            return EFI_INVALID_PARAMETER;
        }
        *AKMSuiteCount = Count;
        if (AKMSuites) {
            for (i = 0; i < Count; i++) {
                CopyMem(&AKMSuites[i], Ie, 4);
                Ie += 4; Length -= 4;
            }
        }
    }
    else {
        return EFI_BAD_BUFFER_SIZE;
    }

    // Optional capabilities

    return 0;
}

STATIC
EFI_STATUS
Ieee80211ParseWpaIe(
    IN CONST UINT8 *Ie, 
    OUT UINT16 *CipherSuiteCount,
    OUT EFI_80211_SUITE_SELECTOR *CipherSuites,
    OUT UINT16 *AKMSuiteCount,
    OUT EFI_80211_SUITE_SELECTOR *AKMSuites)
{
    UINT16 Length;
    UINT16 i, Count;
    UINT16 Version;

    CONST EFI_80211_SUITE_SELECTOR *StdCipherSuite;
    UINT16 StdCipherSuiteCount = 0;
    CONST EFI_80211_SUITE_SELECTOR *StdAkmSuite;
    UINT16 StdAkmSuiteCount = 0;

    ASSERT(Ie != NULL);
    ASSERT(CipherSuiteCount != NULL);
    ASSERT(AKMSuiteCount != NULL);

    Length = Ie[1];
    if (Length < 14) {
        DbgInfo("WPA too short, Length %u\n", Length);
        return EFI_INVALID_PARAMETER;
    }
    Ie += 6; Length -= 4;  /* NOTE: Length is payload only */

    /* NOTE: WPA OUI is validated before  */
    Version = LE16(Ie);
    if (Version != 1) {
        DbgInfo("WPA bad version %u\n", Version);
        return EFI_INVALID_PARAMETER;
    }
    Ie += 2; Length -= 2;

    // Multicast/group cipher
    if (Length >= 4) {
        if (!WpaGetStandardCipherSuite(Ie, TRUE)) {
            DbgInfo("Unsupported group cipher suite: 0x%x\n", GetBe32(Ie));
            return EFI_INVALID_PARAMETER;
        }
        Ie += 4; Length -= 4;
    }
    else {
        return EFI_BAD_BUFFER_SIZE;
    }

    // Unicast ciphers
    if (Length >= 2) {
        Count = LE16(Ie);
        Ie += 2; Length -= 2;
        if (Length < Count * 4) {
            DbgInfo("RSN ucast cipher data too short; Length %u, Count %u\n",
                Length, Count);
            return EFI_INVALID_PARAMETER;
        }
        for (i = 0; i < Count; i++) {
            StdCipherSuite = WpaGetStandardCipherSuite(Ie, FALSE);
            if (StdCipherSuite) {
                if (CipherSuites) {
                    CopyMem(&CipherSuites[StdCipherSuiteCount], StdCipherSuite, SUITE_SIZE);
                }
                StdCipherSuiteCount++;
            }

            Ie += 4, Length -= 4;
        }

        if (StdCipherSuiteCount == 0) {
            DbgInfo("Supported WPA ucast cipher set empty\n");
            return EFI_UNSUPPORTED;
        }

        *CipherSuiteCount = StdCipherSuiteCount;
    }
    else {
        return EFI_BAD_BUFFER_SIZE;
    }

    // Key management algorithms
    if (Length >= 2) {
        Count = LE16(Ie);
        Ie += 2; Length -= 2;
        if (Length < Count * 4) {
            DbgInfo("WPA key mgmt alg data too short; Length %u, Count %u\n",
                Length, Count);
            return EFI_INVALID_PARAMETER;
        }
        for (i = 0; i < Count; i++) {
            StdAkmSuite = WpaGetStandardAkmSuite(Ie);
            if (StdAkmSuite) {
                if (AKMSuites) {
                    CopyMem(&AKMSuites[StdAkmSuiteCount], StdAkmSuite, SUITE_SIZE);
                }
                StdAkmSuiteCount++;
            }
            Ie += 4; Length -= 4;
        }
        *AKMSuiteCount = StdAkmSuiteCount;
    }
    else {
        return EFI_BAD_BUFFER_SIZE;
    }

    // Optional capabilities

    return 0;
}

STATIC UINT8
StaGetCalibratedRSSI(UINT8 rssi)
{
    /*
     * This calculation is based direct observation of the number of signal
     * strength bars shown by Vista in function of the RSSI value returned by
     * the XP driver. (In NDIS 5 the driver does not return the Link Quality
     * directly.)
     * In NDIS 6 the number of bars shown is directly proportional to the link
     * quality, as indicated below. According to the NDIS documentation, the
     * link quality should indicate the percentage of the maximum data rate
     * that can be achieved with a certain RSSI.
     *
     * Use a linear estimate of the link quality based on the RSSI value:
     *     45+          link quality = 100%         5 bars
     * 35..45           link quality = 80%-100%     5 bars
     * 25..35           link quality = 60%-80%      4 bars
     * 15..25           link quality = 40%-60%      3 bars
     *  7..15           link quality = 20%-40%      2 bars
     * -2..7            link quality =  0%-20%      1 bar
     * <= -2            link quality =  0%          1 bar
     *
     * We can use the following expression for 8 <= RSSI <= 45:
     *     LinkQuality = (((rssi + 5) / 10) * 20)
     * For RSSU < 8, use:
     *     LinkQuality = ((rssi + 5) * 2)
     */

     /* RSSI >= 45dB      link quality = 100% */
    if (rssi >= HIGH_RSSI_THRESHOLD)
    {
        return HIGH_RSSI_LINK_QUALITY;
    }

    /* RSSI <=  -2dB      link quality = 0% */
    if (rssi <= LOW_RSSI_THRESHOLD1)
    {
        return LOW_RSSI_LINK_QUALITY;
    }

    /* -2dB =< RSSI <= 7dB: link quality varies linearly from 0 to 18% */
    if (rssi <= LOW_RSSI_THRESHOLD2) {
        return ((rssi + 2) * 2);
    }

    /* 8dB =< RSSI <= 45dB: link quality varies linearly to 100% */
    return ((rssi + 5) * 2);
}

EFI_80211_NETWORK_ENTRY *
Build80211NetworkEntry(struct net80211_bss *bss)
{
    EFI_80211_NETWORK_ENTRY *NetworkEntry;
    EFI_80211_NETWORK_DESCRIPTION *NetworkDesc;
    EFI_80211_NETWORK *Network;
	EFI_STATUS Status;

    UINT16 CipherSuiteCount = 0, AKMSuiteCount = 0;
    EFI_80211_SSID Ssid = { 0 };

    const UINT8 *Position;
    CONST UINT8 *SsidIe, *RsnIe, *WpaIe;
    INT8 Signal;

    Signal = bss->signal;

    // SSID
    SsidIe = net80211_bss_find_ie(bss, WLAN_EID_SSID);
    if (!SsidIe || EFI_ERROR(Ieee80211ParseSsidIe(SsidIe, &Ssid)))
        return NULL;

    // RSN
    RsnIe = net80211_bss_find_ie(bss, WLAN_EID_RSN);
    if (RsnIe && EFI_ERROR(Ieee80211ParseRsnIe(RsnIe, &CipherSuiteCount, NULL, &AKMSuiteCount, NULL)))
        return NULL;

    // WPA
    WpaIe = CipherSuiteCount ? NULL : 
        net80211_bss_find_vendor_ie(bss, WLAN_OUI_MICROSOFT_WPA);
    if (WpaIe && EFI_ERROR(Ieee80211ParseWpaIe(WpaIe, &CipherSuiteCount, NULL, &AKMSuiteCount, NULL)))
        return NULL;

    NetworkEntry = AllocateZeroPool(
        sizeof(*NetworkEntry) +
        SizeofAkmSuiteSelector(AKMSuiteCount) +
        SizeOfCipherSuiteSelector(CipherSuiteCount));
    if (!NetworkEntry)
        return NULL;

    // Position points to available memory
    Position = (UINT8 *)(NetworkEntry + 1);

    NetworkDesc = &NetworkEntry->NetworkDesc;
    NetworkDesc->NetworkQuality = StaGetCalibratedRSSI(Signal - ATH_DEFAULT_NOISE_FLOOR);

    Network = &NetworkDesc->Network;
    Network->BSSType = IeeeInfrastructureBSS;
    Network->SSId = Ssid;

    Network->AKMSuite = (VOID *)Position;
    Position += SizeofAkmSuiteSelector(AKMSuiteCount);

    Network->CipherSuite = (VOID *)Position;
    Position += SizeOfCipherSuiteSelector(CipherSuiteCount);

    // Copy cipher and akm suite
    if (RsnIe) {
        Status = Ieee80211ParseRsnIe(RsnIe,
              &Network->CipherSuite->CipherSuiteCount, Network->CipherSuite->CipherSuiteList,
              &Network->AKMSuite->AKMSuiteCount, Network->AKMSuite->AKMSuiteList);
		if (Status != EFI_SUCCESS) {
            DbgError("RsnIe Parse Fail: %r\n", Status);
			FreePool(NetworkEntry);
			return NULL;
		}
    }
    if (WpaIe) {
        Status = Ieee80211ParseWpaIe(WpaIe,
              &Network->CipherSuite->CipherSuiteCount, Network->CipherSuite->CipherSuiteList,
              &Network->AKMSuite->AKMSuiteCount, Network->AKMSuite->AKMSuiteList);
		if (Status != EFI_SUCCESS) {
            DbgError("WpaIe Parse Fail: %r\n", Status);
            FreePool(NetworkEntry);
			return NULL;
		}
    }

    DbgInfo("Ssid: %a, len: %d Signal: %d, CipherSuiteCount:%d, AKMSuiteCount: %d, Freq: %d, Quality: %d\n",
        Network->SSId.SSId, Network->SSId.SSIdLen, Signal,
        Network->CipherSuite->CipherSuiteCount,
        Network->AKMSuite->AKMSuiteCount,
        bss->channel ? bss->channel->center_freq : 0,
        NetworkDesc->NetworkQuality);

    return NetworkEntry;
}

STATIC
EFI_80211_NETWORK_ENTRY *
NetworkListFindMatchNetwork(
    IN EFI_80211_NETWORK_LIST_INFO *NetworkListInfo,
    IN EFI_80211_NETWORK_ENTRY *NewNetworkEntry
)
{
    LIST_ENTRY *Entry;
    EFI_80211_NETWORK_ENTRY *NetworkEntry;
    EFI_80211_NETWORK_DESCRIPTION *NewNetworkDesc = &NewNetworkEntry->NetworkDesc;
    EFI_80211_NETWORK *NewNetwork = &NewNetworkDesc->Network;

    NET_LIST_FOR_EACH(Entry, &NetworkListInfo->NetworkList) {
        NetworkEntry = NET_LIST_USER_STRUCT(Entry, EFI_80211_NETWORK_ENTRY, Node);
        EFI_80211_NETWORK_DESCRIPTION *NetworkDesc = &NetworkEntry->NetworkDesc;
        EFI_80211_NETWORK *Network = &NetworkDesc->Network;

        if (Network->SSId.SSIdLen != NewNetwork->SSId.SSIdLen)
            continue;

        if (CompareMem(Network->SSId.SSId, NewNetwork->SSId.SSId,
            Network->SSId.SSIdLen) != 0)
            continue;

        if (!!Network->CipherSuite ^ !!NewNetwork->CipherSuite)
            continue;

        if (Network->CipherSuite) {
            if (Network->CipherSuite->CipherSuiteCount !=
                NewNetwork->CipherSuite->CipherSuiteCount)
                continue;

            if (CompareMem(Network->CipherSuite->CipherSuiteList,
                NewNetwork->CipherSuite->CipherSuiteList,
                Network->CipherSuite->CipherSuiteCount * SUITE_SIZE))
                continue;
        }

        if (!!Network->AKMSuite ^ !!NewNetwork->AKMSuite)
            continue;

        if (Network->AKMSuite) {
            if (Network->AKMSuite->AKMSuiteCount !=
                NewNetwork->AKMSuite->AKMSuiteCount)
                continue;

            if (CompareMem(Network->AKMSuite->AKMSuiteList,
                NewNetwork->AKMSuite->AKMSuiteList,
                Network->AKMSuite->AKMSuiteCount * SUITE_SIZE))
                continue;
        }

        return NetworkEntry;
    }

    return NULL;
}

VOID QcWlanScanIterateBss(struct net80211_pdev *pdev, struct net80211_bss *bss, void *data)
{
    EFI_80211_NETWORK_LIST_INFO *NetworkListInfo = data;
    EFI_80211_NETWORK_ENTRY *NetworkEntry;
    EFI_80211_NETWORK *Network;

    NetworkEntry = Build80211NetworkEntry(bss);
    if (!NetworkEntry)
        return;

    // Already exist
    if (NetworkListFindMatchNetwork(NetworkListInfo, NetworkEntry)) {
        FreePool(NetworkEntry);
        return;
    }

    Network = &NetworkEntry->NetworkDesc.Network;

    NetworkListInfo->NetworkCount++;
    NetworkListInfo->NetworkDescTotalSize += 
        sizeof(NetworkEntry->NetworkDesc);
    NetworkListInfo->NetworkDescTotalSize += 
        SizeOfCipherSuiteSelector(Network->CipherSuite->CipherSuiteCount);
    NetworkListInfo->NetworkDescTotalSize += 
        SizeofAkmSuiteSelector(Network->AKMSuite->AKMSuiteCount);

    InsertTailList(&NetworkListInfo->NetworkList, &NetworkEntry->Node);
}

EFI_STATUS
QcWlanBuildScanResult(
    EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    EFI_80211_GET_NETWORKS_RESULT **Result)
{
    NET80211_CONTEXT *Context = &Dev->WiFi;
    EFI_80211_NETWORK_LIST_INFO NetworkListInfo = { 0 };

    EFI_80211_NETWORK_ENTRY *NetworkEntry;
    EFI_80211_NETWORK_DESCRIPTION *NetworkDesc;
    EFI_80211_NETWORK *Network;
    LIST_ENTRY *Entry, *Temp;
    UINT8 *Position;
    UINT32 Size;

    EFI_80211_GET_NETWORKS_RESULT *NetworksResult;

    // Iterate the scan result.
    InitializeListHead(&NetworkListInfo.NetworkList);
    net80211_bss_iterate(Context->NetDev, QcWlanScanIterateBss, &NetworkListInfo);

    if (!NetworkListInfo.NetworkCount)
        return EFI_NOT_FOUND;

    // Build NetworkResults
    NetworksResult = AllocateZeroPool(OFFSET_OF(EFI_80211_GET_NETWORKS_RESULT, NetworkDesc) + 
        NetworkListInfo.NetworkDescTotalSize);
    if (!NetworksResult)
        return EFI_OUT_OF_RESOURCES;

    // Position points to available memory
    Position = (UINT8 *)(&NetworksResult->NetworkDesc[NetworkListInfo.NetworkCount]);

    NET_LIST_FOR_EACH_SAFE(Entry, Temp, &NetworkListInfo.NetworkList) {
        NetworkEntry = NET_LIST_USER_STRUCT(Entry, EFI_80211_NETWORK_ENTRY, Node);
        Network = &NetworkEntry->NetworkDesc.Network;

        NetworkDesc = &NetworksResult->NetworkDesc[NetworksResult->NumOfNetworkDesc++];
        CopyMem(NetworkDesc, &NetworkEntry->NetworkDesc, sizeof(*NetworkDesc));

        NetworkDesc->Network.AKMSuite = (VOID *)Position;
        Size = SizeofAkmSuiteSelector(Network->AKMSuite->AKMSuiteCount);
        CopyMem(NetworkDesc->Network.AKMSuite, Network->AKMSuite, Size);
        Position += Size;

        NetworkDesc->Network.CipherSuite = (VOID *)Position;
        Size = SizeOfCipherSuiteSelector(Network->CipherSuite->CipherSuiteCount);
        CopyMem(NetworkDesc->Network.CipherSuite, Network->CipherSuite, Size);
        Position += Size;

        RemoveEntryList(&NetworkEntry->Node);
        FreePool(NetworkEntry);
    }

    *Result = NetworksResult;

    DbgPrint("Wdev 0x%p: Scan completed - Count %d", 
        Context->NetIf, NetworkListInfo.NetworkCount);
    return EFI_SUCCESS;
}

VOID QcWlanProcessScanComplete(EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    struct net80211_vif *vif, struct net80211_scan_result *scan_result)
{
    EFI_STATUS Status = EFI_SUCCESS;

    if (!Dev->GetNetworksToken && !Dev->GetRssiToken) {
        DbgError("Unexpected scan complete: Scan is not running\n");
        return;
    }

    // Build the scan results
    if (Dev->GetNetworksToken) {
		Status = QcWlanBuildScanResult(Dev, &Dev->GetNetworksToken->Result);
		Dev->GetNetworksToken->Status = Status;
		
        // Complete the scan
        if (Dev->GetNetworksToken->Event)
            gBS->SignalEvent(Dev->GetNetworksToken->Event);
		
        Dev->GetNetworksToken = NULL;
    }

    // Build rssi results
    if (Dev->GetRssiToken) {
        Status = QcWlanBuildGetRssiResult(Dev, Dev->GetRssiToken);
		Dev->GetRssiToken->Status = Status;
		
        // Complete the scan
        if (Dev->GetRssiToken->Event)
            gBS->SignalEvent(Dev->GetRssiToken->Event);
		
        Dev->GetRssiToken = NULL;
    }

    DbgFlush(); // Flush the log
}

EFI_STATUS QcWlanScan(EFI_QCWLAN_DEVICE_CONTEXT *Dev, 
    EFI_80211_SSID *SSIdList, UINT32 NumOfSSId, 
    UINT32 *FrequencyList, UINT32 NumOfFreqency)
{
    EFI_STATUS Status;
    NET80211_CONTEXT *Context = &Dev->WiFi;
    struct net80211_scan_request *scan_request;
    struct ieee80211_channel *channel;
    u32 scan_chan_num;
    u32 n_ssids;
    u32 i;
    int err;

    // At least one SSID is required.
    n_ssids = MAX(NumOfSSId, 1);

    /* 
     * If the scan from RSSI tool, the NumOfFreqency will be set, will set according channels.
     * Else will copy all the scan-channels.
     */
    
	if (NumOfFreqency) {
        scan_chan_num = 0;
	    scan_request = kzalloc(sizeof(*scan_request) +
	        NumOfFreqency * sizeof(struct ieee80211_channel *) +
	        n_ssids * sizeof(struct ieee80211_ssid), GFP_KERNEL);
	}
    else {
        scan_chan_num = net80211_get_scan_channel_num(Context->NetDev);
        scan_request = kzalloc(sizeof(*scan_request) +
	        scan_chan_num * sizeof(struct ieee80211_channel *) +
	        n_ssids * sizeof(struct ieee80211_ssid), GFP_KERNEL);
	}

    if (!scan_request) {
        return EFI_OUT_OF_RESOURCES;
    }

    scan_request->vif = Context->NetIf;
    scan_request->n_ssids = n_ssids;
    if (NumOfFreqency) {
        scan_request->ssids = (void*)((u8*)scan_request +
            sizeof(*scan_request) + NumOfFreqency * sizeof(struct ieee80211_channel*));
    } 
    else {
        scan_request->ssids = (void*)((u8*)scan_request +
            sizeof(*scan_request) + scan_chan_num * sizeof(struct ieee80211_channel*));
    }

    if (NumOfSSId) {
        for (i = 0; i < NumOfSSId; i++) {
            scan_request->ssids[i].ssid_len = SSIdList[i].SSIdLen;
            memcpy(scan_request->ssids[i].ssid,
                SSIdList[i].SSId, scan_request->ssids[i].ssid_len);
        }
    }

    if (NumOfFreqency) {
        for (i = 0; i < NumOfFreqency; i++) {
            channel = net80211_get_channel(Context->NetDev, FrequencyList[i]);
            if (!channel) {
                DbgWarn("NetIf 0x%p: Frequency %d is not supported\n", FrequencyList[i]);
                continue;
            }
            scan_request->channels[scan_request->n_channels++] = channel;
        }
    }
    else {
        scan_request->n_channels = net80211_get_scan_channels(
            Context->NetDev, scan_request->channels, scan_chan_num);
	}

    DbgPrint("NetIf 0x%p: Start scan", Context->NetIf);
	
    err = net80211_scan(Context->NetDev, scan_request);
    Status = Net80211ErrorToEfiStatus(err);

    Dev->ScanTimestamp = GetTimeInMicrosecond();

    return Status;
}

EFI_80211_BSS_RSSI_ENTRY *
Build80211BssRssiEntry(struct net80211_bss *bss, EFI_80211_SSID *SSId, UINT64 Timestamp)
{
    EFI_80211_BSS_RSSI_ENTRY *BssRssiEntry;
    CONST UINT8 * SsidIe;

    if (bss->ts < Timestamp)
        return NULL;

    SsidIe = net80211_bss_find_ie(bss, WLAN_EID_SSID);
    if (!SsidIe || SsidIe[1] > IEEE80211_MAX_SSID_LEN) {
        return NULL;
    }

    if (SSId->SSIdLen != SsidIe[1])
        return NULL;
    if (CompareMem(SSId->SSId, SsidIe + 2, SSId->SSIdLen) != 0)
        return NULL;

    BssRssiEntry = AllocateZeroPool(sizeof(*BssRssiEntry));
    if (!BssRssiEntry)
        return NULL;

    CopyMem(BssRssiEntry->RssiDesc.Bssid, bss->bssid, sizeof(BssRssiEntry->RssiDesc.Bssid));
    CopyMem(BssRssiEntry->RssiDesc.ChainRssi, bss->chain_signal, sizeof(BssRssiEntry->RssiDesc.ChainRssi));
    BssRssiEntry->RssiDesc.ComboRssi = bss->signal;
    BssRssiEntry->RssiDesc.NumOfChain = bss->chains;

    BssRssiEntry->RssiDesc.SSId.SSIdLen = SsidIe[1];
    CopyMem(&BssRssiEntry->RssiDesc.SSId.SSId, SsidIe + 2, SsidIe[1]);
    DbgInfo("Rssi for SSID %a (%02X:%02X:%02X:%02X:%02X:%02X) "
        "NumOfChain: %d, ChainRssi[0]: %d, ChainRssi[1]: %d, ComboRssi: %d\n",
        BssRssiEntry->RssiDesc.SSId,
        BssRssiEntry->RssiDesc.Bssid[0], BssRssiEntry->RssiDesc.Bssid[1],
        BssRssiEntry->RssiDesc.Bssid[2], BssRssiEntry->RssiDesc.Bssid[3],
        BssRssiEntry->RssiDesc.Bssid[4], BssRssiEntry->RssiDesc.Bssid[5],
        BssRssiEntry->RssiDesc.NumOfChain,
        BssRssiEntry->RssiDesc.ChainRssi[0], BssRssiEntry->RssiDesc.ChainRssi[1],
        BssRssiEntry->RssiDesc.ComboRssi);

    return BssRssiEntry;
}

STATIC VOID
QcWlanGetBssRssiIterateBss(struct net80211_pdev *pdev, struct net80211_bss *bss, void *data)
{
	EFI_80211_BSS_RSSI_LIST_INFO *BssRssiListInfo = data;
	EFI_80211_BSS_RSSI_ENTRY *NewBssRssiEntry;
    LIST_ENTRY *Entry, *Temp;
    EFI_80211_BSS_RSSI_ENTRY *BssRssiEntry, *NextBssRssiEntry = NULL;

	// Build new bss rssi entry
    NewBssRssiEntry = Build80211BssRssiEntry(bss,
        &BssRssiListInfo->SSId, BssRssiListInfo->Timestamp);
	if (!NewBssRssiEntry)
		return;

    // Find the position to insert
    NET_LIST_FOR_EACH_SAFE(Entry, Temp, &BssRssiListInfo->BssRssiList) {
        BssRssiEntry = NET_LIST_USER_STRUCT(Entry, EFI_80211_BSS_RSSI_ENTRY, Node);
        if (NewBssRssiEntry->RssiDesc.ComboRssi > BssRssiEntry->RssiDesc.ComboRssi) {
            NextBssRssiEntry = BssRssiEntry;
            break;
        }
    }

    // Insert to list
    if (!NextBssRssiEntry) {
        InsertTailList(&BssRssiListInfo->BssRssiList, &NewBssRssiEntry->Node);
    }
    else {
        InsertListBefore(&BssRssiListInfo->BssRssiList, &NextBssRssiEntry->Node, &NewBssRssiEntry->Node);
    }

    BssRssiListInfo->BssRssiCount++;
}

EFI_STATUS
QcWlanBuildGetRssiResult(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
	IN EFI_QCWLAN_GET_RSSI_TOKEN *Token
)
{
	NET80211_CONTEXT *Context = &Dev->WiFi;
	EFI_80211_BSS_RSSI_LIST_INFO BssRssiListInfo = { 0 };
	EFI_QCWLAN_GET_RSSI_RESULT *RssiResult;

	LIST_ENTRY *Entry, *Temp;
	EFI_80211_BSS_RSSI_ENTRY *BssRssiEntry;
	BOOLEAN IsRecorded = FALSE;

	InitializeListHead(&BssRssiListInfo.BssRssiList);
    CopyMem(&BssRssiListInfo.SSId, &Token->Data->SSId, sizeof(BssRssiListInfo.SSId));
    CopyMem(&BssRssiListInfo.Timestamp, &Dev->ScanTimestamp, sizeof(BssRssiListInfo.Timestamp));
	net80211_bss_iterate(Context->NetDev, QcWlanGetBssRssiIterateBss, &BssRssiListInfo);

	// Build NetworkResults
	RssiResult = AllocateZeroPool(sizeof(*RssiResult) + 
        sizeof(RssiResult->RssiDesc[0]) * BssRssiListInfo.BssRssiCount);
	if (!RssiResult)
		return EFI_OUT_OF_RESOURCES;

	// Match SSID and output buffer
	NET_LIST_FOR_EACH_SAFE(Entry, Temp, &BssRssiListInfo.BssRssiList) {
        BssRssiEntry = NET_LIST_USER_STRUCT(Entry, EFI_80211_BSS_RSSI_ENTRY, Node);
		for (UINT32 i = 0; i < RssiResult->NumOfRssiDesc; i++) {
			if (!CompareMem(RssiResult->RssiDesc[i].Bssid, BssRssiEntry->RssiDesc.Bssid, EFI_MAX_BSSID_LEN)) {
				IsRecorded = TRUE;
				if (BssRssiEntry->RssiDesc.ComboRssi > RssiResult->RssiDesc[i].ComboRssi) {
					DbgInfo("SSID %a (%02X:%02X:%02X:%02X:%02X:%02X) has better BSS. old rssi=%d,  new rssi=%d\n",
                        BssRssiEntry->RssiDesc.SSId,
                        BssRssiEntry->RssiDesc.Bssid[0], BssRssiEntry->RssiDesc.Bssid[1],
                        BssRssiEntry->RssiDesc.Bssid[2], BssRssiEntry->RssiDesc.Bssid[3],
                        BssRssiEntry->RssiDesc.Bssid[4], BssRssiEntry->RssiDesc.Bssid[5],
						RssiResult->RssiDesc[i].ComboRssi, BssRssiEntry->RssiDesc.ComboRssi);

					CopyMem(RssiResult->RssiDesc[i].ChainRssi, BssRssiEntry->RssiDesc.ChainRssi, EFI_MAX_CHAIN);
					RssiResult->RssiDesc[i].ComboRssi = BssRssiEntry->RssiDesc.ComboRssi;
				}
				break;
			}
		}

		if (!IsRecorded) {
			CopyMem(&RssiResult->RssiDesc[RssiResult->NumOfRssiDesc], &BssRssiEntry->RssiDesc, 
                sizeof(BssRssiEntry->RssiDesc));
            RssiResult->NumOfRssiDesc++;
			DbgInfo("NumOfRssiDesc:%u, ChainRssi[0]=%d ChainRssi[1]=%d\n",
                RssiResult->NumOfRssiDesc,
                RssiResult->RssiDesc[RssiResult->NumOfRssiDesc].ChainRssi[0],
                RssiResult->RssiDesc[RssiResult->NumOfRssiDesc].ChainRssi[1]);
		}
        FreePool(BssRssiEntry);
	}

	Token->Result = RssiResult;

	return EFI_SUCCESS;
}