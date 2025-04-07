#ifndef UFS_PHY_SEQ_H
#define UFS_PHY_SEQ_H
 /**********************************************************************
 * ufs_phy_sequence.h
 *
 * UFS PHY sequence 
 *
 * Copyright (c) 2018-2023 Qualcomm Technologies Inc. All rights reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 *********************************************************************

                             Edit History

when         who     what, where, why
----------   ---     ----------------------------------------------------------  
2023-10-16   gml     Update for Palawan version 15.0
2022-08-30   jt      Update for Lanai version 9.0 
2022-03-02   jt      Update for Lanai PHY  
2022-02-23   sa      Move from Setting to Library Folder  
2022-01-13   jt      Update for Kailua version 5.0 
2021-05-19   sa      Update for Kailua PHY.
2020-10-07   jt      Update for PHY version 24.0 
2020-07-08   jt      Update for PHY version 23.0
2020-04-01   jt      Update for PHY version 22.0 
2020-01-17   jt      Update for PHY version 19.0
2019-07-31   jt      Fix RX_MODE_01 settings  
2019-05-14   jt      Kona Updates 
2019-02-14   jt      Update for HSG4 
2018-09-20   jt      Initial version.
-----------------------------------------------------------------------------*/

#include "ufs_bsp.h"
#include "UfsPhyHwio.h"
#include "aang_phy_hwio.h"

// Constant table for UFS-PHY initialization
static struct ufs_mphy_init_item ufs_bsp_mphy_init_table[] = {
   { 0x00, HWIO_UFS_MEM_UFS_PHY_SW_RESET_OFFS,                          0x01},
   { 0x00, HWIO_UFS_MEM_UFS_PHY_POWER_DOWN_CONTROL_OFFS,                0x01},
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_SYSCLK_EN_SEL_OFFS,                 0xD9},
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_CMN_CONFIG_1_OFFS,                  0x16},
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_HSCLK_SEL_1_OFFS,                   0x11}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_HSCLK_HS_SWITCH_SEL_1_OFFS,         0x00}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_LOCK_CMP_EN_OFFS,                   0x01},
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_PLL_IVCO_OFFS,                      0x1F},
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_PLL_IVCO_MODE1_OFFS,                0x1F},
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_CMN_IETRIM_OFFS,                    0x0A},
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_CMN_IPTRIM_OFFS,                    0x17},
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_VCO_TUNE_MAP_OFFS,                  0x04},
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_VCO_TUNE_INITVAL2_OFFS,             0x00},
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_DEC_START_MODE0_OFFS,               0x41},
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_CP_CTRL_MODE0_OFFS,                 0x06}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_PLL_RCTRL_MODE0_OFFS,               0x18}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_PLL_CCTRL_MODE0_OFFS,               0x14}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_LOCK_CMP1_MODE0_OFFS,               0x7F}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_LOCK_CMP2_MODE0_OFFS,               0x06},    
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_DEC_START_MODE1_OFFS,               0x4C}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_CP_CTRL_MODE1_OFFS,                 0x06}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_PLL_RCTRL_MODE1_OFFS,               0x18}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_PLL_CCTRL_MODE1_OFFS,               0x14}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_LOCK_CMP1_MODE1_OFFS,               0x99}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_COM_LOCK_CMP2_MODE1_OFFS,               0x07},    
   { 0x00, HWIO_UFS_MEM_QSERDES_TX0_LANE_MODE_1_OFFS,                   0x01},  
   { 0x00, HWIO_UFS_MEM_QSERDES_TX0_RES_CODE_LANE_OFFSET_TX_OFFS,       0x07},
   { 0x00, HWIO_UFS_MEM_QSERDES_TX0_RES_CODE_LANE_OFFSET_RX_OFFS,       0x0E},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_UCDR_FO_GAIN_RATE2_OFFS,            0x0C},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_UCDR_FO_GAIN_RATE4_OFFS,            0x0C},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_UCDR_SO_GAIN_RATE4_OFFS,            0x04},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_EQ_OFFSET_ADAPTOR_CNTRL1_OFFS,   0x14},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_UCDR_PI_CONTROLS_OFFS,              0x07},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_OFFSET_ADAPTOR_CNTRL3_OFFS,      0x0E},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_UCDR_FASTLOCK_COUNT_HIGH_RATE4_OFFS,0x02},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_UCDR_FASTLOCK_FO_GAIN_RATE4_OFFS,   0x1C},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_UCDR_FASTLOCK_SO_GAIN_RATE4_OFFS,   0x06},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_VGA_CAL_MAN_VAL_OFFS,               0x3E}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_EQU_ADAPTOR_CNTRL4_OFFS,         0x0F},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE_0_1_B0_OFFS,           0xCE},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE_0_1_B1_OFFS,           0xCE},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE_0_1_B2_OFFS,           0x18},   
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE_0_1_B3_OFFS,           0x1A},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE_0_1_B4_OFFS,           0x0F},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE_0_1_B6_OFFS,           0x60},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE2_B3_OFFS,              0x9E},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE2_B6_OFFS,              0x60},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE3_B3_OFFS,              0x9E},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE3_B4_OFFS,              0x0E},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE3_B5_OFFS,              0x36},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE3_B8_OFFS,              0x02},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE4_B0_OFFS,              0x1B}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE4_B1_OFFS,              0x1B},  
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE4_B2_OFFS,              0x20},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE4_B3_OFFS,              0xB9},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_MODE_RATE4_B4_OFFS,              0x5D}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_UCDR_SO_SATURATION_OFFS,            0x1F},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_UCDR_PI_CTRL1_OFFS,                 0x94},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_RX_TERM_BW_CTRL0_OFFS,              0xFA}, 
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_DLL0_FTUNE_CTRL_OFFS,               0x30},
   { STOP_CONDITION, 0,0}};

