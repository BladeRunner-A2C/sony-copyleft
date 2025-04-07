#ifndef __HAL_DP_PHY_1_4_1_HWIO_H__
#define __HAL_DP_PHY_1_4_1_HWIO_H__
/*
===========================================================================
*/
/**
    @file hal_dp_phy_1_4_1_hwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SC8380XP (Hamoa) [hamoa_v1.0_p2q1r63_HAMOA_APSS]
 
    This file contains HWIO register definitions for the following modules:
        AHB2PHY_1_QUSB4PHY_SS_0_QUSB4PHY_SS_0_CM_USB4_USB3_EDP_DP_CON
        AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY
        AHB2PHY_1_QUSB4PHY_SS_1_QUSB4PHY_SS_1_CM_USB4_USB3_EDP_DP_CON
        AHB2PHY_1_QUSB4PHY_SS_2_QUSB4PHY_SS_2_CM_USB4_USB3_EDP_DP_CON
        AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL
        AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX
        AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX
        AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM


    Generation parameters: 
    { 'filename': 'hal_dp_phy_1_4_1_hwio.h',
      'modules': [ 'AHB2PHY_1_QUSB4PHY_SS_0_QUSB4PHY_SS_0_CM_USB4_USB3_EDP_DP_CON',
                   'AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY',
                   'AHB2PHY_1_QUSB4PHY_SS_1_QUSB4PHY_SS_1_CM_USB4_USB3_EDP_DP_CON',
                   'AHB2PHY_1_QUSB4PHY_SS_2_QUSB4PHY_SS_2_CM_USB4_USB3_EDP_DP_CON',
                   'AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL',
                   'AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX',
                   'AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX',
                   'AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM']}
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

/*----------------------------------------------------------------------------
 * MODULE: AHB2PHY_1_QUSB4PHY_SS_0_QUSB4PHY_SS_0_CM_USB4_USB3_EDP_DP_CON
 *--------------------------------------------------------------------------*/
#define AHB2PHY_1_AHB2PHY_1_BASE                                                                  QMP_PHY_1_BASE

#define AHB2PHY_1_QUSB4PHY_SS_0_QUSB4PHY_SS_0_CM_USB4_USB3_EDP_DP_CON_REG_BASE (AHB2PHY_1_AHB2PHY_1_BASE      + 0x00005000)
#define AHB2PHY_1_QUSB4PHY_SS_0_QUSB4PHY_SS_0_CM_USB4_USB3_EDP_DP_CON_REG_BASE_SIZE 0x4000
#define AHB2PHY_1_QUSB4PHY_SS_0_QUSB4PHY_SS_0_CM_USB4_USB3_EDP_DP_CON_REG_BASE_USED 0x0

/*----------------------------------------------------------------------------
 * MODULE: AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY
 *--------------------------------------------------------------------------*/

