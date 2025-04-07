/*=============================================================================

                            ConfigRecovery Module Sources

GENERAL DESCRIPTION
  This file defines XBL Config Recovery api's

Copyright 2023 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
03/08/23     sp      Initial version
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include <string.h>
#include <boot_cfg_recovery.h>
#include <boot_error_if.h>
#include <boot_partition.h>
#include <boot_config_context.h>
#include <boot_reset_if.h>
#include <boot_partition_rw.h>
#include <boot_media_interface_if.h>
#include <boot_recovery_partition.h>

/*=============================================================================
                              FUNCTION DEFINITIONS
=============================================================================*/
/*===========================================================================
**  Function :  cfg_image_error_handler_recovery
** ==========================================================================
*/
/*!
*
* @brief
*   This function clears first 4 bytes in the storage partition upon failure and does hard reset.
*   So on the next boot loader loads the image from secondary partition by calling cfg_select_partition api
*
* @param[in]
*  None
*
* @param[out]
*  None
*
* @par Dependencies
*   None
*
* @retval
*   status = BL_ERR_NONE if no error, else error value
*
* @par Side Effects
*   None
*
*/

bl_error_boot_type cfg_image_error_handler_recovery()
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_media_family media_family = BOOT_MEDIA_FAMILY_MAX;
  boot_partition_if_type * partition_if = NULL;
  boot_reset_if_type * reset_if = NULL;
  boot_media_type boot_device = NO_FLASH;
  uint8 * partition_id = NULL;
  const uint8 *recovery_partition_id = NULL;
  uint8 partition_id_size = 0;
  boolean write_status = FALSE;
  uint8 xcfg_buffer[] = {0, 0 ,0 , 0};
  uint8 xcfg_buffer_size = sizeof(xcfg_buffer);

  do
  {
    status = boot_config_context_get_value(CONFIG_CONTEXT_CRT_HANDLE,
                                              CONFIG_CONTEXT_BOOT_DEVICE,
                                              (void *)&boot_device);

    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = get_boot_media_family(boot_device,
                                   &media_family);

    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE,
                                         CONFIG_CONTEXT_PARTITION_INTERFACE,
                                         (void **)&partition_if);

    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (partition_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = partition_if->get_partition_id_by_partition(media_family,
                                                     IMAGE_SET_B,
                                                     XBL_CONFIG_PARTITION,
                                                     &recovery_partition_id,
                                                     &partition_id_size);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_XBLCFG_PARTITION_ID, (void **)&partition_id);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (boot_recovery_is_booting_from_recovery_partition(partition_id, (uint8*)recovery_partition_id) != TRUE)
    {
      //erase first 4 bytes SET A
      write_status = boot_write_to_partition(partition_id, NULL, 0, (uint8*)xcfg_buffer, xcfg_buffer_size);
      if (write_status != TRUE)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_XCFG_WRITE_FAIL);
        break;
      }
    }
    else
    {
      //erase first 4 bytes SET B
      write_status = boot_write_to_partition((uint8*)recovery_partition_id, NULL, 0, (uint8*)xcfg_buffer, xcfg_buffer_size);
      if (write_status != TRUE)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_XCFG_WRITE_FAIL);
        break;
      }
    }

    status = boot_config_context_get_ptr (CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_RESET_INTERFACE, (void **)&reset_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    //hard reset
    status = reset_if->hw_reset(BOOT_HARD_RESET_TYPE);
    if (status != BL_ERR_NONE)
    {
      break;
    }

  }while(FALSE);


return status;

}

