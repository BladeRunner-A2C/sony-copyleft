#ifndef __CPR_FUSES_HWIO_H__
#define __CPR_FUSES_HWIO_H__
/*
===========================================================================
*/
/**
  @file cpr_fuses_hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    Palawan [ palawan_v1.0_p3q3r56_rtl_partition_MTO]
 
  This file contains HWIO register definitions for the following modules:
    FUSE_CONTROLLER_SW_RANGE4
    QFPROM_CORR

  'Include' filters applied: CALIBRATION[FUSE_CONTROLLER_SW_RANGE4] QFPROM_CORR_CALIBRATION[QFPROM_CORR] QFPROM_CORR_PTE[QFPROM_CORR] 

  Generation parameters: 
  { 'filename': 'cpr_fuses_hwio.h',
    'generator': 'ciomacros',
    'header': '#include "msmhwiobase.h"\n'
              '#define TME_FUSECONTROLLER_BASE (TMESS_BASE            + '
              '0x021c0000)\n',
    'module-filter-include': { 'FUSE_CONTROLLER_SW_RANGE4': ['CALIBRATION'],
                               'QFPROM_CORR': [ 'QFPROM_CORR_CALIBRATION',
                                                'QFPROM_CORR_PTE']},
    'modules': ['FUSE_CONTROLLER_SW_RANGE4', 'QFPROM_CORR'],
    'output-fvals': True,
    'output-offsets': True}
*/
/*
  ===========================================================================

  Copyright (c) 2023 Qualcomm Technologies, Inc.
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
#define TME_FUSECONTROLLER_BASE (TMESS_BASE            + 0x021c0000)


/*----------------------------------------------------------------------------
 * MODULE: QFPROM_CORR
 *--------------------------------------------------------------------------*/

#define QFPROM_CORR_REG_BASE                                                                                         (TMESS_BASE      + 0x021c2000)
#define QFPROM_CORR_REG_BASE_SIZE                                                                                    0x2000
#define QFPROM_CORR_REG_BASE_USED                                                                                    0x137c
#define QFPROM_CORR_REG_BASE_OFFS                                                                                    0x021c2000

#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0x00000098)
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_OFFS                                                                           (QFPROM_CORR_REG_BASE_OFFS + 0x00000098)
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_PTE_ROW0_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_PTE_DATA_31_BMSK                                                               0x80000000
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_PTE_DATA_31_SHFT                                                                     0x1f
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_SPEED_BIN_BMSK                                                                 0x70000000
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_SPEED_BIN_SHFT                                                                       0x1c
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_FEATURE_ID_BMSK                                                                 0xff00000
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_FEATURE_ID_SHFT                                                                      0x14
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_JTAG_ID_BMSK                                                                      0xfffff
#define HWIO_QFPROM_CORR_PTE_ROW0_LSB_JTAG_ID_SHFT                                                                          0x0

#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0x0000009c)
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_OFFS                                                                           (QFPROM_CORR_REG_BASE_OFFS + 0x0000009c)
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_PTE_ROW0_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_BIN_V_IDENTIFIER_BMSK                                                          0xc0000000
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_BIN_V_IDENTIFIER_SHFT                                                                0x1e
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_MINOR_REV_BMSK                                                                 0x30000000
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_MINOR_REV_SHFT                                                                       0x1c
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_LOGIC_RETENTION_BMSK                                                            0xe000000
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_LOGIC_RETENTION_SHFT                                                                 0x19
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_REVISION_CONTROL_BMSK                                                      0x1c00000
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_REVISION_CONTROL_SHFT                                                           0x16
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_MXA_ACTIVE_BMSK                                                             0x3ff000
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_MXA_ACTIVE_SHFT                                                                  0xc
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_CX_ACTIVE_BMSK                                                                 0xffc
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_IDDQ_CX_ACTIVE_SHFT                                                                   0x2
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_INT_SECURE_MCN_IDENTIFIER_BMSK                                                        0x2
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_INT_SECURE_MCN_IDENTIFIER_SHFT                                                        0x1
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_PTE_MCN_IDENTIFIER_BMSK                                                               0x1
#define HWIO_QFPROM_CORR_PTE_ROW0_MSB_PTE_MCN_IDENTIFIER_SHFT                                                               0x0

#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0x000000a0)
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_OFFS                                                                           (QFPROM_CORR_REG_BASE_OFFS + 0x000000a0)
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_PTE_ROW1_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_PTE_DATA_95_93_BMSK                                                            0xe0000000
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_PTE_DATA_95_93_SHFT                                                                  0x1d
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IDDQ_MXC_ACTIVE_BMSK                                                           0x1ff80000
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IDDQ_MXC_ACTIVE_SHFT                                                                 0x13
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IDDQ_MULTIPLIER_BMSK                                                              0x70000
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IDDQ_MULTIPLIER_SHFT                                                                 0x10
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_DVS_PREVIOUSLY_RUN_BMSK                                                            0x8000
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_DVS_PREVIOUSLY_RUN_SHFT                                                               0xf
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_TSENS_REV_CTRL_BMSK                                                                0x4000
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_TSENS_REV_CTRL_SHFT                                                                   0xe
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IDDQ_LPICX_ACTIVE_BMSK                                                             0x3fc0
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_IDDQ_LPICX_ACTIVE_SHFT                                                                0x6
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_PTE_DATA_69_BMSK                                                                     0x20
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_PTE_DATA_69_SHFT                                                                      0x5
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_RETENTION_FAIL_BMSK                                                                  0x10
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_RETENTION_FAIL_SHFT                                                                   0x4
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_HV_ONLY_BMSK                                                                          0x8
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_HV_ONLY_SHFT                                                                          0x3
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_WAFER_ZONE_BMSK                                                                       0x7
#define HWIO_QFPROM_CORR_PTE_ROW1_LSB_WAFER_ZONE_SHFT                                                                       0x0

#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0x000000a4)
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_OFFS                                                                           (QFPROM_CORR_REG_BASE_OFFS + 0x000000a4)
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_PTE_ROW1_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IDDQ_NSP_ACTIVE_BMSK                                                           0xffc00000
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IDDQ_NSP_ACTIVE_SHFT                                                                 0x16
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IDDQ_APC0_ACTIVE_BMSK                                                            0x3ff000
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_IDDQ_APC0_ACTIVE_SHFT                                                                 0xc
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_RBSC_AEBI_RET_BMSK                                                                  0xff0
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_RBSC_AEBI_RET_SHFT                                                                    0x4
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_DOU_BINNING_BMSK                                                                      0xf
#define HWIO_QFPROM_CORR_PTE_ROW1_MSB_DOU_BINNING_SHFT                                                                      0x0

#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0x000000a8)
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_OFFS                                                                           (QFPROM_CORR_REG_BASE_OFFS + 0x000000a8)
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_PTE_ROW2_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_PTE_DATA_159_157_BMSK                                                          0xe0000000
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_PTE_DATA_159_157_SHFT                                                                0x1d
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_IDDQ_MODEM_ACTIVE_BMSK                                                         0x1ff80000
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_IDDQ_MODEM_ACTIVE_SHFT                                                               0x13
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_IDDQ_LPIMX_ACTIVE_BMSK                                                            0x7f800
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_IDDQ_LPIMX_ACTIVE_SHFT                                                                0xb
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_IDDQ_NSP_OFF_BMSK                                                                   0x7fe
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_IDDQ_NSP_OFF_SHFT                                                                     0x1
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_PTE_DATA_128_BMSK                                                                     0x1
#define HWIO_QFPROM_CORR_PTE_ROW2_LSB_PTE_DATA_128_SHFT                                                                     0x0

#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0x000000ac)
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_OFFS                                                                           (QFPROM_CORR_REG_BASE_OFFS + 0x000000ac)
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_PTE_ROW2_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_PTE_DATA_191_189_BMSK                                                          0xe0000000
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_PTE_DATA_191_189_SHFT                                                                0x1d
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_IDDQ_CX_OFF_BMSK                                                               0x1fe00000
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_IDDQ_CX_OFF_SHFT                                                                     0x15
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_IDDQ_AEBI_ACTIVE_BMSK                                                            0x1fe000
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_IDDQ_AEBI_ACTIVE_SHFT                                                                 0xd
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_IDDQ_GFX_ACTIVE_BMSK                                                               0x1ffe
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_IDDQ_GFX_ACTIVE_SHFT                                                                  0x1
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_PTE_DATA_160_BMSK                                                                     0x1
#define HWIO_QFPROM_CORR_PTE_ROW2_MSB_PTE_DATA_160_SHFT                                                                     0x0

#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0x000000b0)
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_OFFS                                                                           (QFPROM_CORR_REG_BASE_OFFS + 0x000000b0)
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_PTE_ROW3_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW3_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_PTE_DATA_223_222_BMSK                                                          0xc0000000
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_PTE_DATA_223_222_SHFT                                                                0x1e
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_NON_COMMERCIAL_IDENTIFIER_BMSK                                                 0x20000000
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_NON_COMMERCIAL_IDENTIFIER_SHFT                                                       0x1d
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_WAFER_ID_BMSK                                                                  0x1f000000
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_WAFER_ID_SHFT                                                                        0x18
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_DIE_X_BMSK                                                                       0xff0000
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_DIE_X_SHFT                                                                           0x10
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_DIE_Y_BMSK                                                                         0xff00
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_DIE_Y_SHFT                                                                            0x8
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_MEM_RETENTION_BMSK                                                                   0xe0
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_MEM_RETENTION_SHFT                                                                    0x5
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_PTE_DATA_196_192_BMSK                                                                0x1f
#define HWIO_QFPROM_CORR_PTE_ROW3_LSB_PTE_DATA_196_192_SHFT                                                                 0x0

#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0x000000b4)
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_OFFS                                                                           (QFPROM_CORR_REG_BASE_OFFS + 0x000000b4)
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_PTE_ROW3_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW3_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_PTE_DATA_255_BMSK                                                              0x80000000
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_PTE_DATA_255_SHFT                                                                    0x1f
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_RBSC_MXC_NOM_BMSK                                                              0x7e000000
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_RBSC_MXC_NOM_SHFT                                                                    0x19
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_IDDQ_APC1_ACTIVE_BMSK                                                           0x1ffe000
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_IDDQ_APC1_ACTIVE_SHFT                                                                 0xd
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_BONE_PILE_BMSK                                                                     0x1800
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_BONE_PILE_SHFT                                                                        0xb
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_DVS_REV_BMSK                                                                        0x700
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_DVS_REV_SHFT                                                                          0x8
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_RBSC_MXA_RET_BMSK                                                                    0xff
#define HWIO_QFPROM_CORR_PTE_ROW3_MSB_RBSC_MXA_RET_SHFT                                                                     0x0

#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0x000000b8)
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_OFFS                                                                           (QFPROM_CORR_REG_BASE_OFFS + 0x000000b8)
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_PTE_ROW4_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_RBSC_LPIMX_NOM_BMSK                                                            0xfc000000
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_RBSC_LPIMX_NOM_SHFT                                                                  0x1a
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_RBSC_NSP_NOM_BMSK                                                               0x3ff0000
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_RBSC_NSP_NOM_SHFT                                                                    0x10
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_IDDQ_MXC_OFF_BMSK                                                                  0xff00
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_IDDQ_MXC_OFF_SHFT                                                                     0x8
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_IDDQ_MXA_OFF_BMSK                                                                    0xff
#define HWIO_QFPROM_CORR_PTE_ROW4_LSB_IDDQ_MXA_OFF_SHFT                                                                     0x0

#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0x000000bc)
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_OFFS                                                                           (QFPROM_CORR_REG_BASE_OFFS + 0x000000bc)
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_PTE_ROW4_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_RBSC_CX_NOM_BMSK                                                               0xff000000
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_RBSC_CX_NOM_SHFT                                                                     0x18
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_IDDQ_MODEM_OFF_BMSK                                                              0xff0000
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_IDDQ_MODEM_OFF_SHFT                                                                  0x10
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_IDDQ_APC1_OFF_BMSK                                                                 0xff00
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_IDDQ_APC1_OFF_SHFT                                                                    0x8
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_IDDQ_APC0_OFF_BMSK                                                                   0xff
#define HWIO_QFPROM_CORR_PTE_ROW4_MSB_IDDQ_APC0_OFF_SHFT                                                                    0x0

#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0x000000c0)
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_OFFS                                                                           (QFPROM_CORR_REG_BASE_OFFS + 0x000000c0)
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_PTE_ROW5_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW5_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_IDDQ_AEBI_OFF_BMSK                                                             0xfc000000
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_IDDQ_AEBI_OFF_SHFT                                                                   0x1a
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_IDDQ_LPIMX_OFF_BMSK                                                             0x3f00000
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_IDDQ_LPIMX_OFF_SHFT                                                                  0x14
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_IDDQ_MM_OFF_BMSK                                                                  0xff000
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_IDDQ_MM_OFF_SHFT                                                                      0xc
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_IDDQ_GFX_OFF_BMSK                                                                   0xfff
#define HWIO_QFPROM_CORR_PTE_ROW5_LSB_IDDQ_GFX_OFF_SHFT                                                                     0x0

#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0x000000c4)
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_OFFS                                                                           (QFPROM_CORR_REG_BASE_OFFS + 0x000000c4)
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_PTE_ROW5_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW5_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_RBSC_LPICX_NOM_BMSK                                                            0xfc000000
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_RBSC_LPICX_NOM_SHFT                                                                  0x1a
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_RBSC_GFX_NOM_BMSK                                                               0x3ffc000
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_RBSC_GFX_NOM_SHFT                                                                     0xe
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_RBSC_APC1_NOM_BMSK                                                                 0x3f80
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_RBSC_APC1_NOM_SHFT                                                                    0x7
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_IDDQ_LPICX_OFF_BMSK                                                                  0x7f
#define HWIO_QFPROM_CORR_PTE_ROW5_MSB_IDDQ_LPICX_OFF_SHFT                                                                   0x0

#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0x000000c8)
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_OFFS                                                                           (QFPROM_CORR_REG_BASE_OFFS + 0x000000c8)
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_PTE_ROW6_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW6_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_RBSC_MM_NOM_BMSK                                                               0xff000000
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_RBSC_MM_NOM_SHFT                                                                     0x18
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_RBSC_MODEM_NOM_BMSK                                                              0xff0000
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_RBSC_MODEM_NOM_SHFT                                                                  0x10
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_RBSC_APC0_NOM_BMSK                                                                 0xff00
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_RBSC_APC0_NOM_SHFT                                                                    0x8
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_RBSC_MXA_NOM_BMSK                                                                    0xff
#define HWIO_QFPROM_CORR_PTE_ROW6_LSB_RBSC_MXA_NOM_SHFT                                                                     0x0

#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0x000000cc)
#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_OFFS                                                                           (QFPROM_CORR_REG_BASE_OFFS + 0x000000cc)
#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_PTE_ROW6_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW6_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_RBSC_LPICX_RET_BMSK                                                            0xff000000
#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_RBSC_LPICX_RET_SHFT                                                                  0x18
#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_IDDQ_APC1_ACTIVEGOLD_BMSK                                                        0xfff000
#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_IDDQ_APC1_ACTIVEGOLD_SHFT                                                             0xc
#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_IDDQ_MM_ACTIVE_BMSK                                                                 0xfff
#define HWIO_QFPROM_CORR_PTE_ROW6_MSB_IDDQ_MM_ACTIVE_SHFT                                                                   0x0

#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0x000000d0)
#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_OFFS                                                                           (QFPROM_CORR_REG_BASE_OFFS + 0x000000d0)
#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_PTE_ROW7_LSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW7_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_RBSC_LPIMX_RET_BMSK                                                            0xff000000
#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_RBSC_LPIMX_RET_SHFT                                                                  0x18
#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_RBSC_TOTAL_PWR_BMSK                                                              0xfff000
#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_RBSC_TOTAL_PWR_SHFT                                                                   0xc
#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_IDDQ_APC1_ACTIVEGOLDP_BMSK                                                          0xfff
#define HWIO_QFPROM_CORR_PTE_ROW7_LSB_IDDQ_APC1_ACTIVEGOLDP_SHFT                                                            0x0

