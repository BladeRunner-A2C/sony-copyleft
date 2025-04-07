#ifndef HALCLKZONDAELUPLL_H
#define HALCLKZONDAELUPLL_H
/*
==============================================================================

FILE:         HALclkZondaeluPLL.h

DESCRIPTION:
  Internal, chipset specific PLL definitions for the clock HAL module.
  
    Copyright (c) 2023 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include "stdbool.h"
#include "HALclkInternal.h"


/* ============================================================================
**    Definitions
** ==========================================================================*/

/*
 * Registers for programming operational mode
 */
#define HAL_PLL_OPMODE_STANDBY  0x0
#define HAL_PLL_OPMODE_RUN      0x1
#define HAL_PLL_OPMODE_FREEZE   0x3


/*
 * PLL register offsets.
 */
#define HWIO_PLL_MODE_OFFS                                                  0x0
#define HWIO_PLL_L_VAL_OFFS                                                 0x4
#define HWIO_PLL_ALPHA_VAL_OFFS                                             0x8
#define HWIO_PLL_USER_CTL_OFFS                                              0xc
#define HWIO_PLL_USER_CTL_U_OFFS                                           0x10
#define HWIO_PLL_CONFIG_CTL_OFFS                                           0x14
#define HWIO_PLL_CONFIG_CTL_U_OFFS                                         0x18
#define HWIO_PLL_CONFIG_CTL_U1_OFFS                                        0x1c
#define HWIO_PLL_CONFIG_CTL_U2_OFFS                                        0x20
#define HWIO_PLL_TEST_CTL_OFFS                                             0x24
#define HWIO_PLL_TEST_CTL_U_OFFS                                           0x28
#define HWIO_PLL_TEST_CTL_U1_OFFS                                          0x2c
#define HWIO_PLL_OPMODE_OFFS                                               0x30
#define HWIO_PLL_SSC_OFFS                                                  0x34
#define HWIO_PLL_DROOP_CTL_OFFS                                            0x38
#define HWIO_PLL_STATUS_OFFS                                               0x3c
#define HWIO_PLL_STATE_OFFS                                                0x40
/*
 * PLL_MODE register definitions.
 */
#define HWIO_PLL_MODE_PLL_LOCK_DET_BMSK                                                    0x80000000
#define HWIO_PLL_MODE_PLL_LOCK_DET_SHFT                                                            31
#define HWIO_PLL_MODE_FREQ_LOCK_DET_BMSK                                                   0x40000000
#define HWIO_PLL_MODE_FREQ_LOCK_DET_SHFT                                                           30
#define HWIO_PLL_MODE_PLL_ENABLE_STATUS_BMSK                                               0x20000000
#define HWIO_PLL_MODE_PLL_ENABLE_STATUS_SHFT                                                       29
#define HWIO_PLL_MODE_RESERVE_BITS28_16_BMSK                                               0x1fff0000
#define HWIO_PLL_MODE_RESERVE_BITS28_16_SHFT                                                       16
#define HWIO_PLL_MODE_PLL_PLLTEST_BMSK                                                         0x8000
#define HWIO_PLL_MODE_PLL_PLLTEST_SHFT                                                             15
#define HWIO_PLL_MODE_PLL_LATCH_INPUT_BMSK                                                     0x4000
#define HWIO_PLL_MODE_PLL_LATCH_INPUT_SHFT                                                         14
#define HWIO_PLL_MODE_PLL_ACK_LATCH_BMSK                                                       0x2000
#define HWIO_PLL_MODE_PLL_ACK_LATCH_SHFT                                                           13
#define HWIO_PLL_MODE_RESERVE_BITS12_8_BMSK                                                    0x1f00
#define HWIO_PLL_MODE_RESERVE_BITS12_8_SHFT                                                         8
#define HWIO_PLL_MODE_OUT_TEST_HW_CTL_BMSK                                                       0x80
#define HWIO_PLL_MODE_OUT_TEST_HW_CTL_SHFT                                                          7
#define HWIO_PLL_MODE_OUT_AUX_HW_CTL_BMSK                                                        0x40
#define HWIO_PLL_MODE_OUT_AUX_HW_CTL_SHFT                                                           6
#define HWIO_PLL_MODE_RESERVE_BIT5_BMSK                                                          0x20
#define HWIO_PLL_MODE_RESERVE_BIT5_SHFT                                                             5
#define HWIO_PLL_MODE_OUT_EVEN_HW_CTL_BMSK                                                       0x10
#define HWIO_PLL_MODE_OUT_EVEN_HW_CTL_SHFT                                                          4
#define HWIO_PLL_MODE_OUT_MAIN_HW_CTL_BMSK                                                        0x8
#define HWIO_PLL_MODE_OUT_MAIN_HW_CTL_SHFT                                                          3
#define HWIO_PLL_MODE_PLL_RESET_N_BMSK                                                            0x4
#define HWIO_PLL_MODE_PLL_RESET_N_SHFT                                                              2
#define HWIO_PLL_MODE_PLL_BYPASSNL_BMSK                                                           0x2
#define HWIO_PLL_MODE_PLL_BYPASSNL_SHFT                                                             1
#define HWIO_PLL_MODE_PLL_OUTCTRL_BMSK                                                            0x1
#define HWIO_PLL_MODE_PLL_OUTCTRL_SHFT                                                              0


