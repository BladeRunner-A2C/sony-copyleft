/*==============================================================================

FILE:      icbcfg_data.c

DESCRIPTION: This file implements the ICB Configuration driver.

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A

Edit History

$Header: $
$DateTime: 2022/04/04 14:42:21 $
$Author: seansw $
$Change: 36371393 $

When        Who    What, where, why
----------  ---    -----------------------------------------------------------
2023/05/04  sds    LLCC HSR v26
2023/04/23  sds    GEMNOC HSR v12
2023/03/08  sds    QM v8
2023/02/15  as     arcg settings
2023/01/09  sds    CPU SCID updates
2022/09/12  sds    LLCC v17
2022/07/20  sds    GEMNOC and DC_NOC ARCG
2022/04/05  sds    Created

                Copyright (c) 2022-2023 Qualcomm Technologies, Inc.
                             All Rights Reserved.
                          QUALCOMM Proprietary/GTDR
==============================================================================*/
#include "icbcfg_hwio.h"
#include "icbcfg_hwio_target.h"
#include "../../../../../Library/ICBLib/icbcfgi.h"

/*---------------------------------------------------------------------------*/
/*          Macro and constant definitions                                   */
/*---------------------------------------------------------------------------*/
//#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))

/*============================================================================
                        DEVICE CONFIG PROPERTY DATA
============================================================================*/

/*---------------------------------------------------------------------------*/
/*          Properties data for device ID  = "icbcfg/boot"                   */
/*---------------------------------------------------------------------------*/

/* ICBcfg Boot Configuration Data*/

/*---------------------------------------------------------------------------*/
/* MILOS v1                                                                 */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* EarlyInit Config Segments                                                 */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* ARCG Config Segment                                                       */
/*---------------------------------------------------------------------------*/
icbcfg_data_type icbcfg_arcg_cfg_data_milos_v1[] =
{ 

  ICBCFG_DEFAULT(),

};

icbcfg_prop_seg_type icbcfg_arcg_cfg_seg_milos_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_arcg_cfg_data_milos_v1),
  /* Pointer to config data array */
  icbcfg_arcg_cfg_data_milos_v1
};

/*---------------------------------------------------------------------------*/
/* EarlyInit Config Segment list                                             */
/*---------------------------------------------------------------------------*/
icbcfg_prop_seg_type *icbcfg_early_init_segs_milos_v1[] =
{
  &icbcfg_arcg_cfg_seg_milos_v1,
};

icbcfg_prop_type icbcfg_early_prop_milos_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_early_init_segs_milos_v1),
  /* Pointer to config data array */
  icbcfg_early_init_segs_milos_v1
};



/*---------------------------------------------------------------------------*/
/* Init Config Segments                                                      */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* QM Config Segment                                                         */
/*---------------------------------------------------------------------------*/
icbcfg_data_type icbcfg_qm_cfg_data_milos_v1[] =
{
  ICBCFG_DEFAULT(),

};

icbcfg_prop_seg_type icbcfg_qm_cfg_seg_milos_v1 = 
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_qm_cfg_data_milos_v1),
  /* Pointer to config data array */ 
  icbcfg_qm_cfg_data_milos_v1                                    
};

