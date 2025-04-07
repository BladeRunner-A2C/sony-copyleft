#ifndef __AOP_HWIO_H__
#define __AOP_HWIO_H__
/*
===========================================================================
*/
/**
    @file aop_hwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8650 (Lanai) [z_lanai_prj_v1.0_p2q0r5.4]
 
    This file contains HWIO register definitions for the following modules:
        AOP_DEC
        AOP_F0_QTMR_V1_F0
        AOP_F1_QTMR_V1_F1
        AOP_QTMR_AC


    Generation parameters: 
    { 'filename': 'aop_hwio.h',
      'header': '#include "msmhwiobase.h"\n\n',
      'modules': [ 'AOP_DEC',
                   'AOP_F0_QTMR_V1_F0',
                   'AOP_F1_QTMR_V1_F1',
                   'AOP_QTMR_AC'],
      'output-offsets': True,
      'output-phys': True}
*/
/*
    ===========================================================================

    Copyright (c) 2021 Qualcomm Technologies, Inc.
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

    $Header: //service/AOP/AOP.HO.5.0-00688-LANAI_E-1.65547/aop_proc/core/kernel/rex/inc/target/lanai/aop_hwio.h#1 $
    $DateTime: 2024/04/01 02:51:58 $
    $Author: cirrusp4svc $

    ===========================================================================
*/

#include "msmhwiobase.h"



/*----------------------------------------------------------------------------
 * MODULE: AOP_DEC
 *--------------------------------------------------------------------------*/

#define AOP_DEC_REG_BASE                                                   (AOSS_BASE      + 0x00080000)
#define AOP_DEC_REG_BASE_SIZE                                              0x2000
#define AOP_DEC_REG_BASE_USED                                              0x11c
#define AOP_DEC_REG_BASE_PHYS                                              (AOSS_BASE_PHYS + 0x00080000)
#define AOP_DEC_REG_BASE_OFFS                                              0x00080000

#define HWIO_AOP_HW_VERSION_ADDR                                           (AOP_DEC_REG_BASE      + 0x0)
#define HWIO_AOP_HW_VERSION_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0x0)
#define HWIO_AOP_HW_VERSION_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0x0)
#define HWIO_AOP_HW_VERSION_RMSK                                           0xffffffff
#define HWIO_AOP_HW_VERSION_IN                    \
                in_dword(HWIO_AOP_HW_VERSION_ADDR)
#define HWIO_AOP_HW_VERSION_INM(m)            \
                in_dword_masked(HWIO_AOP_HW_VERSION_ADDR, m)
#define HWIO_AOP_HW_VERSION_MAJOR_BMSK                                     0xf0000000
#define HWIO_AOP_HW_VERSION_MAJOR_SHFT                                             28
#define HWIO_AOP_HW_VERSION_MINOR_BMSK                                      0xfff0000
#define HWIO_AOP_HW_VERSION_MINOR_SHFT                                             16
#define HWIO_AOP_HW_VERSION_STEP_BMSK                                          0xffff
#define HWIO_AOP_HW_VERSION_STEP_SHFT                                               0

#define HWIO_AOP_WFI_CONFIG_ADDR                                           (AOP_DEC_REG_BASE      + 0x4)
#define HWIO_AOP_WFI_CONFIG_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0x4)
#define HWIO_AOP_WFI_CONFIG_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0x4)
#define HWIO_AOP_WFI_CONFIG_RMSK                                                  0x7
#define HWIO_AOP_WFI_CONFIG_IN                    \
                in_dword(HWIO_AOP_WFI_CONFIG_ADDR)
#define HWIO_AOP_WFI_CONFIG_INM(m)            \
                in_dword_masked(HWIO_AOP_WFI_CONFIG_ADDR, m)
#define HWIO_AOP_WFI_CONFIG_OUT(v)            \
                out_dword(HWIO_AOP_WFI_CONFIG_ADDR,v)
#define HWIO_AOP_WFI_CONFIG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_WFI_CONFIG_ADDR,m,v,HWIO_AOP_WFI_CONFIG_IN)
#define HWIO_AOP_WFI_CONFIG_CHIP_SLEEP_UPON_WFI_BMSK                              0x4
#define HWIO_AOP_WFI_CONFIG_CHIP_SLEEP_UPON_WFI_SHFT                                2
#define HWIO_AOP_WFI_CONFIG_BUS_CLK_HALT_BMSK                                     0x2
#define HWIO_AOP_WFI_CONFIG_BUS_CLK_HALT_SHFT                                       1
#define HWIO_AOP_WFI_CONFIG_PROC_CLK_HALT_BMSK                                    0x1
#define HWIO_AOP_WFI_CONFIG_PROC_CLK_HALT_SHFT                                      0

#define HWIO_AOP_TIMERS_CLK_OFF_CTL_ADDR                                   (AOP_DEC_REG_BASE      + 0x8)
#define HWIO_AOP_TIMERS_CLK_OFF_CTL_PHYS                                   (AOP_DEC_REG_BASE_PHYS + 0x8)
#define HWIO_AOP_TIMERS_CLK_OFF_CTL_OFFS                                   (AOP_DEC_REG_BASE_OFFS + 0x8)
#define HWIO_AOP_TIMERS_CLK_OFF_CTL_RMSK                                          0x1
#define HWIO_AOP_TIMERS_CLK_OFF_CTL_IN                    \
                in_dword(HWIO_AOP_TIMERS_CLK_OFF_CTL_ADDR)
#define HWIO_AOP_TIMERS_CLK_OFF_CTL_INM(m)            \
                in_dword_masked(HWIO_AOP_TIMERS_CLK_OFF_CTL_ADDR, m)
#define HWIO_AOP_TIMERS_CLK_OFF_CTL_OUT(v)            \
                out_dword(HWIO_AOP_TIMERS_CLK_OFF_CTL_ADDR,v)
#define HWIO_AOP_TIMERS_CLK_OFF_CTL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_TIMERS_CLK_OFF_CTL_ADDR,m,v,HWIO_AOP_TIMERS_CLK_OFF_CTL_IN)
#define HWIO_AOP_TIMERS_CLK_OFF_CTL_WDOG_TIMER_CLK_OFF_BMSK                       0x1
#define HWIO_AOP_TIMERS_CLK_OFF_CTL_WDOG_TIMER_CLK_OFF_SHFT                         0

#define HWIO_AOP_IPC_ADDR                                                  (AOP_DEC_REG_BASE      + 0xc)
#define HWIO_AOP_IPC_PHYS                                                  (AOP_DEC_REG_BASE_PHYS + 0xc)
#define HWIO_AOP_IPC_OFFS                                                  (AOP_DEC_REG_BASE_OFFS + 0xc)
#define HWIO_AOP_IPC_RMSK                                                     0xfffff
#define HWIO_AOP_IPC_OUT(v)            \
                out_dword(HWIO_AOP_IPC_ADDR,v)
#define HWIO_AOP_IPC_CDSP_IPC_BMSK                                            0xc0000
#define HWIO_AOP_IPC_CDSP_IPC_SHFT                                                 18
#define HWIO_AOP_IPC_CAMSS_IPC_BMSK                                           0x30000
#define HWIO_AOP_IPC_CAMSS_IPC_SHFT                                                16
#define HWIO_AOP_IPC_GFX_IPC_BMSK                                              0xc000
#define HWIO_AOP_IPC_GFX_IPC_SHFT                                                  14
#define HWIO_AOP_IPC_SPSS_IPC_BMSK                                             0x3000
#define HWIO_AOP_IPC_SPSS_IPC_SHFT                                                 12
#define HWIO_AOP_IPC_MSS_IPC_BMSK                                               0xc00
#define HWIO_AOP_IPC_MSS_IPC_SHFT                                                  10
#define HWIO_AOP_IPC_SSC_IPC_BMSK                                               0x300
#define HWIO_AOP_IPC_SSC_IPC_SHFT                                                   8
#define HWIO_AOP_IPC_LPASS_IPC_BMSK                                              0xc0
#define HWIO_AOP_IPC_LPASS_IPC_SHFT                                                 6
#define HWIO_AOP_IPC_APCS_HV_IPC_BMSK                                            0x30
#define HWIO_AOP_IPC_APCS_HV_IPC_SHFT                                               4
#define HWIO_AOP_IPC_APCS_TZ_IPC_BMSK                                             0xc
#define HWIO_AOP_IPC_APCS_TZ_IPC_SHFT                                               2
#define HWIO_AOP_IPC_APCS_HLOS_IPC_BMSK                                           0x3
#define HWIO_AOP_IPC_APCS_HLOS_IPC_SHFT                                             0

#define HWIO_AOP_GPO_WDATA_ADDR                                            (AOP_DEC_REG_BASE      + 0x10)
#define HWIO_AOP_GPO_WDATA_PHYS                                            (AOP_DEC_REG_BASE_PHYS + 0x10)
#define HWIO_AOP_GPO_WDATA_OFFS                                            (AOP_DEC_REG_BASE_OFFS + 0x10)
#define HWIO_AOP_GPO_WDATA_RMSK                                            0xffffffff
#define HWIO_AOP_GPO_WDATA_IN                    \
                in_dword(HWIO_AOP_GPO_WDATA_ADDR)
#define HWIO_AOP_GPO_WDATA_INM(m)            \
                in_dword_masked(HWIO_AOP_GPO_WDATA_ADDR, m)
#define HWIO_AOP_GPO_WDATA_OUT(v)            \
                out_dword(HWIO_AOP_GPO_WDATA_ADDR,v)
#define HWIO_AOP_GPO_WDATA_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_GPO_WDATA_ADDR,m,v,HWIO_AOP_GPO_WDATA_IN)
#define HWIO_AOP_GPO_WDATA_WDATA_BMSK                                      0xffffffff
#define HWIO_AOP_GPO_WDATA_WDATA_SHFT                                               0

#define HWIO_AOP_GPO_WDSET_ADDR                                            (AOP_DEC_REG_BASE      + 0x14)
#define HWIO_AOP_GPO_WDSET_PHYS                                            (AOP_DEC_REG_BASE_PHYS + 0x14)
#define HWIO_AOP_GPO_WDSET_OFFS                                            (AOP_DEC_REG_BASE_OFFS + 0x14)
#define HWIO_AOP_GPO_WDSET_RMSK                                            0xffffffff
#define HWIO_AOP_GPO_WDSET_OUT(v)            \
                out_dword(HWIO_AOP_GPO_WDSET_ADDR,v)
#define HWIO_AOP_GPO_WDSET_WDSET_BMSK                                      0xffffffff
#define HWIO_AOP_GPO_WDSET_WDSET_SHFT                                               0

#define HWIO_AOP_GPO_WDCLR_ADDR                                            (AOP_DEC_REG_BASE      + 0x18)
#define HWIO_AOP_GPO_WDCLR_PHYS                                            (AOP_DEC_REG_BASE_PHYS + 0x18)
#define HWIO_AOP_GPO_WDCLR_OFFS                                            (AOP_DEC_REG_BASE_OFFS + 0x18)
#define HWIO_AOP_GPO_WDCLR_RMSK                                            0xffffffff
#define HWIO_AOP_GPO_WDCLR_OUT(v)            \
                out_dword(HWIO_AOP_GPO_WDCLR_ADDR,v)
#define HWIO_AOP_GPO_WDCLR_WDCLR_BMSK                                      0xffffffff
#define HWIO_AOP_GPO_WDCLR_WDCLR_SHFT                                               0

#define HWIO_AOP_SLAVES_CLK_GATING_ADDR                                    (AOP_DEC_REG_BASE      + 0x1c)
#define HWIO_AOP_SLAVES_CLK_GATING_PHYS                                    (AOP_DEC_REG_BASE_PHYS + 0x1c)
#define HWIO_AOP_SLAVES_CLK_GATING_OFFS                                    (AOP_DEC_REG_BASE_OFFS + 0x1c)
#define HWIO_AOP_SLAVES_CLK_GATING_RMSK                                           0xf
#define HWIO_AOP_SLAVES_CLK_GATING_IN                    \
                in_dword(HWIO_AOP_SLAVES_CLK_GATING_ADDR)
#define HWIO_AOP_SLAVES_CLK_GATING_INM(m)            \
                in_dword_masked(HWIO_AOP_SLAVES_CLK_GATING_ADDR, m)
#define HWIO_AOP_SLAVES_CLK_GATING_OUT(v)            \
                out_dword(HWIO_AOP_SLAVES_CLK_GATING_ADDR,v)
#define HWIO_AOP_SLAVES_CLK_GATING_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_SLAVES_CLK_GATING_ADDR,m,v,HWIO_AOP_SLAVES_CLK_GATING_IN)
#define HWIO_AOP_SLAVES_CLK_GATING_INTR_CLK_GATING_BMSK                           0x8
#define HWIO_AOP_SLAVES_CLK_GATING_INTR_CLK_GATING_SHFT                             3
#define HWIO_AOP_SLAVES_CLK_GATING_RAM_CLK_GATING_BMSK                            0x4
#define HWIO_AOP_SLAVES_CLK_GATING_RAM_CLK_GATING_SHFT                              2
#define HWIO_AOP_SLAVES_CLK_GATING_PERIPH_CLK_GATING_BMSK                         0x2
#define HWIO_AOP_SLAVES_CLK_GATING_PERIPH_CLK_GATING_SHFT                           1
#define HWIO_AOP_SLAVES_CLK_GATING_SLP_WKUP_FSM_CLK_GATING_BMSK                   0x1
#define HWIO_AOP_SLAVES_CLK_GATING_SLP_WKUP_FSM_CLK_GATING_SHFT                     0

#define HWIO_AOP_BOOTROM_REMAP_ADDR_ADDR                                   (AOP_DEC_REG_BASE      + 0x20)
#define HWIO_AOP_BOOTROM_REMAP_ADDR_PHYS                                   (AOP_DEC_REG_BASE_PHYS + 0x20)
#define HWIO_AOP_BOOTROM_REMAP_ADDR_OFFS                                   (AOP_DEC_REG_BASE_OFFS + 0x20)
#define HWIO_AOP_BOOTROM_REMAP_ADDR_RMSK                                   0xffffffff
#define HWIO_AOP_BOOTROM_REMAP_ADDR_IN                    \
                in_dword(HWIO_AOP_BOOTROM_REMAP_ADDR_ADDR)
#define HWIO_AOP_BOOTROM_REMAP_ADDR_INM(m)            \
                in_dword_masked(HWIO_AOP_BOOTROM_REMAP_ADDR_ADDR, m)
#define HWIO_AOP_BOOTROM_REMAP_ADDR_BOOTROM_REMAP_ADDR_BMSK                0xffffffff
#define HWIO_AOP_BOOTROM_REMAP_ADDR_BOOTROM_REMAP_ADDR_SHFT                         0

#define HWIO_AOP_SYSIF_REMAP_ADDR0_ADDR                                    (AOP_DEC_REG_BASE      + 0x24)
#define HWIO_AOP_SYSIF_REMAP_ADDR0_PHYS                                    (AOP_DEC_REG_BASE_PHYS + 0x24)
#define HWIO_AOP_SYSIF_REMAP_ADDR0_OFFS                                    (AOP_DEC_REG_BASE_OFFS + 0x24)
#define HWIO_AOP_SYSIF_REMAP_ADDR0_RMSK                                    0xffffffff
#define HWIO_AOP_SYSIF_REMAP_ADDR0_IN                    \
                in_dword(HWIO_AOP_SYSIF_REMAP_ADDR0_ADDR)
#define HWIO_AOP_SYSIF_REMAP_ADDR0_INM(m)            \
                in_dword_masked(HWIO_AOP_SYSIF_REMAP_ADDR0_ADDR, m)
#define HWIO_AOP_SYSIF_REMAP_ADDR0_SYSIF_REMAP_ADDR0_BMSK                  0xffffffff
#define HWIO_AOP_SYSIF_REMAP_ADDR0_SYSIF_REMAP_ADDR0_SHFT                           0

#define HWIO_AOP_SYSIF_REMAP_ADDR1_ADDR                                    (AOP_DEC_REG_BASE      + 0x28)
#define HWIO_AOP_SYSIF_REMAP_ADDR1_PHYS                                    (AOP_DEC_REG_BASE_PHYS + 0x28)
#define HWIO_AOP_SYSIF_REMAP_ADDR1_OFFS                                    (AOP_DEC_REG_BASE_OFFS + 0x28)
#define HWIO_AOP_SYSIF_REMAP_ADDR1_RMSK                                    0xffffffff
#define HWIO_AOP_SYSIF_REMAP_ADDR1_IN                    \
                in_dword(HWIO_AOP_SYSIF_REMAP_ADDR1_ADDR)
#define HWIO_AOP_SYSIF_REMAP_ADDR1_INM(m)            \
                in_dword_masked(HWIO_AOP_SYSIF_REMAP_ADDR1_ADDR, m)
#define HWIO_AOP_SYSIF_REMAP_ADDR1_SYSIF_REMAP_ADDR1_BMSK                  0xffffffff
#define HWIO_AOP_SYSIF_REMAP_ADDR1_SYSIF_REMAP_ADDR1_SHFT                           0

#define HWIO_AOP_SYSIF_REMAP_ADDR2_ADDR                                    (AOP_DEC_REG_BASE      + 0x2c)
#define HWIO_AOP_SYSIF_REMAP_ADDR2_PHYS                                    (AOP_DEC_REG_BASE_PHYS + 0x2c)
#define HWIO_AOP_SYSIF_REMAP_ADDR2_OFFS                                    (AOP_DEC_REG_BASE_OFFS + 0x2c)
#define HWIO_AOP_SYSIF_REMAP_ADDR2_RMSK                                    0xffffffff
#define HWIO_AOP_SYSIF_REMAP_ADDR2_IN                    \
                in_dword(HWIO_AOP_SYSIF_REMAP_ADDR2_ADDR)
#define HWIO_AOP_SYSIF_REMAP_ADDR2_INM(m)            \
                in_dword_masked(HWIO_AOP_SYSIF_REMAP_ADDR2_ADDR, m)
#define HWIO_AOP_SYSIF_REMAP_ADDR2_SYSIF_REMAP_ADDR2_BMSK                  0xffffffff
#define HWIO_AOP_SYSIF_REMAP_ADDR2_SYSIF_REMAP_ADDR2_SHFT                           0

#define HWIO_AOP_INTR_POLARITY_0_ADDR                                      (AOP_DEC_REG_BASE      + 0x30)
#define HWIO_AOP_INTR_POLARITY_0_PHYS                                      (AOP_DEC_REG_BASE_PHYS + 0x30)
#define HWIO_AOP_INTR_POLARITY_0_OFFS                                      (AOP_DEC_REG_BASE_OFFS + 0x30)
#define HWIO_AOP_INTR_POLARITY_0_RMSK                                      0xffffffff
#define HWIO_AOP_INTR_POLARITY_0_IN                    \
                in_dword(HWIO_AOP_INTR_POLARITY_0_ADDR)
#define HWIO_AOP_INTR_POLARITY_0_INM(m)            \
                in_dword_masked(HWIO_AOP_INTR_POLARITY_0_ADDR, m)
#define HWIO_AOP_INTR_POLARITY_0_OUT(v)            \
                out_dword(HWIO_AOP_INTR_POLARITY_0_ADDR,v)
