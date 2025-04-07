/***********************************************************************
 * Coldplug Private APIs
 *
 * Coldplug
 * Copyright (C) 2015 QUALCOMM Technologies, Inc.
 *
 * Coldplug Private APIs
 *
 ***********************************************************************/

/*===========================================================================

  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/ColdplugLib/src/coldplug_priv.c#1 $ $DateTime: 2024/04/02 23:00:31 $ $Author: cirrusp4svc $

  when         who   what, where, why
  ----------   ---   ---------------------------------------------------------
  2015-06-15   rp    Create

 ===========================================================================*/

#include "coldplug_config_i.h"
#include "coldplug_api.h"
#include "coldplug_priv_api.h"
#include "coldplug_device.h"
#include "coldplug_util.h"

#include <string.h>

int coldplug_get_partition_info(struct coldplug_handle *chdl,
	struct coldplug_partition_in_ram *parti_info)
{
	struct coldplug_partition *cparti;

	coldplug_handle_validate(chdl);

	cparti = chdl->cparti;

	memset(parti_info, 0, sizeof(struct coldplug_partition_in_ram));

	coldplug_memscpy(parti_info, sizeof(*parti_info),
			&cparti->parti_info, sizeof(cparti->parti_info));

	return 0;
}
