/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/

#include <stdlib.h>
#include <string.h>
#include <miscta.h>
#include <miscta_units.h>
#include "charge-service.h"
#include "miscta_batt_stat.h"
#include "log.h"

#define BATT_SOC_MAX_VAL	11000			/* 110.00% */
#define BATT_SOC_INITIAL_VAL	BATT_SOC_MAX_VAL
#define STAY_CAP_DEGRADATION_MAG	1000000		/* 10^6 */

#if 0
void dump_miscta_batt_stat(struct batt_stat_t *batt_stat)
{
	int i, j;

	LOGD("****** dump miscTA2491 BatteryStatistics cache -S- *****\n");
	LOGD("****** Common & SOH(FCC Learning) Area -S- *****\n");
	LOGD("initialize = %u\n", batt_stat->initialize);
	LOGD("version = %u.%u.%u\n",
			batt_stat->version[0],
			batt_stat->version[1],
			batt_stat->version[2]);

	LOGD("fcc_mah = ");
	for (i = 0; i < MAX_FCC_NUM; i++) {
		LOGD("[%u]", batt_stat->fcc_mah[i]);
	}
	LOGD("\n");

	LOGD("learning_total_cnt = %u\n", batt_stat->learning_total_cnt);

	LOGD("battery_model_name = ");
	for (i = 0;i < MAX_BATTERY_MODEL_NAME; i++) {
		LOGD("%x", batt_stat->battery_model_name[i]);
	}
	LOGD("\n");

	LOGD("initialized_time = %lu\n", batt_stat->initialized_time);
	LOGD("last_learning_time = %lu\n", batt_stat->last_learning_time);
	LOGD("first_learning_time = %lu\n", batt_stat->first_learning_time);

	LOGD("first_soh_time[0-2] = %lu, %lu, %lu\n",
			 batt_stat->first_soh_time[0],
			 batt_stat->first_soh_time[1],
			 batt_stat->first_soh_time[2]);
	LOGD("first_soh_time[3-5] = %lu, %lu, %lu\n",
			 batt_stat->first_soh_time[3],
			 batt_stat->first_soh_time[4],
			 batt_stat->first_soh_time[5]);
	LOGD("first_soh_time[6-8] = %lu, %lu, %lu\n",
			 batt_stat->first_soh_time[6],
			 batt_stat->first_soh_time[7],
			 batt_stat->first_soh_time[8]);
	LOGD("****** Common & SOH(FCC Learning) Area -E- *****\n");

	LOGD("****** Soft Charge Management Area -S- *****\n");
	LOGD("soft_charge_mode = %u\n", batt_stat->soft_charge_mode);
	LOGD("total_cycle_count=%u", batt_stat->total_cycle_count);
	for (i = 0; i < MAX_SC1_TIME_NUM; i++) {
		LOGD("sc1_lv%d_first_start_time=%lu\n", i + 1, batt_stat->sc1_first_start_time[i]);
	}
	LOGD("****** Soft Charge Management Area -E- *****\n");
	LOGD("****** VtCet Table Area -S- *****\n");
	for (i = 0;i < MAX_VBATT_STEP; i++) {
		for (j = 0; j < MAX_TEMP_STEP; j++) {
			if (batt_stat->vt_cet_table[i][j] > 0)
				LOGD("vt_cet_table[%d][%d]=%u", i, j, batt_stat->vt_cet_table[i][j]);
		}
	}
	LOGD("****** VtCet Table Area -E- *****\n");

	LOGD("****** CtCharge Table Area -S- *****\n");
	for (i = 0;i < MAX_SOC_STEP; i++) {
		for (j = 0; j < MAX_TEMP_STEP; j++) {
			if (batt_stat->ct_charge_table[i][j] > 0)
				LOGD("ct_charge_table[%d][%d]=%u", i, j, batt_stat->ct_charge_table[i][j]);
		}
	}
	LOGD("****** CtCharge Table Area -E- *****\n");
	LOGD("****** Misc Area -S- *****\n");
	LOGD("full_cnt = %u\n", batt_stat->full_cnt);
	LOGD("recharge_cnt = %u\n", batt_stat->recharge_cnt);
	LOGD("learning_try_cnt = %u\n", batt_stat->learning_try_cnt);
	LOGD("soc0_shutdown_cnt = %u\n", batt_stat->soc0_shutdown_cnt);
	LOGD("safety_timer_cnt = %u\n", batt_stat->safety_timer_cnt);
	LOGD("off_charge_total_time=%lu", batt_stat->off_charge_total_time);
	LOGD("on_charge_total_time=%lu", batt_stat->on_charge_total_time);
	LOGD("soc_full_time = %lu\n", batt_stat->soc_full_time);
	LOGD("smart_charge_mode_time = %lu\n", batt_stat->smart_charge_mode_time);
	for (i = 0;i < THERMAL_RANGE_NUM; i++) {
		LOGD("thermal_range_stay_time[%d]=%u", i, batt_stat->thermal_range_stay_time[i]);
	}
	LOGD("over_08c_total_time=%u", batt_stat->over_08c_total_time);
	LOGD("over_08c_charge_count=%u", batt_stat->over_08c_charge_count);
	LOGD("over_06c_total_time=%u", batt_stat->over_06c_total_time);
	LOGD("over_06c_charge_count=%u", batt_stat->over_06c_charge_count);
	for (i = 0;i < MAX_DISCHARGE_CURRENT_NUM; i++) {
		LOGD("max_discharge_current[%d]=%u", i, batt_stat->max_discharge_current[i]);
	}
	LOGD("max_temp=%d", batt_stat->max_temp);
	LOGD("min_temp=%d", batt_stat->min_temp);
	for (i = 0;i < MAX_DISCHARGE_CURRENT_NUM; i++) {
		LOGD("max_discharge_current_time[%d]=%u", i, batt_stat->max_discharge_current_time[i]);
	}
	LOGD("min_temp_time=%u", batt_stat->min_temp_time);
	LOGD("max_temp_time=%u", batt_stat->max_temp_time);
	for (i = 0; i < MAX_DISCHARGE_CASE; i++) {
		LOGD("total_discharge_time[%d]=%u", i, batt_stat->total_discharge_time[i]);
	}
	LOGD("fcc_mah_raw = ");
	for (i = 0;i < MAX_FCC_NUM; i++) {
		LOGD("[%u]", batt_stat->fcc_mah_raw[i]);
	}
	LOGD("\n");
	LOGD("max_cell_voltage=%u", batt_stat->max_cell_voltage);
	LOGD("max_cell_voltage_time=%u", batt_stat->max_cell_voltage_time);
	LOGD("****** Misc Area -E- *****\n");

	LOGD("****** Charger Info Area -S- *****\n");
	for (i = 0; i < MAX_DEV_TYPES; i++) {
		LOGD("dev%d_attach_count=%u\n", i + 1, batt_stat->dev[i].attach_count);
		LOGD("dev%d_attach_time=%u\n", i + 1, batt_stat->dev[i].attach_time);
		LOGD("dev%d_charge_count=%u\n", i + 1, batt_stat->dev[i].charge_count);
	}
	LOGD("****** Charger Info Area -E- *****\n");

	LOGD("****** Arrhenius Area -S- *****\n");
	LOGD("online_time=%u", batt_stat->online_time);
	LOGD("total_arrhenius=%u", batt_stat->total_arrhenius);

	for (i = 0;i < ARRHENIUS_RECORDS_NUM; i++) {
		if (batt_stat->arrhenius_per_10days[i] > 0)
			LOGD("arrhenius_per_10days[%d]=%u", i, batt_stat->arrhenius_per_10days[i]);
	}
	for (i = 0;i < ARRHENIUS_RECORDS_NUM; i++) {
		if (batt_stat->arrhenius_aging_level_record[i] != 0xff)
			LOGD("arrhenius_aging_level_record[%d]=%hhu", i, batt_stat->arrhenius_aging_level_record[i]);
	}
	LOGD("****** Arrhenius Area -E- *****\n");
	LOGD("****** dump miscTA2491 BatteryStatistics cache -E- *****\n");
}
#endif

