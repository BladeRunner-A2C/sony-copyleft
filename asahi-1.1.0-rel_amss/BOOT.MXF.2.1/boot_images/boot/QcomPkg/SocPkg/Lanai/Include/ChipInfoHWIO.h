#ifndef __CHIPINFOHWIO_H__
#define __CHIPINFOHWIO_H__
/*
===========================================================================
*/
/**
    @file ChipInfoHWIO.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8650 (Lanai) [z_lanai_prj_v1.0_preF02_p3q1r9.9_rtl_partition]
 
    This file contains HWIO register definitions for the following modules:
        TLMM_REG
        TCSR_TCSR_REGS
        QFPROM_CORR
        FUSE_CONTROLLER_SW_RANGE4

    'Include' filters applied: CHIP_UNIQUE_ID_.*[FUSE_CONTROLLER_SW_RANGE4] QFPROM_CORR_PTE_ROW1_(MSB|LSB)[QFPROM_CORR] QFPROM_CORR_QC_CONFIG_ROW2_LSB[QFPROM_CORR] QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB[QFPROM_CORR] TCSR_SOC_HW_VERSION[TCSR_TCSR_REGS] TLMM_HW_REVISION_NUM.*[TLMM_REG] 

    Generation parameters: 
    { 'exclude-reserved': True,
      'filename': 'ChipInfoHWIO.h',
      'header': '\n'
                '#include "msmhwiobase.h"\n'
                '\n'
                '#define CHIPINFO_QCOM_MFG_ID_REG            '
                'TLMM_HW_REVISION_NUMBER_0\n'
                '#define CHIPINFO_JTAG_ID_REG                '
                'TLMM_HW_REVISION_NUMBER_1\n'
                '#define CHIPINFO_REVISION_NUMBER_REG        '
                'TLMM_HW_REVISION_NUMBER_2\n'
                '#define CHIPINFO_TCSR_SOC_HW_VERSION_REG    TCSR_SOC_HW_VERSION\n'
                '#define CHIPINFO_FOUNDRY_ID_REG             '
                'QFPROM_CORR_QC_CONFIG_ROW2_LSB\n'
                '#define CHIPINFO_SERIAL_NUM_REG             CHIP_UNIQUE_ID_0\n'
                '#define CHIPINFO_QFPROM_CHIP_ID_REG         CHIP_UNIQUE_ID_1\n'
                '#define CHIPINFO_SKU_ID_REG                 '
                'QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB\n'
                '#define CHIPINFO_P_CODE_REG                 '
                'QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB\n',
      'module-filter-exclude': {},
      'module-filter-include': { 'FUSE_CONTROLLER_SW_RANGE4': ['CHIP_UNIQUE_ID_.*'],
                                 'QFPROM_CORR': [ 'QFPROM_CORR_PTE_ROW1_(MSB|LSB)',
                                                  'QFPROM_CORR_QC_CONFIG_ROW2_LSB',
                                                  'QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB'],
                                 'TCSR_TCSR_REGS': ['TCSR_SOC_HW_VERSION'],
                                 'TLMM_REG': ['TLMM_HW_REVISION_NUM.*']},
      'modules': [ 'TLMM_REG',
                   'TCSR_TCSR_REGS',
                   'QFPROM_CORR',
                   'FUSE_CONTROLLER_SW_RANGE4']}
*/
/*
    ===========================================================================

    Copyright (c) 2022,2023 Qualcomm Technologies, Inc. All rights reserved.

    Export of this technology or software is regulated by the U.S. Government.
    Diversion contrary to U.S. law prohibited.

    All ideas, data and information contained in or disclosed by
    this document are confidential and proprietary information of
    Qualcomm Technologies, Inc. and all rights therein are expressly reserved.
    By accepting this material the recipient agrees that this material
    and the information contained therein are held in confidence and in
    trust and will not be used, copied, reproduced in whole or in part,
    nor its contents revealed in any manner to others without the express
    written permission of Qualcomm Technologies, Inc.

    ===========================================================================

    $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/SocPkg/Lanai/Include/ChipInfoHWIO.h#1 $
    $DateTime: 2024/04/02 23:00:31 $
    $Author: cirrusp4svc $

    ===========================================================================
*/


#include "msmhwiobase.h"