#define HWIO_AOP_INTR_POLARITY_0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_INTR_POLARITY_0_ADDR,m,v,HWIO_AOP_INTR_POLARITY_0_IN)
#define HWIO_AOP_INTR_POLARITY_0_POLARITY_BMSK                             0xffffffff
#define HWIO_AOP_INTR_POLARITY_0_POLARITY_SHFT                                      0

#define HWIO_AOP_INTR_POLARITY_1_ADDR                                      (AOP_DEC_REG_BASE      + 0x34)
#define HWIO_AOP_INTR_POLARITY_1_PHYS                                      (AOP_DEC_REG_BASE_PHYS + 0x34)
#define HWIO_AOP_INTR_POLARITY_1_OFFS                                      (AOP_DEC_REG_BASE_OFFS + 0x34)
#define HWIO_AOP_INTR_POLARITY_1_RMSK                                      0xffffffff
#define HWIO_AOP_INTR_POLARITY_1_IN                    \
                in_dword(HWIO_AOP_INTR_POLARITY_1_ADDR)
#define HWIO_AOP_INTR_POLARITY_1_INM(m)            \
                in_dword_masked(HWIO_AOP_INTR_POLARITY_1_ADDR, m)
#define HWIO_AOP_INTR_POLARITY_1_OUT(v)            \
                out_dword(HWIO_AOP_INTR_POLARITY_1_ADDR,v)
#define HWIO_AOP_INTR_POLARITY_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_INTR_POLARITY_1_ADDR,m,v,HWIO_AOP_INTR_POLARITY_1_IN)
#define HWIO_AOP_INTR_POLARITY_1_POLARITY_BMSK                             0xffffffff
#define HWIO_AOP_INTR_POLARITY_1_POLARITY_SHFT                                      0

#define HWIO_AOP_INTR_EDG_LVL_0_ADDR                                       (AOP_DEC_REG_BASE      + 0x38)
#define HWIO_AOP_INTR_EDG_LVL_0_PHYS                                       (AOP_DEC_REG_BASE_PHYS + 0x38)
#define HWIO_AOP_INTR_EDG_LVL_0_OFFS                                       (AOP_DEC_REG_BASE_OFFS + 0x38)
#define HWIO_AOP_INTR_EDG_LVL_0_RMSK                                       0xffffffff
#define HWIO_AOP_INTR_EDG_LVL_0_IN                    \
                in_dword(HWIO_AOP_INTR_EDG_LVL_0_ADDR)
#define HWIO_AOP_INTR_EDG_LVL_0_INM(m)            \
                in_dword_masked(HWIO_AOP_INTR_EDG_LVL_0_ADDR, m)
#define HWIO_AOP_INTR_EDG_LVL_0_OUT(v)            \
                out_dword(HWIO_AOP_INTR_EDG_LVL_0_ADDR,v)
#define HWIO_AOP_INTR_EDG_LVL_0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_INTR_EDG_LVL_0_ADDR,m,v,HWIO_AOP_INTR_EDG_LVL_0_IN)
#define HWIO_AOP_INTR_EDG_LVL_0_EDG_LVL_BMSK                               0xffffffff
#define HWIO_AOP_INTR_EDG_LVL_0_EDG_LVL_SHFT                                        0

#define HWIO_AOP_INTR_EDG_LVL_1_ADDR                                       (AOP_DEC_REG_BASE      + 0x3c)
#define HWIO_AOP_INTR_EDG_LVL_1_PHYS                                       (AOP_DEC_REG_BASE_PHYS + 0x3c)
#define HWIO_AOP_INTR_EDG_LVL_1_OFFS                                       (AOP_DEC_REG_BASE_OFFS + 0x3c)
#define HWIO_AOP_INTR_EDG_LVL_1_RMSK                                       0xffffffff
#define HWIO_AOP_INTR_EDG_LVL_1_IN                    \
                in_dword(HWIO_AOP_INTR_EDG_LVL_1_ADDR)
#define HWIO_AOP_INTR_EDG_LVL_1_INM(m)            \
                in_dword_masked(HWIO_AOP_INTR_EDG_LVL_1_ADDR, m)
#define HWIO_AOP_INTR_EDG_LVL_1_OUT(v)            \
                out_dword(HWIO_AOP_INTR_EDG_LVL_1_ADDR,v)
#define HWIO_AOP_INTR_EDG_LVL_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_INTR_EDG_LVL_1_ADDR,m,v,HWIO_AOP_INTR_EDG_LVL_1_IN)
#define HWIO_AOP_INTR_EDG_LVL_1_EDG_LVL_BMSK                               0xffffffff
#define HWIO_AOP_INTR_EDG_LVL_1_EDG_LVL_SHFT                                        0

#define HWIO_AOP_WDOG_RESET_ADDR                                           (AOP_DEC_REG_BASE      + 0x40)
#define HWIO_AOP_WDOG_RESET_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0x40)
#define HWIO_AOP_WDOG_RESET_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0x40)
#define HWIO_AOP_WDOG_RESET_RMSK                                                  0x3
#define HWIO_AOP_WDOG_RESET_IN                    \
                in_dword(HWIO_AOP_WDOG_RESET_ADDR)
#define HWIO_AOP_WDOG_RESET_INM(m)            \
                in_dword_masked(HWIO_AOP_WDOG_RESET_ADDR, m)
#define HWIO_AOP_WDOG_RESET_OUT(v)            \
                out_dword(HWIO_AOP_WDOG_RESET_ADDR,v)
#define HWIO_AOP_WDOG_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_WDOG_RESET_ADDR,m,v,HWIO_AOP_WDOG_RESET_IN)
#define HWIO_AOP_WDOG_RESET_SYNC_STATUS_BMSK                                      0x2
#define HWIO_AOP_WDOG_RESET_SYNC_STATUS_SHFT                                        1
#define HWIO_AOP_WDOG_RESET_WDOG_RESET_BMSK                                       0x1
#define HWIO_AOP_WDOG_RESET_WDOG_RESET_SHFT                                         0

#define HWIO_AOP_WDOG_CTRL_ADDR                                            (AOP_DEC_REG_BASE      + 0x44)
#define HWIO_AOP_WDOG_CTRL_PHYS                                            (AOP_DEC_REG_BASE_PHYS + 0x44)
#define HWIO_AOP_WDOG_CTRL_OFFS                                            (AOP_DEC_REG_BASE_OFFS + 0x44)
#define HWIO_AOP_WDOG_CTRL_RMSK                                                   0x3
#define HWIO_AOP_WDOG_CTRL_IN                    \
                in_dword(HWIO_AOP_WDOG_CTRL_ADDR)
#define HWIO_AOP_WDOG_CTRL_INM(m)            \
                in_dword_masked(HWIO_AOP_WDOG_CTRL_ADDR, m)
#define HWIO_AOP_WDOG_CTRL_OUT(v)            \
                out_dword(HWIO_AOP_WDOG_CTRL_ADDR,v)
#define HWIO_AOP_WDOG_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_WDOG_CTRL_ADDR,m,v,HWIO_AOP_WDOG_CTRL_IN)
#define HWIO_AOP_WDOG_CTRL_HW_WAKEUP_SLEEP_EN_BMSK                                0x2
#define HWIO_AOP_WDOG_CTRL_HW_WAKEUP_SLEEP_EN_SHFT                                  1
#define HWIO_AOP_WDOG_CTRL_ENABLE_BMSK                                            0x1
#define HWIO_AOP_WDOG_CTRL_ENABLE_SHFT                                              0

#define HWIO_AOP_WDOG_STATUS_ADDR                                          (AOP_DEC_REG_BASE      + 0x48)
#define HWIO_AOP_WDOG_STATUS_PHYS                                          (AOP_DEC_REG_BASE_PHYS + 0x48)
#define HWIO_AOP_WDOG_STATUS_OFFS                                          (AOP_DEC_REG_BASE_OFFS + 0x48)
#define HWIO_AOP_WDOG_STATUS_RMSK                                          0x7fffffff
#define HWIO_AOP_WDOG_STATUS_IN                    \
                in_dword(HWIO_AOP_WDOG_STATUS_ADDR)
#define HWIO_AOP_WDOG_STATUS_INM(m)            \
                in_dword_masked(HWIO_AOP_WDOG_STATUS_ADDR, m)
#define HWIO_AOP_WDOG_STATUS_WDOG_COUNT_BMSK                               0x7ffffff8
#define HWIO_AOP_WDOG_STATUS_WDOG_COUNT_SHFT                                        3
#define HWIO_AOP_WDOG_STATUS_WDOG_CNT_RESET_STATUS_BMSK                           0x4
#define HWIO_AOP_WDOG_STATUS_WDOG_CNT_RESET_STATUS_SHFT                             2
#define HWIO_AOP_WDOG_STATUS_WDOG_FROZEN_BMSK                                     0x2
#define HWIO_AOP_WDOG_STATUS_WDOG_FROZEN_SHFT                                       1
#define HWIO_AOP_WDOG_STATUS_WDOG_EXPIRED_STATUS_BMSK                             0x1
#define HWIO_AOP_WDOG_STATUS_WDOG_EXPIRED_STATUS_SHFT                               0

#define HWIO_AOP_WDOG_BARK_TIME_ADDR                                       (AOP_DEC_REG_BASE      + 0x4c)
#define HWIO_AOP_WDOG_BARK_TIME_PHYS                                       (AOP_DEC_REG_BASE_PHYS + 0x4c)
#define HWIO_AOP_WDOG_BARK_TIME_OFFS                                       (AOP_DEC_REG_BASE_OFFS + 0x4c)
#define HWIO_AOP_WDOG_BARK_TIME_RMSK                                       0x1fffffff
#define HWIO_AOP_WDOG_BARK_TIME_IN                    \
                in_dword(HWIO_AOP_WDOG_BARK_TIME_ADDR)
#define HWIO_AOP_WDOG_BARK_TIME_INM(m)            \
                in_dword_masked(HWIO_AOP_WDOG_BARK_TIME_ADDR, m)
#define HWIO_AOP_WDOG_BARK_TIME_OUT(v)            \
                out_dword(HWIO_AOP_WDOG_BARK_TIME_ADDR,v)
#define HWIO_AOP_WDOG_BARK_TIME_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_WDOG_BARK_TIME_ADDR,m,v,HWIO_AOP_WDOG_BARK_TIME_IN)
#define HWIO_AOP_WDOG_BARK_TIME_SYNC_STATUS_BMSK                           0x10000000
#define HWIO_AOP_WDOG_BARK_TIME_SYNC_STATUS_SHFT                                   28
#define HWIO_AOP_WDOG_BARK_TIME_WDOG_BARK_VAL_BMSK                          0xfffffff
#define HWIO_AOP_WDOG_BARK_TIME_WDOG_BARK_VAL_SHFT                                  0

#define HWIO_AOP_WDOG_BITE_TIME_ADDR                                       (AOP_DEC_REG_BASE      + 0x50)
#define HWIO_AOP_WDOG_BITE_TIME_PHYS                                       (AOP_DEC_REG_BASE_PHYS + 0x50)
#define HWIO_AOP_WDOG_BITE_TIME_OFFS                                       (AOP_DEC_REG_BASE_OFFS + 0x50)
#define HWIO_AOP_WDOG_BITE_TIME_RMSK                                       0x1fffffff
#define HWIO_AOP_WDOG_BITE_TIME_IN                    \
                in_dword(HWIO_AOP_WDOG_BITE_TIME_ADDR)
#define HWIO_AOP_WDOG_BITE_TIME_INM(m)            \
                in_dword_masked(HWIO_AOP_WDOG_BITE_TIME_ADDR, m)
#define HWIO_AOP_WDOG_BITE_TIME_OUT(v)            \
                out_dword(HWIO_AOP_WDOG_BITE_TIME_ADDR,v)
#define HWIO_AOP_WDOG_BITE_TIME_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_WDOG_BITE_TIME_ADDR,m,v,HWIO_AOP_WDOG_BITE_TIME_IN)
#define HWIO_AOP_WDOG_BITE_TIME_SYNC_STATUS_BMSK                           0x10000000
#define HWIO_AOP_WDOG_BITE_TIME_SYNC_STATUS_SHFT                                   28
#define HWIO_AOP_WDOG_BITE_TIME_WDOG_BITE_VAL_BMSK                          0xfffffff
#define HWIO_AOP_WDOG_BITE_TIME_WDOG_BITE_VAL_SHFT                                  0

#define HWIO_AOP_WDOG_TEST_LOAD_ADDR                                       (AOP_DEC_REG_BASE      + 0x54)
#define HWIO_AOP_WDOG_TEST_LOAD_PHYS                                       (AOP_DEC_REG_BASE_PHYS + 0x54)
#define HWIO_AOP_WDOG_TEST_LOAD_OFFS                                       (AOP_DEC_REG_BASE_OFFS + 0x54)
#define HWIO_AOP_WDOG_TEST_LOAD_RMSK                                              0x3
#define HWIO_AOP_WDOG_TEST_LOAD_IN                    \
                in_dword(HWIO_AOP_WDOG_TEST_LOAD_ADDR)
#define HWIO_AOP_WDOG_TEST_LOAD_INM(m)            \
                in_dword_masked(HWIO_AOP_WDOG_TEST_LOAD_ADDR, m)
#define HWIO_AOP_WDOG_TEST_LOAD_OUT(v)            \
                out_dword(HWIO_AOP_WDOG_TEST_LOAD_ADDR,v)
#define HWIO_AOP_WDOG_TEST_LOAD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_WDOG_TEST_LOAD_ADDR,m,v,HWIO_AOP_WDOG_TEST_LOAD_IN)
#define HWIO_AOP_WDOG_TEST_LOAD_SYNC_STATUS_BMSK                                  0x2
#define HWIO_AOP_WDOG_TEST_LOAD_SYNC_STATUS_SHFT                                    1
#define HWIO_AOP_WDOG_TEST_LOAD_LOAD_BMSK                                         0x1
#define HWIO_AOP_WDOG_TEST_LOAD_LOAD_SHFT                                           0

#define HWIO_AOP_WDOG_TEST_ADDR                                            (AOP_DEC_REG_BASE      + 0x58)
#define HWIO_AOP_WDOG_TEST_PHYS                                            (AOP_DEC_REG_BASE_PHYS + 0x58)
#define HWIO_AOP_WDOG_TEST_OFFS                                            (AOP_DEC_REG_BASE_OFFS + 0x58)
#define HWIO_AOP_WDOG_TEST_RMSK                                            0x1fffffff
#define HWIO_AOP_WDOG_TEST_IN                    \
                in_dword(HWIO_AOP_WDOG_TEST_ADDR)
#define HWIO_AOP_WDOG_TEST_INM(m)            \
                in_dword_masked(HWIO_AOP_WDOG_TEST_ADDR, m)
#define HWIO_AOP_WDOG_TEST_OUT(v)            \
                out_dword(HWIO_AOP_WDOG_TEST_ADDR,v)
#define HWIO_AOP_WDOG_TEST_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_WDOG_TEST_ADDR,m,v,HWIO_AOP_WDOG_TEST_IN)
#define HWIO_AOP_WDOG_TEST_SYNC_STATUS_BMSK                                0x10000000
#define HWIO_AOP_WDOG_TEST_SYNC_STATUS_SHFT                                        28
#define HWIO_AOP_WDOG_TEST_LOAD_VALUE_BMSK                                  0xfffffff
#define HWIO_AOP_WDOG_TEST_LOAD_VALUE_SHFT                                          0

#define HWIO_AOP_TEST_BUS_SEL_ADDR                                         (AOP_DEC_REG_BASE      + 0x5c)
#define HWIO_AOP_TEST_BUS_SEL_PHYS                                         (AOP_DEC_REG_BASE_PHYS + 0x5c)
#define HWIO_AOP_TEST_BUS_SEL_OFFS                                         (AOP_DEC_REG_BASE_OFFS + 0x5c)
#define HWIO_AOP_TEST_BUS_SEL_RMSK                                                0xf
#define HWIO_AOP_TEST_BUS_SEL_IN                    \
                in_dword(HWIO_AOP_TEST_BUS_SEL_ADDR)
#define HWIO_AOP_TEST_BUS_SEL_INM(m)            \
                in_dword_masked(HWIO_AOP_TEST_BUS_SEL_ADDR, m)
#define HWIO_AOP_TEST_BUS_SEL_OUT(v)            \
                out_dword(HWIO_AOP_TEST_BUS_SEL_ADDR,v)
#define HWIO_AOP_TEST_BUS_SEL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_TEST_BUS_SEL_ADDR,m,v,HWIO_AOP_TEST_BUS_SEL_IN)
#define HWIO_AOP_TEST_BUS_SEL_VAL_BMSK                                            0xf
#define HWIO_AOP_TEST_BUS_SEL_VAL_SHFT                                              0

#define HWIO_AOP_SPARE_REG0_ADDR                                           (AOP_DEC_REG_BASE      + 0x60)
#define HWIO_AOP_SPARE_REG0_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0x60)
#define HWIO_AOP_SPARE_REG0_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0x60)
#define HWIO_AOP_SPARE_REG0_RMSK                                           0xffffffff
#define HWIO_AOP_SPARE_REG0_IN                    \
                in_dword(HWIO_AOP_SPARE_REG0_ADDR)
#define HWIO_AOP_SPARE_REG0_INM(m)            \
                in_dword_masked(HWIO_AOP_SPARE_REG0_ADDR, m)
#define HWIO_AOP_SPARE_REG0_OUT(v)            \
                out_dword(HWIO_AOP_SPARE_REG0_ADDR,v)
#define HWIO_AOP_SPARE_REG0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_SPARE_REG0_ADDR,m,v,HWIO_AOP_SPARE_REG0_IN)
#define HWIO_AOP_SPARE_REG0_WDATA_BMSK                                     0xffffffff
#define HWIO_AOP_SPARE_REG0_WDATA_SHFT                                              0

#define HWIO_AOP_SPARE_REG1_ADDR                                           (AOP_DEC_REG_BASE      + 0x64)
#define HWIO_AOP_SPARE_REG1_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0x64)
#define HWIO_AOP_SPARE_REG1_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0x64)
#define HWIO_AOP_SPARE_REG1_RMSK                                           0xffffffff
#define HWIO_AOP_SPARE_REG1_IN                    \
                in_dword(HWIO_AOP_SPARE_REG1_ADDR)
#define HWIO_AOP_SPARE_REG1_INM(m)            \
                in_dword_masked(HWIO_AOP_SPARE_REG1_ADDR, m)
#define HWIO_AOP_SPARE_REG1_OUT(v)            \
                out_dword(HWIO_AOP_SPARE_REG1_ADDR,v)
#define HWIO_AOP_SPARE_REG1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_SPARE_REG1_ADDR,m,v,HWIO_AOP_SPARE_REG1_IN)
#define HWIO_AOP_SPARE_REG1_WDATA_BMSK                                     0xffffffff
#define HWIO_AOP_SPARE_REG1_WDATA_SHFT                                              0

#define HWIO_AOP_SPARE_REG2_ADDR                                           (AOP_DEC_REG_BASE      + 0x68)
#define HWIO_AOP_SPARE_REG2_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0x68)
#define HWIO_AOP_SPARE_REG2_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0x68)
#define HWIO_AOP_SPARE_REG2_RMSK                                           0xffffffff
#define HWIO_AOP_SPARE_REG2_IN                    \
                in_dword(HWIO_AOP_SPARE_REG2_ADDR)
