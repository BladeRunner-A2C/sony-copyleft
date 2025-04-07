/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 26/9/21   zxue     handle irq with budget
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <qdf/base_type.h>
#include <qdf/limits.h>
#include <qdf/errno.h>
#include <qdf/pr_debug.h>
#include <qdf/worker.h>
#include <qdf/qtime.h>
#include "interrupt.h"

#define SYNCHRONIZE_POLL_IRQ_TIMEOUT 5000

typedef struct __poll_irq
{
    u8 enabled;
    const u8 *name;
    irq_handler_t handler;
    void *dev;
} poll_irq_t;

static struct 
{
    poll_irq_t irqs[32];
} __g_poll_irq_context;

int __request_poll_irq(unsigned int irq, irq_handler_t handler,
    const char *name, void *dev)
{
    poll_irq_t *poll_irq;

    if (irq >= ARRAY_LENGTH(__g_poll_irq_context.irqs))
        return -EINVAL;
    if (handler == NULL)
        return -EINVAL;

    poll_irq = &__g_poll_irq_context.irqs[irq];
    if (poll_irq->handler) {
        return -EAGAIN;
    }

    poll_irq->name = (const u8 *)name;
    poll_irq->handler = handler;
    poll_irq->dev = dev;
    poll_irq->enabled = 1;

    return 0;
}

const void *__free_poll_irq(unsigned int irq, void *dev_id)
{
    const u8 *name;
    poll_irq_t *poll_irq;

    if (irq >= ARRAY_LENGTH(__g_poll_irq_context.irqs))
        return NULL;

    poll_irq = &__g_poll_irq_context.irqs[irq];
    if (!poll_irq->handler) {
        return NULL;
    }

    name = poll_irq->name;

    poll_irq->name = NULL;
    poll_irq->handler = NULL;
    poll_irq->dev = NULL;
    poll_irq->enabled = 0;

    return name;
}

void __enable_poll_irq(unsigned int irq)
{
    poll_irq_t *poll_irq;

    if (irq >= ARRAY_LENGTH(__g_poll_irq_context.irqs))
        return;

    poll_irq = &__g_poll_irq_context.irqs[irq];
    if (!poll_irq->handler) {
        return;
    }

    poll_irq->enabled = 1;
}

void __disable_poll_irq(unsigned int irq)
{
    poll_irq_t *poll_irq;

    if (irq >= ARRAY_LENGTH(__g_poll_irq_context.irqs))
        return;

    poll_irq = &__g_poll_irq_context.irqs[irq];
    if (!poll_irq->handler) {
        return;
    }

    poll_irq->enabled = 0;
}

void __synchronize_poll_irq(unsigned int irq)
{
    poll_irq_t *poll_irq;
    int work_done;
    u64 ctime, etime;

    poll_irq = &__g_poll_irq_context.irqs[irq];

    if (!poll_irq->enabled)
        return;

    pr_debug("poll for synchronize irq %d: timeout=[%d]\n",
        irq, SYNCHRONIZE_POLL_IRQ_TIMEOUT);

    etime = getwalltime_us() + SYNCHRONIZE_POLL_IRQ_TIMEOUT * 1000;
    do {
        work_done = poll_irq->handler(irq, INT_MAX, poll_irq->dev);
        if (!work_done) {
            ctime = getwalltime_us();
            break;
        }
        ctime = getwalltime_us();
    } while (ctime < etime);

    pr_debug("poll done for synchronize irq %d: ret=[%d]\n",
        irq, ((ctime < etime) ? ((etime - ctime) / 1000) : 0));
}

int __global_poll_irqs(int budget)
{
    u32 i;
    poll_irq_t *poll_irq;
    int work_done;
    u64 timeout = getwalltime_ms() + 10;  /* maximal 10ms time out */
    int ret = 0;

    for (i = 0; i < ARRAY_LENGTH(__g_poll_irq_context.irqs) && budget > 0; i++) {
        poll_irq = &__g_poll_irq_context.irqs[i];

        if (poll_irq->enabled && poll_irq->handler) {
            work_done = poll_irq->handler(i, budget, poll_irq->dev);
            if (work_done)
                budget -= work_done;
            if (getwalltime_ms() >= timeout) {
                ret = -ETIMEDOUT;
                break;
            }
        }
    }

    /* the work has the lower priority */
    if (!ret && budget > 0) {
        ret = invoke_pending_works(budget, timeout);
    }

    return ret;
}
