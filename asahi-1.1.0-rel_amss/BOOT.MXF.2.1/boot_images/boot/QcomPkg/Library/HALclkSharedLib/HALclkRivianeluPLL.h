#ifndef __HALCLKRIVIANELUPLL_H__
#define __HALCLKRIVIANELUPLL_H__
/*
==============================================================================

FILE:         HALclkRivianeluPLL.h

DESCRIPTION:
  Internal, chipset specific PLL definitions for the clock HAL module.

==============================================================================
             Copyright (c) 2023 QUALCOMM Technologies Incorporated. All Rights Reserved.
                    QUALCOMM Proprietary and Confidential.
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/


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
#define HWIO_PLL_MODE_OFFS                                              0x00000000
#define HWIO_PLL_OPMODE_OFFS                                            0x00000004
#define HWIO_PLL_STATE_OFFS                                             0x00000008
#define HWIO_PLL_STATUS_OFFS                                            0x0000000C
#define HWIO_PLL_L_VAL_OFFS                                             0x00000010  
#define HWIO_PLL_USER_CTL_OFFS                                          0x00000014
#define HWIO_PLL_USER_CTL_U_OFFS                                        0x00000018  
#define HWIO_PLL_CONFIG_CTL_OFFS                                        0x0000001C
#define HWIO_PLL_CONFIG_CTL_U_OFFS                                      0x00000020
#define HWIO_PLL_CONFIG_CTL_U1_OFFS                                     0x00000024
#define HWIO_PLL_CONFIG_CTL_U2_OFFS                                     0x00000028
#define HWIO_PLL_TEST_CTL_OFFS                                          0x0000002C
#define HWIO_PLL_TEST_CTL_U_OFFS                                        0x00000030
                                                                        
/*
 * PLL_MODE register definitions.
 */
#define HWIO_PLL_MODE_RMSK                                                                          0xffffffff
#define HWIO_PLL_MODE_PLL_LOCK_DET_BMSK                                                             0x80000000
#define HWIO_PLL_MODE_PLL_LOCK_DET_SHFT                                                                     31
#define HWIO_PLL_MODE_FREQ_LOCK_DET_BMSK                                                            0x40000000
#define HWIO_PLL_MODE_FREQ_LOCK_DET_SHFT                                                                    30
#define HWIO_PLL_MODE_PLL_ENABLE_STATUS_BMSK                                                        0x20000000
#define HWIO_PLL_MODE_PLL_ENABLE_STATUS_SHFT                                                                29
#define HWIO_PLL_MODE_RESERVE_BITS28_24_BMSK                                                        0x1f000000
#define HWIO_PLL_MODE_RESERVE_BITS28_24_SHFT                                                                24
#define HWIO_PLL_MODE_RESERVE_BITS23_15_BMSK                                                          0xff8000
#define HWIO_PLL_MODE_RESERVE_BITS23_15_SHFT                                                                15
#define HWIO_PLL_MODE_PLL_LATCH_INPUT_BMSK                                                              0x4000
#define HWIO_PLL_MODE_PLL_LATCH_INPUT_SHFT                                                                  14
#define HWIO_PLL_MODE_PLL_ACK_LATCH_BMSK                                                                0x2000
#define HWIO_PLL_MODE_PLL_ACK_LATCH_SHFT                                                                    13
#define HWIO_PLL_MODE_RESERVE_BITS12_9_BMSK                                                             0x1e00
#define HWIO_PLL_MODE_RESERVE_BITS12_9_SHFT                                                                  9
#define HWIO_PLL_MODE_RESERVE_BIT8_BMSK                                                                  0x100
#define HWIO_PLL_MODE_RESERVE_BIT8_SHFT                                                                      8
#define HWIO_PLL_MODE_RESERVE_BIT7_BMSK                                                                   0x80
#define HWIO_PLL_MODE_RESERVE_BIT7_SHFT                                                                      7
#define HWIO_PLL_MODE_OUT_AUX_HW_CTL_BMSK                                                                 0x40
#define HWIO_PLL_MODE_OUT_AUX_HW_CTL_SHFT                                                                    6
#define HWIO_PLL_MODE_RESERVE_BIT5_BMSK                                                                   0x20
#define HWIO_PLL_MODE_RESERVE_BIT5_SHFT                                                                      5
#define HWIO_PLL_MODE_OUT_EVEN_HW_CTL_BMSK                                                                0x10
#define HWIO_PLL_MODE_OUT_EVEN_HW_CTL_SHFT                                                                   4
#define HWIO_PLL_MODE_OUT_MAIN_HW_CTL_BMSK                                                                 0x8
#define HWIO_PLL_MODE_OUT_MAIN_HW_CTL_SHFT                                                                   3
#define HWIO_PLL_MODE_PLL_RESET_N_BMSK                                                                     0x4
#define HWIO_PLL_MODE_PLL_RESET_N_SHFT                                                                       2
#define HWIO_PLL_MODE_PLL_BYPASSNL_BMSK                                                                    0x2
#define HWIO_PLL_MODE_PLL_BYPASSNL_SHFT                                                                      1
#define HWIO_PLL_MODE_PLL_OUTCTRL_BMSK                                                                     0x1
#define HWIO_PLL_MODE_PLL_OUTCTRL_SHFT                                                                       0


