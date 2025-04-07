#ifndef __SPSS_HWIO_H__
#define __SPSS_HWIO_H__
/*
===========================================================================
*/
/**
    @file spss_hwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SC8380XP (Hamoa) [hamoa_v1.0_p3q1r83_F04]
 
    This file contains HWIO register definitions for the following modules:
        SP_CNOC_SP_SCSR_REGS


    Generation parameters: 
    { 'explicit-addressing': True,
      'filename': 'spss_hwio.h',
      'header': '#include "HALhwio.h"\n#include "msmhwiobase.h"',
      'modules': ['SP_CNOC_SP_SCSR_REGS'],
      'output-offsets': True}
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

#include "HALhwio.h"
#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: SP_CNOC_SP_SCSR_REGS
 *--------------------------------------------------------------------------*/

#define SP_CNOC_SP_SCSR_REGS_REG_BASE                                                       (SP_SCSR_BASE      + 0x00080000)
#define SP_CNOC_SP_SCSR_REGS_REG_BASE_SIZE                                                  0x10000
#define SP_CNOC_SP_SCSR_REGS_REG_BASE_USED                                                  0xb014
#define SP_CNOC_SP_SCSR_REGS_REG_BASE_OFFS                                                  0x00080000

#define HWIO_SP_CNOC_SP_SCSR_HW_VERSION_ADDR(x)                                             ((x) + 0x0)
#define HWIO_SP_CNOC_SP_SCSR_HW_VERSION_OFFS                                                (0x0)
#define HWIO_SP_CNOC_SP_SCSR_HW_VERSION_RMSK                                                0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_HW_VERSION_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_HW_VERSION_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_HW_VERSION_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_HW_VERSION_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_HW_VERSION_MAJOR_VERSION_BMSK                                  0xff000000
#define HWIO_SP_CNOC_SP_SCSR_HW_VERSION_MAJOR_VERSION_SHFT                                          24
#define HWIO_SP_CNOC_SP_SCSR_HW_VERSION_MINOR_VERSION_BMSK                                    0xff0000
#define HWIO_SP_CNOC_SP_SCSR_HW_VERSION_MINOR_VERSION_SHFT                                          16
#define HWIO_SP_CNOC_SP_SCSR_HW_VERSION_STEP_VERSION_BMSK                                       0xffff
#define HWIO_SP_CNOC_SP_SCSR_HW_VERSION_STEP_VERSION_SHFT                                            0

#define HWIO_SP_CNOC_SP_CORE_HW_VERSION_ADDR(x)                                             ((x) + 0x4)
#define HWIO_SP_CNOC_SP_CORE_HW_VERSION_OFFS                                                (0x4)
#define HWIO_SP_CNOC_SP_CORE_HW_VERSION_RMSK                                                0xffffffff
#define HWIO_SP_CNOC_SP_CORE_HW_VERSION_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_CORE_HW_VERSION_ADDR(x))
#define HWIO_SP_CNOC_SP_CORE_HW_VERSION_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_CORE_HW_VERSION_ADDR(x), m)
#define HWIO_SP_CNOC_SP_CORE_HW_VERSION_MAJOR_VERSION_BMSK                                  0xff000000
#define HWIO_SP_CNOC_SP_CORE_HW_VERSION_MAJOR_VERSION_SHFT                                          24
#define HWIO_SP_CNOC_SP_CORE_HW_VERSION_MINOR_VERSION_BMSK                                    0xff0000
#define HWIO_SP_CNOC_SP_CORE_HW_VERSION_MINOR_VERSION_SHFT                                          16
#define HWIO_SP_CNOC_SP_CORE_HW_VERSION_STEP_VERSION_BMSK                                       0xffff
#define HWIO_SP_CNOC_SP_CORE_HW_VERSION_STEP_VERSION_SHFT                                            0

#define HWIO_SP_CNOC_SP_SCSR_GP_SCSR2CORE_ADDR(x)                                           ((x) + 0x8)
#define HWIO_SP_CNOC_SP_SCSR_GP_SCSR2CORE_OFFS                                              (0x8)
#define HWIO_SP_CNOC_SP_SCSR_GP_SCSR2CORE_RMSK                                              0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_GP_SCSR2CORE_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_GP_SCSR2CORE_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_GP_SCSR2CORE_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_GP_SCSR2CORE_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_GP_SCSR2CORE_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_GP_SCSR2CORE_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_GP_SCSR2CORE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_GP_SCSR2CORE_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_GP_SCSR2CORE_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_GP_SCSR2CORE_GP_BMSK                                           0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_GP_SCSR2CORE_GP_SHFT                                                    0

#define HWIO_SP_CNOC_SP_SCSR_GP_CORE2SCSR_ADDR(x)                                           ((x) + 0xc)
#define HWIO_SP_CNOC_SP_SCSR_GP_CORE2SCSR_OFFS                                              (0xc)
#define HWIO_SP_CNOC_SP_SCSR_GP_CORE2SCSR_RMSK                                              0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_GP_CORE2SCSR_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_GP_CORE2SCSR_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_GP_CORE2SCSR_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_GP_CORE2SCSR_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_GP_CORE2SCSR_GP_BMSK                                           0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_GP_CORE2SCSR_GP_SHFT                                                    0

#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_L_ADDR(x)                                       ((x) + 0x10)
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_L_OFFS                                          (0x10)
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_L_RMSK                                          0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_L_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_L_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_L_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_L_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_L_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_L_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_L_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_L_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_L_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_L_ADDR_BMSK                                     0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_L_ADDR_SHFT                                              0

#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_U_ADDR(x)                                       ((x) + 0x14)
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_U_OFFS                                          (0x14)
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_U_RMSK                                              0xffff
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_U_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_U_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_U_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_U_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_U_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_U_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_U_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_U_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_U_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_U_ADDR_BMSK                                         0xffff
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ADDR_U_ADDR_SHFT                                              0

#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_SIZE_ADDR(x)                                         ((x) + 0x18)
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_SIZE_OFFS                                            (0x18)
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_SIZE_RMSK                                               0xfffff
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_SIZE_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_TEST_CODE_SIZE_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_SIZE_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_TEST_CODE_SIZE_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_SIZE_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_TEST_CODE_SIZE_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_SIZE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_TEST_CODE_SIZE_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_TEST_CODE_SIZE_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_SIZE_SIZE_BMSK                                          0xfffff
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_SIZE_SIZE_SHFT                                                0

#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ENTRY_OFFSET_ADDR(x)                                 ((x) + 0x1c)
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ENTRY_OFFSET_OFFS                                    (0x1c)
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ENTRY_OFFSET_RMSK                                       0xfffff
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ENTRY_OFFSET_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ENTRY_OFFSET_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ENTRY_OFFSET_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ENTRY_OFFSET_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ENTRY_OFFSET_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ENTRY_OFFSET_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ENTRY_OFFSET_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ENTRY_OFFSET_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ENTRY_OFFSET_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ENTRY_OFFSET_OFFSET_BMSK                                0xfffff
#define HWIO_SP_CNOC_SP_SCSR_TEST_CODE_ENTRY_OFFSET_OFFSET_SHFT                                      0

#define HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_ADDR(x)                                               ((x) + 0x20)
#define HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_OFFS                                                  (0x20)
#define HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_RMSK                                                    0xffffff
#define HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_QFPROM_BLOW_TIMER_BMSK                                  0xfff000
#define HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_QFPROM_BLOW_TIMER_SHFT                                        12
#define HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_QFPROM_ACCEL_GATE_LAST_BMSK                                0x800
#define HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_QFPROM_ACCEL_GATE_LAST_SHFT                                   11
#define HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_QFPROM_ACCEL_TRIPPT_SEL_BMSK                               0x700
#define HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_QFPROM_ACCEL_TRIPPT_SEL_SHFT                                   8
#define HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_QFPROM_ACCEL_BMSK                                           0xff
#define HWIO_SP_CNOC_SP_SCSR_OTP_CTRL_QFPROM_ACCEL_SHFT                                              0

