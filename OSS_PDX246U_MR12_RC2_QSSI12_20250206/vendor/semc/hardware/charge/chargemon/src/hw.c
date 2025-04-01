/*
 * Copyright (c) 2014 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <unistd.h>

#include "hw.h"
#include "log.h"
#include "utils.h"
#include "display.h"

#define MAX_STR 255
#define BASE 10

#define POWER_STATE "/sys/power/state"
#define WAKELOCK_LOCK "/sys/power/wake_lock"
#define WAKELOCK_UNLOCK "/sys/power/wake_unlock"
#define LOG_TAG "chargemon"

#define BACKLIGHT_BRIGHTNESS_LEVEL 127
#define BACKLIGHT_INVALID_VALUE 0
#define BACKLIGHT_DEVICE_PATH "/sys/class/backlight/panel0-backlight/brightness"
#define BACKLIGHT_MAX_BRIGHTNESS_PATH "/sys/class/backlight/panel0-backlight/max_brightness"

#define LED_R_DEVICE_PATH "/sys/class/leds/red/brightness"
#define LED_G_DEVICE_PATH "/sys/class/leds/green/brightness"
#define LED_B_DEVICE_PATH "/sys/class/leds/blue/brightness"
#define LED_R_MAX_BRIGHTNESS_PATH "/sys/class/leds/red/max_brightness"
#define LED_G_MAX_BRIGHTNESS_PATH "/sys/class/leds/green/max_brightness"
#define LED_B_MAX_BRIGHTNESS_PATH "/sys/class/leds/blue/max_brightness"

#define BACKLIGHT_DECREASE_INTERVAL_MS 20
#define BACKLIGHT_DECREASE_STEP 40

#define MAX_INPUT_DEVICES 10
#define LONG_PRESS_TIME 2

#define CAPACITY_THRESHOLD_LOW_LED 14
#define CAPACITY_THRESHOLD_MEDIUM_LED 90

#define KEY_EVENT_ERR -1
#define GET_BATTERYCAPACITY_ERR -1

#define DELIM ";"

#define MEMO_CLEAR -1

#define LOCAL_ARRAY_SIZE(x) (int)(sizeof(x) / sizeof((x)[0]))

static int inputfds[MAX_INPUT_DEVICES];
static char *capfile;
static char *chargestatus;
static char *chargehealth;
static char *batterytype;

const char *batt_charge_status[] = {
	"Unknown",
	"Charging",
	"Discharging",
	"Not charging",
	"Full"
};

const char *batt_charge_health[] = {
	"Unknown",
	"Good",
	"Overheat",
	"Dead",
	"Over voltage",
	"Unspecified failure",
	"Cold"
};

const char *battery_type[] = {
	"Unknown Battery",
	"Loading Battery Data",
	"Disconnected Battery",
};

static char *hw_readSysfs(char *sysfs)
{
	FILE *f;
	char tmp[MAX_STR + 1];
	memset(tmp, 0, sizeof(tmp));
	f = fopen(sysfs, "r");
	if (f != NULL) {
		fgets(tmp, sizeof(tmp), f);
		fclose(f);
	}
	return strdup(tmp);
}

static void hw_writeSysfs(char *sysfs, char *str)
{
	FILE *f;
	f = fopen(sysfs, "w");
	if (f != NULL) {
		fputs(str, f);
		fclose(f);
	}
}

enum {
	DISCHARING,
	LOW,
	MEDIUM,
	HIGH,
	LEVEL_MAX,
};

enum {
	RED,
	GREEN,
	BLUE,
	COLOR_MAX,
};

static int RGB_color[LEVEL_MAX][COLOR_MAX];
#define MAX_BRIGHTNESS		0xFF
/* Same value as "config_notificationsBatteryLowARGB" */
#define RGB_LOW_R		0xFF
#define RGB_LOW_G		0
#define RGB_LOW_B		0
/* Same value as "config_notificationsBatteryMediumARGB" */
#define RGB_MEDIUM_R		0xFF
#define RGB_MEDIUM_G		0x30
#define RGB_MEDIUM_B		0
/* Default value is same value as "config_notificationsBatteryFullARGB" */
#define RGB_HIGH_R		0
#define RGB_HIGH_G		0x7F
#define RGB_HIGH_B		0

