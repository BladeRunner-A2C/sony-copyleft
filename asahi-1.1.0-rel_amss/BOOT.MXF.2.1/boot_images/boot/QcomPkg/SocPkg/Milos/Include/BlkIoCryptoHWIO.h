#ifndef BLKIOCRYPTOHWIO_H
#define BLKIOCRYPTOHWIO_H
/*
===========================================================================
*/
/**
    @file BlkIoCryptoHWIO.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM6xxx (Milos) [milos_v1.0_p3q3r45_MTO]
 
    This file contains HWIO register definitions for the following modules:
        UFS_MEM_ICE_REGS
        UFS_MEM_ICE_LUT_KEYS

    'Include' filters applied: UFS_MEM_ICE_CONTROL[UFS_MEM_ICE_REGS] UFS_MEM_ICE_RESET[UFS_MEM_ICE_REGS] UFS_MEM_ICE_VERSION[UFS_MEM_ICE_REGS] UFS_MEM_ICE_BIST_STATUS[UFS_MEM_ICE_REGS] UFS_MEM_ICE_ADVANCED_CONTROL[UFS_MEM_ICE_REGS] UFS_MEM_ICE_CRYPTOCFG_r_n[UFS_MEM_ICE_LUT_KEYS] UFS_MEM_ICE_CRYPTOCFG_r_16[UFS_MEM_ICE_LUT_KEYS] UFS_MEM_ICE_CRYPTOCFG_r_17[UFS_MEM_ICE_LUT_KEYS] 

    Generation parameters: 
    { 'filename': 'BlkIoCryptoHWIO.h',
      'header': '#include "msmhwiobase.h"',
      'module-filter-include': { 'UFS_MEM_ICE_LUT_KEYS': [ 'UFS_MEM_ICE_CRYPTOCFG_r_n',
                                                           'UFS_MEM_ICE_CRYPTOCFG_r_16',
                                                           'UFS_MEM_ICE_CRYPTOCFG_r_17'],
                                 'UFS_MEM_ICE_REGS': [ 'UFS_MEM_ICE_CONTROL',
                                                       'UFS_MEM_ICE_RESET',
                                                       'UFS_MEM_ICE_VERSION',
                                                       'UFS_MEM_ICE_BIST_STATUS',
                                                       'UFS_MEM_ICE_ADVANCED_CONTROL']},
      'modules': ['UFS_MEM_ICE_REGS', 'UFS_MEM_ICE_LUT_KEYS']}
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
 * MODULE: UFS_MEM_ICE_REGS
 *--------------------------------------------------------------------------*/

#define UFS_MEM_ICE_REGS_REG_BASE                                                                 (UFS_MEM_UFS_2LANE_REGS_BASE      + 0x00008000)
#define UFS_MEM_ICE_REGS_REG_BASE_SIZE                                                            0x2000
#define UFS_MEM_ICE_REGS_REG_BASE_USED                                                            0x125c

#define HWIO_UFS_MEM_ICE_CONTROL_ADDR                                                             (UFS_MEM_ICE_REGS_REG_BASE      + 0x0)
#define HWIO_UFS_MEM_ICE_CONTROL_RMSK                                                                   0x1f
#define HWIO_UFS_MEM_ICE_CONTROL_IN                    \
                in_dword(HWIO_UFS_MEM_ICE_CONTROL_ADDR)
#define HWIO_UFS_MEM_ICE_CONTROL_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_ICE_CONTROL_ADDR, m)
#define HWIO_UFS_MEM_ICE_CONTROL_OUT(v)            \
                out_dword(HWIO_UFS_MEM_ICE_CONTROL_ADDR,v)
#define HWIO_UFS_MEM_ICE_CONTROL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_ICE_CONTROL_ADDR,m,v,HWIO_UFS_MEM_ICE_CONTROL_IN)
#define HWIO_UFS_MEM_ICE_CONTROL_GENERAL_PURPOSE_BMSK                                                   0x1e
#define HWIO_UFS_MEM_ICE_CONTROL_GENERAL_PURPOSE_SHFT                                                      1
#define HWIO_UFS_MEM_ICE_CONTROL_ICE_LEGACY_MODE_EN_OTP_BMSK                                             0x1
#define HWIO_UFS_MEM_ICE_CONTROL_ICE_LEGACY_MODE_EN_OTP_SHFT                                               0

#define HWIO_UFS_MEM_ICE_RESET_ADDR                                                               (UFS_MEM_ICE_REGS_REG_BASE      + 0x4)
#define HWIO_UFS_MEM_ICE_RESET_RMSK                                                                  0x10101
#define HWIO_UFS_MEM_ICE_RESET_IN                    \
                in_dword(HWIO_UFS_MEM_ICE_RESET_ADDR)