#define HWIO_SP_CNOC_SP_SCSR_OTP_STATUS_ADDR(x)                                             ((x) + 0x24)
#define HWIO_SP_CNOC_SP_SCSR_OTP_STATUS_OFFS                                                (0x24)
#define HWIO_SP_CNOC_SP_SCSR_OTP_STATUS_RMSK                                                   0x300ff
#define HWIO_SP_CNOC_SP_SCSR_OTP_STATUS_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_OTP_STATUS_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_OTP_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_OTP_STATUS_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_OTP_STATUS_QFPROM_BLOW_STATUS_WR_ERR_BMSK                         0x20000
#define HWIO_SP_CNOC_SP_SCSR_OTP_STATUS_QFPROM_BLOW_STATUS_WR_ERR_SHFT                              17
#define HWIO_SP_CNOC_SP_SCSR_OTP_STATUS_QFPROM_BLOW_STATUS_BUSY_BMSK                           0x10000
#define HWIO_SP_CNOC_SP_SCSR_OTP_STATUS_QFPROM_BLOW_STATUS_BUSY_SHFT                                16
#define HWIO_SP_CNOC_SP_SCSR_OTP_STATUS_QFPROM_HW_KEY_BLOW_STATUS_BMSK                            0xff
#define HWIO_SP_CNOC_SP_SCSR_OTP_STATUS_QFPROM_HW_KEY_BLOW_STATUS_SHFT                               0

#define HWIO_SP_CNOC_SP_SCSR_OTP_ZEROIZE_EN_ADDR(x)                                         ((x) + 0x28)
#define HWIO_SP_CNOC_SP_SCSR_OTP_ZEROIZE_EN_OFFS                                            (0x28)
#define HWIO_SP_CNOC_SP_SCSR_OTP_ZEROIZE_EN_RMSK                                                   0x1
#define HWIO_SP_CNOC_SP_SCSR_OTP_ZEROIZE_EN_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_OTP_ZEROIZE_EN_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_OTP_ZEROIZE_EN_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_OTP_ZEROIZE_EN_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_OTP_ZEROIZE_EN_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_OTP_ZEROIZE_EN_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_OTP_ZEROIZE_EN_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_OTP_ZEROIZE_EN_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_OTP_ZEROIZE_EN_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_OTP_ZEROIZE_EN_EN_BMSK                                                0x1
#define HWIO_SP_CNOC_SP_SCSR_OTP_ZEROIZE_EN_EN_SHFT                                                  0

#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_0_ADDR(x)                                        ((x) + 0x30)
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_0_OFFS                                           (0x30)
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_0_RMSK                                           0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_0_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_0_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_0_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_0_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_0_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_0_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_0_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_0_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_0_ACC_VALUE_BMSK                                 0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_0_ACC_VALUE_SHFT                                          0

#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_1_ADDR(x)                                        ((x) + 0x34)
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_1_OFFS                                           (0x34)
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_1_RMSK                                           0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_1_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_1_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_1_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_1_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_1_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_1_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_1_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_1_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_1_ACC_VALUE_BMSK                                 0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_1_ACC_VALUE_SHFT                                          0

#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_2_ADDR(x)                                        ((x) + 0x38)
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_2_OFFS                                           (0x38)
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_2_RMSK                                               0xffff
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_2_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_2_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_2_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_2_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_2_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_2_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_2_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_2_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_2_ACC_VALUE_BMSK                                     0xffff
#define HWIO_SP_CNOC_SP_SCSR_SW_MEMORY_ACC_2_ACC_VALUE_SHFT                                          0

#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_0_ADDR(x)                                 ((x) + 0x40)
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_0_OFFS                                    (0x40)
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_0_RMSK                                    0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_0_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_0_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_0_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_0_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_0_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_0_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_0_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_0_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_0_VALUE_BMSK                              0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_0_VALUE_SHFT                                       0

#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_1_ADDR(x)                                 ((x) + 0x44)
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_1_OFFS                                    (0x44)
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_1_RMSK                                    0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_1_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_1_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_1_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_1_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_1_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_1_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_1_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_1_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_1_VALUE_BMSK                              0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_1_VALUE_SHFT                                       0

#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_2_ADDR(x)                                 ((x) + 0x48)
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_2_OFFS                                    (0x48)
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_2_RMSK                                    0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_2_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_2_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_2_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_2_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_2_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_2_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_2_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_2_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_2_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_2_VALUE_BMSK                              0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_2_VALUE_SHFT                                       0

#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_3_ADDR(x)                                 ((x) + 0x4c)
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_3_OFFS                                    (0x4c)
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_3_RMSK                                    0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_3_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_3_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_3_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_3_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_3_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_3_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_3_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_3_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_3_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_3_VALUE_BMSK                              0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_TOE_DEBUG_UNLOCK_KEY_3_VALUE_SHFT                                       0

#define HWIO_SP_CNOC_SP_SCSR_NONSEC_BOOT_OVERRIDE_ADDR(x)                                   ((x) + 0x50)
#define HWIO_SP_CNOC_SP_SCSR_NONSEC_BOOT_OVERRIDE_OFFS                                      (0x50)
#define HWIO_SP_CNOC_SP_SCSR_NONSEC_BOOT_OVERRIDE_RMSK                                             0x1
#define HWIO_SP_CNOC_SP_SCSR_NONSEC_BOOT_OVERRIDE_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_NONSEC_BOOT_OVERRIDE_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_NONSEC_BOOT_OVERRIDE_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_NONSEC_BOOT_OVERRIDE_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_NONSEC_BOOT_OVERRIDE_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_NONSEC_BOOT_OVERRIDE_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_NONSEC_BOOT_OVERRIDE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_NONSEC_BOOT_OVERRIDE_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_NONSEC_BOOT_OVERRIDE_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_NONSEC_BOOT_OVERRIDE_VALUE_BMSK                                       0x1
#define HWIO_SP_CNOC_SP_SCSR_NONSEC_BOOT_OVERRIDE_VALUE_SHFT                                         0

#define HWIO_SP_CNOC_SP_SCSR_FEAT_DEBUG_EN_ADDR(x)                                          ((x) + 0x54)
#define HWIO_SP_CNOC_SP_SCSR_FEAT_DEBUG_EN_OFFS                                             (0x54)
#define HWIO_SP_CNOC_SP_SCSR_FEAT_DEBUG_EN_RMSK                                                   0xff
#define HWIO_SP_CNOC_SP_SCSR_FEAT_DEBUG_EN_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_FEAT_DEBUG_EN_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_FEAT_DEBUG_EN_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_FEAT_DEBUG_EN_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_FEAT_DEBUG_EN_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_FEAT_DEBUG_EN_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_FEAT_DEBUG_EN_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_FEAT_DEBUG_EN_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_FEAT_DEBUG_EN_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_FEAT_DEBUG_EN_VALUE_BMSK                                             0xff
#define HWIO_SP_CNOC_SP_SCSR_FEAT_DEBUG_EN_VALUE_SHFT                                                0

#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_L_ADDR(x)                                        ((x) + 0x1000)
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_L_OFFS                                           (0x1000)
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_L_RMSK                                           0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_L_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_L_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_L_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_L_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_L_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_L_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_L_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_L_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_L_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_L_ADDR_BMSK                                      0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_L_ADDR_SHFT                                               0

#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_U_ADDR(x)                                        ((x) + 0x1004)
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_U_OFFS                                           (0x1004)
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_U_RMSK                                               0xffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_U_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_U_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_U_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_U_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_U_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_U_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_U_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_U_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_U_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_U_ADDR_BMSK                                          0xffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_ADDR_U_ADDR_SHFT                                               0

#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_SIZE_ADDR(x)                                          ((x) + 0x1008)
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_SIZE_OFFS                                             (0x1008)
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_SIZE_RMSK                                                0xfffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_SIZE_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_RMB_CODE_SIZE_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_SIZE_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RMB_CODE_SIZE_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_SIZE_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RMB_CODE_SIZE_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_SIZE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_RMB_CODE_SIZE_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_RMB_CODE_SIZE_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_SIZE_SIZE_BMSK                                           0xfffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_CODE_SIZE_SIZE_SHFT                                                 0

