#ifndef __HALHWIOTSENSFUSES_H__
#define __HALHWIOTSENSFUSES_H__
/*
===========================================================================
*/
/**
    @file HALhwioTsensFuses.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8650 (Lanai) [z_tme_fusecontroller_lanai_p3q0r106]
 
    This file contains HWIO register definitions for the following modules:
        QFPROM_CORR

    'Include' filters applied: QFPROM_CORR_CALIB.*[QFPROM_CORR] 

    Generation parameters: 
    { 'filename': 'HALhwioTsensFuses.h',
      'header': '#include "msmhwiobase.h"',
      'module-filter-exclude': {},
      'module-filter-include': {'QFPROM_CORR': ['QFPROM_CORR_CALIB.*']},
      'modules': ['QFPROM_CORR']}
*/
/*
    ===========================================================================

    Copyright (c) 2022 Qualcomm Technologies, Inc.
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

/*----------------------------------------------------------------------------
 * MODULE: QFPROM_CORR
 *--------------------------------------------------------------------------*/
 
#define TME_FUSECONTROLLER_BASE                                                                                      0x221C0000

#define QFPROM_CORR_REG_BASE                                                                                         (TME_FUSECONTROLLER_BASE      + 0x00002000)
#define QFPROM_CORR_REG_BASE_SIZE                                                                                    0x2000
#define QFPROM_CORR_REG_BASE_USED                                                                                    0x137c

