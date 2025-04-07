/*===========================================================================

                       Recovery Boot Loader Source File

GENERAL DESCRIPTION
  This file contains functions to read/write Recovery Boot Info to recovery_boot_info_partition

Copyright 2023 Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ------------------------------------------------------------
02/23/23   vk      Initial revision
=============================================================================*/

/*=============================================================================
                            INCLUDE FILES FOR MODULE
=============================================================================*/
#include <string.h>

#include <RecoveryBootInfoLib.h>
#include <boot_partition_rw.h>
#include <recovery_boot_info.h>
#include <boot_partition.h>
#include <boot_partition_legacy.h>
#include <boot_config_context.h>
#include <boot_error_if.h>
#include <boot_media_interface_if.h>
#include <boot_logger_if.h>
#include <crc.h>
static recovery_boot_info_type recovery_boot_info;
uint32 recovery_boot_info_size = sizeof(recovery_boot_info_type);

/*==============================================================================
**  Functions
**============================================================================*/

/*=========================================================================

**  Function :  rbi_read_partition

** ==========================================================================
*/
/*!
*
* @brief
*   This api reads recovery boot info from storage
*
*/
recovery_boot_status rbi_get_recovery_boot_info(recovery_boot_info_type **recovery_boot_info_ptr)
{
  boolean read_status = FALSE;
  recovery_boot_status status = RBI_SUCCESS;
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
      status = RBI_ERR;
      break;
    }


    bl_status = boot_config_context_get_value(CONFIG_CONTEXT_CRT_HANDLE,
                                              CONFIG_CONTEXT_CURRENT_IMAGE_SET,
                                              (void *)&current_image_set);

    if (bl_status != BL_ERR_NONE)
    {
      status = RBI_ERR;
      break;
    }


    /* Get Media family */
    bl_status = get_boot_media_family(boot_device,
                                      &media_family);

    if (bl_status != BL_ERR_NONE)
    {
      status = RBI_ERR;
      break;
    }


    /* Get partition interface pointer */
    bl_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, 
                                            CONFIG_CONTEXT_PARTITION_INTERFACE, 
                                            (void **)&partition_if);
  
    if (bl_status != BL_ERR_NONE)
    {
      status = RBI_ERR;
      break;
    }

    /* Null pointer check */
    if (partition_if == NULL)
    {
      bl_status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION,
                                 BL_ERR_NULL_PTR_PASSED);
      status = RBI_ERR;
      break;
    }


    /* Get partition id */
    bl_status = partition_if->get_partition_id_by_partition(media_family,
                                                            current_image_set,
                                                            RECOVERY_BOOT_INFO_PARTITION,
                                                            &partition_id,
                                                            &partition_id_size);
  
    if (bl_status != BL_ERR_NONE)
    {
      status = RBI_ERR;
      break;
    }


    if(recovery_boot_info_ptr == NULL)
    {
      status = RBI_NULL_PTR;
      break;
    }

    *recovery_boot_info_ptr = &recovery_boot_info;

    if(recovery_boot_info.magic_cookie == RBI_MAGIC_COOKIE)
    {
      break;
    }

    read_status = boot_read_from_partition((uint8*)partition_id, NULL, 0, (uint8*)&recovery_boot_info, recovery_boot_info_size);
    if(read_status != TRUE)
    {
      status = RBI_READ_ERR;
      break;
    }

    if(recovery_boot_info.magic_cookie != RBI_MAGIC_COOKIE)
    {
      memset ((void*)&recovery_boot_info, 0, sizeof (recovery_boot_info_type));

      recovery_boot_info.magic_cookie          = RBI_MAGIC_COOKIE;
      recovery_boot_info.version               = RBI_CURRENT_VERSION;
      recovery_boot_info.image_set_status      = SET_AB_USABLE;
      recovery_boot_info.owner                 = OWNER_XBL;
      recovery_boot_info.boot_set.magic        = 0;
      recovery_boot_info.boot_set.selected_set = BOOT_SET_INVALID;
    }
    else
    {
      /* If crc enabled, check crc */
      if (recovery_boot_info.recovery_boot_info_crc_enable_magic == RBI_CRC_MAGIC)
      {
        uint32 calculated_crc32 = 0;
        uint16 recoveryinfo_crc_size = 0;
        
        recoveryinfo_crc_size = sizeof (recovery_boot_info_type) -
                                sizeof (recovery_boot_info.recovery_boot_info_crc) -
                                sizeof (recovery_boot_info.recovery_boot_info_crc_enable_magic);
        
        calculated_crc32 = crc_32_calc ((uint8*)&recovery_boot_info, recoveryinfo_crc_size, RBI_CRC32_DEFAULT_SEED);
        if (calculated_crc32 != recovery_boot_info.recovery_boot_info_crc)
        {
          rbi_log_message ("RBOOT: CRC fail");
          memset ((void*)&recovery_boot_info, 0, sizeof (recovery_boot_info_type));
          recovery_boot_info.magic_cookie          = RBI_MAGIC_COOKIE;
          recovery_boot_info.version               = RBI_CURRENT_VERSION;
          recovery_boot_info.image_set_status      = SET_AB_USABLE;
          recovery_boot_info.owner                 = OWNER_UEFI;
          recovery_boot_info.boot_set.magic        = 0;
          recovery_boot_info.boot_set.selected_set = BOOT_SET_INVALID;
        }      
      }
    }
  }while(FALSE);

  return status;
}