#define AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE                                                 (AHB2PHY_1_AHB2PHY_1_BASE      + 0x00007200)
#define AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE_SIZE                                            0x1a0
#define AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE_USED                                            0x19c

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID0_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID0_RMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID0_STEP_7_0_BMSK                                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID0_STEP_7_0_SHFT                                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID1_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID1_RMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID1_STEP_15_8_BMSK                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID1_STEP_15_8_SHFT                                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID2_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID2_RMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID2_MINOR_7_0_BMSK                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID2_MINOR_7_0_SHFT                                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID3_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID3_RMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID3_MAJOR_BMSK                                              0xf0
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID3_MAJOR_SHFT                                                 4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID3_MINOR_11_8_BMSK                                          0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_REVISION_ID3_MINOR_11_8_SHFT                                            0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_ADDR                                                       (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x10)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_RMSK                                                             0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_RSVD_BMSK                                                        0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_RSVD_SHFT                                                           7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_DP_CFG_SPARE_BMSK                                                0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_DP_CFG_SPARE_SHFT                                                   6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_AUX_RESET_BMSK                                                   0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_AUX_RESET_SHFT                                                      5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_CORE_RESET_TSYNC_BMSK                                            0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_CORE_RESET_TSYNC_SHFT                                               4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_PLL_START_BMSK                                                    0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_PLL_START_SHFT                                                      3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_PLL_RESET_BMSK                                                    0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_PLL_RESET_SHFT                                                      2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_SW_RESET_BMSK                                                     0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_SW_RESET_SHFT                                                       1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_RETIMING_ENABLE_BMSK                                              0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_RETIMING_ENABLE_SHFT                                                0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_ADDR                                                     (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x14)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_RMSK                                                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_C_READY_MUX_BMSK                                               0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_C_READY_MUX_SHFT                                                  7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_SW_C_READY_BMSK                                                0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_SW_C_READY_SHFT                                                   6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_TCLK_LINKCLK_SEL_BMSK                                          0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_TCLK_LINKCLK_SEL_SHFT                                             5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_DISABLE_CGC_EN_BMSK                                            0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_DISABLE_CGC_EN_SHFT                                               4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_RT_BUFFER_LANE3_EN_BMSK                                         0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_RT_BUFFER_LANE3_EN_SHFT                                           3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_RT_BUFFER_LANE2_EN_BMSK                                         0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_RT_BUFFER_LANE2_EN_SHFT                                           2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_RT_BUFFER_LANE1_EN_BMSK                                         0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_RT_BUFFER_LANE1_EN_SHFT                                           1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_RT_BUFFER_LANE0_EN_BMSK                                         0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_CFG_1_RT_BUFFER_LANE0_EN_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x18)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_EN_VREG_USE_BMSK                                              0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_EN_VREG_USE_SHFT                                                 7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_DP_CLAMP_EN_B_BMSK                                            0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_DP_CLAMP_EN_B_SHFT                                               6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_PLL_PWRDN_B_BMSK                                              0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_PLL_PWRDN_B_SHFT                                                 5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_LANE_2_3_PWRDN_B_BMSK                                         0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_LANE_2_3_PWRDN_B_SHFT                                            4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_LANE_0_1_PWRDN_B_BMSK                                          0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_LANE_0_1_PWRDN_B_SHFT                                            3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_AUX_PWRDN_B_BMSK                                               0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_AUX_PWRDN_B_SHFT                                                 2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_PSR_PWRDN_BMSK                                                 0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_PSR_PWRDN_SHFT                                                   1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_PWRDN_B_BMSK                                                   0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_PD_CTL_PWRDN_B_SHFT                                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x1c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_RMSK                                                            0x7f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_RETIME_BUFFER_SIZE_BMSK                                         0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_RETIME_BUFFER_SIZE_SHFT                                            6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_LINK_CLOCK_SEL_MUX_BMSK                                         0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_LINK_CLOCK_SEL_MUX_SHFT                                            5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_LINK_CLOCK_SEL_BMSK                                             0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_LINK_CLOCK_SEL_SHFT                                                4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_PAR_RATE_BMSK                                                    0xc
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_PAR_RATE_SHFT                                                      2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_TX_BAND_BMSK                                                     0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MODE_TX_BAND_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG0_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x20)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG0_RMSK                                                         0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG0_AUX_FORCE_TX_EN_BMSK                                         0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG0_AUX_FORCE_TX_EN_SHFT                                           3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG0_AUX_BYPASS_BMSK                                              0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG0_AUX_BYPASS_SHFT                                                2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG0_RSVD_BMSK                                                    0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG0_RSVD_SHFT                                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG1_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x24)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG1_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG1_AUX_DCTRL_7_0_BMSK                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG1_AUX_DCTRL_7_0_SHFT                                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG2_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x28)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG2_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG2_AUX_DCTRL_15_8_BMSK                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG2_AUX_DCTRL_15_8_SHFT                                            0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x2c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_AUX_FORCE_RX_EN_BMSK                                        0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_AUX_FORCE_RX_EN_SHFT                                           7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_AUX_TX_PRECHARGE_BMSK                                       0x70
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_AUX_TX_PRECHARGE_SHFT                                          4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_AUX_PARALLEL_LBK_BMSK                                        0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_AUX_PARALLEL_LBK_SHFT                                          3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_AUX_BYPASS_MANCH_LBK_BMSK                                    0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_AUX_BYPASS_MANCH_LBK_SHFT                                      2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_AUX_SERIAL_LBK_BMSK                                          0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_AUX_SERIAL_LBK_SHFT                                            1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_AUX_NEAREND_LBK_BMSK                                         0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG3_AUX_NEAREND_LBK_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG4_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x30)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG4_RMSK                                                        0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG4_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG4_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG4_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG4_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG4_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG4_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG4_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG4_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG4_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG4_AUX_TX_MANCH_HALFCYC_BMSK                                   0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG4_AUX_TX_MANCH_HALFCYC_SHFT                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG5_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x34)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG5_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG5_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG5_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG5_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG5_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG5_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG5_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG5_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG5_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG5_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG5_AUX_RX_MANCH_TWOCYC_BMSK                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG5_AUX_RX_MANCH_TWOCYC_SHFT                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG6_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x38)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG6_RMSK                                                        0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG6_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG6_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG6_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG6_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG6_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG6_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG6_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG6_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG6_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG6_AUX_RX_MANCH_HALFCYC_BMSK                                   0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG6_AUX_RX_MANCH_HALFCYC_SHFT                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG7_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x3c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG7_RMSK                                                         0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG7_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG7_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG7_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG7_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG7_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG7_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG7_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG7_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG7_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG7_AUX_RX_MANCH_CYCJITTER_BMSK                                  0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG7_AUX_RX_MANCH_CYCJITTER_SHFT                                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG8_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x40)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG8_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG8_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG8_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG8_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG8_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG8_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG8_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG8_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG8_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG8_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG8_AUX_TX_PREAMBLE_BMSK                                        0xf0
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG8_AUX_TX_PREAMBLE_SHFT                                           4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG8_AUX_RX_PREAMBLE_BMSK                                         0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG8_AUX_RX_PREAMBLE_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x44)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_OVERRIDE_TWOCYC_BMSK                                        0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_OVERRIDE_TWOCYC_SHFT                                           7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_OVERRIDE_HALFCYC_BMSK                                       0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_OVERRIDE_HALFCYC_SHFT                                          6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_OVERRIDE_AUX_TIMING_BMSK                                    0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_OVERRIDE_AUX_TIMING_SHFT                                       5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_AUX_RX_CFG_SPARE_BMSK                                       0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_AUX_RX_CFG_SPARE_SHFT                                          4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_AUX_RX_ZERO_IDLE_CNT_BMSK                                    0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG9_AUX_RX_ZERO_IDLE_CNT_SHFT                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG10_ADDR                                                 (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x48)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG10_RMSK                                                       0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG10_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG10_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG10_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG10_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG10_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG10_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG10_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG10_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG10_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG10_AUX_RX_START_DEBOUNCE_ENA_BMSK                             0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG10_AUX_RX_START_DEBOUNCE_ENA_SHFT                                5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG10_AUX_RXOUT_DEBOUNCE_ENA_BMSK                                0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG10_AUX_RXOUT_DEBOUNCE_ENA_SHFT                                   4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG10_AUX_DBOUNCE_SPARE_BMSK                                      0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG10_AUX_DBOUNCE_SPARE_SHFT                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG11_ADDR                                                 (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x4c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG11_RMSK                                                        0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG11_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG11_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG11_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG11_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG11_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG11_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG11_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG11_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG11_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG11_DLY_AUX_RX_VALID_BMSK                                       0x6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG11_DLY_AUX_RX_VALID_SHFT                                         1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG11_USE_AUXRX_GEN1_BMSK                                         0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG11_USE_AUXRX_GEN1_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG12_ADDR                                                 (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x50)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG12_RMSK                                                       0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG12_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG12_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG12_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG12_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG12_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG12_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG12_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG12_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG12_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG12_AUX_DCTRL_23_16_BMSK                                       0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_CFG12_AUX_DCTRL_23_16_SHFT                                          0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x54)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_RMSK                                              0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_AUX_TX_REQ_ERR_MASK_BMSK                          0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_AUX_TX_REQ_ERR_MASK_SHFT                             4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_AUX_RX_ALIGN_ERR_MASK_BMSK                         0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_AUX_RX_ALIGN_ERR_MASK_SHFT                           3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_AUX_RX_SYNC_ERR_MASK_BMSK                          0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_AUX_RX_SYNC_ERR_MASK_SHFT                            2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_AUX_RX_DEC_ERR_MASK_BMSK                           0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_AUX_RX_DEC_ERR_MASK_SHFT                             1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_AUX_RX_STOP_ERR_MASK_BMSK                          0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_MASK_AUX_RX_STOP_ERR_MASK_SHFT                            0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x58)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_RMSK                                             0x9f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_AUX_GLOBE_REQ_CLR_CMD_BMSK                       0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_AUX_GLOBE_REQ_CLR_CMD_SHFT                          7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_AUX_TX_REQ_ERR_CLR_BMSK                          0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_AUX_TX_REQ_ERR_CLR_SHFT                             4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_AUX_RX_ALIGN_ERR_CLR_BMSK                         0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_AUX_RX_ALIGN_ERR_CLR_SHFT                           3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_AUX_RX_SYNC_ERR_CLR_BMSK                          0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_AUX_RX_SYNC_ERR_CLR_SHFT                            2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_AUX_RX_DEC_ERR_CLR_BMSK                           0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_AUX_RX_DEC_ERR_CLR_SHFT                             1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_AUX_RX_STOP_ERR_CLR_BMSK                          0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_CLEAR_AUX_RX_STOP_ERR_CLR_SHFT                            0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x5c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_RMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_AUX_BIST_MODE_BMSK                                      0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_AUX_BIST_MODE_SHFT                                         7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_AUX_BIST_SEL_BMSK                                       0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_AUX_BIST_SEL_SHFT                                          6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_AUX_TX_PATGEN_EN_BMSK                                   0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_AUX_TX_PATGEN_EN_SHFT                                      5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_AUX_TX_FIXPAT_BMSK                                      0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_AUX_TX_FIXPAT_SHFT                                         4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_AUX_RX_PRBS_CHK_EN_BMSK                                  0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_AUX_RX_PRBS_CHK_EN_SHFT                                    3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_AUX_RX_PRBS_CHK_GEN_SHORT_BMSK                           0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_AUX_RX_PRBS_CHK_GEN_SHORT_SHFT                             2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_AUX_RX_PRBS_CHK_ERR_EN_BMSK                              0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_AUX_RX_PRBS_CHK_ERR_EN_SHFT                                1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_AUX_RX_PRBS_CHK_CLR_ERROR_COUNT_BMSK                     0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_CFG_AUX_RX_PRBS_CHK_CLR_ERROR_COUNT_SHFT                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_SEED_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x60)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_SEED_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_SEED_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_SEED_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_SEED_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_SEED_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_SEED_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_SEED_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_SEED_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_SEED_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_SEED_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_SEED_AUX_BIST_PRBS_SEED_BMSK                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_SEED_AUX_BIST_PRBS_SEED_SHFT                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_POLY_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x64)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_POLY_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_POLY_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_POLY_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_POLY_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_POLY_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_POLY_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_POLY_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_POLY_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_POLY_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_POLY_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_POLY_AUX_BIST_PRBS_POLY_BMSK                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_PRBS_POLY_AUX_BIST_PRBS_POLY_SHFT                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_LSB_ADDR                                   (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x68)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_LSB_RMSK                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_LSB_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_LSB_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_LSB_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_LSB_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_LSB_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_LSB_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_LSB_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_LSB_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_LSB_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_LSB_AUX_TX_PROG_PAT_16B_7_0_BMSK                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_LSB_AUX_TX_PROG_PAT_16B_7_0_SHFT                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_MSB_ADDR                                   (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x6c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_MSB_RMSK                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_MSB_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_MSB_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_MSB_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_MSB_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_MSB_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_MSB_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_MSB_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_MSB_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_MSB_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_MSB_AUX_TX_PROG_PAT_16B_15_8_BMSK                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_TX_PROG_PAT_16B_MSB_AUX_TX_PROG_PAT_16B_15_8_SHFT                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_VCO_DIV_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x70)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_VCO_DIV_RMSK                                                          0xb
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_VCO_DIV_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_VCO_DIV_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_VCO_DIV_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_VCO_DIV_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_VCO_DIV_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_VCO_DIV_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_VCO_DIV_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_VCO_DIV_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_VCO_DIV_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_VCO_DIV_FORCE_CLKBUF_EN_BMSK                                          0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_VCO_DIV_FORCE_CLKBUF_EN_SHFT                                            3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_VCO_DIV_VCO_DIV_CLK_SEL_BMSK                                          0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_VCO_DIV_VCO_DIV_CLK_SEL_SHFT                                            0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_ADDR                                                (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x74)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_RMSK                                                      0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_SW_C_EXT_CLKBUF_EN_MUX_BMSK                               0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_SW_C_EXT_CLKBUF_EN_MUX_SHFT                                  5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_SW_C_EXT_CLKBUF_EN_BMSK                                   0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_SW_C_EXT_CLKBUF_EN_SHFT                                      4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_SW_TSYNC_DONE_MUX_BMSK                                     0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_SW_TSYNC_DONE_MUX_SHFT                                       3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_SW_TSYNC_DONE_BMSK                                         0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_SW_TSYNC_DONE_SHFT                                           2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_SW_EXT_TSYNC_MUX_BMSK                                      0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_SW_EXT_TSYNC_MUX_SHFT                                        1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_SW_EXT_TSYNC_BMSK                                          0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TSYNC_OVRD_SW_EXT_TSYNC_SHFT                                            0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_LANE_CTL_ADDR                                          (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x78)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_LANE_CTL_RMSK                                                 0x5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_LANE_CTL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_LANE_CTL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_LANE_CTL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_LANE_CTL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_LANE_CTL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_LANE_CTL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_LANE_CTL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_LANE_CTL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_LANE_CTL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_LANE_CTL_L0_CORE_TXCLK_EN_BMSK                                0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_LANE_CTL_L0_CORE_TXCLK_EN_SHFT                                  2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_LANE_CTL_L0_CORE_PLL_EN_BMSK                                  0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_LANE_CTL_L0_CORE_PLL_EN_SHFT                                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_ADDR                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x7c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_RMSK                                               0x7f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_L0_BIST_TX_HDR_PRBS_SEL_BMSK                       0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_L0_BIST_TX_HDR_PRBS_SEL_SHFT                          6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_L0_BIST_TCLK_SEL_BMSK                              0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_L0_BIST_TCLK_SEL_SHFT                                 5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_L0_BIST_TX_GEN_EN_BMSK                             0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_L0_BIST_TX_GEN_EN_SHFT                                4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_L0_BIST_RX_PRBS_CHK_EN_BMSK                         0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_L0_BIST_RX_PRBS_CHK_EN_SHFT                           3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_L0_BIST_RX_PRBS_GEN_SHORT_BMSK                      0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_L0_BIST_RX_PRBS_GEN_SHORT_SHFT                        2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_L0_BIST_ERROR_INJECT_BMSK                           0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_L0_BIST_ERROR_INJECT_SHFT                             1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_L0_BIST_ERROR_CLEAR_BMSK                            0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG0_L0_BIST_ERROR_CLEAR_SHFT                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG1_ADDR                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x80)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG1_RMSK                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG1_L0_BIST_RX_RESET_PCS_BMSK                          0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG1_L0_BIST_RX_RESET_PCS_SHFT                             7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG1_L0_BIST_TX_RESET_PCS_BMSK                          0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG1_L0_BIST_TX_RESET_PCS_SHFT                             6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG1_L0_BIST_MODE_BMSK                                  0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG1_L0_BIST_MODE_SHFT                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG2_ADDR                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x84)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG2_RMSK                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG2_L0_HEADER_PAT_7_0_BMSK                             0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG2_L0_HEADER_PAT_7_0_SHFT                                0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG3_ADDR                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x88)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG3_RMSK                                                0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG3_L0_BIST_TX_MASK_BMSK                                0xc
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG3_L0_BIST_TX_MASK_SHFT                                  2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG3_L0_HEADER_PAT_9_8_BMSK                              0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_CFG3_L0_HEADER_PAT_9_8_SHFT                                0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE0_ADDR                                   (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x8c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE0_RMSK                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE0_L0_PRBS_SEED_7_0_BMSK                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE0_L0_PRBS_SEED_7_0_SHFT                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE1_ADDR                                   (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x90)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE1_RMSK                                          0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE1_L0_PRBS_SEED_9_8_BMSK                         0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_PRBS_SEED_BYTE1_L0_PRBS_SEED_9_8_SHFT                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN0_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x94)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN0_RMSK                                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN0_L0_PRBS_POLY_7_0_BMSK                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN0_L0_PRBS_POLY_7_0_SHFT                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN1_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x98)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN1_RMSK                                            0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN1_L0_PRBS_POLY_9_8_BMSK                           0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_PATTERN1_L0_PRBS_POLY_9_8_SHFT                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_LANE_CTL_ADDR                                          (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x9c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_LANE_CTL_RMSK                                                 0x5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_LANE_CTL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_LANE_CTL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_LANE_CTL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_LANE_CTL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_LANE_CTL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_LANE_CTL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_LANE_CTL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_LANE_CTL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_LANE_CTL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_LANE_CTL_L1_CORE_TXCLK_EN_BMSK                                0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_LANE_CTL_L1_CORE_TXCLK_EN_SHFT                                  2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_LANE_CTL_L1_CORE_PLL_EN_BMSK                                  0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_LANE_CTL_L1_CORE_PLL_EN_SHFT                                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_ADDR                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xa0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_RMSK                                               0x7f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_L1_BIST_TX_HDR_PRBS_SEL_BMSK                       0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_L1_BIST_TX_HDR_PRBS_SEL_SHFT                          6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_L1_BIST_TCLK_SEL_BMSK                              0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_L1_BIST_TCLK_SEL_SHFT                                 5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_L1_BIST_TX_GEN_EN_BMSK                             0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_L1_BIST_TX_GEN_EN_SHFT                                4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_L1_BIST_RX_PRBS_CHK_EN_BMSK                         0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_L1_BIST_RX_PRBS_CHK_EN_SHFT                           3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_L1_BIST_RX_PRBS_GEN_SHORT_BMSK                      0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_L1_BIST_RX_PRBS_GEN_SHORT_SHFT                        2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_L1_BIST_ERROR_INJECT_BMSK                           0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_L1_BIST_ERROR_INJECT_SHFT                             1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_L1_BIST_ERROR_CLEAR_BMSK                            0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG0_L1_BIST_ERROR_CLEAR_SHFT                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG1_ADDR                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xa4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG1_RMSK                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG1_L1_BIST_RX_RESET_PCS_BMSK                          0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG1_L1_BIST_RX_RESET_PCS_SHFT                             7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG1_L1_BIST_TX_RESET_PCS_BMSK                          0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG1_L1_BIST_TX_RESET_PCS_SHFT                             6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG1_L1_BIST_MODE_BMSK                                  0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG1_L1_BIST_MODE_SHFT                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG2_ADDR                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xa8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG2_RMSK                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG2_L1_HEADER_PAT_7_0_BMSK                             0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG2_L1_HEADER_PAT_7_0_SHFT                                0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG3_ADDR                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xac)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG3_RMSK                                                0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG3_L1_BIST_TX_MASK_BMSK                                0xc
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG3_L1_BIST_TX_MASK_SHFT                                  2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG3_L1_HEADER_PAT_9_8_BMSK                              0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_CFG3_L1_HEADER_PAT_9_8_SHFT                                0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE0_ADDR                                   (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xb0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE0_RMSK                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE0_L1_PRBS_SEED_7_0_BMSK                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE0_L1_PRBS_SEED_7_0_SHFT                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE1_ADDR                                   (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xb4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE1_RMSK                                          0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE1_L1_PRBS_SEED_9_8_BMSK                         0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_PRBS_SEED_BYTE1_L1_PRBS_SEED_9_8_SHFT                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN0_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xb8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN0_RMSK                                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN0_L1_PRBS_POLY_7_0_BMSK                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN0_L1_PRBS_POLY_7_0_SHFT                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN1_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xbc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN1_RMSK                                            0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN1_L1_PRBS_POLY_9_8_BMSK                           0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_PATTERN1_L1_PRBS_POLY_9_8_SHFT                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_CTRL_ADDR                                                 (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xc0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_CTRL_RMSK                                                        0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_CTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_CTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_CTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_CTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_CTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_CTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_CTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_CTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_CTRL_MISR_CLEAR_BMSK                                             0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_CTRL_MISR_CLEAR_SHFT                                               1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_CTRL_MISR_ENABLE_BMSK                                            0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_CTRL_MISR_ENABLE_SHFT                                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS_SEL_ADDR                                             (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xc4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS_SEL_RMSK                                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS_SEL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS_SEL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS_SEL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS_SEL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS_SEL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS_SEL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS_SEL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS_SEL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS_SEL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS_SEL_DEBUG_BUS_SEL_BMSK                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS_SEL_DEBUG_BUS_SEL_SHFT                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE0_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xc8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE0_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE0_EDPPHY_SPARE_7_0_BMSK                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE0_EDPPHY_SPARE_7_0_SHFT                                            0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE1_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xcc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE1_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE1_EDPPHY_SPARE_15_8_BMSK                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE1_EDPPHY_SPARE_15_8_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE2_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xd0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE2_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE2_EDPPHY_SPARE_23_16_BMSK                                       0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_SPARE2_EDPPHY_SPARE_23_16_SHFT                                          0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_ADDR                                                 (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xd4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_RMSK                                                       0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_RTB_DEBUG_UPDATE_MODE_BMSK                                 0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_RTB_DEBUG_UPDATE_MODE_SHFT                                    7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_RTB_DEBUG_LOW_LIMIT_BMSK                                   0x70
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_RTB_DEBUG_LOW_LIMIT_SHFT                                      4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_RTB_DEBUG_HIGH_LIMIT_BMSK                                   0xe
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_RTB_DEBUG_HIGH_LIMIT_SHFT                                     1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_RTB_DEBUG_ENABLE_BMSK                                       0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_DEBUG_RTB_DEBUG_ENABLE_SHFT                                         0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS1_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xd8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS1_RMSK                                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS1_RSVD_BMSK                                                0xe0
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS1_RSVD_SHFT                                                   5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS1_RTB_GAP_BMSK                                             0x1c
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS1_RTB_GAP_SHFT                                                2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS1_RTB_LOW_FLAG_BMSK                                         0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS1_RTB_LOW_FLAG_SHFT                                           1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS1_RTB_HIGH_FLAG_BMSK                                        0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS1_RTB_HIGH_FLAG_SHFT                                          0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS2_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xdc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS2_RMSK                                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS2_RTB_LOW_COUNTER_BMSK                                     0xf0
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS2_RTB_LOW_COUNTER_SHFT                                        4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS2_RTB_HIGH_COUNTER_BMSK                                     0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_RTB_STATUS2_RTB_HIGH_COUNTER_SHFT                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_STATUS_ADDR                                      (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xe0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_STATUS_RMSK                                            0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_STATUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_STATUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_STATUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_STATUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_STATUS_AUX_TX_REQ_ERR_BMSK                             0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_STATUS_AUX_TX_REQ_ERR_SHFT                                4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_STATUS_AUX_RX_ALIGN_ERR_BMSK                            0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_STATUS_AUX_RX_ALIGN_ERR_SHFT                              3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_STATUS_AUX_RX_SYNC_ERR_BMSK                             0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_STATUS_AUX_RX_SYNC_ERR_SHFT                               2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_STATUS_AUX_RX_DEC_ERR_BMSK                              0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_STATUS_AUX_RX_DEC_ERR_SHFT                                1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_STATUS_AUX_RX_STOP_ERR_BMSK                             0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_INTERRUPT_STATUS_AUX_RX_STOP_ERR_SHFT                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_STATUS_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xe4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_STATUS_RMSK                                                           0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_STATUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_STATUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_STATUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_STATUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_STATUS_C_READY_BMSK                                                   0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_STATUS_C_READY_SHFT                                                     2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_STATUS_PHY_READY_BMSK                                                 0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_STATUS_PHY_READY_SHFT                                                   1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_STATUS_TSYNC_DONE_BMSK                                                0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_STATUS_TSYNC_DONE_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS0_ADDR                                          (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xe8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS0_RMSK                                                 0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS0_AUX_BIST_CHECK_DONE_BMSK                             0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS0_AUX_BIST_CHECK_DONE_SHFT                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS1_ADDR                                          (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xec)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS1_RMSK                                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS1_AUX_BIST_ERROR_COUNT_7_0_BMSK                       0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS1_AUX_BIST_ERROR_COUNT_7_0_SHFT                          0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS2_ADDR                                          (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xf0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS2_RMSK                                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS2_AUX_BIST_ERROR_COUNT_15_8_BMSK                      0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_AUX_BIST_STATUS2_AUX_BIST_ERROR_COUNT_15_8_SHFT                         0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS0_ADDR                                      (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xf4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS0_RMSK                                             0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS0_L0_BIST_RXCHK_HEADER_SEL_BMSK                    0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS0_L0_BIST_RXCHK_HEADER_SEL_SHFT                      3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS0_L0_BIST_PAT_DATA_NOT_FOUND_BMSK                  0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS0_L0_BIST_PAT_DATA_NOT_FOUND_SHFT                    2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS0_L0_BIST_HEADER_NOT_FOUND_BMSK                    0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS0_L0_BIST_HEADER_NOT_FOUND_SHFT                      1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS0_L0_BIST_CHECK_DONE_BMSK                          0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS0_L0_BIST_CHECK_DONE_SHFT                            0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS1_ADDR                                      (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xf8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS1_RMSK                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS1_L0_BIST_ERROR_COUNT_7_0_BMSK                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS1_L0_BIST_ERROR_COUNT_7_0_SHFT                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS2_ADDR                                      (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0xfc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS2_RMSK                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS2_L0_BIST_ERROR_COUNT_15_8_BMSK                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_TX1_BIST_STATUS2_L0_BIST_ERROR_COUNT_15_8_SHFT                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS0_ADDR                                      (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x100)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS0_RMSK                                             0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS0_L1_BIST_RXCHK_HEADER_SEL_BMSK                    0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS0_L1_BIST_RXCHK_HEADER_SEL_SHFT                      3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS0_L1_BIST_PAT_DATA_NOT_FOUND_BMSK                  0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS0_L1_BIST_PAT_DATA_NOT_FOUND_SHFT                    2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS0_L1_BIST_HEADER_NOT_FOUND_BMSK                    0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS0_L1_BIST_HEADER_NOT_FOUND_SHFT                      1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS0_L1_BIST_CHECK_DONE_BMSK                          0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS0_L1_BIST_CHECK_DONE_SHFT                            0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS1_ADDR                                      (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x104)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS1_RMSK                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS1_L1_BIST_ERROR_COUNT_7_0_BMSK                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS1_L1_BIST_ERROR_COUNT_7_0_SHFT                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS2_ADDR                                      (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x108)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS2_RMSK                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS2_L1_BIST_ERROR_COUNT_15_8_BMSK                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_TX3_BIST_STATUS2_L1_BIST_ERROR_COUNT_15_8_SHFT                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_STATUS_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x10c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_STATUS_RMSK                                                      0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_STATUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_STATUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_STATUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_STATUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_STATUS_MISR_CAPTURED_BMSK                                        0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_MISR_STATUS_MISR_CAPTURED_SHFT                                          0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS000_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x110)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS000_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS000_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS000_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS000_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS000_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS000_L0_MISR_7_0_BMSK                                  0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS000_L0_MISR_7_0_SHFT                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS001_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x114)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS001_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS001_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS001_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS001_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS001_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS001_L0_MISR_15_8_BMSK                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS001_L0_MISR_15_8_SHFT                                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS010_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x118)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS010_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS010_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS010_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS010_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS010_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS010_L0_MISR_23_16_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS010_L0_MISR_23_16_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS011_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x11c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS011_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS011_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS011_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS011_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS011_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS011_L0_MISR_31_24_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS011_L0_MISR_31_24_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS100_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x120)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS100_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS100_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS100_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS100_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS100_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS100_L0_MISR_39_32_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS100_L0_MISR_39_32_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS101_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x124)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS101_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS101_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS101_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS101_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS101_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS101_L0_MISR_47_40_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS101_L0_MISR_47_40_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS110_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x128)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS110_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS110_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS110_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS110_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS110_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS110_L0_MISR_55_48_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS110_L0_MISR_55_48_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS111_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x12c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS111_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS111_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS111_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS111_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS111_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS111_L0_MISR_63_56_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX0_MISR_STATUS111_L0_MISR_63_56_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS000_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x130)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS000_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS000_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS000_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS000_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS000_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS000_L1_MISR_7_0_BMSK                                  0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS000_L1_MISR_7_0_SHFT                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS001_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x134)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS001_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS001_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS001_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS001_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS001_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS001_L1_MISR_15_8_BMSK                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS001_L1_MISR_15_8_SHFT                                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS010_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x138)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS010_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS010_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS010_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS010_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS010_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS010_L1_MISR_23_16_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS010_L1_MISR_23_16_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS011_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x13c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS011_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS011_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS011_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS011_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS011_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS011_L1_MISR_31_24_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS011_L1_MISR_31_24_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS100_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x140)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS100_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS100_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS100_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS100_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS100_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS100_L1_MISR_39_32_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS100_L1_MISR_39_32_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS101_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x144)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS101_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS101_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS101_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS101_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS101_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS101_L1_MISR_47_40_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS101_L1_MISR_47_40_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS110_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x148)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS110_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS110_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS110_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS110_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS110_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS110_L1_MISR_55_48_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS110_L1_MISR_55_48_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS111_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x14c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS111_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS111_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS111_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS111_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS111_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS111_L1_MISR_63_56_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX1_MISR_STATUS111_L1_MISR_63_56_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS000_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x150)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS000_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS000_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS000_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS000_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS000_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS000_L2_MISR_7_0_BMSK                                  0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS000_L2_MISR_7_0_SHFT                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS001_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x154)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS001_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS001_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS001_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS001_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS001_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS001_L2_MISR_15_8_BMSK                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS001_L2_MISR_15_8_SHFT                                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS010_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x158)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS010_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS010_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS010_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS010_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS010_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS010_L2_MISR_23_16_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS010_L2_MISR_23_16_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS011_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x15c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS011_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS011_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS011_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS011_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS011_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS011_L2_MISR_31_24_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS011_L2_MISR_31_24_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS100_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x160)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS100_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS100_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS100_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS100_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS100_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS100_L2_MISR_39_32_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS100_L2_MISR_39_32_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS101_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x164)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS101_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS101_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS101_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS101_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS101_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS101_L2_MISR_47_40_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS101_L2_MISR_47_40_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS110_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x168)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS110_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS110_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS110_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS110_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS110_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS110_L2_MISR_55_48_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS110_L2_MISR_55_48_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS111_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x16c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS111_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS111_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS111_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS111_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS111_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS111_L2_MISR_63_56_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX2_MISR_STATUS111_L2_MISR_63_56_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS000_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x170)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS000_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS000_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS000_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS000_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS000_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS000_L3_MISR_7_0_BMSK                                  0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS000_L3_MISR_7_0_SHFT                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS001_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x174)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS001_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS001_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS001_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS001_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS001_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS001_L3_MISR_15_8_BMSK                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS001_L3_MISR_15_8_SHFT                                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS010_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x178)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS010_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS010_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS010_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS010_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS010_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS010_L3_MISR_23_16_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS010_L3_MISR_23_16_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS011_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x17c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS011_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS011_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS011_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS011_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS011_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS011_L3_MISR_31_24_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS011_L3_MISR_31_24_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS100_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x180)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS100_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS100_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS100_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS100_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS100_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS100_L3_MISR_39_32_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS100_L3_MISR_39_32_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS101_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x184)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS101_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS101_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS101_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS101_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS101_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS101_L3_MISR_47_40_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS101_L3_MISR_47_40_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS110_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x188)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS110_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS110_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS110_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS110_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS110_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS110_L3_MISR_55_48_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS110_L3_MISR_55_48_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS111_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x18c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS111_RMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS111_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS111_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS111_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS111_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS111_L3_MISR_63_56_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_TX3_MISR_STATUS111_L3_MISR_63_56_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS0_ADDR                                                (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x190)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS0_RMSK                                                      0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS0_DEBUG_BUS_7_0_BMSK                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS0_DEBUG_BUS_7_0_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS1_ADDR                                                (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x194)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS1_RMSK                                                      0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS1_DEBUG_BUS_15_8_BMSK                                       0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS1_DEBUG_BUS_15_8_SHFT                                          0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS2_ADDR                                                (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x198)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS2_RMSK                                                      0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS2_DEBUG_BUS_23_16_BMSK                                      0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS2_DEBUG_BUS_23_16_SHFT                                         0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS3_ADDR                                                (AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_USB4PHY_DP_PHY_REG_BASE      + 0x19c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS3_RMSK                                                      0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS3_DEBUG_BUS_31_24_BMSK                                      0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_DP_PHY_DEBUG_BUS3_DEBUG_BUS_31_24_SHFT                                         0

/*----------------------------------------------------------------------------
 * MODULE: AHB2PHY_1_QUSB4PHY_SS_1_QUSB4PHY_SS_1_CM_USB4_USB3_EDP_DP_CON
 *--------------------------------------------------------------------------*/

#define AHB2PHY_1_QUSB4PHY_SS_1_QUSB4PHY_SS_1_CM_USB4_USB3_EDP_DP_CON_REG_BASE (AHB2PHY_1_AHB2PHY_1_BASE      + 0x0000a000)
#define AHB2PHY_1_QUSB4PHY_SS_1_QUSB4PHY_SS_1_CM_USB4_USB3_EDP_DP_CON_REG_BASE_SIZE 0x4000
#define AHB2PHY_1_QUSB4PHY_SS_1_QUSB4PHY_SS_1_CM_USB4_USB3_EDP_DP_CON_REG_BASE_USED 0x0

/*----------------------------------------------------------------------------
 * MODULE: AHB2PHY_1_QUSB4PHY_SS_2_QUSB4PHY_SS_2_CM_USB4_USB3_EDP_DP_CON
 *--------------------------------------------------------------------------*/

#define AHB2PHY_1_QUSB4PHY_SS_2_QUSB4PHY_SS_2_CM_USB4_USB3_EDP_DP_CON_REG_BASE (AHB2PHY_1_AHB2PHY_1_BASE      + 0x0000f000)
#define AHB2PHY_1_QUSB4PHY_SS_2_QUSB4PHY_SS_2_CM_USB4_USB3_EDP_DP_CON_REG_BASE_SIZE 0x4000
#define AHB2PHY_1_QUSB4PHY_SS_2_QUSB4PHY_SS_2_CM_USB4_USB3_EDP_DP_CON_REG_BASE_USED 0x0

/*----------------------------------------------------------------------------
 * MODULE: AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL
 *--------------------------------------------------------------------------*/

#define AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE                                      (AHB2PHY_1_AHB2PHY_1_BASE      + 0x00007000)
#define AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE_SIZE                                 0x200
#define AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE_USED                                 0x1fc

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE1_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE1_RMSK                                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE1_SSC_STEPSIZE_MODE1_7_0_BMSK                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE1_SSC_STEPSIZE_MODE1_7_0_SHFT                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE1_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE1_RMSK                                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE1_SSC_STEPSIZE_MODE1_15_8_BMSK                             0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE1_SSC_STEPSIZE_MODE1_15_8_SHFT                                0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE1_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE1_RMSK                                                      0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE1_SSC_STEPSIZE_MODE1_16_16_BMSK                             0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE1_SSC_STEPSIZE_MODE1_16_16_SHFT                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE1_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE1_RMSK                                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE1_CLK_EP_DIV_MODE1_BMSK                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE1_CLK_EP_DIV_MODE1_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE1_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x10)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE1_RMSK                                                            0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE1_PLL_CPCTRL_MODE1_BMSK                                           0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE1_PLL_CPCTRL_MODE1_SHFT                                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE1_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x14)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE1_RMSK                                                          0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE1_PLL_RCTRL_MODE1_BMSK                                          0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE1_PLL_RCTRL_MODE1_SHFT                                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE1_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x18)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE1_RMSK                                                          0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE1_PLL_CCTRL_MODE1_BMSK                                          0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE1_PLL_CCTRL_MODE1_SHFT                                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE1_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE1_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE1_CORE_CLK_DIV_MODE1_BMSK                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE1_CORE_CLK_DIV_MODE1_SHFT                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE1_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x20)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE1_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE1_PLLLOCK_CMP_MODE1_7_0_BMSK                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE1_PLLLOCK_CMP_MODE1_7_0_SHFT                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE1_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x24)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE1_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE1_PLLLOCK_CMP_MODE1_15_8_BMSK                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE1_PLLLOCK_CMP_MODE1_15_8_SHFT                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE1_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x28)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE1_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE1_DEC_START_MODE1_7_0_BMSK                                      0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE1_DEC_START_MODE1_7_0_SHFT                                         0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE1_ADDR                                                (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x2c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE1_RMSK                                                       0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE1_DEC_START_MODE1_8_8_BMSK                                   0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE1_DEC_START_MODE1_8_8_SHFT                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE1_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x30)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE1_RMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE1_DIV_FRAC_START_MODE1_7_0_BMSK                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE1_DIV_FRAC_START_MODE1_7_0_SHFT                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE1_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x34)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE1_RMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE1_DIV_FRAC_START_MODE1_15_8_BMSK                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE1_DIV_FRAC_START_MODE1_15_8_SHFT                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE1_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x38)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE1_RMSK                                                     0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE1_DIV_FRAC_START_MODE1_19_16_BMSK                          0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE1_DIV_FRAC_START_MODE1_19_16_SHFT                            0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_SEL_1_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x3c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_SEL_1_RMSK                                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_SEL_1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_SEL_1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_SEL_1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_SEL_1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_SEL_1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_SEL_1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_SEL_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_SEL_1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_SEL_1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_SEL_1_HSCLK_DIVSEL_MODE1_BMSK                                           0xf0
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_SEL_1_HSCLK_DIVSEL_MODE1_SHFT                                              4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_SEL_1_HSCLK_DIVSEL_MODE0_BMSK                                            0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_SEL_1_HSCLK_DIVSEL_MODE0_SHFT                                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE1_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x40)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE1_RMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE1_INTEGLOOP_GAIN_MODE1_7_0_BMSK                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE1_INTEGLOOP_GAIN_MODE1_7_0_SHFT                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE1_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x44)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE1_RMSK                                                     0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE1_INTEGLOOP_GAIN_MODE1_11_8_BMSK                           0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE1_INTEGLOOP_GAIN_MODE1_11_8_SHFT                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE1_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x48)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE1_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE1_PLL_VCOTUNE_MODE1_7_0_BMSK                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE1_PLL_VCOTUNE_MODE1_7_0_SHFT                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE1_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x4c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE1_RMSK                                                           0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE1_PLL_VCOTUNE_MODE1_9_8_BMSK                                     0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE1_PLL_VCOTUNE_MODE1_9_8_SHFT                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE1_ADDR                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x50)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE1_RMSK                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE1_BIN_VCOCAL_MEAS_CNT_MODE1_7_0_BMSK                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE1_BIN_VCOCAL_MEAS_CNT_MODE1_7_0_SHFT                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE1_ADDR                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x54)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE1_RMSK                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE1_BIN_VCOCAL_MEAS_CNT_MODE1_15_8_BMSK                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE1_BIN_VCOCAL_MEAS_CNT_MODE1_15_8_SHFT                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE0_ADDR                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x58)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE0_RMSK                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE0_BIN_VCOCAL_MEAS_CNT_MODE0_7_0_BMSK                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE1_MODE0_BIN_VCOCAL_MEAS_CNT_MODE0_7_0_SHFT                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE0_ADDR                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x5c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE0_RMSK                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE0_BIN_VCOCAL_MEAS_CNT_MODE0_15_8_BMSK                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_CMP_CODE2_MODE0_BIN_VCOCAL_MEAS_CNT_MODE0_15_8_SHFT                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x60)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0_RMSK                                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0_SSC_STEPSIZE_MODE0_7_0_BMSK                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE1_MODE0_SSC_STEPSIZE_MODE0_7_0_SHFT                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x64)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0_RMSK                                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0_SSC_STEPSIZE_MODE0_15_8_BMSK                             0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE2_MODE0_SSC_STEPSIZE_MODE0_15_8_SHFT                                0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE0_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x68)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE0_RMSK                                                      0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE0_SSC_STEPSIZE_MODE0_16_16_BMSK                             0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_STEP_SIZE3_MODE0_SSC_STEPSIZE_MODE0_16_16_SHFT                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE0_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x6c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE0_RMSK                                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE0_CLK_EP_DIV_MODE0_BMSK                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_EP_DIV_MODE0_CLK_EP_DIV_MODE0_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE0_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x70)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE0_RMSK                                                            0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE0_PLL_CPCTRL_MODE0_BMSK                                           0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CP_CTRL_MODE0_PLL_CPCTRL_MODE0_SHFT                                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE0_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x74)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE0_RMSK                                                          0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE0_PLL_RCTRL_MODE0_BMSK                                          0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_RCTRL_MODE0_PLL_RCTRL_MODE0_SHFT                                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE0_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x78)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE0_RMSK                                                          0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE0_PLL_CCTRL_MODE0_BMSK                                          0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CCTRL_MODE0_PLL_CCTRL_MODE0_SHFT                                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE0_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x7c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE0_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE0_CORE_CLK_DIV_MODE0_BMSK                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORECLK_DIV_MODE0_CORE_CLK_DIV_MODE0_SHFT                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE0_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x80)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE0_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE0_PLLLOCK_CMP_MODE0_7_0_BMSK                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP1_MODE0_PLLLOCK_CMP_MODE0_7_0_SHFT                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE0_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x84)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE0_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE0_PLLLOCK_CMP_MODE0_15_8_BMSK                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP2_MODE0_PLLLOCK_CMP_MODE0_15_8_SHFT                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE0_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x88)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE0_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE0_DEC_START_MODE0_7_0_BMSK                                      0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MODE0_DEC_START_MODE0_7_0_SHFT                                         0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE0_ADDR                                                (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x8c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE0_RMSK                                                       0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE0_DEC_START_MODE0_8_8_BMSK                                   0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEC_START_MSB_MODE0_DEC_START_MODE0_8_8_SHFT                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE0_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x90)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE0_RMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE0_DIV_FRAC_START_MODE0_7_0_BMSK                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START1_MODE0_DIV_FRAC_START_MODE0_7_0_SHFT                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE0_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x94)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE0_RMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE0_DIV_FRAC_START_MODE0_15_8_BMSK                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START2_MODE0_DIV_FRAC_START_MODE0_15_8_SHFT                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE0_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x98)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE0_RMSK                                                     0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE0_DIV_FRAC_START_MODE0_19_16_BMSK                          0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DIV_FRAC_START3_MODE0_DIV_FRAC_START_MODE0_19_16_SHFT                            0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_HS_SWITCH_SEL_1_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x9c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_HS_SWITCH_SEL_1_RMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_HS_SWITCH_SEL_1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_HS_SWITCH_SEL_1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_HS_SWITCH_SEL_1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_HS_SWITCH_SEL_1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_HS_SWITCH_SEL_1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_HS_SWITCH_SEL_1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_HS_SWITCH_SEL_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_HS_SWITCH_SEL_1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_HS_SWITCH_SEL_1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_HS_SWITCH_SEL_1_HSCLK_SWITCH_DIVSEL_MODE1_BMSK                          0xf0
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_HS_SWITCH_SEL_1_HSCLK_SWITCH_DIVSEL_MODE1_SHFT                             4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_HS_SWITCH_SEL_1_HSCLK_SWITCH_DIVSEL_MODE0_BMSK                           0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_HSCLK_HS_SWITCH_SEL_1_HSCLK_SWITCH_DIVSEL_MODE0_SHFT                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE0_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xa0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE0_RMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE0_INTEGLOOP_GAIN_MODE0_7_0_BMSK                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN0_MODE0_INTEGLOOP_GAIN_MODE0_7_0_SHFT                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE0_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xa4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE0_RMSK                                                     0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE0_INTEGLOOP_GAIN_MODE0_11_8_BMSK                           0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_GAIN1_MODE0_INTEGLOOP_GAIN_MODE0_11_8_SHFT                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE0_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xa8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE0_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE0_PLL_VCOTUNE_MODE0_7_0_BMSK                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE1_MODE0_PLL_VCOTUNE_MODE0_7_0_SHFT                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE0_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xac)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE0_RMSK                                                           0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE0_PLL_VCOTUNE_MODE0_9_8_BMSK                                     0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE2_MODE0_PLL_VCOTUNE_MODE0_9_8_SHFT                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL1_ADDR                                                           (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xb0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL1_RMSK                                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL1_ATB_SEL_7_0_BMSK                                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL1_ATB_SEL_7_0_SHFT                                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL2_ADDR                                                           (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xb4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL2_RMSK                                                                  0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL2_ATB_SEL_10_8_BMSK                                                     0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ATB_SEL2_ATB_SEL_10_8_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_FREQ_UPDATE_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xb8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_FREQ_UPDATE_RMSK                                                               0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_FREQ_UPDATE_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_FREQ_UPDATE_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_FREQ_UPDATE_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_FREQ_UPDATE_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_FREQ_UPDATE_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_FREQ_UPDATE_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_FREQ_UPDATE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_FREQ_UPDATE_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_FREQ_UPDATE_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_FREQ_UPDATE_PLL_FREQ_UPDATE_BMSK                                               0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_FREQ_UPDATE_PLL_FREQ_UPDATE_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_ADDR                                                           (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xbc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_RMSK                                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_SYSCLK_WAKE_BYPASS_BMSK                                              0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_SYSCLK_WAKE_BYPASS_SHFT                                                 7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_SYSCLK_WAKE_TIME_BMSK                                                0x70
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_SYSCLK_WAKE_TIME_SHFT                                                   4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_REFCLK_FREQ_SEL_BMSK                                                  0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_REFCLK_FREQ_SEL_SHFT                                                    3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_REFCLK_FREQ_SEL_LEGACY_BMSK                                           0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_REFCLK_FREQ_SEL_LEGACY_SHFT                                             2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_BIAS_WAIT_TIME_BMSK                                                   0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BG_TIMER_BIAS_WAIT_TIME_SHFT                                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_EN_CENTER_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xc0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_EN_CENTER_RMSK                                                             0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_EN_CENTER_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_EN_CENTER_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_EN_CENTER_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_EN_CENTER_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_EN_CENTER_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_EN_CENTER_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_EN_CENTER_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_EN_CENTER_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_EN_CENTER_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_EN_CENTER_SSC_CENTER_BMSK                                                  0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_EN_CENTER_SSC_CENTER_SHFT                                                    1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_EN_CENTER_SSC_EN_BMSK                                                      0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_EN_CENTER_SSC_EN_SHFT                                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER1_ADDR                                                       (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xc4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER1_RMSK                                                             0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER1_SSC_ADJPER_7_0_BMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER1_SSC_ADJPER_7_0_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER2_ADDR                                                       (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xc8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER2_RMSK                                                              0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER2_SSC_ADJPER_9_8_BMSK                                               0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_ADJ_PER2_SSC_ADJPER_9_8_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER1_ADDR                                                           (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xcc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER1_RMSK                                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER1_SSC_PER_7_0_BMSK                                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER1_SSC_PER_7_0_SHFT                                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER2_ADDR                                                           (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xd0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER2_RMSK                                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER2_SSC_PER_15_8_BMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SSC_PER2_SSC_PER_15_8_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_ADDR                                                           (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xd4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_RMSK                                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_PLL_POSTDIV_7_0_BMSK                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_PLL_POSTDIV_7_0_SHFT                                                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_ADDR                                                       (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xd8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_RMSK                                                             0xf1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_HS_SWITCH_CLKS_PLL_DIVSEL_MODE2_BMSK                             0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_HS_SWITCH_CLKS_PLL_DIVSEL_MODE2_SHFT                                7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_HS_SWITCH_CLKS_PLL_DIVSEL_MODE1_BMSK                             0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_HS_SWITCH_CLKS_PLL_DIVSEL_MODE1_SHFT                                6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_HS_SWITCH_CLKS_PLL_DIVSEL_MODE0_BMSK                             0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_HS_SWITCH_CLKS_PLL_DIVSEL_MODE0_SHFT                                5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_PLL_POSTDIV_MUX_BMSK                                             0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_PLL_POSTDIV_MUX_SHFT                                                4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_PLL_POSTDIV_8_8_BMSK                                              0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_POST_DIV_MUX_PLL_POSTDIV_8_8_SHFT                                                0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_ADDR                                                (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xdc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_RMSK                                                      0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_EN_SYSCLK_TX_SEL_BMSK                                     0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_EN_SYSCLK_TX_SEL_SHFT                                        4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_CLKBUF_L_EN_BMSK                                           0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_CLKBUF_L_EN_SHFT                                             3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_CLKBUF_R_EN_BMSK                                           0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_CLKBUF_R_EN_SHFT                                             2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_BIAS_EN_MUX_BMSK                                           0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_BIAS_EN_MUX_SHFT                                             1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_BIAS_EN_BMSK                                               0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CLKBUFLR_EN_BIAS_EN_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xe0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_RMSK                                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_CLKDRVIDLE_EN_BMSK                                                0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_CLKDRVIDLE_EN_SHFT                                                   7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_EN_SYSCLK_TX_PS3PS4_BMSK                                          0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_EN_SYSCLK_TX_PS3PS4_SHFT                                             6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_EN_SYSCLK_TX_PS0PS1PS2_BMSK                                       0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_EN_SYSCLK_TX_PS0PS1PS2_SHFT                                          5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_CLK_EP_EN_BMSK                                                    0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_CLK_EP_EN_SHFT                                                       4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_PLL_CLKOUT_EN_MUX_BMSK                                             0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_PLL_CLKOUT_EN_MUX_SHFT                                               3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_PLL_CLKOUT_EN_BMSK                                                 0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_PLL_CLKOUT_EN_SHFT                                                   2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_EXT_CLKBUF_EN_MUX_BMSK                                             0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_EXT_CLKBUF_EN_MUX_SHFT                                               1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_EXT_CLKBUF_EN_BMSK                                                 0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_ENABLE1_EXT_CLKBUF_EN_SHFT                                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_ADDR                                                       (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xe4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_RMSK                                                             0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_CLK_EP_EN_MUX_BMSK                                               0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_CLK_EP_EN_MUX_SHFT                                                  7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_EP_GLITCHFREE_BYPASS_BMSK                                        0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_EP_GLITCHFREE_BYPASS_SHFT                                           6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_SYSCLK_TX_SYSCLKSEL_MUX_BMSK                                     0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_SYSCLK_TX_SYSCLKSEL_MUX_SHFT                                        5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_SYSCLK_TX_SYSCLKSEL_BMSK                                         0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_SYSCLK_TX_SYSCLKSEL_SHFT                                            4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_SYSCLK_DIV2_SEL_BMSK                                              0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_SYSCLK_DIV2_SEL_SHFT                                                3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_SYSCLK_CM_BMSK                                                    0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_SYSCLK_CM_SHFT                                                      2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_SYSCLK_AC_COUPLE_BMSK                                             0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_SYSCLK_AC_COUPLE_SHFT                                               1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_SYSCLK_GNDTERM_BMSK                                               0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYS_CLK_CTRL_SYSCLK_GNDTERM_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xe8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_RMSK                                                         0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_SYSCLK_EN_CTRL_BY_PSM_BMSK                                   0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_SYSCLK_EN_CTRL_BY_PSM_SHFT                                     3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_SYSCLK_EN_PS3PS4_BMSK                                        0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_SYSCLK_EN_PS3PS4_SHFT                                          2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_SYSCLK_BUF_EN_MUX_BMSK                                       0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_SYSCLK_BUF_EN_MUX_SHFT                                         1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_SW_SYSCLK_BUF_EN_BMSK                                        0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_BUF_ENABLE_SW_SYSCLK_BUF_EN_SHFT                                          0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_EN_ADDR                                                             (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xec)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_EN_RMSK                                                                    0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_EN_PLL_EN_MUX_BMSK                                                         0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_EN_PLL_EN_MUX_SHFT                                                           1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_EN_PLL_EN_BMSK                                                             0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_EN_PLL_EN_SHFT                                                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_OVRD_ADDR                                                     (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xf0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_OVRD_RMSK                                                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_OVRD_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_OVRD_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_OVRD_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_OVRD_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_OVRD_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_OVRD_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_OVRD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_OVRD_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_OVRD_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_OVRD_DEBUG_BUS_OVRD_BMSK                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_OVRD_DEBUG_BUS_OVRD_SHFT                                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_ADDR                                                           (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xf4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_RMSK                                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_PLL_IVCO_BMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_PLL_IVCO_SHFT                                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_MODE1_ADDR                                                     (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xf8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_MODE1_RMSK                                                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_MODE1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_MODE1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_MODE1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_MODE1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_MODE1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_MODE1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_MODE1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_MODE1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_MODE1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_MODE1_PLL_IVCO_MODE1_BMSK                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_IVCO_MODE1_PLL_IVCO_MODE1_SHFT                                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IETRIM_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0xfc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IETRIM_RMSK                                                               0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IETRIM_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IETRIM_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IETRIM_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IETRIM_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IETRIM_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IETRIM_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IETRIM_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IETRIM_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IETRIM_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IETRIM_IETRIM_BMSK                                                        0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IETRIM_IETRIM_SHFT                                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IPTRIM_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x100)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IPTRIM_RMSK                                                               0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IPTRIM_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IPTRIM_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IPTRIM_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IPTRIM_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IPTRIM_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IPTRIM_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IPTRIM_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IPTRIM_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IPTRIM_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IPTRIM_IPTRIM_BMSK                                                        0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_IPTRIM_IPTRIM_SHFT                                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x104)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_RMSK                                                     0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_DIVSEL_MUX_BMSK                            0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_DIVSEL_MUX_SHFT                               5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_DIVSEL_BMSK                                0x18
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_DIVSEL_SHFT                                   3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_FORCE_BMSK                                  0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_FORCE_SHFT                                    2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_EN_MUX_BMSK                                 0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_EN_MUX_SHFT                                   1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_EN_BMSK                                     0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_EP_CLOCK_DETECT_CTRL_SYSCLK_CLKDET_EN_SHFT                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_ADDR                                                          (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x108)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_RMSK                                                                0x7f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_PLL_STABLE_TIME_BMSK                                                0x60
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_PLL_STABLE_TIME_SHFT                                                   5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_MASH_RESET_MUX_BMSK                                                 0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_MASH_RESET_MUX_SHFT                                                    4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_MASH_RESET_BMSK                                                      0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_MASH_RESET_SHFT                                                        3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_PLL_CPLIN_BMSK                                                       0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_PLL_CPLIN_SHFT                                                         2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_PLL_DIV_FFEN_BMSK                                                    0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_PLL_DIV_FFEN_SHFT                                                      1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_PLL_DIV_ORD_BMSK                                                     0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_CNTRL_PLL_DIV_ORD_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CTRL_BY_PSM_ADDR                                                (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x10c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CTRL_BY_PSM_RMSK                                                       0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CTRL_BY_PSM_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CTRL_BY_PSM_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CTRL_BY_PSM_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CTRL_BY_PSM_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CTRL_BY_PSM_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CTRL_BY_PSM_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CTRL_BY_PSM_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CTRL_BY_PSM_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CTRL_BY_PSM_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CTRL_BY_PSM_BIAS_EN_CTRL_BY_PSM_BMSK                                   0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIAS_EN_CTRL_BY_PSM_BIAS_EN_CTRL_BY_PSM_SHFT                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x110)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_RMSK                                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_CML_SYSCLK_SEL_BMSK                                             0xe0
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_CML_SYSCLK_SEL_SHFT                                                5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_SYSCLK_TERM_SEL_BMSK                                            0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_SYSCLK_TERM_SEL_SHFT                                               4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_SYSCLK_SEL_BMSK                                                  0xc
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_SYSCLK_SEL_SHFT                                                    2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_SYSCLK_EN_MUX_BMSK                                               0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_SYSCLK_EN_MUX_SHFT                                                 1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_SYSCLK_EN_BMSK                                                   0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_EN_SEL_SYSCLK_EN_SHFT                                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CML_SYSCLK_SEL_ADDR                                                     (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x114)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CML_SYSCLK_SEL_RMSK                                                            0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CML_SYSCLK_SEL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CML_SYSCLK_SEL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CML_SYSCLK_SEL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CML_SYSCLK_SEL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CML_SYSCLK_SEL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CML_SYSCLK_SEL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CML_SYSCLK_SEL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CML_SYSCLK_SEL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CML_SYSCLK_SEL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CML_SYSCLK_SEL_CML_SYSCLK_SEL_MUX_BMSK                                         0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CML_SYSCLK_SEL_CML_SYSCLK_SEL_MUX_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x118)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_RMSK                                                            0x7f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_FORCE_C_READY_BMSK                                              0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_FORCE_C_READY_SHFT                                                 6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_TSYNC_SEL_BMSK                                                  0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_TSYNC_SEL_SHFT                                                     5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_DISABLE_CLKGATE_BMSK                                            0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_DISABLE_CLKGATE_SHFT                                               4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_PLL_UNLOCK_DISABLE_BMSK                                          0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_PLL_UNLOCK_DISABLE_SHFT                                            3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_RSM_START_MUX_BMSK                                               0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_RSM_START_MUX_SHFT                                                 2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_RSM_START_BMSK                                                   0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_RSM_START_SHFT                                                     1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_FORCE_PLLLOCK_BMSK                                               0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL_FORCE_PLLLOCK_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_ADDR                                                     (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x11c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_RMSK                                                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_CORE_PLL_EN_MUX_BMSK                                           0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_CORE_PLL_EN_MUX_SHFT                                              7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_CORE_PLL_EN_BMSK                                               0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_CORE_PLL_EN_SHFT                                                  6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_BYPASS_RSM_BIAS_BMSK                                           0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_BYPASS_RSM_BIAS_SHFT                                              5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_BYPASS_RSM_INTEGLOOP_CAL_BMSK                                  0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_BYPASS_RSM_INTEGLOOP_CAL_SHFT                                     4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_TSYNC_PULSE_WIDTH_BMSK                                          0xc
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_TSYNC_PULSE_WIDTH_SHFT                                            2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_TSYNC_MUX_BMSK                                                  0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_TSYNC_MUX_SHFT                                                    1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_TSYNC_BMSK                                                      0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESETSM_CNTRL2_TSYNC_SHFT                                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x120)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_RMSK                                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_PLLLOCK_RNG_2_BMSK                                                0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_PLLLOCK_RNG_2_SHFT                                                   7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_PLLLOCK_CNT_2_BMSK                                                0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_PLLLOCK_CNT_2_SHFT                                                   6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_PLLLOCK_EN_MUX_BMSK                                               0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_PLLLOCK_EN_MUX_SHFT                                                  5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_PLLLOCK_EN_BMSK                                                   0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_PLLLOCK_EN_SHFT                                                      4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_PLLLOCK_RNG_BMSK                                                   0xc
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_PLLLOCK_RNG_SHFT                                                     2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_PLLLOCK_CNT_BMSK                                                   0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_EN_PLLLOCK_CNT_SHFT                                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_ADDR                                                       (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x124)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_RMSK                                                             0x7f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_LOCK_DETECT_SPEEDUP_EN_BMSK                                      0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_LOCK_DETECT_SPEEDUP_EN_SHFT                                         6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_LOCK_DETECT_SPEEDUP_BY_4_BMSK                                    0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_LOCK_DETECT_SPEEDUP_BY_4_SHFT                                       5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_PLLLOCK_INIT_POINT_CNT_BMSK                                      0x18
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_PLLLOCK_INIT_POINT_CNT_SHFT                                         3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_PLLLOCK_RNG_UPDATE_DISABLE_BMSK                                   0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_PLLLOCK_RNG_UPDATE_DISABLE_SHFT                                     2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_PLLLOCK_STOP_COUNT_BMSK                                           0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_PLLLOCK_STOP_COUNT_SHFT                                             1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_BYP_PLLLOCK_BMSK                                                  0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_LOCK_CMP_CFG_BYP_PLLLOCK_SHFT                                                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_INITVAL_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x128)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_INITVAL_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_INITVAL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_INITVAL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_INITVAL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_INITVAL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_INITVAL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_INITVAL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_INITVAL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_INITVAL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_INITVAL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_INITVAL_INTEGLOOP_INITVAL_BMSK                                      0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_INITVAL_INTEGLOOP_INITVAL_SHFT                                         0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_ADDR                                                       (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x12c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_RMSK                                                              0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_P_GAIN_SIGN_FLIP_BMSK                                             0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_P_GAIN_SIGN_FLIP_SHFT                                               3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_INTEGLOOP_CODE_BYPASS_BMSK                                        0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_INTEGLOOP_CODE_BYPASS_SHFT                                          2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_INTEGLOOP_EN_MUX_BMSK                                             0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_INTEGLOOP_EN_MUX_SHFT                                               1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_INTEGLOOP_EN_BMSK                                                 0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_EN_INTEGLOOP_EN_SHFT                                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN0_ADDR                                             (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x130)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN0_RMSK                                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN0_INTEGLOOP_P_GAIN_7_0_BMSK                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN0_INTEGLOOP_P_GAIN_7_0_SHFT                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN1_ADDR                                             (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x134)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN1_RMSK                                                    0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN1_INTEGLOOP_P_GAIN_9_8_BMSK                               0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_P_PATH_GAIN1_INTEGLOOP_P_GAIN_9_8_SHFT                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_ADDR                                                (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x138)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_RMSK                                                      0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_FBCLK_TOO_SLOW_CNTSEL_BMSK                                0x18
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_FBCLK_TOO_SLOW_CNTSEL_SHFT                                   3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_FORCE_CORRECT_POL_BMSK                                     0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_FORCE_CORRECT_POL_SHFT                                       2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_FBCLK_DEAD_CORRECT_EN_BMSK                                 0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_FBCLK_DEAD_CORRECT_EN_SHFT                                   1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_FBCLK_DEAD_TIME_BMSK                                       0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCOCAL_DEADMAN_CTRL_FBCLK_DEAD_TIME_SHFT                                         0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x13c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_RMSK                                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_BIN_VCOCAL_FORCE_DONE_BMSK                                      0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_BIN_VCOCAL_FORCE_DONE_SHFT                                         7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_VCOCAL_TYPE_SEL_BMSK                                            0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_VCOCAL_TYPE_SEL_SHFT                                               6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_VCOCAL_POS_SLOPE_BMSK                                           0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_VCOCAL_POS_SLOPE_SHFT                                              5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_BYP_VCOCAL_MODE2_BMSK                                           0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_BYP_VCOCAL_MODE2_SHFT                                              4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_BYP_VCOCAL_MODE1_BMSK                                            0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_BYP_VCOCAL_MODE1_SHFT                                              3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_BYP_VCOCAL_MODE0_BMSK                                            0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_BYP_VCOCAL_MODE0_SHFT                                              2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_VCO_TUNE_EN_MUX_BMSK                                             0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_VCO_TUNE_EN_MUX_SHFT                                               1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_VCO_TUNE_EN_BMSK                                                 0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_CTRL_VCO_TUNE_EN_SHFT                                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_ADDR                                                       (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x140)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_RMSK                                                             0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_VCO_DEFAULT_FREQ_BMSK                                            0xc0
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_VCO_DEFAULT_FREQ_SHFT                                               6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_MAP_LANE_PS0C_BMSK                                               0x30
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_MAP_LANE_PS0C_SHFT                                                  4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_MAP_LANE_PS0B_BMSK                                                0xc
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_MAP_LANE_PS0B_SHFT                                                  2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_MAP_LANE_PS0A_BMSK                                                0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAP_MAP_LANE_PS0A_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL1_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x144)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL1_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL1_VCO_TUNE_INITVAL_7_0_BMSK                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL1_VCO_TUNE_INITVAL_7_0_SHFT                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL2_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x148)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL2_RMSK                                                         0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL2_VCO_TUNE_INITVAL_9_8_BMSK                                    0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_INITVAL2_VCO_TUNE_INITVAL_9_8_SHFT                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL1_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x14c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL1_RMSK                                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL1_VCO_TUNE_MINVAL_7_0_BMSK                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL1_VCO_TUNE_MINVAL_7_0_SHFT                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL2_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x150)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL2_RMSK                                                          0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL2_VCO_TUNE_MINVAL_9_8_BMSK                                      0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MINVAL2_VCO_TUNE_MINVAL_9_8_SHFT                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL1_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x154)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL1_RMSK                                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL1_VCO_TUNE_MAXVAL_7_0_BMSK                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL1_VCO_TUNE_MAXVAL_7_0_SHFT                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL2_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x158)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL2_RMSK                                                          0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL2_VCO_TUNE_MAXVAL_9_8_BMSK                                      0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_MAXVAL2_VCO_TUNE_MAXVAL_9_8_SHFT                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER1_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x15c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER1_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER1_PLL_VCOTUNE_TIMER_7_0_BMSK                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER1_PLL_VCOTUNE_TIMER_7_0_SHFT                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER2_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x160)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER2_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER2_PLL_VCOTUNE_TIMER_15_8_BMSK                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_TUNE_TIMER2_PLL_VCOTUNE_TIMER_15_8_SHFT                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x164)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_REFCLK_DRV_EN_MUX_BMSK                                             0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_REFCLK_DRV_EN_MUX_SHFT                                                7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_REFCLK_DRV_EN_BMSK                                                 0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_REFCLK_DRV_EN_SHFT                                                    6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_TSYNC_EN_MUX_BMSK                                                  0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_TSYNC_EN_MUX_SHFT                                                     5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_TSYNC_EN_BMSK                                                      0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_TSYNC_EN_SHFT                                                         4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_SYSCLK_CMOS_PAD_SEL_BMSK                                            0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_SYSCLK_CMOS_PAD_SEL_SHFT                                              3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_SYSCLK_TX_SWINGSEL_BMSK                                             0x6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_SYSCLK_TX_SWINGSEL_SHFT                                               1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_EP_REFCLK_SEL_BMSK                                                  0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CLK_SELECT_EP_REFCLK_SEL_SHFT                                                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_ANALOG_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x168)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_ANALOG_RMSK                                                                0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_ANALOG_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_ANALOG_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_ANALOG_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_ANALOG_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_ANALOG_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_ANALOG_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_ANALOG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_ANALOG_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_ANALOG_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_ANALOG_PLL_ANALOG_BMSK                                                     0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLL_ANALOG_PLL_ANALOG_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SW_RESET_ADDR                                                           (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x16c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SW_RESET_RMSK                                                                  0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SW_RESET_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SW_RESET_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SW_RESET_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SW_RESET_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SW_RESET_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SW_RESET_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SW_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SW_RESET_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SW_RESET_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SW_RESET_SW_RESET_BMSK                                                         0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SW_RESET_SW_RESET_SHFT                                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x170)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_RMSK                                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_ENABLE_INTERNAL_CORECLK_DIV2_RATIO_BMSK                           0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_ENABLE_INTERNAL_CORECLK_DIV2_RATIO_SHFT                              7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_CLKS_PLL_DIVSEL_MODE2_BMSK                                        0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_CLKS_PLL_DIVSEL_MODE2_SHFT                                           6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_CLKS_PLL_DIVSEL_MODE1_BMSK                                        0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_CLKS_PLL_DIVSEL_MODE1_SHFT                                           5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_CLKS_PLL_DIVSEL_MODE0_BMSK                                        0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_CLKS_PLL_DIVSEL_MODE0_SHFT                                           4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_CORECLK_EN_MUX_BMSK                                                0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_CORECLK_EN_MUX_SHFT                                                  3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_CORECLK_EN_BMSK                                                    0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_CORECLK_EN_SHFT                                                      2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_AUXCLK_EN_MUX_BMSK                                                 0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_AUXCLK_EN_MUX_SHFT                                                   1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_AUXCLK_EN_BMSK                                                     0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CORE_CLK_EN_AUXCLK_EN_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_ADDR                                                       (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x174)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_RMSK                                                             0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_PLL_FBCLK_SEL_MODE2_BMSK                                         0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_PLL_FBCLK_SEL_MODE2_SHFT                                            7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_CORECLK_DIVISOR_MODE1_BMSK                                       0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_CORECLK_DIVISOR_MODE1_SHFT                                          6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_CORECLK_DIVISOR_MODE0_BMSK                                       0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_CORECLK_DIVISOR_MODE0_SHFT                                          5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_PLL_FBCLK_SEL_MODE0_BMSK                                         0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_PLL_FBCLK_SEL_MODE0_SHFT                                            4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_PSM_SWITCH_CORECLK_BMSK                                           0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_PSM_SWITCH_CORECLK_SHFT                                             3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_PSM_SWITCH_AUXCLK_BMSK                                            0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_PSM_SWITCH_AUXCLK_SHFT                                              2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_PLL_FBCLK_SEL_MODE1_BMSK                                          0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_PLL_FBCLK_SEL_MODE1_SHFT                                            1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_CLK_BIAS_REFSEL_BMSK                                              0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_CONFIG_1_CLK_BIAS_REFSEL_SHFT                                                0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x178)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_RMSK                                                        0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_PLL_HS_SWITCH_MUX_BMSK                                      0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_PLL_HS_SWITCH_MUX_SHFT                                         5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_PLL_HS_SWITCH_BMSK                                          0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_PLL_HS_SWITCH_SHFT                                             4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_CMN_RATE_SW_UPDATE_BMSK                                      0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_CMN_RATE_SW_UPDATE_SHFT                                        3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_CMN_RATE_SW_SEL_BMSK                                         0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_CMN_RATE_SW_SEL_SHFT                                           2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_CMN_RATE_CODE_BMSK                                           0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_RATE_OVERRIDE_CMN_RATE_CODE_SHFT                                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x17c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_RMSK                                                         0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_PLL_DIGCLK_DIVSEL_MODE2_BMSK                                 0x30
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_PLL_DIGCLK_DIVSEL_MODE2_SHFT                                    4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_PLL_DIGCLK_DIVSEL_MODE1_BMSK                                  0xc
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_PLL_DIGCLK_DIVSEL_MODE1_SHFT                                    2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_PLL_DIGCLK_DIVSEL_MODE0_BMSK                                  0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SVS_MODE_CLK_SEL_PLL_DIGCLK_DIVSEL_MODE0_SHFT                                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_SEL_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x180)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_SEL_RMSK                                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_SEL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_SEL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_SEL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_SEL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_SEL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_SEL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_SEL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_SEL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_SEL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_SEL_CLK_DEBUG_SEL_BMSK                                              0xf0
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_SEL_CLK_DEBUG_SEL_SHFT                                                 4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_SEL_DEBUG_BUS_SEL_BMSK                                               0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS_SEL_DEBUG_BUS_SEL_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_ADDR                                                          (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x184)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_RMSK                                                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_COUPLE_HS_SWITCH_RATE_CHANGE_BMSK                                   0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_COUPLE_HS_SWITCH_RATE_CHANGE_SHFT                                      7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_DIS_CG_RATE_CHANGE_BMSK                                             0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_DIS_CG_RATE_CHANGE_SHFT                                                6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_DIS_CG_SYSGLITCH_BMSK                                               0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_DIS_CG_SYSGLITCH_SHFT                                                  5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_PLL_RESET_MUX_BMSK                                                  0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_PLL_RESET_MUX_SHFT                                                     4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_PLL_RESET_BMSK                                                       0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_PLL_RESET_SHFT                                                         3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_PLL_VREG_READY_MUX_BMSK                                              0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_PLL_VREG_READY_MUX_SHFT                                                2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_PLL_VREG_READY_BMSK                                                  0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_PLL_VREG_READY_SHFT                                                    1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_DISABLE_B2T_INTEGLOOP_CLKGATE_BMSK                                   0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MISC1_DISABLE_B2T_INTEGLOOP_CLKGATE_SHFT                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_ADDR                                                           (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x188)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_RMSK                                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CMN_MODE_7_0_BMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CMN_MODE_7_0_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD_ADDR                                                     (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x18c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD_RMSK                                                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD_CMN_MODE_15_8_BMSK                                             0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD_CMN_MODE_15_8_SHFT                                                0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD1_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x190)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD1_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD1_CMN_MODE_23_16_BMSK                                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD1_CMN_MODE_23_16_SHFT                                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD2_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x194)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD2_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD2_CMN_MODE_31_24_BMSK                                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_MODE_CONTD2_CMN_MODE_31_24_SHFT                                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_DC_LEVEL_CTRL_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x198)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_DC_LEVEL_CTRL_RMSK                                                        0x7f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_DC_LEVEL_CTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_DC_LEVEL_CTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_DC_LEVEL_CTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_DC_LEVEL_CTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_DC_LEVEL_CTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_DC_LEVEL_CTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_DC_LEVEL_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_DC_LEVEL_CTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_DC_LEVEL_CTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_DC_LEVEL_CTRL_PLL_VREFGEN_REFSEL_BMSK                                     0x60
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_DC_LEVEL_CTRL_PLL_VREFGEN_REFSEL_SHFT                                        5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_DC_LEVEL_CTRL_PLL_VAR_DCCTRL_BMSK                                         0x18
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_DC_LEVEL_CTRL_PLL_VAR_DCCTRL_SHFT                                            3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_DC_LEVEL_CTRL_CMN_VREG_SEL_BMSK                                            0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_VCO_DC_LEVEL_CTRL_CMN_VREG_SEL_SHFT                                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_HSCLK_SEL_1_ADDR                                             (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x19c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_HSCLK_SEL_1_RMSK                                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_HSCLK_SEL_1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_HSCLK_SEL_1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_HSCLK_SEL_1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_HSCLK_SEL_1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_HSCLK_SEL_1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_HSCLK_SEL_1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_HSCLK_SEL_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_HSCLK_SEL_1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_HSCLK_SEL_1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_HSCLK_SEL_1_BIN_VCOCAL_HSCLK_SEL_MODE1_BMSK                        0xf0
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_HSCLK_SEL_1_BIN_VCOCAL_HSCLK_SEL_MODE1_SHFT                           4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_HSCLK_SEL_1_BIN_VCOCAL_HSCLK_SEL_MODE0_BMSK                         0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_BIN_VCOCAL_HSCLK_SEL_1_BIN_VCOCAL_HSCLK_SEL_MODE0_SHFT                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1a0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_SELECT_LOOP_UNROLL_BMSK                                     0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_SELECT_LOOP_UNROLL_SHFT                                        7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_SLOWCLK_DIVISOR_DIGCLK_MODE2_BMSK                           0x60
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_SLOWCLK_DIVISOR_DIGCLK_MODE2_SHFT                              5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_SLOWCLK_DIVISOR_DIGCLK_MODE1_BMSK                           0x18
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_SLOWCLK_DIVISOR_DIGCLK_MODE1_SHFT                              3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_SLOWCLK_DIVISOR_DIGCLK_MODE0_BMSK                            0x6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_SLOWCLK_DIVISOR_DIGCLK_MODE0_SHFT                              1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_FORCE_REFGEN_READY_BMSK                                      0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_CTRL_1_FORCE_REFGEN_READY_SHFT                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1a4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_RMSK                                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_KEEP_GAIN_ADJ_STEP_SEL_SSC_BMSK                          0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_KEEP_GAIN_ADJ_STEP_SEL_SSC_SHFT                             7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_GAIN_ADJ_STEP_SEL_BMSK                                   0x70
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_GAIN_ADJ_STEP_SEL_SHFT                                      4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_COUNTER_LIMIT_SEL_BMSK                                    0xe
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_COUNTER_LIMIT_SEL_SHFT                                      1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_ENABLE_GAIN_ADJ_BMSK                                      0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_1_ENABLE_GAIN_ADJ_SHFT                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_2_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1a8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_2_RMSK                                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_2_MAX_KI_GAIN_LSB_BMSK                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_2_MAX_KI_GAIN_LSB_SHFT                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_3_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1ac)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_3_RMSK                                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_3_MIN_KI_GAIN_LSB_BMSK                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_3_MIN_KI_GAIN_LSB_SHFT                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_4_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1b0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_4_RMSK                                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_4_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_4_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_4_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_4_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_4_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_4_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_4_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_4_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_4_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_4_MAX_KI_GAIN_MSB_BMSK                                     0xf0
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_4_MAX_KI_GAIN_MSB_SHFT                                        4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_4_MIN_KI_GAIN_MSB_BMSK                                      0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_AUTO_GAIN_ADJ_CTRL_4_MIN_KI_GAIN_MSB_SHFT                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1b4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_EXT_TSYNC_MUX_BMSK                                            0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_EXT_TSYNC_MUX_SHFT                                               7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_EXT_TSYNC_BMSK                                                0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_EXT_TSYNC_SHFT                                                   6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_CLKS_PLL_DIVSEL_EPCLK_MODE1_BMSK                              0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_CLKS_PLL_DIVSEL_EPCLK_MODE1_SHFT                                 5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_CLKS_PLL_DIVSEL_EPCLK_MODE0_BMSK                              0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_CLKS_PLL_DIVSEL_EPCLK_MODE0_SHFT                                 4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_GAIN_ADJ_INVERSE_POLARITY_BMSK                                 0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_GAIN_ADJ_INVERSE_POLARITY_SHFT                                   3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_COUNTER_LIMIT_SEL_SSC_BMSK                                     0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_COUNTER_LIMIT_SEL_SSC_SHFT                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1b8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_SAVED_FOR_FUTURE_1_BMSK                                     0xc0
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_SAVED_FOR_FUTURE_1_SHFT                                        6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_CLOCK_FORWARDING_EN_BMSK                                    0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_CLOCK_FORWARDING_EN_SHFT                                       5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_CMN_MODE_MODE1_BMSK                                         0x18
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_CMN_MODE_MODE1_SHFT                                            3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_CMN_VREG_SEL_MODE1_BMSK                                      0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_2_CMN_VREG_SEL_MODE1_SHFT                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1bc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_CMN_MODE_4_MODE2_BMSK                                       0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_CMN_MODE_4_MODE2_SHFT                                          7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_CMN_MODE_4_MODE1_BMSK                                       0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_CMN_MODE_4_MODE1_SHFT                                          6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_CLKS_PLL_DIVSEL_EPCLK_MODE2_BMSK                            0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_CLKS_PLL_DIVSEL_EPCLK_MODE2_SHFT                               5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_CMN_MODE_MODE2_BMSK                                         0x18
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_CMN_MODE_MODE2_SHFT                                            3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_CMN_VREG_SEL_MODE2_BMSK                                      0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_3_CMN_VREG_SEL_MODE2_SHFT                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_4_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1c0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_4_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_4_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_4_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_4_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_4_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_4_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_4_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_4_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_4_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_4_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_4_CMN_MODE_31_28_MODE2_BMSK                                   0xf0
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_4_CMN_MODE_31_28_MODE2_SHFT                                      4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_4_CMN_MODE_31_28_MODE1_BMSK                                    0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_4_CMN_MODE_31_28_MODE1_SHFT                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1c4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_HYBRID_MODE_MUX_BMSK                                        0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_HYBRID_MODE_MUX_SHFT                                           7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_HYBRID_MODE_BMSK                                            0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_HYBRID_MODE_SHFT                                               6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_PLL_DIGITAL_REFCLK_DIV2_EN_MODE2_BMSK                       0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_PLL_DIGITAL_REFCLK_DIV2_EN_MODE2_SHFT                          5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_PLL_ANALOG_REFCLK_DIV2_EN_MODE2_BMSK                        0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_PLL_ANALOG_REFCLK_DIV2_EN_MODE2_SHFT                           4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_PLL_DIGITAL_REFCLK_DIV2_EN_MODE1_BMSK                        0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_PLL_DIGITAL_REFCLK_DIV2_EN_MODE1_SHFT                          3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_PLL_ANALOG_REFCLK_DIV2_EN_MODE1_BMSK                         0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_PLL_ANALOG_REFCLK_DIV2_EN_MODE1_SHFT                           2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_PLL_DIGITAL_REFCLK_DIV2_EN_MODE0_BMSK                        0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_PLL_DIGITAL_REFCLK_DIV2_EN_MODE0_SHFT                          1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_PLL_ANALOG_REFCLK_DIV2_EN_MODE0_BMSK                         0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_ADDITIONAL_MISC_5_PLL_ANALOG_REFCLK_DIV2_EN_MODE0_SHFT                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_MODE_OPERATION_STATUS_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1c8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_MODE_OPERATION_STATUS_RMSK                                                     0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_MODE_OPERATION_STATUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_MODE_OPERATION_STATUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_MODE_OPERATION_STATUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_MODE_OPERATION_STATUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_MODE_OPERATION_STATUS_PLL_HS_SWITCH_SELECTED_BMSK                              0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_MODE_OPERATION_STATUS_PLL_HS_SWITCH_SELECTED_SHFT                                2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_MODE_OPERATION_STATUS_PLL_MODE_SELECTED_BMSK                                   0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_MODE_OPERATION_STATUS_PLL_MODE_SELECTED_SHFT                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_DET_COMP_STATUS_ADDR                                             (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1cc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_DET_COMP_STATUS_RMSK                                                    0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_DET_COMP_STATUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_DET_COMP_STATUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_DET_COMP_STATUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_DET_COMP_STATUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_DET_COMP_STATUS_SYSCLK_CLKDET_COMP_BMSK                                 0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_SYSCLK_DET_COMP_STATUS_SYSCLK_CLKDET_COMP_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1d0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_REFGEN_READY_BMSK                                                  0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_REFGEN_READY_SHFT                                                     7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_FREEZEIO_D_BMSK                                                    0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_FREEZEIO_D_SHFT                                                       6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_SWITCH_TO_REFCLK_DONE_BMSK                                         0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_SWITCH_TO_REFCLK_DONE_SHFT                                            5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_SWITCH_TO_CORECLK_DONE_BMSK                                        0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_SWITCH_TO_CORECLK_DONE_SHFT                                           4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_SWITCH_TO_AUXCLK_DONE_BMSK                                          0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_SWITCH_TO_AUXCLK_DONE_SHFT                                            3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_PLL_UNLOCKED_BMSK                                                   0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_PLL_UNLOCKED_SHFT                                                     2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_PLL_LOCKED_BMSK                                                     0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_PLL_LOCKED_SHFT                                                       1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_PLL_FREQ_DONE_BMSK                                                  0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_CMN_STATUS_PLL_FREQ_DONE_SHFT                                                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESET_SM_STATUS_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1d4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESET_SM_STATUS_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESET_SM_STATUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESET_SM_STATUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESET_SM_STATUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESET_SM_STATUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESET_SM_STATUS_RESETSM_BMSK                                                  0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESET_SM_STATUS_RESETSM_SHFT                                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESTRIM_CODE_STATUS_ADDR                                                (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1d8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESTRIM_CODE_STATUS_RMSK                                                      0x7f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESTRIM_CODE_STATUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESTRIM_CODE_STATUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESTRIM_CODE_STATUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESTRIM_CODE_STATUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESTRIM_CODE_STATUS_RESTRIM_CODE_BMSK                                         0x7f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_RESTRIM_CODE_STATUS_RESTRIM_CODE_SHFT                                            0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLLCAL_CODE1_STATUS_ADDR                                                (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1dc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLLCAL_CODE1_STATUS_RMSK                                                      0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLLCAL_CODE1_STATUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLLCAL_CODE1_STATUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLLCAL_CODE1_STATUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLLCAL_CODE1_STATUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLLCAL_CODE1_STATUS_VCO_CTUNE_BINCODE_7_0_BMSK                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLLCAL_CODE1_STATUS_VCO_CTUNE_BINCODE_7_0_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLLCAL_CODE2_STATUS_ADDR                                                (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1e0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLLCAL_CODE2_STATUS_RMSK                                                       0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLLCAL_CODE2_STATUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLLCAL_CODE2_STATUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLLCAL_CODE2_STATUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLLCAL_CODE2_STATUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLLCAL_CODE2_STATUS_VCO_CTUNE_BINCODE_9_8_BMSK                                 0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_PLLCAL_CODE2_STATUS_VCO_CTUNE_BINCODE_9_8_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_BINCODE_STATUS_ADDR                                           (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1e4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_BINCODE_STATUS_RMSK                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_BINCODE_STATUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_BINCODE_STATUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_BINCODE_STATUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_BINCODE_STATUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_BINCODE_STATUS_INTEGLOOP_BINCODE_BMSK                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_INTEGLOOP_BINCODE_STATUS_INTEGLOOP_BINCODE_SHFT                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS0_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1e8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS0_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS0_DEBUG_BUS_7_0_BMSK                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS0_DEBUG_BUS_7_0_SHFT                                                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS1_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1ec)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS1_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS1_DEBUG_BUS_15_8_BMSK                                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS1_DEBUG_BUS_15_8_SHFT                                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS2_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1f0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS2_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS2_DEBUG_BUS_23_16_BMSK                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS2_DEBUG_BUS_23_16_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS3_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1f4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS3_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS3_DEBUG_BUS_31_24_BMSK                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DEBUG_BUS3_DEBUG_BUS_31_24_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_C_READY_STATUS_ADDR                                                     (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1f8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_C_READY_STATUS_RMSK                                                            0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_C_READY_STATUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_C_READY_STATUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_C_READY_STATUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_C_READY_STATUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_C_READY_STATUS_C_READY_BMSK                                                    0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_C_READY_STATUS_C_READY_SHFT                                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_READ_DUMMY_1_ADDR                                                       (AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_DP_QSERDES_PLL_USB4PHY_QMP_PLL_REG_BASE      + 0x1fc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_READ_DUMMY_1_RMSK                                                             0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_READ_DUMMY_1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_READ_DUMMY_1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_READ_DUMMY_1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_READ_DUMMY_1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_READ_DUMMY_1_READ_DUMMY_1_BMSK                                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_DP_QSERDES_PLL_READ_DUMMY_1_READ_DUMMY_1_SHFT                                                   0

/*----------------------------------------------------------------------------
 * MODULE: AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX
 *--------------------------------------------------------------------------*/

#define AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE                                  (AHB2PHY_1_AHB2PHY_1_BASE      + 0x00005400)
#define AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE_SIZE                             0x138
#define AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE_USED                             0x134

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_MODE_LANENO_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_MODE_LANENO_RMSK                                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_MODE_LANENO_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_MODE_LANENO_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_MODE_LANENO_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_MODE_LANENO_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_MODE_LANENO_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_MODE_LANENO_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_MODE_LANENO_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_MODE_LANENO_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_MODE_LANENO_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_MODE_LANENO_BIST_ERROR_INJECT_BMSK                                       0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_MODE_LANENO_BIST_ERROR_INJECT_SHFT                                          7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_MODE_LANENO_BIST_LANE_NUMBER_BMSK                                        0x60
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_MODE_LANENO_BIST_LANE_NUMBER_SHFT                                           5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_MODE_LANENO_BISTMODE_BMSK                                                0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_MODE_LANENO_BISTMODE_SHFT                                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_INVERT_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_INVERT_RMSK                                                               0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_INVERT_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_INVERT_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_INVERT_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_INVERT_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_INVERT_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_INVERT_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_INVERT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_INVERT_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_INVERT_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_INVERT_BIST_FROM_PCS_BMSK                                                 0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_INVERT_BIST_FROM_PCS_SHFT                                                   2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_INVERT_BIST_INVERT_RX_BMSK                                                0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_INVERT_BIST_INVERT_RX_SHFT                                                  1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_INVERT_BIST_INVERT_TX_BMSK                                                0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_INVERT_BIST_INVERT_TX_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_RMSK                                                            0x7f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_DISABLE_LPB_TX_CLKGATE_BMSK                                     0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_DISABLE_LPB_TX_CLKGATE_SHFT                                        6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_TXONLY_CLOCK_EDGE_BMSK                                          0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_TXONLY_CLOCK_EDGE_SHFT                                             5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_GATED_CLK_EN_BMSK                                               0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_GATED_CLK_EN_SHFT                                                  4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_CLKBUF_EN_LANE1_MUX_BMSK                                         0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_CLKBUF_EN_LANE1_MUX_SHFT                                           3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_CLKBUF_EN_LANE1_BMSK                                             0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_CLKBUF_EN_LANE1_SHFT                                               2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_CLKBUF_EN_LANE0_MUX_BMSK                                         0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_CLKBUF_EN_LANE0_MUX_SHFT                                           1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_CLKBUF_EN_LANE0_BMSK                                             0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_CLKBUF_ENABLE_CLKBUF_EN_LANE0_SHFT                                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_EMP_POST1_LVL_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_EMP_POST1_LVL_RMSK                                                         0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_EMP_POST1_LVL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_EMP_POST1_LVL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_EMP_POST1_LVL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_EMP_POST1_LVL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_EMP_POST1_LVL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_EMP_POST1_LVL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_EMP_POST1_LVL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_EMP_POST1_LVL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_EMP_POST1_LVL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_EMP_POST1_LVL_TX_EMP_POST1_LVL_MUX_BMSK                                    0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_EMP_POST1_LVL_TX_EMP_POST1_LVL_MUX_SHFT                                       5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_EMP_POST1_LVL_TX_EMP_POST1_LVL_BMSK                                        0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_EMP_POST1_LVL_TX_EMP_POST1_LVL_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_IDLE_LVL_LARGE_AMP_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x10)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_IDLE_LVL_LARGE_AMP_RMSK                                                     0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_IDLE_LVL_LARGE_AMP_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_IDLE_LVL_LARGE_AMP_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_IDLE_LVL_LARGE_AMP_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_IDLE_LVL_LARGE_AMP_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_IDLE_LVL_LARGE_AMP_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_IDLE_LVL_LARGE_AMP_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_IDLE_LVL_LARGE_AMP_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_IDLE_LVL_LARGE_AMP_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_IDLE_LVL_LARGE_AMP_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_IDLE_LVL_LARGE_AMP_TX_IDLE_LVL_MUX_BMSK                                     0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_IDLE_LVL_LARGE_AMP_TX_IDLE_LVL_MUX_SHFT                                       2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_IDLE_LVL_LARGE_AMP_TX_IDLE_LVL_BMSK                                         0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_IDLE_LVL_LARGE_AMP_TX_IDLE_LVL_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x14)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_RMSK                                                               0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_TX_DRV_LVL_MUX_BMSK                                                0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_TX_DRV_LVL_MUX_SHFT                                                   5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_TX_DRV_LVL_BMSK                                                    0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_TX_DRV_LVL_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_OFFSET_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x18)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_OFFSET_RMSK                                                         0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_OFFSET_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_OFFSET_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_OFFSET_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_OFFSET_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_OFFSET_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_OFFSET_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_OFFSET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_OFFSET_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_OFFSET_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_OFFSET_TX_DRV_LVL_OFFSET_BMSK                                       0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_DRV_LVL_OFFSET_TX_DRV_LVL_OFFSET_SHFT                                         0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_TSYNC_EN_ADDR                                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x1c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_TSYNC_EN_RMSK                                                            0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_TSYNC_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_TSYNC_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_TSYNC_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_TSYNC_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_TSYNC_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_TSYNC_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_TSYNC_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_TSYNC_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_TSYNC_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_TSYNC_EN_RESET_TSYNC_EN_MUX_BMSK                                         0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_TSYNC_EN_RESET_TSYNC_EN_MUX_SHFT                                           1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_TSYNC_EN_RESET_TSYNC_EN_BMSK                                             0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_TSYNC_EN_RESET_TSYNC_EN_SHFT                                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_ADDR                                             (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x20)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_RMSK                                                   0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_EN_VREG_MUX_BMSK                                       0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_EN_VREG_MUX_SHFT                                          5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_EN_VREG_BMSK                                           0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_EN_VREG_SHFT                                              4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_STALL_EN_MUX_BMSK                                       0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_STALL_EN_MUX_SHFT                                         3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_STALL_EN_BMSK                                           0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_STALL_EN_SHFT                                             2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_PRE_EN_MUX_BMSK                                         0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_PRE_EN_MUX_SHFT                                           1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_PRE_EN_BMSK                                             0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_STALL_LDO_BOOST_EN_PRE_EN_SHFT                                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_ADDR                                                             (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x24)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_RMSK                                                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_PLACEHOLDER_CHAIN_INPUT_BMSK                                           0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_PLACEHOLDER_CHAIN_INPUT_SHFT                                              7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_LINE_LPB_EN_MUX_BMSK                                                   0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_LINE_LPB_EN_MUX_SHFT                                                      6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_LINE_LPB_EN_BMSK                                                       0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_LINE_LPB_EN_SHFT                                                          5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_TX_RCLK_LPB_EN_BMSK                                                    0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_TX_RCLK_LPB_EN_SHFT                                                       4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_SER_LPB_EN_MUX_BMSK                                                     0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_SER_LPB_EN_MUX_SHFT                                                       3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_SER_LPB_EN_BMSK                                                         0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_SER_LPB_EN_SHFT                                                           2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_PAR_LPB_EN_BMSK                                                         0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_PAR_LPB_EN_SHFT                                                           1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_RCLK_LPB_EN_BMSK                                                        0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LPB_EN_RCLK_LPB_EN_SHFT                                                          0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_TX_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x28)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_TX_RMSK                                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_TX_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_TX_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_TX_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_TX_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_TX_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_TX_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_TX_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_TX_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_TX_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_TX_RES_CODE_LANE_TX_MUX_BMSK                                    0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_TX_RES_CODE_LANE_TX_MUX_SHFT                                       7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_TX_RES_CODE_LANE_TX_BMSK                                        0x7f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_TX_RES_CODE_LANE_TX_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_RX_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x2c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_RX_RMSK                                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_RX_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_RX_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_RX_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_RX_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_RX_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_RX_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_RX_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_RX_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_RX_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_RX_RES_CODE_LANE_RX_MUX_BMSK                                    0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_RX_RES_CODE_LANE_RX_MUX_SHFT                                       7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_RX_RES_CODE_LANE_RX_BMSK                                        0x7f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_RX_RES_CODE_LANE_RX_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_TX_ADDR                                            (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x30)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_TX_RMSK                                                  0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_TX_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_TX_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_TX_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_TX_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_TX_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_TX_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_TX_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_TX_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_TX_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_TX_RES_CODE_LANE_OFFSET_TX_BMSK                          0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_TX_RES_CODE_LANE_OFFSET_TX_SHFT                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_RX_ADDR                                            (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x34)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_RX_RMSK                                                  0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_RX_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_RX_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_RX_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_RX_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_RX_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_RX_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_RX_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_RX_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_RX_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_RX_RES_CODE_LANE_OFFSET_RX_BMSK                          0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RES_CODE_LANE_OFFSET_RX_RES_CODE_LANE_OFFSET_RX_SHFT                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH1_ADDR                                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x38)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH1_RMSK                                                             0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH1_PERL_LENGTH1_BMSK                                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH1_PERL_LENGTH1_SHFT                                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH2_ADDR                                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x3c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH2_RMSK                                                             0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH2_PERL_LENGTH2_BMSK                                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PERL_LENGTH2_PERL_LENGTH2_SHFT                                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x40)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_RMSK                                                        0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_SERDES_BYP_OUT_MUX_BMSK                                     0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_SERDES_BYP_OUT_MUX_SHFT                                        5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_SERDES_BYP_OUT_BMSK                                         0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_SERDES_BYP_OUT_SHFT                                            4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_SERDES_BYP_OUT_EN_MUX_BMSK                                   0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_SERDES_BYP_OUT_EN_MUX_SHFT                                     3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_SERDES_BYP_OUT_EN_BMSK                                       0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_SERDES_BYP_OUT_EN_SHFT                                         2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_SERDES_BYP_IN_EN_MUX_BMSK                                    0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_SERDES_BYP_IN_EN_MUX_SHFT                                      1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_SERDES_BYP_IN_EN_BMSK                                        0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SERDES_BYP_EN_OUT_SERDES_BYP_IN_EN_SHFT                                          0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS_SEL_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x44)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS_SEL_RMSK                                                            0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS_SEL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS_SEL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS_SEL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS_SEL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS_SEL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS_SEL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS_SEL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS_SEL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS_SEL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS_SEL_CLK_DEBUG_SEL_BMSK                                              0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS_SEL_CLK_DEBUG_SEL_SHFT                                                 4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS_SEL_RSVD_BMSK                                                        0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS_SEL_RSVD_SHFT                                                          3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS_SEL_DEBUGBUS_SEL_BMSK                                                0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS_SEL_DEBUGBUS_SEL_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_ADDR                                                (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x48)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_RMSK                                                      0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_CMN_SEL_MUX_BMSK                                          0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_CMN_SEL_MUX_SHFT                                             7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_CMN_SEL_BMSK                                              0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_CMN_SEL_SHFT                                                 6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_TRANSCEIVER_BIAS_EN_MUX_BMSK                              0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_TRANSCEIVER_BIAS_EN_MUX_SHFT                                 5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_TRANSCEIVER_BIAS_EN_BMSK                                  0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_TRANSCEIVER_BIAS_EN_SHFT                                     4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_TX_EN_LANE1_MUX_BMSK                                       0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_TX_EN_LANE1_MUX_SHFT                                         3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_TX_EN_LANE1_BMSK                                           0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_TX_EN_LANE1_SHFT                                             2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_TX_EN_LANE0_MUX_BMSK                                       0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_TX_EN_LANE0_MUX_SHFT                                         1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_TX_EN_LANE0_BMSK                                           0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRANSCEIVER_BIAS_EN_TX_EN_LANE0_SHFT                                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x4c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_RMSK                                                            0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_DRVR_EN_BMSK                                                    0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_DRVR_EN_SHFT                                                       4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_TX_HIGHZ_LANE1_MUX_BMSK                                          0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_TX_HIGHZ_LANE1_MUX_SHFT                                            3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_TX_HIGHZ_LANE1_BMSK                                              0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_TX_HIGHZ_LANE1_SHFT                                                2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_TX_HIGHZ_LANE0_MUX_BMSK                                          0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_TX_HIGHZ_LANE0_MUX_SHFT                                            1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_TX_HIGHZ_LANE0_BMSK                                              0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_HIGHZ_DRVR_EN_TX_HIGHZ_LANE0_SHFT                                                0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x50)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_RMSK                                                                0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_TX_POL_INV_LANE1_MUX_BMSK                                           0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_TX_POL_INV_LANE1_MUX_SHFT                                             3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_TX_POL_INV_LANE1_BMSK                                               0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_TX_POL_INV_LANE1_SHFT                                                 2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_TX_POL_INV_LANE0_MUX_BMSK                                           0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_TX_POL_INV_LANE0_MUX_SHFT                                             1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_TX_POL_INV_LANE0_BMSK                                               0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_POL_INV_TX_POL_INV_LANE0_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_ADDR                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x54)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_RMSK                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_HR_SEL_BMSK                                        0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_HR_SEL_SHFT                                           7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_TX_PAR_RATE_MUX_BMSK                               0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_TX_PAR_RATE_MUX_SHFT                                  6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_TX_PAR_RATE_BMSK                                   0x30
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_TX_PAR_RATE_SHFT                                      4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_IDLE_EN_MUX_BMSK                                    0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_IDLE_EN_MUX_SHFT                                      3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_IDLE_EN_BMSK                                        0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_IDLE_EN_SHFT                                          2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_RCV_DET_EN_MUX_BMSK                                 0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_RCV_DET_EN_MUX_SHFT                                   1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_RCV_DET_EN_BMSK                                     0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PARRATE_REC_DETECT_IDLE_EN_RCV_DET_EN_SHFT                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN1_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x58)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN1_RMSK                                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN1_BIST_PATTERN1_BMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN1_BIST_PATTERN1_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN2_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x5c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN2_RMSK                                                             0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN2_BIST_PATTERN2_BMSK                                               0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN2_BIST_PATTERN2_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN3_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x60)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN3_RMSK                                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN3_BIST_PATTERN3_BMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN3_BIST_PATTERN3_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN4_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x64)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN4_RMSK                                                             0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN4_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN4_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN4_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN4_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN4_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN4_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN4_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN4_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN4_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN4_BIST_PATTERN4_BMSK                                               0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN4_BIST_PATTERN4_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN5_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x68)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN5_RMSK                                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN5_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN5_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN5_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN5_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN5_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN5_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN5_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN5_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN5_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN5_BIST_PATTERN5_BMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN5_BIST_PATTERN5_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN6_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x6c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN6_RMSK                                                             0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN6_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN6_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN6_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN6_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN6_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN6_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN6_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN6_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN6_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN6_BIST_PATTERN6_BMSK                                               0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN6_BIST_PATTERN6_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN7_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x70)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN7_RMSK                                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN7_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN7_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN7_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN7_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN7_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN7_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN7_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN7_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN7_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN7_BIST_PATTERN7_BMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN7_BIST_PATTERN7_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN8_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x74)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN8_RMSK                                                             0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN8_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN8_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN8_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN8_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN8_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN8_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN8_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN8_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN8_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN8_BIST_PATTERN8_BMSK                                               0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_PATTERN8_BIST_PATTERN8_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_1_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x78)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_1_RMSK                                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_1_LANE_MODE1_BMSK                                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_1_LANE_MODE1_SHFT                                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_2_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x7c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_2_RMSK                                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_2_LANE_MODE2_BMSK                                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_2_LANE_MODE2_SHFT                                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_3_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x80)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_3_RMSK                                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_3_LANE_MODE3_BMSK                                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_MODE_3_LANE_MODE3_SHFT                                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL1_ADDR                                                           (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x84)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL1_RMSK                                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL1_ATB_SEL1_BMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL1_ATB_SEL1_SHFT                                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL2_ADDR                                                           (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x88)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL2_RMSK                                                                  0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL2_ATB_SEL2_BMSK                                                         0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ATB_SEL2_ATB_SEL2_SHFT                                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_ADDR                                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x8c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_RMSK                                                            0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_RCV_DET_LVL_MUX_BMSK                                            0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_RCV_DET_LVL_MUX_SHFT                                              3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_RCV_DET_LVL_BMSK                                                0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_RCV_DET_LVL_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_2_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x90)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_2_RMSK                                                         0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_2_RCV_DET_LVL_2_BMSK                                           0x38
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_2_RCV_DET_LVL_2_SHFT                                              3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_2_RCV_DET_LVL_1_BMSK                                            0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RCV_DETECT_LVL_2_RCV_DET_LVL_1_SHFT                                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED1_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x94)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED1_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED1_PRBS_SEED1_BMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED1_PRBS_SEED1_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED2_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x98)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED2_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED2_PRBS_SEED2_BMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED2_PRBS_SEED2_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED3_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x9c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED3_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED3_PRBS_SEED3_BMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED3_PRBS_SEED3_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED4_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xa0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED4_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED4_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED4_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED4_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED4_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED4_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED4_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED4_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED4_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED4_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED4_PRBS_SEED4_BMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRBS_SEED4_PRBS_SEED4_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_ADDR                                                          (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xa4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_RMSK                                                                0x7f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_SW_CDR_RESET_BMSK                                                   0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_SW_CDR_RESET_SHFT                                                      6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_JITTER_GEN_RESET_BMSK                                               0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_JITTER_GEN_RESET_SHFT                                                  5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_SW_TSYNC_BMSK                                                       0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_SW_TSYNC_SHFT                                                          4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_SW_RSYNC_BMSK                                                        0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_SW_RSYNC_SHFT                                                          3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_RSVD_BMSK                                                            0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_RSVD_SHFT                                                              2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_BIST_TX_RESET_BMSK                                                   0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_BIST_TX_RESET_SHFT                                                     1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_BIST_RX_RESET_BMSK                                                   0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_BIST_RX_RESET_SHFT                                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_MUXES_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xa8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_MUXES_RMSK                                                           0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_MUXES_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_MUXES_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_MUXES_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_MUXES_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_MUXES_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_MUXES_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_MUXES_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_MUXES_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_MUXES_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_MUXES_TSYNC_MUX_BMSK                                                 0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_MUXES_TSYNC_MUX_SHFT                                                   1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_MUXES_RSYNC_MUX_BMSK                                                 0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RESET_GEN_MUXES_RSYNC_MUX_SHFT                                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xac)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_RMSK                                                         0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_TX_DATAPATH_EN_MUX_BMSK                                      0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_TX_DATAPATH_EN_MUX_SHFT                                         5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_TX_DATAPATH_EN_BMSK                                          0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_TX_DATAPATH_EN_SHFT                                             4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_TX_LVL_UPDATE_MUX_BMSK                                        0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_TX_LVL_UPDATE_MUX_SHFT                                          3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_TX_LVL_UPDATE_BMSK                                            0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_TX_LVL_UPDATE_SHFT                                              2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_EMP_EN_MUX_BMSK                                               0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_EMP_EN_MUX_SHFT                                                 1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_EMP_EN_BMSK                                                   0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TRAN_DRVR_EMP_EN_EMP_EN_SHFT                                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_VMODE_CTRL1_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xb0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_VMODE_CTRL1_RMSK                                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_VMODE_CTRL1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_VMODE_CTRL1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_VMODE_CTRL1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_VMODE_CTRL1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_VMODE_CTRL1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_VMODE_CTRL1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_VMODE_CTRL1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_VMODE_CTRL1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_VMODE_CTRL1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_VMODE_CTRL1_VMODE_CTRL1_BMSK                                                  0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_VMODE_CTRL1_VMODE_CTRL1_SHFT                                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_CTRL_1_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xb4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_CTRL_1_RMSK                                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_CTRL_1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_CTRL_1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_CTRL_1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_CTRL_1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_CTRL_1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_CTRL_1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_CTRL_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_CTRL_1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_CTRL_1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_CTRL_1_ALOG_OBSV_BUS_CTRL_1_SEL_BMSK                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_CTRL_1_ALOG_OBSV_BUS_CTRL_1_SEL_SHFT                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_STATUS_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xb8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_STATUS_RMSK                                                               0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_STATUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_STATUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_STATUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_STATUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_STATUS_BIST_STATUS_RO_BMSK                                                0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_STATUS_BIST_STATUS_RO_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_ERROR_COUNT1_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xbc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_ERROR_COUNT1_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_ERROR_COUNT1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_ERROR_COUNT1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_ERROR_COUNT1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_ERROR_COUNT1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_ERROR_COUNT1_BIST_ERROR_COUNT1_STATUS_BMSK                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_ERROR_COUNT1_BIST_ERROR_COUNT1_STATUS_SHFT                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_ERROR_COUNT2_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xc0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_ERROR_COUNT2_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_ERROR_COUNT2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_ERROR_COUNT2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_ERROR_COUNT2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_ERROR_COUNT2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_ERROR_COUNT2_BIST_ERROR_COUNT2_STATUS_BMSK                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_BIST_ERROR_COUNT2_BIST_ERROR_COUNT2_STATUS_SHFT                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_STATUS_1_ADDR                                             (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xc4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_STATUS_1_RMSK                                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_STATUS_1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_STATUS_1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_STATUS_1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_STATUS_1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_STATUS_1_ALOG_OBSV_BUS_STATUS_1_BMSK                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_ALOG_OBSV_BUS_STATUS_1_ALOG_OBSV_BUS_STATUS_1_SHFT                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_DIG_CONFIG_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xc8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_DIG_CONFIG_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_DIG_CONFIG_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_DIG_CONFIG_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_DIG_CONFIG_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_DIG_CONFIG_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_DIG_CONFIG_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_DIG_CONFIG_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_DIG_CONFIG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_DIG_CONFIG_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_DIG_CONFIG_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_DIG_CONFIG_RSVD_BMSK                                                     0xfe
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_DIG_CONFIG_RSVD_SHFT                                                        1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_DIG_CONFIG_LANE_PWRDN_B_BMSK                                              0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_LANE_DIG_CONFIG_LANE_PWRDN_B_SHFT                                                0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PI_QEC_CTRL_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xcc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PI_QEC_CTRL_RMSK                                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PI_QEC_CTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PI_QEC_CTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PI_QEC_CTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PI_QEC_CTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PI_QEC_CTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PI_QEC_CTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PI_QEC_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PI_QEC_CTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PI_QEC_CTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PI_QEC_CTRL_PI_QEC_CTRL_BMSK                                                  0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PI_QEC_CTRL_PI_QEC_CTRL_SHFT                                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_EMPH_ADDR                                                           (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xd0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_EMPH_RMSK                                                                 0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_EMPH_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_EMPH_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_EMPH_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_EMPH_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_EMPH_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_EMPH_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_EMPH_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_EMPH_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_EMPH_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_EMPH_PREEMPH_VAL_MUX_BMSK                                                 0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_EMPH_PREEMPH_VAL_MUX_SHFT                                                    5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_EMPH_PREEMPH_BMSK                                                         0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_PRE_EMPH_PREEMPH_SHFT                                                            0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SW_RESET_ADDR                                                           (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xd4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SW_RESET_RMSK                                                                  0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SW_RESET_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SW_RESET_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SW_RESET_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SW_RESET_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SW_RESET_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SW_RESET_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SW_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SW_RESET_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SW_RESET_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SW_RESET_SW_RESET_BMSK                                                         0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SW_RESET_SW_RESET_SHFT                                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_ADDR                                                            (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xd8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_RMSK                                                                  0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_TX_BAND_RATE3_BMSK                                                    0xc0
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_TX_BAND_RATE3_SHFT                                                       6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_TX_BAND_RATE2_BMSK                                                    0x30
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_TX_BAND_RATE2_SHFT                                                       4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_TX_BAND_RATE1_BMSK                                                     0xc
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_TX_BAND_RATE1_SHFT                                                       2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_TX_BAND_RATE0_BMSK                                                     0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BAND_TX_BAND_RATE0_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL0_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xdc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL0_RMSK                                                               0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL0_SLEW_CNTL_RATE1_BMSK                                               0x38
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL0_SLEW_CNTL_RATE1_SHFT                                                  3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL0_SLEW_CNTL_RATE0_BMSK                                                0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL0_SLEW_CNTL_RATE0_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL1_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xe0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL1_RMSK                                                               0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL1_SLEW_CNTL_RATE3_BMSK                                               0x38
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL1_SLEW_CNTL_RATE3_SHFT                                                  3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL1_SLEW_CNTL_RATE2_BMSK                                                0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_SLEW_CNTL1_SLEW_CNTL_RATE2_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xe4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_RMSK                                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_SEL_20B_10B_RATE3_BMSK                                       0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_SEL_20B_10B_RATE3_SHFT                                          7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_SEL_20B_10B_RATE2_BMSK                                       0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_SEL_20B_10B_RATE2_SHFT                                          6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_SEL_20B_10B_RATE1_BMSK                                       0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_SEL_20B_10B_RATE1_SHFT                                          5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_SEL_20B_10B_RATE0_BMSK                                       0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_SEL_20B_10B_RATE0_SHFT                                          4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_SEL_10B_8B_RATE3_BMSK                                         0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_SEL_10B_8B_RATE3_SHFT                                           3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_SEL_10B_8B_RATE2_BMSK                                         0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_SEL_10B_8B_RATE2_SHFT                                           2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_SEL_10B_8B_RATE1_BMSK                                         0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_SEL_10B_8B_RATE1_SHFT                                           1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_SEL_10B_8B_RATE0_BMSK                                         0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_INTERFACE_SELECT_SEL_10B_8B_RATE0_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE210_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xe8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE210_RMSK                                           0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE210_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE210_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE210_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE210_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE210_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE210_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE210_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE210_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE210_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE210_Q_PI_UPPER_THRESH1_RATE210_BMSK                0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE210_Q_PI_UPPER_THRESH1_RATE210_SHFT                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE3_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xec)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE3_RMSK                                             0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE3_Q_PI_UPPER_THRESH1_RATE3_BMSK                    0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH1_RATE3_Q_PI_UPPER_THRESH1_RATE3_SHFT                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE210_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xf0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE210_RMSK                                           0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE210_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE210_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE210_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE210_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE210_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE210_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE210_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE210_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE210_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE210_Q_PI_UPPER_THRESH2_RATE210_BMSK                0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE210_Q_PI_UPPER_THRESH2_RATE210_SHFT                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE3_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xf4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE3_RMSK                                             0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE3_Q_PI_UPPER_THRESH2_RATE3_BMSK                    0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH2_RATE3_Q_PI_UPPER_THRESH2_RATE3_SHFT                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE210_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xf8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE210_RMSK                                           0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE210_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE210_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE210_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE210_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE210_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE210_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE210_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE210_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE210_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE210_Q_PI_UPPER_THRESH3_RATE210_BMSK                0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE210_Q_PI_UPPER_THRESH3_RATE210_SHFT                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE3_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0xfc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE3_RMSK                                             0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE3_Q_PI_UPPER_THRESH3_RATE3_BMSK                    0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH3_RATE3_Q_PI_UPPER_THRESH3_RATE3_SHFT                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE210_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x100)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE210_RMSK                                           0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE210_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE210_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE210_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE210_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE210_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE210_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE210_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE210_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE210_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE210_Q_PI_UPPER_THRESH4_RATE210_BMSK                0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE210_Q_PI_UPPER_THRESH4_RATE210_SHFT                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE3_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x104)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE3_RMSK                                             0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE3_Q_PI_UPPER_THRESH4_RATE3_BMSK                    0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH4_RATE3_Q_PI_UPPER_THRESH4_RATE3_SHFT                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE210_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x108)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE210_RMSK                                           0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE210_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE210_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE210_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE210_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE210_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE210_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE210_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE210_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE210_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE210_Q_PI_UPPER_THRESH5_RATE210_BMSK                0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE210_Q_PI_UPPER_THRESH5_RATE210_SHFT                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE3_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x10c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE3_RMSK                                             0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE3_Q_PI_UPPER_THRESH5_RATE3_BMSK                    0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH5_RATE3_Q_PI_UPPER_THRESH5_RATE3_SHFT                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE210_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x110)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE210_RMSK                                           0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE210_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE210_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE210_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE210_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE210_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE210_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE210_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE210_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE210_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE210_Q_PI_UPPER_THRESH6_RATE210_BMSK                0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE210_Q_PI_UPPER_THRESH6_RATE210_SHFT                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE3_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x114)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE3_RMSK                                             0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE3_Q_PI_UPPER_THRESH6_RATE3_BMSK                    0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH6_RATE3_Q_PI_UPPER_THRESH6_RATE3_SHFT                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE210_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x118)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE210_RMSK                                           0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE210_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE210_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE210_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE210_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE210_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE210_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE210_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE210_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE210_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE210_Q_PI_UPPER_THRESH7_RATE210_BMSK                0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE210_Q_PI_UPPER_THRESH7_RATE210_SHFT                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE3_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x11c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE3_RMSK                                             0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE3_Q_PI_UPPER_THRESH7_RATE3_BMSK                    0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_RX_MARG_COARSE_THRESH7_RATE3_Q_PI_UPPER_THRESH7_RATE3_SHFT                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DIG_BKUP_CTRL_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x120)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DIG_BKUP_CTRL_RMSK                                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DIG_BKUP_CTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DIG_BKUP_CTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DIG_BKUP_CTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DIG_BKUP_CTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DIG_BKUP_CTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DIG_BKUP_CTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DIG_BKUP_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DIG_BKUP_CTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DIG_BKUP_CTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DIG_BKUP_CTRL_RSVD_BMSK                                                       0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DIG_BKUP_CTRL_RSVD_SHFT                                                          0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS0_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x124)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS0_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS0_DEBUG_BUS_7_0_BMSK                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS0_DEBUG_BUS_7_0_SHFT                                                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS1_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x128)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS1_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS1_DEBUG_BUS_15_8_BMSK                                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS1_DEBUG_BUS_15_8_SHFT                                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS2_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x12c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS2_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS2_DEBUG_BUS_23_16_BMSK                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS2_DEBUG_BUS_23_16_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS3_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x130)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS3_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS3_DEBUG_BUS_31_24_BMSK                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_DEBUG_BUS3_DEBUG_BUS_31_24_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BKUP_RO_BUS_ADDR                                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_USB43DP_QSERDES_TXA_USB4PHY_QMP_TX_REG_BASE      + 0x134)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BKUP_RO_BUS_RMSK                                                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BKUP_RO_BUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BKUP_RO_BUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BKUP_RO_BUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BKUP_RO_BUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BKUP_RO_BUS_TX_BKUP_READ_BUS_BMSK                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXA_TX_BKUP_RO_BUS_TX_BKUP_READ_BUS_SHFT                                             0

