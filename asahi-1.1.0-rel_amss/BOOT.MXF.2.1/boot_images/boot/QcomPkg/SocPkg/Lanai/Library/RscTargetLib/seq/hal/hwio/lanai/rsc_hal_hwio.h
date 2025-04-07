#ifndef __RSC_HAL_HWIO_H__
#define __RSC_HAL_HWIO_H__
/*
===========================================================================
*/
/**
    @file rsc_hal_hwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8650 (Lanai) [z_lanai_prj_v1.0_F04_p3q3r11.9_rtl_partition]
 
    This file contains HWIO register definitions for the following modules:
        RSCC_PCIE_RSC
        TITAN_RSCC_RSCC_RSC


    Generation parameters: 
    { 'exclude-no-doc': True,
      'exclude-reserved': True,
      'filename': 'rsc_hal_hwio.h',
      'header': '#include "msmhwiobase.h"',
      'modules': ['RSCC_PCIE_RSC', 'TITAN_RSCC_RSCC_RSC'],
      'output-attrs': True,
      'output-fvals': True,
      'output-offsets': True,
      'output-resets': True}

    Attribute definitions for the HWIO_*_ATTR macros are as follows:
        0x0: Command register
        0x1: Read-Only
        0x2: Write-Only
        0x3: Read/Write
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
 * MODULE: RSCC_PCIE_RSC
 *--------------------------------------------------------------------------*/

#define RSCC_PCIE_RSC_REG_BASE                                                                              (PCIE_RSCC_BASE      + 0x00000000)
#define RSCC_PCIE_RSC_REG_BASE_SIZE                                                                         0x1000
#define RSCC_PCIE_RSC_REG_BASE_USED                                                                         0xd48
#define RSCC_PCIE_RSC_REG_BASE_OFFS                                                                         0x00000000

#define HWIO_RSCC_RSC_ID_DRVd_ADDR(d)                                                                       (RSCC_PCIE_RSC_REG_BASE      + 0X0 + (0x1000*(d)))
#define HWIO_RSCC_RSC_ID_DRVd_OFFS(d)                                                                       (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X0 + (0x1000*(d)))
#define HWIO_RSCC_RSC_ID_DRVd_RMSK                                                                            0xffffff
#define HWIO_RSCC_RSC_ID_DRVd_MAXd                                                                                   0
#define HWIO_RSCC_RSC_ID_DRVd_POR                                                                           0x00030200
#define HWIO_RSCC_RSC_ID_DRVd_POR_RMSK                                                                      0xffffffff
#define HWIO_RSCC_RSC_ID_DRVd_ATTR                                                                                       0x1
#define HWIO_RSCC_RSC_ID_DRVd_INI(d)                \
                in_dword_masked(HWIO_RSCC_RSC_ID_DRVd_ADDR(d), HWIO_RSCC_RSC_ID_DRVd_RMSK)
#define HWIO_RSCC_RSC_ID_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_RSCC_RSC_ID_DRVd_ADDR(d), mask)
#define HWIO_RSCC_RSC_ID_DRVd_MAJOR_VER_BMSK                                                                  0xff0000
#define HWIO_RSCC_RSC_ID_DRVd_MAJOR_VER_SHFT                                                                        16
#define HWIO_RSCC_RSC_ID_DRVd_MINOR_VER_BMSK                                                                    0xff00
#define HWIO_RSCC_RSC_ID_DRVd_MINOR_VER_SHFT                                                                         8
#define HWIO_RSCC_RSC_ID_DRVd_STEP_VER_BMSK                                                                       0xff
#define HWIO_RSCC_RSC_ID_DRVd_STEP_VER_SHFT                                                                          0

#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_ADDR(d)                                                      (RSCC_PCIE_RSC_REG_BASE      + 0X4 + (0x1000*(d)))
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_OFFS(d)                                                      (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X4 + (0x1000*(d)))
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_RMSK                                                          0x71f1f1f
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_MAXd                                                                  0
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_POR                                                          0x00010100
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_POR_RMSK                                                     0xffffffff
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_ATTR                                                                      0x1
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_INI(d)                \
                in_dword_masked(HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_ADDR(d), HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_RMSK)
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_ADDR(d), mask)
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SEQ_EXTENDED_BMSK                                             0x4000000
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SEQ_EXTENDED_SHFT                                                    26
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SEQ_EXTENDED_SIMPLE_FVAL                                            0x0
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SEQ_EXTENDED_EXTENDED_FVAL                                          0x1
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_IS_CHILD_RSC_BMSK                                             0x2000000
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_IS_CHILD_RSC_SHFT                                                    25
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_IS_CHILD_RSC_PARENT_RSC_FVAL                                        0x0
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_IS_CHILD_RSC_CHILD_RSC_FVAL                                         0x1
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_HW_SOLVER_BMSK                                                0x1000000
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_HW_SOLVER_SHFT                                                       24
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_HW_SOLVER_SOLVER_FALSE_FVAL                                         0x0
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_HW_SOLVER_SOLVER_TRUE_FVAL                                          0x1
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SOLVER_SLOTS_BMSK                                              0x1f0000
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SOLVER_SLOTS_SHFT                                                    16
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SOLVER_MODES_BMSK                                                0x1f00
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SOLVER_MODES_SHFT                                                     8
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_NUM_TIMERS_BMSK                                                    0x1f
#define HWIO_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_NUM_TIMERS_SHFT                                                       0

#define HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_ADDR(d)                                                         (RSCC_PCIE_RSC_REG_BASE      + 0X8 + (0x1000*(d)))
#define HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_OFFS(d)                                                         (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X8 + (0x1000*(d)))
#define HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_RMSK                                                             0x7ff0f1f
#define HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_MAXd                                                                     0
#define HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_POR                                                             0x01100214
#define HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_ATTR                                                                         0x1
#define HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_INI(d)                \
                in_dword_masked(HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_ADDR(d), HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_RMSK)
#define HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_ADDR(d), mask)
#define HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_DRV_BMSK                                                     0x7000000
#define HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_DRV_SHFT                                                            24
#define HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_SEQ_CMD_WORDS_BMSK                                            0xff0000
#define HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_SEQ_CMD_WORDS_SHFT                                                  16
#define HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_TS_EVENTS_BMSK                                                   0xf00
#define HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_TS_EVENTS_SHFT                                                       8
#define HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_DELAY_CNTR_BITWIDTH_BMSK                                              0x1f
#define HWIO_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_DELAY_CNTR_BITWIDTH_SHFT                                                 0

#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_ADDR(d)                                             (RSCC_PCIE_RSC_REG_BASE      + 0XC + (0x1000*(d)))
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_OFFS(d)                                             (RSCC_PCIE_RSC_REG_BASE_OFFS + 0XC + (0x1000*(d)))
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_RMSK                                                0xf8ffffff
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_MAXd                                                         0
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_POR                                                 0x08000001
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_POR_RMSK                                            0xffffffff
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_ATTR                                                             0x1
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_INI(d)                \
                in_dword_masked(HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_ADDR(d), HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_RMSK)
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_ADDR(d), mask)
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_CMDS_PER_TCS_BMSK                               0xf8000000
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_CMDS_PER_TCS_SHFT                                       27
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV3_BMSK                                     0xfc0000
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV3_SHFT                                           18
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV2_BMSK                                      0x3f000
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV2_SHFT                                           12
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV1_BMSK                                        0xfc0
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV1_SHFT                                            6
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV0_BMSK                                         0x3f
#define HWIO_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV0_SHFT                                            0

#define HWIO_RSCC_RSC_STATUS0_DRVd_ADDR(d)                                                                  (RSCC_PCIE_RSC_REG_BASE      + 0X10 + (0x1000*(d)))
#define HWIO_RSCC_RSC_STATUS0_DRVd_OFFS(d)                                                                  (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X10 + (0x1000*(d)))
#define HWIO_RSCC_RSC_STATUS0_DRVd_RMSK                                                                      0x101ffff
#define HWIO_RSCC_RSC_STATUS0_DRVd_MAXd                                                                              0
#define HWIO_RSCC_RSC_STATUS0_DRVd_POR                                                                      0x00000000
#define HWIO_RSCC_RSC_STATUS0_DRVd_POR_RMSK                                                                 0xffffffff
#define HWIO_RSCC_RSC_STATUS0_DRVd_ATTR                                                                                  0x3
#define HWIO_RSCC_RSC_STATUS0_DRVd_INI(d)                \
                in_dword_masked(HWIO_RSCC_RSC_STATUS0_DRVd_ADDR(d), HWIO_RSCC_RSC_STATUS0_DRVd_RMSK)
#define HWIO_RSCC_RSC_STATUS0_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_RSCC_RSC_STATUS0_DRVd_ADDR(d), mask)
#define HWIO_RSCC_RSC_STATUS0_DRVd_OUTI(d,val)        \
                out_dword(HWIO_RSCC_RSC_STATUS0_DRVd_ADDR(d),val)
#define HWIO_RSCC_RSC_STATUS0_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_RSCC_RSC_STATUS0_DRVd_ADDR(d),mask,val,HWIO_RSCC_RSC_STATUS0_DRVd_INI(d))
#define HWIO_RSCC_RSC_STATUS0_DRVd_CLK_GATE_DISABLE_BMSK                                                     0x1000000
#define HWIO_RSCC_RSC_STATUS0_DRVd_CLK_GATE_DISABLE_SHFT                                                            24
#define HWIO_RSCC_RSC_STATUS0_DRVd_STATUS_SLEEP_ENTRY_DONE_BMSK                                                0x10000
#define HWIO_RSCC_RSC_STATUS0_DRVd_STATUS_SLEEP_ENTRY_DONE_SHFT                                                     16
#define HWIO_RSCC_RSC_STATUS0_DRVd_STATUS_SLEEP_CTL_FSM_BMSK                                                    0xffff
#define HWIO_RSCC_RSC_STATUS0_DRVd_STATUS_SLEEP_CTL_FSM_SHFT                                                         0

#define HWIO_RSCC_RSC_STATUS1_DRVd_ADDR(d)                                                                  (RSCC_PCIE_RSC_REG_BASE      + 0X14 + (0x1000*(d)))
#define HWIO_RSCC_RSC_STATUS1_DRVd_OFFS(d)                                                                  (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X14 + (0x1000*(d)))
#define HWIO_RSCC_RSC_STATUS1_DRVd_RMSK                                                                     0xffffffff
#define HWIO_RSCC_RSC_STATUS1_DRVd_MAXd                                                                              0
#define HWIO_RSCC_RSC_STATUS1_DRVd_POR                                                                      0x00000000
#define HWIO_RSCC_RSC_STATUS1_DRVd_POR_RMSK                                                                 0xffffffff
#define HWIO_RSCC_RSC_STATUS1_DRVd_ATTR                                                                                  0x1
#define HWIO_RSCC_RSC_STATUS1_DRVd_INI(d)                \
                in_dword_masked(HWIO_RSCC_RSC_STATUS1_DRVd_ADDR(d), HWIO_RSCC_RSC_STATUS1_DRVd_RMSK)
#define HWIO_RSCC_RSC_STATUS1_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_RSCC_RSC_STATUS1_DRVd_ADDR(d), mask)
#define HWIO_RSCC_RSC_STATUS1_DRVd_PDC_MATCH_VALUE_LO_BMSK                                                  0xffffffff
#define HWIO_RSCC_RSC_STATUS1_DRVd_PDC_MATCH_VALUE_LO_SHFT                                                           0

#define HWIO_RSCC_RSC_STATUS2_DRVd_ADDR(d)                                                                  (RSCC_PCIE_RSC_REG_BASE      + 0X18 + (0x1000*(d)))
#define HWIO_RSCC_RSC_STATUS2_DRVd_OFFS(d)                                                                  (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X18 + (0x1000*(d)))
#define HWIO_RSCC_RSC_STATUS2_DRVd_RMSK                                                                       0xffffff
#define HWIO_RSCC_RSC_STATUS2_DRVd_MAXd                                                                              0
#define HWIO_RSCC_RSC_STATUS2_DRVd_POR                                                                      0x00000000
#define HWIO_RSCC_RSC_STATUS2_DRVd_POR_RMSK                                                                 0xffffffff
#define HWIO_RSCC_RSC_STATUS2_DRVd_ATTR                                                                                  0x1
#define HWIO_RSCC_RSC_STATUS2_DRVd_INI(d)                \
                in_dword_masked(HWIO_RSCC_RSC_STATUS2_DRVd_ADDR(d), HWIO_RSCC_RSC_STATUS2_DRVd_RMSK)
#define HWIO_RSCC_RSC_STATUS2_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_RSCC_RSC_STATUS2_DRVd_ADDR(d), mask)
#define HWIO_RSCC_RSC_STATUS2_DRVd_PDC_MATCH_VALUE_HI_BMSK                                                    0xffffff
#define HWIO_RSCC_RSC_STATUS2_DRVd_PDC_MATCH_VALUE_HI_SHFT                                                           0

#define HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_ADDR                                                                 (RSCC_PCIE_RSC_REG_BASE      + 0x1c)
#define HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_OFFS                                                                 (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x1c)
#define HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_RMSK                                                                    0x10003
#define HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_POR                                                                  0x00000000
#define HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_POR_RMSK                                                             0xffffffff
#define HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_ATTR                                                                              0x3
#define HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_IN                    \
                in_dword(HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_ADDR)
#define HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_ADDR, m)
#define HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_ADDR,v)
#define HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_ADDR,m,v,HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_IN)
#define HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_HIDDEN_TCS_TRIGGER_BMSK                                                 0x10000
#define HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_HIDDEN_TCS_TRIGGER_SHFT                                                      16
#define HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_HIDDEN_TCS_PDC_TIMER_DRV_OWNER_BMSK                                         0x3
#define HWIO_RSCC_HIDDEN_TCS_CTRL_DRV0_HIDDEN_TCS_PDC_TIMER_DRV_OWNER_SHFT                                           0

#define HWIO_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_ADDR                                                   (RSCC_PCIE_RSC_REG_BASE      + 0x20)
#define HWIO_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_OFFS                                                   (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x20)
#define HWIO_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_RMSK                                                       0xffff
#define HWIO_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_POR                                                    0x00004520
#define HWIO_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_POR_RMSK                                               0xffffffff
#define HWIO_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_ATTR                                                                0x3
#define HWIO_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_IN                    \
                in_dword(HWIO_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_ADDR)
#define HWIO_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_ADDR, m)
#define HWIO_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_ADDR,v)
#define HWIO_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_ADDR,m,v,HWIO_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_IN)
#define HWIO_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_PDC_SEQ_START_ADDR_REG_OFFSET_BMSK                         0xffff
#define HWIO_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_PDC_SEQ_START_ADDR_REG_OFFSET_SHFT                              0

#define HWIO_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_ADDR                                                   (RSCC_PCIE_RSC_REG_BASE      + 0x24)
#define HWIO_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_OFFS                                                   (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x24)
#define HWIO_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_RMSK                                                       0xffff
#define HWIO_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_POR                                                    0x00004510
#define HWIO_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_POR_RMSK                                               0xffffffff
#define HWIO_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_ATTR                                                                0x3
#define HWIO_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_IN                    \
                in_dword(HWIO_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_ADDR)
#define HWIO_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_ADDR, m)
#define HWIO_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_ADDR,v)
#define HWIO_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_ADDR,m,v,HWIO_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_IN)
#define HWIO_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_PDC_MATCH_VALUE_LO_REG_OFFSET_BMSK                         0xffff
#define HWIO_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_PDC_MATCH_VALUE_LO_REG_OFFSET_SHFT                              0

#define HWIO_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_ADDR                                                   (RSCC_PCIE_RSC_REG_BASE      + 0x28)
#define HWIO_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_OFFS                                                   (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x28)
#define HWIO_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_RMSK                                                       0xffff
#define HWIO_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_POR                                                    0x00004514
#define HWIO_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_POR_RMSK                                               0xffffffff
#define HWIO_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_ATTR                                                                0x3
#define HWIO_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_IN                    \
                in_dword(HWIO_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_ADDR)
#define HWIO_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_ADDR, m)
#define HWIO_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_ADDR,v)
#define HWIO_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_ADDR,m,v,HWIO_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_IN)
#define HWIO_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_PDC_MATCH_VALUE_HI_REG_OFFSET_BMSK                         0xffff
#define HWIO_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_PDC_MATCH_VALUE_HI_REG_OFFSET_SHFT                              0

#define HWIO_RSCC_PDC_SLAVE_ID_DRV0_ADDR                                                                    (RSCC_PCIE_RSC_REG_BASE      + 0x2c)
#define HWIO_RSCC_PDC_SLAVE_ID_DRV0_OFFS                                                                    (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x2c)
#define HWIO_RSCC_PDC_SLAVE_ID_DRV0_RMSK                                                                           0x7
#define HWIO_RSCC_PDC_SLAVE_ID_DRV0_POR                                                                     0x00000001
#define HWIO_RSCC_PDC_SLAVE_ID_DRV0_POR_RMSK                                                                0xffffffff
#define HWIO_RSCC_PDC_SLAVE_ID_DRV0_ATTR                                                                                 0x3
#define HWIO_RSCC_PDC_SLAVE_ID_DRV0_IN                    \
                in_dword(HWIO_RSCC_PDC_SLAVE_ID_DRV0_ADDR)
#define HWIO_RSCC_PDC_SLAVE_ID_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_PDC_SLAVE_ID_DRV0_ADDR, m)
#define HWIO_RSCC_PDC_SLAVE_ID_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_PDC_SLAVE_ID_DRV0_ADDR,v)
#define HWIO_RSCC_PDC_SLAVE_ID_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_PDC_SLAVE_ID_DRV0_ADDR,m,v,HWIO_RSCC_PDC_SLAVE_ID_DRV0_IN)
#define HWIO_RSCC_PDC_SLAVE_ID_DRV0_PDC_SLAVE_ID_BMSK                                                              0x7
#define HWIO_RSCC_PDC_SLAVE_ID_DRV0_PDC_SLAVE_ID_SHFT                                                                0

#define HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_ADDR(d)                                                            (RSCC_PCIE_RSC_REG_BASE      + 0X30 + (0x1000*(d)))
#define HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_OFFS(d)                                                            (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X30 + (0x1000*(d)))
#define HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_RMSK                                                                  0x70707
#define HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_MAXd                                                                        0
#define HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_POR                                                                0x00000000
#define HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_POR_RMSK                                                           0xffffffff
#define HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_ATTR                                                                            0x1
#define HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_INI(d)                \
                in_dword_masked(HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_ADDR(d), HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_RMSK)
#define HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_ADDR(d), mask)
#define HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_COMPLETED_BMSK                                                        0x70000
#define HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_COMPLETED_SHFT                                                             16
#define HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_ISSUED_BMSK                                                             0x700
#define HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_ISSUED_SHFT                                                                 8
#define HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_TRIGGERED_BMSK                                                            0x7
#define HWIO_RSCC_HIDDEN_TCS_STATUS_DRVd_TRIGGERED_SHFT                                                              0

#define HWIO_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_ADDR(d)                                                         (RSCC_PCIE_RSC_REG_BASE      + 0X34 + (0x1000*(d)))
#define HWIO_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_OFFS(d)                                                         (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X34 + (0x1000*(d)))
#define HWIO_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_RMSK                                                            0xffffffff
#define HWIO_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_MAXd                                                                     0
#define HWIO_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_POR                                                             0x82204514
#define HWIO_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_ATTR                                                                         0x1
#define HWIO_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_INI(d)                \
                in_dword_masked(HWIO_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_ADDR(d), HWIO_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_RMSK)
#define HWIO_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_ADDR(d), mask)
#define HWIO_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_ADDR_BMSK                                                       0xffffffff
#define HWIO_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_ADDR_SHFT                                                                0

#define HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_ADDR(d)                                                         (RSCC_PCIE_RSC_REG_BASE      + 0X38 + (0x1000*(d)))
#define HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_OFFS(d)                                                         (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X38 + (0x1000*(d)))
#define HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_RMSK                                                            0x80ffffff
#define HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_MAXd                                                                     0
#define HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_POR                                                             0x00000000
#define HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_ATTR                                                                         0x3
#define HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_INI(d)                \
                in_dword_masked(HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_ADDR(d), HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_RMSK)
#define HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_ADDR(d), mask)
#define HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_OUTI(d,val)        \
                out_dword(HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_ADDR(d),val)
#define HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_ADDR(d),mask,val,HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_INI(d))
#define HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_PDC_MATCH_VALUE_VALID_BMSK                                      0x80000000
#define HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_PDC_MATCH_VALUE_VALID_SHFT                                              31
#define HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_PDC_MATCH_VALUE_HI_BMSK                                           0xffffff
#define HWIO_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_PDC_MATCH_VALUE_HI_SHFT                                                  0

#define HWIO_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_ADDR(d)                                                         (RSCC_PCIE_RSC_REG_BASE      + 0X3C + (0x1000*(d)))
#define HWIO_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_OFFS(d)                                                         (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X3C + (0x1000*(d)))
#define HWIO_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_RMSK                                                            0xffffffff
#define HWIO_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_MAXd                                                                     0
#define HWIO_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_POR                                                             0x82204510
#define HWIO_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_ATTR                                                                         0x1
#define HWIO_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_INI(d)                \
                in_dword_masked(HWIO_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_ADDR(d), HWIO_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_RMSK)
#define HWIO_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_ADDR(d), mask)
#define HWIO_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_ADDR_BMSK                                                       0xffffffff
#define HWIO_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_ADDR_SHFT                                                                0

#define HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_ADDR(d)                                                         (RSCC_PCIE_RSC_REG_BASE      + 0X40 + (0x1000*(d)))
#define HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_OFFS(d)                                                         (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X40 + (0x1000*(d)))
#define HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_RMSK                                                            0xffffffff
#define HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_MAXd                                                                     0
#define HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_POR                                                             0x00000000
#define HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_ATTR                                                                         0x3
#define HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_INI(d)                \
                in_dword_masked(HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_ADDR(d), HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_RMSK)
#define HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_ADDR(d), mask)
#define HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_OUTI(d,val)        \
                out_dword(HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_ADDR(d),val)
#define HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_ADDR(d),mask,val,HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_INI(d))
#define HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_PDC_MATCH_VALUE_LO_BMSK                                         0xffffffff
#define HWIO_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_PDC_MATCH_VALUE_LO_SHFT                                                  0

#define HWIO_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_ADDR(d)                                                         (RSCC_PCIE_RSC_REG_BASE      + 0X44 + (0x1000*(d)))
#define HWIO_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_OFFS(d)                                                         (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X44 + (0x1000*(d)))
#define HWIO_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_RMSK                                                            0xffffffff
#define HWIO_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_MAXd                                                                     0
#define HWIO_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_POR                                                             0x82204520
#define HWIO_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_ATTR                                                                         0x1
#define HWIO_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_INI(d)                \
                in_dword_masked(HWIO_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_ADDR(d), HWIO_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_RMSK)
#define HWIO_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_ADDR(d), mask)
#define HWIO_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_ADDR_BMSK                                                       0xffffffff
#define HWIO_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_ADDR_SHFT                                                                0

#define HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_ADDR                                                            (RSCC_PCIE_RSC_REG_BASE      + 0x48)
#define HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_OFFS                                                            (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x48)
#define HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_RMSK                                                            0x8000ffff
#define HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_POR                                                             0x00000000
#define HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_POR_RMSK                                                        0xffffffff
#define HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_ATTR                                                                         0x3
#define HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_IN                    \
                in_dword(HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_ADDR)
#define HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_ADDR, m)
#define HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_ADDR,v)
#define HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_ADDR,m,v,HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_IN)
#define HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_PDC_SEQ_START_ADDR_VALID_BMSK                                   0x80000000
#define HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_PDC_SEQ_START_ADDR_VALID_SHFT                                           31
#define HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_PDC_SEQ_START_ADDR_BMSK                                             0xffff
#define HWIO_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_PDC_SEQ_START_ADDR_SHFT                                                  0

