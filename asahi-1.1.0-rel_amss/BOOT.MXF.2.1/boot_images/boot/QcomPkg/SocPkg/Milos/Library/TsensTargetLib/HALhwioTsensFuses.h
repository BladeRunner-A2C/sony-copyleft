#ifndef HALHWIOTSENSFUSES_H
#define HALHWIOTSENSFUSES_H
/*
===========================================================================
*/
/**
    @file HALhwioTsensFuses.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM6xxx (Milos) [z_tme_fusecontroller_1.0_p3q3rblk]
 
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
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_CALIBRATION_30_16_BMSK                                                 0x7fff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_CALIBRATION_30_16_SHFT                                                         16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_1_WEST_BGV_TRIM_BMSK                                                0xff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_1_WEST_BGV_TRIM_SHFT                                                     8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_0_EAST_BGV_TRIM_BMSK                                                  0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_0_EAST_BGV_TRIM_SHFT                                                     0

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
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH3DQ0_PNTUNE_HT_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH3DQ0_PNTUNE_HT_SHFT                                                    30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH3CA_PNTUNE_HT_BMSK                                             0x30000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH3CA_PNTUNE_HT_SHFT                                                     28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH2DQ1_PNTUNE_HT_BMSK                                             0xc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH2DQ1_PNTUNE_HT_SHFT                                                    26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH2DQ0_PNTUNE_HT_BMSK                                             0x3000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH2DQ0_PNTUNE_HT_SHFT                                                    24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_SVS2_BMSK                                                 0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_SVS2_SHFT                                                       18
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
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CALIBRATION_191_188_BMSK                                               0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CALIBRATION_191_188_SHFT                                                       28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_LPASSQ6_MR_BMSK                                                         0x8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_LPASSQ6_MR_SHFT                                                                27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR11_BOOST_QUOT_MIN_BMSK                                               0x7ff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR11_BOOST_QUOT_MIN_SHFT                                                      15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR11_TARG_VOLT_BOOST_BMSK                                                 0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR11_TARG_VOLT_BOOST_SHFT                                                      9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_DDRSS_EW_FUSE_2_BMSK                                                        0x1fc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_DDRSS_EW_FUSE_2_SHFT                                                            2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_DDRSS_CH3DQ1_PNTUNE_HT_BMSK                                                   0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_DDRSS_CH3DQ1_PNTUNE_HT_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa00)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CALIBRATION_223_208_BMSK                                               0xffff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CALIBRATION_223_208_SHFT                                                       16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR7_TARG_VOLT_SVS2_BMSK                                                   0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR7_TARG_VOLT_SVS2_SHFT                                                       10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR4_TARG_VOLT_OFFSET_SVS3_BMSK                                             0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR4_TARG_VOLT_OFFSET_SVS3_SHFT                                                 5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR2_TARG_VOLT_OFFSET_TURL0_BMSK                                             0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CPR2_TARG_VOLT_OFFSET_TURL0_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa04)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CALIBRATION_255_224_BMSK                                               0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CALIBRATION_255_224_SHFT                                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa08)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CALIBRATION_287_286_BMSK                                               0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CALIBRATION_287_286_SHFT                                                       30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ACC_HV_MX_BMSK                                                         0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ACC_HV_MX_SHFT                                                                 24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CALIBRATION_279_256_BMSK                                                 0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CALIBRATION_279_256_SHFT                                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa0c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR0_TARG_VOLT_OFFSET_NOM_BMSK                                         0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR0_TARG_VOLT_OFFSET_NOM_SHFT                                                 27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR0_TARG_VOLT_OFFSET_NOML1_BMSK                                        0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR0_TARG_VOLT_OFFSET_NOML1_SHFT                                               22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR0_TARG_VOLT_OFFSET_TUR_BMSK                                           0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR0_TARG_VOLT_OFFSET_TUR_SHFT                                                 17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR0_TARG_VOLT_OFFSET_TURL1_BMSK                                          0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR0_TARG_VOLT_OFFSET_TURL1_SHFT                                               12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CALIBRATION_299_294_BMSK                                                    0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CALIBRATION_299_294_SHFT                                                        6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ACC_LV_MX_BMSK                                                               0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ACC_LV_MX_SHFT                                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa10)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S5_BMSK                                                   0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S5_SHFT                                                           28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S4_BMSK                                                    0xf000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S4_SHFT                                                           24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S3_BMSK                                                     0xf00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S3_SHFT                                                           20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S2_BMSK                                                      0xf0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S2_SHFT                                                           16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S1_BMSK                                                       0xf000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S1_SHFT                                                           12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S0_BMSK                                                        0xf00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S0_SHFT                                                            8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_BMSK                                                            0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_SHFT                                                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa14)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S2_BMSK                                                   0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S2_SHFT                                                           28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S1_BMSK                                                    0xf000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S1_SHFT                                                           24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S0_BMSK                                                     0xf00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S0_SHFT                                                           20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_BMSK                                                         0xff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_SHFT                                                              12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CALIBRATION_363_360_BMSK                                                    0xf00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_CALIBRATION_363_360_SHFT                                                        8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE1_S7_BMSK                                                         0xf0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE1_S7_SHFT                                                            4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE1_S6_BMSK                                                          0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE1_S6_SHFT                                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa18)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR0_TARG_VOLT_OFFSET_SVSL1_BMSK                                       0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR0_TARG_VOLT_OFFSET_SVSL1_SHFT                                               27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE_REVISION_CONTROL_BMSK                                       0x7000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE_REVISION_CONTROL_SHFT                                              24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CALIBRATION_407_404_BMSK                                                 0xf00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CALIBRATION_407_404_SHFT                                                       20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S7_BMSK                                                      0xf0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S7_SHFT                                                           16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S6_BMSK                                                       0xf000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S6_SHFT                                                           12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S5_BMSK                                                        0xf00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S5_SHFT                                                            8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S4_BMSK                                                         0xf0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S4_SHFT                                                            4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S3_BMSK                                                          0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S3_SHFT                                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa1c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR1_AGING_BMSK                                                        0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR1_AGING_SHFT                                                                24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR1_TARG_VOLT_NOML1_BMSK                                                0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR1_TARG_VOLT_NOML1_SHFT                                                      18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_AGING_BMSK                                                           0x3fc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_AGING_SHFT                                                                10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_SVS2_BMSK                                             0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_SVS2_SHFT                                                 5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_SVS_BMSK                                               0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_SVS_SHFT                                                  0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa20)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_OFFSET_SVS_BMSK                                         0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_OFFSET_SVS_SHFT                                                 27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_OFFSET_SVSL1_BMSK                                        0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_OFFSET_SVSL1_SHFT                                               22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_OFFSET_NOM_BMSK                                           0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_OFFSET_NOM_SHFT                                                 17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_OFFSET_NOML1_BMSK                                          0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_OFFSET_NOML1_SHFT                                               12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_SVS_BMSK                                                     0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_SVS_SHFT                                                         6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_NOM_BMSK                                                      0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_NOM_SHFT                                                         0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa24)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR2_TARG_VOLT_OFFSET_TURL2_BMSK                                       0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR2_TARG_VOLT_OFFSET_TURL2_SHFT                                               27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR2_TARG_VOLT_OFFSET_TURL3_BMSK                                        0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR2_TARG_VOLT_OFFSET_TURL3_SHFT                                               22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR2_TARG_VOLT_TURL1_BMSK                                                0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR2_TARG_VOLT_TURL1_SHFT                                                      16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR1_TARG_VOLT_SVS3_BMSK                                                   0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR1_TARG_VOLT_SVS3_SHFT                                                       10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR1_TARG_VOLT_OFFSET_SVS3_BMSK                                             0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR1_TARG_VOLT_OFFSET_SVS3_SHFT                                                 5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR1_TARG_VOLT_OFFSET_SVS2_BMSK                                              0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR1_TARG_VOLT_OFFSET_SVS2_SHFT                                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa28)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_SVS_BMSK                                                0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_SVS_SHFT                                                        26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_SVSL2_BMSK                                               0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_SVSL2_SHFT                                                      20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_OFFSET_NOM_BMSK                                            0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_OFFSET_NOM_SHFT                                                 15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_OFFSET_NOML1_BMSK                                           0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_OFFSET_NOML1_SHFT                                               10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_OFFSET_TUR_BMSK                                              0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_OFFSET_TUR_SHFT                                                  5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_OFFSET_TURL1_BMSK                                             0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_OFFSET_TURL1_SHFT                                                0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa2c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_OFFSET_SVS_BMSK                                         0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_OFFSET_SVS_SHFT                                                 27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_OFFSET_SVSL0_BMSK                                        0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_OFFSET_SVSL0_SHFT                                               22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_OFFSET_SVSL1_BMSK                                         0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_OFFSET_SVSL1_SHFT                                               17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_OFFSET_SVSL2_BMSK                                          0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_OFFSET_SVSL2_SHFT                                               12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_SVS3_BMSK                                                    0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_SVS3_SHFT                                                        6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_SVS2_BMSK                                                     0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_SVS2_SHFT                                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa30)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR4_TARG_VOLT_TURL1_BMSK                                              0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR4_TARG_VOLT_TURL1_SHFT                                                      26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR3_TARG_VOLT_SVS_BMSK                                                 0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR3_TARG_VOLT_SVS_SHFT                                                        20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR3_TARG_VOLT_NOM_BMSK                                                   0xfc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR3_TARG_VOLT_NOM_SHFT                                                        14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR3_TARG_VOLT_TUR_BMSK                                                    0x3f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR3_TARG_VOLT_TUR_SHFT                                                         8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_AGING_BMSK                                                              0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_AGING_SHFT                                                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0xa34)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR4_TARG_VOLT_NOM_BMSK                                                0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR4_TARG_VOLT_NOM_SHFT                                                        26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR4_TARG_VOLT_TUR_BMSK                                                 0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR4_TARG_VOLT_TUR_SHFT                                                        20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_LSVSD2_BMSK                                         0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_LSVSD2_SHFT                                              15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SVS3_BMSK                                            0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SVS3_SHFT                                                10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_LSVSD0_BMSK                                           0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_LSVSD0_SHFT                                               5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SVS2_BMSK                                              0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SVS2_SHFT                                                 0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa38)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_OFFSET_NOM_BMSK                                        0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_OFFSET_NOM_SHFT                                                27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_OFFSET_NOML1_BMSK                                       0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_OFFSET_NOML1_SHFT                                              22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_OFFSET_TUR_BMSK                                          0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_OFFSET_TUR_SHFT                                                17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_OFFSET_TURL1_BMSK                                         0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_OFFSET_TURL1_SHFT                                              12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CALIBRATION_651_646_BMSK                                                   0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CALIBRATION_651_646_SHFT                                                       6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_SVS_BMSK                                                     0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_SVS_SHFT                                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa3c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CALIBRATION_703_687_BMSK                                              0xffff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CALIBRATION_703_687_SHFT                                                      15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_OFFSET_SVS2_BMSK                                           0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_OFFSET_SVS2_SHFT                                               10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_OFFSET_SVS_BMSK                                             0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_OFFSET_SVS_SHFT                                                 5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_OFFSET_SVSL1_BMSK                                            0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_OFFSET_SVSL1_SHFT                                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa40)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CALIBRATION_735_716_BMSK                                              0xfffff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CALIBRATION_735_716_SHFT                                                      12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR6_TARG_VOLT_TUR_BMSK                                                    0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR6_TARG_VOLT_TUR_SHFT                                                        6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CALIBRATION_709_704_BMSK                                                    0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CALIBRATION_709_704_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa44)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR7_TARG_VOLT_TUR_BMSK                                               0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR7_TARG_VOLT_TUR_SHFT                                                       26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR6_TARG_VOLT_NOM_BMSK                                                0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR6_TARG_VOLT_NOM_SHFT                                                       20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR7_TARG_VOLT_OFFSET_NOM_BMSK                                           0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR7_TARG_VOLT_OFFSET_NOM_SHFT                                                15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR7_TARG_VOLT_OFFSET_TUR_BMSK                                            0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR7_TARG_VOLT_OFFSET_TUR_SHFT                                                10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CALIBRATION_745_736_BMSK                                                   0x3ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CALIBRATION_745_736_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa48)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CALIBRATION_799_795_BMSK                                              0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CALIBRATION_799_795_SHFT                                                      27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_OFFSET_SVS2_BMSK                                        0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_OFFSET_SVS2_SHFT                                               22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_OFFSET_SVS_BMSK                                          0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_OFFSET_SVS_SHFT                                                17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_OFFSET_SVSL1_BMSK                                         0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_OFFSET_SVSL1_SHFT                                              12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_SVS_BMSK                                                    0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_SVS_SHFT                                                        6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_NOM_BMSK                                                     0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_NOM_SHFT                                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa4c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CALIBRATION_831_814_BMSK                                              0xffffc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CALIBRATION_831_814_SHFT                                                      14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_AGING_BMSK                                                           0x3fc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_AGING_SHFT                                                                6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CALIBRATION_805_800_BMSK                                                    0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CALIBRATION_805_800_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa50)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CALIBRATION_863_832_BMSK                                              0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CALIBRATION_863_832_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa54)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CALIBRATION_895_864_BMSK                                              0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CALIBRATION_895_864_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa58)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR10_TARG_VOLT_NOM_BMSK                                              0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR10_TARG_VOLT_NOM_SHFT                                                      26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR10_TARG_VOLT_TURL1_BMSK                                             0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR10_TARG_VOLT_TURL1_SHFT                                                    20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR10_TARG_VOLT_BOOST_BMSK                                               0xfc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR10_TARG_VOLT_BOOST_SHFT                                                    14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CALIBRATION_909_896_BMSK                                                  0x3fff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CALIBRATION_909_896_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa5c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR10_TARG_VOLT_SVS2_BMSK                                             0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR10_TARG_VOLT_SVS2_SHFT                                                     26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR10_TARG_VOLT_SVS_BMSK                                               0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR10_TARG_VOLT_SVS_SHFT                                                      20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CALIBRATION_947_928_BMSK                                                 0xfffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CALIBRATION_947_928_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa60)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CALIBRATION_991_984_BMSK                                              0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CALIBRATION_991_984_SHFT                                                      24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_AON_TARG_VOLT_BMSK                                                      0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_AON_TARG_VOLT_SHFT                                                            18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CALIBRATION_977_960_BMSK                                                 0x3ffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CALIBRATION_977_960_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa64)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CALIBRATION_1023_BMSK                                                 0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CALIBRATION_1023_SHFT                                                         31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_BOOST_QUOT_MIN_BMSK                                             0x7ff80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_BOOST_QUOT_MIN_SHFT                                                     19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_TARG_VOLT_SVS3_BMSK                                                0x7e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_TARG_VOLT_SVS3_SHFT                                                     13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_QUOT_OFFSET_BMSK                                                    0x1fe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_QUOT_OFFSET_SHFT                                                         5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CALIBRATION_996_992_BMSK                                                    0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CALIBRATION_996_992_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa68)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_AGING_BMSK                                                      0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_AGING_SHFT                                                              24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_NOM_QUOT_MIN_BMSK                                                 0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_NOM_QUOT_MIN_SHFT                                                       12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_TURL1_QUOT_MIN_BMSK                                                  0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_TURL1_QUOT_MIN_SHFT                                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa6c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CALIBRATION_1087_1086_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CALIBRATION_1087_1086_SHFT                                                    30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR11_TARG_VOLT_TURL1_BMSK                                            0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR11_TARG_VOLT_TURL1_SHFT                                                    24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_SVS2_QUOT_MIN_BMSK                                                0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_SVS2_QUOT_MIN_SHFT                                                      12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_SVS_QUOT_MIN_BMSK                                                    0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_SVS_QUOT_MIN_SHFT                                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa70)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CALIBRATION_1119_1118_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CALIBRATION_1119_1118_SHFT                                                    30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_NOM_BMSK                                              0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_NOM_SHFT                                                      24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TURL1_QUOT_MIN_BMSK                                               0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TURL1_QUOT_MIN_SHFT                                                     12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR10_SVS3_QUOT_MIN_BMSK                                                   0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR10_SVS3_QUOT_MIN_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa74)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CALIBRATION_1151_1150_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CALIBRATION_1151_1150_SHFT                                                    30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_NOM_QUOT_MIN_BMSK                                               0x3ffc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_NOM_QUOT_MIN_SHFT                                                       18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TARG_VOLT_SVS3_BMSK                                                0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TARG_VOLT_SVS3_SHFT                                                     12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TARG_VOLT_SVS2_BMSK                                                  0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TARG_VOLT_SVS2_SHFT                                                      6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TARG_VOLT_SVS_BMSK                                                    0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TARG_VOLT_SVS_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa78)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_QUOT_OFFSET_BMSK                                                0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_QUOT_OFFSET_SHFT                                                        24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_SVS2_QUOT_MIN_BMSK                                                0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_SVS2_QUOT_MIN_SHFT                                                      12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_SVS_QUOT_MIN_BMSK                                                    0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_SVS_QUOT_MIN_SHFT                                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa7c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_BOOST_BMSK                                            0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_BOOST_SHFT                                                    26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR11_SVS3_QUOT_MIN_BMSK                                               0x3ffc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR11_SVS3_QUOT_MIN_SHFT                                                      14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_AON_AGING_BMSK                                                            0x3fc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_AON_AGING_SHFT                                                                 6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_BOOSTP_BMSK                                                 0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_BOOSTP_SHFT                                                    0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa80)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_QUOT_OFFSET_BMSK                                                0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_QUOT_OFFSET_SHFT                                                        24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_SVS2_BMSK                                               0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_SVS2_SHFT                                                     18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_SVS_BMSK                                                 0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_SVS_SHFT                                                      12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_NOM_BMSK                                                   0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_NOM_SHFT                                                       6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_TURL3_BMSK                                                  0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_TURL3_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa84)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CALIBRATION_1279_1278_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CALIBRATION_1279_1278_SHFT                                                    30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_BOOST_QUOT_MIN_BMSK                                             0x3ffc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_BOOST_QUOT_MIN_SHFT                                                     18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_BOOSTP_QUOT_MIN_BMSK                                               0x3ffc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_BOOSTP_QUOT_MIN_SHFT                                                     6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_TARG_VOLT_SVS3_BMSK                                                   0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_TARG_VOLT_SVS3_SHFT                                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa88)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CALIBRATION_1311_1304_BMSK                                            0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CALIBRATION_1311_1304_SHFT                                                    24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR12_NOM_QUOT_MIN_BMSK                                                 0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR12_NOM_QUOT_MIN_SHFT                                                       12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR12_TURL3_QUOT_MIN_BMSK                                                  0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR12_TURL3_QUOT_MIN_SHFT                                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa8c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CALIBRATION_1343_1333_BMSK                                            0xffe00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CALIBRATION_1343_1333_SHFT                                                    21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_LPICX_MODE_DISABLE_BMSK                                             0x1c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_LPICX_MODE_DISABLE_SHFT                                                   18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_LPIMX_MODE_DISABLE_BMSK                                              0x38000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_LPIMX_MODE_DISABLE_SHFT                                                   15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CALIBRATION_1326_1324_BMSK                                                0x7000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CALIBRATION_1326_1324_SHFT                                                    12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MX_MODE_DISABLE_BMSK                                                   0xe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MX_MODE_DISABLE_SHFT                                                       9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_GFX_MODE_DISABLE_BMSK                                                  0x1c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_GFX_MODE_DISABLE_SHFT                                                      6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MSS_MODE_DISABLE_BMSK                                                   0x38
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MSS_MODE_DISABLE_SHFT                                                      3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_CX_MODE_DISABLE_BMSK                                                     0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_CX_MODE_DISABLE_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa90)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR13_TARG_VOLT_BOOSTP_BMSK                                           0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR13_TARG_VOLT_BOOSTP_SHFT                                                   26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR12_AGING_BMSK                                                       0x3fc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR12_AGING_SHFT                                                              18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CALIBRATION_1361_1359_BMSK                                               0x38000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CALIBRATION_1361_1359_SHFT                                                    15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_VDDA_MODE_DISABLE_BMSK                                                0x7000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_VDDA_MODE_DISABLE_SHFT                                                    12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_APC1_GOLDP_MODE_DISABLE_BMSK                                           0xe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_APC1_GOLDP_MODE_DISABLE_SHFT                                               9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_APC1_GOLD_MODE_DISABLE_BMSK                                            0x1c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_APC1_GOLD_MODE_DISABLE_SHFT                                                6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_APC0_L3_MODE_DISABLE_BMSK                                               0x38
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_APC0_L3_MODE_DISABLE_SHFT                                                  3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_APC0_SILVER_MODE_DISABLE_BMSK                                            0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_APC0_SILVER_MODE_DISABLE_SHFT                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa94)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CALIBRATION_1407_1403_BMSK                                            0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CALIBRATION_1407_1403_SHFT                                                    27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_APC0_PEAK_THROTTLE_FREQ_BMSK                                           0x6000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_APC0_PEAK_THROTTLE_FREQ_SHFT                                                  25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_APC0_PEAK_THROTTLE_TJ_BMSK                                             0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_APC0_PEAK_THROTTLE_TJ_SHFT                                                    20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR13_QUOT_OFFSET_BMSK                                                   0xff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR13_QUOT_OFFSET_SHFT                                                        12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR12_SVS_QUOT_MIN_BMSK                                                    0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR12_SVS_QUOT_MIN_SHFT                                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa98)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR_LOCAL_RC_BMSK                                                     0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR_LOCAL_RC_SHFT                                                             28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR_GLOBAL_RC_BMSK                                                     0xf000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR_GLOBAL_RC_SHFT                                                            24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ACC_LV_APC1_BMSK                                                        0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ACC_LV_APC1_SHFT                                                              18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ACC_LV_APC0_BMSK                                                         0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ACC_LV_APC0_SHFT                                                              12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ACC_HV_APC1_BMSK                                                           0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ACC_HV_APC1_SHFT                                                               6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ACC_HV_APC0_BMSK                                                            0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ACC_HV_APC0_SHFT                                                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xa9c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_AOSS_K_BMSK                                                           0xffff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_AOSS_K_SHFT                                                                   16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_CALIBRATION_1455_BMSK                                                     0x8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_CALIBRATION_1455_SHFT                                                         15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_GFX_FUSE_RESERVED_2_0_BMSK                                                0x7000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_GFX_FUSE_RESERVED_2_0_SHFT                                                    12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_CPR12_SVS2_QUOT_MIN_BMSK                                                   0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_CPR12_SVS2_QUOT_MIN_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xaa0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CALIBRATION_1503_1500_BMSK                                            0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CALIBRATION_1503_1500_SHFT                                                    28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_TDOPCODE_BMSK                                                     0xf800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_TDOPCODE_SHFT                                                            23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_RDOPCODE_BMSK                                                      0x7c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_RDOPCODE_SHFT                                                            18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_N1_BMSK                                                             0x3ffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_N1_SHFT                                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xaa4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_TSENS1_BASE1_BMSK                                                     0xffc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_TSENS1_BASE1_SHFT                                                             22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_CALIBRATION_1525_1522_BMSK                                              0x3c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_CALIBRATION_1525_1522_SHFT                                                    18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_AOSS_P1_BMSK                                                             0x3ffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_AOSS_P1_SHFT                                                                   0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xaa8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_CALIBRATION_1567_1566_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_CALIBRATION_1567_1566_SHFT                                                    30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS1_BASE0_BMSK                                                     0x3ff00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS1_BASE0_SHFT                                                             20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS0_BASE1_BMSK                                                        0xffc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS0_BASE1_SHFT                                                             10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS0_BASE0_BMSK                                                          0x3ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS0_BASE0_SHFT                                                              0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xaac)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_CALIBRATION_1599_1596_BMSK                                            0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_CALIBRATION_1599_1596_SHFT                                                    28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS3_OFFSET_BMSK                                                     0xf800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS3_OFFSET_SHFT                                                            23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS2_OFFSET_BMSK                                                      0x7c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS2_OFFSET_SHFT                                                            18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS1_OFFSET_BMSK                                                       0x3e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS1_OFFSET_SHFT                                                            13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS0_OFFSET_BMSK                                                        0x1f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS0_OFFSET_SHFT                                                             8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_CALIBRATION_1575_1574_BMSK                                                  0xc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_CALIBRATION_1575_1574_SHFT                                                     6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_CPR13_TARG_VOLT_BOOST_BMSK                                                  0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_CPR13_TARG_VOLT_BOOST_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xab0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_CALIBRATION_1631_BMSK                                                 0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_CALIBRATION_1631_SHFT                                                         31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS10_OFFSET_BMSK                                                   0x7c000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS10_OFFSET_SHFT                                                           26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS9_OFFSET_BMSK                                                     0x3e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS9_OFFSET_SHFT                                                            21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS8_OFFSET_BMSK                                                      0x1f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS8_OFFSET_SHFT                                                            16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS7_OFFSET_BMSK                                                        0xf800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS7_OFFSET_SHFT                                                            11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS6_OFFSET_BMSK                                                         0x7c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS6_OFFSET_SHFT                                                             6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS5_OFFSET_BMSK                                                          0x3e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS5_OFFSET_SHFT                                                             1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_CALIBRATION_1600_BMSK                                                        0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_CALIBRATION_1600_SHFT                                                          0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xab4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_CALIBRATION_1663_1661_BMSK                                            0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_CALIBRATION_1663_1661_SHFT                                                    29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS16_OFFSET_BMSK                                                   0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS16_OFFSET_SHFT                                                           24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS15_OFFSET_BMSK                                                     0xf80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS15_OFFSET_SHFT                                                           19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS14_OFFSET_BMSK                                                      0x7c000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS14_OFFSET_SHFT                                                           14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS13_OFFSET_BMSK                                                       0x3e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS13_OFFSET_SHFT                                                            9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS12_OFFSET_BMSK                                                        0x1f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS12_OFFSET_SHFT                                                            4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_CALIBRATION_1635_1632_BMSK                                                   0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_CALIBRATION_1635_1632_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xab8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS23_OFFSET_BMSK                                                   0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS23_OFFSET_SHFT                                                           27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS22_OFFSET_BMSK                                                    0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS22_OFFSET_SHFT                                                           22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS21_OFFSET_BMSK                                                     0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS21_OFFSET_SHFT                                                           17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS20_OFFSET_BMSK                                                      0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS20_OFFSET_SHFT                                                           12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS19_OFFSET_BMSK                                                        0xf80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS19_OFFSET_SHFT                                                            7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS18_OFFSET_BMSK                                                         0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS18_OFFSET_SHFT                                                            2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_CALIBRATION_1665_1664_BMSK                                                   0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_CALIBRATION_1665_1664_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xabc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_CALIBRATION_1727_1716_BMSK                                            0xfff00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_CALIBRATION_1727_1716_SHFT                                                    20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS27_OFFSET_BMSK                                                      0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS27_OFFSET_SHFT                                                           15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS26_OFFSET_BMSK                                                       0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS26_OFFSET_SHFT                                                           10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS25_OFFSET_BMSK                                                        0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS25_OFFSET_SHFT                                                            5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS24_OFFSET_BMSK                                                         0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS24_OFFSET_SHFT                                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xac0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_CALIBRATION_1759_BMSK                                                 0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_CALIBRATION_1759_SHFT                                                         31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS11_OFFSET_BMSK                                                   0x7c000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS11_OFFSET_SHFT                                                           26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_CALIBRATION_1750_1736_BMSK                                             0x3fff800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_CALIBRATION_1750_1736_SHFT                                                    11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS_CAL_SEL_BMSK                                                         0x700
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS_CAL_SEL_SHFT                                                             8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_CALIBRATION_1735_1728_BMSK                                                  0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_CALIBRATION_1735_1728_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xac4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_CALIBRATION_1791_1787_BMSK                                            0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_CALIBRATION_1791_1787_SHFT                                                    27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_CPR13_BOOSTP_QUOT_MIN_BMSK                                             0x7ff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_CPR13_BOOSTP_QUOT_MIN_SHFT                                                    15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS4_OFFSET_BMSK                                                        0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS4_OFFSET_SHFT                                                            10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_CALIBRATION_1755_1751_BMSK                                                 0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_CALIBRATION_1755_1751_SHFT                                                     5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS17_OFFSET_BMSK                                                         0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS17_OFFSET_SHFT                                                            0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xac8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CALIBRATION_1823_1822_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CALIBRATION_1823_1822_SHFT                                                    30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_SVS3_BMSK                                             0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_SVS3_SHFT                                                     24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_SVS2_BMSK                                               0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_SVS2_SHFT                                                     18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_SVS_BMSK                                                 0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_SVS_SHFT                                                      12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_NOM_BMSK                                                   0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_NOM_SHFT                                                       6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_TURL3_BMSK                                                  0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_TURL3_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xacc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CALIBRATION_1855_1848_BMSK                                            0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CALIBRATION_1855_1848_SHFT                                                    24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CPR13_TURL3_QUOT_MIN_BMSK                                               0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CPR13_TURL3_QUOT_MIN_SHFT                                                     12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CPR13_BOOST_QUOT_MIN_BMSK                                                  0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CPR13_BOOST_QUOT_MIN_SHFT                                                      0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xad0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_CALIBRATION_1887_1856_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_CALIBRATION_1887_1856_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xad4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_CALIBRATION_1919_1888_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_CALIBRATION_1919_1888_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xad8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_CALIBRATION_1951_1934_BMSK                                            0xffffc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_CALIBRATION_1951_1934_SHFT                                                    14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_CPR13_NOM_QUOT_MIN_BMSK                                                   0x3ffc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_CPR13_NOM_QUOT_MIN_SHFT                                                        2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_CALIBRATION_1921_1920_BMSK                                                   0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_CALIBRATION_1921_1920_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xadc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_CALIBRATION_1983_1952_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_CALIBRATION_1983_1952_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xae0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CALIBRATION_2015_2014_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CALIBRATION_2015_2014_SHFT                                                    30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_VOLTAGE_DELTA_BMSK                                           0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_VOLTAGE_DELTA_SHFT                                                   25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_VOLTAGE_V_HF_BMSK                                             0x1ff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_VOLTAGE_V_HF_SHFT                                                    15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_CURRENT_DELTA_BMSK                                               0x7ff8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_CURRENT_DELTA_SHFT                                                    3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CALIBRATION_1986_1984_BMSK                                                   0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CALIBRATION_1986_1984_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xae4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CALIBRATION_2047_2040_BMSK                                            0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CALIBRATION_2047_2040_SHFT                                                    24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CPR13_SVS2_QUOT_MIN_BMSK                                                0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CPR13_SVS2_QUOT_MIN_SHFT                                                      12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CPR13_SVS_QUOT_MIN_BMSK                                                    0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CPR13_SVS_QUOT_MIN_SHFT                                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xae8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_CALIBRATION_2079_2048_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_CALIBRATION_2079_2048_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xaec)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CALIBRATION_2111_2104_BMSK                                            0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CALIBRATION_2111_2104_SHFT                                                    24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CPR13_SVS3_QUOT_MIN_BMSK                                                0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CPR13_SVS3_QUOT_MIN_SHFT                                                      12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CALIBRATION_2091_2080_BMSK                                                 0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CALIBRATION_2091_2080_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xaf0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CALIBRATION_2143_2141_BMSK                                            0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CALIBRATION_2143_2141_SHFT                                                    29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ACD_NSP_DVM_TURL1_BMSK                                                0x1fffffe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ACD_NSP_DVM_TURL1_SHFT                                                         5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CALIBRATION_2116_2112_BMSK                                                  0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CALIBRATION_2116_2112_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xaf4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_GFX_CURRENT_REVISION_BMSK                                             0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_GFX_CURRENT_REVISION_SHFT                                                     30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_CALIBRATION_2173_2157_BMSK                                            0x3fffe000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_CALIBRATION_2173_2157_SHFT                                                    13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_GFX_PEAK_CURRENT_I_LF_BMSK                                                0x1fff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_GFX_PEAK_CURRENT_I_LF_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xaf8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CALIBRATION_2207_2194_BMSK                                            0xfffc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CALIBRATION_2207_2194_SHFT                                                    18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_GFX_FUSE_RESERVED_16_0_BMSK                                              0x3ffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_GFX_FUSE_RESERVED_16_0_SHFT                                                    0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xafc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CALIBRATION_2239_2208_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CALIBRATION_2239_2208_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb00)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_CALIBRATION_2271_2264_BMSK                                            0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_CALIBRATION_2271_2264_SHFT                                                    24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ACD_NSP_DVM_TUR_BMSK                                                    0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ACD_NSP_DVM_TUR_SHFT                                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb04)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CALIBRATION_2303_2272_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CALIBRATION_2303_2272_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb08)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_CALIBRATION_2335_2316_BMSK                                            0xfffff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_CALIBRATION_2335_2316_SHFT                                                    12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_CPR12_SVS3_QUOT_MIN_BMSK                                                   0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_CPR12_SVS3_QUOT_MIN_SHFT                                                       0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb0c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CALIBRATION_2367_2336_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CALIBRATION_2367_2336_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb10)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CALIBRATION_2399_2368_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CALIBRATION_2399_2368_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb14)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS98_AUP1_BMSK                                      0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS98_AUP1_SHFT                                              31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AG2_BMSK                                       0x40000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AG2_SHFT                                               30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AG1_BMSK                                       0x20000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AG1_SHFT                                               29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU_BMSK                                        0x10000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU_SHFT                                                28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU2_BMSK                                        0x8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU2_SHFT                                               27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU1_BMSK                                        0x4000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU1_SHFT                                               26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP_BMSK                                        0x2000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP_SHFT                                               25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP2_BMSK                                       0x1000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP2_SHFT                                              24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP1_BMSK                                        0x800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP1_SHFT                                              23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CALIBRATION_2422_2400_BMSK                                              0x7fffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CALIBRATION_2422_2400_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb18)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CALIBRATION_2463_2441_BMSK                                            0xfffffe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CALIBRATION_2463_2441_SHFT                                                     9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_GFX_CDYN_REVISION_BMSK                                                     0x180
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_GFX_CDYN_REVISION_SHFT                                                         7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP8_BMSK                                            0x40
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP8_SHFT                                               6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP7_BMSK                                            0x20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP7_SHFT                                               5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP6_BMSK                                            0x10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP6_SHFT                                               4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP5_BMSK                                             0x8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP5_SHFT                                               3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP4_BMSK                                             0x4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP4_SHFT                                               2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP3_BMSK                                             0x2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP3_SHFT                                               1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP2_BMSK                                             0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP2_SHFT                                               0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb1c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_CALIBRATION_2495_2488_BMSK                                            0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_CALIBRATION_2495_2488_SHFT                                                    24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ACD_NSP_DVM_ENABLE_BMSK                                                 0xff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ACD_NSP_DVM_ENABLE_SHFT                                                       15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_CALIBRATION_2478_2469_BMSK                                                0x7fe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_CALIBRATION_2478_2469_SHFT                                                     5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ACD_NSP_REVISION_BIT_BMSK                                                   0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ACD_NSP_REVISION_BIT_SHFT                                                      3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_CALIBRATION_2466_2464_BMSK                                                   0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_CALIBRATION_2466_2464_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb20)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_DDRSS_CH2CA_PNTUNE_HT_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_DDRSS_CH2CA_PNTUNE_HT_SHFT                                                    30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_DDRSS_CH1DQ1_PNTUNE_HT_BMSK                                           0x30000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_DDRSS_CH1DQ1_PNTUNE_HT_SHFT                                                   28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_DDRSS_CH1DQ0_PNTUNE_HT_BMSK                                            0xc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_DDRSS_CH1DQ0_PNTUNE_HT_SHFT                                                   26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_DDRSS_CH1CA_PNTUNE_HT_BMSK                                             0x3000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_DDRSS_CH1CA_PNTUNE_HT_SHFT                                                    24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ACD_NSP_DVM_LSVSD1_BMSK                                                 0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ACD_NSP_DVM_LSVSD1_SHFT                                                        0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb24)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_DDRSS_CH0DQ1_PNTUNE_HT_BMSK                                           0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_DDRSS_CH0DQ1_PNTUNE_HT_SHFT                                                   30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_DDRSS_CH0DQ0_PNTUNE_HT_BMSK                                           0x30000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_DDRSS_CH0DQ0_PNTUNE_HT_SHFT                                                   28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_DDRSS_CH0CA_PNTUNE_HT_BMSK                                             0xc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_DDRSS_CH0CA_PNTUNE_HT_SHFT                                                    26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_DDRSS_CH3DQ1_PNTUNE_RT_BMSK                                            0x3000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_DDRSS_CH3DQ1_PNTUNE_RT_SHFT                                                   24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ACD_NSP_DVM_LSVS_BMSK                                                   0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ACD_NSP_DVM_LSVS_SHFT                                                          0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb28)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_DDRSS_CH3DQ0_PNTUNE_RT_BMSK                                           0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_DDRSS_CH3DQ0_PNTUNE_RT_SHFT                                                   30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_DDRSS_CH3CA_PNTUNE_RT_BMSK                                            0x30000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_DDRSS_CH3CA_PNTUNE_RT_SHFT                                                    28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_DDRSS_CH2DQ1_PNTUNE_RT_BMSK                                            0xc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_DDRSS_CH2DQ1_PNTUNE_RT_SHFT                                                   26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_DDRSS_CH2DQ0_PNTUNE_RT_BMSK                                            0x3000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_DDRSS_CH2DQ0_PNTUNE_RT_SHFT                                                   24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ACD_NSP_DVM_SVS_BMSK                                                    0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ACD_NSP_DVM_SVS_SHFT                                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb2c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_CALIBRATION_2623_2616_BMSK                                            0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_CALIBRATION_2623_2616_SHFT                                                    24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ACD_NSP_DVM_SVSL1_BMSK                                                  0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ACD_NSP_DVM_SVSL1_SHFT                                                         0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb30)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_DDRSS_CH2CA_PNTUNE_RT_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_DDRSS_CH2CA_PNTUNE_RT_SHFT                                                    30
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_DDRSS_CH1DQ1_PNTUNE_RT_BMSK                                           0x30000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_DDRSS_CH1DQ1_PNTUNE_RT_SHFT                                                   28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_DDRSS_CH1DQ0_PNTUNE_RT_BMSK                                            0xc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_DDRSS_CH1DQ0_PNTUNE_RT_SHFT                                                   26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_DDRSS_CH1CA_PNTUNE_RT_BMSK                                             0x3000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_DDRSS_CH1CA_PNTUNE_RT_SHFT                                                    24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ACD_NSP_DVM_NOM_BMSK                                                    0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ACD_NSP_DVM_NOM_SHFT                                                           0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb34)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_CALIBRATION_2687_BMSK                                                 0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_CALIBRATION_2687_SHFT                                                         31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_DDRSS_EW_FUSE_1_BMSK                                                  0x7f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_DDRSS_EW_FUSE_1_SHFT                                                          24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ACD_NSP_DVM_NOML1_BMSK                                                  0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ACD_NSP_DVM_NOML1_SHFT                                                         0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb38)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_CALIBRATION_2719_BMSK                                                 0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_CALIBRATION_2719_SHFT                                                         31
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0DQ1_PNTUNE_RT_BMSK                                           0x60000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0DQ1_PNTUNE_RT_SHFT                                                   29
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0DQ0_PNTUNE_RT_BMSK                                           0x18000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0DQ0_PNTUNE_RT_SHFT                                                   27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0CA_PNTUNE_RT_BMSK                                             0x6000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0CA_PNTUNE_RT_SHFT                                                    25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_TP_REV_CTRL_BMSK                                                 0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_TP_REV_CTRL_SHFT                                                        20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_EH_FUSE_2_BMSK                                                     0xfe000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_EH_FUSE_2_SHFT                                                          13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_EH_FUSE_1_BMSK                                                      0x1fc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_EH_FUSE_1_SHFT                                                           6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_CALIBRATION_2693_2688_BMSK                                                  0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_CALIBRATION_2693_2688_SHFT                                                     0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0xb3c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_IN                    \
                in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_INM(m)            \
                in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_CALBIST_RESERVED_BMSK                                                 0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_CALBIST_RESERVED_SHFT                                                         28
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_VPID_FT_BMSK                                                           0x8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_VPID_FT_SHFT                                                                  27
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_VPID_WS_BMSK                                                           0x4000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_VPID_WS_SHFT                                                                  26
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_FT_BMSK                                                            0x2000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_FT_SHFT                                                                   25
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_WS_BMSK                                                            0x1000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_WS_SHFT                                                                   24
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_VSENS_FT_BMSK                                                           0x800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_VSENS_FT_SHFT                                                                 23
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_VSENS_WS_BMSK                                                           0x400000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_VSENS_WS_SHFT                                                                 22
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DACC_FT_BMSK                                                            0x200000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DACC_FT_SHFT                                                                  21
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DACC_WS_BMSK                                                            0x100000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DACC_WS_SHFT                                                                  20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_USB_FT_BMSK                                                              0x80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_USB_FT_SHFT                                                                   19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_USB_WS_BMSK                                                              0x40000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_USB_WS_SHFT                                                                   18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_REFGEN_FT_BMSK                                                           0x20000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_REFGEN_FT_SHFT                                                                17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_REFGEN_WS_BMSK                                                           0x10000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_REFGEN_WS_SHFT                                                                16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_CPR_FT_BMSK                                                               0x8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_CPR_FT_SHFT                                                                   15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_CPR_WS_BMSK                                                               0x4000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_CPR_WS_SHFT                                                                   14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_LRET_FT_BMSK                                                              0x2000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_LRET_FT_SHFT                                                                  13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_LRET_WS_BMSK                                                              0x1000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_LRET_WS_SHFT                                                                  12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_MRET_FT_BMSK                                                               0x800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_MRET_FT_SHFT                                                                  11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_MRET_WS_BMSK                                                               0x400
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_MRET_WS_SHFT                                                                  10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_AOSS_FT_BMSK                                                               0x200
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_AOSS_FT_SHFT                                                                   9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_AOSS_WS_BMSK                                                               0x100
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_AOSS_WS_SHFT                                                                   8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_IDDQ_FT_BMSK                                                                0x80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_IDDQ_FT_SHFT                                                                   7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_IDDQ_WS_BMSK                                                                0x40
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_IDDQ_WS_SHFT                                                                   6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DVS_FT_BMSK                                                                 0x20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DVS_FT_SHFT                                                                    5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DVS_WS_BMSK                                                                 0x10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DVS_WS_SHFT                                                                    4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_TSENS_FT_BMSK                                                                0x8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_TSENS_FT_SHFT                                                                  3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_TSENS_WS_BMSK                                                                0x4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_TSENS_WS_SHFT                                                                  2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_QFPROM_FT_BMSK                                                               0x2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_QFPROM_FT_SHFT                                                                 1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_QFPROM_WS_BMSK                                                               0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_QFPROM_WS_SHFT                                                                 0


#endif /* HALHWIOTSENSFUSES_H */
