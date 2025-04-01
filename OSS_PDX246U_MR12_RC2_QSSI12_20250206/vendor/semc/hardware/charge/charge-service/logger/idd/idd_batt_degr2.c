/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/

#include <stdlib.h>
#include <string.h>
#include <idd_api.h>
#include "charge-service.h"
#include "idd_batt_degr2.h"
#include "charging/charging.pb-c.h"
#include "log.h"

#define VT_CET_TABLE_SIZE	(MAX_VBATT_STEP * MAX_TEMP_STEP)
#define CT_CHARGE_TABLE_SIZE	(MAX_SOC_STEP * MAX_TEMP_STEP)

#ifdef LOG_ALL
static void idd_log_batt_degr2_data(Charging__BatteryDegradation2 *batt_degr2_param)
{
	int i;

	LOGD("******************************************************************\n");
	LOGD("batt_degr2_param.version =                          %s\n", batt_degr2_param->version);
	for (i = 0; i < (int)batt_degr2_param->n_fcc_mah; i++) {
		LOGD("batt_degr2_param.fcc_mah[%d] =                     %u\n", i, batt_degr2_param->fcc_mah[i]);
	}
	LOGD("batt_degr2_param.learning_total_count =             %u\n", batt_degr2_param->learning_total_count);
	LOGD("batt_degr2_param.battery_model_name =               %s\n", batt_degr2_param->battery_model_name);
	LOGD("batt_degr2_param.initialized_time =                 %lu\n", batt_degr2_param->initialized_time);
	LOGD("batt_degr2_param.last_learning_time =               %lu\n", batt_degr2_param->last_learning_time);
	LOGD("batt_degr2_param.first_learning_time =              %lu\n", batt_degr2_param->first_learning_time);
	for (i = 0; i < (int)batt_degr2_param->n_first_soh_time; i++) {
		LOGD("batt_degr2_param.first_soh_time[%d] =         %lu\n", i, batt_degr2_param->first_soh_time[i]);
	}
	LOGD("batt_degr2_param.soft_charge_mode =                 %u\n", batt_degr2_param->soft_charge_mode);
	LOGD("batt_degr2_param.total_cycle_count =                %u\n", batt_degr2_param->total_cycle_count);

	for (i = 0; i < (int)batt_degr2_param->n_soft_charge1_onlinetime; i++) {
		LOGD("batt_degr2_param.soft_charge1_onlinetime[%d] =      %lu\n", i, batt_degr2_param->soft_charge1_onlinetime[i]);
	}

	for (i = 0; i < (int)batt_degr2_param->n_soft_charge5_onlinetime; i++) {
		LOGD("batt_degr2_param.soft_charge5_onlinetime[%d] =      %lu\n", i, batt_degr2_param->soft_charge5_onlinetime[i]);
	}

	for (i = 0; i < VT_CET_TABLE_SIZE; i++) {
		LOGD("batt_degr2_param.vt_cet_table[%d] =                 %u\n", i, batt_degr2_param->vt_cet_table[i]);
	}
	for (i = 0; i < CT_CHARGE_TABLE_SIZE; i++) {
		LOGD("batt_degr2_param.ct_charge_table[%d] =              %u\n", i, batt_degr2_param->ct_charge_table[i]);
	}
	LOGD("batt_degr2_param.full_count =                       %u\n", batt_degr2_param->full_count);
	LOGD("batt_degr2_param.recharge_count =                   %u\n", batt_degr2_param->recharge_count);
	LOGD("batt_degr2_param.off_charge_total_time =            %lu\n", batt_degr2_param->off_charge_total_time);
	LOGD("batt_degr2_param.on_charge_total_time =             %lu\n", batt_degr2_param->on_charge_total_time);
	LOGD("batt_degr2_param.soc_full_total_time =              %lu\n", batt_degr2_param->soc_full_total_time);
	LOGD("batt_degr2_param.smart_charge_mode_total_time:      %lu\n", batt_degr2_param->smart_charge_mode_total_time);
	LOGD("batt_degr2_param.jeita_warm_total_time =            %u\n", batt_degr2_param->jeita_warm_total_time);
	LOGD("batt_degr2_param.last_learning_boot_time =          %lu\n", batt_degr2_param->last_learning_boot_time);
	LOGD("batt_degr2_param.learning_try_cnt =                 %u\n", batt_degr2_param->learning_try_cnt);
	LOGD("batt_degr2_param.soc0_shutdown_cnt =                %u\n", batt_degr2_param->soc0_shutdown_cnt);
	LOGD("batt_degr2_param.safety_timer_cnt =                 %u\n", batt_degr2_param->safety_timer_cnt);
	for (i = 0; i < THERMAL_RANGE_NUM; i++) {
		LOGD("batt_degr2_param.thermal_range_stay_time[%d] = %u\n", i, batt_degr2_param->thermal_range_stay_time[i]);
	}
	LOGD("batt_degr2_param.over_08c_total_time =              %u\n", batt_degr2_param->over_08c_total_time);
	LOGD("batt_degr2_param.over_08c_charge_count =            %u\n", batt_degr2_param->over_08c_charge_count);
	LOGD("batt_degr2_param.over_06c_total_time =              %u\n", batt_degr2_param->over_06c_total_time);
	LOGD("batt_degr2_param.over_06c_charge_count =            %u\n", batt_degr2_param->over_06c_charge_count);
	LOGD("batt_degr2_param.max_discharge_current[0] =        %u\n",  batt_degr2_param->max_discharge_current);
	LOGD("batt_degr2_param.max_discharge_current[1] =       %u\n",  batt_degr2_param->max_discharge_current_1);
	LOGD("batt_degr2_param.max_discharge_current[2] =       %u\n",  batt_degr2_param->max_discharge_current_2);
	LOGD("batt_degr2_param.max_discharge_current[3] =       %u\n",  batt_degr2_param->max_discharge_current_3);

	for (i = 0; i < batt_degr2_param->n_max_discharge_time; i++) {
		LOGD("batt_degr2_param.max_discharge_time[%d] =   %u\n", i, batt_degr2_param->max_discharge_time[i]);
	}
	LOGD("batt_degr2_param.max_temp =                         %d\n", batt_degr2_param->max_temp);
	LOGD("batt_degr2_param.max_temp_time =                    %u\n", batt_degr2_param->max_temp_time);
	LOGD("batt_degr2_param.min_temp =                         %d\n", batt_degr2_param->min_temp);
	LOGD("batt_degr2_param.min_temp_time =                    %u\n", batt_degr2_param->min_temp_time);
	for (i = 0; i < batt_degr2_param->n_total_discharge_time; i++) {
		LOGD("batt_degr2_param.total_discharge_time[%d] =         %u\n", i, batt_degr2_param->total_discharge_time[i]);
	}
	for (i = 0; i < (int)batt_degr2_param->n_fcc_mah_raw; i++) {
		LOGD("batt_degr2_param.fcc_mah_raw[%d] =                  %u\n", i, batt_degr2_param->fcc_mah_raw[i]);
	}
	LOGD("batt_degr2_param.max_cell_voltage =                 %u\n", batt_degr2_param->max_cell_voltage);
	LOGD("batt_degr2_param.max_cell_voltage_time =            %u\n", batt_degr2_param->max_cell_voltage_time);
	for (i = 0; i < (int)batt_degr2_param->n_dev_attach_count; i++) {
		LOGD("batt_degr2_param.dev_attach_count[%d] =             %u\n", i, batt_degr2_param->dev_attach_count[i]);
		LOGD("batt_degr2_param.dev_attach_total_time[%d] =        %u\n", i, batt_degr2_param->dev_attach_total_time[i]);
		LOGD("batt_degr2_param.dev_charge_count[%d] =             %u\n", i, batt_degr2_param->dev_charge_count[i]);
	}
	LOGD("batt_degr2_param.online_time =                      %u\n", batt_degr2_param->online_time);
	LOGD("batt_degr2_param.total_arrhenius =                  %u\n", batt_degr2_param->total_arrhenius);
	for (i = 0; i < (int)batt_degr2_param->n_arrhenius_per_10days; i++) {
		LOGD("batt_degr2_param.arrhenius_per_10days[%d] =         %u\n", i, batt_degr2_param->arrhenius_per_10days[i]);
	}
	for (i = 0; i < (int)batt_degr2_param->n_arrhenius_lv; i++) {
		LOGD("batt_degr2_param.arrhenius_lv[%d] = %u\n", i, batt_degr2_param->arrhenius_lv[i]);
	}
	LOGD("******************************************************************\n");
}

