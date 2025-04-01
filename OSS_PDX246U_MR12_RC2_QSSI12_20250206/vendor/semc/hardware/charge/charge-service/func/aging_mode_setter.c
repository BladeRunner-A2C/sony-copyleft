/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/

#include <math.h>
#include "charge-service.h"
#include "aging_mode_setter.h"
#include "log.h"

static int sc5_cycle_check(
	struct cs_data_t *cs_data,
	const struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	int total_ct_charge;
	int row, column;
	int i;
	static const int cycle_threshold_table[] = {
		100,	/* ~100cycle       -> Level 0 */
		200,	/* ~200cycle       -> Level 1 */
		400,	/* ~400cycle       -> Level 2 */
		1100,	/* ~1100cycle      -> Level 3 */
		1300,	/* ~1300cycle      -> Level 4 */
			/* above 1300cycle -> Level 5 */
	};
	const int num_cycle_thresholds = sizeof(cycle_threshold_table) / sizeof(int);

	UNUSED(sysfs_param);

	total_ct_charge = 0;
	for (row = 0; row < MAX_SOC_STEP; row++) {
		for (column = 0; column < MAX_TEMP_STEP; column++) {
			total_ct_charge +=
				batt_stat->ct_charge_table[row][column];
		}
	}

	for (i = 0; i < num_cycle_thresholds; i++) {
		if (total_ct_charge <= cycle_threshold_table[i] * 10000)
			break;
	}
	cs_data->cycle_aging_level = i;

	return cs_data->cycle_aging_level;
}

struct arrhenius_coeff_t {
	const long double num_1;
	const long double num_2;

	const long double vbatt_thr;

	struct {
		const long double den_e1_1;
		const long double den_e1_2;
		const long double den_e2_1;
		const long double den_e2_2;
	} hv;

	struct {
		const long double den_e1_1;
		const long double den_e1_2;
		const long double den_e2_1;
		const long double den_e2_2;
	} lv;
};

struct full_stay_cap_degr_coeff_t {
	const long double intercept;
	const long double temp;
	const long double vbatt;
};

#define ARRHENIUS_ABS_TEMP 273.15L
#define VBATT_MAX          5.0L
#define VBATT_MIN          1.0L
#define TEMP_MAX           100.0L
#define TEMP_MIN           -100.0L

static long double get_arrhenius_increased_value(
	const int temp,
	const int vbatt,
	const struct arrhenius_coeff_t *arrhenius_coeff)
{
	long double arr_den, arrhenius_time, arr_num;
	long double voltage_now = (long double)vbatt / 1000000.0L;
	long double temp_now = (long double)temp / 10.0L;

	if (voltage_now > VBATT_MAX || voltage_now < VBATT_MIN ||
			temp_now > TEMP_MAX || temp_now < TEMP_MIN)
		return 0.0L;

	arr_num = arrhenius_coeff->num_1 * arrhenius_coeff->num_2;
	if (voltage_now > arrhenius_coeff->vbatt_thr)
		arr_den = expl(arrhenius_coeff->hv.den_e1_1 * voltage_now +
			arrhenius_coeff->hv.den_e1_2 + arrhenius_coeff->hv.den_e2_1 *
			(long double)(1.0L / (ARRHENIUS_ABS_TEMP + temp_now)) + arrhenius_coeff->hv.den_e2_2);
	else
		arr_den = expl(arrhenius_coeff->lv.den_e1_1 * voltage_now +
			arrhenius_coeff->lv.den_e1_2 + arrhenius_coeff->lv.den_e2_1 *
			(long double)(1.0L / (ARRHENIUS_ABS_TEMP + temp_now)) + arrhenius_coeff->lv.den_e2_2);

	arrhenius_time = arr_num / arr_den;
	return arrhenius_time;
}

