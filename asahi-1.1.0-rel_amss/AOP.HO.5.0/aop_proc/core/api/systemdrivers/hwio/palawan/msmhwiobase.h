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
  
  Copyright (c) 2023 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary
  
  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.
  
  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies Incorporated and all rights therein are expressly 
  reserved.
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
 * BASE: AOSS
 *--------------------------------------------------------------------------*/

#define AOSS_BASE                                                   0x00000000
#define AOSS_BASE_SIZE                                              0x04000000
#define AOSS_BASE_PHYS                                              0x00000000

/*----------------------------------------------------------------------------
 * BASE: LPASS_VA_LPM_SIZE
 *--------------------------------------------------------------------------*/

#define LPASS_VA_LPM_SIZE_BASE                                      0x00003000
#define LPASS_VA_LPM_SIZE_BASE_SIZE                                 0x00000000
#define LPASS_VA_LPM_SIZE_BASE_PHYS                                 0x00003000

/*----------------------------------------------------------------------------
 * BASE: LPASS_CORE_LPM_SIZE
 *--------------------------------------------------------------------------*/

#define LPASS_CORE_LPM_SIZE_BASE                                    0x00008000
#define LPASS_CORE_LPM_SIZE_BASE_SIZE                               0x00000000
#define LPASS_CORE_LPM_SIZE_BASE_PHYS                               0x00008000

/*----------------------------------------------------------------------------
 * BASE: LPASS_AUDIO_LPM_SIZE
 *--------------------------------------------------------------------------*/

#define LPASS_AUDIO_LPM_SIZE_BASE                                   0x00010000
#define LPASS_AUDIO_LPM_SIZE_BASE_SIZE                              0x00000000
#define LPASS_AUDIO_LPM_SIZE_BASE_PHYS                              0x00010000

/*----------------------------------------------------------------------------
 * BASE: SSC_SDC_DATA_RAM_SIZE
 *--------------------------------------------------------------------------*/

#define SSC_SDC_DATA_RAM_SIZE_BASE                                  0x00010000
#define SSC_SDC_DATA_RAM_SIZE_BASE_SIZE                             0x00000000
#define SSC_SDC_DATA_RAM_SIZE_BASE_PHYS                             0x00010000

/*----------------------------------------------------------------------------
 * BASE: SSC_RAM_SIZE
 *--------------------------------------------------------------------------*/

#define SSC_RAM_SIZE_BASE                                           0x00015400
#define SSC_RAM_SIZE_BASE_SIZE                                      0x00000000
#define SSC_RAM_SIZE_BASE_PHYS                                      0x00015400

/*----------------------------------------------------------------------------
 * BASE: SSC_SDC_CODE_RAM_SIZE
 *--------------------------------------------------------------------------*/

#define SSC_SDC_CODE_RAM_SIZE_BASE                                  0x00018000
#define SSC_SDC_CODE_RAM_SIZE_BASE_SIZE                             0x00000000
#define SSC_SDC_CODE_RAM_SIZE_BASE_PHYS                             0x00018000

/*----------------------------------------------------------------------------
 * BASE: SYSTEM_IMEM_SIZE
 *--------------------------------------------------------------------------*/

#define SYSTEM_IMEM_SIZE_BASE                                       0x0002c000
#define SYSTEM_IMEM_SIZE_BASE_SIZE                                  0x00000000
#define SYSTEM_IMEM_SIZE_BASE_PHYS                                  0x0002c000

/*----------------------------------------------------------------------------
 * BASE: LPASS_LPI_TCM_SIZE
 *--------------------------------------------------------------------------*/

#define LPASS_LPI_TCM_SIZE_BASE                                     0x00080000
#define LPASS_LPI_TCM_SIZE_BASE_SIZE                                0x00000000
#define LPASS_LPI_TCM_SIZE_BASE_PHYS                                0x00080000

/*----------------------------------------------------------------------------
 * BASE: LPASS_Q6_TCM_SIZE
 *--------------------------------------------------------------------------*/

#define LPASS_Q6_TCM_SIZE_BASE                                      0x00280000
#define LPASS_Q6_TCM_SIZE_BASE_SIZE                                 0x00000000
#define LPASS_Q6_TCM_SIZE_BASE_PHYS                                 0x00280000

/*----------------------------------------------------------------------------
 * BASE: MSS__QDSP6_TCM_SIZE
 *--------------------------------------------------------------------------*/

#define MSS__QDSP6_TCM_SIZE_BASE                                    0x00400000
#define MSS__QDSP6_TCM_SIZE_BASE_SIZE                               0x00000000
#define MSS__QDSP6_TCM_SIZE_BASE_PHYS                               0x00400000

/*----------------------------------------------------------------------------
 * BASE: QDSS_STM_SIZE
 *--------------------------------------------------------------------------*/

#define QDSS_STM_SIZE_BASE                                          0x01000000
#define QDSS_STM_SIZE_BASE_SIZE                                     0x00000000
#define QDSS_STM_SIZE_BASE_PHYS                                     0x01000000

/*----------------------------------------------------------------------------
 * BASE: SC_TCM_SIZE
 *--------------------------------------------------------------------------*/

