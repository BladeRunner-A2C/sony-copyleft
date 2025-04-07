#ifndef __PLATFORMINFOHWIO_H__
#define __PLATFORMINFOHWIO_H__
/*
===========================================================================
*/
/**
    @file PlatformInfoHWIO.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8650 (Lanai) [z_lanai_prj_v1.0_p2q0r6.15_rtl_partition]
 
    This file contains HWIO register definitions for the following modules:
        TCSR_TCSR_REGS

    'Include' filters applied: TCSR_SOC_EMULATION_TYPE[TCSR_TCSR_REGS] 

    Generation parameters: 
    { 'exclude-reserved': True,
      'filename': 'PlatformInfoHWIO.h',
      'header': '\n'
                '#include "msmhwiobase.h"\n'
                '\n'
                '#define PLATFORMINFO_TCSR_SOC_EMULATION_TYPE    '
                'TCSR_SOC_EMULATION_TYPE\n',
      'module-filter-exclude': {},
      'module-filter-include': {'TCSR_TCSR_REGS': ['TCSR_SOC_EMULATION_TYPE']},
      'modules': ['TCSR_TCSR_REGS']}
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

    $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/SocPkg/Lanai/Include/PlatformInfoHWIO.h#1 $
    $DateTime: 2024/04/02 23:00:31 $
    $Author: cirrusp4svc $

    ===========================================================================
*/


#include "msmhwiobase.h"

#define PLATFORMINFO_TCSR_SOC_EMULATION_TYPE    TCSR_SOC_EMULATION_TYPE


/*----------------------------------------------------------------------------
 * MODULE: TCSR_TCSR_REGS
 *--------------------------------------------------------------------------*/

#define TCSR_TCSR_REGS_REG_BASE                                                                                                                                  (CORE_TOP_CSR_BASE      + 0x00040000)
#define TCSR_TCSR_REGS_REG_BASE_SIZE                                                                                                                             0xc0000
#define TCSR_TCSR_REGS_REG_BASE_USED                                                                                                                             0xbb000

#define HWIO_TCSR_SOC_EMULATION_TYPE_ADDR                                                                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x88004)
#define HWIO_TCSR_SOC_EMULATION_TYPE_RMSK                                                                                                                               0x3
#define HWIO_TCSR_SOC_EMULATION_TYPE_IN                    \
                in_dword(HWIO_TCSR_SOC_EMULATION_TYPE_ADDR)
#define HWIO_TCSR_SOC_EMULATION_TYPE_INM(m)            \
                in_dword_masked(HWIO_TCSR_SOC_EMULATION_TYPE_ADDR, m)
#define HWIO_TCSR_SOC_EMULATION_TYPE_SOC_EMULATION_TYPE_BMSK                                                                                                            0x3
#define HWIO_TCSR_SOC_EMULATION_TYPE_SOC_EMULATION_TYPE_SHFT                                                                                                              0


#endif /* __PLATFORMINFOHWIO_H__ */
