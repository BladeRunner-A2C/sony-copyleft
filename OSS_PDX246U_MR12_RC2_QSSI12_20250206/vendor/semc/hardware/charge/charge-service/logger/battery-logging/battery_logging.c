/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cutils/properties.h>
#include "charge-service.h"
#include "battery_logging.h"
#include "log.h"

#define LOG_TEXT_MAX_SIZE      4096

#define UNINITIALIZED_LINE_COUNT -1
#define LOG_TITLE_LINE_COUNT      2

#define CHARGE_LOG_SUB_DIR   "charge_log/"
#define BATTLOG_FILE_NAME    "battlog%03d_%s.csv"

#define MAX_NUM_BATTLOG_FILES  1000

#define DEFAULT_MAX_BATTLOG_LINES     10000
#define DEFAULT_MAX_TOTAL_BATTLOG_SIZE  300 /* 300MB */

#define LIMIT_MAX_BATTLOG_LINES      100000
#define LIMIT_MAX_TOTAL_BATTLOG_SIZE 102400 /* 100GB */

enum logval_type_t {
	LOGVAL_TYPE_RAW,
	LOGVAL_TYPE_INTVAL,
	LOGVAL_TYPE_FLOATVAL,
	LOGVAL_TYPE_STRVAL
};

struct battlog_item_t
{
	SYSFS_PARAM_ID	id;
	char	*title;
	int	logval_type;
	char	*format;
};

#define SAGAMI_BATT_LOG_MAJOR_VERSION    9
#define SAGAMI_BATT_LOG_MINOR_VERSION    2
#define SAGAMI_BATT_LOG_REVISION_VERSION 0

