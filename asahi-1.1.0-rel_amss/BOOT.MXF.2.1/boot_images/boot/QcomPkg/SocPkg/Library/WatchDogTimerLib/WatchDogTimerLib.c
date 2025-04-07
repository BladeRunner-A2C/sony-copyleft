/**@file WatchDogTimerLib.c

  Copyright (c) 2020, Qualcomm Technologies Inc. All rights reserved.<BR>

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 
 --------   ---     -----------------------------------------------------------
 09/21/22   rama    Add APIs to support timer 1 and 2 configurations
 12/23/20  ds      Initial revision
=============================================================================*/
#include <Library/ArmLib.h>
#include <WatchDogTimerLib.h>
#include <HALbootHWIO.h>
#include <Target_cust.h>
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
  FUNCTION      WatchDog_Timer1_Enable

  DESCRIPTION   Set Bit 0 in WDOG_CTL to Enable WatchDog Timer1 
  

==============================================================================*/

static void WatchDog_Timer1_Enable(void)
{
  APSS_WDT_TMR1_WDOG_CTL_OUT(APSS_WDT_TMR1_WDOG_CTL_INT_ENABLE);
  ArmInstructionSynchronizationBarrier();
}

/*==============================================================================
  FUNCTION      WatchDog_Timer2_Enable

  DESCRIPTION   Set Bit 0 in WDOG_CTL to Enable WatchDog  Timer2
  

==============================================================================*/

static void WatchDog_Timer2_Enable(void)
{
  APSS_WDT_TMR2_WDOG_CTL_OUT(APSS_WDT_TMR2_WDOG_CTL_INT_ENABLE);
  ArmInstructionSynchronizationBarrier();
}

/*==============================================================================
  FUNCTION      WatchDog_Timer1_Enable_Sec

  DESCRIPTION   Set Secure Bit of WatchDog Timer1 and Enable
  
  Note: Can only be used by NS=0

==============================================================================*/

void WatchDog_Timer1_Enable_Sec(void)
{
  APSS_WDT_TMR1_WDOG_SECURE_OUT(APSS_WDT_TMR1_WDOG_SET_SEC_BIT);
  ArmInstructionSynchronizationBarrier();
  
  WatchDog_Timer1_Enable();
}

/*==============================================================================
  FUNCTION      WatchDog_Timer2_Enable_NSec

  DESCRIPTION   Set Non-Secure Bit of WatchDog Timer2 and Enable  

==============================================================================*/

void WatchDog_Timer2_Enable_NSec(void)
{
  APSS_WDT_TMR2_WDOG_SECURE_OUT(APSS_WDT_TMR2_WDOG_SET_NSEC_BIT);
  ArmInstructionSynchronizationBarrier();
  
  WatchDog_Timer2_Enable();
}

/*==============================================================================
  FUNCTION      WatchDog_Timer1_Disable

  DESCRIPTION   Reset Bit 0 in Timer1 WDOG_CTL to Disable WatchDogReset 
  
==============================================================================*/

void WatchDog_Timer1_Disable(void)
{
  APSS_WDT_TMR1_WDOG_CTL_OUT(APSS_WDT_TMR1_WDOG_CTL_INT_DISABLE);
  ArmInstructionSynchronizationBarrier ();
}

/*==============================================================================
  FUNCTION      WatchDog_Timer2_Disable

  DESCRIPTION   Reset Bit 0 in Timer2 WDOG_CTL to Disable WatchDogReset 
  
==============================================================================*/

void WatchDog_Timer2_Disable(void)
{
  APSS_WDT_TMR2_WDOG_CTL_OUT(APSS_WDT_TMR2_WDOG_CTL_INT_DISABLE);
  ArmInstructionSynchronizationBarrier ();
}

/*==============================================================================
  FUNCTION      WatchDog_Timer1_SetBite_Counter

  DESCRIPTION   Set the WDOG_BITE Counter with value in sleep clocks for WatchDog Timer1
  
  Note: If the watchdog Bite timer value is changed while wdog is enabled,
        the new Bite timer value will take effect immediately
==============================================================================*/


bl_error_boot_type WatchDog_Timer1_SetBite_Counter(uint32 BiteCounterVal)
{
  if ((BiteCounterVal == 0) || (BiteCounterVal > MAX_WDOG_BITE_VAL))
    return GET_ERROR_CODE(BL_ERROR_GROUP_WDOGTMR, BL_ERR_INVALID_PARAMETER);;
  
  APSS_WDT_TMR1_WDOG_BITE_TIME_OUT(BiteCounterVal);

  ArmInstructionSynchronizationBarrier();
  
  WatchDog_Timer1_Pet();
  
  return BL_ERR_NONE;  
}

