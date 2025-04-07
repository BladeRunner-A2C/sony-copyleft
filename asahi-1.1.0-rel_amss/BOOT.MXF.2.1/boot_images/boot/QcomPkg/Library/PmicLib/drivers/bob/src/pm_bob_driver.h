#ifndef __PM_BOB_DRIVER__H__
#define __PM_BOB_DRIVER__H__

/*! \file pm_bob_driver.h
 *  \n
 *  \brief This file contains BOOST BYPASS peripheral driver related function prototypes,
 *         enums and driver data structure type.   
 *  \n  
 *  \n &copy; Copyright 2014-2017, 2021 QUALCOMM Technologies Incorporated, All Rights Reserved
 */
/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/drivers/bob/src/pm_bob_driver.h#1 $

$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/06/14   kt      Created
========================================================================== */

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_pwr_alg.h"
#include "pm_bob.h"

/*===========================================================================

                     BOOST BYPASS TYPES AND STRUCTURES 

===========================================================================*/

typedef struct
{
    pm_comm_info_type *comm_ptr;
    pm_pwr_data_type  pm_pwr_data;
	uint8             *periph_subtype;
} pm_bob_data_type;

/*===========================================================================

                     FUNCTION DECLARATION 

===========================================================================*/
void pm_bob_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index);

pm_bob_data_type* pm_bob_get_data(uint8 pmic_index);

uint8 pm_bob_get_num_peripherals(uint8 pmic_index);

pm_err_flag_type pm_bob_sw_mode(uint8 pmic_chip, uint8 peripheral_index, pm_bob_mode_type mode);

pm_err_flag_type pm_bob_pin_volt_level(uint8 pmic_chip, uint8 peripheral_index, uint8 pin_number, pm_volt_level_type volt_level);

pm_err_flag_type pm_bob_pin_volt_level_status(uint8 pmic_chip, uint8 peripheral_index, uint8 pin_number, pm_volt_level_type* volt_level);


#endif // __PM_BOB_DRIVER__H__
