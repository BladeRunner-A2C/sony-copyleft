/*********************************************************************
 * Copyright (c) 2018 Sony Mobile Communications Inc.                *
 * All rights, including trade secret rights, reserved.              *
 *********************************************************************/
#ifndef _IDD_BATT_DEGR2_H_
#define _IDD_BATT_DEGR2_H_

#include "logger/charge-logging/miscta_batt_stat.h"

bool can_send_idd_batt_degr2(struct cs_data_t *cs_data, struct batt_stat_t *batt_stat);
void send_idd_batt_degr2(struct cs_data_t *cs_data, const struct batt_stat_t *batt_stat);

#endif /* _IDD_BATT_DEGR2_H_ */
