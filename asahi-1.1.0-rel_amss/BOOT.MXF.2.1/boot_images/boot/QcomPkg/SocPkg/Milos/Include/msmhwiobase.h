#ifndef __MSMHWIOBASE_H__
#define __MSMHWIOBASE_H__
/*
===========================================================================
*/
/**
    @file msmhwiobase.h
    @brief Auto-generated HWIO base include file.
*/
/*
    ===========================================================================
  
  Copyright (c) 2024 Qualcomm Technologies, Inc. All rights reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  
  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.
  
  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies Incorporated and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies Incorporated.
  
    ===========================================================================

    $Header: $
    $DateTime: $
    $Author: $

    ===========================================================================
*/

/*----------------------------------------------------------------------------
 * BASE: LPASS_VA_LPM_SIZE
 *--------------------------------------------------------------------------*/

#define LPASS_VA_LPM_SIZE_BASE                                      0x00003000
#define LPASS_VA_LPM_SIZE_BASE_SIZE                                 0x00000000
#define LPASS_VA_LPM_SIZE_BASE_PHYS                                 0x00003000

/*----------------------------------------------------------------------------
 * BASE: LPASS_LPM_SIZE
 *--------------------------------------------------------------------------*/

#define LPASS_LPM_SIZE_BASE                                         0x00008000
#define LPASS_LPM_SIZE_BASE_SIZE                                    0x00000000
#define LPASS_LPM_SIZE_BASE_PHYS                                    0x00008000

/*----------------------------------------------------------------------------
 * BASE: SSC_RAM_SIZE
 *--------------------------------------------------------------------------*/

#define SSC_RAM_SIZE_BASE                                           0x0000a000
#define SSC_RAM_SIZE_BASE_SIZE                                      0x00000000
#define SSC_RAM_SIZE_BASE_PHYS                                      0x0000a000

/*----------------------------------------------------------------------------
 * BASE: LPASS_AUDIO_LPM_SIZE
 *--------------------------------------------------------------------------*/

#define LPASS_AUDIO_LPM_SIZE_BASE                                   0x0000c000
#define LPASS_AUDIO_LPM_SIZE_BASE_SIZE                              0x00000000
#define LPASS_AUDIO_LPM_SIZE_BASE_PHYS                              0x0000c000

/*----------------------------------------------------------------------------
 * BASE: SYSTEM_IMEM_SIZE
 *--------------------------------------------------------------------------*/

#define SYSTEM_IMEM_SIZE_BASE                                       0x0002c000
#define SYSTEM_IMEM_SIZE_BASE_SIZE                                  0x00000000
#define SYSTEM_IMEM_SIZE_BASE_PHYS                                  0x0002c000

/*----------------------------------------------------------------------------
 * BASE: AOP_SS_MSG_RAM_DRV14
 *--------------------------------------------------------------------------*/

#define AOP_SS_MSG_RAM_DRV14_BASE                                   0x000e0000
#define AOP_SS_MSG_RAM_DRV14_BASE_SIZE                              0x00000000
#define AOP_SS_MSG_RAM_DRV14_BASE_PHYS                              0x000e0000

/*----------------------------------------------------------------------------
 * BASE: AOP_SS_MSG_RAM_DRV15
 *--------------------------------------------------------------------------*/

#define AOP_SS_MSG_RAM_DRV15_BASE                                   0x000f0000
#define AOP_SS_MSG_RAM_DRV15_BASE_SIZE                              0x00000000
#define AOP_SS_MSG_RAM_DRV15_BASE_PHYS                              0x000f0000

/*----------------------------------------------------------------------------
 * BASE: CLK_CTL
 *--------------------------------------------------------------------------*/

#define CLK_CTL_BASE                                                0x00100000
#define CLK_CTL_BASE_SIZE                                           0x00200000
#define CLK_CTL_BASE_PHYS                                           0x00100000

/*----------------------------------------------------------------------------
 * BASE: BOOT_ROM
 *--------------------------------------------------------------------------*/

#define BOOT_ROM_BASE                                               0x00300000
#define BOOT_ROM_BASE_SIZE                                          0x00100000
#define BOOT_ROM_BASE_PHYS                                          0x00300000

/*----------------------------------------------------------------------------
 * BASE: MSS__QDSP6_TCM_SIZE
 *--------------------------------------------------------------------------*/

#define MSS__QDSP6_TCM_SIZE_BASE                                    0x00400000
#define MSS__QDSP6_TCM_SIZE_BASE_SIZE                               0x00000000
#define MSS__QDSP6_TCM_SIZE_BASE_PHYS                               0x00400000

/*----------------------------------------------------------------------------
 * BASE: LPASS_TCM_SIZE
 *--------------------------------------------------------------------------*/

#define LPASS_TCM_SIZE_BASE                                         0x00400000
#define LPASS_TCM_SIZE_BASE_SIZE                                    0x00000000
#define LPASS_TCM_SIZE_BASE_PHYS                                    0x00400000

/*----------------------------------------------------------------------------
 * BASE: WPSS_TCM_SIZE
 *--------------------------------------------------------------------------*/

#define WPSS_TCM_SIZE_BASE                                          0x00400000
#define WPSS_TCM_SIZE_BASE_SIZE                                     0x00000000
#define WPSS_TCM_SIZE_BASE_PHYS                                     0x00400000