#define HWIO_RSCC_HW_EVENT_OWNER_DRV0_ADDR                                                                  (RSCC_PCIE_RSC_REG_BASE      + 0x4c)
#define HWIO_RSCC_HW_EVENT_OWNER_DRV0_OFFS                                                                  (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x4c)
#define HWIO_RSCC_HW_EVENT_OWNER_DRV0_RMSK                                                                         0x3
#define HWIO_RSCC_HW_EVENT_OWNER_DRV0_POR                                                                   0x00000000
#define HWIO_RSCC_HW_EVENT_OWNER_DRV0_POR_RMSK                                                              0xffffffff
#define HWIO_RSCC_HW_EVENT_OWNER_DRV0_ATTR                                                                               0x3
#define HWIO_RSCC_HW_EVENT_OWNER_DRV0_IN                    \
                in_dword(HWIO_RSCC_HW_EVENT_OWNER_DRV0_ADDR)
#define HWIO_RSCC_HW_EVENT_OWNER_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_HW_EVENT_OWNER_DRV0_ADDR, m)
#define HWIO_RSCC_HW_EVENT_OWNER_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_HW_EVENT_OWNER_DRV0_ADDR,v)
#define HWIO_RSCC_HW_EVENT_OWNER_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_HW_EVENT_OWNER_DRV0_ADDR,m,v,HWIO_RSCC_HW_EVENT_OWNER_DRV0_IN)
#define HWIO_RSCC_HW_EVENT_OWNER_DRV0_OWNER_BMSK                                                                   0x3
#define HWIO_RSCC_HW_EVENT_OWNER_DRV0_OWNER_SHFT                                                                     0

#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ADDR(d,m)                                                       (RSCC_PCIE_RSC_REG_BASE      + 0X50 + (0x1000*(d)) + (0x4*(m)))
#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_OFFS(d,m)                                                       (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X50 + (0x1000*(d)) + (0x4*(m)))
#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_RMSK                                                            0x80000007
#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_MAXd                                                                     0
#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_MAXm                                                                    31
#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_POR                                                             0x00000000
#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ATTR                                                                         0x3
#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_INI2(d,m)                \
                in_dword_masked(HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ADDR(d,m), HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_RMSK)
#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_INMI2(d,m,mask)        \
                in_dword_masked(HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ADDR(d,m), mask)
#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_OUTI2(d,m,val)        \
                out_dword(HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ADDR(d,m),val)
#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_OUTMI2(d,m,mask,val) \
                out_dword_masked_ns(HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ADDR(d,m),mask,val,HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_INI2(d,m))
#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ENABLE_BMSK                                                     0x80000000
#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ENABLE_SHFT                                                             31
#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ENABLE_NOT_ENABLED_FVAL                                                0x0
#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ENABLE_ENABLED_FVAL                                                    0x1
#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_EVENT_SELECT_BMSK                                                      0x7
#define HWIO_RSCC_HW_EVENT_MUXm_SELECT_DRVd_EVENT_SELECT_SHFT                                                        0

#define HWIO_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_ADDR                                                            (RSCC_PCIE_RSC_REG_BASE      + 0xd0)
#define HWIO_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_OFFS                                                            (RSCC_PCIE_RSC_REG_BASE_OFFS + 0xd0)
#define HWIO_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_RMSK                                                                   0x1
#define HWIO_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_POR                                                             0x00000000
#define HWIO_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_POR_RMSK                                                        0xffffffff
#define HWIO_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_ATTR                                                                         0x1
#define HWIO_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_ADDR)
#define HWIO_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_EPCB_TIMEOUT_IRQ_BMSK                                                  0x1
#define HWIO_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_EPCB_TIMEOUT_IRQ_SHFT                                                    0

#define HWIO_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_ADDR                                                             (RSCC_PCIE_RSC_REG_BASE      + 0xd4)
#define HWIO_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_OFFS                                                             (RSCC_PCIE_RSC_REG_BASE_OFFS + 0xd4)
#define HWIO_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_RMSK                                                                    0x1
#define HWIO_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_POR                                                              0x00000000
#define HWIO_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_POR_RMSK                                                         0xffffffff
#define HWIO_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_ATTR                                                                          0x0
#define HWIO_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_CLR_EPCB_TIMEOUT_IRQ_BMSK                                               0x1
#define HWIO_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_CLR_EPCB_TIMEOUT_IRQ_SHFT                                                 0

#define HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_ADDR                                                            (RSCC_PCIE_RSC_REG_BASE      + 0xd8)
#define HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_OFFS                                                            (RSCC_PCIE_RSC_REG_BASE_OFFS + 0xd8)
#define HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_RMSK                                                              0x10ffff
#define HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_POR                                                             0x00000000
#define HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_POR_RMSK                                                        0xffffffff
#define HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_ATTR                                                                         0x3
#define HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_ADDR)
#define HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_ADDR,m,v,HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_IN)
#define HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_EPCB_TIMEOUT_IRQ_EN_BMSK                                          0x100000
#define HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_EPCB_TIMEOUT_IRQ_EN_SHFT                                                20
#define HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_EPCB_TIMEOUT_IRQ_EN_NOT_ENABLED_FVAL                                   0x0
#define HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_EPCB_TIMEOUT_IRQ_EN_ENABLED_FVAL                                       0x1
#define HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_EPCB_TIMEOUT_THRESHOLD_BMSK                                         0xffff
#define HWIO_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_EPCB_TIMEOUT_THRESHOLD_SHFT                                              0

#define HWIO_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ADDR                                                             (RSCC_PCIE_RSC_REG_BASE      + 0x100)
#define HWIO_RSCC_RSC_ERROR_RESP_CTRL_DRV0_OFFS                                                             (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x100)
#define HWIO_RSCC_RSC_ERROR_RESP_CTRL_DRV0_RMSK                                                                    0x1
#define HWIO_RSCC_RSC_ERROR_RESP_CTRL_DRV0_POR                                                              0x00000000
#define HWIO_RSCC_RSC_ERROR_RESP_CTRL_DRV0_POR_RMSK                                                         0xffffffff
#define HWIO_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ATTR                                                                          0x3
#define HWIO_RSCC_RSC_ERROR_RESP_CTRL_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ADDR)
#define HWIO_RSCC_RSC_ERROR_RESP_CTRL_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_ERROR_RESP_CTRL_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_ERROR_RESP_CTRL_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ADDR,m,v,HWIO_RSCC_RSC_ERROR_RESP_CTRL_DRV0_IN)
#define HWIO_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ERROR_RESP_FOR_INVALID_ADDR_BMSK                                        0x1
#define HWIO_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ERROR_RESP_FOR_INVALID_ADDR_SHFT                                          0

#define HWIO_RSCC_RSC_SECURE_OVERRIDE_DRV0_ADDR                                                             (RSCC_PCIE_RSC_REG_BASE      + 0x104)
#define HWIO_RSCC_RSC_SECURE_OVERRIDE_DRV0_OFFS                                                             (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x104)
#define HWIO_RSCC_RSC_SECURE_OVERRIDE_DRV0_RMSK                                                                    0x1
#define HWIO_RSCC_RSC_SECURE_OVERRIDE_DRV0_POR                                                              0x00000001
#define HWIO_RSCC_RSC_SECURE_OVERRIDE_DRV0_POR_RMSK                                                         0xffffffff
#define HWIO_RSCC_RSC_SECURE_OVERRIDE_DRV0_ATTR                                                                          0x3
#define HWIO_RSCC_RSC_SECURE_OVERRIDE_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SECURE_OVERRIDE_DRV0_ADDR)
#define HWIO_RSCC_RSC_SECURE_OVERRIDE_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SECURE_OVERRIDE_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SECURE_OVERRIDE_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_SECURE_OVERRIDE_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_SECURE_OVERRIDE_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_SECURE_OVERRIDE_DRV0_ADDR,m,v,HWIO_RSCC_RSC_SECURE_OVERRIDE_DRV0_IN)
#define HWIO_RSCC_RSC_SECURE_OVERRIDE_DRV0_SECURE_OVERRIDE_BMSK                                                    0x1
#define HWIO_RSCC_RSC_SECURE_OVERRIDE_DRV0_SECURE_OVERRIDE_SHFT                                                      0

#define HWIO_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_ADDR                                                     (RSCC_PCIE_RSC_REG_BASE      + 0x108)
#define HWIO_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_OFFS                                                     (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x108)
#define HWIO_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_RMSK                                                            0x1
#define HWIO_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_POR                                                      0x00000000
#define HWIO_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_POR_RMSK                                                 0xffffffff
#define HWIO_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_ATTR                                                                  0x3
#define HWIO_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_ADDR)
#define HWIO_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_ADDR,m,v,HWIO_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_IN)
#define HWIO_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_RIF_CLK_GATING_OVERRIDE_BMSK                                    0x1
#define HWIO_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_RIF_CLK_GATING_OVERRIDE_SHFT                                      0

#define HWIO_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_ADDR                                                      (RSCC_PCIE_RSC_REG_BASE      + 0x10c)
#define HWIO_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_OFFS                                                      (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x10c)
#define HWIO_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_RMSK                                                             0x1
#define HWIO_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_POR                                                       0x00000000
#define HWIO_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_POR_RMSK                                                  0xffffffff
#define HWIO_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_ATTR                                                                   0x0
#define HWIO_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_SW_RESET_BMSK                                                    0x1
#define HWIO_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_SW_RESET_SHFT                                                      0

#define HWIO_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_ADDR                                                              (RSCC_PCIE_RSC_REG_BASE      + 0x110)
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_OFFS                                                              (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x110)
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_RMSK                                                                     0x1
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_POR                                                               0x00000000
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_POR_RMSK                                                          0xffffffff
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_ATTR                                                                           0x3
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_ADDR,m,v,HWIO_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_IN)
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_EN_BMSK                                                                  0x1
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_EN_SHFT                                                                    0

#define HWIO_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_ADDR                                                          (RSCC_PCIE_RSC_REG_BASE      + 0x114)
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_OFFS                                                          (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x114)
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_RMSK                                                                 0x1
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_POR                                                           0x00000000
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_POR_RMSK                                                      0xffffffff
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_ATTR                                                                       0x1
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_IRQ_BMSK                                                             0x1
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_IRQ_SHFT                                                               0

#define HWIO_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_ADDR                                                             (RSCC_PCIE_RSC_REG_BASE      + 0x118)
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_OFFS                                                             (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x118)
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_RMSK                                                                    0x1
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_POR                                                              0x00000000
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_POR_RMSK                                                         0xffffffff
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_ATTR                                                                          0x0
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_CLR_BMSK                                                                0x1
#define HWIO_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_CLR_SHFT                                                                  0

#define HWIO_RSCC_RSC_PROFILING_THRESHOLD_DRV0_ADDR                                                         (RSCC_PCIE_RSC_REG_BASE      + 0x11c)
#define HWIO_RSCC_RSC_PROFILING_THRESHOLD_DRV0_OFFS                                                         (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x11c)
#define HWIO_RSCC_RSC_PROFILING_THRESHOLD_DRV0_RMSK                                                         0xffffffff
#define HWIO_RSCC_RSC_PROFILING_THRESHOLD_DRV0_POR                                                          0x00000000
#define HWIO_RSCC_RSC_PROFILING_THRESHOLD_DRV0_POR_RMSK                                                     0xffffffff
#define HWIO_RSCC_RSC_PROFILING_THRESHOLD_DRV0_ATTR                                                                      0x3
#define HWIO_RSCC_RSC_PROFILING_THRESHOLD_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_PROFILING_THRESHOLD_DRV0_ADDR)
#define HWIO_RSCC_RSC_PROFILING_THRESHOLD_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_PROFILING_THRESHOLD_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_PROFILING_THRESHOLD_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_PROFILING_THRESHOLD_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_PROFILING_THRESHOLD_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_PROFILING_THRESHOLD_DRV0_ADDR,m,v,HWIO_RSCC_RSC_PROFILING_THRESHOLD_DRV0_IN)
#define HWIO_RSCC_RSC_PROFILING_THRESHOLD_DRV0_THRESHOLD_BMSK                                               0xffffffff
#define HWIO_RSCC_RSC_PROFILING_THRESHOLD_DRV0_THRESHOLD_SHFT                                                        0

#define HWIO_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_ADDR                                                        (RSCC_PCIE_RSC_REG_BASE      + 0x200)
#define HWIO_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_OFFS                                                        (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x200)
#define HWIO_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_RMSK                                                               0x3
#define HWIO_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_POR                                                         0x00000000
#define HWIO_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_POR_RMSK                                                    0xffffffff
#define HWIO_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_ATTR                                                                     0x3
#define HWIO_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_ADDR)
#define HWIO_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_ADDR,m,v,HWIO_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_IN)
#define HWIO_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_OWNER_BMSK                                                         0x3
#define HWIO_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_OWNER_SHFT                                                           0

#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ADDR(d,m)                                                     (RSCC_PCIE_RSC_REG_BASE      + 0X204 + (0x1000*(d)) + (0x20*(m)))
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_OFFS(d,m)                                                     (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X204 + (0x1000*(d)) + (0x20*(m)))
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_RMSK                                                                 0x1
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_MAXd                                                                   0
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_MAXm                                                                   5
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_POR                                                           0x00000000
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_POR_RMSK                                                      0xffffffff
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ATTR                                                                       0x3
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_INI2(d,m)                \
                in_dword_masked(HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ADDR(d,m), HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_RMSK)
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_INMI2(d,m,mask)        \
                in_dword_masked(HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ADDR(d,m), mask)
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_OUTI2(d,m,val)        \
                out_dword(HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ADDR(d,m),val)
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_OUTMI2(d,m,mask,val) \
                out_dword_masked_ns(HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ADDR(d,m),mask,val,HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_INI2(d,m))
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ENABLE_BMSK                                                          0x1
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ENABLE_SHFT                                                            0
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ENABLE_NOT_ENABLED_FVAL                                              0x0
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ENABLE_ENABLED_FVAL                                                  0x1

#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_ADDR(d,m)                                            (RSCC_PCIE_RSC_REG_BASE      + 0X208 + (0x1000*(d)) + (0x20*(m)))
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_OFFS(d,m)                                            (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X208 + (0x1000*(d)) + (0x20*(m)))
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_RMSK                                                 0xffffffff
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_MAXd                                                          0
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_MAXm                                                          5
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_POR                                                  0x00000000
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_POR_RMSK                                             0xffffffff
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_ATTR                                                              0x1
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_INI2(d,m)                \
                in_dword_masked(HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_ADDR(d,m), HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_RMSK)
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_INMI2(d,m,mask)        \
                in_dword_masked(HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_ADDR(d,m), mask)
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_TS_DATA_L_BMSK                                       0xffffffff
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_TS_DATA_L_SHFT                                                0

#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_ADDR(d,m)                                            (RSCC_PCIE_RSC_REG_BASE      + 0X20C + (0x1000*(d)) + (0x20*(m)))
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_OFFS(d,m)                                            (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X20C + (0x1000*(d)) + (0x20*(m)))
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_RMSK                                                   0xffffff
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_MAXd                                                          0
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_MAXm                                                          5
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_POR                                                  0x00000000
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_POR_RMSK                                             0xffffffff
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_ATTR                                                              0x1
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_INI2(d,m)                \
                in_dword_masked(HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_ADDR(d,m), HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_RMSK)
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_INMI2(d,m,mask)        \
                in_dword_masked(HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_ADDR(d,m), mask)
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_TS_DATA_H_BMSK                                         0xffffff
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_TS_DATA_H_SHFT                                                0

#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_ADDR(d,m)                                                 (RSCC_PCIE_RSC_REG_BASE      + 0X210 + (0x1000*(d)) + (0x20*(m)))
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_OFFS(d,m)                                                 (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X210 + (0x1000*(d)) + (0x20*(m)))
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_RMSK                                                           0x101
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_MAXd                                                               0
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_MAXm                                                               5
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_POR                                                       0x00000000
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_POR_RMSK                                                  0xffffffff
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_ATTR                                                                   0x1
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_INI2(d,m)                \
                in_dword_masked(HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_ADDR(d,m), HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_RMSK)
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_INMI2(d,m,mask)        \
                in_dword_masked(HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_ADDR(d,m), mask)
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_OVERFLOW_BMSK                                               0x100
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_OVERFLOW_SHFT                                                   8
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_OVERFLOW_MULTIPLE_EVENT_CAPTURES_FALSE_FVAL                   0x0
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_OVERFLOW_MULTIPLE_EVENT_CAPTURES_TRUE_FVAL                    0x1
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_VALID_BMSK                                                    0x1
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_VALID_SHFT                                                      0
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_VALID_EVENT_CAPTURED_FALSE_FVAL                               0x0
#define HWIO_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_VALID_EVENT_CAPTURED_TRUE_FVAL                                0x1

#define HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR                                                     (RSCC_PCIE_RSC_REG_BASE      + 0x400)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_OFFS                                                     (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x400)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_RMSK                                                     0x800003ff
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_POR                                                      0x00000000
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_POR_RMSK                                                 0xffffffff
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ATTR                                                                  0x3
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR,m,v,HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_IN)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_VALID_BMSK                                               0x80000000
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_VALID_SHFT                                                       31
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR_BMSK                                                     0x3ff
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR_SHFT                                                         0

#define HWIO_RSCC_RSC_SEQ_BUSY_DRV0_ADDR                                                                    (RSCC_PCIE_RSC_REG_BASE      + 0x404)
#define HWIO_RSCC_RSC_SEQ_BUSY_DRV0_OFFS                                                                    (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x404)
#define HWIO_RSCC_RSC_SEQ_BUSY_DRV0_RMSK                                                                           0x1
#define HWIO_RSCC_RSC_SEQ_BUSY_DRV0_POR                                                                     0x00000000
#define HWIO_RSCC_RSC_SEQ_BUSY_DRV0_POR_RMSK                                                                0xffffffff
#define HWIO_RSCC_RSC_SEQ_BUSY_DRV0_ATTR                                                                                 0x1
#define HWIO_RSCC_RSC_SEQ_BUSY_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_BUSY_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_BUSY_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_BUSY_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_BUSY_DRV0_BUSY_STAT_BMSK                                                                 0x1
#define HWIO_RSCC_RSC_SEQ_BUSY_DRV0_BUSY_STAT_SHFT                                                                   0

#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_ADDR                                                         (RSCC_PCIE_RSC_REG_BASE      + 0x408)
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_OFFS                                                         (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x408)
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_RMSK                                                              0x3ff
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_POR                                                          0x00000000
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_POR_RMSK                                                     0xffffffff
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_ATTR                                                                      0x1
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_CURRENT_INSTR_ADDR_BMSK                                           0x3ff
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_CURRENT_INSTR_ADDR_SHFT                                               0

#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_ADDR                                               (RSCC_PCIE_RSC_REG_BASE      + 0x40c)
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_OFFS                                               (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x40c)
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_RMSK                                                    0x3ff
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_POR                                                0x00000000
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_POR_RMSK                                           0xffffffff
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_ATTR                                                            0x1
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_CURRENT_INSTR_ADDR_BMSK                                 0x3ff
#define HWIO_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_CURRENT_INSTR_ADDR_SHFT                                     0

#define HWIO_RSCC_RSC_SEQ_COMP_DRV0_ADDR                                                                    (RSCC_PCIE_RSC_REG_BASE      + 0x410)
#define HWIO_RSCC_RSC_SEQ_COMP_DRV0_OFFS                                                                    (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x410)
#define HWIO_RSCC_RSC_SEQ_COMP_DRV0_RMSK                                                                    0x80000001
#define HWIO_RSCC_RSC_SEQ_COMP_DRV0_POR                                                                     0x00000000
#define HWIO_RSCC_RSC_SEQ_COMP_DRV0_POR_RMSK                                                                0xffffffff
#define HWIO_RSCC_RSC_SEQ_COMP_DRV0_ATTR                                                                                 0x0
#define HWIO_RSCC_RSC_SEQ_COMP_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_COMP_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_COMP_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_COMP_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_COMP_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_SEQ_COMP_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_SEQ_COMP_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_SEQ_COMP_DRV0_ADDR,m,v,HWIO_RSCC_RSC_SEQ_COMP_DRV0_IN)
#define HWIO_RSCC_RSC_SEQ_COMP_DRV0_CLEAR_BMSK                                                              0x80000000
#define HWIO_RSCC_RSC_SEQ_COMP_DRV0_CLEAR_SHFT                                                                      31
#define HWIO_RSCC_RSC_SEQ_COMP_DRV0_COMP_STAT_BMSK                                                                 0x1
#define HWIO_RSCC_RSC_SEQ_COMP_DRV0_COMP_STAT_SHFT                                                                   0

#define HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_ADDR(i)                                                      (RSCC_PCIE_RSC_REG_BASE      + 0X450 + (0x4*(i)))
#define HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_OFFS(i)                                                      (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X450 + (0x4*(i)))
#define HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_RMSK                                                            0xfffff
#define HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_MAXi                                                                  3
#define HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_POR                                                          0x00000000
#define HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_POR_RMSK                                                     0xffffffff
#define HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_ATTR                                                                      0x3
#define HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_INI(i)                \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_ADDR(i), HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_RMSK)
#define HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_INMI(i,mask)        \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_ADDR(i), mask)
#define HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_OUTI(i,val)        \
                out_dword(HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_ADDR(i),val)
#define HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_OUTMI(i,mask,val) \
                out_dword_masked_ns(HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_ADDR(i),mask,val,HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_INI(i))
#define HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_DELAY_VAL_BMSK                                                  0xfffff
#define HWIO_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_DELAY_VAL_SHFT                                                        0

#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_ADDR                                                        (RSCC_PCIE_RSC_REG_BASE      + 0x460)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_OFFS                                                        (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x460)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_RMSK                                                               0x1
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_POR                                                         0x00000000
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_POR_RMSK                                                    0xffffffff
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_ATTR                                                                     0x3
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_ADDR,m,v,HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_IN)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_SEQ_OVERRIDE_TRIGGER_BMSK                                          0x1
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_SEQ_OVERRIDE_TRIGGER_SHFT                                            0

#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_ADDR                                          (RSCC_PCIE_RSC_REG_BASE      + 0x464)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_OFFS                                          (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x464)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_RMSK                                               0x3ff
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_POR                                           0x00000000
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_POR_RMSK                                      0xffffffff
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_ATTR                                                       0x3
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_ADDR,m,v,HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_IN)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_SEQ_OVERRIDE_TRIGGER_START_ADDR_BMSK               0x3ff
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_SEQ_OVERRIDE_TRIGGER_START_ADDR_SHFT                   0

#define HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_ADDR                                                     (RSCC_PCIE_RSC_REG_BASE      + 0x490)
#define HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_OFFS                                                     (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x490)
#define HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_RMSK                                                     0x800003ff
#define HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_POR                                                      0x00000000
#define HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_POR_RMSK                                                 0xffffffff
#define HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_ATTR                                                                  0x3
#define HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_ADDR,m,v,HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_IN)
#define HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_DBG_BREAKPOINT_VALID_BMSK                                0x80000000
#define HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_DBG_BREAKPOINT_VALID_SHFT                                        31
#define HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_DBG_BREAKPOINT_ADDR_BMSK                                      0x3ff
#define HWIO_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_DBG_BREAKPOINT_ADDR_SHFT                                          0

