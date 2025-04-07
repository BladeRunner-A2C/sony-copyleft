/** 
    @file  spi_hal.h
    @brief HW io abstraction macros
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

#ifndef __SPI_HAL_H__
#define __SPI_HAL_H__

#include "spi_types.h"
#include "HALhwio.h"
#include "HALqupv3CommonHwio.h"
#include "HALqupv3SeHwio.h"
#include "qup_hal.h"


#define FLD_SET(reg, field, data) \
    (((uint32) data << (uint32) HWIO_SHFT(reg, field)) & (uint32) HWIO_FMSK(reg, field))

#define FLD_GET(data, reg, field) \
    ((data & HWIO_FMSK(reg, field)) >> HWIO_SHFT(reg, field))


#endif
