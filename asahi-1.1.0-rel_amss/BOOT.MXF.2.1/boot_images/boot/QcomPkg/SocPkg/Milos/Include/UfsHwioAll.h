#ifndef UFSHWIOALL_H
#define UFSHWIOALL_H
/*
===========================================================================
*/
/**
    @file UfsHwioAll.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM6xxx (Milos) [milos_v1.0_p3q3r45_MTO]
 
    This file contains HWIO register definitions for the following modules:
        UFS_MEM_UFS
        UFS_MEM_ICE_REGS
        TLMM_REG
        GCC_CLK_CTL_REG
        SLP_CNTR

    'Include' filters applied: UFS_MEM_SHARED_ICE*[UFS_MEM_UFS] UFS_MEM_CAP[UFS_MEM_UFS] UFS_MEM_VER[UFS_MEM_UFS] UFS_MEM_UE*[UFS_MEM_UFS] UFS_MEM_UT*[UFS_MEM_UFS] UFS_MEM_CFG*[UFS_MEM_UFS] UFS_MEM_I*[UFS_MEM_UFS] UFS_MEM_ICE_AES_SHARE_CONTROL[UFS_MEM_ICE_REGS] UFS_MEM_ICE_PARAMETERS_1[UFS_MEM_ICE_REGS] TLMM_UFS_RESET[TLMM_REG] GCC_UFS_PHY_BCR*[GCC_CLK_CTL_REG] 

    Generation parameters: 
    { 'filename': 'UfsHwioAll.h',
      'module-filter-include': { 'GCC_CLK_CTL_REG': ['GCC_UFS_PHY_BCR*'],
                                 'TLMM_REG': ['TLMM_UFS_RESET'],
                                 'UFS_MEM_ICE_REGS': [ 'UFS_MEM_ICE_AES_SHARE_CONTROL',
                                                       'UFS_MEM_ICE_PARAMETERS_1'],
                                 'UFS_MEM_UFS': [ 'UFS_MEM_SHARED_ICE*',
                                                  'UFS_MEM_CAP',
                                                  'UFS_MEM_VER',
                                                  'UFS_MEM_UE*',
                                                  'UFS_MEM_UT*',
                                                  'UFS_MEM_CFG*',
                                                  'UFS_MEM_I*']},
      'modules': [ 'UFS_MEM_UFS',
                   'UFS_MEM_ICE_REGS',
                   'TLMM_REG',
                   'GCC_CLK_CTL_REG',
                   'SLP_CNTR'],
      'output-offsets': True}
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

/*----------------------------------------------------------------------------
 * MODULE: UFS_MEM_UFS
 *--------------------------------------------------------------------------*/

#define UFS_MEM_UFS_REG_BASE                                                         (UFS_MEM_UFS_2LANE_REGS_BASE      + 0x00004000)
#define UFS_MEM_UFS_REG_BASE_SIZE                                                    0x3000
#define UFS_MEM_UFS_REG_BASE_USED                                                    0x2710
#define UFS_MEM_UFS_REG_BASE_OFFS                                                    0x00004000

#define HWIO_UFS_MEM_CAP_ADDR                                                        (UFS_MEM_UFS_REG_BASE      + 0x0)
#define HWIO_UFS_MEM_CAP_OFFS                                                        (UFS_MEM_UFS_REG_BASE_OFFS + 0x0)
#define HWIO_UFS_MEM_CAP_RMSK                                                        0x1787ff1f
#define HWIO_UFS_MEM_CAP_IN                    \
                in_dword(HWIO_UFS_MEM_CAP_ADDR)
#define HWIO_UFS_MEM_CAP_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_CAP_ADDR, m)
#define HWIO_UFS_MEM_CAP_CS_BMSK                                                     0x10000000
#define HWIO_UFS_MEM_CAP_CS_SHFT                                                             28
#define HWIO_UFS_MEM_CAP_UICDMETMS_BMSK                                               0x4000000
#define HWIO_UFS_MEM_CAP_UICDMETMS_SHFT                                                      26
#define HWIO_UFS_MEM_CAP_OODDS_BMSK                                                   0x2000000
#define HWIO_UFS_MEM_CAP_OODDS_SHFT                                                          25
#define HWIO_UFS_MEM_CAP_CAP_64AS_BMSK                                                0x1000000
#define HWIO_UFS_MEM_CAP_CAP_64AS_SHFT                                                       24
#define HWIO_UFS_MEM_CAP_AUTOH8_BMSK                                                   0x800000
#define HWIO_UFS_MEM_CAP_AUTOH8_SHFT                                                         23
#define HWIO_UFS_MEM_CAP_NUTMRS_BMSK                                                    0x70000
#define HWIO_UFS_MEM_CAP_NUTMRS_SHFT                                                         16
#define HWIO_UFS_MEM_CAP_NORTT_BMSK                                                      0xff00
#define HWIO_UFS_MEM_CAP_NORTT_SHFT                                                           8
#define HWIO_UFS_MEM_CAP_NUTRS_BMSK                                                        0x1f
#define HWIO_UFS_MEM_CAP_NUTRS_SHFT                                                           0

#define HWIO_UFS_MEM_VER_ADDR                                                        (UFS_MEM_UFS_REG_BASE      + 0x8)
#define HWIO_UFS_MEM_VER_OFFS                                                        (UFS_MEM_UFS_REG_BASE_OFFS + 0x8)
#define HWIO_UFS_MEM_VER_RMSK                                                            0xffff
#define HWIO_UFS_MEM_VER_IN                    \
                in_dword(HWIO_UFS_MEM_VER_ADDR)
#define HWIO_UFS_MEM_VER_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_VER_ADDR, m)
#define HWIO_UFS_MEM_VER_MJR_BMSK                                                        0xff00
#define HWIO_UFS_MEM_VER_MJR_SHFT                                                             8
#define HWIO_UFS_MEM_VER_MNR_BMSK                                                          0xf0
#define HWIO_UFS_MEM_VER_MNR_SHFT                                                             4
#define HWIO_UFS_MEM_VER_VS_BMSK                                                            0xf
#define HWIO_UFS_MEM_VER_VS_SHFT                                                              0

#define HWIO_UFS_MEM_HCDDID_ADDR                                                     (UFS_MEM_UFS_REG_BASE      + 0x10)
#define HWIO_UFS_MEM_HCDDID_OFFS                                                     (UFS_MEM_UFS_REG_BASE_OFFS + 0x10)
#define HWIO_UFS_MEM_HCDDID_RMSK                                                     0xff00ffff
#define HWIO_UFS_MEM_HCDDID_IN                    \
                in_dword(HWIO_UFS_MEM_HCDDID_ADDR)
#define HWIO_UFS_MEM_HCDDID_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_HCDDID_ADDR, m)
#define HWIO_UFS_MEM_HCDDID_HCDID_BMSK                                               0xff000000
#define HWIO_UFS_MEM_HCDDID_HCDID_SHFT                                                       24
#define HWIO_UFS_MEM_HCDDID_DC_BMSK                                                      0xffff
#define HWIO_UFS_MEM_HCDDID_DC_SHFT                                                           0

#define HWIO_UFS_MEM_HCPMID_ADDR                                                     (UFS_MEM_UFS_REG_BASE      + 0x14)
#define HWIO_UFS_MEM_HCPMID_OFFS                                                     (UFS_MEM_UFS_REG_BASE_OFFS + 0x14)
#define HWIO_UFS_MEM_HCPMID_RMSK                                                     0xffffffff
#define HWIO_UFS_MEM_HCPMID_IN                    \
                in_dword(HWIO_UFS_MEM_HCPMID_ADDR)
#define HWIO_UFS_MEM_HCPMID_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_HCPMID_ADDR, m)
#define HWIO_UFS_MEM_HCPMID_PID_BMSK                                                 0xffff0000
#define HWIO_UFS_MEM_HCPMID_PID_SHFT                                                         16
#define HWIO_UFS_MEM_HCPMID_MID_BMSK                                                     0xffff
#define HWIO_UFS_MEM_HCPMID_MID_SHFT                                                          0

#define HWIO_UFS_MEM_AHIT_ADDR                                                       (UFS_MEM_UFS_REG_BASE      + 0x18)
#define HWIO_UFS_MEM_AHIT_OFFS                                                       (UFS_MEM_UFS_REG_BASE_OFFS + 0x18)
#define HWIO_UFS_MEM_AHIT_RMSK                                                           0x1fff
#define HWIO_UFS_MEM_AHIT_IN                    \
                in_dword(HWIO_UFS_MEM_AHIT_ADDR)
#define HWIO_UFS_MEM_AHIT_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_AHIT_ADDR, m)
#define HWIO_UFS_MEM_AHIT_OUT(v)            \
                out_dword(HWIO_UFS_MEM_AHIT_ADDR,v)
#define HWIO_UFS_MEM_AHIT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_AHIT_ADDR,m,v,HWIO_UFS_MEM_AHIT_IN)
#define HWIO_UFS_MEM_AHIT_TS_BMSK                                                        0x1c00
#define HWIO_UFS_MEM_AHIT_TS_SHFT                                                            10
#define HWIO_UFS_MEM_AHIT_AH8ITV_BMSK                                                     0x3ff
#define HWIO_UFS_MEM_AHIT_AH8ITV_SHFT                                                         0

#define HWIO_UFS_MEM_IS_ADDR                                                         (UFS_MEM_UFS_REG_BASE      + 0x20)
#define HWIO_UFS_MEM_IS_OFFS                                                         (UFS_MEM_UFS_REG_BASE_OFFS + 0x20)
#define HWIO_UFS_MEM_IS_RMSK                                                         0xe0071fff
#define HWIO_UFS_MEM_IS_IN                    \
                in_dword(HWIO_UFS_MEM_IS_ADDR)
#define HWIO_UFS_MEM_IS_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_IS_ADDR, m)
#define HWIO_UFS_MEM_IS_OUT(v)            \
                out_dword(HWIO_UFS_MEM_IS_ADDR,v)
#define HWIO_UFS_MEM_IS_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_IS_ADDR,m,v,HWIO_UFS_MEM_IS_IN)
#define HWIO_UFS_MEM_IS_NOT_USE_31_BMSK                                              0x80000000
#define HWIO_UFS_MEM_IS_NOT_USE_31_SHFT                                                      31
#define HWIO_UFS_MEM_IS_NOT_USE_30_BMSK                                              0x40000000
#define HWIO_UFS_MEM_IS_NOT_USE_30_SHFT                                                      30
#define HWIO_UFS_MEM_IS_NOT_USE_29_BMSK                                              0x20000000
#define HWIO_UFS_MEM_IS_NOT_USE_29_SHFT                                                      29
#define HWIO_UFS_MEM_IS_CEFES_BMSK                                                      0x40000
#define HWIO_UFS_MEM_IS_CEFES_SHFT                                                           18
#define HWIO_UFS_MEM_IS_SBFES_BMSK                                                      0x20000
#define HWIO_UFS_MEM_IS_SBFES_SHFT                                                           17
#define HWIO_UFS_MEM_IS_HCFES_BMSK                                                      0x10000
#define HWIO_UFS_MEM_IS_HCFES_SHFT                                                           16
#define HWIO_UFS_MEM_IS_UTPES_BMSK                                                       0x1000
#define HWIO_UFS_MEM_IS_UTPES_SHFT                                                           12
#define HWIO_UFS_MEM_IS_DFES_BMSK                                                         0x800
#define HWIO_UFS_MEM_IS_DFES_SHFT                                                            11
#define HWIO_UFS_MEM_IS_UCCS_BMSK                                                         0x400
#define HWIO_UFS_MEM_IS_UCCS_SHFT                                                            10
#define HWIO_UFS_MEM_IS_UTMRCS_BMSK                                                       0x200
#define HWIO_UFS_MEM_IS_UTMRCS_SHFT                                                           9
#define HWIO_UFS_MEM_IS_ULSS_BMSK                                                         0x100
#define HWIO_UFS_MEM_IS_ULSS_SHFT                                                             8
#define HWIO_UFS_MEM_IS_ULLS_BMSK                                                          0x80
#define HWIO_UFS_MEM_IS_ULLS_SHFT                                                             7
#define HWIO_UFS_MEM_IS_UHES_BMSK                                                          0x40
#define HWIO_UFS_MEM_IS_UHES_SHFT                                                             6
#define HWIO_UFS_MEM_IS_UHXS_BMSK                                                          0x20
#define HWIO_UFS_MEM_IS_UHXS_SHFT                                                             5
#define HWIO_UFS_MEM_IS_UPMS_BMSK                                                          0x10
#define HWIO_UFS_MEM_IS_UPMS_SHFT                                                             4
#define HWIO_UFS_MEM_IS_UTMS_BMSK                                                           0x8
#define HWIO_UFS_MEM_IS_UTMS_SHFT                                                             3
#define HWIO_UFS_MEM_IS_UE_BMSK                                                             0x4
#define HWIO_UFS_MEM_IS_UE_SHFT                                                               2
#define HWIO_UFS_MEM_IS_UDEPRI_BMSK                                                         0x2
#define HWIO_UFS_MEM_IS_UDEPRI_SHFT                                                           1
#define HWIO_UFS_MEM_IS_UTRCS_BMSK                                                          0x1
#define HWIO_UFS_MEM_IS_UTRCS_SHFT                                                            0

#define HWIO_UFS_MEM_IE_ADDR                                                         (UFS_MEM_UFS_REG_BASE      + 0x24)
#define HWIO_UFS_MEM_IE_OFFS                                                         (UFS_MEM_UFS_REG_BASE_OFFS + 0x24)
#define HWIO_UFS_MEM_IE_RMSK                                                         0xe0071fff
#define HWIO_UFS_MEM_IE_IN                    \
                in_dword(HWIO_UFS_MEM_IE_ADDR)
#define HWIO_UFS_MEM_IE_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_IE_ADDR, m)
#define HWIO_UFS_MEM_IE_OUT(v)            \
                out_dword(HWIO_UFS_MEM_IE_ADDR,v)
