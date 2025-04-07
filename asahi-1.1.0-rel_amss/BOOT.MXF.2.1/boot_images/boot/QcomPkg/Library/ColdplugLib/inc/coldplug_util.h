/***********************************************************************
 * Coldplug utility functions.
 *
 * Coldplug
 * Copyright (C) 2017 QUALCOMM Technologies, Inc.
 *
 * Coldplug utility functions to do memory copy functions.
 *
 ***********************************************************************/

/*===========================================================================

  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/ColdplugLib/inc/coldplug_util.h#1 $ $DateTime: 2024/04/02 23:00:31 $ $Author: cirrusp4svc $

  when         who   what, where, why
  ----------   ---   ---------------------------------------------------------
  2017-05-18   rp    Create

 ===========================================================================*/

#ifndef __COLDPLUG_UTIL_H__
#define __COLDPLUG_UTIL_H__

#include "coldplug_config_i.h"

#include <stdlib.h>

/* Check for integer overflows */
#define COLDPLUG_INT_OVERFLOW(x,y) (x + y < x)

void coldplug_memscpy(void *dst, size_t dst_size,
		      const void *src, size_t src_size);

void coldplug_memsmove(void *dst, size_t dst_size,
		       const void *src, size_t src_size);

#endif /* __COLDPLUG_UTIL_H__ */