#define HWIO_AOP_SPARE_REG2_INM(m)            \
                in_dword_masked(HWIO_AOP_SPARE_REG2_ADDR, m)
#define HWIO_AOP_SPARE_REG2_OUT(v)            \
                out_dword(HWIO_AOP_SPARE_REG2_ADDR,v)
#define HWIO_AOP_SPARE_REG2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_SPARE_REG2_ADDR,m,v,HWIO_AOP_SPARE_REG2_IN)
#define HWIO_AOP_SPARE_REG2_WDATA_BMSK                                     0xffffffff
#define HWIO_AOP_SPARE_REG2_WDATA_SHFT                                              0

#define HWIO_AOP_SPARE_REG3_ADDR                                           (AOP_DEC_REG_BASE      + 0x6c)
#define HWIO_AOP_SPARE_REG3_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0x6c)
#define HWIO_AOP_SPARE_REG3_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0x6c)
#define HWIO_AOP_SPARE_REG3_RMSK                                           0xffffffff
#define HWIO_AOP_SPARE_REG3_IN                    \
                in_dword(HWIO_AOP_SPARE_REG3_ADDR)
#define HWIO_AOP_SPARE_REG3_INM(m)            \
                in_dword_masked(HWIO_AOP_SPARE_REG3_ADDR, m)
#define HWIO_AOP_SPARE_REG3_OUT(v)            \
                out_dword(HWIO_AOP_SPARE_REG3_ADDR,v)
#define HWIO_AOP_SPARE_REG3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_SPARE_REG3_ADDR,m,v,HWIO_AOP_SPARE_REG3_IN)
#define HWIO_AOP_SPARE_REG3_WDATA_BMSK                                     0xffffffff
#define HWIO_AOP_SPARE_REG3_WDATA_SHFT                                              0

#define HWIO_AOP_CODE_RAM_DENSITY_ADDR                                     (AOP_DEC_REG_BASE      + 0x70)
#define HWIO_AOP_CODE_RAM_DENSITY_PHYS                                     (AOP_DEC_REG_BASE_PHYS + 0x70)
#define HWIO_AOP_CODE_RAM_DENSITY_OFFS                                     (AOP_DEC_REG_BASE_OFFS + 0x70)
#define HWIO_AOP_CODE_RAM_DENSITY_RMSK                                       0xffffff
#define HWIO_AOP_CODE_RAM_DENSITY_IN                    \
                in_dword(HWIO_AOP_CODE_RAM_DENSITY_ADDR)
#define HWIO_AOP_CODE_RAM_DENSITY_INM(m)            \
                in_dword_masked(HWIO_AOP_CODE_RAM_DENSITY_ADDR, m)
#define HWIO_AOP_CODE_RAM_DENSITY_DENSITY_BMSK                               0xffffff
#define HWIO_AOP_CODE_RAM_DENSITY_DENSITY_SHFT                                      0

#define HWIO_AOP_DATA_RAM_DENSITY_ADDR                                     (AOP_DEC_REG_BASE      + 0x74)
#define HWIO_AOP_DATA_RAM_DENSITY_PHYS                                     (AOP_DEC_REG_BASE_PHYS + 0x74)
#define HWIO_AOP_DATA_RAM_DENSITY_OFFS                                     (AOP_DEC_REG_BASE_OFFS + 0x74)
#define HWIO_AOP_DATA_RAM_DENSITY_RMSK                                       0xffffff
#define HWIO_AOP_DATA_RAM_DENSITY_IN                    \
                in_dword(HWIO_AOP_DATA_RAM_DENSITY_ADDR)
#define HWIO_AOP_DATA_RAM_DENSITY_INM(m)            \
                in_dword_masked(HWIO_AOP_DATA_RAM_DENSITY_ADDR, m)
#define HWIO_AOP_DATA_RAM_DENSITY_DENSITY_BMSK                               0xffffff
#define HWIO_AOP_DATA_RAM_DENSITY_DENSITY_SHFT                                      0

#define HWIO_AOP_MSG_RAM_DENSITY_ADDR                                      (AOP_DEC_REG_BASE      + 0x78)
#define HWIO_AOP_MSG_RAM_DENSITY_PHYS                                      (AOP_DEC_REG_BASE_PHYS + 0x78)
#define HWIO_AOP_MSG_RAM_DENSITY_OFFS                                      (AOP_DEC_REG_BASE_OFFS + 0x78)
#define HWIO_AOP_MSG_RAM_DENSITY_RMSK                                        0xffffff
#define HWIO_AOP_MSG_RAM_DENSITY_IN                    \
                in_dword(HWIO_AOP_MSG_RAM_DENSITY_ADDR)
#define HWIO_AOP_MSG_RAM_DENSITY_INM(m)            \
                in_dword_masked(HWIO_AOP_MSG_RAM_DENSITY_ADDR, m)
#define HWIO_AOP_MSG_RAM_DENSITY_DENSITY_BMSK                                0xffffff
#define HWIO_AOP_MSG_RAM_DENSITY_DENSITY_SHFT                                       0

#define HWIO_AOP_INTR_POLARITY_2_ADDR                                      (AOP_DEC_REG_BASE      + 0x7c)
#define HWIO_AOP_INTR_POLARITY_2_PHYS                                      (AOP_DEC_REG_BASE_PHYS + 0x7c)
#define HWIO_AOP_INTR_POLARITY_2_OFFS                                      (AOP_DEC_REG_BASE_OFFS + 0x7c)
#define HWIO_AOP_INTR_POLARITY_2_RMSK                                      0xffffffff
#define HWIO_AOP_INTR_POLARITY_2_IN                    \
                in_dword(HWIO_AOP_INTR_POLARITY_2_ADDR)
#define HWIO_AOP_INTR_POLARITY_2_INM(m)            \
                in_dword_masked(HWIO_AOP_INTR_POLARITY_2_ADDR, m)
#define HWIO_AOP_INTR_POLARITY_2_OUT(v)            \
                out_dword(HWIO_AOP_INTR_POLARITY_2_ADDR,v)
#define HWIO_AOP_INTR_POLARITY_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_INTR_POLARITY_2_ADDR,m,v,HWIO_AOP_INTR_POLARITY_2_IN)
#define HWIO_AOP_INTR_POLARITY_2_POLARITY_BMSK                             0xffffffff
#define HWIO_AOP_INTR_POLARITY_2_POLARITY_SHFT                                      0

#define HWIO_AOP_INTR_POLARITY_3_ADDR                                      (AOP_DEC_REG_BASE      + 0x80)
#define HWIO_AOP_INTR_POLARITY_3_PHYS                                      (AOP_DEC_REG_BASE_PHYS + 0x80)
#define HWIO_AOP_INTR_POLARITY_3_OFFS                                      (AOP_DEC_REG_BASE_OFFS + 0x80)
#define HWIO_AOP_INTR_POLARITY_3_RMSK                                      0xffffffff
#define HWIO_AOP_INTR_POLARITY_3_IN                    \
                in_dword(HWIO_AOP_INTR_POLARITY_3_ADDR)
#define HWIO_AOP_INTR_POLARITY_3_INM(m)            \
                in_dword_masked(HWIO_AOP_INTR_POLARITY_3_ADDR, m)
#define HWIO_AOP_INTR_POLARITY_3_OUT(v)            \
                out_dword(HWIO_AOP_INTR_POLARITY_3_ADDR,v)
#define HWIO_AOP_INTR_POLARITY_3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_INTR_POLARITY_3_ADDR,m,v,HWIO_AOP_INTR_POLARITY_3_IN)
#define HWIO_AOP_INTR_POLARITY_3_POLARITY_BMSK                             0xffffffff
#define HWIO_AOP_INTR_POLARITY_3_POLARITY_SHFT                                      0

#define HWIO_AOP_INTR_EDG_LVL_2_ADDR                                       (AOP_DEC_REG_BASE      + 0x84)
#define HWIO_AOP_INTR_EDG_LVL_2_PHYS                                       (AOP_DEC_REG_BASE_PHYS + 0x84)
#define HWIO_AOP_INTR_EDG_LVL_2_OFFS                                       (AOP_DEC_REG_BASE_OFFS + 0x84)
#define HWIO_AOP_INTR_EDG_LVL_2_RMSK                                       0xffffffff
#define HWIO_AOP_INTR_EDG_LVL_2_IN                    \
                in_dword(HWIO_AOP_INTR_EDG_LVL_2_ADDR)
#define HWIO_AOP_INTR_EDG_LVL_2_INM(m)            \
                in_dword_masked(HWIO_AOP_INTR_EDG_LVL_2_ADDR, m)
#define HWIO_AOP_INTR_EDG_LVL_2_OUT(v)            \
                out_dword(HWIO_AOP_INTR_EDG_LVL_2_ADDR,v)
#define HWIO_AOP_INTR_EDG_LVL_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_INTR_EDG_LVL_2_ADDR,m,v,HWIO_AOP_INTR_EDG_LVL_2_IN)
#define HWIO_AOP_INTR_EDG_LVL_2_EDG_LVL_BMSK                               0xffffffff
#define HWIO_AOP_INTR_EDG_LVL_2_EDG_LVL_SHFT                                        0

#define HWIO_AOP_INTR_EDG_LVL_3_ADDR                                       (AOP_DEC_REG_BASE      + 0x88)
#define HWIO_AOP_INTR_EDG_LVL_3_PHYS                                       (AOP_DEC_REG_BASE_PHYS + 0x88)
#define HWIO_AOP_INTR_EDG_LVL_3_OFFS                                       (AOP_DEC_REG_BASE_OFFS + 0x88)
#define HWIO_AOP_INTR_EDG_LVL_3_RMSK                                       0xffffffff
#define HWIO_AOP_INTR_EDG_LVL_3_IN                    \
                in_dword(HWIO_AOP_INTR_EDG_LVL_3_ADDR)
#define HWIO_AOP_INTR_EDG_LVL_3_INM(m)            \
                in_dword_masked(HWIO_AOP_INTR_EDG_LVL_3_ADDR, m)
#define HWIO_AOP_INTR_EDG_LVL_3_OUT(v)            \
                out_dword(HWIO_AOP_INTR_EDG_LVL_3_ADDR,v)
#define HWIO_AOP_INTR_EDG_LVL_3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_INTR_EDG_LVL_3_ADDR,m,v,HWIO_AOP_INTR_EDG_LVL_3_IN)
#define HWIO_AOP_INTR_EDG_LVL_3_EDG_LVL_BMSK                               0xffffffff
#define HWIO_AOP_INTR_EDG_LVL_3_EDG_LVL_SHFT                                        0

#define HWIO_AOP_IPC_PULSEWIDTH_ADDR                                       (AOP_DEC_REG_BASE      + 0x8c)
#define HWIO_AOP_IPC_PULSEWIDTH_PHYS                                       (AOP_DEC_REG_BASE_PHYS + 0x8c)
#define HWIO_AOP_IPC_PULSEWIDTH_OFFS                                       (AOP_DEC_REG_BASE_OFFS + 0x8c)
#define HWIO_AOP_IPC_PULSEWIDTH_RMSK                                              0xf
#define HWIO_AOP_IPC_PULSEWIDTH_IN                    \
                in_dword(HWIO_AOP_IPC_PULSEWIDTH_ADDR)
#define HWIO_AOP_IPC_PULSEWIDTH_INM(m)            \
                in_dword_masked(HWIO_AOP_IPC_PULSEWIDTH_ADDR, m)
#define HWIO_AOP_IPC_PULSEWIDTH_OUT(v)            \
                out_dword(HWIO_AOP_IPC_PULSEWIDTH_ADDR,v)
#define HWIO_AOP_IPC_PULSEWIDTH_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_IPC_PULSEWIDTH_ADDR,m,v,HWIO_AOP_IPC_PULSEWIDTH_IN)
#define HWIO_AOP_IPC_PULSEWIDTH_WIDTH_BMSK                                        0xf
#define HWIO_AOP_IPC_PULSEWIDTH_WIDTH_SHFT                                          0

#define HWIO_AOP_ALWAYS_ON_PWR_HOLD_ADDR                                   (AOP_DEC_REG_BASE      + 0x90)
#define HWIO_AOP_ALWAYS_ON_PWR_HOLD_PHYS                                   (AOP_DEC_REG_BASE_PHYS + 0x90)
#define HWIO_AOP_ALWAYS_ON_PWR_HOLD_OFFS                                   (AOP_DEC_REG_BASE_OFFS + 0x90)
#define HWIO_AOP_ALWAYS_ON_PWR_HOLD_RMSK                                          0x1
#define HWIO_AOP_ALWAYS_ON_PWR_HOLD_IN                    \
                in_dword(HWIO_AOP_ALWAYS_ON_PWR_HOLD_ADDR)
#define HWIO_AOP_ALWAYS_ON_PWR_HOLD_INM(m)            \
                in_dword_masked(HWIO_AOP_ALWAYS_ON_PWR_HOLD_ADDR, m)
#define HWIO_AOP_ALWAYS_ON_PWR_HOLD_OUT(v)            \
                out_dword(HWIO_AOP_ALWAYS_ON_PWR_HOLD_ADDR,v)
#define HWIO_AOP_ALWAYS_ON_PWR_HOLD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_ALWAYS_ON_PWR_HOLD_ADDR,m,v,HWIO_AOP_ALWAYS_ON_PWR_HOLD_IN)
#define HWIO_AOP_ALWAYS_ON_PWR_HOLD_ALWAYS_ON_PWR_HOLD_BMSK                       0x1
#define HWIO_AOP_ALWAYS_ON_PWR_HOLD_ALWAYS_ON_PWR_HOLD_SHFT                         0

#define HWIO_AOP_MINI_MMU_0_ADDR                                           (AOP_DEC_REG_BASE      + 0x94)
#define HWIO_AOP_MINI_MMU_0_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0x94)
#define HWIO_AOP_MINI_MMU_0_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0x94)
#define HWIO_AOP_MINI_MMU_0_RMSK                                           0x80000fff
#define HWIO_AOP_MINI_MMU_0_IN                    \
                in_dword(HWIO_AOP_MINI_MMU_0_ADDR)
#define HWIO_AOP_MINI_MMU_0_INM(m)            \
                in_dword_masked(HWIO_AOP_MINI_MMU_0_ADDR, m)
#define HWIO_AOP_MINI_MMU_0_OUT(v)            \
                out_dword(HWIO_AOP_MINI_MMU_0_ADDR,v)
#define HWIO_AOP_MINI_MMU_0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_MINI_MMU_0_ADDR,m,v,HWIO_AOP_MINI_MMU_0_IN)
#define HWIO_AOP_MINI_MMU_0_MMU_ENABLE_BMSK                                0x80000000
#define HWIO_AOP_MINI_MMU_0_MMU_ENABLE_SHFT                                        31
#define HWIO_AOP_MINI_MMU_0_LPAE_35_32_BMSK                                     0xf00
#define HWIO_AOP_MINI_MMU_0_LPAE_35_32_SHFT                                         8
#define HWIO_AOP_MINI_MMU_0_PAGE_SELECT_BMSK                                     0xff
#define HWIO_AOP_MINI_MMU_0_PAGE_SELECT_SHFT                                        0

#define HWIO_AOP_MINI_MMU_1_ADDR                                           (AOP_DEC_REG_BASE      + 0x98)
#define HWIO_AOP_MINI_MMU_1_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0x98)
#define HWIO_AOP_MINI_MMU_1_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0x98)
#define HWIO_AOP_MINI_MMU_1_RMSK                                           0x80000fff
#define HWIO_AOP_MINI_MMU_1_IN                    \
                in_dword(HWIO_AOP_MINI_MMU_1_ADDR)
#define HWIO_AOP_MINI_MMU_1_INM(m)            \
                in_dword_masked(HWIO_AOP_MINI_MMU_1_ADDR, m)
#define HWIO_AOP_MINI_MMU_1_OUT(v)            \
                out_dword(HWIO_AOP_MINI_MMU_1_ADDR,v)
#define HWIO_AOP_MINI_MMU_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_MINI_MMU_1_ADDR,m,v,HWIO_AOP_MINI_MMU_1_IN)
#define HWIO_AOP_MINI_MMU_1_MMU_ENABLE_BMSK                                0x80000000
#define HWIO_AOP_MINI_MMU_1_MMU_ENABLE_SHFT                                        31
#define HWIO_AOP_MINI_MMU_1_LPAE_35_32_BMSK                                     0xf00
#define HWIO_AOP_MINI_MMU_1_LPAE_35_32_SHFT                                         8
#define HWIO_AOP_MINI_MMU_1_PAGE_SELECT_BMSK                                     0xff
#define HWIO_AOP_MINI_MMU_1_PAGE_SELECT_SHFT                                        0

#define HWIO_AOP_MINI_MMU_2_ADDR                                           (AOP_DEC_REG_BASE      + 0x9c)
#define HWIO_AOP_MINI_MMU_2_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0x9c)
#define HWIO_AOP_MINI_MMU_2_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0x9c)
#define HWIO_AOP_MINI_MMU_2_RMSK                                           0x80000fff
#define HWIO_AOP_MINI_MMU_2_IN                    \
                in_dword(HWIO_AOP_MINI_MMU_2_ADDR)
#define HWIO_AOP_MINI_MMU_2_INM(m)            \
                in_dword_masked(HWIO_AOP_MINI_MMU_2_ADDR, m)
#define HWIO_AOP_MINI_MMU_2_OUT(v)            \
                out_dword(HWIO_AOP_MINI_MMU_2_ADDR,v)
#define HWIO_AOP_MINI_MMU_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_MINI_MMU_2_ADDR,m,v,HWIO_AOP_MINI_MMU_2_IN)
#define HWIO_AOP_MINI_MMU_2_MMU_ENABLE_BMSK                                0x80000000
#define HWIO_AOP_MINI_MMU_2_MMU_ENABLE_SHFT                                        31
#define HWIO_AOP_MINI_MMU_2_LPAE_35_32_BMSK                                     0xf00
#define HWIO_AOP_MINI_MMU_2_LPAE_35_32_SHFT                                         8
#define HWIO_AOP_MINI_MMU_2_PAGE_SELECT_BMSK                                     0xff
#define HWIO_AOP_MINI_MMU_2_PAGE_SELECT_SHFT                                        0

#define HWIO_AOP_MINI_MMU_3_ADDR                                           (AOP_DEC_REG_BASE      + 0xa0)
#define HWIO_AOP_MINI_MMU_3_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0xa0)
#define HWIO_AOP_MINI_MMU_3_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0xa0)
#define HWIO_AOP_MINI_MMU_3_RMSK                                           0x80000fff
#define HWIO_AOP_MINI_MMU_3_IN                    \
                in_dword(HWIO_AOP_MINI_MMU_3_ADDR)
#define HWIO_AOP_MINI_MMU_3_INM(m)            \
                in_dword_masked(HWIO_AOP_MINI_MMU_3_ADDR, m)
#define HWIO_AOP_MINI_MMU_3_OUT(v)            \
                out_dword(HWIO_AOP_MINI_MMU_3_ADDR,v)