#define HWIO_UFS_MEM_IE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_IE_ADDR,m,v,HWIO_UFS_MEM_IE_IN)
#define HWIO_UFS_MEM_IE_NOT_USE_31_BMSK                                              0x80000000
#define HWIO_UFS_MEM_IE_NOT_USE_31_SHFT                                                      31
#define HWIO_UFS_MEM_IE_NOT_USE_30_BMSK                                              0x40000000
#define HWIO_UFS_MEM_IE_NOT_USE_30_SHFT                                                      30
#define HWIO_UFS_MEM_IE_NOT_USE_29_BMSK                                              0x20000000
#define HWIO_UFS_MEM_IE_NOT_USE_29_SHFT                                                      29
#define HWIO_UFS_MEM_IE_CEFEE_BMSK                                                      0x40000
#define HWIO_UFS_MEM_IE_CEFEE_SHFT                                                           18
#define HWIO_UFS_MEM_IE_SBFEE_BMSK                                                      0x20000
#define HWIO_UFS_MEM_IE_SBFEE_SHFT                                                           17
#define HWIO_UFS_MEM_IE_HCFEE_BMSK                                                      0x10000
#define HWIO_UFS_MEM_IE_HCFEE_SHFT                                                           16
#define HWIO_UFS_MEM_IE_UTPEE_BMSK                                                       0x1000
#define HWIO_UFS_MEM_IE_UTPEE_SHFT                                                           12
#define HWIO_UFS_MEM_IE_DFEE_BMSK                                                         0x800
#define HWIO_UFS_MEM_IE_DFEE_SHFT                                                            11
#define HWIO_UFS_MEM_IE_UCCE_BMSK                                                         0x400
#define HWIO_UFS_MEM_IE_UCCE_SHFT                                                            10
#define HWIO_UFS_MEM_IE_UTMRCE_BMSK                                                       0x200
#define HWIO_UFS_MEM_IE_UTMRCE_SHFT                                                           9
#define HWIO_UFS_MEM_IE_ULSSE_BMSK                                                        0x100
#define HWIO_UFS_MEM_IE_ULSSE_SHFT                                                            8
#define HWIO_UFS_MEM_IE_ULLSE_BMSK                                                         0x80
#define HWIO_UFS_MEM_IE_ULLSE_SHFT                                                            7
#define HWIO_UFS_MEM_IE_UHESE_BMSK                                                         0x40
#define HWIO_UFS_MEM_IE_UHESE_SHFT                                                            6
#define HWIO_UFS_MEM_IE_UHXSE_BMSK                                                         0x20
#define HWIO_UFS_MEM_IE_UHXSE_SHFT                                                            5
#define HWIO_UFS_MEM_IE_UPMSE_BMSK                                                         0x10
#define HWIO_UFS_MEM_IE_UPMSE_SHFT                                                            4
#define HWIO_UFS_MEM_IE_UTMSE_BMSK                                                          0x8
#define HWIO_UFS_MEM_IE_UTMSE_SHFT                                                            3
#define HWIO_UFS_MEM_IE_UEE_BMSK                                                            0x4
#define HWIO_UFS_MEM_IE_UEE_SHFT                                                              2
#define HWIO_UFS_MEM_IE_UDEPRIE_BMSK                                                        0x2
#define HWIO_UFS_MEM_IE_UDEPRIE_SHFT                                                          1
#define HWIO_UFS_MEM_IE_UTRCE_BMSK                                                          0x1
#define HWIO_UFS_MEM_IE_UTRCE_SHFT                                                            0

#define HWIO_UFS_MEM_HCS_ADDR                                                        (UFS_MEM_UFS_REG_BASE      + 0x30)
#define HWIO_UFS_MEM_HCS_OFFS                                                        (UFS_MEM_UFS_REG_BASE_OFFS + 0x30)
#define HWIO_UFS_MEM_HCS_RMSK                                                        0xfffff70f
#define HWIO_UFS_MEM_HCS_IN                    \
                in_dword(HWIO_UFS_MEM_HCS_ADDR)
#define HWIO_UFS_MEM_HCS_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_HCS_ADDR, m)
#define HWIO_UFS_MEM_HCS_TLUNUTPE_BMSK                                               0xff000000
#define HWIO_UFS_MEM_HCS_TLUNUTPE_SHFT                                                       24
#define HWIO_UFS_MEM_HCS_TTAGUTPE_BMSK                                                 0xff0000
#define HWIO_UFS_MEM_HCS_TTAGUTPE_SHFT                                                       16
#define HWIO_UFS_MEM_HCS_UTPEC_BMSK                                                      0xf000
#define HWIO_UFS_MEM_HCS_UTPEC_SHFT                                                          12
#define HWIO_UFS_MEM_HCS_UPMCRS_BMSK                                                      0x700
#define HWIO_UFS_MEM_HCS_UPMCRS_SHFT                                                          8
#define HWIO_UFS_MEM_HCS_UCRDY_BMSK                                                         0x8
#define HWIO_UFS_MEM_HCS_UCRDY_SHFT                                                           3
#define HWIO_UFS_MEM_HCS_UTMRLRDY_BMSK                                                      0x4
#define HWIO_UFS_MEM_HCS_UTMRLRDY_SHFT                                                        2
#define HWIO_UFS_MEM_HCS_UTRLRDY_BMSK                                                       0x2
#define HWIO_UFS_MEM_HCS_UTRLRDY_SHFT                                                         1
#define HWIO_UFS_MEM_HCS_DP_BMSK                                                            0x1
#define HWIO_UFS_MEM_HCS_DP_SHFT                                                              0

#define HWIO_UFS_MEM_HCE_ADDR                                                        (UFS_MEM_UFS_REG_BASE      + 0x34)
#define HWIO_UFS_MEM_HCE_OFFS                                                        (UFS_MEM_UFS_REG_BASE_OFFS + 0x34)
#define HWIO_UFS_MEM_HCE_RMSK                                                               0x3
#define HWIO_UFS_MEM_HCE_IN                    \
                in_dword(HWIO_UFS_MEM_HCE_ADDR)
#define HWIO_UFS_MEM_HCE_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_HCE_ADDR, m)
#define HWIO_UFS_MEM_HCE_OUT(v)            \
                out_dword(HWIO_UFS_MEM_HCE_ADDR,v)
#define HWIO_UFS_MEM_HCE_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_HCE_ADDR,m,v,HWIO_UFS_MEM_HCE_IN)
#define HWIO_UFS_MEM_HCE_CGE_BMSK                                                           0x2
#define HWIO_UFS_MEM_HCE_CGE_SHFT                                                             1
#define HWIO_UFS_MEM_HCE_HCE_BMSK                                                           0x1
#define HWIO_UFS_MEM_HCE_HCE_SHFT                                                             0

#define HWIO_UFS_MEM_UECPA_ADDR                                                      (UFS_MEM_UFS_REG_BASE      + 0x38)
#define HWIO_UFS_MEM_UECPA_OFFS                                                      (UFS_MEM_UFS_REG_BASE_OFFS + 0x38)
#define HWIO_UFS_MEM_UECPA_RMSK                                                      0xc000001f
#define HWIO_UFS_MEM_UECPA_IN                    \
                in_dword(HWIO_UFS_MEM_UECPA_ADDR)
#define HWIO_UFS_MEM_UECPA_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UECPA_ADDR, m)
#define HWIO_UFS_MEM_UECPA_ERR_BMSK                                                  0x80000000
#define HWIO_UFS_MEM_UECPA_ERR_SHFT                                                          31
#define HWIO_UFS_MEM_UECPA_VS_ERR_BMSK                                               0x40000000
#define HWIO_UFS_MEM_UECPA_VS_ERR_SHFT                                                       30
#define HWIO_UFS_MEM_UECPA_EC_BMSK                                                         0x1f
#define HWIO_UFS_MEM_UECPA_EC_SHFT                                                            0

#define HWIO_UFS_MEM_UECDL_ADDR                                                      (UFS_MEM_UFS_REG_BASE      + 0x3c)
#define HWIO_UFS_MEM_UECDL_OFFS                                                      (UFS_MEM_UFS_REG_BASE_OFFS + 0x3c)
#define HWIO_UFS_MEM_UECDL_RMSK                                                      0x8000ffff
#define HWIO_UFS_MEM_UECDL_IN                    \
                in_dword(HWIO_UFS_MEM_UECDL_ADDR)
#define HWIO_UFS_MEM_UECDL_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UECDL_ADDR, m)
#define HWIO_UFS_MEM_UECDL_ERR_BMSK                                                  0x80000000
#define HWIO_UFS_MEM_UECDL_ERR_SHFT                                                          31
#define HWIO_UFS_MEM_UECDL_EC_BMSK                                                       0xffff
#define HWIO_UFS_MEM_UECDL_EC_SHFT                                                            0

#define HWIO_UFS_MEM_UECN_ADDR                                                       (UFS_MEM_UFS_REG_BASE      + 0x40)
#define HWIO_UFS_MEM_UECN_OFFS                                                       (UFS_MEM_UFS_REG_BASE_OFFS + 0x40)
#define HWIO_UFS_MEM_UECN_RMSK                                                       0x80000007
#define HWIO_UFS_MEM_UECN_IN                    \
                in_dword(HWIO_UFS_MEM_UECN_ADDR)
#define HWIO_UFS_MEM_UECN_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UECN_ADDR, m)
#define HWIO_UFS_MEM_UECN_ERR_BMSK                                                   0x80000000
#define HWIO_UFS_MEM_UECN_ERR_SHFT                                                           31
#define HWIO_UFS_MEM_UECN_EC_BMSK                                                           0x7
#define HWIO_UFS_MEM_UECN_EC_SHFT                                                             0

#define HWIO_UFS_MEM_UECT_ADDR                                                       (UFS_MEM_UFS_REG_BASE      + 0x44)
#define HWIO_UFS_MEM_UECT_OFFS                                                       (UFS_MEM_UFS_REG_BASE_OFFS + 0x44)
#define HWIO_UFS_MEM_UECT_RMSK                                                       0x8000007f
#define HWIO_UFS_MEM_UECT_IN                    \
                in_dword(HWIO_UFS_MEM_UECT_ADDR)
#define HWIO_UFS_MEM_UECT_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UECT_ADDR, m)
#define HWIO_UFS_MEM_UECT_ERR_BMSK                                                   0x80000000
#define HWIO_UFS_MEM_UECT_ERR_SHFT                                                           31
#define HWIO_UFS_MEM_UECT_EC_BMSK                                                          0x7f
#define HWIO_UFS_MEM_UECT_EC_SHFT                                                             0

#define HWIO_UFS_MEM_UECDME_ADDR                                                     (UFS_MEM_UFS_REG_BASE      + 0x48)
#define HWIO_UFS_MEM_UECDME_OFFS                                                     (UFS_MEM_UFS_REG_BASE_OFFS + 0x48)
#define HWIO_UFS_MEM_UECDME_RMSK                                                     0x8000000f
#define HWIO_UFS_MEM_UECDME_IN                    \
                in_dword(HWIO_UFS_MEM_UECDME_ADDR)
#define HWIO_UFS_MEM_UECDME_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UECDME_ADDR, m)
#define HWIO_UFS_MEM_UECDME_ERR_BMSK                                                 0x80000000
#define HWIO_UFS_MEM_UECDME_ERR_SHFT                                                         31
#define HWIO_UFS_MEM_UECDME_EC_BMSK                                                         0xf
#define HWIO_UFS_MEM_UECDME_EC_SHFT                                                           0

#define HWIO_UFS_MEM_UTRIACR_ADDR                                                    (UFS_MEM_UFS_REG_BASE      + 0x4c)
#define HWIO_UFS_MEM_UTRIACR_OFFS                                                    (UFS_MEM_UFS_REG_BASE_OFFS + 0x4c)
#define HWIO_UFS_MEM_UTRIACR_RMSK                                                    0x81111fff
#define HWIO_UFS_MEM_UTRIACR_IN                    \
                in_dword(HWIO_UFS_MEM_UTRIACR_ADDR)
#define HWIO_UFS_MEM_UTRIACR_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UTRIACR_ADDR, m)
#define HWIO_UFS_MEM_UTRIACR_OUT(v)            \
                out_dword(HWIO_UFS_MEM_UTRIACR_ADDR,v)
#define HWIO_UFS_MEM_UTRIACR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_UTRIACR_ADDR,m,v,HWIO_UFS_MEM_UTRIACR_IN)
#define HWIO_UFS_MEM_UTRIACR_IAEN_BMSK                                               0x80000000
#define HWIO_UFS_MEM_UTRIACR_IAEN_SHFT                                                       31
#define HWIO_UFS_MEM_UTRIACR_IAPWEN_BMSK                                              0x1000000
#define HWIO_UFS_MEM_UTRIACR_IAPWEN_SHFT                                                     24
#define HWIO_UFS_MEM_UTRIACR_IASB_BMSK                                                 0x100000
#define HWIO_UFS_MEM_UTRIACR_IASB_SHFT                                                       20
#define HWIO_UFS_MEM_UTRIACR_CTR_BMSK                                                   0x10000
#define HWIO_UFS_MEM_UTRIACR_CTR_SHFT                                                        16
#define HWIO_UFS_MEM_UTRIACR_IACTH_BMSK                                                  0x1f00
#define HWIO_UFS_MEM_UTRIACR_IACTH_SHFT                                                       8
#define HWIO_UFS_MEM_UTRIACR_IATOVAL_BMSK                                                  0xff
#define HWIO_UFS_MEM_UTRIACR_IATOVAL_SHFT                                                     0

#define HWIO_UFS_MEM_UTRLBA_ADDR                                                     (UFS_MEM_UFS_REG_BASE      + 0x50)
#define HWIO_UFS_MEM_UTRLBA_OFFS                                                     (UFS_MEM_UFS_REG_BASE_OFFS + 0x50)
#define HWIO_UFS_MEM_UTRLBA_RMSK                                                     0xfffffc00
#define HWIO_UFS_MEM_UTRLBA_IN                    \
                in_dword(HWIO_UFS_MEM_UTRLBA_ADDR)
#define HWIO_UFS_MEM_UTRLBA_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UTRLBA_ADDR, m)
#define HWIO_UFS_MEM_UTRLBA_OUT(v)            \
                out_dword(HWIO_UFS_MEM_UTRLBA_ADDR,v)
#define HWIO_UFS_MEM_UTRLBA_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_UTRLBA_ADDR,m,v,HWIO_UFS_MEM_UTRLBA_IN)
#define HWIO_UFS_MEM_UTRLBA_UTRLBA_BMSK                                              0xfffffc00
#define HWIO_UFS_MEM_UTRLBA_UTRLBA_SHFT                                                      10

#define HWIO_UFS_MEM_UTRLBAU_ADDR                                                    (UFS_MEM_UFS_REG_BASE      + 0x54)
#define HWIO_UFS_MEM_UTRLBAU_OFFS                                                    (UFS_MEM_UFS_REG_BASE_OFFS + 0x54)
#define HWIO_UFS_MEM_UTRLBAU_RMSK                                                    0xffffffff
#define HWIO_UFS_MEM_UTRLBAU_IN                    \
                in_dword(HWIO_UFS_MEM_UTRLBAU_ADDR)
#define HWIO_UFS_MEM_UTRLBAU_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UTRLBAU_ADDR, m)
#define HWIO_UFS_MEM_UTRLBAU_OUT(v)            \
                out_dword(HWIO_UFS_MEM_UTRLBAU_ADDR,v)
