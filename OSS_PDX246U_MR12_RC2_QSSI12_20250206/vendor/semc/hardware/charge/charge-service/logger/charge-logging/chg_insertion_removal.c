/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/

#include <stdlib.h>
#include <string.h>
#include "charge-service.h"
#include "chg_insertion_removal.h"
#include "log.h"

static int check_chgr_state(int present)
{
	static int prev_present = PRESENT_OFF;
	int state = CHARGER_NO_INSERTING;

	if (prev_present == PRESENT_OFF) {
		if (present == PRESENT_ON)
			state = CHARGER_INSERTION;
		else if (present == PRESENT_OFF)
			state = CHARGER_NO_INSERTING;

	} else if (prev_present == PRESENT_ON) {
		if (present == PRESENT_ON)
			state = CHARGER_INSERTING;
		else if (present == PRESENT_OFF)
			state = CHARGER_REMOVAL;
	}

	prev_present = present;
	return state;
}

static int check_wlc_state(int wlc_present)
{
	static int prev_wlc_present = PRESENT_OFF;
	int state = CHARGER_NO_INSERTING;

	if (prev_wlc_present == PRESENT_OFF) {
		if (wlc_present == PRESENT_ON)
			state = CHARGER_INSERTION;
		else if (wlc_present == PRESENT_OFF)
			state = CHARGER_NO_INSERTING;

	} else if (prev_wlc_present == PRESENT_ON) {
		if (wlc_present == PRESENT_ON)
			state = CHARGER_INSERTING;
		else if (wlc_present == PRESENT_OFF)
			state = CHARGER_REMOVAL;
	}

	prev_wlc_present = wlc_present;
	return state;
}

#define USB_LONG_INSERTION_TIME	86400 /* (24 * 60 * 60) */
#define ICL_MIN_BIT	0x0004 /* 0x110A:BIT_3 */
#define REAL_TYPE_PD	"USB_PD"
#define CHARGER_BAT_CONNECTION	"BAD CONNECTION"
void set_chg_insertion_removal_data(struct cs_data_t *cs_data,
			const struct sysfs_param_t *sysfs_param,
			struct chg_insertion_removal_data_t *chg_in_rm_data)
{
	static time_t prev_time = 0;
	static int prev_thermal_lv = 0;
	static int insertion_elapsed_time = 0;
	static int prev_icl_min_bit = 0;
	int icl_min_bit;
	int time_diff;

	if (!prev_time || !cs_data->event_boot_time)
		time_diff = 0;
	else
		time_diff = (int)difftime(cs_data->event_boot_time, prev_time);

	chg_in_rm_data->wireless_charger_state = check_wlc_state(sysfs_param[SFID_DC_ONLINE].intval);
	switch (chg_in_rm_data->wireless_charger_state) {
	case CHARGER_INSERTION:
		cs_data->usb_long_insertion_counter = 0;
		insertion_elapsed_time = 0;
		chg_in_rm_data->inserted_soc = sysfs_param[SFID_CAPACITY].intval;
		chg_in_rm_data->inserted_sc_stage = sysfs_param[SFID_AGING_LEVEL].intval;
		chg_in_rm_data->moment_max_vbatt = sysfs_param[SFID_VOLTAGE_NOW].intval;
		chg_in_rm_data->wlc_epp_txid = sysfs_param[SFID_WLS_TXID].intval;
		break;
	case CHARGER_INSERTING:
		chg_in_rm_data->thermal_level_time[prev_thermal_lv] += time_diff;

		if (!chg_in_rm_data->battery_care_flg) {
			if (sysfs_param[SFID_SMT_CHARGING_STATUS].intval)
				chg_in_rm_data->battery_care_flg = true;
			else
				chg_in_rm_data->battery_care_flg = false;
		}

		if (sysfs_param[SFID_VOLTAGE_NOW].intval > chg_in_rm_data->moment_max_vbatt)
			chg_in_rm_data->moment_max_vbatt = sysfs_param[SFID_VOLTAGE_NOW].intval;

		if (sysfs_param[SFID_DC_ONLINE].intval)
			snprintf(chg_in_rm_data->charger_type, sizeof(chg_in_rm_data->charger_type),
									"%s", sysfs_param[SFID_WLC_TYPE].strval);
		break;
	case CHARGER_REMOVAL:
		if (strlen(chg_in_rm_data->charger_type) == 0)
			snprintf(chg_in_rm_data->charger_type, sizeof(chg_in_rm_data->charger_type),
									"%s", CHARGER_BAT_CONNECTION);

		chg_in_rm_data->thermal_level_time[prev_thermal_lv] += time_diff;

		chg_in_rm_data->removal_soc = sysfs_param[SFID_CAPACITY].intval;
		chg_in_rm_data->removal_sc_stage = sysfs_param[SFID_AGING_LEVEL].intval;

		if (!chg_in_rm_data->battery_care_flg) {
			if (sysfs_param[SFID_SMT_CHARGING_STATUS].intval)
				chg_in_rm_data->battery_care_flg = true;
			else
				chg_in_rm_data->battery_care_flg = false;
		}

		if (sysfs_param[SFID_VOLTAGE_NOW].intval > chg_in_rm_data->moment_max_vbatt)
			chg_in_rm_data->moment_max_vbatt = sysfs_param[SFID_VOLTAGE_NOW].intval;
		return;
	case CHARGER_NO_INSERTING:
		break;
	default:
		break;
	}

