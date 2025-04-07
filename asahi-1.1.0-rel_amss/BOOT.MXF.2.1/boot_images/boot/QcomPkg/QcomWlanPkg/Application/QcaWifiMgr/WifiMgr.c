/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "WifiMgr.h"
#include "../Include/QcaWifi.h"
#include "../../Include/WlanDeviceType.h"
// Globals

EFI_EVENT gNotifyWaitEvent = NULL;
EFI_EVENT gTokenSignalEvent = NULL;

EFI_LOADED_IMAGE_PROTOCOL* gImageProtocol;

QCA_WIFI_MGR_ACTION WifiMgrAction[] =
{
    {ACTION_LINK_STATE,   L"link_state"},
	{ACTION_LINK_ADDRESS, L"link_address"},
    {ACTION_SCAN,         L"scan"},
    {ACTION_CONNECT,      L"connect"},
    {ACTION_CONNECT_ONEX, L"1xconnect"},
    {ACTION_DISCONNECT,   L"disconnect"},
    {ACTION_RSSI,         L"test_rssi"},
    {ACTION_LOG_LEVEL,    L"log_level"},
    {ACTION_INVALID,      L"Unknown"},
};

static
EFI_STATUS
ReadFileFromVolume(
    IN CHAR16 *FileName,
    OUT VOID **Buffer,
    OUT UINTN *Size
)
{
    EFI_STATUS                      Status = EFI_SUCCESS;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *Volume =NULL;
    EFI_FILE_PROTOCOL               *Root = NULL;
    EFI_FILE_PROTOCOL               *File = NULL;
    EFI_FILE_INFO                   *FileInfo = NULL;
    UINTN                           InfoSize = 0;

    Status = gBS->HandleProtocol(
        gImageProtocol->DeviceHandle,
        &gEfiSimpleFileSystemProtocolGuid,
        (VOID **)&Volume
    );
    if (Status != EFI_SUCCESS) {
        DbgError(L"Open SimpleFileSystemProtocol failed: %r", Status);
        goto Out;
    }

    Status = Volume->OpenVolume(Volume, &Root);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Open volume failed: %r", Status);
        goto Out;
    }

    Status = Root->Open(Root, &File, FileName, EFI_FILE_MODE_READ, 0);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Open file (%s) failed: %r", FileName, Status);
        goto CloseRoot;
    }

    File->GetInfo(File, &gEfiFileInfoGuid, &InfoSize, NULL);
    FileInfo = AllocatePool(InfoSize);
    if (!FileInfo) {
        Status = EFI_OUT_OF_RESOURCES;
        goto CloseFile;
    }

    Status = File->GetInfo(File, &gEfiFileInfoGuid, &InfoSize, FileInfo);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Could not get file size: %r", Status);
        goto CloseFile;
    }

    *Size = FileInfo->FileSize;
    FreePool(FileInfo);
    *Buffer = (VOID *)AllocatePool(*Size);
    if (!*Buffer) {
        DbgError(L"Could not allocate buffer");
        Status = EFI_OUT_OF_RESOURCES;
        goto CloseFile;
    }

    Status = File->Read(File, Size, *Buffer);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Read error: %r", Status);
        goto Cleanup;
    }

    goto CloseFile;

Cleanup:
    FreePool(*Buffer);

CloseFile:
    File->Close(File);

CloseRoot:
    Root->Close(Root);

Out:
    return Status;
}

static
EFI_STATUS
ReadFileFromShell(
    IN CHAR16 *FileName,
    OUT VOID **Buffer,
    OUT UINTN *Size
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
    EFI_SHELL_PROTOCOL *Shell = NULL;
    SHELL_FILE_HANDLE FileHandle = NULL;

    Status = gBS->LocateProtocol(&gEfiShellProtocolGuid, NULL, (VOID**)&Shell);  
	if (EFI_ERROR (Status)) {
		DbgError(L"locate ShellProtocol failed: %r", Status);
		return EFI_ABORTED;  
	}

    Status = Shell->OpenFileByName(FileName, &FileHandle, EFI_FILE_MODE_READ);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Open file (%s) failed: %r", FileName, Status);
        goto Out;
    }

    Status = Shell->GetFileSize(FileHandle, Size);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Could not get file size: %r", Status);
        goto CloseFile;
    }

    *Buffer = (VOID *)AllocatePool(*Size);
    if (!*Buffer) {
        DbgError(L"Could not allocate buffer");
        Status = EFI_OUT_OF_RESOURCES;
        goto CloseFile;
    }

    Status = Shell->ReadFile(FileHandle, Size, *Buffer);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Read error: %r", Status);
        goto Cleanup;
    }

    goto CloseFile;

Cleanup:
    FreePool(*Buffer);

CloseFile:
    Shell->CloseFile(FileHandle);

Out:
    return Status;
}

static
EFI_STATUS
ReadFile(
    IN CHAR16 *FileName,
    OUT VOID **Buffer,
    OUT UINTN *Size
)
{
    EFI_STATUS  Status = EFI_SUCCESS;

	Status = ReadFileFromShell(FileName,Buffer, Size);
	if (Status == EFI_SUCCESS)
		return EFI_SUCCESS;

	Status = ReadFileFromVolume(FileName,Buffer,Size);
	if (Status)
		DbgError(L"Read from Volume fail: %r", Status);
	
	return Status;
}

static
VOID
EFIAPI
NotifyNothing(
    IN EFI_EVENT Event,
    IN VOID *Context
)
{
    return;
}

static
VOID
EFIAPI
InternalWaitEventNotify(
    IN EFI_EVENT Event,
    IN VOID *Context
)
{
    EFI_EVENT *InternalWaitEvent = Context;

    gBS->SignalEvent(*InternalWaitEvent);
}