#define HWIO_UFS_MEM_UTRLBAU_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_UTRLBAU_ADDR,m,v,HWIO_UFS_MEM_UTRLBAU_IN)
#define HWIO_UFS_MEM_UTRLBAU_UTRLBAU_BMSK                                            0xffffffff
#define HWIO_UFS_MEM_UTRLBAU_UTRLBAU_SHFT                                                     0

#define HWIO_UFS_MEM_UTRLDBR_ADDR                                                    (UFS_MEM_UFS_REG_BASE      + 0x58)
#define HWIO_UFS_MEM_UTRLDBR_OFFS                                                    (UFS_MEM_UFS_REG_BASE_OFFS + 0x58)
#define HWIO_UFS_MEM_UTRLDBR_RMSK                                                    0xffffffff
#define HWIO_UFS_MEM_UTRLDBR_IN                    \
                in_dword(HWIO_UFS_MEM_UTRLDBR_ADDR)
#define HWIO_UFS_MEM_UTRLDBR_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UTRLDBR_ADDR, m)
#define HWIO_UFS_MEM_UTRLDBR_OUT(v)            \
                out_dword(HWIO_UFS_MEM_UTRLDBR_ADDR,v)
#define HWIO_UFS_MEM_UTRLDBR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_UTRLDBR_ADDR,m,v,HWIO_UFS_MEM_UTRLDBR_IN)
#define HWIO_UFS_MEM_UTRLDBR_UTRLDBR_BMSK                                            0xffffffff
#define HWIO_UFS_MEM_UTRLDBR_UTRLDBR_SHFT                                                     0

#define HWIO_UFS_MEM_UTRLCLR_ADDR                                                    (UFS_MEM_UFS_REG_BASE      + 0x5c)
#define HWIO_UFS_MEM_UTRLCLR_OFFS                                                    (UFS_MEM_UFS_REG_BASE_OFFS + 0x5c)
#define HWIO_UFS_MEM_UTRLCLR_RMSK                                                    0xffffffff
#define HWIO_UFS_MEM_UTRLCLR_OUT(v)            \
                out_dword(HWIO_UFS_MEM_UTRLCLR_ADDR,v)
#define HWIO_UFS_MEM_UTRLCLR_UTRLCLR_BMSK                                            0xffffffff
#define HWIO_UFS_MEM_UTRLCLR_UTRLCLR_SHFT                                                     0

#define HWIO_UFS_MEM_UTRLRSR_ADDR                                                    (UFS_MEM_UFS_REG_BASE      + 0x60)
#define HWIO_UFS_MEM_UTRLRSR_OFFS                                                    (UFS_MEM_UFS_REG_BASE_OFFS + 0x60)
#define HWIO_UFS_MEM_UTRLRSR_RMSK                                                           0x1
#define HWIO_UFS_MEM_UTRLRSR_IN                    \
                in_dword(HWIO_UFS_MEM_UTRLRSR_ADDR)
#define HWIO_UFS_MEM_UTRLRSR_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UTRLRSR_ADDR, m)
#define HWIO_UFS_MEM_UTRLRSR_OUT(v)            \
                out_dword(HWIO_UFS_MEM_UTRLRSR_ADDR,v)
#define HWIO_UFS_MEM_UTRLRSR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_UTRLRSR_ADDR,m,v,HWIO_UFS_MEM_UTRLRSR_IN)
#define HWIO_UFS_MEM_UTRLRSR_UTRLRSR_BMSK                                                   0x1
#define HWIO_UFS_MEM_UTRLRSR_UTRLRSR_SHFT                                                     0

#define HWIO_UFS_MEM_UTRLCNR_ADDR                                                    (UFS_MEM_UFS_REG_BASE      + 0x64)
#define HWIO_UFS_MEM_UTRLCNR_OFFS                                                    (UFS_MEM_UFS_REG_BASE_OFFS + 0x64)
#define HWIO_UFS_MEM_UTRLCNR_RMSK                                                    0xffffffff
#define HWIO_UFS_MEM_UTRLCNR_IN                    \
                in_dword(HWIO_UFS_MEM_UTRLCNR_ADDR)
#define HWIO_UFS_MEM_UTRLCNR_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UTRLCNR_ADDR, m)
#define HWIO_UFS_MEM_UTRLCNR_OUT(v)            \
                out_dword(HWIO_UFS_MEM_UTRLCNR_ADDR,v)
#define HWIO_UFS_MEM_UTRLCNR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_UTRLCNR_ADDR,m,v,HWIO_UFS_MEM_UTRLCNR_IN)
#define HWIO_UFS_MEM_UTRLCNR_UTRLCNR_BMSK                                            0xffffffff
#define HWIO_UFS_MEM_UTRLCNR_UTRLCNR_SHFT                                                     0

#define HWIO_UFS_MEM_UTMRLBA_ADDR                                                    (UFS_MEM_UFS_REG_BASE      + 0x70)
#define HWIO_UFS_MEM_UTMRLBA_OFFS                                                    (UFS_MEM_UFS_REG_BASE_OFFS + 0x70)
#define HWIO_UFS_MEM_UTMRLBA_RMSK                                                    0xfffffc00
#define HWIO_UFS_MEM_UTMRLBA_IN                    \
                in_dword(HWIO_UFS_MEM_UTMRLBA_ADDR)
#define HWIO_UFS_MEM_UTMRLBA_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UTMRLBA_ADDR, m)
#define HWIO_UFS_MEM_UTMRLBA_OUT(v)            \
                out_dword(HWIO_UFS_MEM_UTMRLBA_ADDR,v)
#define HWIO_UFS_MEM_UTMRLBA_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_UTMRLBA_ADDR,m,v,HWIO_UFS_MEM_UTMRLBA_IN)
#define HWIO_UFS_MEM_UTMRLBA_UTMRLBA_BMSK                                            0xfffffc00
#define HWIO_UFS_MEM_UTMRLBA_UTMRLBA_SHFT                                                    10

#define HWIO_UFS_MEM_UTMRLBAU_ADDR                                                   (UFS_MEM_UFS_REG_BASE      + 0x74)
#define HWIO_UFS_MEM_UTMRLBAU_OFFS                                                   (UFS_MEM_UFS_REG_BASE_OFFS + 0x74)
#define HWIO_UFS_MEM_UTMRLBAU_RMSK                                                   0xffffffff
#define HWIO_UFS_MEM_UTMRLBAU_IN                    \
                in_dword(HWIO_UFS_MEM_UTMRLBAU_ADDR)
#define HWIO_UFS_MEM_UTMRLBAU_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UTMRLBAU_ADDR, m)
#define HWIO_UFS_MEM_UTMRLBAU_OUT(v)            \
                out_dword(HWIO_UFS_MEM_UTMRLBAU_ADDR,v)
#define HWIO_UFS_MEM_UTMRLBAU_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_UTMRLBAU_ADDR,m,v,HWIO_UFS_MEM_UTMRLBAU_IN)
#define HWIO_UFS_MEM_UTMRLBAU_UTMRLBAU_BMSK                                          0xffffffff
#define HWIO_UFS_MEM_UTMRLBAU_UTMRLBAU_SHFT                                                   0

#define HWIO_UFS_MEM_UTMRLDBR_ADDR                                                   (UFS_MEM_UFS_REG_BASE      + 0x78)
#define HWIO_UFS_MEM_UTMRLDBR_OFFS                                                   (UFS_MEM_UFS_REG_BASE_OFFS + 0x78)
#define HWIO_UFS_MEM_UTMRLDBR_RMSK                                                         0xff
#define HWIO_UFS_MEM_UTMRLDBR_IN                    \
                in_dword(HWIO_UFS_MEM_UTMRLDBR_ADDR)
#define HWIO_UFS_MEM_UTMRLDBR_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UTMRLDBR_ADDR, m)
#define HWIO_UFS_MEM_UTMRLDBR_OUT(v)            \
                out_dword(HWIO_UFS_MEM_UTMRLDBR_ADDR,v)
#define HWIO_UFS_MEM_UTMRLDBR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_UTMRLDBR_ADDR,m,v,HWIO_UFS_MEM_UTMRLDBR_IN)
#define HWIO_UFS_MEM_UTMRLDBR_UTMRLDBR_BMSK                                                0xff
#define HWIO_UFS_MEM_UTMRLDBR_UTMRLDBR_SHFT                                                   0

#define HWIO_UFS_MEM_UTMRLCLR_ADDR                                                   (UFS_MEM_UFS_REG_BASE      + 0x7c)
#define HWIO_UFS_MEM_UTMRLCLR_OFFS                                                   (UFS_MEM_UFS_REG_BASE_OFFS + 0x7c)
#define HWIO_UFS_MEM_UTMRLCLR_RMSK                                                         0xff
#define HWIO_UFS_MEM_UTMRLCLR_OUT(v)            \
                out_dword(HWIO_UFS_MEM_UTMRLCLR_ADDR,v)
#define HWIO_UFS_MEM_UTMRLCLR_UTMRLCLR_BMSK                                                0xff
#define HWIO_UFS_MEM_UTMRLCLR_UTMRLCLR_SHFT                                                   0

#define HWIO_UFS_MEM_UTMRLRSR_ADDR                                                   (UFS_MEM_UFS_REG_BASE      + 0x80)
#define HWIO_UFS_MEM_UTMRLRSR_OFFS                                                   (UFS_MEM_UFS_REG_BASE_OFFS + 0x80)
#define HWIO_UFS_MEM_UTMRLRSR_RMSK                                                          0x1
#define HWIO_UFS_MEM_UTMRLRSR_IN                    \
                in_dword(HWIO_UFS_MEM_UTMRLRSR_ADDR)
#define HWIO_UFS_MEM_UTMRLRSR_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UTMRLRSR_ADDR, m)
#define HWIO_UFS_MEM_UTMRLRSR_OUT(v)            \
                out_dword(HWIO_UFS_MEM_UTMRLRSR_ADDR,v)
#define HWIO_UFS_MEM_UTMRLRSR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_UTMRLRSR_ADDR,m,v,HWIO_UFS_MEM_UTMRLRSR_IN)
#define HWIO_UFS_MEM_UTMRLRSR_UTMRLRSR_BMSK                                                 0x1
#define HWIO_UFS_MEM_UTMRLRSR_UTMRLRSR_SHFT                                                   0

#define HWIO_UFS_MEM_UICCMD_ADDR                                                     (UFS_MEM_UFS_REG_BASE      + 0x90)
#define HWIO_UFS_MEM_UICCMD_OFFS                                                     (UFS_MEM_UFS_REG_BASE_OFFS + 0x90)
#define HWIO_UFS_MEM_UICCMD_RMSK                                                           0xff
#define HWIO_UFS_MEM_UICCMD_IN                    \
                in_dword(HWIO_UFS_MEM_UICCMD_ADDR)
#define HWIO_UFS_MEM_UICCMD_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UICCMD_ADDR, m)
#define HWIO_UFS_MEM_UICCMD_OUT(v)            \
                out_dword(HWIO_UFS_MEM_UICCMD_ADDR,v)
#define HWIO_UFS_MEM_UICCMD_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_UICCMD_ADDR,m,v,HWIO_UFS_MEM_UICCMD_IN)
#define HWIO_UFS_MEM_UICCMD_CMDOP_BMSK                                                     0xff
#define HWIO_UFS_MEM_UICCMD_CMDOP_SHFT                                                        0

#define HWIO_UFS_MEM_UICCMDARG1_ADDR                                                 (UFS_MEM_UFS_REG_BASE      + 0x94)
#define HWIO_UFS_MEM_UICCMDARG1_OFFS                                                 (UFS_MEM_UFS_REG_BASE_OFFS + 0x94)
#define HWIO_UFS_MEM_UICCMDARG1_RMSK                                                 0xffffffff
#define HWIO_UFS_MEM_UICCMDARG1_IN                    \
                in_dword(HWIO_UFS_MEM_UICCMDARG1_ADDR)
#define HWIO_UFS_MEM_UICCMDARG1_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UICCMDARG1_ADDR, m)
#define HWIO_UFS_MEM_UICCMDARG1_OUT(v)            \
                out_dword(HWIO_UFS_MEM_UICCMDARG1_ADDR,v)
#define HWIO_UFS_MEM_UICCMDARG1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_UICCMDARG1_ADDR,m,v,HWIO_UFS_MEM_UICCMDARG1_IN)
#define HWIO_UFS_MEM_UICCMDARG1_ARG1_BMSK                                            0xffffffff
#define HWIO_UFS_MEM_UICCMDARG1_ARG1_SHFT                                                     0

#define HWIO_UFS_MEM_UICCMDARG2_ADDR                                                 (UFS_MEM_UFS_REG_BASE      + 0x98)
#define HWIO_UFS_MEM_UICCMDARG2_OFFS                                                 (UFS_MEM_UFS_REG_BASE_OFFS + 0x98)
#define HWIO_UFS_MEM_UICCMDARG2_RMSK                                                   0xff00ff
#define HWIO_UFS_MEM_UICCMDARG2_IN                    \
                in_dword(HWIO_UFS_MEM_UICCMDARG2_ADDR)
#define HWIO_UFS_MEM_UICCMDARG2_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UICCMDARG2_ADDR, m)
#define HWIO_UFS_MEM_UICCMDARG2_OUT(v)            \
                out_dword(HWIO_UFS_MEM_UICCMDARG2_ADDR,v)
#define HWIO_UFS_MEM_UICCMDARG2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_UICCMDARG2_ADDR,m,v,HWIO_UFS_MEM_UICCMDARG2_IN)
#define HWIO_UFS_MEM_UICCMDARG2_ARG2_ATTR_SET_TYPE_BMSK                                0xff0000
#define HWIO_UFS_MEM_UICCMDARG2_ARG2_ATTR_SET_TYPE_SHFT                                      16
#define HWIO_UFS_MEM_UICCMDARG2_ARG2_RSP_BMSK                                              0xff
#define HWIO_UFS_MEM_UICCMDARG2_ARG2_RSP_SHFT                                                 0

#define HWIO_UFS_MEM_UICCMDARG3_ADDR                                                 (UFS_MEM_UFS_REG_BASE      + 0x9c)
#define HWIO_UFS_MEM_UICCMDARG3_OFFS                                                 (UFS_MEM_UFS_REG_BASE_OFFS + 0x9c)
#define HWIO_UFS_MEM_UICCMDARG3_RMSK                                                 0xffffffff
#define HWIO_UFS_MEM_UICCMDARG3_IN                    \
                in_dword(HWIO_UFS_MEM_UICCMDARG3_ADDR)
#define HWIO_UFS_MEM_UICCMDARG3_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UICCMDARG3_ADDR, m)
#define HWIO_UFS_MEM_UICCMDARG3_OUT(v)            \
                out_dword(HWIO_UFS_MEM_UICCMDARG3_ADDR,v)
