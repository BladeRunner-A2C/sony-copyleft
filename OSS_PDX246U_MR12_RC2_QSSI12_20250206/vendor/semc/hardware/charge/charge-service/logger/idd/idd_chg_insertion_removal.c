/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/

#include <stdlib.h>
#include <string.h>
#include <idd_api.h>
#include "charge-service.h"
#include "idd_chg_insertion_removal.h"
#include "charging/charging.pb-c.h"
#include "log.h"

#ifdef LOG_ALL
static void idd_log_chg_in_rm_data(Charging__ChargerInsertionRemoval *chg_insert_removal_param)
{
	int i;

	LOGD("***************************************************************\n");
	LOGD("charger_type                     = %s\n", chg_insert_removal_param->charger_type);
	LOGD("usb_insertion_time               = %u\n", chg_insert_removal_param->usb_insertion_time);
	LOGD("usb_long_insertion_counter       = %u\n", chg_insert_removal_param->usb_long_insertion_counter);
	LOGD("inserted_soc                     = %u\n", chg_insert_removal_param->inserted_soc);
	LOGD("removal_soc                      = %u\n", chg_insert_removal_param->removal_soc);
	LOGD("inserted_sc_stage                = %u\n", chg_insert_removal_param->inserted_sc_stage);
	LOGD("removal_sc_stage                 = %u\n", chg_insert_removal_param->removal_sc_stage);
	LOGD("learning_flg                     = %u\n", chg_insert_removal_param->learning_flg);
	LOGD("battery_care_flg                 = %u\n", chg_insert_removal_param->battery_care_flg);
	LOGD("moment_max_usbin_voltage         = %u\n", chg_insert_removal_param->moment_max_usbin_voltage);
	LOGD("moment_max_vbatt                 = %u\n", chg_insert_removal_param->moment_max_vbatt);
	LOGD("icl_min_counter                  = %u\n", chg_insert_removal_param->icl_min_counter);
	LOGD("learning_flg                     = %u\n", chg_insert_removal_param->learning_flg);
	LOGD("battery_care_flg                 = %u\n", chg_insert_removal_param->battery_care_flg);
	LOGD("wlc_epp_txid                     = %u\n", chg_insert_removal_param->wlc_epp_txid);
	LOGD("wlc_ping_freq                    = %u\n", chg_insert_removal_param->wlc_ping_freq);
	LOGD("wlc_potential_power              = %u\n", chg_insert_removal_param->wlc_potential_power);
	for (i = 0; i < MAX_THERMAL_LEVEL_INDEX; i++) {
		LOGD("thermal_level_time(LV%d)         = %lu\n", i, chg_insert_removal_param->thermal_level_time[i]);
	}
	LOGD("pdo_raw_list:\n%s", chg_insert_removal_param->pdo_raw_list);
	for (i = 0; i < MAX_PDO_INDEX; i++) {
		LOGD("pdo%d_selected_time              = %lu\n", i + 1, chg_insert_removal_param->pdo_selected_time[i]);
	}
	LOGD("wlc_guaranteed_power             = %u\n", chg_insert_removal_param->wlc_guaranteed_power);
	LOGD("***************************************************************\n");
}

#else
static void idd_log_chg_in_rm_data(Charging__ChargerInsertionRemoval *chg_insert_removal_param)
{
	UNUSED(chg_insert_removal_param);
}
#endif

#define NO_BATT_PRODUCT "_cdb"

