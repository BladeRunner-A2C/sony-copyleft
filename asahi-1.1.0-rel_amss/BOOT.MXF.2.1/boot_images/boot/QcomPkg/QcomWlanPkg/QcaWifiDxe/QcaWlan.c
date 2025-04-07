/*
 * Copyright (c) 2021-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 27/5/22   zxue     WAR for the WifiConnMgr for the assert issue
 28/2/22   zxue     uninstall QcWlanTestProtocol when unload driver
 18/11/21  zxue     refine code
 28/7/21   zxue     update the connection error code
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <net/net80211.h>
#include "QcaWlan.h"
#include "Debug.h"
#include "QcaScan.h"
#include "QcaTxRx.h"

/*** WLAN CONFIG ***/

#define QCWLAN_EAPOL_STEP_TIMEOUT_MS   1000
#define QCWLAN_EAPOL_CONNECT_RETRIES   2
#define QCWLAN_EAPOL_TIMEOUT_RETRIES   3
#define QCWLAN_TX_POOL_CAPACITY        4096
#define QCWLAN_TX_BUFFER_MAX_SIZE      2048

extern EFI_QCWLAN_DEVICE_CONTEXT gWlanDriverContext;

EFI_DEVICE_PATH_PROTOCOL *
QcWlanBuildDevicePath(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN EFI_HANDLE DeviceHandle,
    IN EFI_DRIVER_BINDING_PROTOCOL *BindingProtocol
)
{
    EFI_STATUS Status;
    EFI_DEVICE_PATH_PROTOCOL *DevicePath, *Temp, *FinalDevPath;
    MAC_ADDR_DEVICE_PATH     MacNode;
    WIFI_DEVICE_PATH         WifiNode;

    Status = gBS->OpenProtocol(DeviceHandle, &gEfiDevicePathProtocolGuid,
        (VOID **)&DevicePath, BindingProtocol->DriverBindingHandle,
        DeviceHandle, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR(Status)) {
        return NULL;
    }

    ZeroMem(&MacNode, sizeof(MacNode));
    MacNode.Header.Type = MESSAGING_DEVICE_PATH;
    MacNode.Header.SubType = MSG_MAC_ADDR_DP;
    SetDevicePathNodeLength(&MacNode, sizeof(MacNode));

    CopyMem(&MacNode.MacAddress, &Dev->Snm.CurrentAddress,
        sizeof(EFI_MAC_ADDRESS));
    MacNode.IfType = Dev->Snm.IfType;

    ZeroMem(&WifiNode, sizeof(WifiNode));
    WifiNode.Header.Type = MESSAGING_DEVICE_PATH;
    WifiNode.Header.SubType = MSG_WIFI_DP;
    SetDevicePathNodeLength(&WifiNode, sizeof(WifiNode));

    Temp = AppendDevicePathNode(DevicePath, &MacNode.Header);
    if (!Temp) {
        return NULL;
    }

    FinalDevPath = AppendDevicePathNode(Temp, &WifiNode.Header);
    FreePool(Temp);
    if (FinalDevPath == NULL) {
        return NULL;
    }

    return FinalDevPath;
}


EFI_STATUS
QcWlanInitializeNic(IN EFI_QCWLAN_DEVICE_CONTEXT *Dev)
{
    NET80211_CONTEXT *Context = &Dev->WiFi;
    VOID *NetIf = Context->NetIf;

    if (NetIf) {
        DbgError("NetIf 0x%p exists already\n", Context->NetIf);
        return EFI_ALREADY_STARTED;
    }

    DbgPrint("Adding interface");

    // add interface
    Context->NetIf = net80211_add_interface(Context->NetDev);
    DbgPrint("Added NetIf: 0x%p", Context->NetIf);

    return Context->NetIf ? EFI_SUCCESS : EFI_DEVICE_ERROR;
}

EFI_STATUS
QcWlanUninitializeNic(IN EFI_QCWLAN_DEVICE_CONTEXT *Dev)
{
    NET80211_CONTEXT *Context = &Dev->WiFi;
    VOID *NetIf = Context->NetIf;

    // Remove interface
    if (!NetIf) {
        return EFI_SUCCESS;
    }

	Dev->GetNetworksToken = NULL;
	Dev->DisconnectNetworkToken = NULL;
	Dev->ConnectNetworkToken = NULL;
	
    DbgPrint("Removing interface");

    if (net80211_remove_interface(Context->NetDev, NetIf) == 0) {
        Context->NetIf = NULL;
    }

    DbgPrint("NetIf 0x%p -> 0x%p", NetIf, Context->NetIf);

    return EFI_SUCCESS;
}

VOID
QcWlanApplyNicConfiguration(IN EFI_QCWLAN_DEVICE_CONTEXT *Dev)
{
    NET80211_CONTEXT *Context = &Dev->WiFi;
    EFI_80211_AKM_SUITE_SELECTOR *AKMSuites = NULL;
    UINTN AKMSuitesSize = 0;
    EFI_80211_CIPHER_SUITE_SELECTOR *CipherSuites = NULL;
    UINTN CipherSuitesSize = 0;
    EFI_STATUS Status;

    u32 n_akm_suites = 0, n_cipher_suites = 0;
    struct net80211_suite_selector *akm_suites = NULL, *cipher_suites = NULL;
    int err;

    // Supplicant supported akm suites
    Status = Dev->SupplicantProtocol->GetData(Dev->SupplicantProtocol,
        EfiSupplicant80211SupportedAKMSuites,
        (VOID*)AKMSuites, &AKMSuitesSize);
    if (Status == EFI_BUFFER_TOO_SMALL) {
        AKMSuites = AllocateZeroPool(AKMSuitesSize);
        if (AKMSuites) {
            Status = Dev->SupplicantProtocol->GetData(Dev->SupplicantProtocol,
                EfiSupplicant80211SupportedAKMSuites,
                (VOID*)AKMSuites, &AKMSuitesSize);
            DbgInfo("get supplicant supported akm suites: %r\n", Status);
        }
    }
    if (AKMSuites) {
        n_akm_suites = (u32)AKMSuites->AKMSuiteCount;
        akm_suites = (struct net80211_suite_selector *)AKMSuites->AKMSuiteList;

        BUILD_BUG_ON(sizeof(akm_suites[0]) != sizeof(AKMSuites->AKMSuiteList[0]));
    }
    err = net80211_set_supplicant_supported_akm_suites(Context->NetDev,
        akm_suites, n_akm_suites);
    if (AKMSuites)
        FreePool(AKMSuites);
    if (err) {
        DbgInfo("net80211_set_supplicant_supported_akm_suites: %d\n", err);
    }
    
    // Supplicant supported cipher suites
    Status = Dev->SupplicantProtocol->GetData(Dev->SupplicantProtocol,
        EfiSupplicant80211SupportedSoftwareCipherSuites,
        (VOID*)CipherSuites, &CipherSuitesSize);

    if (Status == EFI_BUFFER_TOO_SMALL) {
        CipherSuites = AllocateZeroPool(CipherSuitesSize);
        if (CipherSuites) {
            Status = Dev->SupplicantProtocol->GetData(Dev->SupplicantProtocol,
                EfiSupplicant80211SupportedSoftwareCipherSuites,
                (VOID*)CipherSuites, &CipherSuitesSize);
            DbgInfo("get supplicant supported software cipher suites: %r\n", Status);
        }
    }
    if (CipherSuites) {
        n_cipher_suites = (u32)CipherSuites->CipherSuiteCount;
        cipher_suites = (struct net80211_suite_selector *)CipherSuites->CipherSuiteList;

        BUILD_BUG_ON(sizeof(cipher_suites[0]) != sizeof(CipherSuites->CipherSuiteList[0]));
    }
    err = net80211_set_supplicant_supported_cipher_suites(Context->NetDev,
        cipher_suites, n_cipher_suites);
    if (CipherSuites)
        FreePool(CipherSuites);
    if (err) {
        DbgInfo("net80211_set_supplicant_supported_cipher_suites: %d\n", err);
    }

    // Counry code
#if SUPPORT_DEBUG_PRINT
    if (CfgIsCountryCodeValid()) {
        QcWlanSetCountryCode(Dev, CfgGetCountryCode());
    }
#endif
}

