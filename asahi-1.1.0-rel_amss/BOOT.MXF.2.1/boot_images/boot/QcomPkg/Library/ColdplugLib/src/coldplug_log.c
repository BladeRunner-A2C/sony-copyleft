/***********************************************************************
 * Coldplug Log module.
 *
 * Coldplug
 * Copyright (C) 2015 QUALCOMM Technologies, Inc.
 *
 * Coldplug Log module functions.
 *
 ***********************************************************************/

/*===========================================================================

  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/ColdplugLib/src/coldplug_log.c#1 $ $DateTime: 2024/04/02 23:00:31 $ $Author: cirrusp4svc $

  when         who   what, where, why
  ----------   ---   ---------------------------------------------------------
  2015-06-15   rp    Create

 ===========================================================================*/

#include "coldplug_config_i.h"
#include "coldplug_log.h"

#ifdef COLDPLUG_LOG_ENABLE

#include "boot_logger.h"

void coldplug_log(const char *filename, int line_no, char *msg)
{
	(void) filename; (void) line_no;
	boot_log_message(msg);
}

#endif /* COLDPLUG_LOG_DISABLE */
