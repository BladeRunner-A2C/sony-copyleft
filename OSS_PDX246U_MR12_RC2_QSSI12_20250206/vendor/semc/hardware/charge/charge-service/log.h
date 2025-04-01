/*********************************************************************
 * Copyright (c) 2016 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/
#ifndef _CHARGE_SERVICE_UTILS_H_
#define _CHARGE_SERVICE_UTILS_H_

#include <cutils/klog.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "charge_service"

#define LOG(x...)	KLOG_ERROR(LOG_TAG, x)
#ifdef LOG_ALL
#define LOGD(x...)	KLOG_ERROR(LOG_TAG, x)
#else
#define LOGD(x...)
#endif

#endif /* _CHARGE_SERVICE_UTILS_H_ */
