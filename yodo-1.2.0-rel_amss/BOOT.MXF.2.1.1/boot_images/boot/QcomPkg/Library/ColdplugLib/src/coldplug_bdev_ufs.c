/***********************************************************************
 * Coldplug UFS Block Device.
 *
 * Coldplug
 * Copyright (C) 2015,2019,2021,2022 QUALCOMM Technologies, Inc.
 *
 * Coldplug UFS Block Device.
 *
 ***********************************************************************/

/*===========================================================================

  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/ColdplugLib/src/coldplug_bdev_ufs.c#2 $ $DateTime: 2022/09/15 10:32:02 $ $Author: pwbldsvc $

  when         who   what, where, why
  ----------   ---   ---------------------------------------------------------
  2022-09-14   rn    Add coldplug_bdev_ufs_get_boot_info
  2021-08-23   eo    Add coldplug_set_config API.
  2021-01-15   eo    Add set and get bootable partition support
  2019-01-09   rp    Add flush support.
  2015-06-15   rp    Create

 ===========================================================================*/

#include "coldplug_config_i.h"

#ifdef COLDPLUG_UFS_ENABLE

#include "coldplug_bdev_ops.h"
#include "coldplug_device.h"
#include "coldplug_assert.h"
#include "coldplug_api.h"
#include "coldplug_util.h"
#include "coldplug_debug.h"
#include "coldplug_config.h"

#include "ufs_api.h"

#include <string.h>

#ifdef COLDPLUG_UFS_DEBUG_DISABLE

void static inline void coldplug_bdev_ufs_debug_add(
		enum coldplug_debug_id debug_id, int32_t ufs_res,
		uint32 val1, uint32 val2)
{
	(void) debug_id; (void) ufs_res; (void) val1; (void) val2;
}

#else

static void coldplug_bdev_ufs_debug_add(enum coldplug_debug_id debug_id,
		int32_t ufs_res, uint32 val1, uint32 val2)
{
	struct coldplug_debug_info_type debug_info;

	memset(&debug_info, 0, sizeof(debug_info));
	debug_info.debug_id = debug_id;
	debug_info.dev_type = COLDPLUG_DEVICE_UFS;
	debug_info.result = (int)ufs_res;
	debug_info.val1 = val1;
	debug_info.val2 = val2;

	coldplug_debug_add(&debug_info);
}

#endif

static int coldplug_bdev_ufs_ops_get_slot_and_lun_config(uint32 *max_slots,
		uint32 *max_luns, uint32 *boot_lun_no)
{
	COLDPLUG_ASSERT(max_slots != NULL);
	COLDPLUG_ASSERT(max_luns != NULL);
	COLDPLUG_ASSERT(boot_lun_no != NULL);

	*max_slots = COLDPLUG_MAX_UFS_SLOTS;
	*max_luns = COLDPLUG_MAX_LUNS_IN_ONE_SLOT;
	*boot_lun_no = UFS_WLUN_BOOT;

	return 0;
}

static int coldplug_bdev_ufs_ops_open(void **bdev_hdl, uint32 slot_no,
		uint32 lun_no)
{
	struct ufs_handle *ufs_hdl;
	int result = COLDPLUG_RESULT_ENODEV;

	COLDPLUG_ASSERT(bdev_hdl != NULL);

	ufs_hdl = ufs_open(slot_no, lun_no);
	if (ufs_hdl == NULL) {
		coldplug_bdev_ufs_debug_add(COLDPLUG_DEBUG_ID_OPEN,
			0, slot_no, lun_no);
		goto End;
	}

	*bdev_hdl = (void *) ufs_hdl;

	result = COLDPLUG_RESULT_SUCCESS;

End:
	return result;
}

int coldplug_bdev_ufs_ops_close(void *bdev_hdl)
{
	struct ufs_handle *ufs_hdl = NULL;
	int result = COLDPLUG_RESULT_ENODEV;

	COLDPLUG_ASSERT(bdev_hdl != NULL);
	ufs_hdl = (struct ufs_handle *) bdev_hdl;

	result = ufs_close(ufs_hdl);
	if (result != 0) {
		coldplug_bdev_ufs_debug_add(COLDPLUG_DEBUG_ID_CLOSE, 0, 0, 0);
		goto End;
	}

	result = COLDPLUG_RESULT_SUCCESS;

End:
	return result;
}