static struct ufs_mphy_init_item ufs_bsp_mphy_init_end_table[] = {
   { 0x00, HWIO_UFS_MEM_UFS_PHY_TX_MID_TERM_CTRL1_OFFS,                0x43},
   { CONDITIONAL_FLAG(RATE_A, 0), 
           HWIO_UFS_MEM_UFS_PHY_PCS_CTRL1_OFFS,                        0xC0},
   { CONDITIONAL_FLAG(RATE_B, 0), 
           HWIO_UFS_MEM_UFS_PHY_PCS_CTRL1_OFFS,                        0xC1},   
   { 0x00, HWIO_UFS_MEM_UFS_PHY_PLL_CNTL_OFFS,                         0x33},
   { 0x00, HWIO_UFS_MEM_UFS_PHY_TX_HSGEAR_CAPABILITY_OFFS,             0x05},
   { 0x00, HWIO_UFS_MEM_UFS_PHY_RX_HSGEAR_CAPABILITY_OFFS,             0x05},
   { 0x00, HWIO_UFS_MEM_UFS_PHY_TX_LARGE_AMP_DRV_LVL_OFFS,             0x0F},
   { 0x00, HWIO_UFS_MEM_UFS_PHY_RX_SIGDET_CTRL2_OFFS,                  0x68},
   { 0x00, HWIO_UFS_MEM_UFS_PHY_RX_HS_G5_SYNC_LENGTH_CAPABILITY_OFFS,  0x4D},
   { 0x00, HWIO_UFS_MEM_UFS_PHY_RX_HSG5_SYNC_WAIT_TIME_OFFS,           0x9E},   
   { 0X00, HWIO_UFS_MEM_UFS_PHY_TX_POST_EMP_LVL_S4_OFFS,               0x0E}, 
   { 0X00, HWIO_UFS_MEM_UFS_PHY_TX_POST_EMP_LVL_S5_OFFS,               0x12},  
   { 0X00, HWIO_UFS_MEM_UFS_PHY_TX_POST_EMP_LVL_S6_OFFS,               0x15}, 
   { 0X00, HWIO_UFS_MEM_UFS_PHY_TX_POST_EMP_LVL_S7_OFFS,               0x19}, 
   { 0x00, HWIO_UFS_MEM_UFS_PHY_SW_RESET_OFFS,                         0x00}, 
   { STOP_CONDITION, 0,0}};

static struct ufs_mphy_init_item ufs_bsp_mphy_eom_table[] = {
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_VTHRESH_CAL_CNTRL1_OFFS,            0x04},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_VTHRESH_CAL_MAN_VAL_RATE4_OFFS,     0x00},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX0_VTHRESH_CAL_MAN_VAL_RATE3_OFFS,     0x00},
   { STOP_CONDITION, 0,0}};

static struct ufs_mphy_init_item ufs_bsp_mphy_2_lane_eom_table[] = {
   { 0x00, HWIO_UFS_MEM_QSERDES_RX1_VTHRESH_CAL_CNTRL1_OFFS,            0x04},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX1_VTHRESH_CAL_MAN_VAL_RATE4_OFFS,     0x00},
   { 0x00, HWIO_UFS_MEM_QSERDES_RX1_VTHRESH_CAL_MAN_VAL_RATE3_OFFS,     0x00},
   { STOP_CONDITION, 0,0}};

