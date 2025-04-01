/*
 * Copyright (c) 2014 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/reboot.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <cutils/properties.h>

#include "graphics.h"
#include "hw.h"
#include "log.h"
#include "miscta.h"
#include "miscta_units.h"
#include "utils.h"
#ifdef CFG_SOMC_THERMAL
#include "libsomc_thermal/somc_thermal.h"
#endif
#include "record_timestamp.h"

#define WAIT_INTERVAL_DISP_ON 500
#define WAIT_INTERVAL_DISP_OFF 5000
#define DISP_ON_LOOP_COUNT 30
#define CHARGER_STATUS_LOOP_COUNT 8
#define RAPID_CHECK_COUNT 10
#define VIBRATE_TIME_MS 75
#define POWER_KEY_LONG_PRESS_TIME_S 2

#define ON 1
#define OFF 0
#define DISABLE_USB_CHARGING 1

#define MISCTA_2311_01 0x01	/* Skip power off charge with SoC=5% */
#define MISCTA_2311_02 0x02	/* Skip power off charge with SoC=5% (clear automatically) */
#define MISCTA_2311_C0 0xC0	/* Skip power off charge unconditionally */
#define MISCTA_2311_C1 0xC1	/* Skip power off charge with SoC=1% */
#define MISCTA_2311_C2 0xC2	/* Skip power off charge with SoC=2% */
#define MISCTA_2311_C3 0xC3	/* Skip power off charge with SoC=3% */
#define MISCTA_2311_C4 0xC4	/* Skip power off charge with SoC=4% */
#define MISCTA_2311_CF 0xCF	/* Skip power off charge with SoC=100% */
#define MISCTA_2311_D1 0xD1	/* Skip power off charge in 10min */

#define TIME_LIMIT_DEFAULT 600
#define TIME_LIMIT_NONE     -1
#define TARGET_SOC_FULL      100
#define TARGET_SOC_DEFAULT   5
#define TARGET_SOC_NONE     -1

#define DELAY_NOT_CHARGING 8

#define SLEEP_PREVENTION_TIME 90

#define SHIP_MODE_FLAG_ENABLE_BIT 0x02
#define SHIP_MODE_FLAG_DATA_SIZE 1

void enterShipModeIfEnabled(void)
{
	miscta_status_t status;
	uint8_t unitData = 0;
	uint32_t size = 0;

	size = SHIP_MODE_FLAG_DATA_SIZE;

	status = miscta_read_unit(TA_SHIP_MODE_FLAG, &unitData, &size);

	if(status != MT_SUCCESS || size != SHIP_MODE_FLAG_DATA_SIZE) {
		LOG("Failed to read TA_SHIP_MODE_FLAG\n");
		goto start_chargemon;
	}

	if (!(unitData & SHIP_MODE_FLAG_ENABLE_BIT))
		goto start_chargemon;

	unitData &= ~SHIP_MODE_FLAG_ENABLE_BIT;
	size = SHIP_MODE_FLAG_DATA_SIZE;

	status = miscta_write_unit(TA_SHIP_MODE_FLAG, &unitData, size);

	if (status != MT_SUCCESS || size != SHIP_MODE_FLAG_DATA_SIZE) {
		LOG("Failed to clear TA_SHIP_MODE_FLAG\n");
		goto start_chargemon;
	}

	while (hw_getChargeOnline() == ONLINE) {
		LOG("Charger is still connected. Wait for disconnection...\n");
		sleep(1);
	}

	if (hw_enableShipMode() != SHIPMODE_SUCCESS) {
		LOG("Failed to enable ShipMode\n");
		goto start_chargemon;
	}

	LOG("Enter ShipMode\n");

	reboot(RB_POWER_OFF);
	exit(EXIT_SUCCESS);

start_chargemon:
	return;
}

/* Handling for TA_DISABLE_USB_CHARGING (2312) */
static void setDisableChargingMsgIfRequired(void)
{
	miscta_status_t status;
	uint8_t unitData = 0;
	uint32_t size = sizeof(unitData);

	status = miscta_read_unit(TA_DISABLE_USB_CHARGING, &unitData, &size);

	if (status == MT_SUCCESS && unitData == DISABLE_USB_CHARGING) {
		graphics_disableCharging();
	}
}

