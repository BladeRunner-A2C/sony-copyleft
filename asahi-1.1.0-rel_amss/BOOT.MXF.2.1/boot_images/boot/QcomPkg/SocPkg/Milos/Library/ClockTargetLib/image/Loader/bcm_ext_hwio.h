#ifndef __BCM_EXT_HWIO_H__
#define __BCM_EXT_HWIO_H__
/*
===========================================================================
*/
/**
  @file bcm_ext_hwio.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following modules:
    GCC_CLK_CTL_REG
    TCSR_TCSR_REGS

  'Include' filters applied: MMNOC[GCC_CLK_CTL_REG] GDS_HW_CTRL_SW[GCC_CLK_CTL_REG] TCSR_TIMEOUT_INTR_CH2_CH4_OR_CH6_STATUS[TCSR_TCSR_REGS] 

  Generation parameters: 
  { 'filename': 'bcm_ext_hwio.h',
    'header': '#include "msmhwiobase.h"\n#include "HALhwio.h"',
    'module-filter-exclude': {},
    'module-filter-include': { 'GCC_CLK_CTL_REG': ['MMNOC', 'GDS_HW_CTRL_SW'],
                               'TCSR_TCSR_REGS': [ 'TCSR_TIMEOUT_INTR_CH2_CH4_OR_CH6_STATUS']},
    'modules': ['GCC_CLK_CTL_REG', 'TCSR_TCSR_REGS']}
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
#include "HALhwio.h"

/*----------------------------------------------------------------------------
 * MODULE: TCSR_TCSR_REGS
 *--------------------------------------------------------------------------*/

#define TCSR_TCSR_REGS_REG_BASE                                                                                                                               (CORE_TOP_CSR_BASE      + 0x00040000)
#define TCSR_TCSR_REGS_REG_BASE_SIZE                                                                                                                          0xc0000
#define TCSR_TCSR_REGS_REG_BASE_USED                                                                                                                          0xb8000

/*----------------------------------------------------------------------------
 * MODULE: GCC_CLK_CTL_REG
 *--------------------------------------------------------------------------*/

#define GCC_CLK_CTL_REG_REG_BASE                                                                        (CLK_CTL_BASE      + 0x00010000)
#define GCC_CLK_CTL_REG_REG_BASE_SIZE                                                                   0x1e0000
#define GCC_CLK_CTL_REG_REG_BASE_USED                                                                   0xa1204

#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_ADDR                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x0006402c)
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_RMSK                                                         0x81d00005
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_IN          \
        in_dword(HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_ADDR)
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_ADDR, m)
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_ADDR,v)
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_ADDR,m,v,HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_IN)
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_CLK_OFF_BMSK                                                 0x80000000
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_CLK_OFF_SHFT                                                       0x1f
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_IGNORE_ALL_ARES_BMSK                                          0x1000000
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_IGNORE_ALL_ARES_SHFT                                               0x18
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                        0x800000
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                            0x17
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_CLK_DIS_BMSK                                                   0x400000
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_CLK_DIS_SHFT                                                       0x16
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_IGNORE_RPMH_CLK_DIS_BMSK                                       0x100000
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_IGNORE_RPMH_CLK_DIS_SHFT                                           0x14
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_CLK_ARES_BMSK                                                       0x4
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_CLK_ARES_SHFT                                                       0x2
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_CLK_ENABLE_BMSK                                                     0x1
#define HWIO_GCC_CFG_NOC_HF_MMNOC_AHB_CBCR_CLK_ENABLE_SHFT                                                     0x0

#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_ADDR                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x00064030)
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_RMSK                                                         0x81d00005
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_IN          \
        in_dword(HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_ADDR)
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_ADDR, m)
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_ADDR,v)
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_ADDR,m,v,HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_IN)
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_CLK_OFF_BMSK                                                 0x80000000
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_CLK_OFF_SHFT                                                       0x1f
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_IGNORE_ALL_ARES_BMSK                                          0x1000000
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_IGNORE_ALL_ARES_SHFT                                               0x18
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                        0x800000
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                            0x17
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_CLK_DIS_BMSK                                                   0x400000
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_CLK_DIS_SHFT                                                       0x16
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_IGNORE_RPMH_CLK_DIS_BMSK                                       0x100000
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_IGNORE_RPMH_CLK_DIS_SHFT                                           0x14
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_CLK_ARES_BMSK                                                       0x4
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_CLK_ARES_SHFT                                                       0x2
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_CLK_ENABLE_BMSK                                                     0x1
#define HWIO_GCC_CFG_NOC_SF_MMNOC_AHB_CBCR_CLK_ENABLE_SHFT                                                     0x0

#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_ADDR                                                     (GCC_CLK_CTL_REG_REG_BASE      + 0x00064050)
#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_RMSK                                                     0x81c00005
#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_IN          \
        in_dword(HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_ADDR)
#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_ADDR, m)
#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_ADDR,v)
#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_ADDR,m,v,HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_IN)
#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_CLK_OFF_BMSK                                             0x80000000
#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_CLK_OFF_SHFT                                                   0x1f
#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_IGNORE_ALL_ARES_BMSK                                      0x1000000
#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_IGNORE_ALL_ARES_SHFT                                           0x18
#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                    0x800000
#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                        0x17
#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_CLK_DIS_BMSK                                               0x400000
#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_CLK_DIS_SHFT                                                   0x16
#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_CLK_ARES_BMSK                                                   0x4
#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_CLK_ARES_SHFT                                                   0x2
#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_CLK_ENABLE_BMSK                                                 0x1
#define HWIO_GCC_NOC_MMNOC_HF_CNOC_DCD_XO_CBCR_CLK_ENABLE_SHFT                                                 0x0

#define HWIO_GCC_CONFIG_NOC_MMNOC_HF_DCD_CDIV_DCDR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x000648bc)
#define HWIO_GCC_CONFIG_NOC_MMNOC_HF_DCD_CDIV_DCDR_RMSK                                                        0x3
#define HWIO_GCC_CONFIG_NOC_MMNOC_HF_DCD_CDIV_DCDR_IN          \
        in_dword(HWIO_GCC_CONFIG_NOC_MMNOC_HF_DCD_CDIV_DCDR_ADDR)
#define HWIO_GCC_CONFIG_NOC_MMNOC_HF_DCD_CDIV_DCDR_INM(m)      \
        in_dword_masked(HWIO_GCC_CONFIG_NOC_MMNOC_HF_DCD_CDIV_DCDR_ADDR, m)
#define HWIO_GCC_CONFIG_NOC_MMNOC_HF_DCD_CDIV_DCDR_OUT(v)      \
        out_dword(HWIO_GCC_CONFIG_NOC_MMNOC_HF_DCD_CDIV_DCDR_ADDR,v)
#define HWIO_GCC_CONFIG_NOC_MMNOC_HF_DCD_CDIV_DCDR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_CONFIG_NOC_MMNOC_HF_DCD_CDIV_DCDR_ADDR,m,v,HWIO_GCC_CONFIG_NOC_MMNOC_HF_DCD_CDIV_DCDR_IN)
#define HWIO_GCC_CONFIG_NOC_MMNOC_HF_DCD_CDIV_DCDR_IGNORE_ALL_FSM_CLK_ACTV_BMSK                                0x2
#define HWIO_GCC_CONFIG_NOC_MMNOC_HF_DCD_CDIV_DCDR_IGNORE_ALL_FSM_CLK_ACTV_SHFT                                0x1
#define HWIO_GCC_CONFIG_NOC_MMNOC_HF_DCD_CDIV_DCDR_DCD_ENABLE_BMSK                                             0x1
#define HWIO_GCC_CONFIG_NOC_MMNOC_HF_DCD_CDIV_DCDR_DCD_ENABLE_SHFT                                             0x0

#define HWIO_GCC_CONFIG_NOC_MMNOC_SF_DCD_CDIV_DCDR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x000648c0)
#define HWIO_GCC_CONFIG_NOC_MMNOC_SF_DCD_CDIV_DCDR_RMSK                                                        0x3
#define HWIO_GCC_CONFIG_NOC_MMNOC_SF_DCD_CDIV_DCDR_IN          \
        in_dword(HWIO_GCC_CONFIG_NOC_MMNOC_SF_DCD_CDIV_DCDR_ADDR)
#define HWIO_GCC_CONFIG_NOC_MMNOC_SF_DCD_CDIV_DCDR_INM(m)      \
        in_dword_masked(HWIO_GCC_CONFIG_NOC_MMNOC_SF_DCD_CDIV_DCDR_ADDR, m)
#define HWIO_GCC_CONFIG_NOC_MMNOC_SF_DCD_CDIV_DCDR_OUT(v)      \
        out_dword(HWIO_GCC_CONFIG_NOC_MMNOC_SF_DCD_CDIV_DCDR_ADDR,v)
#define HWIO_GCC_CONFIG_NOC_MMNOC_SF_DCD_CDIV_DCDR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_CONFIG_NOC_MMNOC_SF_DCD_CDIV_DCDR_ADDR,m,v,HWIO_GCC_CONFIG_NOC_MMNOC_SF_DCD_CDIV_DCDR_IN)
#define HWIO_GCC_CONFIG_NOC_MMNOC_SF_DCD_CDIV_DCDR_IGNORE_ALL_FSM_CLK_ACTV_BMSK                                0x2
#define HWIO_GCC_CONFIG_NOC_MMNOC_SF_DCD_CDIV_DCDR_IGNORE_ALL_FSM_CLK_ACTV_SHFT                                0x1
#define HWIO_GCC_CONFIG_NOC_MMNOC_SF_DCD_CDIV_DCDR_DCD_ENABLE_BMSK                                             0x1
#define HWIO_GCC_CONFIG_NOC_MMNOC_SF_DCD_CDIV_DCDR_DCD_ENABLE_SHFT                                             0x0

#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_ADDR                                                     (GCC_CLK_CTL_REG_REG_BASE      + 0x00064a08)
#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_RMSK                                                     0x81c00005
#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_IN          \
        in_dword(HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_ADDR)
#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_ADDR, m)
#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_ADDR,v)
#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_ADDR,m,v,HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_IN)
#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_CLK_OFF_BMSK                                             0x80000000
#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_CLK_OFF_SHFT                                                   0x1f
#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_IGNORE_ALL_ARES_BMSK                                      0x1000000
#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_IGNORE_ALL_ARES_SHFT                                           0x18
#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                    0x800000
#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                        0x17
#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_CLK_DIS_BMSK                                               0x400000
#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_CLK_DIS_SHFT                                                   0x16
#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_CLK_ARES_BMSK                                                   0x4
#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_CLK_ARES_SHFT                                                   0x2
#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_CLK_ENABLE_BMSK                                                 0x1
#define HWIO_GCC_NOC_MMNOC_SF_CNOC_DCD_XO_CBCR_CLK_ENABLE_SHFT                                                 0x0

#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_ADDR                                                             (GCC_CLK_CTL_REG_REG_BASE      + 0x00073160)
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_RMSK                                                             0x81d0000f
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_IN          \
        in_dword(HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_ADDR)
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_ADDR, m)
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_ADDR,v)
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_ADDR,m,v,HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_IN)
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_CLK_OFF_BMSK                                                     0x80000000
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_CLK_OFF_SHFT                                                           0x1f
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_IGNORE_ALL_ARES_BMSK                                              0x1000000
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_IGNORE_ALL_ARES_SHFT                                                   0x18
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                            0x800000
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                                0x17
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_CLK_DIS_BMSK                                                       0x400000
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_CLK_DIS_SHFT                                                           0x16
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_IGNORE_RPMH_CLK_DIS_BMSK                                           0x100000
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_IGNORE_RPMH_CLK_DIS_SHFT                                               0x14
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_SW_ONLY_EN_BMSK                                                         0x8
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_SW_ONLY_EN_SHFT                                                         0x3
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_CLK_ARES_BMSK                                                           0x4
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_CLK_ARES_SHFT                                                           0x2
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_HW_CTL_BMSK                                                             0x2
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_HW_CTL_SHFT                                                             0x1
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_CLK_ENABLE_BMSK                                                         0x1
#define HWIO_GCC_TCU_MMNOC_QTB_SF_CBCR_CLK_ENABLE_SHFT                                                         0x0

#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_ADDR                                                           (GCC_CLK_CTL_REG_REG_BASE      + 0x00073164)
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_RMSK                                                           0x81d0000f
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_IN          \
        in_dword(HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_ADDR)
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_ADDR, m)
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_ADDR,v)
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_ADDR,m,v,HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_IN)
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_IGNORE_ALL_ARES_BMSK                                            0x1000000
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_IGNORE_ALL_ARES_SHFT                                                 0x18
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                          0x800000
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                              0x17
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_CLK_DIS_BMSK                                                     0x400000
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_CLK_DIS_SHFT                                                         0x16
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_IGNORE_RPMH_CLK_DIS_BMSK                                         0x100000
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_IGNORE_RPMH_CLK_DIS_SHFT                                             0x14
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_SW_ONLY_EN_BMSK                                                       0x8
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_SW_ONLY_EN_SHFT                                                       0x3
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_CLK_ARES_BMSK                                                         0x4
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_CLK_ARES_SHFT                                                         0x2
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_GCC_TCU_MMNOC_QTB_HF01_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_ADDR                                                           (GCC_CLK_CTL_REG_REG_BASE      + 0x00073168)
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_RMSK                                                           0x81d0000f
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_IN          \
        in_dword(HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_ADDR)
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_ADDR, m)
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_ADDR,v)
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_ADDR,m,v,HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_IN)
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_CLK_OFF_BMSK                                                   0x80000000
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_CLK_OFF_SHFT                                                         0x1f
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_IGNORE_ALL_ARES_BMSK                                            0x1000000
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_IGNORE_ALL_ARES_SHFT                                                 0x18
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                          0x800000
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                              0x17
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_CLK_DIS_BMSK                                                     0x400000
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_CLK_DIS_SHFT                                                         0x16
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_IGNORE_RPMH_CLK_DIS_BMSK                                         0x100000
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_IGNORE_RPMH_CLK_DIS_SHFT                                             0x14
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_SW_ONLY_EN_BMSK                                                       0x8
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_SW_ONLY_EN_SHFT                                                       0x3
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_CLK_ARES_BMSK                                                         0x4
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_CLK_ARES_SHFT                                                         0x2
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_HW_CTL_BMSK                                                           0x2
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_HW_CTL_SHFT                                                           0x1
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_CLK_ENABLE_BMSK                                                       0x1
#define HWIO_GCC_TCU_MMNOC_QTB_HF23_CBCR_CLK_ENABLE_SHFT                                                       0x0

#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_ADDR                                                               (GCC_CLK_CTL_REG_REG_BASE      + 0x00073180)
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_RMSK                                                                  0x1ffff
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_CMD_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_CMD_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_CMD_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_CMD_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_CMD_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_RCG_SW_CTRL_BMSK                                                      0x18000
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_RCG_SW_CTRL_SHFT                                                          0xf
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_SW_PERF_STATE_BMSK                                                     0x7800
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_SW_PERF_STATE_SHFT                                                        0xb
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_SW_OVERRIDE_BMSK                                                        0x400
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_SW_OVERRIDE_SHFT                                                          0xa
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_PERF_STATE_UPDATE_STATUS_BMSK                                           0x200
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_PERF_STATE_UPDATE_STATUS_SHFT                                             0x9
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_DFS_FSM_STATE_BMSK                                                      0x1c0
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_DFS_FSM_STATE_SHFT                                                        0x6
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_HW_CLK_CONTROL_BMSK                                                      0x20
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_HW_CLK_CONTROL_SHFT                                                       0x5
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_CURR_PERF_STATE_BMSK                                                     0x1e
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_CURR_PERF_STATE_SHFT                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_DFS_EN_BMSK                                                               0x1
#define HWIO_GCC_RPMH_MMNOC_CMD_DFSR_DFS_EN_SHFT                                                               0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF0_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x00073188)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF0_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF0_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF0_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF0_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF0_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF0_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF0_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF0_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF0_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF0_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF0_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF0_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF0_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF0_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF1_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x0007318c)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF1_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF1_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF1_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF1_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF1_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF1_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF1_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF1_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF1_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF1_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF1_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF1_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF1_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF1_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF2_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x00073190)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF2_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF2_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF2_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF2_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF2_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF2_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF2_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF2_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF2_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF2_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF2_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF2_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF2_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF2_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF3_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x00073194)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF3_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF3_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF3_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF3_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF3_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF3_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF3_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF3_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF3_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF3_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF3_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF3_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF3_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF3_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF4_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x00073198)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF4_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF4_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF4_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF4_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF4_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF4_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF4_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF4_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF4_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF4_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF4_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF4_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF4_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF4_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF5_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x0007319c)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF5_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF5_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF5_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF5_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF5_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF5_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF5_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF5_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF5_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF5_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF5_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF5_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF5_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF5_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF6_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x000731a0)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF6_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF6_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF6_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF6_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF6_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF6_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF6_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF6_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF6_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF6_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF6_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF6_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF6_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF6_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF7_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x000731a4)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF7_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF7_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF7_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF7_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF7_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF7_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF7_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF7_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF7_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF7_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF7_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF7_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF7_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF7_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF8_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x000731a8)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF8_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF8_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF8_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF8_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF8_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF8_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF8_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF8_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF8_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF8_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF8_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF8_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF8_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF8_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF9_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x000731ac)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF9_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF9_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF9_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF9_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF9_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF9_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF9_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF9_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF9_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF9_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF9_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF9_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF9_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF9_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF10_DFSR_ADDR                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x000731b0)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF10_DFSR_RMSK                                                     0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF10_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF10_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF10_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF10_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF10_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF10_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF10_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF10_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF10_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF10_DFSR_SRC_SEL_BMSK                                             0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF10_DFSR_SRC_SEL_SHFT                                               0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF10_DFSR_SRC_DIV_BMSK                                              0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF10_DFSR_SRC_DIV_SHFT                                               0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF11_DFSR_ADDR                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x000731b4)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF11_DFSR_RMSK                                                     0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF11_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF11_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF11_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF11_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF11_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF11_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF11_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF11_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF11_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF11_DFSR_SRC_SEL_BMSK                                             0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF11_DFSR_SRC_SEL_SHFT                                               0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF11_DFSR_SRC_DIV_BMSK                                              0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF11_DFSR_SRC_DIV_SHFT                                               0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF12_DFSR_ADDR                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x000731b8)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF12_DFSR_RMSK                                                     0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF12_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF12_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF12_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF12_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF12_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF12_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF12_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF12_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF12_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF12_DFSR_SRC_SEL_BMSK                                             0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF12_DFSR_SRC_SEL_SHFT                                               0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF12_DFSR_SRC_DIV_BMSK                                              0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF12_DFSR_SRC_DIV_SHFT                                               0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF13_DFSR_ADDR                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x000731bc)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF13_DFSR_RMSK                                                     0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF13_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF13_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF13_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF13_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF13_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF13_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF13_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF13_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF13_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF13_DFSR_SRC_SEL_BMSK                                             0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF13_DFSR_SRC_SEL_SHFT                                               0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF13_DFSR_SRC_DIV_BMSK                                              0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF13_DFSR_SRC_DIV_SHFT                                               0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF14_DFSR_ADDR                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x000731c0)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF14_DFSR_RMSK                                                     0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF14_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF14_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF14_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF14_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF14_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF14_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF14_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF14_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF14_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF14_DFSR_SRC_SEL_BMSK                                             0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF14_DFSR_SRC_SEL_SHFT                                               0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF14_DFSR_SRC_DIV_BMSK                                              0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF14_DFSR_SRC_DIV_SHFT                                               0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF15_DFSR_ADDR                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x000731c4)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF15_DFSR_RMSK                                                     0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF15_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF15_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF15_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF15_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF15_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF15_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF15_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF15_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF15_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF15_DFSR_SRC_SEL_BMSK                                             0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF15_DFSR_SRC_SEL_SHFT                                               0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF15_DFSR_SRC_DIV_BMSK                                              0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_HF_QX_PERF15_DFSR_SRC_DIV_SHFT                                               0x0

#define HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_ADDR                                                              (GCC_CLK_CTL_REG_REG_BASE      + 0x0007316c)
#define HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_RMSK                                                              0x80000013
#define HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_IN          \
        in_dword(HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_ADDR)
