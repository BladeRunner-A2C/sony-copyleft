/**@file WatchDogTimerLib.c

  Copyright (c) 2022, Qualcomm Technologies Inc. All rights reserved.<BR>

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 
 --------   ---     -----------------------------------------------------------
 08/19/22  krd     Added support of null lib
 12/23/20  ds      Initial revision
=============================================================================*/
#include <Library/ArmLib.h>
#include <WatchDogTimerLib.h>
#include <HALbootHWIO.h>
#include <HALhwio.h>

#define SLEEP_CLK_FREQ             32768

#define MAX_WDOG_COUNTER_VAL       (1 << 20)

#define MS_TO_WDOG_COUNTER_VAL(x)  ((((x) * SLEEP_CLK_FREQ) / 1000) - 1)

#define MAX_WDOG_BITE_VAL          (MAX_WDOG_COUNTER_VAL - 1)

#define FORCED_BITE_TIME_MS        4

/*==============================================================================
**  Functions
**============================================================================*/

/*==============================================================================
  FUNCTION      WatchDog_Enable

  DESCRIPTION   Set Bit 0 in WDOG_CTL to Enable WatchDog 
  

==============================================================================*/

static void WatchDog_Enable(void)
{

}

/*==============================================================================
  FUNCTION      WatchDog_Enable_Sec

  DESCRIPTION   Set Secure Bit of WatchDog and Enable
  
  Note: Can only be used by NS=0

==============================================================================*/

void WatchDog_Enable_Sec(void)
{

}

/*==============================================================================
  FUNCTION      WatchDog_Enable_NSec

  DESCRIPTION   Set Non-Secure Bit of WatchDog and Enable  

==============================================================================*/

void WatchDog_Enable_NSec(void)
{

}
/*==============================================================================
  FUNCTION      WatchDog_Disable

  DESCRIPTION   Reset Bit 0 in WDOG_CTL to Disable WatchDogReset 
  
==============================================================================*/

void WatchDog_Disable(void)
{

}

/*==============================================================================
  FUNCTION      WatchDog_SetBite_Counter

  DESCRIPTION   Set the WDOG_BITE Counter with value in sleep clocks
  
  Note: If the watchdog Bite timer value is changed while wdog is enabled,
        the new Bite timer value will take effect immediately
==============================================================================*/


bl_error_boot_type WatchDog_SetBite_Counter(uint32 BiteCounterVal)
{

  
  return BL_ERR_NONE;  
}


/*==============================================================================
  FUNCTION      WatchDog_SetBite_MSec

  DESCRIPTION   Set the WDOG_BITE_TIME with the input BiteTime
  
  Note: If the watchdog Bite timer value is changed while wdog is enabled,
        the new Bite timer value will take effect immediately
==============================================================================*/

bl_error_boot_type WatchDog_SetBite_MSec(UINT32 BiteTimeMSec)
{
  return BL_ERR_NONE;
}

/*==============================================================================
  FUNCTION      WatchDog_Pet

  DESCRIPTION   Set the WDOG_RESET register to reset the count in 
                WDOG_STATUS register
==============================================================================*/

void WatchDog_Pet(void)
{

}

/*==============================================================================
  FUNCTION      WatchDog_ForceSecBite

  DESCRIPTION   Enable WatchDog and force wdog bite
  
  Note: Can only be used by NS=0
==============================================================================*/

void WatchDog_ForceSecBite(void)
{

}

/*==============================================================================
  FUNCTION      WatchDog_ForceSecBite

  DESCRIPTION   Enable WatchDog and force wdog bite
==============================================================================*/

void WatchDog_ForceNSecBite(void)
{

}