#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_ADDR                                                                           (QFPROM_CORR_REG_BASE      + 0x000000d4)
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_OFFS                                                                           (QFPROM_CORR_REG_BASE_OFFS + 0x000000d4)
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_RMSK                                                                           0xffffffff
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_PTE_ROW7_MSB_ADDR)
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_PTE_ROW7_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_PTE_MCN_ATTRIBUTE_BMSK                                                         0x80000000
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_PTE_MCN_ATTRIBUTE_SHFT                                                               0x1f
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_MR_RT_PLY_BMSK                                                                 0x40000000
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_MR_RT_PLY_SHFT                                                                       0x1e
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_MR_HT_PLY_BMSK                                                                 0x20000000
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_MR_HT_PLY_SHFT                                                                       0x1d
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_MR_RT_DLY_BMSK                                                                 0x10000000
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_MR_RT_DLY_SHFT                                                                       0x1c
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_MR_HT_DLY_BMSK                                                                  0x8000000
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_MR_HT_DLY_SHFT                                                                       0x1b
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_MR_FT_HT_BMSK                                                                   0x4000000
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_MR_FT_HT_SHFT                                                                        0x1a
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_MR_FT_RT_BMSK                                                                   0x2000000
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_MR_FT_RT_SHFT                                                                        0x19
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_MR_WS_HT_BMSK                                                                   0x1000000
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_MR_WS_HT_SHFT                                                                        0x18
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_MR_WS_RT_BMSK                                                                    0x800000
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_MR_WS_RT_SHFT                                                                        0x17
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_PTE_DATA_502_500_BMSK                                                            0x700000
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_PTE_DATA_502_500_SHFT                                                                0x14
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_RBSC_CX_RET_BMSK                                                                  0xff000
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_RBSC_CX_RET_SHFT                                                                      0xc
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_PTE_DATA_106_101_BMSK                                                               0xfc0
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_PTE_DATA_106_101_SHFT                                                                 0x6
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_RBSC_AEBI_NOM_BMSK                                                                   0x3f
#define HWIO_QFPROM_CORR_PTE_ROW7_MSB_RBSC_AEBI_NOM_SHFT                                                                    0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x000009e8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x000009e8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_USB2PHY_RCAL_CODE_0_BMSK                                               0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_USB2PHY_RCAL_CODE_0_SHFT                                                     0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_CALIBRATION_30_16_BMSK                                                 0x7fff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_CALIBRATION_30_16_SHFT                                                       0x10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_0_NORTH_BGV_TRIM_BMSK                                               0xff00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN_0_NORTH_BGV_TRIM_SHFT                                                  0x8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN1_SOUTH_BGV_TRIM_BMSK                                                  0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_LSB_REFGEN1_SOUTH_BGV_TRIM_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x000009ec)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x000009ec)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_CALIBRATION_63_44_BMSK                                                 0xfffff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_CALIBRATION_63_44_SHFT                                                        0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_APSS_CS_ADC_VREFP_CTRL_IN_BMSK                                              0xf00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_APSS_CS_ADC_VREFP_CTRL_IN_SHFT                                                0x8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_CALIBATION_39_35_BMSK                                                        0xf8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_CALIBATION_39_35_SHFT                                                         0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_USB2PHY_RCAL_CODE_3_1_BMSK                                                    0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW0_MSB_USB2PHY_RCAL_CODE_3_1_SHFT                                                    0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x000009f0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x000009f0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_CALIBRATION_95_64_BMSK                                                 0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_LSB_CALIBRATION_95_64_SHFT                                                        0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x000009f4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x000009f4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_CALIBRATION_127_96_BMSK                                                0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW1_MSB_CALIBRATION_127_96_SHFT                                                       0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x000009f8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x000009f8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH3DQ0_PNTUNE_HT_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH3DQ0_PNTUNE_HT_SHFT                                                  0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH3CA_PNTUNE_HT_BMSK                                             0x30000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH3CA_PNTUNE_HT_SHFT                                                   0x1c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH2DQ1_PNTUNE_HT_BMSK                                             0xc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH2DQ1_PNTUNE_HT_SHFT                                                  0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH2DQ0_PNTUNE_HT_BMSK                                             0x3000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_DDRSS_CH2DQ0_PNTUNE_HT_SHFT                                                  0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_SVS2_BMSK                                                 0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_SVS2_SHFT                                                     0x12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_SVS_BMSK                                                   0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_SVS_SHFT                                                       0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_NOM_BMSK                                                     0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_NOM_SHFT                                                       0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_TURL1_BMSK                                                    0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_LSB_CPR0_TARG_VOLT_TURL1_SHFT                                                     0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x000009fc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x000009fc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CALIBRATION_191_187_BMSK                                               0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CALIBRATION_191_187_SHFT                                                     0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR11_BOOST_QUOT_MIN_BMSK                                               0x7ff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR11_BOOST_QUOT_MIN_SHFT                                                     0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR11_TARG_VOLT_BOOST_BMSK                                                 0x7e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_CPR11_TARG_VOLT_BOOST_SHFT                                                    0x9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_DDRSS_EW_FUSE_2_BMSK                                                        0x1fc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_DDRSS_EW_FUSE_2_SHFT                                                          0x2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_DDRSS_CH3DQ1_PNTUNE_HT_BMSK                                                   0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW2_MSB_DDRSS_CH3DQ1_PNTUNE_HT_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x00000a00)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x00000a00)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CALIBRATION_223_192_BMSK                                               0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_LSB_CALIBRATION_223_192_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x00000a04)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x00000a04)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CALIBRATION_255_224_BMSK                                               0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW3_MSB_CALIBRATION_255_224_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x00000a08)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x00000a08)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CALIBRATION_287_286_BMSK                                               0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CALIBRATION_287_286_SHFT                                                     0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ACC_HV_MXA_BMSK                                                        0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ACC_HV_MXA_SHFT                                                              0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ACC_HV_MXC_BMSK                                                          0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_ACC_HV_MXC_SHFT                                                              0x12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CALIBRATION_273_256_BMSK                                                  0x3ffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_LSB_CALIBRATION_273_256_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x00000a0c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x00000a0c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR0_TARG_VOLT_OFFSET_NOM_BMSK                                         0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR0_TARG_VOLT_OFFSET_NOM_SHFT                                               0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR0_TARG_VOLT_OFFSET_NOML1_BMSK                                        0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR0_TARG_VOLT_OFFSET_NOML1_SHFT                                             0x16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR0_TARG_VOLT_OFFSET_TUR_BMSK                                           0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR0_TARG_VOLT_OFFSET_TUR_SHFT                                               0x11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR0_TARG_VOLT_OFFSET_TURL1_BMSK                                          0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_CPR0_TARG_VOLT_OFFSET_TURL1_SHFT                                              0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ACC_LV_MXC_BMSK                                                             0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ACC_LV_MXC_SHFT                                                               0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ACC_LV_MXA_BMSK                                                              0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW4_MSB_ACC_LV_MXA_SHFT                                                               0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x00000a10)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x00000a10)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S5_BMSK                                                   0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S5_SHFT                                                         0x1c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S4_BMSK                                                    0xf000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S4_SHFT                                                         0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S3_BMSK                                                     0xf00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S3_SHFT                                                         0x14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S2_BMSK                                                      0xf0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S2_SHFT                                                         0x10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S1_BMSK                                                       0xf000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S1_SHFT                                                          0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S0_BMSK                                                        0xf00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_S0_SHFT                                                          0x8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_BMSK                                                            0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_LSB_VSENSE_FUSE1_SHFT                                                             0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x00000a14)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x00000a14)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S2_BMSK                                                   0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S2_SHFT                                                         0x1c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S1_BMSK                                                    0xf000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S1_SHFT                                                         0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S0_BMSK                                                     0xf00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_S0_SHFT                                                         0x14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_BMSK                                                         0xff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE2_SHFT                                                             0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE1_S8_BMSK                                                        0xf00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE1_S8_SHFT                                                          0x8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE1_S7_BMSK                                                         0xf0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE1_S7_SHFT                                                          0x4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE1_S6_BMSK                                                          0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW5_MSB_VSENSE_FUSE1_S6_SHFT                                                          0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x00000a18)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x00000a18)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR0_TARG_VOLT_OFFSET_SVSL1_BMSK                                       0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_CPR0_TARG_VOLT_OFFSET_SVSL1_SHFT                                             0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE_REVISION_CONTROL_BMSK                                       0x7000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE_REVISION_CONTROL_SHFT                                            0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S8_BMSK                                                     0xf00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S8_SHFT                                                         0x14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S7_BMSK                                                      0xf0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S7_SHFT                                                         0x10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S6_BMSK                                                       0xf000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S6_SHFT                                                          0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S5_BMSK                                                        0xf00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S5_SHFT                                                          0x8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S4_BMSK                                                         0xf0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S4_SHFT                                                          0x4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S3_BMSK                                                          0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_LSB_VSENSE_FUSE2_S3_SHFT                                                          0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x00000a1c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x00000a1c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR1_AGING_BMSK                                                        0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR1_AGING_SHFT                                                              0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR1_TARG_VOLT_NOML1_BMSK                                                0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR1_TARG_VOLT_NOML1_SHFT                                                    0x12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_AGING_BMSK                                                           0x3fc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_AGING_SHFT                                                               0xa
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_SVS2_BMSK                                             0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_SVS2_SHFT                                               0x5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_SVS_BMSK                                               0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW6_MSB_CPR0_TARG_VOLT_OFFSET_SVS_SHFT                                                0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x00000a20)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x00000a20)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_OFFSET_SVS_BMSK                                         0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_OFFSET_SVS_SHFT                                               0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_OFFSET_SVSL1_BMSK                                        0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_OFFSET_SVSL1_SHFT                                             0x16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_OFFSET_NOM_BMSK                                           0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_OFFSET_NOM_SHFT                                               0x11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_OFFSET_NOML1_BMSK                                          0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_OFFSET_NOML1_SHFT                                              0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_SVS_BMSK                                                     0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_SVS_SHFT                                                       0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_NOM_BMSK                                                      0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_LSB_CPR1_TARG_VOLT_NOM_SHFT                                                       0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x00000a24)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x00000a24)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR2_TARG_VOLT_OFFSET_TURL2_BMSK                                       0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR2_TARG_VOLT_OFFSET_TURL2_SHFT                                             0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR2_TARG_VOLT_OFFSET_TURL3_BMSK                                        0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR2_TARG_VOLT_OFFSET_TURL3_SHFT                                             0x16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR2_TARG_VOLT_TURL1_BMSK                                                0x3f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR2_TARG_VOLT_TURL1_SHFT                                                    0x10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR1_TARG_VOLT_SVS3_BMSK                                                   0xfc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR1_TARG_VOLT_SVS3_SHFT                                                      0xa
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR1_TARG_VOLT_OFFSET_SVS3_BMSK                                             0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR1_TARG_VOLT_OFFSET_SVS3_SHFT                                               0x5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR1_TARG_VOLT_OFFSET_SVS2_BMSK                                              0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW7_MSB_CPR1_TARG_VOLT_OFFSET_SVS2_SHFT                                               0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x00000a28)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x00000a28)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_SVS_BMSK                                                0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_SVS_SHFT                                                      0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_SVSL2_BMSK                                               0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_SVSL2_SHFT                                                    0x14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_OFFSET_NOM_BMSK                                            0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_OFFSET_NOM_SHFT                                                0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_OFFSET_NOML1_BMSK                                           0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_OFFSET_NOML1_SHFT                                              0xa
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_OFFSET_TUR_BMSK                                              0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_OFFSET_TUR_SHFT                                                0x5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_OFFSET_TURL1_BMSK                                             0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_LSB_CPR2_TARG_VOLT_OFFSET_TURL1_SHFT                                              0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x00000a2c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x00000a2c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_OFFSET_SVS_BMSK                                         0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_OFFSET_SVS_SHFT                                               0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_OFFSET_SVSL0_BMSK                                        0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_OFFSET_SVSL0_SHFT                                             0x16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_OFFSET_SVSL1_BMSK                                         0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_OFFSET_SVSL1_SHFT                                             0x11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_OFFSET_SVSL2_BMSK                                          0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_OFFSET_SVSL2_SHFT                                              0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_SVS3_BMSK                                                    0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_SVS3_SHFT                                                      0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_SVS2_BMSK                                                     0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW8_MSB_CPR2_TARG_VOLT_SVS2_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x00000a30)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x00000a30)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR4_TARG_VOLT_TURL1_BMSK                                              0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR4_TARG_VOLT_TURL1_SHFT                                                    0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR3_TARG_VOLT_SVS_BMSK                                                 0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR3_TARG_VOLT_SVS_SHFT                                                      0x14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR3_TARG_VOLT_NOM_BMSK                                                   0xfc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR3_TARG_VOLT_NOM_SHFT                                                       0xe
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR3_TARG_VOLT_TUR_BMSK                                                    0x3f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR3_TARG_VOLT_TUR_SHFT                                                       0x8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_AGING_BMSK                                                              0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_LSB_CPR2_AGING_SHFT                                                               0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR                                                                   (QFPROM_CORR_REG_BASE      + 0x00000a34)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_OFFS                                                                   (QFPROM_CORR_REG_BASE_OFFS + 0x00000a34)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_RMSK                                                                   0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR4_TARG_VOLT_NOM_BMSK                                                0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR4_TARG_VOLT_NOM_SHFT                                                      0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR4_TARG_VOLT_TUR_BMSK                                                 0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR4_TARG_VOLT_TUR_SHFT                                                      0x14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_LSVSD2_BMSK                                         0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_LSVSD2_SHFT                                             0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SVS3_BMSK                                            0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SVS3_SHFT                                               0xa
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_LSVSD0_BMSK                                           0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_LSVSD0_SHFT                                             0x5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SVS2_BMSK                                              0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW9_MSB_CPR2_TARG_VOLT_OFFSET_SVS2_SHFT                                               0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a38)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a38)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_OFFSET_NOM_BMSK                                        0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_OFFSET_NOM_SHFT                                              0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_OFFSET_NOML1_BMSK                                       0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_OFFSET_NOML1_SHFT                                            0x16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_OFFSET_TUR_BMSK                                          0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_OFFSET_TUR_SHFT                                              0x11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_OFFSET_TURL1_BMSK                                         0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_OFFSET_TURL1_SHFT                                             0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR5_TARG_VOLT_TURL1_BMSK                                                  0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR5_TARG_VOLT_TURL1_SHFT                                                    0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_SVS_BMSK                                                     0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_LSB_CPR4_TARG_VOLT_SVS_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a3c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a3c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR5_TARG_VOLT_NOM_BMSK                                               0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR5_TARG_VOLT_NOM_SHFT                                                     0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR5_TARG_VOLT_TUR_BMSK                                                0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR5_TARG_VOLT_TUR_SHFT                                                     0x14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR5_TARG_VOLT_OFFSET_TURL1_BMSK                                         0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR5_TARG_VOLT_OFFSET_TURL1_SHFT                                             0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_OFFSET_SVS2_BMSK                                           0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_OFFSET_SVS2_SHFT                                              0xa
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_OFFSET_SVS_BMSK                                             0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_OFFSET_SVS_SHFT                                               0x5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_OFFSET_SVSL1_BMSK                                            0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW10_MSB_CPR4_TARG_VOLT_OFFSET_SVSL1_SHFT                                             0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a40)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a40)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_OFFSET_SVSL1_BMSK                                      0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_OFFSET_SVSL1_SHFT                                            0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_OFFSET_NOM_BMSK                                         0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_OFFSET_NOM_SHFT                                              0x16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_OFFSET_NOML1_BMSK                                        0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_OFFSET_NOML1_SHFT                                            0x11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_OFFSET_TUR_BMSK                                           0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_OFFSET_TUR_SHFT                                               0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR6_TARG_VOLT_TUR_BMSK                                                    0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR6_TARG_VOLT_TUR_SHFT                                                      0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_SVS_BMSK                                                     0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_LSB_CPR5_TARG_VOLT_SVS_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a44)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a44)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR7_TARG_VOLT_TUR_BMSK                                               0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR7_TARG_VOLT_TUR_SHFT                                                     0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR6_TARG_VOLT_NOM_BMSK                                                0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR6_TARG_VOLT_NOM_SHFT                                                     0x14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR7_TARG_VOLT_OFFSET_NOM_BMSK                                           0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR7_TARG_VOLT_OFFSET_NOM_SHFT                                               0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR7_TARG_VOLT_OFFSET_TUR_BMSK                                            0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR7_TARG_VOLT_OFFSET_TUR_SHFT                                               0xa
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_SVS2_BMSK                                            0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_SVS2_SHFT                                              0x5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_SVS_BMSK                                              0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW11_MSB_CPR5_TARG_VOLT_OFFSET_SVS_SHFT                                               0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a48)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a48)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_OFFSET_SVS3_BMSK                                       0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_OFFSET_SVS3_SHFT                                             0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_OFFSET_SVS2_BMSK                                        0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_OFFSET_SVS2_SHFT                                             0x16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_OFFSET_SVS_BMSK                                          0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_OFFSET_SVS_SHFT                                              0x11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_OFFSET_SVSL1_BMSK                                         0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_OFFSET_SVSL1_SHFT                                             0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_SVS_BMSK                                                    0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_SVS_SHFT                                                      0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_NOM_BMSK                                                     0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_LSB_CPR7_TARG_VOLT_NOM_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a4c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a4c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR8_TARG_VOLT_SVS_BMSK                                               0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR8_TARG_VOLT_SVS_SHFT                                                     0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR8_TARG_VOLT_NOM_BMSK                                                0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR8_TARG_VOLT_NOM_SHFT                                                     0x14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR8_TARG_VOLT_TUR_BMSK                                                  0xfc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR8_TARG_VOLT_TUR_SHFT                                                      0xe
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_AGING_BMSK                                                           0x3fc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_AGING_SHFT                                                              0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_SVS3_BMSK                                                    0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW12_MSB_CPR7_TARG_VOLT_SVS3_SHFT                                                     0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a50)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a50)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR8_TARG_VOLT_OFFSET_SVSL1_BMSK                                      0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR8_TARG_VOLT_OFFSET_SVSL1_SHFT                                            0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR8_TARG_VOLT_OFFSET_NOM_BMSK                                         0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR8_TARG_VOLT_OFFSET_NOM_SHFT                                              0x16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR8_TARG_VOLT_OFFSET_NOML1_BMSK                                        0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR8_TARG_VOLT_OFFSET_NOML1_SHFT                                            0x11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR8_TARG_VOLT_OFFSET_TUR_BMSK                                           0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR8_TARG_VOLT_OFFSET_TUR_SHFT                                               0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR9_TARG_VOLT_TURL1_BMSK                                                  0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR9_TARG_VOLT_TURL1_SHFT                                                    0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR8_TARG_VOLT_SVS3_BMSK                                                    0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_LSB_CPR8_TARG_VOLT_SVS3_SHFT                                                     0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a54)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a54)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR9_TARG_VOLT_OFFSET_TURL1_BMSK                                      0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR9_TARG_VOLT_OFFSET_TURL1_SHFT                                            0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR9_TARG_VOLT_SVS_BMSK                                                0x7e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR9_TARG_VOLT_SVS_SHFT                                                     0x15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR9_TARG_VOLT_NOM_BMSK                                                 0x1f8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR9_TARG_VOLT_NOM_SHFT                                                      0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_OFFSET_SVS3_BMSK                                           0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_OFFSET_SVS3_SHFT                                              0xa
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_OFFSET_SVS2_BMSK                                            0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_OFFSET_SVS2_SHFT                                              0x5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_OFFSET_SVS_BMSK                                              0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW13_MSB_CPR8_TARG_VOLT_OFFSET_SVS_SHFT                                               0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a58)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a58)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR10_TARG_VOLT_NOM_BMSK                                              0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR10_TARG_VOLT_NOM_SHFT                                                    0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR10_TARG_VOLT_TURL1_BMSK                                             0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR10_TARG_VOLT_TURL1_SHFT                                                  0x14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR10_TARG_VOLT_BOOST_BMSK                                               0xfc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR10_TARG_VOLT_BOOST_SHFT                                                   0xe
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR9_TARG_VOLT_SVS3_BMSK                                                  0x3f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR9_TARG_VOLT_SVS3_SHFT                                                     0x8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_AGING_BMSK                                                             0xff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_LSB_CPR8_AGING_SHFT                                                              0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a5c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a5c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR10_TARG_VOLT_SVS2_BMSK                                             0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR10_TARG_VOLT_SVS2_SHFT                                                   0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR10_TARG_VOLT_SVS_BMSK                                               0x3f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR10_TARG_VOLT_SVS_SHFT                                                    0x14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_OFFSET_SVSL1_BMSK                                         0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_OFFSET_SVSL1_SHFT                                             0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_OFFSET_NOM_BMSK                                            0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_OFFSET_NOM_SHFT                                               0xa
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_OFFSET_NOML1_BMSK                                           0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_OFFSET_NOML1_SHFT                                             0x5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_OFFSET_TUR_BMSK                                              0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW14_MSB_CPR9_TARG_VOLT_OFFSET_TUR_SHFT                                               0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a60)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a60)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CALIBRATION_991_984_BMSK                                              0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CALIBRATION_991_984_SHFT                                                    0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_AON_TARG_VOLT_BMSK                                                      0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_AON_TARG_VOLT_SHFT                                                          0x12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR9_AGING_BMSK                                                          0x3fc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR9_AGING_SHFT                                                              0xa
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR9_TARG_VOLT_OFFSET_SVS2_BMSK                                            0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR9_TARG_VOLT_OFFSET_SVS2_SHFT                                              0x5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR9_TARG_VOLT_OFFSET_SVS_BMSK                                              0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_LSB_CPR9_TARG_VOLT_OFFSET_SVS_SHFT                                               0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a64)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a64)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CALIBRATION_1023_BMSK                                                 0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CALIBRATION_1023_SHFT                                                       0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_BOOST_QUOT_MIN_BMSK                                             0x7ff80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_BOOST_QUOT_MIN_SHFT                                                   0x13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_TARG_VOLT_SVS3_BMSK                                                0x7e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_TARG_VOLT_SVS3_SHFT                                                    0xd
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_QUOT_OFFSET_BMSK                                                    0x1fe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR10_QUOT_OFFSET_SHFT                                                       0x5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR9_TARG_VOLT_OFFSET_SVS3_BMSK                                             0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW15_MSB_CPR9_TARG_VOLT_OFFSET_SVS3_SHFT                                              0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a68)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a68)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_AGING_BMSK                                                      0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_AGING_SHFT                                                            0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_NOM_QUOT_MIN_BMSK                                                 0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_NOM_QUOT_MIN_SHFT                                                      0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_TURL1_QUOT_MIN_BMSK                                                  0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_LSB_CPR10_TURL1_QUOT_MIN_SHFT                                                    0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a6c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a6c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CALIBRATION_1087_1086_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CALIBRATION_1087_1086_SHFT                                                  0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR11_TARG_VOLT_TURL1_BMSK                                            0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR11_TARG_VOLT_TURL1_SHFT                                                  0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_SVS2_QUOT_MIN_BMSK                                                0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_SVS2_QUOT_MIN_SHFT                                                     0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_SVS_QUOT_MIN_BMSK                                                    0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW16_MSB_CPR10_SVS_QUOT_MIN_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a70)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a70)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CALIBRATION_1119_1118_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CALIBRATION_1119_1118_SHFT                                                  0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_NOM_BMSK                                              0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TARG_VOLT_NOM_SHFT                                                    0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TURL1_QUOT_MIN_BMSK                                               0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR11_TURL1_QUOT_MIN_SHFT                                                    0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR10_SVS3_QUOT_MIN_BMSK                                                   0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_LSB_CPR10_SVS3_QUOT_MIN_SHFT                                                     0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a74)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a74)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CALIBRATION_1151_1150_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CALIBRATION_1151_1150_SHFT                                                  0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_NOM_QUOT_MIN_BMSK                                               0x3ffc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_NOM_QUOT_MIN_SHFT                                                     0x12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TARG_VOLT_SVS3_BMSK                                                0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TARG_VOLT_SVS3_SHFT                                                    0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TARG_VOLT_SVS2_BMSK                                                  0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TARG_VOLT_SVS2_SHFT                                                    0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TARG_VOLT_SVS_BMSK                                                    0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW17_MSB_CPR11_TARG_VOLT_SVS_SHFT                                                     0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a78)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a78)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_QUOT_OFFSET_BMSK                                                0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_QUOT_OFFSET_SHFT                                                      0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_SVS2_QUOT_MIN_BMSK                                                0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_SVS2_QUOT_MIN_SHFT                                                     0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_SVS_QUOT_MIN_BMSK                                                    0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_LSB_CPR11_SVS_QUOT_MIN_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a7c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a7c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_BOOST_BMSK                                            0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_BOOST_SHFT                                                  0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR11_SVS3_QUOT_MIN_BMSK                                               0x3ffc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR11_SVS3_QUOT_MIN_SHFT                                                     0xe
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_AON_AGING_BMSK                                                            0x3fc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_AON_AGING_SHFT                                                               0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_BOOSTP_BMSK                                                 0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW18_MSB_CPR12_TARG_VOLT_BOOSTP_SHFT                                                  0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a80)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a80)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_QUOT_OFFSET_BMSK                                                0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_QUOT_OFFSET_SHFT                                                      0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_SVS2_BMSK                                               0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_SVS2_SHFT                                                   0x12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_SVS_BMSK                                                 0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_SVS_SHFT                                                     0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_NOM_BMSK                                                   0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_NOM_SHFT                                                     0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_TURL3_BMSK                                                  0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_LSB_CPR12_TARG_VOLT_TURL3_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a84)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a84)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CALIBRATION_1279_1278_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CALIBRATION_1279_1278_SHFT                                                  0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_BOOST_QUOT_MIN_BMSK                                             0x3ffc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_BOOST_QUOT_MIN_SHFT                                                   0x12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_BOOSTP_QUOT_MIN_BMSK                                               0x3ffc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_BOOSTP_QUOT_MIN_SHFT                                                   0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_TARG_VOLT_SVS3_BMSK                                                   0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW19_MSB_CPR12_TARG_VOLT_SVS3_SHFT                                                    0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a88)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a88)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CALIBRATION_1311_1310_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CALIBRATION_1311_1310_SHFT                                                  0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_GNSS_ADC_CAL_BMSK                                                     0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_GNSS_ADC_CAL_SHFT                                                           0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR12_NOM_QUOT_MIN_BMSK                                                 0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR12_NOM_QUOT_MIN_SHFT                                                      0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR12_TURL3_QUOT_MIN_BMSK                                                  0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_LSB_CPR12_TURL3_QUOT_MIN_SHFT                                                    0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a8c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a8c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CALIBRATION_1343_1339_BMSK                                            0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CALIBRATION_1343_1339_SHFT                                                  0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_NSPCX_MODE_DISABLE_BMSK                                            0x7000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_NSPCX_MODE_DISABLE_SHFT                                                 0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MMCX_MODE_DISABLE_BMSK                                              0xe00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MMCX_MODE_DISABLE_SHFT                                                  0x15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_LPICX_MODE_DISABLE_BMSK                                             0x1c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_LPICX_MODE_DISABLE_SHFT                                                 0x12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_LPIMX_MODE_DISABLE_BMSK                                              0x38000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_LPIMX_MODE_DISABLE_SHFT                                                  0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MXC_MODE_DISABLE_BMSK                                                 0x7000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MXC_MODE_DISABLE_SHFT                                                    0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MX_MODE_DISABLE_BMSK                                                   0xe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MX_MODE_DISABLE_SHFT                                                     0x9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_GFX_MODE_DISABLE_BMSK                                                  0x1c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_GFX_MODE_DISABLE_SHFT                                                    0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MSS_MODE_DISABLE_BMSK                                                   0x38
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_MSS_MODE_DISABLE_SHFT                                                    0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_CX_MODE_DISABLE_BMSK                                                     0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW20_MSB_CPR_CX_MODE_DISABLE_SHFT                                                     0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a90)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a90)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR13_TARG_VOLT_BOOSTP_BMSK                                           0xfc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR13_TARG_VOLT_BOOSTP_SHFT                                                 0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR12_AGING_BMSK                                                       0x3fc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR12_AGING_SHFT                                                            0x12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CALIBRATION_1361_1359_BMSK                                               0x38000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CALIBRATION_1361_1359_SHFT                                                   0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_VDDA_MODE_DISABLE_BMSK                                                0x7000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_VDDA_MODE_DISABLE_SHFT                                                   0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_APC1_GOLDP_MODE_DISABLE_BMSK                                           0xe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_APC1_GOLDP_MODE_DISABLE_SHFT                                             0x9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_APC1_GOLD_MODE_DISABLE_BMSK                                            0x1c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_APC1_GOLD_MODE_DISABLE_SHFT                                              0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_APC0_L3_MODE_DISABLE_BMSK                                               0x38
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_APC0_L3_MODE_DISABLE_SHFT                                                0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_APC0_SILVER_MODE_DISABLE_BMSK                                            0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_LSB_CPR_APC0_SILVER_MODE_DISABLE_SHFT                                            0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a94)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a94)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CALIBRATION_1407_1403_BMSK                                            0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CALIBRATION_1407_1403_SHFT                                                  0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_APC0_PEAK_THROTTLE_FREQ_BMSK                                           0x6000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_APC0_PEAK_THROTTLE_FREQ_SHFT                                                0x19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_APC0_PEAK_THROTTLE_TJ_BMSK                                             0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_APC0_PEAK_THROTTLE_TJ_SHFT                                                  0x14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR13_QUOT_OFFSET_BMSK                                                   0xff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR13_QUOT_OFFSET_SHFT                                                       0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR12_SVS_QUOT_MIN_BMSK                                                    0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW21_MSB_CPR12_SVS_QUOT_MIN_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a98)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a98)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR_LOCAL_RC_BMSK                                                     0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR_LOCAL_RC_SHFT                                                           0x1c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR_GLOBAL_RC_BMSK                                                     0xf000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_CPR_GLOBAL_RC_SHFT                                                          0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ACC_LV_APC1_BMSK                                                        0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ACC_LV_APC1_SHFT                                                            0x12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ACC_LV_APC0_BMSK                                                         0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ACC_LV_APC0_SHFT                                                             0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ACC_HV_APC1_BMSK                                                           0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ACC_HV_APC1_SHFT                                                             0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ACC_HV_APC0_BMSK                                                            0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_LSB_ACC_HV_APC0_SHFT                                                             0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000a9c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000a9c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_AOSS_K_BMSK                                                           0xffff0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_AOSS_K_SHFT                                                                 0x10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_CALIBRATION_1455_BMSK                                                     0x8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_CALIBRATION_1455_SHFT                                                        0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_GFX_FUSE_RESERVED_2_0_BMSK                                                0x7000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_GFX_FUSE_RESERVED_2_0_SHFT                                                   0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_CPR12_SVS2_QUOT_MIN_BMSK                                                   0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW22_MSB_CPR12_SVS2_QUOT_MIN_SHFT                                                     0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000aa0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000aa0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CALIBRATION_1503_1500_BMSK                                            0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_CALIBRATION_1503_1500_SHFT                                                  0x1c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_TDOPCODE_BMSK                                                     0xf800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_TDOPCODE_SHFT                                                          0x17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_RDOPCODE_BMSK                                                      0x7c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_RDOPCODE_SHFT                                                          0x12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_N1_BMSK                                                             0x3ffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_LSB_AOSS_N1_SHFT                                                                 0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000aa4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000aa4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_TSENS1_BASE1_BMSK                                                     0xffc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_TSENS1_BASE1_SHFT                                                           0x16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_CALIBRATION_1525_1522_BMSK                                              0x3c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_CALIBRATION_1525_1522_SHFT                                                  0x12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_AOSS_P1_BMSK                                                             0x3ffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW23_MSB_AOSS_P1_SHFT                                                                 0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000aa8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000aa8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_CALIBRATION_1567_1566_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_CALIBRATION_1567_1566_SHFT                                                  0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS1_BASE0_BMSK                                                     0x3ff00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS1_BASE0_SHFT                                                           0x14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS0_BASE1_BMSK                                                        0xffc00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS0_BASE1_SHFT                                                            0xa
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS0_BASE0_BMSK                                                          0x3ff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_LSB_TSENS0_BASE0_SHFT                                                            0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000aac)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000aac)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_CALIBRATION_1599_1596_BMSK                                            0xf0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_CALIBRATION_1599_1596_SHFT                                                  0x1c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS3_OFFSET_BMSK                                                     0xf800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS3_OFFSET_SHFT                                                          0x17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS2_OFFSET_BMSK                                                      0x7c0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS2_OFFSET_SHFT                                                          0x12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS1_OFFSET_BMSK                                                       0x3e000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS1_OFFSET_SHFT                                                           0xd
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS0_OFFSET_BMSK                                                        0x1f00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_TSENS0_OFFSET_SHFT                                                           0x8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_CALIBRATION_1575_1574_BMSK                                                  0xc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_CALIBRATION_1575_1574_SHFT                                                   0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_CPR13_TARG_VOLT_BOOST_BMSK                                                  0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW24_MSB_CPR13_TARG_VOLT_BOOST_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000ab0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000ab0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_CALIBRATION_1631_BMSK                                                 0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_CALIBRATION_1631_SHFT                                                       0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS10_OFFSET_BMSK                                                   0x7c000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS10_OFFSET_SHFT                                                         0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS9_OFFSET_BMSK                                                     0x3e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS9_OFFSET_SHFT                                                          0x15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS8_OFFSET_BMSK                                                      0x1f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS8_OFFSET_SHFT                                                          0x10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS7_OFFSET_BMSK                                                        0xf800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS7_OFFSET_SHFT                                                           0xb
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS6_OFFSET_BMSK                                                         0x7c0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS6_OFFSET_SHFT                                                           0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS5_OFFSET_BMSK                                                          0x3e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_TSENS5_OFFSET_SHFT                                                           0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_CALIBRATION_1600_BMSK                                                        0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_LSB_CALIBRATION_1600_SHFT                                                        0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000ab4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000ab4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_CALIBRATION_1663_1661_BMSK                                            0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_CALIBRATION_1663_1661_SHFT                                                  0x1d
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS16_OFFSET_BMSK                                                   0x1f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS16_OFFSET_SHFT                                                         0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS15_OFFSET_BMSK                                                     0xf80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS15_OFFSET_SHFT                                                         0x13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS14_OFFSET_BMSK                                                      0x7c000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS14_OFFSET_SHFT                                                          0xe
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS13_OFFSET_BMSK                                                       0x3e00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS13_OFFSET_SHFT                                                          0x9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS12_OFFSET_BMSK                                                        0x1f0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_TSENS12_OFFSET_SHFT                                                          0x4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_CALIBRATION_1635_1632_BMSK                                                   0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW25_MSB_CALIBRATION_1635_1632_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000ab8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000ab8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS23_OFFSET_BMSK                                                   0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS23_OFFSET_SHFT                                                         0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS22_OFFSET_BMSK                                                    0x7c00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS22_OFFSET_SHFT                                                         0x16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS21_OFFSET_BMSK                                                     0x3e0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS21_OFFSET_SHFT                                                         0x11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS20_OFFSET_BMSK                                                      0x1f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS20_OFFSET_SHFT                                                          0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS19_OFFSET_BMSK                                                        0xf80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS19_OFFSET_SHFT                                                          0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS18_OFFSET_BMSK                                                         0x7c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_TSENS18_OFFSET_SHFT                                                          0x2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_CALIBRATION_1665_1664_BMSK                                                   0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_LSB_CALIBRATION_1665_1664_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000abc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000abc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_CALIBRATION_1727_1726_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_CALIBRATION_1727_1726_SHFT                                                  0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS29_OFFSET_BMSK                                                   0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS29_OFFSET_SHFT                                                         0x19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS28_OFFSET_BMSK                                                    0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS28_OFFSET_SHFT                                                         0x14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS27_OFFSET_BMSK                                                      0xf8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS27_OFFSET_SHFT                                                          0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS26_OFFSET_BMSK                                                       0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS26_OFFSET_SHFT                                                          0xa
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS25_OFFSET_BMSK                                                        0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS25_OFFSET_SHFT                                                          0x5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS24_OFFSET_BMSK                                                         0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW26_MSB_TSENS24_OFFSET_SHFT                                                          0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000ac0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000ac0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_CALIBRATION_1759_BMSK                                                 0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_CALIBRATION_1759_SHFT                                                       0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS11_OFFSET_BMSK                                                   0x7c000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS11_OFFSET_SHFT                                                         0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS34_OFFSET_BMSK                                                    0x3e00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS34_OFFSET_SHFT                                                         0x15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS33_OFFSET_BMSK                                                     0x1f0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS33_OFFSET_SHFT                                                         0x10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS32_OFFSET_BMSK                                                       0xf800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS32_OFFSET_SHFT                                                          0xb
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS_CAL_SEL_BMSK                                                         0x700
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS_CAL_SEL_SHFT                                                           0x8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS31_OFFSET_BMSK                                                         0xf8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_TSENS31_OFFSET_SHFT                                                          0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_CALIBRATION_1730_1728_BMSK                                                   0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_LSB_CALIBRATION_1730_1728_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000ac4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000ac4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_CALIBRATION_1791_1787_BMSK                                            0xf8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_CALIBRATION_1791_1787_SHFT                                                  0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_CPR13_BOOSTP_QUOT_MIN_BMSK                                             0x7ff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_CPR13_BOOSTP_QUOT_MIN_SHFT                                                   0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS4_OFFSET_BMSK                                                        0x7c00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS4_OFFSET_SHFT                                                           0xa
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS30_OFFSET_BMSK                                                        0x3e0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS30_OFFSET_SHFT                                                          0x5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS17_OFFSET_BMSK                                                         0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW27_MSB_TSENS17_OFFSET_SHFT                                                          0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000ac8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000ac8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CALIBRATION_1823_1822_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CALIBRATION_1823_1822_SHFT                                                  0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_SVS3_BMSK                                             0x3f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_SVS3_SHFT                                                   0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_SVS2_BMSK                                               0xfc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_SVS2_SHFT                                                   0x12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_SVS_BMSK                                                 0x3f000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_SVS_SHFT                                                     0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_NOM_BMSK                                                   0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_NOM_SHFT                                                     0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_TURL3_BMSK                                                  0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_LSB_CPR13_TARG_VOLT_TURL3_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000acc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000acc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CALIBRATION_1855_1848_BMSK                                            0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CALIBRATION_1855_1848_SHFT                                                  0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CPR13_TURL3_QUOT_MIN_BMSK                                               0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CPR13_TURL3_QUOT_MIN_SHFT                                                    0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CPR13_BOOST_QUOT_MIN_BMSK                                                  0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW28_MSB_CPR13_BOOST_QUOT_MIN_SHFT                                                    0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000ad0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000ad0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_CALIBRATION_1887_1856_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_LSB_CALIBRATION_1887_1856_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000ad4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000ad4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_CALIBRATION_1919_1888_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW29_MSB_CALIBRATION_1919_1888_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000ad8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000ad8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_CALIBRATION_1951_1934_BMSK                                            0xffffc000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_CALIBRATION_1951_1934_SHFT                                                   0xe
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_CPR13_NOM_QUOT_MIN_BMSK                                                   0x3ffc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_CPR13_NOM_QUOT_MIN_SHFT                                                      0x2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_CALIBRATION_1921_1920_BMSK                                                   0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_LSB_CALIBRATION_1921_1920_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000adc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000adc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_CALIBRATION_1983_1952_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW30_MSB_CALIBRATION_1983_1952_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000ae0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000ae0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CALIBRATION_2015_2014_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CALIBRATION_2015_2014_SHFT                                                  0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_VOLTAGE_DELTA_BMSK                                           0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_VOLTAGE_DELTA_SHFT                                                 0x19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_VOLTAGE_V_HF_BMSK                                             0x1ff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_VOLTAGE_V_HF_SHFT                                                   0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_CURRENT_DELTA_BMSK                                               0x7ff8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_GFX_PEAK_CURRENT_DELTA_SHFT                                                  0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CALIBRATION_1986_1984_BMSK                                                   0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_LSB_CALIBRATION_1986_1984_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000ae4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000ae4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CALIBRATION_2047_2040_BMSK                                            0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CALIBRATION_2047_2040_SHFT                                                  0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CPR13_SVS2_QUOT_MIN_BMSK                                                0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CPR13_SVS2_QUOT_MIN_SHFT                                                     0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CPR13_SVS_QUOT_MIN_BMSK                                                    0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW31_MSB_CPR13_SVS_QUOT_MIN_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000ae8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000ae8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_CALIBRATION_2079_2048_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_LSB_CALIBRATION_2079_2048_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000aec)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000aec)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CALIBRATION_2111_2104_BMSK                                            0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CALIBRATION_2111_2104_SHFT                                                  0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CPR13_SVS3_QUOT_MIN_BMSK                                                0xfff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CPR13_SVS3_QUOT_MIN_SHFT                                                     0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CALIBRATION_2091_2080_BMSK                                                 0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW32_MSB_CALIBRATION_2091_2080_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000af0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000af0)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CALIBRATION_2143_2141_BMSK                                            0xe0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CALIBRATION_2143_2141_SHFT                                                  0x1d
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ACD_NSP_DVM_TURL1_BMSK                                                0x1fffffe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_ACD_NSP_DVM_TURL1_SHFT                                                       0x5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CALIBRATION_2116_2112_BMSK                                                  0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_LSB_CALIBRATION_2116_2112_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000af4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000af4)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_GFX_CURRENT_REVISION_BMSK                                             0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_GFX_CURRENT_REVISION_SHFT                                                   0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_CALIBRATION_2173_2157_BMSK                                            0x3fffe000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_CALIBRATION_2173_2157_SHFT                                                   0xd
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_GFX_PEAK_CURRENT_I_LF_BMSK                                                0x1fff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW33_MSB_GFX_PEAK_CURRENT_I_LF_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000af8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000af8)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CALIBATION_2207_2206_BMSK                                             0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CALIBATION_2207_2206_SHFT                                                   0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CALIBRATION_2205_2201_BMSK                                            0x3e000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CALIBRATION_2205_2201_SHFT                                                  0x19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CALIBATION_2200_2196_BMSK                                              0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CALIBATION_2200_2196_SHFT                                                   0x14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CALIBRATION_2195_2194_BMSK                                               0xc0000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_CALIBRATION_2195_2194_SHFT                                                  0x12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_GFX_FUSE_RESERVED_16_0_BMSK                                              0x3ffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_LSB_GFX_FUSE_RESERVED_16_0_SHFT                                                  0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000afc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000afc)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CALIBRATION_2239_2231_BMSK                                            0xff800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CALIBRATION_2239_2231_SHFT                                                  0x17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CALIBATION_2230_2208_BMSK                                               0x7fffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW34_MSB_CALIBATION_2230_2208_SHFT                                                    0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000b00)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000b00)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_CALIBRATION_2271_2264_BMSK                                            0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_CALIBRATION_2271_2264_SHFT                                                  0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ACD_NSP_DVM_TUR_BMSK                                                    0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_LSB_ACD_NSP_DVM_TUR_SHFT                                                         0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000b04)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000b04)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CALIBRATION_2303_2302_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CALIBRATION_2303_2302_SHFT                                                  0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CALIBATION_2302_2285_BMSK                                             0x3ffff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CALIBATION_2302_2285_SHFT                                                    0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CALIBRATION_2283_2278_BMSK                                                 0xfc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CALIBRATION_2283_2278_SHFT                                                   0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CALIBATION_2277_2272_BMSK                                                   0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW35_MSB_CALIBATION_2277_2272_SHFT                                                    0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000b08)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000b08)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_CALIBRATION_2335_2316_BMSK                                            0xfffff000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_CALIBRATION_2335_2316_SHFT                                                   0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_CPR12_SVS3_QUOT_MIN_BMSK                                                   0xfff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_LSB_CPR12_SVS3_QUOT_MIN_SHFT                                                     0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000b0c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000b0c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CALIBRATION_2367_2336_BMSK                                            0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW36_MSB_CALIBRATION_2367_2336_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000b10)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000b10)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CALIBRATION_2399_2383_BMSK                                            0xffff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CALIBRATION_2399_2383_SHFT                                                   0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CALIBATION_2382_BMSK                                                      0x4000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CALIBATION_2382_SHFT                                                         0xe
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CALIBRATION_2381_2368_BMSK                                                0x3fff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_LSB_CALIBRATION_2381_2368_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000b14)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000b14)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS98_AUP1_BMSK                                      0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS98_AUP1_SHFT                                            0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AG2_BMSK                                       0x40000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AG2_SHFT                                             0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AG1_BMSK                                       0x20000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AG1_SHFT                                             0x1d
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU_BMSK                                        0x10000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU_SHFT                                              0x1c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU2_BMSK                                        0x8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU2_SHFT                                             0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU1_BMSK                                        0x4000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AU1_SHFT                                             0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP_BMSK                                        0x2000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP_SHFT                                             0x19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP2_BMSK                                       0x1000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP2_SHFT                                            0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP1_BMSK                                        0x800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CPU_DYN_MEM_ACC_BITS65_AUP1_SHFT                                            0x17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CALIBRATION_2422_2400_BMSK                                              0x7fffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW37_MSB_CALIBRATION_2422_2400_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000b18)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000b18)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_TSENS2_BASE0_BMSK                                                     0xffc00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_TSENS2_BASE0_SHFT                                                           0x16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CALIBRATION_2453_2441_BMSK                                              0x3ffe00
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CALIBRATION_2453_2441_SHFT                                                   0x9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_GFX_CDYN_REVISION_BMSK                                                     0x180
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_GFX_CDYN_REVISION_SHFT                                                       0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP8_BMSK                                            0x40
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP8_SHFT                                             0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP7_BMSK                                            0x20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP7_SHFT                                             0x5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP6_BMSK                                            0x10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP6_SHFT                                             0x4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP5_BMSK                                             0x8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP5_SHFT                                             0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP4_BMSK                                             0x4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP4_SHFT                                             0x2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP3_BMSK                                             0x2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP3_SHFT                                             0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP2_BMSK                                             0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_LSB_CPU_DYN_MEM_ACC_BITS98_AUP2_SHFT                                             0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000b1c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000b1c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_CALIBRATION_2495_2488_BMSK                                            0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_CALIBRATION_2495_2488_SHFT                                                  0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ACD_NSP_DVM_ENABLE_BMSK                                                 0xff8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ACD_NSP_DVM_ENABLE_SHFT                                                      0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_TSENS2_BASE1_BMSK                                                         0x7fe0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_TSENS2_BASE1_SHFT                                                            0x5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ACD_NSP_REVISION_BIT_BMSK                                                   0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_ACD_NSP_REVISION_BIT_SHFT                                                    0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_CALIBRATION_2466_2464_BMSK                                                   0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW38_MSB_CALIBRATION_2466_2464_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000b20)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000b20)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_DDRSS_CH2CA_PNTUNE_HT_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_DDRSS_CH2CA_PNTUNE_HT_SHFT                                                  0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_DDRSS_CH1DQ1_PNTUNE_HT_BMSK                                           0x30000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_DDRSS_CH1DQ1_PNTUNE_HT_SHFT                                                 0x1c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_DDRSS_CH1DQ0_PNTUNE_HT_BMSK                                            0xc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_DDRSS_CH1DQ0_PNTUNE_HT_SHFT                                                 0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_DDRSS_CH1CA_PNTUNE_HT_BMSK                                             0x3000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_DDRSS_CH1CA_PNTUNE_HT_SHFT                                                  0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ACD_NSP_DVM_LSVSD1_BMSK                                                 0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_LSB_ACD_NSP_DVM_LSVSD1_SHFT                                                      0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000b24)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000b24)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_DDRSS_CH0DQ1_PNTUNE_HT_BMSK                                           0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_DDRSS_CH0DQ1_PNTUNE_HT_SHFT                                                 0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_DDRSS_CH0DQ0_PNTUNE_HT_BMSK                                           0x30000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_DDRSS_CH0DQ0_PNTUNE_HT_SHFT                                                 0x1c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_DDRSS_CH0CA_PNTUNE_HT_BMSK                                             0xc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_DDRSS_CH0CA_PNTUNE_HT_SHFT                                                  0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_DDRSS_CH3DQ1_PNTUNE_RT_BMSK                                            0x3000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_DDRSS_CH3DQ1_PNTUNE_RT_SHFT                                                 0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ACD_NSP_DVM_LSVS_BMSK                                                   0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW39_MSB_ACD_NSP_DVM_LSVS_SHFT                                                        0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000b28)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000b28)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_DDRSS_CH3DQ0_PNTUNE_RT_BMSK                                           0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_DDRSS_CH3DQ0_PNTUNE_RT_SHFT                                                 0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_DDRSS_CH3CA_PNTUNE_RT_BMSK                                            0x30000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_DDRSS_CH3CA_PNTUNE_RT_SHFT                                                  0x1c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_DDRSS_CH2DQ1_PNTUNE_RT_BMSK                                            0xc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_DDRSS_CH2DQ1_PNTUNE_RT_SHFT                                                 0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_DDRSS_CH2DQ0_PNTUNE_RT_BMSK                                            0x3000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_DDRSS_CH2DQ0_PNTUNE_RT_SHFT                                                 0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ACD_NSP_DVM_SVS_BMSK                                                    0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_LSB_ACD_NSP_DVM_SVS_SHFT                                                         0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000b2c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000b2c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_CALIBRATION_2623_2616_BMSK                                            0xff000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_CALIBRATION_2623_2616_SHFT                                                  0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ACD_NSP_DVM_SVSL1_BMSK                                                  0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW40_MSB_ACD_NSP_DVM_SVSL1_SHFT                                                       0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000b30)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000b30)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_DDRSS_CH2CA_PNTUNE_RT_BMSK                                            0xc0000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_DDRSS_CH2CA_PNTUNE_RT_SHFT                                                  0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_DDRSS_CH1DQ1_PNTUNE_RT_BMSK                                           0x30000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_DDRSS_CH1DQ1_PNTUNE_RT_SHFT                                                 0x1c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_DDRSS_CH1DQ0_PNTUNE_RT_BMSK                                            0xc000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_DDRSS_CH1DQ0_PNTUNE_RT_SHFT                                                 0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_DDRSS_CH1CA_PNTUNE_RT_BMSK                                             0x3000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_DDRSS_CH1CA_PNTUNE_RT_SHFT                                                  0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ACD_NSP_DVM_NOM_BMSK                                                    0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_LSB_ACD_NSP_DVM_NOM_SHFT                                                         0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000b34)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000b34)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_CALIBRATION_2687_BMSK                                                 0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_CALIBRATION_2687_SHFT                                                       0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_DDRSS_EW_FUSE_1_BMSK                                                  0x7f000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_DDRSS_EW_FUSE_1_SHFT                                                        0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ACD_NSP_DVM_NOML1_BMSK                                                  0xffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW41_MSB_ACD_NSP_DVM_NOML1_SHFT                                                       0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000b38)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000b38)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_CALIBRATION_2719_BMSK                                                 0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_CALIBRATION_2719_SHFT                                                       0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0DQ1_PNTUNE_RT_BMSK                                           0x60000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0DQ1_PNTUNE_RT_SHFT                                                 0x1d
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0DQ0_PNTUNE_RT_BMSK                                           0x18000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0DQ0_PNTUNE_RT_SHFT                                                 0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0CA_PNTUNE_RT_BMSK                                             0x6000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_CH0CA_PNTUNE_RT_SHFT                                                  0x19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_TP_REV_CTRL_BMSK                                                 0x1f00000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_TP_REV_CTRL_SHFT                                                      0x14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_EH_FUSE_2_BMSK                                                     0xfe000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_EH_FUSE_2_SHFT                                                         0xd
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_EH_FUSE_1_BMSK                                                      0x1fc0
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_DDRSS_EH_FUSE_1_SHFT                                                         0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_CALIBRATION_2693_2688_BMSK                                                  0x3f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_LSB_CALIBRATION_2693_2688_SHFT                                                   0x0