VOID
QcWlanGetMacAddress(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev, 
    OUT UINT8* Address
)
{
    net80211_get_mac_address(Dev->WiFi.NetDev, Address);

    DbgPrint("MAC: %02X-%02X-%02X-%02X-%02X-%02X",
        Address[0], Address[1], Address[2], Address[3], Address[4], Address[5]);
}

VOID 
QcWlanOnNet80211DeviceAdded(struct net80211_pdev *pdev, void *ctx)
{
    NET80211_CONTEXT *Context = ctx;

    if (Context->NetDev != NULL) {
        DbgError("Failed to add NetDev 0x%p, exits NetDev 0x%p already!\n",
            pdev, Context->NetDev);
        return;
    }

    Context->NetDev = pdev;
    DbgPrint("NetDev 0x%p added", pdev);
}

VOID
QcWlanOnNet80211DeviceRemoved(struct net80211_pdev *pdev, void *ctx)
{
    NET80211_CONTEXT *Context = ctx;

    if (Context->NetDev == pdev) {
        Context->NetDev = NULL;
        Context->NetIf = NULL;
    }

    DbgPrint("Remove NetDev 0x%p -> 0x%p", pdev, Context->NetDev);
}

EFI_STATUS
QcWlanSetSupplicantConnectionData(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev, 
    IN UINT8 *SsidData,
    IN UINT8 SsidLen,
    IN struct net80211_crypto_settings *crypto)
{
    EFI_STATUS Status = EFI_SUCCESS;
    
    EFI_80211_SSID *Ssid;
    EFI_80211_AKM_SUITE_SELECTOR *AKMSuite;
    EFI_80211_CIPHER_SUITE_SELECTOR *GroupCipher;
    EFI_80211_CIPHER_SUITE_SELECTOR *PairwiseCipher;

    UINTN AKMSuiteSize, GroupCipherSize, PairwiseCipherSize;
    VOID *DataBuffer, *DataFree;
	UINT8 MfpSet = 0;  
    u16 i;

	AKMSuiteSize = OFFSET_OF(EFI_80211_AKM_SUITE_SELECTOR, AKMSuiteList) +
        sizeof(AKMSuite->AKMSuiteList[0]) * crypto->n_akm_suites;
    GroupCipherSize = OFFSET_OF(EFI_80211_CIPHER_SUITE_SELECTOR, CipherSuiteList) +
        sizeof(GroupCipher->CipherSuiteList[0]) * 1;
    PairwiseCipherSize = OFFSET_OF(EFI_80211_CIPHER_SUITE_SELECTOR, CipherSuiteList) +
        sizeof(PairwiseCipher->CipherSuiteList[0]) * crypto->n_ciphers_pairwise;

    DataBuffer = AllocateZeroPool(sizeof(*Ssid) + 
        AKMSuiteSize + GroupCipherSize + PairwiseCipherSize);
    if (!DataBuffer) {
        Status = EFI_OUT_OF_RESOURCES;
        goto End;
    }
    Ssid = DataBuffer;
    Ssid->SSIdLen = SsidLen;
    CopyMem(Ssid->SSId, SsidData, SsidLen);
    DataFree = (UINT8 *)Ssid + sizeof(*Ssid);
    DbgInfo("SsidLen %d\n", SsidLen);

    Status = Dev->SupplicantProtocol->SetData(Dev->SupplicantProtocol,
        EfiSupplicant80211TargetSSIDName,
        (VOID *)Ssid,
        sizeof(EFI_80211_SSID));
    if (Status != EFI_SUCCESS) {
        DbgError("Fail to set SSID to supplicant: %r\n", Status);
        goto End;
    }

    if (AKMSuiteSize) {
        AKMSuite = DataFree;
        AKMSuite->AKMSuiteCount = crypto->n_akm_suites;
        for (i = 0; i < crypto->n_akm_suites; i++) {
            BUILD_BUG_ON(sizeof(AKMSuite->AKMSuiteList[0]) != sizeof(crypto->akm_suites[0]));
            *(UINT32 *)&AKMSuite->AKMSuiteList[i] = crypto->akm_suites[i];
            DbgInfo("AKMSuite[%d]: 0x%08X\n", i, *(UINT32 *)&AKMSuite->AKMSuiteList[i]);
        }
        DataFree = (UINT8 *)AKMSuite + AKMSuiteSize;

        Status = Dev->SupplicantProtocol->SetData(Dev->SupplicantProtocol,
            EfiSupplicant80211AKMSuite,
            (VOID *)AKMSuite,
            AKMSuiteSize);
        if (Status != EFI_SUCCESS) {
            DbgError("Fail to set AKMSuite to supplicant: %r\n", Status);
            goto End;
        }
    }

    if (GroupCipherSize) {
        GroupCipher = DataFree;
        GroupCipher->CipherSuiteCount = 1;
        BUILD_BUG_ON(sizeof(GroupCipher->CipherSuiteList[0]) != sizeof(crypto->cipher_group));
        *(UINT32 *)&GroupCipher->CipherSuiteList[0] = crypto->cipher_group;
        DataFree = (UINT8 *)GroupCipher + GroupCipherSize;

        DbgInfo("GroupCipher[0]: 0x%08X\n", *(UINT32 *)&GroupCipher->CipherSuiteList[0]);

        Status = Dev->SupplicantProtocol->SetData(Dev->SupplicantProtocol,
            EfiSupplicant80211GroupDataCipherSuite,
            (VOID *)GroupCipher,
            GroupCipherSize);
        if (Status != EFI_SUCCESS) {
            DbgError("Fail to set group cipher to supplicant: %r\n", Status);
            goto End;
        }
    }

    if (PairwiseCipherSize) {
        PairwiseCipher = DataFree;
        PairwiseCipher->CipherSuiteCount = crypto->n_ciphers_pairwise;
        for (i = 0; i < crypto->n_ciphers_pairwise; i++) {
            BUILD_BUG_ON(sizeof(PairwiseCipher->CipherSuiteList[0]) != sizeof(crypto->ciphers_pairwise[0]));
            *(UINT32 *)&PairwiseCipher->CipherSuiteList[i] = crypto->ciphers_pairwise[i];
            DbgError("PairwiseCipher[%d]: 0x%08X\n", i, *(UINT32 *)&PairwiseCipher->CipherSuiteList[i]);
        }

        DataFree = (UINT8 *)PairwiseCipher + PairwiseCipherSize;

        Status = Dev->SupplicantProtocol->SetData(Dev->SupplicantProtocol,
            EfiSupplicant80211PairwiseCipherSuite,
            (VOID *)PairwiseCipher,
            PairwiseCipherSize);
        if (Status != EFI_SUCCESS) {
            DbgError("Fail to set pairwise cipher to supplicant: %r\n", Status);
            goto End;
        }
    }

    // Set PMF settings
    if (crypto->mfp == (IEEE80211_RSN_CAP_MFP_ENABLED | IEEE80211_RSN_CAP_MFP_REQUIRED)) {
        MfpSet = EfiSupplicantMfpRequired;
    }
    else if (crypto->mfp == IEEE80211_RSN_CAP_MFP_ENABLED) {
        MfpSet = EfiSupplicantMfpOptional;
    }
    DbgInfo("MFP 0x%x\n", MfpSet);

    Status = Dev->SupplicantProtocol->SetData(Dev->SupplicantProtocol,
        EfiSupplicant80211UserMfp,
        (VOID *)(&MfpSet),
        sizeof(UINT8));
    if ((MfpSet == 0) && 
        (Status == EFI_UNSUPPORTED)) {
        DbgWarn("Cannot set MFP to supplicant: %r\n", Status);
        Status = EFI_SUCCESS;
    }
    else if (Status != EFI_SUCCESS) {
        DbgError("Fail to set MFP to supplicant: %r\n", Status);
        goto End;
    }

    // Set RSNXE capability
    Status = Dev->SupplicantProtocol->SetData(Dev->SupplicantProtocol,
        EfiSupplicant80211RsnxeCapability,
        (VOID *)(&crypto->rsnxe_cap),
        sizeof(UINT8));
    if ((crypto->rsnxe_cap) &&
        (Status == EFI_UNSUPPORTED)) {
        DbgWarn("Cannot set RSNXE capability to supplicant: %r\n", Status);
        Status = EFI_SUCCESS;
    }
    else if (Status != EFI_SUCCESS) {
        DbgError("Fail to set RSNXE capability to supplicant: %r\n", Status);
        goto End;
    }

End:
    FreePool(DataBuffer);
    return Status;
}