#define SC_TCM_SIZE_BASE                                            0x08000000
#define SC_TCM_SIZE_BASE_SIZE                                       0x00000000
#define SC_TCM_SIZE_BASE_PHYS                                       0x08000000

/*----------------------------------------------------------------------------
 * BASE: AOP_RVSS_RVSS_AOP_WRAPPER
 *--------------------------------------------------------------------------*/

#define AOP_RVSS_RVSS_AOP_WRAPPER_BASE                              0x08000000
#define AOP_RVSS_RVSS_AOP_WRAPPER_BASE_SIZE                         0x02000000
#define AOP_RVSS_RVSS_AOP_WRAPPER_BASE_PHYS                         0x08000000

/*----------------------------------------------------------------------------
 * BASE: DDR_SPACE_SIZE
 *--------------------------------------------------------------------------*/

#define DDR_SPACE_SIZE_BASE                                         0x18000000
#define DDR_SPACE_SIZE_BASE_SIZE                                    0x00000000
#define DDR_SPACE_SIZE_BASE_PHYS                                    0x18000000

/*----------------------------------------------------------------------------
 * BASE: CLK_CTL
 *--------------------------------------------------------------------------*/

#define CLK_CTL_BASE                                                0x60100000
#define CLK_CTL_BASE_SIZE                                           0x00200000
#define CLK_CTL_BASE_PHYS                                           0x60100000

/*----------------------------------------------------------------------------
 * BASE: BOOT_ROM
 *--------------------------------------------------------------------------*/

#define BOOT_ROM_BASE                                               0x60300000
#define BOOT_ROM_BASE_SIZE                                          0x00100000
#define BOOT_ROM_BASE_PHYS                                          0x60300000

/*----------------------------------------------------------------------------
 * BASE: IPC_ROUTER_TOP
 *--------------------------------------------------------------------------*/

#define IPC_ROUTER_TOP_BASE                                         0x60400000
#define IPC_ROUTER_TOP_BASE_SIZE                                    0x00200000
#define IPC_ROUTER_TOP_BASE_PHYS                                    0x60400000

/*----------------------------------------------------------------------------
 * BASE: OCIMEM_WRAPPER_CSR
 *--------------------------------------------------------------------------*/

#define OCIMEM_WRAPPER_CSR_BASE                                     0x60618000
#define OCIMEM_WRAPPER_CSR_BASE_SIZE                                0x00006000
#define OCIMEM_WRAPPER_CSR_BASE_PHYS                                0x60618000

/*----------------------------------------------------------------------------
 * BASE: CX_CPR3
 *--------------------------------------------------------------------------*/

#define CX_CPR3_BASE                                                0x60628000
#define CX_CPR3_BASE_SIZE                                           0x00004000
#define CX_CPR3_BASE_PHYS                                           0x60628000

/*----------------------------------------------------------------------------
 * BASE: MXC_CPR3
 *--------------------------------------------------------------------------*/

#define MXC_CPR3_BASE                                               0x6062c000
#define MXC_CPR3_BASE_SIZE                                          0x00004000
#define MXC_CPR3_BASE_PHYS                                          0x6062c000

/*----------------------------------------------------------------------------
 * BASE: MMCX_CPR3
 *--------------------------------------------------------------------------*/

#define MMCX_CPR3_BASE                                              0x60630000
#define MMCX_CPR3_BASE_SIZE                                         0x00004000
#define MMCX_CPR3_BASE_PHYS                                         0x60630000

/*----------------------------------------------------------------------------
 * BASE: MX_CPR3
 *--------------------------------------------------------------------------*/

#define MX_CPR3_BASE                                                0x60638000
#define MX_CPR3_BASE_SIZE                                           0x00004000
#define MX_CPR3_BASE_PHYS                                           0x60638000

/*----------------------------------------------------------------------------
 * BASE: NSP_CX_CPR3
 *--------------------------------------------------------------------------*/

#define NSP_CX_CPR3_BASE                                            0x6063c000
#define NSP_CX_CPR3_BASE_SIZE                                       0x00004000
#define NSP_CX_CPR3_BASE_PHYS                                       0x6063c000

/*----------------------------------------------------------------------------
 * BASE: RDPM_CXRDPM_TOP
 *--------------------------------------------------------------------------*/

#define RDPM_CXRDPM_TOP_BASE                                        0x60640000
#define RDPM_CXRDPM_TOP_BASE_SIZE                                   0x00010000
#define RDPM_CXRDPM_TOP_BASE_PHYS                                   0x60640000

/*----------------------------------------------------------------------------
 * BASE: RDPM_MXC_RDPM_TOP
 *--------------------------------------------------------------------------*/

#define RDPM_MXC_RDPM_TOP_BASE                                      0x60650000
#define RDPM_MXC_RDPM_TOP_BASE_SIZE                                 0x00010000
#define RDPM_MXC_RDPM_TOP_BASE_PHYS                                 0x60650000

/*----------------------------------------------------------------------------
 * BASE: RDPM_MXA_RDPM_TOP
 *--------------------------------------------------------------------------*/

#define RDPM_MXA_RDPM_TOP_BASE                                      0x60660000
#define RDPM_MXA_RDPM_TOP_BASE_SIZE                                 0x00010000
#define RDPM_MXA_RDPM_TOP_BASE_PHYS                                 0x60660000

