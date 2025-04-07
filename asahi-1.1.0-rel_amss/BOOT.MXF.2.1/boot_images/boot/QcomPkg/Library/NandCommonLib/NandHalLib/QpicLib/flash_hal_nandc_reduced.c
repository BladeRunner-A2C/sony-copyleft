/*====================================================================
 *
 * FILE:        flash_hal_nandc_cfg_reduced.c
 *
 * SERVICES:    Config file for reduced NAND driver
 *
 * DESCRIPTION: This file helps configure the inclusion of desired
 *              NAND driver functionality for reduced mode NAND driver.
 *
 *
 * PUBLIC CLASSES AND STATIC FUNCTIONS:
 *
 * INITIALIZATION AND SEQUENCING REQUIREMENTS:
 *
 * Copyright (c) 2012,2020 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Confidential and Proprietary
 *==================================================================*/

/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/NandCommonLib/NandHalLib/QpicLib/flash_hal_nandc_reduced.c#1 $ $DateTime: 2024/04/02 23:00:31 $ $Author: cirrusp4svc $
 *
 *
 * when         who     what, where, why
 * ----------   ---     ----------------------------------------------
 * 06/08/20     sa      Ported for Olympic.
 * 09/04/12     sv      Initial Revision
 *===================================================================*/

#include "flashi_hal_nand.h"
#include "flashi_hal_nandc.h"
#include "flashi_hal_common.h"

/* Initialize command pointers for desired operations in reduced mode. */
enum flash_hal_status hal_nandc_predef_cmd_ptrs_init(
 struct flash_hal_ctlr_data *priv_data,
  struct flash_hal_predef_init_data *init_data,
  struct flash_hal_mem_data *buff_data, uintnt *used_buff_size)
{
  return hal_nandc_predef_cmd_ptrs_init_reduced(priv_data, init_data, 
    buff_data, used_buff_size);
}

/*
 * Init pre-defined sequence function pointers. Call the function to 
 * initialize the reduced mode function pointers.
 */
void hal_nandc_fptrs_init(struct flash_hal_ctlr_ops *ctlr_ops)
{
  hal_nandc_fptrs_init_reduced(ctlr_ops);
}