#define HWIO_RSCC_RSC_SEQ_DBG_STEP_DRV0_ADDR                                                                (RSCC_PCIE_RSC_REG_BASE      + 0x494)
#define HWIO_RSCC_RSC_SEQ_DBG_STEP_DRV0_OFFS                                                                (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x494)
#define HWIO_RSCC_RSC_SEQ_DBG_STEP_DRV0_RMSK                                                                       0x1
#define HWIO_RSCC_RSC_SEQ_DBG_STEP_DRV0_POR                                                                 0x00000000
#define HWIO_RSCC_RSC_SEQ_DBG_STEP_DRV0_POR_RMSK                                                            0xffffffff
#define HWIO_RSCC_RSC_SEQ_DBG_STEP_DRV0_ATTR                                                                             0x3
#define HWIO_RSCC_RSC_SEQ_DBG_STEP_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_DBG_STEP_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_DBG_STEP_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_DBG_STEP_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_DBG_STEP_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_SEQ_DBG_STEP_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_SEQ_DBG_STEP_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_SEQ_DBG_STEP_DRV0_ADDR,m,v,HWIO_RSCC_RSC_SEQ_DBG_STEP_DRV0_IN)
#define HWIO_RSCC_RSC_SEQ_DBG_STEP_DRV0_DBG_STEP_TRIGGER_BMSK                                                      0x1
#define HWIO_RSCC_RSC_SEQ_DBG_STEP_DRV0_DBG_STEP_TRIGGER_SHFT                                                        0

#define HWIO_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_ADDR                                                            (RSCC_PCIE_RSC_REG_BASE      + 0x498)
#define HWIO_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_OFFS                                                            (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x498)
#define HWIO_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_RMSK                                                                   0x1
#define HWIO_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_POR                                                             0x00000000
#define HWIO_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_POR_RMSK                                                        0xffffffff
#define HWIO_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_ATTR                                                                         0x3
#define HWIO_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_ADDR,m,v,HWIO_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_IN)
#define HWIO_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_DBG_STEP_CONTINUE_BMSK                                                 0x1
#define HWIO_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_DBG_STEP_CONTINUE_SHFT                                                   0

#define HWIO_RSCC_RSC_SEQ_DBG_STAT_DRV0_ADDR                                                                (RSCC_PCIE_RSC_REG_BASE      + 0x49c)
#define HWIO_RSCC_RSC_SEQ_DBG_STAT_DRV0_OFFS                                                                (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x49c)
#define HWIO_RSCC_RSC_SEQ_DBG_STAT_DRV0_RMSK                                                                       0x1
#define HWIO_RSCC_RSC_SEQ_DBG_STAT_DRV0_POR                                                                 0x00000000
#define HWIO_RSCC_RSC_SEQ_DBG_STAT_DRV0_POR_RMSK                                                            0xffffffff
#define HWIO_RSCC_RSC_SEQ_DBG_STAT_DRV0_ATTR                                                                             0x1
#define HWIO_RSCC_RSC_SEQ_DBG_STAT_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_DBG_STAT_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_DBG_STAT_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_DBG_STAT_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_DBG_STAT_DRV0_DBG_STEPPING_STATUS_BMSK                                                   0x1
#define HWIO_RSCC_RSC_SEQ_DBG_STAT_DRV0_DBG_STEPPING_STATUS_SHFT                                                     0

#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_ADDR                                                 (RSCC_PCIE_RSC_REG_BASE      + 0x4a0)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_OFFS                                                 (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x4a0)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_RMSK                                                       0x3f
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_POR                                                  0x00000000
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_POR_RMSK                                             0xffffffff
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_ATTR                                                              0x3
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_ADDR,m,v,HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_IN)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_SEQ_OVERRIDE_PWR_CNTRL_MASK_BMSK                           0x3f
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_SEQ_OVERRIDE_PWR_CNTRL_MASK_SHFT                              0

#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_ADDR                                                  (RSCC_PCIE_RSC_REG_BASE      + 0x4a4)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_OFFS                                                  (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x4a4)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_RMSK                                                        0x3f
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_POR                                                   0x00000000
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_POR_RMSK                                              0xffffffff
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_ATTR                                                               0x3
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_ADDR,m,v,HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_IN)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_SEQ_OVERRIDE_PWR_CNTRL_VAL_BMSK                             0x3f
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_SEQ_OVERRIDE_PWR_CNTRL_VAL_SHFT                                0

#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_ADDR                                                (RSCC_PCIE_RSC_REG_BASE      + 0x4a8)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_OFFS                                                (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x4a8)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_RMSK                                                      0x3f
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_POR                                                 0x00000000
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_POR_RMSK                                            0xffffffff
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_ATTR                                                             0x3
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_ADDR,m,v,HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_IN)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_SEQ_OVERRIDE_WAIT_EVENT_MASK_BMSK                         0x3f
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_SEQ_OVERRIDE_WAIT_EVENT_MASK_SHFT                            0

#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_ADDR                                                 (RSCC_PCIE_RSC_REG_BASE      + 0x4ac)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_OFFS                                                 (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x4ac)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_RMSK                                                       0x3f
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_POR                                                  0x00000000
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_POR_RMSK                                             0xffffffff
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_ATTR                                                              0x3
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_ADDR,v)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_ADDR,m,v,HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_IN)
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_SEQ_OVERRIDE_WAIT_EVENT_VAL_BMSK                           0x3f
#define HWIO_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_SEQ_OVERRIDE_WAIT_EVENT_VAL_SHFT                              0

#define HWIO_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_ADDR                                                         (RSCC_PCIE_RSC_REG_BASE      + 0x4b0)
#define HWIO_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_OFFS                                                         (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x4b0)
#define HWIO_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_RMSK                                                         0xffffffff
#define HWIO_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_POR                                                          0x00000000
#define HWIO_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_POR_RMSK                                                     0xffffffff
#define HWIO_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_ATTR                                                                      0x1
#define HWIO_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_PWR_CTRL_STATUS_BMSK                                         0xffffffff
#define HWIO_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_PWR_CTRL_STATUS_SHFT                                                  0

#define HWIO_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_ADDR                                                        (RSCC_PCIE_RSC_REG_BASE      + 0x4b4)
#define HWIO_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_OFFS                                                        (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x4b4)
#define HWIO_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_RMSK                                                        0xffffffff
#define HWIO_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_POR                                                         0x00000000
#define HWIO_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_POR_RMSK                                                    0xffffffff
#define HWIO_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_ATTR                                                                     0x1
#define HWIO_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_PWR_EVENT_STATUS_BMSK                                       0xffffffff
#define HWIO_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_PWR_EVENT_STATUS_SHFT                                                0

#define HWIO_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_ADDR                                                         (RSCC_PCIE_RSC_REG_BASE      + 0x4b8)
#define HWIO_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_OFFS                                                         (RSCC_PCIE_RSC_REG_BASE_OFFS + 0x4b8)
#define HWIO_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_RMSK                                                         0xffffffff
#define HWIO_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_POR                                                          0x00000000
#define HWIO_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_POR_RMSK                                                     0xffffffff
#define HWIO_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_ATTR                                                                      0x1
#define HWIO_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_IN                    \
                in_dword(HWIO_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_ADDR)
#define HWIO_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_ADDR, m)
#define HWIO_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_BR_EVENT_STATUS_BMSK                                         0xffffffff
#define HWIO_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_BR_EVENT_STATUS_SHFT                                                  0

#define HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR(i)                                                        (RSCC_PCIE_RSC_REG_BASE      + 0X4BC + (0x4*(i)))
#define HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_OFFS(i)                                                        (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X4BC + (0x4*(i)))
#define HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_RMSK                                                                0x3ff
#define HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_MAXi                                                                    3
#define HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_POR                                                            0x00000000
#define HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_POR_RMSK                                                       0xffffffff
#define HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ATTR                                                                        0x3
#define HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_INI(i)                \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR(i), HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_RMSK)
#define HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_INMI(i,mask)        \
                in_dword_masked(HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR(i), mask)
#define HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_OUTI(i,val)        \
                out_dword(HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR(i),val)
#define HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_OUTMI(i,mask,val) \
                out_dword_masked_ns(HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR(i),mask,val,HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_INI(i))
#define HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR_BMSK                                                           0x3ff
#define HWIO_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR_SHFT                                                               0

#define HWIO_RSCC_SEQ_MEM_m_DRV0_ADDR(m)                                                                    (RSCC_PCIE_RSC_REG_BASE      + 0X550 + (0x4*(m)))
#define HWIO_RSCC_SEQ_MEM_m_DRV0_OFFS(m)                                                                    (RSCC_PCIE_RSC_REG_BASE_OFFS + 0X550 + (0x4*(m)))
#define HWIO_RSCC_SEQ_MEM_m_DRV0_RMSK                                                                       0xffffffff
#define HWIO_RSCC_SEQ_MEM_m_DRV0_MAXm                                                                               15
#define HWIO_RSCC_SEQ_MEM_m_DRV0_POR                                                                        0x00000000
#define HWIO_RSCC_SEQ_MEM_m_DRV0_POR_RMSK                                                                   0xffffffff
#define HWIO_RSCC_SEQ_MEM_m_DRV0_ATTR                                                                                    0x3
#define HWIO_RSCC_SEQ_MEM_m_DRV0_INI(m)                \
                in_dword_masked(HWIO_RSCC_SEQ_MEM_m_DRV0_ADDR(m), HWIO_RSCC_SEQ_MEM_m_DRV0_RMSK)
#define HWIO_RSCC_SEQ_MEM_m_DRV0_INMI(m,mask)        \
                in_dword_masked(HWIO_RSCC_SEQ_MEM_m_DRV0_ADDR(m), mask)
#define HWIO_RSCC_SEQ_MEM_m_DRV0_OUTI(m,val)        \
                out_dword(HWIO_RSCC_SEQ_MEM_m_DRV0_ADDR(m),val)
#define HWIO_RSCC_SEQ_MEM_m_DRV0_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RSCC_SEQ_MEM_m_DRV0_ADDR(m),mask,val,HWIO_RSCC_SEQ_MEM_m_DRV0_INI(m))
#define HWIO_RSCC_SEQ_MEM_m_DRV0_CMD_WORD_BMSK                                                              0xffffffff
#define HWIO_RSCC_SEQ_MEM_m_DRV0_CMD_WORD_SHFT                                                                       0

#define HWIO_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_ADDR                                                         (RSCC_PCIE_RSC_REG_BASE      + 0xd00)
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_OFFS                                                         (RSCC_PCIE_RSC_REG_BASE_OFFS + 0xd00)
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_RMSK                                                                0x1
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_POR                                                          0x00000000
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_POR_RMSK                                                     0xffffffff
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_ATTR                                                                      0x3
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_IN                    \
                in_dword(HWIO_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_ADDR)
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_ADDR, m)
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_ADDR,v)
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_ADDR,m,v,HWIO_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_IN)
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_AMC_COMPLETION_IRQ_ENABLE_BMSK                                      0x1
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_AMC_COMPLETION_IRQ_ENABLE_SHFT                                        0

#define HWIO_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_ADDR                                                         (RSCC_PCIE_RSC_REG_BASE      + 0xd04)
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_OFFS                                                         (RSCC_PCIE_RSC_REG_BASE_OFFS + 0xd04)
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_RMSK                                                                0x1
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_POR                                                          0x00000000
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_POR_RMSK                                                     0xffffffff
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_ATTR                                                                      0x1
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_IN                    \
                in_dword(HWIO_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_ADDR)
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_ADDR, m)
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_AMC_COMPLETION_IRQ_STATUS_BMSK                                      0x1
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_AMC_COMPLETION_IRQ_STATUS_SHFT                                        0

#define HWIO_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_ADDR                                                          (RSCC_PCIE_RSC_REG_BASE      + 0xd08)
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_OFFS                                                          (RSCC_PCIE_RSC_REG_BASE_OFFS + 0xd08)
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_RMSK                                                                 0x1
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_POR                                                           0x00000000
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_POR_RMSK                                                      0xffffffff
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_ATTR                                                                       0x0
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_ADDR,v)
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_AMC_COMPLETION_IRQ_CLEAR_BMSK                                        0x1
#define HWIO_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_AMC_COMPLETION_IRQ_CLEAR_SHFT                                          0

#define HWIO_RSCC_TCS_TIMEOUT_EN_DRV0_ADDR                                                                  (RSCC_PCIE_RSC_REG_BASE      + 0xd10)
#define HWIO_RSCC_TCS_TIMEOUT_EN_DRV0_OFFS                                                                  (RSCC_PCIE_RSC_REG_BASE_OFFS + 0xd10)
#define HWIO_RSCC_TCS_TIMEOUT_EN_DRV0_RMSK                                                                         0x1
#define HWIO_RSCC_TCS_TIMEOUT_EN_DRV0_POR                                                                   0x00000000
#define HWIO_RSCC_TCS_TIMEOUT_EN_DRV0_POR_RMSK                                                              0xffffffff
#define HWIO_RSCC_TCS_TIMEOUT_EN_DRV0_ATTR                                                                               0x3
#define HWIO_RSCC_TCS_TIMEOUT_EN_DRV0_IN                    \
                in_dword(HWIO_RSCC_TCS_TIMEOUT_EN_DRV0_ADDR)
#define HWIO_RSCC_TCS_TIMEOUT_EN_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_TCS_TIMEOUT_EN_DRV0_ADDR, m)
#define HWIO_RSCC_TCS_TIMEOUT_EN_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_TCS_TIMEOUT_EN_DRV0_ADDR,v)
#define HWIO_RSCC_TCS_TIMEOUT_EN_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_TCS_TIMEOUT_EN_DRV0_ADDR,m,v,HWIO_RSCC_TCS_TIMEOUT_EN_DRV0_IN)
#define HWIO_RSCC_TCS_TIMEOUT_EN_DRV0_EN_BMSK                                                                      0x1
#define HWIO_RSCC_TCS_TIMEOUT_EN_DRV0_EN_SHFT                                                                        0

#define HWIO_RSCC_TCS_TIMEOUT_CLR_DRV0_ADDR                                                                 (RSCC_PCIE_RSC_REG_BASE      + 0xd14)
#define HWIO_RSCC_TCS_TIMEOUT_CLR_DRV0_OFFS                                                                 (RSCC_PCIE_RSC_REG_BASE_OFFS + 0xd14)
#define HWIO_RSCC_TCS_TIMEOUT_CLR_DRV0_RMSK                                                                        0x1
#define HWIO_RSCC_TCS_TIMEOUT_CLR_DRV0_POR                                                                  0x00000000
#define HWIO_RSCC_TCS_TIMEOUT_CLR_DRV0_POR_RMSK                                                             0xffffffff
#define HWIO_RSCC_TCS_TIMEOUT_CLR_DRV0_ATTR                                                                              0x0
#define HWIO_RSCC_TCS_TIMEOUT_CLR_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_TCS_TIMEOUT_CLR_DRV0_ADDR,v)
#define HWIO_RSCC_TCS_TIMEOUT_CLR_DRV0_CLR_BMSK                                                                    0x1
#define HWIO_RSCC_TCS_TIMEOUT_CLR_DRV0_CLR_SHFT                                                                      0

#define HWIO_RSCC_TCS_TIMEOUT_STATUS_DRV0_ADDR                                                              (RSCC_PCIE_RSC_REG_BASE      + 0xd18)
#define HWIO_RSCC_TCS_TIMEOUT_STATUS_DRV0_OFFS                                                              (RSCC_PCIE_RSC_REG_BASE_OFFS + 0xd18)
#define HWIO_RSCC_TCS_TIMEOUT_STATUS_DRV0_RMSK                                                                     0x1
#define HWIO_RSCC_TCS_TIMEOUT_STATUS_DRV0_POR                                                               0x00000000
#define HWIO_RSCC_TCS_TIMEOUT_STATUS_DRV0_POR_RMSK                                                          0xffffffff
#define HWIO_RSCC_TCS_TIMEOUT_STATUS_DRV0_ATTR                                                                           0x1
#define HWIO_RSCC_TCS_TIMEOUT_STATUS_DRV0_IN                    \
                in_dword(HWIO_RSCC_TCS_TIMEOUT_STATUS_DRV0_ADDR)
#define HWIO_RSCC_TCS_TIMEOUT_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_TCS_TIMEOUT_STATUS_DRV0_ADDR, m)
#define HWIO_RSCC_TCS_TIMEOUT_STATUS_DRV0_TIMEOUT_BMSK                                                             0x1
#define HWIO_RSCC_TCS_TIMEOUT_STATUS_DRV0_TIMEOUT_SHFT                                                               0

#define HWIO_RSCC_TCS_TIMEOUT_VAL_DRV0_ADDR                                                                 (RSCC_PCIE_RSC_REG_BASE      + 0xd1c)
#define HWIO_RSCC_TCS_TIMEOUT_VAL_DRV0_OFFS                                                                 (RSCC_PCIE_RSC_REG_BASE_OFFS + 0xd1c)
#define HWIO_RSCC_TCS_TIMEOUT_VAL_DRV0_RMSK                                                                     0xffff
#define HWIO_RSCC_TCS_TIMEOUT_VAL_DRV0_POR                                                                  0x0000ffff
#define HWIO_RSCC_TCS_TIMEOUT_VAL_DRV0_POR_RMSK                                                             0xffffffff
#define HWIO_RSCC_TCS_TIMEOUT_VAL_DRV0_ATTR                                                                              0x3
#define HWIO_RSCC_TCS_TIMEOUT_VAL_DRV0_IN                    \
                in_dword(HWIO_RSCC_TCS_TIMEOUT_VAL_DRV0_ADDR)
#define HWIO_RSCC_TCS_TIMEOUT_VAL_DRV0_INM(m)            \
                in_dword_masked(HWIO_RSCC_TCS_TIMEOUT_VAL_DRV0_ADDR, m)
#define HWIO_RSCC_TCS_TIMEOUT_VAL_DRV0_OUT(v)            \
                out_dword(HWIO_RSCC_TCS_TIMEOUT_VAL_DRV0_ADDR,v)
#define HWIO_RSCC_TCS_TIMEOUT_VAL_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_RSCC_TCS_TIMEOUT_VAL_DRV0_ADDR,m,v,HWIO_RSCC_TCS_TIMEOUT_VAL_DRV0_IN)
#define HWIO_RSCC_TCS_TIMEOUT_VAL_DRV0_TIMEOUT_VAL_BMSK                                                         0xffff
#define HWIO_RSCC_TCS_TIMEOUT_VAL_DRV0_TIMEOUT_VAL_SHFT                                                              0

#define HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_ADDR(m)                                                       (RSCC_PCIE_RSC_REG_BASE      + 0XD20 + (0x2A0*(m)))
#define HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_OFFS(m)                                                       (RSCC_PCIE_RSC_REG_BASE_OFFS + 0XD20 + (0x2A0*(m)))
#define HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_RMSK                                                                 0x1
#define HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_MAXm                                                                   0
#define HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_POR                                                           0x00000000
#define HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_POR_RMSK                                                      0xffffffff
#define HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_ATTR                                                                       0x3
#define HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_INI(m)                \
                in_dword_masked(HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_ADDR(m), HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_RMSK)
#define HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_INMI(m,mask)        \
                in_dword_masked(HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_ADDR(m), mask)
#define HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_OUTI(m,val)        \
                out_dword(HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_ADDR(m),val)
#define HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_ADDR(m),mask,val,HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_INI(m))
#define HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_CMD_WAIT_FOR_CMPL_BMSK                                               0x1
#define HWIO_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_CMD_WAIT_FOR_CMPL_SHFT                                                 0

#define HWIO_RSCC_TCSm_DRV0_CONTROL_ADDR(m)                                                                 (RSCC_PCIE_RSC_REG_BASE      + 0XD24 + (0x2A0*(m)))
#define HWIO_RSCC_TCSm_DRV0_CONTROL_OFFS(m)                                                                 (RSCC_PCIE_RSC_REG_BASE_OFFS + 0XD24 + (0x2A0*(m)))
#define HWIO_RSCC_TCSm_DRV0_CONTROL_RMSK                                                                     0x1010000
#define HWIO_RSCC_TCSm_DRV0_CONTROL_MAXm                                                                             0
#define HWIO_RSCC_TCSm_DRV0_CONTROL_POR                                                                     0x00000000
#define HWIO_RSCC_TCSm_DRV0_CONTROL_POR_RMSK                                                                0xffffffff
#define HWIO_RSCC_TCSm_DRV0_CONTROL_ATTR                                                                                 0x3
#define HWIO_RSCC_TCSm_DRV0_CONTROL_INI(m)                \
                in_dword_masked(HWIO_RSCC_TCSm_DRV0_CONTROL_ADDR(m), HWIO_RSCC_TCSm_DRV0_CONTROL_RMSK)
#define HWIO_RSCC_TCSm_DRV0_CONTROL_INMI(m,mask)        \
                in_dword_masked(HWIO_RSCC_TCSm_DRV0_CONTROL_ADDR(m), mask)
#define HWIO_RSCC_TCSm_DRV0_CONTROL_OUTI(m,val)        \
                out_dword(HWIO_RSCC_TCSm_DRV0_CONTROL_ADDR(m),val)
#define HWIO_RSCC_TCSm_DRV0_CONTROL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RSCC_TCSm_DRV0_CONTROL_ADDR(m),mask,val,HWIO_RSCC_TCSm_DRV0_CONTROL_INI(m))
#define HWIO_RSCC_TCSm_DRV0_CONTROL_AMC_MODE_TRIGGER_BMSK                                                    0x1000000
#define HWIO_RSCC_TCSm_DRV0_CONTROL_AMC_MODE_TRIGGER_SHFT                                                           24
#define HWIO_RSCC_TCSm_DRV0_CONTROL_AMC_MODE_EN_BMSK                                                           0x10000
#define HWIO_RSCC_TCSm_DRV0_CONTROL_AMC_MODE_EN_SHFT                                                                16
#define HWIO_RSCC_TCSm_DRV0_CONTROL_AMC_MODE_EN_AMC_MODE_DISABLE_FVAL                                              0x0
#define HWIO_RSCC_TCSm_DRV0_CONTROL_AMC_MODE_EN_AMC_MODE_ENABLED_FVAL                                              0x1

#define HWIO_RSCC_TCSm_DRV0_STATUS_ADDR(m)                                                                  (RSCC_PCIE_RSC_REG_BASE      + 0XD28 + (0x2A0*(m)))
#define HWIO_RSCC_TCSm_DRV0_STATUS_OFFS(m)                                                                  (RSCC_PCIE_RSC_REG_BASE_OFFS + 0XD28 + (0x2A0*(m)))
#define HWIO_RSCC_TCSm_DRV0_STATUS_RMSK                                                                            0x1
#define HWIO_RSCC_TCSm_DRV0_STATUS_MAXm                                                                              0
#define HWIO_RSCC_TCSm_DRV0_STATUS_POR                                                                      0x00000001
#define HWIO_RSCC_TCSm_DRV0_STATUS_POR_RMSK                                                                 0xffffffff
#define HWIO_RSCC_TCSm_DRV0_STATUS_ATTR                                                                                  0x1
#define HWIO_RSCC_TCSm_DRV0_STATUS_INI(m)                \
                in_dword_masked(HWIO_RSCC_TCSm_DRV0_STATUS_ADDR(m), HWIO_RSCC_TCSm_DRV0_STATUS_RMSK)
#define HWIO_RSCC_TCSm_DRV0_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_RSCC_TCSm_DRV0_STATUS_ADDR(m), mask)
#define HWIO_RSCC_TCSm_DRV0_STATUS_CONTROLLER_IDLE_BMSK                                                            0x1
#define HWIO_RSCC_TCSm_DRV0_STATUS_CONTROLLER_IDLE_SHFT                                                              0
#define HWIO_RSCC_TCSm_DRV0_STATUS_CONTROLLER_IDLE_NOT_IDLE_FVAL                                                   0x0
#define HWIO_RSCC_TCSm_DRV0_STATUS_CONTROLLER_IDLE_IS_IDLE_FVAL                                                    0x1