#define HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_ADDR, m)
#define HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_ADDR,v)
#define HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_ADDR,m,v,HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_IN)
#define HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_ROOT_OFF_BMSK                                                     0x80000000
#define HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_ROOT_OFF_SHFT                                                           0x1f
#define HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                     0x10
#define HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                      0x4
#define HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_ROOT_EN_BMSK                                                             0x2
#define HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_ROOT_EN_SHFT                                                             0x1
#define HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_UPDATE_BMSK                                                              0x1
#define HWIO_GCC_MMNOC_HF_QX_CMD_RCGR_UPDATE_SHFT                                                              0x0

#define HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_ADDR                                                              (GCC_CLK_CTL_REG_REG_BASE      + 0x00073170)
#define HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_RMSK                                                                0x11071f
#define HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_IN          \
        in_dword(HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_ADDR)
#define HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_ADDR, m)
#define HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_ADDR,v)
#define HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_ADDR,m,v,HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_IN)
#define HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_HW_CLK_CONTROL_BMSK                                                 0x100000
#define HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_HW_CLK_CONTROL_SHFT                                                     0x14
#define HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_RCGLITE_DISABLE_BMSK                                                 0x10000
#define HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_RCGLITE_DISABLE_SHFT                                                    0x10
#define HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_SRC_SEL_BMSK                                                           0x700
#define HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_SRC_SEL_SHFT                                                             0x8
#define HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_SRC_DIV_BMSK                                                            0x1f
#define HWIO_GCC_MMNOC_HF_QX_CFG_RCGR_SRC_DIV_SHFT                                                             0x0

#define HWIO_GCC_MMNOC_HF_QX_AACSR_ADDR                                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x00073288)
#define HWIO_GCC_MMNOC_HF_QX_AACSR_RMSK                                                                 0x9e0001ff
#define HWIO_GCC_MMNOC_HF_QX_AACSR_IN          \
        in_dword(HWIO_GCC_MMNOC_HF_QX_AACSR_ADDR)
#define HWIO_GCC_MMNOC_HF_QX_AACSR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HF_QX_AACSR_ADDR, m)
#define HWIO_GCC_MMNOC_HF_QX_AACSR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HF_QX_AACSR_ADDR,v)
#define HWIO_GCC_MMNOC_HF_QX_AACSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HF_QX_AACSR_ADDR,m,v,HWIO_GCC_MMNOC_HF_QX_AACSR_IN)
#define HWIO_GCC_MMNOC_HF_QX_AACSR_AACS_CLK_ON_BMSK                                                     0x80000000
#define HWIO_GCC_MMNOC_HF_QX_AACSR_AACS_CLK_ON_SHFT                                                           0x1f
#define HWIO_GCC_MMNOC_HF_QX_AACSR_AACS_DBG_OUT_BMSK                                                    0x1e000000
#define HWIO_GCC_MMNOC_HF_QX_AACSR_AACS_DBG_OUT_SHFT                                                          0x19
#define HWIO_GCC_MMNOC_HF_QX_AACSR_AACS_MODE_BMSK                                                            0x1c0
#define HWIO_GCC_MMNOC_HF_QX_AACSR_AACS_MODE_SHFT                                                              0x6
#define HWIO_GCC_MMNOC_HF_QX_AACSR_AACS_MPW_CFG_BMSK                                                          0x30
#define HWIO_GCC_MMNOC_HF_QX_AACSR_AACS_MPW_CFG_SHFT                                                           0x4
#define HWIO_GCC_MMNOC_HF_QX_AACSR_AACS_DBG_BUS_SEL_BMSK                                                       0xc
#define HWIO_GCC_MMNOC_HF_QX_AACSR_AACS_DBG_BUS_SEL_SHFT                                                       0x2
#define HWIO_GCC_MMNOC_HF_QX_AACSR_AACS_CGC_HANDSHAKE_DIS_BMSK                                                 0x2
#define HWIO_GCC_MMNOC_HF_QX_AACSR_AACS_CGC_HANDSHAKE_DIS_SHFT                                                 0x1
#define HWIO_GCC_MMNOC_HF_QX_AACSR_AACS_EN_BMSK                                                                0x1
#define HWIO_GCC_MMNOC_HF_QX_AACSR_AACS_EN_SHFT                                                                0x0

#define HWIO_GCC_MMNOC_HF_QX_DCD_CDIV_DCDR_ADDR                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x00073298)
#define HWIO_GCC_MMNOC_HF_QX_DCD_CDIV_DCDR_RMSK                                                                0x3
#define HWIO_GCC_MMNOC_HF_QX_DCD_CDIV_DCDR_IN          \
        in_dword(HWIO_GCC_MMNOC_HF_QX_DCD_CDIV_DCDR_ADDR)
#define HWIO_GCC_MMNOC_HF_QX_DCD_CDIV_DCDR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HF_QX_DCD_CDIV_DCDR_ADDR, m)
#define HWIO_GCC_MMNOC_HF_QX_DCD_CDIV_DCDR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HF_QX_DCD_CDIV_DCDR_ADDR,v)
#define HWIO_GCC_MMNOC_HF_QX_DCD_CDIV_DCDR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HF_QX_DCD_CDIV_DCDR_ADDR,m,v,HWIO_GCC_MMNOC_HF_QX_DCD_CDIV_DCDR_IN)
#define HWIO_GCC_MMNOC_HF_QX_DCD_CDIV_DCDR_IGNORE_ALL_FSM_CLK_ACTV_BMSK                                        0x2
#define HWIO_GCC_MMNOC_HF_QX_DCD_CDIV_DCDR_IGNORE_ALL_FSM_CLK_ACTV_SHFT                                        0x1
#define HWIO_GCC_MMNOC_HF_QX_DCD_CDIV_DCDR_DCD_ENABLE_BMSK                                                     0x1
#define HWIO_GCC_MMNOC_HF_QX_DCD_CDIV_DCDR_DCD_ENABLE_SHFT                                                     0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF0_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x000732b8)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF0_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF0_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF0_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF0_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF0_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF0_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF0_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF0_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF0_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF0_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF0_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF0_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF0_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF0_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF1_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x000732bc)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF1_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF1_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF1_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF1_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF1_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF1_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF1_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF1_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF1_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF1_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF1_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF1_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF1_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF1_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF2_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x000732c0)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF2_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF2_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF2_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF2_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF2_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF2_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF2_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF2_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF2_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF2_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF2_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF2_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF2_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF2_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF3_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x000732c4)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF3_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF3_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF3_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF3_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF3_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF3_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF3_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF3_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF3_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF3_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF3_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF3_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF3_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF3_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF4_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x000732c8)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF4_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF4_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF4_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF4_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF4_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF4_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF4_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF4_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF4_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF4_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF4_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF4_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF4_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF4_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF5_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x000732cc)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF5_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF5_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF5_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF5_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF5_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF5_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF5_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF5_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF5_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF5_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF5_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF5_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF5_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF5_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF6_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x000732d0)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF6_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF6_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF6_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF6_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF6_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF6_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF6_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF6_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF6_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF6_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF6_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF6_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF6_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF6_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF7_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x000732d4)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF7_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF7_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF7_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF7_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF7_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF7_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF7_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF7_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF7_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF7_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF7_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF7_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF7_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF7_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF8_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x000732d8)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF8_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF8_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF8_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF8_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF8_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF8_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF8_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF8_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF8_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF8_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF8_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF8_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF8_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF8_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF9_DFSR_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x000732dc)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF9_DFSR_RMSK                                                      0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF9_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF9_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF9_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF9_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF9_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF9_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF9_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF9_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF9_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF9_DFSR_SRC_SEL_BMSK                                              0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF9_DFSR_SRC_SEL_SHFT                                                0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF9_DFSR_SRC_DIV_BMSK                                               0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF9_DFSR_SRC_DIV_SHFT                                                0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF10_DFSR_ADDR                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x000732e0)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF10_DFSR_RMSK                                                     0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF10_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF10_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF10_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF10_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF10_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF10_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF10_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF10_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF10_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF10_DFSR_SRC_SEL_BMSK                                             0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF10_DFSR_SRC_SEL_SHFT                                               0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF10_DFSR_SRC_DIV_BMSK                                              0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF10_DFSR_SRC_DIV_SHFT                                               0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF11_DFSR_ADDR                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x000732e4)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF11_DFSR_RMSK                                                     0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF11_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF11_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF11_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF11_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF11_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF11_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF11_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF11_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF11_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF11_DFSR_SRC_SEL_BMSK                                             0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF11_DFSR_SRC_SEL_SHFT                                               0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF11_DFSR_SRC_DIV_BMSK                                              0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF11_DFSR_SRC_DIV_SHFT                                               0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF12_DFSR_ADDR                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x000732e8)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF12_DFSR_RMSK                                                     0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF12_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF12_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF12_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF12_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF12_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF12_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF12_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF12_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF12_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF12_DFSR_SRC_SEL_BMSK                                             0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF12_DFSR_SRC_SEL_SHFT                                               0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF12_DFSR_SRC_DIV_BMSK                                              0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF12_DFSR_SRC_DIV_SHFT                                               0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF13_DFSR_ADDR                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x000732ec)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF13_DFSR_RMSK                                                     0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF13_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF13_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF13_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF13_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF13_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF13_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF13_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF13_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF13_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF13_DFSR_SRC_SEL_BMSK                                             0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF13_DFSR_SRC_SEL_SHFT                                               0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF13_DFSR_SRC_DIV_BMSK                                              0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF13_DFSR_SRC_DIV_SHFT                                               0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF14_DFSR_ADDR                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x000732f0)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF14_DFSR_RMSK                                                     0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF14_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF14_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF14_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF14_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF14_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF14_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF14_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF14_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF14_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF14_DFSR_SRC_SEL_BMSK                                             0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF14_DFSR_SRC_SEL_SHFT                                               0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF14_DFSR_SRC_DIV_BMSK                                              0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF14_DFSR_SRC_DIV_SHFT                                               0x0

#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF15_DFSR_ADDR                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x000732f4)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF15_DFSR_RMSK                                                     0x71f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF15_DFSR_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF15_DFSR_ADDR)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF15_DFSR_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF15_DFSR_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF15_DFSR_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF15_DFSR_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF15_DFSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF15_DFSR_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF15_DFSR_IN)
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF15_DFSR_SRC_SEL_BMSK                                             0x700
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF15_DFSR_SRC_SEL_SHFT                                               0x8
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF15_DFSR_SRC_DIV_BMSK                                              0x1f
#define HWIO_GCC_RPMH_MMNOC_MMNOC_SF_QX_PERF15_DFSR_SRC_DIV_SHFT                                               0x0

#define HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_ADDR                                                              (GCC_CLK_CTL_REG_REG_BASE      + 0x0007329c)
#define HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_RMSK                                                              0x80000013
#define HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_IN          \
        in_dword(HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_ADDR)
#define HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_ADDR, m)
#define HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_ADDR,v)
#define HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_ADDR,m,v,HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_IN)
#define HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_ROOT_OFF_BMSK                                                     0x80000000
#define HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_ROOT_OFF_SHFT                                                           0x1f
#define HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_DIRTY_CFG_RCGR_BMSK                                                     0x10
#define HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_DIRTY_CFG_RCGR_SHFT                                                      0x4
#define HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_ROOT_EN_BMSK                                                             0x2
#define HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_ROOT_EN_SHFT                                                             0x1
#define HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_UPDATE_BMSK                                                              0x1
#define HWIO_GCC_MMNOC_SF_QX_CMD_RCGR_UPDATE_SHFT                                                              0x0

#define HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_ADDR                                                              (GCC_CLK_CTL_REG_REG_BASE      + 0x000732a0)
#define HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_RMSK                                                                0x11071f
#define HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_IN          \
        in_dword(HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_ADDR)
#define HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_ADDR, m)
#define HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_ADDR,v)
#define HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_ADDR,m,v,HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_IN)
#define HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_HW_CLK_CONTROL_BMSK                                                 0x100000
#define HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_HW_CLK_CONTROL_SHFT                                                     0x14
#define HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_RCGLITE_DISABLE_BMSK                                                 0x10000
#define HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_RCGLITE_DISABLE_SHFT                                                    0x10
#define HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_SRC_SEL_BMSK                                                           0x700
#define HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_SRC_SEL_SHFT                                                             0x8
#define HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_SRC_DIV_BMSK                                                            0x1f
#define HWIO_GCC_MMNOC_SF_QX_CFG_RCGR_SRC_DIV_SHFT                                                             0x0

#define HWIO_GCC_MMNOC_SF_QX_AACSR_ADDR                                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x000733b8)
#define HWIO_GCC_MMNOC_SF_QX_AACSR_RMSK                                                                 0x9e0001ff
#define HWIO_GCC_MMNOC_SF_QX_AACSR_IN          \
        in_dword(HWIO_GCC_MMNOC_SF_QX_AACSR_ADDR)
#define HWIO_GCC_MMNOC_SF_QX_AACSR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_SF_QX_AACSR_ADDR, m)
#define HWIO_GCC_MMNOC_SF_QX_AACSR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_SF_QX_AACSR_ADDR,v)
#define HWIO_GCC_MMNOC_SF_QX_AACSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_SF_QX_AACSR_ADDR,m,v,HWIO_GCC_MMNOC_SF_QX_AACSR_IN)
#define HWIO_GCC_MMNOC_SF_QX_AACSR_AACS_CLK_ON_BMSK                                                     0x80000000
#define HWIO_GCC_MMNOC_SF_QX_AACSR_AACS_CLK_ON_SHFT                                                           0x1f
#define HWIO_GCC_MMNOC_SF_QX_AACSR_AACS_DBG_OUT_BMSK                                                    0x1e000000
#define HWIO_GCC_MMNOC_SF_QX_AACSR_AACS_DBG_OUT_SHFT                                                          0x19
#define HWIO_GCC_MMNOC_SF_QX_AACSR_AACS_MODE_BMSK                                                            0x1c0
#define HWIO_GCC_MMNOC_SF_QX_AACSR_AACS_MODE_SHFT                                                              0x6
#define HWIO_GCC_MMNOC_SF_QX_AACSR_AACS_MPW_CFG_BMSK                                                          0x30
#define HWIO_GCC_MMNOC_SF_QX_AACSR_AACS_MPW_CFG_SHFT                                                           0x4
#define HWIO_GCC_MMNOC_SF_QX_AACSR_AACS_DBG_BUS_SEL_BMSK                                                       0xc
#define HWIO_GCC_MMNOC_SF_QX_AACSR_AACS_DBG_BUS_SEL_SHFT                                                       0x2
#define HWIO_GCC_MMNOC_SF_QX_AACSR_AACS_CGC_HANDSHAKE_DIS_BMSK                                                 0x2
#define HWIO_GCC_MMNOC_SF_QX_AACSR_AACS_CGC_HANDSHAKE_DIS_SHFT                                                 0x1
#define HWIO_GCC_MMNOC_SF_QX_AACSR_AACS_EN_BMSK                                                                0x1
#define HWIO_GCC_MMNOC_SF_QX_AACSR_AACS_EN_SHFT                                                                0x0

#define HWIO_GCC_MMNOC_SF_QX_DCD_CDIV_DCDR_ADDR                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x000733c8)
#define HWIO_GCC_MMNOC_SF_QX_DCD_CDIV_DCDR_RMSK                                                                0x3
#define HWIO_GCC_MMNOC_SF_QX_DCD_CDIV_DCDR_IN          \
        in_dword(HWIO_GCC_MMNOC_SF_QX_DCD_CDIV_DCDR_ADDR)
#define HWIO_GCC_MMNOC_SF_QX_DCD_CDIV_DCDR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_SF_QX_DCD_CDIV_DCDR_ADDR, m)
#define HWIO_GCC_MMNOC_SF_QX_DCD_CDIV_DCDR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_SF_QX_DCD_CDIV_DCDR_ADDR,v)
#define HWIO_GCC_MMNOC_SF_QX_DCD_CDIV_DCDR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_SF_QX_DCD_CDIV_DCDR_ADDR,m,v,HWIO_GCC_MMNOC_SF_QX_DCD_CDIV_DCDR_IN)
#define HWIO_GCC_MMNOC_SF_QX_DCD_CDIV_DCDR_IGNORE_ALL_FSM_CLK_ACTV_BMSK                                        0x2
#define HWIO_GCC_MMNOC_SF_QX_DCD_CDIV_DCDR_IGNORE_ALL_FSM_CLK_ACTV_SHFT                                        0x1
#define HWIO_GCC_MMNOC_SF_QX_DCD_CDIV_DCDR_DCD_ENABLE_BMSK                                                     0x1
#define HWIO_GCC_MMNOC_SF_QX_DCD_CDIV_DCDR_DCD_ENABLE_SHFT                                                     0x0

#define HWIO_GCC_MMNOC_BCR_ADDR                                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c000)
#define HWIO_GCC_MMNOC_BCR_RMSK                                                                                0x1
#define HWIO_GCC_MMNOC_BCR_IN          \
        in_dword(HWIO_GCC_MMNOC_BCR_ADDR)
#define HWIO_GCC_MMNOC_BCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_BCR_ADDR, m)
#define HWIO_GCC_MMNOC_BCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_BCR_ADDR,v)
#define HWIO_GCC_MMNOC_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_BCR_ADDR,m,v,HWIO_GCC_MMNOC_BCR_IN)
#define HWIO_GCC_MMNOC_BCR_BLK_ARES_BMSK                                                                       0x1
#define HWIO_GCC_MMNOC_BCR_BLK_ARES_SHFT                                                                       0x0

#define HWIO_GCC_MMNOC_GDSCR_ADDR                                                                       (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c004)
#define HWIO_GCC_MMNOC_GDSCR_RMSK                                                                       0xf8ffffff
#define HWIO_GCC_MMNOC_GDSCR_IN          \
        in_dword(HWIO_GCC_MMNOC_GDSCR_ADDR)
#define HWIO_GCC_MMNOC_GDSCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_GDSCR_ADDR, m)
#define HWIO_GCC_MMNOC_GDSCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_GDSCR_ADDR,v)
#define HWIO_GCC_MMNOC_GDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_GDSCR_ADDR,m,v,HWIO_GCC_MMNOC_GDSCR_IN)
#define HWIO_GCC_MMNOC_GDSCR_PWR_ON_BMSK                                                                0x80000000
#define HWIO_GCC_MMNOC_GDSCR_PWR_ON_SHFT                                                                      0x1f
#define HWIO_GCC_MMNOC_GDSCR_GDSC_STATE_BMSK                                                            0x78000000
#define HWIO_GCC_MMNOC_GDSCR_GDSC_STATE_SHFT                                                                  0x1b
#define HWIO_GCC_MMNOC_GDSCR_EN_REST_WAIT_BMSK                                                            0xf00000
#define HWIO_GCC_MMNOC_GDSCR_EN_REST_WAIT_SHFT                                                                0x14
#define HWIO_GCC_MMNOC_GDSCR_EN_FEW_WAIT_BMSK                                                              0xf0000
#define HWIO_GCC_MMNOC_GDSCR_EN_FEW_WAIT_SHFT                                                                 0x10
#define HWIO_GCC_MMNOC_GDSCR_CLK_DIS_WAIT_BMSK                                                              0xf000
#define HWIO_GCC_MMNOC_GDSCR_CLK_DIS_WAIT_SHFT                                                                 0xc
#define HWIO_GCC_MMNOC_GDSCR_RETAIN_FF_ENABLE_BMSK                                                           0x800
#define HWIO_GCC_MMNOC_GDSCR_RETAIN_FF_ENABLE_SHFT                                                             0xb
#define HWIO_GCC_MMNOC_GDSCR_RESTORE_BMSK                                                                    0x400
#define HWIO_GCC_MMNOC_GDSCR_RESTORE_SHFT                                                                      0xa
#define HWIO_GCC_MMNOC_GDSCR_SAVE_BMSK                                                                       0x200
#define HWIO_GCC_MMNOC_GDSCR_SAVE_SHFT                                                                         0x9
#define HWIO_GCC_MMNOC_GDSCR_RETAIN_BMSK                                                                     0x100
#define HWIO_GCC_MMNOC_GDSCR_RETAIN_SHFT                                                                       0x8
#define HWIO_GCC_MMNOC_GDSCR_EN_REST_BMSK                                                                     0x80
#define HWIO_GCC_MMNOC_GDSCR_EN_REST_SHFT                                                                      0x7
#define HWIO_GCC_MMNOC_GDSCR_EN_FEW_BMSK                                                                      0x40
#define HWIO_GCC_MMNOC_GDSCR_EN_FEW_SHFT                                                                       0x6
#define HWIO_GCC_MMNOC_GDSCR_CLAMP_IO_BMSK                                                                    0x20
#define HWIO_GCC_MMNOC_GDSCR_CLAMP_IO_SHFT                                                                     0x5
#define HWIO_GCC_MMNOC_GDSCR_CLK_DISABLE_BMSK                                                                 0x10
#define HWIO_GCC_MMNOC_GDSCR_CLK_DISABLE_SHFT                                                                  0x4
#define HWIO_GCC_MMNOC_GDSCR_PD_ARES_BMSK                                                                      0x8
#define HWIO_GCC_MMNOC_GDSCR_PD_ARES_SHFT                                                                      0x3
#define HWIO_GCC_MMNOC_GDSCR_SW_OVERRIDE_BMSK                                                                  0x4
#define HWIO_GCC_MMNOC_GDSCR_SW_OVERRIDE_SHFT                                                                  0x2
#define HWIO_GCC_MMNOC_GDSCR_HW_CONTROL_BMSK                                                                   0x2
#define HWIO_GCC_MMNOC_GDSCR_HW_CONTROL_SHFT                                                                   0x1
#define HWIO_GCC_MMNOC_GDSCR_SW_COLLAPSE_BMSK                                                                  0x1
#define HWIO_GCC_MMNOC_GDSCR_SW_COLLAPSE_SHFT                                                                  0x0

