/*
==============================================================================

FILE:         ClockBSP.c

DESCRIPTION:
  This file contains the clock driver BSP data.

  Auto-generated from the following IPCat controller releases:

    SM8650v1 (lanai_1.0):
      PLL_HSR   : 7.0
      APSS_CC   : lanai_apss_cc_lanai_apss_1.0_p3q3r465_fp15 [lanai_apss_cc.r4]
      CAM_CC    : lanai_cam_cc_cam_cc_7.0_p3q2r27_fp16 [lanai_cam_cc.r5]
      DISP_CC   : lanai_disp_cc_z_disp_cc_7.0_p3q0r3.21_fp8 [lanai_disp_cc.r2]
      GCC       : lanai_gcc_z_lanai_clk_ctl_p3q3r4.1_fp13 [lanai_gcc.r17]
      GPU_CC    : lanai_gpu_cc_z_gpu_cc_7.0_p3q3r5.03_fp9 [lanai_gpu_cc.r6]
      TCSR_CC   : None
      VIDEO_CC  : lanai_video_cc_z_video_cc_7.0_p3q3r70_fp9 [lanai_video_cc.r3]

    SM8650v2 (lanai_2.0):
      PLL_HSR   : 1.0
      APSS_CC   : lanai_apss_cc_lanai_apss_2.0_p3q3r72_fp20 [lanai_apss_cc.r4]
      CAM_CC    : lanai_cam_cc_cam_cc_7.0_p3q2r27_fp15 [lanai_cam_cc.r5]
      DISP_CC   : lanai_disp_cc_z_disp_cc_7.0_p3q0r3.21_fp8 [lanai_disp_cc.r2]
      GCC       : lanai_gcc_z_lanai_clk_ctl_p3q3r4.1_fp13 [lanai_gcc.r17]
      GPU_CC    : lanai_gpu_cc_z_gpu_cc_7.0_p3q3r5.03_fp14 [lanai_v2_gpu_cc.r1]
      TCSR_CC   : None
      VIDEO_CC  : lanai_video_cc_z_video_cc_7.0_p3q3r70_fp11 [lanai_v2_video_cc.r1]


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
 'generators': [{'options': {'cesta_flags': {'cam': ['DEFAULT_ENABLE']},
                             'clock_flags': {},
                             'clock_flags_hal': {'gcc_qupv3_wrap1_s0_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap1_s1_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap1_s2_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap1_s3_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap1_s4_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap1_s5_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap1_s6_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap1_s7_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap2_s0_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap2_s1_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap2_s2_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap2_s3_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap2_s4_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap2_s5_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap2_s6_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_qupv3_wrap2_s7_clk_src': ['DOMAIN_HW_CLK_CONTROL']},
                             'driver_flags': ['LOG_CLOCK_FREQ_CHANGE',
                                              'LOG_SOURCE_STATE_CHANGE'],
                             'env': ['apcs', 'gpuss', 'UEFI'],
                             'hal_ctl_structs': {'gpu_cc_gx_gdsc': 'HAL_clk_GPUGxPowerDomainControl'},
                             'include_cesta': True,
                             'include_divider': ['.*'],
                             'include_file': {'HALclkPLLSettings.h': False},
                             'include_fmax': ['.*'],
                             'include_source_map': ['.*'],
                             'map_bases': True,
                             'multi_rail': True,
                             'npa_rename': {'/vcs/mxc': '/vcs/vdd_mxc',
                                            '/vcs/vdd_cam_cx': '/vcs/vdd_mm',
                                            '/vcs/vdd_mxa': '/vcs/vdd_mx'},
                             'rename': {'gcc_pcie_rscc_cfg_ahb_clk': 'gcc_pcie_rscc_ahb_clk'},
                             'standalone_bcrs': ['.*pcie.*', '.*usb.*']},
                 'output_dir': 'lanai_output_dir',
                 'type': 'dalclock'}],
 'target': ['lanai']}

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
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlAPSSCC_lanai;
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlCAMCC_lanai;
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlDISPCC_lanai;
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlGCC_lanai;
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlGPUCC_lanai;
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlVIDEOCC_lanai;

/*
 * Custom control structures.
 */
extern HAL_clk_PowerDomainControlType     HAL_clk_GPUGxPowerDomainControl;


/*=========================================================================
      Data Declarations
==========================================================================*/

enum
{
  CESTA_IDX_CAM,
  CESTA_IDX_PCIE,
};

/*=========================================================================
      Bases
==========================================================================*/

uintptr_t HAL_clk_nHWIOBaseAPSSHM;
uintptr_t HAL_clk_nHWIOBaseCLKCTL;
uintptr_t HAL_clk_nHWIOBaseCORETOPCSR;
uintptr_t HAL_clk_nHWIOBaseGFX;
uintptr_t HAL_clk_nHWIOBaseIRIS;
uintptr_t HAL_clk_nHWIOBaseMDSS;
uintptr_t HAL_clk_nHWIOBasePCIERSCC;
uintptr_t HAL_clk_nHWIOBaseTITANSS;

static ClockBaseType aBases[] =
{
  { APSS_HM_BASE_PHYS,        APSS_HM_BASE_SIZE,        &HAL_clk_nHWIOBaseAPSSHM       },
  { CLK_CTL_BASE_PHYS,        CLK_CTL_BASE_SIZE,        &HAL_clk_nHWIOBaseCLKCTL       },
  { CORE_TOP_CSR_BASE_PHYS,   CORE_TOP_CSR_BASE_SIZE,   &HAL_clk_nHWIOBaseCORETOPCSR   },
  { GFX_BASE_PHYS,            GFX_BASE_SIZE,            &HAL_clk_nHWIOBaseGFX          },
  { IRIS_BASE_PHYS,           IRIS_BASE_SIZE,           &HAL_clk_nHWIOBaseIRIS         },
  { MDSS_BASE_PHYS,           MDSS_BASE_SIZE,           &HAL_clk_nHWIOBaseMDSS         },
  { PCIE_RSCC_BASE_PHYS,      PCIE_RSCC_BASE_SIZE,      &HAL_clk_nHWIOBasePCIERSCC     },
  { TITAN_SS_BASE_PHYS,       TITAN_SS_BASE_SIZE,       &HAL_clk_nHWIOBaseTITANSS      },
};

/*=========================================================================
      Voltage Rails
==========================================================================*/

enum
{
  RAIL_IDX_VDD_CX,
  RAIL_IDX_VDD_GX,
  RAIL_IDX_VDD_MM,
  RAIL_IDX_VDD_MX,
  RAIL_IDX_VDD_MXC,
};

#define RAIL_VDD_CX          (1 << RAIL_IDX_VDD_CX)
#define RAIL_VDD_GX          (1 << RAIL_IDX_VDD_GX)
#define RAIL_VDD_MM          (1 << RAIL_IDX_VDD_MM)
#define RAIL_VDD_MX          (1 << RAIL_IDX_VDD_MX)
#define RAIL_VDD_MXC         (1 << RAIL_IDX_VDD_MXC)

static ClockRailType ClockRail_VDDCX =
{
  .szName = "/vcs/vdd_cx",
};

static ClockRailType ClockRail_VDDGX =
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

static ClockRailType ClockRail_VDDMXC =
{
  .szName = "/vcs/vdd_mxc",
};

static ClockRailType *aRails[] =
{
  [RAIL_IDX_VDD_CX]       = &ClockRail_VDDCX,
  [RAIL_IDX_VDD_GX]       = &ClockRail_VDDGX,
  [RAIL_IDX_VDD_MM]       = &ClockRail_VDDMM,
  [RAIL_IDX_VDD_MX]       = &ClockRail_VDDMX,
  [RAIL_IDX_VDD_MXC]      = &ClockRail_VDDMXC,
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
    .pmControl  = &HAL_clk_DebugMuxControlGCC_lanai,
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
  { 33, 8 },
  { 34, 8 },
  { CLOCK_DEBUG_MUX_INPUT_DIV_END },
};

static ClockDebugMuxType ClockDebugMux_APSSCC =
{
  .szName       = "apss_cc",
  .nUniqueId    = 0xD2777925,
  .pParent      = &ClockDebugMux_GCC,
  .nParentSel   = 309,
  .anInputDivs  = aMuxInputDividers_APSSCC,
  .nDivider     = 4,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlAPSSCC_lanai,
  },
};

static ClockDebugMuxType ClockDebugMux_CAMCC =
{
  .szName       = "cam_cc",
  .nUniqueId    = 0xCEB85AEC,
  .pParent      = &ClockDebugMux_GCC,
  .nParentSel   = 106,
  .nDivider     = 4,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlCAMCC_lanai,
  },
};

static ClockDebugMuxType ClockDebugMux_DISPCC =
{
  .szName       = "disp_cc",
  .nUniqueId    = 0x3E02FDA9,
  .pParent      = &ClockDebugMux_GCC,
  .nParentSel   = 111,
  .nDivider     = 4,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlDISPCC_lanai,
  },
};

static ClockDebugMuxType ClockDebugMux_GPUCC =
{
  .szName       = "gpu_cc",
  .nUniqueId    = 0x89008681,
  .pParent      = &ClockDebugMux_GCC,
  .nParentSel   = 397,
  .nDivider     = 2,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlGPUCC_lanai,
  },
};

static ClockDebugMuxType ClockDebugMux_VIDEOCC =
{
  .szName       = "video_cc",
  .nUniqueId    = 0xE8021679,
  .pParent      = &ClockDebugMux_GCC,
  .nParentSel   = 120,
  .nDivider     = 3,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlVIDEOCC_lanai,
  },
};