static void hw_setupRGBLedColor(void)
{
	char *max_brightness_str;
	int max_brightness;
	int i, j;

	max_brightness_str = hw_readSysfs(LED_R_MAX_BRIGHTNESS_PATH);
	if (max_brightness_str == NULL)
		goto error_read;
	max_brightness = atoi(max_brightness_str);
	RGB_color[LOW][RED] =
		max_brightness * RGB_LOW_R    / MAX_BRIGHTNESS;
	RGB_color[MEDIUM][RED] =
		max_brightness * RGB_MEDIUM_R / MAX_BRIGHTNESS;
	RGB_color[HIGH][RED] =
		max_brightness * RGB_HIGH_R   / MAX_BRIGHTNESS;
	free(max_brightness_str);

	max_brightness_str = hw_readSysfs(LED_G_MAX_BRIGHTNESS_PATH);
	if (max_brightness_str == NULL)
		goto error_read;
	max_brightness = atoi(max_brightness_str);
	RGB_color[LOW][GREEN] =
		max_brightness * RGB_LOW_G    / MAX_BRIGHTNESS;
	RGB_color[MEDIUM][GREEN] =
		max_brightness * RGB_MEDIUM_G / MAX_BRIGHTNESS;
	RGB_color[HIGH][GREEN] =
		max_brightness * RGB_HIGH_G   / MAX_BRIGHTNESS;
	free(max_brightness_str);

	max_brightness_str = hw_readSysfs(LED_B_MAX_BRIGHTNESS_PATH);
	if (max_brightness_str == NULL)
		goto error_read;
	max_brightness = atoi(max_brightness_str);
	RGB_color[LOW][BLUE] =
		max_brightness * RGB_LOW_B    / MAX_BRIGHTNESS;
	RGB_color[MEDIUM][BLUE] =
		max_brightness * RGB_MEDIUM_B / MAX_BRIGHTNESS;
	RGB_color[HIGH][BLUE] =
		max_brightness * RGB_HIGH_B   / MAX_BRIGHTNESS;
	free(max_brightness_str);

	LOGD("LOW: R=%d G=%d B=%d\n",
		RGB_color[LOW][RED],
		RGB_color[LOW][GREEN],
		RGB_color[LOW][BLUE]);
	LOGD("MEDIUM: R=%d G=%d B=%d\n",
		RGB_color[MEDIUM][RED],
		RGB_color[MEDIUM][GREEN],
		RGB_color[MEDIUM][BLUE]);
	LOGD("HIGH: R=%d G=%d B=%d\n",
		RGB_color[HIGH][RED],
		RGB_color[HIGH][GREEN],
		RGB_color[HIGH][BLUE]);
	return;

error_read:
	for (i = 0; i < LEVEL_MAX; i++) {
		for (j = 0; j < COLOR_MAX; j++) {
			RGB_color[i][j] = 0;
		}
	}
}

#define VIBRATOR_PLAY_MODE_PATH	"/sys/class/leds/vibrator/play_mode"
#define VIBRATOR_DURATION_PATH	"/sys/class/leds/vibrator/duration"
#define VIBRATOR_ACTIVATE_PATH	"/sys/class/leds/vibrator/activate"
#define INPUT_DEV_PATH		"/dev/input/"
#define VIBRATION_MAGNITUDE	0x7fff
#define test_bit(bit, array)	((array)[(bit) / 8] & (1 << ((bit) % 8)))

#define VIBRATION_MODE_SYSFS1	0
#define VIBRATION_MODE_SYSFS2	1
#define VIBRATION_MODE_IOCTL	2
#define VIBRATION_MODE_UNKNOWN	-1

static int vibration_mode = VIBRATION_MODE_UNKNOWN;
static char vibration_ioctl_path[PATH_MAX];