#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ADDR                                                                  (QFPROM_CORR_REG_BASE      + 0x00000b3c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_OFFS                                                                  (QFPROM_CORR_REG_BASE_OFFS + 0x00000b3c)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_RMSK                                                                  0xffffffff
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_IN          \
        in_dword(HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ADDR)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_INM(m)      \
        in_dword_masked(HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ADDR, m)
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_FT_BMSK                                                           0x80000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_FT_SHFT                                                                 0x1f
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_WS_BMSK                                                           0x40000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GFX_WS_SHFT                                                                 0x1e
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_VSENS_FT_BMSK                                                         0x20000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_VSENS_FT_SHFT                                                               0x1d
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_VSENS_WS_BMSK                                                         0x10000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_VSENS_WS_SHFT                                                               0x1c
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ACD_NSP_FT_BMSK                                                        0x8000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ACD_NSP_FT_SHFT                                                             0x1b
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ACD_NSP_WS_BMSK                                                        0x4000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_ACD_NSP_WS_SHFT                                                             0x1a
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DACC_FT_BMSK                                                           0x2000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DACC_FT_SHFT                                                                0x19
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DACC_WS_BMSK                                                           0x1000000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DACC_WS_SHFT                                                                0x18
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GNSS_FT_BMSK                                                            0x800000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GNSS_FT_SHFT                                                                0x17
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GNSS_WS_BMSK                                                            0x400000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_GNSS_WS_SHFT                                                                0x16
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_USB_FT_BMSK                                                             0x200000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_USB_FT_SHFT                                                                 0x15
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_USB_WS_BMSK                                                             0x100000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_USB_WS_SHFT                                                                 0x14
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_REFGEN_FT_BMSK                                                           0x80000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_REFGEN_FT_SHFT                                                              0x13
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_REFGEN_WS_BMSK                                                           0x40000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_REFGEN_WS_SHFT                                                              0x12
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_CPR_FT_BMSK                                                              0x20000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_CPR_FT_SHFT                                                                 0x11
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_CPR_WS_BMSK                                                              0x10000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_CPR_WS_SHFT                                                                 0x10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_LRET_FT_BMSK                                                              0x8000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_LRET_FT_SHFT                                                                 0xf
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_LRET_WS_BMSK                                                              0x4000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_LRET_WS_SHFT                                                                 0xe
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_MRET_FT_BMSK                                                              0x2000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_MRET_FT_SHFT                                                                 0xd
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_MRET_WS_BMSK                                                              0x1000
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_MRET_WS_SHFT                                                                 0xc
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_AOSS_FT_BMSK                                                               0x800
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_AOSS_FT_SHFT                                                                 0xb
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_AOSS_WS_BMSK                                                               0x400
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_AOSS_WS_SHFT                                                                 0xa
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDR_FT_BMSK                                                                0x200
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDR_FT_SHFT                                                                  0x9
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDR_WS_BMSK                                                                0x100
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DDR_WS_SHFT                                                                  0x8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_IDDQ_FT_BMSK                                                                0x80
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_IDDQ_FT_SHFT                                                                 0x7
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_IDDQ_WS_BMSK                                                                0x40
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_IDDQ_WS_SHFT                                                                 0x6
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DVS_FT_BMSK                                                                 0x20
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DVS_FT_SHFT                                                                  0x5
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DVS_WS_BMSK                                                                 0x10
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_DVS_WS_SHFT                                                                  0x4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_TSENS_FT_BMSK                                                                0x8
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_TSENS_FT_SHFT                                                                0x3
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_TSENS_WS_BMSK                                                                0x4
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_TSENS_WS_SHFT                                                                0x2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_QFPROM_FT_BMSK                                                               0x2
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_QFPROM_FT_SHFT                                                               0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_QFPROM_WS_BMSK                                                               0x1
#define HWIO_QFPROM_CORR_CALIBRATION_ROW42_MSB_QFPROM_WS_SHFT                                                               0x0

/*----------------------------------------------------------------------------
 * MODULE: FUSE_CONTROLLER_SW_RANGE4
 *--------------------------------------------------------------------------*/

#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE                                                                 (TMESS_BASE      + 0x021c8000)
#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE                                                            0x1000
#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE_USED                                                            0xc7c
#define FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS                                                            0x021c8000

