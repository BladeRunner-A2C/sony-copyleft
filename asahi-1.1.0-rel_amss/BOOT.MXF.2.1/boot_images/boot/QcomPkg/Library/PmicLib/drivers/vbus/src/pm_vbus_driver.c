/*! \file pm_vbus_driver.c
*  \n
*  \brief This file contains vbus peripheral driver initialization during which the driver data is stored.
*  \n
*  \n &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/08/22   xj      Porting VBUS driver from core.boot.5.1.1
========================================================================== */

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_vbus_driver.h"
#include "CoreVerify.h"

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/* Static global variable to store the VBUS data */
static pm_vbus_data_type *pm_vbus_data_arr[PM_MAX_NUM_PMICS];

static pm_vbus_register_info_type vbus_reg =
{
  .perph_type        = 0x04,
  .perph_subtype     = 0x05,
  .vbus_det_status1  = 0x08,
  .int_rt_sts        = 0x10,
  .int_set_type      = 0x11,
  .int_polarity_high = 0x12,
  .int_polarity_low  = 0x13,
  .int_latched_clr   = 0x14,
  .int_en_set        = 0x15,
  .int_en_clr        = 0x16,
  .int_latched_sts   = 0x18,
  .int_pending_sts   = 0x19,
  .int_mid_sel       = 0x1A,
  .int_priority      = 0x1B,
};


/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void pm_vbus_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index)
{
  pm_vbus_data_type *vbus_ptr = pm_vbus_data_arr[pmic_index];

  if(NULL == vbus_ptr)
  {
    pm_malloc(sizeof(pm_vbus_data_type), (void**)&vbus_ptr);
    CORE_VERIFY_PTR(vbus_ptr);

    /* Assign Comm ptr */
    vbus_ptr->comm_ptr = comm_ptr;

    vbus_ptr->vbus_register = &vbus_reg;

    vbus_ptr->base_address = peripheral_info->base_address;

    vbus_ptr->num_of_peripherals = pm_target_information_get_periph_count_info(PM_PROP_VBUS_NUM, pmic_index);
    CORE_VERIFY(vbus_ptr->num_of_peripherals != 0);

    pm_vbus_data_arr[pmic_index] = vbus_ptr;
  }
}


pm_vbus_data_type* pm_vbus_get_data(uint32 pmic_index)
{
  return (pmic_index < PM_MAX_NUM_PMICS) ? pm_vbus_data_arr[pmic_index] : NULL;
}

