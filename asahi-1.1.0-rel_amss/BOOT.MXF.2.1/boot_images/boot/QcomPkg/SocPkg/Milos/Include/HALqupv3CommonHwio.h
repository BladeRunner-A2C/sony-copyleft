#ifndef HALQUPV3COMMONHWIO_H
#define HALQUPV3COMMONHWIO_H
/*
===========================================================================
*/
/**
    @file HALqupv3CommonHwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM6xxx (Milos) [milos_v1.0_p3q1r25]
 
    This file contains HWIO register definitions for the following modules:
        QUPV3_0_QUPV3_COMMON


    Generation parameters: 
    { 'explicit-addressing': True,
      'filename': 'HALqupv3CommonHwio.h',
      'header': '#include "msmhwiobase.h"',
      'ignore-prefixes': True,
      'modules': ['QUPV3_0_QUPV3_COMMON'],
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

/*----------------------------------------------------------------------------
 * MODULE: QUPV3_COMMON
 *--------------------------------------------------------------------------*/

#define QUPV3_COMMON_REG_BASE                                                                       (QUPV3_0_QUPV3_ID_1_BASE      + 0x000c0000)
#define QUPV3_COMMON_REG_BASE_SIZE                                                                  0x2000
#define QUPV3_COMMON_REG_BASE_USED                                                                  0x1fac
#define QUPV3_COMMON_REG_BASE_OFFS                                                                  0x000c0000

#define HWIO_QUPV3_HW_PARAM_ADDR(x)                                                                 ((x) + 0x0)
#define HWIO_QUPV3_HW_PARAM_OFFS                                                                    (0x0)
#define HWIO_QUPV3_HW_PARAM_RMSK                                                                    0xffffff0f
#define HWIO_QUPV3_HW_PARAM_IN(x)            \
                in_dword(HWIO_QUPV3_HW_PARAM_ADDR(x))
#define HWIO_QUPV3_HW_PARAM_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_HW_PARAM_ADDR(x), m)
#define HWIO_QUPV3_HW_PARAM_QUPV3_AHB_M_ADDR_W_BMSK                                                 0xff000000
#define HWIO_QUPV3_HW_PARAM_QUPV3_AHB_M_ADDR_W_SHFT                                                         24
#define HWIO_QUPV3_HW_PARAM_QUPV3_NUM_GPIIS_BMSK                                                      0xff0000
#define HWIO_QUPV3_HW_PARAM_QUPV3_NUM_GPIIS_SHFT                                                            16
#define HWIO_QUPV3_HW_PARAM_QUPV3_NUM_SES_BMSK                                                          0xff00
#define HWIO_QUPV3_HW_PARAM_QUPV3_NUM_SES_SHFT                                                               8
#define HWIO_QUPV3_HW_PARAM_QUPV3_WRAPPER_ID_BMSK                                                          0xf
#define HWIO_QUPV3_HW_PARAM_QUPV3_WRAPPER_ID_SHFT                                                            0

#define HWIO_QUPV3_HW_VERSION_ADDR(x)                                                               ((x) + 0x4)
#define HWIO_QUPV3_HW_VERSION_OFFS                                                                  (0x4)
#define HWIO_QUPV3_HW_VERSION_RMSK                                                                  0xffffffff
#define HWIO_QUPV3_HW_VERSION_IN(x)            \
                in_dword(HWIO_QUPV3_HW_VERSION_ADDR(x))
#define HWIO_QUPV3_HW_VERSION_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_HW_VERSION_ADDR(x), m)
#define HWIO_QUPV3_HW_VERSION_MAJOR_BMSK                                                            0xf0000000
#define HWIO_QUPV3_HW_VERSION_MAJOR_SHFT                                                                    28
#define HWIO_QUPV3_HW_VERSION_MINOR_BMSK                                                             0xfff0000
#define HWIO_QUPV3_HW_VERSION_MINOR_SHFT                                                                    16
#define HWIO_QUPV3_HW_VERSION_STEP_BMSK                                                                 0xffff
#define HWIO_QUPV3_HW_VERSION_STEP_SHFT                                                                      0

#define HWIO_QUPV3_STATUS_ADDR(x)                                                                   ((x) + 0x8)
#define HWIO_QUPV3_STATUS_OFFS                                                                      (0x8)
#define HWIO_QUPV3_STATUS_RMSK                                                                             0x1
#define HWIO_QUPV3_STATUS_IN(x)            \
                in_dword(HWIO_QUPV3_STATUS_ADDR(x))
#define HWIO_QUPV3_STATUS_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_STATUS_ADDR(x), m)
#define HWIO_QUPV3_STATUS_GSI_BUSY_BMSK                                                                    0x1
#define HWIO_QUPV3_STATUS_GSI_BUSY_SHFT                                                                      0

#define HWIO_QUPV3_EXT_AHB_ARB_CFG_ADDR(x)                                                          ((x) + 0x100)
#define HWIO_QUPV3_EXT_AHB_ARB_CFG_OFFS                                                             (0x100)
#define HWIO_QUPV3_EXT_AHB_ARB_CFG_RMSK                                                                    0xf
#define HWIO_QUPV3_EXT_AHB_ARB_CFG_IN(x)            \
                in_dword(HWIO_QUPV3_EXT_AHB_ARB_CFG_ADDR(x))
#define HWIO_QUPV3_EXT_AHB_ARB_CFG_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_EXT_AHB_ARB_CFG_ADDR(x), m)
#define HWIO_QUPV3_EXT_AHB_ARB_CFG_OUT(x, v)            \
                out_dword(HWIO_QUPV3_EXT_AHB_ARB_CFG_ADDR(x),v)