#define HWIO_AOP_MINI_MMU_3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_MINI_MMU_3_ADDR,m,v,HWIO_AOP_MINI_MMU_3_IN)
#define HWIO_AOP_MINI_MMU_3_MMU_ENABLE_BMSK                                0x80000000
#define HWIO_AOP_MINI_MMU_3_MMU_ENABLE_SHFT                                        31
#define HWIO_AOP_MINI_MMU_3_LPAE_35_32_BMSK                                     0xf00
#define HWIO_AOP_MINI_MMU_3_LPAE_35_32_SHFT                                         8
#define HWIO_AOP_MINI_MMU_3_PAGE_SELECT_BMSK                                     0xff
#define HWIO_AOP_MINI_MMU_3_PAGE_SELECT_SHFT                                        0

#define HWIO_AOP_MINI_MMU_4_ADDR                                           (AOP_DEC_REG_BASE      + 0xa4)
#define HWIO_AOP_MINI_MMU_4_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0xa4)
#define HWIO_AOP_MINI_MMU_4_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0xa4)
#define HWIO_AOP_MINI_MMU_4_RMSK                                           0x80000fff
#define HWIO_AOP_MINI_MMU_4_IN                    \
                in_dword(HWIO_AOP_MINI_MMU_4_ADDR)
#define HWIO_AOP_MINI_MMU_4_INM(m)            \
                in_dword_masked(HWIO_AOP_MINI_MMU_4_ADDR, m)
#define HWIO_AOP_MINI_MMU_4_OUT(v)            \
                out_dword(HWIO_AOP_MINI_MMU_4_ADDR,v)
#define HWIO_AOP_MINI_MMU_4_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_MINI_MMU_4_ADDR,m,v,HWIO_AOP_MINI_MMU_4_IN)
#define HWIO_AOP_MINI_MMU_4_MMU_ENABLE_BMSK                                0x80000000
#define HWIO_AOP_MINI_MMU_4_MMU_ENABLE_SHFT                                        31
#define HWIO_AOP_MINI_MMU_4_LPAE_35_32_BMSK                                     0xf00
#define HWIO_AOP_MINI_MMU_4_LPAE_35_32_SHFT                                         8
#define HWIO_AOP_MINI_MMU_4_PAGE_SELECT_BMSK                                     0xff
#define HWIO_AOP_MINI_MMU_4_PAGE_SELECT_SHFT                                        0

#define HWIO_AOP_MINI_MMU_5_ADDR                                           (AOP_DEC_REG_BASE      + 0xa8)
#define HWIO_AOP_MINI_MMU_5_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0xa8)
#define HWIO_AOP_MINI_MMU_5_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0xa8)
#define HWIO_AOP_MINI_MMU_5_RMSK                                           0x80000fff
#define HWIO_AOP_MINI_MMU_5_IN                    \
                in_dword(HWIO_AOP_MINI_MMU_5_ADDR)
#define HWIO_AOP_MINI_MMU_5_INM(m)            \
                in_dword_masked(HWIO_AOP_MINI_MMU_5_ADDR, m)
#define HWIO_AOP_MINI_MMU_5_OUT(v)            \
                out_dword(HWIO_AOP_MINI_MMU_5_ADDR,v)
#define HWIO_AOP_MINI_MMU_5_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_MINI_MMU_5_ADDR,m,v,HWIO_AOP_MINI_MMU_5_IN)
#define HWIO_AOP_MINI_MMU_5_MMU_ENABLE_BMSK                                0x80000000
#define HWIO_AOP_MINI_MMU_5_MMU_ENABLE_SHFT                                        31
#define HWIO_AOP_MINI_MMU_5_LPAE_35_32_BMSK                                     0xf00
#define HWIO_AOP_MINI_MMU_5_LPAE_35_32_SHFT                                         8
#define HWIO_AOP_MINI_MMU_5_PAGE_SELECT_BMSK                                     0xff
#define HWIO_AOP_MINI_MMU_5_PAGE_SELECT_SHFT                                        0

#define HWIO_AOP_MINI_MMU_6_ADDR                                           (AOP_DEC_REG_BASE      + 0xac)
#define HWIO_AOP_MINI_MMU_6_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0xac)
#define HWIO_AOP_MINI_MMU_6_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0xac)
#define HWIO_AOP_MINI_MMU_6_RMSK                                           0x80000fff
#define HWIO_AOP_MINI_MMU_6_IN                    \
                in_dword(HWIO_AOP_MINI_MMU_6_ADDR)
#define HWIO_AOP_MINI_MMU_6_INM(m)            \
                in_dword_masked(HWIO_AOP_MINI_MMU_6_ADDR, m)
#define HWIO_AOP_MINI_MMU_6_OUT(v)            \
                out_dword(HWIO_AOP_MINI_MMU_6_ADDR,v)
#define HWIO_AOP_MINI_MMU_6_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_MINI_MMU_6_ADDR,m,v,HWIO_AOP_MINI_MMU_6_IN)
#define HWIO_AOP_MINI_MMU_6_MMU_ENABLE_BMSK                                0x80000000
#define HWIO_AOP_MINI_MMU_6_MMU_ENABLE_SHFT                                        31
#define HWIO_AOP_MINI_MMU_6_LPAE_35_32_BMSK                                     0xf00
#define HWIO_AOP_MINI_MMU_6_LPAE_35_32_SHFT                                         8
#define HWIO_AOP_MINI_MMU_6_PAGE_SELECT_BMSK                                     0xff
#define HWIO_AOP_MINI_MMU_6_PAGE_SELECT_SHFT                                        0

#define HWIO_AOP_MINI_MMU_7_ADDR                                           (AOP_DEC_REG_BASE      + 0xb0)
#define HWIO_AOP_MINI_MMU_7_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0xb0)
#define HWIO_AOP_MINI_MMU_7_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0xb0)
#define HWIO_AOP_MINI_MMU_7_RMSK                                           0x80000fff
#define HWIO_AOP_MINI_MMU_7_IN                    \
                in_dword(HWIO_AOP_MINI_MMU_7_ADDR)
#define HWIO_AOP_MINI_MMU_7_INM(m)            \
                in_dword_masked(HWIO_AOP_MINI_MMU_7_ADDR, m)
#define HWIO_AOP_MINI_MMU_7_OUT(v)            \
                out_dword(HWIO_AOP_MINI_MMU_7_ADDR,v)
#define HWIO_AOP_MINI_MMU_7_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_MINI_MMU_7_ADDR,m,v,HWIO_AOP_MINI_MMU_7_IN)
#define HWIO_AOP_MINI_MMU_7_MMU_ENABLE_BMSK                                0x80000000
#define HWIO_AOP_MINI_MMU_7_MMU_ENABLE_SHFT                                        31
#define HWIO_AOP_MINI_MMU_7_LPAE_35_32_BMSK                                     0xf00
#define HWIO_AOP_MINI_MMU_7_LPAE_35_32_SHFT                                         8
#define HWIO_AOP_MINI_MMU_7_PAGE_SELECT_BMSK                                     0xff
#define HWIO_AOP_MINI_MMU_7_PAGE_SELECT_SHFT                                        0

#define HWIO_AOP_RVSS_BASE_ADDR_ADDR                                       (AOP_DEC_REG_BASE      + 0xb4)
#define HWIO_AOP_RVSS_BASE_ADDR_PHYS                                       (AOP_DEC_REG_BASE_PHYS + 0xb4)
#define HWIO_AOP_RVSS_BASE_ADDR_OFFS                                       (AOP_DEC_REG_BASE_OFFS + 0xb4)
#define HWIO_AOP_RVSS_BASE_ADDR_RMSK                                       0xffffffff
#define HWIO_AOP_RVSS_BASE_ADDR_IN                    \
                in_dword(HWIO_AOP_RVSS_BASE_ADDR_ADDR)
#define HWIO_AOP_RVSS_BASE_ADDR_INM(m)            \
                in_dword_masked(HWIO_AOP_RVSS_BASE_ADDR_ADDR, m)
#define HWIO_AOP_RVSS_BASE_ADDR_OUT(v)            \
                out_dword(HWIO_AOP_RVSS_BASE_ADDR_ADDR,v)
#define HWIO_AOP_RVSS_BASE_ADDR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_RVSS_BASE_ADDR_ADDR,m,v,HWIO_AOP_RVSS_BASE_ADDR_IN)
#define HWIO_AOP_RVSS_BASE_ADDR_RVSS_BASE_ADDR_BMSK                        0xffffffff
#define HWIO_AOP_RVSS_BASE_ADDR_RVSS_BASE_ADDR_SHFT                                 0

#define HWIO_AOP_RVSS_RESET_VECTOR_ADDR                                    (AOP_DEC_REG_BASE      + 0xb8)
#define HWIO_AOP_RVSS_RESET_VECTOR_PHYS                                    (AOP_DEC_REG_BASE_PHYS + 0xb8)
#define HWIO_AOP_RVSS_RESET_VECTOR_OFFS                                    (AOP_DEC_REG_BASE_OFFS + 0xb8)
#define HWIO_AOP_RVSS_RESET_VECTOR_RMSK                                    0xffffffff
#define HWIO_AOP_RVSS_RESET_VECTOR_IN                    \
                in_dword(HWIO_AOP_RVSS_RESET_VECTOR_ADDR)
#define HWIO_AOP_RVSS_RESET_VECTOR_INM(m)            \
                in_dword_masked(HWIO_AOP_RVSS_RESET_VECTOR_ADDR, m)
#define HWIO_AOP_RVSS_RESET_VECTOR_OUT(v)            \
                out_dword(HWIO_AOP_RVSS_RESET_VECTOR_ADDR,v)
#define HWIO_AOP_RVSS_RESET_VECTOR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_RVSS_RESET_VECTOR_ADDR,m,v,HWIO_AOP_RVSS_RESET_VECTOR_IN)
#define HWIO_AOP_RVSS_RESET_VECTOR_RVSS_RESET_VECTOR_BMSK                  0xffffffff
#define HWIO_AOP_RVSS_RESET_VECTOR_RVSS_RESET_VECTOR_SHFT                           0

#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_MASK_ADDR                          (AOP_DEC_REG_BASE      + 0xbc)
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_MASK_PHYS                          (AOP_DEC_REG_BASE_PHYS + 0xbc)
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_MASK_OFFS                          (AOP_DEC_REG_BASE_OFFS + 0xbc)
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_MASK_RMSK                                 0xf
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_MASK_IN                    \
                in_dword(HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_MASK_ADDR)
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_MASK_INM(m)            \
                in_dword_masked(HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_MASK_ADDR, m)
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_MASK_OUT(v)            \
                out_dword(HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_MASK_ADDR,v)
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_MASK_ADDR,m,v,HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_MASK_IN)
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_MASK_MASK_BMSK                            0xf
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_MASK_MASK_SHFT                              0

#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_VAL_ADDR                           (AOP_DEC_REG_BASE      + 0xc0)
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_VAL_PHYS                           (AOP_DEC_REG_BASE_PHYS + 0xc0)
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_VAL_OFFS                           (AOP_DEC_REG_BASE_OFFS + 0xc0)
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_VAL_RMSK                                  0xf
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_VAL_IN                    \
                in_dword(HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_VAL_ADDR)
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_VAL_INM(m)            \
                in_dword_masked(HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_VAL_ADDR, m)
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_VAL_OUT(v)            \
                out_dword(HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_VAL_ADDR,v)
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_VAL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_VAL_ADDR,m,v,HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_VAL_IN)
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_VAL_VAL_BMSK                              0xf
#define HWIO_AOP_RSCC_BR_EVENT_OVERRIDE_VAL_VAL_SHFT                                0

#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_MASK_ADDR                          (AOP_DEC_REG_BASE      + 0xc4)
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_MASK_PHYS                          (AOP_DEC_REG_BASE_PHYS + 0xc4)
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_MASK_OFFS                          (AOP_DEC_REG_BASE_OFFS + 0xc4)
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_MASK_RMSK                          0xffffffff
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_MASK_IN                    \
                in_dword(HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_MASK_ADDR)
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_MASK_INM(m)            \
                in_dword_masked(HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_MASK_ADDR, m)
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_MASK_OUT(v)            \
                out_dword(HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_MASK_ADDR,v)
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_MASK_ADDR,m,v,HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_MASK_IN)
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_MASK_MASK_BMSK                     0xffffffff
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_MASK_MASK_SHFT                              0

#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_VAL_ADDR                           (AOP_DEC_REG_BASE      + 0xc8)
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_VAL_PHYS                           (AOP_DEC_REG_BASE_PHYS + 0xc8)
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_VAL_OFFS                           (AOP_DEC_REG_BASE_OFFS + 0xc8)
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_VAL_RMSK                           0xffffffff
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_VAL_IN                    \
                in_dword(HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_VAL_ADDR)
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_VAL_INM(m)            \
                in_dword_masked(HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_VAL_ADDR, m)
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_VAL_OUT(v)            \
                out_dword(HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_VAL_ADDR,v)
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_VAL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_VAL_ADDR,m,v,HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_VAL_IN)
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_VAL_VAL_BMSK                       0xffffffff
#define HWIO_AOP_RSCC_PWR_CTRL_OVERRIDE_VAL_VAL_SHFT                                0

#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_MASK_ADDR                        (AOP_DEC_REG_BASE      + 0xcc)
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_MASK_PHYS                        (AOP_DEC_REG_BASE_PHYS + 0xcc)
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_MASK_OFFS                        (AOP_DEC_REG_BASE_OFFS + 0xcc)
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_MASK_RMSK                        0xffffffff
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_MASK_IN                    \
                in_dword(HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_MASK_ADDR)
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_MASK_INM(m)            \
                in_dword_masked(HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_MASK_ADDR, m)
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_MASK_OUT(v)            \
                out_dword(HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_MASK_ADDR,v)
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_MASK_ADDR,m,v,HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_MASK_IN)
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_MASK_MASK_BMSK                   0xffffffff
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_MASK_MASK_SHFT                            0

#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_VAL_ADDR                         (AOP_DEC_REG_BASE      + 0xd0)
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_VAL_PHYS                         (AOP_DEC_REG_BASE_PHYS + 0xd0)
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_VAL_OFFS                         (AOP_DEC_REG_BASE_OFFS + 0xd0)
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_VAL_RMSK                         0xffffffff
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_VAL_IN                    \
                in_dword(HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_VAL_ADDR)
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_VAL_INM(m)            \
                in_dword_masked(HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_VAL_ADDR, m)
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_VAL_OUT(v)            \
                out_dword(HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_VAL_ADDR,v)
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_VAL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_VAL_ADDR,m,v,HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_VAL_IN)
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_VAL_VAL_BMSK                     0xffffffff
#define HWIO_AOP_RSCC_WAIT_EVENT_OVERRIDE_VAL_VAL_SHFT                              0

#define HWIO_AOP_RVSS_FP_START_ADDR_ADDR                                   (AOP_DEC_REG_BASE      + 0xd4)
#define HWIO_AOP_RVSS_FP_START_ADDR_PHYS                                   (AOP_DEC_REG_BASE_PHYS + 0xd4)
#define HWIO_AOP_RVSS_FP_START_ADDR_OFFS                                   (AOP_DEC_REG_BASE_OFFS + 0xd4)
#define HWIO_AOP_RVSS_FP_START_ADDR_RMSK                                   0xffffffff
#define HWIO_AOP_RVSS_FP_START_ADDR_IN                    \
                in_dword(HWIO_AOP_RVSS_FP_START_ADDR_ADDR)
#define HWIO_AOP_RVSS_FP_START_ADDR_INM(m)            \
                in_dword_masked(HWIO_AOP_RVSS_FP_START_ADDR_ADDR, m)
#define HWIO_AOP_RVSS_FP_START_ADDR_OUT(v)            \
                out_dword(HWIO_AOP_RVSS_FP_START_ADDR_ADDR,v)
#define HWIO_AOP_RVSS_FP_START_ADDR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_RVSS_FP_START_ADDR_ADDR,m,v,HWIO_AOP_RVSS_FP_START_ADDR_IN)
#define HWIO_AOP_RVSS_FP_START_ADDR_FP_START_ADDR_BMSK                     0xffffffff
#define HWIO_AOP_RVSS_FP_START_ADDR_FP_START_ADDR_SHFT                              0

#define HWIO_AOP_RESET_REQUEST_EN_ADDR                                     (AOP_DEC_REG_BASE      + 0xd8)
#define HWIO_AOP_RESET_REQUEST_EN_PHYS                                     (AOP_DEC_REG_BASE_PHYS + 0xd8)
#define HWIO_AOP_RESET_REQUEST_EN_OFFS                                     (AOP_DEC_REG_BASE_OFFS + 0xd8)
#define HWIO_AOP_RESET_REQUEST_EN_RMSK                                            0xf
#define HWIO_AOP_RESET_REQUEST_EN_IN                    \
                in_dword(HWIO_AOP_RESET_REQUEST_EN_ADDR)
#define HWIO_AOP_RESET_REQUEST_EN_INM(m)            \
                in_dword_masked(HWIO_AOP_RESET_REQUEST_EN_ADDR, m)
#define HWIO_AOP_RESET_REQUEST_EN_OUT(v)            \
                out_dword(HWIO_AOP_RESET_REQUEST_EN_ADDR,v)
#define HWIO_AOP_RESET_REQUEST_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_RESET_REQUEST_EN_ADDR,m,v,HWIO_AOP_RESET_REQUEST_EN_IN)
#define HWIO_AOP_RESET_REQUEST_EN_SW_FORCE_RESET_REQ_BMSK                         0x8
#define HWIO_AOP_RESET_REQUEST_EN_SW_FORCE_RESET_REQ_SHFT                           3
#define HWIO_AOP_RESET_REQUEST_EN_DEBUG_NDRESET_EN_BMSK                           0x4
#define HWIO_AOP_RESET_REQUEST_EN_DEBUG_NDRESET_EN_SHFT                             2
#define HWIO_AOP_RESET_REQUEST_EN_STALL_EN_BMSK                                   0x2
#define HWIO_AOP_RESET_REQUEST_EN_STALL_EN_SHFT                                     1
#define HWIO_AOP_RESET_REQUEST_EN_HALT_EN_BMSK                                    0x1
#define HWIO_AOP_RESET_REQUEST_EN_HALT_EN_SHFT                                      0

#define HWIO_AOP_PROCESSOR_STATUS_ADDR                                     (AOP_DEC_REG_BASE      + 0xdc)
#define HWIO_AOP_PROCESSOR_STATUS_PHYS                                     (AOP_DEC_REG_BASE_PHYS + 0xdc)
#define HWIO_AOP_PROCESSOR_STATUS_OFFS                                     (AOP_DEC_REG_BASE_OFFS + 0xdc)
#define HWIO_AOP_PROCESSOR_STATUS_RMSK                                           0x1f
#define HWIO_AOP_PROCESSOR_STATUS_IN                    \
                in_dword(HWIO_AOP_PROCESSOR_STATUS_ADDR)
#define HWIO_AOP_PROCESSOR_STATUS_INM(m)            \
                in_dword_masked(HWIO_AOP_PROCESSOR_STATUS_ADDR, m)