#define HWIO_GCC_MMNOC_CFG_GDSCR_ADDR                                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c008)
#define HWIO_GCC_MMNOC_CFG_GDSCR_RMSK                                                                    0x7ffffff
#define HWIO_GCC_MMNOC_CFG_GDSCR_IN          \
        in_dword(HWIO_GCC_MMNOC_CFG_GDSCR_ADDR)
#define HWIO_GCC_MMNOC_CFG_GDSCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_CFG_GDSCR_ADDR, m)
#define HWIO_GCC_MMNOC_CFG_GDSCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_CFG_GDSCR_ADDR,v)
#define HWIO_GCC_MMNOC_CFG_GDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_CFG_GDSCR_ADDR,m,v,HWIO_GCC_MMNOC_CFG_GDSCR_IN)
#define HWIO_GCC_MMNOC_CFG_GDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_BMSK                                         0x4000000
#define HWIO_GCC_MMNOC_CFG_GDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_SHFT                                              0x1a
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_PWR_DWN_START_BMSK                                                 0x2000000
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_PWR_DWN_START_SHFT                                                      0x19
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_PWR_UP_START_BMSK                                                  0x1000000
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_PWR_UP_START_SHFT                                                       0x18
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_CFG_FSM_STATE_STATUS_BMSK                                           0xf00000
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_CFG_FSM_STATE_STATUS_SHFT                                               0x14
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_MEM_PWR_ACK_STATUS_BMSK                                              0x80000
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_MEM_PWR_ACK_STATUS_SHFT                                                 0x13
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_ENR_ACK_STATUS_BMSK                                                  0x40000
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_ENR_ACK_STATUS_SHFT                                                     0x12
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_ENF_ACK_STATUS_BMSK                                                  0x20000
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_ENF_ACK_STATUS_SHFT                                                     0x11
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_POWER_UP_COMPLETE_BMSK                                               0x10000
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_POWER_UP_COMPLETE_SHFT                                                  0x10
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_POWER_DOWN_COMPLETE_BMSK                                              0x8000
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_POWER_DOWN_COMPLETE_SHFT                                                 0xf
#define HWIO_GCC_MMNOC_CFG_GDSCR_SOFTWARE_CONTROL_OVERRIDE_BMSK                                             0x7800
#define HWIO_GCC_MMNOC_CFG_GDSCR_SOFTWARE_CONTROL_OVERRIDE_SHFT                                                0xb
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_HANDSHAKE_DIS_BMSK                                                     0x400
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_HANDSHAKE_DIS_SHFT                                                       0xa
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_MEM_PERI_FORCE_IN_SW_BMSK                                              0x200
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_MEM_PERI_FORCE_IN_SW_SHFT                                                0x9
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_MEM_CORE_FORCE_IN_SW_BMSK                                              0x100
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_MEM_CORE_FORCE_IN_SW_SHFT                                                0x8
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_PHASE_RESET_EN_SW_BMSK                                                  0x80
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_PHASE_RESET_EN_SW_SHFT                                                   0x7
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_PHASE_RESET_DELAY_COUNT_SW_BMSK                                         0x60
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_PHASE_RESET_DELAY_COUNT_SW_SHFT                                          0x5
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_PSCBC_PWR_DWN_SW_BMSK                                                   0x10
#define HWIO_GCC_MMNOC_CFG_GDSCR_GDSC_PSCBC_PWR_DWN_SW_SHFT                                                    0x4
#define HWIO_GCC_MMNOC_CFG_GDSCR_UNCLAMP_IO_SOFTWARE_OVERRIDE_BMSK                                             0x8
#define HWIO_GCC_MMNOC_CFG_GDSCR_UNCLAMP_IO_SOFTWARE_OVERRIDE_SHFT                                             0x3
#define HWIO_GCC_MMNOC_CFG_GDSCR_SAVE_RESTORE_SOFTWARE_OVERRIDE_BMSK                                           0x4
#define HWIO_GCC_MMNOC_CFG_GDSCR_SAVE_RESTORE_SOFTWARE_OVERRIDE_SHFT                                           0x2
#define HWIO_GCC_MMNOC_CFG_GDSCR_CLAMP_IO_SOFTWARE_OVERRIDE_BMSK                                               0x2
#define HWIO_GCC_MMNOC_CFG_GDSCR_CLAMP_IO_SOFTWARE_OVERRIDE_SHFT                                               0x1
#define HWIO_GCC_MMNOC_CFG_GDSCR_DISABLE_CLK_SOFTWARE_OVERRIDE_BMSK                                            0x1
#define HWIO_GCC_MMNOC_CFG_GDSCR_DISABLE_CLK_SOFTWARE_OVERRIDE_SHFT                                            0x0

#define HWIO_GCC_MMNOC_CFG2_GDSCR_ADDR                                                                  (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c00c)
#define HWIO_GCC_MMNOC_CFG2_GDSCR_RMSK                                                                     0x7ffff
#define HWIO_GCC_MMNOC_CFG2_GDSCR_IN          \
        in_dword(HWIO_GCC_MMNOC_CFG2_GDSCR_ADDR)
#define HWIO_GCC_MMNOC_CFG2_GDSCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_CFG2_GDSCR_ADDR, m)
#define HWIO_GCC_MMNOC_CFG2_GDSCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_CFG2_GDSCR_ADDR,v)
#define HWIO_GCC_MMNOC_CFG2_GDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_CFG2_GDSCR_ADDR,m,v,HWIO_GCC_MMNOC_CFG2_GDSCR_IN)
#define HWIO_GCC_MMNOC_CFG2_GDSCR_GDSC_MEM_PWRUP_ACK_OVERRIDE_BMSK                                         0x40000
#define HWIO_GCC_MMNOC_CFG2_GDSCR_GDSC_MEM_PWRUP_ACK_OVERRIDE_SHFT                                            0x12
#define HWIO_GCC_MMNOC_CFG2_GDSCR_GDSC_PWRDWN_ENABLE_ACK_OVERRIDE_BMSK                                     0x20000
#define HWIO_GCC_MMNOC_CFG2_GDSCR_GDSC_PWRDWN_ENABLE_ACK_OVERRIDE_SHFT                                        0x11
#define HWIO_GCC_MMNOC_CFG2_GDSCR_GDSC_CLAMP_MEM_SW_BMSK                                                   0x10000
#define HWIO_GCC_MMNOC_CFG2_GDSCR_GDSC_CLAMP_MEM_SW_SHFT                                                      0x10
#define HWIO_GCC_MMNOC_CFG2_GDSCR_DLY_MEM_PWR_UP_BMSK                                                       0xf000
#define HWIO_GCC_MMNOC_CFG2_GDSCR_DLY_MEM_PWR_UP_SHFT                                                          0xc
#define HWIO_GCC_MMNOC_CFG2_GDSCR_DLY_DEASSERT_CLAMP_MEM_BMSK                                                0xf00
#define HWIO_GCC_MMNOC_CFG2_GDSCR_DLY_DEASSERT_CLAMP_MEM_SHFT                                                  0x8
#define HWIO_GCC_MMNOC_CFG2_GDSCR_DLY_ASSERT_CLAMP_MEM_BMSK                                                   0xf0
#define HWIO_GCC_MMNOC_CFG2_GDSCR_DLY_ASSERT_CLAMP_MEM_SHFT                                                    0x4
#define HWIO_GCC_MMNOC_CFG2_GDSCR_MEM_PWR_DWN_TIMEOUT_BMSK                                                     0xf
#define HWIO_GCC_MMNOC_CFG2_GDSCR_MEM_PWR_DWN_TIMEOUT_SHFT                                                     0x0

#define HWIO_GCC_MMNOC_CFG3_GDSCR_ADDR                                                                  (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c010)
#define HWIO_GCC_MMNOC_CFG3_GDSCR_RMSK                                                                   0x7ffffff
#define HWIO_GCC_MMNOC_CFG3_GDSCR_IN          \
        in_dword(HWIO_GCC_MMNOC_CFG3_GDSCR_ADDR)
#define HWIO_GCC_MMNOC_CFG3_GDSCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_CFG3_GDSCR_ADDR, m)
#define HWIO_GCC_MMNOC_CFG3_GDSCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_CFG3_GDSCR_ADDR,v)
#define HWIO_GCC_MMNOC_CFG3_GDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_CFG3_GDSCR_ADDR,m,v,HWIO_GCC_MMNOC_CFG3_GDSCR_IN)
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_DONE_STATUS_BMSK                                 0x4000000
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_DONE_STATUS_SHFT                                      0x1a
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_ACCU_RED_ENABLE_BMSK                                              0x2000000
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_ACCU_RED_ENABLE_SHFT                                                   0x19
#define HWIO_GCC_MMNOC_CFG3_GDSCR_DLY_ACCU_RED_SHIFTER_DONE_BMSK                                         0x1e00000
#define HWIO_GCC_MMNOC_CFG3_GDSCR_DLY_ACCU_RED_SHIFTER_DONE_SHFT                                              0x15
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_ACCU_RED_TIMER_EN_SW_BMSK                                          0x100000
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_ACCU_RED_TIMER_EN_SW_SHFT                                              0x14
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_DONE_OVERRIDE_BMSK                                 0x80000
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_DONE_OVERRIDE_SHFT                                    0x13
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_CLK_EN_SW_BMSK                                     0x40000
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_CLK_EN_SW_SHFT                                        0x12
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_START_SW_BMSK                                      0x20000
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_ACCU_RED_SHIFTER_START_SW_SHFT                                         0x11
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_ACCU_RED_SW_OVERRIDE_BMSK                                           0x10000
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_ACCU_RED_SW_OVERRIDE_SHFT                                              0x10
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_SPARE_CTRL_IN_BMSK                                                   0xff00
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_SPARE_CTRL_IN_SHFT                                                      0x8
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_SPARE_CTRL_OUT_BMSK                                                    0xff
#define HWIO_GCC_MMNOC_CFG3_GDSCR_GDSC_SPARE_CTRL_OUT_SHFT                                                     0x0

#define HWIO_GCC_MMNOC_CFG4_GDSCR_ADDR                                                                  (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c014)
#define HWIO_GCC_MMNOC_CFG4_GDSCR_RMSK                                                                    0xffffff
#define HWIO_GCC_MMNOC_CFG4_GDSCR_IN          \
        in_dword(HWIO_GCC_MMNOC_CFG4_GDSCR_ADDR)
#define HWIO_GCC_MMNOC_CFG4_GDSCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_CFG4_GDSCR_ADDR, m)
#define HWIO_GCC_MMNOC_CFG4_GDSCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_CFG4_GDSCR_ADDR,v)
#define HWIO_GCC_MMNOC_CFG4_GDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_CFG4_GDSCR_ADDR,m,v,HWIO_GCC_MMNOC_CFG4_GDSCR_IN)
#define HWIO_GCC_MMNOC_CFG4_GDSCR_DLY_UNCLAMPIO_BMSK                                                      0xf00000
#define HWIO_GCC_MMNOC_CFG4_GDSCR_DLY_UNCLAMPIO_SHFT                                                          0x14
#define HWIO_GCC_MMNOC_CFG4_GDSCR_DLY_RESTOREFF_BMSK                                                       0xf0000
#define HWIO_GCC_MMNOC_CFG4_GDSCR_DLY_RESTOREFF_SHFT                                                          0x10
#define HWIO_GCC_MMNOC_CFG4_GDSCR_DLY_NORETAINFF_BMSK                                                       0xf000
#define HWIO_GCC_MMNOC_CFG4_GDSCR_DLY_NORETAINFF_SHFT                                                          0xc
#define HWIO_GCC_MMNOC_CFG4_GDSCR_DLY_DEASSERTARES_BMSK                                                      0xf00
#define HWIO_GCC_MMNOC_CFG4_GDSCR_DLY_DEASSERTARES_SHFT                                                        0x8
#define HWIO_GCC_MMNOC_CFG4_GDSCR_DLY_CLAMPIO_BMSK                                                            0xf0
#define HWIO_GCC_MMNOC_CFG4_GDSCR_DLY_CLAMPIO_SHFT                                                             0x4
#define HWIO_GCC_MMNOC_CFG4_GDSCR_DLY_RETAINFF_BMSK                                                            0xf
#define HWIO_GCC_MMNOC_CFG4_GDSCR_DLY_RETAINFF_SHFT                                                            0x0

#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_ADDR                                                           (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c018)
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_RMSK                                                           0xfc0003ff
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_IN          \
        in_dword(HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_ADDR)
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_ADDR, m)
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_ADDR,v)
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_ADDR,m,v,HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_IN)
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_PWR_ON_STATUS_BMSK                                             0x80000000
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_PWR_ON_STATUS_SHFT                                                   0x1f
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_GDS_HW_STATE_BMSK                                              0x7c000000
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_GDS_HW_STATE_SHFT                                                    0x1a
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_POWER_UP_COMPLETE_BMSK                                              0x200
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_POWER_UP_COMPLETE_SHFT                                                0x9
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_POWER_DOWN_COMPLETE_BMSK                                            0x100
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_POWER_DOWN_COMPLETE_SHFT                                              0x8
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_DYNAMIC_INTERFACE_CFG_BMSK                                           0xe0
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_DYNAMIC_INTERFACE_CFG_SHFT                                            0x5
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_DENY_ENABLE_BMSK                                                     0x10
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_DENY_ENABLE_SHFT                                                      0x4
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_COLLAPSE_OUT_BMSK                                                     0x8
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_COLLAPSE_OUT_SHFT                                                     0x3
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_HW_CONTROL_BMSK                                                       0x4
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_HW_CONTROL_SHFT                                                       0x2
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_SW_COLLAPSE_BMSK                                                      0x2
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_SW_COLLAPSE_SHFT                                                      0x1
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_SW_OVERRIDE_BMSK                                                      0x1
#define HWIO_GCC_MMNOC_HW_CTRL_CFG1_GDSR_SW_OVERRIDE_SHFT                                                      0x0

#define HWIO_GCC_MMNOC_HW_CTRL_CFG2_GDSR_ADDR                                                           (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c01c)
#define HWIO_GCC_MMNOC_HW_CTRL_CFG2_GDSR_RMSK                                                              0xfffff
#define HWIO_GCC_MMNOC_HW_CTRL_CFG2_GDSR_IN          \
        in_dword(HWIO_GCC_MMNOC_HW_CTRL_CFG2_GDSR_ADDR)
#define HWIO_GCC_MMNOC_HW_CTRL_CFG2_GDSR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HW_CTRL_CFG2_GDSR_ADDR, m)
#define HWIO_GCC_MMNOC_HW_CTRL_CFG2_GDSR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HW_CTRL_CFG2_GDSR_ADDR,v)
#define HWIO_GCC_MMNOC_HW_CTRL_CFG2_GDSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HW_CTRL_CFG2_GDSR_ADDR,m,v,HWIO_GCC_MMNOC_HW_CTRL_CFG2_GDSR_IN)
#define HWIO_GCC_MMNOC_HW_CTRL_CFG2_GDSR_MAX_RETRY_BMSK                                                    0xf0000
#define HWIO_GCC_MMNOC_HW_CTRL_CFG2_GDSR_MAX_RETRY_SHFT                                                       0x10
#define HWIO_GCC_MMNOC_HW_CTRL_CFG2_GDSR_HYSTERESIS_TIMER_BMSK                                              0xff00
#define HWIO_GCC_MMNOC_HW_CTRL_CFG2_GDSR_HYSTERESIS_TIMER_SHFT                                                 0x8
#define HWIO_GCC_MMNOC_HW_CTRL_CFG2_GDSR_HALT_ACK_TIMEOUT_BMSK                                                0xff
#define HWIO_GCC_MMNOC_HW_CTRL_CFG2_GDSR_HALT_ACK_TIMEOUT_SHFT                                                 0x0

#define HWIO_GCC_MMNOC_HW_CTRL_DVM_STATUS_GDSR_ADDR                                                     (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c020)
#define HWIO_GCC_MMNOC_HW_CTRL_DVM_STATUS_GDSR_RMSK                                                     0xffffffff
#define HWIO_GCC_MMNOC_HW_CTRL_DVM_STATUS_GDSR_IN          \
        in_dword(HWIO_GCC_MMNOC_HW_CTRL_DVM_STATUS_GDSR_ADDR)
#define HWIO_GCC_MMNOC_HW_CTRL_DVM_STATUS_GDSR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HW_CTRL_DVM_STATUS_GDSR_ADDR, m)
#define HWIO_GCC_MMNOC_HW_CTRL_DVM_STATUS_GDSR_DVM_HALT1_PWR_DOWN_DENY_STATUS_BMSK                      0xff000000
#define HWIO_GCC_MMNOC_HW_CTRL_DVM_STATUS_GDSR_DVM_HALT1_PWR_DOWN_DENY_STATUS_SHFT                            0x18
#define HWIO_GCC_MMNOC_HW_CTRL_DVM_STATUS_GDSR_DVM_HALT1_PWR_UP_ACK_STATUS_BMSK                           0xff0000
#define HWIO_GCC_MMNOC_HW_CTRL_DVM_STATUS_GDSR_DVM_HALT1_PWR_UP_ACK_STATUS_SHFT                               0x10
#define HWIO_GCC_MMNOC_HW_CTRL_DVM_STATUS_GDSR_DVM_HALT1_PWR_DOWN_ACK_STATUS_BMSK                           0xff00
#define HWIO_GCC_MMNOC_HW_CTRL_DVM_STATUS_GDSR_DVM_HALT1_PWR_DOWN_ACK_STATUS_SHFT                              0x8
#define HWIO_GCC_MMNOC_HW_CTRL_DVM_STATUS_GDSR_DVM_HALT1_REQ_STATUS_BMSK                                      0xff
#define HWIO_GCC_MMNOC_HW_CTRL_DVM_STATUS_GDSR_DVM_HALT1_REQ_STATUS_SHFT                                       0x0

#define HWIO_GCC_MMNOC_HW_CTRL_HALT1_STATUS_GDSR_ADDR                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c024)
#define HWIO_GCC_MMNOC_HW_CTRL_HALT1_STATUS_GDSR_RMSK                                                   0xffffffff
#define HWIO_GCC_MMNOC_HW_CTRL_HALT1_STATUS_GDSR_IN          \
        in_dword(HWIO_GCC_MMNOC_HW_CTRL_HALT1_STATUS_GDSR_ADDR)