static bool adapt_batt_stat_version(struct batt_stat_t *batt_stat)
{
	int i;

	if (batt_stat->version[0] != BATT_STAT_MAJOR_VERSION) {
		/* Clear all */
		return false;
	} else {
		if (batt_stat->version[1] != BATT_STAT_MINOR_VERSION) {
			if (batt_stat->version[1] == 0) {
				/* Initialize new parameters area */
				for (i = 0; i < MAX_SC5_TIME_NUM; i++) {
					batt_stat->sc5_first_start_time[i] = 0x00000000;
				}
				memset(batt_stat->battery_model_name, 0, sizeof(batt_stat->battery_model_name));
			}

			if (batt_stat->version[1] < 2)
				return false;

			batt_stat->version[1] = BATT_STAT_MINOR_VERSION;
			batt_stat->version[2] = BATT_STAT_REVISION_VERSION;
		} else {
			if (batt_stat->version[2] != BATT_STAT_REVISION_VERSION) {
				if (batt_stat->version[2] == 0)
					return false;

				batt_stat->version[2] = BATT_STAT_REVISION_VERSION;
			}
		}
	}

	return true;
}

#define UNINITIALIZED_ID	0x00
#define FULL_RESET_ID		0xff

void init_batt_stat(struct cs_data_t *cs_data, struct batt_stat_t *batt_stat)
{
	miscta_status_t mt_status;
	uint32_t size;
	int i;
	bool batt_stat_ready = false;

	size = sizeof(struct batt_stat_t);
	mt_status = miscta_read_unit(TA_BATTERY_STATISTICS, batt_stat, &size);

	if (mt_status == MT_SUCCESS) {
		if (size >= 1 && batt_stat->initialize == FULL_RESET_ID) {
			cs_data->force_restoring_charge_full = true;
			batt_stat->initialize = UNINITIALIZED_ID;
		}

		if (size >= CURRENT_BATT_STAT_COMPATIBLE_SIZE &&
				batt_stat->initialize != UNINITIALIZED_ID) {
			if (cs_data->force_restoring_charge_full) {
				batt_stat->last_learning_time = 0;
				batt_stat->first_learning_time = 0;
				for (i = 0; i < MAX_FCC_NUM; i++) {
					batt_stat->fcc_mah[i] = 0;
					batt_stat->fcc_mah_raw[i] = 0;
				}
				batt_stat->learning_total_cnt = 0;
				for (i = 0; i < MAX_SOH_TIME_NUM; i++)
					batt_stat->first_soh_time[i] = 0;
			}

			batt_stat_ready = adapt_batt_stat_version(batt_stat);
		}
	}

	if (!batt_stat_ready) {
		memset(batt_stat, 0, sizeof(struct batt_stat_t));
		batt_stat->initialize = 1;
		batt_stat->version[0] = BATT_STAT_MAJOR_VERSION;
		batt_stat->version[1] = BATT_STAT_MINOR_VERSION;
		batt_stat->version[2] = BATT_STAT_REVISION_VERSION;

		batt_stat->max_temp = -32768;
		batt_stat->min_temp = 32767;

		for (i = 0; i < ARRHENIUS_RECORDS_NUM; i++)
			batt_stat->arrhenius_aging_level_record[i] = 0xff;

		for (i = 0; i < STAY_CAP_DEGRADE_RECORDS_NUM ; i++)
			batt_stat->full_stay_cap_degradation_aging_level_record[i] = 0xff;

		for (i = 0; i < SOH_RECORDS_NUM ; i++) {
			batt_stat->soh_record[i] = 0xff;
		}
	}

	cs_data->online_time = batt_stat->online_time;
	cs_data->total_arrhenius_f = (long double)batt_stat->total_arrhenius;
	for (i = 0; i < ARRHENIUS_RECORDS_NUM; i++)
		cs_data->arrhenius_per_10days_f[i] = (long double)batt_stat->arrhenius_per_10days[i];

	size = sizeof(uint8_t);
	mt_status = miscta_read_unit(TA_USB_CONNECTOR_HEAT_COUNT, &cs_data->usb_connector_heat_count, &size);
	if (mt_status != MT_SUCCESS || size != sizeof(uint8_t))
		cs_data->usb_connector_heat_count = 0;

	size = sizeof(time_t);
	mt_status = miscta_read_unit(TA_USB_CONNECTOR_HEAT_TIMESTAMP, &cs_data->usb_connector_heat_time, &size);
	if (mt_status != MT_SUCCESS || size != sizeof(time_t))
		cs_data->usb_connector_heat_time = 0;

	for (i = 0; i < STAY_CAP_DEGRADE_RECORDS_NUM; i++) {
		cs_data->full_stay_cap_degr_per_10days_f[i] =
			(long double)batt_stat->full_stay_cap_degradation_per_10days[i] / STAY_CAP_DEGRADATION_MAG;
		cs_data->total_full_stay_cap_degr_f += (long double)batt_stat->full_stay_cap_degradation_per_10days[i] / STAY_CAP_DEGRADATION_MAG;
	}

	cs_data->full_stay_cap_degr_aging_level = batt_stat->full_stay_cap_degradation_aging_level_record[i];
}

