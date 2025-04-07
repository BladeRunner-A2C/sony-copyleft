#ifndef __BCM_HWIO_H__
#define __BCM_HWIO_H__
/*
===========================================================================
*/
/**
  @file bcm_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    .*RPMH_BCM.*

  'Exclude' filters applied: CD0_CPn[RPMH] CD1_CPn[RPMH] CD2_CPn[RPMH] CD3_CPn[RPMH] CD4_CPn[RPMH] CD5_CPn[RPMH] CD6_CPn[RPMH] CD7_CPn[RPMH] CD8_CPn[RPMH] CD9_CPn[RPMH] CD10_CPn[RPMH] CD11_CPn[RPMH] CD12_CPn[RPMH] CD13_CPn[RPMH] CD14_CPn[RPMH] CD15_CPn[RPMH] 

  Generation parameters: 
  { 'check-for-overlaps': True,
    'check-sizes': True,
    'create-array': [ [ 'CD_TH_CD0_CPn',
                        { 'arg': 'm',
                          'arg_pos': 8,
                          'array_offset': 64,
                          'max_index': 15}],
                      [ 'TCS_CFG_VOTE_DATA_CD0_CPn',
                        { 'arg': 'm',
                          'arg_pos': 20,
                          'array_offset': 64,
                          'max_index': 15}]],
    'filename': 'bcm_hwio.h',
    'header': '\n#include <HALhwio.h>\n#include <msmhwiobase.h>\n',
    'ignore-prefixes': True,
    'map-type': 'physical',
    'module-filter-exclude': { 'RPMH': [ 'CD0_CPn',
                                         'CD1_CPn',
                                         'CD2_CPn',
                                         'CD3_CPn',
                                         'CD4_CPn',
                                         'CD5_CPn',
                                         'CD6_CPn',
                                         'CD7_CPn',
                                         'CD8_CPn',
                                         'CD9_CPn',
                                         'CD10_CPn',
                                         'CD11_CPn',
                                         'CD12_CPn',
                                         'CD13_CPn',
                                         'CD14_CPn',
                                         'CD15_CPn']},
    'modules': ['.*RPMH_BCM.*']}
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


#include <HALhwio.h>
#include <msmhwiobase.h>


/*----------------------------------------------------------------------------
 * MODULE: RPMH_BCM_BCM_TOP
 *--------------------------------------------------------------------------*/

#define RPMH_BCM_BCM_TOP_REG_BASE (AOSS_BASE      + 0x00a00000)
#define RPMH_BCM_BCM_TOP_REG_BASE_SIZE 0x200000
#define RPMH_BCM_BCM_TOP_REG_BASE_USED 0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_VOTETABLE
 *--------------------------------------------------------------------------*/

#define BCM_VOTETABLE_REG_BASE                                                              (AOSS_BASE      + 0x00a00000)
#define BCM_VOTETABLE_REG_BASE_SIZE                                                         0x1e0000
#define BCM_VOTETABLE_REG_BASE_USED                                                         0x170494

#define HWIO_VOTETABLE_DRVr_NDd_ADDR(r,d)                                                   (BCM_VOTETABLE_REG_BASE      + 0x00000000 + 0x10000 * (r) + 0x4 * (d))
#define HWIO_VOTETABLE_DRVr_NDd_RMSK                                                        0xefffffff
#define HWIO_VOTETABLE_DRVr_NDd_MAXr                                                                23
#define HWIO_VOTETABLE_DRVr_NDd_MAXd                                                                31
#define HWIO_VOTETABLE_DRVr_NDd_INI2(r,d)        \
        in_dword_masked(HWIO_VOTETABLE_DRVr_NDd_ADDR(r,d), HWIO_VOTETABLE_DRVr_NDd_RMSK)
#define HWIO_VOTETABLE_DRVr_NDd_INMI2(r,d,mask)    \
        in_dword_masked(HWIO_VOTETABLE_DRVr_NDd_ADDR(r,d), mask)
#define HWIO_VOTETABLE_DRVr_NDd_OUTI2(r,d,val)    \
        out_dword(HWIO_VOTETABLE_DRVr_NDd_ADDR(r,d),val)
#define HWIO_VOTETABLE_DRVr_NDd_OUTMI2(r,d,mask,val) \
        out_dword_masked_ns(HWIO_VOTETABLE_DRVr_NDd_ADDR(r,d),mask,val,HWIO_VOTETABLE_DRVr_NDd_INI2(r,d))
#define HWIO_VOTETABLE_DRVr_NDd_RESP_REQ_BMSK                                               0x80000000
#define HWIO_VOTETABLE_DRVr_NDd_RESP_REQ_SHFT                                                     0x1f
#define HWIO_VOTETABLE_DRVr_NDd_COMMIT_BMSK                                                 0x40000000
#define HWIO_VOTETABLE_DRVr_NDd_COMMIT_SHFT                                                       0x1e
#define HWIO_VOTETABLE_DRVr_NDd_VOTE_VALID_BMSK                                             0x20000000
#define HWIO_VOTETABLE_DRVr_NDd_VOTE_VALID_SHFT                                                   0x1d
#define HWIO_VOTETABLE_DRVr_NDd_VOTE_X_BMSK                                                  0xfffc000
#define HWIO_VOTETABLE_DRVr_NDd_VOTE_X_SHFT                                                        0xe
#define HWIO_VOTETABLE_DRVr_NDd_VOTE_Y_BMSK                                                     0x3fff
#define HWIO_VOTETABLE_DRVr_NDd_VOTE_Y_SHFT                                                        0x0

#define HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_ADDR(r)                                          (BCM_VOTETABLE_REG_BASE      + 0x00000100 + 0x10000 * (r))
#define HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_RMSK                                                 0x1fff
#define HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_MAXr                                                     23
#define HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_INI(r)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_ADDR(r), HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_INMI(r,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_ADDR(r), mask)
#define HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_AGG_BUSY_CD_BMSK                                     0x1fff
#define HWIO_SHADOW_STATUS_DRVr_FE_AGG_FSM_AGG_BUSY_CD_SHFT                                        0x0

#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_ADDR(r,m)                                            (BCM_VOTETABLE_REG_BASE      + 0x00000104 + 0x10000 * (r) + 0x4 * (m))
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_RMSK                                                 0x3fff00ff
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_MAXr                                                         23
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_MAXm                                                         12
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_INI2(r,m)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_FE_CDm_ADDR(r,m), HWIO_SHADOW_STATUS_DRVr_FE_CDm_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_INMI2(r,m,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_FE_CDm_ADDR(r,m), mask)
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_AGG_BW_BMSK                                          0x3fff0000
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_AGG_BW_SHFT                                                0x10
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_FINAL_CP_BMSK                                              0xf0
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_FINAL_CP_SHFT                                               0x4
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_AGG_CP_BMSK                                                 0xf
#define HWIO_SHADOW_STATUS_DRVr_FE_CDm_AGG_CP_SHFT                                                 0x0

#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_ADDR(r,m)                                            (BCM_VOTETABLE_REG_BASE      + 0x00000274 + 0x10000 * (r) + 0x4 * (m))
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_RMSK                                                    0xfffff
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_MAXr                                                         23
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_MAXm                                                         12
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_INI2(r,m)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_CDm_ADDR(r,m), HWIO_SHADOW_STATUS_DRVr_BE_CDm_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_INMI2(r,m,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_CDm_ADDR(r,m), mask)
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_CLK_DEST_STATE_BMSK                                     0xf0000
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_CLK_DEST_STATE_SHFT                                        0x10
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_COMBINED_CP_BMSK                                         0xf000
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_COMBINED_CP_SHFT                                            0xc
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_SW_CP_SNAP_BMSK                                           0xf00
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_SW_CP_SNAP_SHFT                                             0x8
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_WRITTEN_CP_BMSK                                            0xf0
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_WRITTEN_CP_SHFT                                             0x4
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_CURR_CP_BMSK                                                0xf
#define HWIO_SHADOW_STATUS_DRVr_BE_CDm_CURR_CP_SHFT                                                0x0

#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_ADDR(r,m)                                        (BCM_VOTETABLE_REG_BASE      + 0x000002b4 + 0x10000 * (r) + 0x4 * (m))
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_RMSK                                                0x1ff01
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_MAXr                                                     23
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_MAXm                                                     12
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_INI2(r,m)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_ADDR(r,m), HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_INMI2(r,m,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_ADDR(r,m), mask)
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_SEQ_CURR_PC_BMSK                                    0x1ff00
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_SEQ_CURR_PC_SHFT                                        0x8
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_SEQ_STATE_BMSK                                          0x1
#define HWIO_SHADOW_STATUS_DRVr_BE_SEQ_CDm_SEQ_STATE_SHFT                                          0x0

#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_ADDR(r,m)                           (BCM_VOTETABLE_REG_BASE      + 0x000002f4 + 0x10000 * (r) + 0x4 * (m))
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_RMSK                                       0xf
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_MAXr                                        23
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_MAXm                                        12
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_INI2(r,m)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_ADDR(r,m), HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_INMI2(r,m,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_ADDR(r,m), mask)
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_ISSUE_STATUS_BMSK                          0xf
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_ISSUE_STATUS_CDm_ISSUE_STATUS_SHFT                          0x0

#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_ADDR(r,m)                            (BCM_VOTETABLE_REG_BASE      + 0x00000334 + 0x10000 * (r) + 0x4 * (m))
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_RMSK                                        0xf
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_MAXr                                         23
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_MAXm                                         12
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_INI2(r,m)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_ADDR(r,m), HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_INMI2(r,m,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_ADDR(r,m), mask)
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_SENT_STATUS_BMSK                            0xf
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_SENT_STATUS_CDm_SENT_STATUS_SHFT                            0x0

#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_ADDR(r,m)                            (BCM_VOTETABLE_REG_BASE      + 0x00000374 + 0x10000 * (r) + 0x4 * (m))
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_RMSK                                        0xf
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_MAXr                                         23
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_MAXm                                         12
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_INI2(r,m)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_ADDR(r,m), HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_INMI2(r,m,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_ADDR(r,m), mask)
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_CMPL_STATUS_BMSK                            0xf
#define HWIO_SHADOW_STATUS_DRVr_BE_CMD_CMPL_STATUS_CDm_CMPL_STATUS_SHFT                            0x0

#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_ADDR(r)                                        (BCM_VOTETABLE_REG_BASE      + 0x0000048c + 0x10000 * (r))
#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_RMSK                                            0x1ffffff
#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_MAXr                                                   23
#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_INI(r)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_ADDR(r), HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_INMI(r,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_ADDR(r), mask)
#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_CTT_EMPTY_DRV_BMSK                              0x1fffffe
#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_CTT_EMPTY_DRV_SHFT                                    0x1
#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_CTT_EMPTY_BMSK                                        0x1
#define HWIO_SHADOW_STATUS_DRVr_CE_CTT_EMPTY_CTT_EMPTY_SHFT                                        0x0

#define HWIO_SHADOW_STATUS_DRVr_BCM_ADDR(r)                                                 (BCM_VOTETABLE_REG_BASE      + 0x00000490 + 0x10000 * (r))
#define HWIO_SHADOW_STATUS_DRVr_BCM_RMSK                                                           0x1
#define HWIO_SHADOW_STATUS_DRVr_BCM_MAXr                                                            23
#define HWIO_SHADOW_STATUS_DRVr_BCM_INI(r)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BCM_ADDR(r), HWIO_SHADOW_STATUS_DRVr_BCM_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_BCM_INMI(r,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_BCM_ADDR(r), mask)
#define HWIO_SHADOW_STATUS_DRVr_BCM_BCM_IDLE_BMSK                                                  0x1
#define HWIO_SHADOW_STATUS_DRVr_BCM_BCM_IDLE_SHFT                                                  0x0

#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_ADDR(r)                                          (BCM_VOTETABLE_REG_BASE      + 0x00000494 + 0x10000 * (r))
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_RMSK                                               0xffffff
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_MAXr                                                     23
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_INI(r)        \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_HW_VERSION_ADDR(r), HWIO_SHADOW_STATUS_DRVr_HW_VERSION_RMSK)
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_INMI(r,mask)    \
        in_dword_masked(HWIO_SHADOW_STATUS_DRVr_HW_VERSION_ADDR(r), mask)
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_MAJOR_BMSK                                         0xff0000
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_MAJOR_SHFT                                             0x10
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_MINOR_BMSK                                           0xff00
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_MINOR_SHFT                                              0x8
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_STEP_BMSK                                              0xff
#define HWIO_SHADOW_STATUS_DRVr_HW_VERSION_STEP_SHFT                                               0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_ND_CFG
 *--------------------------------------------------------------------------*/

#define BCM_ND_CFG_REG_BASE                                             (AOSS_BASE      + 0x00be0000)
#define BCM_ND_CFG_REG_BASE_SIZE                                        0x3000
#define BCM_ND_CFG_REG_BASE_USED                                        0xcc4

#define HWIO_ND_CFG_NDd_ADDR(d)                                         (BCM_ND_CFG_REG_BASE      + 0x00000000 + 0x4 * (d))
#define HWIO_ND_CFG_NDd_RMSK                                                   0xf
#define HWIO_ND_CFG_NDd_MAXd                                                    31
#define HWIO_ND_CFG_NDd_INI(d)        \
        in_dword_masked(HWIO_ND_CFG_NDd_ADDR(d), HWIO_ND_CFG_NDd_RMSK)
#define HWIO_ND_CFG_NDd_INMI(d,mask)    \
        in_dword_masked(HWIO_ND_CFG_NDd_ADDR(d), mask)
#define HWIO_ND_CFG_NDd_OUTI(d,val)    \
        out_dword(HWIO_ND_CFG_NDd_ADDR(d),val)
#define HWIO_ND_CFG_NDd_OUTMI(d,mask,val) \
        out_dword_masked_ns(HWIO_ND_CFG_NDd_ADDR(d),mask,val,HWIO_ND_CFG_NDd_INI(d))
#define HWIO_ND_CFG_NDd_CLOCK_DOMAIN_ID_BMSK                                   0xf
#define HWIO_ND_CFG_NDd_CLOCK_DOMAIN_ID_SHFT                                   0x0

#define HWIO_ND_CFG_NDd_SCALARef_ADDR(d,ef)                             (BCM_ND_CFG_REG_BASE      + 0x00000200 + 0x8 * (d) + 0x4 * (ef))
#define HWIO_ND_CFG_NDd_SCALARef_RMSK                                        0xfff
#define HWIO_ND_CFG_NDd_SCALARef_MAXd                                           31
#define HWIO_ND_CFG_NDd_SCALARef_MAXef                                           1
#define HWIO_ND_CFG_NDd_SCALARef_INI2(d,ef)        \
        in_dword_masked(HWIO_ND_CFG_NDd_SCALARef_ADDR(d,ef), HWIO_ND_CFG_NDd_SCALARef_RMSK)
#define HWIO_ND_CFG_NDd_SCALARef_INMI2(d,ef,mask)    \
        in_dword_masked(HWIO_ND_CFG_NDd_SCALARef_ADDR(d,ef), mask)
#define HWIO_ND_CFG_NDd_SCALARef_OUTI2(d,ef,val)    \
        out_dword(HWIO_ND_CFG_NDd_SCALARef_ADDR(d,ef),val)
#define HWIO_ND_CFG_NDd_SCALARef_OUTMI2(d,ef,mask,val) \
        out_dword_masked_ns(HWIO_ND_CFG_NDd_SCALARef_ADDR(d,ef),mask,val,HWIO_ND_CFG_NDd_SCALARef_INI2(d,ef))
#define HWIO_ND_CFG_NDd_SCALARef_VAL_BMSK                                    0xfff
#define HWIO_ND_CFG_NDd_SCALARef_VAL_SHFT                                      0x0

#define HWIO_SCALAR_FORMAT_ADDR                                         (BCM_ND_CFG_REG_BASE      + 0x00000400)
#define HWIO_SCALAR_FORMAT_RMSK                                                0xf
#define HWIO_SCALAR_FORMAT_IN          \
        in_dword(HWIO_SCALAR_FORMAT_ADDR)
#define HWIO_SCALAR_FORMAT_INM(m)      \
        in_dword_masked(HWIO_SCALAR_FORMAT_ADDR, m)
#define HWIO_SCALAR_FORMAT_OUT(v)      \
        out_dword(HWIO_SCALAR_FORMAT_ADDR,v)
#define HWIO_SCALAR_FORMAT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SCALAR_FORMAT_ADDR,m,v,HWIO_SCALAR_FORMAT_IN)
#define HWIO_SCALAR_FORMAT_FRACTION_BMSK                                       0xf
#define HWIO_SCALAR_FORMAT_FRACTION_SHFT                                       0x0

#define HWIO_SND_CFG_SNDs_ADDR(s)                                       (BCM_ND_CFG_REG_BASE      + 0x00000404 + 0x4 * (s))
#define HWIO_SND_CFG_SNDs_RMSK                                                 0x1
#define HWIO_SND_CFG_SNDs_MAXs                                                   4
#define HWIO_SND_CFG_SNDs_INI(s)        \
        in_dword_masked(HWIO_SND_CFG_SNDs_ADDR(s), HWIO_SND_CFG_SNDs_RMSK)
#define HWIO_SND_CFG_SNDs_INMI(s,mask)    \
        in_dword_masked(HWIO_SND_CFG_SNDs_ADDR(s), mask)
#define HWIO_SND_CFG_SNDs_OUTI(s,val)    \
        out_dword(HWIO_SND_CFG_SNDs_ADDR(s),val)
#define HWIO_SND_CFG_SNDs_OUTMI(s,mask,val) \
        out_dword_masked_ns(HWIO_SND_CFG_SNDs_ADDR(s),mask,val,HWIO_SND_CFG_SNDs_INI(s))
#define HWIO_SND_CFG_SNDs_Z_ND_ASSOCIATION_BMSK                                0x1
#define HWIO_SND_CFG_SNDs_Z_ND_ASSOCIATION_SHFT                                0x0

#define HWIO_SND_LUT_SNDs_COLc_ADDR(s,c)                                (BCM_ND_CFG_REG_BASE      + 0x00000504 + 0x10 * (s) + 0x4 * (c))
#define HWIO_SND_LUT_SNDs_COLc_RMSK                                         0x3fff
#define HWIO_SND_LUT_SNDs_COLc_MAXs                                              4
#define HWIO_SND_LUT_SNDs_COLc_MAXc                                              3
#define HWIO_SND_LUT_SNDs_COLc_INI2(s,c)        \
        in_dword_masked(HWIO_SND_LUT_SNDs_COLc_ADDR(s,c), HWIO_SND_LUT_SNDs_COLc_RMSK)
#define HWIO_SND_LUT_SNDs_COLc_INMI2(s,c,mask)    \
        in_dword_masked(HWIO_SND_LUT_SNDs_COLc_ADDR(s,c), mask)
#define HWIO_SND_LUT_SNDs_COLc_OUTI2(s,c,val)    \
        out_dword(HWIO_SND_LUT_SNDs_COLc_ADDR(s,c),val)
#define HWIO_SND_LUT_SNDs_COLc_OUTMI2(s,c,mask,val) \
        out_dword_masked_ns(HWIO_SND_LUT_SNDs_COLc_ADDR(s,c),mask,val,HWIO_SND_LUT_SNDs_COLc_INI2(s,c))
#define HWIO_SND_LUT_SNDs_COLc_COL_THRESHOLD_BMSK                           0x3fff
#define HWIO_SND_LUT_SNDs_COLc_COL_THRESHOLD_SHFT                              0x0

#define HWIO_SND_LUT_SND0_COLc_CPn_ADDR(c,n)                            (BCM_ND_CFG_REG_BASE      + 0x00000704 + 0x40 * (c) + 0x4 * (n))
#define HWIO_SND_LUT_SND0_COLc_CPn_RMSK                                     0x3fff
#define HWIO_SND_LUT_SND0_COLc_CPn_MAXc                                          3
#define HWIO_SND_LUT_SND0_COLc_CPn_MAXn                                         15
#define HWIO_SND_LUT_SND0_COLc_CPn_INI2(c,n)        \
        in_dword_masked(HWIO_SND_LUT_SND0_COLc_CPn_ADDR(c,n), HWIO_SND_LUT_SND0_COLc_CPn_RMSK)
#define HWIO_SND_LUT_SND0_COLc_CPn_INMI2(c,n,mask)    \
        in_dword_masked(HWIO_SND_LUT_SND0_COLc_CPn_ADDR(c,n), mask)
#define HWIO_SND_LUT_SND0_COLc_CPn_OUTI2(c,n,val)    \
        out_dword(HWIO_SND_LUT_SND0_COLc_CPn_ADDR(c,n),val)
#define HWIO_SND_LUT_SND0_COLc_CPn_OUTMI2(c,n,mask,val) \
        out_dword_masked_ns(HWIO_SND_LUT_SND0_COLc_CPn_ADDR(c,n),mask,val,HWIO_SND_LUT_SND0_COLc_CPn_INI2(c,n))
#define HWIO_SND_LUT_SND0_COLc_CPn_ROW_THRESHOLD_BMSK                       0x3fff
#define HWIO_SND_LUT_SND0_COLc_CPn_ROW_THRESHOLD_SHFT                          0x0

#define HWIO_SND_LUT_SND1_COLc_CPn_ADDR(c,n)                            (BCM_ND_CFG_REG_BASE      + 0x00000804 + 0x40 * (c) + 0x4 * (n))
#define HWIO_SND_LUT_SND1_COLc_CPn_RMSK                                     0x3fff
#define HWIO_SND_LUT_SND1_COLc_CPn_MAXc                                          3
#define HWIO_SND_LUT_SND1_COLc_CPn_MAXn                                          7
#define HWIO_SND_LUT_SND1_COLc_CPn_INI2(c,n)        \
        in_dword_masked(HWIO_SND_LUT_SND1_COLc_CPn_ADDR(c,n), HWIO_SND_LUT_SND1_COLc_CPn_RMSK)
#define HWIO_SND_LUT_SND1_COLc_CPn_INMI2(c,n,mask)    \
        in_dword_masked(HWIO_SND_LUT_SND1_COLc_CPn_ADDR(c,n), mask)
#define HWIO_SND_LUT_SND1_COLc_CPn_OUTI2(c,n,val)    \
        out_dword(HWIO_SND_LUT_SND1_COLc_CPn_ADDR(c,n),val)
#define HWIO_SND_LUT_SND1_COLc_CPn_OUTMI2(c,n,mask,val) \
        out_dword_masked_ns(HWIO_SND_LUT_SND1_COLc_CPn_ADDR(c,n),mask,val,HWIO_SND_LUT_SND1_COLc_CPn_INI2(c,n))
#define HWIO_SND_LUT_SND1_COLc_CPn_ROW_THRESHOLD_BMSK                       0x3fff
#define HWIO_SND_LUT_SND1_COLc_CPn_ROW_THRESHOLD_SHFT                          0x0

#define HWIO_SND_LUT_SND2_COLc_CPn_ADDR(c,n)                            (BCM_ND_CFG_REG_BASE      + 0x00000904 + 0x40 * (c) + 0x4 * (n))
#define HWIO_SND_LUT_SND2_COLc_CPn_RMSK                                     0x3fff
#define HWIO_SND_LUT_SND2_COLc_CPn_MAXc                                          3
#define HWIO_SND_LUT_SND2_COLc_CPn_MAXn                                         15
#define HWIO_SND_LUT_SND2_COLc_CPn_INI2(c,n)        \
        in_dword_masked(HWIO_SND_LUT_SND2_COLc_CPn_ADDR(c,n), HWIO_SND_LUT_SND2_COLc_CPn_RMSK)
#define HWIO_SND_LUT_SND2_COLc_CPn_INMI2(c,n,mask)    \
        in_dword_masked(HWIO_SND_LUT_SND2_COLc_CPn_ADDR(c,n), mask)
#define HWIO_SND_LUT_SND2_COLc_CPn_OUTI2(c,n,val)    \
        out_dword(HWIO_SND_LUT_SND2_COLc_CPn_ADDR(c,n),val)
#define HWIO_SND_LUT_SND2_COLc_CPn_OUTMI2(c,n,mask,val) \
        out_dword_masked_ns(HWIO_SND_LUT_SND2_COLc_CPn_ADDR(c,n),mask,val,HWIO_SND_LUT_SND2_COLc_CPn_INI2(c,n))
#define HWIO_SND_LUT_SND2_COLc_CPn_ROW_THRESHOLD_BMSK                       0x3fff
#define HWIO_SND_LUT_SND2_COLc_CPn_ROW_THRESHOLD_SHFT                          0x0

#define HWIO_SND_LUT_SND3_COLc_CPn_ADDR(c,n)                            (BCM_ND_CFG_REG_BASE      + 0x00000a04 + 0x40 * (c) + 0x4 * (n))
#define HWIO_SND_LUT_SND3_COLc_CPn_RMSK                                     0x3fff
#define HWIO_SND_LUT_SND3_COLc_CPn_MAXc                                          3
#define HWIO_SND_LUT_SND3_COLc_CPn_MAXn                                          7
#define HWIO_SND_LUT_SND3_COLc_CPn_INI2(c,n)        \
        in_dword_masked(HWIO_SND_LUT_SND3_COLc_CPn_ADDR(c,n), HWIO_SND_LUT_SND3_COLc_CPn_RMSK)
#define HWIO_SND_LUT_SND3_COLc_CPn_INMI2(c,n,mask)    \
        in_dword_masked(HWIO_SND_LUT_SND3_COLc_CPn_ADDR(c,n), mask)
#define HWIO_SND_LUT_SND3_COLc_CPn_OUTI2(c,n,val)    \
        out_dword(HWIO_SND_LUT_SND3_COLc_CPn_ADDR(c,n),val)
#define HWIO_SND_LUT_SND3_COLc_CPn_OUTMI2(c,n,mask,val) \
        out_dword_masked_ns(HWIO_SND_LUT_SND3_COLc_CPn_ADDR(c,n),mask,val,HWIO_SND_LUT_SND3_COLc_CPn_INI2(c,n))
#define HWIO_SND_LUT_SND3_COLc_CPn_ROW_THRESHOLD_BMSK                       0x3fff
#define HWIO_SND_LUT_SND3_COLc_CPn_ROW_THRESHOLD_SHFT                          0x0

#define HWIO_SND_LUT_SND4_COLc_CPn_ADDR(c,n)                            (BCM_ND_CFG_REG_BASE      + 0x00000b04 + 0x40 * (c) + 0x4 * (n))
#define HWIO_SND_LUT_SND4_COLc_CPn_RMSK                                     0x3fff
#define HWIO_SND_LUT_SND4_COLc_CPn_MAXc                                          3
#define HWIO_SND_LUT_SND4_COLc_CPn_MAXn                                         15
#define HWIO_SND_LUT_SND4_COLc_CPn_INI2(c,n)        \
        in_dword_masked(HWIO_SND_LUT_SND4_COLc_CPn_ADDR(c,n), HWIO_SND_LUT_SND4_COLc_CPn_RMSK)
#define HWIO_SND_LUT_SND4_COLc_CPn_INMI2(c,n,mask)    \
        in_dword_masked(HWIO_SND_LUT_SND4_COLc_CPn_ADDR(c,n), mask)
#define HWIO_SND_LUT_SND4_COLc_CPn_OUTI2(c,n,val)    \
        out_dword(HWIO_SND_LUT_SND4_COLc_CPn_ADDR(c,n),val)
#define HWIO_SND_LUT_SND4_COLc_CPn_OUTMI2(c,n,mask,val) \
        out_dword_masked_ns(HWIO_SND_LUT_SND4_COLc_CPn_ADDR(c,n),mask,val,HWIO_SND_LUT_SND4_COLc_CPn_INI2(c,n))
