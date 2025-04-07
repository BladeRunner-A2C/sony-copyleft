#include <Library/QcomBaseLib.h>
#include <Library/ArmArchTimerLibTemp/TimerLib.h>
#include <HALhwio.h>
#include <HALbootHWIO.h>
#include <boot_target.h>
#include <boot_timer_hw_if.h>

#define CALCULATE_APPS_QTIMER_COUNTER_US(ticks_count, frequency)\
                                (ticks_count / (frequency/1000000ULL))

uint32 __boot_get_aoss_sleep_counter_us(void)
{
  volatile uint32 curr_count;
  curr_count = HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_IN;
  return CALCULATE_AOSS_SLEEP_CNTR_US(curr_count);
}

uint64 __boot_get_apss_qtimer_counter_us(void)
{
  volatile uint32 curr_count_lo = 0;
  volatile uint32 curr_count_hi = 0;
  volatile uint32 clock_frequency = 0;
  uint64 timestamp = 0;
  
  /* Fetching QTIMER from Frame 0, V2 Physical counter */
  do{
      curr_count_hi = HWIO_APSS_QTMR0_F0V2_QTMR_V2_CNTPCT_HI_IN;
      curr_count_lo = HWIO_APSS_QTMR0_F0V2_QTMR_V2_CNTPCT_LO_IN;
  }while(curr_count_hi!=HWIO_APSS_QTMR0_F0V2_QTMR_V2_CNTPCT_HI_IN);
  
  clock_frequency = HWIO_APSS_QTMR0_F0V2_QTMR_V2_CNTFRQ_IN;
  
  timestamp = (((uint64)(curr_count_hi)) << sizeof(uint32)) | ((uint64)curr_count_lo);
  return CALCULATE_APPS_QTIMER_COUNTER_US(timestamp, clock_frequency);
}

boot_timer_hw_if_type timer_hw_if = {
  __boot_get_aoss_sleep_counter_us,
  __boot_get_apss_qtimer_counter_us
};

