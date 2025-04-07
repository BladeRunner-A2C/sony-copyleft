#ifndef CHIPINFOHWIO_H
#define CHIPINFOHWIO_H
/*
===========================================================================
*/
/**
    @file ChipInfoHWIO.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM6xxx (Milos) [milos_v1.0_p3q3r45_MTO]
 
    This file contains HWIO register definitions for the following modules:
        TLMM_REG
        TCSR_TCSR_REGS
        QFPROM_CORR
        FUSE_CONTROLLER_SW_RANGE4

    'Include' filters applied: TLMM_HW_REVISION_NUM.*[TLMM_REG] TCSR_SOC_HW_VERSION[TCSR_TCSR_REGS] QFPROM_CORR_PTE_ROW1_(MSB|LSB)[QFPROM_CORR] QFPROM_CORR_QC_CONFIG_ROW2_LSB[QFPROM_CORR] QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB[QFPROM_CORR] QFPROM_CORR_QC_SPARE_0_ROW0_(MSB|LSB)[QFPROM_CORR] QFPROM_CORR_QC_SPARE_0_ROW1_(MSB|LSB)[QFPROM_CORR] CHIP_UNIQUE_ID_.*[FUSE_CONTROLLER_SW_RANGE4] 

    Generation parameters: 
    { 'exclude-reserved': True,
      'filename': 'ChipInfoHWIO.h',
      'header': '#include "msmhwiobase.h"\n'
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
                'QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB',
      'module-filter-include': { 'FUSE_CONTROLLER_SW_RANGE4': ['CHIP_UNIQUE_ID_.*'],
                                 'QFPROM_CORR': [ 'QFPROM_CORR_PTE_ROW1_(MSB|LSB)',
                                                  'QFPROM_CORR_QC_CONFIG_ROW2_LSB',
                                                  'QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB',
                                                  'QFPROM_CORR_QC_SPARE_0_ROW0_(MSB|LSB)',
                                                  'QFPROM_CORR_QC_SPARE_0_ROW1_(MSB|LSB)'],
                                 'TCSR_TCSR_REGS': ['TCSR_SOC_HW_VERSION'],
                                 'TLMM_REG': ['TLMM_HW_REVISION_NUM.*']},
      'modules': [ 'TLMM_REG',
                   'TCSR_TCSR_REGS',
                   'QFPROM_CORR',
                   'FUSE_CONTROLLER_SW_RANGE4']}
*/
/*
    ===========================================================================

    Copyright (c) 2024 Qualcomm Technologies, Inc.
    All Rights Reserved.
    Confidential and Proprietary - Qualcomm Technologies, Inc.

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

    $Header: $
    $DateTime: $
    $Author: $

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
#define TLMM_REG_REG_BASE_USED                                                   0xd301c

#define HWIO_TLMM_HW_REVISION_NUMBER_0_ADDR                                      (TLMM_REG_REG_BASE      + 0xa9010)
#define HWIO_TLMM_HW_REVISION_NUMBER_0_RMSK                                           0xfff
#define HWIO_TLMM_HW_REVISION_NUMBER_0_IN                    \
                in_dword(HWIO_TLMM_HW_REVISION_NUMBER_0_ADDR)
#define HWIO_TLMM_HW_REVISION_NUMBER_0_INM(m)            \
                in_dword_masked(HWIO_TLMM_HW_REVISION_NUMBER_0_ADDR, m)
#define HWIO_TLMM_HW_REVISION_NUMBER_0_QUALCOMM_MFG_ID_BMSK                           0xffe
#define HWIO_TLMM_HW_REVISION_NUMBER_0_QUALCOMM_MFG_ID_SHFT                               1
#define HWIO_TLMM_HW_REVISION_NUMBER_0_START_BIT_BMSK                                   0x1
#define HWIO_TLMM_HW_REVISION_NUMBER_0_START_BIT_SHFT                                     0

#define HWIO_TLMM_HW_REVISION_NUMBER_1_ADDR                                      (TLMM_REG_REG_BASE      + 0xa9014)
#define HWIO_TLMM_HW_REVISION_NUMBER_1_RMSK                                          0xffff
#define HWIO_TLMM_HW_REVISION_NUMBER_1_IN                    \
                in_dword(HWIO_TLMM_HW_REVISION_NUMBER_1_ADDR)
#define HWIO_TLMM_HW_REVISION_NUMBER_1_INM(m)            \
                in_dword_masked(HWIO_TLMM_HW_REVISION_NUMBER_1_ADDR, m)
#define HWIO_TLMM_HW_REVISION_NUMBER_1_PRODUCT_DEVICE_ID_BMSK                        0xffff
#define HWIO_TLMM_HW_REVISION_NUMBER_1_PRODUCT_DEVICE_ID_SHFT                             0

#define HWIO_TLMM_HW_REVISION_NUMBER_2_ADDR                                      (TLMM_REG_REG_BASE      + 0xa9018)
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

#define TCSR_TCSR_REGS_REG_BASE                                                                                                                               (CORE_TOP_CSR_BASE      + 0x00040000)
#define TCSR_TCSR_REGS_REG_BASE_SIZE                                                                                                                          0xc0000
#define TCSR_TCSR_REGS_REG_BASE_USED                                                                                                                          0xb8000

#define HWIO_TCSR_SOC_HW_VERSION_ADDR                                                                                                                         (TCSR_TCSR_REGS_REG_BASE      + 0x88000)
#define HWIO_TCSR_SOC_HW_VERSION_RMSK                                                                                                                         0xffffffff
#define HWIO_TCSR_SOC_HW_VERSION_IN                    \
                in_dword(HWIO_TCSR_SOC_HW_VERSION_ADDR)
#define HWIO_TCSR_SOC_HW_VERSION_INM(m)            \
                in_dword_masked(HWIO_TCSR_SOC_HW_VERSION_ADDR, m)
#define HWIO_TCSR_SOC_HW_VERSION_FAMILY_NUMBER_BMSK                                                                                                           0xf0000000
#define HWIO_TCSR_SOC_HW_VERSION_FAMILY_NUMBER_SHFT                                                                                                                   28
#define HWIO_TCSR_SOC_HW_VERSION_DEVICE_NUMBER_BMSK                                                                                                            0xfff0000
#define HWIO_TCSR_SOC_HW_VERSION_DEVICE_NUMBER_SHFT                                                                                                                   16
#define HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_BMSK                                                                                                               0xff00
#define HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_SHFT                                                                                                                    8
#define HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_BMSK                                                                                                                 0xff
#define HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_SHFT                                                                                                                    0

/*----------------------------------------------------------------------------
 * MODULE: QFPROM_CORR
 *--------------------------------------------------------------------------*/