static
EFI_STATUS
CreateGlobalEvents(VOID)
{
    EFI_STATUS Status = EFI_SUCCESS;

    Status = gBS->CreateEvent(EVT_NOTIFY_WAIT,
        TPL_CALLBACK,
        NotifyNothing,
        NULL,
        &gNotifyWaitEvent);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Create Notify Wait Event failed: %r", Status);
        return Status;
    }

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
        TPL_CALLBACK,
        InternalWaitEventNotify,
        &gNotifyWaitEvent,
        &gTokenSignalEvent);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Create TokenSignalEvent failed: %r", Status);
        gBS->CloseEvent(gNotifyWaitEvent);
        gNotifyWaitEvent = NULL;
        return Status;
    }

    return EFI_SUCCESS;
}

static
VOID
CloseGlobalEvents(VOID)
{
    if (gNotifyWaitEvent) {
        gBS->CloseEvent(gNotifyWaitEvent);
        gNotifyWaitEvent = NULL;
    }

    if (gTokenSignalEvent) {
        gBS->CloseEvent(gTokenSignalEvent);
        gTokenSignalEvent = NULL;
    }
}

static
EFI_STATUS
InitProtocols(
    IN  EFI_HANDLE ImageHandle,
    OUT EFI_HANDLE *WlanDriverHandle,
    OUT EFI_SUPPLICANT_PROTOCOL** SupplicantProtocol,
    OUT EFI_EAP_CONFIGURATION_PROTOCOL** EapProtocol,
    OUT EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL **WifiProtocol


)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN HandleArraySize = sizeof(*WlanDriverHandle);

    *WlanDriverHandle = NULL;
    *WifiProtocol = NULL;
    *SupplicantProtocol = NULL;

    // locate any wifi card
    Status = gBS->LocateHandle(ByProtocol,
        &gEfiWiFi2ProtocolGuid,
        NULL,
        &HandleArraySize,
        WlanDriverHandle);
    if (Status != EFI_BUFFER_TOO_SMALL && Status != EFI_SUCCESS) {
        DbgError(L"Could not find WiFi2 driver: %r", Status);
        return Status;
    }

    // we should have initialized the supplicant
    Status = gBS->OpenProtocol(*WlanDriverHandle,
        &gEfiSupplicantProtocolGuid,
        (VOID **)SupplicantProtocol,
        ImageHandle,
        NULL,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Could not open Supplicant protocol: %r", Status);
        return Status;
    }

    Status = gBS->OpenProtocol(*WlanDriverHandle,
        &gEfiWiFi2ProtocolGuid,
        (VOID **)WifiProtocol,
        ImageHandle,
        NULL,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Could not open WiFi2 protocol: %r", Status);
        goto cleanup;
    }

    Status = gBS->OpenProtocol(*WlanDriverHandle,
        &gEfiEapConfigurationProtocolGuid,
        (VOID **)EapProtocol,
        ImageHandle,
        NULL,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Could not open EapConfiguration protocol: %r", Status);
        goto cleanup;
    }

    return Status;

cleanup:
    if (*EapProtocol) {
        gBS->CloseProtocol(*WlanDriverHandle, &gEfiEapConfigurationProtocolGuid, ImageHandle, NULL);
        *EapProtocol = NULL;
    }

    if (*WifiProtocol) {
        gBS->CloseProtocol(*WlanDriverHandle, &gEfiWiFi2ProtocolGuid, ImageHandle, NULL);
        *WifiProtocol = NULL;
    }

    if (*SupplicantProtocol) {
        gBS->CloseProtocol(*WlanDriverHandle, &gEfiSupplicantProtocolGuid, ImageHandle, NULL);
        *SupplicantProtocol = NULL;
    }
    return Status;
}

static
VOID
DeinitProtocols(
    IN EFI_HANDLE ImageHandle,
    IN EFI_HANDLE WlanDriverHandle)
{
    gBS->CloseProtocol(WlanDriverHandle, &gEfiWiFi2ProtocolGuid, ImageHandle, NULL);
    gBS->CloseProtocol(WlanDriverHandle, &gEfiSupplicantProtocolGuid, ImageHandle, NULL);
    gBS->CloseProtocol(WlanDriverHandle, &gEfiEapConfigurationProtocolGuid, ImageHandle, NULL);
}

static
VOID
PrintUsage(
    UINT8 ActionId
)
{
    DbgConsolePrint(L"Usage:");
    if (ActionId == ACTION_SCAN) {
        DbgConsolePrint(L" QcaWifiMgr.efi scan [<ssid1> <ssid2> ...]");
    }
    else if (ActionId == ACTION_CONNECT) {
        DbgConsolePrint(L" QcaWifiMgr.efi connect <ssid>       - connect to open network");
        DbgConsolePrint(L"                connect <ssid> <psk> - connect to WPA2 network with PSK");
    }
    else if (ActionId == ACTION_CONNECT_ONEX) {
        DbgConsolePrint(L" QcaWifiMgr.efi 1xconnect <ssid> peap <identity> <password> [<CA-cert-file>] - connect to PEAP + MSCHAPv2");
        DbgConsolePrint(L"                1xconnect <ssid> ttls <identity> <password> [<CA-cert-file>] - connect to TTLS + MSCHAPv2");
        DbgConsolePrint(L"                1xconnect <ssid> tls <identity> <CA-cert-file> <Client-cert-file> <Client-privkey-file> [<privkey-pass>] - connect to TLS");
    }
	if (ActionId == ACTION_RSSI) {
		DbgConsolePrint(L" QcaWifiMgr.efi test_rssi <ssid>");
	}
    else {
        DbgConsolePrint(L" QcaWifiMgr.efi link_state                          - get link state");
		DbgConsolePrint(L" QcaWifiMgr.efi link_address                        - get link address");
        DbgConsolePrint(L"                scan [<ssid1> <ssid2> ...]          - scan for networks");
		DbgConsolePrint(L"                test_rssi <ssid>                    - Test chain rssi for specific ssid");
        DbgConsolePrint(L"                connect <ssid> [<psk>] [<type>]     - connect to a network");
        DbgConsolePrint(L"                1xconnect <ssid> <type> ...         - connect to WPA-Enterprise network");
        DbgConsolePrint(L"                disconnect                          - disconnect from network");
    }
}

