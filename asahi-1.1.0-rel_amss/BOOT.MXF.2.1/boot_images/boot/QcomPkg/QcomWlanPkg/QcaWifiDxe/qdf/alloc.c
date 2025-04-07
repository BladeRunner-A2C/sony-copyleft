/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 21/12/21  zxue     Add a mechanism to check the memory issue 
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include "alloc.h"

typedef struct {
    UINT32 Signature;
    UINT32 Size;
    VOID *Address;
} BUFFER_HEADER;

#define BUFFER_HEADER_SIGNATURE SIGNATURE_32('H', 'E', 'A', 'D')
#define BUFFER_HEADER_GET(_Address, _Offset) (((UINT8 *)(_Address) - (_Offset)))

VOID QdfFreePoolDebug(
    IN VOID *Buffer,
    IN CONST CHAR8 *Func,
    IN UINT32 Line)
{
    BUFFER_HEADER *BufferHeader;

    if (Buffer == NULL) {
        DbgRaw(WLAN_LOG_LEVEL_WARN, "%a(%d): memeory free NULL\n", Func, Line);
        return;
    }

    BufferHeader = (BUFFER_HEADER *)BUFFER_HEADER_GET(Buffer, sizeof(BUFFER_HEADER));

    if ((BufferHeader->Signature != BUFFER_HEADER_SIGNATURE) ||
        (BufferHeader->Address != Buffer)) {
        DbgRaw(WLAN_LOG_LEVEL_ERROR,
            "%a(%d): ERROR: memory free 0x%p(%d) with header: signature=0x%08X, address=0x%p, size=%d\n",
            Func, Line, Buffer, BufferHeader->Size, BufferHeader->Signature, BufferHeader->Address, BufferHeader->Size);
    }
    else {
        DbgRaw(WLAN_LOG_LEVEL_INFO, "%a(%d): memory free 0x%p(%d)\n", Func, Line, Buffer, BufferHeader->Size);
    }

    FreePool(BufferHeader);
}

VOID *QdfAllocatePoolDebug(
    IN UINTN AllocationSize,
    IN CONST CHAR8 *Func,
    IN UINT32 Line)
{
    BUFFER_HEADER *BufferHeader;

    BufferHeader = AllocatePool(AllocationSize + sizeof(BUFFER_HEADER));
    if (BufferHeader) {
        BufferHeader->Signature = BUFFER_HEADER_SIGNATURE;
        BufferHeader->Size = (UINT32)AllocationSize;
        BufferHeader->Address = (UINT8*)BufferHeader + sizeof(BUFFER_HEADER);

        DbgRaw(WLAN_LOG_LEVEL_INFO,
            "%a(%d): memory allocated 0x%p(%d)\n",
            Func, Line, BufferHeader->Address, BufferHeader->Size);

        return BufferHeader->Address;
    }

    return NULL;
}

VOID *QdfAllocateZeroPoolDebug(
    IN UINTN AllocationSize,
    IN CONST CHAR8 *Func,
    IN UINT32 Line)
{
    VOID *Buffer = QdfAllocatePoolDebug(AllocationSize, Func, Line);

    if (Buffer) {
        ZeroMem(Buffer, AllocationSize);
        return Buffer;
    }

    return NULL;
}