#define BATT_STAT_SAVING_INTERVAL    (24 * 60 * 60)	/* 24 hour */

bool can_save_batt_stat(struct cs_data_t *cs_data, const struct sysfs_param_t *sysfs_param,  const struct batt_stat_t *batt_stat)
{
	bool is_save = false;
	static uint64_t prev_last_learning_time = -1;

	if ((int)difftime(cs_data->event_boot_time, cs_data->batt_stat_saved_time)
							>= BATT_STAT_SAVING_INTERVAL) {
		is_save = true;
		goto out;
	}

	if (sysfs_param[SFID_SYSTEM_STATUS].intval == SYSTEM_STATUS_SHUTDOWN) {
		is_save = true;
		goto out;
	}

	if ((prev_last_learning_time != -1) &&
		(batt_stat->last_learning_time != prev_last_learning_time)) {
		is_save = true;
		goto out;
	}

out:
	prev_last_learning_time = batt_stat->last_learning_time;
	return is_save;
}

void save_batt_stat(struct cs_data_t *cs_data, const struct batt_stat_t *batt_stat)
{
	miscta_status_t mt_status;
	uint32_t size;

	size = sizeof(struct batt_stat_t);
	mt_status = miscta_write_unit(TA_BATTERY_STATISTICS, batt_stat, size);
	if (mt_status != MT_SUCCESS) {
		LOG("Failed to save battery statistics");
		return;
	}

	size = sizeof(uint8_t);
	mt_status = miscta_write_unit(TA_USB_CONNECTOR_HEAT_COUNT, &cs_data->usb_connector_heat_count, size);
	if (mt_status != MT_SUCCESS) {
		LOG("Failed to save USB connector heat count");
		return;
	}

	size = sizeof(time_t);
	mt_status = miscta_write_unit(TA_USB_CONNECTOR_HEAT_TIMESTAMP, &cs_data->usb_connector_heat_time, size);
	if (mt_status != MT_SUCCESS) {
		LOG("Failed to save USB connector heat time");
		return;
	}

	cs_data->batt_stat_saved_time = cs_data->event_boot_time;
}

#define WARRANTY_CYCLE_COUNT	3000

static void set_initial_time_if_required(struct cs_data_t *cs_data, struct batt_stat_t *batt_stat)
{
	if (batt_stat->initialized_time)
		return;

	if (!is_adjusted_time(cs_data->event_system_time) || batt_stat->total_cycle_count < WARRANTY_CYCLE_COUNT)
		return;

	batt_stat->initialized_time = cs_data->event_system_time - cs_data->event_boot_time;
}

static void set_battery_model_name_if_required(
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	UNUSED(cs_data);

	if (strlen((const char *)batt_stat->battery_model_name) > 0)
		return;

	strlcpy((char *)batt_stat->battery_model_name, sysfs_param[SFID_BATT_TYPE].raw,
								MAX_BATTERY_MODEL_NAME);
}

#define CALCULATE_SOH(x, y) (((x) * 100) / (y))
#define MAX_SOH             100
static void set_soh_record(struct cs_data_t *cs_data, struct batt_stat_t *batt_stat, const struct sysfs_param_t *sysfs_param)
{
	int current_soh_index;
	int soh;

	if (sysfs_param[SFID_CHARGE_FULL].intval && sysfs_param[SFID_CHARGE_FULL_DESIGN].intval) {
		soh = CALCULATE_SOH(sysfs_param[SFID_CHARGE_FULL].intval,
				sysfs_param[SFID_CHARGE_FULL_DESIGN].intval);
	} else {
		soh = MAX_SOH;
	}

	current_soh_index = cs_data->online_time / SECONDS_IN_10DAYS;
	if (current_soh_index >= SOH_RECORDS_NUM) {
		current_soh_index = SOH_RECORDS_NUM - 1;
	}

	batt_stat->soh_record[current_soh_index] = (uint32_t)soh;
	cs_data->soh = soh;
}

#define INVALID_AGING_LEVEL -1
static void set_learning_state(
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	static int prev_aging_lv = INVALID_AGING_LEVEL;
	int i;
	int current_aging_lv;
	static const int low_check_soh[MAX_SOH_TIME_NUM] = {95, 90, 85, 80, 70, 60, 50, 40, 20};
	static int prev_learning_count = 0;

	current_aging_lv = sysfs_param[SFID_AGING_LEVEL].intval;
	if (sysfs_param[SFID_LEARNING_COUNT].intval != prev_learning_count ) {
		if (!batt_stat->first_learning_time)
			batt_stat->first_learning_time = cs_data->event_system_time;

		for (i = (MAX_FCC_NUM - 1); i > 0; i--) {
			batt_stat->fcc_mah_raw[i] = batt_stat->fcc_mah_raw[(i - 1)];
			batt_stat->fcc_mah[i] = batt_stat->fcc_mah[(i - 1)];
		}

		batt_stat->fcc_mah_raw[0] = sysfs_param[SFID_LEARNED_CAPACITY].intval;
		batt_stat->fcc_mah[0] = sysfs_param[SFID_CHARGE_FULL].intval / 1000;
		batt_stat->last_learning_time = cs_data->event_system_time;
		batt_stat->learning_total_cnt += sysfs_param[SFID_LEARNING_COUNT].intval - prev_learning_count;

		/* save a SOH result */
		for (i = 0; i < MAX_SOH_TIME_NUM; i++) {
			if (batt_stat->first_soh_time[i])
				continue;

			if (cs_data->soh < low_check_soh[i])
				batt_stat->first_soh_time[i] = cs_data->event_system_time;
		}

	} else if (prev_aging_lv > INVALID_AGING_LEVEL &&
					prev_aging_lv != current_aging_lv) {
		for (i = (MAX_FCC_NUM - 1); i > 0; i--) {
			batt_stat->fcc_mah[i] = batt_stat->fcc_mah[(i - 1)];
		}
		batt_stat->fcc_mah[0] = sysfs_param[SFID_CHARGE_FULL].intval / 1000;

		/* save a SOH result */
		for (i = 0; i < MAX_SOH_TIME_NUM; i++) {
			if (batt_stat->first_soh_time[i])
				continue;

			if (cs_data->soh < low_check_soh[i])
				batt_stat->first_soh_time[i] = cs_data->event_system_time;
		}
	}
	prev_learning_count = sysfs_param[SFID_LEARNING_COUNT].intval;
	prev_aging_lv = current_aging_lv;
}

