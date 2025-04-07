/** 
    @file  qup_hal.h
    @brief qup HWIO abstraction macros
 */
/*=============================================================================
            Copyright (c) 2023 Qualcomm Technologies, Incorporated.
                              All rights reserved.
              Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
                              EDIT HISTORY
 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 02/14/23   gkr     Added intial revision
=============================================================================*/
#ifndef __QUP_HAL_H__
#define __QUP_HAL_H__

#include "HALqupv3SeHwio.h"

#define GENI_CFG_BASE(se_base)               se_base + (GENI4_CFG_REG_BASE_OFFS - SE0_REG_BASE_OFFS)
#define GENI_IMAGE_REGS_BASE(se_base)        se_base + (GENI4_IMAGE_REGS_REG_BASE_OFFS - SE0_REG_BASE_OFFS)
#define GENI_DATA_BASE(se_base)              se_base + (GENI4_DATA_REG_BASE_OFFS - SE0_REG_BASE_OFFS)
#define GENI_SE_DMA_BASE(se_base)            se_base + (QUPV3_SE_DMA_REG_BASE_OFFS - SE0_REG_BASE_OFFS)
#define GENI_IMAGE_BASE(se_base)             se_base + (GENI4_IMAGE_REG_BASE_OFFS - SE0_REG_BASE_OFFS)
#define GENI_SE_SEC_BASE(se_base)            se_base + (QUPV3_SEC_REG_BASE_OFFS - SE0_REG_BASE_OFFS)

#endif