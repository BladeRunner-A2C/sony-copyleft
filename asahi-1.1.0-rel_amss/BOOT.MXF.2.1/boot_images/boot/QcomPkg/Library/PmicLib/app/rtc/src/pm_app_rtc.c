/*! \file
*  
*  \brief  pm_app_rtc.c
*  \details Implementation file for rtc resourece type.
*
*  &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/app/rtc/src/pm_app_rtc.c#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when        who     what, where, why
--------    ---     ---------------------------------------------------------- 
01/06/2022  dv      Initial app layer developement for RTC
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_err_flags.h"
#include "pm_app_rtc.h"
#include "pm_rtc_driver.h"
#include "pm_sdam.h"
#include "pm_target_information.h"


pm_err_flag_type 
pm_app_rtc_update_status( void )
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  boolean status = FALSE;
  pm_rtc_app_config *pm_rtc_config = NULL;

  pm_rtc_config = pm_target_information_get_specific_info(PM_PROP_RTC_APP_CONFIG);  
  if(NULL == pm_rtc_config)
  {
	  return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  err_flag = pm_rtc_reset_status(pm_rtc_config->rtc_pmic, &status);

  if ((err_flag == PM_ERR_FLAG_SUCCESS) && status)
  {
    err_flag |= pm_sdam_mem_write (pm_rtc_config->rtc_pmic, pm_rtc_config->rtc_sdam, pm_rtc_config->rtc_sdam_mem, 1, &status);
    err_flag |= pm_rtc_clear_reset_status(pm_rtc_config->rtc_pmic);
  }

  return err_flag;
}