#define HWIO_CALIBRATION0_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b18)
#define HWIO_CALIBRATION0_OFFS                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b18)
#define HWIO_CALIBRATION0_RMSK                                                                             0xffffffff
#define HWIO_CALIBRATION0_IN          \
        in_dword(HWIO_CALIBRATION0_ADDR)
#define HWIO_CALIBRATION0_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION0_ADDR, m)
#define HWIO_CALIBRATION0_USB2PHY_RCAL_CODE_0_BMSK                                                         0x80000000
#define HWIO_CALIBRATION0_USB2PHY_RCAL_CODE_0_SHFT                                                               0x1f
#define HWIO_CALIBRATION0_CALIBRATION_30_16_BMSK                                                           0x7fff0000
#define HWIO_CALIBRATION0_CALIBRATION_30_16_SHFT                                                                 0x10
#define HWIO_CALIBRATION0_REFGEN_0_NORTH_BGV_TRIM_BMSK                                                         0xff00
#define HWIO_CALIBRATION0_REFGEN_0_NORTH_BGV_TRIM_SHFT                                                            0x8
#define HWIO_CALIBRATION0_REFGEN1_SOUTH_BGV_TRIM_BMSK                                                            0xff
#define HWIO_CALIBRATION0_REFGEN1_SOUTH_BGV_TRIM_SHFT                                                             0x0

#define HWIO_CALIBRATION1_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b1c)
#define HWIO_CALIBRATION1_OFFS                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b1c)
#define HWIO_CALIBRATION1_RMSK                                                                             0xffffffff
#define HWIO_CALIBRATION1_IN          \
        in_dword(HWIO_CALIBRATION1_ADDR)
#define HWIO_CALIBRATION1_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION1_ADDR, m)
#define HWIO_CALIBRATION1_CALIBRATION_63_44_BMSK                                                           0xfffff000
#define HWIO_CALIBRATION1_CALIBRATION_63_44_SHFT                                                                  0xc
#define HWIO_CALIBRATION1_APSS_CS_ADC_VREFP_CTRL_IN_BMSK                                                        0xf00
#define HWIO_CALIBRATION1_APSS_CS_ADC_VREFP_CTRL_IN_SHFT                                                          0x8
#define HWIO_CALIBRATION1_CALIBATION_39_35_BMSK                                                                  0xf8
#define HWIO_CALIBRATION1_CALIBATION_39_35_SHFT                                                                   0x3
#define HWIO_CALIBRATION1_USB2PHY_RCAL_CODE_3_1_BMSK                                                              0x7
#define HWIO_CALIBRATION1_USB2PHY_RCAL_CODE_3_1_SHFT                                                              0x0

#define HWIO_CALIBRATION2_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b20)
#define HWIO_CALIBRATION2_OFFS                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b20)
#define HWIO_CALIBRATION2_RMSK                                                                             0xffffffff
#define HWIO_CALIBRATION2_IN          \
        in_dword(HWIO_CALIBRATION2_ADDR)
#define HWIO_CALIBRATION2_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION2_ADDR, m)
#define HWIO_CALIBRATION2_CALIBRATION_95_64_BMSK                                                           0xffffffff
#define HWIO_CALIBRATION2_CALIBRATION_95_64_SHFT                                                                  0x0

#define HWIO_CALIBRATION3_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b24)
#define HWIO_CALIBRATION3_OFFS                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b24)
#define HWIO_CALIBRATION3_RMSK                                                                             0xffffffff
#define HWIO_CALIBRATION3_IN          \
        in_dword(HWIO_CALIBRATION3_ADDR)
#define HWIO_CALIBRATION3_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION3_ADDR, m)
#define HWIO_CALIBRATION3_CALIBRATION_127_96_BMSK                                                          0xffffffff
#define HWIO_CALIBRATION3_CALIBRATION_127_96_SHFT                                                                 0x0

#define HWIO_CALIBRATION4_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b28)
#define HWIO_CALIBRATION4_OFFS                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b28)
#define HWIO_CALIBRATION4_RMSK                                                                             0xffffffff
#define HWIO_CALIBRATION4_IN          \
        in_dword(HWIO_CALIBRATION4_ADDR)
#define HWIO_CALIBRATION4_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION4_ADDR, m)
#define HWIO_CALIBRATION4_DDRSS_CH3DQ0_PNTUNE_HT_BMSK                                                      0xc0000000
#define HWIO_CALIBRATION4_DDRSS_CH3DQ0_PNTUNE_HT_SHFT                                                            0x1e
#define HWIO_CALIBRATION4_DDRSS_CH3CA_PNTUNE_HT_BMSK                                                       0x30000000
#define HWIO_CALIBRATION4_DDRSS_CH3CA_PNTUNE_HT_SHFT                                                             0x1c
#define HWIO_CALIBRATION4_DDRSS_CH2DQ1_PNTUNE_HT_BMSK                                                       0xc000000
#define HWIO_CALIBRATION4_DDRSS_CH2DQ1_PNTUNE_HT_SHFT                                                            0x1a
#define HWIO_CALIBRATION4_DDRSS_CH2DQ0_PNTUNE_HT_BMSK                                                       0x3000000
#define HWIO_CALIBRATION4_DDRSS_CH2DQ0_PNTUNE_HT_SHFT                                                            0x18
#define HWIO_CALIBRATION4_CPR0_TARG_VOLT_SVS2_BMSK                                                           0xfc0000
#define HWIO_CALIBRATION4_CPR0_TARG_VOLT_SVS2_SHFT                                                               0x12
#define HWIO_CALIBRATION4_CPR0_TARG_VOLT_SVS_BMSK                                                             0x3f000
#define HWIO_CALIBRATION4_CPR0_TARG_VOLT_SVS_SHFT                                                                 0xc
#define HWIO_CALIBRATION4_CPR0_TARG_VOLT_NOM_BMSK                                                               0xfc0
#define HWIO_CALIBRATION4_CPR0_TARG_VOLT_NOM_SHFT                                                                 0x6
#define HWIO_CALIBRATION4_CPR0_TARG_VOLT_TURL1_BMSK                                                              0x3f
#define HWIO_CALIBRATION4_CPR0_TARG_VOLT_TURL1_SHFT                                                               0x0

#define HWIO_CALIBRATION5_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b2c)
#define HWIO_CALIBRATION5_OFFS                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b2c)
#define HWIO_CALIBRATION5_RMSK                                                                             0xffffffff
#define HWIO_CALIBRATION5_IN          \
        in_dword(HWIO_CALIBRATION5_ADDR)
#define HWIO_CALIBRATION5_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION5_ADDR, m)
#define HWIO_CALIBRATION5_CALIBRATION_191_187_BMSK                                                         0xf8000000
#define HWIO_CALIBRATION5_CALIBRATION_191_187_SHFT                                                               0x1b
#define HWIO_CALIBRATION5_CPR11_BOOST_QUOT_MIN_BMSK                                                         0x7ff8000
#define HWIO_CALIBRATION5_CPR11_BOOST_QUOT_MIN_SHFT                                                               0xf
#define HWIO_CALIBRATION5_CPR11_TARG_VOLT_BOOST_BMSK                                                           0x7e00
#define HWIO_CALIBRATION5_CPR11_TARG_VOLT_BOOST_SHFT                                                              0x9
#define HWIO_CALIBRATION5_DDRSS_EW_FUSE_2_BMSK                                                                  0x1fc
#define HWIO_CALIBRATION5_DDRSS_EW_FUSE_2_SHFT                                                                    0x2
#define HWIO_CALIBRATION5_DDRSS_CH3DQ1_PNTUNE_HT_BMSK                                                             0x3
#define HWIO_CALIBRATION5_DDRSS_CH3DQ1_PNTUNE_HT_SHFT                                                             0x0

#define HWIO_CALIBRATION6_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b30)
#define HWIO_CALIBRATION6_OFFS                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b30)
#define HWIO_CALIBRATION6_RMSK                                                                             0xffffffff
#define HWIO_CALIBRATION6_IN          \
        in_dword(HWIO_CALIBRATION6_ADDR)
#define HWIO_CALIBRATION6_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION6_ADDR, m)
#define HWIO_CALIBRATION6_CALIBRATION_223_192_BMSK                                                         0xffffffff
#define HWIO_CALIBRATION6_CALIBRATION_223_192_SHFT                                                                0x0

#define HWIO_CALIBRATION7_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b34)
#define HWIO_CALIBRATION7_OFFS                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b34)
#define HWIO_CALIBRATION7_RMSK                                                                             0xffffffff
#define HWIO_CALIBRATION7_IN          \
        in_dword(HWIO_CALIBRATION7_ADDR)
#define HWIO_CALIBRATION7_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION7_ADDR, m)
#define HWIO_CALIBRATION7_CALIBRATION_255_224_BMSK                                                         0xffffffff
#define HWIO_CALIBRATION7_CALIBRATION_255_224_SHFT                                                                0x0

#define HWIO_CALIBRATION8_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b38)
#define HWIO_CALIBRATION8_OFFS                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b38)
#define HWIO_CALIBRATION8_RMSK                                                                             0xffffffff
#define HWIO_CALIBRATION8_IN          \
        in_dword(HWIO_CALIBRATION8_ADDR)
#define HWIO_CALIBRATION8_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION8_ADDR, m)
#define HWIO_CALIBRATION8_CALIBRATION_287_286_BMSK                                                         0xc0000000
#define HWIO_CALIBRATION8_CALIBRATION_287_286_SHFT                                                               0x1e
#define HWIO_CALIBRATION8_ACC_HV_MXA_BMSK                                                                  0x3f000000
#define HWIO_CALIBRATION8_ACC_HV_MXA_SHFT                                                                        0x18
#define HWIO_CALIBRATION8_ACC_HV_MXC_BMSK                                                                    0xfc0000
#define HWIO_CALIBRATION8_ACC_HV_MXC_SHFT                                                                        0x12
#define HWIO_CALIBRATION8_CALIBRATION_273_256_BMSK                                                            0x3ffff
#define HWIO_CALIBRATION8_CALIBRATION_273_256_SHFT                                                                0x0

#define HWIO_CALIBRATION9_ADDR                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b3c)
#define HWIO_CALIBRATION9_OFFS                                                                             (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b3c)
#define HWIO_CALIBRATION9_RMSK                                                                             0xffffffff
#define HWIO_CALIBRATION9_IN          \
        in_dword(HWIO_CALIBRATION9_ADDR)
#define HWIO_CALIBRATION9_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION9_ADDR, m)
#define HWIO_CALIBRATION9_CPR0_TARG_VOLT_OFFSET_NOM_BMSK                                                   0xf8000000
#define HWIO_CALIBRATION9_CPR0_TARG_VOLT_OFFSET_NOM_SHFT                                                         0x1b
#define HWIO_CALIBRATION9_CPR0_TARG_VOLT_OFFSET_NOML1_BMSK                                                  0x7c00000
#define HWIO_CALIBRATION9_CPR0_TARG_VOLT_OFFSET_NOML1_SHFT                                                       0x16
#define HWIO_CALIBRATION9_CPR0_TARG_VOLT_OFFSET_TUR_BMSK                                                     0x3e0000
#define HWIO_CALIBRATION9_CPR0_TARG_VOLT_OFFSET_TUR_SHFT                                                         0x11
#define HWIO_CALIBRATION9_CPR0_TARG_VOLT_OFFSET_TURL1_BMSK                                                    0x1f000
#define HWIO_CALIBRATION9_CPR0_TARG_VOLT_OFFSET_TURL1_SHFT                                                        0xc
#define HWIO_CALIBRATION9_ACC_LV_MXC_BMSK                                                                       0xfc0
#define HWIO_CALIBRATION9_ACC_LV_MXC_SHFT                                                                         0x6
#define HWIO_CALIBRATION9_ACC_LV_MXA_BMSK                                                                        0x3f
#define HWIO_CALIBRATION9_ACC_LV_MXA_SHFT                                                                         0x0

#define HWIO_CALIBRATION10_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b40)
#define HWIO_CALIBRATION10_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b40)
#define HWIO_CALIBRATION10_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION10_IN          \
        in_dword(HWIO_CALIBRATION10_ADDR)
#define HWIO_CALIBRATION10_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION10_ADDR, m)
#define HWIO_CALIBRATION10_VSENSE_FUSE1_S5_BMSK                                                            0xf0000000
#define HWIO_CALIBRATION10_VSENSE_FUSE1_S5_SHFT                                                                  0x1c
#define HWIO_CALIBRATION10_VSENSE_FUSE1_S4_BMSK                                                             0xf000000
#define HWIO_CALIBRATION10_VSENSE_FUSE1_S4_SHFT                                                                  0x18
#define HWIO_CALIBRATION10_VSENSE_FUSE1_S3_BMSK                                                              0xf00000
#define HWIO_CALIBRATION10_VSENSE_FUSE1_S3_SHFT                                                                  0x14
#define HWIO_CALIBRATION10_VSENSE_FUSE1_S2_BMSK                                                               0xf0000
#define HWIO_CALIBRATION10_VSENSE_FUSE1_S2_SHFT                                                                  0x10
#define HWIO_CALIBRATION10_VSENSE_FUSE1_S1_BMSK                                                                0xf000
#define HWIO_CALIBRATION10_VSENSE_FUSE1_S1_SHFT                                                                   0xc
#define HWIO_CALIBRATION10_VSENSE_FUSE1_S0_BMSK                                                                 0xf00
#define HWIO_CALIBRATION10_VSENSE_FUSE1_S0_SHFT                                                                   0x8
#define HWIO_CALIBRATION10_VSENSE_FUSE1_BMSK                                                                     0xff
#define HWIO_CALIBRATION10_VSENSE_FUSE1_SHFT                                                                      0x0

#define HWIO_CALIBRATION11_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b44)
#define HWIO_CALIBRATION11_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b44)
#define HWIO_CALIBRATION11_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION11_IN          \
        in_dword(HWIO_CALIBRATION11_ADDR)
#define HWIO_CALIBRATION11_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION11_ADDR, m)
#define HWIO_CALIBRATION11_VSENSE_FUSE2_S2_BMSK                                                            0xf0000000
#define HWIO_CALIBRATION11_VSENSE_FUSE2_S2_SHFT                                                                  0x1c
#define HWIO_CALIBRATION11_VSENSE_FUSE2_S1_BMSK                                                             0xf000000
#define HWIO_CALIBRATION11_VSENSE_FUSE2_S1_SHFT                                                                  0x18
#define HWIO_CALIBRATION11_VSENSE_FUSE2_S0_BMSK                                                              0xf00000
#define HWIO_CALIBRATION11_VSENSE_FUSE2_S0_SHFT                                                                  0x14
#define HWIO_CALIBRATION11_VSENSE_FUSE2_BMSK                                                                  0xff000
#define HWIO_CALIBRATION11_VSENSE_FUSE2_SHFT                                                                      0xc
#define HWIO_CALIBRATION11_VSENSE_FUSE1_S8_BMSK                                                                 0xf00
#define HWIO_CALIBRATION11_VSENSE_FUSE1_S8_SHFT                                                                   0x8
#define HWIO_CALIBRATION11_VSENSE_FUSE1_S7_BMSK                                                                  0xf0
#define HWIO_CALIBRATION11_VSENSE_FUSE1_S7_SHFT                                                                   0x4
#define HWIO_CALIBRATION11_VSENSE_FUSE1_S6_BMSK                                                                   0xf
#define HWIO_CALIBRATION11_VSENSE_FUSE1_S6_SHFT                                                                   0x0

#define HWIO_CALIBRATION12_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b48)
#define HWIO_CALIBRATION12_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b48)
#define HWIO_CALIBRATION12_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION12_IN          \
        in_dword(HWIO_CALIBRATION12_ADDR)
#define HWIO_CALIBRATION12_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION12_ADDR, m)
#define HWIO_CALIBRATION12_CPR0_TARG_VOLT_OFFSET_SVSL1_BMSK                                                0xf8000000
#define HWIO_CALIBRATION12_CPR0_TARG_VOLT_OFFSET_SVSL1_SHFT                                                      0x1b
#define HWIO_CALIBRATION12_VSENSE_FUSE_REVISION_CONTROL_BMSK                                                0x7000000
#define HWIO_CALIBRATION12_VSENSE_FUSE_REVISION_CONTROL_SHFT                                                     0x18
#define HWIO_CALIBRATION12_VSENSE_FUSE2_S8_BMSK                                                              0xf00000
#define HWIO_CALIBRATION12_VSENSE_FUSE2_S8_SHFT                                                                  0x14
#define HWIO_CALIBRATION12_VSENSE_FUSE2_S7_BMSK                                                               0xf0000
#define HWIO_CALIBRATION12_VSENSE_FUSE2_S7_SHFT                                                                  0x10
#define HWIO_CALIBRATION12_VSENSE_FUSE2_S6_BMSK                                                                0xf000
#define HWIO_CALIBRATION12_VSENSE_FUSE2_S6_SHFT                                                                   0xc
#define HWIO_CALIBRATION12_VSENSE_FUSE2_S5_BMSK                                                                 0xf00
#define HWIO_CALIBRATION12_VSENSE_FUSE2_S5_SHFT                                                                   0x8
#define HWIO_CALIBRATION12_VSENSE_FUSE2_S4_BMSK                                                                  0xf0
#define HWIO_CALIBRATION12_VSENSE_FUSE2_S4_SHFT                                                                   0x4
#define HWIO_CALIBRATION12_VSENSE_FUSE2_S3_BMSK                                                                   0xf
#define HWIO_CALIBRATION12_VSENSE_FUSE2_S3_SHFT                                                                   0x0

#define HWIO_CALIBRATION13_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b4c)
#define HWIO_CALIBRATION13_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b4c)
#define HWIO_CALIBRATION13_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION13_IN          \
        in_dword(HWIO_CALIBRATION13_ADDR)
#define HWIO_CALIBRATION13_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION13_ADDR, m)
#define HWIO_CALIBRATION13_CPR1_AGING_BMSK                                                                 0xff000000
#define HWIO_CALIBRATION13_CPR1_AGING_SHFT                                                                       0x18
#define HWIO_CALIBRATION13_CPR1_TARG_VOLT_NOML1_BMSK                                                         0xfc0000
#define HWIO_CALIBRATION13_CPR1_TARG_VOLT_NOML1_SHFT                                                             0x12
#define HWIO_CALIBRATION13_CPR0_AGING_BMSK                                                                    0x3fc00
#define HWIO_CALIBRATION13_CPR0_AGING_SHFT                                                                        0xa
#define HWIO_CALIBRATION13_CPR0_TARG_VOLT_OFFSET_SVS2_BMSK                                                      0x3e0
#define HWIO_CALIBRATION13_CPR0_TARG_VOLT_OFFSET_SVS2_SHFT                                                        0x5
#define HWIO_CALIBRATION13_CPR0_TARG_VOLT_OFFSET_SVS_BMSK                                                        0x1f
#define HWIO_CALIBRATION13_CPR0_TARG_VOLT_OFFSET_SVS_SHFT                                                         0x0

#define HWIO_CALIBRATION14_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b50)
#define HWIO_CALIBRATION14_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b50)
#define HWIO_CALIBRATION14_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION14_IN          \
        in_dword(HWIO_CALIBRATION14_ADDR)
#define HWIO_CALIBRATION14_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION14_ADDR, m)
#define HWIO_CALIBRATION14_CPR1_TARG_VOLT_OFFSET_SVS_BMSK                                                  0xf8000000
#define HWIO_CALIBRATION14_CPR1_TARG_VOLT_OFFSET_SVS_SHFT                                                        0x1b
#define HWIO_CALIBRATION14_CPR1_TARG_VOLT_OFFSET_SVSL1_BMSK                                                 0x7c00000
#define HWIO_CALIBRATION14_CPR1_TARG_VOLT_OFFSET_SVSL1_SHFT                                                      0x16
#define HWIO_CALIBRATION14_CPR1_TARG_VOLT_OFFSET_NOM_BMSK                                                    0x3e0000
#define HWIO_CALIBRATION14_CPR1_TARG_VOLT_OFFSET_NOM_SHFT                                                        0x11
#define HWIO_CALIBRATION14_CPR1_TARG_VOLT_OFFSET_NOML1_BMSK                                                   0x1f000
#define HWIO_CALIBRATION14_CPR1_TARG_VOLT_OFFSET_NOML1_SHFT                                                       0xc
#define HWIO_CALIBRATION14_CPR1_TARG_VOLT_SVS_BMSK                                                              0xfc0
#define HWIO_CALIBRATION14_CPR1_TARG_VOLT_SVS_SHFT                                                                0x6
#define HWIO_CALIBRATION14_CPR1_TARG_VOLT_NOM_BMSK                                                               0x3f
#define HWIO_CALIBRATION14_CPR1_TARG_VOLT_NOM_SHFT                                                                0x0

#define HWIO_CALIBRATION15_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b54)
#define HWIO_CALIBRATION15_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b54)
#define HWIO_CALIBRATION15_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION15_IN          \
        in_dword(HWIO_CALIBRATION15_ADDR)
#define HWIO_CALIBRATION15_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION15_ADDR, m)
#define HWIO_CALIBRATION15_CPR2_TARG_VOLT_OFFSET_TURL2_BMSK                                                0xf8000000
#define HWIO_CALIBRATION15_CPR2_TARG_VOLT_OFFSET_TURL2_SHFT                                                      0x1b
#define HWIO_CALIBRATION15_CPR2_TARG_VOLT_OFFSET_TURL3_BMSK                                                 0x7c00000
#define HWIO_CALIBRATION15_CPR2_TARG_VOLT_OFFSET_TURL3_SHFT                                                      0x16
#define HWIO_CALIBRATION15_CPR2_TARG_VOLT_TURL1_BMSK                                                         0x3f0000
#define HWIO_CALIBRATION15_CPR2_TARG_VOLT_TURL1_SHFT                                                             0x10
#define HWIO_CALIBRATION15_CPR1_TARG_VOLT_SVS3_BMSK                                                            0xfc00
#define HWIO_CALIBRATION15_CPR1_TARG_VOLT_SVS3_SHFT                                                               0xa
#define HWIO_CALIBRATION15_CPR1_TARG_VOLT_OFFSET_SVS3_BMSK                                                      0x3e0
#define HWIO_CALIBRATION15_CPR1_TARG_VOLT_OFFSET_SVS3_SHFT                                                        0x5
#define HWIO_CALIBRATION15_CPR1_TARG_VOLT_OFFSET_SVS2_BMSK                                                       0x1f
#define HWIO_CALIBRATION15_CPR1_TARG_VOLT_OFFSET_SVS2_SHFT                                                        0x0

#define HWIO_CALIBRATION16_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b58)
#define HWIO_CALIBRATION16_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b58)
#define HWIO_CALIBRATION16_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION16_IN          \
        in_dword(HWIO_CALIBRATION16_ADDR)
#define HWIO_CALIBRATION16_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION16_ADDR, m)
#define HWIO_CALIBRATION16_CPR2_TARG_VOLT_SVS_BMSK                                                         0xfc000000
#define HWIO_CALIBRATION16_CPR2_TARG_VOLT_SVS_SHFT                                                               0x1a
#define HWIO_CALIBRATION16_CPR2_TARG_VOLT_SVSL2_BMSK                                                        0x3f00000
#define HWIO_CALIBRATION16_CPR2_TARG_VOLT_SVSL2_SHFT                                                             0x14
#define HWIO_CALIBRATION16_CPR2_TARG_VOLT_OFFSET_NOM_BMSK                                                     0xf8000
#define HWIO_CALIBRATION16_CPR2_TARG_VOLT_OFFSET_NOM_SHFT                                                         0xf
#define HWIO_CALIBRATION16_CPR2_TARG_VOLT_OFFSET_NOML1_BMSK                                                    0x7c00
#define HWIO_CALIBRATION16_CPR2_TARG_VOLT_OFFSET_NOML1_SHFT                                                       0xa
#define HWIO_CALIBRATION16_CPR2_TARG_VOLT_OFFSET_TUR_BMSK                                                       0x3e0
#define HWIO_CALIBRATION16_CPR2_TARG_VOLT_OFFSET_TUR_SHFT                                                         0x5
#define HWIO_CALIBRATION16_CPR2_TARG_VOLT_OFFSET_TURL1_BMSK                                                      0x1f
#define HWIO_CALIBRATION16_CPR2_TARG_VOLT_OFFSET_TURL1_SHFT                                                       0x0