/*==============================================================================
  FUNCTION      WatchDog_Timer2_SetBite_Counter

  DESCRIPTION   Set the WDOG_BITE Counter with value in sleep clocks for WatchDog Timer2
  
  Note: If the watchdog Bite timer value is changed while wdog is enabled,
        the new Bite timer value will take effect immediately
==============================================================================*/


bl_error_boot_type WatchDog_Timer2_SetBite_Counter(uint32 BiteCounterVal)
{
  if ((BiteCounterVal == 0) || (BiteCounterVal > MAX_WDOG_BITE_VAL))
    return GET_ERROR_CODE(BL_ERROR_GROUP_WDOGTMR, BL_ERR_INVALID_PARAMETER);;
  
  APSS_WDT_TMR2_WDOG_BITE_TIME_OUT(BiteCounterVal);

  ArmInstructionSynchronizationBarrier();
  
  WatchDog_Timer2_Pet();
  
  return BL_ERR_NONE;  
}

/*==============================================================================
  FUNCTION      WatchDog_Timer1_SetBite_MSec

  DESCRIPTION   Set the WDOG_BITE_TIME with the input BiteTime for WatchDog Timer1
  
  Note: If the watchdog Bite timer value is changed while wdog is enabled,
        the new Bite timer value will take effect immediately
==============================================================================*/

bl_error_boot_type WatchDog_Timer1_SetBite_MSec(uint32 BiteTimeMSec)
{
  uint32 BiteTimeCounterVal = MS_TO_WDOG_COUNTER_VAL(BiteTimeMSec);

  return WatchDog_Timer1_SetBite_Counter(BiteTimeCounterVal);
}

/*==============================================================================
  FUNCTION      WatchDog_Timer2_SetBite_MSec

  DESCRIPTION   Set the WDOG_BITE_TIME with the input BiteTime for WatchDog Timer2
  
  Note: If the watchdog Bite timer value is changed while wdog is enabled,
        the new Bite timer value will take effect immediately
==============================================================================*/

bl_error_boot_type WatchDog_Timer2_SetBite_MSec(uint32 BiteTimeMSec)
{
  uint32 BiteTimeCounterVal = MS_TO_WDOG_COUNTER_VAL(BiteTimeMSec);

  return WatchDog_Timer2_SetBite_Counter(BiteTimeCounterVal);
}

/*==============================================================================
  FUNCTION      WatchDog_Timer1_Pet

  DESCRIPTION   Set the WDOG_RESET register to reset the count in 
                WDOG_STATUS register for WatchDog Timer1
==============================================================================*/

void WatchDog_Timer1_Pet(void)
{
  //Reset Wdog count to start from 0 again
  
  APSS_WDT_TMR1_WDOG_RESET_OUT(APSS_WDT_TMR1_WDOG_RESET_COUNT);
  ArmInstructionSynchronizationBarrier();
}

/*==============================================================================
  FUNCTION      WatchDog_Timer2_Pet

  DESCRIPTION   Set the WDOG_RESET register to reset the count in 
                WDOG_STATUS register for WatchDog Timer2
==============================================================================*/

void WatchDog_Timer2_Pet(void)
{
  //Reset Wdog count to start from 0 again
  
  APSS_WDT_TMR2_WDOG_RESET_OUT(APSS_WDT_TMR2_WDOG_RESET_COUNT);
  ArmInstructionSynchronizationBarrier();
}

/*==============================================================================
  FUNCTION      WatchDog_Timer1_ForceSecBite

  DESCRIPTION   Enable WatchDog Timer1 and force wdog bite
  
  Note: Can only be used by NS=0
==============================================================================*/

void WatchDog_Timer1_ForceSecBite(void)
{
  /* CTL, Enable */
  WatchDog_Timer1_Enable_Sec();
  
  WatchDog_Timer1_Pet();

  WatchDog_Timer1_SetBite_MSec(FORCED_BITE_TIME_MS);
  ArmInstructionSynchronizationBarrier();
  
  while(1);
}

/*==============================================================================
  FUNCTION      WatchDog_Timer2_ForceSecBite

  DESCRIPTION   Enable WatchDog Timer2 and force wdog bite
==============================================================================*/

void WatchDog_Timer2_ForceNSecBite(void)
{
  /* CTL, Enable */
  WatchDog_Timer2_Enable_NSec();
  
  WatchDog_Timer2_Pet();

  WatchDog_Timer2_SetBite_MSec(FORCED_BITE_TIME_MS);
  ArmInstructionSynchronizationBarrier();
  
  while(1);
}