/* Handling for TA_DISABLE_CHARGE_ONLY (2311) */
static void getForcedExitOptions(int *time_limit, int *target_soc)
{
	miscta_status_t status;
	uint8_t unitData = 0;
	uint32_t size = 0;

	size = sizeof(unitData);

	status = miscta_read_unit(TA_DISABLE_CHARGE_ONLY,
		&unitData,
		&size);

	switch (unitData) {
	case MISCTA_2311_01:
	case MISCTA_2311_02:
		*target_soc = TARGET_SOC_DEFAULT;
		break;
	case MISCTA_2311_C0:
		*target_soc = 0;
		break;
	case MISCTA_2311_C1:
		*target_soc = 1;
		break;
	case MISCTA_2311_C2:
		*target_soc = 2;
		break;
	case MISCTA_2311_C3:
		*target_soc = 3;
		break;
	case MISCTA_2311_C4:
		*target_soc = 4;
		break;
	case MISCTA_2311_CF:
		*target_soc = TARGET_SOC_FULL;
		break;
	case MISCTA_2311_D1:
		*time_limit = TIME_LIMIT_DEFAULT;
		break;
	default:
		break;
	}

	if (unitData == MISCTA_2311_02) {
		unitData = 0;
		size = sizeof(unitData);
		status = miscta_write_unit(TA_DISABLE_CHARGE_ONLY,
			&unitData,
			size);
		if (status != MT_SUCCESS)
			LOG("Resetting miscTA parameter failed!\n");
	}
}

/* Handling for TA_OFF_MODE_SMART_CHARGE (2318) */
#define SMTCHG_TA_IDX_FLG 0
#define SMTCHG_TA_IDX_SOC 1
void handleSmartChargeSettings(int *smtchg_target_soc)
{
	miscta_status_t status;
	uint8_t unitData[2];
	uint32_t size = 0;

	*smtchg_target_soc = SMTCHG_TARGET_SOC_NONE;

	size = sizeof(unitData);
	status = miscta_read_unit(TA_OFF_MODE_SMART_CHARGE,
		&unitData,
		&size);
	if (status != MT_SUCCESS) {
		LOG("Reading TA_OFF_MODE_SMART_CHARGE from MiscTA failed!\n");
		return;
	}

	LOG("BSP_Charger unitData[SMTCHG_TA_IDX_FLG]:%d, unitData[SMTCHG_TA_IDX_SOC]:%d!\n", unitData[SMTCHG_TA_IDX_FLG], unitData[SMTCHG_TA_IDX_SOC]);

	if (unitData[SMTCHG_TA_IDX_FLG] == 1 &&
		unitData[SMTCHG_TA_IDX_SOC] >= 1 && unitData[SMTCHG_TA_IDX_SOC] <= 100) {
		*smtchg_target_soc = (int)unitData[SMTCHG_TA_IDX_SOC];
		LOG("BSP_Charger first init\n");
		hw_activateSmartCharge();
		LOG("Off mode smart charge is enabled (target_soc=%d)\n", *smtchg_target_soc);
	}
}

static void handleMiscTaOptions(int *time_limit, int *target_soc, int *smtchg_target_soc)
{
	setDisableChargingMsgIfRequired();
	getForcedExitOptions(time_limit, target_soc);
	handleSmartChargeSettings(smtchg_target_soc);
}

#ifdef CFG_SOMC_THERMAL
static bool is_init_thermal = false;
static bool is_start_thermal = false;
static void init_thermal_monitor(void)
{
	if (!is_init_thermal) {
		LOG("init therm monitor\n");
		somc_thermal_monitor_init();
		is_init_thermal = true;
	}
}

static void release_thermal_monitor(void)
{
	if (is_init_thermal) {
		LOG("release therm monitor\n");
		somc_thermal_monitor_release();
		is_init_thermal = false;
	}
}

static void start_thermal_monitor(void)
{
	if (!is_start_thermal) {
		LOG("start therm monitor\n");
		somc_thermal_monitor_ctrl(SOMC_THERMAL_MONITOR_START);
		is_start_thermal = true;
	}
}

static void stop_thermal_monitor(void)
{
	if (is_start_thermal) {
		LOG("stop therm monitor\n");
		somc_thermal_monitor_ctrl(SOMC_THERMAL_MONITOR_STOP);
		is_start_thermal = false;
	}
}
#endif