/*----------------------------------------------------------------------------
 * BASE: IPC_ROUTER_TOP
 *--------------------------------------------------------------------------*/

#define IPC_ROUTER_TOP_BASE                                         0x00400000
#define IPC_ROUTER_TOP_BASE_SIZE                                    0x00200000
#define IPC_ROUTER_TOP_BASE_PHYS                                    0x00400000

/*----------------------------------------------------------------------------
 * BASE: RAMBLUR_PIMEM
 *--------------------------------------------------------------------------*/

#define RAMBLUR_PIMEM_BASE                                          0x00610000
#define RAMBLUR_PIMEM_BASE_SIZE                                     0x00008000
#define RAMBLUR_PIMEM_BASE_PHYS                                     0x00610000

/*----------------------------------------------------------------------------
 * BASE: OCIMEM_WRAPPER_CSR
 *--------------------------------------------------------------------------*/

#define OCIMEM_WRAPPER_CSR_BASE                                     0x00618000
#define OCIMEM_WRAPPER_CSR_BASE_SIZE                                0x00006000
#define OCIMEM_WRAPPER_CSR_BASE_PHYS                                0x00618000

/*----------------------------------------------------------------------------
 * BASE: CX_CPR3
 *--------------------------------------------------------------------------*/

#define CX_CPR3_BASE                                                0x00628000
#define CX_CPR3_BASE_SIZE                                           0x00004000
#define CX_CPR3_BASE_PHYS                                           0x00628000

/*----------------------------------------------------------------------------
 * BASE: MX_CPR3
 *--------------------------------------------------------------------------*/

#define MX_CPR3_BASE                                                0x00638000
#define MX_CPR3_BASE_SIZE                                           0x00004000
#define MX_CPR3_BASE_PHYS                                           0x00638000

/*----------------------------------------------------------------------------
 * BASE: RDPM_CXRDPM_TOP
 *--------------------------------------------------------------------------*/

#define RDPM_CXRDPM_TOP_BASE                                        0x00640000
#define RDPM_CXRDPM_TOP_BASE_SIZE                                   0x00010000
#define RDPM_CXRDPM_TOP_BASE_PHYS                                   0x00640000

/*----------------------------------------------------------------------------
 * BASE: RDPM_MXC_RDPM_TOP
 *--------------------------------------------------------------------------*/

#define RDPM_MXC_RDPM_TOP_BASE                                      0x00650000
#define RDPM_MXC_RDPM_TOP_BASE_SIZE                                 0x00010000
#define RDPM_MXC_RDPM_TOP_BASE_PHYS                                 0x00650000

/*----------------------------------------------------------------------------
 * BASE: RDPM_MXA_RDPM_TOP
 *--------------------------------------------------------------------------*/

#define RDPM_MXA_RDPM_TOP_BASE                                      0x00660000
#define RDPM_MXA_RDPM_TOP_BASE_SIZE                                 0x00010000
#define RDPM_MXA_RDPM_TOP_BASE_PHYS                                 0x00660000

/*----------------------------------------------------------------------------
 * BASE: QTB_NOC_LPASS
 *--------------------------------------------------------------------------*/

#define QTB_NOC_LPASS_BASE                                          0x007b0000
#define QTB_NOC_LPASS_BASE_SIZE                                     0x0000f080
#define QTB_NOC_LPASS_BASE_PHYS                                     0x007b0000

/*----------------------------------------------------------------------------
 * BASE: QTB_NOC_NSP
 *--------------------------------------------------------------------------*/

#define QTB_NOC_NSP_BASE                                            0x007d0000
#define QTB_NOC_NSP_BASE_SIZE                                       0x00010080
#define QTB_NOC_NSP_BASE_PHYS                                       0x007d0000

/*----------------------------------------------------------------------------
 * BASE: QUPV3_1_QUPV3_ID_1
 *--------------------------------------------------------------------------*/

#define QUPV3_1_QUPV3_ID_1_BASE                                     0x00800000
#define QUPV3_1_QUPV3_ID_1_BASE_SIZE                                0x00100000
#define QUPV3_1_QUPV3_ID_1_BASE_PHYS                                0x00800000

/*----------------------------------------------------------------------------
 * BASE: QUPV3_0_QUPV3_ID_1
 *--------------------------------------------------------------------------*/

#define QUPV3_0_QUPV3_ID_1_BASE                                     0x00a00000
#define QUPV3_0_QUPV3_ID_1_BASE_SIZE                                0x00100000
#define QUPV3_0_QUPV3_ID_1_BASE_PHYS                                0x00a00000

/*----------------------------------------------------------------------------
 * BASE: AHB2PHY_EAST
 *--------------------------------------------------------------------------*/

#define AHB2PHY_EAST_BASE                                           0x00ff0000
#define AHB2PHY_EAST_BASE_SIZE                                      0x00004000
#define AHB2PHY_EAST_BASE_PHYS                                      0x00ff0000