#define HWIO_QUPV3_EXT_AHB_ARB_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_QUPV3_EXT_AHB_ARB_CFG_ADDR(x),m,v,HWIO_QUPV3_EXT_AHB_ARB_CFG_IN(x))
#define HWIO_QUPV3_EXT_AHB_ARB_CFG_ARB_TRANSITION_DEPENDS_HREADYIN_IDLE_BMSK                               0x8
#define HWIO_QUPV3_EXT_AHB_ARB_CFG_ARB_TRANSITION_DEPENDS_HREADYIN_IDLE_SHFT                                 3
#define HWIO_QUPV3_EXT_AHB_ARB_CFG_UNLOCK_DEPENDS_HSEL_BMSK                                                0x4
#define HWIO_QUPV3_EXT_AHB_ARB_CFG_UNLOCK_DEPENDS_HSEL_SHFT                                                  2
#define HWIO_QUPV3_EXT_AHB_ARB_CFG_USE_DYNAMIC_HSEL_BMSK                                                   0x2
#define HWIO_QUPV3_EXT_AHB_ARB_CFG_USE_DYNAMIC_HSEL_SHFT                                                     1
#define HWIO_QUPV3_EXT_AHB_ARB_CFG_ARBITRATION_TYPE_BMSK                                                   0x1
#define HWIO_QUPV3_EXT_AHB_ARB_CFG_ARBITRATION_TYPE_SHFT                                                     0

#define HWIO_QUPV3_INT_AHB_ARB_CFG_ADDR(x)                                                          ((x) + 0x104)
#define HWIO_QUPV3_INT_AHB_ARB_CFG_OFFS                                                             (0x104)
#define HWIO_QUPV3_INT_AHB_ARB_CFG_RMSK                                                                    0xf
#define HWIO_QUPV3_INT_AHB_ARB_CFG_IN(x)            \
                in_dword(HWIO_QUPV3_INT_AHB_ARB_CFG_ADDR(x))
#define HWIO_QUPV3_INT_AHB_ARB_CFG_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_INT_AHB_ARB_CFG_ADDR(x), m)
#define HWIO_QUPV3_INT_AHB_ARB_CFG_OUT(x, v)            \
                out_dword(HWIO_QUPV3_INT_AHB_ARB_CFG_ADDR(x),v)
#define HWIO_QUPV3_INT_AHB_ARB_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_QUPV3_INT_AHB_ARB_CFG_ADDR(x),m,v,HWIO_QUPV3_INT_AHB_ARB_CFG_IN(x))
#define HWIO_QUPV3_INT_AHB_ARB_CFG_ARB_TRANSITION_DEPENDS_HREADYIN_IDLE_BMSK                               0x8
#define HWIO_QUPV3_INT_AHB_ARB_CFG_ARB_TRANSITION_DEPENDS_HREADYIN_IDLE_SHFT                                 3
#define HWIO_QUPV3_INT_AHB_ARB_CFG_UNLOCK_DEPENDS_HSEL_BMSK                                                0x4
#define HWIO_QUPV3_INT_AHB_ARB_CFG_UNLOCK_DEPENDS_HSEL_SHFT                                                  2
#define HWIO_QUPV3_INT_AHB_ARB_CFG_USE_DYNAMIC_HSEL_BMSK                                                   0x2
#define HWIO_QUPV3_INT_AHB_ARB_CFG_USE_DYNAMIC_HSEL_SHFT                                                     1
#define HWIO_QUPV3_INT_AHB_ARB_CFG_ARBITRATION_TYPE_BMSK                                                   0x1
#define HWIO_QUPV3_INT_AHB_ARB_CFG_ARBITRATION_TYPE_SHFT                                                     0

#define HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_ADDR(x)                                                    ((x) + 0x108)
#define HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_OFFS                                                       (0x108)
#define HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_RMSK                                                              0xf
#define HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_IN(x)            \
                in_dword(HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_ADDR(x))
#define HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_ADDR(x), m)
#define HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_OUT(x, v)            \
                out_dword(HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_ADDR(x),v)
#define HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_ADDR(x),m,v,HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_IN(x))
#define HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_ARB_TRANSITION_DEPENDS_HREADYIN_IDLE_BMSK                         0x8
#define HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_ARB_TRANSITION_DEPENDS_HREADYIN_IDLE_SHFT                           3
#define HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_UNLOCK_DEPENDS_HSEL_BMSK                                          0x4
#define HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_UNLOCK_DEPENDS_HSEL_SHFT                                            2
#define HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_USE_DYNAMIC_HSEL_BMSK                                             0x2
#define HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_USE_DYNAMIC_HSEL_SHFT                                               1
#define HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_ARBITRATION_TYPE_BMSK                                             0x1
#define HWIO_QUPV3_GSI_SLAVE_AHB_ARB_CFG_ARBITRATION_TYPE_SHFT                                               0

#define HWIO_QUPV3_SE_IF_IRQ_MASKED_ADDR(x)                                                         ((x) + 0x110)
#define HWIO_QUPV3_SE_IF_IRQ_MASKED_OFFS                                                            (0x110)
#define HWIO_QUPV3_SE_IF_IRQ_MASKED_RMSK                                                            0xffffffff
#define HWIO_QUPV3_SE_IF_IRQ_MASKED_IN(x)            \
                in_dword(HWIO_QUPV3_SE_IF_IRQ_MASKED_ADDR(x))
#define HWIO_QUPV3_SE_IF_IRQ_MASKED_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_SE_IF_IRQ_MASKED_ADDR(x), m)
#define HWIO_QUPV3_SE_IF_IRQ_MASKED_SE_IF_IRQ_MASKED_BMSK                                           0xffffffff
#define HWIO_QUPV3_SE_IF_IRQ_MASKED_SE_IF_IRQ_MASKED_SHFT                                                    0

