/*
 * Copyright (C) 2011 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <dirent.h>
#include <fcntl.h>
#include <linux/usb/f_accessory.h>
#include <linux/input.h>
#include <cutils/properties.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

#include "log.h"
#include "utils.h"

#define BITSIZE_LONG (sizeof(long) * 8)
#define NBR_OF_BITS(x) ((((x)-1) / BITSIZE_LONG) + 1)
#define OFF(x) ((x)%BITSIZE_LONG)
#define GET_BIT(x) (1UL<<OFF(x))
#define LONG(x) ((x) / BITSIZE_LONG)
#define is_set(bit, array) ((array[LONG(bit)] >> OFF(bit)) & 1)
#define BUF_SIZE 512

#define OPEN_ERROR -1
#define MEM_ERROR -2
#define READ_ERROR -3
#define RADIX 16
#define MAX_STR 255
#define STRING_MAX_LEN 32

#define USB_CONFIG_ERROR -1
#define USB_FUNCTION_UNLINK_ERROR -2
#define USB_PRODUCT_ERROR -3
#define USB_VENDOR_ERROR -4
#define USB_SYMLINK_ERROR -5
#define USB_CONTROLLER_ERROR -6
#define USB_STATE_ERROR -7
#define USB_OS_DESC_USE_ERROR -8

#define EVENT_BUFFER 64
#define EVENT_SIZE 2

#define DEV_USB_ACCESSORY "/dev/usb_accessory"
#define DEV_INPUT_EVENT "/dev/input/event%d"
#define POWER_SUPPLY_PATH "/sys/class/power_supply/"
#define CAPACITY_PATH "/sys/class/power_supply/%s/capacity"
#define ONLINE_PATH "/sys/class/power_supply/%s/online"
#define STATUS_PATH "/sys/class/power_supply/%s/status"
#define HEALTH_PATH "/sys/class/power_supply/%s/health"
#define PRESENT_PATH "/sys/class/power_supply/%s/present"
#define BATTERY_TYPE_PATH "/sys/class/power_supply/%s/battery_type"
#define USB_TYPE_PATH "/sys/class/qcom-battery/usb_real_type"
#define USB_STATE_PATH "/sys/class/android_usb/android0/state"

#define TYPE_PATH "/sys/class/power_supply/%s/type"

#define LOG_CHARGEMON "Can't open:"

#define USB_FUNCTION_CNT 6
#define USB_TYPE_LOOP_CNT	3
#define DELAY_USB_TYPE_FIX	1

#define FAILED_USB_CONFIG_PATH LOG_CHARGEMON USB_CONFIG_PATH "\n"
#define FAILED_USB_PRODUCT_ID_PATH LOG_CHARGEMON USB_PRODUCT_ID_PATH "\n"
#define FAILED_USB_VENDOR_ID_PATH LOG_CHARGEMON USB_VENDOR_ID_PATH "\n"
#define FAILED_POWER_SUPPLY_PATH LOG_CHARGEMON POWER_SUPPLY_PATH "!?!?!\n"
#define FAILED_USB_CONTROLLER_PATH LOG_CHARGEMON USB_CONTROLLER_PATH "\n"
#define FAILED_USB_OS_DESC_USE LOG_CHARGEMON USB_OS_DESC_USE_PATH "\n"
#define FAILED_USB_STATE "Failed to set property" USB_STATE_PROP_KEY "\n"
#define FAILED_USB_SYMLINK "Failed to symlink\n"

#ifndef EVIOCSSUSPENDBLOCK
    // uapi headers don't include EVIOCSSUSPENDBLOCK, and future kernels
    // will use an epoll flag instead, so as long as we want to support
    // this feature, we need to be prepared to define the ioctl ourselves.
#define EVIOCSSUSPENDBLOCK _IOW('E', 0x91, int)
#endif

/*
 * Locates the /dev/input/event
 * file that deals with keys that shall wake up phone
 * Returns the number devices set,
 * not the complete filename or fd.
 */
int utils_findKeyEvents(int *inputfds, int max)
{
	int fd;
	int i;
	int res = 0;
	char buf[EVENT_BUFFER];
	long events[EVENT_SIZE][NBR_OF_BITS(KEY_MAX)];

	for (i = 0; res < max; i++) {
		snprintf(buf, sizeof(buf), DEV_INPUT_EVENT, i);
		fd = open(buf, O_RDONLY);
		if (fd < 0)
			break;

		LOGD("Check event device (%s)\n", buf);

		/* Figure out the events it supports */
		if (ioctl(fd, EVIOCGBIT(0, EV_MAX), events[0]) < 0) {
			close(fd);
			LOGD("This event device is not used\n");
			continue;
		}

		if (is_set(EV_KEY, events[0])) {
			if (ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(events[1])),
				events[1]) < 0) {
				close(fd);
				LOGD("This event device is not used\n");
				continue;
			}
			if (is_set(KEY_POWER, events[1]) ||
				is_set(KEY_END, events[1]) ||
				is_set(KEY_MENU, events[1]) ||
				is_set(KEY_BACK, events[1]) ||
				is_set(KEY_HOME, events[1]) ||
				is_set(KEY_SEARCH, events[1]) ||
				is_set(KEY_F24, events[1])) {

				/*
				 * say to hold wakelock, till read out
				 */
				if (ioctl(fd, EVIOCSSUSPENDBLOCK, 1))
					LOGD("This event device not support EVIOCSSUSPENDBLOCK\n");

				inputfds[res++] = fd;
				LOGD("This event device is retained\n");
				continue;
			} else {
				LOGD("This event device is not used\n");
			}
		} else {
			LOGD("This event device is not used\n");
		}
		close(fd);
	}

	return res;
}


