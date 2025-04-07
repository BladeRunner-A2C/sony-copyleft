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

#ifndef DIAG_TRACE_H
#define DIAG_TRACE_H

#include <qdf/qbase.h>

typedef void(*trace_diag_write)(void *target, void *data, u32 len);
typedef void(*trace_fw_log_write)(void *target, void *data, u32 len);

/* WMI DIAG */
bool trace_ath_wmi_connect(void *target, trace_diag_write fwrite);
bool trace_ath_wmi_disconnect(void *target, trace_diag_write fwrite);

bool trace_ath_wmi_is_connected(void);

void trace_ath_wmi_set_log_level_handler(
    int(*wmi_set_log_level)(void *dev, bool enable), void *dev);
void trace_ath_wmi_fwlog(struct device *dev, void *data, u32 len);
int wmi_local_write(struct device *dev, unsigned char *buf, int length);

#endif // !DIAG_TRACE_H