#define HWIO_UFS_MEM_UICCMDARG3_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_UICCMDARG3_ADDR,m,v,HWIO_UFS_MEM_UICCMDARG3_IN)
#define HWIO_UFS_MEM_UICCMDARG3_ARG3_BMSK                                            0xffffffff
#define HWIO_UFS_MEM_UICCMDARG3_ARG3_SHFT                                                     0

#define HWIO_UFS_MEM_SYS1CLK_1US_ADDR                                                (UFS_MEM_UFS_REG_BASE      + 0xc0)
#define HWIO_UFS_MEM_SYS1CLK_1US_OFFS                                                (UFS_MEM_UFS_REG_BASE_OFFS + 0xc0)
#define HWIO_UFS_MEM_SYS1CLK_1US_RMSK                                                     0x7ff
#define HWIO_UFS_MEM_SYS1CLK_1US_IN                    \
                in_dword(HWIO_UFS_MEM_SYS1CLK_1US_ADDR)
#define HWIO_UFS_MEM_SYS1CLK_1US_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_SYS1CLK_1US_ADDR, m)
#define HWIO_UFS_MEM_SYS1CLK_1US_OUT(v)            \
                out_dword(HWIO_UFS_MEM_SYS1CLK_1US_ADDR,v)
#define HWIO_UFS_MEM_SYS1CLK_1US_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_SYS1CLK_1US_ADDR,m,v,HWIO_UFS_MEM_SYS1CLK_1US_IN)
#define HWIO_UFS_MEM_SYS1CLK_1US_SYS1CLK_1US_REG_BMSK                                     0x7ff
#define HWIO_UFS_MEM_SYS1CLK_1US_SYS1CLK_1US_REG_SHFT                                         0

#define HWIO_UFS_MEM_REG_PA_ERR_CODE_ADDR                                            (UFS_MEM_UFS_REG_BASE      + 0xcc)
#define HWIO_UFS_MEM_REG_PA_ERR_CODE_OFFS                                            (UFS_MEM_UFS_REG_BASE_OFFS + 0xcc)
#define HWIO_UFS_MEM_REG_PA_ERR_CODE_RMSK                                                  0xff
#define HWIO_UFS_MEM_REG_PA_ERR_CODE_IN                    \
                in_dword(HWIO_UFS_MEM_REG_PA_ERR_CODE_ADDR)
#define HWIO_UFS_MEM_REG_PA_ERR_CODE_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_REG_PA_ERR_CODE_ADDR, m)
#define HWIO_UFS_MEM_REG_PA_ERR_CODE_PA_ERR_CODE_REG_BMSK                                  0xff
#define HWIO_UFS_MEM_REG_PA_ERR_CODE_PA_ERR_CODE_REG_SHFT                                     0

#define HWIO_UFS_MEM_PARAM0_ADDR                                                     (UFS_MEM_UFS_REG_BASE      + 0xd0)
#define HWIO_UFS_MEM_PARAM0_OFFS                                                     (UFS_MEM_UFS_REG_BASE_OFFS + 0xd0)
#define HWIO_UFS_MEM_PARAM0_RMSK                                                       0x3fff73
#define HWIO_UFS_MEM_PARAM0_IN                    \
                in_dword(HWIO_UFS_MEM_PARAM0_ADDR)
#define HWIO_UFS_MEM_PARAM0_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_PARAM0_ADDR, m)
#define HWIO_UFS_MEM_PARAM0_TX_CFG_CTRL2PHY_PIPE_DEPTH_BMSK                            0x300000
#define HWIO_UFS_MEM_PARAM0_TX_CFG_CTRL2PHY_PIPE_DEPTH_SHFT                                  20
#define HWIO_UFS_MEM_PARAM0_TX_CFG_PHY2CTRL_PIPE_DEPTH_BMSK                             0xc0000
#define HWIO_UFS_MEM_PARAM0_TX_CFG_PHY2CTRL_PIPE_DEPTH_SHFT                                  18
#define HWIO_UFS_MEM_PARAM0_TX_DATA_CTRL2PHY_PIPE_DEPTH_BMSK                            0x30000
#define HWIO_UFS_MEM_PARAM0_TX_DATA_CTRL2PHY_PIPE_DEPTH_SHFT                                 16
#define HWIO_UFS_MEM_PARAM0_TX_DATA_PHY2CTRL_PIPE_DEPTH_BMSK                             0xc000
#define HWIO_UFS_MEM_PARAM0_TX_DATA_PHY2CTRL_PIPE_DEPTH_SHFT                                 14
#define HWIO_UFS_MEM_PARAM0_RX_CFG_CTRL2PHY_PIPE_DEPTH_BMSK                              0x3000
#define HWIO_UFS_MEM_PARAM0_RX_CFG_CTRL2PHY_PIPE_DEPTH_SHFT                                  12
#define HWIO_UFS_MEM_PARAM0_RX_CFG_PHY2CTRL_PIPE_DEPTH_BMSK                               0xc00
#define HWIO_UFS_MEM_PARAM0_RX_CFG_PHY2CTRL_PIPE_DEPTH_SHFT                                  10
#define HWIO_UFS_MEM_PARAM0_RX_DATA_PHY2CTRL_PIPE_DEPTH_BMSK                              0x300
#define HWIO_UFS_MEM_PARAM0_RX_DATA_PHY2CTRL_PIPE_DEPTH_SHFT                                  8
#define HWIO_UFS_MEM_PARAM0_MAX_HS_GEAR_BMSK                                               0x70
#define HWIO_UFS_MEM_PARAM0_MAX_HS_GEAR_SHFT                                                  4
#define HWIO_UFS_MEM_PARAM0_NUM_OF_LANES_BMSK                                               0x3
#define HWIO_UFS_MEM_PARAM0_NUM_OF_LANES_SHFT                                                 0

#define HWIO_UFS_MEM_CFG0_ADDR                                                       (UFS_MEM_UFS_REG_BASE      + 0xd8)
#define HWIO_UFS_MEM_CFG0_OFFS                                                       (UFS_MEM_UFS_REG_BASE_OFFS + 0xd8)
#define HWIO_UFS_MEM_CFG0_RMSK                                                              0x3
#define HWIO_UFS_MEM_CFG0_IN                    \
                in_dword(HWIO_UFS_MEM_CFG0_ADDR)
#define HWIO_UFS_MEM_CFG0_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_CFG0_ADDR, m)
#define HWIO_UFS_MEM_CFG0_OUT(v)            \
                out_dword(HWIO_UFS_MEM_CFG0_ADDR,v)
#define HWIO_UFS_MEM_CFG0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_CFG0_ADDR,m,v,HWIO_UFS_MEM_CFG0_IN)
#define HWIO_UFS_MEM_CFG0_HCI_UAWM_ID_ORDER_BMSK                                            0x2
#define HWIO_UFS_MEM_CFG0_HCI_UAWM_ID_ORDER_SHFT                                              1
#define HWIO_UFS_MEM_CFG0_HCI_UAWM_OOO_DIS_BMSK                                             0x1
#define HWIO_UFS_MEM_CFG0_HCI_UAWM_OOO_DIS_SHFT                                               0

#define HWIO_UFS_MEM_CFG1_ADDR                                                       (UFS_MEM_UFS_REG_BASE      + 0xdc)
#define HWIO_UFS_MEM_CFG1_OFFS                                                       (UFS_MEM_UFS_REG_BASE_OFFS + 0xdc)
#define HWIO_UFS_MEM_CFG1_RMSK                                                       0xffffffff
#define HWIO_UFS_MEM_CFG1_IN                    \
                in_dword(HWIO_UFS_MEM_CFG1_ADDR)
#define HWIO_UFS_MEM_CFG1_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_CFG1_ADDR, m)
#define HWIO_UFS_MEM_CFG1_OUT(v)            \
                out_dword(HWIO_UFS_MEM_CFG1_ADDR,v)
#define HWIO_UFS_MEM_CFG1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_CFG1_ADDR,m,v,HWIO_UFS_MEM_CFG1_IN)
#define HWIO_UFS_MEM_CFG1_UTP_SCASI_CHECK_DIS_BMSK                                   0x80000000
#define HWIO_UFS_MEM_CFG1_UTP_SCASI_CHECK_DIS_SHFT                                           31
#define HWIO_UFS_MEM_CFG1_UFS_REG_TEST_BUS_EN_BMSK                                   0x40000000
#define HWIO_UFS_MEM_CFG1_UFS_REG_TEST_BUS_EN_SHFT                                           30
#define HWIO_UFS_MEM_CFG1_DFC_VALID_CLR_REQ_DIS_BMSK                                 0x20000000
#define HWIO_UFS_MEM_CFG1_DFC_VALID_CLR_REQ_DIS_SHFT                                         29
#define HWIO_UFS_MEM_CFG1_WARM_DME_RESET_BMSK                                        0x10000000
#define HWIO_UFS_MEM_CFG1_WARM_DME_RESET_SHFT                                                28
#define HWIO_UFS_MEM_CFG1_SMMU_PREF_DIS_BMSK                                          0x8000000
#define HWIO_UFS_MEM_CFG1_SMMU_PREF_DIS_SHFT                                                 27
#define HWIO_UFS_MEM_CFG1_UFS_DEV_REF_CLK_EN_BMSK                                     0x4000000
#define HWIO_UFS_MEM_CFG1_UFS_DEV_REF_CLK_EN_SHFT                                            26
#define HWIO_UFS_MEM_CFG1_EDTL_RAM_PRIORITY_BMSK                                      0x2000000
#define HWIO_UFS_MEM_CFG1_EDTL_RAM_PRIORITY_SHFT                                             25
#define HWIO_UFS_MEM_CFG1_EDTL_ERR_EN_BMSK                                            0x1000000
#define HWIO_UFS_MEM_CFG1_EDTL_ERR_EN_SHFT                                                   24
#define HWIO_UFS_MEM_CFG1_TR_INDX_NF_UTPES_EN_BMSK                                     0x800000
#define HWIO_UFS_MEM_CFG1_TR_INDX_NF_UTPES_EN_SHFT                                           23
#define HWIO_UFS_MEM_CFG1_UTP_TEST_BUS_SEL_BMSK                                        0x780000
#define HWIO_UFS_MEM_CFG1_UTP_TEST_BUS_SEL_SHFT                                              19
#define HWIO_UFS_MEM_CFG1_UTP_TEST_BUS_EN_BMSK                                          0x40000
#define HWIO_UFS_MEM_CFG1_UTP_TEST_BUS_EN_SHFT                                               18
#define HWIO_UFS_MEM_CFG1_UTP_DBG_RAMS_EN_BMSK                                          0x20000
#define HWIO_UFS_MEM_CFG1_UTP_DBG_RAMS_EN_SHFT                                               17
#define HWIO_UFS_MEM_CFG1_HCI_EDTL_RAM_RD_FORCE_BMSK                                    0x10000
#define HWIO_UFS_MEM_CFG1_HCI_EDTL_RAM_RD_FORCE_SHFT                                         16
#define HWIO_UFS_MEM_CFG1_HCI_TX_RAM_RD_FORCE_BMSK                                       0x8000
#define HWIO_UFS_MEM_CFG1_HCI_TX_RAM_RD_FORCE_SHFT                                           15
#define HWIO_UFS_MEM_CFG1_HCI_RX_RAM_RD_FORCE_BMSK                                       0x4000
#define HWIO_UFS_MEM_CFG1_HCI_RX_RAM_RD_FORCE_SHFT                                           14
#define HWIO_UFS_MEM_CFG1_HCI_DESC_RAM_RD_FORCE_BMSK                                     0x2000
#define HWIO_UFS_MEM_CFG1_HCI_DESC_RAM_RD_FORCE_SHFT                                         13
#define HWIO_UFS_MEM_CFG1_HCI_PRDT_RAM_RD_FORCE_BMSK                                     0x1000
#define HWIO_UFS_MEM_CFG1_HCI_PRDT_RAM_RD_FORCE_SHFT                                         12
#define HWIO_UFS_MEM_CFG1_HCI_RESP_RAM_RD_FORCE_BMSK                                      0x800
#define HWIO_UFS_MEM_CFG1_HCI_RESP_RAM_RD_FORCE_SHFT                                         11
#define HWIO_UFS_MEM_CFG1_UFS_AHB2PHY_SIZE_ERROR_EN_BMSK                                  0x400
#define HWIO_UFS_MEM_CFG1_UFS_AHB2PHY_SIZE_ERROR_EN_SHFT                                     10
#define HWIO_UFS_MEM_CFG1_UFS_AWMEMTYPE_BMSK                                              0x380
#define HWIO_UFS_MEM_CFG1_UFS_AWMEMTYPE_SHFT                                                  7
#define HWIO_UFS_MEM_CFG1_UFS_ARMEMTYPE_BMSK                                               0x70
#define HWIO_UFS_MEM_CFG1_UFS_ARMEMTYPE_SHFT                                                  4
#define HWIO_UFS_MEM_CFG1_UFS_AWNOALLOCATE_BMSK                                             0x8
#define HWIO_UFS_MEM_CFG1_UFS_AWNOALLOCATE_SHFT                                               3
#define HWIO_UFS_MEM_CFG1_UFS_ARNOALLOCATE_BMSK                                             0x4
#define HWIO_UFS_MEM_CFG1_UFS_ARNOALLOCATE_SHFT                                               2
#define HWIO_UFS_MEM_CFG1_UFS_PHY_SOFT_RESET_BMSK                                           0x2
#define HWIO_UFS_MEM_CFG1_UFS_PHY_SOFT_RESET_SHFT                                             1
#define HWIO_UFS_MEM_CFG1_NOT_USE_0_BMSK                                                    0x1
#define HWIO_UFS_MEM_CFG1_NOT_USE_0_SHFT                                                      0

#define HWIO_UFS_MEM_CFG2_ADDR                                                       (UFS_MEM_UFS_REG_BASE      + 0xe0)
#define HWIO_UFS_MEM_CFG2_OFFS                                                       (UFS_MEM_UFS_REG_BASE_OFFS + 0xe0)
#define HWIO_UFS_MEM_CFG2_RMSK                                                       0xffffffff
#define HWIO_UFS_MEM_CFG2_IN                    \
                in_dword(HWIO_UFS_MEM_CFG2_ADDR)
#define HWIO_UFS_MEM_CFG2_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_CFG2_ADDR, m)
#define HWIO_UFS_MEM_CFG2_OUT(v)            \
                out_dword(HWIO_UFS_MEM_CFG2_ADDR,v)