#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_L_ADDR(x)                                    ((x) + 0x100c)
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_L_OFFS                                       (0x100c)
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_L_RMSK                                       0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_L_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_L_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_L_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_L_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_L_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_L_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_L_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_L_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_L_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_L_ADDR_BMSK                                  0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_L_ADDR_SHFT                                           0

#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_U_ADDR(x)                                    ((x) + 0x1010)
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_U_OFFS                                       (0x1010)
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_U_RMSK                                           0xffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_U_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_U_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_U_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_U_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_U_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_U_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_U_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_U_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_U_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_U_ADDR_BMSK                                      0xffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_ADDR_U_ADDR_SHFT                                           0

#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_SIZE_ADDR(x)                                      ((x) + 0x1014)
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_SIZE_OFFS                                         (0x1014)
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_SIZE_RMSK                                            0xfffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_SIZE_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_SIZE_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_SIZE_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_SIZE_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_SIZE_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_SIZE_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_SIZE_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_SIZE_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_SIZE_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_SIZE_SIZE_BMSK                                       0xfffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_RAM_DUMP_SIZE_SIZE_SHFT                                             0

#define HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_ADDR(x)                                          ((x) + 0x1018)
#define HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_OFFS                                             (0x1018)
#define HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_RMSK                                                    0xf
#define HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_CPU_BOOT_EN_BMSK                                        0x8
#define HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_CPU_BOOT_EN_SHFT                                          3
#define HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_RAM_WIPE_EN_BMSK                                        0x4
#define HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_RAM_WIPE_EN_SHFT                                          2
#define HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_GDSC_BRINGUP_EN_BMSK                                    0x2
#define HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_GDSC_BRINGUP_EN_SHFT                                      1
#define HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_COLD_BOOT_EN_BMSK                                       0x1
#define HWIO_SP_CNOC_SP_SCSR_RMB_BOOT_CTRL_COLD_BOOT_EN_SHFT                                         0

#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_ADDR(x)                                  ((x) + 0x101c)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_OFFS                                     (0x101c)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_RMSK                                      0x703000f
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_COLD_BOOT_POWER_CONTROL_BMSK              0x4000000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_COLD_BOOT_POWER_CONTROL_SHFT                     26
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_PBL_DONE_BMSK                             0x2000000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_PBL_DONE_SHFT                                    25
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_SW_INIT_DONE_BMSK                         0x1000000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_SW_INIT_DONE_SHFT                                24
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_SPSS_FIRST_PASS_RESET_BMSK                  0x20000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_SPSS_FIRST_PASS_RESET_SHFT                       17
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_SPSS_INT_ALT_RESET_BMSK                     0x10000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_SPSS_INT_ALT_RESET_SHFT                          16
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_CPU_BOOT_DONE_BMSK                              0x8
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_CPU_BOOT_DONE_SHFT                                3
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_RAM_WIPE_DONE_BMSK                              0x4
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_RAM_WIPE_DONE_SHFT                                2
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_GDSC_BRINGUP_DONE_BMSK                          0x2
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_GDSC_BRINGUP_DONE_SHFT                            1
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_COLD_BOOT_DONE_BMSK                             0x1
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_STATUS_COLD_BOOT_DONE_SHFT                               0

#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_ADDR(x)                                     ((x) + 0x1020)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_OFFS                                        (0x1020)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_RMSK                                         0x703000f
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_COLD_BOOT_POWER_CONTROL_BMSK                 0x4000000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_COLD_BOOT_POWER_CONTROL_SHFT                        26
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_PBL_DONE_BMSK                                0x2000000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_PBL_DONE_SHFT                                       25
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_SW_INIT_DONE_BMSK                            0x1000000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_SW_INIT_DONE_SHFT                                   24
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_SPSS_FIRST_PASS_RESET_BMSK                     0x20000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_SPSS_FIRST_PASS_RESET_SHFT                          17
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_SPSS_INT_ALT_RESET_BMSK                        0x10000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_SPSS_INT_ALT_RESET_SHFT                             16
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_CPU_BOOT_DONE_BMSK                                 0x8
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_CPU_BOOT_DONE_SHFT                                   3
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_RAM_WIPE_DONE_BMSK                                 0x4
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_RAM_WIPE_DONE_SHFT                                   2
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_GDSC_BRINGUP_DONE_BMSK                             0x2
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_GDSC_BRINGUP_DONE_SHFT                               1
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_COLD_BOOT_DONE_BMSK                                0x1
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_SET_COLD_BOOT_DONE_SHFT                                  0

#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_ADDR(x)                                     ((x) + 0x1024)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_OFFS                                        (0x1024)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_RMSK                                         0x703000f
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_COLD_BOOT_POWER_CONTROL_BMSK                 0x4000000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_COLD_BOOT_POWER_CONTROL_SHFT                        26
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_PBL_DONE_BMSK                                0x2000000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_PBL_DONE_SHFT                                       25
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_SW_INIT_DONE_BMSK                            0x1000000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_SW_INIT_DONE_SHFT                                   24
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_SPSS_FIRST_PASS_RESET_BMSK                     0x20000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_SPSS_FIRST_PASS_RESET_SHFT                          17
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_SPSS_INT_ALT_RESET_BMSK                        0x10000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_SPSS_INT_ALT_RESET_SHFT                             16
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_CPU_BOOT_DONE_BMSK                                 0x8
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_CPU_BOOT_DONE_SHFT                                   3
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_RAM_WIPE_DONE_BMSK                                 0x4
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_RAM_WIPE_DONE_SHFT                                   2
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_GDSC_BRINGUP_DONE_BMSK                             0x2
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_GDSC_BRINGUP_DONE_SHFT                               1
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_COLD_BOOT_DONE_BMSK                                0x1
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_CLR_COLD_BOOT_DONE_SHFT                                  0

#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_ADDR(x)                                    ((x) + 0x1028)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_OFFS                                       (0x1028)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_RMSK                                        0x703000f
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_COLD_BOOT_POWER_CONTROL_BMSK                0x4000000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_COLD_BOOT_POWER_CONTROL_SHFT                       26
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_PBL_DONE_BMSK                               0x2000000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_PBL_DONE_SHFT                                      25
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_SW_INIT_DONE_BMSK                           0x1000000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_SW_INIT_DONE_SHFT                                  24
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_SPSS_FIRST_PASS_RESET_BMSK                    0x20000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_SPSS_FIRST_PASS_RESET_SHFT                         17
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_SPSS_INT_ALT_RESET_BMSK                       0x10000
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_SPSS_INT_ALT_RESET_SHFT                            16
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_CPU_BOOT_DONE_BMSK                                0x8
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_CPU_BOOT_DONE_SHFT                                  3
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_RAM_WIPE_DONE_BMSK                                0x4
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_RAM_WIPE_DONE_SHFT                                  2
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_GDSC_BRINGUP_DONE_BMSK                            0x2
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_GDSC_BRINGUP_DONE_SHFT                              1
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_COLD_BOOT_DONE_BMSK                               0x1
#define HWIO_SP_CNOC_SP_SCSR_RMB_SP2SOC_IRQ_MASK_COLD_BOOT_DONE_SHFT                                 0

#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_STATUS_ADDR(x)                                  ((x) + 0x102c)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_STATUS_OFFS                                     (0x102c)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_STATUS_RMSK                                            0xf
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_STATUS_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_STATUS_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_STATUS_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_STATUS_IRQ_BMSK                                        0xf
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_STATUS_IRQ_SHFT                                          0

#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_SET_ADDR(x)                                     ((x) + 0x1030)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_SET_OFFS                                        (0x1030)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_SET_RMSK                                               0xf
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_SET_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_SET_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_SET_IRQ_BMSK                                           0xf
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_SET_IRQ_SHFT                                             0

#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_CLR_ADDR(x)                                     ((x) + 0x1034)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_CLR_OFFS                                        (0x1034)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_CLR_RMSK                                               0xf
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_CLR_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_CLR_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_CLR_IRQ_BMSK                                           0xf
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_CLR_IRQ_SHFT                                             0