/*----------------------------------------------------------------------------
 * MODULE: AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX
 *--------------------------------------------------------------------------*/

#define AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE                                  (AHB2PHY_1_AHB2PHY_1_BASE      + 0x00005a00)
#define AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE_SIZE                             0x138
#define AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE_USED                             0x134

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_MODE_LANENO_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_MODE_LANENO_RMSK                                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_MODE_LANENO_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_MODE_LANENO_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_MODE_LANENO_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_MODE_LANENO_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_MODE_LANENO_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_MODE_LANENO_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_MODE_LANENO_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_MODE_LANENO_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_MODE_LANENO_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_MODE_LANENO_BIST_ERROR_INJECT_BMSK                                       0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_MODE_LANENO_BIST_ERROR_INJECT_SHFT                                          7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_MODE_LANENO_BIST_LANE_NUMBER_BMSK                                        0x60
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_MODE_LANENO_BIST_LANE_NUMBER_SHFT                                           5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_MODE_LANENO_BISTMODE_BMSK                                                0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_MODE_LANENO_BISTMODE_SHFT                                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_INVERT_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_INVERT_RMSK                                                               0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_INVERT_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_INVERT_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_INVERT_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_INVERT_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_INVERT_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_INVERT_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_INVERT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_INVERT_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_INVERT_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_INVERT_BIST_FROM_PCS_BMSK                                                 0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_INVERT_BIST_FROM_PCS_SHFT                                                   2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_INVERT_BIST_INVERT_RX_BMSK                                                0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_INVERT_BIST_INVERT_RX_SHFT                                                  1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_INVERT_BIST_INVERT_TX_BMSK                                                0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_INVERT_BIST_INVERT_TX_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_RMSK                                                            0x7f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_DISABLE_LPB_TX_CLKGATE_BMSK                                     0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_DISABLE_LPB_TX_CLKGATE_SHFT                                        6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_TXONLY_CLOCK_EDGE_BMSK                                          0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_TXONLY_CLOCK_EDGE_SHFT                                             5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_GATED_CLK_EN_BMSK                                               0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_GATED_CLK_EN_SHFT                                                  4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_CLKBUF_EN_LANE1_MUX_BMSK                                         0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_CLKBUF_EN_LANE1_MUX_SHFT                                           3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_CLKBUF_EN_LANE1_BMSK                                             0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_CLKBUF_EN_LANE1_SHFT                                               2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_CLKBUF_EN_LANE0_MUX_BMSK                                         0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_CLKBUF_EN_LANE0_MUX_SHFT                                           1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_CLKBUF_EN_LANE0_BMSK                                             0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_CLKBUF_ENABLE_CLKBUF_EN_LANE0_SHFT                                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_EMP_POST1_LVL_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_EMP_POST1_LVL_RMSK                                                         0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_EMP_POST1_LVL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_EMP_POST1_LVL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_EMP_POST1_LVL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_EMP_POST1_LVL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_EMP_POST1_LVL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_EMP_POST1_LVL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_EMP_POST1_LVL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_EMP_POST1_LVL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_EMP_POST1_LVL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_EMP_POST1_LVL_TX_EMP_POST1_LVL_MUX_BMSK                                    0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_EMP_POST1_LVL_TX_EMP_POST1_LVL_MUX_SHFT                                       5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_EMP_POST1_LVL_TX_EMP_POST1_LVL_BMSK                                        0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_EMP_POST1_LVL_TX_EMP_POST1_LVL_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_IDLE_LVL_LARGE_AMP_ADDR                                              (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x10)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_IDLE_LVL_LARGE_AMP_RMSK                                                     0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_IDLE_LVL_LARGE_AMP_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_IDLE_LVL_LARGE_AMP_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_IDLE_LVL_LARGE_AMP_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_IDLE_LVL_LARGE_AMP_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_IDLE_LVL_LARGE_AMP_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_IDLE_LVL_LARGE_AMP_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_IDLE_LVL_LARGE_AMP_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_IDLE_LVL_LARGE_AMP_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_IDLE_LVL_LARGE_AMP_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_IDLE_LVL_LARGE_AMP_TX_IDLE_LVL_MUX_BMSK                                     0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_IDLE_LVL_LARGE_AMP_TX_IDLE_LVL_MUX_SHFT                                       2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_IDLE_LVL_LARGE_AMP_TX_IDLE_LVL_BMSK                                         0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_IDLE_LVL_LARGE_AMP_TX_IDLE_LVL_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x14)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_RMSK                                                               0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_TX_DRV_LVL_MUX_BMSK                                                0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_TX_DRV_LVL_MUX_SHFT                                                   5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_TX_DRV_LVL_BMSK                                                    0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_TX_DRV_LVL_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_OFFSET_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x18)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_OFFSET_RMSK                                                         0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_OFFSET_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_OFFSET_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_OFFSET_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_OFFSET_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_OFFSET_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_OFFSET_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_OFFSET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_OFFSET_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_OFFSET_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_OFFSET_TX_DRV_LVL_OFFSET_BMSK                                       0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_DRV_LVL_OFFSET_TX_DRV_LVL_OFFSET_SHFT                                         0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_TSYNC_EN_ADDR                                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x1c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_TSYNC_EN_RMSK                                                            0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_TSYNC_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_TSYNC_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_TSYNC_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_TSYNC_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_TSYNC_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_TSYNC_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_TSYNC_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_TSYNC_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_TSYNC_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_TSYNC_EN_RESET_TSYNC_EN_MUX_BMSK                                         0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_TSYNC_EN_RESET_TSYNC_EN_MUX_SHFT                                           1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_TSYNC_EN_RESET_TSYNC_EN_BMSK                                             0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_TSYNC_EN_RESET_TSYNC_EN_SHFT                                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_ADDR                                             (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x20)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_RMSK                                                   0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_EN_VREG_MUX_BMSK                                       0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_EN_VREG_MUX_SHFT                                          5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_EN_VREG_BMSK                                           0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_EN_VREG_SHFT                                              4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_STALL_EN_MUX_BMSK                                       0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_STALL_EN_MUX_SHFT                                         3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_STALL_EN_BMSK                                           0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_STALL_EN_SHFT                                             2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_PRE_EN_MUX_BMSK                                         0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_PRE_EN_MUX_SHFT                                           1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_PRE_EN_BMSK                                             0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_STALL_LDO_BOOST_EN_PRE_EN_SHFT                                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_ADDR                                                             (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x24)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_RMSK                                                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_PLACEHOLDER_CHAIN_INPUT_BMSK                                           0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_PLACEHOLDER_CHAIN_INPUT_SHFT                                              7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_LINE_LPB_EN_MUX_BMSK                                                   0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_LINE_LPB_EN_MUX_SHFT                                                      6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_LINE_LPB_EN_BMSK                                                       0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_LINE_LPB_EN_SHFT                                                          5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_TX_RCLK_LPB_EN_BMSK                                                    0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_TX_RCLK_LPB_EN_SHFT                                                       4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_SER_LPB_EN_MUX_BMSK                                                     0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_SER_LPB_EN_MUX_SHFT                                                       3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_SER_LPB_EN_BMSK                                                         0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_SER_LPB_EN_SHFT                                                           2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_PAR_LPB_EN_BMSK                                                         0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_PAR_LPB_EN_SHFT                                                           1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_RCLK_LPB_EN_BMSK                                                        0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LPB_EN_RCLK_LPB_EN_SHFT                                                          0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_TX_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x28)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_TX_RMSK                                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_TX_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_TX_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_TX_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_TX_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_TX_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_TX_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_TX_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_TX_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_TX_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_TX_RES_CODE_LANE_TX_MUX_BMSK                                    0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_TX_RES_CODE_LANE_TX_MUX_SHFT                                       7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_TX_RES_CODE_LANE_TX_BMSK                                        0x7f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_TX_RES_CODE_LANE_TX_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_RX_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x2c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_RX_RMSK                                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_RX_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_RX_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_RX_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_RX_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_RX_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_RX_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_RX_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_RX_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_RX_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_RX_RES_CODE_LANE_RX_MUX_BMSK                                    0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_RX_RES_CODE_LANE_RX_MUX_SHFT                                       7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_RX_RES_CODE_LANE_RX_BMSK                                        0x7f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_RX_RES_CODE_LANE_RX_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_TX_ADDR                                            (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x30)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_TX_RMSK                                                  0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_TX_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_TX_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_TX_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_TX_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_TX_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_TX_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_TX_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_TX_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_TX_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_TX_RES_CODE_LANE_OFFSET_TX_BMSK                          0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_TX_RES_CODE_LANE_OFFSET_TX_SHFT                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_RX_ADDR                                            (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x34)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_RX_RMSK                                                  0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_RX_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_RX_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_RX_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_RX_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_RX_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_RX_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_RX_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_RX_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_RX_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_RX_RES_CODE_LANE_OFFSET_RX_BMSK                          0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RES_CODE_LANE_OFFSET_RX_RES_CODE_LANE_OFFSET_RX_SHFT                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH1_ADDR                                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x38)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH1_RMSK                                                             0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH1_PERL_LENGTH1_BMSK                                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH1_PERL_LENGTH1_SHFT                                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH2_ADDR                                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x3c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH2_RMSK                                                             0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH2_PERL_LENGTH2_BMSK                                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PERL_LENGTH2_PERL_LENGTH2_SHFT                                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x40)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_RMSK                                                        0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_SERDES_BYP_OUT_MUX_BMSK                                     0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_SERDES_BYP_OUT_MUX_SHFT                                        5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_SERDES_BYP_OUT_BMSK                                         0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_SERDES_BYP_OUT_SHFT                                            4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_SERDES_BYP_OUT_EN_MUX_BMSK                                   0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_SERDES_BYP_OUT_EN_MUX_SHFT                                     3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_SERDES_BYP_OUT_EN_BMSK                                       0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_SERDES_BYP_OUT_EN_SHFT                                         2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_SERDES_BYP_IN_EN_MUX_BMSK                                    0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_SERDES_BYP_IN_EN_MUX_SHFT                                      1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_SERDES_BYP_IN_EN_BMSK                                        0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SERDES_BYP_EN_OUT_SERDES_BYP_IN_EN_SHFT                                          0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS_SEL_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x44)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS_SEL_RMSK                                                            0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS_SEL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS_SEL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS_SEL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS_SEL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS_SEL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS_SEL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS_SEL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS_SEL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS_SEL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS_SEL_CLK_DEBUG_SEL_BMSK                                              0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS_SEL_CLK_DEBUG_SEL_SHFT                                                 4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS_SEL_RSVD_BMSK                                                        0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS_SEL_RSVD_SHFT                                                          3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS_SEL_DEBUGBUS_SEL_BMSK                                                0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS_SEL_DEBUGBUS_SEL_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_ADDR                                                (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x48)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_RMSK                                                      0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_CMN_SEL_MUX_BMSK                                          0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_CMN_SEL_MUX_SHFT                                             7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_CMN_SEL_BMSK                                              0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_CMN_SEL_SHFT                                                 6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_TRANSCEIVER_BIAS_EN_MUX_BMSK                              0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_TRANSCEIVER_BIAS_EN_MUX_SHFT                                 5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_TRANSCEIVER_BIAS_EN_BMSK                                  0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_TRANSCEIVER_BIAS_EN_SHFT                                     4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_TX_EN_LANE1_MUX_BMSK                                       0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_TX_EN_LANE1_MUX_SHFT                                         3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_TX_EN_LANE1_BMSK                                           0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_TX_EN_LANE1_SHFT                                             2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_TX_EN_LANE0_MUX_BMSK                                       0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_TX_EN_LANE0_MUX_SHFT                                         1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_TX_EN_LANE0_BMSK                                           0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRANSCEIVER_BIAS_EN_TX_EN_LANE0_SHFT                                             0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x4c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_RMSK                                                            0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_DRVR_EN_BMSK                                                    0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_DRVR_EN_SHFT                                                       4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_TX_HIGHZ_LANE1_MUX_BMSK                                          0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_TX_HIGHZ_LANE1_MUX_SHFT                                            3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_TX_HIGHZ_LANE1_BMSK                                              0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_TX_HIGHZ_LANE1_SHFT                                                2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_TX_HIGHZ_LANE0_MUX_BMSK                                          0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_TX_HIGHZ_LANE0_MUX_SHFT                                            1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_TX_HIGHZ_LANE0_BMSK                                              0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_HIGHZ_DRVR_EN_TX_HIGHZ_LANE0_SHFT                                                0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x50)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_RMSK                                                                0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_TX_POL_INV_LANE1_MUX_BMSK                                           0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_TX_POL_INV_LANE1_MUX_SHFT                                             3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_TX_POL_INV_LANE1_BMSK                                               0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_TX_POL_INV_LANE1_SHFT                                                 2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_TX_POL_INV_LANE0_MUX_BMSK                                           0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_TX_POL_INV_LANE0_MUX_SHFT                                             1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_TX_POL_INV_LANE0_BMSK                                               0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_POL_INV_TX_POL_INV_LANE0_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_ADDR                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x54)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_RMSK                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_HR_SEL_BMSK                                        0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_HR_SEL_SHFT                                           7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_TX_PAR_RATE_MUX_BMSK                               0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_TX_PAR_RATE_MUX_SHFT                                  6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_TX_PAR_RATE_BMSK                                   0x30
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_TX_PAR_RATE_SHFT                                      4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_IDLE_EN_MUX_BMSK                                    0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_IDLE_EN_MUX_SHFT                                      3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_IDLE_EN_BMSK                                        0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_IDLE_EN_SHFT                                          2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_RCV_DET_EN_MUX_BMSK                                 0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_RCV_DET_EN_MUX_SHFT                                   1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_RCV_DET_EN_BMSK                                     0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PARRATE_REC_DETECT_IDLE_EN_RCV_DET_EN_SHFT                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN1_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x58)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN1_RMSK                                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN1_BIST_PATTERN1_BMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN1_BIST_PATTERN1_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN2_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x5c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN2_RMSK                                                             0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN2_BIST_PATTERN2_BMSK                                               0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN2_BIST_PATTERN2_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN3_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x60)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN3_RMSK                                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN3_BIST_PATTERN3_BMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN3_BIST_PATTERN3_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN4_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x64)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN4_RMSK                                                             0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN4_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN4_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN4_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN4_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN4_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN4_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN4_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN4_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN4_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN4_BIST_PATTERN4_BMSK                                               0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN4_BIST_PATTERN4_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN5_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x68)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN5_RMSK                                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN5_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN5_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN5_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN5_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN5_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN5_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN5_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN5_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN5_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN5_BIST_PATTERN5_BMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN5_BIST_PATTERN5_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN6_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x6c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN6_RMSK                                                             0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN6_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN6_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN6_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN6_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN6_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN6_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN6_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN6_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN6_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN6_BIST_PATTERN6_BMSK                                               0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN6_BIST_PATTERN6_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN7_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x70)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN7_RMSK                                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN7_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN7_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN7_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN7_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN7_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN7_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN7_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN7_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN7_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN7_BIST_PATTERN7_BMSK                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN7_BIST_PATTERN7_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN8_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x74)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN8_RMSK                                                             0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN8_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN8_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN8_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN8_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN8_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN8_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN8_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN8_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN8_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN8_BIST_PATTERN8_BMSK                                               0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_PATTERN8_BIST_PATTERN8_SHFT                                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_1_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x78)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_1_RMSK                                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_1_LANE_MODE1_BMSK                                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_1_LANE_MODE1_SHFT                                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_2_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x7c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_2_RMSK                                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_2_LANE_MODE2_BMSK                                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_2_LANE_MODE2_SHFT                                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_3_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x80)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_3_RMSK                                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_3_LANE_MODE3_BMSK                                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_MODE_3_LANE_MODE3_SHFT                                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL1_ADDR                                                           (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x84)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL1_RMSK                                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL1_ATB_SEL1_BMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL1_ATB_SEL1_SHFT                                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL2_ADDR                                                           (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x88)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL2_RMSK                                                                  0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL2_ATB_SEL2_BMSK                                                         0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ATB_SEL2_ATB_SEL2_SHFT                                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_ADDR                                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x8c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_RMSK                                                            0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_RCV_DET_LVL_MUX_BMSK                                            0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_RCV_DET_LVL_MUX_SHFT                                              3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_RCV_DET_LVL_BMSK                                                0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_RCV_DET_LVL_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_2_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x90)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_2_RMSK                                                         0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_2_RCV_DET_LVL_2_BMSK                                           0x38
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_2_RCV_DET_LVL_2_SHFT                                              3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_2_RCV_DET_LVL_1_BMSK                                            0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RCV_DETECT_LVL_2_RCV_DET_LVL_1_SHFT                                              0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED1_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x94)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED1_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED1_PRBS_SEED1_BMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED1_PRBS_SEED1_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED2_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x98)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED2_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED2_PRBS_SEED2_BMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED2_PRBS_SEED2_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED3_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x9c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED3_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED3_PRBS_SEED3_BMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED3_PRBS_SEED3_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED4_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xa0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED4_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED4_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED4_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED4_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED4_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED4_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED4_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED4_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED4_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED4_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED4_PRBS_SEED4_BMSK                                                    0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRBS_SEED4_PRBS_SEED4_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_ADDR                                                          (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xa4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_RMSK                                                                0x7f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_SW_CDR_RESET_BMSK                                                   0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_SW_CDR_RESET_SHFT                                                      6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_JITTER_GEN_RESET_BMSK                                               0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_JITTER_GEN_RESET_SHFT                                                  5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_SW_TSYNC_BMSK                                                       0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_SW_TSYNC_SHFT                                                          4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_SW_RSYNC_BMSK                                                        0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_SW_RSYNC_SHFT                                                          3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_RSVD_BMSK                                                            0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_RSVD_SHFT                                                              2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_BIST_TX_RESET_BMSK                                                   0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_BIST_TX_RESET_SHFT                                                     1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_BIST_RX_RESET_BMSK                                                   0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_BIST_RX_RESET_SHFT                                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_MUXES_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xa8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_MUXES_RMSK                                                           0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_MUXES_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_MUXES_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_MUXES_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_MUXES_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_MUXES_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_MUXES_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_MUXES_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_MUXES_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_MUXES_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_MUXES_TSYNC_MUX_BMSK                                                 0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_MUXES_TSYNC_MUX_SHFT                                                   1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_MUXES_RSYNC_MUX_BMSK                                                 0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RESET_GEN_MUXES_RSYNC_MUX_SHFT                                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xac)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_RMSK                                                         0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_TX_DATAPATH_EN_MUX_BMSK                                      0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_TX_DATAPATH_EN_MUX_SHFT                                         5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_TX_DATAPATH_EN_BMSK                                          0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_TX_DATAPATH_EN_SHFT                                             4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_TX_LVL_UPDATE_MUX_BMSK                                        0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_TX_LVL_UPDATE_MUX_SHFT                                          3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_TX_LVL_UPDATE_BMSK                                            0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_TX_LVL_UPDATE_SHFT                                              2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_EMP_EN_MUX_BMSK                                               0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_EMP_EN_MUX_SHFT                                                 1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_EMP_EN_BMSK                                                   0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TRAN_DRVR_EMP_EN_EMP_EN_SHFT                                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_VMODE_CTRL1_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xb0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_VMODE_CTRL1_RMSK                                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_VMODE_CTRL1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_VMODE_CTRL1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_VMODE_CTRL1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_VMODE_CTRL1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_VMODE_CTRL1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_VMODE_CTRL1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_VMODE_CTRL1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_VMODE_CTRL1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_VMODE_CTRL1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_VMODE_CTRL1_VMODE_CTRL1_BMSK                                                  0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_VMODE_CTRL1_VMODE_CTRL1_SHFT                                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_CTRL_1_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xb4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_CTRL_1_RMSK                                                     0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_CTRL_1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_CTRL_1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_CTRL_1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_CTRL_1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_CTRL_1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_CTRL_1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_CTRL_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_CTRL_1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_CTRL_1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_CTRL_1_ALOG_OBSV_BUS_CTRL_1_SEL_BMSK                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_CTRL_1_ALOG_OBSV_BUS_CTRL_1_SEL_SHFT                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_STATUS_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xb8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_STATUS_RMSK                                                               0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_STATUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_STATUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_STATUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_STATUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_STATUS_BIST_STATUS_RO_BMSK                                                0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_STATUS_BIST_STATUS_RO_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_ERROR_COUNT1_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xbc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_ERROR_COUNT1_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_ERROR_COUNT1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_ERROR_COUNT1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_ERROR_COUNT1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_ERROR_COUNT1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_ERROR_COUNT1_BIST_ERROR_COUNT1_STATUS_BMSK                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_ERROR_COUNT1_BIST_ERROR_COUNT1_STATUS_SHFT                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_ERROR_COUNT2_ADDR                                                  (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xc0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_ERROR_COUNT2_RMSK                                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_ERROR_COUNT2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_ERROR_COUNT2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_ERROR_COUNT2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_ERROR_COUNT2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_ERROR_COUNT2_BIST_ERROR_COUNT2_STATUS_BMSK                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_BIST_ERROR_COUNT2_BIST_ERROR_COUNT2_STATUS_SHFT                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_STATUS_1_ADDR                                             (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xc4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_STATUS_1_RMSK                                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_STATUS_1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_STATUS_1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_STATUS_1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_STATUS_1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_STATUS_1_ALOG_OBSV_BUS_STATUS_1_BMSK                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_ALOG_OBSV_BUS_STATUS_1_ALOG_OBSV_BUS_STATUS_1_SHFT                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_DIG_CONFIG_ADDR                                                    (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xc8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_DIG_CONFIG_RMSK                                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_DIG_CONFIG_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_DIG_CONFIG_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_DIG_CONFIG_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_DIG_CONFIG_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_DIG_CONFIG_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_DIG_CONFIG_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_DIG_CONFIG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_DIG_CONFIG_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_DIG_CONFIG_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_DIG_CONFIG_RSVD_BMSK                                                     0xfe
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_DIG_CONFIG_RSVD_SHFT                                                        1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_DIG_CONFIG_LANE_PWRDN_B_BMSK                                              0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_LANE_DIG_CONFIG_LANE_PWRDN_B_SHFT                                                0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PI_QEC_CTRL_ADDR                                                        (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xcc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PI_QEC_CTRL_RMSK                                                              0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PI_QEC_CTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PI_QEC_CTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PI_QEC_CTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PI_QEC_CTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PI_QEC_CTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PI_QEC_CTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PI_QEC_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PI_QEC_CTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PI_QEC_CTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PI_QEC_CTRL_PI_QEC_CTRL_BMSK                                                  0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PI_QEC_CTRL_PI_QEC_CTRL_SHFT                                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_EMPH_ADDR                                                           (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xd0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_EMPH_RMSK                                                                 0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_EMPH_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_EMPH_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_EMPH_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_EMPH_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_EMPH_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_EMPH_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_EMPH_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_EMPH_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_EMPH_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_EMPH_PREEMPH_VAL_MUX_BMSK                                                 0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_EMPH_PREEMPH_VAL_MUX_SHFT                                                    5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_EMPH_PREEMPH_BMSK                                                         0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_PRE_EMPH_PREEMPH_SHFT                                                            0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SW_RESET_ADDR                                                           (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xd4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SW_RESET_RMSK                                                                  0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SW_RESET_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SW_RESET_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SW_RESET_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SW_RESET_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SW_RESET_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SW_RESET_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SW_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SW_RESET_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SW_RESET_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SW_RESET_SW_RESET_BMSK                                                         0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SW_RESET_SW_RESET_SHFT                                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_ADDR                                                            (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xd8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_RMSK                                                                  0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_TX_BAND_RATE3_BMSK                                                    0xc0
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_TX_BAND_RATE3_SHFT                                                       6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_TX_BAND_RATE2_BMSK                                                    0x30
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_TX_BAND_RATE2_SHFT                                                       4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_TX_BAND_RATE1_BMSK                                                     0xc
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_TX_BAND_RATE1_SHFT                                                       2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_TX_BAND_RATE0_BMSK                                                     0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BAND_TX_BAND_RATE0_SHFT                                                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL0_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xdc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL0_RMSK                                                               0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL0_SLEW_CNTL_RATE1_BMSK                                               0x38
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL0_SLEW_CNTL_RATE1_SHFT                                                  3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL0_SLEW_CNTL_RATE0_BMSK                                                0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL0_SLEW_CNTL_RATE0_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL1_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xe0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL1_RMSK                                                               0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL1_SLEW_CNTL_RATE3_BMSK                                               0x38
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL1_SLEW_CNTL_RATE3_SHFT                                                  3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL1_SLEW_CNTL_RATE2_BMSK                                                0x7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_SLEW_CNTL1_SLEW_CNTL_RATE2_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_ADDR                                                   (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xe4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_RMSK                                                         0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_SEL_20B_10B_RATE3_BMSK                                       0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_SEL_20B_10B_RATE3_SHFT                                          7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_SEL_20B_10B_RATE2_BMSK                                       0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_SEL_20B_10B_RATE2_SHFT                                          6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_SEL_20B_10B_RATE1_BMSK                                       0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_SEL_20B_10B_RATE1_SHFT                                          5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_SEL_20B_10B_RATE0_BMSK                                       0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_SEL_20B_10B_RATE0_SHFT                                          4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_SEL_10B_8B_RATE3_BMSK                                         0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_SEL_10B_8B_RATE3_SHFT                                           3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_SEL_10B_8B_RATE2_BMSK                                         0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_SEL_10B_8B_RATE2_SHFT                                           2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_SEL_10B_8B_RATE1_BMSK                                         0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_SEL_10B_8B_RATE1_SHFT                                           1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_SEL_10B_8B_RATE0_BMSK                                         0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_INTERFACE_SELECT_SEL_10B_8B_RATE0_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE210_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xe8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE210_RMSK                                           0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE210_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE210_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE210_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE210_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE210_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE210_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE210_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE210_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE210_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE210_Q_PI_UPPER_THRESH1_RATE210_BMSK                0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE210_Q_PI_UPPER_THRESH1_RATE210_SHFT                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE3_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xec)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE3_RMSK                                             0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE3_Q_PI_UPPER_THRESH1_RATE3_BMSK                    0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH1_RATE3_Q_PI_UPPER_THRESH1_RATE3_SHFT                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE210_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xf0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE210_RMSK                                           0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE210_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE210_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE210_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE210_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE210_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE210_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE210_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE210_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE210_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE210_Q_PI_UPPER_THRESH2_RATE210_BMSK                0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE210_Q_PI_UPPER_THRESH2_RATE210_SHFT                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE3_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xf4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE3_RMSK                                             0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE3_Q_PI_UPPER_THRESH2_RATE3_BMSK                    0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH2_RATE3_Q_PI_UPPER_THRESH2_RATE3_SHFT                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE210_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xf8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE210_RMSK                                           0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE210_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE210_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE210_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE210_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE210_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE210_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE210_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE210_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE210_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE210_Q_PI_UPPER_THRESH3_RATE210_BMSK                0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE210_Q_PI_UPPER_THRESH3_RATE210_SHFT                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE3_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0xfc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE3_RMSK                                             0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE3_Q_PI_UPPER_THRESH3_RATE3_BMSK                    0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH3_RATE3_Q_PI_UPPER_THRESH3_RATE3_SHFT                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE210_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x100)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE210_RMSK                                           0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE210_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE210_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE210_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE210_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE210_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE210_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE210_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE210_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE210_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE210_Q_PI_UPPER_THRESH4_RATE210_BMSK                0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE210_Q_PI_UPPER_THRESH4_RATE210_SHFT                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE3_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x104)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE3_RMSK                                             0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE3_Q_PI_UPPER_THRESH4_RATE3_BMSK                    0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH4_RATE3_Q_PI_UPPER_THRESH4_RATE3_SHFT                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE210_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x108)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE210_RMSK                                           0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE210_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE210_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE210_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE210_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE210_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE210_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE210_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE210_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE210_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE210_Q_PI_UPPER_THRESH5_RATE210_BMSK                0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE210_Q_PI_UPPER_THRESH5_RATE210_SHFT                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE3_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x10c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE3_RMSK                                             0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE3_Q_PI_UPPER_THRESH5_RATE3_BMSK                    0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH5_RATE3_Q_PI_UPPER_THRESH5_RATE3_SHFT                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE210_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x110)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE210_RMSK                                           0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE210_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE210_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE210_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE210_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE210_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE210_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE210_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE210_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE210_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE210_Q_PI_UPPER_THRESH6_RATE210_BMSK                0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE210_Q_PI_UPPER_THRESH6_RATE210_SHFT                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE3_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x114)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE3_RMSK                                             0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE3_Q_PI_UPPER_THRESH6_RATE3_BMSK                    0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH6_RATE3_Q_PI_UPPER_THRESH6_RATE3_SHFT                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE210_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x118)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE210_RMSK                                           0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE210_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE210_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE210_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE210_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE210_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE210_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE210_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE210_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE210_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE210_Q_PI_UPPER_THRESH7_RATE210_BMSK                0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE210_Q_PI_UPPER_THRESH7_RATE210_SHFT                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE3_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x11c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE3_RMSK                                             0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE3_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE3_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE3_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE3_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE3_Q_PI_UPPER_THRESH7_RATE3_BMSK                    0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_RX_MARG_COARSE_THRESH7_RATE3_Q_PI_UPPER_THRESH7_RATE3_SHFT                       0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DIG_BKUP_CTRL_ADDR                                                      (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x120)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DIG_BKUP_CTRL_RMSK                                                            0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DIG_BKUP_CTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DIG_BKUP_CTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DIG_BKUP_CTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DIG_BKUP_CTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DIG_BKUP_CTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DIG_BKUP_CTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DIG_BKUP_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DIG_BKUP_CTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DIG_BKUP_CTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DIG_BKUP_CTRL_RSVD_BMSK                                                       0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DIG_BKUP_CTRL_RSVD_SHFT                                                          0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS0_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x124)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS0_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS0_DEBUG_BUS_7_0_BMSK                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS0_DEBUG_BUS_7_0_SHFT                                                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS1_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x128)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS1_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS1_DEBUG_BUS_15_8_BMSK                                                0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS1_DEBUG_BUS_15_8_SHFT                                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS2_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x12c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS2_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS2_DEBUG_BUS_23_16_BMSK                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS2_DEBUG_BUS_23_16_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS3_ADDR                                                         (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x130)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS3_RMSK                                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS3_DEBUG_BUS_31_24_BMSK                                               0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_DEBUG_BUS3_DEBUG_BUS_31_24_SHFT                                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BKUP_RO_BUS_ADDR                                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_USB43DP_QSERDES_TXB_USB4PHY_QMP_TX_REG_BASE      + 0x134)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BKUP_RO_BUS_RMSK                                                           0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BKUP_RO_BUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BKUP_RO_BUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BKUP_RO_BUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BKUP_RO_BUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BKUP_RO_BUS_TX_BKUP_READ_BUS_BMSK                                          0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_QSERDES_TXB_TX_BKUP_RO_BUS_TX_BKUP_READ_BUS_SHFT                                             0