#else
static void idd_log_batt_degr2_data(Charging__BatteryDegradation2 *batt_degr2_param)
{
	UNUSED(batt_degr2_param);
}

#endif
#define BATT_STAT_SENDING_INTERVAL	(10 * 24 * 60 * 60)
#define NO_BATT_PRODUCT "_cdb"
#define UNINITIALIZED_INTERVAL_COUNT	-1
bool can_send_idd_batt_degr2(struct cs_data_t *cs_data, struct batt_stat_t *batt_stat)
{
	int interval_count = UNINITIALIZED_INTERVAL_COUNT;
	static int prev_interval_count = UNINITIALIZED_INTERVAL_COUNT;
	bool sending_timing;

	if (strstr(cs_data->product_name, NO_BATT_PRODUCT) != NULL)
		return false;

	/* when time adjustment is not done, idd is still not ready */
	if (!is_adjusted_time(cs_data->event_system_time))
		return false;

	interval_count = batt_stat->online_time / BATT_STAT_SENDING_INTERVAL;
	if (prev_interval_count == UNINITIALIZED_INTERVAL_COUNT)
		sending_timing = false;
	else
		sending_timing = interval_count > prev_interval_count;

	prev_interval_count = interval_count;
	return sending_timing;
}

static void set_idd_batt_degr2_params(
	Charging__BatteryDegradation2 *batt_degr2_param,
	const struct batt_stat_t *batt_stat,
	struct cs_data_t *cs_data)
{
	static char version[16];
	static uint32_t fcc_mah[MAX_FCC_NUM];
	static uint64_t first_soh_time[MAX_SOH_TIME_NUM];
	static uint64_t soft_charge1_onlinetime[MAX_SC1_TIME_NUM];
	static uint64_t soft_charge5_onlinetime[MAX_SC5_TIME_NUM];
	static uint32_t vt_cet_table[VT_CET_TABLE_SIZE];
	static uint32_t ct_charge_table[CT_CHARGE_TABLE_SIZE];
	static uint32_t max_discharge_time[MAX_DISCHARGE_CURRENT_NUM];
	static uint32_t total_discharge_time[MAX_DISCHARGE_CASE];
	static uint32_t fcc_mah_raw[MAX_FCC_NUM];
	static uint32_t dev_attach_count[MAX_AGGR_CHARGER_TYPE];
	static uint32_t dev_attach_total_time[MAX_AGGR_CHARGER_TYPE];
	static uint32_t dev_charge_count[MAX_AGGR_CHARGER_TYPE];
	static uint32_t thermal_range_stay_time[THERMAL_RANGE_NUM];
	static uint32_t arrhenius_per_10days[ARRHENIUS_RECORDS_NUM];
	static uint32_t arrhenius_aging_level_record[ARRHENIUS_RECORDS_NUM];
	static uint32_t full_stay_cap_degradation_per_10days[STAY_CAP_DEGRADE_RECORDS_NUM];
	static uint32_t full_stay_cap_degradation_aging_level_record[STAY_CAP_DEGRADE_RECORDS_NUM];
	static uint32_t soh_record[SOH_RECORDS_NUM];
	int i, j;
	uint32_t heat_count = 0;

