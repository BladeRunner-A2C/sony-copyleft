/***********************************************************************
 * coldplug
 *
 * Coldplug Block Device
 * Copyright (C) 2017-2019,2021-2023 QUALCOMM Technologies, Inc.
 *
 * Coldplug Block Device Operations module
 *
 ***********************************************************************/

/*===========================================================================

  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/ColdplugLib/inc/coldplug_bdev_ops.h#1 $ $DateTime: 2024/04/02 23:00:31 $ $Author: cirrusp4svc $

  when         who   what, where, why
  ----------   ---   ---------------------------------------------------------
  2023-04-04   sc    Add get_total_lba support
  2023-02-09   sc    Add support for handle validation
  2022-02-18   ss    Updated eMMC COLDPLUG_SD_ALL_LUNS macro
  2022-01-17   ss    Add support for sdcc bootup using Device Tree Config
  2021-08-23   eo    Add coldplug_set_config API.
  2021-01-15   eo    Add set and get bootable partition support
  2019-01-09   rp    Add flush support.
  2017-05-18   rp    Create

  ===========================================================================*/

#ifndef __COLDPLUG_BDEV_OPS_H__
#define __COLDPLUG_BDEV_OPS_H__

#include "coldplug_config_i.h"
#include "coldplug_api.h"

#define COLDPLUG_SD_ALL_LUNS       (0xA)
#define COLDPLUG_SD_START_LUN      ( 0)
#define COLDPLUG_SD_DEFAULT_LUNS   ( 1)

struct coldplug_bdev_ops {
	int (*get_slot_and_lun_config) (uint32 *max_slots, uint32 *max_luns,
					uint32 *boot_lun_no);

	int (*open) (void **bdev_hdl, uint32 slot_no, uint32 lun_no);
	int (*close) (void *bdev_hdl);
	int (*read) (void *bdev_hdl, uint64 lba, uint64 count, uint8 *buff);
	int (*write) (void *bdev_hdl, uint64 lba, uint64 count, uint8 *buff);
	int (*flush) (void *bdev_hdl);

	int (*get_size) (void *bdev_hdl, uint32 *lba_size, uint64 *total_lba);
	int (*get_info) (void *bdev_hdl,
			struct coldplug_device_info *device_info);

	int (*set_pon_wp) (void *bdev_hdl, uint64 start_lba, uint64 total_lba);
	int (*erase) (void *bdev_hdl, uint64 start_lba, uint64 total_lba);
	int (*format) (void *bdev_hdl);
	int (*set_bootable_partition) (uint32 slot_no, uint32 lun_no);
	int (*get_bootable_partition) (uint32 slot_no, uint32 *out_lun_no);

	int (*background_init_start)(uint32 slot_no, uint32 init_context);
	int (*background_init_finish)(uint32 slot_no, uint32 init_context);

	int (*set_config)(uint32 slot_no, enum coldplug_set_cfg_type cfg);
    int (*get_total_lba)(void *bdev_hdl, void *clun,
                    struct coldplug_device_info *device_info);
};

struct coldplug_bdev_ops* coldplug_bdev_ops_get(
		enum coldplug_device_type dev_type);

#endif /* __COLDPLUG_BDEV_OPS_H__ */