/*----------------------------------------------------------------------------
 * BASE: QTB_NOC_LPASS
 *--------------------------------------------------------------------------*/

#define QTB_NOC_LPASS_BASE                                          0x607b0000
#define QTB_NOC_LPASS_BASE_SIZE                                     0x0000f080
#define QTB_NOC_LPASS_BASE_PHYS                                     0x607b0000

/*----------------------------------------------------------------------------
 * BASE: QTB_NOC_NSP
 *--------------------------------------------------------------------------*/

#define QTB_NOC_NSP_BASE                                            0x607d0000
#define QTB_NOC_NSP_BASE_SIZE                                       0x00010080
#define QTB_NOC_NSP_BASE_PHYS                                       0x607d0000

/*----------------------------------------------------------------------------
 * BASE: QUPV3_1_QUPV3_ID_2
 *--------------------------------------------------------------------------*/

#define QUPV3_1_QUPV3_ID_2_BASE                                     0x60800000
#define QUPV3_1_QUPV3_ID_2_BASE_SIZE                                0x00100000
#define QUPV3_1_QUPV3_ID_2_BASE_PHYS                                0x60800000

/*----------------------------------------------------------------------------
 * BASE: QUPV3_0_QUPV3_ID_1
 *--------------------------------------------------------------------------*/

#define QUPV3_0_QUPV3_ID_1_BASE                                     0x60a00000
#define QUPV3_0_QUPV3_ID_1_BASE_SIZE                                0x00100000
#define QUPV3_0_QUPV3_ID_1_BASE_PHYS                                0x60a00000

/*----------------------------------------------------------------------------
 * BASE: IBI_0_I3C_IBI_CTRL_ID_1
 *--------------------------------------------------------------------------*/

#define IBI_0_I3C_IBI_CTRL_ID_1_BASE                                0x60b00000
#define IBI_0_I3C_IBI_CTRL_ID_1_BASE_SIZE                           0x00010000
#define IBI_0_I3C_IBI_CTRL_ID_1_BASE_PHYS                           0x60b00000

/*----------------------------------------------------------------------------
 * BASE: IBI_1_I3C_IBI_CTRL_ID_1
 *--------------------------------------------------------------------------*/

#define IBI_1_I3C_IBI_CTRL_ID_1_BASE                                0x60b10000
#define IBI_1_I3C_IBI_CTRL_ID_1_BASE_SIZE                           0x00010000
#define IBI_1_I3C_IBI_CTRL_ID_1_BASE_PHYS                           0x60b10000

/*----------------------------------------------------------------------------
 * BASE: AHB2PHY_NORTH
 *--------------------------------------------------------------------------*/

#define AHB2PHY_NORTH_BASE                                          0x60ff0000
#define AHB2PHY_NORTH_BASE_SIZE                                     0x00004000
#define AHB2PHY_NORTH_BASE_PHYS                                     0x60ff0000

/*----------------------------------------------------------------------------
 * BASE: SNOC_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define SNOC_THROTTLE_THROTTLE_WRAPPER_1_BASE                       0x60ff4000
#define SNOC_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE                  0x00001000
#define SNOC_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS                  0x60ff4000

/*----------------------------------------------------------------------------
 * BASE: PCIE_THROTTLE_THROTTLE_BWMON_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define PCIE_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE                 0x60ff5000
#define PCIE_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE_SIZE            0x00001000
#define PCIE_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE_PHYS            0x60ff5000

/*----------------------------------------------------------------------------
 * BASE: GIC_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define GIC_THROTTLE_THROTTLE_WRAPPER_1_BASE                        0x60ff6000
#define GIC_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE                   0x00001000
#define GIC_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS                   0x60ff6000

/*----------------------------------------------------------------------------
 * BASE: WLAN_Q6_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define WLAN_Q6_THROTTLE_THROTTLE_WRAPPER_1_BASE                    0x60ffc000
#define WLAN_Q6_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE               0x00001000
#define WLAN_Q6_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS               0x60ffc000

/*----------------------------------------------------------------------------
 * BASE: MODEM_DEMBACK_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define MODEM_DEMBACK_THROTTLE_THROTTLE_WRAPPER_1_BASE              0x60ffd000
#define MODEM_DEMBACK_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE         0x00001000
#define MODEM_DEMBACK_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS         0x60ffd000

/*----------------------------------------------------------------------------
 * BASE: MODEM_DSP_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define MODEM_DSP_THROTTLE_THROTTLE_WRAPPER_1_BASE                  0x60ffe000
#define MODEM_DSP_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE             0x00001000
#define MODEM_DSP_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS             0x60ffe000

/*----------------------------------------------------------------------------
 * BASE: TITAN_THROTTLE_RT_THROTTLE_WRAPPER_2
 *--------------------------------------------------------------------------*/

#define TITAN_THROTTLE_RT_THROTTLE_WRAPPER_2_BASE                   0x61000000
#define TITAN_THROTTLE_RT_THROTTLE_WRAPPER_2_BASE_SIZE              0x00001000
#define TITAN_THROTTLE_RT_THROTTLE_WRAPPER_2_BASE_PHYS              0x61000000