static void update_arrhenius_time(
	struct cs_data_t *cs_data,
	const int temp,
	const int vbatt,
	const struct arrhenius_coeff_t *arrhenius_coeff)
{
	static int prev_temp = 0;
	static int prev_vbatt = 0;
	static time_t prev_time = 0;
	int i;
	int vbatt_diff, temp_diff, time_diff;
	int tranditional_vbatt, tranditional_temp;
	int arrhenius_index;
	long double increased_value;

	time_diff = (int)difftime(cs_data->event_boot_time, prev_time);

	if (prev_time && time_diff > 0) {
		vbatt_diff = vbatt - prev_vbatt;
		temp_diff = temp - prev_temp;
		for (i = 0; i < time_diff; i++) {
			tranditional_temp = INTERPOLATE(prev_temp, temp_diff, time_diff, i);
			tranditional_vbatt = INTERPOLATE(prev_vbatt, vbatt_diff, time_diff, i);
			increased_value = get_arrhenius_increased_value(tranditional_temp, tranditional_vbatt, arrhenius_coeff);

			cs_data->total_arrhenius_f += increased_value;

			arrhenius_index = cs_data->online_time / SECONDS_IN_10DAYS;
			if (arrhenius_index < MAX_ARRHENIUS_RECORDS)
				cs_data->arrhenius_per_10days_f[arrhenius_index] += increased_value;

			cs_data->online_time++;
		}
	}

	prev_temp = temp;
	prev_vbatt = vbatt;
	prev_time = cs_data->event_boot_time;
}

#define MAX_ARRHENIUS_AGING_LEVEL 5
static void determine_arrhenius_aging_level(
	struct cs_data_t *cs_data,
	const struct batt_stat_t *batt_stat,
	const uint32_t arrhenius_thresh_upper,
	const uint32_t arrhenius_thresh_lower)
{
	int i;
	int current_arrhenius_index;
	int current_arrhenius_aging_level;
	uint32_t life_end_arrhenius[ARRHENIUS_RECORDS_NUM];
	uint32_t last_arrhenius_per_10days;
	uint32_t life_end_total_arrhenius;

	current_arrhenius_index = cs_data->online_time / SECONDS_IN_10DAYS;
	if (current_arrhenius_index >= ARRHENIUS_RECORDS_NUM)
		current_arrhenius_index = ARRHENIUS_RECORDS_NUM - 1;

	cs_data->arrhenius_record_index = current_arrhenius_index;

	if (batt_stat->arrhenius_aging_level_record[current_arrhenius_index] != 0xff) {
		cs_data->arrhenius_aging_level = batt_stat->arrhenius_aging_level_record[current_arrhenius_index];
		return;
	}

	if (current_arrhenius_index == 0) {
		cs_data->arrhenius_aging_level = 0;
		return;
	}

	LOG("Phone online time has reached %d days\n", current_arrhenius_index * 10);

	for (i = current_arrhenius_index - 1; i >= 0; i--) {
		if (batt_stat->arrhenius_aging_level_record[i] != 0xff)
			break;
	}
	if (i >= 0)
		current_arrhenius_aging_level = batt_stat->arrhenius_aging_level_record[i];
	else
		current_arrhenius_aging_level = 0;

	for (i = 0; i < current_arrhenius_index; i++)
		life_end_arrhenius[i] = (uint32_t)cs_data->arrhenius_per_10days_f[i];

	last_arrhenius_per_10days = (uint32_t)cs_data->arrhenius_per_10days_f[i - 1];
	for (; i < ARRHENIUS_RECORDS_NUM; i++)
		life_end_arrhenius[i] = last_arrhenius_per_10days;

	life_end_total_arrhenius = 0;
	for (i = 0; i < ARRHENIUS_RECORDS_NUM; i++)
		life_end_total_arrhenius += life_end_arrhenius[i];

	LOG("Expected arrhenius time at end of battery life is %d\n", life_end_total_arrhenius);

	if (life_end_total_arrhenius > arrhenius_thresh_upper) {
		if (current_arrhenius_aging_level < MAX_ARRHENIUS_AGING_LEVEL)
			current_arrhenius_aging_level++;
	} else if (life_end_total_arrhenius < arrhenius_thresh_lower) {
		if (current_arrhenius_aging_level > 0)
			current_arrhenius_aging_level--;
	}
	cs_data->arrhenius_aging_level = current_arrhenius_aging_level;
}