#define HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_ADDR(m)                                                              (RSCC_PCIE_RSC_REG_BASE      + 0XD2C + (0x2A0*(m)))
#define HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_OFFS(m)                                                              (RSCC_PCIE_RSC_REG_BASE_OFFS + 0XD2C + (0x2A0*(m)))
#define HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_RMSK                                                                        0x1
#define HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_MAXm                                                                          0
#define HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_POR                                                                  0x00000000
#define HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_POR_RMSK                                                             0xffffffff
#define HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_ATTR                                                                              0x3
#define HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_INI(m)                \
                in_dword_masked(HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_ADDR(m), HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_RMSK)
#define HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_INMI(m,mask)        \
                in_dword_masked(HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_ADDR(m), mask)
#define HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_OUTI(m,val)        \
                out_dword(HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_ADDR(m),val)
#define HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_ADDR(m),mask,val,HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_INI(m))
#define HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_INDIVIDUAL_CMD_ENABLE_MASK_BMSK                                             0x1
#define HWIO_RSCC_TCSm_DRV0_CMD_ENABLE_INDIVIDUAL_CMD_ENABLE_MASK_SHFT                                               0

#define HWIO_RSCC_TCSm_DRV0_PROFILING_STATUS_ADDR(m)                                                        (RSCC_PCIE_RSC_REG_BASE      + 0XD30 + (0x2A0*(m)))
#define HWIO_RSCC_TCSm_DRV0_PROFILING_STATUS_OFFS(m)                                                        (RSCC_PCIE_RSC_REG_BASE_OFFS + 0XD30 + (0x2A0*(m)))
#define HWIO_RSCC_TCSm_DRV0_PROFILING_STATUS_RMSK                                                                  0x1
#define HWIO_RSCC_TCSm_DRV0_PROFILING_STATUS_MAXm                                                                    0
#define HWIO_RSCC_TCSm_DRV0_PROFILING_STATUS_POR                                                            0x00000001
#define HWIO_RSCC_TCSm_DRV0_PROFILING_STATUS_POR_RMSK                                                       0xffffffff
#define HWIO_RSCC_TCSm_DRV0_PROFILING_STATUS_ATTR                                                                        0x1
#define HWIO_RSCC_TCSm_DRV0_PROFILING_STATUS_INI(m)                \
                in_dword_masked(HWIO_RSCC_TCSm_DRV0_PROFILING_STATUS_ADDR(m), HWIO_RSCC_TCSm_DRV0_PROFILING_STATUS_RMSK)
#define HWIO_RSCC_TCSm_DRV0_PROFILING_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_RSCC_TCSm_DRV0_PROFILING_STATUS_ADDR(m), mask)
#define HWIO_RSCC_TCSm_DRV0_PROFILING_STATUS_CONTROLLER_IDLE_BMSK                                                  0x1
#define HWIO_RSCC_TCSm_DRV0_PROFILING_STATUS_CONTROLLER_IDLE_SHFT                                                    0
#define HWIO_RSCC_TCSm_DRV0_PROFILING_STATUS_CONTROLLER_IDLE_NOT_IDLE_FVAL                                         0x0
#define HWIO_RSCC_TCSm_DRV0_PROFILING_STATUS_CONTROLLER_IDLE_IS_IDLE_FVAL                                          0x1

#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_ADDR(m,n)                                                            (RSCC_PCIE_RSC_REG_BASE      + 0XD34 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_OFFS(m,n)                                                            (RSCC_PCIE_RSC_REG_BASE_OFFS + 0XD34 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_RMSK                                                                    0x1010f
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_MAXm                                                                          0
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_MAXn                                                                          0
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_POR                                                                  0x00000000
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_POR_RMSK                                                             0xffffffff
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_ATTR                                                                              0x3
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_INI2(m,n)                \
                in_dword_masked(HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_ADDR(m,n), HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_RMSK)
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_ADDR(m,n), mask)
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_OUTI2(m,n,val)        \
                out_dword(HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_ADDR(m,n),val)
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_ADDR(m,n),mask,val,HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_INI2(m,n))
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_READ_OR_WRITE_BMSK                                                      0x10000
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_READ_OR_WRITE_SHFT                                                           16
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_READ_OR_WRITE_READ_FVAL                                                     0x0
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_READ_OR_WRITE_WRITE_FVAL                                                    0x1
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_RES_REQ_BMSK                                                              0x100
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_RES_REQ_SHFT                                                                  8
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_RES_REQ_FIRE_AND_FORGET_FVAL                                                0x0
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_RES_REQ_RESPONSE_REQUIRED_FVAL                                              0x1
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_MSG_LENGTH_BMSK                                                             0xf
#define HWIO_RSCC_TCSm_CMDn_DRV0_MSGID_MSG_LENGTH_SHFT                                                               0

#define HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_ADDR(m,n)                                                             (RSCC_PCIE_RSC_REG_BASE      + 0XD38 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_OFFS(m,n)                                                             (RSCC_PCIE_RSC_REG_BASE_OFFS + 0XD38 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_RMSK                                                                     0x7ffff
#define HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_MAXm                                                                           0
#define HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_MAXn                                                                           0
#define HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_POR                                                                   0x00000000
#define HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_POR_RMSK                                                              0xffffffff
#define HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_ATTR                                                                               0x3
#define HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_INI2(m,n)                \
                in_dword_masked(HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_ADDR(m,n), HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_RMSK)
#define HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_ADDR(m,n), mask)
#define HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_OUTI2(m,n,val)        \
                out_dword(HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_ADDR(m,n),val)
#define HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_ADDR(m,n),mask,val,HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_INI2(m,n))
#define HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_SLV_ID_BMSK                                                              0x70000
#define HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_SLV_ID_SHFT                                                                   16
#define HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_OFFSET_BMSK                                                               0xffff
#define HWIO_RSCC_TCSm_CMDn_DRV0_ADDR_OFFSET_SHFT                                                                    0

#define HWIO_RSCC_TCSm_CMDn_DRV0_DATA_ADDR(m,n)                                                             (RSCC_PCIE_RSC_REG_BASE      + 0XD3C + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_RSCC_TCSm_CMDn_DRV0_DATA_OFFS(m,n)                                                             (RSCC_PCIE_RSC_REG_BASE_OFFS + 0XD3C + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_RSCC_TCSm_CMDn_DRV0_DATA_RMSK                                                                  0xffffffff
#define HWIO_RSCC_TCSm_CMDn_DRV0_DATA_MAXm                                                                           0
#define HWIO_RSCC_TCSm_CMDn_DRV0_DATA_MAXn                                                                           0
#define HWIO_RSCC_TCSm_CMDn_DRV0_DATA_POR                                                                   0x00000000
#define HWIO_RSCC_TCSm_CMDn_DRV0_DATA_POR_RMSK                                                              0xffffffff
#define HWIO_RSCC_TCSm_CMDn_DRV0_DATA_ATTR                                                                               0x3
#define HWIO_RSCC_TCSm_CMDn_DRV0_DATA_INI2(m,n)                \
                in_dword_masked(HWIO_RSCC_TCSm_CMDn_DRV0_DATA_ADDR(m,n), HWIO_RSCC_TCSm_CMDn_DRV0_DATA_RMSK)
#define HWIO_RSCC_TCSm_CMDn_DRV0_DATA_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_RSCC_TCSm_CMDn_DRV0_DATA_ADDR(m,n), mask)
#define HWIO_RSCC_TCSm_CMDn_DRV0_DATA_OUTI2(m,n,val)        \
                out_dword(HWIO_RSCC_TCSm_CMDn_DRV0_DATA_ADDR(m,n),val)
#define HWIO_RSCC_TCSm_CMDn_DRV0_DATA_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_RSCC_TCSm_CMDn_DRV0_DATA_ADDR(m,n),mask,val,HWIO_RSCC_TCSm_CMDn_DRV0_DATA_INI2(m,n))
#define HWIO_RSCC_TCSm_CMDn_DRV0_DATA_DATA_BMSK                                                             0xffffffff
#define HWIO_RSCC_TCSm_CMDn_DRV0_DATA_DATA_SHFT                                                                      0

#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_ADDR(m,n)                                                           (RSCC_PCIE_RSC_REG_BASE      + 0XD40 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_OFFS(m,n)                                                           (RSCC_PCIE_RSC_REG_BASE_OFFS + 0XD40 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_RMSK                                                                   0x10101
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_MAXm                                                                         0
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_MAXn                                                                         0
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_POR                                                                 0x00000000
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_POR_RMSK                                                            0xffffffff
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_ATTR                                                                             0x1
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_INI2(m,n)                \
                in_dword_masked(HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_ADDR(m,n), HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_RMSK)
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_ADDR(m,n), mask)
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_COMPLETED_BMSK                                                         0x10000
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_COMPLETED_SHFT                                                              16
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_COMPLETED_HAS_NOT_BEEN_COMPLETE_FVAL                                       0x0
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_COMPLETED_HAS_COMPLETED_FVAL                                               0x1
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_ISSUED_BMSK                                                              0x100
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_ISSUED_SHFT                                                                  8
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_ISSUED_HAS_NOT_BEEN_SENT_OVER_EPCB_FVAL                                    0x0
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_ISSUED_HAS_BEEN_SENT_OVER_EPCB_FVAL                                        0x1
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_TRIGGERED_BMSK                                                             0x1
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_TRIGGERED_SHFT                                                               0
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_TRIGGERED_HAS_NOT_BEEN_TRIGGERE_FVAL                                       0x0
#define HWIO_RSCC_TCSm_CMDn_DRV0_STATUS_TRIGGERED_HAS_BEEN_TRIGGERED_FVAL                                          0x1

#define HWIO_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_ADDR(n)                                                 (RSCC_PCIE_RSC_REG_BASE      + 0XD44 + (0x18*(n)))
#define HWIO_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_OFFS(n)                                                 (RSCC_PCIE_RSC_REG_BASE_OFFS + 0XD44 + (0x18*(n)))
#define HWIO_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_RMSK                                                    0xffffffff
#define HWIO_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_MAXn                                                             0
#define HWIO_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_POR                                                     0x00000000
#define HWIO_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_POR_RMSK                                                0xffffffff
#define HWIO_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_ATTR                                                                 0x1
#define HWIO_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_INI(n)                \
                in_dword_masked(HWIO_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_ADDR(n), HWIO_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_RMSK)
#define HWIO_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_INMI(n,mask)        \
                in_dword_masked(HWIO_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_ADDR(n), mask)
#define HWIO_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_READ_RESPONSE_DATA_BMSK                                 0xffffffff
#define HWIO_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_READ_RESPONSE_DATA_SHFT                                          0

#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ADDR(m,n)                                                 (RSCC_PCIE_RSC_REG_BASE      + 0XD48 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_OFFS(m,n)                                                 (RSCC_PCIE_RSC_REG_BASE_OFFS + 0XD48 + (0x2A0*(m)) + (0x18*(n)))
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_RMSK                                                         0x10101
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_MAXm                                                               0
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_MAXn                                                               0
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_POR                                                       0x00000000
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_POR_RMSK                                                  0xffffffff
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ATTR                                                                   0x1
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_INI2(m,n)                \
                in_dword_masked(HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ADDR(m,n), HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_RMSK)
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ADDR(m,n), mask)
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_COMPLETED_BMSK                                               0x10000
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_COMPLETED_SHFT                                                    16
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_COMPLETED_HAS_NOT_BEEN_COMPLETE_FVAL                             0x0
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_COMPLETED_HAS_COMPLETED_FVAL                                     0x1
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ISSUED_BMSK                                                    0x100
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ISSUED_SHFT                                                        8
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ISSUED_HAS_NOT_BEEN_SENT_OVER_EPCB_FVAL                          0x0
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ISSUED_HAS_BEEN_SENT_OVER_EPCB_FVAL                              0x1
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_TRIGGERED_BMSK                                                   0x1
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_TRIGGERED_SHFT                                                     0
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_TRIGGERED_HAS_NOT_BEEN_TRIGGERE_FVAL                             0x0
#define HWIO_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_TRIGGERED_HAS_BEEN_TRIGGERED_FVAL                                0x1

/*----------------------------------------------------------------------------
 * MODULE: TITAN_RSCC_RSCC_RSC
 *--------------------------------------------------------------------------*/

#define TITAN_RSCC_RSCC_RSC_REG_BASE                                                                              (TITAN_SS_BASE      + 0x001d4000)
#define TITAN_RSCC_RSCC_RSC_REG_BASE_SIZE                                                                         0x3000
#define TITAN_RSCC_RSCC_RSC_REG_BASE_USED                                                                         0x2a60
#define TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS                                                                         0x001d4000

#define HWIO_TITAN_RSCC_RSC_ID_DRVd_ADDR(d)                                                                       (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X0 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_ID_DRVd_OFFS(d)                                                                       (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X0 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_ID_DRVd_RMSK                                                                            0xffffff
#define HWIO_TITAN_RSCC_RSC_ID_DRVd_MAXd                                                                                   2
#define HWIO_TITAN_RSCC_RSC_ID_DRVd_POR                                                                           0x00030200
#define HWIO_TITAN_RSCC_RSC_ID_DRVd_POR_RMSK                                                                      0xffffffff
#define HWIO_TITAN_RSCC_RSC_ID_DRVd_ATTR                                                                                       0x1
#define HWIO_TITAN_RSCC_RSC_ID_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_ID_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_ID_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_ID_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_ID_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_ID_DRVd_MAJOR_VER_BMSK                                                                  0xff0000
#define HWIO_TITAN_RSCC_RSC_ID_DRVd_MAJOR_VER_SHFT                                                                        16
#define HWIO_TITAN_RSCC_RSC_ID_DRVd_MINOR_VER_BMSK                                                                    0xff00
#define HWIO_TITAN_RSCC_RSC_ID_DRVd_MINOR_VER_SHFT                                                                         8
#define HWIO_TITAN_RSCC_RSC_ID_DRVd_STEP_VER_BMSK                                                                       0xff
#define HWIO_TITAN_RSCC_RSC_ID_DRVd_STEP_VER_SHFT                                                                          0

#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_ADDR(d)                                                      (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X4 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_OFFS(d)                                                      (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X4 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_RMSK                                                          0x71f1f1f
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_MAXd                                                                  2
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_POR                                                          0x00010100
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_POR_RMSK                                                     0xffffffff
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_ATTR                                                                      0x1
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SEQ_EXTENDED_BMSK                                             0x4000000
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SEQ_EXTENDED_SHFT                                                    26
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SEQ_EXTENDED_SIMPLE_FVAL                                            0x0
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SEQ_EXTENDED_EXTENDED_FVAL                                          0x1
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_IS_CHILD_RSC_BMSK                                             0x2000000
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_IS_CHILD_RSC_SHFT                                                    25
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_IS_CHILD_RSC_PARENT_RSC_FVAL                                        0x0
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_IS_CHILD_RSC_CHILD_RSC_FVAL                                         0x1
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_HW_SOLVER_BMSK                                                0x1000000
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_HW_SOLVER_SHFT                                                       24
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_HW_SOLVER_SOLVER_FALSE_FVAL                                         0x0
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_HW_SOLVER_SOLVER_TRUE_FVAL                                          0x1
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SOLVER_SLOTS_BMSK                                              0x1f0000
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SOLVER_SLOTS_SHFT                                                    16
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SOLVER_MODES_BMSK                                                0x1f00
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_SOLVER_MODES_SHFT                                                     8
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_NUM_TIMERS_BMSK                                                    0x1f
#define HWIO_TITAN_RSCC_RSC_PARAM_SOLVER_CONFIG_DRVd_NUM_TIMERS_SHFT                                                       0

#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_ADDR(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X8 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_OFFS(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X8 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_RMSK                                                             0x7ff0f1f
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_MAXd                                                                     2
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_POR                                                             0x03100214
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_ATTR                                                                         0x1
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_DRV_BMSK                                                     0x7000000
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_DRV_SHFT                                                            24
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_SEQ_CMD_WORDS_BMSK                                            0xff0000
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_SEQ_CMD_WORDS_SHFT                                                  16
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_TS_EVENTS_BMSK                                                   0xf00
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_NUM_TS_EVENTS_SHFT                                                       8
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_DELAY_CNTR_BITWIDTH_BMSK                                              0x1f
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_CONFIG_DRVd_DELAY_CNTR_BITWIDTH_SHFT                                                 0

#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_ADDR(d)                                             (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0XC + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_OFFS(d)                                             (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0XC + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_RMSK                                                0xf8ffffff
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_MAXd                                                         2
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_POR                                                 0x60004104
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_POR_RMSK                                            0xffffffff
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_ATTR                                                             0x1
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_CMDS_PER_TCS_BMSK                               0xf8000000
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_CMDS_PER_TCS_SHFT                                       27
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV3_BMSK                                     0xfc0000
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV3_SHFT                                           18
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV2_BMSK                                      0x3f000
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV2_SHFT                                           12
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV1_BMSK                                        0xfc0
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV1_SHFT                                            6
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV0_BMSK                                         0x3f
#define HWIO_TITAN_RSCC_RSC_PARAM_RSC_PARENTCHILD_CONFIG_DRVd_NUM_TCS_DRV0_SHFT                                            0

#define HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_ADDR(d)                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X10 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_OFFS(d)                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X10 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_RMSK                                                                      0x101ffff
#define HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_MAXd                                                                              2
#define HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_POR                                                                      0x00000000
#define HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_POR_RMSK                                                                 0xffffffff
#define HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_ATTR                                                                                  0x3
#define HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_OUTI(d,val)        \
                out_dword(HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_ADDR(d),val)
#define HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_ADDR(d),mask,val,HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_INI(d))
#define HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_CLK_GATE_DISABLE_BMSK                                                     0x1000000
#define HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_CLK_GATE_DISABLE_SHFT                                                            24
#define HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_STATUS_SLEEP_ENTRY_DONE_BMSK                                                0x10000
#define HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_STATUS_SLEEP_ENTRY_DONE_SHFT                                                     16
#define HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_STATUS_SLEEP_CTL_FSM_BMSK                                                    0xffff
#define HWIO_TITAN_RSCC_RSC_STATUS0_DRVd_STATUS_SLEEP_CTL_FSM_SHFT                                                         0

#define HWIO_TITAN_RSCC_RSC_STATUS1_DRVd_ADDR(d)                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X14 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_STATUS1_DRVd_OFFS(d)                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X14 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_STATUS1_DRVd_RMSK                                                                     0xffffffff
#define HWIO_TITAN_RSCC_RSC_STATUS1_DRVd_MAXd                                                                              2
#define HWIO_TITAN_RSCC_RSC_STATUS1_DRVd_POR                                                                      0x00000000
#define HWIO_TITAN_RSCC_RSC_STATUS1_DRVd_POR_RMSK                                                                 0xffffffff
#define HWIO_TITAN_RSCC_RSC_STATUS1_DRVd_ATTR                                                                                  0x1
#define HWIO_TITAN_RSCC_RSC_STATUS1_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_STATUS1_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_STATUS1_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_STATUS1_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_STATUS1_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_STATUS1_DRVd_PDC_MATCH_VALUE_LO_BMSK                                                  0xffffffff
#define HWIO_TITAN_RSCC_RSC_STATUS1_DRVd_PDC_MATCH_VALUE_LO_SHFT                                                           0

#define HWIO_TITAN_RSCC_RSC_STATUS2_DRVd_ADDR(d)                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X18 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_STATUS2_DRVd_OFFS(d)                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X18 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_STATUS2_DRVd_RMSK                                                                       0xffffff
#define HWIO_TITAN_RSCC_RSC_STATUS2_DRVd_MAXd                                                                              2
#define HWIO_TITAN_RSCC_RSC_STATUS2_DRVd_POR                                                                      0x00000000
#define HWIO_TITAN_RSCC_RSC_STATUS2_DRVd_POR_RMSK                                                                 0xffffffff
#define HWIO_TITAN_RSCC_RSC_STATUS2_DRVd_ATTR                                                                                  0x1
#define HWIO_TITAN_RSCC_RSC_STATUS2_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_STATUS2_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_STATUS2_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_STATUS2_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_STATUS2_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_STATUS2_DRVd_PDC_MATCH_VALUE_HI_BMSK                                                    0xffffff
#define HWIO_TITAN_RSCC_RSC_STATUS2_DRVd_PDC_MATCH_VALUE_HI_SHFT                                                           0

#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_ADDR                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x1c)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_OFFS                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x1c)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_RMSK                                                                    0x10003
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_POR                                                                  0x00000000
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_POR_RMSK                                                             0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_ATTR                                                                              0x3
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_ADDR)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_IN)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_HIDDEN_TCS_TRIGGER_BMSK                                                 0x10000
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_HIDDEN_TCS_TRIGGER_SHFT                                                      16
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_HIDDEN_TCS_PDC_TIMER_DRV_OWNER_BMSK                                         0x3
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRV0_HIDDEN_TCS_PDC_TIMER_DRV_OWNER_SHFT                                           0

#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRVd_ADDR(d)                                                              (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X1C + (0x1000*(d)))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRVd_OFFS(d)                                                              (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X1C + (0x1000*(d)))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRVd_RMSK                                                                        0x3
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRVd_MAXd                                                                          2
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRVd_POR                                                                  0x00000000
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRVd_POR_RMSK                                                             0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRVd_ATTR                                                                              0x1
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRVd_ADDR(d), HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRVd_RMSK)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRVd_HIDDEN_TCS_PDC_TIMER_DRV_OWNER_BMSK                                         0x3
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CTRL_DRVd_HIDDEN_TCS_PDC_TIMER_DRV_OWNER_SHFT                                           0

#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_ADDR                                                   (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x20)
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_OFFS                                                   (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x20)
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_RMSK                                                       0xffff
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_POR                                                    0x00004520
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_POR_RMSK                                               0xffffffff
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_ATTR                                                                0x3
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_ADDR)
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_IN)
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_PDC_SEQ_START_ADDR_REG_OFFSET_BMSK                         0xffff
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRV0_PDC_SEQ_START_ADDR_REG_OFFSET_SHFT                              0

#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_ADDR(d)                                                (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X20 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_OFFS(d)                                                (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X20 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_RMSK                                                       0xffff
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_MAXd                                                            2
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_POR                                                    0x00004520
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_POR_RMSK                                               0xffffffff
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_ATTR                                                                0x1
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_ADDR(d), HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_RMSK)
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_PDC_SEQ_START_ADDR_REG_OFFSET_BMSK                         0xffff
#define HWIO_TITAN_RSCC_PDC_SEQ_START_ADDR_REG_OFFSET_DRVd_PDC_SEQ_START_ADDR_REG_OFFSET_SHFT                              0

#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_ADDR                                                   (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x24)
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_OFFS                                                   (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x24)
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_RMSK                                                       0xffff
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_POR                                                    0x00004510
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_POR_RMSK                                               0xffffffff
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_ATTR                                                                0x3
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_ADDR)
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_IN)
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_PDC_MATCH_VALUE_LO_REG_OFFSET_BMSK                         0xffff
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRV0_PDC_MATCH_VALUE_LO_REG_OFFSET_SHFT                              0

#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_ADDR(d)                                                (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X24 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_OFFS(d)                                                (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X24 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_RMSK                                                       0xffff
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_MAXd                                                            2
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_POR                                                    0x00004510
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_POR_RMSK                                               0xffffffff
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_ATTR                                                                0x1
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_ADDR(d), HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_RMSK)
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_PDC_MATCH_VALUE_LO_REG_OFFSET_BMSK                         0xffff
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_LO_REG_OFFSET_DRVd_PDC_MATCH_VALUE_LO_REG_OFFSET_SHFT                              0

#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_ADDR                                                   (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x28)
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_OFFS                                                   (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x28)
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_RMSK                                                       0xffff
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_POR                                                    0x00004514
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_POR_RMSK                                               0xffffffff
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_ATTR                                                                0x3
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_ADDR)
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_IN)
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_PDC_MATCH_VALUE_HI_REG_OFFSET_BMSK                         0xffff
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRV0_PDC_MATCH_VALUE_HI_REG_OFFSET_SHFT                              0

