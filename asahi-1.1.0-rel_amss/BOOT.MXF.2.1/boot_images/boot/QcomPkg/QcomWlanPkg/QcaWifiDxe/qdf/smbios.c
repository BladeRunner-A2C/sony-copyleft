/*
 * Copyright (c) 2022-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
  This code produces the Smbios protocol. It also responsible for constructing
  SMBIOS table into system table.

  Copyright (c) 2009 - 2018, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include "Debug.h"
#include <Uefi.h>
#include <qdf/smbios.h>
#include <qdf/alloc.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <IndustryStandard/SmBios.h>
#include <Protocol/Smbios.h>

#if SUPPORT_SMBIOS_CFG

/**
  source:
  Get the full size of SMBIOS structure including optional strings that follow the formatted structure.

  @param This                   The EFI_SMBIOS_PROTOCOL instance.
  @param Head                  Pointer to the beginning of SMBIOS structure.
  @param Size                   The returned size.
  @param NumberOfStrings  The returned number of optional strings that follow the formatted structure.

  @retval EFI_SUCCESS           Size retured in Size.
  @retval EFI_INVALID_PARAMETER Input SMBIOS structure mal-formed or Size is NULL.

**/

extern EFI_GUID gEfiSmbiosProtocolGuid;

#define SMBIOS_INFORMATION_FIELD_DB 0x01        // DEFINE BYTE
#define SMBIOS_INFORMATION_FIELD_DW 0x02        // DEFINE WORD
#define SMBIOS_INFORMATION_FIELD_DD 0x03        // DEFINE DOUBLE WORD
#define SMBIOS_INFORMATION_FIELD_DQ 0x04        // DEFINE QUARTET WORD
#define SMBIOS_INFORMATION_FIELD_DS 0x05        // DEFINE STRING

typedef struct
{
    UINT8 Offset;
    UINT8 Type;
    union
    {
        UINT8  BVal;
        UINT16 WVal;
        UINT32 DWVal;
        UINT64 QWVal;
        UINT8  SVal[256];
    }u;
} SMBIOS_INFORMATION_FIELD;

/* Support 11ac/ax configure, country code setting, BDF name extension by smbios */
/* Qualcomm proposal smbios format */
#define  SMBIOS_CFG_PARA_TYPE             0xF8
#define  SMBIOS_CFG_PARA_11AC_OFFSET      0x04
#define  SMBIOS_CFG_PARA_CC_FLAG_OFFSET   0x05
#define  SMBIOS_CFG_PARA_CC_VALUE_OFFSET  0x06
#define  SMBIOS_CFG_PARA_BDF_EXT_OFFSET   0x08

