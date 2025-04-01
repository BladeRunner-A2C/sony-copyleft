/*********************************************************************
 * Copyright (c) 2016 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/

#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "miscta.h"
#include "miscta_units.h"

#include "log.h"
#include "record_timestamp.h"

#define MISCTA_MAJOR_VERSION	1
#define MISCTA_MINOR_VERSION	0
#define MISCTA_REVISON_VERSION	0

#define MISCTA_SIZE		208
#define REASON_TEXT_LEN		16
#define MEASUREMENT_TIMES_NUM	3

/* Depens-on: record_timestamp.h#end_reason */
const char *reason_table[] = {
	"Power ON.",
	"USB removal.",
};

typedef struct {
	uint64_t	start_charge_time;
	uint64_t	end_charge_time;
	uint8_t		end_reason[REASON_TEXT_LEN];
	uint8_t		reserved[32];
} time_data;

typedef struct {
	uint8_t		initialized;
	uint8_t		version[3];
	uint8_t		reserved[12];
	/* The timestamp is written in the last data[].					*/
	/* At the same time, the former timestamp is copied in the one before data[].	*/
	time_data	data[MEASUREMENT_TIMES_NUM];
} MiscTA_param;	/* Total 208 byte of MISC_DATA_SIZE */

static MiscTA_param power_off_charge_time;
static bool initialized_flag = false;

static bool write_miscta(MiscTA_param *inbuff) {

	miscta_status_t ret = miscta_write_unit(TA_RECORD_POWEROFF_CHARGE_STATUS, inbuff,
		MISCTA_SIZE);
	if (ret == MT_SUCCESS)
		return true;

	LOG("miscta_write_unit() is failure. Return value is %d\n", ret);
	return false;
}

static bool read_miscta(MiscTA_param *outbuff) {
	uint32_t size = MISCTA_SIZE;

	miscta_status_t ret = miscta_read_unit(TA_RECORD_POWEROFF_CHARGE_STATUS, outbuff, &size);
	if (ret == MT_SUCCESS && size == MISCTA_SIZE)
		return true;

	LOG("miscta_read_unit() is failure. Return value is %d. Size is %d\n", ret, size);
	return false;
}

static void reset_miscta() {
	memset(&power_off_charge_time, 0, sizeof(MiscTA_param));
	power_off_charge_time.initialized = 1;
	power_off_charge_time.version[0] = MISCTA_MAJOR_VERSION;
	power_off_charge_time.version[1] = MISCTA_MINOR_VERSION;
	power_off_charge_time.version[2] = MISCTA_REVISON_VERSION;
	write_miscta(&power_off_charge_time);
}

static void update_miscta() {
	/*
	 Add the initialize function for the additional field members
	 when update the MiscTA2583 version.
	*/
	reset_miscta();
}

void record_timestamp_init() {

	memset(&power_off_charge_time, 0, sizeof(MiscTA_param));
	if (read_miscta(&power_off_charge_time) == true) {
		if (power_off_charge_time.version[0] != MISCTA_MAJOR_VERSION) {
			reset_miscta();
		} else if (power_off_charge_time.version[1] != MISCTA_MINOR_VERSION
			|| power_off_charge_time.version[2] != MISCTA_REVISON_VERSION) {
			update_miscta();
		}
	} else {
		reset_miscta();
	}
	initialized_flag = true;
}

void record_timestamp_start() {

	int cnt_i;
	long time_sec;

	if (initialized_flag == false) {
		LOG("can't use record_timestamp_start, don't yet call record_timestamp_init");
		return;
	}

	if (time(&time_sec) == -1) {
		LOG("can't get the time on record_timestamp_start.");
		return;
	}

	for (cnt_i = 0; cnt_i < MEASUREMENT_TIMES_NUM; cnt_i++) {
		if((cnt_i + 1) == MEASUREMENT_TIMES_NUM) {
			power_off_charge_time.data[cnt_i].start_charge_time = time_sec;
			power_off_charge_time.data[cnt_i].end_charge_time = 0;
			memset(power_off_charge_time.data[cnt_i].end_reason, 0, REASON_TEXT_LEN);
		} else {
			memcpy(&power_off_charge_time.data[cnt_i],
				&power_off_charge_time.data[cnt_i + 1], sizeof(time_data));
		}
	}
	write_miscta(&power_off_charge_time);
}

void record_timestamp_end(end_reason reason) {

	long time_sec;

	if (initialized_flag == false) {
		LOG("can't use record_timestamp_end, don't yet call record_timestamp_init");
		return;
	}

	if (time(&time_sec) == -1) {
		LOG("can't get the time on record_timestamp_end.");
		return;
	}

	power_off_charge_time.data[(MEASUREMENT_TIMES_NUM - 1)].end_charge_time = time_sec;
	memset(power_off_charge_time.data[(MEASUREMENT_TIMES_NUM - 1)].end_reason, 0,
		REASON_TEXT_LEN);
	memcpy(power_off_charge_time.data[(MEASUREMENT_TIMES_NUM - 1)].end_reason,
		reason_table[reason], strlen(reason_table[reason]));
	write_miscta(&power_off_charge_time);
}
