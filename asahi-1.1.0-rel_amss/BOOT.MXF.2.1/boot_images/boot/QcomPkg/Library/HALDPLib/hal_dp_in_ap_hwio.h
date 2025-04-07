#ifndef __HAL_DP_IN_AP_HWIO_H__
#define __HAL_DP_IN_AP_HWIO_H__
/*
===========================================================================
*/
/**
    @file hal_dp_in_ap_hwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SC8280XP (Makena) [makena_v1.0_p3q2r69_MTO]
 
    This file contains HWIO register definitions for the following modules:
        USB4_HOST_ROUTER_0CFG_REGS
        USB4_HOST_ROUTER_1CFG_REGS
        USB4_HOST_ROUTER_0DP.*
        USB4_HOST_ROUTER_1DP.*


    Generation parameters: 
    { 'filename': 'hal_dp_in_ap_hwio.h',
      'module-filter-exclude': {},
      'module-filter-include': {},
      'modules': [ 'USB4_HOST_ROUTER_0CFG_REGS',
                   'USB4_HOST_ROUTER_1CFG_REGS',
                   'USB4_HOST_ROUTER_0DP.*',
                   'USB4_HOST_ROUTER_1DP.*'],
      'output-fvals': True,
      'output-offsets': True,
      'output-phys': True}
*/
/*
    ===========================================================================

    Copyright (c) 2020 Qualcomm Technologies, Inc.
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

    $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/HALDPLib/hal_dp_in_ap_hwio.h#1 $
    $DateTime: 2024/04/02 23:00:31 $
    $Author: cirrusp4svc $

    ===========================================================================
*/

#define USB4_HOST_ROUTER_WRAPPER_SIZE                                                                  0x00100000
#define USB4_HOST_ROUTER_0USB4_WRAPPER_BASE                                                            (USB4_HOST_ROUTER_BASE               + 0x00000000)
#define USB4_HOST_ROUTER_0USB4_WRAPPER_BASE_PHYS                                                       USB4_HOST_ROUTER_0USB4_WRAPPER_BASE
#define USB4_HOST_ROUTER_1USB4_WRAPPER_BASE                                                            (USB4_HOST_ROUTER_0USB4_WRAPPER_BASE + USB4_HOST_ROUTER_WRAPPER_SIZE)
#define USB4_HOST_ROUTER_1USB4_WRAPPER_BASE_PHYS                                                       USB4_HOST_ROUTER_1USB4_WRAPPER_BASE

/*----------------------------------------------------------------------------
 * MODULE: USB4_HOST_ROUTER_0CFG_REGS
 *--------------------------------------------------------------------------*/

#define USB4_HOST_ROUTER_0CFG_REGS_REG_BASE                                                            (USB4_HOST_ROUTER_0USB4_WRAPPER_BASE            + 0x00080000)
#define USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_SIZE                                                       0x1000
#define USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_USED                                                       0x404
#define USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_PHYS                                                       (USB4_HOST_ROUTER_0USB4_WRAPPER_BASE_PHYS + 0x00080000)
#define USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_OFFS                                                       0x00080000

#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_ADDR                                               (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE            + 0x0)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_PHYS                                               (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_PHYS + 0x0)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_OFFS                                               (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_OFFS + 0x0)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_RMSK                                                  0x3ffff
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_PCIEAP_BMSK                                0x20000
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_PCIEAP_SHFT                                     17
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_DEBUG_BMSK                                 0x10000
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_DEBUG_SHFT                                      16
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_PORT_BMSK                                   0x8000
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_PORT_SHFT                                       15
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_ULL_BMSK                                    0x4000
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_ULL_SHFT                                        14
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_PG_FAST_BMSK                                0x2000
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_PG_FAST_SHFT                                    13
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_PG_BMSK                                     0x1000
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_PG_SHFT                                         12
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_TMU_BMSK                                     0x800
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_TMU_SHFT                                        11
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_MSGBUS_BMSK                                  0x400
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_MSGBUS_SHFT                                     10
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_LPBK_BMSK                                    0x200
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_LPBK_SHFT                                        9
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_RAM_BMSK                                     0x100
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_RAM_SHFT                                         8
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_USBAP_BMSK                                    0x80
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_USBAP_SHFT                                       7
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_DP_BMSK                                       0x40
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_DP_SHFT                                          6
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_HIA_BMSK                                      0x20
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_HIA_SHFT                                         5
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_SB_BMSK                                       0x10
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_SB_SHFT                                          4
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_UC_NON_DIV_BMSK                                0x8
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_UC_NON_DIV_SHFT                                  3
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_UC_GLOBAL_BMSK                                 0x4
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_UC_GLOBAL_SHFT                                   2
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_UC_FREE_BMSK                                   0x2
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_UC_FREE_SHFT                                     1
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_AHB_MNGR_BMSK                                  0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_AHB_MNGR_SHFT                                    0

#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_ADDR                                             (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE            + 0x4)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_PHYS                                             (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_PHYS + 0x4)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_OFFS                                             (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_OFFS + 0x4)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_RMSK                                                   0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_SB_IF_CLK_EN_BMSK                                      0x80
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_SB_IF_CLK_EN_SHFT                                         7
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_TMU_CLK_EN_BMSK                                        0x40
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_TMU_CLK_EN_SHFT                                           6
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_HIA_MSTR_CLK_EN_BMSK                                   0x20
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_HIA_MSTR_CLK_EN_SHFT                                      5
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_DP_PCLK_EN_BMSK                                        0x10
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_DP_PCLK_EN_SHFT                                           4
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_USB_PIPE_CLK_EN_BMSK                                    0x8
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_USB_PIPE_CLK_EN_SHFT                                      3
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_PCIE_PIPE_CLK_EN_BMSK                                   0x4
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_PCIE_PIPE_CLK_EN_SHFT                                     2
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_RX_CLK_1_EN_BMSK                                        0x2
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_RX_CLK_1_EN_SHFT                                          1
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_RX_CLK_0_EN_BMSK                                        0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_OTHER_CLK_CGC_RX_CLK_0_EN_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_ADDR                                                      (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE            + 0x8)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_PHYS                                                      (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_PHYS + 0x8)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_OFFS                                                      (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_OFFS + 0x8)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_RMSK                                                          0x3fff
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_CMB_DATA_TS_BMSK                                     0x2000
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_CMB_DATA_TS_SHFT                                         13
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_CMB_BYTES_BMSK                                       0x1c00
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_CMB_BYTES_SHFT                                           10
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_CMB_SECURE_EN_BMSK                                    0x200
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_CMB_SECURE_EN_SHFT                                        9
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_CMB_ERR_REQ_BMSK                                      0x100
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_CMB_ERR_REQ_SHFT                                          8
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_CMB_I_BMSK                                             0xe0
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_CMB_I_SHFT                                                5
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_GPR_CLK_EN_BMSK                                        0x10
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_GPR_CLK_EN_SHFT                                           4
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_APB_CLK_EN_BMSK                                         0x8
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_APB_CLK_EN_SHFT                                           3
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_ATB_CLK_EN_BMSK                                         0x4
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_ATB_CLK_EN_SHFT                                           2
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_GPR_CLK_OFF_BMSK                                        0x2
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_GPR_CLK_OFF_SHFT                                          1
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_CMB_CLK_OFF_BMSK                                        0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_CFG_TPDM_CMB_CLK_OFF_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_STATUS_ADDR                                               (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE            + 0xc)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_STATUS_PHYS                                               (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_PHYS + 0xc)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_STATUS_OFFS                                               (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_OFFS + 0xc)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_STATUS_RMSK                                                      0x7
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_STATUS_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_STATUS_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_STATUS_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_STATUS_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_STATUS_TPDM_CMB_CLKON_BMSK                                       0x4
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_STATUS_TPDM_CMB_CLKON_SHFT                                         2
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_STATUS_TPDM_CMB_CGC_ACTIVE_BMSK                                  0x2
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_STATUS_TPDM_CMB_CGC_ACTIVE_SHFT                                    1
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_STATUS_TPDM_CMB_ACTIVE_BMSK                                      0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_TPDM_STATUS_TPDM_CMB_ACTIVE_SHFT                                        0

#define HWIO_USB4_HOST_ROUTER_0USB4_RESP_ERR_EN_ADDR                                                   (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE            + 0x10)
#define HWIO_USB4_HOST_ROUTER_0USB4_RESP_ERR_EN_PHYS                                                   (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_PHYS + 0x10)
#define HWIO_USB4_HOST_ROUTER_0USB4_RESP_ERR_EN_OFFS                                                   (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_OFFS + 0x10)
#define HWIO_USB4_HOST_ROUTER_0USB4_RESP_ERR_EN_RMSK                                                          0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_RESP_ERR_EN_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_RESP_ERR_EN_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_RESP_ERR_EN_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_RESP_ERR_EN_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_RESP_ERR_EN_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_RESP_ERR_EN_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_RESP_ERR_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_RESP_ERR_EN_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_RESP_ERR_EN_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_RESP_ERR_EN_RESP_ERR_EN_BMSK                                              0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_RESP_ERR_EN_RESP_ERR_EN_SHFT                                                0

#define HWIO_USB4_HOST_ROUTER_0USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_ADDR                           (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE            + 0x14)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_PHYS                           (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_PHYS + 0x14)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_OFFS                           (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_OFFS + 0x14)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_RMSK                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_DEFAULT_RD_DATA_BMSK           0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_DEFAULT_RD_DATA_SHFT                    0

#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_RESET_ADDR                                             (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE            + 0x18)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_RESET_PHYS                                             (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_PHYS + 0x18)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_RESET_OFFS                                             (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_OFFS + 0x18)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_RESET_RMSK                                                    0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_RESET_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_RESET_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_RESET_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_RESET_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_RESET_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_RESET_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_RESET_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_RESET_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_RESET_SYS_CLK_SYNC_RST_HIA_BMSK                               0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_CFG_SYS_CLK_RESET_SYS_CLK_SYNC_RST_HIA_SHFT                                 0

#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_ADDR_ADDR                                              (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE            + 0x30)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_ADDR_PHYS                                              (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_PHYS + 0x30)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_ADDR_OFFS                                              (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_OFFS + 0x30)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_ADDR_RMSK                                              0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_ADDR_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_ADDR_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_ADDR_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_ADDR_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_ADDR_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_ADDR_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_ADDR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_ADDR_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_ADDR_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_ADDR_RD_PGRX_RAM_ADDR_BMSK                             0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_ADDR_RD_PGRX_RAM_ADDR_SHFT                                      0

#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_EN_ADDR                                                (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE            + 0x34)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_EN_PHYS                                                (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_PHYS + 0x34)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_EN_OFFS                                                (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_OFFS + 0x34)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_EN_RMSK                                                0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_EN_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_EN_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_EN_RD_PGRX_RAM_EN_BMSK                                 0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_RAM_EN_RD_PGRX_RAM_EN_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_DATA_n_ADDR(n)                                             (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE            + 0x38 + (0x4*(n)))
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_DATA_n_PHYS(n)                                             (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_PHYS + 0x38 + (0x4*(n)))
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_DATA_n_OFFS(n)                                             (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_OFFS + 0x38 + (0x4*(n)))
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_DATA_n_RMSK                                                0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_DATA_n_MAXn                                                         3
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_DATA_n_INI(n)                \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_DATA_n_ADDR(n), HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_DATA_n_RMSK)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_DATA_n_INMI(n,mask)        \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_DATA_n_ADDR(n), mask)
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_DATA_n_RD_PGRX_DATA_BMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_RD_PGRX_DATA_n_RD_PGRX_DATA_SHFT                                            0

#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_n_ADDR(n)                                              (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE            + 0x60 + (0x4*(n)))
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_n_PHYS(n)                                              (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_PHYS + 0x60 + (0x4*(n)))
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_n_OFFS(n)                                              (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_OFFS + 0x60 + (0x4*(n)))
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_n_RMSK                                                 0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_n_MAXn                                                          8
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_n_INI(n)                \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_n_ADDR(n), HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_n_RMSK)
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_n_INMI(n,mask)        \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_n_ADDR(n), mask)
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_n_OUTI(n,val)        \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_n_ADDR(n),val)
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_n_OUTMI(n,mask,val) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_n_ADDR(n),mask,val,HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_n_INI(n))
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_n_TESTBUSE_SEL_BMSK                                    0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_n_TESTBUSE_SEL_SHFT                                             0

#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_ADDR                                           (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE            + 0x100)
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_PHYS                                           (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_PHYS + 0x100)
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_OFFS                                           (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_OFFS + 0x100)
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_RMSK                                            0xfffff3f
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_USB4_QSB2AXI_TEST_BUS_SEL_BMSK                  0xff00000
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_USB4_QSB2AXI_TEST_BUS_SEL_SHFT                         20
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_TPDM_CLK_SEL_BMSK                                 0xff000
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_TPDM_CLK_SEL_SHFT                                      12
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_CFG_BITS_BMSK                                       0xc00
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_CFG_BITS_SHFT                                          10
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_AHB_MANAGER_TEST_BUS_BMSK                           0x300
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_AHB_MANAGER_TEST_BUS_SHFT                               8
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_DP_TEST_BUS_BMSK                                     0x3f
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL1_DP_TEST_BUS_SHFT                                        0

#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_ADDR                                           (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE            + 0x104)
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_PHYS                                           (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_PHYS + 0x104)
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_OFFS                                           (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_OFFS + 0x104)
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_RMSK                                              0xfffff
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_USB4_TEST_PORT_SEL_BMSK                           0xf8000
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_USB4_TEST_PORT_SEL_SHFT                                15
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_USB4_UC_TEST_BUS_CLIENT_SEL_BMSK                   0x7000
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_USB4_UC_TEST_BUS_CLIENT_SEL_SHFT                       12
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_USB4_UC_TEST_BUS_SEL_BMSK                           0xe00
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_USB4_UC_TEST_BUS_SEL_SHFT                               9
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_FETCHER_CMDQ_TEST_BUS_SEL_BMSK                      0x180
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_FETCHER_CMDQ_TEST_BUS_SEL_SHFT                          7
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_FETCHER_CMDQ_TEST_BUS_CLIENT_SEL_BMSK                0x60
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_FETCHER_CMDQ_TEST_BUS_CLIENT_SEL_SHFT                   5
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_USB4_QSB2AXI_TEST_BUS_CLIENT_SEL_BMSK                0x1f
#define HWIO_USB4_HOST_ROUTER_0USB4_TESTBUS_SEL_GLOBAL2_USB4_QSB2AXI_TEST_BUS_CLIENT_SEL_SHFT                   0

#define HWIO_USB4_HOST_ROUTER_0USB4_DEBUG_REG_ADDR                                                     (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE            + 0x200)
#define HWIO_USB4_HOST_ROUTER_0USB4_DEBUG_REG_PHYS                                                     (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_PHYS + 0x200)
#define HWIO_USB4_HOST_ROUTER_0USB4_DEBUG_REG_OFFS                                                     (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_OFFS + 0x200)
#define HWIO_USB4_HOST_ROUTER_0USB4_DEBUG_REG_RMSK                                                     0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DEBUG_REG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DEBUG_REG_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DEBUG_REG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DEBUG_REG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DEBUG_REG_DEBUG_REG_BMSK                                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DEBUG_REG_DEBUG_REG_SHFT                                                    0

#define HWIO_USB4_HOST_ROUTER_0USB4_IP_CAT_VERSION_ADDR                                                (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE            + 0x400)
#define HWIO_USB4_HOST_ROUTER_0USB4_IP_CAT_VERSION_PHYS                                                (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_PHYS + 0x400)
#define HWIO_USB4_HOST_ROUTER_0USB4_IP_CAT_VERSION_OFFS                                                (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_OFFS + 0x400)
#define HWIO_USB4_HOST_ROUTER_0USB4_IP_CAT_VERSION_RMSK                                                0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_IP_CAT_VERSION_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_IP_CAT_VERSION_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_IP_CAT_VERSION_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_IP_CAT_VERSION_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_IP_CAT_VERSION_IP_CAT_VERSION_BMSK                                 0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_IP_CAT_VERSION_IP_CAT_VERSION_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_0USB4_HW_VERSION_ADDR                                                    (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE            + 0x404)
#define HWIO_USB4_HOST_ROUTER_0USB4_HW_VERSION_PHYS                                                    (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_PHYS + 0x404)
#define HWIO_USB4_HOST_ROUTER_0USB4_HW_VERSION_OFFS                                                    (USB4_HOST_ROUTER_0CFG_REGS_REG_BASE_OFFS + 0x404)
#define HWIO_USB4_HOST_ROUTER_0USB4_HW_VERSION_RMSK                                                    0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_HW_VERSION_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_HW_VERSION_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_HW_VERSION_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_HW_VERSION_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_HW_VERSION_HW_VERSION_BMSK                                         0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_HW_VERSION_HW_VERSION_SHFT                                                  0

/*----------------------------------------------------------------------------
 * MODULE: USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP
 *--------------------------------------------------------------------------*/

