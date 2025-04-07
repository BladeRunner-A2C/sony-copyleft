/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
 
/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 19/10/21  zxue     remove the diag log
 6/9/21    zxue     fix parasoft issue
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <qdf/pr_debug.h>
#include "trace.h"

// Will use the WMI event to trace the fw logs.
struct {
    void *target;
    trace_fw_log_write fwrite;

    void *dev;
    int(*wmi_set_log_level)(void *dev, bool enable);
} g_trace_wmi_context = { 0 };

void trace_ath_update_dev_wmi_level(void)
{
    if (!g_trace_wmi_context.wmi_set_log_level)
        return;

    g_trace_wmi_context.wmi_set_log_level(
        g_trace_wmi_context.dev,
        trace_ath_wmi_is_connected());
}

bool trace_ath_wmi_connect(void *target, trace_fw_log_write fwrite)
{
    if (g_trace_wmi_context.fwrite || g_trace_wmi_context.target)
        return false;

    g_trace_wmi_context.fwrite = fwrite;
    g_trace_wmi_context.target = target;

    trace_ath_update_dev_wmi_level();

    return true;
}

bool trace_ath_wmi_disconnect(void *target, trace_diag_write fwrite)
{
    if ((g_trace_wmi_context.fwrite != fwrite) ||
        (g_trace_wmi_context.target != target))
        return false;

    g_trace_wmi_context.fwrite = NULL;
    g_trace_wmi_context.target = NULL;

    trace_ath_update_dev_wmi_level();

    return true;
}

bool trace_ath_wmi_is_connected(void)
{
    return (g_trace_wmi_context.fwrite != NULL);
}

void trace_ath_wmi_set_log_level_handler(
    int(*wmi_set_log_level)(void *dev, bool enable), 
    void *dev)
{
    g_trace_wmi_context.wmi_set_log_level = wmi_set_log_level;
    g_trace_wmi_context.dev = dev;

    trace_ath_update_dev_wmi_level();
}

void trace_ath_wmi_fwlog(struct device *dev, void *data, u32 len)
{
    if (g_trace_wmi_context.fwrite) {
        g_trace_wmi_context.fwrite(
            g_trace_wmi_context.target, data, len);
    }
}

// On HSP, Will use the WMI Event to trace the fw log.
static inline void wmi_printbuf(struct device *dev,
			  unsigned char *payload,
			  int payload_len)
{
    trace_ath_wmi_fwlog(dev, payload, payload_len);
}

int wmi_local_write(struct device *dev, unsigned char *buf, int length)
{
    wmi_printbuf(dev, buf, length);
	return 0;
}