EFI_STATUS
ActionLinkState(
    EFI_SUPPLICANT_PROTOCOL *SupplicantProtocol
)
{
    static const char *LinkStateStr[] = {
      [Ieee80211UnauthenticatedUnassociated]  = "Idle",
      [Ieee80211AuthenticatedUnassociated]    = "Authenticated",
      [Ieee80211PendingRSNAuthentication]     = "PendingRSNAuth",
      [Ieee80211AuthenticatedAssociated]      = "Associated"
    };
    EFI_80211_LINK_STATE LinkState;
    UINTN DataSize = sizeof(LinkState);
    EFI_STATUS Status = EFI_SUCCESS;

    Status = SupplicantProtocol->GetData(SupplicantProtocol,
        EfiSupplicant80211LinkState, (UINT8 *)&LinkState, &DataSize);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Getting link state failed: %r", Status);
        return Status;
    }

    DbgConsolePrint(L"{\"state\": \"%a\"}", LinkStateStr[LinkState]);

    return EFI_SUCCESS;
}

EFI_STATUS
ActionLinkAddress(
    EFI_SUPPLICANT_PROTOCOL *SupplicantProtocol
)
{
	UINT8 LinkAddr[ETH_ALEN] = {0,};
    UINTN DataSize = sizeof(LinkAddr);
    EFI_STATUS Status = EFI_SUCCESS;

    Status = SupplicantProtocol->GetData(SupplicantProtocol,
        EfiSupplicant80211TargetSSIDMac, (UINT8 *)&LinkAddr, &DataSize);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Getting link address failed: %r", Status);
        return Status;
    }

	DbgConsolePrint(L"Link_Addr: 0x%02X-0x%02X-0x%02X-0x%02X-0x%02X-0x%02X",
		LinkAddr[0], LinkAddr[1], LinkAddr[2], LinkAddr[3], LinkAddr[4], LinkAddr[5]);

    return EFI_SUCCESS;
}

static
const CHAR8 *
CipherSuiteName(
    EFI_80211_SUITE_SELECTOR *Suite
)
{
    UINT32 Oui = (Suite->Oui[0] << 16) | (Suite->Oui[1] << 8) | Suite->Oui[2];
    UINT32 CipherSuite = (Oui << 8) | Suite->SuiteType;

    switch (CipherSuite) {
    case WIFI_RSN_CIPHER_SUITE_CCMP:
        return "CCMP";
    case WIFI_RSN_CIPHER_SUITE_TKIP:
        return "TKIP";
    }

    return "Unknown";
}

static
const CHAR8 *
AKMSuiteName(
    EFI_80211_SUITE_SELECTOR *Suite
)
{
    UINT32 Oui = (Suite->Oui[0] << 16) | (Suite->Oui[1] << 8) | Suite->Oui[2];
    UINT32 AKMSelector = (Oui << 8) | Suite->SuiteType;

    switch (AKMSelector) {
    case WIFI_RSN_AKM_SELECTOR_PSK:
        return "PSK";
    case WIFI_RSN_AKM_SELECTOR_8021X:
        return "802.1X";
    }

    return "Unknown";
}

static
EFI_STATUS
ActionTestRssi(
	IN UINTN argc,
	IN CHAR16 **argv,
	IN EFI_QCWLAN_TEST_PROTOCOL *QcWlanTestProtocol
)
{
	EFI_STATUS Status = EFI_SUCCESS;

	EFI_QCWLAN_GET_RSSI_TOKEN *Token;
	EFI_QCWLAN_GET_RSSI_DATA *Data;
	EFI_QCWLAN_GET_RSSI_RESULT *Result;
	UINT32 NumOfFrequency = 0;
	UINT32 FrequencyList[1] = { 0 };
	UINTN EventIdx;

	if (argc == 0) {
		DbgError(L"No SSID sepcified");
		return EFI_INVALID_PARAMETER;
	}

	if (StrLen(argv[0]) > EFI_MAX_SSID_LEN) {
		DbgError(L"Invalid SSID: %s", argv[0]);
		return EFI_INVALID_PARAMETER;
	}

	if (argc > 1) {
		FrequencyList[0] = (UINT32)StrDecimalToUintn(argv[1]);
		if (FrequencyList[0])
			NumOfFrequency++;
	}

	// Allocate the token
	Token = AllocateZeroPool(sizeof(*Token) + sizeof(*Data) + NumOfFrequency * sizeof(UINT32));
	if (!Token) {
		DbgError(L"Could not allocate buffer for Rssi data");
		return EFI_OUT_OF_RESOURCES;
	}
	Data = (VOID *)((UINT8 *)Token + sizeof(*Token));

	/* Initialize the token */
	Token->Event = gTokenSignalEvent;
	Token->Data = Data;

	UnicodeStrToAsciiStrS(argv[0], (CHAR8*)Data->SSId.SSId, EFI_MAX_SSID_LEN);
	Data->SSId.SSIdLen =
		MIN((UINT8)AsciiStrLen((CONST CHAR8*)Data->SSId.SSId), ARRAY_SIZE(Data->SSId.SSId));

	for (UINT32 i = 0; i < MIN(NumOfFrequency, ARRAY_SIZE(FrequencyList)); i++) {
		Data->FrequencyList[i] = FrequencyList[i];
		Data->NumOfFrequency++;
	}

	DbgConsolePrint(L"DoActionTestRssi: SSID: %a, Length: %d, Frequency %d",
		Data->SSId.SSId, Data->SSId.SSIdLen, FrequencyList[0]);

	if (QcWlanTestProtocol) {
		Status = QcWlanTestProtocol->GetRssi(QcWlanTestProtocol, Token);
		if (Status != EFI_SUCCESS) {
			DbgError(L"Failed getting rssi: %r", Status);
			goto cleanup;
		}

		Status = gBS->WaitForEvent(1, &gNotifyWaitEvent, &EventIdx);
		if (Status != EFI_SUCCESS) {
			DbgError(L"Wait on internal event failed: %r", Status);
			goto cleanup;
		}
	}
	else {
		DbgConsolePrint(L"Invalid QcWlanTestProtocol");
		Status = EFI_INVALID_PARAMETER;
		goto cleanup;
	}

	Result = Token->Result;

	if (Result->NumOfRssiDesc && Result->RssiDesc) {
		DbgConsolePrint(L"Total BSSID Count %d of: %a",
			Result->NumOfRssiDesc, Data->SSId.SSId);
		for (UINT32 i = 0; i < Result->NumOfRssiDesc; i++) {
			DbgConsolePrint(L"[%d]BSSID:%02X:%02X:%02X:%02X:%02X:%02X RSSI of Antenna 0: %d",
				i,
				Result->RssiDesc[i].Bssid[0], Result->RssiDesc[i].Bssid[1],
				Result->RssiDesc[i].Bssid[2], Result->RssiDesc[i].Bssid[3],
				Result->RssiDesc[i].Bssid[4], Result->RssiDesc[i].Bssid[5],
				Result->RssiDesc[i].ChainRssi[0]);
			DbgConsolePrint(L"[%d]BSSID:%02X:%02X:%02X:%02X:%02X:%02X RSSI of Antenna 1: %d",
				i,
				Result->RssiDesc[i].Bssid[0], Result->RssiDesc[i].Bssid[1],
				Result->RssiDesc[i].Bssid[2], Result->RssiDesc[i].Bssid[3],
				Result->RssiDesc[i].Bssid[4], Result->RssiDesc[i].Bssid[5],
				Result->RssiDesc[i].ChainRssi[1]);
			DbgConsolePrint(L"Antenna Count %d, Antenna Combo RSSI: %d",
				Result->RssiDesc[i].NumOfChain,
				Result->RssiDesc[i].ComboRssi);
			DbgConsolePrint(L"-----------------------------------------------------------");
		}
	}
	else {
		DbgError(L"Not found SSID %a", Data->SSId.SSId);
		goto cleanup;
	}

cleanup:
	if (Token->Result)
		FreePool(Token->Result);

	if (Token)
		FreePool(Token);

	return Status;
}

