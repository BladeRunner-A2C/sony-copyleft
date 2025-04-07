#ifndef PLATFORMINFOHWIO_H
#define PLATFORMINFOHWIO_H
/*
===========================================================================
*/
/**
    @file PlatformInfoHWIO.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        Palawan [palawan_v1.0_p2q0r18.2_rtl_partition]
 
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

#define PLATFORMINFO_TCSR_SOC_EMULATION_TYPE    TCSR_SOC_EMULATION_TYPE


/*----------------------------------------------------------------------------
 * MODULE: TCSR_TCSR_REGS
 *--------------------------------------------------------------------------*/

#define TCSR_TCSR_REGS_REG_BASE                                                                                                                                  (CORE_TOP_CSR_BASE      + 0x00040000)
#define TCSR_TCSR_REGS_REG_BASE_SIZE                                                                                                                             0xc0000
#define TCSR_TCSR_REGS_REG_BASE_USED                                                                                                                             0xb8000

#define HWIO_TCSR_SOC_EMULATION_TYPE_ADDR                                                                                                                        (TCSR_TCSR_REGS_REG_BASE      + 0x88004)
#define HWIO_TCSR_SOC_EMULATION_TYPE_RMSK                                                                                                                               0x3
#define HWIO_TCSR_SOC_EMULATION_TYPE_IN                    \
                in_dword(HWIO_TCSR_SOC_EMULATION_TYPE_ADDR)
#define HWIO_TCSR_SOC_EMULATION_TYPE_INM(m)            \
                in_dword_masked(HWIO_TCSR_SOC_EMULATION_TYPE_ADDR, m)
#define HWIO_TCSR_SOC_EMULATION_TYPE_SOC_EMULATION_TYPE_BMSK                                                                                                            0x3
#define HWIO_TCSR_SOC_EMULATION_TYPE_SOC_EMULATION_TYPE_SHFT                                                                                                              0


#endif /* PLATFORMINFOHWIO_H */
