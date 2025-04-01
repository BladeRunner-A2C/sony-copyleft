/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/

#include <miscta.h>
#include <miscta_units.h>
#include "charge-service.h"
#include "data/sysfs_accessor.h"
#include "miscta_handler.h"
#include "log.h"

#define SS_FIRST_BOOT_STARTED 0xAB

static void handle_ta_flash_startup_shutdown_result(struct cs_data_t *cs_data)
{
	miscta_status_t status;
	uint64_t unit64Data = 0;
	uint32_t size = 4;

	status = miscta_read_unit(TA_FLASH_STARTUP_SHUTDOWN_RESULT, &unit64Data, &size);
	if ((status == MT_SUCCESS) && (unit64Data == SS_FIRST_BOOT_STARTED)) {
		LOG("This phone is in startup process now, battery charge is limited.\n");
		cs_data->lrc_enabled = true;
	}
}

#define USB_CHARGING_DISABLED 1

static void handle_ta_disable_usb_charging(void)
{
	miscta_status_t status;
	uint8_t unitData = 0;
	uint32_t size = sizeof(unitData);
	struct sysfs_param_t sysfs_value;

	status = miscta_read_unit(TA_DISABLE_USB_CHARGING, &unitData, &size);

	if ((status == MT_SUCCESS) && (unitData == USB_CHARGING_DISABLED)) {
		LOG("Charging will be disabled by miscTA, %d\n", unitData);
		sysfs_value.val_type = SYSFS_PARAM_VAL_INT;
		sysfs_value.intval = 1;
		write_sysfs_param(SFID_USB_INPUT_SUSPEND, &sysfs_value);
	}
}

void handle_miscta(struct cs_data_t *cs_data)
{
	/* MiscTA 2227 */
	handle_ta_flash_startup_shutdown_result(cs_data);

	/* MiscTA 2312 */
	handle_ta_disable_usb_charging();
}
