/***********************************************************************
 * Coldplug SD/eMMC Block Device.
 *
 * Coldplug
 * Copyright (C) 2015,2019-2022 QUALCOMM Technologies, Inc.
 *
 * Coldplug SD/eMMC Block Device functions.
 *
 ***********************************************************************/

/*===========================================================================

  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/ColdplugLib/src/coldplug_bdev_sd.c#2 $ $DateTime: 2022/09/15 10:32:02 $ $Author: pwbldsvc $

  when         who   what, where, why
  ----------   ---   ---------------------------------------------------------
  2022-09-14   rn    change macro COLDPLUG_SD_ALL_LUNS to COLDPLUG_SD_FAKE_BOOT_LUN_NO
  2022-04-26   ss    Add coldplug_bdev_sd_ops_get_boot_info
  2022-04-10   gml   Fix incorrect lun # passed to sdcc_open API
  2022-01-17   ss    Add support for eMMC bootup using Device Tree Config
  2021-08-23   eo    Add coldplug_set_config API.
  2021-01-15   eo    Add set and get bootable partition support
  2019-01-09   rp    Add flush support.
  2015-06-15   rp    Create

 ===========================================================================*/

#include "coldplug_config_i.h"

#ifdef COLDPLUG_SD_OR_EMMC_ENABLE

#include "coldplug_bdev_ops.h"
#include "coldplug_device.h"
#include "coldplug_assert.h"
#include "coldplug_api.h"
#include "coldplug_util.h"
#include "coldplug_debug.h"

#include "sdcc_api.h"

#include <string.h>

#ifdef COLDPLUG_SD_OR_EMMC_DEBUG_DISABLE

static inline void coldplug_bdev_sd_debug_add(enum coldplug_debug_id debug_id,
			SDCC_STATUS sd_res, uint32 val1, uint32 val2)
{
	(void) debug_id; (void) sd_res; (void) val1; (void) val2;
}

#else

static void coldplug_bdev_sd_debug_add(enum coldplug_debug_id debug_id,
			SDCC_STATUS sd_res, uint32 val1, uint32 val2)
{
	struct coldplug_debug_info_type debug_info;

	memset(&debug_info, 0, sizeof(debug_info));
	debug_info.debug_id = debug_id;
	debug_info.dev_type = COLDPLUG_DEVICE_SD;
	debug_info.result = (int)sd_res;
	debug_info.val1 = val1;
	debug_info.val2 = val2;

	coldplug_debug_add(&debug_info);
}

#endif

static int coldplug_bdev_sd_ops_get_slot_and_lun_config(uint32 *max_slots,
		uint32 *max_luns, uint32 *boot_lun_no)
{
	COLDPLUG_ASSERT(max_slots != NULL);
	COLDPLUG_ASSERT(max_luns != NULL);
	COLDPLUG_ASSERT(boot_lun_no != NULL);

	*max_slots = COLDPLUG_MAX_SD_OR_EMMC_SLOTS;
	*max_luns = COLDPLUG_MAX_LUNS_IN_ONE_SLOT;
	*boot_lun_no = COLDPLUG_SD_FAKE_BOOT_LUN_NO;

	return 0;
}

static int coldplug_bdev_sd_ops_open(void **bdev_hdl,
		uint32 slot_no, uint32 lun_no)
{
	/*initializing all the variables to solve kw issues*/
	sdcc_config_info_type sdcc_pconfig = {0};
	struct sdcc_device *sd_hdl = NULL;
	boolean is_valid_slot = FALSE;
	uint32 num_slots=0,lun=0;
	int result = COLDPLUG_RESULT_ENODEV;
	SDCC_STATUS sdcc_res = SDCC_ERR_UNKNOWN;

	COLDPLUG_ASSERT(bdev_hdl != NULL);

	/* Do open_boot_device operation only for 
	   eMMC and skip for all the other slots  */
	if (slot_no != 0 && lun_no == COLDPLUG_SD_FAKE_BOOT_LUN_NO)
		return COLDPLUG_RESULT_NOT_SUPPORTED;

	/* Find out the total number of SD slots that are present on-target. */
	sdcc_res = sdcc_get_config_info(&sdcc_pconfig);
	if (sdcc_res != SDCC_NO_ERROR) {
		coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_OPEN,
			sdcc_res, slot_no, lun_no);
		goto End;
	}

	num_slots = (uint32) sdcc_pconfig.num_slots;
	if (slot_no >= num_slots) {
		coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_OPEN,
			SDCC_ERR_FEATURE_UNSUPPORTED, slot_no, lun_no);
		goto End;
	}

	is_valid_slot = sdcc_slot_has_support(slot_no, SDCC_SLOT_MEMORY);
	if (is_valid_slot == 0)	{
		coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_OPEN,
			SDCC_ERR_FEATURE_UNSUPPORTED, slot_no, lun_no);
		goto End;
	}

	/* coldplug_open_boot_device opens all partitions using Partial 
	 * Initialization where as coldplug_open_device opens specified 
	 * partition with Full Initialization
	 */
	if (lun_no == COLDPLUG_SD_FAKE_BOOT_LUN_NO)
	{
		sd_hdl = sdcc_handle_partial_open(slot_no, lun);
		if (sd_hdl == NULL) {
			coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_OPEN,
			SDCC_ERR_CARD_INIT, slot_no, lun);
			goto End;
		}
	}
	else
	{
		sd_hdl = sdcc_handle_open(slot_no, lun_no);
		if (sd_hdl == NULL) {
			coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_OPEN,
				SDCC_ERR_CARD_INIT, slot_no, lun_no);
			goto End;
		}
	}


	*bdev_hdl = (void *)sd_hdl;
	result = COLDPLUG_RESULT_SUCCESS;