static int get_temp_step_idx(int real_temp)
{
	int i;
	static const int temp_step_range_table[] = {
		600,
		550,
		500,
		450,
		400,
		350,
		300,
		250,
		200,
		150,
		100,
		50,
		0,
		-50,
		-100
	};

	for (i = 0; i < (int)(sizeof(temp_step_range_table) / sizeof(temp_step_range_table[0])); i++) {
		if (real_temp > temp_step_range_table[i])
			break;
	}
	return i;
}

static int get_vbatt_step_idx(int vbatt)
{
	int i;
	static const int vbatt_step_range_table[] = {
		4490000,
		4480000,
		4470000,
		4460000,
		4450000,
		4440000,
		4430000,
		4420000,
		4410000,
		4400000,
		4390000,
		4380000,
		4370000,
		4360000,
		4350000,
		4340000,
		4330000,
		4320000,
		4310000,
		4300000,
		4290000,
		4280000,
		4270000,
		4260000,
		4250000,
		4240000,
		4230000,
		4220000,
		4210000,
		4200000,
		4150000,
		4100000,
		4050000,
		4000000,
		3800000,
		3600000,
		3400000,
		3300000,
		3200000,
		3100000,
		3000000
	};

	for (i = 0; i < (int)(sizeof( vbatt_step_range_table) / sizeof( vbatt_step_range_table[0])); i++) {
		if (vbatt >  vbatt_step_range_table[i])
			break;
	}

	return i;
}

static int get_soc_step_idx(int batt_soc)
{
	int i;
	static const int soc_step_range_table[] = {
		9000,
		8000,
		7000,
		6000,
		5000,
		4000,
		3000,
		2000,
		1000
	};

	for (i = 0; i < (int)(sizeof(soc_step_range_table) / sizeof(soc_step_range_table[0])); i++) {
		if (batt_soc > soc_step_range_table[i])
			break;
	}

	return i;
}

static void set_vt_cet_table(
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	static int prev_temp_step_idx = 0;
	static int prev_temp = 0;
	static int prev_vbatt_step_idx = 0;
	static int prev_vbatt = 0;
	static time_t prev_time = 0;
	int temp_step_idx, vbatt_step_idx;
	int temp, vbatt;
	int vbatt_diff, temp_diff, time_diff;
	int i;

	temp = sysfs_param[SFID_TEMP].intval;
	temp_step_idx = get_temp_step_idx(temp);
	vbatt = sysfs_param[SFID_VOLTAGE_NOW].intval;
	vbatt_step_idx = get_vbatt_step_idx(vbatt);
	time_diff = (int)difftime(cs_data->event_boot_time, prev_time);

	if (prev_time && time_diff > 0) {
		if (temp_step_idx == prev_temp_step_idx &&
					vbatt_step_idx == prev_vbatt_step_idx) {
			batt_stat->vt_cet_table[vbatt_step_idx][temp_step_idx] += (uint32_t)time_diff;
		} else {
			vbatt_diff = vbatt - prev_vbatt;
			temp_diff = temp - prev_temp;
			for (i = 0; i < time_diff; i++) {
				temp_step_idx = get_temp_step_idx(INTERPOLATE(prev_temp, temp_diff, time_diff, i));
				vbatt_step_idx = get_vbatt_step_idx(INTERPOLATE(prev_vbatt, vbatt_diff, time_diff, i));
				batt_stat->vt_cet_table[vbatt_step_idx][temp_step_idx]++;
			}
		}
	}

	prev_temp = temp;
	prev_temp_step_idx = temp_step_idx;
	prev_vbatt = vbatt;
	prev_vbatt_step_idx = vbatt_step_idx;
	prev_time = cs_data->event_boot_time;
}

static void set_ct_charge_table(
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	static int prev_temp_step_idx = 0;
	static int prev_temp = 0;
	static int prev_soc_step_idx= 0;
	static int prev_batt_soc = BATT_SOC_INITIAL_VAL;
	int soc_step_idx, temp_step_idx;
	int batt_soc, temp;
	int soc_diff, temp_diff;
	int i;

	UNUSED(cs_data);

	temp = sysfs_param[SFID_TEMP].intval;
	temp_step_idx = get_temp_step_idx(temp);
	batt_soc = sysfs_param[SFID_BATTERY_SOC].intval;
	if (batt_soc < 0 || batt_soc > BATT_SOC_MAX_VAL) {
		LOG("batt_soc is not valid (%d), ct_charge_table is not updated\n", batt_soc);
		return;
	}
	soc_step_idx = get_soc_step_idx(batt_soc);
	soc_diff = batt_soc - prev_batt_soc;
	if (batt_soc > prev_batt_soc) {
		if (temp_step_idx == prev_temp_step_idx && soc_step_idx == prev_soc_step_idx) {
			batt_stat->ct_charge_table[soc_step_idx][temp_step_idx] += (uint32_t)soc_diff;
		} else {
			temp_diff = temp - prev_temp;
			for (i = 0; i < soc_diff; i++) {
				temp_step_idx = get_temp_step_idx(INTERPOLATE(prev_temp, temp_diff, soc_diff, i));
				soc_step_idx = get_soc_step_idx(prev_batt_soc + i);
				batt_stat->ct_charge_table[soc_step_idx][temp_step_idx]++;
			}
		}
		batt_stat->total_cycle_count += (uint32_t)soc_diff;
	}

	prev_temp_step_idx = temp_step_idx;
	prev_temp = temp;
	prev_soc_step_idx = soc_step_idx;
	prev_batt_soc = batt_soc;
}