#define CHIPINFO_QCOM_MFG_ID_REG            TLMM_HW_REVISION_NUMBER_0
#define CHIPINFO_JTAG_ID_REG                TLMM_HW_REVISION_NUMBER_1
#define CHIPINFO_REVISION_NUMBER_REG        TLMM_HW_REVISION_NUMBER_2
#define CHIPINFO_TCSR_SOC_HW_VERSION_REG    TCSR_SOC_HW_VERSION
#define CHIPINFO_FOUNDRY_ID_REG             QFPROM_CORR_QC_CONFIG_ROW2_LSB
#define CHIPINFO_SERIAL_NUM_REG             CHIP_UNIQUE_ID_0
#define CHIPINFO_QFPROM_CHIP_ID_REG         CHIP_UNIQUE_ID_1
#define CHIPINFO_SKU_ID_REG                 QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB
#define CHIPINFO_P_CODE_REG                 QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB


/*----------------------------------------------------------------------------
 * MODULE: TLMM_REG
 *--------------------------------------------------------------------------*/

#define TLMM_REG_REG_BASE                                                        (TLMM_BASE      + 0x00100000)
#define TLMM_REG_REG_BASE_SIZE                                                   0xf00000
#define TLMM_REG_REG_BASE_USED                                                   0xfd01c

#define HWIO_TLMM_HW_REVISION_NUMBER_0_ADDR                                      (TLMM_REG_REG_BASE      + 0xd4010)
#define HWIO_TLMM_HW_REVISION_NUMBER_0_RMSK                                           0xfff
#define HWIO_TLMM_HW_REVISION_NUMBER_0_IN                    \
                in_dword(HWIO_TLMM_HW_REVISION_NUMBER_0_ADDR)
#define HWIO_TLMM_HW_REVISION_NUMBER_0_INM(m)            \
                in_dword_masked(HWIO_TLMM_HW_REVISION_NUMBER_0_ADDR, m)
#define HWIO_TLMM_HW_REVISION_NUMBER_0_QUALCOMM_MFG_ID_BMSK                           0xffe
#define HWIO_TLMM_HW_REVISION_NUMBER_0_QUALCOMM_MFG_ID_SHFT                               1
#define HWIO_TLMM_HW_REVISION_NUMBER_0_START_BIT_BMSK                                   0x1
#define HWIO_TLMM_HW_REVISION_NUMBER_0_START_BIT_SHFT                                     0

#define HWIO_TLMM_HW_REVISION_NUMBER_1_ADDR                                      (TLMM_REG_REG_BASE      + 0xd4014)
#define HWIO_TLMM_HW_REVISION_NUMBER_1_RMSK                                          0xffff
#define HWIO_TLMM_HW_REVISION_NUMBER_1_IN                    \
                in_dword(HWIO_TLMM_HW_REVISION_NUMBER_1_ADDR)
#define HWIO_TLMM_HW_REVISION_NUMBER_1_INM(m)            \
                in_dword_masked(HWIO_TLMM_HW_REVISION_NUMBER_1_ADDR, m)
#define HWIO_TLMM_HW_REVISION_NUMBER_1_PRODUCT_DEVICE_ID_BMSK                        0xffff
#define HWIO_TLMM_HW_REVISION_NUMBER_1_PRODUCT_DEVICE_ID_SHFT                             0

#define HWIO_TLMM_HW_REVISION_NUMBER_2_ADDR                                      (TLMM_REG_REG_BASE      + 0xd4018)
#define HWIO_TLMM_HW_REVISION_NUMBER_2_RMSK                                             0xf
#define HWIO_TLMM_HW_REVISION_NUMBER_2_IN                    \
                in_dword(HWIO_TLMM_HW_REVISION_NUMBER_2_ADDR)
#define HWIO_TLMM_HW_REVISION_NUMBER_2_INM(m)            \
                in_dword_masked(HWIO_TLMM_HW_REVISION_NUMBER_2_ADDR, m)
#define HWIO_TLMM_HW_REVISION_NUMBER_2_VERSION_ID_BMSK                                  0xf
#define HWIO_TLMM_HW_REVISION_NUMBER_2_VERSION_ID_SHFT                                    0

/*----------------------------------------------------------------------------
 * MODULE: TCSR_TCSR_REGS
 *--------------------------------------------------------------------------*/