#define HWIO_SND_LUT_SND4_COLc_CPn_ROW_THRESHOLD_BMSK                       0x3fff
#define HWIO_SND_LUT_SND4_COLc_CPn_ROW_THRESHOLD_SHFT                          0x0

#define HWIO_SND_LUT_SND5_COLc_CPn_ADDR(c,n)                            (BCM_ND_CFG_REG_BASE      + 0x00000c04 + 0x40 * (c) + 0x4 * (n))
#define HWIO_SND_LUT_SND5_COLc_CPn_RMSK                                     0x3fff
#define HWIO_SND_LUT_SND5_COLc_CPn_MAXc                                          3
#define HWIO_SND_LUT_SND5_COLc_CPn_MAXn                                          0
#define HWIO_SND_LUT_SND5_COLc_CPn_INI2(c,n)        \
        in_dword_masked(HWIO_SND_LUT_SND5_COLc_CPn_ADDR(c,n), HWIO_SND_LUT_SND5_COLc_CPn_RMSK)
#define HWIO_SND_LUT_SND5_COLc_CPn_INMI2(c,n,mask)    \
        in_dword_masked(HWIO_SND_LUT_SND5_COLc_CPn_ADDR(c,n), mask)
#define HWIO_SND_LUT_SND5_COLc_CPn_OUTI2(c,n,val)    \
        out_dword(HWIO_SND_LUT_SND5_COLc_CPn_ADDR(c,n),val)
#define HWIO_SND_LUT_SND5_COLc_CPn_OUTMI2(c,n,mask,val) \
        out_dword_masked_ns(HWIO_SND_LUT_SND5_COLc_CPn_ADDR(c,n),mask,val,HWIO_SND_LUT_SND5_COLc_CPn_INI2(c,n))
#define HWIO_SND_LUT_SND5_COLc_CPn_ROW_THRESHOLD_BMSK                       0x3fff
#define HWIO_SND_LUT_SND5_COLc_CPn_ROW_THRESHOLD_SHFT                          0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_CD_CFG
 *--------------------------------------------------------------------------*/

#define BCM_CD_CFG_REG_BASE                                     (AOSS_BASE      + 0x00be3000)
#define BCM_CD_CFG_REG_BASE_SIZE                                0x1000
#define BCM_CD_CFG_REG_BASE_USED                                0xbc0

#define HWIO_CD_CFG_CDm_ADDR(m)                                 (BCM_CD_CFG_REG_BASE      + 0x00000000 + 0x4 * (m))
#define HWIO_CD_CFG_CDm_RMSK                                       0xf0f00
#define HWIO_CD_CFG_CDm_MAXm                                            12
#define HWIO_CD_CFG_CDm_INI(m)        \
        in_dword_masked(HWIO_CD_CFG_CDm_ADDR(m), HWIO_CD_CFG_CDm_RMSK)
#define HWIO_CD_CFG_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_CD_CFG_CDm_ADDR(m), mask)
#define HWIO_CD_CFG_CDm_OUTI(m,val)    \
        out_dword(HWIO_CD_CFG_CDm_ADDR(m),val)
#define HWIO_CD_CFG_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_CD_CFG_CDm_ADDR(m),mask,val,HWIO_CD_CFG_CDm_INI(m))
#define HWIO_CD_CFG_CDm_PC_TH_BMSK                                 0xf0000
#define HWIO_CD_CFG_CDm_PC_TH_SHFT                                    0x10
#define HWIO_CD_CFG_CDm_DEPENDENT_CD_ID_BMSK                         0xf00
#define HWIO_CD_CFG_CDm_DEPENDENT_CD_ID_SHFT                           0x8

#define HWIO_CD_CFG_ENABLE_CDm_ADDR(m)                          (BCM_CD_CFG_REG_BASE      + 0x00000080 + 0x4 * (m))
#define HWIO_CD_CFG_ENABLE_CDm_RMSK                                    0x1
#define HWIO_CD_CFG_ENABLE_CDm_MAXm                                     12
#define HWIO_CD_CFG_ENABLE_CDm_INI(m)        \
        in_dword_masked(HWIO_CD_CFG_ENABLE_CDm_ADDR(m), HWIO_CD_CFG_ENABLE_CDm_RMSK)
#define HWIO_CD_CFG_ENABLE_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_CD_CFG_ENABLE_CDm_ADDR(m), mask)
#define HWIO_CD_CFG_ENABLE_CDm_OUTI(m,val)    \
        out_dword(HWIO_CD_CFG_ENABLE_CDm_ADDR(m),val)
#define HWIO_CD_CFG_ENABLE_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_CD_CFG_ENABLE_CDm_ADDR(m),mask,val,HWIO_CD_CFG_ENABLE_CDm_INI(m))
#define HWIO_CD_CFG_ENABLE_CDm_SW_ENABLE_BMSK                          0x1
#define HWIO_CD_CFG_ENABLE_CDm_SW_ENABLE_SHFT                          0x0

#define HWIO_CD_TH_CD0_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x00000800 + 0x4 * (n))
#define HWIO_CD_TH_CD0_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD0_CPn_MAXn                                         15
#define HWIO_CD_TH_CD0_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD0_CPn_ADDR(n), HWIO_CD_TH_CD0_CPn_RMSK)
#define HWIO_CD_TH_CD0_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD0_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD0_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD0_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD0_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD0_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD0_CPn_INI(n))
#define HWIO_CD_TH_CD0_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD0_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CDm_CPn_ADDR(m,n)                            (BCM_CD_CFG_REG_BASE      + 0x00000800 + 0x4 * (n) + 0x40 * (m))
#define HWIO_CD_TH_CDm_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CDm_CPn_MAXm                                         15
#define HWIO_CD_TH_CDm_CPn_MAXn                                         15
#define HWIO_CD_TH_CDm_CPn_INI2(m,n)        \
        in_dword_masked(HWIO_CD_TH_CDm_CPn_ADDR(m,n), HWIO_CD_TH_CDm_CPn_RMSK)
#define HWIO_CD_TH_CDm_CPn_INMI2(m,n,mask)    \
        in_dword_masked(HWIO_CD_TH_CDm_CPn_ADDR(m,n), mask)
#define HWIO_CD_TH_CDm_CPn_OUTI2(m,n,val)    \
        out_dword(HWIO_CD_TH_CDm_CPn_ADDR(m,n),val)
#define HWIO_CD_TH_CDm_CPn_OUTMI2(m,n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CDm_CPn_ADDR(m,n),mask,val,HWIO_CD_TH_CDm_CPn_INI2(m,n))
#define HWIO_CD_TH_CDm_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CDm_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD1_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x00000840 + 0x4 * (n))
#define HWIO_CD_TH_CD1_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD1_CPn_MAXn                                          7
#define HWIO_CD_TH_CD1_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD1_CPn_ADDR(n), HWIO_CD_TH_CD1_CPn_RMSK)
#define HWIO_CD_TH_CD1_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD1_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD1_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD1_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD1_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD1_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD1_CPn_INI(n))
#define HWIO_CD_TH_CD1_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD1_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD2_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x00000880 + 0x4 * (n))
#define HWIO_CD_TH_CD2_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD2_CPn_MAXn                                          7
#define HWIO_CD_TH_CD2_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD2_CPn_ADDR(n), HWIO_CD_TH_CD2_CPn_RMSK)
#define HWIO_CD_TH_CD2_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD2_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD2_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD2_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD2_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD2_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD2_CPn_INI(n))
#define HWIO_CD_TH_CD2_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD2_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD3_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x000008c0 + 0x4 * (n))
#define HWIO_CD_TH_CD3_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD3_CPn_MAXn                                          7
#define HWIO_CD_TH_CD3_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD3_CPn_ADDR(n), HWIO_CD_TH_CD3_CPn_RMSK)
#define HWIO_CD_TH_CD3_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD3_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD3_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD3_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD3_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD3_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD3_CPn_INI(n))
#define HWIO_CD_TH_CD3_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD3_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD4_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x00000900 + 0x4 * (n))
#define HWIO_CD_TH_CD4_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD4_CPn_MAXn                                          7
#define HWIO_CD_TH_CD4_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD4_CPn_ADDR(n), HWIO_CD_TH_CD4_CPn_RMSK)
#define HWIO_CD_TH_CD4_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD4_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD4_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD4_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD4_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD4_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD4_CPn_INI(n))
#define HWIO_CD_TH_CD4_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD4_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD5_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x00000940 + 0x4 * (n))
#define HWIO_CD_TH_CD5_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD5_CPn_MAXn                                          7
#define HWIO_CD_TH_CD5_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD5_CPn_ADDR(n), HWIO_CD_TH_CD5_CPn_RMSK)
#define HWIO_CD_TH_CD5_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD5_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD5_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD5_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD5_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD5_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD5_CPn_INI(n))
#define HWIO_CD_TH_CD5_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD5_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD6_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x00000980 + 0x4 * (n))
#define HWIO_CD_TH_CD6_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD6_CPn_MAXn                                          7
#define HWIO_CD_TH_CD6_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD6_CPn_ADDR(n), HWIO_CD_TH_CD6_CPn_RMSK)
#define HWIO_CD_TH_CD6_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD6_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD6_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD6_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD6_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD6_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD6_CPn_INI(n))
#define HWIO_CD_TH_CD6_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD6_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD7_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x000009c0 + 0x4 * (n))
#define HWIO_CD_TH_CD7_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD7_CPn_MAXn                                          7
#define HWIO_CD_TH_CD7_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD7_CPn_ADDR(n), HWIO_CD_TH_CD7_CPn_RMSK)
#define HWIO_CD_TH_CD7_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD7_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD7_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD7_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD7_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD7_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD7_CPn_INI(n))
#define HWIO_CD_TH_CD7_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD7_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD8_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x00000a00 + 0x4 * (n))
#define HWIO_CD_TH_CD8_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD8_CPn_MAXn                                          7
#define HWIO_CD_TH_CD8_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD8_CPn_ADDR(n), HWIO_CD_TH_CD8_CPn_RMSK)
#define HWIO_CD_TH_CD8_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD8_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD8_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD8_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD8_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD8_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD8_CPn_INI(n))
#define HWIO_CD_TH_CD8_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD8_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD9_CPn_ADDR(n)                              (BCM_CD_CFG_REG_BASE      + 0x00000a40 + 0x4 * (n))
#define HWIO_CD_TH_CD9_CPn_RMSK                                     0x3fff
#define HWIO_CD_TH_CD9_CPn_MAXn                                          7
#define HWIO_CD_TH_CD9_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD9_CPn_ADDR(n), HWIO_CD_TH_CD9_CPn_RMSK)
#define HWIO_CD_TH_CD9_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD9_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD9_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD9_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD9_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD9_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD9_CPn_INI(n))
#define HWIO_CD_TH_CD9_CPn_BW_BMSK                                  0x3fff
#define HWIO_CD_TH_CD9_CPn_BW_SHFT                                     0x0

#define HWIO_CD_TH_CD10_CPn_ADDR(n)                             (BCM_CD_CFG_REG_BASE      + 0x00000a80 + 0x4 * (n))
#define HWIO_CD_TH_CD10_CPn_RMSK                                    0x3fff
#define HWIO_CD_TH_CD10_CPn_MAXn                                         7
#define HWIO_CD_TH_CD10_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD10_CPn_ADDR(n), HWIO_CD_TH_CD10_CPn_RMSK)
#define HWIO_CD_TH_CD10_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD10_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD10_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD10_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD10_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD10_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD10_CPn_INI(n))
#define HWIO_CD_TH_CD10_CPn_BW_BMSK                                 0x3fff
#define HWIO_CD_TH_CD10_CPn_BW_SHFT                                    0x0

#define HWIO_CD_TH_CD11_CPn_ADDR(n)                             (BCM_CD_CFG_REG_BASE      + 0x00000ac0 + 0x4 * (n))
#define HWIO_CD_TH_CD11_CPn_RMSK                                    0x3fff
#define HWIO_CD_TH_CD11_CPn_MAXn                                        15
#define HWIO_CD_TH_CD11_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD11_CPn_ADDR(n), HWIO_CD_TH_CD11_CPn_RMSK)
#define HWIO_CD_TH_CD11_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD11_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD11_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD11_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD11_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD11_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD11_CPn_INI(n))
#define HWIO_CD_TH_CD11_CPn_BW_BMSK                                 0x3fff
#define HWIO_CD_TH_CD11_CPn_BW_SHFT                                    0x0

#define HWIO_CD_TH_CD12_CPn_ADDR(n)                             (BCM_CD_CFG_REG_BASE      + 0x00000b00 + 0x4 * (n))
#define HWIO_CD_TH_CD12_CPn_RMSK                                    0x3fff
#define HWIO_CD_TH_CD12_CPn_MAXn                                        15
#define HWIO_CD_TH_CD12_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD12_CPn_ADDR(n), HWIO_CD_TH_CD12_CPn_RMSK)
#define HWIO_CD_TH_CD12_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD12_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD12_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD12_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD12_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD12_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD12_CPn_INI(n))
#define HWIO_CD_TH_CD12_CPn_BW_BMSK                                 0x3fff
#define HWIO_CD_TH_CD12_CPn_BW_SHFT                                    0x0

#define HWIO_CD_TH_CD13_CPn_ADDR(n)                             (BCM_CD_CFG_REG_BASE      + 0x00000b40 + 0x4 * (n))
#define HWIO_CD_TH_CD13_CPn_RMSK                                    0x3fff
#define HWIO_CD_TH_CD13_CPn_MAXn                                         0
#define HWIO_CD_TH_CD13_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD13_CPn_ADDR(n), HWIO_CD_TH_CD13_CPn_RMSK)
#define HWIO_CD_TH_CD13_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD13_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD13_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD13_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD13_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD13_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD13_CPn_INI(n))
#define HWIO_CD_TH_CD13_CPn_BW_BMSK                                 0x3fff
#define HWIO_CD_TH_CD13_CPn_BW_SHFT                                    0x0

#define HWIO_CD_TH_CD14_CPn_ADDR(n)                             (BCM_CD_CFG_REG_BASE      + 0x00000b80 + 0x4 * (n))
#define HWIO_CD_TH_CD14_CPn_RMSK                                    0x3fff
#define HWIO_CD_TH_CD14_CPn_MAXn                                         0
#define HWIO_CD_TH_CD14_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD14_CPn_ADDR(n), HWIO_CD_TH_CD14_CPn_RMSK)
#define HWIO_CD_TH_CD14_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD14_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD14_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD14_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD14_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD14_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD14_CPn_INI(n))
#define HWIO_CD_TH_CD14_CPn_BW_BMSK                                 0x3fff
#define HWIO_CD_TH_CD14_CPn_BW_SHFT                                    0x0

#define HWIO_CD_TH_CD15_CPn_ADDR(n)                             (BCM_CD_CFG_REG_BASE      + 0x00000bc0 + 0x4 * (n))
#define HWIO_CD_TH_CD15_CPn_RMSK                                    0x3fff
#define HWIO_CD_TH_CD15_CPn_MAXn                                         0
#define HWIO_CD_TH_CD15_CPn_INI(n)        \
        in_dword_masked(HWIO_CD_TH_CD15_CPn_ADDR(n), HWIO_CD_TH_CD15_CPn_RMSK)
#define HWIO_CD_TH_CD15_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_CD_TH_CD15_CPn_ADDR(n), mask)
#define HWIO_CD_TH_CD15_CPn_OUTI(n,val)    \
        out_dword(HWIO_CD_TH_CD15_CPn_ADDR(n),val)
#define HWIO_CD_TH_CD15_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_CD_TH_CD15_CPn_ADDR(n),mask,val,HWIO_CD_TH_CD15_CPn_INI(n))
#define HWIO_CD_TH_CD15_CPn_BW_BMSK                                 0x3fff
#define HWIO_CD_TH_CD15_CPn_BW_SHFT                                    0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_SEQ_CFG
 *--------------------------------------------------------------------------*/

#define BCM_SEQ_CFG_REG_BASE                                                 (AOSS_BASE      + 0x00be4000)
#define BCM_SEQ_CFG_REG_BASE_SIZE                                            0x1200
#define BCM_SEQ_CFG_REG_BASE_USED                                            0xb80

#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_ADDR(m)                               (BCM_SEQ_CFG_REG_BASE      + 0x00000080 + 0x4 * (m))
#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_RMSK                                       0x1ff
#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_MAXm                                          12
#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_INI(m)        \
        in_dword_masked(HWIO_SEQ_CFG_HW_START_ADDR_CDm_ADDR(m), HWIO_SEQ_CFG_HW_START_ADDR_CDm_RMSK)
#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SEQ_CFG_HW_START_ADDR_CDm_ADDR(m), mask)
#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_OUTI(m,val)    \
        out_dword(HWIO_SEQ_CFG_HW_START_ADDR_CDm_ADDR(m),val)
#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SEQ_CFG_HW_START_ADDR_CDm_ADDR(m),mask,val,HWIO_SEQ_CFG_HW_START_ADDR_CDm_INI(m))
#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_HW_START_ADDR_BMSK                         0x1ff
#define HWIO_SEQ_CFG_HW_START_ADDR_CDm_HW_START_ADDR_SHFT                           0x0

#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_ADDR(m)                               (BCM_SEQ_CFG_REG_BASE      + 0x00000100 + 0x4 * (m))
#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_RMSK                                       0x1ff
#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_MAXm                                          12
#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_INI(m)        \
        in_dword_masked(HWIO_SEQ_CFG_SW_START_ADDR_CDm_ADDR(m), HWIO_SEQ_CFG_SW_START_ADDR_CDm_RMSK)
#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SEQ_CFG_SW_START_ADDR_CDm_ADDR(m), mask)
#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_OUTI(m,val)    \
        out_dword(HWIO_SEQ_CFG_SW_START_ADDR_CDm_ADDR(m),val)
#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SEQ_CFG_SW_START_ADDR_CDm_ADDR(m),mask,val,HWIO_SEQ_CFG_SW_START_ADDR_CDm_INI(m))
#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_SW_START_ADDR_BMSK                         0x1ff
#define HWIO_SEQ_CFG_SW_START_ADDR_CDm_SW_START_ADDR_SHFT                           0x0

#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_ADDR(b)                                 (BCM_SEQ_CFG_REG_BASE      + 0x00000180 + 0x4 * (b))
#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_RMSK                                         0x1ff
#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_MAXb                                            31
#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_INI(b)        \
        in_dword_masked(HWIO_SEQ_CFG_BRANCH_ADDR_BRb_ADDR(b), HWIO_SEQ_CFG_BRANCH_ADDR_BRb_RMSK)
#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_INMI(b,mask)    \
        in_dword_masked(HWIO_SEQ_CFG_BRANCH_ADDR_BRb_ADDR(b), mask)
#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_OUTI(b,val)    \
        out_dword(HWIO_SEQ_CFG_BRANCH_ADDR_BRb_ADDR(b),val)
#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_OUTMI(b,mask,val) \
        out_dword_masked_ns(HWIO_SEQ_CFG_BRANCH_ADDR_BRb_ADDR(b),mask,val,HWIO_SEQ_CFG_BRANCH_ADDR_BRb_INI(b))
#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_BRANCH_ADDR_BMSK                             0x1ff
#define HWIO_SEQ_CFG_BRANCH_ADDR_BRb_BRANCH_ADDR_SHFT                               0x0

#define HWIO_SEQ_CFG_DELAY_DLYy_ADDR(y)                                      (BCM_SEQ_CFG_REG_BASE      + 0x00000980 + 0x4 * (y))
#define HWIO_SEQ_CFG_DELAY_DLYy_RMSK                                            0xfffff
#define HWIO_SEQ_CFG_DELAY_DLYy_MAXy                                                  3
#define HWIO_SEQ_CFG_DELAY_DLYy_INI(y)        \
        in_dword_masked(HWIO_SEQ_CFG_DELAY_DLYy_ADDR(y), HWIO_SEQ_CFG_DELAY_DLYy_RMSK)
#define HWIO_SEQ_CFG_DELAY_DLYy_INMI(y,mask)    \
        in_dword_masked(HWIO_SEQ_CFG_DELAY_DLYy_ADDR(y), mask)
#define HWIO_SEQ_CFG_DELAY_DLYy_OUTI(y,val)    \
        out_dword(HWIO_SEQ_CFG_DELAY_DLYy_ADDR(y),val)
#define HWIO_SEQ_CFG_DELAY_DLYy_OUTMI(y,mask,val) \
        out_dword_masked_ns(HWIO_SEQ_CFG_DELAY_DLYy_ADDR(y),mask,val,HWIO_SEQ_CFG_DELAY_DLYy_INI(y))
#define HWIO_SEQ_CFG_DELAY_DLYy_DELAY_VAL_BMSK                                  0xfffff
#define HWIO_SEQ_CFG_DELAY_DLYy_DELAY_VAL_SHFT                                      0x0

#define HWIO_SEQ_CFG_BR_EVENT_ADDR                                           (BCM_SEQ_CFG_REG_BASE      + 0x00000b80)
#define HWIO_SEQ_CFG_BR_EVENT_RMSK                                               0x1fff
#define HWIO_SEQ_CFG_BR_EVENT_IN          \
        in_dword(HWIO_SEQ_CFG_BR_EVENT_ADDR)
#define HWIO_SEQ_CFG_BR_EVENT_INM(m)      \
        in_dword_masked(HWIO_SEQ_CFG_BR_EVENT_ADDR, m)
#define HWIO_SEQ_CFG_BR_EVENT_OUT(v)      \
        out_dword(HWIO_SEQ_CFG_BR_EVENT_ADDR,v)
#define HWIO_SEQ_CFG_BR_EVENT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SEQ_CFG_BR_EVENT_ADDR,m,v,HWIO_SEQ_CFG_BR_EVENT_IN)
#define HWIO_SEQ_CFG_BR_EVENT_BR_EVENT_BIT_15_PER_VCD_BMSK                       0x1fff
#define HWIO_SEQ_CFG_BR_EVENT_BR_EVENT_BIT_15_PER_VCD_SHFT                          0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_TCS_CFG
 *--------------------------------------------------------------------------*/

#define BCM_TCS_CFG_REG_BASE                                                          (AOSS_BASE      + 0x00be5400)
#define BCM_TCS_CFG_REG_BASE_SIZE                                                     0x1400
#define BCM_TCS_CFG_REG_BASE_USED                                                     0xa80

#define HWIO_TCS_CFG_CDm_ADDR(m)                                                      (BCM_TCS_CFG_REG_BASE      + 0x00000000 + 0x4 * (m))
#define HWIO_TCS_CFG_CDm_RMSK                                                          0xf0f0f0f
#define HWIO_TCS_CFG_CDm_MAXm                                                                 12
#define HWIO_TCS_CFG_CDm_INI(m)        \
        in_dword_masked(HWIO_TCS_CFG_CDm_ADDR(m), HWIO_TCS_CFG_CDm_RMSK)
#define HWIO_TCS_CFG_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_TCS_CFG_CDm_ADDR(m), mask)
#define HWIO_TCS_CFG_CDm_OUTI(m,val)    \
        out_dword(HWIO_TCS_CFG_CDm_ADDR(m),val)
#define HWIO_TCS_CFG_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_CDm_ADDR(m),mask,val,HWIO_TCS_CFG_CDm_INI(m))
#define HWIO_TCS_CFG_CDm_TCS_CMD_WAIT_BMSK                                             0xf000000
#define HWIO_TCS_CFG_CDm_TCS_CMD_WAIT_SHFT                                                  0x18
#define HWIO_TCS_CFG_CDm_TCS_CMD_RR_CPUP_BMSK                                            0xf0000
#define HWIO_TCS_CFG_CDm_TCS_CMD_RR_CPUP_SHFT                                               0x10
#define HWIO_TCS_CFG_CDm_TCS_CMD_RR_CPDOWN_BMSK                                            0xf00
#define HWIO_TCS_CFG_CDm_TCS_CMD_RR_CPDOWN_SHFT                                              0x8
#define HWIO_TCS_CFG_CDm_TCS_CMD_EN_BMSK                                                     0xf
#define HWIO_TCS_CFG_CDm_TCS_CMD_EN_SHFT                                                     0x0

