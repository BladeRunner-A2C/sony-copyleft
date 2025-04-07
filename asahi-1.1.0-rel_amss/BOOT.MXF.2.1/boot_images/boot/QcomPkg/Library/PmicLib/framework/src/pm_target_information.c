/*! \file pm_target_information.c
*
*  \brief This file contains target specific PMIC settings common across processors.
*  \n
*  &copy; Copyright 2012-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/framework/src/pm_target_information.c#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when        who       what, where, why
--------    ---       ----------------------------------------------------------
06/25/15    al          removing loader specific API from common file
11/19/14    al          Re-naming to target
11/12/14    al          Removing not required include
10/17/14    aab         Added pm_target_information_spmi_chnl_cfg
07/16/14    akm         Comm change Updates
03/31/14    akm         Updated to the latest PMIC driver architecture
09/19/13    aab         Added support for SBL_REG_CONFIG and PBS_RAM_CONFIG
12/06/12    hw          Architecture change from Module to Peripheral based driver
08/07/12    hs          Added support for 5V boost.
04/16/12    hs          Removed irq files.
04/03/10    wra         Creating file for MSM8960
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_target_information.h"
#include "pm_version.h"
#include "pm_comm.h"
#include "device_info.h"
#include "CoreVerify.h"
#include "pm_config_setting.h"

/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/
static boolean pm_target_info_init = FALSE;
static boolean pm_target_common_info_init = FALSE;
static boolean pm_target_img_info_init = FALSE;

static void* pm_config_data_arr[PM_PROP_MAX] = {NULL};

/*===========================================================================

                     FUNCTION DEFINITIONS

===========================================================================*/

pm_err_flag_type pm_target_information_init(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  /*
   * Runtime detection to support multiple PMIC configuration on any target.
   * We're only concerned with the primary PMIC here so we use index 0.
  */
  err_flag = pm_config_common_populate_settings( pm_config_data_arr, PM_PROP_MAX);

  if(err_flag == PM_ERR_FLAG_SUCCESS)
  {
    pm_target_common_info_init = TRUE;
    pm_target_info_init = pm_target_common_info_init && pm_target_img_info_init;
  } 

  return err_flag;
}

void 
pm_update_img_init_status(boolean pm_image_init_status)
{
  pm_target_img_info_init = pm_image_init_status;
  pm_target_info_init = pm_target_common_info_init && pm_target_img_info_init;
}

boolean
pm_target_information_initialized(void)
{
  return pm_target_info_init;
}

pm_err_flag_type
pm_target_information_data_arr(void ***config_data_arr, uint32 *config_arr_size)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if((config_data_arr == NULL) || (config_arr_size == NULL))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  *config_data_arr = pm_config_data_arr;
  *config_arr_size = PM_PROP_MAX;

  return err_flag;
}

enum
{
  DIGITAL_MINOR = 0,
  DIGITAL_MAJOR = 1,
  ANALOG_MINOR = 2,
  ANALOG_MAJOR = 3,
  PERIPH_TYPE = 4,
  PERIPH_SUBTYPE = 5,
  NUM_OF_BYTES,
};

pm_err_flag_type
pm_target_information_read_peripheral_rev(pm_comm_info_type *comm_ptr,
                                        peripheral_info_type *peripheral_info)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_register_data_type temp_peripheral_info[NUM_OF_BYTES] = {0};

  if((NULL == comm_ptr) || (peripheral_info == NULL))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  pm_register_address_type base_address = (pm_register_address_type)peripheral_info->base_address;

  /* Burst read the peripheral info */
  err_flag = pm_comm_read_byte_array_ex(comm_ptr->bus_id, comm_ptr->slave_id, base_address,
                                        NUM_OF_BYTES, temp_peripheral_info);

  /* Valid peripheral type can never be 0 */
  if(temp_peripheral_info[PERIPH_TYPE] == 0)
  {
    return err_flag | PM_ERR_FLAG_INVALID_PERIPHERAL;
  }

  peripheral_info->peripheral_type = temp_peripheral_info[PERIPH_TYPE];
  peripheral_info->peripheral_subtype = temp_peripheral_info[PERIPH_SUBTYPE];
  peripheral_info->digital_major_version = temp_peripheral_info[DIGITAL_MAJOR];
  peripheral_info->digital_minor_version = temp_peripheral_info[DIGITAL_MINOR];
  peripheral_info->analog_major_version = temp_peripheral_info[ANALOG_MAJOR];
  peripheral_info->analog_minor_version = temp_peripheral_info[ANALOG_MINOR];

  return err_flag;
}

void*
pm_target_information_get_specific_info(uint32 prop_id)
{
  return (prop_id < PM_PROP_MAX) ? pm_config_data_arr[prop_id] : NULL;
}

uint32
pm_target_information_get_periph_count_info(uint32 prop_id,
                                              uint8 pmic_index)
{
  uint32 *count = NULL;

  if((count = (uint32*)pm_target_information_get_specific_info(prop_id)) != NULL)
  {
    if(pmic_index < PM_MAX_NUM_PMICS)
    {
      return *(count + pmic_index);
    }
  }

  return 0;
}
