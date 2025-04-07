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
  
  Copyright (c) 2022 Qualcomm Technologies Incorporated.
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

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/SocPkg/Lanai/Include/msmhwiobase.h#1 $
  $DateTime: 2024/04/02 23:00:31 $
  $Author: cirrusp4svc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * BASE: LPASS_VA_LPM_SIZE
 *--------------------------------------------------------------------------*/

#define LPASS_VA_LPM_SIZE_BASE                                          0x3000
#define LPASS_VA_LPM_SIZE_BASE_SIZE                                 0x00000000
#define LPASS_VA_LPM_SIZE_BASE_PHYS                                 0x00003000

/*----------------------------------------------------------------------------
 * BASE: LPASS_CORE_LPM_SIZE
 *--------------------------------------------------------------------------*/

#define LPASS_CORE_LPM_SIZE_BASE                                        0x8000
#define LPASS_CORE_LPM_SIZE_BASE_SIZE                               0x00000000
#define LPASS_CORE_LPM_SIZE_BASE_PHYS                               0x00008000

/*----------------------------------------------------------------------------
 * BASE: LPASS_AUDIO_LPM_SIZE
 *--------------------------------------------------------------------------*/

#define LPASS_AUDIO_LPM_SIZE_BASE                                      0x10000
#define LPASS_AUDIO_LPM_SIZE_BASE_SIZE                              0x00000000
#define LPASS_AUDIO_LPM_SIZE_BASE_PHYS                              0x00010000

/*----------------------------------------------------------------------------
 * BASE: SSC_SDC_DATA_RAM_SIZE
 *--------------------------------------------------------------------------*/

#define SSC_SDC_DATA_RAM_SIZE_BASE                                     0x10000
#define SSC_SDC_DATA_RAM_SIZE_BASE_SIZE                             0x00000000
#define SSC_SDC_DATA_RAM_SIZE_BASE_PHYS                             0x00010000

/*----------------------------------------------------------------------------
 * BASE: SSC_RAM_SIZE
 *--------------------------------------------------------------------------*/

#define SSC_RAM_SIZE_BASE                                              0x15400
#define SSC_RAM_SIZE_BASE_SIZE                                      0x00000000
#define SSC_RAM_SIZE_BASE_PHYS                                      0x00015400

/*----------------------------------------------------------------------------
 * BASE: SSC_SDC_CODE_RAM_SIZE
 *--------------------------------------------------------------------------*/

#define SSC_SDC_CODE_RAM_SIZE_BASE                                     0x18000
#define SSC_SDC_CODE_RAM_SIZE_BASE_SIZE                             0x00000000
#define SSC_SDC_CODE_RAM_SIZE_BASE_PHYS                             0x00018000

/*----------------------------------------------------------------------------
 * BASE: SYSTEM_IMEM_SIZE
 *--------------------------------------------------------------------------*/

#define SYSTEM_IMEM_SIZE_BASE                                          0x2c000
#define SYSTEM_IMEM_SIZE_BASE_SIZE                                  0x00000000
#define SYSTEM_IMEM_SIZE_BASE_PHYS                                  0x0002c000

/*----------------------------------------------------------------------------
 * BASE: AOP_SS_MSG_RAM_DRV14
 *--------------------------------------------------------------------------*/

#define AOP_SS_MSG_RAM_DRV14_BASE                                      0xe0000
#define AOP_SS_MSG_RAM_DRV14_BASE_SIZE                              0x00000000
#define AOP_SS_MSG_RAM_DRV14_BASE_PHYS                              0x000e0000

/*----------------------------------------------------------------------------
 * BASE: AOP_SS_MSG_RAM_DRV15
 *--------------------------------------------------------------------------*/

#define AOP_SS_MSG_RAM_DRV15_BASE                                      0xf0000
#define AOP_SS_MSG_RAM_DRV15_BASE_SIZE                              0x00000000
#define AOP_SS_MSG_RAM_DRV15_BASE_PHYS                              0x000f0000

/*----------------------------------------------------------------------------
 * BASE: CLK_CTL
 *--------------------------------------------------------------------------*/

#define CLK_CTL_BASE                                                  0x100000
#define CLK_CTL_BASE_SIZE                                           0x00200000
#define CLK_CTL_BASE_PHYS                                           0x00100000

/*----------------------------------------------------------------------------
 * BASE: LPASS_LPI_TCM_SIZE
 *--------------------------------------------------------------------------*/

#define LPASS_LPI_TCM_SIZE_BASE                                       0x200000
#define LPASS_LPI_TCM_SIZE_BASE_SIZE                                0x00000000
#define LPASS_LPI_TCM_SIZE_BASE_PHYS                                0x00200000

/*----------------------------------------------------------------------------
 * BASE: LPASS_Q6_TCM_SIZE
 *--------------------------------------------------------------------------*/

#define LPASS_Q6_TCM_SIZE_BASE                                        0x200000
#define LPASS_Q6_TCM_SIZE_BASE_SIZE                                 0x00000000
#define LPASS_Q6_TCM_SIZE_BASE_PHYS                                 0x00200000

/*----------------------------------------------------------------------------
 * BASE: BOOT_ROM
 *--------------------------------------------------------------------------*/

#define BOOT_ROM_BASE                                                 0x300000
#define BOOT_ROM_BASE_SIZE                                          0x00100000
#define BOOT_ROM_BASE_PHYS                                          0x00300000

/*----------------------------------------------------------------------------
 * BASE: MSS__QDSP6_TCM_SIZE
 *--------------------------------------------------------------------------*/

