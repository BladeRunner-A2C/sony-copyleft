/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/
#ifndef _LRC_MODE_H_
#define _LRC_MODE_H_

#include "data/sysfs_accessor.h"

enum {
	LRC_OP_CHARGING = 0,
	LRC_OP_NOT_CHARGING,
	LRC_OP_DISCHARGING,
};

void control_lrc_mode(struct cs_data_t *cs_data,
	const struct sysfs_param_t *sysfs_param);

#endif /* _LRC_MODE_H_ */