static
EFI_STATUS
ActionScan(
    IN UINTN SsidCount,
    IN CHAR16 **Ssids,
    IN EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL *WifiProtocol
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    WIFI_MGR_SCAN_DATA *ScanData = NULL;
    UINTN i;
    CHAR8 TmpSsid[EFI_MAX_SSID_LEN + 1];
    UINTN EventIdx;

    ScanData = AllocateZeroPool(sizeof(*ScanData) + sizeof(EFI_80211_SSID) * (SsidCount - 1));
    if (!ScanData) {
        DbgError(L"Allocate buffer for scan results failed");
        return EFI_OUT_OF_RESOURCES;
    }

    ScanData->Token.Data = &ScanData->Data;
    ScanData->Token.Event = gTokenSignalEvent;

    for (i = 0; i < SsidCount; i++) {
        if (StrLen(Ssids[i]) > EFI_MAX_SSID_LEN) {
            DbgError(L"Invalid SSID: %s", Ssids[i]);
            Status = EFI_INVALID_PARAMETER;
            goto cleanup;
        }

        // convert to ASCII in a temp buffer and then copy only first EFI_MAX_SSID_LEN
        // characters
        UnicodeStrToAsciiStrS(Ssids[i], TmpSsid, EFI_MAX_SSID_LEN);
        AsciiStrnCpyS((CHAR8 *)ScanData->Data.SSIDList[i].SSId, EFI_MAX_SSID_LEN,
            TmpSsid, EFI_MAX_SSID_LEN);
        ScanData->Data.SSIDList[i].SSIdLen = (UINT8)AsciiStrLen(TmpSsid);

        ScanData->Data.NumOfSSID++;
    }

    Status = WifiProtocol->GetNetworks(WifiProtocol, &ScanData->Token);
    if (Status != EFI_SUCCESS) {
        DbgError(L"GetNetworks failed: %r", Status);
        goto cleanup;
    }

    Status = gBS->WaitForEvent(1, &gNotifyWaitEvent, &EventIdx);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Wait on internal event failed: %r", Status);
        goto cleanup;
    }
    if (ScanData->Token.Status != EFI_SUCCESS) {
        DbgError(L"Scan failed: %r", ScanData->Token.Status);
        Status = ScanData->Token.Status;
        goto cleanup;
    }

    Status = EFI_SUCCESS;

    if (!ScanData->Token.Result)
        goto cleanup;

    for (i = 0; i < ScanData->Token.Result->NumOfNetworkDesc; i++) {
        EFI_80211_NETWORK_DESCRIPTION *NetworkDesc =
            &ScanData->Token.Result->NetworkDesc[i];

        // Dump the scan results
        DbgConsolePrint(L"[%03d] SSID: %-32a Quality: %-3d [%a]", i, NetworkDesc->Network.SSId.SSId, NetworkDesc->NetworkQuality, 
        	NetworkDesc->Network.AKMSuite->AKMSuiteCount ? "Secured" : "Open");
    }

cleanup:
    if (ScanData->Token.Result)
        FreePool(ScanData->Token.Result);

    if (ScanData)
        FreePool(ScanData);

    return Status;
}

static
EFI_STATUS
SetSupplicantPsk(
    IN EFI_SUPPLICANT_PROTOCOL *SupplicantProtocol,
    IN CHAR16 *UnicodePsk
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN PskLen;
    CHAR8 AsciiPsk[64];

    PskLen = StrLen(UnicodePsk);
    if (PskLen < 8 || PskLen > 63) {
        DbgError(L"PSK must be between 8 and 63 characters long");
        return EFI_INVALID_PARAMETER;
    }

    UnicodeStrToAsciiStrS(UnicodePsk, AsciiPsk, 64);
    Status = SupplicantProtocol->SetData(SupplicantProtocol,
        EfiSupplicant80211PskPassword,
        (VOID *)AsciiPsk,
        PskLen + 1);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Could not set PSK to supplicant: %r", Status);
        return Status;
    }

    return EFI_SUCCESS;
}

