/*==============================================================================
  FILE:         rsc_config.c

  OVERVIEW:     This file contains target specific data/configuration for rsc
                instances.

  DEPENDENCIES: None

  NOTE:         Generated from: Lanai V1.0
                Version: 0x71df01c

                Copyright (c) 2022, 2023 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================*/

#include "rsc.h"
#include "rsc_seq_hal.h"
#include "rsc_hal_bsp.h"
#include "msmhwiobase.h"

/*==========================================================================
 *                           INTERNAL MACROS
 *=========================================================================*/

/**
 * @brief Common macro to fill out structure members for array followed by
 *        its size.
 */
#define RSC_ARRAY(arr) arr, ARRAY_SIZE(arr)

static rsc_cmd_t cam_rsc_rsc_sleep[] =
{
//MAIN:
  0x21022004,  //0x000: 0x2004   BEQ       channel_to_use_0=0            CHANNEL_1
               //0x002: 0x2102   BEQ       channel_switch_active=0       CHECK_ACTIVE_PULSE_CH_0
  0x40045004,  //0x004: 0x5004   SET1      channel_busy
               //0x006: 0x4004   SET0      channel_busy
//ACTIVE_CH_O:
  0x50055000,  //0x008: 0x5000   SET1      active_tcs_trigger_ch0
               //0x00a: 0x5005   SET1      pwr_st_idx_bit_0
  0x70045006,  //0x00c: 0x5006   SET1      pwr_st_change_req
               //0x00e: 0x7004   WAIT1     pwr_st_change_ack
  0x70004006,  //0x010: 0x4006   SET0      pwr_st_change_req
               //0x012: 0x7000   WAIT1     active_tcs_complete_ch0
  0x18004000,  //0x014: 0x4000   SET0      active_tcs_trigger_ch0
               //0x016: 0x1800   JMP       MAIN
//CHECK_ACTIVE_PULSE_CH_0:
  0x18012083,  //0x018: 0x2083   BEQ       active_tcs_vote=0             CHECK_IDLE_CH_0
               //0x01a: 0x1801   JMP       ACTIVE_CH_O
//CHECK_IDLE_CH_0:
  0x500120c8,  //0x01c: 0x20c8   BEQ       idle_tcs_vote=0               END
               //0x01e: 0x5001   SET1      idle_tcs_trigger_ch0
  0x50064005,  //0x020: 0x4005   SET0      pwr_st_idx_bit_0
               //0x022: 0x5006   SET1      pwr_st_change_req
  0x40067004,  //0x024: 0x7004   WAIT1     pwr_st_change_ack
               //0x026: 0x4006   SET0      pwr_st_change_req
  0x40017001,  //0x028: 0x7001   WAIT1     idle_tcs_complete_ch0
               //0x02a: 0x4001   SET0      idle_tcs_trigger_ch0
  0x20481800,  //0x02c: 0x1800   JMP       MAIN
//CHANNEL_1:
               //0x02e: 0x2048   BEQ       channel_to_use_1=0            END
  0x50042106,  //0x030: 0x2106   BEQ       channel_switch_active=0       CHECK_ACTIVE_PULSE_CH_1
               //0x032: 0x5004   SET1      channel_busy
  0x50024004,  //0x034: 0x4004   SET0      channel_busy
//ACTIVE_CH_1:
               //0x036: 0x5002   SET1      active_tcs_trigger_ch1
  0x50065005,  //0x038: 0x5005   SET1      pwr_st_idx_bit_0
               //0x03a: 0x5006   SET1      pwr_st_change_req
  0x40067004,  //0x03c: 0x7004   WAIT1     pwr_st_change_ack
               //0x03e: 0x4006   SET0      pwr_st_change_req
  0x40027002,  //0x040: 0x7002   WAIT1     active_tcs_complete_ch1
               //0x042: 0x4002   SET0      active_tcs_trigger_ch1
  0x20871800,  //0x044: 0x1800   JMP       MAIN
//CHECK_ACTIVE_PULSE_CH_1:
               //0x046: 0x2087   BEQ       active_tcs_vote=0             CHECK_IDLE_CH_1
  0x20c81805,  //0x048: 0x1805   JMP       ACTIVE_CH_1
//CHECK_IDLE_CH_1:
               //0x04a: 0x20c8   BEQ       idle_tcs_vote=0               END
  0x40055003,  //0x04c: 0x5003   SET1      idle_tcs_trigger_ch1
               //0x04e: 0x4005   SET0      pwr_st_idx_bit_0
  0x70045006,  //0x050: 0x5006   SET1      pwr_st_change_req
               //0x052: 0x7004   WAIT1     pwr_st_change_ack
  0x70034006,  //0x054: 0x4006   SET0      pwr_st_change_req
               //0x056: 0x7003   WAIT1     idle_tcs_complete_ch1
  0x18004003,  //0x058: 0x4003   SET0      idle_tcs_trigger_ch1
               //0x05a: 0x1800   JMP       MAIN
//END:
  0x00001000   //0x05c: 0x1000   RETURN
               //0x05e: 0x0000
};