int main(void)
{
	int reboot_mode;
	int online;
	int present;
	int typec_source;
	int cc_reconnection_running;
	int wlc_reconnection_running;
	int otg;
	enum chargemon_event_t key;
	int capacity = 0;
	int charge_sts = 0;
	int health = 0;
	bool change = false;
	int capacity_bkup = -1;
	int charge_sts_bkup = -1;
	int health_bkup = -1;
	bool disp_on = false;
	time_t now;
	double seconds;
	bool is_normal_battery_type = false;
	int phase = 0;
	bool animation = false;
	bool is_running_loop = false;
	int wait_interval = 0;
	int rapid_check_count = 0;
	time_t off_charge_start;
	int time_limit = TIME_LIMIT_NONE;
	int target_soc = TARGET_SOC_NONE;
	int disp_on_loop_count;
	struct power_key_status_t {
		bool is_pressed;
		time_t pressed_time;
	} power_key_status;
	int smtchg_target_soc = SMTCHG_TARGET_SOC_NONE;
	int uptime;
	bool sleep_enabled = false;

	enterShipModeIfEnabled();

	memset(&power_key_status, 0, sizeof(power_key_status));

	/*
	 * is released in hw_waitForUserAction
	 */
	hw_wakeLock();

	LOG("start chargemon\n");

	if (hw_init() < HW_INIT_SUCCESS) {
		LOG("abort_chargemon: hw_init() failed\n");
		goto abort_chargemon;
	}

	LOG("Wait for charging status to be ready by %dsec\n", DELAY_NOT_CHARGING);
	sleep(DELAY_NOT_CHARGING);

	handleMiscTaOptions(&time_limit, &target_soc, &smtchg_target_soc);
	if (time_limit != TIME_LIMIT_NONE)
		time(&off_charge_start);

	disp_on_loop_count = DISP_ON_LOOP_COUNT;

#ifdef CFG_SOMC_THERMAL
	init_thermal_monitor();
#endif
	/* Measurement of the start time of the PowerOffCharge */
	hw_setBootupShutdownStatus("1");
	record_timestamp_init();
	record_timestamp_start();

	LOG("enter power off charge\n");
	while (1) {
		change = false;

		online = hw_getChargeOnline();
		present = hw_getChargePresent();
		typec_source = hw_checkTypecMode();
		cc_reconnection_running = hw_checkCCReconnectionRunning();
		wlc_reconnection_running = hw_checkWLCReconnectionRunning();
		otg = hw_checkOtg();
		if ((present == NOT_PRESENT) && (online == OFFLINE)
					&& !typec_source && !cc_reconnection_running && !wlc_reconnection_running && !otg) {
			LOG("shutdown_exit: NOT_PRESENT, OFFLINE, typec-mode is not source, CC reconnection is not running\n");
			goto shutdown_exit;
		}

		capacity = hw_getBatteryCapacity();
		if (capacity < 0) {
			LOG("capacity failed! set default value 0.\n");
			capacity = 0;
		}

		if (target_soc != TARGET_SOC_NONE && capacity >= target_soc) {
			LOG("reboot_exit: capacity >= %d, finish minimal charging\n", target_soc);
			goto reboot_exit;
		}

		if (smtchg_target_soc != SMTCHG_TARGET_SOC_NONE)
			hw_controlSmartCharge(capacity, smtchg_target_soc);

		if (time_limit != TIME_LIMIT_NONE) {
			time(&now);
			if (difftime(now, off_charge_start) > (double)time_limit) {
				LOG("reboot_exit: charging time = %fs, finish minimal charging\n", difftime(now, off_charge_start));
				goto reboot_exit;
			}
		}

		if (capacity_bkup != capacity) {
			capacity_bkup = capacity;
			change = true;
		}

		charge_sts = hw_getChargeStatus();
		if (charge_sts_bkup != charge_sts) {
			charge_sts_bkup = charge_sts;
			change = true;
		}
#ifdef CFG_SOMC_THERMAL
		if (charge_sts == FULL)
			stop_thermal_monitor();
		else
			start_thermal_monitor();
#endif

		if ((charge_sts == CHARGING || charge_sts == FULL)
                    && hw_isKnownBattery())
			hw_setRGBled(ON, capacity);
		else
			hw_setRGBled(OFF, CHARGE_COLOR_OFF);

		if (!disp_on || health_bkup != OVERHEAT) {
			health = hw_getChargeHealth();
			if (health_bkup != health) {
				health_bkup = health;
				change = true;
			}
		}

		if (!is_normal_battery_type) {
			if (hw_isKnownBattery()) {
				is_normal_battery_type = true;
				change = true;
			}
		}

		if (change) {
			LOG("capacity = %d, status = %s, health = %s\n", capacity,
				batt_charge_status[charge_sts],
				batt_charge_health[health]);
		}

		if (!is_running_loop) {
			disp_on = true;
			change = true;
			animation = false;
			screen_update(disp_on, capacity, charge_sts, health,
				phase, change, animation, is_normal_battery_type,
				smtchg_target_soc);
			hw_setBacklight(ON);
			is_running_loop = true;
		}

		if (disp_on_loop_count > 0) {
			rapid_check_count = 0;
			wait_interval = WAIT_INTERVAL_DISP_ON;
		} else {
			if (rapid_check_count > 0) {
				rapid_check_count--;
				wait_interval = WAIT_INTERVAL_DISP_ON;
			} else {
				wait_interval = WAIT_INTERVAL_DISP_OFF;
			}
		}
		key = hw_waitForUserAction(wait_interval);

		switch (key) {
		case CHARGEMON_ACTION_POWER_KEY_PRESS:
			power_key_status.is_pressed = true;
			time(&power_key_status.pressed_time);
			disp_on_loop_count = DISP_ON_LOOP_COUNT;
			if (disp_on)
				continue;
			break;
		case CHARGEMON_ACTION_POWER_KEY_RELEASE:
			power_key_status.is_pressed = false;
			power_key_status.pressed_time = time(NULL);
			break;
		case CHARGEMON_ACTION_TIMEOUT:
			if (disp_on_loop_count > 0) {
				disp_on_loop_count--;
				phase++;
			}
			time(&now);
			seconds = difftime(now, power_key_status.pressed_time);

			if (power_key_status.is_pressed && seconds >= POWER_KEY_LONG_PRESS_TIME_S) {
				if (capacity > 0) {
					LOG("reboot_exit: power_key pressed time = %lf and capacity = %d\n",
						seconds, capacity);
					hw_vibrate(VIBRATE_TIME_MS);
					goto reboot_exit;
				}
				LOG("power_key pressed time = %lf. But can't start up phone due to capacity 0\n", seconds);
			}
			break;
		case CHARGEMON_ACTION_UNPLUG_CHARGER:
			LOG("charger is unplugged\n");
			rapid_check_count = RAPID_CHECK_COUNT;
			continue;
		case CHARGEMON_ACTION_ERR:
		case CHARGEMON_ACTION_NONE:
			continue;
		default:
			break;
		}

		if (disp_on_loop_count == 0) {
			if (disp_on) {
				hw_setBacklight(OFF);
				disp_on = false;
				phase = 0;
				screen_update(disp_on, capacity, charge_sts, health,
					phase, change, animation, is_normal_battery_type,
					smtchg_target_soc);
			}
		} else {
			if (disp_on) {
				if (charge_sts == CHARGING &&
					health != OVERHEAT)
					animation = true;

				if (change || animation) {
					screen_update(disp_on, capacity, charge_sts, health,
						phase, change, animation, is_normal_battery_type,
						smtchg_target_soc);
				}
			} else {
				hw_setWakeup();
				disp_on = true;
				change = true;
				animation = false;
				screen_update(disp_on, capacity, charge_sts, health,
					phase, change, animation, is_normal_battery_type,
					smtchg_target_soc);
				hw_setBacklight(ON);
			}
		}

		if (!sleep_enabled) {
			uptime = hw_getUptime();
			if (uptime > SLEEP_PREVENTION_TIME || uptime < 0)
				sleep_enabled = true;
		}

		if (sleep_enabled && !disp_on && charge_sts != CHARGING) {
			hw_setSleep();
		}
	}

reboot_exit:
	LOG("exit chargemon by reboot_exit\n");

	/* Measurement of the end time of the PowerOffCharge */
	record_timestamp_end(END_REASON_POWERKEY);
	reboot_mode = RB_AUTOBOOT;
	goto terminate_chargemon;

shutdown_exit:
	LOG("exit chargemon by shutdown_exit\n");

	/* Measurement of the end time of the PowerOffCharge */
	record_timestamp_end(END_REASON_UNPLUG);
	reboot_mode = RB_POWER_OFF;
	goto terminate_chargemon;

terminate_chargemon:
	hw_setBootupShutdownStatus("4");
	hw_setBacklight(OFF);
	screen_close();
	hw_setRGBled(OFF, CHARGE_COLOR_OFF);
#ifdef CFG_SOMC_THERMAL
	stop_thermal_monitor();
	release_thermal_monitor();
#endif
	hw_setWakeup();

	/*
	 * The chargemon shutdown process waits here for 1 second after setting
	 * bootup_shutdown_phase=4 so that battery_logging can write shutdown log.
	 */
	sleep(1);
	sync();
	reboot(reboot_mode);
	return 0;

abort_chargemon:
	reboot(RB_AUTOBOOT);
	return 0;

}