End:
	return result;
}

static int coldplug_bdev_sd_ops_close(void *bdev_hdl)
{
	struct sdcc_device *sd_hdl = NULL;
	SDCC_STATUS sd_result;
	int result = COLDPLUG_RESULT_ENODEV;

	COLDPLUG_ASSERT(bdev_hdl != NULL);
	sd_hdl = (struct sdcc_device *)bdev_hdl;

	sd_result = sdcc_handle_close(sd_hdl);
	if (sd_result != SDCC_NO_ERROR) {
		coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_CLOSE,
			sd_result, 0, 0);
		goto End;
	}

	result = COLDPLUG_RESULT_SUCCESS;

End:
	return result;
}

static int coldplug_bdev_sd_ops_read(void *bdev_hdl, uint64 lba_arg,
	uint64 count_arg, uint8 *buff)
{
	struct sdcc_device *sd_hdl = NULL;
	uint32 lba;
	uint16 count;
	SDCC_STATUS sd_result;
	int result = COLDPLUG_RESULT_ENODEV;

	COLDPLUG_ASSERT(bdev_hdl != NULL);
	sd_hdl = (struct sdcc_device *)bdev_hdl;

	lba = (uint32) lba_arg;
	count = (uint16) count_arg;

	sd_result = sdcc_handle_read(sd_hdl, lba, buff, count);
	if (sd_result != SDCC_NO_ERROR)	{
		coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_READ,
			sd_result, lba, count);
		goto End;
	}

	result = COLDPLUG_RESULT_SUCCESS;

End:
	return result;
}

static int coldplug_bdev_sd_ops_write(void *bdev_hdl, uint64 lba_arg,
	uint64 count_arg, uint8 *buff)
{
	struct sdcc_device *sd_hdl = NULL;
	uint32 lba;
	uint16 count;
	SDCC_STATUS sd_result;
	int result = COLDPLUG_RESULT_ENODEV;

	COLDPLUG_ASSERT(bdev_hdl != NULL);
	sd_hdl = (struct sdcc_device *)bdev_hdl;

	lba = (uint32) lba_arg;
	count = (uint16) count_arg;

	sd_result = sdcc_handle_write(sd_hdl, lba, buff, count);
	if (sd_result != SDCC_NO_ERROR)	{
		coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_WRITE,
			sd_result, lba, count);
		goto End;
	}

	result = COLDPLUG_RESULT_SUCCESS;

End:
	return result;
}

static int coldplug_bdev_sd_ops_ops_flush(void *bdev_hdl)
{
	(void) bdev_hdl;
	return COLDPLUG_RESULT_SUCCESS;
}

static int coldplug_bdev_sd_ops_get_size(void *bdev_hdl, uint32 *lba_size,
		uint64 *total_lba)
{
	/*Initializing all variables to solve kw issue*/
	struct sdcc_device *sd_hdl = NULL;
	sdcc_mem_info_type sdcc_pmem_info = {0};
	SDCC_STATUS sd_result = SDCC_ERR_UNKNOWN;
	int result = COLDPLUG_RESULT_ENODEV;

	COLDPLUG_ASSERT(bdev_hdl != NULL);
	sd_hdl = (struct sdcc_device *)bdev_hdl;

	sd_result = sdcc_handle_mem_get_device_info(sd_hdl, &sdcc_pmem_info);
	if (sd_result != SDCC_NO_ERROR)	{
		coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_GET_INFO,
			sd_result, 1, 1);
		goto End;
	}

	*lba_size = sdcc_pmem_info.block_len;
	*total_lba = (uint64) sdcc_pmem_info.card_size_in_sectors;

	result = COLDPLUG_RESULT_SUCCESS;

