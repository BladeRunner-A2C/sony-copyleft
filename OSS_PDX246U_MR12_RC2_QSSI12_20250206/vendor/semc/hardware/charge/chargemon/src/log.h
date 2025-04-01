/*
 * Copyright (C) 2012 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef __CHARGEMON_LOG_H
#define __CHARGEMON_LOG_H

#include <cutils/klog.h>

#define LOG_TAG		"chargemon"

#define LOG_ALL

#define LOG(x...)	KLOG_ERROR(LOG_TAG, x)
#ifdef LOG_ALL
#define LOGD(x...)	KLOG_ERROR(LOG_TAG, x)
#else
#define LOGD(x...)
#endif

#endif
