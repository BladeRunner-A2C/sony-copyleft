/*! \file pm_bmd_driver.c
*  \n
*  \brief This file contains bmd peripheral driver initialization during which the driver data is stored.
*  \n
*  \n &copy; Copyright 2017-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/drivers/bmd/src/pm_bmd_driver.c#1 $

$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/07/18   xmp     Implement BMD driver
11/20/17   richaa  Created
========================================================================== */

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_bmd_driver.h"
#include "CoreVerify.h"

/*===========================================================================

                        MACRO AND TYPE DEFINITIONS

===========================================================================*/
#define PMIC_BMD_MAX_HW_VER 0x01

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/* Static global variable to store the BMD data */
static pm_bmd_data_type *pm_bmd_data_arr[PM_MAX_BUSES_SUPPORTED][PM_MAX_NUM_PMICS];

static pm_bmd_register_info_type bmd_reg =
{
  .bmd_fsm_sts       = 0x09,
  .bmd_int_rt_sts    = 0x10,
  .bmd_mode_ctl      = 0x40,
  .bmd_timing        = 0x41,
  .bmd_deb_ctl       = 0x42,
  .bmd_threshold_ctl = 0x43,
  .bmd_src_ctl       = 0x44,
  .bmd_bmd_adc_ctl   = 0x45,
  .bmd_bmd_en        = 0x46,
  .bmd_bmd_adc_dly   = 0x47,
  .bmd_lockbit       = 0xD1,
};


/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void
pm_bmd_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index, uint32 bus_id)
{
  pm_bmd_data_type *bmd_ptr = pm_bmd_data_arr[bus_id][pmic_index];

  if (NULL == bmd_ptr)
  {
    
    pm_malloc(sizeof(pm_bmd_data_type), (void**)&bmd_ptr);
    CORE_VERIFY_PTR(bmd_ptr);
    
    bmd_ptr->dig_maj_min_ver = ((peripheral_info->digital_major_version << 0x4) | 
                                (peripheral_info->digital_minor_version));

    CORE_VERIFY (bmd_ptr->dig_maj_min_ver <= PMIC_BMD_MAX_HW_VER);

    /* Assign Comm ptr */
    bmd_ptr->comm_ptr = comm_ptr;

    bmd_ptr->bmd_reg_table = &bmd_reg;

    bmd_ptr->base_address = peripheral_info->base_address;

    bmd_ptr->num_of_peripherals = 1;

    pm_bmd_data_arr[bus_id][pmic_index] = bmd_ptr;
  }
  else
  {
    bmd_ptr->num_of_peripherals++;
  }
}

pm_bmd_data_type*
pm_bmd_get_data(uint32 bus_id, uint32 pmic_index)
{
  return ((pmic_index < PM_MAX_NUM_PMICS) && (bus_id < PM_MAX_BUSES_SUPPORTED)) ? pm_bmd_data_arr[bus_id][pmic_index] : NULL;
}