End:
	return result;
}

static int coldplug_bdev_sd_ops_get_info(void *bdev_hdl,
		struct coldplug_device_info *dev_info)
{
	struct sdcc_device *sd_hdl = NULL;
	sdcc_mem_info_type sdcc_pmem_info;
	SDCC_STATUS sd_result;
	int result = COLDPLUG_RESULT_ENODEV;

	COLDPLUG_ASSERT(bdev_hdl != NULL);
	sd_hdl = (struct sdcc_device *) bdev_hdl;

	memset(&sdcc_pmem_info, 0, sizeof(sdcc_pmem_info));
	sd_result = sdcc_handle_mem_get_device_info(sd_hdl, &sdcc_pmem_info);
	if (sd_result != SDCC_NO_ERROR)	{
		coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_GET_INFO,
			sd_result, 0, 0);
		goto End;
	}

	dev_info->is_embedded_device = sdcc_pmem_info.is_embedded_device;
	dev_info->bytes_per_lba = sdcc_pmem_info.block_len;
	dev_info->total_lba_count =
		(uint64) sdcc_pmem_info.card_size_in_sectors;
	dev_info->manufacturer_id = sdcc_pmem_info.mfr_id;
	dev_info->oem_id = sdcc_pmem_info.oem_id;
	dev_info->product_rev = sdcc_pmem_info.prod_rev;
	dev_info->product_serial_number = sdcc_pmem_info.prod_serial_num;

	coldplug_memscpy(dev_info->product_name,
		sizeof(dev_info->product_name),
		sdcc_pmem_info.prod_name,
		sizeof(sdcc_pmem_info.prod_name));

	coldplug_memscpy(dev_info->manufactured_date,
		sizeof(dev_info->manufactured_date),
		sdcc_pmem_info.mfr_date,
		sizeof(sdcc_pmem_info.mfr_date));

	result = COLDPLUG_RESULT_SUCCESS;

End:
	return result;
}

static int coldplug_bdev_sd_ops_set_pon_wp(void *bdev_hdl, uint64 start_lba_arg,
		uint64 total_lba_arg)
{
	struct sdcc_device *sd_hdl = NULL;
	SDCC_STATUS sd_result;
	int result = COLDPLUG_RESULT_ENODEV;
	uint32 start_lba, total_lba;

	COLDPLUG_ASSERT(bdev_hdl != NULL);
	sd_hdl = (struct sdcc_device *) bdev_hdl;

	start_lba = (uint32) start_lba_arg;
	total_lba = (uint32) total_lba_arg;

	sd_result = sdcc_handle_set_power_on_write_protection(sd_hdl,
				 start_lba, total_lba);
	if (sd_result != SDCC_NO_ERROR)	{
		coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_SET_PON_WP,
			sd_result, start_lba, total_lba);
		goto End;
	}

	result = COLDPLUG_RESULT_SUCCESS;

End:
	return result;
}

static int coldplug_bdev_sd_ops_erase(void *bdev_hdl, uint64 start_lba_arg,
		uint64 total_lba_arg)
{
	struct sdcc_device *sd_hdl = NULL;
	SDCC_STATUS sd_result;
	int result = COLDPLUG_RESULT_ENODEV;
	uint32 start_lba, total_lba;

	COLDPLUG_ASSERT(bdev_hdl != NULL);
	sd_hdl = (struct sdcc_device *) bdev_hdl;

	start_lba = (uint32) start_lba_arg;
	total_lba = (uint32) total_lba_arg;

	sd_result = sdcc_handle_erase(sd_hdl, start_lba, total_lba);
	if (sd_result != SDCC_NO_ERROR)	{
		coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_ERASE,
			sd_result, start_lba, total_lba);
		goto End;
	}

	result = COLDPLUG_RESULT_SUCCESS;

End:
	return result;
}

static int coldplug_bdev_sd_ops_format(void *bdev_hdl)
{
	COLDPLUG_ASSERT(bdev_hdl != NULL);

	/* Format : No supported for SD/eMMC */
	return COLDPLUG_RESULT_SUCCESS;
}

static int coldplug_bdev_sd_ops_set_bootable_partition(uint32 slot_no, uint32 lun_no)
{
	struct sdcc_device *sd_hdl = NULL;
	SDCC_STATUS sd_result;
	int result = COLDPLUG_RESULT_ENODEV;

	if ((lun_no == 0) || (lun_no > 2)) {
		return COLDPLUG_RESULT_ERANGE;
	}

	sd_hdl = sdcc_handle_open(slot_no, lun_no);
	if (sd_hdl == NULL) {
		coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_OPEN,
			0, 0,0);
		return result;
	}

	sd_result = sdcc_handle_set_active_bootable_partition(sd_hdl);
	coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_SET_BOOTABLE,
		sd_result, lun_no, 0);
	if (sd_result != SDCC_NO_ERROR)	{
		goto End;
	}

	result = COLDPLUG_RESULT_SUCCESS;