	memset(fcc_mah, 0, sizeof(fcc_mah));
	memset(first_soh_time, 0, sizeof(first_soh_time));
	memset(soft_charge1_onlinetime, 0, sizeof(soft_charge1_onlinetime));
	memset(vt_cet_table, 0, sizeof(vt_cet_table));
	memset(ct_charge_table, 0, sizeof(ct_charge_table));
	memset(max_discharge_time, 0, sizeof(max_discharge_time));
	memset(total_discharge_time, 0, sizeof(total_discharge_time));
	memset(fcc_mah_raw, 0, sizeof(fcc_mah_raw));
	memset(dev_attach_count, 0, sizeof(dev_attach_count));
	memset(dev_attach_total_time, 0, sizeof(dev_attach_total_time));
	memset(dev_charge_count, 0, sizeof(dev_charge_count));
	memset(thermal_range_stay_time, 0, sizeof(thermal_range_stay_time));
	memset(arrhenius_per_10days, 0, sizeof(arrhenius_per_10days));
	memset(arrhenius_aging_level_record, 0, sizeof(arrhenius_aging_level_record));
	memset(full_stay_cap_degradation_per_10days, 0, sizeof(full_stay_cap_degradation_per_10days));
	memset(full_stay_cap_degradation_aging_level_record, 0, sizeof(full_stay_cap_degradation_aging_level_record));
	memset(soh_record, 0, sizeof(soh_record));



