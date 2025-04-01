/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cutils/properties.h>
#include "charge-service.h"
#include "data/sysfs_accessor.h"
#include "data/uevent_processor.h"
#include "logger/charge-logging/miscta_batt_stat.h"
#include "logger/charge-logging/chg_insertion_removal.h"
#include "logger/battery-logging/battery_logging.h"
#include "logger/idd/idd_batt_degr2.h"
#include "logger/idd/idd_chg_insertion_removal.h"
#include "func/miscta_handler.h"
#include "func/aging_mode_setter.h"
#include "func/charge_full.h"
#include "func/lrc_mode.h"
#include "func/external_thermal_data.h"
#include "log.h"

#define CONFIG_FILE_PATH             "/vendor/etc/charge-service.cfg"
#define CONFIG_LINE_BUF_SIZE         256
#define CONFIG_PARAM_MIN             2
#define CONFIG_COMMENT               '#'

static struct cfg_param_t *get_cfg_params(void)
{
	static struct cfg_param_t cfg_param[NUM_CIDS] = {
		[CID_DATA_DIR] =			{"data_dir",			CVT_STR, false, {0}},
		[CID_MAX_BATTLOG_LINES] =		{"max_battlog_lines",		CVT_INT, false, {0}},
		[CID_MAX_TOTAL_BATTLOG_SIZE] =		{"max_total_battlog_size",	CVT_INT, false, {0}},
		[CID_BATTLOG_WITH_ALL_EVENTS] =		{"battlog_with_all_events",	CVT_INT, false, {0}},
		[CID_PERIODIC_EVENT_INTERVAL] =		{"periodic_event_interval",	CVT_INT, false, {0}},
		[CID_REGUPDATE_INTERVAL] =		{"bmdbg_regupdate_interval",	CVT_INT, false, {0}},
		[CID_FAKE_LEARNING_COMPLETION] =	{"fake_learning_completion",	CVT_INT, false, {0}},
		[CID_BATTMAN_LOG_INTERVAL] =		{"battman_log_interval",	CVT_INT, false, {0}},
		[CID_BATTMAN_LOG_CATEGORIES0] =		{"battman_log_categories0",	CVT_INT, false, {0}},
		[CID_BATTMAN_LOG_CATEGORIES1] =		{"battman_log_categories1",	CVT_INT, false, {0}},
		[CID_BATTMAN_LOG_CATEGORIES2] =		{"battman_log_categories2",	CVT_INT, false, {0}},
		[CID_BATTMAN_LOG_CATEGORIES3] =		{"battman_log_categories3",	CVT_INT, false, {0}},
		[CID_BATTMAN_LOG_LEVEL] =		{"battman_log_level",		CVT_INT, false, {0}},
	};

#ifdef BUILD_VARIANT_NOT_USER
	FILE *fp;
	int i;
	char config_line_buf[CONFIG_LINE_BUF_SIZE];
	char config_name[CONFIG_LINE_BUF_SIZE];
	char config_param[CONFIG_LINE_BUF_SIZE];
	int scanned_result;

	fp = fopen(CONFIG_FILE_PATH, "r");
	if (fp == NULL)
		return cfg_param;

	LOG("config file exists, load parameters\n");

	while (fgets(config_line_buf, sizeof(config_line_buf), fp)) {
		if (config_line_buf[0] == CONFIG_COMMENT ||
				config_line_buf[0] == '\r' || config_line_buf[0] == '\n')
			continue;

		memset(config_name, 0, sizeof(config_name));
		scanned_result = sscanf(config_line_buf, "%80s%80s", config_name, config_param);
		if (scanned_result == EOF || scanned_result < CONFIG_PARAM_MIN) {
			LOG("unparsable line: %s\n", config_line_buf);
			continue;
		}

		LOG("%s = %s\n", config_name, config_param);

		for (i = 0; i < NUM_CIDS && strcmp(config_name, cfg_param[i].name); i++);

		if (i < NUM_CIDS) {
			switch (cfg_param[i].val_type) {
			case CVT_INT:
				cfg_param[i].valid = true;
				cfg_param[i].intval = strtol(config_param, NULL, 0);
				break;
			case CVT_STR:
				cfg_param[i].valid = true;
				strlcpy(cfg_param[i].strval, config_param, sizeof(cfg_param[i].strval));
				break;
			default:
				LOG("undefine value type: %d\n", cfg_param[i].val_type);
			}
		} else {
			LOG("invalid parameter: %s\n", config_name);
		}
	}

