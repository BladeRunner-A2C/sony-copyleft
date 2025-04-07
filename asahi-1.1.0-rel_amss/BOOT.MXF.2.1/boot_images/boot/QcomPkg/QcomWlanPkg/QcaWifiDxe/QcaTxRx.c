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
 19/8/21   zxue     fix KW issue
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <net/net80211.h>
#include "QcaTxRx.h"


STATIC inline BOOLEAN
IsEapolFrame(UINT8 *llc)
{
    CONST STATIC UINT8 EAPOL_SNAP[2] = { 0x88, 0x8e };
    UINT8 i;
    ASSERT(llc);
    for (i = 0; i < sizeof(EAPOL_SNAP); i++) {
        if (llc[i] != EAPOL_SNAP[i]) {
            return FALSE;
        }
    }

    return TRUE;
}

STATIC inline
BOOLEAN
QcWlanRxFrame(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN ETHER_HEAD *Hdr,
    IN UINTN Len,
    OUT UINT8 *OutBuffer,
    OUT UINTN *BufferSize
)
{
	CopyMem(OutBuffer, Hdr, Len);
	*BufferSize = Len;

	return TRUE;
}

BOOLEAN QcWlanProcessRxPacket(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev, 
    IN struct sk_buff *skb, 
    OUT VOID* OutBuffer, 
    OUT UINTN *BufferSize
)
{
	UINTN Len = skb->len;
	ETHER_HEAD *Hdr = (ETHER_HEAD *)skb->data;
	UINT8 *llc = (UINT8 *)Hdr + sizeof(ETHER_HEAD) - 2;

	if (Len < ETH_HLEN) {
		DbgError("Frame 0x%p is too short: %d\n", skb, Len);
		return FALSE;
	}

    if (IsEapolFrame(llc)) {
        QcWlanRxEapol(Dev, skb);
		return FALSE;
	}

    DbgTxRxInfo("Returns skb 0x%p(%d) to up layer\n", skb, Len);

	return QcWlanRxFrame(Dev, Hdr, Len, OutBuffer, BufferSize);
}

EFI_STATUS
QcWlanTxPacket(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev, 
    IN struct sk_buff *skb
)
{
    NET80211_CONTEXT *Context = &Dev->WiFi;

    // start transmit a pkt
    net80211_transmit_pkt(Context->NetDev, Context->NetIf, skb);

    return EFI_SUCCESS;
}

EFI_STATUS
QcWlanTxEapol(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN struct sk_buff *skb
)
{
    EFI_STATUS Status;

    // The packet start with an ethernet header
	if (skb->len < ETH_HLEN) {
		DbgError("Bad eapol frame: %d\n", skb->len);
		return EFI_BUFFER_TOO_SMALL;
	}

	DbgDump("TX EAPOL Data: ", skb->data, skb->len, 256);

	Status = QcWlanTxPacket(Dev, skb);
	if (Status != EFI_SUCCESS) {
		DbgError("Failed to transmit eapol frame: %r\n", Status);
	} else {
        DbgInfo("Transmit eapol frame successfully\n");
	}

	return Status;
}

#define EAPOL_TYPE_KEY               0x3
#define EAPOL_M_MASK                 0x8813