#define USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE                                                 (USB4_HOST_ROUTER_0USB4_WRAPPER_BASE            + 0x00006000)
#define USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_SIZE                                            0x400
#define USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_USED                                            0x44
#define USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS                                            (USB4_HOST_ROUTER_0USB4_WRAPPER_BASE_PHYS + 0x00006000)
#define USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS                                            0x00006000

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_0_STANDARD_ADDR                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x0)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_0_STANDARD_PHYS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x0)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_0_STANDARD_OFFS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x0)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_0_STANDARD_RMSK                                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_0_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_0_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_0_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_0_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_0_STANDARD_VENDOR_DEFINED_RSV_BMSK                        0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_0_STANDARD_VENDOR_DEFINED_RSV_SHFT                                 0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_1_STANDARD_ADDR                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x4)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_1_STANDARD_PHYS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x4)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_1_STANDARD_OFFS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x4)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_1_STANDARD_RMSK                                              0xfffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_1_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_1_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_1_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_1_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_1_STANDARD_CCS_FLAG_BMSK                                     0x80000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_1_STANDARD_CCS_FLAG_SHFT                                          19
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_1_STANDARD_MAX_COUNTER_SETS_BMSK                             0x7ff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_1_STANDARD_MAX_COUNTER_SETS_SHFT                                   8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_1_STANDARD_NEXT_CAPABILITY_POINTER_BMSK                         0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_1_STANDARD_NEXT_CAPABILITY_POINTER_SHFT                            0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_2_STANDARD_ADDR                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x8)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_2_STANDARD_PHYS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x8)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_2_STANDARD_OFFS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x8)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_2_STANDARD_RMSK                                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_2_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_2_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_2_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_2_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_2_STANDARD_RSVD_BMSK                                      0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_2_STANDARD_RSVD_SHFT                                              24
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_2_STANDARD_ADAPTER_TYPE_PROTOCOL_BMSK                       0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_2_STANDARD_ADAPTER_TYPE_PROTOCOL_SHFT                             16
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_2_STANDARD_ADAPTER_TYPE_VERSION_BMSK                          0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_2_STANDARD_ADAPTER_TYPE_VERSION_SHFT                               8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_2_STANDARD_ADAPTER_TYPE_SUB_TYPE_BMSK                           0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_2_STANDARD_ADAPTER_TYPE_SUB_TYPE_SHFT                              0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_3_STANDARD_ADDR                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0xc)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_3_STANDARD_PHYS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0xc)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_3_STANDARD_OFFS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0xc)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_3_STANDARD_RMSK                                           0xe3f00000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_3_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_3_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_3_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_3_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_3_STANDARD_SBC_BMSK                                       0x80000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_3_STANDARD_SBC_SHFT                                               31
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_3_STANDARD_FCE_BMSK                                       0x40000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_3_STANDARD_FCE_SHFT                                               30
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_3_STANDARD_HE_BMSK                                        0x20000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_3_STANDARD_HE_SHFT                                                29
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_3_STANDARD_ADAPTER_NUMBER_BMSK                             0x3f00000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_3_STANDARD_ADAPTER_NUMBER_SHFT                                    20

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_ADDR                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x10)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_PHYS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x10)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_OFFS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x10)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_RMSK                                           0xfff003ff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_LCK_BMSK                                       0x80000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_LCK_SHFT                                               31
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_PLUGGED_BMSK                                   0x40000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_PLUGGED_SHFT                                           30
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_TOTAL_BUFFERS_BMSK                             0x3ff00000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_TOTAL_BUFFERS_SHFT                                     20
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_NON_FLOW_CONTROLLED_BUFFERS_BMSK                    0x3ff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_4_STANDARD_NON_FLOW_CONTROLLED_BUFFERS_SHFT                        0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_ADDR                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x14)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_PHYS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x14)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_OFFS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x14)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_RMSK                                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_DHP_BMSK                                       0x80000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_DHP_SHFT                                               31
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_FCEE_BMSK                                      0x40000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_FCEE_SHFT                                              30
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_HEE_BMSK                                       0x20000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_HEE_SHFT                                               29
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_LINK_CREDITS_ALLOCATED_BMSK                    0x1fc00000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_LINK_CREDITS_ALLOCATED_SHFT                            22
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_MAX_OUTPUT_HOPID_BMSK                            0x3ff800
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_MAX_OUTPUT_HOPID_SHFT                                  11
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_MAX_INPUT_HOPID_BMSK                                0x7ff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_5_STANDARD_MAX_INPUT_HOPID_SHFT                                    0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_6_STANDARD_ADDR                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x18)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_6_STANDARD_PHYS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x18)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_6_STANDARD_OFFS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x18)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_6_STANDARD_RMSK                                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_6_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_6_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_6_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_6_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_6_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_6_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_6_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_6_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_6_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_6_STANDARD_HEC_ERRORS_BMSK                                0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_6_STANDARD_HEC_ERRORS_SHFT                                         0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_7_STANDARD_ADDR                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x1c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_7_STANDARD_PHYS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x1c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_7_STANDARD_OFFS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x1c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_7_STANDARD_RMSK                                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_7_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_7_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_7_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_7_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_7_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_7_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_7_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_7_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_7_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_7_STANDARD_INVALID_HOPID_ERRORS_BMSK                      0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_7_STANDARD_INVALID_HOPID_ERRORS_SHFT                               0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_8_STANDARD_ADDR                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x20)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_8_STANDARD_PHYS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x20)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_8_STANDARD_OFFS                                           (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x20)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_8_STANDARD_RMSK                                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_8_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_8_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_8_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_8_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_8_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_8_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_8_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_8_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_8_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_8_STANDARD_ECC_ERRORS_BMSK                                0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_CS_8_STANDARD_ECC_ERRORS_SHFT                                         0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_ADDR                                        (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x28)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_PHYS                                        (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x28)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_OFFS                                        (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x28)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_RMSK                                        0xc7ffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_VE_BMSK                                     0x80000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_VE_SHFT                                             31
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_AE_BMSK                                     0x40000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_AE_SHFT                                             30
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_VIDEO_HOPID_BMSK                             0x7ff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_VIDEO_HOPID_SHFT                                    16
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_CAPABILITY_ID_BMSK                              0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_CAPABILITY_ID_SHFT                                   8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_NEXT_CAPABILITY_POINTER_BMSK                      0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_0_STANDARD_NEXT_CAPABILITY_POINTER_SHFT                         0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_1_STANDARD_ADDR                                        (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x2c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_1_STANDARD_PHYS                                        (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x2c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_1_STANDARD_OFFS                                        (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x2c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_1_STANDARD_RMSK                                          0x3fffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_1_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_1_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_1_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_1_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_1_STANDARD_AUX_RX_HOPID_BMSK                             0x3ff800
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_1_STANDARD_AUX_RX_HOPID_SHFT                                   11
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_1_STANDARD_AUX_TX_HOPID_BMSK                                0x7ff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_1_STANDARD_AUX_TX_HOPID_SHFT                                    0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_2_STANDARD_ADDR                                        (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x30)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_2_STANDARD_PHYS                                        (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x30)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_2_STANDARD_OFFS                                        (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x30)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_2_STANDARD_RMSK                                              0x48
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_2_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_2_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_2_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_2_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_2_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_2_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_2_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_2_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_2_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_2_STANDARD_HPD_STATUS_BMSK                                   0x40
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_2_STANDARD_HPD_STATUS_SHFT                                      6
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_2_STANDARD_SWLI_BMSK                                          0x8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_2_STANDARD_SWLI_SHFT                                            3

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_3_STANDARD_ADDR                                        (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x34)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_3_STANDARD_PHYS                                        (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x34)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_3_STANDARD_OFFS                                        (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x34)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_3_STANDARD_RMSK                                             0x600
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_3_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_3_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_3_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_3_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_3_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_3_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_3_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_3_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_3_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_3_STANDARD_HPDS_BMSK                                        0x400
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_3_STANDARD_HPDS_SHFT                                           10
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_3_STANDARD_HPDC_BMSK                                        0x200
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ADP_DP_CS_3_STANDARD_HPDC_SHFT                                            9

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_ADDR                                       (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x38)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_PHYS                                       (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x38)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_OFFS                                       (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x38)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_RMSK                                       0x2fc0ffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_DSC_NOT_SUPPORTED_BMSK                     0x20000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_DSC_NOT_SUPPORTED_SHFT                             29
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_LTTPR_NOT_SUPPORTED_BMSK                    0x8000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_LTTPR_NOT_SUPPORTED_SHFT                           27
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_SECONDARY_SPLIT_CAPABILITY_BMSK             0x4000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_SECONDARY_SPLIT_CAPABILITY_SHFT                    26
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_FEC_NOT_SUPPORTED_BMSK                      0x2000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_FEC_NOT_SUPPORTED_SHFT                             25
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_TPS4_CAPABILITY_BMSK                        0x1000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_TPS4_CAPABILITY_SHFT                               24
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_RSVD_1_BMSK                                  0x800000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_RSVD_1_SHFT                                        23
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_TPS3_CAPABILITY_BMSK                         0x400000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_TPS3_CAPABILITY_SHFT                               22
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_MST_CAPABILITY_BMSK                            0x8000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_MST_CAPABILITY_SHFT                                15
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_MAXIMAL_LANE_COUNT_BMSK                        0x7000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_MAXIMAL_LANE_COUNT_SHFT                            12
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_MAXIMAL_LINK_RATE_BMSK                          0xf00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_MAXIMAL_LINK_RATE_SHFT                              8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_MAXIMAL_DPCD_REV_BMSK                            0xf0
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_MAXIMAL_DPCD_REV_SHFT                               4
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_PROTOCOL_ADAPTER_REVISION_BMSK                    0xf
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_LOCAL_CAP_STANDARD_PROTOCOL_ADAPTER_REVISION_SHFT                      0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_ADDR                                      (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x3c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_PHYS                                      (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x3c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_OFFS                                      (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x3c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_RMSK                                      0x2f40ffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_DSC_NOT_SUPPORTED_BMSK                    0x20000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_DSC_NOT_SUPPORTED_SHFT                            29
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_LTTPR_NOT_SUPPORTED_BMSK                   0x8000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_LTTPR_NOT_SUPPORTED_SHFT                          27
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_SECONDARY_SPLIT_CAPABILITY_BMSK            0x4000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_SECONDARY_SPLIT_CAPABILITY_SHFT                   26
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_FEC_NOT_SUPPORTED_BMSK                     0x2000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_FEC_NOT_SUPPORTED_SHFT                            25
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_TPS4_CAPABILITY_BMSK                       0x1000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_TPS4_CAPABILITY_SHFT                              24
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_TPS3_CAPABILITY_BMSK                        0x400000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_TPS3_CAPABILITY_SHFT                              22
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_MST_CAPABILITY_BMSK                           0x8000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_MST_CAPABILITY_SHFT                               15
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_MAXIMAL_LANE_COUNT_BMSK                       0x7000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_MAXIMAL_LANE_COUNT_SHFT                           12
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_MAXIMAL_LINK_RATE_BMSK                         0xf00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_MAXIMAL_LINK_RATE_SHFT                             8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_MAXIMAL_DPCD_REV_BMSK                           0xf0
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_MAXIMAL_DPCD_REV_SHFT                              4
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_PROTOCOL_ADAPTER_REVISION_BMSK                   0xf
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_REMOTE_CAP_STANDARD_PROTOCOL_ADAPTER_REVISION_SHFT                     0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_STATUS_STANDARD_ADDR                                          (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x40)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_STATUS_STANDARD_PHYS                                          (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x40)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_STATUS_STANDARD_OFFS                                          (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x40)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_STATUS_STANDARD_RMSK                                               0xf07
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_STATUS_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_STATUS_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_STATUS_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_STATUS_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_STATUS_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_STATUS_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_STATUS_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_STATUS_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_STATUS_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_STATUS_STANDARD_LINK_RATE_BMSK                                     0xf00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_STATUS_STANDARD_LINK_RATE_SHFT                                         8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_STATUS_STANDARD_LANE_COUNT_BMSK                                      0x7
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_STATUS_STANDARD_LANE_COUNT_SHFT                                        0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_ADDR                                      (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x44)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_PHYS                                      (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x44)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_OFFS                                      (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x44)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_RMSK                                      0xaf40ffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_DPRX_CAPABILITIES_READ_DONE_BMSK          0x80000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_DPRX_CAPABILITIES_READ_DONE_SHFT                  31
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_DSC_NOT_SUPPORTED_BMSK                    0x20000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_DSC_NOT_SUPPORTED_SHFT                            29
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_LTTPR_NOT_SUPPORTED_BMSK                   0x8000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_LTTPR_NOT_SUPPORTED_SHFT                          27
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_SECONDARY_SPLIT_CAPABILITY_BMSK            0x4000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_SECONDARY_SPLIT_CAPABILITY_SHFT                   26
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_FEC_NOT_SUPPORTED_BMSK                     0x2000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_FEC_NOT_SUPPORTED_SHFT                            25
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_TPS4_CAPABILITY_BMSK                       0x1000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_TPS4_CAPABILITY_SHFT                              24
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_TPS3_CAPABILITY_BMSK                        0x400000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_TPS3_CAPABILITY_SHFT                              22
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_MST_CAPABILITY_BMSK                           0x8000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_MST_CAPABILITY_SHFT                               15
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_MAXIMAL_LANE_COUNT_BMSK                       0x7000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_MAXIMAL_LANE_COUNT_SHFT                           12
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_MAXIMAL_LINK_RATE_BMSK                         0xf00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_MAXIMAL_LINK_RATE_SHFT                             8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_MAXIMAL_DPCD_REV_BMSK                           0xf0
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_MAXIMAL_DPCD_REV_SHFT                              4
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_PROTOCOL_ADAPTER_REVISION_BMSK                   0xf
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_DP_COMMON_CAP_STANDARD_PROTOCOL_ADAPTER_REVISION_SHFT                     0

/*----------------------------------------------------------------------------
 * MODULE: USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT
 *--------------------------------------------------------------------------*/

#define USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE                                                 (USB4_HOST_ROUTER_0USB4_WRAPPER_BASE            + 0x00006400)
#define USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_SIZE                                            0xc00
#define USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_USED                                            0x414
#define USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS                                            (USB4_HOST_ROUTER_0USB4_WRAPPER_BASE_PHYS + 0x00006400)
#define USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS                                            0x00006400

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_ADDR                                  (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x40)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_PHYS                                  (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x40)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_OFFS                                  (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x40)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_RMSK                                  0x80ffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_V_BMSK                                0x80000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_V_SHFT                                        31
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_PATH_CREDITS_ALLOCATED_BMSK             0xfe0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_PATH_CREDITS_ALLOCATED_SHFT                   17
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_OUTPUT_PORT_BMSK                         0x1f800
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_OUTPUT_PORT_SHFT                              11
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_OUTPUT_HOPID_BMSK                          0x7ff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_AUX_STANDARD_OUTPUT_HOPID_SHFT                              0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ADDR                                  (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x44)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_PHYS                                  (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x44)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_OFFS                                  (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x44)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_RMSK                                  0x1ffff7ff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_PP_BMSK                               0x10000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_PP_SHFT                                       28
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ESE_BMSK                               0x8000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ESE_SHFT                                      27
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ISE_BMSK                               0x4000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ISE_SHFT                                      26
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_EFC_BMSK                               0x2000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_EFC_SHFT                                      25
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_IFC_BMSK                               0x1000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_IFC_SHFT                                      24
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_CE_BMSK                                 0x800000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_CE_SHFT                                       23
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_COUNTER_ID_BMSK                         0x7ff000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_COUNTER_ID_SHFT                               12
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_PRIORITY_BMSK                              0x700
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_PRIORITY_SHFT                                  8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_WEIGHT_BMSK                                 0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_AUX_STANDARD_WEIGHT_SHFT                                    0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_ADDR                                 (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x48)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_PHYS                                 (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x48)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_OFFS                                 (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x48)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_RMSK                                 0x80ffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_V_BMSK                               0x80000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_V_SHFT                                       31
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_PATH_CREDITS_ALLOCATED_BMSK            0xfe0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_PATH_CREDITS_ALLOCATED_SHFT                  17
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_OUTPUT_PORT_BMSK                        0x1f800
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_OUTPUT_PORT_SHFT                             11
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_OUTPUT_HOPID_BMSK                         0x7ff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_OUTPUT_HOPID_SHFT                             0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ADDR                                 (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x4c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_PHYS                                 (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x4c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_OFFS                                 (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x4c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_RMSK                                 0x1ffff7ff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_PP_BMSK                              0x10000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_PP_SHFT                                      28
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ESE_BMSK                              0x8000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ESE_SHFT                                     27
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ISE_BMSK                              0x4000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ISE_SHFT                                     26
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_EFC_BMSK                              0x2000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_EFC_SHFT                                     25
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_IFC_BMSK                              0x1000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_IFC_SHFT                                     24
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_CE_BMSK                                0x800000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_CE_SHFT                                      23
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_COUNTER_ID_BMSK                        0x7ff000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_COUNTER_ID_SHFT                              12
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_PRIORITY_BMSK                             0x700
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_PRIORITY_SHFT                                 8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_WEIGHT_BMSK                                0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_WEIGHT_SHFT                                   0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_AUX_STANDARD_ADDR                                   (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x400)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_AUX_STANDARD_PHYS                                   (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x400)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_AUX_STANDARD_OFFS                                   (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x400)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_AUX_STANDARD_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_AUX_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_AUX_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_AUX_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_AUX_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_AUX_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_AUX_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_AUX_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_AUX_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_AUX_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_AUX_STANDARD_RECEIVED_PACKETS_LOW_BMSK              0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_AUX_STANDARD_RECEIVED_PACKETS_LOW_SHFT                       0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_AUX_STANDARD_ADDR                                   (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x404)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_AUX_STANDARD_PHYS                                   (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x404)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_AUX_STANDARD_OFFS                                   (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x404)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_AUX_STANDARD_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_AUX_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_AUX_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_AUX_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_AUX_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_AUX_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_AUX_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_AUX_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_AUX_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_AUX_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_AUX_STANDARD_RECEIVED_PACKETS_HIGH_BMSK             0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_AUX_STANDARD_RECEIVED_PACKETS_HIGH_SHFT                      0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_AUX_STANDARD_ADDR                                   (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x408)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_AUX_STANDARD_PHYS                                   (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x408)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_AUX_STANDARD_OFFS                                   (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x408)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_AUX_STANDARD_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_AUX_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_AUX_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_AUX_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_AUX_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_AUX_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_AUX_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_AUX_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_AUX_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_AUX_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_AUX_STANDARD_DROPPED_PACKETS_BMSK                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_AUX_STANDARD_DROPPED_PACKETS_SHFT                            0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_1_STANDARD_ADDR                                     (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x40c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_1_STANDARD_PHYS                                     (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x40c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_1_STANDARD_OFFS                                     (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x40c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_1_STANDARD_RMSK                                     0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_1_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_1_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_1_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_1_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_1_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_1_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_1_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_1_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_1_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_1_STANDARD_RECEIVED_PACKETS_LOW_BMSK                0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_0_1_STANDARD_RECEIVED_PACKETS_LOW_SHFT                         0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_1_STANDARD_ADDR                                     (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x410)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_1_STANDARD_PHYS                                     (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x410)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_1_STANDARD_OFFS                                     (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x410)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_1_STANDARD_RMSK                                     0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_1_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_1_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_1_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_1_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_1_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_1_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_1_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_1_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_1_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_1_STANDARD_RECEIVED_PACKETS_HIGH_BMSK               0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_1_1_STANDARD_RECEIVED_PACKETS_HIGH_SHFT                        0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_1_STANDARD_ADDR                                     (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x414)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_1_STANDARD_PHYS                                     (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x414)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_1_STANDARD_OFFS                                     (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x414)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_1_STANDARD_RMSK                                     0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_1_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_1_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_1_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_1_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_1_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_1_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_1_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_1_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_1_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_1_STANDARD_DROPPED_PACKETS_BMSK                     0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CNT_CS_2_1_STANDARD_DROPPED_PACKETS_SHFT                              0

/*----------------------------------------------------------------------------
 * MODULE: USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP
 *--------------------------------------------------------------------------*/

#define USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE                                           (USB4_HOST_ROUTER_0USB4_WRAPPER_BASE            + 0x0000f000)
#define USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_SIZE                                      0x1000
#define USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_USED                                      0x228
#define USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS                                      (USB4_HOST_ROUTER_0USB4_WRAPPER_BASE_PHYS + 0x0000f000)
#define USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS                                      0x0000f000

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_ADDR                                         (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x0)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_PHYS                                         (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x0)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_OFFS                                         (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x0)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_RMSK                                         0xffffff01
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_PDF_BMSK                                     0xf0000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_PDF_SHFT                                             28
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_SUPPID_BMSK                                   0x8000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_SUPPID_SHFT                                          27
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_HOPID_BMSK                                    0x7ff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_HOPID_SHFT                                           16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_LENGTH_BMSK                                      0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_LENGTH_SHFT                                           8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_TRIGGER_BMSK                                        0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_HDR_TRIGGER_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_ADDR                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x4)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_PHYS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x4)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_OFFS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x4)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_BYTE3_BMSK                             0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_BYTE3_SHFT                                     24
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_BYTE2_BMSK                               0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_BYTE2_SHFT                                     16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_BYTE1_BMSK                                 0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_BYTE1_SHFT                                      8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_BYTE0_BMSK                                   0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_0_BYTE0_SHFT                                      0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_ADDR                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x8)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_PHYS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x8)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_OFFS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x8)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_BYTE7_BMSK                             0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_BYTE7_SHFT                                     24
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_BYTE6_BMSK                               0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_BYTE6_SHFT                                     16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_BYTE5_BMSK                                 0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_BYTE5_SHFT                                      8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_BYTE4_BMSK                                   0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_1_BYTE4_SHFT                                      0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_ADDR                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0xc)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_PHYS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0xc)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_OFFS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0xc)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_BYTE11_BMSK                            0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_BYTE11_SHFT                                    24
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_BYTE10_BMSK                              0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_BYTE10_SHFT                                    16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_BYTE9_BMSK                                 0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_BYTE9_SHFT                                      8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_BYTE8_BMSK                                   0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_2_BYTE8_SHFT                                      0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_ADDR                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x10)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_PHYS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x10)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_OFFS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x10)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_BYTE15_BMSK                            0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_BYTE15_SHFT                                    24
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_BYTE14_BMSK                              0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_BYTE14_SHFT                                    16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_BYTE13_BMSK                                0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_BYTE13_SHFT                                     8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_BYTE12_BMSK                                  0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_3_BYTE12_SHFT                                     0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_ADDR                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x14)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_PHYS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x14)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_OFFS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x14)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_BYTE19_BMSK                            0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_BYTE19_SHFT                                    24
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_BYTE18_BMSK                              0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_BYTE18_SHFT                                    16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_BYTE17_BMSK                                0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_BYTE17_SHFT                                     8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_BYTE16_BMSK                                  0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TX_PAYLOAD_4_BYTE16_SHFT                                     0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_ADDR                                         (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x20)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_PHYS                                         (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x20)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_OFFS                                         (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x20)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_RMSK                                         0xffffff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_PDF_BMSK                                     0xf0000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_PDF_SHFT                                             28
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_SUPPID_BMSK                                   0x8000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_SUPPID_SHFT                                          27
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_HOPID_BMSK                                    0x7ff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_HOPID_SHFT                                           16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_LENGTH_BMSK                                      0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_HDR_LENGTH_SHFT                                           8

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_ADDR                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x24)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_PHYS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x24)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_OFFS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x24)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_BYTE3_BMSK                             0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_BYTE3_SHFT                                     24
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_BYTE2_BMSK                               0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_BYTE2_SHFT                                     16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_BYTE1_BMSK                                 0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_BYTE1_SHFT                                      8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_BYTE0_BMSK                                   0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_0_BYTE0_SHFT                                      0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_ADDR                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x28)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_PHYS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x28)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_OFFS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x28)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_BYTE7_BMSK                             0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_BYTE7_SHFT                                     24
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_BYTE6_BMSK                               0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_BYTE6_SHFT                                     16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_BYTE5_BMSK                                 0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_BYTE5_SHFT                                      8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_BYTE4_BMSK                                   0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_1_BYTE4_SHFT                                      0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_ADDR                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x2c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_PHYS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x2c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_OFFS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x2c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_BYTE11_BMSK                            0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_BYTE11_SHFT                                    24
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_BYTE10_BMSK                              0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_BYTE10_SHFT                                    16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_BYTE9_BMSK                                 0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_BYTE9_SHFT                                      8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_BYTE8_BMSK                                   0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_2_BYTE8_SHFT                                      0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_ADDR                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x30)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_PHYS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x30)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_OFFS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x30)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_BYTE15_BMSK                            0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_BYTE15_SHFT                                    24
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_BYTE14_BMSK                              0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_BYTE14_SHFT                                    16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_BYTE13_BMSK                                0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_BYTE13_SHFT                                     8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_BYTE12_BMSK                                  0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_3_BYTE12_SHFT                                     0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_ADDR                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x34)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_PHYS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x34)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_OFFS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x34)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_BYTE19_BMSK                            0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_BYTE19_SHFT                                    24
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_BYTE18_BMSK                              0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_BYTE18_SHFT                                    16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_BYTE17_BMSK                                0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_BYTE17_SHFT                                     8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_BYTE16_BMSK                                  0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_PAYLOAD_4_BYTE16_SHFT                                     0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_ADDR                                         (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x38)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_PHYS                                         (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x38)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_OFFS                                         (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x38)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_RMSK                                         0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_CRC_TOKEN_BMSK                               0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_CRC_TOKEN_SHFT                                        0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUFFER_CLR_ADDR                                  (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x3c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUFFER_CLR_PHYS                                  (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x3c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUFFER_CLR_OFFS                                  (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x3c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUFFER_CLR_RMSK                                         0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUFFER_CLR_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUFFER_CLR_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUFFER_CLR_BUFFER_CLR_BMSK                              0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUFFER_CLR_BUFFER_CLR_SHFT                                0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_ADDR                                      (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x40)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_PHYS                                      (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x40)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_OFFS                                      (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x40)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_RMSK                                         0x700ff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_IGNORE_ACK_ECC_ERR_BMSK                      0x40000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_IGNORE_ACK_ECC_ERR_SHFT                           18
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_GRAN_SEL_BMSK                                0x30000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_GRAN_SEL_SHFT                                     16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_ACK_TIMEOUT_BMSK                                0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_TIMER_CFG_ACK_TIMEOUT_SHFT                                   0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_ADDR                                         (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x44)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_PHYS                                         (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x44)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_OFFS                                         (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x44)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_RMSK                                         0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_DP_AUX_SW_IRQ_BMSK                           0x80000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_DP_AUX_SW_IRQ_SHFT                                   31
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_DP_AUX_UC_IRQ_BMSK                           0x40000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_DP_AUX_UC_IRQ_SHFT                                   30
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_RX_BUF_CNT_BMSK                              0x3c000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_RX_BUF_CNT_SHFT                                      26
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_AUTO_ACK_DISABLE_BMSK                         0x2000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_AUTO_ACK_DISABLE_SHFT                                25
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UC_MODE_RX_DROP_PKT_BMSK                      0x1000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UC_MODE_RX_DROP_PKT_SHFT                             24
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UC_MODE_TX_DROP_PKT_BMSK                       0x800000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UC_MODE_TX_DROP_PKT_SHFT                             23
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UC_MODE_RX_ACK_BMSK                            0x400000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UC_MODE_RX_ACK_SHFT                                  22
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UC_MODE_TX_ACK_BMSK                            0x200000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UC_MODE_TX_ACK_SHFT                                  21
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UC_MODE_RX_ACTIVE_BMSK                         0x100000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UC_MODE_RX_ACTIVE_SHFT                               20
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UC_MODE_TX_ACTIVE_BMSK                          0x80000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UC_MODE_TX_ACTIVE_SHFT                               19
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UC_MODE_RX_ENABLE_BMSK                          0x40000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UC_MODE_RX_ENABLE_SHFT                               18
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UC_MODE_TX_ENABLE_BMSK                          0x20000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UC_MODE_TX_ENABLE_SHFT                               17
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_TX_TIMER_ACTIVE_BMSK                            0x10000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_TX_TIMER_ACTIVE_SHFT                                 16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UNCORRECT_ERROR_BMSK                             0x8000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_UNCORRECT_ERROR_SHFT                                 15
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_RX_HPD_CLR_PEND_BMSK                             0x4000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_RX_HPD_CLR_PEND_SHFT                                 14
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_RX_HPD_SET_PEND_BMSK                             0x2000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_RX_HPD_SET_PEND_SHFT                                 13
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_RX_START_PG_RX_BMSK                              0x1000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_RX_START_PG_RX_SHFT                                  12
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_TX_GEN_ACK_PEND_BMSK                              0x800
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_TX_GEN_ACK_PEND_SHFT                                 11
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_TX_START_BMSK                                     0x400
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_TX_START_SHFT                                        10
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_RX_BUFFER_FULL_BMSK                               0x200
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_RX_BUFFER_FULL_SHFT                                   9
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_RX_ENABLE_BMSK                                    0x100
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_RX_ENABLE_SHFT                                        8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_RX_FSM_STATE_BMSK                                  0xf0
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_RX_FSM_STATE_SHFT                                     4
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_TX_ENABLE_BMSK                                      0x8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_TX_ENABLE_SHFT                                        3
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_TX_FSM_STATE_BMSK                                   0x7
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_STATUS_TX_FSM_STATE_SHFT                                     0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_HPD_STATUS_ADDR                                     (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x48)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_HPD_STATUS_PHYS                                     (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x48)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_HPD_STATUS_OFFS                                     (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x48)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_HPD_STATUS_RMSK                                            0x3
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_HPD_STATUS_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_HPD_STATUS_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_HPD_STATUS_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_HPD_STATUS_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_HPD_STATUS_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_HPD_STATUS_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_HPD_STATUS_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_HPD_STATUS_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_HPD_STATUS_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_HPD_STATUS_HPD_STATUS_HW_EN_BMSK                           0x2
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_HPD_STATUS_HPD_STATUS_HW_EN_SHFT                             1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_HPD_STATUS_HPD_STATUS_BMSK                                 0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_HPD_STATUS_HPD_STATUS_SHFT                                   0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_HDR_ADDR                                     (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x50)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_HDR_PHYS                                     (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x50)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_HDR_OFFS                                     (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x50)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_HDR_RMSK                                     0xffffff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_HDR_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_HDR_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_HDR_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_HDR_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_HDR_PDF_BMSK                                 0xf0000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_HDR_PDF_SHFT                                         28
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_HDR_SUPPID_BMSK                               0x8000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_HDR_SUPPID_SHFT                                      27
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_HDR_HOPID_BMSK                                0x7ff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_HDR_HOPID_SHFT                                       16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_HDR_LENGTH_BMSK                                  0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_HDR_LENGTH_SHFT                                       8

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_0_ADDR                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x54)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_0_PHYS                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x54)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_0_OFFS                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x54)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_0_RMSK                               0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_0_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_0_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_0_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_0_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_0_BYTE3_BMSK                         0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_0_BYTE3_SHFT                                 24
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_0_BYTE2_BMSK                           0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_0_BYTE2_SHFT                                 16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_0_BYTE1_BMSK                             0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_0_BYTE1_SHFT                                  8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_0_BYTE0_BMSK                               0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_0_BYTE0_SHFT                                  0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_1_ADDR                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x58)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_1_PHYS                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x58)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_1_OFFS                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x58)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_1_RMSK                               0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_1_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_1_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_1_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_1_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_1_BYTE7_BMSK                         0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_1_BYTE7_SHFT                                 24
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_1_BYTE6_BMSK                           0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_1_BYTE6_SHFT                                 16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_1_BYTE5_BMSK                             0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_1_BYTE5_SHFT                                  8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_1_BYTE4_BMSK                               0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_1_BYTE4_SHFT                                  0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_2_ADDR                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x5c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_2_PHYS                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x5c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_2_OFFS                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x5c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_2_RMSK                               0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_2_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_2_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_2_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_2_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_2_BYTE11_BMSK                        0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_2_BYTE11_SHFT                                24
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_2_BYTE10_BMSK                          0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_2_BYTE10_SHFT                                16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_2_BYTE9_BMSK                             0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_2_BYTE9_SHFT                                  8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_2_BYTE8_BMSK                               0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_2_BYTE8_SHFT                                  0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_3_ADDR                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x60)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_3_PHYS                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x60)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_3_OFFS                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x60)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_3_RMSK                               0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_3_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_3_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_3_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_3_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_3_BYTE15_BMSK                        0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_3_BYTE15_SHFT                                24
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_3_BYTE14_BMSK                          0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_3_BYTE14_SHFT                                16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_3_BYTE13_BMSK                            0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_3_BYTE13_SHFT                                 8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_3_BYTE12_BMSK                              0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_3_BYTE12_SHFT                                 0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_4_ADDR                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x64)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_4_PHYS                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x64)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_4_OFFS                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x64)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_4_RMSK                               0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_4_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_4_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_4_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_4_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_4_BYTE19_BMSK                        0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_4_BYTE19_SHFT                                24
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_4_BYTE18_BMSK                          0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_4_BYTE18_SHFT                                16
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_4_BYTE17_BMSK                            0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_4_BYTE17_SHFT                                 8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_4_BYTE16_BMSK                              0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_BUF_PAYLOAD_4_BYTE16_SHFT                                 0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_ADDR                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x68)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_PHYS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x68)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_OFFS                                   (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x68)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_NUM_BMSK                               0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_NUM_SHFT                                        0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_CTL_ADDR                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x6c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_CTL_PHYS                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x6c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_CTL_OFFS                               (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x6c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_CTL_RMSK                                      0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_CTL_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_CTL_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_CTL_CLR_BMSK                                  0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_DROPPED_PKTS_CTL_CLR_SHFT                                    0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_ADDR                                      (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x150)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_PHYS                                      (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x150)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_OFFS                                      (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x150)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_RMSK                                           0x7ff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_IRQ_RECEIVED_EN_BMSK                           0x400
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_IRQ_RECEIVED_EN_SHFT                              10
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_HPD_PLUG_RECEIVED_EN_BMSK                      0x200
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_HPD_PLUG_RECEIVED_EN_SHFT                          9
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_HPD_UNPLUG_RECEIVED_EN_BMSK                    0x100
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_HPD_UNPLUG_RECEIVED_EN_SHFT                        8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_ACK_RECEIVED_EN_BMSK                            0x80
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_ACK_RECEIVED_EN_SHFT                               7
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_PATH_TEARDOWN_EN_BMSK                           0x40
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_PATH_TEARDOWN_EN_SHFT                              6
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_BLOCK_TX_ACK_EN_BMSK                            0x20
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_BLOCK_TX_ACK_EN_SHFT                               5
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_RST_ACK_EN_BMSK                                 0x10
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_RST_ACK_EN_SHFT                                    4
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_CLK_SYNC_N_PKTS_EN_BMSK                          0x8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_CLK_SYNC_N_PKTS_EN_SHFT                            3
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_ACK_TIMEOUT_EN_BMSK                              0x4
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_ACK_TIMEOUT_EN_SHFT                                2
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_RX_PKT_RECEIVED_EN_BMSK                          0x2
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_RX_PKT_RECEIVED_EN_SHFT                            1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_TX_PKT_DONE_EN_BMSK                              0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_EN_TX_PKT_DONE_EN_SHFT                                0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_ADDR                                  (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x154)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_PHYS                                  (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x154)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_OFFS                                  (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x154)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_RMSK                                       0x7ff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_IRQ_RECEIVED_IRQ_BMSK                      0x400
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_IRQ_RECEIVED_IRQ_SHFT                         10
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_HPD_PLUG_RECEIVED_IRQ_BMSK                 0x200
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_HPD_PLUG_RECEIVED_IRQ_SHFT                     9
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_HPD_UNPLUG_RECEIVED_IRQ_BMSK               0x100
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_HPD_UNPLUG_RECEIVED_IRQ_SHFT                   8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_ACK_RECEIVED_IRQ_BMSK                       0x80
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_ACK_RECEIVED_IRQ_SHFT                          7
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_PATH_TEARDOWN_IRQ_BMSK                      0x40
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_PATH_TEARDOWN_IRQ_SHFT                         6
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_BLOCK_TX_ACK_IRQ_BMSK                       0x20
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_BLOCK_TX_ACK_IRQ_SHFT                          5
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_RST_ACK_IRQ_BMSK                            0x10
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_RST_ACK_IRQ_SHFT                               4
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_CLK_SYNC_N_PKTS_IRQ_BMSK                     0x8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_CLK_SYNC_N_PKTS_IRQ_SHFT                       3
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_ACK_TIMEOUT_IRQ_BMSK                         0x4
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_ACK_TIMEOUT_IRQ_SHFT                           2
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_RX_PKT_RECEIVED_IRQ_BMSK                     0x2
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_RX_PKT_RECEIVED_IRQ_SHFT                       1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_TX_PKT_DONE_IRQ_BMSK                         0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_STATUS_TX_PKT_DONE_IRQ_SHFT                           0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_ADDR                                     (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x158)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_PHYS                                     (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x158)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_OFFS                                     (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x158)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_RMSK                                          0x7ff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_IRQ_RECEIVED_CLR_BMSK                         0x400
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_IRQ_RECEIVED_CLR_SHFT                            10
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_HPD_PLUG_RECEIVED_CLR_BMSK                    0x200
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_HPD_PLUG_RECEIVED_CLR_SHFT                        9
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_HPD_UNPLUG_RECEIVED_CLR_BMSK                  0x100
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_HPD_UNPLUG_RECEIVED_CLR_SHFT                      8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_ACK_RECEIVED_CLR_BMSK                          0x80
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_ACK_RECEIVED_CLR_SHFT                             7
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_PATH_TEARDOWN_CLR_BMSK                         0x40
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_PATH_TEARDOWN_CLR_SHFT                            6
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_BLOCK_TX_ACK_CLR_BMSK                          0x20
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_BLOCK_TX_ACK_CLR_SHFT                             5
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_RST_ACK_CLR_BMSK                               0x10
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_RST_ACK_CLR_SHFT                                  4
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_CLK_SYNC_N_PKTS_CLR_BMSK                        0x8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_CLK_SYNC_N_PKTS_CLR_SHFT                          3
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_ACK_TIMEOUT_CLR_BMSK                            0x4
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_ACK_TIMEOUT_CLR_SHFT                              2
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_RX_PKT_RECEIVED_CLR_BMSK                        0x2
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_RX_PKT_RECEIVED_CLR_SHFT                          1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_TX_PKT_DONE_CLR_BMSK                            0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_SW_INT_CLR_TX_PKT_DONE_CLR_SHFT                              0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_CALC_ADDR                                    (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x15c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_CALC_PHYS                                    (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x15c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_CALC_OFFS                                    (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x15c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_CALC_RMSK                                    0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_CALC_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_CALC_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_CALC_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_CALC_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_CALC_CRC_CALC_BMSK                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_RX_CRC_CALC_CRC_CALC_SHFT                                    0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_ADDR                                    (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x200)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_PHYS                                    (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x200)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_OFFS                                    (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x200)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_RMSK                                          0x1f
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_AUTO_ACK_DISABLE_BMSK                         0x10
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_AUTO_ACK_DISABLE_SHFT                            4
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_UC_MODE_RX_ACTIVE_BMSK                         0x8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_UC_MODE_RX_ACTIVE_SHFT                           3
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_UC_MODE_TX_ACTIVE_BMSK                         0x4
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_UC_MODE_TX_ACTIVE_SHFT                           2
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_UC_MODE_RX_ENABLE_BMSK                         0x2
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_UC_MODE_RX_ENABLE_SHFT                           1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_UC_MODE_TX_ENABLE_BMSK                         0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CFG_UC_MODE_TX_ENABLE_SHFT                           0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_ADDR                                    (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x204)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_PHYS                                    (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x204)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_OFFS                                    (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x204)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_RMSK                                          0x1f
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_UNCORRECTABLE_ERROR_BMSK                      0x10
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_UNCORRECTABLE_ERROR_SHFT                         4
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_UC_MODE_RX_DROP_PKT_BMSK                       0x8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_UC_MODE_RX_DROP_PKT_SHFT                         3
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_UC_MODE_RX_ACK_BMSK                            0x4
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_UC_MODE_RX_ACK_SHFT                              2
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_UC_MODE_TX_DROP_PKT_BMSK                       0x2
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_UC_MODE_TX_DROP_PKT_SHFT                         1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_UC_MODE_TX_ACK_BMSK                            0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_MODE_CTL_UC_MODE_TX_ACK_SHFT                              0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_ADDR                                      (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x220)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_PHYS                                      (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x220)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_OFFS                                      (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x220)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_RMSK                                          0x1fff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_UC_MODE_RX_PKT_PEND_EN_BMSK                   0x1000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_UC_MODE_RX_PKT_PEND_EN_SHFT                       12
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_UC_MODE_TX_PKT_PEND_EN_BMSK                    0x800
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_UC_MODE_TX_PKT_PEND_EN_SHFT                       11
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_IRQ_RECEIVED_EN_BMSK                           0x400
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_IRQ_RECEIVED_EN_SHFT                              10
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_HPD_PLUG_RECEIVED_EN_BMSK                      0x200
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_HPD_PLUG_RECEIVED_EN_SHFT                          9
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_HPD_UNPLUG_RECEIVED_EN_BMSK                    0x100
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_HPD_UNPLUG_RECEIVED_EN_SHFT                        8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_ACK_RECEIVED_EN_BMSK                            0x80
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_ACK_RECEIVED_EN_SHFT                               7
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_PATH_TEARDOWN_EN_BMSK                           0x40
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_PATH_TEARDOWN_EN_SHFT                              6
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_BLOCK_TX_ACK_EN_BMSK                            0x20
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_BLOCK_TX_ACK_EN_SHFT                               5
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_RST_ACK_EN_BMSK                                 0x10
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_RST_ACK_EN_SHFT                                    4
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_CLK_SYNC_N_PKTS_EN_BMSK                          0x8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_CLK_SYNC_N_PKTS_EN_SHFT                            3
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_ACK_TIMEOUT_EN_BMSK                              0x4
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_ACK_TIMEOUT_EN_SHFT                                2
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_RX_PKT_RECEIVED_EN_BMSK                          0x2
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_RX_PKT_RECEIVED_EN_SHFT                            1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_TX_PKT_DONE_EN_BMSK                              0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_EN_TX_PKT_DONE_EN_SHFT                                0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_ADDR                                  (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x224)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_PHYS                                  (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x224)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_OFFS                                  (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x224)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_RMSK                                      0x1fff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_UC_MODE_RX_PKT_PEND_IRQ_BMSK              0x1000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_UC_MODE_RX_PKT_PEND_IRQ_SHFT                  12
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_UC_MODE_TX_PKT_PEND_IRQ_BMSK               0x800
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_UC_MODE_TX_PKT_PEND_IRQ_SHFT                  11
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_IRQ_RECEIVED_IRQ_BMSK                      0x400
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_IRQ_RECEIVED_IRQ_SHFT                         10
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_HPD_PLUG_RECEIVED_IRQ_BMSK                 0x200
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_HPD_PLUG_RECEIVED_IRQ_SHFT                     9
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_HPD_UNPLUG_RECEIVED_IRQ_BMSK               0x100
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_HPD_UNPLUG_RECEIVED_IRQ_SHFT                   8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_ACK_RECEIVED_IRQ_BMSK                       0x80
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_ACK_RECEIVED_IRQ_SHFT                          7
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_PATH_TEARDOWN_IRQ_BMSK                      0x40
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_PATH_TEARDOWN_IRQ_SHFT                         6
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_BLOCK_TX_ACK_IRQ_BMSK                       0x20
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_BLOCK_TX_ACK_IRQ_SHFT                          5
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_RST_ACK_IRQ_BMSK                            0x10
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_RST_ACK_IRQ_SHFT                               4
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_CLK_SYNC_N_PKTS_IRQ_BMSK                     0x8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_CLK_SYNC_N_PKTS_IRQ_SHFT                       3
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_ACK_TIMEOUT_IRQ_BMSK                         0x4
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_ACK_TIMEOUT_IRQ_SHFT                           2
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_RX_PKT_RECEIVED_IRQ_BMSK                     0x2
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_RX_PKT_RECEIVED_IRQ_SHFT                       1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_TX_PKT_DONE_IRQ_BMSK                         0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_STATUS_TX_PKT_DONE_IRQ_SHFT                           0

#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_ADDR                                     (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE            + 0x228)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_PHYS                                     (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x228)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_OFFS                                     (USB4_HOST_ROUTER_0DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x228)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_RMSK                                         0x1fff
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_UC_MODE_RX_PKT_PEND_CLR_BMSK                 0x1000
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_UC_MODE_RX_PKT_PEND_CLR_SHFT                     12
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_UC_MODE_TX_PKT_PEND_CLR_BMSK                  0x800
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_UC_MODE_TX_PKT_PEND_CLR_SHFT                     11
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_IRQ_RECEIVED_CLR_BMSK                         0x400
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_IRQ_RECEIVED_CLR_SHFT                            10
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_HPD_PLUG_RECEIVED_CLR_BMSK                    0x200
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_HPD_PLUG_RECEIVED_CLR_SHFT                        9
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_HPD_UNPLUG_RECEIVED_CLR_BMSK                  0x100
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_HPD_UNPLUG_RECEIVED_CLR_SHFT                      8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_ACK_RECEIVED_CLR_BMSK                          0x80
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_ACK_RECEIVED_CLR_SHFT                             7
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_PATH_TEARDOWN_CLR_BMSK                         0x40
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_PATH_TEARDOWN_CLR_SHFT                            6
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_BLOCK_TX_ACK_CLR_BMSK                          0x20
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_BLOCK_TX_ACK_CLR_SHFT                             5
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_RST_ACK_CLR_BMSK                               0x10
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_RST_ACK_CLR_SHFT                                  4
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_CLK_SYNC_N_PKTS_CLR_BMSK                        0x8
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_CLK_SYNC_N_PKTS_CLR_SHFT                          3
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_ACK_TIMEOUT_CLR_BMSK                            0x4
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_ACK_TIMEOUT_CLR_SHFT                              2
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_RX_PKT_RECEIVED_CLR_BMSK                        0x2
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_RX_PKT_RECEIVED_CLR_SHFT                          1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_TX_PKT_DONE_CLR_BMSK                            0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DP_AUX_UC_INT_CLR_TX_PKT_DONE_CLR_SHFT                              0

/*----------------------------------------------------------------------------
 * MODULE: USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP
 *--------------------------------------------------------------------------*/

#define USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE                                    (USB4_HOST_ROUTER_0USB4_WRAPPER_BASE            + 0x00010000)
#define USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_SIZE                               0x1000
#define USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_USED                               0x54
#define USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS                               (USB4_HOST_ROUTER_0USB4_WRAPPER_BASE_PHYS + 0x00010000)
#define USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS                               0x00010000

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_SIZE_ADDR                                 (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x0)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_SIZE_PHYS                                 (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x0)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_SIZE_OFFS                                 (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x0)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_SIZE_RMSK                                       0x3f
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_SIZE_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_SIZE_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_SIZE_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_SIZE_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_SIZE_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_SIZE_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_SIZE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_SIZE_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_SIZE_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_SIZE_ALOC_SIZE_BMSK                             0x3f
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_SIZE_ALOC_SIZE_SHFT                                0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_STREAM_ADDR                               (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x4)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_STREAM_PHYS                               (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x4)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_STREAM_OFFS                               (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x4)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_STREAM_RMSK                                      0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_STREAM_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_STREAM_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_STREAM_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_STREAM_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_STREAM_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_STREAM_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_STREAM_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_STREAM_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_STREAM_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_STREAM_MST_NSST_BMSK                             0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STREAM_CFG_STREAM_MST_NSST_SHFT                               0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_BAUD_CFG_ADDR                                        (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x8)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_BAUD_CFG_PHYS                                        (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x8)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_BAUD_CFG_OFFS                                        (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x8)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_BAUD_CFG_RMSK                                               0x7
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_BAUD_CFG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_BAUD_CFG_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_BAUD_CFG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_BAUD_CFG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_BAUD_CFG_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_BAUD_CFG_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_BAUD_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_BAUD_CFG_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_BAUD_CFG_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_BAUD_CFG_RATE_BMSK                                          0x7
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_BAUD_CFG_RATE_SHFT                                            0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CTRL_ADDR                                            (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0xc)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CTRL_PHYS                                            (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0xc)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CTRL_OFFS                                            (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0xc)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CTRL_RMSK                                                   0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CTRL_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CTRL_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CTRL_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CTRL_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CTRL_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CTRL_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CTRL_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CTRL_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CTRL_ARM_EN_BMSK                                            0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CTRL_ARM_EN_SHFT                                              0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_ADDR                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x10)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_PHYS                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x10)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_OFFS                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x10)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_RMSK                                    0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_C3_BMSK                                 0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_C3_SHFT                                         24
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_C2_BMSK                                   0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_C2_SHFT                                         16
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_C1_BMSK                                     0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_C1_SHFT                                          8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_C0_BMSK                                       0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_0_C0_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_ADDR                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x14)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_PHYS                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x14)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_OFFS                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x14)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_RMSK                                    0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_C7_BMSK                                 0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_C7_SHFT                                         24
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_C6_BMSK                                   0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_C6_SHFT                                         16
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_C5_BMSK                                     0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_C5_SHFT                                          8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_C4_BMSK                                       0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_1_C4_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_ADDR                                  (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x18)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_PHYS                                  (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x18)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_OFFS                                  (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x18)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_RMSK                                  0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_ACT3_BMSK                             0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_ACT3_SHFT                                     24
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_ACT2_BMSK                               0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_ACT2_SHFT                                     16
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_ACT1_BMSK                                 0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_ACT1_SHFT                                      8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_ACT0_BMSK                                   0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_ACT_ACT0_SHFT                                      0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_ADDR                                 (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x1c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_PHYS                                 (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x1c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_OFFS                                 (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x1c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_RMSK                                 0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_VCPF3_BMSK                           0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_VCPF3_SHFT                                   24
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_VCPF2_BMSK                             0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_VCPF2_SHFT                                   16
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_VCPF1_BMSK                               0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_VCPF1_SHFT                                    8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_VCPF0_BMSK                                 0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_K_CODE_VCPF_VCPF0_SHFT                                    0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_K_CODE_SR_ADDR                                       (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x20)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_K_CODE_SR_PHYS                                       (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x20)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_K_CODE_SR_OFFS                                       (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x20)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_K_CODE_SR_RMSK                                           0xffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_K_CODE_SR_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_K_CODE_SR_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_K_CODE_SR_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_K_CODE_SR_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_K_CODE_SR_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_K_CODE_SR_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_K_CODE_SR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_K_CODE_SR_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_K_CODE_SR_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_K_CODE_SR_SST_SR_BMSK                                    0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_K_CODE_SR_SST_SR_SHFT                                         8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_K_CODE_SR_MST_SR_BMSK                                      0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_K_CODE_SR_MST_SR_SHFT                                         0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_ADDR                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x24)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_PHYS                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x24)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_OFFS                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x24)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_RMSK                                      0xffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_BF_BMSK                                   0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_BF_SHFT                                         16
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_BS_BMSK                                     0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_BS_SHFT                                          8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_BE_BMSK                                       0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_0_BE_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_ADDR                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x28)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_PHYS                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x28)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_OFFS                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x28)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_RMSK                                      0xffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_CP_BMSK                                   0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_CP_SHFT                                         16
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_FEC_CP_BMSK                                 0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_FEC_CP_SHFT                                      8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_EOC_BMSK                                      0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_1_EOC_SHFT                                         0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_ADDR                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x2c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_PHYS                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x2c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_OFFS                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x2c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_RMSK                                    0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_SS_BMSK                                 0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_SS_SHFT                                         24
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_FE_BMSK                                   0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_FE_SHFT                                         16
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_SE_BMSK                                     0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_SE_SHFT                                          8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_FS_BMSK                                       0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_K_CODE_2_FS_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_ADDR                                      (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x30)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_PHYS                                      (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x30)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_OFFS                                      (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x30)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_RMSK                                      0xffffffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_PH_BMSK                                   0xff000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_PH_SHFT                                           24
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_PM_BMSK                                     0xff0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_PM_SHFT                                           16
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_DEC_EN_BMSK                                   0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_DEC_EN_SHFT                                        8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_DEC_DIS_BMSK                                    0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_FEC_K_CODE_DEC_DIS_SHFT                                       0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_CFG_ADDR                                         (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x34)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_CFG_PHYS                                         (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x34)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_CFG_OFFS                                         (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x34)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_CFG_RMSK                                             0xffff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_CFG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_CFG_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_CFG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_CFG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_CFG_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_CFG_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_CFG_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_CFG_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_CFG_MAX_BYTES_PER_USB4_PKT_BMSK                      0xff00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_CFG_MAX_BYTES_PER_USB4_PKT_SHFT                           8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_CFG_MAX_TUS_PER_USB4_PKT_BMSK                          0xff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_MST_CFG_MAX_TUS_PER_USB4_PKT_SHFT                             0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PKT_CFG_SST_ADDR                                     (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x40)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PKT_CFG_SST_PHYS                                     (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x40)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PKT_CFG_SST_OFFS                                     (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x40)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PKT_CFG_SST_RMSK                                         0x3fff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PKT_CFG_SST_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PKT_CFG_SST_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PKT_CFG_SST_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PKT_CFG_SST_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PKT_CFG_SST_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PKT_CFG_SST_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PKT_CFG_SST_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PKT_CFG_SST_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PKT_CFG_SST_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PKT_CFG_SST_SST_MAX_TUS_PER_USB4_PKT_BMSK                0x3e00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PKT_CFG_SST_SST_MAX_TUS_PER_USB4_PKT_SHFT                     9
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PKT_CFG_SST_SST_MAX_BYTES_PER_USB4_PKT_BMSK               0x1ff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_PKT_CFG_SST_SST_MAX_BYTES_PER_USB4_PKT_SHFT                   0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_ADDR                                             (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x44)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_PHYS                                             (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x44)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_OFFS                                             (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x44)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_RMSK                                                    0x7
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_BLOCK_TX_QUIET_BMSK                                     0x4
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_BLOCK_TX_QUIET_SHFT                                       2
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_BLOCK_TX_ACK_BMSK                                       0x2
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_BLOCK_TX_ACK_SHFT                                         1
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_BLOCK_TX_BMSK                                           0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_RST_BLOCK_TX_SHFT                                             0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CLK_SYNC_CFG_ADDR                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x48)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CLK_SYNC_CFG_PHYS                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x48)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CLK_SYNC_CFG_OFFS                                    (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x48)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CLK_SYNC_CFG_RMSK                                           0xf
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CLK_SYNC_CFG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CLK_SYNC_CFG_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CLK_SYNC_CFG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CLK_SYNC_CFG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CLK_SYNC_CFG_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CLK_SYNC_CFG_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CLK_SYNC_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CLK_SYNC_CFG_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CLK_SYNC_CFG_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CLK_SYNC_CFG_NUM_PKTS_TO_INT_BMSK                           0xf
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_CLK_SYNC_CFG_NUM_PKTS_TO_INT_SHFT                             0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ABS_PRIORITY_CFG_ADDR                                (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x4c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ABS_PRIORITY_CFG_PHYS                                (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x4c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ABS_PRIORITY_CFG_OFFS                                (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x4c)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ABS_PRIORITY_CFG_RMSK                                    0x1f1f
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ABS_PRIORITY_CFG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ABS_PRIORITY_CFG_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ABS_PRIORITY_CFG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ABS_PRIORITY_CFG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ABS_PRIORITY_CFG_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ABS_PRIORITY_CFG_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ABS_PRIORITY_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ABS_PRIORITY_CFG_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ABS_PRIORITY_CFG_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ABS_PRIORITY_CFG_CLR_ABS_PRI_THRESH_BMSK                 0x1f00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ABS_PRIORITY_CFG_CLR_ABS_PRI_THRESH_SHFT                      8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ABS_PRIORITY_CFG_SET_ABS_PRI_THRESH_BMSK                   0x1f
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_ABS_PRIORITY_CFG_SET_ABS_PRI_THRESH_SHFT                      0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_ADDR                                      (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x50)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_PHYS                                      (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x50)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_OFFS                                      (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x50)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_RMSK                                      0x7f7f7f7f
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_SST_MAX_BYTES_PER_SDP_TU_4L_BMSK          0x7f000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_SST_MAX_BYTES_PER_SDP_TU_4L_SHFT                  24
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_SST_MAX_BYTES_PER_SDP_TU_2L_BMSK            0x7f0000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_SST_MAX_BYTES_PER_SDP_TU_2L_SHFT                  16
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_SST_MAX_BYTES_PER_SDP_TU_1L_BMSK              0x7f00
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_SST_MAX_BYTES_PER_SDP_TU_1L_SHFT                   8
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_SST_MAX_BYTES_PER_VID_TU_BMSK                   0x7f
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_SST_TU_CFG_SST_MAX_BYTES_PER_VID_TU_SHFT                      0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STATE_FIFOS_ADDR                                     (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x54)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STATE_FIFOS_PHYS                                     (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x54)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STATE_FIFOS_OFFS                                     (USB4_HOST_ROUTER_0DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x54)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STATE_FIFOS_RMSK                                         0x7fff
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STATE_FIFOS_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STATE_FIFOS_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STATE_FIFOS_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STATE_FIFOS_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STATE_FIFOS_SST_TU_IN_FIFO_MAX_CNT_BMSK                  0x7800
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STATE_FIFOS_SST_TU_IN_FIFO_MAX_CNT_SHFT                      11
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STATE_FIFOS_BP_FIFO_MAX_CNT_BMSK                          0x7c0
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STATE_FIFOS_BP_FIFO_MAX_CNT_SHFT                              6
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STATE_FIFOS_EGRESS_FIFO_MAX_CNT_BMSK                       0x3f
#define HWIO_USB4_HOST_ROUTER_0USB4_DPINAP_STATE_FIFOS_EGRESS_FIFO_MAX_CNT_SHFT                          0

/*----------------------------------------------------------------------------
 * MODULE: USB4_HOST_ROUTER_0DPAP_CONFIG_PROP
 *--------------------------------------------------------------------------*/

#define USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE                                             (USB4_HOST_ROUTER_0USB4_WRAPPER_BASE            + 0x00084000)
#define USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE_SIZE                                        0x1000
#define USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE_USED                                        0x10
#define USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE_PHYS                                        (USB4_HOST_ROUTER_0USB4_WRAPPER_BASE_PHYS + 0x00084000)
#define USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE_OFFS                                        0x00084000

#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_ADDR                                       (USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE            + 0x0)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_PHYS                                       (USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE_PHYS + 0x0)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_OFFS                                       (USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE_OFFS + 0x0)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_RMSK                                              0x7
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_DP_PCLK_SYS_CLK_SELECTED_BMSK                     0x4
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_DP_PCLK_SYS_CLK_SELECTED_SHFT                       2
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_DP_PCLK_MAX_PCLK_SELECTED_BMSK                    0x2
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_DP_PCLK_MAX_PCLK_SELECTED_SHFT                      1
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_DP_PCLK_SEL_BMSK                                  0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_PCLK_DP_PCLK_SEL_SHFT                                    0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_SYS_CLK_RESET_ADDR                                 (USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE            + 0x4)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_SYS_CLK_RESET_PHYS                                 (USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE_PHYS + 0x4)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_SYS_CLK_RESET_OFFS                                 (USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE_OFFS + 0x4)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_SYS_CLK_RESET_RMSK                                        0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_SYS_CLK_RESET_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_SYS_CLK_RESET_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_SYS_CLK_RESET_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_SYS_CLK_RESET_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_SYS_CLK_RESET_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_SYS_CLK_RESET_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_SYS_CLK_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_SYS_CLK_RESET_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_SYS_CLK_RESET_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_SYS_CLK_RESET_SYS_CLK_SYNC_RST_DP_BMSK                    0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_SYS_CLK_RESET_SYS_CLK_SYNC_RST_DP_SHFT                      0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_ADDR                                  (USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE            + 0x8)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_PHYS                                  (USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE_PHYS + 0x8)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_OFFS                                  (USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE_OFFS + 0x8)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_RMSK                                  0xe0000007
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_DP_SW_RST_ACK_ANDED_BMSK              0x80000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_DP_SW_RST_ACK_ANDED_SHFT                      31
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_DP_SW_RST_ACK_MX_DOMAIN_BMSK          0x40000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_DP_SW_RST_ACK_MX_DOMAIN_SHFT                  30
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_DP_SW_RST_ACK_MAX_PCLK_BMSK           0x20000000
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_DP_SW_RST_ACK_MAX_PCLK_SHFT                   29
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_DP_AUX_RST_BMSK                              0x4
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_DP_AUX_RST_SHFT                                2
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_DP_AP_CS_RST_BMSK                            0x2
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_DP_AP_CS_RST_SHFT                              1
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_DP_SW_RST_BMSK                               0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_CLK_RESET_DP_SW_RST_SHFT                                 0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_TUNNEL_MODE_ADDR                                (USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE            + 0xc)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_TUNNEL_MODE_PHYS                                (USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE_PHYS + 0xc)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_TUNNEL_MODE_OFFS                                (USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE_OFFS + 0xc)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_TUNNEL_MODE_RMSK                                       0x3
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_TUNNEL_MODE_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_TUNNEL_MODE_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_TUNNEL_MODE_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_TUNNEL_MODE_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_TUNNEL_MODE_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_TUNNEL_MODE_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_TUNNEL_MODE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_TUNNEL_MODE_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_TUNNEL_MODE_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_TUNNEL_MODE_DP_TBT3_MODE_EN_BMSK                       0x2
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_TUNNEL_MODE_DP_TBT3_MODE_EN_SHFT                         1
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_TUNNEL_MODE_DP_ENTERPRIZE_TNL_EN_BMSK                  0x1
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_DP_TUNNEL_MODE_DP_ENTERPRIZE_TNL_EN_SHFT                    0

#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_USB4_LINK_CFG_ADDR                                 (USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE            + 0x10)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_USB4_LINK_CFG_PHYS                                 (USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE_PHYS + 0x10)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_USB4_LINK_CFG_OFFS                                 (USB4_HOST_ROUTER_0DPAP_CONFIG_PROP_REG_BASE_OFFS + 0x10)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_USB4_LINK_CFG_RMSK                                        0xf
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_USB4_LINK_CFG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_USB4_LINK_CFG_ADDR)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_USB4_LINK_CFG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_USB4_LINK_CFG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_USB4_LINK_CFG_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_USB4_LINK_CFG_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_USB4_LINK_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_USB4_LINK_CFG_ADDR,m,v,HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_USB4_LINK_CFG_IN)
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_USB4_LINK_CFG_LINK_RATE_BMSK                              0xf
#define HWIO_USB4_HOST_ROUTER_0USB4_DPAP_CFG_USB4_LINK_CFG_LINK_RATE_SHFT                                0