#define HWIO_UFS_MEM_CFG2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_CFG2_ADDR,m,v,HWIO_UFS_MEM_CFG2_IN)
#define HWIO_UFS_MEM_CFG2_HCI_DB_CLR_DLY_DIS_BMSK                                    0x80000000
#define HWIO_UFS_MEM_CFG2_HCI_DB_CLR_DLY_DIS_SHFT                                            31
#define HWIO_UFS_MEM_CFG2_RTT_CFG_BMSK                                               0x40000000
#define HWIO_UFS_MEM_CFG2_RTT_CFG_SHFT                                                       30
#define HWIO_UFS_MEM_CFG2_UARM_MAX_OTR_BMSK                                          0x38000000
#define HWIO_UFS_MEM_CFG2_UARM_MAX_OTR_SHFT                                                  27
#define HWIO_UFS_MEM_CFG2_UAWM_MAX_OTR_BMSK                                           0x7000000
#define HWIO_UFS_MEM_CFG2_UAWM_MAX_OTR_SHFT                                                  24
#define HWIO_UFS_MEM_CFG2_RXUC_PRDT_EMPTY_DIS_BMSK                                     0x800000
#define HWIO_UFS_MEM_CFG2_RXUC_PRDT_EMPTY_DIS_SHFT                                           23
#define HWIO_UFS_MEM_CFG2_HCI_HCE_CLR_DLY_DIS_BMSK                                     0x400000
#define HWIO_UFS_MEM_CFG2_HCI_HCE_CLR_DLY_DIS_SHFT                                           22
#define HWIO_UFS_MEM_CFG2_TXUC_PRDT_EMPTY_DIS_BMSK                                     0x200000
#define HWIO_UFS_MEM_CFG2_TXUC_PRDT_EMPTY_DIS_SHFT                                           21
#define HWIO_UFS_MEM_CFG2_SBFE_UAWM_DIS_BMSK                                           0x100000
#define HWIO_UFS_MEM_CFG2_SBFE_UAWM_DIS_SHFT                                                 20
#define HWIO_UFS_MEM_CFG2_SBFE_UARM_DIS_BMSK                                            0x80000
#define HWIO_UFS_MEM_CFG2_SBFE_UARM_DIS_SHFT                                                 19
#define HWIO_UFS_MEM_CFG2_HCI_AWCACHE_BMSK                                              0x78000
#define HWIO_UFS_MEM_CFG2_HCI_AWCACHE_SHFT                                                   15
#define HWIO_UFS_MEM_CFG2_HCI_ARCACHE_BMSK                                               0x7800
#define HWIO_UFS_MEM_CFG2_HCI_ARCACHE_SHFT                                                   11
#define HWIO_UFS_MEM_CFG2_HCI_UARM_PRIORITY_MODE_BMSK                                     0x700
#define HWIO_UFS_MEM_CFG2_HCI_UARM_PRIORITY_MODE_SHFT                                         8
#define HWIO_UFS_MEM_CFG2_OCSC_HW_CGC_EN_BMSK                                              0x80
#define HWIO_UFS_MEM_CFG2_OCSC_HW_CGC_EN_SHFT                                                 7
#define HWIO_UFS_MEM_CFG2_TMRLUT_HW_CGC_EN_BMSK                                            0x40
#define HWIO_UFS_MEM_CFG2_TMRLUT_HW_CGC_EN_SHFT                                               6
#define HWIO_UFS_MEM_CFG2_TRLUT_HW_CGC_EN_BMSK                                             0x20
#define HWIO_UFS_MEM_CFG2_TRLUT_HW_CGC_EN_SHFT                                                5
#define HWIO_UFS_MEM_CFG2_DFC_HW_CGC_EN_BMSK                                               0x10
#define HWIO_UFS_MEM_CFG2_DFC_HW_CGC_EN_SHFT                                                  4
#define HWIO_UFS_MEM_CFG2_RXUC_HW_CGC_EN_BMSK                                               0x8
#define HWIO_UFS_MEM_CFG2_RXUC_HW_CGC_EN_SHFT                                                 3
#define HWIO_UFS_MEM_CFG2_TXUC_HW_CGC_EN_BMSK                                               0x4
#define HWIO_UFS_MEM_CFG2_TXUC_HW_CGC_EN_SHFT                                                 2
#define HWIO_UFS_MEM_CFG2_UARM_HW_CGC_EN_BMSK                                               0x2
#define HWIO_UFS_MEM_CFG2_UARM_HW_CGC_EN_SHFT                                                 1
#define HWIO_UFS_MEM_CFG2_UAWM_HW_CGC_EN_BMSK                                               0x1
#define HWIO_UFS_MEM_CFG2_UAWM_HW_CGC_EN_SHFT                                                 0

#define HWIO_UFS_MEM_HW_VERSION_ADDR                                                 (UFS_MEM_UFS_REG_BASE      + 0xe4)
#define HWIO_UFS_MEM_HW_VERSION_OFFS                                                 (UFS_MEM_UFS_REG_BASE_OFFS + 0xe4)
#define HWIO_UFS_MEM_HW_VERSION_RMSK                                                 0xffffffff
#define HWIO_UFS_MEM_HW_VERSION_IN                    \
                in_dword(HWIO_UFS_MEM_HW_VERSION_ADDR)
#define HWIO_UFS_MEM_HW_VERSION_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_HW_VERSION_ADDR, m)
#define HWIO_UFS_MEM_HW_VERSION_MAJOR_BMSK                                           0xf0000000
#define HWIO_UFS_MEM_HW_VERSION_MAJOR_SHFT                                                   28
#define HWIO_UFS_MEM_HW_VERSION_MINOR_BMSK                                            0xfff0000
#define HWIO_UFS_MEM_HW_VERSION_MINOR_SHFT                                                   16
#define HWIO_UFS_MEM_HW_VERSION_STEP_BMSK                                                0xffff
#define HWIO_UFS_MEM_HW_VERSION_STEP_SHFT                                                     0

#define HWIO_UFS_MEM_TEST_BUS_ADDR                                                   (UFS_MEM_UFS_REG_BASE      + 0xe8)
#define HWIO_UFS_MEM_TEST_BUS_OFFS                                                   (UFS_MEM_UFS_REG_BASE_OFFS + 0xe8)
#define HWIO_UFS_MEM_TEST_BUS_RMSK                                                   0xffffffff
#define HWIO_UFS_MEM_TEST_BUS_IN                    \
                in_dword(HWIO_UFS_MEM_TEST_BUS_ADDR)
#define HWIO_UFS_MEM_TEST_BUS_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_TEST_BUS_ADDR, m)
#define HWIO_UFS_MEM_TEST_BUS_TEST_BUS_BMSK                                          0xffffffff
#define HWIO_UFS_MEM_TEST_BUS_TEST_BUS_SHFT                                                   0

#define HWIO_UFS_MEM_TEST_BUS_CTRL_0_ADDR                                            (UFS_MEM_UFS_REG_BASE      + 0xec)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_0_OFFS                                            (UFS_MEM_UFS_REG_BASE_OFFS + 0xec)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_0_RMSK                                            0x1f1f1f1f
#define HWIO_UFS_MEM_TEST_BUS_CTRL_0_IN                    \
                in_dword(HWIO_UFS_MEM_TEST_BUS_CTRL_0_ADDR)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_0_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_TEST_BUS_CTRL_0_ADDR, m)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_0_OUT(v)            \
                out_dword(HWIO_UFS_MEM_TEST_BUS_CTRL_0_ADDR,v)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_0_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_TEST_BUS_CTRL_0_ADDR,m,v,HWIO_UFS_MEM_TEST_BUS_CTRL_0_IN)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_0_UAWM_SEL_BMSK                                   0x1f000000
#define HWIO_UFS_MEM_TEST_BUS_CTRL_0_UAWM_SEL_SHFT                                           24
#define HWIO_UFS_MEM_TEST_BUS_CTRL_0_UARM_SEL_BMSK                                     0x1f0000
#define HWIO_UFS_MEM_TEST_BUS_CTRL_0_UARM_SEL_SHFT                                           16
#define HWIO_UFS_MEM_TEST_BUS_CTRL_0_TXUC_SEL_BMSK                                       0x1f00
#define HWIO_UFS_MEM_TEST_BUS_CTRL_0_TXUC_SEL_SHFT                                            8
#define HWIO_UFS_MEM_TEST_BUS_CTRL_0_RXUC_SEL_BMSK                                         0x1f
#define HWIO_UFS_MEM_TEST_BUS_CTRL_0_RXUC_SEL_SHFT                                            0

#define HWIO_UFS_MEM_TEST_BUS_CTRL_1_ADDR                                            (UFS_MEM_UFS_REG_BASE      + 0xf0)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_1_OFFS                                            (UFS_MEM_UFS_REG_BASE_OFFS + 0xf0)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_1_RMSK                                            0x1f1f1f1f
#define HWIO_UFS_MEM_TEST_BUS_CTRL_1_IN                    \
                in_dword(HWIO_UFS_MEM_TEST_BUS_CTRL_1_ADDR)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_1_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_TEST_BUS_CTRL_1_ADDR, m)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_1_OUT(v)            \
                out_dword(HWIO_UFS_MEM_TEST_BUS_CTRL_1_ADDR,v)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_1_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_TEST_BUS_CTRL_1_ADDR,m,v,HWIO_UFS_MEM_TEST_BUS_CTRL_1_IN)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_1_DFC_SEL_BMSK                                    0x1f000000
#define HWIO_UFS_MEM_TEST_BUS_CTRL_1_DFC_SEL_SHFT                                            24
#define HWIO_UFS_MEM_TEST_BUS_CTRL_1_TRLUT_SEL_BMSK                                    0x1f0000
#define HWIO_UFS_MEM_TEST_BUS_CTRL_1_TRLUT_SEL_SHFT                                          16
#define HWIO_UFS_MEM_TEST_BUS_CTRL_1_TMRLUT_SEL_BMSK                                     0x1f00
#define HWIO_UFS_MEM_TEST_BUS_CTRL_1_TMRLUT_SEL_SHFT                                          8
#define HWIO_UFS_MEM_TEST_BUS_CTRL_1_OCSC_SEL_BMSK                                         0x1f
#define HWIO_UFS_MEM_TEST_BUS_CTRL_1_OCSC_SEL_SHFT                                            0

#define HWIO_UFS_MEM_TEST_BUS_CTRL_2_ADDR                                            (UFS_MEM_UFS_REG_BASE      + 0xf4)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_2_OFFS                                            (UFS_MEM_UFS_REG_BASE_OFFS + 0xf4)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_2_RMSK                                              0x1f1f1f
#define HWIO_UFS_MEM_TEST_BUS_CTRL_2_IN                    \
                in_dword(HWIO_UFS_MEM_TEST_BUS_CTRL_2_ADDR)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_2_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_TEST_BUS_CTRL_2_ADDR, m)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_2_OUT(v)            \
                out_dword(HWIO_UFS_MEM_TEST_BUS_CTRL_2_ADDR,v)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_2_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_TEST_BUS_CTRL_2_ADDR,m,v,HWIO_UFS_MEM_TEST_BUS_CTRL_2_IN)
#define HWIO_UFS_MEM_TEST_BUS_CTRL_2_WRAPPER_SEL_BMSK                                  0x1f0000
#define HWIO_UFS_MEM_TEST_BUS_CTRL_2_WRAPPER_SEL_SHFT                                        16
#define HWIO_UFS_MEM_TEST_BUS_CTRL_2_COMBINED_SEL_BMSK                                   0x1f00
#define HWIO_UFS_MEM_TEST_BUS_CTRL_2_COMBINED_SEL_SHFT                                        8
#define HWIO_UFS_MEM_TEST_BUS_CTRL_2_HCI_SEL_BMSK                                          0x1f
#define HWIO_UFS_MEM_TEST_BUS_CTRL_2_HCI_SEL_SHFT                                             0

#define HWIO_UFS_MEM_UNIPRO_CFG_ADDR                                                 (UFS_MEM_UFS_REG_BASE      + 0xf8)
#define HWIO_UFS_MEM_UNIPRO_CFG_OFFS                                                 (UFS_MEM_UFS_REG_BASE_OFFS + 0xf8)
#define HWIO_UFS_MEM_UNIPRO_CFG_RMSK                                                 0xffffffff
#define HWIO_UFS_MEM_UNIPRO_CFG_IN                    \
                in_dword(HWIO_UFS_MEM_UNIPRO_CFG_ADDR)
#define HWIO_UFS_MEM_UNIPRO_CFG_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_UNIPRO_CFG_ADDR, m)
#define HWIO_UFS_MEM_UNIPRO_CFG_OUT(v)            \
                out_dword(HWIO_UFS_MEM_UNIPRO_CFG_ADDR,v)
#define HWIO_UFS_MEM_UNIPRO_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_UNIPRO_CFG_ADDR,m,v,HWIO_UFS_MEM_UNIPRO_CFG_IN)
#define HWIO_UFS_MEM_UNIPRO_CFG_UNIPRO_TEST_BUS_SEL_BMSK                             0xfff00000
#define HWIO_UFS_MEM_UNIPRO_CFG_UNIPRO_TEST_BUS_SEL_SHFT                                     20
#define HWIO_UFS_MEM_UNIPRO_CFG_NOT_USE_19_0_BMSK                                       0xfffff
#define HWIO_UFS_MEM_UNIPRO_CFG_NOT_USE_19_0_SHFT                                             0

#define HWIO_UFS_MEM_AH8_CFG_ADDR                                                    (UFS_MEM_UFS_REG_BASE      + 0xfc)
#define HWIO_UFS_MEM_AH8_CFG_OFFS                                                    (UFS_MEM_UFS_REG_BASE_OFFS + 0xfc)
#define HWIO_UFS_MEM_AH8_CFG_RMSK                                                         0x7fd
#define HWIO_UFS_MEM_AH8_CFG_IN                    \
                in_dword(HWIO_UFS_MEM_AH8_CFG_ADDR)
#define HWIO_UFS_MEM_AH8_CFG_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_AH8_CFG_ADDR, m)
#define HWIO_UFS_MEM_AH8_CFG_OUT(v)            \
                out_dword(HWIO_UFS_MEM_AH8_CFG_ADDR,v)