#define HWIO_GCC_MMNOC_HW_CTRL_HALT1_STATUS_GDSR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HW_CTRL_HALT1_STATUS_GDSR_ADDR, m)
#define HWIO_GCC_MMNOC_HW_CTRL_HALT1_STATUS_GDSR_HALT1_PWR_DOWN_DENY_STATUS_BMSK                        0xff000000
#define HWIO_GCC_MMNOC_HW_CTRL_HALT1_STATUS_GDSR_HALT1_PWR_DOWN_DENY_STATUS_SHFT                              0x18
#define HWIO_GCC_MMNOC_HW_CTRL_HALT1_STATUS_GDSR_HALT1_PWR_UP_ACK_STATUS_BMSK                             0xff0000
#define HWIO_GCC_MMNOC_HW_CTRL_HALT1_STATUS_GDSR_HALT1_PWR_UP_ACK_STATUS_SHFT                                 0x10
#define HWIO_GCC_MMNOC_HW_CTRL_HALT1_STATUS_GDSR_HALT1_PWR_DOWN_ACK_STATUS_BMSK                             0xff00
#define HWIO_GCC_MMNOC_HW_CTRL_HALT1_STATUS_GDSR_HALT1_PWR_DOWN_ACK_STATUS_SHFT                                0x8
#define HWIO_GCC_MMNOC_HW_CTRL_HALT1_STATUS_GDSR_HALT1_REQ_STATUS_BMSK                                        0xff
#define HWIO_GCC_MMNOC_HW_CTRL_HALT1_STATUS_GDSR_HALT1_REQ_STATUS_SHFT                                         0x0

#define HWIO_GCC_MMNOC_HW_CTRL_HALT2_STATUS_GDSR_ADDR                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c028)
#define HWIO_GCC_MMNOC_HW_CTRL_HALT2_STATUS_GDSR_RMSK                                                   0xffffffff
#define HWIO_GCC_MMNOC_HW_CTRL_HALT2_STATUS_GDSR_IN          \
        in_dword(HWIO_GCC_MMNOC_HW_CTRL_HALT2_STATUS_GDSR_ADDR)
#define HWIO_GCC_MMNOC_HW_CTRL_HALT2_STATUS_GDSR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HW_CTRL_HALT2_STATUS_GDSR_ADDR, m)
#define HWIO_GCC_MMNOC_HW_CTRL_HALT2_STATUS_GDSR_HALT2_PWR_DOWN_DENY_STATUS_BMSK                        0xff000000
#define HWIO_GCC_MMNOC_HW_CTRL_HALT2_STATUS_GDSR_HALT2_PWR_DOWN_DENY_STATUS_SHFT                              0x18
#define HWIO_GCC_MMNOC_HW_CTRL_HALT2_STATUS_GDSR_HALT2_PWR_UP_ACK_STATUS_BMSK                             0xff0000
#define HWIO_GCC_MMNOC_HW_CTRL_HALT2_STATUS_GDSR_HALT2_PWR_UP_ACK_STATUS_SHFT                                 0x10
#define HWIO_GCC_MMNOC_HW_CTRL_HALT2_STATUS_GDSR_HALT2_PWR_DOWN_ACK_STATUS_BMSK                             0xff00
#define HWIO_GCC_MMNOC_HW_CTRL_HALT2_STATUS_GDSR_HALT2_PWR_DOWN_ACK_STATUS_SHFT                                0x8
#define HWIO_GCC_MMNOC_HW_CTRL_HALT2_STATUS_GDSR_HALT2_REQ_STATUS_BMSK                                        0xff
#define HWIO_GCC_MMNOC_HW_CTRL_HALT2_STATUS_GDSR_HALT2_REQ_STATUS_SHFT                                         0x0

#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SW_GDSR_ADDR                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c02c)
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SW_GDSR_RMSK                                                           0xffffff
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SW_GDSR_IN          \
        in_dword(HWIO_GCC_MMNOC_HW_CTRL_REQ_SW_GDSR_ADDR)
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SW_GDSR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HW_CTRL_REQ_SW_GDSR_ADDR, m)
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SW_GDSR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HW_CTRL_REQ_SW_GDSR_ADDR,v)
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SW_GDSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HW_CTRL_REQ_SW_GDSR_ADDR,m,v,HWIO_GCC_MMNOC_HW_CTRL_REQ_SW_GDSR_IN)
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SW_GDSR_HALT2_REQ_SW_BMSK                                              0xff0000
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SW_GDSR_HALT2_REQ_SW_SHFT                                                  0x10
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SW_GDSR_HALT1_REQ_SW_BMSK                                                0xff00
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SW_GDSR_HALT1_REQ_SW_SHFT                                                   0x8
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SW_GDSR_DVM_HALT1_REQ_SW_BMSK                                              0xff
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SW_GDSR_DVM_HALT1_REQ_SW_SHFT                                               0x0

#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_STATUS_GDSR_ADDR                                                     (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c030)
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_STATUS_GDSR_RMSK                                                            0x1
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_STATUS_GDSR_IN          \
        in_dword(HWIO_GCC_MMNOC_HW_CTRL_IRQ_STATUS_GDSR_ADDR)
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_STATUS_GDSR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HW_CTRL_IRQ_STATUS_GDSR_ADDR, m)
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_STATUS_GDSR_IRQ_STATUS_BMSK                                                 0x1
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_STATUS_GDSR_IRQ_STATUS_SHFT                                                 0x0

#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_MASK_GDSR_ADDR                                                       (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c034)
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_MASK_GDSR_RMSK                                                              0x1
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_MASK_GDSR_IN          \
        in_dword(HWIO_GCC_MMNOC_HW_CTRL_IRQ_MASK_GDSR_ADDR)
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_MASK_GDSR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HW_CTRL_IRQ_MASK_GDSR_ADDR, m)
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_MASK_GDSR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HW_CTRL_IRQ_MASK_GDSR_ADDR,v)
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_MASK_GDSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HW_CTRL_IRQ_MASK_GDSR_ADDR,m,v,HWIO_GCC_MMNOC_HW_CTRL_IRQ_MASK_GDSR_IN)
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_MASK_GDSR_IRQ_MASK_BMSK                                                     0x1
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_MASK_GDSR_IRQ_MASK_SHFT                                                     0x0

#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_CLEAR_GDSR_ADDR                                                      (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c038)
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_CLEAR_GDSR_RMSK                                                             0x1
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_CLEAR_GDSR_IN          \
        in_dword(HWIO_GCC_MMNOC_HW_CTRL_IRQ_CLEAR_GDSR_ADDR)
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_CLEAR_GDSR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HW_CTRL_IRQ_CLEAR_GDSR_ADDR, m)
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_CLEAR_GDSR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HW_CTRL_IRQ_CLEAR_GDSR_ADDR,v)
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_CLEAR_GDSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HW_CTRL_IRQ_CLEAR_GDSR_ADDR,m,v,HWIO_GCC_MMNOC_HW_CTRL_IRQ_CLEAR_GDSR_IN)
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_CLEAR_GDSR_IRQ_CLEAR_BMSK                                                   0x1
#define HWIO_GCC_MMNOC_HW_CTRL_IRQ_CLEAR_GDSR_IRQ_CLEAR_SHFT                                                   0x0

#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SPARE_GDSR_ADDR                                                      (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c03c)
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SPARE_GDSR_RMSK                                                            0xff
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SPARE_GDSR_IN          \
        in_dword(HWIO_GCC_MMNOC_HW_CTRL_REQ_SPARE_GDSR_ADDR)
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SPARE_GDSR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HW_CTRL_REQ_SPARE_GDSR_ADDR, m)
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SPARE_GDSR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HW_CTRL_REQ_SPARE_GDSR_ADDR,v)
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SPARE_GDSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HW_CTRL_REQ_SPARE_GDSR_ADDR,m,v,HWIO_GCC_MMNOC_HW_CTRL_REQ_SPARE_GDSR_IN)
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SPARE_GDSR_GDS_HW_CTRL_SPARE_BMSK                                          0xff
#define HWIO_GCC_MMNOC_HW_CTRL_REQ_SPARE_GDSR_GDS_HW_CTRL_SPARE_SHFT                                           0x0

#define HWIO_GCC_MMNOC_HF_AT_CBCR_ADDR                                                                  (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c040)
#define HWIO_GCC_MMNOC_HF_AT_CBCR_RMSK                                                                  0x81d00005
#define HWIO_GCC_MMNOC_HF_AT_CBCR_IN          \
        in_dword(HWIO_GCC_MMNOC_HF_AT_CBCR_ADDR)
#define HWIO_GCC_MMNOC_HF_AT_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HF_AT_CBCR_ADDR, m)
#define HWIO_GCC_MMNOC_HF_AT_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HF_AT_CBCR_ADDR,v)
#define HWIO_GCC_MMNOC_HF_AT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HF_AT_CBCR_ADDR,m,v,HWIO_GCC_MMNOC_HF_AT_CBCR_IN)
#define HWIO_GCC_MMNOC_HF_AT_CBCR_CLK_OFF_BMSK                                                          0x80000000
#define HWIO_GCC_MMNOC_HF_AT_CBCR_CLK_OFF_SHFT                                                                0x1f
#define HWIO_GCC_MMNOC_HF_AT_CBCR_IGNORE_ALL_ARES_BMSK                                                   0x1000000
#define HWIO_GCC_MMNOC_HF_AT_CBCR_IGNORE_ALL_ARES_SHFT                                                        0x18
#define HWIO_GCC_MMNOC_HF_AT_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                                 0x800000
#define HWIO_GCC_MMNOC_HF_AT_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                                     0x17
#define HWIO_GCC_MMNOC_HF_AT_CBCR_CLK_DIS_BMSK                                                            0x400000
#define HWIO_GCC_MMNOC_HF_AT_CBCR_CLK_DIS_SHFT                                                                0x16
#define HWIO_GCC_MMNOC_HF_AT_CBCR_IGNORE_RPMH_CLK_DIS_BMSK                                                0x100000
#define HWIO_GCC_MMNOC_HF_AT_CBCR_IGNORE_RPMH_CLK_DIS_SHFT                                                    0x14
#define HWIO_GCC_MMNOC_HF_AT_CBCR_CLK_ARES_BMSK                                                                0x4
#define HWIO_GCC_MMNOC_HF_AT_CBCR_CLK_ARES_SHFT                                                                0x2
#define HWIO_GCC_MMNOC_HF_AT_CBCR_CLK_ENABLE_BMSK                                                              0x1
#define HWIO_GCC_MMNOC_HF_AT_CBCR_CLK_ENABLE_SHFT                                                              0x0

#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_ADDR                                                             (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c044)
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_RMSK                                                             0x81d0000f
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_IN          \
        in_dword(HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_ADDR)
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_ADDR, m)
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_ADDR,v)
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_ADDR,m,v,HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_IN)
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_CLK_OFF_BMSK                                                     0x80000000
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_CLK_OFF_SHFT                                                           0x1f
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_IGNORE_ALL_ARES_BMSK                                              0x1000000
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_IGNORE_ALL_ARES_SHFT                                                   0x18
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                            0x800000
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                                0x17
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_CLK_DIS_BMSK                                                       0x400000
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_CLK_DIS_SHFT                                                           0x16
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_IGNORE_RPMH_CLK_DIS_BMSK                                           0x100000
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_IGNORE_RPMH_CLK_DIS_SHFT                                               0x14
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_SW_ONLY_EN_BMSK                                                         0x8
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_SW_ONLY_EN_SHFT                                                         0x3
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_CLK_ARES_BMSK                                                           0x4
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_CLK_ARES_SHFT                                                           0x2
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_HW_CTL_BMSK                                                             0x2
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_HW_CTL_SHFT                                                             0x1
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_CLK_ENABLE_BMSK                                                         0x1
#define HWIO_GCC_MMNOC_HF_AHB_CFG_CBCR_CLK_ENABLE_SHFT                                                         0x0

#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_ADDR                                                          (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c048)
#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_RMSK                                                          0x81c00005
#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_IN          \
        in_dword(HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_ADDR)
#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_ADDR, m)
#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_ADDR,v)
#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_ADDR,m,v,HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_IN)
#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_CLK_OFF_BMSK                                                  0x80000000
#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_CLK_OFF_SHFT                                                        0x1f
#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_IGNORE_ALL_ARES_BMSK                                           0x1000000
#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_IGNORE_ALL_ARES_SHFT                                                0x18
#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                         0x800000
#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                             0x17
#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_CLK_DIS_BMSK                                                    0x400000
#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_CLK_DIS_SHFT                                                        0x16
#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_CLK_ARES_BMSK                                                        0x4
#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_CLK_ARES_SHFT                                                        0x2
#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_CLK_ENABLE_BMSK                                                      0x1
#define HWIO_GCC_NOC_MMNOC_HF_DCD_XO_CBCR_CLK_ENABLE_SHFT                                                      0x0

#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_ADDR                                                               (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c04c)
#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_RMSK                                                               0x81c00005
#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_IN          \
        in_dword(HWIO_GCC_MMNOC_HF_TSCTR_CBCR_ADDR)
#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HF_TSCTR_CBCR_ADDR, m)
#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HF_TSCTR_CBCR_ADDR,v)
#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HF_TSCTR_CBCR_ADDR,m,v,HWIO_GCC_MMNOC_HF_TSCTR_CBCR_IN)
#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_IGNORE_ALL_ARES_BMSK                                                0x1000000
#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_IGNORE_ALL_ARES_SHFT                                                     0x18
#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                              0x800000
#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                                  0x17
#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_CLK_DIS_BMSK                                                         0x400000
#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_CLK_DIS_SHFT                                                             0x16
#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_CLK_ARES_BMSK                                                             0x4
#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_CLK_ARES_SHFT                                                             0x2
#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_GCC_MMNOC_HF_TSCTR_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_GCC_MMNOC_HF_QX_CBCR_ADDR                                                                  (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c050)
#define HWIO_GCC_MMNOC_HF_QX_CBCR_RMSK                                                                  0x81f0700f
#define HWIO_GCC_MMNOC_HF_QX_CBCR_IN          \
        in_dword(HWIO_GCC_MMNOC_HF_QX_CBCR_ADDR)
#define HWIO_GCC_MMNOC_HF_QX_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HF_QX_CBCR_ADDR, m)
#define HWIO_GCC_MMNOC_HF_QX_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HF_QX_CBCR_ADDR,v)
#define HWIO_GCC_MMNOC_HF_QX_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HF_QX_CBCR_ADDR,m,v,HWIO_GCC_MMNOC_HF_QX_CBCR_IN)
#define HWIO_GCC_MMNOC_HF_QX_CBCR_CLK_OFF_BMSK                                                          0x80000000
#define HWIO_GCC_MMNOC_HF_QX_CBCR_CLK_OFF_SHFT                                                                0x1f
#define HWIO_GCC_MMNOC_HF_QX_CBCR_IGNORE_ALL_ARES_BMSK                                                   0x1000000
#define HWIO_GCC_MMNOC_HF_QX_CBCR_IGNORE_ALL_ARES_SHFT                                                        0x18
#define HWIO_GCC_MMNOC_HF_QX_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                                 0x800000
#define HWIO_GCC_MMNOC_HF_QX_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                                     0x17
#define HWIO_GCC_MMNOC_HF_QX_CBCR_CLK_DIS_BMSK                                                            0x400000
#define HWIO_GCC_MMNOC_HF_QX_CBCR_CLK_DIS_SHFT                                                                0x16
#define HWIO_GCC_MMNOC_HF_QX_CBCR_IGNORE_PMU_CLK_DIS_BMSK                                                 0x200000
#define HWIO_GCC_MMNOC_HF_QX_CBCR_IGNORE_PMU_CLK_DIS_SHFT                                                     0x15
#define HWIO_GCC_MMNOC_HF_QX_CBCR_IGNORE_RPMH_CLK_DIS_BMSK                                                0x100000
#define HWIO_GCC_MMNOC_HF_QX_CBCR_IGNORE_RPMH_CLK_DIS_SHFT                                                    0x14
#define HWIO_GCC_MMNOC_HF_QX_CBCR_FORCE_MEM_CORE_ON_BMSK                                                    0x4000
#define HWIO_GCC_MMNOC_HF_QX_CBCR_FORCE_MEM_CORE_ON_SHFT                                                       0xe
#define HWIO_GCC_MMNOC_HF_QX_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                  0x2000
#define HWIO_GCC_MMNOC_HF_QX_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                     0xd
#define HWIO_GCC_MMNOC_HF_QX_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                 0x1000
#define HWIO_GCC_MMNOC_HF_QX_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                    0xc
#define HWIO_GCC_MMNOC_HF_QX_CBCR_SW_ONLY_EN_BMSK                                                              0x8
#define HWIO_GCC_MMNOC_HF_QX_CBCR_SW_ONLY_EN_SHFT                                                              0x3
#define HWIO_GCC_MMNOC_HF_QX_CBCR_CLK_ARES_BMSK                                                                0x4
#define HWIO_GCC_MMNOC_HF_QX_CBCR_CLK_ARES_SHFT                                                                0x2
#define HWIO_GCC_MMNOC_HF_QX_CBCR_HW_CTL_BMSK                                                                  0x2
#define HWIO_GCC_MMNOC_HF_QX_CBCR_HW_CTL_SHFT                                                                  0x1
#define HWIO_GCC_MMNOC_HF_QX_CBCR_CLK_ENABLE_BMSK                                                              0x1
#define HWIO_GCC_MMNOC_HF_QX_CBCR_CLK_ENABLE_SHFT                                                              0x0

#define HWIO_GCC_MMNOC_HF_QX_SREGR_ADDR                                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c054)
#define HWIO_GCC_MMNOC_HF_QX_SREGR_RMSK                                                                  0xf1ffffe
#define HWIO_GCC_MMNOC_HF_QX_SREGR_IN          \
        in_dword(HWIO_GCC_MMNOC_HF_QX_SREGR_ADDR)
#define HWIO_GCC_MMNOC_HF_QX_SREGR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HF_QX_SREGR_ADDR, m)
#define HWIO_GCC_MMNOC_HF_QX_SREGR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HF_QX_SREGR_ADDR,v)
#define HWIO_GCC_MMNOC_HF_QX_SREGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HF_QX_SREGR_ADDR,m,v,HWIO_GCC_MMNOC_HF_QX_SREGR_IN)
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SREG_PSCBC_SPARE_CTRL_OUT_BMSK                                        0xf000000
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SREG_PSCBC_SPARE_CTRL_OUT_SHFT                                             0x18
#define HWIO_GCC_MMNOC_HF_QX_SREGR_PWR_FSM_CLK_SEL_BMSK                                                   0x100000
#define HWIO_GCC_MMNOC_HF_QX_SREGR_PWR_FSM_CLK_SEL_SHFT                                                       0x14
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SREG_PSCBC_SPARE_CTRL_IN_BMSK                                           0xf0000
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SREG_PSCBC_SPARE_CTRL_IN_SHFT                                              0x10
#define HWIO_GCC_MMNOC_HF_QX_SREGR_IGNORE_GDSC_PWR_DWN_CSR_BMSK                                             0x8000
#define HWIO_GCC_MMNOC_HF_QX_SREGR_IGNORE_GDSC_PWR_DWN_CSR_SHFT                                                0xf
#define HWIO_GCC_MMNOC_HF_QX_SREGR_PSCBC_SLP_STG_MODE_CSR_BMSK                                              0x4000
#define HWIO_GCC_MMNOC_HF_QX_SREGR_PSCBC_SLP_STG_MODE_CSR_SHFT                                                 0xe
#define HWIO_GCC_MMNOC_HF_QX_SREGR_MEM_CPH_RST_SW_OVERRIDE_BMSK                                             0x2000
#define HWIO_GCC_MMNOC_HF_QX_SREGR_MEM_CPH_RST_SW_OVERRIDE_SHFT                                                0xd
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SW_SM_PSCBC_SEQ_IN_OVERRIDE_BMSK                                         0x1000
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SW_SM_PSCBC_SEQ_IN_OVERRIDE_SHFT                                            0xc
#define HWIO_GCC_MMNOC_HF_QX_SREGR_MEM_CORE_ON_ACK_BMSK                                                      0x800
#define HWIO_GCC_MMNOC_HF_QX_SREGR_MEM_CORE_ON_ACK_SHFT                                                        0xb
#define HWIO_GCC_MMNOC_HF_QX_SREGR_MEM_PERIPH_ON_ACK_BMSK                                                    0x400
#define HWIO_GCC_MMNOC_HF_QX_SREGR_MEM_PERIPH_ON_ACK_SHFT                                                      0xa
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SW_DIV_RATIO_SLP_STG_CLK_BMSK                                             0x300
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SW_DIV_RATIO_SLP_STG_CLK_SHFT                                               0x8
#define HWIO_GCC_MMNOC_HF_QX_SREGR_MEM_CPH_ENABLE_BMSK                                                        0x80
#define HWIO_GCC_MMNOC_HF_QX_SREGR_MEM_CPH_ENABLE_SHFT                                                         0x7
#define HWIO_GCC_MMNOC_HF_QX_SREGR_FORCE_CLK_ON_BMSK                                                          0x40
#define HWIO_GCC_MMNOC_HF_QX_SREGR_FORCE_CLK_ON_SHFT                                                           0x6
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SW_RST_SEL_SLP_STG_BMSK                                                    0x20
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SW_RST_SEL_SLP_STG_SHFT                                                     0x5
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SW_RST_SLP_STG_BMSK                                                        0x10
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SW_RST_SLP_STG_SHFT                                                         0x4
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SW_CTRL_PWR_DOWN_BMSK                                                       0x8
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SW_CTRL_PWR_DOWN_SHFT                                                       0x3
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SW_CLK_EN_SEL_SLP_STG_BMSK                                                  0x4
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SW_CLK_EN_SEL_SLP_STG_SHFT                                                  0x2
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SW_CLK_EN_SLP_STG_BMSK                                                      0x2
#define HWIO_GCC_MMNOC_HF_QX_SREGR_SW_CLK_EN_SLP_STG_SHFT                                                      0x1

