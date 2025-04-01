/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/

#ifndef _MISCTA_BATT_STATS_H_
#define _MISCTA_BATT_STATS_H_

#include <stdint.h>
#include "data/sysfs_accessor.h"

/* MiscTA2491 VERSION */
#define BATT_STAT_MAJOR_VERSION    5
#define BATT_STAT_MINOR_VERSION    2
#define BATT_STAT_REVISION_VERSION 0

#define CURRENT_BATT_STAT_COMPATIBLE_SIZE 5632

#define VERSION_SIZE			3
#define MAX_FCC_NUM			5
#define MAX_BATTERY_MODEL_NAME		16
#define MAX_SOH_TIME_NUM		9
#define MAX_TEMP_STEP			16
#define MAX_VBATT_STEP			42
#define MAX_SOC_STEP			10
#define MAX_SC1_TIME_NUM		5
#define MAX_SC5_TIME_NUM		5
#define THERMAL_RANGE_NUM		4
#define MAX_DISCHARGE_CURRENT_NUM	4
#define MAX_DISCHARGE_CASE		8
#define MAX_DEV_TYPES			16
#define ARRHENIUS_RECORDS_NUM		108
#define STAY_CAP_DEGRADE_RECORDS_NUM	108
#define SOH_RECORDS_NUM			108

#define RESERVED_3BYTE			3
#define RESERVED_4BYTE			4
#define RESERVED_6BYTE			6
#define RESERVED_7BYTE			7
#define RESERVED_8BYTE			8
#define RESERVED_12BYTE			12
#define RESERVED_14BYTE			14
#define RESERVED_15BYTE			15
#define RESERVED_16BYTE			16
#define RESERVED_18BYTE			18
#define RESERVED_20BYTE			20
#define RESERVED_28BYTE			28
#define RESERVED_32BYTE			32
#define RESERVED_36BYTE			36
#define RESERVED_48BYTE			48
#define RESERVED_56BYTE			56
#define RESERVED_78BYTE			78
#define RESERVED_148BYTE		148
#define RESERVED_180BYTE		180

struct batt_stat_t {
	/* Common & SOH(FCC Learning) Area */
	uint8_t		initialize;
	uint8_t		version[VERSION_SIZE];
	uint16_t	fcc_mah[MAX_FCC_NUM];					/* Finally FCC mAh when aging mode completed learning */
	uint16_t	learning_total_cnt;					/* The number of times that learned in total */

	uint8_t		battery_model_name[MAX_BATTERY_MODEL_NAME];		/* saved the battery name strings */

	uint64_t	initialized_time;					/* Time stamp at the time of the initialization */
	uint64_t	last_learning_boot_time;
	uint64_t	last_learning_time;					/* The last system time that FCC learning completed */
	uint64_t	first_learning_time;					/* The first system time that FCC learning completed */
	uint64_t	first_soh_time[MAX_SOH_TIME_NUM];			/* The time stamp when SOH was less than xx% for the first time */
	uint8_t		reserved_1[RESERVED_7BYTE];
	uint8_t		last_shutdown_soc;					/* SoC when shut down timing.*/

	/* Soft Charge Management Area */
	uint32_t	soft_charge_mode;					/* The judge enable / disable of softcharge mode */
	uint8_t		reserved_2[RESERVED_4BYTE];
	uint32_t	total_cycle_count;					/* Total charged capacity (For example, when a user charge a phone from 30% to 100%, this increases by 70) */
	uint8_t		reserved_3[RESERVED_4BYTE];
	uint64_t	sc1_first_start_time[MAX_SC1_TIME_NUM];			/* The time stamp when Soft Charge 1.1 step1~5 triggered at first */
	uint64_t	sc5_first_start_time[MAX_SC5_TIME_NUM];			/* The time stamp when Soft Charge 5.1 step1~5 triggered at first */
	uint8_t		reserved_4[RESERVED_16BYTE];

	/* Table Area */
	uint32_t	vt_cet_table[MAX_VBATT_STEP][MAX_TEMP_STEP];		/* Accmulated Time Table */
	uint32_t	ct_charge_table[MAX_SOC_STEP][MAX_TEMP_STEP];		/* Cycle Count Table */