	batt_degr2_param->has_initialize = true;
	batt_degr2_param->initialize = batt_stat->initialize;

	/* Combine version number as string type */
	snprintf(version, sizeof(version), "%d.%d.%d",
		batt_stat->version[0], batt_stat->version[1], batt_stat->version[2]);
	batt_degr2_param->version = version;

	for (i = 0; i < MAX_FCC_NUM; i++)
		fcc_mah[i] = batt_stat->fcc_mah[i];
	batt_degr2_param->n_fcc_mah = MAX_FCC_NUM;
	batt_degr2_param->fcc_mah = fcc_mah;

	batt_degr2_param->has_learning_total_count = false;
	batt_degr2_param->learning_total_count = batt_stat->learning_total_cnt;

	batt_degr2_param->battery_model_name = (char *)batt_stat->battery_model_name;

	batt_degr2_param->has_initialized_time = true;
	batt_degr2_param->initialized_time = batt_stat->initialized_time;

	batt_degr2_param->has_last_learning_time = true;
	batt_degr2_param->last_learning_time = batt_stat->last_learning_time;

	batt_degr2_param->has_first_learning_time = true;
	batt_degr2_param->first_learning_time = batt_stat->first_learning_time;

	for (i = 0; i < MAX_SOH_TIME_NUM; i++)
		first_soh_time[i] = batt_stat->first_soh_time[i];
	batt_degr2_param->n_first_soh_time = MAX_SOH_TIME_NUM;
	batt_degr2_param->first_soh_time = first_soh_time;

	batt_degr2_param->has_soft_charge_mode = true;
	batt_degr2_param->soft_charge_mode = batt_stat->soft_charge_mode;

	batt_degr2_param->has_total_cycle_count = true;
	batt_degr2_param->total_cycle_count = batt_stat->total_cycle_count;
	for (i = 0; i < MAX_SC1_TIME_NUM; i++)
		soft_charge1_onlinetime[i] = batt_stat->sc1_first_start_time[i];
	batt_degr2_param->n_soft_charge1_onlinetime = MAX_SC1_TIME_NUM;
	batt_degr2_param->soft_charge1_onlinetime = soft_charge1_onlinetime;

	for (i = 0; i < MAX_SC5_TIME_NUM; i++)
		soft_charge5_onlinetime[i] = batt_stat->sc5_first_start_time[i];
	batt_degr2_param->n_soft_charge5_onlinetime = MAX_SC5_TIME_NUM;
	batt_degr2_param->soft_charge5_onlinetime = soft_charge5_onlinetime;
	for (j = 0; j < MAX_VBATT_STEP; j++) {
		for (i = 0; i < MAX_TEMP_STEP; i++)
			vt_cet_table[(j * MAX_TEMP_STEP) + i] = batt_stat->vt_cet_table[j][i];
	}
	batt_degr2_param->n_vt_cet_table = VT_CET_TABLE_SIZE;
	batt_degr2_param->vt_cet_table = vt_cet_table;