/*===========================================================================
**  Function :  cfg_select_partition
** ==========================================================================
*/
/*!
*
* @brief
*   This function selects the xbl config primary/secondary partition by reading the first 4 bytes from storage partition and checking the elf value
*
* @param[in]
*  config_context_handle
*
* @param[out]
*  None
*
* @par Dependencies
*   None
*
* @retval
*   status = BL_ERR_NONE if no error, else error value
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type cfg_select_partition(boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boolean read_status = FALSE;
  boot_media_type boot_device = NO_FLASH;
  boot_media_family media_family = BOOT_MEDIA_FAMILY_MAX;
  const uint8 * partition_id = NULL;
  uint8 partition_id_size = 0;
  const uint8 * recovery_partition_id = NULL;
  uint8 recovery_partition_id_size = 0;
  uint8 elf_magic[] = {0x7F, 'E', 'L', 'F'};
  uint8 elf_magic_size = sizeof(elf_magic);
  uint8 xcfg_buffer[] = {0, 0, 0, 0};
  boot_partition_if_type * partition_if = NULL;

  do
  {
    status = boot_config_context_get_value(config_context_handle, CONFIG_CONTEXT_BOOT_DEVICE, (void *)&boot_device);


    /* Get media family */
    status = get_boot_media_family(boot_device,
                                          &media_family);

    if (status != BL_ERR_NONE)
    {
      break;
    }


    /* Get BootPartitionLib interface pointer */
    status = boot_config_context_get_ptr(config_context_handle, 
                                                CONFIG_CONTEXT_PARTITION_INTERFACE, 
                                                (void **)&partition_if);

    if (status != BL_ERR_NONE)
    {
      break;
    }

    /* Check for NULL pointer */
    if (partition_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_NULL_PTR_PASSED);
      break;
    }
  
  
    /* XBLConfig partition and recovery partition ids */
    status = partition_if->get_partition_id_by_partition(media_family,
                                                                IMAGE_SET_A,
                                                                XBL_CONFIG_PARTITION,
                                                                &partition_id,
                                                                &partition_id_size);

    if (status != BL_ERR_NONE)
    {
      break;
    }
  
  
    status = partition_if->get_partition_id_by_partition(media_family,
                                                                IMAGE_SET_B,
                                                                XBL_CONFIG_PARTITION,
                                                                &recovery_partition_id,
                                                                &recovery_partition_id_size);   

    if (status != BL_ERR_NONE)
    {
      /* If error is returned then a recovery image set does not exist.
        Clear the error and set the recovery image partition id to null. */
      CLEAR_ERROR_CODE;
      recovery_partition_id = NULL;
      status = BL_ERR_NONE;
    }


    status = boot_config_context_set_ptr(config_context_handle, 
                                                CONFIG_CONTEXT_XBLCFG_PARTITION_ID, 
                                                (void *)partition_id);

    if (status != BL_ERR_NONE)
    {
      break;
    }


    status = boot_config_context_set_ptr(config_context_handle, 
                                                CONFIG_CONTEXT_XBLCFG_RECOVERY_PARTITION_ID, 
                                                (void *)recovery_partition_id);

    if (status != BL_ERR_NONE)
    {
      break;
    }

    //read first 4 bytes & cmp elf magic (set A)
    read_status = boot_read_from_partition((uint8*)partition_id, NULL, 0, (uint8*)xcfg_buffer, elf_magic_size);
    if (read_status != TRUE)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_XCFG_READ_FAIL);
      break;
    }
  
    if(memcmp(xcfg_buffer, elf_magic, elf_magic_size) != 0)
    {
      if (recovery_partition_id != NULL)
      {
        //read first 4 bytes & cmp elf magic (set B)
        read_status = boot_read_from_partition((uint8*)recovery_partition_id, NULL, 0, (uint8*)xcfg_buffer, elf_magic_size);
        if (read_status != TRUE)
        {
          status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_XCFG_READ_FAIL);
          break;
        }

        if(memcmp(xcfg_buffer, elf_magic, elf_magic_size) == 0)
        {
          /* Set current_image_set to image_set_b*/
          status = boot_config_context_set_ptr (CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PARTITION_ID, (uint8*)recovery_partition_id);
          if (status != BL_ERR_NONE)
          {
            break;
          }

          status = boot_config_context_set_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_XBLCFG_PARTITION_ID, (uint8*)recovery_partition_id);
          if (status != BL_ERR_NONE)
          {
            break;
          }
        }
        else
        {
          status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_XCFG_PARTITION_AB_CORRUPTED);
          break;
        }
      }
      else
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_XBL_CONFIG, BL_ERR_XCFG_PARTITION_A_CORRUPTED);
      }
    }

  }while(FALSE);

return status;
}

/*===========================================================================
**  Function :  cfg_item_add_partitioninfo_to_smem
** ==========================================================================
*/
/*!
*
* @brief
*   This function copies good and corrupted partition ids to smem
*
* @retval
*   config_status_type   Status of operation
*
*/
bl_error_boot_type cfg_item_add_partitioninfo_to_smem()
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_partition_if_type * partition_if = NULL;
  boot_media_type boot_device = NO_FLASH;
  boot_media_family media_family = BOOT_MEDIA_FAMILY_MAX;
  uint8 *partition_id = NULL;
  uint8 *recovery_partition_id = NULL;
  const uint8 * XBLConfig_partition_id = NULL;
  uint8 partition_id_size = 0;

  do
  {
    /* Get boot device from the config table */
    status = boot_config_context_get_value(CONFIG_CONTEXT_CRT_HANDLE,
                                                  CONFIG_CONTEXT_BOOT_DEVICE,
                                                  (void *)&boot_device);

    if (status != BL_ERR_NONE)
    {
      break;
    }


    /* Get media family */
    status = get_boot_media_family(boot_device,
                                          &media_family);

    if (status != BL_ERR_NONE)
    {
      break;
    }


    /* Get partition interface pointer */
    status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, 
                                         CONFIG_CONTEXT_PARTITION_INTERFACE, 
                                         (void **)&partition_if);

    if (status != BL_ERR_NONE)
    {
      break;
    }

    /* Check for null pointer */
    if (partition_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION, BL_ERR_NULL_PTR_PASSED);
      break;
    }
  
  
    /* Get XBLConfig partition id */
    status = partition_if->get_partition_id_by_partition(media_family,
                                                         IMAGE_SET_A,
                                                         XBL_CONFIG_PARTITION,
                                                         &XBLConfig_partition_id,
                                                         &partition_id_size);

    if (status != BL_ERR_NONE)
    {
      break;
    }


    status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_XBLCFG_PARTITION_ID, (void **)&partition_id);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_XBLCFG_RECOVERY_PARTITION_ID, (void **)&recovery_partition_id);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (recovery_partition_id != NULL)
    {
      if (boot_recovery_is_booting_from_recovery_partition(partition_id, recovery_partition_id) == TRUE)
      {
        status = boot_recovery_add_recovery_info_internal((uint8 *)XBLConfig_partition_id, recovery_partition_id, 0, 0);
        if (status != BL_ERR_NONE)
        {
          break;
        }
      }
    }
  }while(FALSE);
  
  return status;
} 