/*----------------------------------------------------------------------------
 * BASE: SNOC_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define SNOC_THROTTLE_THROTTLE_WRAPPER_1_BASE                       0x00ff4000
#define SNOC_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE                  0x00001000
#define SNOC_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS                  0x00ff4000

/*----------------------------------------------------------------------------
 * BASE: PCIE_THROTTLE_THROTTLE_BWMON_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define PCIE_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE                 0x00ff5000
#define PCIE_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE_SIZE            0x00001000
#define PCIE_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE_PHYS            0x00ff5000

/*----------------------------------------------------------------------------
 * BASE: WLAN_Q6_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define WLAN_Q6_THROTTLE_THROTTLE_WRAPPER_1_BASE                    0x00ffc000
#define WLAN_Q6_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE               0x00001000
#define WLAN_Q6_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS               0x00ffc000

/*----------------------------------------------------------------------------
 * BASE: MODEM_DEMBACK_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define MODEM_DEMBACK_THROTTLE_THROTTLE_WRAPPER_1_BASE              0x00ffd000
#define MODEM_DEMBACK_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE         0x00001000
#define MODEM_DEMBACK_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS         0x00ffd000

/*----------------------------------------------------------------------------
 * BASE: MODEM_DSP_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define MODEM_DSP_THROTTLE_THROTTLE_WRAPPER_1_BASE                  0x00ffe000
#define MODEM_DSP_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE             0x00001000
#define MODEM_DSP_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS             0x00ffe000

/*----------------------------------------------------------------------------
 * BASE: QDSS_STM_SIZE
 *--------------------------------------------------------------------------*/

#define QDSS_STM_SIZE_BASE                                          0x01000000
#define QDSS_STM_SIZE_BASE_SIZE                                     0x00000000
#define QDSS_STM_SIZE_BASE_PHYS                                     0x01000000

/*----------------------------------------------------------------------------
 * BASE: TITAN_THROTTLE_RT_THROTTLE_WRAPPER_2
 *--------------------------------------------------------------------------*/

#define TITAN_THROTTLE_RT_THROTTLE_WRAPPER_2_BASE                   0x01000000
#define TITAN_THROTTLE_RT_THROTTLE_WRAPPER_2_BASE_SIZE              0x00001000
#define TITAN_THROTTLE_RT_THROTTLE_WRAPPER_2_BASE_PHYS              0x01000000

/*----------------------------------------------------------------------------
 * BASE: ANOC2_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define ANOC2_THROTTLE_THROTTLE_WRAPPER_1_BASE                      0x01001000
#define ANOC2_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE                 0x00001000
#define ANOC2_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS                 0x01001000

/*----------------------------------------------------------------------------
 * BASE: VIDEO_THROTTLE_VCODEC_THROTTLE_BWMON_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define VIDEO_THROTTLE_VCODEC_THROTTLE_BWMON_WRAPPER_1_BASE         0x01002000
#define VIDEO_THROTTLE_VCODEC_THROTTLE_BWMON_WRAPPER_1_BASE_SIZE    0x00001000
#define VIDEO_THROTTLE_VCODEC_THROTTLE_BWMON_WRAPPER_1_BASE_PHYS    0x01002000

/*----------------------------------------------------------------------------
 * BASE: TITAN_THROTTLE_NRT_THROTTLE_WRAPPER_3
 *--------------------------------------------------------------------------*/

#define TITAN_THROTTLE_NRT_THROTTLE_WRAPPER_3_BASE                  0x01003000
#define TITAN_THROTTLE_NRT_THROTTLE_WRAPPER_3_BASE_SIZE             0x00001000
#define TITAN_THROTTLE_NRT_THROTTLE_WRAPPER_3_BASE_PHYS             0x01003000

/*----------------------------------------------------------------------------
 * BASE: ANOC1_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define ANOC1_THROTTLE_THROTTLE_WRAPPER_1_BASE                      0x01005000
#define ANOC1_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE                 0x00001000
#define ANOC1_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS                 0x01005000

/*----------------------------------------------------------------------------
 * BASE: GPU_TCU_THROTTLE_THROTTLE_WRAPPER_AXI_1
 *--------------------------------------------------------------------------*/

#define GPU_TCU_THROTTLE_THROTTLE_WRAPPER_AXI_1_BASE                0x01040000
#define GPU_TCU_THROTTLE_THROTTLE_WRAPPER_AXI_1_BASE_SIZE           0x00001000
#define GPU_TCU_THROTTLE_THROTTLE_WRAPPER_AXI_1_BASE_PHYS           0x01040000

/*----------------------------------------------------------------------------
 * BASE: LPASS_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define LPASS_THROTTLE_THROTTLE_WRAPPER_1_BASE                      0x01041000
#define LPASS_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE                 0x00001000
#define LPASS_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS                 0x01041000

/*----------------------------------------------------------------------------
 * BASE: QM
 *--------------------------------------------------------------------------*/

#define QM_BASE                                                     0x010b8000
#define QM_BASE_SIZE                                                0x00004000
#define QM_BASE_PHYS                                                0x010b8000

/*----------------------------------------------------------------------------
 * BASE: QM_MPU_CFG_QM_MPU_WRAPPER
 *--------------------------------------------------------------------------*/

#define QM_MPU_CFG_QM_MPU_WRAPPER_BASE                              0x010bc000
#define QM_MPU_CFG_QM_MPU_WRAPPER_BASE_SIZE                         0x00004000
#define QM_MPU_CFG_QM_MPU_WRAPPER_BASE_PHYS                         0x010bc000

/*----------------------------------------------------------------------------
 * BASE: RNG_SOC_TOP
 *--------------------------------------------------------------------------*/

