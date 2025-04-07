#ifndef HALCLKPONGOELUPLL_H
#define HALCLKPONGOELUPLL_H
/*
==============================================================================

FILE:         HALclkPongoeluPLL.h

DESCRIPTION:
  Internal, chipset specific PLL definitions for the clock HAL module.

==============================================================================
    Copyright (c) 2023 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

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
#define HWIO_PLL_MODE_OFFS                                  0x00000000
#define HWIO_PLL_OPMODE_OFFS                                0x00000004
#define HWIO_PLL_STATE_OFFS                                 0x00000008
#define HWIO_PLL_STATUS_OFFS                                0x0000000c
#define HWIO_PLL_L_VAL_OFFS                                 0x00000010
#define HWIO_PLL_USER_CTL_OFFS                              0x00000014
#define HWIO_PLL_USER_CTL_U_OFFS                            0x00000018
#define HWIO_PLL_CONFIG_CTL_OFFS                            0x0000001C
#define HWIO_PLL_CONFIG_CTL_U_OFFS                          0x00000020
#define HWIO_PLL_CONFIG_CTL_U1_OFFS                         0x00000024
#define HWIO_PLL_CONFIG_CTL_U2_OFFS                         0x00000028
#define HWIO_PLL_TEST_CTL_OFFS                              0x0000002C
#define HWIO_PLL_TEST_CTL_U_OFFS                            0x00000030
#define HWIO_PLL_TEST_CTL_U1_OFFS                           0x00000034
#define HWIO_PLL_TEST_CTL_U2_OFFS                           0x00000038
#define HWIO_PLL_TEST_CTL_U3_OFFS                           0x0000003C
#define HWIO_PLL_FREQ_CTL_OFFS                              0x00000040
#define HWIO_PLL_FREQ_CTL_U_OFFS                            0x00000044
#define HWIO_PLL_SPARE_OFF                                  0x00000048
#define HWIO_PLL_FUSA_STATUS_REGISTER_OFFS                  0x00000080

/*
 * PLL_MODE register definitions.
 */
#define HWIO_PLL_MODE_PLL_LOCK_DET_BMSK                                                       0x80000000
#define HWIO_PLL_MODE_PLL_LOCK_DET_SHFT                                                               31
#define HWIO_PLL_MODE_PLL_LOCK_DET_COARSE_BMSK                                                0x40000000
#define HWIO_PLL_MODE_PLL_LOCK_DET_COARSE_SHFT                                                        30
#define HWIO_PLL_MODE_RESERVE_BITS29_13_BMSK                                                  0x3fffe000
#define HWIO_PLL_MODE_RESERVE_BITS29_13_SHFT                                                          13
#define HWIO_PLL_MODE_PLL_CLOCK_SELECT_BMSK                                                       0x1000
#define HWIO_PLL_MODE_PLL_CLOCK_SELECT_SHFT                                                           12
#define HWIO_PLL_MODE_PLL_REQUESTS_CAL_BMSK                                                        0x800
#define HWIO_PLL_MODE_PLL_REQUESTS_CAL_SHFT                                                           11
#define HWIO_PLL_MODE_PLL_CAL_XO_PRESENT_BMSK                                                      0x400
#define HWIO_PLL_MODE_PLL_CAL_XO_PRESENT_SHFT                                                         10
#define HWIO_PLL_MODE_PLL_IN_CALIBRATION_BMSK                                                      0x200
#define HWIO_PLL_MODE_PLL_IN_CALIBRATION_SHFT                                                          9
#define HWIO_PLL_MODE_RESERVE_BIT8_BMSK                                                            0x100
#define HWIO_PLL_MODE_RESERVE_BIT8_SHFT                                                                8
#define HWIO_PLL_MODE_OUT_TEST_HW_CTL_BMSK                                                          0x80
#define HWIO_PLL_MODE_OUT_TEST_HW_CTL_SHFT                                                             7
#define HWIO_PLL_MODE_RESERVE_BIT6_BMSK                                                             0x40
#define HWIO_PLL_MODE_RESERVE_BIT6_SHFT                                                                6
#define HWIO_PLL_MODE_RESERVE_BIT5_BMSK                                                             0x20
#define HWIO_PLL_MODE_RESERVE_BIT5_SHFT                                                                5
#define HWIO_PLL_MODE_OUT_EVEN_HW_CTL_BMSK                                                          0x10
#define HWIO_PLL_MODE_OUT_EVEN_HW_CTL_SHFT                                                             4
#define HWIO_PLL_MODE_OUT_MAIN_HW_CTL_BMSK                                                           0x8
#define HWIO_PLL_MODE_OUT_MAIN_HW_CTL_SHFT                                                             3
#define HWIO_PLL_MODE_PLL_RESET_N_BMSK                                                               0x4
#define HWIO_PLL_MODE_PLL_RESET_N_SHFT                                                                 2
#define HWIO_PLL_MODE_RESERVE_BIT1_BMSK                                                              0x2
#define HWIO_PLL_MODE_RESERVE_BIT1_SHFT                                                                1
#define HWIO_PLL_MODE_PLL_OUTCTRL_BMSK                                                               0x1
#define HWIO_PLL_MODE_PLL_OUTCTRL_SHFT                                                                 0

