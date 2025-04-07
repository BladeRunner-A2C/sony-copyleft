/*
 *  PCIe root port target config
 *
 *============================================================================
 *       Copyright (c) 2020 - 2023 QUALCOMM Technologies Incorporated
 *                        All Rights Reserved.
 *       Confidential and Proprietary - Qualcomm Technologies, Inc
 *============================================================================*/

#include "Library/pmapp_npa.h"
#include "HALhwio.h"
#include "pcie_hwio_4x2.h"
#include "pcie_cfg_types.h"
#include "pcie_hwio_base.h"

#define REG_OP_TYPE(x)        PCIE_REG_OP_SEQ, {.reg_op_seq = x}}
#define REG_WRITE_TYPE(x)     PCIE_REG_WRITE_SEQ, {.reg_write_val_seq = x}}

/* The macro ENABLE conflicts with the HWIO namespace */
#ifdef ENABLE
#undef ENABLE
#endif

/*******************************************************************************
 *
 *                           PORT 1 Phy GEN 4x2
 *
 *******************************************************************************/
STATIC CONST pcie_reg_write_val_t port_1_phy_init_seq[] =
{
   // Source: lanai_1.0_QMP PCIe 4.0 PHY HSR for n4_17.0

   /* Device Mode: 0x0: EP 0x4: RC */
   {HWIO_OFFS(PCIE_PARF_DEVICE_TYPE),                                           0x04},
   /* Remove PHY from powerdown mode and allow refclk drive */
   {HWIO_OFFS(PCIE4_PCS_COM_POWER_DOWN_CONTROL),                                0x03},
   /*
    * QSERDES_TX0_RES_CODE_LANE_OFFSET_TX
    * 0x18: value for Pinnacles;
    * 0x1D: value for others
    */
   {HWIO_OFFS(QSERDES_TX0_RES_CODE_LANE_OFFSET_TX),                             0x1D},
   /* Adjust rescode to RX */
   {HWIO_OFFS(QSERDES_TX0_RES_CODE_LANE_OFFSET_RX),                             0x03},
   /* Lane analog setting adjustment */
   {HWIO_OFFS(QSERDES_TX0_LANE_MODE_1),                                         0x01},
   /* Lane analog setting adjustment */
   {HWIO_OFFS(QSERDES_TX0_LANE_MODE_2),                                         0x00},
   /* Lane analog setting adjustment */
   {HWIO_OFFS(QSERDES_TX0_LANE_MODE_3),                                         0x51},
   /* Don't use txdata clk enable from PCS */
   {HWIO_OFFS(QSERDES_TX0_TRAN_DRVR_EMP_EN),                                    0x34},
   /* Adjust G3 CDR first order gain */
   {HWIO_OFFS(QSERDES_RX0_UCDR_FO_GAIN_RATE2),                                  0x0C},
   /* Adjust G4 CDR first order gain */
   {HWIO_OFFS(QSERDES_RX0_UCDR_FO_GAIN_RATE3),                                  0x0A},
   /* Adjust G3 CDR second order gain */
   {HWIO_OFFS(QSERDES_RX0_UCDR_SO_GAIN_RATE2),                                  0x04},
   /* Disable fastlock */
   {HWIO_OFFS(QSERDES_RX0_UCDR_PI_CONTROLS),                                    0x16},
   /* Adjust SO Acc init value for G4 */
   {HWIO_OFFS(QSERDES_RX0_UCDR_SO_ACC_DEFAULT_VAL_RATE3),                       0x00},
   /* Adjust summer cal ref source */
   {HWIO_OFFS(QSERDES_RX0_RX_IVCM_CAL_CTRL2),                                   0x80},
   /* Adjust IVCM postcal offset */
   {HWIO_OFFS(QSERDES_RX0_RX_IVCM_POSTCAL_OFFSET),                              0x7C},
   /* tap2 man mode; tap1 10nm mode with sign flip */
   {HWIO_OFFS(QSERDES_RX0_DFE_3),                                               0x05},
   /* Adjust starting value */
   {HWIO_OFFS(QSERDES_RX0_VGA_CAL_MAN_VAL),                                     0x0A},
   /*
    * QSERDES_RX0_GM_CAL
    * 0x11: value for Pinnacles;
    * 0x0D: value for others
    */
   {HWIO_OFFS(QSERDES_RX0_GM_CAL),                                              0x0D},
   /* Adjust starting value; use 0x0F for ultra-short channel (<5dB loss) */
   {HWIO_OFFS(QSERDES_RX0_RX_EQU_ADAPTOR_CNTRL4),                               0x0B},
   /* Force use of local bias; bypass pulse width filter */
   {HWIO_OFFS(QSERDES_RX0_SIGDET_ENABLES),                                      0x1C},
   /* Set pre txadapt mode to 0 */
   {HWIO_OFFS(QSERDES_RX0_PHPRE_CTRL),                                          0x20},
   /* Offset CTLE code by -2 */
   {HWIO_OFFS(QSERDES_RX0_DFE_CTLE_POST_CAL_OFFSET),                            0x30},
   /* Adjust q_pi offset for Gen3/Gen4 */
   {HWIO_OFFS(QSERDES_RX0_Q_PI_INTRINSIC_BIAS_RATE32),                          0x09},
   /*
    * QSERDES_RX0_RX_MODE_RATE2_B0
    * 0xD4: value for Pinnacles;
    * 0x14: value for others
    */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B0),                                    0x14},
   /*
    * QSERDES_RX0_RX_MODE_RATE2_B1
    * 0x73: value for Pinnacles;
    * 0xB3: value for others
    */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B1),                                    0xB3},
   /*
    * QSERDES_RX0_RX_MODE_RATE2_B2
    * 0x18: value for Pinnacles;
    * 0x58: value for others
    */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B2),                                    0x58},
   /* Rx setting adjustment for G3 */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B3),                                    0x9A},
   /*
    * QSERDES_RX0_RX_MODE_RATE2_B4
    * 0x36: value for Pinnacles;
    * 0x26: value for others
    */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B4),                                    0x26},
   /* Rx setting adjustment for G3 */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B5),                                    0xB6},
   /* Rx setting adjustment for G3 */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE2_B6),                                    0xEE},
   /*
    * QSERDES_RX0_RX_MODE_RATE3_B0
    * 0xCB: value for Pinnacles;
    * 0xDB: value for others
    */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B0),                                    0xDB},
   /*
    * QSERDES_RX0_RX_MODE_RATE3_B1
    * 0xCB: value for Pinnacles;
    * 0xDB: value for others
    */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B1),                                    0xDB},
   /*
    * QSERDES_RX0_RX_MODE_RATE3_B2
    * 0xE0: value for Pinnacles;
    * 0xA0: value for others
    */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B2),                                    0xA0},
   /* Rx setting adjustment for G4 */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B3),                                    0xDF},
   /* Rx setting adjustment for G4 */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B4),                                    0x78},
   /* Rx setting adjustment for G4 */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B5),                                    0x76},
   /* Rx setting adjustment for G4 */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_RATE3_B6),                                    0xFF},
   /*
    * QSERDES_TX1_RES_CODE_LANE_OFFSET_TX
    * 0x18: value for Pinnacles;
    * 0x1D: value for others
    */
   {HWIO_OFFS(QSERDES_TX1_RES_CODE_LANE_OFFSET_TX),                             0x1D},
   /* Adjust rescode to RX */
   {HWIO_OFFS(QSERDES_TX1_RES_CODE_LANE_OFFSET_RX),                             0x03},
   /* Lane analog setting adjustment */
   {HWIO_OFFS(QSERDES_TX1_LANE_MODE_1),                                         0x01},
   /* Lane analog setting adjustment */
   {HWIO_OFFS(QSERDES_TX1_LANE_MODE_2),                                         0x00},
   /* Lane analog setting adjustment */
   {HWIO_OFFS(QSERDES_TX1_LANE_MODE_3),                                         0x51},
   /* Don't use txdata clk enable from PCS */
   {HWIO_OFFS(QSERDES_TX1_TRAN_DRVR_EMP_EN),                                    0x34},
   /* Adjust G3 CDR first order gain */
   {HWIO_OFFS(QSERDES_RX1_UCDR_FO_GAIN_RATE2),                                  0x0C},
   /* Adjust G4 CDR first order gain */
   {HWIO_OFFS(QSERDES_RX1_UCDR_FO_GAIN_RATE3),                                  0x0A},
   /* Adjust G3 CDR second order gain */
   {HWIO_OFFS(QSERDES_RX1_UCDR_SO_GAIN_RATE2),                                  0x04},
   /* Disable fastlock */
   {HWIO_OFFS(QSERDES_RX1_UCDR_PI_CONTROLS),                                    0x16},
   /* Adjust SO Acc init value for G4 */
   {HWIO_OFFS(QSERDES_RX1_UCDR_SO_ACC_DEFAULT_VAL_RATE3),                       0x00},
   /* Adjust summer cal ref source */
   {HWIO_OFFS(QSERDES_RX1_RX_IVCM_CAL_CTRL2),                                   0x80},
   /* Adjust IVCM postcal offset */
   {HWIO_OFFS(QSERDES_RX1_RX_IVCM_POSTCAL_OFFSET),                              0x7C},
   /* tap2 man mode; tap1 10nm mode with sign flip */
   {HWIO_OFFS(QSERDES_RX1_DFE_3),                                               0x05},
   /* Adjust starting value */
   {HWIO_OFFS(QSERDES_RX1_VGA_CAL_MAN_VAL),                                     0x0A},
   /*
    * QSERDES_RX1_GM_CAL
    * 0x11: value for Pinnacles;
    * 0x0D: value for others
    */
   {HWIO_OFFS(QSERDES_RX1_GM_CAL),                                              0x0D},
   /* Adjust starting value; use 0x0F for ultra-short channel (<5dB loss) */
   {HWIO_OFFS(QSERDES_RX1_RX_EQU_ADAPTOR_CNTRL4),                               0x0B},
   /* Force use of local bias; bypass pulse width filter */
   {HWIO_OFFS(QSERDES_RX1_SIGDET_ENABLES),                                      0x1C},
   /* Set pre txadapt mode to 0 */
   {HWIO_OFFS(QSERDES_RX1_PHPRE_CTRL),                                          0x20},
   /* Offset CTLE code by -2 */
   {HWIO_OFFS(QSERDES_RX1_DFE_CTLE_POST_CAL_OFFSET),                            0x30},
   /* Adjust q_pi offset for Gen3/Gen4 */
   {HWIO_OFFS(QSERDES_RX1_Q_PI_INTRINSIC_BIAS_RATE32),                          0x09},
   /*
    * QSERDES_RX1_RX_MODE_RATE2_B0
    * 0xD4: value for Pinnacles;
    * 0x14: value for others
    */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B0),                                    0x14},
   /*
    * QSERDES_RX1_RX_MODE_RATE2_B1
    * 0x73: value for Pinnacles;
    * 0xB3: value for others
    */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B1),                                    0xB3},
   /*
    * QSERDES_RX1_RX_MODE_RATE2_B2
    * 0x18: value for Pinnacles;
    * 0x58: value for others
    */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B2),                                    0x58},
   /* Rx setting adjustment for G3 */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B3),                                    0x9A},
   /*
    * QSERDES_RX1_RX_MODE_RATE2_B4
    * 0x36: value for Pinnacles;
    * 0x26: value for others
    */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B4),                                    0x26},
   /* Rx setting adjustment for G3 */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B5),                                    0xB6},
   /* Rx setting adjustment for G3 */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE2_B6),                                    0xEE},
   /*
    * QSERDES_RX1_RX_MODE_RATE3_B0
    * 0xCB: value for Pinnacles;
    * 0xDB: value for others
    */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B0),                                    0xDB},
   /*
    * QSERDES_RX1_RX_MODE_RATE3_B1
    * 0xCB: value for Pinnacles;
    * 0xDB: value for others
    */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B1),                                    0xDB},
   /*
    * QSERDES_RX1_RX_MODE_RATE3_B2
    * 0xE0: value for Pinnacles;
    * 0xA0: value for others
    */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B2),                                    0xA0},
   /* Rx setting adjustment for G4 */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B3),                                    0xDF},
   /* Rx setting adjustment for G4 */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B4),                                    0x78},
   /* Rx setting adjustment for G4 */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B5),                                    0x76},
   /* Rx setting adjustment for G4 */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_RATE3_B6),                                    0xFF},
   /* Gen1 clock management */
   {HWIO_OFFS(QSERDES_LN_SHRD_RXCLK_DIV2_CTRL),                                 0x01},
   /* Disable DFE tap1 DAC in all speeds */
   {HWIO_OFFS(QSERDES_LN_SHRD_DFE_DAC_ENABLE1),                                 0x00},
   /* Adjust txadpt post low threshold */
   {HWIO_OFFS(QSERDES_LN_SHRD_TX_ADAPT_POST_THRESH1),                           0x00},
   /* Adjust txadpt post high threshold */
   {HWIO_OFFS(QSERDES_LN_SHRD_TX_ADAPT_POST_THRESH2),                           0x1F},
   /*
    * QSERDES_LN_SHRD_RX_MODE_RATE_0_1_B0
    * 0xD4: value for Pinnacles;
    * 0x12: value for others
    */
   {HWIO_OFFS(QSERDES_LN_SHRD_RX_MODE_RATE_0_1_B0),                             0x12},
   /* Rx setting adjustment for G1/G2 */
   {HWIO_OFFS(QSERDES_LN_SHRD_RX_MODE_RATE_0_1_B1),                             0x12},
   /* Rx setting adjustment for G1/G2 */
   {HWIO_OFFS(QSERDES_LN_SHRD_RX_MODE_RATE_0_1_B2),                             0xDB},
   /* Rx setting adjustment for G1/G2 */
   {HWIO_OFFS(QSERDES_LN_SHRD_RX_MODE_RATE_0_1_B3),                             0x9A},
   /*
    * QSERDES_LN_SHRD_RX_MODE_RATE_0_1_B4
    * 0x35: value for Pinnacles;
    * 0x38: value for others
    */
   {HWIO_OFFS(QSERDES_LN_SHRD_RX_MODE_RATE_0_1_B4),                             0x38},
   /* Rx setting adjustment for G1/G2 */
   {HWIO_OFFS(QSERDES_LN_SHRD_RX_MODE_RATE_0_1_B5),                             0xB6},
   /* Rx setting adjustment for G1/G2 */
   {HWIO_OFFS(QSERDES_LN_SHRD_RX_MODE_RATE_0_1_B6),                             0x64},
   /* Max out value to prevent adjustment */
   {HWIO_OFFS(QSERDES_LN_SHRD_RX_MARG_COARSE_THRESH1_RATE210),                  0x1F},
   /* Max out value to prevent adjustment */
   {HWIO_OFFS(QSERDES_LN_SHRD_RX_MARG_COARSE_THRESH1_RATE3),                    0x1F},
   /* Max out value to prevent adjustment */
   {HWIO_OFFS(QSERDES_LN_SHRD_RX_MARG_COARSE_THRESH2_RATE210),                  0x1F},
   /* Max out value to prevent adjustment */
   {HWIO_OFFS(QSERDES_LN_SHRD_RX_MARG_COARSE_THRESH2_RATE3),                    0x1F},
   /* Max out value to prevent adjustment */
   {HWIO_OFFS(QSERDES_LN_SHRD_RX_MARG_COARSE_THRESH3_RATE210),                  0x1F},
   /* Max out value to prevent adjustment */
   {HWIO_OFFS(QSERDES_LN_SHRD_RX_MARG_COARSE_THRESH3_RATE3),                    0x1F},
   /* Max out value to prevent adjustment */
   {HWIO_OFFS(QSERDES_LN_SHRD_RX_MARG_COARSE_THRESH4_RATE3),                    0x1F},
   /* Max out value to prevent adjustment */
   {HWIO_OFFS(QSERDES_LN_SHRD_RX_MARG_COARSE_THRESH5_RATE3),                    0x1F},
   /* Max out value to prevent adjustment */
   {HWIO_OFFS(QSERDES_LN_SHRD_RX_MARG_COARSE_THRESH6_RATE3),                    0x1F},
   /* Adjust Gen4 summer speed */
   {HWIO_OFFS(QSERDES_LN_SHRD_RX_SUMMER_CAL_SPD_MODE),                          0x5B},
   /*
    * QSERDES_PLL_SSC_STEP_SIZE1_MODE1
    * 0x97: 19.2Mhz refclk value: set SSC step size for Gen3/4 (4500ppm);
    * 0x26: 38.4Mhz refclk value: set SSC step size for Gen3/4 (4500ppm)
    */
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE1_MODE1),                                0x26},
   /*
    * QSERDES_PLL_SSC_STEP_SIZE2_MODE1
    * 0x0C: 19.2Mhz refclk value;
    * 0x03: 38.4Mhz refclk value
    */
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE2_MODE1),                                0x03},
   /* Gen3/4 PLL charge pump adjustment */
   {HWIO_OFFS(QSERDES_PLL_CP_CTRL_MODE1),                                       0x06},
   /* Gen3/4 PLL RC loop filter adjustment */
   {HWIO_OFFS(QSERDES_PLL_PLL_RCTRL_MODE1),                                     0x16},
   /* Gen3/4 PLL 2nd cap loop filter adjustment */
   {HWIO_OFFS(QSERDES_PLL_PLL_CCTRL_MODE1),                                     0x36},
   /* Set gen3/4 coreclk divider */
   {HWIO_OFFS(QSERDES_PLL_CORECLK_DIV_MODE1),                                   0x04},
   /*
    * QSERDES_PLL_LOCK_CMP1_MODE1
    * 0x14: 19.2Mhz refclk value: Gen3/4 PLL lock compare value;
    * 0x0A: 38.4Mhz refclk value: Gen3/4 PLL lock compare value
    */
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP1_MODE1),                                     0x0A},
   /*
    * QSERDES_PLL_LOCK_CMP2_MODE1
    * 0x34: 19.2Mhz refclk value;
    * 0x1A: 38.4Mhz refclk value
    */
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP2_MODE1),                                     0x1A},
   /*
    * QSERDES_PLL_DEC_START_MODE1
    * 0xD0: 19.2Mhz refclk value: Gen3/4 PLL decimal divider value;
    * 0x68: 38.4Mhz refclk value: Gen3/4 PLL decimal divider value
    */
   {HWIO_OFFS(QSERDES_PLL_DEC_START_MODE1),                                     0x68},
   /*
    * QSERDES_PLL_DIV_FRAC_START1_MODE1
    * 0x55: 19.2Mhz refclk value: Gen3/4 PLL fractional divider value;
    * 0xAB: 38.4Mhz refclk value: Gen3/4 PLL fractional divider value
    */
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START1_MODE1),                               0xAB},
   /*
    * QSERDES_PLL_DIV_FRAC_START2_MODE1
    * 0x55: 19.2Mhz refclk value;
    * 0xAA: 38.4Mhz refclk value
    */
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START2_MODE1),                               0xAA},
   /*
    * QSERDES_PLL_DIV_FRAC_START3_MODE1
    * 0x05: 19.2Mhz refclk value;
    * 0x02: 38.4Mhz refclk value
    */
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START3_MODE1),                               0x02},
   /* Set HSCLK divider for gen1/2 and gen3/4 */
   {HWIO_OFFS(QSERDES_PLL_HSCLK_SEL_1),                                         0x12},
   /*
    * QSERDES_PLL_SSC_STEP_SIZE1_MODE0
    * 0xDE: 19.2Mhz refclk value: set SSC step size for Gen1/2 (4500ppm);
    * 0xF8: 38.4Mhz refclk value: set SSC step size for Gen1/2 (4500ppm)
    */
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE1_MODE0),                                0xF8},
   /*
    * QSERDES_PLL_SSC_STEP_SIZE2_MODE0
    * 0x07: 19.2Mhz refclk value;
    * 0x01: 38.4Mhz refclk value
    */
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE2_MODE0),                                0x01},
   /* Gen1/2 PLL charge pump adjustment */
   {HWIO_OFFS(QSERDES_PLL_CP_CTRL_MODE0),                                       0x06},
   /* Gen1/2 PLL RC loop filter adjustment */
   {HWIO_OFFS(QSERDES_PLL_PLL_RCTRL_MODE0),                                     0x16},
   /* Gen1/2 PLL 2nd cap loop filter adjustment */
   {HWIO_OFFS(QSERDES_PLL_PLL_CCTRL_MODE0),                                     0x36},
   /* Set gen1/2 coreclk divider */
   {HWIO_OFFS(QSERDES_PLL_CORECLK_DIV_MODE0),                                   0x0A},
   /*
    * QSERDES_PLL_LOCK_CMP1_MODE0
    * 0x0A: 19.2Mhz refclk value: Gen1/2 PLL lock compare value;
    * 0x04: 38.4Mhz refclk value: Gen1/2 PLL lock compare value
    */
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP1_MODE0),                                     0x04},
   /*
    * QSERDES_PLL_LOCK_CMP2_MODE0
    * 0x1A: 19.2Mhz refclk value;
    * 0x0D: 38.4Mhz refclk value
    */
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP2_MODE0),                                     0x0D},
   /*
    * QSERDES_PLL_DEC_START_MODE0
    * 0x82: 19.2Mhz refclk value: Gen1/2 PLL decimal divider value;
    * 0x41: 38.4Mhz refclk value: Gen1/2 PLL decimal divider value
    */
   {HWIO_OFFS(QSERDES_PLL_DEC_START_MODE0),                                     0x41},
   /*
    * QSERDES_PLL_DIV_FRAC_START1_MODE0
    * 0x55: 19.2Mhz refclk value: Gen1/2 PLL fractional divider value;
    * 0xAB: 38.4Mhz refclk value: Gen1/2 PLL fractional divider value
    */
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START1_MODE0),                               0xAB},
   /*
    * QSERDES_PLL_DIV_FRAC_START2_MODE0
    * 0x55: 19.2Mhz refclk value;
    * 0xAA: 38.4Mhz refclk value
    */
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START2_MODE0),                               0xAA},
   /*
    * QSERDES_PLL_DIV_FRAC_START3_MODE0
    * 0x03: 19.2Mhz refclk value;
    * 0x01: 38.4Mhz refclk value
    */
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START3_MODE0),                               0x01},
   /*  */
   {HWIO_OFFS(QSERDES_PLL_HSCLK_HS_SWITCH_SEL_1),                               0x00},
   /*
    * QSERDES_PLL_BG_TIMER
    * 0x0E: 19.2Mhz refclk value;
    * 0x0A: 38.4Mhz refclk value
    */
   {HWIO_OFFS(QSERDES_PLL_BG_TIMER),                                            0x0A},
   /*
    * QSERDES_PLL_SSC_EN_CENTER
    * 0x00: Downspread SSC disabled (default, so no write needed);
    * 0x01: Downspread SSC enabled
    */
   {HWIO_OFFS(QSERDES_PLL_SSC_EN_CENTER),                                       0x01},
   /*
    * QSERDES_PLL_SSC_PER1
    * 0x31: 19.2Mhz refclk value: set SSC frequency to 31.5KHz;
    * 0x62: 38.4Mhz refclk value: set SSC frequency to 31.5KHz
    */
   {HWIO_OFFS(QSERDES_PLL_SSC_PER1),                                            0x62},
   /*
    * QSERDES_PLL_SSC_PER2
    * 0x01: 19.2Mhz refclk value;
    * 0x02: 38.4Mhz refclk value
    */
   {HWIO_OFFS(QSERDES_PLL_SSC_PER2),                                            0x02},
   /* Set HSCLK divider for gen1/2 and gen3/4 */
   {HWIO_OFFS(QSERDES_PLL_POST_DIV_MUX),                                        0x40},
   /* Enable right side clock buffers */
   {HWIO_OFFS(QSERDES_PLL_BIAS_EN_CLKBUFLR_EN),                                 0x14},
   /* Enable endpoint clock drive with pulldown when off */
   {HWIO_OFFS(QSERDES_PLL_CLK_ENABLE1),                                         0x90},
   /* Select SW endpoint enable */
   {HWIO_OFFS(QSERDES_PLL_SYS_CLK_CTRL),                                        0x82},
   /* Adjust VCO current */
   {HWIO_OFFS(QSERDES_PLL_PLL_IVCO),                                            0x0f},
   /*
    * QSERDES_PLL_SYSCLK_EN_SEL
    * 0x04: select internal diff cml clock inputs;
    * 0x08: select SE cmos clock input
    */
   {HWIO_OFFS(QSERDES_PLL_SYSCLK_EN_SEL),                                       0x08},
   /* Lock count = 512, lock range = +/-64 */
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP_EN),                                         0x46},
   /* Use same range values for all lock iterations */
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP_CFG),                                        0x04},
   /* Set mode0 as gen1/2 and mode1 as gen3/4 */
   {HWIO_OFFS(QSERDES_PLL_VCO_TUNE_MAP),                                        0x14},
   /* Set rchng clock as endpoint refclk source during relock; set endpoint refclk swing */
   {HWIO_OFFS(QSERDES_PLL_CLK_SELECT),                                          0x34},
   /* Set PLL lock clock divider */
   {HWIO_OFFS(QSERDES_PLL_CORE_CLK_EN),                                         0xA0},
   /* Set gen1/2 PLL feedback divide to 6 */
   {HWIO_OFFS(QSERDES_PLL_CMN_CONFIG_1),                                        0x06},
   /* Set hs_switch as part of rate change */
   {HWIO_OFFS(QSERDES_PLL_CMN_MISC1),                                           0x88},
   /* VCCA selected as input to Vreg */
   {HWIO_OFFS(QSERDES_PLL_CMN_MODE),                                            0x14},
   /* Increase Vreg */
   {HWIO_OFFS(QSERDES_PLL_VCO_DC_LEVEL_CTRL),                                   0x0F},
   /* Adjust G3 pre gain for P7 compliance */
   {HWIO_OFFS(PCIE4_PCS_COM_G3S2_PRE_GAIN),                                     0x2E},
   /* Adjust sigdet level */
   {HWIO_OFFS(PCIE4_PCS_COM_RX_SIGDET_LVL),                                     0xCC},
   /* Disable G3 Tap345 adaption */
   {HWIO_OFFS(PCIE4_PCS_COM_EQ_CONFIG4),                                        0x00},
   /* Disable G3 Tap2 adaption; dfe freeze release w/o align */
   {HWIO_OFFS(PCIE4_PCS_COM_EQ_CONFIG5),                                        0x22},
   /* Enable endpoint refclk drive */
   {HWIO_OFFS(PCIE4_PCS_PCIE_ENDPOINT_REFCLK_DRIVE),                            0xc1},
   /*
    * PCIE4_PCS_COM_FLL_CNTRL2
    * 0x83: default setting (write not needed);
    * 0x87: value for half frequency (required when more than 4 pipeline stages used at SOC)
    */
   {HWIO_OFFS(PCIE4_PCS_COM_FLL_CNTRL2),                                        0x87},
   /*
    * PCIE4_PCS_COM_FLL_CNT_VAL_L
    * 0x09: default setting (write not needed);
    * 0x05: value for half frequency (required when more than 4 pipeline stages used at SOC)
    */
   {HWIO_OFFS(PCIE4_PCS_COM_FLL_CNT_VAL_L),                                     0x05},
   /*
    * PCIE4_PCS_COM_FLL_CNT_VAL_H_TOL
    * 0xA2: default setting (write not needed);
    * 0xA1: value for half frequency (required when more than 4 pipeline stages used at SOC)
    */
   {HWIO_OFFS(PCIE4_PCS_COM_FLL_CNT_VAL_H_TOL),                                 0xA1},
   /*
    * PCIE4_PCS_PCIE_INT_AUX_CLK_CONFIG1
    * 0x02: FLL off - PHY aux_clk not generated (default value - write not needed);
    * 0x03: FLL on - PHY aux_clk generated (and used internally in L1ss mode);
    * 0x0F: FLL on - PHY aux_clk generated (and used internally in all modes - for Lanai)
    */
   {HWIO_OFFS(PCIE4_PCS_PCIE_INT_AUX_CLK_CONFIG1),                              0x0F},
   /* Disable osc detect */
   {HWIO_OFFS(PCIE4_PCS_PCIE_OSC_DTCT_ACTIONS),                                 0x00},
   /* Flip post inc/dec mappings */
   {HWIO_OFFS(PCIE4_PCS_PCIE_EQ_CONFIG1),                                       0x16},
   /* Increase G3 adaption eval time to 40us */
   {HWIO_OFFS(PCIE4_PCS_PCIE_G3_RXEQEVAL_TIME),                                 0x27},
   /* Increase G4 adaption eval time to 40us */
   {HWIO_OFFS(PCIE4_PCS_PCIE_G4_RXEQEVAL_TIME),                                 0x27},
   /* Disable G4 Tap2345 adaption */
   {HWIO_OFFS(PCIE4_PCS_PCIE_G4_EQ_CONFIG5),                                    0x02},
   /* Adjust G4 pre gain for P7 compliance */
   {HWIO_OFFS(PCIE4_PCS_PCIE_G4_PRE_GAIN),                                      0x2E},
   /* Enable rx margining in Gen3 and Gen4 (Gen3 needed for FOM) */
   {HWIO_OFFS(PCIE4_PCS_PCIE_RX_MARGINING_CONFIG1),                             0x03},
   /* Enable horizontal and vertical margining */
   {HWIO_OFFS(PCIE4_PCS_PCIE_RX_MARGINING_CONFIG3),                             0x28},
   /*
    * PCIE4_PCS_COM_PCS_TX_RX_CONFIG1
    * 0x04: Si - set Pinf RTB depth to 5 for gen1/2 (evaluate per SOC)
    * 0x08: DV - set Pinf RTB depth to 7 for gen1/2 (for 5 deep wc delay)
    */
   {HWIO_OFFS(PCIE4_PCS_COM_PCS_TX_RX_CONFIG1),                                 0x04},
   /* Set Pinf RTB depth to 7 for gen3 (evaluate per SOC) */
   {HWIO_OFFS(PCIE4_PCS_COM_PCS_TX_RX_CONFIG2),                                 0x02},
   /* Set Pinf RTB depth to 7 for gen4 (evaluate per SOC) */
   {HWIO_OFFS(PCIE4_PCS_PCIE_PCS_TX_RX_CONFIG),                                 0xC0},
   /* Keep PLL/EP clock on in P2 until CLKREQ# goes high; allow CLKREQ# to go high in P2. */
   {HWIO_OFFS(PCIE4_PCS_PCIE_POWER_STATE_CONFIG2),                              0x1D},
   /* Adjust aux offset to center eye */
   {HWIO_OFFS(PCIE4_PCS_PCIE_RX_MARGINING_CONFIG5),                             0x0F},
   /* Adjust aux offset to center eye */
   {HWIO_OFFS(PCIE4_PCS_PCIE_G3_FOM_EQ_CONFIG5),                                0xF2},
   /* Adjust aux offset to center eye */
   {HWIO_OFFS(PCIE4_PCS_PCIE_G4_FOM_EQ_CONFIG5),                                0xF2},
   /* Gen1/2 -6dB txdeemph coefficient mapping; set to 0x0F to force -3.5dB (for ultra short channel (<5dB loss)) */
   {HWIO_OFFS(PCIE4_PCS_COM_G12S1_TXDEEMPH_M6DB),                               0x17},
   /*
    * PCIE4_PCS_LANE0_OUTSIG_MX_CTRL2
    * 0x00: Link partner Tx Preset adjusted during RxEq training (default value - write not needed);
    * 0x55: Link partner Tx Preset fixed (not adjusted during RxEq training)
    */
   {HWIO_OFFS(PCIE4_PCS_LANE0_OUTSIG_MX_CTRL2),                                 0x00},
   /*
    * PCIE4_PCS_LANE1_OUTSIG_MX_CTRL2
    * 0x00: Link partner Tx Preset adjusted during RxEq training (default value - write not needed);
    * 0x55: Link partner Tx Preset fixed (not adjusted during RxEq training)
    */
   {HWIO_OFFS(PCIE4_PCS_LANE1_OUTSIG_MX_CTRL2),                                 0x00},
   /*
    * PCIE4_PCS_LANE1_INSIG_SW_CTRL2
    * 0x00: 2-lane mode (default value - write not needed);
    * 0x01: 1-lane mode - lane1 disabled
    */
   {HWIO_OFFS(PCIE4_PCS_LANE1_INSIG_SW_CTRL2),                                  0x00},
   /*
    * PCIE4_PCS_LANE1_INSIG_MX_CTRL2
    * 0x00: 2-lane mode (default value - write not needed);
    * 0x01: 1-lane mode - lane1 disabled
    */
   {HWIO_OFFS(PCIE4_PCS_LANE1_INSIG_MX_CTRL2),                                  0x00},

   /*   END   */
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_1_phy_start_seq[] =
{
   {HWIO_OFFS(PCIE4_PCS_COM_SW_RESET),         0x00},  //    Release SW_RESET
   {HWIO_OFFS(PCIE4_PCS_COM_START_CONTROL),    0x03},  //    Start PCS and Serdes power SMs
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t port_1_phy_poll_seq[] =
{
   {PCIE_REG_OP_POLL, HWIO_OFFS(PCIE4_PCS_COM_PCS_STATUS1), HWIO_PCIE4_PCS_COM_PCS_STATUS1_PHYSTATUS_BMSK, FALSE},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_1_phy_de_init_seq[] =
{
   {HWIO_OFFS(PCIE4_PCS_COM_POWER_DOWN_CONTROL),    0x00},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t phy_delay_seq[] =
{
   {PCIE_REG_OP_DELAY, 0, 0, 2000},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t port_1_phy_de_init_cfg[] =
{
   {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(port_1_phy_de_init_seq),
   {PcieSeq_Stop},
};

/*******************************************************************************
 *                       Loopback
 ******************************************************************************/

STATIC CONST pcie_reg_write_val_t port_1_phy_lpb_en_seq[] =
{
   {HWIO_OFFS(QSERDES_TX0_LPB_EN),                      0x0C},
   {HWIO_OFFS(QSERDES_TX1_LPB_EN),                      0x0C},
   {HWIO_OFFS(PCIE4_PCS_LANE0_PCS_LANE_TEST_CONTROL1),  0x03},
   {HWIO_OFFS(PCIE4_PCS_LANE1_PCS_LANE_TEST_CONTROL1),  0x03},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_1_phy_lpb_dis_seq[] =
{
   {HWIO_OFFS(QSERDES_TX0_LPB_EN),                      0x00},
   {HWIO_OFFS(QSERDES_TX1_LPB_EN),                      0x00},
   {HWIO_OFFS(PCIE4_PCS_LANE0_PCS_LANE_TEST_CONTROL1),  0x00},
   {HWIO_OFFS(PCIE4_PCS_LANE1_PCS_LANE_TEST_CONTROL1),  0x00},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t port_1_phy_lpb_en_cfg[] =
{
   {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(port_1_phy_lpb_en_seq),
   {PcieSeq_Stop},
};

STATIC CONST pcie_reg_init_cfg_t port_1_phy_lpb_dis_cfg[] =
{
   {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(port_1_phy_lpb_dis_seq),
   {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(port_1_phy_de_init_seq),
   {PcieSeq_Stop},
};

STATIC CONST pcie_loopback_cfg_t port_1_loopback_seq =
{
   port_1_phy_lpb_en_cfg,
   port_1_phy_lpb_dis_cfg,
};

/*******************************************************************************
 *
 *                       Controller DBI settings
 *
 *******************************************************************************/
/* Set the max capable lane width */
/* 1 for 1 lane
 * 3 for 2 lane
 * 7 for 4 lane */
#define PORT_2_LANE     2
#define PORT_1_LANE     1

#define PORT_LINK_2_LANE_CAPABLE_VAL ((PORT_2_LANE << 1) - 1)
#define PORT_LINK_1_LANE_CAPABLE_VAL (1)

/*******************************************************************************
 *       Post PHY power ON sequence
 ******************************************************************************/
STATIC CONST pcie_reg_op_t post_phy_pwr_up_init_seq[] =
{
   // WARNING..!!: Only AHB registers in this set
   REG_RMW_FVALV(PCIE_PARF_DEVICE_TYPE, DEVICE_TYPE, RC),
   REG_RMW(PCIE_PARF_PM_CTRL, REQ_NOT_ENTR_L1, 0x0),
   REG_RMW(PCIE_PARF_SYS_CTRL, AUX_PWR_DET, 0x1),
   REG_WRITE(PCIE_PARF_AXI_MSTR_WR_ADDR_HALT, 0x0),
   REG_WRITE(PCIE_PARF_SLV_ADDR_SPACE_SIZE, 0x01000000),
   REG_WRITE(PCIE_SRIS_MODE, 0x0),
   {PCIE_REG_OP_STOP},
};

#define PORT_LINK_SPEED_GEN_1     1
#define PORT_LINK_SPEED_GEN_2     2
#define PORT_LINK_SPEED_GEN_3     3
#define PORT_LINK_SPEED_GEN_4     4

STATIC CONST pcie_reg_op_t post_phy_pwr_up_dbi_init_seq[] =
{
   // WARNING..!!: Only AXI registers in this set
   REG_RMW(PCIE_PORT_LINK_CTRL_OFF, LINK_CAPABLE, PORT_LINK_2_LANE_CAPABLE_VAL),
   REG_RMW(PCIE_LINK_CONTROL2_LINK_STATUS2_REG, PCIE_CAP_TARGET_LINK_SPEED, PORT_LINK_SPEED_GEN_4),
   {
      PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_ACK_F_ASPM_CTRL_OFF),
      HWIO_FMSK(PCIE_ACK_F_ASPM_CTRL_OFF, COMMON_CLK_N_FTS) |
         HWIO_FMSK(PCIE_ACK_F_ASPM_CTRL_OFF, ACK_N_FTS),
      HWIO_FVAL(PCIE_ACK_F_ASPM_CTRL_OFF, COMMON_CLK_N_FTS, 0x80) |
         HWIO_FVAL(PCIE_ACK_F_ASPM_CTRL_OFF, ACK_N_FTS, 0x80)
   },
   /* Treats out-of-bar TLPs as supported request - MUST for RC mode. Data book: Table I-2 */
   REG_RMW(PCIE_SYMBOL_TIMER_FILTER_1_OFF, MASK_RADM_1, 0x4),
   REG_WRITE(PCIE_AUX_CLK_FREQ_OFF, 19),
   /* Allow establishing connection on one line even if there is a termination on the second line. Othewise the link will go to compliance */
   REG_RMW(PCIE_GEN2_CTRL_OFF, NUM_OF_LANES, 0x1),
   REG_RMW(PCIE_MISC_CONTROL_1_OFF, DBI_RO_WR_EN, 0x1),
   {PCIE_REG_OP_DSB},
   {
      PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_TYPE1_CLASS_CODE_REV_ID_REG),
      HWIO_FMSK(PCIE_TYPE1_CLASS_CODE_REV_ID_REG, BASE_CLASS_CODE) |
         HWIO_FMSK(PCIE_TYPE1_CLASS_CODE_REV_ID_REG, SUBCLASS_CODE),
      /* These are not defined in HWIO, the values are already shifted properly */
      PCIE_CLASS_CODE_BRIDGE_DEVICE | PCIE_SUBCLASS_CODE_PCI_2_PCI_BRIDGE
   },
   REG_RMW(PCIE_SLOT_CAPABILITIES_REG, PCIE_CAP_HOT_PLUG_CAPABLE, 0x0),
   /* - Set the Downstream Port 8.0 GT/s Transmitter Preset and Upstream Port 8.0 GT/s Transmitter Preset bits in the RC's Lane Equalization Control Register
         to appropriate values for the channel (recommend 5 for short channel and 7 for long channel). */
   REG_WRITE(PCIE_SPCIE_CAP_OFF_0CH_REG, 0x55555555),
   /* - Set the Downstream Port 16.0 GT/s Transmitter Preset and Upstream Port 16.0 GT/s Transmitter Preset bits in the RC's 16.0 GT/s Lane Equalization Control Register
         to appropriate values for the channel (recommend 5 for short channel and 7 for long channel). */
   REG_WRITE(PCIE_PL16G_CAP_OFF_20H_REG, 0x5555),
   {PCIE_REG_OP_DSB},
   REG_RMW(PCIE_MISC_CONTROL_1_OFF, DBI_RO_WR_EN, 0x0),

   /* GEN3 */
   REG_RMW(PCIE_GEN3_RELATED_OFF, RATE_SHADOW_SEL, 0x0),
   {PCIE_REG_OP_DSB},
   {
      PCIE_REG_OP_RMW,
      HWIO_OFFS(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF),
      HWIO_FMSK(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_N_EVALS) |
         HWIO_FMSK(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_MAX_PRE_CUSROR_DELTA) |
         HWIO_FMSK(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_MAX_POST_CUSROR_DELTA) |
         HWIO_FMSK(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_T_MIN_PHASE23),
      HWIO_FVAL(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_N_EVALS, 0xD) |
         HWIO_FVAL(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_MAX_PRE_CUSROR_DELTA, 0x5) |
         HWIO_FVAL(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_MAX_POST_CUSROR_DELTA, 0x5) |
         HWIO_FVAL(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_T_MIN_PHASE23, 0x1)
   },
   {
      PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_GEN3_EQ_CONTROL_OFF),
      HWIO_FMSK(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_PHASE23_EXIT_MODE) |
         HWIO_FMSK(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_PSET_REQ_VEC) |
         HWIO_FMSK(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_FB_MODE),
      HWIO_FVAL(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_PHASE23_EXIT_MODE, 0x0) |
         HWIO_FVAL(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_PSET_REQ_VEC, 0x0) |
         HWIO_FVAL(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_FB_MODE, 0x0)
   },
   {PCIE_REG_OP_DSB},
   /* GEN4 */
   REG_RMW(PCIE_GEN3_RELATED_OFF, RATE_SHADOW_SEL, 0x1),
   {PCIE_REG_OP_DSB},
   {
      PCIE_REG_OP_RMW,
      HWIO_OFFS(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF),
      HWIO_FMSK(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_N_EVALS) |
         HWIO_FMSK(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_MAX_PRE_CUSROR_DELTA) |
         HWIO_FMSK(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_MAX_POST_CUSROR_DELTA) |
         HWIO_FMSK(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_T_MIN_PHASE23),
      HWIO_FVAL(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_N_EVALS, 0xD) |
         HWIO_FVAL(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_MAX_PRE_CUSROR_DELTA, 0x5) |
         HWIO_FVAL(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_MAX_POST_CUSROR_DELTA, 0x5) |
         HWIO_FVAL(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_T_MIN_PHASE23, 0x1)
   },
   {
      PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_GEN3_EQ_CONTROL_OFF),
      HWIO_FMSK(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_PHASE23_EXIT_MODE) |
         HWIO_FMSK(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_PSET_REQ_VEC) |
         HWIO_FMSK(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_FB_MODE),
      HWIO_FVAL(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_PHASE23_EXIT_MODE, 0x0) |
         HWIO_FVAL(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_PSET_REQ_VEC, 0x0) |
         HWIO_FVAL(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_FB_MODE, 0x0)
   },
   {PCIE_REG_OP_DSB},
   REG_RMW(PCIE_GEN3_RELATED_OFF, RATE_SHADOW_SEL, 0x0),
   {
      PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_GEN4_LANE_MARGINING_1_OFF),
      HWIO_FMSK(PCIE_GEN4_LANE_MARGINING_1_OFF, MARGINING_MAX_VOLTAGE_OFFSET) |
         HWIO_FMSK(PCIE_GEN4_LANE_MARGINING_1_OFF, MARGINING_NUM_VOLTAGE_STEPS) |
         HWIO_FMSK(PCIE_GEN4_LANE_MARGINING_1_OFF, MARGINING_MAX_TIMING_OFFSET) |
         HWIO_FMSK(PCIE_GEN4_LANE_MARGINING_1_OFF, MARGINING_NUM_TIMING_STEPS),
      HWIO_FVAL(PCIE_GEN4_LANE_MARGINING_1_OFF, MARGINING_MAX_VOLTAGE_OFFSET, 0x24) |
         HWIO_FVAL(PCIE_GEN4_LANE_MARGINING_1_OFF, MARGINING_NUM_VOLTAGE_STEPS, 0x78) |
         HWIO_FVAL(PCIE_GEN4_LANE_MARGINING_1_OFF, MARGINING_MAX_TIMING_OFFSET, 0x32) |
         HWIO_FVAL(PCIE_GEN4_LANE_MARGINING_1_OFF, MARGINING_NUM_TIMING_STEPS, 0x10)
   },
   {
      PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_GEN4_LANE_MARGINING_2_OFF),
      HWIO_FMSK(PCIE_GEN4_LANE_MARGINING_2_OFF, MARGINING_IND_ERROR_SAMPLER) |
         HWIO_FMSK(PCIE_GEN4_LANE_MARGINING_2_OFF, MARGINING_SAMPLE_REPORTING_METHOD) |
         HWIO_FMSK(PCIE_GEN4_LANE_MARGINING_2_OFF, MARGINING_IND_LEFT_RIGHT_TIMING) |
         HWIO_FMSK(PCIE_GEN4_LANE_MARGINING_2_OFF, MARGINING_IND_UP_DOWN_VOLTAGE) |
         HWIO_FMSK(PCIE_GEN4_LANE_MARGINING_2_OFF, MARGINING_VOLTAGE_SUPPORTED) |
         HWIO_FMSK(PCIE_GEN4_LANE_MARGINING_2_OFF, MARGINING_MAXLANES) |
         HWIO_FMSK(PCIE_GEN4_LANE_MARGINING_2_OFF, MARGINING_SAMPLE_RATE_TIMING) |
         HWIO_FMSK(PCIE_GEN4_LANE_MARGINING_2_OFF, MARGINING_SAMPLE_RATE_VOLTAGE),
      HWIO_FVAL(PCIE_GEN4_LANE_MARGINING_2_OFF, MARGINING_IND_ERROR_SAMPLER, 0x1) |
         HWIO_FVAL(PCIE_GEN4_LANE_MARGINING_2_OFF, MARGINING_SAMPLE_REPORTING_METHOD, 0x1) |
         HWIO_FVAL(PCIE_GEN4_LANE_MARGINING_2_OFF, MARGINING_IND_LEFT_RIGHT_TIMING, 0x1) |
         HWIO_FVAL(PCIE_GEN4_LANE_MARGINING_2_OFF, MARGINING_IND_UP_DOWN_VOLTAGE, 0x1) |
         HWIO_FVAL(PCIE_GEN4_LANE_MARGINING_2_OFF, MARGINING_VOLTAGE_SUPPORTED, 0x1) |
         HWIO_FVAL(PCIE_GEN4_LANE_MARGINING_2_OFF, MARGINING_MAXLANES, 0x1) |
         HWIO_FVAL(PCIE_GEN4_LANE_MARGINING_2_OFF, MARGINING_SAMPLE_RATE_TIMING, 0x3F) |
         HWIO_FVAL(PCIE_GEN4_LANE_MARGINING_2_OFF, MARGINING_SAMPLE_RATE_VOLTAGE, 0x3F)
   },

   REG_RMW(PCIE_GEN3_RELATED_OFF, GEN3_ZRXDC_NONCOMPL, 0x0),
   {PCIE_REG_OP_DSB},

   /* Clear the BAR mask for the root port */
   REG_RMW(PCIE_ELBI_CS2_ENABLE, ENABLE, 0x1),
   {PCIE_REG_OP_DSB},
   REG_WRITE(PCIE_TYPE1_BAR0_REG, 0x0),
   REG_WRITE(PCIE_TYPE1_BAR1_REG, 0x0),
   {PCIE_REG_OP_DSB},
   REG_RMW(PCIE_ELBI_CS2_ENABLE, ENABLE, 0x0),

   {
      PCIE_REG_OP_RMW,
      HWIO_OFFS(PCIE_TYPE1_STATUS_COMMAND_REG),
      HWIO_FMSK(PCIE_TYPE1_STATUS_COMMAND_REG, BME) |
         HWIO_FMSK(PCIE_TYPE1_STATUS_COMMAND_REG, MSE),
      HWIO_FVAL(PCIE_TYPE1_STATUS_COMMAND_REG, BME, 1) |
         HWIO_FVAL(PCIE_TYPE1_STATUS_COMMAND_REG, MSE, 1)
   },
   {PCIE_REG_OP_STOP},
};

/*******************************************************************************
 *    Register region map
 ******************************************************************************/

#define PCIE_1_BAR_32BIT_BASE PCIE_GEN4X2_SPACE_BASE + 0x200000
#define PCIE_1_BAR_32BIT_SIZE PCIE_GEN4X2_SPACE_SIZE - 0x200000

static mem_region_t port_1_mem_region[max_mem_reg] =
{
  /* axi_reg: DBI register space */
  [axi_reg] =
  {
    .pa = PCIE_GEN4X2_SPACE_BASE,
    .sz = PCIE_GEN4X2_SPACE_SIZE
  },

  /* ahb_reg: PARF register space */
  [ahb_reg] =
  {
    .pa = PCIE1_PCIE_WRAPPER_AHB_W_PHY_G4X2_EDMA_BASE,
    .sz = PCIE1_PCIE_WRAPPER_AHB_W_PHY_G4X2_EDMA_SIZE
  },

  /* tcsr_reg: Access TCSR register space */
  [tcsr_reg] =
  {
    .pa = 0,
    .sz = 0
  },

  /* non_prefetch_32_reg */
  [non_prefetch_32_reg] =
  {
    .pa = PCIE_1_BAR_32BIT_BASE,
    .sz = PCIE_1_BAR_32BIT_SIZE
  },

  /* prefetch_64_reg: prefetchable mem space */
  [prefetch_64_reg] =
  {
    .pa = 0,
    .sz = 0
  }
};

/*******************************************************************************
 *   ICB bandwidth request settings
 ******************************************************************************/
STATIC CONST ICBArb_RequestType pcie_1_icb_request[] =
{
  {
    .arbType = ICBARB_REQUEST_TYPE_3,
    .arbData.type3 =
    {
      .uIb = ((400ULL) << 20), /* Instantaneous bandwidth in Bytes/second */
      .uAb = ((400ULL) << 20), /* Arbitrated bandwidth in Bytes/second */
      .uLatencyNs = 0          /* Latency requirement in nanoseconds */
    }
  },
};

STATIC CONST ICBArb_MasterSlaveType pcie_1_icb_mstr_slv_lst[] =
{
  {
    .eMaster = ICBID_MASTER_PCIE_1,
    .eSlave = ICBID_SLAVE_EBI1
  },
};

STATIC pcieIcbClkBW_t pcie_1_icb_bw[] =
{
  {
    .npa_client_name = "pcie_1",
    .ms_list = pcie_1_icb_mstr_slv_lst,
    .ms_size = sizeof(pcie_1_icb_mstr_slv_lst),
    .req_list = pcie_1_icb_request,
    .req_size = sizeof(pcie_1_icb_request)
  },
};

/*******************************************************************************
 *              PCIe port clk related settings
 ******************************************************************************/
STATIC CONST char * pcie_reset_clks_rp1[] =
{
  "gcc_pcie_1_aux_clk",
  NULL
};

STATIC CONST char * pcie_gcc_clks_rp1[] =
{
  "gcc_pcie_1_cfg_ahb_clk",
  "tcsr_pcie_1_clkref_en",
  "gcc_pcie_1_pipe_clk",
  "gcc_pcie_1_aux_clk",
  "gcc_pcie_1_phy_aux_clk",
  "gcc_aggre_noc_pcie_axi_clk",
  "gcc_pcie_1_slv_q2a_axi_clk",
  "gcc_pcie_1_mstr_axi_clk",
  "gcc_pcie_1_slv_axi_clk",
  "gcc_pcie_1_phy_rchng_clk",
  "gcc_ddrss_pcie_sf_qtb_clk",
  "gcc_cnoc_pcie_sf_axi_clk",
  NULL
};

CONST pcie_clk_mux_cfg_t pcie_1_clk_mux =
{
   .clk_name = "gcc_pcie_1_pipe_clk",
   .en_mux_val = 0,
   .dis_mux_val = 2,
};

CONST clk_freq_cfg_t pcie_1_clk_settings[] =
{
  {.freq = 19200000,  .name = "gcc_pcie_1_aux_clk"},
  {.freq = 100000000, .name = "gcc_pcie_1_phy_rchng_clk"},
  {.freq = 0, .name = NULL},
};

STATIC CONST pcie_clocks_cfg_t pcie_clk_rp1 =
{
   .clk_pwr    = "gcc_pcie_1_gdsc",
   .phy_pwr    = "gcc_pcie_1_phy_gdsc",
   .core_clks  = pcie_gcc_clks_rp1,
   .clk_reset  = pcie_reset_clks_rp1,
   .clk_mux    = &pcie_1_clk_mux,
   .clk_freq   = pcie_1_clk_settings,
   .icb_bw     = pcie_1_icb_bw,
};

/*******************************************************************************
 *              PCIe port GPIO settings
 ******************************************************************************/
#define RC_1_GPIO_PCIE_RESET      97
#define RC_1_GPIO_CLK_REQ         98
#define RC_1_GPIO_PCIE_WAKE       99

STATIC CONST pcie_gpio_cfg_t gpio_config_rp1[] =
{
  {
   .cfg_type = MSM_GPIO,
   {
    .tlmm.gpio_num       = RC_1_GPIO_CLK_REQ,
    .tlmm.func_sel       = 1,
    .tlmm.direction      = GPIO_INPUT,
    .tlmm.pull           = GPIO_PULL_UP,
    .tlmm.drive_strength = GPIO_2MA,
    .tlmm.value          = GPIO_LOW_VALUE
   }
  },

  {
   .cfg_type = MSM_GPIO,
   {
    .tlmm.gpio_num       = RC_1_GPIO_PCIE_RESET,
    .tlmm.func_sel       = 0,
    .tlmm.direction      = GPIO_OUTPUT,
    .tlmm.pull           = GPIO_NO_PULL,
    .tlmm.drive_strength = GPIO_2MA,
    .tlmm.value          = GPIO_LOW_VALUE
   }
  },

  {
   .cfg_type = MSM_GPIO,
   {
    .tlmm.gpio_num       = RC_1_GPIO_PCIE_WAKE,
    .tlmm.func_sel       = 0,
    .tlmm.direction      = GPIO_INPUT,
    .tlmm.pull           = GPIO_PULL_UP,
    .tlmm.drive_strength = GPIO_2MA,
    .tlmm.value          = GPIO_LOW_VALUE
   }
  },

  { .cfg_type = NONE, { .delay_us = NONE } },
};

/*******************************************************************************
 *               Port 1 init Configuration
 ******************************************************************************/
STATIC CONST pcie_reg_init_cfg_t port_1_phy_init_cfg[] =
{
   {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(port_1_phy_init_seq),
   {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(port_1_phy_start_seq),

   {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(phy_delay_seq),

   /* Check if the PHY PLL is locked */
   {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(port_1_phy_poll_seq),

   {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(post_phy_pwr_up_init_seq),

   {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(post_phy_pwr_up_dbi_init_seq),

   {PcieSeq_Stop},
};

/*******************************************************************************
 *               Port 1 Driver config definitions
 ******************************************************************************/
pcie_pmic_config_t port_1_pmic_cfg =
{
   .node_id = PMIC_NPA_GROUP_ID_PCIE1,
   .cxo_id = NULL,
};

static const pcie_drvr_cfg_t port_1_drvr_cfg =
{
   .port_clk_cfg           = &pcie_clk_rp1,
   .port_gpio_cfg          = gpio_config_rp1,
   .iommu_cfg              = "PCIE1",
   .pmic_cfg               = &port_1_pmic_cfg,
   .vcs_cfg                = NULL,
};

/*******************************************************************************
 *               Port 1 config definitions
 ******************************************************************************/
const pcie_port_config_t lanai_port_1_cfg[] =
{
   {
      .hw_rp_index            = 1,
      .driver_config          = &port_1_drvr_cfg,
      .port_mem_bases         = port_1_mem_region,
      .port_phy_init_cfg      = port_1_phy_init_cfg,
      .port_phy_deinit_cfg    = port_1_phy_de_init_cfg,
      .loopback_cfg           = &port_1_loopback_seq,
      .perst_pin              = RC_1_GPIO_PCIE_RESET,
      .port_attributes        = aspm_l1_ena_l0s_ena,
   },
};

const uint8_t lanai_port_1_cfg_len = ARRAY_LENGTH(lanai_port_1_cfg);
