/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include "WlanSupplicant.h"
#include "Debug.h"

#define SUITE_SELECTOR_GET(_SL) \
     ((((UINT32)((_SL)->Oui[0])) << 24) | (((UINT32)((_SL)->Oui[1])) << 16) | \
     (((UINT32)((_SL)->Oui[2])) << 8) | ((UINT32)((_SL)->SuiteType)))

static int AKMSuiteSelectorToWpaKeyMgmt(
    CONST EFI_80211_SUITE_SELECTOR *SuiteSelector)
{
    switch (SUITE_SELECTOR_GET(SuiteSelector)) {
    case RSN_AUTH_KEY_MGMT_UNSPEC_802_1X:
        return WPA_KEY_MGMT_IEEE8021X;
    case RSN_AUTH_KEY_MGMT_PSK_OVER_802_1X:
        return WPA_KEY_MGMT_PSK;
#ifdef CONFIG_IEEE80211R
    case RSN_AUTH_KEY_MGMT_FT_802_1X:
        return WPA_KEY_MGMT_FT_IEEE8021X;
    case RSN_AUTH_KEY_MGMT_FT_PSK:
        return WPA_KEY_MGMT_FT_PSK;
#ifdef CONFIG_SHA384
    case RSN_AUTH_KEY_MGMT_FT_802_1X_SHA384:
        return WPA_KEY_MGMT_FT_IEEE8021X_SHA384;
#endif /* CONFIG_SHA384 */
#endif /* CONFIG_IEEE80211R */
    case RSN_AUTH_KEY_MGMT_802_1X_SHA256:
        return WPA_KEY_MGMT_IEEE8021X_SHA256;
    case RSN_AUTH_KEY_MGMT_PSK_SHA256:
        return WPA_KEY_MGMT_PSK_SHA256;
#ifdef CONFIG_SAE
    case RSN_AUTH_KEY_MGMT_SAE:
        return WPA_KEY_MGMT_SAE;
    case RSN_AUTH_KEY_MGMT_FT_SAE:
        return WPA_KEY_MGMT_FT_SAE;
#endif /* CONFIG_SAE */
    case RSN_AUTH_KEY_MGMT_802_1X_SUITE_B:
        return WPA_KEY_MGMT_IEEE8021X_SUITE_B;
    case RSN_AUTH_KEY_MGMT_802_1X_SUITE_B_192:
        return WPA_KEY_MGMT_IEEE8021X_SUITE_B_192;
    case RSN_AUTH_KEY_MGMT_FILS_SHA256:
        return WPA_KEY_MGMT_FILS_SHA256;
    case RSN_AUTH_KEY_MGMT_FILS_SHA384:
        return WPA_KEY_MGMT_FILS_SHA384;
    case RSN_AUTH_KEY_MGMT_FT_FILS_SHA256:
        return WPA_KEY_MGMT_FT_FILS_SHA256;
    case RSN_AUTH_KEY_MGMT_FT_FILS_SHA384:
        return WPA_KEY_MGMT_FT_FILS_SHA384;
#ifdef CONFIG_OWE
    case RSN_AUTH_KEY_MGMT_OWE:
        return WPA_KEY_MGMT_OWE;
#endif /* CONFIG_OWE */
#ifdef CONFIG_DPP
    case RSN_AUTH_KEY_MGMT_DPP:
        return WPA_KEY_MGMT_DPP;
#endif /* CONFIG_DPP */
    case RSN_AUTH_KEY_MGMT_OSEN:
        return WPA_KEY_MGMT_OSEN;
    default:
        return 0;
    }
}

STATIC BOOLEAN SupplicantValidateAKM(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    EFI_80211_AKM_SUITE_SELECTOR *AKMSuiteSelector;
    int WpaKeyMgmt;

    if (DataSize < sizeof(EFI_80211_AKM_SUITE_SELECTOR)) {
        return FALSE;
    }

    AKMSuiteSelector = (EFI_80211_AKM_SUITE_SELECTOR *)Data;
    if (AKMSuiteSelector->AKMSuiteCount == 0)
        return TRUE;
    if (AKMSuiteSelector->AKMSuiteCount != 1) {
        return FALSE;
    }

    WpaKeyMgmt = AKMSuiteSelectorToWpaKeyMgmt(&AKMSuiteSelector->AKMSuiteList[0]);
    if (WpaKeyMgmt != WPA_KEY_MGMT_PSK &&
		WpaKeyMgmt != WPA_KEY_MGMT_PSK_SHA256 &&
        WpaKeyMgmt != WPA_KEY_MGMT_IEEE8021X &&
        WpaKeyMgmt != WPA_KEY_MGMT_SAE &&
        WpaKeyMgmt != WPA_KEY_MGMT_IEEE8021X_SUITE_B &&
        WpaKeyMgmt != WPA_KEY_MGMT_IEEE8021X_SUITE_B_192) {
        SUPP_DBG("Invalid AKM suite 0x%x, wpa key mgmt %X",
            SUITE_SELECTOR_GET(&AKMSuiteSelector->AKMSuiteList[0]), WpaKeyMgmt);
        return FALSE;
    }

    return TRUE;
}

STATIC EFI_STATUS SupplicantSetAKM(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    EFI_80211_AKM_SUITE_SELECTOR *AKMSuiteSelector = (EFI_80211_AKM_SUITE_SELECTOR *)Data;
    struct wpas *wpas = &Instance->wpas;
    int WpaKeyMgmt = AKMSuiteSelectorToWpaKeyMgmt(&AKMSuiteSelector->AKMSuiteList[0]);

    // We assume only a single AKM
    Instance->SaeAkm = (WpaKeyMgmt == WPA_KEY_MGMT_SAE);

    SUPP_DBG("Configure AKM suite 0x%x, wpa key mgmt 0x%x",
        SUITE_SELECTOR_GET(&AKMSuiteSelector->AKMSuiteList[0]), WpaKeyMgmt);

    Instance->SuiteType = WpaKeyMgmt;
    Instance->IsOneXCompleted = 0;

    wpas_set_key_mgmt(wpas, WpaKeyMgmt);

    return EFI_SUCCESS;
}