End:
	sd_result = sdcc_handle_close(sd_hdl);
	if (sd_result != SDCC_NO_ERROR) {
		coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_CLOSE,
			sd_result, 0, 0);
		goto End;
	}
	return result;
}

static int coldplug_bdev_sd_ops_get_boot_info(void *bdev_hdl,
		struct coldplug_device_info *device_info)
{
			
			coldplug_bdev_sd_ops_get_info(bdev_hdl,device_info);
			device_info->is_boot_lun_present = FALSE;
			return COLDPLUG_RESULT_SUCCESS;
}
static int coldplug_bdev_sd_ops_get_bootable_partition(uint32 slot_no, uint32 *out_lun_no)
{
	struct sdcc_device *sd_hdl = NULL;
	sdcc_mem_info_type sd_info;
	SDCC_STATUS sd_result, sd_close_result;
	uint32 sd_boot_lun;
	boolean sd_boot_parti_found = FALSE;
	int result = COLDPLUG_RESULT_ENODEV;

	for (sd_boot_lun = 1; sd_boot_lun <= 2; sd_boot_lun++) {
		sd_hdl = sdcc_handle_open(slot_no, sd_boot_lun);
		if (sd_hdl == NULL) {
			coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_OPEN,
				0, 0,0);
			return result;
		}

		sd_result = sdcc_handle_mem_get_device_info(sd_hdl, &sd_info);
		if (sd_result != SDCC_NO_ERROR)
			coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_GET_INFO,
				sd_result, 0,0);

		sd_close_result = sdcc_handle_close(sd_hdl);
		if (sd_close_result != SDCC_NO_ERROR)
			coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_CLOSE,
				sd_result, 0, 0);

		if ((sd_result != SDCC_NO_ERROR) || (sd_close_result != SDCC_NO_ERROR))
			goto End;

		if (sd_info.is_phy_partition_bootable == TRUE) {
			sd_boot_parti_found = TRUE;
			break;
		}
	}

	if (sd_boot_parti_found == TRUE) {
		*out_lun_no = sd_boot_lun;
		result = COLDPLUG_RESULT_SUCCESS;
	}

End:
	coldplug_bdev_sd_debug_add(COLDPLUG_DEBUG_ID_GET_BOOTABLE,
		result, *out_lun_no, 0);
	return result;
}

static int coldplug_bdev_sd_ops_background_init_start(uint32 slot_no,
		uint32 init_context)
{
	(void) slot_no; (void) init_context;
	return COLDPLUG_RESULT_NOT_SUPPORTED;
}

static int coldplug_bdev_sd_ops_background_init_finish(uint32 slot_no,
		uint32 init_context)
{
	(void) slot_no; (void) init_context;
	return COLDPLUG_RESULT_NOT_SUPPORTED;
}

static int coldplug_bdev_sd_ops_set_config(uint32 slot_no,
        enum coldplug_set_cfg_type cfg)
{
	(void) slot_no; (void) cfg;
	return COLDPLUG_RESULT_NOT_SUPPORTED;
}

static struct coldplug_bdev_ops coldplug_bdev_sd_ops =
{
	coldplug_bdev_sd_ops_get_slot_and_lun_config,
	coldplug_bdev_sd_ops_open,
	coldplug_bdev_sd_ops_close,
	coldplug_bdev_sd_ops_read,
	coldplug_bdev_sd_ops_write,
	coldplug_bdev_sd_ops_ops_flush,
	coldplug_bdev_sd_ops_get_size,
	coldplug_bdev_sd_ops_get_info,
	coldplug_bdev_sd_ops_set_pon_wp,
	coldplug_bdev_sd_ops_erase,
	coldplug_bdev_sd_ops_format,
	coldplug_bdev_sd_ops_set_bootable_partition,
	coldplug_bdev_sd_ops_get_bootable_partition,
	coldplug_bdev_sd_ops_background_init_start,
	coldplug_bdev_sd_ops_background_init_finish,
	coldplug_bdev_sd_ops_set_config,
	coldplug_bdev_sd_ops_get_boot_info
};

struct coldplug_bdev_ops* coldplug_bdev_sd_get_ops(void)
{
	return &coldplug_bdev_sd_ops;
}

void coldplug_bdev_sd_init(void)
{
}

#endif /* COLDPLUG_SD_OR_EMMC_ENABLE */