static int hw_vibration_init()
{
	struct stat s;
	DIR *dp;
	struct dirent *dir;
	uint8_t ff_bitmask[FF_CNT / 8];
	int fd;
	bool ioctl_found = false;

	if (!stat(VIBRATOR_PLAY_MODE_PATH, &s)) {
		vibration_mode = VIBRATION_MODE_SYSFS1;
		return 0;
	}

	if (!stat(VIBRATOR_DURATION_PATH, &s)) {
		vibration_mode = VIBRATION_MODE_SYSFS2;
		return 0;
	}

	dp = opendir(INPUT_DEV_PATH);
	if (!dp) {
		LOG("open %s failed, errno = %d", INPUT_DEV_PATH, errno);
		return -1;
	}

	memset(ff_bitmask, 0, sizeof(ff_bitmask));
	while (!ioctl_found && (dir = readdir(dp)) != NULL) {
		if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
			continue;

		snprintf(vibration_ioctl_path, PATH_MAX, "%s%s", INPUT_DEV_PATH, dir->d_name);
		fd = open(vibration_ioctl_path, O_RDWR);
		if (fd < 0) {
			LOG("open %s failed, errno = %d", vibration_ioctl_path, errno);
			continue;
		}

		if (ioctl(fd, EVIOCGBIT(EV_FF, sizeof(ff_bitmask)), ff_bitmask) != -1) {
			if (test_bit(FF_CONSTANT, ff_bitmask) || test_bit(FF_PERIODIC, ff_bitmask))
				ioctl_found = true;
		}
		close(fd);
	}
	closedir(dp);

	if (ioctl_found) {
		vibration_mode = VIBRATION_MODE_IOCTL;
		return 0;
	}

	return -1;
}

int hw_init(void)
{
	const char *fname;
	memset(inputfds, MEMO_CLEAR, sizeof(inputfds));

	if (!utils_findKeyEvents(inputfds, MAX_INPUT_DEVICES))
		return KEY_EVENT_ERR;

	fname = utils_findBatteryFile();
	LOGD("Battery capacity filename: %s\n", fname);
	if (fname != NULL)
		capfile = strdup(fname);

	hw_setupRGBLedColor();

	if (hw_vibration_init() < 0)
		LOG("hw_vibration_init failed, vibration does not work\n");

	return 0;
}

void hw_vibrate(int time_ms)
{
	FILE *f;
	struct ff_effect effect;
	struct input_event play;
	int fd = 0;
	int ret;

	switch (vibration_mode) {
	case VIBRATION_MODE_SYSFS1:
		f = fopen(VIBRATOR_PLAY_MODE_PATH, "w");
		if (f != NULL) {
			fprintf(f, "%s\n", "direct");
			fclose(f);
		} else {
			return;
		}

		f = fopen(VIBRATOR_DURATION_PATH, "w");
		if (f != NULL) {
			fprintf(f, "%d\n", time_ms);
			fclose(f);
		} else {
			return;
		}

		f = fopen(VIBRATOR_ACTIVATE_PATH, "w");
		if (f != NULL) {
			fprintf(f, "%d\n", 1);
			fclose(f);
		} else {
			return;
		}

		usleep((time_ms + 5) * 1000);
		f = fopen(VIBRATOR_PLAY_MODE_PATH, "w");
		if (f != NULL) {
			fprintf(f, "%s\n", "audio");
			fclose(f);
		} else {
			return;
		}
		break;

	case VIBRATION_MODE_SYSFS2:
		f = fopen(VIBRATOR_DURATION_PATH, "w");
		if (f != NULL) {
			fprintf(f, "%d\n", time_ms);
			fclose(f);
		} else {
			return;
		}

		f = fopen(VIBRATOR_ACTIVATE_PATH, "w");
		if (f != NULL) {
			fprintf(f, "%d\n", 1);
			fclose(f);
		} else {
			return;
		}

		usleep((time_ms + 5) * 1000);
		f = fopen(VIBRATOR_ACTIVATE_PATH, "w");
		if (f != NULL) {
			fprintf(f, "%d\n", 0);
			fclose(f);
		} else {
			return;
		}
		break;

	case VIBRATION_MODE_IOCTL:
		fd = open(vibration_ioctl_path, O_RDWR);
		if (fd < 0) {
			LOG("open %s failed, errno = %d", vibration_ioctl_path, errno);
			return;
		}

		effect.type = FF_CONSTANT;
		effect.u.constant.level = VIBRATION_MAGNITUDE;
		effect.replay.length = time_ms;
		effect.id = -1;
		effect.replay.delay = 0;
		ret = ioctl(fd, EVIOCSFF, &effect);
		if (ret == -1) {
			LOG("ioctl EVIOCSFF failed, errno = %d", -errno);
			close(fd);
			return;
		}

		play.value = 1;
		play.type = EV_FF;
		play.code = 0;
		play.time.tv_sec = 0;
		play.time.tv_usec = 0;
		ret = write(fd, (const void*)&play, sizeof(play));
		if (ret == -1) {
			LOG("write failed, errno = %d", -errno);
			close(fd);
			return;
		}
		usleep((time_ms + 5) * 1000);
		close(fd);
		break;

	default:
		break;
	}
}

