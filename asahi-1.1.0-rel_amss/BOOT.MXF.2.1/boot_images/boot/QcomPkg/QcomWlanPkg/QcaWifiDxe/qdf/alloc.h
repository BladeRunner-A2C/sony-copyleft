/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 28/2/22   zxue     fix the assert issue when free null pointer 
 21/12/21  zxue     Add a mechanism to check the memory issue 
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QDF_ALLOC_H
#define __QDF_ALLOC_H
#include <Library/MemoryAllocationLib.h>
#include <qdf/base_type.h>
#include <qdf/stdio.h>
#include <qdf/pr_debug.h>

#if SUPPORT_DEBUG_PRINT
#define SUPPORT_MEMORY_DEBUG_PRINT 1
#endif

VOID *QdfAllocatePoolDebug(IN UINTN Size, IN CONST CHAR8 *Func, IN UINT32 Line);
VOID *QdfAllocateZeroPoolDebug(IN UINTN Size, IN CONST CHAR8 *Func, IN UINT32 Line);
VOID QdfFreePoolDebug(IN VOID *Buffer, IN CONST CHAR8 *Func, IN UINT32 Line);

#if SUPPORT_MEMORY_DEBUG_PRINT

#define QdfAllocatePool(_Size) QdfAllocatePoolDebug((_Size), __FUNCTION__, __LINE__)
#define QdfAllocateZeroPool(_Size) QdfAllocateZeroPoolDebug((_Size), __FUNCTION__, __LINE__)
#define QdfFreePool(_Buffer) QdfFreePoolDebug((_Buffer), __FUNCTION__, __LINE__)

#else

#define QdfAllocatePool(_Size) AllocatePool((_Size))
#define QdfAllocateZeroPool(_Size) AllocateZeroPool(_Size)
#define QdfFreePool(_Buffer) do {        \
        if (_Buffer)                     \
            FreePool((VOID *)_Buffer);   \
     } while (0)
#endif


/* allocate flags */
#define GFP_KERNEL 0 /* not used */
#define GFP_ATOMIC 1 /* not used */

#define kzfree(_buffer) QdfFreePool((VOID *)_buffer)
#define kfree(_buffer) QdfFreePool((VOID *)_buffer)
#define vfree(_buffer) QdfFreePool((VOID *)_buffer)
#define kzalloc(_size, _flags) QdfAllocateZeroPool(_size)
#define kcalloc(_n, _size, _flags) QdfAllocateZeroPool((_n) * (_size))
#define kmalloc(_size, _flags) QdfAllocatePool(_size)
#define vzalloc(_size) QdfAllocateZeroPool(_size)
#define vmalloc(_size) QdfAllocatePool(_size)


static inline void* kmemdup(const void* src, size_t len, int flags)
{
    void* ptr;

    ptr = kmalloc(len, flags);
    if (ptr) {
        memcpy(ptr, src, len);
    }

    return ptr;
}

#endif // !__QDF_ALLOC_H

