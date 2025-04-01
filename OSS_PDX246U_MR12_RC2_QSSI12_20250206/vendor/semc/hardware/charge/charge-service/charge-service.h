/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/
#ifndef _CHARGE_SERVICE_H_
#define _CHARGE_SERVICE_H_

#include <stdbool.h>
#include <time.h>
#include <errno.h>
#include <assert.h>
#include <cutils/properties.h>

#define UNUSED(x) (void)(x)

#define MAX_FILE_PATH 128

#define DEFAULT_DATA_DIR		"/data/vendor_de/"

#define VALID_CURRENT_TIME		(17167 * 24 * 60 * 60) /* 2017/1/1 0:00:00 (GMT) */
#define is_adjusted_time(time)		((time) >= VALID_CURRENT_TIME)

#define DEFAULT_PERIODIC_EVENT_INTERVAL	10

#define MAX_ARRHENIUS_RECORDS		108
#define MAX_STAY_CAP_DEGRADATION_RECORDS	108

#define INTERPOLATE(base, delta, resolution, count)	((base) + ((delta) * (count) / (resolution)))

struct cs_data_t {
	int periodic_event_interval;
	bool initial_control_completed;

	bool force_restoring_charge_full;

	time_t event_boot_time;
	time_t event_system_time;

	char data_dir[MAX_FILE_PATH];

	char charge_log_dir[MAX_FILE_PATH];
	int battlog_number;
	char battlog_label[PROP_VALUE_MAX];
	int battlog_line_count;

	int max_battlog_lines;
	off_t max_total_battlog_size;
	bool battlog_with_all_events;

	int regupdate_interval;
	bool stay_awake;

	int batt_aging_level;
	int cycle_aging_level;
	int arrhenius_aging_level;
	int online_time;
	int arrhenius_record_index;
	int full_time_aging_level;
	int full_stay_cap_degr_aging_level;
	long double arrhenius_per_10days_f[MAX_ARRHENIUS_RECORDS];
	long double total_arrhenius_f;
	long double full_stay_cap_degr_per_10days_f[MAX_STAY_CAP_DEGRADATION_RECORDS];
	long double total_full_stay_cap_degr_f;
	int full_stay_cap_degr_aging_level_record_index;
	int soh;

	time_t batt_degr2_idd_sent_time;
	time_t chg_insertion_removal_idd_sent_time;
	time_t batt_stat_saved_time;

	char product_name[PROP_VALUE_MAX];

	int usb_long_insertion_counter;
	bool fake_learning_completion;

	bool lrc_enabled;
	int lrc_operation;

	int bmlog_interval;
	char bmlog_categories[32];
	int bmlog_level;

	uint8_t usb_connector_heat_count;
	time_t usb_connector_heat_time;
};

typedef enum {
	CID_DATA_DIR,
	CID_MAX_BATTLOG_LINES,
	CID_MAX_TOTAL_BATTLOG_SIZE,
	CID_BATTLOG_WITH_ALL_EVENTS,
	CID_PERIODIC_EVENT_INTERVAL,
	CID_REGUPDATE_INTERVAL,
	CID_FAKE_LEARNING_COMPLETION,
	CID_BATTMAN_LOG_INTERVAL,
	CID_BATTMAN_LOG_CATEGORIES0,
	CID_BATTMAN_LOG_CATEGORIES1,
	CID_BATTMAN_LOG_CATEGORIES2,
	CID_BATTMAN_LOG_CATEGORIES3,
	CID_BATTMAN_LOG_LEVEL,
	NUM_CIDS
} CFG_PARAM_ID;

typedef enum {
	CVT_INT,
	CVT_STR,
} CFG_VAL_TYPE;

#define MAX_CFG_VAL_STR 32

struct cfg_param_t {
	char *name;
	int val_type;
	bool valid;
	union {
		int intval;
		char strval[MAX_CFG_VAL_STR];
	};
};

#endif /* _CHARGE_SERVICE_H_ */