const static struct battlog_item_t sagami_battlog_item[] = {
	/* SFID					Title						Log Value Type		Format */
	{SFID_SYSTEM_STATUS,			"bootup_shutdown_phase",			LOGVAL_TYPE_RAW,	NULL},
	{SFID_CAPACITY,				"capacity",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_STATUS,				"status",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_TEMP,				"temp",						LOGVAL_TYPE_RAW,	NULL},
	{SFID_SYSTEM_TEMP_LEVEL,		"thermal_lv",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_AGING_LEVEL,			"batt_aging_level",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_CURRENT_NOW,			"current_now",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_VOLTAGE_NOW,			"voltage_now",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_VCELL_MAX,			"vcell_max",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_HEALTH,				"health",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_BATTERY_CHARGER_STATUS,		"battery_charger_status",			LOGVAL_TYPE_RAW,	NULL},
	{SFID_USB_ONLINE,			"usb_online",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_DC_ONLINE,			"dc_online",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_ACTIVE_CHAGER_TYPE,		"active_charger_type",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_USB_TYPE,				"usb_type",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_TYPEC_MODE,			"typec_mode",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_CHARGER_MAX_WATTAGE,		"charger_max_wattage",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_USB_ICL,				"usb_icl",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_AICL_RESULT,			"aicl_result",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_WEAK_LIMIT_CURRENT,		"weak_limit_current",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_USB_CURRENT_NOW,			"usb_current_now",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_USB_VOLTAGE_NOW,			"usb_voltage_now",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_DC_CURRENT_MAX,			"dc_icl",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_DC_VOLTAGE_NOW,			"dc_voltage_now",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_BATT_TEMP,			"batt_temp",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_THERMAL_ZONE_SDM_THERM,		"sdm_therm",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_REAL_TEMP,			"real_temp",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_CURRENT_JEITA_ZONE,		"jeita_zone",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_CURRENT_STEP_PHASE,		"step_phase",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_FV,				"fv",						LOGVAL_TYPE_RAW,	NULL},
	{SFID_FCC,				"fcc",						LOGVAL_TYPE_RAW,	NULL},
	{SFID_D2CP_CFG,				"d2cp_cfg",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_ICM_STATE,			"icm_state",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_BATTERY_SOC,			"batt_soc",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_SYSTEM_SOC,			"system_soc",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_MONOTONIC_SOC,			"monotonic_soc",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_FCSS_ERR_CNT,			"fcss_err_cnt",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_TIME_TO_FULL_NOW,			"time_to_full_now",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_CHARGE_FULL,			"charge_full",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_CHARGE_FULL_DESIGN,		"charge_full_design",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_LEARNED_CAPACITY,			"learned_capacity",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_LEARNING_COUNT,			"learning_counter",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_RESISTANCE,			"resistance",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_BATT_ID,				"batt_id",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_BATT_TYPE,			"batt_type",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_USB_ICL_VOTABLE_STATUS,		"USB ICL votable (Kernel)",			LOGVAL_TYPE_RAW,	NULL},
	{SFID_IUSB0_TOT_VOTABLE_STATUS,		"USB ICL votable (ADSP)",			LOGVAL_TYPE_RAW,	NULL},
	{SFID_FCC_VOTABLE_STATUS,		"FCC votable (Kernel)",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_FCC_0_VOTABLE_STATUS,		"FCC votable (ADSP)",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_FV_0_VOTABLE_STATUS,		"FV votable (ADSP)",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_FAKE_CHG_VOTABLE_STATUS,		"FakeChg votable (Kernel)",			LOGVAL_TYPE_RAW,	NULL},
	{SFID_FAKE_CHG_DISALLOW_VOTABLE_STATUS,	"FakeChg Disallow votable (Kernel)",		LOGVAL_TYPE_RAW,	NULL},
	{SFID_REG_CHGR_CHARGER_STATUS,		"0x2606\nchgr_chager_status",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_CHGR_VBAT_STATUS,		"0x2608\nchgr_vbat_status",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_CHGR_VBAT_STATUS2,		"0x2609\nchgr_vbat_status2",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_CHGR_IBAT_STATUS,		"0x260A\nchgr_ibat_status",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_CHGR_VFLT_STATUS,		"0x260B\nchgr_vflt_status",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_CHGR_INT_RT_STS,		"0x260E\nchgr_int_rt_sts",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_CHGR_ICHG_STATUS,		"0x2610\nchgr_ichg_status",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_CHG_ENABLED,			"0x2646\nchg_enabled",				LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_FAST_CHG_CURRENT_CFG,		"0x2654\nfast_chg_current_cfg",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_FLOAT_VOLTAGE_CFG,		"0x2658\nfloat_voltage_cfg",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_ICL_MAX_STATUS,		"0x2706\nicl_max_status",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_AICL_STATUS,			"0x2707\naicl_status",				LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_ICL_STATUS,			"0x2709\nicl_status",				LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_POWER_PATH_STATUS,		"0x270B\npower_path_status",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_BST_STATUS,			"0x270D\nbst_status",				LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_DCDC_INT_RT_STS,		"0x2710\ndcdc_int_rt_sts",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_BATIF_TEMP_STATUS,		"0x280D\nbatif_temp_status",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_BATIF_INT_RT_STS,		"0x2810\nbatif_int_rt_sts",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_BATIF_SHIP_MODE,		"0x2852\nbatif_ship_mode",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_USBIN_INPUT_STATUS,		"0x2906\nusbin_input_status",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_VUSB_STATUS,			"0x2908\nvusb_status",				LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_APSD_STATUS,			"0x290A\napsd_status",				LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_APSD_RESULT_STATUS,		"0x290B\napsd_result_status",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_USB_INT_RT_STS,		"0x2910\nusb_int_rt_sts",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_USBIN_ADAPTER_ALLOW_OVERRIDE,	"0x2941\nusbin_adapter_allow_override",		LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_USBIN_ADAPTER_ALLOW_CFG,	"0x2940\nusbin_adapter_allow_cfg",		LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_APSD_ENABLED,			"0x2944\napsd_enabled",				LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_USBIN_CURRENT_LIMIT_CFG,	"0x2952\nusbin_current_limit_cfg",		LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_USB_CMD_IL,			"0x2954\nusb_cmd_il",				LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_WLS_INPUT_STATUS,		"0x2A06\nwls_input_status",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_WLS_VWLS_STATUS,		"0x2A08\nwls_vwls_status",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_WLS_INT_RT_STS,		"0x2A10\nwls_int_rt_sts",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_WLS_ADAPTER_ALLOW_CFG,	"0x2A40\nwls_adapter_allow_cfg",		LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_WLS_ICL_CFG,			"0x2A52\nwls_icl_cfg",				LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_WLS_SUSPEND,			"0x2A54\nwls_suspend",				LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_TYPEC_SNK_STATUS,		"0x2B06\ntype_c_snk_status",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_TYPEC_SNK_DBG_ACS_STATUS,	"0x2B07\ntype_c_snk_debug_access_status",	LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_TYPEC_SRC_STATUS,		"0x2B08\ntype_c_src_status",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_TYPEC_STAT_MCN_STATUS,	"0x2B09\ntype_c_state_machine_status",		LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_TYPEC_MISC_STATUS,		"0x2B0B\ntype_c_misc_status",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_TYPEC_TRY_SNK_SRC_STATUS,	"0x2B0C\ntype_c_try_snk_src_status",		LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_TYPEC_LGCY_CBL_STATUS,	"0x2B0D\ntype_c_legacy_cable_status",		LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_TYPEC_INT_RT_STS,		"0x2B10\ntypec_int_rt_sts",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_TYPEC_MODE_CFG,		"0x2B44\ntype_c_mode_cfg",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_MISC_AICL_STATUS,		"0x2C06\nmisc_aicl_status",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_MISC_WDOG_STATUS,		"0x2C07\nmisc_wdog_status",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_MISC_SYSOK_REASON_STATUS,	"0x200D\nmisc_sysok_reason_status",		LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_REG_MISC_INT_RT_STS,		"0x2C10\nmisc_int_rt_sts",			LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_WLS_VRECT,			"vrect",					LOGVAL_TYPE_RAW,	NULL},
	{SFID_WLS_VOUT,				"vout",						LOGVAL_TYPE_RAW,	NULL},
	{SFID_WLS_IOUT,				"iout",						LOGVAL_TYPE_RAW,	NULL},
	{SFID_WIRELESS_BOOST_EN,		"wireless_boost_en",				LOGVAL_TYPE_STRVAL,	"%s"},
	{SFID_WLS_STATUS,			"wls_status",					LOGVAL_TYPE_STRVAL,	"%s"},
	{SFID_WLS_TYPE,				"wls_type",					LOGVAL_TYPE_STRVAL,	"%s"},
	{SFID_WLS_MFR_CODE,			"manufacturer_code",				LOGVAL_TYPE_INTVAL,	"0x%02X"},
	{SFID_CURRENT_ICL,			"wls_current_icl",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_TARGET_ICL,			"wls_target_icl",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_CURRENT_VOUT,			"wls_current_vout",				LOGVAL_TYPE_RAW,	NULL},
	{SFID_TARGET_VOUT,			"wls_target_vout",				LOGVAL_TYPE_RAW,	NULL},
};