#define TCSR_TCSR_REGS_REG_BASE                                                                                                                                  (CORE_TOP_CSR_BASE      + 0x00040000)
#define TCSR_TCSR_REGS_REG_BASE_SIZE                                                                                                                             0xc0000
#define TCSR_TCSR_REGS_REG_BASE_USED                                                                                                                             0xbb000

#define HWIO_TCSR_SOC_HW_VERSION_ADDR                                                                                                                            (TCSR_TCSR_REGS_REG_BASE      + 0x88000)
#define HWIO_TCSR_SOC_HW_VERSION_RMSK                                                                                                                            0xffffffff
#define HWIO_TCSR_SOC_HW_VERSION_IN                    \
                in_dword(HWIO_TCSR_SOC_HW_VERSION_ADDR)
#define HWIO_TCSR_SOC_HW_VERSION_INM(m)            \
                in_dword_masked(HWIO_TCSR_SOC_HW_VERSION_ADDR, m)
#define HWIO_TCSR_SOC_HW_VERSION_FAMILY_NUMBER_BMSK                                                                                                              0xf0000000
#define HWIO_TCSR_SOC_HW_VERSION_FAMILY_NUMBER_SHFT                                                                                                                      28
#define HWIO_TCSR_SOC_HW_VERSION_DEVICE_NUMBER_BMSK                                                                                                               0xfff0000
#define HWIO_TCSR_SOC_HW_VERSION_DEVICE_NUMBER_SHFT                                                                                                                      16
#define HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_BMSK                                                                                                                  0xff00
#define HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_SHFT                                                                                                                       8
#define HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_BMSK                                                                                                                    0xff
#define HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_SHFT                                                                                                                       0

/*----------------------------------------------------------------------------
 * MODULE: QFPROM_CORR
 *--------------------------------------------------------------------------*/

#define QFPROM_CORR_REG_BASE                                                                                         (TMESS_BASE      + 0x021c2000)
#define QFPROM_CORR_REG_BASE_SIZE                                                                                    0x2000
#define QFPROM_CORR_REG_BASE_USED                                                                                    0x137c

#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_ADDR                                                                (QFPROM_CORR_REG_BASE      + 0x160)
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_RMSK                                                                0xffffffff
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_ADDR)
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_FEATURE_CONFIG_415_412_BMSK                                         0xf0000000
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_FEATURE_CONFIG_415_412_SHFT                                                 28
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_P_CODE_BMSK                                                          0xff00000
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_P_CODE_SHFT                                                                 20
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_SKU_ID_BMSK                                                            0xff000
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_SKU_ID_SHFT                                                                 12
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_FEATURE_CONFIG_395_384_BMSK                                              0xfff
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_FEATURE_CONFIG_395_384_SHFT                                                  0

#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_MSB_ADDR                                                                (QFPROM_CORR_REG_BASE      + 0x164)
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_MSB_RMSK                                                                0xffffffff
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_MSB_ADDR)
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_MSB_FEATURE_CONFIG_447_424_BMSK                                         0xffffff00
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_MSB_FEATURE_CONFIG_447_424_SHFT                                                  8
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_MSB_PRODUCT_SEGMENT_ID_BMSK                                                   0xff
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_MSB_PRODUCT_SEGMENT_ID_SHFT                                                      0

#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_ADDR                                                                     (QFPROM_CORR_REG_BASE      + 0x1b0)
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_RMSK                                                                     0xffffffff
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_ADDR)
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_QC_CONFIG_159_146_BMSK                                                   0xfffc0000
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_QC_CONFIG_159_146_SHFT                                                           18
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_APPS_PBL_BOOT_SPEED_BMSK                                                    0x30000
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_APPS_PBL_BOOT_SPEED_SHFT                                                         16
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_VENDOR_LOCK_BMSK                                                             0xf000
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_VENDOR_LOCK_SHFT                                                                 12
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_FOUNDRY_ID_BMSK                                                               0xf00
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_FOUNDRY_ID_SHFT                                                                   8
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_STACKED_MEMORY_ID_BMSK                                                         0xf8
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_STACKED_MEMORY_ID_SHFT                                                            3
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_SEC_TAP_ACCESS_DISABLE_15_13_BMSK                                               0x7
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_SEC_TAP_ACCESS_DISABLE_15_13_SHFT                                                 0

