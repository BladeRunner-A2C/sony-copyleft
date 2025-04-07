#ifndef __ARC_VT_HWIO_H__
#define __ARC_VT_HWIO_H__
/*
===========================================================================
*/
/**
  @file arc_vt_hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    Palawan [ palawan_v1.0_p3q3r56_rtl_partition_MTO]
 
  This file contains HWIO register definitions for the following modules:
    RPMH_ARC_ARC_VT


  Generation parameters: 
  { 'filename': 'arc_vt_hwio.h',
    'header': '#include "msmhwiobase.h"\n\n',
    'modules': ['RPMH_ARC_ARC_VT'],
    'output-fvals': True,
    'output-offsets': True,
    'rmsk-input': True}
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
 * MODULE: RPMH_ARC_ARC_VT
 *--------------------------------------------------------------------------*/

#define RPMH_ARC_ARC_VT_REG_BASE                                                (AOSS_BASE      + 0x00600000)
#define RPMH_ARC_ARC_VT_REG_BASE_SIZE                                           0x1f0000
#define RPMH_ARC_ARC_VT_REG_BASE_USED                                           0x1dd0d8
#define RPMH_ARC_ARC_VT_REG_BASE_OFFS                                           0x00600000

#define HWIO_RPMH_ARC_DRVd_RMm_VOTE_ADDR(d,m)                                   (RPMH_ARC_ARC_VT_REG_BASE      + 0x00000000 + 0x10000 * (d) + 0x10 * (m))
#define HWIO_RPMH_ARC_DRVd_RMm_VOTE_OFFS(d,m)                                   (RPMH_ARC_ARC_VT_REG_BASE_OFFS + 0x00000000 + 0x10000 * (d) + 0x10 * (m))
#define HWIO_RPMH_ARC_DRVd_RMm_VOTE_RMSK                                        0x8000000f
#define HWIO_RPMH_ARC_DRVd_RMm_VOTE_MAXd                                                25
#define HWIO_RPMH_ARC_DRVd_RMm_VOTE_MAXm                                                13
#define HWIO_RPMH_ARC_DRVd_RMm_VOTE_INI2(d,m)        \
        in_dword_masked(HWIO_RPMH_ARC_DRVd_RMm_VOTE_ADDR(d,m), HWIO_RPMH_ARC_DRVd_RMm_VOTE_RMSK)
#define HWIO_RPMH_ARC_DRVd_RMm_VOTE_INMI2(d,m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_DRVd_RMm_VOTE_ADDR(d,m), mask)
#define HWIO_RPMH_ARC_DRVd_RMm_VOTE_OUTI2(d,m,val)    \
        out_dword(HWIO_RPMH_ARC_DRVd_RMm_VOTE_ADDR(d,m),val)
#define HWIO_RPMH_ARC_DRVd_RMm_VOTE_OUTMI2(d,m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_DRVd_RMm_VOTE_ADDR(d,m),mask,val,HWIO_RPMH_ARC_DRVd_RMm_VOTE_INI2(d,m))
#define HWIO_RPMH_ARC_DRVd_RMm_VOTE_RR_BMSK                                     0x80000000
#define HWIO_RPMH_ARC_DRVd_RMm_VOTE_RR_SHFT                                           0x1f
#define HWIO_RPMH_ARC_DRVd_RMm_VOTE_OL_BMSK                                            0xf
#define HWIO_RPMH_ARC_DRVd_RMm_VOTE_OL_SHFT                                            0x0

#define HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_ADDR(d,m)                               (RPMH_ARC_ARC_VT_REG_BASE      + 0x001d0000 + 0x1000 * (d) + 0x10 * (m))
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_OFFS(d,m)                               (RPMH_ARC_ARC_VT_REG_BASE_OFFS + 0x001d0000 + 0x1000 * (d) + 0x10 * (m))
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_RMSK                                    0x8000000f
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_MAXd                                            13
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_MAXm                                            13
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_INI2(d,m)        \
        in_dword_masked(HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_ADDR(d,m), HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_RMSK)
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_INMI2(d,m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_ADDR(d,m), mask)
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_OUTI2(d,m,val)    \
        out_dword(HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_ADDR(d,m),val)
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_OUTMI2(d,m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_ADDR(d,m),mask,val,HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_INI2(d,m))
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_RR_BMSK                                 0x80000000
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_RR_SHFT                                       0x1f
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_OL_BMSK                                        0xf
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_VOTE_OL_SHFT                                        0x0