struct battlog_info_t
{
	const char	*platform;
	const int	major_version;
	const int	minor_version;
	const int	revision_version;
	const struct battlog_item_t *item;
	const int	num_items;
};

const static struct battlog_info_t battlog_info[] = {
	{
		"sagami",
		SAGAMI_BATT_LOG_MAJOR_VERSION,
		SAGAMI_BATT_LOG_MINOR_VERSION,
		SAGAMI_BATT_LOG_REVISION_VERSION,
		sagami_battlog_item,
		sizeof(sagami_battlog_item) / sizeof(struct battlog_item_t)
	},
};
const static int num_battlog_info = sizeof(battlog_info) / sizeof(struct battlog_info_t);

const static struct battlog_info_t *get_battlog_info(void)
{
	int i;

	for (i = 0; i < num_battlog_info; i++) {
		if (strcmp(battlog_info[i].platform, SOMC_PLATFORM) == 0)
			break;
	}
	if (i >= num_battlog_info)
		i = 0;

	return &battlog_info[i];
}

static int dir_exists(char *dir_path)
{
	struct stat s;
	int rv;

	rv = stat(dir_path, &s);
	return rv ? 0 : S_ISDIR(s.st_mode);
}

void init_battery_log_params(struct cs_data_t *cs_data, const struct cfg_param_t *cfg_param)
{
	DIR *charge_log_dp;
	struct dirent *charge_log_dirent;
	int number;
	char label[PROP_VALUE_MAX];
	char date[PROP_VALUE_MAX];
	int label_add_pos;
	time_t build_utc;
	struct tm *build_tm;

	if (!dir_exists(cs_data->data_dir))
		return;

	strlcpy(cs_data->charge_log_dir, cs_data->data_dir, sizeof(cs_data->charge_log_dir));

	if (cs_data->charge_log_dir[strlen(cs_data->charge_log_dir) - 1] != '/')
		strlcat(cs_data->charge_log_dir, "/", sizeof(cs_data->charge_log_dir));

	strlcat(cs_data->charge_log_dir, CHARGE_LOG_SUB_DIR, sizeof(cs_data->charge_log_dir));

	if (!dir_exists(cs_data->charge_log_dir)) {
		if (mkdir(cs_data->charge_log_dir, 0700))
			return;
	}

	cs_data->battlog_number = 0;

	charge_log_dp = opendir(cs_data->charge_log_dir);

	if (charge_log_dp) {
		while (1) {
			charge_log_dirent = readdir(charge_log_dp);
			if (!charge_log_dirent)
				break;

			if (charge_log_dirent->d_type != DT_REG ||
					strncmp(charge_log_dirent->d_name, "battlog", strlen("battlog")))
				continue;

			if (sscanf(charge_log_dirent->d_name, "battlog%03d", &number) == 1 &&
								number > cs_data->battlog_number)
				cs_data->battlog_number = number;
		}
		closedir(charge_log_dp);
	}

	property_get("ro.vendor.build.id", label, "private");
	if (!strcmp(label, "private")) {
		label_add_pos = strlen(label);
		property_get("ro.vendor.build.date.utc", date, "");
		if (!strcmp(date, "")) {
			snprintf(&label[label_add_pos], sizeof(label) - label_add_pos,
				"_%s", "unknown");
		} else {
			build_utc = strtoll(date, NULL, 10);
			build_tm = gmtime(&build_utc);
			snprintf(&label[label_add_pos], sizeof(label) - label_add_pos,
				"_%02d%02d%02d_%02d%02d",
				build_tm->tm_year % 100, build_tm->tm_mon + 1, build_tm->tm_mday,
				build_tm->tm_hour, build_tm->tm_min);
		}
	}
	strlcpy(cs_data->battlog_label, label, sizeof(cs_data->battlog_label));

	cs_data->battlog_line_count = UNINITIALIZED_LINE_COUNT;

	if (cfg_param[CID_MAX_BATTLOG_LINES].valid &&
			cfg_param[CID_MAX_BATTLOG_LINES].intval >= 1 &&
			cfg_param[CID_MAX_BATTLOG_LINES].intval <= LIMIT_MAX_BATTLOG_LINES)
		cs_data->max_battlog_lines = cfg_param[CID_MAX_BATTLOG_LINES].intval;
	else
		cs_data->max_battlog_lines = DEFAULT_MAX_BATTLOG_LINES;

	if (cfg_param[CID_MAX_TOTAL_BATTLOG_SIZE].valid &&
			cfg_param[CID_MAX_TOTAL_BATTLOG_SIZE].intval >= 1 &&
			cfg_param[CID_MAX_TOTAL_BATTLOG_SIZE].intval <= LIMIT_MAX_TOTAL_BATTLOG_SIZE)
		cs_data->max_total_battlog_size = (off_t)cfg_param[CID_MAX_TOTAL_BATTLOG_SIZE].intval * 1024 * 1024;
	else
		cs_data->max_total_battlog_size = DEFAULT_MAX_TOTAL_BATTLOG_SIZE * 1024 * 1024;
}

