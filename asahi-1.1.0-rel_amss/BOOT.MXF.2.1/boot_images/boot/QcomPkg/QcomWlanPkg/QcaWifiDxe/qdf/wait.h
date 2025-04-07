/*
 * Copyright (c) 2020-2021, 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 14/7/21   zxue     branch for core boot

=============================================================================*/

#ifndef __QDF_WAIT_H
#define __QDF_WAIT_H

#include <qdf/base_type.h>
#include <qdf/limits.h>
#include <qdf/interrupt.h>
#include <qdf/pr_debug.h>

#if SUPPORT_DEBUG_PRINT
#define QDF_WAIT_COMPLETION_DEBUG  1
#endif

/*****************************************************************************/
/* completion */

struct completion
{
    unsigned int done;
};


/* implementation */
#if QDF_WAIT_COMPLETION_DEBUG

long __wait_for_completion_timeout_debug(struct completion *x,
    unsigned long timeout, const char* func, unsigned long line);
#else // !QDF_WAIT_COMPLETION_DEBUG
long __wait_for_completion_timeout(struct completion *x,
    unsigned long timeout);
#endif // QDF_WAIT_COMPLETION_DEBUG

static inline void init_completion(struct completion *x)
{
    x->done = 0;
}

static inline void reinit_completion(struct completion *x)
{
    x->done = 0;
}

static inline void complete(struct completion *x)
{
    x->done += 1;
}

static inline void complete_all(struct completion *x)
{
    x->done = UINT_MAX;
}

/**
 *	completion_done - Test to see if a completion has any waiters
 *	@x:	completion structure
 *
 *	Return: 0 if there are waiters (wait_for_completion() in progress)
 *		 1 if there are no waiters.
 *
 *	Note, this will always return true if complete_all() was called on @X.
 */
static bool completion_done(struct completion *x)
{
	if (!(x->done))
		return false;

	return true;
}

#if QDF_WAIT_COMPLETION_DEBUG

#define wait_for_completion_timeout(x, timeout)                \
    __wait_for_completion_timeout_debug(x, timeout, __FUNCTION__, __LINE__)

#define wait_for_completion_interruptible_timeout(x, timeout)  \
    __wait_for_completion_timeout_debug(x, timeout, __FUNCTION__, __LINE__)

#else // !QDF_WAIT_COMPLETION_DEBUG

static inline unsigned long 
wait_for_completion_timeout(struct completion *x, unsigned long timeout)
{   
    return __wait_for_completion_timeout(x, timeout);
}

static inline long wait_for_completion_interruptible_timeout(struct completion *x,
    unsigned long timeout)
{
    return __wait_for_completion_timeout(x, timeout);
}

#endif // QDF_WAIT_COMPLETION_DEBUG


/*****************************************************************************/
/* wait_queue_head */

struct wait_queue_head
{
    u8 lock;
    u8 signaled;  /* TODOTODO: not used yet */
};

typedef struct wait_queue_head wait_queue_head_t;

static inline void init_waitqueue_head(struct wait_queue_head *wq_head)
{
    wq_head->signaled = 0;
}

static inline void wake_up(struct wait_queue_head *wq_head)
{
    wq_head->signaled = 1;
}

static inline void wake_up_all(struct wait_queue_head *wq_head)
{
    wq_head->signaled = 1;
}

static inline void wake_up_interruptible_all(struct wait_queue_head *wq_head)
{
    wake_up(wq_head);
}

#define WAIT_EVENT_NOWAKE_POLL_US       (5 * 1000)
#define WAIT_EVENT_WAKE_POLL_US         (5 * 1000)

#define wait_event_timeout(_wq, _condition, _timeout, _ret)               \
{										                                  \
	u32 _poll_interval;							                          \
    u64 _ctime, _btime, _etime, _delay_us, _timeout_us;                   \
    int _budget;                                                          \
    _ret = _timeout;                                                      \
    if (!(_condition)) {                                                  \
        pr_debug("poll for wq 0x%p: condition=[%a], timeout=[%d]\n",      \
            &(_wq), TO_STRING(_condition), _timeout);                     \
        _delay_us = 0;                                                    \
        _timeout_us = _timeout * 1000;                                    \
        _btime = getwalltime_us();                                        \
        _etime = _btime + _timeout_us;                                    \
        (_wq).signaled = 0;                                               \
	    do {                                                              \
		    _budget = __global_poll_irqs(4);                              \
		    if (_condition) {                                             \
                _ctime = getwalltime_us();                                \
			    break;                                                    \
            }                                                             \
            if (_budget) {                                                \
                _poll_interval = ((_wq).signaled ?                        \
                    WAIT_EVENT_WAKE_POLL_US :                             \
                    WAIT_EVENT_NOWAKE_POLL_US);                           \
		        udelay(_poll_interval);                                   \
                _delay_us += _poll_interval;                              \
                if (_delay_us >= _timeout_us) {                           \
                    pr_err("detected time out by delay for wq 0x%p: "     \
                        "condition=[%a], ctime=%llu, btime=%llu, "        \
                        "delay_us=%llu\n",                                \
                        &(_wq), TO_STRING(_condition), getwalltime_us(),  \
                         _btime, _delay_us);                              \
                    _ctime = _etime;                                      \
                    break;                                                \
                }                                                         \
            }                                                             \
            _ctime = getwalltime_us();                                    \
	    } while(_ctime < _etime); 	                                      \
        _ret = (int)((_ctime < _etime) ? ((_etime - _ctime) / 1000) : 0); \
        pr_debug("poll done for wq 0x%p: condition=[%a], ret=[%d]\n",     \
            &(_wq), TO_STRING(_condition), _ret);                         \
    }                                                                     \
}

#define wait_event_interruptible_locked_irq(_wq, _condtion, _timeout, _ret) \
        wait_event_timeout(_wq, _condtion, _timeout, _ret)

#endif // !__WAIT_H