#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_MASK_ADDR(x)                                    ((x) + 0x1038)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_MASK_OFFS                                       (0x1038)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_MASK_RMSK                                              0xf
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_MASK_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_MASK_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_MASK_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_MASK_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_MASK_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_MASK_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_MASK_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_MASK_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_MASK_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_MASK_IRQ_BMSK                                          0xf
#define HWIO_SP_CNOC_SP_SCSR_RMB_SOC2SP_IRQ_MASK_IRQ_SHFT                                            0

#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_ADDR(x)                                         ((x) + 0x103c)
#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_OFFS                                            (0x103c)
#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_RMSK                                            0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_STATUS_BMSK                                     0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_STATUS_SHFT                                              0

#define HWIO_SP_CNOC_SP_SCSR_RMB_GPm_ADDR(base,m)                                           ((base) + 0X1100 + (0x4*(m)))
#define HWIO_SP_CNOC_SP_SCSR_RMB_GPm_OFFS(m)                                                (0X1100 + (0x4*(m)))
#define HWIO_SP_CNOC_SP_SCSR_RMB_GPm_RMSK                                                       0xffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_GPm_MAXm                                                            1
#define HWIO_SP_CNOC_SP_SCSR_RMB_GPm_INI(base,m)                \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RMB_GPm_ADDR(base,m), HWIO_SP_CNOC_SP_SCSR_RMB_GPm_RMSK)
#define HWIO_SP_CNOC_SP_SCSR_RMB_GPm_INMI(base,m,mask)        \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RMB_GPm_ADDR(base,m), mask)
#define HWIO_SP_CNOC_SP_SCSR_RMB_GPm_OUTI(base,m,val)        \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RMB_GPm_ADDR(base,m),val)
#define HWIO_SP_CNOC_SP_SCSR_RMB_GPm_OUTMI(base,m,mask,val) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_RMB_GPm_ADDR(base,m),mask,val,HWIO_SP_CNOC_SP_SCSR_RMB_GPm_INI(base,m))
#define HWIO_SP_CNOC_SP_SCSR_RMB_GPm_GP_BMSK                                                    0xffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_GPm_GP_SHFT                                                         0

#define HWIO_SP_CNOC_SP_SCSR_SOC_HW_VERSION_ADDR(x)                                         ((x) + 0x1200)
#define HWIO_SP_CNOC_SP_SCSR_SOC_HW_VERSION_OFFS                                            (0x1200)
#define HWIO_SP_CNOC_SP_SCSR_SOC_HW_VERSION_RMSK                                            0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_SOC_HW_VERSION_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_SOC_HW_VERSION_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_SOC_HW_VERSION_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_SOC_HW_VERSION_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_SOC_HW_VERSION_FAMILY_NUMBER_BMSK                              0xf0000000
#define HWIO_SP_CNOC_SP_SCSR_SOC_HW_VERSION_FAMILY_NUMBER_SHFT                                      28
#define HWIO_SP_CNOC_SP_SCSR_SOC_HW_VERSION_DEVICE_NUMBER_BMSK                               0xfff0000
#define HWIO_SP_CNOC_SP_SCSR_SOC_HW_VERSION_DEVICE_NUMBER_SHFT                                      16
#define HWIO_SP_CNOC_SP_SCSR_SOC_HW_VERSION_MAJOR_VERSION_BMSK                                  0xff00
#define HWIO_SP_CNOC_SP_SCSR_SOC_HW_VERSION_MAJOR_VERSION_SHFT                                       8
#define HWIO_SP_CNOC_SP_SCSR_SOC_HW_VERSION_MINOR_VERSION_BMSK                                    0xff
#define HWIO_SP_CNOC_SP_SCSR_SOC_HW_VERSION_MINOR_VERSION_SHFT                                       0

#define HWIO_SP_CNOC_SP_SCSR_JTAG_ID_ADDR(x)                                                ((x) + 0x1204)
#define HWIO_SP_CNOC_SP_SCSR_JTAG_ID_OFFS                                                   (0x1204)
#define HWIO_SP_CNOC_SP_SCSR_JTAG_ID_RMSK                                                   0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_JTAG_ID_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_JTAG_ID_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_JTAG_ID_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_JTAG_ID_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_JTAG_ID_JTAG_ID_BMSK                                           0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_JTAG_ID_JTAG_ID_SHFT                                                    0

#define HWIO_SP_CNOC_SP_SCSR_OEM_ID_ADDR(x)                                                 ((x) + 0x1208)
#define HWIO_SP_CNOC_SP_SCSR_OEM_ID_OFFS                                                    (0x1208)
#define HWIO_SP_CNOC_SP_SCSR_OEM_ID_RMSK                                                        0xffff
#define HWIO_SP_CNOC_SP_SCSR_OEM_ID_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_OEM_ID_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_OEM_ID_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_OEM_ID_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_OEM_ID_OEM_ID_BMSK                                                 0xffff
#define HWIO_SP_CNOC_SP_SCSR_OEM_ID_OEM_ID_SHFT                                                      0

#define HWIO_SP_CNOC_SP_SCSR_SERIAL_NUM_ADDR(x)                                             ((x) + 0x120c)
#define HWIO_SP_CNOC_SP_SCSR_SERIAL_NUM_OFFS                                                (0x120c)
#define HWIO_SP_CNOC_SP_SCSR_SERIAL_NUM_RMSK                                                0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_SERIAL_NUM_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_SERIAL_NUM_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_SERIAL_NUM_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_SERIAL_NUM_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_SERIAL_NUM_SERIAL_NUM_BMSK                                     0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_SERIAL_NUM_SERIAL_NUM_SHFT                                              0

#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_ADDR(x)                               ((x) + 0x1ffc)
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_OFFS                                  (0x1ffc)
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_RMSK                                        0x7f
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_SP_MEM_CLAMP_MEM_BMSK                       0x40
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_SP_MEM_CLAMP_MEM_SHFT                          6
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_SP_MEM_SVS_BMSK                             0x20
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_SP_MEM_SVS_SHFT                                5
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_SP_QFPROM_FREEZIO_BMSK                      0x10
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_SP_QFPROM_FREEZIO_SHFT                         4
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_RET_0PIN_BMSK                                0x8
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_RET_0PIN_SHFT                                  3
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_FREEZIO_HV_BMSK                              0x4
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_FREEZIO_HV_SHFT                                2
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_SP_CC_RESTORE_FF_STATE_BMSK                  0x2
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_SP_CC_RESTORE_FF_STATE_SHFT                    1
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_SP_CC_SAVE_FF_STATE_BMSK                     0x1
#define HWIO_SP_CNOC_SP_SCSR_POWER_CONTROL_DBG_STATUS_SP_CC_SAVE_FF_STATE_SHFT                       0

#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_ADDR(x)                                             ((x) + 0x2000)
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_OFFS                                                (0x2000)
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_RMSK                                                      0x7f
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_DBGEN_EN_BMSK                                             0x40
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_DBGEN_EN_SHFT                                                6
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_DAPEN_EN_BMSK                                             0x20
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_DAPEN_EN_SHFT                                                5
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_NIDEN_EN_BMSK                                             0x10
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_NIDEN_EN_SHFT                                                4
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_TEST_EN_BMSK                                               0x8
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_TEST_EN_SHFT                                                 3
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_SCAN_OUT_EN_BMSK                                           0x4
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_SCAN_OUT_EN_SHFT                                             2
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_BOOT_FROM_ROM_N_EN_BMSK                                    0x2
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_BOOT_FROM_ROM_N_EN_SHFT                                      1
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_DUMP_MODE_EN_BMSK                                          0x1
#define HWIO_SP_CNOC_SP_SCSR_DBG_STATUS_DUMP_MODE_EN_SHFT                                            0

