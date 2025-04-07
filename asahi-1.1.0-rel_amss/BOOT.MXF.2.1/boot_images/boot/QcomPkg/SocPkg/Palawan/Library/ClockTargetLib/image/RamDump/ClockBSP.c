/*
==============================================================================

FILE:         ClockBSP.c

DESCRIPTION:
  This file contains the clock driver BSP data.

  Auto-generated from the following IPCat controller releases:

    Palawanv0 (palawan_1.0):
      PLL_HSR   : 4.0
      DISP_CC   : palawan_disp_cc_z_disp_cc_palawan_1.0_p3q3r13_fp9 [palwan_disp_cc.r2]
      GCC       : palawan_gcc_z_palawan_clk_ctl_1.0_p3q2r16_fp19 [palawan_gcc.r19]
      TCSR_CC   : None


  Generated using the following clockdrivergen settings:

CLOCKDRIVERGEN_CONFIG = \
{'db_override': {'GCC': {'cbc': {'gcc_aggre_ufs_phy_axi_clk': {'func_group': 'ufs_phy'},
                                 'gcc_aggre_usb3_prim_axi_clk': {'func_group': 'usb30_prim'},
                                 'gcc_cfg_noc_usb3_prim_axi_clk': {'func_group': 'usb30_prim'}},
                         'gdsc': {'gcc_ufs_mem_phy_gdsc': {'func_group': 'ufs_phy'}}},
                 'TCSR_CC': {'cbc': {'tcsr_ufs_pad_clkref_en': {'func_group': 'ufs_phy'},
                                     'tcsr_ufs_phy_clkref_en': {'func_group': 'ufs_phy'},
                                     'tcsr_usb2_clkref_en': {'func_group': 'usb30_prim'},
                                     'tcsr_usb3_clkref_en': {'func_group': 'usb30_prim'}}}},
 'exclude_unused': True,
 'filter_warning': 'sw',
 'generators': [{'options': {'clock_flags': {'gcc_gpll0': ['DO_NOT_DISABLE',
                                                           '!DIVIDER_SUPPORTS_HID',
                                                           'INTERNAL_CONTROL'],
                                             'gcc_ufs_phy_rx_symbol_0_clk': ['NO_POLL_AFTER_ENABLE',
                                                                             '!DIVIDER_SUPPORTS_HID'],
                                             'gcc_ufs_phy_rx_symbol_1_clk': ['NO_POLL_AFTER_ENABLE',
                                                                             '!DIVIDER_SUPPORTS_HID'],
                                             'gcc_ufs_phy_tx_symbol_0_clk': ['NO_POLL_AFTER_ENABLE',
                                                                             '!DIVIDER_SUPPORTS_HID'],
                                             'gcc_usb3_prim_phy_pipe_clk': ['NO_POLL_AFTER_ENABLE',
                                                                            '!DIVIDER_SUPPORTS_HID']},
                             'clock_flags_hal': {'.*': ['!DIVIDER_SUPPORTS_HID']},
                             'detect_configs': False,
                             'domain_freq_config_format': '  {{{{ {FREQ:>10}, '
                                                          '{VREG:<30} {{{{ '
                                                          '{SEL:<6} {DIV:<6} '
                                                          '{M:<6} {N:<6} '
                                                          '{DFS:<4} }}}}, '
                                                          '{SOURCE:<45} '
                                                          '{SOURCE_FREQ_IDX:<20}, '
                                                          '{{VERSION}} }}}},  '
                                                          '{COMMENT}\n',
                             'env': 'ramdump',
                             'explicit_ownership': True,
                             'flat_structs': True,
                             'include_bcrs': False,
                             'include_clock_groups': ['ufs_phy',
                                                      'sdcc.*',
                                                      'usb30_prim'],
                             'include_control': ['source'],
                             'include_debug_mux': False,
                             'include_divider': ['.*disp_cc.*'],
                             'include_file': {'HALclkTest.c': False},
                             'include_fmax': False,
                             'include_only_freqs': {'.*qup.*wrap._s.*': [7372800,
                                                                         14745600,
                                                                         19200000,
                                                                         48000000]},
                             'include_source_map': False,
                             'include_source_name': False,
                             'include_unique_id': False,
                             'include_voltage_control': False,
                             'include_xo_voting': False,
                             'pll_disable_mode': None,
                             'source_enums': True,
                             'source_freq_config_format': '  {{{{ {{{{ '
                                                          '{ALPHA}, '
                                                          'HAL_CLK_PLL_FRAC_MODE_{FRACMODE}, '
                                                          '{POST:<30}, {L:<4} '
                                                          '}}}}, '
                                                          '{{VERSION}}}}}},\n'},
                 'output_dir': 'image/RamDump',
                 'type': 'dalclock'}],
 'target': ['palawan']}

==============================================================================

$Header: $

==============================================================================
            Copyright (c) 2023 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================

*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockBSP.h"
#include "HALclkHWIO.h"
#include "HALhwio.h"


/*=========================================================================
      Externs
==========================================================================*/

extern HAL_clk_SourceControlType          HAL_clk_LucidolePLLControl;


/*=========================================================================
      Data Declarations
==========================================================================*/


/*=========================================================================
      Source Register Settings
==========================================================================*/

static const ClockSourceRegSettingsType ClockSourceRegSettings_DISPCC_DISPCCPLL0[] =
{
  {
    .HALSettings = {
      .nConfigCtl   = 0x20485699,
      .nConfigCtl1  = 0x00182261,
      .nConfigCtl2  = 0x82AA299C,
      .nTestCtl     = 0x00000000,
      .nTestCtl1    = 0x00000003,
      .nTestCtl2    = 0x00009000,
      .nTestCtl3    = 0x00000034,
      .nUserCtl     = 0x00000000,
      .nUserCtl1    = 0x00000005,
    },
  },
};


/*=========================================================================
      Source BSP
==========================================================================*/

/*
 * ClockSourceBSP_DISPCC_DISPCCPLL0
 *
 * Used by:
 *   ClockSource_DISPCC_DISPCCPLL0
 */
static const ClockSourceFreqConfigType ClockSourceBSP_DISPCC_DISPCCPLL0[] =
{
  { { 0x00006492, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 13,  }, },
  { { 0x0000A000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 15,  }, },
  { { 0x00003800, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 24,  }, },
  { { 0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 31,  }, },
  { { 0x00007000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 53,  }, },
  { { 0x0000D000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 62,  }, },
  { { 0x00005000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 80,  }, },
  { { 0x0000C000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 93,  }, },
};
static const ClockSourceFreqConfigType ClockSourceBSPCal_DISPCC_DISPCCPLL0[] =
{
  { { 0x00000000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 68,  }, },
};