#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_ADDR(d)                                                (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X28 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_OFFS(d)                                                (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X28 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_RMSK                                                       0xffff
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_MAXd                                                            2
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_POR                                                    0x00004514
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_POR_RMSK                                               0xffffffff
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_ATTR                                                                0x1
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_ADDR(d), HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_RMSK)
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_PDC_MATCH_VALUE_HI_REG_OFFSET_BMSK                         0xffff
#define HWIO_TITAN_RSCC_PDC_MATCH_VALUE_HI_REG_OFFSET_DRVd_PDC_MATCH_VALUE_HI_REG_OFFSET_SHFT                              0

#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRV0_ADDR                                                                    (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2c)
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRV0_OFFS                                                                    (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2c)
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRV0_RMSK                                                                           0x7
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRV0_POR                                                                     0x00000001
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRV0_POR_RMSK                                                                0xffffffff
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRV0_ATTR                                                                                 0x3
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRV0_ADDR)
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRV0_IN)
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRV0_PDC_SLAVE_ID_BMSK                                                              0x7
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRV0_PDC_SLAVE_ID_SHFT                                                                0

#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRVd_ADDR(d)                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2C + (0x1000*(d)))
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRVd_OFFS(d)                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2C + (0x1000*(d)))
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRVd_RMSK                                                                           0x7
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRVd_MAXd                                                                             2
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRVd_POR                                                                     0x00000001
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRVd_POR_RMSK                                                                0xffffffff
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRVd_ATTR                                                                                 0x1
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRVd_ADDR(d), HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRVd_RMSK)
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRVd_PDC_SLAVE_ID_BMSK                                                              0x7
#define HWIO_TITAN_RSCC_PDC_SLAVE_ID_DRVd_PDC_SLAVE_ID_SHFT                                                                0

#define HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_ADDR(d)                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X30 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_OFFS(d)                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X30 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_RMSK                                                                  0x70707
#define HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_MAXd                                                                        2
#define HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_POR                                                                0x00000000
#define HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_POR_RMSK                                                           0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_ATTR                                                                            0x1
#define HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_ADDR(d), HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_COMPLETED_BMSK                                                        0x70000
#define HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_COMPLETED_SHFT                                                             16
#define HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_ISSUED_BMSK                                                             0x700
#define HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_ISSUED_SHFT                                                                 8
#define HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_TRIGGERED_BMSK                                                            0x7
#define HWIO_TITAN_RSCC_HIDDEN_TCS_STATUS_DRVd_TRIGGERED_SHFT                                                              0

#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_ADDR(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X34 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_OFFS(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X34 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_RMSK                                                            0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_MAXd                                                                     2
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_POR                                                             0x82204514
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_ATTR                                                                         0x1
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_ADDR(d), HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_RMSK)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_ADDR_BMSK                                                       0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_ADDR_DRVd_ADDR_SHFT                                                                0

#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_ADDR(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X38 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_OFFS(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X38 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_RMSK                                                            0x80ffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_MAXd                                                                     2
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_POR                                                             0x00000000
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_ATTR                                                                         0x3
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_ADDR(d), HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_RMSK)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_OUTI(d,val)        \
                out_dword(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_ADDR(d),val)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_ADDR(d),mask,val,HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_INI(d))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_PDC_MATCH_VALUE_VALID_BMSK                                      0x80000000
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_PDC_MATCH_VALUE_VALID_SHFT                                              31
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_PDC_MATCH_VALUE_HI_BMSK                                           0xffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD0_DATA_DRVd_PDC_MATCH_VALUE_HI_SHFT                                                  0

#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_ADDR(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X3C + (0x1000*(d)))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_OFFS(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X3C + (0x1000*(d)))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_RMSK                                                            0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_MAXd                                                                     2
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_POR                                                             0x82204510
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_ATTR                                                                         0x1
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_ADDR(d), HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_RMSK)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_ADDR_BMSK                                                       0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_ADDR_DRVd_ADDR_SHFT                                                                0

#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_ADDR(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X40 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_OFFS(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X40 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_RMSK                                                            0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_MAXd                                                                     2
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_POR                                                             0x00000000
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_ATTR                                                                         0x3
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_ADDR(d), HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_RMSK)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_OUTI(d,val)        \
                out_dword(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_ADDR(d),val)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_ADDR(d),mask,val,HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_INI(d))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_PDC_MATCH_VALUE_LO_BMSK                                         0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD1_DATA_DRVd_PDC_MATCH_VALUE_LO_SHFT                                                  0

#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_ADDR(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X44 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_OFFS(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X44 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_RMSK                                                            0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_MAXd                                                                     2
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_POR                                                             0x82204520
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_ATTR                                                                         0x1
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_ADDR(d), HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_RMSK)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_ADDR_BMSK                                                       0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_ADDR_DRVd_ADDR_SHFT                                                                0

#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_ADDR                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x48)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_OFFS                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x48)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_RMSK                                                            0x8000ffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_POR                                                             0x00000000
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_POR_RMSK                                                        0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_ATTR                                                                         0x3
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_ADDR)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_IN)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_PDC_SEQ_START_ADDR_VALID_BMSK                                   0x80000000
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_PDC_SEQ_START_ADDR_VALID_SHFT                                           31
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_PDC_SEQ_START_ADDR_BMSK                                             0xffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRV0_PDC_SEQ_START_ADDR_SHFT                                                  0

#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_ADDR(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X48 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_OFFS(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X48 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_RMSK                                                            0x8000ffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_MAXd                                                                     2
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_POR                                                             0x00000000
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_ATTR                                                                         0x1
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_ADDR(d), HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_RMSK)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_PDC_SEQ_START_ADDR_VALID_BMSK                                   0x80000000
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_PDC_SEQ_START_ADDR_VALID_SHFT                                           31
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_PDC_SEQ_START_ADDR_BMSK                                             0xffff
#define HWIO_TITAN_RSCC_HIDDEN_TCS_CMD2_DATA_DRVd_PDC_SEQ_START_ADDR_SHFT                                                  0

#define HWIO_TITAN_RSCC_HW_EVENT_OWNER_DRV0_ADDR                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x4c)
#define HWIO_TITAN_RSCC_HW_EVENT_OWNER_DRV0_OFFS                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x4c)
#define HWIO_TITAN_RSCC_HW_EVENT_OWNER_DRV0_RMSK                                                                         0x3
#define HWIO_TITAN_RSCC_HW_EVENT_OWNER_DRV0_POR                                                                   0x00000000
#define HWIO_TITAN_RSCC_HW_EVENT_OWNER_DRV0_POR_RMSK                                                              0xffffffff
#define HWIO_TITAN_RSCC_HW_EVENT_OWNER_DRV0_ATTR                                                                               0x3
#define HWIO_TITAN_RSCC_HW_EVENT_OWNER_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_HW_EVENT_OWNER_DRV0_ADDR)
#define HWIO_TITAN_RSCC_HW_EVENT_OWNER_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_HW_EVENT_OWNER_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_HW_EVENT_OWNER_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_HW_EVENT_OWNER_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_HW_EVENT_OWNER_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_HW_EVENT_OWNER_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_HW_EVENT_OWNER_DRV0_IN)
#define HWIO_TITAN_RSCC_HW_EVENT_OWNER_DRV0_OWNER_BMSK                                                                   0x3
#define HWIO_TITAN_RSCC_HW_EVENT_OWNER_DRV0_OWNER_SHFT                                                                     0

#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ADDR(d,m)                                                       (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X50 + (0x1000*(d)) + (0x4*(m)))
#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_OFFS(d,m)                                                       (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X50 + (0x1000*(d)) + (0x4*(m)))
#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_RMSK                                                            0x80000007
#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_MAXd                                                                     2
#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_MAXm                                                                    31
#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_POR                                                             0x00000000
#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ATTR                                                                         0x3
#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_INI2(d,m)                \
                in_dword_masked(HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ADDR(d,m), HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_RMSK)
#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_INMI2(d,m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ADDR(d,m), mask)
#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_OUTI2(d,m,val)        \
                out_dword(HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ADDR(d,m),val)
#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_OUTMI2(d,m,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ADDR(d,m),mask,val,HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_INI2(d,m))
#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ENABLE_BMSK                                                     0x80000000
#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ENABLE_SHFT                                                             31
#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ENABLE_NOT_ENABLED_FVAL                                                0x0
#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_ENABLE_ENABLED_FVAL                                                    0x1
#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_EVENT_SELECT_BMSK                                                      0x7
#define HWIO_TITAN_RSCC_HW_EVENT_MUXm_SELECT_DRVd_EVENT_SELECT_SHFT                                                        0

#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_ADDR                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0xd0)
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_OFFS                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0xd0)
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_RMSK                                                                   0x1
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_POR                                                             0x00000000
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_POR_RMSK                                                        0xffffffff
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_ATTR                                                                         0x1
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_EPCB_TIMEOUT_IRQ_BMSK                                                  0x1
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRV0_EPCB_TIMEOUT_IRQ_SHFT                                                    0

#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_ADDR(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0XD0 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_OFFS(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0XD0 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_RMSK                                                                   0x1
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_MAXd                                                                     2
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_POR                                                             0x00000000
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_ATTR                                                                         0x1
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_EPCB_TIMEOUT_IRQ_BMSK                                                  0x1
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_STATUS_DRVd_EPCB_TIMEOUT_IRQ_SHFT                                                    0

#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_ADDR                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0xd4)
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_OFFS                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0xd4)
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_RMSK                                                                    0x1
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_POR                                                              0x00000000
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_POR_RMSK                                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_ATTR                                                                          0x0
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_CLR_EPCB_TIMEOUT_IRQ_BMSK                                               0x1
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_CLEAR_DRV0_CLR_EPCB_TIMEOUT_IRQ_SHFT                                                 0

#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_ADDR                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0xd8)
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_OFFS                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0xd8)
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_RMSK                                                              0x10ffff
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_POR                                                             0x00000000
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_POR_RMSK                                                        0xffffffff
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_ATTR                                                                         0x3
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_EPCB_TIMEOUT_IRQ_EN_BMSK                                          0x100000
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_EPCB_TIMEOUT_IRQ_EN_SHFT                                                20
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_EPCB_TIMEOUT_IRQ_EN_NOT_ENABLED_FVAL                                   0x0
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_EPCB_TIMEOUT_IRQ_EN_ENABLED_FVAL                                       0x1
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_EPCB_TIMEOUT_THRESHOLD_BMSK                                         0xffff
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRV0_EPCB_TIMEOUT_THRESHOLD_SHFT                                              0

#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_ADDR(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0XD8 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_OFFS(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0XD8 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_RMSK                                                              0x10ffff
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_MAXd                                                                     2
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_POR                                                             0x00000000
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_ATTR                                                                         0x1
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_EPCB_TIMEOUT_IRQ_EN_BMSK                                          0x100000
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_EPCB_TIMEOUT_IRQ_EN_SHFT                                                20
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_EPCB_TIMEOUT_IRQ_EN_NOT_ENABLED_FVAL                                   0x0
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_EPCB_TIMEOUT_IRQ_EN_ENABLED_FVAL                                       0x1
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_EPCB_TIMEOUT_THRESHOLD_BMSK                                         0xffff
#define HWIO_TITAN_RSCC_RSC_ERROR_IRQ_ENABLE_DRVd_EPCB_TIMEOUT_THRESHOLD_SHFT                                              0

#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ADDR                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x100)
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRV0_OFFS                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x100)
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRV0_RMSK                                                                    0x1
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRV0_POR                                                              0x00000000
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRV0_POR_RMSK                                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ATTR                                                                          0x3
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ERROR_RESP_FOR_INVALID_ADDR_BMSK                                        0x1
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRV0_ERROR_RESP_FOR_INVALID_ADDR_SHFT                                          0

#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRVd_ADDR(d)                                                          (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X100 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRVd_OFFS(d)                                                          (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X100 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRVd_RMSK                                                                    0x1
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRVd_MAXd                                                                      2
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRVd_POR                                                              0x00000000
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRVd_POR_RMSK                                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRVd_ATTR                                                                          0x1
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRVd_ERROR_RESP_FOR_INVALID_ADDR_BMSK                                        0x1
#define HWIO_TITAN_RSCC_RSC_ERROR_RESP_CTRL_DRVd_ERROR_RESP_FOR_INVALID_ADDR_SHFT                                          0

#define HWIO_TITAN_RSCC_RSC_SECURE_OVERRIDE_DRV0_ADDR                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x104)
#define HWIO_TITAN_RSCC_RSC_SECURE_OVERRIDE_DRV0_OFFS                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x104)
#define HWIO_TITAN_RSCC_RSC_SECURE_OVERRIDE_DRV0_RMSK                                                                    0x1
#define HWIO_TITAN_RSCC_RSC_SECURE_OVERRIDE_DRV0_POR                                                              0x00000001
#define HWIO_TITAN_RSCC_RSC_SECURE_OVERRIDE_DRV0_POR_RMSK                                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_SECURE_OVERRIDE_DRV0_ATTR                                                                          0x3
#define HWIO_TITAN_RSCC_RSC_SECURE_OVERRIDE_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SECURE_OVERRIDE_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SECURE_OVERRIDE_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SECURE_OVERRIDE_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SECURE_OVERRIDE_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_SECURE_OVERRIDE_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_SECURE_OVERRIDE_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SECURE_OVERRIDE_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_SECURE_OVERRIDE_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_SECURE_OVERRIDE_DRV0_SECURE_OVERRIDE_BMSK                                                    0x1
#define HWIO_TITAN_RSCC_RSC_SECURE_OVERRIDE_DRV0_SECURE_OVERRIDE_SHFT                                                      0

#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_ADDR                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x108)
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_OFFS                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x108)
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_RMSK                                                            0x1
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_POR                                                      0x00000000
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_POR_RMSK                                                 0xffffffff
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_ATTR                                                                  0x3
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_RIF_CLK_GATING_OVERRIDE_BMSK                                    0x1
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRV0_RIF_CLK_GATING_OVERRIDE_SHFT                                      0

#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_ADDR(d)                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X108 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_OFFS(d)                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X108 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_RMSK                                                            0x1
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_MAXd                                                              2
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_POR                                                      0x00000000
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_POR_RMSK                                                 0xffffffff
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_ATTR                                                                  0x1
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_RIF_CLK_GATING_OVERRIDE_BMSK                                    0x1
#define HWIO_TITAN_RSCC_RSC_RIF_CLK_GATING_OVERRIDE_DRVd_RIF_CLK_GATING_OVERRIDE_SHFT                                      0

#define HWIO_TITAN_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_ADDR                                                      (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x10c)
#define HWIO_TITAN_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_OFFS                                                      (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x10c)
#define HWIO_TITAN_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_RMSK                                                             0x1
#define HWIO_TITAN_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_POR                                                       0x00000000
#define HWIO_TITAN_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_POR_RMSK                                                  0xffffffff
#define HWIO_TITAN_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_ATTR                                                                   0x0
#define HWIO_TITAN_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_SW_RESET_BMSK                                                    0x1
#define HWIO_TITAN_RSCC_RSC_PROFILING_REG_SW_RESET_DRV0_SW_RESET_SHFT                                                      0

#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_ADDR                                                              (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x110)
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_OFFS                                                              (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x110)
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_RMSK                                                                     0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_POR                                                               0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_POR_RMSK                                                          0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_ATTR                                                                           0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_EN_BMSK                                                                  0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_EN_DRV0_EN_SHFT                                                                    0

#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_ADDR                                                          (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x114)
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_OFFS                                                          (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x114)
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_RMSK                                                                 0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_POR                                                           0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_POR_RMSK                                                      0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_ATTR                                                                       0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_IRQ_BMSK                                                             0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_STATUS_DRV0_IRQ_SHFT                                                               0

#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_ADDR                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x118)
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_OFFS                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x118)
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_RMSK                                                                    0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_POR                                                              0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_POR_RMSK                                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_ATTR                                                                          0x0
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_CLR_BMSK                                                                0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_TIMEOUT_CLR_DRV0_CLR_SHFT                                                                  0

#define HWIO_TITAN_RSCC_RSC_PROFILING_THRESHOLD_DRV0_ADDR                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x11c)
#define HWIO_TITAN_RSCC_RSC_PROFILING_THRESHOLD_DRV0_OFFS                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x11c)
#define HWIO_TITAN_RSCC_RSC_PROFILING_THRESHOLD_DRV0_RMSK                                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_PROFILING_THRESHOLD_DRV0_POR                                                          0x00000000
#define HWIO_TITAN_RSCC_RSC_PROFILING_THRESHOLD_DRV0_POR_RMSK                                                     0xffffffff
#define HWIO_TITAN_RSCC_RSC_PROFILING_THRESHOLD_DRV0_ATTR                                                                      0x3
#define HWIO_TITAN_RSCC_RSC_PROFILING_THRESHOLD_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_PROFILING_THRESHOLD_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_PROFILING_THRESHOLD_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_PROFILING_THRESHOLD_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_PROFILING_THRESHOLD_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_PROFILING_THRESHOLD_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_PROFILING_THRESHOLD_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_PROFILING_THRESHOLD_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_PROFILING_THRESHOLD_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_PROFILING_THRESHOLD_DRV0_THRESHOLD_BMSK                                               0xffffffff
#define HWIO_TITAN_RSCC_RSC_PROFILING_THRESHOLD_DRV0_THRESHOLD_SHFT                                                        0

#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_ADDR                                                        (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x120)
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_OFFS                                                        (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x120)
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_RMSK                                                               0x3
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_POR                                                         0x00000000
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_POR_RMSK                                                    0xffffffff
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_ATTR                                                                     0x3
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_OWNER_BMSK                                                         0x3
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNIT_OWNER_DRV0_OWNER_SHFT                                                           0

#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ADDR(d,m)                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X124 + (0x1000*(d)) + (0x20*(m)))
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_OFFS(d,m)                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X124 + (0x1000*(d)) + (0x20*(m)))
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_RMSK                                                                 0x1
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_MAXd                                                                   2
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_MAXm                                                                   5
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_POR                                                           0x00000000
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_POR_RMSK                                                      0xffffffff
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ATTR                                                                       0x3
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_INI2(d,m)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ADDR(d,m), HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_INMI2(d,m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ADDR(d,m), mask)
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_OUTI2(d,m,val)        \
                out_dword(HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ADDR(d,m),val)
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_OUTMI2(d,m,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ADDR(d,m),mask,val,HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_INI2(d,m))
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ENABLE_BMSK                                                          0x1
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ENABLE_SHFT                                                            0
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ENABLE_NOT_ENABLED_FVAL                                              0x0
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_EN_DRVd_ENABLE_ENABLED_FVAL                                                  0x1

#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_ADDR(d,m)                                            (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X128 + (0x1000*(d)) + (0x20*(m)))
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_OFFS(d,m)                                            (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X128 + (0x1000*(d)) + (0x20*(m)))
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_RMSK                                                 0xffffffff
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_MAXd                                                          2
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_MAXm                                                          5
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_POR                                                  0x00000000
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_POR_RMSK                                             0xffffffff
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_ATTR                                                              0x1
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_INI2(d,m)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_ADDR(d,m), HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_INMI2(d,m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_ADDR(d,m), mask)
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_TS_DATA_L_BMSK                                       0xffffffff
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_L_DRVd_TS_DATA_L_SHFT                                                0

#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_ADDR(d,m)                                            (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X12C + (0x1000*(d)) + (0x20*(m)))
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_OFFS(d,m)                                            (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X12C + (0x1000*(d)) + (0x20*(m)))
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_RMSK                                                   0xffffff
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_MAXd                                                          2
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_MAXm                                                          5
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_POR                                                  0x00000000
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_POR_RMSK                                             0xffffffff
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_ATTR                                                              0x1
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_INI2(d,m)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_ADDR(d,m), HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_INMI2(d,m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_ADDR(d,m), mask)
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_TS_DATA_H_BMSK                                         0xffffff
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_TIMESTAMP_H_DRVd_TS_DATA_H_SHFT                                                0

#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_ADDR(d,m)                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X130 + (0x1000*(d)) + (0x20*(m)))
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_OFFS(d,m)                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X130 + (0x1000*(d)) + (0x20*(m)))
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_RMSK                                                           0x101
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_MAXd                                                               2
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_MAXm                                                               5
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_POR                                                       0x00000000
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_POR_RMSK                                                  0xffffffff
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_ATTR                                                                   0x1
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_INI2(d,m)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_ADDR(d,m), HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_INMI2(d,m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_ADDR(d,m), mask)
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_OVERFLOW_BMSK                                               0x100
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_OVERFLOW_SHFT                                                   8
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_OVERFLOW_MULTIPLE_EVENT_CAPTURES_FALSE_FVAL                   0x0
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_OVERFLOW_MULTIPLE_EVENT_CAPTURES_TRUE_FVAL                    0x1
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_VALID_BMSK                                                    0x1
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_VALID_SHFT                                                      0
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_VALID_EVENT_CAPTURED_FALSE_FVAL                               0x0
#define HWIO_TITAN_RSCC_RSC_TIMESTAMP_UNITm_OUTPUT_DRVd_TS_VALID_EVENT_CAPTURED_TRUE_FVAL                                0x1

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x220)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_OFFS                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x220)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_RMSK                                                     0x800003ff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_POR                                                      0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_POR_RMSK                                                 0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ATTR                                                                  0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_VALID_BMSK                                               0x80000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_VALID_SHFT                                                       31
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR_BMSK                                                     0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRV0_ADDR_SHFT                                                         0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_ADDR(d)                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X220 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_OFFS(d)                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X220 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_RMSK                                                     0x800003ff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_MAXd                                                              2
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_POR                                                      0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_POR_RMSK                                                 0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_ATTR                                                                  0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_VALID_BMSK                                               0x80000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_VALID_SHFT                                                       31
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_ADDR_BMSK                                                     0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_DRVd_ADDR_SHFT                                                         0

#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRV0_ADDR                                                                    (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x224)
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRV0_OFFS                                                                    (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x224)
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRV0_RMSK                                                                           0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRV0_POR                                                                     0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRV0_POR_RMSK                                                                0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRV0_ATTR                                                                                 0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRV0_BUSY_STAT_BMSK                                                                 0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRV0_BUSY_STAT_SHFT                                                                   0

#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRVd_ADDR(d)                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X224 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRVd_OFFS(d)                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X224 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRVd_RMSK                                                                           0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRVd_MAXd                                                                             2
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRVd_POR                                                                     0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRVd_POR_RMSK                                                                0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRVd_ATTR                                                                                 0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRVd_BUSY_STAT_BMSK                                                                 0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_DRVd_BUSY_STAT_SHFT                                                                   0

#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_ADDR                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x228)
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_OFFS                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x228)
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_RMSK                                                              0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_POR                                                          0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_POR_RMSK                                                     0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_ATTR                                                                      0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_CURRENT_INSTR_ADDR_BMSK                                           0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRV0_CURRENT_INSTR_ADDR_SHFT                                               0

#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_ADDR(d)                                                      (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X228 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_OFFS(d)                                                      (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X228 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_RMSK                                                              0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_MAXd                                                                  2
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_POR                                                          0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_POR_RMSK                                                     0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_ATTR                                                                      0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_CURRENT_INSTR_ADDR_BMSK                                           0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_DRVd_CURRENT_INSTR_ADDR_SHFT                                               0

#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_ADDR                                               (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x22c)
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_OFFS                                               (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x22c)
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_RMSK                                                    0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_POR                                                0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_POR_RMSK                                           0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_ATTR                                                            0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_CURRENT_INSTR_ADDR_BMSK                                 0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_PROFILING_DRV0_CURRENT_INSTR_ADDR_SHFT                                     0

#define HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_ADDR                                                                    (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x230)
#define HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_OFFS                                                                    (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x230)
#define HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_RMSK                                                                    0x80000001
#define HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_POR                                                                     0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_POR_RMSK                                                                0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_ATTR                                                                                 0x0
#define HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_CLEAR_BMSK                                                              0x80000000
#define HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_CLEAR_SHFT                                                                      31
#define HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_COMP_STAT_BMSK                                                                 0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_COMP_DRV0_COMP_STAT_SHFT                                                                   0