	/* Misc Area */
	uint32_t	full_cnt;						/* The number of times that became the full charge */
	uint32_t	recharge_cnt;						/* The number of times that became the recharge */
	uint32_t	learning_try_cnt;					/* The number of times that became the learning */
	uint8_t		reserved_5[RESERVED_4BYTE];
	uint32_t	soc0_shutdown_cnt;					/* The battery level 0 number of times, expect the off charge */
	uint32_t	safety_timer_cnt;					/* The safety timer counter */
	uint8_t		reserved_6[RESERVED_8BYTE];
	uint64_t	off_charge_total_time;					/* The accumulated time on power off charge mode */
	uint64_t	on_charge_total_time;					/* The accumulated time on power on charge mode (=on Android) */
	uint64_t	soc_full_time;						/* Time between SOC 100% */
	uint64_t	smart_charge_mode_time;					/* The accumulated time while battery charging is suspended by Battery Care feature */
	uint8_t		reserved_7[RESERVED_16BYTE];
	uint32_t	jeita_warm_time;					/* The accumulated time during Warm/Overheat as an Android framework */
	uint8_t		reserved_8[RESERVED_28BYTE];
	uint32_t	thermal_range_stay_time[THERMAL_RANGE_NUM];		/* Sojoum time to Thermal Lv.([0]:Lv0 [1]:Lv1~12 [2]:Lv13 [3]: Lv14) */
	uint32_t	over_08c_total_time;					/* The total time when there is phone in upper 0.8C */
	uint32_t	over_08c_charge_count;					/* The charge count when there is phone in upper 0.8C */
	uint32_t	over_06c_total_time;					/* The total time when there is phone in upper 0.6C */
	uint32_t	over_06c_charge_count;					/* The charge count when there is phone in upper 0.6C */
	uint16_t	max_discharge_current[MAX_DISCHARGE_CURRENT_NUM];	/* Maxmum discharge current(mA) */
	uint8_t		reserved_9[RESERVED_4BYTE];
	int16_t		max_temp;
	int16_t		min_temp;
	uint32_t	max_discharge_current_time[MAX_DISCHARGE_CURRENT_NUM];
	uint8_t		reserved_10[RESERVED_8BYTE];
	uint32_t	max_temp_time;
	uint32_t	min_temp_time;
	uint32_t	total_discharge_time[MAX_DISCHARGE_CASE];
	uint16_t	fcc_mah_raw[MAX_FCC_NUM];				/* Final FCC raw mAh when aging mode completed learning without the limiting control */
	uint16_t	max_cell_voltage;
	uint32_t	max_cell_voltage_time;
	uint8_t		reserved_11[RESERVED_12BYTE];
	uint8_t		debug_aging_mode;					/* For debug mode that fixes aging level (When setting D0~D3, this mode becomes active) */
	uint8_t		reserved_12[RESERVED_3BYTE];

	/* Charger Info Area */
	struct {
		uint32_t	attach_count;					/* Total count the USB SDP CHARGER is attatched */
		uint32_t	attach_time;					/* The accumulated time while the USB SDP CHARGER is attatched */
		uint32_t	charge_count;					/* Total cycle count USB SDP CHARGER */
		uint8_t		reserved_13[RESERVED_4BYTE];
	} dev[MAX_DEV_TYPES];

	/* Arrhenius Area */
	uint32_t	online_time;						/* online time */
	uint8_t		reserved_14[RESERVED_12BYTE];
	uint32_t	total_arrhenius;					/* Current total Arrhenius time */
	uint8_t		reserved_15[RESERVED_12BYTE];
	uint32_t	arrhenius_per_10days[ARRHENIUS_RECORDS_NUM];		/* Arrhenius accumulation level every 10th */
	uint8_t		reserved_16[RESERVED_48BYTE];
	uint8_t		arrhenius_aging_level_record[ARRHENIUS_RECORDS_NUM];
	uint8_t		reserved_17[RESERVED_180BYTE];
	uint32_t	full_stay_cap_degradation_per_10days[STAY_CAP_DEGRADE_RECORDS_NUM];
	uint8_t		reserved_18[RESERVED_48BYTE];
	uint8_t		full_stay_cap_degradation_aging_level_record[STAY_CAP_DEGRADE_RECORDS_NUM];
	uint8_t		reserved_19[RESERVED_36BYTE];
	uint8_t		soh_record[STAY_CAP_DEGRADE_RECORDS_NUM];
	uint8_t		reserved_20[RESERVED_4BYTE];

} __attribute__((__packed__)); /* Total 5632 byte of MISC_DATA_SIZE */

enum {
	AGGR_CHARGER_TYPE_UNKNOWN = -1,
	AGGR_CHARGER_TYPE_USB_DCP = 0,
	AGGR_CHARGER_TYPE_USB_SDP,
	AGGR_CHARGER_TYPE_USB_CDP,
	AGGR_CHARGER_TYPE_USB_PROPRIETARY,
	AGGR_CHARGER_TYPE_USB_TYPEC,
	AGGR_CHARGER_TYPE_USB_FLOATED,
	AGGR_CHARGER_TYPE_USB_AUDIO_ADAPTER,
	AGGR_CHARGER_TYPE_USB_PD_RANK_1,
	AGGR_CHARGER_TYPE_USB_PD_RANK_2,
	AGGR_CHARGER_TYPE_USB_PD_RANK_3,
	AGGR_CHARGER_TYPE_USB_PD_RANK_4,
	AGGR_CHARGER_TYPE_USB_PD_RANK_5,
	AGGR_CHARGER_TYPE_USB_RESERVED,
	AGGR_CHARGER_TYPE_WIRELESS_QI_BPP,
	AGGR_CHARGER_TYPE_WIRELESS_QI_EPP,
	AGGR_CHARGER_TYPE_WIRELESS_RESERVED,
	MAX_AGGR_CHARGER_TYPE,
};

#define SECONDS_IN_10DAYS	864000	/* 10 * 24 * 60 * 60 */

void init_batt_stat(struct cs_data_t *cs_data, struct batt_stat_t *batt_stat);
bool can_save_batt_stat(struct cs_data_t *cs_data, const struct sysfs_param_t *sysfs_param, const struct batt_stat_t *batt_stat);
void save_batt_stat(struct cs_data_t *cs_data, const struct batt_stat_t *batt_stat);
void update_batt_stat(
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	const struct sysfs_param_t *sysfs_param);
void update_batt_stat_after_control(
	struct cs_data_t *cs_data, struct batt_stat_t *batt_stat);

#endif /* _MISCTA_BATT_STATS_H_ */
