/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/

#include "charge-service.h"
#include "charge_full.h"
#include "log.h"

void set_restored_capacity(
	struct cs_data_t *cs_data,
	const struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	struct sysfs_param_t sysfs_value;
	int restored_capacity_mah = 0;

	if (cs_data->force_restoring_charge_full)
		restored_capacity_mah = 0;
	else
		restored_capacity_mah = batt_stat->fcc_mah[0];

	LOGD("restored_capacity from %d to %d\n", sysfs_param[SFID_RESTORED_CAPACITY].intval, restored_capacity_mah);
	sysfs_value.intval = restored_capacity_mah;
	sysfs_value.val_type = SYSFS_PARAM_VAL_INT;
	write_sysfs_param(SFID_RESTORED_CAPACITY, &sysfs_value);
	cs_data->force_restoring_charge_full = false;
}