#define MSS__QDSP6_TCM_SIZE_BASE                                      0x400000
#define MSS__QDSP6_TCM_SIZE_BASE_SIZE                               0x00000000
#define MSS__QDSP6_TCM_SIZE_BASE_PHYS                               0x00400000

/*----------------------------------------------------------------------------
 * BASE: SC_TCM_SIZE
 *--------------------------------------------------------------------------*/

#define SC_TCM_SIZE_BASE                                              0x400000
#define SC_TCM_SIZE_BASE_SIZE                                       0x00000000
#define SC_TCM_SIZE_BASE_PHYS                                       0x00400000

/*----------------------------------------------------------------------------
 * BASE: IPC_ROUTER_TOP
 *--------------------------------------------------------------------------*/

#define IPC_ROUTER_TOP_BASE                                           0x400000
#define IPC_ROUTER_TOP_BASE_SIZE                                    0x00200000
#define IPC_ROUTER_TOP_BASE_PHYS                                    0x00400000

/*----------------------------------------------------------------------------
 * BASE: OCIMEM_WRAPPER_CSR
 *--------------------------------------------------------------------------*/

#define OCIMEM_WRAPPER_CSR_BASE                                       0x618000
#define OCIMEM_WRAPPER_CSR_BASE_SIZE                                0x00006000
#define OCIMEM_WRAPPER_CSR_BASE_PHYS                                0x00618000

/*----------------------------------------------------------------------------
 * BASE: CX_CPR3
 *--------------------------------------------------------------------------*/

#define CX_CPR3_BASE                                                  0x628000
#define CX_CPR3_BASE_SIZE                                           0x00004000
#define CX_CPR3_BASE_PHYS                                           0x00628000

/*----------------------------------------------------------------------------
 * BASE: MXC_CPR3
 *--------------------------------------------------------------------------*/

#define MXC_CPR3_BASE                                                 0x62c000
#define MXC_CPR3_BASE_SIZE                                          0x00004000
#define MXC_CPR3_BASE_PHYS                                          0x0062c000

/*----------------------------------------------------------------------------
 * BASE: MMCX_CPR3
 *--------------------------------------------------------------------------*/

#define MMCX_CPR3_BASE                                                0x630000
#define MMCX_CPR3_BASE_SIZE                                         0x00004000
#define MMCX_CPR3_BASE_PHYS                                         0x00630000

/*----------------------------------------------------------------------------
 * BASE: HMX_CPR3
 *--------------------------------------------------------------------------*/

#define HMX_CPR3_BASE                                                 0x634000
#define HMX_CPR3_BASE_SIZE                                          0x00004000
#define HMX_CPR3_BASE_PHYS                                          0x00634000

/*----------------------------------------------------------------------------
 * BASE: MX_CPR3
 *--------------------------------------------------------------------------*/

#define MX_CPR3_BASE                                                  0x638000
#define MX_CPR3_BASE_SIZE                                           0x00004000
#define MX_CPR3_BASE_PHYS                                           0x00638000

/*----------------------------------------------------------------------------
 * BASE: NSP_CX_CPR3
 *--------------------------------------------------------------------------*/

#define NSP_CX_CPR3_BASE                                              0x63c000
#define NSP_CX_CPR3_BASE_SIZE                                       0x00004000
#define NSP_CX_CPR3_BASE_PHYS                                       0x0063c000

/*----------------------------------------------------------------------------
 * BASE: RDPM_CXRDPM_TOP
 *--------------------------------------------------------------------------*/

#define RDPM_CXRDPM_TOP_BASE                                          0x640000
#define RDPM_CXRDPM_TOP_BASE_SIZE                                   0x00010000
#define RDPM_CXRDPM_TOP_BASE_PHYS                                   0x00640000

/*----------------------------------------------------------------------------
 * BASE: RDPM_MXC_RDPM_TOP
 *--------------------------------------------------------------------------*/

#define RDPM_MXC_RDPM_TOP_BASE                                        0x650000
#define RDPM_MXC_RDPM_TOP_BASE_SIZE                                 0x00010000
#define RDPM_MXC_RDPM_TOP_BASE_PHYS                                 0x00650000

/*----------------------------------------------------------------------------
 * BASE: RDPM_MXA_RDPM_TOP
 *--------------------------------------------------------------------------*/

#define RDPM_MXA_RDPM_TOP_BASE                                        0x660000
#define RDPM_MXA_RDPM_TOP_BASE_SIZE                                 0x00010000
#define RDPM_MXA_RDPM_TOP_BASE_PHYS                                 0x00660000

/*----------------------------------------------------------------------------
 * BASE: QTB_NOC_LPASS
 *--------------------------------------------------------------------------*/

#define QTB_NOC_LPASS_BASE                                            0x7b0000
#define QTB_NOC_LPASS_BASE_SIZE                                     0x0000f080
#define QTB_NOC_LPASS_BASE_PHYS                                     0x007b0000

/*----------------------------------------------------------------------------
 * BASE: QTB_NOC_NSP
 *--------------------------------------------------------------------------*/

#define QTB_NOC_NSP_BASE                                              0x7d0000
#define QTB_NOC_NSP_BASE_SIZE                                       0x00010080
#define QTB_NOC_NSP_BASE_PHYS                                       0x007d0000

/*----------------------------------------------------------------------------
 * BASE: QUPV3_2_QUPV3_ID_2
 *--------------------------------------------------------------------------*/