#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_ADDR(i)                                                      (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X270 + (0x4*(i)))
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_OFFS(i)                                                      (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X270 + (0x4*(i)))
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_RMSK                                                            0xfffff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_MAXi                                                                  3
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_POR                                                          0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_POR_RMSK                                                     0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_ATTR                                                                      0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_INI(i)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_ADDR(i), HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_INMI(i,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_ADDR(i), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_OUTI(i,val)        \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_ADDR(i),val)
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_OUTMI(i,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_ADDR(i),mask,val,HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_INI(i))
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_DELAY_VAL_BMSK                                                  0xfffff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRV0_DELAY_VAL_SHFT                                                        0

#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_ADDR(d,i)                                                    (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X270 + (0x1000*(d)) + (0x4*(i)))
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_OFFS(d,i)                                                    (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X270 + (0x1000*(d)) + (0x4*(i)))
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_RMSK                                                            0xfffff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_MAXd                                                                  2
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_MAXi                                                                  3
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_POR                                                          0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_POR_RMSK                                                     0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_ATTR                                                                      0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_INI2(d,i)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_ADDR(d,i), HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_INMI2(d,i,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_ADDR(d,i), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_DELAY_VAL_BMSK                                                  0xfffff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_i_DRVd_DELAY_VAL_SHFT                                                        0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_ADDR                                                        (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x280)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_OFFS                                                        (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x280)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_RMSK                                                               0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_POR                                                         0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_POR_RMSK                                                    0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_ATTR                                                                     0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_SEQ_OVERRIDE_TRIGGER_BMSK                                          0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRV0_SEQ_OVERRIDE_TRIGGER_SHFT                                            0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_ADDR(d)                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X280 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_OFFS(d)                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X280 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_RMSK                                                               0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_MAXd                                                                 2
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_POR                                                         0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_POR_RMSK                                                    0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_ATTR                                                                     0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_SEQ_OVERRIDE_TRIGGER_BMSK                                          0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_DRVd_SEQ_OVERRIDE_TRIGGER_SHFT                                            0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_ADDR                                          (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x284)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_OFFS                                          (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x284)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_RMSK                                               0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_POR                                           0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_POR_RMSK                                      0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_ATTR                                                       0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_SEQ_OVERRIDE_TRIGGER_START_ADDR_BMSK               0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRV0_SEQ_OVERRIDE_TRIGGER_START_ADDR_SHFT                   0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_ADDR(d)                                       (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X284 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_OFFS(d)                                       (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X284 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_RMSK                                               0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_MAXd                                                   2
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_POR                                           0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_POR_RMSK                                      0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_ATTR                                                       0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_SEQ_OVERRIDE_TRIGGER_START_ADDR_BMSK               0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_TRIGGER_START_ADDRESS_DRVd_SEQ_OVERRIDE_TRIGGER_START_ADDR_SHFT                   0

#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_ADDR                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2b0)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_OFFS                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2b0)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_RMSK                                                     0x800003ff
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_POR                                                      0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_POR_RMSK                                                 0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_ATTR                                                                  0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_DBG_BREAKPOINT_VALID_BMSK                                0x80000000
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_DBG_BREAKPOINT_VALID_SHFT                                        31
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_DBG_BREAKPOINT_ADDR_BMSK                                      0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_DRV0_DBG_BREAKPOINT_ADDR_SHFT                                          0

#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_DRV0_ADDR                                                                (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2b4)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_DRV0_OFFS                                                                (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2b4)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_DRV0_RMSK                                                                       0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_DRV0_POR                                                                 0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_DRV0_POR_RMSK                                                            0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_DRV0_ATTR                                                                             0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_DRV0_DBG_STEP_TRIGGER_BMSK                                                      0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_DRV0_DBG_STEP_TRIGGER_SHFT                                                        0

#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_ADDR                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2b8)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_OFFS                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2b8)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_RMSK                                                                   0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_POR                                                             0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_POR_RMSK                                                        0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_ATTR                                                                         0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_DBG_STEP_CONTINUE_BMSK                                                 0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_DRV0_DBG_STEP_CONTINUE_SHFT                                                   0

#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_DRV0_ADDR                                                                (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2bc)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_DRV0_OFFS                                                                (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2bc)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_DRV0_RMSK                                                                       0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_DRV0_POR                                                                 0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_DRV0_POR_RMSK                                                            0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_DRV0_ATTR                                                                             0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_DRV0_DBG_STEPPING_STATUS_BMSK                                                   0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_DRV0_DBG_STEPPING_STATUS_SHFT                                                     0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_ADDR                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2c0)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_OFFS                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2c0)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_RMSK                                                       0x3f
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_POR                                                  0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_POR_RMSK                                             0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_ATTR                                                              0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_SEQ_OVERRIDE_PWR_CNTRL_MASK_BMSK                           0x3f
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRV0_SEQ_OVERRIDE_PWR_CNTRL_MASK_SHFT                              0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_ADDR(d)                                              (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2C0 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_OFFS(d)                                              (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2C0 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_RMSK                                                       0x3f
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_MAXd                                                          2
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_POR                                                  0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_POR_RMSK                                             0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_ATTR                                                              0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_SEQ_OVERRIDE_PWR_CNTRL_MASK_BMSK                           0x3f
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_DRVd_SEQ_OVERRIDE_PWR_CNTRL_MASK_SHFT                              0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_ADDR                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2c4)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_OFFS                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2c4)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_RMSK                                                        0x3f
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_POR                                                   0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_POR_RMSK                                              0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_ATTR                                                               0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_SEQ_OVERRIDE_PWR_CNTRL_VAL_BMSK                             0x3f
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRV0_SEQ_OVERRIDE_PWR_CNTRL_VAL_SHFT                                0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_ADDR(d)                                               (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2C4 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_OFFS(d)                                               (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2C4 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_RMSK                                                        0x3f
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_MAXd                                                           2
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_POR                                                   0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_POR_RMSK                                              0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_ATTR                                                               0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_SEQ_OVERRIDE_PWR_CNTRL_VAL_BMSK                             0x3f
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_DRVd_SEQ_OVERRIDE_PWR_CNTRL_VAL_SHFT                                0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_ADDR                                                (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2c8)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_OFFS                                                (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2c8)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_RMSK                                                      0x3f
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_POR                                                 0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_POR_RMSK                                            0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_ATTR                                                             0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_SEQ_OVERRIDE_WAIT_EVENT_MASK_BMSK                         0x3f
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRV0_SEQ_OVERRIDE_WAIT_EVENT_MASK_SHFT                            0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_ADDR(d)                                             (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2C8 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_OFFS(d)                                             (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2C8 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_RMSK                                                      0x3f
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_MAXd                                                         2
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_POR                                                 0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_POR_RMSK                                            0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_ATTR                                                             0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_SEQ_OVERRIDE_WAIT_EVENT_MASK_BMSK                         0x3f
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_DRVd_SEQ_OVERRIDE_WAIT_EVENT_MASK_SHFT                            0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_ADDR                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2cc)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_OFFS                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2cc)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_RMSK                                                       0x3f
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_POR                                                  0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_POR_RMSK                                             0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_ATTR                                                              0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_IN)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_SEQ_OVERRIDE_WAIT_EVENT_VAL_BMSK                           0x3f
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRV0_SEQ_OVERRIDE_WAIT_EVENT_VAL_SHFT                              0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_ADDR(d)                                              (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2CC + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_OFFS(d)                                              (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2CC + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_RMSK                                                       0x3f
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_MAXd                                                          2
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_POR                                                  0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_POR_RMSK                                             0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_ATTR                                                              0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_SEQ_OVERRIDE_WAIT_EVENT_VAL_BMSK                           0x3f
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_DRVd_SEQ_OVERRIDE_WAIT_EVENT_VAL_SHFT                              0

#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_ADDR                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2d0)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_OFFS                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2d0)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_RMSK                                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_POR                                                          0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_POR_RMSK                                                     0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_ATTR                                                                      0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_PWR_CTRL_STATUS_BMSK                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRV0_PWR_CTRL_STATUS_SHFT                                                  0

#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_ADDR(d)                                                      (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2D0 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_OFFS(d)                                                      (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2D0 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_RMSK                                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_MAXd                                                                  2
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_POR                                                          0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_POR_RMSK                                                     0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_ATTR                                                                      0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_PWR_CTRL_STATUS_BMSK                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_DRVd_PWR_CTRL_STATUS_SHFT                                                  0

#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_ADDR                                                        (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2d4)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_OFFS                                                        (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2d4)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_RMSK                                                        0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_POR                                                         0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_POR_RMSK                                                    0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_ATTR                                                                     0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_PWR_EVENT_STATUS_BMSK                                       0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRV0_PWR_EVENT_STATUS_SHFT                                                0

#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_ADDR(d)                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2D4 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_OFFS(d)                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2D4 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_RMSK                                                        0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_MAXd                                                                 2
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_POR                                                         0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_POR_RMSK                                                    0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_ATTR                                                                     0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_PWR_EVENT_STATUS_BMSK                                       0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_DRVd_PWR_EVENT_STATUS_SHFT                                                0

#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_ADDR                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2d8)
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_OFFS                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2d8)
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_RMSK                                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_POR                                                          0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_POR_RMSK                                                     0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_ATTR                                                                      0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_ADDR)
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_BR_EVENT_STATUS_BMSK                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRV0_BR_EVENT_STATUS_SHFT                                                  0

#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_ADDR(d)                                                      (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2D8 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_OFFS(d)                                                      (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2D8 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_RMSK                                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_MAXd                                                                  2
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_POR                                                          0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_POR_RMSK                                                     0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_ATTR                                                                      0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_BR_EVENT_STATUS_BMSK                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_DRVd_BR_EVENT_STATUS_SHFT                                                  0

#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR(i)                                                        (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2DC + (0x4*(i)))
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_OFFS(i)                                                        (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2DC + (0x4*(i)))
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_RMSK                                                                0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_MAXi                                                                    3
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_POR                                                            0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_POR_RMSK                                                       0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ATTR                                                                        0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_INI(i)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR(i), HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_INMI(i,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR(i), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_OUTI(i,val)        \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR(i),val)
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_OUTMI(i,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR(i),mask,val,HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_INI(i))
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR_BMSK                                                           0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRV0_ADDR_SHFT                                                               0

#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_ADDR(d,i)                                                      (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2DC + (0x1000*(d)) + (0x4*(i)))
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_OFFS(d,i)                                                      (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2DC + (0x1000*(d)) + (0x4*(i)))
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_RMSK                                                                0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_MAXd                                                                    2
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_MAXi                                                                    3
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_POR                                                            0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_POR_RMSK                                                       0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_ATTR                                                                        0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_INI2(d,i)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_ADDR(d,i), HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_INMI2(d,i,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_ADDR(d,i), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_ADDR_BMSK                                                           0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_DRVd_ADDR_SHFT                                                               0

#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_ADDR(m)                                                                    (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X370 + (0x4*(m)))
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_OFFS(m)                                                                    (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X370 + (0x4*(m)))
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_RMSK                                                                       0xffffffff
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_MAXm                                                                               15
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_POR                                                                        0x00000000
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_POR_RMSK                                                                   0xffffffff
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_ATTR                                                                                    0x3
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_INI(m)                \
                in_dword_masked(HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_ADDR(m), HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_RMSK)
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_INMI(m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_ADDR(m), mask)
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_OUTI(m,val)        \
                out_dword(HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_ADDR(m),val)
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_ADDR(m),mask,val,HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_INI(m))
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_CMD_WORD_BMSK                                                              0xffffffff
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRV0_CMD_WORD_SHFT                                                                       0

#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRVd_ADDR(d,m)                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X370 + (0x1000*(d)) + (0x4*(m)))
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRVd_OFFS(d,m)                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X370 + (0x1000*(d)) + (0x4*(m)))
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRVd_RMSK                                                                       0xffffffff
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRVd_MAXd                                                                                2
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRVd_MAXm                                                                               15
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRVd_POR                                                                        0x00000000
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRVd_POR_RMSK                                                                   0xffffffff
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRVd_ATTR                                                                                    0x1
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRVd_INI2(d,m)                \
                in_dword_masked(HWIO_TITAN_RSCC_SEQ_MEM_m_DRVd_ADDR(d,m), HWIO_TITAN_RSCC_SEQ_MEM_m_DRVd_RMSK)
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRVd_INMI2(d,m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_SEQ_MEM_m_DRVd_ADDR(d,m), mask)
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRVd_CMD_WORD_BMSK                                                              0xffffffff
#define HWIO_TITAN_RSCC_SEQ_MEM_m_DRVd_CMD_WORD_SHFT                                                                       0

#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_ADDR(i)                                                (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X420 + (0x4*(i)))
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_OFFS(i)                                                (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X420 + (0x4*(i)))
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_RMSK                                                        0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_MAXi                                                           15
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_POR                                                    0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_POR_RMSK                                               0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_ATTR                                                                0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_INI(i)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_ADDR(i), HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_INMI(i,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_ADDR(i), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_OUTI(i,val)        \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_ADDR(i),val)
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_OUTMI(i,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_ADDR(i),mask,val,HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_INI(i))
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_ADDR_BMSK                                                   0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_BR_ADDR_i_CHN_TCS_DRV0_ADDR_SHFT                                                       0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_ADDR(d)                                          (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X460 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_OFFS(d)                                          (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X460 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_RMSK                                             0x800003ff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_MAXd                                                      2
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_POR                                              0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_POR_RMSK                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_ATTR                                                          0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_OUTI(d,val)        \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_ADDR(d),val)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_ADDR(d),mask,val,HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_INI(d))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_VALID_BMSK                                       0x80000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_VALID_SHFT                                               31
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_ADDR_BMSK                                             0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_START_ADDR_CHN_TCS_DRVd_ADDR_SHFT                                                 0

#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_CHN_TCS_DRVd_ADDR(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X464 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_CHN_TCS_DRVd_OFFS(d)                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X464 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_CHN_TCS_DRVd_RMSK                                                                   0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_CHN_TCS_DRVd_MAXd                                                                     2
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_CHN_TCS_DRVd_POR                                                             0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_CHN_TCS_DRVd_POR_RMSK                                                        0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_CHN_TCS_DRVd_ATTR                                                                         0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_CHN_TCS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_BUSY_CHN_TCS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_BUSY_CHN_TCS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_CHN_TCS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_BUSY_CHN_TCS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_CHN_TCS_DRVd_BUSY_STAT_BMSK                                                         0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_BUSY_CHN_TCS_DRVd_BUSY_STAT_SHFT                                                           0

#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_CHN_TCS_DRVd_ADDR(d)                                              (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X468 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_CHN_TCS_DRVd_OFFS(d)                                              (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X468 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_CHN_TCS_DRVd_RMSK                                                      0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_CHN_TCS_DRVd_MAXd                                                          2
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_CHN_TCS_DRVd_POR                                                  0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_CHN_TCS_DRVd_POR_RMSK                                             0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_CHN_TCS_DRVd_ATTR                                                              0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_CHN_TCS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_CHN_TCS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_CHN_TCS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_CHN_TCS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_CHN_TCS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_CHN_TCS_DRVd_CURRENT_INSTR_ADDR_BMSK                                   0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_PROGRAM_COUNTER_CHN_TCS_DRVd_CURRENT_INSTR_ADDR_SHFT                                       0

#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_ADDR(d)                                          (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X46C + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_OFFS(d)                                          (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X46C + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_RMSK                                             0x800003ff
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_MAXd                                                      2
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_POR                                              0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_POR_RMSK                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_ATTR                                                          0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_OUTI(d,val)        \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_ADDR(d),val)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_ADDR(d),mask,val,HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_INI(d))
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_DBG_BREAKPOINT_VALID_BMSK                        0x80000000
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_DBG_BREAKPOINT_VALID_SHFT                                31
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_DBG_BREAKPOINT_ADDR_BMSK                              0x3ff
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_BREAKPOINT_ADDR_CHN_TCS_DRVd_DBG_BREAKPOINT_ADDR_SHFT                                  0

#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_ADDR(d)                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X470 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_OFFS(d)                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X470 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_RMSK                                                               0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_MAXd                                                                 2
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_POR                                                         0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_POR_RMSK                                                    0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_ATTR                                                                     0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_OUTI(d,val)        \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_ADDR(d),val)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_ADDR(d),mask,val,HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_INI(d))
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_DBG_STEP_TRIGGER_BMSK                                              0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STEP_CHN_TCS_DRVd_DBG_STEP_TRIGGER_SHFT                                                0

#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_ADDR(d)                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X474 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_OFFS(d)                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X474 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_RMSK                                                           0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_MAXd                                                             2
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_POR                                                     0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_POR_RMSK                                                0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_ATTR                                                                 0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_OUTI(d,val)        \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_ADDR(d),val)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_ADDR(d),mask,val,HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_INI(d))
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_DBG_STEP_CONTINUE_BMSK                                         0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_CONTINUE_CHN_TCS_DRVd_DBG_STEP_CONTINUE_SHFT                                           0

#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_CHN_TCS_DRVd_ADDR(d)                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X478 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_CHN_TCS_DRVd_OFFS(d)                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X478 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_CHN_TCS_DRVd_RMSK                                                               0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_CHN_TCS_DRVd_MAXd                                                                 2
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_CHN_TCS_DRVd_POR                                                         0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_CHN_TCS_DRVd_POR_RMSK                                                    0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_CHN_TCS_DRVd_ATTR                                                                     0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_CHN_TCS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_CHN_TCS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_CHN_TCS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_CHN_TCS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_CHN_TCS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_CHN_TCS_DRVd_DBG_STEPPING_STATUS_BMSK                                           0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_DBG_STAT_CHN_TCS_DRVd_DBG_STEPPING_STATUS_SHFT                                             0

#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_ADDR(d,i)                                            (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X47C + (0x1000*(d)) + (0x4*(i)))
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_OFFS(d,i)                                            (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X47C + (0x1000*(d)) + (0x4*(i)))
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_RMSK                                                    0xfffff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_MAXd                                                          2
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_MAXi                                                          3
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_POR                                                  0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_POR_RMSK                                             0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_ATTR                                                              0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_INI2(d,i)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_ADDR(d,i), HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_INMI2(d,i,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_ADDR(d,i), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_OUTI2(d,i,val)        \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_ADDR(d,i),val)
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_OUTMI2(d,i,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_ADDR(d,i),mask,val,HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_INI2(d,i))
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_DELAY_VAL_BMSK                                          0xfffff
#define HWIO_TITAN_RSCC_RSC_SEQ_CFG_DELAY_VAL_CHN_TCS_i_DRVd_DELAY_VAL_SHFT                                                0

#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_ADDR(d)                                              (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X490 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_OFFS(d)                                              (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X490 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_RMSK                                                 0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_MAXd                                                          2
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_POR                                                  0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_POR_RMSK                                             0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_ATTR                                                              0x0
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_OUTI(d,val)        \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_ADDR(d),val)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_ADDR(d),mask,val,HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_INI(d))
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_CLEAR_BMSK                                           0x80000000
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_CLEAR_SHFT                                                   31
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_PWR_CTRL_STATUS_BMSK                                 0x7fffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_CTRL_STATUS_CHN_TCS_DRVd_PWR_CTRL_STATUS_SHFT                                          0

#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_ADDR(d)                                             (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X494 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_OFFS(d)                                             (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X494 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_RMSK                                                0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_MAXd                                                         2
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_POR                                                 0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_POR_RMSK                                            0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_ATTR                                                             0x0
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_OUTI(d,val)        \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_ADDR(d),val)
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_ADDR(d),mask,val,HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_INI(d))
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_CLEAR_BMSK                                          0x80000000
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_CLEAR_SHFT                                                  31
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_PWR_EVENT_STATUS_BMSK                               0x7fffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_PWR_EVENT_STATUS_CHN_TCS_DRVd_PWR_EVENT_STATUS_SHFT                                        0

#define HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_ADDR(d)                                                                   (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X498 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_OFFS(d)                                                                   (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X498 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_RMSK                                                                             0x3
#define HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_MAXd                                                                               2
#define HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_POR                                                                       0x00000000
#define HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_POR_RMSK                                                                  0xffffffff
#define HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_ATTR                                                                                   0x3
#define HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_ADDR(d), HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_RMSK)
#define HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_OUTI(d,val)        \
                out_dword(HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_ADDR(d),val)
#define HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_ADDR(d),mask,val,HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_INI(d))
#define HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_CHANNEL_BMSK                                                                     0x3
#define HWIO_TITAN_RSCC_CHN_UPDATE_DRVd_CHANNEL_SHFT                                                                       0

#define HWIO_TITAN_RSCC_CHN_BUSY_DRVd_ADDR(d)                                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X49C + (0x1000*(d)))
#define HWIO_TITAN_RSCC_CHN_BUSY_DRVd_OFFS(d)                                                                     (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X49C + (0x1000*(d)))
#define HWIO_TITAN_RSCC_CHN_BUSY_DRVd_RMSK                                                                               0x3
#define HWIO_TITAN_RSCC_CHN_BUSY_DRVd_MAXd                                                                                 2
#define HWIO_TITAN_RSCC_CHN_BUSY_DRVd_POR                                                                         0x00000000
#define HWIO_TITAN_RSCC_CHN_BUSY_DRVd_POR_RMSK                                                                    0xffffffff
#define HWIO_TITAN_RSCC_CHN_BUSY_DRVd_ATTR                                                                                     0x1
#define HWIO_TITAN_RSCC_CHN_BUSY_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_CHN_BUSY_DRVd_ADDR(d), HWIO_TITAN_RSCC_CHN_BUSY_DRVd_RMSK)
#define HWIO_TITAN_RSCC_CHN_BUSY_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_CHN_BUSY_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_CHN_BUSY_DRVd_CHANNEL_BMSK                                                                       0x3
#define HWIO_TITAN_RSCC_CHN_BUSY_DRVd_CHANNEL_SHFT                                                                         0

#define HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_ADDR(d)                                                                   (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X4A0 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_OFFS(d)                                                                   (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X4A0 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_RMSK                                                                             0x1
#define HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_MAXd                                                                               2
#define HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_POR                                                                       0x00000000
#define HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_POR_RMSK                                                                  0xffffffff
#define HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_ATTR                                                                                   0x3
#define HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_ADDR(d), HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_RMSK)
#define HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_OUTI(d,val)        \
                out_dword(HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_ADDR(d),val)
#define HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_ADDR(d),mask,val,HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_INI(d))
#define HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_ENABLE_BMSK                                                                      0x1
#define HWIO_TITAN_RSCC_CHN_DRV_EN_DRVd_ENABLE_SHFT                                                                        0