#define QFPROM_CORR_REG_BASE                                                                                         (TMESS_BASE      + 0x021c2000)
#define QFPROM_CORR_REG_BASE_SIZE                                                                                    0x2000
#define QFPROM_CORR_REG_BASE_USED                                                                                    0x137c

#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0xa0)
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW1_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IDDQ_MXC_ACTIVE_6_0_BMSK                                                       0xfe000000
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IDDQ_MXC_ACTIVE_6_0_SHFT                                                               25
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IDDQ_MM_ACTIVE_BMSK                                                             0x1ff8000
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IDDQ_MM_ACTIVE_SHFT                                                                    15
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_MR_WS_RT_BMSK                                                                      0x4000
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_MR_WS_RT_SHFT                                                                          14
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_MR_WS_HT_BMSK                                                                      0x2000
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_MR_WS_HT_SHFT                                                                          13
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_MR_FT_RT_BMSK                                                                      0x1000
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_MR_FT_RT_SHFT                                                                          12
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_MR_FT_HT_BMSK                                                                       0x800
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_MR_FT_HT_SHFT                                                                          11
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_SUBBINA_BMSK                                                                        0x7c0
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_SUBBINA_SHFT                                                                            6
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_PTE_MCN_IDENTIFIER_BMSK                                                              0x20
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_PTE_MCN_IDENTIFIER_SHFT                                                                 5
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_RETENTION_FAIL_BMSK                                                                  0x10
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_RETENTION_FAIL_SHFT                                                                     4
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_HV_ONLY_BMSK                                                                          0x8
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_HV_ONLY_SHFT                                                                            3
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_WAFER_ZONE_BMSK                                                                       0x7
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_WAFER_ZONE_SHFT                                                                         0

