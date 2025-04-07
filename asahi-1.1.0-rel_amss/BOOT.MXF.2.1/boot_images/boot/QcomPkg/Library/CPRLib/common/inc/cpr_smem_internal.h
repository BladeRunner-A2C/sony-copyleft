/**
* @file:  cpr_smem_internal.h
* @brief:
*
* Copyright (c) 2017-2018 Qualcomm Technologies, Inc.
* All Rights Reserved.
* QUALCOMM Proprietary and Confidential.
*
* $DateTime: 2024/04/02 23:00:31 $
* $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/CPRLib/common/inc/cpr_smem_internal.h#1 $
* $Change: 53083464 $
*/
#ifndef CPR_SMEM_INTERNAL_H
#define CPR_SMEM_INTERNAL_H

#include "cpr_cfg.h"
#include "cpr_data.h"
#include "cpr_smem.h"

void cpr_smem_write_rail_settings(cpr_smem_hdr* hdr,
        cpr_smem_rail_hdr* railHdr, uint32 *offset,
        cpr_rail_state* state);
void cpr_smem_read_rail_settings(cpr_smem_hdr* hdr,
        cpr_smem_rail_hdr* railHdr, uint32 *offset,
        cpr_settings *settings, uint8 idx);

void cpr_smem_write_misc_data(cpr_smem_hdr* hdr, uint32 *currOffset);

#endif
