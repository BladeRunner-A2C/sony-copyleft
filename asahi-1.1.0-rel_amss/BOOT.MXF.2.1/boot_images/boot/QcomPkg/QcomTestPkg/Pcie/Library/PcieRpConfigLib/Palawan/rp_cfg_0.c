/*
 *  PCIe root port target config
 *
 *============================================================================
 *       Copyright (c) 2024 Qualcomm Technologies, Inc.
 *       All Rights Reserved.
 *       Confidential and Proprietary - Qualcomm Technologies, Inc.
 *============================================================================*/

#include "Library/pmapp_npa.h"
#include "HALhwio.h"
#include "pcie_hwio_3x2.h"
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
 *                           PORT 0 Phy GEN 3x2
 *
 *******************************************************************************/
STATIC CONST pcie_reg_write_val_t port_0_phy_init_seq[] =
{
   // Source: lanai_1.0_PCIe Gen3 2-lane PHY (n4)_15.0

   /* Device Mode: 0x0: EP 0x4: RC */
   {HWIO_OFFS(PCIE_PARF_DEVICE_TYPE),                                           0x04},
   /*  */
   {HWIO_OFFS(PCS_COM_POWER_DOWN_CONTROL),                                      0x03},
   /*
    * QSERDES_PLL_SSC_EN_CENTER
    * 0x00: Downspread SSC disabled (default, so no write needed);
    * 0x01: Downspread SSC enabled
    */
   {HWIO_OFFS(QSERDES_PLL_SSC_EN_CENTER),                                       0x01},
   /*
    * QSERDES_PLL_SSC_PER1
    * 0x31: 19.2MHz refclk - set SSC frequency to 31.5KHz;
    * 0x62: 38.4MHz refclk - set SSC frequency to 31.5KHz
    */
   {HWIO_OFFS(QSERDES_PLL_SSC_PER1),                                            0x62},
   /*
    * QSERDES_PLL_SSC_PER2
    * 0x01: 19.2MHz refclk;
    * 0x02: 38.4MHz refclk
    */
   {HWIO_OFFS(QSERDES_PLL_SSC_PER2),                                            0x02},
   /*
    * QSERDES_PLL_SSC_STEP_SIZE1_MODE0
    * 0xFF: 19.2MHz refclk - set SSC step size for Gen1/2 (4000ppm);
    * 0xF8: 38.4MHz refclk - set SSC step size for Gen1/2 (4500ppm)
    */
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE1_MODE0),                                0xF8},
   /*
    * QSERDES_PLL_SSC_STEP_SIZE2_MODE0
    * 0x06: 19.2MHz refclk;
    * 0x01: 38.4MHz refclk
    */
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE2_MODE0),                                0x01},
   /*
    * QSERDES_PLL_SSC_STEP_SIZE1_MODE1
    * 0x4C: 19.2MHz refclk - set SSC step size for Gen3 (4500ppm);
    * 0x93: 38.4MHz refclk - set SSC step size for Gen3 (4500ppm)
    */
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE1_MODE1),                                0x93},
   /*
    * QSERDES_PLL_SSC_STEP_SIZE2_MODE1
    * 0x06: 19.2MHz refclk;
    * 0x01: 38.4MHz refclk
    */
   {HWIO_OFFS(QSERDES_PLL_SSC_STEP_SIZE2_MODE1),                                0x01},
   /*  */
   {HWIO_OFFS(QSERDES_PLL_CLK_ENABLE1),                                         0x90},
   /* Select SW endpoint enable */
   {HWIO_OFFS(QSERDES_PLL_SYS_CLK_CTRL),                                        0x82},
   /*  */
   {HWIO_OFFS(QSERDES_PLL_PLL_IVCO),                                            0x07},
   /*  */
   {HWIO_OFFS(QSERDES_PLL_CP_CTRL_MODE0),                                       0x02},
   /*  */
   {HWIO_OFFS(QSERDES_PLL_CP_CTRL_MODE1),                                       0x02},
   /*  */
   {HWIO_OFFS(QSERDES_PLL_PLL_RCTRL_MODE0),                                     0x16},
   /*  */
   {HWIO_OFFS(QSERDES_PLL_PLL_RCTRL_MODE1),                                     0x16},
   /*  */
   {HWIO_OFFS(QSERDES_PLL_PLL_CCTRL_MODE0),                                     0x36},
   /*  */
   {HWIO_OFFS(QSERDES_PLL_PLL_CCTRL_MODE1),                                     0x36},
   /*
    * QSERDES_PLL_SYSCLK_EN_SEL
    * 0x04: select internal diff cml clock inputs;
    * 0x08: select SE cmos clock input
    */
   {HWIO_OFFS(QSERDES_PLL_SYSCLK_EN_SEL),                                       0x08},
   /*
    * QSERDES_PLL_BG_TIMER
    * 0x0E: 19.2MHz refclk value;
    * 0x0A: 38.4MHz refclk value
    */
   {HWIO_OFFS(QSERDES_PLL_BG_TIMER),                                            0x0A},
   /* PLL lock count = 512; use 0x40 for PLL lock count of 1024 (and adjust PLL_LOCK_CMP1/2_MODE0/1 values) */
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP_EN),                                         0x42},
   /*
    * QSERDES_PLL_LOCK_CMP1_MODE0
    * 0x08: 19.2MHz refclk (0x12 when PLL lock count is 1024);
    * 0x04: 38.4MHz refclk (0x0A when PLL lock count is 1024)
    */
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP1_MODE0),                                     0x04},
   /*
    * QSERDES_PLL_LOCK_CMP2_MODE0
    * 0x1A: 19.2MHz refclk (0x34 when PLL lock count is 1024);
    * 0x0D: 38.4MHz refclk (0x1A when PLL lock count is 1024)
    */
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP2_MODE0),                                     0x0D},
   /*
    * QSERDES_PLL_LOCK_CMP1_MODE1
    * 0x14: 19.2MHz refclk (0x2A when PLL lock count is 1024);
    * 0x0A: 38.4MHz refclk (0x14 when PLL lock count is 1024)
    */
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP1_MODE1),                                     0x0A},
   /*
    * QSERDES_PLL_LOCK_CMP2_MODE1
    * 0x34: 19.2MHz refclk (0x68 when PLL lock count is 1024);
    * 0x1A: 38.4MHz refclk (0x34 when PLL lock count is 1024)
    */
   {HWIO_OFFS(QSERDES_PLL_LOCK_CMP2_MODE1),                                     0x1A},
   /*
    * QSERDES_PLL_DEC_START_MODE0
    * 0x82: 19.2MHz refclk;
    * 0x41: 38.4MHz refclk
    */
   {HWIO_OFFS(QSERDES_PLL_DEC_START_MODE0),                                     0x41},
   /*
    * QSERDES_PLL_DEC_START_MODE1
    * 0x68: 19.2MHz refclk;
    * 0x34: 38.4MHz refclk
    */
   {HWIO_OFFS(QSERDES_PLL_DEC_START_MODE1),                                     0x34},
   /*
    * QSERDES_PLL_DIV_FRAC_START1_MODE0
    * 0xAB: 19.2MHz refclk;
    * 0xAB: 38.4MHz refclk
    */
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START1_MODE0),                               0xAB},
   /*
    * QSERDES_PLL_DIV_FRAC_START2_MODE0
    * 0xEA: 19.2MHz refclk;
    * 0xAA: 38.4MHz refclk
    */
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START2_MODE0),                               0xAA},
   /*
    * QSERDES_PLL_DIV_FRAC_START3_MODE0
    * 0x02: 19.2MHz refclk;
    * 0x01: 38.4MHz refclk
    */
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START3_MODE0),                               0x01},
   /*
    * QSERDES_PLL_DIV_FRAC_START1_MODE1
    * 0xAB: 19.2MHz refclk;
    * 0x55: 38.4MHz refclk
    */
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START1_MODE1),                               0x55},
   /*
    * QSERDES_PLL_DIV_FRAC_START2_MODE1
    * 0xAA: 19.2MHz refclk;
    * 0x55: 38.4MHz refclk
    */
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START2_MODE1),                               0x55},
   /*
    * QSERDES_PLL_DIV_FRAC_START3_MODE1
    * 0x02: 19.2MHz refclk;
    * 0x01: 38.4MHz refclk
    */
   {HWIO_OFFS(QSERDES_PLL_DIV_FRAC_START3_MODE1),                               0x01},
   /* Set mode0 as gen1/2 and mode1 as gen3 */
   {HWIO_OFFS(QSERDES_PLL_VCO_TUNE_MAP),                                        0x14},
   /*  */
   {HWIO_OFFS(QSERDES_PLL_CLK_SELECT),                                          0x34},
   /*  */
   {HWIO_OFFS(QSERDES_PLL_HSCLK_SEL_1),                                         0x01},
   /*  */
   {HWIO_OFFS(QSERDES_PLL_CORECLK_DIV_MODE1),                                   0x04},
   /*  */
   {HWIO_OFFS(QSERDES_PLL_CMN_CONFIG_1),                                        0x16},
   /*  */
   {HWIO_OFFS(QSERDES_PLL_ADDITIONAL_MISC_3),                                   0x0F},
   /* Set PLL lock clock divider */
   {HWIO_OFFS(QSERDES_PLL_CORE_CLK_EN),                                         0xA0},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_DFE_CTLE_POST_CAL_OFFSET),                            0x38},
   /*
    * QSERDES_RX0_GM_CAL
    * 0x0D: value for Pinnacles;
    * 0x11: value for others
    */
   {HWIO_OFFS(QSERDES_RX0_GM_CAL),                                              0x11},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_00_HIGH),                                     0xBF},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_00_HIGH2),                                    0xBF},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_00_HIGH3),                                    0xB7},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_00_HIGH4),                                    0xEA},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_00_LOW),                                      0x3F},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_01_HIGH),                                     0x5C},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_01_HIGH2),                                    0x9C},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_01_HIGH3),                                    0x1A},
   /* Use 0x8F for ultra-short channel (<5dB loss) */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_01_HIGH4),                                    0x89},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_01_LOW),                                      0xDC},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_10_HIGH),                                     0x94},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_10_HIGH2),                                    0x5B},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_10_HIGH3),                                    0x1A},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_RX_MODE_10_HIGH4),                                    0x89},
   /* Adjust post cursor adaptation (Palima can keep 0xF0) */
   {HWIO_OFFS(QSERDES_RX0_TX_ADAPT_POST_THRESH),                                0x00},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_UCDR_FO_GAIN),                                        0x09},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_UCDR_SO_GAIN),                                        0x05},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_UCDR_SB2_THRESH1),                                    0x08},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_UCDR_SB2_THRESH2),                                    0x08},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_VGA_CAL_CNTRL2),                                      0x0F},
   /* Force use of local bias; bypass pulse width filter */
   {HWIO_OFFS(QSERDES_RX0_SIGDET_ENABLES),                                      0x1C},
   /*  */
   {HWIO_OFFS(QSERDES_RX0_RX_IDAC_TSETTLE_LOW),                                 0x07},
   /* Adjust sigdet cal trim */
   {HWIO_OFFS(QSERDES_RX0_SIGDET_CAL_TRIM),                                     0x08},
   /* Lane disable variable anchor point (default value) */
   {HWIO_OFFS(QSERDES_TX1_BIST_MODE_LANENO),                                    0x00},
   /*  */
   {HWIO_OFFS(QSERDES_TX0_LANE_MODE_1),                                         0x15},
   /*  */
   {HWIO_OFFS(QSERDES_TX0_LANE_MODE_4),                                         0x3F},
   /*  */
   {HWIO_OFFS(QSERDES_TX0_PI_QEC_CTRL),                                         0x02},
   /*
    * QSERDES_TX0_RES_CODE_LANE_OFFSET_RX
    * 0x09: value for Lanai;
    * 0x06: value for others
    */
   {HWIO_OFFS(QSERDES_TX0_RES_CODE_LANE_OFFSET_RX),                             0x06},
   /*
    * QSERDES_TX0_RES_CODE_LANE_OFFSET_TX
    * 0x15: value for Lanai;
    * 0x18: value for others
    */
   {HWIO_OFFS(QSERDES_TX0_RES_CODE_LANE_OFFSET_TX),                             0x18},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_DFE_CTLE_POST_CAL_OFFSET),                            0x38},
   /*
    * QSERDES_RX1_GM_CAL
    * 0x0D: value for Pinnacles;
    * 0x11: value for others
    */
   {HWIO_OFFS(QSERDES_RX1_GM_CAL),                                              0x11},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_00_HIGH),                                     0xBF},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_00_HIGH2),                                    0xBF},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_00_HIGH3),                                    0xB7},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_00_HIGH4),                                    0xEA},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_00_LOW),                                      0x3F},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_01_HIGH),                                     0x5C},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_01_HIGH2),                                    0x9C},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_01_HIGH3),                                    0x1A},
   /* Use 0x8F for ultra-short channel (<5dB loss) */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_01_HIGH4),                                    0x89},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_01_LOW),                                      0xDC},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_10_HIGH),                                     0x94},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_10_HIGH2),                                    0x5B},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_10_HIGH3),                                    0x1A},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_RX_MODE_10_HIGH4),                                    0x89},
   /* Adjust post cursor adaptation (Palima can keep 0xF0) */
   {HWIO_OFFS(QSERDES_RX1_TX_ADAPT_POST_THRESH),                                0x00},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_UCDR_FO_GAIN),                                        0x09},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_UCDR_SO_GAIN),                                        0x05},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_UCDR_SB2_THRESH1),                                    0x08},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_UCDR_SB2_THRESH2),                                    0x08},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_VGA_CAL_CNTRL2),                                      0x0F},
   /* Force use of local bias; bypass pulse width filter */
   {HWIO_OFFS(QSERDES_RX1_SIGDET_ENABLES),                                      0x1C},
   /*  */
   {HWIO_OFFS(QSERDES_RX1_RX_IDAC_TSETTLE_LOW),                                 0x07},
   /* Adjust sigdet cal trim */
   {HWIO_OFFS(QSERDES_RX1_SIGDET_CAL_TRIM),                                     0x08},
   /*  */
   {HWIO_OFFS(QSERDES_TX1_LANE_MODE_1),                                         0x15},
   /*  */
   {HWIO_OFFS(QSERDES_TX1_LANE_MODE_4),                                         0x3F},
   /*  */
   {HWIO_OFFS(QSERDES_TX1_PI_QEC_CTRL),                                         0x02},
   /*
    * QSERDES_TX1_RES_CODE_LANE_OFFSET_RX
    * 0x09: value for Lanai;
    * 0x06: value for others
    */
   {HWIO_OFFS(QSERDES_TX1_RES_CODE_LANE_OFFSET_RX),                             0x06},
   /*
    * QSERDES_TX1_RES_CODE_LANE_OFFSET_TX
    * 0x15: value for Lanai;
    * 0x18: value for others
    */
   {HWIO_OFFS(QSERDES_TX1_RES_CODE_LANE_OFFSET_TX),                             0x18},
   /*  */
   {HWIO_OFFS(PCS_COM_REFGEN_REQ_CONFIG1),                                      0x05},
   /*  */
   {HWIO_OFFS(PCS_COM_RX_SIGDET_LVL),                                           0x77},
   /*  */
   {HWIO_OFFS(PCS_COM_RATE_SLEW_CNTRL1),                                        0x0B},
   /* Flip post inc/dec mapping */
   {HWIO_OFFS(PCS_PCIE_EQ_CONFIG1),                                             0x1E},
   /* Increase adaption eval time to 40us */
   {HWIO_OFFS(PCS_PCIE_RXEQEVAL_TIME),                                          0x27},
   /*  */
   {HWIO_OFFS(PCS_COM_EQ_CONFIG2),                                              0x0F},
   /*  */
   {HWIO_OFFS(PCS_PCIE_POWER_STATE_CONFIG2),                                    0x1D},
   /*  */
   {HWIO_OFFS(PCS_PCIE_POWER_STATE_CONFIG4),                                    0x07},
   /*  */
   {HWIO_OFFS(PCS_PCIE_ENDPOINT_REFCLK_DRIVE),                                  0xC1},
   /*  */
   {HWIO_OFFS(PCS_PCIE_OSC_DTCT_ACTIONS),                                       0x00},
   /* Set Pinf RTB depth to 5 for all gens (evaluate per SOC) */
   {HWIO_OFFS(PCS_COM_PCS_TX_RX_CONFIG),                                        0x8C},
   /* Gen1/2 -6dB txdeemph coefficient mapping; set to 0x0F to force -3.5dB (for ultra short channel (<5dB loss)) */
   {HWIO_OFFS(PCS_COM_G12S1_TXDEEMPH_M6DB),                                     0x17},
   /*
    * PCS_LANE1_INSIG_SW_CTRL2
    * 0x00: 2-lane mode (default value - write not needed);
    * 0x01: 1-lane mode - lane1 disabled
    */
   {HWIO_OFFS(PCS_LANE1_INSIG_SW_CTRL2),                                        0x00},
   /*
    * PCS_LANE1_INSIG_MX_CTRL2
    * 0x00: 2-lane mode (default value - write not needed);
    * 0x01: 1-lane mode - lane1 disabled
    */
   {HWIO_OFFS(PCS_LANE1_INSIG_MX_CTRL2),                                        0x00},

   /*   END   */
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_0_phy_start_seq[] =
{
   {HWIO_OFFS(PCS_COM_SW_RESET),         0x00},  //    Release software reset
   {HWIO_OFFS(PCS_COM_START_CONTROL),    0x03},  //    Start PCS and Serdes power SMs
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t port_0_phy_poll_seq[] =
{
   {PCIE_REG_OP_POLL, HWIO_OFFS(PCS_COM_PCS_STATUS1), HWIO_PCS_COM_PCS_STATUS1_PHYSTATUS_BMSK, FALSE},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_0_phy_de_init_seq[] =
{
   {HWIO_OFFS(PCS_COM_POWER_DOWN_CONTROL),    0x00},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_op_t phy_delay_seq[] =
{
   {PCIE_REG_OP_DELAY, 0, 0, 2000},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t port_0_phy_de_init_cfg[] =
{
   {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(port_0_phy_de_init_seq),
   {PcieSeq_Stop},
};

/*******************************************************************************
 *                       Loopback
 ******************************************************************************/

STATIC CONST pcie_reg_write_val_t port_0_phy_lpb_en_seq[] =
{
   {HWIO_OFFS(QSERDES_TX0_LPB_EN),                 0x0C},
   {HWIO_OFFS(QSERDES_TX1_LPB_EN),                 0x0C},
   {HWIO_OFFS(PCS_LANE0_PCS_LANE_TEST_CONTROL1),   0x03},
   {HWIO_OFFS(PCS_LANE1_PCS_LANE_TEST_CONTROL1),   0x03},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_write_val_t port_0_phy_lpb_dis_seq[] =
{
   {HWIO_OFFS(QSERDES_TX0_LPB_EN),                 0x00},
   {HWIO_OFFS(QSERDES_TX1_LPB_EN),                 0x00},
   {HWIO_OFFS(PCS_LANE0_PCS_LANE_TEST_CONTROL1),   0x00},
   {HWIO_OFFS(PCS_LANE1_PCS_LANE_TEST_CONTROL1),   0x00},
   {PCIE_REG_OP_STOP},
};

STATIC CONST pcie_reg_init_cfg_t port_0_phy_lpb_en_cfg[] =
{
   {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(port_0_phy_lpb_en_seq),
   {PcieSeq_Stop},
};

STATIC CONST pcie_reg_init_cfg_t port_0_phy_lpb_dis_cfg[] =
{
   {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(port_0_phy_lpb_dis_seq),
   {PcieQcSoCVer_All,     ahb_reg,  REG_WRITE_TYPE(port_0_phy_de_init_seq),
   {PcieSeq_Stop},
};

STATIC CONST pcie_loopback_cfg_t port_0_loopback_seq =
{
   port_0_phy_lpb_en_cfg,
   port_0_phy_lpb_dis_cfg,
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

STATIC CONST pcie_reg_op_t post_phy_pwr_up_dbi_init_seq[] =
{
   // WARNING..!!: Only AXI registers in this set
   REG_RMW(PCIE_PORT_LINK_CTRL_OFF, LINK_CAPABLE, PORT_LINK_2_LANE_CAPABLE_VAL),
   REG_RMW(PCIE_LINK_CONTROL2_LINK_STATUS2_REG, PCIE_CAP_TARGET_LINK_SPEED, PORT_LINK_SPEED_GEN_3),
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
   {PCIE_REG_OP_DSB},
   REG_RMW(PCIE_MISC_CONTROL_1_OFF, DBI_RO_WR_EN, 0x0),

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
         HWIO_FVAL(PCIE_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF, GEN3_EQ_FMDC_T_MIN_PHASE23, 0x0)
   },
   {
      PCIE_REG_OP_RMW, HWIO_OFFS(PCIE_GEN3_EQ_CONTROL_OFF),
      HWIO_FMSK(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_PHASE23_EXIT_MODE) |
         HWIO_FMSK(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_PSET_REQ_VEC),
      HWIO_FVAL(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_PHASE23_EXIT_MODE, 0x0) |
         HWIO_FVAL(PCIE_GEN3_EQ_CONTROL_OFF, GEN3_EQ_PSET_REQ_VEC, 0x0)
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

#define PCIE_0_BAR_32BIT_BASE PCIE_GEN3X2_SPACE_BASE + 0x200000
#define PCIE_0_BAR_32BIT_SIZE PCIE_GEN3X2_SPACE_SIZE - 0x200000

static const mem_region_t port_0_mem_region[max_mem_reg] =
{
  /* axi_reg: DBI register space */
  [axi_reg] =
  {
    .pa = PCIE_GEN3X2_SPACE_BASE,
    .sz = PCIE_GEN3X2_SPACE_SIZE
  },

  /* ahb_reg: PARF register space */
  [ahb_reg] =
  {
    .pa = PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X2_EDMA_BASE,
    .sz = PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X2_EDMA_SIZE
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
    .pa = PCIE_0_BAR_32BIT_BASE,
    .sz = PCIE_0_BAR_32BIT_SIZE
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
STATIC CONST ICBArb_RequestType pcie_0_icb_request[] =
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

STATIC CONST ICBArb_MasterSlaveType pcie_0_icb_mstr_slv_lst[] =
{
  {
    .eMaster = ICBID_MASTER_PCIE_0,
    .eSlave = ICBID_SLAVE_EBI1
  },
};

STATIC pcieIcbClkBW_t pcie_0_icb_bw[] =
{
  {
    .npa_client_name = "pcie_0",
    .ms_list = pcie_0_icb_mstr_slv_lst,
    .ms_size = sizeof(pcie_0_icb_mstr_slv_lst),
    .req_list = pcie_0_icb_request,
    .req_size = sizeof(pcie_0_icb_request)
  },
};

/*******************************************************************************
 *              PCIe port clk related settings
 ******************************************************************************/
STATIC CONST char * pcie_reset_clks_rp0[] =
{
  "gcc_pcie_0_aux_clk",
  NULL
};

STATIC CONST char * pcie_gcc_clks_rp0[] =
{
  "gcc_pcie_0_cfg_ahb_clk",
  "tcsr_pcie_2l_clkref_en",
  "gcc_pcie_0_pipe_clk",
  "gcc_pcie_0_aux_clk",
  "gcc_aggre_noc_pcie_axi_clk",
  "gcc_pcie_0_slv_q2a_axi_clk",
  "gcc_pcie_0_mstr_axi_clk",
  "gcc_pcie_0_slv_axi_clk",
  "gcc_pcie_0_pipe_div2_clk",
  "gcc_pcie_0_phy_rchng_clk",
  "gcc_ddrss_pcie_sf_qtb_clk",
  "gcc_cnoc_pcie_sf_axi_clk",
  NULL
};

CONST pcie_clk_mux_cfg_t palawan_pcie_0_clk_mux =
{
   .clk_name = "gcc_pcie_0_pipe_clk",
   .en_mux_val = 0,
   .dis_mux_val = 2,
};

CONST clk_freq_cfg_t palawan_pcie_0_clk_settings[] =
{
  {.freq = 19200000,  .name = "gcc_pcie_0_aux_clk"},
  {.freq = 100000000, .name = "gcc_pcie_0_phy_rchng_clk"},
  {.freq = 0, .name = NULL},
};

STATIC CONST pcie_clocks_cfg_t palawan_pcie_clk_rp0 =
{
   .clk_pwr    = "gcc_pcie_0_gdsc",
   .phy_pwr    = "gcc_pcie_0_phy_gdsc",
   .core_clks  = pcie_gcc_clks_rp0,
   .clk_reset  = pcie_reset_clks_rp0,
   .clk_mux    = &palawan_pcie_0_clk_mux,
   .clk_freq   = palawan_pcie_0_clk_settings,
   .icb_bw     = pcie_0_icb_bw,
};

/*******************************************************************************
 *              PCIe port GPIO settings
 ******************************************************************************/
#define RC_0_GPIO_PCIE_RESET      33
#define RC_0_GPIO_CLK_REQ         118
#define RC_0_GPIO_PCIE_WAKE       81

STATIC CONST pcie_gpio_cfg_t palawan_gpio_config_rp0[] =
{
  {
   .cfg_type = MSM_GPIO,
   {
    .tlmm.gpio_num       = RC_0_GPIO_CLK_REQ,
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
    .tlmm.gpio_num       = RC_0_GPIO_PCIE_RESET,
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
    .tlmm.gpio_num       = RC_0_GPIO_PCIE_WAKE,
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
 *               Port 0 init Configuration
 ******************************************************************************/
STATIC CONST pcie_reg_init_cfg_t port_0_phy_init_cfg[] =
{
   {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(port_0_phy_init_seq),
   {PcieQcSoCVer_All,    ahb_reg,  REG_WRITE_TYPE(port_0_phy_start_seq),

   {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(phy_delay_seq),

    /* Check if the PHY PLL is locked */
   {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(port_0_phy_poll_seq),

   {PcieQcSoCVer_All,    ahb_reg,  REG_OP_TYPE(post_phy_pwr_up_init_seq),

   {PcieQcSoCVer_All,    axi_reg,  REG_OP_TYPE(post_phy_pwr_up_dbi_init_seq),

   {PcieSeq_Stop},
};

/*******************************************************************************
 *               Port 0 Driver config definitions
 ******************************************************************************/
pcie_pmic_config_t palawan_port_0_pmic_cfg =
{
   .node_id = PMIC_NPA_GROUP_ID_PCIE0,
   .cxo_id = NULL,
};

static const pcie_drvr_cfg_t port_0_drvr_cfg =
{
   .port_clk_cfg           = &palawan_pcie_clk_rp0,
   .port_gpio_cfg          = palawan_gpio_config_rp0,
   .iommu_cfg              = "PCIE0",
   .pmic_cfg               = &palawan_port_0_pmic_cfg,
   .vcs_cfg                = NULL,
};

/*******************************************************************************
 *               Port 0 config definitions
 ******************************************************************************/
const pcie_port_config_t palawan_port_0_cfg[] =
{
   {
      .hw_rp_index            = 0,
      .driver_config          = &port_0_drvr_cfg,
      .port_mem_bases         = port_0_mem_region,
      .port_phy_init_cfg      = port_0_phy_init_cfg,
      .port_phy_deinit_cfg    = port_0_phy_de_init_cfg,
      .loopback_cfg           = &port_0_loopback_seq,
      .perst_pin              = RC_0_GPIO_PCIE_RESET,
      .port_attributes        = aspm_l1_ena_l0s_ena,
   },
};

const uint8_t palawan_port_0_cfg_len = ARRAY_LENGTH(palawan_port_0_cfg);