#define HWIO_QUPV3_SE_HMEMTYPE_CFG_ADDR(x)                                                          ((x) + 0x114)
#define HWIO_QUPV3_SE_HMEMTYPE_CFG_OFFS                                                             (0x114)
#define HWIO_QUPV3_SE_HMEMTYPE_CFG_RMSK                                                                  0x1ff
#define HWIO_QUPV3_SE_HMEMTYPE_CFG_IN(x)            \
                in_dword(HWIO_QUPV3_SE_HMEMTYPE_CFG_ADDR(x))
#define HWIO_QUPV3_SE_HMEMTYPE_CFG_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_SE_HMEMTYPE_CFG_ADDR(x), m)
#define HWIO_QUPV3_SE_HMEMTYPE_CFG_OUT(x, v)            \
                out_dword(HWIO_QUPV3_SE_HMEMTYPE_CFG_ADDR(x),v)
#define HWIO_QUPV3_SE_HMEMTYPE_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_QUPV3_SE_HMEMTYPE_CFG_ADDR(x),m,v,HWIO_QUPV3_SE_HMEMTYPE_CFG_IN(x))
#define HWIO_QUPV3_SE_HMEMTYPE_CFG_HMEMTYPE_WRITE_LAST_BMSK                                              0x1c0
#define HWIO_QUPV3_SE_HMEMTYPE_CFG_HMEMTYPE_WRITE_LAST_SHFT                                                  6
#define HWIO_QUPV3_SE_HMEMTYPE_CFG_HMEMTYPE_WRITE_MID_TRANS_BMSK                                          0x38
#define HWIO_QUPV3_SE_HMEMTYPE_CFG_HMEMTYPE_WRITE_MID_TRANS_SHFT                                             3
#define HWIO_QUPV3_SE_HMEMTYPE_CFG_HMEMTYPE_READ_BMSK                                                      0x7
#define HWIO_QUPV3_SE_HMEMTYPE_CFG_HMEMTYPE_READ_SHFT                                                        0

#define HWIO_QUPV3_SE_AHB_M_CFG_ADDR(x)                                                             ((x) + 0x118)
#define HWIO_QUPV3_SE_AHB_M_CFG_OFFS                                                                (0x118)
#define HWIO_QUPV3_SE_AHB_M_CFG_RMSK                                                                       0x1
#define HWIO_QUPV3_SE_AHB_M_CFG_IN(x)            \
                in_dword(HWIO_QUPV3_SE_AHB_M_CFG_ADDR(x))
#define HWIO_QUPV3_SE_AHB_M_CFG_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_SE_AHB_M_CFG_ADDR(x), m)
#define HWIO_QUPV3_SE_AHB_M_CFG_OUT(x, v)            \
                out_dword(HWIO_QUPV3_SE_AHB_M_CFG_ADDR(x),v)
#define HWIO_QUPV3_SE_AHB_M_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_QUPV3_SE_AHB_M_CFG_ADDR(x),m,v,HWIO_QUPV3_SE_AHB_M_CFG_IN(x))
#define HWIO_QUPV3_SE_AHB_M_CFG_AHB_M_CLK_CGC_ON_BMSK                                                      0x1
#define HWIO_QUPV3_SE_AHB_M_CFG_AHB_M_CLK_CGC_ON_SHFT                                                        0

#define HWIO_QUPV3_COMMON_CFG_ADDR(x)                                                               ((x) + 0x120)
#define HWIO_QUPV3_COMMON_CFG_OFFS                                                                  (0x120)
#define HWIO_QUPV3_COMMON_CFG_RMSK                                                                        0x7f
#define HWIO_QUPV3_COMMON_CFG_IN(x)            \
                in_dword(HWIO_QUPV3_COMMON_CFG_ADDR(x))
#define HWIO_QUPV3_COMMON_CFG_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_COMMON_CFG_ADDR(x), m)
#define HWIO_QUPV3_COMMON_CFG_OUT(x, v)            \
                out_dword(HWIO_QUPV3_COMMON_CFG_ADDR(x),v)
#define HWIO_QUPV3_COMMON_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_QUPV3_COMMON_CFG_ADDR(x),m,v,HWIO_QUPV3_COMMON_CFG_IN(x))
#define HWIO_QUPV3_COMMON_CFG_TLV_IN_TIMESTAMP_IRQ_STATUS_DISABLE_BMSK                                    0x40
#define HWIO_QUPV3_COMMON_CFG_TLV_IN_TIMESTAMP_IRQ_STATUS_DISABLE_SHFT                                       6
#define HWIO_QUPV3_COMMON_CFG_TLV_IN_TIMESTAMP_IRQ_DISABLE_BMSK                                           0x20
#define HWIO_QUPV3_COMMON_CFG_TLV_IN_TIMESTAMP_IRQ_DISABLE_SHFT                                              5
#define HWIO_QUPV3_COMMON_CFG_TLV_USER_DATA_READ_DIS_BMSK                                                 0x10
#define HWIO_QUPV3_COMMON_CFG_TLV_USER_DATA_READ_DIS_SHFT                                                    4
#define HWIO_QUPV3_COMMON_CFG_TIE_HREADY_IN_LOOPBACK_BMSK                                                  0x8
#define HWIO_QUPV3_COMMON_CFG_TIE_HREADY_IN_LOOPBACK_SHFT                                                    3
#define HWIO_QUPV3_COMMON_CFG_AHB2AHB_POST_EN_MASTER_BMSK                                                  0x4
#define HWIO_QUPV3_COMMON_CFG_AHB2AHB_POST_EN_MASTER_SHFT                                                    2
#define HWIO_QUPV3_COMMON_CFG_AHB2AHB_POST_EN_SLAVE_BMSK                                                   0x2
#define HWIO_QUPV3_COMMON_CFG_AHB2AHB_POST_EN_SLAVE_SHFT                                                     1
#define HWIO_QUPV3_COMMON_CFG_FAST_SWITCH_TO_HIGH_DISABLE_BMSK                                             0x1
#define HWIO_QUPV3_COMMON_CFG_FAST_SWITCH_TO_HIGH_DISABLE_SHFT                                               0