#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_CHN_TCS_DRVd_ADDR(d)                                              (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X4A4 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_CHN_TCS_DRVd_OFFS(d)                                              (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X4A4 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_CHN_TCS_DRVd_RMSK                                                 0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_CHN_TCS_DRVd_MAXd                                                          2
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_CHN_TCS_DRVd_POR                                                  0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_CHN_TCS_DRVd_POR_RMSK                                             0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_CHN_TCS_DRVd_ATTR                                                              0x1
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_CHN_TCS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_CHN_TCS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_CHN_TCS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_CHN_TCS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_CHN_TCS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_CHN_TCS_DRVd_BR_EVENT_STATUS_BMSK                                 0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_BR_EVENT_STATUS_CHN_TCS_DRVd_BR_EVENT_STATUS_SHFT                                          0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_ADDR(d)                                      (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X4A8 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_OFFS(d)                                      (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X4A8 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_RMSK                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_MAXd                                                  2
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_POR                                          0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_POR_RMSK                                     0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_ATTR                                                      0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_OUTI(d,val)        \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_ADDR(d),val)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_ADDR(d),mask,val,HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_INI(d))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_SEQ_OVERRIDE_PWR_CNTRL_MASK_BMSK             0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_MASK_CHN_TCS_DRVd_SEQ_OVERRIDE_PWR_CNTRL_MASK_SHFT                      0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_ADDR(d)                                       (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X4AC + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_OFFS(d)                                       (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X4AC + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_RMSK                                          0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_MAXd                                                   2
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_POR                                           0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_POR_RMSK                                      0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_ATTR                                                       0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_OUTI(d,val)        \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_ADDR(d),val)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_ADDR(d),mask,val,HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_INI(d))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_SEQ_OVERRIDE_PWR_CNTRL_VAL_BMSK               0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_PWR_CNTRL_VAL_CHN_TCS_DRVd_SEQ_OVERRIDE_PWR_CNTRL_VAL_SHFT                        0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_ADDR(d)                                     (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X4B0 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_OFFS(d)                                     (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X4B0 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_RMSK                                        0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_MAXd                                                 2
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_POR                                         0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_POR_RMSK                                    0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_ATTR                                                     0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_OUTI(d,val)        \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_ADDR(d),val)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_ADDR(d),mask,val,HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_INI(d))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_SEQ_OVERRIDE_WAIT_EVENT_MASK_BMSK           0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_MASK_CHN_TCS_DRVd_SEQ_OVERRIDE_WAIT_EVENT_MASK_SHFT                    0

#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_ADDR(d)                                      (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X4B4 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_OFFS(d)                                      (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X4B4 + (0x1000*(d)))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_RMSK                                         0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_MAXd                                                  2
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_POR                                          0x00000000
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_POR_RMSK                                     0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_ATTR                                                      0x3
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_INI(d)                \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_ADDR(d), HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_RMSK)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_INMI(d,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_ADDR(d), mask)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_OUTI(d,val)        \
                out_dword(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_ADDR(d),val)
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_OUTMI(d,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_ADDR(d),mask,val,HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_INI(d))
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_SEQ_OVERRIDE_WAIT_EVENT_VAL_BMSK             0xffffffff
#define HWIO_TITAN_RSCC_RSC_SEQ_OVERRIDE_WAIT_EVENT_VAL_CHN_TCS_DRVd_SEQ_OVERRIDE_WAIT_EVENT_VAL_SHFT                      0

#define HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_ADDR(m)                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X4B8 + (0x4*(m)))
#define HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_OFFS(m)                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X4B8 + (0x4*(m)))
#define HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_RMSK                                                               0xffffffff
#define HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_MAXm                                                                       23
#define HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_POR                                                                0x00000000
#define HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_POR_RMSK                                                           0xffffffff
#define HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_ATTR                                                                            0x3
#define HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_INI(m)                \
                in_dword_masked(HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_ADDR(m), HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_RMSK)
#define HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_INMI(m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_ADDR(m), mask)
#define HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_OUTI(m,val)        \
                out_dword(HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_ADDR(m),val)
#define HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_ADDR(m),mask,val,HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_INI(m))
#define HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_CMD_WORD_BMSK                                                      0xffffffff
#define HWIO_TITAN_RSCC_SEQ_MEM_CHN_TCS_m_DRV0_CMD_WORD_SHFT                                                               0

#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_ADDR                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x520)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_OFFS                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x520)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_RMSK                                                                0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_POR                                                          0x00000000
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_POR_RMSK                                                     0xffffffff
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_ATTR                                                                      0x3
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_ADDR)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_IN)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_AMC_COMPLETION_IRQ_ENABLE_BMSK                                      0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV0_AMC_COMPLETION_IRQ_ENABLE_SHFT                                        0

#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_ADDR                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x524)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_OFFS                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x524)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_RMSK                                                                0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_POR                                                          0x00000000
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_POR_RMSK                                                     0xffffffff
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_ATTR                                                                      0x1
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_ADDR)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_AMC_COMPLETION_IRQ_STATUS_BMSK                                      0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV0_AMC_COMPLETION_IRQ_STATUS_SHFT                                        0

#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_ADDR                                                          (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x528)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_OFFS                                                          (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x528)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_RMSK                                                                 0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_POR                                                           0x00000000
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_POR_RMSK                                                      0xffffffff
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_ATTR                                                                       0x0
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_AMC_COMPLETION_IRQ_CLEAR_BMSK                                        0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV0_AMC_COMPLETION_IRQ_CLEAR_SHFT                                          0

#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV0_ADDR                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x530)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV0_OFFS                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x530)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV0_RMSK                                                                         0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV0_POR                                                                   0x00000000
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV0_POR_RMSK                                                              0xffffffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV0_ATTR                                                                               0x3
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV0_ADDR)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV0_IN)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV0_EN_BMSK                                                                      0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV0_EN_SHFT                                                                        0

#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV0_ADDR                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x534)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV0_OFFS                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x534)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV0_RMSK                                                                        0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV0_POR                                                                  0x00000000
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV0_POR_RMSK                                                             0xffffffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV0_ATTR                                                                              0x0
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV0_CLR_BMSK                                                                    0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV0_CLR_SHFT                                                                      0

#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV0_ADDR                                                              (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x538)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV0_OFFS                                                              (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x538)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV0_RMSK                                                                     0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV0_POR                                                               0x00000000
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV0_POR_RMSK                                                          0xffffffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV0_ATTR                                                                           0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV0_ADDR)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV0_TIMEOUT_BMSK                                                             0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV0_TIMEOUT_SHFT                                                               0

#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV0_ADDR                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x53c)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV0_OFFS                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x53c)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV0_RMSK                                                                     0xffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV0_POR                                                                  0x0000ffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV0_POR_RMSK                                                             0xffffffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV0_ATTR                                                                              0x3
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV0_IN                    \
                in_dword(HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV0_ADDR)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV0_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV0_ADDR, m)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV0_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV0_ADDR,v)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV0_ADDR,m,v,HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV0_IN)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV0_TIMEOUT_VAL_BMSK                                                         0xffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV0_TIMEOUT_VAL_SHFT                                                              0

#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_ADDR(m)                                                       (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X540 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_OFFS(m)                                                       (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X540 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_RMSK                                                               0xfff
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_MAXm                                                                   3
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_POR                                                           0x00000000
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_POR_RMSK                                                      0xffffffff
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_ATTR                                                                       0x3
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_INI(m)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_ADDR(m), HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_RMSK)
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_INMI(m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_ADDR(m), mask)
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_OUTI(m,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_ADDR(m),val)
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_ADDR(m),mask,val,HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_INI(m))
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_CMD_WAIT_FOR_CMPL_BMSK                                             0xfff
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_WAIT_FOR_CMPL_CMD_WAIT_FOR_CMPL_SHFT                                                 0

#define HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_ADDR(m)                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X544 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_OFFS(m)                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X544 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_RMSK                                                                     0x1010000
#define HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_MAXm                                                                             3
#define HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_POR                                                                     0x00000000
#define HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_POR_RMSK                                                                0xffffffff
#define HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_ATTR                                                                                 0x3
#define HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_INI(m)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_ADDR(m), HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_RMSK)
#define HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_INMI(m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_ADDR(m), mask)
#define HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_OUTI(m,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_ADDR(m),val)
#define HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_ADDR(m),mask,val,HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_INI(m))
#define HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_AMC_MODE_TRIGGER_BMSK                                                    0x1000000
#define HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_AMC_MODE_TRIGGER_SHFT                                                           24
#define HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_AMC_MODE_EN_BMSK                                                           0x10000
#define HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_AMC_MODE_EN_SHFT                                                                16
#define HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_AMC_MODE_EN_AMC_MODE_DISABLE_FVAL                                              0x0
#define HWIO_TITAN_RSCC_TCSm_DRV0_CONTROL_AMC_MODE_EN_AMC_MODE_ENABLED_FVAL                                              0x1

#define HWIO_TITAN_RSCC_TCSm_DRV0_STATUS_ADDR(m)                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X548 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV0_STATUS_OFFS(m)                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X548 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV0_STATUS_RMSK                                                                            0x1
#define HWIO_TITAN_RSCC_TCSm_DRV0_STATUS_MAXm                                                                              3
#define HWIO_TITAN_RSCC_TCSm_DRV0_STATUS_POR                                                                      0x00000001
#define HWIO_TITAN_RSCC_TCSm_DRV0_STATUS_POR_RMSK                                                                 0xffffffff
#define HWIO_TITAN_RSCC_TCSm_DRV0_STATUS_ATTR                                                                                  0x1
#define HWIO_TITAN_RSCC_TCSm_DRV0_STATUS_INI(m)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV0_STATUS_ADDR(m), HWIO_TITAN_RSCC_TCSm_DRV0_STATUS_RMSK)
#define HWIO_TITAN_RSCC_TCSm_DRV0_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV0_STATUS_ADDR(m), mask)
#define HWIO_TITAN_RSCC_TCSm_DRV0_STATUS_CONTROLLER_IDLE_BMSK                                                            0x1
#define HWIO_TITAN_RSCC_TCSm_DRV0_STATUS_CONTROLLER_IDLE_SHFT                                                              0
#define HWIO_TITAN_RSCC_TCSm_DRV0_STATUS_CONTROLLER_IDLE_NOT_IDLE_FVAL                                                   0x0
#define HWIO_TITAN_RSCC_TCSm_DRV0_STATUS_CONTROLLER_IDLE_IS_IDLE_FVAL                                                    0x1

#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_ADDR(m)                                                              (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X54C + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_OFFS(m)                                                              (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X54C + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_RMSK                                                                      0xfff
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_MAXm                                                                          3
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_POR                                                                  0x00000000
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_POR_RMSK                                                             0xffffffff
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_ATTR                                                                              0x3
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_INI(m)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_ADDR(m), HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_RMSK)
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_INMI(m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_ADDR(m), mask)
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_OUTI(m,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_ADDR(m),val)
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_ADDR(m),mask,val,HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_INI(m))
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_INDIVIDUAL_CMD_ENABLE_MASK_BMSK                                           0xfff
#define HWIO_TITAN_RSCC_TCSm_DRV0_CMD_ENABLE_INDIVIDUAL_CMD_ENABLE_MASK_SHFT                                               0

#define HWIO_TITAN_RSCC_TCSm_DRV0_PROFILING_STATUS_ADDR(m)                                                        (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X550 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV0_PROFILING_STATUS_OFFS(m)                                                        (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X550 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV0_PROFILING_STATUS_RMSK                                                                  0x1
#define HWIO_TITAN_RSCC_TCSm_DRV0_PROFILING_STATUS_MAXm                                                                    3
#define HWIO_TITAN_RSCC_TCSm_DRV0_PROFILING_STATUS_POR                                                            0x00000001
#define HWIO_TITAN_RSCC_TCSm_DRV0_PROFILING_STATUS_POR_RMSK                                                       0xffffffff
#define HWIO_TITAN_RSCC_TCSm_DRV0_PROFILING_STATUS_ATTR                                                                        0x1
#define HWIO_TITAN_RSCC_TCSm_DRV0_PROFILING_STATUS_INI(m)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV0_PROFILING_STATUS_ADDR(m), HWIO_TITAN_RSCC_TCSm_DRV0_PROFILING_STATUS_RMSK)
#define HWIO_TITAN_RSCC_TCSm_DRV0_PROFILING_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV0_PROFILING_STATUS_ADDR(m), mask)
#define HWIO_TITAN_RSCC_TCSm_DRV0_PROFILING_STATUS_CONTROLLER_IDLE_BMSK                                                  0x1
#define HWIO_TITAN_RSCC_TCSm_DRV0_PROFILING_STATUS_CONTROLLER_IDLE_SHFT                                                    0
#define HWIO_TITAN_RSCC_TCSm_DRV0_PROFILING_STATUS_CONTROLLER_IDLE_NOT_IDLE_FVAL                                         0x0
#define HWIO_TITAN_RSCC_TCSm_DRV0_PROFILING_STATUS_CONTROLLER_IDLE_IS_IDLE_FVAL                                          0x1

#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_ADDR(m,n)                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X554 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_OFFS(m,n)                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X554 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_RMSK                                                                    0x1010f
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_MAXm                                                                          3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_MAXn                                                                         11
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_POR                                                                  0x00000000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_POR_RMSK                                                             0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_ATTR                                                                              0x3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_INI2(m,n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_ADDR(m,n), HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_RMSK)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_ADDR(m,n), mask)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_OUTI2(m,n,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_ADDR(m,n),val)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_ADDR(m,n),mask,val,HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_INI2(m,n))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_READ_OR_WRITE_BMSK                                                      0x10000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_READ_OR_WRITE_SHFT                                                           16
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_READ_OR_WRITE_READ_FVAL                                                     0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_READ_OR_WRITE_WRITE_FVAL                                                    0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_RES_REQ_BMSK                                                              0x100
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_RES_REQ_SHFT                                                                  8
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_RES_REQ_FIRE_AND_FORGET_FVAL                                                0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_RES_REQ_RESPONSE_REQUIRED_FVAL                                              0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_MSG_LENGTH_BMSK                                                             0xf
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_MSGID_MSG_LENGTH_SHFT                                                               0

#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_ADDR(m,n)                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X558 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_OFFS(m,n)                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X558 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_RMSK                                                                     0x7ffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_MAXm                                                                           3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_MAXn                                                                          11
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_POR                                                                   0x00000000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_POR_RMSK                                                              0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_ATTR                                                                               0x3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_INI2(m,n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_ADDR(m,n), HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_RMSK)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_ADDR(m,n), mask)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_OUTI2(m,n,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_ADDR(m,n),val)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_ADDR(m,n),mask,val,HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_INI2(m,n))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_SLV_ID_BMSK                                                              0x70000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_SLV_ID_SHFT                                                                   16
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_OFFSET_BMSK                                                               0xffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_ADDR_OFFSET_SHFT                                                                    0

#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_ADDR(m,n)                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X55C + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_OFFS(m,n)                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X55C + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_RMSK                                                                  0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_MAXm                                                                           3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_MAXn                                                                          11
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_POR                                                                   0x00000000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_POR_RMSK                                                              0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_ATTR                                                                               0x3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_INI2(m,n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_ADDR(m,n), HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_RMSK)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_ADDR(m,n), mask)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_OUTI2(m,n,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_ADDR(m,n),val)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_ADDR(m,n),mask,val,HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_INI2(m,n))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_DATA_BMSK                                                             0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_DATA_DATA_SHFT                                                                      0

#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_ADDR(m,n)                                                           (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X560 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_OFFS(m,n)                                                           (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X560 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_RMSK                                                                   0x10101
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_MAXm                                                                         3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_MAXn                                                                        11
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_POR                                                                 0x00000000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_POR_RMSK                                                            0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_ATTR                                                                             0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_INI2(m,n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_ADDR(m,n), HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_RMSK)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_ADDR(m,n), mask)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_COMPLETED_BMSK                                                         0x10000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_COMPLETED_SHFT                                                              16
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_COMPLETED_HAS_NOT_BEEN_COMPLETE_FVAL                                       0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_COMPLETED_HAS_COMPLETED_FVAL                                               0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_ISSUED_BMSK                                                              0x100
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_ISSUED_SHFT                                                                  8
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_ISSUED_HAS_NOT_BEEN_SENT_OVER_EPCB_FVAL                                    0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_ISSUED_HAS_BEEN_SENT_OVER_EPCB_FVAL                                        0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_TRIGGERED_BMSK                                                             0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_TRIGGERED_SHFT                                                               0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_TRIGGERED_HAS_NOT_BEEN_TRIGGERE_FVAL                                       0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_STATUS_TRIGGERED_HAS_BEEN_TRIGGERED_FVAL                                          0x1

#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_ADDR(n)                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X564 + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_OFFS(n)                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X564 + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_RMSK                                                    0xffffffff
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_MAXn                                                            11
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_POR                                                     0x00000000
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_POR_RMSK                                                0xffffffff
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_ATTR                                                                 0x1
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_INI(n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_ADDR(n), HWIO_TITAN_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_RMSK)
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_INMI(n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_ADDR(n), mask)
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_READ_RESPONSE_DATA_BMSK                                 0xffffffff
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV0_READ_RESPONSE_DATA_READ_RESPONSE_DATA_SHFT                                          0

#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ADDR(m,n)                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X568 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_OFFS(m,n)                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X568 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_RMSK                                                         0x10101
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_MAXm                                                               3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_MAXn                                                              11
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_POR                                                       0x00000000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_POR_RMSK                                                  0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ATTR                                                                   0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_INI2(m,n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ADDR(m,n), HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_RMSK)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ADDR(m,n), mask)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_COMPLETED_BMSK                                               0x10000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_COMPLETED_SHFT                                                    16
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_COMPLETED_HAS_NOT_BEEN_COMPLETE_FVAL                             0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_COMPLETED_HAS_COMPLETED_FVAL                                     0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ISSUED_BMSK                                                    0x100
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ISSUED_SHFT                                                        8
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ISSUED_HAS_NOT_BEEN_SENT_OVER_EPCB_FVAL                          0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_ISSUED_HAS_BEEN_SENT_OVER_EPCB_FVAL                              0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_TRIGGERED_BMSK                                                   0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_TRIGGERED_SHFT                                                     0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_TRIGGERED_HAS_NOT_BEEN_TRIGGERE_FVAL                             0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV0_PROFILING_STATUS_TRIGGERED_HAS_BEEN_TRIGGERED_FVAL                                0x1

#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_ADDR                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x1520)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_OFFS                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x1520)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_RMSK                                                                0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_POR                                                          0x00000000
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_POR_RMSK                                                     0xffffffff
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_ATTR                                                                      0x3
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_IN                    \
                in_dword(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_ADDR)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_ADDR, m)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_ADDR,v)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_ADDR,m,v,HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_IN)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_AMC_COMPLETION_IRQ_ENABLE_BMSK                                      0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV1_AMC_COMPLETION_IRQ_ENABLE_SHFT                                        0

#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_ADDR                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x1524)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_OFFS                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x1524)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_RMSK                                                                0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_POR                                                          0x00000000
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_POR_RMSK                                                     0xffffffff
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_ATTR                                                                      0x1
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_IN                    \
                in_dword(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_ADDR)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_ADDR, m)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_AMC_COMPLETION_IRQ_STATUS_BMSK                                      0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV1_AMC_COMPLETION_IRQ_STATUS_SHFT                                        0

#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV1_ADDR                                                          (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x1528)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV1_OFFS                                                          (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x1528)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV1_RMSK                                                                 0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV1_POR                                                           0x00000000
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV1_POR_RMSK                                                      0xffffffff
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV1_ATTR                                                                       0x0
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV1_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV1_ADDR,v)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV1_AMC_COMPLETION_IRQ_CLEAR_BMSK                                        0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV1_AMC_COMPLETION_IRQ_CLEAR_SHFT                                          0

#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV1_ADDR                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x1530)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV1_OFFS                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x1530)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV1_RMSK                                                                         0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV1_POR                                                                   0x00000000
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV1_POR_RMSK                                                              0xffffffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV1_ATTR                                                                               0x3
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV1_IN                    \
                in_dword(HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV1_ADDR)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV1_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV1_ADDR, m)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV1_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV1_ADDR,v)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV1_ADDR,m,v,HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV1_IN)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV1_EN_BMSK                                                                      0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV1_EN_SHFT                                                                        0

#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV1_ADDR                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x1534)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV1_OFFS                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x1534)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV1_RMSK                                                                        0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV1_POR                                                                  0x00000000
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV1_POR_RMSK                                                             0xffffffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV1_ATTR                                                                              0x0
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV1_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV1_ADDR,v)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV1_CLR_BMSK                                                                    0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV1_CLR_SHFT                                                                      0

#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV1_ADDR                                                              (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x1538)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV1_OFFS                                                              (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x1538)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV1_RMSK                                                                     0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV1_POR                                                               0x00000000
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV1_POR_RMSK                                                          0xffffffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV1_ATTR                                                                           0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV1_IN                    \
                in_dword(HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV1_ADDR)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV1_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV1_ADDR, m)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV1_TIMEOUT_BMSK                                                             0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV1_TIMEOUT_SHFT                                                               0

#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV1_ADDR                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x153c)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV1_OFFS                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x153c)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV1_RMSK                                                                     0xffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV1_POR                                                                  0x0000ffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV1_POR_RMSK                                                             0xffffffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV1_ATTR                                                                              0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV1_IN                    \
                in_dword(HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV1_ADDR)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV1_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV1_ADDR, m)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV1_TIMEOUT_VAL_BMSK                                                         0xffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV1_TIMEOUT_VAL_SHFT                                                              0

#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_ADDR(m)                                                       (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X1540 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_OFFS(m)                                                       (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X1540 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_RMSK                                                               0xfff
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_MAXm                                                                   3
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_POR                                                           0x00000000
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_POR_RMSK                                                      0xffffffff
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_ATTR                                                                       0x3
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_INI(m)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_ADDR(m), HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_RMSK)
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_INMI(m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_ADDR(m), mask)
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_OUTI(m,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_ADDR(m),val)
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_ADDR(m),mask,val,HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_INI(m))
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_CMD_WAIT_FOR_CMPL_BMSK                                             0xfff
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_WAIT_FOR_CMPL_CMD_WAIT_FOR_CMPL_SHFT                                                 0

#define HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_ADDR(m)                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X1544 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_OFFS(m)                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X1544 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_RMSK                                                                     0x1010000
#define HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_MAXm                                                                             3
#define HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_POR                                                                     0x00000000
#define HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_POR_RMSK                                                                0xffffffff
#define HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_ATTR                                                                                 0x3
#define HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_INI(m)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_ADDR(m), HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_RMSK)
#define HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_INMI(m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_ADDR(m), mask)
#define HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_OUTI(m,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_ADDR(m),val)
#define HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_ADDR(m),mask,val,HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_INI(m))
#define HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_AMC_MODE_TRIGGER_BMSK                                                    0x1000000
#define HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_AMC_MODE_TRIGGER_SHFT                                                           24
#define HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_AMC_MODE_EN_BMSK                                                           0x10000
#define HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_AMC_MODE_EN_SHFT                                                                16
#define HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_AMC_MODE_EN_AMC_MODE_DISABLE_FVAL                                              0x0
#define HWIO_TITAN_RSCC_TCSm_DRV1_CONTROL_AMC_MODE_EN_AMC_MODE_ENABLED_FVAL                                              0x1

#define HWIO_TITAN_RSCC_TCSm_DRV1_STATUS_ADDR(m)                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X1548 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV1_STATUS_OFFS(m)                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X1548 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV1_STATUS_RMSK                                                                            0x1
#define HWIO_TITAN_RSCC_TCSm_DRV1_STATUS_MAXm                                                                              3
#define HWIO_TITAN_RSCC_TCSm_DRV1_STATUS_POR                                                                      0x00000001
#define HWIO_TITAN_RSCC_TCSm_DRV1_STATUS_POR_RMSK                                                                 0xffffffff
#define HWIO_TITAN_RSCC_TCSm_DRV1_STATUS_ATTR                                                                                  0x1
#define HWIO_TITAN_RSCC_TCSm_DRV1_STATUS_INI(m)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV1_STATUS_ADDR(m), HWIO_TITAN_RSCC_TCSm_DRV1_STATUS_RMSK)
#define HWIO_TITAN_RSCC_TCSm_DRV1_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV1_STATUS_ADDR(m), mask)
#define HWIO_TITAN_RSCC_TCSm_DRV1_STATUS_CONTROLLER_IDLE_BMSK                                                            0x1
#define HWIO_TITAN_RSCC_TCSm_DRV1_STATUS_CONTROLLER_IDLE_SHFT                                                              0
#define HWIO_TITAN_RSCC_TCSm_DRV1_STATUS_CONTROLLER_IDLE_NOT_IDLE_FVAL                                                   0x0
#define HWIO_TITAN_RSCC_TCSm_DRV1_STATUS_CONTROLLER_IDLE_IS_IDLE_FVAL                                                    0x1