#define RNG_SOC_TOP_BASE                                            0x010c0000
#define RNG_SOC_TOP_BASE_SIZE                                       0x00030000
#define RNG_SOC_TOP_BASE_PHYS                                       0x010c0000

/*----------------------------------------------------------------------------
 * BASE: MMSS_NOC_SF
 *--------------------------------------------------------------------------*/

#define MMSS_NOC_SF_BASE                                            0x01400000
#define MMSS_NOC_SF_BASE_SIZE                                       0x0005c000
#define MMSS_NOC_SF_BASE_PHYS                                       0x01400000

/*----------------------------------------------------------------------------
 * BASE: MMSS_NOC_HF
 *--------------------------------------------------------------------------*/

#define MMSS_NOC_HF_BASE                                            0x01480000
#define MMSS_NOC_HF_BASE_SIZE                                       0x0005b800
#define MMSS_NOC_HF_BASE_PHYS                                       0x01480000

/*----------------------------------------------------------------------------
 * BASE: TUNNELS_NOC_WRAPPER
 *--------------------------------------------------------------------------*/

#define TUNNELS_NOC_WRAPPER_BASE                                    0x01500000
#define TUNNELS_NOC_WRAPPER_BASE_SIZE                               0x00241400
#define TUNNELS_NOC_WRAPPER_BASE_PHYS                               0x01500000

/*----------------------------------------------------------------------------
 * BASE: PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X1
 *--------------------------------------------------------------------------*/

#define PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X1_BASE                      0x01c00000
#define PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X1_BASE_SIZE                 0x00008000
#define PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X1_BASE_PHYS                 0x01c00000

/*----------------------------------------------------------------------------
 * BASE: PCIE1_PCIE_WRAPPER_AHB_W_PHY_G3X2
 *--------------------------------------------------------------------------*/

#define PCIE1_PCIE_WRAPPER_AHB_W_PHY_G3X2_BASE                      0x01c08000
#define PCIE1_PCIE_WRAPPER_AHB_W_PHY_G3X2_BASE_SIZE                 0x00008000
#define PCIE1_PCIE_WRAPPER_AHB_W_PHY_G3X2_BASE_PHYS                 0x01c08000

/*----------------------------------------------------------------------------
 * BASE: UFS_MEM_UFS_2LANE_REGS
 *--------------------------------------------------------------------------*/

#define UFS_MEM_UFS_2LANE_REGS_BASE                                 0x01d80000
#define UFS_MEM_UFS_2LANE_REGS_BASE_SIZE                            0x00020000
#define UFS_MEM_UFS_2LANE_REGS_BASE_PHYS                            0x01d80000

/*----------------------------------------------------------------------------
 * BASE: CRYPTO0_CRYPTO_TOP
 *--------------------------------------------------------------------------*/

#define CRYPTO0_CRYPTO_TOP_BASE                                     0x01dc0000
#define CRYPTO0_CRYPTO_TOP_BASE_SIZE                                0x00040000
#define CRYPTO0_CRYPTO_TOP_BASE_PHYS                                0x01dc0000

/*----------------------------------------------------------------------------
 * BASE: CORE_TOP_CSR
 *--------------------------------------------------------------------------*/

#define CORE_TOP_CSR_BASE                                           0x01f00000
#define CORE_TOP_CSR_BASE_SIZE                                      0x00100000
#define CORE_TOP_CSR_BASE_PHYS                                      0x01f00000

/*----------------------------------------------------------------------------
 * BASE: LPASS_TCM
 *--------------------------------------------------------------------------*/

#define LPASS_TCM_BASE                                              0x02c00000
#define LPASS_TCM_BASE_SIZE                                         0x00000000
#define LPASS_TCM_BASE_PHYS                                         0x02c00000

/*----------------------------------------------------------------------------
 * BASE: LPASS
 *--------------------------------------------------------------------------*/

#define LPASS_BASE                                                  0x02c00000
#define LPASS_BASE_SIZE                                             0x01080000
#define LPASS_BASE_PHYS                                             0x02c00000

/*----------------------------------------------------------------------------
 * BASE: LPASS_TCM_END
 *--------------------------------------------------------------------------*/

#define LPASS_TCM_END_BASE                                          0x02ffffff
#define LPASS_TCM_END_BASE_SIZE                                     0x00000000
#define LPASS_TCM_END_BASE_PHYS                                     0x02ffffff

/*----------------------------------------------------------------------------
 * BASE: LPASS_AUDIO_LPM
 *--------------------------------------------------------------------------*/

#define LPASS_AUDIO_LPM_BASE                                        0x03260000
#define LPASS_AUDIO_LPM_BASE_SIZE                                   0x00000000
#define LPASS_AUDIO_LPM_BASE_PHYS                                   0x03260000

/*----------------------------------------------------------------------------
 * BASE: LPASS_AUDIO_LPM_END
 *--------------------------------------------------------------------------*/

#define LPASS_AUDIO_LPM_END_BASE                                    0x0326bfff
#define LPASS_AUDIO_LPM_END_BASE_SIZE                               0x00000000
#define LPASS_AUDIO_LPM_END_BASE_PHYS                               0x0326bfff

/*----------------------------------------------------------------------------
 * BASE: LPASS_VA_LPM
 *--------------------------------------------------------------------------*/