/*----------------------------------------------------------------------------
 * MODULE: USB4_HOST_ROUTER_1CFG_REGS
 *--------------------------------------------------------------------------*/

#define USB4_HOST_ROUTER_1CFG_REGS_REG_BASE                                                            (USB4_HOST_ROUTER_1USB4_WRAPPER_BASE            + 0x00080000)
#define USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_SIZE                                                       0x1000
#define USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_USED                                                       0x404
#define USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_PHYS                                                       (USB4_HOST_ROUTER_1USB4_WRAPPER_BASE_PHYS + 0x00080000)
#define USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_OFFS                                                       0x00080000

#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_ADDR                                               (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE            + 0x0)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_PHYS                                               (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_PHYS + 0x0)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_OFFS                                               (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_OFFS + 0x0)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_RMSK                                                  0x3ffff
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_PCIEAP_BMSK                                0x20000
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_PCIEAP_SHFT                                     17
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_DEBUG_BMSK                                 0x10000
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_DEBUG_SHFT                                      16
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_PORT_BMSK                                   0x8000
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_PORT_SHFT                                       15
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_ULL_BMSK                                    0x4000
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_ULL_SHFT                                        14
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_PG_FAST_BMSK                                0x2000
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_PG_FAST_SHFT                                    13
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_PG_BMSK                                     0x1000
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_PG_SHFT                                         12
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_TMU_BMSK                                     0x800
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_TMU_SHFT                                        11
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_MSGBUS_BMSK                                  0x400
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_MSGBUS_SHFT                                     10
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_LPBK_BMSK                                    0x200
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_LPBK_SHFT                                        9
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_RAM_BMSK                                     0x100
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_RAM_SHFT                                         8
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_USBAP_BMSK                                    0x80
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_USBAP_SHFT                                       7
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_DP_BMSK                                       0x40
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_DP_SHFT                                          6
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_HIA_BMSK                                      0x20
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_HIA_SHFT                                         5
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_SB_BMSK                                       0x10
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_SB_SHFT                                          4
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_UC_NON_DIV_BMSK                                0x8
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_UC_NON_DIV_SHFT                                  3
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_UC_GLOBAL_BMSK                                 0x4
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_UC_GLOBAL_SHFT                                   2
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_UC_FREE_BMSK                                   0x2
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_UC_FREE_SHFT                                     1
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_AHB_MNGR_BMSK                                  0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_CGC_SYS_CLK_EN_AHB_MNGR_SHFT                                    0

