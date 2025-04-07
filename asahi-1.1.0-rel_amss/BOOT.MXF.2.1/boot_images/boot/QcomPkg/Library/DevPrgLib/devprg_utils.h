/**************************************************************************
 * FILE: devprg_utils.h
 *
 * Provides utility functions for devprg.
 * For now we just have the sleep and time
 *
 * Copyright (c) 2017,2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Qualcomm Proprietary
 *
 *************************************************************************/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when         who   what, where, why
----------   ---   ---------------------------------------------------------
2023-28-11   pz    Replace TIMETICK_CLK with busywait(Qtimer) in devprg_usleep.
2017-13-07   svl   Create.

===========================================================================*/

#ifndef __DEVPRG_UTILS_H__
#define __DEVPRG_UTILS_H__

#include "comdef.h"

/* The maximum delay of busywait depends on the frequency of Qtimer. 
In order to prevent overflow, the limit is set to 10s. */
#define MAX_BUSYWAIT_TIME_IN_US   10000000

uint64 devprg_time_usec(void);
int devprg_usleep(uint64 microsecs);

#endif /* __DEVPRG_UTILS_H__ */