#define LPASS_VA_LPM_BASE                                           0x033ec000
#define LPASS_VA_LPM_BASE_SIZE                                      0x00000000
#define LPASS_VA_LPM_BASE_PHYS                                      0x033ec000

/*----------------------------------------------------------------------------
 * BASE: LPASS_VA_LPM_END
 *--------------------------------------------------------------------------*/

#define LPASS_VA_LPM_END_BASE                                       0x033eefff
#define LPASS_VA_LPM_END_BASE_SIZE                                  0x00000000
#define LPASS_VA_LPM_END_BASE_PHYS                                  0x033eefff

/*----------------------------------------------------------------------------
 * BASE: SSC_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define SSC_RAM_START_ADDRESS_BASE                                  0x03600000
#define SSC_RAM_START_ADDRESS_BASE_SIZE                             0x00000000
#define SSC_RAM_START_ADDRESS_BASE_PHYS                             0x03600000

/*----------------------------------------------------------------------------
 * BASE: SSC_RAM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define SSC_RAM_END_ADDRESS_BASE                                    0x03609fff
#define SSC_RAM_END_ADDRESS_BASE_SIZE                               0x00000000
#define SSC_RAM_END_ADDRESS_BASE_PHYS                               0x03609fff

/*----------------------------------------------------------------------------
 * BASE: LPASS_LPM
 *--------------------------------------------------------------------------*/

#define LPASS_LPM_BASE                                              0x03a10000
#define LPASS_LPM_BASE_SIZE                                         0x00000000
#define LPASS_LPM_BASE_PHYS                                         0x03a10000

/*----------------------------------------------------------------------------
 * BASE: LPASS_LPM_END
 *--------------------------------------------------------------------------*/

#define LPASS_LPM_END_BASE                                          0x03a17fff
#define LPASS_LPM_END_BASE_SIZE                                     0x00000000
#define LPASS_LPM_END_BASE_PHYS                                     0x03a17fff

/*----------------------------------------------------------------------------
 * BASE: GFX
 *--------------------------------------------------------------------------*/

#define GFX_BASE                                                    0x03d00000
#define GFX_BASE_SIZE                                               0x00100000
#define GFX_BASE_PHYS                                               0x03d00000

/*----------------------------------------------------------------------------
 * BASE: IPA_WRAPPER
 *--------------------------------------------------------------------------*/

#define IPA_WRAPPER_BASE                                            0x03e00000
#define IPA_WRAPPER_BASE_SIZE                                       0x00200000
#define IPA_WRAPPER_BASE_PHYS                                       0x03e00000

/*----------------------------------------------------------------------------
 * BASE: PCIE_GEN3X1_SPACE_0_SIZE
 *--------------------------------------------------------------------------*/

#define PCIE_GEN3X1_SPACE_0_SIZE_BASE                               0x04000000
#define PCIE_GEN3X1_SPACE_0_SIZE_BASE_SIZE                          0x00000000
#define PCIE_GEN3X1_SPACE_0_SIZE_BASE_PHYS                          0x04000000

/*----------------------------------------------------------------------------
 * BASE: PIMEM_SIZE
 *--------------------------------------------------------------------------*/

#define PIMEM_SIZE_BASE                                             0x04000000
#define PIMEM_SIZE_BASE_SIZE                                        0x00000000
#define PIMEM_SIZE_BASE_PHYS                                        0x04000000

/*----------------------------------------------------------------------------
 * BASE: MODEM_TOP
 *--------------------------------------------------------------------------*/

#define MODEM_TOP_BASE                                              0x04000000
#define MODEM_TOP_BASE_SIZE                                         0x01000000
#define MODEM_TOP_BASE_PHYS                                         0x04000000

/*----------------------------------------------------------------------------
 * BASE: MSS__QDSP6_TCM
 *--------------------------------------------------------------------------*/

#define MSS__QDSP6_TCM_BASE                                         0x05400000
#define MSS__QDSP6_TCM_BASE_SIZE                                    0x00000000
#define MSS__QDSP6_TCM_BASE_PHYS                                    0x05400000

/*----------------------------------------------------------------------------
 * BASE: MSS__QDSP6_TCM_END
 *--------------------------------------------------------------------------*/

#define MSS__QDSP6_TCM_END_BASE                                     0x057fffff
#define MSS__QDSP6_TCM_END_BASE_SIZE                                0x00000000
#define MSS__QDSP6_TCM_END_BASE_PHYS                                0x057fffff

/*----------------------------------------------------------------------------
 * BASE: PMU_WRAPPER
 *--------------------------------------------------------------------------*/

#define PMU_WRAPPER_BASE                                            0x08400000
#define PMU_WRAPPER_BASE_SIZE                                       0x00200000
#define PMU_WRAPPER_BASE_PHYS                                       0x08400000

/*----------------------------------------------------------------------------
 * BASE: PERIPH_SS_SDC2_SDCC5_TOP
 *--------------------------------------------------------------------------*/

#define PERIPH_SS_SDC2_SDCC5_TOP_BASE                               0x08800000
#define PERIPH_SS_SDC2_SDCC5_TOP_BASE_SIZE                          0x00020000
#define PERIPH_SS_SDC2_SDCC5_TOP_BASE_PHYS                          0x08800000