/*---------------------------------------------------------------------------*/
/* GEMNOC Early Config Segment                                               */
/*---------------------------------------------------------------------------*/
icbcfg_data_type icbcfg_gemnoc_early_cfg_data_milos_v1[] =
{

  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_CNOC_SF_CLK_FORCECLKON_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_GEMNOC_CFG_CLK_FORCECLKON_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_GEMNOC_CLK_FORCECLKON_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_GPU_CLK_FORCECLKON_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_LPASS_CLK_FORCECLKON_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MNOC_HF_CLK_FORCECLKON_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MNOC_SF_CLK_FORCECLKON_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MODEM_CLK_FORCECLKON_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_NSP_NOC_CLK_FORCECLKON_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_PCIE_SF_CLK_FORCECLKON_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_SNOC_SF_CLK_FORCECLKON_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_SYS_TCU_CLK_FORCECLKON_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_WLAN_Q6_CLK_FORCECLKON_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MDSP_CLK_FORCECLKON_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_SNOC_GC_CLK_FORCECLKON_LOW, 0x1),

  ICBCFG_HWIO_DW(GEM_NOC_CNOC_SF_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0x3FF),
  ICBCFG_HWIO_DW(GEM_NOC_GEMNOC_CFG_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0x3FF),
  ICBCFG_HWIO_DW(GEM_NOC_GEMNOC_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0x3FF),
  ICBCFG_HWIO_DW(GEM_NOC_GPU_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0x3FF),
  ICBCFG_HWIO_DW(GEM_NOC_LPASS_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0x3FF),
  ICBCFG_HWIO_DW(GEM_NOC_MNOC_HF_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0x3FF),
  ICBCFG_HWIO_DW(GEM_NOC_MNOC_SF_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0x3FF),
  ICBCFG_HWIO_DW(GEM_NOC_MODEM_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0x3FF),
  ICBCFG_HWIO_DW(GEM_NOC_NSP_NOC_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0x3FF),
  ICBCFG_HWIO_DW(GEM_NOC_PCIE_SF_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0x3FF),
  ICBCFG_HWIO_DW(GEM_NOC_SNOC_SF_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0x3FF),
  ICBCFG_HWIO_DW(GEM_NOC_SYS_TCU_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0x3FF),
  ICBCFG_HWIO_DW(GEM_NOC_WLAN_Q6_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0x3FF),
  ICBCFG_HWIO_DW(GEM_NOC_MDSP_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0x3FF),
  ICBCFG_HWIO_DW(GEM_NOC_SNOC_GC_CLK_RCGCONTROLLER_HYSTERESIS_LOW, 0x3FF),


  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_CNOC_SF_CLK_ENABLE_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_GEMNOC_CFG_CLK_ACTIVEDIS_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_GEMNOC_CFG_CLK_ENABLE_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_GEMNOC_CLK_ENABLE_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_GPU_CLK_ENABLE_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_LPASS_CLK_ENABLE_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MNOC_HF_CLK_ENABLE_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MNOC_SF_CLK_ENABLE_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MODEM_CLK_ENABLE_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_NSP_NOC_CLK_ENABLE_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_PCIE_SF_CLK_ENABLE_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_SNOC_SF_CLK_ENABLE_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_SYS_TCU_CLK_ENABLE_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_WLAN_Q6_CLK_ENABLE_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MDSP_CLK_ENABLE_LOW, 0x1),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_SNOC_GC_CLK_ENABLE_LOW, 0x1),


  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_CNOC_SF_CLK_FORCECLKON_LOW, 0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_GEMNOC_CFG_CLK_FORCECLKON_LOW, 0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_GEMNOC_CLK_FORCECLKON_LOW, 0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_GPU_CLK_FORCECLKON_LOW, 0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_LPASS_CLK_FORCECLKON_LOW, 0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MNOC_HF_CLK_FORCECLKON_LOW, 0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MNOC_SF_CLK_FORCECLKON_LOW, 0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MODEM_CLK_FORCECLKON_LOW, 0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_NSP_NOC_CLK_FORCECLKON_LOW, 0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_PCIE_SF_CLK_FORCECLKON_LOW, 0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_SNOC_SF_CLK_FORCECLKON_LOW, 0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_SYS_TCU_CLK_FORCECLKON_LOW, 0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_WLAN_Q6_CLK_FORCECLKON_LOW, 0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_MDSP_CLK_FORCECLKON_LOW, 0x0),
  ICBCFG_HWIO_DW(GEM_NOC_FORCE_CLKON_CSRUNIT_RCG_SNOC_GC_CLK_FORCECLKON_LOW, 0x0),

  /* Other HSR */
  ICBCFG_HWIO_DW(GEM_NOC_QCIDIRECTORY_EVEN_SNOOPFILTER_QNS_MC0_CTL_MAINCTL_LOW, 0x00000004),
  ICBCFG_HWIO_DW(GEM_NOC_QCIDIRECTORY_ODD_SNOOPFILTER_QNS_MC1_CTL_MAINCTL_LOW, 0x00000004),

};

