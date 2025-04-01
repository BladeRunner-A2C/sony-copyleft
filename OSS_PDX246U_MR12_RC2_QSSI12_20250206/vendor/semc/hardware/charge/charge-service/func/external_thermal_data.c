/*********************************************************************
 * Copyright 2021 Sony Corporation
 * All rights, including trade secret rights, reserved.
 *********************************************************************/

#include "charge-service.h"
#include "external_thermal_data.h"
#include "log.h"

void provide_external_thermal_data(
	struct cs_data_t *cs_data,
	const struct sysfs_param_t *sysfs_param)
{
	struct sysfs_param_t sysfs_value;

	UNUSED(cs_data);

	if (sysfs_param[SFID_THERMAL_ZONE_SDM_THERM].val_type != SYSFS_PARAM_VAL_INT ||
			sysfs_param[SFID_SDM_THERM].val_type != SYSFS_PARAM_VAL_INT)
		return;

	sysfs_value.intval = sysfs_param[SFID_THERMAL_ZONE_SDM_THERM].intval / 100;
	sysfs_value.val_type = SYSFS_PARAM_VAL_INT;

	if (sysfs_value.intval != sysfs_param[SFID_SDM_THERM].intval)
		write_sysfs_param(SFID_SDM_THERM, &sysfs_value);
}