/*
 * PLL_L_VAL register definitions.
 */

#define HWIO_PLL_L_VAL_PLL_L_VAL_BMSK                                                                    0x3ff
#define HWIO_PLL_L_VAL_PLL_L_VAL_SHFT                                                                        0


/*
 * PLL_USER_CTL register definitions.
 */
#define HWIO_PLL_USER_CTL_RESERVE_BITS31_28_BMSK                                                    0xf0000000
#define HWIO_PLL_USER_CTL_RESERVE_BITS31_28_SHFT                                                            28
#define HWIO_PLL_USER_CTL_LATCH_INTERFACE_BYPASS_BMSK                                                0x8000000
#define HWIO_PLL_USER_CTL_LATCH_INTERFACE_BYPASS_SHFT                                                       27
#define HWIO_PLL_USER_CTL_OFF_WHEN_NO_VOTE_BMSK                                                      0x4000000
#define HWIO_PLL_USER_CTL_OFF_WHEN_NO_VOTE_SHFT                                                             26
#define HWIO_PLL_USER_CTL_ENABLE_VOTE_RUN_BMSK                                                       0x2000000
#define HWIO_PLL_USER_CTL_ENABLE_VOTE_RUN_SHFT                                                              25
#define HWIO_PLL_USER_CTL_PRE_DIV_RATIO_BMSK                                                         0x1c00000
#define HWIO_PLL_USER_CTL_PRE_DIV_RATIO_SHFT                                                                22
#define HWIO_PLL_USER_CTL_RESERVE_BITS21_14_BMSK                                                      0x3fc000
#define HWIO_PLL_USER_CTL_RESERVE_BITS21_14_SHFT                                                            14
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_EVEN_BMSK                                                      0x3c00
#define HWIO_PLL_USER_CTL_POST_DIV_RATIO_EVEN_SHFT                                                          10
#define HWIO_PLL_USER_CTL_RESERVE_BITS9_5_BMSK                                                           0x3e0
#define HWIO_PLL_USER_CTL_RESERVE_BITS9_5_SHFT                                                               5
#define HWIO_PLL_USER_CTL_PLLOUT_TEST_EN_BMSK                                                             0x10
#define HWIO_PLL_USER_CTL_PLLOUT_TEST_EN_SHFT                                                                4
#define HWIO_PLL_USER_CTL_PLLOUT_AUX_EN_BMSK                                                               0x8
#define HWIO_PLL_USER_CTL_PLLOUT_AUX_EN_SHFT                                                                 3
#define HWIO_PLL_USER_CTL_RESERVE_BIT2_BMSK                                                                0x4
#define HWIO_PLL_USER_CTL_RESERVE_BIT2_SHFT                                                                  2
#define HWIO_PLL_USER_CTL_PLLOUT_EVEN_EN_BMSK                                                              0x2
#define HWIO_PLL_USER_CTL_PLLOUT_EVEN_EN_SHFT                                                                1
#define HWIO_PLL_USER_CTL_PLLOUT_MAIN_EN_BMSK                                                              0x1
#define HWIO_PLL_USER_CTL_PLLOUT_MAIN_EN_SHFT                                                                0