static struct ufs_mphy_init_item ufs_bsp_mphy_init_table_rumi[] = {
     { 0x00, HWIO_UFS_PHY_PHY_START_OFFS,                     0x00}, 
     { 0x00, HWIO_UFS_PHY_POWER_DOWN_CONTROL_OFFS,            0x00}, 
     { 0x00, HWIO_UFS_PHY_RX_SYM_RESYNC_CTRL_OFFS,            0x03}, 
     { 0x00, HWIO_UFS_PHY_TIMER_20US_CORECLK_STEPS_MSB_OFFS,  0x0F}, 
     { 0x00, HWIO_UFS_PHY_TIMER_20US_CORECLK_STEPS_LSB_OFFS,  0x00}, 
     { 0x00, HWIO_QSERDES_COM_BIAS_EN_CLKBUFLR_EN_OFFS,       0x3F}, 
     { 0x00, HWIO_QSERDES_COM_SYSCLK_EN_SEL_OFFS,             0x03}, 
     { 0x00, HWIO_QSERDES_COM_SYS_CLK_CTRL_OFFS,              0x16}, 
     { 0x00, HWIO_QSERDES_COM_RES_CODE_TXBAND_OFFS,           0xC0}, 
     { 0x00, HWIO_QSERDES_COM_PLL_VCOTAIL_EN_OFFS,            0x03}, 
     { 0x00, HWIO_QSERDES_COM_PLL_CNTRL_OFFS,                 0x24}, 
     { 0x00, HWIO_QSERDES_COM_PLL_CLKEPDIV_OFFS,              0x03}, 
     { 0x00, HWIO_QSERDES_COM_RESETSM_CNTRL_OFFS,             0x10}, 
     { 0x00, HWIO_QSERDES_COM_PLL_RXTXEPCLK_EN_OFFS,          0x13}, 
     { 0x00, HWIO_QSERDES_COM_PLL_CRCTRL_OFFS,                0x43}, 
     { 0x00, HWIO_QSERDES_TX0_CLKBUF_ENABLE_OFFS,             0x29},
     { 0x00, HWIO_QSERDES_TX1_CLKBUF_ENABLE_OFFS,             0x29},
     { 0x00, HWIO_QSERDES_COM_DEC_START1_OFFS,                0x98}, 
     { 0x00, HWIO_QSERDES_COM_DEC_START2_OFFS,                0x03}, 
     { 0x00, HWIO_QSERDES_COM_DIV_FRAC_START1_OFFS,           0x80}, 
     { 0x00, HWIO_QSERDES_COM_DIV_FRAC_START2_OFFS,           0x80}, 
     { 0x00, HWIO_QSERDES_COM_DIV_FRAC_START3_OFFS,           0x10}, 
     { 0x00, HWIO_QSERDES_COM_PLLLOCK_CMP1_OFFS,              0x65}, 
     { 0x00, HWIO_QSERDES_COM_PLLLOCK_CMP2_OFFS,              0x1E}, 
     { 0x00, HWIO_QSERDES_COM_PLLLOCK_CMP3_OFFS,              0x00}, 
     { 0x00, HWIO_QSERDES_COM_PLLLOCK_CMP_EN_OFFS,            0x03}, 
     { 0x00, HWIO_QSERDES_COM_PLL_IP_SETI_OFFS,               0x07}, 
     { 0x00, HWIO_QSERDES_COM_PLL_CP_SETI_OFFS,               0x0F}, 
     { 0x00, HWIO_QSERDES_COM_PLL_IP_SETP_OFFS,               0x07}, 
     { 0x00, HWIO_QSERDES_COM_PLL_CP_SETP_OFFS,               0x01}, 
     { 0x00, HWIO_QSERDES_RX0_PWM_CNTRL1_OFFS,                0x08}, 
     { 0x00, HWIO_QSERDES_RX0_PWM_CNTRL2_OFFS,                0x40}, 
     { 0x00, HWIO_QSERDES_RX0_PWM_NDIV_OFFS,                  0x30}, 
     { 0x00, HWIO_QSERDES_RX0_CDR_CONTROL_OFFS,               0x40}, 
     { 0x00, HWIO_QSERDES_RX0_CDR_CONTROL_HALF_OFFS,          0x0C}, 
     { 0x00, HWIO_QSERDES_RX0_CDR_CONTROL_QUARTER_OFFS,       0x12}, 
     { 0x00, HWIO_QSERDES_RX0_SIGDET_CNTRL_OFFS,              0xC0}, 
     { 0x00, HWIO_QSERDES_RX0_SIGDET_CNTRL2_OFFS,             0x07}, 
     { 0x00, HWIO_QSERDES_RX0_RX_BAND_OFFS,                   0x06}, 
     { 0x00, HWIO_QSERDES_RX0_UFS_CNTRL_OFFS,                 0x00}, 
     { 0x00, HWIO_QSERDES_RX0_RX_IQ_RXDET_EN_OFFS,            0xF3},
     { 0x00, HWIO_UFS_PHY_POWER_DOWN_CONTROL_OFFS,            0x01}, 
     { STOP_CONDITION, 0,0}};