#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_ADDR(m,t)                                     (BCM_TCS_CFG_REG_BASE      + 0x00000080 + 0x10 * (m) + 0x4 * (t))
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_RMSK                                          0x80e0ffff
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_MAXm                                                  12
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_MAXt                                                   3
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_INI2(m,t)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_ADDR(m,t), HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_RMSK)
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_INMI2(m,t,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_ADDR(m,t), mask)
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_OUTI2(m,t,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_ADDR(m,t),val)
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_OUTMI2(m,t,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_ADDR(m,t),mask,val,HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_INI2(m,t))
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_IS_VRM_VOTE_BMSK                              0x80000000
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_IS_VRM_VOTE_SHFT                                    0x1f
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_SLV_ID_BMSK                                     0xe00000
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_SLV_ID_SHFT                                         0x15
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_BCM_CD_ID_FOR_ARC_VOTE_BMSK                       0xf000
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_BCM_CD_ID_FOR_ARC_VOTE_SHFT                          0xc
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_OFFSET_BMSK                                        0xfff
#define HWIO_TCS_CFG_VOTE_ADDR_CDm_CMDt_OFFSET_SHFT                                          0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x00000280 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_RMSK                                               0xffff
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_MAXn                                                   15
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_CMD3_DATA_BMSK                                     0xf000
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_CMD3_DATA_SHFT                                        0xc
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD0_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_ADDR(m,n)                                      (BCM_TCS_CFG_REG_BASE      + 0x00000280 + 0x4 * (n) + 0x40 * (m))
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_RMSK                                               0xffff
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_MAXm                                                   15
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_MAXn                                                   15
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_INI2(m,n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_ADDR(m,n), HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_INMI2(m,n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_ADDR(m,n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_OUTI2(m,n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_ADDR(m,n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_OUTMI2(m,n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_ADDR(m,n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_INI2(m,n))
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_CMD3_DATA_BMSK                                     0xf000
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_CMD3_DATA_SHFT                                        0xc
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CDm_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x000002c0 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_RMSK                                               0xffff
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_CMD3_DATA_BMSK                                     0xf000
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_CMD3_DATA_SHFT                                        0xc
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD1_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x00000300 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_RMSK                                               0xffff
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_CMD3_DATA_BMSK                                     0xf000
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_CMD3_DATA_SHFT                                        0xc
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD2_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x00000340 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_RMSK                                               0xffff
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_CMD3_DATA_BMSK                                     0xf000
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_CMD3_DATA_SHFT                                        0xc
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD3_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x00000380 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_RMSK                                               0xffff
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_CMD3_DATA_BMSK                                     0xf000
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_CMD3_DATA_SHFT                                        0xc
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD4_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x000003c0 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_RMSK                                               0xffff
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_CMD3_DATA_BMSK                                     0xf000
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_CMD3_DATA_SHFT                                        0xc
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD5_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x00000400 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_RMSK                                               0xffff
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_CMD3_DATA_BMSK                                     0xf000
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_CMD3_DATA_SHFT                                        0xc
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD6_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x00000440 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_RMSK                                               0xffff
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_CMD3_DATA_BMSK                                     0xf000
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_CMD3_DATA_SHFT                                        0xc
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD7_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x00000480 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_RMSK                                               0xffff
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_CMD3_DATA_BMSK                                     0xf000
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_CMD3_DATA_SHFT                                        0xc
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD8_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_ADDR(n)                                        (BCM_TCS_CFG_REG_BASE      + 0x000004c0 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_RMSK                                               0xffff
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_MAXn                                                    7
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_CMD3_DATA_BMSK                                     0xf000
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_CMD3_DATA_SHFT                                        0xc
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_CMD2_DATA_BMSK                                      0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_CMD2_DATA_SHFT                                        0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_CMD1_DATA_BMSK                                       0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_CMD1_DATA_SHFT                                        0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_CMD0_DATA_BMSK                                        0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD9_CPn_CMD0_DATA_SHFT                                        0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_ADDR(n)                                       (BCM_TCS_CFG_REG_BASE      + 0x00000500 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_RMSK                                              0xffff
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_MAXn                                                   7
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_CMD3_DATA_BMSK                                    0xf000
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_CMD3_DATA_SHFT                                       0xc
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_CMD2_DATA_BMSK                                     0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_CMD2_DATA_SHFT                                       0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_CMD1_DATA_BMSK                                      0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_CMD1_DATA_SHFT                                       0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_CMD0_DATA_BMSK                                       0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD10_CPn_CMD0_DATA_SHFT                                       0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_ADDR(n)                                       (BCM_TCS_CFG_REG_BASE      + 0x00000540 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_RMSK                                              0xffff
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_MAXn                                                  15
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_CMD3_DATA_BMSK                                    0xf000
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_CMD3_DATA_SHFT                                       0xc
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_CMD2_DATA_BMSK                                     0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_CMD2_DATA_SHFT                                       0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_CMD1_DATA_BMSK                                      0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_CMD1_DATA_SHFT                                       0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_CMD0_DATA_BMSK                                       0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD11_CPn_CMD0_DATA_SHFT                                       0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_ADDR(n)                                       (BCM_TCS_CFG_REG_BASE      + 0x00000580 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_RMSK                                              0xffff
#define HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_MAXn                                                  15
#define HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_CMD3_DATA_BMSK                                    0xf000
#define HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_CMD3_DATA_SHFT                                       0xc
#define HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_CMD2_DATA_BMSK                                     0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_CMD2_DATA_SHFT                                       0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_CMD1_DATA_BMSK                                      0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_CMD1_DATA_SHFT                                       0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_CMD0_DATA_BMSK                                       0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD12_CPn_CMD0_DATA_SHFT                                       0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_ADDR(n)                                       (BCM_TCS_CFG_REG_BASE      + 0x000005c0 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_RMSK                                              0xffff
#define HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_MAXn                                                   0
#define HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_CMD3_DATA_BMSK                                    0xf000
#define HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_CMD3_DATA_SHFT                                       0xc
#define HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_CMD2_DATA_BMSK                                     0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_CMD2_DATA_SHFT                                       0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_CMD1_DATA_BMSK                                      0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_CMD1_DATA_SHFT                                       0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_CMD0_DATA_BMSK                                       0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD13_CPn_CMD0_DATA_SHFT                                       0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_ADDR(n)                                       (BCM_TCS_CFG_REG_BASE      + 0x00000600 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_RMSK                                              0xffff
#define HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_MAXn                                                   0
#define HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_CMD3_DATA_BMSK                                    0xf000
#define HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_CMD3_DATA_SHFT                                       0xc
#define HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_CMD2_DATA_BMSK                                     0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_CMD2_DATA_SHFT                                       0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_CMD1_DATA_BMSK                                      0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_CMD1_DATA_SHFT                                       0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_CMD0_DATA_BMSK                                       0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD14_CPn_CMD0_DATA_SHFT                                       0x0

#define HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_ADDR(n)                                       (BCM_TCS_CFG_REG_BASE      + 0x00000640 + 0x4 * (n))
#define HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_RMSK                                              0xffff
#define HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_MAXn                                                   0
#define HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_INI(n)        \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_ADDR(n), HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_RMSK)
#define HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_ADDR(n), mask)
#define HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_OUTI(n,val)    \
        out_dword(HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_ADDR(n),val)
#define HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_ADDR(n),mask,val,HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_INI(n))
#define HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_CMD3_DATA_BMSK                                    0xf000
#define HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_CMD3_DATA_SHFT                                       0xc
#define HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_CMD2_DATA_BMSK                                     0xf00
#define HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_CMD2_DATA_SHFT                                       0x8
#define HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_CMD1_DATA_BMSK                                      0xf0
#define HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_CMD1_DATA_SHFT                                       0x4
#define HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_CMD0_DATA_BMSK                                       0xf
#define HWIO_TCS_CFG_VOTE_DATA_CD15_CPn_CMD0_DATA_SHFT                                       0x0

#define HWIO_TCS_VOTE_RESP_BACK_ADDR                                                  (BCM_TCS_CFG_REG_BASE      + 0x00000a80)
#define HWIO_TCS_VOTE_RESP_BACK_RMSK                                                  0xffffffff
#define HWIO_TCS_VOTE_RESP_BACK_IN          \
        in_dword(HWIO_TCS_VOTE_RESP_BACK_ADDR)
#define HWIO_TCS_VOTE_RESP_BACK_INM(m)      \
        in_dword_masked(HWIO_TCS_VOTE_RESP_BACK_ADDR, m)
#define HWIO_TCS_VOTE_RESP_BACK_OUT(v)      \
        out_dword(HWIO_TCS_VOTE_RESP_BACK_ADDR,v)
#define HWIO_TCS_VOTE_RESP_BACK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TCS_VOTE_RESP_BACK_ADDR,m,v,HWIO_TCS_VOTE_RESP_BACK_IN)
#define HWIO_TCS_VOTE_RESP_BACK_VOTE_RESP_BMSK                                        0xffffffff
#define HWIO_TCS_VOTE_RESP_BACK_VOTE_RESP_SHFT                                               0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_CFG
 *--------------------------------------------------------------------------*/

#define BCM_CFG_REG_BASE                                               (AOSS_BASE      + 0x00be7000)
#define BCM_CFG_REG_BASE_SIZE                                          0x200
#define BCM_CFG_REG_BASE_USED                                          0x110

#define HWIO_BCM_CFG_BCM_EN_ADDR                                       (BCM_CFG_REG_BASE      + 0x00000000)
#define HWIO_BCM_CFG_BCM_EN_RMSK                                              0x1
#define HWIO_BCM_CFG_BCM_EN_IN          \
        in_dword(HWIO_BCM_CFG_BCM_EN_ADDR)
#define HWIO_BCM_CFG_BCM_EN_INM(m)      \
        in_dword_masked(HWIO_BCM_CFG_BCM_EN_ADDR, m)
#define HWIO_BCM_CFG_BCM_EN_OUT(v)      \
        out_dword(HWIO_BCM_CFG_BCM_EN_ADDR,v)
#define HWIO_BCM_CFG_BCM_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BCM_CFG_BCM_EN_ADDR,m,v,HWIO_BCM_CFG_BCM_EN_IN)
#define HWIO_BCM_CFG_BCM_EN_BCM_EN_BMSK                                       0x1
#define HWIO_BCM_CFG_BCM_EN_BCM_EN_SHFT                                       0x0

#define HWIO_BCM_CFG_SLV_ID_FOR_RESP_ADDR                              (BCM_CFG_REG_BASE      + 0x00000004)
#define HWIO_BCM_CFG_SLV_ID_FOR_RESP_RMSK                                     0x7
#define HWIO_BCM_CFG_SLV_ID_FOR_RESP_IN          \
        in_dword(HWIO_BCM_CFG_SLV_ID_FOR_RESP_ADDR)
#define HWIO_BCM_CFG_SLV_ID_FOR_RESP_INM(m)      \
        in_dword_masked(HWIO_BCM_CFG_SLV_ID_FOR_RESP_ADDR, m)
#define HWIO_BCM_CFG_SLV_ID_FOR_RESP_OUT(v)      \
        out_dword(HWIO_BCM_CFG_SLV_ID_FOR_RESP_ADDR,v)
#define HWIO_BCM_CFG_SLV_ID_FOR_RESP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BCM_CFG_SLV_ID_FOR_RESP_ADDR,m,v,HWIO_BCM_CFG_SLV_ID_FOR_RESP_IN)
#define HWIO_BCM_CFG_SLV_ID_FOR_RESP_SLV_ID_BMSK                              0x7
#define HWIO_BCM_CFG_SLV_ID_FOR_RESP_SLV_ID_SHFT                              0x0

#define HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_ADDR                          (BCM_CFG_REG_BASE      + 0x00000008)
#define HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_RMSK                                0x1f
#define HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_IN          \
        in_dword(HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_ADDR)
#define HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_INM(m)      \
        in_dword_masked(HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_ADDR, m)
#define HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_OUT(v)      \
        out_dword(HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_ADDR,v)
#define HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_ADDR,m,v,HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_IN)
#define HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_DRV_ID_BMSK                         0x1f
#define HWIO_BCM_CFG_DRV_ID_FOR_ARC_VOTE_DRV_ID_SHFT                          0x0

#define HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_ADDR                          (BCM_CFG_REG_BASE      + 0x00000088)
#define HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_RMSK                                0x1f
#define HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_IN          \
        in_dword(HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_ADDR)
#define HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_INM(m)      \
        in_dword_masked(HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_ADDR, m)
#define HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_OUT(v)      \
        out_dword(HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_ADDR,v)
#define HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_ADDR,m,v,HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_IN)
#define HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_DRV_ID_BMSK                         0x1f
#define HWIO_BCM_CFG_DRV_ID_FOR_VRM_VOTE_DRV_ID_SHFT                          0x0

#define HWIO_BCM_CFG_DRVr_ADDR(r)                                      (BCM_CFG_REG_BASE      + 0x0000008c + 0x4 * (r))
#define HWIO_BCM_CFG_DRVr_RMSK                                           0xffffff
#define HWIO_BCM_CFG_DRVr_MAXr                                                 23
#define HWIO_BCM_CFG_DRVr_INI(r)        \
        in_dword_masked(HWIO_BCM_CFG_DRVr_ADDR(r), HWIO_BCM_CFG_DRVr_RMSK)
#define HWIO_BCM_CFG_DRVr_INMI(r,mask)    \
        in_dword_masked(HWIO_BCM_CFG_DRVr_ADDR(r), mask)
#define HWIO_BCM_CFG_DRVr_OUTI(r,val)    \
        out_dword(HWIO_BCM_CFG_DRVr_ADDR(r),val)
#define HWIO_BCM_CFG_DRVr_OUTMI(r,mask,val) \
        out_dword_masked_ns(HWIO_BCM_CFG_DRVr_ADDR(r),mask,val,HWIO_BCM_CFG_DRVr_INI(r))
#define HWIO_BCM_CFG_DRVr_RESP_ADDR_BMSK                                 0xffffff
#define HWIO_BCM_CFG_DRVr_RESP_ADDR_SHFT                                      0x0

#define HWIO_BCM_CFG_DEBUG_BUS_ADDR                                    (BCM_CFG_REG_BASE      + 0x0000010c)
#define HWIO_BCM_CFG_DEBUG_BUS_RMSK                                         0x10f
#define HWIO_BCM_CFG_DEBUG_BUS_IN          \
        in_dword(HWIO_BCM_CFG_DEBUG_BUS_ADDR)
#define HWIO_BCM_CFG_DEBUG_BUS_INM(m)      \
        in_dword_masked(HWIO_BCM_CFG_DEBUG_BUS_ADDR, m)
#define HWIO_BCM_CFG_DEBUG_BUS_OUT(v)      \
        out_dword(HWIO_BCM_CFG_DEBUG_BUS_ADDR,v)
#define HWIO_BCM_CFG_DEBUG_BUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BCM_CFG_DEBUG_BUS_ADDR,m,v,HWIO_BCM_CFG_DEBUG_BUS_IN)
#define HWIO_BCM_CFG_DEBUG_BUS_DEBUG_BUS_EN_BMSK                            0x100
#define HWIO_BCM_CFG_DEBUG_BUS_DEBUG_BUS_EN_SHFT                              0x8
#define HWIO_BCM_CFG_DEBUG_BUS_CD_SEL_BMSK                                    0xf
#define HWIO_BCM_CFG_DEBUG_BUS_CD_SEL_SHFT                                    0x0

#define HWIO_BCM_CFG_ARCH_CG_DISABLE_ADDR                              (BCM_CFG_REG_BASE      + 0x00000110)
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_RMSK                                     0x3
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_IN          \
        in_dword(HWIO_BCM_CFG_ARCH_CG_DISABLE_ADDR)
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_INM(m)      \
        in_dword_masked(HWIO_BCM_CFG_ARCH_CG_DISABLE_ADDR, m)
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_OUT(v)      \
        out_dword(HWIO_BCM_CFG_ARCH_CG_DISABLE_ADDR,v)
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BCM_CFG_ARCH_CG_DISABLE_ADDR,m,v,HWIO_BCM_CFG_ARCH_CG_DISABLE_IN)
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_BCM_FE_BMSK                              0x2
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_BCM_FE_SHFT                              0x1
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_BCM_CE_BMSK                              0x1
#define HWIO_BCM_CFG_ARCH_CG_DISABLE_BCM_CE_SHFT                              0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_STATUS
 *--------------------------------------------------------------------------*/

#define BCM_STATUS_REG_BASE                                                     (AOSS_BASE      + 0x00bf0000)
#define BCM_STATUS_REG_BASE_SIZE                                                0x1f00
#define BCM_STATUS_REG_BASE_USED                                                0x170c

#define HWIO_STATUS_FE_AGG_FSM_ADDR                                             (BCM_STATUS_REG_BASE      + 0x00000000)
#define HWIO_STATUS_FE_AGG_FSM_RMSK                                                 0x1fff
#define HWIO_STATUS_FE_AGG_FSM_IN          \
        in_dword(HWIO_STATUS_FE_AGG_FSM_ADDR)
#define HWIO_STATUS_FE_AGG_FSM_INM(m)      \
        in_dword_masked(HWIO_STATUS_FE_AGG_FSM_ADDR, m)
#define HWIO_STATUS_FE_AGG_FSM_AGG_BUSY_CD_BMSK                                     0x1fff
#define HWIO_STATUS_FE_AGG_FSM_AGG_BUSY_CD_SHFT                                        0x0

#define HWIO_STATUS_FE_CDm_ADDR(m)                                              (BCM_STATUS_REG_BASE      + 0x00000004 + 0x4 * (m))
#define HWIO_STATUS_FE_CDm_RMSK                                                 0x3fff00ff
#define HWIO_STATUS_FE_CDm_MAXm                                                         12
#define HWIO_STATUS_FE_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_FE_CDm_ADDR(m), HWIO_STATUS_FE_CDm_RMSK)
#define HWIO_STATUS_FE_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_FE_CDm_ADDR(m), mask)
#define HWIO_STATUS_FE_CDm_AGG_BW_BMSK                                          0x3fff0000
#define HWIO_STATUS_FE_CDm_AGG_BW_SHFT                                                0x10
#define HWIO_STATUS_FE_CDm_FINAL_CP_BMSK                                              0xf0
#define HWIO_STATUS_FE_CDm_FINAL_CP_SHFT                                               0x4
#define HWIO_STATUS_FE_CDm_AGG_CP_BMSK                                                 0xf
#define HWIO_STATUS_FE_CDm_AGG_CP_SHFT                                                 0x0

#define HWIO_STATUS_SNDs_ADDR(s)                                                (BCM_STATUS_REG_BASE      + 0x0000008c + 0x4 * (s))
#define HWIO_STATUS_SNDs_RMSK                                                       0xffff
#define HWIO_STATUS_SNDs_MAXs                                                            4
#define HWIO_STATUS_SNDs_INI(s)        \
        in_dword_masked(HWIO_STATUS_SNDs_ADDR(s), HWIO_STATUS_SNDs_RMSK)
#define HWIO_STATUS_SNDs_INMI(s,mask)    \
        in_dword_masked(HWIO_STATUS_SNDs_ADDR(s), mask)
#define HWIO_STATUS_SNDs_BIT_VEC_BMSK                                               0xffff
#define HWIO_STATUS_SNDs_BIT_VEC_SHFT                                                  0x0

#define HWIO_STATUS_AGG_BW_NDd_ADDR(d)                                          (BCM_STATUS_REG_BASE      + 0x0000010c + 0x4 * (d))
#define HWIO_STATUS_AGG_BW_NDd_RMSK                                                 0x7fff
#define HWIO_STATUS_AGG_BW_NDd_MAXd                                                     31
#define HWIO_STATUS_AGG_BW_NDd_INI(d)        \
        in_dword_masked(HWIO_STATUS_AGG_BW_NDd_ADDR(d), HWIO_STATUS_AGG_BW_NDd_RMSK)
#define HWIO_STATUS_AGG_BW_NDd_INMI(d,mask)    \
        in_dword_masked(HWIO_STATUS_AGG_BW_NDd_ADDR(d), mask)
#define HWIO_STATUS_AGG_BW_NDd_AGG_BW_BMSK                                          0x7fff
#define HWIO_STATUS_AGG_BW_NDd_AGG_BW_SHFT                                             0x0

#define HWIO_STATUS_AGG_BW_Z_NDs_ADDR(s)                                        (BCM_STATUS_REG_BASE      + 0x0000030c + 0x4 * (s))
#define HWIO_STATUS_AGG_BW_Z_NDs_RMSK                                               0x3fff
#define HWIO_STATUS_AGG_BW_Z_NDs_MAXs                                                    4
#define HWIO_STATUS_AGG_BW_Z_NDs_INI(s)        \
        in_dword_masked(HWIO_STATUS_AGG_BW_Z_NDs_ADDR(s), HWIO_STATUS_AGG_BW_Z_NDs_RMSK)
#define HWIO_STATUS_AGG_BW_Z_NDs_INMI(s,mask)    \
        in_dword_masked(HWIO_STATUS_AGG_BW_Z_NDs_ADDR(s), mask)
#define HWIO_STATUS_AGG_BW_Z_NDs_AGG_BW_Z_BMSK                                      0x3fff
#define HWIO_STATUS_AGG_BW_Z_NDs_AGG_BW_Z_SHFT                                         0x0

#define HWIO_STATUS_ME_CDm_ADDR(m)                                              (BCM_STATUS_REG_BASE      + 0x00000330 + 0x4 * (m))
#define HWIO_STATUS_ME_CDm_RMSK                                                   0xffffff
#define HWIO_STATUS_ME_CDm_MAXm                                                          1
#define HWIO_STATUS_ME_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_ME_CDm_ADDR(m), HWIO_STATUS_ME_CDm_RMSK)
#define HWIO_STATUS_ME_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_ME_CDm_ADDR(m), mask)
#define HWIO_STATUS_ME_CDm_ME_MCP_BMSK                                            0xf00000
#define HWIO_STATUS_ME_CDm_ME_MCP_SHFT                                                0x14
#define HWIO_STATUS_ME_CDm_PRE_ME_MCP_BMSK                                         0xf0000
#define HWIO_STATUS_ME_CDm_PRE_ME_MCP_SHFT                                            0x10
#define HWIO_STATUS_ME_CDm_STARC_CP_BMSK                                            0xf000
#define HWIO_STATUS_ME_CDm_STARC_CP_SHFT                                               0xc
#define HWIO_STATUS_ME_CDm_FCP_PLUS_BMSK                                             0xf00
#define HWIO_STATUS_ME_CDm_FCP_PLUS_SHFT                                               0x8
#define HWIO_STATUS_ME_CDm_ACP_BMSK                                                   0xf0
#define HWIO_STATUS_ME_CDm_ACP_SHFT                                                    0x4
#define HWIO_STATUS_ME_CDm_FE_FCP_BMSK                                                 0xf
#define HWIO_STATUS_ME_CDm_FE_FCP_SHFT                                                 0x0

#define HWIO_STATUS_BE_CDm_ADDR(m)                                              (BCM_STATUS_REG_BASE      + 0x00000800 + 0x4 * (m))
#define HWIO_STATUS_BE_CDm_RMSK                                                    0xfffff
#define HWIO_STATUS_BE_CDm_MAXm                                                         12
#define HWIO_STATUS_BE_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_BE_CDm_ADDR(m), HWIO_STATUS_BE_CDm_RMSK)
#define HWIO_STATUS_BE_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_BE_CDm_ADDR(m), mask)
#define HWIO_STATUS_BE_CDm_CLK_DEST_STATE_BMSK                                     0xf0000
#define HWIO_STATUS_BE_CDm_CLK_DEST_STATE_SHFT                                        0x10
#define HWIO_STATUS_BE_CDm_COMBINED_CP_BMSK                                         0xf000
#define HWIO_STATUS_BE_CDm_COMBINED_CP_SHFT                                            0xc
#define HWIO_STATUS_BE_CDm_SW_CP_SNAP_BMSK                                           0xf00
#define HWIO_STATUS_BE_CDm_SW_CP_SNAP_SHFT                                             0x8
#define HWIO_STATUS_BE_CDm_WRITTEN_CP_BMSK                                            0xf0
#define HWIO_STATUS_BE_CDm_WRITTEN_CP_SHFT                                             0x4
#define HWIO_STATUS_BE_CDm_CURR_CP_BMSK                                                0xf
#define HWIO_STATUS_BE_CDm_CURR_CP_SHFT                                                0x0

#define HWIO_STATUS_BE_SEQ_CDm_ADDR(m)                                          (BCM_STATUS_REG_BASE      + 0x00000880 + 0x4 * (m))
#define HWIO_STATUS_BE_SEQ_CDm_RMSK                                                0x1ff01
#define HWIO_STATUS_BE_SEQ_CDm_MAXm                                                     12
#define HWIO_STATUS_BE_SEQ_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_BE_SEQ_CDm_ADDR(m), HWIO_STATUS_BE_SEQ_CDm_RMSK)
#define HWIO_STATUS_BE_SEQ_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_BE_SEQ_CDm_ADDR(m), mask)
#define HWIO_STATUS_BE_SEQ_CDm_SEQ_CURR_PC_BMSK                                    0x1ff00
#define HWIO_STATUS_BE_SEQ_CDm_SEQ_CURR_PC_SHFT                                        0x8
#define HWIO_STATUS_BE_SEQ_CDm_SEQ_STATE_BMSK                                          0x1
#define HWIO_STATUS_BE_SEQ_CDm_SEQ_STATE_SHFT                                          0x0

#define HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_ADDR(m)                             (BCM_STATUS_REG_BASE      + 0x00000900 + 0x4 * (m))
#define HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_RMSK                                       0xf
#define HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_MAXm                                        12
#define HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_ADDR(m), HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_RMSK)
#define HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_ADDR(m), mask)
#define HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_ISSUE_STATUS_BMSK                          0xf
#define HWIO_STATUS_BE_CMD_ISSUE_STATUS_CDm_ISSUE_STATUS_SHFT                          0x0

#define HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_ADDR(m)                              (BCM_STATUS_REG_BASE      + 0x00000980 + 0x4 * (m))
#define HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_RMSK                                        0xf
#define HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_MAXm                                         12
#define HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_ADDR(m), HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_RMSK)
#define HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_ADDR(m), mask)
#define HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_SENT_STATUS_BMSK                            0xf
#define HWIO_STATUS_BE_CMD_SENT_STATUS_CDm_SENT_STATUS_SHFT                            0x0

#define HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_ADDR(m)                              (BCM_STATUS_REG_BASE      + 0x00000a00 + 0x4 * (m))
#define HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_RMSK                                        0xf
#define HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_MAXm                                         12
#define HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_ADDR(m), HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_RMSK)
#define HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_ADDR(m), mask)
#define HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_CMPL_STATUS_BMSK                            0xf
#define HWIO_STATUS_BE_CMD_CMPL_STATUS_CDm_CMPL_STATUS_SHFT                            0x0

#define HWIO_STATUS_BE_SEQ_BR_EV_CDm_ADDR(m)                                    (BCM_STATUS_REG_BASE      + 0x00000a80 + 0x4 * (m))
#define HWIO_STATUS_BE_SEQ_BR_EV_CDm_RMSK                                       0xffffffff
#define HWIO_STATUS_BE_SEQ_BR_EV_CDm_MAXm                                               12
#define HWIO_STATUS_BE_SEQ_BR_EV_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_BE_SEQ_BR_EV_CDm_ADDR(m), HWIO_STATUS_BE_SEQ_BR_EV_CDm_RMSK)
#define HWIO_STATUS_BE_SEQ_BR_EV_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_BE_SEQ_BR_EV_CDm_ADDR(m), mask)
#define HWIO_STATUS_BE_SEQ_BR_EV_CDm_STATUS_BMSK                                0xffffffff
#define HWIO_STATUS_BE_SEQ_BR_EV_CDm_STATUS_SHFT                                       0x0

#define HWIO_STATUS_BE_SEQ_WAIT_EV_CDm_ADDR(m)                                  (BCM_STATUS_REG_BASE      + 0x00000b00 + 0x4 * (m))
#define HWIO_STATUS_BE_SEQ_WAIT_EV_CDm_RMSK                                     0xffffffff
#define HWIO_STATUS_BE_SEQ_WAIT_EV_CDm_MAXm                                             12
#define HWIO_STATUS_BE_SEQ_WAIT_EV_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_BE_SEQ_WAIT_EV_CDm_ADDR(m), HWIO_STATUS_BE_SEQ_WAIT_EV_CDm_RMSK)
#define HWIO_STATUS_BE_SEQ_WAIT_EV_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_BE_SEQ_WAIT_EV_CDm_ADDR(m), mask)
#define HWIO_STATUS_BE_SEQ_WAIT_EV_CDm_STATUS_BMSK                              0xffffffff
#define HWIO_STATUS_BE_SEQ_WAIT_EV_CDm_STATUS_SHFT                                     0x0

#define HWIO_STATUS_BE_SEQ_PWR_CTRL_CDm_ADDR(m)                                 (BCM_STATUS_REG_BASE      + 0x00000b80 + 0x4 * (m))
#define HWIO_STATUS_BE_SEQ_PWR_CTRL_CDm_RMSK                                    0xffffffff
#define HWIO_STATUS_BE_SEQ_PWR_CTRL_CDm_MAXm                                            12
#define HWIO_STATUS_BE_SEQ_PWR_CTRL_CDm_INI(m)        \
        in_dword_masked(HWIO_STATUS_BE_SEQ_PWR_CTRL_CDm_ADDR(m), HWIO_STATUS_BE_SEQ_PWR_CTRL_CDm_RMSK)
#define HWIO_STATUS_BE_SEQ_PWR_CTRL_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_STATUS_BE_SEQ_PWR_CTRL_CDm_ADDR(m), mask)
#define HWIO_STATUS_BE_SEQ_PWR_CTRL_CDm_STATUS_BMSK                             0xffffffff
#define HWIO_STATUS_BE_SEQ_PWR_CTRL_CDm_STATUS_SHFT                                    0x0

#define HWIO_STATUS_CE_DRVr_CTTe_ADDR(r,e)                                      (BCM_STATUS_REG_BASE      + 0x00000f00 + 0x38 * (r) + 0x4 * (e))
#define HWIO_STATUS_CE_DRVr_CTTe_RMSK                                           0xffff07ff
#define HWIO_STATUS_CE_DRVr_CTTe_MAXr                                                   23
#define HWIO_STATUS_CE_DRVr_CTTe_MAXe                                                   13
#define HWIO_STATUS_CE_DRVr_CTTe_INI2(r,e)        \
        in_dword_masked(HWIO_STATUS_CE_DRVr_CTTe_ADDR(r,e), HWIO_STATUS_CE_DRVr_CTTe_RMSK)
#define HWIO_STATUS_CE_DRVr_CTTe_INMI2(r,e,mask)    \
        in_dword_masked(HWIO_STATUS_CE_DRVr_CTTe_ADDR(r,e), mask)
#define HWIO_STATUS_CE_DRVr_CTTe_OFFSET_BMSK                                    0xffff0000
#define HWIO_STATUS_CE_DRVr_CTTe_OFFSET_SHFT                                          0x10
#define HWIO_STATUS_CE_DRVr_CTTe_DESIRED_CP_BMSK                                     0x780
#define HWIO_STATUS_CE_DRVr_CTTe_DESIRED_CP_SHFT                                       0x7
#define HWIO_STATUS_CE_DRVr_CTTe_CD_ID_BMSK                                           0x78
#define HWIO_STATUS_CE_DRVr_CTTe_CD_ID_SHFT                                            0x3
#define HWIO_STATUS_CE_DRVr_CTTe_CTT_STATUS_BMSK                                       0x7
#define HWIO_STATUS_CE_DRVr_CTTe_CTT_STATUS_SHFT                                       0x0

#define HWIO_STATUS_CE_ADDR                                                     (BCM_STATUS_REG_BASE      + 0x00001700)
#define HWIO_STATUS_CE_RMSK                                                      0x1ffffff
#define HWIO_STATUS_CE_IN          \
        in_dword(HWIO_STATUS_CE_ADDR)
#define HWIO_STATUS_CE_INM(m)      \
        in_dword_masked(HWIO_STATUS_CE_ADDR, m)
#define HWIO_STATUS_CE_CTT_EMPTY_DRV_BMSK                                        0x1fffffe
#define HWIO_STATUS_CE_CTT_EMPTY_DRV_SHFT                                              0x1
#define HWIO_STATUS_CE_CTT_EMPTY_BMSK                                                  0x1
#define HWIO_STATUS_CE_CTT_EMPTY_SHFT                                                  0x0

#define HWIO_STATUS_BCM_ADDR                                                    (BCM_STATUS_REG_BASE      + 0x00001704)
#define HWIO_STATUS_BCM_RMSK                                                           0x1
#define HWIO_STATUS_BCM_IN          \
        in_dword(HWIO_STATUS_BCM_ADDR)
#define HWIO_STATUS_BCM_INM(m)      \
        in_dword_masked(HWIO_STATUS_BCM_ADDR, m)
#define HWIO_STATUS_BCM_BCM_IDLE_BMSK                                                  0x1
#define HWIO_STATUS_BCM_BCM_IDLE_SHFT                                                  0x0

#define HWIO_HW_VERSION_ADDR                                                    (BCM_STATUS_REG_BASE      + 0x00001708)
#define HWIO_HW_VERSION_RMSK                                                      0xffffff
#define HWIO_HW_VERSION_IN          \
        in_dword(HWIO_HW_VERSION_ADDR)
#define HWIO_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_HW_VERSION_ADDR, m)
#define HWIO_HW_VERSION_MAJOR_BMSK                                                0xff0000
#define HWIO_HW_VERSION_MAJOR_SHFT                                                    0x10
#define HWIO_HW_VERSION_MINOR_BMSK                                                  0xff00
#define HWIO_HW_VERSION_MINOR_SHFT                                                     0x8
#define HWIO_HW_VERSION_STEP_BMSK                                                     0xff
#define HWIO_HW_VERSION_STEP_SHFT                                                      0x0

#define HWIO_STATUS_ISLAND_LLC_ADDR                                             (BCM_STATUS_REG_BASE      + 0x0000170c)
#define HWIO_STATUS_ISLAND_LLC_RMSK                                                0x11111
#define HWIO_STATUS_ISLAND_LLC_IN          \
        in_dword(HWIO_STATUS_ISLAND_LLC_ADDR)
#define HWIO_STATUS_ISLAND_LLC_INM(m)      \
        in_dword_masked(HWIO_STATUS_ISLAND_LLC_ADDR, m)
#define HWIO_STATUS_ISLAND_LLC_LPINOC_CP_ZERO_BMSK                                 0x10000
#define HWIO_STATUS_ISLAND_LLC_LPINOC_CP_ZERO_SHFT                                    0x10
#define HWIO_STATUS_ISLAND_LLC_LPINOC_ACK_BMSK                                      0x1000
#define HWIO_STATUS_ISLAND_LLC_LPINOC_ACK_SHFT                                         0xc
#define HWIO_STATUS_ISLAND_LLC_LPINOC_REQ_BMSK                                       0x100
#define HWIO_STATUS_ISLAND_LLC_LPINOC_REQ_SHFT                                         0x8
#define HWIO_STATUS_ISLAND_LLC_SPECIAL_APPLIED_BMSK                                   0x10
#define HWIO_STATUS_ISLAND_LLC_SPECIAL_APPLIED_SHFT                                    0x4
#define HWIO_STATUS_ISLAND_LLC_EN_BMSK                                                 0x1
#define HWIO_STATUS_ISLAND_LLC_EN_SHFT                                                 0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_INTERRUPT
 *--------------------------------------------------------------------------*/

#define BCM_INTERRUPT_REG_BASE                                                    (AOSS_BASE      + 0x00bf1f00)
#define BCM_INTERRUPT_REG_BASE_SIZE                                               0x100
#define BCM_INTERRUPT_REG_BASE_USED                                               0xa0

#define HWIO_INTERRUPT_AGG_DONE_INT_EN_ADDR                                       (BCM_INTERRUPT_REG_BASE      + 0x00000000)
#define HWIO_INTERRUPT_AGG_DONE_INT_EN_RMSK                                           0x1fff
#define HWIO_INTERRUPT_AGG_DONE_INT_EN_IN          \
        in_dword(HWIO_INTERRUPT_AGG_DONE_INT_EN_ADDR)
#define HWIO_INTERRUPT_AGG_DONE_INT_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_AGG_DONE_INT_EN_ADDR, m)
#define HWIO_INTERRUPT_AGG_DONE_INT_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_AGG_DONE_INT_EN_ADDR,v)
#define HWIO_INTERRUPT_AGG_DONE_INT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_AGG_DONE_INT_EN_ADDR,m,v,HWIO_INTERRUPT_AGG_DONE_INT_EN_IN)
#define HWIO_INTERRUPT_AGG_DONE_INT_EN_EN_BMSK                                        0x1fff
#define HWIO_INTERRUPT_AGG_DONE_INT_EN_EN_SHFT                                           0x0

#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_ADDR                                 (BCM_INTERRUPT_REG_BASE      + 0x00000004)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_RMSK                                     0x1fff
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_IN          \
        in_dword(HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_ADDR)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_ADDR, m)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_ADDR,v)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_ADDR,m,v,HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_IN)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_EN_BMSK                                  0x1fff
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_EN_EN_SHFT                                     0x0

#define HWIO_INTERRUPT_CTT_FULL_INT_EN_ADDR                                       (BCM_INTERRUPT_REG_BASE      + 0x00000008)
#define HWIO_INTERRUPT_CTT_FULL_INT_EN_RMSK                                         0xffffff
#define HWIO_INTERRUPT_CTT_FULL_INT_EN_IN          \
        in_dword(HWIO_INTERRUPT_CTT_FULL_INT_EN_ADDR)
#define HWIO_INTERRUPT_CTT_FULL_INT_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_CTT_FULL_INT_EN_ADDR, m)
#define HWIO_INTERRUPT_CTT_FULL_INT_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_CTT_FULL_INT_EN_ADDR,v)
#define HWIO_INTERRUPT_CTT_FULL_INT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_CTT_FULL_INT_EN_ADDR,m,v,HWIO_INTERRUPT_CTT_FULL_INT_EN_IN)
#define HWIO_INTERRUPT_CTT_FULL_INT_EN_EN_BMSK                                      0xffffff
#define HWIO_INTERRUPT_CTT_FULL_INT_EN_EN_SHFT                                           0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_ADDR                                  (BCM_INTERRUPT_REG_BASE      + 0x0000000c)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_RMSK                                      0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_IN          \
        in_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_ADDR)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_ADDR, m)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_ADDR,v)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_ADDR,m,v,HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_IN)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_EN_BMSK                                   0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_EN_EN_SHFT                                      0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_ADDR                                  (BCM_INTERRUPT_REG_BASE      + 0x00000010)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_RMSK                                      0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_IN          \
        in_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_ADDR)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_ADDR, m)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_ADDR,v)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_ADDR,m,v,HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_IN)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_EN_BMSK                                   0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_EN_EN_SHFT                                      0x0