int IsConnectionTypeUSB(void)
{
	FILE *fp;
	int i, len;
	char usbtype[MAX_PATH];

	for (i = 0; i < USB_TYPE_LOOP_CNT; i++) {
		fp = fopen(USB_TYPE_PATH, "r");
		if (fp == NULL) {
			LOG("could not open usb type");
			return 0;
		}

		len = fread(usbtype, sizeof(char), MAX_PATH - 1, fp);
		fclose(fp);

		if (len <= 0)
			return 0;
		usbtype[len] = '\0';
		if (strncmp(usbtype, "Unknown\n", MAX_PATH))
			break;
		sleep(DELAY_USB_TYPE_FIX);
	}

	if (strncmp(usbtype, "SDP\n", MAX_PATH) == 0)
		return 1;

	return 0;
}

int IsUsbConnected(void)
{
	int fd;
	char buf;

	fd = open(USB_STATE_PATH, O_RDONLY);
	if (fd < 0) {
		LOG("could not open usb state");
		return 0;
	}

	if (read(fd, &buf, 1) == -1) {
		LOG("could not read usb state");
	}
	close(fd);

	/* CONNECTED or CONFIGURED */
	if (buf == 'C')
		return 1;

	return 0;
}

#define IGNORED_DIR_PATH "bms"

/* Looks for the battery in /sys/class/power_supply */
const char *utils_findBatteryFile(void)
{
	FILE *test;
	DIR  *psdir;
	struct dirent *de;
	static char tmpStr[MAX_STR + 1];

	psdir = opendir(POWER_SUPPLY_PATH);
	if (psdir == NULL) {
		LOG(FAILED_POWER_SUPPLY_PATH);
		return NULL;
	}

	de = readdir(psdir);
	while (de != NULL) {
		LOGD("BT: Trying %s\n", de->d_name);
		if (de->d_name[0] != '.' &&
			strncmp(de->d_name, IGNORED_DIR_PATH,
				sizeof(de->d_name))) {
			snprintf(tmpStr, sizeof(tmpStr), CAPACITY_PATH,
				de->d_name);
			LOGD("** Trying file %s\n", tmpStr);
			test = fopen(tmpStr, "rb");
			if (test != NULL) {
				fclose(test);
				closedir(psdir);
				LOGD("Found it!!!\n");
				return tmpStr;
			}
		}
		de = readdir(psdir);
	}
	LOGD("BT: Couldn't find a single file\n");
	closedir(psdir);
	return NULL;
}

/*
 * Looks for the charger in /sys/class/power_supply
 * Returns the first one that is online
 */
#define IGNORED_ONLINE_PATH "/sys/class/power_supply/battery/online"

const char *utils_findOnlineFile(void)
{
	FILE *test;
	DIR  *psdir;
	struct dirent *de;
	static char tmpStr[MAX_STR + 1];

	psdir = opendir(POWER_SUPPLY_PATH);
	if (psdir == NULL) {
		LOG(FAILED_POWER_SUPPLY_PATH);
		return NULL;
	}

	while ((de = readdir(psdir)) != NULL) {
		if (de->d_name[0] != '.' &&
			strncmp(de->d_name, IGNORED_DIR_PATH,
				sizeof(de->d_name))) {
			LOGD("BT: Trying %s\n", de->d_name);
			snprintf(tmpStr, sizeof(tmpStr),
				ONLINE_PATH,
				de->d_name);
			if (!strncmp(tmpStr, IGNORED_ONLINE_PATH,
				sizeof(tmpStr)))
				continue;
			LOGD("** Trying file %s\n", tmpStr);
			test = fopen(tmpStr, "rb");
			if (test != NULL) {
				int c = fgetc(test);
				fclose(test);
				if (c == '0')
					continue;
				closedir(psdir);
				LOGD("Found it!!!\n");
				return tmpStr;
			}
		}
	}
	LOGD("BT: Couldn't find a single file\n");
	closedir(psdir);
	return NULL;
}

