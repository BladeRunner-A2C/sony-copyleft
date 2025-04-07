/*
==============================================================================

FILE:         ClockBSP.c

DESCRIPTION:
  This file contains the clock driver BSP data.

  Auto-generated from the following IPCat controller releases:

    SM6xxxv1 (milos_1.0):
      PLL_HSR   : None
      APSS_CC   : milos_apss_cc_milos_apss_1.0_p3q1r179.7365_fp3 [milos_apss_cc.r1]
      CAM_CC    : milos_cam_cc_z_cam_cc_milos_1.0_p3q2r9_fp7 [milos_cam_cc.r0]
      DISP_CC   : milos_disp_cc_z_disp_cc_milos_1.0_p3q2r17_fp6 [milos_disp_cc.r0]
      GCC       : milos_gcc_z_milos_clk_ctl_1.0_p3q2r14_fp10 [milos_gcc.r12]
      GPU_CC    : milos_gpu_cc_z_gpu_cc_milos_1.0_p3q2r10_fp5 [milos_gpu_cc.r2]
      GX_CLKCTL : milos_gx_clkctl_d100_milos_p3q1r7_fp5 [milos_gx_clkctl.r0]
      TCSR_CC   : None
      VIDEO_CC  : milos_video_cc_z_video_cc_milos_1.0_p3q2r17_fp6 [milos_video_cc.r1]


  Generated using the following clockdrivergen settings:

CLOCKDRIVERGEN_CONFIG = \
{'db_override': {'GCC': {'cbc': {'gcc_gpu_memnoc_gfx_clk_en': {'d_registers': {'cbcr_name': 'GCC_GPU_MEMNOC_GFX_CLK_EN'},
                                                               'd_sw_owner': {'APCS': 'RW'},
                                                               'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_aggre_noc_mmu_pcie_qtb_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_AGGRE_NOC_MMU_PCIE_QTB_CLK'},
                                                                               'd_sw_owner': {'APCS': 'RW'},
                                                                               'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_aggre_noc_mmu_qtb1_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_AGGRE_NOC_MMU_QTB1_CLK'},
                                                                           'd_sw_owner': {'APCS': 'RW'},
                                                                           'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_aggre_noc_mmu_qtb2_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_AGGRE_NOC_MMU_QTB2_CLK'},
                                                                           'd_sw_owner': {'APCS': 'RW'},
                                                                           'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_all_smmu_mmu_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_ALL_SMMU_MMU_CLK'},
                                                                     'd_sw_owner': {'APCS': 'RW'},
                                                                     'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_gpu_smmu_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_GPU_SMMU_CLK'},
                                                                 'd_sw_owner': {'APCS': 'RW'},
                                                                 'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_lpass_qtb_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_LPASS_QTB_CLK'},
                                                                  'd_sw_owner': {'APCS': 'RW'},
                                                                  'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_mmnoc_mmu_qtb_hf01_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_CLK'},
                                                                           'd_sw_owner': {'APCS': 'RW'},
                                                                           'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_mmnoc_mmu_qtb_hf23_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_CLK'},
                                                                           'd_sw_owner': {'APCS': 'RW'},
                                                                           'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_mmnoc_mmu_qtb_sf_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_CLK'},
                                                                         'd_sw_owner': {'APCS': 'RW'},
                                                                         'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_mmu_tcu_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_MMU_TCU_CLK'},
                                                                'd_sw_owner': {'APCS': 'RW'},
                                                                'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_turing_mmu_qtb0_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_TURING_MMU_QTB0_CLK'},
                                                                        'd_sw_owner': {'APCS': 'RW'},
                                                                        'l_master': ['bi_tcxo']}},
                         'sm_gdsc': {'gcc_hlos1_vote_aggre_noc_mmu_pcie_qtb_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_AGGRE_NOC_MMU_PCIE_QTB_GDS'},
                                                                                   'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_aggre_noc_mmu_qtb1_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_AGGRE_NOC_MMU_QTB1_GDS'},
                                                                               'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_aggre_noc_mmu_qtb2_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_AGGRE_NOC_MMU_QTB2_GDS'},
                                                                               'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_all_smmu_mmu_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_ALL_SMMU_MMU_GDS'},
                                                                         'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_gpu_smmu_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_GPU_SMMU_GDS'},
                                                                     'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_lpass_qtb_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_LPASS_QTB_GDS'},
                                                                      'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_mmnoc_mmu_qtb_hf01_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_GDS'},
                                                                               'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_mmnoc_mmu_qtb_hf23_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_GDS'},
                                                                               'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_mmnoc_mmu_qtb_sf_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_GDS'},
                                                                             'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_mmu_tcu_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_MMU_TCU_GDS'},
                                                                    'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_turing_mmu_qtb0_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_TURING_MMU_QTB0_GDS'},
                                                                            'd_sw_owner': {'APCS': 'RW'}}}}},
 'filter_warning': 'sw',
 'generators': [{'options': {'clock_flags': {},
                             'clock_flags_hal': {'gcc_qupv3_wrap0_s0_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap0_s1_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap0_s2_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap0_s3_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap0_s4_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap0_s5_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap0_s6_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap1_s0_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap1_s1_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap1_s2_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap1_s3_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap1_s4_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap1_s5_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap1_s6_clk_src': ['DOMAIN_HW_CLK_CONTROL']},
                             'driver_flags': ['LOG_CLOCK_FREQ_CHANGE',
                                              'LOG_SOURCE_STATE_CHANGE'],
                             'env': ['apcs', 'gpuss', 'UEFI'],
                             'hal_ctl_structs': {'gx_clkctl_gx_gdsc': 'HAL_clk_GPUGxPowerDomainControl'},
                             'include_divider': ['.*'],
                             'include_file': {'HALclkPLLSettings.h': False},
                             'include_fmax': ['.*'],
                             'include_source_map': ['.*'],
                             'map_bases': True,
                             'multi_rail': True,
                             'npa_rename': {'/vcs/mxc': '/vcs/vdd_mxc',
                                            '/vcs/vdd_cam_cx': '/vcs/vdd_mm',
                                            '/vcs/vdd_gfx': '/vcs/vdd_gx',
                                            '/vcs/vdd_mxa': '/vcs/vdd_mx'},
                             'rename': {'gcc_pcie_rscc_cfg_ahb_clk': 'gcc_pcie_rscc_ahb_clk'},
                             'standalone_bcrs': ['.*pcie.*', '.*usb.*']},
                 'output_dir': 'milos_output_dir',
                 'type': 'dalclock'}],
 'target': ['milos']}

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

#include "Library/ClockCoreLib/inc/ClockBSP.h"
#include "HALclkHWIO.h"
#include "HALhwio.h"


/*=========================================================================
      Externs
==========================================================================*/

extern HAL_clk_ClockControlType           HAL_clk_GenericClockControl;
extern HAL_clk_ClockDomainControlType     HAL_clk_GenericDomainControl;
extern HAL_clk_ClockDomainControlType     HAL_clk_GenericDomainMuxControl;
extern HAL_clk_DividerControlType         HAL_clk_GenericDividerControl;
extern HAL_clk_PowerDomainControlType     HAL_clk_GenericPowerDomainControl;
extern HAL_clk_SourceControlType          HAL_clk_LucidolePLLControl;
extern HAL_clk_SourceControlType          HAL_clk_RivianolePLLControl;

/*
 * Debug mux control structures.
 */
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlAPSSCC_milos;
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlCAMCC_milos;
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlDISPCC_milos;
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlGCC_milos;
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlGPUCC_milos;
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlGXCLKCTL_milos;
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlVIDEOCC_milos;

/*
 * Custom control structures.
 */
extern HAL_clk_PowerDomainControlType     HAL_clk_GPUGxPowerDomainControl;


/*=========================================================================
      Data Declarations
==========================================================================*/


/*=========================================================================
      Bases
==========================================================================*/

uintptr_t HAL_clk_nHWIOBaseAPSSHM;
uintptr_t HAL_clk_nHWIOBaseCAMERASS;
uintptr_t HAL_clk_nHWIOBaseCLKCTL;
uintptr_t HAL_clk_nHWIOBaseCORETOPCSR;
uintptr_t HAL_clk_nHWIOBaseGFX;
uintptr_t HAL_clk_nHWIOBaseIRIS;
uintptr_t HAL_clk_nHWIOBaseMDSS;

static ClockBaseType aBases[] =
{
  { APSS_HM_BASE_PHYS,        APSS_HM_BASE_SIZE,        &HAL_clk_nHWIOBaseAPSSHM       },
  { CAMERA_SS_BASE_PHYS,      CAMERA_SS_BASE_SIZE,      &HAL_clk_nHWIOBaseCAMERASS     },
  { CLK_CTL_BASE_PHYS,        CLK_CTL_BASE_SIZE,        &HAL_clk_nHWIOBaseCLKCTL       },
  { CORE_TOP_CSR_BASE_PHYS,   CORE_TOP_CSR_BASE_SIZE,   &HAL_clk_nHWIOBaseCORETOPCSR   },
  { GFX_BASE_PHYS,            GFX_BASE_SIZE,            &HAL_clk_nHWIOBaseGFX          },
  { IRIS_BASE_PHYS,           IRIS_BASE_SIZE,           &HAL_clk_nHWIOBaseIRIS         },
  { MDSS_BASE_PHYS,           MDSS_BASE_SIZE,           &HAL_clk_nHWIOBaseMDSS         },
};

/*=========================================================================
      Voltage Rails
==========================================================================*/

enum
{
  RAIL_IDX_VDD_CX,
  RAIL_IDX_VDD_GFX,
  RAIL_IDX_VDD_MM,
  RAIL_IDX_VDD_MX,
};

#define RAIL_VDD_CX          (1 << RAIL_IDX_VDD_CX)
#define RAIL_VDD_GFX         (1 << RAIL_IDX_VDD_GFX)
#define RAIL_VDD_MM          (1 << RAIL_IDX_VDD_MM)
#define RAIL_VDD_MX          (1 << RAIL_IDX_VDD_MX)

static ClockRailType ClockRail_VDDCX =
{
  .szName = "/vcs/vdd_cx",
};

static ClockRailType ClockRail_VDDGFX =
{
  .szName = "/vcs/vdd_gx",
};

static ClockRailType ClockRail_VDDMM =
{
  .szName = "/vcs/vdd_mm",
};

static ClockRailType ClockRail_VDDMX =
{
  .szName = "/vcs/vdd_mx",
};

static ClockRailType *aRails[] =
{
  [RAIL_IDX_VDD_CX]       = &ClockRail_VDDCX,
  [RAIL_IDX_VDD_GFX]      = &ClockRail_VDDGFX,
  [RAIL_IDX_VDD_MM]       = &ClockRail_VDDMM,
  [RAIL_IDX_VDD_MX]       = &ClockRail_VDDMX,
};

/*=========================================================================
      Debug Muxes
==========================================================================*/

static ClockDebugMuxType ClockDebugMux_GCC =
{
  .szName       = "gcc",
  .nUniqueId    = 0x53CF8DFF,
  .nDivider     = 2,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlGCC_milos,
  },
};

static ClockDebugMuxInputDivType aMuxInputDividers_APSSCC[] =
{
  { 1, 4 },
  { 2, 4 },
  { 3, 8 },
  { 4, 8 },
  { 5, 4 },
  { 6, 4 },
  { 7, 8 },
  { 8, 8 },
  { CLOCK_DEBUG_MUX_INPUT_DIV_END },
};

static ClockDebugMuxType ClockDebugMux_APSSCC =
{
  .szName       = "apss_cc",
  .nUniqueId    = 0xD2777925,
  .pParent      = &ClockDebugMux_GCC,
  .nParentSel   = 317,
  .anInputDivs  = aMuxInputDividers_APSSCC,
  .nDivider     = 4,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlAPSSCC_milos,
  },
};

static ClockDebugMuxType ClockDebugMux_CAMCC =
{
  .szName       = "cam_cc",
  .nUniqueId    = 0xCEB85AEC,
  .pParent      = &ClockDebugMux_GCC,
  .nParentSel   = 135,
  .nDivider     = 2,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlCAMCC_milos,
  },
};

static ClockDebugMuxType ClockDebugMux_DISPCC =
{
  .szName       = "disp_cc",
  .nUniqueId    = 0x3E02FDA9,
  .pParent      = &ClockDebugMux_GCC,
  .nParentSel   = 140,
  .nDivider     = 4,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlDISPCC_milos,
  },
};

static ClockDebugMuxType ClockDebugMux_GPUCC =
{
  .szName       = "gpu_cc",
  .nUniqueId    = 0x89008681,
  .pParent      = &ClockDebugMux_GCC,
  .nParentSel   = 391,
  .nDivider     = 2,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlGPUCC_milos,
  },
};

static ClockDebugMuxType ClockDebugMux_VIDEOCC =
{
  .szName       = "video_cc",
  .nUniqueId    = 0xE8021679,
  .pParent      = &ClockDebugMux_GCC,
  .nParentSel   = 149,
  .nDivider     = 3,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlVIDEOCC_milos,
  },
};

static ClockDebugMuxType ClockDebugMux_GXCLKCTL =
{
  .szName       = "gx_clkctl",
  .nUniqueId    = 0xA858A01C,
  .pParent      = &ClockDebugMux_GPUCC,
  .nParentSel   = 11,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlGXCLKCTL_milos,
  },
};

static ClockDebugMuxType *aDebugMuxes[] =
{
  &ClockDebugMux_APSSCC,
  &ClockDebugMux_CAMCC,
  &ClockDebugMux_DISPCC,
  &ClockDebugMux_GCC,
  &ClockDebugMux_GPUCC,
  &ClockDebugMux_GXCLKCTL,
  &ClockDebugMux_VIDEOCC,
};


/*=========================================================================
      Primary Sources
==========================================================================*/

static ClockSourceNodeType ClockSource_XO =
{
  .szName    = "/pmic/client/xo",
  .nFlags    = 0x0,
};


/*=========================================================================
      Source Register Settings
==========================================================================*/

/*
 * PLL HSR not yet available on IPCAT.
 */

/*=========================================================================
      Source BSP
==========================================================================*/

/*
 * ClockSourceBSP_CAMCC_CAMCCPLL0
 *
 * Used by:
 *   ClockSource_CAMCC_CAMCCPLL0
 */
static const ClockSourceFreqConfigType ClockSourceBSP_CAMCC_CAMCCPLL0[] =
{
  { 1200000000, &ClockSource_XO, { 0, 0, 1, 62,  0x00008000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2, .Lucidole.nOdd = 3} }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};
