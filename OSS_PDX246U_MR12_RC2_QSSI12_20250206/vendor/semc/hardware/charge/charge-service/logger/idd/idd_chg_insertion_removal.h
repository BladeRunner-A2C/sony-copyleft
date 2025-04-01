/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/
#ifndef _IDD_CHG_INSERTION_REMOVAL_H_
#define _IDD_CHG_INSERTION_REMOVAL_H_

#include "logger/charge-logging/chg_insertion_removal.h"
#include "data/sysfs_accessor.h"

bool can_send_idd_chg_insertion_removal(struct cs_data_t *cs_data,
			struct chg_insertion_removal_data_t *chg_in_rm_data,
			const struct sysfs_param_t *sysfs_param);
void send_idd_chg_insertion_removal(struct cs_data_t *cs_data,
			struct chg_insertion_removal_data_t *chg_in_rm_data);

#endif /* _IDD_CHG_INSERTION_REMOVAL_H_ */