static rsc_cmd_t pcie_rsc_rsc_sleep[] = {
//br_MAIN:
  0xe5a0e3a3,  //0x000: 0xa3   SET1      rsc_pdc_start_monitoring
               //0x001: 0xe3   WAIT1     pdc_rsc_monitoring_started
               //0x002: 0xa0   SET1      hidden_tcs_trig_from_seq
               //0x003: 0xe5   WAIT1     hidden_tcs_comp
  0x81e1a183,  //0x004: 0x83   SET0      rsc_pdc_start_monitoring
               //0x005: 0xa1   SET1      rsc_pdc_shutdown_req
               //0x006: 0xe1   WAIT1     pdc_rsc_shutdown_ack
               //0x007: 0x81   SET0      rsc_pdc_shutdown_req
  0xe2a2e0a5,  //0x008: 0xa5   SET1      seq_wait_wakeup
               //0x009: 0xe0   WAIT1     wakeup_event
               //0x00a: 0xa2   SET1      rsc_pdc_bringup_req
               //0x00b: 0xe2   WAIT1     pdc_rsc_bringup_ack
  0x84e4a482,  //0x00c: 0x82   SET0      rsc_pdc_bringup_req
               //0x00d: 0xa4   SET1      rsc_pdc_start_replay
               //0x00e: 0xe4   WAIT1     pdc_rsc_replay_done
               //0x00f: 0x84   SET0      rsc_pdc_start_replay
  0x00000020   //0x010: 0x20   RETURN
               //0x011: 0x00
               //0x012: 0x00
               //0x013: 0x00
};

static rsc_hal_br_info_t cam_rsc_seq_br_info[] =
{
  {0x0}, // MAIN
  {0x8}, // ACTIVE_CH_O
  {0x18}, // CHECK_ACTIVE_PULSE_CH_0
  {0x1c}, // CHECK_IDLE_CH_0
  {0x2e}, // CHANNEL_1
  {0x36}, // ACTIVE_CH_1
  {0x46}, // CHECK_ACTIVE_PULSE_CH_1
  {0x4a}, // CHECK_IDLE_CH_1
  {0x5c}  // END
};

/**
 * @brief RSC mode configurations
 */
static rsc_hal_bsp_mode_t cam_rsc_modes[] =
{
  {
    {RSC_ARRAY(cam_rsc_rsc_sleep)},
    0,
    0,
    0,
    0,
    cam_rsc_seq_br_info,
     ARRAY_SIZE(cam_rsc_seq_br_info),
    NULL,
    0
  },
};

static rsc_hal_bsp_mode_t pcie_rsc_modes[] =
{
  {
    {RSC_ARRAY(pcie_rsc_rsc_sleep)},
    0,
    0,
    0,
    0,
    NULL,
    0,
    NULL,
    0
  },
};

/**
 * @brief Array containing necessary information of each rsc instance on a
 *        given subsystem.
 */
rsc_t g_rsc_instances[] =
{
  {
    "cam",
	EXTENDED_32BIT_MODE,
    cam_rsc_modes,
    ARRAY_SIZE(cam_rsc_modes),
    (uint8 *)(TITAN_SS_BASE + 0x001d4000),
    0x0
  },
  {
    "pcie",
	EXTENDED_32BIT_MODE,
    pcie_rsc_modes,
    ARRAY_SIZE(pcie_rsc_modes),
    (uint8 *)(PCIE_RSCC_BASE),
    0x0
  }

};

/**
 * @brief Variable to indicate rsc instance counts.
 *
 * @note This will be externed in to rsc target file.
 */
size_t g_rsc_count =
  sizeof(g_rsc_instances)/sizeof(g_rsc_instances[0]);

