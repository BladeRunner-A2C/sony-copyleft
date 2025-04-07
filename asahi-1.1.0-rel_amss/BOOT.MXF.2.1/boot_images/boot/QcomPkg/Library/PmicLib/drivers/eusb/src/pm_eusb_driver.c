/*! \file pm_eusb_driver.c
*  \n
*  \brief This file contains eusb peripheral driver initialization during which the driver data is stored.
*  \n
*  \n &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

  $Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/drivers/eusb/src/pm_eusb_driver.c#1 $

$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/06/22   akm     Implement EUSB driver
========================================================================== */

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_eusb_driver.h"
#include "CoreVerify.h"

/*===========================================================================

                        MACRO AND TYPE DEFINITIONS

===========================================================================*/
#define PMIC_EUSB_MAX_HW_VER 0x02

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/* Static global variable to store the EUSB data */
static pm_eusb_data_type *pm_eusb_data_arr[PM_MAX_BUSES_SUPPORTED][PM_MAX_NUM_PMICS];

static pm_eusb_register_info_type eusb_reg =
{
  .eusb_rptr_sts    = 0x08,
  .eusb_eusb_en     = 0x46,
};


/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void 
pm_eusb_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index, uint32 bus_id)
{
  pm_eusb_data_type *eusb_ptr = pm_eusb_data_arr[bus_id][pmic_index];

  if (NULL == eusb_ptr)
  {
    pm_malloc(sizeof(pm_eusb_data_type), (void**)&eusb_ptr);
    CORE_VERIFY_PTR(eusb_ptr);
    
    eusb_ptr->dig_maj_min_ver = ((peripheral_info->digital_major_version << 0x4) | 
                                (peripheral_info->digital_minor_version));

    CORE_VERIFY (eusb_ptr->dig_maj_min_ver <= PMIC_EUSB_MAX_HW_VER);

    /* Assign Comm ptr */
    eusb_ptr->comm_ptr = comm_ptr;

    eusb_ptr->eusb_reg_table = &eusb_reg;

    eusb_ptr->base_address = peripheral_info->base_address;

    eusb_ptr->num_of_peripherals = 1;

    pm_eusb_data_arr[bus_id][pmic_index] = eusb_ptr;
  }
  else
  {
    eusb_ptr->num_of_peripherals++;
  }
}

pm_eusb_data_type* 
pm_eusb_get_data(uint32 bus_id, uint32 pmic_index)
{
  return ((pmic_index < PM_MAX_NUM_PMICS) && (bus_id < PM_MAX_BUSES_SUPPORTED)) ? pm_eusb_data_arr[bus_id][pmic_index] : NULL;
}