#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_ADDR                                   (BCM_INTERRUPT_REG_BASE      + 0x00000014)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_RMSK                                       0x1fff
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_IN          \
        in_dword(HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_ADDR)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_ADDR, m)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_ADDR,v)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_ADDR,m,v,HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_IN)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_EN_BMSK                                    0x1fff
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_EN_EN_SHFT                                       0x0

#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_ADDR                              (BCM_INTERRUPT_REG_BASE      + 0x00000018)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_RMSK                                  0x1fff
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_IN          \
        in_dword(HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_ADDR)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_ADDR, m)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_ADDR,v)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_ADDR,m,v,HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_IN)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_EN_BMSK                               0x1fff
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_EN_EN_SHFT                                  0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_ADDR                                  (BCM_INTERRUPT_REG_BASE      + 0x0000001c)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_RMSK                                      0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_IN          \
        in_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_ADDR)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_ADDR, m)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_ADDR,v)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_ADDR,m,v,HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_IN)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_EN_BMSK                                   0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_EN_EN_SHFT                                      0x0

#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_ADDR                               (BCM_INTERRUPT_REG_BASE      + 0x00000020)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_RMSK                                      0x1
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_IN          \
        in_dword(HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_ADDR)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_ADDR, m)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_ADDR,v)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_ADDR,m,v,HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_IN)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_EN_BMSK                                   0x1
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_EN_EN_SHFT                                   0x0

#define HWIO_INTERRUPT_AGG_DONE_INT_STATUS_ADDR                                   (BCM_INTERRUPT_REG_BASE      + 0x00000040)
#define HWIO_INTERRUPT_AGG_DONE_INT_STATUS_RMSK                                       0x1fff
#define HWIO_INTERRUPT_AGG_DONE_INT_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_AGG_DONE_INT_STATUS_ADDR)
#define HWIO_INTERRUPT_AGG_DONE_INT_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_AGG_DONE_INT_STATUS_ADDR, m)
#define HWIO_INTERRUPT_AGG_DONE_INT_STATUS_STATUS_BMSK                                0x1fff
#define HWIO_INTERRUPT_AGG_DONE_INT_STATUS_STATUS_SHFT                                   0x0

#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_STATUS_ADDR                             (BCM_INTERRUPT_REG_BASE      + 0x00000044)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_STATUS_RMSK                                 0x1fff
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_CP_CHANGE_DONE_INT_STATUS_ADDR)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_CP_CHANGE_DONE_INT_STATUS_ADDR, m)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_STATUS_STATUS_BMSK                          0x1fff
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_STATUS_STATUS_SHFT                             0x0

#define HWIO_INTERRUPT_CTT_FULL_INT_STATUS_ADDR                                   (BCM_INTERRUPT_REG_BASE      + 0x00000048)
#define HWIO_INTERRUPT_CTT_FULL_INT_STATUS_RMSK                                     0xffffff
#define HWIO_INTERRUPT_CTT_FULL_INT_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_CTT_FULL_INT_STATUS_ADDR)
#define HWIO_INTERRUPT_CTT_FULL_INT_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_CTT_FULL_INT_STATUS_ADDR, m)
#define HWIO_INTERRUPT_CTT_FULL_INT_STATUS_STATUS_BMSK                              0xffffff
#define HWIO_INTERRUPT_CTT_FULL_INT_STATUS_STATUS_SHFT                                   0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_STATUS_ADDR                              (BCM_INTERRUPT_REG_BASE      + 0x0000004c)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_STATUS_RMSK                                  0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_0_STATUS_ADDR)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SEQ_GENERIC_INT_0_STATUS_ADDR, m)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_STATUS_STATUS_BMSK                           0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_STATUS_STATUS_SHFT                              0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_STATUS_ADDR                              (BCM_INTERRUPT_REG_BASE      + 0x00000050)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_STATUS_RMSK                                  0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_1_STATUS_ADDR)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SEQ_GENERIC_INT_1_STATUS_ADDR, m)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_STATUS_STATUS_BMSK                           0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_STATUS_STATUS_SHFT                              0x0

#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_STATUS_ADDR                               (BCM_INTERRUPT_REG_BASE      + 0x00000054)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_STATUS_RMSK                                   0x1fff
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_STOP_AGG_ACK_INT_STATUS_ADDR)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_STOP_AGG_ACK_INT_STATUS_ADDR, m)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_STATUS_STATUS_BMSK                            0x1fff
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_STATUS_STATUS_SHFT                               0x0

#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_STATUS_ADDR                          (BCM_INTERRUPT_REG_BASE      + 0x00000058)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_STATUS_RMSK                              0x1fff
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_STATUS_ADDR)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_STATUS_ADDR, m)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_STATUS_STATUS_BMSK                       0x1fff
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_STATUS_STATUS_SHFT                          0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_STATUS_ADDR                              (BCM_INTERRUPT_REG_BASE      + 0x0000005c)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_STATUS_RMSK                                  0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_2_STATUS_ADDR)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SEQ_GENERIC_INT_2_STATUS_ADDR, m)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_STATUS_STATUS_BMSK                           0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_STATUS_STATUS_SHFT                              0x0

#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_STATUS_ADDR                           (BCM_INTERRUPT_REG_BASE      + 0x00000060)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_STATUS_RMSK                                  0x1
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_STATUS_IN          \
        in_dword(HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_STATUS_ADDR)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_STATUS_INM(m)      \
        in_dword_masked(HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_STATUS_ADDR, m)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_STATUS_STATUS_BMSK                           0x1
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_STATUS_STATUS_SHFT                           0x0

#define HWIO_INTERRUPT_AGG_DONE_INT_CLEAR_ADDR                                    (BCM_INTERRUPT_REG_BASE      + 0x00000080)
#define HWIO_INTERRUPT_AGG_DONE_INT_CLEAR_RMSK                                        0x1fff
#define HWIO_INTERRUPT_AGG_DONE_INT_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_AGG_DONE_INT_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_AGG_DONE_INT_CLEAR_CLEAR_BMSK                                  0x1fff
#define HWIO_INTERRUPT_AGG_DONE_INT_CLEAR_CLEAR_SHFT                                     0x0

#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_CLEAR_ADDR                              (BCM_INTERRUPT_REG_BASE      + 0x00000084)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_CLEAR_RMSK                                  0x1fff
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_CP_CHANGE_DONE_INT_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_CLEAR_CLEAR_BMSK                            0x1fff
#define HWIO_INTERRUPT_CP_CHANGE_DONE_INT_CLEAR_CLEAR_SHFT                               0x0

#define HWIO_INTERRUPT_CTT_FULL_INT_CLEAR_ADDR                                    (BCM_INTERRUPT_REG_BASE      + 0x00000088)
#define HWIO_INTERRUPT_CTT_FULL_INT_CLEAR_RMSK                                      0xffffff
#define HWIO_INTERRUPT_CTT_FULL_INT_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_CTT_FULL_INT_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_CTT_FULL_INT_CLEAR_CLEAR_BMSK                                0xffffff
#define HWIO_INTERRUPT_CTT_FULL_INT_CLEAR_CLEAR_SHFT                                     0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_CLEAR_ADDR                               (BCM_INTERRUPT_REG_BASE      + 0x0000008c)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_CLEAR_RMSK                                   0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_0_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_CLEAR_CLEAR_BMSK                             0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_0_CLEAR_CLEAR_SHFT                                0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_CLEAR_ADDR                               (BCM_INTERRUPT_REG_BASE      + 0x00000090)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_CLEAR_RMSK                                   0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_1_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_CLEAR_CLEAR_BMSK                             0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_1_CLEAR_CLEAR_SHFT                                0x0

#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_CLEAR_ADDR                                (BCM_INTERRUPT_REG_BASE      + 0x00000094)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_CLEAR_RMSK                                    0x1fff
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_STOP_AGG_ACK_INT_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_CLEAR_CLEAR_BMSK                              0x1fff
#define HWIO_INTERRUPT_STOP_AGG_ACK_INT_CLEAR_CLEAR_SHFT                                 0x0

#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_CLEAR_ADDR                           (BCM_INTERRUPT_REG_BASE      + 0x00000098)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_CLEAR_RMSK                               0x1fff
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_CLEAR_CLEAR_BMSK                         0x1fff
#define HWIO_INTERRUPT_SW_CP_CHANGE_DONE_INT_CLEAR_CLEAR_SHFT                            0x0

#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_CLEAR_ADDR                               (BCM_INTERRUPT_REG_BASE      + 0x0000009c)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_CLEAR_RMSK                                   0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SEQ_GENERIC_INT_2_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_CLEAR_CLEAR_BMSK                             0x1fff
#define HWIO_INTERRUPT_SEQ_GENERIC_INT_2_CLEAR_CLEAR_SHFT                                0x0

#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_CLEAR_ADDR                            (BCM_INTERRUPT_REG_BASE      + 0x000000a0)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_CLEAR_RMSK                                   0x1
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_CLEAR_OUT(v)      \
        out_dword(HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_CLEAR_ADDR,v)
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_CLEAR_CLEAR_BMSK                             0x1
#define HWIO_INTERRUPT_SYS_STATE_CHANGE_INT_CLEAR_CLEAR_SHFT                             0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_SEQ_MEM
 *--------------------------------------------------------------------------*/

#define BCM_SEQ_MEM_REG_BASE                     (AOSS_BASE      + 0x00bf2400)
#define BCM_SEQ_MEM_REG_BASE_SIZE                0x200
#define BCM_SEQ_MEM_REG_BASE_USED                0x13c

#define HWIO_SEQ_MEMq_ADDR(q)                    (BCM_SEQ_MEM_REG_BASE      + 0x00000000 + 0x4 * (q))
#define HWIO_SEQ_MEMq_RMSK                       0xffffffff
#define HWIO_SEQ_MEMq_MAXq                               79
#define HWIO_SEQ_MEMq_INI(q)        \
        in_dword_masked(HWIO_SEQ_MEMq_ADDR(q), HWIO_SEQ_MEMq_RMSK)
#define HWIO_SEQ_MEMq_INMI(q,mask)    \
        in_dword_masked(HWIO_SEQ_MEMq_ADDR(q), mask)
#define HWIO_SEQ_MEMq_OUTI(q,val)    \
        out_dword(HWIO_SEQ_MEMq_ADDR(q),val)
#define HWIO_SEQ_MEMq_OUTMI(q,mask,val) \
        out_dword_masked_ns(HWIO_SEQ_MEMq_ADDR(q),mask,val,HWIO_SEQ_MEMq_INI(q))
#define HWIO_SEQ_MEMq_CMD_BMSK                   0xffffffff
#define HWIO_SEQ_MEMq_CMD_SHFT                          0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_SW_OVERRIDE
 *--------------------------------------------------------------------------*/

#define BCM_SW_OVERRIDE_REG_BASE                                                            (AOSS_BASE      + 0x00bf2600)
#define BCM_SW_OVERRIDE_REG_BASE_SIZE                                                       0x800
#define BCM_SW_OVERRIDE_REG_BASE_USED                                                       0x780

#define HWIO_SW_CP_CDm_ADDR(m)                                                              (BCM_SW_OVERRIDE_REG_BASE      + 0x00000000 + 0x4 * (m))
#define HWIO_SW_CP_CDm_RMSK                                                                       0x1f
#define HWIO_SW_CP_CDm_MAXm                                                                         12
#define HWIO_SW_CP_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_CP_CDm_ADDR(m), HWIO_SW_CP_CDm_RMSK)
#define HWIO_SW_CP_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_CP_CDm_ADDR(m), mask)
#define HWIO_SW_CP_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_CP_CDm_ADDR(m),val)
#define HWIO_SW_CP_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_CP_CDm_ADDR(m),mask,val,HWIO_SW_CP_CDm_INI(m))
#define HWIO_SW_CP_CDm_VALID_BMSK                                                                 0x10
#define HWIO_SW_CP_CDm_VALID_SHFT                                                                  0x4
#define HWIO_SW_CP_CDm_SW_CP_BMSK                                                                  0xf
#define HWIO_SW_CP_CDm_SW_CP_SHFT                                                                  0x0

#define HWIO_SW_MASK_FE_BE_TRIG_CDm_ADDR(m)                                                 (BCM_SW_OVERRIDE_REG_BASE      + 0x00000080 + 0x4 * (m))
#define HWIO_SW_MASK_FE_BE_TRIG_CDm_RMSK                                                           0x1
#define HWIO_SW_MASK_FE_BE_TRIG_CDm_MAXm                                                            12
#define HWIO_SW_MASK_FE_BE_TRIG_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_MASK_FE_BE_TRIG_CDm_ADDR(m), HWIO_SW_MASK_FE_BE_TRIG_CDm_RMSK)
#define HWIO_SW_MASK_FE_BE_TRIG_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_MASK_FE_BE_TRIG_CDm_ADDR(m), mask)
#define HWIO_SW_MASK_FE_BE_TRIG_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_MASK_FE_BE_TRIG_CDm_ADDR(m),val)
#define HWIO_SW_MASK_FE_BE_TRIG_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_MASK_FE_BE_TRIG_CDm_ADDR(m),mask,val,HWIO_SW_MASK_FE_BE_TRIG_CDm_INI(m))
#define HWIO_SW_MASK_FE_BE_TRIG_CDm_MASK_BMSK                                                      0x1
#define HWIO_SW_MASK_FE_BE_TRIG_CDm_MASK_SHFT                                                      0x0

#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_ADDR(m)                                               (BCM_SW_OVERRIDE_REG_BASE      + 0x00000100 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_RMSK                                                         0x1
#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_MAXm                                                          12
#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERRIDE_STOP_AGG_CDm_ADDR(m), HWIO_SW_OVERRIDE_STOP_AGG_CDm_RMSK)
#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERRIDE_STOP_AGG_CDm_ADDR(m), mask)
#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_STOP_AGG_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERRIDE_STOP_AGG_CDm_ADDR(m),mask,val,HWIO_SW_OVERRIDE_STOP_AGG_CDm_INI(m))
#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_SW_STOP_AGG_BMSK                                             0x1
#define HWIO_SW_OVERRIDE_STOP_AGG_CDm_SW_STOP_AGG_SHFT                                             0x0

#define HWIO_SW_PERMIT_ONE_AGG_CDm_ADDR(m)                                                  (BCM_SW_OVERRIDE_REG_BASE      + 0x00000180 + 0x4 * (m))
#define HWIO_SW_PERMIT_ONE_AGG_CDm_RMSK                                                            0x1
#define HWIO_SW_PERMIT_ONE_AGG_CDm_MAXm                                                             12
#define HWIO_SW_PERMIT_ONE_AGG_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_PERMIT_ONE_AGG_CDm_ADDR(m),val)
#define HWIO_SW_PERMIT_ONE_AGG_CDm_PERMIT_BMSK                                                     0x1
#define HWIO_SW_PERMIT_ONE_AGG_CDm_PERMIT_SHFT                                                     0x0

#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_ADDR(m)                                              (BCM_SW_OVERRIDE_REG_BASE      + 0x00000200 + 0x4 * (m))
#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_RMSK                                                        0xf
#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_MAXm                                                         12
#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERWRITE_FINAL_CP_CDm_ADDR(m), HWIO_SW_OVERWRITE_FINAL_CP_CDm_RMSK)
#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERWRITE_FINAL_CP_CDm_ADDR(m), mask)
#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERWRITE_FINAL_CP_CDm_ADDR(m),val)
#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERWRITE_FINAL_CP_CDm_ADDR(m),mask,val,HWIO_SW_OVERWRITE_FINAL_CP_CDm_INI(m))
#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_FINAL_CP_BMSK                                               0xf
#define HWIO_SW_OVERWRITE_FINAL_CP_CDm_FINAL_CP_SHFT                                               0x0

#define HWIO_SW_BLOCK_FINAL_CP_CDm_ADDR(m)                                                  (BCM_SW_OVERRIDE_REG_BASE      + 0x00000280 + 0x4 * (m))
#define HWIO_SW_BLOCK_FINAL_CP_CDm_RMSK                                                            0x1
#define HWIO_SW_BLOCK_FINAL_CP_CDm_MAXm                                                             12
#define HWIO_SW_BLOCK_FINAL_CP_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_BLOCK_FINAL_CP_CDm_ADDR(m), HWIO_SW_BLOCK_FINAL_CP_CDm_RMSK)
#define HWIO_SW_BLOCK_FINAL_CP_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_BLOCK_FINAL_CP_CDm_ADDR(m), mask)
#define HWIO_SW_BLOCK_FINAL_CP_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_BLOCK_FINAL_CP_CDm_ADDR(m),val)
#define HWIO_SW_BLOCK_FINAL_CP_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_BLOCK_FINAL_CP_CDm_ADDR(m),mask,val,HWIO_SW_BLOCK_FINAL_CP_CDm_INI(m))
#define HWIO_SW_BLOCK_FINAL_CP_CDm_BLOCK_BMSK                                                      0x1
#define HWIO_SW_BLOCK_FINAL_CP_CDm_BLOCK_SHFT                                                      0x0

#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_ADDR(m)                                            (BCM_SW_OVERRIDE_REG_BASE      + 0x00000300 + 0x4 * (m))
#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_RMSK                                                      0xf
#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_MAXm                                                       12
#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_ADDR(m), HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_RMSK)
#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_ADDR(m), mask)
#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_ADDR(m),val)
#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_ADDR(m),mask,val,HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_INI(m))
#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_WRITTEN_CP_BMSK                                           0xf
#define HWIO_SW_OVERWRITE_WRITTEN_CP_CDm_WRITTEN_CP_SHFT                                           0x0

#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_ADDR(m)                                            (BCM_SW_OVERRIDE_REG_BASE      + 0x00000380 + 0x4 * (m))
#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_RMSK                                                      0xf
#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_MAXm                                                       12
#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERWRITE_CURRENT_CP_CDm_ADDR(m), HWIO_SW_OVERWRITE_CURRENT_CP_CDm_RMSK)
#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERWRITE_CURRENT_CP_CDm_ADDR(m), mask)
#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERWRITE_CURRENT_CP_CDm_ADDR(m),val)
#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERWRITE_CURRENT_CP_CDm_ADDR(m),mask,val,HWIO_SW_OVERWRITE_CURRENT_CP_CDm_INI(m))
#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_CURRENT_CP_BMSK                                           0xf
#define HWIO_SW_OVERWRITE_CURRENT_CP_CDm_CURRENT_CP_SHFT                                           0x0

#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_ADDR(m)                                             (BCM_SW_OVERRIDE_REG_BASE      + 0x00000400 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_RMSK                                                       0xf
#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_MAXm                                                        12
#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_ADDR(m), HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_RMSK)
#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_ADDR(m), mask)
#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_ADDR(m),mask,val,HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_INI(m))
#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_CP_SEL_BMSK                                                0xf
#define HWIO_SW_OVERRIDE_TCS_CP_SEL_CDm_CP_SEL_SHFT                                                0x0

#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_ADDR(m)                                             (BCM_SW_OVERRIDE_REG_BASE      + 0x00000480 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_RMSK                                                       0x1
#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_MAXm                                                        12
#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_ADDR(m), HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_RMSK)
#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_ADDR(m), mask)
#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_ADDR(m),mask,val,HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_INI(m))
#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_ENABLE_BMSK                                                0x1
#define HWIO_SW_OVERRIDE_TCS_ENABLE_CDm_ENABLE_SHFT                                                0x0

