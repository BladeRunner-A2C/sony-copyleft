/**********************************************************************
* boot_common_loader.c
*
* Common services for XBL Loader
*
* Copyright (c) 2018,2022 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
*
*
**********************************************************************/

/*=======================================================================
                        Edit History

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/StorageCommonLib/StorageLoaderCommon.c#1 $
$DateTime: 2024/04/02 23:00:31 $

YYYY-MM-DD   who     what, where, why
----------------------------------------------------------------------
2018-06-11   bb      Initial creation
===========================================================================*/

#include <boot_logger_if.h>
#include <boot_timer_if.h>
#include "StorageBootCommon.h"

// Wrapper for UART logging
void boot_common_log_message(char *str)
{
   boot_log_message(str);
}

// Wrapper for Time in us
uint32 boot_common_get_time()
{
  return boot_get_time_count();
}
