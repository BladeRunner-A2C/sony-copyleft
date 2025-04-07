/*===========================================================================

                       Boot Partition Lib Legacy Source File

GENERAL DESCRIPTION
  This file contains functions to set or get partition ids

Copyright 2022 - 2023 Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
01/26/23   suhas   Removed boot_set_partition_ids and boot_set_recovery_partition_ids_to_null
12/21/22   suhas   Renamed it to boot_partition_legacy.c
11/21/22   sp      Initial Revision
=============================================================================*/

/*=============================================================================
                            INCLUDE FILES FOR MODULE
=============================================================================*/

#include <string.h>
#include <boot_config_context.h>
#include <boot_error_if.h>
#include <boot_partition_legacy.h>
#include <boot_media_types.h>
#include <boot_media_interface_if.h>
#include <boot_config_context.h>
#include <boot_partition.h>
#include <boot_config.h>
#include <boot_memory_mgr_if.h>

extern boot_configuration_table_entry sbl1_config_table[];


/*===========================================================================
**  Function :  boot_media_restore_partition_table
** ==========================================================================
*/
/*!
* 
* @brief
*   Calls into storage api to restore recovery patition table using ioctl
*
* @param[in] None
*
*
*/
bl_error_boot_type boot_media_restore_partition_table(boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_media_interface_if_type *media_if = NULL;
  boot_memory_mgr_if_type * mem_if = NULL;
  boot_handle media_handle = NULL;
  partition_table_restore_ioctl_params *ioctl_params = NULL;
  boot_media_family media_family = BOOT_MEDIA_FAMILY_MAX;
  boot_partition_if_type * partition_if = NULL;
  boot_media_type boot_device = NO_FLASH;
  boot_image_set_t current_image_set = IMAGE_SET_MAX;
  const uint8 * partition_id = NULL;
  uint8 partition_id_size = 0;


  do
  {
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (mem_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MEMORY_MGR, BL_ERR_INTERFACE_FAILURE);
      break;
    }

    status = mem_if->malloc(sizeof(partition_table_restore_ioctl_params), (void **)&ioctl_params);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    memset((void *)ioctl_params, 0, sizeof(partition_table_restore_ioctl_params));

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_BOOT_MEDIA_INTERFACE, (void **)(&media_if));
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (media_if == NULL)
    {
      status = BL_ERROR_GROUP_BOOT_MEDIA_IF | BL_ERR_NULL_PTR_PASSED;
      break;
    }

    status = media_if->open(config_context_handle, &media_handle);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    ioctl_params -> handle = media_handle;


    /* Get boot device */
    status = boot_config_context_get_value(CONFIG_CONTEXT_CRT_HANDLE,
                                           CONFIG_CONTEXT_BOOT_DEVICE,
                                           (void *)&boot_device);

    if (status != BL_ERR_NONE)
    {
      break;
    }
  
  
    status = boot_config_context_get_value(CONFIG_CONTEXT_CRT_HANDLE,
                                           CONFIG_CONTEXT_CURRENT_IMAGE_SET,
                                           (void *)&current_image_set);

    if (status != BL_ERR_NONE)
    {
      break;
    }


    /* Get Media family */
    status = get_boot_media_family(boot_device,
                                   &media_family);

    if (status != BL_ERR_NONE)
    {
      break;
    }


    /* Get partition interface pointer */
    status = boot_config_context_get_ptr(config_context_handle, 
                                         CONFIG_CONTEXT_PARTITION_INTERFACE, 
                                         (void **)&partition_if);
  
    if (status != BL_ERR_NONE)
    {
      break;
    }

    /* Null pointer check */
    if (partition_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION,
                              BL_ERR_NULL_PTR_PASSED);
      break;
    }


    for(boot_partition_t partition_i = PARTITION_TABLE_RESTORE_PARTITION; partition_i < MAX_PARTITION; ++partition_i)
    {
      status = partition_if->get_partition_id_by_partition(media_family,
                                                           current_image_set,
                                                           partition_i,
                                                           &partition_id,
                                                           &partition_id_size);


      if (status != BL_ERR_NONE)
      {
        break;
      }

      ioctl_params -> restore_partition_id = (uint8 *)partition_id;

      status = media_if->ioctl(PARTITION_TABLE_RESTORE, ioctl_params, 0, NULL, NULL);
      if (status != BL_ERR_NONE)
      {
        break;
      }
    }
  }while(FALSE);


  if(ioctl_params != NULL)
  {
    mem_if->free((void *)ioctl_params);
  }

  return status;
}