#define HWIO_UFS_MEM_AH8_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_AH8_CFG_ADDR,m,v,HWIO_UFS_MEM_AH8_CFG_IN)
#define HWIO_UFS_MEM_AH8_CFG_AH8_BYPASS_BMSK                                              0x400
#define HWIO_UFS_MEM_AH8_CFG_AH8_BYPASS_SHFT                                                 10
#define HWIO_UFS_MEM_AH8_CFG_AH8_ENTER_PWR_BUSY_BMSK                                      0x200
#define HWIO_UFS_MEM_AH8_CFG_AH8_ENTER_PWR_BUSY_SHFT                                          9
#define HWIO_UFS_MEM_AH8_CFG_CC_UFS_UNIPRO_CORE_CLK_GATE_EN_BMSK                          0x100
#define HWIO_UFS_MEM_AH8_CFG_CC_UFS_UNIPRO_CORE_CLK_GATE_EN_SHFT                              8
#define HWIO_UFS_MEM_AH8_CFG_CC_UFS_ICE_CORE_CLK_GATE_EN_BMSK                              0x80
#define HWIO_UFS_MEM_AH8_CFG_CC_UFS_ICE_CORE_CLK_GATE_EN_SHFT                                 7
#define HWIO_UFS_MEM_AH8_CFG_CC_UFS_SYS_CLK_GATE_EN_BMSK                                   0x40
#define HWIO_UFS_MEM_AH8_CFG_CC_UFS_SYS_CLK_GATE_EN_SHFT                                      6
#define HWIO_UFS_MEM_AH8_CFG_UFSPHY_AUXCLK_REQ_EN_BMSK                                     0x20
#define HWIO_UFS_MEM_AH8_CFG_UFSPHY_AUXCLK_REQ_EN_SHFT                                        5
#define HWIO_UFS_MEM_AH8_CFG_CC_UFS_UNIPRO_CORE_CLK_REQ_EN_BMSK                            0x10
#define HWIO_UFS_MEM_AH8_CFG_CC_UFS_UNIPRO_CORE_CLK_REQ_EN_SHFT                               4
#define HWIO_UFS_MEM_AH8_CFG_CC_UFS_ICE_CORE_CLK_REQ_EN_BMSK                                0x8
#define HWIO_UFS_MEM_AH8_CFG_CC_UFS_ICE_CORE_CLK_REQ_EN_SHFT                                  3
#define HWIO_UFS_MEM_AH8_CFG_CC_UFS_SYS_CLK_REQ_EN_BMSK                                     0x4
#define HWIO_UFS_MEM_AH8_CFG_CC_UFS_SYS_CLK_REQ_EN_SHFT                                       2
#define HWIO_UFS_MEM_AH8_CFG_HCI_TR_TMR_FIFO_EMPTY_MASK_EN_BMSK                             0x1
#define HWIO_UFS_MEM_AH8_CFG_HCI_TR_TMR_FIFO_EMPTY_MASK_EN_SHFT                               0

#define HWIO_UFS_MEM_CCAP_ADDR                                                       (UFS_MEM_UFS_REG_BASE      + 0x100)
#define HWIO_UFS_MEM_CCAP_OFFS                                                       (UFS_MEM_UFS_REG_BASE_OFFS + 0x100)
#define HWIO_UFS_MEM_CCAP_RMSK                                                       0xff00ffff
#define HWIO_UFS_MEM_CCAP_IN                    \
                in_dword(HWIO_UFS_MEM_CCAP_ADDR)
#define HWIO_UFS_MEM_CCAP_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_CCAP_ADDR, m)
#define HWIO_UFS_MEM_CCAP_CFGPTR_BMSK                                                0xff000000
#define HWIO_UFS_MEM_CCAP_CFGPTR_SHFT                                                        24
#define HWIO_UFS_MEM_CCAP_CFGC_BMSK                                                      0xff00
#define HWIO_UFS_MEM_CCAP_CFGC_SHFT                                                           8
#define HWIO_UFS_MEM_CCAP_CC_BMSK                                                          0xff
#define HWIO_UFS_MEM_CCAP_CC_SHFT                                                             0

#define HWIO_UFS_MEM_CRYPTOCAP_n_ADDR(n)                                             (UFS_MEM_UFS_REG_BASE      + 0X104 + (0x4*(n)))
#define HWIO_UFS_MEM_CRYPTOCAP_n_OFFS(n)                                             (UFS_MEM_UFS_REG_BASE_OFFS + 0X104 + (0x4*(n)))
#define HWIO_UFS_MEM_CRYPTOCAP_n_RMSK                                                  0xffffff
#define HWIO_UFS_MEM_CRYPTOCAP_n_MAXn                                                       254
#define HWIO_UFS_MEM_CRYPTOCAP_n_INI(n)                \
                in_dword_masked(HWIO_UFS_MEM_CRYPTOCAP_n_ADDR(n), HWIO_UFS_MEM_CRYPTOCAP_n_RMSK)
#define HWIO_UFS_MEM_CRYPTOCAP_n_INMI(n,mask)        \
                in_dword_masked(HWIO_UFS_MEM_CRYPTOCAP_n_ADDR(n), mask)
#define HWIO_UFS_MEM_CRYPTOCAP_n_KS_BMSK                                               0xff0000
#define HWIO_UFS_MEM_CRYPTOCAP_n_KS_SHFT                                                     16
#define HWIO_UFS_MEM_CRYPTOCAP_n_SDUSB_BMSK                                              0xff00
#define HWIO_UFS_MEM_CRYPTOCAP_n_SDUSB_SHFT                                                   8
#define HWIO_UFS_MEM_CRYPTOCAP_n_ALGID_BMSK                                                0xff
#define HWIO_UFS_MEM_CRYPTOCAP_n_ALGID_SHFT                                                   0

#define HWIO_UFS_MEM_DBG_RD_REG_UAWMn_ADDR(n)                                        (UFS_MEM_UFS_REG_BASE      + 0X500 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_REG_UAWMn_OFFS(n)                                        (UFS_MEM_UFS_REG_BASE_OFFS + 0X500 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_REG_UAWMn_RMSK                                           0xffffffff
#define HWIO_UFS_MEM_DBG_RD_REG_UAWMn_MAXn                                                   63
#define HWIO_UFS_MEM_DBG_RD_REG_UAWMn_INI(n)                \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_REG_UAWMn_ADDR(n), HWIO_UFS_MEM_DBG_RD_REG_UAWMn_RMSK)
#define HWIO_UFS_MEM_DBG_RD_REG_UAWMn_INMI(n,mask)        \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_REG_UAWMn_ADDR(n), mask)
#define HWIO_UFS_MEM_DBG_RD_REG_UAWMn_UFS_DBG_RD_REG_UAWM_BMSK                       0xffffffff
#define HWIO_UFS_MEM_DBG_RD_REG_UAWMn_UFS_DBG_RD_REG_UAWM_SHFT                                0

#define HWIO_UFS_MEM_DBG_RD_REG_UARMn_ADDR(n)                                        (UFS_MEM_UFS_REG_BASE      + 0X600 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_REG_UARMn_OFFS(n)                                        (UFS_MEM_UFS_REG_BASE_OFFS + 0X600 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_REG_UARMn_RMSK                                           0xffffffff
#define HWIO_UFS_MEM_DBG_RD_REG_UARMn_MAXn                                                   63
#define HWIO_UFS_MEM_DBG_RD_REG_UARMn_INI(n)                \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_REG_UARMn_ADDR(n), HWIO_UFS_MEM_DBG_RD_REG_UARMn_RMSK)
#define HWIO_UFS_MEM_DBG_RD_REG_UARMn_INMI(n,mask)        \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_REG_UARMn_ADDR(n), mask)
#define HWIO_UFS_MEM_DBG_RD_REG_UARMn_UFS_DBG_RD_REG_UARM_BMSK                       0xffffffff
#define HWIO_UFS_MEM_DBG_RD_REG_UARMn_UFS_DBG_RD_REG_UARM_SHFT                                0

#define HWIO_UFS_MEM_DBG_RD_REG_TXUCn_ADDR(n)                                        (UFS_MEM_UFS_REG_BASE      + 0X700 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_REG_TXUCn_OFFS(n)                                        (UFS_MEM_UFS_REG_BASE_OFFS + 0X700 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_REG_TXUCn_RMSK                                           0xffffffff
#define HWIO_UFS_MEM_DBG_RD_REG_TXUCn_MAXn                                                   63
#define HWIO_UFS_MEM_DBG_RD_REG_TXUCn_INI(n)                \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_REG_TXUCn_ADDR(n), HWIO_UFS_MEM_DBG_RD_REG_TXUCn_RMSK)
#define HWIO_UFS_MEM_DBG_RD_REG_TXUCn_INMI(n,mask)        \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_REG_TXUCn_ADDR(n), mask)
#define HWIO_UFS_MEM_DBG_RD_REG_TXUCn_UFS_DBG_RD_REG_TXUC_BMSK                       0xffffffff
#define HWIO_UFS_MEM_DBG_RD_REG_TXUCn_UFS_DBG_RD_REG_TXUC_SHFT                                0

#define HWIO_UFS_MEM_DBG_RD_REG_RXUCn_ADDR(n)                                        (UFS_MEM_UFS_REG_BASE      + 0X800 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_REG_RXUCn_OFFS(n)                                        (UFS_MEM_UFS_REG_BASE_OFFS + 0X800 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_REG_RXUCn_RMSK                                           0xffffffff
#define HWIO_UFS_MEM_DBG_RD_REG_RXUCn_MAXn                                                   63
#define HWIO_UFS_MEM_DBG_RD_REG_RXUCn_INI(n)                \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_REG_RXUCn_ADDR(n), HWIO_UFS_MEM_DBG_RD_REG_RXUCn_RMSK)
#define HWIO_UFS_MEM_DBG_RD_REG_RXUCn_INMI(n,mask)        \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_REG_RXUCn_ADDR(n), mask)
#define HWIO_UFS_MEM_DBG_RD_REG_RXUCn_UFS_DBG_RD_REG_RXUC_BMSK                       0xffffffff
#define HWIO_UFS_MEM_DBG_RD_REG_RXUCn_UFS_DBG_RD_REG_RXUC_SHFT                                0

#define HWIO_UFS_MEM_DBG_RD_REG_DFCn_ADDR(n)                                         (UFS_MEM_UFS_REG_BASE      + 0X900 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_REG_DFCn_OFFS(n)                                         (UFS_MEM_UFS_REG_BASE_OFFS + 0X900 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_REG_DFCn_RMSK                                            0xffffffff
#define HWIO_UFS_MEM_DBG_RD_REG_DFCn_MAXn                                                    63
#define HWIO_UFS_MEM_DBG_RD_REG_DFCn_INI(n)                \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_REG_DFCn_ADDR(n), HWIO_UFS_MEM_DBG_RD_REG_DFCn_RMSK)
#define HWIO_UFS_MEM_DBG_RD_REG_DFCn_INMI(n,mask)        \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_REG_DFCn_ADDR(n), mask)
#define HWIO_UFS_MEM_DBG_RD_REG_DFCn_UFS_DBG_RD_REG_DFC_BMSK                         0xffffffff
#define HWIO_UFS_MEM_DBG_RD_REG_DFCn_UFS_DBG_RD_REG_DFC_SHFT                                  0

#define HWIO_UFS_MEM_DBG_RD_REG_TRLUTn_ADDR(n)                                       (UFS_MEM_UFS_REG_BASE      + 0XA00 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_REG_TRLUTn_OFFS(n)                                       (UFS_MEM_UFS_REG_BASE_OFFS + 0XA00 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_REG_TRLUTn_RMSK                                          0xffffffff
#define HWIO_UFS_MEM_DBG_RD_REG_TRLUTn_MAXn                                                  63
#define HWIO_UFS_MEM_DBG_RD_REG_TRLUTn_INI(n)                \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_REG_TRLUTn_ADDR(n), HWIO_UFS_MEM_DBG_RD_REG_TRLUTn_RMSK)
#define HWIO_UFS_MEM_DBG_RD_REG_TRLUTn_INMI(n,mask)        \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_REG_TRLUTn_ADDR(n), mask)
#define HWIO_UFS_MEM_DBG_RD_REG_TRLUTn_UFS_DBG_RD_REG_TRLUT_BMSK                     0xffffffff
#define HWIO_UFS_MEM_DBG_RD_REG_TRLUTn_UFS_DBG_RD_REG_TRLUT_SHFT                              0

#define HWIO_UFS_MEM_DBG_RD_REG_TMRLUTn_ADDR(n)                                      (UFS_MEM_UFS_REG_BASE      + 0XB00 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_REG_TMRLUTn_OFFS(n)                                      (UFS_MEM_UFS_REG_BASE_OFFS + 0XB00 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_REG_TMRLUTn_RMSK                                         0xffffffff
#define HWIO_UFS_MEM_DBG_RD_REG_TMRLUTn_MAXn                                                 63
#define HWIO_UFS_MEM_DBG_RD_REG_TMRLUTn_INI(n)                \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_REG_TMRLUTn_ADDR(n), HWIO_UFS_MEM_DBG_RD_REG_TMRLUTn_RMSK)
#define HWIO_UFS_MEM_DBG_RD_REG_TMRLUTn_INMI(n,mask)        \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_REG_TMRLUTn_ADDR(n), mask)
#define HWIO_UFS_MEM_DBG_RD_REG_TMRLUTn_UFS_DBG_RD_REG_TMRLUT_BMSK                   0xffffffff
#define HWIO_UFS_MEM_DBG_RD_REG_TMRLUTn_UFS_DBG_RD_REG_TMRLUT_SHFT                            0

#define HWIO_UFS_MEM_DBG_RD_REG_OCSCn_ADDR(n)                                        (UFS_MEM_UFS_REG_BASE      + 0XC00 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_REG_OCSCn_OFFS(n)                                        (UFS_MEM_UFS_REG_BASE_OFFS + 0XC00 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_REG_OCSCn_RMSK                                           0xffffffff
#define HWIO_UFS_MEM_DBG_RD_REG_OCSCn_MAXn                                                   63
#define HWIO_UFS_MEM_DBG_RD_REG_OCSCn_INI(n)                \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_REG_OCSCn_ADDR(n), HWIO_UFS_MEM_DBG_RD_REG_OCSCn_RMSK)
#define HWIO_UFS_MEM_DBG_RD_REG_OCSCn_INMI(n,mask)        \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_REG_OCSCn_ADDR(n), mask)
#define HWIO_UFS_MEM_DBG_RD_REG_OCSCn_UFS_DBG_RD_REG_OCSC_BMSK                       0xffffffff
#define HWIO_UFS_MEM_DBG_RD_REG_OCSCn_UFS_DBG_RD_REG_OCSC_SHFT                                0

