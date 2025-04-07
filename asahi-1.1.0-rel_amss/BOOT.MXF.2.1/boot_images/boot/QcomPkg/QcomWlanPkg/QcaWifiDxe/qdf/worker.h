/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 26/9/21   zxue     invoke work with time out
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QDF_WORKER_H
#define __QDF_WORKER_H

#include <qdf/base_type.h>
#include <qdf/list.h>
#include <qdf/pr_debug.h>

#if SUPPORT_DEBUG_PRINT
#define QDF_WORKER_DEBUG 1
#endif

/*****************************************************************************/
/* work_struct */

typedef void(*work_func_t)(void *context);

enum work_state
{
    WORK_IDLE             = 0,
    WORK_QUEUED           = 1,
    WORK_EXECUTING        = 2,
    WORK_EXECUTING_QUEUED = 3,
};

struct work_struct
{
    list_entry_t node;
    work_func_t execution;
    void *context;
    enum work_state state;
};

#if QDF_WORKER_DEBUG

int __init_work(struct work_struct *work, work_func_t execution, void *context,
    const char* func, unsigned long line);
int __close_work(struct work_struct *work, const char* func, unsigned long line);
int __schedule_work(struct work_struct *work, const char* func, unsigned long line);
int __flush_work(struct work_struct *work, const char* func, unsigned long line);

#else // !QDF_WORKER_DEBUG

int __init_work(struct work_struct *work, work_func_t execution, void *context);
int __close_work(struct work_struct *work);
int __schedule_work(struct work_struct *work);
int __flush_work(struct work_struct *work);

#endif // !QDF_WORKER_DEBUG

#if QDF_WORKER_DEBUG

#define init_work(_w, _e, _c) __init_work(_w, _e, _c, __FUNCTION__, __LINE__)
#define close_work(_w) __close_work(_w, __FUNCTION__, __LINE__)
#define cancel_work_sync(_w) __close_work(_w, __FUNCTION__, __LINE__)
#define schedule_work(_w) __schedule_work(_w, __FUNCTION__, __LINE__)
#define flush_work(_w) __flush_work(_w, __FUNCTION__, __LINE__)

#else // !QDF_WORKER_DEBUG

static inline int init_work(struct work_struct *work, work_func_t execution, void *context)
{
    return __init_work(work, execution, context);
}

static inline int close_work(struct work_struct *work)
{
    return __close_work(work);
}

static inline int cancel_work_sync(struct work_struct *work)
{
    return __close_work(work);
}

static inline int flush_work(struct work_struct *work)
{
    return __flush_work(work);
}

static inline int schedule_work(struct work_struct *work)
{
    return __schedule_work(work);
}

#endif //!QDF_WORKER_DEBUG

/*****************************************************************************/
/* delayed_work */
struct delayed_work
{
    struct work_struct work;
    u64 time_alloted;
};

#if QDF_WORKER_DEBUG

int __init_delayed_work(struct delayed_work *work, work_func_t execution, void *context,
    const char* func, unsigned long line);
int __cancel_delayed_work(struct delayed_work *work, 
    const char* func, unsigned long line);
int __queue_delayed_work(struct delayed_work *work, u32 delay, 
    const char* func, unsigned long line);

#else // !QDF_WORKER_DEBUG

int __init_delayed_work(struct delayed_work *work, work_func_t execution, void *context);
int __cancel_delayed_work(struct delayed_work *work);
int __queue_delayed_work(struct delayed_work *work, u32 delay);

#endif // !QDF_WORKER_DEBUG

#if QDF_WORKER_DEBUG

#define init_delayed_work(_w, _e, _c) __init_delayed_work(_w, _e, _c, __FUNCTION__, __LINE__)
#define cancel_delayed_work(_w) __cancel_delayed_work(_w, __FUNCTION__, __LINE__)
#define cancel_delayed_work_sync(_w) __cancel_delayed_work(_w, __FUNCTION__, __LINE__)
#define queue_delayed_work(_w, _d) __queue_delayed_work(_w, _d, __FUNCTION__, __LINE__)

#else // !QDF_WORKER_DEBUG

static inline int init_delayed_work(
    struct delayed_work *work, work_func_t execution, void *context)
{
    return __init_delayed_work(work, execution, context);
}

static inline int cancel_delayed_work(struct delayed_work *work)
{
    return __cancel_delayed_work(work);
}

static inline int cancel_delayed_work_sync(struct delayed_work *work)
{
    return __cancel_delayed_work(work);
}

static inline int queue_delayed_work(struct delayed_work *work, u32 delay)
{
    return __queue_delayed_work(work, delay);
}

#endif // !QDF_WORKER_DEBUG

int __invoke_pending_works(int budget, u64 timeout);
int __invoke_pending_delayed_works(int budget, u64 timeout);

/* invoke pending work and delayed_work */
static inline int invoke_pending_works(int budget, u64 timeout)
{
    budget = __invoke_pending_works(budget, timeout);
    if (budget > 0)
        budget = __invoke_pending_delayed_works(budget, timeout);

    return budget;
}

#endif // !__WORKER_H