#define QUPV3_2_QUPV3_ID_2_BASE                                       0x800000
#define QUPV3_2_QUPV3_ID_2_BASE_SIZE                                0x00100000
#define QUPV3_2_QUPV3_ID_2_BASE_PHYS                                0x00800000

/*----------------------------------------------------------------------------
 * BASE: I2C_MASTER_0
 *--------------------------------------------------------------------------*/

#define I2C_MASTER_0_BASE                                             0x900000
#define I2C_MASTER_0_BASE_SIZE                                      0x00100000
#define I2C_MASTER_0_BASE_PHYS                                      0x00900000

/*----------------------------------------------------------------------------
 * BASE: QUPV3_1_QUPV3_ID_1
 *--------------------------------------------------------------------------*/

#define QUPV3_1_QUPV3_ID_1_BASE                                       0xa00000
#define QUPV3_1_QUPV3_ID_1_BASE_SIZE                                0x00100000
#define QUPV3_1_QUPV3_ID_1_BASE_PHYS                                0x00a00000

/*----------------------------------------------------------------------------
 * BASE: IBI_0_I3C_IBI_CTRL_ID_1
 *--------------------------------------------------------------------------*/

#define IBI_0_I3C_IBI_CTRL_ID_1_BASE                                  0xb00000
#define IBI_0_I3C_IBI_CTRL_ID_1_BASE_SIZE                           0x00010000
#define IBI_0_I3C_IBI_CTRL_ID_1_BASE_PHYS                           0x00b00000

/*----------------------------------------------------------------------------
 * BASE: IBI_1_I3C_IBI_CTRL_ID_1
 *--------------------------------------------------------------------------*/

#define IBI_1_I3C_IBI_CTRL_ID_1_BASE                                  0xb10000
#define IBI_1_I3C_IBI_CTRL_ID_1_BASE_SIZE                           0x00010000
#define IBI_1_I3C_IBI_CTRL_ID_1_BASE_PHYS                           0x00b10000

/*----------------------------------------------------------------------------
 * BASE: QUPV3_02_QUPV3_ID_4
 *--------------------------------------------------------------------------*/

#define QUPV3_02_QUPV3_ID_4_BASE                                      0xc00000
#define QUPV3_02_QUPV3_ID_4_BASE_SIZE                               0x00100000
#define QUPV3_02_QUPV3_ID_4_BASE_PHYS                               0x00c00000

/*----------------------------------------------------------------------------
 * BASE: AHB2PHY_NORTH
 *--------------------------------------------------------------------------*/

#define AHB2PHY_NORTH_BASE                                            0xff0000
#define AHB2PHY_NORTH_BASE_SIZE                                     0x00004000
#define AHB2PHY_NORTH_BASE_PHYS                                     0x00ff0000

/*----------------------------------------------------------------------------
 * BASE: SNOC_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define SNOC_THROTTLE_THROTTLE_WRAPPER_1_BASE                         0xff4000
#define SNOC_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE                  0x00001000
#define SNOC_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS                  0x00ff4000

/*----------------------------------------------------------------------------
 * BASE: PCIE_THROTTLE_THROTTLE_BWMON_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define PCIE_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE                   0xff5000
#define PCIE_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE_SIZE            0x00001000
#define PCIE_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE_PHYS            0x00ff5000

/*----------------------------------------------------------------------------
 * BASE: GIC_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define GIC_THROTTLE_THROTTLE_WRAPPER_1_BASE                          0xff6000
#define GIC_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE                   0x00001000
#define GIC_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS                   0x00ff6000

/*----------------------------------------------------------------------------
 * BASE: MODEM_DEMBACK_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define MODEM_DEMBACK_THROTTLE_THROTTLE_WRAPPER_1_BASE                0xffd000
#define MODEM_DEMBACK_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE         0x00001000
#define MODEM_DEMBACK_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS         0x00ffd000

/*----------------------------------------------------------------------------
 * BASE: MODEM_DSP_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define MODEM_DSP_THROTTLE_THROTTLE_WRAPPER_1_BASE                    0xffe000
#define MODEM_DSP_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE             0x00001000
#define MODEM_DSP_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS             0x00ffe000

/*----------------------------------------------------------------------------
 * BASE: NSP_HCP_THROTTLE_THROTTLE_BWMON_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define NSP_HCP_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE                0xfff000
#define NSP_HCP_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE_SIZE         0x00001000
#define NSP_HCP_THROTTLE_THROTTLE_BWMON_WRAPPER_1_BASE_PHYS         0x00fff000

/*----------------------------------------------------------------------------
 * BASE: QDSS_STM_SIZE
 *--------------------------------------------------------------------------*/

#define QDSS_STM_SIZE_BASE                                           0x1000000
#define QDSS_STM_SIZE_BASE_SIZE                                     0x00000000
#define QDSS_STM_SIZE_BASE_PHYS                                     0x01000000

/*----------------------------------------------------------------------------
 * BASE: TITAN_THROTTLE_RT_THROTTLE_WRAPPER_2
 *--------------------------------------------------------------------------*/

#define TITAN_THROTTLE_RT_THROTTLE_WRAPPER_2_BASE                    0x1000000
#define TITAN_THROTTLE_RT_THROTTLE_WRAPPER_2_BASE_SIZE              0x00001000
#define TITAN_THROTTLE_RT_THROTTLE_WRAPPER_2_BASE_PHYS              0x01000000

/*----------------------------------------------------------------------------
 * BASE: ANOC2_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define ANOC2_THROTTLE_THROTTLE_WRAPPER_1_BASE                       0x1001000
#define ANOC2_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE                 0x00001000
#define ANOC2_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS                 0x01001000

/*----------------------------------------------------------------------------
 * BASE: VIDEO_THROTTLE_VCODEC_THROTTLE_BWMON_WRAPPER_2
 *--------------------------------------------------------------------------*/

