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

#ifndef __QDF_LOCK_H
#define __QDF_LOCK_H

#include <qdf/base_type.h>


 /*****************************************************************************/
 /* TODOTODO: to review the related code */
struct rwlock {
    u8 locked;
};

struct spinlock {
    u8 locked;
};

typedef struct rwlock rwlock_t;
typedef struct spinlock spinlock_t;

#define read_lock_bh(l) (void)(l)
#define read_unlock_bh(l) (void)(l)

#define write_lock_irqsave(l, f) ((f) = 1)
#define write_unlock_irqrestore(l, f) ((f) = 0)

#define read_lock_irqsave(l, f) ((f) = 1)
#define read_unlock_irqrestore(l, f) ((f) = 0)

#define spin_lock(l) (void)(l)
#define spin_unlock(l) (void)(l)

#define spin_lock_bh(l) (void)(l)
#define spin_unlock_bh(l) (void)(l)

#define write_lock_irq(l) (void)(l)
#define write_unlock_irq(l) (void)(l)

#define spin_lock_irqsave(l, f) ((f) = 1)
#define spin_unlock_irqrestore(l, f) ((f) = 0)

#define smp_wmb MemoryFence

static inline void rcu_read_lock(void) {}
static inline void rcu_read_unlock(void) {}

static inline void synchronize_rcu(void) {}

struct mutex {
    u8 locked;
};

#define MUTEX_INIT(v) {					     \
	.locked = v,			                 \
}

#define DEFINE_MUTEX(name)	struct mutex name = MUTEX_INIT(0)

#define mutex_init(m) (void)(m)
#define mutex_destroy(m) (void)(m)
#define mutex_lock(m) (void)(m)
#define mutex_unlock(m) (void)(m)

#define read_lock_irq(m) (void)(m)
#define	read_unlock_irq(m) (void)(m)

#define rwlock_init(l) (void)(l)
#define	spin_lock_init(l) (void)(l)
#define	spin_lock_init(l) (void)(l)

#define spin_lock_irq(l) (void)(l)
#define spin_unlock_irq(l) (void)(l)

#define write_lock_bh(l) (void)(l)
#define write_unlock_bh(l) (void)(l)

#define rtnl_lock()
#define rtnl_unlock()
#define synchronize_net()

#define local_bh_disable()
#define local_bh_enable()

#define lockdep_assert_held(_x)

/* RCU */
#define __rcu
#define rcu_dereference(_x) (_x)
#define rcu_dereference_rtnl(_x)    (_x)
#define rcu_assign_pointer(_gbl_foo, _new_fp)   ((_gbl_foo) = (_new_fp))
#define rcu_access_pointer(_x)  (_x)

#endif // !__QDF_LOCK_H

