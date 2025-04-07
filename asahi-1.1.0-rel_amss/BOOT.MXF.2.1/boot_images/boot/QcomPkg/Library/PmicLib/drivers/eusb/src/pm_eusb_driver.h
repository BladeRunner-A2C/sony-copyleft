#ifndef __PM_EUSB_DRIVER_H__
#define __PM_EUSB_DRIVER_H__

/*! \file pm_eusb_driver.h
*  \n
*  \brief  This file contains functions prototypes and variable/type/constant
*         declarations for supporting eusb peripheral.
*
*  \n &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/drivers/eusb/src/pm_eusb_driver.h#1 $

$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when         who      what, where, why
--------   ---      ----------------------------------------------------------
01/06/22   akm     Implement EUSB driver
========================================================================== */

/*===========================================================================
            INCLUDE FILES
===========================================================================*/
#include "pm_target_information.h"

/*===========================================================================

                     EUSB TYPES AND STRUCTURES

===========================================================================*/
typedef struct
{
  pm_register_address_type eusb_rptr_sts;                   // 0x08
  pm_register_address_type eusb_eusb_en;                    // 0x46
} pm_eusb_register_info_type;


typedef struct
{
  pm_comm_info_type            *comm_ptr;
  pm_eusb_register_info_type  *eusb_reg_table;
  pm_register_address_type     base_address;
  uint8                        num_of_peripherals;
  uint8                        dig_maj_min_ver;
}pm_eusb_data_type;


/*===========================================================================

                     FUNCTION DECLARATION

===========================================================================*/
void 
pm_eusb_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index, uint32 bus_id);

pm_eusb_data_type* 
pm_eusb_get_data(uint32 bus_id, uint32 pmic_index);


#endif // __PM_EUSB_DRIVER_H__