STATIC UINT16
QcWlanGetEapolKeyAction(UINT8 *Data, UINT32 Len)
{
    STATIC CONST struct {
        UINT16 Mask;
        CONST CHAR8 *Name;
        UINT8 Action;
    } EapolKeyInfoTypes[] = {
        { 0x8800, "M1", QCWLAN_EAPOL_KEY_ALL },
        { 0x0801, "M2", QCWLAN_EAPOL_KEY_NONE },
        { 0x8813, "M3", QCWLAN_EAPOL_KEY_NONE},
        { 0x0803, "M4", QCWLAN_EAPOL_KEY_NONE },
        { 0x8013, "G1", QCWLAN_EAPOL_KEY_GROUP},
    };
    UINT16 KeyInfo;
    UINT8 Type;
    CONST CHAR8 *KeyName = "Unknown eapol message";
    UINT16 KeyAction = QCWLAN_EAPOL_KEY_NONE;
    UINT16 i;

    if (Len < 7) {
        DbgError("Not a EAPOL Key packet (Len %d)\n", Len);
        return FALSE;
    }

    Type = Data[1];
    if (Type != EAPOL_TYPE_KEY) {
        DbgError("Not a EAPOL Key packet (Type %d)\n", Type);
        return FALSE;
    }

    KeyInfo = (Data[5] | ((UINT16)Data[6]) << 8) & EAPOL_M_MASK;
    for (i = 0; i < ARRAY_SIZE(EapolKeyInfoTypes); i++) {
        if (EapolKeyInfoTypes[i].Mask != KeyInfo)
            continue;
        KeyAction = EapolKeyInfoTypes[i].Action;
        KeyName = EapolKeyInfoTypes[i].Name;
    }

    DEBUG_PARAMETER(KeyName);
    DbgError("EAPOL %a: %d\n", KeyName, KeyAction);

    return KeyAction;
}

VOID
QcWlanRxEapol(
    IN EFI_QCWLAN_DEVICE_CONTEXT *Dev,
    IN struct sk_buff *skb
)
{
	EFI_STATUS Status;
    struct sk_buff *skb_eapol;
	UINTN RespSize = 1500;
    
	if (skb) {
        Dev->EapolTimeoutRetries = 0;

        DbgDump("RX EAPOL Data: ", skb->data, skb->len, 256);
        /* skip the ethernet header */
        skb_pull(skb, ETH_HLEN);
	}

	if (!Dev->WantEapol) {
		DbgError("!WantEapol - Dropping\n");
		Status = EFI_SUCCESS;
		goto End;
	}

    if (!Dev->PendingEapolConnect) {
        Status = EFI_NOT_STARTED;
        if (Dev->Snm.MediaPresent) {
			UINT16 KeyAction;
			if (skb == NULL)
                return;
			
            KeyAction = QcWlanGetEapolKeyAction(skb->data, skb->len);
            if (KeyAction) {
                DbgError("Reauthorize 802.1X connection\n");
                QcWlanSetSupplicantState(Dev, Ieee80211PendingRSNAuthentication);
                Status = QcWlanSetupEapolSm(Dev, KeyAction);
                if (EFI_ERROR(Status)) {
                    DbgError("Failed to setup eapol state machine: %r\n", Status);
                }
                DbgInfo("Waiting for supplicant to authorize 802.1X connection\n");
            }
        }

        if (EFI_ERROR(Status)) {
            DbgError("Wrong eapol status - Dropping\n");
            Status = EFI_SUCCESS;
            goto End;
        }
    }

    skb_eapol = sk_buff_pool_alloc_skb(&Dev->tx_skb_pool, 4 /* alignment */);
    if (!skb_eapol) {
        DbgError("Unable to allocate EAPOL skb\n");
        Status = EFI_SUCCESS;
        goto End;
    }

	Status = Dev->SupplicantProtocol->BuildResponsePacket(
        Dev->SupplicantProtocol,
        skb ? skb->data : NULL,
        skb ? skb->len : 0,
        skb_eapol->data,
        &RespSize);

	if (Status != EFI_SUCCESS) {
		DbgError("BuildResponsePacket: %r\n", Status);
        kfree_skb(skb_eapol);
		goto End;
	}

    DbgInfo("BuildResponsePacket Size: %d\n", RespSize);

	if (RespSize > 0) {
        skb_put(skb_eapol, (u32)RespSize);
		Status = QcWlanTxEapol(Dev, skb_eapol);
		if (Status != EFI_SUCCESS) {
            kfree_skb(skb_eapol);
			DbgError("TX Eapol: %r\n", Status);
		  	goto End;
		}
	}

    Status = QcWlanHandleSupplicantState(Dev);

End:
	if (Status != EFI_SUCCESS) {
		DbgError("Failed to process eapol: %r\n", Status);

		// Stop EAPOLs state machine, which can lead to more
		// disconnects
        QcWlanCleanupEapolSm(Dev);
		QcWlanDisconnect(Dev, NULL);
	}
}

