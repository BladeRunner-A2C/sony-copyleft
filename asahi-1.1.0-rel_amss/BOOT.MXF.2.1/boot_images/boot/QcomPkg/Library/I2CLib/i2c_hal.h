/** 
    @file  i2c_hal.h
    @brief HWIO macros
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

#ifndef __I2C_HAL_H__
#define __I2C_HAL_H__

#include "i2c_types.h"
#include "HALhwio.h"
#include "HALqupv3CommonHwio.h"
#include "HALqupv3SeHwio.h"
#include "qup_hal.h"

#define I2C_SLAVE_ADDRESS_BMSK    0xFE00
#define I2C_SLAVE_ADDRESS_SHFT    0x9
#define I2C_PRE_CMD_DELAY_BMSK    0x00000001
#define I2C_PRE_CMD_DELAY_SHFT    0x0
#define I2C_TIMESTAMP_BEFORE_BMSK    0x00000002
#define I2C_TIMESTAMP_BEFORE_SHFT    0x1
#define I2C_STRETCH_BMSK    0x00000004
#define I2C_STRETCH_SHFT    0x2
#define I2C_TIMESTAMP_AFTER_BMSK    0x00000008
#define I2C_TIMESTAMP_AFTER_SHFT    0x3
#define I2C_POST_CMD_DELAY_BMSK    0x00000010
#define I2C_POST_CMD_DELAY_SHFT    0x4
#define I2C_IGNORE_ADDR_NACK_BMSK    0x00000040
#define I2C_IGNORE_ADDR_NACK_SHFT    0x6
#define I2C_READ_FINISH_WITH_ACK_BMSK    0x00000080
#define I2C_READ_FINISH_WITH_ACK_SHFT    0x7
#define I2C_BYPASS_ADDRESS_PHASE_BMSK    0x00000100
#define I2C_BYPASS_ADDRESS_PHASE_SHFT    0x8

#define M_CMD_FLAG_SET(field, data)     (((uint32) data << (uint32) I2C_##field##_SHFT) & (uint32) I2C_##field##_BMSK)

#define FLD_SET(reg, field, data) \
    (((uint32) data << (uint32) HWIO_SHFT(reg, field)) & (uint32) HWIO_FMSK(reg, field))

#define FLD_GET(data, reg, field) \
    ((data & HWIO_FMSK(reg, field)) >> HWIO_SHFT(reg, field))

#endif