#define HWIO_QUPV3_SE_IF_IRQ_MASKED_H_ADDR(x)                                                       ((x) + 0x124)
#define HWIO_QUPV3_SE_IF_IRQ_MASKED_H_OFFS                                                          (0x124)
#define HWIO_QUPV3_SE_IF_IRQ_MASKED_H_RMSK                                                          0xffffffff
#define HWIO_QUPV3_SE_IF_IRQ_MASKED_H_IN(x)            \
                in_dword(HWIO_QUPV3_SE_IF_IRQ_MASKED_H_ADDR(x))
#define HWIO_QUPV3_SE_IF_IRQ_MASKED_H_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_SE_IF_IRQ_MASKED_H_ADDR(x), m)
#define HWIO_QUPV3_SE_IF_IRQ_MASKED_H_SE_IF_IRQ_MASKED_H_BMSK                                       0xffffffff
#define HWIO_QUPV3_SE_IF_IRQ_MASKED_H_SE_IF_IRQ_MASKED_H_SHFT                                                0

#define HWIO_QUPV3_SYNC_ID_SE_MAP0_ADDR(x)                                                          ((x) + 0x128)
#define HWIO_QUPV3_SYNC_ID_SE_MAP0_OFFS                                                             (0x128)
#define HWIO_QUPV3_SYNC_ID_SE_MAP0_RMSK                                                             0xffffffff
#define HWIO_QUPV3_SYNC_ID_SE_MAP0_IN(x)            \
                in_dword(HWIO_QUPV3_SYNC_ID_SE_MAP0_ADDR(x))
#define HWIO_QUPV3_SYNC_ID_SE_MAP0_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_SYNC_ID_SE_MAP0_ADDR(x), m)
#define HWIO_QUPV3_SYNC_ID_SE_MAP0_OUT(x, v)            \
                out_dword(HWIO_QUPV3_SYNC_ID_SE_MAP0_ADDR(x),v)
#define HWIO_QUPV3_SYNC_ID_SE_MAP0_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_QUPV3_SYNC_ID_SE_MAP0_ADDR(x),m,v,HWIO_QUPV3_SYNC_ID_SE_MAP0_IN(x))
#define HWIO_QUPV3_SYNC_ID_SE_MAP0_SYNC_ID3_SE_BITMAP_BMSK                                          0xff000000
#define HWIO_QUPV3_SYNC_ID_SE_MAP0_SYNC_ID3_SE_BITMAP_SHFT                                                  24
#define HWIO_QUPV3_SYNC_ID_SE_MAP0_SYNC_ID2_SE_BITMAP_BMSK                                            0xff0000
#define HWIO_QUPV3_SYNC_ID_SE_MAP0_SYNC_ID2_SE_BITMAP_SHFT                                                  16
#define HWIO_QUPV3_SYNC_ID_SE_MAP0_SYNC_ID1_SE_BITMAP_BMSK                                              0xff00
#define HWIO_QUPV3_SYNC_ID_SE_MAP0_SYNC_ID1_SE_BITMAP_SHFT                                                   8
#define HWIO_QUPV3_SYNC_ID_SE_MAP0_SYNC_ID0_SE_BITMAP_BMSK                                                0xff
#define HWIO_QUPV3_SYNC_ID_SE_MAP0_SYNC_ID0_SE_BITMAP_SHFT                                                   0

#define HWIO_QUPV3_SYNC_ID_SE_MAP1_ADDR(x)                                                          ((x) + 0x12c)
#define HWIO_QUPV3_SYNC_ID_SE_MAP1_OFFS                                                             (0x12c)
#define HWIO_QUPV3_SYNC_ID_SE_MAP1_RMSK                                                             0xffffffff
#define HWIO_QUPV3_SYNC_ID_SE_MAP1_IN(x)            \
                in_dword(HWIO_QUPV3_SYNC_ID_SE_MAP1_ADDR(x))
#define HWIO_QUPV3_SYNC_ID_SE_MAP1_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_SYNC_ID_SE_MAP1_ADDR(x), m)
#define HWIO_QUPV3_SYNC_ID_SE_MAP1_OUT(x, v)            \
                out_dword(HWIO_QUPV3_SYNC_ID_SE_MAP1_ADDR(x),v)
#define HWIO_QUPV3_SYNC_ID_SE_MAP1_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_QUPV3_SYNC_ID_SE_MAP1_ADDR(x),m,v,HWIO_QUPV3_SYNC_ID_SE_MAP1_IN(x))
#define HWIO_QUPV3_SYNC_ID_SE_MAP1_SYNC_ID7_SE_BITMAP_BMSK                                          0xff000000
#define HWIO_QUPV3_SYNC_ID_SE_MAP1_SYNC_ID7_SE_BITMAP_SHFT                                                  24
#define HWIO_QUPV3_SYNC_ID_SE_MAP1_SYNC_ID6_SE_BITMAP_BMSK                                            0xff0000
#define HWIO_QUPV3_SYNC_ID_SE_MAP1_SYNC_ID6_SE_BITMAP_SHFT                                                  16
#define HWIO_QUPV3_SYNC_ID_SE_MAP1_SYNC_ID5_SE_BITMAP_BMSK                                              0xff00
#define HWIO_QUPV3_SYNC_ID_SE_MAP1_SYNC_ID5_SE_BITMAP_SHFT                                                   8
#define HWIO_QUPV3_SYNC_ID_SE_MAP1_SYNC_ID4_SE_BITMAP_BMSK                                                0xff
#define HWIO_QUPV3_SYNC_ID_SE_MAP1_SYNC_ID4_SE_BITMAP_SHFT                                                   0