#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_ADDR(x)                                    ((x) + 0x2004)
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_OFFS                                       (0x2004)
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_RMSK                                             0xff
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_ERROR_POWER_BMSK                                 0x80
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_ERROR_POWER_SHFT                                    7
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_CPU_BOOT_BMSK                                    0x40
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_CPU_BOOT_SHFT                                       6
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_FUSE_UNMASK_BMSK                                 0x20
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_FUSE_UNMASK_SHFT                                    5
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_RAM_WIPE_WAIT_BMSK                               0x10
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_RAM_WIPE_WAIT_SHFT                                  4
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_RAM_WIPE_START_BMSK                               0x8
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_RAM_WIPE_START_SHFT                                 3
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_GDSC_BRINGUP_BMSK                                 0x4
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_GDSC_BRINGUP_SHFT                                   2
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_FUSE_SENSE_BMSK                                   0x2
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_FUSE_SENSE_SHFT                                     1
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_IDLE_BMSK                                         0x1
#define HWIO_SP_CNOC_SP_SCSR_COLD_BOOT_FSM_STATE_IDLE_SHFT                                           0

#define HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_ADDR(x)                                           ((x) + 0x2008)
#define HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_OFFS                                              (0x2008)
#define HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_RMSK                                                     0xe
#define HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_CNOC_DCD_VOTE_SW_DIS_BMSK                                0x8
#define HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_CNOC_DCD_VOTE_SW_DIS_SHFT                                  3
#define HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_CNOC_CGC_SW_EN_BMSK                                      0x4
#define HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_CNOC_CGC_SW_EN_SHFT                                        2
#define HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_SCSR_CGC_SW_EN_BMSK                                      0x2
#define HWIO_SP_CNOC_SP_SCSR_DCD_CGC_CTRL_SCSR_CGC_SW_EN_SHFT                                        1

#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm_ADDR(base,m)                             ((base) + 0X200C + (0x4*(m)))
#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm_OFFS(m)                                  (0X200C + (0x4*(m)))
#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm_RMSK                                     0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm_MAXm                                              3
#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm_INI(base,m)                \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm_ADDR(base,m), HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm_RMSK)
#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm_INMI(base,m,mask)        \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm_ADDR(base,m), mask)
#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm_OUTI(base,m,val)        \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm_ADDR(base,m),val)
#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm_OUTMI(base,m,mask,val) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm_ADDR(base,m),mask,val,HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm_INI(base,m))
#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm_STATUS_BMSK                              0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_RMB_ERR_STATUS_SPAREm_STATUS_SHFT                                       0

#define HWIO_SP_CNOC_SP_SCSR_RST_CTRL_ADDR(x)                                               ((x) + 0x201c)
#define HWIO_SP_CNOC_SP_SCSR_RST_CTRL_OFFS                                                  (0x201c)
#define HWIO_SP_CNOC_SP_SCSR_RST_CTRL_RMSK                                                         0x1
#define HWIO_SP_CNOC_SP_SCSR_RST_CTRL_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_RST_CTRL_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_RST_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RST_CTRL_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_RST_CTRL_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RST_CTRL_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_RST_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_RST_CTRL_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_RST_CTRL_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_RST_CTRL_FULL_SSR_EN_BMSK                                             0x1
#define HWIO_SP_CNOC_SP_SCSR_RST_CTRL_FULL_SSR_EN_SHFT                                               0

#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_STATUS_ADDR(x)                                       ((x) + 0x2020)
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_STATUS_OFFS                                          (0x2020)
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_STATUS_RMSK                                                 0xf
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_STATUS_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_RST_EVENT_STATUS_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RST_EVENT_STATUS_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_STATUS_SPSS_FUNC_RESET_BMSK                                 0x8
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_STATUS_SPSS_FUNC_RESET_SHFT                                   3
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_STATUS_WDOG_RESET_REQUEST_BMSK                              0x4
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_STATUS_WDOG_RESET_REQUEST_SHFT                                2
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_STATUS_COLD_RESET_REQUEST_BMSK                              0x2
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_STATUS_COLD_RESET_REQUEST_SHFT                                1
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_STATUS_GDSC_RESET_BMSK                                      0x1
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_STATUS_GDSC_RESET_SHFT                                        0

#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_CLR_ADDR(x)                                          ((x) + 0x2024)
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_CLR_OFFS                                             (0x2024)
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_CLR_RMSK                                                    0xf
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_CLR_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_RST_EVENT_CLR_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_CLR_SPSS_FUNC_RESET_BMSK                                    0x8
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_CLR_SPSS_FUNC_RESET_SHFT                                      3
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_CLR_WDOG_RESET_REQUEST_BMSK                                 0x4
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_CLR_WDOG_RESET_REQUEST_SHFT                                   2
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_CLR_COLD_RESET_REQUEST_BMSK                                 0x2
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_CLR_COLD_RESET_REQUEST_SHFT                                   1
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_CLR_GDSC_RESET_BMSK                                         0x1
#define HWIO_SP_CNOC_SP_SCSR_RST_EVENT_CLR_GDSC_RESET_SHFT                                           0

#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_ADDR(x)                                              ((x) + 0x2028)
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_OFFS                                                 (0x2028)
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_RMSK                                                    0x301ff
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_RST_STATE_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RST_STATE_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_SPSS_FIRST_PASS_RESET_BMSK                              0x20000
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_SPSS_FIRST_PASS_RESET_SHFT                                   17
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_SPSS_INT_ALT_RESET_BMSK                                 0x10000
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_SPSS_INT_ALT_RESET_SHFT                                      16
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_PREVENT_SSR_BMSK                                          0x100
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_PREVENT_SSR_SHFT                                              8
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_WDOG_FUNC_RESET_BMSK                                       0x80
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_WDOG_FUNC_RESET_SHFT                                          7
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_WDOG_ALT_RESET_BMSK                                        0x40
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_WDOG_ALT_RESET_SHFT                                           6
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_WDOG_CLK_DISABLE_BMSK                                      0x20
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_WDOG_CLK_DISABLE_SHFT                                         5
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_SPSS_INT_CLK_DISABLE_BMSK                                  0x10
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_SPSS_INT_CLK_DISABLE_SHFT                                     4
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_SPSS_FUNC_RESET_BMSK                                        0x8
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_SPSS_FUNC_RESET_SHFT                                          3
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_WDOG_RESET_REQUEST_BMSK                                     0x4
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_WDOG_RESET_REQUEST_SHFT                                       2
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_COLD_RESET_REQUEST_BMSK                                     0x2
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_COLD_RESET_REQUEST_SHFT                                       1
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_GDSC_RESET_BMSK                                             0x1
#define HWIO_SP_CNOC_SP_SCSR_RST_STATE_GDSC_RESET_SHFT                                               0

#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_ADDR(x)                                         ((x) + 0x202c)
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_OFFS                                            (0x202c)
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_RMSK                                                  0xff
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_RSVD_BMSK                                             0x80
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_RSVD_SHFT                                                7
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_SECOND_PASS_RESET_BMSK                                0x40
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_SECOND_PASS_RESET_SHFT                                   6
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_FIRST_PASS_DELAY_BMSK                                 0x20
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_FIRST_PASS_DELAY_SHFT                                    5
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_FIRST_PASS_RESET_EXTEND_BMSK                          0x10
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_FIRST_PASS_RESET_EXTEND_SHFT                             4
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_FIRST_PASS_RESET_BMSK                                  0x8
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_FIRST_PASS_RESET_SHFT                                    3
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_CONTEXT_DELAY_BMSK                                     0x4
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_CONTEXT_DELAY_SHFT                                       2
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_CONTEXT_IRQ_BMSK                                       0x2
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_CONTEXT_IRQ_SHFT                                         1
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_IDLE_BMSK                                              0x1
#define HWIO_SP_CNOC_SP_SCSR_WDOG_FSM_STATE_IDLE_SHFT                                                0