#define HWIO_AOP_PROCESSOR_STATUS_PROC_SLEEPING_BMSK                             0x10
#define HWIO_AOP_PROCESSOR_STATUS_PROC_SLEEPING_SHFT                                4
#define HWIO_AOP_PROCESSOR_STATUS_PROC_WFI_BMSK                                   0x8
#define HWIO_AOP_PROCESSOR_STATUS_PROC_WFI_SHFT                                     3
#define HWIO_AOP_PROCESSOR_STATUS_PROC_CEASE_BMSK                                 0x4
#define HWIO_AOP_PROCESSOR_STATUS_PROC_CEASE_SHFT                                   2
#define HWIO_AOP_PROCESSOR_STATUS_PROC_STALL_BMSK                                 0x2
#define HWIO_AOP_PROCESSOR_STATUS_PROC_STALL_SHFT                                   1
#define HWIO_AOP_PROCESSOR_STATUS_PROC_HALT_BMSK                                  0x1
#define HWIO_AOP_PROCESSOR_STATUS_PROC_HALT_SHFT                                    0

#define HWIO_AOP_INTR_MASK_0_ADDR                                          (AOP_DEC_REG_BASE      + 0xe0)
#define HWIO_AOP_INTR_MASK_0_PHYS                                          (AOP_DEC_REG_BASE_PHYS + 0xe0)
#define HWIO_AOP_INTR_MASK_0_OFFS                                          (AOP_DEC_REG_BASE_OFFS + 0xe0)
#define HWIO_AOP_INTR_MASK_0_RMSK                                          0xffffffff
#define HWIO_AOP_INTR_MASK_0_IN                    \
                in_dword(HWIO_AOP_INTR_MASK_0_ADDR)
#define HWIO_AOP_INTR_MASK_0_INM(m)            \
                in_dword_masked(HWIO_AOP_INTR_MASK_0_ADDR, m)
#define HWIO_AOP_INTR_MASK_0_OUT(v)            \
                out_dword(HWIO_AOP_INTR_MASK_0_ADDR,v)
#define HWIO_AOP_INTR_MASK_0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_INTR_MASK_0_ADDR,m,v,HWIO_AOP_INTR_MASK_0_IN)
#define HWIO_AOP_INTR_MASK_0_INTERRUPT_MASK_BMSK                           0xffffffff
#define HWIO_AOP_INTR_MASK_0_INTERRUPT_MASK_SHFT                                    0

#define HWIO_AOP_INTR_MASK_1_ADDR                                          (AOP_DEC_REG_BASE      + 0xe4)
#define HWIO_AOP_INTR_MASK_1_PHYS                                          (AOP_DEC_REG_BASE_PHYS + 0xe4)
#define HWIO_AOP_INTR_MASK_1_OFFS                                          (AOP_DEC_REG_BASE_OFFS + 0xe4)
#define HWIO_AOP_INTR_MASK_1_RMSK                                          0xffffffff
#define HWIO_AOP_INTR_MASK_1_IN                    \
                in_dword(HWIO_AOP_INTR_MASK_1_ADDR)
#define HWIO_AOP_INTR_MASK_1_INM(m)            \
                in_dword_masked(HWIO_AOP_INTR_MASK_1_ADDR, m)
#define HWIO_AOP_INTR_MASK_1_OUT(v)            \
                out_dword(HWIO_AOP_INTR_MASK_1_ADDR,v)
#define HWIO_AOP_INTR_MASK_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_INTR_MASK_1_ADDR,m,v,HWIO_AOP_INTR_MASK_1_IN)
#define HWIO_AOP_INTR_MASK_1_INTERRUPT_MASK_BMSK                           0xffffffff
#define HWIO_AOP_INTR_MASK_1_INTERRUPT_MASK_SHFT                                    0

#define HWIO_AOP_INTR_MASK_2_ADDR                                          (AOP_DEC_REG_BASE      + 0xe8)
#define HWIO_AOP_INTR_MASK_2_PHYS                                          (AOP_DEC_REG_BASE_PHYS + 0xe8)
#define HWIO_AOP_INTR_MASK_2_OFFS                                          (AOP_DEC_REG_BASE_OFFS + 0xe8)
#define HWIO_AOP_INTR_MASK_2_RMSK                                          0xffffffff
#define HWIO_AOP_INTR_MASK_2_IN                    \
                in_dword(HWIO_AOP_INTR_MASK_2_ADDR)
#define HWIO_AOP_INTR_MASK_2_INM(m)            \
                in_dword_masked(HWIO_AOP_INTR_MASK_2_ADDR, m)
#define HWIO_AOP_INTR_MASK_2_OUT(v)            \
                out_dword(HWIO_AOP_INTR_MASK_2_ADDR,v)
#define HWIO_AOP_INTR_MASK_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_INTR_MASK_2_ADDR,m,v,HWIO_AOP_INTR_MASK_2_IN)
#define HWIO_AOP_INTR_MASK_2_INTERRUPT_MASK_BMSK                           0xffffffff
#define HWIO_AOP_INTR_MASK_2_INTERRUPT_MASK_SHFT                                    0

#define HWIO_AOP_INTR_MASK_3_ADDR                                          (AOP_DEC_REG_BASE      + 0xec)
#define HWIO_AOP_INTR_MASK_3_PHYS                                          (AOP_DEC_REG_BASE_PHYS + 0xec)
#define HWIO_AOP_INTR_MASK_3_OFFS                                          (AOP_DEC_REG_BASE_OFFS + 0xec)
#define HWIO_AOP_INTR_MASK_3_RMSK                                          0xffffffff
#define HWIO_AOP_INTR_MASK_3_IN                    \
                in_dword(HWIO_AOP_INTR_MASK_3_ADDR)
#define HWIO_AOP_INTR_MASK_3_INM(m)            \
                in_dword_masked(HWIO_AOP_INTR_MASK_3_ADDR, m)
#define HWIO_AOP_INTR_MASK_3_OUT(v)            \
                out_dword(HWIO_AOP_INTR_MASK_3_ADDR,v)
#define HWIO_AOP_INTR_MASK_3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_INTR_MASK_3_ADDR,m,v,HWIO_AOP_INTR_MASK_3_IN)
#define HWIO_AOP_INTR_MASK_3_INTERRUPT_MASK_BMSK                           0xffffffff
#define HWIO_AOP_INTR_MASK_3_INTERRUPT_MASK_SHFT                                    0

#define HWIO_AOP_INTR_SET_0_ADDR                                           (AOP_DEC_REG_BASE      + 0xf0)
#define HWIO_AOP_INTR_SET_0_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0xf0)
#define HWIO_AOP_INTR_SET_0_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0xf0)
#define HWIO_AOP_INTR_SET_0_RMSK                                           0xffffffff
#define HWIO_AOP_INTR_SET_0_OUT(v)            \
                out_dword(HWIO_AOP_INTR_SET_0_ADDR,v)
#define HWIO_AOP_INTR_SET_0_INT_SET_BMSK                                   0xffffffff
#define HWIO_AOP_INTR_SET_0_INT_SET_SHFT                                            0

#define HWIO_AOP_INTR_SET_1_ADDR                                           (AOP_DEC_REG_BASE      + 0xf4)
#define HWIO_AOP_INTR_SET_1_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0xf4)
#define HWIO_AOP_INTR_SET_1_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0xf4)
#define HWIO_AOP_INTR_SET_1_RMSK                                           0xffffffff
#define HWIO_AOP_INTR_SET_1_OUT(v)            \
                out_dword(HWIO_AOP_INTR_SET_1_ADDR,v)
#define HWIO_AOP_INTR_SET_1_INT_SET_BMSK                                   0xffffffff
#define HWIO_AOP_INTR_SET_1_INT_SET_SHFT                                            0

#define HWIO_AOP_INTR_SET_2_ADDR                                           (AOP_DEC_REG_BASE      + 0xf8)
#define HWIO_AOP_INTR_SET_2_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0xf8)
#define HWIO_AOP_INTR_SET_2_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0xf8)
#define HWIO_AOP_INTR_SET_2_RMSK                                           0xffffffff
#define HWIO_AOP_INTR_SET_2_OUT(v)            \
                out_dword(HWIO_AOP_INTR_SET_2_ADDR,v)
#define HWIO_AOP_INTR_SET_2_INT_SET_BMSK                                   0xffffffff
#define HWIO_AOP_INTR_SET_2_INT_SET_SHFT                                            0

#define HWIO_AOP_INTR_SET_3_ADDR                                           (AOP_DEC_REG_BASE      + 0xfc)
#define HWIO_AOP_INTR_SET_3_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0xfc)
#define HWIO_AOP_INTR_SET_3_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0xfc)
#define HWIO_AOP_INTR_SET_3_RMSK                                           0xffffffff
#define HWIO_AOP_INTR_SET_3_OUT(v)            \
                out_dword(HWIO_AOP_INTR_SET_3_ADDR,v)
#define HWIO_AOP_INTR_SET_3_INT_SET_BMSK                                   0xffffffff
#define HWIO_AOP_INTR_SET_3_INT_SET_SHFT                                            0

#define HWIO_AOP_INTR_CLR_0_ADDR                                           (AOP_DEC_REG_BASE      + 0x100)
#define HWIO_AOP_INTR_CLR_0_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0x100)
#define HWIO_AOP_INTR_CLR_0_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0x100)
#define HWIO_AOP_INTR_CLR_0_RMSK                                           0xffffffff
#define HWIO_AOP_INTR_CLR_0_OUT(v)            \
                out_dword(HWIO_AOP_INTR_CLR_0_ADDR,v)
#define HWIO_AOP_INTR_CLR_0_INT_CLR_BMSK                                   0xffffffff
#define HWIO_AOP_INTR_CLR_0_INT_CLR_SHFT                                            0

#define HWIO_AOP_INTR_CLR_1_ADDR                                           (AOP_DEC_REG_BASE      + 0x104)
#define HWIO_AOP_INTR_CLR_1_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0x104)
#define HWIO_AOP_INTR_CLR_1_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0x104)
#define HWIO_AOP_INTR_CLR_1_RMSK                                           0xffffffff
#define HWIO_AOP_INTR_CLR_1_OUT(v)            \
                out_dword(HWIO_AOP_INTR_CLR_1_ADDR,v)
#define HWIO_AOP_INTR_CLR_1_INT_CLR_BMSK                                   0xffffffff
#define HWIO_AOP_INTR_CLR_1_INT_CLR_SHFT                                            0

#define HWIO_AOP_INTR_CLR_2_ADDR                                           (AOP_DEC_REG_BASE      + 0x108)
#define HWIO_AOP_INTR_CLR_2_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0x108)
#define HWIO_AOP_INTR_CLR_2_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0x108)
#define HWIO_AOP_INTR_CLR_2_RMSK                                           0xffffffff
#define HWIO_AOP_INTR_CLR_2_OUT(v)            \
                out_dword(HWIO_AOP_INTR_CLR_2_ADDR,v)
#define HWIO_AOP_INTR_CLR_2_INT_CLR_BMSK                                   0xffffffff
#define HWIO_AOP_INTR_CLR_2_INT_CLR_SHFT                                            0

#define HWIO_AOP_INTR_CLR_3_ADDR                                           (AOP_DEC_REG_BASE      + 0x10c)
#define HWIO_AOP_INTR_CLR_3_PHYS                                           (AOP_DEC_REG_BASE_PHYS + 0x10c)
#define HWIO_AOP_INTR_CLR_3_OFFS                                           (AOP_DEC_REG_BASE_OFFS + 0x10c)
#define HWIO_AOP_INTR_CLR_3_RMSK                                           0xffffffff
#define HWIO_AOP_INTR_CLR_3_OUT(v)            \
                out_dword(HWIO_AOP_INTR_CLR_3_ADDR,v)
#define HWIO_AOP_INTR_CLR_3_INT_CLR_BMSK                                   0xffffffff
#define HWIO_AOP_INTR_CLR_3_INT_CLR_SHFT                                            0

#define HWIO_AOP_INTR_PEND_STATUS_0_ADDR                                   (AOP_DEC_REG_BASE      + 0x110)
#define HWIO_AOP_INTR_PEND_STATUS_0_PHYS                                   (AOP_DEC_REG_BASE_PHYS + 0x110)
#define HWIO_AOP_INTR_PEND_STATUS_0_OFFS                                   (AOP_DEC_REG_BASE_OFFS + 0x110)
#define HWIO_AOP_INTR_PEND_STATUS_0_RMSK                                   0xffffffff
#define HWIO_AOP_INTR_PEND_STATUS_0_IN                    \
                in_dword(HWIO_AOP_INTR_PEND_STATUS_0_ADDR)
#define HWIO_AOP_INTR_PEND_STATUS_0_INM(m)            \
                in_dword_masked(HWIO_AOP_INTR_PEND_STATUS_0_ADDR, m)
#define HWIO_AOP_INTR_PEND_STATUS_0_INTERRUPT_PENDING_STATUS_BMSK          0xffffffff
#define HWIO_AOP_INTR_PEND_STATUS_0_INTERRUPT_PENDING_STATUS_SHFT                   0

#define HWIO_AOP_INTR_PEND_STATUS_1_ADDR                                   (AOP_DEC_REG_BASE      + 0x114)
#define HWIO_AOP_INTR_PEND_STATUS_1_PHYS                                   (AOP_DEC_REG_BASE_PHYS + 0x114)
#define HWIO_AOP_INTR_PEND_STATUS_1_OFFS                                   (AOP_DEC_REG_BASE_OFFS + 0x114)
#define HWIO_AOP_INTR_PEND_STATUS_1_RMSK                                   0xffffffff
#define HWIO_AOP_INTR_PEND_STATUS_1_IN                    \
                in_dword(HWIO_AOP_INTR_PEND_STATUS_1_ADDR)
#define HWIO_AOP_INTR_PEND_STATUS_1_INM(m)            \
                in_dword_masked(HWIO_AOP_INTR_PEND_STATUS_1_ADDR, m)
#define HWIO_AOP_INTR_PEND_STATUS_1_INTERRUPT_PENDING_STATUS_BMSK          0xffffffff
#define HWIO_AOP_INTR_PEND_STATUS_1_INTERRUPT_PENDING_STATUS_SHFT                   0

#define HWIO_AOP_INTR_PEND_STATUS_2_ADDR                                   (AOP_DEC_REG_BASE      + 0x118)
#define HWIO_AOP_INTR_PEND_STATUS_2_PHYS                                   (AOP_DEC_REG_BASE_PHYS + 0x118)
#define HWIO_AOP_INTR_PEND_STATUS_2_OFFS                                   (AOP_DEC_REG_BASE_OFFS + 0x118)
#define HWIO_AOP_INTR_PEND_STATUS_2_RMSK                                   0xffffffff
#define HWIO_AOP_INTR_PEND_STATUS_2_IN                    \
                in_dword(HWIO_AOP_INTR_PEND_STATUS_2_ADDR)
#define HWIO_AOP_INTR_PEND_STATUS_2_INM(m)            \
                in_dword_masked(HWIO_AOP_INTR_PEND_STATUS_2_ADDR, m)
#define HWIO_AOP_INTR_PEND_STATUS_2_INTERRUPT_PENDING_STATUS_BMSK          0xffffffff
#define HWIO_AOP_INTR_PEND_STATUS_2_INTERRUPT_PENDING_STATUS_SHFT                   0

#define HWIO_AOP_INTR_PEND_STATUS_3_ADDR                                   (AOP_DEC_REG_BASE      + 0x11c)
#define HWIO_AOP_INTR_PEND_STATUS_3_PHYS                                   (AOP_DEC_REG_BASE_PHYS + 0x11c)
#define HWIO_AOP_INTR_PEND_STATUS_3_OFFS                                   (AOP_DEC_REG_BASE_OFFS + 0x11c)
#define HWIO_AOP_INTR_PEND_STATUS_3_RMSK                                   0xffffffff
#define HWIO_AOP_INTR_PEND_STATUS_3_IN                    \
                in_dword(HWIO_AOP_INTR_PEND_STATUS_3_ADDR)
#define HWIO_AOP_INTR_PEND_STATUS_3_INM(m)            \
                in_dword_masked(HWIO_AOP_INTR_PEND_STATUS_3_ADDR, m)
#define HWIO_AOP_INTR_PEND_STATUS_3_INTERRUPT_PENDING_STATUS_BMSK          0xffffffff
#define HWIO_AOP_INTR_PEND_STATUS_3_INTERRUPT_PENDING_STATUS_SHFT                   0

/*----------------------------------------------------------------------------
 * MODULE: AOP_F0_QTMR_V1_F0
 *--------------------------------------------------------------------------*/

#define AOP_F0_QTMR_V1_F0_REG_BASE                                  (AOSS_BASE      + 0x000a0000)
#define AOP_F0_QTMR_V1_F0_REG_BASE_SIZE                             0x1000
#define AOP_F0_QTMR_V1_F0_REG_BASE_USED                             0xfd0
#define AOP_F0_QTMR_V1_F0_REG_BASE_PHYS                             (AOSS_BASE_PHYS + 0x000a0000)
#define AOP_F0_QTMR_V1_F0_REG_BASE_OFFS                             0x000a0000

#define HWIO_AOP_F0_QTMR_V1_CNTPCT_LO_ADDR                          (AOP_F0_QTMR_V1_F0_REG_BASE      + 0x0)
#define HWIO_AOP_F0_QTMR_V1_CNTPCT_LO_PHYS                          (AOP_F0_QTMR_V1_F0_REG_BASE_PHYS + 0x0)
#define HWIO_AOP_F0_QTMR_V1_CNTPCT_LO_OFFS                          (AOP_F0_QTMR_V1_F0_REG_BASE_OFFS + 0x0)
#define HWIO_AOP_F0_QTMR_V1_CNTPCT_LO_RMSK                          0xffffffff
#define HWIO_AOP_F0_QTMR_V1_CNTPCT_LO_IN                    \
                in_dword(HWIO_AOP_F0_QTMR_V1_CNTPCT_LO_ADDR)
#define HWIO_AOP_F0_QTMR_V1_CNTPCT_LO_INM(m)            \
                in_dword_masked(HWIO_AOP_F0_QTMR_V1_CNTPCT_LO_ADDR, m)
#define HWIO_AOP_F0_QTMR_V1_CNTPCT_LO_CNTPCT_LO_BMSK                0xffffffff
#define HWIO_AOP_F0_QTMR_V1_CNTPCT_LO_CNTPCT_LO_SHFT                         0

#define HWIO_AOP_F0_QTMR_V1_CNTPCT_HI_ADDR                          (AOP_F0_QTMR_V1_F0_REG_BASE      + 0x4)
#define HWIO_AOP_F0_QTMR_V1_CNTPCT_HI_PHYS                          (AOP_F0_QTMR_V1_F0_REG_BASE_PHYS + 0x4)
#define HWIO_AOP_F0_QTMR_V1_CNTPCT_HI_OFFS                          (AOP_F0_QTMR_V1_F0_REG_BASE_OFFS + 0x4)
#define HWIO_AOP_F0_QTMR_V1_CNTPCT_HI_RMSK                            0xffffff
#define HWIO_AOP_F0_QTMR_V1_CNTPCT_HI_IN                    \
                in_dword(HWIO_AOP_F0_QTMR_V1_CNTPCT_HI_ADDR)
#define HWIO_AOP_F0_QTMR_V1_CNTPCT_HI_INM(m)            \
                in_dword_masked(HWIO_AOP_F0_QTMR_V1_CNTPCT_HI_ADDR, m)
#define HWIO_AOP_F0_QTMR_V1_CNTPCT_HI_CNTPCT_HI_BMSK                  0xffffff
#define HWIO_AOP_F0_QTMR_V1_CNTPCT_HI_CNTPCT_HI_SHFT                         0