#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_ADDR                                             (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE            + 0x4)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_PHYS                                             (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_PHYS + 0x4)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_OFFS                                             (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_OFFS + 0x4)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_RMSK                                                   0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_SB_IF_CLK_EN_BMSK                                      0x80
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_SB_IF_CLK_EN_SHFT                                         7
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_TMU_CLK_EN_BMSK                                        0x40
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_TMU_CLK_EN_SHFT                                           6
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_HIA_MSTR_CLK_EN_BMSK                                   0x20
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_HIA_MSTR_CLK_EN_SHFT                                      5
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_DP_PCLK_EN_BMSK                                        0x10
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_DP_PCLK_EN_SHFT                                           4
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_USB_PIPE_CLK_EN_BMSK                                    0x8
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_USB_PIPE_CLK_EN_SHFT                                      3
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_PCIE_PIPE_CLK_EN_BMSK                                   0x4
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_PCIE_PIPE_CLK_EN_SHFT                                     2
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_RX_CLK_1_EN_BMSK                                        0x2
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_RX_CLK_1_EN_SHFT                                          1
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_RX_CLK_0_EN_BMSK                                        0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_OTHER_CLK_CGC_RX_CLK_0_EN_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_ADDR                                                      (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE            + 0x8)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_PHYS                                                      (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_PHYS + 0x8)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_OFFS                                                      (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_OFFS + 0x8)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_RMSK                                                          0x3fff
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_CMB_DATA_TS_BMSK                                     0x2000
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_CMB_DATA_TS_SHFT                                         13
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_CMB_BYTES_BMSK                                       0x1c00
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_CMB_BYTES_SHFT                                           10
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_CMB_SECURE_EN_BMSK                                    0x200
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_CMB_SECURE_EN_SHFT                                        9
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_CMB_ERR_REQ_BMSK                                      0x100
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_CMB_ERR_REQ_SHFT                                          8
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_CMB_I_BMSK                                             0xe0
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_CMB_I_SHFT                                                5
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_GPR_CLK_EN_BMSK                                        0x10
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_GPR_CLK_EN_SHFT                                           4
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_APB_CLK_EN_BMSK                                         0x8
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_APB_CLK_EN_SHFT                                           3
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_ATB_CLK_EN_BMSK                                         0x4
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_ATB_CLK_EN_SHFT                                           2
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_GPR_CLK_OFF_BMSK                                        0x2
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_GPR_CLK_OFF_SHFT                                          1
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_CMB_CLK_OFF_BMSK                                        0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_CFG_TPDM_CMB_CLK_OFF_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_STATUS_ADDR                                               (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE            + 0xc)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_STATUS_PHYS                                               (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_PHYS + 0xc)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_STATUS_OFFS                                               (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_OFFS + 0xc)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_STATUS_RMSK                                                      0x7
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_STATUS_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_STATUS_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_STATUS_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_STATUS_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_STATUS_TPDM_CMB_CLKON_BMSK                                       0x4
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_STATUS_TPDM_CMB_CLKON_SHFT                                         2
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_STATUS_TPDM_CMB_CGC_ACTIVE_BMSK                                  0x2
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_STATUS_TPDM_CMB_CGC_ACTIVE_SHFT                                    1
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_STATUS_TPDM_CMB_ACTIVE_BMSK                                      0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_TPDM_STATUS_TPDM_CMB_ACTIVE_SHFT                                        0