#define HWIO_SP_CNOC_SP_SCSR_PLL_STATUS_ADDR(x)                                             ((x) + 0x2030)
#define HWIO_SP_CNOC_SP_SCSR_PLL_STATUS_OFFS                                                (0x2030)
#define HWIO_SP_CNOC_SP_SCSR_PLL_STATUS_RMSK                                                   0xf000f
#define HWIO_SP_CNOC_SP_SCSR_PLL_STATUS_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_PLL_STATUS_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_PLL_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_PLL_STATUS_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_PLL_STATUS_PLL1_STATE_BMSK                                        0xe0000
#define HWIO_SP_CNOC_SP_SCSR_PLL_STATUS_PLL1_STATE_SHFT                                             17
#define HWIO_SP_CNOC_SP_SCSR_PLL_STATUS_PLL1_LOCK_DET_BMSK                                     0x10000
#define HWIO_SP_CNOC_SP_SCSR_PLL_STATUS_PLL1_LOCK_DET_SHFT                                          16
#define HWIO_SP_CNOC_SP_SCSR_PLL_STATUS_PLL0_STATE_BMSK                                            0xe
#define HWIO_SP_CNOC_SP_SCSR_PLL_STATUS_PLL0_STATE_SHFT                                              1
#define HWIO_SP_CNOC_SP_SCSR_PLL_STATUS_PLL0_LOCK_DET_BMSK                                         0x1
#define HWIO_SP_CNOC_SP_SCSR_PLL_STATUS_PLL0_LOCK_DET_SHFT                                           0

#define HWIO_SP_CNOC_SP_SCSR_GDSC_STATE_ADDR(x)                                             ((x) + 0x2034)
#define HWIO_SP_CNOC_SP_SCSR_GDSC_STATE_OFFS                                                (0x2034)
#define HWIO_SP_CNOC_SP_SCSR_GDSC_STATE_RMSK                                                      0xff
#define HWIO_SP_CNOC_SP_SCSR_GDSC_STATE_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_GDSC_STATE_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_GDSC_STATE_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_GDSC_STATE_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_GDSC_STATE_STATE_BMSK                                                0xff
#define HWIO_SP_CNOC_SP_SCSR_GDSC_STATE_STATE_SHFT                                                   0

#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_ADDR(x)                                ((x) + 0x2038)
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_OFFS                                   (0x2038)
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_RMSK                                         0x7f
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_GEN_DBG_ACK_BMSK                             0x40
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_GEN_DBG_ACK_SHFT                                6
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_REM_SLP_HOLD_REQ_BMSK                        0x20
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_REM_SLP_HOLD_REQ_SHFT                           5
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_GEN_BRINGUP_REQ_BMSK                         0x10
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_GEN_BRINGUP_REQ_SHFT                            4
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_WAIT_FOR_WAKEUP_BMSK                          0x8
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_WAIT_FOR_WAKEUP_SHFT                            3
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_GEN_SHUTDOWN_REQ_BMSK                         0x4
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_GEN_SHUTDOWN_REQ_SHFT                           2
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_GEN_SLP_HOLD_REQ_BMSK                         0x2
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_GEN_SLP_HOLD_REQ_SHFT                           1
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_ACTIVE_BMSK                                   0x1
#define HWIO_SP_CNOC_SP_SCSR_RSCC_CPU_SYNC_FSM_STATE_ACTIVE_SHFT                                     0

#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_ADDR(x)                                       ((x) + 0x203c)
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_OFFS                                          (0x203c)
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_RMSK                                                0x7f
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_TOE_DEBUG_UNLOCK_KEY_MATCH_FAIL_BMSK                0x40
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_TOE_DEBUG_UNLOCK_KEY_MATCH_FAIL_SHFT                   6
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_FUSECTL_SENSE_DONE_BMSK                             0x20
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_FUSECTL_SENSE_DONE_SHFT                                5
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_COLD_BOOT_FUSECTL_SENSE_ERROR_BMSK                  0x10
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_COLD_BOOT_FUSECTL_SENSE_ERROR_SHFT                     4
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_QFPROM_SP_DISABLE_BMSK                               0x8
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_QFPROM_SP_DISABLE_SHFT                                 3
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_QFPROM_FUSE_SENSE_FEC_ERROR_BMSK                     0x4
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_QFPROM_FUSE_SENSE_FEC_ERROR_SHFT                       2
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_QFPROM_FUSE_SENSE_ROM_ERROR_BMSK                     0x2
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_QFPROM_FUSE_SENSE_ROM_ERROR_SHFT                       1
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_QFPROM_KEK_ZEROIZED_BMSK                             0x1
#define HWIO_SP_CNOC_SP_SCSR_OTP_ERROR_STATUS_QFPROM_KEK_ZEROIZED_SHFT                               0

#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_CTRL_ADDR(x)                                  ((x) + 0x2040)
#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_CTRL_OFFS                                     (0x2040)
#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_CTRL_RMSK                                            0x1
#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_CTRL_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_CTRL_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_CTRL_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_CTRL_OUT(x, v)            \
                out_dword(HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_CTRL_ADDR(x),v)
#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_CTRL_ADDR(x),m,v,HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_CTRL_IN(x))
#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_CTRL_CX_PERIPH_CLK_FORCE_ON_BMSK                     0x1
#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_CTRL_CX_PERIPH_CLK_FORCE_ON_SHFT                       0

#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_STATUS_ADDR(x)                                ((x) + 0x2044)
#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_STATUS_OFFS                                   (0x2044)
#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_STATUS_RMSK                                          0x3
#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_STATUS_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_STATUS_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_STATUS_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_STATUS_CX_PERIPH_CLK_OFF_BMSK                        0x2
#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_STATUS_CX_PERIPH_CLK_OFF_SHFT                          1
#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_STATUS_CNOC2SP_INTF_DISABLE_BMSK                     0x1
#define HWIO_SP_CNOC_SP_SCSR_CNOC2SP_INTF_DBG_STATUS_CNOC2SP_INTF_DISABLE_SHFT                       0

#define HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_ADDR(x)                                       ((x) + 0x2048)
#define HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_OFFS                                          (0x2048)
#define HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_RMSK                                          0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_RSVD_BMSK                                     0xffffffe0
#define HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_RSVD_SHFT                                              5
#define HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_ZEROIZED_BMSK                                       0x10
#define HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_ZEROIZED_SHFT                                          4
#define HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_OP_EXT_BMSK                                          0x8
#define HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_OP_EXT_SHFT                                            3
#define HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_OP_INT_BMSK                                          0x4
#define HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_OP_INT_SHFT                                            2
#define HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_PERSO_BMSK                                           0x2
#define HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_PERSO_SHFT                                             1
#define HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_HW_TEST_BMSK                                         0x1
#define HWIO_SP_CNOC_SP_SCSR_LIFECYCLE_STATUS_HW_TEST_SHFT                                           0

#define HWIO_SP_CNOC_SP_SCSR_QFPROM_BIST_ERROR_ADDR(x)                                      ((x) + 0x204c)
#define HWIO_SP_CNOC_SP_SCSR_QFPROM_BIST_ERROR_OFFS                                         (0x204c)
#define HWIO_SP_CNOC_SP_SCSR_QFPROM_BIST_ERROR_RMSK                                         0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_QFPROM_BIST_ERROR_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_QFPROM_BIST_ERROR_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_QFPROM_BIST_ERROR_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_QFPROM_BIST_ERROR_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_QFPROM_BIST_ERROR_ERROR_BMSK                                   0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_QFPROM_BIST_ERROR_ERROR_SHFT                                            0

#define HWIO_SP_CNOC_SP_SCSR_GP_SPAREm_ADDR(base,m)                                         ((base) + 0X2050 + (0x4*(m)))
#define HWIO_SP_CNOC_SP_SCSR_GP_SPAREm_OFFS(m)                                              (0X2050 + (0x4*(m)))
#define HWIO_SP_CNOC_SP_SCSR_GP_SPAREm_RMSK                                                 0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_GP_SPAREm_MAXm                                                          3
#define HWIO_SP_CNOC_SP_SCSR_GP_SPAREm_INI(base,m)                \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_GP_SPAREm_ADDR(base,m), HWIO_SP_CNOC_SP_SCSR_GP_SPAREm_RMSK)
#define HWIO_SP_CNOC_SP_SCSR_GP_SPAREm_INMI(base,m,mask)        \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_GP_SPAREm_ADDR(base,m), mask)
#define HWIO_SP_CNOC_SP_SCSR_GP_SPAREm_OUTI(base,m,val)        \
                out_dword(HWIO_SP_CNOC_SP_SCSR_GP_SPAREm_ADDR(base,m),val)