static ClockDebugMuxType *aDebugMuxes[] =
{
  &ClockDebugMux_APSSCC,
  &ClockDebugMux_CAMCC,
  &ClockDebugMux_DISPCC,
  &ClockDebugMux_GCC,
  &ClockDebugMux_GPUCC,
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

static const ClockSourceRegSettingsType ClockSourceRegSettings_CAMCC_CAMCCPLL0[] =
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
  {  910000000, &ClockSource_XO, { 0, 0, 1, 47,  0x00006555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS,       {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  {  950000000, &ClockSource_XO, { 0, 0, 1, 49,  0x00007AAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS,       {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  { 1150000000, &ClockSource_XO, { 0, 0, 1, 59,  0x0000E555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1350000000, &ClockSource_XO, { 0, 0, 1, 70,  0x00005000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1650000000, &ClockSource_XO, { 0, 0, 1, 85,  0x0000F000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_NOM,       },
};

/*
 * ClockSourceBSP_CAMCC_CAMCCPLL10
 *
 * Used by:
 *   ClockSource_CAMCC_CAMCCPLL10
 *   ClockSource_CAMCC_CAMCCPLL3
 *   ClockSource_CAMCC_CAMCCPLL4
 *   ClockSource_CAMCC_CAMCCPLL5
 *   ClockSource_CAMCC_CAMCCPLL6
 *   ClockSource_CAMCC_CAMCCPLL7
 */
static const ClockSourceFreqConfigType ClockSourceBSP_CAMCC_CAMCCPLL10[] =
{
  {  932000000, &ClockSource_XO, { 0, 0, 1, 48,  0x00008AAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1188000000, &ClockSource_XO, { 0, 0, 1, 61,  0x0000E000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1350000000, &ClockSource_XO, { 0, 0, 1, 70,  0x00005000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1570000000, &ClockSource_XO, { 0, 0, 1, 81,  0x0000C555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};

/*
 * ClockSourceBSP_CAMCC_CAMCCPLL2
 *
 * Used by:
 *   ClockSource_CAMCC_CAMCCPLL2
 */
static const ClockSourceFreqConfigType ClockSourceBSP_CAMCC_CAMCCPLL2[] =
{
  {  960000000, &ClockSource_XO, { 0, 0, 1, 50,  0x00000000, HAL_CLK_PLL_FRAC_MODE_UNKNOWN, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
};

/*
 * ClockSourceBSP_CAMCC_CAMCCPLL8
 *
 * Used by:
 *   ClockSource_CAMCC_CAMCCPLL8
 */
static const ClockSourceFreqConfigType ClockSourceBSP_CAMCC_CAMCCPLL8[] =
{
  {  400000000, &ClockSource_XO, { 0, 0, 1, 20,  0x0000D555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1,},
  {  800000000, &ClockSource_XO, { 0, 0, 1, 41,  0x0000AAAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS,       },
  {  960000000, &ClockSource_XO, { 0, 0, 1, 50,  0x00000000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1570000000, &ClockSource_XO, { 0, 0, 1, 81,  0x0000C555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};

/*
 * ClockSourceBSP_CAMCC_CAMCCPLL9
 *
 * Used by:
 *   ClockSource_CAMCC_CAMCCPLL9
 */
static const ClockSourceFreqConfigType ClockSourceBSP_CAMCC_CAMCCPLL9[] =
{
  {  960000000, &ClockSource_XO, { 0, 0, 1, 50,  0x00000000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidole.nEven = 2, .Lucidole.nOdd = 3} }, RAIL_VOLTAGE_LEVEL_SVS,       },
};

/*
 * ClockSourceBSP_DISPCC_DISPCCPLL0
 *
 * Used by:
 *   ClockSource_DISPCC_DISPCCPLL0
 */
static const ClockSourceFreqConfigType ClockSourceBSP_DISPCC_DISPCCPLL0[] =
{
  {  257142858, &ClockSource_XO, { 0, 0, 1, 13,  0x00006492, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1,},
  {  300000000, &ClockSource_XO, { 0, 0, 1, 15,  0x0000A000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1,},
  {  450000000, &ClockSource_XO, { 0, 0, 1, 23,  0x00007000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1,},
  {  600000000, &ClockSource_XO, { 0, 0, 1, 31,  0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1,},
  {  975000000, &ClockSource_XO, { 0, 0, 1, 50,  0x0000C800, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1206000000, &ClockSource_XO, { 0, 0, 1, 62,  0x0000D000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1542000000, &ClockSource_XO, { 0, 0, 1, 80,  0x00005000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};

/*
 * ClockSourceBSP_DISPCC_DISPCCPLL1
 *
 * Used by:
 *   ClockSource_DISPCC_DISPCCPLL1
 */
static const ClockSourceFreqConfigType ClockSourceBSP_DISPCC_DISPCCPLL1[] =
{
  {  600000000, &ClockSource_XO, { 0, 0, 1, 31,  0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1,},
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
 * ClockSourceBSP_GCC_GCCGPLL1
 *
 * Used by:
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL1[] =
{
  { 1066000000, &ClockSource_XO, { 0, 0, 1, 55,  0x00008555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
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
  {  462000000, &ClockSource_XO, { 0, 0, 1, 24,  0x00001000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1,},
  {  620000000, &ClockSource_XO, { 0, 0, 1, 32,  0x00004AAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
  {  732000000, &ClockSource_XO, { 0, 0, 1, 38,  0x00002000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
  {  844000000, &ClockSource_XO, { 0, 0, 1, 43,  0x0000F555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1000000000, &ClockSource_XO, { 0, 0, 1, 52,  0x00001555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1156000000, &ClockSource_XO, { 0, 0, 1, 60,  0x00003555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1258000000, &ClockSource_XO, { 0, 0, 1, 65,  0x00008555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1360000000, &ClockSource_XO, { 0, 0, 1, 70,  0x0000D555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1440000000, &ClockSource_XO, { 0, 0, 1, 75,  0x00000000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1540000000, &ClockSource_XO, { 0, 0, 1, 80,  0x00003555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1668000000, &ClockSource_XO, { 0, 0, 1, 86,  0x0000E000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_NOM,       },
  { 1738000000, &ClockSource_XO, { 0, 0, 1, 90,  0x00008555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_NOM,       {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  { 1806000000, &ClockSource_XO, { 0, 0, 1, 94,  0x00001000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_NOM,       },
  { 2000000000, &ClockSource_XO, { 0, 0, 1, 104, 0x00002AAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_NOM,       {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  { 2200000000, &ClockSource_XO, { 0, 0, 1, 114, 0x00009555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_TUR_L1,    {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
};

/*
 * ClockSourceBSP_GPUCC_GPUCCPLL1
 *
 * Used by:
 *   ClockSource_GPUCC_GPUCCPLL1
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GPUCC_GPUCCPLL1[] =
{
  {  520000000, &ClockSource_XO, { 0, 0, 1, 27,  0x00001555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1,},
  { 1250000000, &ClockSource_XO, { 0, 0, 1, 65,  0x00001AAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};

/*
 * ClockSourceBSP_VIDEOCC_VIDEOCCPLL0
 *
 * Used by:
 *   ClockSource_VIDEOCC_VIDEOCCPLL0
 */
static const ClockSourceFreqConfigType ClockSourceBSP_VIDEOCC_VIDEOCCPLL0[] =
{
  {  588000000, &ClockSource_XO, { 0, 0, 1, 30,  0x0000A000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1,},
  {  840000000, &ClockSource_XO, { 0, 0, 1, 43,  0x0000C000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  {  900000000, &ClockSource_XO, { 0, 0, 1, 46,  0x0000E000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  { 1140000000, &ClockSource_XO, { 0, 0, 1, 59,  0x00006000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1305000000, &ClockSource_XO, { 0, 0, 1, 67,  0x0000F800, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1440000000, &ClockSource_XO, { 0, 0, 1, 75,  0x00000000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1600000000, &ClockSource_XO, { 0, 0, 1, 83,  0x00005555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};

/*
 * ClockSourceBSP_VIDEOCC_VIDEOCCPLL1
 *
 * Used by:
 *   ClockSource_VIDEOCC_VIDEOCCPLL1
 */
static const ClockSourceFreqConfigType ClockSourceBSP_VIDEOCC_VIDEOCCPLL1[] =
{
  {  840000000, &ClockSource_XO, { 0, 0, 1, 43,  0x0000C000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1050000000, &ClockSource_XO, { 0, 0, 1, 54,  0x0000B000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  { 1110000000, &ClockSource_XO, { 0, 0, 1, 57,  0x0000D000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  { 1350000000, &ClockSource_XO, { 0, 0, 1, 70,  0x00005000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1500000000, &ClockSource_XO, { 0, 0, 1, 78,  0x00002000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1650000000, &ClockSource_XO, { 0, 0, 1, 85,  0x0000F000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_NOM,       },
};


/*=========================================================================
      Sources
==========================================================================*/

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL0 =
{
  .szName       = "cam_cc_pll0",
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0x3E90B842,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL0,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL0),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE |
                  CLOCK_CONFIG_PLL_ODD_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL0_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL1 =
{
  .szName       = "cam_cc_pll1",
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0x6237E726,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL1,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL1),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL1_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL10 =
{
  .szName       = "cam_cc_pll10",
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0x6D530F86,
  .nFlags       = CLOCK_FLAG_CESTA_CONTROLLED |
                  CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL10,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL10),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .CESTA        = { CESTA_IDX_CAM, 5 },
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL10_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL2 =
{
  .szName       = "cam_cc_pll2",
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0x6DF55C3B,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL2,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL2),
  .nRailMask    = RAIL_VDD_MX,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
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
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0x9447D816,
  .nFlags       = CLOCK_FLAG_CESTA_CONTROLLED |
                  CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL10,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL10),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .CESTA        = { CESTA_IDX_CAM, 0 },
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL3_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL4 =
{
  .szName       = "cam_cc_pll4",
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0x70B3A5DD,
  .nFlags       = CLOCK_FLAG_CESTA_CONTROLLED |
                  CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL10,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL10),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .CESTA        = { CESTA_IDX_CAM, 1 },
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL4_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL5 =
{
  .szName       = "cam_cc_pll5",
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0x838225F9,
  .nFlags       = CLOCK_FLAG_CESTA_CONTROLLED |
                  CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL10,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL10),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .CESTA        = { CESTA_IDX_CAM, 2 },
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL5_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL6 =
{
  .szName       = "cam_cc_pll6",
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0xC75C6E13,
  .nFlags       = CLOCK_FLAG_CESTA_CONTROLLED |
                  CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL10,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL10),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .CESTA        = { CESTA_IDX_CAM, 3 },
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL6_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL7 =
{
  .szName       = "cam_cc_pll7",
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0x032BF71E,
  .nFlags       = CLOCK_FLAG_CESTA_CONTROLLED |
                  CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL10,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL10),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .CESTA        = { CESTA_IDX_CAM, 4 },
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL7_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL8 =
{
  .szName       = "cam_cc_pll8",
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0x4A6CF9D1,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL8,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL8),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL8_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL9 =
{
  .szName       = "cam_cc_pll9",
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0x918A07C5,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL9,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL9),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL9_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_DISPCC_DISPCCPLL0 =
{
  .szName       = "disp_cc_pll0",
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0x4C3DD57F,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_DISPCC_DISPCCPLL0,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_DISPCC_DISPCCPLL0),
  .nRailMask    = RAIL_VDD_MM,
  .nConfigMask  = 0x0,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(DISP_CC_PLL0_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_DISPCC_DISPCCPLL1 =
{
  .szName       = "disp_cc_pll1",
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0xECE07681,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_DISPCC_DISPCCPLL1,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_DISPCC_DISPCCPLL1),
  .nRailMask    = RAIL_VDD_MM,
  .nConfigMask  = 0x0,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(DISP_CC_PLL1_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_GCC_GCCGPLL0 =
{
  .szName       = "gcc_gpll0",
  .nRefFreqHz   = 19200000,
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

static ClockSourceNodeType ClockSource_GCC_GCCGPLL1 =
{
  .szName       = "gcc_gpll1",
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0xB6AD3624,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL |
                  CLOCK_FLAG_READ_ONLY,
  .aBSP         = ClockSourceBSP_GCC_GCCGPLL1,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL1),
  .nRailMask    = RAIL_VDD_CX,
  .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(GCC_GPLL1_PLL_MODE),
    .VoterRegister  = {HWIO_PHYS(GCC_PROC_CLK_PLL_ENA_VOTE), 0x2},
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_GCC_GCCGPLL4 =
{
  .szName       = "gcc_gpll4",
  .nRefFreqHz   = 19200000,
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

static ClockSourceNodeType ClockSource_GCC_GCCGPLL9 =
{
  .szName       = "gcc_gpll9",
  .nRefFreqHz   = 19200000,
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
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0x858FC27E,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_GPUCC_GPUCCPLL0,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GPUCC_GPUCCPLL0),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(GPUCC_GPU_CC_PLL0_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_GPUCC_GPUCCPLL1 =
{
  .szName       = "gpu_cc_pll1",
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0x307AC05F,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_GPUCC_GPUCCPLL1,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GPUCC_GPUCCPLL1),
  .nRailMask    = RAIL_VDD_MX,
  .nConfigMask  = 0x0,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(GPUCC_GPU_CC_PLL1_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_VIDEOCC_VIDEOCCPLL0 =
{
  .szName       = "video_cc_pll0",
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0xD9130185,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_VIDEOCC_VIDEOCCPLL0,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_VIDEOCC_VIDEOCCPLL0),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = 0x0,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(VCODEC_VIDEO_CC_PLL0_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_VIDEOCC_VIDEOCCPLL1 =
{
  .szName       = "video_cc_pll1",
  .nRefFreqHz   = 19200000,
  .nUniqueId    = 0x9CFCD8C3,
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_VIDEOCC_VIDEOCCPLL1,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_VIDEOCC_VIDEOCCPLL1),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = 0x0,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(VCODEC_VIDEO_CC_PLL1_PLL_MODE),
    .pmControl      = &HAL_clk_LucidolePLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};


static ClockSourceNodeType *aSources[] =
{
  &ClockSource_CAMCC_CAMCCPLL0,
  &ClockSource_CAMCC_CAMCCPLL1,
  &ClockSource_CAMCC_CAMCCPLL10,
  &ClockSource_CAMCC_CAMCCPLL2,
  &ClockSource_CAMCC_CAMCCPLL3,
  &ClockSource_CAMCC_CAMCCPLL4,
  &ClockSource_CAMCC_CAMCCPLL5,
  &ClockSource_CAMCC_CAMCCPLL6,
  &ClockSource_CAMCC_CAMCCPLL7,
  &ClockSource_CAMCC_CAMCCPLL8,
  &ClockSource_CAMCC_CAMCCPLL9,
  &ClockSource_DISPCC_DISPCCPLL0,
  &ClockSource_DISPCC_DISPCCPLL1,
  &ClockSource_GCC_GCCGPLL0,
  &ClockSource_GCC_GCCGPLL1,
  &ClockSource_GCC_GCCGPLL4,
  &ClockSource_GCC_GCCGPLL9,
  &ClockSource_GPUCC_GPUCCPLL0,
  &ClockSource_GPUCC_GPUCCPLL1,
  &ClockSource_VIDEOCC_VIDEOCCPLL0,
  &ClockSource_VIDEOCC_VIDEOCCPLL1,
  &ClockSource_XO,
};

/*=========================================================================
      Dividers
==========================================================================*/

static ClockDividerNodeType aDividers[] =
{
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
    .szName    = "cam_cc_ife_0_spdm_div_clk_src",
    .nUniqueId = 0x2307C059,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_IFE_0_SPDM_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_ife_1_spdm_div_clk_src",
    .nUniqueId = 0x278D6CEA,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_IFE_1_SPDM_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_ife_2_spdm_div_clk_src",
    .nUniqueId = 0xD3E4B294,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_IFE_2_SPDM_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_ipe_nps_spdm_div_clk_src",
    .nUniqueId = 0xE0D4FE63,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_IPE_NPS_SPDM_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_jpeg_spdm_div_clk_src",
    .nUniqueId = 0xEA3CFA61,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_JPEG_SPDM_DIV_CDIVR),
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
    .szName    = "cam_cc_sfe_0_spdm_div_clk_src",
    .nUniqueId = 0x6141349A,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_SFE_0_SPDM_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_sfe_1_spdm_div_clk_src",
    .nUniqueId = 0x8D5FF382,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_SFE_1_SPDM_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_sfe_2_spdm_div_clk_src",
    .nUniqueId = 0x2D361E2F,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_SFE_2_SPDM_DIV_CDIVR),
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
    .szName    = "disp_cc_mdss_byte1_div_clk_src",
    .nUniqueId = 0x5AC99929,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_BYTE1_DIV_CDIVR),
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
    .szName    = "disp_cc_mdss_dptx1_crypto_div_clk_src",
    .nUniqueId = 0xE2B9610C,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = 0,
      .nFlags      = HAL_CLK_FLAG_DIVIDER_SUPPORTS_HID,
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx1_link_div_clk_src",
    .nUniqueId = 0x0D3EFA4E,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_DPTX1_LINK_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx2_crypto_div_clk_src",
    .nUniqueId = 0x3A8BA1E4,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = 0,
      .nFlags      = HAL_CLK_FLAG_DIVIDER_SUPPORTS_HID,
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx2_link_div_clk_src",
    .nUniqueId = 0x430EBF82,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_DPTX2_LINK_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx3_crypto_div_clk_src",
    .nUniqueId = 0xFC9F97BB,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = 0,
      .nFlags      = HAL_CLK_FLAG_DIVIDER_SUPPORTS_HID,
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx3_link_div_clk_src",
    .nUniqueId = 0x15644C83,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_DPTX3_LINK_DIV_CDIVR),
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
    .szName    = "disp_cc_mdss_spdm_pclk1_div_clk_src",
    .nUniqueId = 0xC61F8E9C,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_SPDM_PCLK1_DIV_CDIVR),
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
    .szName    = "gcc_pdm_xo4_div_clk_src",
    .nUniqueId = 0x45668877,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_PDM_XO4_DIV_CDIVR),
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
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap2_core_div_clk_src",
    .nUniqueId = 0x71FFA9A3,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_QUPV3_WRAP2_CORE_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap3_core_div_clk_src",
    .nUniqueId = 0xCC821DB2,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_QUPV3_WRAP3_CORE_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap3_s0_clk_src",
    .nUniqueId = 0xCED291FE,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_QUPV3_WRAP3_S0_CDIVR),
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
    .szName    = "gpu_cc_gx_gfx3d_div_clk_src",
    .nUniqueId = 0xBD1E1B93,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GPUCC_GPU_CC_GX_GFX3D_DIV_CDIVR),
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
    .szName    = "video_cc_mvs1_div_clk_src",
    .nUniqueId = 0x87081508,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(VCODEC_VIDEO_CC_MVS1_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "video_cc_mvs1c_div2_div_clk_src",
    .nUniqueId = 0x5B279033,
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(VCODEC_VIDEO_CC_MVS1C_DIV2_DIV_CDIVR),
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
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  200000000, &ClockSource_CAMCC_CAMCCPLL8,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL8[ 0] /* 200.0  */ },    /* Mux[6] = CAM_CC_PLL8_OUT_EVEN */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL8,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL8[ 1] /* 400.0  */ },    /* Mux[6] = CAM_CC_PLL8_OUT_EVEN */
  {  480000000, &ClockSource_CAMCC_CAMCCPLL8,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL8[ 2] /* 480.0  */ },    /* Mux[6] = CAM_CC_PLL8_OUT_EVEN */
  {  785000000, &ClockSource_CAMCC_CAMCCPLL8,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL8[ 3] /* 785.0  */ },    /* Mux[6] = CAM_CC_PLL8_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCCAMNOCAXIRT
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCAMNOCAXIRT
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCCAMNOCAXIRT[] =
{
  {  300000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 3,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[3] = CAM_CC_PLL0_OUT_ODD */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCCCI0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCCI0
 *   ClockDomain_CAMCC_CAMCCCCI1
 *   ClockDomain_CAMCC_CAMCCCCI2
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCCCI0[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   37500000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     32,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCCPHYRX
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCPHYRX
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCCPHYRX[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
  {  480000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     5,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCCRE
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCRE
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCCRE[] =
{
  {  200000000, &ClockSource_CAMCC_CAMCCPLL0,             { 3,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[3] = CAM_CC_PLL0_OUT_ODD */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 3,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[3] = CAM_CC_PLL0_OUT_ODD */
  {  480000000, &ClockSource_CAMCC_CAMCCPLL9,             { 5,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[5] = CAM_CC_PLL9_OUT_EVEN */
  {  600000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCSI0PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI1PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI2PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI3PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI4PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI5PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI6PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI7PHYTIMER
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCCSID
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCSID
 *   ClockDomain_CAMCC_CAMCCIFELITE
 *   ClockDomain_CAMCC_CAMCCIFELITECSID
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCCSID[] =
{
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
  {  480000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     5,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCFASTAHB
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCFASTAHB
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCFASTAHB[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  300000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCICP
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCICP
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCICP[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 3,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[3] = CAM_CC_PLL0_OUT_ODD */
  {  480000000, &ClockSource_CAMCC_CAMCCPLL9,             { 5,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[5] = CAM_CC_PLL9_OUT_EVEN */
  {  600000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCIFE0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFE0
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCIFE0[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  466000000, &ClockSource_CAMCC_CAMCCPLL3,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 0] /* 466.0  */ },   /* Mux[6] = CAM_CC_PLL3_OUT_EVEN */
  {  594000000, &ClockSource_CAMCC_CAMCCPLL3,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 1] /* 594.0  */ },   /* Mux[6] = CAM_CC_PLL3_OUT_EVEN */
  {  675000000, &ClockSource_CAMCC_CAMCCPLL3,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 2] /* 675.0  */ },   /* Mux[6] = CAM_CC_PLL3_OUT_EVEN */
  {  785000000, &ClockSource_CAMCC_CAMCCPLL3,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 3] /* 785.0  */ },   /* Mux[6] = CAM_CC_PLL3_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCIFE1
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFE1
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCIFE1[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  466000000, &ClockSource_CAMCC_CAMCCPLL4,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 0] /* 466.0  */ },   /* Mux[6] = CAM_CC_PLL4_OUT_EVEN */
  {  594000000, &ClockSource_CAMCC_CAMCCPLL4,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 1] /* 594.0  */ },   /* Mux[6] = CAM_CC_PLL4_OUT_EVEN */
  {  675000000, &ClockSource_CAMCC_CAMCCPLL4,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 2] /* 675.0  */ },   /* Mux[6] = CAM_CC_PLL4_OUT_EVEN */
  {  785000000, &ClockSource_CAMCC_CAMCCPLL4,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 3] /* 785.0  */ },   /* Mux[6] = CAM_CC_PLL4_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCIFE2
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFE2
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCIFE2[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  466000000, &ClockSource_CAMCC_CAMCCPLL5,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 0] /* 466.0  */ },   /* Mux[6] = CAM_CC_PLL5_OUT_EVEN */
  {  594000000, &ClockSource_CAMCC_CAMCCPLL5,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 1] /* 594.0  */ },   /* Mux[6] = CAM_CC_PLL5_OUT_EVEN */
  {  675000000, &ClockSource_CAMCC_CAMCCPLL5,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 2] /* 675.0  */ },   /* Mux[6] = CAM_CC_PLL5_OUT_EVEN */
  {  785000000, &ClockSource_CAMCC_CAMCCPLL5,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 3] /* 785.0  */ },   /* Mux[6] = CAM_CC_PLL5_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCIPENPS
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIPENPS
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCIPENPS[] =
{
  {  455000000, &ClockSource_CAMCC_CAMCCPLL1,             { 4,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_CAMCC_CAMCCPLL1[ 0] /* 455.0  */ },  /* Mux[4] = CAM_CC_PLL1_OUT_EVEN */
  {  475000000, &ClockSource_CAMCC_CAMCCPLL1,             { 4,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_CAMCC_CAMCCPLL1[ 1] /* 475.0  */ },  /* Mux[4] = CAM_CC_PLL1_OUT_EVEN */
  {  575000000, &ClockSource_CAMCC_CAMCCPLL1,             { 4,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL1[ 2] /* 575.0  */ },    /* Mux[4] = CAM_CC_PLL1_OUT_EVEN */
  {  675000000, &ClockSource_CAMCC_CAMCCPLL1,             { 4,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL1[ 3] /* 675.0  */ },    /* Mux[4] = CAM_CC_PLL1_OUT_EVEN */
  {  825000000, &ClockSource_CAMCC_CAMCCPLL1,             { 4,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL1[ 4] /* 825.0  */ },    /* Mux[4] = CAM_CC_PLL1_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCJPEG
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCJPEG
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCJPEG[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  200000000, &ClockSource_CAMCC_CAMCCPLL0,             { 3,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[3] = CAM_CC_PLL0_OUT_ODD */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 3,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[3] = CAM_CC_PLL0_OUT_ODD */
  {  480000000, &ClockSource_CAMCC_CAMCCPLL9,             { 5,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[5] = CAM_CC_PLL9_OUT_EVEN */
  {  600000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
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
 *   ClockDomain_CAMCC_CAMCCMCLK5
 *   ClockDomain_CAMCC_CAMCCMCLK6
 *   ClockDomain_CAMCC_CAMCCMCLK7
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCMCLK0[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO_MX */
  {   24000000, &ClockSource_CAMCC_CAMCCPLL2,             { 3,     20,    1,     4,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[3] = CAM_CC_PLL2_OUT_EVEN */
  {   68571429, &ClockSource_CAMCC_CAMCCPLL2,             { 5,     28,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[5] = CAM_CC_PLL2_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCQDSSDEBUG
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCQDSSDEBUG
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCQDSSDEBUG[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   75000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     16,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
  {  150000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
  {  300000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCSFE0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCSFE0
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCSFE0[] =
{
  {  466000000, &ClockSource_CAMCC_CAMCCPLL6,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 0] /* 466.0  */ },   /* Mux[6] = CAM_CC_PLL6_OUT_EVEN */
  {  594000000, &ClockSource_CAMCC_CAMCCPLL6,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 1] /* 594.0  */ },   /* Mux[6] = CAM_CC_PLL6_OUT_EVEN */
  {  675000000, &ClockSource_CAMCC_CAMCCPLL6,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 2] /* 675.0  */ },   /* Mux[6] = CAM_CC_PLL6_OUT_EVEN */
  {  785000000, &ClockSource_CAMCC_CAMCCPLL6,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 3] /* 785.0  */ },   /* Mux[6] = CAM_CC_PLL6_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCSFE1
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCSFE1
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCSFE1[] =
{
  {  466000000, &ClockSource_CAMCC_CAMCCPLL7,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 0] /* 466.0  */ },   /* Mux[6] = CAM_CC_PLL7_OUT_EVEN */
  {  594000000, &ClockSource_CAMCC_CAMCCPLL7,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 1] /* 594.0  */ },   /* Mux[6] = CAM_CC_PLL7_OUT_EVEN */
  {  675000000, &ClockSource_CAMCC_CAMCCPLL7,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 2] /* 675.0  */ },   /* Mux[6] = CAM_CC_PLL7_OUT_EVEN */
  {  785000000, &ClockSource_CAMCC_CAMCCPLL7,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 3] /* 785.0  */ },   /* Mux[6] = CAM_CC_PLL7_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCSFE2
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCSFE2
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCSFE2[] =
{
  {  466000000, &ClockSource_CAMCC_CAMCCPLL10,            { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 0] /* 466.0  */ },   /* Mux[6] = CAM_CC_PLL10_OUT_EVEN */
  {  594000000, &ClockSource_CAMCC_CAMCCPLL10,            { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 1] /* 594.0  */ },   /* Mux[6] = CAM_CC_PLL10_OUT_EVEN */
  {  675000000, &ClockSource_CAMCC_CAMCCPLL10,            { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 2] /* 675.0  */ },   /* Mux[6] = CAM_CC_PLL10_OUT_EVEN */
  {  785000000, &ClockSource_CAMCC_CAMCCPLL10,            { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL10[ 3] /* 785.0  */ },   /* Mux[6] = CAM_CC_PLL10_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCSLEEP
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCSLEEP
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
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   80000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     15,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCXO
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCXO
 *   ClockDomain_GCC_GCCPCIE0AUX
 *   ClockDomain_GCC_GCCPCIE1AUX
 *   ClockDomain_GCC_GCCQUPV3I2CS0
 *   ClockDomain_GCC_GCCQUPV3I2CS1
 *   ClockDomain_GCC_GCCQUPV3I2CS2
 *   ClockDomain_GCC_GCCQUPV3I2CS3
 *   ClockDomain_GCC_GCCQUPV3I2CS4
 *   ClockDomain_GCC_GCCQUPV3I2CS5
 *   ClockDomain_GCC_GCCQUPV3I2CS6
 *   ClockDomain_GCC_GCCQUPV3I2CS7
 *   ClockDomain_GCC_GCCQUPV3I2CS8
 *   ClockDomain_GCC_GCCQUPV3I2CS9
 *   ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI
 *   ClockDomain_GCC_GCCUSB3PRIMPHYAUX
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
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },                                                            /* Mux[0] = BI_TCXO */
  {   37500000, &ClockSource_DISPCC_DISPCCPLL1,           { 4,     32,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[4] = DISP_CC_PLL1_OUT_MAIN */
  {   75000000, &ClockSource_DISPCC_DISPCCPLL1,           { 4,     16,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[4] = DISP_CC_PLL1_OUT_MAIN */
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
 *   ClockDomain_VIDEOCC_VIDEOCCAHB
 *   ClockDomain_VIDEOCC_VIDEOCCXO
 */
static ClockMuxConfigType ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },                                                            /* Mux[0] = BI_TCXO */
};

/*
 * ClockDomainBSP_DISPCC_DISPCCMDSSMDP
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSMDP
 */
static ClockMuxConfigType ClockDomainBSP_DISPCC_DISPCCMDSSMDP[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },                                                            /* Mux[0] = BI_TCXO */
  {   85714286, &ClockSource_DISPCC_DISPCCPLL0,           { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, {{0}}, &ClockSourceBSP_DISPCC_DISPCCPLL0[ 0] /* 257.0  */ },  /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  100000000, &ClockSource_DISPCC_DISPCCPLL0,           { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, {{0}}, &ClockSourceBSP_DISPCC_DISPCCPLL0[ 1] /* 300.0  */ },  /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  150000000, &ClockSource_DISPCC_DISPCCPLL0,           { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, {{0}}, &ClockSourceBSP_DISPCC_DISPCCPLL0[ 2] /* 450.0  */ },  /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  200000000, &ClockSource_DISPCC_DISPCCPLL0,           { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_DISPCC_DISPCCPLL0[ 3] /* 600.0  */ },  /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  325000000, &ClockSource_DISPCC_DISPCCPLL0,           { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_DISPCC_DISPCCPLL0[ 4] /* 975.0  */ },  /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  402000000, &ClockSource_DISPCC_DISPCCPLL0,           { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_DISPCC_DISPCCPLL0[ 5] /* 1206.0 */ },  /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  514000000, &ClockSource_DISPCC_DISPCCPLL0,           { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_DISPCC_DISPCCPLL0[ 6] /* 1542.0 */ },  /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_DISPCC_DISPCCSLEEP
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCSLEEP
 *   ClockDomain_VIDEOCC_VIDEOCCSLEEP
 */
static ClockMuxConfigType ClockDomainBSP_DISPCC_DISPCCSLEEP[] =
{
  {      32000, NULL,                                     { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },                                                            /* Mux[0] = CHIP_SLEEP_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCCPUSSUBWCP
 *
 * Used by:
 *   ClockDomain_GCC_GCCCPUSSUBWCP
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCCPUSSUBWCP[] =
{
  {  300000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN */
  {  403000000, &ClockSource_GCC_GCCGPLL4,                { 5,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[5] = GCC_GPLL4_OUT_MAIN */
  {  533000000, &ClockSource_GCC_GCCGPLL1,                { 4,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[4] = GCC_GPLL1_OUT_MAIN */
  {  710666667, &ClockSource_GCC_GCCGPLL1,                { 4,     3,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR,        },                                                            /* Mux[4] = GCC_GPLL1_OUT_MAIN */
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
  {   50000000, &ClockSource_GCC_GCCGPLL0,                { 6,     12,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP28_CLKGEN_ACGC_CLK */
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
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 6,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP23_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCPDM2
 *
 * Used by:
 *   ClockDomain_GCC_GCCPDM2
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCPDM2[] =
{
  {   60000000, &ClockSource_GCC_GCCGPLL0,                { 1,     20,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP5_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCQUPV3WRAP1QSPIREF
 *
 * Note: These frequencies are used by domains possibly under DFS control. The
 *       DFS-enable state will be detected during init. If under DFS control,
 *       the domain will dynamically allocate its own BSP array and populate
 *       it with configurations detected from the DFS registers.
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP1QSPIREF
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP1QSPIREF[] =
{
  {  150000000, &ClockSource_GCC_GCCGPLL0,                { 6,     4,     0,     0,     0x00 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {  240000000, &ClockSource_GCC_GCCGPLL0,                { 1,     5,     0,     0,     0x01 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP7_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCQUPV3WRAP1S0
 *
 * Note: These frequencies are used by domains possibly under DFS control. The
 *       DFS-enable state will be detected during init. If under DFS control,
 *       the domain will dynamically allocate its own BSP array and populate
 *       it with configurations detected from the DFS registers.
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP1S0
 *   ClockDomain_GCC_GCCQUPV3WRAP1S1
 *   ClockDomain_GCC_GCCQUPV3WRAP2S0
 *   ClockDomain_GCC_GCCQUPV3WRAP2S1
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP1S0[] =
{
  {    7372800, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     384,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   14745600, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     768,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0x00 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   29491200, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     1536,  15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   32000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     75,    0x01 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   48000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     25,    0x02 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   64000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     16,    75,    0x03 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   75000000, &ClockSource_GCC_GCCGPLL0,                { 6,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   80000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     15,    0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   96000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     25,    0x04 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 1,     12,    0,     0,     0x05 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP7_CLKGEN_ACGC_CLK */
  {  102400000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     128,   375,   0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {  112000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     28,    75,    0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {  117964800, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     6144,  15625, 0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {  120000000, &ClockSource_GCC_GCCGPLL0,                { 1,     10,    0,     0,     0x06 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP7_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCQUPV3WRAP1S3
 *
 * Note: These frequencies are used by domains possibly under DFS control. The
 *       DFS-enable state will be detected during init. If under DFS control,
 *       the domain will dynamically allocate its own BSP array and populate
 *       it with configurations detected from the DFS registers.
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP1S3
 *   ClockDomain_GCC_GCCQUPV3WRAP1S5
 *   ClockDomain_GCC_GCCQUPV3WRAP1S7
 *   ClockDomain_GCC_GCCQUPV3WRAP2S4
 *   ClockDomain_GCC_GCCQUPV3WRAP2S5
 *   ClockDomain_GCC_GCCQUPV3WRAP2S7
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP1S3[] =
{
  {    7372800, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     384,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   14745600, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     768,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0x00 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   29491200, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     1536,  15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   32000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     75,    0x01 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   48000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     25,    0x02 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   64000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     16,    75,    0x03 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   75000000, &ClockSource_GCC_GCCGPLL0,                { 6,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   80000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     15,    0x04 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   96000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     25,    0x05 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 1,     12,    0,     0,     0x06 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP7_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCQUPV3WRAP1S4
 *
 * Note: These frequencies are used by domains possibly under DFS control. The
 *       DFS-enable state will be detected during init. If under DFS control,
 *       the domain will dynamically allocate its own BSP array and populate
 *       it with configurations detected from the DFS registers.
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP1S4
 *   ClockDomain_GCC_GCCQUPV3WRAP1S6
 *   ClockDomain_GCC_GCCQUPV3WRAP2S2
 *   ClockDomain_GCC_GCCQUPV3WRAP2S3
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP1S4[] =
{
  {    7372800, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     384,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   14745600, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     768,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0x00 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   29491200, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     1536,  15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   32000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     75,    0x01 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   48000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     25,    0x02 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   64000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     16,    75,    0x03 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   75000000, &ClockSource_GCC_GCCGPLL0,                { 6,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   80000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     15,    0x04 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {   96000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     25,    0x05 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP25_CLKGEN_ACGC_CLK */
  {  120000000, &ClockSource_GCC_GCCGPLL0,                { 1,     10,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP7_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCQUPV3WRAP2IBICTRL0
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP2IBICTRL0
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP2IBICTRL0[] =
{
  {   37500000, &ClockSource_GCC_GCCGPLL0,                { 6,     16,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP26_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCQUPV3WRAP2S6
 *
 * Note: These frequencies are used by domains possibly under DFS control. The
 *       DFS-enable state will be detected during init. If under DFS control,
 *       the domain will dynamically allocate its own BSP array and populate
 *       it with configurations detected from the DFS registers.
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP2S6
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP2S6[] =
{
  {    7372800, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     384,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP26_CLKGEN_ACGC_CLK */
  {   14745600, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     768,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP26_CLKGEN_ACGC_CLK */
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0x00 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   29491200, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     1536,  15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP26_CLKGEN_ACGC_CLK */
  {   32000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     75,    0x01 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP26_CLKGEN_ACGC_CLK */
  {   48000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     25,    0x02 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP26_CLKGEN_ACGC_CLK */
  {   64000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     16,    75,    0x03 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP26_CLKGEN_ACGC_CLK */
  {   75000000, &ClockSource_GCC_GCCGPLL0,                { 6,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP26_CLKGEN_ACGC_CLK */
  {   80000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     15,    0x04 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP26_CLKGEN_ACGC_CLK */
  {   96000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     25,    0x05 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP26_CLKGEN_ACGC_CLK */
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 1,     12,    0,     0,     0x06 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP8_CLKGEN_ACGC_CLK */
  {  128000000, &ClockSource_GCC_GCCGPLL0,                { 1,     2,     16,    75,    0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP8_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCQUPV3WRAP3QSPIREF
 *
 * Note: These frequencies are used by domains possibly under DFS control. The
 *       DFS-enable state will be detected during init. If under DFS control,
 *       the domain will dynamically allocate its own BSP array and populate
 *       it with configurations detected from the DFS registers.
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP3QSPIREF
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP3QSPIREF[] =
{
  {  300000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     0,     0,     0x00 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN */
  {  400000000, &ClockSource_GCC_GCCGPLL0,                { 1,     3,     0,     0,     0x01 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN */
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
  {   25000000, &ClockSource_GCC_GCCGPLL0,                { 6,     24,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP23_CLKGEN_ACGC_CLK */
  {   37500000, &ClockSource_GCC_GCCGPLL0,                { 6,     16,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP23_CLKGEN_ACGC_CLK */
  {   50000000, &ClockSource_GCC_GCCGPLL0,                { 6,     12,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP23_CLKGEN_ACGC_CLK */
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 6,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP23_CLKGEN_ACGC_CLK */
  {  202000000, &ClockSource_GCC_GCCGPLL9,                { 2,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[2] = GCC_GPLL9_OUT_MAIN */
};

/*
 * ClockDomainBSP_GCC_GCCSDCC4APPS
 *
 * Used by:
 *   ClockDomain_GCC_GCCSDCC4APPS
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCSDCC4APPS[] =
{
  {     400000, &ClockSource_XO,                          { 0,     24,    1,     4,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   25000000, &ClockSource_GCC_GCCGPLL0,                { 6,     24,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP23_CLKGEN_ACGC_CLK */
  {   75000000, &ClockSource_GCC_GCCGPLL0,                { 6,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP23_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCUFSPHYAXI
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYAXI
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCUFSPHYAXI[] =
{
  {   25000000, &ClockSource_GCC_GCCGPLL0,                { 6,     24,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP23_CLKGEN_ACGC_CLK */
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 6,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP23_CLKGEN_ACGC_CLK */
  {  201500000, &ClockSource_GCC_GCCGPLL4,                { 5,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[5] = GCC_GPLL4_OUT_MAIN */
  {  403000000, &ClockSource_GCC_GCCGPLL4,                { 5,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[5] = GCC_GPLL4_OUT_MAIN */
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
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 6,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP23_CLKGEN_ACGC_CLK */
  {  201500000, &ClockSource_GCC_GCCGPLL4,                { 5,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[5] = GCC_GPLL4_OUT_MAIN */
  {  403000000, &ClockSource_GCC_GCCGPLL4,                { 5,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[5] = GCC_GPLL4_OUT_MAIN */
};

/*
 * ClockDomainBSP_GCC_GCCUFSPHYPHYAUX
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYPHYAUX
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCUFSPHYPHYAUX[] =
{
  {    9600000, &ClockSource_XO,                          { 0,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
};

/*
 * ClockDomainBSP_GCC_GCCUSB30PRIMMASTER
 *
 * Used by:
 *   ClockDomain_GCC_GCCUSB30PRIMMASTER
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCUSB30PRIMMASTER[] =
{
  {   66666667, &ClockSource_GCC_GCCGPLL0,                { 6,     9,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP30_CLKGEN_ACGC_CLK */
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
  {  200000000, NULL,                                     { 5,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D2, {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}, },       /* Mux[5] = GPLL0_OUT_MAIN */
  {  200000000, NULL,                                     { 5,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}, },       /* Mux[5] = GPLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_GPUCC_GPUCCGMU
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCGMU
 */
static ClockMuxConfigType ClockDomainBSP_GPUCC_GPUCCGMU[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D2, },                                                            /* Mux[0] = BI_TCXO */
  {  260000000, &ClockSource_GPUCC_GPUCCPLL1,             { 3,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D2, {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_GPUCC_GPUCCPLL1[ 0] /* 520.0  */ },  /* Mux[3] = GPU_CC_PLL1_OUT_MAIN */
  {  260000000, &ClockSource_GPUCC_GPUCCPLL1,             { 3,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_GPUCC_GPUCCPLL1[ 0] /* 520.0  */ },  /* Mux[3] = GPU_CC_PLL1_OUT_MAIN */
  {  625000000, &ClockSource_GPUCC_GPUCCPLL1,             { 3,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_GPUCC_GPUCCPLL1[ 1] /* 1250.0 */ },  /* Mux[3] = GPU_CC_PLL1_OUT_MAIN */
  {  625000000, &ClockSource_GPUCC_GPUCCPLL1,             { 3,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_GPUCC_GPUCCPLL1[ 1] /* 1250.0 */ },  /* Mux[3] = GPU_CC_PLL1_OUT_MAIN */
};

/*
 * ClockDomainBSP_GPUCC_GPUCCGXGFX3D
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCGXGFX3D
 */
static ClockMuxConfigType ClockDomainBSP_GPUCC_GPUCCGXGFX3D[] =
{
  {  231000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D2, {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 0] /* 462.0  */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  310000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 1] /* 620.0  */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  366000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D0, {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 2] /* 732.0  */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  422000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 3] /* 844.0  */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  500000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_L1, {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 4] /* 1000.0 */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  578000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 5] /* 1156.0 */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  629000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L0,     {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 6] /* 1258.0 */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  680000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 7] /* 1360.0 */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  720000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L2,     {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 8] /* 1440.0 */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  770000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 9] /* 1540.0 */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  834000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM_L1,     {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[10] /* 1668.0 */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  869000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR,        {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_GPUCC_GPUCCPLL0[11] /* 1738.0 */ },  /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  903000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR,        {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_GPUCC_GPUCCPLL0[12] /* 1806.0 */ },  /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  903000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR_L1,     {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_GPUCC_GPUCCPLL0[12] /* 1806.0 */ },  /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  { 1000000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR_L1,     {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_GPUCC_GPUCCPLL0[13] /* 2000.0 */ },  /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  { 1100000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR_L2,     {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_GPUCC_GPUCCPLL0[14] /* 2200.0 */ },  /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
};

/*
 * ClockDomainBSP_GPUCC_GPUCCHUB
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCHUB
 */
static ClockMuxConfigType ClockDomainBSP_GPUCC_GPUCCHUB[] =
{
  {  200000000, NULL,                                     { 5,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D2, {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}, },       /* Mux[5] = GPLL0_OUT_MAIN */
  {  200000000, NULL,                                     { 5,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}, },       /* Mux[5] = GPLL0_OUT_MAIN */
  {  300000000, NULL,                                     { 5,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[5] = GPLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_VIDEOCC_VIDEOCCMVS0
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCMVS0
 */
static ClockMuxConfigType ClockDomainBSP_VIDEOCC_VIDEOCCMVS0[] =
{
  {  588000000, &ClockSource_VIDEOCC_VIDEOCCPLL0,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL0[ 0] /* 588.0  */ },  /* Mux[1] = VIDEO_CC_PLL0_OUT_MAIN */
  {  840000000, &ClockSource_VIDEOCC_VIDEOCCPLL0,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL0[ 1] /* 840.0  */ },  /* Mux[1] = VIDEO_CC_PLL0_OUT_MAIN */
  {  900000000, &ClockSource_VIDEOCC_VIDEOCCPLL0,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL0[ 2] /* 900.0  */ },  /* Mux[1] = VIDEO_CC_PLL0_OUT_MAIN */
  { 1140000000, &ClockSource_VIDEOCC_VIDEOCCPLL0,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL0[ 3] /* 1140.0 */ },  /* Mux[1] = VIDEO_CC_PLL0_OUT_MAIN */
  { 1140000000, &ClockSource_VIDEOCC_VIDEOCCPLL0,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL0[ 3] /* 1140.0 */ },  /* Mux[1] = VIDEO_CC_PLL0_OUT_MAIN */
  { 1305000000, &ClockSource_VIDEOCC_VIDEOCCPLL0,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL0[ 4] /* 1305.0 */ },  /* Mux[1] = VIDEO_CC_PLL0_OUT_MAIN */
  { 1440000000, &ClockSource_VIDEOCC_VIDEOCCPLL0,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL0[ 5] /* 1440.0 */ },  /* Mux[1] = VIDEO_CC_PLL0_OUT_MAIN */
  { 1600000000, &ClockSource_VIDEOCC_VIDEOCCPLL0,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR,        {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL0[ 6] /* 1600.0 */ },  /* Mux[1] = VIDEO_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_VIDEOCC_VIDEOCCMVS1
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCMVS1
 */
static ClockMuxConfigType ClockDomainBSP_VIDEOCC_VIDEOCCMVS1[] =
{
  {  840000000, &ClockSource_VIDEOCC_VIDEOCCPLL1,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL1[ 0] /* 840.0  */ },  /* Mux[1] = VIDEO_CC_PLL1_OUT_MAIN */
  { 1050000000, &ClockSource_VIDEOCC_VIDEOCCPLL1,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL1[ 1] /* 1050.0 */ },  /* Mux[1] = VIDEO_CC_PLL1_OUT_MAIN */
  { 1110000000, &ClockSource_VIDEOCC_VIDEOCCPLL1,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL1[ 2] /* 1110.0 */ },  /* Mux[1] = VIDEO_CC_PLL1_OUT_MAIN */
  { 1350000000, &ClockSource_VIDEOCC_VIDEOCCPLL1,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL1[ 3] /* 1350.0 */ },  /* Mux[1] = VIDEO_CC_PLL1_OUT_MAIN */
  { 1350000000, &ClockSource_VIDEOCC_VIDEOCCPLL1,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL1[ 3] /* 1350.0 */ },  /* Mux[1] = VIDEO_CC_PLL1_OUT_MAIN */
  { 1500000000, &ClockSource_VIDEOCC_VIDEOCCPLL1,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL1[ 4] /* 1500.0 */ },  /* Mux[1] = VIDEO_CC_PLL1_OUT_MAIN */
  { 1650000000, &ClockSource_VIDEOCC_VIDEOCCPLL1,         { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOCCPLL1[ 5] /* 1650.0 */ },  /* Mux[1] = VIDEO_CC_PLL1_OUT_MAIN */
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
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCBPS[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 6,          0, &ClockSource_CAMCC_CAMCCPLL8,            2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCAMNOCAXIRT
 *   ClockDomain_CAMCC_CAMCCCCI0
 *   ClockDomain_CAMCC_CAMCCCCI1
 *   ClockDomain_CAMCC_CAMCCCCI2
 *   ClockDomain_CAMCC_CAMCCCPHYRX
 *   ClockDomain_CAMCC_CAMCCCRE
 *   ClockDomain_CAMCC_CAMCCCSI0PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI1PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI2PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI3PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI4PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI5PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI6PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI7PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSID
 *   ClockDomain_CAMCC_CAMCCFASTAHB
 *   ClockDomain_CAMCC_CAMCCICP
 *   ClockDomain_CAMCC_CAMCCIFELITE
 *   ClockDomain_CAMCC_CAMCCIFELITECSID
 *   ClockDomain_CAMCC_CAMCCJPEG
 *   ClockDomain_CAMCC_CAMCCQDSSDEBUG
 *   ClockDomain_CAMCC_CAMCCSLOWAHB
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1, 1200000000, &ClockSource_CAMCC_CAMCCPLL0,            1, },
  { 2,  600000000, &ClockSource_CAMCC_CAMCCPLL0,            2, },
  { 3,  400000000, &ClockSource_CAMCC_CAMCCPLL0,            3, },
  { 4,  320000000, &ClockSource_CAMCC_CAMCCPLL9,            3, },
  { 5,  480000000, &ClockSource_CAMCC_CAMCCPLL9,            2, },
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
 * ClockSourceMap_CAMCC_CAMCCIFE0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFE0
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCIFE0[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 6,          0, &ClockSource_CAMCC_CAMCCPLL3,            2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCIFE1
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFE1
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCIFE1[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 6,          0, &ClockSource_CAMCC_CAMCCPLL4,            2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCIFE2
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFE2
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCIFE2[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 6,          0, &ClockSource_CAMCC_CAMCCPLL5,            2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCIPENPS
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIPENPS
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCIPENPS[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 4,          0, &ClockSource_CAMCC_CAMCCPLL1,            2, },
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
 *   ClockDomain_CAMCC_CAMCCMCLK5
 *   ClockDomain_CAMCC_CAMCCMCLK6
 *   ClockDomain_CAMCC_CAMCCMCLK7
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCMCLK0[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 3,  960000000, &ClockSource_CAMCC_CAMCCPLL2,            1, },
  { 5,  960000000, &ClockSource_CAMCC_CAMCCPLL2,            1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCPLLTESTSTAGE1015MUX
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCPLLTESTSTAGE1015MUX
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCPLLTESTSTAGE1015MUX[] =
{
  { 0,          0, &ClockSource_CAMCC_CAMCCPLL0,            1, },
  { 1,          0, &ClockSource_CAMCC_CAMCCPLL8,            1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCSFE0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCSFE0
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCSFE0[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 6,          0, &ClockSource_CAMCC_CAMCCPLL6,            2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCSFE1
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCSFE1
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCSFE1[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 6,          0, &ClockSource_CAMCC_CAMCCPLL7,            2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCSFE2
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCSFE2
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCSFE2[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 6,          0, &ClockSource_CAMCC_CAMCCPLL10,           2, },
  { 7,  400000000, NULL,                                    1, },
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
  { 4,  600000000, &ClockSource_DISPCC_DISPCCPLL1,          1, },
  { 6,  600000000, &ClockSource_DISPCC_DISPCCPLL1,          1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSBYTE0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSBYTE0
 *   ClockDomain_DISPCC_DISPCCMDSSBYTE1
 *   ClockDomain_DISPCC_DISPCCMDSSPCLK0
 *   ClockDomain_DISPCC_DISPCCMDSSPCLK1
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSBYTE0[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,          0, NULL,                                    1, },
  { 2,          0, NULL,                                    1, },
  { 3,          0, NULL,                                    1, },
  { 4,          0, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSDPTX0AUX
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3AUX
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
  { 2,          0, NULL,                                    1, },
  { 3,          0, NULL,                                    1, },
  { 4,          0, NULL,                                    1, },
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
  { 3,          0, NULL,                                    1, },
  { 4,          0, NULL,                                    1, },
  { 6,          0, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSDPTX1LINK
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSDPTX1LINK[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 2,          0, NULL,                                    1, },
  { 3,          0, NULL,                                    1, },
  { 4,          0, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSDPTX1PIXEL0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3PIXEL0
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSDPTX1PIXEL0[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 3,          0, NULL,                                    1, },
  { 4,          0, NULL,                                    1, },
  { 6,          0, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSESC0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSESC0
 *   ClockDomain_DISPCC_DISPCCMDSSESC1
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSESC0[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 2,          0, NULL,                                    1, },
  { 4,          0, NULL,                                    1, },
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
  { 4,  600000000, &ClockSource_DISPCC_DISPCCPLL1,          1, },
  { 6,  600000000, &ClockSource_DISPCC_DISPCCPLL1,          1, },
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
  { 1,  600000000, &ClockSource_DISPCC_DISPCCPLL1,          1, },
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
 * ClockSourceMap_GCC_GCCCPUSSUBWCP
 *
 * Used by:
 *   ClockDomain_GCC_GCCCPUSSUBWCP
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCCPUSSUBWCP[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 2,  750000000, NULL,                                    1, },
  { 3, 1100000000, NULL,                                    1, },
  { 4, 1066000000, &ClockSource_GCC_GCCGPLL1,               1, },
  { 5,  806000000, &ClockSource_GCC_GCCGPLL4,               1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
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
 *   ClockDomain_GCC_GCCPDM2
 *   ClockDomain_GCC_GCCSDCC4APPS
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
  { 0,          0, NULL,                                    1, },
  { 1,          0, NULL,                                    1, },
  { 2,   19200000, &ClockSource_XO,                         1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCPCIE1PHYAUX
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE1PHYAUX
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCPCIE1PHYAUX[] =
{
  { 0,   20000000, NULL,                                    1, },
  { 1,  400000000, NULL,                                    1, },
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
  { 0,          0, NULL,                                    1, },
  { 1,          0, NULL,                                    1, },
  { 2,   19200000, &ClockSource_XO,                         1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCQUPV3I2CS0
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3I2CS0
 *   ClockDomain_GCC_GCCQUPV3I2CS1
 *   ClockDomain_GCC_GCCQUPV3I2CS2
 *   ClockDomain_GCC_GCCQUPV3I2CS3
 *   ClockDomain_GCC_GCCQUPV3I2CS4
 *   ClockDomain_GCC_GCCQUPV3I2CS5
 *   ClockDomain_GCC_GCCQUPV3I2CS6
 *   ClockDomain_GCC_GCCQUPV3I2CS7
 *   ClockDomain_GCC_GCCQUPV3I2CS8
 *   ClockDomain_GCC_GCCQUPV3I2CS9
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCQUPV3I2CS0[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
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
 *   ClockDomain_GCC_GCCQUPV3WRAP1S4
 *   ClockDomain_GCC_GCCQUPV3WRAP1S5
 *   ClockDomain_GCC_GCCQUPV3WRAP1S6
 *   ClockDomain_GCC_GCCQUPV3WRAP1S7
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
 * ClockSourceMap_GCC_GCCQUPV3WRAP2IBICTRL0
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP2IBICTRL0
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCQUPV3WRAP2IBICTRL0[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 4, 1066000000, &ClockSource_GCC_GCCGPLL1,               1, },
  { 5,  806000000, &ClockSource_GCC_GCCGPLL4,               1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCQUPV3WRAP2S0
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP2S0
 *   ClockDomain_GCC_GCCQUPV3WRAP2S1
 *   ClockDomain_GCC_GCCQUPV3WRAP2S2
 *   ClockDomain_GCC_GCCQUPV3WRAP2S3
 *   ClockDomain_GCC_GCCQUPV3WRAP2S4
 *   ClockDomain_GCC_GCCQUPV3WRAP2S5
 *   ClockDomain_GCC_GCCQUPV3WRAP2S7
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCQUPV3WRAP2S0[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCQUPV3WRAP2S6
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP2S6
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCQUPV3WRAP2S6[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
  { 2,  500000000, NULL,                                    1, },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               2, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCQUPV3WRAP3QSPIREF
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP3QSPIREF
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCQUPV3WRAP3QSPIREF[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               1, },
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
 *   ClockDomain_GCC_GCCUFSPHYICECORE
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
 *   ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI
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
 * ClockSourceMap_GCC_GCCUSB3PRIMPHYPIPE
 *
 * Used by:
 *   ClockDomain_GCC_GCCUSB3PRIMPHYPIPE
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUSB3PRIMPHYPIPE[] =
{
  { 0,          0, NULL,                                    1, },
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
 */
static const ClockSourceMapType ClockSourceMap_GPUCC_GPUCCGMU[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,          0, &ClockSource_GPUCC_GPUCCPLL0,            1, },
  { 3,          0, &ClockSource_GPUCC_GPUCCPLL1,            1, },
  { 5,  600000000, NULL,                                    1, },
  { 6,  300000000, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GPUCC_GPUCCGXGFX3D
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCGXGFX3D
 */
static const ClockSourceMapType ClockSourceMap_GPUCC_GPUCCGXGFX3D[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,          0, &ClockSource_GPUCC_GPUCCPLL0,            1, },
  { 2,          0, &ClockSource_GPUCC_GPUCCPLL0,            1, },
  { 3,          0, &ClockSource_GPUCC_GPUCCPLL1,            1, },
  { 4,          0, &ClockSource_GPUCC_GPUCCPLL1,            1, },
  { 5,  600000000, NULL,                                    1, },
  { 7,  400000000, NULL,                                    1, },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GPUCC_GPUCCHUB
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCHUB
 */
static const ClockSourceMapType ClockSourceMap_GPUCC_GPUCCHUB[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 3,          0, &ClockSource_GPUCC_GPUCCPLL1,            1, },
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
  { 1,          0, &ClockSource_GPUCC_GPUCCPLL1,            1, },
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
 * ClockSourceMap_VIDEOCC_VIDEOCCMVS1
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCMVS1
 */
static const ClockSourceMapType ClockSourceMap_VIDEOCC_VIDEOCCMVS1[] =
{
  { 0,   19200000, &ClockSource_XO,                         1, },
  { 1,          0, &ClockSource_VIDEOCC_VIDEOCCPLL1,        1, },
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
  { 1,          0, &ClockSource_VIDEOCC_VIDEOCCPLL1,        1, },
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
  {  120000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  {  124800000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  {  158400000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  {  163200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  {  235200000, RAIL_VOLTAGE_LEVEL_SVS,        {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  {  240000000, RAIL_VOLTAGE_LEVEL_SVS,        {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  {  302400000, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  {  312000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  {  364800000, RAIL_VOLTAGE_LEVEL_NOM,        {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  {  384000000, RAIL_VOLTAGE_LEVEL_NOM,        {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  {  417600000, RAIL_VOLTAGE_LEVEL_NOM_L1,     {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  {  436800000, RAIL_VOLTAGE_LEVEL_NOM_L1,     {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  {  456000000, RAIL_VOLTAGE_LEVEL_TUR,        {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  {  499200000, RAIL_VOLTAGE_LEVEL_TUR,        {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  {  518400000, RAIL_VOLTAGE_LEVEL_TUR_L1,     {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  {  561600000, RAIL_VOLTAGE_LEVEL_TUR_L1,     {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  {  614400000, RAIL_VOLTAGE_LEVEL_TUR_L3,     {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  {  657600000, RAIL_VOLTAGE_LEVEL_TUR_L3,     {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
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
  {  200000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  400000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  480000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  785000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCCAMNOCAXIRT
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCAMNOCAXIRT
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCCAMNOCAXIRT[] =
{
  {  300000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  400000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCCCI0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCCI0
 *   ClockDomain_CAMCC_CAMCCCCI1
 *   ClockDomain_CAMCC_CAMCCCCI2
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCCCI0[] =
{
  {   37500000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCCPHYRX
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCPHYRX
 *   ClockDomain_CAMCC_CAMCCCSID
 *   ClockDomain_CAMCC_CAMCCIFELITE
 *   ClockDomain_CAMCC_CAMCCIFELITECSID
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCCPHYRX[] =
{
  {  400000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  480000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCCRE
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCRE
 *   ClockDomain_CAMCC_CAMCCJPEG
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCCRE[] =
{
  {  200000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  400000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  480000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
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
 *   ClockDomain_CAMCC_CAMCCCSI4PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI5PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI6PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI7PHYTIMER
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER[] =
{
  {  400000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
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
  {  480000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  600000000, RAIL_VOLTAGE_LEVEL_SVS,        },
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
  {  300000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  400000000, RAIL_VOLTAGE_LEVEL_NOM,        },
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
 * ClockDomainFMax_CAMCC_CAMCCIFE0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFE0
 *   ClockDomain_CAMCC_CAMCCIFE1
 *   ClockDomain_CAMCC_CAMCCIFE2
 *   ClockDomain_CAMCC_CAMCCSFE0
 *   ClockDomain_CAMCC_CAMCCSFE1
 *   ClockDomain_CAMCC_CAMCCSFE2
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCIFE0[] =
{
  {  466000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  594000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  675000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  785000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCIPENPS
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIPENPS
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCIPENPS[] =
{
  {  455000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  {  475000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  {  575000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  675000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  825000000, RAIL_VOLTAGE_LEVEL_NOM,        },
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
 *   ClockDomain_CAMCC_CAMCCMCLK5
 *   ClockDomain_CAMCC_CAMCCMCLK6
 *   ClockDomain_CAMCC_CAMCCMCLK7
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCMCLK0[] =
{
  {   68571429, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCPLLTESTSTAGE1015MUX
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCPLLTESTSTAGE1015MUX
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCPLLTESTSTAGE1015MUX[] =
{
  {  600000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  { 1200000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCQDSSDEBUG
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCQDSSDEBUG
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCQDSSDEBUG[] =
{
  {   75000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  150000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  300000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
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
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {   37500000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {   75000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSBYTE0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSBYTE0
 *   ClockDomain_DISPCC_DISPCCMDSSBYTE1
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSBYTE0[] =
{
  {  140630000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
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
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3AUX
 *   ClockDomain_DISPCC_DISPCCMDSSESC0
 *   ClockDomain_DISPCC_DISPCCMDSSESC1
 *   ClockDomain_DISPCC_DISPCCMDSSVSYNC
 *   ClockDomain_DISPCC_DISPCCXO
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0LINK
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0LINK[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
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
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3PIXEL0
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  337500000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  405000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  675000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSDPTX3LINK
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSDPTX3LINK[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  270000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  594000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  810000000, RAIL_VOLTAGE_LEVEL_NOM,        },
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
  {  150000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  200000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  325000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  402000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  514000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSPCLK0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSPCLK0
 *   ClockDomain_DISPCC_DISPCCMDSSPCLK1
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSPCLK0[] =
{
  {  225000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
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
  {  500000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
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
  {      32000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCCPUSSUBWCP
 *
 * Used by:
 *   ClockDomain_GCC_GCCCPUSSUBWCP
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCCPUSSUBWCP[] =
{
  {  300000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  403000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  533000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  710666667, RAIL_VOLTAGE_LEVEL_TUR,        },
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
 *   ClockDomain_GCC_GCCQUPV3I2CS0
 *   ClockDomain_GCC_GCCQUPV3I2CS1
 *   ClockDomain_GCC_GCCQUPV3I2CS2
 *   ClockDomain_GCC_GCCQUPV3I2CS3
 *   ClockDomain_GCC_GCCQUPV3I2CS4
 *   ClockDomain_GCC_GCCQUPV3I2CS5
 *   ClockDomain_GCC_GCCQUPV3I2CS6
 *   ClockDomain_GCC_GCCQUPV3I2CS7
 *   ClockDomain_GCC_GCCQUPV3I2CS8
 *   ClockDomain_GCC_GCCQUPV3I2CS9
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
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCPCIE0PIPE[] =
{
  {  125000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  250000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCPCIE1PHYAUX
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE1PHYAUX
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCPCIE1PHYAUX[] =
{
  {   20000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCPCIE1PIPE
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE1PIPE
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCPCIE1PIPE[] =
{
  {  250000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  500000000, RAIL_VOLTAGE_LEVEL_NOM,        },
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
 * ClockDomainFMax_GCC_GCCQUPV3WRAP1QSPIREF
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP1QSPIREF
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCQUPV3WRAP1QSPIREF[] =
{
  {  150000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  240000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCQUPV3WRAP1S0
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP1S0
 *   ClockDomain_GCC_GCCQUPV3WRAP1S1
 *   ClockDomain_GCC_GCCQUPV3WRAP1S4
 *   ClockDomain_GCC_GCCQUPV3WRAP1S6
 *   ClockDomain_GCC_GCCQUPV3WRAP2S0
 *   ClockDomain_GCC_GCCQUPV3WRAP2S1
 *   ClockDomain_GCC_GCCQUPV3WRAP2S2
 *   ClockDomain_GCC_GCCQUPV3WRAP2S3
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCQUPV3WRAP1S0[] =
{
  {   75000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  120000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCQUPV3WRAP1S3
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP1S3
 *   ClockDomain_GCC_GCCQUPV3WRAP1S5
 *   ClockDomain_GCC_GCCQUPV3WRAP1S7
 *   ClockDomain_GCC_GCCQUPV3WRAP2S4
 *   ClockDomain_GCC_GCCQUPV3WRAP2S5
 *   ClockDomain_GCC_GCCQUPV3WRAP2S7
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCQUPV3WRAP1S3[] =
{
  {   75000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  100000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCQUPV3WRAP2IBICTRL0
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP2IBICTRL0
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCQUPV3WRAP2IBICTRL0[] =
{
  {   37500000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCQUPV3WRAP2S6
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP2S6
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCQUPV3WRAP2S6[] =
{
  {   75000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  128000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCQUPV3WRAP3QSPIREF
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP3QSPIREF
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCQUPV3WRAP3QSPIREF[] =
{
  {  300000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  400000000, RAIL_VOLTAGE_LEVEL_SVS,        },
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
 * ClockDomainFMax_GCC_GCCSDCC4APPS
 *
 * Used by:
 *   ClockDomain_GCC_GCCSDCC4APPS
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCSDCC4APPS[] =
{
  {   75000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCUFSPHYAXI
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYAXI
 *   ClockDomain_GCC_GCCUFSPHYICECORE
 *   ClockDomain_GCC_GCCUFSPHYUNIPROCORE
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCUFSPHYAXI[] =
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
  {  312500000, RAIL_VOLTAGE_LEVEL_NOM,        },
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
  {  231000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D2, },
  {  310000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  366000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D0, },
  {  422000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  500000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_L1, },
  {  578000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  629000000, RAIL_VOLTAGE_LEVEL_SVS_L0,     },
  {  680000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  720000000, RAIL_VOLTAGE_LEVEL_SVS_L2,     },
  {  770000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  834000000, RAIL_VOLTAGE_LEVEL_NOM_L1,     },
  {  869000000, RAIL_VOLTAGE_LEVEL_TUR,        {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  {  903000000, RAIL_VOLTAGE_LEVEL_TUR,        {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  {  903000000, RAIL_VOLTAGE_LEVEL_TUR_L1,     {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  { 1000000000, RAIL_VOLTAGE_LEVEL_TUR_L1,     {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  { 1100000000, RAIL_VOLTAGE_LEVEL_TUR_L2,     {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
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
  {  200000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D2, },
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
  {  260000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D2, },
  {  625000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_GPUCC_GPUCCGXGFX3D
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCGXGFX3D
 */
static const ClockFMaxType ClockDomainFMax_GPUCC_GPUCCGXGFX3D[] =
{
  {  231000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D2, },
  {  310000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  366000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D0, },
  {  422000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  500000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_L1, },
  {  578000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  629000000, RAIL_VOLTAGE_LEVEL_SVS_L0,     },
  {  680000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  720000000, RAIL_VOLTAGE_LEVEL_SVS_L2,     },
  {  770000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  834000000, RAIL_VOLTAGE_LEVEL_NOM_L1,     },
  {  869000000, RAIL_VOLTAGE_LEVEL_TUR,        {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  {  903000000, RAIL_VOLTAGE_LEVEL_TUR,        {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  {  903000000, RAIL_VOLTAGE_LEVEL_TUR_L1,     {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  { 1000000000, RAIL_VOLTAGE_LEVEL_TUR_L1,     {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  { 1100000000, RAIL_VOLTAGE_LEVEL_TUR_L2,     {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
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
  {  200000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D2, },
  {  300000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  312500000, RAIL_VOLTAGE_LEVEL_SVS_L0,     },
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
  {  500000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D2, },
  { 1000000000, RAIL_VOLTAGE_LEVEL_SVS,        },
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
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
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
  {  588000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  840000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  {  900000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  { 1140000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  { 1305000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  { 1440000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  { 1600000000, RAIL_VOLTAGE_LEVEL_TUR,        },
  {  0  }
};

/*
 * ClockDomainFMax_VIDEOCC_VIDEOCCMVS1
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCMVS1
 */
static const ClockFMaxType ClockDomainFMax_VIDEOCC_VIDEOCCMVS1[] =
{
  {  840000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  { 1050000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0x01, 0x00}, {0x02, 0x00}, CHIPINFO_FAMILY_LANAI}},
  { 1110000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0x02, 0x00}, {0xFF, 0xFF}, CHIPINFO_FAMILY_LANAI}},
  { 1350000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  { 1500000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  { 1650000000, RAIL_VOLTAGE_LEVEL_NOM,        },
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
  {  800000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
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
  {      32000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
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
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCBPS,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_BPS_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCAMNOCAXIRT =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCAMNOCAXIRT,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCAMNOCAXIRT),
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCAMNOCAXIRT,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
  .CESTA     = { CESTA_IDX_CAM, 8 },
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CAMNOC_AXI_RT_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCCI0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCCI0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCCI0),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCCI0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
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
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCCI0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CCI_1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCCI2 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCCI0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCCI0),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCCI0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CCI_2_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCPHYRX =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCPHYRX,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCPHYRX),
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCPHYRX,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
  .CESTA     = { CESTA_IDX_CAM, 7 },
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CPHY_RX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCRE =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCRE,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCRE),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCRE,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
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
  .nRailMask = RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
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
  .nRailMask = RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
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
  .nRailMask = RAIL_VDD_MX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
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
  .nRailMask = RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CSI3PHYTIMER_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCSI4PHYTIMER =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER),
  .nRailMask = RAIL_VDD_MX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CSI4PHYTIMER_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCSI5PHYTIMER =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER),
  .nRailMask = RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CSI5PHYTIMER_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCSI6PHYTIMER =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER),
  .nRailMask = RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CSI6PHYTIMER_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCSI7PHYTIMER =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER),
  .nRailMask = RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CSI7PHYTIMER_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCSID =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCSID,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCSID),
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCPHYRX,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
  .CESTA     = { CESTA_IDX_CAM, 6 },
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CSID_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCDEBUGMUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_MM,
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
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCFASTAHB,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
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
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCICP,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_ICP_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCIFE0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCIFE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCIFE0),
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCIFE0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCIFE0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
  .CESTA     = { CESTA_IDX_CAM, 0 },
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_IFE_0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCIFE1 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCIFE1,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCIFE1),
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCIFE0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCIFE1,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
  .CESTA     = { CESTA_IDX_CAM, 1 },
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_IFE_1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCIFE2 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCIFE2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCIFE2),
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCIFE0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCIFE2,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
  .CESTA     = { CESTA_IDX_CAM, 2 },
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_IFE_2_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCIFELITE =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCSID,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCSID),
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCPHYRX,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_IFE_LITE_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCIFELITECSID =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCSID,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCSID),
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCPHYRX,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_IFE_LITE_CSID_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCIPENPS =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCIPENPS,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCIPENPS),
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCIPENPS,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCIPENPS,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_IPE_NPS_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCJPEG =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCJPEG,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCJPEG),
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCRE,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_JPEG_CMD_RCGR),
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

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCMCLK5 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCMCLK0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCMCLK0),
  .nRailMask = RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCMCLK0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCMCLK0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_MCLK5_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCMCLK6 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCMCLK0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCMCLK0),
  .nRailMask = RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCMCLK0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCMCLK0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_MCLK6_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCMCLK7 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCMCLK0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCMCLK0),
  .nRailMask = RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCMCLK0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCMCLK0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_MCLK7_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCPLLTESTSTAGE1015MUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCPLLTESTSTAGE1015MUX,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCPLLTESTSTAGE1015MUX,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = 0,
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCQDSSDEBUG =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCQDSSDEBUG,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCQDSSDEBUG),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCQDSSDEBUG,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_QDSS_DEBUG_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCSFE0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCSFE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCSFE0),
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCIFE0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCSFE0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
  .CESTA     = { CESTA_IDX_CAM, 3 },
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_SFE_0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCSFE1 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCSFE1,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCSFE1),
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCIFE0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCSFE1,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
  .CESTA     = { CESTA_IDX_CAM, 4 },
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_SFE_1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCSFE2 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCSFE2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCSFE2),
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCIFE0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCSFE2,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
  .CESTA     = { CESTA_IDX_CAM, 5 },
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_SFE_2_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCSLEEP =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCSLEEP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCSLEEP),
  .nRailMask = RAIL_VDD_MM,
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
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCSLOWAHB,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCCAMNOCAXIRT,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_SLOW_AHB_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCXO =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_MM,
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
  .nRailMask = RAIL_VDD_MM,
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
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSBYTE0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSBYTE0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_BYTE0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSBYTE1 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSBYTE0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSBYTE0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_BYTE1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_MM,
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
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MM,
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
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MM,
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
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX0_PIXEL1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX1AUX =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0AUX,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX1_AUX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0LINK,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX1LINK,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX1_LINK_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL0 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX1PIXEL0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX1_PIXEL0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL1 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX1PIXEL0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX1_PIXEL1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX2AUX =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0AUX,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX2_AUX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0LINK,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX1LINK,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX2_LINK_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL0 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX1PIXEL0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX2_PIXEL0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL1 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX1PIXEL0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX2_PIXEL1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX3AUX =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0AUX,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX3_AUX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX3LINK,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX1LINK,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX3_LINK_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX3PIXEL0 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX1PIXEL0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX3_PIXEL0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSESC0 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSESC0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_ESC0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSESC1 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSESC0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_ESC1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSMDP =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSMDP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSMDP),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MM | RAIL_VDD_MX,
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
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSPCLK0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSBYTE0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_PCLK0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSPCLK1 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MM,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSPCLK0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSBYTE0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_PCLK1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSVSYNC =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_MM,
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
  .nRailMask = RAIL_VDD_MM,
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
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCSLEEP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCSLEEP),
  .nRailMask = RAIL_VDD_MM,
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
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
  .nRailMask = RAIL_VDD_MM,
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

static ClockDomainNodeType ClockDomain_GCC_GCCAGGRENOCNORTHSF =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_AGGRE_NOC_NORTH_SF_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCCNOCNORTHQX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_CNOC_NORTH_QX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCCNOCPERIPH =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aSourceMap = ClockSourceMap_GCC_GCCPCIE0PHYRCHNG,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_CNOC_PERIPH_CMD_RCGR),
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

static ClockDomainNodeType ClockDomain_GCC_GCCCPUSSUBWCP =
{
  .aBSP      = ClockDomainBSP_GCC_GCCCPUSSUBWCP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCCPUSSUBWCP),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCCPUSSUBWCP,
  .aSourceMap = ClockSourceMap_GCC_GCCCPUSSUBWCP,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_CPUSS_UBWCP_CMD_RCGR),
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
  .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
  .CESTA     = { CESTA_IDX_PCIE, 0 },
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

static ClockDomainNodeType ClockDomain_GCC_GCCPCIE1PHYAUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE1PHYAUX,
  .aSourceMap = ClockSourceMap_GCC_GCCPCIE1PHYAUX,
  .pSource   = NULL,
  .nFlags    = CLOCK_FLAG_DOMAIN_FORCE_SETTINGS,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_PCIE_1_PHY_AUX_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
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
  .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
  .CESTA     = { CESTA_IDX_PCIE, 1 },
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
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE1PIPE,
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
  .aSourceMap = ClockSourceMap_GCC_GCCPCIE0PHYRCHNG,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_PDM2_CMD_RCGR),
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

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3I2CCORE =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_I2C_CORE_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3I2CS0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3I2CS0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_I2C_S0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3I2CS1 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3I2CS0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_I2C_S1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3I2CS2 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3I2CS0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_I2C_S2_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3I2CS3 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3I2CS0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_I2C_S3_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3I2CS4 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3I2CS0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_I2C_S4_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3I2CS5 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3I2CS0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_I2C_S5_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3I2CS6 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3I2CS0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_I2C_S6_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3I2CS7 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3I2CS0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_I2C_S7_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3I2CS8 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3I2CS0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_I2C_S8_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3I2CS9 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3I2CS0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_I2C_S9_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
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
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP1QSPIREF,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP1QSPIREF),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP1QSPIREF,
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
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP1S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP1S0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP1S0,
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
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP1S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP1S0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP1S0,
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
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP1S3,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP1S3),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP1S3,
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
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP1S4,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP1S4),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP1S0,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP1QSPIREF,
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
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP1S3,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP1S3),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP1S3,
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
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP1S4,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP1S4),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP1S0,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP1QSPIREF,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_S6_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S7 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP1S3,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP1S3),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP1S3,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP1QSPIREF,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_S7_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP2CORE2X =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP2_CORE_2X_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP2IBICTRL0 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP2IBICTRL0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP2IBICTRL0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP2IBICTRL0,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP2IBICTRL0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP2_IBI_CTRL_0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP2S0 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP1S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP1S0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP1S0,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP2S0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP2_S0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP2S1 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP1S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP1S0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP1S0,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP2S0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP2_S1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP2S2 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP1S4,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP1S4),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP1S0,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP2S0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP2_S2_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP2S3 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP1S4,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP1S4),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP1S0,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP2S0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP2_S3_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP2S4 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP1S3,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP1S3),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP1S3,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP2S0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP2_S4_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP2S5 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP1S3,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP1S3),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP1S3,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP2S0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP2_S5_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP2S6 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP2S6,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP2S6),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP2S6,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP2S6,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP2_S6_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP2S7 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP1S3,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP1S3),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP1S3,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP2S0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP2_S7_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP3CORE2X =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP3_CORE_2X_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP3QSPIREF =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP3QSPIREF,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP3QSPIREF),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP3QSPIREF,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP3QSPIREF,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP3_QSPI_REF_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
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

static ClockDomainNodeType ClockDomain_GCC_GCCSDCC4APPS =
{
  .aBSP      = ClockDomainBSP_GCC_GCCSDCC4APPS,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCSDCC4APPS),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MX,
  .aFMax     = ClockDomainFMax_GCC_GCCSDCC4APPS,
  .aSourceMap = ClockSourceMap_GCC_GCCPCIE0PHYRCHNG,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_SDCC4_APPS_CMD_RCGR),
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
  .aFMax     = ClockDomainFMax_GCC_GCCUFSPHYAXI,
  .aSourceMap = ClockSourceMap_GCC_GCCUFSPHYAXI,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_UFS_PHY_ICE_CORE_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYPHYAUX =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUFSPHYPHYAUX,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUFSPHYPHYAUX),
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
  .aBSP      = ClockDomainBSP_GCC_GCCUFSPHYICECORE,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUFSPHYICECORE),
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
  .aSourceMap = ClockSourceMap_GCC_GCCUSB30PRIMMASTER,
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

static ClockDomainNodeType ClockDomain_GCC_GCCVSENSOR =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_VSENSOR_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
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

static ClockDomainNodeType ClockDomain_GPUCC_GPUCCGXGFX3D =
{
  .aBSP      = ClockDomainBSP_GPUCC_GPUCCGXGFX3D,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GPUCC_GPUCCGXGFX3D),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_GX | RAIL_VDD_MX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_GPUCC_GPUCCGXGFX3D,
  .aSourceMap = ClockSourceMap_GPUCC_GPUCCGXGFX3D,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPUCC_GPU_CC_GX_GFX3D_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GPUCC_GPUCCHUB =
{
  .aBSP      = ClockDomainBSP_GPUCC_GPUCCHUB,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GPUCC_GPUCCHUB),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GPUCC_GPUCCHUB,
  .aSourceMap = ClockSourceMap_GPUCC_GPUCCHUB,
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
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPUCC_GPU_CC_XO_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_VIDEOCC_VIDEOCCAHB =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
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
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_VIDEOCC_VIDEOCCMVS0,
  .aSourceMap = ClockSourceMap_VIDEOCC_VIDEOCCMVS0,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(VCODEC_VIDEO_CC_MVS0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_VIDEOCC_VIDEOCCMVS1 =
{
  .aBSP      = ClockDomainBSP_VIDEOCC_VIDEOCCMVS1,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_VIDEOCC_VIDEOCCMVS1),
  .nRailMask = RAIL_VDD_MM | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_VIDEOCC_VIDEOCCMVS1,
  .aSourceMap = ClockSourceMap_VIDEOCC_VIDEOCCMVS1,
  .pSource   = &ClockSource_XO,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(VCODEC_VIDEO_CC_MVS1_CMD_RCGR),
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
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCSLEEP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCSLEEP),
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
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSBYTE0),
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
  &ClockDomain_CAMCC_CAMCCCAMNOCAXIRT,
  &ClockDomain_CAMCC_CAMCCCCI0,
  &ClockDomain_CAMCC_CAMCCCCI1,
  &ClockDomain_CAMCC_CAMCCCCI2,
  &ClockDomain_CAMCC_CAMCCCPHYRX,
  &ClockDomain_CAMCC_CAMCCCRE,
  &ClockDomain_CAMCC_CAMCCCSI0PHYTIMER,
  &ClockDomain_CAMCC_CAMCCCSI1PHYTIMER,
  &ClockDomain_CAMCC_CAMCCCSI2PHYTIMER,
  &ClockDomain_CAMCC_CAMCCCSI3PHYTIMER,
  &ClockDomain_CAMCC_CAMCCCSI4PHYTIMER,
  &ClockDomain_CAMCC_CAMCCCSI5PHYTIMER,
  &ClockDomain_CAMCC_CAMCCCSI6PHYTIMER,
  &ClockDomain_CAMCC_CAMCCCSI7PHYTIMER,
  &ClockDomain_CAMCC_CAMCCCSID,
  &ClockDomain_CAMCC_CAMCCDEBUGMUX,
  &ClockDomain_CAMCC_CAMCCFASTAHB,
  &ClockDomain_CAMCC_CAMCCICP,
  &ClockDomain_CAMCC_CAMCCIFE0,
  &ClockDomain_CAMCC_CAMCCIFE1,
  &ClockDomain_CAMCC_CAMCCIFE2,
  &ClockDomain_CAMCC_CAMCCIFELITE,
  &ClockDomain_CAMCC_CAMCCIFELITECSID,
  &ClockDomain_CAMCC_CAMCCIPENPS,
  &ClockDomain_CAMCC_CAMCCJPEG,
  &ClockDomain_CAMCC_CAMCCMCLK0,
  &ClockDomain_CAMCC_CAMCCMCLK1,
  &ClockDomain_CAMCC_CAMCCMCLK2,
  &ClockDomain_CAMCC_CAMCCMCLK3,
  &ClockDomain_CAMCC_CAMCCMCLK4,
  &ClockDomain_CAMCC_CAMCCMCLK5,
  &ClockDomain_CAMCC_CAMCCMCLK6,
  &ClockDomain_CAMCC_CAMCCMCLK7,
  &ClockDomain_CAMCC_CAMCCPLLTESTSTAGE1015MUX,
  &ClockDomain_CAMCC_CAMCCQDSSDEBUG,
  &ClockDomain_CAMCC_CAMCCSFE0,
  &ClockDomain_CAMCC_CAMCCSFE1,
  &ClockDomain_CAMCC_CAMCCSFE2,
  &ClockDomain_CAMCC_CAMCCSLEEP,
  &ClockDomain_CAMCC_CAMCCSLOWAHB,
  &ClockDomain_CAMCC_CAMCCXO,
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
  &ClockDomain_DISPCC_DISPCCPLLTESTMUX,
  &ClockDomain_DISPCC_DISPCCSLEEP,
  &ClockDomain_DISPCC_DISPCCXO,
  &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
  &ClockDomain_GCC_CLOCKDRIVERGENXO,
  &ClockDomain_GCC_GCCAGGRENOC,
  &ClockDomain_GCC_GCCAGGRENOCNORTHSF,
  &ClockDomain_GCC_GCCCNOCNORTHQX,
  &ClockDomain_GCC_GCCCNOCPERIPH,
  &ClockDomain_GCC_GCCCONFIGNOC,
  &ClockDomain_GCC_GCCCPUSSUBWCP,
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
  &ClockDomain_GCC_GCCPCIE1PHYAUX,
  &ClockDomain_GCC_GCCPCIE1PHYRCHNG,
  &ClockDomain_GCC_GCCPCIE1PIPE,
  &ClockDomain_GCC_GCCPDM2,
  &ClockDomain_GCC_GCCQDSSATBA,
  &ClockDomain_GCC_GCCQDSSATBB,
  &ClockDomain_GCC_GCCQDSSTRIG,
  &ClockDomain_GCC_GCCQUPV3I2CCORE,
  &ClockDomain_GCC_GCCQUPV3I2CS0,
  &ClockDomain_GCC_GCCQUPV3I2CS1,
  &ClockDomain_GCC_GCCQUPV3I2CS2,
  &ClockDomain_GCC_GCCQUPV3I2CS3,
  &ClockDomain_GCC_GCCQUPV3I2CS4,
  &ClockDomain_GCC_GCCQUPV3I2CS5,
  &ClockDomain_GCC_GCCQUPV3I2CS6,
  &ClockDomain_GCC_GCCQUPV3I2CS7,
  &ClockDomain_GCC_GCCQUPV3I2CS8,
  &ClockDomain_GCC_GCCQUPV3I2CS9,
  &ClockDomain_GCC_GCCQUPV3WRAP1CORE2X,
  &ClockDomain_GCC_GCCQUPV3WRAP1QSPIREF,
  &ClockDomain_GCC_GCCQUPV3WRAP1S0,
  &ClockDomain_GCC_GCCQUPV3WRAP1S1,
  &ClockDomain_GCC_GCCQUPV3WRAP1S3,
  &ClockDomain_GCC_GCCQUPV3WRAP1S4,
  &ClockDomain_GCC_GCCQUPV3WRAP1S5,
  &ClockDomain_GCC_GCCQUPV3WRAP1S6,
  &ClockDomain_GCC_GCCQUPV3WRAP1S7,
  &ClockDomain_GCC_GCCQUPV3WRAP2CORE2X,
  &ClockDomain_GCC_GCCQUPV3WRAP2IBICTRL0,
  &ClockDomain_GCC_GCCQUPV3WRAP2S0,
  &ClockDomain_GCC_GCCQUPV3WRAP2S1,
  &ClockDomain_GCC_GCCQUPV3WRAP2S2,
  &ClockDomain_GCC_GCCQUPV3WRAP2S3,
  &ClockDomain_GCC_GCCQUPV3WRAP2S4,
  &ClockDomain_GCC_GCCQUPV3WRAP2S5,
  &ClockDomain_GCC_GCCQUPV3WRAP2S6,
  &ClockDomain_GCC_GCCQUPV3WRAP2S7,
  &ClockDomain_GCC_GCCQUPV3WRAP3CORE2X,
  &ClockDomain_GCC_GCCQUPV3WRAP3QSPIREF,
  &ClockDomain_GCC_GCCSDCC2APPS,
  &ClockDomain_GCC_GCCSDCC4APPS,
  &ClockDomain_GCC_GCCSLEEP,
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
  &ClockDomain_GCC_GCCVSENSOR,
  &ClockDomain_GCC_GCCXO,
  &ClockDomain_GPUCC_GPUCCDEBUGMUX,
  &ClockDomain_GPUCC_GPUCCFF,
  &ClockDomain_GPUCC_GPUCCGMU,
  &ClockDomain_GPUCC_GPUCCGXGFX3D,
  &ClockDomain_GPUCC_GPUCCHUB,
  &ClockDomain_GPUCC_GPUCCPLLTESTMUX,
  &ClockDomain_GPUCC_GPUCCXO,
  &ClockDomain_VIDEOCC_VIDEOCCAHB,
  &ClockDomain_VIDEOCC_VIDEOCCMVS0,
  &ClockDomain_VIDEOCC_VIDEOCCMVS1,
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
      .nDebugMuxSel = 24,
    },
  },
  {
    .szName    = "cam_cc_cpas_bps_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCBPS,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xAC8F0D50,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CPAS_BPS_CBCR), HWIO_PHYS(CAM_CC_BPS_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 25,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCAMNOCAXIRT                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_camnoc_axi_nrt_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCAMNOCAXIRT,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x033A45DF,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CAMNOC_AXI_NRT_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 134,
    },
  },
  {
    .szName    = "cam_cc_camnoc_axi_rt_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCAMNOCAXIRT,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x7DCEA721,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CAMNOC_AXI_RT_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 73,
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
      .mRegisters   = { HWIO_PHYS(CAM_CC_CCI_0_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 68,
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
      .mRegisters   = { HWIO_PHYS(CAM_CC_CCI_1_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 69,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCCI2                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_cci_2_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCCI2,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x68C6ABCF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CCI_2_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 97,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCPHYRX                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_csid_csiphy_rx_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x2FBDAC2F,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSID_CSIPHY_RX_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 11,
    },
  },
  {
    .szName    = "cam_cc_csiphy0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x5BD9C966,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSIPHY0_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 10,
    },
  },
  {
    .szName    = "cam_cc_csiphy1_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD1C62B7E,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSIPHY1_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 13,
    },
  },
  {
    .szName    = "cam_cc_csiphy2_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xFB341D3F,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSIPHY2_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 15,
    },
  },
  {
    .szName    = "cam_cc_csiphy3_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x29439ED4,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSIPHY3_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 17,
    },
  },
  {
    .szName    = "cam_cc_csiphy4_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xDB01488B,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSIPHY4_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 19,
    },
  },
  {
    .szName    = "cam_cc_csiphy5_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x482323FC,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSIPHY5_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 21,
    },
  },
  {
    .szName    = "cam_cc_csiphy6_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x68B650D6,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSIPHY6_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 89,
    },
  },
  {
    .szName    = "cam_cc_csiphy7_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x7D668D35,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSIPHY7_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 91,
    },
  },
  {
    .szName    = "cam_cc_ife_lite_cphy_rx_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x51577E4F,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_LITE_CPHY_RX_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 54,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCRE                                            */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_cpas_cre_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCRE,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x2B316EB1,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CPAS_CRE_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 93,
    },
  },
  {
    .szName    = "cam_cc_cre_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCRE,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x4B3A4DAF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CRE_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 92,
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
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSI0PHYTIMER_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 9,
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
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSI1PHYTIMER_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 12,
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
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSI2PHYTIMER_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 14,
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
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSI3PHYTIMER_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 16,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCSI4PHYTIMER                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_csi4phytimer_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCSI4PHYTIMER,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xB18687E2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSI4PHYTIMER_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 18,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCSI5PHYTIMER                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_csi5phytimer_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCSI5PHYTIMER,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xB51B47B8,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSI5PHYTIMER_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 20,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCSI6PHYTIMER                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_csi6phytimer_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCSI6PHYTIMER,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xBF415A52,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSI6PHYTIMER_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 88,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCSI7PHYTIMER                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_csi7phytimer_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCSI7PHYTIMER,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xF073D7E4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSI7PHYTIMER_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 90,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCSID                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_csid_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCSID,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x81ECCAD5,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSID_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 72,
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
    .szName    = "cam_cc_bps_fast_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x4343B49C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_BPS_FAST_AHB_CBCR), HWIO_PHYS(CAM_CC_BPS_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 22,
    },
  },
  {
    .szName    = "cam_cc_cpas_fast_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xC8B7CE22,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CPAS_FAST_AHB_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 71,
    },
  },
  {
    .szName    = "cam_cc_ife_0_fast_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x5422ADFD,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_0_FAST_AHB_CBCR), HWIO_PHYS(CAM_CC_IFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 40,
    },
  },
  {
    .szName    = "cam_cc_ife_1_fast_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x24DD2629,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_1_FAST_AHB_CBCR), HWIO_PHYS(CAM_CC_IFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 45,
    },
  },
  {
    .szName    = "cam_cc_ife_2_fast_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x593CF91C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_2_FAST_AHB_CBCR), HWIO_PHYS(CAM_CC_IFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 50,
    },
  },
  {
    .szName    = "cam_cc_ipe_nps_fast_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD108DD15,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IPE_NPS_FAST_AHB_CBCR), HWIO_PHYS(CAM_CC_IPE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 31,
    },
  },
  {
    .szName    = "cam_cc_ipe_pps_fast_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x45B7C8D8,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IPE_PPS_FAST_AHB_CBCR), HWIO_PHYS(CAM_CC_IPE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 32,
    },
  },
  {
    .szName    = "cam_cc_sbi_fast_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x1FBF0450,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SBI_FAST_AHB_CBCR), HWIO_PHYS(CAM_CC_SBI_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 35,
    },
  },
  {
    .szName    = "cam_cc_sfe_0_fast_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x176FFD91,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SFE_0_FAST_AHB_CBCR), HWIO_PHYS(CAM_CC_SFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 59,
    },
  },
  {
    .szName    = "cam_cc_sfe_1_fast_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x552A4B64,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SFE_1_FAST_AHB_CBCR), HWIO_PHYS(CAM_CC_SFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 63,
    },
  },
  {
    .szName    = "cam_cc_sfe_2_fast_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD74B3F55,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SFE_2_FAST_AHB_CBCR), HWIO_PHYS(CAM_CC_SFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 122,
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
      .nDebugMuxSel = 66,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCIFE0                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_cpas_ife_0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x690E94A4,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CPAS_IFE_0_CBCR), HWIO_PHYS(CAM_CC_IFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 37,
    },
  },
  {
    .szName    = "cam_cc_cpas_sbi_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x8F7EBF2C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CPAS_SBI_CBCR), HWIO_PHYS(CAM_CC_SBI_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 34,
    },
  },
  {
    .szName    = "cam_cc_ife_0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x93CC2ED3,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_0_CBCR), HWIO_PHYS(CAM_CC_IFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 36,
    },
  },
  {
    .szName    = "cam_cc_ife_0_spdm_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x4C5D526B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_0_SPDM_CBCR), HWIO_PHYS(CAM_CC_IFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 39,
    },
  },
  {
    .szName    = "cam_cc_sbi_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x8DB0BA19,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SBI_CBCR), HWIO_PHYS(CAM_CC_SBI_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 33,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCIFE1                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_cpas_ife_1_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE1,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x615F16E2,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CPAS_IFE_1_CBCR), HWIO_PHYS(CAM_CC_IFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 42,
    },
  },
  {
    .szName    = "cam_cc_ife_1_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE1,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x20EDB204,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_1_CBCR), HWIO_PHYS(CAM_CC_IFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 41,
    },
  },
  {
    .szName    = "cam_cc_ife_1_spdm_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE1,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x3E07A91F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_1_SPDM_CBCR), HWIO_PHYS(CAM_CC_IFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 44,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCIFE2                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_cpas_ife_2_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE2,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x8FF321B2,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CPAS_IFE_2_CBCR), HWIO_PHYS(CAM_CC_IFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 47,
    },
  },
  {
    .szName    = "cam_cc_ife_2_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE2,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x1A2BDA1C,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_2_CBCR), HWIO_PHYS(CAM_CC_IFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 46,
    },
  },
  {
    .szName    = "cam_cc_ife_2_spdm_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE2,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xEC85B875,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_2_SPDM_CBCR), HWIO_PHYS(CAM_CC_IFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 49,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCIFELITE                                        */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_cpas_ife_lite_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFELITE,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xAA3AA381,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CPAS_IFE_LITE_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 52,
    },
  },
  {
    .szName    = "cam_cc_ife_lite_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFELITE,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD0972606,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_LITE_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 51,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCIFELITECSID                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_ife_lite_csid_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFELITECSID,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xC6E06EE3,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_LITE_CSID_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 53,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCIPENPS                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_cpas_ipe_nps_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIPENPS,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xE538169E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CPAS_IPE_NPS_CBCR), HWIO_PHYS(CAM_CC_IPE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 27,
    },
  },
  {
    .szName    = "cam_cc_ipe_nps_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIPENPS,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xCF45C1D6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IPE_NPS_CBCR), HWIO_PHYS(CAM_CC_IPE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 26,
    },
  },
  {
    .szName    = "cam_cc_ipe_nps_spdm_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIPENPS,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x6C977EB2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IPE_NPS_SPDM_CBCR), HWIO_PHYS(CAM_CC_IPE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 29,
    },
  },
  {
    .szName    = "cam_cc_ipe_pps_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIPENPS,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xFC442BC4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IPE_PPS_CBCR), HWIO_PHYS(CAM_CC_IPE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 28,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCJPEG                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_jpeg_1_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCJPEG,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xDEA82AA4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_JPEG_1_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 95,
    },
  },
  {
    .szName    = "cam_cc_jpeg_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCJPEG,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x9F6924DC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_JPEG_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 64,
    },
  },
  {
    .szName    = "cam_cc_jpeg_spdm_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCJPEG,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x0CBA0835,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_JPEG_SPDM_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 65,
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
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK0_CBCR), 0, {0, 0} },
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
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK1_CBCR), 0, {0, 0} },
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
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK2_CBCR), 0, {0, 0} },
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
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK3_CBCR), 0, {0, 0} },
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
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK4_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 5,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCMCLK5                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_mclk5_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCMCLK5,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD8521D1F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK5_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 6,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCMCLK6                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_mclk6_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCMCLK6,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x405311E7,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK6_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 7,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCMCLK7                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_mclk7_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCMCLK7,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x19DCEE64,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK7_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 8,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCPLLTESTSTAGE1015MUX                            */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_pll_test_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCPLLTESTSTAGE1015MUX,
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
  /* ClockDomain_CAMCC_CAMCCQDSSDEBUG                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_qdss_debug_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCQDSSDEBUG,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x1843A6D1,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_QDSS_DEBUG_CBCR), HWIO_PHYS(CAM_CC_QDSS_DEBUG_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 75,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCSFE0                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_cpas_sfe_0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSFE0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD43D097D,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CPAS_SFE_0_CBCR), HWIO_PHYS(CAM_CC_SFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 57,
    },
  },
  {
    .szName    = "cam_cc_sfe_0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSFE0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x4AC81960,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SFE_0_CBCR), HWIO_PHYS(CAM_CC_SFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 56,
    },
  },
  {
    .szName    = "cam_cc_sfe_0_spdm_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSFE0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x17912262,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SFE_0_SPDM_CBCR), HWIO_PHYS(CAM_CC_SFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 58,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCSFE1                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_cpas_sfe_1_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSFE1,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x9F40BFC4,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CPAS_SFE_1_CBCR), HWIO_PHYS(CAM_CC_SFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 61,
    },
  },
  {
    .szName    = "cam_cc_sfe_1_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSFE1,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x3E73C3C6,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SFE_1_CBCR), HWIO_PHYS(CAM_CC_SFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 60,
    },
  },
  {
    .szName    = "cam_cc_sfe_1_spdm_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSFE1,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x4727C9C6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SFE_1_SPDM_CBCR), HWIO_PHYS(CAM_CC_SFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 62,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCSFE2                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_cpas_sfe_2_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSFE2,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x4D61740A,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CPAS_SFE_2_CBCR), HWIO_PHYS(CAM_CC_SFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 120,
    },
  },
  {
    .szName    = "cam_cc_sfe_2_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSFE2,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD58C804D,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SFE_2_CBCR), HWIO_PHYS(CAM_CC_SFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 118,
    },
  },
  {
    .szName    = "cam_cc_sfe_2_spdm_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSFE2,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xFE1FF03C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SFE_2_SPDM_CBCR), HWIO_PHYS(CAM_CC_SFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 121,
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
      .mRegisters   = { HWIO_PHYS(CAM_CC_SLEEP_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 79,
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
      .nDebugMuxSel = 23,
    },
  },
  {
    .szName    = "cam_cc_core_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xA974C223,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CORE_AHB_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 77,
    },
  },
  {
    .szName    = "cam_cc_cpas_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x7E6C7824,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CPAS_AHB_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 70,
    },
  },
  {
    .szName    = "cam_cc_cre_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x75FFE457,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CRE_AHB_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 94,
    },
  },
  {
    .szName    = "cam_cc_drv_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x3A323E85,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_DRV_AHB_CBCR), HWIO_PHYS(CAM_CC_DRV_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 117,
    },
  },
  {
    .szName    = "cam_cc_icp_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x32CA8C6A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_ICP_AHB_CBCR), HWIO_PHYS(CAM_CC_ICP_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 67,
    },
  },
  {
    .szName    = "cam_cc_ife_lite_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x27E3565D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_LITE_AHB_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 55,
    },
  },
  {
    .szName    = "cam_cc_ipe_nps_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x52744D44,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IPE_NPS_AHB_CBCR), HWIO_PHYS(CAM_CC_IPE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 30,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCXO                                             */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_bps_shift_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xA5E833F6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_BPS_SHIFT_CBCR), HWIO_PHYS(CAM_CC_BPS_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 123,
    },
  },
  {
    .szName    = "cam_cc_camnoc_dcd_xo_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD2B89C42,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CAMNOC_DCD_XO_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 74,
    },
  },
  {
    .szName    = "cam_cc_camnoc_xo_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x6D33216F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CAMNOC_XO_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 96,
    },
  },
  {
    .szName    = "cam_cc_drv_xo_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD5FFFDE7,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_DRV_XO_CBCR), HWIO_PHYS(CAM_CC_DRV_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 116,
    },
  },
  {
    .szName    = "cam_cc_gdsc_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xC9FEBE6E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_GDSC_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 78,
    },
  },
  {
    .szName    = "cam_cc_ife_0_shift_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xC17F80E0,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_0_SHIFT_CBCR), HWIO_PHYS(CAM_CC_IFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 127,
    },
  },
  {
    .szName    = "cam_cc_ife_1_shift_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xE5E6A095,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_1_SHIFT_CBCR), HWIO_PHYS(CAM_CC_IFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 128,
    },
  },
  {
    .szName    = "cam_cc_ife_2_shift_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xED01AC12,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_2_SHIFT_CBCR), HWIO_PHYS(CAM_CC_IFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 129,
    },
  },
  {
    .szName    = "cam_cc_ipe_shift_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xC43417EE,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IPE_SHIFT_CBCR), HWIO_PHYS(CAM_CC_IPE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 124,
    },
  },
  {
    .szName    = "cam_cc_qdss_debug_xo_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xFC7EF9CE,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_QDSS_DEBUG_XO_CBCR), HWIO_PHYS(CAM_CC_QDSS_DEBUG_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 76,
    },
  },
  {
    .szName    = "cam_cc_sbi_shift_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x91FC4622,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SBI_SHIFT_CBCR), HWIO_PHYS(CAM_CC_SBI_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 126,
    },
  },
  {
    .szName    = "cam_cc_sfe_0_shift_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xADB438A9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SFE_0_SHIFT_CBCR), HWIO_PHYS(CAM_CC_SFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 130,
    },
  },
  {
    .szName    = "cam_cc_sfe_1_shift_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x213102CB,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SFE_1_SHIFT_CBCR), HWIO_PHYS(CAM_CC_SFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 131,
    },
  },
  {
    .szName    = "cam_cc_sfe_2_shift_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x68662D21,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SFE_2_SHIFT_CBCR), HWIO_PHYS(CAM_CC_SFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 132,
    },
  },
  {
    .szName    = "cam_cc_titan_top_shift_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x2EB633AC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_TITAN_TOP_SHIFT_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 133,
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
      .nDebugMuxSel = 55,
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
      .nDebugMuxSel = 51,
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
      .nDebugMuxSel = 56,
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
      .nDebugMuxSel = 58,
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
      .nDebugMuxSel = 20,
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
      .nDebugMuxSel = 21,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSBYTE1                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_byte1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSBYTE1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x0DE1DE46,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_BYTE1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 22,
    },
  },
  {
    .szName    = "disp_cc_mdss_byte1_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSBYTE1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xFEEDA5FA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_BYTE1_INTF_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 23,
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
      .nDebugMuxSel = 32,
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
      .nDebugMuxSel = 29,
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
      .nDebugMuxSel = 26,
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
      .nDebugMuxSel = 28,
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
      .nDebugMuxSel = 27,
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
      .nDebugMuxSel = 66,
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
      .nDebugMuxSel = 30,
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
      .nDebugMuxSel = 67,
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
      .nDebugMuxSel = 31,
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
      .nDebugMuxSel = 68,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX1AUX                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx1_aux_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1AUX,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xA4C9FCBA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX1_AUX_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 39,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx1_crypto_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xDC4577D5,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX1_CRYPTO_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 38,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx1_link_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xA6B8960A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX1_LINK_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 35,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx1_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xE09D4224,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX1_LINK_INTF_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 37,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx1_usb_router_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xB01596F5,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX1_USB_ROUTER_LINK_INTF_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 36,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL0                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx1_pixel0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xECF3AF7D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX1_PIXEL0_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 33,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL1                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx1_pixel1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x715982F2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX1_PIXEL1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 34,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX2AUX                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx2_aux_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2AUX,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xEE4EC3B3,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX2_AUX_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 45,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx2_crypto_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xD3922A9C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX2_CRYPTO_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 44,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx2_link_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x98555F85,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX2_LINK_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 42,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx2_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xB5F9954A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX2_LINK_INTF_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 43,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL0                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx2_pixel0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x2A4E6380,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX2_PIXEL0_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 40,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL1                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx2_pixel1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xBABE80B9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX2_PIXEL1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 41,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX3AUX                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx3_aux_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX3AUX,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xB5F17EF7,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX3_AUX_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 49,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx3_crypto_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x9E1CCAE7,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX3_CRYPTO_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 50,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx3_link_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xCE228C2D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX3_LINK_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 47,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx3_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xCEC7F620,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX3_LINK_INTF_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 48,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX3PIXEL0                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx3_pixel0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX3PIXEL0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x153148BC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX3_PIXEL0_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 46,
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
      .nDebugMuxSel = 24,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSESC1                                     */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_esc1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSESC1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x27702EBC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_ESC1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 25,
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
      .nDebugMuxSel = 52,
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
      .nDebugMuxSel = 17,
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
      .nDebugMuxSel = 53,
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
      .nDebugMuxSel = 18,
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
      .nDebugMuxSel = 65,
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
      .nDebugMuxSel = 15,
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
      .nDebugMuxSel = 63,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSPCLK1                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_pclk1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSPCLK1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xEC01E1B5,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_PCLK1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 16,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_pclk1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSPCLK1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x3C6FD75A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_SPDM_PCLK1_CBCR), HWIO_PHYS(DISP_CC_MDSS_SPDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 64,
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
      .nDebugMuxSel = 57,
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
      .nDebugMuxSel = 54,
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
      .nDebugMuxSel = 19,
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
      .nDebugMuxSel = 71,
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
      .nDebugMuxSel = 70,
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
      .nDebugMuxSel = 69,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_CLOCKDRIVERGENXO                                      */
  /*-----------------------------------------------------------------------*/
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
      .nDebugMuxSel = 401,
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
      .nDebugMuxSel = 402,
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
      .nDebugMuxSel = 48,
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
      .nDebugMuxSel = 28,
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
      .nDebugMuxSel = 27,
    },
  },
  {
    .szName    = "gpu_cc_gx_qdss_tsctr_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x39A96FAC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_QDSS_TSCTR_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 17,
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
    .szName    = "gcc_pcie_phy_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x7D75D7C2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_PCIE_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_pcie_phy_cfg_ahb_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x5FB6DA8B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_PCIE_PHY_CFG_AHB_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_pcie_phy_com_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x20D7AA6B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_PCIE_PHY_COM_BCR), {0, 0} },
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
    .szName    = "gcc_usb3_dp_phy_sec_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x6969477E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_USB3_DP_PHY_SEC_BCR), {0, 0} },
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
    .szName    = "gcc_usb3_phy_sec_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xA8BC18B6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_USB3_PHY_SEC_BCR), {0, 0} },
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
    .szName    = "gcc_usb3phy_phy_sec_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x5ECE2A2C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_USB3PHY_PHY_SEC_BCR), {0, 0} },
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
      .nDebugMuxSel = 39,
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
      .nDebugMuxSel = 35,
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
    .szName    = "tcsr_pcie_0_clkref_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x46A80F38,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(TCSR_PCIE_0_CLKREF_EN__PCIE_ENABLE), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "tcsr_pcie_1_clkref_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x30DFDB6B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(TCSR_PCIE_1_CLKREF_EN__PCIE_ENABLE), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "tcsr_ufs_clkref_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xC269EEF4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(TCSR_UFS_CLKREF_EN__UFS_ENABLE), 0, {0, 0} },
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
    .szName    = "tcsr_usb2_clkref_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xA3B407A1,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(TCSR_USB2_CLKREF_EN__USB2_ENABLE), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "tcsr_usb3_clkref_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x3A592B58,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(TCSR_USB3_CLKREF_EN__USB3_ENABLE), 0, {0, 0} },
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
    .szName    = "gcc_qupv3_wrap_1_m_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x728861DF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP_1_M_AHB_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x100000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 174,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap_2_m_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xFBEA7E74,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP_2_M_AHB_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_2_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x4} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 187,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap_3_m_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x36F93CCB,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP_3_M_AHB_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_3_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x40000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 203,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCAGGRENOCNORTHSF                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_aggre_noc_pcie_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOCNORTHSF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x7F143CA9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_AGGRE_NOC_PCIE_AXI_CBCR), 0, {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x1000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 63,
    },
  },
  {
    .szName    = "gcc_cnoc_pcie_sf_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOCNORTHSF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xF1E3FEDD,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CNOC_PCIE_SF_AXI_CBCR), 0, {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x40} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 24,
    },
  },
  {
    .szName    = "gcc_ddrss_pcie_sf_qtb_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOCNORTHSF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x6872C48B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_DDRSS_PCIE_SF_QTB_CBCR), 0, {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x80000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 255,
    },
  },
  {
    .szName    = "gcc_pcie_0_mstr_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOCNORTHSF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x6ECCBB13,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_MSTR_AXI_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x2} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 330,
    },
  },
  {
    .szName    = "gcc_pcie_1_mstr_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOCNORTHSF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xD8A72CC2,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_1_MSTR_AXI_CBCR), HWIO_PHYS(GCC_PCIE_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x8000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 339,
    },
  },
  {
    .szName    = "gcc_pcie_1_slv_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOCNORTHSF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xAA65C59A,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_1_SLV_AXI_CBCR), HWIO_PHYS(GCC_PCIE_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x4000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 338,
    },
  },
  {
    .szName    = "gcc_pcie_1_slv_q2a_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOCNORTHSF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x5F52BA5E,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_1_SLV_Q2A_AXI_CBCR), HWIO_PHYS(GCC_PCIE_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x2000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 337,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCCNOCNORTHQX                                        */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pcie_0_slv_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCCNOCNORTHQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x9331B3EF,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_SLV_AXI_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x1} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 329,
    },
  },
  {
    .szName    = "gcc_pcie_0_slv_q2a_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCCNOCNORTHQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x5B161349,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_SLV_Q2A_AXI_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x20} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 328,
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
      .nDebugMuxSel = 209,
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
      .nDebugMuxSel = 157,
    },
  },
  {
    .szName    = "gcc_sdcc4_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCNOCPERIPH,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xB1EE1963,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_SDCC4_AHB_CBCR), HWIO_PHYS(GCC_SDCC4_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 160,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCCONFIGNOC                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_boot_rom_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x20C2EB7C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_BOOT_ROM_AHB_CBCR), 0, {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x400} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 226,
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
      .nDebugMuxSel = 98,
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
      .nDebugMuxSel = 44,
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
      .nDebugMuxSel = 107,
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
      .nDebugMuxSel = 394,
    },
  },
  {
    .szName    = "gcc_pcie_0_cfg_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xAB33D8F8,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_CFG_AHB_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x4} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 331,
    },
  },
  {
    .szName    = "gcc_pcie_1_cfg_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xB6E6F09E,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_1_CFG_AHB_CBCR), HWIO_PHYS(GCC_PCIE_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x10000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 340,
    },
  },
  {
    .szName    = "gcc_pcie_rscc_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x0252E490,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_RSCC_CFG_AHB_CBCR), HWIO_PHYS(GCC_PCIE_RSCC_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x100000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 429,
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
      .nDebugMuxSel = 99,
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
      .nDebugMuxSel = 100,
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
      .nDebugMuxSel = 108,
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
      .nDebugMuxSel = 395,
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
      .nDebugMuxSel = 327,
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
      .nDebugMuxSel = 116,
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
      .nDebugMuxSel = 113,
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
      .nDebugMuxSel = 115,
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
      .nDebugMuxSel = 114,
    },
  },
  {
    .szName    = "gcc_qupv3_i2c_s_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x3B084431,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_I2C_S_AHB_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_I2C_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x80} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 162,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap_1_s_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x3428967E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP_1_S_AHB_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x200000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 175,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap_2_ibi_2_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x20E6AA7C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP_2_IBI_2_AHB_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_2_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x2000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 199,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap_2_ibi_3_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xE9A86650,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP_2_IBI_3_AHB_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_2_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x4000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 200,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap_2_s_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x306EA255,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP_2_S_AHB_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_2_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x2} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 188,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap_3_s_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xF737BE69,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP_3_S_AHB_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_3_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x80000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 204,
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
      .nDebugMuxSel = 349,
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
      .nDebugMuxSel = 112,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCCPUSSUBWCP                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_cpuss_ubwcp_clk",
    .pDomain   = &ClockDomain_GCC_GCCCPUSSUBWCP,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x9B92D525,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CPUSS_UBWCP_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 306,
    },
  },
  {
    .szName    = "gcc_ddrss_ubwcp_clk",
    .pDomain   = &ClockDomain_GCC_GCCCPUSSUBWCP,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x5356AC6F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_DDRSS_UBWCP_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 263,
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
      .nDebugMuxSel = 324,
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
      .nDebugMuxSel = 325,
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
      .nDebugMuxSel = 326,
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
      .nDebugMuxSel = 254,
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
      .nDebugMuxSel = 398,
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
      .nDebugMuxSel = 400,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCMMNOCHFQX                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_camera_hf_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCMMNOCHFQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x62191536,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CAMERA_HF_AXI_CBCR), HWIO_PHYS(GCC_CAMERA_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 101,
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
      .nDebugMuxSel = 109,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCMMNOCSFQX                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_camera_sf_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCMMNOCSFQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x033685A3,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CAMERA_SF_AXI_CBCR), HWIO_PHYS(GCC_CAMERA_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 103,
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
      .nDebugMuxSel = 117,
    },
  },
  {
    .szName    = "gcc_video_axi1_clk",
    .pDomain   = &ClockDomain_GCC_GCCMMNOCSFQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x4F8C5CD6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_VIDEO_AXI1_CBCR), HWIO_PHYS(GCC_VIDEO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 118,
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
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_AUX_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x8} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 332,
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
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_PHY_RCHNG_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x400000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 334,
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
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_PIPE_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x10} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 333,
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
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_1_AUX_CBCR), HWIO_PHYS(GCC_PCIE_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x20000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 341,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCPCIE1PHYAUX                                        */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pcie_1_phy_aux_clk",
    .pDomain   = &ClockDomain_GCC_GCCPCIE1PHYAUX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xF23222AB,
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_1_PHY_AUX_CBCR), HWIO_PHYS(GCC_PCIE_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x1000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 342,
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
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_1_PHY_RCHNG_CBCR), HWIO_PHYS(GCC_PCIE_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x800000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 344,
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
    .nFlags    = CLOCK_FLAG_CESTA_CONTROLLED,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_1_PIPE_CBCR), HWIO_PHYS(GCC_PCIE_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x40000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 343,
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
      .nDebugMuxSel = 211,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQDSSATBA                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_sdcc2_at_clk",
    .pDomain   = &ClockDomain_GCC_GCCQDSSATBA,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x63F0B54C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_SDCC2_AT_CBCR), HWIO_PHYS(GCC_SDCC2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 158,
    },
  },
  {
    .szName    = "gcc_sdcc4_at_clk",
    .pDomain   = &ClockDomain_GCC_GCCQDSSATBA,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x228145F3,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_SDCC4_AT_CBCR), HWIO_PHYS(GCC_SDCC4_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 161,
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
      .nDebugMuxSel = 26,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQDSSTRIG                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_cx_qdss_trig_clk",
    .pDomain   = &ClockDomain_GCC_GCCQDSSTRIG,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x046DFEBA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_QDSS_TRIG_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 30,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3I2CCORE                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_i2c_core_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3I2CCORE,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x3E8231C8,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_I2C_CORE_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_I2C_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x100} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 163,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3I2CS0                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_i2c_s0_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3I2CS0,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x2897A430,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_I2C_S0_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_I2C_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x400} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 164,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3I2CS1                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_i2c_s1_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3I2CS1,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x0D97F42A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_I2C_S1_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_I2C_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x800} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 165,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3I2CS2                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_i2c_s2_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3I2CS2,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x861954F9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_I2C_S2_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_I2C_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x1000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 166,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3I2CS3                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_i2c_s3_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3I2CS3,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x3D0024FA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_I2C_S3_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_I2C_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x2000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 167,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3I2CS4                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_i2c_s4_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3I2CS4,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xF13B341C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_I2C_S4_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_I2C_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x4000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 168,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3I2CS5                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_i2c_s5_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3I2CS5,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x693008C9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_I2C_S5_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_I2C_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x8000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 169,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3I2CS6                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_i2c_s6_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3I2CS6,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xE9029DB8,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_I2C_S6_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_I2C_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x10000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 170,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3I2CS7                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_i2c_s7_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3I2CS7,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xA5205A17,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_I2C_S7_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_I2C_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x20000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 171,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3I2CS8                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_i2c_s8_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3I2CS8,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xA75C6ECF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_I2C_S8_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_I2C_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x4000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 172,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3I2CS9                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_i2c_s9_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3I2CS9,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x4CE705D0,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_I2C_S9_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_I2C_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x8000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 173,
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
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_CORE_2X_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x40000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 177,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap1_core_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1CORE2X,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x40B685B0,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_CORE_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x80000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 176,
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
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_QSPI_REF_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x20000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 186,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap1_s2_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1QSPIREF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x45AB34F6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S2_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x1000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 180,
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
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S0_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x400000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 178,
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
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S1_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x800000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 179,
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
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S3_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x2000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 181,
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
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S4_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x4000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 182,
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
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S5_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x8000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 183,
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
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S6_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x10000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 184,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S7                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s7_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S7,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x90473589,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S7_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x10000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 185,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP2CORE2X                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap2_core_2x_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP2CORE2X,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x70CC1B69,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP2_CORE_2X_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_2_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x8} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 190,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap2_core_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP2CORE2X,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xAC5F6885,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP2_CORE_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_2_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x1} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 189,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP2IBICTRL0                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap2_ibi_ctrl_2_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP2IBICTRL0,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xF1BF54D2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP2_IBI_CTRL_2_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_2_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x8000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 201,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap2_ibi_ctrl_3_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP2IBICTRL0,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x47DC68A6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP2_IBI_CTRL_3_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_2_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x10000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 202,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP2S0                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap2_s0_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP2S0,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x62380FFF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP2_S0_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_2_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x10} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 191,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP2S1                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap2_s1_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP2S1,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xF02791D2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP2_S1_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_2_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x20} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 192,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP2S2                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap2_s2_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP2S2,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xA5E32B19,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP2_S2_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_2_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x40} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 193,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP2S3                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap2_s3_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP2S3,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xEEF92C79,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP2_S3_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_2_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x80} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 194,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP2S4                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap2_s4_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP2S4,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x7980B17E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP2_S4_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_2_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x100} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 195,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP2S5                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap2_s5_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP2S5,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x9777FCA3,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP2_S5_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_2_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x200} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 196,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP2S6                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap2_s6_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP2S6,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x232CDACA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP2_S6_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_2_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x400} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 197,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP2S7                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap2_s7_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP2S7,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xF372099E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP2_S7_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_2_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x20000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 198,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP3CORE2X                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap3_core_2x_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP3CORE2X,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xBE8AED65,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP3_CORE_2X_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_3_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_3), 0x2} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 206,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap3_core_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP3CORE2X,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x0C8E7F4A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP3_CORE_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_3_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_3), 0x1} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 205,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP3QSPIREF                                  */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap3_qspi_ref_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP3QSPIREF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x61DE362C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP3_QSPI_REF_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_3_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_3), 0x8} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 208,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap3_s0_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP3QSPIREF,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xB2EBD03D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP3_S0_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_3_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_3), 0x4} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 207,
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
      .nDebugMuxSel = 156,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCSDCC4APPS                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_sdcc4_apps_clk",
    .pDomain   = &ClockDomain_GCC_GCCSDCC4APPS,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x582886BC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_SDCC4_APPS_CBCR), HWIO_PHYS(GCC_SDCC4_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 159,
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
      .nDebugMuxSel = 144,
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
      .nDebugMuxSel = 29,
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
      .nDebugMuxSel = 65,
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
      .nDebugMuxSel = 348,
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
      .nDebugMuxSel = 355,
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
      .nDebugMuxSel = 356,
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
      .nDebugMuxSel = 351,
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
      .nDebugMuxSel = 357,
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
      .nDebugMuxSel = 350,
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
      .nDebugMuxSel = 354,
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
      .nDebugMuxSel = 64,
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
      .nDebugMuxSel = 30,
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
      .nDebugMuxSel = 143,
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
      .nDebugMuxSel = 145,
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
      .nDebugMuxSel = 146,
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
      .nDebugMuxSel = 147,
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
      .nDebugMuxSel = 148,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCVSENSOR                                            */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_gx_vsense_clk",
    .pDomain   = &ClockDomain_GCC_GCCVSENSOR,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x2DA8421F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_VSENSE_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 16,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCXO                                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_camera_xo_clk",
    .pDomain   = &ClockDomain_GCC_GCCXO,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xEF993118,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CAMERA_XO_CBCR), HWIO_PHYS(GCC_CAMERA_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 105,
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
      .nDebugMuxSel = 110,
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
      .nDebugMuxSel = 430,
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
      .nDebugMuxSel = 210,
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
      .nDebugMuxSel = 119,
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
      .nDebugMuxSel = 34,
    },
  },
  {
    .szName    = "gpu_cc_gx_ff_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCFF,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xD12CF765,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_FF_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
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
      .nDebugMuxSel = 31,
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
      .nDebugMuxSel = 19,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GPUCC_GPUCCGXGFX3D                                        */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_acd_gfx3d_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCGXGFX3D,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x9AF74722,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_ACD_GFX3D_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 44,
    },
  },
  {
    .szName    = "gpu_cc_cx_gfx3d_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCGXGFX3D,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x2B627FA6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_GFX3D_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GFX3D_AON_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 40,
    },
  },
  {
    .szName    = "gpu_cc_cx_gfx3d_slv_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCGXGFX3D,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xD96DA83B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_GFX3D_SLV_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GFX3D_AON_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 41,
    },
  },
  {
    .szName    = "gpu_cc_gx_gfx3d_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCGXGFX3D,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x40E4E782,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_GFX3D_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 15,
    },
  },
  {
    .szName    = "gpu_cc_gx_gfx3d_rdvm_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCGXGFX3D,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x14588D9F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_GFX3D_RDVM_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 22,
    },
  },
  {
    .szName    = "gpu_cc_mnd1x_gfx3d_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCGXGFX3D,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xCB2F7FA2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_MND1X_GFX3D_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 45,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GPUCC_GPUCCHUB                                            */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_acd_ahb_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCHUB,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xD8CEEBD9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_ACD_AHB_CBCR), HWIO_PHYS(GPUCC_GPU_CC_ACD_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 47,
    },
  },
  {
    .szName    = "gpu_cc_ahb_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCHUB,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x763BA1C4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_AHB_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 24,
    },
  },
  {
    .szName    = "gpu_cc_crc_ahb_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCHUB,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xACF3D523,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CRC_AHB_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 25,
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
      .nDebugMuxSel = 49,
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
      .nDebugMuxSel = 33,
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
    .szName    = "gpu_cc_acd_cxo_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xFB4F06FB,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_ACD_CXO_CBCR), HWIO_PHYS(GPUCC_GPU_CC_ACD_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 46,
    },
  },
  {
    .szName    = "gpu_cc_cx_accu_shift_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x2F27F55F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_ACCU_SHIFT_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 38,
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
      .nDebugMuxSel = 12,
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
      .nDebugMuxSel = 32,
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
      .nDebugMuxSel = 14,
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
      .nDebugMuxSel = 13,
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
      .nDebugMuxSel = 23,
    },
  },
  {
    .szName    = "gpu_cc_gx_cxo_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x28DEB84B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_CXO_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 18,
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
      .nDebugMuxSel = 7,
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
  /* ClockDomain_VIDEOCC_VIDEOCCMVS1                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "video_cc_mvs1_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCMVS1,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0x770FB487,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_MVS1_CBCR), HWIO_PHYS(VCODEC_VIDEO_CC_MVS1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 5,
    },
  },
  {
    .szName    = "video_cc_mvs1c_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCMVS1,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0xD3F30B66,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_MVS1C_CBCR), HWIO_PHYS(VCODEC_VIDEO_CC_MVS1C_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 9,
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
      .nDebugMuxSel = 12,
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
      .nDebugMuxSel = 13,
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
      .nDebugMuxSel = 14,
    },
  },
  {
    .szName    = "video_cc_mvs1_shift_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCXO,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0x782AEB80,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_MVS1_SHIFT_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 15,
    },
  },
  {
    .szName    = "video_cc_mvs1c_shift_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCXO,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0xC5E20EA4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_MVS1C_SHIFT_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 16,
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
      .nDebugMuxSel = 11,
    },
  },
};


/*=========================================================================
      Power Domains
==========================================================================*/

static ClockPowerDomainNodeType aPowerDomains[] =
{
  {
    .szName         = "cam_cc_bps_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MXC,
    .nUniqueId      = 0x08822AAA,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(CAM_CC_BPS_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "cam_cc_ife_0_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MXC,
    .nUniqueId      = 0x04319705,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(CAM_CC_IFE_0_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "cam_cc_ife_1_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MXC,
    .nUniqueId      = 0x4A013E42,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(CAM_CC_IFE_1_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "cam_cc_ife_2_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MXC,
    .nUniqueId      = 0xAA09A362,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(CAM_CC_IFE_2_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "cam_cc_ipe_0_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MXC,
    .nUniqueId      = 0x5AAE87F4,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(CAM_CC_IPE_0_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "cam_cc_sbi_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MXC,
    .nUniqueId      = 0x62F9FBE0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(CAM_CC_SBI_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "cam_cc_sfe_0_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MXC,
    .nUniqueId      = 0x7617DC52,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(CAM_CC_SFE_0_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "cam_cc_sfe_1_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MXC,
    .nUniqueId      = 0xDBEB1524,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(CAM_CC_SFE_1_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "cam_cc_sfe_2_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MXC,
    .nUniqueId      = 0x0D2B528C,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(CAM_CC_SFE_2_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "cam_cc_titan_top_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MXC,
    .nUniqueId      = 0x16E83103,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(CAM_CC_TITAN_TOP_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "disp_cc_mdss_core_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MX,
    .nUniqueId      = 0x32294237,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(DISP_CC_MDSS_CORE_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "disp_cc_mdss_core_int2_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MX,
    .nUniqueId      = 0x4A7593B6,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(DISP_CC_MDSS_CORE_INT2_GDSCR),
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
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MX,
    .nUniqueId      = 0x2AE8F85B,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_PCIE_0_PHY_GDSCR),
      .VoterRegister  = {HWIO_PHYS(GCC_PROC_GDSC_COLLAPSE_ENA_VOTE), 0x8},
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_pcie_1_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MX,
    .nUniqueId      = 0x0BE3F4DE,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_PCIE_1_GDSCR),
      .VoterRegister  = {HWIO_PHYS(GCC_PROC_GDSC_COLLAPSE_ENA_VOTE), 0x2},
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_pcie_1_phy_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MX,
    .nUniqueId      = 0x126858E6,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_PCIE_1_PHY_GDSCR),
      .VoterRegister  = {HWIO_PHYS(GCC_PROC_GDSC_COLLAPSE_ENA_VOTE), 0x10},
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_ufs_mem_phy_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MX,
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
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MX,
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
    .szName         = "gpu_cc_gx_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_GX | RAIL_VDD_MX | RAIL_VDD_MXC,
    .nUniqueId      = 0x1E2E5CC0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GPUCC_GPU_CC_GX_GDSCR),
      .pmControl      = &HAL_clk_GPUGxPowerDomainControl,
    },
  },
  {
    .szName         = "video_cc_mvs0_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MXC,
    .nUniqueId      = 0x0C6A70FC,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(VCODEC_VIDEO_CC_MVS0_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "video_cc_mvs0c_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MXC,
    .nUniqueId      = 0x07EA7371,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(VCODEC_VIDEO_CC_MVS0C_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "video_cc_mvs1_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MXC,
    .nUniqueId      = 0x3E5302F0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(VCODEC_VIDEO_CC_MVS1_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "video_cc_mvs1c_gdsc",
    .nRailMask      = RAIL_VDD_MM | RAIL_VDD_MXC,
    .nUniqueId      = 0x4180BA0C,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(VCODEC_VIDEO_CC_MVS1C_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
};


/*=========================================================================
      CAM CESTA
==========================================================================*/

static const uint32_t aCAMCESTASequence[] =
{
  0x38C15000, //0x000     : 0x5000     br_MAIN:                  SET1 crmc_seq_in_prgs
              //0x002     : 0x38c1                               BEQR perf_up=1 br_PERF_UP
  0x40003882, //0x004     : 0x3882                               BEQR perf_dn=1 br_PERF_DN
              //0x006     : 0x4000                               SET0 crmc_seq_in_prgs
  0x50011000, //0x008     : 0x1000                               RETURN
              //0x00a     : 0x5001     br_FREQ_CHANGE:           SET1 freq_change_in_prgs
  0x1C151C12, //0x00c     : 0x1c12                               CALL br_ENABLE_PLL
              //0x00e     : 0x1c15                               CALL br_UPDATE_RCG
  0x40011C13, //0x010     : 0x1c13                               CALL br_DISABLE_PLL
              //0x012     : 0x4001                               SET0 freq_change_in_prgs
  0xB3001000, //0x014     : 0x1000                               RETURN
              //0x016     : 0xb300     br_SRC_DIV_CHANGE:        RD RCG_CFG_ADDR
  0xED1F8F02, //0x018     : 0x8f02                               MV TEMP6_VAL_RW AHB_RD_DATA
              //0x01a     : 0xed1f                               MVI ALU_NAND_OP_B 0x1F
  0x0000EC1F, //0x01c     : 0xec1f                               MVI ALU_NAND_OP_A 0x1F
              //0x01e     : 0x0000                               DELI 0ns
  0x1C0B8F83, //0x020     : 0x8f83                               MV TEMP7_VAL_RW ALU_RESULT
              //0x022     : 0x1c0b                               CALL br_MASK_VALUE
  0x8212829E, //0x024     : 0x829e                               MV ALU_ADD_OP_B TEMP6_VAL_RW
              //0x026     : 0x8212                               MV ALU_ADD_OP_A SRC_DIV
  0xA3030000, //0x028     : 0x0000                               DELI 0ns
              //0x02a     : 0xa303     br_WRITE_RCG_CFG:         WR RCG_CFG_ADDR ALU_RESULT
  0x398D1000, //0x02c     : 0x1000                               RETURN
              //0x02e     : 0x398d     br_UPDATE_RCG:            BEQR src_div_change=1 br_SRC_DIV_CHANGE
  0xE1033A0E, //0x030     : 0x3a0e                               BEQR src_val_change=1 br_SRC_VAL_CHANGE
              //0x032     : 0xe103                               MVI RD_WR_DATA_PORT 0x3
  0xE202A341, //0x034     : 0xa341                               WR RCG_CMD_ADDR RD_WR_DATA_PORT
              //0x036     : 0xe202                               MVI RD_CMP_DATA 0x2
  0xB340E303, //0x038     : 0xe303                               MVI RD_CMP_MASK 0x3
              //0x03a     : 0xb340     br_POLL_RCG_DONE:         RD RCG_CMD_ADDR
  0x10002007, //0x03c     : 0x2007                               BEQ rd_flag=0 br_POLL_RCG_DONE
              //0x03e     : 0x1000                               RETURN
  0x8F02B300, //0x040     : 0xb300     br_SRC_VAL_CHANGE:        RD RCG_CFG_ADDR
              //0x042     : 0x8f02                               MV TEMP6_VAL_RW AHB_RD_DATA
  0xEA1FEB08, //0x044     : 0xeb08                               MVI ALU_LSHFT_NUM_BITS 0x8
              //0x046     : 0xea1f                               MVI ALU_LSHFT_OP_A 0x1F
  0x86830000, //0x048     : 0x0000                               DELI 0ns
              //0x04a     : 0x8683                               MV ALU_NAND_OP_B ALU_RESULT
  0x00008603, //0x04c     : 0x8603                               MV ALU_NAND_OP_A ALU_RESULT
              //0x04e     : 0x0000                               DELI 0ns
  0x1C0B8F83, //0x050     : 0x8f83                               MV TEMP7_VAL_RW ALU_RESULT
              //0x052     : 0x1c0b                               CALL br_MASK_VALUE
  0x8213829E, //0x054     : 0x829e                               MV ALU_ADD_OP_B TEMP6_VAL_RW
              //0x056     : 0x8213                               MV ALU_ADD_OP_A SRC_VAL
  0x180C0000, //0x058     : 0x0000                               DELI 0ns
              //0x05a     : 0x180c                               JMP br_WRITE_RCG_CFG
  0x861F869E, //0x05c     : 0x869e     br_MASK_VALUE:            MV ALU_NAND_OP_B TEMP6_VAL_RW
              //0x05e     : 0x861f                               MV ALU_NAND_OP_A TEMP7_VAL_RW
  0x86830000, //0x060     : 0x0000                               DELI 0ns
              //0x062     : 0x8683                               MV ALU_NAND_OP_B ALU_RESULT
  0x00008603, //0x064     : 0x8603                               MV ALU_NAND_OP_A ALU_RESULT
              //0x066     : 0x0000                               DELI 0ns
  0x10008F03, //0x068     : 0x8f03                               MV TEMP6_VAL_RW ALU_RESULT
              //0x06a     : 0x1000                               RETURN
  0xEE008793, //0x06c     : 0x8793     br_SET_PLL_FREQ:          MV ALU_BOOL_OP_B SRC_VAL
              //0x06e     : 0xee00                               MVI ALU_BOOL_OP_A 0x0
  0x284F0000, //0x070     : 0x0000                               DELI 0ns
              //0x072     : 0x284f                               BEQ bool_flag=1 br_RETURN
  0x8F02B280, //0x074     : 0xb280                               RD PLL_L_VAL_ADDR
              //0x076     : 0x8f02                               MV TEMP6_VAL_RW AHB_RD_DATA
  0xECFFEDFF, //0x078     : 0xedff                               MVI ALU_NAND_OP_B 0xFF
              //0x07a     : 0xecff                               MVI ALU_NAND_OP_A 0xFF
  0x8F830000, //0x07c     : 0x0000                               DELI 0ns
              //0x07e     : 0x8f83                               MV TEMP7_VAL_RW ALU_RESULT
  0x82851C0B, //0x080     : 0x1c0b                               CALL br_MASK_VALUE
              //0x082     : 0x8285                               MV ALU_ADD_OP_B FP_LVAL
  0x0000821E, //0x084     : 0x821e                               MV ALU_ADD_OP_A TEMP6_VAL_RW
              //0x086     : 0x0000                               DELI 0ns
  0x828AA283, //0x088     : 0xa283                               WR PLL_L_VAL_ADDR ALU_RESULT
              //0x08a     : 0x828a                               MV ALU_ADD_OP_B PLL_L_VAL_ADDR
  0x0000E404, //0x08c     : 0xe404                               MVI ALU_ADD_OP_A 0x4
              //0x08e     : 0x0000                               DELI 0ns
  0x1C10A0D4, //0x090     : 0xa0d4                               WR ALU_RESULT FP_ALPHA_VAL
              //0x092     : 0x1c10                               CALL br_LATCH_PLL_INPUT
  0xEB1F1000, //0x094     : 0x1000                               RETURN
              //0x096     : 0xeb1f     br_POLL_LOCK_DETECT:      MVI ALU_LSHFT_NUM_BITS 31
  0x0000EA01, //0x098     : 0xea01                               MVI ALU_LSHFT_OP_A 1
              //0x09a     : 0x0000                               DELI 0ns
  0x81838103, //0x09c     : 0x8103                               MV RD_CMP_DATA ALU_RESULT
              //0x09e     : 0x8183                               MV RD_CMP_MASK ALU_RESULT
  0x2003B2C0, //0x0a0     : 0xb2c0                               RD PLL_MODE_ADDR
              //0x0a2     : 0x2003                               BEQ rd_flag=0 br_POLL_LOCK_DETECT
  0xB2C01000, //0x0a4     : 0x1000                               RETURN
              //0x0a6     : 0xb2c0     br_LATCH_PLL_INPUT:       RD PLL_MODE_ADDR
  0xEA01EB0E, //0x0a8     : 0xeb0e                               MVI ALU_LSHFT_NUM_BITS 14
              //0x0aa     : 0xea01                               MVI ALU_LSHFT_OP_A 1
  0x8F830000, //0x0ac     : 0x0000                               DELI 0ns
              //0x0ae     : 0x8f83                               MV TEMP7_VAL_RW ALU_RESULT
  0x82028283, //0x0b0     : 0x8283                               MV ALU_ADD_OP_B ALU_RESULT
              //0x0b2     : 0x8202                               MV ALU_ADD_OP_A AHB_RD_DATA
  0xA2C30000, //0x0b4     : 0x0000                               DELI 0ns
              //0x0b6     : 0xa2c3                               WR PLL_MODE_ADDR ALU_RESULT
  0xEA01EB0D, //0x0b8     : 0xeb0d                               MVI ALU_LSHFT_NUM_BITS 13
              //0x0ba     : 0xea01                               MVI ALU_LSHFT_OP_A 1
  0x81030000, //0x0bc     : 0x0000                               DELI 0ns
              //0x0be     : 0x8103                               MV RD_CMP_DATA ALU_RESULT
  0xB2C08183, //0x0c0     : 0x8183                               MV RD_CMP_MASK ALU_RESULT
              //0x0c2     : 0xb2c0     br_LATCH_INPUT_ACK:       RD PLL_MODE_ADDR
  0xB2C02011, //0x0c4     : 0x2011                               BEQ rd_flag=0 br_LATCH_INPUT_ACK
              //0x0c6     : 0xb2c0                               RD PLL_MODE_ADDR
  0x869F8F02, //0x0c8     : 0x8f02                               MV TEMP6_VAL_RW AHB_RD_DATA
              //0x0ca     : 0x869f                               MV ALU_NAND_OP_B TEMP7_VAL_RW
  0x0000861F, //0x0cc     : 0x861f                               MV ALU_NAND_OP_A TEMP7_VAL_RW
              //0x0ce     : 0x0000                               DELI 0ns
  0x1C0B8F83, //0x0d0     : 0x8f83                               MV TEMP7_VAL_RW ALU_RESULT
              //0x0d2     : 0x1c0b                               CALL br_MASK_VALUE
  0x1000A2DE, //0x0d4     : 0xa2de                               WR PLL_MODE_ADDR TEMP6_VAL_RW
              //0x0d6     : 0x1000                               RETURN
  0x8F02B2C0, //0x0d8     : 0xb2c0     br_ENABLE_PLLOUT:         RD PLL_MODE_ADDR
              //0x0da     : 0x8f02                               MV TEMP6_VAL_RW AHB_RD_DATA
  0xEC01ED01, //0x0dc     : 0xed01                               MVI ALU_NAND_OP_B 0x1
              //0x0de     : 0xec01                               MVI ALU_NAND_OP_A 0x1
  0x8F830000, //0x0e0     : 0x0000                               DELI 0ns
              //0x0e2     : 0x8f83                               MV TEMP7_VAL_RW ALU_RESULT
  0x829E1C0B, //0x0e4     : 0x1c0b                               CALL br_MASK_VALUE
              //0x0e6     : 0x829e                               MV ALU_ADD_OP_B TEMP6_VAL_RW
  0x00008219, //0x0e8     : 0x8219                               MV ALU_ADD_OP_A TEMP1_VAL_RW
              //0x0ea     : 0x0000                               DELI 0ns
  0x1000A2C3, //0x0ec     : 0xa2c3                               WR PLL_MODE_ADDR ALU_RESULT
              //0x0ee     : 0x1000                               RETURN
  0x8709878B, //0x0f0     : 0x878b     br_ENABLE_PLL:            MV ALU_BOOL_OP_B PLL_MODE_ADDR
              //0x0f2     : 0x8709                               MV ALU_BOOL_OP_A CONSTANT_ZERO
  0x284F0000, //0x0f4     : 0x0000                               DELI 0ns
              //0x0f6     : 0x284f                               BEQ bool_flag=1 br_RETURN
  0x87098793, //0x0f8     : 0x8793                               MV ALU_BOOL_OP_B SRC_VAL
              //0x0fa     : 0x8709                               MV ALU_BOOL_OP_A CONSTANT_ZERO
  0x284F0000, //0x0fc     : 0x0000                               DELI 0ns
              //0x0fe     : 0x284f                               BEQ bool_flag=1 br_RETURN
  0xF9011C06, //0x100     : 0x1c06                               CALL br_SET_PLL_FREQ
              //0x102     : 0xf901                               MVI TEMP1_VAL_RW 0x1
  0xE404828B, //0x104     : 0x828b                               MV ALU_ADD_OP_B PLL_MODE_ADDR
              //0x106     : 0xe404                               MVI ALU_ADD_OP_A 0x4
  0xA0D90000, //0x108     : 0x0000                               DELI 0ns
              //0x10a     : 0xa0d9                               WR ALU_RESULT TEMP1_VAL_RW
  0x1C030007, //0x10c     : 0x0007                               DELI 1us
              //0x10e     : 0x1c03                               CALL br_POLL_LOCK_DETECT
  0x878B1814, //0x110     : 0x1814                               JMP br_ENABLE_PLLOUT
              //0x112     : 0x878b     br_DISABLE_PLL:           MV ALU_BOOL_OP_B PLL_MODE_ADDR
  0x00008709, //0x114     : 0x8709                               MV ALU_BOOL_OP_A CONSTANT_ZERO
              //0x116     : 0x0000                               DELI 0ns
  0x8793284F, //0x118     : 0x284f                               BEQ bool_flag=1 br_RETURN
              //0x11a     : 0x8793                               MV ALU_BOOL_OP_B SRC_VAL
  0x00008709, //0x11c     : 0x8709                               MV ALU_BOOL_OP_A CONSTANT_ZERO
              //0x11e     : 0x0000                               DELI 0ns
  0x828B204F, //0x120     : 0x204f                               BEQ bool_flag=0 br_RETURN
              //0x122     : 0x828b                               MV ALU_ADD_OP_B PLL_MODE_ADDR
  0x0000E404, //0x124     : 0xe404                               MVI ALU_ADD_OP_A 0x4
              //0x126     : 0x0000                               DELI 0ns
  0x8C89A0C9, //0x128     : 0xa0c9                               WR ALU_RESULT CONSTANT_ZERO
              //0x12a     : 0x8c89                               MV TEMP1_VAL_RW CONSTANT_ZERO
  0x50021814, //0x12c     : 0x1814                               JMP br_ENABLE_PLLOUT
              //0x12e     : 0x5002     br_VOL_CHANGE:            SET1 vol_change_in_prgs
  0x70005003, //0x130     : 0x5003                               SET1 crmv_req
              //0x132     : 0x7000                               WAIT1 crmv_ack
  0x40024003, //0x134     : 0x4003                               SET0 crmv_req
              //0x136     : 0x4002                               SET0 vol_change_in_prgs
  0x1C041000, //0x138     : 0x1000                               RETURN
              //0x13a     : 0x1c04     br_PERF_UP:               CALL br_VOL_CHANGE
  0x1C003949, //0x13c     : 0x3949                               BEQR from_cp0=1 br_FROM_CP0
              //0x13e     : 0x1c00                               CALL br_FREQ_CHANGE
  0x1C001000, //0x140     : 0x1000                               RETURN
              //0x142     : 0x1c00     br_PERF_DN:               CALL br_FREQ_CHANGE
  0x290A1C04, //0x144     : 0x1c04                               CALL br_VOL_CHANGE
              //0x146     : 0x290a                               BEQ to_cp0=1 br_TO_CP0
  0x8C901000, //0x148     : 0x1000                               RETURN
              //0x14a     : 0x8c90     br_TO_CP0:                MV TEMP1_VAL_RW CBCR_OFF_VAL
  0x18131C05, //0x14c     : 0x1c05                               CALL br_CBCR_WRITES
              //0x14e     : 0x1813                               JMP br_DISABLE_PLL
  0x8C911C12, //0x150     : 0x1c12     br_FROM_CP0:              CALL br_ENABLE_PLL
              //0x152     : 0x8c91                               MV TEMP1_VAL_RW CBCR_ON_VAL
  0x878E1805, //0x154     : 0x1805                               JMP br_CBCR_WRITES
              //0x156     : 0x878e     br_CBCR_WRITES:           MV ALU_BOOL_OP_B NUM_CBCS
  0x00008718, //0x158     : 0x8718                               MV ALU_BOOL_OP_A TEMP0_VAL_RW
              //0x15a     : 0x0000                               DELI 0ns
  0x89182848, //0x15c     : 0x2848                               BEQ bool_flag=1 br_END_CBCR_WRITES
              //0x15e     : 0x8918                               MV CBCR_MUX_SEL TEMP0_VAL_RW
  0xE501A3D9, //0x160     : 0xa3d9                               WR CBCR_ADDR TEMP1_VAL_RW
              //0x162     : 0xe501                               MVI ALU_ADD_OP_B 0x1
  0x00008218, //0x164     : 0x8218                               MV ALU_ADD_OP_A TEMP0_VAL_RW
              //0x166     : 0x0000                               DELI 0ns
  0x18058C03, //0x168     : 0x8c03                               MV TEMP0_VAL_RW ALU_RESULT
              //0x16a     : 0x1805                               JMP br_CBCR_WRITES
  0x8C898C09, //0x16c     : 0x8c09     br_END_CBCR_WRITES:       MV TEMP0_VAL_RW CONSTANT_ZERO
              //0x16e     : 0x8c89                               MV TEMP1_VAL_RW CONSTANT_ZERO
  0x10008D09, //0x170     : 0x8d09                               MV TEMP2_VAL_RW CONSTANT_ZERO
              //0x172     : 0x1000     br_RETURN:                RETURN
};

static const uint32_t aCAMCESTABranches[] =
{
  0x00A, //br_FREQ_CHANGE
  0x13A, //br_PERF_UP
  0x142, //br_PERF_DN
  0x096, //br_POLL_LOCK_DETECT
  0x12E, //br_VOL_CHANGE
  0x156, //br_CBCR_WRITES
  0x06C, //br_SET_PLL_FREQ
  0x03A, //br_POLL_RCG_DONE
  0x16C, //br_END_CBCR_WRITES
  0x150, //br_FROM_CP0
  0x14A, //br_TO_CP0
  0x05C, //br_MASK_VALUE
  0x02A, //br_WRITE_RCG_CFG
  0x016, //br_SRC_DIV_CHANGE
  0x040, //br_SRC_VAL_CHANGE
  0x172, //br_RETURN
  0x0A6, //br_LATCH_PLL_INPUT
  0x0C2, //br_LATCH_INPUT_ACK
  0x0F0, //br_ENABLE_PLL
  0x112, //br_DISABLE_PLL
  0x0D8, //br_ENABLE_PLLOUT
  0x02E, //br_UPDATE_RCG
};

static const ClockCESTARegType aCAMCESTARegs[] =
{
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CMD_ADDR, 0),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00011018 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CFG_ADDR, 0),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x0001101C },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 0, 0),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 0, 2),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 0, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 0, 0),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 1, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 1, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 1, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 0, 1),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 2, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 2, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 2, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 0, 2),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 0, 2),                .eType = CESTA_REG_RAW,             .Data.nVal = 0x8AAA0030 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 3, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 3, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 3, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 0, 3),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 0, 3),                .eType = CESTA_REG_RAW,             .Data.nVal = 0xE000003D },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 4, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 4, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 4, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 0, 4),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 0, 4),                .eType = CESTA_REG_RAW,             .Data.nVal = 0x50000046 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 5, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_NOM } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 5, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_NOM } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 5, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 0, 5),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 0, 5),                .eType = CESTA_REG_RAW,             .Data.nVal = 0xC5550051 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_PLL_L_VAL_ADDR, 0),                               .eType = CESTA_REG_RAW,             .Data.nVal = 0x00003010 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_PLL_L_MODE_ADDR, 0),                              .eType = CESTA_REG_RAW,             .Data.nVal = 0x00003000 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_NUM_CBC, 0),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000002 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 0, 0),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x0001103C },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 0, 1),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00011030 },
  { .nAddr = HWIO_PHYSI(TITAN_CRMC_ENm, 0),                                          .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CMD_ADDR, 1),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00012018 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CFG_ADDR, 1),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x0001201C },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 0, 0),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 0, 2),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 0, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 1, 0),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 1, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 1, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 1, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 1, 1),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 2, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 2, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 2, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 1, 2),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 1, 2),                .eType = CESTA_REG_RAW,             .Data.nVal = 0x8AAA0030 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 3, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 3, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 3, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 1, 3),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 1, 3),                .eType = CESTA_REG_RAW,             .Data.nVal = 0xE000003D },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 4, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 4, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 4, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 1, 4),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 1, 4),                .eType = CESTA_REG_RAW,             .Data.nVal = 0x50000046 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 5, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_NOM } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 5, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_NOM } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 5, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 1, 5),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 1, 5),                .eType = CESTA_REG_RAW,             .Data.nVal = 0xC5550051 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_PLL_L_VAL_ADDR, 1),                               .eType = CESTA_REG_RAW,             .Data.nVal = 0x00004010 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_PLL_L_MODE_ADDR, 1),                              .eType = CESTA_REG_RAW,             .Data.nVal = 0x00004000 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_NUM_CBC, 1),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000002 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 1, 0),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x0001203C },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 1, 1),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00012030 },
  { .nAddr = HWIO_PHYSI(TITAN_CRMC_ENm, 1),                                          .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CMD_ADDR, 2),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00012068 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CFG_ADDR, 2),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x0001206C },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 0, 0),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 0, 2),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 0, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 2, 0),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 1, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 1, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 1, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 2, 1),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 2, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 2, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 2, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 2, 2),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 2, 2),                .eType = CESTA_REG_RAW,             .Data.nVal = 0x8AAA0030 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 3, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 3, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 3, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 2, 3),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 2, 3),                .eType = CESTA_REG_RAW,             .Data.nVal = 0xE000003D },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 4, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 4, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 4, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 2, 4),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 2, 4),                .eType = CESTA_REG_RAW,             .Data.nVal = 0x50000046 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 5, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_NOM } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 5, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_NOM } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 2, 5, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 2, 5),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 2, 5),                .eType = CESTA_REG_RAW,             .Data.nVal = 0xC5550051 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_PLL_L_VAL_ADDR, 2),                               .eType = CESTA_REG_RAW,             .Data.nVal = 0x00005010 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_PLL_L_MODE_ADDR, 2),                              .eType = CESTA_REG_RAW,             .Data.nVal = 0x00005000 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_NUM_CBC, 2),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000002 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 2, 0),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x0001208C },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 2, 1),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00012080 },
  { .nAddr = HWIO_PHYSI(TITAN_CRMC_ENm, 2),                                          .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CMD_ADDR, 3),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x0001306C },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CFG_ADDR, 3),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00013070 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 3, 0, 0),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 3, 0, 2),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 3, 0, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 3, 0),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 3, 1, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 3, 1, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 3, 1, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 3, 1),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 3, 1),                .eType = CESTA_REG_RAW,             .Data.nVal = 0x8AAA0030 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 3, 2, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 3, 2, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 3, 2, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 3, 2),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 3, 2),                .eType = CESTA_REG_RAW,             .Data.nVal = 0xE000003D },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 3, 3, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 3, 3, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 3, 3, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 3, 3),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 3, 3),                .eType = CESTA_REG_RAW,             .Data.nVal = 0x50000046 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 3, 4, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_NOM } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 3, 4, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_NOM } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 3, 4, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 3, 4),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 3, 4),                .eType = CESTA_REG_RAW,             .Data.nVal = 0xC5550051 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_PLL_L_VAL_ADDR, 3),                               .eType = CESTA_REG_RAW,             .Data.nVal = 0x00006010 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_PLL_L_MODE_ADDR, 3),                              .eType = CESTA_REG_RAW,             .Data.nVal = 0x00006000 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_NUM_CBC, 3),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000002 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 3, 0),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00013084 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 3, 1),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00013090 },
  { .nAddr = HWIO_PHYSI(TITAN_CRMC_ENm, 3),                                          .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CMD_ADDR, 4),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x000130BC },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CFG_ADDR, 4),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x000130C0 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 4, 0, 0),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 4, 0, 2),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 4, 0, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 4, 0),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 4, 1, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 4, 1, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 4, 1, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 4, 1),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 4, 1),                .eType = CESTA_REG_RAW,             .Data.nVal = 0x8AAA0030 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 4, 2, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 4, 2, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 4, 2, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 4, 2),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 4, 2),                .eType = CESTA_REG_RAW,             .Data.nVal = 0xE000003D },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 4, 3, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 4, 3, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 4, 3, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 4, 3),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 4, 3),                .eType = CESTA_REG_RAW,             .Data.nVal = 0x50000046 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 4, 4, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_NOM } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 4, 4, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_NOM } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 4, 4, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 4, 4),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 4, 4),                .eType = CESTA_REG_RAW,             .Data.nVal = 0xC5550051 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_PLL_L_VAL_ADDR, 4),                               .eType = CESTA_REG_RAW,             .Data.nVal = 0x00007010 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_PLL_L_MODE_ADDR, 4),                              .eType = CESTA_REG_RAW,             .Data.nVal = 0x00007000 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_NUM_CBC, 4),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000002 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 4, 0),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x000130D4 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 4, 1),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x000130E0 },
  { .nAddr = HWIO_PHYSI(TITAN_CRMC_ENm, 4),                                          .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CMD_ADDR, 5),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x0001310C },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CFG_ADDR, 5),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00013110 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 5, 0, 0),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 5, 0, 2),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 5, 0, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 5, 0),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 5, 1, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 5, 1, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 5, 1, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 5, 1),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 5, 1),                .eType = CESTA_REG_RAW,             .Data.nVal = 0x8AAA0030 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 5, 2, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 5, 2, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 5, 2, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 5, 2),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 5, 2),                .eType = CESTA_REG_RAW,             .Data.nVal = 0xE000003D },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 5, 3, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 5, 3, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS_L1 } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 5, 3, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 5, 3),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 5, 3),                .eType = CESTA_REG_RAW,             .Data.nVal = 0x50000046 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 5, 4, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_NOM } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 5, 4, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_NOM } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 5, 4, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 5, 4),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000601 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_PLL_L_VAL_LUT, 5, 4),                .eType = CESTA_REG_RAW,             .Data.nVal = 0xC5550051 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_PLL_L_VAL_ADDR, 5),                               .eType = CESTA_REG_RAW,             .Data.nVal = 0x0000A010 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_PLL_L_MODE_ADDR, 5),                              .eType = CESTA_REG_RAW,             .Data.nVal = 0x0000A000 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_NUM_CBC, 5),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000002 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 5, 0),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00013124 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 5, 1),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00013130 },
  { .nAddr = HWIO_PHYSI(TITAN_CRMC_ENm, 5),                                          .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CMD_ADDR, 6),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00013238 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CFG_ADDR, 6),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x0001323C },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 6, 0, 0),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 6, 0, 2),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 6, 0, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 6, 0),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 6, 1, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 6, 1, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 6, 1, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 6, 1),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000105 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 6, 2, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 6, 2, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 6, 2, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 6, 2),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000104 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_NUM_CBC, 6),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 6, 0),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00013250 },
  { .nAddr = HWIO_PHYSI(TITAN_CRMC_ENm, 6),                                          .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CMD_ADDR, 7),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x0001104C },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CFG_ADDR, 7),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00011050 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 7, 0, 0),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 7, 0, 1),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 7, 0, 2),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 7, 0, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 7, 0),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 7, 1, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 7, 1, 1),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 7, 1, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 7, 1, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 7, 1),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 7, 2, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 7, 2, 1),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 7, 2, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 7, 2, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 7, 2),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000105 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 7, 3, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 7, 3, 1),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mx.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 7, 3, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 7, 3, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 7, 3),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000104 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_NUM_CBC, 7),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x0000000A },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 7, 0),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x000150FC },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 7, 1),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00015120 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 7, 2),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00015140 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 7, 3),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00015160 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 7, 4),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00015180 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 7, 5),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x000151A0 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 7, 6),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x000151C0 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 7, 7),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x000151E0 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 7, 8),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00015100 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 7, 9),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x0001304C },
  { .nAddr = HWIO_PHYSI(TITAN_CRMC_ENm, 7),                                          .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CMD_ADDR, 8),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x0001325C },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_RCGR_CFG_ADDR, 8),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00013260 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 8, 0, 0),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 8, 0, 2),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 8, 0, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 8, 0),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 8, 1, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 8, 1, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 8, 1, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 8, 1),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000203 },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 8, 2, 0),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mmcx.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 8, 2, 2),             .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mxc.lvl", RAIL_VOLTAGE_LEVEL_SVS } },
  { .nAddr = HWIO_PHYSI3(TITAN_VCDm_PERF_LEVELp_RAILr_VOL_LUT, 8, 2, 3),             .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_PERF_LEVELp_CFG_RCGR_LUT, 8, 2),                 .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000301 },
  { .nAddr = HWIO_PHYSI(TITAN_VCDm_NUM_CBC, 8),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000002 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 8, 0),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00013284 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_CBCn_ADDR, 8, 1),                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00013274 },
  { .nAddr = HWIO_PHYSI(TITAN_CRMC_ENm, 8),                                          .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI2(TITAN_RAILr_TCS_CMDn_ADDR, 0, 0),                           .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "mmcx.lvl", 0 } },
  { .nAddr = HWIO_PHYSI2(TITAN_RAILr_TCS_CMDn_ADDR, 1, 0),                           .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "mx.lvl", 0 } },
  { .nAddr = HWIO_PHYSI2(TITAN_RAILr_TCS_CMDn_ADDR, 2, 0),                           .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "mxc.lvl", 0 } },
  { .nAddr = HWIO_PHYSI2(TITAN_RAILr_TCS_CMDn_ADDR, 3, 0),                           .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "xo.lvl", 0 } },
  { .nAddr = HWIO_PHYSI(TITAN_RAILr_EN, 0),                                          .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(TITAN_RAILr_EN, 1),                                          .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(TITAN_RAILr_EN, 2),                                          .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(TITAN_RAILr_EN, 3),                                          .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_BW_CPn_LUT, 0, 0),                               .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_BW_CPn_LUT, 0, 1),                               .eType = CESTA_REG_RAW,             .Data.nVal = 0x0000012C },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_BW_CPn_LUT, 0, 2),                               .eType = CESTA_REG_RAW,             .Data.nVal = 0x00003FFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_BW_CPn_LUT, 0, 3),                               .eType = CESTA_REG_RAW,             .Data.nVal = 0x00003FFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_BW_CPn_LUT, 0, 4),                               .eType = CESTA_REG_RAW,             .Data.nVal = 0x00003FFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_BW_CPn_LUT, 0, 5),                               .eType = CESTA_REG_RAW,             .Data.nVal = 0x00003FFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_BW_CPn_LUT, 0, 6),                               .eType = CESTA_REG_RAW,             .Data.nVal = 0x00003FFF },
  { .nAddr = HWIO_PHYSI2(TITAN_VCDm_BW_CPn_LUT, 0, 7),                               .eType = CESTA_REG_RAW,             .Data.nVal = 0x00003FFF },
  { .nAddr = HWIO_PHYSI2(TITAN_NDn_SCALARs, 0, 0),                                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI2(TITAN_NDn_SCALARs, 0, 1),                                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI2(TITAN_NDn_SCALARs, 1, 0),                                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI2(TITAN_NDn_SCALARs, 1, 1),                                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(TITAN_CRMB_ENm, 0),                                          .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYS(TITAN_CRM_ENABLE),                                            .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
};

