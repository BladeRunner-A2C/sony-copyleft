/*
 * Copyright (c) 2020-2021, 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 26/9/21   zxue     invoke work with time out
 6/9/21    zxue     fix parasoft issue
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <qdf/qbase.h>
#include <qdf/wait.h>
#include "worker.h"

/*****************************************************************************/
/* work_struct */

static struct {
    u8 initialized;
    list_entry_t work_list;
    list_entry_t delayed_work_list;
} __global_work_context;

static inline void __init_global_work_context(void)
{
    __global_work_context.initialized = 1;
    list_init_head(&__global_work_context.work_list);
    list_init_head(&__global_work_context.delayed_work_list);
}

#if QDF_WORKER_DEBUG
int __init_work(struct work_struct *work, work_func_t execution, void *context,
    const char* func, unsigned long line)
#else
int __init_work(struct work_struct *work, work_func_t execution, void *context)
#endif //!QDF_WORKER_DEBUG
{
    if (!__global_work_context.initialized) {
        __init_global_work_context();
    }

    work->execution = execution;
    work->context = context;
    work->state = WORK_IDLE;

#if QDF_WORKER_DEBUG
    pr_raw_dbg("%a(%u): init work 0x%p(%u), execution=0x%p, context=0x%x\n",
        func, line, work, work->state, work->execution, work->context);
#endif

    return 0;
}

#if QDF_WORKER_DEBUG
int __close_work(struct work_struct *work, const char* func, unsigned long line)
#else
int __close_work(struct work_struct *work)
#endif //!QDF_WORKER_DEBUG
{
    if (work->state == WORK_QUEUED) {
        list_del(&work->node);
        work->state = WORK_IDLE;

#if QDF_WORKER_DEBUG
        pr_raw_dbg("%a(%u): close work 0x%p(%u)\n", func, line, work, work->state);
#endif
        return 0;
    }
    
    if (work->state == WORK_EXECUTING_QUEUED) {
        work->state = WORK_EXECUTING;
#if QDF_WORKER_DEBUG
        pr_raw_dbg("%a(%u): close work 0x%p(%u)\n", func, line, work, work->state);
#endif
        return -EBUSY;
    }

    return -EALREADY;
}

#if QDF_WORKER_DEBUG
int __schedule_work(struct work_struct *work, const char* func, unsigned long line)
#else
int __schedule_work(struct work_struct *work)
#endif //!QDF_WORKER_DEBUG
{
    if (work->state == WORK_QUEUED || 
        work->state == WORK_EXECUTING_QUEUED) {
        return -EAGAIN;
    }
    if (work->state == WORK_EXECUTING) {
        work->state = WORK_EXECUTING_QUEUED;
#if QDF_WORKER_DEBUG
        pr_raw_dbg("%a(%u): pending work 0x%p(%u), execution=0x%p, context=0x%x\n",
            func, line, work, work->state, work->execution, work->context);
#endif
        return -EALREADY;
    }

    work->state = WORK_QUEUED;
	list_add_tail(&work->node, &__global_work_context.work_list);

#if QDF_WORKER_DEBUG
    pr_raw_dbg("%a(%u): schedule work 0x%p(%u), execution=0x%p, context=0x%x\n",
        func, line, work, work->state, work->execution, work->context);
#endif

    return 0;
}

void __complete_work(struct work_struct *work)
{
    if (work->state == WORK_EXECUTING) {
        work->state = WORK_IDLE;
        return;
    }
    
    if (work->state == WORK_EXECUTING_QUEUED) {
        work->state = WORK_QUEUED;
		list_add_tail(&work->node, &__global_work_context.work_list);
#if QDF_WORKER_DEBUG
        pr_debug("reschedule work 0x%p(%u), execution=0x%p, context=0x%x\n",
            work, work->state, work->execution, work->context);
#endif
        return;
    }

#if QDF_WORKER_DEBUG
    pr_debug("complete work 0x%p(%u), execution=0x%p, context=0x%x unexpectedly\n",
        work, work->state, work->execution, work->context);
#endif
}