EFI_STATUS
EFIAPI
GetSmbiosStructureSize(
    IN   CONST EFI_SMBIOS_PROTOCOL        *This,
    IN   EFI_SMBIOS_TABLE_HEADER          *Head,
    OUT  UINTN                            *Size,
    OUT  UINTN                            *NumberOfStrings
)
{
    UINTN  FullSize;
    UINTN  StrLen;
    UINTN  MaxLen;
    INT8*  CharInStr;

    if (Size == NULL || NumberOfStrings == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    FullSize = Head->Length;
    CharInStr = (INT8*)Head + Head->Length;
    *Size = FullSize;
    *NumberOfStrings = 0;
    StrLen = 0;
    //
    // look for the two consecutive zeros, check the string limit by the way.
    //
    while (*CharInStr != 0 || *(CharInStr + 1) != 0) {
        if (*CharInStr == 0) {
            *Size += 1;
            CharInStr++;
        }

        if (This->MajorVersion < 2 || (This->MajorVersion == 2 && This->MinorVersion < 7)) {
            MaxLen = SMBIOS_STRING_MAX_LENGTH;
        }
        else if (This->MajorVersion < 3) {
            //
            // Reference SMBIOS 2.7, chapter 6.1.3, it will have no limit on the length of each individual text string.
            // However, the length of the entire structure table (including all strings) must be reported
            // in the Structure Table Length field of the SMBIOS Structure Table Entry Point,
            // which is a WORD field limited to 65,535 bytes.
            //
            MaxLen = SMBIOS_TABLE_MAX_LENGTH;
        }
        else {
            //
            // SMBIOS 3.0 defines the Structure table maximum size as DWORD field limited to 0xFFFFFFFF bytes.
            // Locate the end of string as long as possible.
            //
            MaxLen = SMBIOS_3_0_TABLE_MAX_LENGTH;
        }

        for (StrLen = 0; StrLen < MaxLen; StrLen++) {
            if (*(CharInStr + StrLen) == 0) {
                break;
            }
        }

        if (StrLen == MaxLen) {
            return EFI_INVALID_PARAMETER;
        }

        //
        // forward the pointer
        //
        CharInStr += StrLen;
        *Size += StrLen;
        *NumberOfStrings += 1;
    }

    //
    // count ending two zeros.
    //
    *Size += 2;
    return EFI_SUCCESS;
}

UINT32 SmbiosInformationString(UINT8 *Strings, UINT8 *SEnd, UINT8 Index, UINT8 *SVal, UINT32 SLen)
{
    // index started from 1.
    UINT8 i = 1;
    // the position in current string.
    UINT32 SPos = 0;

    do {
        if (Strings + 2 > SEnd)
            break;

        if (Strings[0] != 0) {
            Strings++;
            SPos++;
            continue;
        }

        if (Index == i) {
            if (SPos + 1 > SLen)
                break;
            CopyMem(SVal, Strings - (SPos++), SPos);
            return SPos;
        }

        Strings++;
        SPos = 0;
        i++;

        // End of the strings.
        if (Strings[0] == 0)
            break;
    } while (TRUE);

    return 0;
}

UINT32 SmbiosInformationField(UINT8 *Info, UINT8 *IEnd, SMBIOS_INFORMATION_FIELD *Field)
{
    UINT8 Length;

    if (Info == NULL || Info + sizeof(EFI_SMBIOS_TABLE_HEADER) > IEnd || Field == NULL)
        return 0;

    Length = ((EFI_SMBIOS_TABLE_HEADER *)Info)->Length;

    switch (Field->Type)
    {
    case SMBIOS_INFORMATION_FIELD_DS:
        if (Info + Length > IEnd || Length < (Field->Offset + sizeof(UINT8)))
            return 0;
        return SmbiosInformationString(Info + Length, IEnd, ((UINT8*)(Info + Field->Offset))[0], Field->u.SVal, sizeof(Field->u.SVal));
    case SMBIOS_INFORMATION_FIELD_DB:
        if (Info + Length > IEnd || Length < (Field->Offset + sizeof(UINT8)))
            return 0;
        Field->u.BVal = ((UINT8*)(Info + Field->Offset))[0];
        return sizeof(UINT8);
    case SMBIOS_INFORMATION_FIELD_DW:
        if (Info + Length > IEnd || Length < (Field->Offset + sizeof(UINT16)))
            return 0;
        Field->u.WVal = ((UINT16*)(Info + Field->Offset))[0];
        return sizeof(UINT16);
    case SMBIOS_INFORMATION_FIELD_DD:
        if (Info + Length > IEnd || Length < (Field->Offset + sizeof(UINT32)))
            return 0;
        Field->u.DWVal = ((UINT32*)(Info + Field->Offset))[0];
        return sizeof(UINT32);
    case SMBIOS_INFORMATION_FIELD_DQ:
        if (Info + Length > IEnd || Length < (Field->Offset + sizeof(UINT64)))
            return 0;
        Field->u.QWVal = ((UINT64*)(Info + Field->Offset))[0];
        return sizeof(UINT64);
    }

    return 0;
}

/* Qca defined smbios format read method */
BOOLEAN SmbiosParaRead(EFI_SMBIOS_TABLE_HEADER *Information, P_SMBIOS_CFG SmbiosCfg, UINT8 *Ielend)
{
    SMBIOS_INFORMATION_FIELD NeedField = { 0 };
    UINT32 Size = 0;

    /* Read 11AC/AX cfg from smbios */
    NeedField.Type = SMBIOS_INFORMATION_FIELD_DB;
    NeedField.Offset = SMBIOS_CFG_PARA_11AC_OFFSET;

    if (0 == (Size = SmbiosInformationField((UINT8 *)Information, Ielend, &NeedField)))
        return FALSE;

    SmbiosCfg->ACAXCfg = NeedField.u.BVal;

    /* Read country code setting flag from smbios */
    SetMem(&NeedField, sizeof(NeedField), 0);
    NeedField.Type = SMBIOS_INFORMATION_FIELD_DB;
    NeedField.Offset = SMBIOS_CFG_PARA_CC_FLAG_OFFSET;

    if (0 == (Size = SmbiosInformationField((UINT8 *)Information, Ielend, &NeedField)))
        return FALSE;

    SmbiosCfg->CCSetFlag = NeedField.u.BVal;

    /* Read country code value or WWR from smbios */
    SetMem(&NeedField, sizeof(NeedField), 0);
    NeedField.Type = SMBIOS_INFORMATION_FIELD_DW;
    NeedField.Offset = SMBIOS_CFG_PARA_CC_VALUE_OFFSET;

    if (0 == (Size = SmbiosInformationField((UINT8 *)Information, Ielend, &NeedField)))
        return FALSE;

    SmbiosCfg->u.CCValue = NeedField.u.WVal;

    /* Read BDF extension name from smbios */
    SetMem(&NeedField, sizeof(NeedField), 0);
    NeedField.Type = SMBIOS_INFORMATION_FIELD_DS;
    NeedField.Offset = SMBIOS_CFG_PARA_BDF_EXT_OFFSET;

    if (0 != (Size = SmbiosInformationField((UINT8 *)Information, Ielend, &NeedField))) {
        /* with string */
        if (Size > VENDER_BDF_EXT_MAX_LEN) {
            return FALSE;
        }
        else {
            CopyMem(SmbiosCfg->VenderBdfString, NeedField.u.SVal, Size);
            DbgPrint("bdf = %a", SmbiosCfg->VenderBdfString);
        }
    }

    return TRUE;
}

EFI_STATUS SmbiosGetWlanCfg(P_SMBIOS_CFG SmbiosCfg)
{
    EFI_STATUS                      Status = EFI_SUCCESS;
    EFI_SMBIOS_HANDLE               SmbiosHandle;
    EFI_SMBIOS_PROTOCOL             *SmbiosProtocol;
    EFI_SMBIOS_TABLE_HEADER         *SmbiosRecord;

    UINT8                           *BufferPointer = NULL;
    UINT8                           *Iend;
    UINTN                           RecordSize = 0;
    UINTN                           NumOfStr = 0;
    BOOLEAN                         BVal = FALSE;

    Status = gBS->LocateProtocol(&gEfiSmbiosProtocolGuid, NULL, (VOID **)&SmbiosProtocol);
    if (EFI_ERROR(Status)) {
        DbgError("Fail to locate gEfiSmbiosProtocolGuid.\n");
        return Status;
    }

    SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
    Status = SmbiosProtocol->GetNext(SmbiosProtocol, &SmbiosHandle, NULL, &SmbiosRecord, NULL);
    while (!EFI_ERROR(Status)) {
        if (SmbiosRecord->Type == SMBIOS_CFG_PARA_TYPE) {
            DbgInfo("Succ get the record of SMBIOS_CFG_PARA_TYPE\n");

            Status = GetSmbiosStructureSize(SmbiosProtocol, SmbiosRecord, &RecordSize, &NumOfStr);
            if (Status == EFI_SUCCESS) {
                BufferPointer = AllocateZeroPool(RecordSize);
                CopyMem(BufferPointer, SmbiosRecord, RecordSize);
                break;
            }
        }
        Status = SmbiosProtocol->GetNext(SmbiosProtocol, &SmbiosHandle, NULL, &SmbiosRecord, NULL);
    }

	if (BufferPointer == NULL) {
		DbgInfo("DO NOT support the wlan configure from SMBIOS.\n");
		return EFI_UNSUPPORTED;
	}

    Iend = BufferPointer + RecordSize;
    BVal = SmbiosParaRead((EFI_SMBIOS_TABLE_HEADER *)BufferPointer, SmbiosCfg, Iend);

    if (BufferPointer)
        FreePool(BufferPointer);

    if (BVal)
        Status = EFI_SUCCESS;

    return Status;
}

#endif /* SUPPORT_SMBIOS_CFG */