static int write_battlog_file(char *charge_log_dir, int battlog_number, char *battlog_label, char *str)
{
	FILE *fp;
	int rc;
	char path[MAX_FILE_PATH];

	if (!str)
		return -1;

	snprintf(path, sizeof(path), "%s" BATTLOG_FILE_NAME, charge_log_dir, battlog_number, battlog_label);

	fp = fopen(path, "a");
	if (!fp) {
		LOG("Open error: '%s'", path);
		return -1;
	}

	rc = fwrite(str, strlen(str), 1, fp);
	fclose(fp);

	return rc;
}

static int battlog_file_exists(char *charge_log_dir, int battlog_number, char *battlog_label)
{
	struct stat s;
	int rv;
	char path[MAX_FILE_PATH];

	snprintf(path, sizeof(path), "%s" BATTLOG_FILE_NAME, charge_log_dir, battlog_number, battlog_label);

	rv = stat(path, &s);
	return rv ? 0 : S_ISREG(s.st_mode);
}

static int get_battlog_line_count(char *charge_log_dir, int battlog_number, char *battlog_label)
{
	FILE *fp;
	int cnt = 0;
	bool in_quotes = false;
	int ch;
	char path[MAX_FILE_PATH];

	snprintf(path, sizeof(path), "%s" BATTLOG_FILE_NAME, charge_log_dir, battlog_number, battlog_label);

	fp = fopen(path, "r");
	if (!fp) {
		LOG("Open error: '%s'", path);
		return LIMIT_MAX_BATTLOG_LINES;
	}

	while ((ch = getc(fp)) != EOF) {
		if (!in_quotes) {
			if (ch == '\"')
				in_quotes = true;
			else if (ch == '\n')
				cnt++;
		} else {
			if (ch == '\"')
				in_quotes = false;
		}
	}

	fclose(fp);

	if (cnt >= LOG_TITLE_LINE_COUNT)
		cnt -= LOG_TITLE_LINE_COUNT;
	else
		cnt = LIMIT_MAX_BATTLOG_LINES;

	return cnt;
}