#define HWIO_CALIBRATION17_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b5c)
#define HWIO_CALIBRATION17_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b5c)
#define HWIO_CALIBRATION17_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION17_IN          \
        in_dword(HWIO_CALIBRATION17_ADDR)
#define HWIO_CALIBRATION17_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION17_ADDR, m)
#define HWIO_CALIBRATION17_CPR2_TARG_VOLT_OFFSET_SVS_BMSK                                                  0xf8000000
#define HWIO_CALIBRATION17_CPR2_TARG_VOLT_OFFSET_SVS_SHFT                                                        0x1b
#define HWIO_CALIBRATION17_CPR2_TARG_VOLT_OFFSET_SVSL0_BMSK                                                 0x7c00000
#define HWIO_CALIBRATION17_CPR2_TARG_VOLT_OFFSET_SVSL0_SHFT                                                      0x16
#define HWIO_CALIBRATION17_CPR2_TARG_VOLT_OFFSET_SVSL1_BMSK                                                  0x3e0000
#define HWIO_CALIBRATION17_CPR2_TARG_VOLT_OFFSET_SVSL1_SHFT                                                      0x11
#define HWIO_CALIBRATION17_CPR2_TARG_VOLT_OFFSET_SVSL2_BMSK                                                   0x1f000
#define HWIO_CALIBRATION17_CPR2_TARG_VOLT_OFFSET_SVSL2_SHFT                                                       0xc
#define HWIO_CALIBRATION17_CPR2_TARG_VOLT_SVS3_BMSK                                                             0xfc0
#define HWIO_CALIBRATION17_CPR2_TARG_VOLT_SVS3_SHFT                                                               0x6
#define HWIO_CALIBRATION17_CPR2_TARG_VOLT_SVS2_BMSK                                                              0x3f
#define HWIO_CALIBRATION17_CPR2_TARG_VOLT_SVS2_SHFT                                                               0x0

#define HWIO_CALIBRATION18_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b60)
#define HWIO_CALIBRATION18_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b60)
#define HWIO_CALIBRATION18_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION18_IN          \
        in_dword(HWIO_CALIBRATION18_ADDR)
#define HWIO_CALIBRATION18_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION18_ADDR, m)
#define HWIO_CALIBRATION18_CPR4_TARG_VOLT_TURL1_BMSK                                                       0xfc000000
#define HWIO_CALIBRATION18_CPR4_TARG_VOLT_TURL1_SHFT                                                             0x1a
#define HWIO_CALIBRATION18_CPR3_TARG_VOLT_SVS_BMSK                                                          0x3f00000
#define HWIO_CALIBRATION18_CPR3_TARG_VOLT_SVS_SHFT                                                               0x14
#define HWIO_CALIBRATION18_CPR3_TARG_VOLT_NOM_BMSK                                                            0xfc000
#define HWIO_CALIBRATION18_CPR3_TARG_VOLT_NOM_SHFT                                                                0xe
#define HWIO_CALIBRATION18_CPR3_TARG_VOLT_TUR_BMSK                                                             0x3f00
#define HWIO_CALIBRATION18_CPR3_TARG_VOLT_TUR_SHFT                                                                0x8
#define HWIO_CALIBRATION18_CPR2_AGING_BMSK                                                                       0xff
#define HWIO_CALIBRATION18_CPR2_AGING_SHFT                                                                        0x0

#define HWIO_CALIBRATION19_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b64)
#define HWIO_CALIBRATION19_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b64)
#define HWIO_CALIBRATION19_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION19_IN          \
        in_dword(HWIO_CALIBRATION19_ADDR)
#define HWIO_CALIBRATION19_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION19_ADDR, m)
#define HWIO_CALIBRATION19_CPR4_TARG_VOLT_NOM_BMSK                                                         0xfc000000
#define HWIO_CALIBRATION19_CPR4_TARG_VOLT_NOM_SHFT                                                               0x1a
#define HWIO_CALIBRATION19_CPR4_TARG_VOLT_TUR_BMSK                                                          0x3f00000
#define HWIO_CALIBRATION19_CPR4_TARG_VOLT_TUR_SHFT                                                               0x14
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_LSVSD2_BMSK                                                  0xf8000
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_LSVSD2_SHFT                                                      0xf
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_SVS3_BMSK                                                     0x7c00
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_SVS3_SHFT                                                        0xa
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_LSVSD0_BMSK                                                    0x3e0
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_LSVSD0_SHFT                                                      0x5
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_SVS2_BMSK                                                       0x1f
#define HWIO_CALIBRATION19_CPR2_TARG_VOLT_OFFSET_SVS2_SHFT                                                        0x0

#define HWIO_CALIBRATION20_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b68)
#define HWIO_CALIBRATION20_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b68)
#define HWIO_CALIBRATION20_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION20_IN          \
        in_dword(HWIO_CALIBRATION20_ADDR)
#define HWIO_CALIBRATION20_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION20_ADDR, m)
#define HWIO_CALIBRATION20_CPR4_TARG_VOLT_OFFSET_NOM_BMSK                                                  0xf8000000
#define HWIO_CALIBRATION20_CPR4_TARG_VOLT_OFFSET_NOM_SHFT                                                        0x1b
#define HWIO_CALIBRATION20_CPR4_TARG_VOLT_OFFSET_NOML1_BMSK                                                 0x7c00000
#define HWIO_CALIBRATION20_CPR4_TARG_VOLT_OFFSET_NOML1_SHFT                                                      0x16
#define HWIO_CALIBRATION20_CPR4_TARG_VOLT_OFFSET_TUR_BMSK                                                    0x3e0000
#define HWIO_CALIBRATION20_CPR4_TARG_VOLT_OFFSET_TUR_SHFT                                                        0x11
#define HWIO_CALIBRATION20_CPR4_TARG_VOLT_OFFSET_TURL1_BMSK                                                   0x1f000
#define HWIO_CALIBRATION20_CPR4_TARG_VOLT_OFFSET_TURL1_SHFT                                                       0xc
#define HWIO_CALIBRATION20_CPR5_TARG_VOLT_TURL1_BMSK                                                            0xfc0
#define HWIO_CALIBRATION20_CPR5_TARG_VOLT_TURL1_SHFT                                                              0x6
#define HWIO_CALIBRATION20_CPR4_TARG_VOLT_SVS_BMSK                                                               0x3f
#define HWIO_CALIBRATION20_CPR4_TARG_VOLT_SVS_SHFT                                                                0x0

#define HWIO_CALIBRATION21_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b6c)
#define HWIO_CALIBRATION21_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b6c)
#define HWIO_CALIBRATION21_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION21_IN          \
        in_dword(HWIO_CALIBRATION21_ADDR)
#define HWIO_CALIBRATION21_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION21_ADDR, m)
#define HWIO_CALIBRATION21_CPR5_TARG_VOLT_NOM_BMSK                                                         0xfc000000
#define HWIO_CALIBRATION21_CPR5_TARG_VOLT_NOM_SHFT                                                               0x1a
#define HWIO_CALIBRATION21_CPR5_TARG_VOLT_TUR_BMSK                                                          0x3f00000
#define HWIO_CALIBRATION21_CPR5_TARG_VOLT_TUR_SHFT                                                               0x14
#define HWIO_CALIBRATION21_CPR5_TARG_VOLT_OFFSET_TURL1_BMSK                                                   0xf8000
#define HWIO_CALIBRATION21_CPR5_TARG_VOLT_OFFSET_TURL1_SHFT                                                       0xf
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_OFFSET_SVS2_BMSK                                                     0x7c00
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_OFFSET_SVS2_SHFT                                                        0xa
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_OFFSET_SVS_BMSK                                                       0x3e0
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_OFFSET_SVS_SHFT                                                         0x5
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_OFFSET_SVSL1_BMSK                                                      0x1f
#define HWIO_CALIBRATION21_CPR4_TARG_VOLT_OFFSET_SVSL1_SHFT                                                       0x0

#define HWIO_CALIBRATION22_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b70)
#define HWIO_CALIBRATION22_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b70)
#define HWIO_CALIBRATION22_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION22_IN          \
        in_dword(HWIO_CALIBRATION22_ADDR)
#define HWIO_CALIBRATION22_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION22_ADDR, m)
#define HWIO_CALIBRATION22_CPR5_TARG_VOLT_OFFSET_SVSL1_BMSK                                                0xf8000000
#define HWIO_CALIBRATION22_CPR5_TARG_VOLT_OFFSET_SVSL1_SHFT                                                      0x1b
#define HWIO_CALIBRATION22_CPR5_TARG_VOLT_OFFSET_NOM_BMSK                                                   0x7c00000
#define HWIO_CALIBRATION22_CPR5_TARG_VOLT_OFFSET_NOM_SHFT                                                        0x16
#define HWIO_CALIBRATION22_CPR5_TARG_VOLT_OFFSET_NOML1_BMSK                                                  0x3e0000
#define HWIO_CALIBRATION22_CPR5_TARG_VOLT_OFFSET_NOML1_SHFT                                                      0x11
#define HWIO_CALIBRATION22_CPR5_TARG_VOLT_OFFSET_TUR_BMSK                                                     0x1f000
#define HWIO_CALIBRATION22_CPR5_TARG_VOLT_OFFSET_TUR_SHFT                                                         0xc
#define HWIO_CALIBRATION22_CPR6_TARG_VOLT_TUR_BMSK                                                              0xfc0
#define HWIO_CALIBRATION22_CPR6_TARG_VOLT_TUR_SHFT                                                                0x6
#define HWIO_CALIBRATION22_CPR5_TARG_VOLT_SVS_BMSK                                                               0x3f
#define HWIO_CALIBRATION22_CPR5_TARG_VOLT_SVS_SHFT                                                                0x0

#define HWIO_CALIBRATION23_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b74)
#define HWIO_CALIBRATION23_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b74)
#define HWIO_CALIBRATION23_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION23_IN          \
        in_dword(HWIO_CALIBRATION23_ADDR)
#define HWIO_CALIBRATION23_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION23_ADDR, m)
#define HWIO_CALIBRATION23_CPR7_TARG_VOLT_TUR_BMSK                                                         0xfc000000
#define HWIO_CALIBRATION23_CPR7_TARG_VOLT_TUR_SHFT                                                               0x1a
#define HWIO_CALIBRATION23_CPR6_TARG_VOLT_NOM_BMSK                                                          0x3f00000
#define HWIO_CALIBRATION23_CPR6_TARG_VOLT_NOM_SHFT                                                               0x14
#define HWIO_CALIBRATION23_CPR7_TARG_VOLT_OFFSET_NOM_BMSK                                                     0xf8000
#define HWIO_CALIBRATION23_CPR7_TARG_VOLT_OFFSET_NOM_SHFT                                                         0xf
#define HWIO_CALIBRATION23_CPR7_TARG_VOLT_OFFSET_TUR_BMSK                                                      0x7c00
#define HWIO_CALIBRATION23_CPR7_TARG_VOLT_OFFSET_TUR_SHFT                                                         0xa
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_OFFSET_SVS2_BMSK                                                      0x3e0
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_OFFSET_SVS2_SHFT                                                        0x5
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_OFFSET_SVS_BMSK                                                        0x1f
#define HWIO_CALIBRATION23_CPR5_TARG_VOLT_OFFSET_SVS_SHFT                                                         0x0

#define HWIO_CALIBRATION24_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b78)
#define HWIO_CALIBRATION24_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b78)
#define HWIO_CALIBRATION24_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION24_IN          \
        in_dword(HWIO_CALIBRATION24_ADDR)
#define HWIO_CALIBRATION24_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION24_ADDR, m)
#define HWIO_CALIBRATION24_CPR7_TARG_VOLT_OFFSET_SVS3_BMSK                                                 0xf8000000
#define HWIO_CALIBRATION24_CPR7_TARG_VOLT_OFFSET_SVS3_SHFT                                                       0x1b
#define HWIO_CALIBRATION24_CPR7_TARG_VOLT_OFFSET_SVS2_BMSK                                                  0x7c00000
#define HWIO_CALIBRATION24_CPR7_TARG_VOLT_OFFSET_SVS2_SHFT                                                       0x16
#define HWIO_CALIBRATION24_CPR7_TARG_VOLT_OFFSET_SVS_BMSK                                                    0x3e0000
#define HWIO_CALIBRATION24_CPR7_TARG_VOLT_OFFSET_SVS_SHFT                                                        0x11
#define HWIO_CALIBRATION24_CPR7_TARG_VOLT_OFFSET_SVSL1_BMSK                                                   0x1f000
#define HWIO_CALIBRATION24_CPR7_TARG_VOLT_OFFSET_SVSL1_SHFT                                                       0xc
#define HWIO_CALIBRATION24_CPR7_TARG_VOLT_SVS_BMSK                                                              0xfc0
#define HWIO_CALIBRATION24_CPR7_TARG_VOLT_SVS_SHFT                                                                0x6
#define HWIO_CALIBRATION24_CPR7_TARG_VOLT_NOM_BMSK                                                               0x3f
#define HWIO_CALIBRATION24_CPR7_TARG_VOLT_NOM_SHFT                                                                0x0

#define HWIO_CALIBRATION25_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b7c)
#define HWIO_CALIBRATION25_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b7c)
#define HWIO_CALIBRATION25_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION25_IN          \
        in_dword(HWIO_CALIBRATION25_ADDR)
#define HWIO_CALIBRATION25_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION25_ADDR, m)
#define HWIO_CALIBRATION25_CPR8_TARG_VOLT_SVS_BMSK                                                         0xfc000000
#define HWIO_CALIBRATION25_CPR8_TARG_VOLT_SVS_SHFT                                                               0x1a
#define HWIO_CALIBRATION25_CPR8_TARG_VOLT_NOM_BMSK                                                          0x3f00000
#define HWIO_CALIBRATION25_CPR8_TARG_VOLT_NOM_SHFT                                                               0x14
#define HWIO_CALIBRATION25_CPR8_TARG_VOLT_TUR_BMSK                                                            0xfc000
#define HWIO_CALIBRATION25_CPR8_TARG_VOLT_TUR_SHFT                                                                0xe
#define HWIO_CALIBRATION25_CPR7_AGING_BMSK                                                                     0x3fc0
#define HWIO_CALIBRATION25_CPR7_AGING_SHFT                                                                        0x6
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_SVS3_BMSK                                                              0x3f
#define HWIO_CALIBRATION25_CPR7_TARG_VOLT_SVS3_SHFT                                                               0x0

#define HWIO_CALIBRATION26_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b80)
#define HWIO_CALIBRATION26_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b80)
#define HWIO_CALIBRATION26_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION26_IN          \
        in_dword(HWIO_CALIBRATION26_ADDR)
#define HWIO_CALIBRATION26_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION26_ADDR, m)
#define HWIO_CALIBRATION26_CPR8_TARG_VOLT_OFFSET_SVSL1_BMSK                                                0xf8000000
#define HWIO_CALIBRATION26_CPR8_TARG_VOLT_OFFSET_SVSL1_SHFT                                                      0x1b
#define HWIO_CALIBRATION26_CPR8_TARG_VOLT_OFFSET_NOM_BMSK                                                   0x7c00000
#define HWIO_CALIBRATION26_CPR8_TARG_VOLT_OFFSET_NOM_SHFT                                                        0x16
#define HWIO_CALIBRATION26_CPR8_TARG_VOLT_OFFSET_NOML1_BMSK                                                  0x3e0000
#define HWIO_CALIBRATION26_CPR8_TARG_VOLT_OFFSET_NOML1_SHFT                                                      0x11
#define HWIO_CALIBRATION26_CPR8_TARG_VOLT_OFFSET_TUR_BMSK                                                     0x1f000
#define HWIO_CALIBRATION26_CPR8_TARG_VOLT_OFFSET_TUR_SHFT                                                         0xc
#define HWIO_CALIBRATION26_CPR9_TARG_VOLT_TURL1_BMSK                                                            0xfc0
#define HWIO_CALIBRATION26_CPR9_TARG_VOLT_TURL1_SHFT                                                              0x6
#define HWIO_CALIBRATION26_CPR8_TARG_VOLT_SVS3_BMSK                                                              0x3f
#define HWIO_CALIBRATION26_CPR8_TARG_VOLT_SVS3_SHFT                                                               0x0

#define HWIO_CALIBRATION27_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b84)
#define HWIO_CALIBRATION27_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b84)
#define HWIO_CALIBRATION27_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION27_IN          \
        in_dword(HWIO_CALIBRATION27_ADDR)
#define HWIO_CALIBRATION27_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION27_ADDR, m)
#define HWIO_CALIBRATION27_CPR9_TARG_VOLT_OFFSET_TURL1_BMSK                                                0xf8000000
#define HWIO_CALIBRATION27_CPR9_TARG_VOLT_OFFSET_TURL1_SHFT                                                      0x1b
#define HWIO_CALIBRATION27_CPR9_TARG_VOLT_SVS_BMSK                                                          0x7e00000
#define HWIO_CALIBRATION27_CPR9_TARG_VOLT_SVS_SHFT                                                               0x15
#define HWIO_CALIBRATION27_CPR9_TARG_VOLT_NOM_BMSK                                                           0x1f8000
#define HWIO_CALIBRATION27_CPR9_TARG_VOLT_NOM_SHFT                                                                0xf
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_OFFSET_SVS3_BMSK                                                     0x7c00
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_OFFSET_SVS3_SHFT                                                        0xa
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_OFFSET_SVS2_BMSK                                                      0x3e0
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_OFFSET_SVS2_SHFT                                                        0x5
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_OFFSET_SVS_BMSK                                                        0x1f
#define HWIO_CALIBRATION27_CPR8_TARG_VOLT_OFFSET_SVS_SHFT                                                         0x0

#define HWIO_CALIBRATION28_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b88)
#define HWIO_CALIBRATION28_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b88)
#define HWIO_CALIBRATION28_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION28_IN          \
        in_dword(HWIO_CALIBRATION28_ADDR)
#define HWIO_CALIBRATION28_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION28_ADDR, m)
#define HWIO_CALIBRATION28_CPR10_TARG_VOLT_NOM_BMSK                                                        0xfc000000
#define HWIO_CALIBRATION28_CPR10_TARG_VOLT_NOM_SHFT                                                              0x1a
#define HWIO_CALIBRATION28_CPR10_TARG_VOLT_TURL1_BMSK                                                       0x3f00000
#define HWIO_CALIBRATION28_CPR10_TARG_VOLT_TURL1_SHFT                                                            0x14
#define HWIO_CALIBRATION28_CPR10_TARG_VOLT_BOOST_BMSK                                                         0xfc000
#define HWIO_CALIBRATION28_CPR10_TARG_VOLT_BOOST_SHFT                                                             0xe
#define HWIO_CALIBRATION28_CPR9_TARG_VOLT_SVS3_BMSK                                                            0x3f00
#define HWIO_CALIBRATION28_CPR9_TARG_VOLT_SVS3_SHFT                                                               0x8
#define HWIO_CALIBRATION28_CPR8_AGING_BMSK                                                                       0xff
#define HWIO_CALIBRATION28_CPR8_AGING_SHFT                                                                        0x0

#define HWIO_CALIBRATION29_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b8c)
#define HWIO_CALIBRATION29_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b8c)
#define HWIO_CALIBRATION29_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION29_IN          \
        in_dword(HWIO_CALIBRATION29_ADDR)
#define HWIO_CALIBRATION29_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION29_ADDR, m)
#define HWIO_CALIBRATION29_CPR10_TARG_VOLT_SVS2_BMSK                                                       0xfc000000
#define HWIO_CALIBRATION29_CPR10_TARG_VOLT_SVS2_SHFT                                                             0x1a
#define HWIO_CALIBRATION29_CPR10_TARG_VOLT_SVS_BMSK                                                         0x3f00000
#define HWIO_CALIBRATION29_CPR10_TARG_VOLT_SVS_SHFT                                                              0x14
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_OFFSET_SVSL1_BMSK                                                   0xf8000
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_OFFSET_SVSL1_SHFT                                                       0xf
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_OFFSET_NOM_BMSK                                                      0x7c00
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_OFFSET_NOM_SHFT                                                         0xa
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_OFFSET_NOML1_BMSK                                                     0x3e0
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_OFFSET_NOML1_SHFT                                                       0x5
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_OFFSET_TUR_BMSK                                                        0x1f
#define HWIO_CALIBRATION29_CPR9_TARG_VOLT_OFFSET_TUR_SHFT                                                         0x0

#define HWIO_CALIBRATION30_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b90)
#define HWIO_CALIBRATION30_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b90)
#define HWIO_CALIBRATION30_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION30_IN          \
        in_dword(HWIO_CALIBRATION30_ADDR)
#define HWIO_CALIBRATION30_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION30_ADDR, m)
#define HWIO_CALIBRATION30_CALIBRATION_991_984_BMSK                                                        0xff000000
#define HWIO_CALIBRATION30_CALIBRATION_991_984_SHFT                                                              0x18
#define HWIO_CALIBRATION30_AON_TARG_VOLT_BMSK                                                                0xfc0000
#define HWIO_CALIBRATION30_AON_TARG_VOLT_SHFT                                                                    0x12
#define HWIO_CALIBRATION30_CPR9_AGING_BMSK                                                                    0x3fc00
#define HWIO_CALIBRATION30_CPR9_AGING_SHFT                                                                        0xa
#define HWIO_CALIBRATION30_CPR9_TARG_VOLT_OFFSET_SVS2_BMSK                                                      0x3e0
#define HWIO_CALIBRATION30_CPR9_TARG_VOLT_OFFSET_SVS2_SHFT                                                        0x5
#define HWIO_CALIBRATION30_CPR9_TARG_VOLT_OFFSET_SVS_BMSK                                                        0x1f
#define HWIO_CALIBRATION30_CPR9_TARG_VOLT_OFFSET_SVS_SHFT                                                         0x0

#define HWIO_CALIBRATION31_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b94)
#define HWIO_CALIBRATION31_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b94)
#define HWIO_CALIBRATION31_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION31_IN          \
        in_dword(HWIO_CALIBRATION31_ADDR)
#define HWIO_CALIBRATION31_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION31_ADDR, m)
#define HWIO_CALIBRATION31_CALIBRATION_1023_BMSK                                                           0x80000000
#define HWIO_CALIBRATION31_CALIBRATION_1023_SHFT                                                                 0x1f
#define HWIO_CALIBRATION31_CPR10_BOOST_QUOT_MIN_BMSK                                                       0x7ff80000
#define HWIO_CALIBRATION31_CPR10_BOOST_QUOT_MIN_SHFT                                                             0x13
#define HWIO_CALIBRATION31_CPR10_TARG_VOLT_SVS3_BMSK                                                          0x7e000
#define HWIO_CALIBRATION31_CPR10_TARG_VOLT_SVS3_SHFT                                                              0xd
#define HWIO_CALIBRATION31_CPR10_QUOT_OFFSET_BMSK                                                              0x1fe0
#define HWIO_CALIBRATION31_CPR10_QUOT_OFFSET_SHFT                                                                 0x5
#define HWIO_CALIBRATION31_CPR9_TARG_VOLT_OFFSET_SVS3_BMSK                                                       0x1f
#define HWIO_CALIBRATION31_CPR9_TARG_VOLT_OFFSET_SVS3_SHFT                                                        0x0

#define HWIO_CALIBRATION32_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b98)
#define HWIO_CALIBRATION32_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b98)
#define HWIO_CALIBRATION32_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION32_IN          \
        in_dword(HWIO_CALIBRATION32_ADDR)
#define HWIO_CALIBRATION32_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION32_ADDR, m)
#define HWIO_CALIBRATION32_CPR10_AGING_BMSK                                                                0xff000000
#define HWIO_CALIBRATION32_CPR10_AGING_SHFT                                                                      0x18
#define HWIO_CALIBRATION32_CPR10_NOM_QUOT_MIN_BMSK                                                           0xfff000
#define HWIO_CALIBRATION32_CPR10_NOM_QUOT_MIN_SHFT                                                                0xc
#define HWIO_CALIBRATION32_CPR10_TURL1_QUOT_MIN_BMSK                                                            0xfff
#define HWIO_CALIBRATION32_CPR10_TURL1_QUOT_MIN_SHFT                                                              0x0