static const char *aCAMCESTAClockDeps[] =
{
  "gcc_camera_ahb_clk",
  "cam_cc_drv_xo_clk",
  "cam_cc_drv_ahb_clk",
};

static ClockCESTA CAMCESTA =
{
  .szName         = "cam_cesta",
  .nCRMCBaseAddr  = TITAN_CRMC_REG_BASE,
  .nSequenceAddr  = HWIO_PHYSI(TITAN_SEQ_MEMs, 0),
  .nBranchAddr    = HWIO_PHYSI(TITAN_SEQ_BR_ADDRn, 0),
  .aSequence      = aCAMCESTASequence,
  .nNumSequence   = SIZEOF_ARRAY(aCAMCESTASequence),
  .aBranches      = aCAMCESTABranches,
  .nNumBranches   = SIZEOF_ARRAY(aCAMCESTABranches),
  .aRegVals       = aCAMCESTARegs,
  .nNumRegVals    = SIZEOF_ARRAY(aCAMCESTARegs),
  .aClockDeps     = aCAMCESTAClockDeps,
  .nNumClockDeps  = SIZEOF_ARRAY(aCAMCESTAClockDeps),
  .nMaxPerfOL     = 8,
  .nFlags         = CLOCK_CESTA_FLAG_DEFAULT_ENABLE,
};

