#ifndef __PM_BMD_DRIVER_H__
#define __PM_BMD_DRIVER_H__

/*! \file pm_bmd_driver.h
*  \n
*  \brief  This file contains functions prototypes and variable/type/constant
*         declarations for supporting bmd peripheral.
*
*  \n &copy; Copyright 2017-2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/drivers/bmd/src/pm_bmd_driver.h#1 $

$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when         who      what, where, why
--------   ---      ----------------------------------------------------------
02/07/18   xmp      Implement BMD driver
11/20/17   richaa   Created
========================================================================== */

/*===========================================================================
            INCLUDE FILES
===========================================================================*/
#include "pm_target_information.h"

/*===========================================================================

                     BMD TYPES AND STRUCTURES

===========================================================================*/
typedef struct
{
  pm_register_address_type bmd_fsm_sts;                   // 0x09
  pm_register_address_type bmd_int_rt_sts;                // 0x10
  pm_register_address_type bmd_mode_ctl;                  // 0x40
  pm_register_address_type bmd_timing;                    // 0x41
  pm_register_address_type bmd_deb_ctl;                   // 0x42
  pm_register_address_type bmd_threshold_ctl;             // 0x43  the name in ipcat is bmd_ctl. Add "threshold" for readability
  pm_register_address_type bmd_src_ctl;                   // 0x44
  pm_register_address_type bmd_bmd_adc_ctl;               // 0x45
  pm_register_address_type bmd_bmd_en;                    // 0x46
  pm_register_address_type bmd_bmd_adc_dly;               // 0x47
  pm_register_address_type bmd_lockbit;                   // 0xD1
} pm_bmd_register_info_type;


typedef struct
{
  pm_comm_info_type            *comm_ptr;
  pm_bmd_register_info_type    *bmd_reg_table;
  pm_register_address_type     base_address;
  uint8                        num_of_peripherals;
  uint8                        dig_maj_min_ver;
}pm_bmd_data_type;


/*===========================================================================

                     FUNCTION DECLARATION

===========================================================================*/
void
pm_bmd_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index, uint32 bus_id);

pm_bmd_data_type*
pm_bmd_get_data(uint32 bus_id, uint32 pmic_index);


#endif // __PM_BMD_DRIVER_H__