static int create_new_battlog_file(char *charge_log_dir, int battlog_number, char *battlog_label)
{
	char line_buf[LOG_TEXT_MAX_SIZE];
	int pos;
	int cnt;
	int i;
	int rc;
	const struct battlog_info_t *battlog_info = get_battlog_info();

	/*** Title line 1 ***/
	pos = 0;

	/* Platform, Battery log version */
	cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos,
		"\"platform: %s, version: %d.%d.%d\"\n",
		battlog_info->platform,
		battlog_info->major_version, battlog_info->minor_version, battlog_info->revision_version);
	pos += (cnt >= 0) ? cnt : 0;

	rc = write_battlog_file(charge_log_dir, battlog_number, battlog_label, line_buf);
	if (rc < 0)
		return rc;

	/*** Title line 2 ***/
	pos = 0;

	/* Basic parameter: date */
	cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos, "\"%s\"", "date");
	pos += (cnt >= 0) ? cnt : 0;

	/* Basic parameter: time */
	cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos, ",\"%s\"", "time");
	pos += (cnt >= 0) ? cnt : 0;

	/* Basic parameter: ktime */
	cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos, ",\"%s\"", "ktime");
	pos += (cnt >= 0) ? cnt : 0;

	/* Basic parameter: event */
	cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos, ",\"%s\"", "event");
	pos += (cnt >= 0) ? cnt : 0;

	/* Platform specific parameters */
	for (i = 0; i < battlog_info->num_items; i++) {
		cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos, ",\"%s\"", battlog_info->item[i].title);
		pos += (cnt >= 0) ? cnt : 0;
	}
	cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos, "%c", '\n');
	pos += (cnt >= 0) ? cnt : 0;

	rc = write_battlog_file(charge_log_dir, battlog_number, battlog_label, line_buf);

	return rc;
}

static int remove_old_battlog_if_over_limit(char *charge_log_dir, int max_total_battlog_size)
{
	DIR *charge_log_dp;
	struct dirent *charge_log_dirent;
	off_t total_battlog_size;
	int i;
	int number;
	struct stat s;
	struct _battlog_list {
		bool valid;
		char path[MAX_FILE_PATH];
		off_t size;
	} *battlog_list;
	const int battlog_list_size = sizeof(struct _battlog_list) * MAX_NUM_BATTLOG_FILES;

	charge_log_dp = opendir(charge_log_dir);

	if (!charge_log_dp)
		return -1;

	battlog_list = malloc(battlog_list_size);
	if (!battlog_list)
		return -1;

	memset(battlog_list, 0, battlog_list_size);

	total_battlog_size = 0;
	while (1) {
		charge_log_dirent = readdir(charge_log_dp);
		if (!charge_log_dirent)
			break;

		if (charge_log_dirent->d_type != DT_REG ||
				strncmp(charge_log_dirent->d_name, "battlog", strlen("battlog")))
			continue;

		if (sscanf(charge_log_dirent->d_name, "battlog%03d", &number) != 1 ||
					number < 0 || number >= MAX_NUM_BATTLOG_FILES)
			continue;

		i = number;

		snprintf(battlog_list[i].path, sizeof(battlog_list[i].path), "%s%s",
						charge_log_dir, charge_log_dirent->d_name);

		if (stat(battlog_list[i].path, &s))
			continue;

		battlog_list[i].size = s.st_size;
		battlog_list[i].valid = true;

		total_battlog_size += battlog_list[i].size;
	}
	closedir(charge_log_dp);

	for (i = 0; total_battlog_size > max_total_battlog_size && i < MAX_NUM_BATTLOG_FILES; i++) {
		if (!battlog_list[i].valid)
			continue;

		if (!remove(battlog_list[i].path))
			total_battlog_size -= battlog_list[i].size;

		battlog_list[i].valid = false;
	}

	free(battlog_list);

	if (total_battlog_size > max_total_battlog_size)
		return -1;

	return 0;
}