	chg_in_rm_data->charger_state = check_chgr_state(sysfs_param[SFID_USB_ONLINE].intval);
	switch (chg_in_rm_data->charger_state) {
	case CHARGER_INSERTION:
		cs_data->usb_long_insertion_counter = 0;
		insertion_elapsed_time = 0;
		chg_in_rm_data->inserted_soc = sysfs_param[SFID_CAPACITY].intval;
		chg_in_rm_data->inserted_sc_stage = sysfs_param[SFID_AGING_LEVEL].intval;
		chg_in_rm_data->moment_max_usbin_voltage = sysfs_param[SFID_USB_VOLTAGE_NOW].intval;
		chg_in_rm_data->moment_max_vbatt = sysfs_param[SFID_VOLTAGE_NOW].intval;
		icl_min_bit = 0;
		prev_icl_min_bit = 0;
		break;
	case CHARGER_INSERTING:
		chg_in_rm_data->usb_insertion_time += time_diff;
		chg_in_rm_data->thermal_level_time[prev_thermal_lv] += time_diff;

		if ((chg_in_rm_data->usb_insertion_time - insertion_elapsed_time) > USB_LONG_INSERTION_TIME) {
			cs_data->usb_long_insertion_counter++;
			insertion_elapsed_time = USB_LONG_INSERTION_TIME * cs_data->usb_long_insertion_counter;
		}

		if (!chg_in_rm_data->battery_care_flg) {
			if (sysfs_param[SFID_SMT_CHARGING_STATUS].intval)
				chg_in_rm_data->battery_care_flg = true;
			else
				chg_in_rm_data->battery_care_flg = false;
		}

		icl_min_bit = sysfs_param[SFID_REG_AICL_STATUS].intval & ICL_MIN_BIT;
		if (!prev_icl_min_bit && icl_min_bit)
			chg_in_rm_data->icl_min_counter++;

		prev_icl_min_bit = icl_min_bit;
		if (sysfs_param[SFID_USB_VOLTAGE_NOW].intval > chg_in_rm_data->moment_max_usbin_voltage)
			chg_in_rm_data->moment_max_usbin_voltage = sysfs_param[SFID_USB_VOLTAGE_NOW].intval;

		if (sysfs_param[SFID_VOLTAGE_NOW].intval > chg_in_rm_data->moment_max_vbatt)
			chg_in_rm_data->moment_max_vbatt = sysfs_param[SFID_VOLTAGE_NOW].intval;

		if (sysfs_param[SFID_USB_ONLINE].intval) {
			snprintf(chg_in_rm_data->charger_type, sizeof(chg_in_rm_data->charger_type),
									"%s", sysfs_param[SFID_USB_TYPE].raw);
		}

		break;
	case CHARGER_REMOVAL:
		chg_in_rm_data->usb_insertion_time += time_diff;
		if ((chg_in_rm_data->usb_insertion_time - insertion_elapsed_time) > USB_LONG_INSERTION_TIME) {
			cs_data->usb_long_insertion_counter++;
			insertion_elapsed_time = USB_LONG_INSERTION_TIME * cs_data->usb_long_insertion_counter;
		}

		if (strlen(chg_in_rm_data->charger_type) == 0)
			snprintf(chg_in_rm_data->charger_type, sizeof(chg_in_rm_data->charger_type),
									"%s", CHARGER_BAT_CONNECTION);

		chg_in_rm_data->thermal_level_time[prev_thermal_lv] += time_diff;

		chg_in_rm_data->removal_soc = sysfs_param[SFID_CAPACITY].intval;
		chg_in_rm_data->removal_sc_stage = sysfs_param[SFID_AGING_LEVEL].intval;

		if (!chg_in_rm_data->battery_care_flg) {
			if (sysfs_param[SFID_SMT_CHARGING_STATUS].intval)
				chg_in_rm_data->battery_care_flg = true;
			else
				chg_in_rm_data->battery_care_flg = false;
		}

		if (sysfs_param[SFID_USB_VOLTAGE_NOW].intval > chg_in_rm_data->moment_max_usbin_voltage)
			chg_in_rm_data->moment_max_usbin_voltage = sysfs_param[SFID_USB_VOLTAGE_NOW].intval;

		if (sysfs_param[SFID_VOLTAGE_NOW].intval > chg_in_rm_data->moment_max_vbatt)
			chg_in_rm_data->moment_max_vbatt = sysfs_param[SFID_VOLTAGE_NOW].intval;
		return;
	case CHARGER_NO_INSERTING:
		return;
	default:
		break;
	}

	if (sysfs_param[SFID_SYSTEM_TEMP_LEVEL].intval == sysfs_param[SFID_SYSTEM_TEMP_LEVEL_MAX].intval)
		chg_in_rm_data->usb_connector_heat_flg = true;
	else
		chg_in_rm_data->usb_connector_heat_flg = false;

	prev_time = cs_data->event_boot_time;
	prev_thermal_lv = sysfs_param[SFID_SYSTEM_TEMP_LEVEL].intval;
	return;
}