/*----------------------------------------------------------------------------
 * BASE: ANOC2_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define ANOC2_THROTTLE_THROTTLE_WRAPPER_1_BASE                      0x61001000
#define ANOC2_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE                 0x00001000
#define ANOC2_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS                 0x61001000

/*----------------------------------------------------------------------------
 * BASE: VIDEO_THROTTLE_VCODEC_THROTTLE_BWMON_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define VIDEO_THROTTLE_VCODEC_THROTTLE_BWMON_WRAPPER_1_BASE         0x61002000
#define VIDEO_THROTTLE_VCODEC_THROTTLE_BWMON_WRAPPER_1_BASE_SIZE    0x00001000
#define VIDEO_THROTTLE_VCODEC_THROTTLE_BWMON_WRAPPER_1_BASE_PHYS    0x61002000

/*----------------------------------------------------------------------------
 * BASE: TITAN_THROTTLE_NRT_THROTTLE_WRAPPER_3
 *--------------------------------------------------------------------------*/

#define TITAN_THROTTLE_NRT_THROTTLE_WRAPPER_3_BASE                  0x61003000
#define TITAN_THROTTLE_NRT_THROTTLE_WRAPPER_3_BASE_SIZE             0x00001000
#define TITAN_THROTTLE_NRT_THROTTLE_WRAPPER_3_BASE_PHYS             0x61003000

/*----------------------------------------------------------------------------
 * BASE: VIDEO_THROTTLE_CVP_THROTTLE_BWMON_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define VIDEO_THROTTLE_CVP_THROTTLE_BWMON_WRAPPER_1_BASE            0x61004000
#define VIDEO_THROTTLE_CVP_THROTTLE_BWMON_WRAPPER_1_BASE_SIZE       0x00001000
#define VIDEO_THROTTLE_CVP_THROTTLE_BWMON_WRAPPER_1_BASE_PHYS       0x61004000

/*----------------------------------------------------------------------------
 * BASE: ANOC1_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define ANOC1_THROTTLE_THROTTLE_WRAPPER_1_BASE                      0x61005000
#define ANOC1_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE                 0x00001000
#define ANOC1_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS                 0x61005000

/*----------------------------------------------------------------------------
 * BASE: VENUS_V_CPU_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define VENUS_V_CPU_THROTTLE_THROTTLE_WRAPPER_1_BASE                0x61006000
#define VENUS_V_CPU_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE           0x00001000
#define VENUS_V_CPU_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS           0x61006000

/*----------------------------------------------------------------------------
 * BASE: VENUS_CV_CPU_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define VENUS_CV_CPU_THROTTLE_THROTTLE_WRAPPER_1_BASE               0x61007000
#define VENUS_CV_CPU_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE          0x00001000
#define VENUS_CV_CPU_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS          0x61007000

/*----------------------------------------------------------------------------
 * BASE: GPU_TCU_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define GPU_TCU_THROTTLE_THROTTLE_WRAPPER_1_BASE                    0x61040000
#define GPU_TCU_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE               0x00001000
#define GPU_TCU_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS               0x61040000

/*----------------------------------------------------------------------------
 * BASE: LPASS_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define LPASS_THROTTLE_THROTTLE_WRAPPER_1_BASE                      0x61041000
#define LPASS_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE                 0x00001000
#define LPASS_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS                 0x61041000

/*----------------------------------------------------------------------------
 * BASE: QM
 *--------------------------------------------------------------------------*/

#define QM_BASE                                                     0x610b8000
#define QM_BASE_SIZE                                                0x00004000
#define QM_BASE_PHYS                                                0x610b8000

/*----------------------------------------------------------------------------
 * BASE: QM_MPU_CFG_QM_MPU_WRAPPER
 *--------------------------------------------------------------------------*/

#define QM_MPU_CFG_QM_MPU_WRAPPER_BASE                              0x610bc000
#define QM_MPU_CFG_QM_MPU_WRAPPER_BASE_SIZE                         0x00004000
#define QM_MPU_CFG_QM_MPU_WRAPPER_BASE_PHYS                         0x610bc000

/*----------------------------------------------------------------------------
 * BASE: RNG_SOC_TOP
 *--------------------------------------------------------------------------*/

#define RNG_SOC_TOP_BASE                                            0x610c0000
#define RNG_SOC_TOP_BASE_SIZE                                       0x00030000
#define RNG_SOC_TOP_BASE_PHYS                                       0x610c0000

/*----------------------------------------------------------------------------
 * BASE: MMSS_NOC_SF
 *--------------------------------------------------------------------------*/

#define MMSS_NOC_SF_BASE                                            0x61400000
#define MMSS_NOC_SF_BASE_SIZE                                       0x0005c000
#define MMSS_NOC_SF_BASE_PHYS                                       0x61400000

/*----------------------------------------------------------------------------
 * BASE: MMSS_NOC_HF
 *--------------------------------------------------------------------------*/

#define MMSS_NOC_HF_BASE                                            0x61480000
#define MMSS_NOC_HF_BASE_SIZE                                       0x0005c000
#define MMSS_NOC_HF_BASE_PHYS                                       0x61480000

/*----------------------------------------------------------------------------
 * BASE: TUNNELS_NOC_WRAPPER
 *--------------------------------------------------------------------------*/

