/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/

#include "charge-service.h"
#include "lrc_mode.h"
#include "log.h"
#include "data/sysfs_accessor.h"

#define SUSPEND_DISABLE 0
#define SUSPEND_ENABLE  1
#define STARTUP_LRC_SOCMAX    60
#define STARTUP_LRC_SOCMIN    40

static void operate_lrc(int lrc_operation, const struct sysfs_param_t *sysfs_param)
{
	struct sysfs_param_t battchg_suspend;
	struct sysfs_param_t usbin_suspend;

	battchg_suspend.val_type = SYSFS_PARAM_VAL_INT;
	usbin_suspend.val_type = SYSFS_PARAM_VAL_INT;

	switch (lrc_operation) {
	case LRC_OP_CHARGING:
		battchg_suspend.intval = SUSPEND_DISABLE;
		usbin_suspend.intval = SUSPEND_DISABLE;
		break;
	case LRC_OP_NOT_CHARGING:
		battchg_suspend.intval = SUSPEND_ENABLE;
		usbin_suspend.intval = SUSPEND_DISABLE;
		break;
	case LRC_OP_DISCHARGING:
		battchg_suspend.intval = SUSPEND_DISABLE;
		usbin_suspend.intval = SUSPEND_ENABLE;
		break;
	default:
		return;
	}

	if (sysfs_param[SFID_LRC_CHARGE_DISABLE].intval != battchg_suspend.intval)
		write_sysfs_param(SFID_LRC_CHARGE_DISABLE, &battchg_suspend);

	if (sysfs_param[SFID_LRC_INPUT_SUSPEND].intval != usbin_suspend.intval)
		write_sysfs_param(SFID_LRC_INPUT_SUSPEND, &usbin_suspend);
}

void control_lrc_mode(struct cs_data_t *cs_data,
				const struct sysfs_param_t *sysfs_param)
{
	int soc = sysfs_param[SFID_CAPACITY].intval;

	switch (cs_data->lrc_operation) {
	case LRC_OP_CHARGING:
		if (soc > STARTUP_LRC_SOCMAX) {
			cs_data->lrc_operation = LRC_OP_DISCHARGING;
		} else if (soc >= STARTUP_LRC_SOCMAX) {
			cs_data->lrc_operation = LRC_OP_NOT_CHARGING;
		}
		break;
	case LRC_OP_NOT_CHARGING:
		if (soc > STARTUP_LRC_SOCMAX) {
			cs_data->lrc_operation = LRC_OP_DISCHARGING;
		} else if (soc <= STARTUP_LRC_SOCMIN) {
			cs_data->lrc_operation = LRC_OP_CHARGING;
		}
		break;
	case LRC_OP_DISCHARGING:
		if (soc <= STARTUP_LRC_SOCMAX && soc > STARTUP_LRC_SOCMIN) {
			cs_data->lrc_operation = LRC_OP_NOT_CHARGING;
		} else if (soc <= STARTUP_LRC_SOCMIN) {
			cs_data->lrc_operation = LRC_OP_CHARGING;
		}
		break;
	default:
		return;
	}

	operate_lrc(cs_data->lrc_operation, sysfs_param);
}