static const ClockSourceFreqConfigType ClockSourceBSPCal_CAMCC_CAMCCPLL0[] =
{
  { 1305600000, &ClockSource_XO, { 0, 0, 1, 68,  0x00000000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_NOM,       },
};

/*
 * ClockSourceBSP_CAMCC_CAMCCPLL1
 *
 * Used by:
 *   ClockSource_CAMCC_CAMCCPLL1
 */
static const ClockSourceFreqConfigType ClockSourceBSP_CAMCC_CAMCCPLL1[] =
{
  {  600000000, &ClockSource_XO, { 0, 0, 1, 31,  0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1,},
  {  820000000, &ClockSource_XO, { 0, 0, 1, 42,  0x0000B555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS,       },
  {  920000000, &ClockSource_XO, { 0, 0, 1, 47,  0x0000EAAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1200000000, &ClockSource_XO, { 0, 0, 1, 62,  0x00008000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1400000000, &ClockSource_XO, { 0, 0, 1, 72,  0x0000EAAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};

/*
 * ClockSourceBSP_CAMCC_CAMCCPLL2
 *
 * Used by:
 *   ClockSource_CAMCC_CAMCCPLL2
 */
static const ClockSourceFreqConfigType ClockSourceBSP_CAMCC_CAMCCPLL2[] =
{
  {  960000000, &ClockSource_XO, { 0, 0, 1, 50,  0x00000000, HAL_CLK_PLL_FRAC_MODE_UNKNOWN, {.Rivianole.nEven = 2}       }, RAIL_VOLTAGE_LEVEL_SVS,       },
};

/*
 * ClockSourceBSP_CAMCC_CAMCCPLL3
 *
 * Used by:
 *   ClockSource_CAMCC_CAMCCPLL3
 */
static const ClockSourceFreqConfigType ClockSourceBSP_CAMCC_CAMCCPLL3[] =
{
  {  600000000, &ClockSource_XO, { 0, 0, 1, 31,  0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1,},
  {  820000000, &ClockSource_XO, { 0, 0, 1, 42,  0x0000B555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1040000000, &ClockSource_XO, { 0, 0, 1, 54,  0x00002AAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1290000000, &ClockSource_XO, { 0, 0, 1, 67,  0x00003000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1400000000, &ClockSource_XO, { 0, 0, 1, 72,  0x0000EAAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};

/*
 * ClockSourceBSP_CAMCC_CAMCCPLL4
 *
 * Used by:
 *   ClockSource_CAMCC_CAMCCPLL4
 *   ClockSource_CAMCC_CAMCCPLL5
 *   ClockSource_CAMCC_CAMCCPLL6
 */
static const ClockSourceFreqConfigType ClockSourceBSP_CAMCC_CAMCCPLL4[] =
{
  {  700000000, &ClockSource_XO, { 0, 0, 1, 36,  0x00007555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1140000000, &ClockSource_XO, { 0, 0, 1, 59,  0x00006000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1200000000, &ClockSource_XO, { 0, 0, 1, 62,  0x00008000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1450000000, &ClockSource_XO, { 0, 0, 1, 75,  0x00008555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};

/*
 * ClockSourceBSP_DISPCC_DISPCCPLL0
 *
 * Used by:
 *   ClockSource_DISPCC_DISPCCPLL0
 */
static const ClockSourceFreqConfigType ClockSourceBSP_DISPCC_DISPCCPLL0[] =
{
  {  600000000, &ClockSource_XO, { 0, 0, 1, 31,  0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1,},
  { 1026000000, &ClockSource_XO, { 0, 0, 1, 53,  0x00007000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1206000000, &ClockSource_XO, { 0, 0, 1, 62,  0x0000D000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1605000000, &ClockSource_XO, { 0, 0, 1, 83,  0x00009800, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_NOM,       },
  { 1800000000, &ClockSource_XO, { 0, 0, 1, 93,  0x0000C000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_NOM,       },
  { 1890000000, &ClockSource_XO, { 0, 0, 1, 98,  0x00007000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_NOM,       },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL0
 *
 * Used by:
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL0[] =
{
  {  600000000, &ClockSource_XO, { 0, 0, 1, 31,  0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1,},
};

/*
 * ClockSourceBSP_GCC_GCCGPLL4
 *
 * Used by:
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL4[] =
{
  {  806000000, &ClockSource_XO, { 0, 0, 1, 41,  0x0000FAAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL6
 *
 * Used by:
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL6[] =
{
  {  384000000, &ClockSource_XO, { 0, 0, 1, 20,  0x00000000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1,},
};

/*
 * ClockSourceBSP_GCC_GCCGPLL9
 *
 * Used by:
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL9[] =
{
  {  808000000, &ClockSource_XO, { 0, 0, 1, 42,  0x00001555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
};

/*
 * ClockSourceBSP_GPUCC_GPUCCPLL0
 *
 * Used by:
 *   ClockSource_GPUCC_GPUCCPLL0
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GPUCC_GPUCCPLL0[] =
{
  {  700000000, &ClockSource_XO, { 0, 0, 1, 36,  0x00007555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1300000000, &ClockSource_XO, { 0, 0, 1, 67,  0x0000B555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1375000000, &ClockSource_XO, { 0, 0, 1, 71,  0x00009D55, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};

/*
 * ClockSourceBSP_GXCLKCTL_GXCLKCTLPLL0
 *
 * Used by:
 *   ClockSource_GXCLKCTL_GXCLKCTLPLL0
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GXCLKCTL_GXCLKCTLPLL0[] =
{
  {  582000000, &ClockSource_XO, { 0, 0, 1, 30,  0x00005000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1,},
  {  790000000, &ClockSource_XO, { 0, 0, 1, 41,  0x00002555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1086000000, &ClockSource_XO, { 0, 0, 1, 56,  0x00009000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1354000000, &ClockSource_XO, { 0, 0, 1, 70,  0x00008555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1454000000, &ClockSource_XO, { 0, 0, 1, 75,  0x0000BAAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1614000000, &ClockSource_XO, { 0, 0, 1, 84,  0x00001000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_NOM,       },
  { 1790000000, &ClockSource_XO, { 0, 0, 1, 93,  0x00003AAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_NOM,       },
  { 1920000000, &ClockSource_XO, { 0, 0, 1, 100, 0x00000000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_NOM,       },
  { 2100000000, &ClockSource_XO, { 0, 0, 1, 109, 0x00006000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_TUR_L1,    },
};

/*
 * ClockSourceBSP_VIDEOCC_VIDEOCCPLL0
 *
 * Used by:
 *   ClockSource_VIDEOCC_VIDEOCCPLL0
 */
static const ClockSourceFreqConfigType ClockSourceBSP_VIDEOCC_VIDEOCCPLL0[] =
{
  {  720000000, &ClockSource_XO, { 0, 0, 1, 37,  0x00008000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1014000000, &ClockSource_XO, { 0, 0, 1, 52,  0x0000D000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1098000000, &ClockSource_XO, { 0, 0, 1, 57,  0x00003000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1332000000, &ClockSource_XO, { 0, 0, 1, 69,  0x00006000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1656000000, &ClockSource_XO, { 0, 0, 1, 86,  0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_NOM,       },
};


/*=========================================================================
      Sources
==========================================================================*/

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL0 =
{
  .szName       = "cam_cc_pll0",
  .nUniqueId    = 0x3E90B842,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL0,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL0),
  .nRailMask    = RAIL_VDD_MX,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE |
                  CLOCK_CONFIG_PLL_ODD_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL0_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = NULL,
  .nRegSettingsLen            = 0,
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL1 =
{
  .szName       = "cam_cc_pll1",
  .nUniqueId    = 0x6237E726,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL1,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL1),
  .nRailMask    = RAIL_VDD_MX,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL1_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = NULL,
  .nRegSettingsLen            = 0,
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL2 =
{
  .szName       = "cam_cc_pll2",
  .nUniqueId    = 0x6DF55C3B,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL2,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL2),
  .nRailMask    = RAIL_VDD_MX,
  .nConfigMask  = 0x0,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL2_PLL_MODE),
    .pmControl      = &HAL_clk_RivianolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSP_CAMCC_CAMCCPLL2,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL2),
  .pRegSettings               = NULL,
  .nRegSettingsLen            = 0,
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL3 =
{
  .szName       = "cam_cc_pll3",
  .nUniqueId    = 0x9447D816,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL3,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL3),
  .nRailMask    = RAIL_VDD_MX,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL3_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = NULL,
  .nRegSettingsLen            = 0,
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL4 =
{
  .szName       = "cam_cc_pll4",
  .nUniqueId    = 0x70B3A5DD,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL4,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL4),
  .nRailMask    = RAIL_VDD_MX,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL4_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = NULL,
  .nRegSettingsLen            = 0,
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL5 =
{
  .szName       = "cam_cc_pll5",
  .nUniqueId    = 0x838225F9,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL4,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL4),
  .nRailMask    = RAIL_VDD_MX,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL5_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = NULL,
  .nRegSettingsLen            = 0,
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL6 =
{
  .szName       = "cam_cc_pll6",
  .nUniqueId    = 0xC75C6E13,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL4,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL4),
  .nRailMask    = RAIL_VDD_MX,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL6_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = NULL,
  .nRegSettingsLen            = 0,
};

static ClockSourceNodeType ClockSource_DISPCC_DISPCCPLL0 =
{
  .szName       = "disp_cc_pll0",
  .nUniqueId    = 0x4C3DD57F,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_DISPCC_DISPCCPLL0,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_DISPCC_DISPCCPLL0),
  .nRailMask    = RAIL_VDD_CX,
  .nConfigMask  = 0x0,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(DISP_CC_PLL0_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = NULL,
  .nRegSettingsLen            = 0,
};

static ClockSourceNodeType ClockSource_GCC_GCCGPLL0 =
{
  .szName       = "gcc_gpll0",
  .nUniqueId    = 0x799CE72B,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL |
                  CLOCK_FLAG_READ_ONLY,
  .aBSP         = ClockSourceBSP_GCC_GCCGPLL0,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL0),
  .nRailMask    = RAIL_VDD_CX,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE |
                  CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(GCC_GPLL0_PLL_MODE),
    .VoterRegister  = {HWIO_PHYS(GCC_PROC_CLK_PLL_ENA_VOTE), 0x1},
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_GCC_GCCGPLL4 =
{
  .szName       = "gcc_gpll4",
  .nUniqueId    = 0xF99FC9C2,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL |
                  CLOCK_FLAG_READ_ONLY,
  .aBSP         = ClockSourceBSP_GCC_GCCGPLL4,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL4),
  .nRailMask    = RAIL_VDD_CX,
  .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(GCC_GPLL4_PLL_MODE),
    .VoterRegister  = {HWIO_PHYS(GCC_PROC_CLK_PLL_ENA_VOTE), 0x10},
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_GCC_GCCGPLL6 =
{
  .szName       = "gcc_gpll6",
  .nUniqueId    = 0x35B8664A,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL |
                  CLOCK_FLAG_READ_ONLY,
  .aBSP         = ClockSourceBSP_GCC_GCCGPLL6,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL6),
  .nRailMask    = RAIL_VDD_CX,
  .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(GCC_GPLL6_PLL_MODE),
    .VoterRegister  = {HWIO_PHYS(GCC_PROC_CLK_PLL_ENA_VOTE), 0x40},
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_GCC_GCCGPLL9 =
{
  .szName       = "gcc_gpll9",
  .nUniqueId    = 0xF7CEA735,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL |
                  CLOCK_FLAG_READ_ONLY,
  .aBSP         = ClockSourceBSP_GCC_GCCGPLL9,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL9),
  .nRailMask    = RAIL_VDD_CX,
  .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(GCC_GPLL9_PLL_MODE),
    .VoterRegister  = {HWIO_PHYS(GCC_PROC_CLK_PLL_ENA_VOTE), 0x200},
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_GPUCC_GPUCCPLL0 =
{
  .szName       = "gpu_cc_pll0",
  .nUniqueId    = 0x858FC27E,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_GPUCC_GPUCCPLL0,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GPUCC_GPUCCPLL0),
  .nRailMask    = RAIL_VDD_MX,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(GPUCC_GPU_CC_PLL0_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = NULL,
  .nRegSettingsLen            = 0,
};

static ClockSourceNodeType ClockSource_GXCLKCTL_GXCLKCTLPLL0 =
{
  .szName       = "gx_clkctl_pll0",
  .nUniqueId    = 0x8945FE1A,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_GXCLKCTL_GXCLKCTLPLL0,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GXCLKCTL_GXCLKCTLPLL0),
  .nRailMask    = RAIL_VDD_MX,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(GPU_GX_CLKCTL_PLL0_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = NULL,
  .nRegSettingsLen            = 0,
};

static ClockSourceNodeType ClockSource_VIDEOCC_VIDEOCCPLL0 =
{
  .szName       = "video_cc_pll0",
  .nUniqueId    = 0xD9130185,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_VIDEOCC_VIDEOCCPLL0,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_VIDEOCC_VIDEOCCPLL0),
  .nRailMask    = RAIL_VDD_MX,
  .nConfigMask  = 0x0,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(VCODEC_VIDEO_CC_PLL0_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = NULL,
  .nRegSettingsLen            = 0,
};


static ClockSourceNodeType *aSources[] =
{
  &ClockSource_CAMCC_CAMCCPLL0,
  &ClockSource_CAMCC_CAMCCPLL1,
  &ClockSource_CAMCC_CAMCCPLL2,
  &ClockSource_CAMCC_CAMCCPLL3,
  &ClockSource_CAMCC_CAMCCPLL4,
  &ClockSource_CAMCC_CAMCCPLL5,
  &ClockSource_CAMCC_CAMCCPLL6,
  &ClockSource_DISPCC_DISPCCPLL0,
  &ClockSource_GCC_GCCGPLL0,
  &ClockSource_GCC_GCCGPLL4,
  &ClockSource_GCC_GCCGPLL6,
  &ClockSource_GCC_GCCGPLL9,
  &ClockSource_GPUCC_GPUCCPLL0,
  &ClockSource_GXCLKCTL_GXCLKCTLPLL0,
  &ClockSource_VIDEOCC_VIDEOCCPLL0,
  &ClockSource_XO,
};

/*=========================================================================
      Dividers
==========================================================================*/

static ClockDividerNodeType aDividers[] =
{
  {
    .szName    = "cam_cc_camnoc_nrt_axi_div_clk_src",
    .nUniqueId = 0x41D53461,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_CAMNOC_NRT_AXI_DIV_DCDR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_debug_div_clk_src",
    .nUniqueId = 0x44FEDC59,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_DEBUG_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_pll_test_div_clk_src",
    .nUniqueId = 0x2937C1CD,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_PLL_TEST_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_spdm_bps_div_clk_src",
    .nUniqueId = 0x38FE1424,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_SPDM_BPS_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_spdm_ope_0_div_clk_src",
    .nUniqueId = 0x670B8C91,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_SPDM_OPE_0_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_spdm_tfe_0_csid_div_clk_src",
    .nUniqueId = 0x41AEA1E2,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_SPDM_TFE_0_CSID_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_spdm_tfe_0_div_clk_src",
    .nUniqueId = 0xE3983AC0,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_SPDM_TFE_0_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_spdm_tfe_1_div_clk_src",
    .nUniqueId = 0xB5634E9D,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_SPDM_TFE_1_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_spdm_tfe_2_div_clk_src",
    .nUniqueId = 0x09123883,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_SPDM_TFE_2_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_debug_div_clk_src",
    .nUniqueId = 0x62B24CF1,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_DEBUG_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_byte0_div_clk_src",
    .nUniqueId = 0x7355820C,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_BYTE0_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx0_crypto_div_clk_src",
    .nUniqueId = 0x24B06A04,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = 0,
      .nFlags      = HAL_CLK_FLAG_DIVIDER_SUPPORTS_HID,
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx0_link_div_clk_src",
    .nUniqueId = 0x44E0BEA7,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_DPTX0_LINK_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_debug_div_clk_src",
    .nUniqueId = 0xEE3A2D86,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_SPDM_DEBUG_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_crypto_div_clk_src",
    .nUniqueId = 0x92140365,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_SPDM_DP_CRYPTO_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_pixel1_div_clk_src",
    .nUniqueId = 0xBA7C3FFE,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_SPDM_DP_PIXEL1_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_pixel_div_clk_src",
    .nUniqueId = 0xB91A8101,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_SPDM_DP_PIXEL_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_mdp_div_clk_src",
    .nUniqueId = 0xF50D25B5,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_SPDM_MDP_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_pclk0_div_clk_src",
    .nUniqueId = 0xC1F3C754,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_SPDM_PCLK0_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_pll_test_div_clk_src",
    .nUniqueId = 0x2DF2D452,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_PLL_TEST_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_gpll0_ufs_phy_rx_symbol_0_div_clk_src",
    .nUniqueId = 0xE2B0632E,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_GPLL0_UFS_PHY_RX_SYMBOL_0_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_gpll0_ufs_phy_rx_symbol_1_div_clk_src",
    .nUniqueId = 0x8E32C3F7,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_GPLL0_UFS_PHY_RX_SYMBOL_1_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_gpll0_ufs_phy_tx_symbol_0_div_clk_src",
    .nUniqueId = 0xB63D9CE4,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_GPLL0_UFS_PHY_TX_SYMBOL_0_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_gpu_memnoc_gfx_dcd_cdiv_clk_src",
    .nUniqueId = 0x0ABCE4B7,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_GPU_MEMNOC_GFX_DCD_CDIV_DCDR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_gpu_pll0_main_div_clk_src",
    .nUniqueId = 0x1D106BCF,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_GPU_PLL0_MAIN_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_gpu_trig_div_clk_src",
    .nUniqueId = 0x74E54DEE,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_GPU_TRIG_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_pcie_0_pipe_div2_clk_src",
    .nUniqueId = 0x2D2A537B,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_PCIE_0_PIPE_DIV2_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_pcie_1_pipe_div2_clk_src",
    .nUniqueId = 0x5F3CFC6A,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_PCIE_1_PIPE_DIV2_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_pdm_xo4_div_clk_src",
    .nUniqueId = 0x45668877,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_PDM_XO4_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap0_core_div_clk_src",
    .nUniqueId = 0x05EECE68,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_QUPV3_WRAP0_CORE_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap0_s2_clk_src",
    .nUniqueId = 0xC4314028,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_QUPV3_WRAP0_S2_CDIVR),
      .nFlags      = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap1_core_div_clk_src",
    .nUniqueId = 0x9C4D8275,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_QUPV3_WRAP1_CORE_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap1_s2_clk_src",
    .nUniqueId = 0x0054935A,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_QUPV3_WRAP1_S2_CDIVR),
      .nFlags      = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_usb30_prim_mock_utmi_postdiv_clk_src",
    .nUniqueId = 0x33EBC056,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_USB30_PRIM_MOCK_UTMI_POSTDIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gpu_cc_debug_div_clk_src",
    .nUniqueId = 0x5614E81D,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GPUCC_GPU_CC_DEBUG_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gpu_cc_demet_div_clk_src",
    .nUniqueId = 0xA02475AF,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GPUCC_GPU_CC_DEMET_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gpu_cc_hub_div_clk_src",
    .nUniqueId = 0x6E8F44EF,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GPUCC_GPU_CC_HUB_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gpu_cc_pll_test_div_clk_src",
    .nUniqueId = 0x13284B79,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GPUCC_GPU_CC_PLL_TEST_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gpu_cc_xo_div_clk_src",
    .nUniqueId = 0x6DA2BFA1,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GPUCC_GPU_CC_XO_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gx_clkctl_gx_gfx3d_div_clk_src",
    .nUniqueId = 0x16932E80,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GPU_GX_CLKCTL_GX_GFX3D_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gx_clkctl_pll_test_div_clk_src",
    .nUniqueId = 0xCD670337,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GPU_GX_CLKCTL_PLL_TEST_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gx_clkctl_xo_clk_div_clk_src",
    .nUniqueId = 0x456174A0,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GPU_GX_CLKCTL_XO_CLK_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "video_cc_debug_div_clk_src",
    .nUniqueId = 0xF29AA514,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(VCODEC_VIDEO_CC_DEBUG_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "video_cc_mvs0_div_clk_src",
    .nUniqueId = 0x6EC8765C,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(VCODEC_VIDEO_CC_MVS0_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "video_cc_mvs0c_div2_div_clk_src",
    .nUniqueId = 0xF9B6D090,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(VCODEC_VIDEO_CC_MVS0C_DIV2_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "video_cc_mvs0c_div_clk_src",
    .nUniqueId = 0x6D4B044F,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(VCODEC_VIDEO_CC_MVS0C_DIV_DCDR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "video_cc_pll_test_div_clk_src",
    .nUniqueId = 0x3AD246DE,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(VCODEC_VIDEO_CC_PLL_TEST_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
};


/*=========================================================================
      Domain BSP
==========================================================================*/

/*
 * ClockDomainBSP_CAMCC_CAMCCBPS
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCBPS
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCBPS[] =
{
  {  300000000, &ClockSource_CAMCC_CAMCCPLL1,             { 3,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL1[ 0] /* 300.0  */ },    /* Mux[3] = CAM_CC_PLL1_OUT_EVEN */
  {  410000000, &ClockSource_CAMCC_CAMCCPLL1,             { 3,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL1[ 1] /* 410.0  */ },    /* Mux[3] = CAM_CC_PLL1_OUT_EVEN */
  {  460000000, &ClockSource_CAMCC_CAMCCPLL1,             { 3,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL1[ 2] /* 460.0  */ },    /* Mux[3] = CAM_CC_PLL1_OUT_EVEN */
  {  600000000, &ClockSource_CAMCC_CAMCCPLL1,             { 3,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL1[ 3] /* 600.0  */ },    /* Mux[3] = CAM_CC_PLL1_OUT_EVEN */
  {  700000000, &ClockSource_CAMCC_CAMCCPLL1,             { 3,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL1[ 4] /* 700.0  */ },    /* Mux[3] = CAM_CC_PLL1_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCCAMNOCAXI
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCAMNOCAXI
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCCAMNOCAXI[] =
{
  {  150000000, &ClockSource_CAMCC_CAMCCPLL0,             { 6,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = CAM_CC_PLL0_OUT_EVEN */
  {  240000000, &ClockSource_CAMCC_CAMCCPLL0,             { 6,     5,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = CAM_CC_PLL0_OUT_EVEN */
  {  300000000, &ClockSource_CAMCC_CAMCCPLL0,             { 6,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[6] = CAM_CC_PLL0_OUT_EVEN */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 5,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[5] = CAM_CC_PLL0_OUT_ODD */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCCCI0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCCI0
 *   ClockDomain_CAMCC_CAMCCCCI1
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCCCI0[] =
{
  {   37500000, &ClockSource_CAMCC_CAMCCPLL0,             { 6,     32,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = CAM_CC_PLL0_OUT_EVEN */
  {   50000000, &ClockSource_CAMCC_CAMCCPLL0,             { 6,     24,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = CAM_CC_PLL0_OUT_EVEN */
  {  100000000, &ClockSource_CAMCC_CAMCCPLL0,             { 6,     12,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[6] = CAM_CC_PLL0_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCCPHYRX
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCPHYRX
 *   ClockDomain_CAMCC_CAMCCTFE0CSID
 *   ClockDomain_CAMCC_CAMCCTFE1CSID
 *   ClockDomain_CAMCC_CAMCCTFE2CSID
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCCPHYRX[] =
{
  {  300000000, &ClockSource_CAMCC_CAMCCPLL0,             { 6,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = CAM_CC_PLL0_OUT_EVEN */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 6,     3,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = CAM_CC_PLL0_OUT_EVEN */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCCRE
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCRE
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCCRE[] =
{
  {  300000000, &ClockSource_CAMCC_CAMCCPLL0,             { 6,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = CAM_CC_PLL0_OUT_EVEN */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 5,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[5] = CAM_CC_PLL0_OUT_ODD */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
  {  600000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCSI0PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI1PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI2PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI3PHYTIMER
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER[] =
{
  {  300000000, &ClockSource_CAMCC_CAMCCPLL0,             { 6,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = CAM_CC_PLL0_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCFASTAHB
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCFASTAHB
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCFASTAHB[] =
{
  {  100000000, &ClockSource_CAMCC_CAMCCPLL0,             { 6,     12,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = CAM_CC_PLL0_OUT_EVEN */
  {  150000000, &ClockSource_CAMCC_CAMCCPLL0,             { 6,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = CAM_CC_PLL0_OUT_EVEN */
  {  200000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     12,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
  {  240000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     10,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCICP
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCICP
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCICP[] =
{
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
  {  480000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     5,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
  {  600000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCMCLK0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCMCLK0
 *   ClockDomain_CAMCC_CAMCCMCLK1
 *   ClockDomain_CAMCC_CAMCCMCLK2
 *   ClockDomain_CAMCC_CAMCCMCLK3
 *   ClockDomain_CAMCC_CAMCCMCLK4
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCMCLK0[] =
{
  {   64000000, &ClockSource_CAMCC_CAMCCPLL2,             { 4,     30,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[4] = CAM_CC_PLL2_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCOPE0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCOPE0
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCOPE0[] =
{
  {  300000000, &ClockSource_CAMCC_CAMCCPLL3,             { 5,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 0] /* 300.0  */ },    /* Mux[5] = CAM_CC_PLL3_OUT_EVEN */
  {  410000000, &ClockSource_CAMCC_CAMCCPLL3,             { 5,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 1] /* 410.0  */ },    /* Mux[5] = CAM_CC_PLL3_OUT_EVEN */
  {  520000000, &ClockSource_CAMCC_CAMCCPLL3,             { 5,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 2] /* 520.0  */ },    /* Mux[5] = CAM_CC_PLL3_OUT_EVEN */
  {  645000000, &ClockSource_CAMCC_CAMCCPLL3,             { 5,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 3] /* 645.0  */ },    /* Mux[5] = CAM_CC_PLL3_OUT_EVEN */
  {  700000000, &ClockSource_CAMCC_CAMCCPLL3,             { 5,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 4] /* 700.0  */ },    /* Mux[5] = CAM_CC_PLL3_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCSLEEP
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCSLEEP
 *   ClockDomain_DISPCC_DISPCCSLEEP
 *   ClockDomain_VIDEOCC_VIDEOCCSLEEP
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCSLEEP[] =
{
  {      32000, NULL,                                     { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = CHIP_SLEEP_CLK */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCSLOWAHB
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCSLOWAHB
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCSLOWAHB[] =
{
  {   80000000, &ClockSource_CAMCC_CAMCCPLL0,             { 6,     15,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = CAM_CC_PLL0_OUT_EVEN */
  {   80000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     30,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCTFE0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCTFE0
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCTFE0[] =
{
  {  350000000, &ClockSource_CAMCC_CAMCCPLL4,             { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL4[ 0] /* 350.0  */ },    /* Mux[2] = CAM_CC_PLL4_OUT_EVEN */
  {  570000000, &ClockSource_CAMCC_CAMCCPLL4,             { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL4[ 1] /* 570.0  */ },    /* Mux[2] = CAM_CC_PLL4_OUT_EVEN */
  {  600000000, &ClockSource_CAMCC_CAMCCPLL4,             { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL4[ 2] /* 600.0  */ },    /* Mux[2] = CAM_CC_PLL4_OUT_EVEN */
  {  725000000, &ClockSource_CAMCC_CAMCCPLL4,             { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL4[ 3] /* 725.0  */ },    /* Mux[2] = CAM_CC_PLL4_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCTFE1
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCTFE1
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCTFE1[] =
{
  {  350000000, &ClockSource_CAMCC_CAMCCPLL5,             { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL4[ 0] /* 350.0  */ },    /* Mux[2] = CAM_CC_PLL5_OUT_EVEN */
  {  570000000, &ClockSource_CAMCC_CAMCCPLL5,             { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL4[ 1] /* 570.0  */ },    /* Mux[2] = CAM_CC_PLL5_OUT_EVEN */
  {  600000000, &ClockSource_CAMCC_CAMCCPLL5,             { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL4[ 2] /* 600.0  */ },    /* Mux[2] = CAM_CC_PLL5_OUT_EVEN */
  {  725000000, &ClockSource_CAMCC_CAMCCPLL5,             { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL4[ 3] /* 725.0  */ },    /* Mux[2] = CAM_CC_PLL5_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCTFE2
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCTFE2
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCTFE2[] =
{
  {  350000000, &ClockSource_CAMCC_CAMCCPLL6,             { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL4[ 0] /* 350.0  */ },    /* Mux[2] = CAM_CC_PLL6_OUT_EVEN */
  {  570000000, &ClockSource_CAMCC_CAMCCPLL6,             { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL4[ 1] /* 570.0  */ },    /* Mux[2] = CAM_CC_PLL6_OUT_EVEN */
  {  600000000, &ClockSource_CAMCC_CAMCCPLL6,             { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL4[ 2] /* 600.0  */ },    /* Mux[2] = CAM_CC_PLL6_OUT_EVEN */
  {  725000000, &ClockSource_CAMCC_CAMCCPLL6,             { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL4[ 3] /* 725.0  */ },    /* Mux[2] = CAM_CC_PLL6_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCXO
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCXO
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX
 *   ClockDomain_DISPCC_DISPCCMDSSESC0
 *   ClockDomain_DISPCC_DISPCCMDSSVSYNC
 *   ClockDomain_DISPCC_DISPCCXO
 *   ClockDomain_GCC_GCCPCIE0AUX
 *   ClockDomain_GCC_GCCPCIE1AUX
 *   ClockDomain_GCC_GCCUFSPHYPHYAUX
 *   ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI
 *   ClockDomain_GCC_GCCUSB3PRIMPHYAUX
 *   ClockDomain_GPUCC_GPUCCXO
 *   ClockDomain_VIDEOCC_VIDEOCCAHB
 *   ClockDomain_VIDEOCC_VIDEOCCXO
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCXO[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
};

/*
 * ClockDomainBSP_DISPCC_DISPCCMDSSAHB
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSAHB
 */
static ClockMuxConfigType ClockDomainBSP_DISPCC_DISPCCMDSSAHB[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   37500000, NULL,                                     { 4,     16,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[4] = GCC_DISP_GPLL0_CLK */
  {   75000000, NULL,                                     { 4,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[4] = GCC_DISP_GPLL0_CLK */
};

/*
 * ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSBYTE0
 */
static ClockMuxConfigType ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0[] =
{
  {  187500000, NULL,                                     { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = DSI0_PHY_PLL_OUT_BYTECLK */
  {  300000000, NULL,                                     { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[2] = DSI0_PHY_PLL_OUT_BYTECLK */
  {  358000000, NULL,                                     { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[2] = DSI0_PHY_PLL_OUT_BYTECLK */
};

/*
 * ClockDomainBSP_DISPCC_DISPCCMDSSDPTX0LINK
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK
 */
static ClockMuxConfigType ClockDomainBSP_DISPCC_DISPCCMDSSDPTX0LINK[] =
{
  {  270000000, NULL,                                     { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[1] = DP0_PHY_PLL_LINK_CLK */
  {  540000000, NULL,                                     { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[1] = DP0_PHY_PLL_LINK_CLK */
  {  810000000, NULL,                                     { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[1] = DP0_PHY_PLL_LINK_CLK */
};

/*
 * ClockDomainBSP_DISPCC_DISPCCMDSSDPTX0PIXEL0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1
 */
static ClockMuxConfigType ClockDomainBSP_DISPCC_DISPCCMDSSDPTX0PIXEL0[] =
{
  {  337500000, NULL,                                     { 2,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = DP0_PHY_PLL_VCO_DIV_CLK */
  {  337500000, NULL,                                     { 2,     2,     5,     12,    0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = DP0_PHY_PLL_VCO_DIV_CLK */
  {  405000000, NULL,                                     { 2,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[2] = DP0_PHY_PLL_VCO_DIV_CLK */
  {  675000000, NULL,                                     { 2,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[2] = DP0_PHY_PLL_VCO_DIV_CLK */
};

/*
 * ClockDomainBSP_DISPCC_DISPCCMDSSMDP
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSMDP
 */
static ClockMuxConfigType ClockDomainBSP_DISPCC_DISPCCMDSSMDP[] =
{
  {  200000000, &ClockSource_DISPCC_DISPCCPLL0,           { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_DISPCC_DISPCCPLL0[ 0] /* 600.0  */ },  /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  342000000, &ClockSource_DISPCC_DISPCCPLL0,           { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_DISPCC_DISPCCPLL0[ 1] /* 1026.0 */ },  /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  402000000, &ClockSource_DISPCC_DISPCCPLL0,           { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_DISPCC_DISPCCPLL0[ 2] /* 1206.0 */ },  /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  535000000, &ClockSource_DISPCC_DISPCCPLL0,           { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_DISPCC_DISPCCPLL0[ 3] /* 1605.0 */ },  /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  600000000, &ClockSource_DISPCC_DISPCCPLL0,           { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM_L1,     {{0}}, &ClockSourceBSP_DISPCC_DISPCCPLL0[ 4] /* 1800.0 */ },  /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  630000000, &ClockSource_DISPCC_DISPCCPLL0,           { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR,        {{0}}, &ClockSourceBSP_DISPCC_DISPCCPLL0[ 5] /* 1890.0 */ },  /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_DISPCC_DISPCCMDSSPCLK0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSPCLK0
 */
static ClockMuxConfigType ClockDomainBSP_DISPCC_DISPCCMDSSPCLK0[] =
{
  {  300000000, NULL,                                     { 1,     5,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[1] = DSI0_PHY_PLL_OUT_DSICLK */
  {  480000000, NULL,                                     { 1,     5,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = DSI0_PHY_PLL_OUT_DSICLK */
  {  625000000, NULL,                                     { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[1] = DSI0_PHY_PLL_OUT_DSICLK */
};

/*
 * ClockDomainBSP_GCC_GCCGP1
 *
 * Used by:
 *   ClockDomain_GCC_GCCGP1
 *   ClockDomain_GCC_GCCGP2
 *   ClockDomain_GCC_GCCGP3
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCGP1[] =
{
  {   50000000, &ClockSource_GCC_GCCGPLL0,                { 6,     12,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP110_CLKGEN_ACGC_CLK */
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 1,     12,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP10_CLKGEN_ACGC_CLK */
  {  200000000, &ClockSource_GCC_GCCGPLL0,                { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP10_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCPCIE0PHYRCHNG
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE0PHYRCHNG
 *   ClockDomain_GCC_GCCPCIE1PHYRCHNG
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCPCIE0PHYRCHNG[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 6,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP127_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCPDM2
 *
 * Used by:
 *   ClockDomain_GCC_GCCPDM2
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCPDM2[] =
{
  {   60000000, &ClockSource_GCC_GCCGPLL0,                { 1,     20,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP35_CLKGEN_ACGC_CLK */
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
 *   ClockDomain_GCC_GCCQUPV3WRAP1QSPIREF
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP0QSPIREF[] =
{
  {  150000000, &ClockSource_GCC_GCCGPLL0,                { 6,     4,     0,     0,     0x00 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {  200000000, &ClockSource_GCC_GCCGPLL0,                { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP7_CLKGEN_ACGC_CLK */
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
 *   ClockDomain_GCC_GCCQUPV3WRAP1S0
 *   ClockDomain_GCC_GCCQUPV3WRAP1S1
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP0S0[] =
{
  {    7372800, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     384,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   14745600, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     768,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0x00 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   29491200, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     1536,  15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   32000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     75,    0x01 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   48000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     25,    0x02 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   64000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     16,    75,    0x03 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   75000000, &ClockSource_GCC_GCCGPLL0,                { 6,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   80000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     15,    0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   96000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     25,    0x04 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 1,     12,    0,     0,     0x05 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP7_CLKGEN_ACGC_CLK */
  {  102400000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     128,   375,   0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {  112000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     28,    75,    0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {  117964800, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     6144,  15625, 0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {  120000000, &ClockSource_GCC_GCCGPLL0,                { 1,     10,    0,     0,     0x06 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP7_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCQUPV3WRAP0S3
 *
 * Note: These frequencies are used by domains possibly under DFS control. The
 *       DFS-enable state will be detected during init. If under DFS control,
 *       the domain will dynamically allocate its own BSP array and populate
 *       it with configurations detected from the DFS registers.
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP0S3
 *   ClockDomain_GCC_GCCQUPV3WRAP0S5
 *   ClockDomain_GCC_GCCQUPV3WRAP1S5
 *   ClockDomain_GCC_GCCQUPV3WRAP1S6
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP0S3[] =
{
  {    7372800, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     384,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   14745600, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     768,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0x00 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   29491200, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     1536,  15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   32000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     75,    0x01 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   48000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     25,    0x02 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   64000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     16,    75,    0x03 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   75000000, &ClockSource_GCC_GCCGPLL0,                { 6,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   80000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     15,    0x04 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   96000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     25,    0x05 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 1,     12,    0,     0,     0x06 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP7_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCQUPV3WRAP0S4
 *
 * Note: These frequencies are used by domains possibly under DFS control. The
 *       DFS-enable state will be detected during init. If under DFS control,
 *       the domain will dynamically allocate its own BSP array and populate
 *       it with configurations detected from the DFS registers.
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP0S4
 *   ClockDomain_GCC_GCCQUPV3WRAP1S4
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP0S4[] =
{
  {    7372800, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     384,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   14745600, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     768,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0x00 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   29491200, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     1536,  15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   32000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     75,    0x01 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   48000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     25,    0x02 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   64000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     16,    75,    0x03 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   80000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     15,    0x04 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   96000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     25,    0x05 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {  128000000, &ClockSource_GCC_GCCGPLL6,                { 2,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = GCC_GPLL6_OUT_MAIN_PWRGRP2_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCQUPV3WRAP0S6
 *
 * Note: These frequencies are used by domains possibly under DFS control. The
 *       DFS-enable state will be detected during init. If under DFS control,
 *       the domain will dynamically allocate its own BSP array and populate
 *       it with configurations detected from the DFS registers.
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP0S6
 *   ClockDomain_GCC_GCCQUPV3WRAP1S3
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP0S6[] =
{
  {    7372800, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     384,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   14745600, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     768,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0x00 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   29491200, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     1536,  15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   32000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     75,    0x01 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   48000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     25,    0x02 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   64000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     16,    75,    0x03 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   75000000, &ClockSource_GCC_GCCGPLL0,                { 6,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   80000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     15,    0x04 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {   96000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     25,    0x05 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP107_CLKGEN_ACGC_CLK */
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 1,     12,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP7_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCSDCC1APPS
 *
 * Used by:
 *   ClockDomain_GCC_GCCSDCC1APPS
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCSDCC1APPS[] =
{
  {     144000, &ClockSource_XO,                          { 0,     32,    3,     25,    0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {     400000, &ClockSource_XO,                          { 0,     24,    1,     4,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   20000000, &ClockSource_GCC_GCCGPLL0,                { 6,     10,    1,     3,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP133_CLKGEN_ACGC_CLK */
  {   25000000, &ClockSource_GCC_GCCGPLL0,                { 6,     24,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP133_CLKGEN_ACGC_CLK */
  {   50000000, &ClockSource_GCC_GCCGPLL0,                { 6,     12,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP133_CLKGEN_ACGC_CLK */
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 6,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP133_CLKGEN_ACGC_CLK */
  {  192000000, &ClockSource_GCC_GCCGPLL6,                { 2,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[2] = GCC_GPLL6_OUT_MAIN_PWRGRP1_CLKGEN_ACGC_CLK */
  {  384000000, &ClockSource_GCC_GCCGPLL6,                { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[2] = GCC_GPLL6_OUT_MAIN_PWRGRP1_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCSDCC1ICECORE
 *
 * Used by:
 *   ClockDomain_GCC_GCCSDCC1ICECORE
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCSDCC1ICECORE[] =
{
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 6,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP132_CLKGEN_ACGC_CLK */
  {  150000000, &ClockSource_GCC_GCCGPLL0,                { 6,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP132_CLKGEN_ACGC_CLK */
  {  300000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP132_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCSDCC2APPS
 *
 * Used by:
 *   ClockDomain_GCC_GCCSDCC2APPS
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCSDCC2APPS[] =
{
  {     400000, &ClockSource_XO,                          { 0,     24,    1,     4,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   25000000, &ClockSource_GCC_GCCGPLL0,                { 6,     24,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP134_CLKGEN_ACGC_CLK */
  {   37500000, &ClockSource_GCC_GCCGPLL0,                { 6,     16,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP134_CLKGEN_ACGC_CLK */
  {   50000000, &ClockSource_GCC_GCCGPLL0,                { 6,     12,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP134_CLKGEN_ACGC_CLK */
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 6,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP134_CLKGEN_ACGC_CLK */
  {  202000000, &ClockSource_GCC_GCCGPLL9,                { 2,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[2] = GCC_GPLL9_OUT_MAIN_PWRGRP0_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCUFSPHYAXI
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYAXI
 *   ClockDomain_GCC_GCCUFSPHYUNIPROCORE
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCUFSPHYAXI[] =
{
  {   75000000, &ClockSource_GCC_GCCGPLL0,                { 6,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP105_CLKGEN_ACGC_CLK */
  {  150000000, &ClockSource_GCC_GCCGPLL0,                { 1,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP6_CLKGEN_ACGC_CLK */
  {  300000000, &ClockSource_GCC_GCCGPLL0,                { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP6_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCUFSPHYICECORE
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYICECORE
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCUFSPHYICECORE[] =
{
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 6,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP105_CLKGEN_ACGC_CLK */
  {  201500000, &ClockSource_GCC_GCCGPLL4,                { 5,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[5] = GCC_GPLL4_OUT_MAIN_PWRGRP6_CLKGEN_ACGC_CLK */
  {  403000000, &ClockSource_GCC_GCCGPLL4,                { 5,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[5] = GCC_GPLL4_OUT_MAIN_PWRGRP6_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCUSB30PRIMMASTER
 *
 * Used by:
 *   ClockDomain_GCC_GCCUSB30PRIMMASTER
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCUSB30PRIMMASTER[] =
{
  {   66666667, &ClockSource_GCC_GCCGPLL0,                { 6,     9,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP112_CLKGEN_ACGC_CLK */
  {  133333333, &ClockSource_GCC_GCCGPLL0,                { 1,     9,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP12_CLKGEN_ACGC_CLK */
  {  200000000, &ClockSource_GCC_GCCGPLL0,                { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP12_CLKGEN_ACGC_CLK */
  {  240000000, &ClockSource_GCC_GCCGPLL0,                { 1,     5,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP12_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GPUCC_GPUCCFF
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCFF
 */
static ClockMuxConfigType ClockDomainBSP_GPUCC_GPUCCFF[] =
{
  {  200000000, NULL,                                     { 5,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[5] = GPLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_GPUCC_GPUCCGMU
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCGMU
 */
static ClockMuxConfigType ClockDomainBSP_GPUCC_GPUCCGMU[] =
{
  {  350000000, &ClockSource_GPUCC_GPUCCPLL0,             { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 0] /* 350.0  */ },    /* Mux[2] = GPU_CC_PLL0_OUT_EVEN */
  {  650000000, &ClockSource_GPUCC_GPUCCPLL0,             { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 1] /* 650.0  */ },    /* Mux[2] = GPU_CC_PLL0_OUT_EVEN */
  {  687500000, &ClockSource_GPUCC_GPUCCPLL0,             { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 2] /* 687.0  */ },    /* Mux[2] = GPU_CC_PLL0_OUT_EVEN */
};

/*
 * ClockDomainBSP_GPUCC_GPUCCHUB
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCHUB
 */
static ClockMuxConfigType ClockDomainBSP_GPUCC_GPUCCHUB[] =
{
  {  200000000, NULL,                                     { 5,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[5] = GPLL0_OUT_MAIN */
  {  300000000, NULL,                                     { 5,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[5] = GPLL0_OUT_MAIN */
  {  400000000, NULL,                                     { 5,     3,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[5] = GPLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_GXCLKCTL_GXCLKCTLGXGFX3D
 *
 * Used by:
 *   ClockDomain_GXCLKCTL_GXCLKCTLGXGFX3D
 */
static ClockMuxConfigType ClockDomainBSP_GXCLKCTL_GXCLKCTLGXGFX3D[] =
{
  {  291000000, &ClockSource_GXCLKCTL_GXCLKCTLPLL0,       { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, {{0}}, &ClockSourceBSP_GXCLKCTL_GXCLKCTLPLL0[ 0] /* 582.0  */ },  /* Mux[1] = GX_CLKCTL_PLL0_OUT_EVEN */
  {  395000000, &ClockSource_GXCLKCTL_GXCLKCTLPLL0,       { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_GXCLKCTL_GXCLKCTLPLL0[ 1] /* 790.0  */ },  /* Mux[1] = GX_CLKCTL_PLL0_OUT_EVEN */
  {  543000000, &ClockSource_GXCLKCTL_GXCLKCTLPLL0,       { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_GXCLKCTL_GXCLKCTLPLL0[ 2] /* 1086.0 */ },  /* Mux[1] = GX_CLKCTL_PLL0_OUT_EVEN */
  {  677000000, &ClockSource_GXCLKCTL_GXCLKCTLPLL0,       { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_GXCLKCTL_GXCLKCTLPLL0[ 3] /* 1354.0 */ },  /* Mux[1] = GX_CLKCTL_PLL0_OUT_EVEN */
  {  727000000, &ClockSource_GXCLKCTL_GXCLKCTLPLL0,       { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L2,     {{0}}, &ClockSourceBSP_GXCLKCTL_GXCLKCTLPLL0[ 4] /* 1454.0 */ },  /* Mux[1] = GX_CLKCTL_PLL0_OUT_EVEN */
  {  807000000, &ClockSource_GXCLKCTL_GXCLKCTLPLL0,       { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_GXCLKCTL_GXCLKCTLPLL0[ 5] /* 1614.0 */ },  /* Mux[1] = GX_CLKCTL_PLL0_OUT_EVEN */
  {  895000000, &ClockSource_GXCLKCTL_GXCLKCTLPLL0,       { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM_L1,     {{0}}, &ClockSourceBSP_GXCLKCTL_GXCLKCTLPLL0[ 6] /* 1790.0 */ },  /* Mux[1] = GX_CLKCTL_PLL0_OUT_EVEN */
  {  960000000, &ClockSource_GXCLKCTL_GXCLKCTLPLL0,       { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR,        {{0}}, &ClockSourceBSP_GXCLKCTL_GXCLKCTLPLL0[ 7] /* 1920.0 */ },  /* Mux[1] = GX_CLKCTL_PLL0_OUT_EVEN */
  { 1050000000, &ClockSource_GXCLKCTL_GXCLKCTLPLL0,       { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR_L1,     {{0}}, &ClockSourceBSP_GXCLKCTL_GXCLKCTLPLL0[ 8] /* 2100.0 */ },  /* Mux[1] = GX_CLKCTL_PLL0_OUT_EVEN */
};

/*
 * ClockDomainBSP_GXCLKCTL_GXCLKCTLXO
 *
 * Used by:
 *   ClockDomain_GXCLKCTL_GXCLKCTLXO
 */
static ClockMuxConfigType ClockDomainBSP_GXCLKCTL_GXCLKCTLXO[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },                                                            /* Mux[0] = BI_TCXO */
};

/*
 * ClockDomainBSP_VIDEOCC_VIDEOCCMVS0
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCMVS0
 */
static ClockMuxConfigType ClockDomainBSP_VIDEOCC_VIDEOCCMVS0[] =
{
  {  720000000, &ClockSource_VIDEOCC_VIDEOCCPLL0,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL0[ 0] /* 720.0  */ },  /* Mux[1] = VIDEO_CC_PLL0_OUT_MAIN */
  { 1014000000, &ClockSource_VIDEOCC_VIDEOCCPLL0,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL0[ 1] /* 1014.0 */ },  /* Mux[1] = VIDEO_CC_PLL0_OUT_MAIN */
  { 1098000000, &ClockSource_VIDEOCC_VIDEOCCPLL0,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL0[ 2] /* 1098.0 */ },  /* Mux[1] = VIDEO_CC_PLL0_OUT_MAIN */
  { 1332000000, &ClockSource_VIDEOCC_VIDEOCCPLL0,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL0[ 3] /* 1332.0 */ },  /* Mux[1] = VIDEO_CC_PLL0_OUT_MAIN */
  { 1656000000, &ClockSource_VIDEOCC_VIDEOCCPLL0,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR,        {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL0[ 4] /* 1656.0 */ },  /* Mux[1] = VIDEO_CC_PLL0_OUT_MAIN */
};


/*=========================================================================
      Domain Source Maps
==========================================================================*/

/*
 * ClockSourceMap_APSSCC_APSSCCDEBUGMUX
 *
 * Used by:
 *   ClockDomain_APSSCC_APSSCCDEBUGMUX
 */
static const ClockSourceMapType ClockSourceMap_APSSCC_APSSCCDEBUGMUX[] =
{
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCBPS
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCBPS
 *   ClockDomain_CAMCC_CAMCCCRE
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCBPS[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1, 1200000000, &ClockSource_CAMCC_CAMCCPLL0,            1, },
  { 2,          0, &ClockSource_CAMCC_CAMCCPLL1,            1, },
  { 3,          0, &ClockSource_CAMCC_CAMCCPLL1,            2, },
  { 5,  400000000, &ClockSource_CAMCC_CAMCCPLL0,            3, },
  { 6,  600000000, &ClockSource_CAMCC_CAMCCPLL0,            2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCCAMNOCAXI
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCAMNOCAXI
 *   ClockDomain_CAMCC_CAMCCCPHYRX
 *   ClockDomain_CAMCC_CAMCCCSI0PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI1PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI2PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI3PHYTIMER
 *   ClockDomain_CAMCC_CAMCCFASTAHB
 *   ClockDomain_CAMCC_CAMCCSLOWAHB
 *   ClockDomain_CAMCC_CAMCCTFE0CSID
 *   ClockDomain_CAMCC_CAMCCTFE1CSID
 *   ClockDomain_CAMCC_CAMCCTFE2CSID
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCCAMNOCAXI[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1, 1200000000, &ClockSource_CAMCC_CAMCCPLL0,            1, },
  { 5,  400000000, &ClockSource_CAMCC_CAMCCPLL0,            3, },
  { 6,  600000000, &ClockSource_CAMCC_CAMCCPLL0,            2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCCCI0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCCI0
 *   ClockDomain_CAMCC_CAMCCCCI1
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCCCI0[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 5,  400000000, &ClockSource_CAMCC_CAMCCPLL0,            3, },
  { 6,  600000000, &ClockSource_CAMCC_CAMCCPLL0,            2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCDEBUGMUX
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCDEBUGMUX
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCDEBUGMUX[] =
{
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCICP
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCICP
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCICP[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1, 1200000000, &ClockSource_CAMCC_CAMCCPLL0,            1, },
  { 6,  600000000, &ClockSource_CAMCC_CAMCCPLL0,            2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCMCLK0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCMCLK0
 *   ClockDomain_CAMCC_CAMCCMCLK1
 *   ClockDomain_CAMCC_CAMCCMCLK2
 *   ClockDomain_CAMCC_CAMCCMCLK3
 *   ClockDomain_CAMCC_CAMCCMCLK4
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCMCLK0[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 3,  480000000, &ClockSource_CAMCC_CAMCCPLL2,            2, },
  { 4,  960000000, &ClockSource_CAMCC_CAMCCPLL2,            1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCOPE0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCOPE0
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCOPE0[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1, 1200000000, &ClockSource_CAMCC_CAMCCPLL0,            1, },
  { 5,          0, &ClockSource_CAMCC_CAMCCPLL3,            2, },
  { 6,  600000000, &ClockSource_CAMCC_CAMCCPLL0,            2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCPLLTESTSTAGE007MUX
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCPLLTESTSTAGE007MUX
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCPLLTESTSTAGE007MUX[] =
{
  { 0,          0, &ClockSource_CAMCC_CAMCCPLL0,            1, },
  { 1,          0, &ClockSource_CAMCC_CAMCCPLL1,            1, },
  { 2,          0, &ClockSource_CAMCC_CAMCCPLL3,            1, },
  { 3,          0, &ClockSource_CAMCC_CAMCCPLL4,            1, },
  { 4,          0, &ClockSource_CAMCC_CAMCCPLL5,            1, },
  { 5,          0, &ClockSource_CAMCC_CAMCCPLL6,            1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCSLEEP
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCSLEEP
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCSLEEP[] =
{
  { 0,      32000, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCTFE0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCTFE0
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCTFE0[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1, 1200000000, &ClockSource_CAMCC_CAMCCPLL0,            1, },
  { 2,          0, &ClockSource_CAMCC_CAMCCPLL4,            2, },
  { 3,          0, &ClockSource_CAMCC_CAMCCPLL4,            1, },
  { 5,  400000000, &ClockSource_CAMCC_CAMCCPLL0,            3, },
  { 6,  600000000, &ClockSource_CAMCC_CAMCCPLL0,            2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCTFE1
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCTFE1
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCTFE1[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1, 1200000000, &ClockSource_CAMCC_CAMCCPLL0,            1, },
  { 2,          0, &ClockSource_CAMCC_CAMCCPLL5,            2, },
  { 3,          0, &ClockSource_CAMCC_CAMCCPLL5,            1, },
  { 5,  400000000, &ClockSource_CAMCC_CAMCCPLL0,            3, },
  { 6,  600000000, &ClockSource_CAMCC_CAMCCPLL0,            2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCTFE2
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCTFE2
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCTFE2[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1, 1200000000, &ClockSource_CAMCC_CAMCCPLL0,            1, },
  { 2,          0, &ClockSource_CAMCC_CAMCCPLL6,            2, },
  { 3,          0, &ClockSource_CAMCC_CAMCCPLL6,            1, },
  { 5,  400000000, &ClockSource_CAMCC_CAMCCPLL0,            3, },
  { 6,  600000000, &ClockSource_CAMCC_CAMCCPLL0,            2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCXO
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCXO
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCXO[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSAHB
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSAHB
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSAHB[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 4,  300000000, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSBYTE0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSBYTE0
 *   ClockDomain_DISPCC_DISPCCMDSSPCLK0
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSBYTE0[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,          0, NULL,                                    1, },
  { 2,          0, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSDPTX0AUX
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX
 *   ClockDomain_DISPCC_DISPCCMDSSVSYNC
 *   ClockDomain_DISPCC_DISPCCXO
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSDPTX0AUX[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSDPTX0LINK
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSDPTX0LINK[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,          0, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSDPTX0PIXEL0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSDPTX0PIXEL0[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,          0, NULL,                                    1, },
  { 2,          0, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSESC0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSESC0
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSESC0[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 2,          0, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSMDP
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSMDP
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSMDP[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,          0, &ClockSource_DISPCC_DISPCCPLL0,          1, },
  { 4,  300000000, NULL,                                    1, },
  { 6,          0, &ClockSource_DISPCC_DISPCCPLL0,          1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCPLLTESTMUX
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCPLLTESTMUX
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCPLLTESTMUX[] =
{
  { 0,          0, &ClockSource_DISPCC_DISPCCPLL0,          1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCSLEEP
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCSLEEP
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCSLEEP[] =
{
  { 0,      32000, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCGP1
 *
 * Used by:
 *   ClockDomain_GCC_GCCGP1
 *   ClockDomain_GCC_GCCGP2
 *   ClockDomain_GCC_GCCGP3
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCGP1[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 5,      32000, NULL,                                    1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCPCIE0AUX
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE0AUX
 *   ClockDomain_GCC_GCCPCIE1AUX
 *   ClockDomain_GCC_GCCUSB3PRIMPHYAUX
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCPCIE0AUX[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 5,      32000, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCPCIE0PHYRCHNG
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE0PHYRCHNG
 *   ClockDomain_GCC_GCCPCIE1PHYRCHNG
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCPCIE0PHYRCHNG[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCPCIE0PIPE
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE0PIPE
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCPCIE0PIPE[] =
{
  { 0,  250000000, NULL,                                    1, },
  { 1,          0, NULL,                                    1, },
  { 2,   19200000, &ClockSource_XO,                         1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCPCIE1PIPE
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE1PIPE
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCPCIE1PIPE[] =
{
  { 0,  250000000, NULL,                                    1, },
  { 1,          0, NULL,                                    1, },
  { 2,   19200000, &ClockSource_XO,                         1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCPDM2
 *
 * Used by:
 *   ClockDomain_GCC_GCCPDM2
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCPDM2[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCQUPV3WRAP0QSPIREF
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP0QSPIREF
 *   ClockDomain_GCC_GCCQUPV3WRAP0S0
 *   ClockDomain_GCC_GCCQUPV3WRAP0S1
 *   ClockDomain_GCC_GCCQUPV3WRAP0S3
 *   ClockDomain_GCC_GCCQUPV3WRAP0S5
 *   ClockDomain_GCC_GCCQUPV3WRAP0S6
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCQUPV3WRAP0QSPIREF[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCQUPV3WRAP0S4
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP0S4
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCQUPV3WRAP0S4[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 2,  384000000, &ClockSource_GCC_GCCGPLL6,               1, },
  { 3,  500000000, NULL,                                    1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCQUPV3WRAP1QSPIREF
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP1QSPIREF
 *   ClockDomain_GCC_GCCQUPV3WRAP1S0
 *   ClockDomain_GCC_GCCQUPV3WRAP1S1
 *   ClockDomain_GCC_GCCQUPV3WRAP1S3
 *   ClockDomain_GCC_GCCQUPV3WRAP1S5
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCQUPV3WRAP1QSPIREF[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCQUPV3WRAP1S4
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP1S4
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCQUPV3WRAP1S4[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 2,  384000000, &ClockSource_GCC_GCCGPLL6,               1, },
  { 3,  500000000, NULL,                                    1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCQUPV3WRAP1S6
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP1S6
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCQUPV3WRAP1S6[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 2,  500000000, NULL,                                    1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCSDCC1APPS
 *
 * Used by:
 *   ClockDomain_GCC_GCCSDCC1APPS
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCSDCC1APPS[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 2,  384000000, &ClockSource_GCC_GCCGPLL6,               1, },
  { 3,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 4, 1000000000, NULL,                                    1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCSDCC1ICECORE
 *
 * Used by:
 *   ClockDomain_GCC_GCCSDCC1ICECORE
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCSDCC1ICECORE[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 2,  384000000, &ClockSource_GCC_GCCGPLL6,               1, },
  { 3,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCSDCC2APPS
 *
 * Used by:
 *   ClockDomain_GCC_GCCSDCC2APPS
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCSDCC2APPS[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 2,  808000000, &ClockSource_GCC_GCCGPLL9,               1, },
  { 5,  806000000, &ClockSource_GCC_GCCGPLL4,               1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUFSPHYAXI
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYAXI
 *   ClockDomain_GCC_GCCUFSPHYUNIPROCORE
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUFSPHYAXI[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 5,  806000000, &ClockSource_GCC_GCCGPLL4,               1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUFSPHYICECORE
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYICECORE
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUFSPHYICECORE[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 5,  806000000, &ClockSource_GCC_GCCGPLL4,               1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUFSPHYPHYAUX
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYPHYAUX
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUFSPHYPHYAUX[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUFSPHYRXSYMBOL0
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYRXSYMBOL0
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUFSPHYRXSYMBOL0[] =
{
  { 0,          0, NULL,                                    1, },
  { 1,          0, NULL,                                    1, },
  { 2,   19200000, &ClockSource_XO,                         1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUFSPHYRXSYMBOL1
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYRXSYMBOL1
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUFSPHYRXSYMBOL1[] =
{
  { 0,          0, NULL,                                    1, },
  { 1,          0, NULL,                                    1, },
  { 2,   19200000, &ClockSource_XO,                         1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUFSPHYTXSYMBOL0
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYTXSYMBOL0
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUFSPHYTXSYMBOL0[] =
{
  { 0,          0, NULL,                                    1, },
  { 1,          0, NULL,                                    1, },
  { 2,   19200000, &ClockSource_XO,                         1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUSB30PRIMMASTER
 *
 * Used by:
 *   ClockDomain_GCC_GCCUSB30PRIMMASTER
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUSB30PRIMMASTER[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUSB30PRIMMOCKUTMI
 *
 * Used by:
 *   ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUSB30PRIMMOCKUTMI[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUSB3PRIMPHYPIPE
 *
 * Used by:
 *   ClockDomain_GCC_GCCUSB3PRIMPHYPIPE
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUSB3PRIMPHYPIPE[] =
{
  { 0,  125000000, NULL,                                    1, },
  { 1,  400000000, NULL,                                    1, },
  { 2,   19200000, &ClockSource_XO,                         1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GPUCC_GPUCCDEBUGMUX
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCDEBUGMUX
 */
static const ClockSourceMapType ClockSourceMap_GPUCC_GPUCCDEBUGMUX[] =
{
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GPUCC_GPUCCFF
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCFF
 */
static const ClockSourceMapType ClockSourceMap_GPUCC_GPUCCFF[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 5,  600000000, NULL,                                    1, },
  { 6,  300000000, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GPUCC_GPUCCGMU
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCGMU
 *   ClockDomain_GPUCC_GPUCCHUB
 */
static const ClockSourceMapType ClockSourceMap_GPUCC_GPUCCGMU[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,          0, &ClockSource_GPUCC_GPUCCPLL0,            1, },
  { 2,          0, &ClockSource_GPUCC_GPUCCPLL0,            2, },
  { 3,          0, &ClockSource_GPUCC_GPUCCPLL0,            1, },
  { 5,  600000000, NULL,                                    1, },
  { 6,  300000000, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GPUCC_GPUCCPLLTESTMUX
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCPLLTESTMUX
 */
static const ClockSourceMapType ClockSourceMap_GPUCC_GPUCCPLLTESTMUX[] =
{
  { 0,          0, &ClockSource_GPUCC_GPUCCPLL0,            1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GPUCC_GPUCCXO
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCXO
 */
static const ClockSourceMapType ClockSourceMap_GPUCC_GPUCCXO[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GXCLKCTL_GXCLKCTLDEBUGMUX
 *
 * Used by:
 *   ClockDomain_GXCLKCTL_GXCLKCTLDEBUGMUX
 */
static const ClockSourceMapType ClockSourceMap_GXCLKCTL_GXCLKCTLDEBUGMUX[] =
{
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GXCLKCTL_GXCLKCTLGXGFX3D
 *
 * Used by:
 *   ClockDomain_GXCLKCTL_GXCLKCTLGXGFX3D
 */
static const ClockSourceMapType ClockSourceMap_GXCLKCTL_GXCLKCTLGXGFX3D[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,          0, &ClockSource_GXCLKCTL_GXCLKCTLPLL0,      1, },
  { 2,          0, &ClockSource_GXCLKCTL_GXCLKCTLPLL0,      1, },
  { 3,          0, &ClockSource_GXCLKCTL_GXCLKCTLPLL0,      1, },
  { 5,  600000000, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GXCLKCTL_GXCLKCTLPLLTESTMUX
 *
 * Used by:
 *   ClockDomain_GXCLKCTL_GXCLKCTLPLLTESTMUX
 */
static const ClockSourceMapType ClockSourceMap_GXCLKCTL_GXCLKCTLPLLTESTMUX[] =
{
  { 0,          0, &ClockSource_GXCLKCTL_GXCLKCTLPLL0,      1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GXCLKCTL_GXCLKCTLXO
 *
 * Used by:
 *   ClockDomain_GXCLKCTL_GXCLKCTLXO
 */
static const ClockSourceMapType ClockSourceMap_GXCLKCTL_GXCLKCTLXO[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_VIDEOCC_VIDEOCCAHB
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCAHB
 *   ClockDomain_VIDEOCC_VIDEOCCXO
 */
static const ClockSourceMapType ClockSourceMap_VIDEOCC_VIDEOCCAHB[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_VIDEOCC_VIDEOCCMVS0
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCMVS0
 */
static const ClockSourceMapType ClockSourceMap_VIDEOCC_VIDEOCCMVS0[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,          0, &ClockSource_VIDEOCC_VIDEOCCPLL0,        1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_VIDEOCC_VIDEOCCPLLTESTMUX
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCPLLTESTMUX
 */
static const ClockSourceMapType ClockSourceMap_VIDEOCC_VIDEOCCPLLTESTMUX[] =
{
  { 0,          0, &ClockSource_VIDEOCC_VIDEOCCPLL0,        1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_VIDEOCC_VIDEOCCSLEEP
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCSLEEP
 */
static const ClockSourceMapType ClockSourceMap_VIDEOCC_VIDEOCCSLEEP[] =
{
  { 0,      32000, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};


/*=========================================================================
      Domain FMAX
==========================================================================*/

/*
 * ClockDomainFMax_APSSCC_APSSCCDEBUGMUX
 *
 * Used by:
 *   ClockDomain_APSSCC_APSSCCDEBUGMUX
 */
static const ClockFMaxType ClockDomainFMax_APSSCC_APSSCCDEBUGMUX[] =
{
  {  158400000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  240000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  302400000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  364800000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  412800000, RAIL_VOLTAGE_LEVEL_NOM_L1,     },
  {  475200000, RAIL_VOLTAGE_LEVEL_TUR,        },
  {  537600000, RAIL_VOLTAGE_LEVEL_TUR_L1,     },
  {  624000000, RAIL_VOLTAGE_LEVEL_TUR_L3,     },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCBPS
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCBPS
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCBPS[] =
{
  {  300000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  410000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  460000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  600000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  700000000, RAIL_VOLTAGE_LEVEL_TUR,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCCAMNOCAXI
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCAMNOCAXI
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCCAMNOCAXI[] =
{
  {  150000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  240000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  300000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  400000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCCCI0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCCI0
 *   ClockDomain_CAMCC_CAMCCCCI1
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCCCI0[] =
{
  {   37500000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {   50000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  100000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCCPHYRX
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCPHYRX
 *   ClockDomain_CAMCC_CAMCCTFE0CSID
 *   ClockDomain_CAMCC_CAMCCTFE1CSID
 *   ClockDomain_CAMCC_CAMCCTFE2CSID
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCCPHYRX[] =
{
  {  300000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  400000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCCRE
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCRE
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCCRE[] =
{
  {  300000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  400000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  600000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCSI0PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI1PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI2PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI3PHYTIMER
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER[] =
{
  {  300000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCDEBUGMUX
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCDEBUGMUX
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCDEBUGMUX[] =
{
  {  600000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCFASTAHB
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCFASTAHB
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCFASTAHB[] =
{
  {  100000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  150000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  200000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  240000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCICP
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCICP
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCICP[] =
{
  {  400000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  480000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  600000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCMCLK0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCMCLK0
 *   ClockDomain_CAMCC_CAMCCMCLK1
 *   ClockDomain_CAMCC_CAMCCMCLK2
 *   ClockDomain_CAMCC_CAMCCMCLK3
 *   ClockDomain_CAMCC_CAMCCMCLK4
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCMCLK0[] =
{
  {   64000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCOPE0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCOPE0
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCOPE0[] =
{
  {  300000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  410000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  520000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  645000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  700000000, RAIL_VOLTAGE_LEVEL_TUR,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCPLLTESTSTAGE007MUX
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCPLLTESTSTAGE007MUX
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCPLLTESTSTAGE007MUX[] =
{
  {  875000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  { 1000000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCSLEEP
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCSLEEP
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCSLEEP[] =
{
  {      32000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCSLOWAHB
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCSLOWAHB
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCSLOWAHB[] =
{
  {   80000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCTFE0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCTFE0
 *   ClockDomain_CAMCC_CAMCCTFE1
 *   ClockDomain_CAMCC_CAMCCTFE2
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCTFE0[] =
{
  {  350000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  570000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  600000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  725000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCXO
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCXO
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCXO[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSAHB
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSAHB
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSAHB[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {   37500000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {   75000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSBYTE0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSBYTE0
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSBYTE0[] =
{
  {  187500000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  300000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  358000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX
 *   ClockDomain_DISPCC_DISPCCMDSSESC0
 *   ClockDomain_DISPCC_DISPCCMDSSVSYNC
 *   ClockDomain_DISPCC_DISPCCXO
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0LINK
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0LINK[] =
{
  {  270000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  540000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  810000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0[] =
{
  {  337500000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  405000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  675000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSMDP
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSMDP
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSMDP[] =
{
  {  200000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  342000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  402000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  535000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  600000000, RAIL_VOLTAGE_LEVEL_NOM_L1,     },
  {  630000000, RAIL_VOLTAGE_LEVEL_TUR,        },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSPCLK0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSPCLK0
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSPCLK0[] =
{
  {  300000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  480000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  625000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCPLLTESTMUX
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCPLLTESTMUX
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCPLLTESTMUX[] =
{
  {  500000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  { 1000000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCSLEEP
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCSLEEP
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCSLEEP[] =
{
  {      32000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCGP1
 *
 * Used by:
 *   ClockDomain_GCC_GCCGP1
 *   ClockDomain_GCC_GCCGP2
 *   ClockDomain_GCC_GCCGP3
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCGP1[] =
{
  {   50000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  100000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  200000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCPCIE0AUX
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE0AUX
 *   ClockDomain_GCC_GCCPCIE1AUX
 *   ClockDomain_GCC_GCCUFSPHYPHYAUX
 *   ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI
 *   ClockDomain_GCC_GCCUSB3PRIMPHYAUX
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCPCIE0AUX[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCPCIE0PHYRCHNG
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE0PHYRCHNG
 *   ClockDomain_GCC_GCCPCIE1PHYRCHNG
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCPCIE0PHYRCHNG[] =
{
  {  100000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCPCIE0PIPE
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE0PIPE
 *   ClockDomain_GCC_GCCPCIE1PIPE
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCPCIE0PIPE[] =
{
  {  250000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCPDM2
 *
 * Used by:
 *   ClockDomain_GCC_GCCPDM2
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCPDM2[] =
{
  {   60000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCQUPV3WRAP0QSPIREF
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP0QSPIREF
 *   ClockDomain_GCC_GCCQUPV3WRAP1QSPIREF
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCQUPV3WRAP0QSPIREF[] =
{
  {  150000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  200000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCQUPV3WRAP0S0
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP0S0
 *   ClockDomain_GCC_GCCQUPV3WRAP0S1
 *   ClockDomain_GCC_GCCQUPV3WRAP1S0
 *   ClockDomain_GCC_GCCQUPV3WRAP1S1
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCQUPV3WRAP0S0[] =
{
  {   75000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  120000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCQUPV3WRAP0S3
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP0S3
 *   ClockDomain_GCC_GCCQUPV3WRAP0S5
 *   ClockDomain_GCC_GCCQUPV3WRAP0S6
 *   ClockDomain_GCC_GCCQUPV3WRAP1S3
 *   ClockDomain_GCC_GCCQUPV3WRAP1S5
 *   ClockDomain_GCC_GCCQUPV3WRAP1S6
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCQUPV3WRAP0S3[] =
{
  {   75000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  100000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCQUPV3WRAP0S4
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP0S4
 *   ClockDomain_GCC_GCCQUPV3WRAP1S4
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCQUPV3WRAP0S4[] =
{
  {  128000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCSDCC1APPS
 *
 * Used by:
 *   ClockDomain_GCC_GCCSDCC1APPS
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCSDCC1APPS[] =
{
  {  100000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  384000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCSDCC1ICECORE
 *
 * Used by:
 *   ClockDomain_GCC_GCCSDCC1ICECORE
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCSDCC1ICECORE[] =
{
  {  100000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  150000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  300000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCSDCC2APPS
 *
 * Used by:
 *   ClockDomain_GCC_GCCSDCC2APPS
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCSDCC2APPS[] =
{
  {  100000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  202000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCUFSPHYAXI
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYAXI
 *   ClockDomain_GCC_GCCUFSPHYUNIPROCORE
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCUFSPHYAXI[] =
{
  {   75000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  150000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  300000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCUFSPHYICECORE
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYICECORE
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCUFSPHYICECORE[] =
{
  {  100000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  201500000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  403000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCUFSPHYRXSYMBOL0
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYRXSYMBOL0
 *   ClockDomain_GCC_GCCUFSPHYRXSYMBOL1
 *   ClockDomain_GCC_GCCUFSPHYTXSYMBOL0
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCUFSPHYRXSYMBOL0[] =
{
  {   75000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  150000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  300000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCUSB30PRIMMASTER
 *
 * Used by:
 *   ClockDomain_GCC_GCCUSB30PRIMMASTER
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCUSB30PRIMMASTER[] =
{
  {   66666667, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  133333333, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  200000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  240000000, RAIL_VOLTAGE_LEVEL_TUR,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCUSB3PRIMPHYPIPE
 *
 * Used by:
 *   ClockDomain_GCC_GCCUSB3PRIMPHYPIPE
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCUSB3PRIMPHYPIPE[] =
{
  {  125000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_GPUCC_GPUCCDEBUGMUX
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCDEBUGMUX
 */
static const ClockFMaxType ClockDomainFMax_GPUCC_GPUCCDEBUGMUX[] =
{
  {  350000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  650000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  687500000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_GPUCC_GPUCCFF
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCFF
 */
static const ClockFMaxType ClockDomainFMax_GPUCC_GPUCCFF[] =
{
  {  200000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_GPUCC_GPUCCGMU
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCGMU
 */
static const ClockFMaxType ClockDomainFMax_GPUCC_GPUCCGMU[] =
{
  {  350000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  650000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  687500000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_GPUCC_GPUCCHUB
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCHUB
 */
static const ClockFMaxType ClockDomainFMax_GPUCC_GPUCCHUB[] =
{
  {  200000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  300000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  400000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_GPUCC_GPUCCPLLTESTMUX
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCPLLTESTMUX
 */
static const ClockFMaxType ClockDomainFMax_GPUCC_GPUCCPLLTESTMUX[] =
{
  {  500000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  { 1000000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_GPUCC_GPUCCXO
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCXO
 */
static const ClockFMaxType ClockDomainFMax_GPUCC_GPUCCXO[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_GXCLKCTL_GXCLKCTLDEBUGMUX
 *
 * Used by:
 *   ClockDomain_GXCLKCTL_GXCLKCTLDEBUGMUX
 */
static const ClockFMaxType ClockDomainFMax_GXCLKCTL_GXCLKCTLDEBUGMUX[] =
{
  {  291000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  395000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  543000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  677000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  727000000, RAIL_VOLTAGE_LEVEL_SVS_L2,     },
  {  807000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  895000000, RAIL_VOLTAGE_LEVEL_NOM_L1,     },
  {  960000000, RAIL_VOLTAGE_LEVEL_TUR,        },
  { 1050000000, RAIL_VOLTAGE_LEVEL_TUR_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_GXCLKCTL_GXCLKCTLGXGFX3D
 *
 * Used by:
 *   ClockDomain_GXCLKCTL_GXCLKCTLGXGFX3D
 */
static const ClockFMaxType ClockDomainFMax_GXCLKCTL_GXCLKCTLGXGFX3D[] =
{
  {  291000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  395000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  543000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  677000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  727000000, RAIL_VOLTAGE_LEVEL_SVS_L2,     },
  {  807000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  895000000, RAIL_VOLTAGE_LEVEL_NOM_L1,     },
  {  960000000, RAIL_VOLTAGE_LEVEL_TUR,        },
  { 1050000000, RAIL_VOLTAGE_LEVEL_TUR_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_GXCLKCTL_GXCLKCTLPLLTESTMUX
 *
 * Used by:
 *   ClockDomain_GXCLKCTL_GXCLKCTLPLLTESTMUX
 */
static const ClockFMaxType ClockDomainFMax_GXCLKCTL_GXCLKCTLPLLTESTMUX[] =
{
  {  500000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  { 1000000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_GXCLKCTL_GXCLKCTLXO
 *
 * Used by:
 *   ClockDomain_GXCLKCTL_GXCLKCTLXO
 */
static const ClockFMaxType ClockDomainFMax_GXCLKCTL_GXCLKCTLXO[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  0  }
};

/*
 * ClockDomainFMax_VIDEOCC_VIDEOCCAHB
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCAHB
 *   ClockDomain_VIDEOCC_VIDEOCCXO
 */
static const ClockFMaxType ClockDomainFMax_VIDEOCC_VIDEOCCAHB[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_VIDEOCC_VIDEOCCMVS0
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCMVS0
 */
static const ClockFMaxType ClockDomainFMax_VIDEOCC_VIDEOCCMVS0[] =
{
  {  720000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  { 1014000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  { 1098000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  { 1332000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  { 1656000000, RAIL_VOLTAGE_LEVEL_TUR,        },
  {  0  }
};

/*
 * ClockDomainFMax_VIDEOCC_VIDEOCCPLLTESTMUX
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCPLLTESTMUX
 */
static const ClockFMaxType ClockDomainFMax_VIDEOCC_VIDEOCCPLLTESTMUX[] =
{
  {  800000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  { 1000000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_VIDEOCC_VIDEOCCSLEEP
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCSLEEP
 */
static const ClockFMaxType ClockDomainFMax_VIDEOCC_VIDEOCCSLEEP[] =
{
  {      32000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};


/*=========================================================================
      Domains
==========================================================================*/

static ClockDomainNodeType ClockDomain_APSSCC_APSSCCDEBUGMUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_APSSCC_APSSCCDEBUGMUX,
  .aSourceMap = ClockSourceMap_APSSCC_APSSCCDEBUGMUX,
  .pSource   = NULL,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(APSS_CC_DEBUG_MUX_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCBPS =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCBPS,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCBPS),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCBPS,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_BPS_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCAMNOCAXI =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCAMNOCAXI,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCAMNOCAXI),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCAMNOCAXI,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXI,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CAMNOC_AXI_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCCI0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCCI0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCCI0),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCCI0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCCI0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CCI_0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCCI1 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCCI0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCCI0),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCCI0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCCI0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CCI_1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCPHYRX =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCPHYRX,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCPHYRX),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCPHYRX,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXI,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CPHY_RX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCRE =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCRE,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCRE),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCRE,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CRE_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCSI0PHYTIMER =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXI,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CSI0PHYTIMER_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCSI1PHYTIMER =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXI,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CSI1PHYTIMER_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCSI2PHYTIMER =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXI,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CSI2PHYTIMER_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCSI3PHYTIMER =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXI,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CSI3PHYTIMER_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCDEBUGMUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCDEBUGMUX,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCDEBUGMUX,
  .pSource   = NULL,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_DEBUG_MUX_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCFASTAHB =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCFASTAHB,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCFASTAHB),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCFASTAHB,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXI,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_FAST_AHB_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCICP =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCICP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCICP),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCICP,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCICP,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_ICP_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCMCLK0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCMCLK0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCMCLK0),
  .nRailMask = RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCMCLK0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCMCLK0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_MCLK0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCMCLK1 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCMCLK0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCMCLK0),
  .nRailMask = RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCMCLK0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCMCLK0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_MCLK1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCMCLK2 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCMCLK0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCMCLK0),
  .nRailMask = RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCMCLK0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCMCLK0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_MCLK2_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCMCLK3 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCMCLK0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCMCLK0),
  .nRailMask = RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCMCLK0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCMCLK0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_MCLK3_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCMCLK4 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCMCLK0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCMCLK0),
  .nRailMask = RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCMCLK0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCMCLK0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_MCLK4_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCOPE0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCOPE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCOPE0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCOPE0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCOPE0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_OPE_0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCPLLTESTSTAGE007MUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCPLLTESTSTAGE007MUX,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCPLLTESTSTAGE007MUX,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = 0,
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCSLEEP =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCSLEEP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCSLEEP),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCSLEEP,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCSLEEP,
  .pSource   = NULL,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_SLEEP_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCSLOWAHB =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCSLOWAHB,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCSLOWAHB),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCSLOWAHB,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXI,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_SLOW_AHB_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCTFE0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCTFE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCTFE0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCTFE0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCTFE0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_TFE_0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCTFE0CSID =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCPHYRX,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCPHYRX),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCPHYRX,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXI,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_TFE_0_CSID_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCTFE1 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCTFE1,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCTFE1),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCTFE0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCTFE1,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_TFE_1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCTFE1CSID =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCPHYRX,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCPHYRX),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCPHYRX,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXI,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_TFE_1_CSID_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCTFE2 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCTFE2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCTFE2),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCTFE0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCTFE2,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_TFE_2_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCTFE2CSID =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCPHYRX,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCPHYRX),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCPHYRX,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXI,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_TFE_2_CSID_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCXO =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCXO,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCXO,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_XO_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSAHB =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSAHB,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSAHB),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSAHB,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSAHB,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_AHB_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSBYTE0 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSBYTE0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSBYTE0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_BYTE0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0AUX,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX0_AUX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSDPTX0LINK,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSDPTX0LINK),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0LINK,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0LINK,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX0_LINK_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSDPTX0PIXEL0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX0_PIXEL0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSDPTX0PIXEL0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX0_PIXEL1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSESC0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSESC0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_ESC0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSMDP =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSMDP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSMDP),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSMDP,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSMDP,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_MDP_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSPCLK0 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSPCLK0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSPCLK0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSPCLK0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSBYTE0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_PCLK0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSVSYNC =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0AUX,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_VSYNC_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCPLLTESTMUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCPLLTESTMUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCPLLTESTMUX,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_PLL_TEST_MUX_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCSLEEP =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCSLEEP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCSLEEP),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCSLEEP,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCSLEEP,
  .pSource   = NULL,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_SLEEP_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCXO =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0AUX,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_XO_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_CLOCKDRIVERGENXO =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = 0x0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = 0,
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = 0x0,
  .pSource   = NULL,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = 0,
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCAGGRENOC =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_AGGRE_NOC_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCAGGRENOCPCIE =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_AGGRE_NOC_PCIE_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCAGGRENOCSOUTHSF =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_AGGRE_NOC_SOUTH_SF_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCCNOCPERIPH =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_CNOC_PERIPH_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCCNOCSOUTHQX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_CNOC_SOUTH_QX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCCONFIGNOC =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_CONFIG_NOC_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCGP1 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCGP1,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCGP1),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCGP1,
  .aSourceMap = ClockSourceMap_GCC_GCCGP1,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_GP1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCGP2 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCGP1,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCGP1),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCGP1,
  .aSourceMap = ClockSourceMap_GCC_GCCGP1,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_GP2_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCGP3 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCGP1,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCGP1),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCGP1,
  .aSourceMap = ClockSourceMap_GCC_GCCGP1,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_GP3_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCGPUMEMNOCGFX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_GPU_MEMNOC_GFX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCMMNOCHFQX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_MMNOC_HF_QX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCMMNOCSFQX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_MMNOC_SF_QX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCPCIE0AUX =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCPCIE0AUX,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_PCIE_0_AUX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCPCIE0PHYRCHNG =
{
  .aBSP      = ClockDomainBSP_GCC_GCCPCIE0PHYRCHNG,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCPCIE0PHYRCHNG),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0PHYRCHNG,
  .aSourceMap = ClockSourceMap_GCC_GCCPCIE0PHYRCHNG,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_PCIE_0_PHY_RCHNG_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCPCIE0PIPE =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0PIPE,
  .aSourceMap = ClockSourceMap_GCC_GCCPCIE0PIPE,
  .pSource   = NULL,
  .nFlags    = CLOCK_FLAG_DOMAIN_FORCE_SETTINGS,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_PCIE_0_PIPE_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCPCIE1AUX =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCPCIE0AUX,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_PCIE_1_AUX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCPCIE1PHYRCHNG =
{
  .aBSP      = ClockDomainBSP_GCC_GCCPCIE0PHYRCHNG,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCPCIE0PHYRCHNG),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0PHYRCHNG,
  .aSourceMap = ClockSourceMap_GCC_GCCPCIE0PHYRCHNG,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_PCIE_1_PHY_RCHNG_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCPCIE1PIPE =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0PIPE,
  .aSourceMap = ClockSourceMap_GCC_GCCPCIE1PIPE,
  .pSource   = NULL,
  .nFlags    = CLOCK_FLAG_DOMAIN_FORCE_SETTINGS,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_PCIE_1_PIPE_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCPDM2 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCPDM2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCPDM2),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPDM2,
  .aSourceMap = ClockSourceMap_GCC_GCCPDM2,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_PDM2_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQDSSAPBTSCTR =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCUSB30PRIMMOCKUTMI,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QDSS_APB_TSCTR_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQDSSATBA =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QDSS_ATB_A_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQDSSATBB =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QDSS_ATB_B_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQDSSTRIG =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QDSS_TRIG_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0CORE2X =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP0_CORE_2X_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0QSPIREF =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0QSPIREF,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0QSPIREF),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0QSPIREF,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0QSPIREF,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP0_QSPI_REF_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S0 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S0,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0QSPIREF,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP0_S0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S1 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S0,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0QSPIREF,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP0_S1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S3 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S3,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S3),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S3,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0QSPIREF,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP0_S3_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S4 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S4,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S4),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S4,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0S4,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP0_S4_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S5 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S3,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S3),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S3,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0QSPIREF,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP0_S5_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S6 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S6,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S6),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S3,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0QSPIREF,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP0_S6_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1CORE2X =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_CORE_2X_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1QSPIREF =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0QSPIREF,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0QSPIREF),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0QSPIREF,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP1QSPIREF,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_QSPI_REF_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S0 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S0,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP1QSPIREF,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_S0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S1 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S0,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP1QSPIREF,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_S1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S3 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S6,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S6),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S3,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP1QSPIREF,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_S3_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S4 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S4,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S4),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S4,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP1S4,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_S4_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S5 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S3,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S3),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S3,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP1QSPIREF,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_S5_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S6 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S3,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S3),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S3,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP1S6,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_S6_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCSDCC1APPS =
{
  .aBSP      = ClockDomainBSP_GCC_GCCSDCC1APPS,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCSDCC1APPS),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCSDCC1APPS,
  .aSourceMap = ClockSourceMap_GCC_GCCSDCC1APPS,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_SDCC1_APPS_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCSDCC1ICECORE =
{
  .aBSP      = ClockDomainBSP_GCC_GCCSDCC1ICECORE,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCSDCC1ICECORE),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCSDCC1ICECORE,
  .aSourceMap = ClockSourceMap_GCC_GCCSDCC1ICECORE,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_SDCC1_ICE_CORE_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCSDCC2APPS =
{
  .aBSP      = ClockDomainBSP_GCC_GCCSDCC2APPS,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCSDCC2APPS),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCSDCC2APPS,
  .aSourceMap = ClockSourceMap_GCC_GCCSDCC2APPS,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_SDCC2_APPS_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCSLEEP =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .pSource   = NULL,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_SLEEP_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCSYSNOC =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_SYS_NOC_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYAXI =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUFSPHYAXI,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUFSPHYAXI),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCUFSPHYAXI,
  .aSourceMap = ClockSourceMap_GCC_GCCUFSPHYAXI,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_UFS_PHY_AXI_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYICECORE =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUFSPHYICECORE,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUFSPHYICECORE),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCUFSPHYICECORE,
  .aSourceMap = ClockSourceMap_GCC_GCCUFSPHYICECORE,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_UFS_PHY_ICE_CORE_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYPHYAUX =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCUFSPHYPHYAUX,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_UFS_PHY_PHY_AUX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYRXSYMBOL0 =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCUFSPHYRXSYMBOL0,
  .aSourceMap = ClockSourceMap_GCC_GCCUFSPHYRXSYMBOL0,
  .pSource   = NULL,
  .nFlags    = CLOCK_FLAG_DOMAIN_FORCE_SETTINGS,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_UFS_PHY_RX_SYMBOL_0_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYRXSYMBOL1 =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCUFSPHYRXSYMBOL0,
  .aSourceMap = ClockSourceMap_GCC_GCCUFSPHYRXSYMBOL1,
  .pSource   = NULL,
  .nFlags    = CLOCK_FLAG_DOMAIN_FORCE_SETTINGS,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_UFS_PHY_RX_SYMBOL_1_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYTXSYMBOL0 =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCUFSPHYRXSYMBOL0,
  .aSourceMap = ClockSourceMap_GCC_GCCUFSPHYTXSYMBOL0,
  .pSource   = NULL,
  .nFlags    = CLOCK_FLAG_DOMAIN_FORCE_SETTINGS,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_UFS_PHY_TX_SYMBOL_0_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYUNIPROCORE =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUFSPHYAXI,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUFSPHYAXI),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCUFSPHYAXI,
  .aSourceMap = ClockSourceMap_GCC_GCCUFSPHYAXI,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_UFS_PHY_UNIPRO_CORE_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUSB30PRIMMASTER =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUSB30PRIMMASTER,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUSB30PRIMMASTER),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCUSB30PRIMMASTER,
  .aSourceMap = ClockSourceMap_GCC_GCCUSB30PRIMMASTER,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_USB30_PRIM_MASTER_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCUSB30PRIMMOCKUTMI,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_USB30_PRIM_MOCK_UTMI_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUSB3PRIMPHYAUX =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCPCIE0AUX,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_USB3_PRIM_PHY_AUX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUSB3PRIMPHYPIPE =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCUSB3PRIMPHYPIPE,
  .aSourceMap = ClockSourceMap_GCC_GCCUSB3PRIMPHYPIPE,
  .pSource   = NULL,
  .nFlags    = CLOCK_FLAG_DOMAIN_FORCE_SETTINGS,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_USB3_PRIM_PHY_PIPE_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCXO =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCUFSPHYPHYAUX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_XO_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GPUCC_GPUCCDEBUGMUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GPUCC_GPUCCDEBUGMUX,
  .aSourceMap = ClockSourceMap_GPUCC_GPUCCDEBUGMUX,
  .pSource   = NULL,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPUCC_GPU_CC_DEBUG_MUX_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_GPUCC_GPUCCFF =
{
  .aBSP      = ClockDomainBSP_GPUCC_GPUCCFF,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GPUCC_GPUCCFF),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GPUCC_GPUCCFF,
  .aSourceMap = ClockSourceMap_GPUCC_GPUCCFF,
  .pSource   = NULL,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPUCC_GPU_CC_FF_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GPUCC_GPUCCGMU =
{
  .aBSP      = ClockDomainBSP_GPUCC_GPUCCGMU,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GPUCC_GPUCCGMU),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GPUCC_GPUCCGMU,
  .aSourceMap = ClockSourceMap_GPUCC_GPUCCGMU,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPUCC_GPU_CC_GMU_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GPUCC_GPUCCHUB =
{
  .aBSP      = ClockDomainBSP_GPUCC_GPUCCHUB,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GPUCC_GPUCCHUB),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GPUCC_GPUCCHUB,
  .aSourceMap = ClockSourceMap_GPUCC_GPUCCGMU,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPUCC_GPU_CC_HUB_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GPUCC_GPUCCPLLTESTMUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GPUCC_GPUCCPLLTESTMUX,
  .aSourceMap = ClockSourceMap_GPUCC_GPUCCPLLTESTMUX,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPUCC_GPU_CC_PLL_TEST_MUX_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_GPUCC_GPUCCXO =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GPUCC_GPUCCXO,
  .aSourceMap = ClockSourceMap_GPUCC_GPUCCXO,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPUCC_GPU_CC_XO_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GXCLKCTL_GXCLKCTLDEBUGMUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_GFX,
  .aFMax     = ClockDomainFMax_GXCLKCTL_GXCLKCTLDEBUGMUX,
  .aSourceMap = ClockSourceMap_GXCLKCTL_GXCLKCTLDEBUGMUX,
  .pSource   = NULL,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPU_GX_CLKCTL_DEBUG_MUX_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_GXCLKCTL_GXCLKCTLGXGFX3D =
{
  .aBSP      = ClockDomainBSP_GXCLKCTL_GXCLKCTLGXGFX3D,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GXCLKCTL_GXCLKCTLGXGFX3D),
  .nRailMask = RAIL_VDD_GFX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GXCLKCTL_GXCLKCTLGXGFX3D,
  .aSourceMap = ClockSourceMap_GXCLKCTL_GXCLKCTLGXGFX3D,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPU_GX_CLKCTL_GX_GFX3D_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GXCLKCTL_GXCLKCTLPLLTESTMUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_GFX,
  .aFMax     = ClockDomainFMax_GXCLKCTL_GXCLKCTLPLLTESTMUX,
  .aSourceMap = ClockSourceMap_GXCLKCTL_GXCLKCTLPLLTESTMUX,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = 0,
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_GXCLKCTL_GXCLKCTLXO =
{
  .aBSP      = ClockDomainBSP_GXCLKCTL_GXCLKCTLXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GXCLKCTL_GXCLKCTLXO),
  .nRailMask = RAIL_VDD_GFX,
  .aFMax     = ClockDomainFMax_GXCLKCTL_GXCLKCTLXO,
  .aSourceMap = ClockSourceMap_GXCLKCTL_GXCLKCTLXO,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPU_GX_CLKCTL_XO_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_VIDEOCC_VIDEOCCAHB =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_VIDEOCC_VIDEOCCAHB,
  .aSourceMap = ClockSourceMap_VIDEOCC_VIDEOCCAHB,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(VCODEC_VIDEO_CC_AHB_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_VIDEOCC_VIDEOCCMVS0 =
{
  .aBSP      = ClockDomainBSP_VIDEOCC_VIDEOCCMVS0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_VIDEOCC_VIDEOCCMVS0),
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_VIDEOCC_VIDEOCCMVS0,
  .aSourceMap = ClockSourceMap_VIDEOCC_VIDEOCCMVS0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(VCODEC_VIDEO_CC_MVS0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_VIDEOCC_VIDEOCCPLLTESTMUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_VIDEOCC_VIDEOCCPLLTESTMUX,
  .aSourceMap = ClockSourceMap_VIDEOCC_VIDEOCCPLLTESTMUX,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(VCODEC_VIDEO_CC_PLL_TEST_MUX_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_VIDEOCC_VIDEOCCSLEEP =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCSLEEP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCSLEEP),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_VIDEOCC_VIDEOCCSLEEP,
  .aSourceMap = ClockSourceMap_VIDEOCC_VIDEOCCSLEEP,
  .pSource   = NULL,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(VCODEC_VIDEO_CC_SLEEP_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_VIDEOCC_VIDEOCCXO =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_VIDEOCC_VIDEOCCAHB,
  .aSourceMap = ClockSourceMap_VIDEOCC_VIDEOCCAHB,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(VCODEC_VIDEO_CC_XO_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};


static ClockDomainNodeType *aDomains[] =
{
  &ClockDomain_APSSCC_APSSCCDEBUGMUX,
  &ClockDomain_CAMCC_CAMCCBPS,
  &ClockDomain_CAMCC_CAMCCCAMNOCAXI,
  &ClockDomain_CAMCC_CAMCCCCI0,
  &ClockDomain_CAMCC_CAMCCCCI1,
  &ClockDomain_CAMCC_CAMCCCPHYRX,
  &ClockDomain_CAMCC_CAMCCCRE,
  &ClockDomain_CAMCC_CAMCCCSI0PHYTIMER,
  &ClockDomain_CAMCC_CAMCCCSI1PHYTIMER,
  &ClockDomain_CAMCC_CAMCCCSI2PHYTIMER,
  &ClockDomain_CAMCC_CAMCCCSI3PHYTIMER,
  &ClockDomain_CAMCC_CAMCCDEBUGMUX,
  &ClockDomain_CAMCC_CAMCCFASTAHB,
  &ClockDomain_CAMCC_CAMCCICP,
  &ClockDomain_CAMCC_CAMCCMCLK0,
  &ClockDomain_CAMCC_CAMCCMCLK1,
  &ClockDomain_CAMCC_CAMCCMCLK2,
  &ClockDomain_CAMCC_CAMCCMCLK3,
  &ClockDomain_CAMCC_CAMCCMCLK4,
  &ClockDomain_CAMCC_CAMCCOPE0,
  &ClockDomain_CAMCC_CAMCCPLLTESTSTAGE007MUX,
  &ClockDomain_CAMCC_CAMCCSLEEP,
  &ClockDomain_CAMCC_CAMCCSLOWAHB,
  &ClockDomain_CAMCC_CAMCCTFE0,
  &ClockDomain_CAMCC_CAMCCTFE0CSID,
  &ClockDomain_CAMCC_CAMCCTFE1,
  &ClockDomain_CAMCC_CAMCCTFE1CSID,
  &ClockDomain_CAMCC_CAMCCTFE2,
  &ClockDomain_CAMCC_CAMCCTFE2CSID,
  &ClockDomain_CAMCC_CAMCCXO,
  &ClockDomain_DISPCC_DISPCCMDSSAHB,
  &ClockDomain_DISPCC_DISPCCMDSSBYTE0,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1,
  &ClockDomain_DISPCC_DISPCCMDSSESC0,
  &ClockDomain_DISPCC_DISPCCMDSSMDP,
  &ClockDomain_DISPCC_DISPCCMDSSPCLK0,
  &ClockDomain_DISPCC_DISPCCMDSSVSYNC,
  &ClockDomain_DISPCC_DISPCCPLLTESTMUX,
  &ClockDomain_DISPCC_DISPCCSLEEP,
  &ClockDomain_DISPCC_DISPCCXO,
  &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
  &ClockDomain_GCC_CLOCKDRIVERGENXO,
  &ClockDomain_GCC_GCCAGGRENOC,
  &ClockDomain_GCC_GCCAGGRENOCPCIE,
  &ClockDomain_GCC_GCCAGGRENOCSOUTHSF,
  &ClockDomain_GCC_GCCCNOCPERIPH,
  &ClockDomain_GCC_GCCCNOCSOUTHQX,
  &ClockDomain_GCC_GCCCONFIGNOC,
  &ClockDomain_GCC_GCCGP1,
  &ClockDomain_GCC_GCCGP2,
  &ClockDomain_GCC_GCCGP3,
  &ClockDomain_GCC_GCCGPUMEMNOCGFX,
  &ClockDomain_GCC_GCCMMNOCHFQX,
  &ClockDomain_GCC_GCCMMNOCSFQX,
  &ClockDomain_GCC_GCCPCIE0AUX,
  &ClockDomain_GCC_GCCPCIE0PHYRCHNG,
  &ClockDomain_GCC_GCCPCIE0PIPE,
  &ClockDomain_GCC_GCCPCIE1AUX,
  &ClockDomain_GCC_GCCPCIE1PHYRCHNG,
  &ClockDomain_GCC_GCCPCIE1PIPE,
  &ClockDomain_GCC_GCCPDM2,
  &ClockDomain_GCC_GCCQDSSAPBTSCTR,
  &ClockDomain_GCC_GCCQDSSATBA,
  &ClockDomain_GCC_GCCQDSSATBB,
  &ClockDomain_GCC_GCCQDSSTRIG,
  &ClockDomain_GCC_GCCQUPV3WRAP0CORE2X,
  &ClockDomain_GCC_GCCQUPV3WRAP0QSPIREF,
  &ClockDomain_GCC_GCCQUPV3WRAP0S0,
  &ClockDomain_GCC_GCCQUPV3WRAP0S1,
  &ClockDomain_GCC_GCCQUPV3WRAP0S3,
  &ClockDomain_GCC_GCCQUPV3WRAP0S4,
  &ClockDomain_GCC_GCCQUPV3WRAP0S5,
  &ClockDomain_GCC_GCCQUPV3WRAP0S6,
  &ClockDomain_GCC_GCCQUPV3WRAP1CORE2X,
  &ClockDomain_GCC_GCCQUPV3WRAP1QSPIREF,
  &ClockDomain_GCC_GCCQUPV3WRAP1S0,
  &ClockDomain_GCC_GCCQUPV3WRAP1S1,
  &ClockDomain_GCC_GCCQUPV3WRAP1S3,
  &ClockDomain_GCC_GCCQUPV3WRAP1S4,
  &ClockDomain_GCC_GCCQUPV3WRAP1S5,
  &ClockDomain_GCC_GCCQUPV3WRAP1S6,
  &ClockDomain_GCC_GCCSDCC1APPS,
  &ClockDomain_GCC_GCCSDCC1ICECORE,
  &ClockDomain_GCC_GCCSDCC2APPS,
  &ClockDomain_GCC_GCCSLEEP,
  &ClockDomain_GCC_GCCSYSNOC,
  &ClockDomain_GCC_GCCUFSPHYAXI,
  &ClockDomain_GCC_GCCUFSPHYICECORE,
  &ClockDomain_GCC_GCCUFSPHYPHYAUX,
  &ClockDomain_GCC_GCCUFSPHYRXSYMBOL0,
  &ClockDomain_GCC_GCCUFSPHYRXSYMBOL1,
  &ClockDomain_GCC_GCCUFSPHYTXSYMBOL0,
  &ClockDomain_GCC_GCCUFSPHYUNIPROCORE,
  &ClockDomain_GCC_GCCUSB30PRIMMASTER,
  &ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI,
  &ClockDomain_GCC_GCCUSB3PRIMPHYAUX,
  &ClockDomain_GCC_GCCUSB3PRIMPHYPIPE,
  &ClockDomain_GCC_GCCXO,
  &ClockDomain_GPUCC_GPUCCDEBUGMUX,
  &ClockDomain_GPUCC_GPUCCFF,
  &ClockDomain_GPUCC_GPUCCGMU,
  &ClockDomain_GPUCC_GPUCCHUB,
  &ClockDomain_GPUCC_GPUCCPLLTESTMUX,
  &ClockDomain_GPUCC_GPUCCXO,
  &ClockDomain_GXCLKCTL_GXCLKCTLDEBUGMUX,
  &ClockDomain_GXCLKCTL_GXCLKCTLGXGFX3D,
  &ClockDomain_GXCLKCTL_GXCLKCTLPLLTESTMUX,
  &ClockDomain_GXCLKCTL_GXCLKCTLXO,
  &ClockDomain_VIDEOCC_VIDEOCCAHB,
  &ClockDomain_VIDEOCC_VIDEOCCMVS0,
  &ClockDomain_VIDEOCC_VIDEOCCPLLTESTMUX,
  &ClockDomain_VIDEOCC_VIDEOCCSLEEP,
  &ClockDomain_VIDEOCC_VIDEOCCXO,
};


/*=========================================================================
      Clocks
==========================================================================*/

static ClockNodeType aClocks[] =
{
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCBPS                                            */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_bps_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCBPS,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x2FE00ED4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_BPS_CBCR), HWIO_PHYS(CAM_CC_BPS_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 14,
    },
  },
  {
    .szName    = "cam_cc_spdm_bps_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCBPS,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xF0BFA945,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SPDM_BPS_CBCR), HWIO_PHYS(CAM_CC_BPS_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 16,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCAMNOCAXI                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_camnoc_nrt_axi_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCAMNOCAXI,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x1372F670,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CAMNOC_NRT_AXI_CBCR), HWIO_PHYS(CAM_CC_CAMNOC_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 63,
    },
  },
  {
    .szName    = "cam_cc_camnoc_rt_axi_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCAMNOCAXI,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x4579B9A5,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CAMNOC_RT_AXI_CBCR), HWIO_PHYS(CAM_CC_CAMNOC_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 60,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCCI0                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_cci_0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCCI0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x2F0FA585,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CCI_0_CBCR), HWIO_PHYS(CAM_CC_CCI_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 53,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCCI1                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_cci_1_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCCI1,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x0072D990,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CCI_1_CBCR), HWIO_PHYS(CAM_CC_CCI_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 54,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCPHYRX                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_csiphy0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x5BD9C966,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSIPHY0_CBCR), HWIO_PHYS(CAM_CC_CSI0PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 7,
    },
  },
  {
    .szName    = "cam_cc_csiphy1_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD1C62B7E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSIPHY1_CBCR), HWIO_PHYS(CAM_CC_CSI1PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 9,
    },
  },
  {
    .szName    = "cam_cc_csiphy2_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xFB341D3F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSIPHY2_CBCR), HWIO_PHYS(CAM_CC_CSI2PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 11,
    },
  },
  {
    .szName    = "cam_cc_csiphy3_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x29439ED4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSIPHY3_CBCR), HWIO_PHYS(CAM_CC_CSI3PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 13,
    },
  },
  {
    .szName    = "cam_cc_tfe_0_cphy_rx_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x9456AEBB,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_TFE_0_CPHY_RX_CBCR), HWIO_PHYS(CAM_CC_TFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 30,
    },
  },
  {
    .szName    = "cam_cc_tfe_1_cphy_rx_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x6A62B28C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_TFE_1_CPHY_RX_CBCR), HWIO_PHYS(CAM_CC_TFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 37,
    },
  },
  {
    .szName    = "cam_cc_tfe_2_cphy_rx_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x4C1ED3D9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_TFE_2_CPHY_RX_CBCR), HWIO_PHYS(CAM_CC_TFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 44,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCRE                                            */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_cre_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCRE,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x4B3A4DAF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CRE_CBCR), HWIO_PHYS(CAM_CC_CRE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 70,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCSI0PHYTIMER                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_csi0phytimer_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCSI0PHYTIMER,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xDF3E55F8,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSI0PHYTIMER_CBCR), HWIO_PHYS(CAM_CC_CSI0PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 6,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCSI1PHYTIMER                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_csi1phytimer_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCSI1PHYTIMER,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xBD91807B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSI1PHYTIMER_CBCR), HWIO_PHYS(CAM_CC_CSI1PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 8,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCSI2PHYTIMER                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_csi2phytimer_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCSI2PHYTIMER,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x411BC4E9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSI2PHYTIMER_CBCR), HWIO_PHYS(CAM_CC_CSI2PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 10,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCSI3PHYTIMER                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_csi3phytimer_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCSI3PHYTIMER,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD8F7C361,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSI3PHYTIMER_CBCR), HWIO_PHYS(CAM_CC_CSI3PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 12,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCDEBUGMUX                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_debug_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCDEBUGMUX,
    .pDebugMux = NULL,
    .nUniqueId = 0x8E6D4CE1,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_DEBUG_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCFASTAHB                                        */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_bps_areg_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x94A0ECE6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_BPS_AREG_CBCR), HWIO_PHYS(CAM_CC_BPS_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 17,
    },
  },
  {
    .szName    = "cam_cc_ope_0_areg_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xF69BF49D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_OPE_0_AREG_CBCR), HWIO_PHYS(CAM_CC_OPE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 22,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCICP                                            */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_icp_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCICP,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xFDC6BEB1,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_ICP_CBCR), HWIO_PHYS(CAM_CC_ICP_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 50,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCMCLK0                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_mclk0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCMCLK0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xAFDBB67A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK0_CBCR), HWIO_PHYS(CAM_CC_MCLK0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 1,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCMCLK1                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_mclk1_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCMCLK1,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x57396D81,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK1_CBCR), HWIO_PHYS(CAM_CC_MCLK1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 2,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCMCLK2                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_mclk2_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCMCLK2,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x70806571,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK2_CBCR), HWIO_PHYS(CAM_CC_MCLK2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 3,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCMCLK3                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_mclk3_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCMCLK3,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x35F364E9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK3_CBCR), HWIO_PHYS(CAM_CC_MCLK3_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 4,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCMCLK4                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_mclk4_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCMCLK4,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x315FF885,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK4_CBCR), HWIO_PHYS(CAM_CC_MCLK4_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 5,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCOPE0                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_ope_0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCOPE0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xEA77BE6E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_OPE_0_CBCR), HWIO_PHYS(CAM_CC_OPE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 19,
    },
  },
  {
    .szName    = "cam_cc_spdm_ope_0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCOPE0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x28060646,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SPDM_OPE_0_CBCR), HWIO_PHYS(CAM_CC_OPE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 21,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCPLLTESTSTAGE007MUX                             */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_pll_test_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCPLLTESTSTAGE007MUX,
    .pDebugMux = NULL,
    .nUniqueId = 0x519E3D27,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_PLL_TEST_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCSLEEP                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_sleep_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLEEP,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xCFDF030C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SLEEP_CBCR), HWIO_PHYS(CAM_CC_CAMSS_TOP_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 69,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCSLOWAHB                                        */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_bps_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xCE8465C2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_BPS_AHB_CBCR), HWIO_PHYS(CAM_CC_BPS_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 18,
    },
  },
  {
    .szName    = "cam_cc_core_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xA974C223,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CORE_AHB_CBCR), HWIO_PHYS(CAM_CC_CAMSS_TOP_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 66,
    },
  },
  {
    .szName    = "cam_cc_cpas_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x7E6C7824,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CPAS_AHB_CBCR), HWIO_PHYS(CAM_CC_CPAS_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 55,
    },
  },
  {
    .szName    = "cam_cc_cre_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x75FFE457,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CRE_AHB_CBCR), HWIO_PHYS(CAM_CC_CRE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 71,
    },
  },
  {
    .szName    = "cam_cc_ope_0_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD1A58733,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_OPE_0_AHB_CBCR), HWIO_PHYS(CAM_CC_OPE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 23,
    },
  },
  {
    .szName    = "cam_cc_tfe_0_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x8390C2B6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_TFE_0_AHB_CBCR), HWIO_PHYS(CAM_CC_TFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 31,
    },
  },
  {
    .szName    = "cam_cc_tfe_1_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xC39CFCE3,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_TFE_1_AHB_CBCR), HWIO_PHYS(CAM_CC_TFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 38,
    },
  },
  {
    .szName    = "cam_cc_tfe_2_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x30524714,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_TFE_2_AHB_CBCR), HWIO_PHYS(CAM_CC_TFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 45,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCTFE0                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_spdm_tfe_0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCTFE0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xBF9C16A1,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SPDM_TFE_0_CBCR), HWIO_PHYS(CAM_CC_TFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 26,
    },
  },
  {
    .szName    = "cam_cc_tfe_0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCTFE0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x18D01E50,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_TFE_0_CBCR), HWIO_PHYS(CAM_CC_TFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 24,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCTFE0CSID                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_spdm_tfe_0_csid_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCTFE0CSID,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xC20D2EE4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SPDM_TFE_0_CSID_CBCR), HWIO_PHYS(CAM_CC_TFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 29,
    },
  },
  {
    .szName    = "cam_cc_tfe_0_csid_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCTFE0CSID,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x49DC3A07,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_TFE_0_CSID_CBCR), HWIO_PHYS(CAM_CC_TFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 27,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCTFE1                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_spdm_tfe_1_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCTFE1,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xBB5115D2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SPDM_TFE_1_CBCR), HWIO_PHYS(CAM_CC_TFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 34,
    },
  },
  {
    .szName    = "cam_cc_tfe_1_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCTFE1,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xCB9B013A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_TFE_1_CBCR), HWIO_PHYS(CAM_CC_TFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 32,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCTFE1CSID                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_tfe_1_csid_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCTFE1CSID,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x9DC9C0DE,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_TFE_1_CSID_CBCR), HWIO_PHYS(CAM_CC_TFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 35,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCTFE2                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_spdm_tfe_2_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCTFE2,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xB5267DA4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SPDM_TFE_2_CBCR), HWIO_PHYS(CAM_CC_TFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 41,
    },
  },
  {
    .szName    = "cam_cc_tfe_2_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCTFE2,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x374E5F6B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_TFE_2_CBCR), HWIO_PHYS(CAM_CC_TFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 39,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCTFE2CSID                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_tfe_2_csid_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCTFE2CSID,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x081E3153,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_TFE_2_CSID_CBCR), HWIO_PHYS(CAM_CC_TFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 42,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCXO                                             */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_gdsc_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xC9FEBE6E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_GDSC_CBCR), HWIO_PHYS(CAM_CC_CAMSS_TOP_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 67,
    },
  },
  {
    .szName    = "cam_cc_sys_tmr_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x9FEA59D8,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SYS_TMR_CBCR), HWIO_PHYS(CAM_CC_ICP_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 52,
    },
  },
  {
    .szName    = "cam_cc_top_shift_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x83F06B75,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_TOP_SHIFT_CBCR), HWIO_PHYS(CAM_CC_CAMSS_TOP_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 68,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSAHB                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_ahb1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSAHB,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xBD9DA764,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_AHB1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_INT2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 93,
    },
  },
  {
    .szName    = "disp_cc_mdss_ahb_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSAHB,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xD86CF434,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_AHB_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 90,
    },
  },
  {
    .szName    = "disp_cc_mdss_non_gdsc_ahb_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSAHB,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xD594BB06,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_NON_GDSC_AHB_CBCR), HWIO_PHYS(DISP_CC_MDSS_RSCC_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 94,
    },
  },
  {
    .szName    = "disp_cc_mdss_rscc_ahb_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSAHB,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x23666C25,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_RSCC_AHB_CBCR), HWIO_PHYS(DISP_CC_MDSS_RSCC_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 95,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSBYTE0                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_byte0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSBYTE0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x62A800C1,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_BYTE0_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 36,
    },
  },
  {
    .szName    = "disp_cc_mdss_byte0_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSBYTE0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xEC7D494E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_BYTE0_INTF_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 37,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx0_aux_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xC2E18940,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX0_AUX_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 81,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx0_crypto_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xC95B6162,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX0_CRYPTO_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 51,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx0_link_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x15BD0141,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX0_LINK_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 48,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx0_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xEBAC4D27,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX0_LINK_INTF_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 50,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx0_usb_router_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xDFF7A70E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX0_USB_ROUTER_LINK_INTF_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 49,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_crypto_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x75EFBB45,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_SPDM_DP_CRYPTO_CBCR), HWIO_PHYS(DISP_CC_MDSS_SPDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 101,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx0_pixel0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x92F8B42B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX0_PIXEL0_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 60,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_pixel_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x72B57E57,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_SPDM_DP_PIXEL_CBCR), HWIO_PHYS(DISP_CC_MDSS_SPDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 56,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx0_pixel1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x5908B325,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX0_PIXEL1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 61,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_pixel1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x24157A60,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_SPDM_DP_PIXEL1_CBCR), HWIO_PHYS(DISP_CC_MDSS_SPDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 57,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSESC0                                     */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_esc0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSESC0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x4485FD1B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_ESC0_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 23,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSMDP                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_mdp1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSMDP,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x085D62A2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_MDP1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_INT2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 91,
    },
  },
  {
    .szName    = "disp_cc_mdss_mdp_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSMDP,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x6A10EA96,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_MDP_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 88,
    },
  },
  {
    .szName    = "disp_cc_mdss_mdp_lut1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSMDP,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x70F2ED4E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_MDP_LUT1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_INT2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 92,
    },
  },
  {
    .szName    = "disp_cc_mdss_mdp_lut_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSMDP,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xF02E7C9A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_MDP_LUT_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 89,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_mdp_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSMDP,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x8D7A3901,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_SPDM_MDP_CBCR), HWIO_PHYS(DISP_CC_MDSS_SPDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 100,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSPCLK0                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_pclk0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSPCLK0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xDF2F28DF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_PCLK0_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 32,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_pclk0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSPCLK0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x757CD20E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_SPDM_PCLK0_CBCR), HWIO_PHYS(DISP_CC_MDSS_SPDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 33,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSVSYNC                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_rscc_vsync_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSVSYNC,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x47CD7D13,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_RSCC_VSYNC_CBCR), HWIO_PHYS(DISP_CC_MDSS_RSCC_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 86,
    },
  },
  {
    .szName    = "disp_cc_mdss_vsync1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSVSYNC,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x106D4032,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_VSYNC1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_INT2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 85,
    },
  },
  {
    .szName    = "disp_cc_mdss_vsync_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSVSYNC,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x80004355,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_VSYNC_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 80,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCPLLTESTMUX                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_pll_test_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCPLLTESTMUX,
    .pDebugMux = NULL,
    .nUniqueId = 0x7D7A63ED,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_PLL_TEST_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCSLEEP                                        */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_sleep_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCSLEEP,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xE16C7ED9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_SLEEP_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 103,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCXO                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_accu_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCXO,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x2CB5F333,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_ACCU_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 112,
    },
  },
  {
    .szName    = "disp_cc_xo_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCXO,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x9C4A81EA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_XO_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 87,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_CLOCKDRIVERGENXO                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "bi_tcxo_gated_for_gx",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xE1229494,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_BI_TCXO_GATED_FOR_GX_ACGCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 22,
    },
  },
  {
    .szName    = "gcc_disp_gpll0_div_clk_src",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x27A6DF61,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_DISPLAY_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x800000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 141,
    },
  },
  {
    .szName    = "gcc_gpll0_ufs_phy_rx_symbol_0_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x106963AD,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GPLL0_UFS_PHY_RX_SYMBOL_0_ACGCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_gpll0_ufs_phy_rx_symbol_1_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x9A09B4DA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GPLL0_UFS_PHY_RX_SYMBOL_1_ACGCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_gpll0_ufs_phy_tx_symbol_0_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x098D4A5E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GPLL0_UFS_PHY_TX_SYMBOL_0_ACGCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_gpu_gpll0_clk_src",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x4B1A4AC7,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_GPU_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x8000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 395,
    },
  },
  {
    .szName    = "gcc_gpu_gpll0_div_clk_src",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x6EEEF079,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_GPU_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x10000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 396,
    },
  },
  {
    .szName    = "gcc_gpu_memnoc_gfx_clk_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0xCEE753AC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GPU_MEMNOC_GFX_CLK_EN), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_aggre_noc_mmu_pcie_qtb_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x28F54D89,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_AGGRE_NOC_MMU_PCIE_QTB_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_aggre_noc_mmu_qtb1_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0xAE4D1A85,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_AGGRE_NOC_MMU_QTB1_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_aggre_noc_mmu_qtb2_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x32CEE595,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_AGGRE_NOC_MMU_QTB2_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_all_smmu_mmu_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0xF26FB3CE,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_ALL_SMMU_MMU_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_gpu_smmu_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x4A750D50,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_GPU_SMMU_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_lpass_qtb_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0xD0D3E743,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_LPASS_QTB_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_mmnoc_mmu_qtb_hf01_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x783936F7,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_mmnoc_mmu_qtb_hf23_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0xFE40C8DA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_mmnoc_mmu_qtb_sf_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x585A9AF6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_mmu_tcu_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x45B7596F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_MMU_TCU_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_turing_mmu_qtb0_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0xD20C70A8,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_TURING_MMU_QTB0_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gpu_cc_cb_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x721C91D0,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CB_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CB_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 40,
    },
  },
  {
    .szName    = "gpu_cc_cx_apb_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x6E5557EC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_APB_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 26,
    },
  },
  {
    .szName    = "gpu_cc_cx_qdss_tsctr_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x403CC85F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_QDSS_TSCTR_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 25,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_debug_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x17181EB2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_DEBUG_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_debug_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x1B862752,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_SPDM_DEBUG_CBCR), HWIO_PHYS(DISP_CC_MDSS_SPDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_gpu_smmu_vote_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xBAEFC8DC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_GPU_SMMU_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_mmu_tcu_vote_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x3DEE7487,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_MMU_TCU_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_pcie_0_link_down_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xB6C4C692,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_PCIE_0_LINK_DOWN_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_pcie_0_nocsr_com_phy_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xD13C8283,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_PCIE_0_NOCSR_COM_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_pcie_0_phy_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x822A9820,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_PCIE_0_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_pcie_0_phy_nocsr_com_phy_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xA7917945,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_PCIE_0_PHY_NOCSR_COM_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_pcie_1_link_down_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xAB0C0523,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_PCIE_1_LINK_DOWN_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_pcie_1_nocsr_com_phy_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x7D99D6D6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_PCIE_1_NOCSR_COM_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_pcie_1_phy_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x778DB555,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_PCIE_1_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_pcie_1_phy_nocsr_com_phy_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x7E512A4B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_PCIE_1_PHY_NOCSR_COM_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_qusb2phy_prim_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x9E2329D1,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_QUSB2PHY_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_qusb2phy_sec_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x7D3CC967,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_QUSB2PHY_SEC_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_usb3_dp_phy_prim_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x1F251390,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_USB3_DP_PHY_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_usb3_phy_prim_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x7F6A6E8C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_USB3_PHY_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_usb3phy_phy_prim_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x12166FD9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_USB3PHY_PHY_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gpu_cc_dpm_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xF3ECE45F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_DPM_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 37,
    },
  },
  {
    .szName    = "gpu_cc_gpu_smmu_vote_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x15F4CCA6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_HLOS1_VOTE_GPU_SMMU_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gpu_cc_hlos1_vote_gpu_smmu_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xF6733823,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_HLOS1_VOTE_GPU_SMMU_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gpu_cc_memnoc_gfx_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xEAA2A911,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_MEMNOC_GFX_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 33,
    },
  },
  {
    .szName    = "gpucc_gpu_cc_ff_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x30673FAE,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GPUCC_GPU_CC_FF_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gpucc_gpu_cc_gmu_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xB67BB00E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GPUCC_GPU_CC_GMU_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "tcsr_pcie_3x1_clkref_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xD556D840,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(TCSR_PCIE_3X1_CLKREF_EN__PCIE_ENABLE), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "tcsr_pcie_3x2_clkref_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x5508F3D9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(TCSR_PCIE_3X2_CLKREF_EN__PCIE_ENABLE), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "tcsr_ufs_pad_clkref_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xE31DE053,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(TCSR_UFS_PAD_CLKREF_EN__UFS_PAD_ENABLE), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "tcsr_ufs_phy_clkref_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xC7D40488,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(TCSR_UFS_PHY_CLKREF_EN__UFS_PHY_ENABLE), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "video_cc_debug_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x9AD7014D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_DEBUG_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCAGGRENOC                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap_0_m_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x79AD882E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP_0_M_AHB_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x100000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 192,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCAGGRENOCPCIE                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pcie_0_mstr_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOCPCIE,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x6ECCBB13,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_MSTR_AXI_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x2} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 334,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCAGGRENOCSOUTHSF                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_aggre_noc_pcie_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOCSOUTHSF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x7F143CA9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_AGGRE_NOC_PCIE_AXI_CBCR), 0, {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x1000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 77,
    },
  },
  {
    .szName    = "gcc_cnoc_pcie_sf_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOCSOUTHSF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xF1E3FEDD,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CNOC_PCIE_SF_AXI_CBCR), 0, {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x40} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 25,
    },
  },
  {
    .szName    = "gcc_ddrss_pcie_sf_qtb_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOCSOUTHSF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x6872C48B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_DDRSS_PCIE_SF_QTB_CBCR), 0, {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x80000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 262,
    },
  },
  {
    .szName    = "gcc_pcie_1_mstr_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOCSOUTHSF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xD8A72CC2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_1_MSTR_AXI_CBCR), HWIO_PHYS(GCC_PCIE_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x8000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 437,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCCNOCPERIPH                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pdm_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCNOCPERIPH,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xA6F0A072,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PDM_AHB_CBCR), HWIO_PHYS(GCC_PDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 216,
    },
  },
  {
    .szName    = "gcc_sdcc1_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCNOCPERIPH,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xD5DB24F5,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_SDCC1_AHB_CBCR), HWIO_PHYS(GCC_SDCC1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 431,
    },
  },
  {
    .szName    = "gcc_sdcc2_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCNOCPERIPH,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xF7AE64AF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_SDCC2_AHB_CBCR), HWIO_PHYS(GCC_SDCC2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 190,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCCNOCSOUTHQX                                        */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pcie_0_slv_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCCNOCSOUTHQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x9331B3EF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_SLV_AXI_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x1} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 333,
    },
  },
  {
    .szName    = "gcc_pcie_0_slv_q2a_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCCNOCSOUTHQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x5B161349,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_SLV_Q2A_AXI_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x20} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 332,
    },
  },
  {
    .szName    = "gcc_pcie_1_slv_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCCNOCSOUTHQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xAA65C59A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_1_SLV_AXI_CBCR), HWIO_PHYS(GCC_PCIE_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x4000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 436,
    },
  },
  {
    .szName    = "gcc_pcie_1_slv_q2a_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCCNOCSOUTHQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x5F52BA5E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_1_SLV_Q2A_AXI_CBCR), HWIO_PHYS(GCC_PCIE_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x2000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 435,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCCONFIGNOC                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_soc_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x38F71E1A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SOC_AHB_CBCR), HWIO_PHYS(CAM_CC_CAMSS_TOP_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 65,
    },
  },
  {
    .szName    = "gcc_boot_rom_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x20C2EB7C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_BOOT_ROM_AHB_CBCR), 0, {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x400} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 233,
    },
  },
  {
    .szName    = "gcc_camera_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xCB81AAEC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CAMERA_AHB_CBCR), HWIO_PHYS(GCC_CAMERA_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 128,
    },
  },
  {
    .szName    = "gcc_cfg_noc_pcie_anoc_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x927E2559,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CFG_NOC_PCIE_ANOC_AHB_CBCR), 0, {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x100000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 57,
    },
  },
  {
    .szName    = "gcc_disp_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xCC324D48,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_DISP_AHB_CBCR), HWIO_PHYS(GCC_DISPLAY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 136,
    },
  },
  {
    .szName    = "gcc_gpu_cfg_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xBDC5D904,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GPU_CFG_AHB_CBCR), HWIO_PHYS(GCC_GPU_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 388,
    },
  },
  {
    .szName    = "gcc_pcie_0_cfg_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xAB33D8F8,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_CFG_AHB_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x4} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 335,
    },
  },
  {
    .szName    = "gcc_pcie_1_cfg_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xB6E6F09E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_1_CFG_AHB_CBCR), HWIO_PHYS(GCC_PCIE_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x10000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 438,
    },
  },
  {
    .szName    = "gcc_pcie_rscc_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x4723F290,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_RSCC_CFG_AHB_CBCR), HWIO_PHYS(GCC_PCIE_RSCC_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x100000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 416,
    },
  },
  {
    .szName    = "gcc_qmip_camera_nrt_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x5508D425,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_CAMERA_NRT_AHB_CBCR), HWIO_PHYS(GCC_CAMERA_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 129,
    },
  },
  {
    .szName    = "gcc_qmip_camera_rt_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x15F7C6F4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_CAMERA_RT_AHB_CBCR), HWIO_PHYS(GCC_CAMERA_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 130,
    },
  },
  {
    .szName    = "gcc_qmip_disp_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x2FE1361E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_DISP_AHB_CBCR), HWIO_PHYS(GCC_DISPLAY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 137,
    },
  },
  {
    .szName    = "gcc_qmip_gpu_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x428F6D35,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_GPU_AHB_CBCR), HWIO_PHYS(GCC_GPU_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 389,
    },
  },
  {
    .szName    = "gcc_qmip_pcie_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x508920D5,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_PCIE_AHB_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x800} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 331,
    },
  },
  {
    .szName    = "gcc_qmip_video_cv_cpu_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x0F770842,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_VIDEO_CV_CPU_AHB_CBCR), HWIO_PHYS(GCC_VIDEO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 146,
    },
  },
  {
    .szName    = "gcc_qmip_video_cvp_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x5577C832,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_VIDEO_CVP_AHB_CBCR), HWIO_PHYS(GCC_VIDEO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 143,
    },
  },
  {
    .szName    = "gcc_qmip_video_v_cpu_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x39939E99,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_VIDEO_V_CPU_AHB_CBCR), HWIO_PHYS(GCC_VIDEO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 145,
    },
  },
  {
    .szName    = "gcc_qmip_video_vcodec_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xED09B49D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_VIDEO_VCODEC_AHB_CBCR), HWIO_PHYS(GCC_VIDEO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 144,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap_0_s_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xB8C59FEE,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP_0_S_AHB_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x200000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 193,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap_1_s_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x3428967E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP_1_S_AHB_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x2} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 205,
    },
  },
  {
    .szName    = "gcc_ufs_phy_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x79B5465B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_PHY_AHB_CBCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 343,
    },
  },
  {
    .szName    = "gcc_video_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x3DC15104,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_VIDEO_AHB_CBCR), HWIO_PHYS(GCC_VIDEO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 142,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCGP1                                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_gp1_clk",
    .pDomain   = &ClockDomain_GCC_GCCGP1,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x5BCD42D6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GP1_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 328,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCGP2                                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_gp2_clk",
    .pDomain   = &ClockDomain_GCC_GCCGP2,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xC0B86CC1,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GP2_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 329,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCGP3                                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_gp3_clk",
    .pDomain   = &ClockDomain_GCC_GCCGP3,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x81385E59,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GP3_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 330,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCGPUMEMNOCGFX                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ddrss_gpu_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCGPUMEMNOCGFX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xDF8E077C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_DDRSS_GPU_AXI_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 261,
    },
  },
  {
    .szName    = "gcc_gpu_memnoc_gfx_clk",
    .pDomain   = &ClockDomain_GCC_GCCGPUMEMNOCGFX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x114959A4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GPU_MEMNOC_GFX_CBCR), HWIO_PHYS(GCC_GPU_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 392,
    },
  },
  {
    .szName    = "gcc_gpu_snoc_dvm_gfx_clk",
    .pDomain   = &ClockDomain_GCC_GCCGPUMEMNOCGFX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x22ACC42A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GPU_SNOC_DVM_GFX_CBCR), HWIO_PHYS(GCC_GPU_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 394,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCMMNOCHFQX                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_camnoc_axi_hf_clk",
    .pDomain   = &ClockDomain_GCC_GCCMMNOCHFQX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD9CFD521,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CAMNOC_AXI_HF_CBCR), HWIO_PHYS(CAM_CC_CAMNOC_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 57,
    },
  },
  {
    .szName    = "gcc_camera_hf_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCMMNOCHFQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x62191536,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CAMERA_HF_AXI_CBCR), HWIO_PHYS(GCC_CAMERA_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 131,
    },
  },
  {
    .szName    = "gcc_disp_hf_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCMMNOCHFQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xBF311160,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_DISP_HF_AXI_CBCR), HWIO_PHYS(GCC_DISPLAY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 138,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCMMNOCSFQX                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_camnoc_axi_sf_clk",
    .pDomain   = &ClockDomain_GCC_GCCMMNOCSFQX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xAF49D0EF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CAMNOC_AXI_SF_CBCR), HWIO_PHYS(CAM_CC_CAMNOC_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 56,
    },
  },
  {
    .szName    = "gcc_camera_sf_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCMMNOCSFQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x033685A3,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CAMERA_SF_AXI_CBCR), HWIO_PHYS(GCC_CAMERA_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 132,
    },
  },
  {
    .szName    = "gcc_video_axi0_clk",
    .pDomain   = &ClockDomain_GCC_GCCMMNOCSFQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x527C9897,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_VIDEO_AXI0_CBCR), HWIO_PHYS(GCC_VIDEO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 147,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCPCIE0AUX                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pcie_0_aux_clk",
    .pDomain   = &ClockDomain_GCC_GCCPCIE0AUX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xDE4195A6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_AUX_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x8} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 336,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCPCIE0PHYRCHNG                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pcie_0_phy_rchng_clk",
    .pDomain   = &ClockDomain_GCC_GCCPCIE0PHYRCHNG,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x4F8DB026,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_PHY_RCHNG_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x400000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 338,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCPCIE0PIPE                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pcie_0_pipe_clk",
    .pDomain   = &ClockDomain_GCC_GCCPCIE0PIPE,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xDCB72BF8,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_PIPE_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x10} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 337,
    },
  },
  {
    .szName    = "gcc_pcie_0_pipe_div2_clk",
    .pDomain   = &ClockDomain_GCC_GCCPCIE0PIPE,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x8EA36E69,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_PIPE_DIV2_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_3), 0x2000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 339,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCPCIE1AUX                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pcie_1_aux_clk",
    .pDomain   = &ClockDomain_GCC_GCCPCIE1AUX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xBC6B4728,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_1_AUX_CBCR), HWIO_PHYS(GCC_PCIE_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x20000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 439,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCPCIE1PHYRCHNG                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pcie_1_phy_rchng_clk",
    .pDomain   = &ClockDomain_GCC_GCCPCIE1PHYRCHNG,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xCA529D26,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_1_PHY_RCHNG_CBCR), HWIO_PHYS(GCC_PCIE_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x100} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 441,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCPCIE1PIPE                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pcie_1_pipe_clk",
    .pDomain   = &ClockDomain_GCC_GCCPCIE1PIPE,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xB60CB671,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_1_PIPE_CBCR), HWIO_PHYS(GCC_PCIE_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x80} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 440,
    },
  },
  {
    .szName    = "gcc_pcie_1_pipe_div2_clk",
    .pDomain   = &ClockDomain_GCC_GCCPCIE1PIPE,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xAFDFD5ED,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_1_PIPE_DIV2_CBCR), HWIO_PHYS(GCC_PCIE_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_3), 0x8000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 442,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCPDM2                                               */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pdm2_clk",
    .pDomain   = &ClockDomain_GCC_GCCPDM2,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xF8EA86EA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PDM2_CBCR), HWIO_PHYS(GCC_PDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 218,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQDSSAPBTSCTR                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_icp_apb_clk",
    .pDomain   = &ClockDomain_GCC_GCCQDSSAPBTSCTR,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD96C8E43,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_ICP_APB_CBCR), HWIO_PHYS(CAM_CC_ICP_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 49,
    },
  },
  {
    .szName    = "cam_cc_icp_ts_clk",
    .pDomain   = &ClockDomain_GCC_GCCQDSSAPBTSCTR,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x7BB44BBF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_ICP_TS_CBCR), HWIO_PHYS(CAM_CC_ICP_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 48,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQDSSATBA                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_camnoc_atb_clk",
    .pDomain   = &ClockDomain_GCC_GCCQDSSATBA,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x569327C8,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CAMNOC_ATB_CBCR), HWIO_PHYS(CAM_CC_CAMNOC_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 62,
    },
  },
  {
    .szName    = "cam_cc_icp_atb_clk",
    .pDomain   = &ClockDomain_GCC_GCCQDSSATBA,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD55B69DD,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_ICP_ATB_CBCR), HWIO_PHYS(CAM_CC_ICP_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 46,
    },
  },
  {
    .szName    = "gcc_sdcc1_at_clk",
    .pDomain   = &ClockDomain_GCC_GCCQDSSATBA,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xEED7DD52,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_SDCC1_AT_CBCR), HWIO_PHYS(GCC_SDCC1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 434,
    },
  },
  {
    .szName    = "gcc_sdcc2_at_clk",
    .pDomain   = &ClockDomain_GCC_GCCQDSSATBA,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x63F0B54C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_SDCC2_AT_CBCR), HWIO_PHYS(GCC_SDCC2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 191,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQDSSATBB                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_cx_qdss_at_clk",
    .pDomain   = &ClockDomain_GCC_GCCQDSSATBB,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x3A64CC97,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_QDSS_AT_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 24,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQDSSTRIG                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_icp_cti_clk",
    .pDomain   = &ClockDomain_GCC_GCCQDSSTRIG,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x4C5996A0,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_ICP_CTI_CBCR), HWIO_PHYS(CAM_CC_ICP_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 47,
    },
  },
  {
    .szName    = "gpu_cc_cx_qdss_trig_clk",
    .pDomain   = &ClockDomain_GCC_GCCQDSSTRIG,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x046DFEBA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_QDSS_TRIG_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 28,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0CORE2X                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_core_2x_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0CORE2X,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x77020808,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_CORE_2X_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x40000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 195,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap0_core_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0CORE2X,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x1B88DC58,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_CORE_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x80000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 194,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0QSPIREF                                  */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_qspi_ref_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0QSPIREF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x87C40B43,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_QSPI_REF_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x20000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 203,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap0_s2_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0QSPIREF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x06533C2C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_S2_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x1000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 198,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S0                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s0_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S0,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x56C239B6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_S0_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x400000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 196,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S1                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s1_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S1,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x299AA1D4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_S1_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x800000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 197,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S3                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s3_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S3,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x939588DB,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_S3_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x2000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 199,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S4                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s4_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S4,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x62F41847,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_S4_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x4000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 200,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S5                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s5_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S5,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x5751B5F3,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_S5_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x8000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 201,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S6                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s6_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S6,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x917A11AD,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_S6_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x10000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 202,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1CORE2X                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_core_2x_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1CORE2X,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xD7DB82C0,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_CORE_2X_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x8} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 207,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap1_core_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1CORE2X,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x40B685B0,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_CORE_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x1} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 206,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1QSPIREF                                  */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_qspi_ref_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1QSPIREF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x386E7E5A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_QSPI_REF_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x40000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 215,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap1_s2_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1QSPIREF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x45AB34F6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S2_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x40} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 210,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S0                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s0_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S0,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xA40B3E1C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S0_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x10} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 208,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S1                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s1_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S1,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xDE8BDAAC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S1_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x20} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 209,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S3                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s3_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S3,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x6CBC20FD,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S3_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x80} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 211,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S4                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s4_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S4,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x2A814B46,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S4_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x100} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 212,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S5                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s5_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S5,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x8279058C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S5_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x200} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 213,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S6                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s6_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S6,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x6FB2266A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S6_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x400} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 214,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCSDCC1APPS                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_sdcc1_apps_clk",
    .pDomain   = &ClockDomain_GCC_GCCSDCC1APPS,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x562E7EDC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_SDCC1_APPS_CBCR), HWIO_PHYS(GCC_SDCC1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 432,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCSDCC1ICECORE                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_sdcc1_ice_core_clk",
    .pDomain   = &ClockDomain_GCC_GCCSDCC1ICECORE,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x4431ADF8,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_SDCC1_ICE_CORE_CBCR), HWIO_PHYS(GCC_SDCC1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 433,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCSDCC2APPS                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_sdcc2_apps_clk",
    .pDomain   = &ClockDomain_GCC_GCCSDCC2APPS,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x99917219,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_SDCC2_APPS_CBCR), HWIO_PHYS(GCC_SDCC2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 189,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCSLEEP                                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_usb30_prim_sleep_clk",
    .pDomain   = &ClockDomain_GCC_GCCSLEEP,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xA3AD9ACB,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_USB30_PRIM_SLEEP_CBCR), HWIO_PHYS(GCC_USB30_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 176,
    },
  },
  {
    .szName    = "gpu_cc_sleep_clk",
    .pDomain   = &ClockDomain_GCC_GCCSLEEP,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xC2E1C465,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_SLEEP_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 27,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCSYSNOC                                             */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap_1_m_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCSYSNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x728861DF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP_1_M_AHB_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x4} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 204,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYAXI                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_aggre_ufs_phy_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYAXI,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x9D270053,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_AGGRE_UFS_PHY_AXI_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 79,
    },
  },
  {
    .szName    = "gcc_ufs_phy_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYAXI,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x9310F430,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_PHY_AXI_CBCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 342,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYICECORE                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_ice_core_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYICECORE,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xEB42CB41,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_PHY_ICE_CORE_CBCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 349,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYPHYAUX                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_phy_aux_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYPHYAUX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x224FBCE6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_PHY_PHY_AUX_CBCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 350,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYRXSYMBOL0                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_rx_symbol_0_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYRXSYMBOL0,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xC250BA4B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_PHY_RX_SYMBOL_0_CBCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 345,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYRXSYMBOL1                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_rx_symbol_1_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYRXSYMBOL1,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xB7C57145,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_PHY_RX_SYMBOL_1_CBCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 351,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYTXSYMBOL0                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_tx_symbol_0_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYTXSYMBOL0,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xDE965215,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_PHY_TX_SYMBOL_0_CBCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 344,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYUNIPROCORE                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_unipro_core_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYUNIPROCORE,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x815C816D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_PHY_UNIPRO_CORE_CBCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 348,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUSB30PRIMMASTER                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_aggre_usb3_prim_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB30PRIMMASTER,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x9C0C2B41,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_AGGRE_USB3_PRIM_AXI_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 78,
    },
  },
  {
    .szName    = "gcc_cfg_noc_usb3_prim_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB30PRIMMASTER,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xE7023B78,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CFG_NOC_USB3_PRIM_AXI_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 32,
    },
  },
  {
    .szName    = "gcc_usb30_prim_atb_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB30PRIMMASTER,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x5F8B6EAA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_USB30_PRIM_ATB_CBCR), HWIO_PHYS(GCC_USB30_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 184,
    },
  },
  {
    .szName    = "gcc_usb30_prim_master_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB30PRIMMASTER,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x91482B7C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_USB30_PRIM_MASTER_CBCR), HWIO_PHYS(GCC_USB30_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 175,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI                                  */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_usb30_prim_mock_utmi_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xFEDF50FF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_USB30_PRIM_MOCK_UTMI_CBCR), HWIO_PHYS(GCC_USB30_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 177,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUSB3PRIMPHYAUX                                     */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_usb3_prim_phy_aux_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB3PRIMPHYAUX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x5BBF945A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_USB3_PRIM_PHY_AUX_CBCR), HWIO_PHYS(GCC_USB30_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 178,
    },
  },
  {
    .szName    = "gcc_usb3_prim_phy_com_aux_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB3PRIMPHYAUX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x84C54E8E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_USB3_PRIM_PHY_COM_AUX_CBCR), HWIO_PHYS(GCC_USB30_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 179,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUSB3PRIMPHYPIPE                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_usb3_prim_phy_pipe_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB3PRIMPHYPIPE,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x8F9EA437,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_USB3_PRIM_PHY_PIPE_CBCR), HWIO_PHYS(GCC_USB30_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 180,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCXO                                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_camera_hf_xo_clk",
    .pDomain   = &ClockDomain_GCC_GCCXO,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x83E10E7E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CAMERA_HF_XO_CBCR), HWIO_PHYS(GCC_CAMERA_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 133,
    },
  },
  {
    .szName    = "gcc_camera_sf_xo_clk",
    .pDomain   = &ClockDomain_GCC_GCCXO,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xEBEC08EA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CAMERA_SF_XO_CBCR), HWIO_PHYS(GCC_CAMERA_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 134,
    },
  },
  {
    .szName    = "gcc_disp_xo_clk",
    .pDomain   = &ClockDomain_GCC_GCCXO,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x9A471C5C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_DISP_XO_CBCR), HWIO_PHYS(GCC_DISPLAY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 139,
    },
  },
  {
    .szName    = "gcc_pcie_rscc_xo_clk",
    .pDomain   = &ClockDomain_GCC_GCCXO,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xEE38661C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_RSCC_XO_CBCR), HWIO_PHYS(GCC_PCIE_RSCC_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x200000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 417,
    },
  },
  {
    .szName    = "gcc_pdm_xo4_clk",
    .pDomain   = &ClockDomain_GCC_GCCXO,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x1C323047,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PDM_XO4_CBCR), HWIO_PHYS(GCC_PDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 217,
    },
  },
  {
    .szName    = "gcc_video_xo_clk",
    .pDomain   = &ClockDomain_GCC_GCCXO,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x79581D18,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_VIDEO_XO_CBCR), HWIO_PHYS(GCC_VIDEO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 148,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GPUCC_GPUCCDEBUGMUX                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_debug_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCDEBUGMUX,
    .pDebugMux = NULL,
    .nUniqueId = 0x2D49728D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_DEBUG_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gpu_cc_debug_measure_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCDEBUGMUX,
    .pDebugMux = NULL,
    .nUniqueId = 0x61D27566,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_DEBUG_MEASURE_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GPUCC_GPUCCFF                                             */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_cx_ff_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCFF,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x276A4142,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_FF_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 32,
    },
  },
  {
    .szName    = "gpu_cc_gx_acd_ahb_ff_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCFF,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x80DCC665,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_ACD_AHB_FF_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 19,
    },
  },
  {
    .szName    = "gpu_cc_gx_ahb_ff_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCFF,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x1DDFC79F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_AHB_FF_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 18,
    },
  },
  {
    .szName    = "gpu_cc_gx_rcg_ahb_ff_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCFF,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x3A012F1F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_RCG_AHB_FF_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 20,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GPUCC_GPUCCGMU                                            */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_cx_gmu_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCGMU,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x85040864,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_GMU_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 29,
    },
  },
  {
    .szName    = "gpu_cc_gx_gmu_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCGMU,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xFD46B6AB,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_GMU_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 17,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GPUCC_GPUCCHUB                                            */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_ahb_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCHUB,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x763BA1C4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_AHB_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 23,
    },
  },
  {
    .szName    = "gpu_cc_hub_aon_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCHUB,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x063271D7,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_HUB_AON_CBCR), HWIO_PHYS(GPUCC_GPU_CC_FAST_HUB_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 42,
    },
  },
  {
    .szName    = "gpu_cc_hub_cx_int_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCHUB,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xC00F7891,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_HUB_CX_INT_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 31,
    },
  },
  {
    .szName    = "gpu_cc_rscc_hub_aon_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCHUB,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x24095AAA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_RSCC_HUB_AON_CBCR), HWIO_PHYS(GPUCC_GPU_CC_FAST_HUB_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 41,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GPUCC_GPUCCPLLTESTMUX                                     */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_pll_test_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCPLLTESTMUX,
    .pDebugMux = NULL,
    .nUniqueId = 0x8F8278F9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_PLL_TEST_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GPUCC_GPUCCXO                                             */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_cx_accu_shift_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x2F27F55F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_ACCU_SHIFT_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 36,
    },
  },
  {
    .szName    = "gpu_cc_cxo_aon_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xA006B60F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CXO_AON_CBCR), HWIO_PHYS(GPUCC_GPU_CC_XO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 14,
    },
  },
  {
    .szName    = "gpu_cc_cxo_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x8DFA73CF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CXO_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 30,
    },
  },
  {
    .szName    = "gpu_cc_demet_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x2217FC16,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_DEMET_CBCR), HWIO_PHYS(GPUCC_GPU_CC_XO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 16,
    },
  },
  {
    .szName    = "gpu_cc_freq_measure_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xC306597F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_FREQ_MEASURE_CBCR), HWIO_PHYS(GPUCC_GPU_CC_XO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 15,
    },
  },
  {
    .szName    = "gpu_cc_gx_accu_shift_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x5EAB0BB8,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_ACCU_SHIFT_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 21,
    },
  },
  {
    .szName    = "gpu_cc_rscc_xo_aon_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xC5B136B0,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_RSCC_XO_AON_CBCR), HWIO_PHYS(GPUCC_GPU_CC_XO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 13,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GXCLKCTL_GXCLKCTLDEBUGMUX                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gx_clkctl_debug_clk",
    .pDomain   = &ClockDomain_GXCLKCTL_GXCLKCTLDEBUGMUX,
    .pDebugMux = NULL,
    .nUniqueId = 0xED4C92E9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPU_GX_CLKCTL_DEBUG_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GXCLKCTL_GXCLKCTLGXGFX3D                                  */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gx_clkctl_acd_gfx3d_clk",
    .pDomain   = &ClockDomain_GXCLKCTL_GXCLKCTLGXGFX3D,
    .pDebugMux = &ClockDebugMux_GXCLKCTL,
    .nUniqueId = 0x875D0742,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPU_GX_CLKCTL_ACD_GFX3D_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 8,
    },
  },
  {
    .szName    = "gx_clkctl_gx_gfx3d_clk",
    .pDomain   = &ClockDomain_GXCLKCTL_GXCLKCTLGXGFX3D,
    .pDebugMux = &ClockDebugMux_GXCLKCTL,
    .nUniqueId = 0x45536680,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPU_GX_CLKCTL_GX_GFX3D_CBCR), HWIO_PHYS(GPU_GX_CLKCTL_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 3,
    },
  },
  {
    .szName    = "gx_clkctl_gx_gfx3d_rdvm_clk",
    .pDomain   = &ClockDomain_GXCLKCTL_GXCLKCTLGXGFX3D,
    .pDebugMux = &ClockDebugMux_GXCLKCTL,
    .nUniqueId = 0xDF5E9C40,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPU_GX_CLKCTL_GX_GFX3D_RDVM_CBCR), HWIO_PHYS(GPU_GX_CLKCTL_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 6,
    },
  },
  {
    .szName    = "gx_clkctl_mnd1x_gfx3d_clk",
    .pDomain   = &ClockDomain_GXCLKCTL_GXCLKCTLGXGFX3D,
    .pDebugMux = &ClockDebugMux_GXCLKCTL,
    .nUniqueId = 0xB0A24B93,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPU_GX_CLKCTL_MND1X_GFX3D_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 7,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GXCLKCTL_GXCLKCTLPLLTESTMUX                               */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gx_clkctl_pll_test_clk",
    .pDomain   = &ClockDomain_GXCLKCTL_GXCLKCTLPLLTESTMUX,
    .pDebugMux = NULL,
    .nUniqueId = 0x9F45DA64,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPU_GX_CLKCTL_PLL_TEST_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GXCLKCTL_GXCLKCTLXO                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gx_clkctl_acd_cxo_clk",
    .pDomain   = &ClockDomain_GXCLKCTL_GXCLKCTLXO,
    .pDebugMux = &ClockDebugMux_GXCLKCTL,
    .nUniqueId = 0x7CDADA98,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPU_GX_CLKCTL_ACD_CXO_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 9,
    },
  },
  {
    .szName    = "gx_clkctl_clk_ctl_xo_clk",
    .pDomain   = &ClockDomain_GXCLKCTL_GXCLKCTLXO,
    .pDebugMux = &ClockDebugMux_GXCLKCTL,
    .nUniqueId = 0x0484D786,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPU_GX_CLKCTL_CLK_CTL_XO_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 1,
    },
  },
  {
    .szName    = "gx_clkctl_demet_clk",
    .pDomain   = &ClockDomain_GXCLKCTL_GXCLKCTLXO,
    .pDebugMux = &ClockDebugMux_GXCLKCTL,
    .nUniqueId = 0xC0027370,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPU_GX_CLKCTL_DEMET_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 2,
    },
  },
  {
    .szName    = "gx_clkctl_gx_accu_clk",
    .pDomain   = &ClockDomain_GXCLKCTL_GXCLKCTLXO,
    .pDebugMux = &ClockDebugMux_GXCLKCTL,
    .nUniqueId = 0xAC6923DC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPU_GX_CLKCTL_GX_ACCU_CBCR), HWIO_PHYS(GPU_GX_CLKCTL_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 10,
    },
  },
  {
    .szName    = "gx_clkctl_gx_cxo_clk",
    .pDomain   = &ClockDomain_GXCLKCTL_GXCLKCTLXO,
    .pDebugMux = &ClockDebugMux_GXCLKCTL,
    .nUniqueId = 0x0EEDCC51,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPU_GX_CLKCTL_GX_CXO_CBCR), HWIO_PHYS(GPU_GX_CLKCTL_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 4,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_VIDEOCC_VIDEOCCAHB                                        */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "video_cc_ahb_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCAHB,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0x12DABE26,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_AHB_CBCR), HWIO_PHYS(VCODEC_VIDEO_CC_INTERFACE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 5,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_VIDEOCC_VIDEOCCMVS0                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "video_cc_mvs0_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCMVS0,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0x69F9979C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_MVS0_CBCR), HWIO_PHYS(VCODEC_VIDEO_CC_MVS0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 3,
    },
  },
  {
    .szName    = "video_cc_mvs0c_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCMVS0,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0xCC22911E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_MVS0C_CBCR), HWIO_PHYS(VCODEC_VIDEO_CC_MVS0C_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 1,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_VIDEOCC_VIDEOCCPLLTESTMUX                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "video_cc_pll_test_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCPLLTESTMUX,
    .pDebugMux = NULL,
    .nUniqueId = 0xF56D61DD,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_PLL_TEST_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_VIDEOCC_VIDEOCCSLEEP                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "video_cc_sleep_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCSLEEP,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0x2CE12181,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_SLEEP_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 9,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_VIDEOCC_VIDEOCCXO                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "video_cc_mvs0_shift_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCXO,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0x0DB0D3BC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_MVS0_SHIFT_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 7,
    },
  },
  {
    .szName    = "video_cc_mvs0c_shift_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCXO,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0x7E371A11,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_MVS0C_SHIFT_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 8,
    },
  },
  {
    .szName    = "video_cc_xo_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCXO,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0x3777936C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_XO_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 6,
    },
  },
};


/*=========================================================================
      Power Domains
==========================================================================*/

static ClockPowerDomainNodeType aPowerDomains[] =
{
  {
    .szName         = "cam_cc_camss_top_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MX,
    .nUniqueId      = 0x0260C52A,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(CAM_CC_CAMSS_TOP_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "disp_cc_mdss_core_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MX,
    .nUniqueId      = 0x32294237,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(DISP_CC_MDSS_CORE_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "disp_cc_mdss_core_int2_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MX,
    .nUniqueId      = 0x4A7593B6,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(DISP_CC_MDSS_CORE_INT2_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_gpu_smmu_vote_gds",
    .nRailMask      = 0x0,
    .nUniqueId      = 0x7BD929E2,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_GPU_SMMU_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_aggre_noc_mmu_pcie_qtb_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nUniqueId      = 0x74DB78FD,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_AGGRE_NOC_MMU_PCIE_QTB_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_aggre_noc_mmu_qtb1_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nUniqueId      = 0xC3798F08,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_AGGRE_NOC_MMU_QTB1_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_aggre_noc_mmu_qtb2_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nUniqueId      = 0x08B324B4,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_AGGRE_NOC_MMU_QTB2_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_all_smmu_mmu_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nUniqueId      = 0xBAACE2AF,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_ALL_SMMU_MMU_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_gpu_smmu_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nUniqueId      = 0x0F149500,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_GPU_SMMU_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_lpass_qtb_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nUniqueId      = 0xDEAABDAA,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_LPASS_QTB_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_mmnoc_mmu_qtb_hf01_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nUniqueId      = 0x1E8A798A,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_mmnoc_mmu_qtb_hf23_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nUniqueId      = 0x87D675C7,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_mmnoc_mmu_qtb_sf_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nUniqueId      = 0xEF85DE46,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_mmu_tcu_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nUniqueId      = 0x4A5857B9,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_MMU_TCU_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_turing_mmu_qtb0_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nUniqueId      = 0x29D59788,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_TURING_MMU_QTB0_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_mmu_tcu_vote_gds",
    .nRailMask      = 0x0,
    .nUniqueId      = 0x66B0BD75,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_MMU_TCU_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_pcie_0_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MX,
    .nUniqueId      = 0xC1C9C0D4,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_PCIE_0_GDSCR),
      .VoterRegister  = {HWIO_PHYS(GCC_PROC_GDSC_COLLAPSE_ENA_VOTE), 0x1},
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_pcie_0_phy_gdsc",
    .nRailMask      = RAIL_VDD_CX,
    .nUniqueId      = 0x2AE8F85B,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_PCIE_0_PHY_GDSCR),
      .VoterRegister  = {HWIO_PHYS(GCC_PROC_GDSC_COLLAPSE_ENA_VOTE), 0x2},
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_pcie_1_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MX,
    .nUniqueId      = 0x0BE3F4DE,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_PCIE_1_GDSCR),
      .VoterRegister  = {HWIO_PHYS(GCC_PROC_GDSC_COLLAPSE_ENA_VOTE), 0x8},
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_pcie_1_phy_gdsc",
    .nRailMask      = RAIL_VDD_CX,
    .nUniqueId      = 0x126858E6,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_PCIE_1_PHY_GDSCR),
      .VoterRegister  = {HWIO_PHYS(GCC_PROC_GDSC_COLLAPSE_ENA_VOTE), 0x10},
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_ufs_mem_phy_gdsc",
    .nRailMask      = RAIL_VDD_CX,
    .nUniqueId      = 0xF7004938,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_UFS_MEM_PHY_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_ufs_phy_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MX,
    .nUniqueId      = 0x0B76D452,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_UFS_PHY_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_usb30_prim_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MX,
    .nUniqueId      = 0x8DA85DD3,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_USB30_PRIM_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_usb3_phy_gdsc",
    .nRailMask      = RAIL_VDD_CX,
    .nUniqueId      = 0x03ED0944,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_USB3_PHY_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gpu_cc_cx_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MX,
    .nUniqueId      = 0x9C476251,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GPUCC_GPU_CC_CX_GDSCR),
      .nGDSHWCtrlAddr = HWIO_PHYS(GPUCC_GPU_CC_CX_HW_CTRL_CFG1_GDSR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gpu_cc_gpu_smmu_vote_gds",
    .nRailMask      = 0x0,
    .nUniqueId      = 0x757192BD,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GPUCC_GPU_CC_HLOS1_VOTE_GPU_SMMU_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gx_clkctl_gx_gdsc",
    .nRailMask      = RAIL_VDD_GFX | RAIL_VDD_MX,
    .nUniqueId      = 0xC37292D5,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GPU_GX_CLKCTL_GX_GDSCR),
      .pmControl      = &HAL_clk_GPUGxPowerDomainControl,
    },
  },
  {
    .szName         = "video_cc_mvs0_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MX,
    .nUniqueId      = 0x0C6A70FC,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(VCODEC_VIDEO_CC_MVS0_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "video_cc_mvs0c_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MX,
    .nUniqueId      = 0x07EA7371,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(VCODEC_VIDEO_CC_MVS0C_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
};


/*=========================================================================
      Main BSP
==========================================================================*/

ClockBSPType ClockBSP =
{
  .aBases            = aBases,
  .nNumBases         = SIZEOF_ARRAY(aBases),
  .aRails            = aRails,
  .nNumRails         = SIZEOF_ARRAY(aRails),
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
  .aDebugMuxes       = aDebugMuxes,
  .nNumDebugMuxes    = SIZEOF_ARRAY(aDebugMuxes),
  .nFlags            = CLOCK_GLOBAL_FLAG_LOG_CLOCK_FREQ_CHANGE |
                       CLOCK_GLOBAL_FLAG_LOG_SOURCE_STATE_CHANGE,
  .SafeMuxConfig     = { 0, 2, 0, 0 },
};