#define TUNNELS_NOC_WRAPPER_BASE                                    0x61500000
#define TUNNELS_NOC_WRAPPER_BASE_SIZE                               0x00241400
#define TUNNELS_NOC_WRAPPER_BASE_PHYS                               0x61500000

/*----------------------------------------------------------------------------
 * BASE: PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X2
 *--------------------------------------------------------------------------*/

#define PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X2_BASE                      0x61c00000
#define PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X2_BASE_SIZE                 0x00008000
#define PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X2_BASE_PHYS                 0x61c00000

/*----------------------------------------------------------------------------
 * BASE: PCIE_RSCC
 *--------------------------------------------------------------------------*/

#define PCIE_RSCC_BASE                                              0x61d00000
#define PCIE_RSCC_BASE_SIZE                                         0x00015000
#define PCIE_RSCC_BASE_PHYS                                         0x61d00000

/*----------------------------------------------------------------------------
 * BASE: UFS_MEM_UFS_2LANE_G5_REGS
 *--------------------------------------------------------------------------*/

#define UFS_MEM_UFS_2LANE_G5_REGS_BASE                              0x61d80000
#define UFS_MEM_UFS_2LANE_G5_REGS_BASE_SIZE                         0x00040000
#define UFS_MEM_UFS_2LANE_G5_REGS_BASE_PHYS                         0x61d80000

/*----------------------------------------------------------------------------
 * BASE: CRYPTO0_CRYPTO_TOP
 *--------------------------------------------------------------------------*/

#define CRYPTO0_CRYPTO_TOP_BASE                                     0x61dc0000
#define CRYPTO0_CRYPTO_TOP_BASE_SIZE                                0x00040000
#define CRYPTO0_CRYPTO_TOP_BASE_PHYS                                0x61dc0000

/*----------------------------------------------------------------------------
 * BASE: CORE_TOP_CSR
 *--------------------------------------------------------------------------*/

#define CORE_TOP_CSR_BASE                                           0x61f00000
#define CORE_TOP_CSR_BASE_SIZE                                      0x00100000
#define CORE_TOP_CSR_BASE_PHYS                                      0x61f00000

/*----------------------------------------------------------------------------
 * BASE: GFX
 *--------------------------------------------------------------------------*/

#define GFX_BASE                                                    0x63d00000
#define GFX_BASE_SIZE                                               0x00100000
#define GFX_BASE_PHYS                                               0x63d00000

/*----------------------------------------------------------------------------
 * BASE: IPA_WRAPPER
 *--------------------------------------------------------------------------*/

#define IPA_WRAPPER_BASE                                            0x63e00000
#define IPA_WRAPPER_BASE_SIZE                                       0x00200000
#define IPA_WRAPPER_BASE_PHYS                                       0x63e00000

/*----------------------------------------------------------------------------
 * BASE: MODEM_TOP
 *--------------------------------------------------------------------------*/

#define MODEM_TOP_BASE                                              0x64000000
#define MODEM_TOP_BASE_SIZE                                         0x01000000
#define MODEM_TOP_BASE_PHYS                                         0x64000000

/*----------------------------------------------------------------------------
 * BASE: MSS__QDSP6_TCM
 *--------------------------------------------------------------------------*/

#define MSS__QDSP6_TCM_BASE                                         0x65400000
#define MSS__QDSP6_TCM_BASE_SIZE                                    0x00000000
#define MSS__QDSP6_TCM_BASE_PHYS                                    0x65400000

/*----------------------------------------------------------------------------
 * BASE: MSS__QDSP6_TCM_END
 *--------------------------------------------------------------------------*/

#define MSS__QDSP6_TCM_END_BASE                                     0x657fffff
#define MSS__QDSP6_TCM_END_BASE_SIZE                                0x00000000
#define MSS__QDSP6_TCM_END_BASE_PHYS                                0x657fffff

/*----------------------------------------------------------------------------
 * BASE: LPASS_LPI_TCM
 *--------------------------------------------------------------------------*/

#define LPASS_LPI_TCM_BASE                                          0x66000000
#define LPASS_LPI_TCM_BASE_SIZE                                     0x00000000
#define LPASS_LPI_TCM_BASE_PHYS                                     0x66000000

/*----------------------------------------------------------------------------
 * BASE: LPASS
 *--------------------------------------------------------------------------*/

#define LPASS_BASE                                                  0x66000000
#define LPASS_BASE_SIZE                                             0x02000000
#define LPASS_BASE_PHYS                                             0x66000000

/*----------------------------------------------------------------------------
 * BASE: LPASS_LPI_TCM_END
 *--------------------------------------------------------------------------*/

#define LPASS_LPI_TCM_END_BASE                                      0x6607ffff
#define LPASS_LPI_TCM_END_BASE_SIZE                                 0x00000000
#define LPASS_LPI_TCM_END_BASE_PHYS                                 0x6607ffff

/*----------------------------------------------------------------------------
 * BASE: LPASS_Q6_TCM
 *--------------------------------------------------------------------------*/

#define LPASS_Q6_TCM_BASE                                           0x66400000
#define LPASS_Q6_TCM_BASE_SIZE                                      0x00000000
#define LPASS_Q6_TCM_BASE_PHYS                                      0x66400000

