/*! \file pm_comm.c
*
*  \brief This file contains processor specific initialization functions.
*         This file contains code for Target specific settings and modes.
*
*  &copy; Copyright 2014 - 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


$Header: //service/BOOT/BOOT.MXF.2.1-01839-LANAI-2.65818/boot_images/boot/QcomPkg/Library/PmicLib/comm/src/pm_comm.c#1 $
$Author: cirrusp4svc $
$DateTime: 2024/04/02 23:00:31 $
when       who     what, where, why
--------   ---     ------------------------------------------------
10/12/15   aab    Updated pm_comm_info_init()
07/16/14   akm    Multiple PMIC's configuration support ( >2 PMICS)

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/
#include "pm_resource_manager.h"
#include "pm_target_information.h"
#include "pm_comm.h"
#include "hw_module_type.h"
#include "CoreVerify.h"
#include "pm_version.h"
#include "device_info.h"
#include "pm_device.h"


/* PMIC Comm Info, Each PMIC device has 1 or more slave ids */
static pm_comm_info_type *pm_comm_info = NULL ;
static boolean pm_comm_info_initialized = FALSE;

void pm_comm_info_init(void)
{
  uint32 sid_count = 0, sid_counter = 0, pmic_index = 0, slaves_per_pmic = 0, bus_id = 0;

  if(pm_comm_info_initialized)
  {
    return;
  }

  pm_malloc(PM_MAX_NUM_OF_SPMI_BUSES * PM_MAX_NUM_SLAVE_IDS * sizeof(pm_comm_info_type), (void **)&pm_comm_info);

  for(bus_id = 0; bus_id < PM_MAX_NUM_OF_SPMI_BUSES; bus_id++)
  {
    pmic_index = 0;
    while(pmic_index < PM_MAX_NUM_PMICS)
    {
      slaves_per_pmic = pm_get_num_of_sid_supported_ex(bus_id, pmic_index);

      if(slaves_per_pmic == 0)
      {
        slaves_per_pmic = pm_is_pmiclib_arch_pre7() ? 2 : 1;
      }

      for(sid_counter = 0; sid_counter < slaves_per_pmic; sid_counter++, sid_count++)
      {
        pm_comm_info[sid_count].mCommType = SPMI_1_0Type;
        pm_comm_info[sid_count].pmic_index = pmic_index;
        pm_get_slave_id_ex(bus_id, pmic_index, sid_counter, &pm_comm_info[sid_count].slave_id);
        pm_comm_info[sid_count].bus_id = bus_id;
      }
      
      if(pm_is_pmiclib_arch_pre7())
      {
        pmic_index++;
      }
      else
      {
        pmic_index += slaves_per_pmic;
      }
    }
  }

  pm_comm_info_initialized = TRUE;
}

pm_comm_info_type*
pm_comm_get_comm_info(uint32 bus_id, uint32 pmic_index, uint32 slave_id_index)
{
  uint32 comm_info_idx = 0;

  if(!pm_comm_info_initialized) return NULL;

  if(TRUE == pm_is_pmiclib_arch_pre7())
  {
    comm_info_idx = (bus_id * PM_MAX_NUM_SLAVE_IDS) + (pmic_index * pm_get_num_slaves_per_pmic()) + slave_id_index;
  }
  else
  {
    comm_info_idx = (bus_id * PM_MAX_NUM_SLAVE_IDS) + pmic_index + slave_id_index;
  }

  return &pm_comm_info[comm_info_idx];
}

boolean
pm_comm_initialized(void)
{
  return pm_comm_info_initialized;
}