/*
 * PLL_USER_CTL_U register definitions.
 */
#define HWIO_PLL_USER_CTL_U_RESERVE_BITS63_58_BMSK                                                  0xfc000000
#define HWIO_PLL_USER_CTL_U_RESERVE_BITS63_58_SHFT                                                          26
#define HWIO_PLL_USER_CTL_U_PDIV_RATIO_AUX_DIV3_BMSK                                                 0x2000000
#define HWIO_PLL_USER_CTL_U_PDIV_RATIO_AUX_DIV3_SHFT                                                        25
#define HWIO_PLL_USER_CTL_U_LOCK_DET_STAY_LOW_BMSK                                                   0x1000000
#define HWIO_PLL_USER_CTL_U_LOCK_DET_STAY_LOW_SHFT                                                          24
#define HWIO_PLL_USER_CTL_U_LOCK_DET_STAY_HIGH_BMSK                                                   0x800000
#define HWIO_PLL_USER_CTL_U_LOCK_DET_STAY_HIGH_SHFT                                                         23
#define HWIO_PLL_USER_CTL_U_LOCK_DET_REPLICA_EN_BMSK                                                  0x400000
#define HWIO_PLL_USER_CTL_U_LOCK_DET_REPLICA_EN_SHFT                                                        22
#define HWIO_PLL_USER_CTL_U_PRESCALER_SEL_BIT2_BIT0_BMSK                                              0x300000
#define HWIO_PLL_USER_CTL_U_PRESCALER_SEL_BIT2_BIT0_SHFT                                                    20
#define HWIO_PLL_USER_CTL_U_FREQ_BAND_BMSK                                                             0xc0000
#define HWIO_PLL_USER_CTL_U_FREQ_BAND_SHFT                                                                  18
#define HWIO_PLL_USER_CTL_U_LOCK_DET_SEL_BMSK                                                          0x30000
#define HWIO_PLL_USER_CTL_U_LOCK_DET_SEL_SHFT                                                               16
#define HWIO_PLL_USER_CTL_U_PRESCALER_SEL_BIT1_BMSK                                                     0x8000
#define HWIO_PLL_USER_CTL_U_PRESCALER_SEL_BIT1_SHFT                                                         15
#define HWIO_PLL_USER_CTL_U_PDIV_RATIO_EVEN_BMSK                                                        0x7800
#define HWIO_PLL_USER_CTL_U_PDIV_RATIO_EVEN_SHFT                                                            11
#define HWIO_PLL_USER_CTL_U_POST_DIV_RATIO_AUX_BMSK                                                      0x780
#define HWIO_PLL_USER_CTL_U_POST_DIV_RATIO_AUX_SHFT                                                          7
#define HWIO_PLL_USER_CTL_U_PDIV_RATIO_AUX_BMSK                                                           0x78
#define HWIO_PLL_USER_CTL_U_PDIV_RATIO_AUX_SHFT                                                              3
#define HWIO_PLL_USER_CTL_U_RESERVE_BITS34_32_BMSK                                                         0x7
#define HWIO_PLL_USER_CTL_U_RESERVE_BITS34_32_SHFT                                                           0

#endif  /* __HALCLKRIVIANELUPLL_H__ */
