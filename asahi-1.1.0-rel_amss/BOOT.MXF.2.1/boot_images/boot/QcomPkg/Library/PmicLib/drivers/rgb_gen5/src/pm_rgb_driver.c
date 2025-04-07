/*! \file pm_rgb_driver.c
*  \n
*  \brief This file contains RGB peripheral driver initialization during which the driver data is stored.
*  \n
*  Copyright (c) 2012,2023 Qualcomm Technologies, Inc. All rights reserved.
*  Confidential and Proprietary - Qualcomm Technologies, Inc.
*/

/* =======================================================================

$Header: //components/dev/core.boot/6.1.1/samakash.core.boot.6.1.1.vce_VDD_Modem/QcomPkg/Library/PmicLib/drivers/rgb/src/pm_rgb_driver.c#1 $
$Author: samakash $
$DateTime: 2023/09/29 10:58:43 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
11/12/17   aab     Moved common Register address defination to driver file
08/20/14   al      Updating comm lib
08/29/14   al      KW fixes
05/20/14   al      Architecture update
05/09/14   va      Using common debug and assert Marco
02/27/13   aab     Creation
========================================================================== */

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_rgb_driver.h"
#include "CoreVerify.h"

/*===========================================================================

                        MACROS AND TYPE DEFINITIONS

===========================================================================*/
#define PMIC_RGB_MAX_HW_VER 0x10

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

/* Static global variable to store the RGB driver data */
static pm_rgb_data_type *pm_rgb_data_arr[PM_MAX_NUM_PMICS];

static pm_rgb_register_info_type rgb_reg =
{
  .peripheral_offset =  0x100,
  .src_sel           =  0x045,
  .en_ctl            =  0x046,
  .chgr_led_config   =  0x058,
};





/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
void pm_rgb_driver_init(pm_comm_info_type *comm_ptr, peripheral_info_type *peripheral_info, uint32 pmic_index)
{
  pm_rgb_data_type *rgb_ptr = NULL;
  uint8 num_of_peripherals = 0;

  rgb_ptr = pm_rgb_data_arr[pmic_index];

  if (rgb_ptr == NULL)
  {
    num_of_peripherals = pm_target_information_get_periph_count_info(PM_PROP_RGB_NUM, pmic_index);
    
    if (num_of_peripherals == 0)
    {
      return;
    }
    
    pm_malloc( sizeof(pm_rgb_data_type), (void**)&rgb_ptr);

    rgb_ptr->dig_maj_min_ver = ((peripheral_info->digital_major_version << 4) |
                                peripheral_info->digital_minor_version);

    CORE_VERIFY(rgb_ptr->dig_maj_min_ver <= PMIC_RGB_MAX_HW_VER);
    
    /* Assign Comm ptr */
    rgb_ptr->comm_ptr = comm_ptr;

    /* RGB Register Info - Obtaining Data through dal config */
    rgb_ptr->rgb_reg_table = &rgb_reg;

    CORE_VERIFY_PTR(rgb_ptr->rgb_reg_table);

    rgb_ptr->base_address = peripheral_info->base_address;

    rgb_ptr->num_of_peripherals = num_of_peripherals;

    rgb_ptr->sub_type = peripheral_info->peripheral_subtype;

    pm_rgb_data_arr[pmic_index] = rgb_ptr;
  }
}

pm_rgb_data_type* pm_rgb_get_data(uint32 pmic_index)
{
  if(pmic_index < PM_MAX_NUM_PMICS)
  {
    return pm_rgb_data_arr[pmic_index];
  }

  return NULL;
}

uint8 pm_rgb_get_num_peripherals(uint32 pmic_index)
{
  if((pmic_index < PM_MAX_NUM_PMICS) && (pm_rgb_data_arr[pmic_index] !=NULL))
  {
    return pm_rgb_data_arr[pmic_index]->num_of_peripherals;
  }

  return 0;
}



