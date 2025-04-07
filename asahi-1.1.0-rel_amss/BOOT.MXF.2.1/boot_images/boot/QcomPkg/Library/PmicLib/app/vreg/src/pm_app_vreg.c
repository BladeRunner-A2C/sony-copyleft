/*! \file
*  
*  \brief  pm_app_vreg.c
*  \details Implementation file for vreg app API.
*    
*  &copy; Copyright 2016-2017, 2023 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================
EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.

$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/app/vreg/src/pm_app_vreg.c#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
10/20/17   czq     Add bob OCP checking and cleraing. 
11/02/16   aab     Creation
===========================================================================*/

/*===========================================================================

                             INCLUDE FILES 

===========================================================================*/
#include "pm_err_flags.h"
#include "pm_config_target.h"  
#include "pm_app_vreg.h"
#include "pm_ldo.h"
#include "pm_smps.h"
#include "pm_bob.h"
#include "pm_smps_driver.h"
#include "pm_ldo_driver.h"
#include "pm_bob_driver.h"
#include "pm_log_utils.h"

/*===========================================================================

                          MACROS AND DEFINITIONS

===========================================================================*/

static pm_err_flag_type pm_log_ocp_info(uint32 pmic_index, uint8 periph_index, pm_vreg_ocp_info_type ocp_info);

/*===========================================================================

                            API Implementation

===========================================================================*/

pm_err_flag_type
pm_app_vreg_clear_ocp_status(void)
{
  pm_err_flag_type       err_flag = PM_ERR_FLAG_SUCCESS;
  pm_vreg_ocp_info_type  ocp_info = {0};
  uint32 pmic_index = 0;
  uint8 smps_count = 0;
  uint8 ldo_count = 0;
  uint8 bob_count = 0;
  uint8 num_smps_periph = 0;
  uint8 num_ldo_periph  = 0;
  uint8 num_bob_periph = 0;
  
  for(pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
  {
       //SMPS
       num_smps_periph = pm_smps_get_num_peripherals(pmic_index);
       for (smps_count = PM_SMPS_1; smps_count < num_smps_periph; smps_count++)
       {
          /*err_flag |=*/ pm_smps_ocp_latched_status_clear(pmic_index, smps_count, &ocp_info);//If OCP occured clear status
           err_flag |= pm_log_ocp_info(pmic_index, smps_count + 1, ocp_info);
       }

       //LDO
       num_ldo_periph = pm_ldo_get_num_peripherals(pmic_index);
       for (ldo_count = PM_LDO_1; ldo_count < num_ldo_periph; ldo_count++)
       {
          err_flag |= pm_ldo_ocp_latched_status_clear(pmic_index, ldo_count, &ocp_info); //If OCP occured clear status
          err_flag |= pm_log_ocp_info(pmic_index, ldo_count + 1, ocp_info);
       }
	   
	   //BOB
       num_bob_periph = pm_bob_get_num_peripherals(pmic_index);
       for (bob_count = PM_BOB_1; bob_count < num_bob_periph; bob_count++)
       {
          err_flag |= pm_bob_ocp_latched_status_clear(pmic_index, bob_count, &ocp_info);//If OCP occured clear status
          err_flag |= pm_log_ocp_info(pmic_index, bob_count + 1, ocp_info);
       }
   }

  return err_flag;
}


static pm_err_flag_type 
pm_log_ocp_info(uint32 pmic_index, uint8 periph_index, pm_vreg_ocp_info_type ocp_info)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  
  if (ocp_info.ocp_occured) 
  {
    if (ocp_info.is_ocp_mode_supported)
    {
      pm_log_message("OCP Occured: PMIC: %d; %s: %d; Status: 0x%02X ", pmic_index, ocp_info.vreg_type, periph_index, ocp_info.ocp_mode_status); 
    }
    else
    {
      pm_log_message("OCP Occured: PMIC: %d; %s: %d ", pmic_index, ocp_info.vreg_type, periph_index);
    }
  }

  return err_flag;
}