static int sc5_arrhenius_check_nagara(
	struct cs_data_t *cs_data,
	const struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	const struct arrhenius_coeff_t arrhenius_coeff = {
		76.25882937,		/* NUM_1 */
		76.25882937,		/* NUM_2 */

		4.40,			/* VBATT_THR */

		/* over VBATT_THR */
		{
			-2.590717444,	/* DEN_E1_1 */
			15.9322614,	/* DEN_E1_2 */
			11482.18513,	/* DEN_E2_1 */
			-31.7563434,	/* DEN_E2_2 */
		},

		/* equal or under VBATT_THR */
		{
			-7.22366584,	/* DEN_E1_1 */
			36.32220593,	/* DEN_E1_2 */
			11482.18513,	/* DEN_E2_1 */
			-31.7563434	/* DEN_E2_2 */
		}
	};

	update_arrhenius_time(cs_data,
		sysfs_param[SFID_TEMP].intval, sysfs_param[SFID_VOLTAGE_NOW].intval, &arrhenius_coeff);

	determine_arrhenius_aging_level(cs_data, batt_stat,
		1831 * 60 * 60, /* arrhenius_thresh_upper = 1831h */
		1821 * 60 * 60  /* arrhenius_thresh_lower = 1821h */
	);

	return cs_data->arrhenius_aging_level;
}

static void update_full_stay_cap_degradation(struct cs_data_t *cs_data, const int soc_full_time,
					const int temp, const int vbatt, const struct full_stay_cap_degr_coeff_t *coeff)
{
	static int prev_soc_full_time = 0;
	int time_diff;
	int index = 0;
	int i;
	long double rate = 0.0L;
	long double voltage_now = (long double)vbatt / 1000000.0L;
	long double temp_now = (long double)temp / 10.0L;

	time_diff = soc_full_time - prev_soc_full_time;
	index = cs_data->online_time / SECONDS_IN_10DAYS;
	if (prev_soc_full_time && time_diff > 0) {
		if (voltage_now > VBATT_MAX || voltage_now < VBATT_MIN ||
			temp_now > TEMP_MAX || temp_now < TEMP_MIN) {
			return;
		} else {
			rate = expl(
					(coeff->vbatt * voltage_now) // X1 * Voltage
					+ (coeff->temp * temp_now)   // X2 * Temperature
					+ coeff->intercept           // Intercept
				)
				* ((long double)time_diff / 3600.0L) // Residence time (hour)
				* 100.0L;
		}

		cs_data->total_full_stay_cap_degr_f += rate;
		if (index < MAX_STAY_CAP_DEGRADATION_RECORDS)
			cs_data->full_stay_cap_degr_per_10days_f[index] += rate;
	}

	prev_soc_full_time = soc_full_time;
	return;
}

#define SOH_THR             80.0
#define STOP_FULL_CAP_DEGR_SOH_THR 82.0
#define MAX_FULL_CAP_DEGR_AGING_LEVEL 4
#define STOP_FULL_CAP_DEGR_AGING_LEVEL 3
static bool can_levelup_full_stay_cap_degr_aging_level(
	uint8_t *full_stay_cap_degradation_aging_level_record,
	int current_level, int current_index, int soh)
{
	int i;
	int past_index;
	bool can_levelup;

	if (soh < STOP_FULL_CAP_DEGR_SOH_THR || current_level >= STOP_FULL_CAP_DEGR_AGING_LEVEL)
		return false;

	can_levelup = true;

	for (i = 0; i < 3; i++) {
		past_index = current_index - (i + 1);
		if (past_index < 0)
			break;

		if (full_stay_cap_degradation_aging_level_record[past_index] == INVALID_AGING_LEVEL)
			continue;

		if (full_stay_cap_degradation_aging_level_record[past_index] < current_level) {
			/*
			 * If lower level is found within the past 30 days,
			 * do not increase the level yet.
			 */
			can_levelup = false;
			break;
		}
		if (full_stay_cap_degradation_aging_level_record[past_index] > current_level) {
			/*
			 * If higher level is found within the past 30 days,
			 * can increase the level again.
			 */
			break;
		}
		/*
		 * If the recorded level is not changed from current level,
		 * continue checking.
		 */
	}

	return can_levelup;
}

