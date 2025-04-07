/**
 * @file:  cpr_measurements.h
 * @brief:
 *
 * Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2024/04/02 23:00:31 $
 * $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/CPRLib/common/inc/cpr_measurements.h#1 $
 * $Change: 53083464 $
 */
#ifndef CPR_MEASUREMENTS_H
#define	CPR_MEASUREMENTS_H

#include "cpr_types.h"
#include "cpr_cfg.h"

void cpr_measurements_settle(cpr_rail* rail, cpr_voltage_mode mode);
void cpr_measurements_thermal_update(cpr_thermal_region region);
void cpr_measurements_aging(cpr_rail* rail);

#endif