/*=========================================================================
      PCIE CESTA
==========================================================================*/

static const uint32_t aPCIECESTASequence[] =
{
  0x38C15000, //0x000     : 0x5000     br_MAIN:                  SET1 crmc_seq_in_prgs
              //0x002     : 0x38c1                               BEQR perf_up=1 br_PERF_UP
  0x40003882, //0x004     : 0x3882                               BEQR perf_dn=1 br_PERF_DN
              //0x006     : 0x4000                               SET0 crmc_seq_in_prgs
  0x39081000, //0x008     : 0x1000                               RETURN
              //0x00a     : 0x3908     br_PERF_DN:               BEQR to_inactive=1 br_M0_M2
  0x1C03310C, //0x00c     : 0x310c                               BEQR to_inactive=0 br_UPDATE_RCG
              //0x00e     : 0x1c03                               CALL br_VOL_CHANGE
  0x1000390E, //0x010     : 0x390e                               BEQR to_inactive=1 br_RSC_SHUTDOWN_REQ
              //0x012     : 0x1000                               RETURN
  0x1C03394F, //0x014     : 0x394f     br_PERF_UP:               BEQR from_inactive=1 br_RSC_BRINGUP_REQ
              //0x016     : 0x1c03                               CALL br_VOL_CHANGE
  0x314C3947, //0x018     : 0x3947                               BEQR from_inactive=1 br_M2_M0
              //0x01a     : 0x314c                               BEQR from_inactive=0 br_UPDATE_RCG
  0xB6001000, //0x01c     : 0x1000                               RETURN
              //0x01e     : 0xb600     br_REG_RMW:               RD TEMP0_VAL_RW
  0x8F9A8F02, //0x020     : 0x8f02                               MV TEMP6_VAL_RW AHB_RD_DATA
              //0x022     : 0x8f9a                               MV TEMP7_VAL_RW TEMP2_VAL_RW
  0x82991C09, //0x024     : 0x1c09                               CALL br_MASK_VALUE
              //0x026     : 0x8299                               MV ALU_ADD_OP_B TEMP1_VAL_RW
  0x0000821E, //0x028     : 0x821e                               MV ALU_ADD_OP_A TEMP6_VAL_RW
              //0x02a     : 0x0000                               DELI 0ns
  0x1000A603, //0x02c     : 0xa603                               WR TEMP0_VAL_RW ALU_RESULT
              //0x02e     : 0x1000                               RETURN
  0x70045007, //0x030     : 0x5007     br_M2_M0:                 SET1 lock_req
              //0x032     : 0x7004                               WAIT1 lock_grant
  0xEA03EB1E, //0x034     : 0xeb1e                               MVI ALU_LSHFT_NUM_BITS 30
              //0x036     : 0xea03                               MVI ALU_LSHFT_OP_A 3
  0x81830000, //0x038     : 0x0000                               DELI 0ns
              //0x03a     : 0x8183                               MV RD_CMP_MASK ALU_RESULT
  0xEA02EB1E, //0x03c     : 0xeb1e                               MVI ALU_LSHFT_NUM_BITS 30
              //0x03e     : 0xea02                               MVI ALU_LSHFT_OP_A 2
  0x81030000, //0x040     : 0x0000                               DELI 0ns
              //0x042     : 0x8103                               MV RD_CMP_DATA ALU_RESULT
  0x2812BC40, //0x044     : 0xbc40     br_POLL_CRMB_PT_IDLE:     RD HW_CLIENT_BW_VOTE_STATUS
              //0x046     : 0x2812                               BEQ rd_flag=1 br_POLL_CRMB_PT_IDLE
  0xF9008C2B, //0x048     : 0x8c2b                               MV TEMP0_VAL_RW GCC_CESTA_GDSC_BRANCH_ENA_VOTE_ADDR
              //0x04a     : 0xf900                               MVI TEMP1_VAL_RW 0x0
  0x1C008D2C, //0x04c     : 0x8d2c                               MV TEMP2_VAL_RW GDSC_SLEEP_ENA_PATTERN
              //0x04e     : 0x1c00                               CALL br_REG_RMW
  0xEA01EB1F, //0x050     : 0xeb1f                               MVI ALU_LSHFT_NUM_BITS 31
              //0x052     : 0xea01                               MVI ALU_LSHFT_OP_A 1
  0x81030000, //0x054     : 0x0000                               DELI 0ns
              //0x056     : 0x8103                               MV RD_CMP_DATA ALU_RESULT
  0xBB408183, //0x058     : 0x8183                               MV RD_CMP_MASK ALU_RESULT
              //0x05a     : 0xbb40     br_POLL_GDSC_PWR_UP:      RD GDSC_STATUS_ADDR
  0xF8002010, //0x05c     : 0x2010                               BEQ rd_flag=0 br_POLL_GDSC_PWR_UP
              //0x05e     : 0xf800                               MVI TEMP0_VAL_RW 0x0
  0xF203AB98, //0x060     : 0xab98                               WR PCIE_PIPE_MUXR TEMP0_VAL_RW
              //0x062     : 0xf203                               MVI CBCR_MUX_SEL 3
  0x8FA98EA9, //0x064     : 0x8ea9                               MV TEMP5_VAL_RW CBCR_3_ON_MASK
              //0x066     : 0x8fa9                               MV TEMP7_VAL_RW CBCR_3_ON_MASK
  0x8C221C04, //0x068     : 0x1c04                               CALL br_CBCR_WRITES
              //0x06a     : 0x8c22                               MV TEMP0_VAL_RW PCIE_PCS_COM_POWER_DOWN_CONTROL
  0xFA01F901, //0x06c     : 0xf901                               MVI TEMP1_VAL_RW 0x1
              //0x06e     : 0xfa01                               MVI TEMP2_VAL_RW 0x1
  0x8C211C00, //0x070     : 0x1c00                               CALL br_REG_RMW
              //0x072     : 0x8c21                               MV TEMP0_VAL_RW PCIE_PCS_PCIE_INT_AUX_CLK_CONFIG1
  0xFAC0F9C0, //0x074     : 0xf9c0                               MVI TEMP1_VAL_RW 0xC0
              //0x076     : 0xfac0                               MVI TEMP2_VAL_RW 0xC0
  0xF2001C00, //0x078     : 0x1c00                               CALL br_REG_RMW
              //0x07a     : 0xf200                               MVI CBCR_MUX_SEL 0
  0x8FA38EA3, //0x07c     : 0x8ea3                               MV TEMP5_VAL_RW CBCR_0_ON_MASK
              //0x07e     : 0x8fa3                               MV TEMP7_VAL_RW CBCR_0_ON_MASK
  0xF2011C04, //0x080     : 0x1c04                               CALL br_CBCR_WRITES
              //0x082     : 0xf201                               MVI CBCR_MUX_SEL 1
  0x8FA58EA5, //0x084     : 0x8ea5                               MV TEMP5_VAL_RW CBCR_1_ON_MASK
              //0x086     : 0x8fa5                               MV TEMP7_VAL_RW CBCR_1_ON_MASK
  0xF2021C04, //0x088     : 0x1c04                               CALL br_CBCR_WRITES
              //0x08a     : 0xf202                               MVI CBCR_MUX_SEL 2
  0x8FA78EA7, //0x08c     : 0x8ea7                               MV TEMP5_VAL_RW CBCR_2_ON_MASK
              //0x08e     : 0x8fa7                               MV TEMP7_VAL_RW CBCR_2_ON_MASK
  0x1C0C1C04, //0x090     : 0x1c04                               CALL br_CBCR_WRITES
              //0x092     : 0x1c0c                               CALL br_UPDATE_RCG
  0xFD00ABD1, //0x094     : 0xabd1                               WR TCSR_PCIE_CLKREF_EN CONSTANT_ONE
              //0x096     : 0xfd00                               MVI TEMP5_VAL_RW 0x0
  0x40071C05, //0x098     : 0x1c05                               CALL br_WRITE_PARF_CLKREQ_OVERRIDE
              //0x09a     : 0x4007                               SET0 lock_req
  0xB8001000, //0x09c     : 0x1000                               RETURN
              //0x09e     : 0xb800     br_WRITE_PARF_CLKREQ_OVERRIDE: RD PARF_CLKREQ_OVERRIDE_ADDR
  0xFF0A8F02, //0x0a0     : 0x8f02                               MV TEMP6_VAL_RW AHB_RD_DATA
              //0x0a2     : 0xff0a                               MVI TEMP7_VAL_RW 0xA
  0x829D1C09, //0x0a4     : 0x1c09                               CALL br_MASK_VALUE
              //0x0a6     : 0x829d                               MV ALU_ADD_OP_B TEMP5_VAL_RW
  0x0000821E, //0x0a8     : 0x821e                               MV ALU_ADD_OP_A TEMP6_VAL_RW
              //0x0aa     : 0x0000                               DELI 0ns
  0x1000A803, //0x0ac     : 0xa803                               WR PARF_CLKREQ_OVERRIDE_ADDR ALU_RESULT
              //0x0ae     : 0x1000                               RETURN
  0x70045007, //0x0b0     : 0x5007     br_M0_M2:                 SET1 lock_req
              //0x0b2     : 0x7004                               WAIT1 lock_grant
  0x1C05FD0A, //0x0b4     : 0xfd0a                               MVI TEMP5_VAL_RW 0xA
              //0x0b6     : 0x1c05                               CALL br_WRITE_PARF_CLKREQ_OVERRIDE
  0xF200ABC9, //0x0b8     : 0xabc9                               WR TCSR_PCIE_CLKREF_EN CONSTANT_ZERO
              //0x0ba     : 0xf200                               MVI CBCR_MUX_SEL 0x0
  0x8FA3FD00, //0x0bc     : 0xfd00                               MVI TEMP5_VAL_RW 0x0
              //0x0be     : 0x8fa3                               MV TEMP7_VAL_RW CBCR_0_ON_MASK
  0xF2011C04, //0x0c0     : 0x1c04                               CALL br_CBCR_WRITES
              //0x0c2     : 0xf201                               MVI CBCR_MUX_SEL 0x1
  0x8FA5FD00, //0x0c4     : 0xfd00                               MVI TEMP5_VAL_RW 0x0
              //0x0c6     : 0x8fa5                               MV TEMP7_VAL_RW CBCR_1_ON_MASK
  0xF2021C04, //0x0c8     : 0x1c04                               CALL br_CBCR_WRITES
              //0x0ca     : 0xf202                               MVI CBCR_MUX_SEL 0x2
  0x8FA7FD00, //0x0cc     : 0xfd00                               MVI TEMP5_VAL_RW 0x0
              //0x0ce     : 0x8fa7                               MV TEMP7_VAL_RW CBCR_2_ON_MASK
  0x1C0C1C04, //0x0d0     : 0x1c04                               CALL br_CBCR_WRITES
              //0x0d2     : 0x1c0c                               CALL br_UPDATE_RCG
  0xAB98F802, //0x0d4     : 0xf802                               MVI TEMP0_VAL_RW 0x2
              //0x0d6     : 0xab98                               WR PCIE_PIPE_MUXR TEMP0_VAL_RW
  0x8CAC8C2B, //0x0d8     : 0x8c2b                               MV TEMP0_VAL_RW GCC_CESTA_GDSC_BRANCH_ENA_VOTE_ADDR
              //0x0da     : 0x8cac                               MV TEMP1_VAL_RW GDSC_SLEEP_ENA_PATTERN
  0x1C008D2C, //0x0dc     : 0x8d2c                               MV TEMP2_VAL_RW GDSC_SLEEP_ENA_PATTERN
              //0x0de     : 0x1c00                               CALL br_REG_RMW
  0xEA01EB0F, //0x0e0     : 0xeb0f                               MVI ALU_LSHFT_NUM_BITS 15
              //0x0e2     : 0xea01                               MVI ALU_LSHFT_OP_A 1
  0x81030000, //0x0e4     : 0x0000                               DELI 0ns
              //0x0e6     : 0x8103                               MV RD_CMP_DATA ALU_RESULT
  0xBC008183, //0x0e8     : 0x8183                               MV RD_CMP_MASK ALU_RESULT
              //0x0ea     : 0xbc00     br_POLL_GDSC_PWR_DN:      RD GCC_PCIE_CFG_GDSCR
  0x40072011, //0x0ec     : 0x2011                               BEQ rd_flag=0 br_POLL_GDSC_PWR_DN
              //0x0ee     : 0x4007                               SET0 lock_req
  0xB3C01000, //0x0f0     : 0x1000                               RETURN
              //0x0f2     : 0xb3c0     br_CBCR_WRITES:           RD CBCR_ADDR
  0x1C098F02, //0x0f4     : 0x8f02                               MV TEMP6_VAL_RW AHB_RD_DATA
              //0x0f6     : 0x1c09                               CALL br_MASK_VALUE
  0x821E829D, //0x0f8     : 0x829d                               MV ALU_ADD_OP_B TEMP5_VAL_RW
              //0x0fa     : 0x821e                               MV ALU_ADD_OP_A TEMP6_VAL_RW
  0xA3C30000, //0x0fc     : 0x0000                               DELI 0ns
              //0x0fe     : 0xa3c3                               WR CBCR_ADDR ALU_RESULT
  0xB3001000, //0x100     : 0x1000                               RETURN
              //0x102     : 0xb300     br_SRC_DIV_CHANGE:        RD RCG_CFG_ADDR
  0xFF1F8F02, //0x104     : 0x8f02                               MV TEMP6_VAL_RW AHB_RD_DATA
              //0x106     : 0xff1f                               MVI TEMP7_VAL_RW 0x1F
  0x829E1C09, //0x108     : 0x1c09                               CALL br_MASK_VALUE
              //0x10a     : 0x829e                               MV ALU_ADD_OP_B TEMP6_VAL_RW
  0x00008212, //0x10c     : 0x8212                               MV ALU_ADD_OP_A SRC_DIV
              //0x10e     : 0x0000                               DELI 0ns
  0xE101A303, //0x110     : 0xa303     br_WRITE_RCG_CFG:         WR RCG_CFG_ADDR ALU_RESULT
              //0x112     : 0xe101                               MVI RD_WR_DATA_PORT 0x1
  0xE200A341, //0x114     : 0xa341                               WR RCG_CMD_ADDR RD_WR_DATA_PORT
              //0x116     : 0xe200                               MVI RD_CMP_DATA 0x0
  0xB340E301, //0x118     : 0xe301                               MVI RD_CMP_MASK 0x1
              //0x11a     : 0xb340     br_POLL_RCG_DONE:         RD RCG_CMD_ADDR
  0x10002006, //0x11c     : 0x2006                               BEQ rd_flag=0 br_POLL_RCG_DONE
              //0x11e     : 0x1000                               RETURN
  0x8F02B300, //0x120     : 0xb300     br_UPDATE_RCG:            RD RCG_CFG_ADDR
              //0x122     : 0x8f02                               MV TEMP6_VAL_RW AHB_RD_DATA
  0xEA1FEB08, //0x124     : 0xeb08                               MVI ALU_LSHFT_NUM_BITS 0x8
              //0x126     : 0xea1f                               MVI ALU_LSHFT_OP_A 0x1F
  0x8F830000, //0x128     : 0x0000                               DELI 0ns
              //0x12a     : 0x8f83                               MV TEMP7_VAL_RW ALU_RESULT
  0x829E1C09, //0x12c     : 0x1c09                               CALL br_MASK_VALUE
              //0x12e     : 0x829e                               MV ALU_ADD_OP_B TEMP6_VAL_RW
  0x00008213, //0x130     : 0x8213                               MV ALU_ADD_OP_A SRC_VAL
              //0x132     : 0x0000                               DELI 0ns
  0x180BA303, //0x134     : 0xa303                               WR RCG_CFG_ADDR ALU_RESULT
              //0x136     : 0x180b                               JMP br_SRC_DIV_CHANGE
  0x861F869F, //0x138     : 0x869f     br_MASK_VALUE:            MV ALU_NAND_OP_B TEMP7_VAL_RW
              //0x13a     : 0x861f                               MV ALU_NAND_OP_A TEMP7_VAL_RW
  0x869E0000, //0x13c     : 0x0000                               DELI 0ns
              //0x13e     : 0x869e                               MV ALU_NAND_OP_B TEMP6_VAL_RW
  0x00008603, //0x140     : 0x8603                               MV ALU_NAND_OP_A ALU_RESULT
              //0x142     : 0x0000                               DELI 0ns
  0x86038683, //0x144     : 0x8683                               MV ALU_NAND_OP_B ALU_RESULT
              //0x146     : 0x8603                               MV ALU_NAND_OP_A ALU_RESULT
  0x8F030000, //0x148     : 0x0000                               DELI 0ns
              //0x14a     : 0x8f03                               MV TEMP6_VAL_RW ALU_RESULT
  0x50021000, //0x14c     : 0x1000                               RETURN
              //0x14e     : 0x5002     br_VOL_CHANGE:            SET1 vol_change_in_prgs
  0x70005003, //0x150     : 0x5003                               SET1 crmv_req
              //0x152     : 0x7000                               WAIT1 crmv_ack
  0x40024003, //0x154     : 0x4003                               SET0 crmv_req
              //0x156     : 0x4002                               SET0 vol_change_in_prgs
  0x50041000, //0x158     : 0x1000                               RETURN
              //0x15a     : 0x5004     br_RSC_SHUTDOWN_REQ:      SET1 crm_rsc_shutdown_req
  0x40047002, //0x15c     : 0x7002                               WAIT1 rsc_crm_shutdown_ack
              //0x15e     : 0x4004                               SET0 crm_rsc_shutdown_req
  0x50051000, //0x160     : 0x1000                               RETURN
              //0x162     : 0x5005     br_RSC_BRINGUP_REQ:       SET1 crm_rsc_bringup_req
  0x40057003, //0x164     : 0x7003                               WAIT1 rsc_crm_bringup_ack
              //0x166     : 0x4005                               SET0 crm_rsc_bringup_req
  0x10001000, //0x168     : 0x1000                               RETURN
              //0x16a     : 0x1000     br_RETURN:                RETURN
};