#define HWIO_QUPV3_SYNC_DATA_DEBUG_ADDR(x)                                                          ((x) + 0x130)
#define HWIO_QUPV3_SYNC_DATA_DEBUG_OFFS                                                             (0x130)
#define HWIO_QUPV3_SYNC_DATA_DEBUG_RMSK                                                                   0xff
#define HWIO_QUPV3_SYNC_DATA_DEBUG_IN(x)            \
                in_dword(HWIO_QUPV3_SYNC_DATA_DEBUG_ADDR(x))
#define HWIO_QUPV3_SYNC_DATA_DEBUG_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_SYNC_DATA_DEBUG_ADDR(x), m)
#define HWIO_QUPV3_SYNC_DATA_DEBUG_SYNC_DATA_BMSK                                                         0xff
#define HWIO_QUPV3_SYNC_DATA_DEBUG_SYNC_DATA_SHFT                                                            0

#define HWIO_QUPV3_WD_TIMER_CFG_ADDR(x)                                                             ((x) + 0x134)
#define HWIO_QUPV3_WD_TIMER_CFG_OFFS                                                                (0x134)
#define HWIO_QUPV3_WD_TIMER_CFG_RMSK                                                                 0x3ffffff
#define HWIO_QUPV3_WD_TIMER_CFG_IN(x)            \
                in_dword(HWIO_QUPV3_WD_TIMER_CFG_ADDR(x))
#define HWIO_QUPV3_WD_TIMER_CFG_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_WD_TIMER_CFG_ADDR(x), m)
#define HWIO_QUPV3_WD_TIMER_CFG_OUT(x, v)            \
                out_dword(HWIO_QUPV3_WD_TIMER_CFG_ADDR(x),v)
#define HWIO_QUPV3_WD_TIMER_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_QUPV3_WD_TIMER_CFG_ADDR(x),m,v,HWIO_QUPV3_WD_TIMER_CFG_IN(x))
#define HWIO_QUPV3_WD_TIMER_CFG_QUPV3_WD_TIMER_EN_BMSK                                               0x2000000
#define HWIO_QUPV3_WD_TIMER_CFG_QUPV3_WD_TIMER_EN_SHFT                                                      25
#define HWIO_QUPV3_WD_TIMER_CFG_QUPV3_WD_TIMER_MAX_BMSK                                              0x1ffffff
#define HWIO_QUPV3_WD_TIMER_CFG_QUPV3_WD_TIMER_MAX_SHFT                                                      0

#define HWIO_QUPV3_WD_TIMER_STS_ADDR(x)                                                             ((x) + 0x138)
#define HWIO_QUPV3_WD_TIMER_STS_OFFS                                                                (0x138)
#define HWIO_QUPV3_WD_TIMER_STS_RMSK                                                                     0x1ff
#define HWIO_QUPV3_WD_TIMER_STS_IN(x)            \
                in_dword(HWIO_QUPV3_WD_TIMER_STS_ADDR(x))
#define HWIO_QUPV3_WD_TIMER_STS_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_WD_TIMER_STS_ADDR(x), m)
#define HWIO_QUPV3_WD_TIMER_STS_QUPV3_WD_TIMER_INFO_BMSK                                                 0x1fe
#define HWIO_QUPV3_WD_TIMER_STS_QUPV3_WD_TIMER_INFO_SHFT                                                     1
#define HWIO_QUPV3_WD_TIMER_STS_QUPV3_WD_TIMER_EXPIRY_BMSK                                                 0x1
#define HWIO_QUPV3_WD_TIMER_STS_QUPV3_WD_TIMER_EXPIRY_SHFT                                                   0

#define HWIO_QUPV3_TEST_BUS_SEL_ADDR(x)                                                             ((x) + 0x200)
#define HWIO_QUPV3_TEST_BUS_SEL_OFFS                                                                (0x200)
#define HWIO_QUPV3_TEST_BUS_SEL_RMSK                                                                 0xf3f7f7f
#define HWIO_QUPV3_TEST_BUS_SEL_IN(x)            \
                in_dword(HWIO_QUPV3_TEST_BUS_SEL_ADDR(x))
#define HWIO_QUPV3_TEST_BUS_SEL_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_TEST_BUS_SEL_ADDR(x), m)
#define HWIO_QUPV3_TEST_BUS_SEL_OUT(x, v)            \
                out_dword(HWIO_QUPV3_TEST_BUS_SEL_ADDR(x),v)
#define HWIO_QUPV3_TEST_BUS_SEL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_QUPV3_TEST_BUS_SEL_ADDR(x),m,v,HWIO_QUPV3_TEST_BUS_SEL_IN(x))
#define HWIO_QUPV3_TEST_BUS_SEL_NON_AON_IBI_TEST_BUS_SEL_BMSK                                        0xf000000
#define HWIO_QUPV3_TEST_BUS_SEL_NON_AON_IBI_TEST_BUS_SEL_SHFT                                               24
#define HWIO_QUPV3_TEST_BUS_SEL_BRIC_TEST_BUS_SEL_BMSK                                                0x380000
#define HWIO_QUPV3_TEST_BUS_SEL_BRIC_TEST_BUS_SEL_SHFT                                                      19
#define HWIO_QUPV3_TEST_BUS_SEL_SE_WRAPPER_TEST_BUS_SEL_BMSK                                           0x70000
#define HWIO_QUPV3_TEST_BUS_SEL_SE_WRAPPER_TEST_BUS_SEL_SHFT                                                16
#define HWIO_QUPV3_TEST_BUS_SEL_SE_WRAPPER_MASTER_TEST_BUS_SEL_BMSK                                     0x7000
#define HWIO_QUPV3_TEST_BUS_SEL_SE_WRAPPER_MASTER_TEST_BUS_SEL_SHFT                                         12
#define HWIO_QUPV3_TEST_BUS_SEL_SLAVE_BRIDGE_TEST_BUS_SEL_BMSK                                           0xc00
#define HWIO_QUPV3_TEST_BUS_SEL_SLAVE_BRIDGE_TEST_BUS_SEL_SHFT                                              10
#define HWIO_QUPV3_TEST_BUS_SEL_MASTER_BRIDGE_TEST_BUS_SEL_BMSK                                          0x300
#define HWIO_QUPV3_TEST_BUS_SEL_MASTER_BRIDGE_TEST_BUS_SEL_SHFT                                              8
#define HWIO_QUPV3_TEST_BUS_SEL_TOP_TEST_BUS_SEL_BMSK                                                     0x7f
#define HWIO_QUPV3_TEST_BUS_SEL_TOP_TEST_BUS_SEL_SHFT                                                        0

