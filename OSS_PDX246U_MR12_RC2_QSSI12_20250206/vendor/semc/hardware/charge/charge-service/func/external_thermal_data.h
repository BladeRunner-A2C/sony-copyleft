/*********************************************************************
 * Copyright 2021 Sony Corporation
 * All rights, including trade secret rights, reserved.
 *********************************************************************/
#ifndef _EXTERNAL_THERMAL_DATA_H_
#define _EXTERNAL_THERMAL_DATA_H_

#include "data/sysfs_accessor.h"

void provide_external_thermal_data(struct cs_data_t *cs_data, const struct sysfs_param_t *sysfs_param);

#endif