VOID
QcWlanProcessConnectComplete(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN struct net80211_vif *vif,
    IN struct net80211_connect_result *result
)
{
    EFI_STATUS ConnectResult;

    if (!Dev->ConnectNetworkToken) {
        DbgError("No ongoing connect!\n");
        return;
    }

    if (result->status) {
        DbgError("Connect failed: %d reason = 0x%x\n", result->status, result->reason);
        ConnectResult = Net80211ErrorToEfiStatus(result->reason);
        goto ClearToken;
    }

    DbgInfo("Connected to BSSID %02X-%02X-%02X-%02X-%02X-%02X\n",
        result->bssid[0], result->bssid[1], result->bssid[2],
        result->bssid[3], result->bssid[4], result->bssid[5]);

    ConnectResult = EFI_SUCCESS;

    // Update the status
    Dev->WantEapol = result->want_eapol;
    if (CompareMem(Dev->Bssid, result->bssid, sizeof(Dev->Bssid)) != 0) {
        CopyMem(Dev->Bssid, result->bssid, sizeof(Dev->Bssid));
        if (Dev->WantEapol) {
            ConnectResult = QcWlanSetSupplicantConnectionData(Dev, result->ssid,
                result->ssid_len, &result->crypto);
            if (EFI_ERROR(ConnectResult)) {
                DbgError("Failed to setup supplicant connection data: %r\n", ConnectResult);
                goto ClearToken;
            }
        }
    }

    sk_buff_pool_init(&Dev->tx_skb_pool, 
        QCWLAN_TX_POOL_CAPACITY, QCWLAN_TX_BUFFER_MAX_SIZE, &Dev->PciDev);

    // For PSK/1X we will continue the eapol/wpa sm
    if (Dev->WantEapol) {
        QcWlanSetSupplicantState(Dev, Ieee80211PendingRSNAuthentication);

        ConnectResult = QcWlanSetupEapolSm(Dev, QCWLAN_EAPOL_KEY_ALL);
        if (EFI_ERROR(ConnectResult)) {
            DbgError("Failed to setup eapol state machine: %r\n", ConnectResult);
            goto ClearToken;
        }
        DbgInfo("Waiting for supplicant to authorize 802.1X connection\n");
    }
    else {
        QcWlanSetSupplicantState(Dev, Ieee80211AuthenticatedAssociated);
        Dev->Snm.MediaPresent = TRUE;
    }

ClearToken:
    if (!Dev->PendingEapolConnect)
        QcWlanCompleteConnection(Dev, ConnectResult);
}

VOID 
QcWlanProcessDisconnectComplete(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN struct net80211_vif *vif,
    IN struct net80211_disconnect_result *result
)
{
    QcWlanCompleteConnection(Dev, EFI_DEVICE_ERROR);

    ZeroMem(Dev->Bssid, ETH_ALEN);
    QcWlanSetSupplicantState(Dev, Ieee80211UnauthenticatedUnassociated);
    Dev->Snm.MediaPresent = FALSE;

    if (Dev->DisconnectNetworkToken) {
        Dev->DisconnectNetworkToken->Status = EFI_SUCCESS;
        gBS->SignalEvent(Dev->DisconnectNetworkToken->Event);
        Dev->DisconnectNetworkToken = NULL;
    }

    sk_buff_pool_purge(&Dev->tx_skb_pool);
}

STATIC
VOID
QcWlanExtAuthAbort(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
)
{
    DbgPrint("QcWlanExtAuthAbort");

    // TODOTODO: abort auth due to failure. clean up here???
}

STATIC
VOID
QcWlanProcessExternalAuthRequest(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN struct net80211_vif *vif,
    IN struct net80211_auth_request_query *query
)
{
    struct net80211_auth_frame_desc *desc = query->desc;
    EFI_STATUS Status = EFI_SUCCESS;
    UINT8 *Buf = desc->data;
    CONST UINTN BufSize = sizeof(desc->data);
    UINTN RespSize = BufSize;

    CopyMem(Dev->Bssid, query->ctx.bssid, sizeof(Dev->Bssid));
    Status = QcWlanSetSupplicantConnectionData(Dev, 
        query->ctx.ssid, query->ctx.ssid_len, &query->ctx.crypto);
    if (Status != EFI_SUCCESS) {
        DbgError("Failed to set supplicant connection data: %r\n", Status);
        goto Out;
    }

    QcWlanSetSupplicantState(Dev, Ieee80211UnauthenticatedUnassociated);

    // Requesting response for NULL packet means build the first commit frame
    Status = Dev->SupplicantProtocol->BuildResponsePacket(
        Dev->SupplicantProtocol,
        NULL,
        0,
        Buf,
        &RespSize);

    if (Status != EFI_SUCCESS || RespSize < 24 || RespSize >= BufSize) {
        DbgError("BuildResponsePacket failed: %r RespSize=%d\n", Status, RespSize);
        goto Out;
    }

    DbgInfo("BuildResponsePacket on buffer 0x%p: Size=%d\n", Buf, RespSize);
    
    desc->err = 0;
    desc->data_len = (u32)RespSize;

    return;
Out:
    if (Status != EFI_SUCCESS) {
        desc->err = -ENODATA;
        QcWlanExtAuthAbort(Dev);
    }

    return;
}