static int prepare_battlog_file(struct cs_data_t *cs_data)
{
	if (!dir_exists(cs_data->charge_log_dir))
		return -1;

	if (cs_data->battlog_number >= MAX_NUM_BATTLOG_FILES)
		return -1;

	if (battlog_file_exists(cs_data->charge_log_dir, cs_data->battlog_number, cs_data->battlog_label)) {
		if (cs_data->battlog_line_count == UNINITIALIZED_LINE_COUNT)
			cs_data->battlog_line_count = get_battlog_line_count(
				cs_data->charge_log_dir, cs_data->battlog_number, cs_data->battlog_label);
	}

	if (cs_data->battlog_line_count >= cs_data->max_battlog_lines) {
		cs_data->battlog_line_count = UNINITIALIZED_LINE_COUNT;
		cs_data->battlog_number++;
		if (cs_data->battlog_number >= MAX_NUM_BATTLOG_FILES)
			return -1;

		if (remove_old_battlog_if_over_limit(cs_data->charge_log_dir, cs_data->max_total_battlog_size) < 0)
			return -1;
	}
	if (cs_data->battlog_line_count == UNINITIALIZED_LINE_COUNT) {
		if (create_new_battlog_file(cs_data->charge_log_dir, cs_data->battlog_number, cs_data->battlog_label) < 0)
			return -1;
		cs_data->battlog_line_count = 0;
	}

	return 0;
}

void output_battery_log(
	struct cs_data_t *cs_data,
	const struct sysfs_param_t *sysfs_param,
	const char *event_name)
{
	char line_buf[LOG_TEXT_MAX_SIZE];
	int pos;
	int cnt;
	int i;
	int rc;
	struct tm *stm;
	const struct battlog_info_t *battlog_info = get_battlog_info();
	const struct battlog_item_t *battlog_item;

	if (prepare_battlog_file(cs_data) < 0) {
		LOG("Failed to prepare battlog file, logging is skipped\n");
		return;
	}

	pos = 0;
	stm = localtime(&cs_data->event_system_time);

	/* Basic parameter: date */
	cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos, "\"%04d/%02d/%02d\"",
		1900 + stm->tm_year, 1 + stm->tm_mon, stm->tm_mday);
	pos += (cnt >= 0) ? cnt : 0;

	/* Basic parameter: time */
	cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos, ",\"%02d:%02d:%02d\"",
		stm->tm_hour, stm->tm_min, stm->tm_sec);
	pos += (cnt >= 0) ? cnt : 0;

	/* Basic parameter: ktime */
	cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos, ",\"%ld\"", cs_data->event_boot_time);
	pos += (cnt >= 0) ? cnt : 0;

	/* Basic parameter: event */
	cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos, ",\"%s\"", event_name);
	pos += (cnt >= 0) ? cnt : 0;

	/* Platform specific parameters */
	for (i = 0; i < battlog_info->num_items; i++) {
		battlog_item = &battlog_info->item[i];

		cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos, "%c%c", ',', '\"');
		pos += (cnt >= 0) ? cnt : 0;

		if (strlen(sysfs_param[battlog_item->id].raw) > 0) {
			switch (battlog_item->logval_type) {
			case LOGVAL_TYPE_RAW:
				cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos,
					"%s", sysfs_param[battlog_item->id].raw);
				break;
			case LOGVAL_TYPE_INTVAL:
				assert(battlog_item->format);
				assert(sysfs_param[battlog_item->id].val_type == SYSFS_PARAM_VAL_INT);
				cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos,
					battlog_item->format, sysfs_param[battlog_item->id].intval);
				break;
			case LOGVAL_TYPE_FLOATVAL:
				assert(battlog_item->format);
				assert(sysfs_param[battlog_item->id].val_type == SYSFS_PARAM_VAL_FLOAT);
				cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos,
					battlog_item->format, sysfs_param[battlog_item->id].floatval);
				break;
			case LOGVAL_TYPE_STRVAL:
				assert(battlog_item->format);
				assert(sysfs_param[battlog_item->id].val_type == SYSFS_PARAM_VAL_STR);
				cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos,
					battlog_item->format, sysfs_param[battlog_item->id].strval);
				break;
			default:
				assert(true);
				break;
			}
		} else {
			cnt = 0;
		}
		pos += (cnt >= 0) ? cnt : 0;

		cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos, "%c", '\"');
		pos += (cnt >= 0) ? cnt : 0;
	}

	cnt = snprintf(&line_buf[pos], sizeof(line_buf) - pos, "%c", '\n');
	pos += (cnt >= 0) ? cnt : 0;

	rc = write_battlog_file(cs_data->charge_log_dir, cs_data->battlog_number, cs_data->battlog_label, line_buf);
	if (rc < 0) {
		LOG("Write error: %d[%s]\n", rc, strerror(errno));
		return;
	}

	cs_data->battlog_line_count++;
}