static void set_charge_total_time(
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	static time_t prev_charging_time = 0;
	static int prev_system_status = SYSTEM_STATUS_BOOTUP;

	if (prev_charging_time) {
		if (prev_system_status == SYSTEM_STATUS_ANDROID)
			batt_stat->on_charge_total_time +=
					(uint64_t)difftime(cs_data->event_boot_time, prev_charging_time);
		else if (prev_system_status == SYSTEM_STATUS_POWER_OFF_CHARGE)
			batt_stat->off_charge_total_time +=
					(uint64_t)difftime(cs_data->event_boot_time, prev_charging_time);
		prev_charging_time = 0;
	}

	if (sysfs_param[SFID_STATUS].intval == STATE_CHARGE || sysfs_param[SFID_STATUS].intval == STATE_FULL)
		prev_charging_time = cs_data->event_boot_time;

	prev_system_status = sysfs_param[SFID_SYSTEM_STATUS].intval;
}

static void set_smart_charge_state(
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	static time_t prev_smart_charge_time = 0;
	static time_t prev_soc_full_time = 0;

	if (prev_smart_charge_time) {
		batt_stat->smart_charge_mode_time +=
			(uint64_t)difftime(cs_data->event_boot_time, prev_smart_charge_time);
		prev_smart_charge_time = 0;
	}

	if (prev_soc_full_time) {
		batt_stat->soc_full_time +=
			(uint64_t)difftime(cs_data->event_boot_time, prev_soc_full_time);
		prev_soc_full_time = 0;
	}

	if (sysfs_param[SFID_CAPACITY].intval >= 100)
		prev_soc_full_time = cs_data->event_boot_time;

	if (sysfs_param[SFID_SMT_CHARGING_STATUS].intval == 1)
		prev_smart_charge_time = cs_data->event_boot_time;
}

static void set_jeita_warm_time(
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	static time_t prev_jeita_warm_time = 0;

	/* Check jeita health */
	if (prev_jeita_warm_time) {
		batt_stat->jeita_warm_time +=
					(uint64_t)difftime(cs_data->event_boot_time, prev_jeita_warm_time);
		prev_jeita_warm_time = 0;
	}
	if (sysfs_param[SFID_HEALTH].intval == HEALTH_WARM)
		prev_jeita_warm_time = cs_data->event_boot_time;
}

enum {
	USB_PD_PWR_RANK_1,
	USB_PD_PWR_RANK_2,
	USB_PD_PWR_RANK_3,
	USB_PD_PWR_RANK_4,
	USB_PD_PWR_RANK_MAX
};

static int usb_pd_pwr_rank_threshold[] =
{
	[USB_PD_PWR_RANK_1] = 18000000,	/* ~18W */
	[USB_PD_PWR_RANK_2] = 30000000,	/* ~30W */
	[USB_PD_PWR_RANK_3] = 45000000,	/* ~45W */
	[USB_PD_PWR_RANK_4] = 65000000	/* ~65W */
	/* USB_PD_PWR_RANK_MAX */	/* above 65W */
};

static int get_aggr_charger_type(const struct sysfs_param_t *sysfs_param)
{
	int aggr_charger_type = AGGR_CHARGER_TYPE_UNKNOWN;
	int usb_pd_pwr_rank;

	switch (sysfs_param[SFID_ACTIVE_CHAGER_TYPE].intval) {
	case SSDEV_PARTNER_SNK_USB_DCP:
		aggr_charger_type = AGGR_CHARGER_TYPE_USB_DCP;
		break;
	case SSDEV_PARTNER_SNK_USB_SDP:
		aggr_charger_type = AGGR_CHARGER_TYPE_USB_SDP;
		break;
	case SSDEV_PARTNER_SNK_USB_CDP:
		aggr_charger_type = AGGR_CHARGER_TYPE_USB_CDP;
		break;
	case SSDEV_PARTNER_SNK_USB_OCP:
		aggr_charger_type = AGGR_CHARGER_TYPE_USB_PROPRIETARY;
		break;
	case SSDEV_PARTNER_SNK_TYPEC_DEFAULT:
	case SSDEV_PARTNER_SNK_TYPEC_RP_MEDIUM_1P5A:
	case SSDEV_PARTNER_SNK_TYPEC_RP_HIGH_3A:
		aggr_charger_type = AGGR_CHARGER_TYPE_USB_TYPEC;
		break;
	case SSDEV_PARTNER_SNK_PD:
	case SSDEV_PARTNER_SNK_PPS:
		for (usb_pd_pwr_rank = 0; usb_pd_pwr_rank < USB_PD_PWR_RANK_MAX; usb_pd_pwr_rank++) {
			if (sysfs_param[SFID_CHARGER_MAX_WATTAGE].intval <= usb_pd_pwr_rank_threshold[usb_pd_pwr_rank])
				break;
		}
		switch (usb_pd_pwr_rank) {
		case USB_PD_PWR_RANK_1:
			aggr_charger_type = AGGR_CHARGER_TYPE_USB_PD_RANK_1;
			break;
		case USB_PD_PWR_RANK_2:
			aggr_charger_type = AGGR_CHARGER_TYPE_USB_PD_RANK_2;
			break;
		case USB_PD_PWR_RANK_3:
			aggr_charger_type = AGGR_CHARGER_TYPE_USB_PD_RANK_3;
			break;
		case USB_PD_PWR_RANK_4:
			aggr_charger_type = AGGR_CHARGER_TYPE_USB_PD_RANK_4;
			break;
		case USB_PD_PWR_RANK_MAX:
			aggr_charger_type = AGGR_CHARGER_TYPE_USB_PD_RANK_5;
			break;
		}
		break;
	case SSDEV_PARTNER_SNK_USB_FLOAT:
		aggr_charger_type = AGGR_CHARGER_TYPE_USB_FLOATED;
		break;
	case SSDEV_PARTNER_SRC_TYPEC_AUDIO_ACCESS:
		aggr_charger_type = AGGR_CHARGER_TYPE_USB_AUDIO_ADAPTER;
		break;
	case SSDEV_PARTNER_WLS_SNK_BPP:
		aggr_charger_type = AGGR_CHARGER_TYPE_WIRELESS_QI_BPP;
		break;
	case SSDEV_PARTNER_WLS_SNK_EPP:
		aggr_charger_type = AGGR_CHARGER_TYPE_WIRELESS_QI_EPP;
		break;
	default:
		aggr_charger_type = AGGR_CHARGER_TYPE_UNKNOWN;
		break;
	}

	return aggr_charger_type;
}