#define HWIO_AOP_F0_QTMR_V1_CNTVCT_LO_ADDR                          (AOP_F0_QTMR_V1_F0_REG_BASE      + 0x8)
#define HWIO_AOP_F0_QTMR_V1_CNTVCT_LO_PHYS                          (AOP_F0_QTMR_V1_F0_REG_BASE_PHYS + 0x8)
#define HWIO_AOP_F0_QTMR_V1_CNTVCT_LO_OFFS                          (AOP_F0_QTMR_V1_F0_REG_BASE_OFFS + 0x8)
#define HWIO_AOP_F0_QTMR_V1_CNTVCT_LO_RMSK                          0xffffffff
#define HWIO_AOP_F0_QTMR_V1_CNTVCT_LO_IN                    \
                in_dword(HWIO_AOP_F0_QTMR_V1_CNTVCT_LO_ADDR)
#define HWIO_AOP_F0_QTMR_V1_CNTVCT_LO_INM(m)            \
                in_dword_masked(HWIO_AOP_F0_QTMR_V1_CNTVCT_LO_ADDR, m)
#define HWIO_AOP_F0_QTMR_V1_CNTVCT_LO_CNTVCT_LO_BMSK                0xffffffff
#define HWIO_AOP_F0_QTMR_V1_CNTVCT_LO_CNTVCT_LO_SHFT                         0

#define HWIO_AOP_F0_QTMR_V1_CNTVCT_HI_ADDR                          (AOP_F0_QTMR_V1_F0_REG_BASE      + 0xc)
#define HWIO_AOP_F0_QTMR_V1_CNTVCT_HI_PHYS                          (AOP_F0_QTMR_V1_F0_REG_BASE_PHYS + 0xc)
#define HWIO_AOP_F0_QTMR_V1_CNTVCT_HI_OFFS                          (AOP_F0_QTMR_V1_F0_REG_BASE_OFFS + 0xc)
#define HWIO_AOP_F0_QTMR_V1_CNTVCT_HI_RMSK                            0xffffff
#define HWIO_AOP_F0_QTMR_V1_CNTVCT_HI_IN                    \
                in_dword(HWIO_AOP_F0_QTMR_V1_CNTVCT_HI_ADDR)
#define HWIO_AOP_F0_QTMR_V1_CNTVCT_HI_INM(m)            \
                in_dword_masked(HWIO_AOP_F0_QTMR_V1_CNTVCT_HI_ADDR, m)
#define HWIO_AOP_F0_QTMR_V1_CNTVCT_HI_CNTVCT_HI_BMSK                  0xffffff
#define HWIO_AOP_F0_QTMR_V1_CNTVCT_HI_CNTVCT_HI_SHFT                         0

#define HWIO_AOP_F0_QTMR_V1_CNTFRQ_ADDR                             (AOP_F0_QTMR_V1_F0_REG_BASE      + 0x10)
#define HWIO_AOP_F0_QTMR_V1_CNTFRQ_PHYS                             (AOP_F0_QTMR_V1_F0_REG_BASE_PHYS + 0x10)
#define HWIO_AOP_F0_QTMR_V1_CNTFRQ_OFFS                             (AOP_F0_QTMR_V1_F0_REG_BASE_OFFS + 0x10)
#define HWIO_AOP_F0_QTMR_V1_CNTFRQ_RMSK                             0xffffffff
#define HWIO_AOP_F0_QTMR_V1_CNTFRQ_IN                    \
                in_dword(HWIO_AOP_F0_QTMR_V1_CNTFRQ_ADDR)
#define HWIO_AOP_F0_QTMR_V1_CNTFRQ_INM(m)            \
                in_dword_masked(HWIO_AOP_F0_QTMR_V1_CNTFRQ_ADDR, m)
#define HWIO_AOP_F0_QTMR_V1_CNTFRQ_CNTFRQ_BMSK                      0xffffffff
#define HWIO_AOP_F0_QTMR_V1_CNTFRQ_CNTFRQ_SHFT                               0

#define HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_ADDR                          (AOP_F0_QTMR_V1_F0_REG_BASE      + 0x14)
#define HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_PHYS                          (AOP_F0_QTMR_V1_F0_REG_BASE_PHYS + 0x14)
#define HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_OFFS                          (AOP_F0_QTMR_V1_F0_REG_BASE_OFFS + 0x14)
#define HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_RMSK                               0x303
#define HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_IN                    \
                in_dword(HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_ADDR)
#define HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_INM(m)            \
                in_dword_masked(HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_ADDR, m)
#define HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_OUT(v)            \
                out_dword(HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_ADDR,v)
#define HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_ADDR,m,v,HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_IN)
#define HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_PL0CTEN_BMSK                       0x200
#define HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_PL0CTEN_SHFT                           9
#define HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_PL0VTEN_BMSK                       0x100
#define HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_PL0VTEN_SHFT                           8
#define HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_PL0VCTEN_BMSK                        0x2
#define HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_PL0VCTEN_SHFT                          1
#define HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_PL0PCTEN_BMSK                        0x1
#define HWIO_AOP_F0_QTMR_V1_CNTPL0ACR_PL0PCTEN_SHFT                          0

#define HWIO_AOP_F0_QTMR_V1_CNTVOFF_LO_ADDR                         (AOP_F0_QTMR_V1_F0_REG_BASE      + 0x18)
#define HWIO_AOP_F0_QTMR_V1_CNTVOFF_LO_PHYS                         (AOP_F0_QTMR_V1_F0_REG_BASE_PHYS + 0x18)
#define HWIO_AOP_F0_QTMR_V1_CNTVOFF_LO_OFFS                         (AOP_F0_QTMR_V1_F0_REG_BASE_OFFS + 0x18)
#define HWIO_AOP_F0_QTMR_V1_CNTVOFF_LO_RMSK                         0xffffffff
#define HWIO_AOP_F0_QTMR_V1_CNTVOFF_LO_IN                    \
                in_dword(HWIO_AOP_F0_QTMR_V1_CNTVOFF_LO_ADDR)
#define HWIO_AOP_F0_QTMR_V1_CNTVOFF_LO_INM(m)            \
                in_dword_masked(HWIO_AOP_F0_QTMR_V1_CNTVOFF_LO_ADDR, m)
#define HWIO_AOP_F0_QTMR_V1_CNTVOFF_LO_CNTVOFF_L0_BMSK              0xffffffff
#define HWIO_AOP_F0_QTMR_V1_CNTVOFF_LO_CNTVOFF_L0_SHFT                       0

#define HWIO_AOP_F0_QTMR_V1_CNTVOFF_HI_ADDR                         (AOP_F0_QTMR_V1_F0_REG_BASE      + 0x1c)
#define HWIO_AOP_F0_QTMR_V1_CNTVOFF_HI_PHYS                         (AOP_F0_QTMR_V1_F0_REG_BASE_PHYS + 0x1c)
#define HWIO_AOP_F0_QTMR_V1_CNTVOFF_HI_OFFS                         (AOP_F0_QTMR_V1_F0_REG_BASE_OFFS + 0x1c)
#define HWIO_AOP_F0_QTMR_V1_CNTVOFF_HI_RMSK                           0xffffff
#define HWIO_AOP_F0_QTMR_V1_CNTVOFF_HI_IN                    \
                in_dword(HWIO_AOP_F0_QTMR_V1_CNTVOFF_HI_ADDR)
#define HWIO_AOP_F0_QTMR_V1_CNTVOFF_HI_INM(m)            \
                in_dword_masked(HWIO_AOP_F0_QTMR_V1_CNTVOFF_HI_ADDR, m)
#define HWIO_AOP_F0_QTMR_V1_CNTVOFF_HI_CNTVOFF_HI_BMSK                0xffffff
#define HWIO_AOP_F0_QTMR_V1_CNTVOFF_HI_CNTVOFF_HI_SHFT                       0

#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_LO_ADDR                       (AOP_F0_QTMR_V1_F0_REG_BASE      + 0x20)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_LO_PHYS                       (AOP_F0_QTMR_V1_F0_REG_BASE_PHYS + 0x20)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_LO_OFFS                       (AOP_F0_QTMR_V1_F0_REG_BASE_OFFS + 0x20)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_LO_RMSK                       0xffffffff
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_LO_IN                    \
                in_dword(HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_LO_ADDR)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_LO_INM(m)            \
                in_dword_masked(HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_LO_ADDR, m)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_LO_OUT(v)            \
                out_dword(HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_LO_ADDR,v)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_LO_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_LO_ADDR,m,v,HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_LO_IN)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_LO_CNTP_CVAL_L0_BMSK          0xffffffff
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_LO_CNTP_CVAL_L0_SHFT                   0

#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_HI_ADDR                       (AOP_F0_QTMR_V1_F0_REG_BASE      + 0x24)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_HI_PHYS                       (AOP_F0_QTMR_V1_F0_REG_BASE_PHYS + 0x24)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_HI_OFFS                       (AOP_F0_QTMR_V1_F0_REG_BASE_OFFS + 0x24)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_HI_RMSK                         0xffffff
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_HI_IN                    \
                in_dword(HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_HI_ADDR)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_HI_INM(m)            \
                in_dword_masked(HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_HI_ADDR, m)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_HI_OUT(v)            \
                out_dword(HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_HI_ADDR,v)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_HI_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_HI_ADDR,m,v,HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_HI_IN)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_HI_CNTP_CVAL_HI_BMSK            0xffffff
#define HWIO_AOP_F0_QTMR_V1_CNTP_CVAL_HI_CNTP_CVAL_HI_SHFT                   0

#define HWIO_AOP_F0_QTMR_V1_CNTP_TVAL_ADDR                          (AOP_F0_QTMR_V1_F0_REG_BASE      + 0x28)
#define HWIO_AOP_F0_QTMR_V1_CNTP_TVAL_PHYS                          (AOP_F0_QTMR_V1_F0_REG_BASE_PHYS + 0x28)
#define HWIO_AOP_F0_QTMR_V1_CNTP_TVAL_OFFS                          (AOP_F0_QTMR_V1_F0_REG_BASE_OFFS + 0x28)
#define HWIO_AOP_F0_QTMR_V1_CNTP_TVAL_RMSK                          0xffffffff
#define HWIO_AOP_F0_QTMR_V1_CNTP_TVAL_IN                    \
                in_dword(HWIO_AOP_F0_QTMR_V1_CNTP_TVAL_ADDR)
#define HWIO_AOP_F0_QTMR_V1_CNTP_TVAL_INM(m)            \
                in_dword_masked(HWIO_AOP_F0_QTMR_V1_CNTP_TVAL_ADDR, m)
#define HWIO_AOP_F0_QTMR_V1_CNTP_TVAL_OUT(v)            \
                out_dword(HWIO_AOP_F0_QTMR_V1_CNTP_TVAL_ADDR,v)
#define HWIO_AOP_F0_QTMR_V1_CNTP_TVAL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F0_QTMR_V1_CNTP_TVAL_ADDR,m,v,HWIO_AOP_F0_QTMR_V1_CNTP_TVAL_IN)
#define HWIO_AOP_F0_QTMR_V1_CNTP_TVAL_CNTP_TVAL_BMSK                0xffffffff
#define HWIO_AOP_F0_QTMR_V1_CNTP_TVAL_CNTP_TVAL_SHFT                         0

#define HWIO_AOP_F0_QTMR_V1_CNTP_CTL_ADDR                           (AOP_F0_QTMR_V1_F0_REG_BASE      + 0x2c)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CTL_PHYS                           (AOP_F0_QTMR_V1_F0_REG_BASE_PHYS + 0x2c)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CTL_OFFS                           (AOP_F0_QTMR_V1_F0_REG_BASE_OFFS + 0x2c)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CTL_RMSK                                  0x7
#define HWIO_AOP_F0_QTMR_V1_CNTP_CTL_IN                    \
                in_dword(HWIO_AOP_F0_QTMR_V1_CNTP_CTL_ADDR)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CTL_INM(m)            \
                in_dword_masked(HWIO_AOP_F0_QTMR_V1_CNTP_CTL_ADDR, m)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CTL_OUT(v)            \
                out_dword(HWIO_AOP_F0_QTMR_V1_CNTP_CTL_ADDR,v)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CTL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F0_QTMR_V1_CNTP_CTL_ADDR,m,v,HWIO_AOP_F0_QTMR_V1_CNTP_CTL_IN)
#define HWIO_AOP_F0_QTMR_V1_CNTP_CTL_ISTAT_BMSK                            0x4
#define HWIO_AOP_F0_QTMR_V1_CNTP_CTL_ISTAT_SHFT                              2
#define HWIO_AOP_F0_QTMR_V1_CNTP_CTL_IMSK_BMSK                             0x2
#define HWIO_AOP_F0_QTMR_V1_CNTP_CTL_IMSK_SHFT                               1
#define HWIO_AOP_F0_QTMR_V1_CNTP_CTL_EN_BMSK                               0x1
#define HWIO_AOP_F0_QTMR_V1_CNTP_CTL_EN_SHFT                                 0

#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_LO_ADDR                       (AOP_F0_QTMR_V1_F0_REG_BASE      + 0x30)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_LO_PHYS                       (AOP_F0_QTMR_V1_F0_REG_BASE_PHYS + 0x30)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_LO_OFFS                       (AOP_F0_QTMR_V1_F0_REG_BASE_OFFS + 0x30)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_LO_RMSK                       0xffffffff
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_LO_IN                    \
                in_dword(HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_LO_ADDR)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_LO_INM(m)            \
                in_dword_masked(HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_LO_ADDR, m)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_LO_OUT(v)            \
                out_dword(HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_LO_ADDR,v)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_LO_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_LO_ADDR,m,v,HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_LO_IN)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_LO_CNTV_CVAL_L0_BMSK          0xffffffff
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_LO_CNTV_CVAL_L0_SHFT                   0

#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_HI_ADDR                       (AOP_F0_QTMR_V1_F0_REG_BASE      + 0x34)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_HI_PHYS                       (AOP_F0_QTMR_V1_F0_REG_BASE_PHYS + 0x34)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_HI_OFFS                       (AOP_F0_QTMR_V1_F0_REG_BASE_OFFS + 0x34)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_HI_RMSK                         0xffffff
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_HI_IN                    \
                in_dword(HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_HI_ADDR)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_HI_INM(m)            \
                in_dword_masked(HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_HI_ADDR, m)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_HI_OUT(v)            \
                out_dword(HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_HI_ADDR,v)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_HI_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_HI_ADDR,m,v,HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_HI_IN)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_HI_CNTV_CVAL_HI_BMSK            0xffffff
#define HWIO_AOP_F0_QTMR_V1_CNTV_CVAL_HI_CNTV_CVAL_HI_SHFT                   0

#define HWIO_AOP_F0_QTMR_V1_CNTV_TVAL_ADDR                          (AOP_F0_QTMR_V1_F0_REG_BASE      + 0x38)
#define HWIO_AOP_F0_QTMR_V1_CNTV_TVAL_PHYS                          (AOP_F0_QTMR_V1_F0_REG_BASE_PHYS + 0x38)
#define HWIO_AOP_F0_QTMR_V1_CNTV_TVAL_OFFS                          (AOP_F0_QTMR_V1_F0_REG_BASE_OFFS + 0x38)
#define HWIO_AOP_F0_QTMR_V1_CNTV_TVAL_RMSK                          0xffffffff
#define HWIO_AOP_F0_QTMR_V1_CNTV_TVAL_IN                    \
                in_dword(HWIO_AOP_F0_QTMR_V1_CNTV_TVAL_ADDR)
#define HWIO_AOP_F0_QTMR_V1_CNTV_TVAL_INM(m)            \
                in_dword_masked(HWIO_AOP_F0_QTMR_V1_CNTV_TVAL_ADDR, m)
#define HWIO_AOP_F0_QTMR_V1_CNTV_TVAL_OUT(v)            \
                out_dword(HWIO_AOP_F0_QTMR_V1_CNTV_TVAL_ADDR,v)
#define HWIO_AOP_F0_QTMR_V1_CNTV_TVAL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F0_QTMR_V1_CNTV_TVAL_ADDR,m,v,HWIO_AOP_F0_QTMR_V1_CNTV_TVAL_IN)
#define HWIO_AOP_F0_QTMR_V1_CNTV_TVAL_CNTV_TVAL_BMSK                0xffffffff
#define HWIO_AOP_F0_QTMR_V1_CNTV_TVAL_CNTV_TVAL_SHFT                         0

#define HWIO_AOP_F0_QTMR_V1_CNTV_CTL_ADDR                           (AOP_F0_QTMR_V1_F0_REG_BASE      + 0x3c)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CTL_PHYS                           (AOP_F0_QTMR_V1_F0_REG_BASE_PHYS + 0x3c)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CTL_OFFS                           (AOP_F0_QTMR_V1_F0_REG_BASE_OFFS + 0x3c)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CTL_RMSK                                  0x7
#define HWIO_AOP_F0_QTMR_V1_CNTV_CTL_IN                    \
                in_dword(HWIO_AOP_F0_QTMR_V1_CNTV_CTL_ADDR)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CTL_INM(m)            \
                in_dword_masked(HWIO_AOP_F0_QTMR_V1_CNTV_CTL_ADDR, m)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CTL_OUT(v)            \
                out_dword(HWIO_AOP_F0_QTMR_V1_CNTV_CTL_ADDR,v)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CTL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F0_QTMR_V1_CNTV_CTL_ADDR,m,v,HWIO_AOP_F0_QTMR_V1_CNTV_CTL_IN)
#define HWIO_AOP_F0_QTMR_V1_CNTV_CTL_ISTAT_BMSK                            0x4
#define HWIO_AOP_F0_QTMR_V1_CNTV_CTL_ISTAT_SHFT                              2
#define HWIO_AOP_F0_QTMR_V1_CNTV_CTL_IMSK_BMSK                             0x2
#define HWIO_AOP_F0_QTMR_V1_CNTV_CTL_IMSK_SHFT                               1
#define HWIO_AOP_F0_QTMR_V1_CNTV_CTL_EN_BMSK                               0x1
#define HWIO_AOP_F0_QTMR_V1_CNTV_CTL_EN_SHFT                                 0

#define HWIO_AOP_F0_QTMR_V1_VERSION_ADDR                            (AOP_F0_QTMR_V1_F0_REG_BASE      + 0xfd0)
#define HWIO_AOP_F0_QTMR_V1_VERSION_PHYS                            (AOP_F0_QTMR_V1_F0_REG_BASE_PHYS + 0xfd0)
#define HWIO_AOP_F0_QTMR_V1_VERSION_OFFS                            (AOP_F0_QTMR_V1_F0_REG_BASE_OFFS + 0xfd0)
#define HWIO_AOP_F0_QTMR_V1_VERSION_RMSK                            0xffffffff
#define HWIO_AOP_F0_QTMR_V1_VERSION_IN                    \
                in_dword(HWIO_AOP_F0_QTMR_V1_VERSION_ADDR)
#define HWIO_AOP_F0_QTMR_V1_VERSION_INM(m)            \
                in_dword_masked(HWIO_AOP_F0_QTMR_V1_VERSION_ADDR, m)