#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_ADDR                                                                    (QFPROM_CORR_REG_BASE      + 0x2d0)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_RMSK                                                                    0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_ADDR)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_QC_SPARE_0_31_25_BMSK                                                   0xfe000000
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_QC_SPARE_0_31_25_SHFT                                                           25
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_SUBBIND_BMSK                                                             0x1f00000
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_SUBBIND_SHFT                                                                    20
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_SUBBINC_BMSK                                                               0xf8000
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_SUBBINC_SHFT                                                                    15
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_SUBBINB_BMSK                                                                0x7c00
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_SUBBINB_SHFT                                                                    10
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_SUBBINA_BMSK                                                                 0x3e0
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_SUBBINA_SHFT                                                                     5
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_PARTIAL_BIN_BMSK                                                              0x1f
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_PARTIAL_BIN_SHFT                                                                 0

#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_ADDR                                                                    (QFPROM_CORR_REG_BASE      + 0x2d4)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_RMSK                                                                    0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_ADDR)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_QC_SPARE_0_63_50_BMSK                                                   0xfffc0000
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_QC_SPARE_0_63_50_SHFT                                                           18
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_CPUSS_BOOT_FSM_CORE_BMSK                                                   0x3fc00
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_CPUSS_BOOT_FSM_CORE_SHFT                                                        10
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_QC_SPARE_0_41_40_BMSK                                                        0x300
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_QC_SPARE_0_41_40_SHFT                                                            8
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_SUBBINA_CORE_BMSK                                                             0xff
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_SUBBINA_CORE_SHFT                                                                0

#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_ADDR                                                                    (QFPROM_CORR_REG_BASE      + 0x2d8)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_RMSK                                                                    0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_ADDR)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_QC_SPARE_0_95_92_BMSK                                                   0xf0000000
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_QC_SPARE_0_95_92_SHFT                                                           28
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_NSP_UNSUPPORTED_FEATURE_BMSK                                             0xfff0000
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_NSP_UNSUPPORTED_FEATURE_SHFT                                                    16
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_CAMERA_UNSUPPORTED_FEATURE_BMSK                                             0xffff
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_CAMERA_UNSUPPORTED_FEATURE_SHFT                                                  0

#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_ADDR                                                                    (QFPROM_CORR_REG_BASE      + 0x2dc)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_RMSK                                                                    0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_ADDR)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_QC_SPARE_0_127_104_BMSK                                                 0xffffff00
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_QC_SPARE_0_127_104_SHFT                                                          8
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_MODEM_UNSUPPORTED_FEATURE_BMSK                                                0xff
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_MODEM_UNSUPPORTED_FEATURE_SHFT                                                   0
/*----------------------------------------------------------------------------
 * MODULE: FUSE_CONTROLLER_SW_RANGE4
 *--------------------------------------------------------------------------*/

#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE                                                                 (TMESS_BASE      + 0x021c8000)
#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE                                                            0x1000
#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE_USED                                                            0xc7c

#define HWIO_CHIP_UNIQUE_ID_0_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x610)
#define HWIO_CHIP_UNIQUE_ID_0_RMSK                                                                         0xffffffff
#define HWIO_CHIP_UNIQUE_ID_0_IN                    \
                in_dword(HWIO_CHIP_UNIQUE_ID_0_ADDR)
#define HWIO_CHIP_UNIQUE_ID_0_INM(m)            \
                in_dword_masked(HWIO_CHIP_UNIQUE_ID_0_ADDR, m)
#define HWIO_CHIP_UNIQUE_ID_0_SERIAL_NUM_BMSK                                                              0xffffffff
#define HWIO_CHIP_UNIQUE_ID_0_SERIAL_NUM_SHFT                                                                       0

#define HWIO_CHIP_UNIQUE_ID_1_ADDR                                                                         (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x614)
#define HWIO_CHIP_UNIQUE_ID_1_RMSK                                                                         0xffffffff
#define HWIO_CHIP_UNIQUE_ID_1_IN                    \
                in_dword(HWIO_CHIP_UNIQUE_ID_1_ADDR)
#define HWIO_CHIP_UNIQUE_ID_1_INM(m)            \
                in_dword_masked(HWIO_CHIP_UNIQUE_ID_1_ADDR, m)
#define HWIO_CHIP_UNIQUE_ID_1_CHIP_ID_BMSK                                                                 0xffffffff
#define HWIO_CHIP_UNIQUE_ID_1_CHIP_ID_SHFT                                                                          0


#endif /* __CHIPINFOHWIO_H__ */