	fclose(fp);
#endif

	return cfg_param;
}

static void init_cs_data(struct cs_data_t *cs_data)
{
	const struct cfg_param_t *cfg_param = get_cfg_params();

	if (cfg_param[CID_DATA_DIR].valid)
		strlcpy(cs_data->data_dir, cfg_param[CID_DATA_DIR].strval, sizeof(cs_data->data_dir));
	else
		strlcpy(cs_data->data_dir, DEFAULT_DATA_DIR, sizeof(cs_data->data_dir));

	cs_data->initial_control_completed = false;
	cs_data->force_restoring_charge_full = false;

	cs_data->event_boot_time = 0;
	cs_data->event_system_time = 0;

	if (cfg_param[CID_PERIODIC_EVENT_INTERVAL].valid && cfg_param[CID_PERIODIC_EVENT_INTERVAL].intval >= 0)
		cs_data->periodic_event_interval = cfg_param[CID_PERIODIC_EVENT_INTERVAL].intval;
	else
		cs_data->periodic_event_interval = DEFAULT_PERIODIC_EVENT_INTERVAL;

	if (cfg_param[CID_REGUPDATE_INTERVAL].valid && cfg_param[CID_REGUPDATE_INTERVAL].intval > 0)
		cs_data->regupdate_interval = cfg_param[CID_REGUPDATE_INTERVAL].intval;
	else
		cs_data->regupdate_interval = 0;

	cs_data->stay_awake = false;

	cs_data->batt_aging_level = INVALID_AGING_LEVEL;
	cs_data->cycle_aging_level = INVALID_AGING_LEVEL;
	cs_data->arrhenius_aging_level = INVALID_AGING_LEVEL;
	cs_data->arrhenius_record_index = -1;

	cs_data->batt_degr2_idd_sent_time = cs_data->event_boot_time;
	cs_data->batt_stat_saved_time = cs_data->event_boot_time;

	cs_data->lrc_enabled = false;
	cs_data->lrc_operation = LRC_OP_CHARGING;

	if (cfg_param[CID_BATTMAN_LOG_INTERVAL].valid)
		cs_data->bmlog_interval = cfg_param[CID_BATTMAN_LOG_INTERVAL].intval;
	else
		cs_data->bmlog_interval = -1;

	if (cfg_param[CID_BATTMAN_LOG_CATEGORIES0].valid || cfg_param[CID_BATTMAN_LOG_CATEGORIES1].valid ||
			cfg_param[CID_BATTMAN_LOG_CATEGORIES2].valid || cfg_param[CID_BATTMAN_LOG_CATEGORIES3].valid)
		snprintf(cs_data->bmlog_categories, sizeof(cs_data->bmlog_categories), "0x%04x%04x%04x%04x\n",
			cfg_param[CID_BATTMAN_LOG_CATEGORIES3].valid ? (cfg_param[CID_BATTMAN_LOG_CATEGORIES3].intval & 0xffff) : 0,
			cfg_param[CID_BATTMAN_LOG_CATEGORIES2].valid ? (cfg_param[CID_BATTMAN_LOG_CATEGORIES2].intval & 0xffff) : 0,
			cfg_param[CID_BATTMAN_LOG_CATEGORIES1].valid ? (cfg_param[CID_BATTMAN_LOG_CATEGORIES1].intval & 0xffff) : 0,
			cfg_param[CID_BATTMAN_LOG_CATEGORIES0].valid ? (cfg_param[CID_BATTMAN_LOG_CATEGORIES0].intval & 0xffff) : 0);
	else
		strlcpy(cs_data->bmlog_categories, "", sizeof(cs_data->bmlog_categories));

	if (cfg_param[CID_BATTMAN_LOG_LEVEL].valid)
		cs_data->bmlog_level = cfg_param[CID_BATTMAN_LOG_LEVEL].intval;
	else
		cs_data->bmlog_level = -1;

	if (cfg_param[CID_BATTLOG_WITH_ALL_EVENTS].valid && cfg_param[CID_BATTLOG_WITH_ALL_EVENTS].intval)
		cs_data->battlog_with_all_events = true;
	else
		cs_data->battlog_with_all_events = false;

#ifdef BUILD_VARIANT_NOT_USER
	init_battery_log_params(cs_data, cfg_param);
#endif

	property_get("ro.product.vendor.model", cs_data->product_name, "");
}

