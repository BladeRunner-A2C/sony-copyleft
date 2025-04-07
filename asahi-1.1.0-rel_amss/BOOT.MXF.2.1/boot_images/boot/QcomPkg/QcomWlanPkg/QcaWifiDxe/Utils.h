/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 6/9/21    zxue     fix parasoft issue
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __EFI_UTILS_H
#define __EFI_UTILS_H

#include <Uefi.h>
#include <Library/BaseLib.h>

// Base Types
#define LE16(p) (*((UINT16 *)p))

STATIC inline
UINT32
GetBe32(CONST UINT8 *a)
{
    return ((UINT32)a[0] << 24) | (a[1] << 16) | (a[2] << 8) | a[3];
}

// Wall Timer
typedef UINT64 MILLISECOND_TYPE;
typedef UINT64 MICROSECOND_TYPE;

VOID WallTimerAttach(VOID);
VOID WallTimerDetach(VOID);

MILLISECOND_TYPE GetTimeInMillisecond(VOID);

STATIC inline MICROSECOND_TYPE GetTimeInMicrosecond(VOID)
{
    return GetTimeInMillisecond() * 1000;
}

// List Helpers
STATIC inline VOID __ListInsert(LIST_ENTRY *NewEntry,
    LIST_ENTRY *PrevEntry, LIST_ENTRY *NextEntry,
    LIST_ENTRY *ListHead)
{
    NewEntry->ForwardLink = NextEntry;
    NewEntry->BackLink = PrevEntry;
    NextEntry->BackLink = NewEntry;
    PrevEntry->ForwardLink = NewEntry;
}

STATIC inline LIST_ENTRY *InsertListBefore(LIST_ENTRY *ListHead,
    LIST_ENTRY *NextEntry, LIST_ENTRY *NewEntry)
{
    __ListInsert(NewEntry, GetPreviousNode(ListHead, NextEntry), NextEntry, ListHead);
    return ListHead;
}

#endif // !__EFI_UTILS_H