#define HWIO_SP_CNOC_SP_SCSR_GP_SPAREm_OUTMI(base,m,mask,val) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_GP_SPAREm_ADDR(base,m),mask,val,HWIO_SP_CNOC_SP_SCSR_GP_SPAREm_INI(base,m))
#define HWIO_SP_CNOC_SP_SCSR_GP_SPAREm_GP_SPARE_BMSK                                        0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_GP_SPAREm_GP_SPARE_SHFT                                                 0

#define HWIO_SP_CNOC_SP_SCSR_MBn_TZ_CTRL_ADDR(base,n)                                       ((base) + 0X5000 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_TZ_CTRL_OFFS(n)                                            (0X5000 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_TZ_CTRL_RMSK                                                      0x1
#define HWIO_SP_CNOC_SP_SCSR_MBn_TZ_CTRL_MAXn                                                        3
#define HWIO_SP_CNOC_SP_SCSR_MBn_TZ_CTRL_INI(base,n)                \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_TZ_CTRL_ADDR(base,n), HWIO_SP_CNOC_SP_SCSR_MBn_TZ_CTRL_RMSK)
#define HWIO_SP_CNOC_SP_SCSR_MBn_TZ_CTRL_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_TZ_CTRL_ADDR(base,n), mask)
#define HWIO_SP_CNOC_SP_SCSR_MBn_TZ_CTRL_OUTI(base,n,val)        \
                out_dword(HWIO_SP_CNOC_SP_SCSR_MBn_TZ_CTRL_ADDR(base,n),val)
#define HWIO_SP_CNOC_SP_SCSR_MBn_TZ_CTRL_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_MBn_TZ_CTRL_ADDR(base,n),mask,val,HWIO_SP_CNOC_SP_SCSR_MBn_TZ_CTRL_INI(base,n))
#define HWIO_SP_CNOC_SP_SCSR_MBn_TZ_CTRL_LOCK_MB_BMSK                                              0x1
#define HWIO_SP_CNOC_SP_SCSR_MBn_TZ_CTRL_LOCK_MB_SHFT                                                0

#define HWIO_SP_CNOC_SP_SCSR_MBn_MSA_CTRL_ADDR(base,n)                                      ((base) + 0X5004 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_MSA_CTRL_OFFS(n)                                           (0X5004 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_MSA_CTRL_RMSK                                                     0x1
#define HWIO_SP_CNOC_SP_SCSR_MBn_MSA_CTRL_MAXn                                                       3
#define HWIO_SP_CNOC_SP_SCSR_MBn_MSA_CTRL_INI(base,n)                \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_MSA_CTRL_ADDR(base,n), HWIO_SP_CNOC_SP_SCSR_MBn_MSA_CTRL_RMSK)
#define HWIO_SP_CNOC_SP_SCSR_MBn_MSA_CTRL_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_MSA_CTRL_ADDR(base,n), mask)
#define HWIO_SP_CNOC_SP_SCSR_MBn_MSA_CTRL_OUTI(base,n,val)        \
                out_dword(HWIO_SP_CNOC_SP_SCSR_MBn_MSA_CTRL_ADDR(base,n),val)
#define HWIO_SP_CNOC_SP_SCSR_MBn_MSA_CTRL_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_MBn_MSA_CTRL_ADDR(base,n),mask,val,HWIO_SP_CNOC_SP_SCSR_MBn_MSA_CTRL_INI(base,n))
#define HWIO_SP_CNOC_SP_SCSR_MBn_MSA_CTRL_LOCK_MB_BMSK                                             0x1
#define HWIO_SP_CNOC_SP_SCSR_MBn_MSA_CTRL_LOCK_MB_SHFT                                               0

#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_L_ADDR(base,n)                                   ((base) + 0X5008 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_L_OFFS(n)                                        (0X5008 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_L_RMSK                                           0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_L_MAXn                                                    3
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_L_INI(base,n)                \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_L_ADDR(base,n), HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_L_RMSK)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_L_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_L_ADDR(base,n), mask)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_L_OUTI(base,n,val)        \
                out_dword(HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_L_ADDR(base,n),val)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_L_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_L_ADDR(base,n),mask,val,HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_L_INI(base,n))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_L_ADDR_BMSK                                      0xffffffff
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_L_ADDR_SHFT                                               0

#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_U_ADDR(base,n)                                   ((base) + 0X500C + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_U_OFFS(n)                                        (0X500C + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_U_RMSK                                               0xffff
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_U_MAXn                                                    3
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_U_INI(base,n)                \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_U_ADDR(base,n), HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_U_RMSK)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_U_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_U_ADDR(base,n), mask)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_U_OUTI(base,n,val)        \
                out_dword(HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_U_ADDR(base,n),val)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_U_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_U_ADDR(base,n),mask,val,HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_U_INI(base,n))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_U_ADDR_BMSK                                          0xffff
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_ADDR_U_ADDR_SHFT                                               0

#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_SIZE_ADDR(base,n)                                     ((base) + 0X5010 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_SIZE_OFFS(n)                                          (0X5010 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_SIZE_RMSK                                                0xfffff
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_SIZE_MAXn                                                      3
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_SIZE_INI(base,n)                \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_SIZE_ADDR(base,n), HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_SIZE_RMSK)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_SIZE_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_SIZE_ADDR(base,n), mask)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_SIZE_OUTI(base,n,val)        \
                out_dword(HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_SIZE_ADDR(base,n),val)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_SIZE_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_SIZE_ADDR(base,n),mask,val,HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_SIZE_INI(base,n))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_SIZE_SIZE_BMSK                                           0xfffff
#define HWIO_SP_CNOC_SP_SCSR_MBn_SMEM_SIZE_SIZE_SHFT                                                 0

#define HWIO_SP_CNOC_SP_SCSR_MB0_SMEM_ATTR_ADDR(x)                                          ((x) + 0x5014)
#define HWIO_SP_CNOC_SP_SCSR_MB0_SMEM_ATTR_OFFS                                             (0x5014)
#define HWIO_SP_CNOC_SP_SCSR_MB0_SMEM_ATTR_RMSK                                                    0x3
#define HWIO_SP_CNOC_SP_SCSR_MB0_SMEM_ATTR_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_MB0_SMEM_ATTR_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_MB0_SMEM_ATTR_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MB0_SMEM_ATTR_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_MB0_SMEM_ATTR_CLIENT_ID_BMSK                                          0x3
#define HWIO_SP_CNOC_SP_SCSR_MB0_SMEM_ATTR_CLIENT_ID_SHFT                                            0

#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_STATUS_ADDR(base,n)                              ((base) + 0X5018 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_STATUS_OFFS(n)                                   (0X5018 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_STATUS_RMSK                                            0x1f
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_STATUS_MAXn                                               3
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_STATUS_INI(base,n)                \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_STATUS_ADDR(base,n), HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_STATUS_RMSK)
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_STATUS_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_STATUS_ADDR(base,n), mask)
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_STATUS_IRQ_BMSK                                        0x1f
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_STATUS_IRQ_SHFT                                           0

#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_SET_ADDR(base,n)                                 ((base) + 0X501C + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_SET_OFFS(n)                                      (0X501C + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_SET_RMSK                                               0x1f
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_SET_MAXn                                                  3
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_SET_OUTI(base,n,val)        \
                out_dword(HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_SET_ADDR(base,n),val)
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_SET_IRQ_BMSK                                           0x1f
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_SET_IRQ_SHFT                                              0

#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_CLR_ADDR(base,n)                                 ((base) + 0X5020 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_CLR_OFFS(n)                                      (0X5020 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_CLR_RMSK                                               0x1f
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_CLR_MAXn                                                  3
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_CLR_OUTI(base,n,val)        \
                out_dword(HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_CLR_ADDR(base,n),val)
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_CLR_IRQ_BMSK                                           0x1f
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_CLR_IRQ_SHFT                                              0