// Connection Data should be set by Wi-Fi Driver
static
EFI_STATUS
SetSupplicantConnectData(
    IN EFI_SUPPLICANT_PROTOCOL *SupplicantProtocol,
    IN EFI_80211_SSID *SSId,
    IN EFI_80211_AKM_SUITE_SELECTOR *AKMSuite,
    IN EFI_80211_CIPHER_SUITE_SELECTOR *GroupCipher,
    IN EFI_80211_CIPHER_SUITE_SELECTOR *PairwiseCipher
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN AKMSuiteSize, GroupCipherSize, PairwiseCipherSize;

    Status = SupplicantProtocol->SetData(SupplicantProtocol,
        EfiSupplicant80211TargetSSIDName,
        (VOID *)SSId,
        sizeof(EFI_80211_SSID));
    if (Status != EFI_SUCCESS) {
        DbgError(L"Could not set SSID to supplicant: %r", Status);
        return Status;
    }

    AKMSuiteSize = sizeof(*AKMSuite);
    if (AKMSuite->AKMSuiteCount) {
        AKMSuiteSize += sizeof(AKMSuite->AKMSuiteList[0]) * (AKMSuite->AKMSuiteCount - 1);
        Status = SupplicantProtocol->SetData(SupplicantProtocol,
            EfiSupplicant80211AKMSuite,
            (VOID *)AKMSuite,
            AKMSuiteSize);
        if (Status != EFI_SUCCESS) {
            DbgError(L"Could not set AKMSuite to supplicant: %r", Status);
            return Status;
        }
    }

    GroupCipherSize = sizeof(*GroupCipher);
    if (GroupCipher->CipherSuiteCount) {
        GroupCipherSize += sizeof(GroupCipher->CipherSuiteList[0]) * (GroupCipher->CipherSuiteCount - 1);
        Status = SupplicantProtocol->SetData(SupplicantProtocol,
            EfiSupplicant80211GroupDataCipherSuite,
            (VOID *)GroupCipher,
            GroupCipherSize);
        if (Status != EFI_SUCCESS) {
            DbgError(L"Could not set group cipher to supplicant: %r", Status);
            return Status;
        }
    }

    PairwiseCipherSize = sizeof(*PairwiseCipher);
    if (PairwiseCipher->CipherSuiteCount) {
        PairwiseCipherSize += sizeof(PairwiseCipher->CipherSuiteList[0]) * (PairwiseCipher->CipherSuiteCount - 1);
        Status = SupplicantProtocol->SetData(SupplicantProtocol,
            EfiSupplicant80211PairwiseCipherSuite,
            (VOID *)PairwiseCipher,
            PairwiseCipherSize);
        if (Status != EFI_SUCCESS) {
            DbgError(L"Could not set pairwise cipher to supplicant: %r", Status);
            return Status;
        }
    }

    return EFI_SUCCESS;
}

static
EFI_STATUS
SetEapMethod(
    IN EFI_EAP_CONFIGURATION_PROTOCOL *EapProtocol,
    IN EFI_EAP_TYPE EapMethod
)
{
    return EapProtocol->SetData(EapProtocol, EFI_EAP_TYPE_ATTRIBUTE,
        EfiEapConfigEapAuthMethod, (VOID *)&EapMethod,
        sizeof(EapMethod));
}

static
EFI_STATUS
SetEapSecondMethod(
    IN EFI_EAP_CONFIGURATION_PROTOCOL *EapProtocol,
    IN EFI_EAP_TYPE EapFirstMethod,
    IN EFI_EAP_TYPE EapSecondMethod
)
{
    return EapProtocol->SetData(EapProtocol, EapFirstMethod,
        EfiEapConfigEap2ndAuthMethod,
        (VOID *)&EapSecondMethod,
        sizeof(EapSecondMethod));
}

static
EFI_STATUS
SetEapIdentity(
    IN EFI_EAP_CONFIGURATION_PROTOCOL *EapProtocol,
    IN CHAR16 *UnicodeIdentity
)
{
    UINTN IdentityLen;
    CHAR8 *AsciiIdentity;
    EFI_STATUS Status = EFI_SUCCESS;

    IdentityLen = StrLen(UnicodeIdentity);
    AsciiIdentity = AllocateZeroPool(IdentityLen + 1);
    if (!AsciiIdentity)
        return EFI_DEVICE_ERROR;

    UnicodeStrToAsciiStrS(UnicodeIdentity, AsciiIdentity, IdentityLen + 1);
    // make sure not to send the terminating null. identity must be exact.
    Status = EapProtocol->SetData(EapProtocol, EFI_EAP_TYPE_IDENTITY,
        EfiEapConfigIdentityString,
        (VOID *)AsciiIdentity, IdentityLen);
    FreePool(AsciiIdentity);
    return Status;
}

static
EFI_STATUS
SetEapPrivKeyPassword(
    IN EFI_EAP_CONFIGURATION_PROTOCOL *EapProtocol,
    IN EFI_EAP_TYPE EapType,
    IN CHAR16 *UnicodePassword
)
{
    UINTN PasswordLen;
    CHAR8 *AsciiPassword;
    EFI_STATUS Status = EFI_SUCCESS;

    PasswordLen = StrLen(UnicodePassword);
    AsciiPassword = AllocateZeroPool(PasswordLen + 1);
    if (!AsciiPassword)
        return EFI_DEVICE_ERROR;

    UnicodeStrToAsciiStrS(UnicodePassword, AsciiPassword, PasswordLen + 1);
    Status = EapProtocol->SetData(EapProtocol, EapType,
        EfiEapConfigEapTlsClientPrivateKeyFilePassword,
        (VOID *)AsciiPassword, PasswordLen + 1);
    FreePool(AsciiPassword);
    return Status;
}

static
EFI_STATUS
SetEapMSCHAPv2Password(
    IN EFI_EAP_CONFIGURATION_PROTOCOL *EapProtocol,
    IN CHAR16 *UnicodePassword
)
{
    // send size of password data for MSCHAPv2
    return EapProtocol->SetData(EapProtocol, EFI_EAP_TYPE_MSCHAPV2,
        EfiEapConfigEapMSChapV2Password,
        (VOID *)UnicodePassword,
        StrLen(UnicodePassword) * 2);
}

