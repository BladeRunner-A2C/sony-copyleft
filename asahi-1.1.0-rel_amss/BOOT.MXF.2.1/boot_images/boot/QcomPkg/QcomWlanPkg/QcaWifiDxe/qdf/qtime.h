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

#ifndef __QDF_QTIME_H
#define __QDF_QTIME_H

#include <qdf/base_type.h>
#include <Uefi.h>
#include <Utils.h>

#define mdelay(x) gBS->Stall((x) * 1000)
#define udelay(x) gBS->Stall(x)

static inline u64 getwalltime_us(void)
{
    return GetTimeInMicrosecond();
}

static inline u64 getwalltime_ms(void)
{
    return GetTimeInMillisecond();
}


#define HZ 1000
#define MSEC_PER_SEC 1000

/* use the milliseconds as jiffies directly */
#define jiffies getwalltime_ms()

static inline unsigned long msecs_to_jiffies(const unsigned int m)
{
    return (m + (MSEC_PER_SEC / HZ) - 1) / (MSEC_PER_SEC / HZ);
}

#define time_after(t1,t2)    ((s64)((t2) - (t1)) < 0)


#endif // !__ERRNO_H