#define HWIO_CALIBRATION33_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000b9c)
#define HWIO_CALIBRATION33_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000b9c)
#define HWIO_CALIBRATION33_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION33_IN          \
        in_dword(HWIO_CALIBRATION33_ADDR)
#define HWIO_CALIBRATION33_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION33_ADDR, m)
#define HWIO_CALIBRATION33_CALIBRATION_1087_1086_BMSK                                                      0xc0000000
#define HWIO_CALIBRATION33_CALIBRATION_1087_1086_SHFT                                                            0x1e
#define HWIO_CALIBRATION33_CPR11_TARG_VOLT_TURL1_BMSK                                                      0x3f000000
#define HWIO_CALIBRATION33_CPR11_TARG_VOLT_TURL1_SHFT                                                            0x18
#define HWIO_CALIBRATION33_CPR10_SVS2_QUOT_MIN_BMSK                                                          0xfff000
#define HWIO_CALIBRATION33_CPR10_SVS2_QUOT_MIN_SHFT                                                               0xc
#define HWIO_CALIBRATION33_CPR10_SVS_QUOT_MIN_BMSK                                                              0xfff
#define HWIO_CALIBRATION33_CPR10_SVS_QUOT_MIN_SHFT                                                                0x0

#define HWIO_CALIBRATION34_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000ba0)
#define HWIO_CALIBRATION34_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000ba0)
#define HWIO_CALIBRATION34_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION34_IN          \
        in_dword(HWIO_CALIBRATION34_ADDR)
#define HWIO_CALIBRATION34_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION34_ADDR, m)
#define HWIO_CALIBRATION34_CALIBRATION_1119_1118_BMSK                                                      0xc0000000
#define HWIO_CALIBRATION34_CALIBRATION_1119_1118_SHFT                                                            0x1e
#define HWIO_CALIBRATION34_CPR11_TARG_VOLT_NOM_BMSK                                                        0x3f000000
#define HWIO_CALIBRATION34_CPR11_TARG_VOLT_NOM_SHFT                                                              0x18
#define HWIO_CALIBRATION34_CPR11_TURL1_QUOT_MIN_BMSK                                                         0xfff000
#define HWIO_CALIBRATION34_CPR11_TURL1_QUOT_MIN_SHFT                                                              0xc
#define HWIO_CALIBRATION34_CPR10_SVS3_QUOT_MIN_BMSK                                                             0xfff
#define HWIO_CALIBRATION34_CPR10_SVS3_QUOT_MIN_SHFT                                                               0x0

#define HWIO_CALIBRATION35_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000ba4)
#define HWIO_CALIBRATION35_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000ba4)
#define HWIO_CALIBRATION35_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION35_IN          \
        in_dword(HWIO_CALIBRATION35_ADDR)
#define HWIO_CALIBRATION35_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION35_ADDR, m)
#define HWIO_CALIBRATION35_CALIBRATION_1151_1150_BMSK                                                      0xc0000000
#define HWIO_CALIBRATION35_CALIBRATION_1151_1150_SHFT                                                            0x1e
#define HWIO_CALIBRATION35_CPR11_NOM_QUOT_MIN_BMSK                                                         0x3ffc0000
#define HWIO_CALIBRATION35_CPR11_NOM_QUOT_MIN_SHFT                                                               0x12
#define HWIO_CALIBRATION35_CPR11_TARG_VOLT_SVS3_BMSK                                                          0x3f000
#define HWIO_CALIBRATION35_CPR11_TARG_VOLT_SVS3_SHFT                                                              0xc
#define HWIO_CALIBRATION35_CPR11_TARG_VOLT_SVS2_BMSK                                                            0xfc0
#define HWIO_CALIBRATION35_CPR11_TARG_VOLT_SVS2_SHFT                                                              0x6
#define HWIO_CALIBRATION35_CPR11_TARG_VOLT_SVS_BMSK                                                              0x3f
#define HWIO_CALIBRATION35_CPR11_TARG_VOLT_SVS_SHFT                                                               0x0

#define HWIO_CALIBRATION36_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000ba8)
#define HWIO_CALIBRATION36_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000ba8)
#define HWIO_CALIBRATION36_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION36_IN          \
        in_dword(HWIO_CALIBRATION36_ADDR)
#define HWIO_CALIBRATION36_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION36_ADDR, m)
#define HWIO_CALIBRATION36_CPR11_QUOT_OFFSET_BMSK                                                          0xff000000
#define HWIO_CALIBRATION36_CPR11_QUOT_OFFSET_SHFT                                                                0x18
#define HWIO_CALIBRATION36_CPR11_SVS2_QUOT_MIN_BMSK                                                          0xfff000
#define HWIO_CALIBRATION36_CPR11_SVS2_QUOT_MIN_SHFT                                                               0xc
#define HWIO_CALIBRATION36_CPR11_SVS_QUOT_MIN_BMSK                                                              0xfff
#define HWIO_CALIBRATION36_CPR11_SVS_QUOT_MIN_SHFT                                                                0x0

#define HWIO_CALIBRATION37_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bac)
#define HWIO_CALIBRATION37_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bac)
#define HWIO_CALIBRATION37_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION37_IN          \
        in_dword(HWIO_CALIBRATION37_ADDR)
#define HWIO_CALIBRATION37_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION37_ADDR, m)
#define HWIO_CALIBRATION37_CPR12_TARG_VOLT_BOOST_BMSK                                                      0xfc000000
#define HWIO_CALIBRATION37_CPR12_TARG_VOLT_BOOST_SHFT                                                            0x1a
#define HWIO_CALIBRATION37_CPR11_SVS3_QUOT_MIN_BMSK                                                         0x3ffc000
#define HWIO_CALIBRATION37_CPR11_SVS3_QUOT_MIN_SHFT                                                               0xe
#define HWIO_CALIBRATION37_AON_AGING_BMSK                                                                      0x3fc0
#define HWIO_CALIBRATION37_AON_AGING_SHFT                                                                         0x6
#define HWIO_CALIBRATION37_CPR12_TARG_VOLT_BOOSTP_BMSK                                                           0x3f
#define HWIO_CALIBRATION37_CPR12_TARG_VOLT_BOOSTP_SHFT                                                            0x0

#define HWIO_CALIBRATION38_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bb0)
#define HWIO_CALIBRATION38_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bb0)
#define HWIO_CALIBRATION38_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION38_IN          \
        in_dword(HWIO_CALIBRATION38_ADDR)
#define HWIO_CALIBRATION38_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION38_ADDR, m)
#define HWIO_CALIBRATION38_CPR12_QUOT_OFFSET_BMSK                                                          0xff000000
#define HWIO_CALIBRATION38_CPR12_QUOT_OFFSET_SHFT                                                                0x18
#define HWIO_CALIBRATION38_CPR12_TARG_VOLT_SVS2_BMSK                                                         0xfc0000
#define HWIO_CALIBRATION38_CPR12_TARG_VOLT_SVS2_SHFT                                                             0x12
#define HWIO_CALIBRATION38_CPR12_TARG_VOLT_SVS_BMSK                                                           0x3f000
#define HWIO_CALIBRATION38_CPR12_TARG_VOLT_SVS_SHFT                                                               0xc
#define HWIO_CALIBRATION38_CPR12_TARG_VOLT_NOM_BMSK                                                             0xfc0
#define HWIO_CALIBRATION38_CPR12_TARG_VOLT_NOM_SHFT                                                               0x6
#define HWIO_CALIBRATION38_CPR12_TARG_VOLT_TURL3_BMSK                                                            0x3f
#define HWIO_CALIBRATION38_CPR12_TARG_VOLT_TURL3_SHFT                                                             0x0

#define HWIO_CALIBRATION39_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bb4)
#define HWIO_CALIBRATION39_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bb4)
#define HWIO_CALIBRATION39_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION39_IN          \
        in_dword(HWIO_CALIBRATION39_ADDR)
#define HWIO_CALIBRATION39_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION39_ADDR, m)
#define HWIO_CALIBRATION39_CALIBRATION_1279_1278_BMSK                                                      0xc0000000
#define HWIO_CALIBRATION39_CALIBRATION_1279_1278_SHFT                                                            0x1e
#define HWIO_CALIBRATION39_CPR12_BOOST_QUOT_MIN_BMSK                                                       0x3ffc0000
#define HWIO_CALIBRATION39_CPR12_BOOST_QUOT_MIN_SHFT                                                             0x12
#define HWIO_CALIBRATION39_CPR12_BOOSTP_QUOT_MIN_BMSK                                                         0x3ffc0
#define HWIO_CALIBRATION39_CPR12_BOOSTP_QUOT_MIN_SHFT                                                             0x6
#define HWIO_CALIBRATION39_CPR12_TARG_VOLT_SVS3_BMSK                                                             0x3f
#define HWIO_CALIBRATION39_CPR12_TARG_VOLT_SVS3_SHFT                                                              0x0

#define HWIO_CALIBRATION40_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bb8)
#define HWIO_CALIBRATION40_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bb8)
#define HWIO_CALIBRATION40_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION40_IN          \
        in_dword(HWIO_CALIBRATION40_ADDR)
#define HWIO_CALIBRATION40_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION40_ADDR, m)
#define HWIO_CALIBRATION40_CALIBRATION_1311_1310_BMSK                                                      0xc0000000
#define HWIO_CALIBRATION40_CALIBRATION_1311_1310_SHFT                                                            0x1e
#define HWIO_CALIBRATION40_GNSS_ADC_CAL_BMSK                                                               0x3f000000
#define HWIO_CALIBRATION40_GNSS_ADC_CAL_SHFT                                                                     0x18
#define HWIO_CALIBRATION40_CPR12_NOM_QUOT_MIN_BMSK                                                           0xfff000
#define HWIO_CALIBRATION40_CPR12_NOM_QUOT_MIN_SHFT                                                                0xc
#define HWIO_CALIBRATION40_CPR12_TURL3_QUOT_MIN_BMSK                                                            0xfff
#define HWIO_CALIBRATION40_CPR12_TURL3_QUOT_MIN_SHFT                                                              0x0

#define HWIO_CALIBRATION41_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bbc)
#define HWIO_CALIBRATION41_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bbc)
#define HWIO_CALIBRATION41_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION41_IN          \
        in_dword(HWIO_CALIBRATION41_ADDR)
#define HWIO_CALIBRATION41_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION41_ADDR, m)
#define HWIO_CALIBRATION41_CALIBRATION_1343_1339_BMSK                                                      0xf8000000
#define HWIO_CALIBRATION41_CALIBRATION_1343_1339_SHFT                                                            0x1b
#define HWIO_CALIBRATION41_CPR_NSPCX_MODE_DISABLE_BMSK                                                      0x7000000
#define HWIO_CALIBRATION41_CPR_NSPCX_MODE_DISABLE_SHFT                                                           0x18
#define HWIO_CALIBRATION41_CPR_MMCX_MODE_DISABLE_BMSK                                                        0xe00000
#define HWIO_CALIBRATION41_CPR_MMCX_MODE_DISABLE_SHFT                                                            0x15
#define HWIO_CALIBRATION41_CPR_LPICX_MODE_DISABLE_BMSK                                                       0x1c0000
#define HWIO_CALIBRATION41_CPR_LPICX_MODE_DISABLE_SHFT                                                           0x12
#define HWIO_CALIBRATION41_CPR_LPIMX_MODE_DISABLE_BMSK                                                        0x38000
#define HWIO_CALIBRATION41_CPR_LPIMX_MODE_DISABLE_SHFT                                                            0xf
#define HWIO_CALIBRATION41_CPR_MXC_MODE_DISABLE_BMSK                                                           0x7000
#define HWIO_CALIBRATION41_CPR_MXC_MODE_DISABLE_SHFT                                                              0xc
#define HWIO_CALIBRATION41_CPR_MX_MODE_DISABLE_BMSK                                                             0xe00
#define HWIO_CALIBRATION41_CPR_MX_MODE_DISABLE_SHFT                                                               0x9
#define HWIO_CALIBRATION41_CPR_GFX_MODE_DISABLE_BMSK                                                            0x1c0
#define HWIO_CALIBRATION41_CPR_GFX_MODE_DISABLE_SHFT                                                              0x6
#define HWIO_CALIBRATION41_CPR_MSS_MODE_DISABLE_BMSK                                                             0x38
#define HWIO_CALIBRATION41_CPR_MSS_MODE_DISABLE_SHFT                                                              0x3
#define HWIO_CALIBRATION41_CPR_CX_MODE_DISABLE_BMSK                                                               0x7
#define HWIO_CALIBRATION41_CPR_CX_MODE_DISABLE_SHFT                                                               0x0

#define HWIO_CALIBRATION42_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bc0)
#define HWIO_CALIBRATION42_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bc0)
#define HWIO_CALIBRATION42_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION42_IN          \
        in_dword(HWIO_CALIBRATION42_ADDR)
#define HWIO_CALIBRATION42_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION42_ADDR, m)
#define HWIO_CALIBRATION42_CPR13_TARG_VOLT_BOOSTP_BMSK                                                     0xfc000000
#define HWIO_CALIBRATION42_CPR13_TARG_VOLT_BOOSTP_SHFT                                                           0x1a
#define HWIO_CALIBRATION42_CPR12_AGING_BMSK                                                                 0x3fc0000
#define HWIO_CALIBRATION42_CPR12_AGING_SHFT                                                                      0x12
#define HWIO_CALIBRATION42_CALIBRATION_1361_1359_BMSK                                                         0x38000
#define HWIO_CALIBRATION42_CALIBRATION_1361_1359_SHFT                                                             0xf
#define HWIO_CALIBRATION42_CPR_VDDA_MODE_DISABLE_BMSK                                                          0x7000
#define HWIO_CALIBRATION42_CPR_VDDA_MODE_DISABLE_SHFT                                                             0xc
#define HWIO_CALIBRATION42_CPR_APC1_GOLDP_MODE_DISABLE_BMSK                                                     0xe00
#define HWIO_CALIBRATION42_CPR_APC1_GOLDP_MODE_DISABLE_SHFT                                                       0x9
#define HWIO_CALIBRATION42_CPR_APC1_GOLD_MODE_DISABLE_BMSK                                                      0x1c0
#define HWIO_CALIBRATION42_CPR_APC1_GOLD_MODE_DISABLE_SHFT                                                        0x6
#define HWIO_CALIBRATION42_CPR_APC0_L3_MODE_DISABLE_BMSK                                                         0x38
#define HWIO_CALIBRATION42_CPR_APC0_L3_MODE_DISABLE_SHFT                                                          0x3
#define HWIO_CALIBRATION42_CPR_APC0_SILVER_MODE_DISABLE_BMSK                                                      0x7
#define HWIO_CALIBRATION42_CPR_APC0_SILVER_MODE_DISABLE_SHFT                                                      0x0

#define HWIO_CALIBRATION43_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bc4)
#define HWIO_CALIBRATION43_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bc4)
#define HWIO_CALIBRATION43_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION43_IN          \
        in_dword(HWIO_CALIBRATION43_ADDR)
#define HWIO_CALIBRATION43_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION43_ADDR, m)
#define HWIO_CALIBRATION43_CALIBRATION_1407_1403_BMSK                                                      0xf8000000
#define HWIO_CALIBRATION43_CALIBRATION_1407_1403_SHFT                                                            0x1b
#define HWIO_CALIBRATION43_APC0_PEAK_THROTTLE_FREQ_BMSK                                                     0x6000000
#define HWIO_CALIBRATION43_APC0_PEAK_THROTTLE_FREQ_SHFT                                                          0x19
#define HWIO_CALIBRATION43_APC0_PEAK_THROTTLE_TJ_BMSK                                                       0x1f00000
#define HWIO_CALIBRATION43_APC0_PEAK_THROTTLE_TJ_SHFT                                                            0x14
#define HWIO_CALIBRATION43_CPR13_QUOT_OFFSET_BMSK                                                             0xff000
#define HWIO_CALIBRATION43_CPR13_QUOT_OFFSET_SHFT                                                                 0xc
#define HWIO_CALIBRATION43_CPR12_SVS_QUOT_MIN_BMSK                                                              0xfff
#define HWIO_CALIBRATION43_CPR12_SVS_QUOT_MIN_SHFT                                                                0x0

#define HWIO_CALIBRATION44_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bc8)
#define HWIO_CALIBRATION44_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bc8)
#define HWIO_CALIBRATION44_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION44_IN          \
        in_dword(HWIO_CALIBRATION44_ADDR)
#define HWIO_CALIBRATION44_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION44_ADDR, m)
#define HWIO_CALIBRATION44_CPR_LOCAL_RC_BMSK                                                               0xf0000000
#define HWIO_CALIBRATION44_CPR_LOCAL_RC_SHFT                                                                     0x1c
#define HWIO_CALIBRATION44_CPR_GLOBAL_RC_BMSK                                                               0xf000000
#define HWIO_CALIBRATION44_CPR_GLOBAL_RC_SHFT                                                                    0x18
#define HWIO_CALIBRATION44_ACC_LV_APC1_BMSK                                                                  0xfc0000
#define HWIO_CALIBRATION44_ACC_LV_APC1_SHFT                                                                      0x12
#define HWIO_CALIBRATION44_ACC_LV_APC0_BMSK                                                                   0x3f000
#define HWIO_CALIBRATION44_ACC_LV_APC0_SHFT                                                                       0xc
#define HWIO_CALIBRATION44_ACC_HV_APC1_BMSK                                                                     0xfc0
#define HWIO_CALIBRATION44_ACC_HV_APC1_SHFT                                                                       0x6
#define HWIO_CALIBRATION44_ACC_HV_APC0_BMSK                                                                      0x3f
#define HWIO_CALIBRATION44_ACC_HV_APC0_SHFT                                                                       0x0

#define HWIO_CALIBRATION45_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bcc)
#define HWIO_CALIBRATION45_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bcc)
#define HWIO_CALIBRATION45_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION45_IN          \
        in_dword(HWIO_CALIBRATION45_ADDR)
#define HWIO_CALIBRATION45_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION45_ADDR, m)
#define HWIO_CALIBRATION45_AOSS_K_BMSK                                                                     0xffff0000
#define HWIO_CALIBRATION45_AOSS_K_SHFT                                                                           0x10
#define HWIO_CALIBRATION45_CALIBRATION_1455_BMSK                                                               0x8000
#define HWIO_CALIBRATION45_CALIBRATION_1455_SHFT                                                                  0xf
#define HWIO_CALIBRATION45_GFX_FUSE_RESERVED_2_0_BMSK                                                          0x7000
#define HWIO_CALIBRATION45_GFX_FUSE_RESERVED_2_0_SHFT                                                             0xc
#define HWIO_CALIBRATION45_CPR12_SVS2_QUOT_MIN_BMSK                                                             0xfff
#define HWIO_CALIBRATION45_CPR12_SVS2_QUOT_MIN_SHFT                                                               0x0

#define HWIO_CALIBRATION46_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bd0)
#define HWIO_CALIBRATION46_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bd0)
#define HWIO_CALIBRATION46_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION46_IN          \
        in_dword(HWIO_CALIBRATION46_ADDR)
#define HWIO_CALIBRATION46_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION46_ADDR, m)
#define HWIO_CALIBRATION46_CALIBRATION_1503_1500_BMSK                                                      0xf0000000
#define HWIO_CALIBRATION46_CALIBRATION_1503_1500_SHFT                                                            0x1c
#define HWIO_CALIBRATION46_AOSS_TDOPCODE_BMSK                                                               0xf800000
#define HWIO_CALIBRATION46_AOSS_TDOPCODE_SHFT                                                                    0x17
#define HWIO_CALIBRATION46_AOSS_RDOPCODE_BMSK                                                                0x7c0000
#define HWIO_CALIBRATION46_AOSS_RDOPCODE_SHFT                                                                    0x12
#define HWIO_CALIBRATION46_AOSS_N1_BMSK                                                                       0x3ffff
#define HWIO_CALIBRATION46_AOSS_N1_SHFT                                                                           0x0

#define HWIO_CALIBRATION47_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bd4)
#define HWIO_CALIBRATION47_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bd4)
#define HWIO_CALIBRATION47_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION47_IN          \
        in_dword(HWIO_CALIBRATION47_ADDR)
#define HWIO_CALIBRATION47_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION47_ADDR, m)
#define HWIO_CALIBRATION47_TSENS1_BASE1_BMSK                                                               0xffc00000
#define HWIO_CALIBRATION47_TSENS1_BASE1_SHFT                                                                     0x16
#define HWIO_CALIBRATION47_CALIBRATION_1525_1522_BMSK                                                        0x3c0000
#define HWIO_CALIBRATION47_CALIBRATION_1525_1522_SHFT                                                            0x12
#define HWIO_CALIBRATION47_AOSS_P1_BMSK                                                                       0x3ffff
#define HWIO_CALIBRATION47_AOSS_P1_SHFT                                                                           0x0

#define HWIO_CALIBRATION48_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bd8)
#define HWIO_CALIBRATION48_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bd8)
#define HWIO_CALIBRATION48_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION48_IN          \
        in_dword(HWIO_CALIBRATION48_ADDR)
#define HWIO_CALIBRATION48_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION48_ADDR, m)
#define HWIO_CALIBRATION48_CALIBRATION_1567_1566_BMSK                                                      0xc0000000
#define HWIO_CALIBRATION48_CALIBRATION_1567_1566_SHFT                                                            0x1e
#define HWIO_CALIBRATION48_TSENS1_BASE0_BMSK                                                               0x3ff00000
#define HWIO_CALIBRATION48_TSENS1_BASE0_SHFT                                                                     0x14
#define HWIO_CALIBRATION48_TSENS0_BASE1_BMSK                                                                  0xffc00
#define HWIO_CALIBRATION48_TSENS0_BASE1_SHFT                                                                      0xa
#define HWIO_CALIBRATION48_TSENS0_BASE0_BMSK                                                                    0x3ff
#define HWIO_CALIBRATION48_TSENS0_BASE0_SHFT                                                                      0x0

#define HWIO_CALIBRATION49_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bdc)
#define HWIO_CALIBRATION49_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bdc)
#define HWIO_CALIBRATION49_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION49_IN          \
        in_dword(HWIO_CALIBRATION49_ADDR)
#define HWIO_CALIBRATION49_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION49_ADDR, m)
#define HWIO_CALIBRATION49_CALIBRATION_1599_1596_BMSK                                                      0xf0000000
#define HWIO_CALIBRATION49_CALIBRATION_1599_1596_SHFT                                                            0x1c
#define HWIO_CALIBRATION49_TSENS3_OFFSET_BMSK                                                               0xf800000
#define HWIO_CALIBRATION49_TSENS3_OFFSET_SHFT                                                                    0x17
#define HWIO_CALIBRATION49_TSENS2_OFFSET_BMSK                                                                0x7c0000
#define HWIO_CALIBRATION49_TSENS2_OFFSET_SHFT                                                                    0x12
#define HWIO_CALIBRATION49_TSENS1_OFFSET_BMSK                                                                 0x3e000
#define HWIO_CALIBRATION49_TSENS1_OFFSET_SHFT                                                                     0xd
#define HWIO_CALIBRATION49_TSENS0_OFFSET_BMSK                                                                  0x1f00
#define HWIO_CALIBRATION49_TSENS0_OFFSET_SHFT                                                                     0x8
#define HWIO_CALIBRATION49_CALIBRATION_1575_1574_BMSK                                                            0xc0
#define HWIO_CALIBRATION49_CALIBRATION_1575_1574_SHFT                                                             0x6
#define HWIO_CALIBRATION49_CPR13_TARG_VOLT_BOOST_BMSK                                                            0x3f
#define HWIO_CALIBRATION49_CPR13_TARG_VOLT_BOOST_SHFT                                                             0x0