/*----------------------------------------------------------------------------
 * BASE: LPASS_Q6_TCM_END
 *--------------------------------------------------------------------------*/

#define LPASS_Q6_TCM_END_BASE                                       0x6667ffff
#define LPASS_Q6_TCM_END_BASE_SIZE                                  0x00000000
#define LPASS_Q6_TCM_END_BASE_PHYS                                  0x6667ffff

/*----------------------------------------------------------------------------
 * BASE: LPASS_AUDIO_LPM
 *--------------------------------------------------------------------------*/

#define LPASS_AUDIO_LPM_BASE                                        0x66c80000
#define LPASS_AUDIO_LPM_BASE_SIZE                                   0x00000000
#define LPASS_AUDIO_LPM_BASE_PHYS                                   0x66c80000

/*----------------------------------------------------------------------------
 * BASE: LPASS_AUDIO_LPM_END
 *--------------------------------------------------------------------------*/

#define LPASS_AUDIO_LPM_END_BASE                                    0x66c8ffff
#define LPASS_AUDIO_LPM_END_BASE_SIZE                               0x00000000
#define LPASS_AUDIO_LPM_END_BASE_PHYS                               0x66c8ffff

/*----------------------------------------------------------------------------
 * BASE: LPASS_VA_LPM
 *--------------------------------------------------------------------------*/

#define LPASS_VA_LPM_BASE                                           0x66d40000
#define LPASS_VA_LPM_BASE_SIZE                                      0x00000000
#define LPASS_VA_LPM_BASE_PHYS                                      0x66d40000

/*----------------------------------------------------------------------------
 * BASE: LPASS_VA_LPM_END
 *--------------------------------------------------------------------------*/

#define LPASS_VA_LPM_END_BASE                                       0x66d42fff
#define LPASS_VA_LPM_END_BASE_SIZE                                  0x00000000
#define LPASS_VA_LPM_END_BASE_PHYS                                  0x66d42fff

/*----------------------------------------------------------------------------
 * BASE: SSC_SDC_CODE_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define SSC_SDC_CODE_RAM_START_ADDRESS_BASE                         0x67000000
#define SSC_SDC_CODE_RAM_START_ADDRESS_BASE_SIZE                    0x00000000
#define SSC_SDC_CODE_RAM_START_ADDRESS_BASE_PHYS                    0x67000000

/*----------------------------------------------------------------------------
 * BASE: SSC_SDC_CODE_RAM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define SSC_SDC_CODE_RAM_END_ADDRESS_BASE                           0x67017fff
#define SSC_SDC_CODE_RAM_END_ADDRESS_BASE_SIZE                      0x00000000
#define SSC_SDC_CODE_RAM_END_ADDRESS_BASE_PHYS                      0x67017fff

/*----------------------------------------------------------------------------
 * BASE: SSC_SDC_DATA_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define SSC_SDC_DATA_RAM_START_ADDRESS_BASE                         0x670e0000
#define SSC_SDC_DATA_RAM_START_ADDRESS_BASE_SIZE                    0x00000000
#define SSC_SDC_DATA_RAM_START_ADDRESS_BASE_PHYS                    0x670e0000

/*----------------------------------------------------------------------------
 * BASE: SSC_SDC_DATA_RAM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define SSC_SDC_DATA_RAM_END_ADDRESS_BASE                           0x670effff
#define SSC_SDC_DATA_RAM_END_ADDRESS_BASE_SIZE                      0x00000000
#define SSC_SDC_DATA_RAM_END_ADDRESS_BASE_PHYS                      0x670effff

/*----------------------------------------------------------------------------
 * BASE: SSC_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define SSC_RAM_START_ADDRESS_BASE                                  0x67800000
#define SSC_RAM_START_ADDRESS_BASE_SIZE                             0x00000000
#define SSC_RAM_START_ADDRESS_BASE_PHYS                             0x67800000

/*----------------------------------------------------------------------------
 * BASE: SSC_RAM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define SSC_RAM_END_ADDRESS_BASE                                    0x678153ff
#define SSC_RAM_END_ADDRESS_BASE_SIZE                               0x00000000
#define SSC_RAM_END_ADDRESS_BASE_PHYS                               0x678153ff

/*----------------------------------------------------------------------------
 * BASE: LPASS_CORE_LPM
 *--------------------------------------------------------------------------*/

#define LPASS_CORE_LPM_BASE                                         0x67c10000
#define LPASS_CORE_LPM_BASE_SIZE                                    0x00000000
#define LPASS_CORE_LPM_BASE_PHYS                                    0x67c10000

/*----------------------------------------------------------------------------
 * BASE: LPASS_CORE_LPM_END
 *--------------------------------------------------------------------------*/

#define LPASS_CORE_LPM_END_BASE                                     0x67c17fff
#define LPASS_CORE_LPM_END_BASE_SIZE                                0x00000000
#define LPASS_CORE_LPM_END_BASE_PHYS                                0x67c17fff

/*----------------------------------------------------------------------------
 * BASE: PMU_WRAPPER
 *--------------------------------------------------------------------------*/