#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_ADDR                                                             (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c058)
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_RMSK                                                             0xffffffff
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_IN          \
        in_dword(HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_ADDR)
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_ADDR, m)
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_ADDR,v)
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_ADDR,m,v,HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_IN)
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_MEM_CORE_OFF_TIMER_BMSK                                          0xfc000000
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_MEM_CORE_OFF_TIMER_SHFT                                                0x1a
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_MEM_PERIPH_ON_ACK_STATUS_BMSK                                     0x2000000
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_MEM_PERIPH_ON_ACK_STATUS_SHFT                                          0x19
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_MEM_CORE_ON_ACK_STATUS_BMSK                                       0x1000000
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_MEM_CORE_ON_ACK_STATUS_SHFT                                            0x18
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_MEM_PERIPH_ON_STATUS_BMSK                                          0x800000
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_MEM_PERIPH_ON_STATUS_SHFT                                              0x17
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_MEM_CORE_ON_STATUS_BMSK                                            0x400000
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_MEM_CORE_ON_STATUS_SHFT                                                0x16
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_MEM_CPH_TIMER_BMSK                                                 0x3f0000
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_MEM_CPH_TIMER_SHFT                                                     0x10
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_SLEEP_TIMER_BMSK                                                     0xff00
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_SLEEP_TIMER_SHFT                                                        0x8
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_WAKEUP_TIMER_BMSK                                                      0xff
#define HWIO_GCC_MMNOC_HF_QX_CFG_SREGR_WAKEUP_TIMER_SHFT                                                       0x0

#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_ADDR                                                              (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c05c)
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_RMSK                                                              0x81d0000f
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_IN          \
        in_dword(HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_ADDR)
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_ADDR, m)
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_ADDR,v)
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_ADDR,m,v,HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_IN)
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_IGNORE_ALL_ARES_BMSK                                               0x1000000
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_IGNORE_ALL_ARES_SHFT                                                    0x18
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                             0x800000
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                                 0x17
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_CLK_DIS_BMSK                                                        0x400000
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_CLK_DIS_SHFT                                                            0x16
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_IGNORE_RPMH_CLK_DIS_BMSK                                            0x100000
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_IGNORE_RPMH_CLK_DIS_SHFT                                                0x14
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_SW_ONLY_EN_BMSK                                                          0x8
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_SW_ONLY_EN_SHFT                                                          0x3
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_CLK_ARES_BMSK                                                            0x4
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_CLK_ARES_SHFT                                                            0x2
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_HW_CTL_BMSK                                                              0x2
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_HW_CTL_SHFT                                                              0x1
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_GCC_MMNOC_HF_PWRCTL_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_ADDR                                                       (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c060)
#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_RMSK                                                       0x81c00005
#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_IN          \
        in_dword(HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_ADDR)
#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_ADDR, m)
#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_ADDR,v)
#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_ADDR,m,v,HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_IN)
#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_CLK_OFF_BMSK                                               0x80000000
#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_CLK_OFF_SHFT                                                     0x1f
#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_IGNORE_ALL_ARES_BMSK                                        0x1000000
#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_IGNORE_ALL_ARES_SHFT                                             0x18
#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                      0x800000
#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                          0x17
#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_CLK_DIS_BMSK                                                 0x400000
#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_CLK_DIS_SHFT                                                     0x16
#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_CLK_ARES_BMSK                                                     0x4
#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_CLK_ARES_SHFT                                                     0x2
#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_CLK_ENABLE_BMSK                                                   0x1
#define HWIO_GCC_MMNOC_HF_QOSGEN_EXTREF_CBCR_CLK_ENABLE_SHFT                                                   0x0

#define HWIO_GCC_MMNOC_SF_AT_CBCR_ADDR                                                                  (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c064)
#define HWIO_GCC_MMNOC_SF_AT_CBCR_RMSK                                                                  0x81d00005
#define HWIO_GCC_MMNOC_SF_AT_CBCR_IN          \
        in_dword(HWIO_GCC_MMNOC_SF_AT_CBCR_ADDR)
#define HWIO_GCC_MMNOC_SF_AT_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_SF_AT_CBCR_ADDR, m)
#define HWIO_GCC_MMNOC_SF_AT_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_SF_AT_CBCR_ADDR,v)
#define HWIO_GCC_MMNOC_SF_AT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_SF_AT_CBCR_ADDR,m,v,HWIO_GCC_MMNOC_SF_AT_CBCR_IN)
#define HWIO_GCC_MMNOC_SF_AT_CBCR_CLK_OFF_BMSK                                                          0x80000000
#define HWIO_GCC_MMNOC_SF_AT_CBCR_CLK_OFF_SHFT                                                                0x1f
#define HWIO_GCC_MMNOC_SF_AT_CBCR_IGNORE_ALL_ARES_BMSK                                                   0x1000000
#define HWIO_GCC_MMNOC_SF_AT_CBCR_IGNORE_ALL_ARES_SHFT                                                        0x18
#define HWIO_GCC_MMNOC_SF_AT_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                                 0x800000
#define HWIO_GCC_MMNOC_SF_AT_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                                     0x17
#define HWIO_GCC_MMNOC_SF_AT_CBCR_CLK_DIS_BMSK                                                            0x400000
#define HWIO_GCC_MMNOC_SF_AT_CBCR_CLK_DIS_SHFT                                                                0x16
#define HWIO_GCC_MMNOC_SF_AT_CBCR_IGNORE_RPMH_CLK_DIS_BMSK                                                0x100000
#define HWIO_GCC_MMNOC_SF_AT_CBCR_IGNORE_RPMH_CLK_DIS_SHFT                                                    0x14
#define HWIO_GCC_MMNOC_SF_AT_CBCR_CLK_ARES_BMSK                                                                0x4
#define HWIO_GCC_MMNOC_SF_AT_CBCR_CLK_ARES_SHFT                                                                0x2
#define HWIO_GCC_MMNOC_SF_AT_CBCR_CLK_ENABLE_BMSK                                                              0x1
#define HWIO_GCC_MMNOC_SF_AT_CBCR_CLK_ENABLE_SHFT                                                              0x0

#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_ADDR                                                             (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c068)
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_RMSK                                                             0x81d0000f
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_IN          \
        in_dword(HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_ADDR)
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_ADDR, m)
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_ADDR,v)
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_ADDR,m,v,HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_IN)
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_CLK_OFF_BMSK                                                     0x80000000
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_CLK_OFF_SHFT                                                           0x1f
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_IGNORE_ALL_ARES_BMSK                                              0x1000000
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_IGNORE_ALL_ARES_SHFT                                                   0x18
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                            0x800000
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                                0x17
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_CLK_DIS_BMSK                                                       0x400000
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_CLK_DIS_SHFT                                                           0x16
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_IGNORE_RPMH_CLK_DIS_BMSK                                           0x100000
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_IGNORE_RPMH_CLK_DIS_SHFT                                               0x14
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_SW_ONLY_EN_BMSK                                                         0x8
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_SW_ONLY_EN_SHFT                                                         0x3
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_CLK_ARES_BMSK                                                           0x4
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_CLK_ARES_SHFT                                                           0x2
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_HW_CTL_BMSK                                                             0x2
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_HW_CTL_SHFT                                                             0x1
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_CLK_ENABLE_BMSK                                                         0x1
#define HWIO_GCC_MMNOC_SF_AHB_CFG_CBCR_CLK_ENABLE_SHFT                                                         0x0

#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_ADDR                                                          (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c06c)
#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_RMSK                                                          0x81c00005
#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_IN          \
        in_dword(HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_ADDR)
#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_ADDR, m)
#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_ADDR,v)
#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_ADDR,m,v,HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_IN)
#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_CLK_OFF_BMSK                                                  0x80000000
#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_CLK_OFF_SHFT                                                        0x1f
#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_IGNORE_ALL_ARES_BMSK                                           0x1000000
#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_IGNORE_ALL_ARES_SHFT                                                0x18
#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                         0x800000
#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                             0x17
#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_CLK_DIS_BMSK                                                    0x400000
#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_CLK_DIS_SHFT                                                        0x16
#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_CLK_ARES_BMSK                                                        0x4
#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_CLK_ARES_SHFT                                                        0x2
#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_CLK_ENABLE_BMSK                                                      0x1
#define HWIO_GCC_NOC_MMNOC_SF_DCD_XO_CBCR_CLK_ENABLE_SHFT                                                      0x0

#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_ADDR                                                               (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c070)
#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_RMSK                                                               0x81c00005
#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_IN          \
        in_dword(HWIO_GCC_MMNOC_SF_TSCTR_CBCR_ADDR)
#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_SF_TSCTR_CBCR_ADDR, m)
#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_SF_TSCTR_CBCR_ADDR,v)
#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_SF_TSCTR_CBCR_ADDR,m,v,HWIO_GCC_MMNOC_SF_TSCTR_CBCR_IN)
#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_IGNORE_ALL_ARES_BMSK                                                0x1000000
#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_IGNORE_ALL_ARES_SHFT                                                     0x18
#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                              0x800000
#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                                  0x17
#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_CLK_DIS_BMSK                                                         0x400000
#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_CLK_DIS_SHFT                                                             0x16
#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_CLK_ARES_BMSK                                                             0x4
#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_CLK_ARES_SHFT                                                             0x2
#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_GCC_MMNOC_SF_TSCTR_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_GCC_MMNOC_SF_CBCR_ADDR                                                                     (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c074)
#define HWIO_GCC_MMNOC_SF_CBCR_RMSK                                                                     0x81f0700f
#define HWIO_GCC_MMNOC_SF_CBCR_IN          \
        in_dword(HWIO_GCC_MMNOC_SF_CBCR_ADDR)
#define HWIO_GCC_MMNOC_SF_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_SF_CBCR_ADDR, m)
#define HWIO_GCC_MMNOC_SF_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_SF_CBCR_ADDR,v)
#define HWIO_GCC_MMNOC_SF_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_SF_CBCR_ADDR,m,v,HWIO_GCC_MMNOC_SF_CBCR_IN)
#define HWIO_GCC_MMNOC_SF_CBCR_CLK_OFF_BMSK                                                             0x80000000
#define HWIO_GCC_MMNOC_SF_CBCR_CLK_OFF_SHFT                                                                   0x1f
#define HWIO_GCC_MMNOC_SF_CBCR_IGNORE_ALL_ARES_BMSK                                                      0x1000000
#define HWIO_GCC_MMNOC_SF_CBCR_IGNORE_ALL_ARES_SHFT                                                           0x18
#define HWIO_GCC_MMNOC_SF_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                                    0x800000
#define HWIO_GCC_MMNOC_SF_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                                        0x17
#define HWIO_GCC_MMNOC_SF_CBCR_CLK_DIS_BMSK                                                               0x400000
#define HWIO_GCC_MMNOC_SF_CBCR_CLK_DIS_SHFT                                                                   0x16
#define HWIO_GCC_MMNOC_SF_CBCR_IGNORE_PMU_CLK_DIS_BMSK                                                    0x200000
#define HWIO_GCC_MMNOC_SF_CBCR_IGNORE_PMU_CLK_DIS_SHFT                                                        0x15
#define HWIO_GCC_MMNOC_SF_CBCR_IGNORE_RPMH_CLK_DIS_BMSK                                                   0x100000
#define HWIO_GCC_MMNOC_SF_CBCR_IGNORE_RPMH_CLK_DIS_SHFT                                                       0x14
#define HWIO_GCC_MMNOC_SF_CBCR_FORCE_MEM_CORE_ON_BMSK                                                       0x4000
#define HWIO_GCC_MMNOC_SF_CBCR_FORCE_MEM_CORE_ON_SHFT                                                          0xe
#define HWIO_GCC_MMNOC_SF_CBCR_FORCE_MEM_PERIPH_ON_BMSK                                                     0x2000
#define HWIO_GCC_MMNOC_SF_CBCR_FORCE_MEM_PERIPH_ON_SHFT                                                        0xd
#define HWIO_GCC_MMNOC_SF_CBCR_FORCE_MEM_PERIPH_OFF_BMSK                                                    0x1000
#define HWIO_GCC_MMNOC_SF_CBCR_FORCE_MEM_PERIPH_OFF_SHFT                                                       0xc
#define HWIO_GCC_MMNOC_SF_CBCR_SW_ONLY_EN_BMSK                                                                 0x8
#define HWIO_GCC_MMNOC_SF_CBCR_SW_ONLY_EN_SHFT                                                                 0x3
#define HWIO_GCC_MMNOC_SF_CBCR_CLK_ARES_BMSK                                                                   0x4
#define HWIO_GCC_MMNOC_SF_CBCR_CLK_ARES_SHFT                                                                   0x2
#define HWIO_GCC_MMNOC_SF_CBCR_HW_CTL_BMSK                                                                     0x2
#define HWIO_GCC_MMNOC_SF_CBCR_HW_CTL_SHFT                                                                     0x1
#define HWIO_GCC_MMNOC_SF_CBCR_CLK_ENABLE_BMSK                                                                 0x1
#define HWIO_GCC_MMNOC_SF_CBCR_CLK_ENABLE_SHFT                                                                 0x0

#define HWIO_GCC_MMNOC_SF_SREGR_ADDR                                                                    (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c078)
#define HWIO_GCC_MMNOC_SF_SREGR_RMSK                                                                     0xf1ffffe
#define HWIO_GCC_MMNOC_SF_SREGR_IN          \
        in_dword(HWIO_GCC_MMNOC_SF_SREGR_ADDR)
#define HWIO_GCC_MMNOC_SF_SREGR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_SF_SREGR_ADDR, m)
#define HWIO_GCC_MMNOC_SF_SREGR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_SF_SREGR_ADDR,v)
#define HWIO_GCC_MMNOC_SF_SREGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_SF_SREGR_ADDR,m,v,HWIO_GCC_MMNOC_SF_SREGR_IN)
#define HWIO_GCC_MMNOC_SF_SREGR_SREG_PSCBC_SPARE_CTRL_OUT_BMSK                                           0xf000000
#define HWIO_GCC_MMNOC_SF_SREGR_SREG_PSCBC_SPARE_CTRL_OUT_SHFT                                                0x18
#define HWIO_GCC_MMNOC_SF_SREGR_PWR_FSM_CLK_SEL_BMSK                                                      0x100000
#define HWIO_GCC_MMNOC_SF_SREGR_PWR_FSM_CLK_SEL_SHFT                                                          0x14
#define HWIO_GCC_MMNOC_SF_SREGR_SREG_PSCBC_SPARE_CTRL_IN_BMSK                                              0xf0000
#define HWIO_GCC_MMNOC_SF_SREGR_SREG_PSCBC_SPARE_CTRL_IN_SHFT                                                 0x10
#define HWIO_GCC_MMNOC_SF_SREGR_IGNORE_GDSC_PWR_DWN_CSR_BMSK                                                0x8000
#define HWIO_GCC_MMNOC_SF_SREGR_IGNORE_GDSC_PWR_DWN_CSR_SHFT                                                   0xf
#define HWIO_GCC_MMNOC_SF_SREGR_PSCBC_SLP_STG_MODE_CSR_BMSK                                                 0x4000
#define HWIO_GCC_MMNOC_SF_SREGR_PSCBC_SLP_STG_MODE_CSR_SHFT                                                    0xe
#define HWIO_GCC_MMNOC_SF_SREGR_MEM_CPH_RST_SW_OVERRIDE_BMSK                                                0x2000
#define HWIO_GCC_MMNOC_SF_SREGR_MEM_CPH_RST_SW_OVERRIDE_SHFT                                                   0xd
#define HWIO_GCC_MMNOC_SF_SREGR_SW_SM_PSCBC_SEQ_IN_OVERRIDE_BMSK                                            0x1000
#define HWIO_GCC_MMNOC_SF_SREGR_SW_SM_PSCBC_SEQ_IN_OVERRIDE_SHFT                                               0xc
#define HWIO_GCC_MMNOC_SF_SREGR_MEM_CORE_ON_ACK_BMSK                                                         0x800
#define HWIO_GCC_MMNOC_SF_SREGR_MEM_CORE_ON_ACK_SHFT                                                           0xb
#define HWIO_GCC_MMNOC_SF_SREGR_MEM_PERIPH_ON_ACK_BMSK                                                       0x400
#define HWIO_GCC_MMNOC_SF_SREGR_MEM_PERIPH_ON_ACK_SHFT                                                         0xa
#define HWIO_GCC_MMNOC_SF_SREGR_SW_DIV_RATIO_SLP_STG_CLK_BMSK                                                0x300
#define HWIO_GCC_MMNOC_SF_SREGR_SW_DIV_RATIO_SLP_STG_CLK_SHFT                                                  0x8
#define HWIO_GCC_MMNOC_SF_SREGR_MEM_CPH_ENABLE_BMSK                                                           0x80
#define HWIO_GCC_MMNOC_SF_SREGR_MEM_CPH_ENABLE_SHFT                                                            0x7
#define HWIO_GCC_MMNOC_SF_SREGR_FORCE_CLK_ON_BMSK                                                             0x40
#define HWIO_GCC_MMNOC_SF_SREGR_FORCE_CLK_ON_SHFT                                                              0x6
#define HWIO_GCC_MMNOC_SF_SREGR_SW_RST_SEL_SLP_STG_BMSK                                                       0x20
#define HWIO_GCC_MMNOC_SF_SREGR_SW_RST_SEL_SLP_STG_SHFT                                                        0x5
#define HWIO_GCC_MMNOC_SF_SREGR_SW_RST_SLP_STG_BMSK                                                           0x10
#define HWIO_GCC_MMNOC_SF_SREGR_SW_RST_SLP_STG_SHFT                                                            0x4
#define HWIO_GCC_MMNOC_SF_SREGR_SW_CTRL_PWR_DOWN_BMSK                                                          0x8
#define HWIO_GCC_MMNOC_SF_SREGR_SW_CTRL_PWR_DOWN_SHFT                                                          0x3
#define HWIO_GCC_MMNOC_SF_SREGR_SW_CLK_EN_SEL_SLP_STG_BMSK                                                     0x4
#define HWIO_GCC_MMNOC_SF_SREGR_SW_CLK_EN_SEL_SLP_STG_SHFT                                                     0x2
#define HWIO_GCC_MMNOC_SF_SREGR_SW_CLK_EN_SLP_STG_BMSK                                                         0x2
#define HWIO_GCC_MMNOC_SF_SREGR_SW_CLK_EN_SLP_STG_SHFT                                                         0x1