static void determine_full_stay_cap_degradation(struct cs_data_t *cs_data,
		const struct batt_stat_t *batt_stat, const struct sysfs_param_t *sysfs_param)
{
	int i = 0;
	int current_full_stay_cap_degr_index = 0;
	int current_full_stay_cap_degr_aging_level = 0;
	long double expected_soh = 0.0L;
	long double last_full_stay_cap_degr = 0.0L;
	long double life_end_total_full_stay_cap_degr = 0.0L;
	long double life_end_full_stay_cap_degr[MAX_STAY_CAP_DEGRADATION_RECORDS];

	/* Check current aging_level */
	current_full_stay_cap_degr_index = cs_data->online_time / SECONDS_IN_10DAYS;
	if (current_full_stay_cap_degr_index >= MAX_STAY_CAP_DEGRADATION_RECORDS)
		current_full_stay_cap_degr_index = MAX_STAY_CAP_DEGRADATION_RECORDS - 1;

	cs_data->full_stay_cap_degr_aging_level_record_index = current_full_stay_cap_degr_index;

	if (batt_stat->full_stay_cap_degradation_aging_level_record[current_full_stay_cap_degr_index] != 0xff) {
		cs_data->full_stay_cap_degr_aging_level =
			batt_stat->full_stay_cap_degradation_aging_level_record[current_full_stay_cap_degr_index];
		return;
	}

	if (current_full_stay_cap_degr_index == 0) {
		cs_data->full_stay_cap_degr_aging_level = 0;
		return;
	}

	for (i = current_full_stay_cap_degr_index - 1; i >= 0; i--) {
		if (batt_stat->full_stay_cap_degradation_aging_level_record[i] != 0xff)
			break;
	}
	if (i >= 0)
		current_full_stay_cap_degr_aging_level = batt_stat->full_stay_cap_degradation_aging_level_record[i];
	else
		current_full_stay_cap_degr_aging_level = 0;

	/* calculate expect full_stay_cap_degradation */
	for (i = 0; i < current_full_stay_cap_degr_index; i++) {
		life_end_full_stay_cap_degr[i] = cs_data->full_stay_cap_degr_per_10days_f[i];
	}

	last_full_stay_cap_degr = cs_data->full_stay_cap_degr_per_10days_f[i - 1];
	for (; i < MAX_STAY_CAP_DEGRADATION_RECORDS; i++)
		life_end_full_stay_cap_degr[i] = last_full_stay_cap_degr;

	for (i = 0; i < MAX_STAY_CAP_DEGRADATION_RECORDS; i++)
		life_end_total_full_stay_cap_degr += life_end_full_stay_cap_degr[i];

	/* check aging_level */
	expected_soh = (long double)cs_data->soh - life_end_total_full_stay_cap_degr;
	if (expected_soh > SOH_THR) {
		if (current_full_stay_cap_degr_aging_level > 0) {
			current_full_stay_cap_degr_aging_level--;
		}
	} else {
		if (current_full_stay_cap_degr_aging_level < MAX_FULL_CAP_DEGR_AGING_LEVEL &&
				can_levelup_full_stay_cap_degr_aging_level(
				batt_stat->full_stay_cap_degradation_aging_level_record,
				current_full_stay_cap_degr_aging_level, current_full_stay_cap_degr_index,
				cs_data->soh)) {
			current_full_stay_cap_degr_aging_level++;
		}
	}

	if (current_full_stay_cap_degr_index == MAX_STAY_CAP_DEGRADATION_RECORDS - 1 &&
			current_full_stay_cap_degr_aging_level >= STOP_FULL_CAP_DEGR_AGING_LEVEL)
		current_full_stay_cap_degr_aging_level = MAX_FULL_CAP_DEGR_AGING_LEVEL;

	cs_data->full_stay_cap_degr_aging_level = current_full_stay_cap_degr_aging_level;
}