#define WAKELOCK_LOCK_NODE   "/sys/power/wake_lock"
#define WAKELOCK_UNLOCK_NODE "/sys/power/wake_unlock"

static void power_wake_lock(const char *tag, bool lock)
{
	const char *node = lock ? WAKELOCK_LOCK_NODE : WAKELOCK_UNLOCK_NODE;
	int fd;

	fd = open(node, O_WRONLY | O_APPEND | O_NONBLOCK);
	if (fd < 0) {
		LOG("Unable to open: '%s'", node);
		return;
	}
	write(fd, tag, strlen(tag));
	close(fd);
}

static void update_event_time(struct cs_data_t *cs_data)
{
	struct timespec boot_time;

	cs_data->event_system_time = time(NULL);

	if (clock_gettime(CLOCK_BOOTTIME, &boot_time) != -1)
		cs_data->event_boot_time = boot_time.tv_sec;
}

static bool is_loaded_battery_profile(const struct sysfs_param_t *sysfs_param)
{
	if ((sysfs_param[SFID_BATT_TYPE].intval != BATT_TYPE_UNKNOWN) &&
			(sysfs_param[SFID_BATT_TYPE].intval != BATT_TYPE_LOADING) &&
			(sysfs_param[SFID_CHARGE_FULL_DESIGN].intval > 0))
		return true;

	return false;
}

static void do_event_process(
	const char *event_name,
	struct cs_data_t *cs_data,
	struct batt_stat_t *batt_stat,
	struct chg_insertion_removal_data_t *chg_in_rm_data)
{
	struct sysfs_param_t sysfs_param[NUM_SFIDS];
	bool sysfs_param_enabled[NUM_SFIDS];
	int i;

	update_event_time(cs_data);

	if (is_periodic_event(event_name)) {
		for (i = 0; i < NUM_SFIDS; i++) {
			switch (i) {
			case SFID_SDM_THERM:
			case SFID_THERMAL_ZONE_SDM_THERM:
				sysfs_param_enabled[i] = true;
				break;
			default:
				sysfs_param_enabled[i] = false;
			}
		}
	} else {
		for (i = 0; i < NUM_SFIDS; i++)
			sysfs_param_enabled[i] = true;
	}

	read_sysfs_params(sysfs_param, sysfs_param_enabled);

#ifdef BUILD_VARIANT_NOT_USER
	if (!is_periodic_event(event_name) || cs_data->battlog_with_all_events)
		output_battery_log(cs_data, sysfs_param, event_name);
#endif
	if (is_periodic_event(event_name)) {
		provide_external_thermal_data(cs_data, sysfs_param);
	} else {
		if (cs_data->lrc_enabled)
			control_lrc_mode(cs_data, sysfs_param);

		if (is_loaded_battery_profile(sysfs_param)) {
			update_batt_stat(cs_data, batt_stat, sysfs_param);

			if (!cs_data->initial_control_completed) {
				set_restored_capacity(cs_data, batt_stat, sysfs_param);
				cs_data->initial_control_completed = true;
			}
			control_soft_charge(cs_data, batt_stat, sysfs_param);
			update_batt_stat_after_control(cs_data, batt_stat);
		}
		set_chg_insertion_removal_data(cs_data, sysfs_param, chg_in_rm_data);

#ifdef USE_IDD
		if (can_send_idd_batt_degr2(cs_data, batt_stat))
			send_idd_batt_degr2(cs_data, batt_stat);

		if (can_send_idd_chg_insertion_removal(cs_data, chg_in_rm_data, sysfs_param))
			send_idd_chg_insertion_removal(cs_data, chg_in_rm_data);
#endif

		if (can_save_batt_stat(cs_data, sysfs_param, batt_stat))
			save_batt_stat(cs_data, batt_stat);
	}