static int coldplug_bdev_ufs_ops_read(void *bdev_hdl, uint64 start_lba_arg,
		uint64 count_arg, uint8 *buff)
{
	struct ufs_handle *ufs_hdl = NULL;
	int32_t ufs_result;
	int result = COLDPLUG_RESULT_ENODEV;
	uint32 start_lba, count;

	COLDPLUG_ASSERT(bdev_hdl != NULL);
	ufs_hdl = (struct ufs_handle *) bdev_hdl;

	start_lba = (uint32) start_lba_arg;
	count = (uint32) count_arg;

	ufs_result = ufs_read(ufs_hdl, buff, start_lba, count);
	if (ufs_result != 0) {
		coldplug_bdev_ufs_debug_add(COLDPLUG_DEBUG_ID_READ,
			0, start_lba, count);
		goto End;
	}

	result = COLDPLUG_RESULT_SUCCESS;

End:
	return result;
}

static int coldplug_bdev_ufs_ops_write(void *bdev_hdl, uint64 start_lba_arg,
                             uint64 count_arg, uint8 *buff)
{
	struct ufs_handle *ufs_hdl = NULL;
	int32_t ufs_result;
	int result = COLDPLUG_RESULT_ENODEV;
	uint32 start_lba, count;

	COLDPLUG_ASSERT(bdev_hdl != NULL);
	ufs_hdl = (struct ufs_handle *) bdev_hdl;

	start_lba = (uint32) start_lba_arg;
	count = (uint32) count_arg;

	ufs_result = ufs_write(ufs_hdl, buff, start_lba, count);
	if (ufs_result != 0) {
		coldplug_bdev_ufs_debug_add(COLDPLUG_DEBUG_ID_WRITE,
			ufs_result, start_lba, count);
		goto End;
	}

	result = COLDPLUG_RESULT_SUCCESS;

End:
	return result;
}

static int coldplug_bdev_ufs_ops_ops_flush(void *bdev_hdl)
{
	(void) bdev_hdl;
	return COLDPLUG_RESULT_SUCCESS;
}


static int coldplug_bdev_ufs_ops_get_size(void *bdev_hdl, uint32 *lba_size,
		uint64 *total_lba)
{
	struct ufs_handle *ufs_hdl = NULL;
	struct ufs_info_type ufs_info;
	int32_t ufs_result;
	int result = COLDPLUG_RESULT_ENODEV;

	COLDPLUG_ASSERT(bdev_hdl != NULL);
	ufs_hdl = (struct ufs_handle *) bdev_hdl;

	memset(&ufs_info, 0, sizeof(ufs_info));
	ufs_result = ufs_get_device_info(ufs_hdl, &ufs_info);
	if (ufs_result != UFS_EOK) {
		coldplug_bdev_ufs_debug_add(COLDPLUG_DEBUG_ID_GET_INFO,
			ufs_result, 0, 0);
		goto End;
	}

	*lba_size = ufs_info.bMinAddrBlockSize * 512;
	*total_lba = (uint64) ufs_info.dLuTotalBlocks;

	result = COLDPLUG_RESULT_SUCCESS;

End:
	return result;
}

static int coldplug_bdev_ufs_get_boot_info(void *bdev_hdl,struct coldplug_device_info *device_info)
{
    device_info->bytes_per_lba = COLDPLUG_LBA_SIZE_IN_BYTES;
	device_info->total_lba_count = 1;
	device_info->is_boot_lun_present = TRUE;
	return COLDPLUG_RESULT_SUCCESS;
	
}

static int coldplug_bdev_ufs_ops_get_info(void *bdev_hdl,
		struct coldplug_device_info *dev_info)
{
	struct ufs_handle *ufs_hdl = NULL;
	struct ufs_info_type ufs_info;
	int32_t ufs_result;
	int result = COLDPLUG_RESULT_ENODEV;

	COLDPLUG_ASSERT(bdev_hdl != NULL);
	ufs_hdl = (struct ufs_handle *) bdev_hdl;

	memset(&ufs_info, 0, sizeof(ufs_info));
	ufs_result = ufs_get_device_info(ufs_hdl, &ufs_info);
	if (ufs_result != UFS_EOK) {
		coldplug_bdev_ufs_debug_add(COLDPLUG_DEBUG_ID_GET_INFO,
			ufs_result, 0, 0);
		goto End;
	}

	memset(dev_info, 0, sizeof(*dev_info));
	dev_info->is_embedded_device = 1;
	dev_info->manufacturer_id = (uint32) ufs_info.wManufacturerID;
	dev_info->bytes_per_lba = ufs_info.bMinAddrBlockSize * 512;
	dev_info->total_lba_count = (uint64) ufs_info.dLuTotalBlocks;