static
EFI_STATUS
SetEapDataFromFile(
    IN EFI_EAP_CONFIGURATION_PROTOCOL *EapProtocol,
    IN EFI_EAP_TYPE EapType,
    IN EFI_EAP_CONFIG_DATA_TYPE DataType,
    IN CHAR16 *FilePath
)
{
    VOID *FileData;
    UINTN FileDataSize;
    EFI_STATUS Status = EFI_SUCCESS;

    Status = ReadFile(FilePath, &FileData, &FileDataSize);
    if (Status != EFI_SUCCESS)
        return Status;

    Status = EapProtocol->SetData(EapProtocol, EapType, DataType, FileData,
        FileDataSize);
    FreePool(FileData);
    return Status;
}

static
EFI_STATUS
ActionConnect(
    IN UINTN argc,
    IN CHAR16 **argv,
    IN EFI_SUPPLICANT_PROTOCOL *SupplicantProtocol,
    IN EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL *WifiProtocol,
    IN EFI_EAP_CONFIGURATION_PROTOCOL *EapProtocol,
    IN BOOLEAN IsOneX
)
{
    WIFI_MGR_CONNECT_DATA *ConnData = NULL;
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN EventIdx;
    CHAR8 TmpSsid[EFI_MAX_SSID_LEN + 1];

    //  802.1X require an EAP type 
    if (argc < 1 || (IsOneX && argc < 2))
        return EFI_INVALID_PARAMETER;

    ConnData = AllocateZeroPool(sizeof(*ConnData));
    if (!ConnData) {
        DbgError(L"Could not allocate buffer for scan results");
        return EFI_OUT_OF_RESOURCES;
    }

    ConnData->Token.Event = gTokenSignalEvent;
    ConnData->Token.Data = &ConnData->Data;
    ConnData->Data.Network = &ConnData->Network;
    ConnData->Network.AKMSuite = &ConnData->AKMSuite;
    ConnData->Network.CipherSuite = &ConnData->CipherSuite;

    ConnData->Network.BSSType = IeeeInfrastructureBSS;
    ConnData->Data.FailureTimeout = 10; // use hard-coded limit for now

    if (StrLen(argv[0]) > EFI_MAX_SSID_LEN) {
        DbgError(L"Invalid SSID: %s", argv[0]);
        Status = EFI_INVALID_PARAMETER;
        goto cleanup;
    }

    // convert to ASCII
    UnicodeStrToAsciiStrS(argv[0], TmpSsid, EFI_MAX_SSID_LEN);
    AsciiStrnCpyS((CHAR8 *)ConnData->Network.SSId.SSId, EFI_MAX_SSID_LEN, TmpSsid,
        EFI_MAX_SSID_LEN);
    ConnData->Network.SSId.SSIdLen = (UINT8)AsciiStrLen(TmpSsid);

    // set cipher to CCMP and AKM suite to PSK or 802.1X
    if (argc >= 2 || IsOneX) {
        UINT8 WifiOui[] = { 0x00, 0x0F, 0xAC };

        ConnData->AKMSuite.AKMSuiteCount = 1;
        CopyMem(ConnData->AKMSuite.AKMSuiteList[0].Oui, WifiOui, 3);
        if (IsOneX)
            ConnData->AKMSuite.AKMSuiteList[0].SuiteType = WIFI_AKM_SUITE_TYPE_8021X;
        else if (argc >= 3 && StrCmp(argv[2], L"sae") == 0)
            ConnData->AKMSuite.AKMSuiteList[0].SuiteType = WIFI_AKM_SUITE_TYPE_SAE;
        else
            ConnData->AKMSuite.AKMSuiteList[0].SuiteType = WIFI_AKM_SUITE_TYPE_PSK;

        ConnData->CipherSuite.CipherSuiteCount = 2;
        CopyMem(ConnData->CipherSuite.CipherSuiteList[0].Oui, WifiOui, 3);
        ConnData->CipherSuite.CipherSuiteList[0].SuiteType = WIFI_CIPHER_SUITE_TYPE_CCMP;
        CopyMem(ConnData->CipherSuite.CipherSuiteList[1].Oui, WifiOui, 3);
        ConnData->CipherSuite.CipherSuiteList[1].SuiteType = WIFI_CIPHER_SUITE_TYPE_TKIP;
    }
    else {
        ConnData->AKMSuite.AKMSuiteCount = 0;
        ConnData->CipherSuite.CipherSuiteCount = 0;
    }

    if (argc >= 2 && !IsOneX) {
        Status = SetSupplicantPsk(SupplicantProtocol, argv[1]);
        if (Status != EFI_SUCCESS) {
            Status = EFI_DEVICE_ERROR;
            goto cleanup;
        }
    }

    if (IsOneX) {
        if (StrCmp(argv[1], L"peap") == 0 || StrCmp(argv[1], L"ttls") == 0) {
            EFI_EAP_TYPE EapType = (StrCmp(argv[1], L"peap") == 0) ?
                EFI_EAP_TYPE_PEAP : EFI_EAP_TYPE_TTLS;

            if (argc < 4) {
                PrintUsage(ACTION_CONNECT_ONEX);
                Status = EFI_INVALID_PARAMETER;
                goto cleanup;
            }

            Status = SetEapMethod(EapProtocol, EapType);
            if (Status != EFI_SUCCESS) {
                Status = EFI_DEVICE_ERROR;
                goto cleanup;
            }

            Status = SetEapSecondMethod(EapProtocol, EapType, EFI_EAP_TYPE_MSCHAPV2);
            if (Status != EFI_SUCCESS) {
                Status = EFI_DEVICE_ERROR;
                goto cleanup;
            }

            Status = SetEapIdentity(EapProtocol, argv[2]);
            if (Status != EFI_SUCCESS) {
                Status = EFI_DEVICE_ERROR;
                goto cleanup;
            }

            Status = SetEapMSCHAPv2Password(EapProtocol, argv[3]);
            if (Status != EFI_SUCCESS) {
                Status = EFI_DEVICE_ERROR;
                goto cleanup;
            }

            if (argc > 4) {
                Status = SetEapDataFromFile(EapProtocol, EapType,
                    EfiEapConfigEapTlsCACert, argv[4]);
                if (Status != EFI_SUCCESS) {
                    Status = EFI_DEVICE_ERROR;
                    goto cleanup;
                }
            }
        }
        else if (StrCmp(argv[1], L"tls") == 0) {
            if (argc < 6) {
                PrintUsage(ACTION_CONNECT_ONEX);
                Status = EFI_INVALID_PARAMETER;
                goto cleanup;
            }

            Status = SetEapMethod(EapProtocol, EFI_EAP_TYPE_EAPTLS);
            if (Status != EFI_SUCCESS) {
                Status = EFI_DEVICE_ERROR;
                goto cleanup;
            }

            Status = SetEapIdentity(EapProtocol, argv[2]);
            if (Status != EFI_SUCCESS) {
                Status = EFI_DEVICE_ERROR;
                goto cleanup;
            }

            Status = SetEapDataFromFile(EapProtocol, EFI_EAP_TYPE_EAPTLS,
                EfiEapConfigEapTlsCACert, argv[3]);
            if (Status != EFI_SUCCESS) {
                Status = EFI_DEVICE_ERROR;
                goto cleanup;
            }

            Status = SetEapDataFromFile(EapProtocol, EFI_EAP_TYPE_EAPTLS,
                EfiEapConfigEapTlsClientCert, argv[4]);
            if (Status != EFI_SUCCESS) {
                Status = EFI_DEVICE_ERROR;
                goto cleanup;
            }

            Status = SetEapDataFromFile(EapProtocol, EFI_EAP_TYPE_EAPTLS,
                EfiEapConfigEapTlsClientPrivateKeyFile, argv[5]);
            if (Status != EFI_SUCCESS) {
                Status = EFI_DEVICE_ERROR;
                goto cleanup;
            }

            if (argc > 6) {
                Status = SetEapPrivKeyPassword(EapProtocol, EFI_EAP_TYPE_EAPTLS,
                    argv[6]);
                if (Status != EFI_SUCCESS) {
                    Status = EFI_DEVICE_ERROR;
                    goto cleanup;
                }
            }
        }
        else {
            DbgConsolePrint(L"EAP method %s unsupported", argv[1]);
            Status = EFI_INVALID_PARAMETER;
            goto cleanup;
        }
    }

    Status = WifiProtocol->ConnectNetwork(WifiProtocol, &ConnData->Token);
    if (Status != EFI_SUCCESS) {
        DbgError(L"ConnectNetwork failed: %r", Status);
        goto cleanup;
    }

    Status = gBS->WaitForEvent(1, &gNotifyWaitEvent, &EventIdx);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Wait on internal event failed: %r", Status);
        goto cleanup;
    }

    if (ConnData->Token.Status != EFI_SUCCESS) {
        DbgError(L"Connect failed: %r", ConnData->Token.Status);
        Status = ConnData->Token.Status;
        goto cleanup;
    }

    DbgConsolePrint(L"{\"result\": %d}", ConnData->Token.ResultCode);
    Status = EFI_SUCCESS;