#define SPEC_BATTERY_LEVEL_LED_COLORS ""

void hw_setRGBled(int on, int capacity)
{
	FILE *f;
	static int last_red = 0;
	static int last_green = 0;
	static int last_blue = 0;
	static int init = -1;
	int err = 0;
	int low_level_thresh = CAPACITY_THRESHOLD_LOW_LED;
	int medium_level_thresh = CAPACITY_THRESHOLD_MEDIUM_LED;
	int level;

	char tokens[MAX_STR];
	strncpy(tokens, SPEC_BATTERY_LEVEL_LED_COLORS, MAX_STR);
	char *str = strtok(tokens, ", ");
	if (str != NULL)
		low_level_thresh = atoi(str);
	str = strtok(NULL, ", ");
	if (str != NULL)
		medium_level_thresh = atoi(str);
	LOGD("LED color battery level thresh: low=%d medium=%d\n",
		low_level_thresh, medium_level_thresh);

	if (on) {
		if (capacity <= low_level_thresh)
			level = LOW;
		else if (capacity < medium_level_thresh)
			level = MEDIUM;
		else
			level = HIGH;
	} else {
		level = DISCHARING;
	}

	if (-1 != init
		&& last_red   == RGB_color[level][RED]
		&& last_green == RGB_color[level][GREEN]
		&& last_blue  == RGB_color[level][BLUE])
		return;

	if (-1 == init)
		init = 0;

	LOGD("Changing LED color, level=%d R=%d G=%d B=%d\n",
				level, RGB_color[level][RED],
				RGB_color[level][GREEN],
				RGB_color[level][BLUE]);

	f = fopen(LED_R_DEVICE_PATH, "w");
	if (f != NULL) {
		fprintf(f, "%d\n", RGB_color[level][RED]);
		fclose(f);
	} else {
		err++;
	}

	f = fopen(LED_G_DEVICE_PATH, "w");
	if (f != NULL) {
		fprintf(f, "%d\n", RGB_color[level][GREEN]);
		fclose(f);
	} else {
		err++;
	}

	f = fopen(LED_B_DEVICE_PATH, "w");
	if (f != NULL) {
		fprintf(f, "%d\n", RGB_color[level][BLUE]);
		fclose(f);
	} else {
		err++;
	}

	if (!err) {
		last_red   = RGB_color[level][RED];
		last_green = RGB_color[level][GREEN];
		last_blue  = RGB_color[level][BLUE];
	}
}