#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_ADDR(m)                                              (BCM_SW_OVERRIDE_REG_BASE      + 0x00000500 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_RMSK                                                        0x1
#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_MAXm                                                         12
#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_ADDR(m), HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_RMSK)
#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_ADDR(m), mask)
#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_ADDR(m),mask,val,HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_INI(m))
#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_FLUSH_BMSK                                                  0x1
#define HWIO_SW_OVERRIDE_TCS_FLUSH_CDm_FLUSH_SHFT                                                  0x0

#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_ADDR(m)                                     (BCM_SW_OVERRIDE_REG_BASE      + 0x00000580 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_RMSK                                             0x111
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_MAXm                                                12
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_ADDR(m), HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_RMSK)
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_ADDR(m), mask)
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_ADDR(m),mask,val,HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_INI(m))
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_SEQ_UNBLOCK_STICKY_C_BMSK                        0x100
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_SEQ_UNBLOCK_STICKY_C_SHFT                          0x8
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_SEQ_UNBLOCK_STICKY_B_BMSK                         0x10
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_SEQ_UNBLOCK_STICKY_B_SHFT                          0x4
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_SEQ_UNBLOCK_STICKY_A_BMSK                          0x1
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_STICKY_CDm_SEQ_UNBLOCK_STICKY_A_SHFT                          0x0

#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_A_CDm_ADDR(m)                                     (BCM_SW_OVERRIDE_REG_BASE      + 0x00000600 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_A_CDm_RMSK                                               0x1
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_A_CDm_MAXm                                                12
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_A_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_A_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_A_CDm_SEQ_UNBLOCK_ONCE_A_BMSK                            0x1
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_A_CDm_SEQ_UNBLOCK_ONCE_A_SHFT                            0x0

#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_B_CDm_ADDR(m)                                     (BCM_SW_OVERRIDE_REG_BASE      + 0x00000680 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_B_CDm_RMSK                                               0x1
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_B_CDm_MAXm                                                12
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_B_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_B_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_B_CDm_SEQ_UNBLOCK_ONCE_B_BMSK                            0x1
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_B_CDm_SEQ_UNBLOCK_ONCE_B_SHFT                            0x0

#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_C_CDm_ADDR(m)                                     (BCM_SW_OVERRIDE_REG_BASE      + 0x000006c0 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_C_CDm_RMSK                                               0x1
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_C_CDm_MAXm                                                12
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_C_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_C_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_C_CDm_SEQ_UNBLOCK_ONCE_C_BMSK                            0x1
#define HWIO_SW_OVERRIDE_SEQ_UNBLOCK_ONCE_C_CDm_SEQ_UNBLOCK_ONCE_C_SHFT                            0x0

#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_ADDR(m)                                               (BCM_SW_OVERRIDE_REG_BASE      + 0x00000700 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_RMSK                                                        0x11
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_MAXm                                                          12
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERRIDE_CE_INPUT_CDm_ADDR(m), HWIO_SW_OVERRIDE_CE_INPUT_CDm_RMSK)
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERRIDE_CE_INPUT_CDm_ADDR(m), mask)
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_CE_INPUT_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERRIDE_CE_INPUT_CDm_ADDR(m),mask,val,HWIO_SW_OVERRIDE_CE_INPUT_CDm_INI(m))
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_VALID_BMSK                                                  0x10
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_VALID_SHFT                                                   0x4
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_AGG_DONE_BMSK                                                0x1
#define HWIO_SW_OVERRIDE_CE_INPUT_CDm_AGG_DONE_SHFT                                                0x0

#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_ADDR(m)                                      (BCM_SW_OVERRIDE_REG_BASE      + 0x00000740 + 0x4 * (m))
#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_RMSK                                                0x1
#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_MAXm                                                 12
#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_INI(m)        \
        in_dword_masked(HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_ADDR(m), HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_RMSK)
#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_INMI(m,mask)    \
        in_dword_masked(HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_ADDR(m), mask)
#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_OUTI(m,val)    \
        out_dword(HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_ADDR(m),val)
#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_ADDR(m),mask,val,HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_INI(m))
#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_FORCE_CLK_EN_BMSK                                   0x1
#define HWIO_SW_OVERRIDE_BE_SEQ_TCS_CLK_ON_CDm_FORCE_CLK_EN_SHFT                                   0x0

#define HWIO_SW_OVERRIDE_MEM_INIT_MUX_ADDR                                                  (BCM_SW_OVERRIDE_REG_BASE      + 0x00000780)
#define HWIO_SW_OVERRIDE_MEM_INIT_MUX_RMSK                                                         0x1
#define HWIO_SW_OVERRIDE_MEM_INIT_MUX_IN          \
        in_dword(HWIO_SW_OVERRIDE_MEM_INIT_MUX_ADDR)
#define HWIO_SW_OVERRIDE_MEM_INIT_MUX_INM(m)      \
        in_dword_masked(HWIO_SW_OVERRIDE_MEM_INIT_MUX_ADDR, m)
#define HWIO_SW_OVERRIDE_MEM_INIT_MUX_OUT(v)      \
        out_dword(HWIO_SW_OVERRIDE_MEM_INIT_MUX_ADDR,v)
#define HWIO_SW_OVERRIDE_MEM_INIT_MUX_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SW_OVERRIDE_MEM_INIT_MUX_ADDR,m,v,HWIO_SW_OVERRIDE_MEM_INIT_MUX_IN)
#define HWIO_SW_OVERRIDE_MEM_INIT_MUX_DIS_MEM_INIT_PATH_BMSK                                       0x1
#define HWIO_SW_OVERRIDE_MEM_INIT_MUX_DIS_MEM_INIT_PATH_SHFT                                       0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_STARC
 *--------------------------------------------------------------------------*/

#define BCM_STARC_REG_BASE                                                             (AOSS_BASE      + 0x00bf2e00)
#define BCM_STARC_REG_BASE_SIZE                                                        0xb00
#define BCM_STARC_REG_BASE_USED                                                        0xa10

#define HWIO_STARC_CTRL_ADDR                                                           (BCM_STARC_REG_BASE      + 0x00000000)
#define HWIO_STARC_CTRL_RMSK                                                           0xc00007ff
#define HWIO_STARC_CTRL_IN          \
        in_dword(HWIO_STARC_CTRL_ADDR)
#define HWIO_STARC_CTRL_INM(m)      \
        in_dword_masked(HWIO_STARC_CTRL_ADDR, m)
#define HWIO_STARC_CTRL_OUT(v)      \
        out_dword(HWIO_STARC_CTRL_ADDR,v)
#define HWIO_STARC_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_STARC_CTRL_ADDR,m,v,HWIO_STARC_CTRL_IN)
#define HWIO_STARC_CTRL_STARC_EN_BMSK                                                  0x80000000
#define HWIO_STARC_CTRL_STARC_EN_SHFT                                                        0x1f
#define HWIO_STARC_CTRL_STARC_DBG_EN_BMSK                                              0x40000000
#define HWIO_STARC_CTRL_STARC_DBG_EN_SHFT                                                    0x1e
#define HWIO_STARC_CTRL_STARC_EN_PER_VCD_BMSK                                               0x7ff
#define HWIO_STARC_CTRL_STARC_EN_PER_VCD_SHFT                                                 0x0

#define HWIO_SST_VCDvc_SSss_ADDR(vc,ss)                                                (BCM_STARC_REG_BASE      + 0x00000004 + 0x80 * (vc) + 0x4 * (ss))
#define HWIO_SST_VCDvc_SSss_RMSK                                                              0xf
#define HWIO_SST_VCDvc_SSss_MAXvc                                                              10
#define HWIO_SST_VCDvc_SSss_MAXss                                                              31
#define HWIO_SST_VCDvc_SSss_INI2(vc,ss)        \
        in_dword_masked(HWIO_SST_VCDvc_SSss_ADDR(vc,ss), HWIO_SST_VCDvc_SSss_RMSK)
#define HWIO_SST_VCDvc_SSss_INMI2(vc,ss,mask)    \
        in_dword_masked(HWIO_SST_VCDvc_SSss_ADDR(vc,ss), mask)
#define HWIO_SST_VCDvc_SSss_OUTI2(vc,ss,val)    \
        out_dword(HWIO_SST_VCDvc_SSss_ADDR(vc,ss),val)
#define HWIO_SST_VCDvc_SSss_OUTMI2(vc,ss,mask,val) \
        out_dword_masked_ns(HWIO_SST_VCDvc_SSss_ADDR(vc,ss),mask,val,HWIO_SST_VCDvc_SSss_INI2(vc,ss))
#define HWIO_SST_VCDvc_SSss_CP_BMSK                                                           0xf
#define HWIO_SST_VCDvc_SSss_CP_SHFT                                                           0x0

#define HWIO_STARC_STATUS_ADDR                                                         (BCM_STARC_REG_BASE      + 0x00000800)
#define HWIO_STARC_STATUS_RMSK                                                               0x1f
#define HWIO_STARC_STATUS_IN          \
        in_dword(HWIO_STARC_STATUS_ADDR)
#define HWIO_STARC_STATUS_INM(m)      \
        in_dword_masked(HWIO_STARC_STATUS_ADDR, m)
#define HWIO_STARC_STATUS_AGG_SYSTEM_STATE_BMSK                                              0x1f
#define HWIO_STARC_STATUS_AGG_SYSTEM_STATE_SHFT                                               0x0

#define HWIO_STARC_STATUS_VCDvc_L_ADDR(vc)                                             (BCM_STARC_REG_BASE      + 0x00000804 + 0x4 * (vc))
#define HWIO_STARC_STATUS_VCDvc_L_RMSK                                                 0xffffffff
#define HWIO_STARC_STATUS_VCDvc_L_MAXvc                                                        10
#define HWIO_STARC_STATUS_VCDvc_L_INI(vc)        \
        in_dword_masked(HWIO_STARC_STATUS_VCDvc_L_ADDR(vc), HWIO_STARC_STATUS_VCDvc_L_RMSK)
#define HWIO_STARC_STATUS_VCDvc_L_INMI(vc,mask)    \
        in_dword_masked(HWIO_STARC_STATUS_VCDvc_L_ADDR(vc), mask)
#define HWIO_STARC_STATUS_VCDvc_L_SYSTEM_STATE_MAP_LOWER_32BITS_BMSK                   0xffffffff
#define HWIO_STARC_STATUS_VCDvc_L_SYSTEM_STATE_MAP_LOWER_32BITS_SHFT                          0x0

#define HWIO_STARC_STATUS_VCDvc_ADDR(vc)                                               (BCM_STARC_REG_BASE      + 0x00000884 + 0x4 * (vc))
#define HWIO_STARC_STATUS_VCDvc_RMSK                                                          0xf
#define HWIO_STARC_STATUS_VCDvc_MAXvc                                                          10
#define HWIO_STARC_STATUS_VCDvc_INI(vc)        \
        in_dword_masked(HWIO_STARC_STATUS_VCDvc_ADDR(vc), HWIO_STARC_STATUS_VCDvc_RMSK)
#define HWIO_STARC_STATUS_VCDvc_INMI(vc,mask)    \
        in_dword_masked(HWIO_STARC_STATUS_VCDvc_ADDR(vc), mask)
#define HWIO_STARC_STATUS_VCDvc_MCP_BMSK                                                      0xf
#define HWIO_STARC_STATUS_VCDvc_MCP_SHFT                                                      0x0

#define HWIO_STARC_OVERRIDE_ADDR                                                       (BCM_STARC_REG_BASE      + 0x000008c4)
#define HWIO_STARC_OVERRIDE_RMSK                                                       0x8000001f
#define HWIO_STARC_OVERRIDE_IN          \
        in_dword(HWIO_STARC_OVERRIDE_ADDR)
#define HWIO_STARC_OVERRIDE_INM(m)      \
        in_dword_masked(HWIO_STARC_OVERRIDE_ADDR, m)
#define HWIO_STARC_OVERRIDE_OUT(v)      \
        out_dword(HWIO_STARC_OVERRIDE_ADDR,v)
#define HWIO_STARC_OVERRIDE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_STARC_OVERRIDE_ADDR,m,v,HWIO_STARC_OVERRIDE_IN)
#define HWIO_STARC_OVERRIDE_EN_BMSK                                                    0x80000000
#define HWIO_STARC_OVERRIDE_EN_SHFT                                                          0x1f
#define HWIO_STARC_OVERRIDE_SS_BMSK                                                          0x1f
#define HWIO_STARC_OVERRIDE_SS_SHFT                                                           0x0

#define HWIO_STARC_SYSTEM_STATE_ADDR                                                   (BCM_STARC_REG_BASE      + 0x000008c8)
#define HWIO_STARC_SYSTEM_STATE_RMSK                                                   0xffffffff
#define HWIO_STARC_SYSTEM_STATE_IN          \
        in_dword(HWIO_STARC_SYSTEM_STATE_ADDR)
#define HWIO_STARC_SYSTEM_STATE_INM(m)      \
        in_dword_masked(HWIO_STARC_SYSTEM_STATE_ADDR, m)
#define HWIO_STARC_SYSTEM_STATE_OUT(v)      \
        out_dword(HWIO_STARC_SYSTEM_STATE_ADDR,v)
#define HWIO_STARC_SYSTEM_STATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_STARC_SYSTEM_STATE_ADDR,m,v,HWIO_STARC_SYSTEM_STATE_IN)
#define HWIO_STARC_SYSTEM_STATE_DIS_BMSK                                               0xffffffff
#define HWIO_STARC_SYSTEM_STATE_DIS_SHFT                                                      0x0

#define HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_ADDR                                    (BCM_STARC_REG_BASE      + 0x000008d0)
#define HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_RMSK                                           0x1
#define HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_IN          \
        in_dword(HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_ADDR)
#define HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_INM(m)      \
        in_dword_masked(HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_ADDR, m)
#define HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_OUT(v)      \
        out_dword(HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_ADDR,v)
#define HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_ADDR,m,v,HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_IN)
#define HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_DIS_BMSK                                       0x1
#define HWIO_STARC_SYSTEM_STATE_RESIDENCY_CTRL_DIS_SHFT                                       0x0

#define HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_ADDR(ss)                            (BCM_STARC_REG_BASE      + 0x00000994 + 0x4 * (ss))
#define HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_RMSK                                0xffffffff
#define HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_MAXss                                       31
#define HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_INI(ss)        \
        in_dword_masked(HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_ADDR(ss), HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_RMSK)
#define HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_INMI(ss,mask)    \
        in_dword_masked(HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_ADDR(ss), mask)
#define HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_COUNT_BMSK                          0xffffffff
#define HWIO_STARC_STATUS_SYSTEM_STATE_RESIDENCYss_COUNT_SHFT                                 0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_DDR_MNGR
 *--------------------------------------------------------------------------*/

#define BCM_DDR_MNGR_REG_BASE                                  (AOSS_BASE      + 0x00bf3900)
#define BCM_DDR_MNGR_REG_BASE_SIZE                             0x100
#define BCM_DDR_MNGR_REG_BASE_USED                             0x8c

#define HWIO_DDR_MNGR_HARDEN_CTRL_ADDR                         (BCM_DDR_MNGR_REG_BASE      + 0x00000000)
#define HWIO_DDR_MNGR_HARDEN_CTRL_RMSK                                0x1
#define HWIO_DDR_MNGR_HARDEN_CTRL_IN          \
        in_dword(HWIO_DDR_MNGR_HARDEN_CTRL_ADDR)
#define HWIO_DDR_MNGR_HARDEN_CTRL_INM(m)      \
        in_dword_masked(HWIO_DDR_MNGR_HARDEN_CTRL_ADDR, m)
#define HWIO_DDR_MNGR_HARDEN_CTRL_OUT(v)      \
        out_dword(HWIO_DDR_MNGR_HARDEN_CTRL_ADDR,v)
#define HWIO_DDR_MNGR_HARDEN_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_DDR_MNGR_HARDEN_CTRL_ADDR,m,v,HWIO_DDR_MNGR_HARDEN_CTRL_IN)
#define HWIO_DDR_MNGR_HARDEN_CTRL_DIS_BMSK                            0x1
#define HWIO_DDR_MNGR_HARDEN_CTRL_DIS_SHFT                            0x0

#define HWIO_DDRSS_CP_EN_ADDR                                  (BCM_DDR_MNGR_REG_BASE      + 0x00000004)
#define HWIO_DDRSS_CP_EN_RMSK                                    0xffffff
#define HWIO_DDRSS_CP_EN_IN          \
        in_dword(HWIO_DDRSS_CP_EN_ADDR)
#define HWIO_DDRSS_CP_EN_INM(m)      \
        in_dword_masked(HWIO_DDRSS_CP_EN_ADDR, m)
#define HWIO_DDRSS_CP_EN_OUT(v)      \
        out_dword(HWIO_DDRSS_CP_EN_ADDR,v)
#define HWIO_DDRSS_CP_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_DDRSS_CP_EN_ADDR,m,v,HWIO_DDRSS_CP_EN_IN)
#define HWIO_DDRSS_CP_EN_SHUB_CP_EN_BMSK                         0xff0000
#define HWIO_DDRSS_CP_EN_SHUB_CP_EN_SHFT                             0x10
#define HWIO_DDRSS_CP_EN_MC_CP_EN_BMSK                             0xffff
#define HWIO_DDRSS_CP_EN_MC_CP_EN_SHFT                                0x0

#define HWIO_DDR_PSol_TO_CP_LUT_ADDR(ol)                       (BCM_DDR_MNGR_REG_BASE      + 0x00000008 + 0x4 * (ol))
#define HWIO_DDR_PSol_TO_CP_LUT_RMSK                                0xf0f
#define HWIO_DDR_PSol_TO_CP_LUT_MAXol                                  15
#define HWIO_DDR_PSol_TO_CP_LUT_INI(ol)        \
        in_dword_masked(HWIO_DDR_PSol_TO_CP_LUT_ADDR(ol), HWIO_DDR_PSol_TO_CP_LUT_RMSK)
#define HWIO_DDR_PSol_TO_CP_LUT_INMI(ol,mask)    \
        in_dword_masked(HWIO_DDR_PSol_TO_CP_LUT_ADDR(ol), mask)
#define HWIO_DDR_PSol_TO_CP_LUT_OUTI(ol,val)    \
        out_dword(HWIO_DDR_PSol_TO_CP_LUT_ADDR(ol),val)
#define HWIO_DDR_PSol_TO_CP_LUT_OUTMI(ol,mask,val) \
        out_dword_masked_ns(HWIO_DDR_PSol_TO_CP_LUT_ADDR(ol),mask,val,HWIO_DDR_PSol_TO_CP_LUT_INI(ol))
#define HWIO_DDR_PSol_TO_CP_LUT_SHUB_CP_BMSK                        0xf00
#define HWIO_DDR_PSol_TO_CP_LUT_SHUB_CP_SHFT                          0x8
#define HWIO_DDR_PSol_TO_CP_LUT_MC_CP_BMSK                            0xf
#define HWIO_DDR_PSol_TO_CP_LUT_MC_CP_SHFT                            0x0

#define HWIO_DDR_MNGR_CPLOCK_CTRL_ADDR                         (BCM_DDR_MNGR_REG_BASE      + 0x00000048)
#define HWIO_DDR_MNGR_CPLOCK_CTRL_RMSK                                0x1
#define HWIO_DDR_MNGR_CPLOCK_CTRL_IN          \
        in_dword(HWIO_DDR_MNGR_CPLOCK_CTRL_ADDR)
#define HWIO_DDR_MNGR_CPLOCK_CTRL_INM(m)      \
        in_dword_masked(HWIO_DDR_MNGR_CPLOCK_CTRL_ADDR, m)
#define HWIO_DDR_MNGR_CPLOCK_CTRL_OUT(v)      \
        out_dword(HWIO_DDR_MNGR_CPLOCK_CTRL_ADDR,v)
#define HWIO_DDR_MNGR_CPLOCK_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_DDR_MNGR_CPLOCK_CTRL_ADDR,m,v,HWIO_DDR_MNGR_CPLOCK_CTRL_IN)
#define HWIO_DDR_MNGR_CPLOCK_CTRL_DIS_BMSK                            0x1
#define HWIO_DDR_MNGR_CPLOCK_CTRL_DIS_SHFT                            0x0

#define HWIO_DDR_MNGR_MCm_FLOOR_ADDR(m)                        (BCM_DDR_MNGR_REG_BASE      + 0x0000004c + 0x4 * (m))
#define HWIO_DDR_MNGR_MCm_FLOOR_RMSK                                  0xf
#define HWIO_DDR_MNGR_MCm_FLOOR_MAXm                                   15
#define HWIO_DDR_MNGR_MCm_FLOOR_INI(m)        \
        in_dword_masked(HWIO_DDR_MNGR_MCm_FLOOR_ADDR(m), HWIO_DDR_MNGR_MCm_FLOOR_RMSK)
#define HWIO_DDR_MNGR_MCm_FLOOR_INMI(m,mask)    \
        in_dword_masked(HWIO_DDR_MNGR_MCm_FLOOR_ADDR(m), mask)
#define HWIO_DDR_MNGR_MCm_FLOOR_OUTI(m,val)    \
        out_dword(HWIO_DDR_MNGR_MCm_FLOOR_ADDR(m),val)
#define HWIO_DDR_MNGR_MCm_FLOOR_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_DDR_MNGR_MCm_FLOOR_ADDR(m),mask,val,HWIO_DDR_MNGR_MCm_FLOOR_INI(m))
#define HWIO_DDR_MNGR_MCm_FLOOR_SHUB_CP_BMSK                          0xf
#define HWIO_DDR_MNGR_MCm_FLOOR_SHUB_CP_SHFT                          0x0

#define HWIO_DDR_MNGR_FE_TO_DDR_PS_ADDR                        (BCM_DDR_MNGR_REG_BASE      + 0x0000008c)
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_RMSK                              0xff
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_IN          \
        in_dword(HWIO_DDR_MNGR_FE_TO_DDR_PS_ADDR)
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_INM(m)      \
        in_dword_masked(HWIO_DDR_MNGR_FE_TO_DDR_PS_ADDR, m)
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_OUT(v)      \
        out_dword(HWIO_DDR_MNGR_FE_TO_DDR_PS_ADDR,v)
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_DDR_MNGR_FE_TO_DDR_PS_ADDR,m,v,HWIO_DDR_MNGR_FE_TO_DDR_PS_IN)
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_MOL_BMSK                          0xf0
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_MOL_SHFT                           0x4
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_BMOL_BMSK                          0xf
#define HWIO_DDR_MNGR_FE_TO_DDR_PS_BMOL_SHFT                          0x0

/*----------------------------------------------------------------------------
 * MODULE: BCM_FT
 *--------------------------------------------------------------------------*/

#define BCM_FT_REG_BASE                                                                 (AOSS_BASE      + 0x00bf3a00)
#define BCM_FT_REG_BASE_SIZE                                                            0x1000
#define BCM_FT_REG_BASE_USED                                                            0xea4

#define HWIO_FT_ADCVS_CTRL_ADDR                                                         (BCM_FT_REG_BASE      + 0x00000000)
#define HWIO_FT_ADCVS_CTRL_RMSK                                                                0x1
#define HWIO_FT_ADCVS_CTRL_IN          \
        in_dword(HWIO_FT_ADCVS_CTRL_ADDR)
#define HWIO_FT_ADCVS_CTRL_INM(m)      \
        in_dword_masked(HWIO_FT_ADCVS_CTRL_ADDR, m)
#define HWIO_FT_ADCVS_CTRL_OUT(v)      \
        out_dword(HWIO_FT_ADCVS_CTRL_ADDR,v)
#define HWIO_FT_ADCVS_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_ADCVS_CTRL_ADDR,m,v,HWIO_FT_ADCVS_CTRL_IN)
#define HWIO_FT_ADCVS_CTRL_EN_BMSK                                                             0x1
#define HWIO_FT_ADCVS_CTRL_EN_SHFT                                                             0x0

#define HWIO_FT_SEQ_MEMm_ADDR(m)                                                        (BCM_FT_REG_BASE      + 0x00000004 + 0x4 * (m))
#define HWIO_FT_SEQ_MEMm_RMSK                                                           0xffffffff
#define HWIO_FT_SEQ_MEMm_MAXm                                                                   63
#define HWIO_FT_SEQ_MEMm_INI(m)        \
        in_dword_masked(HWIO_FT_SEQ_MEMm_ADDR(m), HWIO_FT_SEQ_MEMm_RMSK)
#define HWIO_FT_SEQ_MEMm_INMI(m,mask)    \
        in_dword_masked(HWIO_FT_SEQ_MEMm_ADDR(m), mask)
#define HWIO_FT_SEQ_MEMm_OUTI(m,val)    \
        out_dword(HWIO_FT_SEQ_MEMm_ADDR(m),val)
#define HWIO_FT_SEQ_MEMm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_FT_SEQ_MEMm_ADDR(m),mask,val,HWIO_FT_SEQ_MEMm_INI(m))
#define HWIO_FT_SEQ_MEMm_CMD_BMSK                                                       0xffffffff
#define HWIO_FT_SEQ_MEMm_CMD_SHFT                                                              0x0

#define HWIO_FT_FE_TRIG_ADDR                                                            (BCM_FT_REG_BASE      + 0x000001fc)
#define HWIO_FT_FE_TRIG_RMSK                                                                 0x3ff
#define HWIO_FT_FE_TRIG_IN          \
        in_dword(HWIO_FT_FE_TRIG_ADDR)
#define HWIO_FT_FE_TRIG_INM(m)      \
        in_dword_masked(HWIO_FT_FE_TRIG_ADDR, m)
#define HWIO_FT_FE_TRIG_OUT(v)      \
        out_dword(HWIO_FT_FE_TRIG_ADDR,v)
#define HWIO_FT_FE_TRIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_FE_TRIG_ADDR,m,v,HWIO_FT_FE_TRIG_IN)
#define HWIO_FT_FE_TRIG_DRV_ND_BIT_POS_BMSK                                                  0x3ff
#define HWIO_FT_FE_TRIG_DRV_ND_BIT_POS_SHFT                                                    0x0

#define HWIO_FT_SEQ_DBG_STEP_ADDR                                                       (BCM_FT_REG_BASE      + 0x00000200)
#define HWIO_FT_SEQ_DBG_STEP_RMSK                                                              0x1
#define HWIO_FT_SEQ_DBG_STEP_OUT(v)      \
        out_dword(HWIO_FT_SEQ_DBG_STEP_ADDR,v)
#define HWIO_FT_SEQ_DBG_STEP_DBG_STEP_TRIGGER_BMSK                                             0x1
#define HWIO_FT_SEQ_DBG_STEP_DBG_STEP_TRIGGER_SHFT                                             0x0

#define HWIO_FT_SEQ_DBG_CONTINUE_ADDR                                                   (BCM_FT_REG_BASE      + 0x00000204)
#define HWIO_FT_SEQ_DBG_CONTINUE_RMSK                                                          0x1
#define HWIO_FT_SEQ_DBG_CONTINUE_OUT(v)      \
        out_dword(HWIO_FT_SEQ_DBG_CONTINUE_ADDR,v)
#define HWIO_FT_SEQ_DBG_CONTINUE_DBG_STEP_CONTINUE_BMSK                                        0x1
#define HWIO_FT_SEQ_DBG_CONTINUE_DBG_STEP_CONTINUE_SHFT                                        0x0

#define HWIO_FT_SEQ_DBG_STAT_ADDR                                                       (BCM_FT_REG_BASE      + 0x00000208)
#define HWIO_FT_SEQ_DBG_STAT_RMSK                                                              0x1
#define HWIO_FT_SEQ_DBG_STAT_IN          \
        in_dword(HWIO_FT_SEQ_DBG_STAT_ADDR)
