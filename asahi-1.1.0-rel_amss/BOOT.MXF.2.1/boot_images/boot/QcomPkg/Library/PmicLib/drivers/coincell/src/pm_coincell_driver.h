#ifndef __PM_COINCELL_DRIVER_H__
#define __PM_COINCELL_DRIVER_H__

/*! \file pm_coincell_driver.h 
*  \n
*  \brief  This file contains functions prototypes and variable/type/constant
*         declarations for supporting coincell peripheral.
*  
*  \n &copy; Copyright 2014-2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/drivers/coincell/src/pm_coincell_driver.h#1 $

$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when         who      what, where, why
--------   ---      ----------------------------------------------------------
09/15/14   akm      Created
========================================================================== */

/*===========================================================================
						INCLUDE FILES
===========================================================================*/
#include "pm_target_information.h"

/*===========================================================================

                     coincell TYPES AND STRUCTURES 

===========================================================================*/
typedef struct
{
  pm_register_address_type peripheral_offset;
  pm_register_address_type en_ctl;                  //0x046
  pm_register_address_type coin_chg_rset;           //0x044
  pm_register_address_type coin_chg_vset;           //0x045

} pm_coincell_register_info_type;


typedef struct
{
  pm_comm_info_type               *comm_ptr;
  pm_coincell_register_info_type  *coincell_reg_table;
  uint8                            num_of_peripherals;
  pm_register_address_type         base_address;
  uint8                            dig_maj_min_ver;
}pm_coincell_data_type;


/*===========================================================================

                     FUNCTION DECLARATION 

===========================================================================*/
void pm_coincell_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint8 pmic_index);

pm_coincell_data_type* pm_coincell_get_data(uint8 pmic_index);

uint8 pm_coincell_get_num_peripherals(uint8 pmic_index);

#endif // __PM_COINCELL_DRIVER_H__