/*----------------------------------------------------------------------------
 * MODULE: AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM
 *--------------------------------------------------------------------------*/

#define AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE                                 (AHB2PHY_1_AHB2PHY_1_BASE      + 0x00005000)
#define AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE_SIZE                            0x40
#define AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE_USED                            0x3c

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_ADDR                                          (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE      + 0x0)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_RMSK                                                0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_USB3_ONLY_MODE_PLL_SEL_BMSK                         0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_USB3_ONLY_MODE_PLL_SEL_SHFT                            5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_DP_TUNNELING_PLL_POWER_MODE_SEL_BMSK                0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_DP_TUNNELING_PLL_POWER_MODE_SEL_SHFT                   4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_DP_TUNNELING_CLOCK_GEN_EN_BMSK                       0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_DP_TUNNELING_CLOCK_GEN_EN_SHFT                         3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_USB4_PHY_MODE_BMSK                                   0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_USB4_PHY_MODE_SHFT                                     2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_USB3DP_PHY_MODE_BMSK                                 0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PHY_MODE_CTRL_USB3DP_PHY_MODE_SHFT                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SW_RESET_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE      + 0x4)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SW_RESET_RMSK                                                      0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SW_RESET_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SW_RESET_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SW_RESET_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SW_RESET_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SW_RESET_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SW_RESET_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SW_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SW_RESET_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SW_RESET_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SW_RESET_SW_RESET_BMSK                                             0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SW_RESET_SW_RESET_SHFT                                               0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_POWER_DOWN_CTRL_ADDR                                        (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE      + 0x8)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_POWER_DOWN_CTRL_RMSK                                               0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_POWER_DOWN_CTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_POWER_DOWN_CTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_POWER_DOWN_CTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_POWER_DOWN_CTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_POWER_DOWN_CTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_POWER_DOWN_CTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_POWER_DOWN_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_POWER_DOWN_CTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_POWER_DOWN_CTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_POWER_DOWN_CTRL_PLACEHOLDER_CLK_EN_BMSK                            0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_POWER_DOWN_CTRL_PLACEHOLDER_CLK_EN_SHFT                              1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_POWER_DOWN_CTRL_SW_PWRDN_B_BMSK                                    0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_POWER_DOWN_CTRL_SW_PWRDN_B_SHFT                                      0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SWI_CTRL_ADDR                                               (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE      + 0xc)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SWI_CTRL_RMSK                                                      0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SWI_CTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SWI_CTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SWI_CTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SWI_CTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SWI_CTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SWI_CTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SWI_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SWI_CTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SWI_CTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SWI_CTRL_RSVD_BMSK                                                 0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_SWI_CTRL_RSVD_SHFT                                                   0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_ADDR                                             (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE      + 0x10)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_RMSK                                                   0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_SW_L1_CMN_SEL_MUX_BMSK                                 0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_SW_L1_CMN_SEL_MUX_SHFT                                    7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_SW_L1_CMN_SEL_BMSK                                     0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_SW_L1_CMN_SEL_SHFT                                        6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_SW_L0_CMN_SEL_MUX_BMSK                                 0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_SW_L0_CMN_SEL_MUX_SHFT                                    5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_SW_L0_CMN_SEL_BMSK                                     0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_SW_L0_CMN_SEL_SHFT                                        4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_HW_PORTSELECT_SEL_BMSK                                  0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_HW_PORTSELECT_SEL_SHFT                                    3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_PORTSELECT_POLARITY_BMSK                                0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_PORTSELECT_POLARITY_SHFT                                  2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_SW_PORTSELECT_MUX_BMSK                                  0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_SW_PORTSELECT_MUX_SHFT                                    1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_SW_PORTSELECT_BMSK                                      0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_CTRL_SW_PORTSELECT_SHFT                                        0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE      + 0x14)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_RMSK                                             0x1f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_SW_L1_PWRDN_B_MUX_BMSK                           0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_SW_L1_PWRDN_B_MUX_SHFT                              4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_SW_L1_PWRDN_B_BMSK                                0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_SW_L1_PWRDN_B_SHFT                                  3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_SW_L0_PWRDN_B_MUX_BMSK                            0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_SW_L0_PWRDN_B_MUX_SHFT                              2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_SW_L0_PWRDN_B_BMSK                                0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_SW_L0_PWRDN_B_SHFT                                  1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_UNUSED_LANE_PWRDN_EN_BMSK                         0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_PWRDN_CTRL_UNUSED_LANE_PWRDN_EN_SHFT                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DP_BIST_CFG_0_ADDR                                          (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE      + 0x18)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DP_BIST_CFG_0_RMSK                                                 0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DP_BIST_CFG_0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DP_BIST_CFG_0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DP_BIST_CFG_0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DP_BIST_CFG_0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DP_BIST_CFG_0_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DP_BIST_CFG_0_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DP_BIST_CFG_0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DP_BIST_CFG_0_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DP_BIST_CFG_0_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DP_BIST_CFG_0_SW_DP_BIST_SEL_BMSK                                  0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DP_BIST_CFG_0_SW_DP_BIST_SEL_SHFT                                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE      + 0x1c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_RMSK                                             0x3f
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_SW_USB4PHY_RESET_MUX_BMSK                        0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_SW_USB4PHY_RESET_MUX_SHFT                           5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_SW_USB4PHY_RESET_BMSK                            0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_SW_USB4PHY_RESET_SHFT                               4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_SW_USB3PHY_RESET_MUX_BMSK                         0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_SW_USB3PHY_RESET_MUX_SHFT                           3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_SW_USB3PHY_RESET_BMSK                             0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_SW_USB3PHY_RESET_SHFT                               2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_SW_DPPHY_RESET_MUX_BMSK                           0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_SW_DPPHY_RESET_MUX_SHFT                             1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_SW_DPPHY_RESET_BMSK                               0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL1_SW_DPPHY_RESET_SHFT                                 0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE      + 0x20)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_RMSK                                             0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_SW_C1_RESET_MUX_BMSK                             0x80
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_SW_C1_RESET_MUX_SHFT                                7
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_HW_C1_RESET_BMSK                                 0x40
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_HW_C1_RESET_SHFT                                    6
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_SW_C1_RESET_BMSK                                 0x20
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_SW_C1_RESET_SHFT                                    5
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_SW_C0_PWRDN_B_MUX_BMSK                           0x10
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_SW_C0_PWRDN_B_MUX_SHFT                              4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_SW_C0_PWRDN_B_BMSK                                0x8
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_SW_C0_PWRDN_B_SHFT                                  3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_SW_C0_RESET_MUX_BMSK                              0x4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_SW_C0_RESET_MUX_SHFT                                2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_HW_C0_RESET_BMSK                                  0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_HW_C0_RESET_SHFT                                    1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_SW_C0_RESET_BMSK                                  0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_RESET_OVRD_CTRL2_SW_C0_RESET_SHFT                                    0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DBG_CLK_MUX_CTRL_ADDR                                       (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE      + 0x24)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DBG_CLK_MUX_CTRL_RMSK                                             0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DBG_CLK_MUX_CTRL_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DBG_CLK_MUX_CTRL_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DBG_CLK_MUX_CTRL_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DBG_CLK_MUX_CTRL_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DBG_CLK_MUX_CTRL_OUT(v)            \
                out_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DBG_CLK_MUX_CTRL_ADDR,v)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DBG_CLK_MUX_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DBG_CLK_MUX_CTRL_ADDR,m,v,HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DBG_CLK_MUX_CTRL_IN)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DBG_CLK_MUX_CTRL_DEBUG_CLK_DIV_BMSK                               0xf0
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DBG_CLK_MUX_CTRL_DEBUG_CLK_DIV_SHFT                                  4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DBG_CLK_MUX_CTRL_DEBUG_CLK_SEL_BMSK                                0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_DBG_CLK_MUX_CTRL_DEBUG_CLK_SEL_SHFT                                  0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_STATUS_ADDR                                           (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE      + 0x28)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_STATUS_RMSK                                                  0x3
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_STATUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_STATUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_STATUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_STATUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_STATUS_PORTSELECT_PCS_BMSK                                   0x2
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_STATUS_PORTSELECT_PCS_SHFT                                     1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_STATUS_PORTSELECT_RAW_BMSK                                   0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_TYPEC_STATUS_PORTSELECT_RAW_SHFT                                     0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PLACEHOLDER_STATUS_ADDR                                     (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE      + 0x2c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PLACEHOLDER_STATUS_RMSK                                            0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PLACEHOLDER_STATUS_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PLACEHOLDER_STATUS_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PLACEHOLDER_STATUS_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PLACEHOLDER_STATUS_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PLACEHOLDER_STATUS_PLACEHOLDER_STATUS_BMSK                         0x1
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_PLACEHOLDER_STATUS_PLACEHOLDER_STATUS_SHFT                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID0_ADDR                                           (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE      + 0x30)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID0_RMSK                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID0_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID0_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID0_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID0_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID0_STEP_7_0_BMSK                                        0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID0_STEP_7_0_SHFT                                           0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID1_ADDR                                           (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE      + 0x34)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID1_RMSK                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID1_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID1_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID1_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID1_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID1_STEP_15_8_BMSK                                       0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID1_STEP_15_8_SHFT                                          0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID2_ADDR                                           (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE      + 0x38)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID2_RMSK                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID2_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID2_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID2_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID2_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID2_MINOR_7_0_BMSK                                       0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID2_MINOR_7_0_SHFT                                          0

#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID3_ADDR                                           (AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_USB43DP_COM_USB4PHY_COM_REG_BASE      + 0x3c)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID3_RMSK                                                 0xff
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID3_IN                    \
                in_dword(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID3_ADDR)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID3_INM(m)            \
                in_dword_masked(HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID3_ADDR, m)
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID3_MAJOR_BMSK                                           0xf0
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID3_MAJOR_SHFT                                              4
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID3_MINOR_11_8_BMSK                                       0xf
#define HWIO_AHB2PHY_1_QUSB4PHY_SS_0_USB43DP_COM_REVISION_ID3_MINOR_11_8_SHFT                                         0


#endif /* __HAL_DP_PHY_1_4_1_HWIO_H__ */