/*
 * PLL_L_VAL register definitions.
 */
#define HWIO_PLL_L_VAL_PLL_L_BMSK                                                                0xff
#define HWIO_PLL_L_VAL_PLL_L_SHFT                                                                   0


/*
 * PLL_ALPHA_VAL register definitions.
 */
#define HWIO_PLL_ALPHA_VAL_PLL_ALPHA_VAL_BMSK                                                  0xffff
#define HWIO_PLL_ALPHA_VAL_PLL_ALPHA_VAL_SHFT                                                       0
                                                       
/*
 * PLL_USER_CTL register definitions.
 */
#define HWIO_PLL_USER_CTL_OFF_WHEN_NO_VOTE_BMSK                                             0x4000000
#define HWIO_PLL_USER_CTL_OFF_WHEN_NO_VOTE_SHFT                                                    26
#define HWIO_PLL_USER_CTL_ENABLE_VOTE_RUN_BMSK                                              0x2000000
#define HWIO_PLL_USER_CTL_ENABLE_VOTE_RUN_SHFT                                                     25
#define HWIO_PLL_USER_CTL_RESERVE_BITS24_5_BMSK                                             0x1ffffe0
#define HWIO_PLL_USER_CTL_RESERVE_BITS24_5_SHFT                                                     5
#define HWIO_PLL_USER_CTL_PLLOUT_TEST_ENABLE_BMSK                                                0x10
#define HWIO_PLL_USER_CTL_PLLOUT_TEST_ENABLE_SHFT                                                   4
#define HWIO_PLL_USER_CTL_PLLOUT_AUX_ENABLE_BMSK                                                  0x8
#define HWIO_PLL_USER_CTL_PLLOUT_AUX_ENABLE_SHFT                                                    3
#define HWIO_PLL_USER_CTL_PLLOUT_AUX2_ENABLE_BMSK                                                 0x4
#define HWIO_PLL_USER_CTL_PLLOUT_AUX2_ENABLE_SHFT                                                   2
#define HWIO_PLL_USER_CTL_PLLOUT_EVEN_ENABLE_BMSK                                                 0x2
#define HWIO_PLL_USER_CTL_PLLOUT_EVEN_ENABLE_SHFT                                                   1
#define HWIO_PLL_USER_CTL_PLLOUT_MAIN_ENABLE_BMSK                                                 0x1
#define HWIO_PLL_USER_CTL_PLLOUT_MAIN_ENABLE_SHFT                                                   0


/*
 * PLL_USER_CTL_U register definitions.
 */