static int hw_getBacklight(void)
{
	char *path_all;
	char *path;
	unsigned int buff_len;
	char *buf = NULL;
	int backlight = 0;

	buff_len = strnlen(BACKLIGHT_DEVICE_PATH, MAX_STR) + 1;
	path_all = malloc(buff_len);
	if (path_all == NULL) {
		LOG("hw_getBacklight: malloc error\n");
		return 0;
	}

	strlcpy(path_all, BACKLIGHT_DEVICE_PATH, buff_len);

	path = strtok(path_all, DELIM);
	if (path == NULL) {
		LOG("hw_getBacklight: strtok error\n");
		return 0;
	}
	buf = hw_readSysfs(path);

	free(path_all);
	if (buf == NULL)
		return 0;

	backlight = atoi(buf);
	free(buf);
	return backlight;
}

static int hw_getBacklightMaxBrightness(void)
{
	char *max_brightness_str;
	int max_brightness;

	max_brightness_str = hw_readSysfs(BACKLIGHT_MAX_BRIGHTNESS_PATH);
	if (max_brightness_str == NULL)
		return BACKLIGHT_INVALID_VALUE;

	max_brightness = atoi(max_brightness_str) *
				BACKLIGHT_BRIGHTNESS_LEVEL / MAX_BRIGHTNESS;
	LOGD("Backlight brightness: %d\n", max_brightness);
	free(max_brightness_str);

	return max_brightness;
}

static int _hw_setBacklight(unsigned int backlight)
{
	FILE *fp;
	int written = -1;
	char *path_all;
	char *path;
	unsigned int buff_len;

	buff_len = strnlen(BACKLIGHT_DEVICE_PATH, MAX_STR) + 1;
	path_all = malloc(buff_len);
	if (path_all == NULL) {
		LOG("hw_setBacklight: malloc error\n");
		return written;
	}

	strlcpy(path_all, BACKLIGHT_DEVICE_PATH, buff_len);

	path = path_all;
	while ((path = strtok(path, DELIM)) != NULL) {
		fp = fopen(path, "w");

		if (fp != NULL) {
			written = fprintf(fp, "%d\n", backlight);
			fclose(fp);
		}
		if (written <= 0)
			LOG("Failed to set backlight [%s]\n", path);

		path = NULL;
	}
	free(path_all);
	return written;
}

int hw_setBacklight(int on)
{
	int i;
	int ret = 0;
	int set_backlight;
	int current_backlight;
	int target_backlight;
	static int backlight_max_brightness = BACKLIGHT_INVALID_VALUE;

	if (backlight_max_brightness == BACKLIGHT_INVALID_VALUE) {
		backlight_max_brightness = hw_getBacklightMaxBrightness();
		if (backlight_max_brightness == BACKLIGHT_INVALID_VALUE)
			return ret;
	}

	if (on)
		target_backlight = backlight_max_brightness;
	else
		target_backlight = 0;

	current_backlight = hw_getBacklight();
	/* When turn off or darken, decrease brightness very slowly. */
	if (current_backlight == target_backlight) {
		return ret;
	} else if (current_backlight < target_backlight) {
		ret = _hw_setBacklight(target_backlight);
	} else {
		if (current_backlight > 2 * target_backlight) {
			set_backlight = current_backlight / 2;
			ret = _hw_setBacklight(set_backlight);
			usleep(BACKLIGHT_DECREASE_INTERVAL_MS * 1000);
			current_backlight = set_backlight;
		}
		for (i = 1; i <= BACKLIGHT_DECREASE_STEP; i++) {
			set_backlight = current_backlight
				- i * (current_backlight - target_backlight) /
							BACKLIGHT_DECREASE_STEP;
			ret = _hw_setBacklight(set_backlight);
			usleep(BACKLIGHT_DECREASE_INTERVAL_MS * 1000);
		}
	}
	return ret;
}

enum chargemon_event_t hw_waitForUserAction(int timeout)
{
	fd_set listen;
	int i, max_fd = -1;
	struct timeval delay = {0, 0};
	struct input_event event;
	enum chargemon_event_t ev;
	int rv;

	FD_ZERO(&listen);
	delay.tv_sec  = timeout / 1000;
	delay.tv_usec = (timeout - delay.tv_sec * 1000) * 1000;