bool can_send_idd_chg_insertion_removal(struct cs_data_t *cs_data,
		struct chg_insertion_removal_data_t *chg_in_rm_data,
		const struct sysfs_param_t *sysfs_param)
{
	static int prev_usb_long_insertion_counter = 0;
	static int prev_bootup_phase = 0;
	static int prev_thermal_lv = 0;
	bool f_send = false;
	int current_thermal_lv = 0;

	current_thermal_lv = sysfs_param[SFID_SYSTEM_TEMP_LEVEL].intval;
	if (strstr(cs_data->product_name, NO_BATT_PRODUCT) != NULL)
		goto out;

	/* when time adjustment is not done, idd is still not ready */
	if (!is_adjusted_time(cs_data->event_system_time))
		goto out;

	if (chg_in_rm_data->charger_state == CHARGER_REMOVAL ||
		chg_in_rm_data->wireless_charger_state == CHARGER_REMOVAL) {
		f_send = true;
		goto out;
	}

	if (prev_usb_long_insertion_counter < cs_data->usb_long_insertion_counter) {
		f_send = true;
		goto out;
	}

	if (sysfs_param[SFID_SYSTEM_STATUS].intval == SYSTEM_STATUS_SHUTDOWN &&
			prev_bootup_phase != sysfs_param[SFID_SYSTEM_STATUS].intval &&
			(chg_in_rm_data->charger_state != CHARGER_NO_INSERTING ||
			chg_in_rm_data->wireless_charger_state != CHARGER_NO_INSERTING)) {
		f_send = true;
		goto out;
	}

	if (current_thermal_lv == sysfs_param[SFID_SYSTEM_TEMP_LEVEL_MAX].intval &&
					current_thermal_lv != prev_thermal_lv) {
		f_send = true;
		goto out;
	}

out:
	prev_usb_long_insertion_counter = cs_data->usb_long_insertion_counter;
	prev_bootup_phase = sysfs_param[SFID_SYSTEM_STATUS].intval;
	prev_thermal_lv = current_thermal_lv;
	return f_send;
}

#define MAX_CHARGER_TYPE_STR 16
#define MAX_PDO_STR 56
#define INSERTION_REMOVAL_PARAMS_VERSION 2
static void set_idd_chg_insertion_removal_params(
	Charging__ChargerInsertionRemoval *chg_insert_removal_param,
	const struct chg_insertion_removal_data_t *chg_in_rm_data,
	struct cs_data_t *cs_data)
{
	int i;
	int size = 0;
	int pdo_cnt = 0;
	static uint32_t pdo_selected_time[MAX_PDO_INDEX];
	static uint32_t thermal_level_time[MAX_THERMAL_LEVEL_INDEX];
	static char charger_type[MAX_CHARGER_TYPE_STR];
	static char pdo_raw_list[MAX_PDO_STR];

	memset(pdo_selected_time, 0, sizeof(pdo_selected_time));
	memset(thermal_level_time, 0, sizeof(thermal_level_time));
	memset(charger_type, '\0', sizeof(charger_type));
	memset(pdo_raw_list, '\0', sizeof(pdo_raw_list));

	for (i = 0; i < MAX_THERMAL_LEVEL_INDEX; i++)
		thermal_level_time[i] = chg_in_rm_data->thermal_level_time[i];

	chg_insert_removal_param->has_version = true;
	chg_insert_removal_param->version = INSERTION_REMOVAL_PARAMS_VERSION;

	size = snprintf(charger_type, MAX_CHARGER_TYPE_STR, "%s", chg_in_rm_data->charger_type);
	chg_insert_removal_param->charger_type = charger_type;

	chg_insert_removal_param->has_usb_insertion_time = true;
	chg_insert_removal_param->usb_insertion_time = chg_in_rm_data->usb_insertion_time;

	chg_insert_removal_param->has_usb_long_insertion_counter = true;
	chg_insert_removal_param->usb_long_insertion_counter = cs_data->usb_long_insertion_counter;

	chg_insert_removal_param->pdo_raw_list = pdo_raw_list;

	chg_insert_removal_param->n_pdo_selected_time = pdo_cnt;
	chg_insert_removal_param->pdo_selected_time = pdo_selected_time;

	chg_insert_removal_param->n_thermal_level_time = MAX_THERMAL_LEVEL_INDEX;
	chg_insert_removal_param->thermal_level_time = thermal_level_time;

	chg_insert_removal_param->has_inserted_soc = true;
	chg_insert_removal_param->inserted_soc = chg_in_rm_data->inserted_soc;

	chg_insert_removal_param->has_removal_soc = true;
	chg_insert_removal_param->removal_soc = chg_in_rm_data->removal_soc;