/*----------------------------------------------------------------------------
 * BASE: PERIPH_SS_SDC1_SDCC5_TOP
 *--------------------------------------------------------------------------*/

#define PERIPH_SS_SDC1_SDCC5_TOP_BASE                               0x08840000
#define PERIPH_SS_SDC1_SDCC5_TOP_BASE_SIZE                          0x00020000
#define PERIPH_SS_SDC1_SDCC5_TOP_BASE_PHYS                          0x08840000

/*----------------------------------------------------------------------------
 * BASE: VSENSE_CONTROLLER
 *--------------------------------------------------------------------------*/

#define VSENSE_CONTROLLER_BASE                                      0x088c8000
#define VSENSE_CONTROLLER_BASE_SIZE                                 0x00001000
#define VSENSE_CONTROLLER_BASE_PHYS                                 0x088c8000

/*----------------------------------------------------------------------------
 * BASE: PERIPH_SS_PDM_PERPH_WEB
 *--------------------------------------------------------------------------*/

#define PERIPH_SS_PDM_PERPH_WEB_BASE                                0x088d0000
#define PERIPH_SS_PDM_PERPH_WEB_BASE_SIZE                           0x00004000
#define PERIPH_SS_PDM_PERPH_WEB_BASE_PHYS                           0x088d0000

/*----------------------------------------------------------------------------
 * BASE: QSPI_TOP
 *--------------------------------------------------------------------------*/

#define QSPI_TOP_BASE                                               0x088dc000
#define QSPI_TOP_BASE_SIZE                                          0x00004000
#define QSPI_TOP_BASE_PHYS                                          0x088dc000

/*----------------------------------------------------------------------------
 * BASE: AHB2PHY_WEST
 *--------------------------------------------------------------------------*/

#define AHB2PHY_WEST_BASE                                           0x088e0000
#define AHB2PHY_WEST_BASE_SIZE                                      0x00010000
#define AHB2PHY_WEST_BASE_PHYS                                      0x088e0000

/*----------------------------------------------------------------------------
 * BASE: WPSS
 *--------------------------------------------------------------------------*/

#define WPSS_BASE                                                   0x08a00000
#define WPSS_BASE_SIZE                                              0x00200000
#define WPSS_BASE_PHYS                                              0x08a00000

/*----------------------------------------------------------------------------
 * BASE: USB3_PRI_USB30_PRIM
 *--------------------------------------------------------------------------*/

#define USB3_PRI_USB30_PRIM_BASE                                    0x0a600000
#define USB3_PRI_USB30_PRIM_BASE_SIZE                               0x00200000
#define USB3_PRI_USB30_PRIM_BASE_PHYS                               0x0a600000

/*----------------------------------------------------------------------------
 * BASE: IRIS
 *--------------------------------------------------------------------------*/

#define IRIS_BASE                                                   0x0aa00000
#define IRIS_BASE_SIZE                                              0x00200000
#define IRIS_BASE_PHYS                                              0x0aa00000

/*----------------------------------------------------------------------------
 * BASE: CAMERA_SS
 *--------------------------------------------------------------------------*/

#define CAMERA_SS_BASE                                              0x0ac00000
#define CAMERA_SS_BASE_SIZE                                         0x00200000
#define CAMERA_SS_BASE_PHYS                                         0x0ac00000

/*----------------------------------------------------------------------------
 * BASE: MDSS
 *--------------------------------------------------------------------------*/

#define MDSS_BASE                                                   0x0ae00000
#define MDSS_BASE_SIZE                                              0x00200000
#define MDSS_BASE_PHYS                                              0x0ae00000

/*----------------------------------------------------------------------------
 * BASE: AOSS
 *--------------------------------------------------------------------------*/

#define AOSS_BASE                                                   0x0b000000
#define AOSS_BASE_SIZE                                              0x04000000
#define AOSS_BASE_PHYS                                              0x0b000000

/*----------------------------------------------------------------------------
 * BASE: AOP_SS_MSG_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define AOP_SS_MSG_RAM_START_ADDRESS_BASE                           0x0c300000
#define AOP_SS_MSG_RAM_START_ADDRESS_BASE_SIZE                      0x00000000
#define AOP_SS_MSG_RAM_START_ADDRESS_BASE_PHYS                      0x0c300000

/*----------------------------------------------------------------------------
 * BASE: TLMM
 *--------------------------------------------------------------------------*/

#define TLMM_BASE                                                   0x0f000000
#define TLMM_BASE_SIZE                                              0x01000000
#define TLMM_BASE_PHYS                                              0x0f000000

/*----------------------------------------------------------------------------
 * BASE: QDSS_SOC_DBG
 *--------------------------------------------------------------------------*/

#define QDSS_SOC_DBG_BASE                                           0x10000000
#define QDSS_SOC_DBG_BASE_SIZE                                      0x04000000
#define QDSS_SOC_DBG_BASE_PHYS                                      0x10000000

/*----------------------------------------------------------------------------
 * BASE: SYSTEM_IMEM
 *--------------------------------------------------------------------------*/

#define SYSTEM_IMEM_BASE                                            0x14680000
#define SYSTEM_IMEM_BASE_SIZE                                       0x00000000
#define SYSTEM_IMEM_BASE_PHYS                                       0x14680000

/*----------------------------------------------------------------------------
 * BASE: SYSTEM_IMEM_END
 *--------------------------------------------------------------------------*/