	for (i = 0; i < MAX_INPUT_DEVICES && inputfds[i] >= 0; i++) {
		FD_SET(inputfds[i], &listen);

		if (inputfds[i] > max_fd)
			max_fd = inputfds[i];
	}

	if (max_fd >= 0) {
		hw_wakeUnlock();
		i = select(max_fd + 1, &listen, NULL, NULL, &delay);
		hw_wakeLock();

		/* select() broke or other error. Exit.. */
		if (i < 0)
			return CHARGEMON_ACTION_ERR;

		if (i == 0)
			goto action_timeout;
	} else {
		goto action_timeout;
	}

	for (i = 0; i < MAX_INPUT_DEVICES && inputfds[i] >= 0; i++) {
		if (!FD_ISSET(inputfds[i], &listen))
			continue;

		rv = read(inputfds[i], &event, sizeof(event));
		if (rv != sizeof(event))
			continue;

		ev = CHARGEMON_ACTION_NONE;

		if (event.type == EV_KEY) {
			if (event.code == KEY_POWER) {
				if (event.value) {
					ev = CHARGEMON_ACTION_POWER_KEY_PRESS;
				} else {
					ev = CHARGEMON_ACTION_POWER_KEY_RELEASE;
				}
			} else if (event.code == KEY_F24) {
				ev = CHARGEMON_ACTION_UNPLUG_CHARGER;
			}
		} else if (event.type == EV_ABS) {
			ev = CHARGEMON_ACTION_ERR;
		}
		return ev;
	}

action_timeout:
	return CHARGEMON_ACTION_TIMEOUT;
}

int hw_getBatteryCapacity(void)
{
	FILE *in;
	const char *fname = NULL;
	char tmpStr[MAX_STR + 1];

	if (capfile == NULL) {
		fname = utils_findBatteryFile();
		LOGD("Battery capacity filename: %s\n", fname);
		if (fname != NULL)
			capfile = strdup(fname);
		else
			return GET_BATTERYCAPACITY_ERR;
        }

	if (capfile == NULL)
		return GET_BATTERYCAPACITY_ERR;

	in = fopen(capfile, "rt");
	if (in == NULL) {
		LOG("fopen capfile is error!\n");
		return GET_BATTERYCAPACITY_ERR;
        }

	if (fgets(tmpStr, MAX_STR, in) == NULL) {
		LOG("Failed to read battery capacity!\n");
		fclose(in);
		return GET_BATTERYCAPACITY_ERR;

	}
	LOGD("Battery capacity(ascii): %s\n", tmpStr);
	fclose(in);

	return atoi(tmpStr);
}

int hw_getChargeOnline(void)
{
	const char *fname;
	fname = utils_findOnlineFile();

	if (fname != NULL) {
		LOGD("Charger online filename: %s\n", fname);
		return ONLINE;
	}
	return OFFLINE;
}

int hw_getChargeStatus(void)
{
	FILE *in;
	char tmpStr[MAX_STR + 1];
	const char *fname = NULL;
	int i;

	if (chargestatus == NULL) {
		fname = utils_findStatusFile();
		LOGD("Charger status filename: %s\n", fname);
		if (fname != NULL)
			chargestatus = strdup(fname);
		else
			goto err_exit;
	}

	if (chargestatus == NULL)
		goto err_exit;
	in = fopen(chargestatus, "rt");
	if (in == NULL)
		goto err_exit;

	fgets(tmpStr, MAX_STR, in);
	LOGD("Charger status (ascii): %s\n", tmpStr);
	fclose(in);

	for (i = 0; i < LOCAL_ARRAY_SIZE(batt_charge_status); i++) {
		if (!strncmp(tmpStr, batt_charge_status[i], strlen(batt_charge_status[i])))
		return i;
	}
err_exit:
	return 0;
}