#define HWIO_CALIBRATION50_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000be0)
#define HWIO_CALIBRATION50_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000be0)
#define HWIO_CALIBRATION50_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION50_IN          \
        in_dword(HWIO_CALIBRATION50_ADDR)
#define HWIO_CALIBRATION50_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION50_ADDR, m)
#define HWIO_CALIBRATION50_CALIBRATION_1631_BMSK                                                           0x80000000
#define HWIO_CALIBRATION50_CALIBRATION_1631_SHFT                                                                 0x1f
#define HWIO_CALIBRATION50_TSENS10_OFFSET_BMSK                                                             0x7c000000
#define HWIO_CALIBRATION50_TSENS10_OFFSET_SHFT                                                                   0x1a
#define HWIO_CALIBRATION50_TSENS9_OFFSET_BMSK                                                               0x3e00000
#define HWIO_CALIBRATION50_TSENS9_OFFSET_SHFT                                                                    0x15
#define HWIO_CALIBRATION50_TSENS8_OFFSET_BMSK                                                                0x1f0000
#define HWIO_CALIBRATION50_TSENS8_OFFSET_SHFT                                                                    0x10
#define HWIO_CALIBRATION50_TSENS7_OFFSET_BMSK                                                                  0xf800
#define HWIO_CALIBRATION50_TSENS7_OFFSET_SHFT                                                                     0xb
#define HWIO_CALIBRATION50_TSENS6_OFFSET_BMSK                                                                   0x7c0
#define HWIO_CALIBRATION50_TSENS6_OFFSET_SHFT                                                                     0x6
#define HWIO_CALIBRATION50_TSENS5_OFFSET_BMSK                                                                    0x3e
#define HWIO_CALIBRATION50_TSENS5_OFFSET_SHFT                                                                     0x1
#define HWIO_CALIBRATION50_CALIBRATION_1600_BMSK                                                                  0x1
#define HWIO_CALIBRATION50_CALIBRATION_1600_SHFT                                                                  0x0

#define HWIO_CALIBRATION51_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000be4)
#define HWIO_CALIBRATION51_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000be4)
#define HWIO_CALIBRATION51_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION51_IN          \
        in_dword(HWIO_CALIBRATION51_ADDR)
#define HWIO_CALIBRATION51_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION51_ADDR, m)
#define HWIO_CALIBRATION51_CALIBRATION_1663_1661_BMSK                                                      0xe0000000
#define HWIO_CALIBRATION51_CALIBRATION_1663_1661_SHFT                                                            0x1d
#define HWIO_CALIBRATION51_TSENS16_OFFSET_BMSK                                                             0x1f000000
#define HWIO_CALIBRATION51_TSENS16_OFFSET_SHFT                                                                   0x18
#define HWIO_CALIBRATION51_TSENS15_OFFSET_BMSK                                                               0xf80000
#define HWIO_CALIBRATION51_TSENS15_OFFSET_SHFT                                                                   0x13
#define HWIO_CALIBRATION51_TSENS14_OFFSET_BMSK                                                                0x7c000
#define HWIO_CALIBRATION51_TSENS14_OFFSET_SHFT                                                                    0xe
#define HWIO_CALIBRATION51_TSENS13_OFFSET_BMSK                                                                 0x3e00
#define HWIO_CALIBRATION51_TSENS13_OFFSET_SHFT                                                                    0x9
#define HWIO_CALIBRATION51_TSENS12_OFFSET_BMSK                                                                  0x1f0
#define HWIO_CALIBRATION51_TSENS12_OFFSET_SHFT                                                                    0x4
#define HWIO_CALIBRATION51_CALIBRATION_1635_1632_BMSK                                                             0xf
#define HWIO_CALIBRATION51_CALIBRATION_1635_1632_SHFT                                                             0x0

#define HWIO_CALIBRATION52_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000be8)
#define HWIO_CALIBRATION52_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000be8)
#define HWIO_CALIBRATION52_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION52_IN          \
        in_dword(HWIO_CALIBRATION52_ADDR)
#define HWIO_CALIBRATION52_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION52_ADDR, m)
#define HWIO_CALIBRATION52_TSENS23_OFFSET_BMSK                                                             0xf8000000
#define HWIO_CALIBRATION52_TSENS23_OFFSET_SHFT                                                                   0x1b
#define HWIO_CALIBRATION52_TSENS22_OFFSET_BMSK                                                              0x7c00000
#define HWIO_CALIBRATION52_TSENS22_OFFSET_SHFT                                                                   0x16
#define HWIO_CALIBRATION52_TSENS21_OFFSET_BMSK                                                               0x3e0000
#define HWIO_CALIBRATION52_TSENS21_OFFSET_SHFT                                                                   0x11
#define HWIO_CALIBRATION52_TSENS20_OFFSET_BMSK                                                                0x1f000
#define HWIO_CALIBRATION52_TSENS20_OFFSET_SHFT                                                                    0xc
#define HWIO_CALIBRATION52_TSENS19_OFFSET_BMSK                                                                  0xf80
#define HWIO_CALIBRATION52_TSENS19_OFFSET_SHFT                                                                    0x7
#define HWIO_CALIBRATION52_TSENS18_OFFSET_BMSK                                                                   0x7c
#define HWIO_CALIBRATION52_TSENS18_OFFSET_SHFT                                                                    0x2
#define HWIO_CALIBRATION52_CALIBRATION_1665_1664_BMSK                                                             0x3
#define HWIO_CALIBRATION52_CALIBRATION_1665_1664_SHFT                                                             0x0

#define HWIO_CALIBRATION53_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bec)
#define HWIO_CALIBRATION53_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bec)
#define HWIO_CALIBRATION53_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION53_IN          \
        in_dword(HWIO_CALIBRATION53_ADDR)
#define HWIO_CALIBRATION53_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION53_ADDR, m)
#define HWIO_CALIBRATION53_CALIBRATION_1727_1726_BMSK                                                      0xc0000000
#define HWIO_CALIBRATION53_CALIBRATION_1727_1726_SHFT                                                            0x1e
#define HWIO_CALIBRATION53_TSENS29_OFFSET_BMSK                                                             0x3e000000
#define HWIO_CALIBRATION53_TSENS29_OFFSET_SHFT                                                                   0x19
#define HWIO_CALIBRATION53_TSENS28_OFFSET_BMSK                                                              0x1f00000
#define HWIO_CALIBRATION53_TSENS28_OFFSET_SHFT                                                                   0x14
#define HWIO_CALIBRATION53_TSENS27_OFFSET_BMSK                                                                0xf8000
#define HWIO_CALIBRATION53_TSENS27_OFFSET_SHFT                                                                    0xf
#define HWIO_CALIBRATION53_TSENS26_OFFSET_BMSK                                                                 0x7c00
#define HWIO_CALIBRATION53_TSENS26_OFFSET_SHFT                                                                    0xa
#define HWIO_CALIBRATION53_TSENS25_OFFSET_BMSK                                                                  0x3e0
#define HWIO_CALIBRATION53_TSENS25_OFFSET_SHFT                                                                    0x5
#define HWIO_CALIBRATION53_TSENS24_OFFSET_BMSK                                                                   0x1f
#define HWIO_CALIBRATION53_TSENS24_OFFSET_SHFT                                                                    0x0

#define HWIO_CALIBRATION54_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bf0)
#define HWIO_CALIBRATION54_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bf0)
#define HWIO_CALIBRATION54_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION54_IN          \
        in_dword(HWIO_CALIBRATION54_ADDR)
#define HWIO_CALIBRATION54_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION54_ADDR, m)
#define HWIO_CALIBRATION54_CALIBRATION_1759_BMSK                                                           0x80000000
#define HWIO_CALIBRATION54_CALIBRATION_1759_SHFT                                                                 0x1f
#define HWIO_CALIBRATION54_TSENS11_OFFSET_BMSK                                                             0x7c000000
#define HWIO_CALIBRATION54_TSENS11_OFFSET_SHFT                                                                   0x1a
#define HWIO_CALIBRATION54_TSENS34_OFFSET_BMSK                                                              0x3e00000
#define HWIO_CALIBRATION54_TSENS34_OFFSET_SHFT                                                                   0x15
#define HWIO_CALIBRATION54_TSENS33_OFFSET_BMSK                                                               0x1f0000
#define HWIO_CALIBRATION54_TSENS33_OFFSET_SHFT                                                                   0x10
#define HWIO_CALIBRATION54_TSENS32_OFFSET_BMSK                                                                 0xf800
#define HWIO_CALIBRATION54_TSENS32_OFFSET_SHFT                                                                    0xb
#define HWIO_CALIBRATION54_TSENS_CAL_SEL_BMSK                                                                   0x700
#define HWIO_CALIBRATION54_TSENS_CAL_SEL_SHFT                                                                     0x8
#define HWIO_CALIBRATION54_TSENS31_OFFSET_BMSK                                                                   0xf8
#define HWIO_CALIBRATION54_TSENS31_OFFSET_SHFT                                                                    0x3
#define HWIO_CALIBRATION54_CALIBRATION_1730_1728_BMSK                                                             0x7
#define HWIO_CALIBRATION54_CALIBRATION_1730_1728_SHFT                                                             0x0

#define HWIO_CALIBRATION55_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bf4)
#define HWIO_CALIBRATION55_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bf4)
#define HWIO_CALIBRATION55_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION55_IN          \
        in_dword(HWIO_CALIBRATION55_ADDR)
#define HWIO_CALIBRATION55_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION55_ADDR, m)
#define HWIO_CALIBRATION55_CALIBRATION_1791_1787_BMSK                                                      0xf8000000
#define HWIO_CALIBRATION55_CALIBRATION_1791_1787_SHFT                                                            0x1b
#define HWIO_CALIBRATION55_CPR13_BOOSTP_QUOT_MIN_BMSK                                                       0x7ff8000
#define HWIO_CALIBRATION55_CPR13_BOOSTP_QUOT_MIN_SHFT                                                             0xf
#define HWIO_CALIBRATION55_TSENS4_OFFSET_BMSK                                                                  0x7c00
#define HWIO_CALIBRATION55_TSENS4_OFFSET_SHFT                                                                     0xa
#define HWIO_CALIBRATION55_TSENS30_OFFSET_BMSK                                                                  0x3e0
#define HWIO_CALIBRATION55_TSENS30_OFFSET_SHFT                                                                    0x5
#define HWIO_CALIBRATION55_TSENS17_OFFSET_BMSK                                                                   0x1f
#define HWIO_CALIBRATION55_TSENS17_OFFSET_SHFT                                                                    0x0

#define HWIO_CALIBRATION56_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bf8)
#define HWIO_CALIBRATION56_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bf8)
#define HWIO_CALIBRATION56_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION56_IN          \
        in_dword(HWIO_CALIBRATION56_ADDR)
#define HWIO_CALIBRATION56_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION56_ADDR, m)
#define HWIO_CALIBRATION56_CALIBRATION_1823_1822_BMSK                                                      0xc0000000
#define HWIO_CALIBRATION56_CALIBRATION_1823_1822_SHFT                                                            0x1e
#define HWIO_CALIBRATION56_CPR13_TARG_VOLT_SVS3_BMSK                                                       0x3f000000
#define HWIO_CALIBRATION56_CPR13_TARG_VOLT_SVS3_SHFT                                                             0x18
#define HWIO_CALIBRATION56_CPR13_TARG_VOLT_SVS2_BMSK                                                         0xfc0000
#define HWIO_CALIBRATION56_CPR13_TARG_VOLT_SVS2_SHFT                                                             0x12
#define HWIO_CALIBRATION56_CPR13_TARG_VOLT_SVS_BMSK                                                           0x3f000
#define HWIO_CALIBRATION56_CPR13_TARG_VOLT_SVS_SHFT                                                               0xc
#define HWIO_CALIBRATION56_CPR13_TARG_VOLT_NOM_BMSK                                                             0xfc0
#define HWIO_CALIBRATION56_CPR13_TARG_VOLT_NOM_SHFT                                                               0x6
#define HWIO_CALIBRATION56_CPR13_TARG_VOLT_TURL3_BMSK                                                            0x3f
#define HWIO_CALIBRATION56_CPR13_TARG_VOLT_TURL3_SHFT                                                             0x0

#define HWIO_CALIBRATION57_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000bfc)
#define HWIO_CALIBRATION57_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000bfc)
#define HWIO_CALIBRATION57_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION57_IN          \
        in_dword(HWIO_CALIBRATION57_ADDR)
#define HWIO_CALIBRATION57_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION57_ADDR, m)
#define HWIO_CALIBRATION57_CALIBRATION_1855_1848_BMSK                                                      0xff000000
#define HWIO_CALIBRATION57_CALIBRATION_1855_1848_SHFT                                                            0x18
#define HWIO_CALIBRATION57_CPR13_TURL3_QUOT_MIN_BMSK                                                         0xfff000
#define HWIO_CALIBRATION57_CPR13_TURL3_QUOT_MIN_SHFT                                                              0xc
#define HWIO_CALIBRATION57_CPR13_BOOST_QUOT_MIN_BMSK                                                            0xfff
#define HWIO_CALIBRATION57_CPR13_BOOST_QUOT_MIN_SHFT                                                              0x0

#define HWIO_CALIBRATION58_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c00)
#define HWIO_CALIBRATION58_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c00)
#define HWIO_CALIBRATION58_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION58_IN          \
        in_dword(HWIO_CALIBRATION58_ADDR)
#define HWIO_CALIBRATION58_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION58_ADDR, m)
#define HWIO_CALIBRATION58_CALIBRATION_1887_1856_BMSK                                                      0xffffffff
#define HWIO_CALIBRATION58_CALIBRATION_1887_1856_SHFT                                                             0x0

#define HWIO_CALIBRATION59_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c04)
#define HWIO_CALIBRATION59_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c04)
#define HWIO_CALIBRATION59_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION59_IN          \
        in_dword(HWIO_CALIBRATION59_ADDR)
#define HWIO_CALIBRATION59_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION59_ADDR, m)
#define HWIO_CALIBRATION59_CALIBRATION_1919_1888_BMSK                                                      0xffffffff
#define HWIO_CALIBRATION59_CALIBRATION_1919_1888_SHFT                                                             0x0

#define HWIO_CALIBRATION60_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c08)
#define HWIO_CALIBRATION60_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c08)
#define HWIO_CALIBRATION60_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION60_IN          \
        in_dword(HWIO_CALIBRATION60_ADDR)
#define HWIO_CALIBRATION60_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION60_ADDR, m)
#define HWIO_CALIBRATION60_CALIBRATION_1951_1934_BMSK                                                      0xffffc000
#define HWIO_CALIBRATION60_CALIBRATION_1951_1934_SHFT                                                             0xe
#define HWIO_CALIBRATION60_CPR13_NOM_QUOT_MIN_BMSK                                                             0x3ffc
#define HWIO_CALIBRATION60_CPR13_NOM_QUOT_MIN_SHFT                                                                0x2
#define HWIO_CALIBRATION60_CALIBRATION_1921_1920_BMSK                                                             0x3
#define HWIO_CALIBRATION60_CALIBRATION_1921_1920_SHFT                                                             0x0

#define HWIO_CALIBRATION61_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c0c)
#define HWIO_CALIBRATION61_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c0c)
#define HWIO_CALIBRATION61_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION61_IN          \
        in_dword(HWIO_CALIBRATION61_ADDR)
#define HWIO_CALIBRATION61_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION61_ADDR, m)
#define HWIO_CALIBRATION61_CALIBRATION_1983_1952_BMSK                                                      0xffffffff
#define HWIO_CALIBRATION61_CALIBRATION_1983_1952_SHFT                                                             0x0

#define HWIO_CALIBRATION62_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c10)
#define HWIO_CALIBRATION62_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c10)
#define HWIO_CALIBRATION62_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION62_IN          \
        in_dword(HWIO_CALIBRATION62_ADDR)
#define HWIO_CALIBRATION62_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION62_ADDR, m)
#define HWIO_CALIBRATION62_CALIBRATION_2015_2014_BMSK                                                      0xc0000000
#define HWIO_CALIBRATION62_CALIBRATION_2015_2014_SHFT                                                            0x1e
#define HWIO_CALIBRATION62_GFX_PEAK_VOLTAGE_DELTA_BMSK                                                     0x3e000000
#define HWIO_CALIBRATION62_GFX_PEAK_VOLTAGE_DELTA_SHFT                                                           0x19
#define HWIO_CALIBRATION62_GFX_PEAK_VOLTAGE_V_HF_BMSK                                                       0x1ff8000
#define HWIO_CALIBRATION62_GFX_PEAK_VOLTAGE_V_HF_SHFT                                                             0xf
#define HWIO_CALIBRATION62_GFX_PEAK_CURRENT_DELTA_BMSK                                                         0x7ff8
#define HWIO_CALIBRATION62_GFX_PEAK_CURRENT_DELTA_SHFT                                                            0x3
#define HWIO_CALIBRATION62_CALIBRATION_1986_1984_BMSK                                                             0x7
#define HWIO_CALIBRATION62_CALIBRATION_1986_1984_SHFT                                                             0x0

#define HWIO_CALIBRATION63_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c14)
#define HWIO_CALIBRATION63_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c14)
#define HWIO_CALIBRATION63_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION63_IN          \
        in_dword(HWIO_CALIBRATION63_ADDR)
#define HWIO_CALIBRATION63_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION63_ADDR, m)
#define HWIO_CALIBRATION63_CALIBRATION_2047_2040_BMSK                                                      0xff000000
#define HWIO_CALIBRATION63_CALIBRATION_2047_2040_SHFT                                                            0x18
#define HWIO_CALIBRATION63_CPR13_SVS2_QUOT_MIN_BMSK                                                          0xfff000
#define HWIO_CALIBRATION63_CPR13_SVS2_QUOT_MIN_SHFT                                                               0xc
#define HWIO_CALIBRATION63_CPR13_SVS_QUOT_MIN_BMSK                                                              0xfff
#define HWIO_CALIBRATION63_CPR13_SVS_QUOT_MIN_SHFT                                                                0x0

#define HWIO_CALIBRATION64_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c18)
#define HWIO_CALIBRATION64_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c18)
#define HWIO_CALIBRATION64_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION64_IN          \
        in_dword(HWIO_CALIBRATION64_ADDR)
#define HWIO_CALIBRATION64_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION64_ADDR, m)
#define HWIO_CALIBRATION64_CALIBRATION_2079_2048_BMSK                                                      0xffffffff
#define HWIO_CALIBRATION64_CALIBRATION_2079_2048_SHFT                                                             0x0

#define HWIO_CALIBRATION65_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c1c)
#define HWIO_CALIBRATION65_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c1c)
#define HWIO_CALIBRATION65_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION65_IN          \
        in_dword(HWIO_CALIBRATION65_ADDR)
#define HWIO_CALIBRATION65_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION65_ADDR, m)
#define HWIO_CALIBRATION65_CALIBRATION_2111_2104_BMSK                                                      0xff000000
#define HWIO_CALIBRATION65_CALIBRATION_2111_2104_SHFT                                                            0x18
#define HWIO_CALIBRATION65_CPR13_SVS3_QUOT_MIN_BMSK                                                          0xfff000
#define HWIO_CALIBRATION65_CPR13_SVS3_QUOT_MIN_SHFT                                                               0xc
#define HWIO_CALIBRATION65_CALIBRATION_2091_2080_BMSK                                                           0xfff
#define HWIO_CALIBRATION65_CALIBRATION_2091_2080_SHFT                                                             0x0

#define HWIO_CALIBRATION66_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c20)
#define HWIO_CALIBRATION66_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c20)
#define HWIO_CALIBRATION66_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION66_IN          \
        in_dword(HWIO_CALIBRATION66_ADDR)
#define HWIO_CALIBRATION66_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION66_ADDR, m)
#define HWIO_CALIBRATION66_CALIBRATION_2143_2141_BMSK                                                      0xe0000000
#define HWIO_CALIBRATION66_CALIBRATION_2143_2141_SHFT                                                            0x1d
#define HWIO_CALIBRATION66_ACD_NSP_DVM_TURL1_BMSK                                                          0x1fffffe0
#define HWIO_CALIBRATION66_ACD_NSP_DVM_TURL1_SHFT                                                                 0x5
#define HWIO_CALIBRATION66_CALIBRATION_2116_2112_BMSK                                                            0x1f
#define HWIO_CALIBRATION66_CALIBRATION_2116_2112_SHFT                                                             0x0

#define HWIO_CALIBRATION67_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c24)
#define HWIO_CALIBRATION67_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c24)
#define HWIO_CALIBRATION67_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION67_IN          \
        in_dword(HWIO_CALIBRATION67_ADDR)
#define HWIO_CALIBRATION67_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION67_ADDR, m)
#define HWIO_CALIBRATION67_GFX_CURRENT_REVISION_BMSK                                                       0xc0000000
#define HWIO_CALIBRATION67_GFX_CURRENT_REVISION_SHFT                                                             0x1e
#define HWIO_CALIBRATION67_CALIBRATION_2173_2157_BMSK                                                      0x3fffe000
#define HWIO_CALIBRATION67_CALIBRATION_2173_2157_SHFT                                                             0xd
#define HWIO_CALIBRATION67_GFX_PEAK_CURRENT_I_LF_BMSK                                                          0x1fff
#define HWIO_CALIBRATION67_GFX_PEAK_CURRENT_I_LF_SHFT                                                             0x0

#define HWIO_CALIBRATION68_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c28)
#define HWIO_CALIBRATION68_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c28)
#define HWIO_CALIBRATION68_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION68_IN          \
        in_dword(HWIO_CALIBRATION68_ADDR)
#define HWIO_CALIBRATION68_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION68_ADDR, m)
#define HWIO_CALIBRATION68_CALIBATION_2207_2206_BMSK                                                       0xc0000000
#define HWIO_CALIBRATION68_CALIBATION_2207_2206_SHFT                                                             0x1e
#define HWIO_CALIBRATION68_CALIBRATION_2205_2201_BMSK                                                      0x3e000000
#define HWIO_CALIBRATION68_CALIBRATION_2205_2201_SHFT                                                            0x19
#define HWIO_CALIBRATION68_CALIBATION_2200_2196_BMSK                                                        0x1f00000
#define HWIO_CALIBRATION68_CALIBATION_2200_2196_SHFT                                                             0x14
#define HWIO_CALIBRATION68_CALIBRATION_2195_2194_BMSK                                                         0xc0000
#define HWIO_CALIBRATION68_CALIBRATION_2195_2194_SHFT                                                            0x12
#define HWIO_CALIBRATION68_GFX_FUSE_RESERVED_16_0_BMSK                                                        0x3ffff
#define HWIO_CALIBRATION68_GFX_FUSE_RESERVED_16_0_SHFT                                                            0x0

#define HWIO_CALIBRATION69_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c2c)
#define HWIO_CALIBRATION69_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c2c)
#define HWIO_CALIBRATION69_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION69_IN          \
        in_dword(HWIO_CALIBRATION69_ADDR)
#define HWIO_CALIBRATION69_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION69_ADDR, m)
#define HWIO_CALIBRATION69_CALIBRATION_2239_2231_BMSK                                                      0xff800000
#define HWIO_CALIBRATION69_CALIBRATION_2239_2231_SHFT                                                            0x17
#define HWIO_CALIBRATION69_CALIBATION_2230_2208_BMSK                                                         0x7fffff
#define HWIO_CALIBRATION69_CALIBATION_2230_2208_SHFT                                                              0x0

#define HWIO_CALIBRATION70_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c30)
#define HWIO_CALIBRATION70_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c30)
#define HWIO_CALIBRATION70_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION70_IN          \
        in_dword(HWIO_CALIBRATION70_ADDR)
#define HWIO_CALIBRATION70_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION70_ADDR, m)
#define HWIO_CALIBRATION70_CALIBRATION_2271_2264_BMSK                                                      0xff000000
#define HWIO_CALIBRATION70_CALIBRATION_2271_2264_SHFT                                                            0x18
#define HWIO_CALIBRATION70_ACD_NSP_DVM_TUR_BMSK                                                              0xffffff
#define HWIO_CALIBRATION70_ACD_NSP_DVM_TUR_SHFT                                                                   0x0