STATIC
VOID
QcWlanProcessExternalAuthResponse(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN struct net80211_vif *vif,
    IN struct net80211_auth_response_query *query
)
{
    const struct ieee80211_mgmt *mgmt = query->rx.data;
    u32 mgmt_len = query->rx.data_len;
    struct net80211_auth_frame_desc *desc = query->desc;
    
    EFI_STATUS Status = EFI_SUCCESS;
    UINT8 *Buf = desc->data;
    CONST UINTN BufSize = sizeof(desc->data);
    UINTN RespSize = BufSize;

    DbgInfo("rx data 0X%p, length %d\n", mgmt, mgmt_len);
    DbgInfo("auth_algorithm %d, auth_transaction %d, status_code %d, variable [%d %d]\n",
        mgmt->u.auth.auth_algorithm,
        mgmt->u.auth.auth_transaction, mgmt->u.auth.status_code,
        mgmt->u.auth.variable[0], mgmt->u.auth.variable[1]);

    Status = Dev->SupplicantProtocol->BuildResponsePacket(
        Dev->SupplicantProtocol,
        (UINT8*)mgmt,
        mgmt_len,
        Buf,
        &RespSize);

    if (Status != EFI_SUCCESS || RespSize < 24 || RespSize >= BufSize) {
        DbgError("Failed to BuildResponsePacket: Status %r, RespSize %d\n", Status, RespSize);
        goto End;
    }

    DbgInfo("BuildResponsePacket on buffer 0x%p: Size %d\n", Buf, RespSize);
    desc->err = 0;
    desc->data_len = (u32)RespSize;

End:
    if (Status == EFI_SUCCESS && RespSize == 0) {
        EFI_80211_LINK_STATE State = Ieee80211UnauthenticatedUnassociated;
        UINTN StateSize = sizeof(State);

        Status = Dev->SupplicantProtocol->GetData(Dev->SupplicantProtocol,
            EfiSupplicant80211LinkState,
            (VOID*)&State, &StateSize);
        if (Status != EFI_SUCCESS)
            DbgError("Failed to get Supplicant link state %r\n", Status);

        DbgInfo("Supplicant link state %d\n", State);
    }

    if (Status != EFI_SUCCESS) {
        desc->err = -ENODATA;
        QcWlanExtAuthAbort(Dev);
    }
}

VOID QcWlanOnNet80211DeviceNotification(
    struct net80211_pdev *pdev,
    struct net80211_dev_event *devt, 
    void *ctx
)
{
    EFI_QCWLAN_DEVICE_CONTEXT *Dev = BASE_CR(ctx, EFI_QCWLAN_DEVICE_CONTEXT, WiFi);

    switch (devt->type) {
    case NET80211_EVENT_SCAN_COMPLETE:
        QcWlanProcessScanComplete(Dev, devt->vif, (struct net80211_scan_result *)devt->data);
        break;

    case NET80211_EVENT_EXTERNAL_AUTH_REQUEST:
        QcWlanProcessExternalAuthRequest(Dev, devt->vif, (struct net80211_auth_request_query *)devt->data);
        break;

    case NET80211_EVENT_EXTERNAL_AUTH_RESPONSE:
        QcWlanProcessExternalAuthResponse(Dev, devt->vif, (struct net80211_auth_response_query *)devt->data);
        break;

    case NET80211_EVENT_CONNECT_COMPLETE:
        QcWlanProcessConnectComplete(Dev, devt->vif, (struct net80211_connect_result *)devt->data);
        break;

    case NET80211_EVENT_DISCONNECT_COMPLETE:
        QcWlanProcessDisconnectComplete(Dev, devt->vif, (struct net80211_disconnect_result *)devt->data);
        break;
    default:
        DbgError("UNSUPPORTED EVENT: %u\n", devt->type);
        break;
    }
}

STATIC
VOID
QcWlanGetConnectCryptoSettings(
    IN EFI_80211_NETWORK *Network,
    OUT struct net80211_crypto_settings *settings
)
{
    UINT32 i;

    BUILD_BUG_ON(sizeof(EFI_80211_SUITE_SELECTOR) != sizeof(struct net80211_suite_selector));

    for (i = 0; i < Network->CipherSuite->CipherSuiteCount; i++) {
        EFI_80211_SUITE_SELECTOR *CipherSuite = &Network->CipherSuite->CipherSuiteList[i];

        if (QcWlanIsSupportedCipherSuite(CipherSuite)) {
            settings->ciphers_pairwise[settings->n_ciphers_pairwise++] = 
                WLAN_SUITE_SELECTOR((struct net80211_suite_selector *)CipherSuite);

            DbgInfo("Supported cipher suite: %02X%02X%02X-%02X\n",
                CipherSuite->Oui[0], CipherSuite->Oui[1], CipherSuite->Oui[2], CipherSuite->SuiteType);
        }
        else {
            DbgError("Unsupported cipher suite: %02X%02X%02X-%02X\n",
                CipherSuite->Oui[0], CipherSuite->Oui[1], CipherSuite->Oui[2], CipherSuite->SuiteType);
        }
    }

    for (i = 0; i < Network->AKMSuite->AKMSuiteCount; i++) {
        EFI_80211_SUITE_SELECTOR *AkmSuite = &Network->AKMSuite->AKMSuiteList[i];

        if (QcWlanIsSupportedAkmSuite(AkmSuite)) {
            settings->akm_suites[settings->n_akm_suites++] =
                WLAN_SUITE_SELECTOR((struct net80211_suite_selector *)AkmSuite);

            DbgInfo("Supported akm Suite: %02X%02X%02X-%02X\n",
                AkmSuite->Oui[1], AkmSuite->Oui[1], AkmSuite->Oui[2], AkmSuite->SuiteType);
        }
        else {
            DbgError("Unsupported akm suite: %02X%02X%02X-%02X\n",
                AkmSuite->Oui[1], AkmSuite->Oui[1], AkmSuite->Oui[2], AkmSuite->SuiteType);
        }
    }
}

EFI_STATUS
QcWlanConnect(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN EFI_80211_CONNECT_NETWORK_TOKEN *Token
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    NET80211_CONTEXT *Context;
    EFI_80211_NETWORK *Network;

    struct net80211_connect_params connect_params = { 0 };
    int err;

    Context = &Dev->WiFi;
    if (!Context->NetIf) {
        Status = EFI_ACCESS_DENIED;
        DbgError("Invalid NetIf\n");
        return Status;
    }

    Network = Token->Data->Network;

    DbgPrint("Try to connect to SSID %a", Network->SSId.SSId);

    connect_params.ssid_len = Network->SSId.SSIdLen;
    memcpy(connect_params.ssid, Network->SSId.SSId, connect_params.ssid_len);
    connect_params.auth_type = NL80211_AUTHTYPE_AUTOMATIC;

    QcWlanGetConnectCryptoSettings(Network, &connect_params.crypto);

    // start connect
    Dev->ConnectNetworkToken = Token;
    err = net80211_connect(Context->NetDev, Context->NetIf, &connect_params);
    DbgPrint("net80211_connect returns %d", err);

    if (err) {
        Dev->ConnectNetworkToken = NULL;
        goto Out;
    }
Out:
    return Net80211ErrorToEfiStatus(err);
}

EFI_STATUS
QcWlanDisconnect(
	IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
	IN EFI_80211_DISCONNECT_NETWORK_TOKEN *Token)
{
    EFI_STATUS Status = EFI_SUCCESS;
    NET80211_CONTEXT *Context;
    int err;

    if (!Dev->Snm.MediaPresent && !Dev->ConnectNetworkToken) {
        DbgError("Failing disconnect since not connected\n");
        return EFI_NOT_FOUND;
    }

    Context = &Dev->WiFi;
    if (!Context->NetIf) {
        Status = EFI_ACCESS_DENIED;
        return Status;
    }

	Dev->DisconnectNetworkToken = Token;
    err = net80211_disconnect(Context->NetDev, Context->NetIf);
    if (err) {
        Status = Net80211ErrorToEfiStatus(err);
        DbgError("Failed to send disconnect command: %d\n", err);
    }

    DbgFlush();
    return Status;
}