/*
 * PLL_L_VAL register definitions.
 */
#define HWIO_PLL_L_VAL_PLL_L_BMSK                                                                  0xfff
#define HWIO_PLL_L_VAL_PLL_L_SHFT                                                                      0

/*
 * PLL_USER_CTL register definitions.
 */
#define HWIO_PLL_USER_CTL_RESERVE_BITS31_11_BMSK                                              0xfffff800
#define HWIO_PLL_USER_CTL_RESERVE_BITS31_11_SHFT                                                      11
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_EVEN_BMSK                                                 0x400
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_EVEN_SHFT                                                    10
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_MAIN_BMSK                                                 0x3c0
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_MAIN_SHFT                                                     6
#define HWIO_PLL_USER_CTL_RESERVE_BIT5_BMSK                                                         0x20
#define HWIO_PLL_USER_CTL_RESERVE_BIT5_SHFT                                                            5
#define HWIO_PLL_USER_CTL_PLLOUT_TEST_EN_BMSK                                                       0x10
#define HWIO_PLL_USER_CTL_PLLOUT_TEST_EN_SHFT                                                          4
#define HWIO_PLL_USER_CTL_RESERVE_BITS3_2_BMSK                                                       0xc
#define HWIO_PLL_USER_CTL_RESERVE_BITS3_2_SHFT                                                         2
#define HWIO_PLL_USER_CTL_PLLOUT_EVEN_EN_BMSK                                                        0x2
#define HWIO_PLL_USER_CTL_PLLOUT_EVEN_EN_SHFT                                                          1
#define HWIO_PLL_USER_CTL_PLLOUT_MAIN_EN_BMSK                                                        0x1
#define HWIO_PLL_USER_CTL_PLLOUT_MAIN_EN_SHFT                                                          0


/*
 * PLL_USER_CTL_U register definitions.
 */