int hw_getChargeHealth(void)
{
	FILE *in;
	char tmpStr[MAX_STR + 1];
	const char *fname = NULL;
	int i;

	if (chargehealth == NULL) {
		fname = utils_findHealthFile();
		LOGD("Charger health filename: %s\n", fname);
		if (fname != NULL)
			chargehealth = strdup(fname);
		else
			goto err_exit;
	}

	if (chargehealth == NULL)
		goto err_exit;
	in = fopen(chargehealth, "rt");
	if (in == NULL)
		goto err_exit;

	fgets(tmpStr, MAX_STR, in);
	LOGD("Charger health (ascii): %s\n", tmpStr);
	fclose(in);

	for (i = 0; i < LOCAL_ARRAY_SIZE(batt_charge_health); i++) {
		if (!strncmp(tmpStr, batt_charge_health[i], strlen(batt_charge_health[i])))
		return i;
	}
err_exit:
	return 0;
}

int hw_getChargePresent(void)
{
	const char *fname;
	fname = utils_findPresentFile();

	if (fname != NULL) {
		LOGD("Charger present filename: %s\n", fname);
		return PRESENT;
	}
	return NOT_PRESENT;
}

bool hw_isKnownBattery(void)
{
	FILE *in;
	char tmpStr[MAX_STR + 1];
	const char *fname = NULL;
	int i;

	if (batterytype == NULL) {
		fname = utils_findBatteryType();
		LOGD("Charger battery type filename: %s\n", fname);
		if (fname != NULL)
			batterytype = strdup(fname);
		else
			goto exit;
	}

	if (batterytype == NULL)
		goto exit;
	in = fopen(batterytype, "rt");
	if (in == NULL)
		goto exit;

	fgets(tmpStr, MAX_STR, in);
	LOGD("Battery Type : %s\n", tmpStr);
	fclose(in);

	for (i = 0; i < LOCAL_ARRAY_SIZE(battery_type); i++) {
		if (!strncmp(tmpStr, battery_type[i], strlen(battery_type[i]))) {
			LOG("Battery Type is Unknown battery\n");
			return false;
		}
	}
exit:
	return true;
}

void hw_setSleep(void)
{
	hw_writeSysfs(POWER_STATE, "mem");
}

void hw_setWakeup(void)
{
	hw_writeSysfs(POWER_STATE, "on");
}

void hw_wakeLock(void)
{
	char tmp[] = {LOG_TAG};
	hw_writeSysfs(WAKELOCK_LOCK, tmp);
}

void hw_wakeUnlock(void)
{
	char tmp[] = {LOG_TAG};
	hw_writeSysfs(WAKELOCK_UNLOCK, tmp);
}

#define LOW_BATT_SHUTDOWN_PATH "/sys/class/power_supply/battery/enable_shutdown_at_low_battery"

void hw_enableLowBatteryShutdown(void)
{
	hw_writeSysfs(LOW_BATT_SHUTDOWN_PATH, "1");
}

#define TYPEC_MODE_PATH "/sys/class/power_supply/battchg_ext/typec_mode"
int hw_checkTypecMode(void)
{
	char *buf;
	char *check_str = "Source attached";
	int size, i;

	buf = hw_readSysfs(TYPEC_MODE_PATH);
	if (buf == NULL)
		goto err_exit;

	size = strlen(check_str);
	for (i = 0; i < size; i++) {
		if (buf[i] != check_str[i]) {
			free(buf);
			return 0;
		}
	}

	free(buf);
	return 1;
err_exit:
	return 0;
}

#define CC_RECONNECTION_RUNNING_PATH "/sys/class/battchg_ext/cc_reconnection_running"
int hw_checkCCReconnectionRunning(void)
{
	char *buf;
	int rc;

	buf = hw_readSysfs(CC_RECONNECTION_RUNNING_PATH);
	if (buf == NULL)
		goto err_exit;

	rc = atoi(buf);
	free(buf);
	return rc;
err_exit:
	return 0;
}