#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0xa4)
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_PTE_ROW1_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IDDQ_APC1_ACTIVE_8_0_BMSK                                                      0xff800000
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IDDQ_APC1_ACTIVE_8_0_SHFT                                                              23
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IDDQ_APC0_ACTIVE_BMSK                                                            0x7fe000
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IDDQ_APC0_ACTIVE_SHFT                                                                  13
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_DOU_BINNNING_BMSK                                                                  0x1c00
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_DOU_BINNNING_SHFT                                                                      10
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_TSENS_REV_CTRL_BMSK                                                                 0x200
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_TSENS_REV_CTRL_SHFT                                                                     9
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_PARTIAL_BIN_BMSK                                                                    0x1f0
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_PARTIAL_BIN_SHFT                                                                        4
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_INT_SECURE_MCN_IDENTIFIER_BMSK                                                        0x8
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_INT_SECURE_MCN_IDENTIFIER_SHFT                                                          3
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IDDQ_MXC_ACTIVE_9_7_BMSK                                                              0x7
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IDDQ_MXC_ACTIVE_9_7_SHFT                                                                0

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
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_FEATURE_CONFIG_395_394_BMSK                                              0xc00
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_FEATURE_CONFIG_395_394_SHFT                                                 10
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_PIMEM_MEM_SIZE_BMSK                                                      0x300
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_PIMEM_MEM_SIZE_SHFT                                                          8
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_SYS_CFG_SILVER_PLL_LVAL_BMSK                                              0xff
#define HWIO_QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB_SYS_CFG_SILVER_PLL_LVAL_SHFT                                                 0

#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_ADDR                                                                     (QFPROM_CORR_REG_BASE      + 0x1d0)
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_RMSK                                                                     0xffffffff
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_ADDR)
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_QC_CONFIG_159_147_BMSK                                                   0xfff80000
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_QC_CONFIG_159_147_SHFT                                                           19
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_QC_DDR_ENABLE_TWO_CHANNEL_MODE_BMSK                                         0x40000
#define HWIO_QFPROM_CORR_QC_CONFIG_ROW2_LSB_QC_DDR_ENABLE_TWO_CHANNEL_MODE_SHFT                                              18
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

#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_ADDR                                                                    (QFPROM_CORR_REG_BASE      + 0x328)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_RMSK                                                                    0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_ADDR)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_QC_SPARE_0_31_0_BMSK                                                    0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_LSB_QC_SPARE_0_31_0_SHFT                                                             0

#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_ADDR                                                                    (QFPROM_CORR_REG_BASE      + 0x32c)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_RMSK                                                                    0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_ADDR)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_QC_SPARE_0_63_32_BMSK                                                   0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW0_MSB_QC_SPARE_0_63_32_SHFT                                                            0

#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_ADDR                                                                    (QFPROM_CORR_REG_BASE      + 0x330)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_RMSK                                                                    0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_ADDR)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_QC_SPARE_0_95_64_BMSK                                                   0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_LSB_QC_SPARE_0_95_64_SHFT                                                            0

#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_ADDR                                                                    (QFPROM_CORR_REG_BASE      + 0x334)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_RMSK                                                                    0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_ADDR)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_QC_SPARE_0_127_96_BMSK                                                  0xffffffff
#define HWIO_QFPROM_CORR_QC_SPARE_0_ROW1_MSB_QC_SPARE_0_127_96_SHFT                                                           0

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


#endif /* CHIPINFOHWIO_H */