#if QDF_WORKER_DEBUG
int __flush_work(struct work_struct *work, const char* func, unsigned long line)
#else
int __flush_work(struct work_struct *work)
#endif //!QDF_WORKER_DEBUG
{
    if (work->state == WORK_QUEUED) {
        wait_queue_head_t wait;
        int time_left;

        // TODOTODO: A better way to flush work
        init_waitqueue_head(&wait);

        wait_event_timeout(wait, work->state != WORK_QUEUED, 120000, time_left);
        return time_left ? 0 : -ETIMEDOUT;
    }

    if (work->state == WORK_EXECUTING_QUEUED) {
        work->state = WORK_EXECUTING;
        return 0;
    }

    return -ENOLINK;
}

int __invoke_pending_works(int budget, u64 timeout)
{
    struct work_struct *work;
    int ret = 0;

    while (budget > 0) {
        if (timeout && getwalltime_ms() >= timeout) {
            ret = -ETIMEDOUT;
            break;
        }

        work = list_first_entry_or_null(
            &__global_work_context.work_list,
            struct work_struct, node);
        if (work == NULL) {
            ret = budget;
            break;
        }

        list_del(&work->node);
        if (work->execution) {
#if QDF_WORKER_DEBUG
            pr_debug("invoke work 0x%p(%u), execution=0x%p, context=0x%x\n",
                work, work->state, work->execution, work->context);
#endif
            work->state = WORK_EXECUTING;
            work->execution(work->context);
            budget--;
#if QDF_WORKER_DEBUG
            pr_debug("done work 0x%p(%u), execution=0x%p, context=0x%x\n",
                work, work->state, work->execution, work->context);
#endif
        }
        __complete_work(work);
    }

    return ret;
}

/*****************************************************************************/
/* delayed_work */

#if QDF_WORKER_DEBUG
int __init_delayed_work(struct delayed_work *work, work_func_t execution, void *context,
    const char* func, unsigned long line)
#else
int __init_delayed_work(struct delayed_work *work, work_func_t execution, void *context)
#endif //!QDF_WORKER_DEBUG
{
    if (!__global_work_context.initialized) {
        __init_global_work_context();
    }

    work->time_alloted = 0;
    work->work.execution = execution;
    work->work.context = context;
    work->work.state = WORK_IDLE;

#if QDF_WORKER_DEBUG
    pr_raw_dbg("%a(%u): init delayed work 0x%p(%u), execution=0x%p, context=0x%x\n",
        func, line, work, work->work.state, 
        work->work.execution, work->work.context);
#endif // !QDF_WORKER_DEBUG

    return 0;
}

static int __insert_delayed_work(struct delayed_work *work)
{
    struct delayed_work *cwork, *nwork = NULL;

    /* sort the delayed work based on time_alloted */
    list_for_each_entry(cwork,
        &__global_work_context.delayed_work_list,
        struct delayed_work, work.node) {

        /* already in the queue, should not happen */
        if (cwork == work)
            return -EAGAIN;

        if (cwork->time_alloted > work->time_alloted) {
            nwork = cwork;
            break;
        }
    }

    /* add to the queue */
    work->work.state = WORK_QUEUED;
    if (!nwork) {
		list_add_tail(&work->work.node, &__global_work_context.delayed_work_list);
    }
    else {
        list_insert_before(&__global_work_context.delayed_work_list,
            &nwork->work.node, &work->work.node);
    }

    return 0;
}

#if QDF_WORKER_DEBUG
int __queue_delayed_work(struct delayed_work *work, u32 delay,
    const char* func, unsigned long line)
