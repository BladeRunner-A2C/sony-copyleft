#ifndef __GPU_CLK_HWIO_H__
#define __GPU_CLK_HWIO_H__
/*
===========================================================================
*/
/**
    @file gpu_clk_hwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8450 (Waipio) [waipio_v1.0_p3q3r17.2_MTO_POST_SI]
 
    This file contains HWIO register definitions for the following modules:
        GPUCC_GPU_CC_GPU_CC_GPU_CC_REG

    'Include' filters applied: GPUCC_GPU_CC_GX_BCR[GPUCC_GPU_CC_GPU_CC_GPU_CC_REG] GPUCC_GPU_CC_GX_DOMAIN_MISC[GPUCC_GPU_CC_GPU_CC_GPU_CC_REG] GPUCC_GPU_CC_GX_GDSCR[GPUCC_GPU_CC_GPU_CC_GPU_CC_REG] GPUCC_GPU_CC_ACD_MISC[GPUCC_GPU_CC_GPU_CC_GPU_CC_REG] GPUCC_GPU_CC_ACD_BCR[GPUCC_GPU_CC_GPU_CC_GPU_CC_REG] 

    Generation parameters: 
    { 'filename': 'gpu_clk_hwio.h',
      'module-filter-exclude': {},
      'module-filter-include': { 'GPUCC_GPU_CC_GPU_CC_GPU_CC_REG': [ 'GPUCC_GPU_CC_GX_BCR',
                                                                     'GPUCC_GPU_CC_GX_DOMAIN_MISC',
                                                                     'GPUCC_GPU_CC_GX_GDSCR',
                                                                     'GPUCC_GPU_CC_ACD_MISC',
                                                                     'GPUCC_GPU_CC_ACD_BCR']},
      'modules': ['GPUCC_GPU_CC_GPU_CC_GPU_CC_REG'],
      'output-fvals': True,
      'output-offsets': True,
      'rmsk-input': True}
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

    $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/CPRLib/image/core/inc/gpu_clk_hwio.h#1 $
    $DateTime: 2024/04/02 23:00:31 $
    $Author: cirrusp4svc $

    ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: GPUCC_GPU_CC_GPU_CC_GPU_CC_REG
 *--------------------------------------------------------------------------*/

#define GPUCC_GPU_CC_GPU_CC_GPU_CC_REG_REG_BASE                                             (GFX_BASE            + 0x00094000)
#define GPUCC_GPU_CC_GPU_CC_GPU_CC_REG_REG_BASE_SIZE                                        0x5800
#define GPUCC_GPU_CC_GPU_CC_GPU_CC_REG_REG_BASE_USED                                        0x55c0
#define GPUCC_GPU_CC_GPU_CC_GPU_CC_REG_REG_BASE_OFFS                                        0x00094000

#define HWIO_GPUCC_GPU_CC_GX_BCR_ADDR                                                       (GPUCC_GPU_CC_GPU_CC_GPU_CC_REG_REG_BASE            + 0x5058)
#define HWIO_GPUCC_GPU_CC_GX_BCR_OFFS                                                       (GPUCC_GPU_CC_GPU_CC_GPU_CC_REG_REG_BASE_OFFS + 0x5058)
#define HWIO_GPUCC_GPU_CC_GX_BCR_RMSK                                                              0x1
#define HWIO_GPUCC_GPU_CC_GX_BCR_IN                    \
                in_dword_masked(HWIO_GPUCC_GPU_CC_GX_BCR_ADDR, HWIO_GPUCC_GPU_CC_GX_BCR_RMSK)
#define HWIO_GPUCC_GPU_CC_GX_BCR_INM(m)            \
                in_dword_masked(HWIO_GPUCC_GPU_CC_GX_BCR_ADDR, m)
#define HWIO_GPUCC_GPU_CC_GX_BCR_OUT(v)            \
                out_dword(HWIO_GPUCC_GPU_CC_GX_BCR_ADDR,v)
#define HWIO_GPUCC_GPU_CC_GX_BCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GPUCC_GPU_CC_GX_BCR_ADDR,m,v,HWIO_GPUCC_GPU_CC_GX_BCR_IN)
#define HWIO_GPUCC_GPU_CC_GX_BCR_BLK_ARES_BMSK                                                     0x1
#define HWIO_GPUCC_GPU_CC_GX_BCR_BLK_ARES_SHFT                                                       0
#define HWIO_GPUCC_GPU_CC_GX_BCR_BLK_ARES_DISABLE_FVAL                                             0x0
#define HWIO_GPUCC_GPU_CC_GX_BCR_BLK_ARES_ENABLE_FVAL                                              0x1