static void set_dev_info(
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	static int prev_aggr_charger_type = AGGR_CHARGER_TYPE_UNKNOWN;
	static time_t prev_time = 0;
	static int prev_batt_soc = BATT_SOC_MAX_VAL;
	int aggr_charger_type;
	int batt_soc;

	aggr_charger_type = get_aggr_charger_type(sysfs_param);

	/* Check attach count */
	if ((aggr_charger_type != AGGR_CHARGER_TYPE_UNKNOWN) && (aggr_charger_type != prev_aggr_charger_type))
		batt_stat->dev[aggr_charger_type].attach_count++;

	/* Check attach time */
	if ((prev_aggr_charger_type != AGGR_CHARGER_TYPE_UNKNOWN) && (prev_time != 0)) {
		batt_stat->dev[prev_aggr_charger_type].attach_time += (uint32_t)difftime(cs_data->event_boot_time, prev_time);
		prev_time = 0;
	}
	if (aggr_charger_type != AGGR_CHARGER_TYPE_UNKNOWN)
		prev_time = cs_data->event_boot_time;

	/* Check charge count */
	batt_soc = sysfs_param[SFID_BATTERY_SOC].intval;
	if ((prev_aggr_charger_type != AGGR_CHARGER_TYPE_UNKNOWN) && (batt_soc > prev_batt_soc)) {
		batt_stat->dev[prev_aggr_charger_type].charge_count += (uint32_t)(batt_soc - prev_batt_soc);
		prev_batt_soc = BATT_SOC_MAX_VAL;
	}
	if (aggr_charger_type != AGGR_CHARGER_TYPE_UNKNOWN)
		prev_batt_soc = batt_soc;

	prev_aggr_charger_type = aggr_charger_type;
}

void set_soc0_shutdown_cnt(
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	static int prev_system_status = -1;

	if (sysfs_param[SFID_SYSTEM_STATUS].intval != SYSTEM_STATUS_SHUTDOWN ||
			sysfs_param[SFID_SYSTEM_STATUS].intval == prev_system_status) {
		prev_system_status = sysfs_param[SFID_SYSTEM_STATUS].intval;
		return;
	}

	if (sysfs_param[SFID_CAPACITY].intval < 1)
		batt_stat->soc0_shutdown_cnt++;

	prev_system_status = sysfs_param[SFID_SYSTEM_STATUS].intval;
	return;
}

void set_thermal_range_stay_time(
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	static const int thermal_range_table[] = {0, 12, 13, 14};
	static time_t prev_time = 0;
	static int prev_system_temp_lv = 0;
	int time_diff = 0;
	int i;
	int max_thermal_range_table =
		(int)(sizeof(thermal_range_table) / sizeof(thermal_range_table[0]));

	time_diff = (int)difftime(cs_data->event_boot_time, prev_time);
	if (prev_time && time_diff > 0) {
		for (i = 0; i < max_thermal_range_table; i++) {
			if (prev_system_temp_lv <= thermal_range_table[i])
				break;
		}

		if (i < max_thermal_range_table)
			batt_stat->thermal_range_stay_time[i] += time_diff;
	}

	prev_system_temp_lv = sysfs_param[SFID_SYSTEM_TEMP_LEVEL].intval;
	prev_time = cs_data->event_boot_time;
}

#define CURRENT_0P8C_UA(cap) (cap * 8 / 10)
#define CURRENT_0P6C_UA(cap) (cap * 6 / 10)
void set_rapid_charge_time(
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	static int prev_cur_ma = 0;
	static time_t prev_time = 0;
	int charge_full_design, cur_now_ua, time_diff;

	charge_full_design = sysfs_param[SFID_CHARGE_FULL_DESIGN].intval;
	cur_now_ua = sysfs_param[SFID_CURRENT_NOW].intval;
	time_diff = (int)difftime(cs_data->event_boot_time, prev_time);
	if (prev_time && time_diff > 0) {
		if (prev_cur_ma >= CURRENT_0P8C_UA(charge_full_design) &&
			cur_now_ua >= CURRENT_0P8C_UA(charge_full_design))
			batt_stat->over_08c_total_time += time_diff;
		else if (prev_cur_ma >= CURRENT_0P6C_UA(charge_full_design) &&
			cur_now_ua >= CURRENT_0P6C_UA(charge_full_design))
			batt_stat->over_06c_total_time += time_diff;
	}

	prev_cur_ma = cur_now_ua;
	prev_time = cs_data->event_boot_time;
}

void set_rapid_charge_count(
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	static int prev_cur_ma = 0;
	static int prev_batt_soc = BATT_SOC_INITIAL_VAL;
	int charge_full_design, cur_now_ua, batt_soc, soc_diff;

	UNUSED(cs_data);
	charge_full_design = sysfs_param[SFID_CHARGE_FULL_DESIGN].intval;
	cur_now_ua = sysfs_param[SFID_CURRENT_NOW].intval;
	batt_soc = sysfs_param[SFID_BATTERY_SOC].intval;
	if (batt_soc < 0 || batt_soc > BATT_SOC_MAX_VAL) {
		LOG("batt_soc is not valid (%d), rapid_charge_count is not updated\n", batt_soc);
		return;
	}
	soc_diff = batt_soc - prev_batt_soc;
	if (soc_diff > 0) {
		if (prev_cur_ma >= CURRENT_0P8C_UA(charge_full_design) &&
			cur_now_ua >= CURRENT_0P8C_UA(charge_full_design))
			batt_stat->over_08c_charge_count += soc_diff;
		else if (prev_cur_ma >= CURRENT_0P6C_UA(charge_full_design) &&
			cur_now_ua >= CURRENT_0P6C_UA(charge_full_design))
			batt_stat->over_06c_charge_count += soc_diff;
	}

	prev_cur_ma = cur_now_ua;
	prev_batt_soc = batt_soc;
}