#define HWIO_UFS_MEM_ICE_RESET_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_ICE_RESET_ADDR, m)
#define HWIO_UFS_MEM_ICE_RESET_OUT(v)            \
                out_dword(HWIO_UFS_MEM_ICE_RESET_ADDR,v)
#define HWIO_UFS_MEM_ICE_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_ICE_RESET_ADDR,m,v,HWIO_UFS_MEM_ICE_RESET_IN)
#define HWIO_UFS_MEM_ICE_RESET_CONTROLLER_RESET_BMSK                                                 0x10000
#define HWIO_UFS_MEM_ICE_RESET_CONTROLLER_RESET_SHFT                                                      16
#define HWIO_UFS_MEM_ICE_RESET_IGNORE_CONTROLLER_RESET_BMSK                                            0x100
#define HWIO_UFS_MEM_ICE_RESET_IGNORE_CONTROLLER_RESET_SHFT                                                8
#define HWIO_UFS_MEM_ICE_RESET_ICE_RESET_BMSK                                                            0x1
#define HWIO_UFS_MEM_ICE_RESET_ICE_RESET_SHFT                                                              0

#define HWIO_UFS_MEM_ICE_VERSION_ADDR                                                             (UFS_MEM_ICE_REGS_REG_BASE      + 0x8)
#define HWIO_UFS_MEM_ICE_VERSION_RMSK                                                             0xffffffff
#define HWIO_UFS_MEM_ICE_VERSION_IN                    \
                in_dword(HWIO_UFS_MEM_ICE_VERSION_ADDR)
#define HWIO_UFS_MEM_ICE_VERSION_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_ICE_VERSION_ADDR, m)
#define HWIO_UFS_MEM_ICE_VERSION_MAJOR_VERSION_BMSK                                               0xff000000
#define HWIO_UFS_MEM_ICE_VERSION_MAJOR_VERSION_SHFT                                                       24
#define HWIO_UFS_MEM_ICE_VERSION_MINOR_VERSION_BMSK                                                 0xff0000
#define HWIO_UFS_MEM_ICE_VERSION_MINOR_VERSION_SHFT                                                       16
#define HWIO_UFS_MEM_ICE_VERSION_STEP_VERSION_BMSK                                                    0xffff
#define HWIO_UFS_MEM_ICE_VERSION_STEP_VERSION_SHFT                                                         0

#define HWIO_UFS_MEM_ICE_BIST_STATUS_ADDR                                                         (UFS_MEM_ICE_REGS_REG_BASE      + 0x70)
#define HWIO_UFS_MEM_ICE_BIST_STATUS_RMSK                                                         0xf0000000
#define HWIO_UFS_MEM_ICE_BIST_STATUS_IN                    \
                in_dword(HWIO_UFS_MEM_ICE_BIST_STATUS_ADDR)
#define HWIO_UFS_MEM_ICE_BIST_STATUS_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_ICE_BIST_STATUS_ADDR, m)
#define HWIO_UFS_MEM_ICE_BIST_STATUS_STREAM2_BIST_ERROR_BMSK                                      0x80000000
#define HWIO_UFS_MEM_ICE_BIST_STATUS_STREAM2_BIST_ERROR_SHFT                                              31
#define HWIO_UFS_MEM_ICE_BIST_STATUS_STREAM2_BIST_BUSY_BMSK                                       0x40000000
#define HWIO_UFS_MEM_ICE_BIST_STATUS_STREAM2_BIST_BUSY_SHFT                                               30
#define HWIO_UFS_MEM_ICE_BIST_STATUS_STREAM1_BIST_ERROR_BMSK                                      0x20000000
#define HWIO_UFS_MEM_ICE_BIST_STATUS_STREAM1_BIST_ERROR_SHFT                                              29
#define HWIO_UFS_MEM_ICE_BIST_STATUS_STREAM1_BIST_BUSY_BMSK                                       0x10000000
#define HWIO_UFS_MEM_ICE_BIST_STATUS_STREAM1_BIST_BUSY_SHFT                                               28