#define HWIO_GPUCC_GPU_CC_GX_GDSCR_ADDR                                                     (GPUCC_GPU_CC_GPU_CC_GPU_CC_REG_REG_BASE            + 0x505c)
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_OFFS                                                     (GPUCC_GPU_CC_GPU_CC_GPU_CC_REG_REG_BASE_OFFS + 0x505c)
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_RMSK                                                     0xf8ffffff
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_IN                    \
                in_dword_masked(HWIO_GPUCC_GPU_CC_GX_GDSCR_ADDR, HWIO_GPUCC_GPU_CC_GX_GDSCR_RMSK)
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_INM(m)            \
                in_dword_masked(HWIO_GPUCC_GPU_CC_GX_GDSCR_ADDR, m)
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_OUT(v)            \
                out_dword(HWIO_GPUCC_GPU_CC_GX_GDSCR_ADDR,v)
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GPUCC_GPU_CC_GX_GDSCR_ADDR,m,v,HWIO_GPUCC_GPU_CC_GX_GDSCR_IN)
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_PWR_ON_BMSK                                              0x80000000
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_PWR_ON_SHFT                                                      31
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_GDSC_STATE_BMSK                                          0x78000000
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_GDSC_STATE_SHFT                                                  27
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_EN_REST_WAIT_BMSK                                          0xf00000
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_EN_REST_WAIT_SHFT                                                20
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_EN_FEW_WAIT_BMSK                                            0xf0000
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_EN_FEW_WAIT_SHFT                                                 16
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_CLK_DIS_WAIT_BMSK                                            0xf000
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_CLK_DIS_WAIT_SHFT                                                12
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_RETAIN_FF_ENABLE_BMSK                                         0x800
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_RETAIN_FF_ENABLE_SHFT                                            11
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_RETAIN_FF_ENABLE_DISABLE_FVAL                                   0x0
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_RETAIN_FF_ENABLE_ENABLE_FVAL                                    0x1
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_RESTORE_BMSK                                                  0x400
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_RESTORE_SHFT                                                     10
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_RESTORE_DISABLE_FVAL                                            0x0
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_RESTORE_ENABLE_FVAL                                             0x1
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_SAVE_BMSK                                                     0x200
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_SAVE_SHFT                                                         9
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_SAVE_DISABLE_FVAL                                               0x0
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_SAVE_ENABLE_FVAL                                                0x1
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_RETAIN_BMSK                                                   0x100
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_RETAIN_SHFT                                                       8
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_RETAIN_DISABLE_FVAL                                             0x0
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_RETAIN_ENABLE_FVAL                                              0x1
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_EN_REST_BMSK                                                   0x80
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_EN_REST_SHFT                                                      7
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_EN_REST_DISABLE_FVAL                                            0x0
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_EN_REST_ENABLE_FVAL                                             0x1
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_EN_FEW_BMSK                                                    0x40
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_EN_FEW_SHFT                                                       6
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_EN_FEW_DISABLE_FVAL                                             0x0
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_EN_FEW_ENABLE_FVAL                                              0x1
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_CLAMP_IO_BMSK                                                  0x20
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_CLAMP_IO_SHFT                                                     5
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_CLAMP_IO_DISABLE_FVAL                                           0x0
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_CLAMP_IO_ENABLE_FVAL                                            0x1
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_CLK_DISABLE_BMSK                                               0x10
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_CLK_DISABLE_SHFT                                                  4
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_CLK_DISABLE_CLK_NOT_DISABLE_FVAL                                0x0
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_CLK_DISABLE_CLK_IS_DISABLE_FVAL                                 0x1
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_PD_ARES_BMSK                                                    0x8
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_PD_ARES_SHFT                                                      3
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_PD_ARES_NO_RESET_FVAL                                           0x0
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_PD_ARES_RESET_FVAL                                              0x1
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_SW_OVERRIDE_BMSK                                                0x4
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_SW_OVERRIDE_SHFT                                                  2
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_SW_OVERRIDE_DISABLE_FVAL                                        0x0
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_SW_OVERRIDE_ENABLE_FVAL                                         0x1
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_HW_CONTROL_BMSK                                                 0x2
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_HW_CONTROL_SHFT                                                   1
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_HW_CONTROL_DISABLE_FVAL                                         0x0
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_HW_CONTROL_ENABLE_FVAL                                          0x1
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_SW_COLLAPSE_BMSK                                                0x1
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_SW_COLLAPSE_SHFT                                                  0
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_SW_COLLAPSE_DISABLE_FVAL                                        0x0
#define HWIO_GPUCC_GPU_CC_GX_GDSCR_SW_COLLAPSE_ENABLE_FVAL                                         0x1

#define HWIO_GPUCC_GPU_CC_ACD_BCR_ADDR                                                      (GPUCC_GPU_CC_GPU_CC_GPU_CC_REG_REG_BASE            + 0x5358)
#define HWIO_GPUCC_GPU_CC_ACD_BCR_OFFS                                                      (GPUCC_GPU_CC_GPU_CC_GPU_CC_REG_REG_BASE_OFFS + 0x5358)
#define HWIO_GPUCC_GPU_CC_ACD_BCR_RMSK                                                             0x1
#define HWIO_GPUCC_GPU_CC_ACD_BCR_IN                    \
                in_dword_masked(HWIO_GPUCC_GPU_CC_ACD_BCR_ADDR, HWIO_GPUCC_GPU_CC_ACD_BCR_RMSK)
