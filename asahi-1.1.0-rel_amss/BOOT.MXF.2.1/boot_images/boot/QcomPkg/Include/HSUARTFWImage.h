#ifndef __HSUART_FW_IMAGE_H__
#define __HSUART_FW_IMAGE_H__
/*==================================================================================================

FILE: HSUARTFWImage.h

DESCRIPTION: 

    Copyright 2023 Qualcomm Technologies, Inc. All rights reserved

==================================================================================================*/
/*==================================================================================================
                                    Edit History

$Header: //components/dev/core.boot/5.1/tpoorna.core.boot.5.1.hsuart_apis/QcomPkg/Include/SPIFWImage.h#1 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
01/05/23   RK      Initial revision

==================================================================================================*/

//#include "HSUARTApi.h"
#include "HSUartDefs.h"
   

/*==================================================================================================
                                        FUNCTION PROTOTYPES
==================================================================================================*/


hsuart_result  hsuart_settings_get_fw(uint8** base_ptr, uint32 version);


#endif  // __HSUART_FW_IMAGE_H__