#define HWIO_PLL_USER_CTL_U_ENABLE_32KHZ_FAST_LOCK_BMSK                                       0x80000000
#define HWIO_PLL_USER_CTL_U_ENABLE_32KHZ_FAST_LOCK_SHFT                                               31
#define HWIO_PLL_USER_CTL_U_OUT_CLK_POLARITY_BMSK                                             0x40000000
#define HWIO_PLL_USER_CTL_U_OUT_CLK_POLARITY_SHFT                                                     30
#define HWIO_PLL_USER_CTL_U_USR_FULL_SAVE_BMSK                                                0x20000000
#define HWIO_PLL_USER_CTL_U_USR_FULL_SAVE_SHFT                                                        29
#define HWIO_PLL_USER_CTL_U_USR_SAVE_SELECT_BMSK                                              0x18000000
#define HWIO_PLL_USER_CTL_U_USR_SAVE_SELECT_SHFT                                                      27
#define HWIO_PLL_USER_CTL_U_ENABLE_LOW_LATENCY_CLK_BMSK                                        0x4000000
#define HWIO_PLL_USER_CTL_U_ENABLE_LOW_LATENCY_CLK_SHFT                                               26
#define HWIO_PLL_USER_CTL_U_ENABLE_STANDBY_CLK_BMSK                                            0x2000000
#define HWIO_PLL_USER_CTL_U_ENABLE_STANDBY_CLK_SHFT                                                   25
#define HWIO_PLL_USER_CTL_U_SET_MAX_COMP_RATE_BMSK                                             0x1000000
#define HWIO_PLL_USER_CTL_U_SET_MAX_COMP_RATE_SHFT                                                    24
#define HWIO_PLL_USER_CTL_U_ENABLE_CONT_CAL_BMSK                                                0x800000
#define HWIO_PLL_USER_CTL_U_ENABLE_CONT_CAL_SHFT                                                      23
#define HWIO_PLL_USER_CTL_U_XO_FREQUENCY_SELECT_BMSK                                            0x400000
#define HWIO_PLL_USER_CTL_U_XO_FREQUENCY_SELECT_SHFT                                                  22
#define HWIO_PLL_USER_CTL_U_INTERNAL_CLOCK_SELECTION_BMSK                                       0x300000
#define HWIO_PLL_USER_CTL_U_INTERNAL_CLOCK_SELECTION_SHFT                                             20
#define HWIO_PLL_USER_CTL_U_RESERVE_BITS51_49_BMSK                                               0xe0000
#define HWIO_PLL_USER_CTL_U_RESERVE_BITS51_49_SHFT                                                    17
#define HWIO_PLL_USER_CTL_U_INITIAL_OUTPUT_CLOCK_MUX_BMSK                                        0x18000
#define HWIO_PLL_USER_CTL_U_INITIAL_OUTPUT_CLOCK_MUX_SHFT                                             15
#define HWIO_PLL_USER_CTL_U_KEEP_BIAS_ON_IN_STBY_BMSK                                             0x4000
#define HWIO_PLL_USER_CTL_U_KEEP_BIAS_ON_IN_STBY_SHFT                                                 14
#define HWIO_PLL_USER_CTL_U_XO_CLK_AT_OUT_BMSK                                                    0x2000
#define HWIO_PLL_USER_CTL_U_XO_CLK_AT_OUT_SHFT                                                        13
#define HWIO_PLL_USER_CTL_U_CALIBRATION_SETTING_BMSK                                              0x1000
#define HWIO_PLL_USER_CTL_U_CALIBRATION_SETTING_SHFT                                                  12
#define HWIO_PLL_USER_CTL_U_USE_RESTORE_BMSK                                                       0x800
#define HWIO_PLL_USER_CTL_U_USE_RESTORE_SHFT                                                          11
#define HWIO_PLL_USER_CTL_U_REQUEST_CAL_BMSK                                                       0x400
#define HWIO_PLL_USER_CTL_U_REQUEST_CAL_SHFT                                                          10
#define HWIO_PLL_USER_CTL_U_VREF_REG_VAL_BMSK                                                      0x3f0
#define HWIO_PLL_USER_CTL_U_VREF_REG_VAL_SHFT                                                          4
#define HWIO_PLL_USER_CTL_U_USE_REGISTERVAL_VREF_SEL_BMSK                                            0x8
#define HWIO_PLL_USER_CTL_U_USE_REGISTERVAL_VREF_SEL_SHFT                                              3
#define HWIO_PLL_USER_CTL_U_CAL_SCALING_BMSK                                                         0x6
#define HWIO_PLL_USER_CTL_U_CAL_SCALING_SHFT                                                           1
#define HWIO_PLL_USER_CTL_U_USE_EXTERNAL_CLK_REF_BMSK                                                0x1
#define HWIO_PLL_USER_CTL_U_USE_EXTERNAL_CLK_REF_SHFT                                                  0




#endif /* HALCLKPONGOELUPLL_H */
