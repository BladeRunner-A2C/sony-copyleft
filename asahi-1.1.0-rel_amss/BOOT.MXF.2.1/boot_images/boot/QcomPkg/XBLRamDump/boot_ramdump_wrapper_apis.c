/*=============================================================================

                       Boot Shared Functions Consumer

GENERAL DESCRIPTION
  This file contains definitions of functions for boot ramdump must functions

Copyright 2020 - 2021, 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
02/23/23   suhas   Integrated BootPartitionLib
02/15/23   ck      Renamed edk2 interfaces
07/02/21   rama    Fix error handling in read_ddr_training_data_from_partition
05/24/21   yps     Fixed Raw dump issue with when switch partition.
05/27/20   yps     Intial creation
=============================================================================*/

#include <boot_config_context.h>
#include <boot_framework.h>
#include <boot_ramdump_if.h>
#include <boot_dal_if.h>
#include <boot_clk_if.h>
#include <boot_pmic_if.h>
#include <boot_qsee_if.h>
#include <boot_whitelist_if.h>
#include <boot_smem_if.h>
#include <boot_logger_if.h>
#include <boot_ddr_info_if.h>
#include <boot_platforminfo_if.h>
#include <boot_coldplug_if.h>
#include <boot_shared_imem_cookie.h>
#include <boot_media_interface_if.h>
#include <boot_cache_if.h>
#include <boot_arm_if.h>
#include "secboot_hw.h"
#include "boot_sbl_shared.h"
#include "coldplug_api.h"
#include "boot_partition.h"


bl_error_boot_type  read_ddr_training_data_from_partition(uint8 * ddr_training_data_buf, uint64 offset, uint64 size )
{
  bl_error_boot_type return_status = BL_ERR_NONE, temp_status = BL_ERR_NONE;
  boot_media_interface_if_type *media_if = NULL;
  boot_handle media_handle = NULL;
  boot_handle crt_handle = NULL;
  uint32 pbl_media_boot_device = 0;
  uint32 boot_device = 0;
  struct coldplug_guid *previous_partition_id = NULL;
  boot_media_family media_family = BOOT_MEDIA_FAMILY_MAX;
  boot_partition_if_type * partition_if = NULL;
  const uint8 * ddr_partition_id = NULL;
  uint8 ddr_partition_id_size = 0;
  do
  {
    return_status = boot_config_context_get_crt_handle(&crt_handle);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = boot_config_context_get_value(crt_handle, CONFIG_CONTEXT_BOOT_DEVICE, (void *)&boot_device);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }
    /* backup boot media device */
    return_status = boot_config_context_get_value(crt_handle, CONFIG_CONTEXT_PBL_MEDIA_BOOT_DEVICE, (void *)&pbl_media_boot_device);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }
    /* backup current partition GUID */
    return_status = boot_config_context_get_ptr(crt_handle, CONFIG_CONTEXT_PARTITION_ID, (void **)(uintptr_t)&previous_partition_id);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }
    
    return_status = boot_config_context_set_value(crt_handle, CONFIG_CONTEXT_BOOT_DEVICE, pbl_media_boot_device);
    if(return_status != BL_ERR_NONE)
    {
      break;
    }


    /* get media family */
    return_status = get_boot_media_family(pbl_media_boot_device,
                                          &media_family);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    
    /* get interface pointer to BootPartitionLib */
    return_status = boot_config_context_get_ptr(crt_handle,
                                                CONFIG_CONTEXT_PARTITION_INTERFACE,
                                                (void **)&partition_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
    /* Null Pointer Check */
    if (partition_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION,
                                     BL_ERR_NULL_PTR_PASSED);
      break;
    }


    /* get partition id using BootPartitionLib */
    return_status = partition_if->get_partition_id_by_partition(media_family,
                                                                IMAGE_SET_A,
                                                                DDR_TRAINING_PARTITION,
                                                                &ddr_partition_id,
                                                                &ddr_partition_id_size);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }


    /* set DDR partition GUID */
    return_status = boot_config_context_set_ptr(crt_handle, 
                                                CONFIG_CONTEXT_PARTITION_ID, 
                                                (void *)ddr_partition_id);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = boot_config_context_get_ptr(crt_handle, CONFIG_CONTEXT_BOOT_MEDIA_INTERFACE, (void **)&media_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = media_if->open(crt_handle, &media_handle);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = media_if->read(media_handle, (void *)ddr_training_data_buf, offset, size);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
  } while (FALSE);

  do
  {
    if (media_handle!= NULL)
    {
      temp_status = media_if->close(media_handle);
      if (temp_status != BL_ERR_NONE)
      {
        return_status = temp_status;
        break;
      }
    }
    
    /* restore boot media device */
    temp_status = boot_config_context_set_value(crt_handle, CONFIG_CONTEXT_BOOT_DEVICE, boot_device);
    if (temp_status != BL_ERR_NONE)
    {
      return_status = temp_status;
      break;
    }
    /* restore previous partition GUID */
    return_status = boot_config_context_set_ptr(crt_handle, CONFIG_CONTEXT_PARTITION_ID, previous_partition_id);
    if (temp_status != BL_ERR_NONE)
    {
      return_status = temp_status;
      break;
    }   
  }while (FALSE);
  return return_status;
}

boolean boot_PlatformInfo_IsFusion(void)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_platforminfo_if_type *platforminfo_if = NULL;

  return_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PLATFORMINFO_INTERFACE, (void **)&platforminfo_if);
  if (return_status != BL_ERR_NONE)
    return 0;

  return platforminfo_if->IsFusion();
}

/* SONY_BEGIN(Ramdumper support) */
#ifdef FEATURE_SONY_RAMDUMP
pm_err_flag_type boot_pm_dev_get_power_on_reason(unsigned pmic_device_index,
                                                 uint64 * pwr_on_reason)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_pmic_if_type *pmic_if = NULL;

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PMIC_INTERFACE, (void **)&pmic_if);
  if(status != BL_ERR_NONE)
    return 0;

  return pmic_if->pm_dev_get_power_on_reason(pmic_device_index, pwr_on_reason);
}
#endif /* FEATURE_SONY_RAMDUMP */
/* SONY_END(Ramdumper support) */