	ufs_result = ufs_get_device_info_str(ufs_hdl, ufs_info.iSerialNumber,
			(char *)dev_info->product_serial_number_string,
			sizeof(dev_info->product_serial_number_string));
	if (ufs_result != UFS_EOK) {
		coldplug_bdev_ufs_debug_add(COLDPLUG_DEBUG_ID_GET_INFO,
			ufs_result, 0, 0);
		goto End;
	}

	result = COLDPLUG_RESULT_SUCCESS;

End:
	return result;
}

static int coldplug_bdev_ufs_ops_set_pon_wp(void *bdev_hdl,
		uint64 start_lba, uint64 total_lba)
{
	struct ufs_handle *ufs_hdl = NULL;
	int32_t ufs_result;
	int result = COLDPLUG_RESULT_ENODEV;

	(void) start_lba; (void) total_lba;

	COLDPLUG_ASSERT(bdev_hdl != NULL);
	ufs_hdl = (struct ufs_handle *) bdev_hdl;

	ufs_result = ufs_set_pon_write_protect(ufs_hdl);
	if (ufs_result != UFS_EOK) {
		coldplug_bdev_ufs_debug_add(COLDPLUG_DEBUG_ID_SET_PON_WP,
			ufs_result, start_lba, total_lba);
		goto End;
	}

	result = COLDPLUG_RESULT_SUCCESS;

End:
	return result;
}

static int coldplug_bdev_ufs_ops_erase(void *bdev_hdl, uint64 start_lba_arg,
		uint64 total_lba_arg)
{
	struct ufs_handle *ufs_hdl = NULL;
	int32_t ufs_result;
	int result = COLDPLUG_RESULT_ENODEV;
	uint32 start_lba, total_lba;

	COLDPLUG_ASSERT(bdev_hdl != NULL);
	ufs_hdl = (struct ufs_handle *) bdev_hdl;

	start_lba = (uint32) start_lba_arg;
	total_lba = (uint32) total_lba_arg;

	ufs_result = ufs_unmap(ufs_hdl, start_lba, total_lba);
	if (ufs_result != UFS_EOK) {
		coldplug_bdev_ufs_debug_add(COLDPLUG_DEBUG_ID_ERASE,
			ufs_result, start_lba, total_lba);
		goto End;
	}

	result = COLDPLUG_RESULT_SUCCESS;

End:
	return result;
}

static int coldplug_bdev_ufs_ops_format(void *bdev_hdl)
{
	struct ufs_handle *ufs_hdl = NULL;
	int32_t ufs_result;
	int result = COLDPLUG_RESULT_ENODEV;

	COLDPLUG_ASSERT (bdev_hdl != NULL);
	ufs_hdl = (struct ufs_handle *)bdev_hdl;

	ufs_result = ufs_format(ufs_hdl);
	if (ufs_result != UFS_EOK) {
		coldplug_bdev_ufs_debug_add(COLDPLUG_DEBUG_ID_FORMAT,
			ufs_result, 0, 0);
		goto End;
	}

	result = COLDPLUG_RESULT_SUCCESS;

End:
	return result;
}

static int coldplug_bdev_ufs_ops_set_bootable_partition(uint32 slot_no, uint32 lun_no)
{
	struct ufs_handle *ufs_hdl = NULL;
	int32_t ufs_result;
	int result = COLDPLUG_RESULT_ENODEV;

	if ((lun_no == 0) || (lun_no > 2)) {
		return COLDPLUG_RESULT_ERANGE;
	}

	ufs_hdl = ufs_open(slot_no, UFS_WLUN_DEVICE);
	if (ufs_hdl == NULL) {
		return result;
	}

	ufs_result = ufs_set_bootable(ufs_hdl, lun_no);
	coldplug_bdev_ufs_debug_add(COLDPLUG_DEBUG_ID_SET_BOOTABLE,
		ufs_result, lun_no, 0);
	if (ufs_result != UFS_EOK) {
		goto End;
	}

	result = COLDPLUG_RESULT_SUCCESS;

End:
	ufs_result = ufs_close(ufs_hdl);
	if (ufs_result != UFS_EOK) {
		coldplug_bdev_ufs_debug_add(COLDPLUG_DEBUG_ID_CLOSE,
			ufs_result, 0, 0);
	}
	return result;
}