#define VIDEO_THROTTLE_VCODEC_THROTTLE_BWMON_WRAPPER_2_BASE          0x1002000
#define VIDEO_THROTTLE_VCODEC_THROTTLE_BWMON_WRAPPER_2_BASE_SIZE    0x00001000
#define VIDEO_THROTTLE_VCODEC_THROTTLE_BWMON_WRAPPER_2_BASE_PHYS    0x01002000

/*----------------------------------------------------------------------------
 * BASE: TITAN_THROTTLE_NRT_THROTTLE_WRAPPER_3
 *--------------------------------------------------------------------------*/

#define TITAN_THROTTLE_NRT_THROTTLE_WRAPPER_3_BASE                   0x1003000
#define TITAN_THROTTLE_NRT_THROTTLE_WRAPPER_3_BASE_SIZE             0x00001000
#define TITAN_THROTTLE_NRT_THROTTLE_WRAPPER_3_BASE_PHYS             0x01003000

/*----------------------------------------------------------------------------
 * BASE: VIDEO_THROTTLE_CVP_THROTTLE_BWMON_WRAPPER_2
 *--------------------------------------------------------------------------*/

#define VIDEO_THROTTLE_CVP_THROTTLE_BWMON_WRAPPER_2_BASE             0x1004000
#define VIDEO_THROTTLE_CVP_THROTTLE_BWMON_WRAPPER_2_BASE_SIZE       0x00001000
#define VIDEO_THROTTLE_CVP_THROTTLE_BWMON_WRAPPER_2_BASE_PHYS       0x01004000

/*----------------------------------------------------------------------------
 * BASE: ANOC1_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define ANOC1_THROTTLE_THROTTLE_WRAPPER_1_BASE                       0x1005000
#define ANOC1_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE                 0x00001000
#define ANOC1_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS                 0x01005000

/*----------------------------------------------------------------------------
 * BASE: VENUS_V_CPU_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define VENUS_V_CPU_THROTTLE_THROTTLE_WRAPPER_1_BASE                 0x1006000
#define VENUS_V_CPU_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE           0x00001000
#define VENUS_V_CPU_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS           0x01006000

/*----------------------------------------------------------------------------
 * BASE: VENUS_CV_CPU_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define VENUS_CV_CPU_THROTTLE_THROTTLE_WRAPPER_1_BASE                0x1007000
#define VENUS_CV_CPU_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE          0x00001000
#define VENUS_CV_CPU_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS          0x01007000

/*----------------------------------------------------------------------------
 * BASE: GPU_TCU_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define GPU_TCU_THROTTLE_THROTTLE_WRAPPER_1_BASE                     0x1040000
#define GPU_TCU_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE               0x00001000
#define GPU_TCU_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS               0x01040000

/*----------------------------------------------------------------------------
 * BASE: LPASS_THROTTLE_THROTTLE_WRAPPER_1
 *--------------------------------------------------------------------------*/

#define LPASS_THROTTLE_THROTTLE_WRAPPER_1_BASE                       0x1041000
#define LPASS_THROTTLE_THROTTLE_WRAPPER_1_BASE_SIZE                 0x00001000
#define LPASS_THROTTLE_THROTTLE_WRAPPER_1_BASE_PHYS                 0x01041000

/*----------------------------------------------------------------------------
 * BASE: QM
 *--------------------------------------------------------------------------*/

#define QM_BASE                                                      0x10b8000
#define QM_BASE_SIZE                                                0x00004000
#define QM_BASE_PHYS                                                0x010b8000

/*----------------------------------------------------------------------------
 * BASE: QM_MPU_CFG_QM_MPU_WRAPPER
 *--------------------------------------------------------------------------*/

#define QM_MPU_CFG_QM_MPU_WRAPPER_BASE                               0x10bc000
#define QM_MPU_CFG_QM_MPU_WRAPPER_BASE_SIZE                         0x00004000
#define QM_MPU_CFG_QM_MPU_WRAPPER_BASE_PHYS                         0x010bc000

/*----------------------------------------------------------------------------
 * BASE: RNG_SOC_TOP
 *--------------------------------------------------------------------------*/

#define RNG_SOC_TOP_BASE                                             0x10c0000
#define RNG_SOC_TOP_BASE_SIZE                                       0x00030000
#define RNG_SOC_TOP_BASE_PHYS                                       0x010c0000

/*----------------------------------------------------------------------------
 * BASE: TUNNELS_NOC_WRAPPER
 *--------------------------------------------------------------------------*/

#define TUNNELS_NOC_WRAPPER_BASE                                     0x1500000
#define TUNNELS_NOC_WRAPPER_BASE_SIZE                               0x00241400
#define TUNNELS_NOC_WRAPPER_BASE_PHYS                               0x01500000

/*----------------------------------------------------------------------------
 * BASE: MMSS_NOC
 *--------------------------------------------------------------------------*/

#define MMSS_NOC_BASE                                                0x1780000
#define MMSS_NOC_BASE_SIZE                                          0x0005b800
#define MMSS_NOC_BASE_PHYS                                          0x01780000

/*----------------------------------------------------------------------------
 * BASE: SP_SCSR
 *--------------------------------------------------------------------------*/

#define SP_SCSR_BASE                                                 0x1800000
#define SP_SCSR_BASE_SIZE                                           0x000a0000
#define SP_SCSR_BASE_PHYS                                           0x01800000

