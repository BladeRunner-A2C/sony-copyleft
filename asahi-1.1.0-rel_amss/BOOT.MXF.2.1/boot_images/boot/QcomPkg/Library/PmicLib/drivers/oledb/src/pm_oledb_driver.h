#ifndef __PM_OLEDB_DRIVER_H__
#define __PM_OLEDB_DRIVER_H__

/*! \file pm_oledb _driver.h
 *  \n
 *  \brief This file contains functions prototypes and variable/type/constant
*          declarations for supporting OLEDB peripheral
 *  \n
 *  \n &copy;
 *  Copyright (c) 2018 - 2020 Qualcomm Technologies, Inc.  All Rights Reserved.
 *  Qualcomm Technologies Proprietary and Confidential.
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/drivers/oledb/src/pm_oledb_driver.h#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/06/18   al      Initial revision
========================================================================== */
/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_target_information.h"

/*===========================================================================

                     STRUCTURE TYPE AND ENUM

===========================================================================*/


/************************************************************************/
/* register definitions                                                 */
/************************************************************************/

typedef struct
{
  pm_register_address_type    module_rdy;                          //0x045
  pm_register_address_type    module_enable;                       //0x046
  pm_register_address_type    ext_pin_ctl;                         //0x047
  pm_register_address_type    mode_config;                         //0x048
  pm_register_address_type    vout_pgm;                            //0x049
  pm_register_address_type    vout_default_ctl;                    //0x04A
}pm_oledb_register_info_type;


typedef struct
{
  pm_comm_info_type            *comm_ptr;
  pm_oledb_register_info_type  *oledb_reg_table;
  uint32                       base_address;
  uint8                        num_of_peripherals;
  uint8                        dig_maj_min_ver;
}pm_oledb_data_type;


/*===========================================================================

                     FUNCTION DECLARATION

===========================================================================*/
void pm_oledb_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index);

pm_oledb_data_type* pm_oledb_get_data(uint32 pmic_index);

uint8 pm_oledb_get_num_peripherals(uint32 pmic_index);

#endif // __PM_OLEDB_DRIVER_H__