/*=========================================================================

**  Function :  rbi_write_partition

** ==========================================================================
*/
/*!
*
* @brief
*   This api writes recovery boot info to storage
*
*/
recovery_boot_status rbi_write_partition(recovery_boot_info_type *recovery_boot_info_ptr)
{
  boolean write_status = FALSE;
  recovery_boot_status status = RBI_SUCCESS;
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
    status = RBI_ERR;
    goto exit;
  }


  bl_status = boot_config_context_get_value(CONFIG_CONTEXT_CRT_HANDLE,
                                            CONFIG_CONTEXT_CURRENT_IMAGE_SET,
                                            (void *)&current_image_set);

  if (bl_status != BL_ERR_NONE)
  {
    status = RBI_ERR;
    goto exit;
  }


  /* Get Media family */
  bl_status = get_boot_media_family(boot_device,
                                    &media_family);

  if (bl_status != BL_ERR_NONE)
  {
    status = RBI_ERR;
    goto exit;
  }


  /* get partition interface pointer */
  bl_status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, 
                                          CONFIG_CONTEXT_PARTITION_INTERFACE, 
                                          (void **)&partition_if);

  if (bl_status != BL_ERR_NONE)
  {
    status = RBI_ERR;
    goto exit;
  }

  /* Null pointer check */
  if (partition_if == NULL)
  {
    bl_status = GET_ERROR_CODE(BL_ERROR_GROUP_BOOT_PARTITION,
                               BL_ERR_NULL_PTR_PASSED);
    status = RBI_ERR;
    goto exit;
  }


  /* get partition id */
  bl_status = partition_if->get_partition_id_by_partition(media_family,
                                                          current_image_set,
                                                          RECOVERY_BOOT_INFO_PARTITION,
                                                          &partition_id,
                                                          &partition_id_size);

  if (bl_status != BL_ERR_NONE)
  {
    status = RBI_ERR;
    goto exit;
  }

  /* If crc enabled, update with crc */
  if ((recovery_boot_info_ptr->magic_cookie == RBI_MAGIC_COOKIE) &&
      (recovery_boot_info_ptr->recovery_boot_info_crc_enable_magic == RBI_CRC_MAGIC))
  {
    uint32 calculated_crc32 = 0;
    uint16 recoveryinfo_crc_size = 0;
        
    recoveryinfo_crc_size = sizeof (recovery_boot_info_type) -
                            sizeof (recovery_boot_info.recovery_boot_info_crc) -
                            sizeof (recovery_boot_info.recovery_boot_info_crc_enable_magic);
        
    calculated_crc32 = crc_32_calc ((uint8*)&recovery_boot_info_ptr, recoveryinfo_crc_size, RBI_CRC32_DEFAULT_SEED);
    
    recovery_boot_info_ptr->recovery_boot_info_crc = calculated_crc32;
  }

  write_status = boot_write_to_partition((uint8*)partition_id, NULL, 0, (uint8*)recovery_boot_info_ptr, recovery_boot_info_size);
  if(write_status != TRUE)
  {
    status = RBI_WRITE_ERR;
  }
  

 exit:
  return status;
}


recovery_boot_status rbi_log_message (char* message)
{
  boot_log_message (message);
  return RBI_SUCCESS;
}

