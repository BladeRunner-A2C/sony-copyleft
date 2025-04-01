/*
 * Copyright (c) 2014 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef __CHARGEMON_HW_H
#define __CHARGEMON_HW_H

#define CHARGE_COLOR_OFF 0
#define HW_INIT_SUCCESS 0

#define SMTCHG_TARGET_SOC_NONE -1

#define SHIPMODE_SUCCESS 0
#define SHIPMODE_FAILURE 1

enum chargemon_event_t {
	CHARGEMON_ACTION_ERR = -1,
	CHARGEMON_ACTION_TIMEOUT,
	CHARGEMON_ACTION_POWER_KEY_PRESS,
	CHARGEMON_ACTION_POWER_KEY_RELEASE,
	CHARGEMON_ACTION_UNPLUG_CHARGER,
	CHARGEMON_ACTION_NONE,
};

enum {
	ONLINE,
	OFFLINE,
};

enum {
	UNKNOWN,
	CHARGING,
	DISCHARGING,
	NOT_CHARGING,
	FULL,
};

enum {
	/* UNKNOWN */
	GOOD = 1,
	OVERHEAT,
	DEAD,
	OVER_VOLTAGE,
	UNSPECIFIED_FAILURE,
	COLD,
};

enum {
	PRESENT,
	NOT_PRESENT,
};

int hw_init(void);
void hw_vibrate(int time_ms);
void hw_setRGBled(int on, int capacity);
int hw_setBacklight(int on);
enum chargemon_event_t hw_waitForUserAction(int timeout);
int hw_getBatteryCapacity(void);
int hw_getChargeOnline(void);
int hw_getChargeStatus(void);
int hw_getChargeHealth(void);
int hw_getChargePresent(void);
bool hw_isKnownBattery(void);
void hw_setSleep(void);
void hw_setWakeup(void);
void hw_wakeLock(void);
void hw_wakeUnlock(void);
int hw_getWeakChargerSts(void);
int hw_getInvalidChargerSts(void);
void hw_enableLowBatteryShutdown();
int hw_checkTypecMode(void);
int hw_checkCCReconnectionRunning(void);
int hw_checkWLCReconnectionRunning(void);
int hw_checkOtg(void);
int hw_getLowBatteryShutdown(void);
void hw_setBootupShutdownStatus(char *str);
void hw_activateSmartCharge(void);
void hw_controlSmartCharge(int current_soc, int smtchg_target_soc);
int hw_getUptime(void);
int hw_enableShipMode(void);

extern const char *batt_charge_status[] ;
extern const char *batt_charge_health[] ;
#endif
