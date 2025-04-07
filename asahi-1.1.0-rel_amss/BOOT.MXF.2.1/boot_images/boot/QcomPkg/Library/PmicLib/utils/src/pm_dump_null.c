/*! \file  pm_dump_null.c
*  
*  \brief  pm_dump_null.c ----This file contain PMIC dump related API 
*  \details This file contain PMIC dump related API 
*  
*  &copy; Copyright 2020-2022 Qualcomm Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

EDIT HISTORY FOR MODULE

This document is created by a code generator, therefore this section will
not contain comments describing changes made to the module.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/utils/src/pm_dump_null.c#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
07/20/21   zxz     Created

===========================================================================*/

/*===========================================================================

INCLUDE FILES 

===========================================================================*/
#include "pm_dump.h"
#include "pm_comm.h"
#include "pm_prop_ids.h"
#include "pm_utils.h"
#include "pm_resource_manager.h"
#include "pm_target_information.h"
#include "CoreVerify.h"


/*===========================================================================

                        GLOBALS and TYPE DEFINITIONS 

===========================================================================*/



/*===========================================================================

                        FUNCTION DEFINITIONS 

===========================================================================*/
pm_err_flag_type pm_dump_pbus_logger(uint8* buf, uint64 offset, uint64 size, uint64* dumped_size, boolean* complete)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_pmic_dump_entry(uint8* buf, uint64 offset, uint64 size)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_dump_pmic_register(uint8* buf, uint64 offset, uint64 size, uint64* dumped_size, boolean* complete)
{
  return PM_ERR_FLAG_SUCCESS;
}

