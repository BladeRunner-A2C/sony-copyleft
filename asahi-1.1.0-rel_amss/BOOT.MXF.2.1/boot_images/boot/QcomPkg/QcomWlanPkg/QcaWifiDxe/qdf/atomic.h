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

#ifndef __QDF_ATOMIC_H
#define __QDF_ATOMIC_H

#include <qdf/base_type.h>
#include <qdf/compile_type.h>

typedef u32 atomic_t;
typedef u64 atomic64_t;

/*
 * Atomic operations that C can't guarantee us.  Useful for
 * resource counting etc..
 */

#define ATOMIC_INIT(i)	{ (i) }

/* implementation */
int __atomic_cmpxchg(atomic_t *addr, u32 oldval, u32 newval);
u32 __atomic_read(const atomic_t *addr);
int __atomic_inc(atomic_t *addr);
int __atomic_dec(atomic_t *addr);
int __atomic_set(atomic_t *addr, u32 newval);
int __atomic_dec_and_test(atomic_t *addr);
bool __atomic_try_cmpxchg(atomic_t *addr, u32 *oldv, u32 newv);

static inline int atomic_cmpxchg(atomic_t *addr, u32 oldval, u32 newval)
{
    return __atomic_cmpxchg(addr, oldval, newval);
}

static inline u32 atomic_read(const atomic_t *addr)
{
    return __atomic_read(addr);
}

static inline int atomic_inc(atomic_t *addr)
{
    return __atomic_inc(addr);
}

static inline int atomic_dec(atomic_t *addr)
{
    return __atomic_dec(addr);
}

static inline int atomic_set(atomic_t *addr, u32 newval)
{
    return __atomic_set(addr, newval);
}

static inline int
atomic_dec_and_test(atomic_t *addr)
{
    return __atomic_dec_and_test(addr);
}

static inline int
atomic_inc_return(atomic_t *addr)
{
    return __atomic_inc(addr);
}

static inline int
atomic_dec_return(atomic_t *addr)
{
    return __atomic_dec(addr);
}

static inline int
atomic_fetch_add_unless(atomic_t *addr, int a, int u)
{
    u32 c = *addr;

    for (;;) {
        if (unlikely(c == (u32)u))
            break;
        if (likely(__atomic_try_cmpxchg(addr, &c, c + a)))
            break;
    }
    return (c);
}

static inline bool
atomic_add_unless(atomic_t *addr, int a, int u)
{
    return atomic_fetch_add_unless(addr, a, u) != u;
}

#endif // !__QDF_ATOMIC_H