enum {
	DISCHARGE_CASE1 = 0,
	DISCHARGE_CASE2,
	DISCHARGE_CASE3,
	DISCHARGE_CASE4,
	DISCHARGE_CASE5,
	DISCHARGE_CASE6,
	DISCHARGE_CASE7,
	DISCHARGE_CASE8,
};

#define VBATT_3800MV	3800
#define VBATT_3500MV	3500
#define CURRENT_3A	3000
#define CURRENT_2A	2000
#define TEMP_15C	150
#define TEMP_10C	100
#define TEMP_5C		50
#define TEMP_0C		0
void set_max_discharge_current(
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	int16_t max_discharge_current[MAX_DISCHARGE_CURRENT_NUM] = {0, 0, 0, 0};
	int16_t discharge_current_ma = 0;
	int vbatt_mv;
	int temp;
	int i;

	if (sysfs_param[SFID_CURRENT_NOW].intval >= 0)
		return;

	vbatt_mv = sysfs_param[SFID_VOLTAGE_NOW].intval / 1000;
	temp = sysfs_param[SFID_TEMP].intval;
	discharge_current_ma = sysfs_param[SFID_CURRENT_NOW].intval / 1000;
	for (i = 0; i < MAX_DISCHARGE_CURRENT_NUM; i++) {
		max_discharge_current[i] = batt_stat->max_discharge_current[i] * -1;
	}

	if (discharge_current_ma < max_discharge_current[DISCHARGE_CASE1]) {
		max_discharge_current[DISCHARGE_CASE1] = discharge_current_ma;
		batt_stat->max_discharge_current[DISCHARGE_CASE1] = max_discharge_current[DISCHARGE_CASE1] * -1;
		batt_stat->max_discharge_current_time[DISCHARGE_CASE1] = (uint32_t)cs_data->event_system_time;
	}

	if (discharge_current_ma < max_discharge_current[DISCHARGE_CASE2]) {
		if (vbatt_mv < VBATT_3500MV && temp < TEMP_10C) {
			max_discharge_current[1] = discharge_current_ma;
			batt_stat->max_discharge_current[DISCHARGE_CASE2] = max_discharge_current[DISCHARGE_CASE2] * -1;
			batt_stat->max_discharge_current_time[DISCHARGE_CASE2] = (uint32_t)cs_data->event_system_time;
		}
	}

	if (discharge_current_ma < max_discharge_current[DISCHARGE_CASE3]) {
		if (vbatt_mv < VBATT_3500MV && temp < TEMP_5C) {
			max_discharge_current[DISCHARGE_CASE3] = discharge_current_ma;
			batt_stat->max_discharge_current[DISCHARGE_CASE3] = max_discharge_current[DISCHARGE_CASE3] * -1;
			batt_stat->max_discharge_current_time[DISCHARGE_CASE3] = (uint32_t)cs_data->event_system_time;
		}
	}

	if (discharge_current_ma < max_discharge_current[DISCHARGE_CASE4]) {
		if (vbatt_mv < VBATT_3500MV && temp < TEMP_0C) {
			max_discharge_current[DISCHARGE_CASE4] = discharge_current_ma;
			batt_stat->max_discharge_current[DISCHARGE_CASE4] = max_discharge_current[DISCHARGE_CASE4] * -1;
			batt_stat->max_discharge_current_time[DISCHARGE_CASE4] = (uint32_t)cs_data->event_system_time;
		}
	}

	return;
}

void set_total_discharge_time(
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	int current_ma;
	int vbatt_mv;
	int temp;
	int time_diff;
	static time_t prev_time = 0;

	if (sysfs_param[SFID_STATUS].intval != STATE_DISCHARGE) {
		prev_time = 0;
		return;
	}

	current_ma = (sysfs_param[SFID_CURRENT_NOW].intval / 1000) * -1;
	vbatt_mv = sysfs_param[SFID_VOLTAGE_NOW].intval / 1000;
	temp = sysfs_param[SFID_TEMP].intval;
	time_diff = (int)difftime(cs_data->event_boot_time, prev_time);

	if (prev_time && time_diff > 0) {
		if (current_ma > CURRENT_2A)
			batt_stat->total_discharge_time[DISCHARGE_CASE1] += time_diff;

		if (current_ma > CURRENT_3A)
			batt_stat->total_discharge_time[DISCHARGE_CASE2] += time_diff;

		if (current_ma > CURRENT_2A && temp < TEMP_15C)
			batt_stat->total_discharge_time[DISCHARGE_CASE3] += time_diff;

		if (current_ma > CURRENT_2A && temp < TEMP_15C && vbatt_mv  < VBATT_3500MV)
			batt_stat->total_discharge_time[DISCHARGE_CASE4] += time_diff;

		if (current_ma > CURRENT_2A && temp < TEMP_5C)
			batt_stat->total_discharge_time[DISCHARGE_CASE5] += time_diff;

		if (current_ma > CURRENT_2A && temp < TEMP_5C && vbatt_mv  < VBATT_3500MV)
			batt_stat->total_discharge_time[DISCHARGE_CASE6] += time_diff;

		if (current_ma > CURRENT_2A && temp < TEMP_0C)
			batt_stat->total_discharge_time[DISCHARGE_CASE7] += time_diff;

		if (current_ma > CURRENT_2A && temp < TEMP_0C && vbatt_mv < VBATT_3800MV)
			batt_stat->total_discharge_time[DISCHARGE_CASE8] += time_diff;
	}

	prev_time = cs_data->event_boot_time;
	return;
}

void set_max_cell_voltage(
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	uint16_t current_cell_voltage;

	current_cell_voltage = sysfs_param[SFID_VCELL_MAX].intval;
	if (current_cell_voltage > batt_stat->max_cell_voltage) {
		batt_stat->max_cell_voltage = current_cell_voltage;
		batt_stat->max_cell_voltage_time = (uint32_t)cs_data->event_system_time;
	}
	return;
}