#define PMU_WRAPPER_BASE                                            0x68400000
#define PMU_WRAPPER_BASE_SIZE                                       0x00200000
#define PMU_WRAPPER_BASE_PHYS                                       0x68400000

/*----------------------------------------------------------------------------
 * BASE: PERIPH_SS_SDC2_SDCC5_TOP
 *--------------------------------------------------------------------------*/

#define PERIPH_SS_SDC2_SDCC5_TOP_BASE                               0x68800000
#define PERIPH_SS_SDC2_SDCC5_TOP_BASE_SIZE                          0x00020000
#define PERIPH_SS_SDC2_SDCC5_TOP_BASE_PHYS                          0x68800000

/*----------------------------------------------------------------------------
 * BASE: VSENSE_CONTROLLER
 *--------------------------------------------------------------------------*/

#define VSENSE_CONTROLLER_BASE                                      0x688c8000
#define VSENSE_CONTROLLER_BASE_SIZE                                 0x00001000
#define VSENSE_CONTROLLER_BASE_PHYS                                 0x688c8000

/*----------------------------------------------------------------------------
 * BASE: PERIPH_SS_PDM_PERPH_WEB
 *--------------------------------------------------------------------------*/

#define PERIPH_SS_PDM_PERPH_WEB_BASE                                0x688d0000
#define PERIPH_SS_PDM_PERPH_WEB_BASE_SIZE                           0x00004000
#define PERIPH_SS_PDM_PERPH_WEB_BASE_PHYS                           0x688d0000

/*----------------------------------------------------------------------------
 * BASE: QSPI_TOP
 *--------------------------------------------------------------------------*/

#define QSPI_TOP_BASE                                               0x688dc000
#define QSPI_TOP_BASE_SIZE                                          0x00004000
#define QSPI_TOP_BASE_PHYS                                          0x688dc000

/*----------------------------------------------------------------------------
 * BASE: AHB2PHY_SOUTH
 *--------------------------------------------------------------------------*/

#define AHB2PHY_SOUTH_BASE                                          0x688e0000
#define AHB2PHY_SOUTH_BASE_SIZE                                     0x00010000
#define AHB2PHY_SOUTH_BASE_PHYS                                     0x688e0000

/*----------------------------------------------------------------------------
 * BASE: WPSS
 *--------------------------------------------------------------------------*/

#define WPSS_BASE                                                   0x68a00000
#define WPSS_BASE_SIZE                                              0x00200000
#define WPSS_BASE_PHYS                                              0x68a00000

/*----------------------------------------------------------------------------
 * BASE: USB3_PRI_USB31_PRIM_MVS_WRAPPER
 *--------------------------------------------------------------------------*/

#define USB3_PRI_USB31_PRIM_MVS_WRAPPER_BASE                        0x6a600000
#define USB3_PRI_USB31_PRIM_MVS_WRAPPER_BASE_SIZE                   0x00200000
#define USB3_PRI_USB31_PRIM_MVS_WRAPPER_BASE_PHYS                   0x6a600000

/*----------------------------------------------------------------------------
 * BASE: IRIS
 *--------------------------------------------------------------------------*/

#define IRIS_BASE                                                   0x6aa00000
#define IRIS_BASE_SIZE                                              0x00200000
#define IRIS_BASE_PHYS                                              0x6aa00000

/*----------------------------------------------------------------------------
 * BASE: TITAN_SS
 *--------------------------------------------------------------------------*/

#define TITAN_SS_BASE                                               0x6ac00000
#define TITAN_SS_BASE_SIZE                                          0x00200000
#define TITAN_SS_BASE_PHYS                                          0x6ac00000

/*----------------------------------------------------------------------------
 * BASE: MDSS
 *--------------------------------------------------------------------------*/

#define MDSS_BASE                                                   0x6ae00000
#define MDSS_BASE_SIZE                                              0x00200000
#define MDSS_BASE_PHYS                                              0x6ae00000

/*----------------------------------------------------------------------------
 * BASE: TLMM
 *--------------------------------------------------------------------------*/

#define TLMM_BASE                                                   0x6f000000
#define TLMM_BASE_SIZE                                              0x01000000
#define TLMM_BASE_PHYS                                              0x6f000000

/*----------------------------------------------------------------------------
 * BASE: QDSS_SOC_DBG
 *--------------------------------------------------------------------------*/

#define QDSS_SOC_DBG_BASE                                           0x70000000
#define QDSS_SOC_DBG_BASE_SIZE                                      0x04000000
#define QDSS_SOC_DBG_BASE_PHYS                                      0x70000000

/*----------------------------------------------------------------------------
 * BASE: SYSTEM_IMEM
 *--------------------------------------------------------------------------*/

#define SYSTEM_IMEM_BASE                                            0x74680000
#define SYSTEM_IMEM_BASE_SIZE                                       0x00000000
#define SYSTEM_IMEM_BASE_PHYS                                       0x74680000

/*----------------------------------------------------------------------------
 * BASE: SYSTEM_IMEM_END
 *--------------------------------------------------------------------------*/

#define SYSTEM_IMEM_END_BASE                                        0x746abfff
#define SYSTEM_IMEM_END_BASE_SIZE                                   0x00000000
#define SYSTEM_IMEM_END_BASE_PHYS                                   0x746abfff