#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_ADDR                                                    (UFS_MEM_ICE_REGS_REG_BASE      + 0x1000)
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_RMSK                                                    0x8d807fff
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_IN                    \
                in_dword(HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_ADDR)
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_ADDR, m)
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_OUT(v)            \
                out_dword(HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_ADDR,v)
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_ADDR,m,v,HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_IN)
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_CRYPTO_LIB_FORCE_CLKON_BMSK                             0x80000000
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_CRYPTO_LIB_FORCE_CLKON_SHFT                                     31
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_DATA_DRIVER_PIPELINE_BMSK                                0x8000000
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_DATA_DRIVER_PIPELINE_SHFT                                       27
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_DATA_DRIVER_CTR_OPT_BMSK                                 0x4000000
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_DATA_DRIVER_CTR_OPT_SHFT                                        26
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_AES_MANAGER_EARLY_DD_INIT_BMSK                           0x1000000
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_AES_MANAGER_EARLY_DD_INIT_SHFT                                  24
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_CONTEXT_PROC_OPTIMIZATION_EN_BMSK                         0x800000
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_CONTEXT_PROC_OPTIMIZATION_EN_SHFT                               23
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_CONFIG_CLK_GATING_BMSK                                      0x4000
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_CONFIG_CLK_GATING_SHFT                                          14
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_STREAM2_CLK_GATING_BMSK                                     0x2000
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_STREAM2_CLK_GATING_SHFT                                         13
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_STREAM1_CLK_GATING_BMSK                                     0x1000
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_STREAM1_CLK_GATING_SHFT                                         12
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_CONTEXT_PROC_IGNORE_ERR_BMSK                                 0x800
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_CONTEXT_PROC_IGNORE_ERR_SHFT                                    11
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_CONTEXT_PROC_IGNORE_TRNS_ERR_BMSK                            0x400
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_CONTEXT_PROC_IGNORE_TRNS_ERR_SHFT                               10
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_CONTEXT_PROC_IGNORE_CFG_UPD_ERR_BMSK                         0x200
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_CONTEXT_PROC_IGNORE_CFG_UPD_ERR_SHFT                             9
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_AHB2AHB_POSTED_WRITE_BMSK                                    0x100
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_AHB2AHB_POSTED_WRITE_SHFT                                        8
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_AHBI_HYSTERESIS_VAL_BMSK                                      0xf0
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_AHBI_HYSTERESIS_VAL_SHFT                                         4
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_AHBO_HYSTERESIS_VAL_BMSK                                       0xf
#define HWIO_UFS_MEM_ICE_ADVANCED_CONTROL_AHBO_HYSTERESIS_VAL_SHFT                                         0

/*----------------------------------------------------------------------------
 * MODULE: UFS_MEM_ICE_LUT_KEYS
 *--------------------------------------------------------------------------*/

#define UFS_MEM_ICE_LUT_KEYS_REG_BASE                                        (UFS_MEM_UFS_2LANE_REGS_BASE      + 0x0000c000)
#define UFS_MEM_ICE_LUT_KEYS_REG_BASE_SIZE                                   0x3000
#define UFS_MEM_ICE_LUT_KEYS_REG_BASE_USED                                   0x220c

#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_n_ADDR(r,n)                             (UFS_MEM_ICE_LUT_KEYS_REG_BASE      + 0X0 + (0x80*(r)) + (0x4*(n)))
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_n_RMSK                                  0xffffffff
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_n_MAXr                                          63
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_n_MAXn                                          15
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_n_OUTI2(r,n,val)        \
                out_dword(HWIO_UFS_MEM_ICE_CRYPTOCFG_r_n_ADDR(r,n),val)
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_n_CRYPTOKEY_BMSK                        0xffffffff
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_n_CRYPTOKEY_SHFT                                 0

#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_ADDR(r)                              (UFS_MEM_ICE_LUT_KEYS_REG_BASE      + 0X40 + (0x80*(r)))
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_RMSK                                 0x8000ffff
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_MAXr                                         63
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_INI(r)                \
                in_dword_masked(HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_ADDR(r), HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_RMSK)
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_INMI(r,mask)        \
                in_dword_masked(HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_ADDR(r), mask)
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_OUTI(r,val)        \
                out_dword(HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_ADDR(r),val)
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_OUTMI(r,mask,val) \
                out_dword_masked_ns(HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_ADDR(r),mask,val,HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_INI(r))
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_CFGE_BMSK                            0x80000000
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_CFGE_SHFT                                    31
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_CAPIDX_BMSK                              0xff00
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_CAPIDX_SHFT                                   8
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_DUSIZE_BMSK                                0xff
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_16_DUSIZE_SHFT                                   0

#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_ADDR(r)                              (UFS_MEM_ICE_LUT_KEYS_REG_BASE      + 0X44 + (0x80*(r)))
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_RMSK                                   0x330000
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_MAXr                                         63
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_INI(r)                \
                in_dword_masked(HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_ADDR(r), HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_RMSK)
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_INMI(r,mask)        \
                in_dword_masked(HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_ADDR(r), mask)
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_OUTI(r,val)        \
                out_dword(HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_ADDR(r),val)
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_OUTMI(r,mask,val) \
                out_dword_masked_ns(HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_ADDR(r),mask,val,HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_INI(r))
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_KEY_SELECTION_BMSK                     0x300000
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_KEY_SELECTION_SHFT                           20
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_DECR_BYPASS_BMSK                        0x20000
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_DECR_BYPASS_SHFT                             17
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_ENCR_BYPASS_BMSK                        0x10000
#define HWIO_UFS_MEM_ICE_CRYPTOCFG_r_17_ENCR_BYPASS_SHFT                             16


#endif /* BLKIOCRYPTOHWIO_H */
