/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 18/11/21  zxue     refine code
 1/9/21    zxue     support read specific bdf from DPP
 19/8/21   zxue     fix KW issue
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <Uefi.h>
#include <qdf/qbase.h>
#include <qdf/firmware.h>
#include <Config.h>
#include "dpp.h"

#define WLAN_PROV_FILENAME       L"WLAN.PROVISION"
#define WLAN_CLPC_PROVISION_DATA L"WLAN_CLPC.PROVISION"
#define CHIP_ID_GF_MASK          0x10

#define ETH_ALEN                 6

#if SUPPORT_QCOM_DPP

extern EFI_STATUS
DppItemRead (
  IN  CHAR16       *Type,
  IN  CHAR16       *Name,
  OUT UINT8       **Buff,
  OUT UINTN        *Size
);

#else /* !SUPPORT_QCOM_DPP */

EFI_STATUS
DppItemRead (
  IN  CHAR16       *Type,
  IN  CHAR16       *Name,
  OUT UINT8       **Buff,
  OUT UINTN        *Size
)
{
	return EFI_UNSUPPORTED;
}

#endif

UINT8 DppGetWlanMacAddress(UINT8 *MacAddr)
{
    EFI_STATUS Status  = EFI_SUCCESS;
	UINT8 *pBufferIn   = NULL;
    UINTN BufferInSize = 0;
	UINT8 Version      = 0;
	UINT8 Length       = 0;
	UINT8 NumOfMac      = 0;

	DEBUG_PARAMETER(Version);
	DEBUG_PARAMETER(Length);
  
	Status = DppItemRead(L"QCOM", WLAN_PROV_FILENAME, &pBufferIn, &BufferInSize);
	if (Status || pBufferIn == NULL){
		DbgError("DppItemRead fail Status = 0X%X\n", Status);
		return 0;
	}

	/* Parse the WLAN.PROVISION format:
	  * Byte-0: version
	  * Byte-1: length
	  * Byte-2: num of mac
	  * Byte-3~8: STA mac
	  * Byte-9~14: SAP mac
	  * Byte-15~20: P2P Client mac
	  * Byte-21~26: P2P GO mac
	  */
	Version = pBufferIn[0];
    Length  = pBufferIn[1];
	NumOfMac = pBufferIn[2];

	/* Copy the STA MAC */
	CopyMem(MacAddr,&pBufferIn[3],ETH_ALEN);
	DbgInfo("Version-Length-Num: %d-%d-%d\n", Version, Length, NumOfMac);
	DbgInfo("MacAddr: %2X-%2X-%2X-%2X-%2X-%2X\n", MacAddr[0], MacAddr[1], MacAddr[2], 
		MacAddr[3], MacAddr[4], MacAddr[5]);
	
    if (pBufferIn != NULL)
	{
    	gBS->FreePool(pBufferIn);
    	pBufferIn = NULL;
  	}
	
    return NumOfMac;
}

EFI_STATUS DppGetWlanBdfPerName(struct firmware *FW, CHAR16 *FileName)
{
	EFI_STATUS Status  = EFI_SUCCESS;
	UINT8 *pBufferIn   = NULL;
	UINTN BufferInSize = 0;
	UINT32 BdfSize = 0;
	UINT8 *BdfData   = NULL;
  
    DbgInfo("Read %s\n", FileName);

	Status = DppItemRead (L"QCOM", FileName, &pBufferIn, &BufferInSize);
	if (Status){
		DbgError("DppItemRead fail Status = 0X%X\n", Status);
		return Status;
	}

    if (BufferInSize) {
    	BdfSize = (UINT32)BufferInSize;
		BdfData = kzalloc(BufferInSize, GFP_KERNEL);
		
		CopyMem(BdfData, pBufferIn, BufferInSize);
		FW->data = BdfData;
        FW->size = BdfSize;
    }
	
	if (pBufferIn != NULL)
	{
		gBS->FreePool(pBufferIn);
		pBufferIn = NULL;
	}
	
	return Status;
}

EFI_STATUS DppGetWlanBdf(struct firmware *FW, UINT32 BoardId, UINT32 ChipId)
{
    CHAR16 FileName[64] = { 0 };
    CHAR16 BoardIdExtension[4] = { 0 }, GfModuleExtension[4] = { 0 };
    EFI_STATUS Status;
 
    DbgInfo("BoardId = 0x%X, ChipId = 0x%X\n", BoardId, ChipId);
 
    if (ChipId & CHIP_ID_GF_MASK)
        UnicodeSPrint(GfModuleExtension, sizeof(GfModuleExtension), L".G");
 
    // 1) Get board id and chip id specified bdf
    if (BoardId != 0xFF) {
        UnicodeSPrint(BoardIdExtension, sizeof(BoardIdExtension), L".%02X", BoardId);
        UnicodeSPrint(FileName, sizeof(FileName), L"%s%s%s",
            WLAN_CLPC_PROVISION_DATA,
            BoardIdExtension, GfModuleExtension);
 
        Status = DppGetWlanBdfPerName(FW, FileName);
        if (!EFI_ERROR(Status))
            return Status;
    }

    // 2) Get WLAN_CLPC.PROVISION.G or WLAN_CLPC.PROVISION
    SetMem(FileName, sizeof(FileName), 0);
    UnicodeSPrint(FileName, sizeof(FileName), L"%s%s",
        WLAN_CLPC_PROVISION_DATA, GfModuleExtension);
    Status = DppGetWlanBdfPerName(FW, FileName);

    return Status;
}