#define HWIO_GCC_MMNOC_SF_CFG_SREGR_ADDR                                                                (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c07c)
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_RMSK                                                                0xffffffff
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_IN          \
        in_dword(HWIO_GCC_MMNOC_SF_CFG_SREGR_ADDR)
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_SF_CFG_SREGR_ADDR, m)
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_SF_CFG_SREGR_ADDR,v)
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_SF_CFG_SREGR_ADDR,m,v,HWIO_GCC_MMNOC_SF_CFG_SREGR_IN)
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_MEM_CORE_OFF_TIMER_BMSK                                             0xfc000000
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_MEM_CORE_OFF_TIMER_SHFT                                                   0x1a
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_MEM_PERIPH_ON_ACK_STATUS_BMSK                                        0x2000000
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_MEM_PERIPH_ON_ACK_STATUS_SHFT                                             0x19
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_MEM_CORE_ON_ACK_STATUS_BMSK                                          0x1000000
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_MEM_CORE_ON_ACK_STATUS_SHFT                                               0x18
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_MEM_PERIPH_ON_STATUS_BMSK                                             0x800000
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_MEM_PERIPH_ON_STATUS_SHFT                                                 0x17
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_MEM_CORE_ON_STATUS_BMSK                                               0x400000
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_MEM_CORE_ON_STATUS_SHFT                                                   0x16
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_MEM_CPH_TIMER_BMSK                                                    0x3f0000
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_MEM_CPH_TIMER_SHFT                                                        0x10
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_SLEEP_TIMER_BMSK                                                        0xff00
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_SLEEP_TIMER_SHFT                                                           0x8
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_WAKEUP_TIMER_BMSK                                                         0xff
#define HWIO_GCC_MMNOC_SF_CFG_SREGR_WAKEUP_TIMER_SHFT                                                          0x0

#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_ADDR                                                              (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c080)
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_RMSK                                                              0x81d0000f
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_IN          \
        in_dword(HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_ADDR)
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_ADDR, m)
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_ADDR,v)
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_ADDR,m,v,HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_IN)
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_IGNORE_ALL_ARES_BMSK                                               0x1000000
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_IGNORE_ALL_ARES_SHFT                                                    0x18
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                             0x800000
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                                 0x17
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_CLK_DIS_BMSK                                                        0x400000
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_CLK_DIS_SHFT                                                            0x16
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_IGNORE_RPMH_CLK_DIS_BMSK                                            0x100000
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_IGNORE_RPMH_CLK_DIS_SHFT                                                0x14
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_SW_ONLY_EN_BMSK                                                          0x8
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_SW_ONLY_EN_SHFT                                                          0x3
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_CLK_ARES_BMSK                                                            0x4
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_CLK_ARES_SHFT                                                            0x2
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_HW_CTL_BMSK                                                              0x2
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_HW_CTL_SHFT                                                              0x1
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_GCC_MMNOC_SF_PWRCTL_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_ADDR                                                       (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c084)
#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_RMSK                                                       0x81c00005
#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_IN          \
        in_dword(HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_ADDR)
#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_ADDR, m)
#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_ADDR,v)
#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_ADDR,m,v,HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_IN)
#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_CLK_OFF_BMSK                                               0x80000000
#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_CLK_OFF_SHFT                                                     0x1f
#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_IGNORE_ALL_ARES_BMSK                                        0x1000000
#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_IGNORE_ALL_ARES_SHFT                                             0x18
#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                      0x800000
#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                          0x17
#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_CLK_DIS_BMSK                                                 0x400000
#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_CLK_DIS_SHFT                                                     0x16
#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_CLK_ARES_BMSK                                                     0x4
#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_CLK_ARES_SHFT                                                     0x2
#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_CLK_ENABLE_BMSK                                                   0x1
#define HWIO_GCC_MMNOC_SF_QOSGEN_EXTREF_CBCR_CLK_ENABLE_SHFT                                                   0x0

#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_ADDR                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c088)
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_RMSK                                                         0x81d00005
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_IN          \
        in_dword(HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_ADDR)
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_ADDR, m)
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_ADDR,v)
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_ADDR,m,v,HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_IN)
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_CLK_OFF_BMSK                                                 0x80000000
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_CLK_OFF_SHFT                                                       0x1f
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_IGNORE_ALL_ARES_BMSK                                          0x1000000
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_IGNORE_ALL_ARES_SHFT                                               0x18
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                        0x800000
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                            0x17
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_CLK_DIS_BMSK                                                   0x400000
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_CLK_DIS_SHFT                                                       0x16
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_IGNORE_RPMH_CLK_DIS_BMSK                                       0x100000
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_IGNORE_RPMH_CLK_DIS_SHFT                                           0x14
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_CLK_ARES_BMSK                                                       0x4
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_CLK_ARES_SHFT                                                       0x2
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_CLK_ENABLE_BMSK                                                     0x1
#define HWIO_GCC_MMNOC_SF_NON_GDSC_AT_CBCR_CLK_ENABLE_SHFT                                                     0x0

#define HWIO_GCC_MMNOC_HF_APB_CBCR_ADDR                                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x0000f04c)
#define HWIO_GCC_MMNOC_HF_APB_CBCR_RMSK                                                                 0x81c00005
#define HWIO_GCC_MMNOC_HF_APB_CBCR_IN          \
        in_dword(HWIO_GCC_MMNOC_HF_APB_CBCR_ADDR)
#define HWIO_GCC_MMNOC_HF_APB_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_HF_APB_CBCR_ADDR, m)
#define HWIO_GCC_MMNOC_HF_APB_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_HF_APB_CBCR_ADDR,v)
#define HWIO_GCC_MMNOC_HF_APB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_HF_APB_CBCR_ADDR,m,v,HWIO_GCC_MMNOC_HF_APB_CBCR_IN)
#define HWIO_GCC_MMNOC_HF_APB_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_GCC_MMNOC_HF_APB_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_GCC_MMNOC_HF_APB_CBCR_IGNORE_ALL_ARES_BMSK                                                  0x1000000
#define HWIO_GCC_MMNOC_HF_APB_CBCR_IGNORE_ALL_ARES_SHFT                                                       0x18
#define HWIO_GCC_MMNOC_HF_APB_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                                0x800000
#define HWIO_GCC_MMNOC_HF_APB_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                                    0x17
#define HWIO_GCC_MMNOC_HF_APB_CBCR_CLK_DIS_BMSK                                                           0x400000
#define HWIO_GCC_MMNOC_HF_APB_CBCR_CLK_DIS_SHFT                                                               0x16
#define HWIO_GCC_MMNOC_HF_APB_CBCR_CLK_ARES_BMSK                                                               0x4
#define HWIO_GCC_MMNOC_HF_APB_CBCR_CLK_ARES_SHFT                                                               0x2
#define HWIO_GCC_MMNOC_HF_APB_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_GCC_MMNOC_HF_APB_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_GCC_MMNOC_SF_APB_CBCR_ADDR                                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x0000f050)
#define HWIO_GCC_MMNOC_SF_APB_CBCR_RMSK                                                                 0x81c00005
#define HWIO_GCC_MMNOC_SF_APB_CBCR_IN          \
        in_dword(HWIO_GCC_MMNOC_SF_APB_CBCR_ADDR)
#define HWIO_GCC_MMNOC_SF_APB_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_SF_APB_CBCR_ADDR, m)
#define HWIO_GCC_MMNOC_SF_APB_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_SF_APB_CBCR_ADDR,v)
#define HWIO_GCC_MMNOC_SF_APB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_SF_APB_CBCR_ADDR,m,v,HWIO_GCC_MMNOC_SF_APB_CBCR_IN)
#define HWIO_GCC_MMNOC_SF_APB_CBCR_CLK_OFF_BMSK                                                         0x80000000
#define HWIO_GCC_MMNOC_SF_APB_CBCR_CLK_OFF_SHFT                                                               0x1f
#define HWIO_GCC_MMNOC_SF_APB_CBCR_IGNORE_ALL_ARES_BMSK                                                  0x1000000
#define HWIO_GCC_MMNOC_SF_APB_CBCR_IGNORE_ALL_ARES_SHFT                                                       0x18
#define HWIO_GCC_MMNOC_SF_APB_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                                0x800000
#define HWIO_GCC_MMNOC_SF_APB_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                                    0x17
#define HWIO_GCC_MMNOC_SF_APB_CBCR_CLK_DIS_BMSK                                                           0x400000
#define HWIO_GCC_MMNOC_SF_APB_CBCR_CLK_DIS_SHFT                                                               0x16
#define HWIO_GCC_MMNOC_SF_APB_CBCR_CLK_ARES_BMSK                                                               0x4
#define HWIO_GCC_MMNOC_SF_APB_CBCR_CLK_ARES_SHFT                                                               0x2
#define HWIO_GCC_MMNOC_SF_APB_CBCR_CLK_ENABLE_BMSK                                                             0x1
#define HWIO_GCC_MMNOC_SF_APB_CBCR_CLK_ENABLE_SHFT                                                             0x0

#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_ADDR                                                               (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c350)
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_RMSK                                                               0x81f0000f
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_IN          \
        in_dword(HWIO_GCC_DDRSS_MMNOC_SF_CBCR_ADDR)
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_DDRSS_MMNOC_SF_CBCR_ADDR, m)
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_DDRSS_MMNOC_SF_CBCR_ADDR,v)
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_DDRSS_MMNOC_SF_CBCR_ADDR,m,v,HWIO_GCC_DDRSS_MMNOC_SF_CBCR_IN)
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_CLK_OFF_BMSK                                                       0x80000000
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_CLK_OFF_SHFT                                                             0x1f
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_IGNORE_ALL_ARES_BMSK                                                0x1000000
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_IGNORE_ALL_ARES_SHFT                                                     0x18
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                              0x800000
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                                  0x17
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_CLK_DIS_BMSK                                                         0x400000
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_CLK_DIS_SHFT                                                             0x16
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_IGNORE_PMU_CLK_DIS_BMSK                                              0x200000
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_IGNORE_PMU_CLK_DIS_SHFT                                                  0x15
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_IGNORE_RPMH_CLK_DIS_BMSK                                             0x100000
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_IGNORE_RPMH_CLK_DIS_SHFT                                                 0x14
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_SW_ONLY_EN_BMSK                                                           0x8
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_SW_ONLY_EN_SHFT                                                           0x3
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_CLK_ARES_BMSK                                                             0x4
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_CLK_ARES_SHFT                                                             0x2
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_HW_CTL_BMSK                                                               0x2
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_HW_CTL_SHFT                                                               0x1
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_CLK_ENABLE_BMSK                                                           0x1
#define HWIO_GCC_DDRSS_MMNOC_SF_CBCR_CLK_ENABLE_SHFT                                                           0x0

#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_ADDR                                                            (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c354)
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_RMSK                                                            0x81f0000f
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_IN          \
        in_dword(HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_ADDR)
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_ADDR, m)
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_ADDR,v)
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_ADDR,m,v,HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_IN)
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_CLK_OFF_BMSK                                                    0x80000000
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_CLK_OFF_SHFT                                                          0x1f
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_IGNORE_ALL_ARES_BMSK                                             0x1000000
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_IGNORE_ALL_ARES_SHFT                                                  0x18
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                           0x800000
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                               0x17
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_CLK_DIS_BMSK                                                      0x400000
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_CLK_DIS_SHFT                                                          0x16
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_IGNORE_PMU_CLK_DIS_BMSK                                           0x200000
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_IGNORE_PMU_CLK_DIS_SHFT                                               0x15
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_IGNORE_RPMH_CLK_DIS_BMSK                                          0x100000
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_IGNORE_RPMH_CLK_DIS_SHFT                                              0x14
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_SW_ONLY_EN_BMSK                                                        0x8
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_SW_ONLY_EN_SHFT                                                        0x3
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_CLK_ARES_BMSK                                                          0x4
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_CLK_ARES_SHFT                                                          0x2
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_HW_CTL_BMSK                                                            0x2
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_HW_CTL_SHFT                                                            0x1
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_CLK_ENABLE_BMSK                                                        0x1
#define HWIO_GCC_DDRSS_MMNOC_HF_QX_CBCR_CLK_ENABLE_SHFT                                                        0x0

#define HWIO_GCC_TURING_MMNOC_SF_CBCR_ADDR                                                              (GCC_CLK_CTL_REG_REG_BASE      + 0x00035000)
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_RMSK                                                              0x81f0000f
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_IN          \
        in_dword(HWIO_GCC_TURING_MMNOC_SF_CBCR_ADDR)
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_INM(m)      \
        in_dword_masked(HWIO_GCC_TURING_MMNOC_SF_CBCR_ADDR, m)
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_OUT(v)      \
        out_dword(HWIO_GCC_TURING_MMNOC_SF_CBCR_ADDR,v)
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_TURING_MMNOC_SF_CBCR_ADDR,m,v,HWIO_GCC_TURING_MMNOC_SF_CBCR_IN)
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_CLK_OFF_BMSK                                                      0x80000000
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_CLK_OFF_SHFT                                                            0x1f
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_IGNORE_ALL_ARES_BMSK                                               0x1000000
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_IGNORE_ALL_ARES_SHFT                                                    0x18
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_IGNORE_ALL_CLK_DIS_BMSK                                             0x800000
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_IGNORE_ALL_CLK_DIS_SHFT                                                 0x17
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_CLK_DIS_BMSK                                                        0x400000
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_CLK_DIS_SHFT                                                            0x16
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_IGNORE_PMU_CLK_DIS_BMSK                                             0x200000
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_IGNORE_PMU_CLK_DIS_SHFT                                                 0x15
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_IGNORE_RPMH_CLK_DIS_BMSK                                            0x100000
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_IGNORE_RPMH_CLK_DIS_SHFT                                                0x14
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_SW_ONLY_EN_BMSK                                                          0x8
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_SW_ONLY_EN_SHFT                                                          0x3
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_CLK_ARES_BMSK                                                            0x4
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_CLK_ARES_SHFT                                                            0x2
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_HW_CTL_BMSK                                                              0x2
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_HW_CTL_SHFT                                                              0x1
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_CLK_ENABLE_BMSK                                                          0x1
#define HWIO_GCC_TURING_MMNOC_SF_CBCR_CLK_ENABLE_SHFT                                                          0x0

#define HWIO_GCC_APCS_TZ_MMNOC_SGDSCR_ADDR                                                              (GCC_CLK_CTL_REG_REG_BASE      + 0x00043034)
#define HWIO_GCC_APCS_TZ_MMNOC_SGDSCR_RMSK                                                                     0x7
#define HWIO_GCC_APCS_TZ_MMNOC_SGDSCR_IN          \
        in_dword(HWIO_GCC_APCS_TZ_MMNOC_SGDSCR_ADDR)
#define HWIO_GCC_APCS_TZ_MMNOC_SGDSCR_INM(m)      \
        in_dword_masked(HWIO_GCC_APCS_TZ_MMNOC_SGDSCR_ADDR, m)
#define HWIO_GCC_APCS_TZ_MMNOC_SGDSCR_OUT(v)      \
        out_dword(HWIO_GCC_APCS_TZ_MMNOC_SGDSCR_ADDR,v)
#define HWIO_GCC_APCS_TZ_MMNOC_SGDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_APCS_TZ_MMNOC_SGDSCR_ADDR,m,v,HWIO_GCC_APCS_TZ_MMNOC_SGDSCR_IN)
#define HWIO_GCC_APCS_TZ_MMNOC_SGDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_BMSK                                          0x4
#define HWIO_GCC_APCS_TZ_MMNOC_SGDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_SHFT                                          0x2
#define HWIO_GCC_APCS_TZ_MMNOC_SGDSCR_RETAIN_FF_ENABLE_BMSK                                                    0x2
#define HWIO_GCC_APCS_TZ_MMNOC_SGDSCR_RETAIN_FF_ENABLE_SHFT                                                    0x1
#define HWIO_GCC_APCS_TZ_MMNOC_SGDSCR_SW_OVERRIDE_BMSK                                                         0x1
#define HWIO_GCC_APCS_TZ_MMNOC_SGDSCR_SW_OVERRIDE_SHFT                                                         0x0

#define HWIO_GCC_MSS_Q6_MMNOC_SGDSCR_ADDR                                                               (GCC_CLK_CTL_REG_REG_BASE      + 0x00025034)
#define HWIO_GCC_MSS_Q6_MMNOC_SGDSCR_RMSK                                                                      0x7
#define HWIO_GCC_MSS_Q6_MMNOC_SGDSCR_IN          \
        in_dword(HWIO_GCC_MSS_Q6_MMNOC_SGDSCR_ADDR)
#define HWIO_GCC_MSS_Q6_MMNOC_SGDSCR_INM(m)      \
        in_dword_masked(HWIO_GCC_MSS_Q6_MMNOC_SGDSCR_ADDR, m)
#define HWIO_GCC_MSS_Q6_MMNOC_SGDSCR_OUT(v)      \
        out_dword(HWIO_GCC_MSS_Q6_MMNOC_SGDSCR_ADDR,v)
#define HWIO_GCC_MSS_Q6_MMNOC_SGDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MSS_Q6_MMNOC_SGDSCR_ADDR,m,v,HWIO_GCC_MSS_Q6_MMNOC_SGDSCR_IN)
#define HWIO_GCC_MSS_Q6_MMNOC_SGDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_BMSK                                           0x4
#define HWIO_GCC_MSS_Q6_MMNOC_SGDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_SHFT                                           0x2
#define HWIO_GCC_MSS_Q6_MMNOC_SGDSCR_RETAIN_FF_ENABLE_BMSK                                                     0x2
#define HWIO_GCC_MSS_Q6_MMNOC_SGDSCR_RETAIN_FF_ENABLE_SHFT                                                     0x1
#define HWIO_GCC_MSS_Q6_MMNOC_SGDSCR_SW_OVERRIDE_BMSK                                                          0x1
#define HWIO_GCC_MSS_Q6_MMNOC_SGDSCR_SW_OVERRIDE_SHFT                                                          0x0

#define HWIO_GCC_TME_MMNOC_SGDSCR_ADDR                                                                  (GCC_CLK_CTL_REG_REG_BASE      + 0x00059034)
#define HWIO_GCC_TME_MMNOC_SGDSCR_RMSK                                                                         0x7
#define HWIO_GCC_TME_MMNOC_SGDSCR_IN          \
        in_dword(HWIO_GCC_TME_MMNOC_SGDSCR_ADDR)
#define HWIO_GCC_TME_MMNOC_SGDSCR_INM(m)      \
        in_dword_masked(HWIO_GCC_TME_MMNOC_SGDSCR_ADDR, m)
#define HWIO_GCC_TME_MMNOC_SGDSCR_OUT(v)      \
        out_dword(HWIO_GCC_TME_MMNOC_SGDSCR_ADDR,v)
#define HWIO_GCC_TME_MMNOC_SGDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_TME_MMNOC_SGDSCR_ADDR,m,v,HWIO_GCC_TME_MMNOC_SGDSCR_IN)
#define HWIO_GCC_TME_MMNOC_SGDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_BMSK                                              0x4
#define HWIO_GCC_TME_MMNOC_SGDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_SHFT                                              0x2
#define HWIO_GCC_TME_MMNOC_SGDSCR_RETAIN_FF_ENABLE_BMSK                                                        0x2
#define HWIO_GCC_TME_MMNOC_SGDSCR_RETAIN_FF_ENABLE_SHFT                                                        0x1
#define HWIO_GCC_TME_MMNOC_SGDSCR_SW_OVERRIDE_BMSK                                                             0x1
#define HWIO_GCC_TME_MMNOC_SGDSCR_SW_OVERRIDE_SHFT                                                             0x0

#define HWIO_GCC_WPSS_Q6_MMNOC_SGDSCR_ADDR                                                              (GCC_CLK_CTL_REG_REG_BASE      + 0x000a1034)
#define HWIO_GCC_WPSS_Q6_MMNOC_SGDSCR_RMSK                                                                     0x7
#define HWIO_GCC_WPSS_Q6_MMNOC_SGDSCR_IN          \
        in_dword(HWIO_GCC_WPSS_Q6_MMNOC_SGDSCR_ADDR)
#define HWIO_GCC_WPSS_Q6_MMNOC_SGDSCR_INM(m)      \
        in_dword_masked(HWIO_GCC_WPSS_Q6_MMNOC_SGDSCR_ADDR, m)
#define HWIO_GCC_WPSS_Q6_MMNOC_SGDSCR_OUT(v)      \
        out_dword(HWIO_GCC_WPSS_Q6_MMNOC_SGDSCR_ADDR,v)
