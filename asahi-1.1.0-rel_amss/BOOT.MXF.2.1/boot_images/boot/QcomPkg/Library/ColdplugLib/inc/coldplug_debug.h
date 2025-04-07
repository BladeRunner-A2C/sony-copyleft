/***********************************************************************
 * coldplug debug module.
 *
 * Coldplug
 * Copyright (C) 2017-2019,2021, 2022 QUALCOMM Technologies, Inc.
 *
 * Coldplug Debug module to store the last few errors.
 *
 ***********************************************************************/

/*===========================================================================

  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/ColdplugLib/inc/coldplug_debug.h#1 $ $DateTime: 2024/04/02 23:00:31 $ $Author: cirrusp4svc $

  when         who   what, where, why
  ----------   ---   ---------------------------------------------------------
  2022-06-29   sc    Add coldplug background init start ID
  2021-08-23   eo    Add coldplug_set_config API.
  2021-01-15   eo    Add set and get bootable partition support
  2019-01-09   rp    Add flush support.
  2018-11-28   rp    Add NVME support.
  2017-07-12   rp    Fix compiler warning.
  2017-05-18   rp    Create

 ===========================================================================*/

#ifndef __COLDPLUG_DEBUG_H__
#define __COLDPLUG_DEBUG_H__

#include "coldplug_config_i.h"
#include "coldplug_comdef.h"
#include "coldplug_api.h"

enum coldplug_debug_id
{
	COLDPLUG_DEBUG_ID_NONE              = 0,
	COLDPLUG_DEBUG_ID_OPEN              = 1,
	COLDPLUG_DEBUG_ID_CLOSE             = 2,
	COLDPLUG_DEBUG_ID_READ              = 3,
	COLDPLUG_DEBUG_ID_WRITE             = 4,
	COLDPLUG_DEBUG_ID_FLUSH             = 5,
	COLDPLUG_DEBUG_ID_GET_INFO          = 6,
	COLDPLUG_DEBUG_ID_SET_PON_WP        = 7,
	COLDPLUG_DEBUG_ID_ERASE             = 8,
	COLDPLUG_DEBUG_ID_FORMAT            = 9,
	COLDPLUG_DEBUG_ID_SET_BOOTABLE      = 10,
	COLDPLUG_DEBUG_ID_GET_BOOTABLE      = 11,
	COLDPLUG_DEBUG_ID_GET_SLOT_CONFIG   = 12,
	COLDPLUG_DEBUG_ID_SET_CONFIG        = 13,
	COLDPLUG_DEBUG_ID_BACKGROUND_START  = 14,
};

struct coldplug_debug_info_type
{
	enum coldplug_device_type dev_type;
	enum coldplug_debug_id debug_id;
	int result;
	uint32 val1;
	uint32 val2;
};

#ifndef COLDPLUG_DEBUG_DISABLE

void coldplug_debug_init(void);
void coldplug_debug_add(struct coldplug_debug_info_type *debug_info);

#else /* COLDPLUG_DEBUG_DISABLE */

static inline void
coldplug_debug_init(void)
{
}

static inline void
coldplug_debug_add(struct coldplug_debug_info_type *debug_info)
{
	(void) debug_info;
}

#endif /* COLDPLUG_DEBUG_DISABLE */

#endif /* __COLDPLUG_DEBUG_H__ */