#define HWIO_RPMH_ARC_DRVd_RMm_TIMER_ADDR(d,m)                                  (RPMH_ARC_ARC_VT_REG_BASE      + 0x00000004 + 0x10000 * (d) + 0x10 * (m))
#define HWIO_RPMH_ARC_DRVd_RMm_TIMER_OFFS(d,m)                                  (RPMH_ARC_ARC_VT_REG_BASE_OFFS + 0x00000004 + 0x10000 * (d) + 0x10 * (m))
#define HWIO_RPMH_ARC_DRVd_RMm_TIMER_RMSK                                              0x1
#define HWIO_RPMH_ARC_DRVd_RMm_TIMER_MAXd                                               25
#define HWIO_RPMH_ARC_DRVd_RMm_TIMER_MAXm                                               13
#define HWIO_RPMH_ARC_DRVd_RMm_TIMER_INI2(d,m)        \
        in_dword_masked(HWIO_RPMH_ARC_DRVd_RMm_TIMER_ADDR(d,m), HWIO_RPMH_ARC_DRVd_RMm_TIMER_RMSK)
#define HWIO_RPMH_ARC_DRVd_RMm_TIMER_INMI2(d,m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_DRVd_RMm_TIMER_ADDR(d,m), mask)
#define HWIO_RPMH_ARC_DRVd_RMm_TIMER_OUTI2(d,m,val)    \
        out_dword(HWIO_RPMH_ARC_DRVd_RMm_TIMER_ADDR(d,m),val)
#define HWIO_RPMH_ARC_DRVd_RMm_TIMER_OUTMI2(d,m,mask,val) \
        out_dword_masked_ns(HWIO_RPMH_ARC_DRVd_RMm_TIMER_ADDR(d,m),mask,val,HWIO_RPMH_ARC_DRVd_RMm_TIMER_INI2(d,m))
#define HWIO_RPMH_ARC_DRVd_RMm_TIMER_TIMER_CONSIDERED_BMSK                             0x1
#define HWIO_RPMH_ARC_DRVd_RMm_TIMER_TIMER_CONSIDERED_SHFT                             0x0

#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_ADDR(d,m)                          (RPMH_ARC_ARC_VT_REG_BASE      + 0x00000008 + 0x10000 * (d) + 0x10 * (m))
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_OFFS(d,m)                          (RPMH_ARC_ARC_VT_REG_BASE_OFFS + 0x00000008 + 0x10000 * (d) + 0x10 * (m))
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_RMSK                               0xfffff001
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_MAXd                                       25
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_MAXm                                       13
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_INI2(d,m)        \
        in_dword_masked(HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_ADDR(d,m), HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_RMSK)
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_INMI2(d,m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_ADDR(d,m), mask)
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_DESTINATION_OL_BMSK                0xf0000000
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_DESTINATION_OL_SHFT                      0x1c
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_SEQUENCE_OL_BMSK                    0xf000000
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_SEQUENCE_OL_SHFT                         0x18
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_AGGREGATED_OL_BMSK                   0xf00000
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_AGGREGATED_OL_SHFT                       0x14
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_SOLVED_OL_BMSK                        0xf0000
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_SOLVED_OL_SHFT                           0x10
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_CURRENT_OL_BMSK                        0xf000
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_CURRENT_OL_SHFT                           0xc
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_RESPONSE_PENDING_BMSK                     0x1
#define HWIO_RPMH_ARC_DRVd_RMm_SHADOW_STATUS_RESPONSE_PENDING_SHFT                     0x0

#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_ADDR(d,m)                      (RPMH_ARC_ARC_VT_REG_BASE      + 0x001d0008 + 0x1000 * (d) + 0x10 * (m))
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_OFFS(d,m)                      (RPMH_ARC_ARC_VT_REG_BASE_OFFS + 0x001d0008 + 0x1000 * (d) + 0x10 * (m))
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_RMSK                           0xfffff001
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_MAXd                                   13
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_MAXm                                   13
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_INI2(d,m)        \
        in_dword_masked(HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_ADDR(d,m), HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_RMSK)
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_INMI2(d,m,mask)    \
        in_dword_masked(HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_ADDR(d,m), mask)
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_DESTINATION_OL_BMSK            0xf0000000
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_DESTINATION_OL_SHFT                  0x1c
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_SEQUENCE_OL_BMSK                0xf000000
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_SEQUENCE_OL_SHFT                     0x18
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_AGGREGATED_OL_BMSK               0xf00000
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_AGGREGATED_OL_SHFT                   0x14
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_SOLVED_OL_BMSK                    0xf0000
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_SOLVED_OL_SHFT                       0x10
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_CURRENT_OL_BMSK                    0xf000
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_CURRENT_OL_SHFT                       0xc
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_RESPONSE_PENDING_BMSK                 0x1
#define HWIO_RPMH_ARC_BCM_DRVd_RMm_SHADOW_STATUS_RESPONSE_PENDING_SHFT                 0x0


#endif /* __ARC_VT_HWIO_H__ */
