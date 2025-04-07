#ifndef __QUP_ADRESSES_H__
#define __QUP_ADRESSES_H__

/*=============================================================================   
    @file  qup_address_ranges.h
    @brief interface to device configuration
   
    Copyright (c) 2022 - 2023 Qualcomm Technologies, Inc.
                        All rights reserved.
    Confidential and Proprietary - Qualcomm Technologies, Inc

===============================================================================*/

/*=============================================================================
                              EDIT HISTORY
 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 10/18/23   GST     Updated QUP0 Base address
 04/11/22   RK      Added for Milos.
=============================================================================*/

#include "msmhwiobase.h"

#define QUP_0   0
#define QUP_1   1
#define QUP_2   2

#define QUP0_BASE_ADDRESS_START		 QUPV3_0_QUPV3_ID_1_BASE
#define QUP0_BASE_ADDRESS_END		(QUP0_BASE_ADDRESS_START + QUPV3_0_QUPV3_ID_1_BASE_SIZE)
#define QUP0_COMMON_ADDRESS			(QUP0_BASE_ADDRESS_START + 0xC0000)

#define QUP1_BASE_ADDRESS_START		 QUPV3_1_QUPV3_ID_1_BASE
#define QUP1_BASE_ADDRESS_END		(QUP1_BASE_ADDRESS_START + QUPV3_1_QUPV3_ID_1_BASE_SIZE)
#define QUP1_COMMON_ADDRESS			(QUP1_BASE_ADDRESS_START + 0xC0000)

#define QUP2_BASE_ADDRESS_START		0
#define QUP2_BASE_ADDRESS_END		0
#define QUP2_COMMON_ADDRESS			0

#define TCSR_TCSR_REG_ADDRESS_START	 0x01F40000
#define TCSR_TCSR_REG_ADDRESS_END	(TCSR_TCSR_REG_ADDRESS_START + 0xC0000)

#endif // __QUP_ADRESSES_H__