EFI_STATUS
QcWlanSetKey(EFI_QCWLAN_DEVICE_CONTEXT *Dev, EFI_SUPPLICANT_KEY *Key)
{
    NET80211_CONTEXT *Context = &Dev->WiFi;
    VOID *NetIf = Context->NetIf;

    /* Be sure EFI_SUPPLICANT_KEY is equal to struct net80211_key_set */
    BUILD_BUG_ON(sizeof(*Key) != sizeof(struct net80211_key_set));
    BUILD_BUG_ON(OFFSET_OF(EFI_SUPPLICANT_KEY, KeyLen) != OFFSET_OF(struct net80211_key_set, key_len));
    BUILD_BUG_ON(OFFSET_OF(EFI_SUPPLICANT_KEY, CipherSuite) != OFFSET_OF(struct net80211_key_set, cipher_suite));

    // install key
    net80211_install_key(Context->NetDev, NetIf, (void *)Key);
    return EFI_SUCCESS;
}

EFI_STATUS
QcWlanSetPtkKey(
  IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
)
{
	EFI_SUPPLICANT_KEY Key;
	EFI_STATUS Status;
	UINTN PtkLen = sizeof(EFI_SUPPLICANT_KEY);

	Status = Dev->SupplicantProtocol->GetData(Dev->SupplicantProtocol,
        EfiSupplicant80211PTK,
        (UINT8*)&Key,
        &PtkLen);
	if (Status != EFI_SUCCESS) {
		DbgError("Get PTK fail: %r\n", Status);
		return Status;
	}

    DbgDump("PTK: ", (UINT8 *)&Key, sizeof(EFI_SUPPLICANT_KEY), (UINT32)PtkLen);

	// send cmd to install key
	QcWlanSetKey(Dev, &Key);
	
	return EFI_SUCCESS;
}

EFI_STATUS
QcWlanSetGtkKey(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
)
{
	EFI_SUPPLICANT_GTK_LIST GtkKey;
	EFI_SUPPLICANT_KEY* Key = NULL;
	EFI_STATUS Status;
	UINTN GtkLen = sizeof(EFI_SUPPLICANT_GTK_LIST);

	Status = Dev->SupplicantProtocol->GetData(Dev->SupplicantProtocol,
        EfiSupplicant80211GTK,
        (UINT8*)&GtkKey,
        &GtkLen);
	if (Status != EFI_SUCCESS) {
		DbgError("Get GTK failed: %r\n", Status);
		return Status;
	}

    DbgDump("GTK: ", (UINT8 *)&GtkKey ,sizeof(EFI_SUPPLICANT_GTK_LIST), (UINT32)GtkLen);

	// Send cmd to install key
	Key = &GtkKey.GTKList[0];
	QcWlanSetKey(Dev, Key);
	
	return EFI_SUCCESS;
}


EFI_STATUS
QcWlanSetIGtkKey(
    IN EFI_QCWLAN_DEVICE_CONTEXT* Dev
)
{
    EFI_SUPPLICANT_GTK_LIST iGtkKey;
    EFI_SUPPLICANT_KEY* Key = NULL;
    EFI_STATUS Status;
    UINTN GtkLen = sizeof(EFI_SUPPLICANT_GTK_LIST);

    Status = Dev->SupplicantProtocol->GetData(Dev->SupplicantProtocol,
        EfiSupplicant80211IGTK,
        (UINT8*)&iGtkKey,
        &GtkLen);
    if (Status != EFI_SUCCESS) {
        DbgError("Get IGTK failed: %r\n", Status);
        return Status;
    }
    if(!iGtkKey.GTKCount)
        return EFI_SUCCESS;

    DbgDump("IGTK: ", (UINT8*)&iGtkKey, sizeof(EFI_SUPPLICANT_GTK_LIST), (UINT32)GtkLen);

	// Send cmd to install key
	Key = &iGtkKey.GTKList[0];
	QcWlanSetKey(Dev, Key);

    return EFI_SUCCESS;
}
VOID
QcWlanCompleteConnection(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN EFI_STATUS Status
)
{
    if (!Dev->ConnectNetworkToken)
        return;

    QcWlanCleanupEapolSm(Dev);

	DbgPrint("Status = %r, Event = 0x%x", Status, Dev->ConnectNetworkToken->Event);
    Dev->ConnectNetworkToken->Status = Status;
	switch (Status) {
		case EFI_SUCCESS:
			Dev->ConnectNetworkToken->ResultCode = ConnectSuccess;
			break;
		case EFI_ABORTED:
			Dev->ConnectNetworkToken->ResultCode = ConnectFailureTimeout;
			break;
		default:
			Dev->ConnectNetworkToken->ResultCode = ConnectFailed;
	}

    if (Dev->ConnectNetworkToken->Event) {
        gBS->SignalEvent(Dev->ConnectNetworkToken->Event);
    }

    Dev->ConnectNetworkToken = NULL;
}

VOID
QcWlanSetSupplicantState(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN EFI_80211_LINK_STATE State
)
{
    if (!Dev->SupplicantProtocol)
        return;

    DbgPrint("%02X-%02X-%02X-%02X-%02X-%02X: state %d", Dev->Bssid[0], Dev->Bssid[1],
        Dev->Bssid[2], Dev->Bssid[3], Dev->Bssid[4], Dev->Bssid[5], State);
    Dev->SupplicantProtocol->SetData(Dev->SupplicantProtocol,
        EfiSupplicant80211TargetSSIDMac,
        Dev->Bssid,
        ETH_ALEN);

    Dev->SupplicantProtocol->SetData(Dev->SupplicantProtocol,
        EfiSupplicant80211LinkState,
        &State,
        sizeof(State));
}

EFI_STATUS
QcWlanHandleSupplicantState(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
)
{
    EFI_STATUS Status;
    EFI_80211_LINK_STATE State;
    UINTN StateSize;

    StateSize = sizeof(State);
    Status = Dev->SupplicantProtocol->GetData(Dev->SupplicantProtocol,
        EfiSupplicant80211LinkState,
        (VOID *)&State,
        &StateSize);
    if (Status != EFI_SUCCESS) {
        DbgError("Failed to get supplicant link state fail: %r\n", Status);
        return Status;
    }

    if (StateSize != sizeof(State)) {
        DbgError("Failed to get connection state - wrong size %d\n", StateSize);
        return EFI_DEVICE_ERROR;
    }

    if (State == Ieee80211AuthenticatedAssociated) {
        DbgInfo("Connect success for PSK/802.1X connection\n");

        // Set PTK and GTK
        if (Dev->PendingEapolConnect & QCWLAN_EAPOL_KEY_PAIRWISE) {
            Status = QcWlanSetPtkKey(Dev);
            if (Status != EFI_SUCCESS) {
                DbgError("Failed to set ptk key: %r\n", Status);
                return Status;
            }
        }
        
        if (Dev->PendingEapolConnect & QCWLAN_EAPOL_KEY_GROUP) {
            Status = QcWlanSetGtkKey(Dev);
            if (Status != EFI_SUCCESS) {
                DbgError("Failed to set gtk key: %r\n", Status);
                return Status;
            }
            //Set IGTK here.
            Status = QcWlanSetIGtkKey(Dev);
            if (Status != EFI_SUCCESS) {
                DbgError("Failed to set igtk key: %r\n", Status);
                return Status;
            }
        }

        QcWlanCompleteConnection(Dev, EFI_SUCCESS);
        QcWlanCleanupEapolSm(Dev);
        Dev->Snm.MediaPresent = TRUE;
    }
    else if (State < Ieee80211PendingRSNAuthentication) {
        DbgError("Eapol connect failed, retry %d\n",
            Dev->EapolConnectRetries);
        Dev->EapolConnectRetries++;

        if (Dev->EapolConnectRetries >= QCWLAN_EAPOL_CONNECT_RETRIES) {
            DbgError("Too many Eapol connect retries\n");
            return EFI_DEVICE_ERROR;
        }

        QcWlanSetSupplicantState(Dev, Ieee80211PendingRSNAuthentication);

        QcWlanSetEapolTimer(Dev);
    }
    else {
        DbgInfo("Record State = %d\n", State);
        if (Dev->EapolTimeoutRetries >= QCWLAN_EAPOL_TIMEOUT_RETRIES) {
            DbgError("Too many Eapol timeout retries\n");
            return EFI_DEVICE_ERROR;
        }

        QcWlanSetEapolTimer(Dev);
    }

    return EFI_SUCCESS;
}