#define HWIO_FT_SEQ_DBG_STAT_INM(m)      \
        in_dword_masked(HWIO_FT_SEQ_DBG_STAT_ADDR, m)
#define HWIO_FT_SEQ_DBG_STAT_DBG_STEPPING_STATUS_BMSK                                          0x1
#define HWIO_FT_SEQ_DBG_STAT_DBG_STEPPING_STATUS_SHFT                                          0x0

#define HWIO_FT_SEQ_DBG_BREAKPOINT_ADDR_ADDR                                            (BCM_FT_REG_BASE      + 0x0000020c)
#define HWIO_FT_SEQ_DBG_BREAKPOINT_ADDR_RMSK                                            0x800000ff
#define HWIO_FT_SEQ_DBG_BREAKPOINT_ADDR_IN          \
        in_dword(HWIO_FT_SEQ_DBG_BREAKPOINT_ADDR_ADDR)
#define HWIO_FT_SEQ_DBG_BREAKPOINT_ADDR_INM(m)      \
        in_dword_masked(HWIO_FT_SEQ_DBG_BREAKPOINT_ADDR_ADDR, m)
#define HWIO_FT_SEQ_DBG_BREAKPOINT_ADDR_OUT(v)      \
        out_dword(HWIO_FT_SEQ_DBG_BREAKPOINT_ADDR_ADDR,v)
#define HWIO_FT_SEQ_DBG_BREAKPOINT_ADDR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_SEQ_DBG_BREAKPOINT_ADDR_ADDR,m,v,HWIO_FT_SEQ_DBG_BREAKPOINT_ADDR_IN)
#define HWIO_FT_SEQ_DBG_BREAKPOINT_ADDR_DBG_BREAKPOINT_VALID_BMSK                       0x80000000
#define HWIO_FT_SEQ_DBG_BREAKPOINT_ADDR_DBG_BREAKPOINT_VALID_SHFT                             0x1f
#define HWIO_FT_SEQ_DBG_BREAKPOINT_ADDR_DBG_BREAKPOINT_ADDR_BMSK                              0xff
#define HWIO_FT_SEQ_DBG_BREAKPOINT_ADDR_DBG_BREAKPOINT_ADDR_SHFT                               0x0

#define HWIO_FT_SEQ_CFG_ADDR                                                            (BCM_FT_REG_BASE      + 0x00000210)
#define HWIO_FT_SEQ_CFG_RMSK                                                               0x100ff
#define HWIO_FT_SEQ_CFG_IN          \
        in_dword(HWIO_FT_SEQ_CFG_ADDR)
#define HWIO_FT_SEQ_CFG_INM(m)      \
        in_dword_masked(HWIO_FT_SEQ_CFG_ADDR, m)
#define HWIO_FT_SEQ_CFG_OUT(v)      \
        out_dword(HWIO_FT_SEQ_CFG_ADDR,v)
#define HWIO_FT_SEQ_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_SEQ_CFG_ADDR,m,v,HWIO_FT_SEQ_CFG_IN)
#define HWIO_FT_SEQ_CFG_SEQ_START_BMSK                                                     0x10000
#define HWIO_FT_SEQ_CFG_SEQ_START_SHFT                                                        0x10
#define HWIO_FT_SEQ_CFG_SEQ_START_ADDR_BMSK                                                   0xff
#define HWIO_FT_SEQ_CFG_SEQ_START_ADDR_SHFT                                                    0x0

#define HWIO_FT_SEQ_STAT_ADDR                                                           (BCM_FT_REG_BASE      + 0x00000214)
#define HWIO_FT_SEQ_STAT_RMSK                                                              0x100ff
#define HWIO_FT_SEQ_STAT_IN          \
        in_dword(HWIO_FT_SEQ_STAT_ADDR)
#define HWIO_FT_SEQ_STAT_INM(m)      \
        in_dword_masked(HWIO_FT_SEQ_STAT_ADDR, m)
#define HWIO_FT_SEQ_STAT_SEQ_BUSY_BMSK                                                     0x10000
#define HWIO_FT_SEQ_STAT_SEQ_BUSY_SHFT                                                        0x10
#define HWIO_FT_SEQ_STAT_SEQ_PC_BMSK                                                          0xff
#define HWIO_FT_SEQ_STAT_SEQ_PC_SHFT                                                           0x0

#define HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_MASK_ADDR                                 (BCM_FT_REG_BASE      + 0x00000218)
#define HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_MASK_RMSK                                 0xffffffff
#define HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_MASK_IN          \
        in_dword(HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_MASK_ADDR)
#define HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_MASK_INM(m)      \
        in_dword_masked(HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_MASK_ADDR, m)
#define HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_MASK_OUT(v)      \
        out_dword(HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_MASK_ADDR,v)
#define HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_MASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_MASK_ADDR,m,v,HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_MASK_IN)
#define HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_MASK_MASK_BMSK                            0xffffffff
#define HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_MASK_MASK_SHFT                                   0x0

#define HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_VAL_ADDR                                  (BCM_FT_REG_BASE      + 0x00000220)
#define HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_VAL_RMSK                                  0xffffffff
#define HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_VAL_IN          \
        in_dword(HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_VAL_ADDR)
#define HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_VAL_INM(m)      \
        in_dword_masked(HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_VAL_ADDR, m)
#define HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_VAL_OUT(v)      \
        out_dword(HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_VAL_ADDR,v)
#define HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_VAL_ADDR,m,v,HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_VAL_IN)
#define HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_VAL_OVERRIDE_VAL_BMSK                     0xffffffff
#define HWIO_FT_SEQ_PWR_CTRL_OVRD_BIT_31_TO_0_VAL_OVERRIDE_VAL_SHFT                            0x0

#define HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_MASK_ADDR                               (BCM_FT_REG_BASE      + 0x00000228)
#define HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_MASK_RMSK                               0xffffffff
#define HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_MASK_IN          \
        in_dword(HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_MASK_ADDR)
#define HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_MASK_INM(m)      \
        in_dword_masked(HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_MASK_ADDR, m)
#define HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_MASK_OUT(v)      \
        out_dword(HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_MASK_ADDR,v)
#define HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_MASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_MASK_ADDR,m,v,HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_MASK_IN)
#define HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_MASK_MASK_BMSK                          0xffffffff
#define HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_MASK_MASK_SHFT                                 0x0

#define HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_VAL_ADDR                                (BCM_FT_REG_BASE      + 0x00000230)
#define HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_VAL_RMSK                                0xffffffff
#define HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_VAL_IN          \
        in_dword(HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_VAL_ADDR)
#define HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_VAL_INM(m)      \
        in_dword_masked(HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_VAL_ADDR, m)
#define HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_VAL_OUT(v)      \
        out_dword(HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_VAL_ADDR,v)
#define HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_VAL_ADDR,m,v,HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_VAL_IN)
#define HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_VAL_OVERRIDE_VAL_BMSK                   0xffffffff
#define HWIO_FT_SEQ_WAIT_EVENT_BIT_31_TO_0_OVRD_VAL_OVERRIDE_VAL_SHFT                          0x0

#define HWIO_FT_SEQ_BRANCH_EVENT_OVRD_MASK_ADDR                                         (BCM_FT_REG_BASE      + 0x00000238)
#define HWIO_FT_SEQ_BRANCH_EVENT_OVRD_MASK_RMSK                                         0xffffffff
#define HWIO_FT_SEQ_BRANCH_EVENT_OVRD_MASK_IN          \
        in_dword(HWIO_FT_SEQ_BRANCH_EVENT_OVRD_MASK_ADDR)
#define HWIO_FT_SEQ_BRANCH_EVENT_OVRD_MASK_INM(m)      \
        in_dword_masked(HWIO_FT_SEQ_BRANCH_EVENT_OVRD_MASK_ADDR, m)
#define HWIO_FT_SEQ_BRANCH_EVENT_OVRD_MASK_OUT(v)      \
        out_dword(HWIO_FT_SEQ_BRANCH_EVENT_OVRD_MASK_ADDR,v)
#define HWIO_FT_SEQ_BRANCH_EVENT_OVRD_MASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_SEQ_BRANCH_EVENT_OVRD_MASK_ADDR,m,v,HWIO_FT_SEQ_BRANCH_EVENT_OVRD_MASK_IN)
#define HWIO_FT_SEQ_BRANCH_EVENT_OVRD_MASK_MASK_BMSK                                    0xffffffff
#define HWIO_FT_SEQ_BRANCH_EVENT_OVRD_MASK_MASK_SHFT                                           0x0

#define HWIO_FT_SEQ_BRANCH_EVENT_OVRD_VAL_ADDR                                          (BCM_FT_REG_BASE      + 0x0000023c)
#define HWIO_FT_SEQ_BRANCH_EVENT_OVRD_VAL_RMSK                                          0xffffffff
#define HWIO_FT_SEQ_BRANCH_EVENT_OVRD_VAL_IN          \
        in_dword(HWIO_FT_SEQ_BRANCH_EVENT_OVRD_VAL_ADDR)
#define HWIO_FT_SEQ_BRANCH_EVENT_OVRD_VAL_INM(m)      \
        in_dword_masked(HWIO_FT_SEQ_BRANCH_EVENT_OVRD_VAL_ADDR, m)
#define HWIO_FT_SEQ_BRANCH_EVENT_OVRD_VAL_OUT(v)      \
        out_dword(HWIO_FT_SEQ_BRANCH_EVENT_OVRD_VAL_ADDR,v)
#define HWIO_FT_SEQ_BRANCH_EVENT_OVRD_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_SEQ_BRANCH_EVENT_OVRD_VAL_ADDR,m,v,HWIO_FT_SEQ_BRANCH_EVENT_OVRD_VAL_IN)
#define HWIO_FT_SEQ_BRANCH_EVENT_OVRD_VAL_OVERRIDE_VAL_BMSK                             0xffffffff
#define HWIO_FT_SEQ_BRANCH_EVENT_OVRD_VAL_OVERRIDE_VAL_SHFT                                    0x0

#define HWIO_FT_SEQ_CFG_DELAY_VALq_ADDR(q)                                              (BCM_FT_REG_BASE      + 0x00000240 + 0x4 * (q))
#define HWIO_FT_SEQ_CFG_DELAY_VALq_RMSK                                                    0xfffff
#define HWIO_FT_SEQ_CFG_DELAY_VALq_MAXq                                                          3
#define HWIO_FT_SEQ_CFG_DELAY_VALq_INI(q)        \
        in_dword_masked(HWIO_FT_SEQ_CFG_DELAY_VALq_ADDR(q), HWIO_FT_SEQ_CFG_DELAY_VALq_RMSK)
#define HWIO_FT_SEQ_CFG_DELAY_VALq_INMI(q,mask)    \
        in_dword_masked(HWIO_FT_SEQ_CFG_DELAY_VALq_ADDR(q), mask)
#define HWIO_FT_SEQ_CFG_DELAY_VALq_OUTI(q,val)    \
        out_dword(HWIO_FT_SEQ_CFG_DELAY_VALq_ADDR(q),val)
#define HWIO_FT_SEQ_CFG_DELAY_VALq_OUTMI(q,mask,val) \
        out_dword_masked_ns(HWIO_FT_SEQ_CFG_DELAY_VALq_ADDR(q),mask,val,HWIO_FT_SEQ_CFG_DELAY_VALq_INI(q))
#define HWIO_FT_SEQ_CFG_DELAY_VALq_DELAY_VAL_BMSK                                          0xfffff
#define HWIO_FT_SEQ_CFG_DELAY_VALq_DELAY_VAL_SHFT                                              0x0

#define HWIO_FT_SEQ_BRANCH_ADDRq_ADDR(q)                                                (BCM_FT_REG_BASE      + 0x00000250 + 0x4 * (q))
#define HWIO_FT_SEQ_BRANCH_ADDRq_RMSK                                                         0xff
#define HWIO_FT_SEQ_BRANCH_ADDRq_MAXq                                                           31
#define HWIO_FT_SEQ_BRANCH_ADDRq_INI(q)        \
        in_dword_masked(HWIO_FT_SEQ_BRANCH_ADDRq_ADDR(q), HWIO_FT_SEQ_BRANCH_ADDRq_RMSK)
#define HWIO_FT_SEQ_BRANCH_ADDRq_INMI(q,mask)    \
        in_dword_masked(HWIO_FT_SEQ_BRANCH_ADDRq_ADDR(q), mask)
#define HWIO_FT_SEQ_BRANCH_ADDRq_OUTI(q,val)    \
        out_dword(HWIO_FT_SEQ_BRANCH_ADDRq_ADDR(q),val)
#define HWIO_FT_SEQ_BRANCH_ADDRq_OUTMI(q,mask,val) \
        out_dword_masked_ns(HWIO_FT_SEQ_BRANCH_ADDRq_ADDR(q),mask,val,HWIO_FT_SEQ_BRANCH_ADDRq_INI(q))
#define HWIO_FT_SEQ_BRANCH_ADDRq_BRANCH_ADDR_BMSK                                             0xff
#define HWIO_FT_SEQ_BRANCH_ADDRq_BRANCH_ADDR_SHFT                                              0x0

#define HWIO_FT_SEQ_PWR_CTRL_STAT_BIT_31_TO_0_ADDR                                      (BCM_FT_REG_BASE      + 0x00000448)
#define HWIO_FT_SEQ_PWR_CTRL_STAT_BIT_31_TO_0_RMSK                                      0xffffffff
#define HWIO_FT_SEQ_PWR_CTRL_STAT_BIT_31_TO_0_IN          \
        in_dword(HWIO_FT_SEQ_PWR_CTRL_STAT_BIT_31_TO_0_ADDR)
#define HWIO_FT_SEQ_PWR_CTRL_STAT_BIT_31_TO_0_INM(m)      \
        in_dword_masked(HWIO_FT_SEQ_PWR_CTRL_STAT_BIT_31_TO_0_ADDR, m)
#define HWIO_FT_SEQ_PWR_CTRL_STAT_BIT_31_TO_0_PWR_CTRL_31_TO_0_BMSK                     0xffffffff
#define HWIO_FT_SEQ_PWR_CTRL_STAT_BIT_31_TO_0_PWR_CTRL_31_TO_0_SHFT                            0x0

#define HWIO_FT_SEQ_WAIT_EV_STAT_BIT_31_TO_0_ADDR                                       (BCM_FT_REG_BASE      + 0x00000450)
#define HWIO_FT_SEQ_WAIT_EV_STAT_BIT_31_TO_0_RMSK                                       0xffffffff
#define HWIO_FT_SEQ_WAIT_EV_STAT_BIT_31_TO_0_IN          \
        in_dword(HWIO_FT_SEQ_WAIT_EV_STAT_BIT_31_TO_0_ADDR)
#define HWIO_FT_SEQ_WAIT_EV_STAT_BIT_31_TO_0_INM(m)      \
        in_dword_masked(HWIO_FT_SEQ_WAIT_EV_STAT_BIT_31_TO_0_ADDR, m)
#define HWIO_FT_SEQ_WAIT_EV_STAT_BIT_31_TO_0_WAIT_EV_31_TO_0_BMSK                       0xffffffff
#define HWIO_FT_SEQ_WAIT_EV_STAT_BIT_31_TO_0_WAIT_EV_31_TO_0_SHFT                              0x0

#define HWIO_FT_SEQ_BR_EV_STAT_ADDR                                                     (BCM_FT_REG_BASE      + 0x00000458)
#define HWIO_FT_SEQ_BR_EV_STAT_RMSK                                                     0xffffffff
#define HWIO_FT_SEQ_BR_EV_STAT_IN          \
        in_dword(HWIO_FT_SEQ_BR_EV_STAT_ADDR)
#define HWIO_FT_SEQ_BR_EV_STAT_INM(m)      \
        in_dword_masked(HWIO_FT_SEQ_BR_EV_STAT_ADDR, m)
#define HWIO_FT_SEQ_BR_EV_STAT_BITS_BMSK                                                0xffffffff
#define HWIO_FT_SEQ_BR_EV_STAT_BITS_SHFT                                                       0x0

#define HWIO_FT_SEQ_RF_OUT_STATUSq_ADDR(q)                                              (BCM_FT_REG_BASE      + 0x0000045c + 0x4 * (q))
#define HWIO_FT_SEQ_RF_OUT_STATUSq_RMSK                                                 0xffffffff
#define HWIO_FT_SEQ_RF_OUT_STATUSq_MAXq                                                         15
#define HWIO_FT_SEQ_RF_OUT_STATUSq_INI(q)        \
        in_dword_masked(HWIO_FT_SEQ_RF_OUT_STATUSq_ADDR(q), HWIO_FT_SEQ_RF_OUT_STATUSq_RMSK)
#define HWIO_FT_SEQ_RF_OUT_STATUSq_INMI(q,mask)    \
        in_dword_masked(HWIO_FT_SEQ_RF_OUT_STATUSq_ADDR(q), mask)
#define HWIO_FT_SEQ_RF_OUT_STATUSq_BITS_BMSK                                            0xffffffff
#define HWIO_FT_SEQ_RF_OUT_STATUSq_BITS_SHFT                                                   0x0

#define HWIO_FT_SEQ_BRANCH_EVENT_SW_ADDR                                                (BCM_FT_REG_BASE      + 0x000004a0)
#define HWIO_FT_SEQ_BRANCH_EVENT_SW_RMSK                                                       0xf
#define HWIO_FT_SEQ_BRANCH_EVENT_SW_IN          \
        in_dword(HWIO_FT_SEQ_BRANCH_EVENT_SW_ADDR)
#define HWIO_FT_SEQ_BRANCH_EVENT_SW_INM(m)      \
        in_dword_masked(HWIO_FT_SEQ_BRANCH_EVENT_SW_ADDR, m)
#define HWIO_FT_SEQ_BRANCH_EVENT_SW_OUT(v)      \
        out_dword(HWIO_FT_SEQ_BRANCH_EVENT_SW_ADDR,v)
#define HWIO_FT_SEQ_BRANCH_EVENT_SW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_SEQ_BRANCH_EVENT_SW_ADDR,m,v,HWIO_FT_SEQ_BRANCH_EVENT_SW_IN)
#define HWIO_FT_SEQ_BRANCH_EVENT_SW_BITS_BMSK                                                  0xf
#define HWIO_FT_SEQ_BRANCH_EVENT_SW_BITS_SHFT                                                  0x0

#define HWIO_FT_SEQ_WAIT_EVENT_SW_ADDR                                                  (BCM_FT_REG_BASE      + 0x000004a4)
#define HWIO_FT_SEQ_WAIT_EVENT_SW_RMSK                                                      0xffff
#define HWIO_FT_SEQ_WAIT_EVENT_SW_IN          \
        in_dword(HWIO_FT_SEQ_WAIT_EVENT_SW_ADDR)
#define HWIO_FT_SEQ_WAIT_EVENT_SW_INM(m)      \
        in_dword_masked(HWIO_FT_SEQ_WAIT_EVENT_SW_ADDR, m)
#define HWIO_FT_SEQ_WAIT_EVENT_SW_OUT(v)      \
        out_dword(HWIO_FT_SEQ_WAIT_EVENT_SW_ADDR,v)
#define HWIO_FT_SEQ_WAIT_EVENT_SW_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_SEQ_WAIT_EVENT_SW_ADDR,m,v,HWIO_FT_SEQ_WAIT_EVENT_SW_IN)
#define HWIO_FT_SEQ_WAIT_EVENT_SW_BITS_BMSK                                                 0xffff
#define HWIO_FT_SEQ_WAIT_EVENT_SW_BITS_SHFT                                                    0x0

#define HWIO_FT_MAX_CP_ADDR                                                             (BCM_FT_REG_BASE      + 0x000004a8)
#define HWIO_FT_MAX_CP_RMSK                                                                   0xff
#define HWIO_FT_MAX_CP_IN          \
        in_dword(HWIO_FT_MAX_CP_ADDR)
#define HWIO_FT_MAX_CP_INM(m)      \
        in_dword_masked(HWIO_FT_MAX_CP_ADDR, m)
#define HWIO_FT_MAX_CP_OUT(v)      \
        out_dword(HWIO_FT_MAX_CP_ADDR,v)
#define HWIO_FT_MAX_CP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_MAX_CP_ADDR,m,v,HWIO_FT_MAX_CP_IN)
#define HWIO_FT_MAX_CP_SHUB_BMSK                                                              0xf0
#define HWIO_FT_MAX_CP_SHUB_SHFT                                                               0x4
#define HWIO_FT_MAX_CP_MC_BMSK                                                                 0xf
#define HWIO_FT_MAX_CP_MC_SHFT                                                                 0x0

#define HWIO_FT_BIN_MAP_DRVm_ADDR(m)                                                    (BCM_FT_REG_BASE      + 0x000004ac + 0x4 * (m))
#define HWIO_FT_BIN_MAP_DRVm_RMSK                                                              0x3
#define HWIO_FT_BIN_MAP_DRVm_MAXm                                                               23
#define HWIO_FT_BIN_MAP_DRVm_INI(m)        \
        in_dword_masked(HWIO_FT_BIN_MAP_DRVm_ADDR(m), HWIO_FT_BIN_MAP_DRVm_RMSK)
#define HWIO_FT_BIN_MAP_DRVm_INMI(m,mask)    \
        in_dword_masked(HWIO_FT_BIN_MAP_DRVm_ADDR(m), mask)
#define HWIO_FT_BIN_MAP_DRVm_OUTI(m,val)    \
        out_dword(HWIO_FT_BIN_MAP_DRVm_ADDR(m),val)
#define HWIO_FT_BIN_MAP_DRVm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_FT_BIN_MAP_DRVm_ADDR(m),mask,val,HWIO_FT_BIN_MAP_DRVm_INI(m))
#define HWIO_FT_BIN_MAP_DRVm_BIN_ID_BMSK                                                       0x3
#define HWIO_FT_BIN_MAP_DRVm_BIN_ID_SHFT                                                       0x0

#define HWIO_FT_MAX_BC_MC_CPn_ADDR(n)                                                   (BCM_FT_REG_BASE      + 0x0000052c + 0x4 * (n))
#define HWIO_FT_MAX_BC_MC_CPn_RMSK                                                          0xffff
#define HWIO_FT_MAX_BC_MC_CPn_MAXn                                                              15
#define HWIO_FT_MAX_BC_MC_CPn_INI(n)        \
        in_dword_masked(HWIO_FT_MAX_BC_MC_CPn_ADDR(n), HWIO_FT_MAX_BC_MC_CPn_RMSK)
#define HWIO_FT_MAX_BC_MC_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_MAX_BC_MC_CPn_ADDR(n), mask)
#define HWIO_FT_MAX_BC_MC_CPn_OUTI(n,val)    \
        out_dword(HWIO_FT_MAX_BC_MC_CPn_ADDR(n),val)
#define HWIO_FT_MAX_BC_MC_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_MAX_BC_MC_CPn_ADDR(n),mask,val,HWIO_FT_MAX_BC_MC_CPn_INI(n))
#define HWIO_FT_MAX_BC_MC_CPn_BYTE_COUNT_BMSK                                               0xffff
#define HWIO_FT_MAX_BC_MC_CPn_BYTE_COUNT_SHFT                                                  0x0

#define HWIO_FT_MAX_BC_SHUB_CPn_ADDR(n)                                                 (BCM_FT_REG_BASE      + 0x0000056c + 0x4 * (n))
#define HWIO_FT_MAX_BC_SHUB_CPn_RMSK                                                        0xffff
#define HWIO_FT_MAX_BC_SHUB_CPn_MAXn                                                             7
#define HWIO_FT_MAX_BC_SHUB_CPn_INI(n)        \
        in_dword_masked(HWIO_FT_MAX_BC_SHUB_CPn_ADDR(n), HWIO_FT_MAX_BC_SHUB_CPn_RMSK)
#define HWIO_FT_MAX_BC_SHUB_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_MAX_BC_SHUB_CPn_ADDR(n), mask)
#define HWIO_FT_MAX_BC_SHUB_CPn_OUTI(n,val)    \
        out_dword(HWIO_FT_MAX_BC_SHUB_CPn_ADDR(n),val)
#define HWIO_FT_MAX_BC_SHUB_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_MAX_BC_SHUB_CPn_ADDR(n),mask,val,HWIO_FT_MAX_BC_SHUB_CPn_INI(n))
#define HWIO_FT_MAX_BC_SHUB_CPn_BYTE_COUNT_BMSK                                             0xffff
#define HWIO_FT_MAX_BC_SHUB_CPn_BYTE_COUNT_SHFT                                                0x0

#define HWIO_FT_UTIL_TH_MC_BINn_ADDR(n)                                                 (BCM_FT_REG_BASE      + 0x000005ac + 0x4 * (n))
#define HWIO_FT_UTIL_TH_MC_BINn_RMSK                                                      0xffffff
#define HWIO_FT_UTIL_TH_MC_BINn_MAXn                                                             3
#define HWIO_FT_UTIL_TH_MC_BINn_INI(n)        \
        in_dword_masked(HWIO_FT_UTIL_TH_MC_BINn_ADDR(n), HWIO_FT_UTIL_TH_MC_BINn_RMSK)
#define HWIO_FT_UTIL_TH_MC_BINn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_UTIL_TH_MC_BINn_ADDR(n), mask)
#define HWIO_FT_UTIL_TH_MC_BINn_OUTI(n,val)    \
        out_dword(HWIO_FT_UTIL_TH_MC_BINn_ADDR(n),val)
#define HWIO_FT_UTIL_TH_MC_BINn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_UTIL_TH_MC_BINn_ADDR(n),mask,val,HWIO_FT_UTIL_TH_MC_BINn_INI(n))
#define HWIO_FT_UTIL_TH_MC_BINn_UP_BMSK                                                   0xff0000
#define HWIO_FT_UTIL_TH_MC_BINn_UP_SHFT                                                       0x10
#define HWIO_FT_UTIL_TH_MC_BINn_DN_BMSK                                                     0xff00
#define HWIO_FT_UTIL_TH_MC_BINn_DN_SHFT                                                        0x8
#define HWIO_FT_UTIL_TH_MC_BINn_DN2_BMSK                                                      0xff
#define HWIO_FT_UTIL_TH_MC_BINn_DN2_SHFT                                                       0x0

#define HWIO_FT_UTIL_TH_SHUB_BINn_ADDR(n)                                               (BCM_FT_REG_BASE      + 0x000005bc + 0x4 * (n))
#define HWIO_FT_UTIL_TH_SHUB_BINn_RMSK                                                    0xffffff
#define HWIO_FT_UTIL_TH_SHUB_BINn_MAXn                                                           3
#define HWIO_FT_UTIL_TH_SHUB_BINn_INI(n)        \
        in_dword_masked(HWIO_FT_UTIL_TH_SHUB_BINn_ADDR(n), HWIO_FT_UTIL_TH_SHUB_BINn_RMSK)
#define HWIO_FT_UTIL_TH_SHUB_BINn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_UTIL_TH_SHUB_BINn_ADDR(n), mask)
#define HWIO_FT_UTIL_TH_SHUB_BINn_OUTI(n,val)    \
        out_dword(HWIO_FT_UTIL_TH_SHUB_BINn_ADDR(n),val)