	for (j = 0; j < MAX_SOC_STEP; j++) {
		for (i = 0; i < MAX_TEMP_STEP; i++)
			ct_charge_table[(j * MAX_TEMP_STEP) + i] = batt_stat->ct_charge_table[j][i];
	}
	batt_degr2_param->n_ct_charge_table = CT_CHARGE_TABLE_SIZE;
	batt_degr2_param->ct_charge_table = ct_charge_table;

	batt_degr2_param->has_full_count = false;
	batt_degr2_param->full_count = batt_stat->full_cnt;

	batt_degr2_param->has_recharge_count = false;
	batt_degr2_param->recharge_count = batt_stat->recharge_cnt;

	batt_degr2_param->has_off_charge_total_time = true;
	batt_degr2_param->off_charge_total_time = batt_stat->off_charge_total_time;

	batt_degr2_param->has_on_charge_total_time = true;
	batt_degr2_param->on_charge_total_time = batt_stat->on_charge_total_time;

	batt_degr2_param->has_soc_full_total_time = true;
	batt_degr2_param->soc_full_total_time = batt_stat->soc_full_time;

	batt_degr2_param->has_smart_charge_mode_total_time = true;
	batt_degr2_param->smart_charge_mode_total_time = batt_stat->smart_charge_mode_time;

	batt_degr2_param->has_jeita_warm_total_time = true;
	batt_degr2_param->jeita_warm_total_time = batt_stat->jeita_warm_time;

	for (i = 0; i < MAX_FCC_NUM; i++)
		fcc_mah_raw[i] = batt_stat->fcc_mah_raw[i];
	batt_degr2_param->n_fcc_mah_raw = 0;
	batt_degr2_param->fcc_mah_raw = fcc_mah_raw;

	for (i = 0; i < MAX_AGGR_CHARGER_TYPE; i++)
		dev_attach_count[i] = batt_stat->dev[i].attach_count;
	batt_degr2_param->n_dev_attach_count = MAX_AGGR_CHARGER_TYPE;
	batt_degr2_param->dev_attach_count = dev_attach_count;

	for (i = 0; i < MAX_AGGR_CHARGER_TYPE; i++)
		dev_attach_total_time[i] = batt_stat->dev[i].attach_time;
	batt_degr2_param->n_dev_attach_total_time = MAX_AGGR_CHARGER_TYPE;
	batt_degr2_param->dev_attach_total_time = dev_attach_total_time;

	for (i = 0; i < MAX_AGGR_CHARGER_TYPE; i++)
		dev_charge_count[i] = batt_stat->dev[i].charge_count;
	batt_degr2_param->n_dev_charge_count = MAX_AGGR_CHARGER_TYPE;
	batt_degr2_param->dev_charge_count = dev_charge_count;

	batt_degr2_param->has_last_learning_boot_time = true;
	batt_degr2_param->last_learning_boot_time = batt_stat->last_learning_boot_time;

	batt_degr2_param->has_learning_try_cnt = false;
	batt_degr2_param->learning_try_cnt = batt_stat->learning_try_cnt;

	batt_degr2_param->has_soc0_shutdown_cnt = true;
	batt_degr2_param->soc0_shutdown_cnt = batt_stat->soc0_shutdown_cnt;

	batt_degr2_param->has_safety_timer_cnt = false;
	batt_degr2_param->safety_timer_cnt = batt_stat->safety_timer_cnt;

	for (i = 0; i < THERMAL_RANGE_NUM; i++)
		thermal_range_stay_time[i] = batt_stat->thermal_range_stay_time[i];
	batt_degr2_param->n_thermal_range_stay_time = THERMAL_RANGE_NUM;
	batt_degr2_param->thermal_range_stay_time = thermal_range_stay_time;