void set_min_max_temp(
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	int32_t current_temp;

	current_temp = sysfs_param[SFID_TEMP].intval;
	if (current_temp > batt_stat->max_temp) {
		batt_stat->max_temp = current_temp;
		batt_stat->max_temp_time = (uint32_t)cs_data->event_system_time;
	} else if (current_temp < batt_stat->min_temp) {
		batt_stat->min_temp = current_temp;
		batt_stat->min_temp_time = (uint32_t)cs_data->event_system_time;
	}
	return;
}

void set_last_shutdown_soc(
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	if (sysfs_param[SFID_SYSTEM_STATUS].intval == SYSTEM_STATUS_SHUTDOWN)
		batt_stat->last_shutdown_soc = sysfs_param[SFID_CAPACITY].intval;

	return;
}

void set_usb_connector_heat_count(
	struct cs_data_t *cs_data,
	const struct sysfs_param_t *sysfs_param,
	struct batt_stat_t *batt_stat)
{
	static int prev_system_temp_level = 0;

	if (prev_system_temp_level != sysfs_param[SFID_SYSTEM_TEMP_LEVEL_MAX].intval &&
		sysfs_param[SFID_SYSTEM_TEMP_LEVEL].intval == sysfs_param[SFID_SYSTEM_TEMP_LEVEL_MAX].intval) {
		cs_data->usb_connector_heat_time = cs_data->event_system_time;
		if (cs_data->usb_connector_heat_count < 255)
			cs_data->usb_connector_heat_count++;
	}

	prev_system_temp_level = sysfs_param[SFID_SYSTEM_TEMP_LEVEL].intval;

	return;
}

void update_batt_stat(
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	set_soh_record(cs_data, batt_stat, sysfs_param);
	set_initial_time_if_required(cs_data, batt_stat);
	set_battery_model_name_if_required(cs_data, batt_stat, sysfs_param);
	set_learning_state(cs_data, batt_stat, sysfs_param);
	set_charge_total_time(cs_data, batt_stat, sysfs_param);
	set_vt_cet_table(cs_data, batt_stat, sysfs_param);
	set_ct_charge_table(cs_data, batt_stat, sysfs_param);
	set_smart_charge_state(cs_data, batt_stat, sysfs_param);
	set_jeita_warm_time(cs_data, batt_stat, sysfs_param);
	set_dev_info(cs_data, batt_stat, sysfs_param);
	set_soc0_shutdown_cnt(batt_stat, sysfs_param);
	set_thermal_range_stay_time(cs_data, batt_stat, sysfs_param);
	set_rapid_charge_time(cs_data, batt_stat, sysfs_param);
	set_rapid_charge_count(cs_data, batt_stat, sysfs_param);
	set_max_discharge_current(cs_data, batt_stat, sysfs_param);
	set_max_cell_voltage(cs_data, batt_stat, sysfs_param);
	set_min_max_temp(cs_data, batt_stat, sysfs_param);
	set_total_discharge_time(cs_data, batt_stat, sysfs_param);
	set_last_shutdown_soc(batt_stat, sysfs_param);
	set_usb_connector_heat_count(cs_data, sysfs_param, batt_stat);
}

static void set_sc1_time(struct cs_data_t *cs_data, struct batt_stat_t *batt_stat)
{
	int sc1_time_index;

	if (cs_data->cycle_aging_level <= 0)
		return;

	sc1_time_index = cs_data->cycle_aging_level - 1;

	if (batt_stat->sc1_first_start_time[sc1_time_index])
		return;

	batt_stat->sc1_first_start_time[sc1_time_index] = cs_data->online_time;
}

static void set_sc5_time(struct cs_data_t *cs_data, struct batt_stat_t *batt_stat)
{
	int sc5_time_index;

	if (cs_data->full_time_aging_level <= 0)
		return;

	sc5_time_index = cs_data->full_time_aging_level - 1;

	if (batt_stat->sc5_first_start_time[sc5_time_index])
		return;

	batt_stat->sc5_first_start_time[sc5_time_index] = batt_stat->online_time;
}

static void set_arrhenius_params(struct cs_data_t *cs_data, struct batt_stat_t *batt_stat)
{
	int i;

	batt_stat->online_time = cs_data->online_time;

	batt_stat->total_arrhenius = (uint32_t)cs_data->total_arrhenius_f;

	for (i = 0; i < ARRHENIUS_RECORDS_NUM; i++)
		batt_stat->arrhenius_per_10days[i] = (uint32_t)cs_data->arrhenius_per_10days_f[i];

	if ((cs_data->arrhenius_record_index < 0) || (cs_data->arrhenius_aging_level < 0))
		return;

	if (batt_stat->arrhenius_aging_level_record[cs_data->arrhenius_record_index] != 0xff)
		return;

	batt_stat->arrhenius_aging_level_record[cs_data->arrhenius_record_index] = (uint8_t)cs_data->arrhenius_aging_level;
}

static void set_full_stay_cap_degradation_params(struct cs_data_t *cs_data, struct batt_stat_t *batt_stat)
{
	int i;
	for (i = 0; i < STAY_CAP_DEGRADE_RECORDS_NUM; i++) {
		batt_stat->full_stay_cap_degradation_per_10days[i] =
			(uint32_t)(cs_data->full_stay_cap_degr_per_10days_f[i] * STAY_CAP_DEGRADATION_MAG);
	}
	if ((cs_data->full_stay_cap_degr_aging_level_record_index < 0) || (cs_data->full_stay_cap_degr_aging_level < 0))
		return;

	if (batt_stat->full_stay_cap_degradation_aging_level_record[cs_data->full_stay_cap_degr_aging_level_record_index] != 0xff)
		return;

	batt_stat->full_stay_cap_degradation_aging_level_record[cs_data->full_stay_cap_degr_aging_level_record_index] =
										(uint8_t)cs_data->full_stay_cap_degr_aging_level;
}

static void set_soft_charge_mode(struct cs_data_t *cs_data, struct batt_stat_t *batt_stat)
{
	batt_stat->soft_charge_mode = cs_data->batt_aging_level;
}

void update_batt_stat_after_control(
	struct cs_data_t *cs_data, struct batt_stat_t *batt_stat)
{
	set_sc1_time(cs_data, batt_stat);
	set_sc5_time(cs_data, batt_stat);
	set_arrhenius_params(cs_data, batt_stat);
	set_full_stay_cap_degradation_params(cs_data, batt_stat);
	set_soft_charge_mode(cs_data, batt_stat);
}
