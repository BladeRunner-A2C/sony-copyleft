#ifndef POWERSLEEPTARGETLIB_H
#define POWERSLEEPTARGETLIB_H

/******************************************************************//**
 * @file PowerSleepTargetLib.c
 *
 * @brief PowerSleepLib target specific functions
 *
 * Copyright (c) 2017-2021,2023 Qualcomm Technologies, Inc. All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 * Copyright (c) 2017-2021, 2023 by Qualcomm Technologies, Inc. All rights reserved.
 *
 *********************************************************************/


#include "rpmh_client.h"
#include "rsc_hwio.h"

//SchedulerLib APIs
#include "list.h"
#include "interrupts.h"
#include "kernel/mutex.h"
#include "kernel/wait.h"
#include "Library/PcdLib.h"

#define PSLEEP_NUM_CORES_SUPPORTED FixedPcdGet64(PcdMaxCoreCnt)
#define MAX_NUM_CLUSTERS 1 // Max possible clusters
#define MAX_CORES_PER_CLUSTER 8

typedef enum
{
  PSLEEP_CORE_ACTIVE, //core is awake
  PSLEEP_CORE_C1,     //core is clock gated
  PSLEEP_CORE_C2,     //core is asleep but logic stays on. L1/L2 at retention
  PSLEEP_CORE_C3,     //core is in power collapse, prevent PLLs and rails from turning off
  PSLEEP_CORE_C4,     //core is in power collapse, allow PLLs and rails to turn off. 
                      //C4 is required on all cores in order to enter system D4
  PSLEEP_CORE_C4D4,   //Only applies to the last core to go down. 
  PSLEEP_CORE_OFF,    //core hasn't been brought up or is hotplugged
  PSLEEP_CORE_MAX,
} power_sleep_core_state;

//--------------------------------------------------------------------------
// PSCI IDs
//--------------------------------------------------------------------------

#define CPU_C4      0x40000004
#define L3_D4       0x40
#define RSC_E2      0x200
#define RSC_E3      0x300
#define PDC_F1      0x1000
#define PDC_F2      0x2000
#define PDC_F3      0x3000
#define PDC_F4      0x4000
#define SYS_CACHE   0x8000
#define POWER_DOWN  0x41000000

#define SLEEP_MODE_CXSD  (CPU_C4 | L3_D4 | RSC_E2 | PDC_F4 | SYS_CACHE | POWER_DOWN)
#define SLEEP_MODE_CXRET (CPU_C4 | L3_D4 | RSC_E3 | PDC_F3 | SYS_CACHE | POWER_DOWN)

#define SLEEP_MODE_C4 CPU_C4

//--------------------------------------------------------------------------
// RSC Defines
//--------------------------------------------------------------------------
//Wake TCS 5
#define WAKE0_TCS 5
#define WAKE1_TCS 6

//Sleep TCS 2
#define SLEEP_TCS_START 3
#define WAKE_TCS_START 5
#define TCS_END 7
#define SLEEP0_TCS 3
#define SLEEP1_TCS 4

#define LATE_WAKEUP_THRESHOLD 0x9600 //2mS in 19.2
#define MIN_C4_SLEEP_TIME 0x4B00 //1mS in 19.2
#define MIN_C4D4_SLEEP_TIME 0x2EE00 //10mS in 19.2

typedef struct
{
  boolean                initialized;
  mutex_t                *lock;  // lock for configuring RSC info/globals for Backward compatilibitliy
  spin_lock_t 		     splock;	// lock for configuring psleep global variables
  uint32                 *dbg_state; //debug state for each core
  uint32                 num_cores_supported; //static value for number of supported cores (in config data)
  power_sleep_core_state *core_states; //core states from psleep perspective
  uint32                 core_state_bmsk; //bmsk used to manipulate states
  uint32                 sched_cores_active; //cores being used from the scheduler's POV
  uint64                 wakeup_time; //wakeup time for c4d4
  uint32                 deepest_sleep_mode; //deepest sleep mode supported. Used in case CX collapse/AOSS sleep isn't supported
  rpmh_command_set_t     rpmh_sleep_config[WAKE_TCS_START - SLEEP_TCS_START];  //sleep set
  rpmh_command_set_t     rpmh_wake_config[TCS_END - WAKE_TCS_START]; //wake set
  boolean                cmd_sets_dirty; //Used to track if we've cleaned up from a prior cycle or not
}psleep_type;