	batt_degr2_param->has_over_08c_total_time = true;
	batt_degr2_param->over_08c_total_time = batt_stat->over_08c_total_time;

	batt_degr2_param->has_over_08c_charge_count = true;
	batt_degr2_param->over_08c_charge_count = batt_stat->over_08c_charge_count;

	batt_degr2_param->has_over_06c_total_time = true;
	batt_degr2_param->over_06c_total_time = batt_stat->over_06c_total_time;

	batt_degr2_param->has_over_06c_charge_count = true;
	batt_degr2_param->over_06c_charge_count = batt_stat->over_06c_charge_count;

	batt_degr2_param->has_max_discharge_current = true;
	batt_degr2_param->max_discharge_current = batt_stat->max_discharge_current[0] * -1;

	batt_degr2_param->has_online_time = true;
	batt_degr2_param->online_time = batt_stat->online_time;

	batt_degr2_param->has_total_arrhenius = true;
	batt_degr2_param->total_arrhenius = batt_stat->total_arrhenius;

	for (i = 0; i < ARRHENIUS_RECORDS_NUM; i++)
		arrhenius_per_10days[i] = batt_stat->arrhenius_per_10days[i];
	batt_degr2_param->n_arrhenius_per_10days = ARRHENIUS_RECORDS_NUM;
	batt_degr2_param->arrhenius_per_10days = arrhenius_per_10days;

/* Sent data in MiscTA2491 version 5.0.0 or later */
	batt_degr2_param->has_max_dischg_cur_3500mv_10c = true;
	batt_degr2_param->max_dischg_cur_3500mv_10c = batt_stat->max_discharge_current[1] * -1;
	batt_degr2_param->has_max_dischg_cur_3500mv_5c = true;
	batt_degr2_param->max_dischg_cur_3500mv_5c = batt_stat->max_discharge_current[2] * -1;
	batt_degr2_param->has_max_dischg_cur_3500mv_0c = true;
	batt_degr2_param->max_dischg_cur_3500mv_0c = batt_stat->max_discharge_current[3] * -1;
	for (i = 0; i < MAX_DISCHARGE_CURRENT_NUM; i++)
		max_discharge_time[i] = batt_stat->max_discharge_current_time[i];
	batt_degr2_param->n_max_discharge_time = MAX_DISCHARGE_CURRENT_NUM;
	batt_degr2_param->max_discharge_time = max_discharge_time;
	batt_degr2_param->has_max_temp = true;
	batt_degr2_param->max_temp = batt_stat->max_temp;
	batt_degr2_param->has_max_temp_time = true;
	batt_degr2_param->max_temp_time = batt_stat->max_temp_time;
	batt_degr2_param->has_min_temp = true;
	batt_degr2_param->min_temp = batt_stat->min_temp;
	batt_degr2_param->has_min_temp_time = true;
	batt_degr2_param->min_temp_time = batt_stat->min_temp_time;
	batt_degr2_param->has_max_cell_voltage = true;
	batt_degr2_param->max_cell_voltage = batt_stat->max_cell_voltage;
	batt_degr2_param->has_max_cell_voltage_time = true;
	batt_degr2_param->max_cell_voltage_time = batt_stat->max_cell_voltage_time;

	for (i = 0; i < MAX_DISCHARGE_CASE; i++)
		total_discharge_time[i] = batt_stat->total_discharge_time[i];
	batt_degr2_param->n_total_discharge_time = MAX_DISCHARGE_CASE;
	batt_degr2_param->total_discharge_time = total_discharge_time;

	for (i = 0; i < ARRHENIUS_RECORDS_NUM; i++) {
		if (batt_stat->arrhenius_aging_level_record[i] == 0xff)
			arrhenius_aging_level_record[i] = -1;
		else
			arrhenius_aging_level_record[i] = batt_stat->arrhenius_aging_level_record[i];
	}
	batt_degr2_param->n_arrhenius_lv = ARRHENIUS_RECORDS_NUM;
	batt_degr2_param->arrhenius_lv = arrhenius_aging_level_record;