icbcfg_prop_seg_type icbcfg_gemnoc_early_cfg_seg_milos_v1 = 
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_gemnoc_early_cfg_data_milos_v1),
  /* Pointer to config data array */ 
  icbcfg_gemnoc_early_cfg_data_milos_v1                                    
};

/*---------------------------------------------------------------------------*/
/* Init Config Segment list                                                  */
/*---------------------------------------------------------------------------*/
icbcfg_prop_seg_type *icbcfg_boot_segs_milos_v1[] =
{
  &icbcfg_qm_cfg_seg_milos_v1,
  &icbcfg_gemnoc_early_cfg_seg_milos_v1,
};

icbcfg_prop_type icbcfg_boot_prop_milos_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_boot_segs_milos_v1),
  /* Pointer to config data array */
  icbcfg_boot_segs_milos_v1
};

/*---------------------------------------------------------------------------*/
/* PostInit Config Segments                                                  */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* GEMNOC Post Config Segment                                                */
/*---------------------------------------------------------------------------*/
icbcfg_data_type icbcfg_gemnoc_cfg_data_milos_v1[] =
{
   
   ICBCFG_HWIOF_DW(GEM_NOC_QNM_GPU0_QOSGEN_MAINCTL_LOW, SHAPEREN, 0x1),
   ICBCFG_HWIO_DW(GEM_NOC_QNM_GPU0_QOSGEN_SHAPING_LOW, 0x70707070),
   ICBCFG_HWIO_DW(GEM_NOC_QNM_GPU0_QOSGEN_SHAPING_HIGH, 0x70707070),
   
   ICBCFG_HWIOF_DW(GEM_NOC_QNM_GPU1_QOSGEN_MAINCTL_LOW, SHAPEREN, 0x1),
   ICBCFG_HWIO_DW(GEM_NOC_QNM_GPU1_QOSGEN_SHAPING_LOW, 0x70707070),
   ICBCFG_HWIO_DW(GEM_NOC_QNM_GPU1_QOSGEN_SHAPING_HIGH, 0x70707070),
};

icbcfg_prop_seg_type icbcfg_gemnoc_cfg_seg_milos_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_gemnoc_cfg_data_milos_v1),
  /* Pointer to config data array */
  icbcfg_gemnoc_cfg_data_milos_v1
};

/*---------------------------------------------------------------------------*/
/* LLCC Config Segment                                                       */
/*---------------------------------------------------------------------------*/
icbcfg_data_type icbcfg_llcc_cfg_data_milos_v1[] =
{
  ICBCFG_HWIO_DW(MC_BROADCAST_ANDMC_COMMON_ISU_BEAC_HMSSSELFAUTH_LOCK, 0x1),
  ICBCFG_HWIO_DW(MC_BROADCAST_ANDMC_COMMON_ISU_BEAC_HPROTNS_LOCK,      0x1),
  ICBCFG_HWIO_DW(MC_BROADCAST_ANDMC_COMMON_ISU_BEAC_HSECUREPROC_LOCK,  0x1),
  ICBCFG_HWIO_DW(MC_BROADCAST_ANDMC_COMMON_ISU_BEAC_HTMEROM_LOCK,  0x1),
  ICBCFG_HWIO_DW(MC_BROADCAST_ANDMC_COMMON_ISU_BEAC_HTMEFW_LOCK,  0x1),

  ICBCFG_HWIO_DW(MC_BROADCAST_ORMC_COMMON_ISU_LOAD_CONFIG,  0x1),
};

icbcfg_prop_seg_type icbcfg_llcc_cfg_seg_milos_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_llcc_cfg_data_milos_v1),
  /* Pointer to config data array */
  icbcfg_llcc_cfg_data_milos_v1
};