/**
 * <!-- psleep_is_c4d4 -->
 *
 * @brief Check if psci_id is used to enter C4D4 or a deeper state 
 *
 * @return True if psci_id is for C4D4 or a deeper state
 */
boolean psleep_is_c4d4(uint32_t psci_id);

/**
 * <!-- psleep_get_num_cores -->
 *
 * @brief Returns the # of cores supported for this target
 *
 * @return number of cores supported
 */
uint32 psleep_get_num_cores(void);

/**
 * <!-- psleep_cx_sd_supported -->
 *
 * @brief Returns whether or not we support CX collapse on this target
 *
 * @return TRUE if CX collapse is supported
 */
boolean psleep_cx_sd_supported(void);

/**
 * <!-- psleep_rsc_cfg_get_set_cfg -->
 *
 * @brief Gets the associated static config for the give sent, and indicates how many command sets are used
 *
 * @param set : if we should retrieve the sleep or wake set
 *
 * @param num_sets : Byref var to indicate # of command sets in the returned array
 *
 * @return static config command sets for the given set
 */
rpmh_command_set_t *psleep_rsc_cfg_get_set_cfg(rpmh_set_enum set, uint32_t *num_sets);

/**
 * <!-- psleep_target_init -->
 *
 * @brief Function to initialize psleep target lib.
 */
void psleep_target_init(void);

/**
 * <!-- get_last_core_lpm_state -->
 *
 * @brief Helper function to get the deepest core lpm
 *
 * @return the enum for deepest core lpm
 */
power_sleep_core_state get_last_core_lpm_state(void);

/**
 * <!-- getTime -->
 *
 * @brief Helper function to get current time
 *
 * @return the time read from the timer
 */
uint64_t getTime(void);

/**
 * <!-- update_core_states -->
 *
 * @brief Helper function to update core states based on what the scheduler may have done
 *
 * @param init : If its at init time, set non-zero cores to active
 */
void update_core_states(boolean init);

/**
 * <!-- is_last_core -->
 *
 * @brief Helper function to determine if we are the last core down or not
 *
 * @param core_num : The core number on which we are currently operating
 *
 * @return TRUE if we are the last core going down in the cluster
 */
boolean is_last_core(uint32 core_num);

/**
 * <!-- is_last_cluster -->
 *
 * @brief Helper function to determine if we are the last cluster down or not
 *
 * @param core_num : The core number on which we are currently operating
 *
 * @return TRUE if we are the last cluster going down
 */
boolean is_last_cluster(uint32 core_num);

/**
 * <!-- rsc_config_tcs_contents -->
 *
 * @brief Populate the TCS with the sleep/wake config data
 */
void rsc_config_tcs_contents(void);

/**
 * <!-- set_current_core_state -->
 *
 * @brief Helper function to update our current understanding of core states
 *
 * @param core_num  : The core number on which we are currently operating
 * @param new_state : The state we are trying to enter for the given core
 */
void set_current_core_state(uint32 core_num, power_sleep_core_state new_state);

/**
 * <!-- pdc_set_wakeup_time -->
 *
 * @brief Calculate and populate the wakeup time for the PDC
 *
 * @param wakeup_time : The wakeup time that software needs to start
 */
void pdc_set_wakeup_time(uint64 wakeup_time);

/**
 * <!-- rsc_clean_up -->
 *
 * @brief Clears out the rsc from a prior sleep cycle
 */
void rsc_clean_up(void);

/**
 * <!-- print_sleep_stats -->
 *
 * @brief Helper function to print out sleep stats
 */
void print_sleep_stats(void);

#endif //POWERSLEEPTARGETLIB_H