static struct ufs_mphy_init_item ufs_bsp_mphy_2_lane_init_table[] = {
     { 0x00, HWIO_UFS_MEM_QSERDES_TX1_LANE_MODE_1_OFFS,                   0x01}, 
     { 0x00, HWIO_UFS_MEM_QSERDES_TX1_RES_CODE_LANE_OFFSET_TX_OFFS,       0x07},
     { 0x00, HWIO_UFS_MEM_QSERDES_TX1_RES_CODE_LANE_OFFSET_RX_OFFS,       0x0E},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_UCDR_FO_GAIN_RATE2_OFFS,            0x0C},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_UCDR_FO_GAIN_RATE4_OFFS,            0x0C},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_UCDR_SO_GAIN_RATE4_OFFS,            0x04},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_EQ_OFFSET_ADAPTOR_CNTRL1_OFFS,   0x14},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_UCDR_PI_CONTROLS_OFFS,              0x07},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_OFFSET_ADAPTOR_CNTRL3_OFFS,      0x0E},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_UCDR_FASTLOCK_COUNT_HIGH_RATE4_OFFS,0x02},
	 { 0x00, HWIO_UFS_MEM_QSERDES_RX1_UCDR_FASTLOCK_FO_GAIN_RATE4_OFFS,   0x1C},
	 { 0x00, HWIO_UFS_MEM_QSERDES_RX1_UCDR_FASTLOCK_SO_GAIN_RATE4_OFFS,   0x06},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_VGA_CAL_MAN_VAL_OFFS,               0x3E},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_EQU_ADAPTOR_CNTRL4_OFFS,         0x0F},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE_0_1_B0_OFFS,           0xCE},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE_0_1_B1_OFFS,           0xCE},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE_0_1_B2_OFFS,           0x18},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE_0_1_B3_OFFS,           0x1A},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE_0_1_B4_OFFS,           0x0F},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE_0_1_B6_OFFS,           0x60},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE2_B3_OFFS,              0x9E},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE2_B6_OFFS,              0x60},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE3_B3_OFFS,              0x9E},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE3_B4_OFFS,              0x0E},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE3_B5_OFFS,              0x36},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE3_B8_OFFS,              0x02},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE4_B0_OFFS,              0x1B}, 
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE4_B1_OFFS,              0x1B}, 
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE4_B2_OFFS,              0x20},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE4_B3_OFFS,              0xB9},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_MODE_RATE4_B4_OFFS,              0x5D},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_UCDR_SO_SATURATION_OFFS,            0x1F},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_UCDR_PI_CTRL1_OFFS,                 0x94},
	 { 0x00, HWIO_UFS_MEM_QSERDES_RX1_RX_TERM_BW_CTRL0_OFFS,              0xFA},
     { 0x00, HWIO_UFS_MEM_QSERDES_RX1_DLL0_FTUNE_CTRL_OFFS,               0x30},
	 { 0x00, HWIO_UFS_MEM_UFS_PHY_MULTI_LANE_CTRL1_OFFS,                  0x02},
     { STOP_CONDITION, 0,0}};

static struct ufs_mphy_init_item ufs_bsp_mphy_2_lane_init_table_rumi[] = {
     { 0x00, HWIO_QSERDES_RX1_PWM_CNTRL1_OFFS,                        0x08},
     { 0x00, HWIO_QSERDES_RX1_PWM_CNTRL2_OFFS,                        0x40},
     { 0x00, HWIO_QSERDES_RX1_PWM_NDIV_OFFS,                          0x30},
     { 0x00, HWIO_QSERDES_RX1_CDR_CONTROL_OFFS,                       0x40},
     { 0x00, HWIO_QSERDES_RX1_CDR_CONTROL_HALF_OFFS,                  0x0C},
     { 0x00, HWIO_QSERDES_RX1_CDR_CONTROL_QUARTER_OFFS,               0x12},
     { 0x00, HWIO_QSERDES_RX1_SIGDET_CNTRL_OFFS,                      0xc0},
     { 0x00, HWIO_QSERDES_RX1_SIGDET_CNTRL2_OFFS,                     0x07},
     { 0x00, HWIO_QSERDES_RX1_RX_BAND_OFFS,                           0x06},
     { 0x00, HWIO_QSERDES_RX1_UFS_CNTRL_OFFS,                         0x00},
     { 0x00, HWIO_QSERDES_RX1_RX_IQ_RXDET_EN_OFFS,                    0xf3},
     { 0x00, HWIO_UFS_PHY_MULTI_LANE_CTRL1_OFFS,                      0x02},
     { STOP_CONDITION, 0,0}};

#endif /* #ifndef UFS_PHY_SEQ_H */