#define HWIO_PLL_USER_CTL_U_FRAC_ALPHA_MN_MODE_BMSK                                        0x10000000
#define HWIO_PLL_USER_CTL_U_FRAC_ALPHA_MN_MODE_SHFT                                                28
#define HWIO_PLL_USER_CTL_U_DCO_FREQ_STEP_BMSK                                              0x8000000
#define HWIO_PLL_USER_CTL_U_DCO_FREQ_STEP_SHFT                                                     27
#define HWIO_PLL_USER_CTL_U_SSC_MODE_ENABLE_BMSK                                            0x4000000
#define HWIO_PLL_USER_CTL_U_SSC_MODE_ENABLE_SHFT                                                   26
#define HWIO_PLL_USER_CTL_U_PLL_FRAC_MODE_ENABLE_BMSK                                       0x2000000
#define HWIO_PLL_USER_CTL_U_PLL_FRAC_MODE_ENABLE_SHFT                                              25
#define HWIO_PLL_USER_CTL_U_CTUNE_MIN_ENABLE_BMSK                                           0x1000000
#define HWIO_PLL_USER_CTL_U_CTUNE_MIN_ENABLE_SHFT                                                  24
#define HWIO_PLL_USER_CTL_U_L_VAL_CHANGE_TM_ENABLE_BMSK                                      0x800000
#define HWIO_PLL_USER_CTL_U_L_VAL_CHANGE_TM_ENABLE_SHFT                                            23
#define HWIO_PLL_USER_CTL_U_OLC_EXIT_COUNT_BMSK                                              0x400000
#define HWIO_PLL_USER_CTL_U_OLC_EXIT_COUNT_SHFT                                                    22
#define HWIO_PLL_USER_CTL_U_ADC_STATE_SYNC_DISABLE_BMSK                                      0x200000
#define HWIO_PLL_USER_CTL_U_ADC_STATE_SYNC_DISABLE_SHFT                                            21
#define HWIO_PLL_USER_CTL_U_ADC_LOCK_SYNC_DISABLE_BMSK                                       0x100000
#define HWIO_PLL_USER_CTL_U_ADC_LOCK_SYNC_DISABLE_SHFT                                             20
#define HWIO_PLL_USER_CTL_U_DROOP_BYPASS_IN_CFA_FFA_BMSK                                      0x80000
#define HWIO_PLL_USER_CTL_U_DROOP_BYPASS_IN_CFA_FFA_SHFT                                           19
#define HWIO_PLL_USER_CTL_U_CFA_MIN_TIME_DISABLE_BMSK                                         0x40000
#define HWIO_PLL_USER_CTL_U_CFA_MIN_TIME_DISABLE_SHFT                                              18
#define HWIO_PLL_USER_CTL_U_PRE_DIV_2_ENABLE_BMSK                                             0x20000
#define HWIO_PLL_USER_CTL_U_PRE_DIV_2_ENABLE_SHFT                                                  17
#define HWIO_PLL_USER_CTL_U_FREQ_PLL_LOCK_BMSK                                                0x10000
#define HWIO_PLL_USER_CTL_U_FREQ_PLL_LOCK_SHFT                                                     16
#define HWIO_PLL_USER_CTL_U_ADC_CAL_EXIT_BMSK                                                  0x8000
#define HWIO_PLL_USER_CTL_U_ADC_CAL_EXIT_SHFT                                                      15
#define HWIO_PLL_USER_CTL_U_PLLOUT_AUX2_ENABLE_BMSK                                            0x4000
#define HWIO_PLL_USER_CTL_U_PLLOUT_AUX2_ENABLE_SHFT                                                14
#define HWIO_PLL_USER_CTL_U_POST_DIV_CONTROL_BMSK                                              0x3000
#define HWIO_PLL_USER_CTL_U_POST_DIV_CONTROL_SHFT                                                  12
#define HWIO_PLL_USER_CTL_U_TEST_OUTPUT_SEL_BMSK                                                0x800
#define HWIO_PLL_USER_CTL_U_TEST_OUTPUT_SEL_SHFT                                                   11
#define HWIO_PLL_USER_CTL_U_INV_DIV_PLLOUT_BMSK                                                 0x400
#define HWIO_PLL_USER_CTL_U_INV_DIV_PLLOUT_SHFT                                                    10
#define HWIO_PLL_USER_CTL_U_INV_MAIN_PLLOUT_BMSK                                                0x200
#define HWIO_PLL_USER_CTL_U_INV_MAIN_PLLOUT_SHFT                                                    9
#define HWIO_PLL_USER_CTL_U_RESERVE_BITS40_37_BMSK                                              0x1e0
#define HWIO_PLL_USER_CTL_U_RESERVE_BITS40_37_SHFT                                                  5
#define HWIO_PLL_USER_CTL_U_DN_CONTROL_BMSK                                                      0x18
#define HWIO_PLL_USER_CTL_U_DN_CONTROL_SHFT                                                         3
#define HWIO_PLL_USER_CTL_U_PRE_CHARGE_DISABLE_BMSK                                               0x4
#define HWIO_PLL_USER_CTL_U_PRE_CHARGE_DISABLE_SHFT                                                 2
#define HWIO_PLL_USER_CTL_U_ATEST_MSB_BMSK                                                        0x2
#define HWIO_PLL_USER_CTL_U_ATEST_MSB_SHFT                                                          1
#define HWIO_PLL_USER_CTL_U_ICP_LEAK_DISABLE_BMSK                                                 0x1
#define HWIO_PLL_USER_CTL_U_ICP_LEAK_DISABLE_SHFT                                                   0



#endif /* HALCLKZONDAELUPLL_H */