/*----------------------------------------------------------------------------
 * BASE: PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X2
 *--------------------------------------------------------------------------*/

#define PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X2_BASE                       0x1c00000
#define PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X2_BASE_SIZE                 0x00008000
#define PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X2_BASE_PHYS                 0x01c00000

/*----------------------------------------------------------------------------
 * BASE: PCIE1_PCIE_WRAPPER_AHB_W_PHY_G4X2
 *--------------------------------------------------------------------------*/

#define PCIE1_PCIE_WRAPPER_AHB_W_PHY_G4X2_BASE                       0x1c08000
#define PCIE1_PCIE_WRAPPER_AHB_W_PHY_G4X2_BASE_SIZE                 0x00008000
#define PCIE1_PCIE_WRAPPER_AHB_W_PHY_G4X2_BASE_PHYS                 0x01c08000

/*----------------------------------------------------------------------------
 * BASE: PCIE_RSCC
 *--------------------------------------------------------------------------*/

#define PCIE_RSCC_BASE                                               0x1d00000
#define PCIE_RSCC_BASE_SIZE                                         0x00015000
#define PCIE_RSCC_BASE_PHYS                                         0x01d00000

/*----------------------------------------------------------------------------
 * BASE: UFS_MEM_UFS_2LANE_G5_REGS
 *--------------------------------------------------------------------------*/

#define UFS_MEM_UFS_2LANE_G5_REGS_BASE                               0x1d80000
#define UFS_MEM_UFS_2LANE_G5_REGS_BASE_SIZE                         0x00040000
#define UFS_MEM_UFS_2LANE_G5_REGS_BASE_PHYS                         0x01d80000

/*----------------------------------------------------------------------------
 * BASE: CRYPTO0_CRYPTO_TOP
 *--------------------------------------------------------------------------*/

#define CRYPTO0_CRYPTO_TOP_BASE                                      0x1dc0000
#define CRYPTO0_CRYPTO_TOP_BASE_SIZE                                0x00040000
#define CRYPTO0_CRYPTO_TOP_BASE_PHYS                                0x01dc0000

/*----------------------------------------------------------------------------
 * BASE: CORE_TOP_CSR
 *--------------------------------------------------------------------------*/

#define CORE_TOP_CSR_BASE                                            0x1f00000
#define CORE_TOP_CSR_BASE_SIZE                                      0x00100000
#define CORE_TOP_CSR_BASE_PHYS                                      0x01f00000

/*----------------------------------------------------------------------------
 * BASE: GFX
 *--------------------------------------------------------------------------*/

#define GFX_BASE                                                     0x3d00000
#define GFX_BASE_SIZE                                               0x00100000
#define GFX_BASE_PHYS                                               0x03d00000

/*----------------------------------------------------------------------------
 * BASE: IPA_WRAPPER
 *--------------------------------------------------------------------------*/

#define IPA_WRAPPER_BASE                                             0x3e00000
#define IPA_WRAPPER_BASE_SIZE                                       0x00200000
#define IPA_WRAPPER_BASE_PHYS                                       0x03e00000

/*----------------------------------------------------------------------------
 * BASE: PCIE_GEN3X2_SPACE_0_SIZE
 *--------------------------------------------------------------------------*/

#define PCIE_GEN3X2_SPACE_0_SIZE_BASE                                0x4000000
#define PCIE_GEN3X2_SPACE_0_SIZE_BASE_SIZE                          0x00000000
#define PCIE_GEN3X2_SPACE_0_SIZE_BASE_PHYS                          0x04000000

/*----------------------------------------------------------------------------
 * BASE: MODEM_TOP
 *--------------------------------------------------------------------------*/

#define MODEM_TOP_BASE                                               0x4000000
#define MODEM_TOP_BASE_SIZE                                         0x01000000
#define MODEM_TOP_BASE_PHYS                                         0x04000000

/*----------------------------------------------------------------------------
 * BASE: MSS__QDSP6_TCM
 *--------------------------------------------------------------------------*/

#define MSS__QDSP6_TCM_BASE                                          0x5400000
#define MSS__QDSP6_TCM_BASE_SIZE                                    0x00000000
#define MSS__QDSP6_TCM_BASE_PHYS                                    0x05400000

/*----------------------------------------------------------------------------
 * BASE: MSS__QDSP6_TCM_END
 *--------------------------------------------------------------------------*/

#define MSS__QDSP6_TCM_END_BASE                                      0x57fffff
#define MSS__QDSP6_TCM_END_BASE_SIZE                                0x00000000
#define MSS__QDSP6_TCM_END_BASE_PHYS                                0x057fffff

/*----------------------------------------------------------------------------
 * BASE: LPASS_LPI_TCM
 *--------------------------------------------------------------------------*/

#define LPASS_LPI_TCM_BASE                                           0x6000000
#define LPASS_LPI_TCM_BASE_SIZE                                     0x00000000
#define LPASS_LPI_TCM_BASE_PHYS                                     0x06000000

/*----------------------------------------------------------------------------
 * BASE: LPASS
 *--------------------------------------------------------------------------*/

#define LPASS_BASE                                                   0x6000000
#define LPASS_BASE_SIZE                                             0x02000000
#define LPASS_BASE_PHYS                                             0x06000000

/*----------------------------------------------------------------------------
 * BASE: LPASS_LPI_TCM_END
 *--------------------------------------------------------------------------*/

#define LPASS_LPI_TCM_END_BASE                                       0x61fffff
#define LPASS_LPI_TCM_END_BASE_SIZE                                 0x00000000
#define LPASS_LPI_TCM_END_BASE_PHYS                                 0x061fffff

