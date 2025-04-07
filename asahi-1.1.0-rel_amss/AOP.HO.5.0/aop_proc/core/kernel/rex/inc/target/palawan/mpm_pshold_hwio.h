#ifndef __MPM_PSHOLD_HWIO_H__
#define __MPM_PSHOLD_HWIO_H__
/*
===========================================================================
*/
/**
  @file mpm_pshold_hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    Palawan [ palawan_v1.0_p3q3r56_rtl_partition_MTO]
 
  This file contains HWIO register definitions for the following modules:
    MPM_POWER_STATE_HOLD


  Generation parameters: 
  { 'filename': 'mpm_pshold_hwio.h',
    'header': '#include "msmhwiobase.h"\n\n',
    'modules': ['MPM_POWER_STATE_HOLD']}
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
 * MODULE: MPM_POWER_STATE_HOLD
 *--------------------------------------------------------------------------*/

#define MPM_POWER_STATE_HOLD_REG_BASE             (AOSS_BASE      + 0x01264000)
#define MPM_POWER_STATE_HOLD_REG_BASE_SIZE        0x1000
#define MPM_POWER_STATE_HOLD_REG_BASE_USED        0x0

#define HWIO_MPM_PS_HOLD_ADDR                     (MPM_POWER_STATE_HOLD_REG_BASE      + 0x00000000)
#define HWIO_MPM_PS_HOLD_RMSK                            0x1
#define HWIO_MPM_PS_HOLD_IN          \
        in_dword(HWIO_MPM_PS_HOLD_ADDR)
#define HWIO_MPM_PS_HOLD_INM(m)      \
        in_dword_masked(HWIO_MPM_PS_HOLD_ADDR, m)
#define HWIO_MPM_PS_HOLD_OUT(v)      \
        out_dword(HWIO_MPM_PS_HOLD_ADDR,v)
#define HWIO_MPM_PS_HOLD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MPM_PS_HOLD_ADDR,m,v,HWIO_MPM_PS_HOLD_IN)
#define HWIO_MPM_PS_HOLD_PSHOLD_MPM_BMSK                 0x1
#define HWIO_MPM_PS_HOLD_PSHOLD_MPM_SHFT                 0x0


#endif /* __MPM_PSHOLD_HWIO_H__ */