/*
 * ClockSourceBSP_DISPCC_DISPCCPLL1
 *
 * Used by:
 *   ClockSource_DISPCC_DISPCCPLL1
 */
static const ClockSourceFreqConfigType ClockSourceBSP_DISPCC_DISPCCPLL1[] =
{
  { { 0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 31,  }, },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL0
 *
 * Used by:
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL0[] =
{
  { { 0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}       , 31,  }, },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL1
 *
 * Used by:
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL1[] =
{
  { { 0x00008555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 55,  }, },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL4
 *
 * Used by:
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL4[] =
{
  { { 0x0000FAAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 41,  }, },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL9
 *
 * Used by:
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL9[] =
{
  { { 0x00001555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                     , 42,  }, },
};


/*=========================================================================
      Sources
==========================================================================*/

static ClockSourceNodeType ClockSource_DISPCC_DISPCCPLL0 =
{
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_DISPCC_DISPCCPLL0,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_DISPCC_DISPCCPLL0),
  .nConfigMask  = 0x0,
  .nAddr          = HWIO_ADDR(DISP_CC_PLL0_PLL_MODE),
  .pmControl      = &HAL_clk_LucidolePLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSPCal_DISPCC_DISPCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_DISPCC_DISPCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_DISPCC_DISPCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_DISPCC_DISPCCPLL0),
};

static ClockSourceNodeType ClockSource_DISPCC_DISPCCPLL1 =
{
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_DISPCC_DISPCCPLL1,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_DISPCC_DISPCCPLL1),
  .nConfigMask  = 0x0,
  .nAddr          = HWIO_ADDR(DISP_CC_PLL1_PLL_MODE),
  .pmControl      = &HAL_clk_LucidolePLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSPCal_DISPCC_DISPCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_DISPCC_DISPCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_DISPCC_DISPCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_DISPCC_DISPCCPLL0),
};

static ClockSourceNodeType ClockSource_GCC_GCCGPLL0 =
{
  .nFlags       = CLOCK_FLAG_DO_NOT_DISABLE |
                  CLOCK_FLAG_INTERNAL_CONTROL |
                  CLOCK_FLAG_READ_ONLY,
  .aBSP         = ClockSourceBSP_GCC_GCCGPLL0,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL0),
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE |
                  CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
  .nAddr          = HWIO_ADDR(GCC_GPLL0_PLL_MODE),
  .VoterRegister  = {HWIO_ADDR(GCC_PROC_CLK_PLL_ENA_VOTE), 0x1},
  .pmControl      = &HAL_clk_LucidolePLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSPCal_DISPCC_DISPCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_DISPCC_DISPCCPLL0),
};

static ClockSourceNodeType ClockSource_GCC_GCCGPLL1 =
{
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL |
                  CLOCK_FLAG_READ_ONLY,
  .aBSP         = ClockSourceBSP_GCC_GCCGPLL1,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL1),
  .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
  .nAddr          = HWIO_ADDR(GCC_GPLL1_PLL_MODE),
  .VoterRegister  = {HWIO_ADDR(GCC_PROC_CLK_PLL_ENA_VOTE), 0x2},
  .pmControl      = &HAL_clk_LucidolePLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSPCal_DISPCC_DISPCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_DISPCC_DISPCCPLL0),
};

static ClockSourceNodeType ClockSource_GCC_GCCGPLL4 =
{
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL |
                  CLOCK_FLAG_READ_ONLY,
  .aBSP         = ClockSourceBSP_GCC_GCCGPLL4,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL4),
  .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
  .nAddr          = HWIO_ADDR(GCC_GPLL4_PLL_MODE),
  .VoterRegister  = {HWIO_ADDR(GCC_PROC_CLK_PLL_ENA_VOTE), 0x10},
  .pmControl      = &HAL_clk_LucidolePLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSPCal_DISPCC_DISPCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_DISPCC_DISPCCPLL0),
};

static ClockSourceNodeType ClockSource_GCC_GCCGPLL9 =
{
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL |
                  CLOCK_FLAG_READ_ONLY,
  .aBSP         = ClockSourceBSP_GCC_GCCGPLL9,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL9),
  .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
  .nAddr          = HWIO_ADDR(GCC_GPLL9_PLL_MODE),
  .VoterRegister  = {HWIO_ADDR(GCC_PROC_CLK_PLL_ENA_VOTE), 0x200},
  .pmControl      = &HAL_clk_LucidolePLLControl,
  .pCalibrationFreqConfig     = ClockSourceBSPCal_DISPCC_DISPCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_DISPCC_DISPCCPLL0),
};

enum
{
  SRC_IDX_DISPCC_DISPCCPLL0,
  SRC_IDX_DISPCC_DISPCCPLL1,
  SRC_IDX_GCC_GCCGPLL0,
  SRC_IDX_GCC_GCCGPLL1,
  SRC_IDX_GCC_GCCGPLL4,
  SRC_IDX_GCC_GCCGPLL9,
};

static ClockSourceNodeType *aSources[] =
{
  [SRC_IDX_DISPCC_DISPCCPLL0] = &ClockSource_DISPCC_DISPCCPLL0,
  [SRC_IDX_DISPCC_DISPCCPLL1] = &ClockSource_DISPCC_DISPCCPLL1,
  [SRC_IDX_GCC_GCCGPLL0] = &ClockSource_GCC_GCCGPLL0,
  [SRC_IDX_GCC_GCCGPLL1] = &ClockSource_GCC_GCCGPLL1,
  [SRC_IDX_GCC_GCCGPLL4] = &ClockSource_GCC_GCCGPLL4,
  [SRC_IDX_GCC_GCCGPLL9] = &ClockSource_GCC_GCCGPLL9,
};

/*=========================================================================
      Dividers
==========================================================================*/