VOID
QcWlanEapolTimeout(
    IN EFI_EVENT Event,
    IN VOID *Context
)
{
    EFI_QCWLAN_DEVICE_CONTEXT *Dev = Context;

    Dev->EapolTimeoutRetries++;

    DbgInfo("Eapol state machine timeout retries %d\n", 
        Dev->EapolTimeoutRetries);
    QcWlanRxEapol(Dev, NULL);
}

EFI_STATUS
QcWlanSetupEapolSm(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN UINT16 PendingEapolConnect
)
{
    EFI_STATUS Status;

    if (Dev->PendingEapolConnect)
        return EFI_ALREADY_STARTED;

    Dev->PendingEapolConnect = PendingEapolConnect;

    Dev->EapolConnectRetries = 0;
    Dev->EapolTimeoutRetries = 0;

    // Create an event to drive the eapol state machine.
    Status = gBS->CreateEvent(
        EVT_TIMER | EVT_NOTIFY_SIGNAL,
        TPL_CALLBACK,
        QcWlanEapolTimeout,
        Dev,
        &Dev->EapolTimeout);

    return Status;
}

EFI_STATUS
QcWlanCleanupEapolSm(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
)
{
    EFI_STATUS Status;

    if (!Dev->PendingEapolConnect)
        return EFI_SUCCESS;

    Dev->PendingEapolConnect = 0;

    // Cleanup the EAPOL timeout timer
    gBS->SetTimer(Dev->EapolTimeout, TimerCancel, 0);
    Status = gBS->CloseEvent(&Dev->EapolTimeout);

    return Status;
}

VOID
QcWlanSetEapolTimer(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
)
{
    gBS->SetTimer(Dev->EapolTimeout, TimerCancel, 0);
    gBS->SetTimer(Dev->EapolTimeout, TimerRelative,
        QCWLAN_EAPOL_STEP_TIMEOUT_MS * 10 * 1000);
}

EFI_STATUS
QcWlanSetCountryCode(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN CONST UINT8 *CCode
)
{
    NET80211_CONTEXT *Context = &Dev->WiFi;
    struct net80211_priv_cmd* Pcmd;

    if (!CCode || CCode[0] == '\0' || CCode[1] == '\0') {
        return EFI_INVALID_PARAMETER;
    }

    Pcmd = AllocateZeroPool(sizeof(struct net80211_priv_cmd) + 2 + 1);
    if (!Pcmd)
        return EFI_OUT_OF_RESOURCES;

    Pcmd->id = IEEE80211_PRIV_CMD_CCODE;
    Pcmd->len = 2;
    Pcmd->data[0] = CCode[0];
    Pcmd->data[1] = CCode[1];

    DbgInfo("Country %a\n", (u8 *)Pcmd->data);

    // Set the country code
    net80211_priv_command(Context->NetDev, Pcmd);
    FreePool(Pcmd);
    return EFI_SUCCESS;
}

/* Debugging */
#if SUPPORT_DEBUG_PRINT

STATIC
VOID
QcWlanForceRddm(IN EFI_QCWLAN_DEVICE_CONTEXT *Dev)
{
    NET80211_CONTEXT *Context = &Dev->WiFi;
    struct net80211_priv_cmd cmd = {
        .id = IEEE80211_PRIV_CMD_RDDM,
        .len = 0
    };

    // Always flush the log to avoid log missing
    GlobalLogSetFlushFrequency(1);

    // Trigger RDDM
    net80211_priv_command(Context->NetDev, &cmd);
}

STATIC
EFI_STATUS
QcWlanHandleSsidDebugCode(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN UINT32 NumOfSsid,
    EFI_80211_SSID *SSIDList
)
{
    EFI_80211_SSID *Ssid, *EndSsid;

    if (NumOfSsid < 2)
        return EFI_NOT_FOUND;

    Ssid = SSIDList;
    EndSsid = SSIDList + NumOfSsid;

    // Debug code
    if (AsciiStrnCmp((CONST CHAR8*)Ssid->SSId, "*+*+365296+*+*", Ssid->SSIdLen) != 0)
        return EFI_NOT_FOUND;
    Ssid++;

    // Parameter 1
    if (AsciiStrnCmp((CONST CHAR8*)Ssid->SSId, "RDDM", Ssid->SSIdLen) == 0) {
        QcWlanForceRddm(Dev);
        return EFI_SUCCESS;
    }

	// Set Country Code
    if (AsciiStrnCmp((CONST CHAR8*)Ssid->SSId, "CC", Ssid->SSIdLen) == 0) {
        Ssid++;
        if (Ssid >= EndSsid)
            return EFI_NOT_FOUND;
        if (Ssid->SSIdLen != 2)
            return EFI_INVALID_PARAMETER;

		return QcWlanSetCountryCode(Dev, Ssid->SSId);
    }
	
    if (AsciiStrnCmp((CONST CHAR8*)Ssid->SSId, "FLUSH_LOG", Ssid->SSIdLen) == 0) {
        Ssid++;
        if (Ssid < EndSsid) {
            UINTN ValN = Ssid->SSIdLen < EFI_MAX_SSID_LEN ? AsciiStrDecimalToUintn((CONST CHAR8*)Ssid->SSId) : 0;
            GlobalLogSetFlushFrequency((UINT32)ValN);
            DbgInfo("Set log flush frequency to %d\n", ValN);
        }
        else {
            GlobalLogFlush();
        }
        return EFI_SUCCESS;
    }
    if (AsciiStrnCmp((CONST CHAR8*)Ssid->SSId, "LOG_LEVEL", Ssid->SSIdLen) == 0) {
        UINTN ValN0, ValN1;
        Ssid++;
        if (Ssid >= EndSsid)
            return EFI_NOT_FOUND;
        ValN0 = Ssid->SSIdLen < EFI_MAX_SSID_LEN ? AsciiStrDecimalToUintn((CONST CHAR8*)Ssid->SSId) : 0;
        Ssid++;
        if (Ssid >= EndSsid)
            return EFI_NOT_FOUND;
        ValN1 = Ssid->SSIdLen < EFI_MAX_SSID_LEN ? AsciiStrDecimalToUintn((CONST CHAR8*)Ssid->SSId) : 0;
        GlobalLogSetLogLevel((WLAN_LOG_OUTPUT_TYPE)ValN0, (UINT8)ValN1);
        DbgInfo("Set log level type %d, level %d\n", ValN0, ValN1);
        return EFI_SUCCESS;
    }

    return EFI_NOT_FOUND;
}
#endif // !SUPPORT_DEBUG_PRINT

/*** WiFi2 Protocol ***/