STATIC BOOLEAN SupplicantSupportedAKMValidate(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    EFI_80211_AKM_SUITE_SELECTOR *AKMSuiteSelector;
    UINTN AKMSuiteSelctorSize;

    if (DataSize < sizeof(EFI_80211_AKM_SUITE_SELECTOR)) {
        return FALSE;
    }

    AKMSuiteSelector = (EFI_80211_AKM_SUITE_SELECTOR *)Data;
    AKMSuiteSelctorSize = OFFSET_OF(EFI_80211_AKM_SUITE_SELECTOR, AKMSuiteList) +
        (sizeof(EFI_80211_SUITE_SELECTOR) * AKMSuiteSelector->AKMSuiteCount);

    if (DataSize < AKMSuiteSelctorSize) {
        return FALSE;
    }

    return TRUE;
}

STATIC EFI_STATUS SupplicantSupportedAKMSet(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    EFI_80211_AKM_SUITE_SELECTOR *AKMSuites;

    AKMSuites = AllocateZeroPool(DataSize);
    if (AKMSuites == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    if (Instance->SupportedAKMSuites) {
        FreePool(Instance->SupportedAKMSuites);
    }

    CopyMem(AKMSuites, Data, DataSize);
    Instance->SupportedAKMSuites = AKMSuites;

    return EFI_SUCCESS;
}

STATIC EFI_STATUS SupplicantSupportedAKMGet(IN SUPPLICANT_INSTANCE *Instance,
    OUT VOID *Data,
    IN OUT UINTN *DataSize)
{
    EFI_80211_AKM_SUITE_SELECTOR *AKMSuiteSelector;
    UINTN AKMSuiteSelectorSize;

    if (Instance->SupportedAKMSuites == NULL) {
        return EFI_NOT_FOUND;
    }

    AKMSuiteSelector = Instance->SupportedAKMSuites;
    AKMSuiteSelectorSize = OFFSET_OF(EFI_80211_AKM_SUITE_SELECTOR, AKMSuiteList) +
        (sizeof(EFI_80211_SUITE_SELECTOR) * AKMSuiteSelector->AKMSuiteCount);

    if (*DataSize < AKMSuiteSelectorSize) {
        *DataSize = AKMSuiteSelectorSize;
        return EFI_BUFFER_TOO_SMALL;
    }

    CopyMem(Data, AKMSuiteSelector, AKMSuiteSelectorSize);
    *DataSize = AKMSuiteSelectorSize;

    return EFI_SUCCESS;
}

static int CipherSuiteSelectorToWpaCipher(
    CONST EFI_80211_SUITE_SELECTOR *SuiteSelector)
{
    switch (SUITE_SELECTOR_GET(SuiteSelector)) {
    case RSN_CIPHER_SUITE_NONE:
        return WPA_CIPHER_NONE;
    case RSN_CIPHER_SUITE_TKIP:
        return WPA_CIPHER_TKIP;
    case RSN_CIPHER_SUITE_CCMP:
        return WPA_CIPHER_CCMP;
    case RSN_CIPHER_SUITE_AES_128_CMAC:
        return WPA_CIPHER_AES_128_CMAC;
    case RSN_CIPHER_SUITE_GCMP:
        return WPA_CIPHER_GCMP;
    case RSN_CIPHER_SUITE_CCMP_256:
        return WPA_CIPHER_CCMP_256;
    case RSN_CIPHER_SUITE_GCMP_256:
        return WPA_CIPHER_GCMP_256;
    case RSN_CIPHER_SUITE_BIP_GMAC_128:
        return WPA_CIPHER_BIP_GMAC_128;
    case RSN_CIPHER_SUITE_BIP_GMAC_256:
        return WPA_CIPHER_BIP_GMAC_256;
    case RSN_CIPHER_SUITE_BIP_CMAC_256:
        return WPA_CIPHER_BIP_CMAC_256;
    case RSN_CIPHER_SUITE_NO_GROUP_ADDRESSED:
        return WPA_CIPHER_GTK_NOT_USED;
    default:
        return 0;
    }
}

STATIC BOOLEAN SupplicantValidateGroupCipher(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    EFI_80211_CIPHER_SUITE_SELECTOR *CipherSuiteSelector;
    UINTN i;
    int WpaCiper;

    if (DataSize < sizeof(EFI_80211_CIPHER_SUITE_SELECTOR))
        return FALSE;

    CipherSuiteSelector = (EFI_80211_CIPHER_SUITE_SELECTOR *)Data;
    if (CipherSuiteSelector->CipherSuiteCount == 0)
        return TRUE;

    for (i = 0; i < CipherSuiteSelector->CipherSuiteCount; i++) {
        WpaCiper = CipherSuiteSelectorToWpaCipher(&CipherSuiteSelector->CipherSuiteList[i]);
        SUPP_DBG("Validate Group cipher suite 0x%x, wpa group cipher %d",
            SUITE_SELECTOR_GET(&CipherSuiteSelector->CipherSuiteList[i]), WpaCiper);
        switch (WpaCiper) {
        case WPA_CIPHER_CCMP:
        case WPA_CIPHER_TKIP:
        case WPA_CIPHER_AES_128_CMAC:
        case WPA_CIPHER_GCMP_256:
        case WPA_CIPHER_CCMP_256:
        case WPA_CIPHER_BIP_GMAC_128:
        case WPA_CIPHER_BIP_CMAC_256:
        case WPA_CIPHER_BIP_GMAC_256:
            break;
        default:
            return FALSE;
        }
    }

    return TRUE;
}

STATIC EFI_STATUS SupplicantSetGroupCipher(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    EFI_80211_CIPHER_SUITE_SELECTOR *GroupCipherSelector = (EFI_80211_CIPHER_SUITE_SELECTOR *)Data;
    struct wpas *wpas = &Instance->wpas;
    int WpaGroupCipher = CipherSuiteSelectorToWpaCipher(&GroupCipherSelector->CipherSuiteList[0]);

    SUPP_DBG("Configure Group cipher suite 0x%x, wpa group cipher %d",
        SUITE_SELECTOR_GET(&GroupCipherSelector->CipherSuiteList[0]), WpaGroupCipher);

    Instance->GroupCipher = WpaGroupCipher;
    wpas_set_group_cipher(wpas, WpaGroupCipher);

    return EFI_SUCCESS;
}

STATIC EFI_STATUS SupplicantSetPairwiseCipher(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    EFI_80211_CIPHER_SUITE_SELECTOR *PairwiseCipherSelector = (EFI_80211_CIPHER_SUITE_SELECTOR *)Data;
    struct wpas *wpas = &Instance->wpas;
    int WpaPairwiseCipher = CipherSuiteSelectorToWpaCipher(&PairwiseCipherSelector->CipherSuiteList[0]);

    SUPP_DBG("Configure pairwise cipher suite 0x%x, wpa pairwise cipher %d",
        SUITE_SELECTOR_GET(&PairwiseCipherSelector->CipherSuiteList[0]), WpaPairwiseCipher);

    Instance->PairwiseCipher = WpaPairwiseCipher;
    if (wpas_set_pairwise_cipher(wpas, WpaPairwiseCipher))
        return EFI_ABORTED;

    return EFI_SUCCESS;
}

STATIC BOOLEAN SupplicantValidateSupportedCipherSuites(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    EFI_80211_CIPHER_SUITE_SELECTOR *CipherSuiteSelector;
    UINTN CipherSuiteSelectorSize;

    if (DataSize < sizeof(EFI_80211_CIPHER_SUITE_SELECTOR)) {
        return FALSE;
    }

    CipherSuiteSelector = (EFI_80211_CIPHER_SUITE_SELECTOR *)Data;
    CipherSuiteSelectorSize = OFFSET_OF(EFI_80211_CIPHER_SUITE_SELECTOR, CipherSuiteList) +
        (sizeof(EFI_80211_SUITE_SELECTOR) * CipherSuiteSelector->CipherSuiteCount);

    if (DataSize != CipherSuiteSelectorSize) {
        return FALSE;
    }

    return TRUE;
}

STATIC EFI_STATUS SupportedCipherSuitesSet(
    IN OUT EFI_80211_CIPHER_SUITE_SELECTOR **CipherSuites,
    IN VOID *Data,
    IN UINTN DataSize)
{
    EFI_80211_CIPHER_SUITE_SELECTOR *NewSuites;

    NewSuites = AllocateZeroPool(DataSize);
    if (NewSuites == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    if (*CipherSuites) {
        FreePool(*CipherSuites);
    }

    CopyMem(NewSuites, Data, DataSize);
    *CipherSuites = NewSuites;

    return EFI_SUCCESS;
}

STATIC EFI_STATUS SupportedCipherSuitesGet(
    IN EFI_80211_CIPHER_SUITE_SELECTOR *CipherSuites,
    OUT VOID *Data,
    IN OUT UINTN *DataSize)
{
    UINTN CipherSuitesSize;

    if (CipherSuites == NULL) {
        return EFI_NOT_FOUND;
    }

    CipherSuitesSize = OFFSET_OF(EFI_80211_CIPHER_SUITE_SELECTOR, CipherSuiteList) +
        (sizeof(EFI_80211_SUITE_SELECTOR) * CipherSuites->CipherSuiteCount);

    if (*DataSize < CipherSuitesSize) {
        *DataSize = CipherSuitesSize;
        return EFI_BUFFER_TOO_SMALL;
    }

    CopyMem(Data, CipherSuites, CipherSuitesSize);
    *DataSize = CipherSuitesSize;

    return EFI_SUCCESS;
}

STATIC EFI_STATUS SupplicantSetSupportedSWCipherSuites(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    return SupportedCipherSuitesSet(&Instance->SupportedSWCipherSuites, Data, DataSize);
}

STATIC EFI_STATUS SupplicantGetSupportedSWCipherSuites(IN SUPPLICANT_INSTANCE *Instance,
    OUT VOID *Data,
    IN OUT UINTN *DataSize)
{
    return SupportedCipherSuitesGet(Instance->SupportedSWCipherSuites, Data, DataSize);
}

STATIC EFI_STATUS SupplicantSetSupportedHWCipherSuites(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    return SupportedCipherSuitesSet(&Instance->SupportedHWCipherSuites, Data, DataSize);
}

STATIC EFI_STATUS SupplicantGetSupportedHWCipherSuites(IN SUPPLICANT_INSTANCE *Instance,
    OUT VOID *Data,
    IN OUT UINTN *DataSize)
{
    return SupportedCipherSuitesGet(Instance->SupportedHWCipherSuites, Data, DataSize);
}

STATIC BOOLEAN SupplicantValidateTargetSSID(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    EFI_80211_SSID *SSId = (EFI_80211_SSID *)Data;

    if (DataSize != sizeof(EFI_80211_SSID)) {
        return FALSE;
    }

    if (SSId->SSIdLen > EFI_MAX_SSID_LEN ||
        SSId->SSIdLen == 0) {
        return FALSE;
    }

    return TRUE;
}

STATIC BOOLEAN SupplicantValidateTargetMac(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    return (DataSize == sizeof(EFI_80211_MAC_ADDRESS));
}

STATIC BOOLEAN SupplicantValidateLinkState(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    return (DataSize == sizeof(EFI_80211_LINK_STATE));
}

STATIC BOOLEAN SupplicantValidatePsk(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    return (DataSize != 0);
}

STATIC EFI_STATUS SupplicantSetPsk(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    wpas_set_passphrase(&Instance->wpas, Data);
    return EFI_SUCCESS;
}

STATIC EFI_STATUS SupplicantGetPtk(IN SUPPLICANT_INSTANCE *Instance,
    OUT VOID *Data,
    IN OUT UINTN *DataSize)
{
    if (*DataSize < sizeof(EFI_SUPPLICANT_KEY))
        return EFI_INVALID_PARAMETER;

    CopyMem(Data, &Instance->wpas.PtkSet, sizeof(EFI_SUPPLICANT_KEY));
    return EFI_SUCCESS;
}

STATIC EFI_STATUS SupplicantGetGtk(IN SUPPLICANT_INSTANCE *Instance,
    OUT VOID *Data,
    IN OUT UINTN *DataSize)
{
    if (*DataSize < sizeof(EFI_SUPPLICANT_GTK_LIST))
        return EFI_INVALID_PARAMETER;
	
    CopyMem(Data, &Instance->wpas.GtkSet, sizeof(EFI_SUPPLICANT_GTK_LIST));
    return EFI_SUCCESS;
}

STATIC EFI_STATUS SupplicantGetIGtk(IN SUPPLICANT_INSTANCE* Instance,
    OUT VOID* Data,
    IN OUT UINTN* DataSize)
{
    if (*DataSize < sizeof(EFI_SUPPLICANT_GTK_LIST))
        return EFI_INVALID_PARAMETER;

    CopyMem(Data, &Instance->wpas.IGtkSet, sizeof(EFI_SUPPLICANT_GTK_LIST));
    return EFI_SUCCESS;
}

STATIC EFI_STATUS SupplicantSetTargetSSID(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    EFI_80211_SSID *pSSID = (EFI_80211_SSID *)Data;

    SUPP_DBG("SSIdLen %d", pSSID->SSIdLen);

    wpas_set_ssid(&Instance->wpas, pSSID->SSId, pSSID->SSIdLen);
    return EFI_SUCCESS;
}

STATIC EFI_STATUS SupplicantOwnMacSet(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    wpas_set_own_addr(&Instance->wpas, Data);

    return EFI_SUCCESS;
}

STATIC EFI_STATUS SupplicantSetTargetMac(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    wpas_set_auth_addr(&Instance->wpas, Data);

    return EFI_SUCCESS;
}

STATIC VOID SupplicantNotifyAssoc(IN SUPPLICANT_INSTANCE* Instance)
{
    if (Instance->Mfp)
        wpas_update_mgmt_group_chiper(&Instance->wpas, Instance->SuiteType);
    else
        wpas_update_mgmt_group_chiper(&Instance->wpas, WPA_KEY_MGMT_NONE);

    wpas_notify_assoc(&Instance->wpas);
}

STATIC VOID SupplicantNotifyDisassoc(IN SUPPLICANT_INSTANCE* Instance)
{
    wpas_notify_disassoc(&Instance->wpas);
}

STATIC EFI_STATUS SupplicantSetLinkState(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    EFI_80211_LINK_STATE *pLinkState = (EFI_80211_LINK_STATE *)Data;
    EFI_80211_LINK_STATE PrevState = Instance->LinkState;

    Instance->LinkState = *pLinkState;

    SUPP_DBG("Setting link state: from Previous Link State %d to %d", PrevState, Instance->LinkState);

    if (PrevState < Ieee80211PendingRSNAuthentication &&
        Instance->LinkState == Ieee80211PendingRSNAuthentication) {
        SupplicantNotifyAssoc(Instance);
    }
    else if (PrevState >= Ieee80211PendingRSNAuthentication &&
        Instance->LinkState == Ieee80211UnauthenticatedUnassociated) {
        SupplicantNotifyDisassoc(Instance);
    }

    return EFI_SUCCESS;
}

EFI_STATUS SupplicantGetLinkState(IN SUPPLICANT_INSTANCE *Instance,
    OUT VOID *Data,
    IN OUT UINTN *DataSize)
{
    if (*DataSize < sizeof(Instance->LinkState)) {
        *DataSize = sizeof(Instance->LinkState);
        return EFI_BUFFER_TOO_SMALL;
    }
    CopyMem(Data, &Instance->LinkState, sizeof(Instance->LinkState));
    *DataSize = sizeof(Instance->LinkState);

    return EFI_SUCCESS;
}

EFI_STATUS SupplicantGetTargetSSIDMac(IN SUPPLICANT_INSTANCE *Instance,
    OUT VOID *Data,
    IN OUT UINTN *DataSize)
{
    if (*DataSize < sizeof(EFI_80211_MAC_ADDRESS)) {
        *DataSize = sizeof(EFI_80211_MAC_ADDRESS);
        return EFI_BUFFER_TOO_SMALL;
    }
	wpas_get_auth_addr(&Instance->wpas, Data);
    *DataSize = sizeof(EFI_80211_MAC_ADDRESS);

    return EFI_SUCCESS;
}

STATIC BOOLEAN SupplicantValidateMfp(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    UINT8 mfp;
	
	if (DataSize != 1) {
        return FALSE;
	}

    mfp = *(UINT8*)Data;
	if (mfp > 2) {
       return FALSE;
	}

    return TRUE;
}

STATIC EFI_STATUS SupplicantSetMfp(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
    Instance->Mfp = *(UINT8*)Data;

	wpas_set_mfp(&Instance->wpas, Instance->Mfp);
	
    return EFI_SUCCESS;
}

STATIC BOOLEAN SupplicantValidateRsnxe(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{	
	if (DataSize != 1) {
        return FALSE;
	}

    return TRUE;
}

STATIC EFI_STATUS SupplicantSetRsnxe(IN SUPPLICANT_INSTANCE *Instance,
    IN VOID *Data,
    IN UINTN DataSize)
{
	UINT8 RsnxeCap = *(UINT8*)Data;;
	wpas_set_rsn_extcap(&Instance->wpas, RsnxeCap);
		
    return EFI_SUCCESS;
}

STATIC VOID SupplicantWpaComplete(VOID *Ctx, int success)
{
    SUPPLICANT_INSTANCE *Instance = (SUPPLICANT_INSTANCE *)Ctx;
    EFI_80211_LINK_STATE LinkState;

    LinkState = success ? Ieee80211AuthenticatedAssociated :
        Ieee80211AuthenticatedUnassociated;

    SUPP_DBG("Setting link state from WPA completion");
    SupplicantSetLinkState(Instance, (VOID *)&LinkState, sizeof(LinkState));
}

STATIC VOID SupplicantEapolComplete(VOID *Ctx, int success)
{
    SUPPLICANT_INSTANCE *Instance = (SUPPLICANT_INSTANCE *)Ctx;

    if (success) {
        Instance->IsOneXCompleted = 1;
        SUPP_DBG("IsOneXCompleted %d", Instance->IsOneXCompleted);
    }
    else {
        EFI_80211_LINK_STATE LinkState = Ieee80211AuthenticatedUnassociated;
        SUPP_DBG("EAPOL fail, Set link state to Ieee80211AuthenticatedUnassociated");
        SupplicantSetLinkState(Instance, (VOID *)&LinkState, sizeof(LinkState));
    }
}

STATIC VOID SupplicantSaeComplete(VOID* Ctx, int success)
{
    SUPPLICANT_INSTANCE* Instance = (SUPPLICANT_INSTANCE*)Ctx;
    EFI_80211_LINK_STATE LinkState;

    LinkState = success ? Ieee80211AuthenticatedUnassociated :
        Ieee80211UnauthenticatedUnassociated;

    SUPP_DBG("Setting link state from SAE completion");
    SupplicantSetLinkState(Instance, (VOID*)&LinkState, sizeof(LinkState));

}

#if SUPPORT_DEBUG_PRINT

STATIC CONST CHAR8 *SupplicantDataTypeToString(EFI_SUPPLICANT_DATA_TYPE DataType)
{
    STATIC CONST CHAR8 *SuppDataTypes[] = {
        [EfiSupplicant80211AKMSuite] = "AKMSuite",
        [EfiSupplicant80211GroupDataCipherSuite] = "GroupCipherSuite",
        [EfiSupplicant80211PairwiseCipherSuite] = "PairwiseCipherSuite",
        [EfiSupplicant80211PskPassword] = "PskPassword",
        [EfiSupplicant80211TargetSSIDName] = "TargetSSIDName",
        [EfiSupplicant80211StationMac] = "StationMac",
        [EfiSupplicant80211TargetSSIDMac] = "TargetSSIDMac",
        [EfiSupplicant80211PTK] = "PTK",
        [EfiSupplicant80211GTK] = "GTK",
        [EfiSupplicantState] = "State",
        [EfiSupplicant80211LinkState] = "LinkState",
        [EfiSupplicantKeyRefresh] = "KeyRefresh",
        [EfiSupplicant80211SupportedAKMSuites] = "SupportedAKMSuites",
        [EfiSupplicant80211SupportedSoftwareCipherSuites] = "SupportedSWCipherSuites",
        [EfiSupplicant80211SupportedHardwareCipherSuites] = "SupportedHWCipherSuites",
        [EfiSupplicant80211IGTK] = "IGTK",
        [EfiSupplicant80211PMK] = "PMK",
        [EfiSupplicantDataTypeMaximum] = "InvalidType",
        [EfiSupplicant80211UserMfp] = "MFP",
		[EfiSupplicant80211RsnxeCapability] = "RsnxeCapability",
    };

    if (DataType >= ARRAY_SIZE(SuppDataTypes))
        return NULL;

    return SuppDataTypes[DataType];
}

#endif

/* Helpers */
STATIC BOOLEAN SupplicantIsEapolRequired(IN SUPPLICANT_INSTANCE *Instance)
{
    // Only Enterprise Suite Type require EAPOL
    if (Instance->SuiteType == WPA_KEY_MGMT_IEEE8021X ||
        Instance->SuiteType == WPA_KEY_MGMT_IEEE8021X_SUITE_B ||
        Instance->SuiteType == WPA_KEY_MGMT_IEEE8021X_SUITE_B_192) {
        return Instance->IsOneXCompleted ? FALSE : TRUE;
    }

    return FALSE;
}

STATIC VOID SupplicantConfigureCapabilities(IN SUPPLICANT_INSTANCE *Instance)
{
    STATIC CONST EFI_80211_SUITE_SELECTOR SUPPORTED_AKM_SUITE_LIST[] = {
        { { 0x00, 0x0F, 0xAC }, 1 },   /* 8021X */
        { { 0x00, 0x0F, 0xAC }, 2 },   /* PSK */
        { { 0x00, 0x0F, 0xAC }, 5 },   /* 8021X_SHA256 */
        { { 0x00, 0x0F, 0xAC }, 6 },   /* PSK_SHA256 */
#ifdef CONFIG_SAE
        { { 0x00, 0x0F, 0xAC }, 8 },   /* SAE */
#endif // !CONFIG_SAE
#ifndef CONFIG_TLS_INTERNAL
        { { 0x00, 0x0F, 0xAC }, 11 },  /* SUITE_B */
        { { 0x00, 0x0F, 0xAC }, 12 },  /* SUITE_B_192 */
#endif // !CONFIG_TLS_INTERNAL
    };

    // Construct supported akm suites
    struct {
        UINT16 AKMSuiteCount;
        EFI_80211_SUITE_SELECTOR AKMSuiteList[ARRAY_SIZE(SUPPORTED_AKM_SUITE_LIST)];
    } SupportedAkmSuites;

    SupportedAkmSuites.AKMSuiteCount = ARRAY_SIZE(SUPPORTED_AKM_SUITE_LIST);
    CopyMem(SupportedAkmSuites.AKMSuiteList, SUPPORTED_AKM_SUITE_LIST, sizeof(SUPPORTED_AKM_SUITE_LIST));

    BUILD_BUG_ON((OFFSET_OF(EFI_80211_AKM_SUITE_SELECTOR, AKMSuiteList) + sizeof(EFI_80211_SUITE_SELECTOR) * ARRAY_SIZE(SUPPORTED_AKM_SUITE_LIST)) != sizeof(SupportedAkmSuites));

    SupplicantSupportedAKMSet(Instance, &SupportedAkmSuites, sizeof(SupportedAkmSuites));
}

EFI_STATUS
EFIAPI
SupplicantBuildResponsePacket(
    IN EFI_SUPPLICANT_PROTOCOL              *This,
    IN UINT8                                *RequestBuffer, OPTIONAL
    IN UINTN                                RequestBufferSize, OPTIONAL
    OUT UINT8                               *Buffer,
    IN OUT UINTN                            *BufferSize
)
{
    SUPPLICANT_INSTANCE *Instance;
	int state = 0;

    if ((Buffer == NULL) || (BufferSize == NULL) || (*BufferSize == 0))
        return EFI_INVALID_PARAMETER;

    Instance = SUPPLICANT_INSTANCE_FROM_SUPP_PROTO(This);

    // For Ent-case, first run eapol-sm and then continue the wpa-sm.
    if (!Instance->SaeAkm || 
        (Instance->LinkState >= Ieee80211PendingRSNAuthentication)) {
        if (SupplicantIsEapolRequired(Instance)) {
            wpas_rx_eapol(&Instance->wpas, RequestBuffer, RequestBufferSize, Buffer,
                (size_t*)BufferSize);
        }
        else {
            wpas_rx_wpa(&Instance->wpas, RequestBuffer, RequestBufferSize, Buffer,
                (size_t*)BufferSize);
        }
    }
    else {
        state = wpas_rx_sae(&Instance->wpas, RequestBuffer, RequestBufferSize, Buffer,
            (size_t*)BufferSize);
        if (state != WLAN_STATUS_SUCCESS) {
            DbgError("wpas_rx_sae state: %d\n", state);
        }
    }
    
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
SupplicantProcessPacket(
    IN EFI_SUPPLICANT_PROTOCOL              *This,
    IN OUT EFI_SUPPLICANT_FRAGMENT_DATA     **FragmentTable,
    IN UINT32                               *FragmentCount,
    IN EFI_SUPPLICANT_CRYPT_MODE            CryptMode
)
{
    return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
SupplicantSetData(
    IN EFI_SUPPLICANT_PROTOCOL              *This,
    IN EFI_SUPPLICANT_DATA_TYPE             DataType,
    IN VOID                                 *Data,
    IN UINTN                                DataSize
)
{
    typedef struct _SUPP_DATA_OPS {
        BOOLEAN(*ValidateData)(SUPPLICANT_INSTANCE *Instance, VOID *Data, UINTN DataSize);
        EFI_STATUS(*SetData)(SUPPLICANT_INSTANCE *Instance, VOID *Data, UINTN DataSize);
    } SUPP_DATA_OPS;

    STATIC CONST SUPP_DATA_OPS SuppSetDataOpsTable[] = {
        [EfiSupplicant80211AKMSuite] = { SupplicantValidateAKM, SupplicantSetAKM },
        [EfiSupplicant80211GroupDataCipherSuite] = { SupplicantValidateGroupCipher, SupplicantSetGroupCipher },
        [EfiSupplicant80211PairwiseCipherSuite] = { SupplicantValidateGroupCipher, SupplicantSetPairwiseCipher },
        [EfiSupplicant80211PskPassword] = { SupplicantValidatePsk, SupplicantSetPsk },
        [EfiSupplicant80211TargetSSIDName] = { SupplicantValidateTargetSSID, SupplicantSetTargetSSID },
        [EfiSupplicant80211StationMac] = { SupplicantValidateTargetMac, SupplicantOwnMacSet },
        [EfiSupplicant80211TargetSSIDMac] = { SupplicantValidateTargetMac, SupplicantSetTargetMac },
        [EfiSupplicant80211LinkState] = { SupplicantValidateLinkState, SupplicantSetLinkState },
        [EfiSupplicant80211SupportedAKMSuites] = { SupplicantSupportedAKMValidate, SupplicantSupportedAKMSet },
        [EfiSupplicant80211SupportedSoftwareCipherSuites] = { SupplicantValidateSupportedCipherSuites, SupplicantSetSupportedSWCipherSuites },
        [EfiSupplicant80211SupportedHardwareCipherSuites] = { SupplicantValidateSupportedCipherSuites, SupplicantSetSupportedHWCipherSuites },
        [EfiSupplicant80211UserMfp] = { SupplicantValidateMfp, SupplicantSetMfp },
        [EfiSupplicant80211RsnxeCapability] = { SupplicantValidateRsnxe, SupplicantSetRsnxe },
    };

    SUPPLICANT_INSTANCE *Instance;
    CONST SUPP_DATA_OPS *SuppDataOps;

    if ((Data == NULL) || (DataSize == 0)) {
        return EFI_INVALID_PARAMETER;
    }

    SUPP_DBG("DataType=%a, Data=0x%p, DataSize=%d",
        SupplicantDataTypeToString(DataType), Data, DataSize);

    if (DataType >= ARRAY_SIZE(SuppSetDataOpsTable)) {
        return EFI_UNSUPPORTED;
    }

    Instance = SUPPLICANT_INSTANCE_FROM_SUPP_PROTO(This);

    SuppDataOps = &SuppSetDataOpsTable[DataType];
    if (SuppDataOps->ValidateData &&
        !SuppDataOps->ValidateData(Instance, Data, DataSize)) {
        return EFI_INVALID_PARAMETER;
    }

    if (SuppDataOps->SetData) {
        return SuppDataOps->SetData(Instance, Data, DataSize);
    }

    return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
SupplicantGetData(
    IN EFI_SUPPLICANT_PROTOCOL              *This,
    IN EFI_SUPPLICANT_DATA_TYPE             DataType,
    OUT UINT8                               *Data,
    IN OUT UINTN                            *DataSize
)
{
    typedef EFI_STATUS(*SUPP_GET_DATA)(SUPPLICANT_INSTANCE *Instance, VOID *Data, OUT UINTN *DataSize);

    STATIC CONST SUPP_GET_DATA SuppGetDataOpTable[] = {
        [EfiSupplicant80211PTK] = SupplicantGetPtk,
        [EfiSupplicant80211GTK] = SupplicantGetGtk,
        [EfiSupplicant80211IGTK] = SupplicantGetIGtk,
        [EfiSupplicant80211LinkState] = SupplicantGetLinkState,
        [EfiSupplicant80211TargetSSIDMac] = SupplicantGetTargetSSIDMac,
        [EfiSupplicant80211SupportedAKMSuites] = SupplicantSupportedAKMGet,
        [EfiSupplicant80211SupportedSoftwareCipherSuites] = SupplicantGetSupportedSWCipherSuites,
        [EfiSupplicant80211SupportedHardwareCipherSuites] = SupplicantGetSupportedHWCipherSuites,
    };

    SUPPLICANT_INSTANCE *Instance;
    SUPP_GET_DATA SuppGetData;

    if (DataSize == NULL)
        return EFI_INVALID_PARAMETER;

    SUPP_DBG("DataType=%a, Data=0x%p, DataSize=%d",
        SupplicantDataTypeToString(DataType), Data, DataSize);

    if (DataType >= ARRAY_SIZE(SuppGetDataOpTable)) {
        return EFI_UNSUPPORTED;
    }

    Instance = SUPPLICANT_INSTANCE_FROM_SUPP_PROTO(This);

    SuppGetData = SuppGetDataOpTable[DataType];
    if (SuppGetData) {
        return SuppGetData(Instance, Data, DataSize);
    }

    return EFI_UNSUPPORTED;
}

// EAP_CONFIGURATION_PROTOCOL

STATIC CONST EFI_EAP_TYPE EapCfgSupportedMethods[] = {
    EFI_EAP_TYPE_TTLS,
    EFI_EAP_TYPE_PEAP,
    EFI_EAP_TYPE_EAPTLS
};

STATIC
EFI_STATUS
EapCfgGetSupportedAuthMethods(
    IN SUPPLICANT_INSTANCE *Instance,
    IN EFI_EAP_TYPE EapType,
    OUT VOID *Data,
    IN OUT UINTN *DataSize
)
{
    if (EapType != EFI_EAP_TYPE_ATTRIBUTE) {
        return EFI_UNSUPPORTED;
    }

    if (!Data || *DataSize < sizeof(EapCfgSupportedMethods)) {
        *DataSize = sizeof(EapCfgSupportedMethods);
        return EFI_BUFFER_TOO_SMALL;
    }

    *DataSize = sizeof(EapCfgSupportedMethods);
    CopyMem(Data, EapCfgSupportedMethods, *DataSize);
    return EFI_SUCCESS;
}

STATIC
EFI_STATUS
EapCfgSetIdentity(
    IN SUPPLICANT_INSTANCE *Instance,
    IN EFI_EAP_TYPE EapType,
    IN VOID *Data,
    IN UINTN DataSize
)
{
    if (EapType != EFI_EAP_TYPE_IDENTITY) {
        return EFI_UNSUPPORTED;
    }

    wpas_set_eap_identity(&Instance->wpas, (u8 *)Data, (size_t)DataSize);
    return EFI_SUCCESS;
}

STATIC
EFI_STATUS
EapCfgSetPrivateKeyPassword(
    IN SUPPLICANT_INSTANCE *Instance,
    IN EFI_EAP_TYPE EapType,
    IN VOID *Data,
    IN UINTN DataSize
)
{
    if (EapType == EFI_EAP_TYPE_ATTRIBUTE ||
        EapType != Instance->wpas.phase1_method) {
        return EFI_UNSUPPORTED;
    }

    wpas_set_eap_priv_key_password(&Instance->wpas, (u8 *)Data, (size_t)DataSize);
    return EFI_SUCCESS;
}

STATIC
EFI_STATUS
EapCfgSetCaCert(
    IN SUPPLICANT_INSTANCE *Instance,
    IN EFI_EAP_TYPE EapType,
    IN VOID *Data,
    IN UINTN DataSize
)
{
    if (EapType == EFI_EAP_TYPE_ATTRIBUTE ||
        EapType != Instance->wpas.phase1_method) {
        return EFI_UNSUPPORTED;
    }

    wpas_set_eap_blob(&Instance->wpas, (u8 *)Data, (size_t)DataSize,
        &Instance->wpas.ca_cert_blob);
    return EFI_SUCCESS;
}

STATIC
EFI_STATUS
EapCfgSetClientCert(
    IN SUPPLICANT_INSTANCE *Instance,
    IN EFI_EAP_TYPE EapType,
    IN VOID *Data,
    IN UINTN DataSize
)
{
    if (EapType == EFI_EAP_TYPE_ATTRIBUTE ||
        EapType != Instance->wpas.phase1_method) {
        return EFI_UNSUPPORTED;
    }

    wpas_set_eap_blob(&Instance->wpas, (u8 *)Data, (size_t)DataSize,
        &Instance->wpas.client_cert_blob);
    return EFI_SUCCESS;
}

STATIC
EFI_STATUS
EapCfgSetPrivateKeyFile(
    IN SUPPLICANT_INSTANCE *Instance,
    IN EFI_EAP_TYPE EapType,
    IN VOID *Data,
    IN UINTN DataSize
)
{
    if (EapType == EFI_EAP_TYPE_ATTRIBUTE ||
        EapType != Instance->wpas.phase1_method) {
        return EFI_UNSUPPORTED;
    }

    wpas_set_eap_blob(&Instance->wpas, (u8 *)Data, (size_t)DataSize,
        &Instance->wpas.priv_key_blob);
    return EFI_SUCCESS;
}

STATIC
EFI_STATUS
EapCfgSetAuthMethod(
    IN SUPPLICANT_INSTANCE *Instance,
    IN EFI_EAP_TYPE EapType,
    IN VOID *Data,
    IN UINTN DataSize
)
{
    EFI_EAP_TYPE Method;
    int i;

    if (EapType != EFI_EAP_TYPE_ATTRIBUTE) {
        return EFI_UNSUPPORTED;
    }

    if (DataSize < sizeof(Method)) {
        return EFI_BUFFER_TOO_SMALL;
    }

    Method = *(EFI_EAP_TYPE *)Data;
    for (i = 0; i < ARRAY_SIZE(EapCfgSupportedMethods); i++)
        if (EapCfgSupportedMethods[i] == Method)
            break;

    if (i == ARRAY_SIZE(EapCfgSupportedMethods)) {
        return EFI_UNSUPPORTED;
    }

    wpas_set_phase1_eap_method(&Instance->wpas, Method);
    return EFI_SUCCESS;
}

STATIC
EFI_STATUS
EapCfgSetSecondAuthMethod(
    IN SUPPLICANT_INSTANCE *Instance,
    IN EFI_EAP_TYPE EapType,
    IN VOID *Data,
    IN UINTN DataSize
)
{
    EFI_EAP_TYPE Method;

    if (EapType == EFI_EAP_TYPE_ATTRIBUTE || EapType != Instance->wpas.phase1_method) {
        return EFI_UNSUPPORTED;
    }

    if (DataSize < sizeof(Method)) {
        return EFI_BUFFER_TOO_SMALL;
    }

    Method = *(EFI_EAP_TYPE *)Data;
    if (Method != EFI_EAP_TYPE_MSCHAPV2) {
        return EFI_UNSUPPORTED;
    }

    wpas_set_phase2_eap_method(&Instance->wpas, Method);
    return EFI_SUCCESS;
}

STATIC
EFI_STATUS
EapCfgSetPassword(
    IN SUPPLICANT_INSTANCE *Instance,
    IN EFI_EAP_TYPE EapType,
    IN VOID *Data,
    IN UINTN DataSize
)
{
    CHAR16 *Pwd;
    size_t PwdLen = DataSize / 2;

    if (EapType != EFI_EAP_TYPE_MSCHAPV2) {
        return EFI_UNSUPPORTED;
    }

    if (DataSize == 0) {
        return EFI_INVALID_PARAMETER;
    }

    Pwd = (CHAR16 *)Data;
    if (Pwd[PwdLen - 1] == L'\0')
        PwdLen -= 1;

    wpas_set_eap_pwd(&Instance->wpas, (u8 *)Pwd, PwdLen * 2);
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EapCfgGetData(
    IN EFI_EAP_CONFIGURATION_PROTOCOL       *This,
    IN EFI_EAP_TYPE                         EapType,
    IN EFI_EAP_CONFIG_DATA_TYPE             DataType,
    IN OUT VOID                             *Data,
    IN OUT UINTN                            *DataSize
)
{
    typedef EFI_STATUS(*EAP_CFG_GET_DATA)(
        SUPPLICANT_INSTANCE *Instance, 
        EFI_EAP_TYPE EapType,
        VOID *Data, UINTN *DataSize);

    STATIC CONST EAP_CFG_GET_DATA CfgGetDataTable[] = {
		[EfiEapConfigEapAuthMethod]          = NULL,
        [EfiEapConfigEapSupportedAuthMethod] = EapCfgGetSupportedAuthMethods,
    };

    SUPPLICANT_INSTANCE *Instance;
    EAP_CFG_GET_DATA EapCfgGetData;

    if ((DataSize == NULL) || ((Data == NULL) && (*DataSize != 0))) {
        return EFI_INVALID_PARAMETER;
    }

    if ((UINTN)DataType >= ARRAY_SIZE(CfgGetDataTable)) {
        return EFI_UNSUPPORTED;
    }

    Instance = SUPPLICANT_INSTANCE_FROM_EAP_PROTO(This);

    EapCfgGetData = CfgGetDataTable[DataType];
    if (EapCfgGetData) {
        return EapCfgGetData(Instance, EapType, Data, DataSize);
    }

    return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
EapCfgSetData(
    IN EFI_EAP_CONFIGURATION_PROTOCOL       *This,
    IN EFI_EAP_TYPE                         EapType,
    IN EFI_EAP_CONFIG_DATA_TYPE             DataType,
    IN VOID                                 *Data,
    IN UINTN                                DataSize
)
{
    typedef EFI_STATUS(*EAP_CFG_SET_DATA)(
        SUPPLICANT_INSTANCE *Instance, EFI_EAP_TYPE EapType, 
        VOID *Data, UINTN DataSize);

    STATIC CONST EAP_CFG_SET_DATA CfgSetDataTable[] = {
        [EfiEapConfigEapAuthMethod] = EapCfgSetAuthMethod,
        [EfiEapConfigIdentityString] = EapCfgSetIdentity,
        [EfiEapConfigEapTlsCACert] = EapCfgSetCaCert,
        [EfiEapConfigEapTlsClientCert] = EapCfgSetClientCert,
        [EfiEapConfigEapTlsClientPrivateKeyFile] = EapCfgSetPrivateKeyFile,
        [EfiEapConfigEapTlsClientPrivateKeyFilePassword] = EapCfgSetPrivateKeyPassword,
        [EfiEapConfigEapTlsCipherSuite]  = NULL,
  		[EfiEapConfigEapTlsSupportedCipherSuite] = NULL,
        [EfiEapConfigEapMSChapV2Password] = EapCfgSetPassword,
        [EfiEapConfigEap2ndAuthMethod] = EapCfgSetSecondAuthMethod,
    };

    SUPPLICANT_INSTANCE *Instance;
    EAP_CFG_SET_DATA EapCfgSetData;

    if ((Data == NULL) || (DataSize == 0)) {
        return EFI_INVALID_PARAMETER;
    }

    if ((UINTN)DataType >= ARRAY_SIZE(CfgSetDataTable)) {
        return EFI_UNSUPPORTED;
    }

    Instance = SUPPLICANT_INSTANCE_FROM_EAP_PROTO(This);

    EapCfgSetData = CfgSetDataTable[DataType];
    if (EapCfgSetData) {
        return EapCfgSetData(Instance, EapType, Data, DataSize);
    }

    return EFI_UNSUPPORTED;
}

// Supplicant Instance initialize/deinitialize

EFI_STATUS
SupplicantServiceInitInstance(
    IN  SUPPLICANT_SERVICE   *SupplicantService,
    OUT SUPPLICANT_INSTANCE  *Instance
)
{
    Instance->Signature = SUPPLICANT_INSTANCE_SIGNATURE;
    Instance->SupplicantService = SupplicantService;

    // Initialize the Supplicant Protocol.
    Instance->SupplicantProtocol.BuildResponsePacket = SupplicantBuildResponsePacket;
    Instance->SupplicantProtocol.ProcessPacket = SupplicantProcessPacket;
    Instance->SupplicantProtocol.SetData = SupplicantSetData;
    Instance->SupplicantProtocol.GetData = SupplicantGetData;

    // Initialize the EapConfigurationProtocol
    Instance->EapCfgProtocol.SetData = EapCfgSetData;
    Instance->EapCfgProtocol.GetData = EapCfgGetData;

    // wpa supplicant initialize
    Instance->wpa_cbs.wpa_complete = SupplicantWpaComplete;
    Instance->wpa_cbs.eapol_complete = SupplicantEapolComplete;
    Instance->wpa_cbs.sae_complete = SupplicantSaeComplete;
    if (wpas_init(&Instance->wpas, &Instance->wpa_cbs, Instance) != 0)
        return EFI_DEVICE_ERROR;

    // Configure the capabilities
    SupplicantConfigureCapabilities(Instance);

    return EFI_SUCCESS;
}

VOID
SupplicantServiceDeinitInstance(
    IN  SUPPLICANT_SERVICE   *SupplicantService,
    OUT SUPPLICANT_INSTANCE  *Instance
)
{
    wpas_deinit(&Instance->wpas);

    if (Instance->SupportedHWCipherSuites) {
        FreePool(Instance->SupportedHWCipherSuites);
        Instance->SupportedHWCipherSuites = NULL;
    }
    if (Instance->SupportedSWCipherSuites) {
        FreePool(Instance->SupportedSWCipherSuites);
        Instance->SupportedSWCipherSuites = NULL;
    }
    if (Instance->SupportedAKMSuites) {
        FreePool(Instance->SupportedAKMSuites);
        Instance->SupportedAKMSuites = NULL;
    }
}