#define HWIO_CALIBRATION71_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c34)
#define HWIO_CALIBRATION71_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c34)
#define HWIO_CALIBRATION71_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION71_IN          \
        in_dword(HWIO_CALIBRATION71_ADDR)
#define HWIO_CALIBRATION71_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION71_ADDR, m)
#define HWIO_CALIBRATION71_CALIBRATION_2303_2302_BMSK                                                      0xc0000000
#define HWIO_CALIBRATION71_CALIBRATION_2303_2302_SHFT                                                            0x1e
#define HWIO_CALIBRATION71_CALIBATION_2302_2285_BMSK                                                       0x3ffff000
#define HWIO_CALIBRATION71_CALIBATION_2302_2285_SHFT                                                              0xc
#define HWIO_CALIBRATION71_CALIBRATION_2283_2278_BMSK                                                           0xfc0
#define HWIO_CALIBRATION71_CALIBRATION_2283_2278_SHFT                                                             0x6
#define HWIO_CALIBRATION71_CALIBATION_2277_2272_BMSK                                                             0x3f
#define HWIO_CALIBRATION71_CALIBATION_2277_2272_SHFT                                                              0x0

#define HWIO_CALIBRATION72_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c38)
#define HWIO_CALIBRATION72_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c38)
#define HWIO_CALIBRATION72_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION72_IN          \
        in_dword(HWIO_CALIBRATION72_ADDR)
#define HWIO_CALIBRATION72_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION72_ADDR, m)
#define HWIO_CALIBRATION72_CALIBRATION_2335_2316_BMSK                                                      0xfffff000
#define HWIO_CALIBRATION72_CALIBRATION_2335_2316_SHFT                                                             0xc
#define HWIO_CALIBRATION72_CPR12_SVS3_QUOT_MIN_BMSK                                                             0xfff
#define HWIO_CALIBRATION72_CPR12_SVS3_QUOT_MIN_SHFT                                                               0x0

#define HWIO_CALIBRATION73_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c3c)
#define HWIO_CALIBRATION73_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c3c)
#define HWIO_CALIBRATION73_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION73_IN          \
        in_dword(HWIO_CALIBRATION73_ADDR)
#define HWIO_CALIBRATION73_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION73_ADDR, m)
#define HWIO_CALIBRATION73_CALIBRATION_2367_2336_BMSK                                                      0xffffffff
#define HWIO_CALIBRATION73_CALIBRATION_2367_2336_SHFT                                                             0x0

#define HWIO_CALIBRATION74_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c40)
#define HWIO_CALIBRATION74_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c40)
#define HWIO_CALIBRATION74_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION74_IN          \
        in_dword(HWIO_CALIBRATION74_ADDR)
#define HWIO_CALIBRATION74_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION74_ADDR, m)
#define HWIO_CALIBRATION74_CALIBRATION_2399_2383_BMSK                                                      0xffff8000
#define HWIO_CALIBRATION74_CALIBRATION_2399_2383_SHFT                                                             0xf
#define HWIO_CALIBRATION74_CALIBATION_2382_BMSK                                                                0x4000
#define HWIO_CALIBRATION74_CALIBATION_2382_SHFT                                                                   0xe
#define HWIO_CALIBRATION74_CALIBRATION_2381_2368_BMSK                                                          0x3fff
#define HWIO_CALIBRATION74_CALIBRATION_2381_2368_SHFT                                                             0x0

#define HWIO_CALIBRATION75_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c44)
#define HWIO_CALIBRATION75_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c44)
#define HWIO_CALIBRATION75_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION75_IN          \
        in_dword(HWIO_CALIBRATION75_ADDR)
#define HWIO_CALIBRATION75_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION75_ADDR, m)
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS98_AUP1_BMSK                                                0x80000000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS98_AUP1_SHFT                                                      0x1f
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AG2_BMSK                                                 0x40000000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AG2_SHFT                                                       0x1e
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AG1_BMSK                                                 0x20000000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AG1_SHFT                                                       0x1d
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AU_BMSK                                                  0x10000000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AU_SHFT                                                        0x1c
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AU2_BMSK                                                  0x8000000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AU2_SHFT                                                       0x1b
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AU1_BMSK                                                  0x4000000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AU1_SHFT                                                       0x1a
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AUP_BMSK                                                  0x2000000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AUP_SHFT                                                       0x19
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AUP2_BMSK                                                 0x1000000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AUP2_SHFT                                                      0x18
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AUP1_BMSK                                                  0x800000
#define HWIO_CALIBRATION75_CPU_DYN_MEM_ACC_BITS65_AUP1_SHFT                                                      0x17
#define HWIO_CALIBRATION75_CALIBRATION_2422_2400_BMSK                                                        0x7fffff
#define HWIO_CALIBRATION75_CALIBRATION_2422_2400_SHFT                                                             0x0

#define HWIO_CALIBRATION76_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c48)
#define HWIO_CALIBRATION76_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c48)
#define HWIO_CALIBRATION76_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION76_IN          \
        in_dword(HWIO_CALIBRATION76_ADDR)
#define HWIO_CALIBRATION76_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION76_ADDR, m)
#define HWIO_CALIBRATION76_TSENS2_BASE0_BMSK                                                               0xffc00000
#define HWIO_CALIBRATION76_TSENS2_BASE0_SHFT                                                                     0x16
#define HWIO_CALIBRATION76_CALIBRATION_2453_2441_BMSK                                                        0x3ffe00
#define HWIO_CALIBRATION76_CALIBRATION_2453_2441_SHFT                                                             0x9
#define HWIO_CALIBRATION76_GFX_CDYN_REVISION_BMSK                                                               0x180
#define HWIO_CALIBRATION76_GFX_CDYN_REVISION_SHFT                                                                 0x7
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP8_BMSK                                                      0x40
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP8_SHFT                                                       0x6
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP7_BMSK                                                      0x20
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP7_SHFT                                                       0x5
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP6_BMSK                                                      0x10
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP6_SHFT                                                       0x4
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP5_BMSK                                                       0x8
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP5_SHFT                                                       0x3
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP4_BMSK                                                       0x4
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP4_SHFT                                                       0x2
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP3_BMSK                                                       0x2
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP3_SHFT                                                       0x1
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP2_BMSK                                                       0x1
#define HWIO_CALIBRATION76_CPU_DYN_MEM_ACC_BITS98_AUP2_SHFT                                                       0x0

#define HWIO_CALIBRATION77_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c4c)
#define HWIO_CALIBRATION77_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c4c)
#define HWIO_CALIBRATION77_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION77_IN          \
        in_dword(HWIO_CALIBRATION77_ADDR)
#define HWIO_CALIBRATION77_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION77_ADDR, m)
#define HWIO_CALIBRATION77_CALIBRATION_2495_2488_BMSK                                                      0xff000000
#define HWIO_CALIBRATION77_CALIBRATION_2495_2488_SHFT                                                            0x18
#define HWIO_CALIBRATION77_ACD_NSP_DVM_ENABLE_BMSK                                                           0xff8000
#define HWIO_CALIBRATION77_ACD_NSP_DVM_ENABLE_SHFT                                                                0xf
#define HWIO_CALIBRATION77_TSENS2_BASE1_BMSK                                                                   0x7fe0
#define HWIO_CALIBRATION77_TSENS2_BASE1_SHFT                                                                      0x5
#define HWIO_CALIBRATION77_ACD_NSP_REVISION_BIT_BMSK                                                             0x18
#define HWIO_CALIBRATION77_ACD_NSP_REVISION_BIT_SHFT                                                              0x3
#define HWIO_CALIBRATION77_CALIBRATION_2466_2464_BMSK                                                             0x7
#define HWIO_CALIBRATION77_CALIBRATION_2466_2464_SHFT                                                             0x0

#define HWIO_CALIBRATION78_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c50)
#define HWIO_CALIBRATION78_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c50)
#define HWIO_CALIBRATION78_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION78_IN          \
        in_dword(HWIO_CALIBRATION78_ADDR)
#define HWIO_CALIBRATION78_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION78_ADDR, m)
#define HWIO_CALIBRATION78_DDRSS_CH2CA_PNTUNE_HT_BMSK                                                      0xc0000000
#define HWIO_CALIBRATION78_DDRSS_CH2CA_PNTUNE_HT_SHFT                                                            0x1e
#define HWIO_CALIBRATION78_DDRSS_CH1DQ1_PNTUNE_HT_BMSK                                                     0x30000000
#define HWIO_CALIBRATION78_DDRSS_CH1DQ1_PNTUNE_HT_SHFT                                                           0x1c
#define HWIO_CALIBRATION78_DDRSS_CH1DQ0_PNTUNE_HT_BMSK                                                      0xc000000
#define HWIO_CALIBRATION78_DDRSS_CH1DQ0_PNTUNE_HT_SHFT                                                           0x1a
#define HWIO_CALIBRATION78_DDRSS_CH1CA_PNTUNE_HT_BMSK                                                       0x3000000
#define HWIO_CALIBRATION78_DDRSS_CH1CA_PNTUNE_HT_SHFT                                                            0x18
#define HWIO_CALIBRATION78_ACD_NSP_DVM_LSVSD1_BMSK                                                           0xffffff
#define HWIO_CALIBRATION78_ACD_NSP_DVM_LSVSD1_SHFT                                                                0x0

#define HWIO_CALIBRATION79_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c54)
#define HWIO_CALIBRATION79_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c54)
#define HWIO_CALIBRATION79_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION79_IN          \
        in_dword(HWIO_CALIBRATION79_ADDR)
#define HWIO_CALIBRATION79_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION79_ADDR, m)
#define HWIO_CALIBRATION79_DDRSS_CH0DQ1_PNTUNE_HT_BMSK                                                     0xc0000000
#define HWIO_CALIBRATION79_DDRSS_CH0DQ1_PNTUNE_HT_SHFT                                                           0x1e
#define HWIO_CALIBRATION79_DDRSS_CH0DQ0_PNTUNE_HT_BMSK                                                     0x30000000
#define HWIO_CALIBRATION79_DDRSS_CH0DQ0_PNTUNE_HT_SHFT                                                           0x1c
#define HWIO_CALIBRATION79_DDRSS_CH0CA_PNTUNE_HT_BMSK                                                       0xc000000
#define HWIO_CALIBRATION79_DDRSS_CH0CA_PNTUNE_HT_SHFT                                                            0x1a
#define HWIO_CALIBRATION79_DDRSS_CH3DQ1_PNTUNE_RT_BMSK                                                      0x3000000
#define HWIO_CALIBRATION79_DDRSS_CH3DQ1_PNTUNE_RT_SHFT                                                           0x18
#define HWIO_CALIBRATION79_ACD_NSP_DVM_LSVS_BMSK                                                             0xffffff
#define HWIO_CALIBRATION79_ACD_NSP_DVM_LSVS_SHFT                                                                  0x0

#define HWIO_CALIBRATION80_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c58)
#define HWIO_CALIBRATION80_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c58)
#define HWIO_CALIBRATION80_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION80_IN          \
        in_dword(HWIO_CALIBRATION80_ADDR)
#define HWIO_CALIBRATION80_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION80_ADDR, m)
#define HWIO_CALIBRATION80_DDRSS_CH3DQ0_PNTUNE_RT_BMSK                                                     0xc0000000
#define HWIO_CALIBRATION80_DDRSS_CH3DQ0_PNTUNE_RT_SHFT                                                           0x1e
#define HWIO_CALIBRATION80_DDRSS_CH3CA_PNTUNE_RT_BMSK                                                      0x30000000
#define HWIO_CALIBRATION80_DDRSS_CH3CA_PNTUNE_RT_SHFT                                                            0x1c
#define HWIO_CALIBRATION80_DDRSS_CH2DQ1_PNTUNE_RT_BMSK                                                      0xc000000
#define HWIO_CALIBRATION80_DDRSS_CH2DQ1_PNTUNE_RT_SHFT                                                           0x1a
#define HWIO_CALIBRATION80_DDRSS_CH2DQ0_PNTUNE_RT_BMSK                                                      0x3000000
#define HWIO_CALIBRATION80_DDRSS_CH2DQ0_PNTUNE_RT_SHFT                                                           0x18
#define HWIO_CALIBRATION80_ACD_NSP_DVM_SVS_BMSK                                                              0xffffff
#define HWIO_CALIBRATION80_ACD_NSP_DVM_SVS_SHFT                                                                   0x0

#define HWIO_CALIBRATION81_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c5c)
#define HWIO_CALIBRATION81_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c5c)
#define HWIO_CALIBRATION81_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION81_IN          \
        in_dword(HWIO_CALIBRATION81_ADDR)
#define HWIO_CALIBRATION81_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION81_ADDR, m)
#define HWIO_CALIBRATION81_CALIBRATION_2623_2616_BMSK                                                      0xff000000
#define HWIO_CALIBRATION81_CALIBRATION_2623_2616_SHFT                                                            0x18
#define HWIO_CALIBRATION81_ACD_NSP_DVM_SVSL1_BMSK                                                            0xffffff
#define HWIO_CALIBRATION81_ACD_NSP_DVM_SVSL1_SHFT                                                                 0x0

#define HWIO_CALIBRATION82_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c60)
#define HWIO_CALIBRATION82_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c60)
#define HWIO_CALIBRATION82_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION82_IN          \
        in_dword(HWIO_CALIBRATION82_ADDR)
#define HWIO_CALIBRATION82_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION82_ADDR, m)
#define HWIO_CALIBRATION82_DDRSS_CH2CA_PNTUNE_RT_BMSK                                                      0xc0000000
#define HWIO_CALIBRATION82_DDRSS_CH2CA_PNTUNE_RT_SHFT                                                            0x1e
#define HWIO_CALIBRATION82_DDRSS_CH1DQ1_PNTUNE_RT_BMSK                                                     0x30000000
#define HWIO_CALIBRATION82_DDRSS_CH1DQ1_PNTUNE_RT_SHFT                                                           0x1c
#define HWIO_CALIBRATION82_DDRSS_CH1DQ0_PNTUNE_RT_BMSK                                                      0xc000000
#define HWIO_CALIBRATION82_DDRSS_CH1DQ0_PNTUNE_RT_SHFT                                                           0x1a
#define HWIO_CALIBRATION82_DDRSS_CH1CA_PNTUNE_RT_BMSK                                                       0x3000000
#define HWIO_CALIBRATION82_DDRSS_CH1CA_PNTUNE_RT_SHFT                                                            0x18
#define HWIO_CALIBRATION82_ACD_NSP_DVM_NOM_BMSK                                                              0xffffff
#define HWIO_CALIBRATION82_ACD_NSP_DVM_NOM_SHFT                                                                   0x0

#define HWIO_CALIBRATION83_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c64)
#define HWIO_CALIBRATION83_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c64)
#define HWIO_CALIBRATION83_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION83_IN          \
        in_dword(HWIO_CALIBRATION83_ADDR)
#define HWIO_CALIBRATION83_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION83_ADDR, m)
#define HWIO_CALIBRATION83_CALIBRATION_2687_BMSK                                                           0x80000000
#define HWIO_CALIBRATION83_CALIBRATION_2687_SHFT                                                                 0x1f
#define HWIO_CALIBRATION83_DDRSS_EW_FUSE_1_BMSK                                                            0x7f000000
#define HWIO_CALIBRATION83_DDRSS_EW_FUSE_1_SHFT                                                                  0x18
#define HWIO_CALIBRATION83_ACD_NSP_DVM_NOML1_BMSK                                                            0xffffff
#define HWIO_CALIBRATION83_ACD_NSP_DVM_NOML1_SHFT                                                                 0x0

#define HWIO_CALIBRATION84_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c68)
#define HWIO_CALIBRATION84_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c68)
#define HWIO_CALIBRATION84_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION84_IN          \
        in_dword(HWIO_CALIBRATION84_ADDR)
#define HWIO_CALIBRATION84_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION84_ADDR, m)
#define HWIO_CALIBRATION84_CALIBRATION_2719_BMSK                                                           0x80000000
#define HWIO_CALIBRATION84_CALIBRATION_2719_SHFT                                                                 0x1f
#define HWIO_CALIBRATION84_DDRSS_CH0DQ1_PNTUNE_RT_BMSK                                                     0x60000000
#define HWIO_CALIBRATION84_DDRSS_CH0DQ1_PNTUNE_RT_SHFT                                                           0x1d
#define HWIO_CALIBRATION84_DDRSS_CH0DQ0_PNTUNE_RT_BMSK                                                     0x18000000
#define HWIO_CALIBRATION84_DDRSS_CH0DQ0_PNTUNE_RT_SHFT                                                           0x1b
#define HWIO_CALIBRATION84_DDRSS_CH0CA_PNTUNE_RT_BMSK                                                       0x6000000
#define HWIO_CALIBRATION84_DDRSS_CH0CA_PNTUNE_RT_SHFT                                                            0x19
#define HWIO_CALIBRATION84_DDRSS_TP_REV_CTRL_BMSK                                                           0x1f00000
#define HWIO_CALIBRATION84_DDRSS_TP_REV_CTRL_SHFT                                                                0x14
#define HWIO_CALIBRATION84_DDRSS_EH_FUSE_2_BMSK                                                               0xfe000
#define HWIO_CALIBRATION84_DDRSS_EH_FUSE_2_SHFT                                                                   0xd
#define HWIO_CALIBRATION84_DDRSS_EH_FUSE_1_BMSK                                                                0x1fc0
#define HWIO_CALIBRATION84_DDRSS_EH_FUSE_1_SHFT                                                                   0x6
#define HWIO_CALIBRATION84_CALIBRATION_2693_2688_BMSK                                                            0x3f
#define HWIO_CALIBRATION84_CALIBRATION_2693_2688_SHFT                                                             0x0

#define HWIO_CALIBRATION85_ADDR                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE      + 0x00000c6c)
#define HWIO_CALIBRATION85_OFFS                                                                            (FUSE_CONTROLLER_SW_RANGE4_REG_BASE_OFFS + 0x00000c6c)
#define HWIO_CALIBRATION85_RMSK                                                                            0xffffffff
#define HWIO_CALIBRATION85_IN          \
        in_dword(HWIO_CALIBRATION85_ADDR)
#define HWIO_CALIBRATION85_INM(m)      \
        in_dword_masked(HWIO_CALIBRATION85_ADDR, m)
#define HWIO_CALIBRATION85_GFX_FT_BMSK                                                                     0x80000000
#define HWIO_CALIBRATION85_GFX_FT_SHFT                                                                           0x1f
#define HWIO_CALIBRATION85_GFX_WS_BMSK                                                                     0x40000000
#define HWIO_CALIBRATION85_GFX_WS_SHFT                                                                           0x1e
#define HWIO_CALIBRATION85_VSENS_FT_BMSK                                                                   0x20000000
#define HWIO_CALIBRATION85_VSENS_FT_SHFT                                                                         0x1d
#define HWIO_CALIBRATION85_VSENS_WS_BMSK                                                                   0x10000000
#define HWIO_CALIBRATION85_VSENS_WS_SHFT                                                                         0x1c
#define HWIO_CALIBRATION85_ACD_NSP_FT_BMSK                                                                  0x8000000
#define HWIO_CALIBRATION85_ACD_NSP_FT_SHFT                                                                       0x1b
#define HWIO_CALIBRATION85_ACD_NSP_WS_BMSK                                                                  0x4000000
#define HWIO_CALIBRATION85_ACD_NSP_WS_SHFT                                                                       0x1a
#define HWIO_CALIBRATION85_DACC_FT_BMSK                                                                     0x2000000
#define HWIO_CALIBRATION85_DACC_FT_SHFT                                                                          0x19
#define HWIO_CALIBRATION85_DACC_WS_BMSK                                                                     0x1000000
#define HWIO_CALIBRATION85_DACC_WS_SHFT                                                                          0x18
#define HWIO_CALIBRATION85_GNSS_FT_BMSK                                                                      0x800000
#define HWIO_CALIBRATION85_GNSS_FT_SHFT                                                                          0x17
#define HWIO_CALIBRATION85_GNSS_WS_BMSK                                                                      0x400000
#define HWIO_CALIBRATION85_GNSS_WS_SHFT                                                                          0x16
#define HWIO_CALIBRATION85_USB_FT_BMSK                                                                       0x200000
#define HWIO_CALIBRATION85_USB_FT_SHFT                                                                           0x15
#define HWIO_CALIBRATION85_USB_WS_BMSK                                                                       0x100000
#define HWIO_CALIBRATION85_USB_WS_SHFT                                                                           0x14
#define HWIO_CALIBRATION85_REFGEN_FT_BMSK                                                                     0x80000
#define HWIO_CALIBRATION85_REFGEN_FT_SHFT                                                                        0x13
#define HWIO_CALIBRATION85_REFGEN_WS_BMSK                                                                     0x40000
#define HWIO_CALIBRATION85_REFGEN_WS_SHFT                                                                        0x12
#define HWIO_CALIBRATION85_CPR_FT_BMSK                                                                        0x20000
#define HWIO_CALIBRATION85_CPR_FT_SHFT                                                                           0x11
#define HWIO_CALIBRATION85_CPR_WS_BMSK                                                                        0x10000
#define HWIO_CALIBRATION85_CPR_WS_SHFT                                                                           0x10
#define HWIO_CALIBRATION85_LRET_FT_BMSK                                                                        0x8000
#define HWIO_CALIBRATION85_LRET_FT_SHFT                                                                           0xf
#define HWIO_CALIBRATION85_LRET_WS_BMSK                                                                        0x4000
#define HWIO_CALIBRATION85_LRET_WS_SHFT                                                                           0xe
#define HWIO_CALIBRATION85_MRET_FT_BMSK                                                                        0x2000
#define HWIO_CALIBRATION85_MRET_FT_SHFT                                                                           0xd
#define HWIO_CALIBRATION85_MRET_WS_BMSK                                                                        0x1000
#define HWIO_CALIBRATION85_MRET_WS_SHFT                                                                           0xc
#define HWIO_CALIBRATION85_AOSS_FT_BMSK                                                                         0x800
#define HWIO_CALIBRATION85_AOSS_FT_SHFT                                                                           0xb
#define HWIO_CALIBRATION85_AOSS_WS_BMSK                                                                         0x400
#define HWIO_CALIBRATION85_AOSS_WS_SHFT                                                                           0xa
#define HWIO_CALIBRATION85_DDR_FT_BMSK                                                                          0x200
#define HWIO_CALIBRATION85_DDR_FT_SHFT                                                                            0x9
#define HWIO_CALIBRATION85_DDR_WS_BMSK                                                                          0x100
#define HWIO_CALIBRATION85_DDR_WS_SHFT                                                                            0x8
#define HWIO_CALIBRATION85_IDDQ_FT_BMSK                                                                          0x80
#define HWIO_CALIBRATION85_IDDQ_FT_SHFT                                                                           0x7
#define HWIO_CALIBRATION85_IDDQ_WS_BMSK                                                                          0x40
#define HWIO_CALIBRATION85_IDDQ_WS_SHFT                                                                           0x6
#define HWIO_CALIBRATION85_DVS_FT_BMSK                                                                           0x20
#define HWIO_CALIBRATION85_DVS_FT_SHFT                                                                            0x5
#define HWIO_CALIBRATION85_DVS_WS_BMSK                                                                           0x10
#define HWIO_CALIBRATION85_DVS_WS_SHFT                                                                            0x4
#define HWIO_CALIBRATION85_TSENS_FT_BMSK                                                                          0x8
#define HWIO_CALIBRATION85_TSENS_FT_SHFT                                                                          0x3
#define HWIO_CALIBRATION85_TSENS_WS_BMSK                                                                          0x4
#define HWIO_CALIBRATION85_TSENS_WS_SHFT                                                                          0x2
#define HWIO_CALIBRATION85_QFPROM_FT_BMSK                                                                         0x2
#define HWIO_CALIBRATION85_QFPROM_FT_SHFT                                                                         0x1
#define HWIO_CALIBRATION85_QFPROM_WS_BMSK                                                                         0x1
#define HWIO_CALIBRATION85_QFPROM_WS_SHFT                                                                         0x0


#endif /* __CPR_FUSES_HWIO_H__ */