#define HWIO_AOP_F0_QTMR_V1_VERSION_MAJOR_BMSK                      0xf0000000
#define HWIO_AOP_F0_QTMR_V1_VERSION_MAJOR_SHFT                              28
#define HWIO_AOP_F0_QTMR_V1_VERSION_MINOR_BMSK                       0xfff0000
#define HWIO_AOP_F0_QTMR_V1_VERSION_MINOR_SHFT                              16
#define HWIO_AOP_F0_QTMR_V1_VERSION_STEP_BMSK                           0xffff
#define HWIO_AOP_F0_QTMR_V1_VERSION_STEP_SHFT                                0

/*----------------------------------------------------------------------------
 * MODULE: AOP_F1_QTMR_V1_F1
 *--------------------------------------------------------------------------*/

#define AOP_F1_QTMR_V1_F1_REG_BASE                                  (AOSS_BASE      + 0x000b0000)
#define AOP_F1_QTMR_V1_F1_REG_BASE_SIZE                             0x1000
#define AOP_F1_QTMR_V1_F1_REG_BASE_USED                             0xfd0
#define AOP_F1_QTMR_V1_F1_REG_BASE_PHYS                             (AOSS_BASE_PHYS + 0x000b0000)
#define AOP_F1_QTMR_V1_F1_REG_BASE_OFFS                             0x000b0000

#define HWIO_AOP_F1_QTMR_V1_CNTPCT_LO_ADDR                          (AOP_F1_QTMR_V1_F1_REG_BASE      + 0x0)
#define HWIO_AOP_F1_QTMR_V1_CNTPCT_LO_PHYS                          (AOP_F1_QTMR_V1_F1_REG_BASE_PHYS + 0x0)
#define HWIO_AOP_F1_QTMR_V1_CNTPCT_LO_OFFS                          (AOP_F1_QTMR_V1_F1_REG_BASE_OFFS + 0x0)
#define HWIO_AOP_F1_QTMR_V1_CNTPCT_LO_RMSK                          0xffffffff
#define HWIO_AOP_F1_QTMR_V1_CNTPCT_LO_IN                    \
                in_dword(HWIO_AOP_F1_QTMR_V1_CNTPCT_LO_ADDR)
#define HWIO_AOP_F1_QTMR_V1_CNTPCT_LO_INM(m)            \
                in_dword_masked(HWIO_AOP_F1_QTMR_V1_CNTPCT_LO_ADDR, m)
#define HWIO_AOP_F1_QTMR_V1_CNTPCT_LO_CNTPCT_LO_BMSK                0xffffffff
#define HWIO_AOP_F1_QTMR_V1_CNTPCT_LO_CNTPCT_LO_SHFT                         0

#define HWIO_AOP_F1_QTMR_V1_CNTPCT_HI_ADDR                          (AOP_F1_QTMR_V1_F1_REG_BASE      + 0x4)
#define HWIO_AOP_F1_QTMR_V1_CNTPCT_HI_PHYS                          (AOP_F1_QTMR_V1_F1_REG_BASE_PHYS + 0x4)
#define HWIO_AOP_F1_QTMR_V1_CNTPCT_HI_OFFS                          (AOP_F1_QTMR_V1_F1_REG_BASE_OFFS + 0x4)
#define HWIO_AOP_F1_QTMR_V1_CNTPCT_HI_RMSK                            0xffffff
#define HWIO_AOP_F1_QTMR_V1_CNTPCT_HI_IN                    \
                in_dword(HWIO_AOP_F1_QTMR_V1_CNTPCT_HI_ADDR)
#define HWIO_AOP_F1_QTMR_V1_CNTPCT_HI_INM(m)            \
                in_dword_masked(HWIO_AOP_F1_QTMR_V1_CNTPCT_HI_ADDR, m)
#define HWIO_AOP_F1_QTMR_V1_CNTPCT_HI_CNTPCT_HI_BMSK                  0xffffff
#define HWIO_AOP_F1_QTMR_V1_CNTPCT_HI_CNTPCT_HI_SHFT                         0

#define HWIO_AOP_F1_QTMR_V1_CNTVCT_LO_ADDR                          (AOP_F1_QTMR_V1_F1_REG_BASE      + 0x8)
#define HWIO_AOP_F1_QTMR_V1_CNTVCT_LO_PHYS                          (AOP_F1_QTMR_V1_F1_REG_BASE_PHYS + 0x8)
#define HWIO_AOP_F1_QTMR_V1_CNTVCT_LO_OFFS                          (AOP_F1_QTMR_V1_F1_REG_BASE_OFFS + 0x8)
#define HWIO_AOP_F1_QTMR_V1_CNTVCT_LO_RMSK                          0xffffffff
#define HWIO_AOP_F1_QTMR_V1_CNTVCT_LO_IN                    \
                in_dword(HWIO_AOP_F1_QTMR_V1_CNTVCT_LO_ADDR)
#define HWIO_AOP_F1_QTMR_V1_CNTVCT_LO_INM(m)            \
                in_dword_masked(HWIO_AOP_F1_QTMR_V1_CNTVCT_LO_ADDR, m)
#define HWIO_AOP_F1_QTMR_V1_CNTVCT_LO_CNTVCT_LO_BMSK                0xffffffff
#define HWIO_AOP_F1_QTMR_V1_CNTVCT_LO_CNTVCT_LO_SHFT                         0

#define HWIO_AOP_F1_QTMR_V1_CNTVCT_HI_ADDR                          (AOP_F1_QTMR_V1_F1_REG_BASE      + 0xc)
#define HWIO_AOP_F1_QTMR_V1_CNTVCT_HI_PHYS                          (AOP_F1_QTMR_V1_F1_REG_BASE_PHYS + 0xc)
#define HWIO_AOP_F1_QTMR_V1_CNTVCT_HI_OFFS                          (AOP_F1_QTMR_V1_F1_REG_BASE_OFFS + 0xc)
#define HWIO_AOP_F1_QTMR_V1_CNTVCT_HI_RMSK                            0xffffff
#define HWIO_AOP_F1_QTMR_V1_CNTVCT_HI_IN                    \
                in_dword(HWIO_AOP_F1_QTMR_V1_CNTVCT_HI_ADDR)
#define HWIO_AOP_F1_QTMR_V1_CNTVCT_HI_INM(m)            \
                in_dword_masked(HWIO_AOP_F1_QTMR_V1_CNTVCT_HI_ADDR, m)
#define HWIO_AOP_F1_QTMR_V1_CNTVCT_HI_CNTVCT_HI_BMSK                  0xffffff
#define HWIO_AOP_F1_QTMR_V1_CNTVCT_HI_CNTVCT_HI_SHFT                         0

#define HWIO_AOP_F1_QTMR_V1_CNTFRQ_ADDR                             (AOP_F1_QTMR_V1_F1_REG_BASE      + 0x10)
#define HWIO_AOP_F1_QTMR_V1_CNTFRQ_PHYS                             (AOP_F1_QTMR_V1_F1_REG_BASE_PHYS + 0x10)
#define HWIO_AOP_F1_QTMR_V1_CNTFRQ_OFFS                             (AOP_F1_QTMR_V1_F1_REG_BASE_OFFS + 0x10)
#define HWIO_AOP_F1_QTMR_V1_CNTFRQ_RMSK                             0xffffffff
#define HWIO_AOP_F1_QTMR_V1_CNTFRQ_IN                    \
                in_dword(HWIO_AOP_F1_QTMR_V1_CNTFRQ_ADDR)
#define HWIO_AOP_F1_QTMR_V1_CNTFRQ_INM(m)            \
                in_dword_masked(HWIO_AOP_F1_QTMR_V1_CNTFRQ_ADDR, m)
#define HWIO_AOP_F1_QTMR_V1_CNTFRQ_CNTFRQ_BMSK                      0xffffffff
#define HWIO_AOP_F1_QTMR_V1_CNTFRQ_CNTFRQ_SHFT                               0

#define HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_ADDR                          (AOP_F1_QTMR_V1_F1_REG_BASE      + 0x14)
#define HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_PHYS                          (AOP_F1_QTMR_V1_F1_REG_BASE_PHYS + 0x14)
#define HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_OFFS                          (AOP_F1_QTMR_V1_F1_REG_BASE_OFFS + 0x14)
#define HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_RMSK                               0x303
#define HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_IN                    \
                in_dword(HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_ADDR)
#define HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_INM(m)            \
                in_dword_masked(HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_ADDR, m)
#define HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_OUT(v)            \
                out_dword(HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_ADDR,v)
#define HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_ADDR,m,v,HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_IN)
#define HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_PL0CTEN_BMSK                       0x200
#define HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_PL0CTEN_SHFT                           9
#define HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_PL0VTEN_BMSK                       0x100
#define HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_PL0VTEN_SHFT                           8
#define HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_PL0VCTEN_BMSK                        0x2
#define HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_PL0VCTEN_SHFT                          1
#define HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_PL0PCTEN_BMSK                        0x1
#define HWIO_AOP_F1_QTMR_V1_CNTPL0ACR_PL0PCTEN_SHFT                          0

#define HWIO_AOP_F1_QTMR_V1_CNTVOFF_LO_ADDR                         (AOP_F1_QTMR_V1_F1_REG_BASE      + 0x18)
#define HWIO_AOP_F1_QTMR_V1_CNTVOFF_LO_PHYS                         (AOP_F1_QTMR_V1_F1_REG_BASE_PHYS + 0x18)
#define HWIO_AOP_F1_QTMR_V1_CNTVOFF_LO_OFFS                         (AOP_F1_QTMR_V1_F1_REG_BASE_OFFS + 0x18)
#define HWIO_AOP_F1_QTMR_V1_CNTVOFF_LO_RMSK                         0xffffffff
#define HWIO_AOP_F1_QTMR_V1_CNTVOFF_LO_IN                    \
                in_dword(HWIO_AOP_F1_QTMR_V1_CNTVOFF_LO_ADDR)
#define HWIO_AOP_F1_QTMR_V1_CNTVOFF_LO_INM(m)            \
                in_dword_masked(HWIO_AOP_F1_QTMR_V1_CNTVOFF_LO_ADDR, m)
#define HWIO_AOP_F1_QTMR_V1_CNTVOFF_LO_CNTVOFF_L0_BMSK              0xffffffff
#define HWIO_AOP_F1_QTMR_V1_CNTVOFF_LO_CNTVOFF_L0_SHFT                       0

#define HWIO_AOP_F1_QTMR_V1_CNTVOFF_HI_ADDR                         (AOP_F1_QTMR_V1_F1_REG_BASE      + 0x1c)
#define HWIO_AOP_F1_QTMR_V1_CNTVOFF_HI_PHYS                         (AOP_F1_QTMR_V1_F1_REG_BASE_PHYS + 0x1c)
#define HWIO_AOP_F1_QTMR_V1_CNTVOFF_HI_OFFS                         (AOP_F1_QTMR_V1_F1_REG_BASE_OFFS + 0x1c)
#define HWIO_AOP_F1_QTMR_V1_CNTVOFF_HI_RMSK                           0xffffff
#define HWIO_AOP_F1_QTMR_V1_CNTVOFF_HI_IN                    \
                in_dword(HWIO_AOP_F1_QTMR_V1_CNTVOFF_HI_ADDR)
#define HWIO_AOP_F1_QTMR_V1_CNTVOFF_HI_INM(m)            \
                in_dword_masked(HWIO_AOP_F1_QTMR_V1_CNTVOFF_HI_ADDR, m)
#define HWIO_AOP_F1_QTMR_V1_CNTVOFF_HI_CNTVOFF_HI_BMSK                0xffffff
#define HWIO_AOP_F1_QTMR_V1_CNTVOFF_HI_CNTVOFF_HI_SHFT                       0

#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_LO_ADDR                       (AOP_F1_QTMR_V1_F1_REG_BASE      + 0x20)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_LO_PHYS                       (AOP_F1_QTMR_V1_F1_REG_BASE_PHYS + 0x20)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_LO_OFFS                       (AOP_F1_QTMR_V1_F1_REG_BASE_OFFS + 0x20)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_LO_RMSK                       0xffffffff
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_LO_IN                    \
                in_dword(HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_LO_ADDR)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_LO_INM(m)            \
                in_dword_masked(HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_LO_ADDR, m)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_LO_OUT(v)            \
                out_dword(HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_LO_ADDR,v)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_LO_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_LO_ADDR,m,v,HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_LO_IN)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_LO_CNTP_CVAL_L0_BMSK          0xffffffff
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_LO_CNTP_CVAL_L0_SHFT                   0

#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_HI_ADDR                       (AOP_F1_QTMR_V1_F1_REG_BASE      + 0x24)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_HI_PHYS                       (AOP_F1_QTMR_V1_F1_REG_BASE_PHYS + 0x24)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_HI_OFFS                       (AOP_F1_QTMR_V1_F1_REG_BASE_OFFS + 0x24)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_HI_RMSK                         0xffffff
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_HI_IN                    \
                in_dword(HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_HI_ADDR)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_HI_INM(m)            \
                in_dword_masked(HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_HI_ADDR, m)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_HI_OUT(v)            \
                out_dword(HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_HI_ADDR,v)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_HI_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_HI_ADDR,m,v,HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_HI_IN)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_HI_CNTP_CVAL_HI_BMSK            0xffffff
#define HWIO_AOP_F1_QTMR_V1_CNTP_CVAL_HI_CNTP_CVAL_HI_SHFT                   0

#define HWIO_AOP_F1_QTMR_V1_CNTP_TVAL_ADDR                          (AOP_F1_QTMR_V1_F1_REG_BASE      + 0x28)
#define HWIO_AOP_F1_QTMR_V1_CNTP_TVAL_PHYS                          (AOP_F1_QTMR_V1_F1_REG_BASE_PHYS + 0x28)
#define HWIO_AOP_F1_QTMR_V1_CNTP_TVAL_OFFS                          (AOP_F1_QTMR_V1_F1_REG_BASE_OFFS + 0x28)
#define HWIO_AOP_F1_QTMR_V1_CNTP_TVAL_RMSK                          0xffffffff
#define HWIO_AOP_F1_QTMR_V1_CNTP_TVAL_IN                    \
                in_dword(HWIO_AOP_F1_QTMR_V1_CNTP_TVAL_ADDR)
#define HWIO_AOP_F1_QTMR_V1_CNTP_TVAL_INM(m)            \
                in_dword_masked(HWIO_AOP_F1_QTMR_V1_CNTP_TVAL_ADDR, m)
#define HWIO_AOP_F1_QTMR_V1_CNTP_TVAL_OUT(v)            \
                out_dword(HWIO_AOP_F1_QTMR_V1_CNTP_TVAL_ADDR,v)
#define HWIO_AOP_F1_QTMR_V1_CNTP_TVAL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F1_QTMR_V1_CNTP_TVAL_ADDR,m,v,HWIO_AOP_F1_QTMR_V1_CNTP_TVAL_IN)
#define HWIO_AOP_F1_QTMR_V1_CNTP_TVAL_CNTP_TVAL_BMSK                0xffffffff
#define HWIO_AOP_F1_QTMR_V1_CNTP_TVAL_CNTP_TVAL_SHFT                         0

#define HWIO_AOP_F1_QTMR_V1_CNTP_CTL_ADDR                           (AOP_F1_QTMR_V1_F1_REG_BASE      + 0x2c)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CTL_PHYS                           (AOP_F1_QTMR_V1_F1_REG_BASE_PHYS + 0x2c)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CTL_OFFS                           (AOP_F1_QTMR_V1_F1_REG_BASE_OFFS + 0x2c)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CTL_RMSK                                  0x7
#define HWIO_AOP_F1_QTMR_V1_CNTP_CTL_IN                    \
                in_dword(HWIO_AOP_F1_QTMR_V1_CNTP_CTL_ADDR)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CTL_INM(m)            \
                in_dword_masked(HWIO_AOP_F1_QTMR_V1_CNTP_CTL_ADDR, m)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CTL_OUT(v)            \
                out_dword(HWIO_AOP_F1_QTMR_V1_CNTP_CTL_ADDR,v)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CTL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F1_QTMR_V1_CNTP_CTL_ADDR,m,v,HWIO_AOP_F1_QTMR_V1_CNTP_CTL_IN)
#define HWIO_AOP_F1_QTMR_V1_CNTP_CTL_ISTAT_BMSK                            0x4
#define HWIO_AOP_F1_QTMR_V1_CNTP_CTL_ISTAT_SHFT                              2
#define HWIO_AOP_F1_QTMR_V1_CNTP_CTL_IMSK_BMSK                             0x2
#define HWIO_AOP_F1_QTMR_V1_CNTP_CTL_IMSK_SHFT                               1
#define HWIO_AOP_F1_QTMR_V1_CNTP_CTL_EN_BMSK                               0x1
#define HWIO_AOP_F1_QTMR_V1_CNTP_CTL_EN_SHFT                                 0

#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_LO_ADDR                       (AOP_F1_QTMR_V1_F1_REG_BASE      + 0x30)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_LO_PHYS                       (AOP_F1_QTMR_V1_F1_REG_BASE_PHYS + 0x30)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_LO_OFFS                       (AOP_F1_QTMR_V1_F1_REG_BASE_OFFS + 0x30)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_LO_RMSK                       0xffffffff
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_LO_IN                    \
                in_dword(HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_LO_ADDR)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_LO_INM(m)            \
                in_dword_masked(HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_LO_ADDR, m)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_LO_OUT(v)            \
                out_dword(HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_LO_ADDR,v)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_LO_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_LO_ADDR,m,v,HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_LO_IN)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_LO_CNTV_CVAL_L0_BMSK          0xffffffff
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_LO_CNTV_CVAL_L0_SHFT                   0

#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_HI_ADDR                       (AOP_F1_QTMR_V1_F1_REG_BASE      + 0x34)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_HI_PHYS                       (AOP_F1_QTMR_V1_F1_REG_BASE_PHYS + 0x34)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_HI_OFFS                       (AOP_F1_QTMR_V1_F1_REG_BASE_OFFS + 0x34)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_HI_RMSK                         0xffffff
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_HI_IN                    \
                in_dword(HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_HI_ADDR)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_HI_INM(m)            \
                in_dword_masked(HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_HI_ADDR, m)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_HI_OUT(v)            \
                out_dword(HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_HI_ADDR,v)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_HI_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_HI_ADDR,m,v,HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_HI_IN)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_HI_CNTV_CVAL_HI_BMSK            0xffffff
#define HWIO_AOP_F1_QTMR_V1_CNTV_CVAL_HI_CNTV_CVAL_HI_SHFT                   0

#define HWIO_AOP_F1_QTMR_V1_CNTV_TVAL_ADDR                          (AOP_F1_QTMR_V1_F1_REG_BASE      + 0x38)
#define HWIO_AOP_F1_QTMR_V1_CNTV_TVAL_PHYS                          (AOP_F1_QTMR_V1_F1_REG_BASE_PHYS + 0x38)
#define HWIO_AOP_F1_QTMR_V1_CNTV_TVAL_OFFS                          (AOP_F1_QTMR_V1_F1_REG_BASE_OFFS + 0x38)
#define HWIO_AOP_F1_QTMR_V1_CNTV_TVAL_RMSK                          0xffffffff
#define HWIO_AOP_F1_QTMR_V1_CNTV_TVAL_IN                    \
                in_dword(HWIO_AOP_F1_QTMR_V1_CNTV_TVAL_ADDR)
#define HWIO_AOP_F1_QTMR_V1_CNTV_TVAL_INM(m)            \
                in_dword_masked(HWIO_AOP_F1_QTMR_V1_CNTV_TVAL_ADDR, m)