cleanup:
    if (ConnData)
        FreePool(ConnData);

    return Status;
}

static
EFI_STATUS
ActionDisconnect(
    IN EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL* WifiProtocol
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN EventIdx;
    EFI_80211_DISCONNECT_NETWORK_TOKEN Token = { 0 };

    Token.Event = gTokenSignalEvent;

    Status = WifiProtocol->DisconnectNetwork(WifiProtocol, &Token);
    if (Status != EFI_SUCCESS) {
        DbgError(L"DisconnectNetwork failed: %r", Status);
        goto cleanup;
    }

    Status = gBS->WaitForEvent(1, &gNotifyWaitEvent, &EventIdx);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Wait on internal event failed: %r", Status);
        goto cleanup;
    }

    if (Token.Status != EFI_SUCCESS) {
        DbgError(L"Disconnect failed: %r", Token.Status);
        Status = Token.Status;
        goto cleanup;
    }

    DbgConsolePrint(L"{\"result\": 0}");
    Status = EFI_SUCCESS;

cleanup:
    return Status;
}

VOID
EFIAPI
WifiEnableCallback( 
    IN EFI_EVENT  Event,
    IN VOID      *Context
  )
{
	//Do Nothing
}

EFI_STATUS
ConnectAllEfi (
VOID
)
{
	EFI_STATUS Status;
	UINTN HandleCount;
	EFI_HANDLE *HandleBuffer;
	UINTN Index;
	
	Status = gBS->LocateHandleBuffer (
				AllHandles,
				NULL,
				NULL,
				&HandleCount,
				&HandleBuffer
				);
	if (EFI_ERROR (Status)) {
		return Status;
	}
	
	for (Index = 0; Index < HandleCount; Index++) {
		Status = gBS->ConnectController (HandleBuffer[Index], NULL, NULL, TRUE);
	}
	
	if (HandleBuffer != NULL) {
		FreePool (HandleBuffer);
	}
	
	return EFI_SUCCESS;
}

static
EFI_STATUS
ActionLoadWifi(
VOID
)
{
    EFI_STATUS 	Status;
	EFI_EVENT  	WifiEnableEvent = (EFI_EVENT)NULL;
	EFI_GUID 	gEfiEventWifiReadyToEnableGuid = 
		{ 0xB7B70E36, 0xEC24, 0x46FB, { 0x9B, 0x39, 0x2E, 0x73, 0xB0, 0x59, 0xB4, 0x12 } };
	
    Status = gBS->CreateEventEx (
                   EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   WifiEnableCallback,
                   NULL,
                   &gEfiEventWifiReadyToEnableGuid,
                   &WifiEnableEvent
                   );
	if (Status != EFI_SUCCESS) {
		DbgError(L"create event Status = %x", Status);
        return Status;
	}
	
  	Status = gBS->SignalEvent(WifiEnableEvent);
	if (Status != EFI_SUCCESS) {
		DbgError(L"siginal status = %x", Status);
		return Status;
	}
	
	Status = ConnectAllEfi();
	if (Status != EFI_SUCCESS) {
    	DbgError(L"conn drv status = %x", Status);
		return Status;
	}
	
	gBS->CloseEvent(WifiEnableEvent);
    return Status;
}

