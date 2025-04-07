#ifndef __I2C_FW_IMAGE_H__
#define __I2C_FW_IMAGE_H__
/*==================================================================================================

FILE: I2CFWImage.h

DESCRIPTION: 

    Copyright (c) 2017 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.

==================================================================================================*/
/*==================================================================================================
                                    Edit History

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Include/I2CFWImage.h#1 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
13/07/17    VG       Initial revision

==================================================================================================*/

#include "i2c_api.h"    

/*==================================================================================================
                                        FUNCTION PROTOTYPES
==================================================================================================*/


i2c_status i2c_get_fw(uint8** base_ptr, uint32 version);


#endif  // __I2C_FW_IMAGE_H__