static int sc5_2_full_stay_cap_degr_check_nagara(
	struct cs_data_t *cs_data,
	const struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	const struct full_stay_cap_degr_coeff_t full_stay_cap_degr_coeff = {
		-12.86115053L,		/* INTERCEPT_COEFF */
		0.05505588L,		/* TEMP_COEFF */
		0.0L			/* VOLTAGE_COEFF */
	};

	/* Calc full_stay_cap_degradation */
	update_full_stay_cap_degradation(cs_data, batt_stat->soc_full_time,
		sysfs_param[SFID_TEMP].intval, sysfs_param[SFID_VOLTAGE_NOW].intval,
		&full_stay_cap_degr_coeff);

	determine_full_stay_cap_degradation(cs_data, batt_stat, sysfs_param);
	return cs_data->full_stay_cap_degr_aging_level;
}

#define NUM_MAX_SC_METHODS 4

struct sc_spec_t {
	int batt_type;
	int (*method[NUM_MAX_SC_METHODS])(
		struct cs_data_t *cs_data,
		const struct batt_stat_t *batt_stat,
		const struct sysfs_param_t *sysfs_param);
};

#define DEBUG_MODE_MASK        0xf0
#define DEBUG_MODE_IDENTIFIER  0xd0
#define DEBUG_MODE_SC_SKIP     0xe0
#define DEBUG_AGING_LEVEL_MASK 0x0f

void control_soft_charge(
	struct cs_data_t *cs_data,
	const struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param)
{
	int batt_aging_level;
	int method_aging_level;
	struct sysfs_param_t sysfs_value;
	int i;
	struct sc_spec_t sc_spec[] = {
		{BATT_TYPE_NAGARA,  {sc5_cycle_check, sc5_arrhenius_check_nagara, sc5_2_full_stay_cap_degr_check_nagara, NULL}},
		{BATT_TYPE_YODO,  {sc5_cycle_check, sc5_arrhenius_check_nagara, sc5_2_full_stay_cap_degr_check_nagara, NULL}},
		{BATT_TYPE_HUAQIN,  {sc5_cycle_check, sc5_arrhenius_check_nagara, sc5_2_full_stay_cap_degr_check_nagara, NULL}}
	};
	const int num_sc_specs = sizeof(sc_spec) / sizeof(struct sc_spec_t);
	struct sc_spec_t *sc_spec_ptr;

	if ((batt_stat->debug_aging_mode & DEBUG_MODE_MASK) == DEBUG_MODE_SC_SKIP) {
		LOGD("The softcharge control skip mode is enabled.\n");
		return;
	}

	for (i = 0; i < num_sc_specs; i++) {
		if (sc_spec[i].batt_type == sysfs_param[SFID_BATT_TYPE].intval)
			break;
	}
	if (i == num_sc_specs)
		return;

	sc_spec_ptr = &sc_spec[i];

	batt_aging_level = INVALID_AGING_LEVEL;

	for (i = 0; i < NUM_MAX_SC_METHODS; i++) {
		if (sc_spec_ptr->method[i]) {
			method_aging_level = sc_spec_ptr->method[i](cs_data, batt_stat, sysfs_param);
			if (method_aging_level > batt_aging_level)
				batt_aging_level = method_aging_level;
		}
	}

	if (batt_aging_level != INVALID_AGING_LEVEL)
		cs_data->batt_aging_level = batt_aging_level;

	/*
	 * for Debugging
	 * When debug_aging_mode in MiscTA2491 is set, aging level is determined
	 * based on its value instead of value that calculated with vt_cet/ct_charge
	 * table. The aging_level by this mode is not saved to MiscTA2491.
	 */
	if ((batt_stat->debug_aging_mode & DEBUG_MODE_MASK) == DEBUG_MODE_IDENTIFIER) {
		batt_aging_level = batt_stat->debug_aging_mode & DEBUG_AGING_LEVEL_MASK;
		LOGD("The aging_level fixed mode is enabled.\n");
	}

	if ((batt_aging_level != INVALID_AGING_LEVEL) &&
			sysfs_param[SFID_AGING_LEVEL].intval != batt_aging_level) {
		LOGD("Battery Aging Level: %d -> %d\n",
			sysfs_param[SFID_AGING_LEVEL].intval, batt_aging_level);
		sysfs_value.intval = batt_aging_level;
		sysfs_value.val_type = SYSFS_PARAM_VAL_INT;
		write_sysfs_param(SFID_AGING_LEVEL, &sysfs_value);
	}
}
