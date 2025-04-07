/*! \file
*
*  \brief  pm_utils_loader.c
*  &copy; Copyright 2016-2023 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/utils/src/pm_utils_loader.c#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/21/22   rama     Rename watchdog APIs
03/15/17   aab      Added pm_sbl_set_batt_id_forced_mode()
02/02/17   cs       SBL needs to do a fresh reading of batt id
08/03/16   akm      Created

===========================================================================*/

/*===========================================================================

INCLUDE FILES

===========================================================================*/

#include "DALSys.h"
#include "adc.h"
#include "busywait.h"
#include "boot_reset_if.h"

#include "pm_utils.h"
#include "pm_log_utils.h"

#include "pm_dump.h"
#include "pm_resource_manager.h"
#include "device_info.h"
#include "pm_target_information.h"
#include "pm_prop_ids.h"
#include "CoreVerify.h"
#include <WatchDogTimerLib.h>


pm_err_flag_type
pm_busy_wait(uint32 us)
{
  busywait(us);
  return PM_ERR_FLAG_SUCCESS;
}

void
pm_msm_watch_dog_pet(void)
{
  WatchDog_Timer1_Pet();
}

void
pm_log_message(const char* format, ...)
{
  char buffer[PM_STATUS_MSG_LEN] = "PM: ";
  va_list args = {0};

  va_start(args, format);
  vsnprintf(buffer + PM_STATUS_MSG_HEAD_LEN, PM_STATUS_MSG_LEN - PM_STATUS_MSG_HEAD_LEN, format, args);
  va_end(args);
  LogMsg(buffer);
}


pm_err_flag_type
pm_device_shutdown(void)
{
  boot_hw_powerdown();

  /*should not return*/
  return PM_ERR_FLAG_SUCCESS;
}
