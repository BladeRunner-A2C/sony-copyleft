/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/
#ifndef _CHG_INSERTION_REMOVAL_H_
#define _CHG_INSERTION_REMOVAL_H_

#include "data/sysfs_accessor.h"

enum {
	PRESENT_OFF = 0,
	PRESENT_ON,
};

enum {
	CHARGER_NO_INSERTING = 0,
	CHARGER_INSERTION,
	CHARGER_INSERTING,
	CHARGER_REMOVAL,
};

#define MAX_PDO_INDEX 7
#define MAX_THERMAL_LEVEL_INDEX 20
struct chg_insertion_removal_data_t {
	bool learning_flg;
	bool battery_care_flg;
	uint32_t pdo_raw_list[MAX_PDO_INDEX];
	char charger_type[16];
	int inserted_soc;
	int removal_soc;
	int inserted_sc_stage;
	int removal_sc_stage;
	int moment_max_usbin_voltage;
	int moment_max_vbatt;
	int icl_min_counter;
	int wlc_epp_txid;
	int wlc_ping_freq;
	int wlc_potential_power;
	int pdo_selected_time[MAX_PDO_INDEX];
	int thermal_level_time[MAX_THERMAL_LEVEL_INDEX];
	int usb_insertion_time;
	int charger_state;
	int wireless_charger_state;
	int wlc_guaranteed_power;
	bool usb_connector_heat_flg;
};

void set_chg_insertion_removal_data(struct cs_data_t *cs_data,
			const struct sysfs_param_t *sysfs_param,
			struct chg_insertion_removal_data_t *chg_in_rm_data);

#endif /* _CHG_INSERTION_REMOVAL_H_ */
