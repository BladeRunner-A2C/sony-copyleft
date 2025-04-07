/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <Library/UefiBootServicesTableLib.h>
#include "atomic.h"

int __atomic_cmpxchg(atomic_t *addr, u32 oldval, u32 newval)
{
    /* Raise TPL to be sure there is no other S */
    EFI_TPL PreviousTpl = gBS->RaiseTPL(TPL_HIGH_LEVEL);
    atomic_t lval = *addr;

    if (lval == oldval)
        *addr = newval;

    /* Restore the TPL after operation complete */
    gBS->RestoreTPL(PreviousTpl);
    return lval;
}

u32 __atomic_read(const atomic_t *addr)
{
    /* Raise TPL to be sure there is no other modifier */
    EFI_TPL PreviousTpl = gBS->RaiseTPL(TPL_HIGH_LEVEL);
    atomic_t lval = *addr;
    gBS->RestoreTPL(PreviousTpl);
    return lval;
}

int __atomic_inc(atomic_t *addr)
{
    /* Raise TPL to be sure there is no other modifier */
    EFI_TPL PreviousTpl = gBS->RaiseTPL(TPL_HIGH_LEVEL);
    atomic_t lval = *addr;

    *addr += 1;

    /* Restore the TPL after operation complete */
    gBS->RestoreTPL(PreviousTpl);
    return lval;
}

int __atomic_dec(atomic_t *addr)
{
    /* Raise TPL to be sure there is no other modifier */
    EFI_TPL PreviousTpl = gBS->RaiseTPL(TPL_HIGH_LEVEL);
    atomic_t lval = *addr;

    *addr -= 1;

    gBS->RestoreTPL(PreviousTpl);
    return lval;
}

int __atomic_set(atomic_t *addr, u32 newval)
{
    /* Raise TPL to be sure there is no other modifier */
    EFI_TPL PreviousTpl = gBS->RaiseTPL(TPL_HIGH_LEVEL);
    *addr = newval;
    gBS->RestoreTPL(PreviousTpl);
    return newval;
}

int __atomic_dec_and_test(atomic_t *addr)
{
    /* Raise TPL to be sure there is no other modifier */
    EFI_TPL PreviousTpl = gBS->RaiseTPL(TPL_HIGH_LEVEL);
    atomic_t lval = *addr;
    *addr -= 1;
    gBS->RestoreTPL(PreviousTpl);
    return (lval == 1) ? 1 : 0;
}

bool
__atomic_try_cmpxchg(atomic_t *addr, u32 *oldv, u32 newv)
{
    u32 rdv, cmpv = *oldv;
    rdv = __atomic_cmpxchg(addr, cmpv, newv);
    if (unlikely(rdv != cmpv)) {
        *oldv = rdv;
        return false;
    }

    return true;
}