/*
 * Copyright (C) 2012 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef __CHARGEMON_UTILS_H
#define __CHARGEMON_UTILS_H

#define USB_SUCCESS 0

enum usb_mode {
	USB_MODE_MSC,
	USB_MODE_ACCESSORY
};

#define MAX_PATH _POSIX_PATH_MAX

int utils_findKeyEvents(int *inputfds, int max);
const char *utils_findBatteryFile(void);
const char *utils_findOnlineFile(void);
const char *utils_findStatusFile(void);
const char *utils_findHealthFile(void);
const char *utils_findPresentFile(void);
const char *utils_findBatteryType(void);
int IsConnectionTypeUSB(void);
int IsUsbConnected(void);

#endif