	cleanup_sysfs_params(sysfs_param);
}

void set_bmdbg(struct cs_data_t *cs_data) {
	struct sysfs_param_t sysfs_value;

	if (cs_data->regupdate_interval >= 0) {
		sysfs_value.intval = cs_data->regupdate_interval;
		sysfs_value.val_type = SYSFS_PARAM_VAL_INT;
		write_sysfs_param(SFID_REGUPDATE_INTERVAL, &sysfs_value);
	}

	if (cs_data->bmlog_interval >= 0) {
		sysfs_value.intval = cs_data->bmlog_interval;
		sysfs_value.val_type = SYSFS_PARAM_VAL_INT;
		write_sysfs_param(SFID_BMLOG_INTERVAL, &sysfs_value);
	}

	if (strlen(cs_data->bmlog_categories) > 0) {
		sysfs_value.strval = cs_data->bmlog_categories;
		sysfs_value.val_type = SYSFS_PARAM_VAL_STR;
		write_sysfs_param(SFID_BMLOG_CATEGORIES, &sysfs_value);
	}

	if (cs_data->bmlog_level >= 0) {
		sysfs_value.intval = cs_data->bmlog_level;
		sysfs_value.val_type = SYSFS_PARAM_VAL_INT;
		write_sysfs_param(SFID_BMLOG_LEVEL, &sysfs_value);
	}
}

#define WAKELOCK_TAG           "charge-service-wakelock"
#define PERMANENT_WAKELOCK_TAG "charge-service-permanent-wakelock"

int main(int argc, char *argv[])
{
	int uevent_sock = -1;
	char event_name[EVENT_NAME_SIZE];
	static struct cs_data_t cs_data;
	static struct batt_stat_t batt_stat;
	static struct chg_insertion_removal_data_t chg_in_rm_data;

	UNUSED(argc);
	UNUSED(argv);

	LOGD("--- start charge-service ---\n");

	/* create uevent socket */
	if (create_uevent_socket(&uevent_sock) != 0) {
		LOG("cannot create uevent socket, abort charge-service\n");
		return 0;
	}

	/* initialize data */
	init_cs_data(&cs_data);
	init_batt_stat(&cs_data, &batt_stat);

	/* handle MiscTA */
	handle_miscta(&cs_data);

#ifdef BUILD_VARIANT_NOT_USER
	if (cs_data.stay_awake)
		power_wake_lock(PERMANENT_WAKELOCK_TAG, true);

	set_bmdbg(&cs_data);
#endif

	/* charge service main loop */
	while (1) {
		if (wait_for_uevent(uevent_sock, cs_data.periodic_event_interval, event_name) < 0)
			break;

		power_wake_lock(WAKELOCK_TAG, true);
		do_event_process(event_name, &cs_data, &batt_stat, &chg_in_rm_data);
		power_wake_lock(WAKELOCK_TAG, false);
	}
#ifdef BUILD_VARIANT_NOT_USER
	if (cs_data.stay_awake)
		power_wake_lock(PERMANENT_WAKELOCK_TAG, false);
#endif

	cleanup_uevent_socket(uevent_sock);

	LOGD("--- end charge-service ---\n");
	return 0;
}