#else
int __queue_delayed_work(struct delayed_work *work, u32 delay)
#endif //!QDF_WORKER_DEBUG
{
    int ret;

    if (work->work.state == WORK_QUEUED ||
        work->work.state == WORK_EXECUTING_QUEUED) {
        return -EAGAIN;
    }

    work->time_alloted = getwalltime_us() + delay * 1000;

    if (work->work.state == WORK_EXECUTING) {
        work->work.state = WORK_EXECUTING_QUEUED;    
#if QDF_WORKER_DEBUG
        pr_raw_dbg("%a(%u): pending delayed work 0x%p(%u), execution=0x%p, context=0x%x\n",
            func, line, work, work->work.state, work->work.execution, work->work.context);
#endif
        return -EALREADY;
    }

    ret = __insert_delayed_work(work);

#if QDF_WORKER_DEBUG
    if (!ret) {
        pr_raw_dbg("%a(%u): queue delayed work 0x%p(%u), execution=0x%p, context=0x%x, time_alloted=%u\n",
            func, line, work, work->work.state, work->work.execution,
            work->work.context, work->time_alloted);
    }
#endif

    return ret;
}

void __complete_delayed_work(struct delayed_work *work)
{
    if (work->work.state == WORK_EXECUTING) {
        work->work.state = WORK_IDLE;
        return;
    }

    if (work->work.state == WORK_EXECUTING_QUEUED) {
        __insert_delayed_work(work);
#if QDF_WORKER_DEBUG
        pr_debug("requeued delayed work 0x%p(%u), execution=0x%p, context=0x%x\n",
            work, work->work.state, work->work.execution, work->work.context);
#endif
        return;
    }

#if QDF_WORKER_DEBUG
    pr_warn("complete delayed work 0x%p(%u), execution=0x%p, context=0x%x unexpectedly\n",
        work, work->work.state, work->work.execution, work->work.context);
#endif
}

#if QDF_WORKER_DEBUG
int __cancel_delayed_work(struct delayed_work *work, const char* func, unsigned long line)
#else
int __cancel_delayed_work(struct delayed_work *work)
#endif //!QDF_WORKER_DEBUG
{
    if (work->work.state == WORK_QUEUED) {
        list_del(&work->work.node);
        work->work.state = WORK_IDLE;

#if QDF_WORKER_DEBUG
        pr_raw_dbg("%a(%u): cancel delayed work 0x%p(%u), execution=0x%p, context=0x%x, time_alloted=%u\n",
            func, line, work, work->work.state, work->work.execution,
            work->work.context, work->time_alloted);
#endif
        return 0;
    }

    if (work->work.state == WORK_EXECUTING_QUEUED) {
        work->work.state = WORK_EXECUTING;
#if QDF_WORKER_DEBUG
        pr_raw_dbg("%a(%u): cancel delayed work 0x%p(%u), execution=0x%p, context=0x%x, time_alloted=%u\n",
            func, line, work, work->work.state, work->work.execution,
            work->work.context, work->time_alloted);
#endif
        return 0;
    }

    return -EALREADY;
}

int __invoke_pending_delayed_works(int budget, u64 timeout)
{
    struct delayed_work *work;
    u64 now = getwalltime_us();
    int ret = 0;

    while (budget > 0) {
        if (timeout && getwalltime_ms() >= timeout) {
            ret = -ETIMEDOUT;
            break;
        }

        work = list_first_entry_or_null(
            &__global_work_context.delayed_work_list,
            struct delayed_work, work.node);
        if (work == NULL) {
            ret = budget;
            break;
        }

        if (now < work->time_alloted) {
            ret = budget;
            break;
        }

        WARN_ON(work->work.state != WORK_QUEUED);

        /* wall time beyond the alloted time */
        list_del(&work->work.node);

        if (work->work.execution) {
#if QDF_WORKER_DEBUG
            pr_debug("invoke delayed work 0x%p(%u), execution=0x%p, context=0x%x\n",
                work, work->work.state, work->work.execution, work->work.context);
#endif
            work->work.state = WORK_EXECUTING;
            work->work.execution(work->work.context);
            budget--;
#if QDF_WORKER_DEBUG
            pr_debug("done delayed work done 0x%p(%u), execution=0x%p, context=0x%x\n",
                work, work->work.state, work->work.execution, work->work.context);
#endif
        }
        __complete_delayed_work(work);
    }

    return ret;
}
