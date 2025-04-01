/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/
#ifndef _AGING_MODE_SETTER_H_
#define _AGING_MODE_SETTER_H_

#include <stdbool.h>
#include <time.h>
#include "logger/charge-logging/miscta_batt_stat.h"
#include "data/sysfs_accessor.h"

#define INVALID_AGING_LEVEL -1

void control_soft_charge(
	struct cs_data_t *cs_data,
	const struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param);

#endif /* _AGING_MODE_SETTER_H_ */