#define HWIO_AOP_F1_QTMR_V1_CNTV_TVAL_OUT(v)            \
                out_dword(HWIO_AOP_F1_QTMR_V1_CNTV_TVAL_ADDR,v)
#define HWIO_AOP_F1_QTMR_V1_CNTV_TVAL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F1_QTMR_V1_CNTV_TVAL_ADDR,m,v,HWIO_AOP_F1_QTMR_V1_CNTV_TVAL_IN)
#define HWIO_AOP_F1_QTMR_V1_CNTV_TVAL_CNTV_TVAL_BMSK                0xffffffff
#define HWIO_AOP_F1_QTMR_V1_CNTV_TVAL_CNTV_TVAL_SHFT                         0

#define HWIO_AOP_F1_QTMR_V1_CNTV_CTL_ADDR                           (AOP_F1_QTMR_V1_F1_REG_BASE      + 0x3c)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CTL_PHYS                           (AOP_F1_QTMR_V1_F1_REG_BASE_PHYS + 0x3c)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CTL_OFFS                           (AOP_F1_QTMR_V1_F1_REG_BASE_OFFS + 0x3c)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CTL_RMSK                                  0x7
#define HWIO_AOP_F1_QTMR_V1_CNTV_CTL_IN                    \
                in_dword(HWIO_AOP_F1_QTMR_V1_CNTV_CTL_ADDR)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CTL_INM(m)            \
                in_dword_masked(HWIO_AOP_F1_QTMR_V1_CNTV_CTL_ADDR, m)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CTL_OUT(v)            \
                out_dword(HWIO_AOP_F1_QTMR_V1_CNTV_CTL_ADDR,v)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CTL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_F1_QTMR_V1_CNTV_CTL_ADDR,m,v,HWIO_AOP_F1_QTMR_V1_CNTV_CTL_IN)
#define HWIO_AOP_F1_QTMR_V1_CNTV_CTL_ISTAT_BMSK                            0x4
#define HWIO_AOP_F1_QTMR_V1_CNTV_CTL_ISTAT_SHFT                              2
#define HWIO_AOP_F1_QTMR_V1_CNTV_CTL_IMSK_BMSK                             0x2
#define HWIO_AOP_F1_QTMR_V1_CNTV_CTL_IMSK_SHFT                               1
#define HWIO_AOP_F1_QTMR_V1_CNTV_CTL_EN_BMSK                               0x1
#define HWIO_AOP_F1_QTMR_V1_CNTV_CTL_EN_SHFT                                 0

#define HWIO_AOP_F1_QTMR_V1_VERSION_ADDR                            (AOP_F1_QTMR_V1_F1_REG_BASE      + 0xfd0)
#define HWIO_AOP_F1_QTMR_V1_VERSION_PHYS                            (AOP_F1_QTMR_V1_F1_REG_BASE_PHYS + 0xfd0)
#define HWIO_AOP_F1_QTMR_V1_VERSION_OFFS                            (AOP_F1_QTMR_V1_F1_REG_BASE_OFFS + 0xfd0)
#define HWIO_AOP_F1_QTMR_V1_VERSION_RMSK                            0xffffffff
#define HWIO_AOP_F1_QTMR_V1_VERSION_IN                    \
                in_dword(HWIO_AOP_F1_QTMR_V1_VERSION_ADDR)
#define HWIO_AOP_F1_QTMR_V1_VERSION_INM(m)            \
                in_dword_masked(HWIO_AOP_F1_QTMR_V1_VERSION_ADDR, m)
#define HWIO_AOP_F1_QTMR_V1_VERSION_MAJOR_BMSK                      0xf0000000
#define HWIO_AOP_F1_QTMR_V1_VERSION_MAJOR_SHFT                              28
#define HWIO_AOP_F1_QTMR_V1_VERSION_MINOR_BMSK                       0xfff0000
#define HWIO_AOP_F1_QTMR_V1_VERSION_MINOR_SHFT                              16
#define HWIO_AOP_F1_QTMR_V1_VERSION_STEP_BMSK                           0xffff
#define HWIO_AOP_F1_QTMR_V1_VERSION_STEP_SHFT                                0

/*----------------------------------------------------------------------------
 * MODULE: AOP_QTMR_AC
 *--------------------------------------------------------------------------*/

#define AOP_QTMR_AC_REG_BASE                                        (AOSS_BASE      + 0x00090000)
#define AOP_QTMR_AC_REG_BASE_SIZE                                   0x1000
#define AOP_QTMR_AC_REG_BASE_USED                                   0xff0
#define AOP_QTMR_AC_REG_BASE_PHYS                                   (AOSS_BASE_PHYS + 0x00090000)
#define AOP_QTMR_AC_REG_BASE_OFFS                                   0x00090000

#define HWIO_AOP_QTMR_AC_CNTFRQ_ADDR                                (AOP_QTMR_AC_REG_BASE      + 0x0)
#define HWIO_AOP_QTMR_AC_CNTFRQ_PHYS                                (AOP_QTMR_AC_REG_BASE_PHYS + 0x0)
#define HWIO_AOP_QTMR_AC_CNTFRQ_OFFS                                (AOP_QTMR_AC_REG_BASE_OFFS + 0x0)
#define HWIO_AOP_QTMR_AC_CNTFRQ_RMSK                                0xffffffff
#define HWIO_AOP_QTMR_AC_CNTFRQ_IN                    \
                in_dword(HWIO_AOP_QTMR_AC_CNTFRQ_ADDR)
#define HWIO_AOP_QTMR_AC_CNTFRQ_INM(m)            \
                in_dword_masked(HWIO_AOP_QTMR_AC_CNTFRQ_ADDR, m)
#define HWIO_AOP_QTMR_AC_CNTFRQ_OUT(v)            \
                out_dword(HWIO_AOP_QTMR_AC_CNTFRQ_ADDR,v)
#define HWIO_AOP_QTMR_AC_CNTFRQ_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_QTMR_AC_CNTFRQ_ADDR,m,v,HWIO_AOP_QTMR_AC_CNTFRQ_IN)
#define HWIO_AOP_QTMR_AC_CNTFRQ_CNTFRQ_BMSK                         0xffffffff
#define HWIO_AOP_QTMR_AC_CNTFRQ_CNTFRQ_SHFT                                  0

#define HWIO_AOP_QTMR_AC_CNTNSAR_FG0_ADDR                           (AOP_QTMR_AC_REG_BASE      + 0x4)
#define HWIO_AOP_QTMR_AC_CNTNSAR_FG0_PHYS                           (AOP_QTMR_AC_REG_BASE_PHYS + 0x4)
#define HWIO_AOP_QTMR_AC_CNTNSAR_FG0_OFFS                           (AOP_QTMR_AC_REG_BASE_OFFS + 0x4)
#define HWIO_AOP_QTMR_AC_CNTNSAR_FG0_RMSK                                  0x3
#define HWIO_AOP_QTMR_AC_CNTNSAR_FG0_IN                    \
                in_dword(HWIO_AOP_QTMR_AC_CNTNSAR_FG0_ADDR)
#define HWIO_AOP_QTMR_AC_CNTNSAR_FG0_INM(m)            \
                in_dword_masked(HWIO_AOP_QTMR_AC_CNTNSAR_FG0_ADDR, m)
#define HWIO_AOP_QTMR_AC_CNTNSAR_FG0_OUT(v)            \
                out_dword(HWIO_AOP_QTMR_AC_CNTNSAR_FG0_ADDR,v)
#define HWIO_AOP_QTMR_AC_CNTNSAR_FG0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_QTMR_AC_CNTNSAR_FG0_ADDR,m,v,HWIO_AOP_QTMR_AC_CNTNSAR_FG0_IN)
#define HWIO_AOP_QTMR_AC_CNTNSAR_FG0_NSN_BMSK                              0x3
#define HWIO_AOP_QTMR_AC_CNTNSAR_FG0_NSN_SHFT                                0

#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_ADDR                           (AOP_QTMR_AC_REG_BASE      + 0x8)
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_PHYS                           (AOP_QTMR_AC_REG_BASE_PHYS + 0x8)
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_OFFS                           (AOP_QTMR_AC_REG_BASE_OFFS + 0x8)
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_RMSK                           0xffffffff
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_IN                    \
                in_dword(HWIO_AOP_QTMR_AC_CNTTIDR_FG0_ADDR)
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_INM(m)            \
                in_dword_masked(HWIO_AOP_QTMR_AC_CNTTIDR_FG0_ADDR, m)
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_F7_CFG_BMSK                    0xf0000000
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_F7_CFG_SHFT                            28
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_F6_CFG_BMSK                     0xf000000
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_F6_CFG_SHFT                            24
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_F5_CFG_BMSK                      0xf00000
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_F5_CFG_SHFT                            20
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_F4_CFG_BMSK                       0xf0000
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_F4_CFG_SHFT                            16
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_F3_CFG_BMSK                        0xf000
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_F3_CFG_SHFT                            12
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_F2_CFG_BMSK                         0xf00
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_F2_CFG_SHFT                             8
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_F1_CFG_BMSK                          0xf0
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_F1_CFG_SHFT                             4
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_F0_CFG_BMSK                           0xf
#define HWIO_AOP_QTMR_AC_CNTTIDR_FG0_F0_CFG_SHFT                             0

#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_ADDR(n)                        (AOP_QTMR_AC_REG_BASE      + 0X40 + (0x4*(n)))
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_PHYS(n)                        (AOP_QTMR_AC_REG_BASE_PHYS + 0X40 + (0x4*(n)))
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_OFFS(n)                        (AOP_QTMR_AC_REG_BASE_OFFS + 0X40 + (0x4*(n)))
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_RMSK                                 0x3f
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_MAXn                                    1
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_INI(n)                \
                in_dword_masked(HWIO_AOP_QTMR_AC_CNTACRn_FG0_ADDR(n), HWIO_AOP_QTMR_AC_CNTACRn_FG0_RMSK)
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_INMI(n,mask)        \
                in_dword_masked(HWIO_AOP_QTMR_AC_CNTACRn_FG0_ADDR(n), mask)
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_OUTI(n,val)        \
                out_dword(HWIO_AOP_QTMR_AC_CNTACRn_FG0_ADDR(n),val)
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_OUTMI(n,mask,val) \
                out_dword_masked_ns(HWIO_AOP_QTMR_AC_CNTACRn_FG0_ADDR(n),mask,val,HWIO_AOP_QTMR_AC_CNTACRn_FG0_INI(n))
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_RWPT_BMSK                            0x20
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_RWPT_SHFT                               5
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_RWVT_BMSK                            0x10
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_RWVT_SHFT                               4
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_RVOFF_BMSK                            0x8
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_RVOFF_SHFT                              3
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_RFRQ_BMSK                             0x4
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_RFRQ_SHFT                               2
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_RPVCT_BMSK                            0x2
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_RPVCT_SHFT                              1
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_RPCT_BMSK                             0x1
#define HWIO_AOP_QTMR_AC_CNTACRn_FG0_RPCT_SHFT                               0

#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_LO_n_ADDR(n)                   (AOP_QTMR_AC_REG_BASE      + 0X80 + (0x8*(n)))
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_LO_n_PHYS(n)                   (AOP_QTMR_AC_REG_BASE_PHYS + 0X80 + (0x8*(n)))
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_LO_n_OFFS(n)                   (AOP_QTMR_AC_REG_BASE_OFFS + 0X80 + (0x8*(n)))
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_LO_n_RMSK                      0xffffffff
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_LO_n_MAXn                               1
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_LO_n_INI(n)                \
                in_dword_masked(HWIO_AOP_QTMR_AC_CNTVOFF_FG0_LO_n_ADDR(n), HWIO_AOP_QTMR_AC_CNTVOFF_FG0_LO_n_RMSK)
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_LO_n_INMI(n,mask)        \
                in_dword_masked(HWIO_AOP_QTMR_AC_CNTVOFF_FG0_LO_n_ADDR(n), mask)
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_LO_n_OUTI(n,val)        \
                out_dword(HWIO_AOP_QTMR_AC_CNTVOFF_FG0_LO_n_ADDR(n),val)
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_LO_n_OUTMI(n,mask,val) \
                out_dword_masked_ns(HWIO_AOP_QTMR_AC_CNTVOFF_FG0_LO_n_ADDR(n),mask,val,HWIO_AOP_QTMR_AC_CNTVOFF_FG0_LO_n_INI(n))
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_LO_n_CNTVOFF_LO_BMSK           0xffffffff
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_LO_n_CNTVOFF_LO_SHFT                    0

#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_HI_n_ADDR(n)                   (AOP_QTMR_AC_REG_BASE      + 0X84 + (0x8*(n)))
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_HI_n_PHYS(n)                   (AOP_QTMR_AC_REG_BASE_PHYS + 0X84 + (0x8*(n)))
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_HI_n_OFFS(n)                   (AOP_QTMR_AC_REG_BASE_OFFS + 0X84 + (0x8*(n)))
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_HI_n_RMSK                        0xffffff
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_HI_n_MAXn                               1
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_HI_n_INI(n)                \
                in_dword_masked(HWIO_AOP_QTMR_AC_CNTVOFF_FG0_HI_n_ADDR(n), HWIO_AOP_QTMR_AC_CNTVOFF_FG0_HI_n_RMSK)
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_HI_n_INMI(n,mask)        \
                in_dword_masked(HWIO_AOP_QTMR_AC_CNTVOFF_FG0_HI_n_ADDR(n), mask)
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_HI_n_OUTI(n,val)        \
                out_dword(HWIO_AOP_QTMR_AC_CNTVOFF_FG0_HI_n_ADDR(n),val)
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_HI_n_OUTMI(n,mask,val) \
                out_dword_masked_ns(HWIO_AOP_QTMR_AC_CNTVOFF_FG0_HI_n_ADDR(n),mask,val,HWIO_AOP_QTMR_AC_CNTVOFF_FG0_HI_n_INI(n))
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_HI_n_CNTVOFF_HI_BMSK             0xffffff
#define HWIO_AOP_QTMR_AC_CNTVOFF_FG0_HI_n_CNTVOFF_HI_SHFT                    0

#define HWIO_AOP_QTMR_AC_CFG_ADDR                                   (AOP_QTMR_AC_REG_BASE      + 0xfc0)
#define HWIO_AOP_QTMR_AC_CFG_PHYS                                   (AOP_QTMR_AC_REG_BASE_PHYS + 0xfc0)
#define HWIO_AOP_QTMR_AC_CFG_OFFS                                   (AOP_QTMR_AC_REG_BASE_OFFS + 0xfc0)
#define HWIO_AOP_QTMR_AC_CFG_RMSK                                          0x3
#define HWIO_AOP_QTMR_AC_CFG_IN                    \
                in_dword(HWIO_AOP_QTMR_AC_CFG_ADDR)
#define HWIO_AOP_QTMR_AC_CFG_INM(m)            \
                in_dword_masked(HWIO_AOP_QTMR_AC_CFG_ADDR, m)
#define HWIO_AOP_QTMR_AC_CFG_OUT(v)            \
                out_dword(HWIO_AOP_QTMR_AC_CFG_ADDR,v)
#define HWIO_AOP_QTMR_AC_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_QTMR_AC_CFG_ADDR,m,v,HWIO_AOP_QTMR_AC_CFG_IN)
#define HWIO_AOP_QTMR_AC_CFG_DSBL_ATOMIC_BMSK                              0x2
#define HWIO_AOP_QTMR_AC_CFG_DSBL_ATOMIC_SHFT                                1
#define HWIO_AOP_QTMR_AC_CFG_TEST_BUS_EN_BMSK                              0x1
#define HWIO_AOP_QTMR_AC_CFG_TEST_BUS_EN_SHFT                                0

#define HWIO_AOP_QTMR_AC_VERSION_ADDR                               (AOP_QTMR_AC_REG_BASE      + 0xfd0)
#define HWIO_AOP_QTMR_AC_VERSION_PHYS                               (AOP_QTMR_AC_REG_BASE_PHYS + 0xfd0)
#define HWIO_AOP_QTMR_AC_VERSION_OFFS                               (AOP_QTMR_AC_REG_BASE_OFFS + 0xfd0)
#define HWIO_AOP_QTMR_AC_VERSION_RMSK                               0xffffffff
#define HWIO_AOP_QTMR_AC_VERSION_IN                    \
                in_dword(HWIO_AOP_QTMR_AC_VERSION_ADDR)
#define HWIO_AOP_QTMR_AC_VERSION_INM(m)            \
                in_dword_masked(HWIO_AOP_QTMR_AC_VERSION_ADDR, m)
#define HWIO_AOP_QTMR_AC_VERSION_MAJOR_BMSK                         0xf0000000
#define HWIO_AOP_QTMR_AC_VERSION_MAJOR_SHFT                                 28
#define HWIO_AOP_QTMR_AC_VERSION_MINOR_BMSK                          0xfff0000
#define HWIO_AOP_QTMR_AC_VERSION_MINOR_SHFT                                 16
#define HWIO_AOP_QTMR_AC_VERSION_STEP_BMSK                              0xffff
#define HWIO_AOP_QTMR_AC_VERSION_STEP_SHFT                                   0

#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_1_ADDR                        (AOP_QTMR_AC_REG_BASE      + 0xfe0)
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_1_PHYS                        (AOP_QTMR_AC_REG_BASE_PHYS + 0xfe0)
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_1_OFFS                        (AOP_QTMR_AC_REG_BASE_OFFS + 0xfe0)
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_1_RMSK                        0xffffffff
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_1_IN                    \
                in_dword(HWIO_AOP_QTMR_AC_HW_FRAME_SEL_1_ADDR)
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_1_INM(m)            \
                in_dword_masked(HWIO_AOP_QTMR_AC_HW_FRAME_SEL_1_ADDR, m)
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_1_OUT(v)            \
                out_dword(HWIO_AOP_QTMR_AC_HW_FRAME_SEL_1_ADDR,v)
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_QTMR_AC_HW_FRAME_SEL_1_ADDR,m,v,HWIO_AOP_QTMR_AC_HW_FRAME_SEL_1_IN)
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_1_HW_FRAME_SEL1_BMSK          0xffffffff
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_1_HW_FRAME_SEL1_SHFT                   0

#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_2_ADDR                        (AOP_QTMR_AC_REG_BASE      + 0xff0)
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_2_PHYS                        (AOP_QTMR_AC_REG_BASE_PHYS + 0xff0)
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_2_OFFS                        (AOP_QTMR_AC_REG_BASE_OFFS + 0xff0)
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_2_RMSK                        0xffffffff
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_2_IN                    \
                in_dword(HWIO_AOP_QTMR_AC_HW_FRAME_SEL_2_ADDR)
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_2_INM(m)            \
                in_dword_masked(HWIO_AOP_QTMR_AC_HW_FRAME_SEL_2_ADDR, m)
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_2_OUT(v)            \
                out_dword(HWIO_AOP_QTMR_AC_HW_FRAME_SEL_2_ADDR,v)
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AOP_QTMR_AC_HW_FRAME_SEL_2_ADDR,m,v,HWIO_AOP_QTMR_AC_HW_FRAME_SEL_2_IN)
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_2_HW_FRAME_SEL2_BMSK          0xffffffff
#define HWIO_AOP_QTMR_AC_HW_FRAME_SEL_2_HW_FRAME_SEL2_SHFT                   0


#endif /* __AOP_HWIO_H__ */