/*---------------------------------------------------------------------------*/
/* LLCC Config Segment                                                       */
/*---------------------------------------------------------------------------*/
icbcfg_data_type icbcfg_wa_data_milos_v1[] =
{
  /* CNOC HSR settings */
  ICBCFG_HWIO_DW(CNOC_MAIN_CSRUNIT_MAIN_MEMTYPE_CSRUNIT_QHB_MEMTYPE_QHS_AOSS_LOW, 0x00000002),
  ICBCFG_HWIO_DW(CNOC_MAIN_CSRUNIT_MAIN_MEMTYPE_CSRUNIT_QHB_MEMTYPE_QHS_IPA_LOW, 0x00000002),
  ICBCFG_HWIO_DW(CNOC_MAIN_CSRUNIT_MAIN_MEMTYPE_CSRUNIT_QHB_MEMTYPE_QHS_IPC_ROUTER_LOW, 0x00000002),

};

icbcfg_prop_seg_type icbcfg_wa_seg_milos_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_wa_data_milos_v1),
  /* Pointer to config data array */
  icbcfg_wa_data_milos_v1
};

/*---------------------------------------------------------------------------*/
/* PostInit Config Segment list                                              */
/*---------------------------------------------------------------------------*/
icbcfg_prop_seg_type *icbcfg_post_boot_segs_milos_v1[] =
{
  &icbcfg_gemnoc_cfg_seg_milos_v1,
  &icbcfg_llcc_cfg_seg_milos_v1,
  &icbcfg_wa_seg_milos_v1,
};

icbcfg_prop_type icbcfg_post_prop_milos_v1 =
{
  /* Length of the config  data array */
  ARRAY_SIZE(icbcfg_post_boot_segs_milos_v1),
  /* Pointer to config data array */
  icbcfg_post_boot_segs_milos_v1
};


icbcfg_mem_region_type map_ddr_regions_milos_v1[] =
{
  { 0x0080000000ULL, 0x0100000000ULL },
  { 0x0880000000ULL, 0x1000000000ULL },
};

/* Translation block base addresses. */
uint8 *trans_bases_milos_v1[] =
{
  (uint8 *)HWIO_ADDR(MC0_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG),
  (uint8 *)HWIO_ADDR(MC1_MC_COMMON_ISU_ADDR_TRANSLATOR_CFG),
};

/*---------------------------------------------------------------------------*/
/* TARGET DEFINITIONS                                                        */
/*---------------------------------------------------------------------------*/
icbcfg_device_config_type milos_v1 =
{
  /* Chip version information for this device data. */
  CHIPINFO_FAMILY_MILOS,      /**< Chip family */
  false,                      /**< Exact match for version? */
  0,                          /**< Chip version */

  /* Device information. */
  ARRAY_SIZE(map_ddr_regions_milos_v1), /**< Number of regions in the DDR map */
  map_ddr_regions_milos_v1,             /**< Array of mappable DDR regions */
  6,                                     /**< Number of mapping segments. */
  2,                                     /**< Number of channels. */
  36,                                    /**< Address width in bits. */
  ICBCFG_ADDR_TRANS_MC,                /**< Address translator hardware type. */
  trans_bases_milos_v1,                 /**< Translation block base addresses. */

  /* Prop lists. */
  .prop_data = &icbcfg_boot_prop_milos_v1,           /**< Init time prop list. */
  .post_prop_data = &icbcfg_post_prop_milos_v1,           /**< Post-init time prop list. */
  .early_prop_data =  &icbcfg_early_prop_milos_v1,          /**< Early init pop list. */
};

/*---------------------------------------------------------------------------*/
/* TARGET LIST                                                               */
/*---------------------------------------------------------------------------*/
icbcfg_device_config_type *configs_milos[] =
{
  &milos_v1,
};

/*---------------------------------------------------------------------------*/
/* EXPORTED TARGET DEFINITION                                                */
/*---------------------------------------------------------------------------*/
icbcfg_info_type icbcfg_info =
{
  ARRAY_SIZE(configs_milos),
  configs_milos,
};