STATIC
EFI_STATUS
EFIAPI QcWlanGetNetworks(
    IN EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL *This,
    IN EFI_80211_GET_NETWORKS_TOKEN *Token
)
{
    EFI_QCWLAN_DEVICE_CONTEXT *Dev;
    NET80211_CONTEXT *Context;
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_TPL OldTpl;

    if (!This || !Token || !Token->Data)
        return EFI_INVALID_PARAMETER;
	
    if (Token->Result) {
        DbgError("Invalid Token->Result\n");
        return EFI_INVALID_PARAMETER;
    }

    Dev = QCWLAN_DEV_FROM_WIFI2(This);

    OldTpl = gBS->RaiseTPL(TPL_CALLBACK);

    Context = &Dev->WiFi;
    if (!Context->NetIf) {
        Status = EFI_ACCESS_DENIED;
        DbgError("Invalid NetIf\n");
        goto Out;
    }

#if SUPPORT_DEBUG_PRINT
    Status = QcWlanHandleSsidDebugCode(Dev, 
        Token->Data->NumOfSSID, Token->Data->SSIDList);
    if (!EFI_ERROR(Status)) {
        DbgError("Debug command handled\n");
        Status = EFI_NOT_READY;
        goto Out;
    }
#endif //!SUPPORT_DEBUG_PRINT

    if (Dev->GetNetworksToken || Dev->GetRssiToken) {
        DbgError("Scan already in progress\n");
        Status = EFI_ACCESS_DENIED;
        goto Out;
    }

    if (Dev->ConnectNetworkToken) {
        DbgError("Failed to scan as connect already in progress\n");
        Status = EFI_ACCESS_DENIED;
        goto Out;
    }

    Dev->GetNetworksToken = Token;

    Status = QcWlanScan(Dev, Token->Data->SSIDList, Token->Data->NumOfSSID, NULL, 0);
	if (Status != EFI_SUCCESS) {
        Dev->GetNetworksToken = NULL;
        DbgError("Scan fail: %r\n", Status);
        goto Out;
	}

Out:
    gBS->RestoreTPL(OldTpl);
    return Status;
}

STATIC
EFI_STATUS
EFIAPI QcWlanConnectNetwork(
    IN EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL *This,
    IN EFI_80211_CONNECT_NETWORK_TOKEN *Token
)
{
    EFI_QCWLAN_DEVICE_CONTEXT *Dev;
    EFI_TPL OldTpl;
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_80211_NETWORK *Network;

    if (!This || !Token || !Token->Data || !Token->Data->Network)
        return EFI_INVALID_PARAMETER;

    Dev = QCWLAN_DEV_FROM_WIFI2(This);

    Network = Token->Data->Network;

    if (Network->BSSType != IeeeInfrastructureBSS) {
        DbgError("Unsupported BSSType %d\n", Network->BSSType);
        return EFI_UNSUPPORTED;
    }

    if (Dev->Snm.MediaPresent) {
        DbgError("Already connected\n");
        return EFI_ALREADY_STARTED;
    }

    if (Dev->GetNetworksToken || Dev->GetRssiToken) {
        UINT32 Tries = 0;
        DbgPrint("Waiting for scan completion...");
        do {
            gBS->Stall(100 * 1000); // 100ms
            Tries++;
        } while (Dev->GetNetworksToken && Tries < 100);

        if (Dev->GetNetworksToken) {
            DbgPrint("Timeout waiting for scan completion");
            return EFI_DEVICE_ERROR;
        }
    }

    DbgPrint("Proceeding with connect");

    OldTpl = gBS->RaiseTPL(TPL_CALLBACK);

    // initialize to failure
    Token->ResultCode = ConnectFailedReasonUnspecified;
    Token->Status = EFI_NOT_READY;

    // Connect to network
    Status = QcWlanConnect(Dev, Token);

    gBS->RestoreTPL(OldTpl);

    DbgFlush();

    return Status;
}

STATIC
EFI_STATUS
EFIAPI QcWlanDisconnectNetwork(
    IN EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL *This,
    IN EFI_80211_DISCONNECT_NETWORK_TOKEN *Token
)
{
    EFI_QCWLAN_DEVICE_CONTEXT *Dev;
    EFI_TPL OldTpl;
    EFI_STATUS Status = EFI_SUCCESS;

    if (!This || !Token)
        return EFI_INVALID_PARAMETER;

    Dev = QCWLAN_DEV_FROM_WIFI2(This);
    OldTpl = gBS->RaiseTPL(TPL_CALLBACK);

    Status = QcWlanDisconnect(Dev, Token);

    gBS->RestoreTPL(OldTpl);
    return Status;
}

STATIC
EFI_STATUS
QcWlanGetRssi(
    IN  EFI_QCWLAN_TEST_PROTOCOL *This,
    IN  EFI_QCWLAN_GET_RSSI_TOKEN *Token
)
{
    EFI_QCWLAN_DEVICE_CONTEXT *Dev;
    EFI_TPL OldTpl;
    EFI_STATUS Status = EFI_SUCCESS;

    if (!This || !Token || !Token->Data)
        return EFI_INVALID_PARAMETER;

    if (!Token->Data->SSId.SSId || !Token->Data->SSId.SSIdLen ||
        Token->Data->SSId.SSIdLen > EFI_MAX_SSID_LEN) {
        DbgError("Invalid SSID or length: %r\n");
        return EFI_INVALID_PARAMETER;
    }
    if (Token->Result) {
        DbgError("Invalid Token->Result\n");
        return EFI_INVALID_PARAMETER;
    }

    Dev = QCWLAN_DEV_FROM_TEST(This);
    OldTpl = gBS->RaiseTPL(TPL_CALLBACK);

    // Valiate the context
    if (!Dev->WiFi.NetIf) {
        Status = EFI_ACCESS_DENIED;
        DbgError("Invalid NetIf\n");
        goto Out;
    }

    if (Dev->GetNetworksToken || Dev->GetRssiToken) {
        DbgError("Scan already in progress\n");
        Status = EFI_ACCESS_DENIED;
        goto Out;
    }

    if (Dev->ConnectNetworkToken) {
        DbgError("Failed to scan as connect already in progress\n");
        Status = EFI_ACCESS_DENIED;
        goto Out;
    }

    // Scan
    DbgPrint("Get Chain RSSI for SSID: %a Length: %d, NumOfFrequency %d",
        Token->Data->SSId.SSId, Token->Data->SSId.SSIdLen,
        Token->Data->NumOfFrequency);
    Dev->GetRssiToken = Token;

    Status = QcWlanScan(Dev, (VOID *)&Token->Data->SSId, 1, 
        Token->Data->FrequencyList, Token->Data->NumOfFrequency);
    if (Status != EFI_SUCCESS) {
        Dev->GetRssiToken = NULL;
        DbgError("Failed to scan %a for rssi test: %r\n", Token->Data->SSId.SSId, Status);
        goto Out;
    }

Out:
    gBS->RestoreTPL(OldTpl);
    return Status;
}