static ClockDividerNodeType aDividers[] =
{
  {
    .szName    = "disp_cc_debug_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = HWIO_ADDR(DISP_CC_DEBUG_DIV_CDIVR),
  },
  {
    .szName    = "disp_cc_mdss_byte0_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = HWIO_ADDR(DISP_CC_MDSS_BYTE0_DIV_CDIVR),
  },
  {
    .szName    = "disp_cc_mdss_byte1_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = HWIO_ADDR(DISP_CC_MDSS_BYTE1_DIV_CDIVR),
  },
  {
    .szName    = "disp_cc_mdss_dptx0_crypto_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = 0,
  },
  {
    .szName    = "disp_cc_mdss_dptx0_link_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = HWIO_ADDR(DISP_CC_MDSS_DPTX0_LINK_DIV_CDIVR),
  },
  {
    .szName    = "disp_cc_mdss_dptx1_crypto_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = 0,
  },
  {
    .szName    = "disp_cc_mdss_dptx1_link_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = HWIO_ADDR(DISP_CC_MDSS_DPTX1_LINK_DIV_CDIVR),
  },
  {
    .szName    = "disp_cc_mdss_dptx2_crypto_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = 0,
  },
  {
    .szName    = "disp_cc_mdss_dptx2_link_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = HWIO_ADDR(DISP_CC_MDSS_DPTX2_LINK_DIV_CDIVR),
  },
  {
    .szName    = "disp_cc_mdss_dptx3_crypto_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = 0,
  },
  {
    .szName    = "disp_cc_mdss_dptx3_link_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = HWIO_ADDR(DISP_CC_MDSS_DPTX3_LINK_DIV_CDIVR),
  },
  {
    .szName    = "disp_cc_mdss_spdm_debug_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = HWIO_ADDR(DISP_CC_MDSS_SPDM_DEBUG_DIV_CDIVR),
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_crypto_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = HWIO_ADDR(DISP_CC_MDSS_SPDM_DP_CRYPTO_DIV_CDIVR),
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_pixel1_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = HWIO_ADDR(DISP_CC_MDSS_SPDM_DP_PIXEL1_DIV_CDIVR),
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_pixel_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = HWIO_ADDR(DISP_CC_MDSS_SPDM_DP_PIXEL_DIV_CDIVR),
  },
  {
    .szName    = "disp_cc_mdss_spdm_mdp_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = HWIO_ADDR(DISP_CC_MDSS_SPDM_MDP_DIV_CDIVR),
  },
  {
    .szName    = "disp_cc_mdss_spdm_pclk0_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = HWIO_ADDR(DISP_CC_MDSS_SPDM_PCLK0_DIV_CDIVR),
  },
  {
    .szName    = "disp_cc_mdss_spdm_pclk1_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = HWIO_ADDR(DISP_CC_MDSS_SPDM_PCLK1_DIV_CDIVR),
  },
  {
    .szName    = "disp_cc_pll_test_div_clk_src",
    .nFlags    = 0x0,
    .nAddr       = HWIO_ADDR(DISP_CC_PLL_TEST_DIV_CDIVR),
  },
};


/*=========================================================================
      Domain BSP
==========================================================================*/

/*
 * ClockDomainBSP_DISPCC_DISPCCMDSSAHB
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSAHB
 */
static ClockMuxConfigType ClockDomainBSP_DISPCC_DISPCCMDSSAHB[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, { 0,     2,     0,     0,     0xFF }, SRC_IDX_NULL,                                 0                   ,  },   /* Mux[0] = BI_TCXO */
  {   37500000, RAIL_VOLTAGE_LEVEL_SVS,        { 4,     32,    0,     0,     0xFF }, SRC_IDX_DISPCC_DISPCCPLL1,                    0                   ,  },   /* Mux[4] = DISP_CC_PLL1_OUT_MAIN */
  {   75000000, RAIL_VOLTAGE_LEVEL_NOM,        { 4,     16,    0,     0,     0xFF }, SRC_IDX_DISPCC_DISPCCPLL1,                    0                   ,  },   /* Mux[4] = DISP_CC_PLL1_OUT_MAIN */
};

/*
 * ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSBYTE0
 *   ClockDomain_DISPCC_DISPCCMDSSBYTE1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSESC0
 *   ClockDomain_DISPCC_DISPCCMDSSESC1
 *   ClockDomain_DISPCC_DISPCCMDSSPCLK0
 *   ClockDomain_DISPCC_DISPCCMDSSPCLK1
 *   ClockDomain_DISPCC_DISPCCMDSSVSYNC
 *   ClockDomain_DISPCC_DISPCCXO
 */
static ClockMuxConfigType ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, { 0,     2,     0,     0,     0xFF }, SRC_IDX_NULL,                                 0                   ,  },   /* Mux[0] = BI_TCXO */
};

/*
 * ClockDomainBSP_DISPCC_DISPCCMDSSMDP
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSMDP
 */
static ClockMuxConfigType ClockDomainBSP_DISPCC_DISPCCMDSSMDP[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, { 0,     2,     0,     0,     0xFF }, SRC_IDX_NULL,                                 0                   ,  },   /* Mux[0] = BI_TCXO */
  {   85714286, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, { 1,     6,     0,     0,     0xFF }, SRC_IDX_DISPCC_DISPCCPLL0,                    0 /* 257.1  */      ,  },   /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  100000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, { 1,     6,     0,     0,     0xFF }, SRC_IDX_DISPCC_DISPCCPLL0,                    1 /* 300.0  */      ,  },   /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  155000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, { 1,     6,     0,     0,     0xFF }, SRC_IDX_DISPCC_DISPCCPLL0,                    2 /* 465.0  */      ,  },   /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  200000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 1,     6,     0,     0,     0xFF }, SRC_IDX_DISPCC_DISPCCPLL0,                    3 /* 600.0  */      ,  },   /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  342000000, RAIL_VOLTAGE_LEVEL_SVS,        { 1,     6,     0,     0,     0xFF }, SRC_IDX_DISPCC_DISPCCPLL0,                    4 /* 1026.0 */      ,  },   /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  402000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     { 1,     6,     0,     0,     0xFF }, SRC_IDX_DISPCC_DISPCCPLL0,                    5 /* 1206.0 */      ,  },   /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  514000000, RAIL_VOLTAGE_LEVEL_NOM,        { 1,     6,     0,     0,     0xFF }, SRC_IDX_DISPCC_DISPCCPLL0,                    6 /* 1542.0 */      ,  },   /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  600000000, RAIL_VOLTAGE_LEVEL_TUR,        { 1,     6,     0,     0,     0xFF }, SRC_IDX_DISPCC_DISPCCPLL0,                    7 /* 1800.0 */      ,  },   /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_DISPCC_DISPCCSLEEP
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCSLEEP
 */