#define HWIO_QUPV3_TEST_BUS_EN_ADDR(x)                                                              ((x) + 0x204)
#define HWIO_QUPV3_TEST_BUS_EN_OFFS                                                                 (0x204)
#define HWIO_QUPV3_TEST_BUS_EN_RMSK                                                                      0x111
#define HWIO_QUPV3_TEST_BUS_EN_IN(x)            \
                in_dword(HWIO_QUPV3_TEST_BUS_EN_ADDR(x))
#define HWIO_QUPV3_TEST_BUS_EN_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_TEST_BUS_EN_ADDR(x), m)
#define HWIO_QUPV3_TEST_BUS_EN_OUT(x, v)            \
                out_dword(HWIO_QUPV3_TEST_BUS_EN_ADDR(x),v)
#define HWIO_QUPV3_TEST_BUS_EN_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_QUPV3_TEST_BUS_EN_ADDR(x),m,v,HWIO_QUPV3_TEST_BUS_EN_IN(x))
#define HWIO_QUPV3_TEST_BUS_EN_SW_TB_TOGGLE_BMSK                                                         0x100
#define HWIO_QUPV3_TEST_BUS_EN_SW_TB_TOGGLE_SHFT                                                             8
#define HWIO_QUPV3_TEST_BUS_EN_TEST_BUS_EN_BMSK                                                           0x10
#define HWIO_QUPV3_TEST_BUS_EN_TEST_BUS_EN_SHFT                                                              4
#define HWIO_QUPV3_TEST_BUS_EN_TEST_BUS_REG_EN_BMSK                                                        0x1
#define HWIO_QUPV3_TEST_BUS_EN_TEST_BUS_REG_EN_SHFT                                                          0

#define HWIO_QUPV3_TEST_BUS_REG_ADDR(x)                                                             ((x) + 0x208)
#define HWIO_QUPV3_TEST_BUS_REG_OFFS                                                                (0x208)
#define HWIO_QUPV3_TEST_BUS_REG_RMSK                                                                0xffffffff
#define HWIO_QUPV3_TEST_BUS_REG_IN(x)            \
                in_dword(HWIO_QUPV3_TEST_BUS_REG_ADDR(x))
#define HWIO_QUPV3_TEST_BUS_REG_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_TEST_BUS_REG_ADDR(x), m)
#define HWIO_QUPV3_TEST_BUS_REG_TEST_BUS_VALUE_BMSK                                                 0xffffffff
#define HWIO_QUPV3_TEST_BUS_REG_TEST_BUS_VALUE_SHFT                                                          0

#define HWIO_QUPV3_HW_EVENTS_MUX_CFG_ADDR(x)                                                        ((x) + 0x20c)
#define HWIO_QUPV3_HW_EVENTS_MUX_CFG_OFFS                                                           (0x20c)
#define HWIO_QUPV3_HW_EVENTS_MUX_CFG_RMSK                                                           0x80003f00
#define HWIO_QUPV3_HW_EVENTS_MUX_CFG_IN(x)            \
                in_dword(HWIO_QUPV3_HW_EVENTS_MUX_CFG_ADDR(x))
#define HWIO_QUPV3_HW_EVENTS_MUX_CFG_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_HW_EVENTS_MUX_CFG_ADDR(x), m)
#define HWIO_QUPV3_HW_EVENTS_MUX_CFG_OUT(x, v)            \
                out_dword(HWIO_QUPV3_HW_EVENTS_MUX_CFG_ADDR(x),v)
#define HWIO_QUPV3_HW_EVENTS_MUX_CFG_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_QUPV3_HW_EVENTS_MUX_CFG_ADDR(x),m,v,HWIO_QUPV3_HW_EVENTS_MUX_CFG_IN(x))
#define HWIO_QUPV3_HW_EVENTS_MUX_CFG_HW_EVENTS_EN_BMSK                                              0x80000000
#define HWIO_QUPV3_HW_EVENTS_MUX_CFG_HW_EVENTS_EN_SHFT                                                      31
#define HWIO_QUPV3_HW_EVENTS_MUX_CFG_HW_EVENTS_SEL_BMSK                                                 0x3f00
#define HWIO_QUPV3_HW_EVENTS_MUX_CFG_HW_EVENTS_SEL_SHFT                                                      8

#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_NS_ADDR(x)                                                 ((x) + 0x210)
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_NS_OFFS                                                    (0x210)
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_NS_RMSK                                                           0x1
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_NS_IN(x)            \
                in_dword(HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_NS_ADDR(x))
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_NS_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_NS_ADDR(x), m)
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_NS_OUT(x, v)            \
                out_dword(HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_NS_ADDR(x),v)
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_NS_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_NS_ADDR(x),m,v,HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_NS_IN(x))
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_NS_FORCE_TLVOUT_LOOPBACK_NS_BMSK                                  0x1
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_NS_FORCE_TLVOUT_LOOPBACK_NS_SHFT                                    0

