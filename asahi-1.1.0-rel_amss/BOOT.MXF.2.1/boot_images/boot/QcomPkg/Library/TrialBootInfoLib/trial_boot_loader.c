/*===========================================================================

                       Trial Boot Loader Source File

GENERAL DESCRIPTION
  This file contains functions to read/write Trial Boot Info to trial_boot_info_partition

Copyright 2021, 2023 Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
02/23/23   suhas   Integrated BootPartitionLib
01/15/23   suhas   Included boot_partition_legacy.h
05/27/21   sp      Initial Revision
=============================================================================*/

/*=============================================================================
                            INCLUDE FILES FOR MODULE
=============================================================================*/
#include <TrialBootInfoLib.h>
#include <boot_partition_rw.h>
#include <trial_boot_info.h>
#include <coldplug_api.h>
#include <boot_partition.h>
#include <boot_partition_legacy.h>
#include <boot_config_context.h>
#include <boot_error_if.h>
#include <boot_media_interface_if.h>

static trial_boot_info_type trial_boot_info;
uint32 trial_boot_info_size = sizeof(trial_boot_info_type);

/*==============================================================================
**  Functions
**============================================================================*/

/*=========================================================================

**  Function :  tbi_read_partition

** ==========================================================================
*/
/*!
*
* @brief
*   This api reads trial boot info from storage
*
*/
trial_boot_status tbi_get_trial_boot_info(trial_boot_info_type **trial_boot_info_ptr)
{
  boolean read_status = FALSE;
  trial_boot_status status = TBI_SUCCESS;
  bl_error_boot_type bl_status = BL_ERR_NONE;
  boot_media_family media_family = BOOT_MEDIA_FAMILY_MAX;
  boot_partition_if_type * partition_if = NULL;
  boot_media_type boot_device = NO_FLASH;
  boot_image_set_t current_image_set = IMAGE_SET_MAX;
  const uint8 * partition_id = NULL;
  uint8 partition_id_size = 0;


  do
  {
    /* Get boot device */
    bl_status = boot_config_context_get_value(CONFIG_CONTEXT_CRT_HANDLE,
                                              CONFIG_CONTEXT_BOOT_DEVICE,
                                              (void *)&boot_device);

    if (bl_status != BL_ERR_NONE)
    {
      status = TBI_ERR;
      break;
    }


    bl_status = boot_config_context_get_value(CONFIG_CONTEXT_CRT_HANDLE,
                                              CONFIG_CONTEXT_CURRENT_IMAGE_SET,
                                              (void *)&current_image_set);

    if (bl_status != BL_ERR_NONE)
    {
      status = TBI_ERR;
      break;
    }


    /* Get Media family */
    bl_status = get_boot_media_family(boot_device,
                                      &media_family);

    if (bl_status != BL_ERR_NONE)
    {
      status = TBI_ERR;
      break;
    }


    /* Get partition interface pointer */
    bl_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, 
                                            CONFIG_CONTEXT_PARTITION_INTERFACE, 
                                            (void **)&partition_if);
  
    if (bl_status != BL_ERR_NONE)
    {
      status = TBI_ERR;
      break;
    }

    /* Null pointer check */
    if (partition_if == NULL)
    {
      bl_status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION,
                                 BL_ERR_NULL_PTR_PASSED);
      status = TBI_ERR;
      break;
    }


    /* Get partition id */
    bl_status = partition_if->get_partition_id_by_partition(media_family,
                                                            current_image_set,
                                                            TRAIL_BOOT_INFO_PARTITION,
                                                            &partition_id,
                                                            &partition_id_size);
  
    if (bl_status != BL_ERR_NONE)
    {
      status = TBI_ERR;
      break;
    }


    if(trial_boot_info_ptr == NULL)
    {
      status = TBI_NULL_PTR;
      break;
    }

    *trial_boot_info_ptr = &trial_boot_info;

    if(trial_boot_info.magic_cookie == TBI_MAGIC_COOKIE)
    {
      break;
    }

    read_status = boot_read_from_partition((uint8*)partition_id, NULL, 0, (uint8*)&trial_boot_info, trial_boot_info_size);
    if(read_status != TRUE)
    {
      status = TBI_READ_ERR;
      break;
    }

    if(trial_boot_info.magic_cookie != TBI_MAGIC_COOKIE)
    {
      trial_boot_info.magic_cookie = TBI_MAGIC_COOKIE;
      trial_boot_info.version = TBI_VERSION;
      trial_boot_info.trial_boot_max_attempts = TBI_MAX_ATTEMPTS;
      trial_boot_info.trial_boot_enable = 0;
      trial_boot_info.trial_boot_failed_attempts = 0;
      trial_boot_info.partition_table_restore_enable = 0;
      trial_boot_info.partition_table_restore_status = 0;
      trial_boot_info.image_set_to_boot = 0;
    }
  }while(FALSE);

  return status;
}

/*=========================================================================

**  Function :  tbi_write_partition

** ==========================================================================
*/
/*!
*
* @brief
*   This api writes trial boot info to storage
*
*/
trial_boot_status tbi_write_partition(trial_boot_info_type *trial_boot_info_ptr)
{
  boolean write_status = FALSE;
  trial_boot_status status = TBI_SUCCESS;
  bl_error_boot_type bl_status = BL_ERR_NONE;
  boot_media_family media_family = BOOT_MEDIA_FAMILY_MAX;
  boot_partition_if_type * partition_if = NULL;
  boot_media_type boot_device = NO_FLASH;
  boot_image_set_t current_image_set = IMAGE_SET_MAX;
  const uint8 * partition_id = NULL;
  uint8 partition_id_size = 0;

  
  /* Get boot device */
  bl_status = boot_config_context_get_value(CONFIG_CONTEXT_CRT_HANDLE,
                                            CONFIG_CONTEXT_BOOT_DEVICE,
                                            (void *)&boot_device);

  if (bl_status != BL_ERR_NONE)
  {
    status = TBI_ERR;
    goto exit;
  }


  bl_status = boot_config_context_get_value(CONFIG_CONTEXT_CRT_HANDLE,
                                            CONFIG_CONTEXT_CURRENT_IMAGE_SET,
                                            (void *)&current_image_set);

  if (bl_status != BL_ERR_NONE)
  {
    status = TBI_ERR;
    goto exit;
  }


  /* Get Media family */
  bl_status = get_boot_media_family(boot_device,
                                    &media_family);

  if (bl_status != BL_ERR_NONE)
  {
    status = TBI_ERR;
    goto exit;
  }


  /* get partition interface pointer */
  bl_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, 
                                          CONFIG_CONTEXT_PARTITION_INTERFACE, 
                                          (void **)&partition_if);

  if (bl_status != BL_ERR_NONE)
  {
    status = TBI_ERR;
    goto exit;
  }

  /* Null pointer check */
  if (partition_if == NULL)
  {
    bl_status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION,
                               BL_ERR_NULL_PTR_PASSED);
    status = TBI_ERR;
    goto exit;
  }


  /* get partition id */
  bl_status = partition_if->get_partition_id_by_partition(media_family,
                                                          current_image_set,
                                                          TRAIL_BOOT_INFO_PARTITION,
                                                          &partition_id,
                                                          &partition_id_size);

  if (bl_status != BL_ERR_NONE)
  {
    status = TBI_ERR;
    goto exit;
  }


  write_status = boot_write_to_partition((uint8*)partition_id, NULL, 0, (uint8*)trial_boot_info_ptr, trial_boot_info_size);
  if(write_status != TRUE)
  {
    status = TBI_WRITE_ERR;
  }
  

 exit:
  return status;
}