/*----------------------------------------------------------------------------
 * BASE: LPASS_Q6_TCM
 *--------------------------------------------------------------------------*/

#define LPASS_Q6_TCM_BASE                                            0x6400000
#define LPASS_Q6_TCM_BASE_SIZE                                      0x00000000
#define LPASS_Q6_TCM_BASE_PHYS                                      0x06400000

/*----------------------------------------------------------------------------
 * BASE: LPASS_Q6_TCM_END
 *--------------------------------------------------------------------------*/

#define LPASS_Q6_TCM_END_BASE                                        0x65fffff
#define LPASS_Q6_TCM_END_BASE_SIZE                                  0x00000000
#define LPASS_Q6_TCM_END_BASE_PHYS                                  0x065fffff

/*----------------------------------------------------------------------------
 * BASE: LPASS_AUDIO_LPM
 *--------------------------------------------------------------------------*/

#define LPASS_AUDIO_LPM_BASE                                         0x6c80000
#define LPASS_AUDIO_LPM_BASE_SIZE                                   0x00000000
#define LPASS_AUDIO_LPM_BASE_PHYS                                   0x06c80000

/*----------------------------------------------------------------------------
 * BASE: LPASS_AUDIO_LPM_END
 *--------------------------------------------------------------------------*/

#define LPASS_AUDIO_LPM_END_BASE                                     0x6c8ffff
#define LPASS_AUDIO_LPM_END_BASE_SIZE                               0x00000000
#define LPASS_AUDIO_LPM_END_BASE_PHYS                               0x06c8ffff

/*----------------------------------------------------------------------------
 * BASE: LPASS_VA_LPM
 *--------------------------------------------------------------------------*/

#define LPASS_VA_LPM_BASE                                            0x6d40000
#define LPASS_VA_LPM_BASE_SIZE                                      0x00000000
#define LPASS_VA_LPM_BASE_PHYS                                      0x06d40000

/*----------------------------------------------------------------------------
 * BASE: LPASS_VA_LPM_END
 *--------------------------------------------------------------------------*/

#define LPASS_VA_LPM_END_BASE                                        0x6d42fff
#define LPASS_VA_LPM_END_BASE_SIZE                                  0x00000000
#define LPASS_VA_LPM_END_BASE_PHYS                                  0x06d42fff

/*----------------------------------------------------------------------------
 * BASE: SSC_SDC_CODE_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define SSC_SDC_CODE_RAM_START_ADDRESS_BASE                          0x7000000
#define SSC_SDC_CODE_RAM_START_ADDRESS_BASE_SIZE                    0x00000000
#define SSC_SDC_CODE_RAM_START_ADDRESS_BASE_PHYS                    0x07000000

/*----------------------------------------------------------------------------
 * BASE: SSC_SDC_CODE_RAM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define SSC_SDC_CODE_RAM_END_ADDRESS_BASE                            0x7017fff
#define SSC_SDC_CODE_RAM_END_ADDRESS_BASE_SIZE                      0x00000000
#define SSC_SDC_CODE_RAM_END_ADDRESS_BASE_PHYS                      0x07017fff

/*----------------------------------------------------------------------------
 * BASE: SSC_SDC_DATA_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define SSC_SDC_DATA_RAM_START_ADDRESS_BASE                          0x70e0000
#define SSC_SDC_DATA_RAM_START_ADDRESS_BASE_SIZE                    0x00000000
#define SSC_SDC_DATA_RAM_START_ADDRESS_BASE_PHYS                    0x070e0000

/*----------------------------------------------------------------------------
 * BASE: SSC_SDC_DATA_RAM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define SSC_SDC_DATA_RAM_END_ADDRESS_BASE                            0x70effff
#define SSC_SDC_DATA_RAM_END_ADDRESS_BASE_SIZE                      0x00000000
#define SSC_SDC_DATA_RAM_END_ADDRESS_BASE_PHYS                      0x070effff

/*----------------------------------------------------------------------------
 * BASE: SSC_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define SSC_RAM_START_ADDRESS_BASE                                   0x7800000
#define SSC_RAM_START_ADDRESS_BASE_SIZE                             0x00000000
#define SSC_RAM_START_ADDRESS_BASE_PHYS                             0x07800000

/*----------------------------------------------------------------------------
 * BASE: SSC_RAM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define SSC_RAM_END_ADDRESS_BASE                                     0x78153ff
#define SSC_RAM_END_ADDRESS_BASE_SIZE                               0x00000000
#define SSC_RAM_END_ADDRESS_BASE_PHYS                               0x078153ff

/*----------------------------------------------------------------------------
 * BASE: LPASS_CORE_LPM
 *--------------------------------------------------------------------------*/

#define LPASS_CORE_LPM_BASE                                          0x7c10000
#define LPASS_CORE_LPM_BASE_SIZE                                    0x00000000
#define LPASS_CORE_LPM_BASE_PHYS                                    0x07c10000

/*----------------------------------------------------------------------------
 * BASE: LPASS_CORE_LPM_END
 *--------------------------------------------------------------------------*/

#define LPASS_CORE_LPM_END_BASE                                      0x7c17fff
#define LPASS_CORE_LPM_END_BASE_SIZE                                0x00000000
#define LPASS_CORE_LPM_END_BASE_PHYS                                0x07c17fff

/*----------------------------------------------------------------------------
 * BASE: PMU_WRAPPER
 *--------------------------------------------------------------------------*/