#define HWIO_GPUCC_GPU_CC_ACD_BCR_INM(m)            \
                in_dword_masked(HWIO_GPUCC_GPU_CC_ACD_BCR_ADDR, m)
#define HWIO_GPUCC_GPU_CC_ACD_BCR_OUT(v)            \
                out_dword(HWIO_GPUCC_GPU_CC_ACD_BCR_ADDR,v)
#define HWIO_GPUCC_GPU_CC_ACD_BCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GPUCC_GPU_CC_ACD_BCR_ADDR,m,v,HWIO_GPUCC_GPU_CC_ACD_BCR_IN)
#define HWIO_GPUCC_GPU_CC_ACD_BCR_BLK_ARES_BMSK                                                    0x1
#define HWIO_GPUCC_GPU_CC_ACD_BCR_BLK_ARES_SHFT                                                      0
#define HWIO_GPUCC_GPU_CC_ACD_BCR_BLK_ARES_DISABLE_FVAL                                            0x0
#define HWIO_GPUCC_GPU_CC_ACD_BCR_BLK_ARES_ENABLE_FVAL                                             0x1

#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_ADDR                                              (GPUCC_GPU_CC_GPU_CC_GPU_CC_REG_REG_BASE            + 0x5504)
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_OFFS                                              (GPUCC_GPU_CC_GPU_CC_GPU_CC_REG_REG_BASE_OFFS + 0x5504)
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_RMSK                                                0x3c0011
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_IN                    \
                in_dword_masked(HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_ADDR, HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_RMSK)
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_INM(m)            \
                in_dword_masked(HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_ADDR, m)
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_OUT(v)            \
                out_dword(HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_ADDR,v)
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_ADDR,m,v,HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_IN)
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_RAC_ENR_STATUS_BMSK                                 0x200000
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_RAC_ENR_STATUS_SHFT                                       21
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_RAC_ENF_STATUS_BMSK                                 0x100000
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_RAC_ENF_STATUS_SHFT                                       20
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_SPTP_ENR_STATUS_BMSK                                 0x80000
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_SPTP_ENR_STATUS_SHFT                                      19
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_SPTP_ENF_STATUS_BMSK                                 0x40000
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_SPTP_ENF_STATUS_SHFT                                      18
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_GPU_GX_RAIL_RESET_BMSK                                  0x10
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_GPU_GX_RAIL_RESET_SHFT                                     4
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_GPU_GX_RAIL_CLAMP_IO_BMSK                                0x1
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC3_GPU_GX_RAIL_CLAMP_IO_SHFT                                  0

#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC4_ADDR                                              (GPUCC_GPU_CC_GPU_CC_GPU_CC_REG_REG_BASE            + 0x5508)
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC4_OFFS                                              (GPUCC_GPU_CC_GPU_CC_GPU_CC_REG_REG_BASE_OFFS + 0x5508)
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC4_RMSK                                                     0x1
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC4_IN                    \
                in_dword_masked(HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC4_ADDR, HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC4_RMSK)
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC4_INM(m)            \
                in_dword_masked(HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC4_ADDR, m)
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC4_OUT(v)            \
                out_dword(HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC4_ADDR,v)
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC4_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC4_ADDR,m,v,HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC4_IN)
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC4_GFX_CLAMP_MEM_BMSK                                       0x1
#define HWIO_GPUCC_GPU_CC_GX_DOMAIN_MISC4_GFX_CLAMP_MEM_SHFT                                         0

#define HWIO_GPUCC_GPU_CC_ACD_MISC_ADDR                                                     (GPUCC_GPU_CC_GPU_CC_GPU_CC_REG_REG_BASE            + 0x558c)
#define HWIO_GPUCC_GPU_CC_ACD_MISC_OFFS                                                     (GPUCC_GPU_CC_GPU_CC_GPU_CC_REG_REG_BASE_OFFS + 0x558c)
#define HWIO_GPUCC_GPU_CC_ACD_MISC_RMSK                                                            0x1
#define HWIO_GPUCC_GPU_CC_ACD_MISC_IN                    \
                in_dword_masked(HWIO_GPUCC_GPU_CC_ACD_MISC_ADDR, HWIO_GPUCC_GPU_CC_ACD_MISC_RMSK)
#define HWIO_GPUCC_GPU_CC_ACD_MISC_INM(m)            \
                in_dword_masked(HWIO_GPUCC_GPU_CC_ACD_MISC_ADDR, m)
#define HWIO_GPUCC_GPU_CC_ACD_MISC_OUT(v)            \
                out_dword(HWIO_GPUCC_GPU_CC_ACD_MISC_ADDR,v)
#define HWIO_GPUCC_GPU_CC_ACD_MISC_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GPUCC_GPU_CC_ACD_MISC_ADDR,m,v,HWIO_GPUCC_GPU_CC_ACD_MISC_IN)
#define HWIO_GPUCC_GPU_CC_ACD_MISC_IROOT_ARES_BMSK                                                 0x1
#define HWIO_GPUCC_GPU_CC_ACD_MISC_IROOT_ARES_SHFT                                                   0


#endif /* __GPU_CLK_HWIO_H__ */