#define WLC_RECONNECTION_RUNNING_PATH "/sys/class/power_supply/wireless/wlc_reconnection_running"
int hw_checkWLCReconnectionRunning(void)
{
	char *buf;
	int rc;

	buf = hw_readSysfs(WLC_RECONNECTION_RUNNING_PATH);
	if (buf == NULL)
		goto err_exit;

	rc = atoi(buf);
	free(buf);
	return rc;
err_exit:
	return 0;
}

#define OTG_CONNECTED_PATH "/sys/class/power_supply/battery_ext/otg_connected"
int hw_checkOtg(void)
{
	char *buf = NULL;
	int otg_connected = 0;

	buf = hw_readSysfs(OTG_CONNECTED_PATH);
	if (buf != NULL) {
		otg_connected = atoi(buf);
		free(buf);
	}
	return otg_connected;
}

int hw_getLowBatteryShutdown(void)
{
	char *buf;
	int lowbatt_shutdown;

	buf = hw_readSysfs(LOW_BATT_SHUTDOWN_PATH);
	if (buf == NULL)
		return 0;

	lowbatt_shutdown = atoi(buf);
	free(buf);
	return lowbatt_shutdown;
}

#define BOOTUP_SHUTDOWN_PATH "/sys/class/battchg_ext/bootup_shutdown_phase"
#define BATTERY_UEVENT_PATH "/sys/class/power_supply/battery/uevent"
void hw_setBootupShutdownStatus(char *str)
{
	hw_writeSysfs(BOOTUP_SHUTDOWN_PATH, str);
	hw_writeSysfs(BATTERY_UEVENT_PATH, "change");
}

#define SMART_CHARGING_ACTIVATION_PATH "/sys/class/battchg_ext/smart_charging_activation"
void hw_activateSmartCharge(void)
{
	hw_writeSysfs(SMART_CHARGING_ACTIVATION_PATH, "1");
}

static bool hw_isSmartChargeActivated(void)
{
	char *buf;
	int smart_charging_activation;

	buf = hw_readSysfs(SMART_CHARGING_ACTIVATION_PATH);
	if (buf == NULL)
		return false;

	smart_charging_activation = atoi(buf);
	free(buf);

	return (smart_charging_activation == 1) ? true : false;
}

#define SMART_CHARGING_INTERRUPTION_PATH "/sys/class/battchg_ext/smart_charging_interruption"
void hw_controlSmartCharge(int current_soc, int smtchg_target_soc)
{
	if (hw_isSmartChargeActivated()) {
		if (current_soc >= smtchg_target_soc)
			hw_writeSysfs(SMART_CHARGING_INTERRUPTION_PATH, "1");
		else
			hw_writeSysfs(SMART_CHARGING_INTERRUPTION_PATH, "0");
	}
}

#define UPTIME_PATH "/proc/uptime"
int hw_getUptime(void)
{
	char *uptime_full_info;
	char *uptime_str;
	int uptime = -1;

	uptime_full_info = hw_readSysfs(UPTIME_PATH);
	if (uptime_full_info == NULL) {
		LOG("Failed to get uptime\n");
		goto err_exit;
	}

	uptime_str = strtok(uptime_full_info, ".");
	if (uptime_str == NULL) {
		LOG("Failed to strtok /proc/uptime\n");
		goto err_exit;
	}

	uptime = atoi(uptime_str);

err_exit:
	if (uptime_full_info)
		free(uptime_full_info);

	return uptime;
}

#define SHIPMODE_PATH "/sys/class/qcom-battery/ship_mode_en"
#define SHIPMODE_ENABLE "1"

int hw_enableShipMode(void)
{
	char *ship_mode_en_str = NULL;
	int rc;

	hw_writeSysfs(SHIPMODE_PATH, SHIPMODE_ENABLE);

	ship_mode_en_str = hw_readSysfs(SHIPMODE_PATH);
	if (!ship_mode_en_str)
		return SHIPMODE_FAILURE;

	if (atoi(ship_mode_en_str) == atoi(SHIPMODE_ENABLE))
		rc = SHIPMODE_SUCCESS;
	else
		rc = SHIPMODE_FAILURE;

	free(ship_mode_en_str);

	return rc;
}