static
EFI_STATUS
DoWifiMgrAction(
    IN UINT8 ActionId,
    IN UINTN argc,
    IN CHAR16** argv,
    IN EFI_SUPPLICANT_PROTOCOL* SupplicantProtocol,
    IN EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL* WifiProtocol,
    IN EFI_EAP_CONFIGURATION_PROTOCOL* EapProtocol,
	EFI_QCWLAN_TEST_PROTOCOL* QcwlanProtocol
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    switch (ActionId) {   
    case ACTION_LINK_STATE:
        Status = ActionLinkState(SupplicantProtocol);
        break;
	case ACTION_LINK_ADDRESS:
		Status = ActionLinkAddress(SupplicantProtocol);
		break;
    case ACTION_SCAN:
        Status = ActionScan(argc - 2, &argv[2], WifiProtocol);
        break;
    case ACTION_CONNECT:
        Status = ActionConnect(argc - 2, &argv[2], SupplicantProtocol,
            WifiProtocol, EapProtocol, FALSE);
        break;
    case ACTION_CONNECT_ONEX:
        Status = ActionConnect(argc - 2, &argv[2], SupplicantProtocol,
            WifiProtocol, EapProtocol, TRUE);
        break;
    case ACTION_DISCONNECT:
        Status = ActionDisconnect(WifiProtocol);
        break;
    case ACTION_RSSI:
        Status = ActionTestRssi(argc - 2, &argv[2], QcwlanProtocol);
        break;
    default:
        DbgError(L"Invalid Action to do");
    }

    return Status;
}

EFI_STATUS
EFIAPI
QcaWifiMgrEntryPoint(
    IN  EFI_HANDLE          ImageHandle,
    IN  EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HANDLE WlanDriverHandle;

    EFI_SHELL_PARAMETERS_PROTOCOL           *ShellParamsProtocol = NULL;
    EFI_EAP_CONFIGURATION_PROTOCOL          *EapConfigProtocol = NULL;
    EFI_SUPPLICANT_PROTOCOL                 *SupplicantProtocol = NULL;
    EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL *WifiProtocol = NULL;
	EFI_QCWLAN_TEST_PROTOCOL    *QcwlanProtocol = NULL;

   
    CHAR16 **argv;
    UINTN argc;

#if SUPPORT_GET_DEVICE_TYPE_BY_WLANLIB
	enum WLAN_DEVICE_TYPE Type;	
    WlanDeviceInfoHandle DeviceHandle;
	
	/*Get Device Type is HMT/HSP*/
	Status = WlanGetDeviceType(&Type);
	DbgConsolePrint(L"Get Device Type Status = 0x%x, Type = %d\n", Status, Type);

	Status = WlanGetDeviceInfo(&DeviceHandle);
	DbgConsolePrint(L"Get Device Info Status = 0x%x, ChipIdStr/ChipId/VendorId/DeviceId = %a/0x%x/0x%x/0x%x\n",
		Status, DeviceHandle->ChipIdStr, DeviceHandle->ChipId, DeviceHandle->VendorId, DeviceHandle->DeviceId);
#endif

#if SUPPORT_LOAD_BY_EVT
	/* Siginal the Event to enable Wifi*/
	Status = ActionLoadWifi();
#endif

    Status = gBS->HandleProtocol(ImageHandle,
        &gEfiLoadedImageProtocolGuid,
        (VOID**)&gImageProtocol);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Open LoadedImage Protocol failed: %r", Status);
        return Status;
    }

    Status = InitProtocols(ImageHandle,
        &WlanDriverHandle, 
        &SupplicantProtocol,
        &EapConfigProtocol,
        &WifiProtocol
        );
    if (Status != EFI_SUCCESS) {
        DbgError(L"Init Protocols failed: %r", Status);
        goto cleanup;
    }

    Status = gBS->LocateProtocol(&gEfiQcWlanTestProtocolGuid,
        NULL,
        (VOID**)&QcwlanProtocol);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Locate Qcwlan Protocol failed: %r", Status);
        goto cleanup;
    }

    Status = gBS->OpenProtocol(ImageHandle,
        &gEfiShellParametersProtocolGuid,
        (VOID**)&ShellParamsProtocol,
        ImageHandle,
        NULL,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (Status != EFI_SUCCESS) {
        DbgError(L"Open Shell Parameters Protocol failed: %r", Status);
        goto cleanup;
    }

	Status = gBS->LocateProtocol(&gEfiQcWlanTestProtocolGuid,
		NULL,
		(VOID **)&QcwlanProtocol);
	if (Status != EFI_SUCCESS) {
		DbgError(L"Could not Locate QcWlanTestProtocol protocol: %r", Status);
		return Status;
	}

    Status = InitProtocols(ImageHandle,
        &WlanDriverHandle, 
		&SupplicantProtocol, &EapConfigProtocol, &WifiProtocol);
    if (Status != EFI_SUCCESS)
        return Status;

    argv = ShellParamsProtocol->Argv;
    argc = ShellParamsProtocol->Argc;
    if (argc < 2) {
        PrintUsage(ACTION_INVALID);
        goto cleanup;
    }

    Status = CreateGlobalEvents();
    if (Status != EFI_SUCCESS) {
        DbgError(L"Create global events failed: %r", Status);
        goto cleanup;
    }
    for (int i = 0; i < ACTION_INVALID; i++) {
        if (StrCmp(argv[1], WifiMgrAction[i].ActionStr) == 0) {
            DoWifiMgrAction(WifiMgrAction[i].ActionId,
                argc, argv,
                SupplicantProtocol,
                WifiProtocol,
                EapConfigProtocol,
                QcwlanProtocol
                );

            if (Status == EFI_INVALID_PARAMETER) {
                PrintUsage(WifiMgrAction[i].ActionId);
            }
        }
    }

cleanup:
    CloseGlobalEvents();

    if (ShellParamsProtocol)
        gBS->CloseProtocol(ImageHandle, &gEfiShellParametersProtocolGuid, ImageHandle, NULL);

    if (WifiProtocol)
        DeinitProtocols(ImageHandle, WlanDriverHandle);

    return EFI_SUCCESS;
}