STATIC
EFI_STATUS
QcWlanInitializeSupplicant(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
)
{
    EFI_SUPPLICANT_PROTOCOL *Supp = Dev->SupplicantProtocol;
	UINT8 DevMacAddress[ETHER_ADDR_LEN] = { 0 };
    EFI_80211_CIPHER_SUITE_SELECTOR CipherSuite;
    UINT8 WifiOui[] = { 0x00, 0x0F, 0xAC };
    EFI_STATUS Status;

	QcWlanGetMacAddress(Dev, DevMacAddress);

    // SupportedHardwareCipherSuites
    CipherSuite.CipherSuiteCount = 1;
    CopyMem(CipherSuite.CipherSuiteList[0].Oui, WifiOui, 3);
    CipherSuite.CipherSuiteList[0].SuiteType = 4; // CCMP
    Status = Supp->SetData(Supp,
        EfiSupplicant80211SupportedHardwareCipherSuites,
        (VOID *)&CipherSuite,
        sizeof(CipherSuite));
    if (Status != EFI_SUCCESS)
        goto End;

    // StationMac
    DbgInfo("MAC: %02X-%02X-%02X-%02X-%02X-%02X\n", DevMacAddress[0], DevMacAddress[1], DevMacAddress[2],
             DevMacAddress[3], DevMacAddress[4], DevMacAddress[5]);
    Status = Supp->SetData(Supp, 
        EfiSupplicant80211StationMac,
        (VOID *)DevMacAddress, 
        sizeof(EFI_80211_MAC_ADDRESS));
    if (Status != EFI_SUCCESS)
        goto End;

End:
    return Status;
}

STATIC
EFI_STATUS
QcWlanInstallSupplicantProtocol(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
)
{
    EFI_STATUS Status;
    EFI_HANDLE SupplicantServiceBindingProtocolHandle = NULL;
    UINTN HandleArraySize = sizeof(SupplicantServiceBindingProtocolHandle);

    Dev->SupplicantBindingProtocol = NULL;

    Status = gBS->LocateHandle(ByProtocol,
        &gEfiSupplicantServiceBindingProtocolGuid,
        NULL,
        &HandleArraySize,
        &SupplicantServiceBindingProtocolHandle);
    if (Status != EFI_SUCCESS) {
        DbgError("Failed to locate supplicant service binding handle: %r\n", Status);
        return Status;
    }

    Status = gBS->OpenProtocol(
        SupplicantServiceBindingProtocolHandle,
        &gEfiSupplicantServiceBindingProtocolGuid,
        (VOID **)&Dev->SupplicantBindingProtocol,
        Dev->BindingProtocol->DriverBindingHandle,
        NULL,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (Status != EFI_SUCCESS) {
        DbgError("Failed to open supplicant service binding protocol: %r\n", Status);
        return Status;
    }

    Status = Dev->SupplicantBindingProtocol->CreateChild(
        Dev->SupplicantBindingProtocol,
        &Dev->MacHandle);
    if (Status != EFI_SUCCESS) {
        DbgError("Failed to create supplicant handle: %r\n", Status);
        goto failure;
    }

    Status = gBS->OpenProtocol(
        Dev->MacHandle,
        &gEfiSupplicantProtocolGuid,
        (VOID **)&Dev->SupplicantProtocol,
        Dev->BindingProtocol->DriverBindingHandle,
        NULL,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (Status != EFI_SUCCESS) {
        DbgError("Failed to open supplicant protocol: %r\n", Status);
        goto failure;
    }

    Dev->SupplicantServiceBindingProtocolHandle = SupplicantServiceBindingProtocolHandle;

    Status = QcWlanInitializeSupplicant(Dev);
    if (Status != EFI_SUCCESS) {
        DbgError("Failed to set supplicant driver data: %r\n", Status);
        goto failure;
    }

    DbgPrint("Supplicant initalized");
    return EFI_SUCCESS;

failure:
    gBS->CloseProtocol(SupplicantServiceBindingProtocolHandle,
        &gEfiSupplicantServiceBindingProtocolGuid,
        Dev->BindingProtocol->DriverBindingHandle,
        NULL);
    Dev->SupplicantBindingProtocol = NULL;

    return Status;
}

STATIC
VOID
QcWlanUninstallSupplicantProtocol(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
)
{
    EFI_STATUS Status;

    if (Dev->SupplicantProtocol) {
        Status = gBS->CloseProtocol(Dev->MacHandle,
            &gEfiSupplicantProtocolGuid,
            Dev->BindingProtocol->DriverBindingHandle,
            NULL);
        if (EFI_ERROR(Status)) {
            DbgError("Failed to close supplicant protocol: %r\n", Status);
        }
        Dev->SupplicantProtocol = NULL;
    }

    if (Dev->SupplicantBindingProtocol) {
        Status = Dev->SupplicantBindingProtocol->DestroyChild(
            Dev->SupplicantBindingProtocol,
            Dev->MacHandle);
        if (EFI_ERROR(Status)) {
            DbgError("Failed to destory supplicant handle: %r\n", Status);
        }

        Status = gBS->CloseProtocol(Dev->SupplicantServiceBindingProtocolHandle,
            &gEfiSupplicantServiceBindingProtocolGuid,
            Dev->BindingProtocol->DriverBindingHandle,
            NULL);
        if (EFI_ERROR(Status)) {
            DbgError("Failed to close supplicant service binding protocol: %r\n", Status);
        }
        Dev->SupplicantBindingProtocol = NULL;
    }
}

EFI_STATUS
QcWlanInstallConnectionProtocols(
    IN EFI_QCWLAN_DEVICE_CONTEXT                *Dev
)
{
    EFI_STATUS Status;

    Status = QcWlanInstallSupplicantProtocol(Dev);
    if (EFI_ERROR(Status)) {
        DbgError("Failed to install supplicant protocol: %r\n", Status);
        goto Fail;
    };

    /* WirelessMacConnectionProtocol */
    Dev->WirelessMacConnectionProtocol.GetNetworks = QcWlanGetNetworks;
    Dev->WirelessMacConnectionProtocol.ConnectNetwork = QcWlanConnectNetwork;
    Dev->WirelessMacConnectionProtocol.DisconnectNetwork = QcWlanDisconnectNetwork;
    /* QcWlanTestProtocol */
    Dev->QcWlanTestProtocol.GetRssi = QcWlanGetRssi;

    Status = gBS->InstallMultipleProtocolInterfaces(
        &Dev->MacHandle,
        &gEfiWiFi2ProtocolGuid, &Dev->WirelessMacConnectionProtocol,
        &gEfiQcWlanTestProtocolGuid, &Dev->QcWlanTestProtocol,
        NULL);
    if (EFI_ERROR(Status)) {
        DbgError("Failed to install WiFi protocols: %r\n", Status);
        goto Fail;
    };

    return Status;

Fail:
    QcWlanUninstallSupplicantProtocol(Dev);
    return Status;
}

VOID
QcWlanUninstallConnectionProtocols(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev
)
{
    EFI_STATUS Status;

    if (Dev->GetNetworksToken) {
        QcWlanProcessScanComplete(Dev, Dev->WiFi.NetIf, NULL);
    }

    if (Dev->ConnectNetworkToken) {
        struct net80211_connect_result result = { 0 };

        result.status = 1;
        QcWlanProcessConnectComplete(Dev, Dev->WiFi.NetIf, &result);
    }

    if (Dev->DisconnectNetworkToken) {
        struct net80211_disconnect_result result = { 0 };

        result.reason = 1;
        result.from_ap = false;
        QcWlanProcessDisconnectComplete(Dev, Dev->WiFi.NetIf, &result);
    }

    Status = gBS->UninstallMultipleProtocolInterfaces(
        Dev->MacHandle,
        &gEfiWiFi2ProtocolGuid, &Dev->WirelessMacConnectionProtocol,
		&gEfiQcWlanTestProtocolGuid, &Dev->QcWlanTestProtocol,
        NULL
    );
    if (EFI_ERROR(Status)) {
        DbgError("Failed to uninstall WiFi protocols: %r\n", Status);
    };

    QcWlanCleanupEapolSm(Dev);

    QcWlanUninstallSupplicantProtocol(Dev);
}
