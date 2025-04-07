/**************************************************************************
 * FILE: devprg_utils.c
 *
 * Provides utility functions for devprg.
 * For now we just have the sleep and time
 *
 * Copyright (c) 2017,2020,2023 Qualcomm Technologies, Inc.
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
2023-09-07   pz    Fix timetick count overflow.
2017-13-07   svl   Create.

===========================================================================*/

#include "boot_target.h"
#include "msmhwio.h"
#include "HALbootHWIO.h"
#include "devprg_utils.h"
#include "busywait.h"

boolean devprg_busywait_timer_inited = FALSE;

static uint64 devprg_timetick(void)
{
  uint32 curr_count;
  uint32 last_count;
  uint32 diff;

  // Grab current time count
  curr_count = HWIO_IN(TIMETICK_CLK);

  // Keep grabbing the time until a stable count is given
  do
  {
    last_count = curr_count;
    curr_count = HWIO_IN(TIMETICK_CLK);
    diff = curr_count - last_count;
  } while (diff > 5); /* If the tick is less than 5 then assume the clock is
  stable. This is to handle the case where the CPU instruction clock is slow
  (like RUMI) and we get two different readings between to counter reads */

  return curr_count;
}

uint64 devprg_time_usec(void)
{
  uint64 curr_time_count = devprg_timetick();
  curr_time_count = CALCULATE_AOSS_SLEEP_CNTR_US(curr_time_count);
  return curr_time_count;
}

int devprg_usleep(uint64 microsecs)
{
  uint32 max_delay = MAX_BUSYWAIT_TIME_IN_US;
  
  if (FALSE == devprg_busywait_timer_inited)
  {
    busywait_init();
    devprg_busywait_timer_inited = TRUE;
  }

  while (microsecs > max_delay)
  {
    busywait(max_delay);
	microsecs -= max_delay;
  }
  
  busywait((uint32) microsecs);
  
  return 0;
}