	chg_insert_removal_param->has_inserted_sc_stage = true;
	chg_insert_removal_param->inserted_sc_stage = chg_in_rm_data->inserted_sc_stage;

	chg_insert_removal_param->has_removal_sc_stage = true;
	chg_insert_removal_param->removal_sc_stage = chg_in_rm_data->removal_sc_stage;

	chg_insert_removal_param->has_learning_flg = false;
	chg_insert_removal_param->learning_flg = chg_in_rm_data->learning_flg;

	chg_insert_removal_param->has_battery_care_flg = true;
	chg_insert_removal_param->battery_care_flg = chg_in_rm_data->battery_care_flg;

	chg_insert_removal_param->has_moment_max_usbin_voltage = true;
	chg_insert_removal_param->moment_max_usbin_voltage = chg_in_rm_data->moment_max_usbin_voltage;

	chg_insert_removal_param->has_moment_max_vbatt = true;
	chg_insert_removal_param->moment_max_vbatt = chg_in_rm_data->moment_max_vbatt;

	chg_insert_removal_param->has_icl_min_counter = true;
	chg_insert_removal_param->icl_min_counter = chg_in_rm_data->icl_min_counter;

	chg_insert_removal_param->has_wlc_epp_txid = true;
	chg_insert_removal_param->wlc_epp_txid = chg_in_rm_data->wlc_epp_txid;

	chg_insert_removal_param->has_wlc_potential_power = false;
	chg_insert_removal_param->wlc_potential_power = chg_in_rm_data->wlc_potential_power;

	chg_insert_removal_param->has_wlc_ping_freq = false;
	chg_insert_removal_param->wlc_ping_freq = chg_in_rm_data->wlc_ping_freq;

	chg_insert_removal_param->has_wlc_guaranteed_power = false;
	chg_insert_removal_param->wlc_guaranteed_power = chg_in_rm_data->wlc_guaranteed_power;

	chg_insert_removal_param->has_usb_connector_heat_flg = true;
	chg_insert_removal_param->usb_connector_heat_flg = chg_in_rm_data->usb_connector_heat_flg;

	idd_log_chg_in_rm_data(chg_insert_removal_param);
}

void send_idd_chg_insertion_removal(struct cs_data_t *cs_data,
				struct chg_insertion_removal_data_t *chg_in_rm_data)
{
	IDD_t *idd_p;
	size_t size;
	uint8_t *serialized_p;
	int ret;
	Charging__ChargerInsertionRemoval chg_insert_removal_param
		= CHARGING__CHARGER_INSERTION_REMOVAL__INIT;

	idd_p = idd_create();
	if (idd_p == NULL) {
		LOG("IDD_T for Charger_Insertion_Removal is NULL\n");
		return ;
	}

	ret = idd_is_active(idd_p);
	if (ret <= 0) {
		LOG("idd_is_active: %d\n", ret);
		idd_destroy(&idd_p);
		return;
	}

	set_idd_chg_insertion_removal_params(&chg_insert_removal_param, chg_in_rm_data, cs_data);
	size = charging__charger_insertion_removal__get_packed_size(&chg_insert_removal_param);
	if (size > 0) {
		LOGD("Upload Charger insert/removal log to IDD. size: %d\n", size);
		serialized_p = malloc(size);
		if (serialized_p) {
			size = charging__charger_insertion_removal__pack(&chg_insert_removal_param, serialized_p);
			idd_add_event(idd_p, "charging", "ChargerInsertionRemoval",
				(char *)serialized_p, size);
			LOG("Sending idd event for ChargerInsertionRemoval\n");
			free(serialized_p);
		} else {
			LOG("malloc failed\n");
		}
	} else {
		LOG("IDD log Could not serialize message data\n");
	}
	idd_destroy(&idd_p);

	cs_data->chg_insertion_removal_idd_sent_time = cs_data->event_boot_time;
	memset(chg_in_rm_data, 0, sizeof(struct chg_insertion_removal_data_t));
}
