#ifndef BOOT_FRAMEWORK_H
#define BOOT_FRAMEWORK_H

/*===========================================================================

                      Boot Config Context Header File

GENERAL DESCRIPTION
  This file contains the interfaces for Config Context module. 

Copyright 2019 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Include/api/boot/boot_framework.h#1 $ 
$DateTime: 2024/04/02 23:00:31 $ 
$Author: cirrusp4svc $

when        who      what, where, why
----------  ---      ----------------------------------------------------------
04/03/19    ep       Initial version

===========================================================================*/


/*===========================================================================
                           INCLUDE FILES
===========================================================================*/
#include "boot_comdef.h"


/*==========================================================================
                          PUBLIC DATA DECLARATIONS
===========================================================================*/
#define CLOSED_OBJECT_ID	-1


typedef void* boot_handle;

typedef struct boot_handle_common_type
{
	uint32 id;
	boot_handle config_context_handle;
} boot_handle_common_type;

#endif // BOOT_FRAMEWORK_H