#define HWIO_GCC_WPSS_Q6_MMNOC_SGDSCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_WPSS_Q6_MMNOC_SGDSCR_ADDR,m,v,HWIO_GCC_WPSS_Q6_MMNOC_SGDSCR_IN)
#define HWIO_GCC_WPSS_Q6_MMNOC_SGDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_BMSK                                          0x4
#define HWIO_GCC_WPSS_Q6_MMNOC_SGDSCR_PRE_PWRUP_RETAIN_FF_ENABLE_SHFT                                          0x2
#define HWIO_GCC_WPSS_Q6_MMNOC_SGDSCR_RETAIN_FF_ENABLE_BMSK                                                    0x2
#define HWIO_GCC_WPSS_Q6_MMNOC_SGDSCR_RETAIN_FF_ENABLE_SHFT                                                    0x1
#define HWIO_GCC_WPSS_Q6_MMNOC_SGDSCR_SW_OVERRIDE_BMSK                                                         0x1
#define HWIO_GCC_WPSS_Q6_MMNOC_SGDSCR_SW_OVERRIDE_SHFT                                                         0x0

#define HWIO_GCC_GDS_HW_CTRL_SW_OVRD_ADDR                                                               (GCC_CLK_CTL_REG_REG_BASE      + 0x00068040)
#define HWIO_GCC_GDS_HW_CTRL_SW_OVRD_RMSK                                                                      0x1
#define HWIO_GCC_GDS_HW_CTRL_SW_OVRD_IN          \
        in_dword(HWIO_GCC_GDS_HW_CTRL_SW_OVRD_ADDR)
#define HWIO_GCC_GDS_HW_CTRL_SW_OVRD_INM(m)      \
        in_dword_masked(HWIO_GCC_GDS_HW_CTRL_SW_OVRD_ADDR, m)
#define HWIO_GCC_GDS_HW_CTRL_SW_OVRD_OUT(v)      \
        out_dword(HWIO_GCC_GDS_HW_CTRL_SW_OVRD_ADDR,v)
#define HWIO_GCC_GDS_HW_CTRL_SW_OVRD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_GDS_HW_CTRL_SW_OVRD_ADDR,m,v,HWIO_GCC_GDS_HW_CTRL_SW_OVRD_IN)
#define HWIO_GCC_GDS_HW_CTRL_SW_OVRD_SW_OVERRIDE_BMSK                                                          0x1
#define HWIO_GCC_GDS_HW_CTRL_SW_OVRD_SW_OVERRIDE_SHFT                                                          0x0

#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR                                                      (GCC_CLK_CTL_REG_REG_BASE      + 0x0006b014)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_CLK_RMSK                                                      0x80000001
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_CLK_IN          \
        in_dword(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR, m)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_CLK_OUT(v)      \
        out_dword(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR,v)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR,m,v,HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_CLK_IN)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_OFF_BMSK                                              0x80000000
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_OFF_SHFT                                                    0x1f
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_ENABLE_BMSK                                                  0x1
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_ENABLE_SHFT                                                  0x0

#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR                                                    (GCC_CLK_CTL_REG_REG_BASE      + 0x0006b018)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_CLK_RMSK                                                    0x80000001
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_CLK_IN          \
        in_dword(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR, m)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_CLK_OUT(v)      \
        out_dword(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR,v)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR,m,v,HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_CLK_IN)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_OFF_BMSK                                            0x80000000
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_OFF_SHFT                                                  0x1f
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_ENABLE_BMSK                                                0x1
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_ENABLE_SHFT                                                0x0

#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR                                                    (GCC_CLK_CTL_REG_REG_BASE      + 0x0006b050)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_GDS_RMSK                                                    0x80000001
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_GDS_IN          \
        in_dword(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR, m)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_GDS_OUT(v)      \
        out_dword(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR,v)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR,m,v,HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_GDS_IN)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_GDS_PWR_ON_BMSK                                             0x80000000
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_GDS_PWR_ON_SHFT                                                   0x1f
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_GDS_SW_COLLAPSE_BMSK                                               0x1
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF01_GDS_SW_COLLAPSE_SHFT                                               0x0

#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR                                                      (GCC_CLK_CTL_REG_REG_BASE      + 0x0006b054)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_GDS_RMSK                                                      0x80000001
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_GDS_IN          \
        in_dword(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR, m)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_GDS_OUT(v)      \
        out_dword(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR,v)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR,m,v,HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_GDS_IN)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_GDS_PWR_ON_BMSK                                               0x80000000
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_GDS_PWR_ON_SHFT                                                     0x1f
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_GDS_SW_COLLAPSE_BMSK                                                 0x1
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_SF_GDS_SW_COLLAPSE_SHFT                                                 0x0

#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR                                                    (GCC_CLK_CTL_REG_REG_BASE      + 0x0006b070)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_CLK_RMSK                                                    0x80000001
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_CLK_IN          \
        in_dword(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR, m)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_CLK_OUT(v)      \
        out_dword(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR,v)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR,m,v,HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_CLK_IN)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_OFF_BMSK                                            0x80000000
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_OFF_SHFT                                                  0x1f
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_ENABLE_BMSK                                                0x1
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_ENABLE_SHFT                                                0x0

#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR                                                    (GCC_CLK_CTL_REG_REG_BASE      + 0x0006b078)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_GDS_RMSK                                                    0x80000001
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_GDS_IN          \
        in_dword(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR, m)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_GDS_OUT(v)      \
        out_dword(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR,v)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR,m,v,HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_GDS_IN)
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_GDS_PWR_ON_BMSK                                             0x80000000
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_GDS_PWR_ON_SHFT                                                   0x1f
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_GDS_SW_COLLAPSE_BMSK                                               0x1
#define HWIO_GCC_TZ_VOTE_MMNOC_MMU_QTB_HF23_GDS_SW_COLLAPSE_SHFT                                               0x0

#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR                                                     (GCC_CLK_CTL_REG_REG_BASE      + 0x0006c014)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_CLK_RMSK                                                     0x80000001
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_CLK_IN          \
        in_dword(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR, m)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_CLK_OUT(v)      \
        out_dword(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR,v)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR,m,v,HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_CLK_IN)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_OFF_BMSK                                             0x80000000
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_OFF_SHFT                                                   0x1f
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_ENABLE_BMSK                                                 0x1
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_ENABLE_SHFT                                                 0x0

#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x0006c018)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_CLK_RMSK                                                   0x80000001
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_CLK_IN          \
        in_dword(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR, m)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_CLK_OUT(v)      \
        out_dword(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR,v)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR,m,v,HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_CLK_IN)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_OFF_BMSK                                           0x80000000
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_OFF_SHFT                                                 0x1f
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_ENABLE_BMSK                                               0x1
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_ENABLE_SHFT                                               0x0

#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x0006c050)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_GDS_RMSK                                                   0x80000001
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_GDS_IN          \
        in_dword(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR, m)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_GDS_OUT(v)      \
        out_dword(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR,v)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR,m,v,HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_GDS_IN)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_GDS_PWR_ON_BMSK                                            0x80000000
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_GDS_PWR_ON_SHFT                                                  0x1f
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_GDS_SW_COLLAPSE_BMSK                                              0x1
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF01_GDS_SW_COLLAPSE_SHFT                                              0x0

#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR                                                     (GCC_CLK_CTL_REG_REG_BASE      + 0x0006c054)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_GDS_RMSK                                                     0x80000001
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_GDS_IN          \
        in_dword(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR, m)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_GDS_OUT(v)      \
        out_dword(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR,v)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR,m,v,HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_GDS_IN)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_GDS_PWR_ON_BMSK                                              0x80000000
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_GDS_PWR_ON_SHFT                                                    0x1f
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_GDS_SW_COLLAPSE_BMSK                                                0x1
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_SF_GDS_SW_COLLAPSE_SHFT                                                0x0

#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x0006c070)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_CLK_RMSK                                                   0x80000001
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_CLK_IN          \
        in_dword(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR, m)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_CLK_OUT(v)      \
        out_dword(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR,v)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR,m,v,HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_CLK_IN)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_OFF_BMSK                                           0x80000000
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_OFF_SHFT                                                 0x1f
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_ENABLE_BMSK                                               0x1
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_ENABLE_SHFT                                               0x0

#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x0006c078)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_GDS_RMSK                                                   0x80000001
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_GDS_IN          \
        in_dword(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR, m)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_GDS_OUT(v)      \
        out_dword(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR,v)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR,m,v,HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_GDS_IN)
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_GDS_PWR_ON_BMSK                                            0x80000000
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_GDS_PWR_ON_SHFT                                                  0x1f
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_GDS_SW_COLLAPSE_BMSK                                              0x1
#define HWIO_GCC_HYP_VOTE_MMNOC_MMU_QTB_HF23_GDS_SW_COLLAPSE_SHFT                                              0x0

#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x0006d014)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_CLK_RMSK                                                   0x80000001
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_CLK_IN          \
        in_dword(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR, m)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_CLK_OUT(v)      \
        out_dword(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR,v)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR,m,v,HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_CLK_IN)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_OFF_BMSK                                           0x80000000
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_OFF_SHFT                                                 0x1f
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_ENABLE_BMSK                                               0x1
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_ENABLE_SHFT                                               0x0

#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x0006d018)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_CLK_RMSK                                                 0x80000001
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_CLK_IN          \
        in_dword(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR, m)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_CLK_OUT(v)      \
        out_dword(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR,v)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR,m,v,HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_CLK_IN)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_OFF_BMSK                                         0x80000000
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_OFF_SHFT                                               0x1f
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_ENABLE_BMSK                                             0x1
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_ENABLE_SHFT                                             0x0

#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x0006d050)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_GDS_RMSK                                                 0x80000001
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_GDS_IN          \
        in_dword(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR, m)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_GDS_OUT(v)      \
        out_dword(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR,v)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR,m,v,HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_GDS_IN)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_GDS_PWR_ON_BMSK                                          0x80000000
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_GDS_PWR_ON_SHFT                                                0x1f
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_GDS_SW_COLLAPSE_BMSK                                            0x1
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF01_GDS_SW_COLLAPSE_SHFT                                            0x0

#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x0006d054)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_GDS_RMSK                                                   0x80000001
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_GDS_IN          \
        in_dword(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR, m)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_GDS_OUT(v)      \
        out_dword(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR,v)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR,m,v,HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_GDS_IN)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_GDS_PWR_ON_BMSK                                            0x80000000
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_GDS_PWR_ON_SHFT                                                  0x1f
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_GDS_SW_COLLAPSE_BMSK                                              0x1
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_SF_GDS_SW_COLLAPSE_SHFT                                              0x0

#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x0006d070)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_CLK_RMSK                                                 0x80000001
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_CLK_IN          \
        in_dword(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR, m)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_CLK_OUT(v)      \
        out_dword(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR,v)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR,m,v,HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_CLK_IN)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_OFF_BMSK                                         0x80000000
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_OFF_SHFT                                               0x1f
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_ENABLE_BMSK                                             0x1
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_ENABLE_SHFT                                             0x0

#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x0006d078)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_GDS_RMSK                                                 0x80000001
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_GDS_IN          \
        in_dword(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR, m)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_GDS_OUT(v)      \
        out_dword(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR,v)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR,m,v,HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_GDS_IN)
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_GDS_PWR_ON_BMSK                                          0x80000000
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_GDS_PWR_ON_SHFT                                                0x1f
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_GDS_SW_COLLAPSE_BMSK                                            0x1
#define HWIO_GCC_HLOS1_VOTE_MMNOC_MMU_QTB_HF23_GDS_SW_COLLAPSE_SHFT                                            0x0

#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x0006e014)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_CLK_RMSK                                                   0x80000001
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_CLK_IN          \
        in_dword(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR, m)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_CLK_OUT(v)      \
        out_dword(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR,v)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR,m,v,HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_CLK_IN)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_OFF_BMSK                                           0x80000000
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_OFF_SHFT                                                 0x1f
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_ENABLE_BMSK                                               0x1
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_ENABLE_SHFT                                               0x0

#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x0006e018)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_CLK_RMSK                                                 0x80000001
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_CLK_IN          \
        in_dword(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR, m)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_CLK_OUT(v)      \
        out_dword(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR,v)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR,m,v,HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_CLK_IN)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_OFF_BMSK                                         0x80000000
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_OFF_SHFT                                               0x1f
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_ENABLE_BMSK                                             0x1
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_ENABLE_SHFT                                             0x0

#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x0006e050)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_GDS_RMSK                                                 0x80000001
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_GDS_IN          \
        in_dword(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR, m)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_GDS_OUT(v)      \
        out_dword(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR,v)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR,m,v,HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_GDS_IN)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_GDS_PWR_ON_BMSK                                          0x80000000
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_GDS_PWR_ON_SHFT                                                0x1f
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_GDS_SW_COLLAPSE_BMSK                                            0x1
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF01_GDS_SW_COLLAPSE_SHFT                                            0x0

#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x0006e054)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_GDS_RMSK                                                   0x80000001
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_GDS_IN          \
        in_dword(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR, m)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_GDS_OUT(v)      \
        out_dword(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR,v)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR,m,v,HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_GDS_IN)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_GDS_PWR_ON_BMSK                                            0x80000000
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_GDS_PWR_ON_SHFT                                                  0x1f
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_GDS_SW_COLLAPSE_BMSK                                              0x1
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_SF_GDS_SW_COLLAPSE_SHFT                                              0x0

#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x0006e070)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_CLK_RMSK                                                 0x80000001
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_CLK_IN          \
        in_dword(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR, m)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_CLK_OUT(v)      \
        out_dword(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR,v)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR,m,v,HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_CLK_IN)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_OFF_BMSK                                         0x80000000
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_OFF_SHFT                                               0x1f
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_ENABLE_BMSK                                             0x1
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_ENABLE_SHFT                                             0x0

#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x0006e078)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_GDS_RMSK                                                 0x80000001
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_GDS_IN          \
        in_dword(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR, m)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_GDS_OUT(v)      \
        out_dword(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR,v)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR,m,v,HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_GDS_IN)
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_GDS_PWR_ON_BMSK                                          0x80000000
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_GDS_PWR_ON_SHFT                                                0x1f
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_GDS_SW_COLLAPSE_BMSK                                            0x1
#define HWIO_GCC_HLOS2_VOTE_MMNOC_MMU_QTB_HF23_GDS_SW_COLLAPSE_SHFT                                            0x0

#define HWIO_GCC_MMNOC_SREG_MISC_ADDR                                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x0000c480)
#define HWIO_GCC_MMNOC_SREG_MISC_RMSK                                                                          0x3
#define HWIO_GCC_MMNOC_SREG_MISC_IN          \
        in_dword(HWIO_GCC_MMNOC_SREG_MISC_ADDR)
#define HWIO_GCC_MMNOC_SREG_MISC_INM(m)      \
        in_dword_masked(HWIO_GCC_MMNOC_SREG_MISC_ADDR, m)
#define HWIO_GCC_MMNOC_SREG_MISC_OUT(v)      \
        out_dword(HWIO_GCC_MMNOC_SREG_MISC_ADDR,v)
#define HWIO_GCC_MMNOC_SREG_MISC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MMNOC_SREG_MISC_ADDR,m,v,HWIO_GCC_MMNOC_SREG_MISC_IN)
#define HWIO_GCC_MMNOC_SREG_MISC_HF_MICRO_FORCE_MEM_CORE_ON_BMSK                                               0x2
#define HWIO_GCC_MMNOC_SREG_MISC_HF_MICRO_FORCE_MEM_CORE_ON_SHFT                                               0x1
#define HWIO_GCC_MMNOC_SREG_MISC_SF_MICRO_FORCE_MEM_CORE_ON_BMSK                                               0x1
#define HWIO_GCC_MMNOC_SREG_MISC_SF_MICRO_FORCE_MEM_CORE_ON_SHFT                                               0x0

#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x00076014)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_CLK_RMSK                                                 0x80000001
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_CLK_IN          \
        in_dword(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR, m)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_CLK_OUT(v)      \
        out_dword(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR,v)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR,m,v,HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_CLK_IN)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_OFF_BMSK                                         0x80000000
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_OFF_SHFT                                               0x1f
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_ENABLE_BMSK                                             0x1
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_ENABLE_SHFT                                             0x0

#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR                                               (GCC_CLK_CTL_REG_REG_BASE      + 0x00076018)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_CLK_RMSK                                               0x80000001
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_CLK_IN          \
        in_dword(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR, m)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_CLK_OUT(v)      \
        out_dword(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR,v)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR,m,v,HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_CLK_IN)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_OFF_BMSK                                       0x80000000
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_OFF_SHFT                                             0x1f
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_ENABLE_BMSK                                           0x1
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_ENABLE_SHFT                                           0x0

#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR                                               (GCC_CLK_CTL_REG_REG_BASE      + 0x00076050)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_GDS_RMSK                                               0x80000001
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_GDS_IN          \
        in_dword(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR, m)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_GDS_OUT(v)      \
        out_dword(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR,v)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR,m,v,HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_GDS_IN)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_GDS_PWR_ON_BMSK                                        0x80000000
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_GDS_PWR_ON_SHFT                                              0x1f
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_GDS_SW_COLLAPSE_BMSK                                          0x1
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF01_GDS_SW_COLLAPSE_SHFT                                          0x0

#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR                                                 (GCC_CLK_CTL_REG_REG_BASE      + 0x00076054)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_GDS_RMSK                                                 0x80000001
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_GDS_IN          \
        in_dword(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR, m)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_GDS_OUT(v)      \
        out_dword(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR,v)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR,m,v,HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_GDS_IN)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_GDS_PWR_ON_BMSK                                          0x80000000
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_GDS_PWR_ON_SHFT                                                0x1f
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_GDS_SW_COLLAPSE_BMSK                                            0x1
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_SF_GDS_SW_COLLAPSE_SHFT                                            0x0

#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR                                               (GCC_CLK_CTL_REG_REG_BASE      + 0x00076070)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_CLK_RMSK                                               0x80000001
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_CLK_IN          \
        in_dword(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR, m)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_CLK_OUT(v)      \
        out_dword(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR,v)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR,m,v,HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_CLK_IN)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_OFF_BMSK                                       0x80000000
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_OFF_SHFT                                             0x1f
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_ENABLE_BMSK                                           0x1
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_ENABLE_SHFT                                           0x0

#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR                                               (GCC_CLK_CTL_REG_REG_BASE      + 0x00076078)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_GDS_RMSK                                               0x80000001
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_GDS_IN          \
        in_dword(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR, m)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_GDS_OUT(v)      \
        out_dword(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR,v)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR,m,v,HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_GDS_IN)
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_GDS_PWR_ON_BMSK                                        0x80000000
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_GDS_PWR_ON_SHFT                                              0x1f
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_GDS_SW_COLLAPSE_BMSK                                          0x1
#define HWIO_GCC_WPSS_Q6_VOTE_MMNOC_MMU_QTB_HF23_GDS_SW_COLLAPSE_SHFT                                          0x0

#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR                                                     (GCC_CLK_CTL_REG_REG_BASE      + 0x00077014)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_CLK_RMSK                                                     0x80000001
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_CLK_IN          \
        in_dword(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR, m)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_CLK_OUT(v)      \
        out_dword(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR,v)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR,m,v,HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_CLK_IN)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_OFF_BMSK                                             0x80000000
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_OFF_SHFT                                                   0x1f
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_ENABLE_BMSK                                                 0x1
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_ENABLE_SHFT                                                 0x0

#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x00077018)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_CLK_RMSK                                                   0x80000001
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_CLK_IN          \
        in_dword(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR, m)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_CLK_OUT(v)      \
        out_dword(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR,v)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR,m,v,HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_CLK_IN)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_OFF_BMSK                                           0x80000000
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_OFF_SHFT                                                 0x1f
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_ENABLE_BMSK                                               0x1
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_ENABLE_SHFT                                               0x0

#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x00077050)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_GDS_RMSK                                                   0x80000001
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_GDS_IN          \
        in_dword(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR, m)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_GDS_OUT(v)      \
        out_dword(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR,v)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR,m,v,HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_GDS_IN)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_GDS_PWR_ON_BMSK                                            0x80000000
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_GDS_PWR_ON_SHFT                                                  0x1f
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_GDS_SW_COLLAPSE_BMSK                                              0x1
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF01_GDS_SW_COLLAPSE_SHFT                                              0x0

#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR                                                     (GCC_CLK_CTL_REG_REG_BASE      + 0x00077054)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_GDS_RMSK                                                     0x80000001
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_GDS_IN          \
        in_dword(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR, m)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_GDS_OUT(v)      \
        out_dword(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR,v)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR,m,v,HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_GDS_IN)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_GDS_PWR_ON_BMSK                                              0x80000000
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_GDS_PWR_ON_SHFT                                                    0x1f
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_GDS_SW_COLLAPSE_BMSK                                                0x1
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_SF_GDS_SW_COLLAPSE_SHFT                                                0x0

