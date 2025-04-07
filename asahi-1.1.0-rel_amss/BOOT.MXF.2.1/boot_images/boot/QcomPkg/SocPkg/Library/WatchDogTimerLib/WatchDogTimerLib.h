#ifndef WATCHDOGTIMERLIB_H
#define WATCHDOGTIMERLIB_H

/**@file WatchDogTimerLib.h

  Copyright (c) 2020, Qualcomm Technologies Inc. All rights reserved.<BR>

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 
 --------   ---     -----------------------------------------------------------
 09/21/22   rama    Add APIs to support timer 1 and 2 configurations
 12/23/20  ds      Initial revision
=============================================================================*/
#include <boot_error_if.h>

/*==============================================================================
**  Functions
**============================================================================*/
/*==============================================================================
  FUNCTION      WatchDog_Timer1_Enable_Sec

  DESCRIPTION   Set Secure Bit of WatchDog Timer1 and Enable
  
  Note: Can only be used by NS=0

==============================================================================*/
void WatchDog_Timer1_Enable_Sec(void);

/*==============================================================================
  FUNCTION      WatchDog_Timer2_Enable_NSec

  DESCRIPTION   Set Non-Secure Bit of WatchDog Timer2 and Enable  

==============================================================================*/
void WatchDog_Timer2_Enable_NSec(void);

/*==============================================================================
  FUNCTION      WatchDog_Timer1_Disable

  DESCRIPTION   Reset Bit 0 in Timer1 WDOG_CTL to Disable WatchDogReset 
  
==============================================================================*/
void WatchDog_Timer1_Disable(void);

/*==============================================================================
  FUNCTION      WatchDog_Timer2_Disable

  DESCRIPTION   Reset Bit 0 in Timer2 WDOG_CTL to Disable WatchDogReset 
  
==============================================================================*/
void WatchDog_Timer2_Disable(void);

/*==============================================================================
  FUNCTION      WatchDog_Timer1_SetBite_Counter

  DESCRIPTION   Set the WDOG_BITE Counter with value in sleep clocks for WatchDog Timer1
  
  Note: If the watchdog Bite timer value is changed while wdog is enabled,
        the new Bite timer value will take effect immediately
==============================================================================*/
bl_error_boot_type WatchDog_Timer1_SetBite_Counter(uint32 BiteCounterVal);

/*==============================================================================
  FUNCTION      WatchDog_Timer2_SetBite_Counter

  DESCRIPTION   Set the WDOG_BITE Counter with value in sleep clocks for WatchDog Timer2
  
  Note: If the watchdog Bite timer value is changed while wdog is enabled,
        the new Bite timer value will take effect immediately
==============================================================================*/
bl_error_boot_type WatchDog_Timer2_SetBite_Counter(uint32 BiteCounterVal);

/*==============================================================================
  FUNCTION      WatchDog_Timer1_SetBite_MSec

  DESCRIPTION   Set the WDOG_BITE_TIME with the input BiteTime for WatchDog Timer1
  
  Note: If the watchdog Bite timer value is changed while wdog is enabled,
        the new Bite timer value will take effect immediately
==============================================================================*/
bl_error_boot_type WatchDog_Timer1_SetBite_MSec(uint32 BiteTimeMSec);

/*==============================================================================
  FUNCTION      WatchDog_Timer2_SetBite_MSec

  DESCRIPTION   Set the WDOG_BITE_TIME with the input BiteTime for WatchDog Timer2
  
  Note: If the watchdog Bite timer value is changed while wdog is enabled,
        the new Bite timer value will take effect immediately
==============================================================================*/
bl_error_boot_type WatchDog_Timer2_SetBite_MSec(uint32 BiteTimeMSec);

/*==============================================================================
  FUNCTION      WatchDog_Timer1_Pet

  DESCRIPTION   Set the WDOG_RESET register to reset the count in 
                WDOG_STATUS register for WatchDog Timer1
==============================================================================*/
void WatchDog_Timer1_Pet(void);

/*==============================================================================
  FUNCTION      WatchDog_Timer2_Pet

  DESCRIPTION   Set the WDOG_RESET register to reset the count in 
                WDOG_STATUS register for WatchDog Timer1
==============================================================================*/
void WatchDog_Timer2_Pet(void);

/*==============================================================================
  FUNCTION      WatchDog_Timer1_ForceSecBite

  DESCRIPTION   Enable WatchDog Timer1 and force wdog bite
  
  Note: Can only be used by NS=0
==============================================================================*/
void WatchDog_Timer1_ForceSecBite(void);

/*==============================================================================
  FUNCTION      WatchDog_Timer2_ForceSecBite

  DESCRIPTION   Enable WatchDog Timer2 and force wdog bite
==============================================================================*/
void WatchDog_Timer2_ForceNSecBite(void);

#endif