#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_MASK_ADDR(base,n)                                ((base) + 0X5024 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_MASK_OFFS(n)                                     (0X5024 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_MASK_RMSK                                              0x1f
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_MASK_MAXn                                                 3
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_MASK_INI(base,n)                \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_MASK_ADDR(base,n), HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_MASK_RMSK)
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_MASK_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_MASK_ADDR(base,n), mask)
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_MASK_OUTI(base,n,val)        \
                out_dword(HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_MASK_ADDR(base,n),val)
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_MASK_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_MASK_ADDR(base,n),mask,val,HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_MASK_INI(base,n))
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_MASK_IRQ_BMSK                                          0x1f
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_IRQ_MASK_IRQ_SHFT                                             0

#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_GPm_ADDR(base,n,m)                                   ((base) + 0X5028 + (0x2000*(n)) + (0x4*(m)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_GPm_OFFS(n,m)                                        (0X5028 + (0x2000*(n)) + (0x4*(m)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_GPm_RMSK                                                 0xffff
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_GPm_MAXn                                                      3
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_GPm_MAXm                                                      1
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_GPm_INI2(base,n,m)                \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_GPm_ADDR(base,n,m), HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_GPm_RMSK)
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_GPm_INMI2(base,n,m,mask)        \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_GPm_ADDR(base,n,m), mask)
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_GPm_OUTI2(base,n,m,val)        \
                out_dword(HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_GPm_ADDR(base,n,m),val)
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_GPm_OUTMI2(base,n,m,mask,val) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_GPm_ADDR(base,n,m),mask,val,HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_GPm_INI2(base,n,m))
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_GPm_GP_BMSK                                              0xffff
#define HWIO_SP_CNOC_SP_SCSR_MBn_CL2SP_GPm_GP_SHFT                                                   0

#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_STATUS_ADDR(base,n)                              ((base) + 0X6000 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_STATUS_OFFS(n)                                   (0X6000 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_STATUS_RMSK                                            0x1f
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_STATUS_MAXn                                               3
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_STATUS_INI(base,n)                \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_STATUS_ADDR(base,n), HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_STATUS_RMSK)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_STATUS_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_STATUS_ADDR(base,n), mask)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_STATUS_IRQ_BMSK                                        0x1f
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_STATUS_IRQ_SHFT                                           0

#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_SET_ADDR(base,n)                                 ((base) + 0X6004 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_SET_OFFS(n)                                      (0X6004 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_SET_RMSK                                               0x1f
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_SET_MAXn                                                  3
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_SET_OUTI(base,n,val)        \
                out_dword(HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_SET_ADDR(base,n),val)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_SET_IRQ_BMSK                                           0x1f
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_SET_IRQ_SHFT                                              0

#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_CLR_ADDR(base,n)                                 ((base) + 0X6008 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_CLR_OFFS(n)                                      (0X6008 + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_CLR_RMSK                                               0x1f
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_CLR_MAXn                                                  3
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_CLR_OUTI(base,n,val)        \
                out_dword(HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_CLR_ADDR(base,n),val)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_CLR_IRQ_BMSK                                           0x1f
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_CLR_IRQ_SHFT                                              0

#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_MASK_ADDR(base,n)                                ((base) + 0X601C + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_MASK_OFFS(n)                                     (0X601C + (0x2000*(n)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_MASK_RMSK                                              0x1f
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_MASK_MAXn                                                 3
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_MASK_INI(base,n)                \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_MASK_ADDR(base,n), HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_MASK_RMSK)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_MASK_INMI(base,n,mask)        \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_MASK_ADDR(base,n), mask)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_MASK_OUTI(base,n,val)        \
                out_dword(HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_MASK_ADDR(base,n),val)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_MASK_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_MASK_ADDR(base,n),mask,val,HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_MASK_INI(base,n))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_MASK_IRQ_BMSK                                          0x1f
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_IRQ_MASK_IRQ_SHFT                                             0

#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_GPm_ADDR(base,n,m)                                   ((base) + 0X6020 + (0x2000*(n)) + (0x4*(m)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_GPm_OFFS(n,m)                                        (0X6020 + (0x2000*(n)) + (0x4*(m)))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_GPm_RMSK                                                 0xffff
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_GPm_MAXn                                                      3
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_GPm_MAXm                                                      1
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_GPm_INI2(base,n,m)                \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_GPm_ADDR(base,n,m), HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_GPm_RMSK)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_GPm_INMI2(base,n,m,mask)        \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_GPm_ADDR(base,n,m), mask)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_GPm_OUTI2(base,n,m,val)        \
                out_dword(HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_GPm_ADDR(base,n,m),val)
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_GPm_OUTMI2(base,n,m,mask,val) \
                out_dword_masked_ns(HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_GPm_ADDR(base,n,m),mask,val,HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_GPm_INI2(base,n,m))
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_GPm_GP_BMSK                                              0xffff
#define HWIO_SP_CNOC_SP_SCSR_MBn_SP2CL_GPm_GP_SHFT                                                   0

#define HWIO_SP_CNOC_SP_SCSR_MB1_SMEM_ATTR_ADDR(x)                                          ((x) + 0x7014)
#define HWIO_SP_CNOC_SP_SCSR_MB1_SMEM_ATTR_OFFS                                             (0x7014)
#define HWIO_SP_CNOC_SP_SCSR_MB1_SMEM_ATTR_RMSK                                                    0x3
#define HWIO_SP_CNOC_SP_SCSR_MB1_SMEM_ATTR_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_MB1_SMEM_ATTR_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_MB1_SMEM_ATTR_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MB1_SMEM_ATTR_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_MB1_SMEM_ATTR_CLIENT_ID_BMSK                                          0x3
#define HWIO_SP_CNOC_SP_SCSR_MB1_SMEM_ATTR_CLIENT_ID_SHFT                                            0

#define HWIO_SP_CNOC_SP_SCSR_MB2_SMEM_ATTR_ADDR(x)                                          ((x) + 0x9014)
#define HWIO_SP_CNOC_SP_SCSR_MB2_SMEM_ATTR_OFFS                                             (0x9014)
#define HWIO_SP_CNOC_SP_SCSR_MB2_SMEM_ATTR_RMSK                                                    0x3
#define HWIO_SP_CNOC_SP_SCSR_MB2_SMEM_ATTR_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_MB2_SMEM_ATTR_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_MB2_SMEM_ATTR_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MB2_SMEM_ATTR_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_MB2_SMEM_ATTR_CLIENT_ID_BMSK                                          0x3
#define HWIO_SP_CNOC_SP_SCSR_MB2_SMEM_ATTR_CLIENT_ID_SHFT                                            0

#define HWIO_SP_CNOC_SP_SCSR_MB3_SMEM_ATTR_ADDR(x)                                          ((x) + 0xb014)
#define HWIO_SP_CNOC_SP_SCSR_MB3_SMEM_ATTR_OFFS                                             (0xb014)
#define HWIO_SP_CNOC_SP_SCSR_MB3_SMEM_ATTR_RMSK                                                    0x3
#define HWIO_SP_CNOC_SP_SCSR_MB3_SMEM_ATTR_IN(x)            \
                in_dword(HWIO_SP_CNOC_SP_SCSR_MB3_SMEM_ATTR_ADDR(x))
#define HWIO_SP_CNOC_SP_SCSR_MB3_SMEM_ATTR_INM(x, m)            \
                in_dword_masked(HWIO_SP_CNOC_SP_SCSR_MB3_SMEM_ATTR_ADDR(x), m)
#define HWIO_SP_CNOC_SP_SCSR_MB3_SMEM_ATTR_CLIENT_ID_BMSK                                          0x3
#define HWIO_SP_CNOC_SP_SCSR_MB3_SMEM_ATTR_CLIENT_ID_SHFT                                            0


#endif /* __SPSS_HWIO_H__ */