static int coldplug_bdev_ufs_ops_get_bootable_partition(uint32 slot_no, uint32 *out_lun_no)
{
	struct ufs_handle *ufs_hdl = NULL;
	struct ufs_info_type ufs_info;
	int32_t ufs_result;
	int result = COLDPLUG_RESULT_ENODEV;

	if (out_lun_no == NULL) {
		return COLDPLUG_RESULT_INVALID_ARG;
	}

	ufs_hdl = ufs_open(slot_no, UFS_WLUN_DEVICE);
	if (ufs_hdl == NULL) {
		return result;
	}

	memset(&ufs_info, 0, sizeof(ufs_info));
	ufs_result = ufs_get_device_info(ufs_hdl, &ufs_info);
	if (ufs_result != UFS_EOK) {
		coldplug_bdev_ufs_debug_add(COLDPLUG_DEBUG_ID_GET_INFO,
			ufs_result, 0, 0);
		goto End;
	}

	*out_lun_no = ufs_info.bBootLunEn;
	result = COLDPLUG_RESULT_SUCCESS;

End:
	coldplug_bdev_ufs_debug_add(COLDPLUG_DEBUG_ID_GET_BOOTABLE,
		result, *out_lun_no, 0);

	ufs_result = ufs_close(ufs_hdl);
	if (ufs_result != UFS_EOK) {
		coldplug_bdev_ufs_debug_add(COLDPLUG_DEBUG_ID_CLOSE,
			ufs_result, 0, 0);
	}
	return result;
}

static int coldplug_bdev_background_init_start(uint32 slot_no,
		uint32 init_context)
{
	int result;

	result = ufs_background_init_start(slot_no, init_context);
	if (result != 0)
		result = COLDPLUG_RESULT_ENODEV;

	return result;
}

static int coldplug_bdev_background_init_finish(uint32 slot_no,
		uint32 init_context)
{
	int result;

	result = ufs_background_init_finish(slot_no, init_context);
	if (result != 0)
		result = COLDPLUG_RESULT_ENODEV;

	return result;
}

static int coldplug_bdev_ufs_set_config(uint32 slot_no,
		 enum coldplug_set_cfg_type cfg)
{
	struct ufs_handle *ufs_hdl = NULL;
	int32_t ufs_result;
	ufs_config_mode ufs_mode = UFS_BATTERY_SAVINGS_CONFIG;
	int result = COLDPLUG_RESULT_ENODEV;

	ufs_hdl = ufs_open(slot_no, UFS_WLUN_DEVICE);
	if (ufs_hdl == NULL) {
		return result;
	}

    switch (cfg) {
		case COLDPLUG_SET_CFG_LOW_POWER:
			ufs_mode = UFS_BATTERY_SAVINGS_CONFIG;
			break;
		case COLDPLUG_SET_CFG_PERFORMANCE:
			ufs_mode = UFS_PERF_CONFIG;
			break;
		default:
			result = COLDPLUG_RESULT_ENODEV;
			goto End;
	}
	
	result = ufs_set_config(ufs_hdl, ufs_mode);
	coldplug_bdev_ufs_debug_add(COLDPLUG_DEBUG_ID_SET_CONFIG,
		result, ufs_mode, 0);

	if (result != 0)
		result = COLDPLUG_RESULT_ENODEV;

End:
	ufs_result = ufs_close(ufs_hdl);
	if (ufs_result != UFS_EOK) {
		coldplug_bdev_ufs_debug_add(COLDPLUG_DEBUG_ID_CLOSE,
			ufs_result, 0, 0);
	}

	return result;
}

static struct coldplug_bdev_ops coldplug_bdev_ufs_ops = {
	coldplug_bdev_ufs_ops_get_slot_and_lun_config,
	coldplug_bdev_ufs_ops_open,
	coldplug_bdev_ufs_ops_close,
	coldplug_bdev_ufs_ops_read,
	coldplug_bdev_ufs_ops_write,
	coldplug_bdev_ufs_ops_ops_flush,
	coldplug_bdev_ufs_ops_get_size,
	coldplug_bdev_ufs_ops_get_info,
	coldplug_bdev_ufs_ops_set_pon_wp,
	coldplug_bdev_ufs_ops_erase,
	coldplug_bdev_ufs_ops_format,
	coldplug_bdev_ufs_ops_set_bootable_partition,
	coldplug_bdev_ufs_ops_get_bootable_partition,
	coldplug_bdev_background_init_start,
	coldplug_bdev_background_init_finish,
	coldplug_bdev_ufs_set_config,
	coldplug_bdev_ufs_get_boot_info
};

struct coldplug_bdev_ops* coldplug_bdev_ufs_get_ops(void)
{
	return &coldplug_bdev_ufs_ops;
}

void coldplug_bdev_ufs_init(void)
{
}

#endif /* COLDPLUG_UFS_ENABLE */