#define SYSTEM_IMEM_END_BASE                                        0x146abfff
#define SYSTEM_IMEM_END_BASE_SIZE                                   0x00000000
#define SYSTEM_IMEM_END_BASE_PHYS                                   0x146abfff

/*----------------------------------------------------------------------------
 * BASE: BOOT_IMEM
 *--------------------------------------------------------------------------*/

#define BOOT_IMEM_BASE                                              0x14800000
#define BOOT_IMEM_BASE_SIZE                                         0x00400000
#define BOOT_IMEM_BASE_PHYS                                         0x14800000

/*----------------------------------------------------------------------------
 * BASE: WPSS_TCM
 *--------------------------------------------------------------------------*/

#define WPSS_TCM_BASE                                               0x14c00000
#define WPSS_TCM_BASE_SIZE                                          0x00000000
#define WPSS_TCM_BASE_PHYS                                          0x14c00000

/*----------------------------------------------------------------------------
 * BASE: WPSS_TCM_END
 *--------------------------------------------------------------------------*/

#define WPSS_TCM_END_BASE                                           0x14ffffff
#define WPSS_TCM_END_BASE_SIZE                                      0x00000000
#define WPSS_TCM_END_BASE_PHYS                                      0x14ffffff

/*----------------------------------------------------------------------------
 * BASE: SMMU_500_APPS_REG_WRAPPER
 *--------------------------------------------------------------------------*/

#define SMMU_500_APPS_REG_WRAPPER_BASE                              0x15000000
#define SMMU_500_APPS_REG_WRAPPER_BASE_SIZE                         0x00200000
#define SMMU_500_APPS_REG_WRAPPER_BASE_PHYS                         0x15000000

/*----------------------------------------------------------------------------
 * BASE: QDSS_STM
 *--------------------------------------------------------------------------*/

#define QDSS_STM_BASE                                               0x16000000
#define QDSS_STM_BASE_SIZE                                          0x00000000
#define QDSS_STM_BASE_PHYS                                          0x16000000

/*----------------------------------------------------------------------------
 * BASE: QDSS_STM_END
 *--------------------------------------------------------------------------*/

#define QDSS_STM_END_BASE                                           0x16ffffff
#define QDSS_STM_END_BASE_SIZE                                      0x00000000
#define QDSS_STM_END_BASE_PHYS                                      0x16ffffff

/*----------------------------------------------------------------------------
 * BASE: APSS_HM
 *--------------------------------------------------------------------------*/

#define APSS_HM_BASE                                                0x17000000
#define APSS_HM_BASE_SIZE                                           0x02000000
#define APSS_HM_BASE_PHYS                                           0x17000000

/*----------------------------------------------------------------------------
 * BASE: PIMEM
 *--------------------------------------------------------------------------*/

#define PIMEM_BASE                                                  0x1c000000
#define PIMEM_BASE_SIZE                                             0x00000000
#define PIMEM_BASE_PHYS                                             0x1c000000

/*----------------------------------------------------------------------------
 * BASE: PIMEM_END
 *--------------------------------------------------------------------------*/

#define PIMEM_END_BASE                                              0x1fffffff
#define PIMEM_END_BASE_SIZE                                         0x00000000
#define PIMEM_END_BASE_PHYS                                         0x1fffffff

/*----------------------------------------------------------------------------
 * BASE: TMESS
 *--------------------------------------------------------------------------*/

#define TMESS_BASE                                                  0x20000000
#define TMESS_BASE_SIZE                                             0x02300000
#define TMESS_BASE_PHYS                                             0x20000000

/*----------------------------------------------------------------------------
 * BASE: DDR_SS
 *--------------------------------------------------------------------------*/

#define DDR_SS_BASE                                                 0x24000000
#define DDR_SS_BASE_SIZE                                            0x01000000
#define DDR_SS_BASE_PHYS                                            0x24000000

/*----------------------------------------------------------------------------
 * BASE: MODEM_OFFLINE
 *--------------------------------------------------------------------------*/

#define MODEM_OFFLINE_BASE                                          0x28000000
#define MODEM_OFFLINE_BASE_SIZE                                     0x04000000
#define MODEM_OFFLINE_BASE_PHYS                                     0x28000000

/*----------------------------------------------------------------------------
 * BASE: TURING
 *--------------------------------------------------------------------------*/

#define TURING_BASE                                                 0x30000000
#define TURING_BASE_SIZE                                            0x03000000
#define TURING_BASE_PHYS                                            0x30000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_GEN3X2_PCIE_WRAPPER_AXI_G3X2
 *--------------------------------------------------------------------------*/

#define PCIE_GEN3X2_PCIE_WRAPPER_AXI_G3X2_BASE                      0x40000000
#define PCIE_GEN3X2_PCIE_WRAPPER_AXI_G3X2_BASE_SIZE                 0x02000000
#define PCIE_GEN3X2_PCIE_WRAPPER_AXI_G3X2_BASE_PHYS                 0x40000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_GEN3X1_SPACE_0
 *--------------------------------------------------------------------------*/

#define PCIE_GEN3X1_SPACE_0_BASE                                    0x60000000
#define PCIE_GEN3X1_SPACE_0_BASE_SIZE                               0x00000000
#define PCIE_GEN3X1_SPACE_0_BASE_PHYS                               0x60000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_GEN3X1_PCIE_WRAPPER_AXI_G3X1
 *--------------------------------------------------------------------------*/