static ClockMuxConfigType ClockDomainBSP_DISPCC_DISPCCSLEEP[] =
{
  {      32000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, { 0,     2,     0,     0,     0xFF }, SRC_IDX_NULL,                                 0                   ,  },   /* Mux[0] = CHIP_SLEEP_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCCONFIGNOC
 *
 * Note: These frequencies are used by domains possibly under DFS control. The
 *       DFS-enable state will be detected during init. If under DFS control,
 *       the domain will dynamically allocate its own BSP array and populate
 *       it with configurations detected from the DFS registers.
 *
 * Used by:
 *   ClockDomain_GCC_GCCCONFIGNOC
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCCONFIGNOC[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 0,     2,     0,     0,     0x00 }, SRC_IDX_NULL,                                 0                   ,  },   /* Mux[0] = BI_TCXO */
  {   37500000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     16,    0,     0,     0x02 }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP118_CLKGEN_ACGC_CLK */
  {   75000000, RAIL_VOLTAGE_LEVEL_NOM,        { 1,     16,    0,     0,     0x04 }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP18_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCMMNOCHFQX
 *
 * Note: These frequencies are used by domains possibly under DFS control. The
 *       DFS-enable state will be detected during init. If under DFS control,
 *       the domain will dynamically allocate its own BSP array and populate
 *       it with configurations detected from the DFS registers.
 *
 * Used by:
 *   ClockDomain_GCC_GCCMMNOCHFQX
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCMMNOCHFQX[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 0,     2,     0,     0,     0x00 }, SRC_IDX_NULL,                                 0                   ,  },   /* Mux[0] = BI_TCXO */
  {  200000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     3,     0,     0,     0x02 }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP102_CLKGEN_ACGC_CLK */
  {  355333333, RAIL_VOLTAGE_LEVEL_SVS,        { 4,     6,     0,     0,     0x03 }, SRC_IDX_GCC_GCCGPLL1,                         0                   ,  },   /* Mux[4] = GCC_GPLL1_OUT_MAIN_PWRGRP6_CLKGEN_ACGC_CLK */
  {  403000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     { 5,     4,     0,     0,     0x04 }, SRC_IDX_GCC_GCCGPLL4,                         0                   ,  },   /* Mux[5] = GCC_GPLL4_OUT_MAIN_PWRGRP5_CLKGEN_ACGC_CLK */
  {  533000000, RAIL_VOLTAGE_LEVEL_NOM,        { 4,     4,     0,     0,     0x05 }, SRC_IDX_GCC_GCCGPLL1,                         0                   ,  },   /* Mux[4] = GCC_GPLL1_OUT_MAIN_PWRGRP6_CLKGEN_ACGC_CLK */
  {  600000000, RAIL_VOLTAGE_LEVEL_TUR,        { 1,     2,     0,     0,     0x06 }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP2_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCQUPV3WRAP0QSPIREF
 *
 * Note: These frequencies are used by domains possibly under DFS control. The
 *       DFS-enable state will be detected during init. If under DFS control,
 *       the domain will dynamically allocate its own BSP array and populate
 *       it with configurations detected from the DFS registers.
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP0QSPIREF
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP0QSPIREF[] =
{
  {    7372800, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     384,   15625, 0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   14745600, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     768,   15625, 0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 0,     2,     0,     0,     0x00 }, SRC_IDX_NULL,                                 0                   ,  },   /* Mux[0] = BI_TCXO */
  {   29491200, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     1536,  15625, 0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   32000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     8,     75,    0x01 }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   48000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     4,     25,    0x02 }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   51200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     64,    375,   0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   64000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     16,    75,    0x03 }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   75000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     8,     0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   80000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     4,     15,    0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   96000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     8,     25,    0x04 }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {  100000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 1,     12,    0,     0,     0x05 }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP8_CLKGEN_ACGC_CLK */
  {  102400000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     128,   375,   0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {  112000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     28,    75,    0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {  117964800, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     6144,  15625, 0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {  120000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 1,     10,    0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP8_CLKGEN_ACGC_CLK */
  {  150000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     4,     0,     0,     0x06 }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {  240000000, RAIL_VOLTAGE_LEVEL_SVS,        { 1,     5,     0,     0,     0x07 }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP8_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCQUPV3WRAP0S0
 *
 * Note: These frequencies are used by domains possibly under DFS control. The
 *       DFS-enable state will be detected during init. If under DFS control,
 *       the domain will dynamically allocate its own BSP array and populate
 *       it with configurations detected from the DFS registers.
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP0S0
 *   ClockDomain_GCC_GCCQUPV3WRAP0S1
 *   ClockDomain_GCC_GCCQUPV3WRAP0S3
 *   ClockDomain_GCC_GCCQUPV3WRAP0S4
 *   ClockDomain_GCC_GCCQUPV3WRAP0S5
 *   ClockDomain_GCC_GCCQUPV3WRAP0S6
 *   ClockDomain_GCC_GCCQUPV3WRAP0S7
 *   ClockDomain_GCC_GCCQUPV3WRAP1S0
 *   ClockDomain_GCC_GCCQUPV3WRAP1S1
 *   ClockDomain_GCC_GCCQUPV3WRAP1S2
 *   ClockDomain_GCC_GCCQUPV3WRAP1S3
 *   ClockDomain_GCC_GCCQUPV3WRAP1S4
 *   ClockDomain_GCC_GCCQUPV3WRAP1S5
 *   ClockDomain_GCC_GCCQUPV3WRAP1S6
 *   ClockDomain_GCC_GCCQUPV3WRAP1S7
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP0S0[] =
{
  {    7372800, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     384,   15625, 0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   14745600, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     768,   15625, 0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 0,     2,     0,     0,     0x00 }, SRC_IDX_NULL,                                 0                   ,  },   /* Mux[0] = BI_TCXO */
  {   48000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     2,     4,     25,    0x02 }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCQUPV3WRAP1IBICTRL0
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP1IBICTRL0
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP1IBICTRL0[] =
{
  {   37500000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     16,    0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP108_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCSDCC2APPS
 *
 * Used by:
 *   ClockDomain_GCC_GCCSDCC2APPS
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCSDCC2APPS[] =
{
  {     400000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 0,     24,    1,     4,     0xFF }, SRC_IDX_NULL,                                 0                   ,  },   /* Mux[0] = BI_TCXO */
  {   25000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     24,    0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP132_CLKGEN_ACGC_CLK */
  {   37500000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     16,    0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP132_CLKGEN_ACGC_CLK */
  {   50000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     12,    0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP132_CLKGEN_ACGC_CLK */
  {  100000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     6,     0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP132_CLKGEN_ACGC_CLK */
  {  202000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     { 2,     8,     0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL9,                         0                   ,  },   /* Mux[2] = GCC_GPLL9_OUT_MAIN */
};

/*
 * ClockDomainBSP_GCC_GCCUFSPHYAXI
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYAXI
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCUFSPHYAXI[] =
{
  {   25000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     24,    0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP105_CLKGEN_ACGC_CLK */
  {  100000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     6,     0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP105_CLKGEN_ACGC_CLK */
  {  201500000, RAIL_VOLTAGE_LEVEL_SVS,        { 5,     8,     0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL4,                         0                   ,  },   /* Mux[5] = GCC_GPLL4_OUT_MAIN_PWRGRP6_CLKGEN_ACGC_CLK */
  {  403000000, RAIL_VOLTAGE_LEVEL_NOM,        { 5,     4,     0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL4,                         0                   ,  },   /* Mux[5] = GCC_GPLL4_OUT_MAIN_PWRGRP6_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCUFSPHYICECORE
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYICECORE
 *   ClockDomain_GCC_GCCUFSPHYUNIPROCORE
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCUFSPHYICECORE[] =
{
  {  100000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     6,     0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP105_CLKGEN_ACGC_CLK */
  {  201500000, RAIL_VOLTAGE_LEVEL_SVS,        { 5,     8,     0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL4,                         0                   ,  },   /* Mux[5] = GCC_GPLL4_OUT_MAIN_PWRGRP6_CLKGEN_ACGC_CLK */
  {  403000000, RAIL_VOLTAGE_LEVEL_NOM,        { 5,     4,     0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL4,                         0                   ,  },   /* Mux[5] = GCC_GPLL4_OUT_MAIN_PWRGRP6_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCUFSPHYPHYAUX
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYPHYAUX
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCUFSPHYPHYAUX[] =
{
  {    9600000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 0,     4,     0,     0,     0xFF }, SRC_IDX_NULL,                                 0                   ,  },   /* Mux[0] = BI_TCXO */
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 0,     2,     0,     0,     0xFF }, SRC_IDX_NULL,                                 0                   ,  },   /* Mux[0] = BI_TCXO */
};

/*
 * ClockDomainBSP_GCC_GCCUSB30PRIMMASTER
 *
 * Used by:
 *   ClockDomain_GCC_GCCUSB30PRIMMASTER
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCUSB30PRIMMASTER[] =
{
  {   66666667, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 6,     9,     0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP112_CLKGEN_ACGC_CLK */
  {  133333333, RAIL_VOLTAGE_LEVEL_SVS,        { 1,     9,     0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP12_CLKGEN_ACGC_CLK */
  {  200000000, RAIL_VOLTAGE_LEVEL_NOM,        { 1,     6,     0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP12_CLKGEN_ACGC_CLK */
  {  240000000, RAIL_VOLTAGE_LEVEL_TUR,        { 1,     5,     0,     0,     0xFF }, SRC_IDX_GCC_GCCGPLL0,                         0                   ,  },   /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP12_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCUSB30PRIMMOCKUTMI
 *
 * Used by:
 *   ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI
 *   ClockDomain_GCC_GCCUSB3PRIMPHYAUX
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCUSB30PRIMMOCKUTMI[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    { 0,     2,     0,     0,     0xFF }, SRC_IDX_NULL,                                 0                   ,  },   /* Mux[0] = BI_TCXO */
};


/*=========================================================================
      Domain Source Maps
==========================================================================*/


/*=========================================================================
      Domain FMAX
==========================================================================*/


/*=========================================================================
      Domains
==========================================================================*/

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSAHB =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSAHB,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSAHB),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_AHB_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSBYTE0 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_BYTE0_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSBYTE1 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_BYTE1_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_DPTX0_AUX_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_DPTX0_LINK_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_DPTX0_PIXEL0_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_DPTX0_PIXEL1_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX1AUX =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_DPTX1_AUX_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_DPTX1_LINK_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL0 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_DPTX1_PIXEL0_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL1 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_DPTX1_PIXEL1_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX2AUX =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_DPTX2_AUX_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_DPTX2_LINK_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL0 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_DPTX2_PIXEL0_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL1 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_DPTX2_PIXEL1_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX3AUX =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_DPTX3_AUX_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_DPTX3_LINK_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX3PIXEL0 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_DPTX3_PIXEL0_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSESC0 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_ESC0_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSESC1 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_ESC1_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSMDP =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSMDP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSMDP),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_MDP_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSPCLK0 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_PCLK0_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSPCLK1 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_PCLK1_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSVSYNC =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_MDSS_VSYNC_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCSLEEP =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCSLEEP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCSLEEP),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_SLEEP_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCXO =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nCGRAddr   = HWIO_ADDR(DISP_CC_XO_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCCONFIGNOC =
{
  .aBSP      = ClockDomainBSP_GCC_GCCCONFIGNOC,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCCONFIGNOC),
  .nCGRAddr   = HWIO_ADDR(GCC_CONFIG_NOC_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCMMNOCHFQX =
{
  .aBSP      = ClockDomainBSP_GCC_GCCMMNOCHFQX,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCMMNOCHFQX),
  .nCGRAddr   = HWIO_ADDR(GCC_MMNOC_HF_QX_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0QSPIREF =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0QSPIREF,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0QSPIREF),
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP0_QSPI_REF_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S0 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP0_S0_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S1 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP0_S1_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S3 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP0_S3_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S4 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP0_S4_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S5 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP0_S5_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S6 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP0_S6_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S7 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP0_S7_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1IBICTRL0 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP1IBICTRL0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP1IBICTRL0),
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP1_IBI_CTRL_0_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S0 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP1_S0_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S1 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP1_S1_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S2 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP1_S2_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S3 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP1_S3_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S4 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP1_S4_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S5 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP1_S5_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S6 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP1_S6_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S7 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nCGRAddr   = HWIO_ADDR(GCC_QUPV3_WRAP1_S7_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCSDCC2APPS =
{
  .aBSP      = ClockDomainBSP_GCC_GCCSDCC2APPS,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCSDCC2APPS),
  .nCGRAddr   = HWIO_ADDR(GCC_SDCC2_APPS_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYAXI =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUFSPHYAXI,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUFSPHYAXI),
  .nCGRAddr   = HWIO_ADDR(GCC_UFS_PHY_AXI_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYICECORE =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUFSPHYICECORE,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUFSPHYICECORE),
  .nCGRAddr   = HWIO_ADDR(GCC_UFS_PHY_ICE_CORE_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYPHYAUX =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUFSPHYPHYAUX,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUFSPHYPHYAUX),
  .nCGRAddr   = HWIO_ADDR(GCC_UFS_PHY_PHY_AUX_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYUNIPROCORE =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUFSPHYICECORE,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUFSPHYICECORE),
  .nCGRAddr   = HWIO_ADDR(GCC_UFS_PHY_UNIPRO_CORE_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCUSB30PRIMMASTER =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUSB30PRIMMASTER,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUSB30PRIMMASTER),
  .nCGRAddr   = HWIO_ADDR(GCC_USB30_PRIM_MASTER_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUSB30PRIMMOCKUTMI,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUSB30PRIMMOCKUTMI),
  .nCGRAddr   = HWIO_ADDR(GCC_USB30_PRIM_MOCK_UTMI_CMD_RCGR),
};

static ClockDomainNodeType ClockDomain_GCC_GCCUSB3PRIMPHYAUX =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUSB30PRIMMOCKUTMI,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUSB30PRIMMOCKUTMI),
  .nCGRAddr   = HWIO_ADDR(GCC_USB3_PRIM_PHY_AUX_CMD_RCGR),
};


static ClockDomainNodeType *aDomains[] =
{
  &ClockDomain_DISPCC_DISPCCMDSSAHB,
  &ClockDomain_DISPCC_DISPCCMDSSBYTE0,
  &ClockDomain_DISPCC_DISPCCMDSSBYTE1,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX1AUX,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL0,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL1,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX2AUX,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL0,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL1,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX3AUX,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX3PIXEL0,
  &ClockDomain_DISPCC_DISPCCMDSSESC0,
  &ClockDomain_DISPCC_DISPCCMDSSESC1,
  &ClockDomain_DISPCC_DISPCCMDSSMDP,
  &ClockDomain_DISPCC_DISPCCMDSSPCLK0,
  &ClockDomain_DISPCC_DISPCCMDSSPCLK1,
  &ClockDomain_DISPCC_DISPCCMDSSVSYNC,
  &ClockDomain_DISPCC_DISPCCSLEEP,
  &ClockDomain_DISPCC_DISPCCXO,
  &ClockDomain_GCC_GCCCONFIGNOC,
  &ClockDomain_GCC_GCCMMNOCHFQX,
  &ClockDomain_GCC_GCCQUPV3WRAP0QSPIREF,
  &ClockDomain_GCC_GCCQUPV3WRAP0S0,
  &ClockDomain_GCC_GCCQUPV3WRAP0S1,
  &ClockDomain_GCC_GCCQUPV3WRAP0S3,
  &ClockDomain_GCC_GCCQUPV3WRAP0S4,
  &ClockDomain_GCC_GCCQUPV3WRAP0S5,
  &ClockDomain_GCC_GCCQUPV3WRAP0S6,
  &ClockDomain_GCC_GCCQUPV3WRAP0S7,
  &ClockDomain_GCC_GCCQUPV3WRAP1IBICTRL0,
  &ClockDomain_GCC_GCCQUPV3WRAP1S0,
  &ClockDomain_GCC_GCCQUPV3WRAP1S1,
  &ClockDomain_GCC_GCCQUPV3WRAP1S2,
  &ClockDomain_GCC_GCCQUPV3WRAP1S3,
  &ClockDomain_GCC_GCCQUPV3WRAP1S4,
  &ClockDomain_GCC_GCCQUPV3WRAP1S5,
  &ClockDomain_GCC_GCCQUPV3WRAP1S6,
  &ClockDomain_GCC_GCCQUPV3WRAP1S7,
  &ClockDomain_GCC_GCCSDCC2APPS,
  &ClockDomain_GCC_GCCUFSPHYAXI,
  &ClockDomain_GCC_GCCUFSPHYICECORE,
  &ClockDomain_GCC_GCCUFSPHYPHYAUX,
  &ClockDomain_GCC_GCCUFSPHYUNIPROCORE,
  &ClockDomain_GCC_GCCUSB30PRIMMASTER,
  &ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI,
  &ClockDomain_GCC_GCCUSB3PRIMPHYAUX,
};


/*=========================================================================
      Clocks
==========================================================================*/

static ClockNodeType aClocks[] =
{
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSAHB                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_ahb1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSAHB,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_AHB1_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_ahb_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSAHB,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_AHB_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_non_gdsc_ahb_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSAHB,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_NON_GDSC_AHB_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_rscc_ahb_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSAHB,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_RSCC_AHB_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSBYTE0                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_byte0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSBYTE0,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_BYTE0_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_byte0_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSBYTE0,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_BYTE0_INTF_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSBYTE1                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_byte1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSBYTE1,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_BYTE1_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_byte1_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSBYTE1,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_BYTE1_INTF_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx0_aux_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX0_AUX_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx0_crypto_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX0_CRYPTO_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_dptx0_link_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX0_LINK_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_dptx0_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX0_LINK_INTF_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_dptx0_usb_router_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX0_USB_ROUTER_LINK_INTF_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_crypto_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_SPDM_DP_CRYPTO_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx0_pixel0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX0_PIXEL0_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_pixel_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_SPDM_DP_PIXEL_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx0_pixel1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX0_PIXEL1_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_pixel1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_SPDM_DP_PIXEL1_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX1AUX                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx1_aux_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1AUX,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX1_AUX_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx1_crypto_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX1_CRYPTO_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_dptx1_link_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX1_LINK_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_dptx1_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX1_LINK_INTF_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_dptx1_usb_router_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX1_USB_ROUTER_LINK_INTF_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL0                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx1_pixel0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL0,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX1_PIXEL0_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL1                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx1_pixel1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL1,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX1_PIXEL1_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX2AUX                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx2_aux_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2AUX,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX2_AUX_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx2_crypto_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX2_CRYPTO_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_dptx2_link_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX2_LINK_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_dptx2_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX2_LINK_INTF_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL0                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx2_pixel0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL0,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX2_PIXEL0_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL1                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx2_pixel1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL1,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX2_PIXEL1_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX3AUX                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx3_aux_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX3AUX,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX3_AUX_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx3_crypto_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX3_CRYPTO_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_dptx3_link_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX3_LINK_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_dptx3_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX3_LINK_INTF_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX3PIXEL0                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx3_pixel0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX3PIXEL0,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_DPTX3_PIXEL0_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSESC0                                     */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_esc0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSESC0,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_ESC0_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSESC1                                     */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_esc1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSESC1,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_ESC1_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSMDP                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_mdp1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSMDP,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_MDP1_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_mdp_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSMDP,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_MDP_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_mdp_lut1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSMDP,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_MDP_LUT1_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_mdp_lut_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSMDP,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_MDP_LUT_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_spdm_mdp_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSMDP,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_SPDM_MDP_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSPCLK0                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_pclk0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSPCLK0,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_PCLK0_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_spdm_pclk0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSPCLK0,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_SPDM_PCLK0_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSPCLK1                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_pclk1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSPCLK1,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_PCLK1_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_spdm_pclk1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSPCLK1,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_SPDM_PCLK1_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSVSYNC                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_rscc_vsync_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSVSYNC,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_RSCC_VSYNC_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_vsync1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSVSYNC,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_VSYNC1_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_vsync_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSVSYNC,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_VSYNC_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCPLLTESTMUX                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_pll_test_clk",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_PLL_TEST_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCSLEEP                                        */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_sleep_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCSLEEP,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_SLEEP_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCXO                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_accu_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCXO,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_ACCU_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_xo_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCXO,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_XO_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_debug_clk",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_DEBUG_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "disp_cc_mdss_spdm_debug_clk",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(DISP_CC_MDSS_SPDM_DEBUG_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_gpll0_ufs_phy_rx_symbol_0_clk",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_GPLL0_UFS_PHY_RX_SYMBOL_0_ACGCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_gpll0_ufs_phy_rx_symbol_1_clk",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_GPLL0_UFS_PHY_RX_SYMBOL_1_ACGCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_gpll0_ufs_phy_tx_symbol_0_clk",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_GPLL0_UFS_PHY_TX_SYMBOL_0_ACGCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "tcsr_ufs_phy_clkref_en",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(TCSR_UFS_PHY_CLKREF_EN__UFS_PHY_ENABLE),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "tcsr_usb3_clkref_en",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(TCSR_USB3_CLKREF_EN__USB3_ENABLE),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCCNOCPERIPH                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_sdcc2_ahb_clk",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_SDCC2_AHB_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCCONFIGNOC                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_camera_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_CAMERA_AHB_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_disp_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_DISP_AHB_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_qmip_camera_nrt_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QMIP_CAMERA_NRT_AHB_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_qmip_camera_rt_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QMIP_CAMERA_RT_AHB_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_qmip_video_cv_cpu_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QMIP_VIDEO_CV_CPU_AHB_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_qmip_video_cvp_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QMIP_VIDEO_CVP_AHB_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_qmip_video_v_cpu_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QMIP_VIDEO_V_CPU_AHB_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_qmip_video_vcodec_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QMIP_VIDEO_VCODEC_AHB_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_qupv3_wrap_1_ibi_2_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP_1_IBI_2_AHB_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x2000000},
  },
  {
    .szName    = "gcc_qupv3_wrap_1_ibi_3_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP_1_IBI_3_AHB_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x4000000},
  },
  {
    .szName    = "gcc_ufs_phy_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_AHB_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_video_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_VIDEO_AHB_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCMMNOCHFQX                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_camera_hf_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCMMNOCHFQX,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_CAMERA_HF_AXI_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_disp_hf_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCMMNOCHFQX,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_DISP_HF_AXI_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCMMNOCSFQX                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_camera_sf_axi_clk",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_CAMERA_SF_AXI_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_video_axi0_clk",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_VIDEO_AXI0_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_video_axi1_clk",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_VIDEO_AXI1_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQDSSATBA                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_mmnoc_hf_at_clk",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_MMNOC_HF_AT_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_sdcc2_at_clk",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_SDCC2_AT_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0QSPIREF                                  */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_qspi_ref_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0QSPIREF,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP0_QSPI_REF_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x20000000},
  },
  {
    .szName    = "gcc_qupv3_wrap0_s2_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0QSPIREF,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP0_S2_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x1000000},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S0                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s0_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S0,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP0_S0_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x400000},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S1                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s1_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S1,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP0_S1_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x800000},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S3                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s3_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S3,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP0_S3_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x2000000},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S4                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s4_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S4,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP0_S4_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x4000000},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S5                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s5_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S5,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP0_S5_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x8000000},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S6                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s6_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S6,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP0_S6_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x10000000},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S7                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s7_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S7,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP0_S7_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x10000},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1IBICTRL0                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_ibi_ctrl_2_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1IBICTRL0,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_IBI_CTRL_2_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x8000000},
  },
  {
    .szName    = "gcc_qupv3_wrap1_ibi_ctrl_3_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1IBICTRL0,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_IBI_CTRL_3_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x10000000},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S0                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s0_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S0,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_S0_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x10},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S1                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s1_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S1,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_S1_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x20},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S2                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s2_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S2,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_S2_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x40},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S3                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s3_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S3,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_S3_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x80},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S4                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s4_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S4,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_S4_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x100},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S5                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s5_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S5,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_S5_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x200},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S6                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s6_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S6,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_S6_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x400},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S7                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s7_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S7,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_QUPV3_WRAP1_S7_CBCR),
    .mHWVotable  = {HWIO_ADDR(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x20000},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCSDCC2APPS                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_sdcc2_apps_clk",
    .pDomain   = &ClockDomain_GCC_GCCSDCC2APPS,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_SDCC2_APPS_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCSLEEP                                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_usb30_prim_sleep_clk",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_USB30_PRIM_SLEEP_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYAXI                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_aggre_ufs_phy_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYAXI,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_AGGRE_UFS_PHY_AXI_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_ufs_phy_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYAXI,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_AXI_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYICECORE                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_ice_core_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYICECORE,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_ICE_CORE_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYPHYAUX                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_phy_aux_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYPHYAUX,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_PHY_AUX_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYRXSYMBOL0                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_rx_symbol_0_clk",
    .nFlags    = CLOCK_FLAG_NO_POLL_AFTER_ENABLE,
    .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_RX_SYMBOL_0_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYRXSYMBOL1                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_rx_symbol_1_clk",
    .nFlags    = CLOCK_FLAG_NO_POLL_AFTER_ENABLE,
    .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_RX_SYMBOL_1_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYTXSYMBOL0                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_tx_symbol_0_clk",
    .nFlags    = CLOCK_FLAG_NO_POLL_AFTER_ENABLE,
    .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_TX_SYMBOL_0_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYUNIPROCORE                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_unipro_core_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYUNIPROCORE,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_UNIPRO_CORE_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUSB30PRIMMASTER                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_aggre_usb3_prim_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB30PRIMMASTER,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_AGGRE_USB3_PRIM_AXI_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_usb30_prim_master_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB30PRIMMASTER,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_USB30_PRIM_MASTER_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI                                  */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_usb30_prim_mock_utmi_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_USB30_PRIM_MOCK_UTMI_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUSB3PRIMPHYAUX                                     */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_usb3_prim_phy_aux_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB3PRIMPHYAUX,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_USB3_PRIM_PHY_AUX_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_usb3_prim_phy_com_aux_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB3PRIMPHYAUX,
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_USB3_PRIM_PHY_COM_AUX_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUSB3PRIMPHYPIPE                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_usb3_prim_phy_pipe_clk",
    .nFlags    = CLOCK_FLAG_NO_POLL_AFTER_ENABLE,
    .nBranchAddr = HWIO_ADDR(GCC_USB3_PRIM_PHY_PIPE_CBCR),
    .mHWVotable  = {0, 0},
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCXO                                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_camera_hf_xo_clk",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_CAMERA_HF_XO_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_camera_sf_xo_clk",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_CAMERA_SF_XO_CBCR),
    .mHWVotable  = {0, 0},
  },
  {
    .szName    = "gcc_video_xo_clk",
    .nFlags    = 0x0,
    .nBranchAddr = HWIO_ADDR(GCC_VIDEO_XO_CBCR),
    .mHWVotable  = {0, 0},
  },
};


/*=========================================================================
      Power Domains
==========================================================================*/

static ClockPowerDomainNodeType aPowerDomains[] =
{
  {
    .szName         = "disp_cc_mdss_core_gdsc",
    .nGDSCRAddr     = HWIO_ADDR(DISP_CC_MDSS_CORE_GDSCR),
  },
  {
    .szName         = "disp_cc_mdss_core_int2_gdsc",
    .nGDSCRAddr     = HWIO_ADDR(DISP_CC_MDSS_CORE_INT2_GDSCR),
  },
  {
    .szName         = "gcc_ufs_mem_phy_gdsc",
    .nGDSCRAddr     = HWIO_ADDR(GCC_UFS_MEM_PHY_GDSCR),
  },
  {
    .szName         = "gcc_ufs_phy_gdsc",
    .nGDSCRAddr     = HWIO_ADDR(GCC_UFS_PHY_GDSCR),
  },
  {
    .szName         = "gcc_usb30_prim_gdsc",
    .nGDSCRAddr     = HWIO_ADDR(GCC_USB30_PRIM_GDSCR),
  },
};


/*=========================================================================
      Functional Groups
==========================================================================*/

static ClockGroupType aClockGroups[] =
{
  {
    .szName = "sdcc2",
    .aClocks = (ClockNodeType[]){
      {
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_SDCC2_AHB_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCSDCC2APPS,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_SDCC2_APPS_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_SDCC2_AT_CBCR),
        .mHWVotable  = {0, 0},
      },
    },
    .nClocks = 3,
    .aDomains = (ClockDomainNodeType*[]){
      &ClockDomain_GCC_GCCSDCC2APPS,
    },
    .nDomains = 1,
    .nResetAddr = HWIO_ADDR(GCC_SDCC2_BCR),
  },
  {
    .szName = "ufs_phy",
    .aClocks = (ClockNodeType[]){
      {
        .pDomain     = &ClockDomain_GCC_GCCUFSPHYAXI,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_AGGRE_UFS_PHY_AXI_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCCONFIGNOC,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_AHB_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCUFSPHYAXI,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_AXI_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCUFSPHYICECORE,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_ICE_CORE_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCUFSPHYPHYAUX,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_PHY_AUX_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = CLOCK_FLAG_NO_POLL_AFTER_ENABLE,
        .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_RX_SYMBOL_0_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = CLOCK_FLAG_NO_POLL_AFTER_ENABLE,
        .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_RX_SYMBOL_1_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = CLOCK_FLAG_NO_POLL_AFTER_ENABLE,
        .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_TX_SYMBOL_0_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCUFSPHYUNIPROCORE,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_UFS_PHY_UNIPRO_CORE_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(TCSR_UFS_PHY_CLKREF_EN__UFS_PHY_ENABLE),
        .mHWVotable  = {0, 0},
      },
    },
    .nClocks = 10,
    .aDomains = (ClockDomainNodeType*[]){
      &ClockDomain_GCC_GCCUFSPHYAXI,
      &ClockDomain_GCC_GCCUFSPHYICECORE,
      &ClockDomain_GCC_GCCUFSPHYPHYAUX,
      &ClockDomain_GCC_GCCUFSPHYUNIPROCORE,
    },
    .nDomains = 4,
    .aPowerDomains = (uint32_t[]){
      HWIO_ADDR(GCC_UFS_MEM_PHY_GDSCR),
      HWIO_ADDR(GCC_UFS_PHY_GDSCR),
    },
    .nPowerDomains = 2,
    .nResetAddr = HWIO_ADDR(GCC_UFS_PHY_BCR),
  },
  {
    .szName = "usb30_prim",
    .aClocks = (ClockNodeType[]){
      {
        .pDomain     = &ClockDomain_GCC_GCCUSB30PRIMMASTER,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_AGGRE_USB3_PRIM_AXI_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCUSB30PRIMMASTER,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_USB30_PRIM_MASTER_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_USB30_PRIM_MOCK_UTMI_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_USB30_PRIM_SLEEP_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCUSB3PRIMPHYAUX,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_USB3_PRIM_PHY_AUX_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .pDomain     = &ClockDomain_GCC_GCCUSB3PRIMPHYAUX,
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(GCC_USB3_PRIM_PHY_COM_AUX_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = CLOCK_FLAG_NO_POLL_AFTER_ENABLE,
        .nBranchAddr = HWIO_ADDR(GCC_USB3_PRIM_PHY_PIPE_CBCR),
        .mHWVotable  = {0, 0},
      },
      {
        .nFlags      = 0x0,
        .nBranchAddr = HWIO_ADDR(TCSR_USB3_CLKREF_EN__USB3_ENABLE),
        .mHWVotable  = {0, 0},
      },
    },
    .nClocks = 8,
    .aDomains = (ClockDomainNodeType*[]){
      &ClockDomain_GCC_GCCUSB30PRIMMASTER,
      &ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI,
      &ClockDomain_GCC_GCCUSB3PRIMPHYAUX,
    },
    .nDomains = 3,
    .aPowerDomains = (uint32_t[]){
      HWIO_ADDR(GCC_USB30_PRIM_GDSCR),
    },
    .nPowerDomains = 1,
    .nResetAddr = HWIO_ADDR(GCC_USB30_PRIM_BCR),
  },
};

/*=========================================================================
      Main BSP
==========================================================================*/

ClockBSPType ClockBSP =
{
  .aClocks           = aClocks,
  .nNumClocks        = SIZEOF_ARRAY(aClocks),
  .aDomains          = aDomains,
  .nNumDomains       = SIZEOF_ARRAY(aDomains),
  .aSources          = aSources,
  .nNumSources       = SIZEOF_ARRAY(aSources),
  .aDividers         = aDividers,
  .nNumDividers      = SIZEOF_ARRAY(aDividers),
  .aPowerDomains     = aPowerDomains,
  .nNumPowerDomains  = SIZEOF_ARRAY(aPowerDomains),
  .SafeMuxConfig     = { 0, 2, 0, 0 },
  .aClockGroups      = aClockGroups,
  .nNumClockGroups   = SIZEOF_ARRAY(aClockGroups),
};