#define HWIO_USB4_HOST_ROUTER_1USB4_RESP_ERR_EN_ADDR                                                   (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE            + 0x10)
#define HWIO_USB4_HOST_ROUTER_1USB4_RESP_ERR_EN_PHYS                                                   (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_PHYS + 0x10)
#define HWIO_USB4_HOST_ROUTER_1USB4_RESP_ERR_EN_OFFS                                                   (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_OFFS + 0x10)
#define HWIO_USB4_HOST_ROUTER_1USB4_RESP_ERR_EN_RMSK                                                          0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_RESP_ERR_EN_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_RESP_ERR_EN_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_RESP_ERR_EN_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_RESP_ERR_EN_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_RESP_ERR_EN_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_RESP_ERR_EN_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_RESP_ERR_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_RESP_ERR_EN_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_RESP_ERR_EN_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_RESP_ERR_EN_RESP_ERR_EN_BMSK                                              0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_RESP_ERR_EN_RESP_ERR_EN_SHFT                                                0

#define HWIO_USB4_HOST_ROUTER_1USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_ADDR                           (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE            + 0x14)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_PHYS                           (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_PHYS + 0x14)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_OFFS                           (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_OFFS + 0x14)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_RMSK                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_DEFAULT_RD_DATA_BMSK           0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_RESP_ACCESS_NON_IMPLEMENTED_REGS_DEFAULT_RD_DATA_SHFT                    0

#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_RESET_ADDR                                             (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE            + 0x18)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_RESET_PHYS                                             (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_PHYS + 0x18)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_RESET_OFFS                                             (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_OFFS + 0x18)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_RESET_RMSK                                                    0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_RESET_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_RESET_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_RESET_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_RESET_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_RESET_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_RESET_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_RESET_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_RESET_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_RESET_SYS_CLK_SYNC_RST_HIA_BMSK                               0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_CFG_SYS_CLK_RESET_SYS_CLK_SYNC_RST_HIA_SHFT                                 0

#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_ADDR_ADDR                                              (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE            + 0x30)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_ADDR_PHYS                                              (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_PHYS + 0x30)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_ADDR_OFFS                                              (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_OFFS + 0x30)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_ADDR_RMSK                                              0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_ADDR_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_ADDR_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_ADDR_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_ADDR_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_ADDR_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_ADDR_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_ADDR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_ADDR_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_ADDR_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_ADDR_RD_PGRX_RAM_ADDR_BMSK                             0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_ADDR_RD_PGRX_RAM_ADDR_SHFT                                      0

#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_EN_ADDR                                                (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE            + 0x34)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_EN_PHYS                                                (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_PHYS + 0x34)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_EN_OFFS                                                (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_OFFS + 0x34)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_EN_RMSK                                                0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_EN_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_EN_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_EN_RD_PGRX_RAM_EN_BMSK                                 0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_RAM_EN_RD_PGRX_RAM_EN_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_DATA_n_ADDR(n)                                             (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE            + 0x38 + (0x4*(n)))
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_DATA_n_PHYS(n)                                             (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_PHYS + 0x38 + (0x4*(n)))
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_DATA_n_OFFS(n)                                             (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_OFFS + 0x38 + (0x4*(n)))
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_DATA_n_RMSK                                                0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_DATA_n_MAXn                                                         3
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_DATA_n_INI(n)                \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_DATA_n_ADDR(n), HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_DATA_n_RMSK)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_DATA_n_INMI(n,mask)        \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_DATA_n_ADDR(n), mask)
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_DATA_n_RD_PGRX_DATA_BMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_RD_PGRX_DATA_n_RD_PGRX_DATA_SHFT                                            0

#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_n_ADDR(n)                                              (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE            + 0x60 + (0x4*(n)))
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_n_PHYS(n)                                              (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_PHYS + 0x60 + (0x4*(n)))
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_n_OFFS(n)                                              (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_OFFS + 0x60 + (0x4*(n)))
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_n_RMSK                                                 0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_n_MAXn                                                          8
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_n_INI(n)                \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_n_ADDR(n), HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_n_RMSK)
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_n_INMI(n,mask)        \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_n_ADDR(n), mask)
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_n_OUTI(n,val)        \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_n_ADDR(n),val)
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_n_OUTMI(n,mask,val) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_n_ADDR(n),mask,val,HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_n_INI(n))
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_n_TESTBUSE_SEL_BMSK                                    0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_n_TESTBUSE_SEL_SHFT                                             0

#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_ADDR                                           (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE            + 0x100)
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_PHYS                                           (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_PHYS + 0x100)
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_OFFS                                           (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_OFFS + 0x100)
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_RMSK                                            0xfffff3f
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_USB4_QSB2AXI_TEST_BUS_SEL_BMSK                  0xff00000
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_USB4_QSB2AXI_TEST_BUS_SEL_SHFT                         20
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_TPDM_CLK_SEL_BMSK                                 0xff000
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_TPDM_CLK_SEL_SHFT                                      12
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_CFG_BITS_BMSK                                       0xc00
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_CFG_BITS_SHFT                                          10
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_AHB_MANAGER_TEST_BUS_BMSK                           0x300
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_AHB_MANAGER_TEST_BUS_SHFT                               8
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_DP_TEST_BUS_BMSK                                     0x3f
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL1_DP_TEST_BUS_SHFT                                        0

#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_ADDR                                           (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE            + 0x104)
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_PHYS                                           (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_PHYS + 0x104)
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_OFFS                                           (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_OFFS + 0x104)
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_RMSK                                              0xfffff
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_USB4_TEST_PORT_SEL_BMSK                           0xf8000
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_USB4_TEST_PORT_SEL_SHFT                                15
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_USB4_UC_TEST_BUS_CLIENT_SEL_BMSK                   0x7000
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_USB4_UC_TEST_BUS_CLIENT_SEL_SHFT                       12
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_USB4_UC_TEST_BUS_SEL_BMSK                           0xe00
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_USB4_UC_TEST_BUS_SEL_SHFT                               9
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_FETCHER_CMDQ_TEST_BUS_SEL_BMSK                      0x180
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_FETCHER_CMDQ_TEST_BUS_SEL_SHFT                          7
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_FETCHER_CMDQ_TEST_BUS_CLIENT_SEL_BMSK                0x60
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_FETCHER_CMDQ_TEST_BUS_CLIENT_SEL_SHFT                   5
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_USB4_QSB2AXI_TEST_BUS_CLIENT_SEL_BMSK                0x1f
#define HWIO_USB4_HOST_ROUTER_1USB4_TESTBUS_SEL_GLOBAL2_USB4_QSB2AXI_TEST_BUS_CLIENT_SEL_SHFT                   0

#define HWIO_USB4_HOST_ROUTER_1USB4_DEBUG_REG_ADDR                                                     (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE            + 0x200)
#define HWIO_USB4_HOST_ROUTER_1USB4_DEBUG_REG_PHYS                                                     (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_PHYS + 0x200)
#define HWIO_USB4_HOST_ROUTER_1USB4_DEBUG_REG_OFFS                                                     (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_OFFS + 0x200)
#define HWIO_USB4_HOST_ROUTER_1USB4_DEBUG_REG_RMSK                                                     0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DEBUG_REG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DEBUG_REG_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DEBUG_REG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DEBUG_REG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DEBUG_REG_DEBUG_REG_BMSK                                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DEBUG_REG_DEBUG_REG_SHFT                                                    0

#define HWIO_USB4_HOST_ROUTER_1USB4_IP_CAT_VERSION_ADDR                                                (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE            + 0x400)
#define HWIO_USB4_HOST_ROUTER_1USB4_IP_CAT_VERSION_PHYS                                                (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_PHYS + 0x400)
#define HWIO_USB4_HOST_ROUTER_1USB4_IP_CAT_VERSION_OFFS                                                (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_OFFS + 0x400)
#define HWIO_USB4_HOST_ROUTER_1USB4_IP_CAT_VERSION_RMSK                                                0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_IP_CAT_VERSION_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_IP_CAT_VERSION_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_IP_CAT_VERSION_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_IP_CAT_VERSION_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_IP_CAT_VERSION_IP_CAT_VERSION_BMSK                                 0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_IP_CAT_VERSION_IP_CAT_VERSION_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_1USB4_HW_VERSION_ADDR                                                    (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE            + 0x404)
#define HWIO_USB4_HOST_ROUTER_1USB4_HW_VERSION_PHYS                                                    (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_PHYS + 0x404)
#define HWIO_USB4_HOST_ROUTER_1USB4_HW_VERSION_OFFS                                                    (USB4_HOST_ROUTER_1CFG_REGS_REG_BASE_OFFS + 0x404)
#define HWIO_USB4_HOST_ROUTER_1USB4_HW_VERSION_RMSK                                                    0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_HW_VERSION_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_HW_VERSION_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_HW_VERSION_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_HW_VERSION_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_HW_VERSION_HW_VERSION_BMSK                                         0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_HW_VERSION_HW_VERSION_SHFT                                                  0

/*----------------------------------------------------------------------------
 * MODULE: USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP
 *--------------------------------------------------------------------------*/

