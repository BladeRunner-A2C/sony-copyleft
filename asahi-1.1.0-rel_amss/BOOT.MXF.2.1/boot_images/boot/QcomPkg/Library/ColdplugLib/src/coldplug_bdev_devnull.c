/***********************************************************************
 * Coldplug Null Block Device.
 *
 * Coldplug
 * Copyright (C) 2017-2019,2021,2023 QUALCOMM Technologies, Inc.
 *
 * Coldplug Null Block device.
 *
 ***********************************************************************/

/*===========================================================================

  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/ColdplugLib/src/coldplug_bdev_devnull.c#1 $ $DateTime: 2024/04/02 23:00:31 $ $Author: cirrusp4svc $

  when         who   what, where, why
  ----------   ---   ---------------------------------------------------------
  2023-04-04   sc    Add coldplug_get_total_lba support
  2021-08-23   eo    Add coldplug_set_config API.
  2020-01-15   eo    Add set and get bootable partition support
  2019-01-09   rp    Add flush support.
  2017-06-15   rp    Create

 ===========================================================================*/

#include "coldplug_config_i.h"
#include "coldplug_bdev_ops.h"
#include "coldplug_device.h"
#include "coldplug_api.h"

static int coldplug_bdev_devnull_ops_get_slot_and_lun_config(
		uint32 *max_slots, uint32 *max_luns, uint32 *boot_lun_no)
{
	(void) max_slots; (void) max_luns; (void) boot_lun_no;
	return COLDPLUG_RESULT_ENODEV;
}

static int coldplug_bdev_devnull_ops_open(void **bdev_hdl,
		uint32 slot_no, uint32 lun_no)
{
	(void) bdev_hdl; (void) slot_no; (void) lun_no;
	return COLDPLUG_RESULT_ENODEV;
}

static int coldplug_bdev_devnull_ops_close(void *bdev_hdl)
{
	(void) bdev_hdl;
	return COLDPLUG_RESULT_ENODEV;
}

static int coldplug_bdev_devnull_ops_read(void *bdev_hdl,
		uint64 lba, uint64 count, uint8 *buff)
{
	(void) bdev_hdl; (void) lba; (void) count; (void) buff;
	return COLDPLUG_RESULT_ENODEV;
}

static int coldplug_bdev_devnull_ops_write(void *bdev_hdl,
		uint64 lba, uint64 count, uint8 *buff)
{
	(void) bdev_hdl; (void) lba; (void) count; (void) buff;
	return COLDPLUG_RESULT_ENODEV;
}

static int coldplug_bdev_devnull_ops_flush(void *bdev_hdl)
{
	(void) bdev_hdl;
	return COLDPLUG_RESULT_SUCCESS;
}

static int coldplug_bdev_devnull_ops_get_size(void *bdev_hdl,
		uint32 *lba_size, uint64 *total_lba)
{
	(void) bdev_hdl; (void) lba_size; (void) total_lba;
	return COLDPLUG_RESULT_ENODEV;
}

static int coldplug_bdev_devnull_ops_get_info(void *bdev_hdl,
		struct coldplug_device_info *dev_info)
{
	(void) bdev_hdl; (void) dev_info;
	return COLDPLUG_RESULT_ENODEV;
}

static int coldplug_bdev_devnull_ops_set_pon_wp(void *bdev_hdl,
		uint64 start_lba, uint64 total_lba)
{
	(void) bdev_hdl; (void) start_lba; (void) total_lba;
	return COLDPLUG_RESULT_ENODEV;
}

static int coldplug_bdev_devnull_ops_erase(void *bdev_hdl,
		uint64 start_lba, uint64 total_lba)
{
	(void) bdev_hdl; (void) start_lba; (void) total_lba;
	return COLDPLUG_RESULT_ENODEV;
}

static int coldplug_bdev_devnull_ops_format(void *bdev_hdl)
{
	(void) bdev_hdl;
	return COLDPLUG_RESULT_ENODEV;
}

static int coldplug_bdev_devnull_ops_set_bootable_partition(uint32 slot_no,
		uint32 lun_no)
{
	(void) slot_no; (void) lun_no;
	return COLDPLUG_RESULT_ENODEV;
}

static int coldplug_bdev_devnull_ops_get_bootable_partition(uint32 slot_no,
		uint32 *out_lun_no)
{
	(void) slot_no; (void) out_lun_no;
	return COLDPLUG_RESULT_ENODEV;
}

static int coldplug_bdev_devnull_ops_background_init_start(uint32 slot_no,
		uint32 init_context)
{
	(void) slot_no; (void) init_context;
	return COLDPLUG_RESULT_ENODEV;
}

static int coldplug_bdev_devnull_ops_background_init_finish(uint32 slot_no,
		uint32 init_context)
{
	(void) slot_no; (void) init_context;
	return COLDPLUG_RESULT_ENODEV;
}

static int coldplug_bdev_devnull_ops_set_config(uint32 slot_no,
		enum coldplug_set_cfg_type cfg)
{
	(void) slot_no; (void) cfg;
	return COLDPLUG_RESULT_ENODEV;
}

static int coldplug_bdev_devnull_ops_get_total_lba(void *bdev_hdl, void *clun,
        struct coldplug_device_info *device_info)
{
	(void) bdev_hdl; (void) clun; (void) device_info;
	return COLDPLUG_RESULT_ENODEV;
}

static struct coldplug_bdev_ops coldplug_bdev_devnull_ops =
{
	coldplug_bdev_devnull_ops_get_slot_and_lun_config,
	coldplug_bdev_devnull_ops_open,
	coldplug_bdev_devnull_ops_close,
	coldplug_bdev_devnull_ops_read,
	coldplug_bdev_devnull_ops_write,
	coldplug_bdev_devnull_ops_flush,
	coldplug_bdev_devnull_ops_get_size,
	coldplug_bdev_devnull_ops_get_info,
	coldplug_bdev_devnull_ops_set_pon_wp,
	coldplug_bdev_devnull_ops_erase,
	coldplug_bdev_devnull_ops_format,
	coldplug_bdev_devnull_ops_set_bootable_partition,
	coldplug_bdev_devnull_ops_get_bootable_partition,
	coldplug_bdev_devnull_ops_background_init_start,
	coldplug_bdev_devnull_ops_background_init_finish,
	coldplug_bdev_devnull_ops_set_config,
    coldplug_bdev_devnull_ops_get_total_lba
};

struct coldplug_bdev_ops* coldplug_bdev_devnull_get_ops(void)
{
	return &coldplug_bdev_devnull_ops;
}