	for (i = 0; i < STAY_CAP_DEGRADE_RECORDS_NUM; i++)
		full_stay_cap_degradation_per_10days[i] = batt_stat->full_stay_cap_degradation_per_10days[i];

	batt_degr2_param->n_full_stay_capacity_degradation_per_10days = STAY_CAP_DEGRADE_RECORDS_NUM;
	batt_degr2_param->full_stay_capacity_degradation_per_10days = full_stay_cap_degradation_per_10days;

	for (i = 0; i < STAY_CAP_DEGRADE_RECORDS_NUM; i++) {
		if (batt_stat->full_stay_cap_degradation_aging_level_record[i] == 0xff)
			full_stay_cap_degradation_aging_level_record[i] = -1;
		else
			full_stay_cap_degradation_aging_level_record[i] = batt_stat->full_stay_cap_degradation_aging_level_record[i];
	}

	batt_degr2_param->n_full_stay_capacity_degradation_aging_lv = STAY_CAP_DEGRADE_RECORDS_NUM;
	batt_degr2_param->full_stay_capacity_degradation_aging_lv = full_stay_cap_degradation_aging_level_record;

	for (i = 0; i < SOH_RECORDS_NUM; i++) {
		if (batt_stat->soh_record[i] == 0xff)
			soh_record[i] = -1;
		else
			soh_record[i] = batt_stat->soh_record[i];
	}

	batt_degr2_param->n_soh_per_10days = SOH_RECORDS_NUM;
	batt_degr2_param->soh_per_10days = soh_record;

	batt_degr2_param->has_usb_connector_heat_count = true;
	batt_degr2_param->usb_connector_heat_count = cs_data->usb_connector_heat_count;

	batt_degr2_param->has_usb_connector_heat_time = true;
	batt_degr2_param->usb_connector_heat_time = cs_data->usb_connector_heat_time;

/* Data not sent with MiscTA2491 version 5.0.0 */
	batt_degr2_param->n_soft_charge3_time = 0;
	batt_degr2_param->has_sc4_first_start_time = false;
	batt_degr2_param->has_jeita_batt_warm_total_time = false;
	batt_degr2_param->has_jeita_aux_warm_total_time = false;
	batt_degr2_param->has_jeita_wlc_warm_total_time = false;

	idd_log_batt_degr2_data(batt_degr2_param);
}

void send_idd_batt_degr2(struct cs_data_t *cs_data, const struct batt_stat_t *batt_stat)
{
	IDD_t *idd_p;
	size_t size;
	uint8_t *serialized_p;
	int ret;
	Charging__BatteryDegradation2 batt_degr2_param
		= CHARGING__BATTERY_DEGRADATION2__INIT;

	idd_p = idd_create();
	if (idd_p == NULL) {
		LOG("IDD_T for BatteryDegradation is NULL\n");
		return ;
	}

	ret = idd_is_active(idd_p);
	if (ret <= 0) {
		LOG("idd_is_active: %d\n", ret);
		idd_destroy(&idd_p);
		return;
	}

	set_idd_batt_degr2_params(&batt_degr2_param, batt_stat, cs_data);
	size = charging__battery_degradation2__get_packed_size(&batt_degr2_param);
	if (size > 0) {
		LOGD("Upload battery log to IDD. size: %d\n", size);
		serialized_p = malloc(size);
		if (serialized_p) {
			size = charging__battery_degradation2__pack(&batt_degr2_param, serialized_p);
			idd_add_event(idd_p, "charging", "BatteryDegradation2",
				(char *)serialized_p, size);
			LOG("Sending idd event for BatteryDegradation2\n");
			free(serialized_p);
		} else {
			LOG("malloc failed\n");
		}
	} else {
		LOG("IDD log Could not serialize message data\n");
	}
	idd_destroy(&idd_p);

	cs_data->batt_degr2_idd_sent_time = cs_data->event_boot_time;

}