#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_ADDR(m)                                                              (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X154C + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_OFFS(m)                                                              (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X154C + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_RMSK                                                                      0xfff
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_MAXm                                                                          3
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_POR                                                                  0x00000000
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_POR_RMSK                                                             0xffffffff
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_ATTR                                                                              0x3
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_INI(m)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_ADDR(m), HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_RMSK)
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_INMI(m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_ADDR(m), mask)
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_OUTI(m,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_ADDR(m),val)
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_ADDR(m),mask,val,HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_INI(m))
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_INDIVIDUAL_CMD_ENABLE_MASK_BMSK                                           0xfff
#define HWIO_TITAN_RSCC_TCSm_DRV1_CMD_ENABLE_INDIVIDUAL_CMD_ENABLE_MASK_SHFT                                               0

#define HWIO_TITAN_RSCC_TCSm_DRV1_PROFILING_STATUS_ADDR(m)                                                        (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X1550 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV1_PROFILING_STATUS_OFFS(m)                                                        (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X1550 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV1_PROFILING_STATUS_RMSK                                                                  0x1
#define HWIO_TITAN_RSCC_TCSm_DRV1_PROFILING_STATUS_MAXm                                                                    3
#define HWIO_TITAN_RSCC_TCSm_DRV1_PROFILING_STATUS_POR                                                            0x00000001
#define HWIO_TITAN_RSCC_TCSm_DRV1_PROFILING_STATUS_POR_RMSK                                                       0xffffffff
#define HWIO_TITAN_RSCC_TCSm_DRV1_PROFILING_STATUS_ATTR                                                                        0x1
#define HWIO_TITAN_RSCC_TCSm_DRV1_PROFILING_STATUS_INI(m)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV1_PROFILING_STATUS_ADDR(m), HWIO_TITAN_RSCC_TCSm_DRV1_PROFILING_STATUS_RMSK)
#define HWIO_TITAN_RSCC_TCSm_DRV1_PROFILING_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV1_PROFILING_STATUS_ADDR(m), mask)
#define HWIO_TITAN_RSCC_TCSm_DRV1_PROFILING_STATUS_CONTROLLER_IDLE_BMSK                                                  0x1
#define HWIO_TITAN_RSCC_TCSm_DRV1_PROFILING_STATUS_CONTROLLER_IDLE_SHFT                                                    0
#define HWIO_TITAN_RSCC_TCSm_DRV1_PROFILING_STATUS_CONTROLLER_IDLE_NOT_IDLE_FVAL                                         0x0
#define HWIO_TITAN_RSCC_TCSm_DRV1_PROFILING_STATUS_CONTROLLER_IDLE_IS_IDLE_FVAL                                          0x1

#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_ADDR(m,n)                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X1554 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_OFFS(m,n)                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X1554 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_RMSK                                                                    0x1010f
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_MAXm                                                                          3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_MAXn                                                                         11
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_POR                                                                  0x00000000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_POR_RMSK                                                             0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_ATTR                                                                              0x3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_INI2(m,n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_ADDR(m,n), HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_RMSK)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_ADDR(m,n), mask)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_OUTI2(m,n,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_ADDR(m,n),val)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_ADDR(m,n),mask,val,HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_INI2(m,n))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_READ_OR_WRITE_BMSK                                                      0x10000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_READ_OR_WRITE_SHFT                                                           16
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_READ_OR_WRITE_READ_FVAL                                                     0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_READ_OR_WRITE_WRITE_FVAL                                                    0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_RES_REQ_BMSK                                                              0x100
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_RES_REQ_SHFT                                                                  8
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_RES_REQ_FIRE_AND_FORGET_FVAL                                                0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_RES_REQ_RESPONSE_REQUIRED_FVAL                                              0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_MSG_LENGTH_BMSK                                                             0xf
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_MSGID_MSG_LENGTH_SHFT                                                               0

#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_ADDR(m,n)                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X1558 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_OFFS(m,n)                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X1558 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_RMSK                                                                     0x7ffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_MAXm                                                                           3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_MAXn                                                                          11
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_POR                                                                   0x00000000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_POR_RMSK                                                              0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_ATTR                                                                               0x3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_INI2(m,n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_ADDR(m,n), HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_RMSK)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_ADDR(m,n), mask)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_OUTI2(m,n,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_ADDR(m,n),val)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_ADDR(m,n),mask,val,HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_INI2(m,n))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_SLV_ID_BMSK                                                              0x70000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_SLV_ID_SHFT                                                                   16
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_OFFSET_BMSK                                                               0xffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_ADDR_OFFSET_SHFT                                                                    0

#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_ADDR(m,n)                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X155C + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_OFFS(m,n)                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X155C + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_RMSK                                                                  0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_MAXm                                                                           3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_MAXn                                                                          11
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_POR                                                                   0x00000000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_POR_RMSK                                                              0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_ATTR                                                                               0x3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_INI2(m,n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_ADDR(m,n), HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_RMSK)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_ADDR(m,n), mask)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_OUTI2(m,n,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_ADDR(m,n),val)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_ADDR(m,n),mask,val,HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_INI2(m,n))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_DATA_BMSK                                                             0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_DATA_DATA_SHFT                                                                      0

#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_ADDR(m,n)                                                           (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X1560 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_OFFS(m,n)                                                           (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X1560 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_RMSK                                                                   0x10101
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_MAXm                                                                         3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_MAXn                                                                        11
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_POR                                                                 0x00000000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_POR_RMSK                                                            0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_ATTR                                                                             0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_INI2(m,n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_ADDR(m,n), HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_RMSK)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_ADDR(m,n), mask)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_COMPLETED_BMSK                                                         0x10000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_COMPLETED_SHFT                                                              16
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_COMPLETED_HAS_NOT_BEEN_COMPLETE_FVAL                                       0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_COMPLETED_HAS_COMPLETED_FVAL                                               0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_ISSUED_BMSK                                                              0x100
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_ISSUED_SHFT                                                                  8
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_ISSUED_HAS_NOT_BEEN_SENT_OVER_EPCB_FVAL                                    0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_ISSUED_HAS_BEEN_SENT_OVER_EPCB_FVAL                                        0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_TRIGGERED_BMSK                                                             0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_TRIGGERED_SHFT                                                               0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_TRIGGERED_HAS_NOT_BEEN_TRIGGERE_FVAL                                       0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_STATUS_TRIGGERED_HAS_BEEN_TRIGGERED_FVAL                                          0x1

#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_ADDR(n)                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X1564 + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_OFFS(n)                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X1564 + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_RMSK                                                    0xffffffff
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_MAXn                                                            11
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_POR                                                     0x00000000
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_POR_RMSK                                                0xffffffff
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_ATTR                                                                 0x1
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_INI(n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_ADDR(n), HWIO_TITAN_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_RMSK)
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_INMI(n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_ADDR(n), mask)
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_READ_RESPONSE_DATA_BMSK                                 0xffffffff
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV1_READ_RESPONSE_DATA_READ_RESPONSE_DATA_SHFT                                          0

#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_ADDR(m,n)                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X1568 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_OFFS(m,n)                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X1568 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_RMSK                                                         0x10101
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_MAXm                                                               3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_MAXn                                                              11
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_POR                                                       0x00000000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_POR_RMSK                                                  0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_ATTR                                                                   0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_INI2(m,n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_ADDR(m,n), HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_RMSK)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_ADDR(m,n), mask)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_COMPLETED_BMSK                                               0x10000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_COMPLETED_SHFT                                                    16
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_COMPLETED_HAS_NOT_BEEN_COMPLETE_FVAL                             0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_COMPLETED_HAS_COMPLETED_FVAL                                     0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_ISSUED_BMSK                                                    0x100
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_ISSUED_SHFT                                                        8
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_ISSUED_HAS_NOT_BEEN_SENT_OVER_EPCB_FVAL                          0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_ISSUED_HAS_BEEN_SENT_OVER_EPCB_FVAL                              0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_TRIGGERED_BMSK                                                   0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_TRIGGERED_SHFT                                                     0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_TRIGGERED_HAS_NOT_BEEN_TRIGGERE_FVAL                             0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV1_PROFILING_STATUS_TRIGGERED_HAS_BEEN_TRIGGERED_FVAL                                0x1

#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_ADDR                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2520)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_OFFS                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2520)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_RMSK                                                                0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_POR                                                          0x00000000
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_POR_RMSK                                                     0xffffffff
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_ATTR                                                                      0x3
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_IN                    \
                in_dword(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_ADDR)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_ADDR, m)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_ADDR,v)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_ADDR,m,v,HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_IN)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_AMC_COMPLETION_IRQ_ENABLE_BMSK                                      0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_ENABLE_DRV2_AMC_COMPLETION_IRQ_ENABLE_SHFT                                        0

#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_ADDR                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2524)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_OFFS                                                         (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2524)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_RMSK                                                                0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_POR                                                          0x00000000
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_POR_RMSK                                                     0xffffffff
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_ATTR                                                                      0x1
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_IN                    \
                in_dword(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_ADDR)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_ADDR, m)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_AMC_COMPLETION_IRQ_STATUS_BMSK                                      0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_STATUS_DRV2_AMC_COMPLETION_IRQ_STATUS_SHFT                                        0

#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV2_ADDR                                                          (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2528)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV2_OFFS                                                          (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2528)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV2_RMSK                                                                 0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV2_POR                                                           0x00000000
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV2_POR_RMSK                                                      0xffffffff
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV2_ATTR                                                                       0x0
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV2_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV2_ADDR,v)
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV2_AMC_COMPLETION_IRQ_CLEAR_BMSK                                        0xf
#define HWIO_TITAN_RSCC_TCS_AMC_MODE_IRQ_CLEAR_DRV2_AMC_COMPLETION_IRQ_CLEAR_SHFT                                          0

#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV2_ADDR                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2530)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV2_OFFS                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2530)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV2_RMSK                                                                         0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV2_POR                                                                   0x00000000
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV2_POR_RMSK                                                              0xffffffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV2_ATTR                                                                               0x3
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV2_IN                    \
                in_dword(HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV2_ADDR)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV2_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV2_ADDR, m)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV2_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV2_ADDR,v)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV2_ADDR,m,v,HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV2_IN)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV2_EN_BMSK                                                                      0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_EN_DRV2_EN_SHFT                                                                        0

#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV2_ADDR                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2534)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV2_OFFS                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2534)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV2_RMSK                                                                        0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV2_POR                                                                  0x00000000
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV2_POR_RMSK                                                             0xffffffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV2_ATTR                                                                              0x0
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV2_OUT(v)            \
                out_dword(HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV2_ADDR,v)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV2_CLR_BMSK                                                                    0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_CLR_DRV2_CLR_SHFT                                                                      0

#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV2_ADDR                                                              (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x2538)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV2_OFFS                                                              (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x2538)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV2_RMSK                                                                     0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV2_POR                                                               0x00000000
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV2_POR_RMSK                                                          0xffffffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV2_ATTR                                                                           0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV2_IN                    \
                in_dword(HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV2_ADDR)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV2_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV2_ADDR, m)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV2_TIMEOUT_BMSK                                                             0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_STATUS_DRV2_TIMEOUT_SHFT                                                               0

#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV2_ADDR                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0x253c)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV2_OFFS                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0x253c)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV2_RMSK                                                                     0xffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV2_POR                                                                  0x0000ffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV2_POR_RMSK                                                             0xffffffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV2_ATTR                                                                              0x1
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV2_IN                    \
                in_dword(HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV2_ADDR)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV2_INM(m)            \
                in_dword_masked(HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV2_ADDR, m)
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV2_TIMEOUT_VAL_BMSK                                                         0xffff
#define HWIO_TITAN_RSCC_TCS_TIMEOUT_VAL_DRV2_TIMEOUT_VAL_SHFT                                                              0

#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_ADDR(m)                                                       (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2540 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_OFFS(m)                                                       (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2540 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_RMSK                                                               0xfff
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_MAXm                                                                   3
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_POR                                                           0x00000000
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_POR_RMSK                                                      0xffffffff
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_ATTR                                                                       0x3
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_INI(m)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_ADDR(m), HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_RMSK)
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_INMI(m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_ADDR(m), mask)
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_OUTI(m,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_ADDR(m),val)
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_ADDR(m),mask,val,HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_INI(m))
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_CMD_WAIT_FOR_CMPL_BMSK                                             0xfff
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_WAIT_FOR_CMPL_CMD_WAIT_FOR_CMPL_SHFT                                                 0

#define HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_ADDR(m)                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2544 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_OFFS(m)                                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2544 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_RMSK                                                                     0x1010000
#define HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_MAXm                                                                             3
#define HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_POR                                                                     0x00000000
#define HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_POR_RMSK                                                                0xffffffff
#define HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_ATTR                                                                                 0x3
#define HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_INI(m)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_ADDR(m), HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_RMSK)
#define HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_INMI(m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_ADDR(m), mask)
#define HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_OUTI(m,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_ADDR(m),val)
#define HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_ADDR(m),mask,val,HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_INI(m))
#define HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_AMC_MODE_TRIGGER_BMSK                                                    0x1000000
#define HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_AMC_MODE_TRIGGER_SHFT                                                           24
#define HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_AMC_MODE_EN_BMSK                                                           0x10000
#define HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_AMC_MODE_EN_SHFT                                                                16
#define HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_AMC_MODE_EN_AMC_MODE_DISABLE_FVAL                                              0x0
#define HWIO_TITAN_RSCC_TCSm_DRV2_CONTROL_AMC_MODE_EN_AMC_MODE_ENABLED_FVAL                                              0x1

#define HWIO_TITAN_RSCC_TCSm_DRV2_STATUS_ADDR(m)                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2548 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV2_STATUS_OFFS(m)                                                                  (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2548 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV2_STATUS_RMSK                                                                            0x1
#define HWIO_TITAN_RSCC_TCSm_DRV2_STATUS_MAXm                                                                              3
#define HWIO_TITAN_RSCC_TCSm_DRV2_STATUS_POR                                                                      0x00000001
#define HWIO_TITAN_RSCC_TCSm_DRV2_STATUS_POR_RMSK                                                                 0xffffffff
#define HWIO_TITAN_RSCC_TCSm_DRV2_STATUS_ATTR                                                                                  0x1
#define HWIO_TITAN_RSCC_TCSm_DRV2_STATUS_INI(m)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV2_STATUS_ADDR(m), HWIO_TITAN_RSCC_TCSm_DRV2_STATUS_RMSK)
#define HWIO_TITAN_RSCC_TCSm_DRV2_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV2_STATUS_ADDR(m), mask)
#define HWIO_TITAN_RSCC_TCSm_DRV2_STATUS_CONTROLLER_IDLE_BMSK                                                            0x1
#define HWIO_TITAN_RSCC_TCSm_DRV2_STATUS_CONTROLLER_IDLE_SHFT                                                              0
#define HWIO_TITAN_RSCC_TCSm_DRV2_STATUS_CONTROLLER_IDLE_NOT_IDLE_FVAL                                                   0x0
#define HWIO_TITAN_RSCC_TCSm_DRV2_STATUS_CONTROLLER_IDLE_IS_IDLE_FVAL                                                    0x1

#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_ADDR(m)                                                              (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X254C + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_OFFS(m)                                                              (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X254C + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_RMSK                                                                      0xfff
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_MAXm                                                                          3
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_POR                                                                  0x00000000
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_POR_RMSK                                                             0xffffffff
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_ATTR                                                                              0x3
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_INI(m)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_ADDR(m), HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_RMSK)
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_INMI(m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_ADDR(m), mask)
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_OUTI(m,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_ADDR(m),val)
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_OUTMI(m,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_ADDR(m),mask,val,HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_INI(m))
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_INDIVIDUAL_CMD_ENABLE_MASK_BMSK                                           0xfff
#define HWIO_TITAN_RSCC_TCSm_DRV2_CMD_ENABLE_INDIVIDUAL_CMD_ENABLE_MASK_SHFT                                               0

#define HWIO_TITAN_RSCC_TCSm_DRV2_PROFILING_STATUS_ADDR(m)                                                        (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2550 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV2_PROFILING_STATUS_OFFS(m)                                                        (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2550 + (0x150*(m)))
#define HWIO_TITAN_RSCC_TCSm_DRV2_PROFILING_STATUS_RMSK                                                                  0x1
#define HWIO_TITAN_RSCC_TCSm_DRV2_PROFILING_STATUS_MAXm                                                                    3
#define HWIO_TITAN_RSCC_TCSm_DRV2_PROFILING_STATUS_POR                                                            0x00000001
#define HWIO_TITAN_RSCC_TCSm_DRV2_PROFILING_STATUS_POR_RMSK                                                       0xffffffff
#define HWIO_TITAN_RSCC_TCSm_DRV2_PROFILING_STATUS_ATTR                                                                        0x1
#define HWIO_TITAN_RSCC_TCSm_DRV2_PROFILING_STATUS_INI(m)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV2_PROFILING_STATUS_ADDR(m), HWIO_TITAN_RSCC_TCSm_DRV2_PROFILING_STATUS_RMSK)
#define HWIO_TITAN_RSCC_TCSm_DRV2_PROFILING_STATUS_INMI(m,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_DRV2_PROFILING_STATUS_ADDR(m), mask)
#define HWIO_TITAN_RSCC_TCSm_DRV2_PROFILING_STATUS_CONTROLLER_IDLE_BMSK                                                  0x1
#define HWIO_TITAN_RSCC_TCSm_DRV2_PROFILING_STATUS_CONTROLLER_IDLE_SHFT                                                    0
#define HWIO_TITAN_RSCC_TCSm_DRV2_PROFILING_STATUS_CONTROLLER_IDLE_NOT_IDLE_FVAL                                         0x0
#define HWIO_TITAN_RSCC_TCSm_DRV2_PROFILING_STATUS_CONTROLLER_IDLE_IS_IDLE_FVAL                                          0x1

#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_ADDR(m,n)                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2554 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_OFFS(m,n)                                                            (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2554 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_RMSK                                                                    0x1010f
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_MAXm                                                                          3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_MAXn                                                                         11
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_POR                                                                  0x00000000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_POR_RMSK                                                             0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_ATTR                                                                              0x3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_INI2(m,n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_ADDR(m,n), HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_RMSK)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_ADDR(m,n), mask)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_OUTI2(m,n,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_ADDR(m,n),val)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_ADDR(m,n),mask,val,HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_INI2(m,n))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_READ_OR_WRITE_BMSK                                                      0x10000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_READ_OR_WRITE_SHFT                                                           16
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_READ_OR_WRITE_READ_FVAL                                                     0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_READ_OR_WRITE_WRITE_FVAL                                                    0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_RES_REQ_BMSK                                                              0x100
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_RES_REQ_SHFT                                                                  8
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_RES_REQ_FIRE_AND_FORGET_FVAL                                                0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_RES_REQ_RESPONSE_REQUIRED_FVAL                                              0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_MSG_LENGTH_BMSK                                                             0xf
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_MSGID_MSG_LENGTH_SHFT                                                               0

#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_ADDR(m,n)                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2558 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_OFFS(m,n)                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2558 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_RMSK                                                                     0x7ffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_MAXm                                                                           3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_MAXn                                                                          11
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_POR                                                                   0x00000000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_POR_RMSK                                                              0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_ATTR                                                                               0x3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_INI2(m,n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_ADDR(m,n), HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_RMSK)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_ADDR(m,n), mask)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_OUTI2(m,n,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_ADDR(m,n),val)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_ADDR(m,n),mask,val,HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_INI2(m,n))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_SLV_ID_BMSK                                                              0x70000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_SLV_ID_SHFT                                                                   16
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_OFFSET_BMSK                                                               0xffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_ADDR_OFFSET_SHFT                                                                    0

#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_ADDR(m,n)                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X255C + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_OFFS(m,n)                                                             (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X255C + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_RMSK                                                                  0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_MAXm                                                                           3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_MAXn                                                                          11
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_POR                                                                   0x00000000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_POR_RMSK                                                              0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_ATTR                                                                               0x3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_INI2(m,n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_ADDR(m,n), HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_RMSK)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_ADDR(m,n), mask)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_OUTI2(m,n,val)        \
                out_dword(HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_ADDR(m,n),val)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_OUTMI2(m,n,mask,val) \
                out_dword_masked_ns(HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_ADDR(m,n),mask,val,HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_INI2(m,n))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_DATA_BMSK                                                             0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_DATA_DATA_SHFT                                                                      0

#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_ADDR(m,n)                                                           (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2560 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_OFFS(m,n)                                                           (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2560 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_RMSK                                                                   0x10101
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_MAXm                                                                         3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_MAXn                                                                        11
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_POR                                                                 0x00000000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_POR_RMSK                                                            0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_ATTR                                                                             0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_INI2(m,n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_ADDR(m,n), HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_RMSK)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_ADDR(m,n), mask)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_COMPLETED_BMSK                                                         0x10000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_COMPLETED_SHFT                                                              16
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_COMPLETED_HAS_NOT_BEEN_COMPLETE_FVAL                                       0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_COMPLETED_HAS_COMPLETED_FVAL                                               0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_ISSUED_BMSK                                                              0x100
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_ISSUED_SHFT                                                                  8
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_ISSUED_HAS_NOT_BEEN_SENT_OVER_EPCB_FVAL                                    0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_ISSUED_HAS_BEEN_SENT_OVER_EPCB_FVAL                                        0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_TRIGGERED_BMSK                                                             0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_TRIGGERED_SHFT                                                               0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_TRIGGERED_HAS_NOT_BEEN_TRIGGERE_FVAL                                       0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_STATUS_TRIGGERED_HAS_BEEN_TRIGGERED_FVAL                                          0x1

#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_ADDR(n)                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2564 + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_OFFS(n)                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2564 + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_RMSK                                                    0xffffffff
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_MAXn                                                            11
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_POR                                                     0x00000000
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_POR_RMSK                                                0xffffffff
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_ATTR                                                                 0x1
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_INI(n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_ADDR(n), HWIO_TITAN_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_RMSK)
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_INMI(n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_ADDR(n), mask)
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_READ_RESPONSE_DATA_BMSK                                 0xffffffff
#define HWIO_TITAN_RSCC_TCS0_CMDn_DRV2_READ_RESPONSE_DATA_READ_RESPONSE_DATA_SHFT                                          0

#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_ADDR(m,n)                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE      + 0X2568 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_OFFS(m,n)                                                 (TITAN_RSCC_RSCC_RSC_REG_BASE_OFFS + 0X2568 + (0x150*(m)) + (0x18*(n)))
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_RMSK                                                         0x10101
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_MAXm                                                               3
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_MAXn                                                              11
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_POR                                                       0x00000000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_POR_RMSK                                                  0xffffffff
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_ATTR                                                                   0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_INI2(m,n)                \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_ADDR(m,n), HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_RMSK)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_INMI2(m,n,mask)        \
                in_dword_masked(HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_ADDR(m,n), mask)
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_COMPLETED_BMSK                                               0x10000
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_COMPLETED_SHFT                                                    16
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_COMPLETED_HAS_NOT_BEEN_COMPLETE_FVAL                             0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_COMPLETED_HAS_COMPLETED_FVAL                                     0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_ISSUED_BMSK                                                    0x100
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_ISSUED_SHFT                                                        8
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_ISSUED_HAS_NOT_BEEN_SENT_OVER_EPCB_FVAL                          0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_ISSUED_HAS_BEEN_SENT_OVER_EPCB_FVAL                              0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_TRIGGERED_BMSK                                                   0x1
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_TRIGGERED_SHFT                                                     0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_TRIGGERED_HAS_NOT_BEEN_TRIGGERE_FVAL                             0x0
#define HWIO_TITAN_RSCC_TCSm_CMDn_DRV2_PROFILING_STATUS_TRIGGERED_HAS_BEEN_TRIGGERED_FVAL                                0x1


#endif /* __RSC_HAL_HWIO_H__ */
