/**
 * @file:  cpr_image_target.h
 * @brief:
 *
 * Copyright (c) 2015-2019 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2024/04/02 23:00:31 $
 * $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/CPRLib/image/xbl/inc/cpr_image_target.h#1 $
 * $Change: 53083464 $
 */
#ifndef CPR_IMAGE_TARGET_H
#define CPR_IMAGE_TARGET_H

#include "cpr_data.h"
#include "cpr_defs.h"
#include "railway.h"


const cpr_settings* cpr_image_target_get_settings(void);

boolean cpr_image_target_is_turbo_mode_only(void);

cpr_domain_id cpr_image_target_railway_rail_to_cpr_domain(int railway_rail);
railway_corner cpr_image_target_cpr_mode_to_railway_corner(cpr_voltage_mode mode);
cpr_voltage_mode cpr_image_target_railway_corner_to_cpr_mode(railway_corner corner);

void cpr_image_target_enable_measurements(cpr_rail* rail, cpr_measurement_type type);
void cpr_image_target_disable_measurements(cpr_rail* rail, cpr_measurement_type type);

void cpr_image_target_extra_init(void);

boolean cpr_image_target_parse_bin(void);
void cpr_image_target_init_rail_config(cpr_rail *rail);

uint8 cpr_image_decode_vp_id(void);
int32 cpr_image_get_vbump_margin(cpr_domain_id railId, cpr_voltage_mode mode);

#endif /*CPR_IMAGE_TARGET_H*/