#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x00077070)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_CLK_RMSK                                                   0x80000001
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_CLK_IN          \
        in_dword(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR, m)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_CLK_OUT(v)      \
        out_dword(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR,v)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR,m,v,HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_CLK_IN)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_OFF_BMSK                                           0x80000000
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_OFF_SHFT                                                 0x1f
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_ENABLE_BMSK                                               0x1
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_ENABLE_SHFT                                               0x0

#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR                                                   (GCC_CLK_CTL_REG_REG_BASE      + 0x00077078)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_GDS_RMSK                                                   0x80000001
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_GDS_IN          \
        in_dword(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR, m)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_GDS_OUT(v)      \
        out_dword(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR,v)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR,m,v,HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_GDS_IN)
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_GDS_PWR_ON_BMSK                                            0x80000000
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_GDS_PWR_ON_SHFT                                                  0x1f
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_GDS_SW_COLLAPSE_BMSK                                              0x1
#define HWIO_GCC_MSS_VOTE_MMNOC_MMU_QTB_HF23_GDS_SW_COLLAPSE_SHFT                                              0x0

#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR                                              (GCC_CLK_CTL_REG_REG_BASE      + 0x00019014)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_CLK_RMSK                                              0x80000001
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_CLK_IN          \
        in_dword(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR, m)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_CLK_OUT(v)      \
        out_dword(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR,v)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_CLK_ADDR,m,v,HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_CLK_IN)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_OFF_BMSK                                      0x80000000
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_OFF_SHFT                                            0x1f
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_ENABLE_BMSK                                          0x1
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_CLK_CLK_ENABLE_SHFT                                          0x0

#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR                                            (GCC_CLK_CTL_REG_REG_BASE      + 0x00019018)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_CLK_RMSK                                            0x80000001
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_CLK_IN          \
        in_dword(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR, m)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_CLK_OUT(v)      \
        out_dword(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR,v)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_CLK_ADDR,m,v,HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_CLK_IN)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_OFF_BMSK                                    0x80000000
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_OFF_SHFT                                          0x1f
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_ENABLE_BMSK                                        0x1
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_CLK_CLK_ENABLE_SHFT                                        0x0

#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR                                            (GCC_CLK_CTL_REG_REG_BASE      + 0x00019050)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_GDS_RMSK                                            0x80000001
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_GDS_IN          \
        in_dword(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR, m)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_GDS_OUT(v)      \
        out_dword(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR,v)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_GDS_ADDR,m,v,HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_GDS_IN)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_GDS_PWR_ON_BMSK                                     0x80000000
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_GDS_PWR_ON_SHFT                                           0x1f
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_GDS_SW_COLLAPSE_BMSK                                       0x1
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF01_GDS_SW_COLLAPSE_SHFT                                       0x0

#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR                                              (GCC_CLK_CTL_REG_REG_BASE      + 0x00019054)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_GDS_RMSK                                              0x80000001
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_GDS_IN          \
        in_dword(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR, m)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_GDS_OUT(v)      \
        out_dword(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR,v)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_GDS_ADDR,m,v,HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_GDS_IN)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_GDS_PWR_ON_BMSK                                       0x80000000
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_GDS_PWR_ON_SHFT                                             0x1f
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_GDS_SW_COLLAPSE_BMSK                                         0x1
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_SF_GDS_SW_COLLAPSE_SHFT                                         0x0

#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR                                            (GCC_CLK_CTL_REG_REG_BASE      + 0x00019070)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_CLK_RMSK                                            0x80000001
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_CLK_IN          \
        in_dword(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_CLK_INM(m)      \
        in_dword_masked(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR, m)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_CLK_OUT(v)      \
        out_dword(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR,v)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_CLK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_CLK_ADDR,m,v,HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_CLK_IN)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_OFF_BMSK                                    0x80000000
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_OFF_SHFT                                          0x1f
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_ENABLE_BMSK                                        0x1
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_CLK_CLK_ENABLE_SHFT                                        0x0

#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR                                            (GCC_CLK_CTL_REG_REG_BASE      + 0x00019078)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_GDS_RMSK                                            0x80000001
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_GDS_IN          \
        in_dword(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_GDS_INM(m)      \
        in_dword_masked(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR, m)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_GDS_OUT(v)      \
        out_dword(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR,v)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_GDS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_GDS_ADDR,m,v,HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_GDS_IN)
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_GDS_PWR_ON_BMSK                                     0x80000000
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_GDS_PWR_ON_SHFT                                           0x1f
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_GDS_SW_COLLAPSE_BMSK                                       0x1
#define HWIO_GCC_TURING_DSP_VOTE_MMNOC_MMU_QTB_HF23_GDS_SW_COLLAPSE_SHFT                                       0x0

#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_ADDR                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x00085000)
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_RMSK                                                              0x3ff
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_ADDR)
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_IN)
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL9_BMSK                                                    0x200
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL9_SHFT                                                      0x9
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL8_BMSK                                                    0x100
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL8_SHFT                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL7_BMSK                                                     0x80
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL7_SHFT                                                      0x7
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL6_BMSK                                                     0x40
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL6_SHFT                                                      0x6
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL5_BMSK                                                     0x20
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL5_SHFT                                                      0x5
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL4_BMSK                                                     0x10
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL4_SHFT                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL3_BMSK                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL3_SHFT                                                      0x3
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL2_BMSK                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL2_SHFT                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL1_BMSK                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL1_SHFT                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL0_BMSK                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF0_ENA_VOTE_GCC_GPLL0_SHFT                                                      0x0

#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_ADDR                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x00085004)
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_RMSK                                                              0x3ff
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_ADDR)
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_IN)
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL9_BMSK                                                    0x200
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL9_SHFT                                                      0x9
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL8_BMSK                                                    0x100
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL8_SHFT                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL7_BMSK                                                     0x80
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL7_SHFT                                                      0x7
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL6_BMSK                                                     0x40
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL6_SHFT                                                      0x6
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL5_BMSK                                                     0x20
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL5_SHFT                                                      0x5
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL4_BMSK                                                     0x10
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL4_SHFT                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL3_BMSK                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL3_SHFT                                                      0x3
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL2_BMSK                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL2_SHFT                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL1_BMSK                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL1_SHFT                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL0_BMSK                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF1_ENA_VOTE_GCC_GPLL0_SHFT                                                      0x0

#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_ADDR                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x00085008)
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_RMSK                                                              0x3ff
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_ADDR)
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_IN)
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL9_BMSK                                                    0x200
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL9_SHFT                                                      0x9
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL8_BMSK                                                    0x100
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL8_SHFT                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL7_BMSK                                                     0x80
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL7_SHFT                                                      0x7
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL6_BMSK                                                     0x40
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL6_SHFT                                                      0x6
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL5_BMSK                                                     0x20
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL5_SHFT                                                      0x5
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL4_BMSK                                                     0x10
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL4_SHFT                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL3_BMSK                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL3_SHFT                                                      0x3
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL2_BMSK                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL2_SHFT                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL1_BMSK                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL1_SHFT                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL0_BMSK                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF2_ENA_VOTE_GCC_GPLL0_SHFT                                                      0x0

#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_ADDR                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x0008500c)
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_RMSK                                                              0x3ff
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_ADDR)
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_IN)
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL9_BMSK                                                    0x200
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL9_SHFT                                                      0x9
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL8_BMSK                                                    0x100
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL8_SHFT                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL7_BMSK                                                     0x80
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL7_SHFT                                                      0x7
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL6_BMSK                                                     0x40
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL6_SHFT                                                      0x6
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL5_BMSK                                                     0x20
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL5_SHFT                                                      0x5
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL4_BMSK                                                     0x10
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL4_SHFT                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL3_BMSK                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL3_SHFT                                                      0x3
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL2_BMSK                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL2_SHFT                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL1_BMSK                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL1_SHFT                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL0_BMSK                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF3_ENA_VOTE_GCC_GPLL0_SHFT                                                      0x0

#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_ADDR                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x00085010)
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_RMSK                                                              0x3ff
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_ADDR)
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_IN)
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL9_BMSK                                                    0x200
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL9_SHFT                                                      0x9
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL8_BMSK                                                    0x100
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL8_SHFT                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL7_BMSK                                                     0x80
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL7_SHFT                                                      0x7
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL6_BMSK                                                     0x40
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL6_SHFT                                                      0x6
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL5_BMSK                                                     0x20
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL5_SHFT                                                      0x5
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL4_BMSK                                                     0x10
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL4_SHFT                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL3_BMSK                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL3_SHFT                                                      0x3
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL2_BMSK                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL2_SHFT                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL1_BMSK                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL1_SHFT                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL0_BMSK                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF4_ENA_VOTE_GCC_GPLL0_SHFT                                                      0x0

#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_ADDR                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x00085014)
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_RMSK                                                              0x3ff
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_ADDR)
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_IN)
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL9_BMSK                                                    0x200
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL9_SHFT                                                      0x9
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL8_BMSK                                                    0x100
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL8_SHFT                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL7_BMSK                                                     0x80
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL7_SHFT                                                      0x7
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL6_BMSK                                                     0x40
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL6_SHFT                                                      0x6
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL5_BMSK                                                     0x20
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL5_SHFT                                                      0x5
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL4_BMSK                                                     0x10
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL4_SHFT                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL3_BMSK                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL3_SHFT                                                      0x3
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL2_BMSK                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL2_SHFT                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL1_BMSK                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL1_SHFT                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL0_BMSK                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF5_ENA_VOTE_GCC_GPLL0_SHFT                                                      0x0

#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_ADDR                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x00085018)
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_RMSK                                                              0x3ff
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_ADDR)
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_IN)
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL9_BMSK                                                    0x200
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL9_SHFT                                                      0x9
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL8_BMSK                                                    0x100
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL8_SHFT                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL7_BMSK                                                     0x80
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL7_SHFT                                                      0x7
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL6_BMSK                                                     0x40
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL6_SHFT                                                      0x6
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL5_BMSK                                                     0x20
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL5_SHFT                                                      0x5
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL4_BMSK                                                     0x10
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL4_SHFT                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL3_BMSK                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL3_SHFT                                                      0x3
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL2_BMSK                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL2_SHFT                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL1_BMSK                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL1_SHFT                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL0_BMSK                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF6_ENA_VOTE_GCC_GPLL0_SHFT                                                      0x0

#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_ADDR                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x0008501c)
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_RMSK                                                              0x3ff
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_ADDR)
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_IN)
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL9_BMSK                                                    0x200
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL9_SHFT                                                      0x9
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL8_BMSK                                                    0x100
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL8_SHFT                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL7_BMSK                                                     0x80
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL7_SHFT                                                      0x7
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL6_BMSK                                                     0x40
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL6_SHFT                                                      0x6
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL5_BMSK                                                     0x20
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL5_SHFT                                                      0x5
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL4_BMSK                                                     0x10
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL4_SHFT                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL3_BMSK                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL3_SHFT                                                      0x3
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL2_BMSK                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL2_SHFT                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL1_BMSK                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL1_SHFT                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL0_BMSK                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF7_ENA_VOTE_GCC_GPLL0_SHFT                                                      0x0

#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_ADDR                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x00085020)
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_RMSK                                                              0x3ff
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_ADDR)
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_IN)
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL9_BMSK                                                    0x200
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL9_SHFT                                                      0x9
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL8_BMSK                                                    0x100
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL8_SHFT                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL7_BMSK                                                     0x80
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL7_SHFT                                                      0x7
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL6_BMSK                                                     0x40
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL6_SHFT                                                      0x6
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL5_BMSK                                                     0x20
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL5_SHFT                                                      0x5
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL4_BMSK                                                     0x10
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL4_SHFT                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL3_BMSK                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL3_SHFT                                                      0x3
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL2_BMSK                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL2_SHFT                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL1_BMSK                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL1_SHFT                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL0_BMSK                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF8_ENA_VOTE_GCC_GPLL0_SHFT                                                      0x0

#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_ADDR                                                         (GCC_CLK_CTL_REG_REG_BASE      + 0x00085024)
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_RMSK                                                              0x3ff
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_ADDR)
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_IN)
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL9_BMSK                                                    0x200
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL9_SHFT                                                      0x9
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL8_BMSK                                                    0x100
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL8_SHFT                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL7_BMSK                                                     0x80
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL7_SHFT                                                      0x7
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL6_BMSK                                                     0x40
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL6_SHFT                                                      0x6
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL5_BMSK                                                     0x20
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL5_SHFT                                                      0x5
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL4_BMSK                                                     0x10
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL4_SHFT                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL3_BMSK                                                      0x8
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL3_SHFT                                                      0x3
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL2_BMSK                                                      0x4
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL2_SHFT                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL1_BMSK                                                      0x2
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL1_SHFT                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL0_BMSK                                                      0x1
#define HWIO_GCC_RPMH_MMNOC_PERF9_ENA_VOTE_GCC_GPLL0_SHFT                                                      0x0

#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_ADDR                                                        (GCC_CLK_CTL_REG_REG_BASE      + 0x00085028)
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_RMSK                                                             0x3ff
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_ADDR)
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_IN)
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL9_BMSK                                                   0x200
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL9_SHFT                                                     0x9
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL8_BMSK                                                   0x100
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL8_SHFT                                                     0x8
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL7_BMSK                                                    0x80
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL7_SHFT                                                     0x7
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL6_BMSK                                                    0x40
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL6_SHFT                                                     0x6
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL5_BMSK                                                    0x20
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL5_SHFT                                                     0x5
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL4_BMSK                                                    0x10
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL4_SHFT                                                     0x4
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL3_BMSK                                                     0x8
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL3_SHFT                                                     0x3
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL2_BMSK                                                     0x4
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL2_SHFT                                                     0x2
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL1_BMSK                                                     0x2
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL1_SHFT                                                     0x1
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL0_BMSK                                                     0x1
#define HWIO_GCC_RPMH_MMNOC_PERF10_ENA_VOTE_GCC_GPLL0_SHFT                                                     0x0

#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_ADDR                                                        (GCC_CLK_CTL_REG_REG_BASE      + 0x0008502c)
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_RMSK                                                             0x3ff
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_ADDR)
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_IN)
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL9_BMSK                                                   0x200
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL9_SHFT                                                     0x9
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL8_BMSK                                                   0x100
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL8_SHFT                                                     0x8
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL7_BMSK                                                    0x80
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL7_SHFT                                                     0x7
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL6_BMSK                                                    0x40
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL6_SHFT                                                     0x6
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL5_BMSK                                                    0x20
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL5_SHFT                                                     0x5
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL4_BMSK                                                    0x10
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL4_SHFT                                                     0x4
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL3_BMSK                                                     0x8
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL3_SHFT                                                     0x3
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL2_BMSK                                                     0x4
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL2_SHFT                                                     0x2
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL1_BMSK                                                     0x2
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL1_SHFT                                                     0x1
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL0_BMSK                                                     0x1
#define HWIO_GCC_RPMH_MMNOC_PERF11_ENA_VOTE_GCC_GPLL0_SHFT                                                     0x0

#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_ADDR                                                        (GCC_CLK_CTL_REG_REG_BASE      + 0x00085030)
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_RMSK                                                             0x3ff
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_ADDR)
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_IN)
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL9_BMSK                                                   0x200
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL9_SHFT                                                     0x9
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL8_BMSK                                                   0x100
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL8_SHFT                                                     0x8
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL7_BMSK                                                    0x80
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL7_SHFT                                                     0x7
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL6_BMSK                                                    0x40
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL6_SHFT                                                     0x6
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL5_BMSK                                                    0x20
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL5_SHFT                                                     0x5
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL4_BMSK                                                    0x10
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL4_SHFT                                                     0x4
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL3_BMSK                                                     0x8
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL3_SHFT                                                     0x3
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL2_BMSK                                                     0x4
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL2_SHFT                                                     0x2
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL1_BMSK                                                     0x2
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL1_SHFT                                                     0x1
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL0_BMSK                                                     0x1
#define HWIO_GCC_RPMH_MMNOC_PERF12_ENA_VOTE_GCC_GPLL0_SHFT                                                     0x0

#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_ADDR                                                        (GCC_CLK_CTL_REG_REG_BASE      + 0x00085034)
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_RMSK                                                             0x3ff
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_ADDR)
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_IN)
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL9_BMSK                                                   0x200
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL9_SHFT                                                     0x9
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL8_BMSK                                                   0x100
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL8_SHFT                                                     0x8
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL7_BMSK                                                    0x80
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL7_SHFT                                                     0x7
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL6_BMSK                                                    0x40
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL6_SHFT                                                     0x6
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL5_BMSK                                                    0x20
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL5_SHFT                                                     0x5
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL4_BMSK                                                    0x10
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL4_SHFT                                                     0x4
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL3_BMSK                                                     0x8
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL3_SHFT                                                     0x3
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL2_BMSK                                                     0x4
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL2_SHFT                                                     0x2
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL1_BMSK                                                     0x2
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL1_SHFT                                                     0x1
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL0_BMSK                                                     0x1
#define HWIO_GCC_RPMH_MMNOC_PERF13_ENA_VOTE_GCC_GPLL0_SHFT                                                     0x0

#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_ADDR                                                        (GCC_CLK_CTL_REG_REG_BASE      + 0x00085038)
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_RMSK                                                             0x3ff
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_ADDR)
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_IN)
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL9_BMSK                                                   0x200
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL9_SHFT                                                     0x9
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL8_BMSK                                                   0x100
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL8_SHFT                                                     0x8
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL7_BMSK                                                    0x80
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL7_SHFT                                                     0x7
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL6_BMSK                                                    0x40
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL6_SHFT                                                     0x6
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL5_BMSK                                                    0x20
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL5_SHFT                                                     0x5
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL4_BMSK                                                    0x10
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL4_SHFT                                                     0x4
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL3_BMSK                                                     0x8
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL3_SHFT                                                     0x3
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL2_BMSK                                                     0x4
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL2_SHFT                                                     0x2
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL1_BMSK                                                     0x2
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL1_SHFT                                                     0x1
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL0_BMSK                                                     0x1
#define HWIO_GCC_RPMH_MMNOC_PERF14_ENA_VOTE_GCC_GPLL0_SHFT                                                     0x0

#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_ADDR                                                        (GCC_CLK_CTL_REG_REG_BASE      + 0x0008503c)
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_RMSK                                                             0x3ff
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_ADDR)
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_OUT(v)      \
        out_dword(HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_ADDR,v)
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_ADDR,m,v,HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_IN)
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL9_BMSK                                                   0x200
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL9_SHFT                                                     0x9
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL8_BMSK                                                   0x100
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL8_SHFT                                                     0x8
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL7_BMSK                                                    0x80
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL7_SHFT                                                     0x7
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL6_BMSK                                                    0x40
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL6_SHFT                                                     0x6
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL5_BMSK                                                    0x20
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL5_SHFT                                                     0x5
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL4_BMSK                                                    0x10
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL4_SHFT                                                     0x4
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL3_BMSK                                                     0x8
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL3_SHFT                                                     0x3
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL2_BMSK                                                     0x4
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL2_SHFT                                                     0x2
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL1_BMSK                                                     0x2
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL1_SHFT                                                     0x1
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL0_BMSK                                                     0x1
#define HWIO_GCC_RPMH_MMNOC_PERF15_ENA_VOTE_GCC_GPLL0_SHFT                                                     0x0

#define HWIO_GCC_RPMH_MMNOC_INTERFACE_FSM_ADDR                                                          (GCC_CLK_CTL_REG_REG_BASE      + 0x00085100)
#define HWIO_GCC_RPMH_MMNOC_INTERFACE_FSM_RMSK                                                                0x1f
#define HWIO_GCC_RPMH_MMNOC_INTERFACE_FSM_IN          \
        in_dword(HWIO_GCC_RPMH_MMNOC_INTERFACE_FSM_ADDR)
#define HWIO_GCC_RPMH_MMNOC_INTERFACE_FSM_INM(m)      \
        in_dword_masked(HWIO_GCC_RPMH_MMNOC_INTERFACE_FSM_ADDR, m)
#define HWIO_GCC_RPMH_MMNOC_INTERFACE_FSM_FSM_STATE_BMSK                                                      0x1f
#define HWIO_GCC_RPMH_MMNOC_INTERFACE_FSM_FSM_STATE_SHFT                                                       0x0


#endif /* __BCM_EXT_HWIO_H__ */
