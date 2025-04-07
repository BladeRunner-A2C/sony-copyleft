/*==================================================================================================

FILE: i2c_geni_fw

DESCRIPTION: I2C GENI FW

                      Copyright (c) 2019 , 2021-2022 Qualcomm Technologies, Incorporated.
                                        All rights reserved.
                        Qualcomm Technologies, Confidential and Proprietary.

==================================================================================================*/
/*==================================================================================================
                                    Edit History

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/NullLibs/I2CFWImageLibNull/i2c_geni_fw.c#1 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
03/29/22   gkr     Added stubs for i2c_fetch_common_clock() and i2c_fetch_clk_cfg() 
01/03/19   bng     Kona FW upgrade

==================================================================================================*/

#include "I2CFWImage.h"
#include "i2c_api.h"
#include "i2c_config.h"

uint8  __attribute__ ((aligned (4))) qup_v2_5_i2c_fw[] =
{
};

i2c_status i2c_get_fw (uint8 **base_ptr, uint32 version)
{
    *base_ptr = qup_v2_5_i2c_fw;
    return I2C_SUCCESS;
}

i2c_status i2c_fetch_common_clock(plat_device_config *dcfg)
{
    return I2C_SUCCESS;
}

void i2c_fetch_clk_cfg(plat_device_config *dcfg)
{

}