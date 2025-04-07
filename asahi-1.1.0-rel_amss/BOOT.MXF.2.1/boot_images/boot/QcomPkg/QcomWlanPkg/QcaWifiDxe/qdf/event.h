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

#ifndef __QDF_EVNET_H
#define __QDF_EVNET_H

#include <qdf/base_type.h>

struct timer;

typedef void (*timer_handler)(struct timer *t, void *context);

struct timer
{
    EFI_EVENT evt;
    timer_handler handler;
    void *context;
};

int __init_timer(struct timer *t, timer_handler handler, void *context);
int __set_timer(struct timer *t, u8 periodic, u32 ms);
int __cancel_timer(struct timer *t);
int __close_timer(struct timer *t);

static inline int init_timer(struct timer *t, timer_handler handler, void *context)
{
    return __init_timer(t, handler, context);
}

static inline int set_timer(struct timer *t, u8 periodic, u32 ms)
{
    return __set_timer(t, periodic, ms);
}

static inline int cancel_timer(struct timer *t)
{
    return __cancel_timer(t);
}

static inline int close_timer(struct timer *t)
{
    return __close_timer(t);
}

/***********************/

void __wait_for_enter_key(void);

static inline void wait_for_enter_key(void)
{
    __wait_for_enter_key();
}

#endif // !__QDF_EVNET_H