/* Looks for the charger status in /sys/class/power_supply */
const char *utils_findStatusFile(void)
{
	FILE *test;
	DIR  *psdir;
	struct dirent *de;
	static char tmpStr[MAX_STR + 1];

	psdir = opendir(POWER_SUPPLY_PATH);
	if (psdir == NULL) {
		LOG(FAILED_POWER_SUPPLY_PATH);
		return NULL;
	}

	while ((de = readdir(psdir)) != NULL) {
		if (de->d_name[0] != '.' &&
			strncmp(de->d_name, IGNORED_DIR_PATH,
				sizeof(de->d_name))) {
			LOGD("BT: Trying %s\n", de->d_name);
			snprintf(tmpStr, sizeof(tmpStr),
				STATUS_PATH,
				de->d_name);
			LOGD("** Trying file %s\n", tmpStr);
			test = fopen(tmpStr, "rb");
			if (test != NULL) {
				fclose(test);
				closedir(psdir);
				LOGD("Found it!!!\n");
				return tmpStr;
			}
		}
	}
	LOGD("BT: Couldn't find a single file\n");
	closedir(psdir);
	return NULL;
}

static int utils_isPowerSupplyType(char *dir_name, const char *type_name)
{
	char path[MAX_STR + 1];
	char tmp[MAX_STR + 1];
	FILE *f;
	int ret = 0;

	snprintf(path, sizeof(path), TYPE_PATH, dir_name);
	memset(tmp, 0, sizeof(tmp));
	f = fopen(path, "r");
	if (f != NULL) {
		fgets(tmp, sizeof(tmp), f);
		fclose(f);
		ret = !strncmp(tmp, type_name, strlen(type_name));
	}
	return ret;
}

const char *utils_findHealthFile(void)
{
	FILE *test;
	DIR  *psdir;
	struct dirent *de;
	static char tmpStr[MAX_STR + 1];

	psdir = opendir(POWER_SUPPLY_PATH);
	if (psdir == NULL) {
		LOG(FAILED_POWER_SUPPLY_PATH);
		return NULL;
	}

	while ((de = readdir(psdir)) != NULL) {
		if (de->d_name[0] != '.' &&
			strncmp(de->d_name, IGNORED_DIR_PATH,
				sizeof(de->d_name))) {
			if (!utils_isPowerSupplyType(de->d_name, "Battery"))
				continue;
			LOGD("BT: Trying %s\n", de->d_name);
			snprintf(tmpStr, sizeof(tmpStr),
				HEALTH_PATH,
				de->d_name);
			LOGD("** Trying file %s\n", tmpStr);
			test = fopen(tmpStr, "rb");
			if (test != NULL) {
				fclose(test);
				closedir(psdir);
				LOGD("Found it!!!\n");
				return tmpStr;
			}
		}
	}
	LOGD("BT: Couldn't find a single file\n");
	closedir(psdir);
	return NULL;
}

/*
 * Looks for the charger in /sys/class/power_supply
 * Returns the first one that is present
 */
const char *utils_findPresentFile(void)
{
	FILE *test;
	DIR  *psdir;
	struct dirent *de;
	static char tmpStr[MAX_STR + 1];
	const char *batt_path;

	psdir = opendir(POWER_SUPPLY_PATH);
	if (psdir == NULL) {
		LOG(FAILED_POWER_SUPPLY_PATH);
		return NULL;
	}

	batt_path = utils_findBatteryFile();

	while ((de = readdir(psdir)) != NULL) {
		if (de->d_name[0] != '.' &&
			strncmp(de->d_name, IGNORED_DIR_PATH,
				sizeof(de->d_name))) {
			LOGD("BT: Trying %s\n", de->d_name);
			if (batt_path != NULL &&
				strstr(batt_path, de->d_name)) {
				LOGD("battery path is ignored\n");
				continue;
			}
			snprintf(tmpStr, sizeof(tmpStr),
				PRESENT_PATH,
				de->d_name);
			LOGD("** Trying file %s\n", tmpStr);
			test = fopen(tmpStr, "rb");
			if (test != NULL) {
				int c = fgetc(test);
				fclose(test);
				if (c == '0')
					continue;
				closedir(psdir);
				LOGD("Found it!!!\n");
				return tmpStr;
			}
		}
	}
	LOGD("BT: Couldn't find a single file\n");
	closedir(psdir);
	return NULL;
}

const char *utils_findBatteryType(void)
{
	FILE *test;
	DIR  *psdir;
	struct dirent *de;
	static char tmpStr[MAX_STR + 1];

	psdir = opendir(POWER_SUPPLY_PATH);
	if (psdir == NULL) {
		LOG(FAILED_POWER_SUPPLY_PATH);
		return NULL;
	}

	de = readdir(psdir);
	while (de != NULL) {
		LOGD("BT: Trying %s\n", de->d_name);
		if (de->d_name[0] != '.') {
			snprintf(tmpStr, sizeof(tmpStr), BATTERY_TYPE_PATH,
				de->d_name);
			LOGD("** Trying file %s\n", tmpStr);
			test = fopen(tmpStr, "rb");
			if (test != NULL) {
				fclose(test);
				closedir(psdir);
				LOGD("Found it!!!\n");
				return tmpStr;
			}
		}
		de = readdir(psdir);
	}
	LOGD("BT: Couldn't find a single file\n");
	closedir(psdir);
	return NULL;
}
