/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/
#ifndef _BATTERY_LOGGING_H_
#define _BATTERY_LOGGING_H_

#include "data/sysfs_accessor.h"

void init_battery_log_params(
	struct cs_data_t *cs_data,
	const struct cfg_param_t *cfg_param);

void output_battery_log(
	struct cs_data_t *cs_data,
	const struct sysfs_param_t *sysfs_param,
	const char *event_name);

#endif /* _BATTERY_LOGGING_H_ */
