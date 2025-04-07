#ifndef POWERSLEEPLIB_H
#define POWERSLEEPLIB_H

/******************************************************************//**
 * @file PowerSleepLib.h
 *
 * @brief PowerSleepLib functions
 *
 * Copyright (c) 2017-2018, 2022, 2023 by Qualcomm Technologies, Inc.
 * All Rights Reserved.
 *
 *********************************************************************/
/*=======================================================================
                        Edit History

   when       who     what, where, why
  --------   ----    --------------------------------------------------- 
  11-10-17    mab     Created

========================================================================*/

#include <Uefi.h>
#include <stddef.h>
#include <string.h>
#include "comdef.h"
#include <Protocol/EFIPsleepInterface.h>
#include <Protocol/EFIKernelInterface.h>

//Target Specific header
#include "PowerSleepTargetLib.h"

#define PWR_SLEEP_LOCK    STR_OBJECT_ID('P','W','R','_','S','L','P',0)

//--------------------------------------------------------------------------
// PSCI Defines
//--------------------------------------------------------------------------

// PSCI Function IDs
typedef enum
{
	POWER_SLEEP_PSCI_CPU_SUSPEND           = 0xC4000001,
	POWER_SLEEP_PSCI_CPU_OFF               = 0x84000002,
	POWER_SLEEP_PSCI_CPU_ON                = 0xC4000003,
	POWER_SLEEP_PSCI_CPU_SET_SUSPEND_MODE  = 0x8400000F,
	OS_INITIATED_MODE                      = 0x1,
} psci_func_ID;

typedef enum
{
  PSCI_UNKNOWN_ERROR = 0x80000000,     /* To force 32bit width */
  PSCI_INVALID_ADDRESS    = -9,
  PSCI_DISABLED,
  PSCI_NOT_PRESENT,
  PSCI_INTERNAL_FAILURE,
  PSCI_ON_PENDING,
  PSCI_ALREADY_ON,
  PSCI_DENIED,
  PSCI_INVALID_PARAMETERS,
  PSCI_NOT_SUPPORTED,
  PSCI_SUCCESS = 0
} power_sleep_psci_err_enum;


typedef enum
{
  POWER_SLEEP_SUCCESS                    = PSCI_SUCCESS, //Successful sleep entry/exit
  POWER_SLEEP_ERROR_RESTORE_PTR          = PSCI_INVALID_ADDRESS, //Function pointer passed by the client is invalid
  POWER_SLEEP_ERROR_CORE_SHALLOW_SLEEP   = PSCI_INVALID_PARAMETERS, //We tried to enter C4D4 but another core is in < C4
  POWER_SLEEP_ERROR_CORE_RUNNNING        = PSCI_DENIED, //We tried to enter C4D4 but another core started running
  POWER_SLEEP_INTERRUPT_PENDING          = PSCI_SUCCESS, //There was a pending wakeup/interrupt so we 
                                                         //short circuited and never fully entered power collapse
  POWER_SLEEP_OTHER_FAILURE              = (~0),
} power_sleep_pc_err_enum;

typedef struct _power_sleep_stats_t
{
  uint32 *dict_addr;
  uint32 *base_addr;
  sleep_stats_t lpm[POWER_SLEEP_STATS_NUM_STATS];
  boolean init;
} power_sleep_stats_t;

typedef UINTN (*power_sleep_restore_fn) (void* ctxt);

extern int sleep_psci_call(long arg0, long arg1, long arg2, long arg3);

// LPM profiling
extern lpm_profiling_t psleep_lpm_profiling[PSLEEP_NUM_CORES_SUPPORTED];

/**
 * <!-- power_sleep_get_lpm_counts -->
 *
 * @brief Gets the lpm counts for the requested sleep mode
 *
 * @param sleep_mode : the sleep mode for which counts are requested
 *
 * @return pointer to lpm_profiling_data
 */
sleep_stats_t *power_sleep_get_lpm_counts(power_sleep_stats_enum_t sleep_mode);

/**
 * <!-- power_sleep_get_lpm_profiling_data -->
 *
 * @brief Gets the lpm_profiling_data
 *
 * @return pointer to lpm_profiling_data
 */
lpm_profiling_t *power_sleep_get_lpm_profiling_data(void);

/**
 * <!-- power_sleep_init -->
 *
 * @brief Initialize power sleep library 
 */
void power_sleep_init(void);

/**
 * <!-- power_sleep_enter_pc -->
 *
 * @brief Attempts to enter the deepest sleep mode possible for the running core 
 *
 * @param restore_ptr : The function pointer to call on wakeup from sleep
 * @param ctxt        : Client context to be passed along with the function pointer
 * @param wakeup_time : Absolute time in XO ticks (19.2Mhz) that we want the subsystem to wake up.
 *                      This should be the earliest wakeup time for any cores
 *
 * @return error code if there is an issue, SUCCESS otherwise
 */
power_sleep_pc_err_enum power_sleep_enter_pc (power_sleep_restore_fn restore_ptr, void * ctxt, uint64_t wakeup_time);

/**
 * <!-- power_sleep_enter_pc_ex -->
 *
 * @brief Attempts to enter the deepest sleep mode based on the sleep duration input
 *
 * @param restore_ptr : The function pointer to call on wakeup from sleep
 * @param ctxt        : Client context to be passed along with the function pointer
 * @param sleep_duration : Sleep duration in uS for the core to be in idle. 
 * @param exit_latency : Exit latency requirement in uS. 
 * @param sleep_hint : Hint to indicate the deepest sytem level idle state we can enter. 
 *
 * @return error code if there is an issue, SUCCESS otherwise
 */
power_sleep_psci_err_enum power_sleep_enter_pc_ex(
        power_sleep_restore_fn restore_ptr, 
        void * ctxt, 
        uint64 sleep_duration, 
        uint64 exit_latency,
        enum LpmType sleep_hint);

/**
 * <!-- is_retention_lpm -->
 *
 * @brief Check whether retention lpm or not
 *
 * @return true or false based on retention check
 */
boolean is_retention_lpm(void);

/**
 * <!-- veto_lpm_mode -->
 *
 * @brief Limits a core/cluster to a particular LPM state for any duration higher than its residency value.
 *
 * @param coreMask : Core mask on which the veto is to be applied
 * @param mode_id  : Mode id of the LPM state to which core/cluster is to be limited
 */
void veto_lpm_mode(uint32_t coreMask, uint16_t mode_id);

#endif //POWERSLEEPLIB_H