#define PMU_WRAPPER_BASE                                             0x8400000
#define PMU_WRAPPER_BASE_SIZE                                       0x00200000
#define PMU_WRAPPER_BASE_PHYS                                       0x08400000

/*----------------------------------------------------------------------------
 * BASE: PERIPH_SS_SDC2_SDCC5_TOP
 *--------------------------------------------------------------------------*/

#define PERIPH_SS_SDC2_SDCC5_TOP_BASE                                0x8800000
#define PERIPH_SS_SDC2_SDCC5_TOP_BASE_SIZE                          0x00020000
#define PERIPH_SS_SDC2_SDCC5_TOP_BASE_PHYS                          0x08800000

/*----------------------------------------------------------------------------
 * BASE: PERIPH_SS_SDC4_SDCC5_TOP
 *--------------------------------------------------------------------------*/

#define PERIPH_SS_SDC4_SDCC5_TOP_BASE                                0x8840000
#define PERIPH_SS_SDC4_SDCC5_TOP_BASE_SIZE                          0x00020000
#define PERIPH_SS_SDC4_SDCC5_TOP_BASE_PHYS                          0x08840000

/*----------------------------------------------------------------------------
 * BASE: VSENSE_CONTROLLER
 *--------------------------------------------------------------------------*/

#define VSENSE_CONTROLLER_BASE                                       0x88c8000
#define VSENSE_CONTROLLER_BASE_SIZE                                 0x00001000
#define VSENSE_CONTROLLER_BASE_PHYS                                 0x088c8000

/*----------------------------------------------------------------------------
 * BASE: PERIPH_SS_PDM_PERPH_WEB
 *--------------------------------------------------------------------------*/

#define PERIPH_SS_PDM_PERPH_WEB_BASE                                 0x88d0000
#define PERIPH_SS_PDM_PERPH_WEB_BASE_SIZE                           0x00004000
#define PERIPH_SS_PDM_PERPH_WEB_BASE_PHYS                           0x088d0000

/*----------------------------------------------------------------------------
 * BASE: QSPI_TOP
 *--------------------------------------------------------------------------*/

#define QSPI_TOP_BASE                                                0x88dc000
#define QSPI_TOP_BASE_SIZE                                          0x00004000
#define QSPI_TOP_BASE_PHYS                                          0x088dc000

/*----------------------------------------------------------------------------
 * BASE: AHB2PHY_SOUTH
 *--------------------------------------------------------------------------*/

#define AHB2PHY_SOUTH_BASE                                           0x88e0000
#define AHB2PHY_SOUTH_BASE_SIZE                                     0x00010000
#define AHB2PHY_SOUTH_BASE_PHYS                                     0x088e0000

/*----------------------------------------------------------------------------
 * BASE: USB3_PRI_USB31_PRIM_MVS_WRAPPER
 *--------------------------------------------------------------------------*/

#define USB3_PRI_USB31_PRIM_MVS_WRAPPER_BASE                         0xa600000
#define USB3_PRI_USB31_PRIM_MVS_WRAPPER_BASE_SIZE                   0x00200000
#define USB3_PRI_USB31_PRIM_MVS_WRAPPER_BASE_PHYS                   0x0a600000

/*----------------------------------------------------------------------------
 * BASE: IRIS
 *--------------------------------------------------------------------------*/

#define IRIS_BASE                                                    0xaa00000
#define IRIS_BASE_SIZE                                              0x00200000
#define IRIS_BASE_PHYS                                              0x0aa00000

/*----------------------------------------------------------------------------
 * BASE: TITAN_SS
 *--------------------------------------------------------------------------*/

#define TITAN_SS_BASE                                                0xac00000
#define TITAN_SS_BASE_SIZE                                          0x00200000
#define TITAN_SS_BASE_PHYS                                          0x0ac00000

/*----------------------------------------------------------------------------
 * BASE: MDSS
 *--------------------------------------------------------------------------*/

#define MDSS_BASE                                                    0xae00000
#define MDSS_BASE_SIZE                                              0x00200000
#define MDSS_BASE_PHYS                                              0x0ae00000

/*----------------------------------------------------------------------------
 * BASE: AOSS
 *--------------------------------------------------------------------------*/

#define AOSS_BASE                                                    0xb000000
#define AOSS_BASE_SIZE                                              0x04000000
#define AOSS_BASE_PHYS                                              0x0b000000

/*----------------------------------------------------------------------------
 * BASE: AOP_SS_MSG_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define AOP_SS_MSG_RAM_START_ADDRESS_BASE                            0xc300000
#define AOP_SS_MSG_RAM_START_ADDRESS_BASE_SIZE                      0x00000000
#define AOP_SS_MSG_RAM_START_ADDRESS_BASE_PHYS                      0x0c300000

/*----------------------------------------------------------------------------
 * BASE: TLMM
 *--------------------------------------------------------------------------*/

#define TLMM_BASE                                                    0xf000000
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
 * BASE: BOOT2_BOOT_IMEM
 *--------------------------------------------------------------------------*/

#define BOOT2_BOOT_IMEM_BASE                                        0x14c00000
#define BOOT2_BOOT_IMEM_BASE_SIZE                                   0x00400000
#define BOOT2_BOOT_IMEM_BASE_PHYS                                   0x14c00000

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
 * BASE: PCIE_GEN4X2_SPACE_1_SIZE
 *--------------------------------------------------------------------------*/