#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x9e8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_USB2PHY_RCAL_CODE_0_BMSK                                               0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_USB2PHY_RCAL_CODE_0_SHFT                                                       31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_CALIBRATION_30_24_BMSK                                                 0x7f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_CALIBRATION_30_24_SHFT                                                         24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_2_NORTH_BGV_TRIM_BMSK                                             0xff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_2_NORTH_BGV_TRIM_SHFT                                                   16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_0_NORTH_BGV_TRIM_BMSK                                               0xff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_0_NORTH_BGV_TRIM_SHFT                                                    8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_1_SOUTH_BGV_TRIM_BMSK                                                 0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_1_SOUTH_BGV_TRIM_SHFT                                                    0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x9ec)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_CALIBRATION_63_44_BMSK                                                 0xfffff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_CALIBRATION_63_44_SHFT                                                         12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_APSS_CS_ADC_VREFP_CTRL_IN_BMSK                                              0xf00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_APSS_CS_ADC_VREFP_CTRL_IN_SHFT                                                  8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_CALIBRATION_39_35_BMSK                                                       0xf8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_CALIBRATION_39_35_SHFT                                                          3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_USB2PHY_RCAL_CODE_3_1_BMSK                                                    0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_USB2PHY_RCAL_CODE_3_1_SHFT                                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x9f0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_CALIBRATION_95_64_BMSK                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_CALIBRATION_95_64_SHFT                                                          0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x9f4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_CALIBRATION_127_96_BMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_CALIBRATION_127_96_SHFT                                                         0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x9f8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_OFFSET_TUR_2_0_BMSK                                     0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_OFFSET_TUR_2_0_SHFT                                             29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_OFFSET_TURL1_BMSK                                       0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_OFFSET_TURL1_SHFT                                               24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_LSVS_BMSK                                                 0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_LSVS_SHFT                                                       18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_SVS_BMSK                                                   0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_SVS_SHFT                                                        12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_NOM_BMSK                                                     0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_NOM_SHFT                                                         6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_TURL1_BMSK                                                    0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_TURL1_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x9fc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR0_AGING_4_0_BMSK                                                    0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR0_AGING_4_0_SHFT                                                            27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR0_TARG_VOLT_OFFSET_LSVS_BMSK                                         0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR0_TARG_VOLT_OFFSET_LSVS_SHFT                                                22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR0_TARG_VOLT_OFFSET_SVS_BMSK                                           0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR0_TARG_VOLT_OFFSET_SVS_SHFT                                                 17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR0_TARG_VOLT_OFFSET_SVSL1_BMSK                                          0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR0_TARG_VOLT_OFFSET_SVSL1_SHFT                                               12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR0_TARG_VOLT_OFFSET_NOM_BMSK                                              0xf80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR0_TARG_VOLT_OFFSET_NOM_SHFT                                                  7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR0_TARG_VOLT_OFFSET_NOML1_BMSK                                             0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR0_TARG_VOLT_OFFSET_NOML1_SHFT                                                2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR0_TARG_VOLT_OFFSET_TUR_4_3_BMSK                                            0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR0_TARG_VOLT_OFFSET_TUR_4_3_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa00)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR1_TARG_VOLT_OFFSET_NOML1_BMSK                                       0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR1_TARG_VOLT_OFFSET_NOML1_SHFT                                               27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR1_TARG_VOLT_LSVSD1_BMSK                                              0x7e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR1_TARG_VOLT_LSVSD1_SHFT                                                     21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR1_TARG_VOLT_SVS_BMSK                                                  0x1f8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR1_TARG_VOLT_SVS_SHFT                                                        15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR1_TARG_VOLT_NOM_BMSK                                                    0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR1_TARG_VOLT_NOM_SHFT                                                         9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR1_TARG_VOLT_NOML1_BMSK                                                   0x1f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR1_TARG_VOLT_NOML1_SHFT                                                       3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR0_AGING_7_5_BMSK                                                           0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR0_AGING_7_5_SHFT                                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa04)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CPR1_AGING_6_0_BMSK                                                    0xfe000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CPR1_AGING_6_0_SHFT                                                            25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CPR1_TARG_VOLT_OFFSET_LSVSD1_BMSK                                       0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CPR1_TARG_VOLT_OFFSET_LSVSD1_SHFT                                              20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CPR1_TARG_VOLT_OFFSET_LSVS_BMSK                                           0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CPR1_TARG_VOLT_OFFSET_LSVS_SHFT                                                15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CPR1_TARG_VOLT_OFFSET_SVS_BMSK                                             0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CPR1_TARG_VOLT_OFFSET_SVS_SHFT                                                 10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CPR1_TARG_VOLT_OFFSET_SVSL1_BMSK                                            0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CPR1_TARG_VOLT_OFFSET_SVSL1_SHFT                                                5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CPR1_TARG_VOLT_OFFSET_NOM_BMSK                                               0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CPR1_TARG_VOLT_OFFSET_NOM_SHFT                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa08)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CPR2_TARG_VOLT_OFFSET_TURL1_0_BMSK                                     0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CPR2_TARG_VOLT_OFFSET_TURL1_0_SHFT                                             31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CPR2_TARG_VOLT_LSVSD1_BMSK                                             0x7e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CPR2_TARG_VOLT_LSVSD1_SHFT                                                     25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CPR2_TARG_VOLT_LSVS_BMSK                                                0x1f80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CPR2_TARG_VOLT_LSVS_SHFT                                                       19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CPR2_TARG_VOLT_SVS_BMSK                                                   0x7e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CPR2_TARG_VOLT_SVS_SHFT                                                        13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CPR2_TARG_VOLT_NOM_BMSK                                                    0x1f80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CPR2_TARG_VOLT_NOM_SHFT                                                         7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CPR2_TARG_VOLT_TURL1_BMSK                                                    0x7e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CPR2_TARG_VOLT_TURL1_SHFT                                                       1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CPR1_AGING_7_BMSK                                                             0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CPR1_AGING_7_SHFT                                                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa0c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_SVSL0_2_0_BMSK                                   0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_SVSL0_2_0_SHFT                                           29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_SVSL1_BMSK                                       0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_SVSL1_SHFT                                               24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_SVSL2_BMSK                                         0xf80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_SVSL2_SHFT                                               19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_NOM_BMSK                                            0x7c000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_NOM_SHFT                                                 14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_NOML1_BMSK                                           0x3e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_NOML1_SHFT                                                9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_TUR_BMSK                                              0x1f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_TUR_SHFT                                                  4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_TURL1_4_1_BMSK                                          0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR2_TARG_VOLT_OFFSET_TURL1_4_1_SHFT                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa10)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CPR2_TARG_VOLT_OFFSET_LSVSD2_BMSK                                      0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CPR2_TARG_VOLT_OFFSET_LSVSD2_SHFT                                              27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CPR2_TARG_VOLT_OFFSET_LSVSD1_BMSK                                       0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CPR2_TARG_VOLT_OFFSET_LSVSD1_SHFT                                              22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CPR2_TARG_VOLT_OFFSET_LSVSD0_BMSK                                        0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CPR2_TARG_VOLT_OFFSET_LSVSD0_SHFT                                              17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CPR2_TARG_VOLT_OFFSET_LSVS_BMSK                                           0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CPR2_TARG_VOLT_OFFSET_LSVS_SHFT                                                12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CPR2_TARG_VOLT_OFFSET_LSVSL1_BMSK                                           0xf80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CPR2_TARG_VOLT_OFFSET_LSVSL1_SHFT                                               7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CPR2_TARG_VOLT_OFFSET_SVS_BMSK                                               0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CPR2_TARG_VOLT_OFFSET_SVS_SHFT                                                  2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CPR2_TARG_VOLT_OFFSET_SVSL0_4_3_BMSK                                          0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_CPR2_TARG_VOLT_OFFSET_SVSL0_4_3_SHFT                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa14)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CPR4_TARG_VOLT_TURL1_0_BMSK                                            0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CPR4_TARG_VOLT_TURL1_0_SHFT                                                    31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CPR3_TARG_VOLT_SVS_BMSK                                                0x7e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CPR3_TARG_VOLT_SVS_SHFT                                                        25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CPR3_TARG_VOLT_NOM_BMSK                                                 0x1f80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CPR3_TARG_VOLT_NOM_SHFT                                                        19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CPR3_TARG_VOLT_TUR_BMSK                                                   0x7e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CPR3_TARG_VOLT_TUR_SHFT                                                        13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CPR2_AGING_BMSK                                                            0x1fe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CPR2_AGING_SHFT                                                                 5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CPR2_TARG_VOLT_OFFSET_LSVSD3_BMSK                                            0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CPR2_TARG_VOLT_OFFSET_LSVSD3_SHFT                                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa18)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR4_TARG_VOLT_OFFSET_TUR_3_0_BMSK                                     0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR4_TARG_VOLT_OFFSET_TUR_3_0_SHFT                                             28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR4_TARG_VOLT_OFFSET_TURL1_BMSK                                        0xf800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR4_TARG_VOLT_OFFSET_TURL1_SHFT                                               23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR4_TARG_VOLT_SVS_BMSK                                                  0x7e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR4_TARG_VOLT_SVS_SHFT                                                        17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR4_TARG_VOLT_NOM_BMSK                                                   0x1f800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR4_TARG_VOLT_NOM_SHFT                                                        11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR4_TARG_VOLT_TUR_BMSK                                                     0x7e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR4_TARG_VOLT_TUR_SHFT                                                         5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR4_TARG_VOLT_TURL1_5_1_BMSK                                                0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR4_TARG_VOLT_TURL1_5_1_SHFT                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa1c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR5_TARG_VOLT_TURL1_BMSK                                              0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR5_TARG_VOLT_TURL1_SHFT                                                      26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR4_TARG_VOLT_OFFSET_LSVS_BMSK                                         0x3e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR4_TARG_VOLT_OFFSET_LSVS_SHFT                                                21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR4_TARG_VOLT_OFFSET_SVS_BMSK                                           0x1f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR4_TARG_VOLT_OFFSET_SVS_SHFT                                                 16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR4_TARG_VOLT_OFFSET_SVSL1_BMSK                                           0xf800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR4_TARG_VOLT_OFFSET_SVSL1_SHFT                                               11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR4_TARG_VOLT_OFFSET_NOM_BMSK                                              0x7c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR4_TARG_VOLT_OFFSET_NOM_SHFT                                                  6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR4_TARG_VOLT_OFFSET_NOML1_BMSK                                             0x3e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR4_TARG_VOLT_OFFSET_NOML1_SHFT                                                1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR4_TARG_VOLT_OFFSET_TUR_4_BMSK                                              0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR4_TARG_VOLT_OFFSET_TUR_4_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa20)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR5_TARG_VOLT_OFFSET_NOML1_3_0_BMSK                                   0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR5_TARG_VOLT_OFFSET_NOML1_3_0_SHFT                                           28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR5_TARG_VOLT_OFFSET_TUR_BMSK                                          0xf800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR5_TARG_VOLT_OFFSET_TUR_SHFT                                                 23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR5_TARG_VOLT_OFFSET_TURL1_BMSK                                         0x7c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR5_TARG_VOLT_OFFSET_TURL1_SHFT                                               18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR5_TARG_VOLT_SVS_BMSK                                                   0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR5_TARG_VOLT_SVS_SHFT                                                        12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR5_TARG_VOLT_NOM_BMSK                                                     0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR5_TARG_VOLT_NOM_SHFT                                                         6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR5_TARG_VOLT_TUR_BMSK                                                      0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR5_TARG_VOLT_TUR_SHFT                                                         0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa24)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR6_TARG_VOLT_NOM_4_0_BMSK                                            0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR6_TARG_VOLT_NOM_4_0_SHFT                                                    27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR6_TARG_VOLT_TUR_BMSK                                                 0x7e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR6_TARG_VOLT_TUR_SHFT                                                        21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR5_TARG_VOLT_OFFSET_LSVS_BMSK                                          0x1f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR5_TARG_VOLT_OFFSET_LSVS_SHFT                                                16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR5_TARG_VOLT_OFFSET_SVS_BMSK                                             0xf800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR5_TARG_VOLT_OFFSET_SVS_SHFT                                                 11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR5_TARG_VOLT_OFFSET_SVSL1_BMSK                                            0x7c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR5_TARG_VOLT_OFFSET_SVSL1_SHFT                                                6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR5_TARG_VOLT_OFFSET_NOM_BMSK                                               0x3e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR5_TARG_VOLT_OFFSET_NOM_SHFT                                                  1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR5_TARG_VOLT_OFFSET_NOML1_4_BMSK                                            0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR5_TARG_VOLT_OFFSET_NOML1_4_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa28)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR7_TARG_VOLT_OFFSET_NOM_1_0_BMSK                                     0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR7_TARG_VOLT_OFFSET_NOM_1_0_SHFT                                             30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR7_TARG_VOLT_OFFSET_TUR_BMSK                                         0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR7_TARG_VOLT_OFFSET_TUR_SHFT                                                 25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR7_TARG_VOLT_LSVSD1_BMSK                                              0x1f80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR7_TARG_VOLT_LSVSD1_SHFT                                                     19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR7_TARG_VOLT_SVS_BMSK                                                   0x7e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR7_TARG_VOLT_SVS_SHFT                                                        13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR7_TARG_VOLT_NOM_BMSK                                                    0x1f80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR7_TARG_VOLT_NOM_SHFT                                                         7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR7_TARG_VOLT_TUR_BMSK                                                      0x7e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR7_TARG_VOLT_TUR_SHFT                                                         1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR6_TARG_VOLT_NOM_5_BMSK                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR6_TARG_VOLT_NOM_5_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa2c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR8_TARG_VOLT_TUR_0_BMSK                                              0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR8_TARG_VOLT_TUR_0_SHFT                                                      31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR7_AGING_BMSK                                                        0x7f800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR7_AGING_SHFT                                                                23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR7_TARG_VOLT_OFFSET_LSVSD1_BMSK                                        0x7c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR7_TARG_VOLT_OFFSET_LSVSD1_SHFT                                              18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR7_TARG_VOLT_OFFSET_LSVS_BMSK                                           0x3e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR7_TARG_VOLT_OFFSET_LSVS_SHFT                                                13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR7_TARG_VOLT_OFFSET_SVS_BMSK                                             0x1f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR7_TARG_VOLT_OFFSET_SVS_SHFT                                                  8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR7_TARG_VOLT_OFFSET_SVSL1_BMSK                                             0xf8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR7_TARG_VOLT_OFFSET_SVSL1_SHFT                                                3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR7_TARG_VOLT_OFFSET_NOM_4_2_BMSK                                            0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR7_TARG_VOLT_OFFSET_NOM_4_2_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa30)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR8_TARG_VOLT_OFFSET_NOM_3_0_BMSK                                     0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR8_TARG_VOLT_OFFSET_NOM_3_0_SHFT                                             28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR8_TARG_VOLT_OFFSET_TUR_BMSK                                          0xf800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR8_TARG_VOLT_OFFSET_TUR_SHFT                                                 23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR8_TARG_VOLT_LSVSD1_BMSK                                               0x7e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR8_TARG_VOLT_LSVSD1_SHFT                                                     17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR8_TARG_VOLT_SVS_BMSK                                                   0x1f800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR8_TARG_VOLT_SVS_SHFT                                                        11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR8_TARG_VOLT_NOM_BMSK                                                     0x7e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR8_TARG_VOLT_NOM_SHFT                                                         5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR8_TARG_VOLT_TUR_5_1_BMSK                                                  0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR8_TARG_VOLT_TUR_5_1_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa34)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR9_TARG_VOLT_TURL3_2_0_BMSK                                          0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR9_TARG_VOLT_TURL3_2_0_SHFT                                                  29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR8_AGING_BMSK                                                        0x1fe00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR8_AGING_SHFT                                                                21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR8_TARG_VOLT_OFFSET_LSVSD1_BMSK                                        0x1f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR8_TARG_VOLT_OFFSET_LSVSD1_SHFT                                              16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR8_TARG_VOLT_OFFSET_LSVS_BMSK                                            0xf800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR8_TARG_VOLT_OFFSET_LSVS_SHFT                                                11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR8_TARG_VOLT_OFFSET_SVS_BMSK                                              0x7c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR8_TARG_VOLT_OFFSET_SVS_SHFT                                                  6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR8_TARG_VOLT_OFFSET_SVSL1_BMSK                                             0x3e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR8_TARG_VOLT_OFFSET_SVSL1_SHFT                                                1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR8_TARG_VOLT_OFFSET_NOM_4_BMSK                                              0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR8_TARG_VOLT_OFFSET_NOM_4_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa38)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR9_TARG_VOLT_OFFSET_TUR_0_BMSK                                      0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR9_TARG_VOLT_OFFSET_TUR_0_SHFT                                              31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR9_TARG_VOLT_OFFSET_TURL1_BMSK                                      0x7c000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR9_TARG_VOLT_OFFSET_TURL1_SHFT                                              26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR9_TARG_VOLT_OFFSET_TURL3_BMSK                                       0x3e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR9_TARG_VOLT_OFFSET_TURL3_SHFT                                              21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR9_TARG_VOLT_LSVS_BMSK                                                0x1f8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR9_TARG_VOLT_LSVS_SHFT                                                      15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR9_TARG_VOLT_SVS_BMSK                                                   0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR9_TARG_VOLT_SVS_SHFT                                                        9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR9_TARG_VOLT_NOML1_BMSK                                                  0x1f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR9_TARG_VOLT_NOML1_SHFT                                                      3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR9_TARG_VOLT_TURL3_5_3_BMSK                                                0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR9_TARG_VOLT_TURL3_5_3_SHFT                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa3c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR9_AGING_2_0_BMSK                                                   0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR9_AGING_2_0_SHFT                                                           29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR9_TARG_VOLT_OFFSET_LSVS_BMSK                                       0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR9_TARG_VOLT_OFFSET_LSVS_SHFT                                               24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR9_TARG_VOLT_OFFSET_SVS_BMSK                                          0xf80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR9_TARG_VOLT_OFFSET_SVS_SHFT                                                19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR9_TARG_VOLT_OFFSET_SVSL1_BMSK                                         0x7c000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR9_TARG_VOLT_OFFSET_SVSL1_SHFT                                              14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR9_TARG_VOLT_OFFSET_NOM_BMSK                                            0x3e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR9_TARG_VOLT_OFFSET_NOM_SHFT                                                 9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR9_TARG_VOLT_OFFSET_NOML1_BMSK                                           0x1f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR9_TARG_VOLT_OFFSET_NOML1_SHFT                                               4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR9_TARG_VOLT_OFFSET_TUR_4_1_BMSK                                           0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR9_TARG_VOLT_OFFSET_TUR_4_1_SHFT                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa40)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR10_TARG_VOLT_OFFSET_NOM_2_0_BMSK                                   0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR10_TARG_VOLT_OFFSET_NOM_2_0_SHFT                                           29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR10_TARG_VOLT_LSVSD2_BMSK                                           0x1f800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR10_TARG_VOLT_LSVSD2_SHFT                                                   23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR10_TARG_VOLT_LSVSD1_BMSK                                             0x7e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR10_TARG_VOLT_LSVSD1_SHFT                                                   17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR10_TARG_VOLT_SVS_BMSK                                                 0x1f800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR10_TARG_VOLT_SVS_SHFT                                                      11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR10_TARG_VOLT_NOM_BMSK                                                   0x7e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR10_TARG_VOLT_NOM_SHFT                                                       5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR9_AGING_7_3_BMSK                                                         0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR9_AGING_7_3_SHFT                                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa44)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR10_AGING_4_0_BMSK                                                  0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR10_AGING_4_0_SHFT                                                          27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR10_TARG_VOLT_OFFSET_LSVSD2_BMSK                                     0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR10_TARG_VOLT_OFFSET_LSVSD2_SHFT                                            22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR10_TARG_VOLT_OFFSET_LSVSD1_BMSK                                      0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR10_TARG_VOLT_OFFSET_LSVSD1_SHFT                                            17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR10_TARG_VOLT_OFFSET_LSVS_BMSK                                         0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR10_TARG_VOLT_OFFSET_LSVS_SHFT                                              12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR10_TARG_VOLT_OFFSET_SVS_BMSK                                            0xf80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR10_TARG_VOLT_OFFSET_SVS_SHFT                                                7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR10_TARG_VOLT_OFFSET_SVSL1_BMSK                                           0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR10_TARG_VOLT_OFFSET_SVSL1_SHFT                                              2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR10_TARG_VOLT_OFFSET_NOM_4_3_BMSK                                          0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR10_TARG_VOLT_OFFSET_NOM_4_3_SHFT                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa48)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR11_TARG_VOLT_TUR_4_0_BMSK                                          0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR11_TARG_VOLT_TUR_4_0_SHFT                                                  27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR11_TARG_VOLT_BOOST_BMSK                                             0x7e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR11_TARG_VOLT_BOOST_SHFT                                                    21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR_GLOBAL_RC_BMSK                                                      0x1e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR_GLOBAL_RC_SHFT                                                            17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_AON_AGING_BMSK                                                           0x1fe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_AON_AGING_SHFT                                                                 9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_AON_TARG_VOLT_BMSK                                                         0x1f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_AON_TARG_VOLT_SHFT                                                             3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR10_AGING_7_5_BMSK                                                         0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR10_AGING_7_5_SHFT                                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa4c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR11_TURBO_QUOT_MIN_0_BMSK                                           0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR11_TURBO_QUOT_MIN_0_SHFT                                                   31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR11_BOOST_QUOT_MIN_BMSK                                             0x7ff80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR11_BOOST_QUOT_MIN_SHFT                                                     19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR11_TARG_VOLT_SVS2_BMSK                                                0x7e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR11_TARG_VOLT_SVS2_SHFT                                                     13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR11_TARG_VOLT_SVS_BMSK                                                  0x1f80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR11_TARG_VOLT_SVS_SHFT                                                       7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR11_TARG_VOLT_NOM_BMSK                                                    0x7e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR11_TARG_VOLT_NOM_SHFT                                                       1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR11_TARG_VOLT_TUR_5_BMSK                                                   0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR11_TARG_VOLT_TUR_5_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa50)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR11_SVS_QUOT_MIN_8_0_BMSK                                           0xff800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR11_SVS_QUOT_MIN_8_0_SHFT                                                   23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR11_NOMINAL_QUOT_MIN_BMSK                                             0x7ff800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR11_NOMINAL_QUOT_MIN_SHFT                                                   11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR11_TURBO_QUOT_MIN_11_1_BMSK                                             0x7ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR11_TURBO_QUOT_MIN_11_1_SHFT                                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa54)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR12_TARG_VOLT_BOOST_0_BMSK                                          0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR12_TARG_VOLT_BOOST_0_SHFT                                                  31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR11_AGING_BMSK                                                      0x7f800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR11_AGING_SHFT                                                              23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR11_QUOT_OFFSET_BMSK                                                  0x7f8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR11_QUOT_OFFSET_SHFT                                                        15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR11_SVS2_QUOT_MIN_BMSK                                                  0x7ff8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR11_SVS2_QUOT_MIN_SHFT                                                       3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR11_SVS_QUOT_MIN_11_9_BMSK                                                 0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR11_SVS_QUOT_MIN_11_9_SHFT                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa58)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR12_BOOST_QUOT_MIN_2_0_BMSK                                         0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR12_BOOST_QUOT_MIN_2_0_SHFT                                                 29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR12_TARG_VOLT_SVS2_BMSK                                             0x1f800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR12_TARG_VOLT_SVS2_SHFT                                                     23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR12_TARG_VOLT_SVS_BMSK                                                0x7e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR12_TARG_VOLT_SVS_SHFT                                                      17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR12_TARG_VOLT_NOM_BMSK                                                 0x1f800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR12_TARG_VOLT_NOM_SHFT                                                      11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR12_TARG_VOLT_TUR_BMSK                                                   0x7e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR12_TARG_VOLT_TUR_SHFT                                                       5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR12_TARG_VOLT_BOOST_5_1_BMSK                                              0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR12_TARG_VOLT_BOOST_5_1_SHFT                                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa5c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR12_NOMINAL_QUOT_MIN_10_0_BMSK                                      0xffe00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR12_NOMINAL_QUOT_MIN_10_0_SHFT                                              21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR12_TURBO_QUOT_MIN_BMSK                                               0x1ffe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR12_TURBO_QUOT_MIN_SHFT                                                      9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR12_BOOST_QUOT_MIN_11_3_BMSK                                             0x1ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR12_BOOST_QUOT_MIN_11_3_SHFT                                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa60)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR12_QUOT_OFFSET_6_0_BMSK                                            0xfe000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR12_QUOT_OFFSET_6_0_SHFT                                                    25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR12_SVS2_QUOT_MIN_BMSK                                               0x1ffe000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR12_SVS2_QUOT_MIN_SHFT                                                      13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR12_SVS_QUOT_MIN_BMSK                                                   0x1ffe
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR12_SVS_QUOT_MIN_SHFT                                                        1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR12_NOMINAL_QUOT_MIN_11_BMSK                                               0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR12_NOMINAL_QUOT_MIN_11_SHFT                                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa64)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR13_TARG_VOLT_SVS2_0_BMSK                                           0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR13_TARG_VOLT_SVS2_0_SHFT                                                   31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR13_TARG_VOLT_SVS_BMSK                                              0x7e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR13_TARG_VOLT_SVS_SHFT                                                      25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR13_TARG_VOLT_NOM_BMSK                                               0x1f80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR13_TARG_VOLT_NOM_SHFT                                                      19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR13_TARG_VOLT_TUR_BMSK                                                 0x7e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR13_TARG_VOLT_TUR_SHFT                                                      13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR13_TARG_VOLT_BOOST_BMSK                                                0x1f80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR13_TARG_VOLT_BOOST_SHFT                                                     7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR13_TARG_VOLT_BOOSTP_BMSK                                                 0x7e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR13_TARG_VOLT_BOOSTP_SHFT                                                    1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR12_QUOT_OFFSET_7_BMSK                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR12_QUOT_OFFSET_7_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa68)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR13_TURBO_QUOT_MIN_2_0_BMSK                                         0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR13_TURBO_QUOT_MIN_2_0_SHFT                                                 29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR13_BOOST_QUOT_MIN_BMSK                                             0x1ffe0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR13_BOOST_QUOT_MIN_SHFT                                                     17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR13_BOOSTP_QUOT_MIN_BMSK                                               0x1ffe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR13_BOOSTP_QUOT_MIN_SHFT                                                     5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR13_TARG_VOLT_SVS2_5_1_BMSK                                               0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR13_TARG_VOLT_SVS2_5_1_SHFT                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa6c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR13_SVS_QUOT_MIN_10_0_BMSK                                          0xffe00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR13_SVS_QUOT_MIN_10_0_SHFT                                                  21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR13_NOMINAL_QUOT_MIN_BMSK                                             0x1ffe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR13_NOMINAL_QUOT_MIN_SHFT                                                    9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR13_TURBO_QUOT_MIN_11_3_BMSK                                             0x1ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR13_TURBO_QUOT_MIN_11_3_SHFT                                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa70)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR14_TARG_VOLT_BOOSTP_2_0_BMSK                                       0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR14_TARG_VOLT_BOOSTP_2_0_SHFT                                               29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR13_AGING_BMSK                                                      0x1fe00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR13_AGING_SHFT                                                              21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR13_QUOT_OFFSET_BMSK                                                  0x1fe000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR13_QUOT_OFFSET_SHFT                                                        13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR13_SVS2_QUOT_MIN_BMSK                                                  0x1ffe
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR13_SVS2_QUOT_MIN_SHFT                                                       1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR13_SVS_QUOT_MIN_11_BMSK                                                   0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR13_SVS_QUOT_MIN_11_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa74)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR14_TARG_VOLT_SVS2_4_0_BMSK                                         0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR14_TARG_VOLT_SVS2_4_0_SHFT                                                 27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR14_TARG_VOLT_SVS_BMSK                                               0x7e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR14_TARG_VOLT_SVS_SHFT                                                      21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR14_TARG_VOLT_NOM_BMSK                                                0x1f8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR14_TARG_VOLT_NOM_SHFT                                                      15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR14_TARG_VOLT_TUR_BMSK                                                  0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR14_TARG_VOLT_TUR_SHFT                                                       9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR14_TARG_VOLT_BOOST_BMSK                                                 0x1f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR14_TARG_VOLT_BOOST_SHFT                                                     3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR14_TARG_VOLT_BOOSTP_5_3_BMSK                                              0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR14_TARG_VOLT_BOOSTP_5_3_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa78)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR14_TURBO_QUOT_MIN_6_0_BMSK                                         0xfe000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR14_TURBO_QUOT_MIN_6_0_SHFT                                                 25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR14_BOOST_QUOT_MIN_BMSK                                              0x1ffe000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR14_BOOST_QUOT_MIN_SHFT                                                     13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR14_BOOSTP_QUOT_MIN_BMSK                                                0x1ffe
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR14_BOOSTP_QUOT_MIN_SHFT                                                     1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR14_TARG_VOLT_SVS2_5_BMSK                                                  0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR14_TARG_VOLT_SVS2_5_SHFT                                                    0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa7c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR14_SVS2_QUOT_MIN_2_0_BMSK                                          0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR14_SVS2_QUOT_MIN_2_0_SHFT                                                  29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR14_SVS_QUOT_MIN_BMSK                                               0x1ffe0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR14_SVS_QUOT_MIN_SHFT                                                       17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR14_NOMINAL_QUOT_MIN_BMSK                                              0x1ffe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR14_NOMINAL_QUOT_MIN_SHFT                                                    5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR14_TURBO_QUOT_MIN_11_7_BMSK                                              0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR14_TURBO_QUOT_MIN_11_7_SHFT                                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa80)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR15_TARG_VOLT_TUR_2_0_BMSK                                          0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR15_TARG_VOLT_TUR_2_0_SHFT                                                  29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR15_TARG_VOLT_BOOST_BMSK                                            0x1f800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR15_TARG_VOLT_BOOST_SHFT                                                    23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR15_TARG_VOLT_BOOSTP_BMSK                                             0x7e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR15_TARG_VOLT_BOOSTP_SHFT                                                   17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR14_QUOT_OFFSET_BMSK                                                   0x1fe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR14_QUOT_OFFSET_SHFT                                                         9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR14_SVS2_QUOT_MIN_11_3_BMSK                                              0x1ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR14_SVS2_QUOT_MIN_11_3_SHFT                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa84)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR15_BOOSTP_QUOT_MIN_10_0_BMSK                                       0xffe00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR15_BOOSTP_QUOT_MIN_10_0_SHFT                                               21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR15_TARG_VOLT_SVS2_BMSK                                               0x1f8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR15_TARG_VOLT_SVS2_SHFT                                                     15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR15_TARG_VOLT_SVS_BMSK                                                  0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR15_TARG_VOLT_SVS_SHFT                                                       9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR15_TARG_VOLT_NOM_BMSK                                                   0x1f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR15_TARG_VOLT_NOM_SHFT                                                       3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR15_TARG_VOLT_TUR_5_3_BMSK                                                 0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR15_TARG_VOLT_TUR_5_3_SHFT                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa88)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR15_NOMINAL_QUOT_MIN_6_0_BMSK                                       0xfe000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR15_NOMINAL_QUOT_MIN_6_0_SHFT                                               25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR15_TURBO_QUOT_MIN_BMSK                                              0x1ffe000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR15_TURBO_QUOT_MIN_SHFT                                                     13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR15_BOOST_QUOT_MIN_BMSK                                                 0x1ffe
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR15_BOOST_QUOT_MIN_SHFT                                                      1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR15_BOOSTP_QUOT_MIN_11_BMSK                                                0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR15_BOOSTP_QUOT_MIN_11_SHFT                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa8c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR15_QUOT_OFFSET_2_0_BMSK                                            0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR15_QUOT_OFFSET_2_0_SHFT                                                    29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR15_SVS2_QUOT_MIN_BMSK                                              0x1ffe0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR15_SVS2_QUOT_MIN_SHFT                                                      17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR15_SVS_QUOT_MIN_BMSK                                                  0x1ffe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR15_SVS_QUOT_MIN_SHFT                                                        5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR15_NOMINAL_QUOT_MIN_11_7_BMSK                                            0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR15_NOMINAL_QUOT_MIN_11_7_SHFT                                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa90)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_MXC_MODE_DISABLE_BMSK                                             0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_MXC_MODE_DISABLE_SHFT                                                     29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_MX_MODE_DISABLE_BMSK                                              0x1c000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_MX_MODE_DISABLE_SHFT                                                      26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_GFX_MODE_DISABLE_BMSK                                              0x3800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_GFX_MODE_DISABLE_SHFT                                                     23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_MSS_MODE_DISABLE_BMSK                                               0x700000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_MSS_MODE_DISABLE_SHFT                                                     20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_CX_MODE_DISABLE_BMSK                                                 0xe0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_CX_MODE_DISABLE_SHFT                                                      17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_LOCAL_RC_BMSK                                                        0x1e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_LOCAL_RC_SHFT                                                             13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR15_AGING_BMSK                                                          0x1fe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR15_AGING_SHFT                                                               5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR15_QUOT_OFFSET_7_3_BMSK                                                  0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR15_QUOT_OFFSET_7_3_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa94)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_RESERVED_1_0_BMSK                                                 0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_RESERVED_1_0_SHFT                                                         30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_APC2_GOLD_MODE_DISABLE_BMSK                                       0x38000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_APC2_GOLD_MODE_DISABLE_SHFT                                               27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_APC1_GOLDP_MODE_DISABLE_BMSK                                       0x7000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_APC1_GOLDP_MODE_DISABLE_SHFT                                              24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_APC1_GOLD_MODE_DISABLE_BMSK                                         0xe00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_APC1_GOLD_MODE_DISABLE_SHFT                                               21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_APC0_L3_MODE_DISABLE_BMSK                                           0x1c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_APC0_L3_MODE_DISABLE_SHFT                                                 18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_APC0_SILVER_MODE_DISABLE_BMSK                                        0x38000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_APC0_SILVER_MODE_DISABLE_SHFT                                             15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_NSP2_MODE_DISABLE_BMSK                                                0x7000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_NSP2_MODE_DISABLE_SHFT                                                    12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_NSP1_MODE_DISABLE_BMSK                                                 0xe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_NSP1_MODE_DISABLE_SHFT                                                     9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_MMCX_MODE_DISABLE_BMSK                                                 0x1c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_MMCX_MODE_DISABLE_SHFT                                                     6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_LPICX_MODE_DISABLE_BMSK                                                 0x38
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_LPICX_MODE_DISABLE_SHFT                                                    3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_LPIMX_MODE_DISABLE_BMSK                                                  0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR_LPIMX_MODE_DISABLE_SHFT                                                    0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa98)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR_RESERVED_33_2_BMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR_RESERVED_33_2_SHFT                                                         0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa9c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_DHRY_POWER_TJ_SPEC2_BMSK                                              0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_DHRY_POWER_TJ_SPEC2_SHFT                                                      24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_DHRY_POWER_TJ_SPEC1_BMSK                                                0xff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_DHRY_POWER_TJ_SPEC1_SHFT                                                      16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_CPR_RESERVED_49_34_BMSK                                                   0xffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_CPR_RESERVED_49_34_SHFT                                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xaa0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ACC_HV_MXA_2_0_BMSK                                                   0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ACC_HV_MXA_2_0_SHFT                                                           29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_GNSS_ADC_CAL_BMSK                                                     0x1f800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_GNSS_ADC_CAL_SHFT                                                             23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_APC0_PEAK_THROTTLE_FREQ_BMSK                                            0x600000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_APC0_PEAK_THROTTLE_FREQ_SHFT                                                  21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_APC0_PEAK_THROTTLE_TJ_BMSK                                              0x1f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_APC0_PEAK_THROTTLE_TJ_SHFT                                                    16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS98_AUP8_BMSK                                          0x8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS98_AUP8_SHFT                                              15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS98_AUP7_BMSK                                          0x4000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS98_AUP7_SHFT                                              14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS98_AUP6_BMSK                                          0x2000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS98_AUP6_SHFT                                              13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS98_AUP5_BMSK                                          0x1000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS98_AUP5_SHFT                                              12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS98_AUP4_BMSK                                           0x800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS98_AUP4_SHFT                                              11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS98_AUP3_BMSK                                           0x400
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS98_AUP3_SHFT                                              10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS98_AUP2_BMSK                                           0x200
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS98_AUP2_SHFT                                               9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS98_AUP1_BMSK                                           0x100
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS98_AUP1_SHFT                                               8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS65_AG2_BMSK                                             0x80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS65_AG2_SHFT                                                7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS65_AG1_BMSK                                             0x40
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS65_AG1_SHFT                                                6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU__DYN_MEM_ACC_BITS65_AU_BMSK                                             0x20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU__DYN_MEM_ACC_BITS65_AU_SHFT                                                5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS65_AU2_BMSK                                             0x10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS65_AU2_SHFT                                                4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS65_AU1_BMSK                                              0x8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS65_AU1_SHFT                                                3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS65_AUP_BMSK                                              0x4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS65_AUP_SHFT                                                2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS65_AUP2_BMSK                                             0x2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS65_AUP2_SHFT                                               1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS65_AUP1_BMSK                                             0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CPU_DYN_MEM_ACC_BITS65_AUP1_SHFT                                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xaa4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ACC_HV_APC1_4_0_BMSK                                                  0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ACC_HV_APC1_4_0_SHFT                                                          27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ACC_HV_APC0_BMSK                                                       0x7e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ACC_HV_APC0_SHFT                                                              21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ACC_LV_MXC_BMSK                                                         0x1f8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ACC_LV_MXC_SHFT                                                               15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ACC_LV_MXA_BMSK                                                           0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ACC_LV_MXA_SHFT                                                                9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ACC_HV_MXC_BMSK                                                            0x1f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ACC_HV_MXC_SHFT                                                                3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ACC_HV_MXA_5_3_BMSK                                                          0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ACC_HV_MXA_5_3_SHFT                                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xaa8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_AOSS_N1_2_0_BMSK                                                      0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_AOSS_N1_2_0_SHFT                                                              29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_AOSS_K_BMSK                                                           0x1fffe000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_AOSS_K_SHFT                                                                   13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ACC_LV_APC1_BMSK                                                          0x1f80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ACC_LV_APC1_SHFT                                                               7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ACC_LV_APC0_BMSK                                                            0x7e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ACC_LV_APC0_SHFT                                                               1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ACC_HV_APC1_5_BMSK                                                           0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ACC_HV_APC1_5_SHFT                                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xaac)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_AOSS_P1_16_0_BMSK                                                     0xffff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_AOSS_P1_16_0_SHFT                                                             15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_AOSS_N1_17_3_BMSK                                                         0x7fff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_AOSS_N1_17_3_SHFT                                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xab0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS_C1_BASE0_0_BMSK                                                 0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS_C1_BASE0_0_SHFT                                                         31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS_C0_BASE1_BMSK                                                   0x7fe00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS_C0_BASE1_SHFT                                                           21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS_C0_BASE0_BMSK                                                     0x1ff800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS_C0_BASE0_SHFT                                                           11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_AOSS_TDOPCODE_BMSK                                                         0x7c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_AOSS_TDOPCODE_SHFT                                                             6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_AOSS_RDOPCODE_BMSK                                                          0x3e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_AOSS_RDOPCODE_SHFT                                                             1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_AOSS_P1_17_BMSK                                                              0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_AOSS_P1_17_SHFT                                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xab4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS_C2_BASE1_2_0_BMSK                                               0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS_C2_BASE1_2_0_SHFT                                                       29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS_C2_BASE0_BMSK                                                   0x1ff80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS_C2_BASE0_SHFT                                                           19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS_C1_BASE1_BMSK                                                      0x7fe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS_C1_BASE1_SHFT                                                            9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS_C1_BASE0_9_1_BMSK                                                    0x1ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS_C1_BASE0_9_1_SHFT                                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xab8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS4_C0_OFFSET_BMSK                                                 0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS4_C0_OFFSET_SHFT                                                         27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS3_C0_OFFSET_BMSK                                                  0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS3_C0_OFFSET_SHFT                                                         22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS2_C0_OFFSET_BMSK                                                   0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS2_C0_OFFSET_SHFT                                                         17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS1_C0_OFFSET_BMSK                                                    0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS1_C0_OFFSET_SHFT                                                         12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS0_C0_OFFSET_BMSK                                                      0xf80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS0_C0_OFFSET_SHFT                                                          7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS_C2_BASE1_9_3_BMSK                                                     0x7f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS_C2_BASE1_9_3_SHFT                                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xabc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS11_C0_OFFSET_1_0_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS11_C0_OFFSET_1_0_SHFT                                                    30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS10_C0_OFFSET_BMSK                                                0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS10_C0_OFFSET_SHFT                                                        25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS9_C0_OFFSET_BMSK                                                  0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS9_C0_OFFSET_SHFT                                                         20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS8_C0_OFFSET_BMSK                                                    0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS8_C0_OFFSET_SHFT                                                         15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS7_C0_OFFSET_BMSK                                                     0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS7_C0_OFFSET_SHFT                                                         10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS6_C0_OFFSET_BMSK                                                      0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS6_C0_OFFSET_SHFT                                                          5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS5_C0_OFFSET_BMSK                                                       0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS5_C0_OFFSET_SHFT                                                          0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xac0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS17_C1_OFFSET_3_0_BMSK                                            0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS17_C1_OFFSET_3_0_SHFT                                                    28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS16_C1_OFFSET_BMSK                                                 0xf800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS16_C1_OFFSET_SHFT                                                        23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS15_C1_OFFSET_BMSK                                                  0x7c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS15_C1_OFFSET_SHFT                                                        18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS14_C0_OFFSET_BMSK                                                   0x3e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS14_C0_OFFSET_SHFT                                                        13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS13_C0_OFFSET_BMSK                                                    0x1f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS13_C0_OFFSET_SHFT                                                         8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS12_C0_OFFSET_BMSK                                                      0xf8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS12_C0_OFFSET_SHFT                                                         3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS11_C0_OFFSET_4_2_BMSK                                                   0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS11_C0_OFFSET_4_2_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xac4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS24_C1_OFFSET_0_BMSK                                              0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS24_C1_OFFSET_0_SHFT                                                      31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS23_C1_OFFSET_BMSK                                                0x7c000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS23_C1_OFFSET_SHFT                                                        26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS22_C1_OFFSET_BMSK                                                 0x3e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS22_C1_OFFSET_SHFT                                                        21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS21_C1_OFFSET_BMSK                                                  0x1f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS21_C1_OFFSET_SHFT                                                        16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS20_C1_OFFSET_BMSK                                                    0xf800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS20_C1_OFFSET_SHFT                                                        11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS19_C1_OFFSET_BMSK                                                     0x7c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS19_C1_OFFSET_SHFT                                                         6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS18_C1_OFFSET_BMSK                                                      0x3e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS18_C1_OFFSET_SHFT                                                         1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS17_C1_OFFSET_4_BMSK                                                     0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS17_C1_OFFSET_4_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xac8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS30_C1_OFFSET_2_0_BMSK                                            0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS30_C1_OFFSET_2_0_SHFT                                                    29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS29_C1_OFFSET_BMSK                                                0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS29_C1_OFFSET_SHFT                                                        24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS28_C1_OFFSET_BMSK                                                  0xf80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS28_C1_OFFSET_SHFT                                                        19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS27_C1_OFFSET_BMSK                                                   0x7c000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS27_C1_OFFSET_SHFT                                                        14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS26_C1_OFFSET_BMSK                                                    0x3e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS26_C1_OFFSET_SHFT                                                         9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS25_C1_OFFSET_BMSK                                                     0x1f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS25_C1_OFFSET_SHFT                                                         4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS24_C1_OFFSET_4_1_BMSK                                                   0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_TSENS24_C1_OFFSET_4_1_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xacc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS36_C2_OFFSET_BMSK                                                0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS36_C2_OFFSET_SHFT                                                        27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS35_C2_OFFSET_BMSK                                                 0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS35_C2_OFFSET_SHFT                                                        22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS34_C2_OFFSET_BMSK                                                  0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS34_C2_OFFSET_SHFT                                                        17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS33_C2_OFFSET_BMSK                                                   0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS33_C2_OFFSET_SHFT                                                        12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS32_C2_OFFSET_BMSK                                                     0xf80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS32_C2_OFFSET_SHFT                                                         7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS31_C2_OFFSET_BMSK                                                      0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS31_C2_OFFSET_SHFT                                                         2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS30_C1_OFFSET_4_3_BMSK                                                   0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_TSENS30_C1_OFFSET_4_3_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xad0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_TSENS43_C2_OFFSET_1_0_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_TSENS43_C2_OFFSET_1_0_SHFT                                                    30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_TSENS42_C2_OFFSET_BMSK                                                0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_TSENS42_C2_OFFSET_SHFT                                                        25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_TSENS41_C2_OFFSET_BMSK                                                 0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_TSENS41_C2_OFFSET_SHFT                                                        20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_TSENS40_C2_OFFSET_BMSK                                                   0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_TSENS40_C2_OFFSET_SHFT                                                        15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_TSENS39_C2_OFFSET_BMSK                                                    0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_TSENS39_C2_OFFSET_SHFT                                                        10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_TSENS38_C2_OFFSET_BMSK                                                     0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_TSENS38_C2_OFFSET_SHFT                                                         5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_TSENS37_C2_OFFSET_BMSK                                                      0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_TSENS37_C2_OFFSET_SHFT                                                         0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xad4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ACD_NSP1_DVM_LSVSD2_12_0_BMSK                                         0xfff80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ACD_NSP1_DVM_LSVSD2_12_0_SHFT                                                 19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ACD_NSP1_DVM_ENABLE_BMSK                                                 0x7fe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ACD_NSP1_DVM_ENABLE_SHFT                                                       9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ACD_NSP1_REVISION_BIT_BMSK                                                 0x180
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ACD_NSP1_REVISION_BIT_SHFT                                                     7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_TSENS_REV_CTRL_BMSK                                                         0x40
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_TSENS_REV_CTRL_SHFT                                                            6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_TSENS_CAL_SEL_BMSK                                                          0x38
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_TSENS_CAL_SEL_SHFT                                                             3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_TSENS43_C2_OFFSET_4_2_BMSK                                                   0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_TSENS43_C2_OFFSET_4_2_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xad8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ACD_NSP1_DVM_LSVSD1_20_0_BMSK                                         0xfffff800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ACD_NSP1_DVM_LSVSD1_20_0_SHFT                                                 11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ACD_NSP1_DVM_LSVSD2_23_13_BMSK                                             0x7ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ACD_NSP1_DVM_LSVSD2_23_13_SHFT                                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xadc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ACD_NSP1_DVM_SVS_4_0_BMSK                                             0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ACD_NSP1_DVM_SVS_4_0_SHFT                                                     27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ACD_NSP1_DVM_LSVS_BMSK                                                 0x7fffff8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ACD_NSP1_DVM_LSVS_SHFT                                                         3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ACD_NSP1_DVM_LSVSD1_23_21_BMSK                                               0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ACD_NSP1_DVM_LSVSD1_23_21_SHFT                                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xae0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ACD_NSP1_DVM_SVSL1_12_0_BMSK                                          0xfff80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ACD_NSP1_DVM_SVSL1_12_0_SHFT                                                  19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ACD_NSP1_DVM_SVS_23_5_BMSK                                               0x7ffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ACD_NSP1_DVM_SVS_23_5_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xae4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ACD_NSP1_DVM_NOM_20_0_BMSK                                            0xfffff800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ACD_NSP1_DVM_NOM_20_0_SHFT                                                    11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ACD_NSP1_DVM_SVSL1_23_13_BMSK                                              0x7ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ACD_NSP1_DVM_SVSL1_23_13_SHFT                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xae8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ACD_NSP1_DVM_TUR_4_0_BMSK                                             0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ACD_NSP1_DVM_TUR_4_0_SHFT                                                     27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ACD_NSP1_DVM_NOML1_BMSK                                                0x7fffff8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ACD_NSP1_DVM_NOML1_SHFT                                                        3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ACD_NSP1_DVM_NOM_23_21_BMSK                                                  0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ACD_NSP1_DVM_NOM_23_21_SHFT                                                    0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xaec)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ACD_NSP1_DVM_TURL1_12_0_BMSK                                          0xfff80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ACD_NSP1_DVM_TURL1_12_0_SHFT                                                  19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ACD_NSP1_DVM_TUR_23_5_BMSK                                               0x7ffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ACD_NSP1_DVM_TUR_23_5_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xaf0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ACD_NSP1_DVM_TURL3_20_0_BMSK                                          0xfffff800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ACD_NSP1_DVM_TURL3_20_0_SHFT                                                  11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ACD_NSP1_DVM_TURL1_23_13_BMSK                                              0x7ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ACD_NSP1_DVM_TURL1_23_13_SHFT                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xaf4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ACD_NSP2_DVM_LSVSD2_16_0_BMSK                                         0xffff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ACD_NSP2_DVM_LSVSD2_16_0_SHFT                                                 15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ACD_NSP2_DVM_ENABLE_BMSK                                                  0x7fe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ACD_NSP2_DVM_ENABLE_SHFT                                                       5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ACD_NSP2_REVISION_BIT_BMSK                                                  0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ACD_NSP2_REVISION_BIT_SHFT                                                     3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ACD_NSP1_DVM_TURL3_23_21_BMSK                                                0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ACD_NSP1_DVM_TURL3_23_21_SHFT                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xaf8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ACD_NSP2_DVM_LSVS_0_BMSK                                              0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ACD_NSP2_DVM_LSVS_0_SHFT                                                      31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ACD_NSP2_DVM_LSVSD1_BMSK                                              0x7fffff80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ACD_NSP2_DVM_LSVSD1_SHFT                                                       7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ACD_NSP2_DVM_LSVSD2_23_17_BMSK                                              0x7f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ACD_NSP2_DVM_LSVSD2_23_17_SHFT                                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xafc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ACD_NSP2_DVM_SVS_8_0_BMSK                                             0xff800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ACD_NSP2_DVM_SVS_8_0_SHFT                                                     23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ACD_NSP2_DVM_LSVS_23_1_BMSK                                             0x7fffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ACD_NSP2_DVM_LSVS_23_1_SHFT                                                    0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb00)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ACD_NSP2_DVM_SVSL1_16_0_BMSK                                          0xffff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ACD_NSP2_DVM_SVSL1_16_0_SHFT                                                  15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ACD_NSP2_DVM_SVS_23_9_BMSK                                                0x7fff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ACD_NSP2_DVM_SVS_23_9_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb04)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ACD_NSP2_DVM_NOML1_0_BMSK                                             0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ACD_NSP2_DVM_NOML1_0_SHFT                                                     31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ACD_NSP2_DVM_NOM_BMSK                                                 0x7fffff80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ACD_NSP2_DVM_NOM_SHFT                                                          7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ACD_NSP2_DVM_SVSL1_23_17_BMSK                                               0x7f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ACD_NSP2_DVM_SVSL1_23_17_SHFT                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb08)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ACD_NSP2_DVM_TUR_8_0_BMSK                                             0xff800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ACD_NSP2_DVM_TUR_8_0_SHFT                                                     23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ACD_NSP2_DVM_NOML1_23_1_BMSK                                            0x7fffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ACD_NSP2_DVM_NOML1_23_1_SHFT                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb0c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ACD_NSP2_DVM_TURL1_16_0_BMSK                                          0xffff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ACD_NSP2_DVM_TURL1_16_0_SHFT                                                  15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ACD_NSP2_DVM_TUR_23_9_BMSK                                                0x7fff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ACD_NSP2_DVM_TUR_23_9_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb10)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_OPAMP_FUSE_CPURAIL_CPU4_WS_0_BMSK                                     0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_OPAMP_FUSE_CPURAIL_CPU4_WS_0_SHFT                                             31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ACD_NSP2_DVM_TURL3_BMSK                                               0x7fffff80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ACD_NSP2_DVM_TURL3_SHFT                                                        7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ACD_NSP2_DVM_TURL1_23_17_BMSK                                               0x7f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ACD_NSP2_DVM_TURL1_23_17_SHFT                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb14)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_OPAMP_FUSE_CPURAIL_CPU6_FT_2_0_BMSK                                   0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_OPAMP_FUSE_CPURAIL_CPU6_FT_2_0_SHFT                                           29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_OPAMP_FUSE_CPURAIL_CPU6_WS_BMSK                                       0x1f800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_OPAMP_FUSE_CPURAIL_CPU6_WS_SHFT                                               23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_OPAMP_FUSE_CPURAIL_CPU5_FT_BMSK                                         0x7e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_OPAMP_FUSE_CPURAIL_CPU5_FT_SHFT                                               17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_OPAMP_FUSE_CPURAIL_CPU5_WS_BMSK                                          0x1f800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_OPAMP_FUSE_CPURAIL_CPU5_WS_SHFT                                               11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_OPAMP_FUSE_CPURAIL_CPU4_FT_BMSK                                            0x7e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_OPAMP_FUSE_CPURAIL_CPU4_FT_SHFT                                                5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_OPAMP_FUSE_CPURAIL_CPU4_WS_5_1_BMSK                                         0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_OPAMP_FUSE_CPURAIL_CPU4_WS_5_1_SHFT                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb18)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_OPAMP_FUSE_CPURAIL_CPU9_WS_4_0_BMSK                                   0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_OPAMP_FUSE_CPURAIL_CPU9_WS_4_0_SHFT                                           27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_OPAMP_FUSE_CPURAIL_CPU8_FT_BMSK                                        0x7e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_OPAMP_FUSE_CPURAIL_CPU8_FT_SHFT                                               21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_OPAMP_FUSE_CPURAIL_CPU8_WS_BMSK                                         0x1f8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_OPAMP_FUSE_CPURAIL_CPU8_WS_SHFT                                               15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_OPAMP_FUSE_CPURAIL_CPU7_FT_BMSK                                           0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_OPAMP_FUSE_CPURAIL_CPU7_FT_SHFT                                                9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_OPAMP_FUSE_CPURAIL_CPU7_WS_BMSK                                            0x1f8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_OPAMP_FUSE_CPURAIL_CPU7_WS_SHFT                                                3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_OPAMP_FUSE_CPURAIL_CPU6_FT_5_3_BMSK                                          0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_OPAMP_FUSE_CPURAIL_CPU6_FT_5_3_SHFT                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb1c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ISENSE_FUSE_CURRENT_CPU5_F1_4_0_BMSK                                  0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ISENSE_FUSE_CURRENT_CPU5_F1_4_0_SHFT                                          27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ISENSE_FUSE_CURRENT_CPU4_F2_BMSK                                       0x7fe0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ISENSE_FUSE_CURRENT_CPU4_F2_SHFT                                              17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ISENSE_FUSE_CURRENT_CPU4_F1_BMSK                                         0x1ff80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ISENSE_FUSE_CURRENT_CPU4_F1_SHFT                                               7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_OPAMP_FUSE_CPURAIL_CPU9_FT_BMSK                                             0x7e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_OPAMP_FUSE_CPURAIL_CPU9_FT_SHFT                                                1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_OPAMP_FUSE_CPURAIL_CPU9_WS_5_BMSK                                            0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_OPAMP_FUSE_CPURAIL_CPU9_WS_5_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb20)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ISENSE_FUSE_CURRENT_CPU6_F2_6_0_BMSK                                  0xfe000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ISENSE_FUSE_CURRENT_CPU6_F2_6_0_SHFT                                          25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ISENSE_FUSE_CURRENT_CPU6_F1_BMSK                                       0x1ff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ISENSE_FUSE_CURRENT_CPU6_F1_SHFT                                              15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ISENSE_FUSE_CURRENT_CPU5_F2_BMSK                                          0x7fe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ISENSE_FUSE_CURRENT_CPU5_F2_SHFT                                               5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ISENSE_FUSE_CURRENT_CPU5_F1_9_5_BMSK                                        0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ISENSE_FUSE_CURRENT_CPU5_F1_9_5_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb24)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ISENSE_FUSE_CURRENT_CPU8_F1_8_0_BMSK                                  0xff800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ISENSE_FUSE_CURRENT_CPU8_F1_8_0_SHFT                                          23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ISENSE_FUSE_CURRENT_CPU7_F2_BMSK                                        0x7fe000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ISENSE_FUSE_CURRENT_CPU7_F2_SHFT                                              13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ISENSE_FUSE_CURRENT_CPU7_F1_BMSK                                          0x1ff8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ISENSE_FUSE_CURRENT_CPU7_F1_SHFT                                               3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ISENSE_FUSE_CURRENT_CPU6_F2_9_7_BMSK                                         0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ISENSE_FUSE_CURRENT_CPU6_F2_9_7_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb28)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ISENSE_FUSE_VOLTAGE_CPU4_WS_0_BMSK                                    0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ISENSE_FUSE_VOLTAGE_CPU4_WS_0_SHFT                                            31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ISENSE_FUSE_CURRENT_CPU9_F2_BMSK                                      0x7fe00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ISENSE_FUSE_CURRENT_CPU9_F2_SHFT                                              21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ISENSE_FUSE_CURRENT_CPU9_F1_BMSK                                        0x1ff800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ISENSE_FUSE_CURRENT_CPU9_F1_SHFT                                              11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ISENSE_FUSE_CURRENT_CPU8_F2_BMSK                                           0x7fe
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ISENSE_FUSE_CURRENT_CPU8_F2_SHFT                                               1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ISENSE_FUSE_CURRENT_CPU8_F1_9_BMSK                                           0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ISENSE_FUSE_CURRENT_CPU8_F1_9_SHFT                                             0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb2c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ISENSE_FUSE_VOLTAGE_CPU5_FT_2_0_BMSK                                  0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ISENSE_FUSE_VOLTAGE_CPU5_FT_2_0_SHFT                                          29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ISENSE_FUSE_VOLTAGE_CPU4_FT_BMSK                                      0x1ff80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ISENSE_FUSE_VOLTAGE_CPU4_FT_SHFT                                              19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ISENSE_FUSE_VOLTAGE_CPU5_WS_BMSK                                         0x7fe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ISENSE_FUSE_VOLTAGE_CPU5_WS_SHFT                                               9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ISENSE_FUSE_VOLTAGE_CPU4_WS_9_1_BMSK                                       0x1ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ISENSE_FUSE_VOLTAGE_CPU4_WS_9_1_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb30)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_CALIBRATION_2719_2695_BMSK                                            0xffffff80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_CALIBRATION_2719_2695_SHFT                                                     7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ISENSE_FUSE_VOLTAGE_CPU5_FT_9_3_BMSK                                        0x7f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ISENSE_FUSE_VOLTAGE_CPU5_FT_9_3_SHFT                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb34)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_CALIBRATION_2751_2720_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_CALIBRATION_2751_2720_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb38)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_GFX_FUSE_RESERVED_2_0_BMSK                                            0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_GFX_FUSE_RESERVED_2_0_SHFT                                                    29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_GFX_PEAK_CURRENT_DELTA_BMSK                                           0x1ffe0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_GFX_PEAK_CURRENT_DELTA_SHFT                                                   17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_GFX_PEAK_VOLTAGE_HF_BMSK                                                 0x1ff80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_GFX_PEAK_VOLTAGE_HF_SHFT                                                       7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_GFX_PEAK_VOLTAGE_DELTA_BMSK                                                 0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_GFX_PEAK_VOLTAGE_DELTA_SHFT                                                    2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_GFX_FUSE_CDYN_REVISION_BIT_BMSK                                              0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_GFX_FUSE_CDYN_REVISION_BIT_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb3c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_CURRENT_REVISION_BIT_BMSK                                         0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_CURRENT_REVISION_BIT_SHFT                                                 30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_FUSE_RESERVED_16_0_BMSK                                           0x3fffe000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_FUSE_RESERVED_16_0_SHFT                                                   13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_PEAK_CURRENT_LF_BMSK                                                  0x1fff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_PEAK_CURRENT_LF_SHFT                                                       0


#endif /* __HALHWIOTSENSFUSES_H__ */
