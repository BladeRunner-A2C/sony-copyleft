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

#include <qdf/qbase.h>
#include <qdf/interrupt.h>
#include <qdf/pr_debug.h>
#include "wait.h"

#define DEFAULT_IRQ_POLL_US (5 * 1000)

#if QDF_WAIT_COMPLETION_DEBUG
long __wait_for_completion_timeout_debug(struct completion *x,
    unsigned long timeout, const char* func, unsigned long line)
#else
long __wait_for_completion_timeout(struct completion *x,
    unsigned long timeout)
#endif
{
    int ret;
    u64 ctime, btime, etime, delay_us, timeout_us;
    int budget;

    ret = timeout;
	if (!(x->done)) {
#if QDF_WAIT_COMPLETION_DEBUG
        pr_raw_dbg("%a(%u): poll for completion 0x%p: timeout=[%d]\n",
            func, line, x, timeout);
#endif
        delay_us = 0;
        timeout_us = timeout * 1000;
        btime = getwalltime_us();
        etime = btime + timeout_us;
	    do {
            budget = __global_poll_irqs(4);
		    if (x->done) {
                ctime = getwalltime_us();
			    break;
            }
            if (budget) {
                udelay(DEFAULT_IRQ_POLL_US);
                delay_us += DEFAULT_IRQ_POLL_US;
                if (delay_us >= timeout_us) {
                    pr_raw_err("%a(%u): detected time out by delay for completion 0x%p: "
                        "ctime=%llu, btime=%llu, delay_us=%llu\n",
                        func, line, x, getwalltime_us(), btime, delay_us);
                    ctime = etime;
                    break;
                }
            }
            ctime = getwalltime_us();
        } while (ctime < etime);
        ret = (int)((ctime < etime) ? ((etime - ctime) / 1000) : 0);
#if QDF_WAIT_COMPLETION_DEBUG
        pr_raw_dbg("%a(%u): poll done for completion 0x%p: ret=[%d]\n",
            func, line, x, ret);
#endif
    }

    return ret;
}