static const uint32_t aPCIECESTABranches[] =
{
  0x01E, //br_REG_RMW
  0x014, //br_PERF_UP
  0x00A, //br_PERF_DN
  0x14E, //br_VOL_CHANGE
  0x0F2, //br_CBCR_WRITES
  0x09E, //br_WRITE_PARF_CLKREQ_OVERRIDE
  0x11A, //br_POLL_RCG_DONE
  0x030, //br_M2_M0
  0x0B0, //br_M0_M2
  0x138, //br_MASK_VALUE
  0x110, //br_WRITE_RCG_CFG
  0x102, //br_SRC_DIV_CHANGE
  0x120, //br_UPDATE_RCG
  0x16A, //br_RETURN
  0x15A, //br_RSC_SHUTDOWN_REQ
  0x162, //br_RSC_BRINGUP_REQ
  0x05A, //br_POLL_GDSC_PWR_UP
  0x0EA, //br_POLL_GDSC_PWR_DN
  0x044, //br_POLL_CRMB_PT_IDLE
};

static const ClockCESTARegType aPCIECESTARegs[] =
{
  { .nAddr = HWIO_PHYSI(VCDm_SEQ_PWR_CTRL_OVRD_MASK, 0),                             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000010 },
  { .nAddr = HWIO_PHYSI(VCDm_SEQ_PWR_CTRL_OVRD_VAL, 0),                              .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000010 },
  { .nAddr = HWIO_PHYSI(VCDm_SEQ_PWR_CTRL_OVRD_MASK, 0),                             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI(VCDm_RCGR_CMD_ADDR, 0),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x0016B058 },
  { .nAddr = HWIO_PHYSI(VCDm_RCGR_CFG_ADDR, 0),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x0016B05C },
  { .nAddr = HWIO_PHYSI(VCDm_CLK_GATING_THRESHOLD, 0),                               .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 0, 0),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 0, 2),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 0, 3),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "cx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 0, 4),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI2(VCDm_PERF_LEVELp_CFG_RCGR_LUT, 0, 0),                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 1, 0),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 1, 2),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 1, 3),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "cx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 1, 4),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 1, 5),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(VCDm_PERF_LEVELp_CFG_RCGR_LUT, 0, 1),                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 2, 0),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 2, 2),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 2, 3),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "cx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 2, 4),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 2, 5),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(VCDm_PERF_LEVELp_CFG_RCGR_LUT, 0, 2),                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 3, 0),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 3, 2),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 3, 3),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "cx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 3, 4),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 3, 5),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(VCDm_PERF_LEVELp_CFG_RCGR_LUT, 0, 3),                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 4, 0),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 4, 2),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 4, 3),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "cx.lvl", RAIL_VOLTAGE_LEVEL_NOM } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 4, 4),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mx.lvl", RAIL_VOLTAGE_LEVEL_NOM } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 0, 4, 5),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(VCDm_PERF_LEVELp_CFG_RCGR_LUT, 0, 4),                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000605 },
  { .nAddr = HWIO_PHYSI(VCDm_NUM_CBC, 0),                                            .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000004 },
  { .nAddr = HWIO_PHYSI2(VCDm_CBCn_ADDR, 0, 0),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00179008 },
  { .nAddr = HWIO_PHYSI2(VCDm_CBCn_ADDR, 0, 1),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00179008 },
  { .nAddr = HWIO_PHYSI2(VCDm_CBCn_ADDR, 0, 2),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00179000 },
  { .nAddr = HWIO_PHYSI2(VCDm_CBCn_ADDR, 0, 3),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00179008 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 0),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x01C002B0 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 1),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x01C06654 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 2),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x01C06240 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 3),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000039 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 4),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFC6 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 5),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000006 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 6),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFF9 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 7),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x00400000 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 8),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFBFFFFF },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 9),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000004 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 10),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFB },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 11),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x0017914C },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 12),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 13),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x0016B004 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 14),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x0016B070 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 15),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x01FF1100 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 16),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x0016B008 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 0, 17),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x01D02644 },
  { .nAddr = HWIO_PHYSI(CRMC_ENm, 0),                                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(VCDm_SEQ_PWR_CTRL_OVRD_MASK, 1),                             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000010 },
  { .nAddr = HWIO_PHYSI(VCDm_SEQ_PWR_CTRL_OVRD_VAL, 1),                              .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000010 },
  { .nAddr = HWIO_PHYSI(VCDm_SEQ_PWR_CTRL_OVRD_MASK, 1),                             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI(VCDm_RCGR_CMD_ADDR, 1),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x0018D060 },
  { .nAddr = HWIO_PHYSI(VCDm_RCGR_CFG_ADDR, 1),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x0018D064 },
  { .nAddr = HWIO_PHYSI(VCDm_CLK_GATING_THRESHOLD, 1),                               .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 0, 0),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 0, 1),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 0, 2),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 0, 3),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "cx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 0, 4),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI2(VCDm_PERF_LEVELp_CFG_RCGR_LUT, 1, 0),                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 1, 0),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 1, 1),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 1, 2),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 1, 3),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "cx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 1, 4),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 1, 5),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(VCDm_PERF_LEVELp_CFG_RCGR_LUT, 1, 1),                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 2, 0),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 2, 1),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 2, 2),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 2, 3),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "cx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 2, 4),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 2, 5),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(VCDm_PERF_LEVELp_CFG_RCGR_LUT, 1, 2),                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 3, 0),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 3, 1),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 3, 2),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 3, 3),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "cx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 3, 4),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 3, 5),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(VCDm_PERF_LEVELp_CFG_RCGR_LUT, 1, 3),                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 4, 0),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 4, 1),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 4, 2),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 4, 3),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "cx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 4, 4),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mx.lvl", RAIL_VOLTAGE_LEVEL_LOW_SVS } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 4, 5),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(VCDm_PERF_LEVELp_CFG_RCGR_LUT, 1, 4),                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000605 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 5, 0),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 5, 1),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 5, 2),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 5, 3),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "cx.lvl", RAIL_VOLTAGE_LEVEL_NOM } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 5, 4),                   .eType = CESTA_REG_HLVL,            .Data.VLVL = { "mx.lvl", RAIL_VOLTAGE_LEVEL_NOM } },
  { .nAddr = HWIO_PHYSI3(VCDm_PERF_LEVELp_RAILr_VOL_LUT, 1, 5, 5),                   .eType = CESTA_REG_RAW,             .Data.nVal = 0xFFFFFFFF },
  { .nAddr = HWIO_PHYSI2(VCDm_PERF_LEVELp_CFG_RCGR_LUT, 1, 5),                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000605 },
  { .nAddr = HWIO_PHYSI(VCDm_NUM_CBC, 1),                                            .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000004 },
  { .nAddr = HWIO_PHYSI2(VCDm_CBCn_ADDR, 1, 0),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00179000 },
  { .nAddr = HWIO_PHYSI2(VCDm_CBCn_ADDR, 1, 1),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00179000 },
  { .nAddr = HWIO_PHYSI2(VCDm_CBCn_ADDR, 1, 2),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00179000 },
  { .nAddr = HWIO_PHYSI2(VCDm_CBCn_ADDR, 1, 3),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00179000 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 0),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x01C082B0 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 1),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x01C0F450 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 2),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x01C0F240 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 3),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x67000000 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 4),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x98FFFFFF },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 5),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x18000000 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 6),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0xE7FFFFFF },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 7),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x00800000 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 8),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0xFF7FFFFF },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 9),                                       .eType = CESTA_REG_RAW,             .Data.nVal = 0x10000000 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 10),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0xEFFFFFFF },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 11),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x0017914C },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 12),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000002 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 13),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x0018D004 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 14),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x0018D078 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 15),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x01FF1114 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 16),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x0018D008 },
  { .nAddr = HWIO_PHYSI2(SEQ_VCDm_GPRr, 1, 17),                                      .eType = CESTA_REG_RAW,             .Data.nVal = 0x01D02694 },
  { .nAddr = HWIO_PHYSI(CRMC_ENm, 1),                                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(VCDm_SEQ_PWR_CTRL_OVRD_MASK, 2),                             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000010 },
  { .nAddr = HWIO_PHYSI(VCDm_SEQ_PWR_CTRL_OVRD_VAL, 2),                              .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000010 },
  { .nAddr = HWIO_PHYSI(VCDm_SEQ_PWR_CTRL_OVRD_MASK, 2),                             .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000000 },
  { .nAddr = HWIO_PHYSI2(RAILr_TCS_CMDn_ADDR, 0, 0),                                 .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "ldoi1", 4 } },
  { .nAddr = HWIO_PHYSI2(RAILr_TCS_CMDn_ADDR, 1, 0),                                 .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "ldoe3", 4 } },
  { .nAddr = HWIO_PHYSI2(RAILr_TCS_CMDn_ADDR, 2, 0),                                 .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "ldoi3", 4 } },
  { .nAddr = HWIO_PHYSI2(RAILr_TCS_CMDn_ADDR, 3, 0),                                 .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "cx.lvl", 0 } },
  { .nAddr = HWIO_PHYSI2(RAILr_TCS_CMDn_ADDR, 4, 0),                                 .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "mx.lvl", 0 } },
  { .nAddr = HWIO_PHYSI2(RAILr_TCS_CMDn_ADDR, 5, 0),                                 .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "xo.lvl", 0 } },
  { .nAddr = HWIO_PHYSI(RAILr_EN, 0),                                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(RAILr_EN, 1),                                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(RAILr_EN, 2),                                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(RAILr_EN, 3),                                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(RAILr_EN, 4),                                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI(RAILr_EN, 5),                                                .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
  { .nAddr = HWIO_PHYSI2(HW_CLIENTm_NDn_TCS_CMD_ADDR, 0, 0),                         .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "MC0", 0 } },
  { .nAddr = HWIO_PHYSI2(HW_CLIENTm_NDn_TCS_CMD_ADDR, 0, 1),                         .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "SH0", 0 } },
  { .nAddr = HWIO_PHYSI2(HW_CLIENTm_NDn_TCS_CMD_ADDR, 0, 2),                         .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "SH1", 0 } },
  { .nAddr = HWIO_PHYSI2(HW_CLIENTm_NDn_TCS_CMD_ADDR, 0, 3),                         .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "SN4", 0 } },
  { .nAddr = HWIO_PHYSI2(HW_CLIENTm_NDn_TCS_CMD_ADDR, 0, 4),                         .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "IP0", 0 } },
  { .nAddr = HWIO_PHYSI2(HW_CLIENTm_NDn_TCS_CMD_ADDR, 0, 5),                         .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "ACV", 0 } },
  { .nAddr = HWIO_PHYSI2(HW_CLIENTm_NDn_TCS_CMD_ADDR, 1, 0),                         .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "MC0", 0 } },
  { .nAddr = HWIO_PHYSI2(HW_CLIENTm_NDn_TCS_CMD_ADDR, 1, 1),                         .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "SH0", 0 } },
  { .nAddr = HWIO_PHYSI2(HW_CLIENTm_NDn_TCS_CMD_ADDR, 1, 2),                         .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "SH1", 0 } },
  { .nAddr = HWIO_PHYSI2(HW_CLIENTm_NDn_TCS_CMD_ADDR, 1, 3),                         .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "SN4", 0 } },
  { .nAddr = HWIO_PHYSI2(HW_CLIENTm_NDn_TCS_CMD_ADDR, 1, 4),                         .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "IP0", 0 } },
  { .nAddr = HWIO_PHYSI2(HW_CLIENTm_NDn_TCS_CMD_ADDR, 1, 5),                         .eType = CESTA_REG_CMD_DB_ADDR,     .Data.CmdDB = { "ACV", 0 } },
  { .nAddr = HWIO_PHYS(CRM_ENABLE),                                                  .eType = CESTA_REG_RAW,             .Data.nVal = 0x00000001 },
};

static ClockCESTA PCIECESTA =
{
  .szName         = "pcie_cesta",
  .nCRMCBaseAddr  = CRMC_REG_BASE,
  .nSequenceAddr  = HWIO_PHYSI(SEQ_MEMs, 0),
  .nBranchAddr    = HWIO_PHYSI(SEQ_BR_ADDRn, 0),
  .aSequence      = aPCIECESTASequence,
  .nNumSequence   = SIZEOF_ARRAY(aPCIECESTASequence),
  .aBranches      = aPCIECESTABranches,
  .nNumBranches   = SIZEOF_ARRAY(aPCIECESTABranches),
  .aRegVals       = aPCIECESTARegs,
  .nNumRegVals    = SIZEOF_ARRAY(aPCIECESTARegs),
  .nMaxPerfOL     = 8,
  .nFlags         = 0x0,
};

/*=========================================================================
      CESTA
==========================================================================*/

static const ClockCESTA *aCESTA[] =
{
  [CESTA_IDX_CAM] = &CAMCESTA,
  [CESTA_IDX_PCIE] = &PCIECESTA,
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
  .aCESTA            = aCESTA,
  .nNumCESTA         = SIZEOF_ARRAY(aCESTA),
};