#define HWIO_FT_UTIL_TH_SHUB_BINn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_UTIL_TH_SHUB_BINn_ADDR(n),mask,val,HWIO_FT_UTIL_TH_SHUB_BINn_INI(n))
#define HWIO_FT_UTIL_TH_SHUB_BINn_UP_BMSK                                                 0xff0000
#define HWIO_FT_UTIL_TH_SHUB_BINn_UP_SHFT                                                     0x10
#define HWIO_FT_UTIL_TH_SHUB_BINn_DN_BMSK                                                   0xff00
#define HWIO_FT_UTIL_TH_SHUB_BINn_DN_SHFT                                                      0x8
#define HWIO_FT_UTIL_TH_SHUB_BINn_DN2_BMSK                                                    0xff
#define HWIO_FT_UTIL_TH_SHUB_BINn_DN2_SHFT                                                     0x0

#define HWIO_FT_MOD_DEPTH_MC_BINn_ADDR(n)                                               (BCM_FT_REG_BASE      + 0x000005cc + 0x4 * (n))
#define HWIO_FT_MOD_DEPTH_MC_BINn_RMSK                                                     0xf0f0f
#define HWIO_FT_MOD_DEPTH_MC_BINn_MAXn                                                           3
#define HWIO_FT_MOD_DEPTH_MC_BINn_INI(n)        \
        in_dword_masked(HWIO_FT_MOD_DEPTH_MC_BINn_ADDR(n), HWIO_FT_MOD_DEPTH_MC_BINn_RMSK)
#define HWIO_FT_MOD_DEPTH_MC_BINn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_MOD_DEPTH_MC_BINn_ADDR(n), mask)
#define HWIO_FT_MOD_DEPTH_MC_BINn_OUTI(n,val)    \
        out_dword(HWIO_FT_MOD_DEPTH_MC_BINn_ADDR(n),val)
#define HWIO_FT_MOD_DEPTH_MC_BINn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_MOD_DEPTH_MC_BINn_ADDR(n),mask,val,HWIO_FT_MOD_DEPTH_MC_BINn_INI(n))
#define HWIO_FT_MOD_DEPTH_MC_BINn_UP_BMSK                                                  0xf0000
#define HWIO_FT_MOD_DEPTH_MC_BINn_UP_SHFT                                                     0x10
#define HWIO_FT_MOD_DEPTH_MC_BINn_DN_BMSK                                                    0xf00
#define HWIO_FT_MOD_DEPTH_MC_BINn_DN_SHFT                                                      0x8
#define HWIO_FT_MOD_DEPTH_MC_BINn_DN2_BMSK                                                     0xf
#define HWIO_FT_MOD_DEPTH_MC_BINn_DN2_SHFT                                                     0x0

#define HWIO_FT_MOD_DEPTH_SHUB_BINn_ADDR(n)                                             (BCM_FT_REG_BASE      + 0x000005dc + 0x4 * (n))
#define HWIO_FT_MOD_DEPTH_SHUB_BINn_RMSK                                                   0xf0f0f
#define HWIO_FT_MOD_DEPTH_SHUB_BINn_MAXn                                                         3
#define HWIO_FT_MOD_DEPTH_SHUB_BINn_INI(n)        \
        in_dword_masked(HWIO_FT_MOD_DEPTH_SHUB_BINn_ADDR(n), HWIO_FT_MOD_DEPTH_SHUB_BINn_RMSK)
#define HWIO_FT_MOD_DEPTH_SHUB_BINn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_MOD_DEPTH_SHUB_BINn_ADDR(n), mask)
#define HWIO_FT_MOD_DEPTH_SHUB_BINn_OUTI(n,val)    \
        out_dword(HWIO_FT_MOD_DEPTH_SHUB_BINn_ADDR(n),val)
#define HWIO_FT_MOD_DEPTH_SHUB_BINn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_MOD_DEPTH_SHUB_BINn_ADDR(n),mask,val,HWIO_FT_MOD_DEPTH_SHUB_BINn_INI(n))
#define HWIO_FT_MOD_DEPTH_SHUB_BINn_UP_BMSK                                                0xf0000
#define HWIO_FT_MOD_DEPTH_SHUB_BINn_UP_SHFT                                                   0x10
#define HWIO_FT_MOD_DEPTH_SHUB_BINn_DN_BMSK                                                  0xf00
#define HWIO_FT_MOD_DEPTH_SHUB_BINn_DN_SHFT                                                    0x8
#define HWIO_FT_MOD_DEPTH_SHUB_BINn_DN2_BMSK                                                   0xf
#define HWIO_FT_MOD_DEPTH_SHUB_BINn_DN2_SHFT                                                   0x0

#define HWIO_FT_BMCP_DEPTH_MC_DRVm_ADDR(m)                                              (BCM_FT_REG_BASE      + 0x000005ec + 0x4 * (m))
#define HWIO_FT_BMCP_DEPTH_MC_DRVm_RMSK                                                      0xf0f
#define HWIO_FT_BMCP_DEPTH_MC_DRVm_MAXm                                                         23
#define HWIO_FT_BMCP_DEPTH_MC_DRVm_INI(m)        \
        in_dword_masked(HWIO_FT_BMCP_DEPTH_MC_DRVm_ADDR(m), HWIO_FT_BMCP_DEPTH_MC_DRVm_RMSK)
#define HWIO_FT_BMCP_DEPTH_MC_DRVm_INMI(m,mask)    \
        in_dword_masked(HWIO_FT_BMCP_DEPTH_MC_DRVm_ADDR(m), mask)
#define HWIO_FT_BMCP_DEPTH_MC_DRVm_OUTI(m,val)    \
        out_dword(HWIO_FT_BMCP_DEPTH_MC_DRVm_ADDR(m),val)
#define HWIO_FT_BMCP_DEPTH_MC_DRVm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_FT_BMCP_DEPTH_MC_DRVm_ADDR(m),mask,val,HWIO_FT_BMCP_DEPTH_MC_DRVm_INI(m))
#define HWIO_FT_BMCP_DEPTH_MC_DRVm_UP_BMSK                                                   0xf00
#define HWIO_FT_BMCP_DEPTH_MC_DRVm_UP_SHFT                                                     0x8
#define HWIO_FT_BMCP_DEPTH_MC_DRVm_DN_BMSK                                                     0xf
#define HWIO_FT_BMCP_DEPTH_MC_DRVm_DN_SHFT                                                     0x0

#define HWIO_FT_BMCP_DEPTH_SHUB_DRVm_ADDR(m)                                            (BCM_FT_REG_BASE      + 0x0000066c + 0x4 * (m))
#define HWIO_FT_BMCP_DEPTH_SHUB_DRVm_RMSK                                                    0xf0f
#define HWIO_FT_BMCP_DEPTH_SHUB_DRVm_MAXm                                                       23
#define HWIO_FT_BMCP_DEPTH_SHUB_DRVm_INI(m)        \
        in_dword_masked(HWIO_FT_BMCP_DEPTH_SHUB_DRVm_ADDR(m), HWIO_FT_BMCP_DEPTH_SHUB_DRVm_RMSK)
#define HWIO_FT_BMCP_DEPTH_SHUB_DRVm_INMI(m,mask)    \
        in_dword_masked(HWIO_FT_BMCP_DEPTH_SHUB_DRVm_ADDR(m), mask)
#define HWIO_FT_BMCP_DEPTH_SHUB_DRVm_OUTI(m,val)    \
        out_dword(HWIO_FT_BMCP_DEPTH_SHUB_DRVm_ADDR(m),val)
#define HWIO_FT_BMCP_DEPTH_SHUB_DRVm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_FT_BMCP_DEPTH_SHUB_DRVm_ADDR(m),mask,val,HWIO_FT_BMCP_DEPTH_SHUB_DRVm_INI(m))
#define HWIO_FT_BMCP_DEPTH_SHUB_DRVm_UP_BMSK                                                 0xf00
#define HWIO_FT_BMCP_DEPTH_SHUB_DRVm_UP_SHFT                                                   0x8
#define HWIO_FT_BMCP_DEPTH_SHUB_DRVm_DN_BMSK                                                   0xf
#define HWIO_FT_BMCP_DEPTH_SHUB_DRVm_DN_SHFT                                                   0x0

#define HWIO_FT_AB2CP_LUT_MC_CPn_ADDR(n)                                                (BCM_FT_REG_BASE      + 0x000006ec + 0x4 * (n))
#define HWIO_FT_AB2CP_LUT_MC_CPn_RMSK                                                       0x3fff
#define HWIO_FT_AB2CP_LUT_MC_CPn_MAXn                                                           15
#define HWIO_FT_AB2CP_LUT_MC_CPn_INI(n)        \
        in_dword_masked(HWIO_FT_AB2CP_LUT_MC_CPn_ADDR(n), HWIO_FT_AB2CP_LUT_MC_CPn_RMSK)
#define HWIO_FT_AB2CP_LUT_MC_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_AB2CP_LUT_MC_CPn_ADDR(n), mask)
#define HWIO_FT_AB2CP_LUT_MC_CPn_OUTI(n,val)    \
        out_dword(HWIO_FT_AB2CP_LUT_MC_CPn_ADDR(n),val)
#define HWIO_FT_AB2CP_LUT_MC_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_AB2CP_LUT_MC_CPn_ADDR(n),mask,val,HWIO_FT_AB2CP_LUT_MC_CPn_INI(n))
#define HWIO_FT_AB2CP_LUT_MC_CPn_TH_BMSK                                                    0x3fff
#define HWIO_FT_AB2CP_LUT_MC_CPn_TH_SHFT                                                       0x0

#define HWIO_FT_AB2CP_LUT_SHUB_CPn_ADDR(n)                                              (BCM_FT_REG_BASE      + 0x0000072c + 0x4 * (n))
#define HWIO_FT_AB2CP_LUT_SHUB_CPn_RMSK                                                     0x3fff
#define HWIO_FT_AB2CP_LUT_SHUB_CPn_MAXn                                                          7
#define HWIO_FT_AB2CP_LUT_SHUB_CPn_INI(n)        \
        in_dword_masked(HWIO_FT_AB2CP_LUT_SHUB_CPn_ADDR(n), HWIO_FT_AB2CP_LUT_SHUB_CPn_RMSK)
#define HWIO_FT_AB2CP_LUT_SHUB_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_AB2CP_LUT_SHUB_CPn_ADDR(n), mask)
#define HWIO_FT_AB2CP_LUT_SHUB_CPn_OUTI(n,val)    \
        out_dword(HWIO_FT_AB2CP_LUT_SHUB_CPn_ADDR(n),val)
#define HWIO_FT_AB2CP_LUT_SHUB_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_AB2CP_LUT_SHUB_CPn_ADDR(n),mask,val,HWIO_FT_AB2CP_LUT_SHUB_CPn_INI(n))
#define HWIO_FT_AB2CP_LUT_SHUB_CPn_TH_BMSK                                                  0x3fff
#define HWIO_FT_AB2CP_LUT_SHUB_CPn_TH_SHFT                                                     0x0

#define HWIO_FT_BC2CP_LUT_MC_CPn_ADDR(n)                                                (BCM_FT_REG_BASE      + 0x0000076c + 0x4 * (n))
#define HWIO_FT_BC2CP_LUT_MC_CPn_RMSK                                                       0xffff
#define HWIO_FT_BC2CP_LUT_MC_CPn_MAXn                                                           15
#define HWIO_FT_BC2CP_LUT_MC_CPn_INI(n)        \
        in_dword_masked(HWIO_FT_BC2CP_LUT_MC_CPn_ADDR(n), HWIO_FT_BC2CP_LUT_MC_CPn_RMSK)
#define HWIO_FT_BC2CP_LUT_MC_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_BC2CP_LUT_MC_CPn_ADDR(n), mask)
#define HWIO_FT_BC2CP_LUT_MC_CPn_OUTI(n,val)    \
        out_dword(HWIO_FT_BC2CP_LUT_MC_CPn_ADDR(n),val)
#define HWIO_FT_BC2CP_LUT_MC_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_BC2CP_LUT_MC_CPn_ADDR(n),mask,val,HWIO_FT_BC2CP_LUT_MC_CPn_INI(n))
#define HWIO_FT_BC2CP_LUT_MC_CPn_TH_BMSK                                                    0xffff
#define HWIO_FT_BC2CP_LUT_MC_CPn_TH_SHFT                                                       0x0

#define HWIO_FT_BC2CP_LUT_SHUB_CPn_ADDR(n)                                              (BCM_FT_REG_BASE      + 0x000007ac + 0x4 * (n))
#define HWIO_FT_BC2CP_LUT_SHUB_CPn_RMSK                                                     0xffff
#define HWIO_FT_BC2CP_LUT_SHUB_CPn_MAXn                                                          7
#define HWIO_FT_BC2CP_LUT_SHUB_CPn_INI(n)        \
        in_dword_masked(HWIO_FT_BC2CP_LUT_SHUB_CPn_ADDR(n), HWIO_FT_BC2CP_LUT_SHUB_CPn_RMSK)
#define HWIO_FT_BC2CP_LUT_SHUB_CPn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_BC2CP_LUT_SHUB_CPn_ADDR(n), mask)
#define HWIO_FT_BC2CP_LUT_SHUB_CPn_OUTI(n,val)    \
        out_dword(HWIO_FT_BC2CP_LUT_SHUB_CPn_ADDR(n),val)
#define HWIO_FT_BC2CP_LUT_SHUB_CPn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_BC2CP_LUT_SHUB_CPn_ADDR(n),mask,val,HWIO_FT_BC2CP_LUT_SHUB_CPn_INI(n))
#define HWIO_FT_BC2CP_LUT_SHUB_CPn_TH_BMSK                                                  0xffff
#define HWIO_FT_BC2CP_LUT_SHUB_CPn_TH_SHFT                                                     0x0

#define HWIO_FT_OVERRIDE_VOTE_MC_DRVn_ADDR(n)                                           (BCM_FT_REG_BASE      + 0x000007ec + 0x4 * (n))
#define HWIO_FT_OVERRIDE_VOTE_MC_DRVn_RMSK                                              0x3fff3fff
#define HWIO_FT_OVERRIDE_VOTE_MC_DRVn_MAXn                                                      23
#define HWIO_FT_OVERRIDE_VOTE_MC_DRVn_INI(n)        \
        in_dword_masked(HWIO_FT_OVERRIDE_VOTE_MC_DRVn_ADDR(n), HWIO_FT_OVERRIDE_VOTE_MC_DRVn_RMSK)
#define HWIO_FT_OVERRIDE_VOTE_MC_DRVn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_OVERRIDE_VOTE_MC_DRVn_ADDR(n), mask)
#define HWIO_FT_OVERRIDE_VOTE_MC_DRVn_OUTI(n,val)    \
        out_dword(HWIO_FT_OVERRIDE_VOTE_MC_DRVn_ADDR(n),val)
#define HWIO_FT_OVERRIDE_VOTE_MC_DRVn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_OVERRIDE_VOTE_MC_DRVn_ADDR(n),mask,val,HWIO_FT_OVERRIDE_VOTE_MC_DRVn_INI(n))
#define HWIO_FT_OVERRIDE_VOTE_MC_DRVn_AB_BMSK                                           0x3fff0000
#define HWIO_FT_OVERRIDE_VOTE_MC_DRVn_AB_SHFT                                                 0x10
#define HWIO_FT_OVERRIDE_VOTE_MC_DRVn_IB_BMSK                                               0x3fff
#define HWIO_FT_OVERRIDE_VOTE_MC_DRVn_IB_SHFT                                                  0x0

#define HWIO_FT_OVERRIDE_VOTE_SHUB_DRVn_ADDR(n)                                         (BCM_FT_REG_BASE      + 0x0000086c + 0x4 * (n))
#define HWIO_FT_OVERRIDE_VOTE_SHUB_DRVn_RMSK                                            0x3fff3fff
#define HWIO_FT_OVERRIDE_VOTE_SHUB_DRVn_MAXn                                                    23
#define HWIO_FT_OVERRIDE_VOTE_SHUB_DRVn_INI(n)        \
        in_dword_masked(HWIO_FT_OVERRIDE_VOTE_SHUB_DRVn_ADDR(n), HWIO_FT_OVERRIDE_VOTE_SHUB_DRVn_RMSK)
#define HWIO_FT_OVERRIDE_VOTE_SHUB_DRVn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_OVERRIDE_VOTE_SHUB_DRVn_ADDR(n), mask)
#define HWIO_FT_OVERRIDE_VOTE_SHUB_DRVn_OUTI(n,val)    \
        out_dword(HWIO_FT_OVERRIDE_VOTE_SHUB_DRVn_ADDR(n),val)
#define HWIO_FT_OVERRIDE_VOTE_SHUB_DRVn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_OVERRIDE_VOTE_SHUB_DRVn_ADDR(n),mask,val,HWIO_FT_OVERRIDE_VOTE_SHUB_DRVn_INI(n))
#define HWIO_FT_OVERRIDE_VOTE_SHUB_DRVn_AB_BMSK                                         0x3fff0000
#define HWIO_FT_OVERRIDE_VOTE_SHUB_DRVn_AB_SHFT                                               0x10
#define HWIO_FT_OVERRIDE_VOTE_SHUB_DRVn_IB_BMSK                                             0x3fff
#define HWIO_FT_OVERRIDE_VOTE_SHUB_DRVn_IB_SHFT                                                0x0

#define HWIO_FT_OVERRIDE_AB_FT_MC_DRVn_ADDR(n)                                          (BCM_FT_REG_BASE      + 0x000008ec + 0x4 * (n))
#define HWIO_FT_OVERRIDE_AB_FT_MC_DRVn_RMSK                                                   0x71
#define HWIO_FT_OVERRIDE_AB_FT_MC_DRVn_MAXn                                                     23
#define HWIO_FT_OVERRIDE_AB_FT_MC_DRVn_INI(n)        \
        in_dword_masked(HWIO_FT_OVERRIDE_AB_FT_MC_DRVn_ADDR(n), HWIO_FT_OVERRIDE_AB_FT_MC_DRVn_RMSK)
#define HWIO_FT_OVERRIDE_AB_FT_MC_DRVn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_OVERRIDE_AB_FT_MC_DRVn_ADDR(n), mask)
#define HWIO_FT_OVERRIDE_AB_FT_MC_DRVn_OUTI(n,val)    \
        out_dword(HWIO_FT_OVERRIDE_AB_FT_MC_DRVn_ADDR(n),val)
#define HWIO_FT_OVERRIDE_AB_FT_MC_DRVn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_OVERRIDE_AB_FT_MC_DRVn_ADDR(n),mask,val,HWIO_FT_OVERRIDE_AB_FT_MC_DRVn_INI(n))
#define HWIO_FT_OVERRIDE_AB_FT_MC_DRVn_SEL_BMSK                                               0x70
#define HWIO_FT_OVERRIDE_AB_FT_MC_DRVn_SEL_SHFT                                                0x4
#define HWIO_FT_OVERRIDE_AB_FT_MC_DRVn_EN_BMSK                                                 0x1
#define HWIO_FT_OVERRIDE_AB_FT_MC_DRVn_EN_SHFT                                                 0x0

#define HWIO_FT_OVERRIDE_AB_FT_SHUB_DRVn_ADDR(n)                                        (BCM_FT_REG_BASE      + 0x0000096c + 0x4 * (n))
#define HWIO_FT_OVERRIDE_AB_FT_SHUB_DRVn_RMSK                                                 0x71
#define HWIO_FT_OVERRIDE_AB_FT_SHUB_DRVn_MAXn                                                   23
#define HWIO_FT_OVERRIDE_AB_FT_SHUB_DRVn_INI(n)        \
        in_dword_masked(HWIO_FT_OVERRIDE_AB_FT_SHUB_DRVn_ADDR(n), HWIO_FT_OVERRIDE_AB_FT_SHUB_DRVn_RMSK)
#define HWIO_FT_OVERRIDE_AB_FT_SHUB_DRVn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_OVERRIDE_AB_FT_SHUB_DRVn_ADDR(n), mask)
#define HWIO_FT_OVERRIDE_AB_FT_SHUB_DRVn_OUTI(n,val)    \
        out_dword(HWIO_FT_OVERRIDE_AB_FT_SHUB_DRVn_ADDR(n),val)
#define HWIO_FT_OVERRIDE_AB_FT_SHUB_DRVn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_OVERRIDE_AB_FT_SHUB_DRVn_ADDR(n),mask,val,HWIO_FT_OVERRIDE_AB_FT_SHUB_DRVn_INI(n))
#define HWIO_FT_OVERRIDE_AB_FT_SHUB_DRVn_SEL_BMSK                                             0x70
#define HWIO_FT_OVERRIDE_AB_FT_SHUB_DRVn_SEL_SHFT                                              0x4
#define HWIO_FT_OVERRIDE_AB_FT_SHUB_DRVn_EN_BMSK                                               0x1
#define HWIO_FT_OVERRIDE_AB_FT_SHUB_DRVn_EN_SHFT                                               0x0

#define HWIO_FT_OVERRIDE_IB_FT_MC_DRVn_ADDR(n)                                          (BCM_FT_REG_BASE      + 0x000009ec + 0x4 * (n))
#define HWIO_FT_OVERRIDE_IB_FT_MC_DRVn_RMSK                                                   0x71
#define HWIO_FT_OVERRIDE_IB_FT_MC_DRVn_MAXn                                                     23
#define HWIO_FT_OVERRIDE_IB_FT_MC_DRVn_INI(n)        \
        in_dword_masked(HWIO_FT_OVERRIDE_IB_FT_MC_DRVn_ADDR(n), HWIO_FT_OVERRIDE_IB_FT_MC_DRVn_RMSK)
#define HWIO_FT_OVERRIDE_IB_FT_MC_DRVn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_OVERRIDE_IB_FT_MC_DRVn_ADDR(n), mask)
#define HWIO_FT_OVERRIDE_IB_FT_MC_DRVn_OUTI(n,val)    \
        out_dword(HWIO_FT_OVERRIDE_IB_FT_MC_DRVn_ADDR(n),val)
#define HWIO_FT_OVERRIDE_IB_FT_MC_DRVn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_OVERRIDE_IB_FT_MC_DRVn_ADDR(n),mask,val,HWIO_FT_OVERRIDE_IB_FT_MC_DRVn_INI(n))
#define HWIO_FT_OVERRIDE_IB_FT_MC_DRVn_SEL_BMSK                                               0x70
#define HWIO_FT_OVERRIDE_IB_FT_MC_DRVn_SEL_SHFT                                                0x4
#define HWIO_FT_OVERRIDE_IB_FT_MC_DRVn_EN_BMSK                                                 0x1
#define HWIO_FT_OVERRIDE_IB_FT_MC_DRVn_EN_SHFT                                                 0x0

#define HWIO_FT_OVERRIDE_IB_FT_SHUB_DRVn_ADDR(n)                                        (BCM_FT_REG_BASE      + 0x00000a6c + 0x4 * (n))
#define HWIO_FT_OVERRIDE_IB_FT_SHUB_DRVn_RMSK                                                 0x71
#define HWIO_FT_OVERRIDE_IB_FT_SHUB_DRVn_MAXn                                                   23
#define HWIO_FT_OVERRIDE_IB_FT_SHUB_DRVn_INI(n)        \
        in_dword_masked(HWIO_FT_OVERRIDE_IB_FT_SHUB_DRVn_ADDR(n), HWIO_FT_OVERRIDE_IB_FT_SHUB_DRVn_RMSK)
#define HWIO_FT_OVERRIDE_IB_FT_SHUB_DRVn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_OVERRIDE_IB_FT_SHUB_DRVn_ADDR(n), mask)
#define HWIO_FT_OVERRIDE_IB_FT_SHUB_DRVn_OUTI(n,val)    \
        out_dword(HWIO_FT_OVERRIDE_IB_FT_SHUB_DRVn_ADDR(n),val)
#define HWIO_FT_OVERRIDE_IB_FT_SHUB_DRVn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_OVERRIDE_IB_FT_SHUB_DRVn_ADDR(n),mask,val,HWIO_FT_OVERRIDE_IB_FT_SHUB_DRVn_INI(n))
#define HWIO_FT_OVERRIDE_IB_FT_SHUB_DRVn_SEL_BMSK                                             0x70
#define HWIO_FT_OVERRIDE_IB_FT_SHUB_DRVn_SEL_SHFT                                              0x4
#define HWIO_FT_OVERRIDE_IB_FT_SHUB_DRVn_EN_BMSK                                               0x1
#define HWIO_FT_OVERRIDE_IB_FT_SHUB_DRVn_EN_SHFT                                               0x0

#define HWIO_FT_UNSAFE_ALERT_ADDR                                                       (BCM_FT_REG_BASE      + 0x00000b00)
#define HWIO_FT_UNSAFE_ALERT_RMSK                                                       0xffff0001
#define HWIO_FT_UNSAFE_ALERT_IN          \
        in_dword(HWIO_FT_UNSAFE_ALERT_ADDR)
#define HWIO_FT_UNSAFE_ALERT_INM(m)      \
        in_dword_masked(HWIO_FT_UNSAFE_ALERT_ADDR, m)
#define HWIO_FT_UNSAFE_ALERT_OUT(v)      \
        out_dword(HWIO_FT_UNSAFE_ALERT_ADDR,v)
#define HWIO_FT_UNSAFE_ALERT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_UNSAFE_ALERT_ADDR,m,v,HWIO_FT_UNSAFE_ALERT_IN)
#define HWIO_FT_UNSAFE_ALERT_TH_BMSK                                                    0xffff0000
#define HWIO_FT_UNSAFE_ALERT_TH_SHFT                                                          0x10
#define HWIO_FT_UNSAFE_ALERT_EN_BMSK                                                           0x1
#define HWIO_FT_UNSAFE_ALERT_EN_SHFT                                                           0x0

#define HWIO_FT_BWMON_INT_CTRL_ADDR                                                     (BCM_FT_REG_BASE      + 0x00000b04)
#define HWIO_FT_BWMON_INT_CTRL_RMSK                                                           0xff
#define HWIO_FT_BWMON_INT_CTRL_IN          \
        in_dword(HWIO_FT_BWMON_INT_CTRL_ADDR)
#define HWIO_FT_BWMON_INT_CTRL_INM(m)      \
        in_dword_masked(HWIO_FT_BWMON_INT_CTRL_ADDR, m)
#define HWIO_FT_BWMON_INT_CTRL_OUT(v)      \
        out_dword(HWIO_FT_BWMON_INT_CTRL_ADDR,v)
#define HWIO_FT_BWMON_INT_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_BWMON_INT_CTRL_ADDR,m,v,HWIO_FT_BWMON_INT_CTRL_IN)
#define HWIO_FT_BWMON_INT_CTRL_EN_BMSK                                                        0xff
#define HWIO_FT_BWMON_INT_CTRL_EN_SHFT                                                         0x0

#define HWIO_FT_BWMON_INT_STATUS_ADDR                                                   (BCM_FT_REG_BASE      + 0x00000b08)
#define HWIO_FT_BWMON_INT_STATUS_RMSK                                                         0xff
#define HWIO_FT_BWMON_INT_STATUS_IN          \
        in_dword(HWIO_FT_BWMON_INT_STATUS_ADDR)
#define HWIO_FT_BWMON_INT_STATUS_INM(m)      \
        in_dword_masked(HWIO_FT_BWMON_INT_STATUS_ADDR, m)
#define HWIO_FT_BWMON_INT_STATUS_STATUS_BMSK                                                  0xff
#define HWIO_FT_BWMON_INT_STATUS_STATUS_SHFT                                                   0x0

#define HWIO_FT_RD_MISS_CNT_TH_ADDR                                                     (BCM_FT_REG_BASE      + 0x00000b0c)
#define HWIO_FT_RD_MISS_CNT_TH_RMSK                                                       0xffffff
#define HWIO_FT_RD_MISS_CNT_TH_IN          \
        in_dword(HWIO_FT_RD_MISS_CNT_TH_ADDR)