/*----------------------------------------------------------------------------
 * BASE: BOOT_IMEM
 *--------------------------------------------------------------------------*/

#define BOOT_IMEM_BASE                                              0x74800000
#define BOOT_IMEM_BASE_SIZE                                         0x00400000
#define BOOT_IMEM_BASE_PHYS                                         0x74800000

/*----------------------------------------------------------------------------
 * BASE: SMMU_500_APPS_REG_WRAPPER
 *--------------------------------------------------------------------------*/

#define SMMU_500_APPS_REG_WRAPPER_BASE                              0x75000000
#define SMMU_500_APPS_REG_WRAPPER_BASE_SIZE                         0x00200000
#define SMMU_500_APPS_REG_WRAPPER_BASE_PHYS                         0x75000000

/*----------------------------------------------------------------------------
 * BASE: QDSS_STM
 *--------------------------------------------------------------------------*/

#define QDSS_STM_BASE                                               0x76000000
#define QDSS_STM_BASE_SIZE                                          0x00000000
#define QDSS_STM_BASE_PHYS                                          0x76000000

/*----------------------------------------------------------------------------
 * BASE: QDSS_STM_END
 *--------------------------------------------------------------------------*/

#define QDSS_STM_END_BASE                                           0x76ffffff
#define QDSS_STM_END_BASE_SIZE                                      0x00000000
#define QDSS_STM_END_BASE_PHYS                                      0x76ffffff

/*----------------------------------------------------------------------------
 * BASE: APSS_HM
 *--------------------------------------------------------------------------*/

#define APSS_HM_BASE                                                0x77000000
#define APSS_HM_BASE_SIZE                                           0x02000000
#define APSS_HM_BASE_PHYS                                           0x77000000

/*----------------------------------------------------------------------------
 * BASE: DDR_SPACE
 *--------------------------------------------------------------------------*/

#define DDR_SPACE_BASE                                              0x80000000
#define DDR_SPACE_BASE_SIZE                                         0x00000000
#define DDR_SPACE_BASE_PHYS                                         0x80000000

/*----------------------------------------------------------------------------
 * BASE: TURING
 *--------------------------------------------------------------------------*/

#define TURING_BASE                                                 0x88000000
#define TURING_BASE_SIZE                                            0x03000000
#define TURING_BASE_PHYS                                            0x88000000

/*----------------------------------------------------------------------------
 * BASE: TMESS
 *--------------------------------------------------------------------------*/

#define TMESS_BASE                                                  0x90000000
#define TMESS_BASE_SIZE                                             0x02300000
#define TMESS_BASE_PHYS                                             0x90000000

/*----------------------------------------------------------------------------
 * BASE: DDR_SS
 *--------------------------------------------------------------------------*/

#define DDR_SS_BASE                                                 0x94000000
#define DDR_SS_BASE_SIZE                                            0x02000000
#define DDR_SS_BASE_PHYS                                            0x94000000

/*----------------------------------------------------------------------------
 * BASE: DDR_SPACE_END
 *--------------------------------------------------------------------------*/

#define DDR_SPACE_END_BASE                                          0x97ffffff
#define DDR_SPACE_END_BASE_SIZE                                     0x00000000
#define DDR_SPACE_END_BASE_PHYS                                     0x97ffffff

/*----------------------------------------------------------------------------
 * BASE: SC_TCM
 *--------------------------------------------------------------------------*/

#define SC_TCM_BASE                                                 0x98000000
#define SC_TCM_BASE_SIZE                                            0x00000000
#define SC_TCM_BASE_PHYS                                            0x98000000

/*----------------------------------------------------------------------------
 * BASE: MODEM_OFFLINE
 *--------------------------------------------------------------------------*/

#define MODEM_OFFLINE_BASE                                          0x98000000
#define MODEM_OFFLINE_BASE_SIZE                                     0x04000000
#define MODEM_OFFLINE_BASE_PHYS                                     0x98000000

/*----------------------------------------------------------------------------
 * BASE: SC_TCM_END
 *--------------------------------------------------------------------------*/

#define SC_TCM_END_BASE                                             0x9fffffff
#define SC_TCM_END_BASE_SIZE                                        0x00000000
#define SC_TCM_END_BASE_PHYS                                        0x9fffffff

/*----------------------------------------------------------------------------
 * BASE: PCIE_GEN3X2_0_PCIE_WRAPPER_AXI_G3X2
 *--------------------------------------------------------------------------*/

#define PCIE_GEN3X2_0_PCIE_WRAPPER_AXI_G3X2_BASE                    0xd0000000
#define PCIE_GEN3X2_0_PCIE_WRAPPER_AXI_G3X2_BASE_SIZE               0x02000000
#define PCIE_GEN3X2_0_PCIE_WRAPPER_AXI_G3X2_BASE_PHYS               0xd0000000

/*----------------------------------------------------------------------------
 * MEMORY: AOP_SS_MSG_RAM
 *--------------------------------------------------------------------------*/

#define AOP_SS_MSG_RAM                                              0x01300000
#define AOP_SS_MSG_RAM_SIZE                                         0x00100000
#define AOP_SS_MSG_RAM_PHYS                                         0x01300000


#endif /* __MSMHWIOBASE_H__ */