#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_MSA_ADDR(x)                                                ((x) + 0x214)
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_MSA_OFFS                                                   (0x214)
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_MSA_RMSK                                                          0x1
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_MSA_IN(x)            \
                in_dword(HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_MSA_ADDR(x))
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_MSA_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_MSA_ADDR(x), m)
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_MSA_OUT(x, v)            \
                out_dword(HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_MSA_ADDR(x),v)
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_MSA_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_MSA_ADDR(x),m,v,HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_MSA_IN(x))
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_MSA_FORCE_TLVOUT_LOOPBACK_MSA_BMSK                                0x1
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_MSA_FORCE_TLVOUT_LOOPBACK_MSA_SHFT                                  0

#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_SP_ADDR(x)                                                 ((x) + 0x218)
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_SP_OFFS                                                    (0x218)
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_SP_RMSK                                                           0x1
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_SP_IN(x)            \
                in_dword(HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_SP_ADDR(x))
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_SP_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_SP_ADDR(x), m)
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_SP_OUT(x, v)            \
                out_dword(HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_SP_ADDR(x),v)
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_SP_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_SP_ADDR(x),m,v,HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_SP_IN(x))
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_SP_FORCE_TLVOUT_LOOPBACK_SP_BMSK                                  0x1
#define HWIO_QUPV3_FORCE_TLVOUT_LOOPBACK_SP_FORCE_TLVOUT_LOOPBACK_SP_SHFT                                    0

#define HWIO_QUPV3_COMMON_CGC_CTRL_ADDR(x)                                                          ((x) + 0x21c)
#define HWIO_QUPV3_COMMON_CGC_CTRL_OFFS                                                             (0x21c)
#define HWIO_QUPV3_COMMON_CGC_CTRL_RMSK                                                                    0x7
#define HWIO_QUPV3_COMMON_CGC_CTRL_IN(x)            \
                in_dword(HWIO_QUPV3_COMMON_CGC_CTRL_ADDR(x))
#define HWIO_QUPV3_COMMON_CGC_CTRL_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_COMMON_CGC_CTRL_ADDR(x), m)
#define HWIO_QUPV3_COMMON_CGC_CTRL_OUT(x, v)            \
                out_dword(HWIO_QUPV3_COMMON_CGC_CTRL_ADDR(x),v)
#define HWIO_QUPV3_COMMON_CGC_CTRL_OUTM(x,m,v) \
                out_dword_masked_ns(HWIO_QUPV3_COMMON_CGC_CTRL_ADDR(x),m,v,HWIO_QUPV3_COMMON_CGC_CTRL_IN(x))
#define HWIO_QUPV3_COMMON_CGC_CTRL_TLV_OUT_CLK_CGC_ON_BMSK                                                 0x4
#define HWIO_QUPV3_COMMON_CGC_CTRL_TLV_OUT_CLK_CGC_ON_SHFT                                                   2
#define HWIO_QUPV3_COMMON_CGC_CTRL_TLV_IN_CLK_CGC_ON_BMSK                                                  0x2
#define HWIO_QUPV3_COMMON_CGC_CTRL_TLV_IN_CLK_CGC_ON_SHFT                                                    1
#define HWIO_QUPV3_COMMON_CGC_CTRL_COMMON_CSR_SLV_CLK_CGC_ON_BMSK                                          0x1
#define HWIO_QUPV3_COMMON_CGC_CTRL_COMMON_CSR_SLV_CLK_CGC_ON_SHFT                                            0

#define HWIO_QUPV3_QTIMER_BIN_ADDR(x)                                                               ((x) + 0x220)
#define HWIO_QUPV3_QTIMER_BIN_OFFS                                                                  (0x220)
#define HWIO_QUPV3_QTIMER_BIN_RMSK                                                                  0xffffffff
#define HWIO_QUPV3_QTIMER_BIN_IN(x)            \
                in_dword(HWIO_QUPV3_QTIMER_BIN_ADDR(x))
#define HWIO_QUPV3_QTIMER_BIN_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_QTIMER_BIN_ADDR(x), m)
#define HWIO_QUPV3_QTIMER_BIN_QTIMER_BIN_BMSK                                                       0xffffffff
#define HWIO_QUPV3_QTIMER_BIN_QTIMER_BIN_SHFT                                                                0

#define HWIO_QUPV3_QTIMER_BIN_MSB_ADDR(x)                                                           ((x) + 0x224)
#define HWIO_QUPV3_QTIMER_BIN_MSB_OFFS                                                              (0x224)
#define HWIO_QUPV3_QTIMER_BIN_MSB_RMSK                                                              0xffffffff
#define HWIO_QUPV3_QTIMER_BIN_MSB_IN(x)            \
                in_dword(HWIO_QUPV3_QTIMER_BIN_MSB_ADDR(x))
#define HWIO_QUPV3_QTIMER_BIN_MSB_INM(x, m)            \
                in_dword_masked(HWIO_QUPV3_QTIMER_BIN_MSB_ADDR(x), m)
#define HWIO_QUPV3_QTIMER_BIN_MSB_QTIMER_BIN_MSB_BMSK                                               0xffffffff
#define HWIO_QUPV3_QTIMER_BIN_MSB_QTIMER_BIN_MSB_SHFT                                                        0

#define HWIO_QUPV3_USER_DATA_TX_SEn_ADDR(base,n)                                                    ((base) + 0X1000 + (0x100*(n)))
#define HWIO_QUPV3_USER_DATA_TX_SEn_OFFS(n)                                                         (0X1000 + (0x100*(n)))
#define HWIO_QUPV3_USER_DATA_TX_SEn_RMSK                                                            0xffffffff
#define HWIO_QUPV3_USER_DATA_TX_SEn_MAXn                                                                     6
#define HWIO_QUPV3_USER_DATA_TX_SEn_INI(base,n)                \
                in_dword_masked(HWIO_QUPV3_USER_DATA_TX_SEn_ADDR(base,n), HWIO_QUPV3_USER_DATA_TX_SEn_RMSK)
#define HWIO_QUPV3_USER_DATA_TX_SEn_INMI(base,n,mask)        \
                in_dword_masked(HWIO_QUPV3_USER_DATA_TX_SEn_ADDR(base,n), mask)
