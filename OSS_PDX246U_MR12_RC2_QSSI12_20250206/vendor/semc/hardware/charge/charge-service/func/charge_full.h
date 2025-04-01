/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/
#ifndef _CHARGE_FULL_H_
#define _CHARGE_FULL_H_

#include "logger/charge-logging/miscta_batt_stat.h"
#include "data/sysfs_accessor.h"

void set_restored_capacity(
	struct cs_data_t *cs_data,
	const struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param);

#endif /* _CHARGE_FULL_H_ */