#define HWIO_UFS_MEM_DBG_RD_TX_BUFFn_ADDR(n)                                         (UFS_MEM_UFS_REG_BASE      + 0XD00 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_TX_BUFFn_OFFS(n)                                         (UFS_MEM_UFS_REG_BASE_OFFS + 0XD00 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_TX_BUFFn_RMSK                                            0xffffffff
#define HWIO_UFS_MEM_DBG_RD_TX_BUFFn_MAXn                                                   511
#define HWIO_UFS_MEM_DBG_RD_TX_BUFFn_INI(n)                \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_TX_BUFFn_ADDR(n), HWIO_UFS_MEM_DBG_RD_TX_BUFFn_RMSK)
#define HWIO_UFS_MEM_DBG_RD_TX_BUFFn_INMI(n,mask)        \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_TX_BUFFn_ADDR(n), mask)
#define HWIO_UFS_MEM_DBG_RD_TX_BUFFn_UFS_DBG_RD_TX_BUFF_BMSK                         0xffffffff
#define HWIO_UFS_MEM_DBG_RD_TX_BUFFn_UFS_DBG_RD_TX_BUFF_SHFT                                  0

#define HWIO_UFS_MEM_DBG_RD_RX_BUFFn_ADDR(n)                                         (UFS_MEM_UFS_REG_BASE      + 0X1500 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_RX_BUFFn_OFFS(n)                                         (UFS_MEM_UFS_REG_BASE_OFFS + 0X1500 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_RX_BUFFn_RMSK                                            0xffffffff
#define HWIO_UFS_MEM_DBG_RD_RX_BUFFn_MAXn                                                   255
#define HWIO_UFS_MEM_DBG_RD_RX_BUFFn_INI(n)                \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_RX_BUFFn_ADDR(n), HWIO_UFS_MEM_DBG_RD_RX_BUFFn_RMSK)
#define HWIO_UFS_MEM_DBG_RD_RX_BUFFn_INMI(n,mask)        \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_RX_BUFFn_ADDR(n), mask)
#define HWIO_UFS_MEM_DBG_RD_RX_BUFFn_UFS_DBG_RD_RX_BUFF_BMSK                         0xffffffff
#define HWIO_UFS_MEM_DBG_RD_RX_BUFFn_UFS_DBG_RD_RX_BUFF_SHFT                                  0

#define HWIO_UFS_MEM_DBG_RD_DESC_RAMn_ADDR(n)                                        (UFS_MEM_UFS_REG_BASE      + 0X1900 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_DESC_RAMn_OFFS(n)                                        (UFS_MEM_UFS_REG_BASE_OFFS + 0X1900 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_DESC_RAMn_RMSK                                           0xffffffff
#define HWIO_UFS_MEM_DBG_RD_DESC_RAMn_MAXn                                                  127
#define HWIO_UFS_MEM_DBG_RD_DESC_RAMn_INI(n)                \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_DESC_RAMn_ADDR(n), HWIO_UFS_MEM_DBG_RD_DESC_RAMn_RMSK)
#define HWIO_UFS_MEM_DBG_RD_DESC_RAMn_INMI(n,mask)        \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_DESC_RAMn_ADDR(n), mask)
#define HWIO_UFS_MEM_DBG_RD_DESC_RAMn_UFS_DBG_RD_DESC_RAM_BMSK                       0xffffffff
#define HWIO_UFS_MEM_DBG_RD_DESC_RAMn_UFS_DBG_RD_DESC_RAM_SHFT                                0

#define HWIO_UFS_MEM_DBG_RD_PRDT_RAMn_ADDR(n)                                        (UFS_MEM_UFS_REG_BASE      + 0X1B00 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_PRDT_RAMn_OFFS(n)                                        (UFS_MEM_UFS_REG_BASE_OFFS + 0X1B00 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_PRDT_RAMn_RMSK                                           0xffffffff
#define HWIO_UFS_MEM_DBG_RD_PRDT_RAMn_MAXn                                                   63
#define HWIO_UFS_MEM_DBG_RD_PRDT_RAMn_INI(n)                \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_PRDT_RAMn_ADDR(n), HWIO_UFS_MEM_DBG_RD_PRDT_RAMn_RMSK)
#define HWIO_UFS_MEM_DBG_RD_PRDT_RAMn_INMI(n,mask)        \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_PRDT_RAMn_ADDR(n), mask)
#define HWIO_UFS_MEM_DBG_RD_PRDT_RAMn_UFS_DBG_RD_PRDT_RAM_BMSK                       0xffffffff
#define HWIO_UFS_MEM_DBG_RD_PRDT_RAMn_UFS_DBG_RD_PRDT_RAM_SHFT                                0

#define HWIO_UFS_MEM_DBG_RD_RESP_RAMn_ADDR(n)                                        (UFS_MEM_UFS_REG_BASE      + 0X1C00 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_RESP_RAMn_OFFS(n)                                        (UFS_MEM_UFS_REG_BASE_OFFS + 0X1C00 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_RESP_RAMn_RMSK                                           0xffffffff
#define HWIO_UFS_MEM_DBG_RD_RESP_RAMn_MAXn                                                   63
#define HWIO_UFS_MEM_DBG_RD_RESP_RAMn_INI(n)                \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_RESP_RAMn_ADDR(n), HWIO_UFS_MEM_DBG_RD_RESP_RAMn_RMSK)
#define HWIO_UFS_MEM_DBG_RD_RESP_RAMn_INMI(n,mask)        \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_RESP_RAMn_ADDR(n), mask)
#define HWIO_UFS_MEM_DBG_RD_RESP_RAMn_UFS_DBG_RD_RESP_RAM_BMSK                       0xffffffff
#define HWIO_UFS_MEM_DBG_RD_RESP_RAMn_UFS_DBG_RD_RESP_RAM_SHFT                                0

#define HWIO_UFS_MEM_DBG_RD_EDTL_RAMn_ADDR(n)                                        (UFS_MEM_UFS_REG_BASE      + 0X1D00 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_EDTL_RAMn_OFFS(n)                                        (UFS_MEM_UFS_REG_BASE_OFFS + 0X1D00 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_EDTL_RAMn_RMSK                                           0xffffffff
#define HWIO_UFS_MEM_DBG_RD_EDTL_RAMn_MAXn                                                   31
#define HWIO_UFS_MEM_DBG_RD_EDTL_RAMn_INI(n)                \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_EDTL_RAMn_ADDR(n), HWIO_UFS_MEM_DBG_RD_EDTL_RAMn_RMSK)
#define HWIO_UFS_MEM_DBG_RD_EDTL_RAMn_INMI(n,mask)        \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_EDTL_RAMn_ADDR(n), mask)
#define HWIO_UFS_MEM_DBG_RD_EDTL_RAMn_UFS_DBG_RD_EDTL_RAM_BMSK                       0xffffffff
#define HWIO_UFS_MEM_DBG_RD_EDTL_RAMn_UFS_DBG_RD_EDTL_RAM_SHFT                                0

#define HWIO_UFS_MEM_DBG_RD_ICE_CNXT_RAMn_ADDR(n)                                    (UFS_MEM_UFS_REG_BASE      + 0X1E00 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_ICE_CNXT_RAMn_OFFS(n)                                    (UFS_MEM_UFS_REG_BASE_OFFS + 0X1E00 + (0x4*(n)))
#define HWIO_UFS_MEM_DBG_RD_ICE_CNXT_RAMn_RMSK                                       0xffffffff
#define HWIO_UFS_MEM_DBG_RD_ICE_CNXT_RAMn_MAXn                                              127
#define HWIO_UFS_MEM_DBG_RD_ICE_CNXT_RAMn_INI(n)                \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_ICE_CNXT_RAMn_ADDR(n), HWIO_UFS_MEM_DBG_RD_ICE_CNXT_RAMn_RMSK)
#define HWIO_UFS_MEM_DBG_RD_ICE_CNXT_RAMn_INMI(n,mask)        \
                in_dword_masked(HWIO_UFS_MEM_DBG_RD_ICE_CNXT_RAMn_ADDR(n), mask)
#define HWIO_UFS_MEM_DBG_RD_ICE_CNXT_RAMn_UFS_DBG_RD_ICE_CNXT_RAM_BMSK               0xffffffff
#define HWIO_UFS_MEM_DBG_RD_ICE_CNXT_RAMn_UFS_DBG_RD_ICE_CNXT_RAM_SHFT                        0

#define HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_ADDR(n)                                (UFS_MEM_UFS_REG_BASE      + 0X2400 + (0x4*(n)))
#define HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_OFFS(n)                                (UFS_MEM_UFS_REG_BASE_OFFS + 0X2400 + (0x4*(n)))
#define HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_RMSK                                   0x8000001f
#define HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_MAXn                                           31
#define HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_INI(n)                \
                in_dword_masked(HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_ADDR(n), HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_RMSK)
#define HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_INMI(n,mask)        \
                in_dword_masked(HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_ADDR(n), mask)
#define HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_OUTI(n,val)        \
                out_dword(HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_ADDR(n),val)
#define HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_OUTMI(n,mask,val) \
                out_dword_masked_ns(HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_ADDR(n),mask,val,HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_INI(n))
#define HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_HW_EVENT_EN_BMSK                       0x80000000
#define HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_HW_EVENT_EN_SHFT                               31
#define HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_HW_EVENT_SEL_BMSK                            0x1f
#define HWIO_UFS_MEM_HW_EVENT_MUX_SELECT_REGn_HW_EVENT_SEL_SHFT                               0

#define HWIO_UFS_MEM_ICE_CFG_ADDR                                                    (UFS_MEM_UFS_REG_BASE      + 0x2600)
#define HWIO_UFS_MEM_ICE_CFG_OFFS                                                    (UFS_MEM_UFS_REG_BASE_OFFS + 0x2600)
#define HWIO_UFS_MEM_ICE_CFG_RMSK                                                          0x7f
#define HWIO_UFS_MEM_ICE_CFG_IN                    \
                in_dword(HWIO_UFS_MEM_ICE_CFG_ADDR)
#define HWIO_UFS_MEM_ICE_CFG_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_ICE_CFG_ADDR, m)
#define HWIO_UFS_MEM_ICE_CFG_OUT(v)            \
                out_dword(HWIO_UFS_MEM_ICE_CFG_ADDR,v)
#define HWIO_UFS_MEM_ICE_CFG_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_ICE_CFG_ADDR,m,v,HWIO_UFS_MEM_ICE_CFG_IN)
#define HWIO_UFS_MEM_ICE_CFG_ICE_DBG_RAM_RD_FORCE_BMSK                                     0x40
#define HWIO_UFS_MEM_ICE_CFG_ICE_DBG_RAM_RD_FORCE_SHFT                                        6
#define HWIO_UFS_MEM_ICE_CFG_ICE_SYNC_RES_ACK_BMSK                                         0x20
#define HWIO_UFS_MEM_ICE_CFG_ICE_SYNC_RES_ACK_SHFT                                            5
#define HWIO_UFS_MEM_ICE_CFG_ICE_SYNC_RST_SW_BMSK                                          0x10
#define HWIO_UFS_MEM_ICE_CFG_ICE_SYNC_RST_SW_SHFT                                             4
#define HWIO_UFS_MEM_ICE_CFG_ICE_SYNC_RST_SEL_BMSK                                          0x8
#define HWIO_UFS_MEM_ICE_CFG_ICE_SYNC_RST_SEL_SHFT                                            3
#define HWIO_UFS_MEM_ICE_CFG_UFS_ICE_CNXT_RAM_PRIORITY_BMSK                                 0x7
#define HWIO_UFS_MEM_ICE_CFG_UFS_ICE_CNXT_RAM_PRIORITY_SHFT                                   0

#define HWIO_UFS_MEM_ICE_STAT_ADDR                                                   (UFS_MEM_UFS_REG_BASE      + 0x2604)
#define HWIO_UFS_MEM_ICE_STAT_OFFS                                                   (UFS_MEM_UFS_REG_BASE_OFFS + 0x2604)
#define HWIO_UFS_MEM_ICE_STAT_RMSK                                                          0x1
#define HWIO_UFS_MEM_ICE_STAT_IN                    \
                in_dword(HWIO_UFS_MEM_ICE_STAT_ADDR)
#define HWIO_UFS_MEM_ICE_STAT_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_ICE_STAT_ADDR, m)
#define HWIO_UFS_MEM_ICE_STAT_UFS_FUSE_ICE_DISABLE_BMSK                                     0x1
#define HWIO_UFS_MEM_ICE_STAT_UFS_FUSE_ICE_DISABLE_SHFT                                       0

#define HWIO_UFS_MEM_HW_H8_ENTER_CNT_ADDR                                            (UFS_MEM_UFS_REG_BASE      + 0x2700)
#define HWIO_UFS_MEM_HW_H8_ENTER_CNT_OFFS                                            (UFS_MEM_UFS_REG_BASE_OFFS + 0x2700)
#define HWIO_UFS_MEM_HW_H8_ENTER_CNT_RMSK                                                0xffff
#define HWIO_UFS_MEM_HW_H8_ENTER_CNT_IN                    \
                in_dword(HWIO_UFS_MEM_HW_H8_ENTER_CNT_ADDR)
#define HWIO_UFS_MEM_HW_H8_ENTER_CNT_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_HW_H8_ENTER_CNT_ADDR, m)
#define HWIO_UFS_MEM_HW_H8_ENTER_CNT_OUT(v)            \
                out_dword(HWIO_UFS_MEM_HW_H8_ENTER_CNT_ADDR,v)
#define HWIO_UFS_MEM_HW_H8_ENTER_CNT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_HW_H8_ENTER_CNT_ADDR,m,v,HWIO_UFS_MEM_HW_H8_ENTER_CNT_IN)
#define HWIO_UFS_MEM_HW_H8_ENTER_CNT_HW_H8_ENTER_CNT_BMSK                                0xffff
#define HWIO_UFS_MEM_HW_H8_ENTER_CNT_HW_H8_ENTER_CNT_SHFT                                     0

#define HWIO_UFS_MEM_SW_H8_ENTER_CNT_ADDR                                            (UFS_MEM_UFS_REG_BASE      + 0x2704)
#define HWIO_UFS_MEM_SW_H8_ENTER_CNT_OFFS                                            (UFS_MEM_UFS_REG_BASE_OFFS + 0x2704)
#define HWIO_UFS_MEM_SW_H8_ENTER_CNT_RMSK                                                0xffff
#define HWIO_UFS_MEM_SW_H8_ENTER_CNT_IN                    \
                in_dword(HWIO_UFS_MEM_SW_H8_ENTER_CNT_ADDR)
#define HWIO_UFS_MEM_SW_H8_ENTER_CNT_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_SW_H8_ENTER_CNT_ADDR, m)
#define HWIO_UFS_MEM_SW_H8_ENTER_CNT_OUT(v)            \
                out_dword(HWIO_UFS_MEM_SW_H8_ENTER_CNT_ADDR,v)
#define HWIO_UFS_MEM_SW_H8_ENTER_CNT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_SW_H8_ENTER_CNT_ADDR,m,v,HWIO_UFS_MEM_SW_H8_ENTER_CNT_IN)
#define HWIO_UFS_MEM_SW_H8_ENTER_CNT_SW_H8_ENTER_CNT_BMSK                                0xffff
#define HWIO_UFS_MEM_SW_H8_ENTER_CNT_SW_H8_ENTER_CNT_SHFT                                     0