#define USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE                                                 (USB4_HOST_ROUTER_1USB4_WRAPPER_BASE            + 0x00006000)
#define USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_SIZE                                            0x400
#define USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_USED                                            0x44
#define USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS                                            (USB4_HOST_ROUTER_1USB4_WRAPPER_BASE_PHYS + 0x00006000)
#define USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS                                            0x00006000

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_0_STANDARD_ADDR                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x0)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_0_STANDARD_PHYS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x0)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_0_STANDARD_OFFS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x0)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_0_STANDARD_RMSK                                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_0_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_0_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_0_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_0_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_0_STANDARD_VENDOR_DEFINED_RSV_BMSK                        0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_0_STANDARD_VENDOR_DEFINED_RSV_SHFT                                 0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_1_STANDARD_ADDR                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x4)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_1_STANDARD_PHYS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x4)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_1_STANDARD_OFFS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x4)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_1_STANDARD_RMSK                                              0xfffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_1_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_1_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_1_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_1_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_1_STANDARD_CCS_FLAG_BMSK                                     0x80000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_1_STANDARD_CCS_FLAG_SHFT                                          19
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_1_STANDARD_MAX_COUNTER_SETS_BMSK                             0x7ff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_1_STANDARD_MAX_COUNTER_SETS_SHFT                                   8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_1_STANDARD_NEXT_CAPABILITY_POINTER_BMSK                         0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_1_STANDARD_NEXT_CAPABILITY_POINTER_SHFT                            0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_2_STANDARD_ADDR                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x8)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_2_STANDARD_PHYS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x8)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_2_STANDARD_OFFS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x8)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_2_STANDARD_RMSK                                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_2_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_2_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_2_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_2_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_2_STANDARD_RSVD_BMSK                                      0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_2_STANDARD_RSVD_SHFT                                              24
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_2_STANDARD_ADAPTER_TYPE_PROTOCOL_BMSK                       0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_2_STANDARD_ADAPTER_TYPE_PROTOCOL_SHFT                             16
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_2_STANDARD_ADAPTER_TYPE_VERSION_BMSK                          0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_2_STANDARD_ADAPTER_TYPE_VERSION_SHFT                               8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_2_STANDARD_ADAPTER_TYPE_SUB_TYPE_BMSK                           0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_2_STANDARD_ADAPTER_TYPE_SUB_TYPE_SHFT                              0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_3_STANDARD_ADDR                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0xc)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_3_STANDARD_PHYS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0xc)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_3_STANDARD_OFFS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0xc)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_3_STANDARD_RMSK                                           0xe3f00000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_3_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_3_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_3_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_3_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_3_STANDARD_SBC_BMSK                                       0x80000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_3_STANDARD_SBC_SHFT                                               31
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_3_STANDARD_FCE_BMSK                                       0x40000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_3_STANDARD_FCE_SHFT                                               30
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_3_STANDARD_HE_BMSK                                        0x20000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_3_STANDARD_HE_SHFT                                                29
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_3_STANDARD_ADAPTER_NUMBER_BMSK                             0x3f00000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_3_STANDARD_ADAPTER_NUMBER_SHFT                                    20

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_ADDR                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x10)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_PHYS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x10)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_OFFS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x10)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_RMSK                                           0xfff003ff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_LCK_BMSK                                       0x80000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_LCK_SHFT                                               31
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_PLUGGED_BMSK                                   0x40000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_PLUGGED_SHFT                                           30
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_TOTAL_BUFFERS_BMSK                             0x3ff00000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_TOTAL_BUFFERS_SHFT                                     20
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_NON_FLOW_CONTROLLED_BUFFERS_BMSK                    0x3ff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_4_STANDARD_NON_FLOW_CONTROLLED_BUFFERS_SHFT                        0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_ADDR                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x14)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_PHYS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x14)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_OFFS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x14)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_RMSK                                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_DHP_BMSK                                       0x80000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_DHP_SHFT                                               31
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_FCEE_BMSK                                      0x40000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_FCEE_SHFT                                              30
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_HEE_BMSK                                       0x20000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_HEE_SHFT                                               29
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_LINK_CREDITS_ALLOCATED_BMSK                    0x1fc00000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_LINK_CREDITS_ALLOCATED_SHFT                            22
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_MAX_OUTPUT_HOPID_BMSK                            0x3ff800
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_MAX_OUTPUT_HOPID_SHFT                                  11
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_MAX_INPUT_HOPID_BMSK                                0x7ff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_5_STANDARD_MAX_INPUT_HOPID_SHFT                                    0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_6_STANDARD_ADDR                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x18)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_6_STANDARD_PHYS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x18)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_6_STANDARD_OFFS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x18)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_6_STANDARD_RMSK                                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_6_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_6_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_6_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_6_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_6_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_6_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_6_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_6_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_6_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_6_STANDARD_HEC_ERRORS_BMSK                                0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_6_STANDARD_HEC_ERRORS_SHFT                                         0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_7_STANDARD_ADDR                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x1c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_7_STANDARD_PHYS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x1c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_7_STANDARD_OFFS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x1c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_7_STANDARD_RMSK                                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_7_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_7_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_7_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_7_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_7_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_7_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_7_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_7_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_7_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_7_STANDARD_INVALID_HOPID_ERRORS_BMSK                      0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_7_STANDARD_INVALID_HOPID_ERRORS_SHFT                               0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_8_STANDARD_ADDR                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x20)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_8_STANDARD_PHYS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x20)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_8_STANDARD_OFFS                                           (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x20)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_8_STANDARD_RMSK                                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_8_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_8_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_8_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_8_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_8_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_8_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_8_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_8_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_8_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_8_STANDARD_ECC_ERRORS_BMSK                                0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_CS_8_STANDARD_ECC_ERRORS_SHFT                                         0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_ADDR                                        (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x28)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_PHYS                                        (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x28)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_OFFS                                        (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x28)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_RMSK                                        0xc7ffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_VE_BMSK                                     0x80000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_VE_SHFT                                             31
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_AE_BMSK                                     0x40000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_AE_SHFT                                             30
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_VIDEO_HOPID_BMSK                             0x7ff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_VIDEO_HOPID_SHFT                                    16
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_CAPABILITY_ID_BMSK                              0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_CAPABILITY_ID_SHFT                                   8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_NEXT_CAPABILITY_POINTER_BMSK                      0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_0_STANDARD_NEXT_CAPABILITY_POINTER_SHFT                         0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_1_STANDARD_ADDR                                        (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x2c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_1_STANDARD_PHYS                                        (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x2c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_1_STANDARD_OFFS                                        (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x2c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_1_STANDARD_RMSK                                          0x3fffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_1_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_1_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_1_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_1_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_1_STANDARD_AUX_RX_HOPID_BMSK                             0x3ff800
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_1_STANDARD_AUX_RX_HOPID_SHFT                                   11
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_1_STANDARD_AUX_TX_HOPID_BMSK                                0x7ff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_1_STANDARD_AUX_TX_HOPID_SHFT                                    0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_2_STANDARD_ADDR                                        (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x30)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_2_STANDARD_PHYS                                        (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x30)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_2_STANDARD_OFFS                                        (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x30)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_2_STANDARD_RMSK                                              0x48
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_2_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_2_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_2_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_2_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_2_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_2_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_2_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_2_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_2_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_2_STANDARD_HPD_STATUS_BMSK                                   0x40
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_2_STANDARD_HPD_STATUS_SHFT                                      6
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_2_STANDARD_SWLI_BMSK                                          0x8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_2_STANDARD_SWLI_SHFT                                            3

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_3_STANDARD_ADDR                                        (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x34)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_3_STANDARD_PHYS                                        (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x34)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_3_STANDARD_OFFS                                        (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x34)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_3_STANDARD_RMSK                                             0x600
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_3_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_3_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_3_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_3_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_3_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_3_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_3_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_3_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_3_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_3_STANDARD_HPDS_BMSK                                        0x400
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_3_STANDARD_HPDS_SHFT                                           10
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_3_STANDARD_HPDC_BMSK                                        0x200
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ADP_DP_CS_3_STANDARD_HPDC_SHFT                                            9

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_ADDR                                       (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x38)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_PHYS                                       (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x38)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_OFFS                                       (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x38)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_RMSK                                       0x2fc0ffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_DSC_NOT_SUPPORTED_BMSK                     0x20000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_DSC_NOT_SUPPORTED_SHFT                             29
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_LTTPR_NOT_SUPPORTED_BMSK                    0x8000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_LTTPR_NOT_SUPPORTED_SHFT                           27
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_SECONDARY_SPLIT_CAPABILITY_BMSK             0x4000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_SECONDARY_SPLIT_CAPABILITY_SHFT                    26
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_FEC_NOT_SUPPORTED_BMSK                      0x2000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_FEC_NOT_SUPPORTED_SHFT                             25
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_TPS4_CAPABILITY_BMSK                        0x1000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_TPS4_CAPABILITY_SHFT                               24
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_RSVD_1_BMSK                                  0x800000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_RSVD_1_SHFT                                        23
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_TPS3_CAPABILITY_BMSK                         0x400000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_TPS3_CAPABILITY_SHFT                               22
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_MST_CAPABILITY_BMSK                            0x8000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_MST_CAPABILITY_SHFT                                15
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_MAXIMAL_LANE_COUNT_BMSK                        0x7000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_MAXIMAL_LANE_COUNT_SHFT                            12
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_MAXIMAL_LINK_RATE_BMSK                          0xf00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_MAXIMAL_LINK_RATE_SHFT                              8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_MAXIMAL_DPCD_REV_BMSK                            0xf0
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_MAXIMAL_DPCD_REV_SHFT                               4
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_PROTOCOL_ADAPTER_REVISION_BMSK                    0xf
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_LOCAL_CAP_STANDARD_PROTOCOL_ADAPTER_REVISION_SHFT                      0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_ADDR                                      (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x3c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_PHYS                                      (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x3c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_OFFS                                      (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x3c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_RMSK                                      0x2f40ffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_DSC_NOT_SUPPORTED_BMSK                    0x20000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_DSC_NOT_SUPPORTED_SHFT                            29
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_LTTPR_NOT_SUPPORTED_BMSK                   0x8000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_LTTPR_NOT_SUPPORTED_SHFT                          27
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_SECONDARY_SPLIT_CAPABILITY_BMSK            0x4000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_SECONDARY_SPLIT_CAPABILITY_SHFT                   26
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_FEC_NOT_SUPPORTED_BMSK                     0x2000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_FEC_NOT_SUPPORTED_SHFT                            25
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_TPS4_CAPABILITY_BMSK                       0x1000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_TPS4_CAPABILITY_SHFT                              24
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_TPS3_CAPABILITY_BMSK                        0x400000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_TPS3_CAPABILITY_SHFT                              22
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_MST_CAPABILITY_BMSK                           0x8000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_MST_CAPABILITY_SHFT                               15
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_MAXIMAL_LANE_COUNT_BMSK                       0x7000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_MAXIMAL_LANE_COUNT_SHFT                           12
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_MAXIMAL_LINK_RATE_BMSK                         0xf00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_MAXIMAL_LINK_RATE_SHFT                             8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_MAXIMAL_DPCD_REV_BMSK                           0xf0
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_MAXIMAL_DPCD_REV_SHFT                              4
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_PROTOCOL_ADAPTER_REVISION_BMSK                   0xf
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_REMOTE_CAP_STANDARD_PROTOCOL_ADAPTER_REVISION_SHFT                     0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_STATUS_STANDARD_ADDR                                          (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x40)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_STATUS_STANDARD_PHYS                                          (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x40)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_STATUS_STANDARD_OFFS                                          (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x40)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_STATUS_STANDARD_RMSK                                               0xf07
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_STATUS_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_STATUS_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_STATUS_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_STATUS_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_STATUS_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_STATUS_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_STATUS_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_STATUS_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_STATUS_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_STATUS_STANDARD_LINK_RATE_BMSK                                     0xf00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_STATUS_STANDARD_LINK_RATE_SHFT                                         8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_STATUS_STANDARD_LANE_COUNT_BMSK                                      0x7
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_STATUS_STANDARD_LANE_COUNT_SHFT                                        0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_ADDR                                      (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE            + 0x44)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_PHYS                                      (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_PHYS + 0x44)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_OFFS                                      (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_CAP_REG_BASE_OFFS + 0x44)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_RMSK                                      0xaf40ffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_DPRX_CAPABILITIES_READ_DONE_BMSK          0x80000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_DPRX_CAPABILITIES_READ_DONE_SHFT                  31
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_DSC_NOT_SUPPORTED_BMSK                    0x20000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_DSC_NOT_SUPPORTED_SHFT                            29
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_LTTPR_NOT_SUPPORTED_BMSK                   0x8000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_LTTPR_NOT_SUPPORTED_SHFT                          27
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_SECONDARY_SPLIT_CAPABILITY_BMSK            0x4000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_SECONDARY_SPLIT_CAPABILITY_SHFT                   26
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_FEC_NOT_SUPPORTED_BMSK                     0x2000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_FEC_NOT_SUPPORTED_SHFT                            25
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_TPS4_CAPABILITY_BMSK                       0x1000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_TPS4_CAPABILITY_SHFT                              24
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_TPS3_CAPABILITY_BMSK                        0x400000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_TPS3_CAPABILITY_SHFT                              22
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_MST_CAPABILITY_BMSK                           0x8000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_MST_CAPABILITY_SHFT                               15
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_MAXIMAL_LANE_COUNT_BMSK                       0x7000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_MAXIMAL_LANE_COUNT_SHFT                           12
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_MAXIMAL_LINK_RATE_BMSK                         0xf00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_MAXIMAL_LINK_RATE_SHFT                             8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_MAXIMAL_DPCD_REV_BMSK                           0xf0
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_MAXIMAL_DPCD_REV_SHFT                              4
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_PROTOCOL_ADAPTER_REVISION_BMSK                   0xf
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_DP_COMMON_CAP_STANDARD_PROTOCOL_ADAPTER_REVISION_SHFT                     0

/*----------------------------------------------------------------------------
 * MODULE: USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT
 *--------------------------------------------------------------------------*/

#define USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE                                                 (USB4_HOST_ROUTER_1USB4_WRAPPER_BASE            + 0x00006400)
#define USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_SIZE                                            0xc00
#define USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_USED                                            0x414
#define USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS                                            (USB4_HOST_ROUTER_1USB4_WRAPPER_BASE_PHYS + 0x00006400)
#define USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS                                            0x00006400

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_ADDR                                  (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x40)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_PHYS                                  (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x40)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_OFFS                                  (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x40)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_RMSK                                  0x80ffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_V_BMSK                                0x80000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_V_SHFT                                        31
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_PATH_CREDITS_ALLOCATED_BMSK             0xfe0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_PATH_CREDITS_ALLOCATED_SHFT                   17
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_OUTPUT_PORT_BMSK                         0x1f800
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_OUTPUT_PORT_SHFT                              11
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_OUTPUT_HOPID_BMSK                          0x7ff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_AUX_STANDARD_OUTPUT_HOPID_SHFT                              0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ADDR                                  (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x44)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_PHYS                                  (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x44)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_OFFS                                  (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x44)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_RMSK                                  0x1ffff7ff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_PP_BMSK                               0x10000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_PP_SHFT                                       28
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ESE_BMSK                               0x8000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ESE_SHFT                                      27
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ISE_BMSK                               0x4000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_ISE_SHFT                                      26
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_EFC_BMSK                               0x2000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_EFC_SHFT                                      25
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_IFC_BMSK                               0x1000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_IFC_SHFT                                      24
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_CE_BMSK                                 0x800000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_CE_SHFT                                       23
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_COUNTER_ID_BMSK                         0x7ff000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_COUNTER_ID_SHFT                               12
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_PRIORITY_BMSK                              0x700
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_PRIORITY_SHFT                                  8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_WEIGHT_BMSK                                 0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_AUX_STANDARD_WEIGHT_SHFT                                    0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_ADDR                                 (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x48)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_PHYS                                 (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x48)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_OFFS                                 (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x48)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_RMSK                                 0x80ffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_V_BMSK                               0x80000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_V_SHFT                                       31
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_PATH_CREDITS_ALLOCATED_BMSK            0xfe0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_PATH_CREDITS_ALLOCATED_SHFT                  17
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_OUTPUT_PORT_BMSK                        0x1f800
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_OUTPUT_PORT_SHFT                             11
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_OUTPUT_HOPID_BMSK                         0x7ff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_0_MAIN_STANDARD_OUTPUT_HOPID_SHFT                             0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ADDR                                 (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x4c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_PHYS                                 (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x4c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_OFFS                                 (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x4c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_RMSK                                 0x1ffff7ff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_PP_BMSK                              0x10000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_PP_SHFT                                      28
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ESE_BMSK                              0x8000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ESE_SHFT                                     27
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ISE_BMSK                              0x4000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_ISE_SHFT                                     26
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_EFC_BMSK                              0x2000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_EFC_SHFT                                     25
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_IFC_BMSK                              0x1000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_IFC_SHFT                                     24
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_CE_BMSK                                0x800000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_CE_SHFT                                      23
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_COUNTER_ID_BMSK                        0x7ff000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_COUNTER_ID_SHFT                              12
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_PRIORITY_BMSK                             0x700
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_PRIORITY_SHFT                                 8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_WEIGHT_BMSK                                0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PATH_CS_1_MAIN_STANDARD_WEIGHT_SHFT                                   0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_AUX_STANDARD_ADDR                                   (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x400)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_AUX_STANDARD_PHYS                                   (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x400)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_AUX_STANDARD_OFFS                                   (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x400)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_AUX_STANDARD_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_AUX_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_AUX_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_AUX_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_AUX_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_AUX_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_AUX_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_AUX_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_AUX_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_AUX_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_AUX_STANDARD_RECEIVED_PACKETS_LOW_BMSK              0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_AUX_STANDARD_RECEIVED_PACKETS_LOW_SHFT                       0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_AUX_STANDARD_ADDR                                   (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x404)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_AUX_STANDARD_PHYS                                   (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x404)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_AUX_STANDARD_OFFS                                   (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x404)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_AUX_STANDARD_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_AUX_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_AUX_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_AUX_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_AUX_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_AUX_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_AUX_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_AUX_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_AUX_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_AUX_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_AUX_STANDARD_RECEIVED_PACKETS_HIGH_BMSK             0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_AUX_STANDARD_RECEIVED_PACKETS_HIGH_SHFT                      0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_AUX_STANDARD_ADDR                                   (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x408)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_AUX_STANDARD_PHYS                                   (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x408)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_AUX_STANDARD_OFFS                                   (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x408)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_AUX_STANDARD_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_AUX_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_AUX_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_AUX_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_AUX_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_AUX_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_AUX_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_AUX_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_AUX_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_AUX_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_AUX_STANDARD_DROPPED_PACKETS_BMSK                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_AUX_STANDARD_DROPPED_PACKETS_SHFT                            0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_1_STANDARD_ADDR                                     (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x40c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_1_STANDARD_PHYS                                     (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x40c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_1_STANDARD_OFFS                                     (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x40c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_1_STANDARD_RMSK                                     0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_1_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_1_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_1_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_1_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_1_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_1_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_1_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_1_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_1_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_1_STANDARD_RECEIVED_PACKETS_LOW_BMSK                0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_0_1_STANDARD_RECEIVED_PACKETS_LOW_SHFT                         0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_1_STANDARD_ADDR                                     (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x410)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_1_STANDARD_PHYS                                     (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x410)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_1_STANDARD_OFFS                                     (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x410)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_1_STANDARD_RMSK                                     0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_1_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_1_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_1_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_1_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_1_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_1_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_1_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_1_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_1_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_1_STANDARD_RECEIVED_PACKETS_HIGH_BMSK               0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_1_1_STANDARD_RECEIVED_PACKETS_HIGH_SHFT                        0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_1_STANDARD_ADDR                                     (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE            + 0x414)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_1_STANDARD_PHYS                                     (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_PHYS + 0x414)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_1_STANDARD_OFFS                                     (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_REG_BASE_OFFS + 0x414)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_1_STANDARD_RMSK                                     0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_1_STANDARD_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_1_STANDARD_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_1_STANDARD_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_1_STANDARD_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_1_STANDARD_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_1_STANDARD_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_1_STANDARD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_1_STANDARD_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_1_STANDARD_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_1_STANDARD_DROPPED_PACKETS_BMSK                     0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CNT_CS_2_1_STANDARD_DROPPED_PACKETS_SHFT                              0

/*----------------------------------------------------------------------------
 * MODULE: USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP
 *--------------------------------------------------------------------------*/

#define USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE                                           (USB4_HOST_ROUTER_1USB4_WRAPPER_BASE            + 0x0000f000)
#define USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_SIZE                                      0x1000
#define USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_USED                                      0x228
#define USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS                                      (USB4_HOST_ROUTER_1USB4_WRAPPER_BASE_PHYS + 0x0000f000)
#define USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS                                      0x0000f000

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_ADDR                                         (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x0)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_PHYS                                         (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x0)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_OFFS                                         (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x0)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_RMSK                                         0xffffff01
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_PDF_BMSK                                     0xf0000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_PDF_SHFT                                             28
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_SUPPID_BMSK                                   0x8000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_SUPPID_SHFT                                          27
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_HOPID_BMSK                                    0x7ff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_HOPID_SHFT                                           16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_LENGTH_BMSK                                      0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_LENGTH_SHFT                                           8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_TRIGGER_BMSK                                        0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_HDR_TRIGGER_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_ADDR                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x4)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_PHYS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x4)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_OFFS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x4)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_BYTE3_BMSK                             0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_BYTE3_SHFT                                     24
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_BYTE2_BMSK                               0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_BYTE2_SHFT                                     16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_BYTE1_BMSK                                 0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_BYTE1_SHFT                                      8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_BYTE0_BMSK                                   0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_0_BYTE0_SHFT                                      0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_ADDR                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x8)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_PHYS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x8)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_OFFS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x8)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_BYTE7_BMSK                             0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_BYTE7_SHFT                                     24
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_BYTE6_BMSK                               0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_BYTE6_SHFT                                     16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_BYTE5_BMSK                                 0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_BYTE5_SHFT                                      8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_BYTE4_BMSK                                   0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_1_BYTE4_SHFT                                      0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_ADDR                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0xc)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_PHYS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0xc)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_OFFS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0xc)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_BYTE11_BMSK                            0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_BYTE11_SHFT                                    24
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_BYTE10_BMSK                              0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_BYTE10_SHFT                                    16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_BYTE9_BMSK                                 0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_BYTE9_SHFT                                      8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_BYTE8_BMSK                                   0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_2_BYTE8_SHFT                                      0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_ADDR                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x10)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_PHYS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x10)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_OFFS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x10)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_BYTE15_BMSK                            0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_BYTE15_SHFT                                    24
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_BYTE14_BMSK                              0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_BYTE14_SHFT                                    16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_BYTE13_BMSK                                0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_BYTE13_SHFT                                     8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_BYTE12_BMSK                                  0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_3_BYTE12_SHFT                                     0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_ADDR                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x14)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_PHYS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x14)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_OFFS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x14)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_BYTE19_BMSK                            0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_BYTE19_SHFT                                    24
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_BYTE18_BMSK                              0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_BYTE18_SHFT                                    16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_BYTE17_BMSK                                0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_BYTE17_SHFT                                     8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_BYTE16_BMSK                                  0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TX_PAYLOAD_4_BYTE16_SHFT                                     0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_ADDR                                         (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x20)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_PHYS                                         (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x20)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_OFFS                                         (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x20)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_RMSK                                         0xffffff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_PDF_BMSK                                     0xf0000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_PDF_SHFT                                             28
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_SUPPID_BMSK                                   0x8000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_SUPPID_SHFT                                          27
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_HOPID_BMSK                                    0x7ff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_HOPID_SHFT                                           16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_LENGTH_BMSK                                      0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_HDR_LENGTH_SHFT                                           8

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_ADDR                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x24)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_PHYS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x24)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_OFFS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x24)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_BYTE3_BMSK                             0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_BYTE3_SHFT                                     24
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_BYTE2_BMSK                               0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_BYTE2_SHFT                                     16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_BYTE1_BMSK                                 0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_BYTE1_SHFT                                      8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_BYTE0_BMSK                                   0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_0_BYTE0_SHFT                                      0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_ADDR                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x28)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_PHYS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x28)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_OFFS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x28)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_BYTE7_BMSK                             0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_BYTE7_SHFT                                     24
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_BYTE6_BMSK                               0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_BYTE6_SHFT                                     16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_BYTE5_BMSK                                 0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_BYTE5_SHFT                                      8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_BYTE4_BMSK                                   0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_1_BYTE4_SHFT                                      0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_ADDR                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x2c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_PHYS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x2c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_OFFS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x2c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_BYTE11_BMSK                            0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_BYTE11_SHFT                                    24
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_BYTE10_BMSK                              0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_BYTE10_SHFT                                    16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_BYTE9_BMSK                                 0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_BYTE9_SHFT                                      8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_BYTE8_BMSK                                   0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_2_BYTE8_SHFT                                      0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_ADDR                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x30)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_PHYS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x30)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_OFFS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x30)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_BYTE15_BMSK                            0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_BYTE15_SHFT                                    24
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_BYTE14_BMSK                              0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_BYTE14_SHFT                                    16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_BYTE13_BMSK                                0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_BYTE13_SHFT                                     8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_BYTE12_BMSK                                  0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_3_BYTE12_SHFT                                     0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_ADDR                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x34)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_PHYS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x34)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_OFFS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x34)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_BYTE19_BMSK                            0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_BYTE19_SHFT                                    24
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_BYTE18_BMSK                              0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_BYTE18_SHFT                                    16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_BYTE17_BMSK                                0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_BYTE17_SHFT                                     8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_BYTE16_BMSK                                  0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_PAYLOAD_4_BYTE16_SHFT                                     0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_ADDR                                         (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x38)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_PHYS                                         (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x38)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_OFFS                                         (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x38)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_RMSK                                         0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_CRC_TOKEN_BMSK                               0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_CRC_TOKEN_SHFT                                        0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUFFER_CLR_ADDR                                  (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x3c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUFFER_CLR_PHYS                                  (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x3c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUFFER_CLR_OFFS                                  (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x3c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUFFER_CLR_RMSK                                         0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUFFER_CLR_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUFFER_CLR_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUFFER_CLR_BUFFER_CLR_BMSK                              0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUFFER_CLR_BUFFER_CLR_SHFT                                0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_ADDR                                      (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x40)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_PHYS                                      (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x40)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_OFFS                                      (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x40)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_RMSK                                         0x700ff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_IGNORE_ACK_ECC_ERR_BMSK                      0x40000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_IGNORE_ACK_ECC_ERR_SHFT                           18
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_GRAN_SEL_BMSK                                0x30000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_GRAN_SEL_SHFT                                     16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_ACK_TIMEOUT_BMSK                                0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_TIMER_CFG_ACK_TIMEOUT_SHFT                                   0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_ADDR                                         (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x44)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_PHYS                                         (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x44)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_OFFS                                         (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x44)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_RMSK                                         0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_DP_AUX_SW_IRQ_BMSK                           0x80000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_DP_AUX_SW_IRQ_SHFT                                   31
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_DP_AUX_UC_IRQ_BMSK                           0x40000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_DP_AUX_UC_IRQ_SHFT                                   30
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_RX_BUF_CNT_BMSK                              0x3c000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_RX_BUF_CNT_SHFT                                      26
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_AUTO_ACK_DISABLE_BMSK                         0x2000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_AUTO_ACK_DISABLE_SHFT                                25
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UC_MODE_RX_DROP_PKT_BMSK                      0x1000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UC_MODE_RX_DROP_PKT_SHFT                             24
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UC_MODE_TX_DROP_PKT_BMSK                       0x800000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UC_MODE_TX_DROP_PKT_SHFT                             23
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UC_MODE_RX_ACK_BMSK                            0x400000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UC_MODE_RX_ACK_SHFT                                  22
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UC_MODE_TX_ACK_BMSK                            0x200000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UC_MODE_TX_ACK_SHFT                                  21
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UC_MODE_RX_ACTIVE_BMSK                         0x100000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UC_MODE_RX_ACTIVE_SHFT                               20
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UC_MODE_TX_ACTIVE_BMSK                          0x80000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UC_MODE_TX_ACTIVE_SHFT                               19
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UC_MODE_RX_ENABLE_BMSK                          0x40000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UC_MODE_RX_ENABLE_SHFT                               18
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UC_MODE_TX_ENABLE_BMSK                          0x20000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UC_MODE_TX_ENABLE_SHFT                               17
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_TX_TIMER_ACTIVE_BMSK                            0x10000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_TX_TIMER_ACTIVE_SHFT                                 16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UNCORRECT_ERROR_BMSK                             0x8000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_UNCORRECT_ERROR_SHFT                                 15
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_RX_HPD_CLR_PEND_BMSK                             0x4000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_RX_HPD_CLR_PEND_SHFT                                 14
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_RX_HPD_SET_PEND_BMSK                             0x2000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_RX_HPD_SET_PEND_SHFT                                 13
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_RX_START_PG_RX_BMSK                              0x1000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_RX_START_PG_RX_SHFT                                  12
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_TX_GEN_ACK_PEND_BMSK                              0x800
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_TX_GEN_ACK_PEND_SHFT                                 11
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_TX_START_BMSK                                     0x400
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_TX_START_SHFT                                        10
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_RX_BUFFER_FULL_BMSK                               0x200
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_RX_BUFFER_FULL_SHFT                                   9
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_RX_ENABLE_BMSK                                    0x100
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_RX_ENABLE_SHFT                                        8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_RX_FSM_STATE_BMSK                                  0xf0
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_RX_FSM_STATE_SHFT                                     4
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_TX_ENABLE_BMSK                                      0x8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_TX_ENABLE_SHFT                                        3
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_TX_FSM_STATE_BMSK                                   0x7
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_STATUS_TX_FSM_STATE_SHFT                                     0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_HPD_STATUS_ADDR                                     (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x48)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_HPD_STATUS_PHYS                                     (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x48)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_HPD_STATUS_OFFS                                     (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x48)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_HPD_STATUS_RMSK                                            0x3
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_HPD_STATUS_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_HPD_STATUS_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_HPD_STATUS_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_HPD_STATUS_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_HPD_STATUS_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_HPD_STATUS_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_HPD_STATUS_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_HPD_STATUS_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_HPD_STATUS_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_HPD_STATUS_HPD_STATUS_HW_EN_BMSK                           0x2
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_HPD_STATUS_HPD_STATUS_HW_EN_SHFT                             1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_HPD_STATUS_HPD_STATUS_BMSK                                 0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_HPD_STATUS_HPD_STATUS_SHFT                                   0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_HDR_ADDR                                     (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x50)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_HDR_PHYS                                     (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x50)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_HDR_OFFS                                     (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x50)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_HDR_RMSK                                     0xffffff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_HDR_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_HDR_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_HDR_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_HDR_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_HDR_PDF_BMSK                                 0xf0000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_HDR_PDF_SHFT                                         28
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_HDR_SUPPID_BMSK                               0x8000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_HDR_SUPPID_SHFT                                      27
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_HDR_HOPID_BMSK                                0x7ff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_HDR_HOPID_SHFT                                       16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_HDR_LENGTH_BMSK                                  0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_HDR_LENGTH_SHFT                                       8

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_0_ADDR                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x54)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_0_PHYS                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x54)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_0_OFFS                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x54)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_0_RMSK                               0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_0_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_0_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_0_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_0_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_0_BYTE3_BMSK                         0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_0_BYTE3_SHFT                                 24
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_0_BYTE2_BMSK                           0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_0_BYTE2_SHFT                                 16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_0_BYTE1_BMSK                             0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_0_BYTE1_SHFT                                  8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_0_BYTE0_BMSK                               0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_0_BYTE0_SHFT                                  0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_1_ADDR                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x58)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_1_PHYS                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x58)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_1_OFFS                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x58)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_1_RMSK                               0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_1_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_1_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_1_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_1_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_1_BYTE7_BMSK                         0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_1_BYTE7_SHFT                                 24
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_1_BYTE6_BMSK                           0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_1_BYTE6_SHFT                                 16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_1_BYTE5_BMSK                             0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_1_BYTE5_SHFT                                  8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_1_BYTE4_BMSK                               0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_1_BYTE4_SHFT                                  0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_2_ADDR                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x5c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_2_PHYS                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x5c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_2_OFFS                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x5c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_2_RMSK                               0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_2_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_2_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_2_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_2_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_2_BYTE11_BMSK                        0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_2_BYTE11_SHFT                                24
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_2_BYTE10_BMSK                          0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_2_BYTE10_SHFT                                16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_2_BYTE9_BMSK                             0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_2_BYTE9_SHFT                                  8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_2_BYTE8_BMSK                               0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_2_BYTE8_SHFT                                  0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_3_ADDR                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x60)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_3_PHYS                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x60)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_3_OFFS                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x60)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_3_RMSK                               0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_3_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_3_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_3_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_3_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_3_BYTE15_BMSK                        0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_3_BYTE15_SHFT                                24
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_3_BYTE14_BMSK                          0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_3_BYTE14_SHFT                                16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_3_BYTE13_BMSK                            0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_3_BYTE13_SHFT                                 8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_3_BYTE12_BMSK                              0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_3_BYTE12_SHFT                                 0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_4_ADDR                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x64)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_4_PHYS                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x64)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_4_OFFS                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x64)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_4_RMSK                               0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_4_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_4_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_4_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_4_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_4_BYTE19_BMSK                        0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_4_BYTE19_SHFT                                24
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_4_BYTE18_BMSK                          0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_4_BYTE18_SHFT                                16
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_4_BYTE17_BMSK                            0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_4_BYTE17_SHFT                                 8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_4_BYTE16_BMSK                              0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_BUF_PAYLOAD_4_BYTE16_SHFT                                 0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_ADDR                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x68)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_PHYS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x68)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_OFFS                                   (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x68)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_RMSK                                   0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_NUM_BMSK                               0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_NUM_SHFT                                        0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_CTL_ADDR                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x6c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_CTL_PHYS                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x6c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_CTL_OFFS                               (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x6c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_CTL_RMSK                                      0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_CTL_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_CTL_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_CTL_CLR_BMSK                                  0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_DROPPED_PKTS_CTL_CLR_SHFT                                    0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_ADDR                                      (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x150)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_PHYS                                      (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x150)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_OFFS                                      (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x150)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_RMSK                                           0x7ff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_IRQ_RECEIVED_EN_BMSK                           0x400
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_IRQ_RECEIVED_EN_SHFT                              10
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_HPD_PLUG_RECEIVED_EN_BMSK                      0x200
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_HPD_PLUG_RECEIVED_EN_SHFT                          9
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_HPD_UNPLUG_RECEIVED_EN_BMSK                    0x100
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_HPD_UNPLUG_RECEIVED_EN_SHFT                        8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_ACK_RECEIVED_EN_BMSK                            0x80
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_ACK_RECEIVED_EN_SHFT                               7
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_PATH_TEARDOWN_EN_BMSK                           0x40
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_PATH_TEARDOWN_EN_SHFT                              6
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_BLOCK_TX_ACK_EN_BMSK                            0x20
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_BLOCK_TX_ACK_EN_SHFT                               5
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_RST_ACK_EN_BMSK                                 0x10
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_RST_ACK_EN_SHFT                                    4
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_CLK_SYNC_N_PKTS_EN_BMSK                          0x8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_CLK_SYNC_N_PKTS_EN_SHFT                            3
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_ACK_TIMEOUT_EN_BMSK                              0x4
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_ACK_TIMEOUT_EN_SHFT                                2
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_RX_PKT_RECEIVED_EN_BMSK                          0x2
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_RX_PKT_RECEIVED_EN_SHFT                            1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_TX_PKT_DONE_EN_BMSK                              0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_EN_TX_PKT_DONE_EN_SHFT                                0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_ADDR                                  (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x154)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_PHYS                                  (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x154)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_OFFS                                  (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x154)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_RMSK                                       0x7ff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_IRQ_RECEIVED_IRQ_BMSK                      0x400
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_IRQ_RECEIVED_IRQ_SHFT                         10
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_HPD_PLUG_RECEIVED_IRQ_BMSK                 0x200
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_HPD_PLUG_RECEIVED_IRQ_SHFT                     9
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_HPD_UNPLUG_RECEIVED_IRQ_BMSK               0x100
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_HPD_UNPLUG_RECEIVED_IRQ_SHFT                   8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_ACK_RECEIVED_IRQ_BMSK                       0x80
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_ACK_RECEIVED_IRQ_SHFT                          7
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_PATH_TEARDOWN_IRQ_BMSK                      0x40
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_PATH_TEARDOWN_IRQ_SHFT                         6
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_BLOCK_TX_ACK_IRQ_BMSK                       0x20
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_BLOCK_TX_ACK_IRQ_SHFT                          5
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_RST_ACK_IRQ_BMSK                            0x10
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_RST_ACK_IRQ_SHFT                               4
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_CLK_SYNC_N_PKTS_IRQ_BMSK                     0x8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_CLK_SYNC_N_PKTS_IRQ_SHFT                       3
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_ACK_TIMEOUT_IRQ_BMSK                         0x4
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_ACK_TIMEOUT_IRQ_SHFT                           2
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_RX_PKT_RECEIVED_IRQ_BMSK                     0x2
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_RX_PKT_RECEIVED_IRQ_SHFT                       1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_TX_PKT_DONE_IRQ_BMSK                         0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_STATUS_TX_PKT_DONE_IRQ_SHFT                           0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_ADDR                                     (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x158)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_PHYS                                     (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x158)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_OFFS                                     (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x158)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_RMSK                                          0x7ff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_IRQ_RECEIVED_CLR_BMSK                         0x400
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_IRQ_RECEIVED_CLR_SHFT                            10
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_HPD_PLUG_RECEIVED_CLR_BMSK                    0x200
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_HPD_PLUG_RECEIVED_CLR_SHFT                        9
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_HPD_UNPLUG_RECEIVED_CLR_BMSK                  0x100
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_HPD_UNPLUG_RECEIVED_CLR_SHFT                      8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_ACK_RECEIVED_CLR_BMSK                          0x80
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_ACK_RECEIVED_CLR_SHFT                             7
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_PATH_TEARDOWN_CLR_BMSK                         0x40
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_PATH_TEARDOWN_CLR_SHFT                            6
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_BLOCK_TX_ACK_CLR_BMSK                          0x20
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_BLOCK_TX_ACK_CLR_SHFT                             5
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_RST_ACK_CLR_BMSK                               0x10
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_RST_ACK_CLR_SHFT                                  4
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_CLK_SYNC_N_PKTS_CLR_BMSK                        0x8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_CLK_SYNC_N_PKTS_CLR_SHFT                          3
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_ACK_TIMEOUT_CLR_BMSK                            0x4
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_ACK_TIMEOUT_CLR_SHFT                              2
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_RX_PKT_RECEIVED_CLR_BMSK                        0x2
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_RX_PKT_RECEIVED_CLR_SHFT                          1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_TX_PKT_DONE_CLR_BMSK                            0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_SW_INT_CLR_TX_PKT_DONE_CLR_SHFT                              0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_CALC_ADDR                                    (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x15c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_CALC_PHYS                                    (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x15c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_CALC_OFFS                                    (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x15c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_CALC_RMSK                                    0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_CALC_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_CALC_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_CALC_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_CALC_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_CALC_CRC_CALC_BMSK                           0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_RX_CRC_CALC_CRC_CALC_SHFT                                    0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_ADDR                                    (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x200)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_PHYS                                    (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x200)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_OFFS                                    (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x200)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_RMSK                                          0x1f
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_AUTO_ACK_DISABLE_BMSK                         0x10
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_AUTO_ACK_DISABLE_SHFT                            4
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_UC_MODE_RX_ACTIVE_BMSK                         0x8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_UC_MODE_RX_ACTIVE_SHFT                           3
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_UC_MODE_TX_ACTIVE_BMSK                         0x4
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_UC_MODE_TX_ACTIVE_SHFT                           2
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_UC_MODE_RX_ENABLE_BMSK                         0x2
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_UC_MODE_RX_ENABLE_SHFT                           1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_UC_MODE_TX_ENABLE_BMSK                         0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CFG_UC_MODE_TX_ENABLE_SHFT                           0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_ADDR                                    (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x204)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_PHYS                                    (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x204)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_OFFS                                    (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x204)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_RMSK                                          0x1f
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_UNCORRECTABLE_ERROR_BMSK                      0x10
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_UNCORRECTABLE_ERROR_SHFT                         4
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_UC_MODE_RX_DROP_PKT_BMSK                       0x8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_UC_MODE_RX_DROP_PKT_SHFT                         3
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_UC_MODE_RX_ACK_BMSK                            0x4
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_UC_MODE_RX_ACK_SHFT                              2
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_UC_MODE_TX_DROP_PKT_BMSK                       0x2
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_UC_MODE_TX_DROP_PKT_SHFT                         1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_UC_MODE_TX_ACK_BMSK                            0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_MODE_CTL_UC_MODE_TX_ACK_SHFT                              0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_ADDR                                      (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x220)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_PHYS                                      (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x220)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_OFFS                                      (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x220)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_RMSK                                          0x1fff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_UC_MODE_RX_PKT_PEND_EN_BMSK                   0x1000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_UC_MODE_RX_PKT_PEND_EN_SHFT                       12
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_UC_MODE_TX_PKT_PEND_EN_BMSK                    0x800
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_UC_MODE_TX_PKT_PEND_EN_SHFT                       11
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_IRQ_RECEIVED_EN_BMSK                           0x400
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_IRQ_RECEIVED_EN_SHFT                              10
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_HPD_PLUG_RECEIVED_EN_BMSK                      0x200
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_HPD_PLUG_RECEIVED_EN_SHFT                          9
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_HPD_UNPLUG_RECEIVED_EN_BMSK                    0x100
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_HPD_UNPLUG_RECEIVED_EN_SHFT                        8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_ACK_RECEIVED_EN_BMSK                            0x80
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_ACK_RECEIVED_EN_SHFT                               7
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_PATH_TEARDOWN_EN_BMSK                           0x40
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_PATH_TEARDOWN_EN_SHFT                              6
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_BLOCK_TX_ACK_EN_BMSK                            0x20
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_BLOCK_TX_ACK_EN_SHFT                               5
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_RST_ACK_EN_BMSK                                 0x10
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_RST_ACK_EN_SHFT                                    4
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_CLK_SYNC_N_PKTS_EN_BMSK                          0x8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_CLK_SYNC_N_PKTS_EN_SHFT                            3
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_ACK_TIMEOUT_EN_BMSK                              0x4
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_ACK_TIMEOUT_EN_SHFT                                2
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_RX_PKT_RECEIVED_EN_BMSK                          0x2
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_RX_PKT_RECEIVED_EN_SHFT                            1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_TX_PKT_DONE_EN_BMSK                              0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_EN_TX_PKT_DONE_EN_SHFT                                0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_ADDR                                  (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x224)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_PHYS                                  (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x224)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_OFFS                                  (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x224)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_RMSK                                      0x1fff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_UC_MODE_RX_PKT_PEND_IRQ_BMSK              0x1000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_UC_MODE_RX_PKT_PEND_IRQ_SHFT                  12
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_UC_MODE_TX_PKT_PEND_IRQ_BMSK               0x800
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_UC_MODE_TX_PKT_PEND_IRQ_SHFT                  11
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_IRQ_RECEIVED_IRQ_BMSK                      0x400
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_IRQ_RECEIVED_IRQ_SHFT                         10
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_HPD_PLUG_RECEIVED_IRQ_BMSK                 0x200
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_HPD_PLUG_RECEIVED_IRQ_SHFT                     9
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_HPD_UNPLUG_RECEIVED_IRQ_BMSK               0x100
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_HPD_UNPLUG_RECEIVED_IRQ_SHFT                   8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_ACK_RECEIVED_IRQ_BMSK                       0x80
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_ACK_RECEIVED_IRQ_SHFT                          7
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_PATH_TEARDOWN_IRQ_BMSK                      0x40
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_PATH_TEARDOWN_IRQ_SHFT                         6
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_BLOCK_TX_ACK_IRQ_BMSK                       0x20
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_BLOCK_TX_ACK_IRQ_SHFT                          5
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_RST_ACK_IRQ_BMSK                            0x10
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_RST_ACK_IRQ_SHFT                               4
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_CLK_SYNC_N_PKTS_IRQ_BMSK                     0x8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_CLK_SYNC_N_PKTS_IRQ_SHFT                       3
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_ACK_TIMEOUT_IRQ_BMSK                         0x4
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_ACK_TIMEOUT_IRQ_SHFT                           2
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_RX_PKT_RECEIVED_IRQ_BMSK                     0x2
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_RX_PKT_RECEIVED_IRQ_SHFT                       1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_TX_PKT_DONE_IRQ_BMSK                         0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_STATUS_TX_PKT_DONE_IRQ_SHFT                           0

#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_ADDR                                     (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE            + 0x228)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_PHYS                                     (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_PHYS + 0x228)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_OFFS                                     (USB4_HOST_ROUTER_1DP_IN_AP_AUX_PROP_REG_BASE_OFFS + 0x228)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_RMSK                                         0x1fff
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_UC_MODE_RX_PKT_PEND_CLR_BMSK                 0x1000
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_UC_MODE_RX_PKT_PEND_CLR_SHFT                     12
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_UC_MODE_TX_PKT_PEND_CLR_BMSK                  0x800
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_UC_MODE_TX_PKT_PEND_CLR_SHFT                     11
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_IRQ_RECEIVED_CLR_BMSK                         0x400
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_IRQ_RECEIVED_CLR_SHFT                            10
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_HPD_PLUG_RECEIVED_CLR_BMSK                    0x200
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_HPD_PLUG_RECEIVED_CLR_SHFT                        9
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_HPD_UNPLUG_RECEIVED_CLR_BMSK                  0x100
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_HPD_UNPLUG_RECEIVED_CLR_SHFT                      8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_ACK_RECEIVED_CLR_BMSK                          0x80
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_ACK_RECEIVED_CLR_SHFT                             7
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_PATH_TEARDOWN_CLR_BMSK                         0x40
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_PATH_TEARDOWN_CLR_SHFT                            6
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_BLOCK_TX_ACK_CLR_BMSK                          0x20
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_BLOCK_TX_ACK_CLR_SHFT                             5
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_RST_ACK_CLR_BMSK                               0x10
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_RST_ACK_CLR_SHFT                                  4
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_CLK_SYNC_N_PKTS_CLR_BMSK                        0x8
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_CLK_SYNC_N_PKTS_CLR_SHFT                          3
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_ACK_TIMEOUT_CLR_BMSK                            0x4
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_ACK_TIMEOUT_CLR_SHFT                              2
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_RX_PKT_RECEIVED_CLR_BMSK                        0x2
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_RX_PKT_RECEIVED_CLR_SHFT                          1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_TX_PKT_DONE_CLR_BMSK                            0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DP_AUX_UC_INT_CLR_TX_PKT_DONE_CLR_SHFT                              0

/*----------------------------------------------------------------------------
 * MODULE: USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP
 *--------------------------------------------------------------------------*/

#define USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE                                    (USB4_HOST_ROUTER_1USB4_WRAPPER_BASE            + 0x00010000)
#define USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_SIZE                               0x1000
#define USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_USED                               0x54
#define USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS                               (USB4_HOST_ROUTER_1USB4_WRAPPER_BASE_PHYS + 0x00010000)
#define USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS                               0x00010000

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_SIZE_ADDR                                 (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x0)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_SIZE_PHYS                                 (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x0)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_SIZE_OFFS                                 (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x0)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_SIZE_RMSK                                       0x3f
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_SIZE_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_SIZE_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_SIZE_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_SIZE_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_SIZE_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_SIZE_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_SIZE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_SIZE_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_SIZE_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_SIZE_ALOC_SIZE_BMSK                             0x3f
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_SIZE_ALOC_SIZE_SHFT                                0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_STREAM_ADDR                               (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x4)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_STREAM_PHYS                               (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x4)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_STREAM_OFFS                               (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x4)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_STREAM_RMSK                                      0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_STREAM_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_STREAM_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_STREAM_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_STREAM_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_STREAM_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_STREAM_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_STREAM_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_STREAM_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_STREAM_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_STREAM_MST_NSST_BMSK                             0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STREAM_CFG_STREAM_MST_NSST_SHFT                               0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_BAUD_CFG_ADDR                                        (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x8)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_BAUD_CFG_PHYS                                        (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x8)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_BAUD_CFG_OFFS                                        (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x8)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_BAUD_CFG_RMSK                                               0x7
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_BAUD_CFG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_BAUD_CFG_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_BAUD_CFG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_BAUD_CFG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_BAUD_CFG_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_BAUD_CFG_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_BAUD_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_BAUD_CFG_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_BAUD_CFG_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_BAUD_CFG_RATE_BMSK                                          0x7
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_BAUD_CFG_RATE_SHFT                                            0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CTRL_ADDR                                            (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0xc)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CTRL_PHYS                                            (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0xc)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CTRL_OFFS                                            (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0xc)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CTRL_RMSK                                                   0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CTRL_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CTRL_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CTRL_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CTRL_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CTRL_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CTRL_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CTRL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CTRL_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CTRL_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CTRL_ARM_EN_BMSK                                            0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CTRL_ARM_EN_SHFT                                              0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_ADDR                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x10)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_PHYS                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x10)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_OFFS                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x10)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_RMSK                                    0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_C3_BMSK                                 0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_C3_SHFT                                         24
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_C2_BMSK                                   0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_C2_SHFT                                         16
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_C1_BMSK                                     0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_C1_SHFT                                          8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_C0_BMSK                                       0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_0_C0_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_ADDR                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x14)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_PHYS                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x14)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_OFFS                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x14)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_RMSK                                    0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_C7_BMSK                                 0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_C7_SHFT                                         24
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_C6_BMSK                                   0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_C6_SHFT                                         16
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_C5_BMSK                                     0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_C5_SHFT                                          8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_C4_BMSK                                       0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_1_C4_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_ADDR                                  (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x18)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_PHYS                                  (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x18)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_OFFS                                  (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x18)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_RMSK                                  0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_ACT3_BMSK                             0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_ACT3_SHFT                                     24
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_ACT2_BMSK                               0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_ACT2_SHFT                                     16
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_ACT1_BMSK                                 0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_ACT1_SHFT                                      8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_ACT0_BMSK                                   0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_ACT_ACT0_SHFT                                      0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_ADDR                                 (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x1c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_PHYS                                 (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x1c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_OFFS                                 (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x1c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_RMSK                                 0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_VCPF3_BMSK                           0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_VCPF3_SHFT                                   24
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_VCPF2_BMSK                             0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_VCPF2_SHFT                                   16
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_VCPF1_BMSK                               0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_VCPF1_SHFT                                    8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_VCPF0_BMSK                                 0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_K_CODE_VCPF_VCPF0_SHFT                                    0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_K_CODE_SR_ADDR                                       (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x20)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_K_CODE_SR_PHYS                                       (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x20)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_K_CODE_SR_OFFS                                       (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x20)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_K_CODE_SR_RMSK                                           0xffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_K_CODE_SR_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_K_CODE_SR_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_K_CODE_SR_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_K_CODE_SR_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_K_CODE_SR_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_K_CODE_SR_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_K_CODE_SR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_K_CODE_SR_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_K_CODE_SR_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_K_CODE_SR_SST_SR_BMSK                                    0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_K_CODE_SR_SST_SR_SHFT                                         8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_K_CODE_SR_MST_SR_BMSK                                      0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_K_CODE_SR_MST_SR_SHFT                                         0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_ADDR                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x24)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_PHYS                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x24)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_OFFS                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x24)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_RMSK                                      0xffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_BF_BMSK                                   0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_BF_SHFT                                         16
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_BS_BMSK                                     0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_BS_SHFT                                          8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_BE_BMSK                                       0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_0_BE_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_ADDR                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x28)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_PHYS                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x28)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_OFFS                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x28)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_RMSK                                      0xffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_CP_BMSK                                   0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_CP_SHFT                                         16
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_FEC_CP_BMSK                                 0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_FEC_CP_SHFT                                      8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_EOC_BMSK                                      0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_1_EOC_SHFT                                         0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_ADDR                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x2c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_PHYS                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x2c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_OFFS                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x2c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_RMSK                                    0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_SS_BMSK                                 0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_SS_SHFT                                         24
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_FE_BMSK                                   0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_FE_SHFT                                         16
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_SE_BMSK                                     0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_SE_SHFT                                          8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_FS_BMSK                                       0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_K_CODE_2_FS_SHFT                                          0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_ADDR                                      (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x30)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_PHYS                                      (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x30)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_OFFS                                      (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x30)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_RMSK                                      0xffffffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_PH_BMSK                                   0xff000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_PH_SHFT                                           24
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_PM_BMSK                                     0xff0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_PM_SHFT                                           16
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_DEC_EN_BMSK                                   0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_DEC_EN_SHFT                                        8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_DEC_DIS_BMSK                                    0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_FEC_K_CODE_DEC_DIS_SHFT                                       0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_CFG_ADDR                                         (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x34)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_CFG_PHYS                                         (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x34)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_CFG_OFFS                                         (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x34)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_CFG_RMSK                                             0xffff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_CFG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_CFG_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_CFG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_CFG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_CFG_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_CFG_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_CFG_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_CFG_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_CFG_MAX_BYTES_PER_USB4_PKT_BMSK                      0xff00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_CFG_MAX_BYTES_PER_USB4_PKT_SHFT                           8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_CFG_MAX_TUS_PER_USB4_PKT_BMSK                          0xff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_MST_CFG_MAX_TUS_PER_USB4_PKT_SHFT                             0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PKT_CFG_SST_ADDR                                     (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x40)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PKT_CFG_SST_PHYS                                     (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x40)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PKT_CFG_SST_OFFS                                     (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x40)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PKT_CFG_SST_RMSK                                         0x3fff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PKT_CFG_SST_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PKT_CFG_SST_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PKT_CFG_SST_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PKT_CFG_SST_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PKT_CFG_SST_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PKT_CFG_SST_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PKT_CFG_SST_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PKT_CFG_SST_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PKT_CFG_SST_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PKT_CFG_SST_SST_MAX_TUS_PER_USB4_PKT_BMSK                0x3e00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PKT_CFG_SST_SST_MAX_TUS_PER_USB4_PKT_SHFT                     9
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PKT_CFG_SST_SST_MAX_BYTES_PER_USB4_PKT_BMSK               0x1ff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_PKT_CFG_SST_SST_MAX_BYTES_PER_USB4_PKT_SHFT                   0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_ADDR                                             (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x44)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_PHYS                                             (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x44)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_OFFS                                             (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x44)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_RMSK                                                    0x7
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_BLOCK_TX_QUIET_BMSK                                     0x4
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_BLOCK_TX_QUIET_SHFT                                       2
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_BLOCK_TX_ACK_BMSK                                       0x2
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_BLOCK_TX_ACK_SHFT                                         1
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_BLOCK_TX_BMSK                                           0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_RST_BLOCK_TX_SHFT                                             0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CLK_SYNC_CFG_ADDR                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x48)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CLK_SYNC_CFG_PHYS                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x48)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CLK_SYNC_CFG_OFFS                                    (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x48)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CLK_SYNC_CFG_RMSK                                           0xf
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CLK_SYNC_CFG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CLK_SYNC_CFG_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CLK_SYNC_CFG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CLK_SYNC_CFG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CLK_SYNC_CFG_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CLK_SYNC_CFG_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CLK_SYNC_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CLK_SYNC_CFG_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CLK_SYNC_CFG_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CLK_SYNC_CFG_NUM_PKTS_TO_INT_BMSK                           0xf
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_CLK_SYNC_CFG_NUM_PKTS_TO_INT_SHFT                             0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ABS_PRIORITY_CFG_ADDR                                (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x4c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ABS_PRIORITY_CFG_PHYS                                (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x4c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ABS_PRIORITY_CFG_OFFS                                (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x4c)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ABS_PRIORITY_CFG_RMSK                                    0x1f1f
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ABS_PRIORITY_CFG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ABS_PRIORITY_CFG_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ABS_PRIORITY_CFG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ABS_PRIORITY_CFG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ABS_PRIORITY_CFG_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ABS_PRIORITY_CFG_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ABS_PRIORITY_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ABS_PRIORITY_CFG_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ABS_PRIORITY_CFG_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ABS_PRIORITY_CFG_CLR_ABS_PRI_THRESH_BMSK                 0x1f00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ABS_PRIORITY_CFG_CLR_ABS_PRI_THRESH_SHFT                      8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ABS_PRIORITY_CFG_SET_ABS_PRI_THRESH_BMSK                   0x1f
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_ABS_PRIORITY_CFG_SET_ABS_PRI_THRESH_SHFT                      0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_ADDR                                      (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x50)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_PHYS                                      (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x50)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_OFFS                                      (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x50)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_RMSK                                      0x7f7f7f7f
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_SST_MAX_BYTES_PER_SDP_TU_4L_BMSK          0x7f000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_SST_MAX_BYTES_PER_SDP_TU_4L_SHFT                  24
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_SST_MAX_BYTES_PER_SDP_TU_2L_BMSK            0x7f0000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_SST_MAX_BYTES_PER_SDP_TU_2L_SHFT                  16
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_SST_MAX_BYTES_PER_SDP_TU_1L_BMSK              0x7f00
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_SST_MAX_BYTES_PER_SDP_TU_1L_SHFT                   8
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_SST_MAX_BYTES_PER_VID_TU_BMSK                   0x7f
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_SST_TU_CFG_SST_MAX_BYTES_PER_VID_TU_SHFT                      0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STATE_FIFOS_ADDR                                     (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE            + 0x54)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STATE_FIFOS_PHYS                                     (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_PHYS + 0x54)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STATE_FIFOS_OFFS                                     (USB4_HOST_ROUTER_1DP_IN_0_ADAPTER_PORT_PROP_REG_BASE_OFFS + 0x54)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STATE_FIFOS_RMSK                                         0x7fff
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STATE_FIFOS_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STATE_FIFOS_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STATE_FIFOS_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STATE_FIFOS_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STATE_FIFOS_SST_TU_IN_FIFO_MAX_CNT_BMSK                  0x7800
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STATE_FIFOS_SST_TU_IN_FIFO_MAX_CNT_SHFT                      11
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STATE_FIFOS_BP_FIFO_MAX_CNT_BMSK                          0x7c0
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STATE_FIFOS_BP_FIFO_MAX_CNT_SHFT                              6
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STATE_FIFOS_EGRESS_FIFO_MAX_CNT_BMSK                       0x3f
#define HWIO_USB4_HOST_ROUTER_1USB4_DPINAP_STATE_FIFOS_EGRESS_FIFO_MAX_CNT_SHFT                          0

/*----------------------------------------------------------------------------
 * MODULE: USB4_HOST_ROUTER_1DPAP_CONFIG_PROP
 *--------------------------------------------------------------------------*/

#define USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE                                             (USB4_HOST_ROUTER_1USB4_WRAPPER_BASE            + 0x00084000)
#define USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE_SIZE                                        0x1000
#define USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE_USED                                        0x10
#define USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE_PHYS                                        (USB4_HOST_ROUTER_1USB4_WRAPPER_BASE_PHYS + 0x00084000)
#define USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE_OFFS                                        0x00084000

#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_ADDR                                       (USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE            + 0x0)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_PHYS                                       (USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE_PHYS + 0x0)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_OFFS                                       (USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE_OFFS + 0x0)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_RMSK                                              0x7
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_DP_PCLK_SYS_CLK_SELECTED_BMSK                     0x4
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_DP_PCLK_SYS_CLK_SELECTED_SHFT                       2
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_DP_PCLK_MAX_PCLK_SELECTED_BMSK                    0x2
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_DP_PCLK_MAX_PCLK_SELECTED_SHFT                      1
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_DP_PCLK_SEL_BMSK                                  0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_PCLK_DP_PCLK_SEL_SHFT                                    0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_SYS_CLK_RESET_ADDR                                 (USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE            + 0x4)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_SYS_CLK_RESET_PHYS                                 (USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE_PHYS + 0x4)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_SYS_CLK_RESET_OFFS                                 (USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE_OFFS + 0x4)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_SYS_CLK_RESET_RMSK                                        0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_SYS_CLK_RESET_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_SYS_CLK_RESET_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_SYS_CLK_RESET_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_SYS_CLK_RESET_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_SYS_CLK_RESET_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_SYS_CLK_RESET_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_SYS_CLK_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_SYS_CLK_RESET_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_SYS_CLK_RESET_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_SYS_CLK_RESET_SYS_CLK_SYNC_RST_DP_BMSK                    0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_SYS_CLK_RESET_SYS_CLK_SYNC_RST_DP_SHFT                      0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_ADDR                                  (USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE            + 0x8)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_PHYS                                  (USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE_PHYS + 0x8)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_OFFS                                  (USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE_OFFS + 0x8)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_RMSK                                  0xe0000007
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_DP_SW_RST_ACK_ANDED_BMSK              0x80000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_DP_SW_RST_ACK_ANDED_SHFT                      31
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_DP_SW_RST_ACK_MX_DOMAIN_BMSK          0x40000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_DP_SW_RST_ACK_MX_DOMAIN_SHFT                  30
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_DP_SW_RST_ACK_MAX_PCLK_BMSK           0x20000000
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_DP_SW_RST_ACK_MAX_PCLK_SHFT                   29
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_DP_AUX_RST_BMSK                              0x4
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_DP_AUX_RST_SHFT                                2
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_DP_AP_CS_RST_BMSK                            0x2
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_DP_AP_CS_RST_SHFT                              1
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_DP_SW_RST_BMSK                               0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_CLK_RESET_DP_SW_RST_SHFT                                 0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_TUNNEL_MODE_ADDR                                (USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE            + 0xc)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_TUNNEL_MODE_PHYS                                (USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE_PHYS + 0xc)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_TUNNEL_MODE_OFFS                                (USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE_OFFS + 0xc)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_TUNNEL_MODE_RMSK                                       0x3
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_TUNNEL_MODE_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_TUNNEL_MODE_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_TUNNEL_MODE_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_TUNNEL_MODE_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_TUNNEL_MODE_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_TUNNEL_MODE_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_TUNNEL_MODE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_TUNNEL_MODE_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_TUNNEL_MODE_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_TUNNEL_MODE_DP_TBT3_MODE_EN_BMSK                       0x2
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_TUNNEL_MODE_DP_TBT3_MODE_EN_SHFT                         1
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_TUNNEL_MODE_DP_ENTERPRIZE_TNL_EN_BMSK                  0x1
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_DP_TUNNEL_MODE_DP_ENTERPRIZE_TNL_EN_SHFT                    0

#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_USB4_LINK_CFG_ADDR                                 (USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE            + 0x10)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_USB4_LINK_CFG_PHYS                                 (USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE_PHYS + 0x10)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_USB4_LINK_CFG_OFFS                                 (USB4_HOST_ROUTER_1DPAP_CONFIG_PROP_REG_BASE_OFFS + 0x10)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_USB4_LINK_CFG_RMSK                                        0xf
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_USB4_LINK_CFG_IN                    \
                in_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_USB4_LINK_CFG_ADDR)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_USB4_LINK_CFG_INM(m)            \
                in_dword_masked(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_USB4_LINK_CFG_ADDR, m)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_USB4_LINK_CFG_OUT(v)            \
                out_dword(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_USB4_LINK_CFG_ADDR,v)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_USB4_LINK_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_USB4_LINK_CFG_ADDR,m,v,HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_USB4_LINK_CFG_IN)
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_USB4_LINK_CFG_LINK_RATE_BMSK                              0xf
#define HWIO_USB4_HOST_ROUTER_1USB4_DPAP_CFG_USB4_LINK_CFG_LINK_RATE_SHFT                                0


#endif /* __HAL_DP_IN_AP_HWIO_H__ */