#define PCIE_GEN3X1_PCIE_WRAPPER_AXI_G3X1_BASE                      0x60000000
#define PCIE_GEN3X1_PCIE_WRAPPER_AXI_G3X1_BASE_SIZE                 0x04000000
#define PCIE_GEN3X1_PCIE_WRAPPER_AXI_G3X1_BASE_PHYS                 0x60000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_GEN3X1_SPACE_0_END
 *--------------------------------------------------------------------------*/

#define PCIE_GEN3X1_SPACE_0_END_BASE                                0x63ffffff
#define PCIE_GEN3X1_SPACE_0_END_BASE_SIZE                           0x00000000
#define PCIE_GEN3X1_SPACE_0_END_BASE_PHYS                           0x63ffffff

/*----------------------------------------------------------------------------
 * BASE: DDR_SPACE
 *--------------------------------------------------------------------------*/

#define DDR_SPACE_BASE                                              0x80000000
#define DDR_SPACE_BASE_SIZE                                         0x00000000
#define DDR_SPACE_BASE_PHYS                                         0x80000000

/*----------------------------------------------------------------------------
 * BASE: DDR_SPACE_SIZE
 *--------------------------------------------------------------------------*/

#define DDR_SPACE_SIZE_BASE                                         0x80000000
#define DDR_SPACE_SIZE_BASE_SIZE                                    0x00000000
#define DDR_SPACE_SIZE_BASE_PHYS                                    0x80000000

/*----------------------------------------------------------------------------
 * BASE: DDR_SPACE_END
 *--------------------------------------------------------------------------*/

#define DDR_SPACE_END_BASE                                          0xffffffff
#define DDR_SPACE_END_BASE_SIZE                                     0x00000000
#define DDR_SPACE_END_BASE_PHYS                                     0xffffffff

/*----------------------------------------------------------------------------
 * BASE: PCIE_1_SPACE_SIZE
 *--------------------------------------------------------------------------*/

#define PCIE_1_SPACE_SIZE_BASE                                      0x300000000uLL
#define PCIE_1_SPACE_SIZE_BASE_SIZE                                 0x00000000
#define PCIE_1_SPACE_SIZE_BASE_PHYS                                 0x300000000uLL

/*----------------------------------------------------------------------------
 * BASE: PCIE_1_SPACE
 *--------------------------------------------------------------------------*/

#define PCIE_1_SPACE_BASE                                           0x400000000uLL
#define PCIE_1_SPACE_BASE_SIZE                                      0x00000000
#define PCIE_1_SPACE_BASE_PHYS                                      0x400000000uLL

/*----------------------------------------------------------------------------
 * BASE: PCIE_1_SPACE_END
 *--------------------------------------------------------------------------*/

#define PCIE_1_SPACE_END_BASE                                       0x6ffffffffuLL
#define PCIE_1_SPACE_END_BASE_SIZE                                  0x00000000
#define PCIE_1_SPACE_END_BASE_PHYS                                  0x6ffffffffuLL

/*----------------------------------------------------------------------------
 * BASE: DDR_1_SPACE_SIZE
 *--------------------------------------------------------------------------*/

#define DDR_1_SPACE_SIZE_BASE                                       0x780000000uLL
#define DDR_1_SPACE_SIZE_BASE_SIZE                                  0x00000000
#define DDR_1_SPACE_SIZE_BASE_PHYS                                  0x780000000uLL

/*----------------------------------------------------------------------------
 * BASE: DDR_1_SPACE
 *--------------------------------------------------------------------------*/

#define DDR_1_SPACE_BASE                                            0x880000000uLL
#define DDR_1_SPACE_BASE_SIZE                                       0x00000000
#define DDR_1_SPACE_BASE_PHYS                                       0x880000000uLL

/*----------------------------------------------------------------------------
 * BASE: DDR_1_SPACE_END
 *--------------------------------------------------------------------------*/

#define DDR_1_SPACE_END_BASE                                        0xfffffffffuLL
#define DDR_1_SPACE_END_BASE_SIZE                                   0x00000000
#define DDR_1_SPACE_END_BASE_PHYS                                   0xfffffffffuLL

/*----------------------------------------------------------------------------
 * MEMORY: TCM1
 *--------------------------------------------------------------------------*/

#define TCM1                                                        0x20400000
#define TCM1_SIZE                                                   0x00048000
#define TCM1_PHYS                                                   0x20400000

/*----------------------------------------------------------------------------
 * MEMORY: TME_MBOX_RAM_LOW
 *--------------------------------------------------------------------------*/

#define TME_MBOX_RAM_LOW                                            0x22000000
#define TME_MBOX_RAM_LOW_SIZE                                       0x00000800
#define TME_MBOX_RAM_LOW_PHYS                                       0x22000000

/*----------------------------------------------------------------------------
 * MEMORY: TME_MBOX_RAM_HIGH
 *--------------------------------------------------------------------------*/

#define TME_MBOX_RAM_HIGH                                           0x22002800
#define TME_MBOX_RAM_HIGH_SIZE                                      0x00001000
#define TME_MBOX_RAM_HIGH_PHYS                                      0x22002800


#endif /* __MSMHWIOBASE_H__ */
