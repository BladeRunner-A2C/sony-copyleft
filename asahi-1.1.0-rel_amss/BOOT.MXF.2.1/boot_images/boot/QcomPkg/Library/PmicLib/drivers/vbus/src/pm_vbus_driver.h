#ifndef __PM_VBUS_DRIVER_H__
#define __PM_VBUS_DRIVER_H__

/*! \file pm_vbus_driver.h
*  \n
*  \brief  This file contains functions prototypes and variable/type/constant
*         declarations for supporting vbus peripheral.
*
*  \n &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.


when       who      what, where, why
--------   ---      ----------------------------------------------------------
09/08/22   xj       Porting VBUS driver from core.boot.5.1.1
========================================================================== */

/*===========================================================================
            INCLUDE FILES
===========================================================================*/


#include "pm_target_information.h"
#include "pm_comm.h"

/*===========================================================================

                     VBUS TYPES AND STRUCTURES

===========================================================================*/
typedef struct
{
  pm_register_address_type perph_type;        //0x04
  pm_register_address_type perph_subtype;     //0x05
  pm_register_address_type vbus_det_status1;  //0x08
  pm_register_address_type int_rt_sts;        //0x10
  pm_register_address_type int_set_type;      //0x11
  pm_register_address_type int_polarity_high; //0x12
  pm_register_address_type int_polarity_low;  //0x13
  pm_register_address_type int_latched_clr;   //0x14
  pm_register_address_type int_en_set;        //0x15
  pm_register_address_type int_en_clr;        //0x16
  pm_register_address_type int_latched_sts;   //0x18
  pm_register_address_type int_pending_sts;   //0x19
  pm_register_address_type int_mid_sel;       //0x1A
  pm_register_address_type int_priority;      //0x1B
} pm_vbus_register_info_type;


typedef struct
{
  pm_comm_info_type            *comm_ptr;
  pm_register_address_type     base_address;
  pm_vbus_register_info_type   *vbus_register;
  uint8                        num_of_peripherals;
}pm_vbus_data_type;


/*===========================================================================

                     FUNCTION DECLARATION

===========================================================================*/
void pm_vbus_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index);

pm_vbus_data_type* pm_vbus_get_data(uint32 pmic_index);


#endif // __PM_VBUS_DRIVER_H__