#define HWIO_UFS_MEM_SW_AFTER_HW_H8_ENTER_CNT_ADDR                                   (UFS_MEM_UFS_REG_BASE      + 0x2708)
#define HWIO_UFS_MEM_SW_AFTER_HW_H8_ENTER_CNT_OFFS                                   (UFS_MEM_UFS_REG_BASE_OFFS + 0x2708)
#define HWIO_UFS_MEM_SW_AFTER_HW_H8_ENTER_CNT_RMSK                                       0xffff
#define HWIO_UFS_MEM_SW_AFTER_HW_H8_ENTER_CNT_IN                    \
                in_dword(HWIO_UFS_MEM_SW_AFTER_HW_H8_ENTER_CNT_ADDR)
#define HWIO_UFS_MEM_SW_AFTER_HW_H8_ENTER_CNT_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_SW_AFTER_HW_H8_ENTER_CNT_ADDR, m)
#define HWIO_UFS_MEM_SW_AFTER_HW_H8_ENTER_CNT_OUT(v)            \
                out_dword(HWIO_UFS_MEM_SW_AFTER_HW_H8_ENTER_CNT_ADDR,v)
#define HWIO_UFS_MEM_SW_AFTER_HW_H8_ENTER_CNT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_SW_AFTER_HW_H8_ENTER_CNT_ADDR,m,v,HWIO_UFS_MEM_SW_AFTER_HW_H8_ENTER_CNT_IN)
#define HWIO_UFS_MEM_SW_AFTER_HW_H8_ENTER_CNT_SW_AFTER_HW_H8_ENTER_CNT_BMSK              0xffff
#define HWIO_UFS_MEM_SW_AFTER_HW_H8_ENTER_CNT_SW_AFTER_HW_H8_ENTER_CNT_SHFT                   0

#define HWIO_UFS_MEM_HW_H8_EXIT_CNT_ADDR                                             (UFS_MEM_UFS_REG_BASE      + 0x270c)
#define HWIO_UFS_MEM_HW_H8_EXIT_CNT_OFFS                                             (UFS_MEM_UFS_REG_BASE_OFFS + 0x270c)
#define HWIO_UFS_MEM_HW_H8_EXIT_CNT_RMSK                                                 0xffff
#define HWIO_UFS_MEM_HW_H8_EXIT_CNT_IN                    \
                in_dword(HWIO_UFS_MEM_HW_H8_EXIT_CNT_ADDR)
#define HWIO_UFS_MEM_HW_H8_EXIT_CNT_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_HW_H8_EXIT_CNT_ADDR, m)
#define HWIO_UFS_MEM_HW_H8_EXIT_CNT_OUT(v)            \
                out_dword(HWIO_UFS_MEM_HW_H8_EXIT_CNT_ADDR,v)
#define HWIO_UFS_MEM_HW_H8_EXIT_CNT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_HW_H8_EXIT_CNT_ADDR,m,v,HWIO_UFS_MEM_HW_H8_EXIT_CNT_IN)
#define HWIO_UFS_MEM_HW_H8_EXIT_CNT_HW_H8_EXIT_CNT_BMSK                                  0xffff
#define HWIO_UFS_MEM_HW_H8_EXIT_CNT_HW_H8_EXIT_CNT_SHFT                                       0

#define HWIO_UFS_MEM_SW_H8_EXIT_CNT_ADDR                                             (UFS_MEM_UFS_REG_BASE      + 0x2710)
#define HWIO_UFS_MEM_SW_H8_EXIT_CNT_OFFS                                             (UFS_MEM_UFS_REG_BASE_OFFS + 0x2710)
#define HWIO_UFS_MEM_SW_H8_EXIT_CNT_RMSK                                                 0xffff
#define HWIO_UFS_MEM_SW_H8_EXIT_CNT_IN                    \
                in_dword(HWIO_UFS_MEM_SW_H8_EXIT_CNT_ADDR)
#define HWIO_UFS_MEM_SW_H8_EXIT_CNT_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_SW_H8_EXIT_CNT_ADDR, m)
#define HWIO_UFS_MEM_SW_H8_EXIT_CNT_OUT(v)            \
                out_dword(HWIO_UFS_MEM_SW_H8_EXIT_CNT_ADDR,v)
#define HWIO_UFS_MEM_SW_H8_EXIT_CNT_OUTM(m,v) \
                out_dword_masked_ns(HWIO_UFS_MEM_SW_H8_EXIT_CNT_ADDR,m,v,HWIO_UFS_MEM_SW_H8_EXIT_CNT_IN)
#define HWIO_UFS_MEM_SW_H8_EXIT_CNT_SW_H8_EXIT_CNT_BMSK                                  0xffff
#define HWIO_UFS_MEM_SW_H8_EXIT_CNT_SW_H8_EXIT_CNT_SHFT                                       0

/*----------------------------------------------------------------------------
 * MODULE: UFS_MEM_ICE_REGS
 *--------------------------------------------------------------------------*/

#define UFS_MEM_ICE_REGS_REG_BASE                                                                 (UFS_MEM_UFS_2LANE_REGS_BASE      + 0x00008000)
#define UFS_MEM_ICE_REGS_REG_BASE_SIZE                                                            0x2000
#define UFS_MEM_ICE_REGS_REG_BASE_USED                                                            0x125c
#define UFS_MEM_ICE_REGS_REG_BASE_OFFS                                                            0x00008000

#define HWIO_UFS_MEM_ICE_PARAMETERS_1_ADDR                                                        (UFS_MEM_ICE_REGS_REG_BASE      + 0x14)
#define HWIO_UFS_MEM_ICE_PARAMETERS_1_OFFS                                                        (UFS_MEM_ICE_REGS_REG_BASE_OFFS + 0x14)
#define HWIO_UFS_MEM_ICE_PARAMETERS_1_RMSK                                                        0xffffff07
#define HWIO_UFS_MEM_ICE_PARAMETERS_1_IN                    \
                in_dword(HWIO_UFS_MEM_ICE_PARAMETERS_1_ADDR)
#define HWIO_UFS_MEM_ICE_PARAMETERS_1_INM(m)            \
                in_dword_masked(HWIO_UFS_MEM_ICE_PARAMETERS_1_ADDR, m)
#define HWIO_UFS_MEM_ICE_PARAMETERS_1_DATA_WIDTH_BMSK                                             0xff000000
#define HWIO_UFS_MEM_ICE_PARAMETERS_1_DATA_WIDTH_SHFT                                                     24
#define HWIO_UFS_MEM_ICE_PARAMETERS_1_CDU_NUM_WIDTH_BMSK                                            0xff0000
#define HWIO_UFS_MEM_ICE_PARAMETERS_1_CDU_NUM_WIDTH_SHFT                                                  16
#define HWIO_UFS_MEM_ICE_PARAMETERS_1_DBO_WIDTH_BMSK                                                  0xff00
#define HWIO_UFS_MEM_ICE_PARAMETERS_1_DBO_WIDTH_SHFT                                                       8
#define HWIO_UFS_MEM_ICE_PARAMETERS_1_ASYNC_CLIENT_CORE_CLKS_BMSK                                        0x4
#define HWIO_UFS_MEM_ICE_PARAMETERS_1_ASYNC_CLIENT_CORE_CLKS_SHFT                                          2
#define HWIO_UFS_MEM_ICE_PARAMETERS_1_QRIB_EN_BMSK                                                       0x2
#define HWIO_UFS_MEM_ICE_PARAMETERS_1_QRIB_EN_SHFT                                                         1
#define HWIO_UFS_MEM_ICE_PARAMETERS_1_NUM_OF_STREAMS_BMSK                                                0x1
#define HWIO_UFS_MEM_ICE_PARAMETERS_1_NUM_OF_STREAMS_SHFT                                                  0

/*----------------------------------------------------------------------------
 * MODULE: TLMM_REG
 *--------------------------------------------------------------------------*/

#define TLMM_REG_REG_BASE                                                        (TLMM_BASE      + 0x00100000)
#define TLMM_REG_REG_BASE_SIZE                                                   0xf00000
#define TLMM_REG_REG_BASE_USED                                                   0xd301c
#define TLMM_REG_REG_BASE_OFFS                                                   0x00100000

#define HWIO_TLMM_UFS_RESET_CTL_ADDR                                             (TLMM_REG_REG_BASE      + 0xb4004)
#define HWIO_TLMM_UFS_RESET_CTL_OFFS                                             (TLMM_REG_REG_BASE_OFFS + 0xb4004)
#define HWIO_TLMM_UFS_RESET_CTL_RMSK                                                   0x1f
#define HWIO_TLMM_UFS_RESET_CTL_IN                    \
                in_dword(HWIO_TLMM_UFS_RESET_CTL_ADDR)
#define HWIO_TLMM_UFS_RESET_CTL_INM(m)            \
                in_dword_masked(HWIO_TLMM_UFS_RESET_CTL_ADDR, m)
#define HWIO_TLMM_UFS_RESET_CTL_OUT(v)            \
                out_dword(HWIO_TLMM_UFS_RESET_CTL_ADDR,v)
#define HWIO_TLMM_UFS_RESET_CTL_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TLMM_UFS_RESET_CTL_ADDR,m,v,HWIO_TLMM_UFS_RESET_CTL_IN)
#define HWIO_TLMM_UFS_RESET_CTL_UFS_RESET_PULL_BMSK                                    0x18
#define HWIO_TLMM_UFS_RESET_CTL_UFS_RESET_PULL_SHFT                                       3
#define HWIO_TLMM_UFS_RESET_CTL_UFS_RESET_HDRV_BMSK                                     0x7
#define HWIO_TLMM_UFS_RESET_CTL_UFS_RESET_HDRV_SHFT                                       0

#define HWIO_TLMM_UFS_RESET_ADDR                                                 (TLMM_REG_REG_BASE      + 0xb5000)
#define HWIO_TLMM_UFS_RESET_OFFS                                                 (TLMM_REG_REG_BASE_OFFS + 0xb5000)
#define HWIO_TLMM_UFS_RESET_RMSK                                                        0x1
#define HWIO_TLMM_UFS_RESET_IN                    \
                in_dword(HWIO_TLMM_UFS_RESET_ADDR)
#define HWIO_TLMM_UFS_RESET_INM(m)            \
                in_dword_masked(HWIO_TLMM_UFS_RESET_ADDR, m)
#define HWIO_TLMM_UFS_RESET_OUT(v)            \
                out_dword(HWIO_TLMM_UFS_RESET_ADDR,v)
#define HWIO_TLMM_UFS_RESET_OUTM(m,v) \
                out_dword_masked_ns(HWIO_TLMM_UFS_RESET_ADDR,m,v,HWIO_TLMM_UFS_RESET_IN)
#define HWIO_TLMM_UFS_RESET_UFS_RESET_BMSK                                              0x1
#define HWIO_TLMM_UFS_RESET_UFS_RESET_SHFT                                                0

/*----------------------------------------------------------------------------
 * MODULE: GCC_CLK_CTL_REG
 *--------------------------------------------------------------------------*/

#define GCC_CLK_CTL_REG_REG_BASE                                                                        (CLK_CTL_BASE      + 0x00010000)
#define GCC_CLK_CTL_REG_REG_BASE_SIZE                                                                   0x1e0000
#define GCC_CLK_CTL_REG_REG_BASE_USED                                                                   0xa1204
#define GCC_CLK_CTL_REG_REG_BASE_OFFS                                                                   0x00010000

#define HWIO_GCC_UFS_PHY_BCR_ADDR                                                                       (GCC_CLK_CTL_REG_REG_BASE      + 0x67000)
#define HWIO_GCC_UFS_PHY_BCR_OFFS                                                                       (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x67000)
#define HWIO_GCC_UFS_PHY_BCR_RMSK                                                                              0x1
#define HWIO_GCC_UFS_PHY_BCR_IN                    \
                in_dword(HWIO_GCC_UFS_PHY_BCR_ADDR)
#define HWIO_GCC_UFS_PHY_BCR_INM(m)            \
                in_dword_masked(HWIO_GCC_UFS_PHY_BCR_ADDR, m)
#define HWIO_GCC_UFS_PHY_BCR_OUT(v)            \
                out_dword(HWIO_GCC_UFS_PHY_BCR_ADDR,v)
#define HWIO_GCC_UFS_PHY_BCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_UFS_PHY_BCR_ADDR,m,v,HWIO_GCC_UFS_PHY_BCR_IN)
#define HWIO_GCC_UFS_PHY_BCR_BLK_ARES_BMSK                                                                     0x1
#define HWIO_GCC_UFS_PHY_BCR_BLK_ARES_SHFT                                                                       0

/*----------------------------------------------------------------------------
 * MODULE: SLP_CNTR
 *--------------------------------------------------------------------------*/

#define SLP_CNTR_REG_BASE                                    (AOSS_BASE      + 0x01221000)
#define SLP_CNTR_REG_BASE_SIZE                               0x1000
#define SLP_CNTR_REG_BASE_USED                               0x0
#define SLP_CNTR_REG_BASE_OFFS                               0x01221000

#define HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_ADDR               (SLP_CNTR_REG_BASE      + 0x0)
#define HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_OFFS               (SLP_CNTR_REG_BASE_OFFS + 0x0)
#define HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_RMSK               0xffffffff
#define HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_IN                    \
                in_dword(HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_ADDR)
#define HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_INM(m)            \
                in_dword_masked(HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_ADDR, m)
#define HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_DATA_BMSK          0xffffffff
#define HWIO_MPM_SLEEP_TIMETICK_COUNT_VAL_DATA_SHFT                   0


/* Define the required HWIO input/out macro mapping */

#define HWIO_REG_IN(base, reg)                           \
        (in_dword((base + HWIO_##reg##_OFFS)))
#define HWIO_REG_OUT(base, reg, v)                       \
        (out_dword((base + HWIO_##reg##_OFFS),v))
#define HWIO_REG_INF(base, reg, offs)                           \
        (in_dword((base + HWIO_##reg##_OFFS + offs)))
#define HWIO_REG_OUTF(base, reg, offs,v)                       \
        (out_dword((base + HWIO_##reg##_OFFS + offs),v))
#define HWIO_REG_OUTM(base, reg, m, v)                   \
        (out_dword((base + HWIO_##reg##_OFFS),  \
        ((in_dword((base + HWIO_##reg##_OFFS)) & (m)) | (v))))
#define HWIO_REG_BMSK(reg)   (HWIO_##reg##_BMSK)
#define HWIO_REG_SHFT(reg)   (HWIO_##reg##_SHFT)


#endif /* __UFSHWIOALL__ */
