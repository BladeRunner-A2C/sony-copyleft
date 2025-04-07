#ifndef __QUP_ADRESSES_H__
#define __QUP_ADRESSES_H__

/*=============================================================================   
    @file  qup_address_ranges.h
    @brief interface to device configuration
   
    Copyright (c) 2022, 2023 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.
===============================================================================*/

/*=============================================================================
                              EDIT HISTORY
 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/07/23   STR     Updated for Palawan
 02/13/23   sy      Added for Palawan
 04/11/22   RK      Added for Lanai.
=============================================================================*/

#include "msmhwiobase.h"

#define QUP_0   0
#define QUP_1   1
#define QUP_2   2

#define QUP0_BASE_ADDRESS_START     QUPV3_0_QUPV3_ID_1_BASE
#define QUP0_BASE_ADDRESS_END       (QUP0_BASE_ADDRESS_START + QUPV3_0_QUPV3_ID_1_BASE_SIZE)
#define QUP0_COMMON_ADDRESS         (QUP0_BASE_ADDRESS_START + 0xC0000)

#define QUP1_BASE_ADDRESS_START     QUPV3_1_QUPV3_ID_2_BASE
#define QUP1_BASE_ADDRESS_END       (QUP1_BASE_ADDRESS_START + QUPV3_1_QUPV3_ID_2_BASE_SIZE)
#define QUP1_COMMON_ADDRESS         (QUP1_BASE_ADDRESS_START + 0xC0000)

#define QUP2_BASE_ADDRESS_START     0
#define QUP2_BASE_ADDRESS_END       0
#define QUP2_COMMON_ADDRESS         0

#define TCSR_TCSR_REG_ADDRESS_START 0x01FC0000
#define TCSR_TCSR_REG_ADDRESS_END   (TCSR_TCSR_REG_ADDRESS_START + 0xC0000)

#endif // __QUP_ADRESSES_H__