#define HWIO_QUPV3_USER_DATA_TX_SEn_USER_DATA_TX_SE_BMSK                                            0xffffffff
#define HWIO_QUPV3_USER_DATA_TX_SEn_USER_DATA_TX_SE_SHFT                                                     0

#define HWIO_QUPV3_USER_DATA_RX_SEn_ADDR(base,n)                                                    ((base) + 0X1004 + (0x100*(n)))
#define HWIO_QUPV3_USER_DATA_RX_SEn_OFFS(n)                                                         (0X1004 + (0x100*(n)))
#define HWIO_QUPV3_USER_DATA_RX_SEn_RMSK                                                            0xffffffff
#define HWIO_QUPV3_USER_DATA_RX_SEn_MAXn                                                                     6
#define HWIO_QUPV3_USER_DATA_RX_SEn_INI(base,n)                \
                in_dword_masked(HWIO_QUPV3_USER_DATA_RX_SEn_ADDR(base,n), HWIO_QUPV3_USER_DATA_RX_SEn_RMSK)
#define HWIO_QUPV3_USER_DATA_RX_SEn_INMI(base,n,mask)        \
                in_dword_masked(HWIO_QUPV3_USER_DATA_RX_SEn_ADDR(base,n), mask)
#define HWIO_QUPV3_USER_DATA_RX_SEn_USER_DATA_RX_SE_BMSK                                            0xffffffff
#define HWIO_QUPV3_USER_DATA_RX_SEn_USER_DATA_RX_SE_SHFT                                                     0

#define HWIO_QUPV3_USER_DATA_GENI_M_SEn_ADDR(base,n)                                                ((base) + 0X1008 + (0x100*(n)))
#define HWIO_QUPV3_USER_DATA_GENI_M_SEn_OFFS(n)                                                     (0X1008 + (0x100*(n)))
#define HWIO_QUPV3_USER_DATA_GENI_M_SEn_RMSK                                                        0xffffffff
#define HWIO_QUPV3_USER_DATA_GENI_M_SEn_MAXn                                                                 6
#define HWIO_QUPV3_USER_DATA_GENI_M_SEn_INI(base,n)                \
                in_dword_masked(HWIO_QUPV3_USER_DATA_GENI_M_SEn_ADDR(base,n), HWIO_QUPV3_USER_DATA_GENI_M_SEn_RMSK)
#define HWIO_QUPV3_USER_DATA_GENI_M_SEn_INMI(base,n,mask)        \
                in_dword_masked(HWIO_QUPV3_USER_DATA_GENI_M_SEn_ADDR(base,n), mask)
#define HWIO_QUPV3_USER_DATA_GENI_M_SEn_USER_DATA_GENI_M_SE_BMSK                                    0xffffffff
#define HWIO_QUPV3_USER_DATA_GENI_M_SEn_USER_DATA_GENI_M_SE_SHFT                                             0

#define HWIO_QUPV3_USER_DATA_GENI_S_SEn_ADDR(base,n)                                                ((base) + 0X100C + (0x100*(n)))
#define HWIO_QUPV3_USER_DATA_GENI_S_SEn_OFFS(n)                                                     (0X100C + (0x100*(n)))
#define HWIO_QUPV3_USER_DATA_GENI_S_SEn_RMSK                                                        0xffffffff
#define HWIO_QUPV3_USER_DATA_GENI_S_SEn_MAXn                                                                 6
#define HWIO_QUPV3_USER_DATA_GENI_S_SEn_INI(base,n)                \
                in_dword_masked(HWIO_QUPV3_USER_DATA_GENI_S_SEn_ADDR(base,n), HWIO_QUPV3_USER_DATA_GENI_S_SEn_RMSK)
#define HWIO_QUPV3_USER_DATA_GENI_S_SEn_INMI(base,n,mask)        \
                in_dword_masked(HWIO_QUPV3_USER_DATA_GENI_S_SEn_ADDR(base,n), mask)
#define HWIO_QUPV3_USER_DATA_GENI_S_SEn_USER_DATA_GENI_S_SE_BMSK                                    0xffffffff
#define HWIO_QUPV3_USER_DATA_GENI_S_SEn_USER_DATA_GENI_S_SE_SHFT                                             0

#define HWIO_QUPV3_GPII_QADn_ADDR(base,n)                                                           ((base) + 0X1F80 + (0x4*(n)))
#define HWIO_QUPV3_GPII_QADn_OFFS(n)                                                                (0X1F80 + (0x4*(n)))
#define HWIO_QUPV3_GPII_QADn_RMSK                                                                         0x1f
#define HWIO_QUPV3_GPII_QADn_MAXn                                                                           11
#define HWIO_QUPV3_GPII_QADn_INI(base,n)                \
                in_dword_masked(HWIO_QUPV3_GPII_QADn_ADDR(base,n), HWIO_QUPV3_GPII_QADn_RMSK)
#define HWIO_QUPV3_GPII_QADn_INMI(base,n,mask)        \
                in_dword_masked(HWIO_QUPV3_GPII_QADn_ADDR(base,n), mask)
#define HWIO_QUPV3_GPII_QADn_OUTI(base,n,val)        \
                out_dword(HWIO_QUPV3_GPII_QADn_ADDR(base,n),val)
#define HWIO_QUPV3_GPII_QADn_OUTMI(base,n,mask,val) \
                out_dword_masked_ns(HWIO_QUPV3_GPII_QADn_ADDR(base,n),mask,val,HWIO_QUPV3_GPII_QADn_INI(base,n))
#define HWIO_QUPV3_GPII_QADn_GPII_QADID_BMSK                                                              0x1f
#define HWIO_QUPV3_GPII_QADn_GPII_QADID_SHFT                                                                 0


#endif /* HALQUPV3COMMONHWIO_H */