#define HWIO_FT_RD_MISS_CNT_TH_INM(m)      \
        in_dword_masked(HWIO_FT_RD_MISS_CNT_TH_ADDR, m)
#define HWIO_FT_RD_MISS_CNT_TH_OUT(v)      \
        out_dword(HWIO_FT_RD_MISS_CNT_TH_ADDR,v)
#define HWIO_FT_RD_MISS_CNT_TH_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_RD_MISS_CNT_TH_ADDR,m,v,HWIO_FT_RD_MISS_CNT_TH_IN)
#define HWIO_FT_RD_MISS_CNT_TH_TH_BMSK                                                    0xffffff
#define HWIO_FT_RD_MISS_CNT_TH_TH_SHFT                                                         0x0

#define HWIO_FT_BW_RATIO_TH_BINn_ADDR(n)                                                (BCM_FT_REG_BASE      + 0x00000b10 + 0x4 * (n))
#define HWIO_FT_BW_RATIO_TH_BINn_RMSK                                                         0xff
#define HWIO_FT_BW_RATIO_TH_BINn_MAXn                                                            3
#define HWIO_FT_BW_RATIO_TH_BINn_INI(n)        \
        in_dword_masked(HWIO_FT_BW_RATIO_TH_BINn_ADDR(n), HWIO_FT_BW_RATIO_TH_BINn_RMSK)
#define HWIO_FT_BW_RATIO_TH_BINn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_BW_RATIO_TH_BINn_ADDR(n), mask)
#define HWIO_FT_BW_RATIO_TH_BINn_OUTI(n,val)    \
        out_dword(HWIO_FT_BW_RATIO_TH_BINn_ADDR(n),val)
#define HWIO_FT_BW_RATIO_TH_BINn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_BW_RATIO_TH_BINn_ADDR(n),mask,val,HWIO_FT_BW_RATIO_TH_BINn_INI(n))
#define HWIO_FT_BW_RATIO_TH_BINn_TH_BMSK                                                      0xff
#define HWIO_FT_BW_RATIO_TH_BINn_TH_SHFT                                                       0x0

#define HWIO_FT_HIST_WEIGHT_MCn_ADDR(n)                                                 (BCM_FT_REG_BASE      + 0x00000b20 + 0x4 * (n))
#define HWIO_FT_HIST_WEIGHT_MCn_RMSK                                                           0x7
#define HWIO_FT_HIST_WEIGHT_MCn_MAXn                                                             7
#define HWIO_FT_HIST_WEIGHT_MCn_INI(n)        \
        in_dword_masked(HWIO_FT_HIST_WEIGHT_MCn_ADDR(n), HWIO_FT_HIST_WEIGHT_MCn_RMSK)
#define HWIO_FT_HIST_WEIGHT_MCn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_HIST_WEIGHT_MCn_ADDR(n), mask)
#define HWIO_FT_HIST_WEIGHT_MCn_OUTI(n,val)    \
        out_dword(HWIO_FT_HIST_WEIGHT_MCn_ADDR(n),val)
#define HWIO_FT_HIST_WEIGHT_MCn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_HIST_WEIGHT_MCn_ADDR(n),mask,val,HWIO_FT_HIST_WEIGHT_MCn_INI(n))
#define HWIO_FT_HIST_WEIGHT_MCn_VAL_BMSK                                                       0x7
#define HWIO_FT_HIST_WEIGHT_MCn_VAL_SHFT                                                       0x0

#define HWIO_FT_HIST_WEIGHT_SHUBn_ADDR(n)                                               (BCM_FT_REG_BASE      + 0x00000b50 + 0x4 * (n))
#define HWIO_FT_HIST_WEIGHT_SHUBn_RMSK                                                         0x7
#define HWIO_FT_HIST_WEIGHT_SHUBn_MAXn                                                           7
#define HWIO_FT_HIST_WEIGHT_SHUBn_INI(n)        \
        in_dword_masked(HWIO_FT_HIST_WEIGHT_SHUBn_ADDR(n), HWIO_FT_HIST_WEIGHT_SHUBn_RMSK)
#define HWIO_FT_HIST_WEIGHT_SHUBn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_HIST_WEIGHT_SHUBn_ADDR(n), mask)
#define HWIO_FT_HIST_WEIGHT_SHUBn_OUTI(n,val)    \
        out_dword(HWIO_FT_HIST_WEIGHT_SHUBn_ADDR(n),val)
#define HWIO_FT_HIST_WEIGHT_SHUBn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_HIST_WEIGHT_SHUBn_ADDR(n),mask,val,HWIO_FT_HIST_WEIGHT_SHUBn_INI(n))
#define HWIO_FT_HIST_WEIGHT_SHUBn_VAL_BMSK                                                     0x7
#define HWIO_FT_HIST_WEIGHT_SHUBn_VAL_SHFT                                                     0x0

#define HWIO_FT_SAMPLE_TIMER_ADDR                                                       (BCM_FT_REG_BASE      + 0x00000b80)
#define HWIO_FT_SAMPLE_TIMER_RMSK                                                           0xffff
#define HWIO_FT_SAMPLE_TIMER_IN          \
        in_dword(HWIO_FT_SAMPLE_TIMER_ADDR)
#define HWIO_FT_SAMPLE_TIMER_INM(m)      \
        in_dword_masked(HWIO_FT_SAMPLE_TIMER_ADDR, m)
#define HWIO_FT_SAMPLE_TIMER_OUT(v)      \
        out_dword(HWIO_FT_SAMPLE_TIMER_ADDR,v)
#define HWIO_FT_SAMPLE_TIMER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_SAMPLE_TIMER_ADDR,m,v,HWIO_FT_SAMPLE_TIMER_IN)
#define HWIO_FT_SAMPLE_TIMER_COUNT_BMSK                                                     0xffff
#define HWIO_FT_SAMPLE_TIMER_COUNT_SHFT                                                        0x0

#define HWIO_FT_DECISION_TIMER_ADDR                                                     (BCM_FT_REG_BASE      + 0x00000b84)
#define HWIO_FT_DECISION_TIMER_RMSK                                                         0xffff
#define HWIO_FT_DECISION_TIMER_IN          \
        in_dword(HWIO_FT_DECISION_TIMER_ADDR)
#define HWIO_FT_DECISION_TIMER_INM(m)      \
        in_dword_masked(HWIO_FT_DECISION_TIMER_ADDR, m)
#define HWIO_FT_DECISION_TIMER_OUT(v)      \
        out_dword(HWIO_FT_DECISION_TIMER_ADDR,v)
#define HWIO_FT_DECISION_TIMER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_DECISION_TIMER_ADDR,m,v,HWIO_FT_DECISION_TIMER_IN)
#define HWIO_FT_DECISION_TIMER_COUNT_BMSK                                                   0xffff
#define HWIO_FT_DECISION_TIMER_COUNT_SHFT                                                      0x0

#define HWIO_FT_LOW_CP_BR_ADDR                                                          (BCM_FT_REG_BASE      + 0x00000b88)
#define HWIO_FT_LOW_CP_BR_RMSK                                                                0xff
#define HWIO_FT_LOW_CP_BR_IN          \
        in_dword(HWIO_FT_LOW_CP_BR_ADDR)
#define HWIO_FT_LOW_CP_BR_INM(m)      \
        in_dword_masked(HWIO_FT_LOW_CP_BR_ADDR, m)
#define HWIO_FT_LOW_CP_BR_OUT(v)      \
        out_dword(HWIO_FT_LOW_CP_BR_ADDR,v)
#define HWIO_FT_LOW_CP_BR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_LOW_CP_BR_ADDR,m,v,HWIO_FT_LOW_CP_BR_IN)
#define HWIO_FT_LOW_CP_BR_SHUB_CP_TH_BMSK                                                     0xf0
#define HWIO_FT_LOW_CP_BR_SHUB_CP_TH_SHFT                                                      0x4
#define HWIO_FT_LOW_CP_BR_MC_CP_TH_BMSK                                                        0xf
#define HWIO_FT_LOW_CP_BR_MC_CP_TH_SHFT                                                        0x0

#define HWIO_FT_MC_MOD_FLOOR_ADDR                                                       (BCM_FT_REG_BASE      + 0x00000b8c)
#define HWIO_FT_MC_MOD_FLOOR_RMSK                                                              0xf
#define HWIO_FT_MC_MOD_FLOOR_IN          \
        in_dword(HWIO_FT_MC_MOD_FLOOR_ADDR)
#define HWIO_FT_MC_MOD_FLOOR_INM(m)      \
        in_dword_masked(HWIO_FT_MC_MOD_FLOOR_ADDR, m)
#define HWIO_FT_MC_MOD_FLOOR_OUT(v)      \
        out_dword(HWIO_FT_MC_MOD_FLOOR_ADDR,v)
#define HWIO_FT_MC_MOD_FLOOR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_MC_MOD_FLOOR_ADDR,m,v,HWIO_FT_MC_MOD_FLOOR_IN)
#define HWIO_FT_MC_MOD_FLOOR_MC_CP_TH_BMSK                                                     0xf
#define HWIO_FT_MC_MOD_FLOOR_MC_CP_TH_SHFT                                                     0x0

#define HWIO_FT_STATUS_HIST_UTIL_MC_BINn_HISTm_ADDR(n,m)                                (BCM_FT_REG_BASE      + 0x00000b98 + 0x20 * (n) + 0x4 * (m))
#define HWIO_FT_STATUS_HIST_UTIL_MC_BINn_HISTm_RMSK                                            0x3
#define HWIO_FT_STATUS_HIST_UTIL_MC_BINn_HISTm_MAXn                                              3
#define HWIO_FT_STATUS_HIST_UTIL_MC_BINn_HISTm_MAXm                                              7
#define HWIO_FT_STATUS_HIST_UTIL_MC_BINn_HISTm_INI2(n,m)        \
        in_dword_masked(HWIO_FT_STATUS_HIST_UTIL_MC_BINn_HISTm_ADDR(n,m), HWIO_FT_STATUS_HIST_UTIL_MC_BINn_HISTm_RMSK)
#define HWIO_FT_STATUS_HIST_UTIL_MC_BINn_HISTm_INMI2(n,m,mask)    \
        in_dword_masked(HWIO_FT_STATUS_HIST_UTIL_MC_BINn_HISTm_ADDR(n,m), mask)
#define HWIO_FT_STATUS_HIST_UTIL_MC_BINn_HISTm_UTIL_LVL_BMSK                                   0x3
#define HWIO_FT_STATUS_HIST_UTIL_MC_BINn_HISTm_UTIL_LVL_SHFT                                   0x0

#define HWIO_FT_STATUS_HIST_UTIL_SHUB_BINn_HISTm_ADDR(n,m)                              (BCM_FT_REG_BASE      + 0x00000c18 + 0x20 * (n) + 0x4 * (m))
#define HWIO_FT_STATUS_HIST_UTIL_SHUB_BINn_HISTm_RMSK                                          0x3
#define HWIO_FT_STATUS_HIST_UTIL_SHUB_BINn_HISTm_MAXn                                            3
#define HWIO_FT_STATUS_HIST_UTIL_SHUB_BINn_HISTm_MAXm                                            7
#define HWIO_FT_STATUS_HIST_UTIL_SHUB_BINn_HISTm_INI2(n,m)        \
        in_dword_masked(HWIO_FT_STATUS_HIST_UTIL_SHUB_BINn_HISTm_ADDR(n,m), HWIO_FT_STATUS_HIST_UTIL_SHUB_BINn_HISTm_RMSK)
#define HWIO_FT_STATUS_HIST_UTIL_SHUB_BINn_HISTm_INMI2(n,m,mask)    \
        in_dword_masked(HWIO_FT_STATUS_HIST_UTIL_SHUB_BINn_HISTm_ADDR(n,m), mask)
#define HWIO_FT_STATUS_HIST_UTIL_SHUB_BINn_HISTm_UTIL_LVL_BMSK                                 0x3
#define HWIO_FT_STATUS_HIST_UTIL_SHUB_BINn_HISTm_UTIL_LVL_SHFT                                 0x0

#define HWIO_FT_STATUS_HIST_BMCP_MC_BINn_HISTm_ADDR(n,m)                                (BCM_FT_REG_BASE      + 0x00000c98 + 0x20 * (n) + 0x4 * (m))
#define HWIO_FT_STATUS_HIST_BMCP_MC_BINn_HISTm_RMSK                                            0xf
#define HWIO_FT_STATUS_HIST_BMCP_MC_BINn_HISTm_MAXn                                              3
#define HWIO_FT_STATUS_HIST_BMCP_MC_BINn_HISTm_MAXm                                              7
#define HWIO_FT_STATUS_HIST_BMCP_MC_BINn_HISTm_INI2(n,m)        \
        in_dword_masked(HWIO_FT_STATUS_HIST_BMCP_MC_BINn_HISTm_ADDR(n,m), HWIO_FT_STATUS_HIST_BMCP_MC_BINn_HISTm_RMSK)
#define HWIO_FT_STATUS_HIST_BMCP_MC_BINn_HISTm_INMI2(n,m,mask)    \
        in_dword_masked(HWIO_FT_STATUS_HIST_BMCP_MC_BINn_HISTm_ADDR(n,m), mask)
#define HWIO_FT_STATUS_HIST_BMCP_MC_BINn_HISTm_BM_CP_BMSK                                      0xf
#define HWIO_FT_STATUS_HIST_BMCP_MC_BINn_HISTm_BM_CP_SHFT                                      0x0

#define HWIO_FT_STATUS_HIST_BMCP_SHUB_BINn_HISTm_ADDR(n,m)                              (BCM_FT_REG_BASE      + 0x00000d18 + 0x20 * (n) + 0x4 * (m))
#define HWIO_FT_STATUS_HIST_BMCP_SHUB_BINn_HISTm_RMSK                                          0xf
#define HWIO_FT_STATUS_HIST_BMCP_SHUB_BINn_HISTm_MAXn                                            3
#define HWIO_FT_STATUS_HIST_BMCP_SHUB_BINn_HISTm_MAXm                                            7
#define HWIO_FT_STATUS_HIST_BMCP_SHUB_BINn_HISTm_INI2(n,m)        \
        in_dword_masked(HWIO_FT_STATUS_HIST_BMCP_SHUB_BINn_HISTm_ADDR(n,m), HWIO_FT_STATUS_HIST_BMCP_SHUB_BINn_HISTm_RMSK)
#define HWIO_FT_STATUS_HIST_BMCP_SHUB_BINn_HISTm_INMI2(n,m,mask)    \
        in_dword_masked(HWIO_FT_STATUS_HIST_BMCP_SHUB_BINn_HISTm_ADDR(n,m), mask)
#define HWIO_FT_STATUS_HIST_BMCP_SHUB_BINn_HISTm_BM_CP_BMSK                                    0xf
#define HWIO_FT_STATUS_HIST_BMCP_SHUB_BINn_HISTm_BM_CP_SHFT                                    0x0

#define HWIO_FT_STATUS_BMCP_MC_BINn_ADDR(n)                                             (BCM_FT_REG_BASE      + 0x00000d98 + 0x4 * (n))
#define HWIO_FT_STATUS_BMCP_MC_BINn_RMSK                                                       0xf
#define HWIO_FT_STATUS_BMCP_MC_BINn_MAXn                                                         3
#define HWIO_FT_STATUS_BMCP_MC_BINn_INI(n)        \
        in_dword_masked(HWIO_FT_STATUS_BMCP_MC_BINn_ADDR(n), HWIO_FT_STATUS_BMCP_MC_BINn_RMSK)
#define HWIO_FT_STATUS_BMCP_MC_BINn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_STATUS_BMCP_MC_BINn_ADDR(n), mask)
#define HWIO_FT_STATUS_BMCP_MC_BINn_BM_CP_FIN_BMSK                                             0xf
#define HWIO_FT_STATUS_BMCP_MC_BINn_BM_CP_FIN_SHFT                                             0x0

#define HWIO_FT_STATUS_BMCP_SHUB_BINn_ADDR(n)                                           (BCM_FT_REG_BASE      + 0x00000da8 + 0x4 * (n))
#define HWIO_FT_STATUS_BMCP_SHUB_BINn_RMSK                                                     0xf
#define HWIO_FT_STATUS_BMCP_SHUB_BINn_MAXn                                                       3
#define HWIO_FT_STATUS_BMCP_SHUB_BINn_INI(n)        \
        in_dword_masked(HWIO_FT_STATUS_BMCP_SHUB_BINn_ADDR(n), HWIO_FT_STATUS_BMCP_SHUB_BINn_RMSK)
#define HWIO_FT_STATUS_BMCP_SHUB_BINn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_STATUS_BMCP_SHUB_BINn_ADDR(n), mask)
#define HWIO_FT_STATUS_BMCP_SHUB_BINn_BM_CP_FIN_BMSK                                           0xf
#define HWIO_FT_STATUS_BMCP_SHUB_BINn_BM_CP_FIN_SHFT                                           0x0

#define HWIO_FT_STATUS_FLTR_DRVn_ADDR(n)                                                (BCM_FT_REG_BASE      + 0x00000db8 + 0x4 * (n))
#define HWIO_FT_STATUS_FLTR_DRVn_RMSK                                                       0x7777
#define HWIO_FT_STATUS_FLTR_DRVn_MAXn                                                           23
#define HWIO_FT_STATUS_FLTR_DRVn_INI(n)        \
        in_dword_masked(HWIO_FT_STATUS_FLTR_DRVn_ADDR(n), HWIO_FT_STATUS_FLTR_DRVn_RMSK)
#define HWIO_FT_STATUS_FLTR_DRVn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_STATUS_FLTR_DRVn_ADDR(n), mask)
#define HWIO_FT_STATUS_FLTR_DRVn_SHUB_IB_BMSK                                               0x7000
#define HWIO_FT_STATUS_FLTR_DRVn_SHUB_IB_SHFT                                                  0xc
#define HWIO_FT_STATUS_FLTR_DRVn_MC_IB_BMSK                                                  0x700
#define HWIO_FT_STATUS_FLTR_DRVn_MC_IB_SHFT                                                    0x8
#define HWIO_FT_STATUS_FLTR_DRVn_SHUB_AB_BMSK                                                 0x70
#define HWIO_FT_STATUS_FLTR_DRVn_SHUB_AB_SHFT                                                  0x4
#define HWIO_FT_STATUS_FLTR_DRVn_MC_AB_BMSK                                                    0x7
#define HWIO_FT_STATUS_FLTR_DRVn_MC_AB_SHFT                                                    0x0

#define HWIO_FT_CMB_TRACE_CFG_0_ADDR                                                    (BCM_FT_REG_BASE      + 0x00000e38)
#define HWIO_FT_CMB_TRACE_CFG_0_RMSK                                                           0x1
#define HWIO_FT_CMB_TRACE_CFG_0_IN          \
        in_dword(HWIO_FT_CMB_TRACE_CFG_0_ADDR)
#define HWIO_FT_CMB_TRACE_CFG_0_INM(m)      \
        in_dword_masked(HWIO_FT_CMB_TRACE_CFG_0_ADDR, m)
#define HWIO_FT_CMB_TRACE_CFG_0_OUT(v)      \
        out_dword(HWIO_FT_CMB_TRACE_CFG_0_ADDR,v)
#define HWIO_FT_CMB_TRACE_CFG_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_CMB_TRACE_CFG_0_ADDR,m,v,HWIO_FT_CMB_TRACE_CFG_0_IN)
#define HWIO_FT_CMB_TRACE_CFG_0_MUX_SEL_BMSK                                                   0x1
#define HWIO_FT_CMB_TRACE_CFG_0_MUX_SEL_SHFT                                                   0x0

#define HWIO_FT_CMB_TRACE_CFG_1_ADDR                                                    (BCM_FT_REG_BASE      + 0x00000e3c)
#define HWIO_FT_CMB_TRACE_CFG_1_RMSK                                                    0x1f1f1f1f
#define HWIO_FT_CMB_TRACE_CFG_1_IN          \
        in_dword(HWIO_FT_CMB_TRACE_CFG_1_ADDR)
#define HWIO_FT_CMB_TRACE_CFG_1_INM(m)      \
        in_dword_masked(HWIO_FT_CMB_TRACE_CFG_1_ADDR, m)
#define HWIO_FT_CMB_TRACE_CFG_1_OUT(v)      \
        out_dword(HWIO_FT_CMB_TRACE_CFG_1_ADDR,v)
#define HWIO_FT_CMB_TRACE_CFG_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_CMB_TRACE_CFG_1_ADDR,m,v,HWIO_FT_CMB_TRACE_CFG_1_IN)
#define HWIO_FT_CMB_TRACE_CFG_1_DRV_D_ID_BMSK                                           0x1f000000
#define HWIO_FT_CMB_TRACE_CFG_1_DRV_D_ID_SHFT                                                 0x18
#define HWIO_FT_CMB_TRACE_CFG_1_DRV_C_ID_BMSK                                             0x1f0000
#define HWIO_FT_CMB_TRACE_CFG_1_DRV_C_ID_SHFT                                                 0x10
#define HWIO_FT_CMB_TRACE_CFG_1_DRV_B_ID_BMSK                                               0x1f00
#define HWIO_FT_CMB_TRACE_CFG_1_DRV_B_ID_SHFT                                                  0x8
#define HWIO_FT_CMB_TRACE_CFG_1_DRV_A_ID_BMSK                                                 0x1f
#define HWIO_FT_CMB_TRACE_CFG_1_DRV_A_ID_SHFT                                                  0x0

#define HWIO_FT_BWMON_FE_BINn_ADDR(n)                                                   (BCM_FT_REG_BASE      + 0x00000e40 + 0x4 * (n))
#define HWIO_FT_BWMON_FE_BINn_RMSK                                                          0xffff
#define HWIO_FT_BWMON_FE_BINn_MAXn                                                               3
#define HWIO_FT_BWMON_FE_BINn_INI(n)        \
        in_dword_masked(HWIO_FT_BWMON_FE_BINn_ADDR(n), HWIO_FT_BWMON_FE_BINn_RMSK)
#define HWIO_FT_BWMON_FE_BINn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_BWMON_FE_BINn_ADDR(n), mask)
#define HWIO_FT_BWMON_FE_BINn_OUTI(n,val)    \
        out_dword(HWIO_FT_BWMON_FE_BINn_ADDR(n),val)
#define HWIO_FT_BWMON_FE_BINn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_BWMON_FE_BINn_ADDR(n),mask,val,HWIO_FT_BWMON_FE_BINn_INI(n))
#define HWIO_FT_BWMON_FE_BINn_BYTE_COUNT_BMSK                                               0xffff
#define HWIO_FT_BWMON_FE_BINn_BYTE_COUNT_SHFT                                                  0x0

#define HWIO_FT_BWMON_BE_BINn_ADDR(n)                                                   (BCM_FT_REG_BASE      + 0x00000e60 + 0x4 * (n))
#define HWIO_FT_BWMON_BE_BINn_RMSK                                                          0xffff
#define HWIO_FT_BWMON_BE_BINn_MAXn                                                               3
#define HWIO_FT_BWMON_BE_BINn_INI(n)        \
        in_dword_masked(HWIO_FT_BWMON_BE_BINn_ADDR(n), HWIO_FT_BWMON_BE_BINn_RMSK)
#define HWIO_FT_BWMON_BE_BINn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_BWMON_BE_BINn_ADDR(n), mask)
#define HWIO_FT_BWMON_BE_BINn_OUTI(n,val)    \
        out_dword(HWIO_FT_BWMON_BE_BINn_ADDR(n),val)
#define HWIO_FT_BWMON_BE_BINn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_BWMON_BE_BINn_ADDR(n),mask,val,HWIO_FT_BWMON_BE_BINn_INI(n))
#define HWIO_FT_BWMON_BE_BINn_BYTE_COUNT_BMSK                                               0xffff
#define HWIO_FT_BWMON_BE_BINn_BYTE_COUNT_SHFT                                                  0x0

#define HWIO_FT_QM_UNSAFE_CLIENTn_ADDR(n)                                               (BCM_FT_REG_BASE      + 0x00000e80 + 0x4 * (n))
#define HWIO_FT_QM_UNSAFE_CLIENTn_RMSK                                                  0xffffffff
#define HWIO_FT_QM_UNSAFE_CLIENTn_MAXn                                                           5
#define HWIO_FT_QM_UNSAFE_CLIENTn_INI(n)        \
        in_dword_masked(HWIO_FT_QM_UNSAFE_CLIENTn_ADDR(n), HWIO_FT_QM_UNSAFE_CLIENTn_RMSK)
#define HWIO_FT_QM_UNSAFE_CLIENTn_INMI(n,mask)    \
        in_dword_masked(HWIO_FT_QM_UNSAFE_CLIENTn_ADDR(n), mask)
#define HWIO_FT_QM_UNSAFE_CLIENTn_OUTI(n,val)    \
        out_dword(HWIO_FT_QM_UNSAFE_CLIENTn_ADDR(n),val)
#define HWIO_FT_QM_UNSAFE_CLIENTn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_FT_QM_UNSAFE_CLIENTn_ADDR(n),mask,val,HWIO_FT_QM_UNSAFE_CLIENTn_INI(n))
#define HWIO_FT_QM_UNSAFE_CLIENTn_COUNT_BMSK                                            0xffffffff
#define HWIO_FT_QM_UNSAFE_CLIENTn_COUNT_SHFT                                                   0x0

#define HWIO_FT_RD_MISS_CNT0_ADDR                                                       (BCM_FT_REG_BASE      + 0x00000ea0)
#define HWIO_FT_RD_MISS_CNT0_RMSK                                                         0xffffff
#define HWIO_FT_RD_MISS_CNT0_IN          \
        in_dword(HWIO_FT_RD_MISS_CNT0_ADDR)
#define HWIO_FT_RD_MISS_CNT0_INM(m)      \
        in_dword_masked(HWIO_FT_RD_MISS_CNT0_ADDR, m)
#define HWIO_FT_RD_MISS_CNT0_OUT(v)      \
        out_dword(HWIO_FT_RD_MISS_CNT0_ADDR,v)
#define HWIO_FT_RD_MISS_CNT0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_RD_MISS_CNT0_ADDR,m,v,HWIO_FT_RD_MISS_CNT0_IN)
#define HWIO_FT_RD_MISS_CNT0_COUNT_BMSK                                                   0xffffff
#define HWIO_FT_RD_MISS_CNT0_COUNT_SHFT                                                        0x0

#define HWIO_FT_RD_MISS_CNT1_ADDR                                                       (BCM_FT_REG_BASE      + 0x00000ea4)
#define HWIO_FT_RD_MISS_CNT1_RMSK                                                         0xffffff
#define HWIO_FT_RD_MISS_CNT1_IN          \
        in_dword(HWIO_FT_RD_MISS_CNT1_ADDR)
#define HWIO_FT_RD_MISS_CNT1_INM(m)      \
        in_dword_masked(HWIO_FT_RD_MISS_CNT1_ADDR, m)
#define HWIO_FT_RD_MISS_CNT1_OUT(v)      \
        out_dword(HWIO_FT_RD_MISS_CNT1_ADDR,v)
#define HWIO_FT_RD_MISS_CNT1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_FT_RD_MISS_CNT1_ADDR,m,v,HWIO_FT_RD_MISS_CNT1_IN)
#define HWIO_FT_RD_MISS_CNT1_COUNT_BMSK                                                   0xffffff
#define HWIO_FT_RD_MISS_CNT1_COUNT_SHFT                                                        0x0


#endif /* __BCM_HWIO_H__ */
