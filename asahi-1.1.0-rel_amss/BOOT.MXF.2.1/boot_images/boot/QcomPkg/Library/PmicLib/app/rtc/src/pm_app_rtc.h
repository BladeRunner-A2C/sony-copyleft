/*! \file
*  
*  \brief  pm_app_rtc.h
*  \details Implementation file for rtc resourece type.
*
*  &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/app/rtc/src/pm_app_rtc.h#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when        who     what, where, why
--------    ---     ---------------------------------------------------------- 
01/16/2022  dv      Initial app layer developement for RTC
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "pm_err_flags.h"
#include "pm_resources_and_types.h"
#include "com_dtypes.h"
#include "pm_sdam.h"

typedef struct
{
  uint8 rtc_pmic;
  pm_sdam_type rtc_sdam;
  uint8 rtc_sdam_mem;
} pm_rtc_app_config;

/*===========================================================================
FUNCTION  pm_app_rtc_get_rtc_status                      EXTERNAL FUNCTION

DESCRIPTION
This function gets the RTC reset status

PARAMETERS
None

RETURN VALUE
Type: pm_err_flag_type
- Possible values:
- PM_ERR_FLAG_SUCCESS               -> Operation succeeded.
- PM_ERR_FLAG_INVALID_PARAMETER     -> NULL pointer provided for reset_status.
- PM_ERR_FLAG_FEATURE_NOT_SUPPORTED -> Feature not available on this
version of the PMIC.
- PM_ERR_FLAG_BUS_ERR           	-> Communication with PM chip failed.
===========================================================================*/
pm_err_flag_type 
pm_app_rtc_update_status(void);
