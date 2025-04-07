#ifndef __SPI_FW_IMAGE_H__
#define __SPI_FW_IMAGE_H__
/*==================================================================================================

FILE: SPIFWImage.h

DESCRIPTION: 

    Copyright (c) 2019 Qualcomm Technologies, Incorporated.
                        All rights reserved.
    Qualcomm Technologies, Confidential and Proprietary.

==================================================================================================*/
/*==================================================================================================
                                    Edit History

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Include/SPIFWImage.h#1 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
13/07/17    VG       Initial revision

==================================================================================================*/

#include "SpiApi.h"    
#include "spi_config.h"

/*==================================================================================================
                                        FUNCTION PROTOTYPES
==================================================================================================*/


spi_status spi_get_fw(uint8** base_ptr, spi_plat_device_config *dcfg);


#endif  // __I2C_FW_IMAGE_H__