#define PCIE_GEN4X2_SPACE_1_SIZE_BASE                               0x20000000
#define PCIE_GEN4X2_SPACE_1_SIZE_BASE_SIZE                          0x00000000
#define PCIE_GEN4X2_SPACE_1_SIZE_BASE_PHYS                          0x20000000

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
#define DDR_SS_BASE_SIZE                                            0x02000000
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
 * BASE: SC_TCM
 *--------------------------------------------------------------------------*/

#define SC_TCM_BASE                                                 0x38000000
#define SC_TCM_BASE_SIZE                                            0x00000000
#define SC_TCM_BASE_PHYS                                            0x38000000

/*----------------------------------------------------------------------------
 * BASE: SC_TCM_END
 *--------------------------------------------------------------------------*/

#define SC_TCM_END_BASE                                             0x383fffff
#define SC_TCM_END_BASE_SIZE                                        0x00000000
#define SC_TCM_END_BASE_PHYS                                        0x383fffff

/*----------------------------------------------------------------------------
 * BASE: PCIE_GEN4X2_SPACE_1
 *--------------------------------------------------------------------------*/

#define PCIE_GEN4X2_SPACE_1_BASE                                    0x40000000
#define PCIE_GEN4X2_SPACE_1_BASE_SIZE                               0x00000000
#define PCIE_GEN4X2_SPACE_1_BASE_PHYS                               0x40000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_GEN4X2_1_PCIE_WRAPPER_AXI_G4X2
 *--------------------------------------------------------------------------*/

#define PCIE_GEN4X2_1_PCIE_WRAPPER_AXI_G4X2_BASE                    0x40000000
#define PCIE_GEN4X2_1_PCIE_WRAPPER_AXI_G4X2_BASE_SIZE               0x02000000
#define PCIE_GEN4X2_1_PCIE_WRAPPER_AXI_G4X2_BASE_PHYS               0x40000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_GEN4X2_SPACE_1_END
 *--------------------------------------------------------------------------*/

#define PCIE_GEN4X2_SPACE_1_END_BASE                                0x5fffffff
#define PCIE_GEN4X2_SPACE_1_END_BASE_SIZE                           0x00000000
#define PCIE_GEN4X2_SPACE_1_END_BASE_PHYS                           0x5fffffff

/*----------------------------------------------------------------------------
 * BASE: PCIE_GEN3X2_SPACE_0
 *--------------------------------------------------------------------------*/

#define PCIE_GEN3X2_SPACE_0_BASE                                    0x60000000
#define PCIE_GEN3X2_SPACE_0_BASE_SIZE                               0x00000000
#define PCIE_GEN3X2_SPACE_0_BASE_PHYS                               0x60000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_GEN3X2_0_PCIE_WRAPPER_AXI_G3X2
 *--------------------------------------------------------------------------*/

#define PCIE_GEN3X2_0_PCIE_WRAPPER_AXI_G3X2_BASE                    0x60000000
#define PCIE_GEN3X2_0_PCIE_WRAPPER_AXI_G3X2_BASE_SIZE               0x02000000
#define PCIE_GEN3X2_0_PCIE_WRAPPER_AXI_G3X2_BASE_PHYS               0x60000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_GEN3X2_SPACE_0_END
 *--------------------------------------------------------------------------*/

#define PCIE_GEN3X2_SPACE_0_END_BASE                                0x63ffffff
#define PCIE_GEN3X2_SPACE_0_END_BASE_SIZE                           0x00000000
#define PCIE_GEN3X2_SPACE_0_END_BASE_PHYS                           0x63ffffff

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

#define PCIE_1_SPACE_SIZE_BASE                                      0x300000000ull
#define PCIE_1_SPACE_SIZE_BASE_SIZE                                 0x00000000
#define PCIE_1_SPACE_SIZE_BASE_PHYS                                 0x300000000ull

/*----------------------------------------------------------------------------
 * BASE: PCIE_1_SPACE
 *--------------------------------------------------------------------------*/

#define PCIE_1_SPACE_BASE                                           0x400000000ull
#define PCIE_1_SPACE_BASE_SIZE                                      0x00000000
#define PCIE_1_SPACE_BASE_PHYS                                      0x400000000ull

/*----------------------------------------------------------------------------
 * BASE: PCIE_1_SPACE_END
 *--------------------------------------------------------------------------*/

#define PCIE_1_SPACE_END_BASE                                       0x6ffffffffull
#define PCIE_1_SPACE_END_BASE_SIZE                                  0x00000000
#define PCIE_1_SPACE_END_BASE_PHYS                                  0x6ffffffffull

/*----------------------------------------------------------------------------
 * BASE: DDR_1_SPACE_SIZE
 *--------------------------------------------------------------------------*/

#define DDR_1_SPACE_SIZE_BASE                                       0x780000000ull
#define DDR_1_SPACE_SIZE_BASE_SIZE                                  0x00000000
#define DDR_1_SPACE_SIZE_BASE_PHYS                                  0x780000000ull

/*----------------------------------------------------------------------------
 * BASE: DDR_1_SPACE
 *--------------------------------------------------------------------------*/

#define DDR_1_SPACE_BASE                                            0x880000000ull
#define DDR_1_SPACE_BASE_SIZE                                       0x00000000
#define DDR_1_SPACE_BASE_PHYS                                       0x880000000ull

/*----------------------------------------------------------------------------
 * BASE: DDR_1_SPACE_END
 *--------------------------------------------------------------------------*/

#define DDR_1_SPACE_END_BASE                                        0xfffffffffull
#define DDR_1_SPACE_END_BASE_SIZE                                   0x00000000
#define DDR_1_SPACE_END_BASE_PHYS                                   0xfffffffffull

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
